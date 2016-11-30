#pragma once
#include "CWnd.h"

class CCommonWnd : public CWnd
{
public:
    CCommonWnd ();
	~CCommonWnd ();
protected:
	virtual void PostNcDestroy();
	virtual Activity *GetWndActivity();
private:
	static CWnd *m_pWindow;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	static DWORD NotifyHandler(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);
};
