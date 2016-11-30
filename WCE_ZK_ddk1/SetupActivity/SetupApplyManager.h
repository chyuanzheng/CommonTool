#pragma once
#include "SetupDllModule.h"
#include "SetupFuction.h"
#include "GXNotify.h"
#include "VersionXml.h"


class CE_SETUPACTIVITY_API SetupApplyManager
{
public:
	static SetupApplyManager* GetInstance();
	static void  SetFucPos()
	{
		SetupFuction::GetInstance()->SetFunction( SReadSetup, SWriteSetup,SReadMinMax );
	}

private:
	enum { OFF=0,S_5,S_10,S_15};
	enum { ALL,Front_L,Front_R,Front_LR};
	SetupApplyManager();
	~SetupApplyManager();
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, SetupApplyManager);
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

	bool  ReadMinMax(const string &sline_name,int & min_cursor,int & max_cursor);
	bool  ReadSetup(const string  &sline_name,int   &n_cursor, string &sline_data);
	bool  WriteSetup(const string &sline_name, int &n_cursor, string &sline_data);
	
	static SetupApplyManager *m_pInstance;
	int	 m_auto_answer;
	int	 m_phone_speaker;

	VersionXml::Option_Language		m_opt_language;
	VersionXml::Option_NaviSoftWare m_opt_Navi_SoftWare;
	VersionXml::Option_NaviMixSound m_opt_Navi_MixSound;
	VersionXml::Option_BT_Module    m_bt_Module;
	VersionXml::Option_BSF_Module   m_bsf_Module;

};


