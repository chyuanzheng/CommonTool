#pragma once
//#include "../GxxLib/GxxWindow.h"
#include "GXNotify.h"
#include "HardwareDllModule.h"
#include "GxxString.h"
#include "GxxView.h"
#include "GxxAniLable.h"

class CE_HardwareDll_API TccMediaWnd : public GxxView
{
	BOOL	bAutoTop;
	BOOL	bAlwaysOnBottom;
	BOOL	bEnableVideo;
	
	
	GxxString	sBackupBackImage;
public:
	TccMediaWnd();
	~TccMediaWnd();

	bool GetIsBrake();

	void SetBackColor(COLORREF color);
	void CreateFromXml(TiXmlElement *pXmlElement);
	LRESULT OnLButtonDown(POINT pt);
	LRESULT OnTimer(UINT nID);
	void ShowWindow(int show, int redraw/* =0 */);
	void AutoTopScreen(BOOL b);
	void SetTopScreen(BOOL b);
	void AlwaysOnBottom(BOOL b, BOOL redraw = 1);
	void CloseVideo(BOOL redraw = 1);
	void ShowVideo(BOOL redraw = 1);
	static GxxView* CreateControl();
	static DWORD LButtonDownHandler(GxxView *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);
	static DWORD MouseMoveHandler(GxxView *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);
	
	bool GetVideoEnable();

	UINT	backColor;

	GxxAniLable* pLabelWarnning;

	BOOL	bBrake;				// µ±Ç°É²³µ×´Ì¬
	
	
	DECLARE_NOTIFY_CALLBACK(CarBrakeChange, TccMediaWnd);
};