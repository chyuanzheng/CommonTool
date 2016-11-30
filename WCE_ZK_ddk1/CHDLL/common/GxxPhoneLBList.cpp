#include "StdAfx.h"
#include "GxxPhoneLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxPhoneListLine.h"


void GxxPhoneLBList::AddPhone( int id, const wstring &phone_name,const wstring &phone_num )
{
	int ntop = 0;
	if (getCtrlsSize()==0)
	{
		ntop = m_ActRect.top;
	}
	else
	{
		GxxView *v =m_pCtrlVet->back();
		ntop =v->getCtrRect().bottom;
	}

	GxxPhoneListLine *ctr = new GxxPhoneListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
	AddCtrl(ctr);


	ctr->setPhoneLine(id, ntop, phone_name,phone_num);
}

void GxxPhoneLBList::DeleteItem( int iItemId )
{
	GxxPhoneListLine *pl = NULL;
	for (ControlList::iterator pos =  m_pCtrlVet->begin(); pos != m_pCtrlVet->end(); ++pos)
	{
		if ( ((GxxPhoneListLine *)(*pos))->getIndex() == iItemId )
		{
			pl = (GxxPhoneListLine *)(*pos);
			break;
		}	
	}

	if (pl !=NULL )
	{
		deleteOneCtrl(pl);
	}
}

