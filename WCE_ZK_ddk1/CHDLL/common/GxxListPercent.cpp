#include "StdAfx.h"
#include "GxxListPercent.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxToolGroup.h"
#include "GXCreateControls.h"
#include "ControlHelp.h"
#include "GxxAniLable.h"

static RegisterHelp help("GxxListPercent", GxxListPercent::CreateControl);
GxxView* GxxListPercent::CreateControl()
{
	return new GxxListPercent;
}

GxxListPercent::GxxListPercent()
{
}

GxxListPercent::~GxxListPercent()
{

}


//BOOL GxxListPercent::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
//{
//	if (0x119==message || WM_MOUSEMOVE ==  message || WM_SETCURSOR ==  message || CTR_ANIMATION_MES ==  message)
//	{
//		return FALSE;//
//	}
//	if (!getDraw())
//	{
//		return false;
//	}
//	ControlList::reverse_iterator pos;	
//	pos = m_pCtrlVet->rbegin();
//	while(pos != m_pCtrlVet->rend())
//	{
//
//		if ( (*pos)->DealCtrlMsg(message, wParam, lParam ))
//		{
//			return TRUE;
//		}
//		pos++;
//	}
//	if (Response(message, wParam, lParam ) == TRUE)
//	{
//		return TRUE;
//	}
//	return FALSE;
//}
void GxxListPercent::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);	

	TiXmlElement * chid = ele->FirstChildElement();

	setCtrList(chid);

	m_btn[0] = (GxxAniLable *)safeFindViewByName("percent_10");
	m_btn[1] = (GxxAniLable *)safeFindViewByName("percent_20");
	m_btn[2] = (GxxAniLable *)safeFindViewByName("percent_30");
	m_btn[3] = (GxxAniLable *)safeFindViewByName("percent_40");
	m_btn[4] = (GxxAniLable *)safeFindViewByName("percent_50");
	m_btn[5] = (GxxAniLable *)safeFindViewByName("percent_60");
	m_btn[6] = (GxxAniLable *)safeFindViewByName("percent_70");
	m_btn[7] = (GxxAniLable *)safeFindViewByName("percent_80");
	m_btn[8] = (GxxAniLable *)safeFindViewByName("percent_90");
	m_btn[9] = (GxxAniLable *)safeFindViewByName("percent_100");
	setDraw(false);
}

BOOL GxxListPercent::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			for (int i = 0; i<10; i++)
			{
				if ((GxxAniLable *)wParam == m_btn[i])
				{
					saftGetParentView()->TranslateMessage(CTR_LIST_PERCENT_BTN,(i+1)*10-5,0);
					return TRUE;
				}
			}
		}
		break;
	default:
		break;
	}

	return FALSE;
}


