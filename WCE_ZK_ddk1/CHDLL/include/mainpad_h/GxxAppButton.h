#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAtButton.h"
#define  A_PAGE_SIZE   8
class CE_CONTROL_API GxxAppButton : public GxxAtButton
{

public:
	static RECT       m_pageActRect[A_PAGE_SIZE];//一个页中所有rect
	static RECT       m_pageEditRect[A_PAGE_SIZE];//一个页中所有rect
	void setLocal(int local);
	int  getLocal(){return m_local;}
	virtual TYPE_BTN getBtnType(){return  APP_BTN;}  
protected:
	int     m_local;
	RECT    m_preTextRect; //没有移动前的rect
	//绘画
	virtual    int  GetPageMoveX();
	
    

public:
	GxxAppButton(int nth);
	virtual ~GxxAppButton();
	virtual void setCtrLayout( TiXmlElement * ele);
	
	
};
