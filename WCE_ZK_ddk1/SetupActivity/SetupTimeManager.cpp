#include "StdAfx.h"
#include "SetupTimeManager.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "StrDef.h"

const string cs_AutoAdjustSwith = "AutoAdjustSwith";
const string cs_year = "year";
const string cs_month = "month";
const string cs_date  = "date";
const string cs_clock  = "clock";
const string cs_minute  = "minute";
const string cs_timemode  = "time_mode";
const string cs_calender  = "calender_type_set";

#define  GPS_CALIENABLE  L"E_GPSCALIENABLE"
#define  GPS_READY   L"E_GPSREADY"

SetupTimeManager *SetupTimeManager::m_pInstance = NULL;
SetupTimeManager::SetupTimeManager()
{

	if (sysConfig.sysParam.curCalenderDayType<0||sysConfig.sysParam.curCalenderDayType>1)
	{
		sysConfig.sysParam.curCalenderDayType = 0;
		sysConfig.WriteConfig(&sysConfig.sysParam.curCalenderDayType);
	}
	if (sysConfig.sysParam.curTime24HMode<0||sysConfig.sysParam.curTime24HMode>1)
	{
		sysConfig.sysParam.curTime24HMode = 0;
		sysConfig.WriteConfig(&sysConfig.sysParam.curTime24HMode);
	}

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

	m_pAdjustTitle = NULL;//校正text

	m_hGpsCaliEnable	=  NULL;//OpenEvent(EVENT_ALL_ACCESS,FALSE,GPS_CALIENABLE);
	m_hGpsCaliReady = NULL;//OpenEvent(EVENT_ALL_ACCESS,FALSE,GPS_READY);



	//检查是否打开了自动校正
	//if ((bool)sysConfig.sysParam.curAutoAdjustSwith)
	//{
	//	SetEvent(m_hGpsCaliEnable);
	//}
	//else
	//{
	//	ResetEvent(m_hGpsCaliEnable);
	//}
	

}

SetupTimeManager::~SetupTimeManager()
{

}

//恢复出厂设置
LRESULT SetupTimeManager::RestoreDefault(DWORD param1, DWORD param2)
{

	sysConfig.sysParam.curCalenderDayType = 0;
	sysConfig.WriteConfig(&sysConfig.sysParam.curCalenderDayType);

	sysConfig.sysParam.curTime24HMode = 0;
	sysConfig.WriteConfig(&sysConfig.sysParam.curTime24HMode);

	sysConfig.sysParam.curAutoAdjustSwith= 1;
	sysConfig.WriteConfig(&sysConfig.sysParam.curAutoAdjustSwith);
	SetEvent(m_hGpsCaliEnable);
	
	sysConfig.sysParam.curAutoAdjustDone = false;//未校正
	sysConfig.WriteConfig(&sysConfig.sysParam.curAutoAdjustDone);

	return 0;
}

SetupTimeManager* SetupTimeManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupTimeManager;
	}
	return m_pInstance;
}


bool SetupTimeManager::ReadMinMax( const string &sline_name, int & min_cursor, int & max_cursor )
{
	if(cs_timemode == sline_name|| cs_calender == sline_name || cs_AutoAdjustSwith == sline_name)
	{
		min_cursor = 0;
		max_cursor = 1;
		if(sline_name == cs_AutoAdjustSwith)
		{
			AfxPostMessage(CTR_LISTLINE_ENABLE,WPARAM( !(bool)sysConfig.sysParam.curAutoAdjustSwith),0);
		}
		return true;
	}
	ReadTimeSetup();
	return false;//没有最大 最小游标
}

