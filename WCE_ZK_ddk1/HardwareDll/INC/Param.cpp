#include "stdafx.h"
#include "Param.h"
#include "../i2c/24CXX.h"



#define MECHANISM_TYPE 1
#define  SPECAIL_MACHINE 2

#ifdef USEFILE
#define CONFIGVERSION 14

void CreateParamFile(void)
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,CREATE_NEW,0,0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		BYTE Paramp[PARAMSIZE] = {0};
		Paramp[0] = CONFIGVERSION;
		Paramp[3] = 20;			//默认音量设置
		Paramp[8] = Paramp[9] = 4; //默认声场设置 
		Paramp[10] = Paramp[11] = Paramp[12] = 0x80; //亮度,对比度,饱和度		
		DWORD dwWrite = 0;
		WriteFile(hFile,Paramp,PARAMSIZE,&dwWrite,NULL);
		CloseHandle(hFile);
	}
}

void WriteBYTE(BYTE data,WORD pos)
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	BYTE writedate = data;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
		WriteFile(hFile,&writedate,1,&dwWrite,NULL);
		CloseHandle(hFile);
	}
}

void WriteUINT(UINT data,WORD pos)
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	UINT writedate = data;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
		WriteFile(hFile,&writedate,4,&dwWrite,NULL);
		CloseHandle(hFile);
	}
}

void WriteUINTTable(UINT *data,WORD pos)
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
		WriteFile(hFile,data,4*30,&dwWrite,NULL);
		CloseHandle(hFile);
	}
}

void ReadUINTTable(UINT *data,WORD pos)
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
		ReadFile(hFile,data,4*30,&dwWrite,NULL);
		CloseHandle(hFile);
	}
}


BYTE ReadBYTE(WORD pos)
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	BYTE data = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
		ReadFile(hFile,&data,1,&dwWrite,NULL);
		CloseHandle(hFile);
	}
	return data;
}

UINT ReadUINT(WORD pos)
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	UINT data = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		SetFilePointer(hFile,pos,NULL,FILE_BEGIN);
		ReadFile(hFile,&data,4,&dwWrite,NULL);
		CloseHandle(hFile);
	}
	return data;
}



void WriteCurBand(BYTE data)
{
	WriteBYTE(data,32);
}

void WriteCurPage(BYTE data)
{
	WriteBYTE(data,33);
}

void WriteCurChannel(BYTE data)
{
	WriteBYTE(data,34);
}

void WriteCurFreq(UINT data)
{
	WriteUINT(data,40);
}

BYTE ReadCurBand(void)
{
	return ReadBYTE(32);
}

BYTE ReadCurPage(void)
{
	return ReadBYTE(33);
}

BYTE ReadCurChannel(void)
{
	return ReadBYTE(34);
}

UINT ReadCurFreq(void)
{
	return ReadUINT(40);
}

void WriteBandTable(UINT *table, BYTE curBand)
{
	WriteUINTTable(table,44 + curBand*4*30);
}

void UpdateBandFreq(UINT freq, UINT channel, BYTE curBand)
{
	WriteUINT(freq,44 + curBand*4*30 + 4*channel);
}

void ReadBandTable(UINT *table, BYTE curBand)
{
	ReadUINTTable(table,44 + curBand*4*30);
}

void WriteTVTable(UINT *table)
{
	WriteUINTTable(table,44+4*30*7);
}
void ReadTVTable(UINT *table)
{
	ReadUINTTable(table,44+4*30*7);
}
void WriteTVFreq(UINT freq, int channel)
{
	WriteUINT(freq, 44+4*30*7+channel*4);
}
UINT ReadTVFreq(int channel)
{
	return ReadUINT(44+4*30*7+channel*4);
}


Config sysConfig;

Config::Config()
{
	CreateParamFile();
	bFullScreen = 0;	// 当前是否全屏状态
	bMute = 0;			// 当前是否静音状态
	bBackLightOn = 0;	// 当前背光状态
	bMapOn = 0;
}



