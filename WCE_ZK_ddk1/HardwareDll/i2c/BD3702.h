#pragma once

#include "stdAfx.h"
#include "iic.h"

// multi gain
enum
{
	MUTEDB = 0xFF,
	_79DB = 0xCF,
	_78DB = 0xCE,
	_77DB = 0xCD,
	_76DB = 0xCC,
	_75DB = 0xCB,
	_74DB = 0xCA,
	_73DB = 0xC9,
	_72DB = 0xC8,
	_71DB = 0xC7,
	_70DB = 0xC6,
	_69DB = 0xC5,
	_68DB = 0xC4,
	_67DB = 0xC3,
	_66DB = 0xC2,
	_65DB = 0xC1,
	_64DB = 0xC0,
	_63DB = 0xBF,
	_62DB = 0xBE,
	_61DB = 0xBD,
	_60DB = 0xBC,
	_59DB = 0xBB,
	_58DB = 0xBA,
	_57DB = 0xB9,
	_56DB = 0xB8,
	_55DB = 0xB7,
	_54DB = 0xB6,
	_53DB = 0xB5,
	_52DB = 0xB4,
	_51DB = 0xB3,
	_50DB = 0xB2,
	_49DB = 0xB1,
	_48DB = 0xB0,
	_47DB = 0xAF,
	_46DB = 0xAE,
	_45DB = 0xAD,
	_44DB = 0xAC,
	_43DB = 0xAB,
	_42DB = 0xAA,
	_41DB = 0xA9,
	_40DB = 0xA8,
	_39DB = 0xA7,
	_38DB = 0xA6,
	_37DB = 0xA5,
	_36DB = 0xA4,
	_35DB = 0xA3,
	_34DB = 0xA2,
	_33DB = 0xA1,
	_32DB = 0xA0,
	_31DB = 0x9F,
	_30DB = 0x9E,
	_29DB = 0x9D,
	_28DB = 0x9C,
	_27DB = 0x9B,
	_26DB = 0x9A,
	_25DB = 0x99,
	_24DB = 0x98,
	_23DB = 0x97,
	_22DB = 0x96,
	_21DB = 0x95,
	_20DB = 0x94,
	_19DB = 0x93,
	_18DB = 0x92,
	_17DB = 0x91,
	_16DB = 0x90,
	_15DB = 0x8F,
	_14DB = 0x8E,
	_13DB = 0x8D,
	_12DB = 0x8C,
	_11DB = 0x8B,
	_10DB = 0x8A,
	_9DB = 0x89,
	_8DB = 0x88,
	_7DB = 0x87,
	_6DB = 0x86,
	_5DB = 0x85,
	_4DB = 0x84,
	_3DB = 0x83,
	_2DB = 0x82,
	_1DB = 0x81,
	DB0 = 0x80,
	DB1 = 0x7F,
	DB2 = 0x7E,
	DB3 = 0x7D,
	DB4 = 0x7C,
	DB5 = 0x7B,
	DB6 = 0x7A,
	DB7 = 0x79,
	DB8 = 0x78,
	DB9 = 0x77,
	DB10 = 0x76,
	DB11 = 0x75,
	DB12 = 0x74,
	DB13 = 0x73,
	DB14 = 0x72,
	DB15 = 0x71
};
static BYTE FadeTabel[]=
{
	DB0,
	_3DB,
	_6DB,
	_9DB,
	_12DB,
	_15DB,
	_16DB,
	_17DB,
	_18DB,
	_19DB,
	_20DB,
	_21DB,
	_22DB,
	_23DB,
	_24DB,
	_25DB,
	_26DB,


};
//
//static BYTE VolTabel[]=
//{
//	MUTEDB,
//	_60DB,
//	_55DB,
//	_52DB,
//	_51DB,
//	_50DB,
//	_49DB ,
//	_48DB ,
//	_47DB ,
//	_46DB ,
//	_45DB ,
//	_44DB ,
//	_43DB ,
//	_42DB ,
//	_41DB ,
//	_40DB ,
//	_39DB ,
//	_38DB ,
//	_37DB ,
//	_36DB ,
//	_35DB ,
//	_34DB ,
//	_33DB ,
//	_32DB ,
//	_31DB ,
//	_30DB ,
//	_29DB ,
//	_28DB ,
//	_27DB ,
//	_26DB ,
//	_25DB ,	// 30
//	_24DB ,
//	_23DB ,
//	_22DB ,
//	_21DB ,
//	_20DB ,
//	_19DB ,
//	_18DB ,
//	_17DB ,
//	_16DB ,
//	_15DB ,	// 40
//	_14DB ,
//	_13DB ,
//	_12DB ,
//	_11DB ,
//	_10DB ,
//	_9DB,
//	_8DB,
//	_7DB,
//	_6DB,
//	_5DB,
//	_4DB,
//	_3DB,
//	_2DB,
//	_1DB,
//	DB0,
//	DB1,
//	DB2,
//	DB3,
//	DB4,
//	DB5,
//};

