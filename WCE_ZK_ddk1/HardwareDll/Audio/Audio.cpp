#include "stdafx.h"
#include "../i2c/chip.h"
#include "Audio.h"
#include "../Hero/public.h"
#include "../Hero/Hero_Audio_Drv.h"
#include "GXNotify.h"
#include "pip/PIP.h"

#include "../chdll/include/common_h/VersionXml.h"

#define pi 3.1415926

int Audio::volume = 0;
BOOL Audio::mute = 0;
BOOL Audio::navi_mute = 0;
BOOL Audio::subw_mute = 0;
int Audio::nowCH = AUDIO_NONE;
int Audio::saveCH = AUDIO_NONE;
int Audio::media_atten = 0;

int mode = AUDIO_NORMALMODE;
int inNaviMode = 0;
int inPhoneMode = 0;

VersionXml* pVersionXml = NULL;		//用于读取XML的值。作为全局变量。 add by yf 
VersionXml::Option_NaviMixSound naviMixSound;	//用于保存混音是否开关 add by yf

BOOL hw_version = 0;
void Audio::Init()
{
	Init_Hero();
	AMPPowerOn();

	//读取XML	add by yf
	pVersionXml = VersionXml::GetInstance();
	naviMixSound = pVersionXml->GetNaviMix();
	
	//判断是否混音，做不同的处理	add by yf
	if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		Audio_DrvSetStreamInput(NavigationStr, INPUT_SOURCE_IIS1);
		//Audio_DrvSetStreamInput(PhoneStr, INPUT_SOURCE_AIN0);
		//Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	}
	else
	{
		Audio_DrvSetStreamInput(NavigationStr, INPUT_SOURCE_IIS1);
		NavMixSwitch(0);
	}
	
	if (pVersionXml->GetBSFModule() == VersionXml::Navi_BSF_Added)
	{
		// 设置DAC输出重低音
		WriteHero_MEM_1Word(I2CDRV_X_MEM, ADSP_X_FDACpntr, ADSP_X_SwOutL_REL);
		WriteHero_MEM_1Word(I2CDRV_X_MEM, ADSP_X_RDACpntr, ADSP_X_SwOutL_REL);
		// 设置 subw 使用四阶低通滤波器
		Audio_DrvPEQConfig(4, 4);
		hw_version = 1;
	}
}

void Audio::Mute()
{
	mute = 1;
	Audio_DrvSoftMuteSwitch(0xFFFF,1);		//shut down all channels softmute
	Sleep(200);
	chip_tda7801.Mute();
	chip_mcu.AMPMute(1);
	
}

void Audio::MuteNoKeyTone()
{
	Audio_DrvSoftMuteSwitch(0xFFFF,1);		//shut down all channels softmute
}

void Audio::UnMute()
{
	mute = 0;
	U16 ch = 0xFFFF;
	if (navi_mute)
	{
		ch &= ~Audio_NCHANNEL;
	}
	if (subw_mute)
	{
		ch &= ~(Audio_SWLCHANNEL | Audio_SWRCHANNEL);
	}
	Audio_DrvSoftMuteSwitch(ch,0);		//shut down all channels softmute
	Sleep(200);
	chip_tda7801.UnMute();
	chip_mcu.AMPMute(0);
}

void Audio::AMPPowerOff()
{
	chip_tda7801.PowerOff();
}

void Audio::AMPPowerOn()
{
	chip_tda7801.PowerOn();
}

void Audio::MuteKey()
{
	if (mute)
	{
		UnMute();
	}
	else
	{
		Mute();
	}
}

void Audio::SetVolume(int vol)
{
	if (vol == 0)
	{
		Audio_DrvSoftMuteSwitch(Audio_PCHANNEL, 1);
	}
	else if(volume == 0)
	{
		Audio_DrvSoftMuteSwitch(Audio_PCHANNEL, 0);
	}
	volume = vol;
	switch(media_atten)
	{
	case 1:
		vol = vol*2/3;
		break;
	case 2:
		vol = vol/2;
		break;
	case 3:
		vol = vol/4;
		break;
	}
	Audio_SetVolume(PrimaryStr, vol);
}

