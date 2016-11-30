#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "VolumeActivity.h"
#include "ControlHelp.h"
#include "GxxFileListGroup.h"
 

Activity* VolumeActivity::CreateControl()
{
	return new VolumeActivity;
}

void VolumeActivity::onCreate()
{
	Activity::onCreate();
	setContentView("layout\\VolumePad.xml");
}
 

BOOL VolumeActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_LISTBOX_MES:
		{

			return TRUE;
		}
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
/*			if ((GxxView *)wParam == m_btx)
			{
				finish();
				return TRUE;
			}*/			
		}
		return FALSE;
	default:
		return FALSE;
	}
	return FALSE;
}

void VolumeActivity::onResume()
{

	
}

static RegisterHelp help("VolumeActivity", VolumeActivity::CreateControl);