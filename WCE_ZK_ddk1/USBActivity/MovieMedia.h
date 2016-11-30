#pragma once
#include "media.h"
#include "TccMediaWndEx.h"
#include "Activity.h"
class MovieMedia :
	public Media
{
public:
	Activity* pActivity;

	TccMediaWndEx *pMediaWnd;

	
	MovieMedia(GxxString, Activity*, CHAR*);
	~MovieMedia(void);
	BOOL PlayMedia(double playtime);
	void PlayMedia();
	void InitMeida();
	void PlayAndPause();
	void PauseMedia();
	void StopMedia();
	void Save();



	BOOL PlayMedia(GxxString str, double playtime = 0);

	//CRect rcMediaWnd;
private:
	GxxString fileName;
	GxxString fileExt;


	HANDLE hEventPlayMovie;

	static GxLock lock;

	static DWORD PlayMovieThread(LPVOID lpParam);

	void CreatePlayMovieThread();
	void PlayMovieByThread(GxxString strPlayPath, int iPlayTime);
};
