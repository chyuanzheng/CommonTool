#pragma once
#include "Activity.h"
#include "SetupDllModule.h"
#include "GXNotify.h"

class GxxAniLable;
class GxxSwText;
class GxxPicture;
class GxxParamPad;

class CE_SETUPACTIVITY_API  ParametricEqPad : public Activity
{
public:
	ParametricEqPad();
	virtual ~ParametricEqPad ();
	virtual  void onCreate();

	void ResetSelect();

	virtual  void onResume();

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	static Activity* CreateControl();
	void RenewPadBtn();

	void SetFreq( float ffreq );

private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, ParametricEqPad);

	GxxView  *m_btx;
	GxxView * m_btnBack;
	
	GxxSwText   *m_text_khz;
	GxxAniLable *m_level_up;
	GxxAniLable *m_level_text;
	GxxAniLable *m_level_down;

	GxxAniLable *m_freq_left;
	GxxAniLable *m_freq_text;
	GxxAniLable *m_freq_right;

	GxxAniLable *m_qvalue_left;
	GxxAniLable *m_qvalue_text;
	GxxAniLable *m_qvalue_right;


	GxxAniLable *m_flat;
	GxxAniLable *m_band;
	GxxAniLable *m_preset1;
	GxxAniLable *m_preset2;
	GxxAniLable *m_preset3;
	
	GxxParamPad *m_paramPad;

};


