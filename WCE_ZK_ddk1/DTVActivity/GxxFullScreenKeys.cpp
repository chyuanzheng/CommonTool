#include "StdAfx.h"
#include "XmlDef.h"
//#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxFullScreenKeys.h"
#include "ControlHelp.h"
#include "GxxVedioSetup.h"
#include "GxxFullSKeyBoard.h"
#include "TVCommand.h"

#define  TIMER_LEN   3000
GxxFullScreenKeys::GxxFullScreenKeys()
{
	m_mesView = NULL;
	m_timer_id = RegisterTimer(6000);
}

GxxFullScreenKeys::~GxxFullScreenKeys()
{
	UnRegisterTimer(m_timer_id);
}

void GxxFullScreenKeys::SetMessageView( GxxView * mesView )
{
	m_mesView = mesView;
	ASSERT(m_keyBoard);
	m_keyBoard->SetMessageView(m_mesView);
}


void GxxFullScreenKeys::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);

	int iVisible = 1;
	if(ele->Attribute(VISIBLE, &iVisible))	//是否出现控件
	{
		if(iVisible == 0)
		{
			setDraw(FALSE);
		}
	}
	setCtrList( ele->FirstChildElement() );

	m_vedioSetup = (GxxVedioSetup   *)safeFindViewByName("VideoSetup");
	m_keyBoard = (GxxFullSKeyBoard *)safeFindViewByName("group_FullSKeyBoard");
	m_closeBtn = (GxxView *)safeFindViewByName("close_btn");
	m_keyBtn = (GxxView *)safeFindViewByName("key_btn");
	m_setBtn = (GxxView *)safeFindViewByName("set_btn");
	m_leaveBtn = (GxxView *)safeFindViewByName("leave_btn");
	

}

BOOL GxxFullScreenKeys::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_keyBtn)	
			{
				m_keyBoard->setDraw(! m_keyBoard->getDraw() );
				if (m_keyBoard->getDraw())
				{
					m_vedioSetup->setDraw(false);
				}
				AfxInvalidateRect(NULL);
				return TRUE;
			}
			if ((GxxView *)wParam == m_closeBtn)//退出全屏	
			{
				PostDtvMessage(DTV_Quit_FullScreen);
				return TRUE;
			}
			if ((GxxView *)wParam == m_setBtn)	
			{
				m_vedioSetup->setDraw( !m_vedioSetup->getDraw() );
				if (m_vedioSetup->getDraw())
				{
					m_keyBoard->setDraw(false);
				}
				AfxInvalidateRect(NULL);
				return TRUE;
			}
			if ((GxxView *)wParam == m_leaveBtn)	
			{
				PostDtvMessage(DTV_OK);//改成进入
				return TRUE;
			}
		}
	}
	return 0;
}

void GxxFullScreenKeys::PostDtvMessage( UINT msg )
{
	if (m_mesView)
	{
		m_mesView->TranslateMessage(msg,(WPARAM)this,0);
	}
}

GxxView* GxxFullScreenKeys::CreateControl()
{
	return new GxxFullScreenKeys;
}

void GxxFullScreenKeys::ClickWnd()//点击窗口，出现按键
{
	if (!getDraw())
	{
		setDraw(true);
		m_keyBoard->setDraw(true );//点击窗口 即打开小键盘
		m_vedioSetup->setDraw(false);

		AfxInvalidateRect(NULL);
		StartTimer(m_timer_id);
	}
}

void GxxFullScreenKeys::TimerTick( UINT nIDEvent )
{
	if (nIDEvent == m_timer_id)
	{
		StopTimer(m_timer_id);
		setDraw(false);
		AfxInvalidateRect(NULL);
	}
}

void GxxFullScreenKeys::UserClick()//用户点击，持续按键的出现的时间
{
	if (getDraw())
	{
		StartTimer(m_timer_id);
	}
}

void GxxFullScreenKeys::Reset()
{
	StopTimer(m_timer_id);
	setDraw(false);
	m_keyBoard->setDraw(false);
	m_vedioSetup->setDraw(false);
}

void GxxFullScreenKeys::onPause()
{
	Reset();
}

static RegisterHelp help("GxxFullScreenKeys", GxxFullScreenKeys::CreateControl);