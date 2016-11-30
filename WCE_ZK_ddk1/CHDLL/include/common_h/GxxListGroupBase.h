#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxPicture.h"


class GxxLBList;
class GxxAniButton;
class GxxProgressV;
class GxxSwText;
class CE_CONTROL_API GxxListGroupBase : public  GxxPicture
{
protected:

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	//virtual bool TranslateMessage( GxxView* mesView, UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void AfterMovePage(){}
	void CacuViewSatus();
	void FindChildCtrls();


	GxxLBList*	 m_curListBox;
	GxxAniButton *m_upBtn;
	GxxAniButton *m_downBtn;
	GxxProgressV *m_progress;
	GxxSwText *m_titleText;

	GxxView  *m_btx;
	GxxView * m_btnBack;
    

public:
	GxxListGroupBase();
	virtual ~GxxListGroupBase();


};
