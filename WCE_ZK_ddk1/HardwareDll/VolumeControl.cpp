#include "VolumeControl.h"
#include "AVSet.h"
#include "Audio/Audio.h"
#include "GxLock.h"
#include "GXNotify.h"

#define ESPECIAL_DEFINE 0	//特殊处理

#define ELAPSE_ADD_VOLUME 500

map<int,VolumeModule*> VolumeControl::mapVolumeModule;
wstring VolumeControl::wsModule;	//当前正在控制音量的模块
int VolumeControl::iModule;	//当前正在控制模块音量的ID
int VolumeControl::iMachineVolume = -1;	//当前机器音量
bool VolumeControl::bSetMute = false;

HANDLE VolumeControl::hThreadIncreaseVolume = NULL;	//音量缓升的线程句柄
HANDLE VolumeControl::hThreadDecreaseVolume = NULL;	//音量缓降的线程句柄

bool VolumeControl::bIncreaseVolumeing = false;	//音量是否渐升中的标志位
bool VolumeControl::bDecreaseVolumeing = false;	//音量是否渐降中的标志位

// 事件通知
HANDLE VolumeControl::hIncreaseVolumeEvent = NULL;
HANDLE VolumeControl::hDecreaseVolumeEvent = NULL;

GxLock VolumeControl::lock;

void VolumeControl::Init()
{
	//机器音量未始化时，初始化
	if(iMachineVolume == -1)
	{

		if(!CheckMachineVolumeValid(sysConfig.sysParam.curVol))
		{
			sysConfig.sysParam.curVol = 16;	//默认值
		}

		if(sysConfig.sysParam.curVol > 16)
		{
			sysConfig.sysParam.curVol = 16;
		}
		iMachineVolume = sysConfig.sysParam.curVol;

	}
}

//申请控制音量的权限
bool VolumeControl::ApplayForPermission(int ModuleID, int iVolume,wstring wsName)
{
	//机器音量未始化时，初始化
	if(iMachineVolume == -1)
	{

		if(!CheckMachineVolumeValid(sysConfig.sysParam.curVol))
		{
			sysConfig.sysParam.curVol = 16;	//默认值
		}

		if(sysConfig.sysParam.curVol > 16)
		{
			sysConfig.sysParam.curVol = 16;
		}
		iMachineVolume = sysConfig.sysParam.curVol;
		
	}

	if(!VolumeModuleId::CheckModuleId(ModuleID))	//超出范围
	{
		return false;
	}

	VolumeModule* module;

	module= SeekModule(ModuleID);
	if(module == NULL)	//不存在
	{
		module = new VolumeModule;
		//分配一个ID
		module->iId = ModuleID;
		
		mapVolumeModule.insert(pair<int,VolumeModule*>(ModuleID, module));
	}
	

	//初始化
	module->wsName = wsName;
	
	int iVolumeAddorSubtract = VolumeEPROMAction::VolumeAddOrSubGet(ModuleID);
	if(CheckAddOrSubtractVolumeValid(iVolumeAddorSubtract))	//检查音量是否合法
	{
		module->iVolumeAddorSubtract = iVolumeAddorSubtract;
		module->iVolume = iMachineVolume + iVolumeAddorSubtract;	
	}
	else
	{
		module->iVolumeAddorSubtract = 0;
		module->iVolume = iVolume;	//使用默认音量
	}
	
	return true;
}

//设定特定模块音量
//bool VolumeControl::SetVolumeForModule(int ModuleID, int iVolume)
//{
//	if(!VolumeModuleId::CheckModuleId(ModuleID))	//模块号，超出范围
//	{
//		return false;
//	}
//
//	if(!CheckMachineVolumeValid(iVolume))	//音量，超出范围
//	{
//		return false;
//	}
//	
//
//	VolumeModule* module = SeekModule(ModuleID);
//
//	if(module != NULL)
//	{
//		module->iVolume = iVolume;
//		//保存音量增幅或抑制
//		VolumeEPROMAction::VolumeSaveAddOrSub(ModuleID, iVolume - iMachineVolume);
//		return true;
//	}
//
//	return false;
//}

