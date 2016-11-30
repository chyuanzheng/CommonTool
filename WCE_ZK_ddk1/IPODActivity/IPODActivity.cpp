#pragma once
#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "IPODActivity.h"
#include "VolumeControl.h"
#include "AVSet.h"
#include "WheelMsg.h"
#include "iPodHardware/IpodHardware.h"

#define ELAPSE_DETECT_IPOD 5000
#define ELAPSE_DETECT_VIDEO 1000
#define TIMER_HIDE_CONTROLS_ELAPSE 6000

#define ELAPSE_FIVE_SECONDS 5000

#define ELAPSE_PLAY_PAUSE_STATUS 2000

#define ELAPSE_DETECT_MEDIA_MODE 2000

#define ELAPSE_REFRESH_PROGRESS 1500

IPODActivity* IPODActivity::pThis;

IPODActivity::IPODActivity()
{
	pThis = this;	//保存自身的指针

	iCurrentVideo = 0;
	iTotalVideo = 0;

	bAllRepeat = false;

	bSingleRepeat = false;

	bRefreshProgress = true;
}

Activity* IPODActivity::CreateControl()
{
	return new IPODActivity;
}

void IPODActivity::onCreate()
{
	
	setContentView("layout\\IPOD\\IPodPad.xml");
	Activity::onCreate();

	pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");
	
	pIPodLib = IPodAppLib::Instance(AfxGetHWND());
	pIPodLib->RegisterMsg(HandleIpodMsg, (DWORD)this);
	//初始化音量
	VolumeControl::ApplayForPermission(VolumeModuleId::IPOD, 0, L"ipod");

	

	pLabel_PrevVideo  = (GxxAniLable*)safeFindViewByName("Label_PrevVideo");
	pLabel_NextVideo  = (GxxAniLable*)safeFindViewByName("Label_NextVideo");
	pLabelPlayAndPause  = (GxxAniLable*)safeFindViewByName("LabelPlayAndPause");
	//pLabelPause  = (GxxAniLable*)safeFindViewByName("LabelPause");

	pLabel_MusicName = (GxxMoveText*)safeFindViewByName("Label_MusicName");
	pLabel_MusicArtist = (GxxMoveText*)safeFindViewByName("Label_MusicArtist");
	pLabel_MusicAlbum = (GxxMoveText*)safeFindViewByName("Label_MusicAlbum");


	pLabel_BrowseList = (GxxAniLable*)safeFindViewByName("Label_BrowseList");

	pPicPlayStatus = (GxxPicIcon*)safeFindViewByName("PicPlayStatus");
	pPicPauseStatus = (GxxPicIcon*)safeFindViewByName("PicPauseStatus");
	pPicStopStatus = (GxxPicIcon*)safeFindViewByName("PicStopStatus");
	pPicPlayStatus->setDraw(false);
	pPicPauseStatus->setDraw(false);
	pPicStopStatus->setDraw(false);


//	pLabelSwitchToMusic = (GxxAniLable*)safeFindViewByName("LabelSwitchToMusic");
//	pLabelSwitchToMovie = (GxxAniLable*)safeFindViewByName("LabelSwitchToMovie");

	pPicCommandFail = (GxxPicIcon*)safeFindViewByName("PicCommandFail");
	pPicCommandFail->setDraw(false);

	pLabel_currentTime = (GxxAniLable*)safeFindViewByName("Label_currentTime");
	pLabel_totaltime = (GxxAniLable*)safeFindViewByName("Label_totaltime");
	pLabel_totaltime->SetText("");

	pProgressVideoTime = (GxxClickProgressBar*)safeFindViewByName("ProgressVideoTime");
	pProgressVideoTime->SetMessageView(this);

	pLabel_Repeat = (GxxAniLable*)safeFindViewByName("Label_Repeat");
	pLabelShre = (GxxAniLable*)safeFindViewByName("LabelShre");
	
	pLabelToSetupAudio = (GxxAniLable*)safeFindViewByName("LabelToSetupAudio");

	pPicLoop1 = (GxxPicIcon*)safeFindViewByName("PicLoop1");
	pPicLoop1->setDraw(false);
	pPicLoopAll = (GxxPicIcon*)safeFindViewByName("PicLoopAll");
	pPicLoopAll->setDraw(false);
	pPicShuffle = (GxxPicIcon*)safeFindViewByName("PicShuffle");
	pPicShuffle->setDraw(false);
	
	pControlGroup_MusicInfo = (GxxControlGroup*)safeFindViewByName("ControlGroup_MusicInfo");
	pControlGroup_MovieInfo= (GxxControlGroup*)safeFindViewByName("ControlGroup_MovieInfo");

	pLabel_MainOrInfo = (GxxAniLable*)safeFindViewByName("Label_MainOrInfo");

	pControlGroup_fullScreen = (GxxControlGroup*)safeFindViewByName("ControlGroup_fullScreen");
	pControlGroup_fullScreen->setDraw(false);
	pControlGroup_FullScreenControls = (GxxControlGroup*)safeFindViewByName("ControlGroup_FullScreenControls");

	pLabel_ReturnMain = (GxxAniLable *)safeFindViewByName("Label_ReturnMain");

	//初始化视频窗口
	pMediaWnd = (TccMediaWndEx*)safeFindViewByName("moviewindow");
	pMediaWnd->SetFun(ClickMediaWnd, this);

	//设置驾驶中警告语
	GxxAniLable* pLabelWarnning = (GxxAniLable*)safeFindViewByName("LabelWarnning");
	pMediaWnd->SetWarning(pLabelWarnning, false);
	
	iTimerPlayStatus	= RegisterTimer(ELAPSE_PLAY_PAUSE_STATUS);	//显示播放暂时的状态
	//iTimerDetectMediaMode	= RegisterTimer(ELAPSE_DETECT_MEDIA_MODE);

	pControlGroup_main = (GxxControlGroup*)safeFindViewByName("ControlGroup_main");
	pControlGroup_Info = (GxxControlGroup*)safeFindViewByName("ControlGroup_Info");
	pControl_group_IpodList = (GxxControlGroup*)safeFindViewByName("Control_group_IpodList");

	pLabel_VideoCount =  (GxxAniLable *)safeFindViewByName("Label_VideoCount");

	pLabel_Setting =  (GxxAniLable *)safeFindViewByName("Label_Setting");

	pPicMusicLogo =  (GxxIpodIcon *)safeFindViewByName("PicMusicLogo");
	
	Notify notify;
	notify.dwParam = this;

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);
	notify.funNotify = IpodNameNotify;
	GXNotify::RegisterNotifyHandler("ipod_name", notify);
	notify.funNotify = NotifyCurrentAndTotalFileNum;
	GXNotify::RegisterNotifyHandler("ipod_msg_current_and_total_filenum", notify);
	
	notify.funNotify = SetIPODVolume;
	GXNotify::RegisterNotifyHandler("SetIPODVolume", notify);

	notify.funNotify = SetIpodMute;
	GXNotify::RegisterNotifyHandler("SetIPodMute", notify);

	EnableActivity("IPODActivity", false);

	
	iTimerDetectIpod = RegisterTimer(ELAPSE_DETECT_IPOD);	//检测IPOD
	StartTimer(iTimerDetectIpod);

	iTimeVideoDetect =	RegisterTimer(ELAPSE_DETECT_VIDEO);	//检测VIDEO
	iTimerHideControlId	= RegisterTimer(TIMER_HIDE_CONTROLS_ELAPSE);
 
	iTimerRefreshProgress	= RegisterTimer(ELAPSE_REFRESH_PROGRESS);

	pVideoSetup =   (GxxVedioSetup *)safeFindViewByName("VideoSetup");	//用于设置视频
	pVideoSetup->setDraw(false);



 	pIpodList = (GxxIpodListGroup*)safeFindViewByName("IpodList");
	pIpodList->SetMessageView(this);

	
	m_iCurrentMediaMode = DBSEL_AUDIO;
	

	bIntial = false;

	iTimerFullScreenMovie = RegisterTimer(ELAPSE_FIVE_SECONDS);

	ipodPlayStatus = IpodHardware::IPOD_STOP;

	//由于出现IPOD与USB同时出声音的情况，IPOD音量设定为0
	pIPodLib->Ipod_SetVolume(0);
	
}

