#pragma once
#include "GxxString.h"
#include "NaviDllModule.h"

class CE_NaviACTIVITY_API Navi
{
	static GxxString			sNaviPath;
	static HWND				hWndNavi;
	static PROCESS_INFORMATION	piNavi;
	static HANDLE				hMonitorNaviThread;		
	static BOOL				bNaviOn;
	static BOOL				bNaviOnTop;
	static HWND				hWndGRT;
public:
	static GxxString GetNaviPath();
	static void SetNaviPath(GxxString str);
	static BOOL IsNaviOn();
	static BOOL StartNavi();
	static DWORD MonitorNaviThread(LPVOID lpParam);
	static BOOL EnumWindows(HWND hWnd, LPARAM lParam);
	static BOOL ShowNavi();
	static BOOL HideNavi();
	static BOOL IsNaviOnTop();
	static void ForceCloseNavi();	//强制关闭导航
	static void SetNaviVol(int vol);

	static void SetNaviOnTop(BOOL b)
	{
		bNaviOnTop = b;
	}
	static void SetHwnd(HWND hwnd);
	static HWND GetNaviHwnd()
	{
		if (bNaviOn)
		{
			if (hWndNavi == 0)
			{
				::EnumWindows(EnumWindows, NULL);
				return hWndNavi;
			}
		}
		return hWndNavi;
	}
	static HANDLE GetNavihProcess()
	{
		return piNavi.hProcess;
	}
	static void SetNaviHwnd(LPTSTR lpcsHwnd)
	{
		if (lpcsHwnd[0] == L'0' && lpcsHwnd[1] == L'x')
		{
			int h = _ttoi(&lpcsHwnd[2]);
			HWND hWnd = (HWND)h;
			if(IsWindow(hWnd))
			{
				hWndNavi = hWnd;
				bNaviOn = 1;
				GetWindowThreadProcessId(hWnd, &piNavi.dwProcessId);
				piNavi.hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,piNavi.dwProcessId);
				DWORD dwThreadID;
				hMonitorNaviThread = (HANDLE)::CreateThread(NULL, 0, MonitorNaviThread, 0, 0, &dwThreadID);
			}
		}
	}
	static void SetNavihProcess(LPTSTR lpcsHwnd)
	{
		if (lpcsHwnd[0] == L'0' && lpcsHwnd[1] == L'x')
		{
			int h = _ttoi(&lpcsHwnd[2]);
			if (h != 0)
			{
				piNavi.hProcess = (HANDLE)h;
				bNaviOn = 1;
				::EnumWindows(EnumWindows, NULL);
				DWORD dwThreadID;
				hMonitorNaviThread = (HANDLE)::CreateThread(NULL, 0, MonitorNaviThread, 0, 0, &dwThreadID);
			}
		}
	}
};