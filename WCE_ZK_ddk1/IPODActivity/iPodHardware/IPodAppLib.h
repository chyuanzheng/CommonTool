#pragma once
#include "iPodConfig.h"
#include "iPodCommandControl.h"
#include "CHardware.h"
#include "GxxString.h"
#include "GxxView.h"

#define DECLARE_WMMSGHANDLER(theFun, theClass) \
	static DWORD theFun(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)\
{\
	theClass *pThis = (theClass *)dwParam;\
	return pThis->theFun(msg, wParam, lParam);\
}\
	DWORD theFun(UINT msg, WPARAM wParam, LPARAM lParam);

enum
{
	IPOD_MSG_NAME=100,
	IPOD_MSG_TIME,
	IPOD_MSG_PLAYSTATUS,
	IPOD_MSG_ARTIST,
	IPOD_MSG_ALBUM,
	IPOD_MSG_GENRE,
	IPOD_MSG_TITLE,
	IPOD_MSG_NUMRECORD,
	IPOD_MSG_CATRECORD,
	IPOD_MSG_SHUFFLE,
	IPOD_MSG_REPEAT,
	IPOD_MSG_AUTHSUCCESS,
	IPOD_LIST_INIT,
	IPOD_LIST_START,
	IPOD_LIST_INSERT,
	IPOD_LIST_INSERT_END,
	IPOD_PLAY_CONTROL,
	IPOD_PLAY_STATUS_FRESH,
	
};

#define UI_BRWS_UPDATE_UNIT_CNT	(30)

class IPodAppLib : public CHardware
{
private:
	DWORD nCurrentFileNum;
	DWORD nTotalFileNum;

	IPOD_PLAYER_CONTEXT *m_pPlayerContext;
	BYTE *m_pAlbumArtRawData;
	DWORD m_AlbumArtBitmap_Width;
	DWORD m_AlbumArtBitmap_Height;
	DWORD m_AlbumArtBitmap_x;
	DWORD m_AlbumArtBitmap_y;

	void PostMsg_ToDisconnectionDetectThread(DWORD msgID, WPARAM wParam, LPARAM lParam);
	void PostMsg_ToCMDControlThread( DWORD msgID, WPARAM wParam, LPARAM lParam);
	void PostMsg_ToEventControlThread( DWORD msgID, WPARAM wParam, LPARAM lParam);
	void PostMsg_ToAudioReadThread( DWORD msgID, WPARAM wParam, LPARAM lParam);
	LPCTSTR GetBrowserCategoryName( CategoryType eCategory );
	CategoryType GetBrowserTopCategory( DWORD zIndex );
	DWORD GetLogoImageForIPOD(BYTE *pRGB565Data,int width,int height);
	void InitBrws(void);
	void ClearBrws(void);
	void SetPlayControlButtonEnable( BOOL bEnable );
	void SetControlUIState(BOOL bEnable);
	static IPodAppLib* pInstance;
	IPOD_SEL_DB_TYPE m_ipod_hierarchy;
	BRWS_INFO	music_brws_info;
	BRWS_INFO	video_brws_info;
	int			current_video_index;
	int			current_music_index;
	BOOL		hasVideo;
	BOOL		isConnect;
	HWND		hWnd;
	bool        m_isToReceiveList;//是否准备接收列表
	BOOL		ipod_mute;
	int			ipod_volume;
	IPodAppLib();
public:
	int		iCurTime;
	int		iTotalTime;
	static IPodAppLib * Instance(HWND hwnd)
	{
		if (!pInstance)
		{
			pInstance = new IPodAppLib();
			pInstance->Init(hwnd);
			pInstance->ipod_mute = 0;
		}
		return pInstance;
	}
public:
	int		GetCurTime()
	{
		return iCurTime;
	}
	int		GetTotalTime()
	{
		return iTotalTime;
	}
	void IpodPlay();
	void IpodPause();
	void SetPlaypause();
	void IpodNext();
	void IpodPrev();
	BOOL IsConnected();
	BOOL HasVideo();

	BOOL ListBack();

