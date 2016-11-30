#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "HardwareDllModule.h"

class CE_HardwareDll_API GxxProgressBar : public GxxView
{
protected:
	HANDLE     m_handleBack;	//背景
	HANDLE     m_handleProgress;	//前景
	HANDLE     m_handleConver;	//封面
	RECT       m_ProRect;//显示的RECT
	int        iMax;
	int		   iMin;
	int        iPos;	//位置

protected:

	//绘画
	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
    

public:
	GxxProgressBar();
	virtual ~GxxProgressBar();
	virtual void SetDisplayPos(int n);
	int  GetRatioNum();
	void SetRange(int _iMin, int _iMax);
	static GxxView* CreateControl();
	//void startAnimation(Animation * ani);
	

};
