#pragma once
#include "GxxString.h"
#include "GxxFileListGroup.h"
#include "VolumeControl.h"

class MediaListItem
{
public:
	int	iPlayItem;
	wstring sItemPath;
};

class Media
{
public:
	enum	//循环模式
	{
		//PLAYMODE_ALL,	//全部
		PLAYMODE_ALLLLOOP,	//全部循环
		PLAYMODE_SINGLELOOP,	//单曲循环
	};

	enum	//随机模式
	{
		RANDOMMODE_NO,
		RANDOMMODE_YES
	};


	enum	//媒体
	{
		MEDIAMODE_NONE,
		MEDIAMODE_MUSIC,
		MEDIAMODE_MOVIE,
		MEDIAMODE_PICTURE
	};
	int eMediaMode;


	int eRandomMode;
	int ePlayMode;
	int GetRandomMode(){return eRandomMode;}	//返回随机模式
	int GetPlayMode(){return ePlayMode;}	//返回播放模式
	void SetShuffle();
	void SetCore();
	
	double dLastPlayTime;
	double dTotalPlayTime;


	int eLastPlayStatus;

	

	static void TurnToCEAV();	//切换到当前声道
	void Init();
	void Resume();
	
	virtual void Save(){};

	
	BOOL NextVideo();	//下一曲目
	int PrevVideo();	//上一曲目
	void Play();	//播放
	void Pause();	//暂停
	BOOL StopVideo();	//停止
	bool Play(GxxString str, double playtime = 0);	//播放

	virtual void PlayMedia(){};
	virtual BOOL PlayMedia(GxxString str, double playtime = 0);
	virtual BOOL PlayMedia(double playtime){return false;}
	BOOL PlayMediaFile(GxxString str, double playtime = 0);
	virtual void PlayAndPause(){};
	virtual void InitMeida() = 0;
	virtual void PauseMedia(){};
	virtual void StopMedia(){};


	static void SetFileList(FileListGroupInterface* _fileList);

	Media(void);
	~Media(void);

	
	FileItem::EnumFileType efileType;
	FileItem::EnumFileType GetFileTypeByMediaMode(int eMode);

	double playtime;
	GxxString sLastPlayPath;
	int iItemPlaying;
	void SetItemPlaying(int iItem)
	{
		iItemPlaying = iItem;
	}
	int GetItemPlaying()
	{
		return iItemPlaying;
	}
	void SetLastPlayPath(GxxString str)
	{
		sLastPlayPath =str;
	}
	GxxString GetLastPlayPath(){return sLastPlayPath;}
	double GetPlayTime(){return dLastPlayTime;}
	void SetPlayTime(double _LastPlayTime)
	{
		dLastPlayTime = _LastPlayTime;
	}
	
	
protected:
	static FileListGroupInterface* fileList;

	int eLastMediaMode;

	std::vector<int>			vMediaRandomList;
	std::vector<MediaListItem>	vMediaList;
	int iItemRandomPlaying;
	
	void SetPlayMode(int mode);

	GxxString sMediaExtName;	//当前的媒体文件的后缀名

};
