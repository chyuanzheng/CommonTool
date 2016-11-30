#pragma once
#include "USBDllModule.h"
#include "Activity.h"
#include "ControlHelp.h"
#include "GxxAniLable.h"
#include "MusicMedia.h"
#include "MovieMedia.h"
#include "PictureMedia.h"
#include "GxxControlGroup.h"

#include "TccMediaWndEx.h"
#include "GXNotify.h"
#include "GxxFileListGroup.h"
#include "TimerManager.h"

#include "GxxMoveText.h"
#include "GxxClickProgressBar.h"

class CE_USBACTIVITY_API  USBActivity : public Activity, public GxxTimer
{
public:
	static USBActivity* pThis;	//保存自身的指针

	Media *media;
	MusicMedia *musicMedia;
	MovieMedia *movieMedia;
	PictureMedia *pictureMedia;

	GxxString strDevicePath;

	wstring strMusicExt;
	wstring strMovieExt;
	wstring strPictureExt;

	FileListGroupInterface* fileList;

	GxxString strPlayTime;

	double dLastPlayTime;

	enum
	{
		MEDIAMODE_BEGINE = -1,
		MEDIAMODE_NONE,
		MEDIAMODE_MUSIC,
		MEDIAMODE_MOVIE,
		MEDIAMODE_PICTURE,
		MEDIAMODE_END
	};

	int eCurrentMediaMode;	//当前的媒体类型


	int elasyMediaMode;


	void SwitchMediaMode(int iMediaMode);	//转换媒体

	void UpdateUI(int iPlayMode);	//更新UI界面

	void UpdateMoive();
	void UpdateMusic();
	void UpdatePicture();
	

	USBActivity();
	virtual ~USBActivity (){}
	virtual  void onCreate();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	
	static Activity* CreateControl();
	virtual void  onResume();
	virtual void onPause();
	virtual void onStop();
	
	static DWORD DeviceChange(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);
	static DWORD MovieTimeHandler(void *pControl, DWORD dwParam, UINT &msg, WPARAM wParam, LPARAM lParam);
	static DWORD MusicTimeHandler(void *pControl, DWORD dwParam, UINT &msg, WPARAM wParam, LPARAM lParam);
	
	static DWORD MusicInfoHandler(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);


	static void ClickMediaWnd(GxxView *p, void *dwParam);	//视频全屏时，点击视频的处理函数

	void ShowFullControls();	//视频全屏时，显示的控件

	DECLARE_NOTIFY_CALLBACK(NotifyPowerOff, USBActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, USBActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyPauseMediaMovie, USBActivity);
	
	

	void TimerTick( UINT nIDEvent );	//接收定时器消息


	bool IsDeviceExist();	//设备是否存在

	void AutoPictureScan();	//图片自动切换
	void StopAutoPictureScan();	//停止图片自动切换
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
private:

	int ePlayMode;

	GxxString sLastPlayPath;
	int iItemPlaying;

	int iTimerShowFullScreenControls;
	int iTimerCheckDevice;
	int iTimerPlayStatus;	//定时器ID，播放状态
	int iTimerFullScreenMovie;	//视频全屏

	int iTimerPictureScan;	//图片自动切换

	bool bIsDeviceExist;


	LPCTSTR GetTimeFormat(int iTime);	//获得一定格式的播放时间


	void KeyPlayAndPause();	//播放
	int KeyNextVideo();	//下一曲
	int KeyPrevVideo();	//上一曲

	void HideUIControl();

	void UpdatePlayStatusUI();	//更新播放状态的UI

	void SubScreen();	//缩小屏幕
	

	void FullMovieScreen();	//全屏
	void FullPictureScreen();	//图片全屏
	void ResetAutoPictureScan();	//重新开始图片自动切换

	void LoadPlayStatus();

	void StartFullScreenMovieWnd();		//视频窗口，全屏
	void StopFullScreenMovieWnd();		//停止视频窗口
	void ReStartFullScreenMovieWnd();		//重新开始视频窗口全屏


	GxxControlGroup* pControlGroup_main;	//主界面
	GxxControlGroup* pControlGroup_info;	//曲目信息
	GxxControlGroup* pControlGroup_fullScreen;	//全屏界面
	GxxControlGroup* pControlGroup_FileList;	//列表界面

	//GxxControlGroup* pControlGroup_infoMusic;

	GxxClickProgressBar* pClickProgressBar;

	GxxAniLable* pLabel_VideoCount;

	GxxAniLable* pLabelPlayPause;
	GxxAniLable* pLabelNext;
	GxxAniLable* pLabelPrev;
	GxxAniLable* pLabelVideoInfo;
	GxxAniLable* pLabel_BrowseList;

	GxxAniLable* pLabel_Conre;
	GxxAniLable* pLabelShre;
	GxxPicIcon*  pPicRandom;
	GxxPicIcon*  pPicLoop;
	GxxPicIcon*  pPicLoop1;
	GxxPicIcon*  pPicLoopF;


	GxxAniLable* pLabel_MovieTime;
	GxxMoveText* pLabel_MovieName;
	GxxMoveText* pLabel_MovieType;
	GxxAniLable* pLabel_Title_Movie;

	GxxAniLable* pLabel_icon_Movie_sicon1;
	GxxAniLable* pLabel_icon_Movie_sicon2;

	//GxxAniLable* pLabel_InfoMusicTime;

	GxxAniLable* pLabel_MusicTime;
	GxxMoveText* pLabel_MusicName;
	GxxAniLable* pLabel_Title_Music;
	GxxMoveText* pLabel_MusicArtist;
	GxxMoveText* pLabel_MusicAlbum;
	GxxPicIcon* pPicIconLogo;

	GxxAniLable* pLabelToSetupAudio;	//设置Audio

	GxxAniLable* pLabel_icon_sicon1;
	GxxAniLable* pLabel_icon_sicon2;
	GxxAniLable* pLabel_icon_sicon3;
	//GxxAniLable* pLabel_icon_sicon4;


	GxxAniLable* pLabel_iconudlr;	//全屏
	GxxAniLable* pLabel_ReturnMain;





	GxxDCContainer* pPictureContainer;
	GxxAniLable* pLabel_Title_Picture;
	GxxAniLable* pLabel_Rotate;



	GxxAniLable* pLabel_SwitchPicutre;
	GxxAniLable* pLabel_SwitchMusic;
	GxxAniLable* pLabel_SwitchMovie;

	GxxAniLable* pInc_Into_MainInterface;	//返回主界面

	GxxPicIcon* pPicPlayStatus;
	GxxPicIcon* pPicPauseStatus;
	GxxPicIcon* pPicStopStatus;
	const char *m_logPath;


	BOOL		comeFromiPod;

};


