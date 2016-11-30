#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "DiscActivity.h"
#include "WMMsg.h"
#include "AVSet.h"
#include "TimerManager.h"
#include "WheelMsg.h"


#include "GXNotify.h"
#include "VolumeControl.h"

#define TIMER_HIDE_CONTROLS 1
#define TIMER_HIDE_CONTROLS_ELAPSE 6000

#define TIMER_COMMAND_FAIL 2000
#define TIMER_DVD_DETECT 2000
#define ELAPSE_PLAY_PAUSE_STATUS 2000

#define DVD_DETECT 1
#define DVD_DETECT_ELAPSE 5000

#define ELAPSE_FIVE_SECONDS 5000

#define DEBUG_DVD 0



DiscActivity* DiscActivity::pThis;
Activity* DiscActivity::CreateControl()
{
	return new DiscActivity;
}

DiscActivity::DiscActivity()
{
	pThis = this;	//���������ָ��
	bClickPlayPauseLabel = false;
}

void DiscActivity::onCreate()
{
	
	VolumeControl::ApplayForPermission(VolumeModuleId::DISC, 0, L"disc");
	
	setContentView("layout\\dvd\\DiscPad.xml");
	Activity::onCreate();
	setBackColor(0xffff0000);

	pLabel_eject = (GxxAniLable*)safeFindViewByName("label_eject");
	pLabel_play_and_pause = (GxxAniLable*)safeFindViewByName("label_play_and_pause");
	pLabel_stop = (GxxAniLable*)safeFindViewByName("label_stop");
	pProgressVideoTime = (GxxProgressBar*)safeFindViewByName("ProgressVideoTime");
	pLabel_totaltime = (GxxAniLable*)safeFindViewByName("label_totaltime");
	pLabel_currentTime = (GxxAniLable*)safeFindViewByName("label_currentTime");

	pPicRepeatIcon = (GxxPicIcon*)safeFindViewByName("PicRepeatIcon");
	pPicRepeatOneIcon = (GxxPicIcon*)safeFindViewByName("PicRepeatOneIcon");
	pPicRepeatFIcon = (GxxPicIcon*)safeFindViewByName("PicRepeatFIcon");

	pPicCommandFail= (GxxPicIcon*)safeFindViewByName("PicCommandFail");		//����ʧ��ʱ����ʾ
	pPicCommandFail->setDraw(false);

	pLabel_ReturnMain = (GxxAniLable*)safeFindViewByName("label_ReturnMain");

	pMediaWnd = (TccMediaWndEx*)safeFindViewByName("moviewindow");
	pMediaWnd->SetFun(ClickMediaWnd, this);

	//���ü�ʻ�о�����
	GxxAniLable* pLabelWarnning = (GxxAniLable*)safeFindViewByName("LabelWarnning");
	pMediaWnd->SetWarning(pLabelWarnning, false);

	pControlGroup_main = (GxxControlGroup*)safeFindViewByName("ControlGroup_main");


	pControlGroup_fullScreen = (GxxControlGroup*)safeFindViewByName("ControlGroup_fullScreen");
	pControlGroup_fullScreen->setDraw(false);

	pControlGroup_FullScreenControls = (GxxControlGroup*)safeFindViewByName("ControlGroup_FullScreenControls");
	pControlGroup_FullScreenControls->setDraw(false);

	pControlGroup_KeyBoard = (GxxControlGroup*)safeFindViewByName("ControlGroup_KeyBoard");	//С����
	pLabel_KeyBoard_close = (GxxAniLable*)safeFindViewByName("Label_KeyBoard_close");	//�ر�
	pLabel_KeyBoard_up = (GxxAniLable*)safeFindViewByName("Label_KeyBoard_up");	//��
	pLabel_KeyBoard_left = (GxxAniLable*)safeFindViewByName("Label_KeyBoard_left");	
	pLabel_KeyBoard_right = (GxxAniLable*)safeFindViewByName("Label_KeyBoard_right");	
	pLabel_KeyBoard_down = (GxxAniLable*)safeFindViewByName("Label_KeyBoard_down");	
	//pLabel_KeyBoard_ToleftOrRight = (GxxAniLable*)safeFindViewByName("Label_KeyBoard_ToleftOrRight");	
	pLabel_KeyBoard_Toleft = (GxxAniLable*)safeFindViewByName("Label_KeyBoard_Toleft");
	pLabel_KeyBoard_ToRight= (GxxAniLable*)safeFindViewByName("Label_KeyBoard_ToRight");
	pLabel_KeyBoard_ToRight->setDraw(false);

	pLabel_PrevVideo = (GxxAniLable*)safeFindViewByName("Label_PrevVideo");	
	pLabel_NextVideo = (GxxAniLable*)safeFindViewByName("Label_NextVideo");	
	pLabel_VideoName = (GxxAniLable*)safeFindViewByName("Label_VideoName");

	pLabel_FastForwardText = (GxxAniLable*)safeFindViewByName("Label_FastForwardText");
	pLabel_FastForwardText->setDraw(false);

	pLabel_FastBackwardText = (GxxAniLable*)safeFindViewByName("Label_FastBackwardText");
	pLabel_FastBackwardText->setDraw(false);

	pLabel_FastForward = (GxxAniLable*)safeFindViewByName("Label_FastForward");
	pLabel_FastBackward = (GxxAniLable*)safeFindViewByName("Label_FastBackward");

	pLabel_SubTitle = (GxxAniLable*)safeFindViewByName("Label_SubTitle");
	pLabel_Audio = (GxxAniLable*)safeFindViewByName("Label_Audio");
	pLabel_Angle = (GxxAniLable*)safeFindViewByName("Label_Angle");
	pLabel_Repeat = (GxxAniLable*)safeFindViewByName("Label_Repeat");


	pLabel_TopTitleDiscType = (GxxAniLable*)safeFindViewByName("Label_TopTitleDiscType");
	pPicMusicLogo = (GxxPicIcon*)safeFindViewByName("PicMusicLogo");
	/*pLabel_titleDiscType = (GxxAniLable*)safeFindViewByName("Label_titleDiscType");*/

	pLabel_Page1 = (GxxAniLable*)safeFindViewByName("Label_Page1");
	pLabel_Page2 = (GxxAniLable*)safeFindViewByName("Label_Page2");

	pControlGroup_page1 = (GxxControlGroup*)safeFindViewByName("ControlGroup_page1");	
	pControlGroup_page2 = (GxxControlGroup*)safeFindViewByName("ControlGroup_page2");
	//pControlGroup_Label = (GxxControlGroup*)safeFindViewByName("ControlGroup_Label");
	pControlGroup_Info = (GxxControlGroup*)safeFindViewByName("ControlGroup_Info");

	pLabel_SwitchInfoOrMain  = (GxxAniLable*)safeFindViewByName("Label_SwitchInfoOrMain");

	pLabel_Menu  = (GxxAniLable*)safeFindViewByName("Label_Menu");
	pLabel_TopMenu  = (GxxAniLable*)safeFindViewByName("Label_TopMenu");

	pLabel_Enter = (GxxAniLable*)safeFindViewByName("Label_Enter");	

	pLabel_iconudlr = (GxxAniLable*)safeFindViewByName("label_iconudlr");
	pLabel_Key = (GxxAniLable*)safeFindViewByName("label_Key");

	pLabelToSetupAudio = (GxxAniLable*)safeFindViewByName("LabelToSetupAudio");
	pLabelToSetupDisplay = (GxxAniLable*)safeFindViewByName("LabelToSetupDisplay");

	pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");

	pLabel_Setting = (GxxAniLable*)safeFindViewByName("Label_Setting");

	pPicPlayStatus = (GxxPicIcon*)safeFindViewByName("PicPlayStatus");
	pPicPauseStatus = (GxxPicIcon*)safeFindViewByName("PicPauseStatus");
	pPicStopStatus = (GxxPicIcon*)safeFindViewByName("PicStopStatus");
	pPicPlayStatus->setDraw(false);
	pPicPauseStatus->setDraw(false);
	pPicStopStatus->setDraw(false);

	pVideoSetup =   (GxxVedioSetup *)safeFindViewByName("VideoSetup");	//����������Ƶ
	pVideoSetup->setDraw(false);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = DiscInfoNotify;
	GXNotify::RegisterNotifyHandler("disc_info", notify);
	
	notify.funNotify = MediaPlayInfoNotify;
	GXNotify::RegisterNotifyHandler("media_play_info", notify);

	notify.funNotify = SysmodeNotify;
	GXNotify::RegisterNotifyHandler("sysmode_info", notify);

	notify.funNotify = LoadDiscNotify;
	GXNotify::RegisterNotifyHandler("load_disc", notify);
	notify.funNotify = FileNameInfoNotify;
	GXNotify::RegisterNotifyHandler("filename_info", notify);
	notify.funNotify = FolderInfoNotify;
	GXNotify::RegisterNotifyHandler("folder_info", notify);
	notify.funNotify = FirstPostionInfoNotify;
	GXNotify::RegisterNotifyHandler("firstposition_info", notify);
	notify.funNotify = SecondPositionInfoNotify;
	GXNotify::RegisterNotifyHandler("secondposition_info", notify);
	notify.funNotify = NotifyEject;
	GXNotify::RegisterNotifyHandler("NotifyEject", notify);
	notify.funNotify = NotifyCommandFail;
	GXNotify::RegisterNotifyHandler("NotifyCommandFail", notify);
	//notify.funNotify = NotifyCommandAccept;
	//GXNotify::RegisterNotifyHandler("NotifyCommandAccept", notify);
	notify.funNotify = NotifyPlayInfo;
	GXNotify::RegisterNotifyHandler("dvd_play_info", notify);
	
	notify.funNotify = NotifyPowerOff;
	GXNotify::RegisterNotifyHandler("power_off", notify);

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);
	
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

	CRect rcWnd;
	pMediaWnd->getCtrRect(rcWnd);
	MediaControl::SetMediaRect(rcWnd);


	tvSystem = NOVIDEO;

	iCurrentMediaType = MOVIE;
	
	dvdControl.Init(AfxGetHWND());
	dvdControl.PowerOn();

	iTimerHideControlId	= RegisterTimer(TIMER_HIDE_CONTROLS_ELAPSE);
	iTimerCommandFail	= RegisterTimer(TIMER_COMMAND_FAIL);
	
	iTimerPlayDVD = RegisterTimer(1500);
	
	bIsDVDEnable = false;	//Ĭ��DVD������
	Activity::EnableActivity("DiscActivity",(bool)bIsDVDEnable);

	iTimerDVDEnable	= RegisterTimer(TIMER_DVD_DETECT);
	StartTimer(iTimerDVDEnable);

	iTimerPlayPauseStatus	= RegisterTimer(ELAPSE_PLAY_PAUSE_STATUS);	//��ʾ������ʱ��״̬
	iTimerFullScreenMovie = RegisterTimer(ELAPSE_FIVE_SECONDS);

	UpdateUI(NONE);

}

