#pragma once

#include "CXWinFun.h"
#include "IpodHardware.h"
#include "GxxLabel.h"
#include "GxxProBar.h"
#include "GxxListView.h"
#include "TccMediaWnd.h"
#include "ipodcp.h"
#include "IpodList.h"
#include "iPodLib.h"


class IpodWnd : public CXWinFun
{
	//IpodHardware*	pIpodHardware;
	//IpodCP			ipodCP;
	//IpodList		ipodList;
	iPodLib*		pIPodLib;
	int iCurTime;
	int iTotalTime;
	GxxLabel		*pButtPlay;
	GxxLabel		*pButtPause;
	GxxProBar		*pProbarIpod;
	GxxLabel		*pCurTime;
	GxxLabel		*pTotalTime;
	GxxLabel		*pLabDisplay1;
	GxxLabel		*pLabDisplay2;
	GxxLabel		*pLabDisplay3;
	GxxLabel	*pLabIpodInfo;

	GxxWindow	*pMainWnd;
	GxxWindow	*pListWnd;
	GxxWindow	*pWndMusic;
	GxxListView	*pPlayList;

	GxxProBar	*pProbarList;
	

	int			videoType;
	BOOL		bHasIpod;

	GXString sIpodName;

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
	int	ipodPlayStatus;

	enum
	{
		NOIPOD,
		MUSICIPOD,
		VIDEOIPOD
	};

	POINT	ptClick;
	BOOL	bPressed;

public:
	void Init();
	void Start();
	void End();
	void Entry();
	void Leave();
	void Deinit();
	void SetControlFun(GXBaseControl *pControl, const char *funtype, const char *funval);

	// 按键功能函数
	DECLARE_BUTTON_CALLBACK(KeyPlay, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyPause, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyNext, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyPrev, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyMenu, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyOK, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyStop, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyUp, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyDown, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyLeft, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyRight, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyPlayPause, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyFF, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyFB, IpodWnd);
	DECLARE_BUTTON_CALLBACK(ClickIpodBar, IpodWnd);
	DECLARE_BUTTON_CALLBACK(IpodListClick, IpodWnd);

	DECLARE_BUTTON_CALLBACK(IpodSelection, IpodWnd);
	DECLARE_BUTTON_CALLBACK(SelectionToHome, IpodWnd);
	DECLARE_BUTTON_CALLBACK(IpodBack, IpodWnd);
	DECLARE_BUTTON_CALLBACK(IpodListDown, IpodWnd);
	DECLARE_BUTTON_CALLBACK(IpodListUp, IpodWnd);

	DECLARE_NOTIFY_CALLBACK(IpodDetectNotify, IpodWnd);

	LRESULT DoTimer(GXBaseControl *pControl, UINT nID);
	LRESULT DoLButtonDown(GXBaseControl *pControl, POINT pt);
	LRESULT DoLButtonUp(GXBaseControl *pControl, POINT pt);

	GXString FormatTimeString(int time);

	DECLARE_MSGHANDLER(HandlerIpodMsg, IpodWnd);
	DECLARE_NOTIFY_CALLBACK(IpodClick, IpodWnd);

	GxxLabel *pLabKeyMode;
	GxxLabel *pLabKeyRepeat;
	GxxLabel *pLabModePreview;
	GxxLabel *pLabModeRandom;
	GxxLabel *pLabRepeatTrack;
	GxxLabel *pLabRepeatFolder;
	DECLARE_BUTTON_CALLBACK(KeyMode, IpodWnd);
	DECLARE_BUTTON_CALLBACK(ModeRand, IpodWnd);
	DECLARE_BUTTON_CALLBACK(ModePreview, IpodWnd);
	DECLARE_BUTTON_CALLBACK(KeyRepeat, IpodWnd);
	DECLARE_BUTTON_CALLBACK(RepeatTrack, IpodWnd);
	DECLARE_BUTTON_CALLBACK(RepeatFolder, IpodWnd);

	BOOL IsDeviceExist();

	BOOL EndHook()
	{
		return 0;
	}

	DECLARE_NOTIFY_CALLBACK(PowerOff, IpodWnd);
	DECLARE_NOTIFY_CALLBACK(SystemMute, IpodWnd);
	DECLARE_NOTIFY_CALLBACK(SystemNext, IpodWnd);
	DECLARE_NOTIFY_CALLBACK(SystemPrev, IpodWnd);
	DECLARE_NOTIFY_CALLBACK(SysRightKey, IpodWnd);

	ListItem* InsertSong(GXString str);
	void InsertSongID(GXString sid);
	static void FileListStatus(GXBaseControl *pControl, DWORD status, BOOL redraw);

	BOOL bPreviewMode;
	void PreviewStop();

	DECLARE_NOTIFY_CALLBACK(NaviMediaControl, IpodWnd);


	
	


	
	





};