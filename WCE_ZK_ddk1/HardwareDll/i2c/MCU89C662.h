#pragma once

#include "stdAfx.h"
#include "iic.h"
#include "GXNotify.h"
#include "../LoadConfig.h"
#include "INC/Param.h"

/// <summary>
	/// MCU控制以及GPIO控制
	/// </summary>
class MCU89C662
{
		/// <summary>
		/// 读数组
		/// </summary>
		BYTE ReadBytes;
		/// <summary>
		/// 写数组
		/// </summary>
		BYTE WriteBytes[3];
		/// <summary>
		/// 屏幕显示模式
		/// </summary>
		enum screenmodo
		{
			full,       // 全屏
			center,     // 中心
			wide,       // 宽屏
			zoom1,      // 放大1
			zoom2,      // 放大2
			zoom3,      // 放大3
			left,       // 靠左显示
			right       // 靠右显示
		};
public:
		BOOL bMute;

public:
		/// <summary>
		/// 构造函数
		/// </summary>
		MCU89C662()
		{
			WriteBytes[0] = MCUAdd;
			IICEnableByteData = 0x80;
		}

		/// <summary>
		/// 初始化MCU
		/// </summary>
		void InitMcu()
		{
			InitPowerByte();
			InitAMPStandbyByte();
		}
		/// <summary>
		/// 初始化功放待机字节
		/// </summary>
		BOOL InitAMPStandbyByte()
		{
			WriteBytes[1] = AMPStandbyByte;
			WriteBytes[2] = AMPStandbyByteData;
			return WriteIIC();
		}
		/// <summary>
		/// 初始化电源状态字节
		/// </summary>
		BOOL InitPowerByte()
		{
			WriteBytes[1] = POWERByte;
			WriteBytes[2] = POWERByteData;
			return WriteIIC();
		}
		/// <summary>
		/// 单片机地址（8位）
		/// </summary>
		static const BYTE MCUAdd = 0xD2;

