#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxPicture.h"
class GxxSwText;
class GxxAniLable;
class CE_CONTROL_API GxxLableSet : public GxxView
{
public:
	GxxLableSet();
	virtual ~GxxLableSet();
	static GxxView* CreateControl();
	void StartAction(bool bright);
protected:

	virtual void onPause();
	//绘画
	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);

    


private:
	HANDLE m_hAni;
	AnimationAction * m_moveAction_1;
	AnimationAction * m_moveAction_2;
	typedef list<GxxAniLable *> TL_Lable;
	TL_Lable m_all_lable;
	GxxAniLable * m_sel_lable;
	typedef list<GxxSwText *> TL_TEXT;
	TL_TEXT m_alltext;	

};
