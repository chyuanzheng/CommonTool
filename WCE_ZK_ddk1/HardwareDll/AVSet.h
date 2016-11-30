#include "HardwareDllModule.h"
namespace AVSET
{
	class Section
	{
	public:
		static CRITICAL_SECTION	*GET()
		{
			if (avset_cs == NULL)
			{
				avset_cs = new CRITICAL_SECTION;
				InitializeCriticalSection(avset_cs);
			}
			return avset_cs;
		}
	private:
		static CRITICAL_SECTION	*avset_cs;
	};
	
	void  CE_HardwareDll_API Init();
	// 音视频切换
	void  CE_HardwareDll_API ToRadio();
	void  CE_HardwareDll_API ToDVD();
	void  CE_HardwareDll_API ToIpod();
	void  CE_HardwareDll_API ToAux();
	void  CE_HardwareDll_API ToTV();
	void  CE_HardwareDll_API ToMedia();
	void  CE_HardwareDll_API ToBTMusic();
	void  CE_HardwareDll_API ToNavi();
	void  CE_HardwareDll_API CloseAuxOutput();
	// 蓝牙电话时调用
	void  CE_HardwareDll_API ToBTPhone();
	// 蓝牙电话挂断时调用
	void  CE_HardwareDll_API LeaveBTPhone();
	// 音频控制
	void  CE_HardwareDll_API Mute();
	void  CE_HardwareDll_API UnMute();
	void  CE_HardwareDll_API AMPPowerOn();
	void  CE_HardwareDll_API AMPPowerOff();
	void  CE_HardwareDll_API SetSoundAffect(int affect);
	// 设置声场,中心点(x=0,y=0) 前:y>0 右:x>0
	void  CE_HardwareDll_API SetSoundField(int x, int y);
	void  CE_HardwareDll_API SetEQ(int eq);

	/*
		band		: GEQ波段, (0-8)
		fc			: 中心频率, (20-15000)
		Q			: Q 值 (1-100) 对应 0.1-10
	*/
	void  CE_HardwareDll_API ConfigGEQ(int band, int fc, int Q);
/*
		band		: GEQ波段, (0-9)
		level		: 增益, (-12-12)
	*/
	void  CE_HardwareDll_API SetGEQ(int band, int level);
	// 参数EQ设置
	/*
		band		: PEQ波段, (0-6)
		center_freq	: 中心频率, (20-20000)
		Q			: Q 值 (1-100) 对应 0.1-10
		level		: 增益 (-14-14)
	*/
	void  CE_HardwareDll_API SetPEQ(int band, int center_freq, int Q, int level);
	void  CE_HardwareDll_API SetTreble(int trebel);
	void  CE_HardwareDll_API SetMiddle(int midd);
	void  CE_HardwareDll_API SetBass(int bass);
	void  CE_HardwareDll_API SetLoudness(int l);
	// 重低音 level (0-24)
	void  CE_HardwareDll_API SetSubw(int s);
	// 重低音开关
	void  CE_HardwareDll_API SubwOn(BOOL on);

	// 通道相位调整
	/*
		ch	: 通道 0-5 FL FR RL RR SubwL SubwR
		rev : 0=不反转, 1=翻转
	*/
	void  CE_HardwareDll_API SoundPhase(int ch, BOOL rev);
	// 通道延时调整
	/*
		ch	: 通道 1-5 FL FR RL RR 
		delay : 延时时间,ms, 所有通道之和不超过20ms, 简单处理的话,每个通道不超过3ms, 最小分辨率0.1ms
	*/
	enum
	{
		AUDIOCH_FL = 1,
		AUDIOCH_FR = 2,
		AUDIOCH_RL = 4,
		AUDIOCH_RR = 8,
		AUDIOCH_SubWL = 16,
		AUDIOCH_SubWR = 32
	};
	void  CE_HardwareDll_API SoundDelay(int ch, double delay);

	BOOL  CE_HardwareDll_API IsMute();
	void  CE_HardwareDll_API Beep();
	void  CE_HardwareDll_API SetVolume(int vol);
	int   CE_HardwareDll_API GetVolume();
	void  CE_HardwareDll_API SetNavVolume(int vol);
	// 视频控制
	int   CE_HardwareDll_API SourceCheck();
	void   CE_HardwareDll_API BackLight(BOOL b);					
	void   CE_HardwareDll_API BackLightLevel(unsigned char l);	// 背光等级,不是所有硬件都支持
	// 设置 CPU LCD 控制器的亮度和对比度,可以影响所有显示画面,调节幅度和效果较差
	void  CE_HardwareDll_API CPUSetBright(int bright);
	void  CE_HardwareDll_API CPUSetContrast(int c);
	// 设置 屏幕驱动IC 的亮度和对比度,可以影响所有显示画面,调节效果好,仅仅在系统有驱动IC时才可以用
	void  CE_HardwareDll_API LCDSetBright(int b);
	void  CE_HardwareDll_API LCDSetContrast(int c);

	void  CE_HardwareDll_API LCDBrightDown();
	void  CE_HardwareDll_API LCDBrightResume();
	// 设置 模拟视频解码芯片 的亮度,对比度和颜色,仅仅影响dvd,aux,tv等视频画面,调节效果好
	void  CE_HardwareDll_API VideoSetBrght(int bright);
	void  CE_HardwareDll_API VideoSetContrast(int c);
	void  CE_HardwareDll_API VideoSetColor(int color); 
	// 外部输出123
	enum EXTOUTPUT
	{
		EXTOUTPUT_ANDROID,
		EXTOUTPUT_TV,
		EXTOUTPUT_BT,
		EXTOUTPUT_RADIO,
		EXTOUTPUT_AUX,
		EXTOUTPUT_IPOD,
		EXTOUTPUT_DVD,
		EXTOUTPUT_CE,
		EXTOUTPUT_AUTO
	};
	void  CE_HardwareDll_API SetAutoExt1Out(BOOL bAuto);
	void  CE_HardwareDll_API SetAutoExt2Out(BOOL bAuto);
	void  CE_HardwareDll_API SetAutoExt3Out(BOOL bAuto);

	void  CE_HardwareDll_API ExtOut1(EXTOUTPUT output);
	void  CE_HardwareDll_API ExtOut2(EXTOUTPUT output);
	void  CE_HardwareDll_API ExtOut3(EXTOUTPUT output);

	void  CE_HardwareDll_API SetResType(int type);
}

