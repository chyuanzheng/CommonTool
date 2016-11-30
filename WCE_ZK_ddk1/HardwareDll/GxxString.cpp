#include "StdAfx.h"
#include "GxxString.h"


GxxString::GxxString() : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = '\0';
}

GxxString::GxxString(const TCHAR ch) : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = ch;
	m_szBuffer[1] = '\0';
}

GxxString::GxxString(LPCTSTR lpsz, int nLen) : m_pstr(m_szBuffer)
{      
	//ASSERT(!::IsBadStringPtr(lpsz,-1) || lpsz==NULL);
	Assign(lpsz, nLen);
}
GxxString GxxString::TimeStr(int time)
{
	if (time < 0)
	{
		time = 0;
	}
	int hour = time/3600;
	int min = (time-3600*hour)/60;
	int sec = time-hour*3600-min*60;
	if (hour)
	{
		Format(L"%d:%02d:%02d", hour, min ,sec);
	}
	else
	{
		Format(L"%02d:%02d", min, sec);
	}
	return *this;
}
GxxString::GxxString(LPCSTR lpsz, int nLen) : m_pstr(m_szBuffer)
{
	if (!lpsz)
	{
		m_szBuffer[0] = '\0';
		return;
	}
	if (nLen < 0)
	{
		nLen = strlen(lpsz);
	}
	TCHAR *szBuffer = new TCHAR[strlen(lpsz)+1];
	::MultiByteToWideChar(CP_ACP, 0, lpsz, nLen, szBuffer, nLen + 1);
	Assign(szBuffer, nLen);
	delete szBuffer;
}
void GxxString::FromCustomCode(UINT code, LPCSTR lpsz, int nLen /* = -1 */)
{
	if (!lpsz)
	{
		m_szBuffer[0] = '\0';
		return;
	}
	if (nLen < 0)
	{
		nLen = strlen(lpsz);
	}
	int wcharLen = ::MultiByteToWideChar(code, 0, lpsz, nLen, NULL, 0);

	TCHAR *szBuffer = new TCHAR[wcharLen+1];
	memset(szBuffer, 0, 2*(wcharLen+1));
	::MultiByteToWideChar(code, 0, lpsz, nLen, szBuffer, wcharLen);
	Assign(szBuffer, nLen);
	delete szBuffer;
}

void GxxString::UTF8ToUNICODE(LPCSTR lpsz, int nLen)
{
	if (!lpsz)
	{
		m_szBuffer[0] = '\0';
		return;
	}
	if (nLen < 0)
	{
		nLen = strlen(lpsz);
	}
	int wcharLen = ::MultiByteToWideChar(CP_UTF8, 0, lpsz, nLen, NULL, 0);

	TCHAR *szBuffer = new TCHAR[wcharLen+1];
	memset(szBuffer, 0, 2*(wcharLen+1));
	::MultiByteToWideChar(CP_UTF8, 0, lpsz, nLen, szBuffer, wcharLen);
	Assign(szBuffer, nLen);
	delete szBuffer;
}
void GxxString::FromAscii(LPCSTR lpsz, int nLen)
{
	if (!lpsz)
	{
		m_szBuffer[0] = '\0';
		return;
	}
	if (nLen < 0)
	{
		nLen = strlen(lpsz);
	}
	int wcharLen = ::MultiByteToWideChar(CP_ACP, 0, lpsz, nLen, NULL, 0);

	TCHAR *szBuffer = new TCHAR[wcharLen+1];
	memset(szBuffer, 0, 2*(wcharLen+1));
	::MultiByteToWideChar(CP_ACP, 0, lpsz, nLen, szBuffer, wcharLen);
	Assign(szBuffer, nLen);
	delete szBuffer;
}
int GxxString::ToAscii(char *szAscii, int len)
{
	if (szAscii)
	{
		WideCharToMultiByte(CP_ACP, 0, GetData(), GetLength(), szAscii, len, NULL, NULL);
	}
	return GetLength()+1;
}
int GxxString::ToUTF8(char *szUTF8, int len)
{
	if (szUTF8)
	{
		WideCharToMultiByte(CP_UTF8, 0, GetData(), GetLength(), szUTF8, len, NULL, NULL);
	}
	return GetLength()+1;
}
GxxString::GxxString(const GxxString& src) : m_pstr(m_szBuffer)
{
	Assign(src.m_pstr);
}

GxxString::~GxxString()
{
	if( m_pstr != m_szBuffer ) free(m_pstr);
}


