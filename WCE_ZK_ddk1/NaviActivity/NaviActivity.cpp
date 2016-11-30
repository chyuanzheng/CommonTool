#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "NaviActivity.h"
#include "ControlHelp.h"
#include "Navi.h"
#include "TimerManager.h"
#include "aygshell.h"
#include "shellsdk.h"
#include "Audio/Audio.h"
#include "VolumeControl.h"
#include "MsgHandle.h"
#include "WheelMsg.h"

#define TIMER_DEVICE_DETECT_ELAPSE 3000

#include "VersionXml.h"


Activity* NaviActivity::CreateControl()
{
	return new NaviActivity;
}

void NaviActivity::onCreate()
{
	
	setContentView("layout\\NaviPad.xml");
	Activity::onCreate();
	setBackColor(0xffff0000);
	Navi::SetHwnd(AfxGetHWND());

	strDevicePath = L"Storage Card";


	VersionXml* pVersionXml = VersionXml::GetInstance();
	string strNavi = pVersionXml->GetNaviSoftWare();
	strNaviPath = strNavi.c_str();

	Navi::SetNaviPath(strNaviPath);

	// 注册硬件改变事件
	SetMsgHandler(WM_FILECHANGEINFO, DeviceChange, (DWORD)this, this);
	
	VolumeControl::ApplayForPermission(VolumeModuleId::NAVI, 15, L"navi");

	pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");


	bIsDeviceExist = true;
	iTimerCheckDevice =  RegisterTimer(TIMER_DEVICE_DETECT_ELAPSE);
	

	StartTimer(iTimerCheckDevice);

	Notify notify;
	notify.dwParam = this;

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);

	notify.funNotify = NotifyHideNavi;
	GXNotify::RegisterNotifyHandler("HideNavi", notify);

	notify.funNotify = NotifyNaviVol;
	GXNotify::RegisterNotifyHandler("set_navi_vol", notify);

	notify.funNotify = NotifyNaviVol2;
	GXNotify::RegisterNotifyHandler("set_navi_vol2", notify);
}

bool NaviActivity::IsNaviOn()
{
	return Navi::IsNaviOn();
}

bool NaviActivity::HideNavi()
{
	return Navi::HideNavi();
}

bool NaviActivity::ShowNavi()
{
	return Navi::ShowNavi();
}

bool NaviActivity::IsNaviOnTop()
{
	return Navi::IsNaviOnTop();
}



LRESULT NaviActivity::NotifyHideNavi(DWORD param1, DWORD param2)
{
	if(Navi::IsNaviOn())		//导航是否运行中
	{
		Navi::HideNavi();
	}
	return 0;
}

LRESULT NaviActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//不在本窗口下
	if( Activity::GetActiveActiviy() != (NaviActivity*)this)
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

void NaviActivity::TimerTick( UINT nIDEvent )	//接收定时器消息
{
	if(nIDEvent == iTimerCheckDevice)
	{
		if(IsDeviceExist() != bIsDeviceExist)
		{
			bIsDeviceExist = IsDeviceExist();

			Activity::EnableActivity("NaviActivity",bIsDeviceExist);
		}

	}
}

DWORD NaviActivity::DeviceChange(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{
	NaviActivity *pNaviActivity = (NaviActivity *)pControl;

	FILECHANGENOTIFY *pFcn = (FILECHANGENOTIFY*)lParam;
	if (pFcn->fci.wEventId == SHCNE_DELETE)		//取出设备
	{
		GxxString sPath = (TCHAR*)pFcn->fci.dwItem1;
		if(sPath == pNaviActivity->strDevicePath)
		{
			if(Navi::IsNaviOn())		//导航是否运行中
			{
				Navi::ForceCloseNavi();
				Activity::EnableActivity("NaviActivity",false);
			}
			
		}
	}
	if (pFcn->fci.wEventId == SHCNE_MEDIAINSERTED)	//插入设备
	{
		if( Activity::GetActiveActiviy() != pNaviActivity)	//不在导航界面中，不处理
		{
			return 0;
		}

		GxxString sPath = (TCHAR*)pFcn->fci.dwItem1;
		GxxString strTempDevicePath = L"\\";
		strTempDevicePath += pNaviActivity->strDevicePath;
		if(sPath == strTempDevicePath)
		{
			int iRet = GetFileAttributes(pNaviActivity->strNaviPath.GetData());
			if ( iRet != -1)
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);	//跳到主界面
				Navi::StartNavi();		//启动导航
				Activity::EnableActivity("NaviActivity",true);
			}
		}
		

	}
	return 0;
}

bool NaviActivity::IsDeviceExist()
{
	GxxString strTempDevicePath = L"\\";
	strTempDevicePath +=  strDevicePath;
	if(GetFileAttributes(strTempDevicePath) == -1)
	{
		return false;
	}
	return true;
}

BOOL NaviActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_LISTBOX_MES:
		{
			
			return TRUE;
		}
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
	default:
		return FALSE;
	}
	return FALSE;
}

void NaviActivity::onResume()
{
	Audio::ToNavi();

	int iRet = GetFileAttributes(strNaviPath);
	if ( iRet != -1)
	{
		AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);	//跳到主界面

		Navi::StartNavi();

		//设定导航音量
		NotifyNaviVol(sysConfig.sysParam.curGPSVol, 0);
	}
	
}

void NaviActivity::onPause()
{
	//Navi::HideNavi();
}

void NaviActivity::onStop()
{
	Navi::HideNavi();
}

LRESULT NaviActivity::NotifyNaviVol(DWORD param1, DWORD param2)
{
	RETAILMSG(COUT_MSG,( TEXT("NotifyNaviVol = %d\n"), param1));
	Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
	return 0;
}

LRESULT NaviActivity::NotifyNaviVol2(DWORD param1, DWORD param2)
{
	RETAILMSG(COUT_MSG,( TEXT("NotifyNaviVol2 = %d\n"), param1));
	if (param1 > 10)
	{
		param1 = 10;
	}
	Navi::SetNaviVol(param1);
	return 0;
}


static RegisterHelp help("NaviActivity", NaviActivity::CreateControl);