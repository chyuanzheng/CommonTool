#pragma once
#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "USBActivity.h"
#include "../PIP/mediamsg.h"
#include "shellsdk.h"
#include "diskio.h"
#include "param.h"
#include "AVSet.h"
#include "TCCMediaInfo.h"
#include "aygshell.h"
#include "VolumeControl.h"
#include "MsgHandle.h"

#include "WheelMsg.h"
#include "Audio/Audio.h"

#pragma comment(lib, "aygshell.lib")



#define TIMER_HIDE_CONTROLS_ELAPSE 6000 

#define TIMER_DEVICE_DETECT_ELAPSE 3000

#define ELAPSE_PLAY_PAUSE_STATUS 2000

#define ELAPSE_FIVE_SECONDS 5000

USBActivity* USBActivity::pThis = NULL;

USBActivity::USBActivity()
{
	media = NULL;
	musicMedia = NULL;
	movieMedia = NULL;
	pictureMedia = NULL;
	dLastPlayTime = 0;

	pThis = this;	//保存自身的指针

}

Activity* USBActivity::CreateControl()
{
	return new USBActivity;
}

void USBActivity::onCreate()
{
	
	setContentView("layout\\USBPad.xml");
	Activity::onCreate();

	VolumeControl::ApplayForPermission(VolumeModuleId::USB, 0, L"usb");

	pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");
 
	

	pControlGroup_main = (GxxControlGroup* )findViewByName("ControlGroup_main");
	pControlGroup_info = (GxxControlGroup* )findViewByName("ControlGroup_info");
	pControlGroup_fullScreen = (GxxControlGroup* )findViewByName("ControlGroup_fullScreen");
	pControlGroup_FileList = (GxxControlGroup* )findViewByName("ControlGroup_FileList");
	pControlGroup_FileList->setDraw(false);

//	pControlGroup_infoMusic = (GxxControlGroup* )findViewByName("ControlGroup_infoMusic");

	

	pControlGroup_main->setDraw(TRUE);
	pControlGroup_info->setDraw(FALSE);

		
		
	pLabelPlayPause =(GxxAniLable *) safeFindViewByName("button_play_pause");

	pLabelNext = (GxxAniLable *)safeFindViewByName("button_Next");
	pLabelPrev = (GxxAniLable *)safeFindViewByName("button_Prev");

	pLabelVideoInfo = (GxxAniLable *)safeFindViewByName("button_video_info");
	
	pLabel_MusicTime = (GxxAniLable *)safeFindViewByName("Label_MusicTime");
	pLabel_MovieName = (GxxMoveText *)safeFindViewByName("Label_MovieName");

	//pLabel_InfoMusicTime = (GxxAniLable *)safeFindViewByName("Label_InfoMusicTime");
	
	
	
	pLabel_Title_Music = (GxxAniLable *)safeFindViewByName("Label_Title_Music");	
	pLabel_icon_sicon1 = (GxxAniLable *)safeFindViewByName("Label_icon_sicon1");
	pLabel_icon_sicon2 = (GxxAniLable *)safeFindViewByName("Label_icon_sicon2");
	pLabel_icon_sicon3 = (GxxAniLable *)safeFindViewByName("Label_icon_sicon3");
	//pLabel_icon_sicon4 = (GxxAniLable *)safeFindViewByName("Label_icon_sicon4");

	pLabel_VideoCount = (GxxAniLable *)safeFindViewByName("Label_VideoCount");

	pLabel_icon_Movie_sicon1 = (GxxAniLable *)safeFindViewByName("Label_icon_Movie_sicon1");

	pLabel_icon_Movie_sicon2 = (GxxAniLable *)safeFindViewByName("Label_icon_Movie_sicon2");

	pLabel_MusicName = (GxxMoveText *)safeFindViewByName("Label_MusicName");
	pLabel_MusicArtist = (GxxMoveText *)safeFindViewByName("Label_MusicArtist");
	pLabel_MusicAlbum = (GxxMoveText *)safeFindViewByName("Label_MusicAlbum");
	pPicIconLogo = (GxxPicIcon *)safeFindViewByName("PicMusicLogo");
	m_logPath = pPicIconLogo->GetPicPath();

	pLabel_MovieType = (GxxMoveText *)safeFindViewByName("Label_MovieType");
	
	pLabel_MovieTime = (GxxAniLable *)safeFindViewByName("Label_MovieTime");
	pLabel_Title_Movie = (GxxAniLable *)safeFindViewByName("Label_Title_Movie");

	pLabel_iconudlr = (GxxAniLable *)safeFindViewByName("Label_iconudlr");
	pLabel_ReturnMain = (GxxAniLable *)safeFindViewByName("Label_ReturnMain");
	pLabel_BrowseList = (GxxAniLable *)safeFindViewByName("Label_BrowseList");
	pLabel_Conre =  (GxxAniLable *)safeFindViewByName("Label_Conre");
	pLabelShre =  (GxxAniLable *)safeFindViewByName("LabelShre");
	pPicRandom =  (GxxPicIcon *)safeFindViewByName("PicRandom");
	pPicLoop =  (GxxPicIcon *)safeFindViewByName("PicLoop");
	pPicLoop1 =  (GxxPicIcon *)safeFindViewByName("PicLoop1");
	pPicLoopF =  (GxxPicIcon *)safeFindViewByName("PicLoopF");

	pPicPlayStatus = (GxxPicIcon*)safeFindViewByName("PicPlayStatus");
	pPicPauseStatus = (GxxPicIcon*)safeFindViewByName("PicPauseStatus");
	pPicStopStatus = (GxxPicIcon*)safeFindViewByName("PicStopStatus");
	pPicPlayStatus->setDraw(false);
	pPicPauseStatus->setDraw(false);
	pPicStopStatus->setDraw(false);

	fileList = (GxxFileListGroup *)safeFindViewByName("FileList");

	#if _DEBUG
	{
		strDevicePath = L"USB";
		//strDevicePath = L"Storage Card"; 
	} 
	#else
	{
		strDevicePath = L"USB";
	}  
	#endif
	

	strMusicExt = L"mp3_wma_mp2_ogg_aac_flac_ape_wav_ra";
	strMovieExt = L"wmv_avi_mpg_mp4_rmvb_ts_m2ts_tp_mov_vob_mkv_3gp_3ga_asf_trp_flv_rm_mpeg_m4v_m2v";
	strPictureExt = L"jpg_png_bmp";


	fileList->GotoPath(strDevicePath.GetData(), strMusicExt, strMovieExt, strPictureExt);

	pPictureContainer = (GxxDCContainer *)safeFindViewByName("picture_container");
	pLabel_Title_Picture = (GxxAniLable *)safeFindViewByName("Label_Title_Picture");
	pLabel_Rotate = (GxxAniLable *)safeFindViewByName("Label_Rotate");
	pLabel_Rotate->setDraw(false);


	pLabel_SwitchPicutre =  (GxxAniLable *)safeFindViewByName("label_SwitchPicutre");
	pLabel_SwitchMusic =  (GxxAniLable *)safeFindViewByName("label_SwitchMusic");
	pLabel_SwitchMovie =  (GxxAniLable *)safeFindViewByName("label_SwitchMovie");

	pLabelToSetupAudio =   (GxxAniLable *)safeFindViewByName("LabelToSetupAudio");

	pClickProgressBar =   (GxxClickProgressBar *)safeFindViewByName("ClickProgressBar");
	pClickProgressBar->SetMessageView(this);

	//设定列表
	Media::SetFileList(fileList);

	GxxString sMusicExtName = "mp3_wma_mp2_ogg_aac_flac_ape_wav_ra";
	musicMedia = new MusicMedia(sMusicExtName);
	//musicMedia->InitFileList(fileList);
	musicMedia->Init();

	GxxString sMovieExtName = "avi_wmv_mpg_mp4_rmvb_ts_m2ts_tp_mov_vob_mkv_3gp_3ga_asf_divx_trp_flv_rm_mpeg_m4v_m2v";
	movieMedia = new MovieMedia(sMovieExtName, this, "moviewindow");
	movieMedia->Init();
	movieMedia->pMediaWnd->SetFun(ClickMediaWnd, this);

	//TccMediaWndEx* pMediaWnd = (TccMediaWndEx*)safeFindViewByName("moviewindow");
	//pMediaWnd->SetFun(ClickMediaWnd, NULL);

	GxxString sPictureExtName = "jpg_png_bmp_gif";
	pictureMedia = new PictureMedia(sPictureExtName);
	pictureMedia->SetDisplayLable(pPictureContainer);
	pictureMedia->Init();



	SetMsgHandler(WM_MUSICTIME, MusicTimeHandler, (DWORD)this, this);	//音乐时间
	SetMsgHandler(WM_MOVIETIME, MovieTimeHandler, (DWORD)this, this);	//视频时间


	SetMsgHandler(WM_COPYDATA, MusicInfoHandler, (DWORD)this, this);	//音乐信息


	// 注册硬件改变事件
	SetMsgHandler(WM_FILECHANGEINFO, DeviceChange, (DWORD)this, this);

	// 注册文件改变通知
	SHCHANGENOTIFYENTRY schneNotifyEntry;
	schneNotifyEntry.dwEventMask = SHCNE_ALLEVENTS;//监视所有事件
	schneNotifyEntry.pszWatchDir = NULL;//要监视的目录名,NULL表示所有
	schneNotifyEntry.fRecursive = TRUE;//监视目录时，是否递归
	SHChangeNotifyRegister(AfxGetHWND(), &schneNotifyEntry);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = NotifyPowerOff;
	GXNotify::RegisterNotifyHandler("power_off", notify);

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);

	notify.funNotify = NotifyPauseMediaMovie;
	GXNotify::RegisterNotifyHandler("NotifyPauseMediaMovie", notify);
	

	iTimerShowFullScreenControls = RegisterTimer(TIMER_HIDE_CONTROLS_ELAPSE);

	iTimerFullScreenMovie = RegisterTimer(ELAPSE_FIVE_SECONDS);

	bIsDeviceExist = true;
	iTimerCheckDevice =  RegisterTimer(TIMER_DEVICE_DETECT_ELAPSE);

	iTimerPictureScan =  RegisterTimer(ELAPSE_FIVE_SECONDS);
	
	StartTimer(iTimerCheckDevice);

	iTimerPlayStatus	= RegisterTimer(ELAPSE_PLAY_PAUSE_STATUS);	//显示播放暂时的状态
	

	LoadPlayStatus();

	//读取上一次关机的播放状态
	if(elasyMediaMode > MEDIAMODE_BEGINE && elasyMediaMode < MEDIAMODE_END )
	{
		//elasyMediaMode = sysConfig.sysParam.curUSBMediaMode;
		switch(elasyMediaMode)
		{
		case MEDIAMODE_MUSIC:
			{
				musicMedia->SetLastPlayPath(sLastPlayPath);
				musicMedia->SetItemPlaying(iItemPlaying);
				musicMedia->SetPlayTime(dLastPlayTime);
			}
			break;
		case MEDIAMODE_MOVIE:
			{
				movieMedia->SetLastPlayPath(sLastPlayPath);
				movieMedia->SetItemPlaying(iItemPlaying);
				movieMedia->SetPlayTime(dLastPlayTime);
			}
			break;
		case MEDIAMODE_PICTURE:
			{
				pictureMedia->SetLastPlayPath(sLastPlayPath);
				pictureMedia->SetItemPlaying(iItemPlaying);
			}
			break;		
		}
	}
	else
	{
		elasyMediaMode = MEDIAMODE_NONE;
	}

	eCurrentMediaMode= MEDIAMODE_NONE;
	
	comeFromiPod = 0;
}

