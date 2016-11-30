#include "StdAfx.h"
#include "GxxPhoneListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxView.h"
#include "GxxAniLable.h"
#include "GxxProgressV.h"
#include "GxxPhoneLBList.h"
#include "GxxPhoneListLine.h"
#include "GxxListPercent.h"

//
//#include "aygshell.h"
#define  PercentLineMin 60

static RegisterHelp help("GxxPhoneListGroup", GxxPhoneListGroup::CreateControl);
GxxView* GxxPhoneListGroup::CreateControl()
{
	return new GxxPhoneListGroup;
}
GxxPhoneListGroup::GxxPhoneListGroup()
{
	m_curListBox =  new GxxPhoneLBList;
	AddCtrl(m_curListBox);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

}


//»Ö¸´³ö³§ÉèÖÃ
LRESULT GxxPhoneListGroup::RestoreDefault(DWORD param1, DWORD param2)
{
	DeleteAllItem();
	//ResetList();
	return 0;
}

GxxPhoneListGroup::~GxxPhoneListGroup()
{
	
}

bool GxxPhoneListGroup::GetSelected( PhoneItem & item )
{
	if (m_select_line!=NULL)
	{
		item.iId = m_select_line->getIndex();
		item.strName = m_select_line->getLineName();
		return true;
	}
	return false;
}

void GxxPhoneListGroup::DeleteAllItem()
{
	m_curListBox->deleteAllCtrls();
	ResetList();
}

int GxxPhoneListGroup::GetAllItemCount()
{
	return m_curListBox->getCtrlsSize();
}

bool GxxPhoneListGroup::AddItem( const PhoneItem& item )
{
	((GxxPhoneLBList *)m_curListBox)->AddPhone(item.iId,item.strName,item.cPhoneNum);
	return true;
}

bool GxxPhoneListGroup::DeleteItem( int iItemId )
{
	((GxxPhoneLBList *)m_curListBox)->DeleteItem(iItemId);
	return true;
}

void GxxPhoneListGroup::ResetList()
{
	m_curListBox->CaculateRation(false);
	m_curListBox->invalidateRect();

	m_percentBtn->setDraw(m_curListBox->getCtrlsSize()>PercentLineMin);
	m_percentBtn->invalidateRect();
	m_deleteAll->setEnable(m_curListBox->getCtrlsSize()>0);
}



BOOL GxxPhoneListGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			//if ((GxxView *)wParam == m_btx)
			//{
			//	AfxPostMessage(CTR_LISTBOX_X, (WPARAM)this, 0 );
			//	return TRUE;
			//}
			if ((GxxView *)wParam == m_btnBack)
			{
				AfxPostMessage(CTR_LISTBOX_X, (WPARAM)this, 0 );
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_deleteAll)
			{
				AfxMessageBox("Delete_All_Sure_31",this,0,ZKY_MB_OKCANCEL);
				return TRUE;
			}
		}
		break;
	case CTR_LISTLINE_MES:
		LineBtnDown(wParam, lParam);
		return TRUE;
	case  MES_MSG_CANCEL:
		return TRUE;
	case  MES_MSG_OK:
		DeleteAllItem();
		AfxPostMessage(CTR_DELETE_ALL,(WPARAM)this,0);
		return TRUE;
	default:
		break;
	}
	return GxxListGroupBase::Response(nMsg,wParam,lParam);
}

void GxxPhoneListGroup::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);
	if (setPicHandle(ele,BACKGROUD))
	{
		bindHandleRect();
	}
	
	

	TiXmlElement * chid = ele->FirstChildElement();
	setCtrList(chid);
	FindChildCtrls();

	m_percentBtn = (GxxListPercent *)safeFindViewByName("list_percent");
	m_deleteAll = (GxxAniLable *)safeFindViewByName("List_DeleteAll");
	ASSERT(m_btnBack!=NULL);

}



void GxxPhoneListGroup::LineBtnDown( WPARAM wParam, LPARAM lParam )
{

	m_select_line = (GxxPhoneListLine *)wParam;
	AfxSendMessage( CTR_LISTBOX_MES, (WPARAM)this, lParam );
	m_select_line = NULL;

}

