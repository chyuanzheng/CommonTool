#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxString.h"
#include "CRect.h"
#include "HardwareDllModule.h"
class CE_HardwareDll_API GxxLabel : public GxxView
{
protected:
	HANDLE     m_handleUp;
	HANDLE	   handleOldUp;

	//按钮图片
	//判断是否被按下
	TCHAR     m_isGxxLabelDown;
protected:

	//绘画
	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    

public:
	GxxLabel();
	virtual ~GxxLabel();

	static GxxView* CreateControl();

	//void SetImage(const wchar_t* str, BOOL bDraw = TRUE);
	void SetText(string str, BOOL bDraw = TRUE);
	void SetText(const wstring &str, BOOL bDraw = TRUE);
	void Empty();
	//void startAnimation(Animation * ani);

	

protected:
	
	
	int iWidth;
	int iHeight;



	string strText;

	wstring wstrText;
};
