#include "StdAfx.h"
#include "SetupAuxManager.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "StrDef.h"
const string aux_open_set  =		"aux_in_set";
const string aux_signal_set  = "aux_signal_set";



SetupAuxManager *SetupAuxManager::m_pInstance = NULL;
SetupAuxManager::SetupAuxManager()
{

	m_bAuxOpen = (bool)sysConfig.sysParam.curAuxOpen;
	m_auxSignal =  sysConfig.sysParam.curAuxSignal;

	if (m_auxSignal>PAL)
	{
		m_auxSignal = Auto;
	}

	Activity::EnableActivity("AuxActivity",m_bAuxOpen);
	//Activity::EnableActivity("BTMusicActivity",m_bAuxOpen);
	//

	//GXNotify::SendNotify("NotifyOpenOrCloseBT", m_bBluetoothOpen, 0);
	//这里要写入硬件
}

SetupAuxManager::~SetupAuxManager()
{

}


SetupAuxManager* SetupAuxManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupAuxManager;
	}
	return m_pInstance;
}


bool SetupAuxManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	if(sline_name == aux_open_set)
	{
		min_cursor = 0;
		max_cursor = 1;
		AfxPostMessage(CTR_LISTLINE_ENABLE,WPARAM(m_bAuxOpen),0);
	}
	else if (sline_name == aux_signal_set)
	{
		min_cursor = Auto;
		max_cursor = PAL;
	}
	else
	{
		ASSERT(0);
	}
	return true;//没有最大 最小游标
}

bool SetupAuxManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{

	if (sline_name == aux_open_set)
	{
		n_cursor = (int)m_bAuxOpen;
		if (m_bAuxOpen)
		{
			sline_data=CHDLL_STR::C_ON;;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
	}
	else if (sline_name == aux_signal_set)
	{
		n_cursor = (int)m_auxSignal;
		if (m_auxSignal == Auto)
		{
			sline_data="Auto";
		}
		else if (m_auxSignal == NTSC)
		{
			sline_data="NTSC";
		}
		else if (m_auxSignal == PAL)
		{
			sline_data="PAL";
		}
	}
	AfxInvalidateRect(NULL);
	return true;
}



bool SetupAuxManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == aux_open_set)
	{
		m_bAuxOpen = (bool)n_cursor;
		ReadSetup(sline_name,n_cursor,sline_data);
		sysConfig.sysParam.curAuxOpen = (BYTE)m_bAuxOpen;
		sysConfig.WriteConfig(&sysConfig.sysParam.curAuxOpen);
		AfxPostMessage(CTR_LISTLINE_ENABLE,WPARAM(m_bAuxOpen),0);
		Activity::EnableActivity("AuxActivity",m_bAuxOpen);
	}
	else if (sline_name == aux_signal_set)
	{
		m_auxSignal = n_cursor;
		ReadSetup(sline_name,n_cursor,sline_data);
		sysConfig.sysParam.curAuxSignal = (BYTE)m_auxSignal;
		sysConfig.WriteConfig(&sysConfig.sysParam.curAuxSignal);
	}
	else
	{
		ASSERT(0);
	}

	return true;
}


