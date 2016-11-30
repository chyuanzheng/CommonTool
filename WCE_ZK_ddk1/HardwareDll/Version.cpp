#include "stdafx.h"
#include "Version.h"
#include "i2c/chip.h"
#include "windev.h"


string Version::sVer1;
string Version::sVer2;
string Version::sVer3;
string Version::sVer4;
string Version::sVer5;

string Version::CANVersion()
{
	return string();
}

string Version::MCUVersion()
{
	static BYTE year = 0;
	static BYTE month = 0;
	static BYTE day = 0;
	static BYTE time = 0;
	if (year == 0)
	{
		year = chip_mcu.ReadYear();
	}
	if (month == 0)
	{
		int errorTimes = 0;
		while(month < 1 || month > 12)
		{
			if (errorTimes++ > 10)
			{
				break;
			}
			month = chip_mcu.ReadMonth();
			time = month>>4;
			month = month&0x0f;
		}
	}
	if (day == 0)
	{
		int errorTimes = 0;
		while(day < 1 || day > 12)
		{
			if (errorTimes++ > 10)
			{
				break;
			}
			day = chip_mcu.ReadDay();
		}	
	}
	char ver[256] = {0};
	sprintf(ver, "MCU Version : %02d%02d%02d%02d", year, month, day,time);
	//str.Format(L"MCU Version : %02d%02d%02d", year, month, day);
	return ver;
}

string Version::BTModuleVersion()
{
	return string();
}

string Version::APPVersion()
{
	TCHAR sModuleFile[MAX_PATH];
	GetModuleFileName(NULL, sModuleFile, MAX_PATH);
	//WIN32_FIND_DATA fd;
	//HANDLE hFind = FindFirstFile(sModuleFile, &fd);
	//FindClose(hFind);
	//FILETIME ftime = fd.ftLastWriteTime;


	wstring strPath = sModuleFile;
	wstring::size_type nth = strPath.rfind(L'\\');
	strPath = strPath.substr(0,nth);

	FILETIME ftime;
	::memset(&ftime, 0, sizeof(ftime));
 
	{
		WIN32_FIND_DATA fdtemp;
		HANDLE hFindtemp = ::FindFirstFile((strPath + L"\\*.*").c_str(), &fdtemp);
		do 
		{
			if ( !(fdtemp.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			{
				if (fdtemp.ftLastWriteTime.dwHighDateTime>ftime.dwHighDateTime )
				{
					ftime = fdtemp.ftLastWriteTime;
				}
				else if ( (fdtemp.ftLastWriteTime.dwHighDateTime == ftime.dwHighDateTime ) && (fdtemp.ftLastWriteTime.dwLowDateTime > ftime.dwLowDateTime ) )
				{
					ftime = fdtemp.ftLastWriteTime;
				}
			}

		} while(FindNextFile(hFindtemp, &fdtemp));
		FindClose(hFindtemp);
	}

	SYSTEMTIME st;
	FileTimeToSystemTime(&ftime, &st);

	char ver[256] = {0};
	sprintf(ver, "App Version : %d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//str.Format(L"App Version : %d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return ver;
}

string Version::CoreVersion()
{
	// 获取 wince.nls 的修改时间
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(L"\\windows\\wince.nls", &fd);
	FindClose(hFind);
	SYSTEMTIME st;
	FileTimeToSystemTime(&fd.ftLastWriteTime, &st);
	char ver[256] = {0};
	sprintf(ver, "Core Version : %x%x(%d%02d%02d)", fd.ftLastWriteTime.dwHighDateTime, fd.ftLastWriteTime.dwLowDateTime, st.wYear, st.wMonth, st.wDay);
	//str.Format(L"Core Version : %x%x(%d%02d%02d)", fd.ftLastWriteTime.dwHighDateTime, fd.ftLastWriteTime.dwLowDateTime, st.wYear, st.wMonth, st.wDay);
	return ver;
}

string Version::CDVersrion()
{
	return string();
}


BOOL GetStroageID(LPCTSTR szDisk, char* sID)
{

	return TRUE;
}
string Version::HardwareSerial()
{
	return string();
}

string Version::NaviSoftVersion()
{
	return string();
}

string Version::BootVersion()
{
	static int version = ReadBootVersion();
	char ver[256] = {0};
	sprintf(ver, "Boot Version : %02d%02d%02d%02d", version>>24, (version>>16)&0xFF, (version>>8)&0xFF, version&0xFF);
	return ver;
}

string Version::NaviDataVersion1()
{
	return "Navi Version : no version";
}

string Version::NaviDataVersion2()
{
	return sVer2;
}

string Version::NaviDataVersion3()
{
	return sVer3;
}

string Version::NaviDataVersion4()
{
	return sVer4;
}

string Version::NaviDataVersion5()
{
	return sVer5;
}