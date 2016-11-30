////////////////////////////////////////////////////////////////////// 
// Include the standard header files 

/* 
#define STRICT 
#include <crtdbg.h> 
#include <tchar.h> 
#include <windows.h> 
*/ 
#include "StdAfx.h" 

////////////////////////////////////////////////////////////////////// 
// Include module headerfile 

#include "SerialWnd.h" 

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
// Code 

// Register the standard CSerialWnd COM message 
const UINT CSerialWnd::mg_nDefaultComMsg = ::RegisterWindowMessage(_T("CSerialWnd_DefaultComMsg")); 


CSerialWnd::CSerialWnd() 
: m_hwndDest(0) 
, m_nComMsg(WM_NULL) 
, m_lParam(0) 
{ 
} 

CSerialWnd::~CSerialWnd() 
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

LONG CSerialWnd::Open (LPCTSTR lpszDevice, HWND hwndDest, UINT nComMsg, LPARAM lParam, DWORD dwInQueue, DWORD dwOutQueue) 
{ 
// Call the base class first 
long lLastError = CSerialEx::Open(lpszDevice,dwInQueue,dwOutQueue); 
if (lLastError != ERROR_SUCCESS) 
return lLastError; 

// Save the window handle, notification message and user message 
m_hwndDest = hwndDest; 
m_nComMsg = nComMsg?nComMsg:mg_nDefaultComMsg; 
m_lParam = lParam; 

// Start the listener thread 
lLastError = StartListener(); 
if (lLastError != ERROR_SUCCESS) 
{ 
// Close the serial port 
Close(); 

// Return the error-code 
m_lLastError = lLastError; 
return m_lLastError; 
} 

// Return the error 
m_lLastError = ERROR_SUCCESS; 
return m_lLastError; 
} 

LONG CSerialWnd::Close (void) 
{ 
// Reset all members 
m_hwndDest = 0; 
m_nComMsg = WM_NULL; 

// Call the base class 
return CSerialEx::Close(); 
} 

void CSerialWnd::OnEvent (EEvent eEvent, EError eError) 
{ 
// Post message to the client window 
::PostMessage(m_hwndDest,m_nComMsg,MAKEWPARAM(eEvent,eError),LPARAM(m_lParam)); 
}