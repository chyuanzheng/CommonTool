#pragma once

#include "CESerial/Serial.h"
#include "queue.h"
#include "CHardware.h"
#include <vector>
#include "GxxString.h"
#include "GXNotify.h"
#include "StdAfx.h"

#define BT_DEBUG 0

enum
{
	CALL_INCOMING,
	CALL_OUTGOING,
	CALL_MISS,
};

class DialNum
{
	char PhoneNum[40];
	BYTE iPhoneNumLen;

	GxxString	strPhoneNum;

public:
	DialNum()
	{
		ClearDialNum();
	}
	void ClearDialNum()
	{
		memset(PhoneNum,0,sizeof(PhoneNum)/sizeof(BYTE));
		iPhoneNumLen = 0;
		strPhoneNum = _T("");
	}
	void Add2DialNum(char c)
	{
		if (iPhoneNumLen < 39)
		{
			PhoneNum[iPhoneNumLen++] = c;
		}
		GxxString strTmp;
		strTmp.Format(_T("%c"), c);
		strPhoneNum += strTmp;
	}
	void DeleteDialNum()
	{
		if (iPhoneNumLen<39 && iPhoneNumLen>0)
		{
			iPhoneNumLen--;
			PhoneNum[iPhoneNumLen] = 0;
		}
		strPhoneNum = strPhoneNum.Left(strPhoneNum.GetLength()-1);
	}
	void SetDialNum(GxxString sNum)
	{
		ClearDialNum();
		strPhoneNum = sNum;
		for (int i=0;i<sNum.GetLength();i++)
		{
			PhoneNum[iPhoneNumLen++] = sNum[i] & 0xFF; 
		}
	}
	void SetDialNum(char* num, int len)
	{
		ClearDialNum();
		for (int i=0;i<min(len, 40); i++)
		{
			Add2DialNum(num[i]);
		}
	}
	GxxString & GetPhoneNum()
	{
		return strPhoneNum;
	}

	char* GetDialNum()
	{
		return PhoneNum;
	}
	int GetLen()
	{
		return iPhoneNumLen;
	}
};

struct CONTACT 
{
	DialNum		num;
	GxxString	Name;
};

class PhoneHardware : public CHardware
{
	//static PhoneHardware *This;

	HWND hWnd;
	// 串口对象
	CSerial		serial;
	CSerial		*pPhoneSerial;
	// 蓝牙消息队列
	Queue		BTCmdQueue;
	// 蓝牙事件通知
	HANDLE		hEventBT;
	// 串口线程句柄
	HANDLE		hThreadSerial;
	int			retryTimes;

	HANDLE		hEventVesrion;
	HANDLE		hEventName;
	HANDLE		hEventPwd;
	HANDLE		hEventQFP;
	HANDLE		hEventAutoStatus;

	BOOL		isExist;

	

public:
	CONTACT	contact;
	DialNum	dialNum;
	GxxString sVersion;		//xyf修改，去掉static
	char btname[32];
	char password[5];
public:
	
	void Init(HWND hwnd)
	{
		hWnd = hwnd;
		pbSupport = PHONEBOOK_UNSUPPORT;
		SoundStatus = SOUND_BTMODULE;
		// 初始化串口
//#ifndef _DEBUG
		if(GetFileAttributes(L"\\nand") != -1)
		{	
			serial.Open(_T("COM1:"));
		}
		
		serial.Setup(CSerial::EBaud115200);
		serial.SetupHandshaking(CSerial::EHandshakeOff);
		pPhoneSerial = &serial;

		// 创建串口监视线程
		DWORD dwThreadID = 0;
		hThreadSerial = (HANDLE)::CreateThread(NULL,0,SerialReadThread,this,0,&dwThreadID);
		if(hThreadSerial == INVALID_HANDLE_VALUE)
		{
			//MessageBox(_T("COM1 cannot be opened"),_T("Fatal error"));
		}
		// 创建蓝牙事件
		hEventBT = CreateEvent(NULL,0,0,NULL);
		// 创建蓝牙事件处理线程
		CreateThread(NULL, 0, HandleCommandThread, this, 0, &dwThreadID);


		// 查询蓝牙软件版本号
		hEventVesrion = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEventPwd = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEventName = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEventQFP = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEventAutoStatus = CreateEvent(NULL, FALSE, FALSE, NULL);

		// 创建配对线程
		Sleep(200);
		CreateThread(NULL, 0, PairThread, this, 0, &dwThreadID);
	}

