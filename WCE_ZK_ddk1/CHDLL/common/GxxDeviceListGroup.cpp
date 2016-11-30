#include "StdAfx.h"
#include "GxxDeviceListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxView.h"
#include "GxxAniLable.h"
#include "GxxProgressV.h"
#include "GxxDeviceLBList.h"
#include "GxxDeviceListLine.h"
#include "GxxListPercent.h"
#define  PercentLineMin 60
//
//#include "aygshell.h"
static RegisterHelp help("GxxDeviceListGroup", GxxDeviceListGroup::CreateControl);
GxxView* GxxDeviceListGroup::CreateControl()
{
	return new GxxDeviceListGroup;
}
GxxDeviceListGroup::GxxDeviceListGroup()
{
	m_curListBox =  new GxxDeviceLBList;
	AddCtrl(m_curListBox);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

}


//»Ö¸´³ö³§ÉèÖÃ
LRESULT GxxDeviceListGroup::RestoreDefault(DWORD param1, DWORD param2)
{
	DeleteAllItem();
	return 0;
}
GxxDeviceListGroup::~GxxDeviceListGroup()
{
	
}


bool GxxDeviceListGroup::SetDeviceStatus( int iItemID, DeviceItem::DeviceStatus ds )
{
	return ((GxxDeviceLBList *)m_curListBox)->SetDeviceStatus(iItemID,ds);
}


bool GxxDeviceListGroup::GetSelected( DeviceItem & item )
{
	if (m_select_line!=NULL)
	{
		item.iId = m_select_line->getIndex();
		item.strDeviceName = m_select_line->getLineName();
		item.eDeviceStatus = m_select_line->getStatus();
		return true;
	}
	return false;
}

void GxxDeviceListGroup::DeleteAllItem()
{
	m_curListBox->deleteAllCtrls();
	ResetList();
}

int GxxDeviceListGroup::GetAllItemCount()
{
	return m_curListBox->getCtrlsSize();
}

bool GxxDeviceListGroup::AddItem( const DeviceItem& item )
{
	((GxxDeviceLBList *)m_curListBox)->AddDevice(item.iId,item.strDeviceName,item.eDeviceStatus);
	return true;
}

bool GxxDeviceListGroup::DeleteItem( int iItemId )
{
	((GxxDeviceLBList *)m_curListBox)->DeleteItem(iItemId);
	return true;
}

void GxxDeviceListGroup::ResetList()
{
	m_curListBox->CaculateRation(false);
	m_curListBox->invalidateRect();
	m_percentBtn->setDraw(m_curListBox->getCtrlsSize()>PercentLineMin);
	m_percentBtn->invalidateRect();
	m_deleteAll->setEnable(m_curListBox->getCtrlsSize()>0);
}



BOOL GxxDeviceListGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
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

void GxxDeviceListGroup::setCtrLayout( TiXmlElement * ele )
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
	ASSERT(m_btnBack!=NULL );

}



void GxxDeviceListGroup::LineBtnDown( WPARAM wParam, LPARAM lParam )
{

	m_select_line = (GxxDeviceListLine *)wParam;
	AfxSendMessage( CTR_LISTBOX_MES, (WPARAM)this, lParam );
	m_select_line = NULL;

}

