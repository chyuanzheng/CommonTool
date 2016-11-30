#pragma once

#include "stdAfx.h"
#include "iic.h"
class CM52795
{
		//52795视频开关使用手记
		//52795为四路音视频输入（左右声道），两路路音视频输出（左右声道）
		//地址：0x90（接低）0x92（接高）
		//子地址：控制视频1开关
		//数据：控制视频2开关，具体控制方法同视频1开关，即与子地址写法相同.
		//子地址具体用法：
		//一个字节8个位从左到右为

		//值XXXXXXXX
		//位76543210

		//其中7、6用于控制音频模式
		//7、6为00时表示静音
		//7、6为01时表示右声道输出
		//7、6为10时表示左声道输出
		//7、6为11时为左右声道输出

		//其中5、4为IO输出控制
		//5为0时为高、1时为低
		//4为0时为高、1时为低

		//其中3为放大增强控制
		//3为0时不放大
		//3为1时放大6dB

		//其中2不用

		//其中1、0用于控制输出视频
		//1、0为00时第一路视频输出
		//1、0为01时第二路视频输出
		//1、0为10时第三路视频输出
		//1、0为11时第四路视频输出

		//例子：
		//假如需要输出第一路不放大左右声道同时输出时2进制表示：
		//11110000
		//第三路放大左声道输出为：
		//10001010
		//第四路不放大静音输出为：
		//00110011 
		BYTE WriteBytes[3];
		/// <summary>
		/// 第十六脚为设置地址脚，如果接地则地址为0x90,如果接高地址为0x92.

public:
		/// </summary>
		enum  LEVEL { Low, High };
		/// <summary>
		/// 输入选择
		/// </summary>
		enum  InputSele { TUNER, VIDEO2, VIDEO3, VIDEO4 };
		/// <summary>
		/// 输出选择
		/// </summary>
		enum  OutputSele { V1OUT, V2OUT, ALL }; 
		/// <summary>
		/// 放大
		/// </summary>

		/// <summary>
		/// 音响模式
		/// </summary>
		enum  AudioMode { MUTE, RIGHT, LEFT, NORMAL };
		/// <summary>
		/// 输出I/O控制口
		/// </summary>
		enum  IOoutPort{ DC, DD, D4, D5 };
		InputSele curInput1;
		InputSele curInput2;
public:
		CM52795()
		{
			WriteBytes[0] = 0x92;             // 默认地址为0x48(七位地址)
			WriteBytes[1] = 0xF8;                  // 用于控制第一输出口，默认为第一输入做为输出，声音为不放大左右声道
			WriteBytes[2] = 0xF8;                  // 用于控制第二输出口，默认为第一输入做为输出，声音为不放大左右声道
			curInput1 = TUNER;
			curInput2 = TUNER;
		}



		/// <summary>
		/// 输出的输入选择
		/// </summary>
		/// <param name="pOutputSele"></param>
		/// <param name="pInputSelect">输入的视频接口</param>
		/// <returns>是否成功选择</returns>
		BOOL InputSelect(OutputSele pOutputSele,InputSele pInputSelect)
		{
#ifdef UIONLY
			return 1;
#else
			WriteBytes[1] = 0xF0;		// 不放大
			WriteBytes[2] = 0xF0;
			//WriteBytes[1] = 0xF8;		// 放大6DB
			//WriteBytes[2] = 0xF8;
			if (pOutputSele == V1OUT)
			{
				curInput1 = pInputSelect;
			}
			if (pOutputSele == V2OUT)
			{
				curInput2 = pInputSelect;
			}
			if (pOutputSele == ALL)
			{
				curInput1 = curInput2 = pInputSelect;
			}
			WriteBytes[1] |= curInput1;
			WriteBytes[2] |= curInput2;
			return WriteIIC();
#endif
		}

		BOOL AutoSelect()
		{
			WriteBytes[1] = 0xF0;		// 不放大
			WriteBytes[2] = 0xF0;
			//WriteBytes[1] = 0xF8;		// 放大6DB
			//WriteBytes[2] = 0xF8;
			curInput2 = curInput1;
			WriteBytes[1] |= curInput1;
			WriteBytes[2] |= curInput2;
			return WriteIIC();
		}

