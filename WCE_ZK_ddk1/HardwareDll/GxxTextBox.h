#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxString.h"
#include "CRect.h"
#include "HardwareDllModule.h"
#include "GxxPicIcon.h"
#include "GxxSwText.h"
#include "GxxPicIcon.h"

class CE_HardwareDll_API GxxTextBox : public GxxPicIcon
{
public:
	//清空
	void DeleteAll();

	//是否为空
	bool IsEmpty();

	//获取长度
	int GetLength();

	//增加一个字符
	bool AddOneChar(char c);

	//删除一个字符
	bool DeleteOneChar();

	wstring GetText();

	void SetText(const wstring &str, bool bDraw = true);
	void SetText(const char *str,bool bDraw = true);
protected:
	
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	


	GxxSwText *m_swtext;
	GxxPicIcon *m_picIcon;
	GxxPicIcon *m_pPicDisable;

	void SetLayout( int center_x,int center_y,const char *picDisable );
	//void setChildLayout( TiXmlElement * ele );
	virtual void setCtrLayout( TiXmlElement * ele);

public:
	GxxTextBox();
	virtual ~GxxTextBox();

	static GxxView* CreateControl();
};
