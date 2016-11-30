#pragma once
#include "Activity.h"
#include "SetupDllModule.h"

class GxxSetupListGroup;
class GxxFileListGroup;
class GxxAniLable;
class GxxPicLine;
class GxxSwText;
class CE_SETUPACTIVITY_API  InputActivity : public Activity
{
public:
	InputActivity(){}
	virtual ~InputActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	static Activity* CreateControl();
	bool InputKey( GxxView * lable );
	void CheckEnableKey();
private:
	GxxView  *m_btx;
	GxxView * m_btnBack;
	int   m_num;
	string m_titleID;
	string m_text;

	GxxAniLable* pLabel_Key[10];

	GxxAniLable* pLabel_KeyC;
	GxxAniLable* pLabel_KeyXin;
	GxxAniLable* pLabel_KeyJin;
	GxxAniLable* pLabelDeleteAll;

	GxxAniLable* pLabel_KeyRing;
	GxxAniLable* pTextBox_PhoneNum;
	GxxSwText* pTextBox_PhoneTitle;
};


