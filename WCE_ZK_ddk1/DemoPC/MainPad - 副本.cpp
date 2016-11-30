#include "stdAfx.h"
#include "ControlHelp.h"
#include "AnimationManage.h"
#include "MainPad.h"
#include "GxxAppButton.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "Audio/Audio.h"
#include "MesDef.h"
#include "WMMsg.h"
#include "VolumeControl.h" 
#include "LangStringManager.h"
#include "Hardware.h"
#include "AVSet.h"
#include "MsgHandle.h"
#include "WheelMsg.h"
#include "AppManage.h"
#include "BT\PhoneHardwareManager.h"
#include "GxxBeep.h"
#include "GXNotify.h"
#include "StrHelp.h"
#include <iostream>
#include <fstream>
#include "NaviActivity.h"
#include "StrDef.h"
#include "VersionXml.h"


#define  ACC_POWER_OFF   11
Activity* MainPad::CreateControl()
{
	return new MainPad;
}
 
void MainPad::onCreate()
{
	VersionXml::GetInstance();
	// ��ʼ��Ӳ��
	PlaySound(L"\\windows\\1.wav", NULL, SND_FILENAME);
	PlaySound(L"\\windows\\1.wav", NULL, SND_FILENAME);
	CreatecHardware::Init(AfxGetHWND());
	MediaControl::Init(AfxGetHWND());
	VolumeControl::Init();	//��ʼ������ģ��

	if (VersionXml::GetInstance()->GetNaviSoftCode() == VersionXml::Navi_KaiLiDe)
	{
		SetMsgHandler(WM_NAVISOUND_KLD, NaviSound, (DWORD)this);
	}
	else if (VersionXml::GetInstance()->GetNaviSoftCode() == VersionXml::Navi_NaviKing)
	{
		SetMsgHandler(WM_NAIVSOUND, NaviSound, (DWORD)this);
	}
	else if (VersionXml::GetInstance()->GetNaviSoftCode() == VersionXml::Navi_GaoDe)
	{
		SetMsgHandler(WM_NAVISOUND_GD, NaviSound, (DWORD)this);
	}
	else 
	{
		SetMsgHandler(WM_NAIVSOUND, NaviSound, (DWORD)this);
	}
	

	iTIMER_RESUMEVOL = RegisterTimer(100);
	iTimerResumeMedia = RegisterTimer(600);
	iTimerResumerVolDelay = RegisterTimer(800);

	//m_hardware = PhoneHardwareManager::GetPhoneHardware();


	Notify notify;
	notify.dwParam = this;
	notify.funNotify = CarBrakeChange;
	GXNotify::RegisterNotifyHandler("car_brake_change", notify);


	notify.funNotify = WarnningText;
	GXNotify::RegisterNotifyHandler("warnning_text", notify);

	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);


#ifdef _DEBUG
	SetMainActivity(this);
#endif
	
	//// ����ȡ������
	//Audio::UnMute();
	//DWORD s0 = GetTickCount();

	Activity::CheckAccOff();



	//AVSET::Mute();//�ȹر�����

	

	//DWORD s1 = GetTickCount() - s0;
	//CHAR  show[60];
	//sprintf(show,"time is :%d",s1);
	//std::ofstream   fdfdd("\\NAND\\test1.txt");
	//fdfdd << show << endl;

	m_testTime = RegisterTimer(2000);
	//StartTimer(m_testTime);

	HWND hWndTaskbar = FindWindow(_T("HHTaskbar"),NULL);
	if (NULL != hWndTaskbar)
	{
		::ShowWindow(hWndTaskbar,SW_HIDE);
	}

	bVolResuming = 0;

}

