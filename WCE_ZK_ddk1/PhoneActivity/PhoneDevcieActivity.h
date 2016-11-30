#pragma once
#include "Activity.h"
#include "PhoneDllModule.h"
#include "GxxString.h"
#include "GXNotify.h"
#include "GxxAniLable.h"
#include "GxxDeviceListGroup.h"
#include "BT/PhoneHardwareManager.h"

class CE_PHONEACTIVITY_API  PhoneDevcieActivity : public Activity
{
public:
	PhoneDevcieActivity(){}
	virtual ~PhoneDevcieActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();

	PhoneHardware *pPhoneHardware;

	DECLARE_NOTIFY_CALLBACK(BtStatusNotify, PhoneDevcieActivity);
	DECLARE_NOTIFY_CALLBACK(PairRecordNotify, PhoneDevcieActivity);	

	void PreparePairRecord();
	void InsertPairRecord(GxxString strName, int pos);

	void PairDisConnect();
	void PairConnect(int select);
	void DeletePairRecord(int pos);

	DECLARE_NOTIFY_CALLBACK(RestoreDefault, PhoneDevcieActivity);



private:
	GxxAniLable* pLabelList_DeleteAll;

	PhoneDeviceInterface* pLstPairRecord;

	bool bConnectStatus;

	//int iTimerConnect;

	//void TimerTick( UINT nIDEvent );

	bool bConnectAnotherBtDevice;
	bool bDeleteBtDevice;
	
	int	iWillingSelect;
};


