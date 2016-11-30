#include "VolumeControl.h"
#include "AVSet.h"
#include "Audio/Audio.h"
#include "GxLock.h"
#include "GXNotify.h"

#define ESPECIAL_DEFINE 0	//���⴦��

#define ELAPSE_ADD_VOLUME 500

map<int,VolumeModule*> VolumeControl::mapVolumeModule;
wstring VolumeControl::wsModule;	//��ǰ���ڿ���������ģ��
int VolumeControl::iModule;	//��ǰ���ڿ���ģ��������ID
int VolumeControl::iMachineVolume = -1;	//��ǰ��������
bool VolumeControl::bSetMute = false;

HANDLE VolumeControl::hThreadIncreaseVolume = NULL;	//�����������߳̾��
HANDLE VolumeControl::hThreadDecreaseVolume = NULL;	//�����������߳̾��

bool VolumeControl::bIncreaseVolumeing = false;	//�����Ƿ����еı�־λ
bool VolumeControl::bDecreaseVolumeing = false;	//�����Ƿ񽥽��еı�־λ

// �¼�֪ͨ
HANDLE VolumeControl::hIncreaseVolumeEvent = NULL;
HANDLE VolumeControl::hDecreaseVolumeEvent = NULL;

GxLock VolumeControl::lock;

void VolumeControl::Init()
{
	//��������δʼ��ʱ����ʼ��
	if(iMachineVolume == -1)
	{

		if(!CheckMachineVolumeValid(sysConfig.sysParam.curVol))
		{
			sysConfig.sysParam.curVol = 16;	//Ĭ��ֵ
		}

		if(sysConfig.sysParam.curVol > 16)
		{
			sysConfig.sysParam.curVol = 16;
		}
		iMachineVolume = sysConfig.sysParam.curVol;

	}
}

//�������������Ȩ��
bool VolumeControl::ApplayForPermission(int ModuleID, int iVolume,wstring wsName)
{
	//��������δʼ��ʱ����ʼ��
	if(iMachineVolume == -1)
	{

		if(!CheckMachineVolumeValid(sysConfig.sysParam.curVol))
		{
			sysConfig.sysParam.curVol = 16;	//Ĭ��ֵ
		}

		if(sysConfig.sysParam.curVol > 16)
		{
			sysConfig.sysParam.curVol = 16;
		}
		iMachineVolume = sysConfig.sysParam.curVol;
		
	}

	if(!VolumeModuleId::CheckModuleId(ModuleID))	//������Χ
	{
		return false;
	}

	VolumeModule* module;

	module= SeekModule(ModuleID);
	if(module == NULL)	//������
	{
		module = new VolumeModule;
		//����һ��ID
		module->iId = ModuleID;
		
		mapVolumeModule.insert(pair<int,VolumeModule*>(ModuleID, module));
	}
	

	//��ʼ��
	module->wsName = wsName;
	
	int iVolumeAddorSubtract = VolumeEPROMAction::VolumeAddOrSubGet(ModuleID);
	if(CheckAddOrSubtractVolumeValid(iVolumeAddorSubtract))	//��������Ƿ�Ϸ�
	{
		module->iVolumeAddorSubtract = iVolumeAddorSubtract;
		module->iVolume = iMachineVolume + iVolumeAddorSubtract;	
	}
	else
	{
		module->iVolumeAddorSubtract = 0;
		module->iVolume = iVolume;	//ʹ��Ĭ������
	}
	
	return true;
}

//�趨�ض�ģ������
//bool VolumeControl::SetVolumeForModule(int ModuleID, int iVolume)
//{
//	if(!VolumeModuleId::CheckModuleId(ModuleID))	//ģ��ţ�������Χ
//	{
//		return false;
//	}
//
//	if(!CheckMachineVolumeValid(iVolume))	//������������Χ
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
//		//������������������
//		VolumeEPROMAction::VolumeSaveAddOrSub(ModuleID, iVolume - iMachineVolume);
//		return true;
//	}
//
//	return false;
//}

