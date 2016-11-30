#include "StdAfx.h"
#include "GxxCommonCtr.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxToolGroup.h"
#include "GXCreateControls.h"
#include "ControlHelp.h"

GxxView *GxxCommonCtr::s_commonCtrl = NULL;
static RegisterHelp help("GxxCommonCtr", GxxCommonCtr::CreateControl);
GxxView* GxxCommonCtr::CreateControl()
{
	return new GxxCommonCtr;
}

GxxCommonCtr::GxxCommonCtr()
{
}

GxxCommonCtr::~GxxCommonCtr()
{

}



void GxxCommonCtr::setCtrLayout( TiXmlElement * ele )
{
	ASSERT(NULL==GxxCommonCtr::s_commonCtrl);

	GxxCommonCtr::s_commonCtrl = this;
	setCtrName(ele);
	setCtrRect(ele);	
	string ctrname;


	TiXmlElement * chid = ele->FirstChildElement();

	GxxView *ctr=NULL;
	while(chid)
	{
		ctr=NULL;
		ctrname = chid->Value();

		if (ctrname == GXXMAININFO)
		{
			ctr = GXCreateControl::CreateControlByType(ctrname.c_str());
		}
		else if (ctrname ==GXXTOOLGROUP)
		{
			ctr = new GxxToolGroup;
		}
		else if (ctrname == GXXCYCLE)
		{
			ctr = GXCreateControl::CreateControlByType(ctrname.c_str());
			//ctr = new GxxCycle;
		}
		else
		{
			ctr = GXCreateControl::CreateControlByType(ctrname.c_str());
		}
		ASSERT(NULL!=ctr);
		if (ctr)
		{
			AddCtrl(ctr);
			ctr->setCtrLayout(chid);
		}
		chid = chid->NextSiblingElement();
	}
	m_groupbtn = findViewByName("icon_group");
}

BOOL GxxCommonCtr::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )//
	{
	case CTR_INTO_FULL_SCREEN://MES_ANIMATION_END  MAKELONG
		setSelView(m_groupbtn);
		setDraw(false);
		return TRUE;
	case CTR_EXIT_FULL_SCREEN:
		if (m_groupbtn == getSelView())
		{
			setSelView(NULL);
		}
		setDraw(true);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}


