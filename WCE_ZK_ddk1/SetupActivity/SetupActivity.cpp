#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "SetupActivity.h"
#include "ControlHelp.h"
#include "GxxSetupListGroup.h"
#include "GxxFileListGroup.h"
#include "SetupTimeManager.h"
#include "SetupVolumeManager.h"
#include "SetupNormalManager.h"
#include "SetupDislayManager.h"
#include "SetupBlueToothManager.h"
#include "SetupCameraManager.h"
#include "SetupNaviManager.h"
#include "SetupAuxManager.h"
#include "SetupApplyManager.h"
#include "SetupBMTManager.h"
#include "GxxAniLable.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "Version.h"
#include "GxxSetupListLine.h"

 
const  wstring WS_MUSIC = L"mp3_wma_mp2_ogg_aac_flac_ape_wav_ra";


const  wstring WS_MOVIE = L"avi_wmv_mpg_mp4_rmvb_ts_m2ts_tp_mov_vob_mkv_3gp_3ga_asf_divx_trp_flv_rm_mpeg_m4v_m2v";



const  wstring WS_PICTURE = L"jpg_png_bmp_gif";


const  wstring WS_PATH = L"\\NAND\\ZKYApp\\";

#define FILE_LIST_BOX 0
//file_box_group
Activity* SetupActivity::CreateControl()
{
	return new SetupActivity;
}

SetupActivity::SetupActivity()
{
	m_bt_input = NULL;
	m_f_type = Null_type;
	m_bt_password = "0000";
	m_phoneHardware = NULL;
}


//恢复出厂设置
LRESULT SetupActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	ASSERT(m_phoneHardware);
	m_phoneHardware->SetPassword("0000");
	m_phoneHardware->ReadPassword();
	return 0;

}
void SetupActivity::onCreate()
{
	Activity::onCreate();

	//if (Activity::s_no_bluetooth)//
	//{
	//	setContentView("layout\\SetupPad_no_bluetooth.xml");
	//}
	//else
	//{
	//	setContentView("layout\\SetupPad.xml");
	//}
	setContentView("layout\\SetupPad.xml");

	setBackColor(0xffff0000);
	string path;
	AfxGetWorkPathA(path);
	m_lb_group = (GxxSetupListGroup *)findViewByName("box_group");
	ASSERT(NULL!=m_lb_group);


	m_btx = findViewByName("x_btn");
	m_btnBack = findViewByName("back_btn");
	ASSERT(m_btnBack!=NULL && m_btx!=NULL);

	SetupNormalManager::GetInstance();//
	SetupBlueToothManager::GetInstance();//
	//SetupAuxManager::GetInstance();//
	SetupDislayManager::GetInstance();
	SetupBMTManager::GetInstance();
	SetupVolumeManager::GetInstance();
	SetupApplyManager::GetInstance();
	SetupNaviManager::GetInstance();
	SetupTimeManager::GetInstance();

	findActivity("BtnMatchActivity");//启动方控 
	findActivity("BassActivity");//启动低音均衡器
	findActivity("BSFActivity");//启动低音均衡器 
	findActivity("ParametricEqPad");//PEQ 
	findActivity("TimeCorrectPad");//

	Notify notify;

	notify.dwParam = this;
	notify.funNotify = BtStatusNotify;
	GXNotify::RegisterNotifyHandler("phonepassword", notify);


	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

	m_phoneHardware = PhoneHardwareManager::GetPhoneHardware();
	m_phoneHardware->ReadPassword();


	//if (!m_phoneHardware->IsExist())
	//{
	//	GxxView *blist_v =  GxxSetupListGroup::S_FindList("2_normal_setup");
	//	GxxSetupListLine *bline_v = (GxxSetupListLine *)blist_v->safeFindViewByName("bluetooth_set");
	//	bline_v->SetLineEnable(FALSE);
	//}


	m_boot_version_txt = NULL;
	//m_Timer = RegisterTimer(2000);


	
}
 

BOOL SetupActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case	CTR_LIST_BACK_ACTIVITY://back_btn
	case	CTR_BTN_MATCH_BACK:
		if (!finish())
		{
			startActivity(NULL,"MainPad");
		}
		return TRUE;
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				RetToFucActivity();
				return TRUE;
			}
			if ( m_bt_input!=NULL && (GxxAniLable *)wParam == m_bt_input)
			{
				Activity::SetContentInt("num",4);
				Activity::SetContentStr("title_id","bt_input_title");
				m_f_type = InputPassword;
				Activity::startActivity(this,"InputActivity");
				return TRUE;
			}
		}
		return FALSE;
	case  CTR_SETUP_START_ACTIVITY:
		StartSetupActivity(wParam);
		return TRUE;
	case  CTR_SETUP_START_LISTBOX:
		StartSetupListBox( (const char* )wParam, (int)lParam);
		return TRUE;
	case CTR_SETUP_START_MASSAGE:
		StartSetupMassage(wParam);
		return TRUE;
	case CTR_VOLUME_MES:
		if (m_bReRead)
		{
			AfxPostMessage(CTR_SETUP_READ_LIST,0,0);
		}
		return FALSE;
	case  MES_MSG_CANCEL:
		return TRUE;
	case  MES_MSG_OK:
		GXNotify::SendNotify("restore_factory_set", 0, 0);
		return TRUE;
	case MES_ADD_VEDIO_SET://全屏的时候调用视频设置
		SetupDislayManager::GetInstance()->SetFucPos();
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}

