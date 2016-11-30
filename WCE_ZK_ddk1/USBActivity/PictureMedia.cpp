#include "StdAfx.h"
#include "PictureMedia.h"


PictureMedia::PictureMedia(GxxString sMediaExtName)
{
	this->sMediaExtName = sMediaExtName;

	eLastPlayStatus = PLAY_STATUS_PAUSE;

	ePlayMode = PLAYMODE_ALLLLOOP;
	
}

PictureMedia::~PictureMedia(void)
{
	
}

void PictureMedia::InitMeida()
{
	eMediaMode = MEDIAMODE_PICTURE;

	//
}

void PictureMedia::PlayAndPause()
{	


	//1.1 ÔÝÍ£×´Ì¬£¬Ôò²¥·Å
	if (eLastPlayStatus == PLAY_STATUS_PAUSE || eLastPlayStatus == PLAY_STATUS_STOP)
	{	
		AfxPostMessage(CTR_USB_MEDIA_PLAY, 0, 0);
		eLastPlayStatus = PLAY_STATUS_PLAY;
	}//1.2.²¥·Å×´Ì¬£¬ÔòÔÝÍ£
	else if (eLastPlayStatus == PLAY_STATUS_PLAY)
	{	
		AfxPostMessage(CTR_USB_MEDIA_PAUSE, 0, 0);
		eLastPlayStatus = PLAY_STATUS_PAUSE;
	}
	



}

BOOL PictureMedia::PlayMedia(GxxString strPath, double playtime/* = 0*/)
{
	BOOL ret = 0;

	pPictureContainer->SetImage(strPath.GetData());
	sLastPlayPath = strPath;
//	RETAILMSG(COUT_MSG, (TEXT("video path = %s\r\n"),strPath.GetData()));

	return ret;
}


void PictureMedia::Save()
{
	


	//²¥·Å×´Ì¬£¬ÔòÔÝÍ£
	if (eLastPlayStatus == PLAY_STATUS_PLAY)
	{	
		AfxPostMessage(CTR_USB_MEDIA_PAUSE, 0, 0);
		eLastPlayStatus = PLAY_STATUS_PAUSE;
	}

}