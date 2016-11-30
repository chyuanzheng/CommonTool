#include "StdAfx.h"
#include "GxxRationPage.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"

#define  LEN_TWO   20

static RegisterHelp help("GxxRationPage", GxxRationPage::CreateControl);
GxxView* GxxRationPage::CreateControl()
{
	return new GxxRationPage;
}


GxxRationPage::GxxRationPage()
{
	m_curIcon = new GxxPicture;
	m_norIcon = new GxxPicture;
}

GxxRationPage::~GxxRationPage()
{
}



void GxxRationPage::Draw(  )
{

	
	for (int i = 0; i< m_tv_rect.size();i++)
	{
		if (i == m_pos)
		{
			m_curIcon->DrawPicWithRect(m_tv_rect[i]);
		}
		else
		{
			m_norIcon->DrawPicWithRect(m_tv_rect[i]);
		}
	}
}

void GxxRationPage::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	setCtrRect(ele);

	bool b1 = m_curIcon->setPicHandle(ele,BTN_UP);
	bool b2 = m_norIcon->setPicHandle(ele,BTN_DISABLE);
	ASSERT(b1&&b2);

	m_iconWidth = m_curIcon->getPicWidth();
	m_iconHeight = m_curIcon->getPicHeight();

	m_iconTop = m_ActRect.top + (m_ActRect.bottom - m_ActRect.top - m_iconHeight)/2;

}

void GxxRationPage::setRation( int pos, int sun )
{
	ASSERT(sun <= 4 && sun > 0 && pos <= sun && pos >=0);
	m_pos = pos;
	
	int w = m_ActRect.right -m_ActRect.left;
	int s_x = (w - (LEN_TWO + m_iconWidth)*sun + LEN_TWO)/2;
	s_x += m_ActRect.left;

	m_tv_rect.clear();
	RECT rc;
	for (int i=0; i<sun; i++)
	{
		SetRect(&rc,s_x,m_iconTop,s_x+m_iconWidth,m_iconTop+m_iconHeight);
		s_x += LEN_TWO + m_iconWidth;
		m_tv_rect.push_back(rc);
	}

	AfxInvalidateRect(&m_ActRect);
}