//�ָ���������
LRESULT MainPad::RestoreDefault(DWORD param1, DWORD param2)
{
	ASSERT(m_appGroup);
	m_appGroup->resetToFactory();
	m_groupbtn->resetToFactory();
	return 0;
}
DWORD MainPad::NaviSound(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{
	VersionXml* pVersionXml = VersionXml::GetInstance();
	VersionXml::Option_NaviMixSound bNaviMix = pVersionXml->GetNaviMix();
	if(bNaviMix == VersionXml::Navi_Mix_Removed)	// ������
	{
		return 0;
	}

	MainPad *pMainPad = (MainPad*)dwParam;
	if (wParam == 1)
	{
		RETAILMSG(COUT_MSG, (TEXT("Navi sound start\r\n")));
		if (sysConfig.bRecvPhone == 0)
		{
			pMainPad->StopTimer(pMainPad->iTimerResumeMedia);
			pMainPad->StopTimer(pMainPad->iTIMER_RESUMEVOL);
			pMainPad->StopTimer(pMainPad->iTimerResumerVolDelay);
			pMainPad->bVolResuming = 0;
			// ����������ʼ
			// 1. ����ý�岥������ 

			// 2. ����������
			if (sysConfig.bMute)
			{
				//// �ر���ͨ������,��ʱ��������
				//Audio::SetVolumeTmp(0);
				//Audio::UnMute();
			}
			else 
			{
				if (sysConfig.sysParam.naviTips == 1)
				{
#if 0
					// none
					// ���㵼��������ý�������Ĳ�
					int voldb = Audio::GetVolDistance(sysConfig.sysParam.curGPSVol , Audio::GetVolume());
					//RETAILMSG(COUT_MSG, (TEXT("curGPSVol = %d, curVol = %d\r\n"), sysConfig.sysParam.curGPSVol, sysConfig.sysParam.curVol));
					//RETAILMSG(COUT_MSG, (TEXT("���㵼��������ý�������Ĳ� = %d\r\n"), voldb));
					MediaControl::SetVolume(voldb/2);
					//RETAILMSG(COUT_MSG, (TEXT("������Ϊ = %d\r\n"), voldb*16/10));
					int ipod_vol = 30;
					if (sysConfig.sysParam.curGPSVol > Audio::GetVolume())
					{
						ipod_vol = ipod_vol-(sysConfig.sysParam.curGPSVol - Audio::GetVolume());
						//	RETAILMSG(COUT_MSG, (TEXT("ipod_vol������Ϊ = %d\r\n"), ipod_vol*16/10));
					}
					GXNotify::SendNotify("SetIPODVolume", ipod_vol, -1);
#endif
				}
				else
				{
					if (sysConfig.sysParam.naviAtten == 0)
					{
						// low
						// ���㵼��������ý�������Ĳ�
						int voldb = Audio::GetVolDistance(sysConfig.sysParam.curGPSVol , Audio::GetVolume());
						//RETAILMSG(COUT_MSG, (TEXT("curGPSVol = %d, curVol = %d\r\n"), sysConfig.sysParam.curGPSVol, sysConfig.sysParam.curVol));
						//RETAILMSG(COUT_MSG, (TEXT("���㵼��������ý�������Ĳ� = %d\r\n"), voldb));
						/*if (Audio::GetVolume() > 10)
						{
							voldb += Audio::GetVolDistance2(Audio::GetVolume() , 10);
							Audio::SetMediaVolInNavi(10);						
						}*/
						voldb += Audio::GetVolDistance2(Audio::GetVolume() , Audio::GetVolume()*2/3);
						Audio::SetMediaVolAttenInNavi(1);
						MediaControl::SetVolume(voldb*2/3);
						//RETAILMSG(COUT_MSG, (TEXT("������Ϊ = %d\r\n"), voldb*16/10));
						//int ipod_vol = 30;
						//if (sysConfig.sysParam.curGPSVol*2+5 > sysConfig.sysParam.curVol)
						//{
						//	ipod_vol = ipod_vol-(sysConfig.sysParam.curGPSVol*2+5 - sysConfig.sysParam.curVol)-2;
						//	//	RETAILMSG(COUT_MSG, (TEXT("ipod_vol������Ϊ = %d\r\n"), ipod_vol*16/10));
						//	if(ipod_vol < 0)
						//	{
						//		ipod_vol = 0;
						//	} 
						//}
						int ipod_vol = 30 - voldb/8;
						GXNotify::SendNotify("SetIPODVolume", ipod_vol, -1);
					}
					if (sysConfig.sysParam.naviAtten == 1)
					{
						// mid 
						// ���㵼��������ý�������Ĳ�
						int voldb = Audio::GetVolDistance(sysConfig.sysParam.curGPSVol , Audio::GetVolume());
						/*if (Audio::GetVolume() > 7)
						{
							voldb += Audio::GetVolDistance2(Audio::GetVolume() , 7);
							Audio::SetMediaVolInNavi(7);
						}*/
						voldb += Audio::GetVolDistance2(Audio::GetVolume() , Audio::GetVolume()*1/2);
						Audio::SetMediaVolAttenInNavi(2);
						MediaControl::SetVolume(voldb);

						/*int ipod_vol = 10;
						if (sysConfig.sysParam.curGPSVol*2+5 > sysConfig.sysParam.curVol)
						{
							ipod_vol = ipod_vol-(sysConfig.sysParam.curGPSVol*2+5 - sysConfig.sysParam.curVol);
							if(ipod_vol < 0)
							{
								ipod_vol = 0;
							}
						}*/
						int ipod_vol = 30 - voldb/4;
						GXNotify::SendNotify("SetIPODVolume", ipod_vol, -1);
					}
					if (sysConfig.sysParam.naviAtten == 2)
					{
						// high
						// ���㵼��������ý�������Ĳ�
						int voldb = Audio::GetVolDistance(sysConfig.sysParam.curGPSVol , Audio::GetVolume());
						/*if (Audio::GetVolume() > 5)
						{
							voldb += Audio::GetVolDistance2(Audio::GetVolume() , 5);
							Audio::SetMediaVolInNavi(5);
						}*/
						voldb += Audio::GetVolDistance2(Audio::GetVolume() , Audio::GetVolume()*1/4);
						Audio::SetMediaVolAttenInNavi(3);	
						MediaControl::SetVolume(2*voldb);
						/*int ipod_vol = 5;
						if (sysConfig.sysParam.curGPSVol*2+5 > sysConfig.sysParam.curVol)
						{
							ipod_vol = ipod_vol-(sysConfig.sysParam.curGPSVol*2+5 - sysConfig.sysParam.curVol);
							if(ipod_vol < 0)
							{
								ipod_vol = 0;
							}
						}*/
						int ipod_vol = 30 - voldb/2;
						GXNotify::SendNotify("SetIPODVolume", ipod_vol, 0);
					}
				}
				
			}

			// 3. ����������������������
			Audio::EnterNaviMode();
			//Audio::SetNaviVolume(sysConfig.sysParam.curGPSVol);
			//Sleep(200);
			// 4. ֪ͨ�������Է�����
		//	NaviEvent::NaviOpenSound();
		}
	}
	if (wParam == 0)
	{
		RETAILMSG(COUT_MSG, (TEXT("Navi sound end\r\n")));
		Sleep(200);
		//Audio::ExitNaviMode();
		// ������������
		// 0. �˳�����ģʽ
		if (1)
		{
			if (sysConfig.sysParam.naviTips == 0)
			{
				// 1. �ָ�������, ͬʱ Mix ����Ҳ���ָ�
				//Audio::SetVolume(Audio::GetVolume());
				if (sysConfig.sysParam.naviAtten == 0)
				{
					/*pMainPad->resumeVolTimes = Audio::GetVolume()-10;
					pMainPad->startVol = 10;*/
					
					pMainPad->resumeVolTimes = Audio::GetVolume()-Audio::GetVolume()*2/3;
					pMainPad->startVol = Audio::GetVolume()*2/3;
					Sleep(100);
				}
				if (sysConfig.sysParam.naviAtten == 1)
				{
					/*pMainPad->resumeVolTimes = Audio::GetVolume()-7;
					pMainPad->startVol = 7;
					if (Audio::GetVolume() > 7)
					{
						Sleep(100);
					}*/

					pMainPad->resumeVolTimes = Audio::GetVolume()-Audio::GetVolume()*1/2;
					pMainPad->startVol = Audio::GetVolume()*1/2;
					Sleep(100);

				}
				if (sysConfig.sysParam.naviAtten == 2)
				{
					/*pMainPad->resumeVolTimes = Audio::GetVolume()-5;
					pMainPad->startVol = 5;	
					if (Audio::GetVolume() > 5)
					{
						Sleep(100);
					}*/

					pMainPad->resumeVolTimes = Audio::GetVolume()-Audio::GetVolume()*1/4;
					pMainPad->startVol = Audio::GetVolume()*1/4;
					Sleep(100);
				}	
			}
			Audio::ExitNaviMode(1);	
			if (sysConfig.sysParam.naviTips == 0)
			pMainPad->StartTimer(pMainPad->iTimerResumeMedia);
			//iPodLib::Ipod_SetVolume(30);
			if (pMainPad->resumeVolTimes <= 0)
			{
				pMainPad->resumeVolTimes = 0; 
				Audio::SetMediaVolAttenInNavi(0);
				Audio::SetVolume(Audio::GetVolume());
			}
			else if (sysConfig.sysParam.naviTips == 1)
			{
				// �������ر�
				pMainPad->resumeVolTimes = 0; 
				Audio::SetMediaVolAttenInNavi(0);
				Audio::SetVolume(Audio::GetVolume());
			}
			else
				pMainPad->StartTimer(pMainPad->iTimerResumerVolDelay);//->SetTimer(TIMER_RESUMEVOL, 100, NULL);
			// 2. �ָ�ý������
			if (sysConfig.bMute && sysConfig.bRecvPhone==0)
			{
				Audio::Mute();
			}
		}
		
	}
	return 0;
}


//Ϊ���ṩ���������Ĺ��ܽ� LoadXml�Ӻ�
void MainPad::LoadXml()
{

	m_volType=0;
	m_volTimer1 = RegisterTimer(300);
	m_volTimer2 = RegisterTimer(100);

	SetMsgHandler(WM_MCUINT, MCUEventHandler, (DWORD)this, this);

	LangStringManager::GetInstance()->SetLangID(sysConfig.sysParam.curLang);//�����ȳ�ʼ��
	//LangStringManager::GetInstance()->SetLangID(0);//�����ȳ�ʼ��

	setContentView("layout\\MainPad.xml");
	Activity::onCreate();//������setContentView����
	m_groupbtn = (GxxToolGroup *)findViewByName("icon_group");
	ASSERT(m_groupbtn!=NULL);

	m_commonview = findViewByName("gxx_common");
	ASSERT(NULL!=m_commonview);
	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);

	m_appGroup = (GxxAppGroup *)findViewByName("app_group");
	ASSERT(m_appGroup!=NULL);
	m_isMainPad = true;




	AfxPostMessage(CTR_VOLUME_MAX,Audio::MaxVolume,0);

	

	//MCUEventHandler(NULL, this, 0, MEM_BRAKE_STATUS, 0);

	Notify notify;
	notify.dwParam = this;

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);

	notify.funNotify = NotifyWheel_Msg_Up;
	GXNotify::RegisterNotifyHandler("Wheel_Msg_Up", notify);

	RECT rc;
	::SetRect(&rc,220,15,620,55);
	AfxMessageBox("wait_app_31",5,&rc);//�����ȴ��Ի���
}

