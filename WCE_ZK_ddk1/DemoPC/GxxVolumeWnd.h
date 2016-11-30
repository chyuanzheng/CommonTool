#pragma once
#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "XmlDef.h"
class GxxVolumeWnd: public GxxPicture
{
public:
	GxxVolumeWnd(void);
	~GxxVolumeWnd(void);
	static GxxVolumeWnd* This;
	
	virtual Activity *GetWndActivity(){return NULL;}
	static LRESULT CALLBACK WndProc0(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void CreateWnd(TCHAR* szClassName, DWORD dwStyle, int x, int y, int width, int height,
		HWND hParentWnd, HINSTANCE hInstance);

	BOOL setContentView( const CHAR* layout );
	void ShowWindow(int nCmdShow);

	void Paint();

	HWND m_hWnd;
private:
	
};
