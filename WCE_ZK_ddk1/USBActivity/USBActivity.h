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
	static USBActivity* pThis;	//���������ָ��

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

	int eCurrentMediaMode;	//��ǰ��ý������


	int elasyMediaMode;


	void SwitchMediaMode(int iMediaMode);	//ת��ý��

	void UpdateUI(int iPlayMode);	//����UI����

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


	static void ClickMediaWnd(GxxView *p, void *dwParam);	//��Ƶȫ��ʱ�������Ƶ�Ĵ�����

	void ShowFullControls();	//��Ƶȫ��ʱ����ʾ�Ŀؼ�

	DECLARE_NOTIFY_CALLBACK(NotifyPowerOff, USBActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, USBActivity);
	DECLARE_NOTIFY_CALLBACK(NotifyPauseMediaMovie, USBActivity);
	
	

	void TimerTick( UINT nIDEvent );	//���ն�ʱ����Ϣ


	bool IsDeviceExist();	//�豸�Ƿ����

	void AutoPictureScan();	//ͼƬ�Զ��л�
	void StopAutoPictureScan();	//ֹͣͼƬ�Զ��л�
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
private:

	int ePlayMode;

	GxxString sLastPlayPath;
	int iItemPlaying;

	int iTimerShowFullScreenControls;
	int iTimerCheckDevice;
	int iTimerPlayStatus;	//��ʱ��ID������״̬
	int iTimerFullScreenMovie;	//��Ƶȫ��

	int iTimerPictureScan;	//ͼƬ�Զ��л�

	bool bIsDeviceExist;


	LPCTSTR GetTimeFormat(int iTime);	//���һ����ʽ�Ĳ���ʱ��


	void KeyPlayAndPause();	//����
	int KeyNextVideo();	//��һ��
	int KeyPrevVideo();	//��һ��

	void HideUIControl();

	void UpdatePlayStatusUI();	//���²���״̬��UI

	void SubScreen();	//��С��Ļ
	

	void FullMovieScreen();	//ȫ��
	void FullPictureScreen();	//ͼƬȫ��
	void ResetAutoPictureScan();	//���¿�ʼͼƬ�Զ��л�

	void LoadPlayStatus();

	void StartFullScreenMovieWnd();		//��Ƶ���ڣ�ȫ��
	void StopFullScreenMovieWnd();		//ֹͣ��Ƶ����
	void ReStartFullScreenMovieWnd();		//���¿�ʼ��Ƶ����ȫ��


	GxxControlGroup* pControlGroup_main;	//������
	GxxControlGroup* pControlGroup_info;	//��Ŀ��Ϣ
	GxxControlGroup* pControlGroup_fullScreen;	//ȫ������
	GxxControlGroup* pControlGroup_FileList;	//�б����

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

	GxxAniLable* pLabelToSetupAudio;	//����Audio

	GxxAniLable* pLabel_icon_sicon1;
	GxxAniLable* pLabel_icon_sicon2;
	GxxAniLable* pLabel_icon_sicon3;
	//GxxAniLable* pLabel_icon_sicon4;


	GxxAniLable* pLabel_iconudlr;	//ȫ��
	GxxAniLable* pLabel_ReturnMain;





	GxxDCContainer* pPictureContainer;
	GxxAniLable* pLabel_Title_Picture;
	GxxAniLable* pLabel_Rotate;



	GxxAniLable* pLabel_SwitchPicutre;
	GxxAniLable* pLabel_SwitchMusic;
	GxxAniLable* pLabel_SwitchMovie;

	GxxAniLable* pInc_Into_MainInterface;	//����������

	GxxPicIcon* pPicPlayStatus;
	GxxPicIcon* pPicPauseStatus;
	GxxPicIcon* pPicStopStatus;
	const char *m_logPath;


	BOOL		comeFromiPod;

};


