#pragma once

#include "GxxView.h"
#include "AnimationManage.h"

class GxxAniLable;
/************************************************************************/
/* ���� �����Ŀؼ�����������                                                                     */
/************************************************************************/
class CE_CONTROL_API GxxListPercent : public GxxView
{
public:
	GxxListPercent();
	virtual ~GxxListPercent();
	static	GxxView* CreateControl();
	//void startAnimation(Animation * ani);

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	//virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);

private:

	GxxAniLable *m_btn[10];
};
