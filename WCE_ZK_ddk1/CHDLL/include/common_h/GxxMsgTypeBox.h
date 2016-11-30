#pragma once
#include "AnimationManage.h"
#include "GxxPicture.h"


class GxxSwText;
class GxxAniLable;
class  GxxMsgTypeBox : public GxxPicture
{
public:
	GxxMsgTypeBox();
	virtual ~GxxMsgTypeBox();
	static GxxView* CreateControl();
	static void ShowMsgBox( const string& sid, GxxView* view,DWORD param, int type);
	static void ShowMsgBox( const wstring& text, GxxView* view,DWORD param, int type);
protected:
	virtual void onPause();

	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	void ResetBox();

	virtual void setCtrLayout( TiXmlElement * ele);
	void DoShowMsgBox( const string& sid, GxxView* view,DWORD param, int type);
	void DoShowMsgBox( const wstring& text, GxxView* view,DWORD param, int type);

	void SetMsgBoxValue( GxxView* view, DWORD param, int type );

private:
	GxxSwText  *m_textlable;
	GxxAniLable* m_leftBtn;
	GxxAniLable * m_left_Dial_Btn;
	GxxAniLable* m_rightBtn;
	GxxView *m_mesView;
	DWORD m_param;

	static  GxxMsgTypeBox * S_msgBox;
	RECT    m_defRect;
	
};