//��Ƶȫ��ʱ�������Ƶ����Ӧ����
void DiscActivity::ClickMediaWnd(GxxView *p, void *dwParam)
{
	DiscActivity* pThis = (DiscActivity*)dwParam;
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

void DiscActivity::StartFullScreenMovieWnd()		//��Ƶ���ڣ�ȫ��
{
	StartTimer(iTimerFullScreenMovie);
}

void DiscActivity::StopFullScreenMovieWnd()		//ֹͣ��Ƶ����
{
	StopTimer(iTimerFullScreenMovie);
}

void DiscActivity::ReStartFullScreenMovieWnd()		//���¿�ʼ��Ƶ����ȫ��
{
	StopTimer(iTimerFullScreenMovie);
	StartTimer(iTimerFullScreenMovie);
}

LRESULT DiscActivity::NotifyEject(DWORD param1, DWORD param2)
{

	dvdControl.DVDEject();

	if((Activity::GetActiveActiviy() == (DiscActivity *)this) && iCurrentMediaType == MOVIE)
	{
		LessenScreen();

		ReStartFullScreenMovieWnd();
	}

	return 0;
}

LRESULT DiscActivity::NotifyPlayInfo(DWORD param1, DWORD param2)
{

	PLAY_INFO* play_info = (PLAY_INFO*)param1;
	BYTE bytePlayMode = play_info->PlayMode;
	RETAILMSG(COUT_MSG, (TEXT("Play Mode=%d\r\n"), bytePlayMode));

	if(ucharPlayMode != bytePlayMode)	//����̽�ⲥ��ģʽ�Ƿ����˱仯
	{
		ucharPlayMode = bytePlayMode;	//���䲥��״̬

		switch(bytePlayMode)
		{
		case 0x04:	//play
			{
				//���ڿ�����0x02ʱ�����������˾�����������ʱ���ָ�����
				VolumeControl::ApplyForVolumeControl(VolumeModuleId::DISC);

				//����ǰ����˲�����ͣ������Ĳ���״̬����������
				if(!sysConfig.bMute && bClickPlayPauseLabel)
				{
					VolumeControl::UnMuteAndSlowlyIncreaseVolume();

					bClickPlayPauseLabel = false;	//�ָ�����Ĭ��ֵ
				}
				else if(!sysConfig.bMute)
				{
					AVSET::UnMute();	//�ָ�����
				}
				

				pLabel_FastForwardText->setDraw(false);
				pLabel_FastBackwardText->setDraw(false);
				pPicPlayStatus->setDraw(true);
				pPicPauseStatus->setDraw(false);
				pPicStopStatus->setDraw(false);
				//pPicPauseStatus->setDraw(false);
				StopTimer(iTimerPlayPauseStatus);
				StartTimer(iTimerPlayPauseStatus);

				
			}
			break;
		case 0x05:	//pause
			{
				if(!sysConfig.bMute)
				{
					AVSET::UnMute();	//�ָ�����
				}

				pPicPauseStatus->setDraw(true);
				pPicPlayStatus->setDraw(false);
				pPicStopStatus->setDraw(false);
				StopTimer(iTimerPlayPauseStatus);

				bClickPlayPauseLabel = false;
			
				
			}
			break;
		case 0x02:	//stop
			{
				pPicStopStatus->setDraw(true);
				pPicPauseStatus->setDraw(false);
				pPicPlayStatus->setDraw(false);
				StopTimer(iTimerPlayPauseStatus);

			}
			break;
		case 0x0a:	//���
			{
				pLabel_FastBackwardText->setDraw(false);
				pLabel_FastForwardText->setDraw(true);
				//AfxInvalidateRect(&pLabel_FastForwardText->m_ActRect);



				BYTE byteSpeed = play_info->Speed;
				switch(byteSpeed)
				{
				case 0x02:
					{

						pLabel_FastForwardText->SetText(L"X2", true);
					}
					break;
				case 0x08:
					{
						pLabel_FastForwardText->SetText(L"X8", true);
					}
					break;
				case 0x10:
					{
						pLabel_FastForwardText->SetText(L"X16", true);
					}
					break;
				case 0x20:
					{
						pLabel_FastForwardText->SetText(L"X32", true);
					}
					break;
				}

				break;
			}
		case 0x0B:	//����
			{
				pLabel_FastForwardText->setDraw(false);

				pLabel_FastBackwardText->setDraw(true);

				BYTE byteSpeed = play_info->Speed;
				if(byteSpeed == 0x02)
				{
					pLabel_FastBackwardText->SetText(L"X2", true);
				}
				if(byteSpeed == 0x08)
				{
					pLabel_FastBackwardText->SetText(L"X8",true);
				}
				if(byteSpeed == 0x10)
				{
					pLabel_FastBackwardText->SetText(L"X16", true);
				}
				if(byteSpeed == 0x20)
				{
					pLabel_FastBackwardText->SetText(L"X32", true);
				}
				break;
			}
		}
	}

	switch(bytePlayMode)
	{
	case 0x0a:	//���
		{
			pLabel_FastBackwardText->setDraw(false);
			pLabel_FastForwardText->setDraw(true);
			//AfxInvalidateRect(&pLabel_FastForwardText->m_ActRect);



			BYTE byteSpeed = play_info->Speed;
			switch(byteSpeed)
			{
			case 0x02:
				{

					pLabel_FastForwardText->SetText(L"X2", true);
				}
				break;
			case 0x08:
				{
					pLabel_FastForwardText->SetText(L"X8", true);
				}
				break;
			case 0x10:
				{
					pLabel_FastForwardText->SetText(L"X16", true);
				}
				break;
			case 0x20:
				{
					pLabel_FastForwardText->SetText(L"X32", true);
				}
				break;
			}

			break;
		}
	case 0x0B:	//����
		{
			pLabel_FastForwardText->setDraw(false);

			pLabel_FastBackwardText->setDraw(true);

			BYTE byteSpeed = play_info->Speed;
			if(byteSpeed == 0x02)
			{
				pLabel_FastBackwardText->SetText(L"X2", true);
			}
			if(byteSpeed == 0x08)
			{
				pLabel_FastBackwardText->SetText(L"X8",true);
			}
			if(byteSpeed == 0x10)
			{
				pLabel_FastBackwardText->SetText(L"X16", true);
			}
			if(byteSpeed == 0x20)
			{
				pLabel_FastBackwardText->SetText(L"X32", true);
			}
			break;
		}
	}
	

	BYTE byteRepeatMode = play_info->RepeatMode;
	RETAILMSG(COUT_MSG, (TEXT("repeatmode=%d\r\n"), byteRepeatMode));

	pPicRepeatIcon->setDraw(false);
	pPicRepeatOneIcon->setDraw(false);
	pPicRepeatFIcon->setDraw(false);

	switch(byteRepeatMode)
	{
	case 0x00:	//The setting of the Repeat System is OFF.
		{
			pPicRepeatIcon->setDraw(false);
			pPicRepeatOneIcon->setDraw(false);
			pPicRepeatFIcon->setDraw(false);
		}
		break;
	case 0x11:	//Second Position RPT
		{
			

			pPicRepeatOneIcon->setDraw(true);
		}
		break;
	case 0x12:	//First Position RPT
		{
			

			pPicRepeatFIcon->setDraw(true);
		}
		break;
	case 0x13:	//Disc RPT
		{

			pPicRepeatIcon->setDraw(false);

		}
		break;
	case 0x41:
		{
			//ASSERT(false);
		}
		break;
	case 0x42:
		{
			//ASSERT(false);
		}
		break;
	}
	if( Activity::GetActiveActiviy() == (DiscActivity*)this)
	{
		AfxInvalidateRect(NULL);
	}
	
	
	return 0;
}

//LRESULT DiscActivity::NotifyCommandAccept(DWORD param1, DWORD param2)
//{
//	int iGroupId = param1;
//	int iSubId = param2;
//	//GxxString strTip;
//
//	if(iGroupId == 0x80)
//	{
//		switch(iSubId)
//		{
//			return 0;
//		}
//		//һ��ʱ����������
//		//pWindow->SetTimer(ACTION_RESULT_TIP, ACTION_RESULT_TIP_ELAPSE, NULL);
//	}
//
//	return 0;
//}


LRESULT DiscActivity::LoadDiscNotify(DWORD param1, DWORD param2)
{
	static int load_status = 0;
	if (param1 == 0x3)
	{
		// pushback
		load_status = 3;

		UpdateUI(NONE);
		AfxPostMessage(CTR_INTO_DVD_INTERFACE, 0, 0);	//������ת��DVD�������Ϣ
	}
	if (param1 == 0x4)
	{
		load_status = 4;

		//����DVDģʽ��ת��DVDģʽ
		if( Activity::GetActiveActiviy() != (DiscActivity *)this)
		{
			UpdateUI(NONE);
			AfxPostMessage(CTR_INTO_DVD_INTERFACE, 0, 0);	//������ת��DVD�������Ϣ
		}
		
		//ASSERT(false);
	}
	if (param1 == 0x5)
	{
		if (load_status == 4)
		{
			if( Activity::GetActiveActiviy() == (DiscActivity *)this)
			{
				dvdControl.EnterDvd();
				Sleep(100);
				VolumeControl::SlowlyIncreaseVolume();	//��������
				dvdControl.Play();
			}
			else
			{
				//����DVD����ʱ��������
				dvdControl.LeaveDvd();
			}
		}                    
		
	}
	if (param1 == 0x0)
	{
		load_status = 0;
		tvSystem = NOVIDEO;
		//GXNotify::SendNotify("dvd_loader", 0, 0);
		
		if( Activity::GetActiveActiviy() == (DiscActivity *)this)
		{
			AfxPostMessage(CTR_EXIT_DVD_INTERFACE, 0, 0);	//�����˳�DVD�������Ϣ
		}
		
		
	}
	return 0;
}

//��ʾȫ��ʱ�Ŀؼ�
void DiscActivity::ShowFullControls()
{
	StopTimer(iTimerHideControlId);

	
	if(!pControlGroup_FullScreenControls->getDraw())
	{
		pControlGroup_FullScreenControls->setDraw(true);
	}
	AfxInvalidateRect(&(pThis->m_ActRect));
	StartTimer(iTimerHideControlId);

}


 
BOOL DiscActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	//case MCU_POPMENU:
	//	{
	//		if( Activity::GetActiveActiviy() == this)
	//		{
	//			LessenScreen();	//��С��Ļ
	//		} 
	//		return TRUE;
	//	}
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxAniLable *)wParam == pLabel_SwitchInfoOrMain)	
			{
				bool bMainShow = pControlGroup_main->getDraw();
				bool pInfoShow = pControlGroup_Info->getDraw();
				
				if(bMainShow && !pInfoShow)
				{
					bool pMediaWndShow =  pMediaWnd->getDraw();
					if(pMediaWndShow)
					{
						pMediaWnd->setDraw(false);	//������Ƶ����
					}
					

					pControlGroup_main->setDraw(false);
					pControlGroup_Info->setDraw(true);
					Activity::overridePendingTransition(pControlGroup_main,pControlGroup_Info,Activity::s_hAniRotateY);
					
					if(pMediaWndShow)
					{
						pMediaWnd->setDraw(true);	//������Ƶ����
					}
					
				}
				else if(!bMainShow && pInfoShow)
				{
					bool pMediaWndShow =  pMediaWnd->getDraw();
					if(pMediaWndShow)
					{
						pMediaWnd->setDraw(false);	//������Ƶ����
					}

					pControlGroup_main->setDraw(true);
					pControlGroup_Info->setDraw(false);
					Activity::overridePendingTransition(pControlGroup_Info,pControlGroup_main,Activity::s_hAniRotateY);
					
					if(pMediaWndShow)
					{
						pMediaWnd->setDraw(true);	//������Ƶ����
					}
				}
				AfxInvalidateRect(NULL);

				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pLabel_Setting)	
			{
				if(pVideoSetup->getDraw())
				{
					pVideoSetup->setDraw(false);
				}
				else
				{
					pVideoSetup->setDraw(true);
					if(pControlGroup_KeyBoard->getDraw())	//С������ʾʱ������
					{
						pControlGroup_KeyBoard->setDraw(false);
					}
					
				}
				//CRect rect;
				//pVideoSetup->getCtrRect(rect);
				AfxInvalidateRect(NULL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pInc_Into_MainInterface)	
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_eject)	//����
			{
				dvdControl.DVDEject();
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_FastForward)	//���
			{
				//���ڿ��Ϊ0x02ʱ�������������農��
				AVSET::SetVolume(0);
				dvdControl.FastF();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_FastBackward)	//����
			{
				dvdControl.FastR();
				return TRUE;
			}

			if ((GxxAniLable *)wParam == pLabel_play_and_pause)	//��ͣ����
			{
				AVSET::Mute();	//������������������Ĵ��������������������DVD��ͣʱ������������
				dvdControl.DVDPlayPause();

				bClickPlayPauseLabel = true;	//����ǰ����˲�����ͣ������Ĳ���״̬����������
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_stop)	//ֹͣ
			{
				dvdControl.DVDStop();
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pLabel_iconudlr)	//ȫ��
			{
				if(iCurrentMediaType == MOVIE)
				{
					FullScreen();
				}
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_ReturnMain)	//��С��Ļ
			{
				LessenScreen();	//��С��Ļ

				pPicCommandFail->setMoveRect(0, 230);

				ReStartFullScreenMovieWnd();		//���¿�ʼ��Ƶ����ȫ��

				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key)	//��ʾ���ؼ���
			{
				if(!pControlGroup_KeyBoard->getDraw())	
				{
					pControlGroup_KeyBoard->setDraw(true);
					if(pVideoSetup->getDraw())
					{
						pVideoSetup->setDraw(false);
					}
					ShowFullControls();
				}
				else
				{
					pControlGroup_KeyBoard->setDraw(false);
					AfxInvalidateRect(&m_ActRect);
				}
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyBoard_close)	//���ؼ���
			{
				if(pControlGroup_KeyBoard->getDraw())
				{
					pControlGroup_KeyBoard->setDraw(false);
					AfxInvalidateRect(&m_ActRect);
				}
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyBoard_up)	
			{
				ShowFullControls();
				dvdControl.KeyUp();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyBoard_left)	
			{
				ShowFullControls();
				dvdControl.KeyLeft();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyBoard_right)	
			{
				ShowFullControls();
				dvdControl.KeyRight();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyBoard_down)	
			{
				ShowFullControls();
				dvdControl.KeyDown();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Enter)	
			{
				ShowFullControls();
				
				dvdControl.KeyEnter();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyBoard_Toleft)	//����
			{
				pControlGroup_KeyBoard->setMoveRect(-220,0);
				pLabel_KeyBoard_Toleft->setDraw(false);
				pLabel_KeyBoard_ToRight->setDraw(true);

				AfxInvalidateRect(NULL);
				return TRUE;
			}	
			if ((GxxAniLable *)wParam == pLabel_KeyBoard_ToRight)	//����
			{
				pControlGroup_KeyBoard->setMoveRect(220,0);
				pLabel_KeyBoard_Toleft->setDraw(true);
				pLabel_KeyBoard_ToRight->setDraw(false);

				//RECT rc;
				//pControlGroup_KeyBoard->getCtrRect(rc);
				AfxInvalidateRect(NULL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_PrevVideo)	//��һ��
			{
				dvdControl.Skipb();
				return TRUE;
			}	
			if ((GxxAniLable *)wParam == pLabel_NextVideo)	//��һ��
			{
				dvdControl.Skipf();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SubTitle)	//��Ļ
			{
				dvdControl.DVDSubp_key();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Audio)		//����
			{
				dvdControl.DVDAudio_key();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Angle)		//�Ƕ�
			{
				dvdControl.DVDANGLE_KEY();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Repeat)		//ѭ��
			{
				dvdControl.DiscRepeat_Key();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Page1)		//��ҳ
			{
				pControlGroup_page1->setDraw(false);
				pControlGroup_page2->setDraw(true);
				AfxInvalidateRect(&m_ActRect);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Page2)		//��ҳ
			{
				pControlGroup_page1->setDraw(true);
				pControlGroup_page2->setDraw(false);
				AfxInvalidateRect(&m_ActRect);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_TopMenu)		
			{
				dvdControl.DVDTopMenu();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Menu)		
			{
				dvdControl.DVDMenu();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelToSetupAudio)	//��ת�����ý���
			{
				Activity::startActivity(this,"SetupActivity","2_sound_setup");
				return true;
			}
			if ((GxxAniLable *)wParam == pLabelToSetupDisplay)	//��ת�����ý���
			{
				Activity::startActivity(this,"SetupActivity","2_display_setup");
				return true;
			}
			

		}
		return FALSE;
	default:
		return FALSE;
	}
}

