
#ifndef _IPOD_HID_H_
#define _IPOD_HID_H_


#define DRIVERSTRING_SZ		L"DriverString"

#define DRIVEROPENCOUNT_SZ		L"OpenCount"

#define IPOD_ONE_WIRE (ML_GENERAL | ML_REMOTE_UI_EXTENDED | ML_DISPLAY_REMOTE | ML_DIGITAL_AUDIO)
#define IPOD_TWO_WIRE (ML_GENERAL | ML_REMOTE_UI_EXTENDED | ML_DISPLAY_REMOTE )

#define IPOD_INIT_RETRY_CNT 3

typedef enum
{
    IPOD_UPDATE_PLAY = 0,
    IPOD_UPDATE_PAUSE
}IPOD_UPDATE_PLAY_STATUS;
// Structure
typedef struct {
	CategoryType	eCategory;		
	unsigned int zStartIndex;
	unsigned int nCount;
}BRWSListReqInfo;

typedef struct{
	CategoryType eCategory;

	DWORD nBrwsDBRecordNum;
	PIPOD_RECORD_TYPE pBrwsDBRecord;
} BRWSGetNameResInfo;

extern HANDLE iPod_DisconnectionDetectThread( HANDLE hWnd, DWORD *pThreadID );

extern HANDLE iPod_StartCMDControlThread( HANDLE hWnd, DWORD *pThreadID ) ;

extern BOOL iPod_StopCMDControlThread( HANDLE hThread, DWORD ThreadID );
extern BOOL iPod_StopDisconnectionDetectThread( HANDLE hThread, DWORD ThreadID );

extern DWORD iPod_GetControlDeviceDriverNumber( DWORD UniqueID );
extern BOOL iPod_RetrieveControlDeviceDriverNumber( DWORD *pDevcieDriverNumber, DWORD *pUniqueID );



////////////////////////////////

typedef enum {
	PS_PAUSED,
	PS_PLAY,
	PS_FFREW,
	PLAYSTATUS_MAX,
} PLAY_STATUS;

typedef struct{
	unsigned int nTotalNum;
	unsigned int nUpdatedCnt;
	unsigned int BrwsDepth;

	CategoryType eCategory;
	int	cateHistory[5];
	int zStartIndex;
	int nCount;
} BRWS_INFO;

typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int displayformat;
	unsigned char *pImage;
} DEVICEDISPLAY_INFO;

typedef struct {
	HANDLE hWnd;
	DWORD m_dwVolume;

	// Command control part
	DWORD m_HIDDrvierNumber;

	HANDLE m_hDisconnectionDetectThread;
	DWORD m_DisconnectionDetectThreadID;

	HANDLE m_hControlThread;
	DWORD m_ControlThreadID;

#ifdef TEST_TERMINATE_THREAD
	BOOL	m_bControlThreadClosing;
	HANDLE	m_hTerminateControlThread;
#endif

	// Event control part
	HANDLE m_hEventThread;
	DWORD m_EventThreadID;

	DWORD m_iPodHandle;
	DWORD m_uniqueID;

	// Audio control part
	DWORD m_AudioDrvierNumber;
	HANDLE m_hAudioThread;
	DWORD m_AudioReadThreadID;

	BOOL m_HIDConnected;
	BOOL m_AudioConnected;

	DWORD m_nTotalNumOfPlayTracks;
	DWORD m_zCurrentTrackIndex;
	BOOL m_bBrwsInitializedFlag;
	PLAY_STATUS m_playstatus;

	DEVICEDISPLAY_INFO m_stDeviceDisplayInfo;

	BRWS_INFO	m_stBrwsViewInfo;
	BRWSListReqInfo m_stBrwsReqInfo;
} IPOD_PLAYER_CONTEXT;

typedef struct {
	DWORD m_DeviceNumber;
	DWORD m_ConnectionType;
	DWORD m_EventThreadID;
	void *m_iPodDev;
}IPOD_CMD_CTRL_PARAM, *pIPOD_CMD_CTRL_PARAM;

typedef enum {
	PLAYBACK_STATE_STOP,
	PLAYBACK_STATE_PLAY,
	PLAYBACK_STATE_PAUSED,
	PLAYBACK_STATE_FF,
	PLAYBACK_STATE_REW,

	PLAYBACK_STATE_MAX, 
}PLAYBACK_STATE;

typedef enum {
	PLAYER_NONE,
	PLAYER_DISCONNECTED,
	PLAYER_CONNECTING,
	PLAYER_DISCONNECTING,
	PLAYER_CONNECTED,

	PLAYER_INITIALIZED,
	PLAYER_STATE_MAX
} PLAYER_STATE;

typedef enum{
	//IPODUI_BRWS_SELECT_ALL,
	IPODUI_BRWS_PLAYLIST,
	IPODUI_BRWS_ARTIST,
	IPODUI_BRWS_ALBUM,
	IPODUI_BRWS_GENRE,
	IPODUI_BRWS_TRACK,
	IPODUI_BRWS_MAX
}IPODUI_BRWS_CATEGORYTYPE;

#endif	// _IPOD_HID_H_
