#pragma once

#include "GxxSwText.h"
#include "AnimationManage.h"
#include "SkiaBitmapManager.h"
class CE_CONTROL_API GxxMarginText : public GxxSwText
{
public:
	GxxMarginText();
	virtual ~GxxMarginText();


	static GxxView* CreateControl();
	void setMargin(UINT mc);

protected:
	virtual void Draw( );
	virtual void setCtrLayout( TiXmlElement * ele);
	UINT   *m_marginColor;
	void FreeColor() ;


};
