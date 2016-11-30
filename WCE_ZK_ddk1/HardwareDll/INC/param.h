#pragma once

#include "stdAfx.h"
#include "HardwareDllModule.h"
#define USEEEPROM

#ifdef USEFILE

/*
	参数文件存储布局
	参数名		含义		占用字节
软件设置
	curVersion	当前参数文件版本1		BYTE
	Angle		屏幕角度		1		BYTE
	curWnd		当前窗口		1		BYTE
音量设置
	curVol		当前音量		1		BYTE
	curTreble	当前高音		1		BYTE
	curBass		当前低音		1		BYTE
	curLoudness	当前响度		1		BYTE
	curAPreset	预置值			1		BYTE
平衡设置
	curXPos		声场x位置		1		BYTE
	curYPos		声场y位置		1		BYTE
视频设置
	curLightness  亮度			1		BYTE
	curContast	  对比度		1		BYTE
	curSaturation 饱和度		1		BYTE
	curHue		  色调			1		BYTE
	curVPreset	  预置值		1		BYTE
通用设置
	curRDS		RDS开关			1		BYTE
	curZone		当前区域		1		BYTE
	curLang		当前语言		1		BYTE
	CamMirror	后视镜像		1		BYTE
	Buzzer		蜂鸣器开关		1		BYTE
	ExtAVSource 外部视频输出源  1		BYTE
	MapStauts	地图状态		1		BYTE
	AudioMix	混音开关		1		BYTE
	curTVCh		当前TV频道		1		BYTE
	LightDetect 大灯检测		1		BYTE
	BrakeDetect 手刹检测		1		BYTE
	xxx			预留			6		BYTE
	GPSPath		GPS导航软件路径
收音机:
	curBand		当前波段		1		BYTE
	curPage		当前显示页		1		BYTE
	curChannel	当前频道		1		BYTE
	curPAT						1		BYTE
	curAF						1		BYTE
	curRST						1		BYTE
	curTA						1		BYTE
	xx			填充			1		BYTE		
	curFreq		当前频率		4		UINT				
	FM1Table	FM1频率表	   4x30		UINT[30]
	FM2Table	FM2频率表	   4x30		UINT[30]
	FM3Table	FM2频率表	   4x30		UINT[30]
	AM1Table	AM1频率表	   4x30		UINT[30]
	AM2Table	AM2频率表	   4x30		UINT[30]
	AM3Table	AM3频率表	   4x30		UINT[30]
	AM4Table	AM4频率表	   4x30		UINT[30]
TV:
	FreqTable	电视频率表	   4x64		UINT[30]
*/

#define PARAMFILE	_T("\\residentflash\\paramdat.dat")

#define PARAMSIZE	(32+12+280*4+120)

void CreateParamFile(void);
void WriteBYTE(BYTE data,int pos);
void WriteUINT(UINT data,int pos);
void WriteUINTTable(UINT *data,int pos);
void ReadUINTTable(UINT *data,int pos);
BYTE ReadBYTE(int pos);
UINT ReadUINT(int pos);
//void WriteAngle(BYTE data);
//void WriteCurWnd(BYTE data);
//void WriteCurVol(BYTE data);
void WriteCurBand(BYTE data);
void WriteCurPage(BYTE data);
void WriteCurChannel(BYTE data);
void WriteCurFreq(UINT data);
//BYTE ReadAngle(void);
//BYTE ReadCurWnd(void);
//BYTE ReadCurVol(void);
BYTE ReadCurBand(void);
BYTE ReadCurPage(void);
BYTE ReadCurChannel(void);
UINT ReadCurFreq(void);
void WriteBandTable(UINT *table, BYTE curBand);
void ReadBandTable(UINT *table, BYTE curBand);
void UpdateBandFreq(UINT freq, UINT channel, BYTE curBand);

void WriteTVTable(UINT *table);
void ReadTVTable(UINT *table);
void WriteTVFreq(UINT freq, int channel);
UINT ReadTVFreq(int channel);



