#include "StdAfx.h"
#include "GxxMsgTypeBox.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GxxSwText.h"
#include "GxxAniLable.h"
#include "LangStringManager.h"

GxxMsgTypeBox * GxxMsgTypeBox::S_msgBox = NULL;
static RegisterHelp help("GxxMsgTypeBox", GxxMsgTypeBox::CreateControl);
GxxView* GxxMsgTypeBox::CreateControl()
{
	ASSERT(S_msgBox == NULL);
	S_msgBox = new GxxMsgTypeBox;
	return S_msgBox;
}


GxxMsgTypeBox::GxxMsgTypeBox()
{
	m_mesView = NULL;
	setDraw(false);
	setOnlyDrawActRect(true);
}

GxxMsgTypeBox::~GxxMsgTypeBox()
{

}




BOOL GxxMsgTypeBox::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;
	if (nMsg==WM_LBUTTONDOWN&&InMyArea(lParam))
	{
		return TRUE;
	}
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		return TRUE;

	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxAniLable *)wParam == m_leftBtn|| (GxxAniLable *)wParam == m_left_Dial_Btn)	
			{
				ASSERT(m_mesView);
				m_mesView->TranslateMessage(MES_MSG_OK,m_param,0);
				ResetBox();
				return TRUE;
			}
			else if  ((GxxAniLable *)wParam == m_rightBtn)	
			{
				ASSERT(m_mesView);
				m_mesView->TranslateMessage(MES_MSG_CANCEL,m_param,0);
				ResetBox();
				return TRUE;
			}
		}
	}
	return FALSE;
}

void GxxMsgTypeBox::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	bool b = setCtrRectUseCenter(ele);
	ASSERT(b);

	b = setPicHandle(ele,BACK_BMP);
	ASSERT(b);

	bindHandleRect();//m_pPicDisable
	TiXmlElement * chid = ele->FirstChildElement();
	setCtrList(chid);

	m_textlable = (GxxSwText  *)safeFindViewByName("msg_txt");
	m_leftBtn =  (GxxAniLable *)safeFindViewByName("msg_left");
	m_left_Dial_Btn = (GxxAniLable *)safeFindViewByName("msg_dial_left");
	m_rightBtn = (GxxAniLable *)safeFindViewByName("msg_right");
}



void GxxMsgTypeBox::ShowMsgBox( const string& sid, GxxView* view, DWORD param,int type )
{
	ASSERT(S_msgBox != NULL);
	ASSERT(view);
	S_msgBox->DoShowMsgBox(sid,view,param,type);
}
void GxxMsgTypeBox::ShowMsgBox( const wstring& text, GxxView* view, DWORD param,int type )
{
	ASSERT(S_msgBox != NULL);
	ASSERT(view);
	S_msgBox->DoShowMsgBox(text,view,param,type);
}


void GxxMsgTypeBox::DoShowMsgBox( const string& sid, GxxView* view,DWORD param, int type )
{
	m_textlable->setTextFromId(sid);
	SetMsgBoxValue(view, param, type);
}

void GxxMsgTypeBox::DoShowMsgBox( const wstring& text, GxxView* view,DWORD param, int type )
{
	m_textlable->setText(text);
	SetMsgBoxValue(view, param, type);
}



void GxxMsgTypeBox::SetMsgBoxValue( GxxView* view, DWORD param, int type )
{
	ASSERT(NULL==m_mesView);
	m_mesView = view;
	m_param = param;
	switch(type)
	{
	case ZKY_MB_OKCANCEL:
		m_leftBtn->setDraw(true);
		m_left_Dial_Btn->setDraw(false);
		break;
	case ZKY_MB_DIAL_CANCEL:
		m_leftBtn->setDraw(false);
		m_left_Dial_Btn->setDraw(true);
		break;
	default:
		ASSERT(0);
		break;
	}
	setDraw(true);
	invalidateRect();
}

void GxxMsgTypeBox::onPause()
{
	if (getDraw())
	{
		ResetBox();
	}

}

void GxxMsgTypeBox::ResetBox()
{
	setDraw(false);
	//setSelView(NULL);
	m_mesView = NULL;
	invalidateRect();
}

