#include "stdAfx.h"
#include "CommonWnd.h"
#define  DEF_WNDCLASS    L"dfdf"


/////////////////////////////////////////////////////////////////////////
// CPopupWnd message map and member functions

//SetWindowPos(&CWnd::wndTopMost ,0,0,480,272,SWP_SHOWWINDOW);
const RECT IM_MAIN_RECT = {550,330,700,480};//��ߵ� �˳����� {0,0,480,272};//��ߵ� �˳�����

CWnd *CPopupWnd::m_pWindow=NULL;
CPopupWnd::CPopupWnd ()
{

	static BOOL bReg = 0;

	if(!bReg)//��ֻ֤ע��һ��
	{
		RegisterWindow( DEF_WNDCLASS,CPopupWnd::WndProc );
		bReg = 1;
	}

	if ( Create( DEF_WNDCLASS, L"popup_wnd", WS_POPUP, IM_MAIN_RECT, AfxGetHWND()))
	{
		AfxSetPopupDcRect(IM_MAIN_RECT);
		AfxSetPopupHWND(m_hWnd);
		m_pWindow = this;
	}
}
CPopupWnd::~CPopupWnd ()
{

}
void CPopupWnd::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CWnd::PostNcDestroy();
	delete this;
}

LRESULT CALLBACK CPopupWnd::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//���ô�����Ļص�����
	if(m_pWindow == NULL)
	{
		return ::DefWindowProc(hWnd, nMsg, wParam, lParam);;
	}


	switch( nMsg )
	{
	case WM_ERASEBKGND://����Ҫˢ����
		return 0;
	case WM_EXIT_PROSS:
		return ::DestroyWindow(m_pWindow->GetHWnd());
	case WM_DESTROY://
		PostQuitMessage(m_pWindow->GetExitCode());
		//#ifndef CH_CE_DEBUG
		//	   return 0; 
		//   case WM_NCDESTROY:
		//#endif
		m_pWindow->PostNcDestroy();
		return 0; 
	default:
		break;
	}

	return m_pWindow->WindowProc( nMsg, wParam, lParam );
}

Activity * CPopupWnd::GetWndActivity()
{
	return Activity::GetPopupActiveActiviy();
}
