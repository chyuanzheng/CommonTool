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
	enum	//ѭ��ģʽ
	{
		//PLAYMODE_ALL,	//ȫ��
		PLAYMODE_ALLLLOOP,	//ȫ��ѭ��
		PLAYMODE_SINGLELOOP,	//����ѭ��
	};

	enum	//���ģʽ
	{
		RANDOMMODE_NO,
		RANDOMMODE_YES
	};


	enum	//ý��
	{
		MEDIAMODE_NONE,
		MEDIAMODE_MUSIC,
		MEDIAMODE_MOVIE,
		MEDIAMODE_PICTURE
	};
	int eMediaMode;


	int eRandomMode;
	int ePlayMode;
	int GetRandomMode(){return eRandomMode;}	//�������ģʽ
	int GetPlayMode(){return ePlayMode;}	//���ز���ģʽ
	void SetShuffle();
	void SetCore();
	
	double dLastPlayTime;
	double dTotalPlayTime;


	int eLastPlayStatus;

	

	static void TurnToCEAV();	//�л�����ǰ����
	void Init();
	void Resume();
	
	virtual void Save(){};

	
	BOOL NextVideo();	//��һ��Ŀ
	int PrevVideo();	//��һ��Ŀ
	void Play();	//����
	void Pause();	//��ͣ
	BOOL StopVideo();	//ֹͣ
	bool Play(GxxString str, double playtime = 0);	//����

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

	GxxString sMediaExtName;	//��ǰ��ý���ļ��ĺ�׺��

};
