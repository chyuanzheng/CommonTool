#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
/************************************************************************/
/* ���� �����Ŀؼ�����������                                                                     */
/************************************************************************/
class CE_CONTROL_API GxxCommonCtr : public GxxView
{

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
    
public:
	GxxCommonCtr();
	virtual ~GxxCommonCtr();
    static	GxxView* CreateControl();
	//void startAnimation(Animation * ani);
	static GxxView *s_commonCtrl;//�����ؼ�
	GxxView * m_groupbtn;
	

};
