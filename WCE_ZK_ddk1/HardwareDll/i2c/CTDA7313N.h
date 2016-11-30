#pragma once

#include "stdAfx.h"
#include "iic.h"

class CTDA7313N
{
		//7313音频控制
		//地址：0x88
		//子地址为控制位：
		//具体控制方式如下：

		//一个字节8个位从左到右为

		//值XXXXXXXX
		//位76543210

		//================================================================
		//7、6为00时表示音量控制
		//----------------------------------------------------------------
		//其中2、1、0为从0dB开始值每加1后减小1.25dB直到-8.75dB
		//0,	-1.25,	-2.5,	-3.75,	-5,	-6.25,	-7.5,	-8.75	具体值
		//000	001	010	011	100	101	110	111	二进制表示值

		//其中5、4、3为从0dB开始值每加1后减小10dB直到-70dB
		//0,	-10,	-20,	-30,	-40,	-50,	-60,	-70	具体值
		//000	001	010	011	100	101	110	111	二进制表示值

		//例如音量为-45dB可以表示为
		//值00100100
		//位76543210
		//7、6为音量，5、4、3为-40dB，2、1、0为-5dB

		//================================================================
		//7、6、5为110时为左后声道输出控制
		//7、6、5为111时为右后声道输出控制
		//7、6、5为100时为左前声道输出控制
		//7、6、5为101时为右前声道输出控制
		//----------------------------------------------------------------
		//其中2、1、0为从0dB开始值每加1后减小1.25dB直到-8.75dB
		//0,	-1.25,	-2.5,	-3.75,	-5,	-6.25,	-7.5,	-8.75	具体值
		//000	001	010	011	100	101	110	111	二进制表示值

		//其中4、3为从0dB开始值每加1后减小10dB直到-30dB
		//0,	-10,	-20,	-30,	具体值
		//00	01	10	11	二进制表示值

		//其中4、3、2、1、0都为1时为静音

		//例如右前声道衰减25dB可以表示为
		//值10110100
		//位76543210
		//7、6、5为右前声道，4、3为-20dB，2、1、0为-5dB

		//================================================================
		//7、6、5为010时为声音开关控制
		//----------------------------------------------------------------
		//其中1、0为00时为立体声1通道
		//其中1、0为01时为立体声2通道
		//其中1、0为10时为立体声3通道
		//其中1、0为11时为立体声4通道（链接在内部，无可用脚）

		//其中2为大声（LOUNDNESS ON)开关，0为开，1为关

		//其中4、3为从+11.25dB开始值每加1后减小3.75dB直到0dB
		//11.25,	7.5,	3.75,	0,	具体值
		//00	01	10	11	二进制表示值

		//例如选择立体声2通道增加7.5dB并打开LOUNDNESS ON开关可以表示为
		//值01001001
		//位76543210
		//7、6、5声音开关控制，4、3为+7.5dB，2为开，1、0为立体声2通道

		//==================================================================
		//7、6、5、4为0110时为低音控制（***）容易错，注意有符号位，加1时值在负时为增加，值在正的时候为减少。
		//7、6、5、4为0111时为高音控制
		//------------------------------------------------------------------
		//其中2、1、0为从-14dB开始值每加1后增加2dB直到0dB
		//-14,	-12,	-10,	-8,	-6，	-4，	-2，	0，	具体值
		//000	001	010	011	100	101	110	111	二进制表示值

		//其中2、1、0为从14dB开始值每加1后减小2dB直到0dB
		//14，	12，	10，	8，	6，	4，	2，	0	具体值
		//000	001	010	011	100	101	110	111	二进制表示值

		//其中3为符号位（***）

