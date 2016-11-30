#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "BassActivity.h"
#include "ControlHelp.h"
#include "GxxBassListGroup.h"
#include "GxxAniLable.h"
#include "LangStringManager.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "Audio/Audio.h"
#include "AVSet.h"


Activity* BassActivity::CreateControl()
{
	return new BassActivity;
}

void BassActivity::onCreate()
{
	Activity::onCreate();
	setContentView("layout\\BassPad.xml");

	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);

	m_lanGroup = (GxxBassListGroup *)findViewByName("bass_group");
	ASSERT(m_lanGroup!=NULL);

	BYTE  &eq = sysConfig.sysParam.curEqLineValue;
	if (eq<0||eq>9)
	{
		eq =0;
	}
	SetDefault(sysConfig.sysParam.curDefeat,0);
	//AVSET::SetEQ(eq);
	m_lanGroup->SetSelLine(eq);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);


	notify.funNotify = SetDefault;
	GXNotify::RegisterNotifyHandler("eq_default_set", notify);

}

//恢复出厂设置
LRESULT BassActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	AVSET::SetEQ(0);
	sysConfig.sysParam.curEqLineValue = 0;
	m_lanGroup->SetSelLine(0);
	sysConfig.WriteConfig(&sysConfig.sysParam.curEqLineValue);
	return 0;
}

// 如果param1是1则需要预设成默认
LRESULT BassActivity::SetDefault(DWORD param1, DWORD param2)
{
	if (bool(param1))
	{
		AVSET::SetEQ(0);
	}
	else
	{
		AVSET::SetEQ(sysConfig.sysParam.curEqLineValue);
	}
	return 0;
}

void BassActivity::onResume()
{
	
}

BOOL BassActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
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
		}
		return FALSE;

	case CTR_TRANLATE_MES:
		{
			int eq = int(wParam);
			ASSERT (eq>=0&&eq<=9);
			AVSET::SetEQ(eq);
			sysConfig.sysParam.curEqLineValue = eq;
			sysConfig.WriteConfig(&sysConfig.sysParam.curEqLineValue);
		}
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}





static RegisterHelp help("BassActivity", BassActivity::CreateControl);