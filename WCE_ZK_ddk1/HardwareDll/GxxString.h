#pragma once
#include "windows.h"
#include "HardwareDllModule.h"
class CE_HardwareDll_API  GxxString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	GxxString();
	GxxString(const TCHAR ch);
	GxxString(const GxxString& src);
	GxxString(LPCTSTR lpsz, int nLen = -1);
	GxxString(LPCSTR lpsz, int nLen = -1);
	void UTF8ToUNICODE(LPCSTR lpsz, int nLen = -1);
	int ToAscii(char *szAscii, int len=MAX_PATH);
	int ToUTF8(char *szUTF8, int len=MAX_PATH);
	void FromAscii(LPCSTR lpsz, int nLen = -1);
	void FromCustomCode(UINT code, LPCSTR lpsz, int nLen  = -1 );
	virtual ~GxxString();

	

	void Empty();
	int GetLength() const;
	bool IsEmpty() const;
	TCHAR GetAt(int nIndex) const;
	void Append(LPCTSTR pstr);
	void Assign(LPCTSTR pstr, int nLength = -1);
	LPCTSTR GetData();



	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const GxxString& operator=(const GxxString& src);
	const GxxString& operator=(const TCHAR ch);
	const GxxString& operator=(LPCTSTR pstr);
#ifndef _UNICODE
	const GxxString& GxxString::operator=(LPCWSTR lpwStr);
#endif
	GxxString operator+(const GxxString& src);
	GxxString operator+(LPCTSTR pstr);
	const GxxString& operator+=(const GxxString& src);
	const GxxString& operator+=(LPCTSTR pstr);
	const GxxString& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const;
	int CompareNoCase(LPCTSTR pstr) const;

	void MakeUpper();
	void MakeLower();

	GxxString Left(int nLength) const;
	GxxString Mid(int iPos, int nLength = -1) const;
	GxxString Right(int nLength) const;

	int Find(TCHAR ch, int iPos = 0) const;
	int Find(LPCTSTR pstr, int iPos = 0) const;
	int ReverseFind(TCHAR ch) const;
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

	GxxString Ext();	// 获取后缀名
	GxxString Filename();	// 获取文件名
	GxxString EraseExt();	// 删除后缀名
	GxxString GetPath();	// 获取路径名
	GxxString TimeStr(int time);

	int __cdecl Format(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};