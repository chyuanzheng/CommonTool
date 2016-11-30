#include "StdAfx.h"
#include "SetupVolumeManager.h"
#include "VolumeControl.h"
#include "Audio/Audio.h"

const string cs_aux  = "AUX";
const string cs_disc  = "Disc";
const string cs_dtv  = "DTV";
const string cs_ipod  = "Ipod";
const string cs_navi  = "Navi";
const string cs_radio = "Radio";
const string cs_usb = "USB";
const string cs_bt_music = "BTMusic";
const string cs_phone = "Phone";


SetupVolumeManager *SetupVolumeManager::m_pInstance = NULL;
SetupVolumeManager::SetupVolumeManager()
{
	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);
}

SetupVolumeManager::~SetupVolumeManager()
{
}


SetupVolumeManager* SetupVolumeManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupVolumeManager;
	}
	return m_pInstance;
}

//恢复出厂设置
LRESULT SetupVolumeManager::RestoreDefault(DWORD param1, DWORD param2)
{
	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::AUX,0);

	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::DISC,0);

	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::DTV,0);

	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::IPOD,0);

	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::NAVI,0);


	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::RADIO,0);

	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::USB,0);

	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::BTMUSIC,0);

	VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::PHONE,0);

	return 0;
}

bool SetupVolumeManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{

	max_cursor = VolumeControl::VOLUME_ADD;
	min_cursor = VolumeControl::VOLUME_SUB;
	return true;//没有最大 最小游标
}

bool SetupVolumeManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{
	if (sline_name == cs_aux)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::AUX);
	}
	else if (sline_name == cs_disc)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::DISC);
	}
	else if (sline_name == cs_dtv)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::DTV);
	}
	else if (sline_name == cs_ipod)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::IPOD);
	}
	else if (sline_name == cs_navi)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::NAVI);
	}
	else if (sline_name == cs_radio)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::RADIO);
	}
	else if (sline_name == cs_usb)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::USB);
	}
	else if (sline_name == cs_bt_music)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::BTMUSIC);
	}
	else if (sline_name == cs_phone)
	{
		n_cursor = VolumeControl::GetCurrentModuleAddOrSubVolume(VolumeModuleId::PHONE);
	}
	else
	{
		ASSERT(0);
	}

	if(n_cursor< VolumeControl::VOLUME_SUB || n_cursor> VolumeControl::VOLUME_ADD)
	{
		return false;
	}
	int nCur = n_cursor;
	char text_v[8]; 
	sprintf(text_v,"%2d",nCur);
	sline_data = text_v;

	return true;
}



bool SetupVolumeManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == cs_aux)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::AUX,n_cursor);
	}
	else if (sline_name == cs_disc)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::DISC,n_cursor);
	}
	else if (sline_name == cs_dtv)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::DTV,n_cursor);
	}
	else if (sline_name == cs_ipod)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::IPOD,n_cursor);
	}
	else if (sline_name == cs_navi)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::NAVI,n_cursor);
	}
	else if (sline_name == cs_radio)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::RADIO,n_cursor);
	}
	else if (sline_name == cs_usb)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::USB,n_cursor);
	}
	else if (sline_name == cs_bt_music)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::BTMUSIC,n_cursor);
	}
	else if (sline_name == cs_phone)
	{
		ret = VolumeControl::SetVolumeAddOrSubForModule(VolumeModuleId::PHONE,n_cursor);
	}
	else
	{
		ASSERT(0);
	}

	if (!ret)
	{
		n_cursor = 0;
	}
	if(n_cursor< VolumeControl::VOLUME_SUB || n_cursor> VolumeControl::VOLUME_ADD)
	{
		return false;
	}
	int nCur = n_cursor;
	char text_v[8]; 
	sprintf(text_v,"%2d",nCur);
	sline_data = text_v;

	//if ( (bool)sysConfig.sysParam.curbMute)
	//{
	//	AfxPostMessage(CTR_CLOSE_MUTE,0,0);
	//}
	return true;
}


