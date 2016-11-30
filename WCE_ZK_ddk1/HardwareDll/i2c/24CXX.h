#pragma once
#include "iic.h"


// A0 A1 A2 接地
// 从地址 1000xxx(R/W);	xxx子地址的高3位
class CHIP24CXX
{
public:
	BOOL Read(WORD subaddr, int iCount, BYTE *databuf)
	{
		return IICRead3(0xA0 | ((subaddr>>7) & 0xE), (subaddr & 0xFF), iCount, databuf);
	}
	BOOL Write(WORD subaddr, int iCount, BYTE *databuf)
	{
		for (int i=0;i<iCount;i++)
		{
			Write(subaddr++, *databuf++);
			//Sleep(1);
		}
		return 1;
	}
	BOOL Write(WORD subaddr, BYTE data)
	{
		return IICWrite3(0xA0 | ((subaddr>>7) & 0xE), (subaddr & 0xFF), data);
	}
protected:
private:
} chip_24cxx;