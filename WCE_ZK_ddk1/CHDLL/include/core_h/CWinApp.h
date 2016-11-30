#pragma once
 
#include "CWnd.h"
#include "CPopupWnd.h"
//����Ӧ��
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

	//ʵ�����
	HINSTANCE m_hInstance;
	LPTSTR m_lpCmdLine;
	int    m_nCmdShow;
	LPCTSTR m_pszAppName;
};
