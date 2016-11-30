#include "StdAfx.h"
#include "SetupDislayManager.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "AVSet.h"

const string s_brightness  = "s_brightness";
const string s_contrast  = "s_contrast";
const string v_brightness  = "v_brightness";
const string v_contrast  = "v_contrast";
const string v_color  = "v_color";




SetupDislayManager *SetupDislayManager::m_pInstance = NULL;
SetupDislayManager::SetupDislayManager():m_nScreenBrightness(sysConfig.sysParam.curScreenBrightness),
m_nScreenContrast (sysConfig.sysParam.curScreenContrast),
m_nVedioBrightness (sysConfig.sysParam.curVedioBrightness),
m_nVedioContrast  (sysConfig.sysParam.curVedioContrast),
m_nVedioColor  (sysConfig.sysParam.curVedioColor)
{

	SetDataInArea(m_nScreenBrightness,-9,9);
	SetDataInArea(m_nScreenContrast,-9,9);
	SetDataInArea(m_nVedioBrightness,-9,9);
	SetDataInArea(m_nVedioContrast,-9,9);
	SetDataInArea(m_nVedioColor,-9,9);



	AVSET::LCDSetBright(m_nScreenBrightness);
	AVSET::LCDSetContrast(m_nScreenContrast);

	AVSET::VideoSetBrght(m_nVedioBrightness);
	AVSET::VideoSetContrast(m_nVedioContrast);
	AVSET::VideoSetColor(m_nVedioColor);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);


	//这里要写入硬件
}

SetupDislayManager::~SetupDislayManager()
{

}


//恢复出厂设置
LRESULT SetupDislayManager::RestoreDefault(DWORD param1, DWORD param2)
{

		m_nScreenBrightness = 0 ;
		AVSET::LCDSetBright(m_nScreenBrightness);
		sysConfig.WriteConfig((BYTE *)&m_nScreenBrightness);

		m_nScreenContrast = 0 ;
		AVSET::LCDSetContrast(m_nScreenContrast);
		sysConfig.WriteConfig((BYTE *)&m_nScreenContrast);

		m_nVedioBrightness = 0;
		AVSET::VideoSetBrght(m_nVedioBrightness);
		sysConfig.WriteConfig((BYTE *)&m_nVedioBrightness);

		m_nVedioContrast = 0;
		AVSET::VideoSetContrast(m_nVedioContrast);
		sysConfig.WriteConfig((BYTE *)&m_nVedioContrast);

		m_nVedioColor = 0;
		AVSET::VideoSetColor(m_nVedioColor);
		sysConfig.WriteConfig((BYTE *)&m_nVedioColor);


	return 0;
}


SetupDislayManager* SetupDislayManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupDislayManager;
	}
	return m_pInstance;
}


bool SetupDislayManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	
	min_cursor = -9;
	max_cursor = 9;
	return true;//没有最大 最小游标
}

bool SetupDislayManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{
	if (sline_name == s_brightness)
	{
		n_cursor =  m_nScreenBrightness;
	}
	else if (sline_name == s_contrast)
	{
		n_cursor =  m_nScreenContrast;
	}
	else if (sline_name == v_brightness)
	{
		n_cursor =  m_nVedioBrightness;
	}
	else if (sline_name == v_contrast)
	{
		n_cursor =  m_nVedioContrast;
	}
	else if (sline_name == v_color)
	{
		n_cursor =  m_nVedioColor;
	}

	char text_v[16]; 
	sprintf(text_v,"%d",n_cursor);
	sline_data = text_v;

	AfxInvalidateRect(NULL);
	return true;
}



bool SetupDislayManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == s_brightness)
	{
		m_nScreenBrightness = n_cursor ;
		AVSET::LCDSetBright(m_nScreenBrightness);
		sysConfig.WriteConfig((BYTE *)&m_nScreenBrightness);
	}
	else if (sline_name == s_contrast)
	{
		m_nScreenContrast = n_cursor ;
		AVSET::LCDSetContrast(m_nScreenContrast);
		sysConfig.WriteConfig((BYTE *)&m_nScreenContrast);
	}
	else if (sline_name == v_brightness)
	{
		m_nVedioBrightness = n_cursor;
		AVSET::VideoSetBrght(m_nVedioBrightness);
		sysConfig.WriteConfig((BYTE *)&m_nVedioBrightness);
	}
	else if (sline_name == v_contrast)
	{
		m_nVedioContrast = n_cursor;
		AVSET::VideoSetContrast(m_nVedioContrast);
		sysConfig.WriteConfig((BYTE *)&m_nVedioContrast);
	}
	else if (sline_name == v_color)
	{
		 m_nVedioColor = n_cursor;
		 AVSET::VideoSetColor(m_nVedioColor);
		 sysConfig.WriteConfig((BYTE *)&m_nVedioColor);
	}

	char text_v[16]; 
	sprintf(text_v,"%d",n_cursor);
	sline_data = text_v;

	return true;
}

void SetupDislayManager::SetDataInArea( char &d, int min, int max )
{
	if (d<min || d >max)
	{
		d = (min + max)/2;
	}
}