void Audio::SetVolumeTmp(int vol)
{
	if (vol == 0)
	{
		Audio_DrvSoftMuteSwitch(Audio_PCHANNEL, 1);
	}
	else if(volume == 0)
	{
		Audio_DrvSoftMuteSwitch(Audio_PCHANNEL, 0);
	}
	Audio_SetVolume(PrimaryStr, vol);
}

void Audio::MixVolume(int vol)
{

}

int Audio::GetVolume()
{
	return Audio::volume;
}

void Audio::VolDown()
{
	volume--;
	if (volume < 0)
	{
		volume = 0;
	}

}

void Audio::VolUp()
{
	volume++;
	if (volume>MaxVolume)
	{
		volume = MaxVolume;
	}

}

void Audio::ToRadio()
{
	if (saveCH != AUDIO_NONE)
	{
		saveCH = AUDIO_RADIO;
		return;
	}
	nowCH = AUDIO_RADIO;
	Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_RADIO);

	
	
	//判断是否混音，做不同的处理	add by yf
	//if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		NavMixSwitch(1);
	}
}

void Audio::ToDVD()
{
	if (saveCH != AUDIO_NONE)
	{;
		saveCH = AUDIO_DVD;
		return;
	}
	nowCH = AUDIO_DVD;
	// i2s 0
	Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_IIS0);

	//判断是否混音，做不同的处理	add by yf
	//if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		NavMixSwitch(1);
	}
}

void Audio::ToBT()
{
	if (saveCH != AUDIO_NONE)
	{
		saveCH = AUDIO_BT;
		return;
	}
	nowCH = AUDIO_BT;
	if (hw_version == 0)
	{
		// ain 0
		chip_njw2753.OutputSelect(NJW2753::INPUT_1);
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN0);	
	}
	if (hw_version == 1)
	{
		// ain 1
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN1);	
	}
	

	
	//判断是否混音，做不同的处理	add by yf
	//if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		NavMixSwitch(1);
	}

}

void Audio::ToBT2()
{
	// ain 0
	if (hw_version == 0)
	{
		// ain 0
		chip_njw2753.OutputSelect(NJW2753::INPUT_1);
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN0);	
	}
	if (hw_version == 1)
	{
		// ain 1
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN1);	
	}
}

void Audio::ToMedia()
{
	if (saveCH != AUDIO_NONE)
	{
		saveCH = AUDIO_MEDIA;
		return;
	}
	nowCH = AUDIO_MEDIA;
	// i2s 1
	Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_IIS1);

	//判断是否混音，做不同的处理	add by yf
	//if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		NavMixSwitch(0);
	}

	GXNotify::SendNotify("set_navi_vol", 0, 0);
}

void Audio::ToIpod()
{
	if (saveCH != AUDIO_NONE)
	{
		saveCH = AUDIO_IPOD;
		return;
	}
	nowCH = AUDIO_IPOD;
	// ain 1
	Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_IIS1);	

	//判断是否混音，做不同的处理	add by yf
	//if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		NavMixSwitch(0);
	}

	GXNotify::SendNotify("set_navi_vol", 0, 0);
}
void Audio::ToAux()
{
	if (saveCH != AUDIO_NONE)
	{
		saveCH = AUDIO_AUX;
		return;
	}
	nowCH = AUDIO_AUX;
	if (hw_version == 0)
	{
		// ain 0
		chip_njw2753.OutputSelect(NJW2753::INPUT_3);
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN0);	
	}
	if (hw_version == 1)
	{
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN0);	
	}
		

	//判断是否混音，做不同的处理	add by yf
	//if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		NavMixSwitch(1);
	}
}
void Audio::ToNavi()
{
	/*if (saveCH != AUDIO_NONE)
	{
		saveCH = AUDIO_NAVI;
		return;
	}
	Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_IIS1);

	NavMixSwitch(0);*/
}
void Audio::ToTV()
{
	if (saveCH != AUDIO_NONE)
	{
		saveCH = AUDIO_TV;
		return;
	}
	nowCH = AUDIO_TV;
	if (hw_version == 0)
	{
		// ain 0
		chip_njw2753.OutputSelect(NJW2753::INPUT_2);
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN0);	
	}
	else
	{
		// ain 
		Audio_DrvSetStreamInput(PrimaryStr, INPUT_SOURCE_AIN2);	
	}

	//判断是否混音，做不同的处理	add by yf
	//if(naviMixSound == VersionXml::Navi_Mix_Removed)	//无导航混音
	{
		NavMixSwitch(1);
	}

}
void Audio::Restore()
{
	int ch = saveCH;
	saveCH = AUDIO_NONE;
	switch(ch)
	{
	case AUDIO_RADIO:
		{
			ToRadio();
			break;
		}
	case AUDIO_DVD:
		{
			ToDVD();
			break;
		}
	case AUDIO_BT:
		{
			ToBT();
			break;
		}
	case AUDIO_MEDIA:
		{
			ToMedia();
			break;
		}
	case AUDIO_IPOD:
		{
			ToIpod();
			break;
		}
	case AUDIO_AUX:
		{
			ToAux();
			break;
		}
	case AUDIO_NAVI:
		{
			ToNavi();
			break;
		}
	case AUDIO_TV:
		{
			ToTV();
			break;
		}
	}
}

