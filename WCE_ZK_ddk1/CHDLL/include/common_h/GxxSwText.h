#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "SkiaBitmapManager.h"
class CE_CONTROL_API GxxSwText : public GxxView
{
public:
	GxxSwText();
	virtual ~GxxSwText();
	static GxxView* CreateControl();

	
	void setText(const wstring& wstr);
	void setText(const char *str);
	void setTextFromId(const string& sid);
	void setText(const wstring* textFromId);
	
	const wstring& getText(){ return m_wstrText;}

	void setColor(UINT color);
	void setFormat(UINT f){m_format = f;}
	void setTextFont(UINT color,int size,UINT alpha=255,SkiaBitmapManager::T_TYPEFACE textType = SkiaBitmapManager::msyh);
	virtual void setCtrLayout( TiXmlElement * ele);
	void DrawTextWithRect(int xm,int ym);
	void DrawTextWithRect(const RECT &rc);
	void DrawTextWithRect(const wstring &text,const RECT &rc);
	void DrawTextWithRect(const wstring *text_id,const wstring &text,const RECT &rc);
protected:
	
	virtual void Draw( );
	virtual void OnTextSet(){}
	int    m_size;
	UINT   m_color;
	int    m_alpha;
	wstring m_wstrText;
	const wstring *m_wstrFromId;
	UINT	 m_format;
	H_SKFONT m_wfont;

};