int GxxString::GetLength() const
{ 
	return (int) _tcslen(m_pstr); 
}

GxxString::operator LPCTSTR() const 
{ 
	return m_pstr; 
}

void GxxString::Append(LPCTSTR pstr)
{
	int nNewLength = GetLength() + (int) _tcslen(pstr);
	if( nNewLength >= MAX_LOCAL_STRING_LEN ) {
		if( m_pstr == m_szBuffer ) {
			m_pstr = static_cast<LPTSTR>(malloc((nNewLength + 1) * sizeof(TCHAR)));
			_tcscpy(m_pstr, m_szBuffer);
			_tcscat(m_pstr, pstr);
		}
		else {
			m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (nNewLength + 1) * sizeof(TCHAR)));
			_tcscat(m_pstr, pstr);
		}
	}
	else {
		if( m_pstr != m_szBuffer ) {
			free(m_pstr);
			m_pstr = m_szBuffer;
		}
		_tcscat(m_szBuffer, pstr);
	}
}

void GxxString::Assign(LPCTSTR pstr, int cchMax)
{
	if( pstr == NULL ) pstr = _T("");
	cchMax = (cchMax < 0 ? (int) _tcslen(pstr) : cchMax);
	if( cchMax < MAX_LOCAL_STRING_LEN ) {
		if( m_pstr != m_szBuffer ) {
			free(m_pstr);
			m_pstr = m_szBuffer;
		}
	}
	else if( cchMax > GetLength() || m_pstr == m_szBuffer ) {
		if( m_pstr == m_szBuffer ) m_pstr = NULL;
		m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (cchMax + 1) * sizeof(TCHAR)));
	}
	_tcsncpy(m_pstr, pstr, cchMax);
	m_pstr[cchMax] = '\0';
}

bool GxxString::IsEmpty() const 
{ 
	return m_pstr[0] == '\0'; 
}

void GxxString::Empty() 
{ 
	if( m_pstr != m_szBuffer ) free(m_pstr);
	m_pstr = m_szBuffer;
	m_szBuffer[0] = '\0'; 
}

LPCTSTR GxxString::GetData()
{
	return m_pstr;
}

TCHAR GxxString::GetAt(int nIndex) const
{
	return m_pstr[nIndex];
}

TCHAR GxxString::operator[] (int nIndex) const
{ 
	return m_pstr[nIndex];
}   

const GxxString& GxxString::operator=(const GxxString& src)
{      
	Assign(src);
	return *this;
}

const GxxString& GxxString::operator=(LPCTSTR lpStr)
{      
	//ASSERT(!::IsBadStringPtr(lpStr,-1));
	Assign(lpStr);
	return *this;
}

#ifndef _UNICODE

const GxxString& GxxString::operator=(LPCWSTR lpwStr)
{      
	ASSERT(!::IsBadStringPtrW(lpwStr,-1));
	int cchStr = ((int) wcslen(lpwStr) * 2) + 1;
	LPSTR pstr = (LPSTR) _alloca(cchStr);
	if( pstr != NULL ) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);
	Assign(pstr);
	return *this;
}

#endif // _UNICODE

const GxxString& GxxString::operator=(const TCHAR ch)
{
	Empty();
	m_szBuffer[0] = ch;
	m_szBuffer[1] = '\0';
	return *this;
}

GxxString GxxString::operator+(const GxxString& src)
{
	GxxString strTmp = *this;
	strTmp.Append(src);
	return strTmp;
}

GxxString GxxString::operator+(LPCTSTR lpStr)
{
	//ASSERT(!::IsBadStringPtr(lpStr,-1));
	GxxString strTmp = *this;
	strTmp.Append(lpStr);
	return strTmp;
}

const GxxString& GxxString::operator+=(const GxxString& src)
{      
	Append(src);
	return *this;
}

const GxxString& GxxString::operator+=(LPCTSTR lpStr)
{      
	//ASSERT(!::IsBadStringPtr(lpStr,-1));
	Append(lpStr);
	return *this;
}

const GxxString& GxxString::operator+=(const TCHAR ch)
{      
	TCHAR str[] = { ch, '\0' };
	Append(str);
	return *this;
}

