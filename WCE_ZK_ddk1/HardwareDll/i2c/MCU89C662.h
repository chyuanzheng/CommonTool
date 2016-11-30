#pragma once

#include "stdAfx.h"
#include "iic.h"
#include "GXNotify.h"
#include "../LoadConfig.h"
#include "INC/Param.h"

/// <summary>
	/// MCU�����Լ�GPIO����
	/// </summary>
class MCU89C662
{
		/// <summary>
		/// ������
		/// </summary>
		BYTE ReadBytes;
		/// <summary>
		/// д����
		/// </summary>
		BYTE WriteBytes[3];
		/// <summary>
		/// ��Ļ��ʾģʽ
		/// </summary>
		enum screenmodo
		{
			full,       // ȫ��
			center,     // ����
			wide,       // ����
			zoom1,      // �Ŵ�1
			zoom2,      // �Ŵ�2
			zoom3,      // �Ŵ�3
			left,       // ������ʾ
			right       // ������ʾ
		};
public:
		BOOL bMute;

public:
		/// <summary>
		/// ���캯��
		/// </summary>
		MCU89C662()
		{
			WriteBytes[0] = MCUAdd;
			IICEnableByteData = 0x80;
		}

		/// <summary>
		/// ��ʼ��MCU
		/// </summary>
		void InitMcu()
		{
			InitPowerByte();
			InitAMPStandbyByte();
		}
		/// <summary>
		/// ��ʼ�����Ŵ����ֽ�
		/// </summary>
		BOOL InitAMPStandbyByte()
		{
			WriteBytes[1] = AMPStandbyByte;
			WriteBytes[2] = AMPStandbyByteData;
			return WriteIIC();
		}
		/// <summary>
		/// ��ʼ����Դ״̬�ֽ�
		/// </summary>
		BOOL InitPowerByte()
		{
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = POWERByteData;
			return WriteIIC();
		}
		/// <summary>
		/// ��Ƭ����ַ��8λ��
		/// </summary>
		static const BYTE MCUAdd = 0xD2;

