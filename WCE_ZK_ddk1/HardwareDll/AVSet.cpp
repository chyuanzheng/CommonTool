#include "stdafx.h"
#include "../i2c/chip.h"
#include "Audio/Audio.h"
#include "Video/Video.h"
#include "AVSet.h"
#include <math.h>

namespace AVSET
{
	int output1_type = EXTOUTPUT_AUTO;
	int output2_type = EXTOUTPUT_AUTO;
	int output3_type = EXTOUTPUT_AUTO;
	CRITICAL_SECTION	*Section::avset_cs = NULL;

	void Init()
	{
		Section::GET();
		Audio::Init(); 
		Video::Init();
	}

	void ToRadio()
	{
		Audio::ToRadio();
		chip_fms6502.Output1Select(FMS6502::INPUT_OFF);
		chip_fms6502.Output2Select(FMS6502::INPUT_OFF);
	}

	void ToDVD()
	{
		Audio::ToDVD();
		Video::ToDVD();
		if (output1_type)
		{
			ExtOut1(EXTOUTPUT_AUTO);
		}
		if (output2_type)
		{
			ExtOut2(EXTOUTPUT_AUTO);
		}
	}

	void ToIpod()
	{
		Audio::ToIpod();
		Video::ToIpod();
		if (output1_type)
		{
			ExtOut1(EXTOUTPUT_AUTO);
		}
		if (output2_type)
		{
			ExtOut2(EXTOUTPUT_AUTO);
		}
	}

	void ToAux()
	{
		Audio::ToAux();
		Video::ToAux();
		if (output1_type)
		{
			ExtOut1(EXTOUTPUT_AUTO);
		}
		if (output2_type)
		{
			ExtOut2(EXTOUTPUT_AUTO);
		}
	}

	void ToTV()
	{
		Audio::ToTV();
		Video::ToTV();
		if (output1_type)
		{
			ExtOut1(EXTOUTPUT_AUTO);
		}
		if (output2_type)
		{
			ExtOut2(EXTOUTPUT_AUTO);
		}
	}

	void ToNavi()
	{
		Audio::ToNavi();
	}

	void ToMedia()
	{
		Audio::ToMedia();
		/*if (output1_type)
		{
			ExtOut1(EXTOUTPUT_AUTO);
		}
		if (output2_type)
		{
			ExtOut2(EXTOUTPUT_AUTO);
		}*/
	}

	void CloseAuxOutput()
	{
		chip_fms6502.Output1Select(FMS6502::INPUT_OFF);
		chip_fms6502.Output2Select(FMS6502::INPUT_OFF);
	}

	void ToBTMusic()
	{
		Audio::ToBT();
		if (output1_type)
		{
			ExtOut1(EXTOUTPUT_AUTO);
		}
		if (output2_type)
		{
			ExtOut2(EXTOUTPUT_AUTO);
		}
	}

	void ToBTPhone()
	{
		Audio::Save();
		Audio::ToBT2();
		Sleep(10);
	}

	void LeaveBTPhone()
	{
		Audio::Restore();
	}

	void Mute()
	{
		Audio::Mute();
		RETAILMSG(COUT_MSG, (TEXT("---------mute-------\r\n")));
	}

	void UnMute()
	{
		Audio::UnMute();
		RETAILMSG(COUT_MSG, (TEXT("---------unmute------\r\n")));
	}

	void AMPPowerOn()
	{
		Audio::AMPPowerOn();
	}

	void AMPPowerOff()
	{
		Audio::AMPPowerOff();
	}

	void SetSoundAffect(int affect)
	{
		
	}

	void SetSoundField(int x, int y)
	{
		Audio::SetSoundField( x,  y);
	}	

	void SetEQ(int eq)
	{
		Audio::SetEq(eq);
	}

	void ConfigGEQ(int band, int fc, int Q)
	{

	}

	void SetGEQ(int band, int eq)
	{

	}

	void SetPEQ(int band, int center_freq, int Q, int level)
	{
		Audio::SetPEQ(band, center_freq, Q, level);
	}

