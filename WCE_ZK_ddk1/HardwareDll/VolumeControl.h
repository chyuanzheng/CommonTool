#pragma once
#include "StdAfx.h"
#include "HardwareDllModule.h"
#include "INC\param.h"
#include "GxLock.h"

#define MACHINE_MAX_VOLUME 35
#define NAVI_MAX_VOLUME 15

class VolumeModuleId
{
private:
	const static int START = 0;
	 
public:
	
	const static int AUX = START + 1;
	const static int DISC = START +  2;
	const static int DTV = START +  3;
	const static int IPOD = START +  4;
	const static int NAVI = START +  5; 
	const static int RADIO = START +  6;
	const static int USB = START +  7;
	const static int BTMUSIC = START +  8;
	const static int PHONE = START +  9;

private:
	const static int END = START +  10;

public:

	//检查模块ID是否合法
	static bool CheckModuleId(int iMoudleID)
	{
		if(iMoudleID > START && iMoudleID < END)
		{
			return true;
		}
		return false;
	}

};

class VolumeModule
{
public:
	int iId;	//模块ID
	////总音量
	//int iTotalVolume;
	//音量增幅或抑制
	int iVolumeAddorSubtract;
	//实际音量大小。实际音量大小 = 机器音量 + 音量增幅或抑制
	int iVolume;
	wstring wsName;	//模块名

};

class CE_HardwareDll_API VolumeControl
{
public:
	static const int  VOLUME_ADD = 14;	//增幅音量
	static const int VOLUME_SUB = -14;	//抑制音量

private:
	static std::map<int,VolumeModule*> mapVolumeModule;
	static int iMachineVolume;	//当前机器音量
	static int iNaviVolPercent;		//获得当前导航音量百分比
	static wstring wsModule;	//当前正在控制音量的模块名称
	static int iModule;	//当前正在控制音量的模块ID

	static HANDLE hThreadIncreaseVolume;	//音量缓升的线程句柄

	static HANDLE hThreadDecreaseVolume;	//音量缓降的线程句柄

	

	// 事件通知
	static HANDLE hIncreaseVolumeEvent;
	static HANDLE hDecreaseVolumeEvent;

public:
	//获得当前机器当量
	static int GetCurrentMachineVolume()
	{
		return iMachineVolume;
	}

	//获得当前音量与整体音量的比例
	/*static float GetCurrentVolumeRate()
	{
		return iMachineVolume / (float)MACHINE_MAX_VOLUME;
		
	}*/
	static int SetNaviTip(bool bTip);	//设定混音开关
	static int CalculateNaviVolume();
	static bool AddNaviVolPercent();	//增加导航音量的百比分
	static bool DecNaviVolPercent();	//减少导航音量的百比分
	static int ReadNaviVolRate(){return sysConfig.sysParam.curGPS_Vol_Rate; }

	static bool  SetNaviVolRate(int iRate);
	static bool  SetNaviVolPercent(int iPercent);

	//申请控制音量的权限
	static bool ApplayForPermission(int ModuleID, int iVolume, wstring wsName = L"");

	//申请音量控制
	static bool ApplyForVolumeControl(int iId);

	//设定特定模块音量
	//static bool SetVolumeForModule(int ModuleID, int iId);

	//加大机器音量
	static bool AddVolume();

	//减小机器音量
	static bool DecreaseVolume();

	//设定机器音量
	static bool SetMachineVolume(int iVolume);

	//增减音量
	//static bool ChangeVolume(int iVolume);

	

	//返回当前模块音量,失败时，返回-1
	static int  GetCurrentModuleVolume();

	//获得模块音量,失败时，返回-1
	static int GetCurrentModuleVolume(int);
	
	//音量范围合法 
	static bool CheckMachineVolumeValid(int iVolume);

	//音量增幅或抑制范围是否合法 
	static bool CheckAddOrSubtractVolumeValid(int iVolume);

	//设定特定模块音量增幅或抑制
	static bool SetVolumeAddOrSubForModule(int ModuleID, int iVolume, bool bIsEffect = true);

	//获得模块增幅或抑制音量,失败时，返回-1
	static int GetCurrentModuleAddOrSubVolume(int iModule);

	//缓升音量
	static void SlowlyIncreaseVolume();
	static void StartSlowlyIncreaseVolume();

