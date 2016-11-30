#pragma once

#include "stdAfx.h"
#include "HardwareDllModule.h"
#define USEEEPROM

#ifdef USEFILE

/*
	�����ļ��洢����
	������		����		ռ���ֽ�
�������
	curVersion	��ǰ�����ļ��汾1		BYTE
	Angle		��Ļ�Ƕ�		1		BYTE
	curWnd		��ǰ����		1		BYTE
��������
	curVol		��ǰ����		1		BYTE
	curTreble	��ǰ����		1		BYTE
	curBass		��ǰ����		1		BYTE
	curLoudness	��ǰ���		1		BYTE
	curAPreset	Ԥ��ֵ			1		BYTE
ƽ������
	curXPos		����xλ��		1		BYTE
	curYPos		����yλ��		1		BYTE
��Ƶ����
	curLightness  ����			1		BYTE
	curContast	  �Աȶ�		1		BYTE
	curSaturation ���Ͷ�		1		BYTE
	curHue		  ɫ��			1		BYTE
	curVPreset	  Ԥ��ֵ		1		BYTE
ͨ������
	curRDS		RDS����			1		BYTE
	curZone		��ǰ����		1		BYTE
	curLang		��ǰ����		1		BYTE
	CamMirror	���Ӿ���		1		BYTE
	Buzzer		����������		1		BYTE
	ExtAVSource �ⲿ��Ƶ���Դ  1		BYTE
	MapStauts	��ͼ״̬		1		BYTE
	AudioMix	��������		1		BYTE
	curTVCh		��ǰTVƵ��		1		BYTE
	LightDetect ��Ƽ��		1		BYTE
	BrakeDetect ��ɲ���		1		BYTE
	xxx			Ԥ��			6		BYTE
	GPSPath		GPS�������·��
������:
	curBand		��ǰ����		1		BYTE
	curPage		��ǰ��ʾҳ		1		BYTE
	curChannel	��ǰƵ��		1		BYTE
	curPAT						1		BYTE
	curAF						1		BYTE
	curRST						1		BYTE
	curTA						1		BYTE
	xx			���			1		BYTE		
	curFreq		��ǰƵ��		4		UINT				
	FM1Table	FM1Ƶ�ʱ�	   4x30		UINT[30]
	FM2Table	FM2Ƶ�ʱ�	   4x30		UINT[30]
	FM3Table	FM2Ƶ�ʱ�	   4x30		UINT[30]
	AM1Table	AM1Ƶ�ʱ�	   4x30		UINT[30]
	AM2Table	AM2Ƶ�ʱ�	   4x30		UINT[30]
	AM3Table	AM3Ƶ�ʱ�	   4x30		UINT[30]
	AM4Table	AM4Ƶ�ʱ�	   4x30		UINT[30]
TV:
	FreqTable	����Ƶ�ʱ�	   4x64		UINT[30]
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
		BYTE curVPreset;	// ��ƵԤ��
		BYTE curRDS;
		BYTE curZone;
		BYTE curLang;
		BYTE CamMirror;
		BYTE Buzzer;
		BYTE ExtAVSource;
		BYTE MapStatus;		// ��ͼ״̬
		BYTE AudioMix;
		BYTE LightDetect;	// ��Ƽ��
		BYTE BrakeDetect;	// ��ɲ���
		BYTE curTVCh;
		BYTE reverse[6];
	}sysParam;

// ����Ҫ��¼���ļ��еĲ���
	BYTE bFullScreen;	// ��ǰ�Ƿ�ȫ��״̬
	BYTE bMute;			// ��ǰ�Ƿ���״̬
	BYTE bBackLightOn;	// ��ǰ����״̬
	BYTE bMapOn;		// ��ǰ��ͼ�Ƿ��
	BYTE bBrake;		// ��ǰ��ɲ�Ƿ�����

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

// ʹ��24c16 ��������
// �洢����		���ݴ�С(BYTE)		��ע
// ϵͳ����		48+48					��sysConfig
// ������ѧϰ	16
// TVƵ��		100x4
// ����������	16					curBand; curPage; curChannel; totalCh; curPAT; curAF; curRT; curTA; curFreq(x4); ...
// ������FM		60x4
// ������AM		60x4

// ͨ����¼ 1024 ��ʼ
// 10��x20BYTE	200 

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

// 1700��ʼ172�ֽڴ洢ʱ����Ϣ
void SaveTimeZoneInfo(TIME_ZONE_INFORMATION *tiZone);
void ReadTimeZoneInfo(TIME_ZONE_INFORMATION *tiZone);
// 1780-1781���xml�汾��Ϣ
void SaveXmlVer(int ver);
int GetXmlVer();

// 1900 ��ʼ���100�ֽڴ�Ŵ�����У׼ֵ
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

		BYTE curLang;//�����趨

		BYTE curUILibary;

		BYTE curLoudness;
		BYTE curAPreset;

		BYTE curHue;
		BYTE curVPreset;	// ��ƵԤ��
		BYTE curRDS;
		BYTE curZone;
		
		BYTE CamFormat;
		BYTE Buzzer;
		BYTE ExtAVSource;
		BYTE MapStatus;		// ��ͼ״̬
		BYTE AudioMix;
		BYTE LightDetect;	// ��Ƽ��
		BYTE BrakeDetect;	// ��ɲ���
		BYTE curTVCh;
		BYTE KeylightMode;	// ��ǰ������ģʽ
		BYTE curBLightness;
		BYTE curBContast;
		BYTE curBSaturation;
		BYTE curBVPreset;
		BYTE bMapOn;		// ��ͼ�Ƿ��
		BYTE bDTVFormat;	// ���ֵ�����Ƶ��ʽ
		//BYTE curMacineVol;	//��������
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
		BYTE bAFOn;		//43 ��ǰ������AF״̬
		BYTE bFactoryLock;	// ��ǰ�Ƿ���Ե�����ǿ�����û��˵� 44
		BYTE KeylightColor;		// ���̵���ɫ 45
		BYTE curGPSVol;		// ��ǰGPS����
		BYTE curGPS_Vol_Rate;	//GPS���������������ı���
		BYTE curVol;
		BYTE curTimeFormat; // ��ǰʱ���ʽ
		BYTE usbMode;		// usbģʽ

		BYTE videoBrightness;
		BYTE videoContrast;
		BYTE videoSaturation;
		BYTE videoHue;


		BYTE hasStartWaring;	// ����ʱ���Ƿ����warning
		BYTE appDisable;		// �Ƿ��ֹ�û�ʹ�� app ����
		BYTE ipodDisable;		// �Ƿ��ֹ�û�ʹ�� ipod ����
		BYTE noUIChange;		// �Ƿ��ֹ�û�ѡ��UI
		BYTE mediaCap;			// ������Ƶ������
		BYTE fanControl;		// ���ȿ���
		BYTE usbTips;			// USB ��ʾ
		BYTE pbEnable;			// �Ƿ�����PhoneBook����

		
		BYTE curSubw;

		
		//char eq0;
		//char eq1;
		//char eq2;
		//char eq3;
		//char eq4;
		//char eq5;
		//char eq6;
		//char eq7;


		//BYTE NaviMix;	//��������
		
		//BYTE BtPassword;	//��������
		BYTE FMorAM;
		BYTE CurrentFreqNum;	//��ǰ��������̨��Ƶ��ID
		BYTE mediaShuffle;
		BYTE mediaHour;
		BYTE mediaMin;
		BYTE mediaSec;
		BYTE mediaRandom;

		BYTE curEqLineValue;//cyz
		BYTE curEqBSFValue;//cyz
		BYTE curBsfSet;//BSF��or�ر� �趨 cyz
		BYTE curBsfPhase;//BSF ��λ��or�ر�cyz
		char curSoundFieldX;//cyz
		char curSoundFieldY;//cyz
		BYTE curScreenColor;// ��Ļ��ɫ�趨 cyz
		BYTE curBeep;//  beep
		BYTE curDefeat;//  defeat
		BYTE curDtvEnable;//  DtvEnable
		//BYTE curBluetoothOpen;//������
		//BYTE curBluetoothAutolink;//�����Զ�����
		BYTE curCamera;//����ͷ
		//BYTE curNaviInt;//�����ж�
		//BYTE curNaviMix;//��������ɼ��� cyz

		BYTE curCalenderDayType;//�������
		BYTE curTime24HMode;//ʱ��12Сʱģʽ
		BYTE curAutoAdjustSwith;//ʱ���Ƿ���Զ�У��
		BYTE curAutoAdjustDone;//ʱ���Ƿ��Ѿ��Զ�У��

		BYTE curPhoneAutoAnswer;//�绰
		BYTE curPhoneSpeaker;// cyz
		//BYTE curPhoneVolume;//cyz

		BYTE curAuxOpen;//������ cyz
		BYTE curAuxSignal;//�����Զ����� cyz

		//BYTE curBluetoothPassword_set;//123��ʾ�趨��
		//char curBluetoothPassword0;
		//char curBluetoothPassword1;
		//char curBluetoothPassword2;
		//char curBluetoothPassword3;

		char curScreenBrightness;//
		char curScreenContrast;//
		char curVedioBrightness;//
		char curVedioContrast;//
		char curVedioColor;//
		
		BYTE curCodeSwitch;//���� �ķ��� ���� cyz
		BYTE curCodeBack;//���� ���� cyz 
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

		BYTE curbMute;			// ��ǰ�Ƿ���״̬
		BYTE curbBtnPower;		// ��ǰ�Ƿ�ͨ��Btn���ػ�
		BYTE curNthStartActivity;		// ��ǰ�Ƿ�ͨ��Btn���ػ�
		char curNthTestActivity;		// ��ǰ�Ƿ�ͨ��Btn���ػ�
		BYTE curNaviOption;		// �������ѡ��


		char		curFreqLevel[7];//cyz
		BYTE		curQLevel[7];//cyz
		BYTE		curBandFreq[7];//cyz

		char		presetFreqLevel[21];//cyz Ԥ��ֵ
		BYTE		presetQLevel[21];//cyz Ԥ��ֵ
		BYTE		presetBandFreq[21];//cyz Ԥ��ֵ
		BYTE		curBtnMatchR;//���ص���
		
		BYTE	curIpodMedia; 
		BYTE	naviGain;//��������
		BYTE naviTips;	//�����Ƿ��ж� xyf
		BYTE naviAtten;	//��������	xyf
	}sysParam;

	// ����Ҫ��¼���ļ��еĲ���
	BYTE bFullScreen;	// ��ǰ�Ƿ�ȫ��״̬
	BYTE bMute;			// ��ǰ�Ƿ���״̬
	BYTE bBackLightOn;	// ��ǰ����״̬
	BYTE bMapOn;		// ��ǰ��ͼ�Ƿ��
	BYTE bBrake;		// ��ǰ��ɲ�Ƿ�����
	BYTE bLightOn;		// ��ǰ����Ƿ��
	BYTE bFactory;		// ��ǰ�Ѿ��ָ���������
	BYTE bForceMute;	// ��ǰ�Ƿ���ǿ�ƾ���״̬
	BYTE bMapResume;	// �ָ���ͼ״̬
	BYTE curVFormat;    // ��ǰϵͳ��ʾ����ʽ
	BYTE bRecvPhone;	// ��ǰ�Ƿ�����绰״̬
	BYTE bNaviSpeak;	// ��ǰ�Ƿ񵼺�����״̬
	BYTE bBackCamera;	// ��ǰ�Ƿ�����ʾ������״̬
	BYTE bTvOut;		// ��ǰ�Ƿ���8900��TVOUT״̬
	BYTE bTvModule;		// ���ֻ���ģ�����
	BYTE bBTDebug;		// ��������״̬
	BYTE bWinceAndroid;	// wince ���� android
	

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