void DiscActivity::FullScreen(bool bShowControl/* = true*/)		//ȫ��
{
	if(iCurrentMediaType == MOVIE)
	{
		AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);

		pPicCommandFail->setMoveRect(0, -230);

		pControlGroup_main->setDraw(false);
		pMediaWnd->SetFullScreen();

		if(!pControlGroup_fullScreen->getDraw())
		{
			pControlGroup_fullScreen->setDraw(true);

			pControlGroup_FullScreenControls->setDraw(false);

		}

		if(bShowControl)
		{
			ShowFullControls();
		}
		if( Activity::GetActiveActiviy() == (DiscActivity*)this)
		{
			AfxInvalidateRect(NULL);
		}
	}
}

void DiscActivity::LessenScreen()	//��С��Ļ
{
	if( Activity::GetActiveActiviy() == (DiscActivity*)this)
	{
		AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);
		pMediaWnd->ReductionScreen();
		pControlGroup_fullScreen->setDraw(false);

		if(!pControlGroup_main->getDraw() && !pControlGroup_Info->getDraw())
		{
			pControlGroup_main->setDraw(true);
		}


		AfxInvalidateRect(&m_ActRect);
	}
}

void  DiscActivity::onStart()
{
	//��֪�����򣬽���ȫ��
	if( Activity::GetActiveActiviy() == (DiscActivity*)this)
	{
		if(pMediaWnd->IsFullScreen())
		{
			AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);
		}

	}
}

