#pragma once
#include "DTVDllModule.h"
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxFullSKeyBoard.h"

class GxxVedioSetup;
class CE_DTVACTIVITY_API GxxNormalKeys : public GxxView
{
public:
	GxxNormalKeys();
	virtual ~GxxNormalKeys();
	static GxxView* CreateControl();
	void SetMessageView(GxxView * mesView);

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam );
	void PostDtvMessage( UINT msg );
private:
	GxxView			*m_mesView;

	GxxView   *m_play_pause;
	GxxView   *m_content;
	GxxView   *m_showlist;
	GxxView   *m_stop;
	GxxView   *m_full_screen;
	GxxView   *m_fast_forward;
	GxxView   *m_fast_backward;
	GxxView   *m_replay;
	GxxView   *m_ok;
	GxxView   *m_vol_add;
	GxxView   *m_vol_dec;

	GxxView   *m_setup_audio;
	GxxView   *m_page_one;
	GxxView   *m_page_two;
	GxxView	  *m_setup_vedio;


	GxxView  *m_group_one;
	GxxView  *m_group_two;
	GxxView * m_leave;

};