void Audio::Save()
{
	saveCH = nowCH;
}

void Audio::SetTreble(int t)
{
	// 为了兼容以前范围为-9到9
	Audio_DrvTrebSet(PrimaryStr, t*2, _10000_HZ);
}

void Audio::SetMiddle(int m)
{
	// 为了兼容以前范围为-9到9
	Audio_DrvMidSet(PrimaryStr, m*2, _500_HZ);

}

void Audio::SetBass(int b)
{
	// 为了兼容以前范围为-9到9
	Audio_DrvBassSet(PrimaryStr, b*2, _80_HZ);
}

void Audio::SetFL(int v)
{

}

void Audio::SetFR(int v)
{

}

void Audio::SetRL(int v)
{

}

void Audio::SetRR(int v)
{
}


void Audio::SetSoundField(int x, int y)
{
	S8 iXpos = -x*2;
	S8 iYpos = -y*2;
	Audio_SetFader(&iYpos);
	Audio_SetBalance(PrimaryStr, &iXpos);


	//// x y 从 0-30 15 中间
	//// 声场点距离喇叭越近(取x,y中的大值),该喇叭声音越大
	//int lf = 0;	// 前左
	//int lr = 0;	// 后左
	//int rf = 0;	// 前右
	//int rr = 0; // 后右
	//if (iYpos >= CENTERVOL)
	//{
	//	// 前左 前右衰减
	//	lf = iYpos-CENTERVOL;
	//	rf = iYpos-CENTERVOL;
	//}
	//else
	//{
	//	// 后左,后右衰减
	//	lr = CENTERVOL-iYpos;
	//	rr = CENTERVOL-iYpos;
	//}
	//if (iXpos >= CENTERVOL)
	//{
	//	// 前左,后左衰减
	//	lf = max(lf, iXpos-CENTERVOL);
	//	lr = max(lr, iXpos-CENTERVOL);
	//}
	//else
	//{
	//	// 前右,后右衰减
	//	rf = max(rf, CENTERVOL-iXpos);
	//	rr = max(rr, CENTERVOL-iXpos);
	//}
	//// vw           me		color
	//// rr			lr		purple
	//// fl			rf		write
	//// rl			lf		green
	//// fr			rr		gray
	//SetRR(rf);	// 
	//SetFL(lr);	// 
	//SetFR(lf);	// 
	//SetRL(rr);	// 
}

BOOL Audio::IsMute()
{
	return mute;
}

void Audio::Beep()
{
	if (IsMute())
	{
		return;
	}
	::Beep(0);
}

void Audio::BeepVol(BYTE vol)
{
	if (vol > 7)
	{
		return;
	}
	const static int beep_vol[8] =
	{
		-66,
		-56,
		-46,
		-36,
		-26,
		-16,
		-6,
		0
	};
	Audio_DrvSetChimeMasterVol(beep_vol[vol]);
}

int Audio::GetCH()
{
	return nowCH;
}

void Audio::SetEq(int eq)
{
	Audio_SetEQMode(eq);
}

