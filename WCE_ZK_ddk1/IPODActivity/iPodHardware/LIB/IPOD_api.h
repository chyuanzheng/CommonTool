/**************************************************************************			
	Copyright (c) Telechips, Inc.
	All Rights Reserved

	File Name : iPod_api.h

	LastModifier : SYS1 group

	Project: TCC76x/TCC86X

	SW-Component:  iPod module

	SW-Module: The interface between iPod library and Application. 

	Description: 
	
**************************************************************************/
#ifndef _IPOD_API_H_
#define _IPOD_API_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include "./IPOD_error.h"
#include "./iPodLib.h"

#ifdef IPOD_UART_INCLUDE
#include "./iPod_interface_uart.h"
#endif

#ifdef IPOD_USB_INCLUDE
#include "./iPod_interface_usb.h"
#endif

#ifdef WINCE
#include <windows.h>
#include "../ipodconfig.h"
#include <winioctl.h>
#include <winuser.h>
#endif
/********************************************/
/* Select TCCxxxx chipset                   */
/********************************************/
#define TCC890X_WINCE
//#define TCC880X_WINCE
//#define TCC892X_WINCE


//#define IPOD_SWITCH
//#define IPOD_RX_IRQ_ONLY
#define IPOD_CPBUFSIZE (50*1024)
#define IPOD_RXBUFSIZE ((128*128*2)+1024)	//(65535+6)		//uart rx buffer size
//#define IPOD_TXBUFSIZE 65535+6//255+4	최소한 512 이상 설정
//#define IPOD_TXBUFSIZE 255+4				//uart tx buffer size
#define IPOD_TXBUFSIZE 2048

#ifdef WINCE
#define USBH_AUDIO_PLAYBUFSIZE 0
#define AUTH_IC_20B
//#define AUTH_IC_20C
#define	IAP_CP_slaveaddr	0x20 
#endif

#define IPOD_TOTALBUFSIZE	(IPOD_CPBUFSIZE+IPOD_TXBUFSIZE+(IPOD_RXBUFSIZE*3)+USBH_AUDIO_PLAYBUFSIZE)
#define IPOD_SYNC 0xFF					//packet sync flag
#define IPOD_START 0x55					//packet start flag

#define IPOD_5MS_TIMEOUT 300
#define IPOD_5MS_TIMEOUT_MOUNT 400

#define IPOD_1MS_TIMEOUT 50 //(IPOD_5MS_TIMEOUT*5)
#define IPOD_1MS_TIMEOUT_MOUNT 65//(IPOD_5MS_TIMEOUT_MOUNT*5)

#define IPOD_1S_TIME_CHECK 1000

#if defined(TCC860x) || defined(TCC78X)

#ifndef	BITCSET
#define	BITCSET(X, CMASK, SMASK)	( (X) = ((((U32)(X)) & ~((U32)(CMASK))) | ((U32)(SMASK))) )
#endif

#ifndef	BITCLR
#define	BITCLR(X, MASK)				( (X) &= ~((U32)(MASK)) )
#endif

#ifndef	ISONE
#define	ISONE(X, MASK)				( (U32)(X) & ((U32)(MASK)) )
#endif

#ifndef	ISZERO
#define	ISZERO(X, MASK)				(  ! (((U32)(X)) & ((U32)(MASK))) )
#endif

#ifndef	ISCLR
#define	ISCLR(X, MASK)				(  ! (((U32)(X)) & ((U32)(MASK))) )
#endif

#endif /*defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)*/


/*************************************************************************/
/*enum                                                                                                                    */
/*************************************************************************/
enum
{
	IPOD_UFD_REMOVED,
	IPOD_UFD_INSERTED
};

typedef enum
{
	IPOD_AUDIO_TRACK = 0x00,
	IPOD_VIDEO_TRACK = 0x01


}IPOD_PLAYBACK_MODE;


//IPOD status 
typedef enum
{
	IPOD_UNPLUGED = 0x00000000,	
	IPOD_PLUGED = 0x00000001,
	IPOD_INITIALIZED = 0x00000002,
	IPOD_MOUNTED = 0x00000003,
	IPOD_UNMOUNTED = 0x00000004,
	
	IPOD_STATUS_MAX= 0x7FFFFFFF
}IPOD_STATE;

