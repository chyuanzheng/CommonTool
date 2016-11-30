#pragma once
#include "media.h"

class MusicMedia : public Media
{
public:
	MusicMedia(GxxString sMediaExtName);
	~MusicMedia(void);
	void InitMeida();
	void PlayMedia();
	BOOL PlayMedia(double playtime);
	void PlayAndPause();
	void PauseMedia();
	void StopMedia();
	void Save();

	BOOL PlayMedia(GxxString str, double playtime = 0);
};
