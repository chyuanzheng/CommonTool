#pragma once
#include "Activity.h"
#include "SetupDllModule.h"

class GxxFileListGroup;
class CE_SETUPACTIVITY_API  VolumeActivity : public Activity
{
public:
	VolumeActivity(){}
	virtual ~VolumeActivity (){}
	virtual  void onCreate();
	virtual void onResume();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();


private:

};


