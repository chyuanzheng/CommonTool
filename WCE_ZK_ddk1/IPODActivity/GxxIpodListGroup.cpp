#include "StdAfx.h"
#include "GxxIpodListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxView.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxIpodLBList.h"
#include "GxxIpodListLine.h"
#include "GxxListPercent.h"
#include "GxxSwText.h"


#define  PercentLineMin 60



static RegisterHelp help("GxxIpodListGroup", GxxIpodListGroup::CreateControl);
GxxView* GxxIpodListGroup::CreateControl()
{
	return new GxxIpodListGroup;
}
GxxIpodListGroup::GxxIpodListGroup()
{
	m_curListBox =  new GxxIpodLBList;
	AddCtrl(m_curListBox);
}

GxxIpodListGroup::~GxxIpodListGroup()
{
	delete m_curListBox;
}






BOOL GxxIpodListGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				SendGxxMessage(GX_LISTBOX_BACK_TO_ACTIVITY);
				return TRUE;
			}

			if ((GxxView *)wParam == m_btnBack)
			{
				if (FIRST_LIST == m_listType)
				{
					SendGxxMessage(GX_LISTBOX_BACK_TO_ACTIVITY);
				}
				else if (MUSIC_MENU_LIST == m_listType)
				{
					InitFirstList();
				}
				else
				{
					SendGxxMessage(GX_LISTBOX_BACK_TO_LIST);
				}
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

void GxxIpodListGroup::setCtrLayout( TiXmlElement * ele )
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

	ResetList();
	ASSERT(m_btnBack!=NULL );

}



void GxxIpodListGroup::LineBtnDown( WPARAM wParam, LPARAM lParam )
{
	int nth = lParam;
	if(FIRST_LIST == m_listType )
	{
		if (0 == nth)//进入MUSIC目录
		{
			InitMusicList();
		}
		else if ( 1 == nth)//进入MOVIE目录
		{
			SendGxxMessage(GX_INIT_MOVIE_LIST);
		}
		else
		{
			ASSERT(0);
		}
	}
	else if (MUSIC_MENU_LIST == m_listType)//
	{
		SendGxxMessage(GX_INIT_MUSIC_LIST,nth);		
	}
	else if (MOVIE_CLASS_LIST == m_listType || MUSIC_CLASS_LIST == m_listType)
	{
		SendGxxMessage(GX_LISTBOX_BUTTON_DOWNM,nth);
	}

	//GxxIpodListLine* line = ((GxxIpodListLine*)wParam);
	//ASSERT(line);
	//m_lineName = line->GetTextName();
}


void GxxIpodListGroup::StartReceiveList()
{
	DeleteAllItem();
	if (MUSIC_MENU_LIST == m_listType)
	{
		m_listType = MUSIC_CLASS_LIST;
		//SetGroupTitle(m_lineName);
	}
	else if (FIRST_LIST == m_listType)
	{
		m_listType = MOVIE_CLASS_LIST;
		//SetGroupTitle(m_lineName);
	}
}

void GxxIpodListGroup::AddItem( wstring name )
{
	ASSERT (MOVIE_CLASS_LIST == m_listType || MUSIC_CLASS_LIST == m_listType);
	((GxxIpodLBList *)m_curListBox)->AddLine(name);

}



void GxxIpodListGroup::ResetList()
{
	m_curListBox->CaculateRation(false);
	m_curListBox->invalidateRect();
	m_percentBtn->setDraw(m_curListBox->getCtrlsSize()>PercentLineMin);
	m_percentBtn->invalidateRect();
}


void GxxIpodListGroup::BackToMenu()
{
	if (MOVIE_CLASS_LIST == m_listType )
	{
		InitFirstList();
	}
	else if ( MUSIC_CLASS_LIST == m_listType)
	{
		InitMusicList();
	}
}



void GxxIpodListGroup::InitFirstList()
{
	m_listType = FIRST_LIST;
	m_curListBox->deleteAllCtrls();
	((GxxIpodLBList *)m_curListBox)->AddLine("ID_MUSIC");//初始化第一层目录
	((GxxIpodLBList *)m_curListBox)->AddLine("ID_MOVIE");
	ResetList();
	SetGroupTitle(m_ipodName);


}


void GxxIpodListGroup::InitList()
{
	m_listType = FIRST_LIST;
	m_curListBox->deleteAllCtrls();
	ResetList();
	m_titleText->setText( wstring());
}


void GxxIpodListGroup::InitMusicList()
{
	m_listType = MUSIC_MENU_LIST;
	m_curListBox->deleteAllCtrls();
	((GxxIpodLBList *)m_curListBox)->AddLine("Ipod_Playlist");//初始化第二层目录（MUISC）
	((GxxIpodLBList *)m_curListBox)->AddLine("Ipod_Artist");
	((GxxIpodLBList *)m_curListBox)->AddLine("Ipod_Album");
	((GxxIpodLBList *)m_curListBox)->AddLine("Ipod_Genre");
	((GxxIpodLBList *)m_curListBox)->AddLine("Ipod_Track");
	ResetList();
	SetGroupTitle(m_ipodName);
}



void GxxIpodListGroup::SendGxxMessage( UINT msg,LPARAM lParam /*= 0 */ )
{
	if (m_mesView)
	{
		m_mesView->TranslateMessage(msg,(WPARAM)this,lParam);
	}
}



void GxxIpodListGroup::DeleteAllItem()
{
	m_curListBox->deleteAllCtrls();
	ResetList();
}

void GxxIpodListGroup::SetIpodName( const WCHAR *name )
{
	m_ipodName = name;
	if (FIRST_LIST == m_listType|| MUSIC_MENU_LIST == m_listType )
	{
		SetGroupTitle(m_ipodName);
	}
	
}



void GxxIpodListGroup::SetGroupTitle( const wstring &str )
{
	m_titleText->setText(str);
	m_titleText->invalidateRect();
}