bool GxxString::operator == (LPCTSTR str) const { return (Compare(str) == 0); };
bool GxxString::operator != (LPCTSTR str) const { return (Compare(str) != 0); };
bool GxxString::operator <= (LPCTSTR str) const { return (Compare(str) <= 0); };
bool GxxString::operator <  (LPCTSTR str) const { return (Compare(str) <  0); };
bool GxxString::operator >= (LPCTSTR str) const { return (Compare(str) >= 0); };
bool GxxString::operator >  (LPCTSTR str) const { return (Compare(str) >  0); };

void GxxString::SetAt(int nIndex, TCHAR ch)
{
	ASSERT(nIndex>=0 && nIndex<GetLength());
	m_pstr[nIndex] = ch;
}

int GxxString::Compare(LPCTSTR lpsz) const 
{ 
	return _tcscmp(m_pstr, lpsz); 
}

int GxxString::CompareNoCase(LPCTSTR lpsz) const 
{ 
	return _tcsicmp(m_pstr, lpsz); 
}

void GxxString::MakeUpper() 
{ 
	_tcsupr(m_pstr); 
}

void GxxString::MakeLower() 
{ 
	_tcslwr(m_pstr); 
}

GxxString GxxString::Left(int iLength) const
{
	if( iLength < 0 ) iLength = 0;
	if( iLength > GetLength() ) iLength = GetLength();
	return GxxString(m_pstr, iLength);
}

GxxString GxxString::Mid(int iPos, int iLength) const
{
	if( iLength < 0 ) iLength = GetLength() - iPos;
	if( iPos + iLength > GetLength() ) iLength = GetLength() - iPos;
	if( iLength <= 0 ) return GxxString();
	return GxxString(m_pstr + iPos, iLength);
}

GxxString GxxString::Right(int iLength) const
{
	int iPos = GetLength() - iLength;
	if( iPos < 0 ) {
		iPos = 0;
		iLength = GetLength();
	}
	return GxxString(m_pstr + iPos, iLength);
}

int GxxString::Find(TCHAR ch, int iPos /*= 0*/) const
{
	ASSERT(iPos>=0 && iPos<=GetLength());
	if( iPos != 0 && (iPos < 0 || iPos >= GetLength()) ) return -1;
	LPCTSTR p = _tcschr(m_pstr + iPos, ch);
	if( p == NULL ) return -1;
	return p - m_pstr;
}

int GxxString::Find(LPCTSTR pstrSub, int iPos /*= 0*/) const
{
	//ASSERT(!::IsBadStringPtr(pstrSub,-1));
	ASSERT(iPos>=0 && iPos<=GetLength());
	if( iPos != 0 && (iPos < 0 || iPos > GetLength()) ) return -1;
	LPCTSTR p = _tcsstr(m_pstr + iPos, pstrSub);
	if( p == NULL ) return -1;
	return p - m_pstr;
}

int GxxString::ReverseFind(TCHAR ch) const
{
	LPCTSTR p = _tcsrchr(m_pstr, ch);
	if( p == NULL ) return -1;
	return p - m_pstr;
}

int GxxString::Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo)
{
	GxxString sTemp;
	int nCount = 0;
	int iPos = Find(pstrFrom);
	if( iPos < 0 ) return 0;
	int cchFrom = (int) _tcslen(pstrFrom);
	int cchTo = (int) _tcslen(pstrTo);
	while( iPos >= 0 ) {
		sTemp = Left(iPos);
		sTemp += pstrTo;
		sTemp += Mid(iPos + cchFrom);
		Assign(sTemp);
		iPos = Find(pstrFrom, iPos + cchTo);
		nCount++;
	}
	return nCount;
}

int GxxString::Format(LPCTSTR pstrFormat, ...)
{
	GxxString sFormat = pstrFormat;
	//sFormat.ProcessResourceTokens();
	// Do ordinary printf replacements
	// NOTE: Documented max-length of wvsprintf() is 1024
	TCHAR szBuffer[1025] = { 0 };
	va_list argList;
	va_start(argList, pstrFormat);
	int iRet = ::wvsprintf(szBuffer, sFormat, argList);
	va_end(argList);
	Assign(szBuffer);
	return iRet;
}

GxxString GxxString::Ext()
{
	GxxString str = Right(GetLength() - 1 - ReverseFind(_T('.')));
	str.MakeLower();
	return str;
}

GxxString GxxString::Filename()
{
	return Right(GetLength() - 1 - ReverseFind(_T('\\')));
}

GxxString GxxString::EraseExt()
{
	return Left(Find(_T('.')));
}

GxxString GxxString::GetPath()
{
	return Left(ReverseFind(_T('\\')));
}