		/// <summary>
		/// 9V��Դ����
		/// </summary>
		static const BYTE NineVPowerOn = 1<<4;
		/// <summary>
		/// 9V��Դֹͣ
		/// </summary>
		static const BYTE NineVPowerOff = ~(1<<4);
		/// <summary>
		/// DVD�ϵ�
		/// </summary>
		static const BYTE DVDPowenOn = 1<<5;
		/// <summary>
		/// DVD�µ�
		/// </summary>
		static const BYTE DVDPowerOff = ~(1<<5);
		/// <summary>
		/// ������ϵ�
		/// </summary>
		static const BYTE DVDCPowerOn = 0;
		/// <summary>
		/// ������µ�
		/// </summary>
		static const BYTE DVDCPowerOff = 0xff;
		/// <summary>
		/// �״��ϵ�
		/// </summary>
		static const BYTE RADARPowerOn = 0x00;
		/// <summary>
		/// �״�ϵ�
		/// </summary>
		static const BYTE RADARPowerOff = 0xff;
		/// <summary>
		/// �����ϵ�
		/// </summary>
		static const BYTE RADIOPowerOn = 1<<4;
		/// <summary>
		/// �����ϵ�
		/// </summary>
		static const BYTE RADIOPowerOff = ~(1<<4);
		/// <summary>
		/// ���Ŵ���
		/// </summary>
		static const BYTE AMPStadyBit = ~(1<<1);
		/// <summary>
		/// ����ȡ������
		/// </summary>
		static const BYTE AMPNoStadyBit = 1<<1;
		/// <summary>
		/// ���ž���
		/// </summary>
		static const BYTE AMPMuteBit = ~(1<<2);
		/// <summary>
		/// ���ŷǾ���
		/// </summary>
		static const BYTE AMPNoMuteBit = (1<<2);
		/// <summary>
		/// ���ߵ���
		/// </summary>
		static const BYTE RADIOANNTOut = 0x40;
		/// <summary>
		/// �����ջ�
		/// </summary>
		static const BYTE RADIOANNTIn = 0xbf;
		/// <summary>
		/// ��Ļ��������λ2��
		/// </summary>
		static const BYTE ScreenContral2On = 1<<1;
		/// <summary>
		/// ��Ļ��������λ2��
		/// </summary>
		static const BYTE ScreenContral2Off = ~(1<<1);
		/// <summary>
		/// ��Ļ��������λ1��
		/// </summary>
		static const BYTE ScreenContral1On = 1<<0;
		/// <summary>
		/// ��Ļ��������λ1��
		/// </summary>
		static const BYTE ScreenContral1Off = ~(1<<0);
		/// <summary>
		/// ������IIC����
		/// </summary>
		static const BYTE RadioIICEnable = 0xf7;
		/// <summary>
		/// ������IIC������
		/// </summary>
		static const BYTE RadioIICDisable = 0x08;
		/// <summary>
		/// 52795IIC����
		/// </summary>
		static const BYTE M52795Enable = 0xFB;
		/// <summary>
		/// 52795IIC������
		/// </summary>
		static const BYTE M52795Disable = 0x04;
		/// <summary>
		/// PT2313_1IIC����
		/// </summary>
		static const BYTE PT2313_1Enable = 0xfd;
		/// <summary>
		/// PT2313_1IIC������
		/// </summary>
		static const BYTE PT2313_1Disable = 0x02;
		/// <summary>
		/// PT2313_2IIC����
		/// </summary>
		static const BYTE PT2313_2Enable = 0xfe;
		/// <summary>
		/// PT2313_2IIC������
		/// </summary>
		static const BYTE PT2313_2Disable = 0x01;


//״̬�ֽڳ�����ַ��״̬�ֽڳ�ʼ״ַ̬
		/// <summary>
		/// ��Դ״̬�ֽ�
		/// </summary>
		static const BYTE POWERByte = 0x00;
		/// <summary>
		/// ��Դ״̬����
		/// ��ʼ״̬��4��9V��Դ�� 3��DVD��о��Դ�ر� 2����������Դ�� 1�������״��Դ�ر� 0����������Դ�ر�
		/// </summary>
		static const BYTE  POWERByteData = 1<<4;
		/// <summary>
		/// ���Ŵ����ֽ�
		/// </summary>
		static const BYTE AMPStandbyByte = 0x01;
		/// <summary>
		/// ���Ŵ�������
		/// ��ʼ״̬��4�����Ŵ���1�ǹ�����0�Ǵ���
		/// </summary>
		static const BYTE  AMPStandbyByteData = 0x00;
		/// <summary>
		/// ����
		/// </summary>
		static const BYTE  PowerOffData = 0x40;
		/// <summary>
		/// ��е�����ֽ�
		/// </summary>
		static const BYTE MechineByte = 0x02;
		/// <summary>
		/// IIC��������
		/// ��ʼ״̬��7�����ž��� 6�������ջ� 5��4����Ļ���� 3��������IIC���� 2��M52795IIC���� 1��2313(U303)���� 0��2313(U302)����
		/// </summary>
		BYTE  IICEnableByteData;
		/// <summary>
		/// ������״̬�ֽ�
		/// </summary>
		static const BYTE LineStateByte = 0x04;
		/// <summary>
		/// ����״̬����
		/// </summary>
		//byte LineStateByteData = 0x00;


// ����

		BOOL FanControl(BOOL bOn)
		{
			WriteBytes[1] = 0xb;
			WriteBytes[2] = bOn;
			return WriteIIC();
		}

		BOOL ReadSStop(void)
		{
			BYTE data = 0;
			if (IICReadMcu(0xd2,0x5,1,&data))
			{
				return data;
			}
			return 0;
		}

		BOOL RDSReady()
		{
			return ReadRdsReady() & (1<<17);
		}

		BOOL SetMixON(BOOL on)
		{
			ReadIIC(AMPStandbyByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte |= (1<<0);
			}
			else
			{
				tempbyte &= ~(1<<0);
			}
			WriteBytes[1] = AMPStandbyByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}