void  DiscActivity::onResume()
{
	AVSET::ToDVD();


	//��һ��ʱ����һ��ʱ�䣬�ٲ���DVD��
	//��Ϊ��һ�ο���DVD��о������Ӧ
	static bool bInital = false;
	if(!bInital)
	{
		bInital = true;
		StartTimer(iTimerPlayDVD);
	}
	

	CRect rcWnd;
	pMediaWnd->getCtrRect(rcWnd);
	MediaControl::SetMediaRect(rcWnd);
	// �л���cameraģʽ
	MediaControl::SetMediaMode(CAMERA);
	
	bool dvdin = IsDiscIn();
	if(dvdin != bIsDVDEnable)
	{
		bIsDVDEnable = dvdin;
		Activity::EnableActivity("DiscActivity",(bool)bIsDVDEnable);
	}
	RETAILMSG(COUT_MSG, (TEXT("bDiscIn = %d\r\n"), dvdin));
	dvdControl.EnterDvd();
	Sleep(300);
	dvdControl.Play();
	dvdControl.Play();
 
	//�趨����
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::DISC);

	
	// ������Ƶ��ʽ
	int tv = NOVIDEO;
	if (tv = SourceCheck())
	{
		MediaControl::StopCamera();
		MediaControl::InitCamera(tv);
		// ��ʼ��Ƶ
		MediaControl::StartCamera();
		RETAILMSG(COUT_MSG, (TEXT("tv = %d\r\n"), tv));
	}
	
	ucharPlayMode = 255;	//��ʼ������״̬
	
}

