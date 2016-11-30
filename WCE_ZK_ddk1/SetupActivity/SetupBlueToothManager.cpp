#include "StdAfx.h"
#include "SetupBlueToothManager.h"
#include "StrDef.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"

const string bt_open_set  =		"bt_open_set";
const string bt_autolink_set  = "bt_autolink_set";



SetupBlueToothManager *SetupBlueToothManager::m_pInstance = NULL;
SetupBlueToothManager::SetupBlueToothManager()
{

	phoneHardware = PhoneHardwareManager::GetPhoneHardware();
	phoneHardware->GetAutoStatus();
	m_bBluetoothOpen = m_bBluetoothAutolink =  false;





	//GXNotify::SendNotify("NotifyOpenOrCloseBT", m_bBluetoothOpen, 0);
	//����Ҫд��Ӳ��

	Notify notify;
	notify.dwParam = this;

	notify.funNotify = BTSwitchStatus;
	GXNotify::RegisterNotifyHandler("hfpstatus", notify);


	notify.funNotify = BTAutolinkStatus;
	GXNotify::RegisterNotifyHandler("autostatus", notify);

	m_bBtOpenWaiting = false;
	m_bBtAutolinkWaiting = false;
	m_setuplist = NULL;

}


SetupBlueToothManager::~SetupBlueToothManager()
{

}

//��ȡ��������״̬
LRESULT SetupBlueToothManager::BTSwitchStatus(DWORD param1, DWORD param2)
{
	m_bBluetoothOpen = param1;
	m_bBtOpenWaiting = false;
	
	if (m_setuplist&&m_setuplist == GxxSetupListGroup::GetCurList())
	{
		AfxPostMessage(CTR_LISTLINE_ENABLE,WPARAM(m_bBluetoothOpen),0);
		AfxPostMessage(CTR_SETUP_READ_LIST,(WPARAM)bt_open_set.c_str(),0);
	}

	Activity::EnableActivity("PhoneActivity",m_bBluetoothOpen);
	Activity::EnableActivity("BTMusicActivity",m_bBluetoothOpen);
	AfxPostMessage(CTR_BT_SWITCH, m_bBluetoothOpen, 0);
	return 0;
}

//��ȡ����Autolink
LRESULT SetupBlueToothManager::BTAutolinkStatus(DWORD param1, DWORD param2)
{
	m_bBluetoothAutolink =  param2;
	m_bBtAutolinkWaiting = false;

	if (m_setuplist&&m_setuplist == GxxSetupListGroup::GetCurList())
	{
		AfxPostMessage(CTR_SETUP_READ_LIST,(WPARAM)bt_autolink_set.c_str(),0);
	}
	return 0;
}



SetupBlueToothManager* SetupBlueToothManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupBlueToothManager;
	}
	return m_pInstance;
}


bool SetupBlueToothManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	
	min_cursor = 0;
	max_cursor = 1;
	if(sline_name == bt_open_set)
	{
		AfxPostMessage(CTR_LISTLINE_ENABLE,WPARAM(m_bBluetoothOpen &&  !m_bBtOpenWaiting),0);
	}
	return true;//û����� ��С�α�
}

bool SetupBlueToothManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{

	if (sline_name == bt_open_set)
	{
		n_cursor = (int)m_bBluetoothOpen;
		if (m_bBluetoothOpen)
		{
			sline_data=CHDLL_STR::C_ON;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
	}
	else if (sline_name == bt_autolink_set)
	{
		n_cursor = (int)m_bBluetoothAutolink;
		if (m_bBluetoothAutolink)
		{
			sline_data=CHDLL_STR::C_ON;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
	}
	AfxInvalidateRect(NULL);
	return true;
}



bool SetupBlueToothManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == bt_open_set)
	{
		m_bBluetoothOpen = (bool)n_cursor;
		if (m_bBluetoothOpen)
		{
			sline_data=CHDLL_STR::C_ON;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
		}
		
		m_bBtOpenWaiting = true;
		phoneHardware->BTSwitch(m_bBluetoothOpen);
		if (!m_bBluetoothOpen)
		{
			phoneHardware->QueryHFP();//�ر����ѯ��Ϣ

		}
		
	}
	else if (sline_name == bt_autolink_set)
	{
		m_bBluetoothAutolink = (bool)n_cursor;
		if (m_bBluetoothAutolink)
		{
			sline_data=CHDLL_STR::C_ON;
		}
		else
		{
			sline_data=CHDLL_STR::C_OFF;
			
		}
		m_bBtAutolinkWaiting = true;
		phoneHardware->AutoConnect(m_bBluetoothAutolink);
		phoneHardware->GetAutoStatus();
		
	}
	return true;
}

int SetupBlueToothManager::GetStatus(const string &sline_name)
{

	if (sline_name == bt_open_set)
	{
		if (m_bBtOpenWaiting)
		{
			return SETUP_FUN_WAITING;
		}
	}
	else if (sline_name == bt_autolink_set)
	{
		if (m_bBtAutolinkWaiting)
		{
			return SETUP_FUN_WAITING;
		}
	}

	return SETUP_FUN_OK;
}


