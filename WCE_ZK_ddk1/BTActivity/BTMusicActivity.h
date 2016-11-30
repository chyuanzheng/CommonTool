#pragma once
#include "Activity.h"
#include "BTMusicDllModule.h"
#include "GxxString.h"
#include "GXNotify.h"
#include "GxxAniLable.h"
//#include "BT\PhoneHardware2.h"
#include "GxxControlGroup.h"
#include "BT/PhoneHardwareManager.h"
class CE_BTMUSICACTIVITY_API  BTMusicActivity : public Activity
{
public:

	enum
	{
		CONNECT = 0,
		DISCONNECT
	};

	void UpdateUI(int iStatus);	//更新界面
	void PlayMusic();

	BTMusicActivity(){}
	virtual ~BTMusicActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();

	DECLARE_NOTIFY_CALLBACK(BtStatusNotify, BTMusicActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, BTMusicActivity);
	

	PhoneHardware *pPhoneHardware;


private:
	
	bool bIsPlaying;	//正在播放中

	GxxAniLable* pLabel_PlayAndPause;
	GxxAniLable* pLabel_SearchPrev;
	GxxAniLable* pLabel_SearchNext;

	GxxAniLable* pLabel_ToPhone;

	GxxAniLable* pLabel_Text_Tip;

	GxxAniLable* pInc_Into_MainInterface;
	GxxControlGroup* pControlGroup_page1;
	GxxAniLable* pLabel_Reconnect;
	GxxAniLable* pLabel_Disconnect;
	GxxAniLable* pLabel_ChangeDevice;


};