BOOL DiscActivity::IsDiscIn()
{
	return dvdControl.IsDiscIn();
}

void DiscActivity::onPause()
{
	//���ڿ�����0x02ʱ�����������˾�����������ʱ���ָ�����
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::DISC);

	AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);

	//if( Activity::GetActiveActiviy() == (DiscActivity*)this)
	//{
	//	LessenScreen();	//��С��Ļ
	//}
	
	StopFullScreenMovieWnd();

	
	//MediaControl::PauseCamera();
	

	//Ϊ�˷�ֹ�������ͼ��Ĳ���״̬��������һ������
	bool dvdin = IsDiscIn();
	bIsDVDEnable = dvdin;
	Activity::EnableActivity("DiscActivity",(bool)bIsDVDEnable);

}

void DiscActivity::onStop()
{
	tvSystem = NOVIDEO;
	//dvdControl.DVDStop();
	dvdControl.LeaveDvd();
	MediaControl::StopCamera();

	
}

LRESULT DiscActivity::NotifyCommandFail(DWORD param1, DWORD param2)
{
	int iGroupId = param1;
	int iSubId = param2;
	GxxString strTip;


	if(iGroupId == 0x80)
	{
		switch(iSubId)
		{

		case 0x22:	//ֹͣ
		case 0x26:	//���
		case 0x27:	//����
		case 0x33:	//����/��ͣ
		case 0x2f:	//��һ��
		case 0x30:	//��һ��
		case 0x41:	//����	
		case 0x42:	//��Ļ
		case 0x46:	//�˵�
		case 0x47:	//Ŀ¼
		case 0x51:	//ѭ��
		case 0x62:	//��������
		case 0x65:	//�س�
			{
				pPicCommandFail->setDraw(true);
				CRect rc ;
				pPicCommandFail->getCtrRect(rc);
				AfxInvalidateRect(&rc);
				StartTimer(iTimerCommandFail);
				break;
			}

		}
	}
	//RETAILMSG(1, (TEXT("fail command = %d, %d"), iGroupId, iSubId));

	return 0;
}

