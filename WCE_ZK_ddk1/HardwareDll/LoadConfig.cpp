#include "stdafx.h"
#include "LoadConfig.h"
//#include "WLan.h"
#include "Param.h"
#include "i2c/chip.h"
//#include "../GxxLib/GXCreateControls.h"
//#include "../GxxLib/LanguageEngine.h"
#include "GxxString.h"
#include "i2c/Auth.h"
#include "Audio/Audio.h"
#include "AVSet.h"
#include "Hardware.h"

#define CStdString GxxString
//#define UTF8ToUNICODE FromUTF8
//#include "GXTimeZone.h"

#define FLIPRGB(x) (RGB(GetBValue(x), GetGValue(x), GetRValue(x))|(x&0xFF000000))

TiXmlDocument CreatecConfig::xmlDoc;

void U2A(char *buf, int len, GxxString str)
{
	WideCharToMultiByte(CP_ACP, 0, str.GetData(), str.GetLength()+1, buf, len, NULL, NULL);
}

void U2UTF8(char *buf, int len, GxxString str)
{
	WideCharToMultiByte(CP_UTF8, 0, str.GetData(), str.GetLength()+1, buf, len, NULL, NULL);
}



COLORREF getColor(const char* str)
{
	if (!str)
	{
		return 0;
	}
	DWORD color = (strtoul(str, NULL, 16));
	if ((color >> 24) == 0)
	{
		color |= 0xFF000000;
	}
	return color;
}

BOOL CreatecHardware::IsAuthOK()
{
	return Auth::IsAuth();
}

void CreatecHardware::Init(HWND hWnd)
{
	Auth::Init(hWnd); 
	AVSET::Init();
	Audio::Mute();
	

	// 读配置
	sysConfig.ReadConfig();
	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	sysConfig.bBackLightOn = 1;

	// 读方向盘按键
	WheelKey *pWheelKey = WheelKey::Instance();
	pWheelKey->ReadWheelValue();

	// 设置默认时间 
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (st.wYear < 2009 || st.wYear > 2100)
	{
		st.wYear = 2011;
		st.wMonth = 1;
		st.wDay = 1;
		st.wHour = 0;
		st.wMinute = 0;
		st.wSecond = 0;
		SetLocalTime(&st);
	}
	//Sleep(100);
	//Audio::UnMute();
	
	// 设置声场
	Audio::SetSoundField(sysConfig.sysParam.curXPos,sysConfig.sysParam.curYPos);
	// 调整ce的声音到最大
	waveOutSetVolume(0,0xFFFF);
	// 设置音量为0
	Audio::SetVolume(0);//VolumeSet(0);
	sysConfig.sysParam.ExtAVSource = 0;
}