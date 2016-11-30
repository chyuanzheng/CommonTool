#pragma once
#include <windows.h>
// wince 版本的多线程lock
#include "DllDefine.h"
class CE_CONTROL_API GxLock
{
	CRITICAL_SECTION	cs;
	BOOL				debug;
public:
	GxLock(BOOL d=0)
	{
		debug = d;
		Init();
	}
	~GxLock()
	{
		Deinit();
	}
	void Init()
	{
		InitializeCriticalSection(&cs);
	}
	void Lock()
	{
		RETAILMSG(debug,(TEXT("Lock-------\r\n")));
		EnterCriticalSection(&cs);
	}

	void UnLock()
	{
		LeaveCriticalSection(&cs);
		RETAILMSG(debug,(TEXT("UnLock-------\r\n")));
	}

	void Deinit()
	{
		DeleteCriticalSection(&cs);
	}
};