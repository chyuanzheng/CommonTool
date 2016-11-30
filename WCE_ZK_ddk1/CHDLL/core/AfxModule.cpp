#include "StdAfx.h"
#include "SkiaBitmapManager.h"
#include "GXCreateControls.h"
#include "StrHelp.h"
#include "AfxModule.h"




AfxModule* AfxModule::m_s_pInstance= NULL;
AfxModule* AfxModule::GetModuleState()
{
    if(AfxModule::m_s_pInstance == NULL)
    {
        AfxModule::m_s_pInstance = new AfxModule;
    }
    return AfxModule::m_s_pInstance;
}


CWinApp* AfxModule::GetApp()
{
    return AfxModule::m_s_pInstance->m_pCurrentWinApp;
}


void AfxModule::SetApp( CWinApp* app )
{
	AfxModule::m_s_pInstance->m_pCurrentWinApp=app;
}

BOOL  AfxModule::WinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	 LPTSTR lpCmdLine, int nCmdShow)
{
	_ASSERT(hPrevInstance == NULL);
	// set resource handles
	AfxModule* pModuleState = AfxModule::GetModuleState();
	pModuleState->m_hCurrentInstanceHandle = hInstance;
	CWinApp* pApp = AfxModule::GetApp();
	if (pApp != NULL)
	{
		// Windows specific initialization (not done if no CWinApp)
		pApp->m_hInstance = hInstance;
		hPrevInstance; // Obsolete.
		pApp->m_lpCmdLine = lpCmdLine;
		pApp->m_nCmdShow = nCmdShow;
	}
    else
    {
        return FALSE;
    }

	return TRUE;
}

HINSTANCE AfxModule::GetInstanceHandle( )
{
    AfxModule* pModuleState = AfxModule::GetModuleState();
	return pModuleState->m_hCurrentInstanceHandle ;
}



 BOOL  AfxModule::GetWorkPathW(wstring &path)
{
	AfxModule* pModuleState = AfxModule::GetModuleState();
	if (pModuleState->m_wWorkPath.length()>0)
	{
		path = pModuleState->m_wWorkPath;
		return TRUE;
	}

	WCHAR tWorkPath[MAX_PATH];
	if(::GetModuleFileName(   NULL,   tWorkPath,   MAX_PATH   ) == 0)
	{
		return FALSE;
	}
	WCHAR   *p   =   wcsrchr(   tWorkPath,   '\\'   );     
	*(p+1)   =   0;  
	pModuleState->m_wWorkPath = path = tWorkPath;
	return TRUE;
}

 BOOL  AfxModule::GetWorkPathA(string &path)
{
	AfxModule* pModuleState = AfxModule::GetModuleState();
	if (pModuleState->m_aWorkPath.length()>0)
	{
		path = pModuleState->m_aWorkPath;
		return TRUE;
	}

	wstring wpath;
	AfxModule::GetWorkPathW(wpath);
	pModuleState->m_aWorkPath = path = StrHelp::WStringToString(wpath);
	return TRUE;

}

const char * AfxModule::AddWorkPathA( const char * addstr )
{
	ASSERT(NULL!=addstr);
	GetWorkPathA(m_bufferStr);
	m_bufferStr += addstr;
	return m_bufferStr.c_str();
}

 BOOL AfxModule::ShowTaskBar( BOOL Show /*= TRUE*/ )
{
#ifdef  CH_CE_DEBUG 
	//Òþ²ØÈÎÎñÀ¸
	HWND hTaskBar;
	hTaskBar = ::FindWindow(TEXT("HHTaskBar"), NULL);  //ËÑÑ°ÈÎÎñÀ¸¾ä±ú
	if (NULL == hTaskBar)
	{
		hTaskBar = ::FindWindow(_T("Tray"), NULL);
	}
	if(NULL != hTaskBar)
	{
		if (Show)
		{
			::ShowWindow(hTaskBar, SW_SHOW); //Òþ²Ø
		}
		else
		{
			::ShowWindow(hTaskBar, SW_HIDE); //Òþ²Ø
		}
	}
#endif
	return TRUE;
}


 BOOL AfxModule::InvalidatePopupRect( LPCRECT rc )
 {
	 ::InvalidateRect(AfxModule::m_s_pInstance->m_popup_wnd,rc,FALSE);

	 RECT rect;
	 if (NULL==rc)
	 {
		 rect = AfxGetPopupDcRect();
	 }else{
		 rect = *rc;
	 }
	 SkiaBitmapManager::GetInstance()->InvalidRect(&rect);
	 return TRUE;
 }

 BOOL AfxModule::InvalidateRect( LPCRECT rc )
{

	::InvalidateRect(AfxModule::m_s_pInstance->m_wnd,rc,FALSE);
	RECT rect;
	if (NULL==rc)
	{
		rect = AfxGetDcRect();;
	}else{
		rect = *rc;
	}
	SkiaBitmapManager::GetInstance()->InvalidRect( &rect);
	return TRUE;
}

 void AfxModule::Validate()
{
	SkiaBitmapManager::GetInstance()->Validate();
}
 void AfxModule::SetPopupHWND(HWND  hwnd)
 {
	AfxModule::m_s_pInstance->m_popup_wnd = hwnd;
 }
 HWND  AfxModule::GetPopupHWND()
 {
	return AfxModule::m_s_pInstance->m_popup_wnd ;
 }
 void AfxModule::SetHWND( HWND hwnd )
{
	AfxModule::m_s_pInstance->m_wnd = hwnd;
}

 HWND AfxModule::GetHWND()
{
	return AfxModule::m_s_pInstance->m_wnd ;
}

 BOOL AfxModule::PostMessage( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	return ::PostMessage(AfxModule::m_s_pInstance->m_wnd, nMsg, wParam, lParam);
}

 BOOL AfxModule::SendMessage( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	return ::SendMessage(AfxModule::m_s_pInstance->m_wnd, nMsg, wParam, lParam);
}

 void AfxModule::SetDcRect( const RECT& rt )
{
	AfxModule::m_s_pInstance->m_deviceRect=rt;
}

const RECT& AfxModule::GetDcRect()
{
	return AfxModule::m_s_pInstance->m_deviceRect;
}
void AfxModule::SetPopupDcRect( const RECT& rt )
{
	AfxModule::m_s_pInstance->m_devicePopupRect=rt;
}

const RECT& AfxModule::GetPopupDcRect()
{
	return AfxModule::m_s_pInstance->m_devicePopupRect;
}

AfxModule::AfxModule()
{
	m_pCurrentWinApp=NULL;
	m_wWorkPath.clear();

	HDC dc = ::GetDC(NULL);
	m_DeviceBitCount = ::GetDeviceCaps(dc, BITSPIXEL); 
	m_DeviceHeight  = ::GetDeviceCaps(dc, VERTRES); 
	m_DeviceWidth = ::GetDeviceCaps(dc, HORZRES); 

	::ReleaseDC(NULL, dc);

}

int AfxModule::GetDeviceBitcount()
{
	return m_DeviceBitCount;
}

int AfxModule::GetDevWidth()
{
	return AfxModule::m_s_pInstance->m_DeviceWidth;
}

int AfxModule::GetDevHeight()
{
	return AfxModule::m_s_pInstance->m_DeviceHeight;
}

