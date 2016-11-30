#include <windows.h>
#include "Thread.h"

DWORD cThread::ThreadProc(LPVOID lpParameter)
{
    return ((cThread *)lpParameter)->Run();
}
///////////////////////////////////////////////////////////////////////////////
// cThread
cThread::cThread():
mhThread(NULL),
mIDThread(0)
{
}

cThread::~cThread()
{
}

BOOL cThread::Create(DWORD dwCreationFlags, DWORD dwStackSize, LPSECURITY_ATTRIBUTES lpThreadAttributes)
{
    if( NULL==mhThread )
    {
        mhThread=::CreateThread(lpThreadAttributes, dwStackSize, cThread::ThreadProc, this, dwCreationFlags, &mIDThread);
        if( mhThread ) 
            return TRUE;
    }

    return FALSE;
}