int cutoff = 50, level = 0;
void Audio::SetSubw(int s)
{
	
	level = s;
	double a01, a02, a11, a12, b00, b01, b02, b10, b11, b12;
	double g, t0, t1, t2;
	double fs, fc;
	fs = 44100;
	fc = cutoff;
	g=pow(10, (level-12)/20.0);
	t0 = tan(pi*fc/fs);
	t1 = 1+2*cos(pi/8)*t0+t0*t0;
	t2 = 1+2*cos(3*pi/8)*t0+t0*t0;
	a01 = (1-t0*t0)/t1;
	a02 = (2*cos(pi/8)*t0-1-t0*t0)/(2*t1);
	a11 = (1-t0*t0)/t2;
	a12 = (2*cos(3*pi/8)*t0-1-t0*t0)/(2*t2);
	
	b00 = t0*t0/t1/2;
	b01 = 2*b00;
	b02 = b00;

	b10 = g*t0*t0/2/t2;
	b11 = 2*b10;
	b12 = b10;

	int B00[2], B01[2], B02[2], A01[2], A02[2];
	Hero_TransDouble2XYHexData(HERO_2YDATA, b00, B00);
	Hero_TransDouble2XYHexData(HERO_2YDATA, b01, B01);
	Hero_TransDouble2XYHexData(HERO_2YDATA, b02, B02);
	Hero_TransDouble2XYHexData(HERO_2YDATA, a01, A01);
	Hero_TransDouble2XYHexData(HERO_2YDATA, a02, A02);
	U32 coefs[10] = {B00[1], B00[0], B01[1], B01[0], B02[1], B02[0], A01[1], A01[0], A02[1], A02[0]};
	int B10[2], B11[2], B12[2], A11[2], A12[2];
	Hero_TransDouble2XYHexData(HERO_2YDATA, b10, B10);
	Hero_TransDouble2XYHexData(HERO_2YDATA, b11, B11);
	Hero_TransDouble2XYHexData(HERO_2YDATA, b12, B12);
	Hero_TransDouble2XYHexData(HERO_2YDATA, a11, A11);
	Hero_TransDouble2XYHexData(HERO_2YDATA, a12, A12);
	U32 coefs2[10] = {B10[1], B10[0], B11[1], B11[0], B12[1], B12[0], A11[1], A11[0], A12[1], A12[0]};
	Audio_DrvPEQSet(Center, BAND1, coefs);
	Audio_DrvPEQSet(Center, BAND2, coefs2);
	Audio_DrvPEQSet(SubWoofer, BAND1, coefs);
	Audio_DrvPEQSet(SubWoofer, BAND2, coefs2);
	
}

void Audio::SubwOn(BOOL on)
{
	if (on)
	{
		subw_mute = 0;
		if (IsMute() == 0)
		{
			// unmute subwoofer
			Audio_DrvSoftMuteSwitch(Audio_SWLCHANNEL | Audio_SWRCHANNEL, 0);
		}
		cutoff = on*50;
		SetSubw(level);
	}
	else
	{
		subw_mute = 1;
		// mute subwoofer
		Audio_DrvSoftMuteSwitch(Audio_SWLCHANNEL | Audio_SWRCHANNEL, 1);
	}
}

void Audio::SetLoudness(int lound)
{
	if (lound)
	{
		Audio_SetLoudness(AUDIO_ON);
	}
	else
	{
		Audio_SetLoudness(AUDIO_OFF);
	}
}

// PEQ 使用2阶带通滤波器
	/* 参数:
			band : 0-6	         
			fc : 中心频率      (20-20k)
			Q  : Q值           (1-100 对应 0.1-10)
			G  : 增益          (-14-14)
	   参考文档 UM_Audio_TEF6635_TEF6638_V1C0_20120511.pdf Page132 & Page138
       band1-4:
	   G=(pow(10, Gdb/20)-1)/4;
       t= 2*pi*fc/fs;
	   if(Gdb >=0)
	   {
	     D=1;
	   }
	   else
	   {
	     D=1/(4G+1);
	   }
	   a2 = -0.5*(1-D*(t/2Q))/(1+D*(t/2Q));
	   a1 = (0.5-a2)*cos(t);
	   b0=(0.5+a2)/2;

	   band567公式:
	   Gmax = 20*log10(2+Q*fs/(pi*fc);
	   g = pow(10, G/20);
	   t0 = 2pi*fc/fs
	   if(g>=1)
	   {
	      beta = t0/2Q;
	   }
	   else
	   {
		  beta = t0/(2*g*Q)
	   }
	   a2 = (-1/2)*(1-beta)/(1+beta);
	   a1 = (0.5-a2)cos(t0);
	   b0 = (g-1)*(0.25+0.5*a2)+0.5;
	   b1 = -a1;
	   b2 = -(g-1)*(0.25+0.5*a2)-a2;
	*/
