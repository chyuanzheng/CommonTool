#pragma once

#include "CHardware.h"
#include "i2c/chip.h"
#include "queue.h"
#include "CESerial/Serial.h"
#include "WMMsg.h"
#include <vector>
#include "ipodcp.h"
#include <Pnp.h>
#include <Objbase.h>

using namespace std;


#define IPODDEBUG 0

//#define USESERIAL
#define USBIPOD
typedef union {
	DEVDETAIL d;
	char pad[sizeof(DEVDETAIL)+MAX_DEVCLASS_NAMELEN];
} MYDEV;
#define IPOD_E  _T("IPOD_READ_EVENT")
#define IPOD_MAXBYTE 256

enum
{
	IPOD_NAME,
	IPOD_TIME,
	IPOD_PLAYSTATUS,
	IPOD_ARTIST,
	IPOD_ALBUM,
	IPOD_GENRE,
	IPOD_TITLE,
	IPOD_NUMRECORD,
	IPOD_CATRECORD,
	IPOD_SHUFFLE,
	IPOD_REPEAT,
	IPOD_AUTHSUCCESS
};
class IpodHardware : public CHardware
{
public:
	HANDLE	hSendEvent;
	HANDLE	hReadThread;
	HANDLE	hHandlerEvent;
#ifdef USESERIAL
	CSerial		IPODSerial;
	CSerial*	pIPODSerial;
	
	int		IsCmdAck;

	int failTimes;
#endif

#ifdef USBIPOD
	HANDLE m_hDrv;
	HANDLE m_hEventRead;
	HANDLE m_hEventAttach;
	HANDLE m_hEventHandler;
	HANDLE m_hTreadHandler;
#endif
	GxxString	sIpodName;
	enum
	{
		NOIPOD,
		MUSICIPOD,
		VIDEOIPOD
	};
	int			iPodModel;
	enum
	{
		IPOD_NOAUTH,
		IPOD_CRACKAUTH,
		IPOD_CPAUTH
	};
	int	ipodAuthMode;
	IpodCP			ipodCP;
	enum
	{
		IPOD_STOP,
		IPOD_PLAYING,
		IPOD_PAUSE,
		IPOD_FF,
		IPOD_FB,
		IPOD_ENDFFB,
		IPOD_RESERVE
	};
	int ipodPlayStatus;
	int ipodShuffleStatus;
	int ipodRestoreShuffleStatus;
	int ipodRepeatStatus;

	DWORD ipodNowIndex;

	int iCurTime;
	int iTotalTime;

	
public:
	// IPOD消息队列
	Queue		ipodQueue;
	// IPOD 发送队列
	Queue		ipodCMD;

