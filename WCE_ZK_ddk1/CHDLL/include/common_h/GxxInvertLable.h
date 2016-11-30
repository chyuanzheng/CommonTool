#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "SkiaBitmapManager.h"
class CE_CONTROL_API GxxInvertLable : public GxxView
{
public:
	GxxInvertLable();
	virtual ~GxxInvertLable();
	static GxxView* CreateControl();

	virtual void setCtrLayout( TiXmlElement * ele);

protected:
	virtual void Paint();//**
	virtual void Draw( );
	int m_Invert_y;


};
