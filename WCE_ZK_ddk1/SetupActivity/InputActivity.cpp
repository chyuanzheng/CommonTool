#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "InputActivity.h"
#include "ControlHelp.h"
#include "GxxSetupListGroup.h"
#include "GxxFileListGroup.h"
#include "GxxAniLable.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "GxxPicLine.h"
#include "GxxSwText.h"
static RegisterHelp help("InputActivity", InputActivity::CreateControl);

Activity* InputActivity::CreateControl()
{
	return new InputActivity;
}

void InputActivity::onCreate()
{
	Activity::onCreate();
	setContentView("layout\\InputActivity.xml");
	setBackColor(0xffff0000);
	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);
	m_btnBack = findViewByName("back_btn");
	ASSERT(m_btnBack!=NULL);

	pLabel_Key[0] = (GxxAniLable*)safeFindViewByName("Label_Key0");
	pLabel_Key[1] = (GxxAniLable*)safeFindViewByName("Label_Key1");
	pLabel_Key[2] = (GxxAniLable*)safeFindViewByName("Label_Key2");
	pLabel_Key[3] = (GxxAniLable*)safeFindViewByName("Label_Key3");
	pLabel_Key[4] = (GxxAniLable*)safeFindViewByName("Label_Key4");
	pLabel_Key[5] = (GxxAniLable*)safeFindViewByName("Label_Key5");
	pLabel_Key[6] = (GxxAniLable*)safeFindViewByName("Label_Key6");
	pLabel_Key[7]= (GxxAniLable*)safeFindViewByName("Label_Key7");
	pLabel_Key[8] = (GxxAniLable*)safeFindViewByName("Label_Key8");
	pLabel_Key[9] = (GxxAniLable*)safeFindViewByName("Label_Key9");

	pLabel_KeyC = (GxxAniLable*)safeFindViewByName("Label_KeyC");

	pLabel_KeyXin = (GxxAniLable*)safeFindViewByName("Label_KeyXin");	
	pLabel_KeyXin->setDraw(false);
	pLabel_KeyJin = (GxxAniLable*)safeFindViewByName("Label_KeyJin");
	pLabel_KeyJin->setDraw(false);

	pLabelDeleteAll = (GxxAniLable*)safeFindViewByName("LabelDeleteAll");

	pLabel_KeyRing = (GxxAniLable*)safeFindViewByName("Label_KeyRing");
	pLabel_KeyRing->setEnable(false);

	pTextBox_PhoneNum = (GxxAniLable*)safeFindViewByName("TextBox_PhoneNum");
	pTextBox_PhoneTitle = (GxxSwText*)safeFindViewByName("Label_Title");

}



BOOL InputActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				RetToFucActivity();
				return TRUE;
			}
			else if ((GxxView *)wParam == m_btnBack)
			{
				finish();
				return TRUE;
			}
			else if ((GxxView *)wParam == pLabelDeleteAll)
			{
				m_text = "";
				pTextBox_PhoneNum->SetText(m_text.c_str());
				CheckEnableKey();
				return TRUE;
			}
			else if ((GxxView *)wParam == pLabel_KeyC)
			{
				if (m_text.size()>0)
				{
					m_text.erase(--m_text.end());
					pTextBox_PhoneNum->SetText(m_text.c_str());
					CheckEnableKey();
				}
				return TRUE;
			}
			else if ((GxxView *)wParam == pLabel_KeyRing)
			{
				Activity::SetContentStr("password",m_text);
				finish();
				return TRUE;
			}
			else if ( InputKey((GxxView *)wParam))
			{
				return TRUE;
			}

		}
		return FALSE;
	default:
		return FALSE;
	}
	return FALSE;
}

void InputActivity::onResume()
{
	Activity::GetContentInt("num",m_num);
	ASSERT(m_num>0);
	bool b=Activity::GetContentStr("title_id",m_titleID);
	ASSERT(b);
	pTextBox_PhoneTitle->setTextFromId(m_titleID);
	m_text.clear();
	pTextBox_PhoneNum->SetText(m_text.c_str());
	CheckEnableKey();
}

bool InputActivity::InputKey( GxxView * lable )
{
	for (int i = 0; i<10; ++i)
	{
		if (lable == pLabel_Key[i])
		{
			m_text += 48+i;
			pTextBox_PhoneNum->SetText(m_text.c_str());
			CheckEnableKey();
			return true;
		}
	}
	return false;
}

void InputActivity::CheckEnableKey()
{
	if (m_text.size()<m_num)
	{
		for (int i = 0; i<10; ++i)
		{
			pLabel_Key[i]->setEnable(true);
		}
		pLabel_KeyRing->setEnable(false);
	}
	else
	{
		for (int i = 0; i<10; ++i)
		{
			pLabel_Key[i]->setEnable(false);
		}
		pLabel_KeyRing->setEnable(true);
	}
}
