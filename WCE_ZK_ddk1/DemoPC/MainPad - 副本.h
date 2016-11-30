#pragma once

#include "Activity.h"
#include "GxxToolGroup.h"
#include "GxxAppGroup.h"
#include "GXNotify.h"


//class PhoneHardware;
class MainPad : public Activity,GxxTimer
{
public: 
	MainPad(){}
	virtual ~MainPad (){}
	virtual public void onCreate();
	//virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	static Activity* CreateControl();
	virtual void onResume();
	virtual void onPause();
	virtual BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );


	void xbtnDown();

	static DWORD MCUEventHandler(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);
	static DWORD NaviSound(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);


	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, MainPad);
	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg_Up, MainPad);
	void LoadXml();
	void LanchModule();
	DECLARE_NOTIFY_CALLBACK(CarBrakeChange, MainPad);

	DECLARE_NOTIFY_CALLBACK(WarnningText, MainPad);
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, MainPad);
protected:
	virtual void TimerTick(UINT nIDEvent);
private:
	GxxToolGroup  *m_groupbtn;
	GxxView  *m_btx;
	GxxView  *m_commonview;
	GxxAppGroup   *m_appGroup;
	//PhoneHardware* m_hardware;

	UINT iTimerResumerVolDelay;
	UINT iTIMER_RESUMEVOL;
	UINT iTimerResumeMedia;
	BOOL bVolResuming;

	UINT m_volTimer1;
	UINT m_volTimer2;
	UINT m_volType; //0,无动作，1减音量，2加音量

	UINT m_testTime;

	int resumeVolTimes;
	int startVol;
	


};