//设定特定模块音量增幅或抑制
bool VolumeControl::SetVolumeAddOrSubForModule(int ModuleID, int iVolume, bool bIsEffect)	//参数bIsEffect设置是否立即生效
{
	if(!VolumeModuleId::CheckModuleId(ModuleID))	//模块号，超出范围
	{
		return false;
	}

	if(!CheckAddOrSubtractVolumeValid(iVolume))	//音量，超出范围
	{
		return false;
	}


	VolumeModule* module = SeekModule(ModuleID);
	
	if(module != NULL)
	{
		module->iVolumeAddorSubtract = iVolume;

		//保存音量增幅或抑制
		VolumeEPROMAction::VolumeSaveAddOrSub(ModuleID, iVolume);

		if(bIsEffect)	//立即生效
		{
			//计算模块音量
			module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);

			if(iModule == ModuleID)	//如果是当前模块，声音产生变化
			{
				AVSET::SetVolume(module->iVolume);
			}		


		}

		//if(sysConfig.sysParam.naviTips == 1)	//不混音
		{
			sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
			Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
		}

		return true;
	}

	return false;
}

//申请音量控制
bool VolumeControl::ApplyForVolumeControl(int iId)
{
	VolumeModule* module = SeekModule(iId);

	if(module != NULL)
	{
		iModule = module->iId;
		wsModule = module->wsName;

		//计算模块音量
		module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);

		AVSET::SetVolume(module->iVolume);
		AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"SetVolume", 0);
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d, %s AddOrSub = %d\r\n"),
			iMachineVolume, wsModule.c_str(), module->iVolumeAddorSubtract));


		//if(sysConfig.sysParam.naviTips == 1)	//不混音
		{
			sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
			Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
		}

	}

	return false;
}

int VolumeControl::CalculateModuleVolume(int iVolumeAddorSubtract)
{
	//计算模块音量
	int iModuleVolume = iMachineVolume + iVolumeAddorSubtract;

	if(iModuleVolume > Audio::MaxVolume)
	{
		iModuleVolume = Audio::MaxVolume;
	}
	else if(iModuleVolume < 0)
	{
		iModuleVolume = 0;

	}

	return iModuleVolume;
}

//返回当前模块音量,失败时，返回-1
int  VolumeControl::GetCurrentModuleVolume()
{
	VolumeModule* module = SeekModule(iModule);

	if(module != NULL)
	{
		if(module->iVolume > Audio::MaxVolume)
		{
			module->iVolume = Audio::MaxVolume;
		}

		if(module->iVolume < 0)
		{
			module->iVolume = 0;
		}

		return module->iVolume;
	}

	return -1;
}

//加大机器音量
bool VolumeControl::AddVolume()
{
	iMachineVolume ++;
	if(iMachineVolume > Audio::MaxVolume)
	{
		iMachineVolume = Audio::MaxVolume;
	}
	//保存机器音量
	VolumeEPROMAction::MachineVolumeSave(iMachineVolume);

	VolumeModule* module = SeekModule(iModule);
	if(module != NULL)											//当前有模块时，设定模块音量
	{
		//计算模块音量
		module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);

		if(!bIncreaseVolumeing)	//音量渐升中，音量不变化
		{
			AVSET::SetVolume(module->iVolume);
			RETAILMSG(COUT_MSG, (TEXT("MODULE VOL = %d \r\n"), module->iVolume));
		}
		
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d, %s AddOrSub = %d\r\n"),
			iMachineVolume, wsModule.c_str(), module->iVolumeAddorSubtract));
	}
	else														//当前无模块时，设定机器音量
	{ 
		AVSET::SetVolume(iMachineVolume);
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d\r\n"), iMachineVolume));
	}
	
	//if(sysConfig.sysParam.naviTips == 1)	//不混音
	{
		sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
		Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	}
	
	
	return true;
}

/************************************************************************/
/* 该函数用于设定导航混音开关。
   参数无用，但为了兼容，保留参数*/
/************************************************************************/
int VolumeControl::SetNaviTip(bool bTip)
{
	
	sysConfig.sysParam.curGPSVol = CalculateNaviVolume();
	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	GXNotify::SendNotify("set_navi_vol", sysConfig.sysParam.curGPSVol, 0);
	return sysConfig.sysParam.curGPSVol;
}

bool VolumeControl::AddNaviVolPercent()
{
	sysConfig.sysParam.curGPS_Vol_Rate += 1;
	if(sysConfig.sysParam.curGPS_Vol_Rate > 15)
	{
		sysConfig.sysParam.curGPS_Vol_Rate = 15;
		sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
		return false;
	}
	//sysConfig.WriteConfig(&sysConfig.sysParam.curGPS_Vol_Rate);
	sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	//sysConfig.WriteConfig(&sysConfig.sysParam.curGPSVol);
	return true;
}

bool VolumeControl::DecNaviVolPercent()
{
	sysConfig.sysParam.curGPS_Vol_Rate -= 1;
	if(sysConfig.sysParam.curGPS_Vol_Rate < 0)
	{
		sysConfig.sysParam.curGPS_Vol_Rate = 0;
		sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
		return false;
	}
	sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);

	return true;
}