	void Deinit()
	{

	}
	static DWORD PairThread(LPVOID lpParam)
	{
		PhoneHardware *p = (PhoneHardware *)lpParam;
		if(p->Version())
		{
			p->ReadPassword();
			p->ReadName();
			//p->QueryHFP();
			p->GetAutoStatus();
			p->isExist = 1;
		}
		else
		{
			p->isExist = 0;
		}
		//p->PairRecord();*/
		return 0;
	}
	static DWORD SerialReadThread(LPVOID lpParam)
	{
		COMSTAT comstat;				// COMSTAT struct 
		DWORD dwError;
		PhoneHardware *p = (PhoneHardware *)lpParam;
		if (p->serial.IsOpen())
		{
			RETAILMSG(BT_DEBUG,(TEXT("COM1 is Opened\r\n")));
			p->serial.Purge();
		}
		else
		{
			RETAILMSG(BT_DEBUG,(TEXT("COM1 is Closed\r\n")));
			return 0;
		}
		std::vector<BYTE> cmd;
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
				cmd.push_back(data[i]);
				if (cmd.size() > 256)
				{
					cmd.clear();
					break;
				}
				char cmd_data[256] = {0};
				if (data[i] == '\n' && cmd.size() > 1)
				{
					if (cmd[cmd.size()-2] == '\r')
					{
						// 一条指令收到, 插入到队列中
						for (int i=0;i<cmd.size();i++)
						{
							cmd_data[i] = cmd[i];
							//RETAILMSG(1, (TEXT("%c"), cmd[i]));
						}

						GxxString str;
						str.UTF8ToUNICODE(cmd_data);
						RETAILMSG(BT_DEBUG, (TEXT("%s"), str.GetData()));

						p->BTCmdQueue.join((BYTE*)cmd_data);
						SetEvent(p->hEventBT);
						cmd.clear();
					}
				}
			}
		}
	}
	void Pair()
	{
		char *cmd = "AT#CA\r\n";
		serial.Write(cmd);
	}
	void PairStop()
	{
		char *cmd = "AT#CB\r\n";
		serial.Write(cmd);
	}

	void HshfConnect(int index)
	{
		char *cmd;
		if (index == 0)
		{
			cmd = "AT#CC\r\n";
		}
		else
		{
			char cmd2[32] = {0};
			sprintf(cmd2, "AT#CC%d\r\n", index);
			cmd = cmd2;
		}
		serial.Write(cmd);
	}
	void HshfDisconnect()
	{
		char *cmd = "AT#CD\r\n";
		serial.Write(cmd);
	}
	void Reject()
	{
		char *cmd = "AT#CE\r\n";
		serial.Write(cmd);
	}
	void RecvCall()
	{
		char *cmd = "AT#CF\r\n";
		serial.Write(cmd);
	}
	void HangUp()
	{
		char *cmd = "AT#CG\r\n";
		serial.Write(cmd);
	}
	void RedKey()
	{
		if (CallStatus == CALL_COMING)
		{
			Reject();
		}
		else
		{
			HangUp();
		}
	}
	void Redial()
	{
		char *cmd = "AT#CH\r\n";
		serial.Write(cmd);
	}
	void Divert()
	{
		char *cmd = "AT#CO\r\n";
		serial.Write(cmd);
	}
	void MicSwitch()
	{
		char *cmd = "AT#CM\r\n";
		serial.Write(cmd);
	}
	void DeletePairInfo(int index)
	{
		char *cmd;
		if (index == -1)
		{
			cmd = "AT#CV\r\n"; 
		}
		else
		{
			char cmd2[32] = {0};
			sprintf(cmd2, "AT#CV%d\r\n", index);
			cmd = cmd2;
		}
		serial.Write(cmd);
	}
	void Dial(char *szTelenum)
	{
		char cmd2[256] = {0};
		sprintf(cmd2, "AT#CW%s\r\n", szTelenum);
		serial.Write(cmd2);
	}
	void Dial()
	{
		Dial(dialNum.GetDialNum());	
	}
	void DTMF(char c)
	{
		char cmd2[32] = {0};
		sprintf(cmd2, "AT#CX%c\r\n", c);
		serial.Write(cmd2);
	}
	void Reset()
	{
		char *cmd = "AT#CZ\r\n";
		serial.Write(cmd);
	}
	BOOL QueryHFP()
	{
		for (int i=0;i<3;i++)
		{
			char *cmd = "AT#CY\r\n";
			serial.Write(cmd);
			if(WAIT_OBJECT_0 == WaitForSingleObject(hEventQFP, 1000))
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	void PlayMusic()
	{
		char *cmd = "AT#MA\r\n";
		serial.Write(cmd);
	}
	void PauseMusic()
	{
		char *cmd = "AT#MB\r\n";
		serial.Write(cmd);
	}
	void StopMusic()
	{
		char *cmd = "AT#MC\r\n";
		serial.Write(cmd);
	}
	void NextMusic()
	{
		char *cmd = "AT#MD\r\n";
		serial.Write(cmd);
	}
	void PrevMusic()
	{
		char *cmd = "AT#ME\r\n";
		serial.Write(cmd);
	}
	void SetName(char *name)
	{
		char cmd2[256] = {0};
		sprintf(cmd2, "AT#MM%s\r\n", name);
		serial.Write(cmd2);
	}
	BOOL ReadName()
	{
		for (int i=0;i<3;i++)
		{
			char *cmd = "AT#MM\r\n";
			serial.Write(cmd);
			if (WAIT_OBJECT_0 == WaitForSingleObject(hEventName, 1000)) 
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	void SetPassword(const char *password)
	{
		char cmd2[256] = {0};
		sprintf(cmd2, "AT#MN%s\r\n", password);
		serial.Write(cmd2);
	}
	BOOL ReadPassword()
	{
		for (int i=0;i<3;i++)
		{
			char *cmd = "AT#MN\r\n";
			serial.Write(cmd);
			if (WAIT_OBJECT_0 == WaitForSingleObject(hEventPwd, 1000))
			{
				return FALSE;
			}
		}
		return FALSE;
	}
	void AutoConnect(BOOL bOn)
	{
		char *cmd;
		if (bOn)
		{
			cmd = "AT#MG\r\n";
		}
		else
		{
			cmd = "AT#MH\r\n";
		}
		serial.Write(cmd);
	}
	void AutoRecv(BOOL bOn)
	{
		char *cmd;
		if (bOn)
		{
			cmd = "AT#MP\r\n";
		}
		else
		{
			cmd = "AT#MQ\r\n";
		}
		serial.Write(cmd);
	}
	BOOL GetAutoStatus()
	{
		for (int i=0;i<3;i++)
		{
			char *cmd = "AT#MF\r\n";
			serial.Write(cmd);
			if(WAIT_OBJECT_0 == WaitForSingleObject(hEventAutoStatus, 1000))
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	void GetA2DPStatus()
	{
		char *cmd = "AT#MV\r\n";
		serial.Write(cmd);
	}
	void Upgrade()
	{
		char *cmd = "AT#MU\r\n";
		serial.Write(cmd);
	}
	void PairRecord()
	{
		char *cmd = "AT#MX\r\n";
		serial.Write(cmd);
	}
	BOOL Version()
	{
		for (int i=0;i<3;i++)
		{
			char *cmd = "AT#MY\r\n";
			serial.Write(cmd);
			if(WAIT_OBJECT_0 == WaitForSingleObject(hEventVesrion, 1000))
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	enum CALL_RECORD
	{
		RECORD_DIAL = 1,
		RECORD_RECV = 2,
		RECORD_MISS = 3
	};
	int now_record;
	void ReadRecord(CALL_RECORD r)
	{
		int record = (int)r;
		now_record = (int)r;
		char cmd[32] = {0};
		sprintf(cmd, "AT#PP%d\r\n", record);
		serial.Write(cmd);
	}
	void NextRecord()
	{
		char *cmd = "AT#PQ\r\n";
		serial.Write(cmd);
	}
	void GetSimBook()
	{
		char *cmd = "AT#PA\r\n";
		serial.Write(cmd);
	}
	BOOL GetPhoneBook()
	{
		if (BtStatus != BT_CONNECTED)
		{
			return 0;
		}
		retryTimes++;
		if (retryTimes > 5)
		{
			return 0;
		}
		pbSupport = PHONEBOOK_UNSUPPORT;
		char *cmd = "AT#PN\r\n";
		serial.Write(cmd);
		return 1;
	}
	void BTSwitch(BOOL bOn)
	{
		char *cmd;
		if (!bOn)
		{
			cmd = "AT#P0\r\n";
		}
		else
		{
			cmd = "AT#P1\r\n";
		}
		serial.Write(cmd);
	}
	void QueryDevice()
	{
		char *cmd = "AT#SA\r\n";
		serial.Write(cmd);
	}
	void StopQueryDevice()
	{
		char *cmd = "AT#SB\r\n";
		serial.Write(cmd);
	}
	void SPPConnect(char *addr)
	{
		char cmd[256] = {0};
		sprintf(cmd, "AT#SC%s\r\n", addr);
		serial.Write(cmd);
	}
	void SPPDisconnect()
	{
		char *cmd = "AT#SD\r\n";
		serial.Write(cmd);
	}
	void SPPSend(int len, char *data)
	{
		char cmd[256] = {0};
		sprintf(cmd, "AT#SE%02d%s\r\n", len, data);
		serial.Write(cmd);
	}
	void QueryDeviceName(char *addr)
	{
		char cmd[256] = {0};
		sprintf(cmd, "AT#SF%s\r\n", addr);
		serial.Write(cmd);
	}
	void StopQueryDeviceName()
	{
		char *cmd = "AT#SH\r\n";
		serial.Write(cmd);
	}
	void QuerySPP()
	{
		char *cmd = "AT#SY\r\n";
		serial.Write(cmd);
	}
	void PlayRing()
	{
		char *cmd = "AT#SR\r\n";
		serial.Write(cmd);
	}
	void OpenBT()
	{
		char *cmd = "AT#P1\r\n";
		serial.Write(cmd);
	}
	void CloseBT()
	{
		char *cmd = "AT#P0\r\n";
		serial.Write(cmd);
	}

	// --------------------------------------
	enum HFPSTATUS
	{
		HFP_INIT,
		HFP_STANDBY,
		HFP_CONNECTING,
		HFP_CONNECTED,
		HFP_DAILOUT,
		HFP_LINEIN,
		HFP_CALLING
	} HfpsStatus;
	enum CALLSTATUS
	{
		CALL_OUT,
		CALL_DIALING,
		CALL_COMING,
		CALL_IN
	}CallStatus;
	enum SPPSTATUS
	{
		SPP_INIT,
		SPP_STANDBY,
		SPP_QUERY,
		SPP_CONNECTING,
		SPP_CONNECTED,
		SPP_CANBEFOUND
	} SppStatus;
	enum BTSTATUS
	{
		BT_DISCONNECT,
		BT_PAIR,
		BT_STOPPAIR,
		BT_CONNECTING,
		BT_CONNECTED,
		BT_LINEIN,
		BT_DIALING,
		BT_DIALNO,
		BT_HANGUP,
		BT_RECV,
	} BtStatus;
	enum MUSICSTATUS
	{
		MUSIC_STANDBY,
		MUSIC_RUN
	} MusicStatus;
	enum SOUNDSTATUS
	{
		SOUND_MOBILE,
		SOUND_BTMODULE
	} SoundStatus;
	enum AUTOSTATUS
	{
		NO,
		YES
	};
	enum A2DPSTATUS
	{
		A2DP_NOCONNECT,
		A2DP_CONNECTED,
		A2DP_DISCONNECT
	} A2dpStatus;
	enum PHONEBOOKSTATUS
	{
		PHONEBOOK_INITED,
		PHONEBOOK_UNSUPPORT,
		PHONEBOOK_SUPPORT,
		PHONEBOOK_NO,
		PHONEBOOK_MOBILEEND,
		PHONEBOOK_SIMEND
	} PhoneBookStatus;
	enum DEVICESTATUS
	{
		DEVICE_STRENGTH,
		DEVICE_NAME,
		DEVICE_QUERYEND,
		DEVICE_QUERYSTOP
	} DeviceStatus;
	enum MICSTATUS
	{
		MIC_ON,
		MIC_OFF
	} MicStatus;
	static DWORD HandleCommandThread(LPVOID lpParam)
	{
		char CMD[256] = {0};
		PhoneHardware *p = (PhoneHardware*)lpParam;
		p->QueryHFP();
		while (1)
		{
			WaitForSingleObject(p->hEventBT,INFINITE);
			while (p->BTCmdQueue.fetch((BYTE*)CMD))
			{
				p->ParseCMD(CMD);
			}
		}
		return 0;
	}
	struct PairInfo 
	{
		int index;
		char addr[16];
		char name[256];
	};
	PairInfo pair_info[8];
	struct DeviceInfo
	{
		char addr[16];
		char name[256];
		char rssi[8];
	};
	BOOL pbSupport;
	void ParseCMD(char *cmd)
	{
		if (0 == strncmp(cmd, "IA", 2))
		{
			// 断开连接
			if (BtStatus != BT_DISCONNECT)
			{
				BtStatus = BT_DISCONNECT;
				GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_DISCONNECT, 0);
			}
			GXNotify::SendNotifyAsync(hWnd, "hfpstatus", 1, 0);
			
		}
		if (0 == strncmp(cmd, "IB", 2))
		{
			// 连接成功
			if (BtStatus != BT_CONNECTED)
			{
				pbSupport = PHONEBOOK_UNSUPPORT;
				retryTimes = 0;
				BtStatus = BT_CONNECTED;
				GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_CONNECTED, 0);
				GXNotify::SendNotifyAsync(hWnd, "hfpstatus", 3, 0);
			}
		}
		if (0 == strncmp(cmd, "ID", 2))
		{
			// 电话打入
			char szTeleNo[256] = {0};
			for (int i=0;i<strlen(cmd)-2;i++)
			{
				if (cmd[i+2] == '\r')
				{
					break;
				}
				szTeleNo[i] = cmd[i+2];
			}
			CallStatus = CALL_COMING;
			contact.num.SetDialNum(szTeleNo, strlen(szTeleNo));
			BtStatus = BT_LINEIN;
			GXNotify::SendNotifyAsync(hWnd,  "btstatus", BT_LINEIN, (DWORD)szTeleNo);
		}
		if (0 == strncmp(cmd, "IC", 2))
		{
			// 拨号
			BtStatus = BT_DIALING;
			CallStatus = CALL_DIALING;
			GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_DIALING, 0);
		}
		if (0 == strncmp(cmd, "IR", 2))
		{
			// 拨出的号码
			char szTeleNo[256] = {0};
			for (int i=0;i<strlen(cmd)-2;i++)
			{
				if (cmd[i+2] == '\r')
				{
					break;
				}
				szTeleNo[i] = cmd[i+2];
			}
			contact.num.SetDialNum(szTeleNo, strlen(szTeleNo));
			BtStatus = BT_DIALNO;
			GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_DIALNO, (DWORD)szTeleNo);
		}
		if (0 == strncmp(cmd, "IF", 2))
		{
			// 挂断电话
			BtStatus = BT_HANGUP;
			CallStatus = CALL_OUT;
			GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_HANGUP, 0);
		}
		if (0 == strncmp(cmd, "IG", 2))
		{
			// 接听电话
			BtStatus = BT_RECV;
			CallStatus = CALL_IN;
			GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_RECV, 0);
		}
		if (0 == strncmp(cmd, "IV", 2))
		{
			// 正在连接
			//BtStatus = BT_CONNECTING;
			GXNotify::SendNotifyAsync(hWnd, "hfpstatus", 2, 0);
			GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_CONNECTING, 0);
		}
		if (0 == strncmp(cmd, "IS", 2))
		{
			// Uart初始化完成
		}
		if (0 == strncmp(cmd, "II", 2))
		{
			BtStatus = BT_PAIR;
			// 进入配对
			GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_PAIR, 0);
		}
		if (0 == strncmp(cmd, "IJ", 2))
		{
			// 退出配对
			BtStatus = BT_STOPPAIR;
			GXNotify::SendNotifyAsync(hWnd, "btstatus", BT_STOPPAIR, 0);
		}
		if (0 == strncmp(cmd, "IO", 2))
		{
			// mic 状态
			if (cmd[2] == '1')
			{
				MicStatus = MIC_OFF;
				GXNotify::SendNotifyAsync(hWnd, "micstatus", MIC_OFF, 0);
			}
			else
			{
				MicStatus = MIC_ON;
				GXNotify::SendNotifyAsync(hWnd, "micstatus", MIC_ON, 0);
			}
		}
		if (0 == strncmp(cmd, "MA", 2))
		{
			// AV 处于待机状态
			MusicStatus = MUSIC_STANDBY;
			GXNotify::SendNotifyAsync(hWnd, "musicstatus", MUSIC_STANDBY, 0);
		}
		if (0 == strncmp(cmd, "MB", 2))
		{
			// AV 开始运行
			MusicStatus = MUSIC_RUN;
			GXNotify::SendNotifyAsync(hWnd, "musicstatus", MUSIC_RUN, 0);
		}
		if (0 == strncmp(cmd, "mc", 2))
		{
			// 语音在蓝牙端
			SoundStatus = SOUND_BTMODULE;
			GXNotify::SendNotifyAsync(hWnd, "soundstatus", SOUND_BTMODULE, 0);
		}
		if (0 == strncmp(cmd, "md", 2))
		{
			// 语言在手机端
			SoundStatus = SOUND_MOBILE;
			GXNotify::SendNotifyAsync(hWnd, "soundstatus", SOUND_MOBILE, 0);
		}
		if (0 == strncmp(cmd, "MF", 2))
		{
			// 自动接听的状态
			int recv_status = 0;
			int connect_status = 0;
			if (cmd[3] == '0')
			{
				recv_status = NO;
			}
			else
			{
				recv_status = YES;
			}
			if (cmd[2] == '0')
			{
				connect_status = NO;
			}
			else
			{
				connect_status = YES;
			}
			SetEvent(hEventAutoStatus);
			GXNotify::SendNotifyAsync(hWnd, "autostatus", recv_status, connect_status);
		}
		if (0 == strncmp(cmd, "MN", 2))
		{
			// 蓝牙密码
			memset(password, 0, sizeof(password)/sizeof(password[0]));
			for (int i=0;i<4;i++)
			{
				password[i] = cmd[i+2];
			}
			SetEvent(hEventPwd);
			GXNotify::SendNotifyAsync(hWnd, "phonepassword", (DWORD)password, 0);
		}
		if (0 == strncmp(cmd, "MM", 2))
		{
			// 蓝牙名字
			char name[32] = {0};
			for (int i=0;i<strlen(cmd)-2;i++)
			{
				if (cmd[i+2] == '\r')
				{
					break;
				}
				name[i] = cmd[i+2];
			}
			SetEvent(hEventName);
			strcpy(btname, name);
			GXNotify::SendNotifyAsync(hWnd, "btname", (DWORD)name, 0);
		}
		if (0 == strncmp(cmd, "MG", 2))
		{
			// HFP 的状态
			int hfp_status = cmd[2]-0x30;
			HfpsStatus = (HFPSTATUS)hfp_status;
			if (HfpsStatus >= HFP_CONNECTED)
			{
				BtStatus = BT_CONNECTED;
				GXNotify::SendNotifyAsync(hWnd, "btstatus", BtStatus, 0);
			}
			if (HfpsStatus == HFP_CALLING)
			{
				CallStatus = CALL_IN;
			}
			if (HfpsStatus == HFP_DAILOUT)
			{
				CallStatus = CALL_DIALING;
			}
			if (HfpsStatus == HFP_LINEIN)
			{
				CallStatus = CALL_COMING;
			}
			SetEvent(hEventQFP);
			GXNotify::SendNotifyAsync(hWnd, "hfpstatus", hfp_status, 0);
		}
		if (0 == strncmp(cmd, "MX", 2))
		{
			// 配对记录
			int index = cmd[2]-0x30;
			if (index > 0)
			{
				PairInfo *p_pair_info = &pair_info[index-1];
				memset(p_pair_info, 0, sizeof(pair_info[0]));
				//try
				{
					p_pair_info->index = cmd[2]-0x30;
					for (int i=0;i<12;i++)
					{
						p_pair_info->addr[i] = cmd[3+i];
					}
					for (int i=0;i<strlen(cmd)-15;i++)
					{
						if (cmd[15+i] == '\r')
						{
							break;
						}
						p_pair_info->name[i] = cmd[15+i];
					}
				}
				//catch (CException* e)
				{

				}
				GXNotify::SendNotifyAsync(hWnd, "pairrecord", (DWORD)p_pair_info, 0);
			}
			
		}
		if (0 == strncmp(cmd, "MU", 2))
		{
			// A2DP 状态
			if (cmd[2] == '1')
			{
				A2dpStatus = A2DP_CONNECTED;
				GXNotify::SendNotifyAsync(hWnd, "a2dpstatus", A2DP_CONNECTED, 0);
			}
			else
			{
				A2dpStatus = A2DP_NOCONNECT;
				GXNotify::SendNotifyAsync(hWnd, "a2dpstatus", A2DP_NOCONNECT, 0);
			}
			
		}
		if (0 == strncmp(cmd, "MY", 2))
		{
			// A2DP 断开连接
			A2dpStatus = A2DP_DISCONNECT;
			GXNotify::SendNotifyAsync(hWnd, "a2dpstatus", A2DP_DISCONNECT, 0);
		}
		if (0 == strncmp(cmd, "WN", 2))
		{
			// 下载电话本初始化完成
			PhoneBookStatus = PHONEBOOK_INITED;
			GXNotify::SendNotifyAsync(hWnd, "phonebookstatus", PHONEBOOK_INITED, 0);
		}
		if (0 == strncmp(cmd, "MW", 2))
		{
			// 蓝牙软件版本
			char version[32] = {0};
			for (int i=0;i<strlen(cmd)-2;i++)
			{
				if (cmd[i+2] == '\r')
				{
					break;
				}
				version[i] = cmd[i+2];
			}
			sVersion.UTF8ToUNICODE(version, 32);
			SetEvent(hEventVesrion);
			GXNotify::SendNotifyAsync(hWnd, "btversion", (DWORD)version, 0);
		}
		if (0 == strncmp(cmd, "PA", 2))
		{
			// 是否支持电话本的下载
			if (cmd[2] == '0')
			{	
				PhoneBookStatus = PHONEBOOK_UNSUPPORT;
				pbSupport = PHONEBOOK_UNSUPPORT;
				GXNotify::SendNotifyAsync(hWnd, "phonebookstatus", PHONEBOOK_UNSUPPORT, 0);
			}
			else
			{
				PhoneBookStatus = PHONEBOOK_SUPPORT;
				pbSupport = PHONEBOOK_SUPPORT;
				GXNotify::SendNotifyAsync(hWnd, "phonebookstatus", PHONEBOOK_SUPPORT, 0);
			}
		}
		if (0 == strncmp(cmd, "PB", 2))
		{
			// 下载的电话号码
			char szName[256] = {0};
			char szNo[32] = {0};
			int start=0;
			for (int i=0;i<strlen(cmd)-2;i++)
			{
				if (cmd[i+2] == -1)
				{
					start = i+1;
					break;
				}
				szName[i] = cmd[i+2];
			}
			for (int i=0;i<strlen(cmd)-2;i++)
			{
				if (cmd[start+i+2] == '\r')
				{
					break;
				}
				szNo[i] = cmd[start+i+2];
			}
			CONTACT contact;
			contact.num.SetDialNum(szNo, strlen(szNo));
			contact.Name.UTF8ToUNICODE(szName);
			PhoneBookStatus = PHONEBOOK_NO;
			GXNotify::SendNotifyAsync(hWnd, "phonebookstatus", PHONEBOOK_NO, (DWORD)&contact);
		}
		if (0 == strncmp(cmd, "PC", 2))
		{
			// 下载手机电话本结束
			PhoneBookStatus = PHONEBOOK_MOBILEEND;
			GXNotify::SendNotifyAsync(hWnd, "phonebookstatus", PHONEBOOK_MOBILEEND, 0);
		}
		if (0 == strncmp(cmd, "PE", 2))
		{
			// 下载SIM卡电话本结束
			PhoneBookStatus = PHONEBOOK_SIMEND;
			GXNotify::SendNotifyAsync(hWnd, "phonebookstatus", PHONEBOOK_SIMEND, 0);
		}
		if (0 == strncmp(cmd, "PD", 2))
		{
			// 通话记录
			char szName[256] = {0};
			char szNo[40] = {0};
			int start=0;
			for (int i=0;i<strlen(cmd)-2;i++)
			{
				if (cmd[i+2] == -1)
				{
					start = i+1;
					break;
				}
				szName[i] = cmd[i+2];
			}
			for (int i=0;i<strlen(cmd)-2&&i<40;i++)
			{
				if (cmd[start+i+2] == '\r')
				{
					break;
				}
				if ((cmd[start+i+2]>='0' && cmd[start+i+2]<='9') || cmd[start+i+2]=='+')
				{
					szNo[i] = cmd[start+i+2];
				}
			}

			CONTACT contact;
			contact.num.SetDialNum(szNo, strlen(szNo));
			contact.Name.UTF8ToUNICODE(szName);
			//RETAILMSG(COUT_MSG,(TEXT("phone record  name=%s, name=%s \r\n"), contact.Name.GetData(),  contact.num.GetDialNum()));

			GXNotify::SendNotifyAsync(hWnd, "phonerecordstatus", now_record, (DWORD)&contact);
		}
		if (0 == strncmp(cmd, "PF", 2))
		{
			// 通话记录结束
			GXNotify::SendNotifyAsync(hWnd, "phonerecordstatus", now_record, 0);
	//		RETAILMSG(COUT_MSG,(TEXT("phone record  end \r\n")));
		}
		if (0 == strncmp(cmd, "SA", 2))
		{
			// 查询蓝牙地址和信号强度
			DeviceInfo device_info;
			memset(&device_info, 0, sizeof(device_info));
			for (int i=0;i<12;i++)
			{
				device_info.addr[i] = cmd[2+i];
			}
			for (int i=0;i<4;i++)
			{
				device_info.rssi[i] = cmd[14+i];
			}
			DeviceStatus = DEVICE_STRENGTH;
			GXNotify::SendNotifyAsync(hWnd, "devicestatus", DEVICE_STRENGTH, (DWORD)&device_info);
		}
		if (0 == strncmp(cmd, "SB", 2))
		{
			// 查询蓝牙地址和信号强度结束
			DeviceStatus = DEVICE_QUERYEND;
			GXNotify::SendNotifyAsync(hWnd, "devicestatus", DEVICE_QUERYEND, 0);
		}
		if (0 == strncmp(cmd, "SE", 2))
		{
			// 接收的SPP数据
			char len[4] = {0};
			char data[128] = {0};
			for (int i=0;i<2;i++)
			{
				len[i] = cmd[2+i];
			}
			for (int i=0;i<strlen(cmd)-4;i++)
			{
				if (cmd[4+i] = '\r')
				{
					break;
				}
				data[i] = cmd[4+i];
			}
			GXNotify::SendNotifyAsync(hWnd, "sppdata", atoi(len), (DWORD)data);
		}
		if (0 == strncmp(cmd, "SF", 2))
		{
			// 查询蓝牙设备的名字
			DeviceInfo device_info;
			memset(&device_info, 0, sizeof(device_info));
			for (int i=0;i<12;i++)
			{
				device_info.addr[i] = cmd[2+i];
			}
			for (int i=0;i<strlen(cmd)-14;i++)
			{
				if (cmd[14+i] == '\r')
				{
					break;
				}
				device_info.name[i] = cmd[14+i];
			}
			DeviceStatus = DEVICE_NAME;
			GXNotify::SendNotifyAsync(hWnd, "devicestatus", DEVICE_NAME, (DWORD)&device_info);
		}
		if (0 == strncmp(cmd, "SH", 2))
		{
			// 停止查询蓝牙设备的名字,或者查询失败
			DeviceStatus = DEVICE_QUERYSTOP;
			GXNotify::SendNotifyAsync(hWnd, "devicestatus", DEVICE_QUERYSTOP, 0);
		}
		if (0 == strncmp(cmd, "SP", 2))
		{
			// SPP的状态
			int spp_status = cmd[2] - 0x30;
			SppStatus = (SPPSTATUS)spp_status;
			GXNotify::SendNotifyAsync(hWnd, "sppstatus", spp_status, 0);
		}
	}

	GxxString GetVersion()	//xyf修改，去掉static
	{
		return (GxxString)L"BT Version : "+sVersion;
	}

	public:
		PhoneHardware()
		{
			HfpsStatus = HFP_INIT;
			CallStatus = CALL_OUT;
			SppStatus = SPP_INIT;
			BtStatus = BT_DISCONNECT;
			MusicStatus = MUSIC_STANDBY;
			SoundStatus = SOUND_MOBILE;
			A2dpStatus = A2DP_NOCONNECT;
			PhoneBookStatus = PHONEBOOK_INITED;
			DeviceStatus = DEVICE_STRENGTH;
			MicStatus = MIC_OFF;
			now_record = (CALL_RECORD)0;
			isExist = -1;
		}
public:
	static PhoneHardware* pInstance;
	static PhoneHardware * Instance(HWND hwnd)
	{
		if (!pInstance)
		{
			pInstance = new PhoneHardware();
		}
		return pInstance;
	}
public:
	BOOL IsExist()
	{
		int i=0;
		while (isExist == -1)
		{
			Sleep(100);
			if (i++>80)
			{
				return FALSE;
			}
		}
		return isExist;
	}
};