	WORD		TransID;


#ifdef USEIIC
	BYTE	WriteBytes[2];
#endif
	HWND hWnd;
	int		iNum;
public:
	void Init(HWND hwnd)
	{
		hWnd = hwnd;
		DWORD dwThreadId = 0;
		// 初始化后串口
#ifdef USESERIAL
		IPODSerial.Open(_T("COM3:"));
		IPODSerial.Setup(CSerial::EBaud38400);
		IPODSerial.SetupHandshaking(CSerial::EHandshakeOff);
		pIPODSerial = &IPODSerial;
		IsCmdAck = 1;
#endif
#ifdef USBIPOD
		m_hDrv = CreateFile(_T("IPD1:"),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
#endif

		ipodPlayStatus = 0;
		ipodAuthMode = 0;
		iCurTime = 0;
		iTotalTime = 0;
		ipodPlayStatus = 0;
		iPodModel = 0;
		eHierarchy = HIERARCHY_NONE;
		TransID = 0;
		if(ipodCP.DetectIpodCPVersion())
		{
			ipodCP.ReadDeviceID();
			ipodCP.SelfTest();
			ipodCP.ReadAcCertificateLength();
			ipodCP.ReadAcCertificateData();
		}
		// 创建串口读线程
		hReadThread = ::CreateThread(NULL, 0, ReadThread, this, 0, &dwThreadId);
		// 创建串口发送线程
		::CreateThread(NULL, 0, SendThread, this, 0, &dwThreadId);
		// 创建事件
		hSendEvent = ::CreateEvent(NULL, 0, 0, NULL);
		hHandlerEvent = CreateEvent(NULL, 0, 0, NULL);
		m_hEventAttach = CreateEvent(NULL, 0, 0, NULL);
		// 创建处理线程
		CreateThread(NULL, 0, HandlerThread, this, 0, &dwThreadId);
		// 创建检测线程
		CreateThread(NULL, 0, CheckThread, this, 0, &dwThreadId);
	}


	// lingoes 0 General lingoes
	void RequestiPodName(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x02,0x00,0x07,0xF7};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));

		}
	}

	void RequestiPodModelNum(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x02,0x00,0x0D,0xF1};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));

		}
	}
	// lingoes 2 simply remote lingoes
	void ReleaseKey(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x00,0xfb};
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
		}
	}
	void Play(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x01,0xfa};
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));	
		}
	}
	// 音量加
	void VolumeAdd(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x02,0xf9};
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}
	// 音量减
	void VolumeDec(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x04,0xf7};
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
		}
	}
	// 下一首
	void Forward(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x08,0xf3};
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}		
	}
	// 上一首
	void Backward(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x10,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}		
	}
	// 下一专辑
	void Next(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x20,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}
	// 上一专辑
	void Last(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x40,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}
	// 停止
	void Stop(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x03,0x02,0x00,0x80,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
		ReleaseKey();
	}
	// 播放（仅）
	void PlayOnly(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x06,0x02,0x00,0x00,0x01, 0x00, 0x00,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
		}
		ReleaseKey();
	}
	// 暂停（仅）
	void PauseOnly(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x06,0x02,0x00,0x00,0x02,0x00,0x00,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}
	// 静音（交替）
	void Mute(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x04,0x02,0x00,0x00, 0x04,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// 下一播放列表
	void NextList(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x04,0x02,0x00,0x00, 0x20,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}
	// 上一播放列表
	void LastList(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x04,0x02,0x00,0x00, 0x40,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// 随机播放
	void RandomPlay(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x04,0x02,0x00,0x00, 0x80,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// 重复播放
	void RepeatPlay(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x05,0x02,0x00,0x00,0x00, 0x01,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// IPOD关闭
	void IPODOFF(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x05,0x02,0x00,0x00,0x00,0x04,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// IPOD打开
	void IPODON(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x05,0x02,0x00,0x00,0x00,0x08,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// 菜单按钮
	void MENU(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x05,0x02,0x00,0x00,0x00,0x40,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// OK/选择按钮
	void OK(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x05,0x02,0x00,0x00,0x00,0x80,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// 向上滚动
	void ScrollUp(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x06,0x02,0x00,0x00,0x00,0x00,0x01,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}

	// 向下滚动
	void ScrollDown(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x06,0x02,0x00,0x00,0x00,0x00,0x02,0x00};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));
			 
		}
	}
	// 向左
	void Left()
	{
	}
	// 向右
	void Right()
	{
	}


	// lingoes 3 display lingoes
	void GetPlayStatus3(int send = 0)
	{
		BYTE cmd[] = {0xff,0x55,0x02,0x03,0x0F,0xEC};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));

		}
	}

	// SetRemoteEventNotification － Enable following notifications: Track playback index, Play status (play, pause, stop, FF, and RW)
	void SetRemoteEventNotification3(int send = 0)
	{
		BYTE cmd[] = {0xFF, 0x55, 0x06, 0x03, 0x08, 0x00, 0x00, 0x80, 0x0E, 0xE5 };
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));

		}
	}

	void GetIndexedPlayingTrackInfo3(BYTE type, DWORD tracknum, int send = 0)
	{
		BYTE cmd[] = {0xFF, 0x55, 0x09, 0x03, 0x12, 0x00, 0x00, 0x00, 0x00,0x00, 0x00,0x00, 0xE5 };
		cmd[5] = type;
		cmd[6] = tracknum >> 24;
		cmd[7] = tracknum >> 16;
		cmd[8] = tracknum >> 8;
		cmd[9] = tracknum;
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		if (send)
		{
			SendCommand(cmd, sizeof(cmd));
		}
		else
		{
			JoinToSend(cmd, sizeof(cmd));

		}
	}



	// longoes 4 Extent lingoes



	// 获取歌曲信息
	BOOL GetMusicID3(BYTE *CMD)
	{
		// 返回当前歌曲的类型列表的位置
		BYTE sendCMD[] = {0xFF, 0x55, 0x07, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00 };
		for (int i=0;i<4;i++)
		{
			sendCMD[6+i] = CMD[4+i];
		}
		// 发送获取歌曲名命令
		sendCMD[10] = Checksum(&sendCMD[2], sendCMD[2]);
		JoinToSend(sendCMD, sizeof(sendCMD));
		// 发送获取演唱者命令
		sendCMD[5] = 0x22;
		sendCMD[10] = Checksum(&sendCMD[2], sendCMD[2]);
		JoinToSend(sendCMD, sizeof(sendCMD));
		// 发送获取专辑命令
		sendCMD[5] = 0x24;
		sendCMD[10] = Checksum(&sendCMD[2], sendCMD[2]);
		JoinToSend(sendCMD, sizeof(sendCMD));
		return 0;
	}
	// 获取歌曲信息
	BOOL GetMusicID3(int trackindex)
	{
		// 返回当前歌曲的类型列表的位置
		BYTE sendCMD[] = {0xFF, 0x55, 0x07, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00 };

		sendCMD[6] = trackindex>>24;
		sendCMD[7] = trackindex>>16;
		sendCMD[8] = trackindex>>8;
		sendCMD[9] = trackindex;

		// 发送获取歌曲名命令
		sendCMD[10] = Checksum(&sendCMD[2], sendCMD[2]);
		JoinToSend(sendCMD, sizeof(sendCMD));
		// 发送获取演唱者命令
		sendCMD[5] = 0x22;
		sendCMD[10] = Checksum(&sendCMD[2], sendCMD[2]);
		JoinToSend(sendCMD, sizeof(sendCMD));
		// 发送获取专辑命令
		sendCMD[5] = 0x24;
		sendCMD[10] = Checksum(&sendCMD[2], sendCMD[2]);
		JoinToSend(sendCMD, sizeof(sendCMD));
		return 0;
	}

	void GetMusicNumCMD()
	{
		// 获取歌曲目录号
		BYTE cmd3[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x1E, 0xDB};
		JoinToSend(cmd3, sizeof(cmd3));
	}

	void SetPlayStatusChangeNotification()
	{
		// 打开所有的状态变化通知
		BYTE cmd1[] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x26, 0x01, 0xd1};
		JoinToSend(cmd1, sizeof(cmd1));
	}

	void ClosePlayStatusChangeNotification()
	{
		// 关闭所有的状态变化通知
		BYTE cmd1[] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x26, 0x00, 0xd2};
		JoinToSend(cmd1, sizeof(cmd1));
	}

	void GetPlayStatus()
	{
		// 获取播放状态
		BYTE cmd[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x1c, 0xdd};
		JoinToSend(cmd, sizeof(cmd));
	}

	void GetStatus()
	{
		// 获取歌曲目录号
		BYTE cmd1[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x1E, 0xDB};
		JoinToSend(cmd1, sizeof(cmd1));
		Sleep(100);
		// 获取播放状态
		BYTE cmd2[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x1c, 0xdd};
		JoinToSend(cmd2, sizeof(cmd2));
	}
	void IpodPlay()
	{
		BYTE cmd[] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x29, 0x01, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
		// 获取歌曲目录号
		BYTE cmd1[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x1E, 0xDB};
		JoinToSend(cmd1, sizeof(cmd1));
		// 获取播放状态
		BYTE cmd2[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x1c, 0xdd};
		JoinToSend(cmd2, sizeof(cmd2));
	}

	void IpodPause()
	{
		BYTE cmd[] = {0xFF, 0x55, 0x04, 0x4, 0x00, 0x29, 0x01, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	void IpodStop()
	{
		BYTE cmd[] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x29, 0x02, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	void IpodNext()
	{		
		BYTE cmd[] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x29, 0x03, 0xcc};
		JoinToSend(cmd, sizeof(cmd));
	}

	void IpodLast()
	{
		BYTE cmd[] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x29, 0x04, 0xcb};
		JoinToSend(cmd, sizeof(cmd));
	}

	void IpodCircle()
	{
		BYTE cmd1[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x1E, 0xDB};
		JoinToSend(cmd1, sizeof(cmd1));
	}

	void IpodRandom()
	{

	}

	void GetShuffle()
	{
		BYTE cmd[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x2C, 0xCD};
		JoinToSend(cmd, sizeof(cmd));
	}

	enum
	{
		SHUFFLE_OFF,
		SHUFFLE_TRACK,
		SHUFFLE_ALBUM
	};
	void SetShuffle(BYTE mode, BYTE bRestore = 1)
	{
		BYTE cmd[] = {0xFF, 0x55, 0x05, 0x04, 0x00, 0x2E, 0x00, 0x00, 0x00};
		cmd[6] = mode;
		cmd[7] = bRestore;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	enum
	{
		REPEAT_OFF,
		REPEAT_TRACK,
		REPEAT_ALL
	};
	void SetRepeat(BYTE mode, BYTE bRestore = 1)
	{
		BYTE cmd[] = {0xFF, 0x55, 0x05, 0x04, 0x00, 0x31, 0x00, 0x00, 0x00};
		cmd[6] = mode;
		cmd[7] = bRestore;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	void StartIDPS(WORD transID)
	{
		BYTE cmd[] = {0xFF, 0x55, 0x04, 0x00, 0x38, transID>>8, transID, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	void EndIDPS(WORD transID)
	{
		BYTE cmd[] = {0xFF, 0x55, 0x05, 0x00, 0x3B, transID>>8, transID, 0x00, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	void SetFIDTokenValues(WORD transID, BYTE numFIDTokenValues, BYTE *FIDTokenValues)
	{
		BYTE cmd[256] = {0xFF, 0x55, 0x00, 0x00, 0x39, transID>>8, transID, numFIDTokenValues};
		cmd[2] = 9+numFIDTokenValues;
		for (int i=0;i<numFIDTokenValues;i++)
		{
			cmd[8+i] = FIDTokenValues[i];
		}
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	void IdentifyDeviceLingoes(int type=0, DWORD deviceID = 0, int send = 0)
	{
		if (type == 0)
		{
			// lingo 0 ,不要求授权
			BYTE cmd[] = {0xFF, 0x55, 0x0E, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00,\
				0x00, 0x00, 0x00, 0xDE};
			cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
			if (send)
			{
				SendCommand(cmd, sizeof(cmd));
			}
			else
			{
				JoinToSend(cmd, sizeof(cmd));
			}
		}
		if (type == 1)
		{
			// lingo 0 2 3 4, 立即要求授权
			BYTE cmd[] = {0xFF, 0x55, 0x0E, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1D, 0x00,\
				0x00, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0xBA};
			cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
			if (send)
			{
				SendCommand(cmd, sizeof(cmd));
			}
			else
			{
				JoinToSend(cmd, sizeof(cmd));
			}
		}
	}

	void SetiPodPreferences()
	{
		RETAILMSG(1, (TEXT("SetiPodPreferences\r\n")));
		BYTE cmd[] = {0xFF, 0x55, 0x05, 0x00, 0x2B, 0x00, 0x01, 0x01, 0xCE};
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		{
			JoinToSend(cmd, sizeof(cmd));
		}
		cmd[6] = 0x08;
		cmd[7] = 0x01;
		cmd[sizeof(cmd)-1] = Checksum(&cmd[2], cmd[2]);
		{
			JoinToSend(cmd, sizeof(cmd));
		}
	}
	void SetiPodPreferences_AudioOut()
	{
		RETAILMSG(1, (TEXT("SetiPodPreferences_AudioOut\r\n")));
		BYTE cmd2[] = {0xFF, 0x55, 0x05, 0x00, 0x2B, 0x03, 0x01, 0x01, 0xCE};
		cmd2[sizeof(cmd2)-1] = Checksum(&cmd2[2], cmd2[2]);
		JoinToSend(cmd2, sizeof(cmd2));
	}
	enum
	{
		CATE_NONE,
		CATE_PLAYLIST,
		CATE_ARTIST,
		CATE_ALBUM,
		CATE_GENRE,
		CATE_TRACK,
		CATE_COMPOSER,
		CATE_AUDIOBOOK,
		CATE_PODCAST,
	};
	void SelectDBRecord(BYTE code, DWORD index)
	{
		BYTE cmd[12] = {0xFF, 0x55, 0x08, 0x04, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00};
		cmd[6] = code;
		cmd[7] = index>>24;
		cmd[8] = index>>16;
		cmd[9] = index>>8;
		cmd[10] = index;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	void PlayCurrentSelection(DWORD index)
	{
		BYTE cmd[11] = {0xFF, 0x55, 0x08, 0x04, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00};
		cmd[6] = index>>24;
		cmd[7] = index>>16;
		cmd[8] = index>>8;
		cmd[9] = index;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	void ResetDBSelection()
	{
		eHierarchy = HIERARCHY_MUSIC;
		BYTE cmd[7] = {0xFF, 0x55, 0x3, 0x4, 0x00, 0x16, 0xE3};
		JoinToSend(cmd, sizeof(cmd));
	}

	void GetNumberCategorizedDBRecords(BYTE code)
	{
		BYTE cmd[8] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x18, 0x00, 0x00};
		cmd[6] = code;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	//void GetNumberCategorizedDatabaseRecords()
	//{

	//}
	void RetrieveCategorizedDatabaseRecords(BYTE type, DWORD index, DWORD count)
	{
		BYTE cmd[16] = {0xFF, 0x55, 0x0C, 0x04, 0x00, 0x1A};
		cmd[6] = type;
		cmd[7] = index >> 24;
		cmd[8] = index >> 16;
		cmd[9] = index >> 8;
		cmd[10] = index;
		cmd[11] = count >> 24;
		cmd[12] = count >> 16;
		cmd[13] = count >> 8;
		cmd[14] = count;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	enum
	{
		HIERARCHY_NONE,
		HIERARCHY_MUSIC = 0x1,
		HIERARCHY_VIDEO = 0x2
	};	
	BYTE eHierarchy;
	void ResetDBSelectionHierarchy(BYTE type)
	{
		eHierarchy = type;
		BYTE cmd[8] = {0xFF, 0x55, 0x04, 0x04, 0x00, 0x3b, 0x00, 0x00};
		cmd[6] = type;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	void RetAcInfoCap()
	{
		RETAILMSG(1, (TEXT("Ret ac capicity\r\n")));
		// 返回 bit 0 1 (2 3) 
		BYTE cmd[] = {0xFF, 0x55, 0x07, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	void RetAcName(BYTE type, GxxString strName)
	{
		// 0x01 0x06 0x07 0x08
		RETAILMSG(1, (TEXT("Ret ac name %d\r\n"), type));
		BYTE cmd[64] = {0xFF, 0x55, 0x00, 0x00, 0x28, type};
		char ac_name[64] = {0};
		strName.ToUTF8(ac_name, 64);
		memcpy(&cmd[6], ac_name, strName.GetLength()+1);
		cmd[2] = strName.GetLength()+1+3;
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	void RetAcSurportFirmware()
	{

	}
	void RetAcSurportLingo()
	{

	}
	void RetAcFirmwareVersion()
	{
		// 0x4
		RETAILMSG(1, (TEXT("Ret ac firmware\r\n")));
		BYTE cmd[] = {0xFF, 0x55, 0x06, 0x00, 0x28, 0x04, 0x01, 0x00, 0x00, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	void RetAcHardVersion()
	{
		// 0x5
		RETAILMSG(1, (TEXT("Ret ac hardware\r\n")));
		BYTE cmd[] = {0xFF, 0x55, 0x06, 0x00, 0x28, 0x05, 0x01, 0x00, 0x00, 0x00};
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}
	void RetAcManufacturer()
	{

	}
	void RetAcModelNum()
	{

	}
	void RetAcSerialNum()
	{

	}
	void RetIncomingPayloadSize()
	{

	}

	void RetDevAuthenticationInfo(BYTE *pCertData, int certLen)
	{
		BYTE totalBlock = (certLen-1)/128;
		for (int i=0;;i++)
		{
			if (certLen >= 128)
			{
				BYTE cmd[138] = {0xFF, 0x55, 0x86, 0x00, 0x15, 0x02, 0x00, i, totalBlock};
				memcpy(&cmd[9], &pCertData[i*128], 128);
				cmd[137] = Checksum(&cmd[2], cmd[2]);
				JoinToSend(cmd, sizeof(cmd));
			}
			if (certLen < 128)
			{
				BYTE cmd[138] = {0xFF, 0x55, 0x00, 0x00, 0x15, 0x02, 0x00, i, totalBlock};
				memcpy(&cmd[9], &pCertData[i*128], certLen);
				cmd[2] = certLen + 6;
				cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
				JoinToSend(cmd, sizeof(cmd));
				break;
			}
			certLen -= 128;
		}
	}

	void RetDevAuthSignature(BYTE *data, int len)
	{
		BYTE cmd[138] = {0xFF, 0x55, 0x00, 0x00, 0x18};
		cmd[2] = len+2;
		memcpy(&cmd[5], data, len);
		cmd[cmd[2]+3] = Checksum(&cmd[2], cmd[2]);
		JoinToSend(cmd, sizeof(cmd));
	}

	static DWORD SendThread(LPVOID lpParam);
	enum
	{
		P_NONE,
		P_START=2,
		P_LEN = 3,
		P_DATA,
		P_CHCEKSUM = 0xFFFE,
		P_END = 0xFFFF,
		P_ERROR
	};
	static DWORD ReadThread(LPVOID lpParam);

	static DWORD HandlerThread(LPVOID lpParam);
	static DWORD CheckThread(LPVOID lpParam)
	{
		IpodHardware *p = (IpodHardware*)lpParam;
#ifdef USBIPOD
		GUID guid={ 0xe92020db, 0x39ab, 0x47f8, { 0x8b, 0x5d, 0x2f, 0x7a, 0x22, 0x6d, 0x73, 0xde } };
		HANDLE hQueue, hn;
		MSGQUEUEOPTIONS msgopts;

		msgopts.dwSize = sizeof(MSGQUEUEOPTIONS);
		msgopts.dwFlags = 0;
		msgopts.dwMaxMessages = 0;
		msgopts.cbMaxMessage = sizeof(MYDEV);
		msgopts.bReadAccess = TRUE;

		//创建消息队列
		hQueue = CreateMsgQueue(NULL, &msgopts);

		if (hQueue == 0) 
		{
			return 0;
		}

		hn = RequestDeviceNotifications(&guid, hQueue, TRUE);

		MYDEV devDetail;
		DWORD dwFlags;
		DWORD dwSize;

		for(;;)
		{
			//等待消息队列的返回
			DWORD rel = ::WaitForSingleObject(hQueue, INFINITE);

			if(rel == WAIT_OBJECT_0)
			{
				//读消息队列的数据，这里是读出很多消息的，因为有比较多的设备
				while(::ReadMsgQueue(hQueue, &devDetail, sizeof(MYDEV), &dwSize, 0, &dwFlags) == TRUE)
				{
					if (devDetail.d.fAttached)
					{
						if (p->m_hDrv == INVALID_HANDLE_VALUE)
						{
							p->m_hDrv = CreateFile(_T("IPD1:"),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
						}
						SetEvent(p->m_hEventAttach);
						// ipod 加载
						if (!p->iPodModel)
						{
							p->EntrySimpleControlMode();
						}
						p->RequestiPodName();
					}else{

						// ipod 卸载
						if (p->iPodModel != NOIPOD)
						{
							if(INVALID_HANDLE_VALUE!=p->m_hDrv)
							{
								CloseHandle(p->m_hDrv);
								p->m_hDrv = INVALID_HANDLE_VALUE;
							}
							p->iPodModel = NOIPOD;
							p->sIpodName.Empty();
							p->ResetTransID();
							p->SendMsg(WM_IPOD, IPOD_NAME, 0);
						}
					}
				}
			}
		}
		return 1;
#else
		while (1)
		{
			if (!p->iPodModel)
			{
				p->EntrySimpleControlMode();
			}
			p->RequestiPodName();
			//Sleep(100);
			//p->GetShuffle();
			//Sleep(100);
			//p->GetRepeat();
			Sleep(1000);
		}
#endif
	}
	
	BYTE IpodHardware::Checksum(BYTE *cmd, int len)
	{
		WORD checksum = 0;
		for (int i=0;i<len+1;i++)
		{
			checksum += cmd[i];
		}
		return (BYTE)(0x100 - (checksum & 0xFF));
	}

	

	

	




	// 进入高级控制模式
	void EntryHighControlMode()
	{
		// 进入高级控制模式
		//BYTE cmd0[] = {0xff,0x55,0x03,0x00,0x01,0x04,0xf8}; // 这条命令重新验证了,导致之前的验证失败
		BYTE cmd0[] = {0xff,0x55,0x02,0x00,0x05,0xf9};
		JoinToSend(cmd0, sizeof(cmd0));
	}

	// 进入简单控制模式
	void EntrySimpleControlMode()
	{
		BYTE cmd0[] = {0xff,0x55,0x03,0x00,0x01,0x02,0xFA};
		SendCommand(cmd0, sizeof(cmd0));
	}


	
	void SaveShuffle()
	{
		ipodRestoreShuffleStatus = ipodShuffleStatus;
	}
	void RestoreShuffle()
	{
		if (ipodRestoreShuffleStatus != SHUFFLE_OFF)
		{
			SetShuffle(ipodRestoreShuffleStatus);
		}
	}

	void GetRepeat()
	{
		BYTE cmd[] = {0xFF, 0x55, 0x03, 0x04, 0x00, 0x2F, 0xCA};
		JoinToSend(cmd, sizeof(cmd));
	}



	// mode 0

	void JoinToSend(BYTE *cmd, int len)
	{
		ipodCMD.join(cmd, len);
		SetEvent(hSendEvent);
	}
	void ClearRead()
	{
		iNum = 0;
	}
	int GetIpodModel()
	{
		return iPodModel;
	}
	GxxString GetIpodName()
	{
		return sIpodName;
	}
	int GetCurTime()
	{
		return iCurTime;
	}
	int GetTotalTime()
	{
		return iTotalTime;
	}
	int GetHierarchy()
	{
		return eHierarchy;
	}
private:
	IpodHardware()
	{

	}
public:
	static IpodHardware* pInstance;
	static IpodHardware * Instance(HWND hwnd)
	{
		if (!pInstance)
		{
			pInstance = new IpodHardware();
			pInstance->Init(hwnd);
		}
		return pInstance;
	}
	WORD GetTransID()
	{
		return ++TransID;
	}
	void ResetTransID()
	{
		TransID = 0;
	}
	DWORD GetNowIndex()
	{
		return ipodNowIndex;
	}
	void SendCommand(const BYTE* cmd ,DWORD count)
	{
#ifdef USBIPOD
		DWORD dwWritten = 0;
		::WriteFile(m_hDrv,cmd+1,count-1,&dwWritten,NULL);
#endif
#ifdef USESERIAL
		pIPODSerial->Write(cmd, count);
#endif

	}
};