static BYTE VolTabel[]=
{
	MUTEDB,
	_44DB ,
	_37DB ,
	_32DB ,
	_28DB ,
	_25DB ,
	_23DB ,
	_21DB ,
	_20DB ,
	_19DB ,
	_18DB ,	// 10
	_17DB ,
	_16DB ,
	_15DB ,	
	_14DB ,
	_13DB ,
	_12DB ,
	_11DB ,	
	_10DB ,
	_9DB ,
	_8DB , // 20
	_7DB ,
	_6DB ,
	_5DB ,
	_4DB ,
	_3DB,
	_2DB,	
	_1DB,
	DB0,
	DB1,
	DB2,  //30
	DB3,
	DB4,
	DB5,
	DB6,
	DB7,
	DB8,	
	DB9,
	DB10,
	DB11,
	DB12, //40
	DB13,
	DB14,
	DB15,
};

static BYTE SubwTabel[]=
{
	MUTEDB,
	_24DB ,
	_23DB ,
	_22DB ,
	_21DB ,
	_20DB ,
	_19DB ,
	_18DB ,
	_17DB ,
	_16DB ,
	_15DB ,
	_14DB ,
	_13DB ,
	_12DB ,
	_11DB ,
	_10DB ,
	_9DB,
	_8DB,
	_7DB,
	_6DB,
	_5DB,
	_4DB,
	_3DB,
	_2DB,
	_1DB,
	DB0,
	DB1,
	DB2,
	DB3,
	DB4,
	DB5,
};
static BYTE MixTabel[]=
{
	MUTEDB,
	_10DB ,
	_9DB ,
	_8DB ,
	_7DB ,
	_6DB ,
	_5DB ,
	_5DB ,
	_3DB ,
	_2DB ,
	_1DB ,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB0,
	DB1,
	DB2,
	DB3,
	DB4,
	DB5,
	DB6 ,
	DB7 ,
	DB7 , 
	DB7 ,
	DB7 ,
	DB7 ,
	DB7 ,
	DB7 ,
	DB7 ,
	DB7 ,
};

class BD3702
{
	static const BYTE slaveAddr = 0x80;
public:
	enum
	{
		SUB_INITSETUP1 = 0x01,
		SUB_INITSETUP2 = 0x02,
		SUB_INITSETUP3 = 0x03,
		SUB_INPUT = 0x05,
		SUB_INPUTGAIN = 0x06,
		SUB_VOLUME = 0x20,
		SUB_LF = 0x28,
		SUB_RF = 0x29,
		SUB_LR = 0x2A,
		SUB_RR = 0x2B,
		SUB_SUBWOOFER = 0x2C,
		SUB_MIXING = 0x30,
		SUB_BASSSTUP = 0x41,
		SUB_MIDDLESTUP = 0x44,
		SUB_TREBLESTUP = 0x47,
		SUB_BASSGAIN = 0x51,
		SUB_MIDDLEGAIN = 0x54,
		SUB_TREBLEGAIN = 0x57,
		SUB_LOUDNESS = 0x75,
		SUB_INITSETUP4 = 0x90,
		SUB_TESTMODE1 = 0xF0,
		SUB_TESTMODE2 = 0xF1,
		SUB_RESET = 0xFE
	};
	// init1
	enum
	{
		SWTIMEMUTE06,
		SWTIMEMUTE10,
		SWTIMEMUTE14,
		SWTIMEMUTE32
	};
	enum
	{
		SWTIMEGAIN47,
		SWTIMEGAIN71,
		SWTIMEGAIN112,
		SWTIMEGAIN144
	};
	enum
	{
		ADSW_OFF,
		ADSW_ON
	};
	// init2
	enum
	{
		SUBWLPF_OFF,
		SUBLPF_55,
		SUBLPF_85,
		SUBLPF_120
	};
	enum
	{
		SUBWOUT_LPF,
		SUBWOUT_FRONT,
		SUBWOUT_REAR,
	};
	enum
	{
		LEVELMETER_HOLD,
		LEVELMETER_RESET
	};
	// init2
	enum
	{
		LOUDFO_250,
		LOUDFO_400,
		LOUDFO_800,
	};
	// input selector
	enum
	{
		MODE_A,
		MODE_B,
		MODE_C,
		MODE_D,
		MODE_E1 = 10,
		MODE_E2 = 11,
		MODE_DDIFF = 6,
		MODE_EFULLDIFF = 8,
		MODE_SHORT = 9
	};
	enum
	{
		FDBIASTYPE_NEG,
		FDBIASTYPE_BIAS
	};
	// input gain
	enum
	{
		INPUTMUTE_OFF,
		INPUTMUTE_ON
	};

