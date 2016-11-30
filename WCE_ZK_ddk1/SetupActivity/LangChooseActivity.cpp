#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "LangChooseActivity.h"
#include "ControlHelp.h"
#include "GxxLangListGroup.h"
#include "GxxAniLable.h"
#include "LangStringManager.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "Audio/Audio.h"
#include "VersionXml.h"
#include "GxxLBList.h"




Activity* LangChooseActivity::CreateControl()
{
	return new LangChooseActivity;
}

void LangChooseActivity::onCreate()
{
	Activity::onCreate();
	setContentView("layout\\LangChoosePad.xml");

	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);

	m_back = findViewByName("back_btn");
	ASSERT(m_back!=NULL);

	m_lanGroup = (GxxLangListGroup *)findViewByName("lang_group");

	GxxLBList *list = (GxxLBList *)m_lanGroup->safeFindViewByName("lan_set");

	if ( VersionXml::GetInstance()->GetLanguage() == VersionXml::LAN_ALL)
	{
		//n_cursor = 0;
		//sline_data = "All";
	}
	else if (VersionXml::GetInstance()->GetLanguage() == VersionXml::LAN_Traditional)
	{
		GxxView * simChinese = list->safeFindViewByName("chinese");
		list->removeCtrl(simChinese);
		list->CaculateRation(false);
		//n_cursor = 1;
		//sline_data = "Simplified";
	}
	else if (VersionXml::GetInstance()->GetLanguage() == VersionXml::LAN_Simplified)
	{
		GxxView * traChinese = list->safeFindViewByName("fan_chinese");
		list->removeCtrl(traChinese);
		list->CaculateRation(false);
		//n_cursor = 2;
		//sline_data = "Traditional";
	}
	else
	{
		ASSERT(0);
	}

	ASSERT(m_lanGroup!=NULL);
	

	m_okLable = (GxxAniLable *)findViewByName("set_ok");
	ASSERT(m_okLable!=NULL);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

}
//恢复出厂设置
LRESULT LangChooseActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	LangStringManager::GetInstance()->SetLangID(1);
	sysConfig.sysParam.curLang = 1;
	sysConfig.WriteConfig(&sysConfig.sysParam.curLang);
	return 0;
}

void LangChooseActivity::onResume()
{
	int id = LangStringManager::GetInstance()->GetLangID();
	bool b=m_lanGroup->SetSelLine(id);
	m_is_init_sound = false;
	if (m_param == "power_on")
	{
		m_lanGroup->SetSelLine(0);//B+ 断电选中第0项
		m_is_init_sound = true;
		m_btx->setDraw(false);
		m_back->setDraw(false);//开机的时候不显示 后退和X 按键
		SetPermitStart(false);

	}
	else
	{
		m_btx->setDraw(true);
		m_back->setDraw(true);

	}
	ASSERT(b);
}

void LangChooseActivity::onPause()
{
	m_btx->setDraw(true);
	m_back->setDraw(true);
}

BOOL LangChooseActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case	CTR_LIST_BACK_ACTIVITY://back_btn
	case	CTR_BTN_MATCH_BACK:
		ExitLangActivity();

		return TRUE;
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				RetToFucActivity();
				return TRUE;
			}
			else if ((GxxView *)wParam == m_okLable)
			{
				SetPermitStart(true);
				SetLang();
				ExitLangActivity();
				return TRUE;
			}
		}
		return FALSE;

	default:
		return FALSE;
	}
	return FALSE;
}



void LangChooseActivity::SetLang()
{
	int id  = 0;
	bool b= m_lanGroup->GetSelLine(id);
	ASSERT(b);
	LangStringManager::GetInstance()->SetLangID(id);
	sysConfig.sysParam.curLang = id;
	sysConfig.WriteConfig(&sysConfig.sysParam.curLang);

}

void LangChooseActivity::ExitLangActivity()
{
	if (m_is_init_sound)
	{
		Activity::s_is_init_sound = true;
		AfxPostMessage(CTR_INIT_MUTE,0,0);//发消息通知设置声音
	}
	if (!finish())
	{
		Activity::startActivity(NULL,"RadioActivity");
	}
	Activity::S_isPowerInLanguage = false;
}


static RegisterHelp help("LangChooseActivity", LangChooseActivity::CreateControl);