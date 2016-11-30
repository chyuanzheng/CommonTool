#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxListGroupBase.h"
#include "GxxSelectListGroupBase.h"

class GxxSetupListLine;
class CE_CONTROL_API GxxLangListGroup : public GxxSelectListGroupBase
{

public:
	GxxLangListGroup();
	virtual ~GxxLangListGroup();
	static GxxView* CreateControl();

};