void Config::ReadConfig()
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		ReadFile(hFile,&(this->sysParam),sizeof(Param),&dwWrite,NULL);
		CloseHandle(hFile);
	}
	else
	{
		memset(this,0,sizeof(Param));
		sysParam.curVersion = CONFIGVERSION;
		sysParam.curVol = 20;
		sysParam.curXPos = sysParam.curYPos = 4;
		sysParam.curLightness = sysParam.curContast = sysParam.curSaturation = 0x80;
	}
	if (sysParam.curVersion != CONFIGVERSION)
	{
		DeleteFile(PARAMFILE);
		CreateParamFile();
		memset(this,0,sizeof(Param));
		HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD dwWrite = 0;
			ReadFile(hFile,&(this->sysParam),sizeof(Param),&dwWrite,NULL);
			CloseHandle(hFile);
		}
	}
}

void Config::WriteConfig()
{
	HANDLE hFile = CreateFile(PARAMFILE,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,0,0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWrite = 0;
		WriteFile(hFile,&(this->sysParam),sizeof(Param),&dwWrite,NULL);
		CloseHandle(hFile);
	}
}

void Config::WriteAngle(BYTE angle)
{
	sysParam.Angle = angle;
	WriteBYTE(angle,1);
}

void Config::WriteWnd(BYTE wnd)
{
	sysParam.curWnd = wnd;
	WriteBYTE(wnd,2);
}

void Config::WriteVol(BYTE vol)
{
	sysParam.curVol = vol;
	WriteBYTE(vol,3);
}
#endif

#ifdef USEEEPROM


Config sysConfig;

Config::Config()
{
	bFullScreen = 0;	// 当前是否全屏状态
	bMute = 0;			// 当前是否静音状态
	bBackLightOn = 0;	// 当前背光状态
	bMapOn = 0;
	bFactory = 0;
	bForceMute = 0;
	bMapResume = 0;
	bRecvPhone = 0;
	bNaviSpeak = 0;
	bTvModule = 0;
	bBrake = 1;
}



void Config::ReadConfig()
{
	chip_24cxx.Read(0, sizeof(Param), (BYTE*)&(this->sysParam));
	BYTE *tmp = (BYTE*)&sysParam.curVersion;
	for (int i=0;i<sizeof(Param);i++)
	{
		if (*tmp == 255)
		{
			*tmp++ = 0;
		}
	}
	sysParam.curVersion &= 0x7F;
	WriteConfig(&sysParam.curVersion);
	if (sysParam.curVersion != CONFIGVERSION)
	{
		Factory();
	}
}

void Config::WriteConfig(BYTE* distance)
{
	WORD pos = (DWORD)distance - (DWORD)&sysParam.curVersion;
	if (pos>sizeof(Param))
	{
		return;
	}
	chip_24cxx.Write(pos, *distance);
}


//void Config::WriteWnd(BYTE wnd)
//{
//	//sysParam.curWnd = wnd;
//	//chip_24cxx.Write(1, wnd);
//}

//void Config::WriteVol(BYTE vol)
//{
//	sysParam.curVol = vol;
//	chip_24cxx.Write(2, vol);
//}