		/// <summary>
		/// 9V电源工作
		/// </summary>
		static const BYTE NineVPowerOn = 1<<4;
		/// <summary>
		/// 9V电源停止
		/// </summary>
		static const BYTE NineVPowerOff = ~(1<<4);
		/// <summary>
		/// DVD上电
		/// </summary>
		static const BYTE DVDPowenOn = 1<<5;
		/// <summary>
		/// DVD下电
		/// </summary>
		static const BYTE DVDPowerOff = ~(1<<5);
		/// <summary>
		/// 多碟机上电
		/// </summary>
		static const BYTE DVDCPowerOn = 0;
		/// <summary>
		/// 多碟机下电
		/// </summary>
		static const BYTE DVDCPowerOff = 0xff;
		/// <summary>
		/// 雷达上电
		/// </summary>
		static const BYTE RADARPowerOn = 0x00;
		/// <summary>
		/// 雷达断电
		/// </summary>
		static const BYTE RADARPowerOff = 0xff;
		/// <summary>
		/// 收音上电
		/// </summary>
		static const BYTE RADIOPowerOn = 1<<4;
		/// <summary>
		/// 收音断电
		/// </summary>
		static const BYTE RADIOPowerOff = ~(1<<4);
		/// <summary>
		/// 功放待机
		/// </summary>
		static const BYTE AMPStadyBit = ~(1<<1);
		/// <summary>
		/// 功放取消待机
		/// </summary>
		static const BYTE AMPNoStadyBit = 1<<1;
		/// <summary>
		/// 功放静音
		/// </summary>
		static const BYTE AMPMuteBit = ~(1<<2);
		/// <summary>
		/// 功放非静音
		/// </summary>
		static const BYTE AMPNoMuteBit = (1<<2);
		/// <summary>
		/// 天线弹出
		/// </summary>
		static const BYTE RADIOANNTOut = 0x40;
		/// <summary>
		/// 天线收回
		/// </summary>
		static const BYTE RADIOANNTIn = 0xbf;
		/// <summary>
		/// 屏幕翻动控制位2开
		/// </summary>
		static const BYTE ScreenContral2On = 1<<1;
		/// <summary>
		/// 屏幕翻动控制位2关
		/// </summary>
		static const BYTE ScreenContral2Off = ~(1<<1);
		/// <summary>
		/// 屏幕翻动控制位1开
		/// </summary>
		static const BYTE ScreenContral1On = 1<<0;
		/// <summary>
		/// 屏幕翻动控制位1关
		/// </summary>
		static const BYTE ScreenContral1Off = ~(1<<0);
		/// <summary>
		/// 收音机IIC允许
		/// </summary>
		static const BYTE RadioIICEnable = 0xf7;
		/// <summary>
		/// 收音机IIC不允许
		/// </summary>
		static const BYTE RadioIICDisable = 0x08;
		/// <summary>
		/// 52795IIC允许
		/// </summary>
		static const BYTE M52795Enable = 0xFB;
		/// <summary>
		/// 52795IIC不允许
		/// </summary>
		static const BYTE M52795Disable = 0x04;
		/// <summary>
		/// PT2313_1IIC允许
		/// </summary>
		static const BYTE PT2313_1Enable = 0xfd;
		/// <summary>
		/// PT2313_1IIC不允许
		/// </summary>
		static const BYTE PT2313_1Disable = 0x02;
		/// <summary>
		/// PT2313_2IIC允许
		/// </summary>
		static const BYTE PT2313_2Enable = 0xfe;
		/// <summary>
		/// PT2313_2IIC不允许
		/// </summary>
		static const BYTE PT2313_2Disable = 0x01;


//状态字节常量地址及状态字节初始状态址
		/// <summary>
		/// 电源状态字节
		/// </summary>
		static const BYTE POWERByte = 0x00;
		/// <summary>
		/// 电源状态内容
		/// 初始状态：4，9V电源打开 3，DVD机芯电源关闭 2，换碟机电源打开 1，倒车雷达电源关闭 0，收音机电源关闭
		/// </summary>
		static const BYTE  POWERByteData = 1<<4;
		/// <summary>
		/// 功放待机字节
		/// </summary>
		static const BYTE AMPStandbyByte = 0x01;
		/// <summary>
		/// 功放待机内容
		/// 初始状态：4，功放待机1是工作，0是待机
		/// </summary>
		static const BYTE  AMPStandbyByteData = 0x00;
		/// <summary>
		/// 待机
		/// </summary>
		static const BYTE  PowerOffData = 0x40;
		/// <summary>
		/// 机械控制字节
		/// </summary>
		static const BYTE MechineByte = 0x02;
		/// <summary>
		/// IIC允许内容
		/// 初始状态：7，功放静音 6，天线收回 5，4，屏幕不动 3，收音机IIC允许 2，M52795IIC允许 1，2313(U303)允许 0，2313(U302)允许
		/// </summary>
		BYTE  IICEnableByteData;
		/// <summary>
		/// 接入线状态字节
		/// </summary>
		static const BYTE LineStateByte = 0x04;
		/// <summary>
		/// 接线状态内容
		/// </summary>
		//byte LineStateByteData = 0x00;


// 属性

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
		/// 获得POWER键状态
		/// </summary>
		/// <returns>键的状态，按下为FALSE，非按下为TRUE</returns>
		BOOL GetPowerKeyState()
		{
			ReadIIC(POWERByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<5);
		}
		/// <summary>
		/// 关闭总电源
		/// </summary>
		void PowerOff()
		{
			WriteBytes[1] = AMPStandbyByte;
			WriteBytes[2] = PowerOffData;
			WriteIIC();
		}
		/// <summary>
		/// 打开9V电源
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
		/// 打开DVD电源
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
		/// 打开DVDC电源
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
		/// 打开雷达电源
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
		/// 打开收音电源
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
		/// 功放待机
		/// </summary>
		/// <param name="on">1为待机</param>
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
		/// 打开功放静音
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
		/// 屏幕向上翻
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
		/// 屏幕向下翻
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
		/// 屏幕停止运动
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
		/// 获取中断状态字
		/// </summary>
		/// <returns></returns>
		BYTE GetLineStateByte()
		{
			ReadIIC(LineStateByte);
			return ReadBytes;
		}
		/// <summary>
		/// 点火线状态
		/// </summary>
		/// <returns></returns>
		BOOL GetACCState()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<7);
		}
		/// <summary>
		/// 手刹状态
		/// </summary>
		/// <returns></returns>
		BOOL GetBreakState()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<6);
		}
		/// <summary>
		/// 倒车检测
		/// </summary>
		/// <returns></returns>
		BOOL GetBACKState()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<5);
		}
		/// <summary>
		/// 获得按键状态
		/// </summary>
		/// <returns></returns>
		BOOL GetPowerKeyPress()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<4);
		}
		/// <summary>
		/// 屏幕到底
		/// </summary>
		/// <returns></returns>
		BOOL ScreenDowned()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<3);
		}
		/// <summary>
		/// 屏幕到顶
		/// </summary>
		/// <returns></returns>
		BOOL ScreenUped()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<2);
		}
		/// <summary>
		/// 视频输入
		/// </summary>
		/// <returns></returns>
		BOOL VidioIn()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<1);
		}
		/// <summary>
		/// 光敏检测
		/// </summary>
		/// <returns></returns>
		BOOL Photosensitive()
		{
			ReadIIC(LineStateByte);
			BYTE tempbyte = ReadBytes;
			return tempbyte | (1<<0);
		}

// GPIO控制
		/// <summary>
		/// 设置是否打开AV显示
		/// </summary>
		/// <param name="on"></param>
		/// <returns>是否执行成功</returns>
		BOOL SetAVon(BOOL on)
		{
			return WriteGPIO(0x09, on);
		}
		/// <summary>
		/// 设置是否从左到右显示
		/// </summary>
		/// <param name="on">TRUE L->R,FALSE R->L</param>
		/// <returns>是否执行成功</returns>
		BOOL SetLeftShow(BOOL on)
		{
			return WriteGPIO(0x67, on);
		}
		/// <summary>
		/// 振动器振动
		/// </summary>
		/// <param name="millisecond">毫秒</param>
		/// <returns>是否执行成功</returns>
		BOOL Vibrate(int millisecond)
		{
			BOOL result = false;
			result |= WriteGPIO(0x04, true);
			Sleep(millisecond);
			result |= WriteGPIO(0x04, false);
			return result;
		}
		/// <summary>
		/// 设置屏幕显示模式
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
			// 这里需要想其他的办法比较好
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
// 私有函数
		/// <summary>
		/// 将WriteBytes写入IIC
		/// </summary>
		/// <returns>是否成功写入</returns>
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
		/// 读取DVD所有信息
		/// </summary>
		/// <returns>是否成功读取</returns>
		BOOL ReadIIC(byte sub)
		{
			return IICReadMcu(0xd2,sub,1,&ReadBytes);
		}
		/// <summary>
		/// 写入GPIO端口
		/// </summary>
		/// <param name="port">端口号</param>
		/// <param name="on"></param>
		/// <returns></returns>
		BOOL WriteGPIO(byte port,BOOL on)
		{
		}
		/// <summary>
		/// 读取GPIO端口
		/// </summary>
		/// <param name="port"></param>
		/// <returns></returns>
		BOOL ReadGPIO(byte port)
		{
		}


};

