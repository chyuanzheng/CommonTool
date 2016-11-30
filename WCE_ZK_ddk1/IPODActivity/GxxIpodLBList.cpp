#include "StdAfx.h"
#include "GxxIpodLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxIpodListLine.h"

GxxIpodLBList::GxxIpodLBList()
{

}


void GxxIpodLBList::AddLine( const string &s_id )
{
	GxxIpodListLine *ctr = new GxxIpodListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
	AddCtrl(ctr);
	ctr->setIpodLine(getCtrlsSize()-1,&s_id,NULL);
}

void GxxIpodLBList::AddLine( const wstring &s )
{
	GxxIpodListLine *ctr = new GxxIpodListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
	AddCtrl(ctr);
	ctr->setIpodLine(getCtrlsSize()-1,NULL,&s);
}