void Config::Factory()
{
	BYTE data[2048] = {0};
	chip_24cxx.Write(0, 2048, data);
	BYTE tmpLang = sysParam.curLang;
	BYTE tmpTVFormat = sysParam.bDTVFormat;
	BYTE tmpFactoryLock = sysParam.bFactoryLock;
	BYTE tmpAppDisable = sysParam.appDisable;
	BYTE tmpIpodDisable = sysParam.ipodDisable;
	BYTE tmpHasWarning = sysParam.hasStartWaring;
	BYTE tmpCanUIChange = sysParam.noUIChange;
	BYTE tmpMediaCap = sysParam.mediaCap;
	BYTE tmpKeyLightColor = sysParam.KeylightColor;
	BYTE tmpFanControl = sysParam.fanControl;
	BYTE tmpUsbTips = sysParam.usbTips;
	BYTE tmpPBEnable = sysParam.pbEnable;
	memset(&sysParam, 0, sizeof(Param));
	sysParam.curVersion = CONFIGVERSION;
	//sysParam.curVol = 20;
	sysParam.curXPos = sysParam.curYPos = 15;
	sysParam.curLightness = sysParam.curContast = sysParam.curSaturation = 0x00;
	sysParam.curVPreset = 3; //标准
	sysParam.curBVPreset = 1;//柔和
	sysParam.curAPreset = 4; //标准
	sysParam.curLang = tmpLang;
	sysParam.curBContast = sysParam.curBLightness = 110;
	sysParam.curBSaturation = 128;
	//sysParam.curWnd = 0;	// radio
	sysParam.curHue = 40;
	sysParam.curDvdVol = 20;
	sysParam.curRadioVol = 20;
	sysParam.curTvVol = 20;
	sysParam.curPhoneVol = 20;
	sysParam.curIpodVol = 20;
	sysParam.curUsbVol = 15;
	sysParam.curPhoneMusicVol = 20;
	sysParam.curAuxVol = 20;
	sysParam.curGPSVol = 5;
	sysParam.CamFormat = 1;
	sysParam.curTimeZoneNum = 5;
	sysParam.MapStatus = 1;
	sysParam.curZone = 5;
	sysParam.KeylightMode = 1;
	sysParam.curLoudness = 0;
	sysParam.curSubw = 0;
	sysParam.curTimeFormat = 0x30;
	sysParam.bDTVFormat = tmpTVFormat;
	sysParam.bFactoryLock = tmpFactoryLock;
	sysParam.hasStartWaring = tmpHasWarning;
	sysParam.appDisable = tmpAppDisable;
	sysParam.ipodDisable = tmpIpodDisable;
	sysParam.noUIChange = tmpCanUIChange;
	sysParam.mediaCap = tmpMediaCap;
	sysParam.hasStartWaring = tmpHasWarning;
	sysParam.KeylightColor = tmpKeyLightColor;
	sysParam.fanControl = tmpFanControl;
	sysParam.usbTips = tmpUsbTips;
	sysParam.pbEnable = tmpPBEnable;
	
	sysConfig.sysParam.curTreble = 0;	//低音 中音 高音 都默认为 0
	sysConfig.sysParam.curBass = 0;	//
	sysConfig.sysParam.curMiddle = 0;


	//sysConfig.sysParam.NaviMix = 0;		//第0项
	sysConfig.sysParam.Buzzer = 1;	//按键开
	sysConfig.sysParam.FMorAM = 0;	//FM
	sysConfig.sysParam.mediaShuffle = 0;
	sysConfig.sysParam.mediaRandom = 0;
	sysConfig.sysParam.mediaHour = 0;
	sysConfig.sysParam.mediaMin = 0;
	sysConfig.sysParam.mediaSec = 0;

	sysConfig.sysParam.curScreenColor = 0;	//屏幕颜色默认是蓝色 czy
	sysConfig.sysParam.curEqBSFValue = 0;	//当前使用的EQ czy
	sysConfig.sysParam.curBsfSet = 0;//cyz 
	sysConfig.sysParam.curBsfPhase = 0;//cyz
	sysConfig.sysParam.curSoundFieldX = 0;//cyz
	sysConfig.sysParam.curSoundFieldY = 0;//cyz

	//sysConfig.sysParam.curNaviMix = 0;//导航音混成级别
	//sysConfig.sysParam.curNaviInt = 0;//导航中断默认关闭
	sysConfig.sysParam.curAuxOpen = 1;//默认打开Aux
	sysConfig.sysParam.curLang = 1;//默认中文 
	//sysConfig.sysParam.curBluetoothOpen = 1;//蓝牙打开 
	//sysConfig.sysParam.curBluetoothAutolink = 1;//蓝牙自动连接打开 cyz
	sysConfig.sysParam.curbMute = 0;//默认不静音
	//sysConfig.sysParam.BtPassword = 0;	//第0项
	sysConfig.sysParam.curTimeFrontL = 0;//cyz
	sysConfig.sysParam.curTimeFrontR = 0;//cyz
	sysConfig.sysParam.curTimeRearL = 0;//cyz
	sysConfig.sysParam.curTimeRearR = 0;//cyz
	sysConfig.sysParam.curbBtnPower=0;//cyz
	sysConfig.sysParam.curCalenderDayType=0;//cyz
	sysConfig.sysParam.curTime24HMode=0;//cyz

	sysConfig.sysParam.curDefeat=0;//cyzcur
	sysConfig.sysParam.curNthStartActivity = -1;//cyz
	

	sysConfig.sysParam.curDtvEnable=1;//
	
	sysConfig.sysParam.curIpodMedia = 0;
	sysConfig.sysParam.naviTips = 0;

	sysConfig.sysParam.CurrentFreqNum = 0;	//当前的收音机台的频率ID,0表示为空


	::memset(sysConfig.sysParam.curFreqLevel, -1, sizeof(sysConfig.sysParam.curFreqLevel)/sizeof(sysConfig.sysParam.curFreqLevel[0]) );
	::memset(sysConfig.sysParam.curQLevel, 0, sizeof(sysConfig.sysParam.curQLevel)/sizeof(sysConfig.sysParam.curQLevel[0]) );
	::memset(sysConfig.sysParam.curBandFreq, 0, sizeof(sysConfig.sysParam.curBandFreq)/sizeof(sysConfig.sysParam.curBandFreq[0]) );

	if ((ReadMachine() & MECHANISM_TYPE) == SPECAIL_MACHINE)
	{
		//专用机
		sysParam.BrakeDetect = 1;
	}
	bFactory = 1;
	chip_24cxx.Write(0, sizeof(Param),(BYTE*) &(sysParam));

	// 设置默认FM频率
	UINT defaultFMTable[60] = {87500, 88100, 90000, 98000, 106000, 107800};
	WriteBandTable(defaultFMTable, 0);
	// 设置默认AM频率
	UINT defaultAMTable[60] = {522, 603, 999, 1200, 1404, 1620};
	WriteBandTable(defaultAMTable, 1);
	WriteCurFreq(87500);
	// 设置默认TV频率
	UINT TVFreqTable[100] = {0x60000000|(5272500 + 389000),0x60000000|(5352500 + 389000),0x60000000|(6232500 + 389000),0x60000000|(7752500 + 389000),0x60000000|(7912500 + 389000)};
	WriteTVTable(TVFreqTable);
}