		/// <summary>
		/// ���POWER��״̬
		/// </summary>
		/// <returns>����״̬������ΪFALSE���ǰ���ΪTRUE</returns>
		BOOL GetPowerKeyState()
		{
			ReadIIC(POWERByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<5);
		}
		/// <summary>
		/// �ر��ܵ�Դ
		/// </summary>
		void PowerOff()
		{
			WriteBytes[1] = AMPStandbyByte;
			WriteBytes[2] = PowerOffData;
			WriteIIC();
		}
		/// <summary>
		/// ��9V��Դ
		/// </summary>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL NineVPower(BOOL on)
		{
			ReadIIC(POWERByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte |= NineVPowerOn;
			}
			else
			{
				tempbyte &= NineVPowerOff;
			}
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}
		/// <summary>
		/// ��DVD��Դ
		/// </summary>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL DVDPower(BOOL on)
		{
			ReadIIC(POWERByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte |= DVDPowenOn;
			}
			else
			{
				tempbyte &= DVDPowerOff;
			}
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}
		/// <summary>
		/// ��DVDC��Դ
		/// </summary>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL DVDCPower(BOOL on)
		{
			ReadIIC(POWERByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte |= (1<<5);
			}
			else
			{
				tempbyte &= ~(1<<5);
			}
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}
		BOOL DTVPower(BOOL on)
		{
			ReadIIC(POWERByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte |= (1<<4);
			}
			else
			{
				tempbyte &= ~(1<<4);
			}
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}
		/// <summary>
		/// ���״��Դ
		/// </summary>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL RADARPower(BOOL on)
		{
			ReadIIC(POWERByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte |= RADARPowerOn;
			}
			else
			{
				tempbyte &= RADARPowerOff;
			}
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}
		/// <summary>
		/// ��������Դ
		/// </summary>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL RadioPower(BOOL on)
		{
			ReadIIC(POWERByte);
			byte tempbyte = ReadBytes;
			RETAILMSG(1,(TEXT("RadioPower : tempbyte = 0x%x\r\n"),tempbyte));
			if (on)
			{
				tempbyte |= RADIOPowerOn;
			}
			else
			{
				tempbyte &= RADIOPowerOff;
			}
			RETAILMSG(1,(TEXT("RadioPower2 : tempbyte = 0x%x\r\n"),tempbyte));
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}
		/// <summary>
		/// ���Ŵ���
		/// </summary>
		/// <param name="on">1Ϊ����</param>
		/// <returns></returns>
		BOOL AMPStandby(BOOL on)
		{
			ReadIIC(AMPStandbyByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte &= AMPStadyBit;
			}
			else
			{
				tempbyte |= AMPNoStadyBit;
			}
			WriteBytes[1] = AMPStandbyByte;
			WriteBytes[2] = tempbyte;
			return WriteIIC();
		}
		/// <summary>
		/// �򿪹��ž���
		/// </summary>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL AMPMute(BOOL on)
		{
			bMute = on;
			ReadIIC(AMPStandbyByte);
			byte tempbyte = ReadBytes;
			if (on)
			{
				tempbyte &= AMPMuteBit;
				//f.Mute = true;

			}
			else
			{
				tempbyte |= AMPNoMuteBit;
				//f.Mute = false;
			}
			WriteBytes[1] = AMPStandbyByte;
			WriteBytes[2] = tempbyte;

			return WriteIIC();
		}
	
		/// <summary>
		/// ��Ļ���Ϸ�
		/// </summary>
		/// <returns></returns>
		BOOL ScreenUP()
		{
			IICEnableByteData &= ScreenContral1Off;
			IICEnableByteData |= ScreenContral2On;
			WriteBytes[1] = MechineByte;
			WriteBytes[2] = IICEnableByteData;
			return WriteIIC();
		}
		/// <summary>
		/// ��Ļ���·�
		/// </summary>
		/// <returns></returns>
		BOOL ScreenDown()
		{
			IICEnableByteData |= ScreenContral1On;
			IICEnableByteData &= ScreenContral2Off;
			WriteBytes[1] = MechineByte;
			WriteBytes[2] = IICEnableByteData;
			return WriteIIC();
		}
		/// <summary>
		/// ��Ļֹͣ�˶�
		/// </summary>
		/// <returns></returns>
		BOOL ScreenStop()
		{
			IICEnableByteData |= ScreenContral1On;
			IICEnableByteData |= ScreenContral2On;
			WriteBytes[1] = MechineByte;
			WriteBytes[2] = IICEnableByteData;
			return WriteIIC();
		}

