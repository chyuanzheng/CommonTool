#pragma once
#include "SetupDllModule.h"
#include "SetupFuction.h"
#include "GXNotify.h"

class CE_SETUPACTIVITY_API SetupNormalManager
{
public:
	enum S_COLOR{Blue=0,Red,Green,Amber,Mono};
	static SetupNormalManager* GetInstance();
	static void  SetFucPos()
	{
		SetupFuction::GetInstance()->SetFunction( SReadSetup, SWriteSetup,SReadMinMax );
	}


private:
	SetupNormalManager();
	~SetupNormalManager();
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, SetupNormalManager);
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

	void WriteColor( string & sline_data );

	bool  WriteSetup(const string &sline_name, int &n_cursor, string &sline_data);



	static SetupNormalManager *m_pInstance;
	int  m_color; 
	BYTE  &m_beepValue;



};