void Audio::SetPEQ(int band, int center_freq, int Q, int level)
{
	//RETAILMSG(1, (TEXT("band = %d center_freq = %d Q = %d level = %d\r\n"), band, center_freq, Q, level));

	if (band < 4)
	{
		double a1, a2, b0;
		double G, t, D;
		double q, fs, fc;
		q = Q/10.0;
		fs = 44100;
		fc = center_freq;
		G=(pow(10, level/20.0)-1)/4;
		t= 2*pi*fc/fs;
		if(level >=0)
		{
			D=1;
		}
		else
		{
			D=1/(4*G+1);
		}
		a2 = -0.5*(1-D*(t/(2*q)))/(1+D*(t/(2*q)));
		a1 = (0.5-a2)*cos(t);
		b0=(0.5+a2)/2;

		int bG;
		bG = G*2048;
		int B0[2], A1[2], A2[2];
		Hero_TransDouble2XYHexData(HERO_2YDATA, b0, B0);
		Hero_TransDouble2XYHexData(HERO_2YDATA, a1, A1);
		Hero_TransDouble2XYHexData(HERO_2YDATA, a2, A2);
		U32 coefs[7] = {B0[1], B0[0], A2[1], A2[0], A1[1], A1[0], bG}; // b0 a2 a1 g L-H
		Audio_DrvPEQSet(FrontLeft, band, coefs);
		Audio_DrvPEQSet(FrontRight, band, coefs);
		Audio_DrvPEQSet(RearLeft, band, coefs);
		Audio_DrvPEQSet(RearRight, band, coefs);
	}
	if (band >= 4)
	{
		double a1, a2, b0, b1, b2;
		double gmax, g, t0, beta;
		double q, fs, fc;
		// band>=4 时 使用二阶滤波器,level最大值为12
		{
			if (level == 12)
			{
				level = 11;
			}
			else if (level == 14)
			{
				level = 12;
			}
			else if (level == -12)
			{
				level = -11;
			}
			else if (level == -14)
			{
				level = -12;
			}
		}
		q = Q/10.0;
		fs = 44100;
		fc = center_freq;
		g = pow(10, level/20.0);
		t0 = 2*pi*fc/fs;
		gmax = 20*log10(2+1*fs/(pi*fc));
		if (g>gmax)
		{
			g = gmax;
		}
		if(g>=1)
		{
			beta = t0/(2*q);
		}
		else
		{
			beta = t0/(2*g*Q);
		}
		a2 = -0.5*(1-beta)/(1+beta);
		a1 = (0.5-a2)*cos(t0);
		b0 = (g-1)*(0.25+0.5*a2)+0.5;
		b1 = -a1;
		b2 = -(g-1)*(0.25+0.5*a2)-a2;
		int B0[2], B1[2], B2[2], A1[2], A2[2];
		Hero_TransDouble2XYHexData(HERO_2YDATA, b0, B0);
		Hero_TransDouble2XYHexData(HERO_2YDATA, b1, B1);
		Hero_TransDouble2XYHexData(HERO_2YDATA, b2, B2);
		Hero_TransDouble2XYHexData(HERO_2YDATA, a1, A1);
		Hero_TransDouble2XYHexData(HERO_2YDATA, a2, A2);
		U32 coefs[10] = {B0[1], B0[0], B1[1], B1[0], B2[1], B2[0], A1[1], A1[0], A2[1], A2[0]};
		Audio_DrvPEQSet(FrontLeft, band, coefs);
		Audio_DrvPEQSet(FrontRight, band, coefs);
		Audio_DrvPEQSet(RearLeft, band, coefs);
		Audio_DrvPEQSet(RearRight, band, coefs);
	}
}

