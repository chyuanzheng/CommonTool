#include "StdAfx.h"
#include "GXNotify.h"
using namespace std;
map<UINT, list<Notify>> GXNotify::mapNotify;
UINT GXNotify::nowNotify;
DWORD GXNotify::nowParam1;
DWORD GXNotify::nowParam2;
DWORD GXNotify::nowTimeID;
GxLock GXNotify::lock;	
int  GXNotify::m_msg_count = 0;
void GXNotify::RegisterNotifyHandler(char* strNotify, Notify notify)
{
	map<UINT, list<Notify>>::iterator iter;
	UINT hashcode = BKDRHash(strNotify);
	iter = mapNotify.find(hashcode);
	if (iter != mapNotify.end())
	{
		iter->second.remove(notify);	// 注意同一个发起者多次插入的情况 (多次插入,删除之)
		iter->second.push_back(notify);
	}
	else
	{
		// 未找到
		list<Notify> lstNotify;
		lstNotify.push_back(notify);
		mapNotify.insert(pair<UINT, list<Notify>>(hashcode, lstNotify));
	}
}

void GXNotify::UnRegisterNotifyHandler(char* strNotify, Notify notify)
{
	map<UINT, list<Notify>>::iterator iter;
	UINT hashcode = BKDRHash(strNotify);
	iter = mapNotify.find(hashcode);
	if (iter != mapNotify.end())
	{
		iter->second.remove(notify);
	}
}

LRESULT GXNotify::SendNotify(char* strNotify, DWORD param1, DWORD param2)
{
	BOOL ret = 0;
	map<UINT, list<Notify>>::iterator iter;
	UINT hashcode = BKDRHash(strNotify);
	iter = mapNotify.find(hashcode);
	
	if (iter != mapNotify.end())
	{
		list<Notify> lstNotify = iter->second;
		list<Notify>::iterator iterList;
		for (iterList=iter->second.begin(); iterList!=iter->second.end(); iterList++)
		{
			NotifyHandler fun = (*iterList).funNotify;
			void* p = (*iterList).dwParam;
			ret = fun(p, param1, param2);
		}
	}
	return ret;
}

LRESULT GXNotify::SendNotify(UINT hashcodNotilfy, DWORD param1, DWORD param2)
{
	map<UINT, list<Notify>>::iterator iter;
	iter = mapNotify.find(hashcodNotilfy);
	if (iter != mapNotify.end())
	{
		list<Notify>::iterator iterList;
		for (iterList=iter->second.begin(); iterList!=iter->second.end(); iterList++)
		{
			NotifyHandler fun = (*iterList).funNotify;
			void* p = (*iterList).dwParam;
			fun(p, param1, param2);
		}
	}
	return 0;
}

LRESULT GXNotify::SendNotifyAsync(HWND hWnd, char* strNotify, DWORD param1, DWORD param2)
{
	UINT hashcode = BKDRHash(strNotify);
	SendNotifyAsync(hWnd, hashcode, param1, param2);
	return 0;
}

LRESULT GXNotify::SendNotifyAsync(HWND hWnd, UINT hashcodNotilfy, DWORD param1, DWORD param2)
{
	//lock.Lock();
	//nowNotify = hashcodNotilfy;
	//nowParam1 = param1;
	//nowParam2 = param2;
	//nowTimeID = ::SetTimer(hWnd, 0xFFFFFFFE, 0, TimerProc);
	//lock.UnLock();
	DWORD *param = new DWORD[2];
	param[0] = param1;
	param[1] = param2;
	GXNotify::m_msg_count++;
	ASSERT(GXNotify::m_msg_count<600);
	PostMessage(hWnd, RegisterWindowMessage(L"GXNotify"), hashcodNotilfy, (LPARAM)param);
	return  0;
}

LRESULT GXNotify::SendNotifySync(HWND hWnd, char* strNotify, DWORD param1, DWORD param2)
{
	UINT hashcode = BKDRHash(strNotify);
	SendNotifyAsync(hWnd, hashcode, param1, param2);
	return 0;
}

LRESULT GXNotify::SendNotifySync(HWND hWnd, UINT hashcodNotilfy, DWORD param1, DWORD param2)
{
	//lock.Lock();
	//nowNotify = hashcodNotilfy;
	//nowParam1 = param1;
	//nowParam2 = param2;
	//nowTimeID = ::SetTimer(hWnd, 0xFFFFFFFE, 0, TimerProc);
	//lock.UnLock();
	DWORD *param = new DWORD[2];
	param[0] = param1;
	param[1] = param2;
	GXNotify::m_msg_count++;
	ASSERT(GXNotify::m_msg_count<600);
	SendMessage(hWnd, RegisterWindowMessage(L"GXNotify"), hashcodNotilfy, (LPARAM)param);
	return  0;
}

void GXNotify::ReleasParam()
{
	--GXNotify::m_msg_count;
}


void GXNotify::TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
	lock.Lock();
	::KillTimer(hwnd, idEvent);
	SendNotify(nowNotify, nowParam1, nowParam2);
	lock.UnLock();
}

void GXNotify::ClearAll()
{
	mapNotify.clear();
}