bool USBActivity::IsDeviceExist()
{
	GxxString strTempDevicePath = L"\\";
	strTempDevicePath +=  strDevicePath;
	if(GetFileAttributes(strTempDevicePath) == -1)
	{
		return false;
	}
	return true;
}


DWORD USBActivity::DeviceChange(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{
	USBActivity *pUSBActivity = (USBActivity *)pControl;
	/*if( Activity::GetActiveActiviy() != pUSBActivity)
	{
		return 0;
	}*/

	FILECHANGENOTIFY *pFcn = (FILECHANGENOTIFY*)lParam;
	if (pFcn->fci.wEventId == SHCNE_DELETE)		//取出设备
	{
		GxxString sPath = (TCHAR*)pFcn->fci.dwItem1;
		if(sPath == pUSBActivity->strDevicePath)
		{
			pUSBActivity->media->StopVideo();
			//媒体为无
			pUSBActivity->eCurrentMediaMode = MEDIAMODE_NONE;

			if( Activity::GetActiveActiviy() == pUSBActivity)
			{
				startActivity(NULL,"MainPad");
			} 
		}
	}
	if (pFcn->fci.wEventId == SHCNE_MEDIAINSERTED)	//插入设备
	{
		
		GxxString sPath = (TCHAR*)pFcn->fci.dwItem1;

		GxxString strTempDevicePath;

		strTempDevicePath = L"\\";
		strTempDevicePath += pUSBActivity->strDevicePath;
		
		sPath.MakeLower();
		strTempDevicePath.MakeLower();
		if(sPath == strTempDevicePath)
		{
			pUSBActivity->fileList->GotoPath(pUSBActivity->strDevicePath.GetData(), pUSBActivity->strMusicExt, 
				pUSBActivity->strMovieExt, pUSBActivity->strPictureExt);
			if( Activity::GetActiveActiviy() == pUSBActivity)
			{
				pUSBActivity->media->Resume();

			}
			
			startActivity(NULL,"USBActivity");

		}
		

	}
	return 0;

}


//视频全屏时，点击视频的响应函数
void USBActivity::ClickMediaWnd(GxxView *p, void *dwParam)
{
	USBActivity* pThis = (USBActivity*)dwParam;
	if(pThis->movieMedia->pMediaWnd->IsFullScreen())
	{
		//pThis->ShowFullControls();
		pThis->SubScreen();

		pThis->ReStartFullScreenMovieWnd();		//重新开始视频窗口全屏

	}
	else
	{
		pThis->FullMovieScreen();
	}

	
}


LPCTSTR USBActivity::GetTimeFormat(int iTime)
{

	//static char szPlaytime[MAX_PATH] = {0};

	int hour = iTime/3600;
	int min = (iTime-3600*hour)/60;
	int sec = iTime-hour*3600-min*60;
	
	if (hour)
	{
		strPlayTime.Format(_T("%d:%02d\'%02d\""), hour, min, sec);
		//RETAILMSG(COUT_MSG, (TEXT("strPlayTime = %s\r\n"), strPlayTime.GetData()));
	}
	else
	{
		strPlayTime.Format(_T("%02d\'%02d\""), min, sec);
		//RETAILMSG(COUT_MSG, (TEXT("strPlayTime = %s\r\n"), strPlayTime.GetData()));
	}


	return strPlayTime.GetData();
}

DWORD USBActivity::MusicTimeHandler(void *pControl, DWORD dwParam, UINT &msg, WPARAM wParam, LPARAM lParam)
{
	USBActivity *pUSBActivity = (USBActivity *)pControl;
	if(pUSBActivity->eCurrentMediaMode != MEDIAMODE_MUSIC)
	{
		return 0;
	}
	if (wParam != 0)
	{
		if (wParam == pUSBActivity->media->dLastPlayTime)
		{
			return 0;
		}
		pUSBActivity->media->dLastPlayTime = wParam;
		pUSBActivity->media->dTotalPlayTime = lParam;

		//设置滚动条
		pUSBActivity->pClickProgressBar->SetRange(0,lParam);
		pUSBActivity->pClickProgressBar->SetDisplayPos(wParam);

		LPCTSTR wstrPlaytime;
		wstrPlaytime = pUSBActivity->GetTimeFormat(pUSBActivity->media->dLastPlayTime);
		pUSBActivity->pLabel_MusicTime->SetText(wstrPlaytime, true);		

	}

	if (wParam == lParam && wParam != 0)
	{
		// 放完一首歌,根据播放循环模式决定下一首
		if(pUSBActivity->media->GetPlayMode() == Media::PLAYMODE_SINGLELOOP)	//单曲循环时，始终播放
		{
			pUSBActivity->media->PlayMedia(0);
		}
		else
		{
			pUSBActivity->media->NextVideo();	//下一曲
		}
	}
	
	return 0;
}

DWORD USBActivity::MovieTimeHandler(void *pControl, DWORD dwParam, UINT &msg, WPARAM wParam, LPARAM lParam)
{
	USBActivity *pUSBActivity = (USBActivity *)pControl;
	if(pUSBActivity->eCurrentMediaMode != MEDIAMODE_MOVIE)
	{
		return 0;
	}

	if (wParam != 0)
	{
		if (wParam == pUSBActivity->media->dLastPlayTime)
		{
			return 0;
		}
		pUSBActivity->media->dLastPlayTime = wParam;
		pUSBActivity->media->dTotalPlayTime = lParam;
		
		//设置滚动条
		pUSBActivity->pClickProgressBar->SetRange(0,lParam);
		pUSBActivity->pClickProgressBar->SetDisplayPos(wParam);


		LPCTSTR wstrPlaytime;
		wstrPlaytime = pUSBActivity->GetTimeFormat(pUSBActivity->media->dLastPlayTime);
		pUSBActivity->pLabel_MovieTime->SetText(wstrPlaytime, true);

	}


	if (wParam == lParam && wParam != 0)
	{
		// 放完一首歌,根据播放循环模式决定下一首
		if(pUSBActivity->media->GetPlayMode() == Media::PLAYMODE_SINGLELOOP)	//单曲循环时，始终播放
		{
			pUSBActivity->media->PlayMedia(0);
		}
		else
		{
			pUSBActivity->media->NextVideo();	//下一曲
		}
		
	}
	
	return 0;
}


DWORD USBActivity::MusicInfoHandler(void *pControl, DWORD dwParam, UINT &msg, WPARAM wParam, LPARAM lParam)
{
	USBActivity *pUSBActivity = (USBActivity *)pControl;
	/*if( Activity::GetActiveActiviy() != pUSBActivity)
	{
		return 0;
	}*/

	if (wParam == WM_MUSICINFO)
	{
		COPYDATASTRUCT *pCS = (COPYDATASTRUCT*)lParam;
		TCCMediaInfo *pMediaInfo = (TCCMediaInfo *)pCS->lpData;
		GxxString strTitle = pMediaInfo->tagInfo.SongTitle;
		GxxString strArtist = pMediaInfo->tagInfo.Artist;
		GxxString strAlbum = pMediaInfo->tagInfo.Album;

	//	char szTitle[255] ={0};
	//	strTitle.ToUTF8(szTitle);
		
		pUSBActivity->pLabel_MusicName->setText(strTitle.GetData()); 
		pUSBActivity->pLabel_MusicArtist->setText(strArtist.GetData()); 
		pUSBActivity->pLabel_MusicAlbum->setText(strAlbum.GetData()); 

		//如果曲目名为空，显示文件名
		if(pUSBActivity->pLabel_MusicName->getText() == L"")
		{
			FileItem *pItem = new FileItem();
			pUSBActivity->fileList->GetMediaItemInAll(pUSBActivity->media->iItemPlaying, pUSBActivity->media->efileType, *pItem);
			pUSBActivity->pLabel_MusicName->setText(pItem->fileName);
		}
		AfxInvalidateRect(NULL);
	}

	if (wParam == WM_MUSICALBUM)
	{
		COPYDATASTRUCT *pCS = (COPYDATASTRUCT*)lParam;

		if (pCS->cbData && pUSBActivity->pPicIconLogo->SetPicPath((TCHAR*)pCS->lpData) )
		{
			RETAILMSG(COUT_MSG, (TEXT("Exist CALBUM PIC\r\n")));
		}
		else
		{
			pUSBActivity->pPicIconLogo->SetPicPath(pUSBActivity->m_logPath);
			RETAILMSG(COUT_MSG, (TEXT("no CALBUM PIC\r\n")));

		}
		pUSBActivity->pPicIconLogo->invalidateRect();
	}
	
	return 0;
}

int USBActivity::KeyNextVideo()	//下一曲
{
	media->NextVideo();
	return 1;
}

int USBActivity::KeyPrevVideo()	//上一曲
{

	return media->PrevVideo();
}

 

BOOL USBActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	/*case MCU_POPMENU:
		{
			if( Activity::GetActiveActiviy() == this)
			{
				SubScreen();
			} 
			return TRUE;
		}
		break;*/
	case CTR_USB_MOVIE_INFO:
		{
			GxxString* fileName = (GxxString*)wParam;
			GxxString* fileExt = (GxxString*)lParam;
			RETAILMSG(COUT_MSG, (TEXT("fileName = %s, fileExt = %s \r\n"), 
				fileName->GetData(), fileExt->GetData()));

			pLabel_MovieName->setText(fileName->GetData());
			pLabel_MovieType->setText(fileExt->GetData());

			AfxInvalidateRect(NULL);
			return TRUE;
		}
		break;
	case CTR_USB_MEDIA_RECODE_FAIL:
		{
			//提示曲目播放失败
			RECT rc;
			::SetRect(&rc,220,15,620,55);
			AfxMessageBox("ID_VIDEO_RECODE_FAIL",3,&rc);

			//停止播放
			media->StopMedia();
			return TRUE;
		}
		break;
	case CTR_USB_MEDIA_VIDEO_CHANG:
		{
			int iPlayingVideo = wParam + 1;
			FileItem::EnumFileType eFileType = media->GetFileTypeByMediaMode(lParam);
			int iTotalVideo;
			fileList->GetTotalMediaCountInAll(eFileType, iTotalVideo);
			GxxString str;
			str.Format(L"%04d/%04d", iPlayingVideo, iTotalVideo);
			
			pLabel_VideoCount->SetText(str.GetData(), true);

			return TRUE;
		}
		break;
	case CTR_USB_MEDIA_PLAY:
		{
			if(media->eMediaMode == MEDIAMODE_PICTURE)	
			{
				AutoPictureScan();	//预读
			}
			pPicPlayStatus->setDraw(true);
			pPicPauseStatus->setDraw(false);
			pPicStopStatus->setDraw(false);
			StopTimer(iTimerPlayStatus);
			StartTimer(iTimerPlayStatus);
			AfxInvalidateRect(NULL);
			return TRUE;
		}
		break;
	case CTR_USB_MEDIA_PAUSE:
		{
			if(media->eMediaMode == MEDIAMODE_PICTURE)	
			{
				StopAutoPictureScan();	//停止图片自动切换
			}

			pPicPlayStatus->setDraw(false);
			pPicPauseStatus->setDraw(true);
			pPicStopStatus->setDraw(false);
			StopTimer(iTimerPlayStatus);
		//	StartTimer(iTimerPlayStatus);
			AfxInvalidateRect(NULL);
			return TRUE;
		}
		break;
	case CTR_USB_MEDIA_STOP:
		{
			

			if(eCurrentMediaMode == MEDIAMODE_MOVIE && movieMedia->pMediaWnd->IsFullScreen())	//缩小屏幕
			{
				SubScreen();
			}
			else if(eCurrentMediaMode == MEDIAMODE_MUSIC)
			{
				pLabel_MusicName->setTextFromId("ID_Track");
				pLabel_MusicArtist->setTextFromId("ID_Artist");
				pLabel_MusicAlbum->setTextFromId("ID_Album");
				pLabel_MusicTime->SetText("00\'00\"",true);
			}

			pPicPlayStatus->setDraw(false);
			pPicPauseStatus->setDraw(false);
			pPicStopStatus->setDraw(true);
			AfxInvalidateRect(NULL);
			StopTimer(iTimerPlayStatus);
			//StartTimer(iTimerPlayStatus);
			return true;
		}
		break;
	case CTR_LISTBOX_FILEITEM:	//从浏览界面点击曲目，返回
		{

			//修改当前的播放曲目
			int iItemId = lParam;
			media->iItemPlaying = iItemId;

			FileItem *item = (FileItem *)wParam;


			FileItem::EnumFileType efileType = item->fileType;
			switch(efileType)
			{
			case FileItem::FILE_TYPE_NULL:
			case FileItem::FILE_TYPE_MUSIC:
				{
					ePlayMode = MEDIAMODE_MUSIC;
					musicMedia->SetItemPlaying(iItemId);
				}
				break; 
			case FileItem::FILE_TYPE_MOVIE:
				{
					ePlayMode = MEDIAMODE_MOVIE;
					movieMedia->pMediaWnd->setDraw(true);
					movieMedia->SetItemPlaying(iItemId);
				}
				break;
			case FileItem::FILE_TYPE_PICTURE:
				{
					ePlayMode = MEDIAMODE_PICTURE;
					pPictureContainer->setDraw(true);
					pictureMedia->SetItemPlaying(iItemId);
				}
				break;

			}
			if(eCurrentMediaMode != ePlayMode)
			{
				SwitchMediaMode(ePlayMode);
			}
			

			
			wstring wsVideoPath = item->filePath;
			media->PlayMediaFile(wsVideoPath.c_str(),0);
			pControlGroup_main->setDraw(true);

			if(pControlGroup_FileList->getDraw())
			{
				pControlGroup_FileList->setDraw(false);
			}
			AfxInvalidateRect(&m_ActRect);
			

		}
		return TRUE;
	case CTR_LISTBOX_X:
		{
			pControlGroup_FileList->setDraw(false);
			pControlGroup_main->setDraw(true);
			if(ePlayMode == MEDIAMODE_MOVIE)
			{
				if(!movieMedia->pMediaWnd->getDraw())
				{
					movieMedia->pMediaWnd->setDraw(true);
				}
				
			}
			if(ePlayMode == MEDIAMODE_PICTURE)
			{
				if(!pPictureContainer->getDraw())
				{
					pPictureContainer->setDraw(true);
				}

			}
			AfxInvalidateRect(&m_ActRect);

			//关闭浏览界面后，播放
			media->Play();

			return true;
		}
	case CTR_MESSAGE:
		if ((GxxClickProgressBar *)wParam == pClickProgressBar)	
		{
			RETAILMSG(COUT_MSG, (L"probar pos = %d\r\n", lParam));
			media->PlayMedia(lParam);
			return TRUE;
		}
		if (MES_LBUTTONUP==lParam)
		{
			
			
			if ((GxxAniLable *)wParam == pLabel_Rotate)	
			{
				pPictureContainer->Rotate();
				return TRUE;
			}
			if ((GxxDCContainer *)wParam == pPictureContainer)	
			{
				if (!pPictureContainer->getFullScreen())	//全屏
				{
					FullPictureScreen();
					AfxInvalidateRect(NULL);
				}
				else
				{
					SubScreen();

					//ReStartFullScreenMovieWnd();		//重新开始视频窗口全屏
				}
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pInc_Into_MainInterface)	
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0); 
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelPlayPause)	//播放暂停
			{
				KeyPlayAndPause();			
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SwitchPicutre)	//转换为图片模式
			{
				if(eCurrentMediaMode != MEDIAMODE_PICTURE)
					SwitchMediaMode(MEDIAMODE_PICTURE);		
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SwitchMusic)	//转换为音乐模式
			{

				if(eCurrentMediaMode != MEDIAMODE_MUSIC)
					SwitchMediaMode(MEDIAMODE_MUSIC);			
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SwitchMovie)	//转换为视频模式
			{
				if(eCurrentMediaMode != MEDIAMODE_MOVIE)
					SwitchMediaMode(MEDIAMODE_MOVIE);			
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_BrowseList)	//浏览菜单
			{	
				movieMedia->pMediaWnd->setDraw(false);
				pControlGroup_FileList->setDraw(true);
				pPictureContainer->setDraw(false);
				if(pControlGroup_main->getDraw())
				{
					pControlGroup_main->setDraw(false);
				}
				if(pControlGroup_info->getDraw())
				{
					pControlGroup_info->setDraw(false);
				}
				if(pControlGroup_fullScreen->getDraw())
				{
					pControlGroup_info->setDraw(false);
				}
				AfxInvalidateRect(&m_ActRect);
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pLabelShre)	//随机
			{
				if(media)
				{
					media->SetShuffle();

					UpdatePlayStatusUI();

				}
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Conre)	//循环
			{
				if(media)
				{
					media->SetCore();

					UpdatePlayStatusUI();
					
				}
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pLabelNext)	//下一曲
			{
				KeyNextVideo();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelPrev)	//上一曲
			{
				KeyPrevVideo();
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelVideoInfo)	//主界面与曲目信息界面的切换
			{
				
				if(pControlGroup_main->getDraw() && !pControlGroup_info->getDraw())
				{
					//显示信息界面，隐藏主界面
					pControlGroup_main->setDraw(FALSE);
					pControlGroup_info->setDraw(TRUE);

					overridePendingTransition(pControlGroup_info,pControlGroup_main,Activity::s_hAniRotateY);

				}
				else if(!pControlGroup_main->getDraw() && pControlGroup_info->getDraw())
				{
					//显示主界面，隐藏信息界面
					pControlGroup_main->setDraw(TRUE);
					pControlGroup_info->setDraw(FALSE);

					overridePendingTransition(pControlGroup_info,pControlGroup_main,Activity::s_hAniRotateY);

				}
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_iconudlr)	//全屏
			{
				if(eCurrentMediaMode == MEDIAMODE_MOVIE)
				{
					FullMovieScreen();
				}
				if(eCurrentMediaMode == MEDIAMODE_PICTURE)
				{
					FullPictureScreen();
					AfxInvalidateRect(NULL);
				}
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_ReturnMain)	//缩小屏幕
			{
				SubScreen();

				ReStartFullScreenMovieWnd();		//重新开始视频窗口全屏
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelToSetupAudio)
			{
				Activity::startActivity(this,"SetupActivity","2_sound_setup");
				return true;
			}
			
			
		}
		if((GxxDCContainer *)wParam == pPictureContainer)
		{
			if(eCurrentMediaMode == MEDIAMODE_PICTURE)
			{
				if(media->eLastPlayStatus == PLAY_STATUS_PLAY)
				{
					ResetAutoPictureScan();	//重新开始图片播放
				}

			}
			return TRUE;
		}
		return FALSE;
	default:
		return FALSE;
	}
}