	void SetTreble(int trebel)
	{
		Audio::SetTreble(trebel);
	}

	void SetMiddle(int midd)
	{
		Audio::SetMiddle(midd);
	}

	void SetBass(int bass)
	{
		Audio::SetBass(bass);
	}

	void SetLoudness(int lound)
	{
		Audio::SetLoudness(lound);
	}

	void  SetSubw( int s )
	{
		Audio::SetSubw(s);
	}

	void SubwOn(BOOL on)
	{
		Audio::SubwOn(on);
	}

	void SoundPhase(int ch, BOOL rev)
	{

	}

	void SoundDelay(int ch, double delay)
	{
		Audio::SoundDelay(ch, delay);
	}

	BOOL IsMute()
	{
		return Audio::IsMute();
	}

	void Beep()
	{
		Audio::Beep();
	}

	void SetVolume(int vol)
	{
		Audio::SetVolume(vol);
	}

	int GetVolume()
	{
		return Audio::GetVolume();
	}

	void SetNaviVolume(int vol)
	{
		Audio::SetNaviVolume(vol);
	}

	int SourceCheck()
	{
		EnterCriticalSection(Section::GET());
		int ret = Video::SourceCheck();
		LeaveCriticalSection(Section::GET());
		return ret;
	}	

	void BackLight(BOOL b)
	{
		Video::BackLight(b);
	}

	void BackLightLevel(unsigned char l)
	{
		Video::BackLightLevel(l);
	}

	void CPUSetBright(int bright)
	{
		Video::CPUSetBright(bright);
	}

	void CPUSetContrast(int c)
	{
		Video::CPUSetContrast(c);
	}

	int bright = 0;
	int lcd_down = 0;
	void LCDSetBright(int b)
	{
		bright = b;
		if (lcd_down)
		{
			Video::LCDSetBright(b-5);
		}
		else
		{
			Video::LCDSetBright(b);
		}
	}

	void LCDBrightDown()
	{
		lcd_down = 1;
		LCDSetBright(bright);
	}

	void LCDBrightResume()
	{
		lcd_down = 0;
		LCDSetBright(bright);
	}

	void LCDSetContrast(int c)
	{
		Video::LCDSetContast(c);
	}

	void VideoSetBrght(int bright)
	{
		Video::VideoSetBrght(bright);
	}

	void VideoSetContrast(int c)
	{
		Video::VideoSetContrast(c);
	}

