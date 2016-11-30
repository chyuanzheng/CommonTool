#include "StdAfx.h"

#include "MediaMsg.h"
#include "PIP.h" 
#include "param.h"
#include "TVOut.h"
#include "../i2c/chip.h"
#include "../Audio/Audio.h"
#include "MInfoLib/TCCMediaInfo.h"

#pragma comment(lib, "PIP/MInfoLib/MInfoLib.lib")

HWND MediaControl::hWndGRT;
HWND MediaControl::hWndVedio;
CRect MediaControl::rcMedia;
int MediaControl::mediaMode;
int MediaControl::movieStatus;
int MediaControl::musicStatus;
int MediaControl::cameraStatus;
int MediaControl::cameraFormat;
int MediaControl::volMedia = 0;
int MediaControl::videoMode;
GXString	MediaControl::lastMovieFile;
GXString	MediaControl::lastMusicFile;
int	MediaControl::lastMovieTime = 0;
int MediaControl::lastMusicTime = 0;
int	MediaControl::TIMES;
BOOL MediaControl::isMute = 0;
BOOL CALLBACK MediaControl::OnEnumWindows(HWND hWnd, LPARAM lParam)
{
	DWORD dwProID;
	GetWindowThreadProcessId(hWnd, &dwProID);
	if (lParam == dwProID)
	{
		hWndVedio = hWnd;
		return FALSE;
	}
	return TRUE;
}

void SetDShowThreadPriorityReg(BOOL bActive)
{
	if( bActive )
	{
		// Set DShow Priority
		HKEY hkey = NULL;
		DWORD dwDisposition;
		if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\DirectShow\\ThreadPriority"), 
			0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey, &dwDisposition) != ERROR_SUCCESS) 
		{
			//RETAILMSG(1, (APP FUNC L" Couldn't create registry key\r\n"));
			return;
		}

		int readjust_priority = 2;

		DWORD dwValue;
		dwValue = 249 - readjust_priority;
		RegSetValueEx(hkey, _T("Highest"), 0, REG_DWORD, (PBYTE)&dwValue, sizeof(DWORD));
		dwValue = 250 - readjust_priority;
		RegSetValueEx(hkey, _T("AboveNormal"), 0, REG_DWORD, (PBYTE)&dwValue, sizeof(DWORD));
		dwValue = 251 - readjust_priority;
		RegSetValueEx(hkey, _T("Normal"), 0, REG_DWORD, (PBYTE)&dwValue, sizeof(DWORD));
		dwValue = 252 - readjust_priority;
		RegSetValueEx(hkey, _T("BelowNormal"), 0, REG_DWORD, (PBYTE)&dwValue, sizeof(DWORD));

		dwValue = 250 - readjust_priority;
		RegSetValueEx(hkey, _T("Video"), 0, REG_DWORD, (PBYTE)&dwValue, sizeof(DWORD));

		dwValue = 249 - readjust_priority;
		RegSetValueEx(hkey, _T("AsyncVideoRenderer"), 0, REG_DWORD, (PBYTE)&dwValue, sizeof(DWORD));

		RegCloseKey(hkey);
	}
	else 
	{
		// Remove DShow Priority
		RegDeleteKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\DirectShow"));
	}
}