void USBActivity::UpdatePlayStatusUI()
{
	pPicLoop->setDraw(false);
	pPicLoop1->setDraw(false);
	pPicLoopF->setDraw(false);
	int iPlayMode = media->GetPlayMode();
	switch(iPlayMode)
	{
	/*case Media::PLAYMODE_ALL:
		{
			pPicLoop->setDraw(false);
		}
		break;*/
	case Media::PLAYMODE_ALLLLOOP:
		{
			pPicLoopF->setDraw(true);
		}
		break;
	case Media::PLAYMODE_SINGLELOOP:
		{
			pPicLoop1->setDraw(true);
		}
		break;

	}
	CRect rc;
	pPicLoop->getCtrRect(rc);
	AfxInvalidateRect(&rc);

	int iRandomMode = media->GetRandomMode();
	if(iRandomMode == Media::RANDOMMODE_NO)
	{
		pPicRandom->setDraw(false);
	}
	else if(iRandomMode == Media::RANDOMMODE_YES)
	{
		pPicRandom->setDraw(true);
	}	rc;
	pPicRandom->getCtrRect(rc);
	AfxInvalidateRect(&rc);


}


void USBActivity::KeyPlayAndPause()
{	
	if(media)
	{
		
		media->PlayAndPause();
	}
	
}


