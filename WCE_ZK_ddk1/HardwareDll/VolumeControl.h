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

	//���ģ��ID�Ƿ�Ϸ�
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
	int iId;	//ģ��ID
	////������
	//int iTotalVolume;
	//��������������
	int iVolumeAddorSubtract;
	//ʵ��������С��ʵ��������С = �������� + ��������������
	int iVolume;
	wstring wsName;	//ģ����

};

class CE_HardwareDll_API VolumeControl
{
public:
	static const int  VOLUME_ADD = 14;	//��������
	static const int VOLUME_SUB = -14;	//��������

private:
	static std::map<int,VolumeModule*> mapVolumeModule;
	static int iMachineVolume;	//��ǰ��������
	static int iNaviVolPercent;		//��õ�ǰ���������ٷֱ�
	static wstring wsModule;	//��ǰ���ڿ���������ģ������
	static int iModule;	//��ǰ���ڿ���������ģ��ID

	static HANDLE hThreadIncreaseVolume;	//�����������߳̾��

	static HANDLE hThreadDecreaseVolume;	//�����������߳̾��

	

	// �¼�֪ͨ
	static HANDLE hIncreaseVolumeEvent;
	static HANDLE hDecreaseVolumeEvent;

public:
	//��õ�ǰ��������
	static int GetCurrentMachineVolume()
	{
		return iMachineVolume;
	}

	//��õ�ǰ���������������ı���
	/*static float GetCurrentVolumeRate()
	{
		return iMachineVolume / (float)MACHINE_MAX_VOLUME;
		
	}*/
	static int SetNaviTip(bool bTip);	//�趨��������
	static int CalculateNaviVolume();
	static bool AddNaviVolPercent();	//���ӵ��������İٱȷ�
	static bool DecNaviVolPercent();	//���ٵ��������İٱȷ�
	static int ReadNaviVolRate(){return sysConfig.sysParam.curGPS_Vol_Rate; }

	static bool  SetNaviVolRate(int iRate);
	static bool  SetNaviVolPercent(int iPercent);

	//�������������Ȩ��
	static bool ApplayForPermission(int ModuleID, int iVolume, wstring wsName = L"");

	//������������
	static bool ApplyForVolumeControl(int iId);

	//�趨�ض�ģ������
	//static bool SetVolumeForModule(int ModuleID, int iId);

	//�Ӵ��������
	static bool AddVolume();

	//��С��������
	static bool DecreaseVolume();

	//�趨��������
	static bool SetMachineVolume(int iVolume);

	//��������
	//static bool ChangeVolume(int iVolume);

	

	//���ص�ǰģ������,ʧ��ʱ������-1
	static int  GetCurrentModuleVolume();

	//���ģ������,ʧ��ʱ������-1
	static int GetCurrentModuleVolume(int);
	
	//������Χ�Ϸ� 
	static bool CheckMachineVolumeValid(int iVolume);

	//�������������Ʒ�Χ�Ƿ�Ϸ� 
	static bool CheckAddOrSubtractVolumeValid(int iVolume);

	//�趨�ض�ģ����������������
	static bool SetVolumeAddOrSubForModule(int ModuleID, int iVolume, bool bIsEffect = true);

	//���ģ����������������,ʧ��ʱ������-1
	static int GetCurrentModuleAddOrSubVolume(int iModule);

	//��������
	static void SlowlyIncreaseVolume();
	static void StartSlowlyIncreaseVolume();

	//��������
	static void SlowlyDecreaseVolume();
	static void StartSlowlyDecreaseVolume();

	//ȡ������������������
	static void UnMuteAndSlowlyIncreaseVolume();

	//����������������
	static void SlowlyDecreaseVolumeAndMute();

	static void Init();
	

private:

	static bool bSetMute;

	//����ģ������
	static int CalculateModuleVolume(int iVolumeAddorSubtract);

	//ͨ��ģ��ID����ģ��
	static VolumeModule* SeekModule(int iModuleid);

	static DWORD IncreaseVolumeThread(LPVOID lpParam);

	static DWORD DecreaseVolumeThread(LPVOID lpParam);

	static GxLock lock;

	static bool bIncreaseVolumeing;		//�����Ƿ����еı�־λ
	static bool bDecreaseVolumeing;		//�����Ƿ񽥽��еı�־λ
	

};


class VolumeEPROMAction
{
public:
	//�������������
	static void MachineVolumeSave(int iMacineVolue)
	{
		sysConfig.sysParam.curVol = iMacineVolue;
		sysConfig.WriteConfig(&sysConfig.sysParam.curVol);
	}
	
	//����ģ�����������������
	static void VolumeSaveAddOrSub(int iVolumeModule, int _iVolume)
	{
		int iVolume = _iVolume + 14;	//���㣬��Ϊ�洢���˸���
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
	//���ģ�����������������
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
		//�����������Χ
		if(!VolumeControl::CheckMachineVolumeValid(iVolume))
		{
			iVolume = 0;
		}
		iVolume = iVolume - 14;	//���㣬��Ϊ�洢���˸���
		return iVolume;
	}
};