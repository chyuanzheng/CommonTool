#include "StdAfx.h"
#include "SetupApplyManager.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "VolumeControl.h"
#include "Audio/Audio.h"
#include "StrDef.h"


const string auto_answer_set  =			"auto_answer_set";
const string cs_dtv  = "DTV_set";
const string cs_bluetooth_module  = "bt_module_set";
const string cs_languages_set  = "languages_set";
const string cs_navi_option_set  = "navi_option_set";
const string cs_navi_mix_set  = "navi_mix_set";
const string cs_bsf_option_set  = "bsf_option_set";



#define   Phone_DIV    5
SetupApplyManager *SetupApplyManager::m_pInstance = NULL;
SetupApplyManager::SetupApplyManager()
{

	m_auto_answer = sysConfig.sysParam.curPhoneAutoAnswer/Phone_DIV;
	m_phone_speaker = sysConfig.sysParam.curPhoneSpeaker;


	if (m_auto_answer>S_15)
	{
		m_auto_answer = OFF;
		sysConfig.sysParam.curPhoneAutoAnswer = OFF;
	}
	sysConfig.WriteConfig(&sysConfig.sysParam.curPhoneAutoAnswer);

	//if (m_phone_speaker>Front_LR)
	//{
	//	m_phone_speaker = ALL;
	//	sysConfig.sysParam.curPhoneSpeaker = ALL;
	//}
	//sysConfig.WriteConfig(&sysConfig.sysParam.curPhoneSpeaker);

	if (sysConfig.sysParam.curDtvEnable<0||sysConfig.sysParam.curDtvEnable>1)
	{
		sysConfig.sysParam.curDtvEnable = 0;
		sysConfig.WriteConfig(&sysConfig.sysParam.curDtvEnable);
	}
	Activity::EnableActivity("DTVActivity",(bool)sysConfig.sysParam.curDtvEnable);


	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

	m_opt_language = VersionXml::GetInstance()->GetLanguage();
	m_opt_Navi_SoftWare = VersionXml::GetInstance()->GetNaviSoftCode();
	m_opt_Navi_MixSound = VersionXml::GetInstance()->GetNaviMix();;
	m_bt_Module = VersionXml::GetInstance()->GetBtModule();
	m_bsf_Module  = VersionXml::GetInstance()->GetBSFModule();

}

SetupApplyManager::~SetupApplyManager()
{

}

//恢复出厂设置
LRESULT SetupApplyManager::RestoreDefault(DWORD param1, DWORD param2)
{
	m_auto_answer = OFF;
	sysConfig.sysParam.curPhoneAutoAnswer = m_auto_answer*Phone_DIV;
	sysConfig.WriteConfig(&sysConfig.sysParam.curPhoneAutoAnswer);


	//m_phone_speaker = ALL;
	//sysConfig.sysParam.curPhoneSpeaker = (BYTE)m_phone_speaker;
	//sysConfig.WriteConfig(&sysConfig.sysParam.curPhoneSpeaker);

	sysConfig.sysParam.curDtvEnable = 1;
	sysConfig.WriteConfig(&sysConfig.sysParam.curDtvEnable);
	Activity::EnableActivity("DTVActivity",(bool)sysConfig.sysParam.curDtvEnable);


	return 0;
}

SetupApplyManager* SetupApplyManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupApplyManager;
	}
	return m_pInstance;
}


bool SetupApplyManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	if(sline_name == auto_answer_set)
	{
		min_cursor = OFF;
		max_cursor = S_15;
	}
	else if (sline_name == cs_dtv)
	{
		min_cursor = 0;
		max_cursor = 1;
		return true;
	}
	else if (sline_name == cs_bluetooth_module)
	{
		min_cursor = 0;
		max_cursor = 1;
	}
	else if (sline_name == cs_languages_set)
	{
		min_cursor = 0;
		max_cursor = 2;
	}
	else if (sline_name == cs_navi_option_set)
	{
		min_cursor = 0;
		max_cursor = 2;
	}
	else if (sline_name == cs_navi_mix_set)
	{
		min_cursor = 0;
		max_cursor = 1;
	}
	else if (sline_name == cs_bsf_option_set)
	{
		min_cursor = 0;
		max_cursor = 1;
	}
	else
	{
		ASSERT(0);
	}
	return true;//没有最大 最小游标
}

