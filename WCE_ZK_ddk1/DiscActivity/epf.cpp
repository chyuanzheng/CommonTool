#include "stdafx.h"
#include "i2c/iic.h"
BOOL epf_send(BYTE *buf, int num)
{
	BYTE sbuf[17] = {0};
	BYTE rbuf[17] = {0};
	for (int i=0;i<17;i++)
	{
		sbuf[i] = buf[i];
	}
	for (int i=0;i<15;i++)
	{
		sbuf[15] ^= sbuf[i];
	}
	for(int i=0;i<17;i++)
	{
		RETAILMSG(0, (TEXT("<%02X> "), sbuf[i]));
	}
	RETAILMSG(0, (TEXT("\r\n")));
	return EpfWrite(sbuf, rbuf, num);
}