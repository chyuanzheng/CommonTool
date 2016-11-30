#include "StdAfx.h"
#include "GxxPicLine.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"

#define  S_MAX_LINE            "s_maxline" 
#define  S_LAYOUT_X            "s_layout_x" 
#define  S_LAYOUT_Y            "s_layout_y"
#define  S_LAYOUT_WIDTH        "s_layout_width"
#define  S_LAYOUT_HEIGHT       "s_layout_height"


static RegisterHelp help("GxxPicLine", GxxPicLine::CreateControl);
GxxView* GxxPicLine::CreateControl()
{
	return new GxxPicLine;
}


GxxPicLine::GxxPicLine()
{
	m_pPicBack = new GxxPicture;
	m_pPicPoint = new GxxPicture;
	m_xline = m_yline = -100;
	m_btnDown = false;
	
}

GxxPicLine::~GxxPicLine()
{
	delete m_pPicBack;
	delete m_pPicPoint;
}


void GxxPicLine::Draw(  )
{
	m_pPicBack->DrawPic();
	SkiaBitmapManager::GetInstance()->DrawLine(m_ActShowRect.left,m_y,m_ActShowRect.right,m_y);
	SkiaBitmapManager::GetInstance()->DrawLine(m_x,m_ActShowRect.top,m_x,m_ActShowRect.bottom);
	m_pPicPoint->DrawPic();

}

void GxxPicLine::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	setCtrRect(ele);

	setShowRect(ele);
	ASSERT( (m_ActShowRect.right - m_ActShowRect.left) == (m_ActShowRect.bottom - m_ActShowRect.top) );

	m_nMaxLine=0;
	ele->Attribute(S_MAX_LINE,&m_nMaxLine);
	ASSERT(m_nMaxLine>0);
	m_nLineInterval = (m_ActShowRect.right - m_ActShowRect.left)/(m_nMaxLine*2);
	
	if (m_pPicBack->setPicHandle(ele,BTN_UP))
	{
		m_pPicBack->setCtrRect(m_ActRect);
		m_pPicBack->bindHandleRect();//
	}

	if (!m_pPicPoint->setPicHandle(ele,BTN_POINT))
	{
		ASSERT(0);
	}
}

BOOL GxxPicLine::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	RECT rcClick;
	int half_len = m_nLineInterval/2;
	SetRect(&rcClick,m_ActShowRect.left-half_len, m_ActShowRect.top-half_len, m_ActShowRect.right+half_len, m_ActShowRect.bottom+half_len);
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea(rcClick,LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			CaculatePoint( LOWORD( lParam ), HIWORD( lParam ) );
			m_btnDown = true;
			return TRUE;
		}
		return FALSE;
	case  WM_MOUSEMOVE:
		if (m_btnDown )
		{
			if ( InMyArea(rcClick,LOWORD( lParam ), HIWORD( lParam )) )
			{
				CaculatePoint( LOWORD( lParam ), HIWORD( lParam ) );
			}
			return TRUE;
		}
		return FALSE;
	case  WM_LBUTTONUP:
		if (m_btnDown)
		{
			if ( InMyArea(rcClick,LOWORD( lParam ), HIWORD( lParam )) )
			{
				CaculatePoint( LOWORD( lParam ), HIWORD( lParam ) );
			}
			m_btnDown = false;
			return TRUE;
		}
		return FALSE;
	default:
		return FALSE;
	}
	return FALSE;
}

void GxxPicLine::CaculatePoint( int x,int y )
{
	int xline = (x-m_ActShowRect.left)/m_nLineInterval;

	int nmore = (x-m_ActShowRect.left)%m_nLineInterval;

	if (nmore > m_nLineInterval/2)
	{
		xline++;
	}

	if (xline > m_nMaxLine*2)
	{
		xline =m_nMaxLine*2;
	}


	int yline = (y-m_ActShowRect.top)/m_nLineInterval;
	nmore = (y-m_ActShowRect.top)%m_nLineInterval;
	if (nmore > m_nLineInterval/2)
	{
		yline++;
	}

	if (yline > m_nMaxLine*2)
	{
		yline =m_nMaxLine*2;
	}
	if (m_xline ==xline && m_yline == yline)
	{
		return;
	}
	m_xline = xline;
	m_yline = yline;
	InvalidateLine();

	
	
}

void GxxPicLine::SetFront()
{
	m_yline--;
	InvalidateLine();
}
void GxxPicLine::SetRear()
{
	m_yline++;
	InvalidateLine();
}

void GxxPicLine::SetLeft()
{
	m_xline--;
	InvalidateLine();
}

void GxxPicLine::SetRight()
{
	m_xline++;
	InvalidateLine();
}


void GxxPicLine::SetPoint( int xline,int yline )
{
	m_xline = m_nMaxLine + xline;
	m_yline =  m_nMaxLine -yline;

	InvalidateLine();
}

void GxxPicLine::GetPoint( int &xline,int &yline )
{

	xline = m_xline-m_nMaxLine;
	yline = m_nMaxLine -m_yline;

}


bool GxxPicLine::setShowRect( TiXmlElement * ele )
{
	int data =0;

	const char * c = ele->Attribute(S_LAYOUT_X,&data);
	ASSERT (NULL != c);
	m_ActShowRect.left = data;

	c = ele->Attribute(S_LAYOUT_Y,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActShowRect.top =  data;

	c = ele->Attribute(S_LAYOUT_WIDTH,&data);
	ASSERT (NULL != c);
	m_ActShowRect.right =  data + m_ActShowRect.left;

	c = ele->Attribute(S_LAYOUT_HEIGHT,&data);
	ASSERT (NULL != c);
	m_ActShowRect.bottom =  data + m_ActShowRect.top;

	return true;
}




void GxxPicLine::InvalidateLine()
{
	m_x = m_ActShowRect.left + m_xline*m_nLineInterval;
	m_y = m_ActShowRect.top + m_yline*m_nLineInterval;

	m_pPicPoint->setCtrRectUseCenter(m_x,m_y,m_pPicPoint->getPicWidth(),m_pPicPoint->getPicHeight());
	m_pPicPoint->bindHandleRect();
	AfxInvalidateRect(&m_ActRect);
	saftGetParentView()->TranslateMessage(CTR_SET_BSF_LINE,0,0);
}

