/**************************************************************************			
	Copyright (c) Telechips, Inc.
	All Rights Reserved

	File Name : iPodLib.h

	LastModifier : SYS1 group 1team

	Project: TCC76x/TCC86X

	SW-Component:  iPod module

	SW-Module: The interface between iPod library and Application. 

	Description: 
	
**************************************************************************/

#ifndef _IPOD_LIB_H_
#define _IPOD_LIB_H_

#ifdef IPOD_INCLUDE


#if defined(__cplusplus)
extern "C" {
#endif


/*************************************************************************/
/*Lingo ID define                                                                                                      */
/*************************************************************************/
typedef unsigned char		SLingoType;

#define SL_GENERAL					0x00
#define SL_MICROPHONE				0x01
#define SL_SIMPLE_REMOTE			0x02
#define SL_DISPLAY_REMOTE			0x03
#define SL_REMOTE_UI_EXTENDED		0x04

typedef unsigned int		MLingoType;

#define ML_GENERAL 					0x0001
#define ML_MICROPHONE				0x0002
#define ML_SIMPLE_REMOTE 			0x0004
#define ML_DISPLAY_REMOTE			0x0008
#define ML_REMOTE_UI_EXTENDED		0x0010
#define ML_ACCESSORY_POWER		0x0020
#define ML_USB_HOST_CONTROL		0x0040
#define ML_RF_TRANSMITTER			0x0080
#define ML_ACCESSORY_EQ			0x0100
#define ML_DIGITAL_AUDIO			0x0400
#define ML_STORAGE					0x1000


#if 0
typedef unsigned char		IPOD_LINGOS;

#define LINGO_GENERAL				0x00
#define LINGO_MICROPHONE			0x01
#define LINGO_SIMPLE_REMOTE		0x02
#define LINGO_DISPLAY_REMOTE		0x03
#define LINGO_EXTENDED_INTERFACE	0x04
#define LINGO_ACCESSORY_POWER		0x05
#define LINGO_USB_HOST_CONTROL	0x06
#define LINGO_RF_TUNER				0x07
#define LINGO_ACCESSORY_EQUALIZER	0x08
#define LINGO_SPORTS				0x09
#define LINGO_DIGITAL_AUDIO		0x0A
#define LINGO_STORAGE				0x0C
#define LINGO_LOCATION				0x0E
#define LINGO_MAX					0x0F
#else

typedef enum
{
	LINGO_GENERAL					= 0x00U,
	LINGO_MICROPHONE				= 0x01U,
	LINGO_SIMPLE_REMOTE			= 0x02U,
	LINGO_DISPLAY_REMOTE			= 0x03U,
	LINGO_EXTENDED_INTERFACE		= 0x04U,
	LINGO_ACCESSORY_POWER		= 0x05U,
	LINGO_USB_HOST_CONTROL		= 0x06U,
	LINGO_RF_TUNER				= 0x07U,
	LINGO_ACCESSORY_EQUALIZER	= 0x08U,
	LINGO_SPORTS					= 0x09U,
	LINGO_DIGITAL_AUDIO			= 0x0AU,
	LINGO_STORAGE					= 0x0CU,
	LINGO_LOCATION				= 0x0EU,
	LINGO_MAX						= 0x0FU
}IPOD_LINGOS;

#endif


// Accessory capabilities bit values //
#define AC_ANALOG_LINE_OUT		(0x00000001<<0)
#define AC_ANALOG_LINE_IN			(0x00000001<<1)
#define AC_ANALOG_VIDEO_OUT		(0x00000001<<2)
#define AC_USB_DIGITAL_AUDIO		(0x00000001<<4)
#define AC_SUPPORT_IPHONE_OS_APP	(0x00000001<<9)
#define AC_CHECK_IPOD_VOLUME		(0x00000001<<11)


#define IPOD_MAX_ARTWORK	6

/*************************************************************************/
/*Enum                  			                                                                             */
/*************************************************************************/
typedef enum 
{
	IPOD_NORMAL = 0x00U, 
	IPOD_FAST = 0x01U,
	IPOD_SLOW = 0xFFU
}AudiobookSpeed;

typedef enum 
{
	CAPAINFO, //Track capabilities/information  
	PODCASTNAME,
	RELEASEDATE,
	DESCRIPTION,
	SONGLYRICS,
	GENRE,
	COMPOSER,
	ARTWORKCOUNT
}TrackInformationType;

typedef enum
{
	IPOD_LIB_ALL,
	IPOD_LIB_PLAYLIST,
	IPOD_LIB_ARTIST,
	IPOD_LIB_ALBUM,
	IPOD_LIB_GENRE,
	IPOD_LIB_TRACK,
	IPOD_LIB_COMPOSER,
	IPOD_LIB_AUDIOBOOK,
	IPOD_LIB_PODCAST
}CategoryType;

#define MEDIA_KIND IPOD_LIB_GENRE

typedef enum 
{
	IPOD_STOPPING = 0x00U,  
	IPOD_PLAYING = 0x01U,
	IPOD_PAUSED = 0x02U,
	IPOD_STATUS_ERROR = 0xFFU	//Enable all change notification
}IpodPlayStatus;

typedef enum
{
	/* the new setting persists after accessory detach */
	UPDATE_NEW_SETTING,

	/* the original setting is restored on detach */
	RESTORE_ORG_SETTING
}RestoreOnExit;

typedef enum 
{

	DISABLENOTIFICATION = 0x00,  //Disable all change notification
	ENABLENOTIFICATION = 0x01,	//Enable all change notification

	ONE_BYTE_FORMAT = 0x00,  //Disable all change notification
	FOUR_BYTE_FORMAT = 0x01,	//Enable all change notification
	IPOD_EVT_BASIC_PLAY_STATUS = (0x01<<0),
	IPOD_EVT_EXTENDED_PLAY_STATUS_CHANGES = (0x01<<1),
	IPOD_EVT_TRACK_INDEX = (0x01<<2),
	IPOD_EVT_TRACK_TIME_OFFSET_MSEC = (0x01<<3),
	IPOD_EVT_TRACK_TIME_OFFSET_SEC = (0x01<<4),
	IPOD_EVT_CHAPTER_INDEX = (0x01<<5),
	IPOD_EVT_CHAPTER_OFFSET_MSEC = (0x01<<6),
	IPOD_EVT_CHAPTER_OFFSET_SEC = (0x01<<7),
	IPOD_EVT_TRACK_UNIQUE_ID = (0x01<<8),
	IPOD_EVT_TRACK_MEDIA_TYPE = (0x01<<9),
	IPOD_EVT_TRACK_LYRICS_READY = (0x01<<10),
	IPOD_EVT_TRACK_CAPABILITIES_CHANGED = (0x01<<11),
	IPOD_EVT_TRACK_PLAYBACK_ENGINE_CONTENTS_CHANGED = (0x01<<12)

//	IPOD_EVT_MAX = 0x7FFFFFFF
	
}SetPlayStatusNotification;



typedef enum
{
	STOPPED = 0x00000000U,
	TRACKCHANGED = 0x00000001U,
	FFSEEKSTOP = 0x00000002U,
	REWSEEKSTOP = 0x00000003U,
	TRACKPOSITION = 0x00000004U,
	CHAPTERINDEX = 0x00000005U,
	PLAYBACK_STATUS_EXT = 0x00000006U,  /* Extended play state changes */
	TRACKTIME_OFFSET = 0x00000007U,
	CHAPTER_TIME_OFFSET_MSEC = 0x00000008U,
	CHAPTER_TIME_OFFSET_SEC = 0x00000009U,
	TRACK_UNIQUE_ID = 0x0000000AU,
	TRACK_PLAYBACK_MODE = 0x0000000BU,
	TRACK_LYRICS_READY = 0x0000000CU,
	TRACK_CAPABILITIES_CHANGED = 0x0000000DU,
	PLAYBACK_ENGINE_CONTNENTS_CHANGED = 0x0000000EU,
	
	NOTIFICATION_MAX = 0x7FFFFFFFU
	
}NotificationPlayStatus;

typedef enum
{
	IPOD_DR_EVT_TRACK_POSITION = 0x00U,
	IPOD_DR_EVT_TRACK_INDEX = 0x01U,
	IPOD_DR_EVT_CHAPTER_INFO = 0x02U,
	IPOD_DR_EVT_PLAY_STATUS = 0x03U,
	IPOD_DR_EVT_MUTE_UI_VOL = 0x04U,
	IPOD_DR_EVT_POWER_BATTERY = 0x05U,
	IPOD_DR_EVT_EQALIZER_STATE = 0x06U,
	IPOD_DR_EVT_SHUFFLE = 0x07U,
	IPOD_DR_EVT_REPEAT = 0x08U,
	IPOD_DR_EVT_DATE_TIME = 0x09U,
	IPOD_DR_EVT_ALARM = 0x0AU,
	IPOD_DR_EVT_BACKLIGHT = 0x0BU,
	IPOD_DR_EVT_HOLD_SWITCH = 0x0CU,
	IPOD_DR_EVT_SOUND_CHECK = 0x0DU,
	IPOD_DR_EVT_AUDIOBOOK = 0x0EU,
	IPOD_DR_EVT_TRACK_POSITION_IN_SECONDS = 0x0FU,
	IPOD_DR_EVT_MUTE_UI_ABSOLUTE_VOL = 0x10U,
	IPOD_DR_EVT_TRACK_CAPABILITIES = 0x11U,
	IPOD_DR_EVT_PLAYBACK_ENGINE_CONTENTS_CHANGED = 0x12U,
	
	IPOD_DR_EVENT_MAX = 0x7FU

}IPOD_REMOTE_EVENT_NOTI;


typedef enum
{
	IPOD_STATUS_STOPPED = 0x02U,
	IPOD_STATUS_FFW_SEEK_STARTED = 0x05U,
	IPOD_STATUS_REW_SEEK_STARTED = 0x06U,
	IPOD_STATUS_FFW_REW_SEEK_STOPPED = 0x07U,
	IPOD_STATUS_PLAYING = 0x0AU,
	IPOD_STATUS_PAUSED = 0x0BU,
	
	IPOD_PLAYBACK_STATUS_MAX = 0x7FFFFFFFU

}IPOD_PLAYBACK_STATUS;

typedef enum
{
	IPOD_DR_STATUS_TRACK_POS_MS = 0x00U,
	IPOD_DR_STATUS_PLAYBACK_INDEX = 0x01U,
	IPOD_DR_STATUS_CHAPTER_INFO = 0x02U,
	IPOD_DR_STATUS_PLAY_STATUS = 0x03U,
	IPOD_DR_STATUS_MUTE_AND_VOLUME = 0x04U,
	IPOD_DR_STATUS_POWER_AND_BATTERY = 0x05U,
	IPOD_DR_STATUS_EQ_SETTING = 0x06U,
	IPOD_DR_STATUS_SHUFFLE_SETTING = 0x07U,
	IPOD_DR_STATUS_REPEAT_SETTING = 0x08U,
	IPOD_DR_STATUS_DATA_AND_TIME = 0x09U,
	IPOD_DR_STATUS_ALARM_STATE_AND_DATE = 0x0AU,
	IPOD_DR_STATUS_BACKLIGHT = 0x0BU,
	IPOD_DR_STATUS_HOLD_SWITCH = 0x0CU,
	IPOD_DR_STATUS_SOUND_CHECK = 0x0DU,
	IPOD_DR_STATUS_AUDIO_BOOK_SPEED = 0x0EU,
	IPOD_DR_STATUS_TRACK_POS_S = 0x0FU,
	IPOD_DR_STATUS_MUTE_UI_ABSOLUTE_VOL = 0x10U,
	
	IPOD_STATUS_INFO_MAX = 0x7FU

}IPOD_DR_STATUS_INFO;

typedef enum
{
	IPOD_DR_PLAYBACK_STOPPED = 0x00U,
	IPOD_DR_PLAYING = 0x01U,
	IPOD_DR_PLAYBACK_PAUSED = 0x02U,
	IPOD_DR_FAST_FORWARD = 0x03U,
	IPOD_DR_FAST_REWIND = 0x04U,
	IPOD_DR_END_FAST_FORWARD_OR_REWIND =0x05U,

	IPOD_DR_MAX_PLAYSTATUS = 0x7FU

}IPOD_DR_PLAY_STATUS;

// Connection mode iAP over USB
typedef enum{
	TWO_WIRE_CONNECTION,
	ONE_WIRE_CONNECTION,
	CONNECTION_MODE_MAX
} IAP_CONNECTION_MODE;

typedef struct{
	unsigned char m_Mute;
	unsigned char m_Vol;
	unsigned char m_AbsoluteVol;
}IPOD_DR_STATEINFO_MUTEVOL;

typedef struct{
	unsigned short m_Year;
	unsigned char m_Month;
	unsigned char m_Day;
	unsigned char m_Hour;
	unsigned char m_Min;
}IPOD_DR_DATETIME;

typedef struct{
	unsigned char m_State;
	unsigned char m_Hour;
	unsigned char m_Min;
}IPOD_DR_ALARM;

typedef union tag_IPOD_DR_SETSTATEINFO_PARAM_DATA{
	unsigned long m_TrackPos_ms;
	unsigned long m_TrackIndex;
	unsigned short m_ChapterIndex;
	IPOD_DR_PLAY_STATUS m_PlayStatus;
	IPOD_DR_STATEINFO_MUTEVOL m_MuteVol;
	unsigned long m_EqIndex;
	unsigned char m_ShuffleState;
	unsigned char m_RepeatSetting;
	IPOD_DR_DATETIME m_DateTime;
	IPOD_DR_ALARM m_Alarm;
	unsigned char m_BackLight;
	unsigned char m_SoundCheck;
	unsigned char m_AudioBookSpeed;
	unsigned short m_TrackPos_s;
	IPOD_DR_STATEINFO_MUTEVOL  m_MuteUiAbsoluteVol;
}IPOD_DR_SETSTATEINFO_PARAM_DATA, *pIPOD_DR_SETSTATEINFO_PARAM_DATA;


typedef struct {
	IPOD_DR_STATUS_INFO m_InfoType;
	IPOD_DR_SETSTATEINFO_PARAM_DATA m_data;
	RestoreOnExit m_RestoreOpt;
}IPOD_DR_SETSTATEINFO_PARAM, *pIPOD_DR_SETSTATEINFO_PARAM;


typedef struct{
	IPOD_DR_PLAY_STATUS m_Status;
	unsigned long m_TrackIndex;
	unsigned long m_TrackTotalLen_ms;
	unsigned long m_TrackPos_ms;
}IPOD_DR_PLAYSTATUS, *pIPOD_DR_PLAYSTATUS;

typedef enum{
	IPOD_DR_TRACK_INFO_CAPS = 0x00U,
	IPOD_DR_TRACK_INFO_CHAPTER_TIMENAME = 0x01U,
	IPOD_DR_TRACK_INFO_ARTIST_NAME = 0x02U,
	IPOD_DR_TRACK_INFO_ALBUM_NAME = 0x03U,
	IPOD_DR_TRACK_INFO_GENRE_NAME = 0x04U,
	IPOD_DR_TRACK_INFO_TRACK_TITLE = 0x05U,
	IPOD_DR_TRACK_INFO_COMPOSER_NAME = 0x06U,
	IPOD_DR_TRACK_INFO_LYRICS = 0x07U,
	IPOD_DR_TRACK_INFO_ARTWORK_CNT = 0x08U,

	IPOD_DR_TRACK_INFO_MAX = 0x7FU
}IPOD_DR_TRACK_INFO_TYPE;


typedef struct{
	unsigned long m_TrackCaps;
	unsigned long m_TrackTotalLen_ms;
	unsigned short m_ChapterCnt;
}IPOD_DR_TRACK_CAP_INFO, *pIPOD_DR_TRACK_CAP_INFO;

typedef struct{
	unsigned long m_ChapterTime;
	unsigned char *m_ChapterName;
	unsigned long m_ChapterNameBufSize;
	unsigned long m_ChapterNameActualSize;
}IPOD_DR_TRACK_CHAPTER_INFO, *pIPOD_DR_TRACK_CHAPTER_INFO;

typedef struct{
	unsigned char *m_String;
	unsigned long m_StringBufSize;
	unsigned long m_StringActualSize;
}IPOD_DR_TRACK_STRING_DATA_INFO, *pIPOD_DR_TRACK_STRING_DATA_INFO;

typedef struct{
	unsigned char m_PacketInfo;
	unsigned char m_padding;
	unsigned short m_PacketIndex;
	unsigned char *m_Lyrics;
	unsigned long m_LyricsBufSize;
	unsigned long m_LyricsActualSize;
}IPOD_DR_TRACK_LYRICS, *pIPOD_DR_TRACK_LYRICS;

typedef struct{
	unsigned short m_FormatID;
	unsigned short m_ArtworkCnt;
}IPOD_DR_TRACK_ARTWORK_, *pIPOD_DR_TRACK_ARTWORK_;

typedef struct{
	unsigned long m_ActualCnt;
	IPOD_DR_TRACK_ARTWORK_ m_ArtworkCnt[IPOD_MAX_ARTWORK];
}IPOD_DR_TRACK_ARTWORK, *pIPOD_DR_TRACK_ARTWORK;

typedef union{
	IPOD_DR_TRACK_CAP_INFO m_capInfo;
	IPOD_DR_TRACK_CHAPTER_INFO m_ChapterInfo;
	IPOD_DR_TRACK_STRING_DATA_INFO m_StringInfo;
	IPOD_DR_TRACK_LYRICS m_lyrics;
	IPOD_DR_TRACK_ARTWORK m_Artwork;
}IPOD_DR_TRACK_INFO, *pIPOD_DR_TRACK_INFO;

typedef struct{
	IPOD_DR_TRACK_INFO_TYPE m_type;
	unsigned char m_padding_1;
	unsigned short m_ChapterIndex;
	unsigned long m_TrackIndex;
	IPOD_DR_TRACK_INFO m_TrackInfo;
}IPOD_DR_TRACK_INFO_PARAM, *pIPOD_DR_TRACK_INFO_PARAM;


typedef enum{
	IPOD_DR_EVT_SET_TRACK_TIME_POS_MS = (0x01<<0),
	IPOD_DR_EVT_SET_TRACK_PLAY_INDEX = (0x01<<1), 
	IPOD_DR_EVT_SET_CHAPTER_INDEX = (0x01<<2),
	IPOD_DR_EVT_SET_PLAY_STATUS = (0x01<<3),
	IPOD_DR_EVT_SET_MUTE_UI_VOL = (0x01<<4),
	IPOD_DR_EVT_SET_POWER_BAT = (0x01<<5),
	IPOD_DR_EVT_SET_EQ_SETTING = (0x01<<6),
	IPOD_DR_EVT_SET_SHUFFLE_SETTING = (0x01<<7),
	IPOD_DR_EVT_SET_REPEAT_SETTING = (0x01<<8),
	IPOD_DR_EVT_SET_DATE_TIME_SETTING = (0x01<<9),
	IPOD_DR_EVT_SET_ALARM_SETTING = (0x01<<10),
	IPOD_DR_EVT_SET_BACKLIGHT_STATE = (0x01<<11),
	IPOD_DR_EVT_SET_HOLD_SWITCH = (0x01<<12),
	IPOD_DR_EVT_SET_SOUND_CHECK = (0x01<<13),
	IPOD_DR_EVT_SET_AUDIO_BOOK_SPEED = (0x01<<14),
	IPOD_DR_EVT_SET_TRACK_POS_S = (0x01<<15),
	IPOD_DR_EVT_SET_MUTE_UI_ABSOLUTEVOL = (0x01<<16),
	IPOD_DR_EVT_SET_TRACK_CAPABILITIES = (0x01<<17),
	IPOD_DR_EVT_SET_PLAYBACK_ENGINE_CONTENTS_CHANGED = (0x01<<18),

	IPOD_DR_EVT_SET_MAX = 0x7FFFFFFF

}IPOD_REMOTE_EVENT_NOTI_SET;


typedef enum 
{
	PLAYPAUSE 		= 0x01U, //Toggle play/pause 1.00
	STOP			= 0x02U,
	NEXTTRACK		= 0x03U, //Deprecated; use Next(0x08) instead.
	PREVIOUSTRACK	= 0x04U, //Deprecated; use Previous(0x09) instead.
	STARTFF			= 0x05U, //1.00		
	STARTREW		= 0x06U, //1.00	
	ENDFFREW		= 0x07U, //1.00	
	NEXT			= 0x08U, //1.06
	PREVIOUS		= 0x09U, //1.06
	NEWPLAY			= 0x0AU, //1.13
	NEWPAUSE		= 0x0BU, //1.13
	NEXTCHAPTER		= 0x0CU, //Deprecated; use Next(0x08) instead.
	PREVIOUSCHAPTER	= 0x0DU,	  //Deprecated; use Previous(0x09) instead.
	RESUME_IPOD     = 0x0EU
}PlayCmdCode;



typedef enum 
{
	SHUFFLEOFF, 
	SHUFFLETRACKS,
	SHUFFLEALBUMS
}ShuffleMode;

typedef enum 
{
	REPEATOFF,
	REPEATONETRACK,
	REPEATALLTRACKS
}CurrentRepeatState;

typedef enum
{
	SORTBYGENRE = 0x00U,
	SORTBYARTIST = 0x01U,
	SORTBYCOMPOSER = 0x02U,
	SORTBYALBUM = 0x03U,
	SORTBYNAME = 0x04U,
	SORTBYPLAYLIST = 0x05U,
	SORTBYRELEASEDATE = 0x06U,
	SORTBYDEFAULT = 0xFFU
}SortOrder;

typedef enum
{
	MONOCHROME_2BPP = 0x01,
	RGB565_LITTLE_ENDIAN_16BPP,
	RGB565_BIG_ENDIAN_16BPP
//	MAX_PIXEL_FORMAT = 0x7F
}DisplayPixelFormat;

typedef enum
{
	IPOD_DISCONNECTED,
	IPOD_CONNECTED
}IPOD_PORT_STATE;

typedef enum
{
	// 2bits per pixel
	IPOD_PIXEL_MONOCHROME = 0x01U,

	// RGB 565 color little-endian, 16bpp
	IPOD_PIXEL_RGB_565_LITTLE = 0x02U,

	// RGB 565 color big-endian, 16bpp
	IPOD_PIXEL_RGB_565_BIG = 0x03U,

	IPOD_PIXEL_MAX = 0x7FFFFFFFU

}IPOD_PIXEL_FORMAT;

typedef enum 
{
	IPOD_ANALOG_AUDIO
	,IPOD_DIGITAL_AUDIO
}IPOD_INIT_TYPE;

//=========================
//buad rate 
//=========================
#define		IPOD_BAUD_9600		0x30
#define		IPOD_BAUD_19200		0x18
#define		IPOD_BAUD_38400		0x10
#define		IPOD_BAUD_57600		0x08

typedef enum
{
	DBSEL_AUDIO =  0x01
	,DBSEL_VIDEO = 0x02
}IPOD_SEL_DB_TYPE;

typedef enum
{
	IPOD_SIMPLE_NO_BUTTONS				= (0x00UL),
	IPOD_SIMPLE_PLAY_PAUSE 				= (0x01UL),
	IPOD_SIMPLE_VOLUME_UP 				= (0x02UL),
	IPOD_SIMPLE_VOLUME_DOWN 			= (0x04UL),
	IPOD_SIMPLE_NEXT_TRACK 				= (0x08UL),
	IPOD_SIMPLE_PREVIOUS_TRACK 			= (0x10UL),
	IPOD_SIMPLE_NEXT_ALBUM 				= (0x20UL),
	IPOD_SIMPLE_PREVIOUS_ALBUM 			= (0x40UL),
	IPOD_SIMPLE_STOP 						= (0x80UL),
	
	IPOD_SIMPLE_PLAY_RESUME 				= (0x01UL<<8),
	IPOD_SIMPLE_PAUSE 					= (0x02UL<<8),
	IPOD_SIMPLE_MUTE_TOGGLE 				= (0x04UL<<8),
	IPOD_SIMPLE_NEXT_CHAPTER 			= (0x08UL<<8),
	IPOD_SIMPLE_PREVIOUS_CHAPTER 		= (0x10UL<<8),
	IPOD_SIMPLE_NEXT_PLAYLIST 			= (0x20UL<<8),
	IPOD_SIMPLE_PREVIOUS_PLAYLIST 		= (0x40UL<<8),
	IPOD_SIMPLE_SHUFFLE_SETTING_ADV 	= (0x80UL<<8),
	
	IPOD_SIMPLE_REPEAT_SETTING_ADV 		= (0x01UL<<16),
	IPOD_SIMPLE_POWER_ON 				= (0x02UL<<16),
	IPOD_SIMPLE_POWER_OFF 				= (0x04UL<<16),
	IPOD_SIMPLE_BACKLIGHT_FOR_30SEC 	= (0x08UL<<16),
	IPOD_SIMPLE_BEGIN_FAST_FORWARD 		= (0x10UL<<16),
	IPOD_SIMPLE_BEGIN_REWIND 			= (0x20UL<<16),
	IPOD_SIMPLE_MENU 						= (0x40UL<<16),
	IPOD_SIMPLE_SELECT 					= (0x80UL<<16),
	
	IPOD_SIMPLE_UP_ARROW 				= (0x01UL<<24),
	IPOD_SIMPLE_DOWN_ARROW 				= (0x02UL<<24),
	IPOD_SIMPLE_BACKLIGHT_OFF 			= (0x04UL<<24)

}IPOD_SIMPLE_BUTTON_CTRL;

typedef enum
{
	IPOD_IMG_PLAY_PAUSE 				= (0x01UL),
	IPOD_IMG_NEXT_IMG 				= (0x02UL),
	IPOD_IMG_PREVIOUS_IMG 			= (0x04UL),
	IPOD_IMG_STOP		 				= (0x08UL),
	IPOD_IMG_PLAY_RESUME				= (0x10UL),
	IPOD_IMG_PAUSE 					= (0x20UL),
	IPOD_IMG_SHUFFLE_ADV 			= (0x40UL),
	IPOD_IMG_REPEAT_ADV				= (0x80UL)
}IPOD_IMG_BUTTON_CTRL;


typedef enum
{
	IPOD_VIDEO_PLAY_PAUSE 				= (0x01UL),
	IPOD_VIDEO_NEXT_VIDEO 				= (0x02UL),
	IPOD_VIDEO_PREVIOUS_VIDEO 			= (0x04UL),
	IPOD_VIDEO_STOP		 				= (0x08UL),
	IPOD_VIDEO_PLAY_RESUME				= (0x10UL),
	IPOD_VIDEO_PAUSE 						= (0x20UL),
	IPOD_VIDEO_BEGIN_FF 					= (0x40UL),
	IPOD_VIDEO_BEGIN_REW					= (0x80UL),
	
	IPOD_VIDEO_NEXT_CHAPTER 				= (0x01UL<<8),
	IPOD_VIDEO_PREVIOUS_CHAPTER 			= (0x02UL<<8),
	IPOD_VIDEO_NEXT_FRAME 				= (0x04UL<<8),
	IPOD_VIDEO_PREVIOUS_FRAME			= (0x08UL<<8)
	
}IPOD_VIDEO_BUTTON_CTRL;

typedef enum
{
	IPOD_AUDIO_PLAY_PAUSE 				= (0x01UL),
	IPOD_AUDIO_VOLUME_UP 				= (0x02UL),
	IPOD_AUDIO_VOLUME_DOWN 				= (0x04UL),
	IPOD_AUDIO_NEXT_TRACK 				= (0x08UL),
	IPOD_AUDIO_PREVIOUS_TRACK 			= (0x10UL),
	IPOD_AUDIO_NEXT_ALBUM 				= (0x20UL),
	IPOD_AUDIO_PREVIOUS_ALBUM 			= (0x40UL),
	IPOD_AUDIO_STOP 						= (0x80UL),
	
	IPOD_AUDIO_PLAY_RESUME 				= (0x01UL<<8),
	IPOD_AUDIO_PAUSE 						= (0x02UL<<8),
	IPOD_AUDIO_MUTE_TOGGLE 				= (0x04UL<<8),
	IPOD_AUDIO_NEXT_CHAPTER 				= (0x08UL<<8),
	IPOD_AUDIO_PREVIOUS_CHAPTER 		= (0x10UL<<8),
	IPOD_AUDIO_NEXT_PLAYLIST 			= (0x20UL<<8),
	IPOD_AUDIO_PREVIOUS_PLAYLIST 		= (0x40UL<<8),
	IPOD_AUDIO_SHUFFLE_SETTING_ADV 		= (0x80UL<<8),
	
	IPOD_AUDIO_REPEAT_SETTING_ADV 		= (0x01UL<<16),
	IPOD_AUDIO_BEGIN_FF 					= (0x02UL<<16),
	IPOD_AUDIO_BEGIN_REW 				= (0x04UL<<16),
	IPOD_AUDIO_RECORD 					= (0x08UL<<16)

}IPOD_AUDIO_BUTTON_CTRL;

typedef enum
{
	IPOD_NOTI_TYPE_FLOW_CONTROL 				= 0x02U,
	IPOD_NOTI_TYPE_RADIO_TAGGING 				= 0x03U,
	IPOD_NOTI_TYPE_CAMERA_NOTIFICATIONS 		= 0x04U,		
	IPOD_NOTI_TYPE_CHARGING_INFO				= 0x05U,
	IPOD_NOTI_TYPE_NOWPLAYINGAPPFOCUSCHANGE 	= 0x0AU,
	IPOD_NOTI_TYPE_SESSIONSPACEAVAILABLE		= 0x0BU,
	IPOD_NOTI_TYPE_DATABASE_AVAILABLE			= 0x0CU,
	IPOD_NOTI_TYPE_COMMAND_COMPLETE			= 0x0DU
}IPOD_NOTI_TYPE;

typedef enum
{
	IPOD_NOTI_TAGGING_OPERATION_SUCCESSFUL				= 0x01U,
	IPOD_NOTI_TAGGING_OPERATION_FAILED						= 0x02U,
	IPOD_NOTI_INFORMATION_AVAILABLE_FOR_TAGGING 			= 0x03U,		
	IPOD_NOTI_INFORMATION_NOT_AVAILABLE_FOR_TAGGING		= 0x04U
}IPOD_NOTI_TAG_STATUS;

typedef enum
{
	IPOD_NOTI_CAMERA_APP_OFF		= 0x01U,
	IPOD_NOTI_PREVIEW					= 0x03U,
	IPOD_NOTI_RECODING 				= 0x04U
}IPOD_NOTI_CAMERA_PAYLOAD;

typedef enum
{
	IPOD_NOTI_DATABASE_NOT_AVAILABLE		= 0x00U,
	IPOD_NOTI_DATABASE_AVAILABLE			= 0x01U
}IPOD_NOTI_DATABASE_AVAILABLE_STATUS;

typedef enum
{
	IPOD_NOTI_COMMAND_SUCCESSFUL			= 0x00U,
	IPOD_NOTI_COMMAND_FAILED				= 0x01U,
	IPOD_NOTI_COMMAND_CANCELLED			= 0x02U
}IPOD_NOTI_COMMAND_COMPLETION_STATUS;

typedef enum
{
	IPOD_NOTI_AVAILABLE_CURRENT			= 0x00U
}IPOD_NOTI_CHARGING_INFO_TYPE;

typedef enum
{
	IPOD_NOTI_AVAILABLE_CURRENT_VALUE		= 0x00U
}IPOD_NOTI_CHARGING_INFO_VALUE;

typedef enum
{
	IPOD_NOTI_BITMASK_RESERVED_BIT0							= (0x01U<<0),
	IPOD_NOTI_BITMASK_RESERVED_BIT1							= (0x01U<<1),
	IPOD_NOTI_BITMASK_FLOW_CONTROL							= (0x01U<<2),
	IPOD_NOTI_BITMASK_RADIO_TAGGING_STATUS					= (0x01U<<3),
	IPOD_NOTI_BITMASK_CAMERA_STATUS							= (0x01U<<4),
	IPOD_NOTI_BITMASK_CHARGING_INFO							= (0x01U<<5),
	IPOD_NOTI_BITMASK_RESERVED_BIT6							= (0x01U<<6),
	IPOD_NOTI_BITMASK_RESERVED_BIT7							= (0x01U<<7),
	IPOD_NOTI_BITMASK_RESERVED_BIT8							= (0x01U<<8),
	IPOD_NOTI_BITMASK_DATABASE_CHANGED							= (0x01U<<9),
	IPOD_NOTI_BITMASK_NOWPLAYINGFOCUSAPP_STATUS			= (0x01U<<10),
	IPOD_NOTI_BITMASK_SSESSIONSPACEAVAILABLE_STATUS		= (0x01U<<11),
	IPOD_NOTI_BITMASK_RESERVED_BIT12					= (0x01U<<12),
	IPOD_NOTI_BITMASK_COMMAND_COMPLETED					= (0x01U<<13),
	IPOD_NOTI_BITMASK_RESERVED_BIT14							= (0x01U<<14),
	IPOD_NOTI_BITMASK_STATUS_IPOD_OUT_MODE					= (0x01U<<15),
	IPOD_NOTI_BITMASK_RESERVED_BIT16						= (0x01U<<16),
	IPOD_NOTI_BITMASK_BT_CONNECTION_STATUS					= (0x01U<<17),
	IPOD_NOTI_BITMASK_RESERVED_BIT18						= (0x01U<<18),
	IPOD_NOTI_BITMASK_NOWPLAYINGAPPDISPLAYNAME_STATUS		= (0x01U<<19),
	IPOD_NOTI_BITMASK_ASSISTIVETOUCH_STATUS					= (0x01U<<20)
	
}IPOD_NOTI_BITMASK_STATUS;

/*************************************************************************/
/*Struct                                                                                                                    */
/*************************************************************************/
typedef struct tag_IPOD_Command
{
	/*
		Length of Data which is member of IPOD_Command structure.
	*/
	short Length;

	/*
		Lingo data from packet.
	*/
	char Lingo;

	/* byte align */
	char IsLargePacket;

	/*
		
	*/
	unsigned short CommandID;

	/*
		Transaction ID 
	*/
	unsigned short TransID;
	
	char *Data;
}IPOD_Command, *pIPOD_Command;


typedef struct tag_IPOD_CURIDX_FORMATINFO
{
	short FormatID[IPOD_MAX_ARTWORK];
	short CountOfImage[IPOD_MAX_ARTWORK];
}IPOD_CURIDX_FORMATINFO, pIPOD_CURIDX_FORMATINFO;


//Command:0x000D Return Information for Indexed Track : Track Information Structure
//Capability bit field : valid only Bit0 - Bit6
//Bit0 : 1 = Track is audiobook
//Bit1 : 1 = Track has chapters
//Bit2 : 1 = Track has album artwork
//Bit3 : 1 = Track has song lyrics
//Bit4 : 1 = Track is a podcast episode
//Bit5 : 1 = Track has release date
//Bit6 : 1 = Track has description
typedef struct
{
	/*response of CAPAINFO*/
	int Capability; //Track Capability bitfields
	int TotalLength; // Track total length in ms
	short ChapterCount;

	/*response of RELEASEDATE*/	
	char Seconds; // 0-59
	char Minutes; // 0- 59
	char Hours; // 0-23
	char Day; // 0- 31
	char Month; // 1-12
	char Weekday; //0-6
	short Year; // 1- xxxx
	
	/*response of ARTWORKCOUNT*/
	IPOD_CURIDX_FORMATINFO curformatInfo;

	/* 
		response of 
			PODCASTNAME,	DESCRIPTION,	SONGLYRICS
			GENRE,			COMPOSER
		Unicode
	*/
	char * InfoString;
}Info_Indexed_Track, *pInfo_Indexed_Track;

typedef struct
{
	short FormatID;
	DisplayPixelFormat PixelFormat;
	short ImageWidth;
	short ImageHeight;
}ArtworkFormat, *pArtworkFormat;

typedef struct
{
	char	cPixelFormat;
	short sWidth;
	short sHeight;
	short sTopLeftX;
	short sTopLeftY;
	short sBottomRightX;
	short sBottomRightY;
	unsigned int uiRowSize;
	unsigned int uiTotalSize;
	unsigned char* pImageData;
}ArtworkData, *pArtworkData;


typedef enum
{
	IPOD_VIDEO_OUT_SETTING = 0x00,
	IPOD_SCREEEN_CONFIGURATION = 0x01,
	IPOD_VIDEO_SIGINAL_FORMAT= 0x02,
	IPOD_LINE_OUT_USAGE = 0x03,
	IPOD_VIDEO_OUT_CONNECTION = 0x08,
	IPOD_CLOSED_CAPTIONING = 0x09,
	IPOD_VIDEO_MONITOR_ASPECT_RATIO = 0x0A,
	IPOD_SUBTITLES = 0x0C,
	IPOD_VIDEO_ALTERNATE_AUDIO_CHANNEL =0x0D
}IPOD_PREFERENCE_CLASSID;

enum
{
	IPOD_SETTING_OFF,
	IPOD_SETTING_ON
};

enum
{
	IPOD_VIDEO_FULLSCREEN,
	IPOD_VIDEO_FIT_TO_SCREEN
};

enum
{
	IPOD_VIDEO_NTSC,
	IPOD_VIDEO_PAL
};

enum
{	
	IPOD_VIDEO_OUT_NONE,
	IPOD_VIDEO_OUT_COMPOSITE,
	IPOD_VIDEO_OUT_SVIDEO,
	IPOD_VIDEO_OUT_COMPONENT
};

enum
{	
	IPOD_VIDEO_4BY3_RATIO,
	IPOD_VIDEO_16BY9_RATIO
};


// This power is from iPod
#define LOW_POWER_ONLY (0x00<<2)
#define INTERMITTENT_HIGH_POWER (0x01<<2)
#define CONSTANT_HIGH_POWER (0x03<<2)

#define NO_AUTHENTICATION 0x00
#define AUTHENTICATION_IMMEDIATELY 0x02

#define IPOD_MAX_LINGO_LEN 20

#define IPOD_FUNC_ENABLE 0x01
#define IPOD_FUNC_DISABLE 0x00

typedef struct tag_IPOD_IDENTIFY_TOKEN_VAL
{
	// Lingo setting //
	unsigned int LingoCnt;
	unsigned char Lingos[IPOD_MAX_LINGO_LEN];
	MLingoType ML_Lingo;
	unsigned int DeviceOption;

	/*
		If the the LINGO_EXTENDED_INTERFACE set on Lingos parameter, 
		Enter-extended-mode function called automatically.
		If user doesn't want to call the enter-extended-mode function,
		Please set the EnterExtendedModeOnInitFunc as "IPOD_FUNC_DISABLE"
	*/
	unsigned int EnterExtendedModeOnInit;
}IPOD_IDENTIFY_TOKEN_VAL, *pIPOD_IDENTIFY_TOKEN_VAL;


typedef unsigned long long		IPOD_ACCCAPS_TOCKEN_VAL;


#define IPOD_MAX_INFO_STR	64

/* TABLE 2-59 */
#define IPOD_ACCESSORY_CAP_INFO							(0x01<<0)
#define IPOD_ACCESSORY_NAME								(0x01<<1)
//#define IPOD_ACCESSORY_MIN_SUPPORT_IPOD_FIRMWARE_VER	(0x01<<2)
//#define IPOD_ACCESSORY_MIN_SUPPORT_LINGO_VER			(0x01<<3)
#define IPOD_ACCESSORY_FIRMWARE_VERSION					(0x01<<4)
#define IPOD_ACCESSORY_HARDWARE_VERSION					(0x01<<5)
#define IPOD_ACCESSORY_MANUFACTURER						(0x01<<6)
#define IPOD_ACCESSORY_MODEL_NUM							(0x01<<7)
#define IPOD_ACCESSORY_SERIAL_NUM						(0x01<<8)
#define IPOD_ACCESSORY_INCOMING_MAX_PAYLOAD_SIZE		(0x01<<9)

//#define IPOD_ACCESSORY_STATUS							(0x01<<11)
//#define IPOD_ACCESSORY_ASYNC_PLAYBACK_STATUS_CHANGE	(0x01<<18)

/* This is not defined on table 2-59. but It is used on Library definition*/
#define IPOD_ACCESSORY_RF_CERTIFICATIONS					(0x01<<20)


#define IPOD_RF_CERT_CLASS1	(0x01<<0)
#define IPOD_RF_CERT_CLASS2	(0x01<<1)
#define IPOD_RF_CERT_CLASS3	(0x01<<2) /*It is reserved - Do not use this one*/
#define IPOD_RF_CERT_CLASS4	(0x01<<3)



typedef struct tag_IPOD_ACCINFO_TOKEN_VAL
{
	unsigned int AccInfo;
	unsigned int AccInfoCnt;
	unsigned char Accessory_Name_Info[IPOD_MAX_INFO_STR];  /* UTF-8 String*/
	unsigned char Accessory_Firmware_Ver[3];
	unsigned char Padding_1;
	unsigned char Accessory_Hardware_Ver[3];
	unsigned char Padding_2;
	unsigned char Accessory_manufacturer[IPOD_MAX_INFO_STR];  /* UTF-8 String*/
	unsigned char Accessory_modelNum[IPOD_MAX_INFO_STR];  /* UTF-8 String*/
	unsigned char Accessory_serialNum[IPOD_MAX_INFO_STR];  /* UTF-8 String*/
	unsigned short Accessory_incommingMaximumPayloadSize;
	unsigned char Padding_3;
	unsigned char Padding_4;
	unsigned long Accessory_RF_Certifications;

}IPOD_ACCINFO_TOKEN_VAL, *pIPOD_ACCINFO_TOKEN_VAL;

typedef struct tag_IPOD_ACC_PREF_SETTING_FORMAT
{
	/*Please refer tothe */
	unsigned char m_ClassID;
	unsigned char m_SettingID;
	RestoreOnExit m_RestoreOnExit;
}IPOD_ACC_PREF_SETTING_FORMAT, *pIPOD_ACC_PREF_SETTING_FORMAT;


#define IPOD_PREF_MAX_CNT 0x0D
typedef struct tag_IPOD_ACCPREF_TOKEN_VAL
{
	unsigned int Total_PreferenceCnt;
	IPOD_ACC_PREF_SETTING_FORMAT Pref[IPOD_PREF_MAX_CNT];

}IPOD_ACCPREF_TOKEN_VAL, *pIPOD_ACCPREF_TOKEN_VAL;

typedef struct tag_IPOD_SDK_PROTOCOL_DATA
{
	unsigned char m_protocolIndex;
	unsigned char m_ProtocolStringSize;
	unsigned short m_padding_;
	unsigned char *m_pProtocolString;
}IPOD_SDK_PROTOCOL_DATA, *pIPOD_SDK_PROTOCOL_DATA;


#define IPOD_SDK_PROTOCOL_MAX_CNT 0x0D

typedef struct tag_IPOD_SDK_PROTOCOL_TOKEN
{
	unsigned int Total_ProtocolCnt;
	IPOD_SDK_PROTOCOL_DATA m_protocolTokenData[IPOD_SDK_PROTOCOL_MAX_CNT];

}IPOD_SDK_PROTOCOL_TOKEN, *pIPOD_SDK_PROTOCOL_TOKEN;

#define IPOD_BUNDLE_SEEDID_STRING_SIZE 11
typedef struct tag_IPOD_BUNDLE_SEED_ID_PREF_TOKEN
{
	unsigned char m_BundleSeedIDString[IPOD_BUNDLE_SEEDID_STRING_SIZE];

	/* If user want to add Bundle Seed ID string, Please set the m_BundleSeedIDIsExist as '1'*/
	unsigned char m_BundleSeedIDIsExist;
}IPOD_BUNDLE_SEED_ID_PREF_TOKEN, *pIPOD_BUNDLE_SEED_ID_PREF_TOKEN;

typedef enum
{
	IPOD_UART_CONNECT = 0x00000000,
	IPOD_USB_CONNECT = 0x00000001,

	IPOD_MAX_CONNECT = 0x7FFFFFFF
	
}IPOD_CONNECTION_TYPE;

typedef enum
{
	/* 
		In case of UART connection, 
		User can select the default connection as IDPS.
		To support IDPS, You need a authenticatin IC.
	*/
	IPOD_IDPS_NOT_SUPPORT = 0x00000000,

	/* 
		In case of USB connection, IDPS is default setting.
	*/
	IPOD_IDPS_SUPPORT = 0x00000001,

	IPOD_MAX_DEFAULT_CONNECTION = 0x7FFFFFFF

}IPOD_DEFAULT_CONNECTION;


/* Fot only WINCE */
typedef enum
{
	/*****************************************************/
	/* Extended Remote Events                                                    */
	/*****************************************************/

	/*
		param1 : None
	*/
	IPOD_APP_EVT_STOPPED = 0x00000000,

	/*
		param1 : (int)new_index 
	*/
	IPOD_APP_EVT_TRACKCHANGED = 0x00000001,

	/*
		param1 : None
	*/
	IPOD_APP_EVT_FFSEEKSTOP = 0x00000002,

	/*
		param1 : None
	*/
	IPOD_APP_EVT_REWSEEKSTOP = 0x00000003,

	/*
		param1 : (int)track_position
		PlayTime = (unsigned int)(track_position/1000);	
	*/
	IPOD_APP_EVT_TRACKPOSITION = 0x00000004,

	/*
		AUDIO CLASS EVENT
		param1 : (int)bitrate
	*/
	IPOD_APP_EVT_CHANGE_SAMPLEFREQ = 0x00000005,


	/*
		This event will be occur after IPOD_AskFileName() or IPOD_GetMediaKindName() function.
		param1 : buffer pointer
		param2 : size 
	*/
	IPOD_APP_EVT_CATEGORIZED_DATABASE_RECORD = 0x00000006,

	/*****************************************************/
	/* Display Remote Events                                                       */
	/*****************************************************/

	/*
		param1 : (int)track_position (ms)
		PlayTime = (unsigned int)(track_position/1000);	
	*/
	IPOD_APP_DR_EVT_TRACK_POSITION = 0x00000007,
	
	/*
		param1 : (int)current index
	*/
	IPOD_APP_DR_EVT_TRACK_INDEX = 0x00000008,

	/*
		param1 : (int)current index
		param2 : (int)chapter index
	*/
	IPOD_APP_DR_EVT_CHAPTER_INFO = 0x00000009,

	/*
		param1 : (int)Play status
	*/
	IPOD_APP_DR_EVT_PLAY_STATUS = 0x0000000A,
	
	/*
		param1 : (int)MuteState
		param2 : (int)UIvolLevel
	*/
	IPOD_APP_DR_EVT_MUTE_UI_VOL = 0x0000000B,
	
	/*
		param1 : (int)PowerStatus
		param2 : (int)BatteryLevel
	*/
	IPOD_APP_DR_EVT_POWER_BATTERY = 0x0000000C,

	/*
		param1 : (int)EqStatus
	*/
	IPOD_APP_DR_EVT_EQALIZER_STATE = 0x0000000D,

	/*
		param1 : (int)ShuffleStatus
	*/
	IPOD_APP_DR_EVT_SHUFFLE = 0x0000000E,

	/*
		param1 : (int)RepeatStatus
	*/
	IPOD_APP_DR_EVT_REPEAT = 0x0000000F,

	/*
		param1 : (int)Hour
		param2 : (int)Minute
	*/
	IPOD_APP_DR_EVT_DATE_TIME = 0x00000010,

	/*
		param1 : (int)AlarmStatus
		param2 : (int) Hour(0x0000FF00) + Min(0x000000FF)
	*/
	IPOD_APP_DR_EVT_ALARM = 0x00000011,

	/*
		param1 : (int)BackLight
	*/
	IPOD_APP_DR_EVT_BACKLIGHT = 0x00000012,

	/*
		param1 : (int)Holdswitch
	*/
	IPOD_APP_DR_EVT_HOLD_SWITCH = 0x00000013,

	/*
		param1 : (int)SoundCheck
	*/
	IPOD_APP_DR_EVT_SOUND_CHECK = 0x00000014,

	/*
		param1 : (int)AudioBook
	*/
	IPOD_APP_DR_EVT_AUDIOBOOK = 0x00000015,

	/*
		param1 : (int)TimePosition (sec)
	*/
	IPOD_APP_DR_EVT_TRACK_POSITION_IN_SECONDS = 0x00000016,

	/*
		param1 : (int)MuteState
		param2 : (int) UIVolume(0x0000FF00) + AbsoluteVolume(0x000000FF)
	*/
	IPOD_APP_DR_EVT_MUTE_UI_ABSOLUTE_VOL = 0x00000017,
	/*
	    param1 : (int) Track capabilities bits
	*/
    IPOD_APP_DR_EVT_TRACK_CAPABILITIES = 0x00000018,
    /*
        param1 : (int) number of tracks in new playlist.
    */
    IPOD_APP_DR_EVT_PLAYBACK_ENGINE_CONTENTS_CHANGED = 0x00000019,


	IPOD_APP_DR_EVT_MAX= 0x7FFFFFFF
}IPOD_EVENT_ID;


typedef struct tag_IPOD_BUFF_VAL
{
	unsigned char *CP_buffer;
	unsigned long CP_buffer_size;
	
	unsigned char *Tx_buffer;
	unsigned long Tx_buffer_size;
	
	unsigned char *Rx_buffer;
	unsigned long Rx_buffer_size;
	
	unsigned char *RxData_buffer;
	unsigned long RxData_buffer_size;

	unsigned char *UTF8DecodeBuffer;
	unsigned long UTF8DecodeBuffer_size;

}IPOD_BUF_PARAM, *pIPOD_BUF_PARAM;

typedef struct tag_IPOD_DEV_HANDLE_DES
{
	void *HID;
	void *I2C;
	unsigned long I2C_channelNum;
	unsigned long I2C_SlaveAddr;
}IPOD_DEV_HANDLE_DES, *pIPOD_DEV_HANDLE_DES;

typedef struct tag_IPOD_INIT_CHANNEL_PARAM
{
	unsigned long ExtInfo;
	IPOD_BUF_PARAM buff;
	IPOD_CONNECTION_TYPE ConnectionType; 
	IPOD_DEFAULT_CONNECTION IDPS_support;

	/*It is used for WINCE now.--> */
	unsigned long EventThreadID;
	IPOD_DEV_HANDLE_DES DevHandleDes;
	void *iPod_Handle;
	/* <-- For WINCE */
}IPOD_INIT_CHANNRL_PARAM, *pIPOD_INIT_CHANNRL_PARAM;

typedef struct tag_IPOD_INIT_PARAM
{
//-	unsigned long ExtInfo;
//-	IPOD_BUF_PARAM buff;
//-	IPOD_CONNECTION_TYPE ConnectionType; 
//-	IPOD_DEFAULT_CONNECTION IDPS_support;
	
	IPOD_IDENTIFY_TOKEN_VAL IdentifyToken;
	IPOD_ACCCAPS_TOCKEN_VAL AccesoryCapToken;
	pIPOD_ACCINFO_TOKEN_VAL pAccInfoToken;
	IPOD_ACCPREF_TOKEN_VAL AccPrefToken;
	IPOD_SDK_PROTOCOL_TOKEN m_SDKProtocolToken;
	IPOD_BUNDLE_SEED_ID_PREF_TOKEN m_BundleSeedIDPrefToken;

	/*It is used for WINCE now.--> */
//-	unsigned long EventThreadID;
//-	IPOD_DEV_HANDLE_DES DevHandleDes;
	/* <-- For WINCE */

}IPOD_INIT_PARAM, *pIPOD_INIT_PARAM;

typedef struct tag_IPOD_LINGO_VER
{
	unsigned long Major;
	unsigned long Minor;

}IPOD_LINGO_VER, *pIPOD_LINGO_VER;

typedef union tag_IPOD_LINGO_INFO
{
	unsigned long long LingoOption[LINGO_MAX];
	IPOD_LINGO_VER LingoVer[LINGO_MAX];
}IPOD_LINGO_INFO, *pIPOD_LINGO_INFO;


typedef struct tag_IPOD_LINGO_INFO_DATA
{
	/*
		If the m_IsVersion is set as '1', Please access m_LingoInfo.LingoVer.
		If the m_IsVersion is set as '0', Please access m_LingoInfo.LingoOption.
	*/
	unsigned int m_IsVerison;
	IPOD_LINGO_INFO m_LingoInfo;
	IPOD_ERROR m_Lingo_result[LINGO_MAX];
}IPOD_LINGO_INFO_DATA, *pIPOD_LINGO_INFO_DATA;


#define INTERNAL_EX_FLAG 0x01
#define TRANSID_IGNOR_EX_FLAG 0x02

#define IPOD_SEND_ORG 0x00
#define IPOD_SEND_ADD_HEADER 0x01
#define IPOD_SEND_SKIP 0x02

#define IPOD_TIMEOUT_FLAG_USE_ORIGINAL_TIMEOUT_VAL 0x01

typedef struct tag_IPOD_cmd_param
{
	void *m_iPod_Handle;
	unsigned short m_TransID;

	/* IPOD_FLAG - USER setting */
	unsigned char m_Flag;

	/* Internal Ex_flag */
	unsigned char m_Ex_Flag;

	unsigned long m_CurCmd;

	unsigned long m_SendFunc;

	unsigned long m_TimeOutFlag;
	unsigned long m_TimeOut;

	unsigned char *m_SendCmdBuf;
	unsigned long m_SendCmdBufSize;

	unsigned long m_ExecutionTime;

	unsigned char *m_ResponseBuf;
	unsigned long m_ResponseBufSize;	

}IPOD_CMD_PARAM, *pIPOD_CMD_PARAM;

#define IPOD_RECORD_SIZE_MAX 500


typedef struct
{
	long DBindex;
	long ActualLen;
	unsigned char Data[IPOD_RECORD_SIZE_MAX];

}IPOD_RECORD_TYPE, *PIPOD_RECORD_TYPE;

typedef enum
{
	
	IPOD_DATA_SINGLE_SESSION,
	
	IPOD_DATA_MULTI_SESSION,
	IPOD_DATA_MULTI_SESSION_END,

	IPOD_MULTI_RESPONSE,
	IPOD_MULTI_RESPONSE_END,

	IPOD_DATA_IDLE

}IPOD_DATA_STATUS;

typedef enum
{
	IPOD_AUTH_ING,
	IPOD_AUTH_FINISHED
}IPOD_AUTH_STATUS, *pIPOD_AUTH_STATUS;

typedef enum
{
	ONCE_EXECUTED_IDENTIFYDEVICELINGOES,
	TWICE_EXECUTED_IDENTIFYDEVICELINGOES	
}IPOD_IDENTIFYDEVICELINGOES_STATUS;

#define MAX_RETRY_DATA_TRANSFER_COUNT (10)

typedef enum
{
    IPOD_DATATRANSFER_NORMAL,
    IPOD_DATATRANSFER_TIMEOUT
}IPOD_DATATRANSFER_TYPE;


/*************************************************************************/
/* Functions                                                                                  				*/
/*************************************************************************/

/**************************************************************************
*	Function : IPOD_Init
*
*	Description : This function returns  the iPod handle
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_Open(unsigned long *iPod_Handle);

/**************************************************************************
*	Function : IPOD_Init
*
*	Description : This function initialize the iPod 
*			Please refer to the USBH_API_IPOD_InitParam() function to fill the pParam parameter.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle
*		- pParam : pIPOD_INIT_PARAM structure
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_Init(void *iPod_Handle, pIPOD_INIT_PARAM pParam);

/**************************************************************************
*	Function : IPOD_Close
*
*	Description : This function deinitialized the iPod
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_Close(void *iPod_Handle);

#ifdef WINCE
/**************************************************************************
*	Function : IPOD_Reset
*
*	Description : This function reset the iPod when the init function is failed.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_Reset(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_CheckiPodTaskStatus
*
*	Description : This function check the iPod thread status.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_CheckiPodTaskStatus(void *iPod_Handle);
/**************************************************************************
*	Function : IPOD_CheckiPodTaskStatus
*
*	Description : This function set the iPod IDPS status.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetStartIDPSStatus(void *iPod_Handle);

#endif 

/**************************************************************************
*	Function : IPOD_GetStatus
*
*	Description : This funtion returns device status
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- length : total time value
*		- Curtime : time value (milli-seconds)
*		- PlayStatus : 0 = stop, 1 = playing, 2 = paused / {PlayStatus}
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*  	
**************************************************************************/
extern IPOD_ERROR IPOD_GetStatus(void *iPod_Handle, int *TotalTracklength, int *Curtime_ms, int *PlayStatus);

/**************************************************************************
*	Function : IPOD_ButtonControl
*
*	Description : This funtion set the iPod status ( play / pluse )
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- PlayCmdCode : command {STOP | PLAYPAUSE | ...}
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_ButtonControl(void *iPod_Handle, PlayCmdCode cmdcode);

/**************************************************************************
*	Function : IPOD_GetTitle
*
*	Description : This funtion returns title string of current filelist index.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : file index
*		- pTitle : title string pointer
*		- BufLen : buffer length
*		- ActualLen : string actual length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetTitle(void *iPod_Handle, int index, unsigned char *pTitle, long BufLen, long *ActualLen);

/**************************************************************************
*	Function : IPOD_GetArtist
*
*	Description : This funtion returns Artist string of current filelist index.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : file index
*		- pArtist : artist string pointer
*		- BufLen : buffer length
*		- ActualLen : string actual length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetArtist(void *iPod_Handle, int index, unsigned char *pArtist, long BufLen, long *ActualLen);

/**************************************************************************
*	Function : IPOD_GetAlbum
*
*	Description : This funtion returns Album string of current filelist index.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : file index
*		- pAlbum : title string pointer
*		- BufLen : buffer length
*		- ActualLen : string actual length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetAlbum(void *iPod_Handle, int index, unsigned char *pAlbum, long BufLen, long *ActualLen);

/**************************************************************************
*	Function : IPOD_GetCurrentFileNum
*
*	Description : This funtion returns current playing file index
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : file index
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
**************************************************************************/
extern IPOD_ERROR IPOD_GetCurrentFileNum(void *iPod_Handle, long *Index);

/**************************************************************************
*	Function : IPOD_ResetDB
*
*	Description : This funtion reset the iPod DB
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
**************************************************************************/
extern IPOD_ERROR IPOD_ResetDB(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_SelectList
*
*	Description : This funtion select the File list as category type
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Type : category type
*		- index : DB index(0, 1, 2, ...)
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SelectList(void *iPod_Handle, CategoryType type, int index);

/**************************************************************************
*	Function : IPOD_SelectListType
*
*	Description : This funtion select the File list as category type
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Type : category type
*		- TotalListNum : Total list Number
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SelectListType(void *iPod_Handle, CategoryType type, long *TotalListNum);

#ifdef WINCE

/**************************************************************************
*	Function : IPOD_AskFileName
*
*	Description : This funtion request titles list from List (index) to List (index+num) of specific category.
*							
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- type : Category Type
*  		- index : Start Index
*  		- num : num
*		- RecordBuf :  record data
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*	
**************************************************************************/
IPOD_ERROR IPOD_AskFileName(void *iPod_Handle, CategoryType type, int index, int num, IPOD_RECORD_TYPE *RecordBuf);

#else /*WINCE*/

/**************************************************************************
*	Function : IPOD_AskFileName
*
*	Description : This funtion request titles list from List (index) to List (index+num) of specific category.
*							
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- type : Category Type
*  		- index : Start Index
*  		- num : num
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*	
**************************************************************************/
extern IPOD_ERROR IPOD_AskFileName(void *iPod_Handle, CategoryType type, int index, int num);

/**************************************************************************
*	Function : IPOD_GetFileName
*
*	Description : This function returns DB records requested by iPOD_AskFileName() function.
*				You need to call this function within the request count of IPOD_AskFileName() function.
*							
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- pIndex : current index
*  		- BuffLen : buffer length
*  		- pData : buffer pointer.
*		- pActualLen : string actual length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*	
**************************************************************************/
extern IPOD_ERROR IPOD_GetFileName(void *iPod_Handle, long *pIndex, long BuffLen , unsigned char *pData, long *pActualLen);

#endif /*WINCE*/

/**************************************************************************
*	Function : IPOD_Set_Enable_event
*
*	Description : This function enables the iPod event ( Track Info )
*							
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- setting : SetPlayStatusNotification combination
*		- Extended : 0: 4 byte setting / 1: 7Byte setting 
*					Please refer to the APPLE specification.
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_Enable_event(void *iPod_Handle, unsigned int setting, unsigned int Extended);

/**************************************************************************
*	Function : IPOD_GetNumPlayingTracks
*
*	Description : This funtion returns total track number
*
*	Parameter :  
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- TotalTrackNum : Total track number
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetNumPlayingTracks(void *iPod_Handle, long *TotalTrackNum);

/**************************************************************************
*	Function : IPOD_SetCurrentPlayingTrack
*
*	Description : This function sets the index of the track that needs to be played in the now playing playlist on the IPOD.
*				
*	Parameter :  
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : index of DB list
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetCurrentPlayingTrack(void *iPod_Handle, int index);

/**************************************************************************
*	Function : IPOD_SelectSortList
*
*	Description : This function selects on or more records in the IPOD database bsaed on a category relativeindex
*				If the type is track, it will play.
*				Please use this function after IPOD_SelectListType() function.
*							
*	Parameter :  
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
* 		- type : Category Type
*  		- index : DB index(0, 1, 2, ...)
*  		- sort :SortOrder
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SelectSortList(void *iPod_Handle, CategoryType type, int index, SortOrder sort);

/**************************************************************************
*	Function : IPOD_PlayCurrentSelection
*
*	Description : This function selects and play a record in the IPOD database bsaed on a category relativeindex
*							
*	Parameter :  
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- index : DB index(0, 1, 2, ...)
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_PlayCurrentSelection(void *iPod_Handle, int index);

/**************************************************************************
*	Function : IPOD_GetAlbumArtFormats
*
*	Description : This function returns album art formats
*							
*	Parameter :  
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- pArtworkFormat : albumart attribute
*  		- FormatCnt : Format count
*  		- AcutalFormatCnt : copied format count
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetAlbumArtFormats(void *iPod_Handle, pArtworkFormat pArtFormatData, long FormatCnt, long *AcutalFormatCnt);

/**************************************************************************
*	Function : IPOD_GetAlbumArt
*
*	Description : This funtion returns albumart data (user can choose the data format)
*
*			This function call the IPOD_GetDefaultArtworkFormatID() function to get the basic format to display.
*
*			If user doesn't set the basic format, It will returns
*			IPDO_INVALID_BASIC_FORMATID error
*
*			IPOD_SetDefaultArtworkFormatID() will set the default format ID.
*			The basic format ID is depend on the iPod RX buffer size and artwork display limit size. 
*			( the artwork maximum data size is limited as iPod RX buffer size about 60Kbyte in iPod library)
*
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- index : num of current playing track
*  		- pData : ArtworkData
*		- BufLen : artwork data buffer size 
*		- pActualLen : Actual artwork data size
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetAlbumArt(void *iPod_Handle, unsigned long index, pArtworkData pData,  unsigned long BufLen, unsigned long *pActualLen);

/**************************************************************************
*	Function : IPOD_SetShuffle
*
*	Description : This function set  the shuffle Mode
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- ShuffleMode : shuffleMode
*		- RestoreOn : 
*			UPDATE_NEW_SETTING :  the new setting persists after accessory detach
*			RESTORE_ORG_SETTING : the original setting is restored on detach
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetShuffle(void *iPod_Handle, ShuffleMode mode, RestoreOnExit RestoreOn);

/**************************************************************************
*	Function : IPOD_GetShuffle
*
*	Description : This function get  the shuffle Mode
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- ShuffleMode : shuffleMode
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetShuffle(void *iPod_Handle, ShuffleMode *mode);

/**************************************************************************
*	Function : IPOD_SetRepeat
*
*	Description : This function set  the repeat Mode
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- CurrentRepeatState : repeat mode
*		- RestoreOn : 
*			UPDATE_NEW_SETTING :  the new setting persists after accessory detach
*			RESTORE_ORG_SETTING : the original setting is restored on detach
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetRepeat(void *iPod_Handle, CurrentRepeatState mode, RestoreOnExit RestoreOn);

/**************************************************************************
*	Function :  IPOD_GetRepeat
*
*	Description : This function get  the repeat Mode
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- CurrentRepeatState : repeat mode
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetRepeat(void *iPod_Handle, CurrentRepeatState *mode);

/**************************************************************************
*	Function : IPOD_GetMonoDisplayImageLimits
*
*	Description : This function returns image limit information of iPod
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- format :  IPOD_PIXEL_FORMAT
*		- height : heigth size of image limit
*		- width : width size of image limit
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetMonoDisplayImageLimits(void *iPod_Handle, IPOD_PIXEL_FORMAT * format, int * width, int * height);

/**************************************************************************
*	Function : IPOD_SetBitmap
*	
*	Description : This function send the bitmap data to iPod
*			(*) If you use the return vale (height, width info) of 
*			IPOD_GetMonoDisplayImageLimits() or IPOD_GetColorDisplayLimit() function,
*			It happens error.
*			Please use lower width value than the height or equal data
*
* 	Parameter
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*  		- format, width, heght :
*  		- buffer : image buffer
*  		
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
*
*	[Image format information]
*
*	1. Image Map
*	
*		0,0			1,0			2,0			3,0			4,0			5,0			...	Column max,0
*		0,1			1,1			2,1			3,1			4,1			5,1			...	Column max,1
*		0,2			1,2			2,2			3,2			4,2			5,2			...	Column max,2
*		0,3			1,3			2,3			3,3			4,3			5,3			...	Column max,3
*		...			...			...			...			...			...			...	...
*		0,Row max	1,Row max	2,Row max	3,Row max	4,Row max	5,Row max	...	Column max,Row max
*
*	2. Image Format
*	
*		|Image Data Byte 0x0000											|
*		|	Pixel 0		|	Pixel 1		|	Pixel 2		|	Pixel 3		|
*		|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
*
*		|Image Data Byte 0x0001											|
*		|	Pixel 4		|	Pixel 5		|	Pixel 6		|	Pixel 7		|
*		|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
*
*		|Image Data Byte 0x0002											|
*		|	Pixel 8		|	Pixel 9		|	Pixel 10		|	Pixel 11		|
*		|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
*
*		|Image Data Byte 0x0003											|
*		|	Pixel 12		|	Pixel 13		|	Pixel 14		|	Pixel 15		|
*		|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
*
*		|Image Data Byte 0xNNNN											|
*		|	Pixel N		|	Pixel N+1		|	Pixel N+2		|	Pixel N+3		|
*		|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
*
*	3. Display Pixel Format Codes
*	
*		Monochrome, 2 bits/pixel : 0x01
*
*	4. 2bpp Monochrome Pixel Intensities
*	
*		Pixel off (not visible) 		: 00b
*		Pixel on 25% (light grey) 	: 01b
*		Pixel on 50% (dark grey) 	: 10b
*		Pixel on 100% (black) 		: 11b
*		
*	5, Parameter
*	
*		Width : The number of pixels per row from left to right
*		Height : The number of rows, from top to bottom, in the image
*		Row Size : The number of bytes representing one row of pixels. Each row is zero padded to end on a 32-bit boundary.
*		                The cumulative size(in Bytes) of the Image Data transferred across all telegrams in this transaction is effectively,
*		                Row Size * Image Height.
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetBitmap(void *iPod_Handle, IPOD_PIXEL_FORMAT format, int width, int height, unsigned char * buffer);

/**************************************************************************
*	Function : IPOD_GetColorDisplayLimit
*
*	Description : This function returns color display limit
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- format : IPOD_PIXEL_FORMAT
*  		- int *width, int *height
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetColorDisplayLimit(void *iPod_Handle, IPOD_PIXEL_FORMAT *format, int *width, int *height);

/**************************************************************************
*	Function : IPOD_GetIPODName
*
*	Description : This funtion returns iPod name 
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- iPodNameStr : iPod name buffer pointer.
*		- Buffer Length : buffer size
*		- ActualLen : Actual data Length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetIPODName(void *iPod_Handle, unsigned char *iPodNameStr, long BufLen, long *ActualLen);

/**************************************************************************
*	Function : IPOD_GetIPODName
*
*	Description : This funtion returns iPod version information 
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- major, minor, revision (1 byte size data)
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetIPODSoftwareVersion(void *iPod_Handle, char *major,  char *minor,  char *revision);

/**************************************************************************
*	Function : IPOD_GetIPODSerialNum
*
*	Description : This funtion returns iPod serial number
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- SerialStr : serial strings
*		- Buffer Length : serial strings buffers length.
*		- ActualLen : Actual data Length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetIPODSerialNum(void *iPod_Handle, unsigned char *SerialStr, long BufLen, long *ActualLen);

/**************************************************************************
*	Function : IPOD_GetIPODModelNum
*
*	Description : This funtion returns iPod model Num and Model string
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- model_num : model Num 
*		- ModelStr : model string 
*		- BufLen : Buffer Length
*		- ActualLen : Actual data length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetIPODModelNum(void *iPod_Handle, int *model_num, unsigned char *ModelStr, long BufLen, long *ActualLen);

/**************************************************************************
*	Function : IPOD_RequestProtocolVersion
*
*	Description : This funtion returns iPod protocol version
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- major
*		- minor
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_RequestProtocolVersion(void *iPod_Handle, int *major, int *minor);


// For iPod video borwsing control //
/**************************************************************************
*	Function : IPOD_SelectDBHierarchy
*
*	Description : A hierarchy selection value of 0x01 means that the accessory wants to navigate
*				the audio hierarchy.
*			A hierarchy selection value of 0x02 means that the accessory want to navigate
*				the video hierarchy.
*				
*	Parameter :
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- IPOD_SEL_DB_TYPE {  DBSEL_AUDIO =  0x01, DBSEL_VIDEO = 0x02 }
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SelectDBHierarchy(void *iPod_Handle, IPOD_SEL_DB_TYPE DB_type);

// For iPod video borwsing control //
/**************************************************************************
*	Function : IPOD_GetVideoMediaKindCnt
*
*	Description : This funtion returns categorized database record count.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- pMedia_kind_record_cnt : media kind record count
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetVideoMediaKindCnt(void *iPod_Handle, long *pMedia_kind_record_cnt);

// For iPod video borwsing control //
/**************************************************************************
*	Function : IPOD_GetVideoMediaKindname 
*
*		
*    **********    defeated    ************
*
**************************************************************************/
//extern IPOD_ERROR IPOD_GetVideoMediaKindname(void *iPod_Handle, long Media_kind_record_cnt, unsigned char *buf, int size);

// For iPod video borwsing control //
/**************************************************************************
*	Function : IPOD_SelectVedeoDBRecord
*
*	Description : This funtion select the categorized database record.
*				(ex. Movies, TV shows, video Podcasts, Music Videos.)
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Total_Media_kind_record_cnt : total Media kind record count
*		- index : index of media kind
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SelectVedeoDBRecord(void *iPod_Handle, long Total_Media_kind_record_cnt, int index);

/**************************************************************************
*	Function : IPOD_ExitRemoteUIMode
*
*	Description : This function exit the remote UI mode.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_ExitRemoteUIMode(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_GetiPodOption
*
*	Description : This function returns the iPod option
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- *option : Option data
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetiPodOption(void *iPod_Handle, unsigned char *Option);

/**************************************************************************
*	Function : IPOD_GetiPodPreference
*
*	Description : This function returns the iPod preference
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- ClassID : reference classID
*		- *SettingID : setting ID
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetiPodPreference(void *iPod_Handle, IPOD_PREFERENCE_CLASSID ClassID, unsigned char *settingID);

/**************************************************************************
*	Function : IPOD_SetiPodPreferences
*
*	Description : This function set the reference class setting ID
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- ClassID : reference classID
*		- SettingID : setting ID
*		- RestoreOn : 
*			UPDATE_NEW_SETTING :  the new setting persists after accessory detach
*			RESTORE_ORG_SETTING : the original setting is restored on detach
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetiPodPreferences(void *iPod_Handle, IPOD_PREFERENCE_CLASSID ClassID, unsigned char settingID, RestoreOnExit RestoreOn);

/**************************************************************************
*	Function : IPOD_ProcessiPodEvent
*
*	Description : This function process the iPod event
*				This function just used on nucleus OS version ( TCC860x, TCC830x, TCC800x)
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_ProcessiPodEvent(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_Check_iPod_status
*
*	Description : This function check iPod status
*				This function just used on nucleus OS version ( TCC860x, TCC830x, TCC800x)
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_Check_iPod_status(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_GetCurentPlayingTrackChapterInfo
*
*	Description : This function returns current playing track chapter information
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- *chapterIndex : chapter index
*		- *chapterCount : chapter count
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetCurentPlayingTrackChapterInfo(void *iPod_Handle, int *chapterIndex, int * chapterCount);

/**************************************************************************
*	Function : IPOD_SetCurrentPlayingTrackChapter
*
*	Description : This function sets the chapter index of the currently playing track.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : index
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetCurrentPlayingTrackChapter(void *iPod_Handle, unsigned long index);

/**************************************************************************
*	Function : IPOD_GetCurrentPlayingTrackChapterPlayStatus
*
*	Description : This function returns current playing track chapter play status.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : index
*		- ChapterLen : chapter length (ms)
*		- ElapsedTime : Elapsed time in chapter (ms)
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetCurrentPlayingTrackChapterPlayStatus(void *iPod_Handle, unsigned long Chapter_index, unsigned long *ChapterLen, unsigned long *ElapsedTime);

/**************************************************************************
*	Function : IPOD_GetCurrentPlayingTrackChapterName
*
*	Description : This function returns current playing track chapter name.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : index
*		- pChapterName : chapter name buffer pointer
*		- BufLen : name buffer size
*		- pActualLen : actual data Length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetCurrentPlayingTrackChapterName(void *iPod_Handle, unsigned long index, unsigned char *pChapterName, unsigned long BufLen, unsigned long *pActualLen);

/**************************************************************************
*	Function : IPOD_GetAudioBookSpeed
*
*	Description : This function returns audio book speed
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- speed : audio book speed
*				0xFF : slower, 0x00 : normal, 0x01 : faster, 0x02 -0xFE :reserved
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetAudioBookSpeed(void *iPod_Handle,  unsigned char * speed);

/**************************************************************************
*	Function : IPOD_SetAudioBookSpeed
*
*	Description : This function set the audio book speed
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- speed : AudiobookSpeed
*				0xFF : slower, 0x00 : normal, 0x01 : faster, 0x02 -0xFE :reserved
*		- GlobalSetting : 
*				0x00: set the speed of the current playing audiobllo 
*				0x01: set the global audiobook speed.
*		- RestoreOnExit : Restore on exit
*				0x01: the original setting is restored on detach
*				0x00 : the new setting persists after accessory detach.
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SetAudioBookSpeed(void *iPod_Handle, AudiobookSpeed speed , unsigned char GlobalSetting, unsigned char RestoreOnExit);

/**************************************************************************
*	Function : IPOD_GetIndexedPlayingTrackInfo
*
*	Description : This function returns the indexed playing track information.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- type : TrackInformationType
*		- pTrackInfo : pInfo_Indexed_Track
*		- trackindex : track index
*		- chapterindex : chapter index
*		- BufLen : pTrackInfo->InfoString buffer length
*		- pActualLen : pTrackInfo->InfoString actual length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetIndexedPlayingTrackInfo(void *iPod_Handle, TrackInformationType type, pInfo_Indexed_Track pTrackInfo, unsigned long trackindex, unsigned long chapterindex, long BufLen, long *pActualLen);

/**************************************************************************
*	Function : IPOD_ContextButtonStatus
*
*	Description : (SIMPLE REMOTE) ButtonControl 
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- ButtonCtrl : Button control IPOD_SIMPLE_BUTTON_CTRL
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_ContextButtonStatus(void *iPod_Handle, IPOD_SIMPLE_BUTTON_CTRL ButtonCtrl);

/**************************************************************************
*	Function : IPOD_ImageButtonStatus
*
*	Description : (SIMPLE REMOTE) ButtonControl 
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- ButtonCtrl : Button control IPOD_IMG_BUTTON_CTRL
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_ImageButtonStatus(void *iPod_Handle, IPOD_IMG_BUTTON_CTRL ButtonCtrl);

/**************************************************************************
*	Function : IPOD_VideoButtonStatus
*
*	Description : (SIMPLE REMOTE) ButtonControl 
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- ButtonCtrl : Button control IPOD_VIDEO_BUTTON_CTRL
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_VideoButtonStatus(void *iPod_Handle, IPOD_VIDEO_BUTTON_CTRL ButtonCtrl);

/**************************************************************************
*	Function : IPOD_AudioButtonStatus
*
*	Description : (SIMPLE REMOTE) ButtonControl 
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- ButtonCtrl : Button control IPOD_AUDIO_BUTTON_CTRL
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_AudioButtonStatus(void *iPod_Handle, IPOD_AUDIO_BUTTON_CTRL ButtonCtrl);

/**************************************************************************
*	Function : IPOD_EnterRemoteUIMode
*
*	Description : This function make enter the Remote UI mode
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_EnterRemoteUIMode(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_GetProtocolVersion
*
*	Description : This function returns protocol version.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- lingo : lingo
*		- inform
*		- major : major version
*		- minor : minor version
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetProtocolVersion(void *iPod_Handle, int lingo, int *inform, int *major, int *minor);

/**************************************************************************
*	Function : IPOD_GetInitType
*
*	Description : It returns init type. (IPOD_INIT_TYPE)
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- type : IPOD_INIT_TYPE
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetInitType(void *iPod_Handle, IPOD_INIT_TYPE *type);


/* For User command */
/**************************************************************************
*	Function : IPOD_USER_CMD_RCVResponse
*
*	Description : This function receives the iPod response.
*				Please do not use this function. - it will be deleted.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Lingo : Lingo ID
*		- cmd : command ID
*		- Timeout : commmand Timeout value
*		- TransID : Transaction ID
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_USER_CMD_RcvResponse(void *iPod_Handle, unsigned short Lingo, unsigned short Snd_cmd, unsigned short Rcv_cmd, unsigned int TimeOut, unsigned short TransID);

/*For User command */
/**************************************************************************
*	Function : IPOD_USER_FUNC_SendCmd_RcvResponse
*
*	Description : This function send the iPod command and receives the iPod response.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Lingo : Lingo ID
*		- Rcv_cmd : return command ID
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_USER_FUNC_SendCmd_RcvResponse(pIPOD_CMD_PARAM pCmdParam, unsigned short Lingo, unsigned short Rcv_cmd);

/* For User command */
/**************************************************************************
*	Function : IPOD_USER_EnterCriticalSection
*
*	Description : This function enter the critical section for iPod communication.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
IPOD_ERROR IPOD_USER_EnterCriticalSection(void *iPod_Handle);

/* For User command */
/**************************************************************************
*	Function : IPOD_USER_ExitCriticalSection
*
*	Description : This function exit the critical section for iPod communication.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
IPOD_ERROR IPOD_USER_ExitCriticalSection(void *iPod_Handle);

/* For User command */
/**************************************************************************
*	Function : IPOD_GetNextTransID
*
*	Description : This function returns next transaction ID
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : none
*
**************************************************************************/
extern unsigned short IPOD_GetNextTransID(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_Get_IDPS_DataOffset
*
*	Description : This function returns DIPS data offset
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : none
*
**************************************************************************/
extern unsigned int IPOD_Get_IDPS_DataOffset(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_GetExtInfo
*
*	Description : This function returns extended information by user.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return : none
*
**************************************************************************/
extern void *IPOD_GetExtInfo(void *iPod_Handle);

/**************************************************************************
*	Function : IPOD_InitVar
*
*	Description : This functin initialize the iPod resource.
*				
*	Parameter : 
*		- Res0 : semaphore resource 
*
*  	Return : none
*
**************************************************************************/
extern void IPOD_InitVar(void *Res0, void *Res1, void *Res2, void *Res3, void *Res4);

/**************************************************************************
*	Function : IPOD_GetGener
*
*	Description : This funtion returns Gener string of current filelist index.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : file index
*		- pGener : Gener string pointer
*		- BufLen : buffer length
*		- ActualLen : string actual length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetGener(void *iPod_Handle, int index, unsigned char *pGener, long BufLen, long *pActualLen);

/**************************************************************************
*	Function : IPOD_GetTrackArtworkData
*
*	Description : This funtion returns artwork data
*				We recommend to use the IPOD_GetAlbumArt() function instead of this function.
*				please refer to the IPOD_GetAlbumArt() function description.
*				This function is sub function of IPOD_GetAlbumArt() function.
*				
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- trackIndex : file index
*		- formatID
*		- timeOffset
*		- pData : ArtworkData
*		- BufLen : artwork image data len
*		- ActualLen : string actual length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_GetTrackArtworkData(void *iPod_Handle, unsigned int trackIndex, short formatID, int timeOffset, ArtworkData *pData, unsigned long BufLen, unsigned long *ActualLen);

/**************************************************************************
*	Function : IPOD_SearchExtInfo_fromHandle
*
*	Description : 
*				This funtion returns iPod_Handle contains specific searching data.
*				This function will call the IPOD_Callback_CheckExtInfo() function to search the specific member of all handle.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- SearchingData : Searching data
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_SearchExtInfo_fromHandle(unsigned long SearchingData, unsigned long *iPod_Handle);

/**************************************************************************
*	Function : IPOD_GetCurrentEQProfileIndex
*
*	Description : (Display Remote)
*				This function returns current EQ profile index
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Index : Current equalizer Index
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetCurrentEQProfileIndex(void *iPod_Handle, unsigned long *Index);

/**************************************************************************
*	Function : IPOD_SetCurrentEQProfileIndex
*
*	Description : (Display Remote)
*				This function sets the EQ profile Index
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Index : Current equalizer Index
*		- bRestoreOnExit : RestoreOnExit
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_SetCurrentEQProfileIndex(void *iPod_Handle, unsigned long Index, RestoreOnExit bRestoreOnExit);

/**************************************************************************
*	Function : IPOD_DR_GetNumEQProfiles
*
*	Description : (Display Remote)
*				This function returns Total EQ profile Number.
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- ProfileCnt : Total Profile Count
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetNumEQProfiles(void *iPod_Handle, unsigned long *ProfileCnt);

/**************************************************************************
*	Function : IPOD_DR_GetIdxEqProfileName
*
*	Description : (Display Remote)
*				This functions returns current indexed EQ profile index.
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Index : Eq profile index
*		- eqProfileName : Eq profile Name
*		- BufLen : buffer Length
*		- pActualLen : returned data length
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetIdxEqProfileName(void *iPod_Handle, unsigned long Index, unsigned char *eqProfileName, long BufLen, long *pActualLen);

/**************************************************************************
*	Function : IPOD_DR_SetRemoteEventNoti
*
*	Description : (Display Remote)
*				This functions sets the remote event.
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- EventMask : combination of IPOD_REMOTE_EVENT_NOTI_SET enum values.
*			*ex) EventMask = IPOD_DR_EVT_SET_TRACK_POS_S | IPOD_DR_EVT_SET_HOLD_SWITCH;
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_SetRemoteEventNoti(void *iPod_Handle, unsigned long EventMask);

/**************************************************************************
*	Function : IPOD_DR_GetRemoteEventStatus
*
*	Description : (Display Remote)
*				This functions returns Remote Event status
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- EventMask : combination of IPOD_REMOTE_EVENT_NOTI_SET enum values.
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetRemoteEventStatus(void *iPod_Handle, unsigned long *EventStatus);

/**************************************************************************
*	Function : IPOD_DR_GetiPodStateInfo
*
*	Description : (Display Remote)
*				This functions returns iPod state information.
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- InfoType : {IPOD_DR_STATUS_INFO}
*
*	Example :
*		pIPOD_PLAY_INFO ExtInfo = IPOD_GetExtInfo(iPod_Handle);
*		IPOD_DR_STATUS_INFO InfoType ={0, };
*		InfoType = IPOD_DR_STATUS_TRACK_POS_MS;
*		err = IPOD_DR_GetiPodStateInfo(iPod_Handle, InfoType);
*		if(IPOD_NO_ERROR == err)	
*		{
*			PRINT("\t\t iPodStateInfo TimePosition_ms : %d\n", ExtInfo->TimePosition_ms); 
*		}
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetiPodStateInfo(void *iPod_Handle, IPOD_DR_STATUS_INFO InfoType);

/**************************************************************************
*	Function : IPOD_DR_SetiPodStateInfo
*
*	Description : (Display Remote)
*				This functions sets iPod state information.
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- pStateParam : {pIPOD_DR_SETSTATEINFO_PARAM}
*
*	Example :
*		SettingInfo.InfoType = IPOD_DR_STATUS_PLAYBACK_INDEX;
*		SettingInfo.data.TrackIndex = 0x03;
*		IPOD_DR_SetiPodStateInfo(iPod_Handle, &SettingInfo);
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_SetiPodStateInfo(void *iPod_Handle, pIPOD_DR_SETSTATEINFO_PARAM pStateParam);

/**************************************************************************
*	Function : IPOD_DR_GetPlayStatus
*
*	Description : (Display Remote)
*				This functions returns Play status
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- pPlayStatus : {pIPOD_DR_PLAYSTATUS}
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetPlayStatus(void *iPod_Handle, pIPOD_DR_PLAYSTATUS pPlayStatus);

/**************************************************************************
*	Function : IPOD_DR_SetiPodCurPlayingTrack
*
*	Description : (Display Remote)
*				This functions sets iPod current Playing Track
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- TrackIndex : current Playing Track Information.
*
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_SetiPodCurPlayingTrack(void *iPod_Handle, unsigned long TrackIndex);

/**************************************************************************
*	Function : IPOD_DR_GetIndexedPlayingTrackInfo
*
*	Description : (Display Remote)
*				This functions returns indexed playing track information.
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- pTrackParam : {pIPOD_DR_TRACK_INFO_PARAM}
*
*	Example :
*			TrackInfoParam.type = IPOD_DR_TRACK_INFO_CAPS;
*			TrackInfoParam.TrackIndex = 5;
*			TrackInfoParam.ChapterIndex = 0;
*			IPOD_DR_GetIndexedPlayingTrackInfo(iPod_Handle, &TrackInfoParam);
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetIndexedPlayingTrackInfo(void *iPod_Handle, pIPOD_DR_TRACK_INFO_PARAM pTrackParam);

/**************************************************************************
*	Function : IPOD_DR_GetNumPlayingTracks
*
*	Description : (Display Remote)
*				This functions returns play track number.
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- numPlayTracks : Play Track Number.
*
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetNumPlayingTracks(void *iPod_Handle, unsigned long *numPlayTracks);

/**************************************************************************
*	Function : IPOD_DR_GetArtworkFormats
*
*	Description : (Display Remote)
*				This functions returns artwork formats
*				
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- pArtFormatData : {pArtworkFormat}
*		- FormatCnt : buffer format count 
*		- AcutalFormatCnt : received format count
*
*	Example :
*			Please refer to the IPOD_SetDefaultArtworkFormatID() function on IPOD_API.c file.
*
*  	Return : IPOD_ERROR ( please refer to the iPod_error.h)
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetArtworkFormats(void *iPod_Handle, pArtworkFormat pArtFormatData, long FormatCnt, long *AcutalFormatCnt);

/**************************************************************************
*	Function : IPOD_DR_GetAlbumArt
*
*	Description : (Display Remote)
*				This functions returns album art data.
*				Before this fucntion  IPOD_SetDefaultArtworkFormatID() function should be called.
*				On IPOD_SetDefaultArtworkFormatID() function, You should enalbe IPOD_DR_GetArtworkFormats() function.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- index : {pArtworkData}
*		- pData : album art data buffer pointer
*		- BufLen : album art data buffer length
*		- pActualLen : albumart actual data.
*
*	Example :
*			ArtworkData ArtworkData;
*			int TrackIndex = 20;
*			unsigned int ActualLen;
*			static unsigned char AlbumartData[320*320*2];
*			ArtworkData.pImageData = AlbumartData;
*			IPOD_DR_GetAlbumArt(iPod_Handle, TrackIndex, &ArtworkData, 320*320*2, &ActualLen);
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*		   IPOD_NO_DATA : It means that indexed contents does not contains album art data.
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetAlbumArt(void *iPod_Handle, unsigned long  index, pArtworkData pData, unsigned long BufLen, unsigned long *pActualLen);

/**************************************************************************
*	Function : IPOD_DR_GetPowerBatteryState
*
*	Description : (Display Remote)
*				This functions returns Power state and battery level
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- PowerState : Power state
*		- BattLevel : Battery Level
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetPowerBatteryState(void *iPod_Handle, unsigned char *PowerState, unsigned char *BattLevel);

/**************************************************************************
*	Function : IPOD_DR_GetSoundCheckState
*
*	Description : (Display Remote)
*				This functions returns the sound checkstate
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- SndChkStatel : Sound check state
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_GetSoundCheckState(void *iPod_Handle, unsigned char *SndChkStatel);

/**************************************************************************
*	Function : IPOD_DR_SetSoundCheckState
*
*	Description : (Display Remote)
*				This functions sets the sound checkstate
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- SndChkState : Sound check state
*		- RestoreOn : {RestoreOnExit}
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_DR_SetSoundCheckState(void *iPod_Handle, unsigned char SndChkState, RestoreOnExit RestoreOn);



#ifdef WINCE
/**************************************************************************
*	Function : IPOD_SendAccAck
*
*	Description : This functions send the AccAck to iPod
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Info : msg param from iPod library.
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_SendAccAck(void *iPod_Handle, unsigned short Info);
#endif /*#ifdef WINCE*/

/**************************************************************************
*	Function : IPOD_CheckiPodOption
*
*	Description : (General)This functions gets the iPod option data
*
*	Parameter : 
*		- IPOD_LINGOS : Lingo ID
*		- pIPOD_LINGO_INFO : Lingo option or version Info
*		- IsVerion : If the return value is version, it will be set.
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_CheckiPodOption(void *iPod_Handle, IPOD_LINGOS Lingo, pIPOD_LINGO_INFO pLingo_Info, unsigned int *IsVerion);

/**************************************************************************
*	Function : IPOD_CheckiPodOption
*
*	Description : This functions gets the iPod option data or version data.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- pIPOD_INIT_CHANNRL_PARAM : Channel param
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_InitChannel(void *iPod_Handle, pIPOD_INIT_CHANNRL_PARAM pChannelPrarm);

/**************************************************************************
*	Function : IPOD_UART_IRQ_PutData
*
*	Description : This functions gets the iPod data from UART channel.
*
*	Parameter : 
*		- UartData : uart data 
*
*  	Return :
*		- none.
*
**************************************************************************/
extern void IPOD_UART_IRQ_PutData(unsigned char UartData);

/**************************************************************************
*	Function : IPOD_DevDataTransfer
*
*	Description : This function send data to iOS application.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- SessingID : session id
*		- pData : data pointer
*		- nDataSize : data size
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_DevDataTransfer( void *iPod_Handle, unsigned int SessingID, unsigned char *pData, unsigned int nDataSize, IPOD_DATATRANSFER_TYPE iPodDataTransferType, unsigned int *RetryTransID, unsigned int *RetryDataCount);


/**************************************************************************
*	Function : IPOD_CheckLingoOption
*
*	Description : It check the lingo option.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*
**************************************************************************/
extern IPOD_ERROR IPOD_CheckLingoOption(void *iPod_Handle, pIPOD_INIT_PARAM pParam);

/**************************************************************************
*	Function : IPOD_GetTxBuffer
*
*	Description : It returns TX buffer pointer.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*
*  	Return :
*		- Tx buffer pointer
*
**************************************************************************/
extern unsigned char *IPOD_GetTxBuffer(void *iPod_Handle);

extern IPOD_ERROR IPOD_Identify(void *iPod_Handle, IPOD_LINGOS Lingo);
/**************************************************************************
*	Function : IPOD_CheckNewTrackInfoStatus
*
*	Description : It checks that whether iPod send the TrackNewAudioAttributes command or not.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- status : 1 - iPod sent the TrackNewAudioAttributes command to Host. 
*		- status : 0 - iPod didn't send the TrackNewAudioAttributes command to Host. 
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_CheckNewTrackInfoStatus(void *iPod_Handle, unsigned long *status);
/**************************************************************************
*	Function : IPOD_RequestApplicationLaunch
*
*	Description : This function call to launch a specific iPod application.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- AppString : Application Bundle ID string, such as "com.mycompany.myapp"
*		- Strlen : Application Bundle ID string length
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_RequestApplicationLaunch(void* iPod_Handle, unsigned char *AppString, unsigned int Strlen);
/**************************************************************************
*	Function : IPOD_GetSupportedEventNotification
*
*	Description : This function get a iPod device's support for notifications.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- eventNotiMask : IPOD_NOTI_BITMASK_STATUS ( please refer to the iPodLib.h) 
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_GetSupportedEventNotification(void *iPod_Handle, unsigned long long *eventNotiMask);
/**************************************************************************
*	Function : IPOD_SetEventNotification
*
*	Description : This function enables asynchronous remote event notifications for specific Apple device events.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- eventNotiMask : IPOD_NOTI_BITMASK_STATUS ( please refer to the iPodLib.h) 
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_SetEventNotification(void *iPod_Handle, unsigned long long eventNotiMask);

/**************************************************************************
*	Function : IPOD_GetEventNotification
*
*	Description : This function get Apple device's current notification bitmask.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- eventNotiMask : IPOD_NOTI_BITMASK_STATUS ( please refer to the iPodLib.h) 
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_GetEventNotification(void *iPod_Handle, unsigned long long *eventNotiMask);
/**************************************************************************
*	Function : IPOD_RequestTransportMaxPayloadSize
*
*	Description : This function determine the maximum allowable payload size per packet using the current transport.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- maxPayload : The maximum allowable packet payload, in bytes.
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_RequestTransportMaxPayloadSize(void *iPod_Handle, unsigned int *maxPayload);
extern IPOD_ERROR IPOD_ButtonControl_EndFFREWinCallback(void *iPod_Handle, PlayCmdCode cmdcode); 
/**************************************************************************
*	Function : IPOD_SetVideoDelay
*
*	Description : This function determine the maximum allowable payload size per packet using the current transport.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- Delay : Video delay in milliseconds.
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_SetVideoDelay(void *iPod_Handle, int Delay);
/**************************************************************************
*	Function : IPOD_GetOptionForLingo
*
*	Description : This function get result iPodOptionForLingoes command.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		- lingo : IPOD_LINGOS(please refer to the iPodLib.h, support LINGO_GENERAL and LINGO_EXTENDED_INTERFACE)
        - OptionForLingo : Option bit field. refer to Mfi document.
*
*  	Return :
*		- IPOD_ERROR ( please refer to the iPod_error.h) 
*	
**************************************************************************/
extern IPOD_ERROR IPOD_GetOptionForLingo(void *iPod_Handle, IPOD_LINGOS lingo, unsigned long long *OptionForLingo);
/**************************************************************************
*	Function : IPOD_BuffReset
*
*	Description : This function set buffer pointer zero.
*
*	Parameter : 
*		- iPod_Handle : iPod Handle ( by iPod_init() function ) 
*		
*  	Return :
*		- void
*	
**************************************************************************/
extern void IPOD_ResetBufferPtr(void *iPod_Handle);

#if defined(__cplusplus)
};
#endif

#endif	/* IPOD_INCLUDE */


#endif /*  _IPOD_LIB_H_ */
/* End of File */