LRESULT MainPad::WarnningText(DWORD param1, DWORD param2)
{
	const char *str = (const char *)param1;
	RECT rc;
	::SetRect(&rc,220,15,620,55);
	AfxMessageBox(str,3,&rc,false);
	return 0;
}

LRESULT MainPad::CarBrakeChange(DWORD param1, DWORD param2)
{
	if (sysConfig.sysParam.BrakeDetect)	// 1 �����ɲ��
	{
		// ��������ɲ��,��������Ӧ
		return 0;
	}
	Activity::EnableActivity("SetupActivity", bool(param1));
	Activity::SetBrake(bool(param1));
	return 0;
}

LRESULT MainPad::NotifyWheel_Msg_Up(DWORD param1, DWORD param2)
{
	if (m_volType!=0)
	{
		StopTimer(m_volTimer1);
		StopTimer(m_volTimer2);
		m_volType =0;

	}
	return 0;
}
LRESULT MainPad::NotifyWheel_Msg(DWORD param1, DWORD param2)
{

	int iMsg = param1;
	static int iMode = 0;
	switch(iMsg)
	{
	case HardwareBtnMatch::VOL_ADD_KEY:	// + ����
	//case HardwareBtnMatch::VOL_DEC_KEY:	// - ����
		{
			if (0==param2)
			{
				StartTimer(m_volTimer1);
				m_volType = 1;
			}
			::PostMessage(AfxGetHWND(), WM_MCUINT, KEY_VOLD, 0);

		}
		break;
	case HardwareBtnMatch::VOL_DEC_KEY:	// - ����
	//case HardwareBtnMatch::VOL_ADD_KEY:	// + ����
		{
			if (0==param2)
			{
				StartTimer(m_volTimer1);
				m_volType = 2;
			}
			::PostMessage(AfxGetHWND(), WM_MCUINT, KEY_VOLU, 0);

		}
		break;
	case HardwareBtnMatch::POWER_KEY:	// power off
		{
			::PostMessage(AfxGetHWND(), WM_MCUINT, MEM_SYSTEM_POWER_OFF, 0);
		}
		break;
	case HardwareBtnMatch::MODE_KEY:	//ģʽ
		{
			bool bIsModuleEnable = false;
			bool bGetModuleEnableSuccessOrFail;
			NaviActivity* activity;

			iMode ++;
			iMode = iMode % 9;
			switch(iMode)
			{
			case 0:
				startActivity(NULL,"AuxActivity");
				break;
			case 1:
				if (Activity::s_bluetooth_exist)
				{
					startActivity(NULL,"BTMusicActivity");
					break;
				}
				else
				{
					iMode ++;
				}
			case 2:
				//startActivity(NULL,"DiscActivity");
				bGetModuleEnableSuccessOrFail = AppManage::GetAppEnable("DiscActivity", bIsModuleEnable);
				if(bGetModuleEnableSuccessOrFail && bIsModuleEnable)	//���سɹ�����IPOD��Ч
				{
					startActivity(NULL,"DiscActivity");
					break;
				}
				else	//������һ��ģʽ
				{
					iMode ++;
				}
				
			case 3:
				startActivity(NULL,"DTVActivity");
				break;
			case 4:
				bGetModuleEnableSuccessOrFail = AppManage::GetAppEnable("IPODActivity", bIsModuleEnable);
				if(bGetModuleEnableSuccessOrFail && bIsModuleEnable)	//���سɹ�����IPOD��Ч
				{
					startActivity(NULL,"IPODActivity");
					break;
				}
				else	//������һ��ģʽ
				{
					iMode ++;
				}
				
				
			case 5:
				bGetModuleEnableSuccessOrFail = AppManage::GetAppEnable("NaviActivity", bIsModuleEnable);
				if(bGetModuleEnableSuccessOrFail && bIsModuleEnable)	//���سɹ�����IPOD��Ч
				{
					startActivity(NULL,"NaviActivity");

					activity = (NaviActivity*)findActivity("NaviActivity");
					if(!activity->IsNaviOn())
					{
						activity->ShowNavi();
					}
					break;
				}
				else	//������һ��ģʽ
				{
					iMode ++;
				}
				
				break;
			case 6:
				//��һģʽ�ǵ�����������������ˣ����ص���
				activity = (NaviActivity*)findActivity("NaviActivity");
				if(activity->IsNaviOn())
				{
					activity->HideNavi();
				}

				if (Activity::s_bluetooth_exist)
				{
					startActivity(NULL,"PhoneActivity");
					break;
				}
				else
				{
					
					iMode ++;
				}
			case 7:
				startActivity(NULL,"RadioActivity");
				break;
			case 8:
				bGetModuleEnableSuccessOrFail = AppManage::GetAppEnable("USBActivity", bIsModuleEnable);
				if(bGetModuleEnableSuccessOrFail && bIsModuleEnable)	//���سɹ�����IPOD��Ч
				{
					startActivity(NULL,"USBActivity");
					break;
				}
				else	//������һ��ģʽ
				{
					iMode ++;
				}
				
			}
		}
		break;

	}
	return 0;
}



