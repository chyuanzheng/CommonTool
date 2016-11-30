#include "StdAfx.h"
#include "GxxSetupLBList.h"
#include "GxxSetupListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxSetupListLine.h"
#include "GxxSwText.h"
//
//#include "aygshell.h"
GxxLBList* GxxSetupListGroup::S_curList = NULL;
TMap_ListBox  GxxSetupListGroup::s_allListBox;
static RegisterHelp help("GxxSetupListGroup", GxxSetupListGroup::CreateControl);
GxxView* GxxSetupListGroup::CreateControl()
{
	return new GxxSetupListGroup;
}
GxxSetupListGroup::GxxSetupListGroup()
{
}

GxxSetupListGroup::~GxxSetupListGroup()
{

}


BOOL GxxSetupListGroup::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{

	if (message == WM_LBUTTONDOWN)
	{
		m_downTime = GetTickCount();
	}
	return GxxListGroupBase::DealCtrlMsg(message,wParam,lParam);
}

BOOL GxxSetupListGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			//if ((GxxView *)wParam == m_btx)
			//{
			//	AfxSendMessage(CTR_FUC_ACTIVITY,0,0);
			//	return TRUE;
			//}
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


void GxxSetupListGroup::LineBtnDown( WPARAM wParam, LPARAM lParam )
{
	
	GxxSetupListLine *sline = (GxxSetupListLine *)wParam;
	if (sline->getClickType() == GxxSetupListLine::T_ListBox)
	{
		//setActiveListBox(sline->getClickName());
		AfxSendMessage(CTR_SETUP_START_LISTBOX,WPARAM(sline->getClickName().c_str()),LPARAM(1));//1表示按下进入
	}
	else if (sline->getClickType() == GxxSetupListLine::T_ListBoxAboutMore)
	{
		//if (GetTickCount()-m_downTime > 4000)
		//{
			AfxSendMessage(CTR_SETUP_START_LISTBOX,WPARAM(sline->getClickName().c_str()),LPARAM(1));//1表示按下进入
		//}
	}
	else if ( sline->getClickType() == GxxSetupListLine::T_Activity )
	{
		AfxSendMessage(CTR_SETUP_START_ACTIVITY,WPARAM(sline->getClickName().c_str()),NULL);
	}
	else if ( sline->getClickType() == GxxSetupListLine::T_Massage )
	{
		AfxSendMessage(CTR_SETUP_START_MASSAGE,WPARAM(sline->getClickName().c_str()),NULL);
	}
}


void GxxSetupListGroup::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);
	TiXmlElement * chid = ele->FirstChildElement();
	setListBoxList(chid);
}

//这里并不把GxxLBList加入子控件，这样方便动态加入特定的GxxLBList；
void GxxSetupListGroup::setListBoxList( TiXmlElement * ele )
{
	string ctrname;

	while(ele)
	{
		GxxView *ctr=NULL;
		ctrname = ele->Value();
		if(ctrname == "GxxListBox")
		{
			ctr = new GxxSetupLBList;//GXCreateControl::CreateControlByType(ctrname.c_str());
			ctr->setCtrLayout(ele);
			s_allListBox.insert( make_pair(ctr->getCtrName(),(GxxSetupLBList*)ctr) );
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
	ASSERT(s_allListBox.size()>0);
}

/************************************************************************/
//bReturn = 0表示第一次进入setup
//bReturn = 1表示第一次以后进入不同的setup
//bReturn = 2表示setup回退
/* 设置当前的       GxxLBList                                         */
/************************************************************************/
void GxxSetupListGroup::setActiveListBox( const string & listname,int isReStart )
{
	removeCtrl(m_curListBox);

	GxxLBList* preListBox=m_curListBox;//记住前一个以便返回;
	TMap_ListBox::iterator pos  = s_allListBox.find(listname);
	ASSERT(s_allListBox.end()!=pos);
	m_curListBox = pos->second;// m_allListBox[listname];
	AddCtrl(m_curListBox);
	S_curList = m_curListBox;

	if (isReStart==1)
	{
		m_curListBox->setPreListBox(preListBox);
	}
	else if (isReStart == 0)
	{
		m_curListBox->setPreListBox(NULL);
	}
	else if (isReStart == 2)
	{
	}

	

	
	m_curListBox->ResetPosition();

	if (NULL != m_curListBox->getTitleFromID())
	{
		m_titleText->setText(m_curListBox->getTitleFromID());
	}
	else
	{
		m_titleText->setText(m_curListBox->getTitle().c_str());
	}
	AfxInvalidateRect(NULL);
	//这里要打开 GxxLBList 对应的Xml文件 m_curListBox.open();

	
	CacuViewSatus();
}

void GxxSetupListGroup::finish()
{
	GxxLBList *preListBox = m_curListBox->getPreListBox();
	if (NULL != preListBox)
	{
		AfxSendMessage(CTR_SETUP_START_LISTBOX,WPARAM(preListBox->getCtrName().c_str()),LPARAM(2));//2表示finish
	}
	else
	{
		AfxSendMessage(CTR_LIST_BACK_ACTIVITY,0,0);//返回主页面
	}
}

GxxView * GxxSetupListGroup::S_FindList(const string & str )
{
	TMap_ListBox::iterator pos  = s_allListBox.find(str);
	ASSERT(s_allListBox.end()!=pos);
	return pos->second;// m_allListBox[listname];
}