void SetupActivity::onResume()
{
	if (m_param == "finish")//说明子Activity finish；
	{
		if (m_f_type==InputPassword)
		{
			string s;
			if (Activity::GetContentStr("password",s))
			{
				//ASSERT(m_bt_input!=NULL);
				//m_bt_input->SetText(s.c_str());
				SetBluePassword(s);
			}
			//
		}
	}
	else if (m_param.size()!=0)//启动到
	{
		StartSetupListBox(m_param,0);//0表示第一次启动
	}
	else
	{
		StartSetupListBox("setup_box",0);//0表示第一次启动
	}
	//StartTimer(m_Timer);
} 

void SetupActivity::onPause()
{
	//StopTimer(m_Timer);
}

void SetupActivity::StartSetupActivity(WPARAM wParam)
{
	string str = (const char* )wParam;
	startActivity(this,str);
}

void SetupActivity::StartSetupMassage( WPARAM wParam )
{
	string str = (const char* )wParam;
	if (str == "calibration_msg")
	{
		TouchCalibrate();
	}
	else if (str == "factory_msg")
	{
		AfxMessageBox("factory_31",this,0,ZKY_MB_OKCANCEL);
	}
}

void SetupActivity::TouchCalibrate()
{
	HINSTANCE  hinstance = LoadLibrary(_T("coredll.dll")); 
	if  (hinstance == NULL)
	{
		return;
	}
	typedef  BOOL    (WINAPI *_TouchCalibrate)(); 
	_TouchCalibrate TouchCalibrate = NULL;
	TouchCalibrate = (_TouchCalibrate)GetProcAddress(hinstance , L"TouchCalibrate");
	if (TouchCalibrate != NULL)
	{
		TouchCalibrate();
	}
	FreeLibrary(hinstance);
}
//bReturn = 0表示第一次进入setup
//bReturn = 1表示第一次以后进入不同的setup
//bReturn = 2表示setup回退
void SetupActivity::StartSetupListBox( const string & name,int bReturn )
{
	m_bReRead = false;
	m_lb_group->setActiveListBox(name,bReturn);
	if (name == "4_time_set"||name == "3_normal_time_setup")
	{
		SetupTimeManager::GetInstance()->SetFucPos();
		if (name == "4_time_set")
		{
			//GxxSwText * pText = ((GxxSetupListLine *)safeFindViewByName("AutoAdjustSwith"))->GetTitleText();
			//SetupTimeManager::GetInstance()->SetAjustText(pText);
		}
		
	}
	else if (name == "3_sound_setup")
	{
		m_bReRead = true;
		SetupVolumeManager::GetInstance()->SetFucPos();
	}
	else if (name == "2_normal_setup"|| name == "2_sound_setup")
	{
		SetupNormalManager::GetInstance()->SetFucPos();
	}
	else if (name == "3_screen_setup" || name == "3_video_setup")
	{
		SetupDislayManager::GetInstance()->SetFucPos();
	}
	else if (name == "3_bluetooth_setup" )
	{
		SetupBlueToothManager::GetInstance()->SetFucPos();
		if (m_bt_input==NULL)
		{
			m_bt_input = (GxxAniLable *)safeFindViewByName("input_view");	
			m_bt_input->SetText(m_bt_password.c_str());
			//GXNotify::SendNotify("NotifyReadBTPassword", 0,0);
		}
	}
	//else if (name == "3_camera_set")//这一项 没有作用了
	//{
	//	SetupCameraManager::GetInstance()->SetFucPos();
	//}
	else if (name == "3_navi_set")
	{
		SetupNaviManager::GetInstance()->SetFucPos();
	}
	//else if (name == "3_AUX_set")//这一项 没有作用了
	//{
	//	SetupAuxManager::GetInstance()->SetFucPos();
	//}
	else if (name == "2_apply_setup" )
	{
		SetupApplyManager::GetInstance()->SetFucPos();
	}
	else if (name == "3_bmt_setup")
	{
		SetupBMTManager::GetInstance()->SetFucPos();
	}
	else if (name == "3_about_more_setup")
	{
		if (NULL == m_boot_version_txt)
		{
			m_boot_version_txt = (GxxSwText *)safeFindViewByName("boot_version_txt");
			m_boot_version_txt->setText(Version::BootVersion().c_str());

			GxxSwText *v_text = (GxxSwText *)safeFindViewByName("nk_version_txt");
			v_text->setText(Version::CoreVersion().c_str());

			v_text = (GxxSwText *)safeFindViewByName("app_version_txt");
			v_text->setText(Version::APPVersion().c_str());

			v_text = (GxxSwText *)safeFindViewByName("bluetooth_version_txt");
			wstring wv = m_phoneHardware->GetVersion().GetData();
			v_text->setText(wv);
			//v_text->setText(Version::BTModuleVersion().c_str());

			v_text = (GxxSwText *)safeFindViewByName("mcu_version_txt");
			v_text->setText(Version::MCUVersion().c_str());
		}
		SetupApplyManager::GetInstance()->SetFucPos();
		

	}
	else
	{
		//ASSERT(0);
		return;
	}
	AfxPostMessage(CTR_SETUP_READ_CURSOR,0,0);
	AfxPostMessage(CTR_SETUP_READ_LIST,0,0);
	
}

void SetupActivity::SetBluePassword(  const string& s )
{
	ASSERT(s.size() == 4);
	m_phoneHardware->SetPassword(s.c_str());
	m_phoneHardware->ReadPassword();

}

LRESULT SetupActivity::BtStatusNotify(DWORD param1, DWORD param2)
{
	const char * s = (const char *)param1;
	if (s!=NULL)
	{
		m_bt_password = s;
		ASSERT(m_bt_password.size() == 4);
	}

	if (m_bt_input!=NULL)
	{
		m_bt_input->SetText(s);
	}
	
	return 0;
}

//void SetupActivity::TimerTick( UINT nIDEvent )
//{
//	SetupTimeManager::GetInstance()->CheckCaliDone();
//}




static RegisterHelp help("SetupActivity", SetupActivity::CreateControl);