//����������tool up G 
void MainPad::onResume()
{
	m_commonview->setDraw(true);
	m_groupbtn->startAnimation(TRUE);
	m_groupbtn->setLock(TRUE);
}

void MainPad::onPause()
{
	m_groupbtn->setLock(FALSE);
	m_groupbtn->startAnimation(FALSE);
}

BOOL MainPad::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
#ifdef _DEBUG
	case TEST_ACTIVITY:
		{
			int nth = AppManage::GetInstance()->GetActivityNth( (Activity *)wParam);
			if (nth<0)
			{
				nth = 100;//��ҳ��Ϊ100
			}
			sysConfig.sysParam.curNthTestActivity = nth+9;
			sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curNthTestActivity);
		}

		return 0;
#endif
	case CTR_MAIN_LOAD:
		LoadXml();
		LanchModule();
		Hardware::ExtAMPPower(1);
		
		return TRUE;
	case CTR_ENTER_EDIT_MODE:
		m_appGroup->SetEidtMode(true);
		return TRUE;
	case CTR_EXIT_EDIT_MODE:
		m_appGroup->SetEidtMode(false);
		return TRUE;
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				if (!m_appGroup->SetEidtMode(false))
				{
					RetToFucActivity();//���ع��ܽ���
				}
				return TRUE;
			}
		}
		return FALSE;
	default:
		return FALSE;
	}
	return FALSE;
}


