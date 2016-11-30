#pragma once

#include "stdAfx.h"
//#include "../GxxLib/base.h"
#include "GxxString.h"
#include "tinyxml.h"
#define CStdString GxxString


class CreatecConfig
{
	static TiXmlDocument	xmlDoc;
public:
	static BOOL Load(char* szPath);
	static BOOL Load2(char* szPath);
	static void Save();
	static CStdString GetNaviPath();
	static CStdString GetUIXmlPath();
	static void SetNaviPath(CStdString path);
	static void SetUIXmlPath(CStdString path);
	static void GetWheelDefaultValue(int value[12]);
	static CStdString GetAppPath(CStdString appID);
	static CStdString GetAppName(CStdString appID);
	static CStdString GetAppIconPath(CStdString appID);
	static void SetAppPath(CStdString appID, CStdString strPath, CStdString strIconPath = _T(""));
	static CStdString GetLangValue();
	static void SetLangValue(CStdString strValue);
	static void Save3GInfo(CStdString sUserName, CStdString sPwd, CStdString sAPN, CStdString sPhoneNo);
	static void Get3GInfo(CStdString &sUserName, CStdString &sPwd, CStdString &sAPN, CStdString &sPhoneNo);
};

class UIConfig 
{
	static TiXmlDocument xmlDoc;
	static CStdString	sUIPath;
public:
	static BOOL Load(CStdString strPath);
	static CStdString GetUIPath();
	static CStdString GetMainXmlPath();
	static CStdString GetPhoneDlgXmlPath();
	static CStdString GetPreviewPath();
	static CStdString GetSplashPath();
	static CStdString GetPreviewPath(CStdString filepath);
	static COLORREF	  GetBackColor();
	static CStdString GetBackImage();
	static void SetBackColor(COLORREF col);
	static void SetBackImage(CStdString strPath);
//	static void InitFont();
};

class CE_HardwareDll_API CreatecHardware
{
	static BOOL bAuthOK;
public:
	static BOOL IsAuthOK(); 
	static void Init(HWND);
};