void IPODActivity::HidePlayStatus()	//隐藏播放状态
{
	pPicPlayStatus->setDraw(false);
	pPicPauseStatus->setDraw(false);
	pPicStopStatus->setDraw(false);
}

void IPODActivity::UpdatePlayStatus(int iPlayStatus)	//更新播放状态
{
	StopTimer(iTimerPlayStatus);

	HidePlayStatus();
	AfxInvalidateRect(NULL);
	
	switch(iPlayStatus)
	{
	case IpodHardware::IPOD_PLAYING:
		{
			pPicPlayStatus->setDraw(true);
			//pPicPauseStatus->setDraw(false);
			//pPicStopS tatus->setDraw(false); 
			StartTimer(iTimerPlayStatus);
		}
		break;
	case IpodHardware::IPOD_PAUSE:
		{
			//pPicPlayStatus->setDraw(false);
			pPicPauseStatus->setDraw(true);
			//pPicStopStatus->setDraw(false);
		}
		break;
	case IpodHardware::IPOD_STOP:
		{
			//pPicPlayStatus->setDraw(false);
			//pPicPauseStatus->setDraw(false);
			pPicStopStatus->setDraw(true);
			//StartTimer(iTimerPlayStatus);
		}
		break;
	}

}


void IPODActivity::StartFullScreenMovieWnd()		//视频窗口，全屏
{
	StartTimer(iTimerFullScreenMovie);
}

