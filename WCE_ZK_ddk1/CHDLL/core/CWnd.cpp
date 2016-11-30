#include "StdAfx.h"
#include "CWnd.h"
#include "SkiaBitmapManager.h"
#include "AnimationManage.h"
//#include "resource.h"

//#include "GxxTimer.h"
#include "TimerManager.h"

CWnd::CWnd()
{
    m_hWnd = NULL;
    m_nExitCode = 0;

}
CWnd::~CWnd()
{
	
}


BOOL CWnd::Create(LPCTSTR lpszClassName,LPCTSTR lpszWindowName,DWORD dwStyle,const RECT& rect,HWND hWndParent,UINT nID)
{

	if( ::IsWindow( m_hWnd ) )
		return FALSE;


    m_hWnd =::CreateWindowEx(NULL, lpszClassName, lpszWindowName, dwStyle,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		hWndParent, NULL, AfxGetInstanceHandle(),NULL);
  
	if (m_hWnd)
	{
		m_WndRect= rect;
		return TRUE;
	}

	
	return FALSE;
}
BOOL CWnd::ShowWindow(int nCmdShow)
	{ _ASSERT(::IsWindow(m_hWnd)); return ::ShowWindow(m_hWnd, nCmdShow); }

void CWnd::UpdateWindow()
	{ _ASSERT(::IsWindow(m_hWnd)); ::UpdateWindow(m_hWnd); }
void CWnd::PostNcDestroy()
{
	// default to nothing
}

BOOL CWnd::RegisterWindow(LPCTSTR lpClassName,WNDPROC wnd_poc)
{
	//为防止此类已经被注册过，先销毁注册
	//::UnregisterClass( lpClassName, GetModuleHandle(NULL) );

	//设置窗体类属性
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = wnd_poc;
	wndclass.lpszClassName = lpClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.hbrBackground = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;

	return RegisterClass(&wndclass);
}

LRESULT CWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	Activity* db = GetWndActivity();
	if (NULL==db)
	{
		return 0;
	}
	switch( message )
	{
         case WM_PAINT:
             OnPaint();
            return 0;
		 case WM_TIMER:
			
			TimerManager::GetInstance()->DoTimerMessage(wParam);
			return 0;
		default:
			break;
	}

	if (db->DealActivityMsg(message, wParam, lParam))
	{
		return 0;
	}
	if(db->DealSelCtrlMsg(message, wParam, lParam))
	{
		return 0;
	}
	if(db->DealCtrlMsg(message, wParam, lParam))
	{
		return 0;
	}
    return ::DefWindowProc(m_hWnd, message, wParam, lParam);
};

void  CWnd::OnPaint()
{
	//int time = GetTickCount();
    PAINTSTRUCT ps;

	HDC hdc = ::BeginPaint( m_hWnd, &ps );


	Activity* db = GetWndActivity();
	ASSERT(NULL!=db);
	
	GxxView *view = db->getSelView();
	if (view&&view->S_OnlyPaintSel)
	{
		db->PaintSelView();
	}
	else
	{
		db->Paint();
		db->PaintSelView();
	}

	
	SkiaBitmapManager::GetInstance()->DrawToDevice(hdc,m_WndRect);

	::EndPaint( m_hWnd, &ps );
	AfxValidate();
	//RETAILMSG(1, (TEXT("Time = %d\r\n"), GetTickCount()-time));
}




