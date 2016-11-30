#include "StdAfx.h"
#include "GxxRecordListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxView.h"
#include "GxxAniLable.h"
#include "GxxProgressV.h"
#include "GxxRecordLBList.h"
#include "GxxRecordListLine.h"
#include "GxxListPercent.h"

//
//#include "aygshell.h"
#define  PercentLineMin 60
//#include "aygshell.h"
static RegisterHelp help("GxxRecordListGroup", GxxRecordListGroup::CreateControl);
GxxView* GxxRecordListGroup::CreateControl()
{
	return new GxxRecordListGroup;
}
GxxRecordListGroup::GxxRecordListGroup()
{

	m_lableOutCall = NULL;
	m_lableInCall = NULL;
	m_lableMissCall = NULL;
	m_curOutCall =  new GxxRecordLBList;
	m_curInCall  =  new GxxRecordLBList;
	m_curMissCall  =  new GxxRecordLBList;



	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

}


//恢复出厂设置
LRESULT GxxRecordListGroup::RestoreDefault(DWORD param1, DWORD param2)
{
	m_curOutCall->deleteAllCtrls();
	m_curInCall->deleteAllCtrls();
	m_curMissCall->deleteAllCtrls();
	removeCtrl(m_curListBox);
	InitList();
	return 0;
}
GxxRecordListGroup::~GxxRecordListGroup()
{
	
}

bool GxxRecordListGroup::GetSelected( RecordItem & item )
{
	if (m_select_line!=NULL)
	{
		item.iId = m_select_line->getIndex();
		item.cPhoneNum = m_select_line->getLineName();
		item.date = m_select_line->getDate();
		item.eRecordType = m_select_line->getRecordType();
		item.cPerson = m_select_line->getPerson();
		return true;
	}
	return false;
}

void GxxRecordListGroup::DeleteAllItem()
{
	m_curOutCall->deleteAllCtrls();
	m_curInCall->deleteAllCtrls();
	m_curMissCall->deleteAllCtrls();
	ResetList();
}




bool GxxRecordListGroup::AddItem( const RecordItem& item, bool toBack /*= true*/  )
{
	GxxRecordLBList * rList = NULL;
	switch (item.eRecordType)
	{
	case  RecordItem::OUTCALL:
		rList = m_curOutCall;
		break;
	case  RecordItem::INCALL:
		rList = m_curInCall;
		break;
	case RecordItem::CALLMISS:
		rList = m_curMissCall;
		break;

	default:
		break;

	}
	if (rList)
	{
		rList->AddRecord(item.iId,item.cPhoneNum,item.eRecordType,item.date, item.cPerson,toBack);
		return true;
	}
	//((GxxRecordLBList *)m_curListBox)->AddRecord(item.iId,item.cPhoneNum,item.eRecordType,item.date);
	ASSERT(0);
	return false;
}




void GxxRecordListGroup::ResetList()
{
	m_curListBox->CaculateRation(false);
	m_curListBox->invalidateRect();
	m_percentBtn->setDraw(m_curListBox->getCtrlsSize()>PercentLineMin);
	m_percentBtn->invalidateRect();


	m_deleteAll->setEnable( (m_curOutCall->getCtrlsSize() + m_curInCall->getCtrlsSize() + m_curMissCall->getCtrlsSize()) >0);
}



BOOL GxxRecordListGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
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
			if ((GxxAniLable *)wParam == m_lableOutCall)
			{
				SetCallList(RecordItem::OUTCALL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_lableInCall)
			{
				SetCallList(RecordItem::INCALL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_lableMissCall)
			{
				SetCallList(RecordItem::CALLMISS);
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

void GxxRecordListGroup::setCtrLayout( TiXmlElement * ele )
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
	m_deleteAll->setEnable(false);

	m_lableOutCall = (GxxAniLable *)safeFindViewByName("Label_outcall");;
	m_lableInCall = (GxxAniLable *)safeFindViewByName("Label_incall");;
	m_lableMissCall = (GxxAniLable *)safeFindViewByName("Label_misscall");;


	InitList();

	ASSERT(m_btnBack!=NULL );

}



void GxxRecordListGroup::LineBtnDown( WPARAM wParam, LPARAM lParam )
{

	m_select_line = (GxxRecordListLine *)wParam;
	AfxSendMessage( CTR_LISTBOX_MES, (WPARAM)this, lParam );
	m_select_line = NULL;

}

void GxxRecordListGroup::SetCallList( RecordItem::RecordType type )
{
	if (m_callType == type)
	{
		return;
	}
	m_callType = type;

	m_lableOutCall->SetSelect(false);
	m_lableInCall->SetSelect(false);
	m_lableMissCall->SetSelect(false);

	removeCtrl(m_curListBox);
	switch (m_callType)
	{
	case  RecordItem::OUTCALL:
		m_curListBox = m_curOutCall;
		m_lableOutCall->SetSelect(true);
		break;
	case  RecordItem::INCALL:
		m_curListBox = m_curInCall;
		m_lableInCall->SetSelect(true);
		break;
	case RecordItem::CALLMISS:
		m_curListBox = m_curMissCall;
		m_lableMissCall->SetSelect(true);
		break;

	default:
		ASSERT(0);
		break;

	}
	m_curListBox->setParentView(this);
	m_pCtrlVet->push_front(m_curListBox);
	
	ResetList();
	AfxInvalidateRect(NULL);
}

void GxxRecordListGroup::InitList()
{
	m_curListBox =  m_curOutCall;
	m_callType = RecordItem::OUTCALL;//首先是去电

	m_curListBox->setParentView(this);
	m_pCtrlVet->push_front(m_curListBox);

	m_lableOutCall->SetSelect(true);
	m_lableInCall->SetSelect(false);
	m_lableMissCall->SetSelect(false);

	ResetList();
}


