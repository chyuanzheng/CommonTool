#pragma once

#include "stdAfx.h"
#include "iic.h"

class NJW1110
{
	static const BYTE slaveAddr = 0x94;
	static const BYTE slaveAddr2 = 0x96;
	BOOL WriteIIC(BYTE sub, BYTE data)
	{
		return IICWrite4(slaveAddr, sub, data);
	}
public:
	enum INPUT
	{
		INPUT_MUTE,
		INPUT_1,
		INPUT_2,
		INPUT_3,
		INPUT_4,
		INPUT_5,
		INPUT_6,
		INPUT_7,
		INPUT_8,
		INPUT_9
	};
	enum GAIN
	{
		GAIN_00,
		GAIN_30,
		GAIN_35,
		GAIN_40,
		GAIN_45,
		GAIN_50,
		GAIN_55,
		GAIN_60,
		GAIN_65,
		GAIN_70,
		GAIN_75,
		GAIN_80
	};
private:
	INPUT curInput1;
	INPUT curInput2;
	INPUT curInput3;
	GAIN  curGain1;
	GAIN  curGain2;
	GAIN  curGain3;
	BOOL  curMute;
public:
	NJW1110()
	{
		curMute = 0;
		curGain3 = GAIN_00;
	}
	BOOL Out1Select(INPUT input, GAIN gain = GAIN_00)
	{
		curInput1 = input;
		curGain1 = gain;
		BYTE data = input | (gain<<4);
		BOOL ret = WriteIIC(0, data);
		//RETAILMSG(1,(TEXT("NJW1110: data=0x%x, ret=%d\r\n"), data, ret));
		return ret;
	}
	BOOL Out2Select(INPUT input, GAIN gain = GAIN_00)
	{
		curInput2 = input;
		curGain2 = gain;
		if (curMute)
		{
			return 0;
		}
		BYTE data = input | (gain<<4);
		return WriteIIC(1, data);
	}
	BOOL Out3Gain(GAIN gain)
	{
		curGain3 = gain;
		BYTE data = curInput3 | (curGain3<<4);
		return WriteIIC(2, data);
	}
	BOOL Out3Mute(BOOL mute)
	{
		if (mute)
		{
			Out3Select(INPUT_MUTE);
		}
		else
		{
			Out3Select(curInput3);
		}
		return 1;
	}
	BOOL Out3Select(INPUT input, GAIN gain = GAIN_50)
	{
		if (input != INPUT_MUTE)
		{
			curInput3 = input;
		}
		curGain3 = gain;
		if (curMute)
		{
			return 0;
		}
		BYTE data = input | (curGain3<<4);
		return WriteIIC(2, data);
	}
	void Mute3(int bMute)
	{
		if (bMute)
		{
			Out3Select(INPUT_MUTE);
		}
		else
		{
			Out3Select(curInput3);
		}
	}
	void Mute(int bMute)
	{
		curMute = bMute;
		if (bMute)
		{
			Out1Select(INPUT_MUTE);
			Out2Select(INPUT_MUTE);
			Out3Select(INPUT_MUTE);
		}
		else
		{
			Out1Select(curInput1, curGain1);
			Out2Select(curInput2, curGain2);
			Out3Select(curInput3);
		}
	}
};