int VolumeControl::CalculateNaviVolume()
{
	if(sysConfig.sysParam.curGPS_Vol_Rate < 0)
	{
		sysConfig.sysParam.curGPS_Vol_Rate = 0;
	}
	if(sysConfig.sysParam.curGPS_Vol_Rate > 15)
	{
		sysConfig.sysParam.curGPS_Vol_Rate = 15;
	}
	
	int iCurrentModuleVolume;
	iCurrentModuleVolume = GetCurrentModuleVolume(VolumeControl::iModule);

	if(iCurrentModuleVolume == -1)
	{
		iCurrentModuleVolume = MACHINE_MAX_VOLUME;
	}

	int iGPSVol = 0;

	iGPSVol = iCurrentModuleVolume * sysConfig.sysParam.curGPS_Vol_Rate / 10;

	if(iGPSVol < 0)
	{
		iGPSVol = 0;
	}

	if(iGPSVol > 35)
	{
		iGPSVol = 35;
	}
	RETAILMSG(COUT_MSG, (TEXT("curGPS_Vol_Rate = %d, GPS_vol= %d \n"), 
		sysConfig.sysParam.curGPS_Vol_Rate, iGPSVol));
	//sysConfig.WriteConfig(&sysConfig.sysParam.curGPSVol);
	
	return iGPSVol;
}

/***********************
功能：设定机器音量与导航音量之间的增益
参数范围：0-15

************************************/
bool  VolumeControl::SetNaviVolRate(int iRate)
{
	if(iRate < 0)
	{
		return false;
	}
	if(iRate > 15)
	{
		return false;
	}
	sysConfig.sysParam.curGPS_Vol_Rate = iRate;
	
	sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);

	return true;
}


bool  VolumeControl::SetNaviVolPercent(int iPercent)
{
	if(iPercent < 0)
	{
		return false;
	}
	if(iPercent > 150)
	{
		return false;
	}
	sysConfig.sysParam.curGPS_Vol_Rate = iPercent / 10;

	//sysConfig.WriteConfig(&sysConfig.sysParam.curGPS_Vol_Rate);
	sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	//sysConfig.WriteConfig(&sysConfig.sysParam.curGPSVol);
	return true;
}

//获得模块音量,失败时，返回-1
int VolumeControl::GetCurrentModuleVolume(int iModule)
{
	int iVolume = -1;

	if(!VolumeModuleId::CheckModuleId(iModule))	//超出范围
	{
		return iVolume;
	}

	VolumeModule* module = SeekModule(iModule);

	if(module != NULL)
	{
		iVolume = module->iVolume;
	}
	return iVolume;
}

//获得模块增幅或抑制音量,失败时，返回-1
int VolumeControl::GetCurrentModuleAddOrSubVolume(int iModule)
{
	int iVolume = -1;

	if(!VolumeModuleId::CheckModuleId(iModule))	//超出范围
	{
		return iVolume;
	}

	iVolume = VolumeEPROMAction::VolumeAddOrSubGet(iModule);
	/*VolumeModule* module = SeekModule(iModule);

	if(module != NULL)
	{
		iVolume = module->iVolumeAddorSubtract;
	}*/

	return iVolume;
}

//增减音量
//bool VolumeControl::ChangeVolume(int iVolume)
//{
//
//	VolumeModule* module = SeekModule(iModule);
//
//	if(module != NULL)
//	{
//		iModule = module->iId;
//
//		module->iVolume += iVolume;
//
//		if(module->iVolume < 0)
//		{
//			module->iVolume = 0;
//		}
//
//		if(module->iVolume > Audio::MaxVolume)
//		{
//			module->iVolume = Audio::MaxVolume;
//		}
//
//		AVSET::SetVolume(module->iVolume);
//
//		//保存音量
//		VolumeEPROMAction::VolumeSave(iModule, module->iVolume);
//
//		//AfxPostMessage(CTR_VOLUME_MES, module->iVolume, 0);
//		RETAILMSG(COUT_MSG,(TEXT("%s volume = %d\r\n"), wsModule.c_str(), module->iVolume));
//		return true;
//	}
//
//	return false;
//}

