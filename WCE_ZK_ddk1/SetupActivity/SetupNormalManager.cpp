#include "StdAfx.h"
#include "SetupNormalManager.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "StrDef.h"
#include "StrHelp.h"
#include "AVSet.h"

const string cs_led  = "led_set";
const string cs_beep  = "beep_set";
const string cs_defeat  = "defeat_set";
const string cs_match_set  = "btn_match_set";



#define  MAX_BEEP_VOLUE    7
#define   MAX_Ohm_Match    3
SetupNormalManager *SetupNormalManager::m_pInstance = NULL;
SetupNormalManager::SetupNormalManager():m_beepValue(sysConfig.sysParam.curBeep)
{
	//这里应该读取flash 得到m_color的值
	m_color = sysConfig.sysParam.curScreenColor;

	if (m_beepValue<0||m_beepValue>MAX_BEEP_VOLUE)
	{
		m_beepValue = 0;
		sysConfig.WriteConfig(&m_beepValue);
	}
	if (sysConfig.sysParam.curDefeat<0||sysConfig.sysParam.curDefeat>1)
	{
		sysConfig.sysParam.curDefeat = 0;
		sysConfig.WriteConfig(&sysConfig.sysParam.curDefeat);
	}


	string temp;
	WriteColor(temp);
	AfxPostMessage(CTR_SET_BEEP,(WPARAM)m_beepValue,0);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

	if (sysConfig.sysParam.curBtnMatchR >MAX_Ohm_Match)
	{
		sysConfig.sysParam.curBtnMatchR = 0;
		sysConfig.WriteConfig(&sysConfig.sysParam.curBtnMatchR);
	}

	AVSET::SetResType(sysConfig.sysParam.curBtnMatchR);
}

SetupNormalManager::~SetupNormalManager()
{

}

//恢复出厂设置
LRESULT SetupNormalManager::RestoreDefault(DWORD param1, DWORD param2)
{

	m_color = Blue;//默认蓝色
	sysConfig.sysParam.curScreenColor = m_color;
	sysConfig.WriteConfig(&sysConfig.sysParam.curScreenColor);
	string temp;
	WriteColor(temp);

	m_beepValue = MAX_BEEP_VOLUE/2;
	sysConfig.WriteConfig(&m_beepValue);
	AfxPostMessage(CTR_SET_BEEP,(WPARAM)m_beepValue,0);

	sysConfig.sysParam.curDefeat = 0;//默认Off
	sysConfig.WriteConfig(&sysConfig.sysParam.curDefeat);


	sysConfig.sysParam.curBtnMatchR=0;//默认值是10K
	sysConfig.WriteConfig(&sysConfig.sysParam.curBtnMatchR);
	AVSET::SetResType(sysConfig.sysParam.curBtnMatchR);

	AfxPostMessage(CTR_SETUP_READ_LIST,0,0);
	return 0;
}
SetupNormalManager* SetupNormalManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupNormalManager;
	}
	return m_pInstance;
}


bool SetupNormalManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	
	if (sline_name == cs_led)
	{
		
		if (m_color<Blue||m_color>Mono)
		{
			m_color=Blue;
		}
		min_cursor = (int)Blue;
		max_cursor = (int)Mono;
		return true;
	}
	else if (sline_name == cs_beep)
	{
		min_cursor = 0;
		max_cursor = MAX_BEEP_VOLUE;
		return true;
	}
	else if (sline_name == cs_defeat)
	{
		min_cursor = 0;
		max_cursor = 1;
		AfxPostMessage(CTR_DEFEAT_ENABLE,WPARAM(sysConfig.sysParam.curDefeat),0);
		return true;
	}
	else if (sline_name == cs_match_set)
	{
		min_cursor = 0;
		max_cursor = MAX_Ohm_Match;
		return true;
	}

	ASSERT(0);
	return true;//没有最大 最小游标
}

bool SetupNormalManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{
	if (sline_name == cs_led)
	{
		n_cursor = (int)m_color;
		WriteColor(sline_data);

	}
	else if (sline_name == cs_beep )
	{
		n_cursor = m_beepValue;
		sline_data=StrHelp::FormatToString("%d",m_beepValue);
	
	}
	else if (sline_name == cs_defeat )
	{
		n_cursor = (int)sysConfig.sysParam.curDefeat;
		if (bool(n_cursor))
		{
			sline_data= CHDLL_STR::C_ON;;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
	}
	else if (sline_name == cs_match_set)
	{
		n_cursor = sysConfig.sysParam.curBtnMatchR;
		if (0==n_cursor)
		{
			sline_data = "10K";
		}
		else if (1==n_cursor)
		{
			sline_data = "2.2K";
		}
		else if (2==n_cursor)
		{
			sline_data = "470R";
		}
		else if (3==n_cursor)
		{
			sline_data = "33R";
		}
		return true;
	}


	AfxInvalidateRect(NULL);
	return true;
}



bool SetupNormalManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == cs_led)
	{
		m_color = n_cursor;
		sysConfig.sysParam.curScreenColor = m_color;
		sysConfig.WriteConfig(&sysConfig.sysParam.curScreenColor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}
	else if (sline_name == cs_beep)
	{
		m_beepValue = n_cursor;
		sline_data=StrHelp::FormatToString("%d",m_beepValue);

		sysConfig.WriteConfig(&m_beepValue);
		AfxPostMessage(CTR_SET_BEEP,(WPARAM)m_beepValue,0);
	}
	else if (sline_name == cs_defeat)
	{
		sysConfig.sysParam.curDefeat = n_cursor;
		if (bool(n_cursor))
		{
			sline_data=CHDLL_STR::C_ON;;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
		sysConfig.WriteConfig(&sysConfig.sysParam.curDefeat);
		AfxPostMessage(CTR_DEFEAT_ENABLE,WPARAM(sysConfig.sysParam.curDefeat),0);
		GXNotify::SendNotifyAsync(AfxGetHWND(),"eq_default_set", WPARAM(sysConfig.sysParam.curDefeat), 0);
	}
	else if (sline_name == cs_match_set)
	{
		sysConfig.sysParam.curBtnMatchR = n_cursor ;
		sysConfig.WriteConfig(&sysConfig.sysParam.curBtnMatchR);
		ASSERT(0<=n_cursor && n_cursor <=MAX_Ohm_Match);
		AVSET::SetResType(n_cursor);
		ReadSetup(sline_name,n_cursor,sline_data);
	}
	return true;
}

void SetupNormalManager::WriteColor( string & sline_data )
{
	switch( (S_COLOR)m_color )
	{
	case Blue:
		sline_data = "Blue";
		Activity::SetActivityBackColor(0xFF0000FF);
		break;
	case Red:
		sline_data = "Red";
		Activity::SetActivityBackColor(0xFFFF0000);
		break;
	case  Green:
		sline_data = "Green";
		Activity::SetActivityBackColor(0xFF00FF00);
		break;
	case Amber:
		sline_data = "Amber";
		Activity::SetActivityBackColor(0xFFFF9933);
		break;
	case Mono:
		sline_data = "Mono";
		Activity::SetActivityBackColor(0xFF808080);
		break;
	default:
		ASSERT(0);
		break;
	}	
}

