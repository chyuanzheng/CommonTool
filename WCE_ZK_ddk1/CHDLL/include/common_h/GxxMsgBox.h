#pragma once
#include "AnimationManage.h"
#include "GxxTimer.h"

class GxxPicture;
class GxxSwText;
class  GxxMsgBox : public GxxView,protected GxxTimer
{
public:
	GxxMsgBox();
	virtual ~GxxMsgBox();
	static GxxView* CreateControl();
	static void ShowMsgBox( const string& text, UINT time, LPCRECT rc,bool bIsID );
protected:

	virtual void onPause();
	virtual void TimerTick(UINT nIDEvent);
	//绘画
	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	void DoShowMsgBox( const string& text, UINT time,  LPCRECT rc ,bool bIsID );
private:
	GxxPicture *m_pPicBack;
	GxxSwText *m_textlable;
	static  GxxMsgBox * S_msgBox;
	UINT	m_uTimerId;
	UINT    m_timeCount;
	RECT    m_defRect;

};
