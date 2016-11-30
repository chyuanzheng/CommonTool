#include "StdAfx.h"
#include "GxxSelectLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxSetupListLine.h"

#include "LangStringManager.h"

GxxSelectLBList::GxxSelectLBList()
{
	m_nSelNth = -1;
	m_selPic = new GxxPicture;
	m_selPic->setDraw(false);
	
}

GxxSelectLBList::~GxxSelectLBList()
{
	delete m_selPic;
}


void GxxSelectLBList::setCtrLayout( TiXmlElement * ele )
{
	SetNameTitle(ele);	
	setCtrRect(ele);

	//select_pic


	TiXmlElement * chid = ele->FirstChildElement();
	//setCtrList(chid);//设定每一行
	string ctrname;


	while(chid)
	{
		GxxSetupListLine *ctr=NULL;

		ctrname = chid->Value();
		ASSERT(ctrname == "GxxListLine");
		ctr = new GxxSetupListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
		AddCtrl(ctr);
		ctr->setLineLayout(getCtrlsSize()-1,chid);

		chid = chid->NextSiblingElement();
	}
	CaculateRation(false);

	m_selPic->setPicHandle(ele,SELECT_PICTURE);
	//m_selPic->setHandleAlpha(130);
	//int nsize= getCtrlsSize();

}

bool GxxSelectLBList::SetLineChoosed( int nlan,bool showSel/*=false */ )
{
	m_nSelNth=nlan;
	if (m_nSelNth < 0 || m_nSelNth >= getCtrlsSize())
	{
		m_nSelNth = -1;
		m_selPic->setDraw(false);
		return false;
	}
	m_selPic->setDraw(true);
	if (showSel)
	{
		MoveToLine(m_nSelNth);
	}
	return true;
}



GxxSetupListLine * GxxSelectLBList::GetNthLine( int nlan )
{
	GxxSetupListLine *chLine = NULL;
	ControlList::iterator pos;
	int i =0;
	for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++,i++)
	{
		if (i == nlan)
		{
			chLine = (GxxSetupListLine*)(*pos) ;
			break;
		}
	}
	ASSERT(chLine != NULL);
	return chLine;
}


void GxxSelectLBList::Draw()
{
	
	if (!m_selPic->getDraw())
	{
		return;
	}
	
	int n =  GxxLBLine:: S_nlineHeight*m_nSelNth+getHaveMove();
	RECT rc;
	::SetRect(&rc,m_ActRect.left, m_ActRect.top+n,  m_ActRect.right, m_ActRect.top+n+GxxLBLine:: S_nlineHeight);
	m_selPic->DrawPicWithRect(rc);
}

void GxxSelectLBList::onMoveRect( int x_len, int y_len )
{
	m_selPic->setMoveRect(x_len,y_len);
}

BOOL GxxSelectLBList::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message<WM_USER)
	{
		return GxxLBList::DealCtrlMsg(message,wParam,lParam);
	}
	return GxxView::DealCtrlMsg(message,wParam,lParam);
}

int GxxSelectLBList::GetViewIndex( GxxView * vline )
{
	ControlList::iterator pos;
	int index = 0;
	for (pos = m_pCtrlVet->begin(); pos != m_pCtrlVet->end(); ++pos)
	{
		if ( *pos == vline)
		{
			break;
		}
		index++;
	}
	ASSERT(pos != m_pCtrlVet->end());
	return index;
}