void IPODActivity::StopFullScreenMovieWnd()		//停止视频窗口
{
	StopTimer(iTimerFullScreenMovie);
}

void IPODActivity::ReStartFullScreenMovieWnd()		//重新开始视频窗口全屏
{
	StopTimer(iTimerFullScreenMovie);
	StartTimer(iTimerFullScreenMovie);
}




//视频全屏时，点击视频的响应函数
void IPODActivity::ClickMediaWnd(GxxView *p, void *dwParam)
{
	IPODActivity* pThis = (IPODActivity*)dwParam;
	if(pThis->pMediaWnd->IsFullScreen())
	{
		pThis->ShowFullControls();
		//pThis->dvdControl.DvdUser_cont(pThis->pMediaWnd->ptClickPosX, pThis->pMediaWnd->ptClickPosY);
	}
	else
	{
		pThis->FullScreen();

	}


}

void IPODActivity::FullScreen(bool bShowControl/* = true*/)		//全屏
{
	if(m_iCurrentMediaMode == DBSEL_VIDEO)
	{
		AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);
		pControlGroup_main->setDraw(false);
		pMediaWnd->SetFullScreen();

		if(!pControlGroup_fullScreen->getDraw())
		{
			pControlGroup_fullScreen->setDraw(true);

		}

		if(bShowControl)
		{
			ShowFullControls();
		}

		AfxInvalidateRect(NULL);
	}
}

//显示全屏时的控件
void IPODActivity::ShowFullControls()
{
	StopTimer(iTimerHideControlId);

	

	//显示视频全屏时的控件
	if(!pControlGroup_FullScreenControls->getDraw())
	{
		pControlGroup_FullScreenControls->setDraw(true);
	}
	AfxInvalidateRect(NULL);
	
	StartTimer(iTimerHideControlId);



}

void IPODActivity::ClearUserInterface()	//清空界面
{
	m_iCurrentMediaMode = DBSEL_AUDIO;
	SwitchUserInterface();

	pLabel_MusicName->setTextFromId("ID_Track");
	pLabel_MusicArtist->setTextFromId("ID_Artist");
	pLabel_MusicAlbum->setTextFromId("ID_Album");
	
	pProgressVideoTime->SetDisplayPos(0);
	pLabel_currentTime->SetText("");
	pLabel_totaltime->SetText("");
	pLabel_VideoCount->SetText("0000/0000");

	pPicMusicLogo->ResetIcon();	//恢复默认图片
}

void IPODActivity::SwitchUserInterface()	//切换UI
{
	switch(m_iCurrentMediaMode)
	{
	case DBSEL_AUDIO:
		{
			pControlGroup_main->setDraw(true);
			pControlGroup_MusicInfo->setDraw(true);
			pControl_group_IpodList->setDraw(false);
			pControlGroup_MovieInfo->setDraw(false);
			pPicMusicLogo->SetReceiveIcon(true);
			pMediaWnd->setDraw(false);
		}
		break;
	case DBSEL_VIDEO:
		{
			pControlGroup_main->setDraw(true);
			pControlGroup_MusicInfo->setDraw(false);
			pControl_group_IpodList->setDraw(false);
			pControlGroup_MovieInfo->setDraw(true);
			pPicMusicLogo->SetReceiveIcon(false);
			
			//初始化视频状态，避免闪频
			video_source = NOVIDEO;
			pMediaWnd->setDraw(true);
			pMediaWnd->CloseVideo(true);
		}
		break;

	}
	AfxInvalidateRect(NULL);
}

void IPODActivity::SwitchToListGroup()
{
	pControlGroup_main->setDraw(false);
	pControlGroup_MusicInfo->setDraw(false);
	pControlGroup_MovieInfo->setDraw(false);

	pControl_group_IpodList->setDraw(true);
	//pIpodList->InitFirstList();//每次进入list从最前面的第一层目录开始
	AfxInvalidateRect(NULL);
}

