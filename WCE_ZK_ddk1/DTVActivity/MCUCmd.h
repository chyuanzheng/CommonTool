#pragma once
#include "stdafx.h"
#include "CESerial/Serial.h"

class MCUCmd
{
	CSerial serial;
public:
	MCUCmd()
	{
		serial.Open(L"COM3:");
		serial.Setup(CSerial::EBaud19200);
	}
	void WriteCMD(BYTE sub, BYTE cmd)
	{
		BYTE data[3] = {0, sub, cmd};
		serial.Write(data, 3);
	}
};

extern MCUCmd mcuCMD;