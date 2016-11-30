#pragma once
#include "GxxPicture.h"
#include "AnimationManage.h"
class CE_CONTROL_API GxxDelimiter : public GxxPicture
{
public:
	GxxDelimiter();
	virtual ~GxxDelimiter();
	static GxxView* CreateControl();
	void setLayout();
protected:
	static string s_str_path;  
	
	
};
