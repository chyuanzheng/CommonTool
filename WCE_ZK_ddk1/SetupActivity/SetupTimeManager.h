#pragma once
#include "SetupDllModule.h"
#include "SetupFuction.h"
#include "GXNotify.h"
#include "GxxSwText.h"

typedef map<string,WORD *>   T_LIST_DATA;//string为每一行的名字
class CE_SETUPACTIVITY_API SetupTimeManager
{
public:
	static SetupTimeManager* GetInstance();
	static void  SetFucPos()
	{
		SetupFuction::GetInstance()->SetFunction( SReadSetup, SWriteSetup,SReadMinMax );
	}

	//void SetAjustText(GxxSwText *pAdjustTitle);//设置 view
	//void CheckCaliDone();
private:
	SetupTimeManager();
	~SetupTimeManager();

	DECLARE_NOTIFY_CALLBACK(RestoreDefault, SetupTimeManager);

	static bool  SReadMinMax(const string &sline_name,int & min_cursor,int & max_cursor)
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



	static SetupTimeManager *m_pInstance;

	T_LIST_DATA m_curListData;//当前列表的所有设定
//设置时间
	void ReadTimeSetup();
	bool WriteTimerSetup();
	BOOL IsRunNian(WORD year);
	void SetDataInArea( WORD &d, int min, int max );
	void CheckSetAdjustText( bool bAdjust );
	
	SYSTEMTIME m_systime;

	GxxSwText *m_pAdjustTitle;//校正text

	bool     m_curAutoAdjustDone;
	HANDLE   m_hGpsCaliEnable;
	HANDLE   m_hGpsCaliReady;	
};