		//例如低音-10dB可表示为
		//值01100010
		//位76543210
		//7、6、5、4低音控制，3为-，2、1、0为10db
		static const BYTE slaveAddr = 0x88;              // 默认地址为0x88(8位地址）
		BYTE WriteBytes[9];

public:
		/// <summary>
		/// 音源选择
		/// </summary>
		enum AudioSwitch { Stereo1, Stereo2, Stereo3, Stereo4, NONE };
		/// <summary>
		/// 音箱选择
		/// </summary>
		enum SpeakerAtten { LF, RF, LR, RR };
		/// <summary>
		/// 低音高音选择
		/// </summary>
		enum BassTreble { Bass, Treble };
public: 
		CTDA7313N()
		{
			WriteBytes[0] = slaveAddr;// 设置芯片地址
			
			// 此处是初始值
			VolumeByte = 0x0;     // 音量
			Volume = 0;

			//7、6、5为110时为左后声道输出控制
			//7、6、5为111时为右后声道输出控制
			//7、6、5为100时为左前声道输出控制
			//7、6、5为101时为右前声道输出控制

			LRByte = 0xC0;         // 后置左声道衰减	110 00000
			LRAtten = 0;
			RRByte = 0xE0;         // 后置右声道衰减	111 00000
			RRAtten = 0;
			LFByte = 0x80;         // 前置左声道衰减	100 00000
			LFAtten = 0;
			RFByte = 0xA0;         // 前置右声道衰减	101 00000
			RFAtten = 0;
			AudioSwitchByte = 0x40;// 音频选择开关
			BassByte = 0x67;       // 低音控制
			BASS = 0;
			TrebleByte = 0x77;     // 高音控制
			TrebleControl = 0;
			
			currAudioSwitch = NONE;
		}

		BOOL Init7313()
		{
#ifdef UIONLY
			return 1;
#else
			return SetALL();
#endif
		}
		/// <summary>
		/// 音量
		/// </summary>
		//private int volume = 0;
		/// <summary>
		/// 音量73级可调0~72，72最大
		/// </summary>
		int Volume;
		/// <summary>
		/// 后左声道衰减
		/// </summary>
		///private int lRAtten = 0;
		/// <summary>
		/// 后左声道衰减，0~31，0为不衰减，31为静音
		/// </summary>
		int LRAtten;
		/// <summary>
		/// 后右声道衰减
		/// </summary>
		//private int rRAtten = 0;
		/// <summary>
		/// 后右声道衰减，0~31，0为不衰减，31为静音
		/// </summary>
		int RRAtten;
		/// <summary>
		/// 前左声道衰减，0~31，0为不衰减，31为静音
		/// </summary>
		int LFAtten;
		/// <summary>
		/// 前右声道衰减，0~31，0为不衰减，31为静音
		/// </summary>
		int RFAtten;
		/// <summary>
		/// 低音控制
		/// </summary>
		//private int bASS = 0;
		/// <summary>
		/// 低音控制，-7~7，共15级
		/// </summary>
		int BASS;
		/// <summary>
		/// 高音控制，-7~7，共15级
		/// </summary>
		int TrebleControl;
		/// <summary>
		/// 当前声道选择，便于查询用
		/// </summary>
		AudioSwitch currAudioSwitch;


		/// <summary>
		/// 响度开关
		/// </summary>
		//private bool lOUDNESSon = true;
		/// <summary>
		/// 响度开关
		/// </summary>
		int LOUDNESS;
		// 此处是初始值
		BYTE VolumeByte;      // 音量
		BYTE LRByte;          // 后置左声道衰减         
		BYTE RRByte;          // 后置右声道衰减
		BYTE LFByte;          // 前置左声道衰减
		BYTE RFByte;          // 前置右声道衰减
		BYTE AudioSwitchByte; // 音频选择开关
		BYTE BassByte;        // 低音控制
		BYTE TrebleByte;      // 高音控制