		/// <summary>
		/// ��ȡ�ж�״̬��
		/// </summary>
		/// <returns></returns>
		BYTE GetLineStateByte()
		{
			ReadIIC(LineStateByte);
			return ReadBytes;
		}
		/// <summary>
		/// �����״̬
		/// </summary>
		/// <returns></returns>
		BOOL GetACCState()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<7);
		}
		/// <summary>
		/// ��ɲ״̬
		/// </summary>
		/// <returns></returns>
		BOOL GetBreakState()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<6);
		}
		/// <summary>
		/// �������
		/// </summary>
		/// <returns></returns>
		BOOL GetBACKState()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<5);
		}
		/// <summary>
		/// ��ð���״̬
		/// </summary>
		/// <returns></returns>
		BOOL GetPowerKeyPress()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<4);
		}
		/// <summary>
		/// ��Ļ����
		/// </summary>
		/// <returns></returns>
		BOOL ScreenDowned()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<3);
		}
		/// <summary>
		/// ��Ļ����
		/// </summary>
		/// <returns></returns>
		BOOL ScreenUped()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<2);
		}
		/// <summary>
		/// ��Ƶ����
		/// </summary>
		/// <returns></returns>
		BOOL VidioIn()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<1);
		}
		/// <summary>
		/// �������
		/// </summary>
		/// <returns></returns>
		BOOL Photosensitive()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<0);
		}

// GPIO����
		/// <summary>
		/// �����Ƿ��AV��ʾ
		/// </summary>
		/// <param name="on"></param>
		/// <returns>�Ƿ�ִ�гɹ�</returns>
		BOOL SetAVon(BOOL on)
		{
			return WriteGPIO(0x09, on);
		}
		/// <summary>
		/// �����Ƿ��������ʾ
		/// </summary>
		/// <param name="on">TRUE L->R,FALSE R->L</param>
		/// <returns>�Ƿ�ִ�гɹ�</returns>
		BOOL SetLeftShow(BOOL on)
		{
			return WriteGPIO(0x67, on);
		}
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="millisecond">����</param>
		/// <returns>�Ƿ�ִ�гɹ�</returns>
		BOOL Vibrate(int millisecond)
		{
			BOOL result = false;
			result |= WriteGPIO(0x04, true);
			Sleep(millisecond);
			result |= WriteGPIO(0x04, false);
			return result;
		}
		/// <summary>
		/// ������Ļ��ʾģʽ
		/// </summary>
		/// <param name="modo"></param>
		/// <returns></returns>
		BOOL ScreenMode(screenmodo modo)
		{
			BOOL result = false;
			BOOL m0 = false,m1 = false,m2 = false;
			switch (modo)   
			{
			case full:
				{
					m0 = false;
					m1 = false;
					m2 = false;
					break;
				}
			case center:
				{
					m0 = true;
					m1 = false;
					m2 = false;
					break;
				}
			case wide:
				{
					m0 = false;
					m1 = true;
					m2 = false;
					break;
				}
			case zoom1:
				{
					m0 = true;
					m1 = true;
					m2 = false;
					break;
				}
			case zoom2:
				{
					m0 = false;
					m1 = false;
					m2 = true;
					break;
				}
			case zoom3:
				{
					m0 = true;
					m1 = true;
					m2 = true;
					break;
				}
			case left:
				{
					m0 = true;
					m1 = false;
					m2 = true;
					break;
				}
			case right:
				{
					m0 = false;
					m1 = true;
					m2 = true;
					break;
				}
			default:
				{
					m0 = false;
					m1 = false;
					m2 = false;
					break;
				}
			}
			result |= WriteGPIO(0x64, m0);
			result |= WriteGPIO(0x65, m1);
			result |= WriteGPIO(0x66, m2);
			return result;
		}
		BYTE ReadIRCode()
		{
			BYTE data[5] = {0};
			for (int i=0;i<5;i++)
			{
				IICReadMcu(MCUAdd,0x9,1,&data[i]);
				//RETAILMSG(1,(TEXT("data[%d] = %d\r\n"),i, data[i]));
			}
			BYTE times[5] = {0};
			BYTE data2[5] = {0};
			for (int i=0;i<5;i++)
			{
				data2[i] = data[i];
				for (int j=0;j<=i;j++)
				{
					if (data[i] == data2[j])
					{
						times[j]++;
					}
				}
			}
			int max = 0;
			int ret = 0;
			for (int i=0;i<5;i++)
			{
				if (max < times[i])
				{
					max = times[i];
					ret = i;
				}
			}
			if (data[ret] == 0)
			{
				ASSERT(1);
				ret = 0;
			}
			return data[ret];
		}

		BYTE ReadCarStatus()
		{
			BYTE data=0;
			IICReadMcu(MCUAdd,0x3,1,&data);
			return data;
			// ������Ҫ�������İ취�ȽϺ�
			//BYTE data[5] = {0};
			//for (int i=0;i<5;i++)
			//{
			//	IICReadMcu(MCUAdd,0x3,1,&data[i]);
			//	Sleep(5);
			//	//RETAILMSG(1,(TEXT("data[%d] = %d\r\n"),i, data[i]));
			//}
			//BYTE times[5] = {0};
			//BYTE data2[5] = {0};
			//for (int i=0;i<5;i++)
			//{
			//	data2[i] = data[i];
			//	for (int j=0;j<=i;j++)
			//	{
			//		if (data[i] == data2[j])
			//		{
			//			times[j]++;
			//		}
			//	}
			//}
			//int max = 0;
			//int ret = 0;
			//for (int i=0;i<5;i++)
			//{
			//	if (max < times[i])
			//	{
			//		max = times[i];
			//		ret = i;
			//	}
			//}
			//if (data[ret] == 0)
			//{
			//	ASSERT(1);
			//	ret = 0;
			//}
			//return data[ret];
		}

		void Beep()
		{
			//WriteBytes[1] = 0x7;	// beep byte
			//WriteBytes[2] = 1;
			//WriteIIC();
			GXNotify::SendNotify("play_beep_sound", 0, 0);
		}

		BOOL BeepPower(BOOL bOn)
		{
			BYTE data = 0;
			IICReadMcu(MCUAdd,0x0,1,&data);
			if (bOn)
			{
				data |= (1<<3);
			}
			else
			{
				data &= ~(1<<3);
			}
			return IICWrite4(MCUAdd,0,data);
		}
		BOOL ExtAMPPower(BOOL bOn)
		{
			BYTE data = 0;
			IICReadMcu(MCUAdd,0x0,1,&data);
			if (bOn)
			{
				data |= (1<<6);
			}
			else
			{
				data &= ~(1<<6);
			}
			 return IICWrite4(MCUAdd,0,data);
		}

		BOOL RadioAntPower(BOOL bOn)
		{
			BYTE data = 0;
			IICReadMcu(MCUAdd,0x0,1,&data);
			if (bOn)
			{
				data |= (1<<2);
			}
			else
			{
				data &= ~(1<<2);
			}
			return IICWrite4(MCUAdd,0,data);
		}
		BOOL Reset()
		{
			WriteBytes[1] = 0x20;
			WriteBytes[2] = 0x55;
			return WriteIIC(); 
		}
		BOOL SwitchToCE()
		{
			AMPMute(1);
			Sleep(100);
			WriteBytes[1] = 0xf;
			WriteBytes[2] = 0x0;
			BOOL bRet = WriteIIC();
			Sleep(100);
			if (!sysConfig.bMute)
			{
				AMPMute(0);
			}
			return bRet;
		}
		BOOL SwitchToTV()
		{
			AMPMute(1);
			Sleep(100);
			WriteBytes[1] = 0xf;
			WriteBytes[2] = 0x1;
			BOOL bRet = WriteIIC();
			Sleep(100);
			if (!sysConfig.bMute)
			{
				AMPMute(0);
			}
			return bRet;
		}
