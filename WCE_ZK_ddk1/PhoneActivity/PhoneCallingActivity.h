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

	PhoneHardware*	phoneHardware;	//ͨѶЭ�� 

	GxxAniLable* pLabelContactsName;
	GxxAniLable* pLabelDiagKeyToKeypad;	//��ͨ�����棬�ص����̽���
	GxxAniLable* pLabelDialInterfaceRing;	//ͨ�������н����绰
	GxxAniLable* pLabelDialInterfaceTime;

	GxxAniLable* pLabelHandup;	//�ҵ绰
	GxxAniLable* pLabelSwitchAudio;	//�л��ֻ�����������

	void Handup();
	void KeyTransform();
	void Contact();

	int dialTime;	//ͨ��ʱ��

	int iTimerPhoneTime;	//ͨ�绰��ʱ����ʱ��IDs

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