BOOL is_navi_mix = 0;
int navi_vol = 0;
void Audio::SetNaviVolume(int vol)
{
	RETAILMSG(COUT_MSG, (TEXT("Navi vol = %d\r\n"), vol));
	if (nowCH == AUDIO_MEDIA || nowCH == AUDIO_IPOD)
	{
		int media_vol = volume;
		if (sysConfig.sysParam.naviTips == 0)
		{
			switch(sysConfig.sysParam.naviAtten)
			{
			case 0:
				{
					media_vol = volume*2/3;
					break;
				}
			case 1:
				{
					media_vol = volume/3;
					break;
				}
			case 2:
				{
					media_vol = volume/8;
					break;
				}
			}
		}
		if (vol < media_vol)
		{
			
			//Navi::SetNaviVol(vol);

			GXNotify::SendNotify("set_navi_vol2", vol*10/volume, 0);
			vol = 0;
		}
		else
		{
			//Navi::SetNaviVol(10);
			GXNotify::SendNotify("set_navi_vol2", 10, 0);
			if (media_vol == volume)
			{
				vol = (vol-media_vol)*5/2;
			}
			else
			{
				vol = vol-media_vol;
			}
			if (sysConfig.sysParam.naviTips == 1)
			{
				// none
				// 计算导航音量与媒体音量的差
				int voldb = Audio::GetVolDistance(sysConfig.sysParam.curGPSVol , Audio::GetVolume());
				MediaControl::SetVolume(voldb/2);
				int ipod_vol = 30;
				if (sysConfig.sysParam.curGPSVol > Audio::GetVolume())
				{
					ipod_vol = ipod_vol-(sysConfig.sysParam.curGPSVol - Audio::GetVolume());
				}
				GXNotify::SendNotify("SetIPODVolume", ipod_vol, -1);
			}
		}
	}
	else
	{
		//Navi::SetNaviVol(10);
		if (vol == 0)
		{
			GXNotify::SendNotify("set_navi_vol2", 0, 0);
		}
		else
			GXNotify::SendNotify("set_navi_vol2", 10, 0);
	}
	Audio_SetVolume(NavigationStr, vol);
	if (vol == 0)
	{
		Audio_DrvSoftMuteSwitch(Audio_NCHANNEL, 1);
		navi_mute = 1;
	}
	else
	{
		navi_mute = 0;
		if (navi_vol == 0)
		{
			if(IsMute() == 0)
			{
				Audio_DrvSoftMuteSwitch(Audio_NCHANNEL, 0);
			}
		}
	}
	navi_vol = vol;
	
}

void Audio::NavMixSwitch(BOOL onoff)
{
	//return ;
	//Audio_DrvSetStreamInput(NavigationStr, INPUT_SOURCE_IIS1);
	if (onoff)
	{
		is_navi_mix = 1;
		Audio_ImposeNavOnFront(-16);
	}
	else
	{
		is_navi_mix = 0;
		Audio_ImposeNavOnFront(-71);
	}
}

void Audio::SoundDelay(int ch, double delay)
{
	Audio_DrvSetDelay(ch, delay);
}

int Audio::GetVolDistance(int h, int l)
{
	int ret = tblNaviVolLevelTrans[h] - tblVolLevelTrans[l];
	return ret>0?ret:0;
}

int Audio::GetVolDistance2(int h, int l)
{
	int ret = tblVolLevelTrans[h] - tblVolLevelTrans[l];
	return ret>0?ret:0;
}

void Audio::SetMediaVolInNavi(int vol)
{
	if (nowCH == AUDIO_MEDIA)
	{
		//vol = 0;
	}
	SetVolumeTmp(vol);
}

void Audio::SetMediaVolAttenInNavi(int atten)
{
	media_atten = atten;
	if (atten)
	{
		SetVolume(volume);
	}
}

void Audio::EnterNaviMode()
{
	mode = AUDIO_NAVIMODE;
	inNaviMode = 1;
	if (nowCH == AUDIO_IPOD || nowCH == AUDIO_MEDIA)
	{
		NavMixSwitch(1);
	}
}

void Audio::ExitNaviMode(int mode)
{
	if (mode == AUDIO_NAVIMODE)
	{
		if (inPhoneMode == 1)
		{
			mode = AUDIO_PHONEMODE;
		}
		else
			mode = AUDIO_NORMALMODE;
	}
	//MuteNavi();
	inNaviMode = 0;
	if (mode == 0)
	{
		if (nowCH == AUDIO_IPOD || nowCH == AUDIO_MEDIA)
		{
			NavMixSwitch(0);
		}
	}
	
}

int Audio::GetAudioMode()
{
	return mode;
}