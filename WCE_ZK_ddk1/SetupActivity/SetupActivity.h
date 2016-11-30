#pragma once
#include "Activity.h"
#include "SetupDllModule.h"
#include "GXNotify.h"
#include "BT\PhoneHardwareManager.h"

class GxxSetupListGroup;
class GxxFileListGroup;
class GxxAniLable;
class GxxSwText;
class GxxSetupListLine;
class CE_SETUPACTIVITY_API  SetupActivity : public Activity
{
public:
	enum  F_TYPE{InputPassword,Null_type};
	SetupActivity();
	virtual ~SetupActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();
	DECLARE_NOTIFY_CALLBACK(BtStatusNotify, SetupActivity);
protected:
	//virtual void TimerTick(UINT nIDEvent);
private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, SetupActivity);
	void SetBluePassword( const string& s );//
	void StartSetupActivity(WPARAM wParam);
	void StartSetupListBox( const string &name,int bReturn = 1 );
	void StartSetupMassage( WPARAM wParam );
	void TouchCalibrate();
	PhoneHardware* m_phoneHardware;
    GxxSetupListGroup *m_lb_group;
	GxxSetupListLine * m_bfs_line;
	GxxSetupListLine * m_parametric_line;
	GxxAniLable *m_bt_input;
	GxxView  *m_btx;
	GxxView * m_btnBack;
	string m_s_password;
	bool    m_bReRead;
	F_TYPE  m_f_type;//
	string  m_bt_password;

	GxxSwText *m_boot_version_txt;

};


