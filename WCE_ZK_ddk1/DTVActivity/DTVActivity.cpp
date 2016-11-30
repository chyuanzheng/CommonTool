#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "DTVActivity.h"
#include "ControlHelp.h"
#include "TimerManager.h"
#include "PIP/PIP.h"
#include "VolumeControl.h"
#include "AVSet.h"
#include "Hardware.h"
#include "WheelMsg.h"
#include "GxxFullScreenKeys.h"
#include "GxxCommonKeys.h"
#include "GxxNormalKeys.h"
#include "TVCommand.h"

#define DETECT_HIDE_KEYPAD 3000

Activity* DTVActivity::CreateControl()
{
	return new DTVActivity;
}

void DTVActivity::onCreate()
{
	
	setContentView("layout\\DTVPad.xml");
	Activity::onCreate();

	m_isFullScreen = false;
	m_isInfoScreen = false;

	VolumeControl::ApplayForPermission(VolumeModuleId::DTV, 0, L"dtv");


	m_mediaWnd = (DtvMediaWndEx*)safeFindViewByName("moviewindow");
	m_mediaWnd->setDraw(false);
	m_mediaWnd->SetMessageView(this);

	m_pLabelTip = (GxxAniLable*)safeFindViewByName("LabelTip");
	m_picAuxLogo = (GxxPicIcon*)safeFindViewByName("PicAuxLogo");
	//m_picAuxLogo->setDraw(false);

	

	

	m_i_group = (GxxControlGroup*)safeFindViewByName("i_group");
	m_normal_group = (GxxControlGroup*)safeFindViewByName("normal_group");
	m_full_group = (GxxControlGroup*)safeFindViewByName("full_group");


	m_fullscreenKeys = (GxxFullScreenKeys*)safeFindViewByName("fullscreen_keys");
	m_fullscreenKeys->SetMessageView(this);
	m_fullscreenKeys->setDraw(false);

	m_commonKeys = (GxxCommonKeys *)safeFindViewByName("common_keys");
	m_commonKeys->SetMessageView(this);

	m_normalKeys = (GxxNormalKeys *)safeFindViewByName("normal_keys");
	m_normalKeys->SetMessageView(this);





	m_checkHandle = NULL;
	
	DWORD dwTheadID;
	m_checkHandle = CreateThread(NULL, 0, CheckDtvThread, (LPVOID)this, 0, &dwTheadID);
	SetThreadPriority(m_checkHandle,THREAD_PRIORITY_LOWEST);

	

	m_dtvHardware.Init(AfxGetHWND());

	//pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");

	Notify notify;
	notify.dwParam = this;

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);

	m_fsTimer = RegisterTimer(5000);
	m_curVFormat = 0;//
}


LRESULT DTVActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//不在本窗口下
	if( Activity::GetActiveActiviy() != (DTVActivity*)this)
	{
		return 0;
	}
	int iMsg = param1;
	switch(iMsg)
	{
	case HardwareBtnMatch::PLAY_KEY:	//暂停播放
		{
			m_dtvHardware.KeyPlayPause();
		}
		break;
	case HardwareBtnMatch::PRE_KEY:	//上一曲
		{
			m_dtvHardware.KeyChannelAdd();
		}
		break;
	case HardwareBtnMatch::NEXT_KEY:	//下一曲 
		{
			m_dtvHardware.KeyChannelDec();
		}
		break;
	case HardwareBtnMatch::BACK_KEY:	//返回
		{
			AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		}
	}
	return 0;
}



