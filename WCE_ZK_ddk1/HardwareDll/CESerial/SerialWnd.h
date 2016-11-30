#ifndef __SERIAL_WND_H 
#define __SERIAL_WND_H 


////////////////////////////////////////////////////////////////////// 
// Include CSerialEx base class 

#include "SerialEx.h" 


class CSerialWnd : public CSerialEx 
{ 
// Construction 
public: 
CSerialWnd(); 
virtual ~CSerialWnd(); 

// Operations 
public: 
// Open the serial communications for a particular COM port. You 
// need to use the full devicename (i.e. "COM1") to open the port. 
virtual LONG Open (LPCTSTR lpszDevice, HWND hwndDest, UINT nComMsg=WM_NULL, LPARAM lParam=0, DWORD dwInQueue = 0, DWORD dwOutQueue = 0); 

// Close the serial port. 
virtual LONG Close (void); 

protected: 
// Event handler that is called when 
virtual void OnEvent (EEvent eEvent, EError eError); 

public: 
// Default Serial notification message 
static const UINT mg_nDefaultComMsg; 

protected: 
// Internal attributes 
HWND m_hwndDest; 
UINT m_nComMsg; 
LONG m_lParam; 
}; 

#endif // __SERIAL_WND_H