#include "StdAfx.h"
#include "MovieMedia.h"
#include "../PIP/PIP.h"

GxLock MovieMedia::lock;

MovieMedia::~MovieMedia(void)
{
	
	
}

void MovieMedia::CreatePlayMovieThread()
{
	hEventPlayMovie = CreateEvent(NULL,0,0,NULL);

	DWORD dwTheadId;
	CreateThread(NULL, 0, PlayMovieThread,this, 0, &dwTheadId);
}

MovieMedia::MovieMedia(GxxString sMediaExtName, Activity* activity, CHAR* strMediaWndName)
{
	pActivity= NULL;

	this->sMediaExtName = sMediaExtName;
	this->pActivity = activity;

	ePlayMode = PLAYMODE_ALLLLOOP;

	CreatePlayMovieThread();

	if(pActivity)
	{
		pMediaWnd = (TccMediaWndEx*)pActivity->safeFindViewByName(strMediaWndName);

		//设置驾驶中警告语
		GxxAniLable* pLabelWarnning = (GxxAniLable*)pActivity->safeFindViewByName("LabelWarnning");
		pMediaWnd->SetWarning(pLabelWarnning, false);
		

		if(pMediaWnd)
		{
			CRect rcWnd;
			pMediaWnd->getCtrRect(rcWnd);
			MediaControl::SetMediaRect(rcWnd);
			pMediaWnd->setDraw(TRUE);
		}
		
	}
	
}

void MovieMedia::InitMeida()
{
	eMediaMode = MEDIAMODE_MOVIE;
	MediaControl::SetMediaMode(MOVIE);
	MediaControl::SetVMode(1);

	

	if(pMediaWnd)
	{
		CRect rcWnd;
		pMediaWnd->getCtrRect(rcWnd);
		MediaControl::SetMediaRect(rcWnd);
	}

	ResumeThread(hEventPlayMovie);
	
}

void MovieMedia::PlayMedia()
{
	//1.获取播放状态

	int eStatus = MediaControl::GetMoviePlayStatus();

	//1.播放
	if(eStatus == PLAY_STATUS_STOP)
	{
		PlayMediaFile(sLastPlayPath, playtime);
	}
	else if (eStatus == PLAY_STATUS_PAUSE)
	{	
		MediaControl::PlayMovie();	
	}
	
}

void MovieMedia::PlayAndPause()
{	

	//1.获取播放状态

	int eStatus = MediaControl::GetMoviePlayStatus();


	//1.1 暂停状态，则播放
	if (eStatus == PLAY_STATUS_PAUSE)
	{	
		VolumeControl::SlowlyIncreaseVolume();
		Play();
		//eLastPlayStatus = PLAY_STATUS_PLAY;
	}//1.2.播放状态，则暂停
	else if (eStatus == PLAY_STATUS_PLAY)
	{	
		Pause();
		//eLastPlayStatus = PLAY_STATUS_PAUSE;
	}
	eLastPlayStatus = MediaControl::GetMoviePlayStatus();



}

BOOL MovieMedia::PlayMedia(GxxString str, double playtime)
{
	BOOL ret = 0;

	int iRet = GetFileAttributes(str.GetData());
	if ( iRet != -1)
	{

		PlayMovieByThread(str, playtime);
		

		//RETAILMSG(COUT_MSG, (TEXT("playingfile = %s\r\n"),str.GetData()));
		

		//发送曲目名和格式
		fileName = str.Filename().EraseExt();
		fileExt = str.Ext();
		AfxPostMessage(CTR_USB_MOVIE_INFO, (DWORD)&fileName, (DWORD)&fileExt);
	}

	
	

	return ret;
}

void MovieMedia::PlayMovieByThread(GxxString strPlayPath, int iPlayTime)
{
	sLastPlayPath = strPlayPath;
	playtime = iPlayTime;
	SetEvent(hEventPlayMovie);
}

BOOL MovieMedia::PlayMedia(double playtime)
{
	BOOL ret = 0;

	int iRet = GetFileAttributes(sLastPlayPath.GetData());
	if ( iRet != -1)
	{
		
	//	this->playtime = playtime;

		PlayMovieByThread(sLastPlayPath, playtime);
		
	}

	return ret;
}

DWORD MovieMedia::PlayMovieThread(LPVOID lpParam)
{
	MovieMedia* pThis = (MovieMedia*)lpParam;

	while(true)
	{	
		WaitForSingleObject(pThis->hEventPlayMovie,INFINITE);

		lock.Lock();
		//MediaControl::StopMovie();
		BOOL ret = MediaControl::PlayMovieFile(pThis->sLastPlayPath, pThis->playtime);
		RETAILMSG(COUT_MSG, (TEXT("recodeing result = %d\r\n"), ret));
		if(ret == 0)
		{
			
			AfxSendMessage(CTR_USB_MEDIA_RECODE_FAIL, 0, 0);
		}
		
		RETAILMSG(COUT_MSG, (TEXT("playingfile = %s\r\n"), pThis->sLastPlayPath.GetData()));
		lock.UnLock();

	}


	return 0;
}

void MovieMedia::PauseMedia()
{
	int eStatus = MediaControl::GetMoviePlayStatus();

	if (eStatus == PLAY_STATUS_PLAY)
	{	
		MediaControl::PauseMovie();
		eLastPlayStatus = PLAY_STATUS_PLAY;
	}

}

void MovieMedia::StopMedia()
{
	
	MediaControl::StopMovie();
	AfxPostMessage(CTR_USB_MEDIA_STOP, 0, 0);
}

void MovieMedia::Save()
{
	int ePlayStatus = MediaControl::GetMoviePlayStatus();


	//播放状态，则暂停
	if (ePlayStatus == PLAY_STATUS_PLAY)
	{	
		MediaControl::StopMovie();
		eLastPlayStatus = PLAY_STATUS_PAUSE;
	}

	SuspendThread(hEventPlayMovie);

}