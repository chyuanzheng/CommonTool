#include "stdAfx.h"
#include "CommonWnd.h"
#define  DEF_WNDCLASS    L"CHNiHao"
#include "GXNotify.h"

#include "MsgHandle.h"
/////////////////////////////////////////////////////////////////////////
// CCommonWnd message map and member functions

//SetWindowPos(&CWnd::wndTopMost ,0,0,480,272,SWP_SHOWWINDOW);
const RECT IM_MAIN_RECT = {0,0,800,480};//��ߵ� �˳����� {0,0,480,272};//��ߵ� �˳�����
CWnd *CCommonWnd::m_pWindow=NULL;
CCommonWnd::CCommonWnd ()
{

	static BOOL bReg = 0;

	if(!bReg)//��ֻ֤ע��һ��
	{
		RegisterWindow( DEF_WNDCLASS,CCommonWnd::WndProc );
		bReg = 1;
	}

   if ( Create( DEF_WNDCLASS, L"gfdgs", WS_VISIBLE, IM_MAIN_RECT, NULL))
   {
	   AfxSetDcRect(IM_MAIN_RECT);
	   AfxSetHWND(m_hWnd);
	   m_pWindow = this;
	   SetMsgHandler(RegisterWindowMessage(L"GXNotify"), NotifyHandler, (DWORD)this,this);
   }
   


}
CCommonWnd::~CCommonWnd ()
{

}

DWORD CCommonWnd::NotifyHandler(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{
	DWORD *param = (DWORD*)lParam;
	DWORD param1 = param[0];
	DWORD param2 = param[1];
	delete []param;
	GXNotify::SendNotify(wParam, param1, param2);
	GXNotify::ReleasParam();
	return 0;
}

void CCommonWnd::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CWnd::PostNcDestroy();
	delete this;
}

LRESULT CALLBACK CCommonWnd::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//���ô�����Ļص�����
	if(m_pWindow == NULL)
	{
		return ::DefWindowProc(hWnd, nMsg, wParam, lParam);;
	}

	TMAP_MSG_HANDLES::iterator map_pos;
	map_pos = MsgHandle::mapMsgHandle.find(nMsg);
	if (map_pos != MsgHandle::mapMsgHandle.end())
	{
		T_MSG_HANDLES::iterator it;
		for (it = map_pos->second.begin(); it != map_pos->second.end(); it++)
		{
			(*it).funMsg((*it).pThis, (*it).dwParam, nMsg, wParam, lParam);
		}
		return ::DefWindowProc(hWnd, nMsg, wParam, lParam);
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

Activity * CCommonWnd::GetWndActivity()
{
	return Activity::GetActiveActiviy();

}
