#pragma once
#include "GxxLBList.h"
#include "bluetooth.h"
class CE_CONTROL_API GxxRecordLBList : public GxxLBList
{
public:
	GxxRecordLBList(){;}
	virtual ~GxxRecordLBList(){;}
	void AddRecord( int id, const wstring &phone_name,RecordItem::RecordType rt, const wstring &date, const wstring &strPerson, bool toBack );
	void DeleteItem( int iItemId );
};