LRESULT DiscActivity::DiscInfoNotify(DWORD param1, DWORD param2)
{
	
	DISC_INFO* pInfo = (DISC_INFO*)param1;
	//RETAILMSG(DEBUG_DVD, (TEXT("��Ƭ���� = %d\r\n"), pInfo->PhyMedia));
	// ��Ƭ����
	switch(pInfo->PhyMedia)
	{
	case 0x00:
		{
			// �޵�
			strDiscType = L"NONE";
			UpdateUI(NONE);
			break;
		}
	case 0x01:
		{
			// CDDA

			// �����CDDA,��Ҫ��ȡ CD track ��Ϣ
			//RETAILMSG(DEBUG_DVD, (TEXT("CDDA : start = %d, end = %d\r\n"), pInfo->CDDA_block.StartTrackNo, pInfo->CDDA_block.EndTrackNo));
			/*pDvdList->DeleteAllItem();
			for (int i=0;i<pInfo->CDDA_block.EndTrackNo;i++)
			{
				CStdString str;
				str.Format(L"Track%d", i+1);
				InsertCDList(str, 0);
			}

			ToList(NULL);*/
			strDiscType = L"CDDA";
			UpdateUI(MUSIC);
			
			break;
		}
	case 0x02:
		{
			// CDROM
			if (pInfo->SetMediaType == MEDIATYPE_VCD)
			{

				//ToMenu(NULL);
				strDiscType = L"CDROM";
				UpdateUI(MOVIE);
				
			}
			else
			{
				//ToList(NULL);
				strDiscType = L"CDROM";
				UpdateUI(MUSIC);
				
			}
			break;
		}
	case 0x03:
		{
			// Enhanced CD
		//	ToList(NULL);
			strDiscType = L"CD";
			UpdateUI(MUSIC);
			
			break;
		}
	case 0x04:
		{
			// Mixed CD
		//	ToList(NULL);
			strDiscType = L"CD";
			UpdateUI(MUSIC);
			
			break;
		}
	case 0x21:
		{
			// DVD ROM
		//	ToMenu(NULL);
			strDiscType = L"DVD";
			UpdateUI(MOVIE);
			ReStartFullScreenMovieWnd();	//��Ƶ���ڣ�ȫ��
			break;
		}
	case 0x22:
		{
			// DVD-R
			
		//	ToMenu(NULL);
			strDiscType = L"DVD";
			UpdateUI(MOVIE);
			ReStartFullScreenMovieWnd();	//��Ƶ���ڣ�ȫ��
			break;
		}
	case 0x23:
		{
			// DVD-R (General / Authoring) disc
		//	ToMenu(NULL);
			strDiscType = L"DVD";
			UpdateUI(MOVIE);
			ReStartFullScreenMovieWnd();	//��Ƶ���ڣ�ȫ��
			break;
		}
	case 0x24:
		{
			// DVD-RW
		//	ToMenu(NULL);
			strDiscType = L"DVD";
			UpdateUI(MOVIE);
			ReStartFullScreenMovieWnd();	//��Ƶ���ڣ�ȫ��
			break;
		}
	case 0x25:
		{
			// DVD_RAM
		//	ToMenu(NULL);
			strDiscType = L"DVD";
			UpdateUI(MOVIE);
			ReStartFullScreenMovieWnd();	//��Ƶ���ڣ�ȫ��
			break;
		}
	case 0x26:
		{
			// DVD+R
		//	ToMenu(NULL);
			strDiscType = L"DVD";
			UpdateUI(MOVIE);
			ReStartFullScreenMovieWnd();	//��Ƶ���ڣ�ȫ��
			break;
		}
	case 0x27:
		{
			// DVD+RW
		//	ToMenu(NULL);
			strDiscType = L"DVD";
			UpdateUI(MOVIE);
			ReStartFullScreenMovieWnd();	//��Ƶ���ڣ�ȫ��
			break;
		}
	case 0x7F:
		{
			// unknown
			break;
		}
	}
//	RETAILMSG(DEBUG_DVD, (TEXT("pInfo->SetMediaType = %d\r\n"), pInfo->SetMediaType));
	switch(pInfo->SetMediaType)
	{
	case MEDIATYPE_INVALID:
		{
			break;
		}
	case MEDIATYPE_CDDA:
		{
			break;
		}
	case MEDIATYPE_VCD:
		{
			int totaltime = pInfo->VCD_block.TimeMinute*60 + pInfo->VCD_block.TimeSecond;
			GxxString str;
			str.TimeStr(totaltime);
			pLabel_totaltime->SetText(str.GetData(), true);
			pProgressVideoTime->SetRange(0, totaltime);

			break;
		}
	case MEDIATYPE_COMPRESS:
		{
			// ���ݵ�
			// ���ļ���,����Ŀ
			break;
		}
	case MEDIATYPE_DVDV:
		{
			break;
		}
	case MEDIATYPE_UPDATE:
		{
			break;
		}
	}
	//pWindowLoading->ShowWindow(0, 1);
	//GXNotify::SendNotify("dvd_loader", 1, 0);
	//if(pInfo->PhyMedia != 0x00 )//|| pInfo->SetMediaType != 0x00)
	//{
	//	
	//}
	
	return 0;
}

LRESULT DiscActivity::FirstPostionInfoNotify(DWORD param1, DWORD param2)
{
	FIRSTPOSITION_INFO *pInfo = (FIRSTPOSITION_INFO*)param1;
	switch(param2)
	{
	case MEDIATYPE_CDDA:
		{
			break;
		}
	case MEDIATYPE_VCD:
		{
			break;
		}
	case MEDIATYPE_COMPRESS:
		{
			// ��ǰ���ŵ��ļ���,�͵�ǰ���ŵ��ļ������ж�����Ŀ
			// folder 1 = root
			// ���ֻ��2��foler,�Ͳ���ʾ����
			//pDvdList->DeleteAllItem();
			//if (pInfo->FirstPositionNo == 1)
			//{
			//	// �����ļ���
			//	for (int i=0;i<dvdControl.disc_info.DATA_block.FolderNs-1;i++)
			//	{
			//		GxxString str;
			//		str.Format(L"Folder%d", i+1);
			//		RETAILMSG(DEBUG_DVD, (TEXT("Folder = %s"), str.GetData()));
			//		//InsertList(str, FileItem::FILETYPE_FOLDER);
			//	}
			//}
			//if (pInfo->FirstPositionNo > 1)
			//{
			//	if (dvdControl.disc_info.DATA_block.FolderNs > 2)
			//	{
			//		//InsertList(L"", FileItem::FILETYPE_BACK);
			//	}
			//}
			//for (int i=0;i<pInfo->SecondPositionNs;i++)
			//{
			//	GxxString str;
			//	str.Format(L"Track%d", i+1);
			//	RETAILMSG(DEBUG_DVD, (TEXT("Track = %s\r\n"), str.GetData()));
			//	//InsertList(str, FileItem::FILETYPE_FILTER);
			//}
			////pDvdList->Invalidate(1);
			////call_file_name_info(dvdControl.firstpostion_info.FirstPositionNo, 0, 0, 0, 5);
			//RETAILMSG(1, (TEXT("folder = %d, file = %d\r\n"), pInfo->FirstPositionNo, pInfo->SecondPositionNs));
			break;
		}
	case MEDIATYPE_DVDV:
		{
			GxxString str;
			str.TimeStr(pInfo->DVDV_block.TimeHour*3600 + pInfo->DVDV_block.TimeMinute*60 + pInfo->DVDV_block.TimeSecond);
			pLabel_totaltime->SetText(str.GetData(), true);		
			pProgressVideoTime->SetRange(0, pInfo->DVDV_block.TimeHour*3600 + pInfo->DVDV_block.TimeMinute*60 + pInfo->DVDV_block.TimeSecond);
			break;
		}
	}
	return 0;
}

