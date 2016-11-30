#include "StdAfx.h"
#include "GxxVedioSetup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "Activity.h"
#include "ResStringManager.h"
#include "ControlHelp.h"
#include "GxxSetupListGroup.h"
//#include "SetupDislayManager.h"

static RegisterHelp help("GxxVedioSetup", GxxVedioSetup::CreateControl);
GxxView* GxxVedioSetup::CreateControl()
{
	return new GxxVedioSetup;
}

GxxVedioSetup::GxxVedioSetup(  )
{
	m_vedioList = NULL;
	m_setupActivity = NULL;
}

GxxVedioSetup::~GxxVedioSetup()
{

}

BOOL GxxVedioSetup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	//switch( nMsg )
	//{
	//case CTR_MESSAGE:
	//	if (MES_LBUTTONUP==lParam)
	//	{

	//	}
	//	return FALSE;
	//default:
	//	return FALSE;
	//}
	return FALSE;
}

void GxxVedioSetup::setCtrLayout( TiXmlElement * ele )
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

	TiXmlElement * chid = ele->FirstChildElement();
	setCtrList(chid);
}


void GxxVedioSetup::onResume()
{

}

void GxxVedioSetup::onPause()
{
	//CloseVedioSetup();
}

