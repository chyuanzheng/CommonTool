#pragma once
#include "iic.h"


class Auth
{
	static BOOL bAuthOK;
public:
	static void Init(HWND hwnd)
	{
#if 0//#ifndef _DEBUG 
		if (!IICOpen())
		{
			bAuthOK = 0;
		}

		BYTE temp = 0;
		while((temp!=0x66) && (temp!=0x55))
		{
			temp = IICRead();
			if(temp == 0x66)
			{
				bAuthOK = 1;
			}
			else if(temp == 0x55)
			{
				bAuthOK = 0;
			}
			else
			{
				//printf("Authen value = %x, i = %d \n", temp, i);
				//i++;
			}
		} 
#endif
		IICOpen((int)hwnd);

	}
	static BOOL IsAuth()
	{
		return bAuthOK;
	}
};