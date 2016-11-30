#pragma once
#include "DllDefine.h"
class Activity;
struct CE_CONTROL_API T_AppModule
{
	T_AppModule()
	{
		b_playing = false;
		b_enable = true;
		p_act = NULL;
	}
	static string iconback;
	static string iconplay;
	string activity;
	string icon;
	string icong;
	string s_icon;
	string s_icong;
	string title;
	string title_id;
	string param_id;
	bool   b_playing;
	bool   b_enable;//是否可以点击运行
	int    m_nth;//第几个
	Activity * p_act;
	
};


typedef vector<T_AppModule *> TV_Module;



class CE_CONTROL_API  AppManage
{
public:
	static AppManage* GetInstance();
	//根据nth得到Module
    T_AppModule* GetModule(UINT nth);
	void  SetAppPlaying(const string & str_a,const string & str_para);
	void  SetAppEnable(const string & str_a,bool b);
	static bool GetAppEnable( const string & str_a, bool& ret);

	void SetActivity( const string& tostart, Activity * pAct );
	int GetActivityNth(Activity * const pAct );
private:
	AppManage();
	~AppManage();
	void init();

	void InitDllManifest();
	
	static AppManage *m_pInstance;
	static TV_Module m_vModule;
};

