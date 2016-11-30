/* 
#define STRICT 
#include <crtdbg.h> 
#include <tchar.h> 
#include <windows.h> 
*/
//#include "stdafx.h"
#include "StdAfx.h" 

////////////////////////////////////////////////////////////////////// 
// Include module headerfile 

#include "Serial.h" 

////////////////////////////////////////////////////////////////////// 
// Enable debug memory manager 

#ifdef _DEBUG 

#ifdef THIS_FILE 
#undef THIS_FILE 
#endif 

static const char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW 

#endif 

CSerial::CSerial () 
: m_lLastError(ERROR_SUCCESS) 
, m_hFile(0) 
, m_eEvent(EEventNone) 
, m_dwEventMask(0) 
{ 
} 

CSerial::~CSerial () 
{ 
	// If the device is already closed, 
	// then we don't need to do anything. 
	if (m_hFile) 
	{ 
	// Close implicitly 
		Close(); 
	} 
} 

CSerial::EPort CSerial::CheckPort (LPCTSTR lpszDevice) 
{ 
	// Try to open the device 
	HANDLE hFile = ::CreateFile(lpszDevice, 
	GENERIC_READ|GENERIC_WRITE, 
	0, 
	0, 
	OPEN_EXISTING, 
	0, 
	0); 

	// Check if we could open the device 
	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
	// Display error 
		switch (::GetLastError()) 
		{ 
			case ERROR_FILE_NOT_FOUND: 
			// The specified COM-port does not exist 
			return EPortNotAvailable; 

			case ERROR_ACCESS_DENIED: 
			// The specified COM-port is in use 
			return EPortInUse; 

			default: 
			// Something else is wrong 
			return EPortUnknownError; 
		} 
	} 

	// Close handle 
	::CloseHandle(hFile); 

	// Port is available 
	return EPortAvailable; 
} 

LONG CSerial::Open (LPCTSTR lpszDevice, DWORD dwInQueue, DWORD dwOutQueue) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 

	// Check if the port isn't already opened 
	if (m_hFile) 
	{ 
		m_lLastError = ERROR_ALREADY_INITIALIZED; 
		//MessageBox(NULL,TEXT("Port already initialized"),_T("error"),MB_OK); 
		return m_lLastError; 
	} 

	// Open the device 
	m_hFile = ::CreateFile(lpszDevice, 
						GENERIC_READ|GENERIC_WRITE, 
						0, 
						0, 
						OPEN_EXISTING, 
						0, 
						0); 
	if (m_hFile == INVALID_HANDLE_VALUE) 
	{ 
		// Reset file handle 
		m_hFile = 0; 

		// Get error 
		m_lLastError = ::GetLastError(); 
		//Afx//MessageBox(TEXT("Failed to create file")); 
		//MessageBox(NULL,TEXT("Port cannot be opened"),_T("error"),MB_OK); 
		return m_lLastError; 
	} 

	// Setup the COM-port 
	if (dwInQueue || dwOutQueue) 
	{ 
		// Make sure the queue-sizes are reasonable sized. Win9X systems crash 
		// if the input queue-size is zero. Both queues need to be at least 
		// 16 bytes large. 
		_ASSERTE(dwInQueue >= 16); 
		_ASSERTE(dwOutQueue >= 16); 

		if (!::SetupComm(m_hFile,dwInQueue,dwOutQueue)) 
		{ 
			// Get error 
			long lLastError = ::GetLastError(); 

			// Close the port 
			Close(); 

			// Save last error from SetupComm 
			m_lLastError = lLastError; 
			//MessageBox(NULL,TEXT("Failed to setup Port"),_T("error"),MB_OK);
			return m_lLastError; 
		} 
	} 

	// Setup the default communication mask 
	SetMask(); 

	// Non-blocking reads is default 
	SetupReadTimeouts(EReadTimeoutNonblocking); 

	// Return successful 
	return m_lLastError; 
} 

