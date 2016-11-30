#pragma once
#include "DTVDllModule.h"
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxFullSKeyBoard.h"

class GxxVedioSetup;
class CE_DTVACTIVITY_API GxxCommonKeys : public GxxView
{
public:
	GxxCommonKeys();
	virtual ~GxxCommonKeys();
	static GxxView* CreateControl();
	void SetMessageView(GxxView * mesView);

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam );
	void PostDtvMessage( UINT msg );

private:
	GxxView			*m_mesView;
	GxxView			*m_back_btn;
	GxxView			*m_left_btn;
	GxxView			*m_right_btn;
	GxxView			*m_info_btn;

};