DWORD MainPad::MCUEventHandler(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{
	MainPad *pMainWnd = (MainPad *)dwParam;
	BYTE ircode = 0;	// Ϊ���ó����ܹ�������ȡ��״̬��Ϣ,���ǽ�������Ƭ���ж� 010427
	if (wParam != 0)
	{
		ircode = wParam;
	}
	else
	{
		ircode = Hardware::ReadHardwareCode();
	}


	// ��������
	switch(ircode)
	{
	case KEY_VOLD:	//����-
		{
			//������
			GxxBeep *beep = GxxBeep::GetInstance();
			if (beep && beep->GetIsBeep())
			{
				AVSET::Beep();
				//Sleep(50);	//�ӳ�һ�㣬��֤������
			}
			if (pMainWnd->bVolResuming)
			{
				// �����ָ�������,��ֹ������
				break;
			}
			//Ϊ��Ӧ��ɽ�Ļ�����RELEASE�汾������һ��
			#if _DEBUG
				AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"DecVolume", 1);
			#else
				AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"AddVolume", 1);
			#endif

			//float iNaviVolPercent = VolumeControl::GetCurrentNaviVolPercent();
			//ASSERT(false);
		}
		break;
	case KEY_VOLU:	//����+
		{
			if (StrHelp::SaveScreen())
			{
				//break;
			}
			//������
			GxxBeep *beep = GxxBeep::GetInstance();
			if (beep && beep->GetIsBeep())
			{
				AVSET::Beep();
				//Sleep(50);	//�ӳ�һ�㣬��֤������
			}
			if (pMainWnd->bVolResuming)
			{
				// �����ָ�������,��ֹ������
				break;
			}
			//Ϊ��Ӧ��ɽ�Ļ�����RELEASE�汾������һ��
			#if _DEBUG
				AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"AddVolume", 1);
			#else
				AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"DecVolume", 1);
			#endif

			//float iNaviVolPercent = VolumeControl::GetCurrentNaviVolPercent();
			//ASSERT(false);
			
		}
		break;
	case KEY_DVD:	//������Ƭ
		{
			//������
			GxxBeep *beep = GxxBeep::GetInstance();
			if (beep && beep->GetIsBeep())
			{
				AVSET::Beep();
			}			

			//�����ڿ���ʱ������ѡ�������
			if(!Activity::S_isPowerInLanguage)
			{
				GXNotify::SendNotify("NotifyEject", 0, 0);
			}
			
		}
		break;
	case MEM_BACK_STATUS:
		{
			if (Hardware::ReadBack())
			{
				// ����״̬,��Ҫ��ֹ��Ƶ��ʾ,ͬɲ��,���ǲ�Ҫ�����ַ�
				//GXNotify::SendNotify("car_brake_change", 1, 0);  ����Ҫ
			}
			else
			{
				// �ָ���Ƶ��ʾ
				//GXNotify::SendNotify("car_brake_change", 0, 0);  ����Ҫ
			}
		}
		break;
	case MEM_LIGHT_STATUS:	// ��Ƽ���
		{
			if (Hardware::ReadLight())
			{
				// ������Ļ����
				AVSET::LCDBrightDown();
			}
			else
			{
				// �����Ļ����
				AVSET::LCDBrightResume();
			}
		}
		break;
	case MEM_BRAKE_STATUS:
		{
			// ��״̬
			//bit 1 : brake;
			BYTE brake_status = Hardware::ReadBrake();
#ifdef _DEBUG
			sysConfig.sysParam.BrakeDetect = 1;	// ��Ϊ���Ի�������ɲ��û������,��ʱ����
#endif
			
			if (sysConfig.sysParam.BrakeDetect == 0)
			{
				if (brake_status)
				{
					GXNotify::SendNotify("car_brake_change", 1, 0);	//�Ѿ�ɲ��
				}
				else
				{

					GXNotify::SendNotify("car_brake_change", 0, 0);//���ڼ�ʻ
				}
			}
			else
			{
				if (brake_status == 0)
				{
					GXNotify::SendNotify("car_brake_change", 0, 0);
				}
			}

		}
		break;
	case MEM_POWER_KEY:	//��������
		{
			//������
			GxxBeep *beep = GxxBeep::GetInstance();
			if (beep && beep->GetIsBeep())
			{
				AVSET::Beep();
			}

			switch(Hardware::ReadPowerKey())
			{
			case 0:
				{

				}
				break;
			case 1:	// �̰�
				{
					AfxPostMessage( MCU_POPMENU, 0, 0 );
				}
				break;
			case 2:	// ����
				{
					GXNotify::SendNotify("HideNavi", 0, 0);
					AfxPostMessage( MCU_POPMENU_LONG, 0, 0 );
				}
				break;
			}
		}
		break;
	case MEM_SYSTEM_POWER_OFF:
		{
			//������
			GxxBeep *beep = GxxBeep::GetInstance();
			if (beep && beep->GetIsBeep())
			{
				AVSET::Beep();
			}

			//sysConfig.sysParam.curbBtnPower = ACC_POWER_OFF;
			//sysConfig.WriteConfig(&sysConfig.sysParam.curbBtnPower);

			int nth = AppManage::GetInstance()->GetActivityNth(GetFuctionAct());
			sysConfig.sysParam.curNthStartActivity = nth;
			sysConfig.WriteConfig(&sysConfig.sysParam.curNthStartActivity);
			RETAILMSG(COUT_MSG, (TEXT("curNthStartActivity = %d\n"), sysConfig.sysParam.curNthStartActivity));
			// �ر�ϵͳ 
			// ����Ļ
			RETAILMSG(COUT_MSG,(TEXT("Power Off -1-----------------------\r\n")));
			AVSET::BackLight(0);
		
			//����
			AVSET::Mute();
			Sleep(1000);
			RETAILMSG(COUT_MSG,(TEXT("Power Off 0-----------------------\r\n")));

			GXNotify::SendNotify("power_off", 0, 0);

			// ����ȷ�Ϲػ�����
			Hardware::PowerDownSystem();
		}
		break;
	case MEM_IR_ARM:
		{
//			BYTE ircode = Hardware::ReadIRCode();
//			switch(ircode)
//			{
//			case 0x14:
//				{
//					if (StrHelp::SaveScreen())
//					{
//						//break;
//					}
//					//������
//					GxxBeep *beep = GxxBeep::GetInstance();
//					if (beep && beep->GetIsBeep())
//					{
//						AVSET::Beep();
//						//Sleep(50);	//�ӳ�һ�㣬��֤������
//					}
//					if (pMainWnd->bVolResuming)
//					{
//						// �����ָ�������,��ֹ������
//						break;
//					}
//					//Ϊ��Ӧ��ɽ�Ļ�����RELEASE�汾������һ��
//#if _DEBUG
//					AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"AddVolume", 1);
//#else
//					AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"DecVolume", 1);
//#endif
//
//					//float iNaviVolPercent = VolumeControl::GetCurrentNaviVolPercent();
//					//ASSERT(false);
//					break;
//				}
//			case 0x15:
//				{
//					//������
//					GxxBeep *beep = GxxBeep::GetInstance();
//					if (beep && beep->GetIsBeep())
//					{
//						AVSET::Beep();
//						//Sleep(50);	//�ӳ�һ�㣬��֤������
//					}
//					if (pMainWnd->bVolResuming)
//					{
//						// �����ָ�������,��ֹ������
//						break;
//					}
//					//Ϊ��Ӧ��ɽ�Ļ�����RELEASE�汾������һ��
//#if _DEBUG
//					AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"DecVolume", 1);
//#else
//					AfxPostMessage(CTR_VOLUME_MES, (WPARAM)"AddVolume", 1);
//#endif
//
//					//float iNaviVolPercent = VolumeControl::GetCurrentNaviVolPercent();
//					//ASSERT(false);
//					break;
//				}
//			}
//			break;
		}
	}
	return 0;
}

