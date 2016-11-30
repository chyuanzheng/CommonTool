#pragma once

#include "GxxPicture.h"
#include "GxxAniPictureA.h"
#include "AnimationManage.h"
#include "GxxSwText.h"
#include "GxxAniButton.h"
#include "GxxPicIcon.h"
class CE_CONTROL_API GxxAniLable : public GxxAniButton
{
public:
	GxxAniLable();
	virtual ~GxxAniLable();
	static GxxView* CreateControl();
	void SetText(const wstring &str, bool bDraw = true);
	void SetText(const wstring &str,int index, bool bDraw = true);
	void SetText(const char *str,bool bDraw = true);
	void SetLayout(int center_x,int center_y,const char *picDisable);
	GxxSwText* GetTextView();
protected:
	virtual void setCtrLayout( TiXmlElement * ele);

	void setChildLayout( TiXmlElement * ele ) ;
	
private:
	
	GxxSwText *m_swtext[3];
	GxxPicIcon *m_picIcon[3];

};
