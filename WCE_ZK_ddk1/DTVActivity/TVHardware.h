#pragma once

#include "Param.h"
#include "CHardware.h"
#include "Hardware.h"
#include "MCUCmd.h"

#pragma once

class DTVHardware
{
	CSerial serial;
	HWND hWnd;
public:
	void Init(HWND hWnd)
	{
		this->hWnd = hWnd;
		serial.Open(L"COM4:");
		serial.Setup(CSerial::EBaud19200);
		Hardware::DTVIrCustomer(0x80);
		DWORD dwThreadID = 0;
		CreateThread(NULL, 0, ReadThread, this, 0, &dwThreadID);
	}
	void WriteCMD(BYTE sub, BYTE cmd)
	{
		BYTE data[3] = {0, sub, cmd};
		serial.Write(data, 3);
	}
	void Key0_9(int iNum)
	{
		//这里添加数字电视数字按钮
		switch(iNum)
		{ 
		case 0:
			{
				Hardware::DTVIrCode(0x91);
				break;
			}
		case 1:
			{
				Hardware::DTVIrCode(0x94);
				break;
			}
		case 2:
			{
				Hardware::DTVIrCode(0x95);
				break;
			}
		case 3:
			{
				Hardware::DTVIrCode(0x80);
				break;
			}
		case 4:
			{
				Hardware::DTVIrCode(0x88);
				break;
			}
		case 5:
			{
				Hardware::DTVIrCode(0x89);
				break;
			}
		case 6:
			{
				Hardware::DTVIrCode(0x8A);
				break;
			}
		case 7:
			{
				Hardware::DTVIrCode(0x8C);
				break;
			}
		case 8:
			{
				Hardware::DTVIrCode(0x8D);
				break;
			}
		case 9:
			{
				Hardware::DTVIrCode(0x8E);
				break;
			}
		}
	}
	void KeyPlayPause(void)
	{
		Hardware::DTVIrCode(0x16);
	}
	void KeyMenu()
	{
		Hardware::DTVIrCode(0x02);
	}
	void KeyShowList()
	{
		Hardware::DTVIrCode(0x99);
	}
	void KeyStop()
	{
		Hardware::DTVIrCode(0x14);
	}
	void KeyFastForward()
	{
		Hardware::DTVIrCode(0x17);
	}
	void KeyFastBackward()
	{
		Hardware::DTVIrCode(0x15);
	}
	void KeyChannelDec(void)
	{
		//这里添加数字电视下
		Hardware::DTVIrCode(0x9E);
	}
	void KeyChannelAdd(void)
	{
		Hardware::DTVIrCode(0x9A);
	}
	void KeyVolAdd(void)
	{
		Hardware::DTVIrCode(0x98);
	}
	void KeyVolDec(void)
	{
		Hardware::DTVIrCode(0x9C);
	}
	void KeyOk(void)
	{
		Hardware::DTVIrCode(0x9D);
	}
	void KeyQuit(void)
	{
		Hardware::DTVIrCode(0xC2);
	}
	void KeyInfo(void)
	{
		Hardware::DTVIrCode(0x01);
	}

	static DWORD ReadThread(LPVOID lpParam)
	{
		COMSTAT comstat;				// COMSTAT struct 
		DWORD dwError;
		DTVHardware *p = (DTVHardware *)lpParam;
		if (p->serial.IsOpen())
		{
			RETAILMSG(0,(TEXT("COM4 is Opened\r\n")));
			p->serial.Purge();
		}
		else
		{
			RETAILMSG(0,(TEXT("COM4 is Closed\r\n")));
			return 0;
		}
		int msglen = 0;
		static BYTE msg[130];
		while (1)
		{
			p->serial.WaitEvent();
			if (p->serial.GetEventType()&EV_ERR)
			{
				::ClearCommError(p->serial.GetCommHandle(), &dwError, &comstat);
			}
			BYTE data[1024] = {0};
			DWORD len = 0;
			p->serial.Read(data,1024, &len);
			
			for (int i=0;i<len;i++)
			{
				msg[msglen] = data[i];
				if(msg[msglen] == '\r' || msg[msglen] == '\n')
				{
					msg[msglen] = 0;
					msglen = 0;
					GXNotify::SendNotifyAsync(p->hWnd, "warnning_text", (DWORD)msg, 0);
				}
				msglen++;
				if (msglen > 127)
				{
					msglen = 0;
				}
			}

		}
	}
};

