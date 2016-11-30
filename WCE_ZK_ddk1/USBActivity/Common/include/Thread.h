#ifndef __THREAD_H__
#define __THREAD_H__

#include <windows.h>

// Thread
// cThread
// by typearc
// typearc@empal.com

class cThread
{
protected:
    HANDLE mhThread;
    DWORD mIDThread;

private:
    static DWORD ThreadProc(LPVOID lpParameter)
    {
        return ((cThread *)lpParameter)->Run();
    };

protected:
    virtual DWORD Run(void)=0;

public:
	cThread()
        : mhThread(NULL)
        , mIDThread(0)
    {
    };

	virtual ~cThread()
    {
    };

    operator HANDLE()const{return mhThread;};

public:
    BOOL Create(DWORD dwCreationFlags=0, DWORD dwStackSize=0, LPSECURITY_ATTRIBUTES lpThreadAttributes=(LPSECURITY_ATTRIBUTES)NULL)
    {
        if( NULL==mhThread )
        {
            mhThread=::CreateThread(lpThreadAttributes, dwStackSize, cThread::ThreadProc, this, dwCreationFlags, &mIDThread);
            if( mhThread )
            {
                return TRUE;
            }
        }

        return FALSE;
    };

public: // wrapping
    BOOL Terminate(DWORD dwExitCode){return ::TerminateThread(mhThread, dwExitCode);};
    BOOL GetExitCode(LPDWORD lpExitCode){return ::GetExitCodeThread(mhThread, lpExitCode);};

    BOOL Priority(int nPriority){return ::SetThreadPriority(mhThread, nPriority);};
    int Priority(void){return ::GetThreadPriority(mhThread);};

    DWORD Resume(void){return ::ResumeThread(mhThread);};
    DWORD Suspend(void){return ::SuspendThread(mhThread);};
};

#endif//__THREAD_H__
