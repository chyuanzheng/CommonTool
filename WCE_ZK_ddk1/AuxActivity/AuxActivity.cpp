#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "AuxActivity.h"
#include "ControlHelp.h"
#include "TimerManager.h"
#include "Audio/Audio.h"
#include "PIP/PIP.h"
#include "AVSet.h"
#include "VolumeControl.h"
#include "WheelMsg.h"

#define DETECT_AUX_ELAPSE 1000
#define DETECT_TimerFullWnd_ELAPSE 2000

Activity* AuxActivity::CreateControl()
{
	return new AuxActivity;
}

void AuxActivity::onCreate()
{
	
	setContentView("layout\\AuxPad.xml");
	Activity::onCreate();

	VolumeControl::ApplayForPermission(VolumeModuleId::AUX, 0, L"aux");

	pMediaWnd = (TccMediaWndEx*)safeFindViewByName("moviewindow");
	pMediaWnd->SetFun(ClickMediaWnd, this);

	//设置驾驶中警告语
	pLabelWarnning = (GxxAniLable*)safeFindViewByName("LabelWarnning");
	pMediaWnd->SetWarning(pLabelWarnning, false);

	pPicAuxLogo = (GxxPicIcon*)safeFindViewByName("PicAuxLogo");


	iTimerDetectAuxId = RegisterTimer(DETECT_AUX_ELAPSE);

	iTimerFullWnd = RegisterTimer(DETECT_TimerFullWnd_ELAPSE);

	pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");

	Notify notify;
	notify.dwParam = this;

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);
	
}

//视频全屏时，点击视频的响应函数
void AuxActivity::ClickMediaWnd(GxxView *p, void *dwParam)
{
	AuxActivity* pThis = (AuxActivity*)dwParam;
	if(pThis->pMediaWnd->IsFullScreen())
	{
		pThis->pInc_Into_MainInterface->setDraw(true);
		CRect rc;
		pThis->pInc_Into_MainInterface->getCtrRect(rc);
		AfxInvalidateRect(&rc);
		pThis->StopTimer(pThis->iTimerFullWnd);
		pThis->StartTimer(pThis->iTimerFullWnd);
	}
	else
	{
		pThis->StopTimer(pThis->iTimerFullWnd);
		pThis->pInc_Into_MainInterface->setDraw(false);
		CRect rc;
		pThis->pInc_Into_MainInterface->getCtrRect(rc);
		AfxInvalidateRect(&rc);
	}


}

LRESULT AuxActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//不在本窗口下
	if( Activity::GetActiveActiviy() != (AuxActivity*)this)
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
	}
	return 0;
}
 
void AuxActivity::TimerTick( UINT nIDEvent )
{
	if(nIDEvent == iTimerFullWnd)
	{
		StopTimer(nIDEvent);
		pInc_Into_MainInterface->setDraw(false);
		CRect rc;
		pInc_Into_MainInterface->getCtrRect(rc);
		AfxInvalidateRect(&rc);
	}
	if(nIDEvent == iTimerDetectAuxId)
	{
		// 如果现在在倒车通道,不检查视频
		int vFormat = AVSET::SourceCheck();
		RETAILMSG(COUT_MSG, (TEXT("aux video = %d\r\n"), vFormat));
		if (vFormat != curVFormat)
		{
			if (curVFormat == 0)
			{
				if (vFormat == 1)
				{
					MediaControl::StopCamera();
					MediaControl::InitCamera(NTSC);
					MediaControl::StartCamera();
				}
				if (vFormat == 2)
				{
					MediaControl::StopCamera();
					MediaControl::InitCamera(PAL);
					MediaControl::StartCamera();
				}

				if (pMediaWnd)
				{
					StopTimer(iTimerFullWnd);
					pMediaWnd->setDraw(true);
					pMediaWnd->SetFullScreen();
					pPicAuxLogo->setDraw(false);
					pInc_Into_MainInterface->setDraw(false);
					AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);	////进入全屏
					AfxInvalidateRect(&m_ActRect);
				}
				curVFormat = vFormat;
				return;
			}
			if (vFormat == 0)
			{

				if (pMediaWnd)
				{
					StopTimer(iTimerFullWnd);
					pMediaWnd->setDraw(false);
					pPicAuxLogo->setDraw(true);
					pInc_Into_MainInterface->setDraw(true);
					AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);	//退出全屏
					AfxInvalidateRect(&m_ActRect);
				}
				curVFormat = vFormat;
				return;
			}
			if (vFormat == 1)
			{
				MediaControl::StopCamera();
				MediaControl::InitCamera(NTSC);
				MediaControl::StartCamera();
			}
			if (vFormat == 2)
			{
				MediaControl::StopCamera();
				MediaControl::InitCamera(PAL);
				MediaControl::StartCamera();
			}

			if (pMediaWnd)
			{
				StopTimer(iTimerFullWnd);
				pMediaWnd->setDraw(true);
				pMediaWnd->SetFullScreen();
				pPicAuxLogo->setDraw(false);
				pInc_Into_MainInterface->setDraw(false);
				AfxPostMessage(CTR_INTO_FULL_SCREEN, 0, 0);	////进入全屏
				AfxInvalidateRect(&m_ActRect);
			}

			curVFormat = vFormat;
		}
	}

}


BOOL AuxActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{

			if ((GxxAniLable *)wParam == pInc_Into_MainInterface)	
			{				
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
				return TRUE;
			}
		}
		return FALSE;
	case CTR_LISTBOX_MES:
		{
			
			return TRUE;
		}
	default:
		return FALSE;
	}
	return FALSE;
}

void AuxActivity::onStop()
{
	// 暂停视频
	MediaControl::StopCamera();

	StopTimer(iTimerFullWnd);

}

void AuxActivity::onResume()
{
	AVSET::ToAux();

	// 切换到camera模式
	MediaControl::SetMediaMode(CAMERA); 
	CRect rc;
	pMediaWnd->getCtrRect(rc);
	pMediaWnd->setDraw(false);
	MediaControl::SetMediaRect(rc);
	pInc_Into_MainInterface->setDraw(true);

	curVFormat = NOVIDEO;

	//设定音量
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::AUX);

	StartTimer(iTimerDetectAuxId);
}

void AuxActivity::onPause()
{
	MediaControl::PauseCamera();
	StopTimer(iTimerDetectAuxId);

	AfxPostMessage(CTR_EXIT_FULL_SCREEN, 0, 0);

}

static RegisterHelp help("AuxActivity", AuxActivity::CreateControl);