void USBActivity::SwitchMediaMode(int iMediaMode)
{
	if(eCurrentMediaMode == iMediaMode)
	{
		ASSERT(media != NULL);
		if(media)
		{
			media->InitMeida();
			if (comeFromiPod)
			{
				waveOutSetVolume(0,0);
			}
			media->Play();
			if (comeFromiPod)
			{
				Sleep(200);
				comeFromiPod = 0;
				waveOutSetVolume(0,0xFFFFFFFFF);
			}
		}
		
		return;
	}

	if(eCurrentMediaMode != MEDIAMODE_NONE && eCurrentMediaMode != iMediaMode)
	{
		media->Save();
	}

	switch(iMediaMode)
	{
	case MEDIAMODE_NONE:
		{

		}
		break;
	case MEDIAMODE_MUSIC:
		{
			ePlayMode = MEDIAMODE_MUSIC;
			media = musicMedia;

		}
		break;
	case MEDIAMODE_MOVIE:
		{
			ePlayMode = MEDIAMODE_MOVIE;
			media = movieMedia;

		}
		break;
	case MEDIAMODE_PICTURE:
		{
			ePlayMode = MEDIAMODE_PICTURE;
			media = pictureMedia;
			
		}
		break;
	}
	
	UpdateUI(iMediaMode);

	
	if(media)
	{
		media->Resume();
	}

	ASSERT(media!=NULL);
	
	
	
	eCurrentMediaMode = iMediaMode;
	
}

