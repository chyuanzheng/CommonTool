#pragma once
#include "Activity.h"
#include "DTVDllModule.h"
#include "GxxString.h"
#include "GXNotify.h"
#include "DtvMediaWndEx.h"
#include "TVHardware.h"
#include "GxxProgressBar.h"
#include "TimerManager.h"
#include "GxxControlGroup.h"
#include "GxxTimer.h"

class GxxFullScreenKeys;
class GxxCommonKeys;
class GxxNormalKeys;
class CE_DTVACTIVITY_API  DTVActivity : public Activity,GxxTimer
{
public:
	DTVActivity(){}
	virtual ~DTVActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();


	DtvMediaWndEx	*m_mediaWnd;

	

	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, DTVActivity);
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam );
	virtual void TimerTick(UINT nIDEvent);
private:

	

	DTVHardware	m_dtvHardware;
	int		m_curVFormat;//0��ʾ���ź�
	bool    m_isInfoScreen;//�Ƿ�ΪIͼ
	bool	m_isFullScreen;

	//GXWindow		*pNormalWnd;
	//GXWindow		*pFullWnd;

	GxxControlGroup* m_i_group;
	GxxControlGroup* m_normal_group;
	GxxControlGroup *m_full_group;


	GxxFullScreenKeys  *m_fullscreenKeys;
	GxxCommonKeys      *m_commonKeys;
	GxxNormalKeys      *m_normalKeys;

	GxxAniLable* m_pLabelTip;
	GxxPicIcon* m_picAuxLogo;



	HANDLE		m_checkHandle;
	static  bool s_pauseCheck;//�Ƿ�ֹͣ���

	UINT     m_fsTimer;
	
	
private:
	static DWORD CheckDtvThread(LPVOID lpParam);
	void  CheckDtvThread();
	void StartDTV( int type );
	void DtvSignal( int nSig );
	void EnterFullScreen(bool isEnter);
	
};


