#pragma once
#pragma warning(disable:4244) //仅显示一个
#include "DllDefine.h"
#include "stdAfx.h"
typedef list<string> TL_STR;
typedef list<wstring> TL_WSTR;
class CE_CONTROL_API StrHelp 
{
public:
	static	wstring StringToWString(const string &_src);

	//只拷贝低字节至string中
	static string WStringToString(const wstring &_src);

	static void   StringToSubStr(const string & source, TL_STR &deLStr, CHAR delimiter);
	static void   WStringToSubWStr(const wstring & source, TL_WSTR &deLStr, wchar_t delimiter);
	static bool   WStringEqual(const wstring & ws1,const wstring &ws2 );
	static bool   StringEqual(const string & ws1,const string &ws2 );


	static int  StrToInt(const char *str);
	static RECT StringToRect(const char *str);
	static const char* FormatToString(const char* format,...);
	static bool SaveScreen();
protected:
	static int Hex2Int(const char *hdec, int nlen = -1);
	static int Dec2Int(const char *dec, int nlen = -1);
	static bool IsFileExist(const wstring & path);
	static bool OnScreenSave(string filename);

	
};


