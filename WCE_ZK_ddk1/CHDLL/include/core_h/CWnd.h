#pragma once
//#include "Control.h"

#include <ddraw.h>
#include "GxxView.h"


class Activity;
class CE_CONTROL_API CWnd
{
public:
    CWnd();
    ~CWnd();
    BOOL ShowWindow(int nCmdShow);
    void UpdateWindow();
	HWND GetHWnd(){return m_hWnd;}
	int  GetExitCode(){return m_nExitCode;}
    virtual void  PostNcDestroy();
	virtual Activity *GetWndActivity()=0;
    //static CWnd* PASCAL FromHandlePermanent(HWND hWnd);
    //virtual void OnCreate();

    virtual BOOL Create(LPCTSTR lpszClassName,LPCTSTR lpszWindowName,DWORD dwStyle,const RECT& rect,HWND hWndParent=NULL,UINT nID = 0);
    
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
    HWND	 m_hWnd;
    int      m_nExitCode;      
	RECT     m_WndRect;
   

    void  OnPaint();
	BOOL RegisterWindow(LPCTSTR lpClassName,WNDPROC wnd_poc);
	static void DoAnimation();
;

	//LPDIRECTDRAWCLIPPER DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds,int num_rects,LPRECT clip_list)
    
};