//设定机器音量
bool VolumeControl::SetMachineVolume(int iVolume)
{

	if(!CheckMachineVolumeValid(iVolume))	//判断音量范围
	{
		return false;
	}

	iMachineVolume = iVolume;

	VolumeModule* module = SeekModule(iModule);

	if(module != NULL)	//当前有模块正在控制音量？
	{
		
		int iAddOrSubVolume = GetCurrentModuleAddOrSubVolume(iModule);
		module->iVolume = iMachineVolume + iAddOrSubVolume;
		//计算模块音量
		AVSET::SetVolume(module->iVolume);
	}
	else
	{
		//计算模块音量
		AVSET::SetVolume(iMachineVolume);
	}

	//保存机器音量
	VolumeEPROMAction::MachineVolumeSave(iMachineVolume);

	return true;
}

//减小音量
bool VolumeControl::DecreaseVolume()
{
	iMachineVolume --;
	if(iMachineVolume < 0)
	{
		iMachineVolume = 0;
	}

	//保存机器音量
	VolumeEPROMAction::MachineVolumeSave(iMachineVolume);

	VolumeModule* module = SeekModule(iModule);
	if(module != NULL)											//当前有模块时，设定模块音量
	{
		//计算模块音量
		if(iMachineVolume == 0)		//整机的音量为0，机器也为0
		{
			module->iVolume = 0;
		}
		else	//整机的音量不为0时，整机音量加上模块的音量
		{
			module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);
		}
		
		if(!bIncreaseVolumeing)	//音量渐升中，音量不变化
		{
			AVSET::SetVolume(module->iVolume);
		}
		
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d, %s AddOrSub = %d\r\n"),
			iMachineVolume, wsModule.c_str(), module->iVolumeAddorSubtract));
	}
	else														//当前无模块时，设定机器音量
	{
		AVSET::SetVolume(iMachineVolume);
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d\r\n"), iMachineVolume));
	}

	//if(sysConfig.sysParam.naviTips == 1)	//不混音
	{
		sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
		Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	}

	return true;
}

//通过模块ID，找模块
VolumeModule* VolumeControl::SeekModule(int iModuleid)
{
	VolumeModule* module = NULL;

	

	map<int,VolumeModule*>::iterator it;
	it = mapVolumeModule.find(iModuleid);
	if(it != mapVolumeModule.end())
	{
		module = (*it).second;
	}
	else
	{
		//创建一个
		if(VolumeModuleId::CheckModuleId(iModuleid))	//不超出范围
		{
			module = new VolumeModule;
			//分配一个ID
			module->iId = iModuleid;

			mapVolumeModule.insert(pair<int,VolumeModule*>(iModuleid, module));
		}
	}
	
	
	return module;
}

//机器音量范围是否合法 
bool VolumeControl::CheckMachineVolumeValid(int iVolume)
{
	if(iVolume >= 0 && iVolume <= Audio::MaxVolume)
	{
		return true;
	}
	return false;
}

//音量增幅或抑制范围是否合法 
bool VolumeControl::CheckAddOrSubtractVolumeValid(int iVolume)
{
	if(iVolume >= VOLUME_SUB && iVolume <= VOLUME_ADD)
	{
		return true;
	}
	return false;
}
//取消静音，并缓升音量
void VolumeControl::UnMuteAndSlowlyIncreaseVolume()
{

	//Sleep(100);
	SlowlyIncreaseVolume();
}

//缓降音量，并静音
void VolumeControl::SlowlyDecreaseVolumeAndMute()
{
//	Sleep(100);
	bSetMute = true;
	SlowlyDecreaseVolume();
	
}

//缓降音量
void VolumeControl::SlowlyDecreaseVolume()
{
	DWORD dwThreadID = 0;
	if(hThreadDecreaseVolume == NULL)
	{

		// 创建事件
		hDecreaseVolumeEvent = CreateEvent(NULL,0,0,NULL);
		hThreadDecreaseVolume = (HANDLE)::CreateThread(NULL,0,DecreaseVolumeThread,NULL,0,&dwThreadID);

	}

	StartSlowlyDecreaseVolume();
	
}

void VolumeControl::StartSlowlyDecreaseVolume()
{
	//如果正在音量渐升，结束音量渐升的线程	
	if(bIncreaseVolumeing)
	{
		DWORD dwExit = 0;
		bool bSuccess = TerminateThread(hThreadIncreaseVolume, dwExit);
		if(bSuccess)
		{
			hThreadIncreaseVolume = NULL;
			bIncreaseVolumeing = false;
			RETAILMSG(COUT_MSG, (TEXT("exit increase thread \n")));
		}
		
	}

	SetEvent(hDecreaseVolumeEvent);
}

