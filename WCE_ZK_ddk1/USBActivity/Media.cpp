#include "StdAfx.h"
#include "Media.h"
#include "../i2c/chip.h"
#include "../PIP/PIP.h"
#include "Audio/Audio.h"
#include "MesDef.h"

FileListGroupInterface* Media::fileList;

Media::Media(void)
{
	dLastPlayTime = 0;
	dTotalPlayTime = 0;
	iItemPlaying = 0;
	eMediaMode = MEDIAMODE_NONE;
	
}

void Media::SetFileList(FileListGroupInterface* _fileList)
{
	ASSERT(_fileList != NULL);
	fileList = _fileList;

	
}

Media::~Media(void)
{
}

//设定播放模式：单曲循环，全部循环……等
void Media::SetPlayMode(int mode)
{
	ePlayMode = mode;
}
void Media::Init()
{
	//初始化为停止模式
	eLastPlayStatus = PLAY_STATUS_STOP;

	eRandomMode = RANDOMMODE_NO;

}

void Media::TurnToCEAV()
{
	//切换到当前的声道
	Audio::ToMedia();
}


 
FileItem::EnumFileType Media::GetFileTypeByMediaMode(int eMode)
{
	FileItem::EnumFileType efileType = FileItem::FILE_TYPE_MUSIC;
	switch(eMode)
	{
	case MEDIAMODE_NONE:
	case MEDIAMODE_MUSIC:
		{
			efileType = FileItem::FILE_TYPE_MUSIC;
		}
		break;
	case MEDIAMODE_MOVIE:
		{
			efileType = FileItem::FILE_TYPE_MOVIE;
		}
		break;
	case MEDIAMODE_PICTURE:
		{
			efileType = FileItem::FILE_TYPE_PICTURE;
		}
		break;
	default:
		{
			efileType = FileItem::FILE_TYPE_MUSIC;
		}
	}
	return efileType;
}