LONG CSerial::Close (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 

	// If the device is already closed, 
	// then we don't need to do anything. 
	if (m_hFile == 0) 
	{ 
		return m_lLastError; 
	} 

	// Close COM port 
	::CloseHandle(m_hFile); 
	m_hFile = 0; 

	// Return successful 
	return m_lLastError; 
} 

LONG CSerial::Setup (EBaudrate eBaudrate, EDataBits eDataBits, EParity eParity, EStopBits eStopBits) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 

	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 

	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = :: GetLastError(); 
		return m_lLastError; 
	} 

	// Set the new data 
	dcb.BaudRate = DWORD(eBaudrate); 
	dcb.ByteSize = BYTE(eDataBits); 
	dcb.Parity = BYTE(eParity); 
	dcb.StopBits = BYTE(eStopBits); 

	// Determine if parity is used 
	dcb.fParity = (eParity != EParNone); 

	// Set the new DCB structure 
	if (!::SetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 

	// Return successful 
	return m_lLastError; 
} 

LONG CSerial::SetEventChar (BYTE bEventChar, bool fAdjustMask) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 

	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 

	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 

	// Set the new event character 
	dcb.EvtChar = char(bEventChar); 

	// Adjust the event mask, to make sure the event will be received 
	if (fAdjustMask) 
	{ 
		// Enable 'receive event character' event. Note that this 
		// will generate an EEventNone if there is an asynchronous 
		// WaitCommEvent pending. 
		SetMask(GetEventMask() | EEventRcvEv); 
		} 
	
	// Set the new DCB structure 
	if (!::SetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Return successful 
	return m_lLastError; 
} 

LONG CSerial::SetMask (DWORD dwEventMask) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	
	// Set the new mask. Note that this will generate an EEventNone 
	// if there is an asynchronous WaitCommEvent pending. 
	if (!::SetCommMask(m_hFile,dwEventMask)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Save event mask and return successful 
	m_dwEventMask = dwEventMask; 
	return m_lLastError; 
} 

LONG CSerial::WaitEvent (DWORD dwTimeout) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	
	// Wait for the COM event 
	if (!::WaitCommEvent(m_hFile,LPDWORD(&m_eEvent),0)) 
	{ 
		// Set the internal error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Return successfully 
	return m_lLastError; 
} 

LONG CSerial::SetupHandshaking (EHandshake eHandshake) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	
	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Set the handshaking flags 
	switch (eHandshake) 
	{ 
	case EHandshakeOff: 
		dcb.fOutxCtsFlow = false; // Disable CTS monitoring 
		dcb.fOutxDsrFlow = false; // Disable DSR monitoring 
		dcb.fDtrControl = DTR_CONTROL_DISABLE; // Disable DTR monitoring 
		dcb.fOutX = false; // Disable XON/XOFF for transmission 
		dcb.fInX = false; // Disable XON/XOFF for receiving 
		dcb.fRtsControl = RTS_CONTROL_DISABLE; // Disable RTS (Ready To Send) 
		break; 
		
	case EHandshakeHardware: 
		dcb.fOutxCtsFlow = true; // Enable CTS monitoring 
		dcb.fOutxDsrFlow = true; // Enable DSR monitoring 
		dcb.fDtrControl = DTR_CONTROL_HANDSHAKE; // Enable DTR handshaking 
		dcb.fOutX = false; // Disable XON/XOFF for transmission 
		dcb.fInX = false; // Disable XON/XOFF for receiving 
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE; // Enable RTS handshaking 
		break; 
		
	case EHandshakeSoftware: 
		dcb.fOutxCtsFlow = false; // Disable CTS (Clear To Send) 
		dcb.fOutxDsrFlow = false; // Disable DSR (Data Set Ready) 
		dcb.fDtrControl = DTR_CONTROL_DISABLE; // Disable DTR (Data Terminal Ready) 
		dcb.fOutX = true; // Enable XON/XOFF for transmission 
		dcb.fInX = true; // Enable XON/XOFF for receiving 
		dcb.fRtsControl = RTS_CONTROL_DISABLE; // Disable RTS (Ready To Send) 
		break; 
		
	default: 
		// This shouldn't be possible 
		_ASSERTE(false); 
		m_lLastError = E_INVALIDARG; 
		return m_lLastError; 
	} 
	
	// Set the new DCB structure 
	if (!::SetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Return successful 
	return m_lLastError; 
} 

