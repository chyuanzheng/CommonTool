#include "StdAfx.h"
#include "SetupNaviManager.h"
#include "StrDef.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "Audio/Audio.h"
#include "LangStringManager.h"
#include "StrHelp.h"
#include "VolumeControl.h"
const string cs_navi_int = "navi_int_set";
const string cs_navi_mix = "navi_mix_adjust_set";
const string cs_navi_level = "navi_mix_level_set";
const string cs_navi_gain = "navi_mix_gain_set";



SetupNaviManager *SetupNaviManager::m_pInstance = NULL;
SetupNaviManager::SetupNaviManager()
{
	//这里应该读取flash 得到m_color的值
	//m_navi_mix = sysConfig.sysParam.curGPSVol;

	//if (m_navi_mix>15)
	//{
	//	m_navi_mix = 5;
	//}
	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

	if (sysConfig.sysParam.naviAtten>2)
	{
		sysConfig.sysParam.naviAtten = 0;
		sysConfig.WriteConfig(&sysConfig.sysParam.naviAtten);
	}

	VolumeControl::SetNaviTip(!sysConfig.sysParam.naviTips);

	if (sysConfig.sysParam.naviGain>15)
	{
		sysConfig.sysParam.naviGain = 10;
		sysConfig.WriteConfig(&sysConfig.sysParam.naviGain);
	}
	//VolumeControl::SetNaviVolPercent(sysConfig.sysParam.naviGain*10);
	VolumeControl::SetNaviVolRate(sysConfig.sysParam.naviGain);

}

SetupNaviManager::~SetupNaviManager()
{

}


//恢复出厂设置
LRESULT SetupNaviManager::RestoreDefault(DWORD param1, DWORD param2)
{

	sysConfig.sysParam.naviTips = 1;//导航混音默认是 关
	sysConfig.WriteConfig(&sysConfig.sysParam.naviTips);
	VolumeControl::SetNaviTip(!sysConfig.sysParam.naviTips);


	//m_navi_mix = 5;
	//sysConfig.sysParam.curGPSVol = m_navi_mix;
	//sysConfig.WriteConfig(&sysConfig.sysParam.curGPSVol);
	//Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);  // add by yf

	sysConfig.sysParam.naviAtten = 0;
	sysConfig.WriteConfig(&sysConfig.sysParam.naviAtten);

	sysConfig.sysParam.naviGain = 10;
	sysConfig.WriteConfig(&sysConfig.sysParam.naviGain);
	//VolumeControl::SetNaviVolPercent(10*10); 
	VolumeControl::SetNaviVolRate(10);

	return 0;
}
SetupNaviManager* SetupNaviManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupNaviManager;
	}
	return m_pInstance;
}


bool SetupNaviManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	
	if (sline_name == cs_navi_int)
	{
		
		min_cursor = 0;
		max_cursor = 1;
		AfxPostMessage(CTR_LINE_01_SWITCH,WPARAM(!sysConfig.sysParam.naviTips),0);
		return true;
	}
	//else if (sline_name == cs_navi_mix)
	//{
	//	min_cursor = 0;
	//	max_cursor = 15;
	//	return true;
	//}
	else if (sline_name == cs_navi_level)
	{
		min_cursor = 0;
		max_cursor = 2;
		return true;
	}
	else if (sline_name == cs_navi_gain || sline_name == cs_navi_mix)
	{
		min_cursor = 0;
		max_cursor = 15;
		return true;
	}
	return false;//没有最大 最小游标
}

bool SetupNaviManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{
	if (sline_name == cs_navi_int)
	{
		n_cursor = (bool)sysConfig.sysParam.naviTips;
		if (!sysConfig.sysParam.naviTips )//0是ON，1是OFF
		{
			sline_data=CHDLL_STR::C_ON;;
			
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}

	}
	//else if (sline_name == cs_navi_mix)
	//{
	//	n_cursor = (int)m_navi_mix;
	//	ASSERT(m_navi_mix<=15);
	//	char text_v[8]; 
	//	sprintf(text_v,"%d",m_navi_mix);
	//	sline_data = text_v;

	//}
	else if (sline_name == cs_navi_level)
	{
		n_cursor = sysConfig.sysParam.naviAtten;

		if (0==n_cursor)
		{
			//注意:用"_31_line"为结尾的ID，表示这是一个需要语言翻译的选项，不是一个直接的字符串
			sline_data = "Low_31_line";
			//sdata = *(LangStringManager::GetInstance()->getString("Low_31"));
		}
		else if (1==n_cursor)
		{
			sline_data = "Medium_31_line";//注意:用"_31_line"为结尾的ID，表示这是一个需要语言翻译的选项，不是一个直接的字符串
			//sdata = *(LangStringManager::GetInstance()->getString("Medium_31"));
		}
		else if (2==n_cursor)
		{
			sline_data = "High_31_line";//注意:用"_31_line"为结尾的ID，表示这是一个需要语言翻译的选项，不是一个直接的字符串
			//sdata = *(LangStringManager::GetInstance()->getString("High_31"));
		}
		else
		{
			ASSERT(0);
		}

	}
	else if (sline_name == cs_navi_gain || sline_name == cs_navi_mix)
	{
		n_cursor = sysConfig.sysParam.naviGain;
		sline_data = StrHelp::FormatToString("%d",n_cursor);
	}
	AfxInvalidateRect(NULL);
	return true;
}



bool SetupNaviManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == cs_navi_int)
	{
		sysConfig.sysParam.naviTips = n_cursor;
		sysConfig.WriteConfig(&sysConfig.sysParam.naviTips);
		ReadSetup(sline_name,n_cursor,sline_data);
		VolumeControl::SetNaviTip(!sysConfig.sysParam.naviTips);
		AfxPostMessage(CTR_LINE_01_SWITCH,WPARAM(!sysConfig.sysParam.naviTips),0);
		AfxPostMessage(CTR_SETUP_READ_LIST,0,0);

	}
	//else if (sline_name == cs_navi_mix)
	//{
	//	m_navi_mix = n_cursor;
	//	sysConfig.sysParam.curGPSVol = m_navi_mix;
	//	sysConfig.WriteConfig(&sysConfig.sysParam.curGPSVol);
	//	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	//	ReadSetup(sline_name,n_cursor,sline_data);
	//}
	else if (sline_name == cs_navi_level)
	{
		sysConfig.sysParam.naviAtten = n_cursor;
		sysConfig.WriteConfig(&sysConfig.sysParam.naviAtten);
		ReadSetup(sline_name,n_cursor,sline_data);
		GXNotify::SendNotify("set_navi_vol", sysConfig.sysParam.curGPSVol, 0);
	}
	else if (sline_name == cs_navi_gain || sline_name == cs_navi_mix)
	{
		sysConfig.sysParam.naviGain = n_cursor;
		sysConfig.WriteConfig(&sysConfig.sysParam.naviGain);
		//VolumeControl::SetNaviVolPercent(n_cursor*10); 
		VolumeControl::SetNaviVolRate(n_cursor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}
	else
	{
		ASSERT(0);
	}	
	return true;
}
