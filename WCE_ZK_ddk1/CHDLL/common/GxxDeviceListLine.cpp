#include "StdAfx.h"
#include "GxxDeviceListLine.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "GxxAniPictureA.h"
#include "GxxSwText.h"
#include "GxxDelimiter.h"
#include "bluetooth.h"

#include "GxxPicture.h"
#include "GxxAniButton.h"


GxxDeviceListLine::GxxDeviceListLine()
{

	m_pTextTitle = new GxxSwText;
	m_pTextTitle->setFormat(DT_VCENTER|DT_LEFT);
	m_pTextTitle->setTextFont(0xffffffff,26);
	AddCtrl(m_pTextTitle);

	m_btn_Delete = new GxxAniButton;
	m_btn_Connect = new GxxAniButton;
	AddCtrl(m_btn_Delete);
	AddCtrl(m_btn_Connect);
	

	m_text_Delete = new GxxSwText;
	m_text_Connect = new GxxSwText;
	AddCtrl(m_text_Delete);
	AddCtrl(m_text_Connect);

	m_text_Delete->setTextFromId("delete_31");
	m_text_Delete->setTextFont(0xffffffff,24);
	m_text_Connect->setTextFont(0xffffffff,24);
	
}

GxxDeviceListLine::~GxxDeviceListLine()
{
	delete m_pTextTitle;

	delete m_btn_Delete;
	delete m_btn_Connect;
	delete m_text_Delete;
	delete m_text_Connect;


}


void GxxDeviceListLine::setDeviceLine( int index, int top,const wstring& wstr,DeviceItem::DeviceStatus ds )
{
	
	m_index = index;
	RECT p_rect = getParentView()->getCtrRect();
	::SetRect(&m_ActRect,p_rect.left,top,p_rect.right,top +S_nlineHeight);
	//CheckEnable();

	const char *strAni = ResStringManager::GetInstance()->getString("IconDirectAni");
	const char *strDisable = ResStringManager::GetInstance()->getString("IconDirectDisable");
	const char *strPicup = ResStringManager::GetInstance()->getString("IconDirectPicUp");//µ×Í¼


	m_btn_Delete->SetLayout(m_ActRect.left+580, (m_ActRect.bottom+m_ActRect.top)/2,strPicup,NULL,strAni,strDisable);
	m_btn_Connect->SetLayout(m_ActRect.left+490, (m_ActRect.bottom+m_ActRect.top)/2,strPicup,NULL,strAni,strDisable);
	m_text_Delete->setCtrRect(m_btn_Delete->getCtrRect());
	m_text_Connect->setCtrRect(m_btn_Connect->getCtrRect());


	SetDeviceStatus(ds);

	m_pTextTitle->setText(wstr);
	m_pTextTitle->setCtrRect(m_ActRect);

}

BOOL GxxDeviceListLine::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btn_Delete)
			{
				AfxSendMessage(CTR_DEVICE_DELETE, (WPARAM)saftGetParentView()->saftGetParentView(),(LPARAM)getIndex() );
				return TRUE;
			}
			if ((GxxView *)wParam == m_btn_Connect)
			{
				if (m_status==DeviceItem::CONNECTED){
					AfxSendMessage(CTR_DEVICE_CONNECT, (WPARAM)saftGetParentView()->saftGetParentView(),(LPARAM)getIndex() );
				}
				else{
					AfxSendMessage(CTR_DEVICE_DISCONNECT, (WPARAM)saftGetParentView()->saftGetParentView(),(LPARAM)getIndex() );
				}
				return TRUE;
			}
		}
		break;
	default:
		break;
	}
	return GxxLBLine::Response(nMsg,wParam,lParam);
}


const wstring & GxxDeviceListLine::getLineName()
{
	return m_pTextTitle->getText();
}


bool GxxDeviceListLine::SetDeviceStatus( DeviceItem::DeviceStatus ds )
{
	m_status = ds;
	if (m_status==DeviceItem::CONNECTED){
		m_text_Connect->setTextFromId("connect_31");
	}
	else{
		m_text_Connect->setTextFromId("disconnect_31");
	}
	//m_text_Connect->invalidateRect();
	return true;
}
