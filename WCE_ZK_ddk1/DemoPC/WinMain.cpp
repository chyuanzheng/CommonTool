// WinDll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdAfx.h"
#include "WinDll.h"
#include "CommonApp.h"
#include "MainPad.h"
CCommonApp myApp;
int WINAPI _tWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{

	return WinMainDll( hInstance,
		 hPrevInstance,
		    lpCmdLine,
		       nCmdShow);
}

