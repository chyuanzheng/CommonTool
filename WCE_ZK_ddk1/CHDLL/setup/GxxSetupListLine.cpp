#include "StdAfx.h"
#include "GxxSetupListLine.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "StrDef.h"
#include "GxxAniPictureA.h"
#include "GxxSwText.h"
#include "GxxDelimiter.h"
#include "GxxSetupChooseBtn.h"
#include "GXCreateControls.h"
#include "ResStringManager.h"

GxxSetupListLine::GxxSetupListLine()
{
	m_pTextTitle = new GxxSwText;
	m_pTextTitle->setFormat(DT_VCENTER|DT_LEFT);
	m_pTextTitle->setTextFont(0xffffffff,26);
	AddCtrl(m_pTextTitle);

	m_clickType = T_None;
	m_btnType = TL_None;
	m_pPicIcon = NULL;
	m_pMoreView = NULL;
	m_aboutTimerId = 0;
}

GxxSetupListLine::~GxxSetupListLine()
{

	delete m_pTextTitle;
	if (NULL!=m_pPicIcon)
	{
		delete m_pPicIcon;
	}
	if (NULL!=m_pMoreView)
	{
		delete m_pMoreView;
	}
}




void GxxSetupListLine::setLineLayout( int index, TiXmlElement * ele )
{
	m_index = index;
	setCtrName(ele);//ResStringManager

	RECT p_rect = getParentView()->getCtrRect();
	int nlineHeight = ResStringManager::GetInstance()->getInt("ListLineHeight");
	::SetRect(&m_ActRect,p_rect.left,p_rect.top+index*nlineHeight,p_rect.right,p_rect.top+(index+1)*nlineHeight);
	RECT rc;
	SetRect(&rc,m_ActRect.left+10,m_ActRect.top,m_ActRect.right,m_ActRect.bottom);
	m_pTextTitle->setCtrRect(rc);
	const char *stitle_id = ele->Attribute(LISTLINE_TITLE_ID);
	if (NULL!=stitle_id)
	{
		m_pTextTitle->setTextFromId(stitle_id);//StrHelp::StringToWString(string(stitle));
	}
	else
	{
		const char *stitle = ele->Attribute(LISTLINE_TITLE);
		ASSERT(NULL!=stitle);
		m_pTextTitle->setText( stitle );
	}
	

	setClickType(ele);


	setMoreView(ele);


	if (m_btnType == TL_None && m_clickType == T_None)
	{
		SetLineEnable(false);

	}



	TiXmlElement * chid = ele->FirstChildElement();
	setLineChildLayout(chid);

}

void GxxSetupListLine::setLineChildLayout( TiXmlElement * ele )
{
	string ctrname;
	while(ele)
	{
		GxxView *ctr=NULL;
		ctrname = ele->Value();

		ctr = GXCreateControl::CreateControlByType(ctrname.c_str());
		if (NULL!=ctr)
		{
			AddCtrl(ctr);
			ctr->setCtrLayout(ele);
		}
		ele = ele->NextSiblingElement();
	}
}



void GxxSetupListLine::setClickType( TiXmlElement * ele )
{
	const char *s = ele->Attribute(CLICK_TYPE);
	if (s == string(TYPE_LISTBOX))
	{
		m_clickType = T_ListBox;
	}
	else if (s == string(TYPE_LISTBOX_ABOUT_MORE))
	{
		m_clickType = T_ListBoxAboutMore;
		m_aboutTimerId =  RegisterTimer(4000);
	}
	else if (s == string(TYPE_ACTIVITY))
	{
		m_clickType = T_Activity;
	}
	else if (s == string(TYPE_MASSAGE))
	{
		m_clickType = T_Massage;
	}
	else 
	{
		m_clickType = T_None;
	}

	if (m_clickType != T_None )
	{
		s = ele->Attribute(CLICK_NAME);
		ASSERT(NULL!=s);
		m_clickName = s;
		if (m_clickType != T_ListBoxAboutMore)
		{
			setIconMore();
		}
		
	}
}

void GxxSetupListLine::setMoreView( TiXmlElement * ele )
{

	int x = m_ActRect.right;
	int y = (m_ActRect.top + m_ActRect.bottom)/2;

	ASSERT(NULL == m_pMoreView);
	const char *s = ele->Attribute(LINE_BTN_TYPE);
	if (s == string(TYPE_BTN_GXXTHREEBTN_ONOFF))
	{
		//m_btnType = TL_ThreeBtnOnOff;
		//m_pMoreView = new GxxThreeBtnBool(x,y,CHDLL_STR::C_ON,CHDLL_STR::C_OFF);
		//AddCtrl(m_pMoreView);
		ASSERT(0);
	}
	else if (s == string(TYPE_BTN_GXXTHREEBTN_M_D))
	{
		//m_btnType = TL_ThreeBtnOnMD;
		//m_pMoreView = new GxxThreeBtnBool(x,y,"M/D","D/M");
		//AddCtrl(m_pMoreView);
		ASSERT(0);
	}
	else if (s == string(TYPE_BTN_ENABLE) || s == string(TYPE_BTN_SELECT))
	{
		m_btnType = TL_LINE_ENABLE;
	}
	else if (s == string(TYPE_BTN_APP_VERSION))
	{
		m_btnType = TL_LINE_VERSION;
		GxxSwText *vtext = new GxxSwText;
		RECT rc = m_ActRect;
		rc.left += 250; 
		vtext->setCtrRect(rc);
		vtext->setFormat(DT_VCENTER|DT_LEFT);
		vtext->setTextFont(0xffffffff,26);	
		//APPVersion(vtext);
		m_pMoreView  = vtext;
		AddCtrl(m_pMoreView);
	}
	else if (s == string(TYPE_SETUP_CHOOSE_BTN))
	{
		m_btnType = TL_SetChooseBtn;
		m_pMoreView = new GxxSetupChooseBtn(x,y,getCtrName());
		AddCtrl(m_pMoreView);
		if (m_clickType!=T_None)
		{
			m_pMoreView->setMoveRect(-60,0);
		}
	}
	else if (s == string(TYPE_SETUP_CHOOSE_BTN_SWITCH))
	{
		m_btnType = TL_SetChooseBtn_Switch;
		m_pMoreView = new GxxSetupChooseBtn(x,y,getCtrName());
		AddCtrl(m_pMoreView);
	}
	else if (s == string("GxxDefeat"))
	{
		m_btnType = TL_DEFEAT;
	}
	else
	{
		m_btnType = TL_None;
	}

}