	void VideoSetColor(int color)
	{
		Video::VideoSetColor(color);
	}

	
	void ExtOut1(EXTOUTPUT output)
	{
		//chip_fms6502.GainControl(0xFF);
		switch(output)
		{
		case EXTOUTPUT_ANDROID:
			{
				// “Ù∆µ
				chip_njw1110.Out1Select(NJW1110::INPUT_1);
				//  ”∆µ
				chip_fms6502.Output1Select(FMS6502::INPUT_4);
				break;
			}
		case EXTOUTPUT_TV:
			{
				// “Ù∆µ
				chip_njw1110.Out1Select(NJW1110::INPUT_2);
				//  ”∆µ
				chip_fms6502.Output1Select(FMS6502::INPUT_3);
				break;
			}
		case EXTOUTPUT_AUX:
			{
				// “Ù∆µ
				chip_njw1110.Out1Select(NJW1110::INPUT_5);
				//  ”∆µ
				chip_fms6502.Output1Select(FMS6502::INPUT_8);
				break;
			}
		case EXTOUTPUT_IPOD:
			{
				// “Ù∆µ
				chip_njw1110.Out1Select(NJW1110::INPUT_6);
				//  ”∆µ
				chip_fms6502.Output1Select(FMS6502::INPUT_2);
				break;
			}
		case EXTOUTPUT_DVD:
			{
				// “Ù∆µ
				chip_njw1110.Out1Select(NJW1110::INPUT_7);
				//  ”∆µ
				chip_fms6502.Output1Select(FMS6502::INPUT_6);
				break;
			}
		case EXTOUTPUT_CE:
			{
				// “Ù∆µ
				chip_njw1110.Out1Select(NJW1110::INPUT_8);
				//  ”∆µ
				chip_fms6502.Output1Select(FMS6502::INPUT_5);
				//chip_fms6502.GainControl(0xFF);
				break;
			}
		case EXTOUTPUT_AUTO:
			{
				// “Ù∆µ
				switch(Audio::GetCH())
				{
				case Audio::AUDIO_TV:	// tv android bt
					{
						chip_njw1110.Out1Select(NJW1110::INPUT_2);
						//  ”∆µ
						chip_fms6502.Output1Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_BT:
					{
						chip_njw1110.Out1Select(NJW1110::INPUT_3);
						break;
					}
				case Audio::AUDIO_RADIO:	// radio
					{
						chip_njw1110.Out1Select(NJW1110::INPUT_4);
						//  ”∆µ
						chip_fms6502.Output1Select(FMS6502::INPUT_1);
						break;
					}
				case Audio::AUDIO_AUX:	// aux
					{
						chip_njw1110.Out1Select(NJW1110::INPUT_5);
						//  ”∆µ
						chip_fms6502.Output1Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_IPOD:	// ipod
					{
						chip_njw1110.Out1Select(NJW1110::INPUT_6);
						//  ”∆µ
						chip_fms6502.Output1Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_DVD:	// dvd
					{
						chip_njw1110.Out1Select(NJW1110::INPUT_7);
						//  ”∆µ
						chip_fms6502.Output1Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_MEDIA:	// ce
					{
						// “Ù∆µ
						chip_njw1110.Out1Select(NJW1110::INPUT_8);
						//  ”∆µ
						//chip_fms6502.Output1Select(FMS6502::INPUT_5);
						//chip_fms6502.GainControl(0xFF);
						break;
					}
				}
				
				break;
			}
		}
	}
	
	void ExtOut2(EXTOUTPUT output)
	{
		//chip_fms6502.GainControl(0xFF);
		switch(output)
		{
		case EXTOUTPUT_ANDROID:
			{
				// “Ù∆µ
				chip_njw1110.Out2Select(NJW1110::INPUT_1, NJW1110::GAIN_70);
				//  ”∆µ
				chip_fms6502.Output2Select(FMS6502::INPUT_4);
				break;
			}
		case EXTOUTPUT_TV:
			{
				// “Ù∆µ
				chip_njw1110.Out2Select(NJW1110::INPUT_2);
				//  ”∆µ
				chip_fms6502.Output2Select(FMS6502::INPUT_3);
				break;
			}
		case EXTOUTPUT_AUX:
			{
				// “Ù∆µ
				chip_njw1110.Out2Select(NJW1110::INPUT_5, NJW1110::GAIN_70);
				//  ”∆µ
				chip_fms6502.Output2Select(FMS6502::INPUT_8);
				break;
			}
		case EXTOUTPUT_IPOD:
			{
				// “Ù∆µ
				chip_njw1110.Out2Select(NJW1110::INPUT_6, NJW1110::GAIN_80);
				//  ”∆µ
				chip_fms6502.Output2Select(FMS6502::INPUT_2);
				break;
			}
		case EXTOUTPUT_DVD:
			{
				// “Ù∆µ
				chip_njw1110.Out2Select(NJW1110::INPUT_7, NJW1110::GAIN_50);
				//  ”∆µ
				chip_fms6502.Output2Select(FMS6502::INPUT_6);
				break;
			}
		case EXTOUTPUT_CE:
			{
				// “Ù∆µ 
				chip_njw1110.Out2Select(NJW1110::INPUT_8, NJW1110::GAIN_80);
				//  ”∆µ
				chip_fms6502.Output2Select(FMS6502::INPUT_5);
				//chip_fms6502.GainControl(0xFF);
				break;
			}
		case EXTOUTPUT_AUTO:
			{
				// “Ù∆µ
				switch(Audio::GetCH())
				{
				case Audio::AUDIO_TV:	// tv android bt
					{
						chip_njw1110.Out2Select(NJW1110::INPUT_2);
						//  ”∆µ
						chip_fms6502.Output2Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_BT:
					{
						chip_njw1110.Out2Select(NJW1110::INPUT_3);
						break;
					}
				case Audio::AUDIO_RADIO:	// radio
					{
						chip_njw1110.Out2Select(NJW1110::INPUT_4);
						//  ”∆µ
						chip_fms6502.Output2Select(FMS6502::INPUT_1);
						break;
					}
				case Audio::AUDIO_AUX:	// aux
					{
						chip_njw1110.Out2Select(NJW1110::INPUT_5);
						//  ”∆µ
						chip_fms6502.Output2Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_IPOD:	// ipod
					{
						chip_njw1110.Out2Select(NJW1110::INPUT_6);
						//  ”∆µ
						chip_fms6502.Output2Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_DVD:	// dvd
					{
						chip_njw1110.Out2Select(NJW1110::INPUT_7);
						//  ”∆µ
						chip_fms6502.Output2Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_MEDIA:	// ce
					{
						// “Ù∆µ
						chip_njw1110.Out1Select(NJW1110::INPUT_8);
						//  ”∆µ
						chip_fms6502.Output1Select(FMS6502::INPUT_5);
						//chip_fms6502.GainControl(0xFF);
						break;
					}
				}

				break;
			}
		}
	}
	
	void ExtOut3(EXTOUTPUT output)
	{
		//chip_fms6502.GainControl(0xFF);
		switch(output)
		{
		case EXTOUTPUT_ANDROID:
			{
				// “Ù∆µ
				chip_njw1110.Out3Select(NJW1110::INPUT_1);
				break;
			}
		case EXTOUTPUT_TV:
			{
				// “Ù∆µ
				chip_njw1110.Out3Select(NJW1110::INPUT_2);
				break; 
			}
		case EXTOUTPUT_AUX:
			{
				// “Ù∆µ
				chip_njw1110.Out3Select(NJW1110::INPUT_5);
				break;
			}
		case EXTOUTPUT_IPOD:
			{
				// “Ù∆µ
				chip_njw1110.Out3Select(NJW1110::INPUT_6);
				break;
			}
		case EXTOUTPUT_DVD:
			{
				// “Ù∆µ
				chip_njw1110.Out3Select(NJW1110::INPUT_7);
				break;
			}
		case EXTOUTPUT_CE:
			{
				// “Ù∆µ 
				chip_njw1110.Out3Select(NJW1110::INPUT_8);
				break;
			}
		case EXTOUTPUT_AUTO:
			{
				// “Ù∆µ
				switch(Audio::GetCH())
				{
				case Audio::AUDIO_TV:	// tv android bt
					{
						chip_njw1110.Out3Select(NJW1110::INPUT_2);
						//  ”∆µ
						chip_fms6502.Output3Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_BT:
					{
						chip_njw1110.Out3Select(NJW1110::INPUT_3);
						break;
					}
				case Audio::AUDIO_RADIO:	// radio
					{
						chip_njw1110.Out3Select(NJW1110::INPUT_4);
						//  ”∆µ
						chip_fms6502.Output3Select(FMS6502::INPUT_1);
						break;
					}
				case Audio::AUDIO_AUX:	// aux
					{
						chip_njw1110.Out3Select(NJW1110::INPUT_5);
						//  ”∆µ
						chip_fms6502.Output3Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_IPOD:	// ipod
					{
						chip_njw1110.Out3Select(NJW1110::INPUT_6);
						//  ”∆µ
						chip_fms6502.Output3Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_DVD:	// dvd
					{
						chip_njw1110.Out3Select(NJW1110::INPUT_7);
						//  ”∆µ
						chip_fms6502.Output3Select(chip_fms6502.GetMainInput());
						break;
					}
				case Audio::AUDIO_MEDIA:	// ce
					{
						chip_njw1110.Out3Select(NJW1110::INPUT_8);
						//  ”∆µ
						chip_fms6502.Output3Select(chip_fms6502.GetMainInput());
						break;
					}
				}

				break;
			}
		}
	}

}

void AVSET::SetResType(int type)
{
	MCU::NJW2573Output(type);
}

