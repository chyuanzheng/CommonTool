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
	// ����Ƶ�л�
	void  CE_HardwareDll_API ToRadio();
	void  CE_HardwareDll_API ToDVD();
	void  CE_HardwareDll_API ToIpod();
	void  CE_HardwareDll_API ToAux();
	void  CE_HardwareDll_API ToTV();
	void  CE_HardwareDll_API ToMedia();
	void  CE_HardwareDll_API ToBTMusic();
	void  CE_HardwareDll_API ToNavi();
	void  CE_HardwareDll_API CloseAuxOutput();
	// �����绰ʱ����
	void  CE_HardwareDll_API ToBTPhone();
	// �����绰�Ҷ�ʱ����
	void  CE_HardwareDll_API LeaveBTPhone();
	// ��Ƶ����
	void  CE_HardwareDll_API Mute();
	void  CE_HardwareDll_API UnMute();
	void  CE_HardwareDll_API AMPPowerOn();
	void  CE_HardwareDll_API AMPPowerOff();
	void  CE_HardwareDll_API SetSoundAffect(int affect);
	// ��������,���ĵ�(x=0,y=0) ǰ:y>0 ��:x>0
	void  CE_HardwareDll_API SetSoundField(int x, int y);
	void  CE_HardwareDll_API SetEQ(int eq);

	/*
		band		: GEQ����, (0-8)
		fc			: ����Ƶ��, (20-15000)
		Q			: Q ֵ (1-100) ��Ӧ 0.1-10
	*/
	void  CE_HardwareDll_API ConfigGEQ(int band, int fc, int Q);
/*
		band		: GEQ����, (0-9)
		level		: ����, (-12-12)
	*/
	void  CE_HardwareDll_API SetGEQ(int band, int level);
	// ����EQ����
	/*
		band		: PEQ����, (0-6)
		center_freq	: ����Ƶ��, (20-20000)
		Q			: Q ֵ (1-100) ��Ӧ 0.1-10
		level		: ���� (-14-14)
	*/
	void  CE_HardwareDll_API SetPEQ(int band, int center_freq, int Q, int level);
	void  CE_HardwareDll_API SetTreble(int trebel);
	void  CE_HardwareDll_API SetMiddle(int midd);
	void  CE_HardwareDll_API SetBass(int bass);
	void  CE_HardwareDll_API SetLoudness(int l);
	// �ص��� level (0-24)
	void  CE_HardwareDll_API SetSubw(int s);
	// �ص�������
	void  CE_HardwareDll_API SubwOn(BOOL on);

	// ͨ����λ����
	/*
		ch	: ͨ�� 0-5 FL FR RL RR SubwL SubwR
		rev : 0=����ת, 1=��ת
	*/
	void  CE_HardwareDll_API SoundPhase(int ch, BOOL rev);
	// ͨ����ʱ����
	/*
		ch	: ͨ�� 1-5 FL FR RL RR 
		delay : ��ʱʱ��,ms, ����ͨ��֮�Ͳ�����20ms, �򵥴���Ļ�,ÿ��ͨ��������3ms, ��С�ֱ���0.1ms
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
	// ��Ƶ����
	int   CE_HardwareDll_API SourceCheck();
	void   CE_HardwareDll_API BackLight(BOOL b);					
	void   CE_HardwareDll_API BackLightLevel(unsigned char l);	// ����ȼ�,��������Ӳ����֧��
	// ���� CPU LCD �����������ȺͶԱȶ�,����Ӱ��������ʾ����,���ڷ��Ⱥ�Ч���ϲ�
	void  CE_HardwareDll_API CPUSetBright(int bright);
	void  CE_HardwareDll_API CPUSetContrast(int c);
	// ���� ��Ļ����IC �����ȺͶԱȶ�,����Ӱ��������ʾ����,����Ч����,������ϵͳ������ICʱ�ſ�����
	void  CE_HardwareDll_API LCDSetBright(int b);
	void  CE_HardwareDll_API LCDSetContrast(int c);

	void  CE_HardwareDll_API LCDBrightDown();
	void  CE_HardwareDll_API LCDBrightResume();
	// ���� ģ����Ƶ����оƬ ������,�ԱȶȺ���ɫ,����Ӱ��dvd,aux,tv����Ƶ����,����Ч����
	void  CE_HardwareDll_API VideoSetBrght(int bright);
	void  CE_HardwareDll_API VideoSetContrast(int c);
	void  CE_HardwareDll_API VideoSetColor(int color); 
	// �ⲿ���123
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

