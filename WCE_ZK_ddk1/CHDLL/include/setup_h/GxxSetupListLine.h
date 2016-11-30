#pragma once

#include "GxxView.h"
#include "GxxLBLine.h"


class GxxDelimiter;
class GxxSwText;
class GxxAniPictureA;
class GxxPicture;
class CE_CONTROL_API GxxSetupListLine : public GxxLBLine,protected GxxTimer
{
public:
	typedef enum {T_ListBox,T_ListBoxAboutMore,T_Activity,T_Massage,T_None }TYPE_CLICK;//点击启动的类型
	typedef enum {TL_ThreeBtnNum,TL_ThreeBtnBool,TL_ThreeBtnOnOff,TL_ThreeBtnOnMD,TL_LINE_ENABLE,TL_LINE_VERSION,TL_SetChooseBtn,TL_SetChooseBtn_Switch,TL_DEFEAT,TL_None }TYPE_LINE_BTN;//

	GxxSetupListLine();
	virtual ~GxxSetupListLine();

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	TYPE_CLICK getClickType(){return m_clickType;}
	const string &getClickName(){return m_clickName;}
	void SetLineEnable(bool b);
	void setLineLayout(int index,  TiXmlElement * ele );
	GxxSwText *GetTitleText() {return m_pTextTitle;}

private:
	


	TYPE_CLICK      m_clickType;
	string          m_clickName;//要启动的listbox ,activity 的名字

	GxxPicture *m_pPicIcon;//右边 icon
	GxxView  *m_pMoreView;//其它的控件
	GxxSwText *m_pTextTitle;

	TYPE_LINE_BTN   m_btnType;

	void setIconMore();
	void setClickType( TiXmlElement * ele );
	void setMoreView( TiXmlElement * ele );

	

	void APPVersion(GxxSwText *v);
	void setLineChildLayout( TiXmlElement * ele );
	void SetLineDraw( bool b );

private:
	virtual void TimerTick(UINT nIDEvent);
	UINT		m_aboutTimerId;
	bool    m_aboutBtnDown;
	//string   m_title;
	//string   m_btnName;//要设置的xml标签 的名字
	
};