void Media::Resume()
{
	
	ASSERT(this != NULL);

	InitMeida();
	
	efileType = GetFileTypeByMediaMode(eMediaMode);

	//曲目处于停止状态时
	if (eLastPlayStatus == PLAY_STATUS_STOP)
	{
		if (sLastPlayPath.IsEmpty() || GetFileAttributes(sLastPlayPath) == -1)
		{
			

			// 生成 vMediaList
			{
				vMediaList.clear();
				MediaListItem mListItem;
				//mListItem.iPlayItem = 0;
//				mListItem.sItemPath = fileList->GetCurFolderPath();
				//vMediaList.push_back(mListItem);

				// 将当前目录所有的文件添加到vMediaList;
				//int j=0;
				//iItemPlaying = 0;
				int iFileCount;
				fileList->GetTotalMediaCountInAll(efileType, iFileCount);
				for (int i=0;i < iFileCount;i++)
				{
					FileItem item;// = new FileItem() ;
					fileList->GetMediaItemInAll(i, efileType, item);

					mListItem.iPlayItem = i; 
					
					mListItem.sItemPath = item.filePath;
					vMediaList.push_back(mListItem);
				}

				
				if(iFileCount != 0)		//列表中存在曲目
				{

					// 生成随机播放列表
					vMediaRandomList.clear();
					//iItemRandomPlaying = 0;
					vMediaRandomList.push_back(iItemPlaying);	// 插入第一首曲目
					int size = vMediaList.size()-1;	// 减去第一首
					srand(GetTickCount());
					// 1. 生成顺序数组
					for (int i=1;i<size+1;i++)	
					{
						if (vMediaRandomList[0] != i)
						{
							vMediaRandomList.push_back(i);
						}
					}
					// 2. 进行随机交换
					size = vMediaRandomList.size()-1;
					for (int i=size;i>1;i--)
					{
						int randnum = rand()%i;
						int tmp = vMediaRandomList[i];
						vMediaRandomList[i] = vMediaRandomList[randnum];
						vMediaRandomList[randnum] = tmp;
					}
					if (!sLastPlayPath.IsEmpty() && GetFileAttributes(sLastPlayPath) != -1)	//文件存在
					{
						int ret = Play(sLastPlayPath.GetData(), 0);
					}
					else
					{
						

						int iRandomMode = GetRandomMode();
						iItemPlaying = 0;
						if(iRandomMode == RANDOMMODE_YES)
						{
							iItemPlaying = vMediaRandomList[iItemPlaying];						
						}
						
						int iRet = GetFileAttributes(vMediaList[iItemPlaying].sItemPath.c_str());
						if ( iRet != -1)
						{
							int ret = Play(vMediaList[iItemPlaying].sItemPath.c_str(), 0);
							sLastPlayPath = vMediaList[iItemPlaying].sItemPath.c_str();
						}
						
					}
					

				}
				//RETAILMSG(COUT_MSG, (TEXT("video path = %s\r\n"),vMediaList[1].sItemPath.GetData()));
				
			}

		}
		else if (GetFileAttributes(sLastPlayPath) != -1)	//文件存在
		{
			//fileList->SetRootPath(_T(""));
	//		fileList->GotoPath(sLastPlayPath.Left(sLastPlayPath.ReverseFind(_T('\\'))),  
	//														sMediaExtName);
			//int iPlaying = 0;
			// 重新加载vMediaList
			{
				vMediaList.clear();
				MediaListItem mListItem;
				//mListItem.iPlayItem = 0;
				/*mListItem.sItemPath = fileList->GetCurFolderPath();
				vMediaList.push_back(mListItem);*/
				// 将当前目录所有的文件添加到vMediaList;
				int j=0;
				int iFileCount;
				fileList->GetTotalMediaCountInAll(efileType, iFileCount);
				for (int i=0;i < iFileCount;i++)
				{
					FileItem item;// = new FileItem() ;
					fileList->GetMediaItemInAll(i, efileType, item);

					mListItem.iPlayItem = i; 

					mListItem.sItemPath = item.filePath;
					vMediaList.push_back(mListItem);
				}

				
				if(iFileCount != 0)		//列表中存在曲目
				{

					// 生成随机播放列表
					vMediaRandomList.clear();
					//iItemRandomPlaying = 0;
					vMediaRandomList.push_back(iItemPlaying);	// 插入第一首曲目
					int size = vMediaList.size()-1;	// 减去第一首
					srand(GetTickCount());
					// 1. 生成顺序数组
					for (int i=1;i<size+1;i++)	
					{
						if (vMediaRandomList[0] != i)
						{
							vMediaRandomList.push_back(i);
						}
					}
					// 2. 进行随机交换
					size = vMediaRandomList.size()-1;
					for (int i=size;i>1;i--)
					{
						int randnum = rand()%i;
						int tmp = vMediaRandomList[i];
						vMediaRandomList[i] = vMediaRandomList[randnum];
						vMediaRandomList[randnum] = tmp;
					}

					//iItemPlaying = 0;
					int iRet = GetFileAttributes(sLastPlayPath);
					if ( iRet != -1)
					{
						int ret = PlayMediaFile(sLastPlayPath, dLastPlayTime);
						//sLastPlayPath = sLastPlayPath;
					}

				}
			}
		}
	}
	if (eLastPlayStatus == PLAY_STATUS_PAUSE || eLastPlayStatus == PLAY_STATUS_PLAY)
	{	
		if (dTotalPlayTime == dLastPlayTime && dLastPlayTime != 0)
		{
			NextVideo();
		}
		else if(eLastPlayStatus == PLAY_STATUS_PAUSE || eLastPlayStatus == PLAY_STATUS_PLAY)
		{	
			Play(sLastPlayPath, dLastPlayTime);
			//PlayMediaFile(sLastPlayPath, dLastPlayTime);
		}
	}	
}

BOOL Media::PlayMediaFile(GxxString str, double playtime)
{
	//发送曲目当前ID和总数
	AfxPostMessage(CTR_USB_MEDIA_VIDEO_CHANG, iItemPlaying, eMediaMode);
	
	
	 
	BOOL ret = PlayMedia(str, playtime);
	
	AfxPostMessage(CTR_USB_MEDIA_PLAY, 0, 0);
	
	return ret;

}

BOOL Media::PlayMedia(GxxString str, double playtime/* = 0*/)
{

	BOOL ret = 0;


	//

	//ret = MediaControl::PlayMusicFile(str, playtime);
	//RETAILMSG(COUT_MSG, (TEXT("video path = %s\r\n"),str.GetData()));

	return ret;
}


