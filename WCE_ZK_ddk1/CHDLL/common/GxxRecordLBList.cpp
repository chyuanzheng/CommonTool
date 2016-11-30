#include "StdAfx.h"
#include "GxxRecordLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxRecordListLine.h"


void GxxRecordLBList::AddRecord( int id, const wstring &phone_name,RecordItem::RecordType rt, const wstring &date, const wstring &strPerson, bool toBack   )
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

	GxxRecordListLine *ctr = new GxxRecordListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());

	ctr->setParentView(this);
	if (toBack)
	{
		m_pCtrlVet->push_back(ctr);
	}
	else
	{
		m_pCtrlVet->push_front(ctr);
	}



	ctr->setRecordLine(id, ntop, phone_name, rt, date,strPerson );
}

void GxxRecordLBList::DeleteItem( int iItemId )
{
	GxxRecordListLine *pl = NULL;
	for (ControlList::iterator pos =  m_pCtrlVet->begin(); pos != m_pCtrlVet->end(); ++pos)
	{
		if ( ((GxxRecordListLine *)(*pos))->getIndex() == iItemId )
		{
			pl = (GxxRecordListLine *)(*pos);
			break;;
		}	
	}

	if (pl !=NULL )
	{
		deleteOneCtrl(pl);
	}
}

