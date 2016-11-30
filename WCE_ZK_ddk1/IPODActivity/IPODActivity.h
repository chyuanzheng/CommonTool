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

	static IPODActivity* pThis;	//���������ָ��

	IPOD_SEL_DB_TYPE m_iCurrentMediaMode;	//��ǰ��ý������
	void SwitchUserInterface();	//�л�UI

	void ClearUserInterface();	//��ս���

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

	int iTimerDetectIpod;	//ID��������IPOD��timer��ID
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
	int iTimeVideoDetect;	//���VIDEO�Ķ�ʱ����ID
	int iTimerHideControlId;	//����ȫ��ʱ�Ŀؼ�

	void SubScreen();	//��С��Ļ
	void StartVideoDetect();	//���VIDEO
	void VideoSourceAutoDetect();

	void NextVideo();
	void PrevVideo();
	void PlayAndPause();

	void StartFullScreenMovieWnd();		//��Ƶ���ڣ�ȫ��
	void StopFullScreenMovieWnd();		//ֹͣ��Ƶ����
	void ReStartFullScreenMovieWnd();		//���¿�ʼ��Ƶ����ȫ��

	static void ClickMediaWnd(GxxView *p, void *dwParam);	//��Ƶȫ��ʱ�������Ƶ�Ĵ�����
	void ShowFullControls();
	void FullScreen(bool bShowControl = true);		//ȫ��

	void ShowIPostListInterface();	//��ʾIPOD�б����

	void UpdatePlayStatus(int);	//���²���״̬
	void HidePlayStatus();	//���ز���״̬

	DECLARE_MSGHANDLER(HandleIpodMsg, IPODActivity);

	int iTimerPlayStatus;	//��ʱ��ID������״̬

	//int iTotalNumVideo;		//����Ŀ
	//int iCurrentPlayingVideo;	//��ǰ���ŵ���Ŀ

	GxxVedioSetup* pVideoSetup;
	GxxAniLable* pLabel_Setting;

	bool bIntial;

	GxxIpodIcon* pPicMusicLogo;

	int iTimerFullScreenMovie;	//��Ƶȫ��
	int iTimerRefreshProgress;	//��ʱ�������ڿ��ƶ���ʱ�������ˢ�¹�����
	bool bRefreshProgress;	//��־λ���Ƿ�����ˢ�¹�����

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