void WriteBYTE(BYTE data,WORD pos)
{
	chip_24cxx.Write(pos, data);
}

void WriteWORD(WORD data, WORD pos)
{
	BYTE byteData[2] = {(BYTE)data, (data>>8)&0xFF};
	chip_24cxx.Write(pos, 2, byteData);
}

void WriteUINT(UINT data,WORD pos)
{
	BYTE byteData[4] = {data, (data>>8)&0xFF, (data>>16)&0xFF, (data>>24)&0xFF};
	chip_24cxx.Write(pos, 4, byteData);
}

BYTE ReadBYTE(WORD pos)
{
	BYTE data = 0;
	chip_24cxx.Read(pos, 1, &data);
	return data;
}

WORD ReadWORD(WORD pos)
{
	BYTE data[2] = {0};
	chip_24cxx.Read(pos, 2, data);
	return data[1]<<8 | data[0];
}

UINT ReadUINT(WORD pos)
{
	BYTE data[4] = {0};
	chip_24cxx.Read(pos, 4, data);
	return data[3]<<24 | data[2]<<16 | data[1]<<8 | data[0];
}


void WriteWheelValue(int wheel[12])
{
	BYTE val[12] = {0};
	for (int i=0;i<12;i++)
	{
		val[i] = wheel[i];
	}
	chip_24cxx.Write(WHEELADDR, 12, (BYTE*)val);
}

void SetWheelKeyValue(int i, int val)
{
	chip_24cxx.Write(WHEELADDR+i, (BYTE)val);
}

void ReadWheelValue(int wheel[12])
{
	BYTE val[12] = {0};
	chip_24cxx.Read(WHEELADDR, 12, (BYTE*)val);
	for (int i=0;i<12;i++)
	{
		if (val[i] == 255)
		{
			val[i] = 0;
		}
		wheel[i] = val[i];
	}
}

WheelKey* WheelKey::pInstance = NULL;
WheelKey* WheelKey::Instance()
{
	if (!pInstance)
	{
		pInstance = new WheelKey();
	}
	return pInstance;
}

void WheelKey::ReadWheelValue()
{
	::ReadWheelValue(KeyValue);
}

void WheelKey::SaveWheelValue()
{
	::WriteWheelValue(KeyValue);
}

void WheelKey::SetWheelKeyValue(int i, int val)
{
	KeyValue[i] = val;
	::SetWheelKeyValue(i, val);
}

int WheelKey::GetWheelKeyValue(int i)
{
	return KeyValue[i];
}

int WheelKey::GetKey(int value)
{
	for (int i=0;i<12;i++)
	{
		if (abs(KeyValue[i] - value)<3)
		{
			return i;
		}
	}
	return -1;
}