	//缓降音量
	static void SlowlyDecreaseVolume();
	static void StartSlowlyDecreaseVolume();

	//取消静音，并缓升音量
	static void UnMuteAndSlowlyIncreaseVolume();

	//缓降音量，并静音
	static void SlowlyDecreaseVolumeAndMute();

	static void Init();
	

private:

	static bool bSetMute;

	//计算模块音量
	static int CalculateModuleVolume(int iVolumeAddorSubtract);

	//通过模块ID，找模块
	static VolumeModule* SeekModule(int iModuleid);

	static DWORD IncreaseVolumeThread(LPVOID lpParam);

	static DWORD DecreaseVolumeThread(LPVOID lpParam);

	static GxLock lock;

	static bool bIncreaseVolumeing;		//音量是否渐升中的标志位
	static bool bDecreaseVolumeing;		//音量是否渐降中的标志位
	

};


class VolumeEPROMAction
{
public:
	//保存机器的音量
	static void MachineVolumeSave(int iMacineVolue)
	{
		sysConfig.sysParam.curVol = iMacineVolue;
		sysConfig.WriteConfig(&sysConfig.sysParam.curVol);
	}
	
	//保存模块的增幅或抑制音量
	static void VolumeSaveAddOrSub(int iVolumeModule, int _iVolume)
	{
		int iVolume = _iVolume + 14;	//换算，因为存储不了负数
		switch(iVolumeModule)
		{
		case VolumeModuleId::AUX:
			{
				sysConfig.sysParam.curAuxVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curAuxVol);
			}
			break;
		case VolumeModuleId::DISC:
			{
				sysConfig.sysParam.curDvdVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curDvdVol);
			}
			break;
		case VolumeModuleId::DTV:
			{
				sysConfig.sysParam.curDtvVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curDtvVol);
			}
			break;
		case VolumeModuleId::IPOD:
			{
				sysConfig.sysParam.curIpodVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curIpodVol);
			}
			break;
		case VolumeModuleId::NAVI:
			{
				sysConfig.sysParam.curNaviVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curNaviVol);
			}
			break;
		case VolumeModuleId::RADIO:
			{
				sysConfig.sysParam.curRadioVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curRadioVol);
			}
			break;
		case VolumeModuleId::USB:
			{
				sysConfig.sysParam.curUsbVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curUsbVol);
			}
			break;
		case VolumeModuleId::PHONE:
			{
				sysConfig.sysParam.curPhoneVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curPhoneVol);
			}
			break;
		case VolumeModuleId::BTMUSIC:
			{
				sysConfig.sysParam.curPhoneMusicVol = iVolume;
				sysConfig.WriteConfig(&sysConfig.sysParam.curPhoneMusicVol);
			}
			break;
		}
	}
	//获得模块的增幅或抑制音量
	static int VolumeAddOrSubGet(int iVolumeModule)
	{
		int iVolume;
		switch(iVolumeModule)
		{
		case VolumeModuleId::AUX:
			{
				iVolume = sysConfig.sysParam.curAuxVol;
			}
			break;
		case VolumeModuleId::DISC:
			{
				iVolume = sysConfig.sysParam.curDvdVol;
			}
			break;
		case VolumeModuleId::DTV:
			{
				iVolume = sysConfig.sysParam.curDtvVol;
			}
			break;
		case VolumeModuleId::IPOD:
			{
				iVolume = sysConfig.sysParam.curIpodVol;
			}
			break;
		case VolumeModuleId::NAVI:
			{
				iVolume = sysConfig.sysParam.curNaviVol;
			}
			break;
		case VolumeModuleId::RADIO:
			{
				iVolume = sysConfig.sysParam.curRadioVol;
			}
			break;
		case VolumeModuleId::USB:
			{
				iVolume = sysConfig.sysParam.curUsbVol;
			}
			break;
		case VolumeModuleId::PHONE:
			{
				iVolume = sysConfig.sysParam.curPhoneVol;
			}
			break;
		case VolumeModuleId::BTMUSIC:
			{
				iVolume = sysConfig.sysParam.curPhoneMusicVol;
			}
			break;
		}
		//检查声音合理范围
		if(!VolumeControl::CheckMachineVolumeValid(iVolume))
		{
			iVolume = 0;
		}
		iVolume = iVolume - 14;	//换算，因为存储不了负数
		return iVolume;
	}
};