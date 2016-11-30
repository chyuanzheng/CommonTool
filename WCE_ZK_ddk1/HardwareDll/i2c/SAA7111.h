#pragma once

#include "stdAfx.h"
#include "iic.h"


class SAA7111
{
	static const BYTE ChipAddr = 0x4A;
	static const BYTE ChipAddr_9910 = 0x8A;
public:
	enum DEVICETYPE
	{
		CHIP_SAA7111,
		CHIP_TW9910
	} eDeviceType;
	enum CHANNEL
	{
		CH_CVBS,
		CH_YC,
		CH_CAMERA
	}eCh;
public:
	BOOL WriteTW9910(BYTE subaddr, BYTE data)
	{
		return IICWrite(ChipAddr_9910, subaddr, data);
	}
	BOOL Init(void)
	{
#ifdef UIONLY
		return 1;
#else
		BYTE data = 0;
		eDeviceType = CHIP_SAA7111;
		if (IICRead(ChipAddr_9910, 0x0, 1, &data))
		{
			if (data == 0x58 || data == 0x59)
			{
				eDeviceType = CHIP_TW9910;
			}
		}
		RETAILMSG(1,(TEXT("tw9910 data = 0x%x\r\n"), data));
		if (eDeviceType == CHIP_SAA7111)
		{
			BYTE reg_table[96] = {0x11,0x08,0xC3,0x33,0x00,0x00,0xE9,0x0D,0x98,0x01,0x75,0x4d,0x4e,0x00,0x01,0x42,
				0x00,0x0C,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA0,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
				0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x54,0x07,0x83,0x00,0x00,0x00,0x00,};
			return IICWrite(ChipAddr,0,reg_table,96);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			// pal cvbs
			BYTE reg_table_9910[][2] = {
				0x00, 0x59,
				0x01, 0x93,
				0x02, 0x44,
				0x03, 0x8A,
				0x04, 0x00,
				0x05, 0x01,
				0x06, 0x00,
				0x07, 0x12,
				0x08, 0x17,
				0x09, 0x20,
				0x0A, 0x0B,
				0x0B, 0xD0,
				0x0C, 0xCC,
				0x0D, 0x00,
				0x0E, 0x11,
				0x0F, 0x00,
				0x10, 0xD6,
				0x11, 0x6A,
				0x12, 0x41,
				0x13, 0x80,
				0x14, 0x80,
				0x15, 0x00,
				0x16, 0x00,
				0x17, 0x30,
				0x18, 0x44,
				0x19, 0x57,
				0x1A, 0x0F,
				0x1B, 0x00,
				0x1C, 0x27,
				0x1D, 0x7F,
				0x1E, 0x08,
				0x1F, 0x00,
				0x20, 0x50,
				0x21, 0x42,
				0x22, 0xF0,
				0x23, 0xD8,
				0x24, 0xBC,
				0x25, 0xB8,
				0x26, 0x44,
				0x27, 0x2A,
				0x28, 0x00,
				0x29, 0x03,
				0x2A, 0x78,
				0x2B, 0x44,
				0x2C, 0x30,
				0x2D, 0x07,
				0x2E, 0xA5,
				0x2F, 0xE0,
				0x30, 0xD4,
				0x31, 0x80,
				0x32, 0x00,
				0x33, 0x05,
				0x34, 0x1A,
				0x35, 0x00,
				0x36, 0x00,
				0x37, 0x00,
				0x38, 0x00,
				0x39, 0x00,
				0x3A, 0x00,
				0x3B, 0x00,
				0x3C, 0x00,
				0x3D, 0x00,
				0x3E, 0x00,
				0x3F, 0x00,
				0x40, 0x00,
				0x41, 0x00,
				0x42, 0x00,
				0x43, 0x00,
				0x44, 0x00,
				0x45, 0x00,
				0x46, 0x00,
				0x47, 0x00,
				0x48, 0x00,
				0x49, 0x00,
				0x4A, 0x00,
				0x4B, 0x00,
				0x4C, 0x0D,
				0x4D, 0x40,
				0x4E, 0x00,
				0x4F, 0x00,
				0x50, 0xA0,
				0x51, 0x22,
				0x52, 0x31,
				0x53, 0x80,
				0x54, 0x00,
				0x55, 0x00,
				0x56, 0x00,
				0x57, 0x00,
				0x58, 0x00,
				0x59, 0x00,
				0x5A, 0x00,
				0x5B, 0x00,
				0x5C, 0x00,
				0x5D, 0x00,
				0x5E, 0x00,
				0x5F, 0x00,
				0x60, 0x00,
				0x61, 0x00,
				0x62, 0x00,
				0x63, 0x00,
				0x64, 0x00,
				0x65, 0x00,
				0x66, 0x00,
				0x67, 0x00,
				0x68, 0x00,
				0x69, 0x00,
				0x6A, 0x00,
				0x6B, 0x26,
				0x6C, 0x36,
				0x6D, 0xF0,
				0x6E, 0x28,
				0x6F, 0x24,
			};
			for (int i=0;i<sizeof(reg_table_9910)/2;i++)
			{
				IICWrite(ChipAddr_9910, reg_table_9910[i][0], reg_table_9910[i][1]);
			}
			return 1;
		}
		return 0;

#endif
	}
	BOOL ColorStandardSelect(int colorstandard)
	{
		colorstandard++;
		if (eDeviceType == CHIP_SAA7111)
		{
			if (colorstandard == 3)
			{
				return IICWrite(ChipAddr,0x0e,0x51);
			}
			else
			{
				return IICWrite(ChipAddr,0x0e,0x01);
			}
		}
		if (eDeviceType == CHIP_TW9910)
		{
			if (colorstandard == 1)
			{
				// ntsc
				WriteTW9910(0x7, 0x02);
				WriteTW9910(0x8, 0x13);
				WriteTW9910(0x9, 0xF2);
				WriteTW9910(0xA, 0x0C);
			}
			else
			{
				// pal
				WriteTW9910(0x7, 0x12);
				WriteTW9910(0x8, 0x18);
				WriteTW9910(0x9, 0x20);
				WriteTW9910(0xA, 0x06);
			}
		}
		return 0;
	}
	BOOL SelectYC()
	{
		// 如果在倒车状态下等待
		WaitRearCamera();
		eCh = CH_YC;
		if (eDeviceType == CHIP_SAA7111)
		{
			IICWrite(ChipAddr, 2, 0xC8);
			return IICWrite(ChipAddr, 9, 0x81);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			WriteTW9910(0x7, 0x02);
			WriteTW9910(0x8, 0x13);
			WriteTW9910(0x9, 0xF2);
			WriteTW9910(0xA, 0x0C);
			IICWrite(ChipAddr_9910, 0x02, 0x50);
			BYTE ch = 0;
			IICRead(ChipAddr_9910, 0x2, 1, &ch);
			if (ch != 0x44)
			{
				IICWrite(ChipAddr_9910, 0x6, 0x80);
			}
		}
		return 0;
	}
	void WaitRearCamera()
	{
		//if (ReadMachine() == SPECAIL_MACHINE)
		//{
		//	if (eDeviceType == CHIP_TW9910)
		//	{
		//		while (1)
		//		{
		//			BYTE data;
		//			IICRead(ChipAddr_9910, 0x2, 1, &data);
		//			if (data != 0x44)
		//			{
		//				break;
		//			}
		//			Sleep(50);
		//		}
		//	}
		//}
	}
	BOOL SelectCVBS()
	{
		// 如果在倒车状态下等待
		WaitRearCamera();
		eCh = CH_CVBS;
		if (eDeviceType == CHIP_SAA7111)
		{
			IICWrite(ChipAddr, 2, 0xC3);
			IICWrite(ChipAddr, 9, 0x01);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			IICWrite(ChipAddr_9910, 0x02, 0x48);
			BYTE ch = 0;
			IICRead(ChipAddr_9910, 0x2, 1, &ch);
			if (ch != 0x44)
			{
				IICWrite(ChipAddr_9910, 0x6, 0x80);
			}
			
		}
		return 0;
	}
	BOOL SelectCamera()
	{
		eCh = CH_CAMERA;
		if (eDeviceType == CHIP_SAA7111)
		{
			IICWrite(ChipAddr, 2, 0xC3);
			return IICWrite(ChipAddr, 9, 0x01);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			IICWrite(ChipAddr_9910, 0x02, 0x44);
			return IICWrite(ChipAddr_9910, 0x6, 0x80);;
		}
		return 0;
	}
	CHANNEL GetVideoChannel()
	{
		return eCh;
	}
	void SetSaturation(BYTE sa)
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			IICWrite(ChipAddr, 0xC, 0x4E+sa*3);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			WriteTW9910(0x13, 0x80+sa*3);
			WriteTW9910(0x14, 0x80+sa*3);
		}
	}
	BOOL SelectVideoChannel(CHANNEL ch)
	{
		switch(ch)
		{
		case CH_CAMERA:
			{
				return SelectCamera();
			}
		case CH_YC:
			{
				return SelectYC();
			}
		case CH_CVBS:
			{
				return SelectCVBS();
			}
		}
		return 0;
	}
	int SourceCheckQuick()
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			BYTE status = 0;
			for (int i=0;i<20;i++)
			{
				IICRead(ChipAddr, 0x1F, 1, &status);
				if ((status & (1<<6)) == 0)
				{
					if (status & (1<<5))
					{
						return 1;
					}
					return 2;
				}
				Sleep(1);
			}
			return 0;
		}
		if (eDeviceType == CHIP_TW9910)
		{
			BYTE status = 0;
			for (int i=0;i<20;i++)
			{
				IICRead(ChipAddr_9910, 0x1, 1, &status);
				if (status & (1<<6))
				{
					if (status & 0x1)
					{
						// pal
						WriteTW9910(0x7, 0x12);
						WriteTW9910(0x8, 0x18);
						WriteTW9910(0x9, 0x20);
						WriteTW9910(0xA, 0x06);
						return 2;
					}
					else
					{
						// ntsc
						WriteTW9910(0x7, 0x02);
						WriteTW9910(0x8, 0x13);
						WriteTW9910(0x9, 0xF2);
						WriteTW9910(0xA, 0x0C);
						return 1;
					}
				}
				Sleep(1);
			}
			return 0;
		}
		return 0;
	}
	void SetNTSC()
	{
		if (eDeviceType == CHIP_TW9910)
		{
			// ntsc
			WriteTW9910(0x7, 0x02);
			WriteTW9910(0x8, 0x13);
			WriteTW9910(0x9, 0xF2);
			WriteTW9910(0xA, 0x0C);
		}
	}

	BOOL IsBackCamera()
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			BYTE data=0;
			IICRead(ChipAddr, 2, 1, &data);
			if (data == 0xC1)
			{
				return 1;
			}
		}
		if (eDeviceType == CHIP_TW9910)
		{
			BYTE data = 0;
			IICRead(ChipAddr_9910, 0x2, 1, &data);
			if (data == 0x44)
			{
				return 1;
			}
		}
		return 0;
	}
	void SetPAL()
	{
		if (eDeviceType == CHIP_TW9910)
		{
			// pal
			WriteTW9910(0x7, 0x12);
			WriteTW9910(0x8, 0x18);
			WriteTW9910(0x9, 0x20);
			WriteTW9910(0xA, 0x06);

		}
	}
	int SourceCheckSlow()
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			BYTE status = 0;
			for (int i=0;i<20;i++)
			{
				IICRead(ChipAddr, 0x1F, 1, &status);
				if ((status & (1<<0)))
				{
					if (status & (1<<5))
					{
						return 1;
					}
					return 2;
				}
				Sleep(10);
			}
			return 0;
		}
		if (eDeviceType == CHIP_TW9910)
		{
			BYTE status = 0;
			for (int i=0;i<20;i++)
			{
				IICRead(ChipAddr_9910, 0x1, 1, &status);
				if ((status & 0x70)>0x50 || (status & (1<<3)))
				{
					if (status & 0x1)
					{
						// pal
						WriteTW9910(0x7, 0x12);
						WriteTW9910(0x8, 0x18);
						WriteTW9910(0x9, 0x20);
						WriteTW9910(0xA, 0x06);
						return 2;
					}
					else
					{
						// ntsc
						WriteTW9910(0x7, 0x02);
						WriteTW9910(0x8, 0x13);
						WriteTW9910(0x9, 0xF2);
						WriteTW9910(0xA, 0x0C);
						return 1;
					}
				}
				Sleep(10);
			}
			return 0;
		}
		return 0;
	}
	int	SourceCheck()	// 0 无视频 1 NTSC 2 PAL
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			BYTE status = 0;
			for (int i=0;i<20;i++)
			{
				IICRead(ChipAddr, 0x1F, 1, &status);
				if ((status & (1<<6)) == 0)
				{
					if (status & (1<<5))
					{
						return 1;
					}
					return 2;
				}
				Sleep(10);
			}
			return 0;
		}
		if (eDeviceType == CHIP_TW9910)
		{
			BYTE status = 0;
			for (int i=0;i<20;i++)
			{
				IICRead(ChipAddr_9910, 0x1, 1, &status);
				if ((status & 0x70)>0x50 || (status & (1<<3)))
				{
					if (status & 0x1)
					{
						// pal
						WriteTW9910(0x7, 0x12);
						WriteTW9910(0x8, 0x18);
						WriteTW9910(0x9, 0x20);
						WriteTW9910(0xA, 0x06);
						return 2;
					}
					else
					{
						// ntsc
						WriteTW9910(0x7, 0x02);
						WriteTW9910(0x8, 0x13);
						WriteTW9910(0x9, 0xF2);
						WriteTW9910(0xA, 0x0C);
						return 1;
					}
				}
				Sleep(10);
			}
			return 0;
		}
		return 0;
	}
	void BrightnessSet(char b)
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			b+=3;
			IICWrite(ChipAddr, 0xA, 0x75+b*3);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			WriteTW9910(0x10, 0xD6+b*3);
		}
	}
	void ContrastSet(char c)
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			c-=8;
			IICWrite(ChipAddr, 0xB, 0x4D+c*3);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			WriteTW9910(0x11, 0x6A+c*3);
		}
	}
	void HueSet(char h)
	{
		if (eDeviceType == CHIP_SAA7111)
		{
			IICWrite(ChipAddr, 0xC, 0x4E+h*3);
		}
		if (eDeviceType == CHIP_TW9910)
		{
			WriteTW9910(0x15, h);
		}
	}
};