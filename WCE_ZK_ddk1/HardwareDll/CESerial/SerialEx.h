#ifndef __SERIAL_EX_H 
#define __SERIAL_EX_H 


////////////////////////////////////////////////////////////////////// 
// Include CSerial base class 

#include "Serial.h" 

class CSerialEx : public CSerial 
{ 
public: 
CSerialEx(); 
virtual ~CSerialEx(); 

// Operations 
public: 
// Open the serial communications for a particular COM port. You 
// need to use the full devicename (i.e. "COM1") to open the port. 
virtual LONG Open (LPCTSTR lpszDevice, DWORD dwInQueue = 0, DWORD dwOutQueue = 0, bool fStartListener = false); 

// Close the serial port. 
virtual LONG Close (void); 

// Start the listener thread 
virtual LONG StartListener (void); 

// Stop the listener thread. Because the other thread might be 
// busy processing data it might take a while, so you can specify 
// a time-out. 
virtual LONG StopListener (DWORD dwTimeout = INFINITE); 

protected: 
// Each opened COM-port uses its own specific thread, which will 
// wait for one of the events to happen. When an event happens, 
// then the client window is send a message informing about the 
// event. 
static DWORD WINAPI ThreadProc (LPVOID lpArg); 
DWORD ThreadProc (void); 

// Event handler 
virtual void OnEvent (EEvent eEvent, EError eError) = 0; 

protected: 
// The WaitEvent method is being used by this class internally 
// and shouldn't be used by client applications. Client 
// application should monior the messages. 
using CSerial::WaitEvent; 

// The event-type is send in the WPARAM of the message and 
// the GetEventType method returns the wrong data, so we'll 
// hide this method for client applications to avoid problems. 
using CSerial::GetEventType; 
using CSerial::GetError; 

protected: 
// Internal attributes 
bool m_fStopping; 
HANDLE m_hThread; 
}; 

#endif // __SERIAL_EX_H