LONG CSerial::SetupReadTimeouts (EReadTimeout eReadTimeout) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	
	// Determine the time-outs 
	COMMTIMEOUTS cto; 
	if (!::GetCommTimeouts(m_hFile,&cto)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Set the new timeouts 
	switch (eReadTimeout) 
	{ 
	case EReadTimeoutBlocking: 
		cto.ReadIntervalTimeout = 0; 
		cto.ReadTotalTimeoutConstant = 0; 
		cto.ReadTotalTimeoutMultiplier = 0; 
		break; 
	case EReadTimeoutNonblocking: 
		cto.ReadIntervalTimeout = MAXDWORD; 
		cto.ReadTotalTimeoutConstant = 0; 
		cto.ReadTotalTimeoutMultiplier = 0; 
		break; 
	default: 
		// This shouldn't be possible 
		_ASSERTE(false); 
		m_lLastError = E_INVALIDARG; 
		return m_lLastError; 
	} 
	
	// Set the new DCB structure 
	if (!::SetCommTimeouts(m_hFile,&cto)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Return successful 
	return m_lLastError; 
} 

CSerial::EBaudrate CSerial::GetBaudrate (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return EBaudUnknown; 
	} 
	
	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return EBaudUnknown; 
	} 
	
	// Return the appropriate baudrate 
	return EBaudrate(dcb.BaudRate); 
} 

CSerial::EDataBits CSerial::GetDataBits (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return EDataUnknown; 
	} 
	
	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return EDataUnknown; 
	} 
	
	// Return the appropriate bytesize 
	return EDataBits(dcb.ByteSize); 
} 

CSerial::EParity CSerial::GetParity (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return EParUnknown; 
	} 
	
	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return EParUnknown; 
	} 
	
	// Check if parity is used 
	if (!dcb.fParity) 
	{ 
		// No parity 
		return EParNone; 
	} 
	
	// Return the appropriate parity setting 
	return EParity(dcb.Parity); 
} 

CSerial::EStopBits CSerial::GetStopBits (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return EStopUnknown; 
	} 
	
	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return EStopUnknown; 
	} 
	
	// Return the appropriate stopbits 
	return EStopBits(dcb.StopBits); 
} 

DWORD CSerial::GetEventMask (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return 0; 
	} 
	
	// Return the event mask 
	return m_dwEventMask; 
} 

BYTE CSerial::GetEventChar (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return 0; 
	} 
	
	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return 0; 
	} 
	
	// Set the new event character 
	return BYTE(dcb.EvtChar); 
} 

CSerial::EHandshake CSerial::GetHandshaking (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return EHandshakeUnknown; 
	} 
	
	// Obtain the DCB structure for the device 
	CDCB dcb; 
	if (!::GetCommState(m_hFile,&dcb)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return EHandshakeUnknown; 
	} 
	
	// Check if hardware handshaking is being used 
	if ((dcb.fDtrControl == DTR_CONTROL_HANDSHAKE) && (dcb.fRtsControl == RTS_CONTROL_HANDSHAKE)) 
		return EHandshakeHardware; 
	
	// Check if software handshaking is being used 
	if (dcb.fOutX && dcb.fInX) 
		return EHandshakeSoftware; 
	
	// No handshaking is being used 
	return EHandshakeOff; 
} 

LONG CSerial::Write (const void* pData, size_t iLen, DWORD* pdwWritten, DWORD dwTimeout) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Use our own variable for read count 
	DWORD dwWritten; 
	if (pdwWritten == 0) 
	{ 
		pdwWritten = &dwWritten; 
	} 
	
	// Reset the number of bytes written 
	*pdwWritten = 0; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	// Write the data 
	if (!::WriteFile(m_hFile,pData,iLen,pdwWritten,0)) 
	{ 
		// Set the internal error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Return successfully 
	return m_lLastError; 
} 