LRESULT IPODActivity::NotifyCurrentAndTotalFileNum(DWORD param1, DWORD param2)
{
	iCurrentVideo = param1;
	iTotalVideo = param2;
	GxxString strCurrentAndTotalFileNum;
	strCurrentAndTotalFileNum.Format(L"%04d/%04d", param1, param2);
	pLabel_VideoCount->SetText(strCurrentAndTotalFileNum.GetData());
	return 0;
}

LRESULT IPODActivity::SetIPODVolume(DWORD param1, DWORD param2)
{
	if (param2 == -1)
	{
		if(running == 0)
		{
			return 0;
		}
	}
	RETAILMSG(1, (TEXT("iPod Setvol = %d\r\n"), param1));
	pIPodLib->Ipod_SetVolume(param1);// Ipod_SetVolume(param1);
	return 0;
}

LRESULT IPODActivity::SetIpodMute(DWORD param1, DWORD param2)
{
	if (param1 == 0)
	{
		pIPodLib->Ipod_Mute(0);
	}
	else
	{
		pIPodLib->Ipod_Mute(1);
	}
	return 0;
}


LRESULT IPODActivity::IpodNameNotify(DWORD param1, DWORD param2)
{
	//pLabel_IPodName->SetText((LPCTSTR)param1, true);
	pIpodList->SetIpodName( (const WCHAR *)param1 );
	return 0;
}

LRESULT IPODActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//不在本窗口下
	if( Activity::GetActiveActiviy() != (IPODActivity*)this)
	{
		return 0;
	}

	int iMsg = param1;
	switch(iMsg)
	{
	case HardwareBtnMatch::BACK_KEY:	//返回
		{
			AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		}
		break;
	case HardwareBtnMatch::PLAY_KEY:	//暂停播放
		{
			PlayAndPause();
		}
		break;
	case HardwareBtnMatch::PRE_KEY:	//上一曲
		{
			PrevVideo();
		}
		break;
	case HardwareBtnMatch::NEXT_KEY:	//下一曲
		{
			NextVideo();
		}
		break;
	}
	return 0;
}


 

