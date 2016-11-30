#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "BTMusicActivity.h"
#include "ControlHelp.h"
#include "TimerManager.h"
#include "AVSet.h"
#include "VolumeControl.h"
#include "WheelMsg.h"

Activity* BTMusicActivity::CreateControl()
{
	return new BTMusicActivity;
	
}

void BTMusicActivity::onCreate()
{
	
	setContentView("layout\\BTMusicPad.xml");
	Activity::onCreate();

	pLabel_SearchPrev = (GxxAniLable*)safeFindViewByName("Label_SearchPrev");
	pLabel_SearchNext = (GxxAniLable*)safeFindViewByName("Label_SearchNext");
	pLabel_PlayAndPause = (GxxAniLable*)safeFindViewByName("Label_PlayAndPause");
	pLabel_Reconnect = (GxxAniLable*)safeFindViewByName("Label_Reconnect");
	pLabel_Disconnect = (GxxAniLable*)safeFindViewByName("Label_Disconnect");
	pLabel_ChangeDevice = (GxxAniLable*)safeFindViewByName("Label_ChangeDevice");

	pControlGroup_page1 = (GxxControlGroup*)safeFindViewByName("ControlGroup_page1");

	pLabel_Text_Tip = (GxxAniLable*)safeFindViewByName("Label_Text_Tip");

	pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");

	pLabel_ToPhone = (GxxAniLable*)safeFindViewByName("Label_ToPhone");


	VolumeControl::ApplayForPermission(VolumeModuleId::BTMUSIC, 0, L"BT");



	Notify notify;
	notify.dwParam = this;
	//notify.funNotify = GetPhoneHardware;
	//GXNotify::RegisterNotifyHandler("PhoneHardware", notify);

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);

	notify.funNotify = BtStatusNotify;
	GXNotify::RegisterNotifyHandler("btstatus", notify);

	pPhoneHardware =  PhoneHardwareManager::GetPhoneHardware();;
	UpdateUI(DISCONNECT);

	bIsPlaying = false;

}

LRESULT BTMusicActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//���ڱ�������
	if( Activity::GetActiveActiviy() != (BTMusicActivity*)this)
	{
		return 0;
	}

	int iMsg = param1;
	switch(iMsg)
	{
		case HardwareBtnMatch::PLAY_KEY:	//��ͣ����
			{
				PlayMusic();
			}
			break;
		case HardwareBtnMatch::PRE_KEY:	//��һ��
			{
				if(pPhoneHardware)
					pPhoneHardware->PrevMusic();
			}
			break;
		case HardwareBtnMatch::NEXT_KEY:	//��һ��
			{
				if(pPhoneHardware)
					pPhoneHardware->NextMusic();
			}
			break;
		case HardwareBtnMatch::BACK_KEY:	//����
		{
			AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		}

	}
	return 0;
}
void BTMusicActivity::PlayMusic()
{
	if(pPhoneHardware)
	{
		//VolumeControl::SlowlyIncreaseVolume();
		pPhoneHardware->PlayMusic();
	}
}

LRESULT BTMusicActivity::BtStatusNotify(DWORD param1, DWORD param2)
{
	switch((PhoneHardware::BTSTATUS)param1)
	{
	case PhoneHardware::BT_CONNECTED:
		{
			UpdateUI(CONNECT);
			if( Activity::GetActiveActiviy() == (BTMusicActivity*)this)
			{
				PlayMusic();
			}
			
			break;
		}
	case PhoneHardware::BT_DISCONNECT:
		{
			
			UpdateUI(DISCONNECT);

			break;
		}
	case PhoneHardware::BT_LINEIN:
		{
			
			break;
		}
	case PhoneHardware::BT_DIALING:
		{
			
			break;
		}
	case PhoneHardware::BT_DIALNO:
		{
			
			break;
		}
	case PhoneHardware::BT_RECV:
		{
			
			break;
		}
	case PhoneHardware::BT_HANGUP:
		{
			break;
		}

	}
	return 0;
}

void BTMusicActivity::UpdateUI(int iStatus)	//���½���
{
	switch(iStatus)
	{
	case CONNECT:
		{
			pLabel_Text_Tip->setDraw(false);
			pControlGroup_page1->setDraw(true);
			pLabel_Reconnect->setDraw(false);
			pLabel_Disconnect->setDraw(true);
		}
		break;
	case DISCONNECT:
		{
			pLabel_Text_Tip->setDraw(true);
			pControlGroup_page1->setDraw(false);
			pLabel_Reconnect->setDraw(true);
			pLabel_Disconnect->setDraw(true);
		}
		break;
	}
	AfxInvalidateRect(&m_ActRect);
}




BOOL BTMusicActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxAniLable *)wParam == pLabel_ChangeDevice)	
			{
				startActivity(this ,"PhoneDevcieActivity");
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_ToPhone)	
			{
				startActivity(NULL ,"PhoneActivity");
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pInc_Into_MainInterface)	//����������
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SearchPrev)	//��һ��
			{
				if(pPhoneHardware)
					pPhoneHardware->PrevMusic();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SearchNext)	//��һ��
			{
				if(pPhoneHardware)
					pPhoneHardware->NextMusic();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_PlayAndPause)
			{
				PlayMusic();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Disconnect)	//�Ͽ���������
			{
				if(pPhoneHardware)
					pPhoneHardware->HshfDisconnect();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Reconnect)	//������������
			{
				if(pPhoneHardware)
					pPhoneHardware->HshfConnect(0);
				return TRUE;
			}
			
			
			
			return TRUE;
		}
	default:
		return FALSE;
	}
	return FALSE;
}

void BTMusicActivity::onStop()
{
	if(pPhoneHardware)
	{
		pPhoneHardware->StopMusic();
		bIsPlaying = false;
	}
}

void BTMusicActivity::onResume()
{
	AVSET::ToBTMusic();

	//��������
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::BTMUSIC);
	
	
	if(bIsPlaying == false)
	{
		//��������
		PlayMusic();

		bIsPlaying = true;
	}
	
}

void BTMusicActivity::onPause()
{
	bIsPlaying = true;
}

static RegisterHelp help("BTMusicActivity", BTMusicActivity::CreateControl);