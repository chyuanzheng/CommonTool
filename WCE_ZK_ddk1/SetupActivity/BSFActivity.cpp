#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "BSFActivity.h"
#include "ControlHelp.h"
#include "GxxSetupListGroup.h"
#include "GxxFileListGroup.h"
#include "GxxAniLable.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "GxxPicLine.h"
#include "GxxSwText.h"
#include "AVSet.h"
#include "VersionXml.h"
#include "StrHelp.h"
#include "StrDef.h"

#define  MAX_EQ_VALUE    12

#define  MAX_SubW_Set    4
Activity* BSFActivity::CreateControl()
{
	return new BSFActivity;
}

void BSFActivity::onCreate()
{
	Activity::onCreate();
	if ( VersionXml::GetInstance()->GetBSFModule() == VersionXml::Navi_BSF_Removed)//BSFActivity.xml
	{
		setContentView("layout\\BSFActivity.xml");
	}
	else if ( VersionXml::GetInstance()->GetBSFModule() == VersionXml::Navi_BSF_Added)
	{
		setContentView("layout\\BSFActivity_All_Set.xml");
	}
	
	setBackColor(0xffff0000);
	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);
	m_btnBack = findViewByName("back_btn");
	ASSERT(m_btnBack!=NULL);


	m_front = (GxxAniLable *)safeFindViewByName("bsf_front");
	m_left = (GxxAniLable *)safeFindViewByName("bsf_left");
	m_right = (GxxAniLable *)safeFindViewByName("bsf_right");
	m_center= (GxxAniLable *)safeFindViewByName("bsf_center");
	m_rear = (GxxAniLable *)safeFindViewByName("bsf_rear");


	m_subw_left= (GxxAniLable *)safeFindViewByName("subw_left");
	m_subw_text= (GxxAniLable *)safeFindViewByName("subw_mid");
	m_subw_right= (GxxAniLable *)safeFindViewByName("subw_right");

	

	m_subw_level_left= (GxxAniLable *)safeFindViewByName("subwlevel_left");
	m_subw_level_text= (GxxAniLable *)safeFindViewByName("subwlevel_mid");
	m_subw_level_right= (GxxAniLable *)safeFindViewByName("subwlevel_right");



	m_subw_phase_left= (GxxAniLable *)safeFindViewByName("subphase_left");
	m_subw_phase_text= (GxxAniLable *)safeFindViewByName("subphase_mid");
	m_subw_phase_right= (GxxAniLable *)safeFindViewByName("subphase_right");


	//重低音相位硬件暂不支持。设为false；

	if( VersionXml::GetInstance()->GetBSFModule() == VersionXml::Navi_BSF_Removed )
	{
		m_subw_left->setDraw(false);
		m_subw_text->setDraw(false);
		m_subw_right->setDraw(false);

		m_subw_level_left->setDraw(false);
		m_subw_level_text->setDraw(false);
		m_subw_level_right->setDraw(false);

		m_subw_phase_left->setDraw(false);
		m_subw_phase_text->setDraw(false);
		m_subw_phase_right->setDraw(false);
	}
	else
	{
		m_subw_phase_left->setDraw(false);
		m_subw_phase_text->setDraw(false);
		m_subw_phase_right->setDraw(false);
	}
	m_showPicLine = (GxxPicLine *)safeFindViewByName("show_sub_line");


	m_textFade =  (GxxSwText *)safeFindViewByName("fade"); 
	m_textBalance =  (GxxSwText *)safeFindViewByName("balance"); 

	////x,y 从内存读出；
	

	SetInZone(sysConfig.sysParam.curSoundFieldX);
	SetInZone(sysConfig.sysParam.curSoundFieldY);
	

	if (sysConfig.sysParam.curBsfPhase>1)
	{
		sysConfig.sysParam.curBsfPhase = 0;
	}



	if (sysConfig.sysParam.curEqBSFValue>MAX_EQ_VALUE || sysConfig.sysParam.curEqBSFValue<0)
	{
		sysConfig.sysParam.curEqBSFValue = 0;
	}
	
	AVSET::SetSubw(sysConfig.sysParam.curEqBSFValue);//设置超低音音量

	BSF_SetPhaseOn(sysConfig.sysParam.curBsfPhase);
	BSF_SetSubwOn(sysConfig.sysParam.curBsfSet);
	setSubwText();
	m_showPicLine->SetPoint(sysConfig.sysParam.curSoundFieldX,sysConfig.sysParam.curSoundFieldY);


	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

}