//Track Capabilities
typedef enum
{
	IPOD_CAPABILITIES_AUDIOBOOK = ((unsigned int)0x01<<0),
	IPOD_CAPABILITIES_CHAPTERS = ((unsigned int)0x01<<1), 
	IPOD_CAPABILITIES_ALBUM_ARTWORK = ((unsigned int)0x01<<2),
	IPOD_CAPABILITIES_SONG_LYRICS = ((unsigned int)0x01<<3),
	IPOD_CAPABILITIES_PODCAST_EPISODE = ((unsigned int)0x01<<4),
	IPOD_CAPABILITIES_RELEASE_DATE = ((unsigned int)0x01<<5),
	IPOD_CAPABILITIES_DESCRIPTION = ((unsigned int)0x01<<6),
	IPOD_CAPABILITIES_CONTAINS_VIDEO = ((unsigned int)0x01<<7),
	IPOD_CAPABILITIES_CURRENTLY_QUEUED_TO_PLAY_AS_VIDEO = ((unsigned int)0x01<<8),
	IPOD_CAPABILITIES_CAPABLE_OF_GENERATING_GENIUS_PLAYLIST = ((unsigned int)0x01<<13),
	IPOD_CAPABILITIES_ITUNESU_EPISODE = ((unsigned int)0x01<<14)
}IPOD_CAPABILITIES;

typedef struct tag_IPOD_TRACK_CAPABILITIES_INFO{
	unsigned char m_Audiobook;
	unsigned char m_Chapter;
	unsigned char m_AlbumArtwork;
	unsigned char m_SongLyrics;
	unsigned char m_PodcastEpisode;
	unsigned char m_ReleaseDate;
	unsigned char m_Description;
	unsigned char m_ContainsVideo;
	unsigned char m_CurrentlyQueuedToPlayAsVideo;
	unsigned char m_CapableOfGeneratingGeniusPlaylist;
	unsigned char m_ItunseUEpisode;
	unsigned char m_padding;
}IPOD_TRACK_CAPABILITIES_INFO, *pIPOD_TRACK_CAPABILITIES_INFO;

typedef struct tag_IPOD_STATUS{
	IPOD_STATE ipod_state;
	unsigned int DevNo;
/* 	void *iPod_Handle; */
	unsigned int SamplingFreq;
}IPOD_BASIC_INFO, *pIPOD_INFO;


typedef struct tag_IPOD_ARTWORK_INFO{
	unsigned int BasicFormatID;
	unsigned int CapableFormatID[IPOD_MAX_ARTWORK];
	unsigned int CapableSize[IPOD_MAX_ARTWORK];
	unsigned int MaxDisplaySize;
	unsigned int MaxFormatCount;
}IPOD_ARTWORK_INFO, *pIPOD_ARTWORK_INFO;

#define IPOD_NOT_ESTABLISED_SESSIONGID (0xFFFFFFFF)

#define IPOD_PLAY_INFO_MAX_CNT 6
typedef struct tag_IPOD_PLAYINFO
{
	/* Do not modify - Status member*/
	unsigned int m_Status;

	/* If Application detect the disconnection of iPod, Please set the below member*/
	unsigned int DisconnecEvt;
	/* User can add up the member variables*/
	unsigned int CurrentIdx;
	unsigned int TimePosition; /*sec*/
	unsigned int TimePosition_ms; /*m sec*/
	unsigned int TotalTime;
	unsigned int TotalPlayNum;
	unsigned int TargetIdx;
	unsigned int BrwsIdx;
	unsigned long ChapterIdx;
	unsigned int ChapterTimePosition;
	unsigned int Disk;
	unsigned int TotalVideos;
	unsigned char *pBuffer;

	/*For Display Remote Lingo*/
	unsigned short ChapterCnt;
	unsigned char PowerStatus;
	unsigned char BatteryLevel;
	
	unsigned char ShuffleStatus;
	unsigned char RepeatStatus;
	unsigned char BackLight;
	unsigned char Holdswitch;
	
	unsigned long EqStatus;

	unsigned short Year;
	unsigned char Month;
	unsigned char Day;
	
	unsigned char Hour;
	unsigned char Minute;
	unsigned char AlarmStatus;
	unsigned char AlarmHour;
	
	unsigned char AlarmMin;
	unsigned char SoundCheck;
	unsigned char AudioBook;
	unsigned char MuteState;
	
	unsigned char UIvolLevel;
	unsigned char AbsoluteVol;
	IPOD_DR_PLAY_STATUS Rd_playStatus;
	unsigned char padding_1; /*Padding*/
		
	IPOD_ARTWORK_INFO ArtworkInfo;
	IPOD_BASIC_INFO Basic_Info;
	IPOD_PLAYBACK_STATUS m_PlayStatus;
	IPOD_PLAYBACK_MODE PlayBackMode;
	IPOD_TRACK_CAPABILITIES_INFO CapabilitiesInfo;

	/*For iPod OS application */
	unsigned long m_iPod_OSApp_DataSesiongID;
	unsigned long m_iPod_OSApp_ProtocolIndex;

	/*For iPod Flow Control */
	unsigned int m_Noti_WaitTime;
	unsigned short m_Noti_OverflowTransID;
	
	/* iPod Name Buffer */
	unsigned char iPodNameBuf[512];
	unsigned long iPodNameActualLen;
}IPOD_PLAY_INFO, *pIPOD_PLAY_INFO;





