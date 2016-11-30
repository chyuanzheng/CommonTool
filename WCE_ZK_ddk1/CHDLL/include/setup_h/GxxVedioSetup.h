#pragma once

#include "GxxView.h"
#include "AnimationManage.h"

class Activity;
class CE_CONTROL_API GxxVedioSetup : public GxxView
{
public:
	GxxVedioSetup();
	virtual ~GxxVedioSetup();
	static GxxView* CreateControl();

protected:
	//virtual void Draw( );
	//响应自身事件
	virtual void onResume();
	virtual void onPause();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);

private:
	GxxView * m_vedioList;
	Activity *m_setupActivity;
};

