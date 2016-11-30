#include "stdafx.h"
#include "IICWrap.h"
#include "../i2c/iic.h"




U8 I2C1_WriteData(U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	U8 ret = IICWrite4(SlaveAddr, BufferP[0], Num-1, BufferP+1);
	//RETAILMSG(1, (TEXT("I2C1_WriteData ret = %d\r\n"), ret)); 
	
	//if (ret)
	//{
	//	RETAILMSG(1, (TEXT("I2CW S %02X "), SlaveAddr));
	//	for (int i=0;i<Num; i++)
	//	{
	//		RETAILMSG(1, (TEXT("%02X "), BufferP[i]));
	//	}
	//	RETAILMSG(1, (TEXT("P\r\n")));
	//}
	
	
	return ret;
}
U8 I2C1_ReadData(U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	U8 ret =  IICRead4(SlaveAddr, Num, BufferP);
	//RETAILMSG(1, (TEXT("I2C1_ReadData ret = %d\r\n"), ret));
	return ret;
}

void TimerDelayMs(int ms)
{
	Sleep(ms);
}