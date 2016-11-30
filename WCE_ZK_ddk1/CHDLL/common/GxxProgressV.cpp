#include "StdAfx.h"
#include "GxxProgressV.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
//
//#include "aygshell.h"
static RegisterHelp help("GxxProgressV", GxxProgressV::CreateControl);
GxxView* GxxProgressV::CreateControl()
{
	return new GxxProgressV;
}

GxxProgressV::GxxProgressV()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_pPicUp = new GxxPicture;
	m_pPicProgress = new GxxPicture;
	m_pPicBack = new GxxPicture;
	m_isHorizon = false;

	m_pPicProgress->setOnlyDrawActRect(true);
	AddCtrl(m_pPicProgress);
	AddCtrl(m_pPicUp);
	
}

GxxProgressV::~GxxProgressV()
{

	delete m_pPicUp;
	delete m_pPicProgress;
	delete m_pPicBack;

}



void GxxProgressV::Draw(  )
{
	//被按下为真

}


BOOL GxxProgressV::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;
	return FALSE;
}

void GxxProgressV::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	

	const char* pa = ele->Attribute(PROGRESS_HORIZON);
	if (pa!=NULL)
	{
		if ( StrHelp::StringEqual( string(pa),string("true") ) )
		{
			m_isHorizon = true;
		}
	}


	pa = ele->Attribute(UP_BMP);
	ASSERT(pa);
	if (m_pPicUp->setPicHandle(pa))
	{
		setCtrRectUseCenter(ele,m_pPicUp->getPicWidth(),m_pPicUp->getPicHeight());
		m_pPicUp->setCtrRect(m_ActRect);
		m_pPicUp->bindHandleRect();
		
	}
	else
	{
		ASSERT(0);
	}


	pa = ele->Attribute(BACK_BMP);
	if (m_pPicBack->setPicHandle(pa))
	{
		m_pPicBack->setCtrRect(m_ActRect);
		m_pPicBack->bindHandleRect();
		AddCtrl(m_pPicBack,m_pPicProgress);
	}


	pa = ele->Attribute(PROGRESS_BMP);
	ASSERT(pa);
	m_pPicProgress->setPicHandle(pa);
	m_pPicProgress->setCtrRect(m_ActRect);
	m_pPicProgress->bindHandleRect();



	SetProgress(0.0,1.0);	
}

#define  Min_Len  5
void GxxProgressV::SetProgress( float fs, float fe )
{
	m_fstart = fs;
	m_fend  = fe; 
	ASSERT( 1.0>=fe&& fe>=fs &&fs>=0.0 );
	RECT rect;
	if (m_isHorizon)
	{
		::SetRect(&rect,m_ActRect.left+ int((m_ActRect.right - m_ActRect.left)*fs),m_ActRect.top, m_ActRect.left+int((m_ActRect.right - m_ActRect.left)*fe), m_ActRect.bottom);
	}
	else
	{
		::SetRect(&rect,m_ActRect.left,m_ActRect.top+ int((m_ActRect.bottom - m_ActRect.top)*fs), m_ActRect.right, m_ActRect.top+ int((m_ActRect.bottom - m_ActRect.top)*fe));
	}

	if (fe-fs>0.0001)
	{
		if (m_isHorizon)
		{
			int len = rect.right - rect.left;
			int mid = (rect.right + rect.left)/2;
			if (len < Min_Len*2)
			{
				rect.left = mid-Min_Len ;
				rect.right = mid+Min_Len;
				int  overlen = m_ActRect.left - rect.left;
				int  overlen_2 = m_ActRect.right - rect.right;
				if (overlen > 0)
				{
					rect.left += overlen;
					rect.right += overlen;
				}
				else if (overlen_2<0)
				{
					rect.left += overlen_2;
					rect.right += overlen_2;
				}
			}
		}
		else
		{
			int len = rect.bottom - rect.top;
			int mid = (rect.bottom + rect.top)/2;
			if (len < Min_Len*2)
			{
				rect.top = mid-Min_Len ;
				rect.bottom = mid+Min_Len;	

				int  overlen = m_ActRect.top - rect.top;
				int  overlen_2 = m_ActRect.bottom - rect.bottom;
				if (overlen > 0)
				{
					rect.top += overlen;
					rect.bottom += overlen;
				}
				else if (overlen_2<0)
				{
					rect.top += overlen_2;
					rect.bottom += overlen_2;
				}
			}

		}

	}

	m_pPicProgress->bindHandleRect(m_ActRect);
	m_pPicProgress->setCtrRect(rect);
	AfxInvalidateRect(&m_ActRect);
}


