#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
class CE_CONTROL_API GxxPicture : public GxxView
{
public:
	GxxPicture();
	virtual ~GxxPicture();
	bool setPicHandle( TiXmlElement * ele,const char *attr);
	bool setPicHandle( const char* picPath);
	bool ResetPicHandle(const char* picPath);

	

	void setPicRect(int cx,int cy);
	HANDLE getPicHandle(){return m_hPicture;}
	int getPicWidth();
	int getPicHeight();

	bool  bindHandleRect();//设置画面的显示RECT，必须有 m_hPicture 和 m_ActRect才能设置成功
	bool  bindHandleRect(const RECT &rc);//设置画面的显示RECT，必须有 m_hPicture 和 m_ActRect才能设置成功
	bool  setHandleAlpha(UINT a);

	void DrawPicWithRect(const RECT &rc,UINT alpha = 255);
	void DrawPicWithRect(int xm,int ym,UINT alpha = 255);
	void DrawPic();
protected:
	void DoSetHandle( const char* picPath );
	void DoSetHandle( const WCHAR* picPath );
	virtual void    onMoveRect(int x_len, int y_len );
	HANDLE     m_hPicture;

protected:
	//绘画
	virtual void Draw( );
	void  releaseHandle();
	
    


};
