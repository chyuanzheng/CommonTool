#pragma once
#include "Activity.h"
#include "PHONEDllModule.h"
#include "GxxString.h"
#include "GXNotify.h"
#include "GxxAniLable.h"
#include "GxxControlGroup.h"
//#include "BT\PhoneHardware2.h"
#include "BT/PhoneHardwareManager.h"
#include "TimerManager.h"
#include "GxxTextBox.h"

#include "GxxPhoneListGroup.h"
#include "GxxRecordListGroup.h"
#include "bluetooth.h"

#include "PhoneCallingActivity.h"

class CE_PHONEACTIVITY_API  PhoneActivity : public Activity,GxxTimer
{
public:
	class PHONE
	{
	public:
		GxxString strNo;
		GxxString strName;
	};
	enum
	{
		CONNECT = 0,
		DISCONNECT,
		KEYPAD_INTERFACE,	//键盘界面
		PHONE_INTERFACE,	//电话本界面
		RECORD_INTERFACE,	//电话记录界面
		MAIN_INTERFACE,	//主界面
		CALLING_INTERFACE	//通话中界面
		
	};

	PhoneActivity(){}
	virtual ~PhoneActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();

	//蓝牙状态
	DECLARE_NOTIFY_CALLBACK(BtStatusNotify, PhoneActivity);
	//蓝牙与手机之间切换
	//DECLARE_NOTIFY_CALLBACK(SoundStatusNotify, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(PhoneBookNotify, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifySetBtPassword, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifySetAutoConnect, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyOpenOrCloseBT, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyReadBTPassword, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyPhoneRecordStatus, PhoneActivity);
	
	
	//DECLARE_NOTIFY_CALLBACK(NotifyDeviceStatus, PhoneActivity);

	

	//插入电话
	void InsertPhoneBook(GxxString strName, GxxString strNO);
	void InsertPhoneRecord(GxxString strName, GxxString strNO, RecordItem::RecordType type);

	GxxString GetNameFromNo(GxxString strNo);

	PhoneListInterface *pPhoneList;
	RecordListInterface *pRecordList;
	

	void ClearPhoneBook();

	//读取通话记录
	void ReadRecord();




private:
	GxxAniLable* pLabelRecentCalls;	//通话记录
	GxxAniLable* pLabelPhoneBook;	//电话本
	GxxAniLable* pLabelKeypad;	//键盘

	Activity * pLastActivity;	//用于保存来电之前的窗口
	Activity* pPhoneCallingActivity;


	GxxAniLable* pLabel_Return_Main;	//返回主界面

	GxxControlGroup* pControlGroup_Main;	//主界面
	GxxAniLable* pLabel_Disconnect;
	GxxAniLable* pLabel_Reconnect;
	GxxAniLable* pLabel_ChangeDevice;

	GxxControlGroup* pControlGroup_keypad;	//键盘界面

	GxxAniLable* pLabel_Key0;
	GxxAniLable* pLabel_Key1;
	GxxAniLable* pLabel_Key2;
	GxxAniLable* pLabel_Key3;
	GxxAniLable* pLabel_Key4;
	GxxAniLable* pLabel_Key5;
	GxxAniLable* pLabel_Key6;
	GxxAniLable* pLabel_Key7;
	GxxAniLable* pLabel_Key8;
	GxxAniLable* pLabel_Key9;
	GxxAniLable* pLabel_KeyC;
	GxxAniLable* pLabel_KeyXin;
	GxxAniLable* pLabel_KeyJin;
	GxxAniLable* pLabelDeleteAll;

	GxxAniLable* pLabel_KeyRing;


	GxxTextBox* pTextBox_PhoneNum;

	GxxControlGroup* pControlGroup_PhoneList;	//电话本界面
	GxxControlGroup* pControlGroup_RecordList;	//通话记录
	GxxControlGroup* pControlGroup_CallReceive;	//电话通话窗口

	GxxAniLable* pLabelContactsName;

	GxxAniLable* pLabelHandup;	//挂电话
	GxxAniLable* pLabelSwitchAudio;	//切换手机和蓝牙声道
	GxxAniLable* pLabelDiagKeyToKeypad;	//从通话界面，回到键盘界面
	GxxAniLable* pLabelDialInterfaceRing;	//通话界面中接听电话
	GxxAniLable* pLabelDialInterfaceTime;
	GxxAniLable* pLabelDialInterfaceTip;

	GxxAniLable* pLabel_CallReceiveReturnMain;

	GxxAniLable* pLabel_To_Music;

	//bool bIsDialing;	//通话中

//	GxxAniLable* pLabel_PhoneListToMain;

	PhoneHardware*	phoneHardware;	//通讯协议 
	//map< GxxString, GxxString>mapPhoneBook;	//电话薄
	map<int, PHONE>mapPhoneBook;	//电话薄
	int iPhoneRecordCount;
	map<int, PHONE>mapPhoneRecord;	//通话记录

	int iTimerPhonebook;	//定时器ID，获取电话本
	int iTimerPhoneTime;	//通电话计时，定时器ID
	//int iTimerPhoneSignal;	//信号强度
	int iTimerPhoneAutoAnswer;	//自动应答

	int dialTime;	//通话时间

	void TimerTick( UINT nIDEvent );

	void UpdateUI(int iStatus);	//更新UI
	
	int iLastUIInterface;	//上一UI界面
	int iCurrentUIInterface;
	void IntoLastUIInterface();	//跳转到上一UI界面

	void Contact();	//拨电话

	void KeyTransform();	//切换手机与蓝牙声道

	void KeyKeyPad(char c);

	void Handup();

	

	GxxAniLable* pInc_Into_MainInterface;

private:
	void InitAutoAnswer();	//初始化自动应答
	void AutoAnswer();	//自动应答
	void ExitAutoAnswer();	//退出自动应答
	int iAutoAnswerTime;
	void RememberLastUIInterfatce();	//记住上一个界面

	bool isNaviOnBeforeCalling;	//通话前，是否在导航界面

};