void WheelKey::SetWheelKeyValue(int val[12])
{
	for (int i=0; i<12; i++)
	{
		KeyValue[i] = val[i];
	}
	SaveWheelValue();
}



void WriteCurBand(BYTE data)
{
	WriteBYTE(data, RADIOSTARTADDR);
}

void WriteCurPage(BYTE data)
{
	WriteBYTE(data, RADIOSTARTADDR+1);
}

void WriteCurChannel(BYTE data, int band)
{
	WriteBYTE(data, RADIOSTARTADDR+2+band);
}

void WriteCurFreq(UINT data)
{
	WriteUINT(data, RADIOSTARTADDR+8);
}

BYTE ReadCurBand()
{
	return ReadBYTE(RADIOSTARTADDR);
}

BYTE ReadCurPage()
{
	return ReadBYTE(RADIOSTARTADDR+1);
}

BYTE ReadCurChannel(int band)
{
	return ReadBYTE(RADIOSTARTADDR+2+band);
}

UINT ReadCurFreq()
{
	return ReadUINT(RADIOSTARTADDR+8);
}

void WriteBandTable(UINT *table, BYTE curBand)
{
	if (curBand>1)
	{
		curBand = 1;
	}
	WORD pos = RADIOSTARTADDR+16+curBand*(60*4);
	chip_24cxx.Write(pos, 60*4, (BYTE*)table);
}

void ReadBandTable(UINT *table, BYTE curBand)
{
	WORD pos = RADIOSTARTADDR+16+curBand*(60*4);
	chip_24cxx.Read(pos, 60*4, (BYTE*)table);
}

void UpdateBandFreq(UINT freq, UINT channel, BYTE curBand)
{
	if (curBand>1)
	{
		return;
	}
	if (channel>59)
	{
		return;
	}
	WORD pos = RADIOSTARTADDR+16+curBand*(60*4)+channel*4;
	WriteUINT(freq, pos);
}


void WriteTVTable(UINT *table)
{
	chip_24cxx.Write(TVSTARTADDR+8, 100*4, (BYTE*)table);
}

void ReadTVTable(UINT *table)
{
	chip_24cxx.Read(TVSTARTADDR+8, 100*4, (BYTE*)table);
}

void WriteTVFreq(UINT freq, int channel)
{
	if (channel>99)
	{
		return;
	}
	WORD pos = TVSTARTADDR+8+channel*4;
	WriteUINT(freq, pos);
}

UINT ReadTVFreq(int channel)
{
	if (channel>99)
	{
		return 0;
	}
	WORD pos = TVSTARTADDR+8+channel*4;
	return ReadUINT(pos);
}

void WritePhoneNum(BYTE *pn)
{
	chip_24cxx.Write(1024, 10*20, (BYTE*)pn);
}

void ReadPhoneNum(BYTE *pn)
{
	chip_24cxx.Read(1024, 10*20, (BYTE*)pn);
}

void SavaCaliData(TCHAR *strData)
{
	chip_24cxx.Write(1900, _tcslen(strData)*2);
	//STLOG_WRITE("len = %d",_tcslen(strData)*2);
	chip_24cxx.Write(1901, _tcslen(strData)*2, (BYTE*)strData);
}

BOOL ReadCaliData(TCHAR *strData)
{
	BYTE len = 0;
	chip_24cxx.Read(1900, 1, &len);
	if (len == 0 || len == 255)
	{
		return 0;
	}
	chip_24cxx.Read(1901, len, (BYTE*)strData);
	return 1;
}

//void SaveTimeZoneInfo(TIME_ZONE_INFORMATION *tiZone)
//{
//	chip_24cxx.Write(1700, sizeof(tiZone->Bias), (BYTE*)tiZone);
//}
//
//void ReadTimeZoneInfo(TIME_ZONE_INFORMATION *tiZone)
//{
//	chip_24cxx.Read(1700, sizeof(tiZone->Bias), (BYTE*)tiZone);
//}

void SaveXmlVer(int ver)
{
	BYTE by1 = ver;
	BYTE by2 = ver>>8;
	chip_24cxx.Write(1780, by1);
	chip_24cxx.Write(1781, by2);
}

int GetXmlVer()
{
	BYTE by1, by2;
	chip_24cxx.Read(1780, 1, &by1);
	chip_24cxx.Read(1781, 1, &by2);
	return (by2<<8 | by1);
}

#endif