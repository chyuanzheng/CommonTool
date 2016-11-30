#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAtButton.h"
class CE_CONTROL_API GxxToolButton : public GxxAtButton
{
private:
	GxxPicture *m_picBack;
	BOOL       m_bshow;
	
protected:

	//»æ»­
	virtual void Draw( );
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual TYPE_BTN getBtnType(){return TOOL_BTN;}  

public:
	GxxToolButton(int nth);
	virtual ~GxxToolButton();
	void   renewModule(T_AppModule * m_);
	HANDLE getAniHandle();
	void   showButton(BOOL show);
	virtual void setCtrLayout( TiXmlElement * ele);
	

};
