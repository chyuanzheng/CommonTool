#include "StdAfx.h"
#include "GxxClickProgressBar.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
// back_conver
//#include "aygshell.h"

static RegisterHelp help("GxxClickProgressBar", GxxClickProgressBar::CreateControl);
GxxView* GxxClickProgressBar::CreateControl()
{
	return new GxxClickProgressBar;
}

GxxClickProgressBar::GxxClickProgressBar()
{
	m_mesView = NULL;
	m_bClick = false;
}

GxxClickProgressBar::~GxxClickProgressBar()
{

}

BOOL GxxClickProgressBar::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea(m_clickRect,LOWORD( lParam ), HIWORD( lParam )))
		{
			m_bClick = true;
			SetDisplayX(LOWORD( lParam ));
			return TRUE;
		}
	case  WM_MOUSEMOVE:
		if (m_bClick)
		{
			SetDisplayX(LOWORD( lParam ));
			return TRUE;
		}
	case  WM_LBUTTONUP:
		if (m_bClick)
		{
			m_bClick =false;
			SetDisplayX(LOWORD( lParam ));
			if (m_mesView)
			{
				m_mesView->TranslateMessage(CTR_MESSAGE,WPARAM(this),LPARAM(iPos));
			}
			return TRUE;
		}
	default:
		return FALSE;
	}
	return FALSE;
}

void GxxClickProgressBar::setCtrLayout( TiXmlElement * ele )
{

	GxxProgressBar::setCtrLayout(ele);
	m_clickRect.setLTRB(m_ActRect.left,m_ActRect.top-30,m_ActRect.right,m_ActRect.bottom + 30);
}

void GxxClickProgressBar::SetDisplayPos( int n )
{
	if (!m_bClick)
	{
		return GxxProgressBar::SetDisplayPos(n);
	}
}

void GxxClickProgressBar::SetDisplayX( int xpos )
{
	if (m_clickRect.left > xpos)
	{
		xpos = m_clickRect.left;
	}

	if (m_clickRect.right < xpos)
	{
		xpos = m_clickRect.right;
	}
	GxxProgressBar::SetDisplayPos( (xpos-m_clickRect.left)*iMax/m_clickRect.width() );
	invalidateRect();
}

void GxxClickProgressBar::SetMessageView( GxxView *pView )
{
	m_mesView = pView;
}