		/// <summary>
		/// 放大选择
		/// </summary>
		/// <param name="pOutputSele">输出的视频接口</param>
		/// <param name="pGain">是否放大</param>
		/// <returns>是否控制成功</returns>
		BOOL AmpGain(OutputSele pOutputSele, LEVEL pGain)
		{
#ifdef UIONLY
			return 1;
#else
			byte ZeroBit = 251;// OxFB;        // &11111011,倒数第三位清零。用于清除所需要控制的位
			byte CONTROL = 0x00;        // 用于控制的操作
			if (pGain == High)
			{
				CONTROL = 0x04; //对应控制位为1
			}
			else
			{
				CONTROL = 0x00; //对应控制位为0
			}
			Outputselect(pOutputSele, ZeroBit, CONTROL);
			return WriteIIC();
#endif
		}
		/// <summary>
		/// 声音模式选择
		/// </summary>
		/// <param name="pOutputSele">输出的视频接口</param>
		/// <param name="pAudioMode">声音模式</param>
		/// <returns>是否成功选择</returns>
		BOOL AudioModeSelect(OutputSele pOutputSele, AudioMode pAudioMode)
		{
#ifdef UIONLY
			return 1;
#else
			byte ZeroBit = 63;// Ox3f;        // &00111111,最前两位清零。用于清除所需要控制的位
			byte CONTROL = 0x00;        // 用于控制的操作
			switch (pAudioMode)
			{
			case MUTE:
				{
					CONTROL = 0x00; //7、6为00时表示静音
					break;
				}
			case RIGHT:
				{
					CONTROL = 0x40; //7、6为01时表示右声道输出
					break;
				}
			case LEFT:
				{
					CONTROL = 0x80; //7、6为10时表示左声道输出
					break;
				}
			case NORMAL:
				{
					CONTROL = 0xC0; //7、6为11时为左右声道输出
					break;
				}
			}
			Outputselect(pOutputSele, ZeroBit, CONTROL);
			return WriteIIC();
#endif
		}

		/// <summary>
		/// IO口控制
		/// </summary>
		/// <param name="pIOoutPort">IO口选择</param>
		/// <param name="pIOHighLow">IO口设置</param>
		/// <returns>是否成功控制</returns>
		BOOL IOoutControl(IOoutPort pIOoutPort,LEVEL pIOHighLow)
		{
#ifdef UIONLY
			return 1;
#else
			byte ZeroBit4 = 239;// OxEF;        // &11101111,最后两位清零。用于清除所需要控制的位
			byte ZeroBit5 = 223;// OxDF;        // &11011111,最后两位清零。用于清除所需要控制的位
			switch (pIOoutPort)
			{
			case DC:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[2] &= ZeroBit4;
						WriteBytes[2] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[2] &= ZeroBit4;
						WriteBytes[2] |= 0x10;
					}
					break;
				}
			case DD:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[2] &= ZeroBit5;
						WriteBytes[2] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[2] &= ZeroBit5;
						WriteBytes[2] |= 0x20;
					}

					break;
				}
			case D4:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[1] &= ZeroBit4;
						WriteBytes[1] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[1] &= ZeroBit4;
						WriteBytes[1] |= 0x10;
					}

					break;
				}
			case D5:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[1] &= ZeroBit5;
						WriteBytes[1] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[1] &= ZeroBit5;
						WriteBytes[1] |= 0x20;
					}

					break;
				}
			}
			return WriteIIC();
#endif
		}
		/// <summary>
		/// 输出选择
		/// </summary>
		/// <param name="pOutputSele">输出选择</param>
		/// <param name="ZeroBit">置零位</param>
		/// <param name="CONTROL">控制位</param>
	private:
		void Outputselect(OutputSele pOutputSele, byte ZeroBit, byte CONTROL)
		{
#ifdef UIONLY
			return;
#else
			WriteBytes[1] = 0xF0;		// 不放大
			WriteBytes[2] = 0xF0;
			//WriteBytes[1] = 0xF8;		// 放大6DB
			//WriteBytes[2] = 0xF8;
			switch (pOutputSele)
			{
			case V1OUT:
				{
					WriteBytes[1] &= ZeroBit;
					WriteBytes[1] |= CONTROL;
					break;
				}
			case V2OUT:
				{
					WriteBytes[2] &= ZeroBit;
					WriteBytes[2] |= CONTROL;
					break;
				}
			case ALL:
				{
					WriteBytes[1] &= ZeroBit;
					WriteBytes[1] |= CONTROL;
					WriteBytes[2] &= ZeroBit;
					WriteBytes[2] |= CONTROL;
					break;
				}
			default:
				{
					WriteBytes[1] &= ZeroBit;
					WriteBytes[1] |= CONTROL;
					WriteBytes[2] &= ZeroBit;
					WriteBytes[2] |= CONTROL;
					break;
				}
			}
#endif
		}
		/// <summary>
		/// I2C写入
		/// </summary>
		BOOL WriteIIC()
		{
#ifdef UIONLY
			return 1;
#else
			return IICWrite4(WriteBytes,3);
#endif
		}


};