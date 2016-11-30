#pragma once

#include "stdAfx.h"
#include "iic.h"

class CTDA7313N
{
		//7313��Ƶ����
		//��ַ��0x88
		//�ӵ�ַΪ����λ��
		//������Ʒ�ʽ���£�

		//һ���ֽ�8��λ������Ϊ

		//ֵXXXXXXXX
		//λ76543210

		//================================================================
		//7��6Ϊ00ʱ��ʾ��������
		//----------------------------------------------------------------
		//����2��1��0Ϊ��0dB��ʼֵÿ��1���С1.25dBֱ��-8.75dB
		//0,	-1.25,	-2.5,	-3.75,	-5,	-6.25,	-7.5,	-8.75	����ֵ
		//000	001	010	011	100	101	110	111	�����Ʊ�ʾֵ

		//����5��4��3Ϊ��0dB��ʼֵÿ��1���С10dBֱ��-70dB
		//0,	-10,	-20,	-30,	-40,	-50,	-60,	-70	����ֵ
		//000	001	010	011	100	101	110	111	�����Ʊ�ʾֵ

		//��������Ϊ-45dB���Ա�ʾΪ
		//ֵ00100100
		//λ76543210
		//7��6Ϊ������5��4��3Ϊ-40dB��2��1��0Ϊ-5dB

		//================================================================
		//7��6��5Ϊ110ʱΪ��������������
		//7��6��5Ϊ111ʱΪ�Һ������������
		//7��6��5Ϊ100ʱΪ��ǰ�����������
		//7��6��5Ϊ101ʱΪ��ǰ�����������
		//----------------------------------------------------------------
		//����2��1��0Ϊ��0dB��ʼֵÿ��1���С1.25dBֱ��-8.75dB
		//0,	-1.25,	-2.5,	-3.75,	-5,	-6.25,	-7.5,	-8.75	����ֵ
		//000	001	010	011	100	101	110	111	�����Ʊ�ʾֵ

		//����4��3Ϊ��0dB��ʼֵÿ��1���С10dBֱ��-30dB
		//0,	-10,	-20,	-30,	����ֵ
		//00	01	10	11	�����Ʊ�ʾֵ

		//����4��3��2��1��0��Ϊ1ʱΪ����

		//������ǰ����˥��25dB���Ա�ʾΪ
		//ֵ10110100
		//λ76543210
		//7��6��5Ϊ��ǰ������4��3Ϊ-20dB��2��1��0Ϊ-5dB

		//================================================================
		//7��6��5Ϊ010ʱΪ�������ؿ���
		//----------------------------------------------------------------
		//����1��0Ϊ00ʱΪ������1ͨ��
		//����1��0Ϊ01ʱΪ������2ͨ��
		//����1��0Ϊ10ʱΪ������3ͨ��
		//����1��0Ϊ11ʱΪ������4ͨ�����������ڲ����޿��ýţ�

		//����2Ϊ������LOUNDNESS ON)���أ�0Ϊ����1Ϊ��

		//����4��3Ϊ��+11.25dB��ʼֵÿ��1���С3.75dBֱ��0dB
		//11.25,	7.5,	3.75,	0,	����ֵ
		//00	01	10	11	�����Ʊ�ʾֵ

		//����ѡ��������2ͨ������7.5dB����LOUNDNESS ON���ؿ��Ա�ʾΪ
		//ֵ01001001
		//λ76543210
		//7��6��5�������ؿ��ƣ�4��3Ϊ+7.5dB��2Ϊ����1��0Ϊ������2ͨ��

		//==================================================================
		//7��6��5��4Ϊ0110ʱΪ�������ƣ�***�����״�ע���з���λ����1ʱֵ�ڸ�ʱΪ���ӣ�ֵ������ʱ��Ϊ���١�
		//7��6��5��4Ϊ0111ʱΪ��������
		//------------------------------------------------------------------
		//����2��1��0Ϊ��-14dB��ʼֵÿ��1������2dBֱ��0dB
		//-14,	-12,	-10,	-8,	-6��	-4��	-2��	0��	����ֵ
		//000	001	010	011	100	101	110	111	�����Ʊ�ʾֵ

