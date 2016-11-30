#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
class CE_CONTROL_API GxxAniPictureA : public GxxPicture
{
public:
	GxxAniPictureA();
	virtual ~GxxAniPictureA();
	void Start();
	void Stop();

protected:
	static HANDLE S_hAniScale;
	
};