BOOL IPODActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case GX_INIT_MUSIC_LIST:
		{
			pIPodLib->InitHierarchy(DBSEL_AUDIO,lParam);
			return TRUE;
		}

	case  GX_INIT_MOVIE_LIST:
		{
			pIPodLib->InitHierarchy(DBSEL_VIDEO,lParam);
			return TRUE;
		}

	case GX_LISTBOX_BACK_TO_ACTIVITY:
		SwitchUserInterface();
		return TRUE;
	

	case GX_LISTBOX_BACK_TO_LIST:
		{
			if( !pIPodLib->ListBack() )	//返回分类菜单
			{
				pIpodList->BackToMenu();
			}	
			return TRUE;
		}

	case GX_LISTBOX_BUTTON_DOWNM:
		{
			int iItem = (int)lParam;
			
			bool ret = pIPodLib->IpodSelectList(iItem);
			if(ret)	//跳到播放界面
			{
				m_iCurrentMediaMode = pIPodLib->GetMediaPathType();
				SwitchUserInterface();		
			}
		}
		return TRUE;
	case CTR_MESSAGE:
		if ((GxxClickProgressBar *)wParam == pProgressVideoTime)	
		{
			int iTime = lParam;
			
			pIPodLib->SetPlayTime(iTime);
			
			//间隔一定时间后，才允许刷新滚动条，以免滚动条显示不正确
			StartTimer(iTimerRefreshProgress);
			bRefreshProgress = false;

			
		//	int hour = iTime/3600;
		//	int min = (iTime-3600*hour)/60;
		//	int sec = iTime-hour*3600-min*60;

		//	RETAILMSG(COUT_MSG, (TEXT("1.set play time ----------------------\n")));
		//	RETAILMSG(COUT_MSG, (TEXT("ipod time = %d:%d \r\n"), min, sec ));

			return TRUE;
		}
		if (MES_LBUTTONUP==lParam)
		{
			
			if ((GxxAniLable *)wParam == pLabel_MainOrInfo)		//主界面与信息界面切换
			{
				
				bool bMainShow = pControlGroup_main->getDraw();
				bool pInfoShow = pControlGroup_Info->getDraw();

				if(bMainShow && !pInfoShow)
				{
					pControlGroup_main->setDraw(false);
					pControlGroup_Info->setDraw(true);
					Activity::overridePendingTransition(pControlGroup_main,pControlGroup_Info,Activity::s_hAniRotateY);
				}
				else if(!bMainShow && pInfoShow)
				{
					pControlGroup_main->setDraw(true);
					pControlGroup_Info->setDraw(false);

					Activity::overridePendingTransition(pControlGroup_Info,pControlGroup_main,Activity::s_hAniRotateY);
				}
				AfxInvalidateRect(NULL);

				return TRUE;

			}

			if ((GxxAniLable *)wParam == pLabel_Setting)		//设定
			{
				if(pVideoSetup->getDraw())
				{
					pVideoSetup->setDraw(false);
				}
				else
				{
					pVideoSetup->setDraw(true);
				}
				AfxInvalidateRect(NULL);

				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_BrowseList)		//搜索
			{
				SwitchToListGroup();
			//	pIpodList->Invatelidate(-1);	//回到根目录
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pInc_Into_MainInterface)		//返回主界面
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_PrevVideo)	
			{
				
				PrevVideo();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_NextVideo)	
			{
				NextVideo();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelPlayAndPause)	
			{
				PlayAndPause();

				return TRUE;
			}
			/*if ((GxxAniLable *)wParam == pLabelPause)	
			{
				pIPodLib->IpodPause();
				return TRUE;
			}*/
			//if ((GxxAniLable *)wParam == pLabelSwitchToMusic)	
			//{
			//	//BOOL ret = pIPodLib->MusicResume(TRUE);
			//	pMediaWnd->CloseVideo();
			//	pMediaWnd->setDraw(false);
			//	AfxInvalidateRect(NULL);
			//	SwitchMedia(MEDIA_MUSIC);
			//	pIPodLib->IpodPlay();
			//	return TRUE;
			//}
			//if ((GxxAniLable *)wParam == pLabelSwitchToMovie)	
			//{
			//	//BOOL ret = pIPodLib->VideoResume(TRUE);
			//	SwitchMedia(MEDIA_MOVIE);
			//	pIPodLib->IpodPlay();
			//	return TRUE;
			//}
			if ((GxxAniLable *)wParam == pLabel_ReturnMain)	//缩小屏幕
			{
				SubScreen();

				ReStartFullScreenMovieWnd();	//重新开始视频窗口全屏
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Repeat)	
			{
				static int i = 0;
				switch(i)
				{
				case 0:
					{
						pIPodLib->SetRepeat(REPEATONETRACK);
					}
					break;
				case 1:
					{
						pIPodLib->SetRepeat(REPEATALLTRACKS);
					}
					break;
				case 2:
					{
						pIPodLib->SetRepeat(REPEATOFF);
					}
					break;
				}
				i++;
				i = i%3;
				
				return TRUE; 
			}
			if ((GxxAniLable *)wParam == pLabelShre)	
			{
				static int iShuffleMode = SHUFFLETRACKS;
				switch(iShuffleMode)
				{
				case 0:
					{
						pIPodLib->SetShuffle(SHUFFLETRACKS);
					}
					break;
				case 1:
					{
						pIPodLib->SetShuffle(REPEATOFF);
					}
					break;
				}
				iShuffleMode++;
				iShuffleMode = iShuffleMode%2;
				return TRUE; 
			}
			if ((GxxAniLable *)wParam == pLabelToSetupAudio)
			{
				Activity::startActivity(this,"SetupActivity","2_sound_setup");
				return TRUE;
			}
		}
		
		return FALSE;
	default:
		return FALSE;
	}
}

void IPODActivity::PlayAndPause()
{
	if(ipodPlayStatus != IpodHardware::IPOD_PLAYING)
	{
		VolumeControl::SlowlyIncreaseVolume();	//音量缓升

	}
	pIPodLib->SetPlaypause();

	//媒体类型可能会有变化
//	DetectMediaMode();
}

void IPODActivity::NextVideo()
{
	if(iCurrentVideo == 0)	return;
	//曲目名和曲目总数一致，目不是循环时，返回
	//防止到最后一曲，出错
	if(iCurrentVideo == iTotalVideo && !bAllRepeat)
	{
		return;
	}

	//切换视频时，关于视频，防止视频闪
	if(m_iCurrentMediaMode == DBSEL_VIDEO)
	{
		video_source = 0;
		pMediaWnd->CloseVideo(true);
	}

	pIPodLib->IpodNext();

	//媒体类型可能会有变化
	//DetectMediaMode();
	
}
//
//void IPODActivity::DetectMediaMode()
//{
//	//StopTimer(iTimerDetectMediaMode);
//	StartTimer(iTimerDetectMediaMode);
//
//
//}

