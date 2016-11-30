#pragma once
#include "TccMediaWnd.h"
#include "ControlHelp.h"
#include "pip/PIP.h"
#include "HardwareDllModule.h"
//#include "GXNotify.h"

#define SHOW_FULL_VIDEO 1
typedef void (*FunButton)(GxxView *p, void *dwParam);
class CE_HardwareDll_API TccMediaWndEx : public TccMediaWnd
{
private:
	
	FunButton	funClick;
	void*		dwParam;
	HANDLE m_handleUp;

	CRect rcOld;

	int iWidth;
	int iHeight;
	string strText;

	

	

public:
	TccMediaWndEx::TccMediaWndEx()
	{
		ptClickPosX = 0;
		ptClickPosY = 0;

	} 



	BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );

	//设置警告语
	void SetWarning(GxxAniLable* pLabel, bool bIsShow);

	bool IsFullScreen();	//用于判断是否全屏

	static GxxView* CreateControl()
	{
		return new TccMediaWndEx;
	}


	 

	void SetFun(FunButton fun, void *parma);
	


	void setCtrLayout( TiXmlElement * ele );
	//void setCtrolLayoutByCenterPoint( TiXmlElement * ele );

	void Draw();

	BOOL InMyArea( int x, int y );
	void SetFullScreen();
	//缩小屏幕
	void ReductionScreen();

	void setDraw(bool bShow);

	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);

	WORD ptClickPosX;
	WORD ptClickPosY;
	//
};


	