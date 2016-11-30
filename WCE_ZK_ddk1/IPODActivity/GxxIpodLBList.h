#pragma once
#include "IPODDllModule.h"
#include "GxxLBList.h"

class CE_IPODACTIVITY_API GxxIpodLBList : public GxxLBList
{
public:
	GxxIpodLBList();
	virtual ~GxxIpodLBList(){;}
	void AddLine( const string &s_id);
	void AddLine( const wstring &s );

};
