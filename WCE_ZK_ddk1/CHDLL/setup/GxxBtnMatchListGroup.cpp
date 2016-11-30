#include "StdAfx.h"
#include "GxxSelectLBList.h"
#include "GxxBtnMatchListGroup.h"
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
static RegisterHelp help("GxxBtnMatchListGroup", GxxBtnMatchListGroup::CreateControl);
GxxView* GxxBtnMatchListGroup::CreateControl()
{
	return new GxxBtnMatchListGroup;
}
GxxBtnMatchListGroup::GxxBtnMatchListGroup()
{

}

GxxBtnMatchListGroup::~GxxBtnMatchListGroup()
{

}

bool GxxBtnMatchListGroup::SetSelLine( int nlan,bool showSel/*=false */ )
{
	bool b_ret = GxxSelectListGroupBase::SetSelLine(nlan,showSel);
	if (b_ret)
	{
		AfxSendMessage(CTR_SET_BTN_MATCH,(WPARAM)((GxxSelectLBList *)m_curListBox)->GetNthLine(nlan),nlan);//通知可以进行方控学习
	}
	
	return b_ret;
}