class Config
{
public:
	class Param
	{
	public:
		BYTE curVersion;
		BYTE Angle;
		BYTE curWnd;
		BYTE curVol;
		char curTreble;
		char curBass;
		BYTE curLoudness;
		BYTE curAPreset;
		char curXPos;
		char curYPos;
		BYTE curLightness;
		BYTE curContast;
		BYTE curSaturation;
		BYTE curHue;
		BYTE curVPreset;	// 视频预设
		BYTE curRDS;
		BYTE curZone;
		BYTE curLang;
		BYTE CamMirror;
		BYTE Buzzer;
		BYTE ExtAVSource;
		BYTE MapStatus;		// 地图状态
		BYTE AudioMix;
		BYTE LightDetect;	// 大灯检测
		BYTE BrakeDetect;	// 手刹检测
		BYTE curTVCh;
		BYTE reverse[6];
	}sysParam;

// 不需要记录到文件中的参数
	BYTE bFullScreen;	// 当前是否全屏状态
	BYTE bMute;			// 当前是否静音状态
	BYTE bBackLightOn;	// 当前背光状态
	BYTE bMapOn;		// 当前地图是否打开
	BYTE bBrake;		// 当前手刹是否拉起

public:
	Config();
	void ReadConfig();
	void WriteConfig();
	void WriteAngle(BYTE angle);
	void WriteWnd(BYTE wnd);
	void WriteVol(BYTE vol);
};

extern Config sysConfig;

#endif

#ifdef USEEEPROM

#define CONFIGVERSION 9

// 使用24c16 参数布局
// 存储内容		数据大小(BYTE)		备注
// 系统设置		48+48					见sysConfig
// 方向盘学习	16
// TV频道		100x4
// 收音机设置	16					curBand; curPage; curChannel; totalCh; curPAT; curAF; curRT; curTA; curFreq(x4); ...
// 收音机FM		60x4
// 收音机AM		60x4

// 通话记录 1024 开始
// 10条x20BYTE	200 

#define SYSCONFIGSIZE	(300)
#define WHEELADDR (SYSCONFIGSIZE)
#define WHEELSIZE	16
#define TVSTARTADDR (WHEELADDR+WHEELSIZE)
#define TVSIZE		400
#define RADIOSTARTADDR (TVSTARTADDR+TVSIZE)
#define RADIOSIZE	(60*2*4)


void WriteWheelValue(int wheel[12]);
void SetWheelKeyValue(int i, int val);
void ReadWheelValue(int wheel[12]);

class WheelKey
{
	static WheelKey* pInstance;
	int KeyValue[12];
public:
	static WheelKey* Instance();
	void ReadWheelValue();
	void SaveWheelValue();
	void SetWheelKeyValue(int i, int val);
	void SetWheelKeyValue(int val[12]);
	int	GetWheelKeyValue(int i);
	int GetKey(int value);
protected:
	WheelKey()
	{

	}
};

// 1700开始172字节存储时区信息
void SaveTimeZoneInfo(TIME_ZONE_INFORMATION *tiZone);
void ReadTimeZoneInfo(TIME_ZONE_INFORMATION *tiZone);
// 1780-1781存放xml版本信息
void SaveXmlVer(int ver);
int GetXmlVer();

// 1900 开始最后100字节存放触摸屏校准值
void WriteBYTE(BYTE data,WORD pos);
void WriteWORD(WORD data, WORD pos);
void WriteUINT(UINT data,WORD pos);
BYTE ReadBYTE(WORD pos);
WORD ReadWORD(WORD pos);
UINT ReadUINT(WORD pos);

void CE_HardwareDll_API WriteCurBand(BYTE data);
void CE_HardwareDll_API WriteCurPage(BYTE data);
void CE_HardwareDll_API WriteCurChannel(BYTE data, int);
void CE_HardwareDll_API WriteCurFreq(UINT data);

BYTE CE_HardwareDll_API ReadCurBand(void);
BYTE CE_HardwareDll_API ReadCurPage(void);
BYTE CE_HardwareDll_API ReadCurChannel(int band);
UINT CE_HardwareDll_API ReadCurFreq(void);
void CE_HardwareDll_API WriteBandTable(UINT *table, BYTE curBand);
void CE_HardwareDll_API ReadBandTable(UINT *table, BYTE curBand);
void CE_HardwareDll_API UpdateBandFreq(UINT freq, UINT channel, BYTE curBand);

void WriteTVTable(UINT *table);
void ReadTVTable(UINT *table);
void WriteTVFreq(UINT freq, int channel);
UINT ReadTVFreq(int channel);

void WritePhoneNum(BYTE *pn);
void ReadPhoneNum(BYTE *pn);

void SavaCaliData(TCHAR *strData);
BOOL ReadCaliData(TCHAR *strData);

