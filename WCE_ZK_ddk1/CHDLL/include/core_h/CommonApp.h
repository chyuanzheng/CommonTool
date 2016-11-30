#pragma once
#include "CWinApp.h"
class CE_CONTROL_API CCommonApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
	virtual BOOL DeInitInstance();
	BOOL InitActivity( const char* strManifest );

};