void USBActivity::onStop()
{
	//保存播放时间
	media->playtime = media->GetPlayTime();

	media->StopMedia();
}

void  USBActivity::onResume()
{

	//切换到当前声道
	if (Audio::GetCH() == Audio::AUDIO_IPOD)
	{
		comeFromiPod = 1;
	}
	AVSET::ToMedia();
	//设定音量
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::USB);

	//int eMediaMode;// = eCurrentMediaMode;

	if(elasyMediaMode == MEDIAMODE_NONE)
	{
		elasyMediaMode = MEDIAMODE_MUSIC;
	}

	if(elasyMediaMode != MEDIAMODE_MOVIE)
	{
		AVSET::CloseAuxOutput();
	}

	//切换媒体
	SwitchMediaMode(elasyMediaMode);

	//全屏时，缩小屏幕
	if(movieMedia->pMediaWnd->IsFullScreen() && !pControlGroup_main->getDraw())
	{
		SubScreen();
	}

	
	StartFullScreenMovieWnd();	//视频窗口，全屏
}

void USBActivity::StartFullScreenMovieWnd()		//视频窗口，全屏
{
	StartTimer(iTimerFullScreenMovie);
}

void USBActivity::StopFullScreenMovieWnd()		//停止视频窗口
{
	StopTimer(iTimerFullScreenMovie);
}

