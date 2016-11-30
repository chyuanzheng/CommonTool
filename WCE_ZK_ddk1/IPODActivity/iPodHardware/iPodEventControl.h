
#ifndef _IPOD_EVENTCONTROL_H_
#define _IPOD_EVENTCONTROL_H_


extern DWORD iPodEventControlThread(LPVOID pData);

extern HANDLE iPod_StartEventControlThread( HANDLE hWnd, DWORD *pThreadID );

extern BOOL iPod_StopEventControlThread( HANDLE hThread, DWORD ThreadID );

#endif
