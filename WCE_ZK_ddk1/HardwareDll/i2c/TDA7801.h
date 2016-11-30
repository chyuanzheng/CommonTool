#pragma once
#include "iic.h"


// A0 A1 A2 接地
// 从地址 1000xxx(R/W);	xxx子地址的高3位
class TDA7801
{
	const static BYTE ADDR = 0xD8;
	BYTE IB1,IB2,IB3,IB4,IB5;
public:
	void Init()
	{
		IB1 = IB2 = IB3 = IB4= IB5 = 0;
		IICWrite4(ADDR, 0, 0);
		IICWrite4(ADDR, 1, 0);
		IICWrite4(ADDR, 2, 0);
		IICWrite4(ADDR, 3, 0);
		IICWrite4(ADDR, 4, 0);
	}
	void PowerOn()
	{
		IB1 |= 0x80;
		BOOL ret = IICWrite4(ADDR, 1, IB1);
		RETAILMSG(COUT_MSG, (TEXT(" Power on = %d\r\n"), ret));
	}
	void PowerOff()
	{
		IB1 &= ~0x80;
		IICWrite4(ADDR, 1, 0);
	}
	void Mute()
	{
		IB1 &= ~(0x3<<2);
		IICWrite4(ADDR, 1, IB1);
		
	}
	void UnMute()
	{
		IB1 |= 0x3<<2;
		IICWrite4(ADDR, 1, IB1);
	}

};