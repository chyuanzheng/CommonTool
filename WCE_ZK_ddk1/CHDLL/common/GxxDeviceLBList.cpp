#include "StdAfx.h"
#include "GxxDeviceLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxDeviceListLine.h"


void GxxDeviceLBList::AddDevice( int id, const wstring &name, DeviceItem::DeviceStatus ds )
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

	GxxDeviceListLine *ctr = new GxxDeviceListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
	AddCtrl(ctr);


	ctr->setDeviceLine(id, ntop, name, ds );
}

void GxxDeviceLBList::DeleteItem( int iItemId )
{
	GxxDeviceListLine *pl = NULL;
	for (ControlList::iterator pos =  m_pCtrlVet->begin(); pos != m_pCtrlVet->end(); ++pos)
	{
		if ( ((GxxDeviceListLine *)(*pos))->getIndex() == iItemId )
		{
			pl = (GxxDeviceListLine *)(*pos);
			break;
		}	
	}

	if (pl !=NULL )
	{
		deleteOneCtrl(pl);
	}
}

bool GxxDeviceLBList::SetDeviceStatus( int iItemID, DeviceItem::DeviceStatus ds )
{
	GxxDeviceListLine *pl = NULL;
	for (ControlList::iterator pos =  m_pCtrlVet->begin(); pos != m_pCtrlVet->end(); ++pos)
	{
		if ( ((GxxDeviceListLine *)(*pos))->getIndex() == iItemID )
		{
			pl = (GxxDeviceListLine *)(*pos);
			bool b = pl->SetDeviceStatus(ds);
			pl->invalidateRect();
			return b;
		}	
	}
	return false;
}