	void SetShuffle(int mode);
	void SetRepeat(int mode);
	void SetPlayTime(int time);
	void SetPlayTime2(int time);
	void SetPlayFrew();//fast后退
	void SetPlayFf();//fast前进

	IPOD_SEL_DB_TYPE GetMediaPathType(){return m_ipod_hierarchy;}	//媒体类型 xyf add

	//BOOL MusicResume(BOOL bPlay);
	//BOOL VideoResume(BOOL bPlay);
	void InitHierarchy(IPOD_SEL_DB_TYPE hierachy, int index);
	BOOL IpodSelectList(int index);

	void MusicRestore();
	void VideoRestore();
	void ResetDBSelectionHierarchy(IPOD_SEL_DB_TYPE hierachy);
public:
	void Init(HWND hwnd);

	////////////////////////////////////

	//static DWORD  OnMessageDetectHID(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageDetectAudio(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageUpdateCurrentTrackInfo(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageUpdateCurrentTrackNumber(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageUpdateTrackPlaybackPosition(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageUpdateFFSeekStop(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageUpdateREWSeekStop(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageUpdateSamplingFrequency(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_Init(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageSetiPodHandle(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_Stop(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_Terminate(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_Play(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_Pause(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_NextTrack(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_PrevTrack(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_FF(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_REW(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageShuffle(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageRepeat(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessagePlaying(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessagePause(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_GetCurrentTrackIndex(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_GetTotalPlayTracks(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_GetTitle(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_Artist(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_Album(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_AlbumArt(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_InformSamplingFreqChecked(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_GetDeviceDisplayInfo(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlRes_SetDeviceDisplayImage(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlBrwsRes_Init(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlBrwsRes_SelectAll(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlBrwsRes_Select(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlBrwsRes_MoveUpper(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlBrwsRes_GetName(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageControlBrwsRes_VideoInit(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);
	//static DWORD  OnMessageGetiPodName(GxxView *pControl, DWORD dwParam,UINT &msg, WPARAM wParam, LPARAM lParam);



	DECLARE_WMMSGHANDLER(OnMessageDetectHID, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageDetectAudio, IPodAppLib);

	DECLARE_WMMSGHANDLER(OnMessageUpdateCurrentTrackInfo, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageUpdateCurrentTrackNumber, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageUpdateTrackPlaybackPosition, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageUpdateFFSeekStop, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageUpdateREWSeekStop, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageUpdateSamplingFrequency, IPodAppLib);


	DECLARE_WMMSGHANDLER(OnMessageControlRes_Init, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageSetiPodHandle, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_Stop, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_Terminate, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_Play, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_Pause, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_NextTrack, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_PrevTrack, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_FF, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_REW, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageShuffle, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageRepeat, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessagePlaying, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessagePause, IPodAppLib);


	DECLARE_WMMSGHANDLER(OnMessageControlRes_GetCurrentTrackIndex, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_GetTotalPlayTracks, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_GetTitle, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_Artist, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_Album, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_AlbumArt, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_InformSamplingFreqChecked, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_GetDeviceDisplayInfo, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlRes_SetDeviceDisplayImage, IPodAppLib);

	DECLARE_WMMSGHANDLER(OnMessageControlBrwsRes_Init, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlBrwsRes_Select, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlBrwsRes_MoveUpper, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageControlBrwsRes_GetName, IPodAppLib);
	DECLARE_WMMSGHANDLER(OnMessageGetiPodName, IPodAppLib);

	//DECLARE_WMMSGHANDLER(OnMessageControlExt_Func1, iPodLib);
	//DECLARE_WMMSGHANDLER(OnMessageControlExt_Func2, iPodLib);
	//DECLARE_WMMSGHANDLER(OnMessageControlExt_Func3, iPodLib);
	//DECLARE_WMMSGHANDLER(OnMessageControlExt_Func4, iPodLib);
	//DECLARE_WMMSGHANDLER(OnMessageControlExt_Func5, iPodLib);
	//DECLARE_WMMSGHANDLER(OnMessageSetFullBandWidth, iPodLib);

	
	void Ipod_Mute(BOOL mute);
	void Ipod_SetVolume(DWORD dwVolume);
};

