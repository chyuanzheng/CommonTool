#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxListGroupBase.h"
#include "GxxSelectListGroupBase.h"

class GxxSetupListLine;
class GxxPicIcon;
class CE_CONTROL_API GxxBassListGroup : public GxxSelectListGroupBase
{

public:
	GxxBassListGroup();
	virtual ~GxxBassListGroup();
	static GxxView* CreateControl();
	virtual bool SetSelLine(int nlan,bool showSel=false );

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	GxxPicIcon *m_bassPic;

	string pic_path[10];

};