LRESULT DiscActivity::SecondPositionInfoNotify(DWORD param1, DWORD param2)
{
	SECONDPOSITION_INFO	*pInfo = (SECONDPOSITION_INFO*)param1;
	switch(param2)
	{
	case MEDIATYPE_CDDA:	// cdda
		{
			CStdString str;
			str.Format(L"Track%d", pInfo->SecondPositionNo);
			pLabel_VideoName->SetText(str.GetData(), true);
			//RETAILMSG(DEBUG_DVD, (TEXT("Track = %s \r\n"), str.GetData()));

			/*if (pDvdList->GetSelected() != pInfo->SecondPositionNo-1)
			{
				pDvdList->SetItemStatus(pDvdList->GetSelected(), 0);
				pDvdList->SetItemStatus(pInfo->SecondPositionNo-1, LVIS_SELECTED);
				pDvdList->EnsureVisible(pInfo->SecondPositionNo-1);
				pDvdList->Invalidate(1);
			}*/

			str.Format(L"%02d:%02d", pInfo->CDDA_block.TimeMinute, pInfo->CDDA_block.TimeSecond);
			pLabel_totaltime->SetText(str.GetData(), true);
			pProgressVideoTime->SetRange(0, pInfo->CDDA_block.TimeMinute*60 + pInfo->CDDA_block.TimeSecond);

			// ��ȡcdda��Ϣ

			break;
		}
	case MEDIATYPE_VCD:	// vcd
		{
			break;
		}
	case MEDIATYPE_COMPRESS:	// compress
		{
			// ������ڵ�ǰ�ļ���
			GxxString str;
			if (1)
			{
				str.Format(L"Track%d", pInfo->SecondPositionNo);
				//RETAILMSG(DEBUG_DVD, (TEXT("Track = %s \r\n"), str.GetData()));
				pLabel_VideoName->SetText(str.GetData(),true);
			}

			str.Format(L"%02d:%02d", pInfo->DATA_block.TimeMinute, pInfo->DATA_block.TimeSecond);
			pLabel_totaltime->SetText(str.GetData(), true);
			pProgressVideoTime->SetRange(0, pInfo->DATA_block.TimeMinute*60 + pInfo->DATA_block.TimeSecond);

			if (pInfo->DATA_block.VideoType != 0)
			{
				// ��Ƶ
			}
			//call_file_name_info(dvdControl.firstpostion_info.FirstPositionNo, 1, 0, 0, 5);
			// ��ȡID3 ��Ϣ
			call_file_name_info(dvdControl.firstpostion_info.FirstPositionNo, dvdControl.secondposition_info.SecondPositionNo, 1, 0, 0);
			break;
		}
	case MEDIATYPE_DVDV:	// dvdv
		{
			break;
		}
	}
	return 0;
}

LRESULT DiscActivity::FileNameInfoNotify(DWORD param1, DWORD param2)
{
	static BYTE FileName[70];
	static TCHAR wFileName[34];
	FILENAME_INFO *pInfo = (FILENAME_INFO*)param1;
	if (pInfo->PageNo == 1)
	{
		memset(FileName, 0, 64);
		memset(wFileName, 0, 34*2);
	}
	for (int i=0;i<10;i++)
	{
		FileName[(pInfo->PageNo-1)*10+i] = pInfo->FILENAME[i];
	}
	for (int i=0;i<5;i++)
	{
		wFileName[(pInfo->PageNo-1)*5+i] = (pInfo->FILENAME[i*2]<<8) + pInfo->FILENAME[i*2+1];
	}
	if (pInfo->PageNo > 0 && pInfo->PageNo < 7)
	{
		if(!call_file_name_info(dvdControl.firstpostion_info.FirstPositionNo, dvdControl.secondposition_info.SecondPositionNo, pInfo->PageNo+1, 0, 0))
		{
			//ASSERT(FALSE);
		}
	}
	//if (pInfo->PageNo == 7)
	{
		GxxString sFileName1;
		GxxString sFileName2;
		GxxString sFileName3;
		sFileName1.FromAscii((char*)FileName);
		sFileName3 = wFileName;
		//RETAILMSG(DEBUG_DVD, (TEXT("sFileName3 = %s \r\n"), sFileName3.GetData()));
		pLabel_VideoName->SetText(sFileName3.GetData(), true);
	}

	return 0;
}

LRESULT DiscActivity::FolderInfoNotify(DWORD param1, DWORD param2)
{
	//FOLDER_INFO	*pInfo = (FOLDER_INFO*)param1;
	//if (pInfo->folder_info_folder_block.UpperFolderNo == 0xFFFF)
	//{
	//}
	//else
	//{
	//	if (dvdControl.disc_info.DATA_block.FolderNs > 2)
	//	{
	//		//pDvdList->DeleteAllItem();
	//		//InsertList(L"", FileItem::FILETYPE_BACK);
	//		GxxString str;
	//		for (int i=0;i<pInfo->folder_info_folder_block.FileNs;i++)
	//		{
	//			str.Format(L"Track%d", i+1);
	//			RETAILMSG(DEBUG_DVD, (TEXT("Track = %s \r\n"), str.GetData()));
	//		//	InsertList(str, FileItem::FILETYPE_FILTER);
	//		}
	//		//pDvdList->Invalidate(1);
	//	}
	//}
	return 0;
}


LRESULT DiscActivity::SysmodeNotify(DWORD param1, DWORD param2)
{

	SYSMODE_INFO *pSystemInfo = (SYSMODE_INFO*)param1;
	// ����״̬����
	if (pSystemInfo->ErrorCode1)
	{
		dvdControl.DVDEject();
		return 0;
	}
	if (pSystemInfo->ErrorCode2)
	{
		dvdControl.DVDEject();
		return 0;
	}
	if (pSystemInfo->MediaErrorCode1)
	{
		// ����
		dvdControl.DVDEject();
		return 0;
	}
	if (pSystemInfo->MediaErrorCode2)
	{
		// ����
		dvdControl.DVDEject();
		return 0;
	}

	//�ڱ�������
	if( Activity::GetActiveActiviy() == (DiscActivity*)this)
	{
		if (pSystemInfo->TvSystem == NTSC) // ntsc
		{
			if (tvSystem != NTSC)
			{
				//if (chip_saa7111.SourceCheckQuick() == NTSC)
				{
					tvSystem = NTSC;
					MediaControl::StopCamera();
					MediaControl::InitCamera(tvSystem);
					MediaControl::StartCamera();
				}

			}
		}
		if (pSystemInfo->TvSystem == PAL) // pal
		{
			if (tvSystem != PAL)
			{
				//if (chip_saa7111.SourceCheckQuick() == PAL)
				{
					tvSystem = PAL;
					MediaControl::StopCamera();
					MediaControl::InitCamera(tvSystem);
					MediaControl::StartCamera();
				}

			}
		}
	}
	
	
	return 0;
}


LRESULT DiscActivity::NotifyPowerOff(DWORD param1, DWORD param2)
{

	return 0;
}