/*************************************************************************/
/*Variable                                                                                                                 */
/*************************************************************************/

extern const IPOD_ACCINFO_TOKEN_VAL gIPOD_AccInfo;
extern const IPOD_ACC_PREF_SETTING_FORMAT gIPOD_Pref[IPOD_PREF_MAX_CNT];
extern IPOD_PLAY_INFO gIPOD_PlayInfo[IPOD_PLAY_INFO_MAX_CNT];

extern unsigned char IPOD_Bitmap[24*50];

extern volatile unsigned char *IPOD_UTF8DecodeBuffer;	//UTF8 decode buffer

extern volatile unsigned int IPOD_RX_W_Ptr;	// For filling receive buffer
extern volatile unsigned int IPOD_RX_R_Ptr;	// For fetching receive buffer
extern volatile unsigned int IPOD_TX_Start;	// Start Position which data was pushed

extern unsigned char *pIPOD_RxBuff;			//rx buffer pointer
extern unsigned char *pIPOD_TxBuff;			//tx buffer pointer
extern unsigned char *pIPOD_RXData;		// rx data buffer pointer

extern unsigned int IPOD_RX_Size;			//rx buffer size
extern unsigned int IPOD_TX_Size;			//tx buffer size

extern unsigned int IPOD_SyncFlag;			// set after sync command
extern unsigned int IPOD_LengthSetFlag;		// set after receiving length field

extern unsigned int IPOD_DataLength;		// data length of received packet
extern unsigned int IPOD_RX_DataPtr;		// used to move from buffer to data area

extern IPOD_Command IPOD_RX_Cmd;

//extern unsigned char IPOD_PlayPauseFlag;	// 1: Play , 0: Pause  //This flag is for 0x0029 PlayControl()'s PlayPause toggle command.
extern int IPOD_Insert;						// set after IPOD inserted
//extern int IPOD_Identify;					// set after IPOD identified(not used)
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
extern int IPOD_Access;
extern int IPOD_Navi_Access;
extern int IPOD_FFREW_Flag;
#endif
//extern int IPOD_Transper_Mode;

extern int IPOD_UFDStatusFlag;

extern unsigned char IPOD_Category[5];

extern unsigned char media_kind[10][40];
//extern ArtworkFormat stArtworkFormat[];
//extern pArtworkFormat pstArtworkFormat;



extern MLingoType IPOD_ConvertSingleToMultiLingo(const IPOD_INIT_PARAM *pParam);

/*************************************************************************/
/*IPOD Function                                                                                                         */
/*************************************************************************/
extern int IPOD_ResetVideoSupportDB(void *iPod_Handle);
extern void IPOD_initResource(void);
extern void *IPOD_Malloc_iPodBuf(void);
extern pIPOD_PLAY_INFO IPOD_Get_AudioPlayInfo(void *iPod_Handle);
extern void IPOD_Free_AudioPlayInfo(void *iPod_Handle);

extern void IPOD_API_SetStatus(void *iPod_Handle, IPOD_STATE state);
extern IPOD_STATE IPOD_API_GetStatus(void *iPod_Handle);
extern int IPOD_API_GetDevNo(void *ExtInfo);
extern void IPOD_API_SaveSamplingFreq(void *ExtInfo, unsigned int SamplingFreq);
extern unsigned int IPOD_API_GetSamplingFreq(void *ExtInfo);
extern void *IPOD_GetHandle_fromDevNo(unsigned int DevNo);
extern unsigned int IPOD_Callback_CheckExtInfo(void *ExtInfo, unsigned long SearchingData);

extern IPOD_ERROR IPOD_ResetDataBase(void *iPod_Handle);
extern int IPOD_SelectFileList(void *iPod_Handle);
extern int IPOD_DB_Init(void *iPod_Handle);
extern void IPOD_CheckPlayStatus(void *iPod_Handle);

extern int IPOD_Display_Init(void *iPod_Handle, unsigned int Block);

extern unsigned int IPOD_Callback_TimeDly(void *ExtInfo, unsigned short ticks);
extern void DMP_IPOD_DisplayAlbumArt(int new_index, int loc);

extern int IPOD_Callback_GetReturnPlayInfo(void *ExtInfo);
extern int IPOD_Callback_DisplayRemoteEvent(unsigned char EventNum, const unsigned char *pData, void *ExtInfo);

extern void IPOD_Callback_EndAuthentication(void* iPod_Handle, unsigned int IsSuccess);

