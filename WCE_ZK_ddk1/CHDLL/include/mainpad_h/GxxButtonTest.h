#pragma once

#include "GxxView.h"
#include "AnimationManage.h"

class GxxVedioSetup;
class CE_CONTROL_API GxxButtonTest : public GxxView
{
protected:
	HANDLE     m_handleUp;
	GxxVedioSetup *m_setupV;
	//按钮图片
	//判断是否被按下
	TCHAR     m_isGxxButtonDown;
protected:

	//绘画
	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    

public:
	GxxButtonTest();
	virtual ~GxxButtonTest();
	static GxxView* CreateControl();
	DWORD m_time;
	//void startAnimation(Animation * ani);
	

};
