#pragma once
 
#include "CWnd.h"
#include "CPopupWnd.h"
//窗口应用
class CE_CONTROL_API CWinApp
{
public:
	CWinApp( );
	virtual int Run();
    virtual BOOL InitApplication();
    virtual BOOL InitInstance() = 0;
	virtual BOOL DeInitInstance() = 0;
	void ShowPopupWnd( bool b );
	CWnd* m_pMainWnd;
	CPopupWnd *m_pPopupWnd;

	//实例句柄
	HINSTANCE m_hInstance;
	LPTSTR m_lpCmdLine;
	int    m_nCmdShow;
	LPCTSTR m_pszAppName;
};