	// mixing gain

	// bass
	enum
	{
		BASSQ_05,
		BASSQ_10,
		BASSQ_15,
		BASSQ_20
	};
	enum
	{
		BASSFO_60,
		BASSFO_80,
		BASSFO_100,
		BASSFO_120
	};
	// middle
	enum
	{
		MIDQ_075,
		MIDQ_100,
		MIDQ_125,
		MIDQ_150
	};
	enum
	{
		MIDFO_500,
		MIDFO_1000,
		MIDFO_1500,
		MIDFO_2500
	};
	// treble
	enum
	{
		TREBLEQ_075,
		TREBLEQ_125
	};
	enum
	{
		TREBELFO_075,
		TREBELFO_100,
		TREBELFO_125,
		TREBELFO_150
	};
	// bass middle treble gain
	enum
	{
		BMT_BOOST,
		BMT_CUT
	};
	// loudness
	enum
	{
		LOUDHICUT1,
		LOUDHICUT2,
		LOUDHICUT3,
		LOUDHICUT4
	};
private:
	int curInputGain;
	int curInput;
	int curVolume;

	int saveInputGain;
	int saveInput;
	int saveVolume;

	int saveInputGain2;
	int saveInput2;
	int saveVolume2;
	int save2;

	int subwOn;

	int mixMute;

public:
	void SaveStatus()
	{
		saveInputGain = curInputGain;
		saveInput = curInput;
		saveVolume = curVolume;
	}
	void SaveStatus2()
	{
		save2 = 1;
		saveInputGain2 = curInputGain;
		saveInput2 = curInput;
		saveVolume2 = curVolume;
	}
	void RestoreStatus()
	{
		InputGain(0, saveInputGain);
		InputSelect(saveInput);
		Volume(saveVolume);
	}
	void RestoreStatus2()
	{
		if (save2)
		{
			InputGain(0, saveInputGain2);
			InputSelect(saveInput2);
			Volume(saveVolume2);
			save2 = 0;
		}
		
	}
	BOOL WriteIIC(BYTE subaddr, BYTE data)
	{
		BOOL ret = IICWrite4(slaveAddr, subaddr, data);
		return ret;
	}
	BOOL InitSetup1(BYTE adsw = ADSW_ON, BYTE swtime_gain = SWTIMEGAIN112, BYTE swtime_mute = SWTIMEMUTE06)
	{
		BYTE data = 0x44 | (adsw<<7) | (swtime_gain<<4) | (swtime_mute);
		return WriteIIC(SUB_INITSETUP1, data);
	}
	BOOL InitSetup2(BYTE lm_reset = LEVELMETER_HOLD, BYTE subw_out = SUBWOUT_LPF, BYTE subw_lpf = SUBLPF_120)
	{
		BYTE data = 0x0 | (lm_reset<<6) | (subw_out<<4) | subw_lpf;
		return WriteIIC(SUB_INITSETUP2, data);
	}
	BOOL InitSetup3(BYTE loud_fo = LOUDFO_250)
	{
		BYTE data = 0x1 | (loud_fo<<3);
		return WriteIIC(SUB_INITSETUP3, data);
	}
	BOOL InputSelect(BYTE input, BYTE fulldiff_type = FDBIASTYPE_BIAS)
	{
		BYTE data = 0x0 | (fulldiff_type<<7) | input;
		curInput = input;
		if (curInput == MODE_E2)
		{
			MixerVol(0);	// for ce mixer
		}
		return WriteIIC(SUB_INPUT, data);
	}
	BOOL InputGain(BYTE mute, BYTE gain)
	{
		curInputGain = gain;
		BYTE data = 0x0 | (mute<<7) | gain;
		return WriteIIC(SUB_INPUTGAIN, data);
	}
	BOOL MainVolDown()
	{
		if (curInput == MODE_E2)
		{
			return 0;
		}
		int vol = curVolume-12>0?curVolume-12:0;
		return WriteIIC(SUB_VOLUME, VolTabel[vol]);
	}
	BOOL MainVolUp()
	{
		if (curInput == MODE_E2)
		{
			return 0;
		}
		return WriteIIC(SUB_VOLUME, VolTabel[curVolume]);
	}
	BOOL Volume(BYTE vol)
	{
		if (curInput == MODE_E2)
		{
			MixerVol(0);	// for ce mixer
		}
		else if (!mixMute)
		{
			MixerVol(vol);
		}
		curVolume = vol;
		if (subwOn)
		{
			SetSubW(vol/2);
		}
		return WriteIIC(SUB_VOLUME, VolTabel[vol]);
	}
	BOOL SetLF(BYTE gain)
	{
		return WriteIIC(SUB_LF, FadeTabel[gain]);
	}
	BOOL SetRF(BYTE gain)
	{
		return WriteIIC(SUB_RF, FadeTabel[gain]);
	}
	BOOL SetLR(BYTE gain)
	{
		return WriteIIC(SUB_LR, FadeTabel[gain]);
	}
	BOOL SetRR(BYTE gain)
	{
		return WriteIIC(SUB_RR, FadeTabel[gain]);
	}
	BOOL SetSubW(BYTE gain)
	{
		return WriteIIC(SUB_SUBWOOFER, SubwTabel[gain]);
	}
	BOOL MixerVol(BYTE gain)
	{
		RETAILMSG(1, (TEXT("mixer vol = %d\r\n"), gain));
		return WriteIIC(SUB_MIXING,  MixTabel[gain]);
		return 0;
	}
	BOOL BassSetup(BYTE bassfo, BYTE bassq)
	{
		BYTE data = 0x0 | (bassfo<<4) | bassq;
		return WriteIIC(SUB_BASSSTUP, data);
	}
	BOOL MiddSetup(BYTE midfo, BYTE midq)
	{
		BYTE data = 0x0 | (midfo<<4) | midq;
		return WriteIIC(SUB_MIDDLESTUP, data);
	}
	BOOL TrebelSetup(BYTE treblefo, BYTE trebleq)
	{
		BYTE data = 0x0 | (treblefo<<4) | trebleq;
		return WriteIIC(SUB_TREBLESTUP, data);
	}
	BOOL BassGain(BYTE gain, BYTE boost = BMT_BOOST)
	{
		if (gain>20)
		{
			return 0;
		}
		BYTE data = 0x0 | (boost<<7) | gain;
		return WriteIIC(SUB_BASSGAIN, data);
	}
	BOOL MiddGain(BYTE gain, BYTE boost = BMT_BOOST)
	{
		if (gain > 20)
		{
			return 0;
		}
		BYTE data = 0x0 | (boost<<7) | gain;
		return WriteIIC(SUB_MIDDLEGAIN, data);
	}
	BOOL TrebelGain(BYTE gain, BYTE boost = BMT_BOOST)
	{
		if (gain > 20)
		{
			return 0;
		}
		BYTE data = 0x0 | (boost<<7) | gain;
		return WriteIIC(SUB_TREBLEGAIN, data);
	}
	BOOL Loudness(BYTE hint, BYTE gain)
	{
		if (gain>20)
		{
			return 0;
		}
		BYTE data = 0x0 | (hint<<4) | gain;
		return WriteIIC(SUB_LOUDNESS, data);
	}
	BOOL InitSetup4(BYTE loudgain, BYTE loudhicut = LOUDHICUT1)
	{
		if (loudgain>20)
		{
			return 0;
		}
		BYTE data = 0x0 | (loudhicut<<5) | loudgain;
		return WriteIIC(SUB_INITSETUP4, data);
	}
	void Init()
	{
		if (!InitSetup1() || !InitSetup2() || !InitSetup3())
		{
			//MessageBox(NULL, L"³õÊ¼»¯ÒôÆµÐ¾Æ¬Ê§°Ü", L"ERROR", MB_OK);
		}

		SetLF(0);
		SetLR(0);
		SetRF(0);
		SetRR(0);
		BassGain(0);
		MiddGain(0);
		TrebelGain(0);
		Loudness(LOUDHICUT1, 0);
		BassSetup(BASSFO_120, BASSQ_05);
		SubwOn(0);
		save2 = 0;
		mixMute = 0;
	}
	void SubwOn(int b)
	{
		subwOn = b;
		if (subwOn == 0)
		{
			SetSubW(0);
		}
		else
		{
			SetSubW(curVolume/2);
		}
	}
	int GetCurInput()
	{
		return curInput;
	}
	int GetCurVolume()
	{
		return curVolume;
	}
	void MixMute(BOOL b)
	{
		if (b)
		{
			mixMute = 1;
			MixerVol(0);
		}
		else
		{
			mixMute = 0;
		}
	}
};