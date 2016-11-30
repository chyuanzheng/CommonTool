#pragma once
#include "CWinApp.h"
#include "Activity.h"
#include <string>
using namespace std;

//表示Activity的分层，暂时分为DLL , MAIN两个层
#define ZKY_MB_OK                       0x00000000L
#define ZKY_MB_OKCANCEL                 0x00000001L
#define ZKY_MB_DIAL_CANCEL                 0x00000002L

//所有的全局函数
//保存程序的全局状态
CE_CONTROL_API void AfxSetApp(CWinApp* app);
CE_CONTROL_API CWinApp*  AfxGetApp();
CE_CONTROL_API void  AfxShowPopupWnd(bool b);

CE_CONTROL_API HINSTANCE AfxGetInstanceHandle( );

CE_CONTROL_API BOOL  AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                 LPTSTR lpCmdLine, int nCmdShow);


CE_CONTROL_API BOOL AfxInvalidateRect(LPCRECT  rc);
CE_CONTROL_API BOOL AfxInvalidatePopupRect(LPCRECT  rc);
CE_CONTROL_API void AfxValidate();

CE_CONTROL_API BOOL  AfxGetWorkPathW(wstring &path);
CE_CONTROL_API BOOL  AfxGetWorkPathA(string &path);
CE_CONTROL_API const char *  AfxAddWorkPathA(const char * addstr);
CE_CONTROL_API BOOL  AfxShowTaskBar(BOOL Show = TRUE);


CE_CONTROL_API void AfxMessageBox(const string &text,UINT time=3,LPCRECT  rc = NULL,bool bIsTextId = true);
CE_CONTROL_API void AfxMessageBox(const string& sid, GxxView* view,DWORD param,  int type);
CE_CONTROL_API void AfxMessageBox(const wstring& text, GxxView* view,DWORD param,  int type);




//CE_CONTROL_API void  AfxFinishActiviy( Activity* const act);

CE_CONTROL_API void  AfxSetHWND(HWND  hwnd);
CE_CONTROL_API HWND  AfxGetHWND();
CE_CONTROL_API void  AfxSetPopupHWND(HWND  hwnd);
CE_CONTROL_API HWND  AfxGetPopupHWND();
CE_CONTROL_API BOOL  AfxPostMessage( UINT nMsg, WPARAM wParam, LPARAM lParam );
CE_CONTROL_API BOOL  AfxSendMessage( UINT nMsg, WPARAM wParam, LPARAM lParam );
CE_CONTROL_API BOOL  AfxGetDeviceBitcount();

CE_CONTROL_API void  AfxSetDcRect(const RECT&  rt);
CE_CONTROL_API const RECT&  AfxGetDcRect();

CE_CONTROL_API int   AfxGetDevWidth();
CE_CONTROL_API int   AfxGetDevHeight();

CE_CONTROL_API void  AfxSetPopupDcRect(const RECT&  rt);
CE_CONTROL_API const RECT&  AfxGetPopupDcRect();
