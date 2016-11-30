#include "StdAfx.h"
#include "MusicMedia.h"
#include "../PIP/PIP.h"




MusicMedia::MusicMedia(GxxString sMediaExtName)
{
	this->sMediaExtName = sMediaExtName;

	ePlayMode = PLAYMODE_ALLLLOOP;
}

MusicMedia::~MusicMedia(void)
{
}

void MusicMedia::InitMeida()
{
	eMediaMode = MEDIAMODE_MUSIC;

	MediaControl::SetMediaMode(MUSIC);


}

void MusicMedia::PlayMedia()
{
	//1.»ñÈ¡²¥·Å×´Ì¬

	eLastPlayStatus = MediaControl::GetMusicPlayStatus();


	//1.1 ²¥·Å
	if(eLastPlayStatus == PLAY_STATUS_STOP )
	{
		PlayMediaFile(sLastPlayPath, playtime);
	}
	else if (eLastPlayStatus == PLAY_STATUS_PAUSE)
	{	
		MediaControl::PlayMusic();
	}
	
}
void MusicMedia::PlayAndPause()
{	

	//1.»ñÈ¡²¥·Å×´Ì¬
	eLastPlayStatus = MediaControl::GetMusicPlayStatus();
	
	//1.1 ÔÝÍ£×´Ì¬£¬Ôò²¥·Å
	if(eLastPlayStatus == PLAY_STATUS_STOP)
	{ 
		Play();
		//PlayMediaFile(sLastPlayPath,0);
	}
	else if (eLastPlayStatus == PLAY_STATUS_PAUSE)
	{	
		
		VolumeControl::SlowlyIncreaseVolume();
		Play();
		//MediaControl::PlayMusic();	
	}//1.2.²¥·Å×´Ì¬£¬ÔòÔÝÍ£
	else if (eLastPlayStatus == PLAY_STATUS_PLAY)
	{	
		

		Pause();
		//MediaControl::PauseMusic();
	}	

}

void MusicMedia::PauseMedia()
{
	int ePlayStatus = MediaControl::GetMusicPlayStatus();
	if (ePlayStatus == PLAY_STATUS_PLAY)
	{	
		MediaControl::PauseMusic();
		eLastPlayStatus = PLAY_STATUS_PAUSE;
	}
	
}

void MusicMedia::StopMedia()
{
	MediaControl::StopMusic();
	AfxPostMessage(CTR_USB_MEDIA_STOP, 0, 0);
}

BOOL MusicMedia::PlayMedia(double playtime)
{
	BOOL ret = 0;

	int iRet = GetFileAttributes(sLastPlayPath.GetData());
	if ( iRet != -1)
	{
		//playtime = _playtime;
		ret = MediaControl::PlayMusicFile(sLastPlayPath, playtime);
		RETAILMSG(COUT_MSG, (TEXT("recodeing result = %d\r\n"), ret));
		if(ret == 0)
		{
			AfxSendMessage(CTR_USB_MEDIA_RECODE_FAIL, 0, 0);
		}

		RETAILMSG(COUT_MSG, (TEXT("playingfile = %s\r\n"),sLastPlayPath.GetData()));
	}

	return ret;
}

BOOL MusicMedia::PlayMedia(GxxString str, double playtime/* = 0*/)
{
	BOOL ret = 0;

	int iRet = GetFileAttributes(str.GetData());
	if ( iRet != -1)
	{
		//VolumeControl::SlowlyIncreaseVolume();
		ret = MediaControl::PlayMusicFile(str.GetData(), playtime);
		RETAILMSG(COUT_MSG, (TEXT("recodeing result = %d\r\n"), ret));
		if(ret == 0)
		{
			AfxSendMessage(CTR_USB_MEDIA_RECODE_FAIL, 0, 0);
		}

		RETAILMSG(COUT_MSG, (TEXT("playingfile = %s\r\n"),str.GetData()));
		sLastPlayPath = str;
	}

	return ret;
}

void MusicMedia::Save()
{
	int ePlayStatus = MediaControl::GetMusicPlayStatus();

	//²¥·Å×´Ì¬£¬ÔòÔÝÍ£
	if (ePlayStatus == PLAY_STATUS_PLAY)
	{	
		MediaControl::PauseMusic();
		eLastPlayStatus = PLAY_STATUS_PAUSE;
	}
	
}