bool SetupApplyManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{

	if (sline_name == auto_answer_set)
	{
		n_cursor = (int)m_auto_answer;
		if (m_auto_answer==OFF)
		{
			sline_data= CHDLL_STR::C_OFF;
		}
		else if (m_auto_answer==S_5)
		{
			sline_data="5 S";
		}
		else if (m_auto_answer==S_10)
		{
			sline_data="10 S";
		}
		else if (m_auto_answer==S_15)
		{
			sline_data="15 S";
		}
		else
		{
			ASSERT(0);
		}
	}
	else if (sline_name == cs_dtv )
	{
		n_cursor = (int)sysConfig.sysParam.curDtvEnable;
		if (bool(n_cursor))
		{
			sline_data= CHDLL_STR::C_ON;;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
	}
	else if (sline_name == cs_bluetooth_module)
	{
		if (m_bt_Module == VersionXml::BT_Module_Added )
		{
			n_cursor = 0;
			sline_data = "Added";
		}
		else if(m_bt_Module == VersionXml::BT_Module_Removed )
		{
			n_cursor = 1;
			sline_data = "Removed";
		}
		else
		{
			ASSERT(0);
		}
	}
	else if (sline_name == cs_languages_set)
	{
		if (m_opt_language == VersionXml::LAN_ALL)
		{
			n_cursor = 0;
			sline_data = "QuanBu";
		}
		else if (m_opt_language == VersionXml::LAN_Traditional)
		{
			n_cursor = 1;
			sline_data = "FanTi";
		}
		else if(m_opt_language == VersionXml::LAN_Simplified)
		{
			n_cursor = 2;
			sline_data = "JianTi";
		}
		else
		{
			ASSERT(0);
		}
	}
	else if (sline_name == cs_navi_option_set)
	{
		if (m_opt_Navi_SoftWare == VersionXml::Navi_NaviKing)
		{
			n_cursor = 0;
			sline_data = "NaviKing";
		}
		else if (m_opt_Navi_SoftWare == VersionXml::Navi_KaiLiDe)
		{
			n_cursor = 1;
			sline_data = "KaiLiDe";
		}
		else if (m_opt_Navi_SoftWare == VersionXml::Navi_GaoDe)
		{
			n_cursor = 2;
			sline_data = "GaoDe";
		}
		else
		{
			ASSERT(0);
		}
	}
	else if (sline_name == cs_navi_mix_set)
	{
		if (m_opt_Navi_MixSound == VersionXml::Navi_Mix_Added )
		{
			n_cursor = 0;
			sline_data = "Added";
		}
		else if(m_opt_Navi_MixSound == VersionXml::Navi_Mix_Removed )
		{
			n_cursor = 1;
			sline_data = "Removed";
		}
		else
		{
			ASSERT(0);
		}
	}
	else if (sline_name == cs_bsf_option_set)
	{
		if(m_bsf_Module == VersionXml::Navi_BSF_Added )
		{
			n_cursor = 0;
			sline_data = "Added";
		}
		else if(m_bsf_Module == VersionXml::Navi_BSF_Removed )
		{
			n_cursor = 1;
			sline_data = "Removed";
		}
		else
		{
			ASSERT(0);
		}
	}
	AfxInvalidateRect(NULL);
	return true;
}



bool SetupApplyManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == auto_answer_set)
	{
		m_auto_answer = n_cursor;
		ReadSetup(sline_name,n_cursor,sline_data);
		sysConfig.sysParam.curPhoneAutoAnswer = m_auto_answer*Phone_DIV;
		sysConfig.WriteConfig(&sysConfig.sysParam.curPhoneAutoAnswer);

	}
	else if (sline_name == cs_dtv)
	{
		sysConfig.sysParam.curDtvEnable = n_cursor;
		if (bool(n_cursor))
		{
			sline_data=CHDLL_STR::C_ON;;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
		sysConfig.WriteConfig(&sysConfig.sysParam.curDtvEnable);
		Activity::EnableActivity("DTVActivity",(bool)sysConfig.sysParam.curDtvEnable);
	}
	else if (sline_name == cs_bluetooth_module)
	{
		m_bt_Module = (VersionXml::Option_BT_Module)n_cursor;
		VersionXml::GetInstance()->SetBtModule(n_cursor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}
	else if (sline_name == cs_languages_set)
	{
		m_opt_language = (VersionXml::Option_Language)n_cursor;
		VersionXml::GetInstance()->SetLanguage(n_cursor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}
	else if (sline_name == cs_navi_option_set)
	{
		m_opt_Navi_SoftWare = (VersionXml::Option_NaviSoftWare)n_cursor;
		VersionXml::GetInstance()->SetSoftWare(n_cursor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}
	else if (sline_name == cs_navi_mix_set)
	{
		m_opt_Navi_MixSound = (VersionXml::Option_NaviMixSound)n_cursor;
		VersionXml::GetInstance()->SetNaviMix(n_cursor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}
	else if (sline_name == cs_bsf_option_set)
	{

		m_bsf_Module = (VersionXml::Option_BSF_Module)n_cursor;
		VersionXml::GetInstance()->SetBSFModule(n_cursor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}

	else
	{
		ASSERT(0);
	}

	return true;
}