void IPODActivity::PrevVideo()
{
	if(iCurrentVideo == 1 && bSingleRepeat)	return;

	//切换视频时，隐藏视频窗口，防止视频闪
	if(m_iCurrentMediaMode == DBSEL_VIDEO)
	{
		video_source = 0;
		pMediaWnd->CloseVideo(true);
		//pMediaWnd->setDraw(false);
		//CRect rc;
		//pMediaWnd->getCtrRect(rc);
		//AfxInvalidateRect(&rc);
		
	}

	pIPodLib->IpodPrev();

	//媒体类型可能会有变化
	//DetectMediaMode();
}

void IPODActivity::SubScreen()	//缩小屏幕
{
	AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);
	
	if(pMediaWnd->IsFullScreen())
	{
		pMediaWnd->ReductionScreen();
		pControlGroup_FullScreenControls->setDraw(false);
		pControlGroup_fullScreen->setDraw(false);
		if(!pControlGroup_Info->getDraw())
		{
			pControlGroup_main->setDraw(true);
		}
		
	}
	

	AfxInvalidateRect(&m_ActRect);
}

void IPODActivity::onStop()
{
	pIPodLib->IpodPause();
	MediaControl::StopCamera();
	bIntial = false;
	Sleep(300);

	running = 0;
	//由于出现IPOD与USB同时出声音的情况，退出IPOD时，IPOD音量设定为0
	pIPodLib->Ipod_SetVolume(0);
}

void  IPODActivity::onResume()
{
	// 切换声音到ipod
	AVSET::ToIpod();

	VolumeControl::ApplyForVolumeControl(VolumeModuleId::IPOD);

	//设定IPOD的声音
	pIPodLib->Ipod_SetVolume(30);

	pControl_group_IpodList->setDraw(false);
	
	MediaControl::SetMediaMode(CAMERA);

	CRect rcWnd;
	pMediaWnd->getCtrRect(rcWnd);
	//pMediaWnd->setDraw(false);
	MediaControl::SetMediaRect(rcWnd);

	
	
	if(!bIntial)	//插入IPOD后，第一次进入IPOD界面
	{
		bIntial = true;

		video_source = NOVIDEO;
		pIPodLib->IpodPlay();
	}
	
	StartVideoDetect();	//检查VIDEO

	StartFullScreenMovieWnd();		//视频窗口，全屏

	running = 1;
}

void IPODActivity::StartVideoDetect()	//检查VIDEO
{
	StartTimer(iTimeVideoDetect);
}



void IPODActivity::onPause()
{
	SubScreen();	//缩小屏幕
	StopTimer(iTimeVideoDetect);

	StopFullScreenMovieWnd();		//停止视频窗口
}

void IPODActivity::TimerTick( UINT nIDEvent )
{
	if (nIDEvent == iTimerHideControlId)
	{
		if(pThis->pControlGroup_FullScreenControls->getDraw())
		{
			pThis->pControlGroup_FullScreenControls->setDraw(false);

		}
		AfxInvalidateRect(NULL);

		StopTimer(nIDEvent);
	}
	else if(nIDEvent == iTimeVideoDetect)
	{
		 VideoSourceAutoDetect();

	}
	else if(nIDEvent == iTimerPlayStatus)
	{
		StopTimer(iTimerPlayStatus);

		HidePlayStatus();

		AfxInvalidateRect(NULL);

	}
	else if(nIDEvent == iTimerDetectIpod)	//开机检测有没有IPOD
	{
		bool bRet = pIPodLib->IsConnected();
		EnableActivity("IPODActivity", bRet);

		StopTimer(nIDEvent);
	}
	else if(nIDEvent == iTimerFullScreenMovie)
	{
		if(
			pMediaWnd->getDraw()
			&& pMediaWnd->GetVideoEnable()
			&& !pMediaWnd->IsFullScreen()
			&& (!pControl_group_IpodList->getDraw())
			&& pMediaWnd->GetIsBrake()
			)
		{
			FullScreen(false);

			//重新开始计时
			StopTimer(iTimerFullScreenMovie);
			StartTimer(iTimerFullScreenMovie);
		}
	}
	//间隔一定时间后，才允许刷新滚动条，以免滚动条显示不正确
	else if(nIDEvent == iTimerRefreshProgress)
	{
		StopTimer(iTimerRefreshProgress);
		bRefreshProgress = true;
	}
	
}

