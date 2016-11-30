#include "StdAfx.h"
#include "CWinApp.h"

//初始化静态成员
CWinApp::CWinApp(  )
{
	// initialize CWinThread state
    m_pMainWnd = NULL ;
	m_pPopupWnd = NULL;
	AfxSetApp(this);
	_ASSERT(AfxGetApp() == this);	
}
BOOL CWinApp::InitApplication()
{
    return TRUE;
}

int CWinApp::Run()
{
	//消息循环
    MSG    msg;
	while(GetMessage(&msg, NULL, 0, 0 ))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void CWinApp::ShowPopupWnd( bool b )
{
	if (NULL!=m_pPopupWnd)
	{
		if (b)
		{
			m_pPopupWnd->ShowWindow(SW_SHOW);
		}
		else
		{
			m_pPopupWnd->ShowWindow(SW_HIDE);
		}
		
	}
}
