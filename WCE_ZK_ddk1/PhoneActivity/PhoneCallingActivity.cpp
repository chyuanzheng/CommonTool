#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "PhoneCallingActivity.h"
#include "ControlHelp.h"
#include "Audio/Audio.h"
#include "PIP/PIP.h"
#include "AVSet.h"
#include "VolumeControl.h"

#define ELAPSE_PHONETIME 1000	//�����ʱ���

Activity * PhoneCallingActivity::pThis = NULL;

PhoneCallingActivity::PhoneCallingActivity()
{
	pThis = this;
}

Activity* PhoneCallingActivity::CreateControl()
{
	

	return new PhoneCallingActivity;
}

void PhoneCallingActivity::onCreate()
{
	
	setContentView("layout\\phone\\PhoneCallingPad.xml");
	Activity::onCreate();

	phoneHardware = PhoneHardwareManager::GetPhoneHardware();

	pLabelContactsName = (GxxAniLable*)safeFindViewByName("LabelContactsName");
	//pLabelDiagKeyToKeypad = (GxxAniLable*)safeFindViewByName("LabelDiagKeyToKeypad");
	pLabelDialInterfaceRing = (GxxAniLable*)safeFindViewByName("LabelDialInterfaceRing");
	pLabelDialInterfaceTime = (GxxAniLable*)safeFindViewByName("LabelDialInterfaceTime");
	//pLabelDialInterfaceTip = (GxxAniLable*)safeFindViewByName("LabelDialInterfaceTip");
	pLabelHandup = (GxxAniLable*)safeFindViewByName("LabelHandup");
	pLabelSwitchAudio = (GxxAniLable*)safeFindViewByName("LabelSwitchAudio");

	iTimerPhoneTime = RegisterTimer(ELAPSE_PHONETIME);

	dialTime = 0;	//ͨ��ʱ��
	

	Notify notify;
	notify.dwParam = this;

	notify.funNotify = BtStatusNotify;
	GXNotify::RegisterNotifyHandler("btstatus", notify);

	phoneHardware = PhoneHardwareManager::GetPhoneHardware();
	
}

void PhoneCallingActivity::SetContactName(GxxString str)
{
	pLabelContactsName->SetText(str.GetData());
}

void PhoneCallingActivity::TimerTick( UINT nIDEvent )
{
	if(nIDEvent == iTimerPhoneTime)
	{
		int min = ++dialTime/60;
		int sec = dialTime%60;
		GxxString strTime;
		strTime.Format(_T("%02d:%02d"), min, sec);
		pLabelDialInterfaceTime->SetText(strTime.GetData(), true);

	}
	//else if(nIDEvent == iTimerPhoneAutoAnswer)
	//{
	//	int iTimer = sysConfig.sysParam.curPhoneAutoAnswer;
	//	if(iAutoAnswerTime < iTimer)
	//	{
	//		iAutoAnswerTime++;
	//		RETAILMSG(COUT_MSG, (L"autoAnswerTimer = %d\r\n", iAutoAnswerTime));
	//	}
	//	else
	//	{
	//		ExitAutoAnswer();

	//		//�����绰
	//		if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
	//		{
	//			phoneHardware->Reject();
	//		}
	//	}
	//}
}

LRESULT PhoneCallingActivity::BtStatusNotify(DWORD param1, DWORD param2)
{
	switch((PhoneHardware::BTSTATUS)param1)
	{
	case PhoneHardware::BT_CONNECTED:
		{
			
			break;
		}
	case PhoneHardware::BT_DISCONNECT:
		{

			break;
		}
	case PhoneHardware::BT_LINEIN:
		{
			pLabelSwitchAudio->setEnable(false);
			break;
		}
	case PhoneHardware::BT_DIALING:
		{
			//pLabelSwitchAudio->setDraw(true);
			break;
		}
	case PhoneHardware::BT_DIALNO:
		{
			//pLabelSwitchAudio->setDraw(false);
			break;
		}
	case PhoneHardware::BT_RECV:
		{
			pLabelSwitchAudio->setEnable(true);

			dialTime = 0;
			StartTimer(iTimerPhoneTime);
			break;
		}
	case PhoneHardware::BT_HANGUP:
		{

			pLabelSwitchAudio->setEnable(false);

			StopTimer(iTimerPhoneTime);
			pLabelDialInterfaceTime->SetText(L"", true);
			pLabelContactsName->SetText("");
			break;
		}

	}
	return 0;
}


BOOL PhoneCallingActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if((GxxAniLable *)wParam == pLabelHandup)
			{
				Handup();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelSwitchAudio)	//�л��ֻ�����������
			{
				KeyTransform();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelDialInterfaceRing)	//ͨ�������н����绰
			{
				Contact();
				return TRUE;
			}
		}
	default:
		return FALSE;
	}
	return FALSE;
}

void PhoneCallingActivity::Contact()
{
	if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
	{
		phoneHardware->Reject();
	}
}

void PhoneCallingActivity::KeyTransform()
{
	if (phoneHardware->SoundStatus == PhoneHardware::SOUND_BTMODULE)
	{
		phoneHardware->Divert();
	}
	else
	{
		phoneHardware->Divert();
	}

}

void PhoneCallingActivity::Handup()
{
	if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
	{
		phoneHardware->RecvCall();
	}
	else
	{

		phoneHardware->HangUp();
	}
}

void PhoneCallingActivity::onStop()
{
	//��������
	AVSET::LeaveBTPhone();
}

void PhoneCallingActivity::onResume()
{
	AVSET::ToBTPhone();

	//��������
	//VolumeControl::ApplyForVolumeControl(VolumeModuleId::PHONE);
	

	
}

void PhoneCallingActivity::onPause()
{
	
	//��������
	AVSET::LeaveBTPhone();
}

static RegisterHelp help("PhoneCallingActivity", PhoneCallingActivity::CreateControl);