#pragma once
#include "IPODDllModule.h"
#include "Activity.h"
#include "ControlHelp.h"

#include "GxxControlGroup.h"
#include "GXNotify.h"
#include "GxxAniLable.h"
#include "iPodHardware/IPodAppLib.h"
#include "GxxMoveText.h"
#include "GxxPicIcon.h"
#include "GxxClickProgressBar.h"
#include "TimerManager.h"
#include "GxxIpodListGroup.h"
#include "TccMediaWndEx.h"
#include "GxxVedioSetup.h"
#include "GxxIpodIcon.h"

class CE_IPODACTIVITY_API  IPODActivity : public Activity, public GxxTimer
{
public:

	/*enum
	{
		NONE = -1,
		MUSIC,
		MOVIE,
		LIST
	};*/

	static IPODActivity* pThis;	//保存自身的指针

	IPOD_SEL_DB_TYPE m_iCurrentMediaMode;	//当前的媒体类型
	void SwitchUserInterface();	//切换UI

	void ClearUserInterface();	//清空界面

	void SwitchToListGroup() ;

	int video_source;

	IPODActivity();
	virtual ~IPODActivity (){}
	virtual  void onCreate();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	
	static Activity* CreateControl();
	virtual void  onResume();
	virtual void onPause();
	virtual void onStop();

	void TimerTick( UINT nIDEvent );

	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, IPODActivity);

	DECLARE_NOTIFY_CALLBACK(IpodNameNotify, IPODActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyCurrentAndTotalFileNum, IPODActivity);
	DECLARE_NOTIFY_CALLBACK(SetIPODVolume, IPODActivity);
	DECLARE_NOTIFY_CALLBACK(SetIpodMute, IPODActivity);

	//void DetectMediaMode();

protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
private:

	int iTimerDetectIpod;	//ID，保存检测IPOD的timer的ID
	//int iTimerDetectMediaMode;

	GxxAniLable* pInc_Into_MainInterface;
	IPodAppLib		*pIPodLib;

	GxxAniLable* pLabel_PrevVideo;
	GxxAniLable* pLabel_NextVideo;
	GxxAniLable* pLabelPlayAndPause;
	//GxxAniLable* pLabelPause;

	GxxMoveText* pLabel_MusicName;
	GxxMoveText* pLabel_MusicArtist;
	GxxMoveText* pLabel_MusicAlbum;

	GxxAniLable* pLabel_BrowseList;


//	GxxAniLable* pLabelSwitchToMusic;
//	GxxAniLable* pLabelSwitchToMovie;

	GxxAniLable* pLabel_MainOrInfo;

	GxxAniLable* pLabel_currentTime;
	GxxAniLable* pLabel_totaltime;

	GxxClickProgressBar* pProgressVideoTime;

	GxxAniLable* pLabel_Repeat;
	GxxAniLable* pLabelShre;

	GxxPicIcon* pPicShuffle;

	GxxPicIcon* pPicLoop1;
	GxxPicIcon* pPicLoopAll;

	GxxPicIcon* pPicCommandFail;

	GxxAniLable* pLabelToSetupAudio;
	
	GxxIpodListGroup* pIpodList;

	int IpodListItemId;

	GxxControlGroup* pControlGroup_main;
	GxxControlGroup* pControlGroup_Info;
	GxxControlGroup* pControl_group_IpodList;

	GxxControlGroup* pControlGroup_MusicInfo;
	GxxControlGroup* pControlGroup_MovieInfo;
	GxxControlGroup* pControlGroup_fullScreen;
	GxxControlGroup* pControlGroup_FullScreenControls;

	GxxAniLable* pLabel_VideoCount;

	GxxAniLable* pLabel_ReturnMain;

	TccMediaWndEx* pMediaWnd;
	int iTimeVideoDetect;	//检查VIDEO的定时器的ID
	int iTimerHideControlId;	//隐藏全屏时的控件

	void SubScreen();	//缩小屏幕
	void StartVideoDetect();	//检查VIDEO
	void VideoSourceAutoDetect();

	void NextVideo();
	void PrevVideo();
	void PlayAndPause();

	void StartFullScreenMovieWnd();		//视频窗口，全屏
	void StopFullScreenMovieWnd();		//停止视频窗口
	void ReStartFullScreenMovieWnd();		//重新开始视频窗口全屏

	static void ClickMediaWnd(GxxView *p, void *dwParam);	//视频全屏时，点击视频的处理函数
	void ShowFullControls();
	void FullScreen(bool bShowControl = true);		//全屏

	void ShowIPostListInterface();	//显示IPOD列表界面

	void UpdatePlayStatus(int);	//更新播放状态
	void HidePlayStatus();	//隐藏播放状态

	DECLARE_MSGHANDLER(HandleIpodMsg, IPODActivity);

	int iTimerPlayStatus;	//定时器ID，播放状态

	//int iTotalNumVideo;		//总曲目
	//int iCurrentPlayingVideo;	//当前播放的曲目

	GxxVedioSetup* pVideoSetup;
	GxxAniLable* pLabel_Setting;

	bool bIntial;

	GxxIpodIcon* pPicMusicLogo;

	int iTimerFullScreenMovie;	//视频全屏
	int iTimerRefreshProgress;	//定时器，用于控制多少时间后，允许刷新滚动条
	bool bRefreshProgress;	//标志位，是否允许刷新滚动条

	int ipodPlayStatus;

	GxxPicIcon* pPicPlayStatus;
	GxxPicIcon* pPicPauseStatus;
	GxxPicIcon* pPicStopStatus;

	int iCurrentVideo;
	int iTotalVideo;

	bool bAllRepeat;
	bool bSingleRepeat;

	int running;
};


