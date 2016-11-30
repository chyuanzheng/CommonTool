#pragma once
#include "GxxLBList.h"
#include "bluetooth.h"
#include "GxxFileListLine.h"

class CE_CONTROL_API GxxFileLBList : public GxxLBList
{
public:
	GxxFileLBList(){;}
	virtual ~GxxFileLBList(){;}
	void DeleteItem( int iItemId );
	void AddLine( const wstring  &wstr ,GxxFileListLine::ICON_TYPE type = GxxFileListLine::NoneLine,HANDLE h = NULL);
	void AddLine( const string  &str_id ,GxxFileListLine::ICON_TYPE type = GxxFileListLine::NoneLine,HANDLE h = NULL);
	bool  getLineName( int nItem ,wstring &name);
};
