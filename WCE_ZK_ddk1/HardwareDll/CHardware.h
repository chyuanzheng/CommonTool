#pragma once

class CHardware;

typedef DWORD (*FunMsg)(CHardware *pHardware, DWORD dwParam, UINT msg, WPARAM wParam, LPARAM lParam);

#define DECLARE_MSGHANDLER(theFun, theClass) \
static DWORD theFun(CHardware *pControl, DWORD dwParam, UINT msg, WPARAM wParam, LPARAM lParam)\
{\
	theClass *pThis = (theClass *)dwParam;\
	return pThis->theFun(pControl, msg, wParam, lParam);\
}\
	DWORD theFun(CHardware *pControl, UINT msg, WPARAM wParam, LPARAM lParam);


/*
	��Ҫͳһ Hardware ��,�� WinFun ��,������Ϣ�ķ���
	������̲߳���UI
*/
class CHardware
{
	DWORD dwParam;
public:
	FunMsg	funMsg;
	CHardware()
	{
		funMsg = NULL;
	}
public:
	void RegisterMsg(FunMsg fun, DWORD param)
	{
		funMsg = fun;
		dwParam = param;
	}
	void SendMsg(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (funMsg)
		{
			funMsg(this, dwParam, msg, wParam, lParam);
		}
	}
};