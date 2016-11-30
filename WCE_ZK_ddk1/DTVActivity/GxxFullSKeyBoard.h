#pragma once
#include "DTVDllModule.h"
#include "GxxView.h"
#include "AnimationManage.h"

class CE_DTVACTIVITY_API GxxFullSKeyBoard : public GxxView
{
public:
	GxxFullSKeyBoard();
	virtual ~GxxFullSKeyBoard();
	static GxxView* CreateControl();
	void SetMessageView( GxxView * mesView );

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam );
	void PostDtvMessage( UINT msg );

private:
	GxxView * m_mesView;
	GxxView * m_left_right_btn;
	GxxView * m_ok_btn;
	GxxView * m_up_btn;
	GxxView * m_left_btn;
	GxxView * m_right_btn;
	GxxView * m_down_btn;
	bool    m_isLeft;
	GxxView * m_picToLeft;
	GxxView * m_picToRight;
};