bool SetupTimeManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{

	if(cs_AutoAdjustSwith == sline_name)
	{
		n_cursor = (bool)sysConfig.sysParam.curAutoAdjustSwith;
		if (n_cursor)
		{
			sline_data=CHDLL_STR::C_ON;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
		return true;
	}
	else if(cs_timemode == sline_name)
	{
		bool b = (bool)sysConfig.sysParam.curTime24HMode;
		if (b)
		{
			n_cursor = b;
			sline_data = "24h";
		}
		else
		{
			n_cursor = b;
			sline_data = "12h";	
		}
		return true;
	}
	else if (cs_calender == sline_name)
	{
		bool b = (bool)sysConfig.sysParam.curCalenderDayType;
		if (b)
		{
			n_cursor = 1;
			sline_data = "D/M";
		}
		else
		{
			n_cursor = 0;
			sline_data = "M/D";	
		}
		return true;

	}
	T_LIST_DATA::iterator pos = m_curListData.find(sline_name);
	ASSERT(pos != m_curListData.end());
	n_cursor = *(pos->second);
	
	char text_v[8]; 
	int nCur = n_cursor;
	if (sline_name == cs_clock)
	{
		bool b = (bool)sysConfig.sysParam.curTime24HMode;
		if (!b)
		{
			if (nCur>12)
			{
				nCur = nCur%12;
			}
			if (n_cursor>=12)
			{
				sprintf(text_v,"%02d PM",nCur);
			}
			else
			{
				sprintf(text_v,"%02d AM",nCur);
			}
		}
		else
		{
			sprintf(text_v,"%02d",nCur);
		}

		
	}
	else
	{
		sprintf(text_v,"%d",nCur);
	}
	
	sline_data = text_v;
	return true;
}



bool SetupTimeManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{

	if(cs_AutoAdjustSwith == sline_name)
	{
		sysConfig.sysParam.curAutoAdjustSwith = n_cursor;
		sysConfig.WriteConfig(&sysConfig.sysParam.curAutoAdjustSwith);
		AfxPostMessage(CTR_LISTLINE_ENABLE,WPARAM( !(bool)sysConfig.sysParam.curAutoAdjustSwith),0);
		ReadSetup(sline_name,n_cursor,sline_data);

		if ((bool)sysConfig.sysParam.curAutoAdjustSwith)
		{
			SetEvent(m_hGpsCaliEnable);
		}
		else
		{
			ResetEvent(m_hGpsCaliEnable);
		}

		return true;
	}
	else if(cs_timemode == sline_name)
	{
		if (n_cursor)
		{
			sline_data = "24h";
		}
		else
		{
			sline_data = "12h";
		}
		sysConfig.sysParam.curTime24HMode  = n_cursor;
		sysConfig.WriteConfig(&sysConfig.sysParam.curTime24HMode);
		return true;
	}
	else if (cs_calender == sline_name)
	{
		if (n_cursor)
		{
			sline_data = "D/M";		
		}
		else
		{
			sline_data = "M/D";	
		}
		sysConfig.sysParam.curCalenderDayType = n_cursor;
		sysConfig.WriteConfig(&sysConfig.sysParam.curCalenderDayType);
		return true;
	}
	T_LIST_DATA::iterator pos = m_curListData.find(sline_name);
	ASSERT(pos != m_curListData.end());
	*(pos->second) =  n_cursor;
	if (WriteTimerSetup())//写入后需要重新读取
	{
		if (sline_name==cs_date)
		{
			//m_systime.wDay = 1;
		}
		else
		{
			AfxSendMessage(CTR_SETUP_READ_LIST,(WPARAM)cs_date.c_str(),0);
			//return true;//本次写入需要重读
		}

	}
	ReadSetup(sline_name,n_cursor,sline_data);

	//CheckSetAdjustText(false);//未校正
	return true;
}

void SetupTimeManager::ReadTimeSetup()
{
	
	GetLocalTime(&m_systime);
	m_curListData[cs_year] =  &m_systime.wYear;
	m_curListData[cs_month] = &m_systime.wMonth;
	m_curListData[cs_date] = &m_systime.wDay;
	m_curListData[cs_clock] = &m_systime.wHour;
	m_curListData[cs_minute] = &m_systime.wMinute;
	if (m_systime.wYear<2013)
	{
		m_systime.wYear = 2013;
		SetLocalTime(&m_systime);
	}
}

bool SetupTimeManager::WriteTimerSetup()
{
	bool bChanged = false;
	SetDataInArea(m_systime.wYear,2013,2050);
	SetDataInArea(m_systime.wMonth,1,12);
	SetDataInArea(m_systime.wHour,0,23);
	SetDataInArea(m_systime.wMinute,0,59);

	if (m_systime.wDay > 31)
	{
			m_systime.wDay = 1;
	}
	else if (m_systime.wDay <1)
	{
		m_systime.wDay = 31;
	}
	if (m_systime.wMonth == 4 || m_systime.wMonth == 6 || m_systime.wMonth == 9 || m_systime.wMonth == 11)
	{
		if (m_systime.wDay > 30)
		{
			m_systime.wDay = 30;
			bChanged = true;
		}
	}
	else if (m_systime.wMonth == 2)
	{
		if (IsRunNian(m_systime.wYear))
		{
			if (m_systime.wDay > 29)
			{
				m_systime.wDay = 29;
				bChanged = true;
			}
		}
		else
		{
			if (m_systime.wDay > 28)
			{
				m_systime.wDay = 28;
				bChanged = true;
			}
		}
	}

	
	bool b = SetLocalTime(&m_systime);
	return bChanged;
}


BOOL SetupTimeManager::IsRunNian(WORD year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return 1;
			}
			return 0;
		}
		return 1;
	}
	return 0;
}

void SetupTimeManager::SetDataInArea( WORD &d, int min, int max )
{
	if (d<min || d > 0x8000)
	{
		d = max;
	}
	else if (d > max)
	{
		d = min;
	}
}

void SetupTimeManager::CheckSetAdjustText( bool bAdjust )
{
	if (NULL == m_pAdjustTitle)
	{
		return;
	}
	//ASSERT(m_pAdjustTitle);
	if (bAdjust == (bool)sysConfig.sysParam.curAutoAdjustDone)
	{
		return;
	}
	sysConfig.sysParam.curAutoAdjustDone = bAdjust;
	sysConfig.WriteConfig(&sysConfig.sysParam.curAutoAdjustDone);
	if (sysConfig.sysParam.curAutoAdjustDone)
	{
		m_pAdjustTitle->setTextFromId("ID_Ok_Adjust_Tile");
	}
	else
	{
		m_pAdjustTitle->setTextFromId("ID_No_Adjust_Tile");
	}
	
}

//void SetupTimeManager::SetAjustText( GxxSwText *pAdjustTitle )//进入 时钟校正 界面时检查
//{
//	m_pAdjustTitle = pAdjustTitle;
//	ASSERT(m_pAdjustTitle);
//
//	if (sysConfig.sysParam.curAutoAdjustDone)
//	{
//		m_pAdjustTitle->setTextFromId("ID_Ok_Adjust_Tile");
//	}
//	else
//	{
//		m_pAdjustTitle->setTextFromId("ID_No_Adjust_Tile");
//	}
//
//}

//void SetupTimeManager::CheckCaliDone()
//{
//	if (m_pAdjustTitle && m_hGpsCaliReady && WAIT_OBJECT_0 == WaitForSingleObject(m_hGpsCaliReady,0) )//检查有没有校正 
//	{
//		ResetEvent(m_hGpsCaliReady);
//		CheckSetAdjustText(true);//已经校正
//	}
//}


