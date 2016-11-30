#pragma once
#define CENTERVOL	9

enum
{
	AUDIO_NORMALMODE,
	AUDIO_PHONEMODE,
	AUDIO_NAVIMODE
};

class CE_HardwareDll_API Audio
{
public:
	static const int MaxVolume = 35;
private:
	static int	volume;
	static BOOL mute;
	static BOOL navi_mute;
	static BOOL subw_mute;
	static int nowCH;
	static int saveCH;
	static int media_atten;
public:
	enum
	{
		AUDIO_NONE,
		AUDIO_RADIO,
		AUDIO_DVD,
		AUDIO_BT,
		AUDIO_MEDIA,
		AUDIO_IPOD,
		AUDIO_AUX,
		AUDIO_NAVI,
		AUDIO_TV
	};
	static void Init();
	static void Mute();
	static void UnMute();
	static void MuteNoKeyTone();
	static void AMPPowerOff();
	static void AMPPowerOn();
	static void MuteKey();
	static void SetVolume(int vol);
	static void SetVolumeTmp(int vol);
	static void MixVolume(int vol);
	static void SetNaviVolume(int vol);
	static void SetPhoneVolume(int vol);
	static void NavMixSwitch(BOOL onoff);
	static int GetVolume();
	static void VolDown();
	static void VolUp();
	static void ToRadio();
	static void ToDVD();
	static void ToBT();
	static void ToBT2();
	static void ToMedia();
	static void ToIpod();
	static void ToAux();
	static void ToNavi();
	static void ToTV();
	static int GetCH();
	static void Restore();
	static void Save();
	static void SetTreble(int t);
	static void SetMiddle(int m);
	static void SetBass(int b);
	static void SetFL(int v);
	static void SetFR(int v);
	static void SetRL(int v);
	static void SetRR(int v);
	static void SetSoundField(int x, int y);
	static BOOL IsMute();
	static void Beep();
	static void BeepVol(BYTE vol);
	static void SetEq(int eq);
	static void SetSubw(int s);
	static void SubwOn(BOOL on);
	static void SetLoudness(int lound);
	static void SetPEQ(int band, int center_freq, int Q, int level);
	static void SoundDelay(int ch, double delay);
	static int GetVolDistance(int h, int l);
	static int GetVolDistance2(int , int);
	static void EnterNaviMode();
	static void ExitNaviMode(int mode = 0);
	static int GetAudioMode();
	static void SetMediaVolInNavi(int vol);
	static void SetMediaVolAttenInNavi(int atten);
};