void USBActivity::onPause()
{
	AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);

	StopFullScreenMovieWnd();

	elasyMediaMode = eCurrentMediaMode;

	StopAutoPictureScan();	//停止图片自动切换

	/*if(eCurrentMediaMode == MEDIAMODE_MOVIE)
	{
		media->PauseMedia();
	}*/
	
}


void USBActivity::HideUIControl()
{

	//音乐
	pLabel_MusicName->setDraw(false);
	pLabel_MusicTime->setDraw(false);
//	pControlGroup_infoMusic->setDraw(false);
	//pLabel_VideoCount->setDraw(false);

	pLabel_Title_Music->setDraw(false);

	pLabel_icon_sicon1->setDraw(false);
	pLabel_icon_sicon2->setDraw(false);
	pLabel_icon_sicon3->setDraw(false);
	//pLabel_icon_sicon4->setDraw(false);

	pLabel_MusicAlbum->setDraw(false);
	pLabel_MusicArtist->setDraw(false); 
	pPicIconLogo->setDraw(false);

	//视频
	pLabel_Title_Movie->setDraw(false);
	pLabel_MovieTime->setDraw(false);
	movieMedia->pMediaWnd->setDraw(false);

	pLabel_MovieName->setDraw(false);
	pLabel_MovieType->setDraw(false);

	pLabel_icon_Movie_sicon1->setDraw(false);
	pLabel_icon_Movie_sicon2->setDraw(false);

	//图片
	pPictureContainer->setDraw(false);
	pLabel_Title_Picture->setDraw(false);
	pLabel_Rotate->setDraw(false);


	
}


void USBActivity::UpdateUI(int iPlayMode)
{
	//CRect rect;
	
	HideUIControl();

	
	
	switch(iPlayMode)
	{
	case MEDIAMODE_NONE:
		{
			
		}
	case MEDIAMODE_MUSIC:
		{
			UpdateMusic();
		}
		break;
	case MEDIAMODE_MOVIE:
		{
			UpdateMoive();
			
		}
		break;
	case MEDIAMODE_PICTURE:
		{
			UpdatePicture();
		}
		break;
	}

	UpdatePlayStatusUI();

	AfxInvalidateRect(NULL);
}



void USBActivity::SubScreen()	//缩小屏幕
{
	AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);

	pControlGroup_fullScreen->setDraw(false);

	if(!pControlGroup_info->getDraw())
	{
		pControlGroup_main->setDraw(true);
	}
	
	pControlGroup_FileList->setDraw(false);

	if(eCurrentMediaMode == MEDIAMODE_MOVIE)
	{
		if(movieMedia->pMediaWnd->IsFullScreen())
		{
			movieMedia->pMediaWnd->ReductionScreen();
		}
	}
	else if(eCurrentMediaMode == MEDIAMODE_PICTURE)
	{
		pPictureContainer->SetFullScreen(false);
	}
	
	AfxInvalidateRect(NULL);
}


void USBActivity::FullMovieScreen()	//全屏
{
	
	AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);

	pControlGroup_main->setDraw(FALSE);
	movieMedia->pMediaWnd->SetFullScreen();
	//ShowFullControls();
	AfxInvalidateRect(NULL);
	
}

void USBActivity::FullPictureScreen()	//图片全屏
{
	bool ret = pPictureContainer->SetFullScreen(true);
	if(ret)
	{
		AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);
		pControlGroup_main->setDraw(false);
	}
}