BOOL DTVActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	//case MCU_POPMENU:
	//	if (m_isFullScreen)
	//	{
	//		EnterFullScreen(false);
	//	}
	//	return FALSE;
	case  CTR_DTV_SIGNAL:
		DtvSignal(wParam);
		return TRUE;

	case DTV_Click_Media_Wnd:
		if (m_isFullScreen)
		{
			m_fullscreenKeys->ClickWnd();
		}
		else
		{
			if (0!=m_curVFormat)//如果非全屏下播放 则要进入全屏
			{
				EnterFullScreen(true);
			}
		}
		return TRUE;

	case  DTV_Play_Pause:
		m_dtvHardware.KeyPlayPause();
		return TRUE;

	case  DTV_Content:
		m_dtvHardware.KeyMenu();
		return TRUE;

	case  DTV_ShowList:
		m_dtvHardware.KeyShowList();
		return TRUE;

	case  DTV_Stop:
		m_dtvHardware.KeyStop();
		return TRUE;

	case  DTV_Full_Screen:
		EnterFullScreen(true);
		return TRUE;

	case  DTV_Fast_Forward:
		m_dtvHardware.KeyFastForward();
		return TRUE;

	case  DTV_Fast_Backward:
		m_dtvHardware.KeyFastBackward();
		return TRUE;

	case  DTV_SetupVedio:
		Activity::startActivity(this,"SetupActivity","2_display_setup");
		return TRUE;

	case  DTV_SetupAudio:
		Activity::startActivity(this,"SetupActivity","2_sound_setup");
		return TRUE;

	case  DTV_Vol_Add:
		m_dtvHardware.KeyVolAdd();
		return TRUE;

	case  DTV_Vol_Dec:
		m_dtvHardware.KeyVolDec();
		return TRUE;

	case DTV_Channel_Dec://CH-
		m_dtvHardware.KeyChannelDec();
		return TRUE;

	case  DTV_Channel_Add://CH+
		m_dtvHardware.KeyChannelAdd();
		return TRUE;

	case  DTV_OK:
		m_dtvHardware.KeyOk();
		return TRUE;

	case  DTV_Leave:
		m_dtvHardware.KeyQuit();
		return TRUE;

	case  CTR_BTN_MATCH_BACK:
	case  DTV_Back_Btn:
		AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		return TRUE;


	case DTV_Quit_FullScreen:
		EnterFullScreen(false);
		return TRUE;
	case DTV_Info_Btn:
		m_isInfoScreen = !m_isInfoScreen;
		m_i_group->setDraw(m_isInfoScreen);
		m_normal_group->setDraw(!m_isInfoScreen);
		if (m_isInfoScreen)
		{
			Activity::overridePendingTransition(m_normal_group,m_i_group,Activity::s_hAniRotateY);
		}
		else
		{
			Activity::overridePendingTransition(m_i_group,m_normal_group,Activity::s_hAniRotateY);
		}
		
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}

void DTVActivity::onStop()
{
	// 暂停视频
	m_dtvHardware.KeyStop();
	MediaControl::StopCamera();
	// 隐藏视频窗口
	//MediaControl::HideMediaWnd();

	m_curVFormat = 0;//
	//pWindow->KillTimer(0);
}

void DTVActivity::onResume()
{
	AVSET::ToTV();
	//m_curVFormat = 0;//

	// 切换到camera模式
	MediaControl::SetMediaMode(CAMERA); 
	CRect rc;
	m_mediaWnd->getCtrRect(rc);
	MediaControl::SetMediaRect(rc);

	if (m_curVFormat==0)
	{
		m_mediaWnd->setDraw(false);
		m_picAuxLogo->setDraw(true);
		m_pLabelTip->setDraw(true);
	}

	
	s_pauseCheck = false;
	ResumeThread(m_checkHandle); 

	//设定音量
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::DTV);

	StartTimer(m_fsTimer);


}

void DTVActivity::onPause()
{
	s_pauseCheck = true;
	//MediaControl::PauseCamera();
	EnterFullScreen(false);//退出全屏

	StopTimer(m_fsTimer);
}


bool DTVActivity::s_pauseCheck = true;
DWORD DTVActivity::CheckDtvThread(LPVOID lpParam)
{
	DTVActivity * pAty = (DTVActivity *)lpParam;
	while(1)
	{

		if (s_pauseCheck)
		{
			SuspendThread (pAty->m_checkHandle);
		}

		Sleep(1000);

		if (s_pauseCheck)
		{
			SuspendThread (pAty->m_checkHandle);
		}

		pAty->CheckDtvThread();

	}
	
	return 0;
}

