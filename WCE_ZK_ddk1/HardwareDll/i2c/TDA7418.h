#pragma once

#include "../stdafx.h"
#include "iic.h"

static const unsigned char VolTable[]=
{
	0x7F, // mute// 0
	0x50, // ------------ 1
	//0x4F,
	//0x4E,
	//0x4D,
	//0x4C,
	//0x4B,
	0x4A, // ------------ 2	
	//0x49,
	//0x48,
	//0x47,
	//0x46,
	//0x45,
	0x44, // ------------ 3
	//0x43,
	//0x42,
	//0x41,
	//0x40,
	//0x3F,
	0x3E, // ------------ 4
    //0x3D,
	//0x3C,
	//0x3B,
	//0x3A,
	//0x39,
	0x38, // -40dB -------- 5
	//0x37, // -39dB
	0x36, // -38dB -------- 6
	//0x35, // -37dB
	0x34, // -36dB -------- 7
	//0x33, // -35dB
	0x32, // -34dB -------- 8
	0x31, // -33dB
	0x30, // -32dB
	0x2F, // -31dB
	0x2E, // -30dB// 30
	0x2D, // -29dB
	0x2C, // -28dB
	0x2B, // -27dB
	0x2A, // -26dB
	0x29, // -25dB
	0x28, // -24dB
	0x27, // -23dB
	0x26, // -22dB
	0x25, // -21dB
	0x24, // -20dB// 10
	0x23, // -19dB
	0x22, // -18dB
	0x21, // -17dB
	0x20, // -16dB
	0x1F, // -15dB
	0x1E, // -14dB
	0x1D, // -13dB
	0x1C, // -12dB
	0x1B, // -11dB
	0x1A, // -10dB// 20

	0x19, // -9dB
	0x18, // -8dB
	0x17, // -7dB
	0x16, // -6dB
	0x15, // -5dB
	0x14, // -4dB
	0x13, // -3dB
	0x12, // -2dB
	0x11, // -1dB
	0x00, // +0dB// 30
	0x01, // +1dB
	0x02, // +2dB
	0x03, // +3dB
	0x04, // +4dB
	0x05, // +5dB
	0x06, // +6dB
	0x07, // +7dB
	0x08, // +8dB
	0x09, // +9dB
};

static const unsigned char MixVolTable[]=
{
	0x7F, // mute// 0
	0x2D, // -29dB
	0x2C, // -28dB
	0x2B, // -27dB
	0x2A, // -26dB
	0x29, // -25dB
	0x28, // -24dB
	0x27, // -23dB
	0x26, // -22dB
	0x25, // -21dB
	0x24, // -20dB// 10
	0x23, // -19dB
	0x22, // -18dB
	0x21, // -17dB
	0x20, // -16dB
	0x1F, // -15dB
	0x1E, // -14dB
	0x1D, // -13dB
	0x1C, // -12dB
	0x1B, // -11dB
	0x1A, // -10dB// 20
	0x19, // -9dB
	0x18, // -8dB
	0x17, // -7dB
	0x16, // -6dB
	0x15, // -5dB
	0x14, // -4dB
	0x13, // -3dB
	0x12, // -2dB
	0x11, // -1dB
	0x00, // +0dB// 30
	0x01, // +1dB
	0x02, // +2dB
	0x03, // +3dB
	0x04, // +4dB
	0x05, // +5dB
	0x06, // +6dB
	0x07, // +7dB
	0x08, // +8dB
	0x09, // +9dB
};

static const unsigned char SubVolTable[]=
{
	0x16, // -6dB
	0x15, // -5dB
	0x14, // -4dB
	0x13, // -3dB
	0x12, // -2dB
	0x11, // -1dB
	0x00, // +0dB// 30
	0x01, // +1dB
	0x02, // +2dB
	0x03, // +3dB
	0x04, // +4dB
	0x05, // +5dB
	0x06, // +6dB
	0x07, // +7dB
	0x08,
	0x09,
	0x0A,
	0x0B,
	0x0C,
	0x0D,
	0x0E,
	0x0F,
};

static const unsigned char BasTreTable[]=
{
	////0x0F, // -15dB
	//0x0E, // -14dB
	////0x0D, // -13dB
	//0x0C, // -12dB    
	////0x0B, // -11dB
	//0x0A, // -10dB
	////0x09, // -9dB
	//0x08, // -8dB
	0x07, // -7dB
	0x06, // -6dB
	0x05, // -5dB
	0x04, // -4dB
	0x03, // -3dB
	0x02, // -2dB
	0x01, // -1dB
	0x10, // +0dB
	0x11, // +1dB
	0x12, // +2dB
	0x13, // +3dB
	0x14, // +4dB
	0x15, // +5dB
	0x16, // +6dB
	0x17, // +7dB
	//0x18, // +8dB
	////0x19, // +9dB
	//0x1A, // +10dB
	////0x1B, // +11dB
	//0x1C, //  +12dB
	////0x1D, // +13dB
	//0x1E, // +14dB
	////0x1F, // +15dB
};

class TDA7418
{
	