		/// <summary>
		/// 增大音量，之后需要调用SetALL()
		/// </summary>
		/// <returns>是否成功增大音量</returns>
		bool VolumeAdd()
		{
#ifdef UIONLY
			return true;
#else
			if (Volume >72)
			{
				Volume = 72;
				return false;
			}
			else
			{
				Volume += 1;
				return VolumeToSetBytes(Volume);
			}            
#endif
		}
		/// <summary>
		/// 减小音量，之后需要调用SetALL()
		/// </summary>
		/// <returns>是否成功减小音量</returns>
		bool VolumeDec()
		{
#ifdef UIONLY
			return true;
#else
			if (Volume < 0)
			{
				Volume = 0;
				return false;
			}
			else
			{
				Volume -= 1;
				return VolumeToSetBytes(Volume);
			}
#endif
		}
		/// <summary>
		/// 根据具体数值设置声音，之后需要调用SetALL()
		/// </summary>
		/// <param name="pvolume">要设置的数值72为最大，最小为0</param>
		/// <returns>是否成功设置</returns>
		//public bool VolumeSet(int pvolume)
		//{
		//    if (pvolume >= 0 && pvolume < 73)
		//    {
		//        Volume = pvolume;
		//        return VolumeToSetBytes(Volume);
		//    }
		//    else
		//    {
		//        return false;
		//    }
		//}
		/// <summary>
		/// 音量表，由具体数值修改相应的数据位
		/// </summary>
		/// <param name="volume"></param>
		bool VolumeToSetBytes(int volume)
		{
#ifdef UIONLY
			return true;
#else
			if (volume < 64 && volume >= 0)
			{
				//+0dB
				//AudioSwitchByte |= 0x18;
				//AudioSwitchByte &= 0xFF;
				//-(78.75~0)dB
				VolumeByte = (byte)(63 - volume);
			}
			return true;
#endif
		}
		/// <summary>
		/// 增加某声道的衰减，之后需要调用SetALL()
		/// </summary>
		/// <param name="pspeakeratten">声道选择</param>
		/// <returns>是否成功增大</returns>
		bool SpeakerAttenAdd(SpeakerAtten pspeakeratten)
		{
			bool result = false;
			switch (pspeakeratten)
			{
			case  LF:
				{
					if (LFAtten > 31)
					{
						LFAtten = 31;
						result = false;
					}
					else
					{
						LFAtten++;
						result = AttenToSetBytes(pspeakeratten, LFAtten);
					}
					break;
				}
			case  LR:
				{
					if (LRAtten > 31)
					{
						LRAtten = 31;
						result = false;
					}
					else
					{
						LRAtten++;
						result = AttenToSetBytes(pspeakeratten, LRAtten);
					}
					break;
				}
			case  RF:
				{
					if (RFAtten > 31)
					{
						RFAtten = 31;
						result = false;
					}
					else
					{
						RFAtten++;
						result = AttenToSetBytes(pspeakeratten, RFAtten);
					}
					break;
				}
			case  RR:
				{
					if (RRAtten > 31)
					{
						RRAtten = 31;
						result = false;
					}
					else
					{
						RRAtten++;
						result = AttenToSetBytes(pspeakeratten, RRAtten);
					}
					break;
				}
			}
			return result;
		}
		/// <summary>
		/// 减小某声道的衰减，之后需要调用SetALL()
		/// </summary>
		/// <param name="pspeakeratten">声道选择</param>
		/// <returns>是否成功减小</returns>
		bool SpeakerAttenDec(SpeakerAtten pspeakeratten)
		{
			bool result = false;
			switch (pspeakeratten)
			{
			case  LF:
				{
					if (LFAtten < 0)
					{
						LFAtten = 0;
						result = false;
					}
					else
					{
						LFAtten--;
						result = AttenToSetBytes(pspeakeratten, LFAtten);
					}
					break;
				}
			case  LR:
				{
					if (LRAtten < 0)
					{
						LRAtten = 0;
						result = false;
					}
					else
					{
						LRAtten--;
						result = AttenToSetBytes(pspeakeratten, LRAtten);
					}
					break;
				}
			case  RF:
				{
					if (RFAtten < 0)
					{
						RFAtten = 0;
						result = false;
					}
					else
					{
						RFAtten--;
						result = AttenToSetBytes(pspeakeratten, RFAtten);
					}
					break;
				}
			case  RR:
				{
					if (RRAtten < 0)
					{
						RRAtten = 0;
						result = false;
					}
					else
					{
						RRAtten--;
						result = AttenToSetBytes(pspeakeratten, RRAtten);
					}
					break;
				}
			}
			return result;
		}
		/// <summary>
		/// 设置某声道的衰减，之后需要调用SetALL()
		/// </summary>
		/// <param name="pspeakeratten">声道选择</param>
		/// <param name="pvolume">衰减值
		/// </param>
		/// <returns>是否成功设置</returns>
		bool SpeakerAttenSet(SpeakerAtten pspeakeratten, int Atten)
		{
			bool result = false;
			switch (pspeakeratten)
			{
			case  LF:
				{
					if (Atten >= 0 && Atten < 32)
					{
						LFAtten = Atten;
						result = AttenToSetBytes(pspeakeratten, Atten);
					}
					else
					{
						result = false;
					}
					break;
				}
			case  LR:
				{
					if (Atten >= 0 && Atten < 32)
					{
						LRAtten = Atten;
						result = AttenToSetBytes(pspeakeratten, Atten);
					}
					else
					{
						result = false;
					}
					break;
				}
			case  RF:
				{
					if (Atten >= 0 && Atten < 32)
					{
						RFAtten = Atten;
						result = AttenToSetBytes(pspeakeratten, Atten);
					}
					else
					{
						result = false;
					}
					break;
				}
			case  RR:
				{
					if (Atten >= 0 && Atten < 32)
					{
						RRAtten = Atten;
						result = AttenToSetBytes(pspeakeratten, Atten);
					}
					else
					{
						result = false;
					}
					break;
				}
			}
			return result;
		}
		/// <summary>
		/// 声道衰减，由具体数值修改相应的数据位
		/// </summary>
		/// <param name="pspeakeratten"></param>
		/// <param name="Atten"></param>
		/// <returns></returns>
		bool AttenToSetBytes(SpeakerAtten pspeakeratten, int Atten)
		{
			switch (pspeakeratten)
			{
			case  LF:
				{
					LFByte &= 0xe0;
					LFByte |= (byte)Atten;
					break;
				}
			case  LR:
				{
					LRByte &= 0xe0;
					LRByte |= (byte)Atten;
					break;
				}
			case  RF:
				{
					RFByte &= 0xe0;
					RFByte |= (byte)Atten;
					break;
				}
			case  RR:
				{
					RRByte &= 0xe0;
					RRByte |= (byte)Atten;
					break;
				}
			}
			return true;
		}
		/// <summary>
		/// 高低音增大，之后需要调用SetALL()
		/// </summary>
		/// <param name="pbasstreble">高低音选择</param>
		/// <returns>是否成功增大</returns>
		bool BTAdd(BassTreble pbasstreble)
		{
			bool result = false;
			switch (pbasstreble)
			{
			case  Bass:
				{
					if (BASS>7)
					{
						BASS = 7;
						result = false;
					}
					else
					{
						BASS++;
						result = BTToSetBytes(pbasstreble, BASS);
					}  
					break;
				}
			case  Treble:
				{
					if (TrebleControl > 7)
					{
						TrebleControl = 7;
						result = false;
					}
					else
					{
						TrebleControl++;
						result = BTToSetBytes(pbasstreble, TrebleControl);
					}
					break;
				}
			}
			return result;
		}
		/// <summary>
		/// 高低音减小，之后需要调用SetALL()
		/// </summary>
		/// <param name="pbasstreble">高低音选择</param>
		/// <returns>是否成功减小</returns>
		bool BTDec(BassTreble pbasstreble)
		{
			bool result = false;
			switch (pbasstreble)
			{
			case  Bass:
				{
					if (BASS < -7)
					{
						BASS = -7;
						result = false;
					}
					else
					{
						BASS--;
						result = BTToSetBytes(pbasstreble, BASS);
					}
					break;
				}
			case  Treble:
				{
					if (TrebleControl < -7)
					{
						TrebleControl = -7;
						result = false;
					}
					else
					{
						TrebleControl--;
						result = BTToSetBytes(pbasstreble, TrebleControl);
					}
					break;
				}
			}
			return result;
		}
		/// <summary>
		/// 高低音设置，之后需要调用SetALL()
		/// </summary>
		/// <param name="pbasstreble">高低音选择</param>
		/// <param name="pvolume">音量</param>
		/// <returns>是否成功设置</returns>
		//public bool BTSet(BassTreble pbasstreble, int Atten)
		//{
		//    bool result = false;
		//    switch (pbasstreble)
		//    {
		//        case  Bass:
		//            {
		//                if (BASS <= 7 && BASS >= -7)
		//                {
		//                    BASS = Atten;
		//                    result = BTToSetBytes(pbasstreble, Atten);
		//                }
		//                else
		//                {
		//                    result = false;
		//                }
		//                break;
		//            }
		//        case  Treble:
		//            {
		//                if (Treble <= 7 && Treble >= -7)
		//                {
		//                    Treble = Atten;
		//                    result = false;
		//                }
		//                else
		//                {
		//                    result = BTToSetBytes(pbasstreble, Atten);
		//                }
		//                break;
		//            }
		//    }
		//    return result;
		//}
		/// <summary>
		/// 高低音设置，由具体数值修改相应的数据位
		/// </summary>
		/// <param name="pbasstreble"></param>
		/// <param name="Atten"></param>
		/// <returns></returns>
		bool BTToSetBytes(BassTreble pbasstreble, int Atten)
		{
			byte tempbyte = 0x00;
			switch (Atten)
			{
			case -7:
				{
					tempbyte = 0x00;
					break;
				}
			case -6:
				{
					tempbyte = 0x01;
					break;
				}
			case -5:
				{
					tempbyte = 0x02;
					break;
				}
			case -4:
				{
					tempbyte = 0x03;
					break;
				}
			case -3:
				{
					tempbyte = 0x04;
					break;
				}
			case -2:
				{
					tempbyte = 0x05;
					break;
				}
			case -1:
				{
					tempbyte = 0x06;
					break;
				}
			case 0:
				{
					tempbyte = 0x07;
					break;
				}
			case 1:
				{
					tempbyte = 0x0e;
					break;
				}
			case 2:
				{
					tempbyte = 0x0d;
					break;
				}
			case 3:
				{
					tempbyte = 0x0c;
					break;
				}
			case 4:
				{
					tempbyte = 0x0b;
					break;
				}
			case 5:
				{
					tempbyte = 0x0a;
					break;
				}
			case 6:
				{
					tempbyte = 0x09;
					break;
				}
			case 7:
				{
					tempbyte = 0x08;
					break;
				}
			}
			switch (pbasstreble)
			{
			case  Bass:
				{
					BassByte &= 0xf0;
					BassByte |= tempbyte;
					break;
				}
			case  Treble:
				{
					TrebleByte &= 0xf0;
					TrebleByte |= tempbyte;
					break;
				}
			}
			return true;
		}
		/// <summary>
		/// 音源选择，之后需要调用SetALL()
		/// </summary>
		/// <param name="paudioswitch">四声道为内部声道，注意！</param>
		/// <returns></returns>
		BOOL AudioSwitchSet(AudioSwitch paudioswitch, BYTE a=0x3)
		{
			currAudioSwitch = paudioswitch;
			//AudioSwitchByte = 0x40;// 音频选择开关
			AudioSwitchByte &= ~(0x3<<3);
			AudioSwitchByte |= (a<<3);
			switch (paudioswitch)
			{
			case  Stereo1:	// DVD
				{
					//AudioSwitchByte &= ~(0x1<<3);
					AudioSwitchByte &= 0xFC;
					AudioSwitchByte |= 0x00;
					//STLOG_WRITE("AudioSwitchSet : DVD");
					break;
				}
			case  Stereo2:	// RADIO
				{
					//AudioSwitchByte &= ~(0x3<<3);
					AudioSwitchByte &= 0xFC;
					AudioSwitchByte |= 0x01;
					//STLOG_WRITE("AudioSwitchSet : RADIO");
					break;
				}
			case  Stereo3:	// GPS
				{
					// AudioSwitchByte &= ~(0x1<<3); 降低增益
					AudioSwitchByte &= 0xFC;
					AudioSwitchByte |= 0x02;
					//STLOG_WRITE("AudioSwitchSet : GPS");
					break;
				}
			case  Stereo4: // PHONE, 提高增益
				{
					//AudioSwitchByte &= ~(0x2<<3);
					AudioSwitchByte &= 0xFC;
					AudioSwitchByte |= 0x03;
					//STLOG_WRITE("AudioSwitchSet : PHONE");
					break;
				}
			}
			return TRUE;
		}
		/// <summary>
		/// 响度开关，之后需要调用SetALL()
		/// </summary>
		/// <param name="ploudness">开？关</param>
		/// <returns>是否成功设置</returns>
		bool Loudness(bool ploudness)
		{
			//LOUDNESSon = ploudness;
			if (ploudness) 
			{
				AudioSwitchByte |= 0x00;
				AudioSwitchByte &= 0xFB;
			}
			else
			{
				AudioSwitchByte |= 0x04;
				AudioSwitchByte &= 0xFF;
			}
			return true;
		}
		/// <summary>
		/// 设置所有参数，并写入，调用任何公用函数时都应该最后调用这个函数才能执行。
		/// </summary>
		/// <returns></returns>
		BOOL SetALL()
		{
			WriteBytes[1] = VolumeByte;         // 音量
			WriteBytes[2] = LRByte;             // 后置左声道衰减
			WriteBytes[3] = RRByte;             // 后置右声道衰减
			WriteBytes[4] = LFByte;             // 前置左声道衰减
			WriteBytes[5] = RFByte;             // 前置右声道衰减
			WriteBytes[6] = AudioSwitchByte;    // 音频选择开关
			WriteBytes[7] = BassByte;           // 低音控制
			WriteBytes[8] = TrebleByte;         // 高音控制
			return WriteIIC();
		}

