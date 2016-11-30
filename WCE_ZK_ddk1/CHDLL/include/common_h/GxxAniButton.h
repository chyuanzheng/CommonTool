#pragma once

#include "GxxPicture.h"
#include "GxxAniPictureA.h"
#include "AnimationManage.h"
class CE_CONTROL_API GxxAniButton : public GxxView,GxxTimer 
{
public:
	GxxAniButton();
	void SetLayout(int center_x,int center_y,const char *picUp,const char* picTwo, const char* Ani,const char* disable);
	virtual ~GxxAniButton();
	static GxxView* CreateControl();
	HANDLE GetActionHandle();
	void   SetSelect(bool b);
	bool   GetSelect(){return m_pPicSel->getDraw();}
protected:
	virtual void  onEnable(bool e);
	GxxAniPictureA *m_pAniPicBack;
	GxxPicture *m_pPicUp;
	GxxPicture *m_pPicUpTwo;
	GxxPicture *m_pPicSel;//选中状态
	GxxPicture *m_pPicDisable;
	UINT     m_idTimer;

	//按钮图片
	//判断是否被按下
	bool       m_isBtnDown;
	bool       m_isClick;//没有动画就不允许按键
	bool       m_isSelEnable;
protected:
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual void TimerTick(UINT nIDEvent);
	void Start_AniBack();
	void Stop_AniBack();
};
