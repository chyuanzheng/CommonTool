#pragma once

#include "CWnd.h"
class CE_CONTROL_API CPopupWnd : public CWnd
{
public:
	CPopupWnd ();
	~CPopupWnd ();
protected:
	virtual void PostNcDestroy();
	virtual Activity *GetWndActivity();
private:
	static CWnd *m_pWindow;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
    
};
