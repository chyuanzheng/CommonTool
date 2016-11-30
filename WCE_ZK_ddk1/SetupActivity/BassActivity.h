#pragma once
#include "Activity.h"
#include "SetupDllModule.h"
#include "GXNotify.h"
class GxxBassListGroup;

class GxxAniLable;

class CE_SETUPACTIVITY_API  BassActivity : public Activity
{
public:
	enum{chinese,english};
	BassActivity(){}
	virtual ~BassActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();
private:
	DECLARE_NOTIFY_CALLBACK(SetDefault, BassActivity);	

	DECLARE_NOTIFY_CALLBACK(RestoreDefault, BassActivity);
	GxxView  *m_btx;
	GxxBassListGroup *m_lanGroup;


};