		BOOL SetVolume()
		{
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = VolumeByte;
			return IICWrite4(data,2);
		}
		
		BOOL SetLR(int atten)
		{	
			if (atten > 31)
			{
				atten = 31;
			}
			if (atten < 0)
			{
				atten = 0;
			}
			LRAtten = atten;
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = LRByte | atten;
			return IICWrite4(data,2);
		}

		BOOL SetRR(int atten)
		{
			if (atten > 31)
			{
				atten = 31;
			}
			if (atten < 0)
			{
				atten = 0;
			}
			RRAtten = atten;
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = RRByte | atten;
			return IICWrite4(data,2);
		}

		BOOL SetLF(int atten)
		{
			if (atten > 31)
			{
				atten = 31;
			}
			if (atten < 0)
			{
				atten = 0;
			}
			LFAtten = atten;
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = LFByte | atten;
			return IICWrite4(data,2);
		}

		BOOL SetRF(int atten)
		{
			if (atten > 31)
			{
				atten = 31;
			}
			if (atten < 0)
			{
				atten = 0;
			}
			RFAtten = atten;
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = RFByte | atten;
			return IICWrite4(data,2);
		}
		
		BOOL SetSwitch()
		{
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = AudioSwitchByte;
			return IICWrite4(data,2);
		}