void IPODActivity::VideoSourceAutoDetect()
{
	int source_now = AVSET::SourceCheck();
	//RETAILMSG(COUT_MSG, (TEXT("ipod video = %d\r\n"), source_now));
	//source_now = NTSC
	if (video_source == source_now)
	{
		return;
	}
	video_source = source_now;
	if (video_source == NTSC)
	{
		MediaControl::StopCamera();
		MediaControl::InitCamera(NTSC); 
		MediaControl::StartCamera();
		pMediaWnd->setDraw(true);
		pMediaWnd->ShowVideo(true);
	
	}
	if (video_source == PAL)
	{
		MediaControl::StopCamera();
		MediaControl::InitCamera(PAL);
		MediaControl::StartCamera();
		pMediaWnd->setDraw(true);
		pMediaWnd->ShowVideo(true);

		
		
	}
	if (video_source == NOVIDEO)
	{
		MediaControl::StopCamera();
		pMediaWnd->setDraw(true);
		pMediaWnd->CloseVideo(true);


		
	}
}

DWORD IPODActivity::HandleIpodMsg(CHardware *pControl, UINT msg, WPARAM wParam, LPARAM lParam)
{
//	RETAILMSG(1, (TEXT("Ipod Msg wParam = %d\r\n"), wParam));
	switch(msg)
	{
	case IPOD_MSG_AUTHSUCCESS:
		{
			if (lParam == 0)
			{
				startActivity(NULL,"IPODActivity");
				EnableActivity("IPODActivity", true);

				if( Activity::GetActiveActiviy() == (IPODActivity*)this)
				{
					// iPod接入
					pIPodLib->IpodPlay();
				}

				IpodListItemId = 0;
			}
			if (lParam == 1)
			{
				// iPod授权成功
				RETAILMSG(COUT_MSG, (TEXT("授权成功\r\n")));
			}
			break;
		}
	case IPOD_MSG_NAME:
		{
			if (lParam != 0)
			{
				//pLabel_IPodName->SetText((LPCTSTR)lParam);
				RETAILMSG(COUT_MSG, (TEXT("IPOD_MSG_NAME = %d\r\n"), (LPCTSTR)lParam));
				/*pLabDisplay1->SetText((LPCTSTR)lParam, 1);*/
			}
			else
			{
				// iPod 拔出
				pIpodList->InitList();
				bIntial = false;
				m_iCurrentMediaMode = DBSEL_AUDIO;
				SwitchUserInterface();

				ClearUserInterface();	//清空界面

				EnableActivity("IPODActivity", false);
				
				if( Activity::GetActiveActiviy() == (IPODActivity*)this)
				{
					startActivity(NULL,"MainPad");
					onStop();
				}
				
			}
			break;
		}

	case IPOD_MSG_TIME:
		{
			if(!bRefreshProgress)
			{
				break;
			}
			int curTime = pIPodLib->GetCurTime();

			//int hour = curTime/3600;
			//int min = (curTime-3600*hour)/60;
			//int sec = curTime-hour*3600-min*60;
			//RETAILMSG(COUT_MSG, (TEXT("ipod time = %d:%d \r\n"), min, sec ));
			
			GxxString str;
			if(curTime)
			{
				pProgressVideoTime->SetDisplayPos(curTime);

				str.TimeStr(curTime);
				pLabel_currentTime->SetText(str.GetData());
			}

			int totalTime = pIPodLib->GetTotalTime();
			if (totalTime)
			{
				pProgressVideoTime->SetRange(0, totalTime);
				//RETAILMSG(COUT_MSG, (TEXT("curTime = %d, totalTime = %d\r\n"), curTime, totalTime ));
				str.TimeStr(totalTime);
				pLabel_totaltime->SetText(str.GetData());
			}
			break;
		}
	case IPOD_MSG_PLAYSTATUS:
		{
			ipodPlayStatus = lParam;
			if (ipodPlayStatus == IpodHardware::IPOD_PLAYING)
			{
				UpdatePlayStatus(IpodHardware::IPOD_PLAYING);
			}

			if (ipodPlayStatus == IpodHardware::IPOD_STOP)
			{
				UpdatePlayStatus(IpodHardware::IPOD_STOP);
			}

			if(ipodPlayStatus == IpodHardware::IPOD_PAUSE)
			{
				UpdatePlayStatus(IpodHardware::IPOD_PAUSE);
			}

			break;
		}
	case IPOD_MSG_ARTIST:
		{
			/*SetArtist((LPCTSTR)lParam);*/
			pLabel_MusicArtist->setText((LPCTSTR)lParam);
			RECT rc;
			pLabel_MusicArtist->getCtrRect(rc);
			AfxInvalidateRect(&rc);
			RETAILMSG(COUT_MSG, (TEXT("IPOD_MSG_ARTIST = %s\r\n"), (LPCTSTR)lParam));
			
			break;
		}
	case IPOD_MSG_ALBUM:
		{
			pLabel_MusicAlbum->setText((LPCTSTR)lParam);
			RECT rc;
			pLabel_MusicAlbum->getCtrRect(rc);
			AfxInvalidateRect(&rc);
			RETAILMSG(COUT_MSG, (TEXT("IPOD_MSG_ALBUM = %s\r\n"), (LPCTSTR)lParam));
			break;
		}
	case IPOD_MSG_GENRE:
		{
			RETAILMSG(1, (TEXT("IPOD_MSG_GENRE = %s\r\n"), (LPCTSTR)lParam));
			break;
		}
	case IPOD_MSG_TITLE:
		{
			wstring wstr = (LPCTSTR)lParam;
			pLabel_MusicName->setText(wstr);
			RECT rc;
			pLabel_MusicName->getCtrRect(rc);
			AfxInvalidateRect(&rc);
			RETAILMSG(COUT_MSG, (TEXT("IPOD_MSG_TITLE = %s\r\n"), wstr.c_str()));
			//RETAILMSG(1, (TEXT("IPOD_TITLE = %s\r\n"), (TCHAR*)lParam));
			/*SetTitle((LPCTSTR)lParam);*/
			break;
		}
	case IPOD_MSG_SHUFFLE:
		{
			// 0x00 shuffle off
			// 0x01 shuffle tracks
			// 0x02 shuffle albums
			switch(lParam)
			{
			case 0x00:
				{
					pPicShuffle->setDraw(false);
					
				}
				break;
			case 0x01:
				{
					pPicShuffle->setDraw(true);
					
				}
				break;
			default:
				{
					pPicShuffle->setDraw(false);
				}
			}
			RECT rc;
			pPicShuffle->getCtrRect(rc);
			AfxInvalidateRect(&rc);
			break;
		}
	case IPOD_MSG_REPEAT:
		{
			bAllRepeat = false;
			bSingleRepeat = false;
			// 0x00 repeat off
			// 0x01 repeat one track
			// 0x02 repeat all track
			RETAILMSG(COUT_MSG, (TEXT("IPOD_MSG_REPEAT = %d,%d\r\n"),(LPCTSTR)wParam, (LPCTSTR)lParam));
			switch(lParam)
			{
			case 0x00:
				{
					pPicLoop1->setDraw(false);
					pPicLoopAll->setDraw(false);
				}
				break;
			case 0x01:
				{
					pPicLoopAll->setDraw(false);
					pPicLoop1->setDraw(true);

					bSingleRepeat = true;
				}
				break;
			case 0x02:
				{
					pPicLoopAll->setDraw(true);
					pPicLoop1->setDraw(false);

					bAllRepeat = true;
				}
				break;
			default:
				{
					pPicLoopAll->setDraw(false);
					pPicLoop1->setDraw(false);
				}
			}
			RECT rc;
			pPicLoop1->getCtrRect(rc);
			AfxInvalidateRect(&rc);
			//AfxInvalidateRect(NULL);
		}
		break;

	case IPOD_LIST_INIT:
		{
			pIpodList->InitFirstList();
			RETAILMSG(COUT_MSG, (TEXT("IPOD_LIST_INIT \r\n")));
			break;
		}
	case IPOD_LIST_START:
		{
			pIpodList->StartReceiveList();
			break;
		}
	case IPOD_LIST_INSERT:
		{
			wstring name = (LPCTSTR)lParam;
			if(name.empty() || name == L" ")
			{
				name  = L"Unknown";
			}
			pIpodList->AddItem(name);
			
			//RETAILMSG(COUT_MSG, (TEXT("LIST_INSERT = %s\r\n"), (LPCTSTR)lParam));
			break;
		}
	case  IPOD_LIST_INSERT_END:
		pIpodList->ResetList();
		break;
	}
	return 0;
}

BOOL IPODActivity::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message == WM_LBUTTONDOWN)
	{
		ReStartFullScreenMovieWnd();	//重新开始视频窗口全屏

		//延长控件的显示时间
		if(pMediaWnd->IsFullScreen() && !pControlGroup_main->getDraw())
		{
			ShowFullControls();
		}
	}
	return Activity::DealCtrlMsg(message,wParam,lParam);
}



static RegisterHelp help("IPODActivity", IPODActivity::CreateControl);