void GxxSetupListLine::APPVersion( GxxSwText *v )
{
	TCHAR sModuleFile[MAX_PATH];
	GetModuleFileName(NULL, sModuleFile, MAX_PATH);
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(sModuleFile, &fd);
	FindClose(hFind);
	SYSTEMTIME st;
	FileTimeToSystemTime(&fd.ftLastWriteTime, &st);

	

	v->setText( StrHelp::FormatToString("%d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond) );
}


void GxxSetupListLine::TimerTick( UINT nIDEvent )
{
	if (m_aboutTimerId == nIDEvent)
	{
		m_aboutBtnDown = false;
		StopTimer(m_aboutTimerId);
		saftGetParentView()->saftGetParentView()->TranslateMessage( CTR_LISTLINE_MES, (WPARAM)this, m_index );//直接发送到gruop
	}
}


BOOL GxxSetupListLine::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	if (T_ListBoxAboutMore == m_clickType)
	{
		switch( nMsg )
		{
		case WM_LBUTTONDOWN: 
			if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
			{	
				if (m_ActRect.right-LOWORD( lParam ) > 500)//只有点击左边才有效果
				{
					StartTimer(m_aboutTimerId);
					m_aboutBtnDown = true;
				}
				return TRUE;//
			}
			return FALSE;
		//case WM_MOUSEMOVE:
		//	if (m_aboutBtnDown)
		//	{
		//		if ( !InMyArea( LOWORD( lParam ), HIWORD( lParam )) )
		//		{
		//			m_aboutBtnDown = false;
		//			StopTimer(m_aboutTimerId);
		//		}
		//		return TRUE;//
		//	}
		//	return FALSE;
		case WM_LBUTTONUP://
			if(m_aboutBtnDown )
			{
				m_aboutBtnDown = false;
				StopTimer(m_aboutTimerId);
				return TRUE;

			}
			return FALSE;
		default:
			return FALSE;
		}
	}
	else if (nMsg==MES_CHOOSE_BTN_DISABLE)
	{
		m_pTextTitle->setColor(0xff444444);
		setEnable(false);
	}
	else if (nMsg==CTR_LISTLINE_ENABLE)
	{
		SetLineDraw( bool(wParam));
		return FALSE;
	}
	else if (nMsg == CTR_DEFEAT_ENABLE)
	{
		if (m_btnType == TL_DEFEAT)
		{
			SetLineEnable(!bool(wParam));
			invalidateRect();
		}
		return FALSE;
	}
	else
	{
		return GxxLBLine::Response(nMsg,wParam,lParam);
	}
	return TRUE;
}

void GxxSetupListLine::SetLineDraw( bool b )
{
	if (m_btnType != TL_SetChooseBtn_Switch)
	{
		if (b)
		{
			setDraw(true);
			//if (m_btnType == TL_None && m_clickType == T_None)
			//{
			//	m_pTextTitle->setColor(0xff444444);
			//	setEnable(false);
			//}
			//else
			//{
			//	m_pTextTitle->setColor(0xffffffff);
			//	setEnable(true);
			//}

		}
		else
		{
			setDraw(false);
			//m_pTextTitle->setColor(0xff444444);
			//setEnable(false);
		}
		AfxInvalidateRect(&m_ActRect);
	}
}


void GxxSetupListLine::setIconMore()
{
	ASSERT(NULL == m_pPicIcon);
	m_pPicIcon = new GxxPicture;
	AddCtrl(m_pPicIcon);
	if (m_pPicIcon->setPicHandle(ResStringManager::GetInstance()->getString("ListIconMore")))
	{
		int w = m_pPicIcon->getPicWidth();
		int h = m_pPicIcon->getPicHeight();
		int d =  ((m_ActRect.bottom-m_ActRect.top)-h)/2;
		RECT rect;
		::SetRect(&rect,m_ActRect.right-w, m_ActRect.top+d,  m_ActRect.right, m_ActRect.top+d+h);
		m_pPicIcon->setCtrRect(rect);
		m_pPicIcon->bindHandleRect();
	}
}

void GxxSetupListLine::SetLineEnable( bool b )
{

	if (b)
	{
		m_pTextTitle->setColor(0xffffffff);
		setEnable(true);
	}
	else
	{

		m_pTextTitle->setColor(0xff444444);
		setEnable(false);
	}
}