BOOL Media::NextVideo()
{
	if (vMediaList.empty())
	{
		return 0;
	}

	
		if (eRandomMode == RANDOMMODE_YES)
		{
			int errorItem = 0;
ALLLOOP2:
			if (++iItemRandomPlaying > vMediaRandomList.size()-1)
			{
				iItemRandomPlaying = 0;
			}
			iItemPlaying = vMediaRandomList[iItemRandomPlaying];

			int ret = Play(vMediaList[iItemPlaying].sItemPath.c_str(), 0);
			if (ret != 1)
			{
				if (++errorItem > vMediaRandomList.size()-1)
				{
					return ret;
				}
				goto ALLLOOP2;
			}
			return ret;
		}
	



	if (ePlayMode == PLAYMODE_ALLLLOOP || ePlayMode == PLAYMODE_SINGLELOOP)
	{
		int errorItem = 0;
		if (eRandomMode == RANDOMMODE_NO)
		{
ALLLOOP:
			if (++iItemPlaying > vMediaList.size()-1)
			{
				iItemPlaying = 0;
			}

			int ret = Play(vMediaList[iItemPlaying].sItemPath.c_str(), 0);
			if (ret != 1)
			{
				if (++errorItem > vMediaList.size()-1)
				{
					return ret;
				}
				goto ALLLOOP;
			}
		}

//		if (eRandomMode == RANDOMMODE_YES)
//		{
//ALLLOOP2:
//			if (++iItemRandomPlaying > vMediaRandomList.size()-1)
//			{
//				iItemRandomPlaying = 0;
//			}
//			iItemPlaying = vMediaRandomList[iItemRandomPlaying];
//
//			int ret = Play(vMediaList[iItemPlaying].sItemPath.c_str(), 0);
//			if (ret != 1)
//			{
//				if (++errorItem > vMediaRandomList.size()-1)
//				{
//					return ret;
//				}
//				goto ALLLOOP2;
//			}
//		}
	}
	return TRUE;
}

void Media::SetCore()
{
	eRandomMode = RANDOMMODE_NO;

	ePlayMode++;
	if (ePlayMode > PLAYMODE_SINGLELOOP)
	{
		ePlayMode = PLAYMODE_ALLLLOOP;
	}
	SetPlayMode(ePlayMode);
}

void Media::SetShuffle()
{
	ePlayMode = PLAYMODE_ALLLLOOP;

	if (eRandomMode == RANDOMMODE_NO)
	{
		eRandomMode = RANDOMMODE_YES;
		

		// 生成随机播放列表
		vMediaRandomList.clear();
		iItemRandomPlaying = 0;
		vMediaRandomList.push_back(iItemPlaying);	// 插入第一首曲目
		int size = vMediaList.size()-1;	// 减去第一首
		srand(GetTickCount());
		// 1. 生成顺序数组
		for (int i=1;i<size+1;i++)
		{
			if (vMediaRandomList[0] != i)
			{
				vMediaRandomList.push_back(i);
			}
		}
		// 2. 进行随机交换
		size = vMediaRandomList.size()-1;
		for (int i=size;i>=1;i--)
		{
			int randnum = rand()%i + 1;
			int tmp = vMediaRandomList[i];
			vMediaRandomList[i] = vMediaRandomList[randnum];
			vMediaRandomList[randnum] = tmp;
		}
	}
	else
	{
		eRandomMode = RANDOMMODE_NO;
	}

	
};

int Media::PrevVideo()	//上一曲
{

	if (dLastPlayTime > 3)
	{
		dLastPlayTime = 0;
		Play(vMediaList[iItemPlaying].sItemPath.c_str(), dLastPlayTime);
		return 0;
	}
	if (vMediaList.empty())
	{
		return 0;
	}
	if (eRandomMode == RANDOMMODE_YES)
	{
		if (--iItemRandomPlaying < 0)
		{
			iItemRandomPlaying = vMediaRandomList.size()-1;
		}
		iItemPlaying = vMediaRandomList[iItemRandomPlaying];
	}
	else
	{
		if (--iItemPlaying >=  vMediaList.size())
		{
			iItemPlaying  = vMediaList.size()-1;
		}

	}
	Play(vMediaList[iItemPlaying].sItemPath.c_str(), 0);
	//PlayMediaFile(vMediaList[iItemPlaying].sItemPath.c_str(), 0);
	return 1;
}

void Media::Pause()
{
	PauseMedia();
	AfxPostMessage(CTR_USB_MEDIA_PAUSE, 0, 0);
}
bool Media::Play(GxxString str, double playtime)
{
	
	PlayMediaFile(str, playtime);
	AfxPostMessage(CTR_USB_MEDIA_PLAY, 0, 0);
	return true;
}

void Media::Play()
{
	
	PlayMedia();
	AfxPostMessage(CTR_USB_MEDIA_PLAY, 0, 0);
}

BOOL Media::StopVideo()
{
	StopMedia();
	AfxPostMessage(CTR_USB_MEDIA_STOP, 0, 0);
	return true;
}
