#pragma once
#include "Activity.h"
#include "SetupDllModule.h"
#include "GXNotify.h"

class GxxAniLable;
class GxxSwText;
class GxxPicture;
class GxxPicIcon;
class CE_SETUPACTIVITY_API  TimeCorrectPad : public Activity
{
public:
	enum BTN_TYPE{ Front_L,Front_R,Rear_L,Rear_R,SubW_L,SubW_R};
	TimeCorrectPad();
	virtual ~TimeCorrectPad ();
	virtual  void onCreate();
	virtual  void onResume();

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	void SavePreset( int nth );

	

	

	static Activity* CreateControl();
	void BtnDownSet( BTN_TYPE type );

	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, TimeCorrectPad);
protected:
	virtual void Draw( );
private:
	
	void SetPreset(int i);
	void SetFlat();
	void SetInZone( BYTE &bt );
	void SetMidText( int type );
	void DoSetMidText( GxxAniLable * left, GxxAniLable * right, GxxAniLable * mid, BYTE &bt );
	void SetTimeVal( int type );
	void CheckSumValue();
	GxxView  *m_btx;
	GxxView * m_btnBack;

	GxxSwText *m_txtRemainVal;

	bool       m_isMsec;
	GxxSwText *m_txtCm;
	GxxSwText *m_txtMsec;

	GxxSwText *m_s_txtCm;
	GxxSwText *m_s_txtMsec;

	GxxAniLable *m_frontL_left;
	GxxAniLable *m_frontL_mid;
	GxxAniLable *m_frontL_right;
	GxxAniLable *m_frontR_left;
	GxxAniLable *m_frontR_mid;
	GxxAniLable *m_frontR_right;

	GxxAniLable *m_rearL_left;
	GxxAniLable *m_rearL_mid;
	GxxAniLable *m_rearL_right;
	GxxAniLable *m_rearR_left;
	GxxAniLable *m_rearR_mid;
	GxxAniLable *m_rearR_right;

	GxxAniLable *m_subwL_left;
	GxxAniLable *m_subwL_mid;
	GxxAniLable *m_subwL_right;
	GxxAniLable *m_subwR_left;
	GxxAniLable *m_subwR_mid;
	GxxAniLable *m_subwR_right;

	GxxPicIcon *m_frontL_pic;
	GxxPicIcon *m_frontR_pic;

	GxxPicIcon *m_rearL_pic;
	GxxPicIcon *m_rearR_pic;

	GxxPicIcon *m_set_pic;

	GxxPicIcon *m_subwL_pic;
	GxxPicIcon *m_subwR_pic;

	//GxxAniLable *m_freq_left;
	//GxxAniLable *m_freq_text;
	//GxxAniLable *m_freq_right;

	//GxxAniLable *m_qvalue_left;
	//GxxAniLable *m_qvalue_text;
	//GxxAniLable *m_qvalue_right;


	GxxAniLable *m_flat;
	GxxAniLable *m_cm_msec;
	GxxAniLable *m_preset1;
	GxxAniLable *m_preset2;
	GxxAniLable *m_preset3;


	BYTE * m_presetTimeFrontL;
	BYTE * m_presetTimeFrontR;
	BYTE * m_presetTimeRearL;
	BYTE * m_presetTimeRearR;

	BYTE * m_presetSubwL;
	BYTE * m_presetSubwR;
	

};


