#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "TimeCorrectPad.h"
#include "ControlHelp.h"
#include "GxxSetupListGroup.h"
#include "GxxFileListGroup.h"
#include "GxxAniLable.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "GxxSwText.h"
#include "AVSet.h"
#include "GxxParamPad.h"
#include "GxxPicIcon.h"
#include "VersionXml.h"
#include "StrHelp.h"

#define  SUM_VALUE 200
//#define  MAX_VALUE 60
#define  MAX_PRESET 3
static RegisterHelp help("TimeCorrectPad", TimeCorrectPad::CreateControl);
Activity* TimeCorrectPad::CreateControl()
{
	return new TimeCorrectPad;
}

TimeCorrectPad::TimeCorrectPad():
m_presetTimeFrontL(sysConfig.sysParam.presetTimeFrontL),
m_presetTimeFrontR(sysConfig.sysParam.presetTimeFrontR),
m_presetTimeRearL (sysConfig.sysParam.presetTimeRearL),
m_presetTimeRearR (sysConfig.sysParam.presetTimeRearR),
m_presetSubwL (sysConfig.sysParam.presetSubwL),
m_presetSubwR (sysConfig.sysParam.presetSubwR)
{


}


TimeCorrectPad::~TimeCorrectPad()
{

}



void TimeCorrectPad::onCreate()
{
	Activity::onCreate();
	//if (VersionXml::Navi_BSF_Added == VersionXml::GetInstance()->GetBSFModule())
	//{
	//	setContentView("layout\\TimeCorrectPad.xml");
	//}
	//else
	{
		setContentView("layout\\TimeCorrectPad.xml");
	}
	
	setBackColor(0xffff0000);
	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);
	m_btnBack = findViewByName("back_btn");
	ASSERT(m_btnBack!=NULL);

	m_txtRemainVal = (GxxSwText *)safeFindViewByName("remain_val");

	m_txtCm = (GxxSwText *)safeFindViewByName("cm_text");
	m_txtMsec = (GxxSwText *)safeFindViewByName("msec_text");

	m_s_txtCm = (GxxSwText *)safeFindViewByName("s_cm_txt");
	m_s_txtMsec = (GxxSwText *)safeFindViewByName("s_ms_txt");

	m_txtMsec->setDraw(false);
	m_s_txtCm->setDraw(false);
	m_isMsec = true;

	m_flat = (GxxAniLable *)safeFindViewByName("flat_btn");
	m_cm_msec = (GxxAniLable *)safeFindViewByName("msec_cm_btn");
	m_preset1 = (GxxAniLable *)safeFindViewByName("preset1_btn");
	m_preset2 = (GxxAniLable *)safeFindViewByName("preset2_btn");
	m_preset3 = (GxxAniLable *)safeFindViewByName("preset3_btn");

	m_frontL_left = (GxxAniLable *)safeFindViewByName("Front_L_BtnL");
	m_frontL_mid = (GxxAniLable *)safeFindViewByName("Front_L_Mid");
	m_frontL_right = (GxxAniLable *)safeFindViewByName("Front_L_BtnR");
	m_frontR_left = (GxxAniLable *)safeFindViewByName("Front_R_BtnL");
	m_frontR_mid = (GxxAniLable *)safeFindViewByName("Front_R_Mid");
	m_frontR_right = (GxxAniLable *)safeFindViewByName("Front_R_BtnR");

	m_rearL_left = (GxxAniLable *)safeFindViewByName("Rear_L_BtnL");
	m_rearL_mid = (GxxAniLable *)safeFindViewByName("Rear_L_Mid");
	m_rearL_right = (GxxAniLable *)safeFindViewByName("Rear_L_BtnR");
	m_rearR_left = (GxxAniLable *)safeFindViewByName("Rear_R_BtnL");
	m_rearR_mid = (GxxAniLable *)safeFindViewByName("Rear_R_Mid");
	m_rearR_right = (GxxAniLable *)safeFindViewByName("Rear_R_BtnR");

	m_subwL_left = (GxxAniLable *)safeFindViewByName("SubW_L_BtnL");
	m_subwL_mid = (GxxAniLable *)safeFindViewByName("SubW_L_Mid");
	m_subwL_right = (GxxAniLable *)safeFindViewByName("SubW_L_BtnR");
	m_subwR_left = (GxxAniLable *)safeFindViewByName("SubW_R_BtnL");
	m_subwR_mid = (GxxAniLable *)safeFindViewByName("SubW_R_Mid");
	m_subwR_right = (GxxAniLable *)safeFindViewByName("SubW_R_BtnR");



	m_frontL_pic = (GxxPicIcon *)safeFindViewByName("s_frontL_pic");
	m_frontR_pic = (GxxPicIcon *)safeFindViewByName("s_frontR_pic");

	m_rearL_pic = (GxxPicIcon *)safeFindViewByName("s_rearL_pic");
	m_rearR_pic = (GxxPicIcon *)safeFindViewByName("s_rearR_pic");

	m_subwL_pic = (GxxPicIcon *)safeFindViewByName("s_subwL_pic");
	m_subwR_pic = (GxxPicIcon *)safeFindViewByName("s_subwR_pic");

	if (VersionXml::Navi_BSF_Removed == VersionXml::GetInstance()->GetBSFModule())
	{
		safeFindViewByName("SubW_L_Text")->setDraw(false);
		safeFindViewByName("SubW_R_Text")->setDraw(false);

		safeFindViewByName("subwL_pic")->setDraw(false);
		safeFindViewByName("subwR_pic")->setDraw(false);

		m_subwL_left->setDraw(false);
		m_subwL_mid->setDraw(false);
		m_subwL_right->setDraw(false);
		m_subwR_left->setDraw(false);
		m_subwR_mid->setDraw(false);
		m_subwR_right->setDraw(false);
	}
	else
	{
		//重低音右硬件暂时不支持
		safeFindViewByName("SubW_R_Text")->setDraw(false);
		safeFindViewByName("subwR_pic")->setDraw(false);

		m_subwR_left->setDraw(false);
		m_subwR_mid->setDraw(false);
		m_subwR_right->setDraw(false);
	}

	m_frontL_pic->setDraw(false);
	m_frontR_pic->setDraw(false);
	m_rearL_pic->setDraw(false);
	m_rearR_pic->setDraw(false);

	m_subwL_pic->setDraw(false);
	m_subwR_pic->setDraw(false);

	m_set_pic = NULL;


	//SetInZone(sysConfig.sysParam.curTimeFrontL);
	//SetInZone(sysConfig.sysParam.curTimeFrontR);
	//SetInZone(sysConfig.sysParam.curTimeRearL);
	//SetInZone(sysConfig.sysParam.curTimeRearR);

	//for (int i = 0;i< MAX_PRESET;i++)
	//{
	//	SetInZone(m_presetTimeFrontL[i]);
	//	SetInZone(m_presetTimeFrontR[i]);
	//	SetInZone(m_presetTimeRearL[i]);
	//	SetInZone(m_presetTimeRearR[i]);
	//}

	SetTimeVal(AVSET::AUDIOCH_FL);
	SetTimeVal(AVSET::AUDIOCH_FR);
	SetTimeVal(AVSET::AUDIOCH_RL);
	SetTimeVal(AVSET::AUDIOCH_RR);
	SetTimeVal(AVSET::AUDIOCH_SubWL);
	SetTimeVal(AVSET::AUDIOCH_SubWR);

	SetMidText(AVSET::AUDIOCH_FL);
	SetMidText(AVSET::AUDIOCH_FR);
	SetMidText(AVSET::AUDIOCH_RL);
	SetMidText(AVSET::AUDIOCH_RR);
	SetMidText(AVSET::AUDIOCH_SubWL);
	SetMidText(AVSET::AUDIOCH_SubWR);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

}