extern unsigned int IPOD_Callback_GetWaitTimeMount(void);
extern unsigned int IPOD_Callback_GetWaitTime(void);
extern void IPOD_Callback_SetSamplerate(void *ExtInfo, unsigned int SamplingFrequency);

extern void IPOD_InitBuff(pIPOD_BUF_PARAM buf_param, unsigned char * buffer);
extern void IPOD_BuffReset(void *iPod_Handle);
extern void IPOD_API_Init(void);
extern IPOD_PORT_STATE IPOD_GetDetectStatus(void *ExtInfo);
extern void IPOD_SendSync(void);
extern unsigned char IPOD_Calc_CheckSum(unsigned char *buff);
extern unsigned char IPOD_Calc_CheckSum_L(const unsigned char *data, int size);
extern int IPOD_SendPacket(unsigned char *buff, int len);
extern int IPOD_SendPacket_new(void *Hid_Handle, unsigned char *buff, int len);
extern void IPOD_SetAccess(void *pPlayInfo, int set);
extern void IPOD_API_EventProcess(void);
extern void IPOD_API_SetSkipProcessMode(unsigned int Mode);
extern void IPOD_SetDisconnectionStatus(void *Handle);

extern void IPOD_GetCuriPodInfo(void *iPod_Handle, long *CurFileNum, long *TotalFileNum, long *CurTime);
extern void IPOD_API_InitArtworkInfo(pIPOD_PLAY_INFO pPlayInfo);
extern int IPOD_GetDefaultArtworkFormatID(void *iPod_Handle);
extern IPOD_ERROR IPOD_SetDefaultArtworkFormatID(void *iPod_Handle, unsigned long Lingo);





extern unsigned int IPOD_Get_Oneword(const unsigned char *Data);
extern unsigned short IPOD_Get_Short(const unsigned char *Data);
//extern IPOD_TRACK_CAPABILITIES_INFO IPOD_Get_TrackCapabilities(const unsigned char * Data);

extern void IPOD_API_CheckiPodOption(void *iPod_Handle, pIPOD_INIT_PARAM pParam, pIPOD_LINGO_INFO_DATA pLingo_InfoData);
extern int IPOD_API_Check_Storage_tagging_support(const IPOD_LINGO_INFO_DATA *pLingo_InfoData);

extern IPOD_ERROR IPOD_Callback_OpenDataSessionForProtocol( void *iPod_Handle, unsigned int SessionID, unsigned int nProtocolIndex );
extern IPOD_ERROR IPOD_Callback_CloseDataSession( void *iPod_Handle, unsigned int SessiongID );
extern IPOD_ERROR IPOD_Callback_iPodDataTransfer( void *iPod_Handle, unsigned int usSessionID, unsigned char *pData, unsigned int nDataSize );
extern IPOD_ERROR iPod_ExampleCode_getLingoProtocolVer(void *iPod_Handle, unsigned long Lingo, unsigned char *inform, unsigned char *major, unsigned char *minor);
extern IPOD_ERROR IPOD_API_Transfer_DevData_to_App(void *iPod_Handle, unsigned char *SendBuff, unsigned int size);
extern IPOD_ERROR IPOD_API_GetDRPlayStatus(void *iPod_Handle, IPOD_DR_PLAY_STATUS *playStatus);
extern IPOD_ERROR IPOD_API_SetDRPlayStatus(void *iPod_Handle, IPOD_DR_PLAY_STATUS playStatus);
#ifdef WINCE
extern IPOD_ERROR IPOD_API_Open(void *iPod_Handle);
extern IPOD_ERROR IPOD_API_Malloc_ExtInfo(void *iPod_Handle);
extern HANDLE IPOD_API_GetControlThreadID(void* iPod_Handle);
extern HANDLE IPOD_API_GetDataThreadID(void* iPod_Handle);
#endif
extern void IPOD_API_CheckSetSampleRateInfo(void *pHandle, pIPOD_PLAY_INFO pInfo);
extern IPOD_ERROR IPOD_API_RequestApplicationLaunch(void *iPod_Handle, unsigned char* AppString, unsigned int Strlen);
extern int IPOD_Callback_iPodNotification(void* iPod_Handle, unsigned char EventNum, const unsigned char *pData);
extern IPOD_ERROR IPOD_API_GetSupportMultiLingo(void* iPod_Handle, MLingoType *supportMultiLingo);
extern IPOD_ERROR IPOD_API_GetIDPSSupport(void* iPod_Handle, IPOD_DEFAULT_CONNECTION *IDPS_support);
#if defined(__cplusplus)
};
#endif

#endif	/* _IPOD_API_H_ */

/* End of File */