enum
{
	EXTOUT_AUTO,
	EXTOUT_DVD,
	EXTOUT_TV,
	EXTOUT_AV,
	EXTOUT_IPOD,
	EXTOUT_CE
};

class CE_HardwareDll_API  Config
{
public:
	class Param
	{
	public:
		BYTE curVersion;
		//BYTE curWnd;
		//BYTE curVol;

		char curTreble;
		char curBass;
		char curMiddle;
		BYTE curSoundEnhancement;

		char curXPos;
		char curYPos;

		BYTE curLightness;
		BYTE curContast;
		BYTE curSaturation;

		BYTE curLang;//语言设定

		BYTE curUILibary;

		BYTE curLoudness;
		BYTE curAPreset;

		BYTE curHue;
		BYTE curVPreset;	// 视频预设
		BYTE curRDS;
		BYTE curZone;
		
		BYTE CamFormat;
		BYTE Buzzer;
		BYTE ExtAVSource;
		BYTE MapStatus;		// 地图状态
		BYTE AudioMix;
		BYTE LightDetect;	// 大灯检测
		BYTE BrakeDetect;	// 手刹检测
		BYTE curTVCh;
		BYTE KeylightMode;	// 当前按键灯模式
		BYTE curBLightness;
		BYTE curBContast;
		BYTE curBSaturation;
		BYTE curBVPreset;
		BYTE bMapOn;		// 地图是否打开
		BYTE bDTVFormat;	// 数字电视视频制式
		//BYTE curMacineVol;	//机器音量
		BYTE curPhoneMusicVol;
		BYTE curDvdVol;
		BYTE curRadioVol;
		BYTE curTvVol;
		BYTE curPhoneVol;
		BYTE curIpodVol;
		BYTE curAuxVol;
		BYTE curUsbVol;
		BYTE curDtvVol;
		BYTE curNaviVol;
		BYTE curTimeZoneNum; //42
		BYTE bAFOn;		//43 当前收音机AF状态
		BYTE bFactoryLock;	// 当前是否可以调整增强功能用户菜单 44
		BYTE KeylightColor;		// 键盘灯颜色 45
		BYTE curGPSVol;		// 当前GPS音量
		BYTE curGPS_Vol_Rate;	//GPS音量与整体音量的比例
		BYTE curVol;
		BYTE curTimeFormat; // 当前时间格式
		BYTE usbMode;		// usb模式

		BYTE videoBrightness;
		BYTE videoContrast;
		BYTE videoSaturation;
		BYTE videoHue;


		BYTE hasStartWaring;	// 开机时候是否出现warning
		BYTE appDisable;		// 是否禁止用户使用 app 功能
		BYTE ipodDisable;		// 是否禁止用户使用 ipod 功能
		BYTE noUIChange;		// 是否禁止用户选择UI
		BYTE mediaCap;			// 播放视频的能力
		BYTE fanControl;		// 风扇控制
		BYTE usbTips;			// USB 提示
		BYTE pbEnable;			// 是否允许PhoneBook功能

		
		BYTE curSubw;

		
		//char eq0;
		//char eq1;
		//char eq2;
		//char eq3;
		//char eq4;
		//char eq5;
		//char eq6;
		//char eq7;


		//BYTE NaviMix;	//导航混音
		
		//BYTE BtPassword;	//蓝牙密码
		BYTE FMorAM;
		BYTE CurrentFreqNum;	//当前的收音机台的频率ID
		BYTE mediaShuffle;
		BYTE mediaHour;
		BYTE mediaMin;
		BYTE mediaSec;
		BYTE mediaRandom;

		BYTE curEqLineValue;//cyz
		BYTE curEqBSFValue;//cyz
		BYTE curBsfSet;//BSF打开or关闭 设定 cyz
		BYTE curBsfPhase;//BSF 相位打开or关闭cyz
		char curSoundFieldX;//cyz
		char curSoundFieldY;//cyz
		BYTE curScreenColor;// 屏幕颜色设定 cyz
		BYTE curBeep;//  beep
		BYTE curDefeat;//  defeat
		BYTE curDtvEnable;//  DtvEnable
		//BYTE curBluetoothOpen;//蓝牙打开
		//BYTE curBluetoothAutolink;//蓝牙自动连接
		BYTE curCamera;//摄像头
		//BYTE curNaviInt;//导航中断
		//BYTE curNaviMix;//导航音混成级别 cyz