void USBActivity::UpdateMoive()
{
	

	CRect rcWnd;
	movieMedia->pMediaWnd->getCtrRect(rcWnd);
	MediaControl::SetMediaRect(rcWnd);

	movieMedia->pMediaWnd->setDraw(true);
	pLabel_Title_Movie->setDraw(true);


	//显示曲目当前时间
	LPCTSTR wstrPlaytime;
	wstrPlaytime = GetTimeFormat(media->dLastPlayTime);
	pLabel_MovieTime->SetText(wstrPlaytime, true);

	pLabel_MovieTime->setDraw(true);

	pLabel_MovieName->setDraw(true);

	pLabelPlayPause->setDraw(true);

	pLabel_Conre->setDraw(true);
	pLabel_Conre->setEnable(true);
	pLabelShre->setEnable(true);
	

	pClickProgressBar->setDraw(true);

	pLabelToSetupAudio->setEnable(true);

	pLabelPlayPause->setDraw(true);

	pLabel_MovieType->setDraw(true);

	pLabel_icon_Movie_sicon1->setDraw(true);
	pLabel_icon_Movie_sicon2->setDraw(true);

	pLabel_iconudlr->setEnable(true);


}

void USBActivity::UpdateMusic()
{
	//LPCTSTR wstrPlaytime;

	pLabel_MusicName->setDraw(true);
	pLabel_MusicTime->setDraw(true);
	pLabel_Title_Music->setDraw(true);
	pLabel_icon_sicon1->setDraw(true);
	pLabel_icon_sicon2->setDraw(true);
	pLabel_icon_sicon3->setDraw(true);


	//pLabel_icon_sicon4->setDraw(true);

	pLabel_MusicAlbum->setDraw(true);
	pLabel_MusicArtist->setDraw(true);
	pPicIconLogo->setDraw(true);

	pLabelPlayPause->setDraw(true);

	pLabel_Conre->setDraw(true);
	pLabel_Conre->setEnable(true);
	pLabelShre->setEnable(true);

	pClickProgressBar->setDraw(true);

	//显示曲目当前时间
	LPCTSTR wstrPlaytime;
	wstrPlaytime = GetTimeFormat(media->dLastPlayTime);
	pLabel_MusicTime->SetText(wstrPlaytime, true);

	pLabelToSetupAudio->setEnable(true);

	pLabel_iconudlr->setEnable(false);

}


void USBActivity::UpdatePicture()
{
	pPictureContainer->setDraw(true);
	pLabel_Title_Picture->setDraw(true);

	pLabel_Conre->setDraw(false);
	pLabelShre->setDraw(true);
	pLabel_Rotate->setDraw(true);

	//用不到的控件，设定为无用。
	pLabelShre->setEnable(false);
	pLabelToSetupAudio->setEnable(false);
	//pLabel_Conre->setEnable(false);

	pClickProgressBar->setDraw(false);

	pLabel_iconudlr->setEnable(true);


}

//显示全屏时的控件
void USBActivity::ShowFullControls()
{
	

	if(!pControlGroup_fullScreen->getDraw())
	{
		pControlGroup_fullScreen->setDraw(TRUE);
		

	}
	
	AfxInvalidateRect(&(pThis->m_ActRect));
	

	StartTimer(iTimerShowFullScreenControls);

}

void USBActivity::TimerTick( UINT nIDEvent )	//接收定时器消息
{
	if(nIDEvent == iTimerShowFullScreenControls)
	{
		StopTimer(nIDEvent);
		if(pControlGroup_fullScreen->getDraw())
		{
			pControlGroup_fullScreen->setDraw(FALSE);

		}
		AfxInvalidateRect(NULL);
	}
	else if(nIDEvent == iTimerCheckDevice)
	{
		if(IsDeviceExist() != bIsDeviceExist)
		{
			bIsDeviceExist = IsDeviceExist();

			Activity::EnableActivity("USBActivity",bIsDeviceExist);
		}
		
	}
	else if(nIDEvent == iTimerPlayStatus)
	{
		StopTimer(iTimerPlayStatus);
		pPicPlayStatus->setDraw(false);
		pPicPauseStatus->setDraw(false);
		pPicStopStatus->setDraw(false);
		AfxInvalidateRect(NULL);

	}
	else if(nIDEvent == iTimerFullScreenMovie)
	{
		if(
			eCurrentMediaMode == MEDIAMODE_MOVIE 
			&& !(movieMedia->pMediaWnd->IsFullScreen()) 
			&& !pControlGroup_FileList->getDraw()
			&& (MediaControl::GetMoviePlayStatus() !=  PLAY_STATUS_STOP)
			&&movieMedia->pMediaWnd->GetIsBrake()
			)
		{
			FullMovieScreen();

			
			ReStartFullScreenMovieWnd();	//重新开始视频播放
		}
		

	}
	else if(nIDEvent == iTimerPictureScan)
	{
		if(eCurrentMediaMode == MEDIAMODE_PICTURE)	//自动播放下一个图片
		{
			if(
				media->eLastPlayStatus == PLAY_STATUS_PLAY
				&& (!pPictureContainer->IsInDecoding())
				)
			{
				
				media->NextVideo();

				ResetAutoPictureScan();
			}
			
		}
	}
	
	
}

void USBActivity::ReStartFullScreenMovieWnd()		//重新开始视频窗口全屏
{
	StopTimer(iTimerFullScreenMovie);
	StartTimer(iTimerFullScreenMovie);
}

void USBActivity::AutoPictureScan()	//图片自动切换
{
	StartTimer(iTimerPictureScan);
}

void USBActivity::StopAutoPictureScan()	//停止图片自动切换
{
	StopTimer(iTimerPictureScan);
}

void USBActivity::ResetAutoPictureScan()	//重新开始图片自动切换
{
	StopTimer(iTimerPictureScan);
	StartTimer(iTimerPictureScan);
}

BOOL WriteStringToFile(HANDLE hFile, GxxString str)
{
	TCHAR szPath[MAX_PATH] = {0};
	_tcscpy(szPath, str.GetData());
	szPath[_tcslen(szPath)] = L'\n';
	DWORD dwWritten = 0;
	if(WriteFile(hFile, szPath, 2*(_tcslen(szPath)), &dwWritten, NULL))
	{
		return dwWritten == 2*(_tcslen(szPath));
	}
	return 0;
}