LRESULT DiscActivity::MediaPlayInfoNotify(DWORD param1, DWORD param2)
{
	MEDIA_PLAY_INFO *pInfo = (MEDIA_PLAY_INFO *)param1;
	switch(pInfo->MediaType)
	{
	case MEDIATYPE_INVALID:
		{
			break;
		}
	case MEDIATYPE_CDDA:
		{
			GxxString str;
			str.Format(L"%02d:%02d", pInfo->media_play_info_CDDA_VCD.TrackTimeMinute, pInfo->media_play_info_CDDA_VCD.TrackTimeSecond);
			pLabel_currentTime->SetText(str.GetData(), true);
			pProgressVideoTime->SetDisplayPos(pInfo->media_play_info_CDDA_VCD.TrackTimeMinute*60 + pInfo->media_play_info_CDDA_VCD.TrackTimeSecond);
			break;
		}
	case MEDIATYPE_VCD:
		{
			GxxString str;
			str.Format(L"%02d:%02d", pInfo->media_play_info_CDDA_VCD.DiscTimeMinute, pInfo->media_play_info_CDDA_VCD.DiscTimeSecond);
			pLabel_currentTime->SetText(str.GetData(), true);
			pProgressVideoTime->SetDisplayPos(pInfo->media_play_info_CDDA_VCD.DiscTimeMinute*60 + pInfo->media_play_info_CDDA_VCD.DiscTimeSecond);
			break;
		}
	case MEDIATYPE_COMPRESS:
		{
			GxxString str;
			str.TimeStr(pInfo->media_play_info_DATA.FileTimeHour*3600+pInfo->media_play_info_DATA.FileTimeMinute*60+pInfo->media_play_info_DATA.FileTimeSecond);
			pLabel_currentTime->SetText(str.GetData(), true);
			pProgressVideoTime->SetDisplayPos(pInfo->media_play_info_DATA.FileTimeHour*3600+pInfo->media_play_info_DATA.FileTimeMinute*60+pInfo->media_play_info_DATA.FileTimeSecond);
			break;
		}
	case MEDIATYPE_DVDV:
		{
			GxxString str;
			str.TimeStr(pInfo->media_play_info_DVDV.PGCTimeHour*3600 + pInfo->media_play_info_DVDV.PGCTimeMinute*60 + pInfo->media_play_info_DVDV.PGCTimeSecond);
			pLabel_currentTime->SetText(str.GetData(), true);		
			pProgressVideoTime->SetDisplayPos(pInfo->media_play_info_DVDV.PGCTimeHour*3600 + pInfo->media_play_info_DVDV.PGCTimeMinute*60 + pInfo->media_play_info_DVDV.PGCTimeSecond);
			break;
		}
	case MEDIATYPE_UPDATE:
		{
			break;
		}
	}
	return 0;
}


void DiscActivity::UpdateUI(int iMediaType)
{
	
	switch(iMediaType)
	{
	case NONE:
		{
			//���ڱ�������
			if( Activity::GetActiveActiviy() != (DiscActivity*)this)
			{
				break;
			}
			LessenScreen();	//��С��Ļ
			pMediaWnd->setDraw(false);
			pPicMusicLogo->setDraw(true);

			pLabel_currentTime->SetText(L"00:00", true);
			pLabel_totaltime->SetText(L"00:00", true);
			pProgressVideoTime->SetDisplayPos(0);
			//pLabel_TopTitleDiscType->SetText(L"DVD", true);
			pControlGroup_page1->setDraw(true);
			pControlGroup_page2->setDraw(false);
			pLabel_VideoName->SetText(L"Video Name", true);
		}
		break;
	case MUSIC:
		{
			//�ڱ�������
			if( Activity::GetActiveActiviy() == (DiscActivity*)this)
			{
				LessenScreen();	//��С��Ļ
			}

			pMediaWnd->setDraw(false);
			pPicMusicLogo->setDraw(true);
		}
		break;
	case MOVIE:
		{
			pPicMusicLogo->setDraw(false);
			
			pMediaWnd->setDraw(true);
			
			
		}
		break;
	}

	GxxString str = "Disc ";
	str += strDiscType;
	pLabel_TopTitleDiscType->SetText(str.GetData(), true);

	iCurrentMediaType = iMediaType;

	//�ڱ�������
	if( Activity::GetActiveActiviy() == (DiscActivity*)this)
	{
		AfxInvalidateRect(NULL);
	}
	
	
}

LRESULT DiscActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//���ڱ�������
	if( Activity::GetActiveActiviy() != (DiscActivity*)this)
	{
		return 0;
	}

	int iMsg = param1;
	switch(iMsg)
	{
	case HardwareBtnMatch::PLAY_KEY:	//��ͣ����
		{
			dvdControl.DVDPlayPause();
		}
		break;
	case HardwareBtnMatch::PRE_KEY:	//��һ��
		{
			dvdControl.Skipb();
		}
		break;
	case HardwareBtnMatch::NEXT_KEY:	//��һ��
		{
			dvdControl.Skipf();
		}
		break;
	case HardwareBtnMatch::BACK_KEY:	//����
		{
			AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		}

	}
	return 0;
}

void DiscActivity::TimerTick( UINT nIDEvent )
{
	
	if (nIDEvent == iTimerHideControlId)
	{
		if(pThis->pControlGroup_fullScreen->getDraw())
		{
			if(pThis->pControlGroup_FullScreenControls->getDraw())
			{
				pThis->pControlGroup_FullScreenControls->setDraw(false);
				
			}
		}
		AfxInvalidateRect(&(pThis->m_ActRect));
		
		StopTimer(nIDEvent);
	}
	else if(nIDEvent == iTimerCommandFail)
	{
		pPicCommandFail->setDraw(false);
		CRect rc ;
		pPicCommandFail->getCtrRect(rc);
		AfxInvalidateRect(&rc);
		StopTimer(iTimerCommandFail);
	}
	else if(nIDEvent == iTimerDVDEnable)
	{
		bool bRet = IsDiscIn();
		//RETAILMSG(COUT_MSG, (TEXT("dsic in or not = %d\n"), bRet));
		if(bRet != bIsDVDEnable)
		{
			bIsDVDEnable = bRet;
			Activity::EnableActivity("DiscActivity",(bool)bIsDVDEnable);
		}
	}
	else if(nIDEvent == iTimerPlayPauseStatus)
	{
		StopTimer(iTimerPlayPauseStatus);
		pPicPlayStatus->setDraw(false);
		pPicPauseStatus->setDraw(false);
		pPicStopStatus->setDraw(false);
		if( Activity::GetActiveActiviy() == (DiscActivity*)this)
		{
			AfxInvalidateRect(NULL);
		}

	}
	else if(nIDEvent == iTimerPlayDVD)
	{
		StopTimer(nIDEvent);
		dvdControl.Play();
	}
	else if(nIDEvent == iTimerFullScreenMovie)
	{
		if(
			pMediaWnd->getDraw()
			&& !(pMediaWnd->IsFullScreen()) 
			&&pMediaWnd->GetIsBrake()
			)
		{
			if( Activity::GetActiveActiviy() == (DiscActivity*)this)
			{
				FullScreen(false);

				//���¿�ʼ��ʱ
				StopTimer(iTimerFullScreenMovie);
				StartTimer(iTimerFullScreenMovie);
			}
			else
			{
				StopTimer(iTimerFullScreenMovie);
			}
		}
	}
}



BOOL DiscActivity::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
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

LRESULT DiscActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	dvdControl.DVDReset();
	return 0;
}

static RegisterHelp help("DiscActivity", DiscActivity::CreateControl);