//#define  _TEST_DEBUG  //DEBUG�� �Ƿ�������
void MainPad::LanchModule()
{
	string toStart;
	SYSTEMTIME systime;
	

	if (Activity::s_isAccOff)//ACC_POWER_OFF ����ʹ��
	{
		T_AppModule* tm = AppManage::GetInstance()->GetModule(sysConfig.sysParam.curNthStartActivity);
		RETAILMSG(COUT_MSG, (TEXT("curNthStartActivity = %d\n"), sysConfig.sysParam.curNthStartActivity));
		if (tm&&tm->b_enable)
		{
			toStart = tm->activity;
			//Activity::startActivity(NULL,tm->activity);
		}
		else if (tm)
		{
			if ("DiscActivity" == tm->activity)
			{
				toStart = "DiscActivity";
			}
		}
		else
		{
			toStart = "RadioActivity";
			//Activity::startActivity(NULL,"RadioActivity");
		}
	}
	else
	{//B+ �ϵ�

		//��ʱ��
		
		GetLocalTime(&systime);
		//if (systime.wYear < 2013 || (systime.wYear== 2013 && systime.wMonth<9) )
		{
			systime.wYear = 2013;
			systime.wMonth = 9;
			systime.wDay = 1;
			systime.wHour = 0;
			systime.wMinute = 0;
			SetLocalTime(&systime);
		}
#if _DEBUG// sysConfig.sysParam.curNthTestActivity
//#ifndef _DEBUG
		#ifdef  _TEST_DEBUG
			int ntest = sysConfig.sysParam.curNthTestActivity;
			ntest -= 9;
			if (ntest==100)
			{
				toStart = "MainPad";
				//Activity::startActivity(NULL,"MainPad");
			}
			else
			{
				T_AppModule* tm = AppManage::GetInstance()->GetModule(ntest);
				if (tm)
				{
					toStart = tm->activity;
					//Activity::startActivity(NULL,tm->activity);
				}
				else
				{
					toStart = "RadioActivity";
					//Activity::startActivity(NULL,"RadioActivity");
				}
			}
		#else
			//toStart = "RadioActivity";   
			//Activity::startActivity(NULL,"RadioActivity");
			Activity::s_is_init_sound = false;
			Activity::startActivity(NULL,"LangChooseActivity","power_on");
			
		#endif
		//
#else

		Activity::s_is_init_sound = false;
		Activity::startActivity(NULL,"LangChooseActivity","power_on");

#endif
		
	}

	if (!Activity::s_is_init_sound || sysConfig.sysParam.curbMute)//�������Խ��� ����
	{
		AVSET::Mute();//�ȹر�����
	}
	else
	{
		AVSET::UnMute();//������
	}

	if (toStart == "MainPad"|| toStart == "SetupActivity")
	{
		Activity::startActivity(NULL,toStart);
	}
	else if (!toStart.empty())
	{
		TMapStr_Str::iterator pos = S_ActivityDllContainer.find(toStart);
		if (pos != S_ActivityDllContainer.end())
		{
			Activity::loadDllModule(pos->second.c_str(),pos->first.c_str());
			Activity::startActivity(NULL,toStart);
			S_ActivityDllContainer.erase(pos);
		}
	}
	//sysConfig.sysParam.curbBtnPower = 0;
	//sysConfig.WriteConfig(&sysConfig.sysParam.curbBtnPower);

	sysConfig.sysParam.curNthStartActivity = -1;
	sysConfig.WriteConfig(&sysConfig.sysParam.curNthStartActivity);
}


