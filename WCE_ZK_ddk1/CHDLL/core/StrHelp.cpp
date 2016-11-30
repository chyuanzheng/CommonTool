#include "StrHelp.h"

string StrHelp::WStringToString( const wstring &_src)
{

	int nBufSize = WideCharToMultiByte(CP_ACP, 0, _src.c_str(),-1, NULL, 0, 0, FALSE);

	char *szBuf = new char[nBufSize];

	WideCharToMultiByte(CP_ACP, 0, _src.c_str(),-1, szBuf, nBufSize, 0, FALSE);
	string strRet(szBuf);

	delete []szBuf;
	szBuf = NULL;

	return strRet;
	//{
	//	string str(wstr.length(), ' ');
	//	copy(wstr.begin(), wstr.end(), str.begin());
	//	return str; 
	//}
}

wstring StrHelp::StringToWString( const string &_src )
{
	//计算字符串 string 转成 wchar_t 之后占用的内存字节数
	int nBufSize = MultiByteToWideChar(CP_UTF8,0,_src.c_str(),-1,NULL,0); 

	//为 wsbuf 分配内存 BufSize 个字节
	wchar_t *wsBuf = new wchar_t[nBufSize];

	//转化为 unicode 的 WideString
	MultiByteToWideChar(CP_UTF8,0,_src.c_str(),-1,wsBuf,nBufSize); 

	wstring wstrRet(wsBuf);

	delete []wsBuf;
	wsBuf = NULL;

	return wstrRet;
	//{
	//	wstring wstr(str.length(),L' ');
	//	copy(str.begin(), str.end(), wstr.begin());
	//	return wstr; 
	//}
}

void StrHelp::StringToSubStr( const string & source, TL_STR &deLStr, CHAR delimiter )
{
	string t_source = source;
	int nlocal=0;
	while (t_source.size()>0)
	{
		nlocal = t_source.find_first_of(delimiter);
		if (nlocal >= 0)
		{
			deLStr.push_back( t_source.substr(0,nlocal) );
			t_source = t_source.substr(nlocal + 1);
		}
		else
		{
			deLStr.push_back(t_source);
			break;
		}	
	}

}


void StrHelp::WStringToSubWStr( const wstring & source, TL_WSTR &deLStr, wchar_t delimiter )
{
	wstring t_source = source;
	int nlocal=0;
	while (t_source.size()>0)
	{
		nlocal = t_source.find_first_of(delimiter);
		if (nlocal >= 0)
		{
			deLStr.push_back( t_source.substr(0,nlocal) );
			t_source = t_source.substr(nlocal + 1);
		}
		else
		{
			deLStr.push_back(t_source);
			break;
		}	
	}
}


int StrHelp::Dec2Int( const char *dec,int nlen )
{
	const char *p = dec;
	int i, x = 1;
	int s = 0;

	if (nlen == -1)
	{
		nlen = strlen(dec);
	}
	p += nlen;
	for(i=0;i < nlen;i++)
	{
		p--;
		if(*p >= 48 && *p <= 57)
			s += (*p - 48)*x;
		else
		{
			if (*p == '-'&&i==nlen-1)
			{
				s = -s;
				return s;
			}
			ASSERT(0);//转换错误
		}

		x *= 10;
	}

	return s;
}


int StrHelp::Hex2Int(const  char *hdec,int nlen)
{
	const char *p = hdec;
	int i, x = 1;
	int s = 0;

	if (nlen == -1)
	{
		 nlen = strlen(hdec);
	}
	p += nlen;
	for(i=0;i < nlen ;i++)
	{
		p--;
		if(*p >= 48 && *p <= 57)
			s += (*p - 48)*x;
		else
		{
			switch(*p)
			{
			case 'A':
			case 'a':
				s += 10*x;
				break;
			case 'B':
			case 'b':
				s += 11*x;
				break;
			case 'C':
			case 'c':
				s += 12*x;
				break;
			case 'D':
			case 'd':
				s += 13*x;
				break;
			case 'E':
			case 'e':
				s += 14*x;
				break;
			case 'F':
			case 'f':
				s += 15*x;
				break;
			default:
				ASSERT(0);//转换错误
			}
		}

		x *= 16;
	}

	return s;
} 

RECT StrHelp::StringToRect( const char *str )
{
	ASSERT(NULL!= str);
	RECT rect;
	TL_STR tlstr;
	StringToSubStr(str,tlstr,'-');
	ASSERT(tlstr.size()==4);
	TL_STR::iterator pos = tlstr.begin();
	rect.left = Dec2Int((*pos).c_str());
	++pos;
	rect.top = Dec2Int((*pos).c_str());
	++pos;
	rect.right = Dec2Int((*pos).c_str());
	++pos;
	rect.bottom = Dec2Int((*pos).c_str());

	return rect;

}

int StrHelp::StrToInt( const char *str )
{

	int retInt = 0;
	ASSERT(NULL!= str);
	const char *p = str;
	const int nlen = strlen(str);
	bool isneg = false;
	int i = 0;
	if (*p == '-')
	{
		isneg = true; 
		++p;
		++i;
	}
	if ( ( nlen > 1) && 
		 *p++ == '0' && 
		(*p == 'x'|| *p == 'X') )
	{
		i += 2; 
		retInt = Hex2Int(str+i,nlen-i);
	}
	else 
	{
		retInt = Dec2Int(str+i,nlen-i);
	}
	
	if (isneg)
	{
		return -retInt;
	}
	return retInt;
}

