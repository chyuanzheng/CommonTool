#include "StdAfx.h"
#include "GxxFileLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxFileListLine.h"

void GxxFileLBList::DeleteItem( int iItemId )
{
	GxxFileListLine *pl = NULL;
	for (ControlList::iterator pos =  m_pCtrlVet->begin(); pos != m_pCtrlVet->end(); ++pos)
	{
		if ( ((GxxFileListLine *)(*pos))->getIndex() == iItemId )
		{
			pl = (GxxFileListLine *)(*pos);
			break;
		}	
	}

	if (pl !=NULL )
	{
		deleteOneCtrl(pl);
	}
}



void GxxFileLBList::AddLine( const wstring  & wstr ,GxxFileListLine::ICON_TYPE type /*= GxxFileListLine::NoneLine*/,HANDLE h /*= NULL*/ )
{
	GxxFileListLine *ctr = new GxxFileListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
	AddCtrl(ctr);
	ctr->setFileLine(getCtrlsSize()-1,wstr,type,h);
}

void GxxFileLBList::AddLine( const string &str_id ,GxxFileListLine::ICON_TYPE type /*= GxxFileListLine::NoneLine*/,HANDLE h /*= NULL*/ )
{
	GxxFileListLine *ctr = new GxxFileListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
	AddCtrl(ctr);
	ctr->setFileLine(getCtrlsSize()-1,str_id,type,h);
}


bool GxxFileLBList::getLineName( int nItem ,wstring &name )
{
	if (nItem >= m_pCtrlVet->size()  )
	{
		return false;
	}
	ControlList::iterator pos = m_pCtrlVet->begin();
	std::advance(pos,nItem);
	name = ((GxxFileListLine *)(*pos))->getLineName();
	return true;
}
