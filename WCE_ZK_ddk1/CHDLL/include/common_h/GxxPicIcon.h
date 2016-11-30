#pragma once
#include "GxxPicture.h"
#include "AnimationManage.h"
class CE_CONTROL_API GxxPicIcon : public GxxPicture
{
public:
	GxxPicIcon();
	virtual ~GxxPicIcon();
	static GxxView* CreateControl();
	const char* GetPicPath();
	bool   SetPicPath(const char* path);
	bool   SetPicPath(const WCHAR* path);
protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	
};