//�趨�ض�ģ����������������
bool VolumeControl::SetVolumeAddOrSubForModule(int ModuleID, int iVolume, bool bIsEffect)	//����bIsEffect�����Ƿ�������Ч
{
	if(!VolumeModuleId::CheckModuleId(ModuleID))	//ģ��ţ�������Χ
	{
		return false;
	}

	if(!CheckAddOrSubtractVolumeValid(iVolume))	//������������Χ
	{
		return false;
	}


	VolumeModule* module = SeekModule(ModuleID);
	
	if(module != NULL)
	{
		module->iVolumeAddorSubtract = iVolume;

		//������������������
		VolumeEPROMAction::VolumeSaveAddOrSub(ModuleID, iVolume);

		if(bIsEffect)	//������Ч
		{
			//����ģ������
			module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);

			if(iModule == ModuleID)	//����ǵ�ǰģ�飬���������仯
			{
				AVSET::SetVolume(module->iVolume);
			}		


		}

		//if(sysConfig.sysParam.naviTips == 1)	//������
		{
			sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
			Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
		}

		return true;
	}

	return false;
}

//������������
bool VolumeControl::ApplyForVolumeControl(int iId)
{
	VolumeModule* module = SeekModule(iId);

	if(module != NULL)
	{
		iModule = module->iId;
		wsModule = module->wsName;

		//����ģ������
		module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);

		AVSET::SetVolume(module->iVolume);
		AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"SetVolume", 0);
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d, %s AddOrSub = %d\r\n"),
			iMachineVolume, wsModule.c_str(), module->iVolumeAddorSubtract));


		//if(sysConfig.sysParam.naviTips == 1)	//������
		{
			sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
			Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
		}

	}

	return false;
}

int VolumeControl::CalculateModuleVolume(int iVolumeAddorSubtract)
{
	//����ģ������
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

//���ص�ǰģ������,ʧ��ʱ������-1
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

//�Ӵ��������
bool VolumeControl::AddVolume()
{
	iMachineVolume ++;
	if(iMachineVolume > Audio::MaxVolume)
	{
		iMachineVolume = Audio::MaxVolume;
	}
	//�����������
	VolumeEPROMAction::MachineVolumeSave(iMachineVolume);

	VolumeModule* module = SeekModule(iModule);
	if(module != NULL)											//��ǰ��ģ��ʱ���趨ģ������
	{
		//����ģ������
		module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);

		if(!bIncreaseVolumeing)	//���������У��������仯
		{
			AVSET::SetVolume(module->iVolume);
			RETAILMSG(COUT_MSG, (TEXT("MODULE VOL = %d \r\n"), module->iVolume));
		}
		
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d, %s AddOrSub = %d\r\n"),
			iMachineVolume, wsModule.c_str(), module->iVolumeAddorSubtract));
	}
	else														//��ǰ��ģ��ʱ���趨��������
	{ 
		AVSET::SetVolume(iMachineVolume);
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d\r\n"), iMachineVolume));
	}
	
	//if(sysConfig.sysParam.naviTips == 1)	//������
	{
		sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
		Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	}
	
	
	return true;
}

/************************************************************************/
/* �ú��������趨�����������ء�
   �������ã���Ϊ�˼��ݣ���������*/
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
���ܣ��趨���������뵼������֮�������
������Χ��0-15

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

