#include "StdAfx.h"
#include "GxxSelectLBList.h"
#include "GxxSelectListGroupBase.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxSetupListLine.h"
#include "GxxSwText.h"
//

GxxSelectListGroupBase::GxxSelectListGroupBase()
{

}

GxxSelectListGroupBase::~GxxSelectListGroupBase()
{

}
BOOL GxxSelectListGroupBase::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btnBack)
			{
				finish();
				return TRUE;
			}
		}
		break;
	case CTR_LISTLINE_MES:
		LineBtnDown(wParam, lParam);
		return TRUE;
	default:
		break;
	}
	return GxxListGroupBase::Response(nMsg,wParam,lParam);
}


void GxxSelectListGroupBase::LineBtnDown( WPARAM wParam, LPARAM lParam )
{

	int index = ((GxxSelectLBList *)m_curListBox)->GetViewIndex((GxxView *)wParam );
	bool b = SetSelLine(index);
	ASSERT(b);
}


void GxxSelectListGroupBase::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);
	TiXmlElement * chid = ele->FirstChildElement();
	setListBoxList(chid);
}




//这里并不把GxxLBList加入子控件，这样方便动态加入特定的GxxLBList；
void GxxSelectListGroupBase::setListBoxList( TiXmlElement * ele )
{
	string ctrname;

	ASSERT(NULL==m_curListBox);
	while(ele)
	{
		GxxView *ctr=NULL;
		ctrname = ele->Value();
		

		if(ctrname == "GxxListBox")
		{
			m_curListBox = new GxxSelectLBList;//GXCreateControl::CreateControlByType(ctrname.c_str());
			m_curListBox->setCtrLayout(ele);
			AddCtrl(m_curListBox);
		}
		else 
		{
			if (ctrname == INCLUDE)
			{
				loadXmlView(ele);
				ele = ele->NextSiblingElement();
				continue;
			}
			else
			{
				ctr = GXCreateControl::CreateControlByType(ctrname.c_str());
				AddCtrl(ctr);
				ctr->setCtrLayout(ele);
			}

		}

		ele = ele->NextSiblingElement();
	}

	FindChildCtrls();

	

	ASSERT(NULL!=m_curListBox);
	m_curListBox->ResetPosition();
	if (NULL != m_curListBox->getTitleFromID())
	{
		m_titleText->setText(m_curListBox->getTitleFromID());
	}
	else
	{
		m_titleText->setText(m_curListBox->getTitle().c_str());
	}
	CacuViewSatus();

}

bool GxxSelectListGroupBase::SetSelLine( int nlan,bool showSel/*=false*/  )
{
	if (((GxxSelectLBList *)m_curListBox)->SetLineChoosed(nlan,showSel))
	{
		AfxInvalidateRect(&m_ActRect);
		return true;
	}

	return false;
}

void GxxSelectListGroupBase::finish()
{
	AfxSendMessage(CTR_LIST_BACK_ACTIVITY,0,0);//返回
}


bool GxxSelectListGroupBase::GetSelLine( int &nline )
{
	int n = ((GxxSelectLBList *)m_curListBox)->GetLineChoosed();
	if (n==-1)
	{
		return false;
	}
	nline = n;
	return true;
}




