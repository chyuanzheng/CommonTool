#include "stdAfx.h"
//#include "base.h"
#include "Navi.h"
#include "param.h"
#include "pip/PIP.h"
#include "GXNotify.h"
//#include "ProcManage.h"

GxxString Navi::sNaviPath;
HWND Navi::hWndNavi = 0;
PROCESS_INFORMATION Navi::piNavi = {0};
HANDLE Navi::hMonitorNaviThread = INVALID_HANDLE_VALUE;
BOOL	Navi::bNaviOn = 0;
BOOL	Navi::bNaviOnTop = 0;
HWND	Navi::hWndGRT;

#define WM_SETNAVIVOL  ::RegisterWindowMessage(L"Navi_SetVol")

GxxString Navi::GetNaviPath()
{
	return sNaviPath;
}

void Navi::SetNaviPath(GxxString str)
{
	sNaviPath = str;
}

BOOL Navi::StartNavi()
{
	BOOL ret = 0;
	hWndNavi = FindWindow(L"GEOBOTCLASS", NULL);
	if (hWndNavi != INVALID_HANDLE_VALUE && hWndNavi != NULL)
	{
		bNaviOn = 1;
	}
	if (Navi::bNaviOn)
	{
		ShowNavi();
		return 1;
	}
//	RETAILMSG(1, (TEXT("navi path = %s\r\n"), sNaviPath.GetData()));
	bNaviOnTop = bNaviOn = ret = CreateProcess(sNaviPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &piNavi);
	if (ret)
	{
		if (hMonitorNaviThread == INVALID_HANDLE_VALUE)
		{
			DWORD dwThreadID;
			hMonitorNaviThread = (HANDLE)::CreateThread(NULL, 0, MonitorNaviThread, 0, 0, &dwThreadID);
		}
	}
	if (bNaviOnTop)
	{
		MediaControl::SetVMode(1);
		//GXNotify::SendNotify("movie_stop", 0, 0);
	}
	
	return bNaviOn;
}

DWORD Navi::MonitorNaviThread(LPVOID lpParam)
{
	while (1) 
	{
		if (piNavi.hProcess != 0)
		{
			Sleep(2000);
			hWndNavi = FindWindow(L"GEOBOTCLASS", NULL);
			GXNotify::SendNotify("set_navi_vol", 0, 0);
			WaitForSingleObject(piNavi.hProcess, INFINITE);
			if (hWndNavi = FindWindow(L"SpFrameWndClass", NULL))
			{
				// 导航软件仍然在运行

			}
			else
			{
				hWndNavi = 0;
				piNavi.hProcess = 0;
				bNaviOn = 0;
				bNaviOnTop = 0;
				::ShowWindow(hWndGRT, SW_SHOW);
				SetForegroundWindow(hWndGRT);
				HWND hWndTaskbar = FindWindow(_T("HHTaskbar"),NULL);
				if (NULL != hWndTaskbar)
				{
					MoveWindow(hWndTaskbar, 0, 480, 0, 0, 0);
					::ShowWindow(hWndTaskbar,SW_HIDE);
					//SetWindowPos(hWndTaskbar, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
				}
			}
		}
		Sleep(1000);
	}
}

BOOL Navi::EnumWindows(HWND hWnd, LPARAM lParam)
{
	HWND hParent;
	hWndNavi = FindWindow(L"GEOBOTCLASS", NULL);

	//找到导航的顶层窗口
	int i = 0;
	if (hWndNavi != NULL)
	{
		hParent = GetParent(hWndNavi);
		while (hParent != NULL)
		{
			hWndNavi = hParent;
			hParent = GetParent(hWndNavi);

			//避免死循环
			i++;
			if(i > 500) 
			{
				break;
			}
		}
	}
	if (hParent == NULL)	 //已找到顶层窗口
	{
		return TRUE;
	}
	DWORD dwProID;
	GetWindowThreadProcessId(hWnd, &dwProID);
	Sleep(1);
	if (piNavi.dwProcessId == dwProID)
	{
		hWndNavi = hWnd;
		return FALSE;
	}
	return TRUE;
}

BOOL Navi::ShowNavi()
{
	if (Navi::bNaviOn)
	{
		if (Navi::hWndNavi == 0)
		{
			::EnumWindows(EnumWindows, NULL);
		}
		if (Navi::hWndNavi != 0)
		{
			ShowWindow(Navi::hWndNavi, SW_SHOW);
			SetForegroundWindow(Navi::hWndNavi);
		}
		bNaviOnTop = 1;
		Sleep(200);
		if (GetForegroundWindow() == Navi::hWndGRT)
		{
			SetWindowPos(Navi::hWndGRT, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		}
		//::ShowWindow(hWndGRT, SW_HIDE);
		if (sysConfig.bFullScreen)
		{
			MediaControl::HideMediaWnd();
		}
		SetCursorPos(800, 480);

		MediaControl::SetVMode(1);
		
		HWND hWndTaskbar = FindWindow(_T("HHTaskbar"),NULL);
		if (NULL != hWndTaskbar)
		{
			//::ShowWindow(hWndTaskbar,SW_HIDE);
			//SetWindowPos(hWndTaskbar, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		}
		AfxPostMessage(CTR_NAVI_SHOW, 0, 0);
	}
	
	return Navi::bNaviOn;
}

BOOL Navi::HideNavi()
{
	if (Navi::bNaviOn)
	{
		bNaviOnTop = 0;
		HWND hWndTaskbar = FindWindow(_T("HHTaskbar"),NULL);
		if (NULL != hWndTaskbar)
		{
			MoveWindow(hWndTaskbar, 0, 480, 0, 0, 0);
			::ShowWindow(hWndTaskbar,SW_HIDE);
		}

		if (sysConfig.bFullScreen)
		{
			//::ShowWindow(hWndGRT, SW_SHOW);
			//ShowWindow(hWndNavi, SW_HIDE);
			SetForegroundWindow(hWndGRT);
			//MediaControl::ShowMediaWnd();
			//SetWindowPos(hWndNavi, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
			
		}
		else
		{
			//::ShowWindow(hWndGRT, SW_SHOW);
			//SetWindowPos(hWndGRT, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
			if (Navi::hWndNavi == 0)
			{
				::EnumWindows(EnumWindows, NULL);
			}
			//ShowWindow(hWndNavi, SW_HIDE);
			Sleep(100);
			SetForegroundWindow(hWndGRT);
			//SetWindowPos(hWndNavi, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		}
		SetCursorPos(800, 480);
		//HWND hWndTaskbar = FindWindow(_T("HHTaskbar"),NULL);
		//if (NULL != hWndTaskbar)
		//{
		//	MoveWindow(hWndTaskbar, 0, 480, 0, 0, 0);
		//	::ShowWindow(hWndTaskbar,SW_HIDE);
		//	//SetWindowPos(hWndTaskbar, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		//}
		AfxPostMessage(CTR_NAVI_HIDE, 0, 0);
	}
	return bNaviOn;
}

BOOL Navi::IsNaviOn()
{
	return bNaviOn;
}

BOOL Navi::IsNaviOnTop()
{
	return bNaviOnTop && bNaviOn;
}

void Navi::SetHwnd(HWND hwnd)
{
	hWndGRT = hwnd;
	
}

void Navi::ForceCloseNavi()	//强制关闭导航
{
	TerminateProcess(Navi::piNavi.hProcess, 0);
	HideNavi();
	bNaviOn = 0;
}

void Navi::SetNaviVol(int vol)
{
	SendMessage(hWndNavi, WM_SETNAVIVOL, vol, 0);
}