BOOL ReadStringFromFile(HANDLE hFile, TCHAR *szData)
{
	DWORD dwRead = 0;
	TCHAR tcsCode = 0;
	int i;
	for (i=0;tcsCode != L'\n'&& i<MAX_PATH;i++)
	{
		if(ReadFile(hFile, &tcsCode, 2, &dwRead, NULL))
		{
			if (dwRead != 2)
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
		szData[i] = tcsCode;
	}
	szData[i-1] = 0;
	return 1;
}

void USBActivity::LoadPlayStatus()
{
	// 使用 windows api 读取以下内容
	GxxString strPath = L"\\" ;
	strPath =strDevicePath + "\\usb.lst";
	HANDLE hFile = CreateFile(strPath, GENERIC_WRITE | GENERIC_READ, 0, NULL,OPEN_EXISTING, 0,0);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		goto END;
	}

	TCHAR szFile[MAX_PATH] = {0};

	//读取媒体类型
	
	if (!ReadStringFromFile(hFile, szFile))
	{
		goto END;
	}

	TCHAR *p = _tcsstr(szFile, L"MediaMode=");
	if (p)
	{
		p+=10;
		TCHAR szMode[16] = {0};
		for (int i=0;*p!=L'\n'&&i<16;p++,i++)
		{
			szMode[i]=*p;
		}
		elasyMediaMode = _ttoi(szMode);
	}
	//读取曲目时间
	
	if (!ReadStringFromFile(hFile, szFile))
	{
		goto END;
	}
	p = _tcsstr(szFile, L"time=");
	if (p)
	{
		p+=5;
		TCHAR szMode[16] = {0};
		for (int i=0;*p!=L'\n'&&i<16;p++,i++)
		{
			szMode[i]=*p;
		}
		dLastPlayTime = _ttoi(szMode);
		dLastPlayTime -= 3;
		if (dLastPlayTime < 0)
		{
			dLastPlayTime = 0;
		}
	}
	//读取曲目项ID
	if (ReadStringFromFile(hFile, szFile))
	{
		p = _tcsstr(szFile, L"ItemPlaying=");
		if (p)
		{
			p+=12;
			TCHAR szMode[16] = {0};
			for (int i=0;*p!=L'\n'&&i<16;p++,i++)
			{
				szMode[i]=*p;
			}
			iItemPlaying = _ttoi(szMode);
		}
	}
	
	// 读当前播放的曲目
	if (ReadStringFromFile(hFile, szFile))
	{
		sLastPlayPath = szFile;
	}
	else
	{
		goto END;
	}
END:
	CloseHandle(hFile);

#ifndef _DEBUG
	//GxxString strPath = L"\\" ;
	//strPath =strDevicePath + "\\usb.lst";
	DeleteFile(strPath);
#endif
}


LRESULT USBActivity::NotifyPauseMediaMovie(DWORD param1, DWORD param2)
{
	if(eCurrentMediaMode == MEDIAMODE_MOVIE)
	{
		media->PauseMedia();
	}
	return 0;
}

LRESULT USBActivity::NotifyPowerOff(DWORD param1, DWORD param2)
{
	if(!media)	return 0;

	dLastPlayTime = media->GetPlayTime();
	sLastPlayPath = media->GetLastPlayPath();
	
	//关机，停止播放
	onStop();
	

	GxxString strPath = L"\\" ;
	strPath =strDevicePath + "\\usb.lst";
	HANDLE hFile = CreateFile(strPath,GENERIC_WRITE | GENERIC_READ,0,NULL,CREATE_ALWAYS
		,0,0);
	if (hFile != INVALID_HANDLE_VALUE)
	{

		GxxString str;
		DWORD dwWritten = 0;
		
		//记录当前媒体类型
		str.Format( L"MediaMode=%d\n", eCurrentMediaMode);
		WriteFile(hFile, str.GetData(), str.GetLength()*2, &dwWritten, NULL);
		RETAILMSG(COUT_MSG, (TEXT("MediaMode = %d\r\n"), eCurrentMediaMode));

		// 记录当前播放时间
		str.Format( L"time=%f\n", dLastPlayTime);
		WriteFile(hFile, str.GetData(), str.GetLength()*2, &dwWritten, NULL);
		RETAILMSG(COUT_MSG, (TEXT("time = %s\r\n"), str.GetData()));
		
		//记录当前曲目
		iItemPlaying = media->GetItemPlaying();
		str.Format( L"ItemPlaying=%d\n", iItemPlaying);
		WriteFile(hFile, str.GetData(), str.GetLength()*2, &dwWritten, NULL);

		
		// 写入当前播放的曲目
		WriteStringToFile(hFile, sLastPlayPath);
		//RETAILMSG(1, (TEXT("sLastPlayMoviePath = %s\r\n"), sLastPlayPath.GetData()));
		
		CloseHandle(hFile);
	}

	return 0;
}

LRESULT USBActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//不在本窗口下
	if( Activity::GetActiveActiviy() != (USBActivity*)this)
	{
		return 0;
	}

	int iMsg = param1;
	switch(iMsg)
	{
	case HardwareBtnMatch::PLAY_KEY:	//暂停播放
		{
			KeyPlayAndPause();
		}
		break;
	case HardwareBtnMatch::PRE_KEY:	//上一曲
		{
			if(media)
			{
				media->PrevVideo();
			}
		}
		break;
	case HardwareBtnMatch::NEXT_KEY:	//下一曲
		{
			if(media)
			{
				media->NextVideo();
			}
		}
		break;
	case HardwareBtnMatch::BACK_KEY:	//返回
		{
			

			if(pControlGroup_FileList->getDraw())	//曲目列表下
			{
				pControlGroup_FileList->setDraw(false);
				pControlGroup_main->setDraw(true);
				AfxInvalidateRect(NULL);

				//关闭浏览界面后，播放
				media->Play();
			}
			else if(pControlGroup_fullScreen->getDraw())	//全屏下
			{
				pControlGroup_fullScreen->setDraw(false);
				pControlGroup_main->setDraw(true);
				AfxInvalidateRect(NULL);
			}
			else
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
			}		
		}

	}
	return 0;
}

BOOL USBActivity::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message == WM_LBUTTONDOWN)
	{
		if (eCurrentMediaMode == MEDIAMODE_MOVIE)
		{
			ReStartFullScreenMovieWnd();	//重新开始视频窗口全屏
		}
		if(eCurrentMediaMode == MEDIAMODE_PICTURE)
		{
			if(media->eLastPlayStatus == PLAY_STATUS_PLAY)
			{
				ResetAutoPictureScan();	//重新开始图片播放
			}

		}
	}
	
	
	return Activity::DealCtrlMsg(message,wParam,lParam);
}


static RegisterHelp help("USBActivity", USBActivity::CreateControl);