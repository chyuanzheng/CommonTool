#pragma once
#include "Activity.h"
#include "SetupDllModule.h"
#include "GXNotify.h"

class GxxLangListGroup;

class GxxAniLable;

class CE_SETUPACTIVITY_API  LangChooseActivity : public Activity
{
public:
	enum{chinese,english};
	LangChooseActivity(){}
	virtual ~LangChooseActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	void ExitLangActivity() ;
	static Activity* CreateControl();
	void SetLang();
private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, LangChooseActivity);
	GxxView  *m_btx;
	GxxLangListGroup *m_lanGroup;
	GxxAniLable *m_okLable;
	GxxView * m_back;
	bool      m_is_init_sound;
};