//���ģ������,ʧ��ʱ������-1
int VolumeControl::GetCurrentModuleVolume(int iModule)
{
	int iVolume = -1;

	if(!VolumeModuleId::CheckModuleId(iModule))	//������Χ
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

//���ģ����������������,ʧ��ʱ������-1
int VolumeControl::GetCurrentModuleAddOrSubVolume(int iModule)
{
	int iVolume = -1;

	if(!VolumeModuleId::CheckModuleId(iModule))	//������Χ
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

//��������
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
//		//��������
//		VolumeEPROMAction::VolumeSave(iModule, module->iVolume);
//
//		//AfxPostMessage(CTR_VOLUME_MES, module->iVolume, 0);
//		RETAILMSG(COUT_MSG,(TEXT("%s volume = %d\r\n"), wsModule.c_str(), module->iVolume));
//		return true;
//	}
//
//	return false;
//}

//�趨��������
bool VolumeControl::SetMachineVolume(int iVolume)
{

	if(!CheckMachineVolumeValid(iVolume))	//�ж�������Χ
	{
		return false;
	}

	iMachineVolume = iVolume;

	VolumeModule* module = SeekModule(iModule);

	if(module != NULL)	//��ǰ��ģ�����ڿ���������
	{
		
		int iAddOrSubVolume = GetCurrentModuleAddOrSubVolume(iModule);
		module->iVolume = iMachineVolume + iAddOrSubVolume;
		//����ģ������
		AVSET::SetVolume(module->iVolume);
	}
	else
	{
		//����ģ������
		AVSET::SetVolume(iMachineVolume);
	}

	//�����������
	VolumeEPROMAction::MachineVolumeSave(iMachineVolume);

	return true;
}

//��С����
bool VolumeControl::DecreaseVolume()
{
	iMachineVolume --;
	if(iMachineVolume < 0)
	{
		iMachineVolume = 0;
	}

	//�����������
	VolumeEPROMAction::MachineVolumeSave(iMachineVolume);

	VolumeModule* module = SeekModule(iModule);
	if(module != NULL)											//��ǰ��ģ��ʱ���趨ģ������
	{
		//����ģ������
		if(iMachineVolume == 0)		//����������Ϊ0������ҲΪ0
		{
			module->iVolume = 0;
		}
		else	//������������Ϊ0ʱ��������������ģ�������
		{
			module->iVolume = CalculateModuleVolume(module->iVolumeAddorSubtract);
		}
		
		if(!bIncreaseVolumeing)	//���������У��������仯
		{
			AVSET::SetVolume(module->iVolume);
		}
		
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d, %s AddOrSub = %d\r\n"),
			iMachineVolume, wsModule.c_str(), module->iVolumeAddorSubtract));
	}
	else														//��ǰ��ģ��ʱ���趨��������
	{
		AVSET::SetVolume(iMachineVolume);
		RETAILMSG(COUT_MSG,(TEXT("machine volume = %d\r\n"), iMachineVolume));
	}

	//if(sysConfig.sysParam.naviTips == 1)	//������
	{
		sysConfig.sysParam.curGPSVol = VolumeControl::CalculateNaviVolume();
		Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	}

	return true;
}

//ͨ��ģ��ID����ģ��
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
		//����һ��
		if(VolumeModuleId::CheckModuleId(iModuleid))	//��������Χ
		{
			module = new VolumeModule;
			//����һ��ID
			module->iId = iModuleid;

			mapVolumeModule.insert(pair<int,VolumeModule*>(iModuleid, module));
		}
	}
	
	
	return module;
}

//����������Χ�Ƿ�Ϸ� 
bool VolumeControl::CheckMachineVolumeValid(int iVolume)
{
	if(iVolume >= 0 && iVolume <= Audio::MaxVolume)
	{
		return true;
	}
	return false;
}

//�������������Ʒ�Χ�Ƿ�Ϸ� 
bool VolumeControl::CheckAddOrSubtractVolumeValid(int iVolume)
{
	if(iVolume >= VOLUME_SUB && iVolume <= VOLUME_ADD)
	{
		return true;
	}
	return false;
}
//ȡ������������������
void VolumeControl::UnMuteAndSlowlyIncreaseVolume()
{

	//Sleep(100);
	SlowlyIncreaseVolume();
}

//����������������
void VolumeControl::SlowlyDecreaseVolumeAndMute()
{
//	Sleep(100);
	bSetMute = true;
	SlowlyDecreaseVolume();
	
}