//缓升音量
void VolumeControl::SlowlyIncreaseVolume()
{
	//静音时，不执行
	if(sysConfig.bMute)
	{
		return;
	}
	DWORD dwThreadID = 0;
	if(hThreadIncreaseVolume == NULL)
	{
		
		// 创建事件
		hIncreaseVolumeEvent = CreateEvent(NULL,0,0,NULL);
		hThreadIncreaseVolume = (HANDLE)::CreateThread(NULL,0,IncreaseVolumeThread,NULL,0,&dwThreadID);
		
	}

	StartSlowlyIncreaseVolume();
	
}

void VolumeControl::StartSlowlyIncreaseVolume()
{
	//如果正在音量渐弱，结束音量渐弱的线程
	if(bDecreaseVolumeing)
	{
		DWORD dwExit = 0;
		bool bSuccess = TerminateThread(hThreadDecreaseVolume, dwExit);
		
		if(bSuccess)
		{ 
			hThreadDecreaseVolume = NULL;
			RETAILMSG(COUT_MSG, (TEXT("exit decrease thread \n")));
			bDecreaseVolumeing = false;
		}		
		
	}

	SetEvent(hIncreaseVolumeEvent);
}

DWORD VolumeControl::DecreaseVolumeThread(LPVOID lpParam)
{
	while(true)
	{

		WaitForSingleObject(hDecreaseVolumeEvent,INFINITE);

		lock.Lock();

		bDecreaseVolumeing = true;
		
		//int iMachineVol = iMachineVolume;
		int iAddOrSubVolume = GetCurrentModuleAddOrSubVolume(iModule);
		//计算模块音量
		int Volume = CalculateModuleVolume(iAddOrSubVolume);
		int iElapse = ELAPSE_ADD_VOLUME;

		if(Volume > 0)
		{
			iElapse = ELAPSE_ADD_VOLUME / Volume;
		}

		

		while(Volume >= 0)
		{

			AVSET::SetVolume(Volume);
			//间隔
			Sleep(iElapse);
			RETAILMSG(COUT_MSG, (L"volume %d\r\n", Volume));
			Volume--;

			//再获得模块音量，因为在音量渐弱过程中，模块音量可能被改变。
			//Volume = CalculateModuleVolume(iAddOrSubVolume);

			//渐弱过程，被打断
			if(!bDecreaseVolumeing)
			{
				break;
			}
		}

		//再设置一次音量，保证音量正确

		if(VolumeControl::bDecreaseVolumeing && !VolumeControl::bIncreaseVolumeing)	//渐弱没有被打断
		{
			
			AVSET::SetVolume(Volume);

			if(bSetMute)
			{
				bSetMute = false;
				AVSET::Mute();
			}	
		}

		bDecreaseVolumeing = false;

		lock.UnLock();
	}
}

DWORD VolumeControl::IncreaseVolumeThread(LPVOID lpParam)
{
	while(true)
	{
		
		WaitForSingleObject(hIncreaseVolumeEvent,INFINITE);
		
		lock.Lock();

		bIncreaseVolumeing = true;

		int i = 0;
		int iAddOrSubVolume = GetCurrentModuleAddOrSubVolume(iModule);
		//计算模块音量
		int Volume = CalculateModuleVolume(iAddOrSubVolume);
		
		int iElapse = ELAPSE_ADD_VOLUME; 

		if(Volume > 0)
		{
			iElapse = ELAPSE_ADD_VOLUME / Volume;
		}
		

		if(!sysConfig.bMute)
		{
			//AVSET::Mute();
			Audio::MuteNoKeyTone();	//为了避免按键音被禁，调用这个函数
		}
		AVSET::SetVolume(0);
		Sleep(50);		//延迟一下，要不然机器会先大声一下
		AVSET::UnMute();
		
		while(i <= Volume)
		{
			i++;

			AVSET::SetVolume(i);
			//间隔
			Sleep(iElapse);
			RETAILMSG(COUT_MSG, (L"volume %d\r\n", i));
			

			//再获得模块音量，因为在音量渐升过程中，模块音量可能被改变。
			Volume = CalculateModuleVolume(iAddOrSubVolume);

			//渐升过程，被打断
			if(!bIncreaseVolumeing)
			{
				break;
			}
		}

		//再设置一次音量，保证音量正确

		if(bIncreaseVolumeing && !bDecreaseVolumeing)	//渐升没有被打断
		{
			//再获得模块音量，因为在音量渐升过程中，模块音量可能被改变。
			Volume = CalculateModuleVolume(iAddOrSubVolume);
			AVSET::SetVolume(Volume);
		}
		
		bIncreaseVolumeing = false;

		lock.UnLock();
	}
	
	
	return 0;
}