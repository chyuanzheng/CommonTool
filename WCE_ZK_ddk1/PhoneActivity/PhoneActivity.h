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
		KEYPAD_INTERFACE,	//���̽���
		PHONE_INTERFACE,	//�绰������
		RECORD_INTERFACE,	//�绰��¼����
		MAIN_INTERFACE,	//������
		CALLING_INTERFACE	//ͨ���н���
		
	};

	PhoneActivity(){}
	virtual ~PhoneActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();

	//����״̬
	DECLARE_NOTIFY_CALLBACK(BtStatusNotify, PhoneActivity);
	//�������ֻ�֮���л�
	//DECLARE_NOTIFY_CALLBACK(SoundStatusNotify, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(PhoneBookNotify, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifySetBtPassword, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifySetAutoConnect, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyOpenOrCloseBT, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyReadBTPassword, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, PhoneActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyPhoneRecordStatus, PhoneActivity);
	
	
	//DECLARE_NOTIFY_CALLBACK(NotifyDeviceStatus, PhoneActivity);

	

	//����绰
	void InsertPhoneBook(GxxString strName, GxxString strNO);
	void InsertPhoneRecord(GxxString strName, GxxString strNO, RecordItem::RecordType type);

	GxxString GetNameFromNo(GxxString strNo);

	PhoneListInterface *pPhoneList;
	RecordListInterface *pRecordList;
	

	void ClearPhoneBook();

	//��ȡͨ����¼
	void ReadRecord();




private:
	GxxAniLable* pLabelRecentCalls;	//ͨ����¼
	GxxAniLable* pLabelPhoneBook;	//�绰��
	GxxAniLable* pLabelKeypad;	//����

	Activity * pLastActivity;	//���ڱ�������֮ǰ�Ĵ���
	Activity* pPhoneCallingActivity;


	GxxAniLable* pLabel_Return_Main;	//����������

	GxxControlGroup* pControlGroup_Main;	//������
	GxxAniLable* pLabel_Disconnect;
	GxxAniLable* pLabel_Reconnect;
	GxxAniLable* pLabel_ChangeDevice;

	GxxControlGroup* pControlGroup_keypad;	//���̽���

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

	GxxControlGroup* pControlGroup_PhoneList;	//�绰������
	GxxControlGroup* pControlGroup_RecordList;	//ͨ����¼
	GxxControlGroup* pControlGroup_CallReceive;	//�绰ͨ������

	GxxAniLable* pLabelContactsName;

	GxxAniLable* pLabelHandup;	//�ҵ绰
	GxxAniLable* pLabelSwitchAudio;	//�л��ֻ�����������
	GxxAniLable* pLabelDiagKeyToKeypad;	//��ͨ�����棬�ص����̽���
	GxxAniLable* pLabelDialInterfaceRing;	//ͨ�������н����绰
	GxxAniLable* pLabelDialInterfaceTime;
	GxxAniLable* pLabelDialInterfaceTip;

	GxxAniLable* pLabel_CallReceiveReturnMain;

	GxxAniLable* pLabel_To_Music;

	//bool bIsDialing;	//ͨ����

//	GxxAniLable* pLabel_PhoneListToMain;

	PhoneHardware*	phoneHardware;	//ͨѶЭ�� 
	//map< GxxString, GxxString>mapPhoneBook;	//�绰��
	map<int, PHONE>mapPhoneBook;	//�绰��
	int iPhoneRecordCount;
	map<int, PHONE>mapPhoneRecord;	//ͨ����¼

	int iTimerPhonebook;	//��ʱ��ID����ȡ�绰��
	int iTimerPhoneTime;	//ͨ�绰��ʱ����ʱ��ID
	//int iTimerPhoneSignal;	//�ź�ǿ��
	int iTimerPhoneAutoAnswer;	//�Զ�Ӧ��

	int dialTime;	//ͨ��ʱ��

	void TimerTick( UINT nIDEvent );

	void UpdateUI(int iStatus);	//����UI
	
	int iLastUIInterface;	//��һUI����
	int iCurrentUIInterface;
	void IntoLastUIInterface();	//��ת����һUI����

	void Contact();	//���绰

	void KeyTransform();	//�л��ֻ�����������

	void KeyKeyPad(char c);

	void Handup();

	

	GxxAniLable* pInc_Into_MainInterface;

private:
	void InitAutoAnswer();	//��ʼ���Զ�Ӧ��
	void AutoAnswer();	//�Զ�Ӧ��
	void ExitAutoAnswer();	//�˳��Զ�Ӧ��
	int iAutoAnswerTime;
	void RememberLastUIInterfatce();	//��ס��һ������

	bool isNaviOnBeforeCalling;	//ͨ��ǰ���Ƿ��ڵ�������

};


