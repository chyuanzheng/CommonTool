/**********************************************************************
* TCC_COPYRIGHT
*

* END_TCC_COPYRIGHT
***********************************************************************/

#ifndef __DEBUG__H
#define __DEBUG__H

#include <windows.h>

#define tcw_logline				tcw::LogEvent(tcw::_TRACE,_T("[%s %d]\r\n"),_T(__FILE__),__LINE__)
#define tcw_assert(exp)	if(!(exp)) tcw::LogEvent(tcw::_ERROR,_T("assertion failed. (%s) is 0. [%s %d]\r\n"), _T(#exp), _T(__FILE__),__LINE__)
#define tcw_assert_eq(exp1, exp2)	if((exp1) != (exp2)) tcw::LogEvent(tcw::_ERROR,_T("%s(%d) != %s(%d) [%s %d]\r\n"), _T(#exp1), exp1, _T(#exp2), exp2, _T(__FILE__),__LINE__)

#define _CHECK(func) if(!(func)) {LPVOID lpMsgBuf; FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 0, (LPTSTR) &lpMsgBuf, 0, NULL ); tcw::LogEvent(tcw::_ERROR,_T("%s failed(%s) [%s %d]\r\n"), _T(#func), lpMsgBuf, _T(__FILE__),__LINE__);LocalFree( lpMsgBuf );}

namespace tcw{

void SetLogMask(long mask);

void LogEvent(long Mask, LPCTSTR pszFormat, ...);

enum
{
	_TRACE = 		   	0x00000001,
	_WARN  =       	0x00000002,
	_ERROR =       	0x00000004,
	_IO		=       	0x00000008,
	_UG =     		0x00000010,
	_LOG		=					0x00000020,
	_ALARM =     		0x00000040,
	_TEST  =  	  		0x00000080,
	_TIMER =     		0x00000100,
	_CTRAC =     		0x00000200,
	_MAINT =     		0x00000400
};

class FUNC_LOG
{
public:
	FUNC_LOG(const char* funcName){		
		int i;		
		++_nIndent;
		for(i=0;i<_nIndent;++i)
			printf(" ");
		MultiByteToWideChar(GetACP(), 0, funcName, -1, 
			_funcName, sizeof(_funcName)/sizeof(_funcName[0]));		
		LogEvent(_TRACE, _T("+%s\r\n"), _funcName);
	}
	~FUNC_LOG(){
		int i;
		for(i=0;i<_nIndent;++i)
			printf(" ");
		LogEvent(_TRACE, _T("-%s\r\n"), _funcName);
		--_nIndent;
	}
protected:
	TCHAR _funcName[128];
	static int _nIndent;
};
	
}
#endif
