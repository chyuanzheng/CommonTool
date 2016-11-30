#pragma once
#include "GxxPicture.h"
#include "AnimationManage.h"
class CE_CONTROL_API GxxIconInView : public GxxPicture
{
public:
	GxxIconInView();
	virtual ~GxxIconInView();
	static GxxView* CreateControl();
protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	
};