LONG CSerial::Write (LPCSTR pString, DWORD* pdwWritten, DWORD dwTimeout) 
{ 
	// Determine the length of the string 
	return Write(pString,strlen(pString),pdwWritten,dwTimeout); 
} 

LONG CSerial::Read (void* pData, size_t iLen, DWORD* pdwRead, DWORD dwTimeout) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Use our own variable for read count 
	DWORD dwRead; 
	if (pdwRead == 0) 
	{ 
		pdwRead = &dwRead; 
	} 
	
	// Reset the number of bytes read 
	*pdwRead = 0; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	
#ifdef _DEBUG 
	// The debug version fills the entire data structure with 
	// 0xDC bytes, to catch buffer errors as soon as possible. 
	memset(pData,0xDC,iLen); 
#endif 
	
	// Read the data 
	if (!::ReadFile(m_hFile,pData,iLen,pdwRead,0)) 
	{ 
		// Set the internal error code 
		m_lLastError = ::GetLastError(); 
		return m_lLastError; 
	} 
	
	// Return successfully 
	return m_lLastError; 
} 

LONG CSerial::Purge() 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	
	if (!::PurgeComm(m_hFile, PURGE_TXCLEAR | PURGE_RXCLEAR)) 
	{ 
		// Set the internal error code 
		m_lLastError = ::GetLastError(); 
	} 
	
	// Return successfully 
	return m_lLastError; 
} 

LONG CSerial::Break (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return m_lLastError; 
	} 
	
	// Set the RS-232 port in break mode for a little while 
	::SetCommBreak(m_hFile); 
	::Sleep(100); 
	::ClearCommBreak(m_hFile); 
	
	// Return successfully 
	return m_lLastError; 
} 

CSerial::EEvent CSerial::GetEventType (void) 
{ 
	// Obtain the event (mask unwanted events out) 
	EEvent eEvent = EEvent(m_eEvent & m_dwEventMask); 
	
	// Reset internal event type 
	m_eEvent = EEventNone; 
	
	// Return the current cause 
	return eEvent; 
} 

CSerial::EError CSerial::GetError (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Check if the device is open 
	if (m_hFile == 0) 
	{ 
		// Set the internal error code 
		m_lLastError = ERROR_INVALID_HANDLE; 
		return EErrorUnknown; 
	} 
	
	// Obtain COM status 
	DWORD dwErrors = 0; 
	if (!::ClearCommError(m_hFile,&dwErrors,0)) 
	{ 
		// Set the internal error code 
		m_lLastError = ::GetLastError(); 
		return EErrorUnknown; 
	} 
	
	// Return the error 
	return EError(dwErrors); 
} 

bool CSerial::GetCTS (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Obtain the modem status 
	DWORD dwModemStat = 0; 
	if (!::GetCommModemStatus(m_hFile,&dwModemStat)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return false; 
	} 
	
	// Determine if CTS is on 
	return (dwModemStat & MS_CTS_ON) != 0; 
} 

bool CSerial::GetDSR (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Obtain the modem status 
	DWORD dwModemStat = 0; 
	if (!::GetCommModemStatus(m_hFile,&dwModemStat)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return false; 
	} 
	
	// Determine if DSR is on 
	return (dwModemStat & MS_DSR_ON) != 0; 
} 

bool CSerial::GetRing (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Obtain the modem status 
	DWORD dwModemStat = 0; 
	if (!::GetCommModemStatus(m_hFile,&dwModemStat)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return false; 
	} 
	
	// Determine if Ring is on 
	return (dwModemStat & MS_RING_ON) != 0; 
} 

bool CSerial::GetRLSD (void) 
{ 
	// Reset error state 
	m_lLastError = ERROR_SUCCESS; 
	
	// Obtain the modem status 
	DWORD dwModemStat = 0; 
	if (!::GetCommModemStatus(m_hFile,&dwModemStat)) 
	{ 
		// Obtain the error code 
		m_lLastError = ::GetLastError(); 
		return false; 
	} 
	
	// Determine if RLSD is on 
	return (dwModemStat & MS_RLSD_ON) != 0; 
}