bool StrHelp::WStringEqual( const wstring & ws1,const wstring &ws2 )
{
	int nsize = ws1.size();
	if (nsize != ws2.size())
	{
		return false;
	}
	for (int i=0;i< nsize;++i)
	{
		if (tolower(ws1[i])!=tolower(ws2[i]))
		{
			return false;
		}
	}
	return true;
}

bool StrHelp::StringEqual( const string & ws1,const string &ws2 )
{
	int nsize = ws1.size();
	if (nsize != ws2.size())
	{
		return false;
	}
	for (int i=0;i< nsize;++i)
	{
		if (tolower(ws1[i])!=tolower(ws2[i]))
		{
			return false;
		}
	}
	return true;
}



const char* StrHelp::FormatToString(const char* format,...)
{
	static char s_text[128];

	va_list argList;
	va_start(argList, format);

	vsprintf(s_text,format,argList);
	va_end(argList);
	return s_text;
}

bool StrHelp::OnScreenSave(string filename)
{
	HDC  hScrDC, hMemDC;        
	int  width, height;

	//the pointer will save all pixel point's color value
	BYTE  *lpBitmapBits = NULL;

	//creates a device context for the screen device
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

	//get the screen point size
	width = GetDeviceCaps(hScrDC, HORZRES);
	height = GetDeviceCaps(hScrDC, VERTRES);

	//creates a memory device context (DC) compatible with the screen device(hScrDC) 
	hMemDC = CreateCompatibleDC(hScrDC);

	//initialise the struct BITMAPINFO for the bimap infomation，
	//in order to use the function CreateDIBSection
	//on wince os, each pixel stored by 24 bits(biBitCount=24)
	//and no compressing(biCompression=0)
	BITMAPINFO RGB24BitsBITMAPINFO;
	ZeroMemory(&RGB24BitsBITMAPINFO, sizeof(BITMAPINFO));
	RGB24BitsBITMAPINFO.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	RGB24BitsBITMAPINFO.bmiHeader.biWidth = width;
	RGB24BitsBITMAPINFO.bmiHeader.biHeight = height;
	RGB24BitsBITMAPINFO.bmiHeader.biPlanes = 1;
	RGB24BitsBITMAPINFO.bmiHeader.biBitCount = 24;

	//use the function CreateDIBSection and SelectObject
	//in order to get the bimap pointer : lpBitmapBits
	HBITMAP directBmp = CreateDIBSection(hMemDC, (BITMAPINFO*)&RGB24BitsBITMAPINFO,
		DIB_RGB_COLORS, (void **)&lpBitmapBits, NULL, 0);
	HGDIOBJ previousObject = SelectObject(hMemDC, directBmp);

	// copy the screen dc to the memory dc
	BitBlt(hMemDC, 0, 0, width, height, hScrDC, 0, 0, SRCCOPY);

	//if you only want to get the every pixel color value,
	//you can begin here and the following part of this function will be unuseful;
	//the following part is in order to write file;

	//bimap file header in order to write bmp file
	BITMAPFILEHEADER bmBITMAPFILEHEADER;
	ZeroMemory(&bmBITMAPFILEHEADER, sizeof(BITMAPFILEHEADER));
	bmBITMAPFILEHEADER.bfType = 0x4d42;  //bmp 
	bmBITMAPFILEHEADER.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmBITMAPFILEHEADER.bfSize = bmBITMAPFILEHEADER.bfOffBits + ((width*height)*3); ///3=(24 / 8)

	//write into file
	FILE *mStream = NULL;
	if((mStream = fopen(filename.c_str(), "wb")))
	{ 
		//write bitmap file header
		fwrite(&bmBITMAPFILEHEADER, sizeof(BITMAPFILEHEADER), 1, mStream);
		//write bitmap info
		fwrite(&(RGB24BitsBITMAPINFO.bmiHeader), sizeof(BITMAPINFOHEADER), 1, mStream);
		//write bitmap pixels data
		fwrite(lpBitmapBits, 3*width*height, 1, mStream);
		//close file
		fclose(mStream);
		return true;
	}

	//delete
	DeleteObject(hMemDC);
	DeleteObject(hScrDC);
	DeleteObject(directBmp);
	DeleteObject(previousObject);
	return false;

}
bool StrHelp::SaveScreen()
{
	static int index = 0;
	wstring str = L"\\Storage Card\\__ALPINEXXXDO.NET";
	wstring str2 = L"\\Storage Card\\__snapshot";
	if (IsFileExist(str) && IsFileExist(str2))
	{
		string strName = StrHelp::FormatToString("\\Storage Card\\__snapshot\\screen%d.bmp", index++);
		return OnScreenSave(strName);
	}
	return false;
}

bool StrHelp::IsFileExist(const wstring & path)
{
	WIN32_FIND_DATA FindFileData;
	wstring  strPath = path;
	HANDLE hFind  = ::FindFirstFile(strPath.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return false;
	} 
	FindClose(hFind);
	return true;
}

