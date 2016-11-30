#pragma once
#include "GxxString.h"
#include "CRect.h"

#define GXString GxxString 

enum    //magellan/src/inc/camdef.h
{
	NONE_CAMMOD = 0,
	MT9D112,
	TVP5150A,
	TVP5150A_PAL,
	TW9900,
	TW9900_PAL
};

// render flag
enum
{
	RENDER_NORMAL,		// 普通,无半透明,无特征色	
	RENDER_CHKEY,		// 仅特征色可见
	RENDER_ALPHA,		// 25% 半透明
	RENDER_ALPHACHKEY	// 25% 半透明 + 特征色全不透明(?)
};

enum
{
	NOVIDEO,
	NTSC,
	PAL,
	SECAM
};

enum MEDIAMODE
{
	NONE,
	MOVIE,
	CAMERA,
	MUSIC
};

enum{
	PLAY_STATUS_STOP,
	PLAY_STATUS_PLAY,
	PLAY_STATUS_PAUSE,
	PLAY_STATUS_MAX,		
};
enum
{
	NOPLAY,
	CAMERAPLAY,
	CAMERAPAUSE,
	MEDIAPLAY,
	MEDIAPAUSE,
	MOVIEPRESTOP,
	MUSICPRESTOP
};

class CE_HardwareDll_API MediaControl
{
	static HWND		hWndGRT;
	static HWND		hWndVedio;
	static CRect	rcMedia;
	static int		mediaMode;
	static int		movieStatus;
	static int		musicStatus;
	static int		cameraStatus;
	static int		cameraFormat;
	static int		volMedia;
	static int		videoMode;

	static GXString	lastMovieFile;
	static int		lastMovieTime;
	static GXString	lastMusicFile;
	static int		lastMusicTime;
	static int		TIMES;
	static BOOL		isMute;

public:
	static int GetMusicPlayTime();
	static int GetMoviePlayTime();
public:
	static CRect GetMediaRect()
	{
		return rcMedia;
	}
	static int GetMediaMode()
	{
		return mediaMode;
	}
	static int GetMediaStatus()
	{
		if (mediaMode == MUSIC)
		{
			return musicStatus;
		}
		if (mediaMode == MOVIE)
		{
			return movieStatus;
		}
		if (mediaMode == CAMERA)
		{
			return cameraStatus;
		}
		return NOPLAY;
	}
	static int GetCameraFormat()
	{
		return cameraFormat;
	}
	static BOOL CALLBACK OnEnumWindows(HWND hWnd, LPARAM lParam);
	static BOOL Init(HWND hwnd);
	static DWORD MonitorThread(LPVOID lpParam);
	static void InitPIP(UINT x = 244,\
		UINT y = 76,\
		UINT xcut = 0,\
		UINT ycut = 0,\
		UINT srcwidth = 720,\
		UINT srcheight = 480,\
		UINT winoff_w = 0,\
		UINT winoff_h = 0,\
		UINT dest_w = 360,\
		UINT dest_h = 270,\
		UINT xoff = 3);

	static void DeinitPIP();
	static void PIPSetRenderMode(int mode);
	static void PIPSetVideoPos(CRect &rect);
	static void PIPSetVideoWindow(HWND hWnd);
	static void StartPIP();
	static void EndPIP();
	static void StartMovie();
	static void EndMovie();
	static void PlayFile(GXString path);

	static void PIPPlayFiles(GXString FilePath, CRect CurrentVRendRect, HWND hWnd);
	static void PIPPlay();
	static void PIPPause();
	static void PIPStop();
	static void PIPFullScreen(BOOL bFull);

	static void SetMediaMode(int mode);
	static void InitCamera(int format, int width=0, int height=0);
	static void StartCamera();
	static void PauseCamera();
	static void StopCamera();

	static int PlayMovieFile(GXString str, double playtime);
	static void PlayMovie();
	static void PauseMovie();
	static void PreStopMovie();
	static void StopMovie();
	static void SetMovieTime(int);
	static void ResumeMovie();

	static int PlayMusicFile(GXString str, double playtime);
	static BOOL PlayMusic();
	static void PauseMusic();
	static void PreStopMusic();
	static void StopMusic();
	static void SetMusicTime(int);

	static void ShowMediaWnd();
	static void HideMediaWnd();
	static void SetMediaRect(CRect &rc);
	static int	GetMoviePlayStatus();
	static int GetMusicPlayStatus(); 

	static int SetMovieCap(int cap);
	static void SetVolume(int vol);
	static void ResumeVolume();

	static int SetVMode(int mode);
	static int SetVModeNoStore(int mode);
	static int ResumeVMode();

	static void MuteMedia();
	static void UnMuteMedia(int time = 500);

	static void Mute(BOOL mute);

	static void SetRatio(BOOL b);

	static void CALLBACK PopAttenProc(
		HWND hwnd, 
		UINT uMsg, 
		UINT idEvent, 
		DWORD dwTime 
		); 
	static void CALLBACK ResumeVolProc(
		HWND hwnd, 
		UINT uMsg, 
		UINT idEvent, 
		DWORD dwTime 
		); 

	static void Close()
	{
		PostMessage(hWndVedio, WM_CLOSE, 0, 0);
	}
	static void SetCameraCrop(int left, int right, int top, int bottom);
};


//#define  ALLOW_VIDEO