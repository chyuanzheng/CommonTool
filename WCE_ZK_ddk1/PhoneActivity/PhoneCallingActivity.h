#pragma once
#include "Activity.h"
#include "PhoneDllModule.h"
#include "GxxString.h"
#include "GXNotify.h"
#include "GxxAniLable.h"
//#include "GxxDeviceListGroup.h"
#include "BT/PhoneHardwareManager.h"

class CE_PHONEACTIVITY_API  PhoneCallingActivity : public Activity,GxxTimer
{
public:
	static Activity * pThis;
	PhoneCallingActivity();
	virtual ~PhoneCallingActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();

	PhoneHardware*	phoneHardware;	//通讯协议 

	GxxAniLable* pLabelContactsName;
	GxxAniLable* pLabelDiagKeyToKeypad;	//从通话界面，回到键盘界面
	GxxAniLable* pLabelDialInterfaceRing;	//通话界面中接听电话
	GxxAniLable* pLabelDialInterfaceTime;

	GxxAniLable* pLabelHandup;	//挂电话
	GxxAniLable* pLabelSwitchAudio;	//切换手机和蓝牙声道

	void Handup();
	void KeyTransform();
	void Contact();

	int dialTime;	//通话时间

	int iTimerPhoneTime;	//通电话计时，定时器IDs

	DECLARE_NOTIFY_CALLBACK(BtStatusNotify, PhoneCallingActivity);

	void TimerTick( UINT nIDEvent );

	void SetContactName(GxxString str);

	/*DECLARE_NOTIFY_CALLBACK(PairRecordNotify, PhoneCallingActivity);	

	void PreparePairRecord();
	void InsertPairRecord(GxxString strName, int pos);

	void PairDisConnect();
	void PairConnect(int select);
	void DeletePairRecord(int pos);*/



private:
	//GxxAniLable* pLabelBack_btn;

//	PhoneDeviceInterface* pLstPairRecord;
};


