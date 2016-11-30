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
	pThis = this;	//���������ָ��

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
	//��ʼ������
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

	//��ʼ����Ƶ����
	pMediaWnd = (TccMediaWndEx*)safeFindViewByName("moviewindow");
	pMediaWnd->SetFun(ClickMediaWnd, this);

	//���ü�ʻ�о�����
	GxxAniLable* pLabelWarnning = (GxxAniLable*)safeFindViewByName("LabelWarnning");
	pMediaWnd->SetWarning(pLabelWarnning, false);
	
	iTimerPlayStatus	= RegisterTimer(ELAPSE_PLAY_PAUSE_STATUS);	//��ʾ������ʱ��״̬
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

	
	iTimerDetectIpod = RegisterTimer(ELAPSE_DETECT_IPOD);	//���IPOD
	StartTimer(iTimerDetectIpod);

	iTimeVideoDetect =	RegisterTimer(ELAPSE_DETECT_VIDEO);	//���VIDEO
	iTimerHideControlId	= RegisterTimer(TIMER_HIDE_CONTROLS_ELAPSE);
 
	iTimerRefreshProgress	= RegisterTimer(ELAPSE_REFRESH_PROGRESS);

	pVideoSetup =   (GxxVedioSetup *)safeFindViewByName("VideoSetup");	//����������Ƶ
	pVideoSetup->setDraw(false);



 	pIpodList = (GxxIpodListGroup*)safeFindViewByName("IpodList");
	pIpodList->SetMessageView(this);

	
	m_iCurrentMediaMode = DBSEL_AUDIO;
	

	bIntial = false;

	iTimerFullScreenMovie = RegisterTimer(ELAPSE_FIVE_SECONDS);

	ipodPlayStatus = IpodHardware::IPOD_STOP;

	//���ڳ���IPOD��USBͬʱ�������������IPOD�����趨Ϊ0
	pIPodLib->Ipod_SetVolume(0);
	
}

void IPODActivity::HidePlayStatus()	//���ز���״̬
{
	pPicPlayStatus->setDraw(false);
	pPicPauseStatus->setDraw(false);
	pPicStopStatus->setDraw(false);
}

void IPODActivity::UpdatePlayStatus(int iPlayStatus)	//���²���״̬
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


void IPODActivity::StartFullScreenMovieWnd()		//��Ƶ���ڣ�ȫ��
{
	StartTimer(iTimerFullScreenMovie);
}

void IPODActivity::StopFullScreenMovieWnd()		//ֹͣ��Ƶ����
{
	StopTimer(iTimerFullScreenMovie);
}

void IPODActivity::ReStartFullScreenMovieWnd()		//���¿�ʼ��Ƶ����ȫ��
{
	StopTimer(iTimerFullScreenMovie);
	StartTimer(iTimerFullScreenMovie);
}




//��Ƶȫ��ʱ�������Ƶ����Ӧ����
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

void IPODActivity::FullScreen(bool bShowControl/* = true*/)		//ȫ��
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

//��ʾȫ��ʱ�Ŀؼ�
void IPODActivity::ShowFullControls()
{
	StopTimer(iTimerHideControlId);

	

	//��ʾ��Ƶȫ��ʱ�Ŀؼ�
	if(!pControlGroup_FullScreenControls->getDraw())
	{
		pControlGroup_FullScreenControls->setDraw(true);
	}
	AfxInvalidateRect(NULL);
	
	StartTimer(iTimerHideControlId);



}

void IPODActivity::ClearUserInterface()	//��ս���
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

	pPicMusicLogo->ResetIcon();	//�ָ�Ĭ��ͼƬ
}

void IPODActivity::SwitchUserInterface()	//�л�UI
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
			
			//��ʼ����Ƶ״̬��������Ƶ
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
	//pIpodList->InitFirstList();//ÿ�ν���list����ǰ��ĵ�һ��Ŀ¼��ʼ
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
	//���ڱ�������
	if( Activity::GetActiveActiviy() != (IPODActivity*)this)
	{
		return 0;
	}

	int iMsg = param1;
	switch(iMsg)
	{
	case HardwareBtnMatch::BACK_KEY:	//����
		{
			AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		}
		break;
	case HardwareBtnMatch::PLAY_KEY:	//��ͣ����
		{
			PlayAndPause();
		}
		break;
	case HardwareBtnMatch::PRE_KEY:	//��һ��
		{
			PrevVideo();
		}
		break;
	case HardwareBtnMatch::NEXT_KEY:	//��һ��
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
			if( !pIPodLib->ListBack() )	//���ط���˵�
			{
				pIpodList->BackToMenu();
			}	
			return TRUE;
		}

	case GX_LISTBOX_BUTTON_DOWNM:
		{
			int iItem = (int)lParam;
			
			bool ret = pIPodLib->IpodSelectList(iItem);
			if(ret)	//�������Ž���
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
			
			//���һ��ʱ��󣬲�����ˢ�¹������������������ʾ����ȷ
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
			
			if ((GxxAniLable *)wParam == pLabel_MainOrInfo)		//����������Ϣ�����л�
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

			if ((GxxAniLable *)wParam == pLabel_Setting)		//�趨
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
			if ((GxxAniLable *)wParam == pLabel_BrowseList)		//����
			{
				SwitchToListGroup();
			//	pIpodList->Invatelidate(-1);	//�ص���Ŀ¼
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pInc_Into_MainInterface)		//����������
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
			if ((GxxAniLable *)wParam == pLabel_ReturnMain)	//��С��Ļ
			{
				SubScreen();

				ReStartFullScreenMovieWnd();	//���¿�ʼ��Ƶ����ȫ��
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
		VolumeControl::SlowlyIncreaseVolume();	//��������

	}
	pIPodLib->SetPlaypause();

	//ý�����Ϳ��ܻ��б仯
//	DetectMediaMode();
}