		BOOL SetBass(int bass)
		{
			bass = -bass;
			if (bass > 7 || bass < -7)
			{
				return FALSE;
			}
			if (bass >= 0)
			{
				BassByte  = 0x60 | (BYTE)(7-bass);
			}
			else
			{
				BassByte = 0x68 | (BYTE)(7+bass);
			}
			BASS = bass;
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = BassByte;
			return IICWrite4(data,2);
		}

		BOOL SetTreble(int treble)
		{
			treble = -treble;
			if (treble > 7 || treble < -7)
			{
				return FALSE;
			}
			if (treble >= 0)
			{
				TrebleByte  = 0x70 | (BYTE)(7-treble);
			}
			else
			{
				TrebleByte = 0x78 | (BYTE)(7+treble);
			}
			TrebleControl = treble;
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			data[1] = TrebleByte;
			return IICWrite4(data,2);
		}

		BOOL SetLoudness(int loudness)
		{
			if (loudness<0 || loudness>4)
			{
				return FALSE;
			}
			LOUDNESS = loudness;
			BYTE data[2] = {0};
			data[0] = slaveAddr;
			if (loudness) 
			{
				AudioSwitchByte &= ~0x4;
			}
			else
			{
				AudioSwitchByte |= 0x4;
			}
			data[1] = AudioSwitchByte;
			return IICWrite4(data,2);
		}
		/// <summary>
		/// I2C写入
		/// </summary>
	private:
		BOOL WriteIIC()
		{
#ifdef UIONLY
			return 1;
#else
			return IICWrite4(WriteBytes,9);
#endif
		}

};