void DTVActivity::CheckDtvThread()
{
	int vFormat = AVSET::SourceCheck();//这个函数需要  线程安全 使一个函数变成可重入的
	if (vFormat != m_curVFormat)
	{
		AfxPostMessage(CTR_DTV_SIGNAL,vFormat,0);
	}
}

void DTVActivity::DtvSignal( int nSig )
{
	int vFormat = nSig;
	ASSERT(m_curVFormat != nSig);
	ASSERT(m_mediaWnd);
	if (m_curVFormat == 0)//打开dtv
	{
		m_curVFormat = nSig;
		if (m_curVFormat == 1)
		{
			StartDTV(NTSC);
		}
		else if (m_curVFormat == 2)
		{
			StartDTV(PAL);
		}
		else
		{
			ASSERT(0);
		}
		m_mediaWnd->setDraw(true);
		m_mediaWnd->ReductionScreen();
		ASSERT(!m_isFullScreen);
		m_picAuxLogo->setDraw( false);
		m_pLabelTip->setDraw( false);
		AfxInvalidateRect(NULL);
		return;
	}
	else if (nSig == 0)//dtv失去信号
	{
		m_curVFormat = nSig;
		if (m_mediaWnd)
		{
			m_mediaWnd->setDraw(false);
			AfxInvalidateRect(NULL);
			m_picAuxLogo->setDraw( true);
			m_pLabelTip->setDraw( true);

			if (m_isFullScreen)//如果是全屏则要退出
			{
				EnterFullScreen(false);
			}
		}
		return;
	}
	else//切换 DTV
	{
		m_curVFormat = nSig;
		if (m_curVFormat == 1)
		{
			StartDTV(NTSC);

		}
		else if (m_curVFormat == 2)
		{
			StartDTV(PAL);
		}
		else
		{
			ASSERT(0);
		}
	}
}



void DTVActivity::StartDTV( int type )
{
	MediaControl::StopCamera();
	MediaControl::InitCamera(type);
	MediaControl::StartCamera();
	StartTimer(m_fsTimer);
}



void DTVActivity::EnterFullScreen(bool isEnter)
{
	if (m_isFullScreen == isEnter)
	{
		return;
	}

	m_isFullScreen = isEnter;
	if (m_isFullScreen )
	{
		StopTimer(m_fsTimer);
		if (0==m_curVFormat)//无信号不能进入全屏
		{
			m_isFullScreen = false;
			return;
		}
		m_full_group->setDraw(true);
		m_i_group->setDraw(false);
		m_normal_group->setDraw(false);
		m_fullscreenKeys->Reset();
		m_mediaWnd->SetFullScreen();
		AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);	////进入全屏//cyz
	}
	else
	{

		m_full_group->setDraw(false);
		m_i_group->setDraw(m_isInfoScreen);
		m_normal_group->setDraw(!m_isInfoScreen);

		if (0!=m_curVFormat)
		{
			m_mediaWnd->ReductionScreen();
			StartTimer(m_fsTimer);
		}
		
		AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);	//退出全屏//cyz
	}
	AfxInvalidateRect(NULL);
}


BOOL DTVActivity::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP)
	{
		m_fullscreenKeys->UserClick();
		if (0!=m_curVFormat&& !m_isFullScreen)
		{
			if (message == WM_LBUTTONDOWN )
			{
				StopTimer(m_fsTimer);
			}
			else
			{
				StartTimer(m_fsTimer);
			}
		}
	}
	return Activity::DealCtrlMsg(message,wParam,lParam);
}

void DTVActivity::TimerTick( UINT nIDEvent )
{
	if (nIDEvent == m_fsTimer)
	{
		EnterFullScreen(true);
	}
}

static RegisterHelp help("DTVActivity", DTVActivity::CreateControl);