// ˽�к���
		/// <summary>
		/// ��WriteBytesд��IIC
		/// </summary>
		/// <returns>�Ƿ�ɹ�д��</returns>
	private:
		BOOL WriteIIC()
		{
#ifdef UIONLY
			return 1;
#else
			if (!CreatecHardware::IsAuthOK())
			{
				return 1;
			}
			//RETAILMSG(1,(TEXT("WriteByte 1 = 0x%x, 2 = 0x%x, 3 = 0x%x\r\n"),WriteBytes[0],WriteBytes[1],WriteBytes[2]));
			return IICWrite4(WriteBytes,3);
#endif
		}
		/// <summary>
		/// ��ȡDVD������Ϣ
		/// </summary>
		/// <returns>�Ƿ�ɹ���ȡ</returns>
		BOOL ReadIIC(byte sub)
		{
			return IICReadMcu(0xd2,sub,1,&ReadBytes);
		}
		/// <summary>
		/// д��GPIO�˿�
		/// </summary>
		/// <param name="port">�˿ں�</param>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL WriteGPIO(byte port,BOOL on)
		{
		}
		/// <summary>
		/// ��ȡGPIO�˿�
		/// </summary>
		/// <param name="port"></param>
		/// <returns></returns>
		BOOL ReadGPIO(byte port)
		{
		}


};