		BYTE curCalenderDayType;//日历风格
		BYTE curTime24HMode;//时钟12小时模式
		BYTE curAutoAdjustSwith;//时钟是否打开自动校正
		BYTE curAutoAdjustDone;//时钟是否已经自动校正

		BYTE curPhoneAutoAnswer;//电话
		BYTE curPhoneSpeaker;// cyz
		//BYTE curPhoneVolume;//cyz

		BYTE curAuxOpen;//蓝牙打开 cyz
		BYTE curAuxSignal;//蓝牙自动连接 cyz

		//BYTE curBluetoothPassword_set;//123表示设定好
		//char curBluetoothPassword0;
		//char curBluetoothPassword1;
		//char curBluetoothPassword2;
		//char curBluetoothPassword3;

		char curScreenBrightness;//
		char curScreenContrast;//
		char curVedioBrightness;//
		char curVedioContrast;//
		char curVedioColor;//
		
		BYTE curCodeSwitch;//开关 的方控 编码 cyz
		BYTE curCodeBack;//方控 返回 cyz 
		BYTE curCodeWaveBand;//
		BYTE curCodeMode;//
		BYTE curCodeAnswer;//
		BYTE curCodeDrop;//
		BYTE curCodeMute;//
		BYTE curCodePrevious;//
		BYTE curCodeNext;//
		BYTE curCodeVolAdd;//
		BYTE curCodeVolDec;//
		BYTE curCodeVolPaly;//cyz

		BYTE curTimeFrontL;//cyz
		BYTE curTimeFrontR;//cyz
		BYTE curTimeRearL;//cyz
		BYTE curTimeRearR;//cyz
		BYTE curSubwL;//cyz
		BYTE curSubwR;//cyz

		BYTE presetTimeFrontL[3];//cyz
		BYTE presetTimeFrontR[3];//cyz
		BYTE presetTimeRearL[3];//cyz
		BYTE presetTimeRearR[3];//cyz
		BYTE presetSubwL[3];//cyz
		BYTE presetSubwR[3];//cyz

		BYTE curbMute;			// 当前是否静音状态
		BYTE curbBtnPower;		// 当前是否通过Btn来关机
		BYTE curNthStartActivity;		// 当前是否通过Btn来关机
		char curNthTestActivity;		// 当前是否通过Btn来关机
		BYTE curNaviOption;		// 导航软件选择


		char		curFreqLevel[7];//cyz
		BYTE		curQLevel[7];//cyz
		BYTE		curBandFreq[7];//cyz

		char		presetFreqLevel[21];//cyz 预设值
		BYTE		presetQLevel[21];//cyz 预设值
		BYTE		presetBandFreq[21];//cyz 预设值
		BYTE		curBtnMatchR;//方控电阻
		
		BYTE	curIpodMedia; 
		BYTE	naviGain;//导航增益
		BYTE naviTips;	//导航是否中断 xyf
		BYTE naviAtten;	//混音级别	xyf
	}sysParam;

	// 不需要记录到文件中的参数
	BYTE bFullScreen;	// 当前是否全屏状态
	BYTE bMute;			// 当前是否静音状态
	BYTE bBackLightOn;	// 当前背光状态
	BYTE bMapOn;		// 当前地图是否打开
	BYTE bBrake;		// 当前手刹是否拉起
	BYTE bLightOn;		// 当前大灯是否打开
	BYTE bFactory;		// 当前已经恢复出厂设置
	BYTE bForceMute;	// 当前是否处在强制静音状态
	BYTE bMapResume;	// 恢复地图状态
	BYTE curVFormat;    // 当前系统显示的制式
	BYTE bRecvPhone;	// 当前是否接听电话状态
	BYTE bNaviSpeak;	// 当前是否导航发声状态
	BYTE bBackCamera;	// 当前是否处于显示倒车的状态
	BYTE bTvOut;		// 当前是否处于8900的TVOUT状态
	BYTE bTvModule;		// 数字还是模拟电视
	BYTE bBTDebug;		// 蓝牙调试状态
	BYTE bWinceAndroid;	// wince 还是 android
	

public:
	Config();
	void ReadConfig();
	void WriteConfig(BYTE *distance);
	void WriteAngle(BYTE angle);
	//void WriteWnd(BYTE wnd);
	//void WriteVol(BYTE vol);
	void Factory();
};

extern CE_HardwareDll_API Config sysConfig;

enum
{
	MODE_WINCE,
	MODE_ANDROID = 5
};

#endif