/* 
#define STRICT 
#include <crtdbg.h> 
#include <tchar.h> 
#include <windows.h> 
*/ 
#include "StdAfx.h" 

////////////////////////////////////////////////////////////////////// 
// Include module headerfile 

#include "SerialEx.h" 

////////////////////////////////////////////////////////////////////// 
// Enable debug memory manager 

#ifdef _DEBUG 

#ifdef THIS_FILE 
#undef THIS_FILE 
#endif 

static const char THIS_FILE[] = __FILE__; 
#define new DEBUG_NEW 

#endif 

////////////////////////////////////////////////////////////////////// 
// Construction/Destruction 
////////////////////////////////////////////////////////////////////// 

CSerialEx::CSerialEx() 
: m_fStopping(false) 
, m_hThread(0) 
{ 
} 

CSerialEx::~CSerialEx() 
{ 
// Check if the thread handle is still there. If so, then we 
// didn't close the serial port. We cannot depend on the 
// CSerial destructor, because if it calls Close then it 
// won't call our overridden Close. 
if (m_hThread) 
{ 
// Close implicitly 
Close(); 
} 
} 

LONG CSerialEx::Open (LPCTSTR lpszDevice, DWORD dwInQueue, DWORD dwOutQueue, bool fStartListener) 
{ 
// Call the base class first 
long lLastError = CSerial::Open(lpszDevice,dwInQueue,dwOutQueue); 
if (lLastError != ERROR_SUCCESS) 
return lLastError; 

// Start the listener thread (only on request) 
if (fStartListener) 
{ 
lLastError = StartListener(); 
if (lLastError != ERROR_SUCCESS) 
return lLastError; 
} 

// Return the error 
return m_lLastError; 
} 

LONG CSerialEx::Close (void) 
{ 
// Stop listener thread (wait until it ends) 
StopListener(INFINITE); 

// Call the base class 
return CSerial::Close(); 
} 

LONG CSerialEx::StartListener (void) 
{ 
// Check if the watcher thread was already running 
if (m_hThread == 0) 
{ 
// Make sure the thread has stopped 
_ASSERTE(!m_fStopping); 

// Start the watcher thread 
DWORD dwThreadId = 0; 
m_hThread = ::CreateThread(0,0,ThreadProc,LPVOID(this),0,&dwThreadId); 
if (m_hThread == 0) 
{ 
// Set the error code and exit 
m_lLastError = ::GetLastError(); 
return m_lLastError; 
} 
} 

// Return the error 
m_lLastError = ERROR_SUCCESS; 
return m_lLastError; 
} 

LONG CSerialEx::StopListener (DWORD dwTimeout) 
{ 
// Check if the thread is running 
if (m_hThread) 
{ 
// Set the flag that the thread must be stopped 
m_fStopping = true; 

// Cancel the pending WaitEvent, but we won't do this using 
// CancelIo. This would break Win95 compatibility and some 
// USB serial dongles cannot handle CancelIo correctly. By 
// setting the event mask again, the call will also be 
// completed before the thread exits. 
SetMask(GetEventMask()); 

// Wait until the watcher thread has stopped 
::WaitForSingleObject(m_hThread,dwTimeout); 

// The thread has stopped 
m_fStopping = false; 

// Close handle to the thread 
::CloseHandle(m_hThread); 
m_hThread = 0; 
} 

// Return the error 
m_lLastError = ERROR_SUCCESS; 
return m_lLastError; 
} 

DWORD WINAPI CSerialEx::ThreadProc (LPVOID lpArg) 
{ 
// Route the method to the actual object 
CSerialEx* pThis = reinterpret_cast<CSerialEx*>(lpArg); 
return pThis->ThreadProc(); 
} 

DWORD CSerialEx::ThreadProc (void) 
{ 
// Use overlapped structure 
LPOVERLAPPED lpOverlapped = 0; 

// Keep looping 
do 
{ 
// Start the WaitEvent (don't need to specify an overlapped structure) 
if (WaitEvent() != ERROR_SUCCESS) 
return m_lLastError; 

// Wait until one of the events happens 
if (!m_fStopping) 
{ 
// Determine the event 
EEvent eEvent = GetEventType(); 

// Obtain the error status during this event 
DWORD dwErrors = 0; 
if (!::ClearCommError(m_hFile,&dwErrors,0)) 
{ 
// Set the internal error code 
m_lLastError = ::GetLastError(); 
} 

// Convert the error 
EError eError = EError(dwErrors); 

// There was a COMM event, which needs handling. We'll call the 
// event handler. We can receive a "zero" event, when the 
// mask or event character has been set. We won't pass this 
// down to the window. 
if (eEvent) 
OnEvent(eEvent,eError); 
} 
} 
while (!m_fStopping); 

// Bye bye 
return 0; 
}