void MainPad::TimerTick( UINT nIDEvent )
{
	if (nIDEvent==m_volTimer1)
	{
		if (1==m_volType){
			::PostMessage(AfxGetHWND(), WM_MCUINT, KEY_VOLD, 0);
			StartTimer(m_volTimer2);
		}
		else if(2==m_volType){
			::PostMessage(AfxGetHWND(), WM_MCUINT, KEY_VOLU, 0);
			StartTimer(m_volTimer2);
		}
		StopTimer(m_volTimer1);
	}

	else if (nIDEvent==m_volTimer2)
	{
		if (1==m_volType){
			::PostMessage(AfxGetHWND(), WM_MCUINT, KEY_VOLD, 0);
		}
		else if(2==m_volType){
			::PostMessage(AfxGetHWND(), WM_MCUINT, KEY_VOLU, 0);
		}
	}
	if (nIDEvent == iTimerResumeMedia)
	{
		Audio::ExitNaviMode();
		MediaControl::ResumeVolume();
		GXNotify::SendNotify("SetIPODVolume", 30, -1);
		StopTimer(iTimerResumeMedia);
	}
	if (nIDEvent == iTimerResumerVolDelay)
	{
		StopTimer(iTimerResumerVolDelay);
		StartTimer(iTIMER_RESUMEVOL);
	}
	if (nIDEvent == iTIMER_RESUMEVOL)
	{
		bVolResuming = 1;
		Audio::SetMediaVolAttenInNavi(0);
		Audio::SetVolumeTmp(Audio::GetVolume()-(--resumeVolTimes));
		if (resumeVolTimes == 0)
		{
			StopTimer(iTIMER_RESUMEVOL);
			Audio::SetVolume(Audio::GetVolume());
			bVolResuming = 0;
		}
	}

	if (nIDEvent == m_testTime)
	{
		static int testTimers = 0;
		RETAILMSG(1, (TEXT("Auto Test = %d\r\n"), testTimers++));
		if( Activity::GetActiveActiviy() == (MainPad*)this)
		{
			// �л��� dvd
			Activity::startActivity(NULL,"DiscActivity");
		}
		else
		{
			// �л�����ҳ��
			Activity::startActivity(NULL,"MainPad");
		}
	}
	
}




static RegisterHelp help("MainPad", MainPad::CreateControl);