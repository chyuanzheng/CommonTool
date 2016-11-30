#pragma once
#include "Activity.h"
#include "SetupDllModule.h"
#include "GXNotify.h"

class GxxSetupListGroup;
class GxxFileListGroup;
class GxxAniLable;
class GxxPicLine;
class GxxSwText;
class CE_SETUPACTIVITY_API  BSFActivity : public Activity
{
public:
	BSFActivity(){}
	virtual ~BSFActivity (){}
	virtual  void onCreate();
	virtual  void onResume();

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();
	void BSF_SetSubwOn( UINT data );
	void SetPosition();
	void SetInZone( char &bt );
	void setSubwText();
	void BSF_SetPhaseOn( bool b );
private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, BSFActivity);
	GxxView  *m_btx;
	GxxView * m_btnBack;

	GxxAniLable *m_front;
	GxxAniLable *m_left;
	GxxAniLable *m_right;
	GxxAniLable *m_center;
	GxxAniLable *m_rear;


	GxxAniLable *m_subw_left;
	GxxAniLable *m_subw_text;
	GxxAniLable *m_subw_right;

	GxxAniLable *m_subw_level_left;
	GxxAniLable *m_subw_level_text;
	GxxAniLable *m_subw_level_right;

	GxxAniLable *m_subw_phase_left;
	GxxAniLable *m_subw_phase_text;
	GxxAniLable *m_subw_phase_right;

	GxxPicLine *m_showPicLine;
	GxxSwText  *m_textFade;
	GxxSwText  *m_textBalance;


};


