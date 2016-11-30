#pragma once
#include "SetupDllModule.h"
#include "SetupFuction.h"
#include "BT\PhoneHardwareManager.h"
#include "GXNotify.h"
#include "GxxSetupListGroup.h"
class CE_SETUPACTIVITY_API SetupBlueToothManager
{
public:
	static SetupBlueToothManager* GetInstance();
	void  SetFucPos()
	{
		m_setuplist  = GxxSetupListGroup::GetCurList();
		SetupFuction::GetInstance()->SetFunction( SReadSetup, SWriteSetup,SReadMinMax,SGetStatus );
	}

private:
	SetupBlueToothManager();
	~SetupBlueToothManager();
	DECLARE_NOTIFY_CALLBACK(BTSwitchStatus, SetupBlueToothManager);
	DECLARE_NOTIFY_CALLBACK(BTAutolinkStatus, SetupBlueToothManager);
	
	static bool  SReadMinMax(const string &sline_name, int & min_cursor, int & max_cursor)
	{
		return GetInstance()->ReadMinMax(sline_name,min_cursor,max_cursor);
	}
	static bool  SReadSetup(const string  &sline_name,int   &n_cursor, string &sline_data)
	{
		return GetInstance()->ReadSetup(sline_name,n_cursor,sline_data);
	}
	static bool  SWriteSetup(const string &sline_name, int &n_cursor, string &sline_data)
	{
		return GetInstance()->WriteSetup(sline_name,n_cursor,sline_data);
	}

	static int  SGetStatus(const string &sline_name)
	{
		return GetInstance()->GetStatus(sline_name);
	}


	bool  ReadMinMax(const string &sline_name,int & min_cursor,int & max_cursor);
	bool  ReadSetup(const string  &sline_name,int   &n_cursor, string &sline_data);
	void  WriteColor( string & sline_data );
	bool  WriteSetup(const string &sline_name, int &n_cursor, string &sline_data);
	int   GetStatus(const string &sline_name);
	
	static SetupBlueToothManager *m_pInstance;
	bool m_bBluetoothOpen;
	bool m_bBluetoothAutolink;

	bool m_bBtOpenWaiting;
	bool m_bBtAutolinkWaiting;

	GxxLBList* m_setuplist;
	PhoneHardware* phoneHardware;


};