BOOL MediaControl::Init(HWND hwnd)
{
	hWndGRT = hwnd;
	PROCESS_INFORMATION piVideo;
	if (CreateProcess(_T("\\windows\\media.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &piVideo))
	{
		Sleep(200); 
		EnumWindows(OnEnumWindows, (LPARAM)piVideo.dwProcessId);
		PostMessage(hWndVedio, WM_SETHWND, (WPARAM)hWndGRT, 0);
		HideMediaWnd();
		MediaControl::SetMediaRect(CRect(0, 0, 800, 480));
		MediaControl::SetVMode(1);
		SetDShowThreadPriorityReg(TRUE);
		return 1;
	}
	return 0;
}

void MediaControl::SetMediaMode(int mode)
{
	// 如果在倒车状态下等待
	/*static HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"GRT_REARCAMERA_STATUS");
	while (1)
	{
		if (WaitForSingleObject(hEvent, 1) == WAIT_OBJECT_0)
		{
			Sleep(1);
		}
		else
		{
			break;
		}
	}*/
	
	mediaMode = mode;
	SendMessage(hWndVedio, WM_MEDIAMODE, mode, 0);
}

void MediaControl::InitCamera(int format, int width, int height)
{
	// 如果在倒车状态下等待
	//chip_saa7111.WaitRearCamera();
	cameraFormat = format;
	format -= 1;
	SendMessage(hWndVedio, WM_INITPREVIEW, format, (LPARAM)(width|height<<16));
}

void MediaControl::StartCamera()
{
	// 如果在倒车状态下等待
	//chip_saa7111.WaitRearCamera();
	cameraStatus = CAMERAPLAY;
	SendMessage(hWndVedio, WM_CAMERAPLAY, 0, 0);
}

void MediaControl::PauseCamera()
{
	// 如果在倒车状态下等待
	//chip_saa7111.WaitRearCamera();
	cameraStatus = CAMERAPAUSE;
	SendMessage(hWndVedio, WM_CAMERAPLAY, 1, 0);
}

void MediaControl::StopCamera()
{
	// 如果在倒车状态下等待
	//chip_saa7111.WaitRearCamera();
	cameraStatus = NOPLAY;
	SendMessage(hWndVedio, WM_CAMERAPLAY, 2, 0);
}

int MediaControl::PlayMovieFile(GXString str, double playtime)
{
	TccTVOut::Instance()->TVOutClose();
	if (str.IsEmpty())
	{
		return 0;
	}
	if (GetFileAttributes(str.GetData()) == -1)
	{
		return 0;
	}
	CTCCMediaInfo mInfo;
	mInfo.CheckFile((WCHAR*)str.GetData());
	unsigned int VideoCodec = mInfo.m_info.videoCodecInfo.videoCodec;
	if ((VideoCodec>>8) == 0x444956)
	{
		return 0;
	}
	switch (VideoCodec)
	{
	case TCC_VC_DIV4:
	case TCC_VC_DIV5:
	case TCC_VC_DIV6:
	case TCC_VC_DIVX:
	case TCC_VC_DX50:
	case TCC_VC_div4:
	case TCC_VC_div5:
	case TCC_VC_div6:
	case TCC_VC_divx:
	case TCC_VC_dx50:
		return 0;
	default:
		break;
	}
	
	COPYDATASTRUCT cs;
	cs.lpData = (PVOID)str.GetData();
	cs.cbData = 2*(str.GetLength()+1);
	lastMovieFile = str;

	SendMessage(hWndVedio, WM_COPYDATA, (WPARAM)hWndGRT, (LPARAM)&cs);
	MuteMedia();
	int bRet =  SendMessage(hWndVedio, WM_MOVIEPLAY, 3, playtime);
	if (bRet == 1)
	{
		movieStatus = MEDIAPLAY;
		SetVMode(videoMode);
	}
	else
	{
		movieStatus = NOPLAY;
	}
	Sleep(500);
	UnMuteMedia(1500);
	TccTVOut::Instance()->TVOutOpen();
	return bRet;
}

void MediaControl::ResumeMovie()
{
	if (!lastMovieFile.IsEmpty())
	{
		PlayMovieFile(lastMovieFile, lastMovieTime);
	}
}

void MediaControl::PlayMovie()
{
	if (movieStatus == NOPLAY)
	{
		return ;
	}
	if (movieStatus == MOVIEPRESTOP)
	{
		PlayMovieFile(lastMovieFile, lastMovieTime);
	}
	else
	{
		movieStatus = MEDIAPLAY;
		MuteMedia();
		PostMessage(hWndVedio, WM_MOVIEPLAY, 0, 0);
		UnMuteMedia();
	}
}

void MediaControl::PauseMovie()
{
	movieStatus = MEDIAPAUSE;
	MuteMedia();
	PostMessage(hWndVedio, WM_MOVIEPLAY, 1, 0);
}

void MediaControl::PreStopMovie()
{
	lastMovieTime = GetMoviePlayTime();
	SetVModeNoStore(1);
	movieStatus = MOVIEPRESTOP;
	MuteMedia();
	SendMessage(hWndVedio, WM_MOVIEPLAY, 2, 0);
	TccTVOut::Instance()->TVOutClose();
}

void MediaControl::StopMovie()
{
	TccTVOut *p = TccTVOut::Instance();
	p->TVOutClose();
	lastMovieTime = 0;
	lastMovieFile.Empty();
	SetVModeNoStore(1);
	movieStatus = NOPLAY;
	MuteMedia();
	SendMessage(hWndVedio, WM_MOVIEPLAY, 2, 0);
	
}

int MediaControl::PlayMusicFile(GXString str, double playtime)
{
	if (str.IsEmpty())
	{
		return 0;
	}
	if (GetFileAttributes(str.GetData()) == -1)
	{
		return 0;
	}
	COPYDATASTRUCT cs;
	cs.lpData = (PVOID)str.GetData();
	cs.cbData = 2*(str.GetLength()+1);
	lastMusicFile = str;
	SendMessage(hWndVedio, WM_COPYDATA, (WPARAM)hWndGRT, (LPARAM)&cs);
	MuteMedia();
	int ret = SendMessage(hWndVedio, WM_MUSICPLAY, 3, playtime);
	if (ret)
	{
		musicStatus = MEDIAPLAY;
	}
	UnMuteMedia();
	return ret;
}

BOOL MediaControl::PlayMusic()
{
	if (musicStatus == NOPLAY)
	{
		return 0;
	}
	if (musicStatus == MUSICPRESTOP)
	{
		return PlayMusicFile(lastMusicFile, lastMusicTime);
	}
	else
	{
		musicStatus = MEDIAPLAY;
		MuteMedia();
		PostMessage(hWndVedio, WM_MUSICPLAY, 0, 0);
		UnMuteMedia();
		return 0;
	}
	
}

void MediaControl::PauseMusic()
{
	//mediaStatus = MEDIAPAUSE;
	MuteMedia();
	PostMessage(hWndVedio, WM_MUSICPLAY, 1, 0);

}

void MediaControl::SetMusicTime(int time)
{
	MuteMedia();
	PostMessage(hWndVedio, WM_MUSICTIME, time, 0);
	UnMuteMedia();
}

void MediaControl::SetMovieTime(int time)
{
	MuteMedia();
	PostMessage(hWndVedio, WM_MOVIETIME, time, 0);
	UnMuteMedia();
}

void MediaControl::PreStopMusic()
{
	lastMusicTime = GetMusicPlayTime();
	musicStatus = MUSICPRESTOP;
	MuteMedia();
	SendMessage(hWndVedio, WM_MUSICPLAY, 2, 0);
}
void MediaControl::StopMusic()
{
	lastMusicTime = 0;
	musicStatus = NOPLAY;
	MuteMedia();
	SendMessage(hWndVedio, WM_MUSICPLAY, 2, 0);
}

void MediaControl::ShowMediaWnd()
{
	ShowWindow(hWndVedio, SW_SHOW);
	sysConfig.bFullScreen = 1;
}

void MediaControl::HideMediaWnd()
{
	ShowWindow(hWndVedio, SW_HIDE);
}

void MediaControl::SetMediaRect(CRect &rc)
{
	rcMedia = rc;
	if (rc.Height() == 480)
	{
		sysConfig.bFullScreen = 1;
	}
	else
	{
		sysConfig.bFullScreen = 0;
	}
	PostMessage(hWndVedio, WM_MEDIARECT, rc.left|(rc.top<<16), rc.right|(rc.bottom<<16));
}


int	MediaControl::GetMoviePlayStatus()
{
	return  SendMessage(hWndVedio, WM_MOVIESTATUS, 0, 0);
}

int MediaControl::GetMusicPlayStatus()
{
	return  SendMessage(hWndVedio, WM_MUSICSTATUS, 0, 0);
}

int MediaControl::SetMovieCap(int cap)
{
	if (cap)
	{
		return SendMessage(hWndVedio, WM_MOVIEPLAY, 4, 1);
	}
	else
	{
		return SendMessage(hWndVedio, WM_MOVIEPLAY, 4, 0);
	}
	return 0;
}

void MediaControl::SetVolume(int vol)
{
	volMedia = vol;
	//KillTimer(NULL, 1);
	if (isMute)
	{
		vol = 100;
	}
	if (vol > 100)
	{
		vol = 100;
	}
	if (vol < 0)
	{
		vol = 0;
	}
	SendMessage(hWndVedio, WM_VOLUME, vol, 0);
}

void MediaControl::ResumeVolume()
{
	if (volMedia==0)
	{
		return;
	}
	volMedia = 0;
	SendMessage(hWndVedio, WM_VOLUME, 0, 0);
	//TIMES = volMedia/4;
	//SetTimer(NULL, 1, 50, ResumeVolProc);
}

int MediaControl::SetVMode(int mode)
{
	videoMode = mode;
	return PostMessage(hWndVedio, WM_VMODE, mode, 0);
}

int MediaControl::SetVModeNoStore(int mode)
{
	return PostMessage(hWndVedio, WM_VMODE, mode, 0);
}

int MediaControl::ResumeVMode()
{
	return PostMessage(hWndVedio, WM_VMODE, videoMode, 0);
}

int MediaControl::GetMusicPlayTime()
{
	return SendMessage(hWndVedio, WM_MUSICTIME, 0, 1);
}

int MediaControl::GetMoviePlayTime()
{
	return SendMessage(hWndVedio, WM_MOVIETIME, 0, 1);
}

void MediaControl::PopAttenProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
	KillTimer(hwnd, idEvent);
	SendMessage(hWndVedio, WM_VOLUME, volMedia, 0);
	RETAILMSG(1, (TEXT("Movie sound open\r\n")));
}

void MediaControl::ResumeVolProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
	// 500ms
	SendMessage(hWndVedio, WM_VOLUME, --TIMES*4, 0);
	if (TIMES <= 0)
	{
		volMedia = 0;
		KillTimer(NULL, idEvent);
	}
}

void MediaControl::MuteMedia()
{
	SendMessage(hWndVedio, WM_VOLUME, 100, 0);
	Sleep(50);
}

void MediaControl::UnMuteMedia(int time)
{
	Sleep(200);
	SetTimer(hWndGRT, ::RegisterWindowMessage(L"_MuteMedia"), time, PopAttenProc);
}

void MediaControl::SetRatio(BOOL bRadio)
{
	SendMessage(hWndVedio, WM_PLAYRADIO, bRadio, 0);
}

void MediaControl::SetCameraCrop(int left, int right, int top, int bottom)
{
	PostMessage(hWndVedio, WM_CAMERACROPRECT, left|(top<<16), right|(bottom<<16));
}

void MediaControl::Mute(BOOL mute)
{
	isMute = mute;
	SetVolume(volMedia);
}