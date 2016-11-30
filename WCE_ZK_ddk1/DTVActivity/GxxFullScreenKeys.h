#pragma once
#include "DTVDllModule.h"
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxTimer.h"

class GxxVedioSetup;
class GxxFullSKeyBoard;
class CE_DTVACTIVITY_API GxxFullScreenKeys : public GxxView,GxxTimer
{
public:
	GxxFullScreenKeys();
	virtual ~GxxFullScreenKeys();
	static GxxView* CreateControl();
	void SetMessageView(GxxView * mesView);
	void ClickWnd();
	void UserClick();//用户有动作
	void Reset();
	void onPause();

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam );
	void PostDtvMessage( UINT msg );
	virtual void TimerTick(UINT nIDEvent);
	

private:
	GxxView				*m_mesView;
	GxxFullSKeyBoard	*m_keyBoard;
	GxxView				*m_closeBtn;
	GxxVedioSetup		*m_vedioSetup;
	GxxView				*m_keyBtn;
	GxxView				*m_setBtn;
	GxxView				*m_leaveBtn;
	UINT     m_timer_id;
};
