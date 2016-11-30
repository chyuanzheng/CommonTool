#include "StdAfx.h"
#include "GxxCommonKeys.h"

#include "XmlDef.h"
//#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxLabel.h"
#include "ControlHelp.h"
#include "GxxVedioSetup.h"
#include "TVCommand.h"

GxxCommonKeys::GxxCommonKeys()
{
	m_mesView = NULL;

}

GxxCommonKeys::~GxxCommonKeys()
{

}

void GxxCommonKeys::SetMessageView( GxxView * mesView )
{
	m_mesView = mesView;
}


void GxxCommonKeys::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);

	int iVisible = 1;
	if(ele->Attribute(VISIBLE, &iVisible))	//是否出现控件
	{
		if(iVisible == 0)
		{
			setDraw(FALSE);
		}
	}
	setCtrList( ele->FirstChildElement() );

	m_back_btn = safeFindViewByName("Inc_Into_MainInterface");
	m_left_btn = safeFindViewByName("Label_SearchPrev");
	m_right_btn = safeFindViewByName("Label_SearchNext");
	m_info_btn = safeFindViewByName("Label_SwitchInfoOrMain");
	

}

BOOL GxxCommonKeys::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_back_btn)	
			{
				PostDtvMessage(DTV_Back_Btn);
				return TRUE;
			}
			if ((GxxView *)wParam == m_left_btn)	
			{
				PostDtvMessage(DTV_Vol_Dec);
				return TRUE;
			}
			if ((GxxView *)wParam == m_right_btn)	
			{
				PostDtvMessage(DTV_Vol_Add);
				return TRUE;
			}
			if ((GxxView *)wParam == m_info_btn)	
			{
				PostDtvMessage(DTV_Info_Btn);
				return TRUE;
			}
		}
	}

	return 0;
}

void GxxCommonKeys::PostDtvMessage( UINT msg )
{
	if (m_mesView)
	{
		m_mesView->TranslateMessage(msg,(WPARAM)this,0);
	}
}

GxxView* GxxCommonKeys::CreateControl()
{
	return new GxxCommonKeys;
}
static RegisterHelp help("GxxCommonKeys", GxxCommonKeys::CreateControl);