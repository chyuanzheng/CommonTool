#pragma once
#include "Activity.h"
#include "GxxAniLable.h"
#include "ControlHelp.h"
#include "DiscDllModule.h"
#include "DVDHardware.h"
#include "GxxString.h"
#include "TccMediaWndEx.h"
#include "GxxProgressBar.h"
#include "GxxControlGroup.h"
#include "GxxPicIcon.h"
#include "GxxVedioSetup.h"

class CE_DISCACTIVITY_API  DiscActivity : public Activity ,protected GxxTimer
{
public:

	enum
	{
		NONE,
		MUSIC,
		MOVIE
	};


	//定时器ID
	int iTimerHideControlId;
	int iTimerCommandFail;
	int iTimerDVDEnable;
	int iTimerPlayPauseStatus;
	int iTimerPlayDVD;

	GxxString strDiscType;
	int iCurrentMediaType;
	void UpdateUI(int iMediaType);

	DVDHardware	dvdControl;
	TccMediaWndEx* pMediaWnd;
	static DiscActivity* pThis;	//保存自身的指针
	

	DiscActivity();
	virtual ~DiscActivity (){}
	virtual  void onCreate();
	virtual void  onResume();
	virtual void onStart();
	virtual void onPause();
	virtual void onStop();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();


	BOOL IsDiscIn();

	
	DECLARE_NOTIFY_CALLBACK(DiscInfoNotify, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(MediaPlayInfoNotify, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(SysmodeNotify, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(LoadDiscNotify, DiscActivity);

	DECLARE_NOTIFY_CALLBACK(FileNameInfoNotify, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(FolderInfoNotify, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(FirstPostionInfoNotify, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(SecondPositionInfoNotify, DiscActivity);

	DECLARE_NOTIFY_CALLBACK(NotifyEject, DiscActivity);	//出碟

	DECLARE_NOTIFY_CALLBACK(NotifyPowerOff, DiscActivity);
	


	DECLARE_NOTIFY_CALLBACK(NotifyCommandFail, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyPlayInfo, DiscActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, DiscActivity);
	
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, DiscActivity);
	

	static void ClickMediaWnd(GxxView *p, void *dwParam);	//视频全屏时，点击视频的处理函数


	void ShowFullControls();	//视频全屏时，显示的控件

	
	void TimerTick( UINT nIDEvent );	//接收定时器消息

	void LessenScreen();	//缩小屏幕
	void FullScreen(bool bShowControl = true);		//全屏

	void StartFullScreenMovieWnd();		//视频窗口，全屏
	void StopFullScreenMovieWnd();		//停止视频窗口
	void ReStartFullScreenMovieWnd();		//重新开始视频窗口全屏

	
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
protected:
	GxxAniLable* pLabel_eject;
	GxxAniLable* pLabel_play_and_pause;
	GxxAniLable* pLabel_stop;
	GxxProgressBar* pProgressVideoTime;
	GxxAniLable* pLabel_totaltime;	//曲目总时间
	GxxAniLable* pLabel_currentTime;	//曲目当前时间

	GxxControlGroup* pControlGroup_main;	//主界面
	GxxControlGroup* pControlGroup_fullScreen;	//视频全屏时的界面

	GxxAniLable* pLabel_SwitchInfoOrMain;
	//GxxControlGroup* pControlGroup_Label;
	GxxControlGroup* pControlGroup_Info;

	GxxControlGroup* pControlGroup_KeyBoard;
	GxxAniLable* pLabel_KeyBoard_close;
	GxxAniLable* pLabel_KeyBoard_up;
	GxxAniLable* pLabel_KeyBoard_left;
	GxxAniLable* pLabel_KeyBoard_right;
	GxxAniLable* pLabel_KeyBoard_down;
	//GxxAniLable* pLabel_KeyBoard_ToleftOrRight;
	GxxAniLable* pLabel_KeyBoard_Toleft;
	GxxAniLable* pLabel_KeyBoard_ToRight;

	GxxAniLable* pLabel_Setting;

	GxxAniLable* pLabel_PrevVideo;
	GxxAniLable* pLabel_NextVideo;

	GxxAniLable* pLabel_Enter;

	GxxAniLable* pLabel_FastForwardText;
	GxxAniLable* pLabel_FastBackwardText;
	GxxAniLable* pLabel_FastForward;
	GxxAniLable* pLabel_FastBackward;
	

	GxxAniLable* pLabel_iconudlr;
	GxxAniLable* pLabel_ReturnMain;
	GxxAniLable* pLabel_Key;

	GxxAniLable* pLabel_SubTitle;
	GxxAniLable* pLabel_Audio;
	GxxAniLable* pLabel_Angle;
	GxxAniLable* pLabel_Repeat;


	GxxAniLable* pLabel_VideoName;
	GxxAniLable* pLabel_TopTitleDiscType;
	GxxPicIcon* pPicMusicLogo;
	GxxPicIcon* pPicPlayStatus;
	GxxPicIcon* pPicPauseStatus;
	GxxPicIcon* pPicStopStatus;


	int iTimerFullScreenMovie;	//视频全屏

	/*GxxAniLable* pLabel_titleDiscType;*/

	GxxAniLable* pLabel_Page1;
	GxxAniLable* pLabel_Page2;

	GxxControlGroup* pControlGroup_page1;
	GxxControlGroup* pControlGroup_page2;
	GxxControlGroup* pControlGroup_FullScreenControls;

	GxxAniLable* pLabelToSetupAudio;
	GxxAniLable* pLabelToSetupDisplay;

	GxxAniLable* pLabel_Menu;
	GxxAniLable* pLabel_TopMenu;

	GxxPicIcon* pPicRepeatIcon;
	GxxPicIcon* pPicRepeatOneIcon;
	GxxPicIcon* pPicRepeatFIcon;
	GxxPicIcon* pPicCommandFail;

	GxxAniLable* pInc_Into_MainInterface;


	bool bIsDVDEnable;
	int	tvSystem;
	
	GxxVedioSetup* pVideoSetup;

	bool bClickPlayPauseLabel;	//记录是否按下了播放暂停键。如果是按下了播放暂停键引起的播放状态，音量缓升
 
	BYTE ucharPlayMode;	//记忆播放状态 

};


