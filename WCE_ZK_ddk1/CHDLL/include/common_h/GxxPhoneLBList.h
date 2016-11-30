#pragma once
#include "GxxLBList.h"
class CE_CONTROL_API GxxPhoneLBList : public GxxLBList
{
public:
	GxxPhoneLBList(){;}
	virtual ~GxxPhoneLBList(){;}
	void AddPhone( int id, const wstring &phone_name,const wstring &phone_num );
	void DeleteItem( int iItemId );
};