		//����2��1��0Ϊ��14dB��ʼֵÿ��1���С2dBֱ��0dB
		//14��	12��	10��	8��	6��	4��	2��	0	����ֵ
		//000	001	010	011	100	101	110	111	�����Ʊ�ʾֵ

		//����3Ϊ����λ��***��

		//�������-10dB�ɱ�ʾΪ
		//ֵ01100010
		//λ76543210
		//7��6��5��4�������ƣ�3Ϊ-��2��1��0Ϊ10db
		static const BYTE slaveAddr = 0x88;              // Ĭ�ϵ�ַΪ0x88(8λ��ַ��
		BYTE WriteBytes[9];

public:
		/// <summary>
		/// ��Դѡ��
		/// </summary>
		enum AudioSwitch { Stereo1, Stereo2, Stereo3, Stereo4, NONE };
		/// <summary>
		/// ����ѡ��
		/// </summary>
		enum SpeakerAtten { LF, RF, LR, RR };
		/// <summary>
		/// ��������ѡ��
		/// </summary>
		enum BassTreble { Bass, Treble };
public: 
		CTDA7313N()
		{
			WriteBytes[0] = slaveAddr;// ����оƬ��ַ
			
			// �˴��ǳ�ʼֵ
			VolumeByte = 0x0;     // ����
			Volume = 0;

			//7��6��5Ϊ110ʱΪ��������������
			//7��6��5Ϊ111ʱΪ�Һ������������
			//7��6��5Ϊ100ʱΪ��ǰ�����������
			//7��6��5Ϊ101ʱΪ��ǰ�����������

			LRByte = 0xC0;         // ����������˥��	110 00000
			LRAtten = 0;
			RRByte = 0xE0;         // ����������˥��	111 00000
			RRAtten = 0;
			LFByte = 0x80;         // ǰ��������˥��	100 00000
			LFAtten = 0;
			RFByte = 0xA0;         // ǰ��������˥��	101 00000
			RFAtten = 0;
			AudioSwitchByte = 0x40;// ��Ƶѡ�񿪹�
			BassByte = 0x67;       // ��������
			BASS = 0;
			TrebleByte = 0x77;     // ��������
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
		/// ����
		/// </summary>
		//private int volume = 0;
		/// <summary>
		/// ����73���ɵ�0~72��72���
		/// </summary>
		int Volume;
		/// <summary>
		/// ��������˥��
		/// </summary>
		///private int lRAtten = 0;
		/// <summary>
		/// ��������˥����0~31��0Ϊ��˥����31Ϊ����
		/// </summary>
		int LRAtten;
		/// <summary>
		/// ��������˥��
		/// </summary>
		//private int rRAtten = 0;
		/// <summary>
		/// ��������˥����0~31��0Ϊ��˥����31Ϊ����
		/// </summary>
		int RRAtten;
		/// <summary>
		/// ǰ������˥����0~31��0Ϊ��˥����31Ϊ����
		/// </summary>
		int LFAtten;
		/// <summary>
		/// ǰ������˥����0~31��0Ϊ��˥����31Ϊ����
		/// </summary>
		int RFAtten;
		/// <summary>
		/// ��������
		/// </summary>
		//private int bASS = 0;
		/// <summary>
		/// �������ƣ�-7~7����15��
		/// </summary>
		int BASS;
		/// <summary>
		/// �������ƣ�-7~7����15��
		/// </summary>
		int TrebleControl;
		/// <summary>
		/// ��ǰ����ѡ�񣬱��ڲ�ѯ��
		/// </summary>
		AudioSwitch currAudioSwitch;


		/// <summary>
		/// ��ȿ���
		/// </summary>
		//private bool lOUDNESSon = true;
		/// <summary>
		/// ��ȿ���
		/// </summary>
		int LOUDNESS;
		// �˴��ǳ�ʼֵ
		BYTE VolumeByte;      // ����
		BYTE LRByte;          // ����������˥��         
		BYTE RRByte;          // ����������˥��
		BYTE LFByte;          // ǰ��������˥��
		BYTE RFByte;          // ǰ��������˥��
		BYTE AudioSwitchByte; // ��Ƶѡ�񿪹�
		BYTE BassByte;        // ��������
		BYTE TrebleByte;      // ��������

		/// <summary>
		/// ����������֮����Ҫ����SetALL()
		/// </summary>
		/// <returns>�Ƿ�ɹ���������</returns>
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
		/// ��С������֮����Ҫ����SetALL()
		/// </summary>
		/// <returns>�Ƿ�ɹ���С����</returns>
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
		/// ���ݾ�����ֵ����������֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="pvolume">Ҫ���õ���ֵ72Ϊ�����СΪ0</param>
		/// <returns>�Ƿ�ɹ�����</returns>
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
		/// �������ɾ�����ֵ�޸���Ӧ������λ
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
		/// ����ĳ������˥����֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="pspeakeratten">����ѡ��</param>
		/// <returns>�Ƿ�ɹ�����</returns>
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
		/// ��Сĳ������˥����֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="pspeakeratten">����ѡ��</param>
		/// <returns>�Ƿ�ɹ���С</returns>
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
		/// ����ĳ������˥����֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="pspeakeratten">����ѡ��</param>
		/// <param name="pvolume">˥��ֵ
		/// </param>
		/// <returns>�Ƿ�ɹ�����</returns>
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
		/// ����˥�����ɾ�����ֵ�޸���Ӧ������λ
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
		/// �ߵ�������֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="pbasstreble">�ߵ���ѡ��</param>
		/// <returns>�Ƿ�ɹ�����</returns>
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
		/// �ߵ�����С��֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="pbasstreble">�ߵ���ѡ��</param>
		/// <returns>�Ƿ�ɹ���С</returns>
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
		/// �ߵ������ã�֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="pbasstreble">�ߵ���ѡ��</param>
		/// <param name="pvolume">����</param>
		/// <returns>�Ƿ�ɹ�����</returns>
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
		/// �ߵ������ã��ɾ�����ֵ�޸���Ӧ������λ
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
		/// ��Դѡ��֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="paudioswitch">������Ϊ�ڲ�������ע�⣡</param>
		/// <returns></returns>
		BOOL AudioSwitchSet(AudioSwitch paudioswitch, BYTE a=0x3)
		{
			currAudioSwitch = paudioswitch;
			//AudioSwitchByte = 0x40;// ��Ƶѡ�񿪹�
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
					// AudioSwitchByte &= ~(0x1<<3); ��������
					AudioSwitchByte &= 0xFC;
					AudioSwitchByte |= 0x02;
					//STLOG_WRITE("AudioSwitchSet : GPS");
					break;
				}
			case  Stereo4: // PHONE, �������
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
		/// ��ȿ��أ�֮����Ҫ����SetALL()
		/// </summary>
		/// <param name="ploudness">������</param>
		/// <returns>�Ƿ�ɹ�����</returns>
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
		/// �������в�������д�룬�����κι��ú���ʱ��Ӧ�������������������ִ�С�
		/// </summary>
		/// <returns></returns>
		BOOL SetALL()
		{
			WriteBytes[1] = VolumeByte;         // ����
			WriteBytes[2] = LRByte;             // ����������˥��
			WriteBytes[3] = RRByte;             // ����������˥��
			WriteBytes[4] = LFByte;             // ǰ��������˥��
			WriteBytes[5] = RFByte;             // ǰ��������˥��
			WriteBytes[6] = AudioSwitchByte;    // ��Ƶѡ�񿪹�
			WriteBytes[7] = BassByte;           // ��������
			WriteBytes[8] = TrebleByte;         // ��������
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
		/// I2Cд��
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

