#pragma once

#include "stdAfx.h"
#include "iic.h"

class FMS6502
{
	static const BYTE slaveAddr = 0x06;
	static const BYTE slaveAddr2 = 0x46;
	static const BYTE slaveAddr3 = 0x86;
	static const BYTE slaveAddr4 = 0xC6;
	BOOL WriteIIC(BYTE sub, BYTE data)
	{
		BOOL ret = 0;
		ret = IICWrite4(slaveAddr, sub, data);
		if (ret == 0)
		{
			//MessageBox(NULL, L"6502·ÃÎÊÊ§°Ü", NULL, MB_OK);
		}
		return ret;
	}
	
	BYTE sub1;
	BYTE sub2;
	BYTE sub3;
public:
	FMS6502()
	{
		sub1 = sub2 = sub3 = 0;
	}
	enum INPUT
	{
		INPUT_OFF,
		INPUT_1,
		INPUT_2,
		INPUT_3,
		INPUT_4,
		INPUT_5,
		INPUT_6,
		INPUT_7,
		INPUT_8
	};
	BOOL Output1Select(INPUT input)
	{
		return Output12Select(input, (INPUT)(sub1>>4));
	}
	BOOL Output2Select(INPUT input)
	{
		return Output12Select((INPUT)(sub1&0xF), input);
	}
	BOOL Output3Select(INPUT input)
	{
		return Output34Select(input, (INPUT)(sub2>>4));
	}
	BOOL Output12Select(INPUT input1, INPUT input2)
	{
		BYTE data = input1 | (input2<<4);
		sub1 = data;
//		RETAILMSG(1,(TEXT("FMS6502: sub1=0x%x\r\n"), sub1));
		WriteIIC(4, 0);
		return WriteIIC(0, data);
	}
	BOOL Output34Select(INPUT input1, INPUT input2)
	{
		BYTE data = input1 | (input2<<4);
		sub2 = data;
		WriteIIC(4, 0);
		return WriteIIC(1, data);
	}
	BOOL Output56Select(INPUT input1, INPUT input2)
	{
		BYTE data = input1 | (input2<<4);
		sub3 = data;
		WriteIIC(4, 0);
		return WriteIIC(2, data);
	}
	BOOL ClampControl(BYTE clamp)
	{
		return WriteIIC(3, clamp);
	}
	BOOL GainControl(BYTE gain)
	{
		return WriteIIC(4, gain);
	}
	INPUT GetMainInput()
	{
		return (INPUT)(sub2&0xF);
	}
};