//恢复出厂设置
LRESULT BSFActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	m_showPicLine->SetPoint(0,0);

	sysConfig.sysParam.curEqBSFValue = MAX_EQ_VALUE/2;
	AVSET::SetSubw(sysConfig.sysParam.curEqBSFValue);
	m_subw_level_left->setEnable(true);
	m_subw_level_right->setEnable(true);
	setSubwText();

	
	BSF_SetPhaseOn(false);
	BSF_SetSubwOn(0);

	return 0;
}


void BSFActivity::onResume()
{

	
}

void BSFActivity::SetInZone( char &bt )
{
	int nmaxline = m_showPicLine->getMaxLine();
	if (bt<-nmaxline || bt >nmaxline)
	{
		bt = 0; 
	}
}

void BSFActivity::BSF_SetPhaseOn( bool b )
{
	m_subw_phase_left->setEnable(b);
	m_subw_phase_right->setEnable(!b);
	sysConfig.sysParam.curBsfPhase = (BYTE)b;
	AVSET::SoundPhase(4,b);
	AVSET::SoundPhase(5,b);
	sysConfig.WriteConfig(&sysConfig.sysParam.curBsfPhase);
	if (b)
	{
		m_subw_phase_text->SetText(L"180°");
	}
	else
	{
		m_subw_phase_text->SetText(L"0°");
	}
}

void BSFActivity::BSF_SetSubwOn( UINT data )
{
	if (data>MAX_SubW_Set)
	{
		sysConfig.sysParam.curBsfSet = 0;
	}
	else
	{
		sysConfig.sysParam.curBsfSet = data;
	}

	


	m_subw_right->setEnable(MAX_SubW_Set>sysConfig.sysParam.curBsfSet);
	m_subw_left->setEnable(0<sysConfig.sysParam.curBsfSet);


	bool b = (0!=data); 
	m_subw_level_left->setEnable(b);
	m_subw_level_right->setEnable(b);
	m_subw_phase_left->setEnable(b);
	m_subw_phase_right->setEnable(b);

	if (b)//On
	{
		m_subw_text->SetText(StrHelp::FormatToString("%d",sysConfig.sysParam.curBsfSet*50));

		bool btemp = (bool)sysConfig.sysParam.curBsfPhase;
		m_subw_phase_left->setEnable(btemp);
		m_subw_phase_right->setEnable(!btemp);

		if (sysConfig.sysParam.curEqBSFValue==0)
		{
			m_subw_level_left->setEnable(false);
		}
		if (sysConfig.sysParam.curEqBSFValue==MAX_EQ_VALUE)
		{
			m_subw_level_right->setEnable(false);
		}


	}
	else
	{
		m_subw_text->SetText(CHDLL_STR::C_OFF);
		
	}
	
	AVSET::SubwOn(b);//这里设定超低音
	//sysConfig.sysParam.curBsfSet = (BYTE)b;
	sysConfig.WriteConfig(&sysConfig.sysParam.curBsfSet);
}