	static const BYTE slaveAddr = 0x88;              // ƒ¨»œµÿ÷∑Œ™0x88(8Œªµÿ÷∑£©
	int	attenLF;
	int attenRF;
	int b6DBOn;

public:
	int volume;
	/// “Ù‘¥—°‘Ò
	enum AudioSwitch { Stereo1, Stereo2, Stereo3, Stereo4, NONE };
	/// “Ùœ‰—°‘Ò
	enum SpeakerAtten { LF, RF, LR, RR };
	/// µÕ“Ù∏ﬂ“Ù—°‘Ò
	enum BassTreble { Bass, Treble };

	enum
	{
		SUB_MainSourceSelector = 0x60,
		SUB_MainLoudness,
		SUB_Volume,
		SUB_Treble,
		SUB_Middle,
		SUB_Bass,
		SUB_MBSelect,
		SUB_SpeakerLF,
		SUB_SpeakerRF,
		SUB_SpeakerLR,
		SUB_SpeakerRR,
		SUB_SubwooferAtten,
		SUB_SoftMute,
		SUB_Testing
	};

	BOOL WriteIIC(BYTE subaddr, BYTE data)
	{
		BOOL ret = IICWrite4(slaveAddr, subaddr, data);
		return ret;
	}
	enum
	{
		QD,
		SE1,
		SE2,
		SE3,
		SE
	};
	BOOL MainSelector(BYTE source, BYTE inputgain = 0, BYTE autozero = 0)
	{
		BYTE data = (source & 0x7) | (inputgain<<3 & 0xF<<3) | (autozero<<7);
		return WriteIIC(SUB_MainSourceSelector, data);
	}
	void SetLoudness(BYTE atten, BYTE centerfreq=0, BYTE hightboost=0, BYTE softstep=0)
	{
		BYTE data = atten | (centerfreq<<5) | (hightboost<<6) | (softstep<<7);
		WriteIIC(SUB_MainLoudness, data);
	}
	BOOL Volume(BYTE vol, BYTE softstep = 0)
	{
		volume = vol;
		vol = VolTable[vol];
		BYTE data = vol | (softstep<<7);
		BYTE dataMix = VolTable[volume] | (softstep<<7);
		BOOL ret =  WriteIIC(SUB_Volume, data);
		return ret;
	}
	BOOL VolumeMute(BOOL bMute)
	{
		BYTE data = 0;
		if(bMute)
		{
			data = 0x76;
		}
		else
		{
			data = 0x77;
		}
		BOOL ret =  WriteIIC(SUB_SoftMute, data);
		return ret;
	}
	void SetTreble(int trebel, BYTE centerfreq=0, BYTE ref=1)
	{
		trebel = trebel+7;
		trebel = BasTreTable[trebel];
		BYTE data = trebel | centerfreq<<5 | ref<<7;
		WriteIIC(SUB_Treble, data);
	}
	void SetMiddle(int middle, BYTE qfactor=0, BYTE softstep=0)
	{
		BYTE data = middle | qfactor<<5 | softstep<<7;
		WriteIIC(SUB_Middle, data);
	}
	void SetBass(BYTE bass, BYTE qfactor=0, BYTE softstep=0)
	{
		bass = bass+7;
		bass = BasTreTable[bass];
		BYTE data = bass | qfactor<<5 | softstep<<7;
		WriteIIC(SUB_Bass, data);
	}
	void SetLR(int atten, BYTE softstep=0)
	{
		//RETAILMSG(1, (TEXT("LR = %d\r\n"), atten));
		atten = SubVolTable[atten];
		BYTE data = atten | (softstep<<7);
		WriteIIC(SUB_SpeakerLR, data);
	}
	void SetRR(int atten, BYTE softstep=0)
	{
		//RETAILMSG(1, (TEXT("RR = %d\r\n"), atten));
		atten = SubVolTable[atten];
		BYTE data = atten | (softstep<<7);
		WriteIIC(SUB_SpeakerRR, data);
	}
	void SetLF(int atten, BYTE softstep=0)
	{
		//RETAILMSG(1, (TEXT("LF = %d\r\n"), atten));
		attenLF = atten;
		atten = SubVolTable[atten+6*b6DBOn];
		BYTE data = atten | (softstep<<7);
		WriteIIC(SUB_SpeakerLF, data);
	}
	void SetRF(int atten, BYTE softstep=0)
	{
		//RETAILMSG(1, (TEXT("RF = %d\r\n"), atten));
		attenRF = atten;
		atten = SubVolTable[atten+6*b6DBOn]; 
		BYTE data = atten | (softstep<<7);
		WriteIIC(SUB_SpeakerRF, data);
	}
	void SetFront6DB(int bOn)
	{
		b6DBOn = bOn;
		int atten;
		atten = SubVolTable[attenLF + 6*bOn];
		BYTE data = atten | (0<<7);
		WriteIIC(SUB_SpeakerLF, data);
		atten = SubVolTable[attenRF + 6*bOn]; 
		data = atten | (0<<7);
		WriteIIC(SUB_SpeakerRF, data);
	}
	void Init()
	{
		BYTE data[14] = {
			0x00,
			0xE0,
			0x55,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x0F,
			0x77,
			0x00
		};
		BOOL ret = 1;
		for (int i=0;i<14;i++)
		{
			ret &= WriteIIC(i, data[i]);
		}
		MainSelector(SE1, 0, 0);
		SetLoudness(0);
		Volume(20);
		if (!ret)
		{
			MessageBox(NULL, L"≥ı ºªØ“Ù∆µ–æ∆¨ ß∞‹", L"ERROR", MB_OK);
		}
	}
};