#pragma once
#include "Activity.h"
#include "NaviDllModule.h"
#include "GxxString.h"
#include "GXNotify.h"
#include "GxxAniLable.h"
#include "TimerManager.h"

class CE_NaviACTIVITY_API  NaviActivity : public Activity,public GxxTimer
{
public:
	NaviActivity(){}
	virtual ~NaviActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual bool GetAnimation(){return false;}
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();
	
	static DWORD DeviceChange(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);
	
	//int iVolumePermissionId;
	void TimerTick( UINT nIDEvent );	//接收定时器消息

	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, NaviActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyHideNavi, NaviActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyNaviVol, NaviActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyNaviVol2, NaviActivity);

	bool IsNaviOn();
	bool HideNavi();
	bool IsNaviOnTop();
	bool ShowNavi();
	

private:
	GxxString strDevicePath;
	GxxString strNaviPath;

	bool bIsDeviceExist;
	int iTimerCheckDevice;

	GxxAniLable* pInc_Into_MainInterface;

	bool IsDeviceExist();

	



};


