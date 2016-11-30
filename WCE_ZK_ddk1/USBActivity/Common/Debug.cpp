/******************************************************************************
* TCC_COPYRIGHT
*
* END_TCC_COPYRIGHT
******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <tchar.h>
#include "debug.h"

//long g_mask = 0xffff & ~tcw::_TRACE;
long g_mask = tcw::_ERROR;
void tcw::SetLogMask(long mask){g_mask = mask;}

int tcw::FUNC_LOG::_nIndent = -1;

void tcw::LogEvent(long Mask, LPCTSTR pszFormat, ...)
{
	static LPCTSTR DebLevel[]=
	{
		TEXT("TRACE"),
		TEXT("WARNG"),
		TEXT("ERROR"),
		TEXT("INOUT"),
		TEXT("DEBUG"),
		TEXT("LOG  "),
		TEXT("ALARM"),
		TEXT("TEST "),
		TEXT("TIMER"),
		TEXT("CTRAC"),
		TEXT("MAINT")
	};

	int Level=0;
	TCHAR szOutputDebugString[256];

	if( 0!=(Mask&g_mask) )
	{
		while( !(Mask&1) )
		{
			Level++;
			Mask>>=1;
		}

		SYSTEMTIME SystemTime;
		::GetSystemTime(&SystemTime);

//		::wsprintf(szOutputDebugString,
//					TEXT("%02d:%02d:%02d.%03d %08X.%08X> %s :"),
//					SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond, SystemTime.wMilliseconds,
//					::GetCurrentProcessId(), ::GetCurrentThreadId(), DebLevel[Level]);

		va_list vl;
		va_start(vl, pszFormat);
		
		::_vstprintf(&szOutputDebugString[0], pszFormat, vl);
		::OutputDebugString(szOutputDebugString);

		va_end(vl);
	}
}