void IPODActivity::NextVideo()
{
	if(iCurrentVideo == 0)	return;
	//��Ŀ������Ŀ����һ�£�Ŀ����ѭ��ʱ������
	//��ֹ�����һ��������
	if(iCurrentVideo == iTotalVideo && !bAllRepeat)
	{
		return;
	}

	//�л���Ƶʱ��������Ƶ����ֹ��Ƶ��
	if(m_iCurrentMediaMode == DBSEL_VIDEO)
	{
		video_source = 0;
		pMediaWnd->CloseVideo(true);
	}

	pIPodLib->IpodNext();

	//ý�����Ϳ��ܻ��б仯
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

	//�л���Ƶʱ��������Ƶ���ڣ���ֹ��Ƶ��
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

	//ý�����Ϳ��ܻ��б仯
	//DetectMediaMode();
}

void IPODActivity::SubScreen()	//��С��Ļ
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
	//���ڳ���IPOD��USBͬʱ��������������˳�IPODʱ��IPOD�����趨Ϊ0
	pIPodLib->Ipod_SetVolume(0);
}

void  IPODActivity::onResume()
{
	// �л�������ipod
	AVSET::ToIpod();

	VolumeControl::ApplyForVolumeControl(VolumeModuleId::IPOD);

	//�趨IPOD������
	pIPodLib->Ipod_SetVolume(30);

	pControl_group_IpodList->setDraw(false);
	
	MediaControl::SetMediaMode(CAMERA);

	CRect rcWnd;
	pMediaWnd->getCtrRect(rcWnd);
	//pMediaWnd->setDraw(false);
	MediaControl::SetMediaRect(rcWnd);

	
	
	if(!bIntial)	//����IPOD�󣬵�һ�ν���IPOD����
	{
		bIntial = true;

		video_source = NOVIDEO;
		pIPodLib->IpodPlay();
	}
	
	StartVideoDetect();	//���VIDEO

	StartFullScreenMovieWnd();		//��Ƶ���ڣ�ȫ��

	running = 1;
}

void IPODActivity::StartVideoDetect()	//���VIDEO
{
	StartTimer(iTimeVideoDetect);
}



void IPODActivity::onPause()
{
	SubScreen();	//��С��Ļ
	StopTimer(iTimeVideoDetect);

	StopFullScreenMovieWnd();		//ֹͣ��Ƶ����
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
	else if(nIDEvent == iTimerDetectIpod)	//���������û��IPOD
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

			//���¿�ʼ��ʱ
			StopTimer(iTimerFullScreenMovie);
			StartTimer(iTimerFullScreenMovie);
		}
	}
	//���һ��ʱ��󣬲�����ˢ�¹������������������ʾ����ȷ
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
					// iPod����
					pIPodLib->IpodPlay();
				}

				IpodListItemId = 0;
			}
			if (lParam == 1)
			{
				// iPod��Ȩ�ɹ�
				RETAILMSG(COUT_MSG, (TEXT("��Ȩ�ɹ�\r\n")));
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
				// iPod �γ�
				pIpodList->InitList();
				bIntial = false;
				m_iCurrentMediaMode = DBSEL_AUDIO;
				SwitchUserInterface();

				ClearUserInterface();	//��ս���

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
		ReStartFullScreenMovieWnd();	//���¿�ʼ��Ƶ����ȫ��

		//�ӳ��ؼ�����ʾʱ��
		if(pMediaWnd->IsFullScreen() && !pControlGroup_main->getDraw())
		{
			ShowFullControls();
		}
	}
	return Activity::DealCtrlMsg(message,wParam,lParam);
}



static RegisterHelp help("IPODActivity", IPODActivity::CreateControl);