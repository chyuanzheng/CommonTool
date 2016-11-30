#pragma once
#include "media.h"
#include "GxxDCContainer.h"
#include "PIP.h"
class PictureMedia :
	public Media
{
private:
	GxxDCContainer* pPictureContainer;		//¿Ø¼þ£¬ÏÔÊ¾Í¼Æ¬

public:
	PictureMedia(GxxString);
	virtual ~PictureMedia(void);
	void InitMeida();
	BOOL PlayMedia(GxxString str, double playtime = 0);
	void PlayAndPause();
	void Save();

	void SetDisplayLable(GxxDCContainer* p)
	{
		pPictureContainer = p;
	}
};
