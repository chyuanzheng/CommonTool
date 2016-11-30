#include "StdAfx.h"
#include "GxxToolButton.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "AppManage.h"
#include "GxxAppButton.h"
#include "GxxAtButton.h"
//
//#include "aygshell.h"
const int LEN_DEC = 5;
GxxToolButton::GxxToolButton(int nth):GxxAtButton(nth)
{
	//需要申请内存的变量都需要在默认构造函数中赋空值

	m_picBack = new GxxPicture;
	m_bshow = TRUE;
}



GxxToolButton::~GxxToolButton()
{

	delete m_picBack;
}



void GxxToolButton::Draw(  )
{
	//被按下为真
	
	if (!getBtnIsDown())
	{
		m_picBack->DrawPic();
	}

	if (!m_bshow)
	{
		return;
	}

	GxxAtButton::Draw();

}


void GxxToolButton::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);

	RectChanged();

	RECT rc;
	SetRect(&rc,m_ActRect.left-LEN_DEC,m_ActRect.top-LEN_DEC,m_ActRect.right+LEN_DEC ,m_ActRect.bottom+LEN_DEC);	
	 
	if (m_picBack->setPicHandle(ele,BTN_BACK))
	{
		m_picBack->setCtrRect(rc);
		m_picBack->bindHandleRect();
	}
	else
	{
		ASSERT(0);
	}
}


void GxxToolButton::renewModule(T_AppModule * m )
{
	setBtnModule(m);
	RectChanged();
}

HANDLE GxxToolButton::getAniHandle()
{
	return m_picBack->getPicHandle();
}

BOOL GxxToolButton::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	if (!m_bshow)
	{
		return FALSE;
	}
	return GxxAtButton::Response(nMsg,wParam,lParam);
}

void GxxToolButton::showButton( BOOL show )
{
	m_bshow = show;
}



