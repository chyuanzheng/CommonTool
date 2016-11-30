// 用于控制外置功放

#pragma once
#include "CESerial/Serial.h"

class AMP
{
	static CSerial	serial;
	static void CalCheckSum(BYTE *data, int len)
	{
		BYTE sum = 0;
		for (int i=0;i<len-2;i++)
		{
			sum += data[i];
		}
		data[len-2] = sum;
	}
public:
	static void Init()
	{
		serial.Open(L"COM5:");
		serial.Setup();
	}
	static  void SendCMD(BYTE cmdType, BYTE cmdData)
	{
		BYTE data[] = {0xFE, cmdType, 1, cmdData, 0xFF, 0xAA};
		CalCheckSum(data, sizeof(data)/sizeof(data[0]));
		serial.Write(data, sizeof(data)/sizeof(data[0]));
	}
	static void SetVol(int vol);
	static void SetEQ(int eqnum, int eqdata);
	static void SetPower(BOOL bPower);
	static void SetMute(BOOL bMute);
};