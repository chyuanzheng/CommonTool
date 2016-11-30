#pragma once

#include "GxLock.h"
#include <map>
#include <list>
using namespace std;

typedef LRESULT (*NotifyHandler)(void* pThis, DWORD param1, DWORD param2);

#define DECLARE_NOTIFY_CALLBACK(theFun, theClass) \
	static LRESULT theFun(void* pThis, DWORD param1, DWORD param2) \
{\
	theClass *p = (theClass *)pThis;\
	return p->theFun(param1, param2);\
}\
	LRESULT theFun(DWORD param1, DWORD param2)



class CE_CONTROL_API Notify
{
public:
	NotifyHandler funNotify;
	void*	dwParam;

public:
	BOOL operator==(const Notify &n) const 
	{
		if (funNotify == n.funNotify && dwParam == n.dwParam)
		{
			return 1;
		}
		return 0;
	}
};

// 采用字符串的BKDRHash作为标识,提高性能
// 字符串仅仅支持ascii

class CE_CONTROL_API GXNotify
{
	static map<UINT, list<Notify>> mapNotify;
	static UINT nowNotify;
	static DWORD nowParam1;
	static DWORD nowParam2;
	static DWORD nowTimeID;
	static GxLock lock;	
	static int  m_msg_count;	
public:
	static unsigned int BKDRHash(const char *str)
	{
		if (!str)
		{
			return 0;
		}
		unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
		unsigned int hash = 0;

		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		if (hash == 0)
		{
			hash = 0xFFFFFFFF;
		}
		return (hash & 0x7FFFFFFF);
	}
public:
	static void ClearAll();
	static void RegisterNotifyHandler(char* strNotify, Notify notify);
	static void UnRegisterNotifyHandler(char* strNotify, Notify notify);
	// 同步发送消息
	static LRESULT SendNotify(char* strNotify, DWORD param1, DWORD param2);
	static LRESULT SendNotify(UINT hashcodNotilfy, DWORD param1, DWORD param2);
	// 异步发送消息
	static LRESULT SendNotifyAsync(HWND hWnd, char* strNotify, DWORD param1, DWORD param2);
	static LRESULT SendNotifyAsync(HWND hWnd, UINT hashcodNotilfy, DWORD param1, DWORD param2);
	static LRESULT SendNotifySync(HWND hWnd, char* strNotify, DWORD param1, DWORD param2);
	static LRESULT SendNotifySync(HWND hWnd, UINT hashcodNotilfy, DWORD param1, DWORD param2);
	
	static void CALLBACK TimerProc(
		HWND hwnd, 
		UINT uMsg, 
		UINT idEvent, 
		DWORD dwTime 
		); 
	static void ReleasParam();
};