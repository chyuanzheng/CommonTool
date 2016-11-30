#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxListGroupBase.h"
#include "GxxSelectListGroupBase.h"

class GxxSetupListLine;
class CE_CONTROL_API GxxBtnMatchListGroup : public GxxSelectListGroupBase
{

public:
	GxxBtnMatchListGroup();
	virtual ~GxxBtnMatchListGroup();
	static GxxView* CreateControl();
	virtual bool SetSelLine( int nlan,bool showSel=false  );
};
