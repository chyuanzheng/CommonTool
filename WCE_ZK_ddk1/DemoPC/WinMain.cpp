// WinDll.cpp : ���� DLL Ӧ�ó������ڵ㡣
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