//��������
void VolumeControl::SlowlyDecreaseVolume()
{
	DWORD dwThreadID = 0;
	if(hThreadDecreaseVolume == NULL)
	{

		// �����¼�
		hDecreaseVolumeEvent = CreateEvent(NULL,0,0,NULL);
		hThreadDecreaseVolume = (HANDLE)::CreateThread(NULL,0,DecreaseVolumeThread,NULL,0,&dwThreadID);

	}

	StartSlowlyDecreaseVolume();
	
}

void VolumeControl::StartSlowlyDecreaseVolume()
{
	//��������������������������������߳�	
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

//��������
void VolumeControl::SlowlyIncreaseVolume()
{
	//����ʱ����ִ��
	if(sysConfig.bMute)
	{
		return;
	}
	DWORD dwThreadID = 0;
	if(hThreadIncreaseVolume == NULL)
	{
		
		// �����¼�
		hIncreaseVolumeEvent = CreateEvent(NULL,0,0,NULL);
		hThreadIncreaseVolume = (HANDLE)::CreateThread(NULL,0,IncreaseVolumeThread,NULL,0,&dwThreadID);
		
	}

	StartSlowlyIncreaseVolume();
	
}

void VolumeControl::StartSlowlyIncreaseVolume()
{
	//��������������������������������߳�
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
		//����ģ������
		int Volume = CalculateModuleVolume(iAddOrSubVolume);
		int iElapse = ELAPSE_ADD_VOLUME;

		if(Volume > 0)
		{
			iElapse = ELAPSE_ADD_VOLUME / Volume;
		}

		

		while(Volume >= 0)
		{

			AVSET::SetVolume(Volume);
			//���
			Sleep(iElapse);
			RETAILMSG(COUT_MSG, (L"volume %d\r\n", Volume));
			Volume--;

			//�ٻ��ģ����������Ϊ���������������У�ģ���������ܱ��ı䡣
			//Volume = CalculateModuleVolume(iAddOrSubVolume);

			//�������̣������
			if(!bDecreaseVolumeing)
			{
				break;
			}
		}

		//������һ����������֤������ȷ

		if(VolumeControl::bDecreaseVolumeing && !VolumeControl::bIncreaseVolumeing)	//����û�б����
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
		//����ģ������
		int Volume = CalculateModuleVolume(iAddOrSubVolume);
		
		int iElapse = ELAPSE_ADD_VOLUME; 

		if(Volume > 0)
		{
			iElapse = ELAPSE_ADD_VOLUME / Volume;
		}
		

		if(!sysConfig.bMute)
		{
			//AVSET::Mute();
			Audio::MuteNoKeyTone();	//Ϊ�˱��ⰴ���������������������
		}
		AVSET::SetVolume(0);
		Sleep(50);		//�ӳ�һ�£�Ҫ��Ȼ�������ȴ���һ��
		AVSET::UnMute();
		
		while(i <= Volume)
		{
			i++;

			AVSET::SetVolume(i);
			//���
			Sleep(iElapse);
			RETAILMSG(COUT_MSG, (L"volume %d\r\n", i));
			

			//�ٻ��ģ����������Ϊ���������������У�ģ���������ܱ��ı䡣
			Volume = CalculateModuleVolume(iAddOrSubVolume);

			//�������̣������
			if(!bIncreaseVolumeing)
			{
				break;
			}
		}

		//������һ����������֤������ȷ

		if(bIncreaseVolumeing && !bDecreaseVolumeing)	//����û�б����
		{
			//�ٻ��ģ����������Ϊ���������������У�ģ���������ܱ��ı䡣
			Volume = CalculateModuleVolume(iAddOrSubVolume);
			AVSET::SetVolume(Volume);
		}
		
		bIncreaseVolumeing = false;

		lock.UnLock();
	}
	
	
	return 0;
}