BOOL BSFActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case	CTR_BTN_MATCH_BACK:
		finish();
		return TRUE;
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
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
			if ((GxxView *)wParam == m_subw_level_left)
			{
				if (sysConfig.sysParam.curEqBSFValue>0)
				{
					sysConfig.sysParam.curEqBSFValue--;
				}
				AVSET::SetSubw(sysConfig.sysParam.curEqBSFValue);
				if (sysConfig.sysParam.curEqBSFValue==0)
				{
					m_subw_level_left->setEnable(false);
				}
				m_subw_level_right->setEnable(true);
				setSubwText();
				return TRUE;
			}
			if ((GxxView *)wParam == m_subw_level_right)
			{
				if (sysConfig.sysParam.curEqBSFValue<MAX_EQ_VALUE)
				{
					sysConfig.sysParam.curEqBSFValue++;
				}
				AVSET::SetSubw(sysConfig.sysParam.curEqBSFValue);
				if (sysConfig.sysParam.curEqBSFValue==MAX_EQ_VALUE)
				{
					m_subw_level_right->setEnable(false);
				}
				m_subw_level_left->setEnable(true);
				setSubwText();
				return TRUE;
			}
			if ((GxxView *)wParam == m_subw_right)
			{
				sysConfig.sysParam.curBsfSet++;
				BSF_SetSubwOn(sysConfig.sysParam.curBsfSet);
				return TRUE;
			}
			if ((GxxView *)wParam == m_subw_left)
			{
				sysConfig.sysParam.curBsfSet--;
				BSF_SetSubwOn(sysConfig.sysParam.curBsfSet);
				return TRUE;
			}
			if ((GxxView *)wParam == m_subw_phase_right)
			{
				BSF_SetPhaseOn(true);
				return TRUE;
			}
			if ((GxxView *)wParam == m_subw_phase_left)
			{
				BSF_SetPhaseOn(false);
				return TRUE;
			}

			//以下是 x，y的按键 
			if ((GxxView *)wParam == m_front)
			{
				m_showPicLine->SetFront();
				return TRUE;
			}
			if ((GxxView *)wParam == m_rear)
			{
				m_showPicLine->SetRear();
				return TRUE;
			}
			if ((GxxView *)wParam == m_left)
			{
				m_showPicLine->SetLeft();
				return TRUE;
			}
			if ((GxxView *)wParam == m_right)
			{
				m_showPicLine->SetRight();
				return TRUE;
			}
			if ((GxxView *)wParam == m_center)
			{
				m_showPicLine->SetPoint(0,0);
				return TRUE;
			}
		}
		return FALSE;
	case CTR_SET_BSF_LINE:
		SetPosition();
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}

void BSFActivity::setSubwText()
{

	ASSERT(sysConfig.sysParam.curEqBSFValue>=0 && sysConfig.sysParam.curEqBSFValue<=MAX_EQ_VALUE);

	m_subw_level_text->SetText( StrHelp::FormatToString("%d",sysConfig.sysParam.curEqBSFValue) );

	sysConfig.WriteConfig(&sysConfig.sysParam.curEqBSFValue);

}


void BSFActivity::SetPosition()
{
	int x,y;
	m_showPicLine->GetPoint(x,y);

	//x,y 写入内存；
	sysConfig.sysParam.curSoundFieldX = (char)x;
	sysConfig.sysParam.curSoundFieldY = (char)y;
	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curSoundFieldX);
	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curSoundFieldY);
	AVSET::SetSoundField(sysConfig.sysParam.curSoundFieldX,sysConfig.sysParam.curSoundFieldY);


	int nmaxline = m_showPicLine->getMaxLine();

	if (x==-nmaxline){
		m_left->setEnable(false);
	}else{
		m_left->setEnable(true);
	}

	if (x==nmaxline){
		m_right->setEnable(false);
	}else{
		m_right->setEnable(true);
	}

	if (y==-nmaxline){
		m_rear->setEnable(false);
	}else{
		m_rear->setEnable(true);
	}

	if (y==nmaxline){
		m_front->setEnable(false);
	}else{
		m_front->setEnable(true);
	}

	string strline = "";
	if (x>0)
	{
		strline = "R";
	}
	else if (x<0)
	{
		x = -x;
		strline = "L";
	}
	char text_v[16];
	sprintf(text_v,"%d",x);
	strline += text_v;



	m_textBalance->setText(strline.c_str());
	m_textBalance->invalidateRect();



	strline = "";
	if (y>0)
	{
		strline = "F";
	}
	else if (y<0)
	{
		y=-y;
		strline = "R";
	}
	sprintf(text_v,"%d",y);
	strline += text_v;

	m_textFade->setText(strline.c_str());
	m_textFade->invalidateRect();

}






static RegisterHelp help("BSFActivity", BSFActivity::CreateControl);