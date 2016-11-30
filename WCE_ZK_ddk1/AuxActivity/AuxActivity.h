#pragma once
#include "Activity.h"
#include "AuxDllModule.h"
#include "GxxString.h"
#include "GXNotify.h"
#include "TccMediaWndEx.h"
#include "TimerManager.h"



class CE_AuxACTIVITY_API  AuxActivity : public Activity,public GxxTimer
{
public:
	AuxActivity(){}
	virtual ~AuxActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();


	TccMediaWndEx	*pMediaWnd;


	int iTimerDetectAuxId;
	int iTimerFullWnd;

	void TimerTick( UINT nIDEvent );

	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, AuxActivity);

	static void ClickMediaWnd(GxxView *p, void *dwParam);	//��Ƶȫ��ʱ�������Ƶ�Ĵ�����

private:

	
	GxxPicIcon* pPicAuxLogo;
	int	curVFormat;	// ��ǰ��Ƶ��ʽ

	GxxAniLable* pInc_Into_MainInterface;

	GxxAniLable* pLabelWarnning;
};


