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
		AfxSendMessage(CTR_SETUP_START_LISTBOX,WPARAM(sline->getClickName().c_str()),LPARAM(1));//1��ʾ���½���
	}
	else if (sline->getClickType() == GxxSetupListLine::T_ListBoxAboutMore)
	{
		//if (GetTickCount()-m_downTime > 4000)
		//{
			AfxSendMessage(CTR_SETUP_START_LISTBOX,WPARAM(sline->getClickName().c_str()),LPARAM(1));//1��ʾ���½���
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

//���ﲢ����GxxLBList�����ӿؼ����������㶯̬�����ض���GxxLBList��
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
//bReturn = 0��ʾ��һ�ν���setup
//bReturn = 1��ʾ��һ���Ժ���벻ͬ��setup
//bReturn = 2��ʾsetup����
/* ���õ�ǰ��       GxxLBList                                         */
/************************************************************************/
void GxxSetupListGroup::setActiveListBox( const string & listname,int isReStart )
{
	removeCtrl(m_curListBox);

	GxxLBList* preListBox=m_curListBox;//��סǰһ���Ա㷵��;
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
	//����Ҫ�� GxxLBList ��Ӧ��Xml�ļ� m_curListBox.open();

	
	CacuViewSatus();
}

void GxxSetupListGroup::finish()
{
	GxxLBList *preListBox = m_curListBox->getPreListBox();
	if (NULL != preListBox)
	{
		AfxSendMessage(CTR_SETUP_START_LISTBOX,WPARAM(preListBox->getCtrName().c_str()),LPARAM(2));//2��ʾfinish
	}
	else
	{
		AfxSendMessage(CTR_LIST_BACK_ACTIVITY,0,0);//������ҳ��
	}
}

GxxView * GxxSetupListGroup::S_FindList(const string & str )
{
	TMap_ListBox::iterator pos  = s_allListBox.find(str);
	ASSERT(s_allListBox.end()!=pos);
	return pos->second;// m_allListBox[listname];
}