//恢复出厂设置
LRESULT TimeCorrectPad::RestoreDefault(DWORD param1, DWORD param2)
{
	SetFlat();
	SavePreset(0);
	SavePreset(1);
	SavePreset(2);
	m_preset1->SetSelect(false);
	m_preset2->SetSelect(false);
	m_preset3->SetSelect(false);
	return 0;
}

void TimeCorrectPad::onResume()
{

}




BOOL TimeCorrectPad::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message == WM_LBUTTONUP&& m_set_pic != NULL)
	{
		m_set_pic->setDraw(false);
		m_set_pic->invalidateRect();
		m_set_pic = NULL;
	}
	return Activity::DealCtrlMsg(message, wParam,lParam);
}

BOOL TimeCorrectPad::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case	CTR_BTN_MATCH_BACK://方控
		finish();
		return TRUE;
	case MES_INVALIDATE:
		return TRUE;
	case CTR_MESSAGE:
		if (MES_LBUTTONLONG == lParam)
		{
			if ((GxxAniLable *)wParam == m_preset1)
			{
				SavePreset(0);


				m_preset1->SetSelect(false);
				m_preset2->SetSelect(false);
				m_preset3->SetSelect(false);

				m_preset1->SetSelect(true);


				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset2)
			{
				SavePreset(1);


				m_preset1->SetSelect(false);
				m_preset2->SetSelect(false);
				m_preset3->SetSelect(false);

				m_preset2->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset3)
			{
				SavePreset(2);


				m_preset1->SetSelect(false);
				m_preset2->SetSelect(false);
				m_preset3->SetSelect(false);

				m_preset3->SetSelect(true);
				return TRUE;
			}
		}
		else if (MES_LBUTTONDOWN == lParam)
		{
			if ((GxxAniLable *)wParam == m_frontL_left || (GxxAniLable *)wParam == m_frontL_right)
			{
				BtnDownSet(Front_L);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_frontR_left || (GxxAniLable *)wParam == m_frontR_right)
			{
				BtnDownSet(Front_R);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_rearL_left || (GxxAniLable *)wParam == m_rearL_right)
			{
				BtnDownSet(Rear_L);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_rearR_left || (GxxAniLable *)wParam == m_rearR_right)
			{
				BtnDownSet(Rear_R);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_subwL_left || (GxxAniLable *)wParam == m_subwL_right)
			{
				BtnDownSet(SubW_L);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_subwR_left || (GxxAniLable *)wParam == m_subwR_right)
			{
				BtnDownSet(SubW_R);
				return TRUE;
			}
		}
		else if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				RetToFucActivity();
				return TRUE;
			}
			if ((GxxView *)wParam == m_btnBack)
			{
				finish();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_frontL_left)
			{
				sysConfig.sysParam.curTimeFrontL -= 1;
				SetTimeVal(AVSET::AUDIOCH_FL);
				SetMidText(AVSET::AUDIOCH_FL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_frontL_right)
			{
				sysConfig.sysParam.curTimeFrontL += 1;
				SetTimeVal(AVSET::AUDIOCH_FL);
				SetMidText(AVSET::AUDIOCH_FL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_frontR_left)
			{
				sysConfig.sysParam.curTimeFrontR -= 1;
				SetTimeVal(AVSET::AUDIOCH_FR);
				SetMidText(AVSET::AUDIOCH_FR);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_frontR_right)
			{
				sysConfig.sysParam.curTimeFrontR += 1;
				SetTimeVal(AVSET::AUDIOCH_FR);
				SetMidText(AVSET::AUDIOCH_FR);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_rearL_left)
			{
				sysConfig.sysParam.curTimeRearL -= 1;
				SetTimeVal(AVSET::AUDIOCH_RL);
				SetMidText(AVSET::AUDIOCH_RL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_rearL_right)
			{
				sysConfig.sysParam.curTimeRearL += 1;
				SetTimeVal(AVSET::AUDIOCH_RL);
				SetMidText(AVSET::AUDIOCH_RL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_rearR_left)
			{
				sysConfig.sysParam.curTimeRearR -= 1;
				SetTimeVal(AVSET::AUDIOCH_RR);
				SetMidText(AVSET::AUDIOCH_RR);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_rearR_right)
			{
				sysConfig.sysParam.curTimeRearR += 1;
				SetTimeVal(AVSET::AUDIOCH_RR);
				SetMidText(AVSET::AUDIOCH_RR);
				return TRUE;
			}

			if ((GxxAniLable *)wParam == m_subwL_left)
			{
				sysConfig.sysParam.curSubwL -= 1;
				SetTimeVal(AVSET::AUDIOCH_SubWL);
				SetMidText(AVSET::AUDIOCH_SubWL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_subwL_right)
			{
				sysConfig.sysParam.curSubwL += 1;
				SetTimeVal(AVSET::AUDIOCH_SubWL);
				SetMidText(AVSET::AUDIOCH_SubWL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_subwR_left)
			{
				sysConfig.sysParam.curSubwR -= 1;
				SetTimeVal(AVSET::AUDIOCH_SubWR);
				SetMidText(AVSET::AUDIOCH_SubWR);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_subwR_right)
			{
				sysConfig.sysParam.curSubwR += 1;
				SetTimeVal(AVSET::AUDIOCH_SubWR);
				SetMidText(AVSET::AUDIOCH_SubWR);
				return TRUE;
			}


			if ((GxxAniLable *)wParam == m_flat)
			{
				SetFlat();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_cm_msec)
			{
				m_isMsec = !m_isMsec;
				m_txtMsec->setDraw(!m_isMsec);
				m_txtCm->setDraw(m_isMsec);
				m_s_txtCm->setDraw(!m_isMsec);
				m_s_txtMsec->setDraw(m_isMsec);
				
				SetMidText(AVSET::AUDIOCH_FL);
				SetMidText(AVSET::AUDIOCH_FR);
				SetMidText(AVSET::AUDIOCH_RL);
				SetMidText(AVSET::AUDIOCH_RR);
				SetMidText(AVSET::AUDIOCH_SubWL);
				SetMidText(AVSET::AUDIOCH_SubWR);
				AfxInvalidateRect(NULL);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset1)
			{
				
				SetPreset(0);
				m_preset1->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset2)
			{
				
				SetPreset(1);
				m_preset2->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset3)
			{
				
				SetPreset(2);
				m_preset3->SetSelect(true);
				return TRUE;
			}

		return FALSE;
		}
	default:
		return FALSE;
	}
	return FALSE;
}


void TimeCorrectPad::BtnDownSet( BTN_TYPE type )
{
	switch(type)
	{
	case Front_L:
		m_frontL_pic->setDraw(true);
		m_frontL_pic->invalidateRect();
		m_set_pic = m_frontL_pic;
		break;
	case Front_R:
		m_frontR_pic->setDraw(true);
		m_frontR_pic->invalidateRect();
		m_set_pic = m_frontR_pic;
		break;
	case Rear_L:
		m_rearL_pic->setDraw(true);
		m_rearL_pic->invalidateRect();
		m_set_pic = m_rearL_pic;
		break;
	case Rear_R:
		m_rearR_pic->setDraw(true);
		m_rearR_pic->invalidateRect();
		m_set_pic = m_rearR_pic;
		break;
	case SubW_L:
		m_subwL_pic->setDraw(true);
		m_subwL_pic->invalidateRect();
		m_set_pic = m_subwL_pic;
		break;
	case SubW_R:
		m_subwR_pic->setDraw(true);
		m_subwR_pic->invalidateRect();
		m_set_pic = m_subwR_pic;
		break;
	default:
		break;
	}
}



//void TimeCorrectPad::SetInZone( BYTE &bt )
//{
//	if (bt >MAX_VALUE)
//	{
//		bt = 0; 
//	}
//	sysConfig.WriteConfig(&bt);
//}

void TimeCorrectPad::SetMidText( int type )
{
	switch(type)
	{
	case AVSET::AUDIOCH_FL:
		DoSetMidText(m_frontL_left,m_frontL_right,m_frontL_mid,sysConfig.sysParam.curTimeFrontL);
		break;
	case AVSET::AUDIOCH_FR:
		DoSetMidText(m_frontR_left,m_frontR_right,m_frontR_mid,sysConfig.sysParam.curTimeFrontR);
		break;
	case AVSET::AUDIOCH_RL:
		DoSetMidText(m_rearL_left,m_rearL_right,m_rearL_mid,sysConfig.sysParam.curTimeRearL);
		break;
	case AVSET::AUDIOCH_RR:
		DoSetMidText(m_rearR_left,m_rearR_right,m_rearR_mid,sysConfig.sysParam.curTimeRearR);
		break;

	case AVSET::AUDIOCH_SubWL:
		DoSetMidText(m_subwL_left,m_subwL_right,m_subwL_mid,sysConfig.sysParam.curSubwL);
		break;
	case AVSET::AUDIOCH_SubWR:
		DoSetMidText(m_subwR_left,m_subwR_right,m_subwR_mid,sysConfig.sysParam.curSubwR);
		break;
	default:
		ASSERT(0);
		break;
	}
}

void TimeCorrectPad::DoSetMidText( GxxAniLable * left, GxxAniLable * right, GxxAniLable * mid, BYTE &bt )
{

	left->setEnable( !(bt==0));
	//right->setEnable( !(bt == MAX_VALUE) );

	float fval =  bt/10.0;
	if (!m_isMsec)
	{
		fval = 34*fval;
	}
	char text_v[16];
	sprintf(text_v,"%2.1f",fval);
	mid->SetText(text_v);

	static int s_Sum = -1;
	static int b_Msec = -2; 
	int sum = sysConfig.sysParam.curTimeFrontL + sysConfig.sysParam.curTimeFrontR + sysConfig.sysParam.curTimeRearL
		+ sysConfig.sysParam.curTimeRearR +sysConfig.sysParam.curSubwL +sysConfig.sysParam.curSubwR;


	if ((bool)b_Msec != m_isMsec ||  s_Sum != sum)
	{
		b_Msec = m_isMsec;
		float fRemain = SUM_VALUE -sum;
		fRemain = fRemain/10.0;
		if (!m_isMsec)
		{
			fRemain = 34*fRemain;
		}
		string str = StrHelp::FormatToString("%2.1f",fRemain);
		m_txtRemainVal->setText(str.c_str());
		m_txtRemainVal->invalidateRect();
	}


	if (s_Sum == sum)
	{
		return;
	}


	s_Sum = sum;
	if (SUM_VALUE == s_Sum)
	{
		m_frontL_right->setEnable(false);
		m_frontR_right->setEnable(false);
		m_rearL_right->setEnable(false);
		m_rearR_right->setEnable(false);
		m_subwL_right->setEnable(false);
		m_subwR_right->setEnable(false);
	}
	else
	{
		ASSERT(s_Sum<SUM_VALUE);
		m_frontL_right->setEnable(true);
		m_frontR_right->setEnable(true);
		m_rearL_right->setEnable(true);
		m_rearR_right->setEnable(true);
		m_subwL_right->setEnable(true);
		m_subwR_right->setEnable(true);
	}
}

void TimeCorrectPad::SetTimeVal( int type )
{
	switch(type)
	{
	case AVSET::AUDIOCH_FL:
		sysConfig.WriteConfig(&sysConfig.sysParam.curTimeFrontL);
		AVSET::SoundDelay(AVSET::AUDIOCH_FL,sysConfig.sysParam.curTimeFrontL/10.0);
		break;
	case AVSET::AUDIOCH_FR:
		sysConfig.WriteConfig(&sysConfig.sysParam.curTimeFrontR);
		AVSET::SoundDelay(AVSET::AUDIOCH_FR,sysConfig.sysParam.curTimeFrontR/10.0);
		break;
	case AVSET::AUDIOCH_RL:
		sysConfig.WriteConfig(&sysConfig.sysParam.curTimeRearL);
		AVSET::SoundDelay(AVSET::AUDIOCH_RL,sysConfig.sysParam.curTimeRearL/10.0);
		break;
	case AVSET::AUDIOCH_RR:
		sysConfig.WriteConfig(&sysConfig.sysParam.curTimeRearR);
		AVSET::SoundDelay(AVSET::AUDIOCH_RR,sysConfig.sysParam.curTimeRearR/10.0);
		break;
	case AVSET::AUDIOCH_SubWL:
		sysConfig.WriteConfig(&sysConfig.sysParam.curSubwL);
		AVSET::SoundDelay(AVSET::AUDIOCH_SubWL,sysConfig.sysParam.curSubwL/10.0);
		break;
	case AVSET::AUDIOCH_SubWR:
		sysConfig.WriteConfig(&sysConfig.sysParam.curSubwR);
		AVSET::SoundDelay(AVSET::AUDIOCH_SubWR,sysConfig.sysParam.curSubwR/10.0);
		break;
	default:
		ASSERT(0);
		break;
	}

	m_preset1->SetSelect(false);
	m_preset2->SetSelect(false);
	m_preset3->SetSelect(false);
}

void TimeCorrectPad::SetFlat()
{
	sysConfig.sysParam.curTimeFrontL = 0;//cyz
	sysConfig.sysParam.curTimeFrontR = 0;//cyz
	sysConfig.sysParam.curTimeRearL = 0;//cyz
	sysConfig.sysParam.curTimeRearR = 0;//cyz
	sysConfig.sysParam.curSubwL = 0;//cyz
	sysConfig.sysParam.curSubwR = 0;//cyz


	SetTimeVal(AVSET::AUDIOCH_FL);
	SetTimeVal(AVSET::AUDIOCH_FR);
	SetTimeVal(AVSET::AUDIOCH_RL);
	SetTimeVal(AVSET::AUDIOCH_RR);
	SetTimeVal(AVSET::AUDIOCH_SubWL);
	SetTimeVal(AVSET::AUDIOCH_SubWR);


	SetMidText(AVSET::AUDIOCH_FL);
	SetMidText(AVSET::AUDIOCH_FR);
	SetMidText(AVSET::AUDIOCH_RL);
	SetMidText(AVSET::AUDIOCH_RR);
	SetMidText(AVSET::AUDIOCH_SubWL);
	SetMidText(AVSET::AUDIOCH_SubWR);
}

void TimeCorrectPad::SetPreset(int i)
{
	ASSERT(i>=0&&i<3);
	sysConfig.sysParam.curTimeFrontL = m_presetTimeFrontL[i];//cyz
	sysConfig.sysParam.curTimeFrontR = m_presetTimeFrontR[i];//cyz
	sysConfig.sysParam.curTimeRearL = m_presetTimeRearL[i];//cyz
	sysConfig.sysParam.curTimeRearR = m_presetTimeRearR[i];//cyz
	sysConfig.sysParam.curSubwL = m_presetSubwL[i];//cyz
	sysConfig.sysParam.curSubwR = m_presetSubwR[i];//cyz

	SetTimeVal(AVSET::AUDIOCH_FL);
	SetTimeVal(AVSET::AUDIOCH_FR);
	SetTimeVal(AVSET::AUDIOCH_RL);
	SetTimeVal(AVSET::AUDIOCH_RR);
	SetTimeVal(AVSET::AUDIOCH_SubWL);
	SetTimeVal(AVSET::AUDIOCH_SubWR);


	SetMidText(AVSET::AUDIOCH_FL);
	SetMidText(AVSET::AUDIOCH_FR);
	SetMidText(AVSET::AUDIOCH_RL);
	SetMidText(AVSET::AUDIOCH_RR);
	SetMidText(AVSET::AUDIOCH_SubWL);
	SetMidText(AVSET::AUDIOCH_SubWR);
}

void TimeCorrectPad::Draw()
{
	Activity::Draw();
	SkiaBitmapManager::GetInstance()->DrawLine(737,90,777,90,0xffffffff,2);

}

void TimeCorrectPad::SavePreset( int nth  )
{
	ASSERT(nth>=0 && nth <3);
	m_presetTimeFrontL[nth] = sysConfig.sysParam.curTimeFrontL;//cyz
	m_presetTimeFrontR[nth] = sysConfig.sysParam.curTimeFrontR;//cyz
	m_presetTimeRearL[nth] = sysConfig.sysParam.curTimeRearL;//cyz
	m_presetTimeRearR[nth] = sysConfig.sysParam.curTimeRearR;//cyz
	m_presetSubwL[nth] = sysConfig.sysParam.curSubwL;//cyz
	m_presetSubwR[nth] = sysConfig.sysParam.curSubwR;//cyz

	sysConfig.WriteConfig(&m_presetTimeFrontL[nth]);
	sysConfig.WriteConfig(&m_presetTimeFrontR[nth]);
	sysConfig.WriteConfig(&m_presetTimeRearL[nth]);
	sysConfig.WriteConfig(&m_presetTimeRearR[nth]);
	sysConfig.WriteConfig(&m_presetSubwL[nth]);
	sysConfig.WriteConfig(&m_presetSubwR[nth]);
}

void TimeCorrectPad::CheckSumValue()
{
	throw std::exception("The method or operation is not implemented.");
}
