#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "ParametricEqPad.h"
#include "ControlHelp.h"
#include "GxxSetupListGroup.h"
#include "GxxFileListGroup.h"
#include "GxxAniLable.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "GxxSwText.h"
#include "AVSet.h"
#include "GxxParamPad.h"

static RegisterHelp help("ParametricEqPad", ParametricEqPad::CreateControl);
Activity* ParametricEqPad::CreateControl()
{
	return new ParametricEqPad;
}

ParametricEqPad::ParametricEqPad()
{

}


ParametricEqPad::~ParametricEqPad()
{

}
void ParametricEqPad::onCreate()
{
	Activity::onCreate();
	setContentView("layout\\ParametricEqPad.xml");
	setBackColor(0xffff0000);
	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);
	m_btnBack = findViewByName("back_btn");
	ASSERT(m_btnBack!=NULL);

	m_level_up = (GxxAniLable *)safeFindViewByName("level_up");
	m_level_text = (GxxAniLable *)safeFindViewByName("level_text");
	m_level_down = (GxxAniLable *)safeFindViewByName("level_down");

	m_freq_left = (GxxAniLable *)safeFindViewByName("Freq_left");
	m_freq_text = (GxxAniLable *)safeFindViewByName("Freq_mid");
	m_freq_right = (GxxAniLable *)safeFindViewByName("Freq_right");

	m_qvalue_left = (GxxAniLable *)safeFindViewByName("Adjust_left");
	m_qvalue_text = (GxxAniLable *)safeFindViewByName("Adjust_mid");
	m_qvalue_right = (GxxAniLable *)safeFindViewByName("Adjust_right");


	m_flat = (GxxAniLable *)safeFindViewByName("flat_btn");
	m_band = (GxxAniLable *)safeFindViewByName("band_btn");
	m_preset1 = (GxxAniLable *)safeFindViewByName("preset1_btn");
	m_preset2 = (GxxAniLable *)safeFindViewByName("preset2_btn");
	m_preset3 = (GxxAniLable *)safeFindViewByName("preset3_btn");

	m_text_khz = (GxxSwText*)safeFindViewByName("Freq_mid_khz");


	m_paramPad = (GxxParamPad *)safeFindViewByName("gxx_param_pad");

	RenewPadBtn();

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);
}


//恢复出厂设置
LRESULT ParametricEqPad::RestoreDefault(DWORD param1, DWORD param2)
{
	m_paramPad->SetFlat(true);
	m_paramPad->SavePre(1);
	m_paramPad->SavePre(2);
	m_paramPad->SavePre(3);
	ResetSelect();
	RenewPadBtn();
	return 0;
}

void ParametricEqPad::onResume()
{

}



BOOL ParametricEqPad::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case	CTR_BTN_MATCH_BACK://方控
		finish();
		return TRUE;
	case MES_INVALIDATE:
		RenewPadBtn();
		return TRUE;
	case CTR_MESSAGE:
		if (MES_LBUTTONLONG == lParam)
		{
			if ((GxxAniLable *)wParam == m_preset1)
			{
				m_paramPad->SavePre(1);
				ResetSelect();
				m_preset1->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset2)
			{
				m_paramPad->SavePre(2);
				ResetSelect();
				m_preset2->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset3)
			{
				m_paramPad->SavePre(3);
				ResetSelect();
				m_preset3->SetSelect(true);
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
			if ((GxxAniLable *)wParam == m_flat)
			{
				m_paramPad->SetFlat(true);
				ResetSelect();
				RenewPadBtn();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_band)
			{
				m_paramPad->NextBand();
				RenewPadBtn();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset1)
			{
				m_paramPad->SetPre(1);
				ResetSelect();
				m_preset1->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset2)
			{
				m_paramPad->SetPre(2);
				ResetSelect();
				m_preset2->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_preset3)
			{
				m_paramPad->SetPre(3);
				ResetSelect();
				m_preset3->SetSelect(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_level_up)
			{
				int n = m_paramPad->MoveLevel(1);
				m_level_text->SetText(  StrHelp::FormatToString("%d",n));
				if (n == BAND_COUNT)
				{
					m_level_up->setEnable(false);
				}
				m_level_down->setEnable(true);
				ResetSelect();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_level_down)
			{
				int n =  m_paramPad->MoveLevel(-1);
				m_level_text->SetText( StrHelp::FormatToString("%d",n) );
				if (n == -BAND_COUNT)
				{
					m_level_down->setEnable(false);
				}
				m_level_up->setEnable(true);
				ResetSelect();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_qvalue_left)
			{
				int n =m_paramPad->MoveQValue(-1);
				m_qvalue_text->SetText(StrHelp::FormatToString("%d",n) );
				if (n == MIN_Q)
				{
					m_qvalue_left->setEnable(false);
				}
				m_qvalue_right->setEnable(true);
				ResetSelect();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_qvalue_right)
			{
				int n =m_paramPad->MoveQValue(1);
				m_qvalue_text->SetText(StrHelp::FormatToString("%d",n) );
				if (n == MAX_Q)
				{
					m_qvalue_right->setEnable(false);
				}
				m_qvalue_left->setEnable(true);
				ResetSelect();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_freq_left)
			{
				bool bmax,bmin;
				float ffreq   =m_paramPad->MoveFreq(-1,bmax,bmin);
				SetFreq(ffreq);
				m_freq_left->setEnable(!bmin);
				m_freq_right->setEnable(!bmax);
				ResetSelect();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == m_freq_right)
			{
				bool bmax,bmin;
				float ffreq = m_paramPad->MoveFreq(1,bmax,bmin);
				SetFreq(ffreq);
				m_freq_left->setEnable(!bmin);
				m_freq_right->setEnable(!bmax);
				ResetSelect();
				return TRUE;
			}
		}
		return FALSE;

	default:
		return FALSE;
	}
	return FALSE;
}

void ParametricEqPad::RenewPadBtn()
{
	int nlevel = m_paramPad->GetLevel();
	char text_v[16]; 
	sprintf(text_v,"%d",nlevel);
	m_level_text->SetText(text_v);
	m_level_up->setEnable(nlevel != BAND_COUNT);
	m_level_down->setEnable(nlevel != -BAND_COUNT);

	bool bmax,bmin;
	float ffreq = m_paramPad->GetFreq(bmax,bmin);
	SetFreq(ffreq);

	m_freq_left->setEnable(!bmin);
	m_freq_right->setEnable(!bmax);

	int nqvalue = m_paramPad->GetQValue();
	sprintf(text_v,"%d",nqvalue);
	m_qvalue_text->SetText(text_v);
	m_qvalue_left->setEnable(nqvalue != MIN_Q);
	m_qvalue_right->setEnable(nqvalue != MAX_Q);


}

void ParametricEqPad::SetFreq( float ffreq )
{
	char text_v[16]; 
	if (ffreq>=1000)
	{
		ffreq = ffreq/1000;
		if (ffreq>=10)
		{
			sprintf(text_v,"%2.0f",ffreq);
			m_text_khz->setText("KHz");
		}
		else
		{
			sprintf(text_v,"%1.1f",ffreq);
			m_text_khz->setText("KHz");
		}
		
	}
	else
	{
		sprintf(text_v,"%d",(int)ffreq);
		m_text_khz->setText("Hz");
	}

	m_freq_text->SetText(text_v);
}

void ParametricEqPad::ResetSelect()
{
	m_preset1->SetSelect(false);
	m_preset2->SetSelect(false);
	m_preset3->SetSelect(false);
}


