#pragma once
#include "Activity.h"


class MainPad : public Activity
{
public:
	MainPad(){}
	virtual ~MainPad (){}
	virtual public void onCreate();
	virtual BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );
	static Activity* CreateControl();

private:
	void LoadXml();

};
