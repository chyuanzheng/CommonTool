#pragma once
#include "CWinApp.h"
#include "Activity.h"

typedef map<string, Activity *>  TM_ACTIVITY;
class AfxModule 
{
public:
	
	static AfxModule*  GetModuleState();

	CWinApp*  GetApp();
	void      SetApp(CWinApp* app);

	HINSTANCE GetInstanceHandle( );

	BOOL  WinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPTSTR lpCmdLine, int nCmdShow);


	BOOL InvalidateRect(LPCRECT  rc);
	BOOL InvalidatePopupRect(LPCRECT  rc);

	void Validate();

	BOOL  GetWorkPathW(wstring &path);
	BOOL  GetWorkPathA(string &path);
	const char * AddWorkPathA(const char * addstr);
	BOOL  ShowTaskBar(BOOL Show = TRUE);


	void  SetHWND(HWND  hwnd);
	HWND  GetHWND();
	void  SetPopupHWND(HWND  hwnd);
	HWND  GetPopupHWND();
	BOOL  PostMessage( UINT nMsg, WPARAM wParam, LPARAM lParam );
	BOOL  SendMessage( UINT nMsg, WPARAM wParam, LPARAM lParam );
	int   GetDeviceBitcount();
	int   GetDevWidth();
	int   GetDevHeight();
	void  SetDcRect(const RECT&  rt);
	const RECT&  GetDcRect();

	void  SetPopupDcRect(const RECT&  rt);
	const RECT&  GetPopupDcRect();

	




private:
	CWinApp* m_pCurrentWinApp;
	HINSTANCE m_hCurrentInstanceHandle;

	wstring m_wWorkPath;
	string m_aWorkPath;//ascci ¹¤×÷Ä¿Â¼
	string m_bufferStr;
	HWND       m_wnd;
	HWND       m_popup_wnd;
	int       m_DeviceBitCount;
	int       m_DeviceHeight;
	int       m_DeviceWidth;
	
	RECT     m_deviceRect;

	static AfxModule* m_s_pInstance;
	RECT  m_devicePopupRect;
	AfxModule();

};