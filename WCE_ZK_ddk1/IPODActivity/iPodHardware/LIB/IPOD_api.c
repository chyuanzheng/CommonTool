/**************************************************************************			
***                                                                          
***   2005.11.30.  yohoj, TELECHIPS.                                     
***                                                                          
***   Last Updated : 2005.12.27                                                
***                                                              
**************************************************************************/
//#pragma comment(lib, "ipod\\lib\\iPod_LIB_WINCE6.lib")

#ifdef IPOD_NUCLUES
#include "include/main.h"
#endif

#ifdef IPOD_INCLUDE

#include "IPOD_error.h"
#include "iPodLib.h"
#include "iPod_api.h"

#ifdef WINCE
#include <windows.h>
#include "../ipodconfig.h"
#include <winioctl.h>
#include <winuser.h>
#endif


#ifdef IPOD_NUCLUES

#include "uiappl/ui_def.h"
#include "uiappl/ui_global.h"
#include "uiappl/ui_api.h"
#include "uiappl/ui_drivers.h"
#include "uiappl/ui_function.h"
#include "uiappl/scroll.h"
#include "USBHost/USB_AUDIO/USBHost_Audio_BuffCtrl.h"
#include "IPOD/IPOD_api.h"
//#include "USBHost/USB_AUDIO/USBHost_Audio_BuffCtrl.h"
#include "USBHost/USBHost_HID.h"
#include "Resource/TCCresource.h"

#ifdef TCC78X
#include "tcc78x.h"
#include "include/globals.h"
#include "usbhost/USB_host.h"
#include "usbhost/TCCHID.h"
#include "FS/disk.h"
#endif /*ifdef TCC78X*/

#if defined(TCC860x)
#include "TCC86x.h"
#include "kernel/telechips.h"
#include "fs/utils.h"
#include "USBHost/USBHost_Header.h" 
#include "FS/disk.h"
#include "FileBuffer/FileBufferCtrl.h"
#include "TCC_Api.h"
#include "commoncmd.h"
#endif /*ifdef defined(TCC860x)*/

#if defined(TCC83XX)
#include "tcc83xx.h"
#include "FS/disk.h"
#include "USBHost/USBHostLib.h" 
#include "FileBuffer/FileBufferCtrl.h"
#endif /*ifdef defined(TCC83XX)*/

#ifdef TCC76X
#include "tcc760.h"
#include "USBHost/USBHostLib.h" 
#include "USBHost/USBHost_HID.h"
#endif /*TCC76X*/

#if defined(TCC80XX)
#include "buffer/buffer.h"
#include "FS/disk.h"
#include "include/Globals.h"
#include "FileBuffer/filebufferctrl.h"
#include "include/common_array.h"
#include "USBHost/USB_AUDIO/USBHost_Audio_BuffCtrl.h"
#include "USBHost/USBHost_header.h"
#include "USBHost/USBHost_HID.h"
#include "FS/disk.h"
#include "DDI/DDIManager/DDI_Manager.h"

#if 1 //def DMP_MESSAGE_INCLUDE
#include "TC_MSG/TC_MSG_Parser.h"
#ifdef USE_DISPLAY_OBJECT
#include "TC_UI/TC_UI_ScreenAxis.h"
#endif
#endif /*DMP_MESSAGE_INCLUDE*/
#endif /*ifdef defined(TCC80XX)*/

#ifdef TCLINK_UART_PC_SIMULATOR_INCLUDE
#include "TCLSAPI.h"
#endif


#include "LCD/lcd.h"

#ifdef CD_HOST_RIPPING_INCLUDE
#define CD_RIPPING_INCLUDE
#endif
#ifdef CD_RIPPING_INCLUDE
#include "CDIF/CD_Ripping.h"
#endif

#endif /*#ifdef IPOD_NUCLUES*/





/*************************************************************************/
/*Global Variable                                                                                                      */
/*************************************************************************/

volatile unsigned char *IPOD_UTF8DecodeBuffer;

/* UTF-8 Format */
const IPOD_ACCINFO_TOKEN_VAL gIPOD_AccInfo = {	/* QAC : 9.2 */
	(IPOD_ACCESSORY_NAME |IPOD_ACCESSORY_FIRMWARE_VERSION | IPOD_ACCESSORY_HARDWARE_VERSION 
	| IPOD_ACCESSORY_MANUFACTURER | IPOD_ACCESSORY_MODEL_NUM | IPOD_ACCESSORY_RF_CERTIFICATIONS),
	0x06/*0x05*/,
	{'T','E','L','E','C','H','I','P','S',0x00 ,0x00 }, /* Name Info */
	{1, 0, 0 }, NULL,						     /* Firmware Version + padding */
	{1, 3, 0 }, NULL,						    /* Hardware Version + padding */
	{'T','E','L','E','C','H','I','P','S',0x00 ,0x00 }, /* manufacturer Name info */

#ifdef WINCE	
	{'T','C','C','8','9','0','X',0x00 ,0x00 }, /* Model Number */
	{'W','I','N','_','C','E',0x00 ,0x00 }, /* Serial Number */
#endif

#ifdef TCC860x	
	{'T','C','C','8','6','0','X',0x00 ,0x00 }, /* Model Number */
	{'D','M','P','_','H','O','S', 'T',0x00 ,0x00 }, /* Serial Number */
#endif

#ifdef TCC83XX
	{'T','C','C','8','3','0','X',0x00 ,0x00 }, /* Model Number */
	{'D','M','P','_','H','O','S', 'T',0x00 ,0x00 }, /* Serial Number */
#endif

#ifdef TCC80XX
	{'T','C','C','8','0','0','X',0x00 ,0x00 }, /* Model Number */
	{'D','M','P','_','H','O','S', 'T',0x00 ,0x00 }, /* Serial Number */
#endif

	/* See Apples's MFi Accessory Testing Specification */
	//(IPOD_RF_CERT_CLASS1|IPOD_RF_CERT_CLASS2|IPOD_RF_CERT_CLASS4) /* RF certifications*/
	0x00,
};

const IPOD_ACC_PREF_SETTING_FORMAT gIPOD_Pref[IPOD_PREF_MAX_CNT] = {
	/*{IPOD_PREFERENCE_CLASSID, 			SettingID, 	RestoreOnExit},*/
	{IPOD_VIDEO_OUT_SETTING, 				0x01, 		RESTORE_ORG_SETTING}, /*Enable Apple device video output based on the other video preferences(NTSC/PAL,screen configuration, etc)*/
	{IPOD_SCREEEN_CONFIGURATION, 			0x01, 		RESTORE_ORG_SETTING}, /*0x00: Fill entire screen, 0x01:fit to screen edge*/
	{IPOD_VIDEO_SIGINAL_FORMAT, 			0x00, 		RESTORE_ORG_SETTING}, /*0x00: NTSC*/
	//-{IPOD_LINE_OUT_USAGE, 					0x01, 		RESTORE_ORG_SETTING}, /*0x01: Used*/
	{IPOD_VIDEO_OUT_CONNECTION,				0x01, 		RESTORE_ORG_SETTING}, /*0x00:None, 0x01:Composite, 0x02:S-Video, 0x03:Component*/
	//-{IPOD_CLOSED_CAPTIONING, 				0x01, 		RESTORE_ORG_SETTING}, /*0x00:Off, 0x01:On*/
	{IPOD_VIDEO_MONITOR_ASPECT_RATIO, 		0x00, 		RESTORE_ORG_SETTING}, /*0x00:4:3, 0x01:16:9*/
	//{IPOD_SUBTITLES, 						0x00, 		RESTORE_ORG_SETTING}, /*0x00:Subtitles off, 0x01:Subtitle On*/
	//{IPOD_VIDEO_ALTERNATE_AUDIO_CHANNEL, 	0x00, 		RESTORE_ORG_SETTING}, /*Alternate audio off*/ 
	//-{IPOD_PAUSE_ON_POWER_REMOVAL, 			0x00, 		RESTORE_ORG_SETTING}, /*0x00:Pause off, 0x01:Pause on*/
	//{IPOD_VOICEOVER_PREFERENCE, 0x00, RESTORE_ORG_SETTING},/*0x00:VoiceOver off, 0x01:VoiceOver on*/
	//{IPOD_ASSISTIVETOUCH, 0x00, RESTORE_ORG_SETTING}/*0x00:Off, 0x01:On*/
};

IPOD_PLAY_INFO gIPOD_PlayInfo[IPOD_PLAY_INFO_MAX_CNT] = {0};

unsigned char IPOD_Bitmap[24*50] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xf4, 0x03, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x15, 0x55, 0xf5, 0x55, 0x54, 0x0f, 0xc0, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0x3f, 0x00, 0x03, 0xf0, 0x00, 0xfc, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x03, 0xf0, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x3c, 0x03, 0xc0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x3c, 0x0f, 0xc0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x3c, 0x0f, 0xc0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x3c, 0x03, 0xc0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x03, 0xf0, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0x3f, 0x00, 0x03, 0xf0, 0x00, 0xfc, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0x0f, 0xc0, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf4, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xfc, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0xfc, 0x00, 0x0f, 0xc0, 0x0f, 0xc0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x03, 0xf0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xfc, 0x00, 0x00, 0xfc, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0x00, 0x3c, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0x0f, 0x03, 0xf0, 0x00, 0x00, 0x3c, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0x3f, 0x03, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0xfc, 0x03, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0xff, 0xff, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0xff, 0xff, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x03, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0xfc, 0x03, 0xf0, 0x00, 0x00, 0x3c, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x3f, 0x00, 0xf0, 0x00, 0x00, 0x3c, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xfc, 0x00, 0x00, 0xfc, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x03, 0xf0, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x3f, 0x00, 0x03, 0xf0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0f, 0xc0, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0xc0, 0x0f, 0xc0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x03, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xff, 0xfc, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
	
volatile unsigned int IPOD_RX_W_Ptr=0;// For filling receive buffer
volatile unsigned int IPOD_RX_R_Ptr=0;// For fetching receive buffer
volatile unsigned int IPOD_TX_Start;

unsigned char *pIPOD_RxBuff;
unsigned char *pIPOD_TxBuff;
unsigned char *pIPOD_RXData;
	
unsigned int IPOD_RX_Size = IPOD_RXBUFSIZE;
unsigned int IPOD_TX_Size = IPOD_TXBUFSIZE;


unsigned int IPOD_SyncFlag;// set after sync command
unsigned int IPOD_LengthSetFlag;// set after receiving length field

unsigned int IPOD_DataLength;// data length of received packet
unsigned int IPOD_RX_DataPtr;// used to move from buffer to data area

IPOD_Command IPOD_RX_Cmd;

int IPOD_Insert = 0;


#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
int IPOD_Access;
int IPOD_Navi_Access;
int IPOD_FFREW_Flag;
#endif  


unsigned char IPOD_Category[5] = {'I','P','O','D','\0'};

#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
extern void TC_TimeDly(unsigned int ticks);
extern void OSTimeDly(unsigned short ticks);
extern void IO_TimerDelay(unsigned int ucTime);
#endif

//void IPOD_SetFileNum(long CurFileNum, long TotalFileNum, pIPOD_PLAY_INFO pPlayInfo);
static void IPOD_Display_No_SongMsg(void *iPod_Handle);
static void IPOD_SetPlayTime(unsigned int Time, pIPOD_PLAY_INFO pPlayInfo);
static void IPOD_SetPartionID(void);
static unsigned int IPOD_API_GetDisplayDataSize(void);
static void IPOD_UpdateTimeInfo(unsigned int TimePosition, unsigned int Disk);
static void IPOD_UpdateTrackInfo(const IPOD_PLAY_INFO *pInfo/*unsigned int CurrentIdx*/, unsigned int Disk);	/* QAC : 16.7 */
static void IPOD_UpdateFFSeekStopInfo(unsigned int Disk);
static void IPOD_UpdateREWSeekStopInfo(unsigned int Disk);


/*************************************************************************/
/*IPOD Function                                                                                                         */
/*************************************************************************/

/**************************************************************************
*	Function : IPOD_initResource
*
*	Description : This function initialize the iPod resource
*				
*	Parameter : none
*
*  	Return : none
*
**************************************************************************/
#ifdef WINCE
void *TCC_IPOD0_SEM;
void *TCC_IPOD1_SEM;
void *TCC_IPOD2_SEM;
void *TCC_IPOD3_SEM;
void *TCC_IPOD4_SEM;
#ifndef NULL
#define NULL 0
#endif

#endif /*WINCE*/

void IPOD_initResource(void)
{
#ifdef IPOD_NUCLUES
	(void) TC_Create_Semaphore(&TCC_IPOD0_SEM,	"IPOD_S0", 1);
	(void) TC_Create_Semaphore(&TCC_IPOD1_SEM,	"IPOD_S1", 1);
	(void) TC_Create_Semaphore(&TCC_IPOD2_SEM,	"IPOD_S2", 1);
	(void) TC_Create_Semaphore(&TCC_IPOD3_SEM,	"IPOD_S3", 1);
	(void) TC_Create_Semaphore(&TCC_IPOD4_SEM,	"IPOD_S4", 1);
#endif

#ifdef WINCE
	TCC_IPOD0_SEM = CreateSemaphore(NULL,1,1,NULL);
	TCC_IPOD1_SEM = CreateSemaphore(NULL,1,1,NULL);
	TCC_IPOD2_SEM = CreateSemaphore(NULL,1,1,NULL);
	TCC_IPOD3_SEM = CreateSemaphore(NULL,1,1,NULL);
	TCC_IPOD4_SEM = CreateSemaphore(NULL,1,1,NULL);
#endif
}

/**************************************************************************
*	Function : IPOD_Alloc_communication_mem
*
*	Description : This function allocate the iPod communication buffer
*				
*	Parameter : buffer size
*
*  	Return : void pointer of communication buffer
*
**************************************************************************/
static void *IPOD_Alloc_communication_mem(unsigned long size)
{
	unsigned char *Buff=NULL;
	
#if defined(TCC80XX) || defined(TCC860x) || defined(TCC83XX) || defined(TCC78X) 
	Buff = TC_Allocate_Memory(size);
	if(0 == Buff)
	{
		PRINTF("[%s : %d]Memory full",__func__, __LINE__);
	}
#endif

#if 0
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
	Buff = gFileBuffer;
#endif
#endif
#ifdef WINCE
//	Buff = new unsigned char[64*1024*4];
//	Buff = malloc(64*1024*4);
	Buff = malloc(size);
#endif

	return Buff;
}
/**************************************************************************
*	Function : IPOD_Malloc_iPodBuf
*
*	Description : This function allocate the iPod play info
*				
*	Parameter : none
*
*  	Return : void pointer of play info
*
**************************************************************************/
void *IPOD_Malloc_iPodBuf(void)
{
	int i;
	void *Ret = NULL;
	unsigned char *Buff;

	for(i=0; i<IPOD_PLAY_INFO_MAX_CNT; i++)
	{
		if(gIPOD_PlayInfo[i].m_Status == 0)
		{
			gIPOD_PlayInfo[i].m_Status = 1;

			if(gIPOD_PlayInfo[i].pBuffer == 0)
			{
				Buff = IPOD_Alloc_communication_mem(IPOD_TOTALBUFSIZE);
				if(Buff == 0)
				{
					/* Alloc ERROR */
					gIPOD_PlayInfo[i].m_Status = 0;
					break;
				}
				else
				{
					gIPOD_PlayInfo[i].pBuffer = Buff;
				}
			}
			else
			{
				Buff = gIPOD_PlayInfo[i].pBuffer;
			}
			gIPOD_PlayInfo[i].DisconnecEvt = 0;
			//IPOD_InitBuff(pbuf_param, Buff); //move to IPOD_API_WINCE_USB_InitChannelParam()
			
			Ret = (void *)&gIPOD_PlayInfo[i];
			break;
		}

	}
	return Ret;
}

/**************************************************************************
*	Function : IPOD_Get_AudioPlayInfo
*
*	Description : This function returns play information of iPod 
*				
*	Parameter : iPod_Handle
*
*  	Return : pIPOD_PLAY_INFO pointer
*
**************************************************************************/
pIPOD_PLAY_INFO IPOD_Get_AudioPlayInfo(void *iPod_Handle)
{
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(iPod_Handle);
	
	return pInfo;

}

void IPOD_BuffReset(void *iPod_Handle)
{
    IPOD_ResetBufferPtr(iPod_Handle);
	pIPOD_TxBuff = 0;

	pIPOD_RxBuff = 0;
	IPOD_RX_W_Ptr = 0;
	IPOD_RX_R_Ptr = 0;

	pIPOD_RXData  = 0;

	IPOD_UTF8DecodeBuffer =0;
}
/**************************************************************************
*	Function : IPOD_Free_AudioPlayInfo
*
*	Description : This function deallocate the play information of iPod
*				
*	Parameter : iPod_Handle
*
*  	Return : none.
*
**************************************************************************/
void IPOD_Free_AudioPlayInfo(void *iPod_Handle)
{
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(iPod_Handle);

	if(pInfo != 0)
	{
#ifdef WINCE 
		if(pInfo->pBuffer != 0)
		{
				   free(pInfo->pBuffer);
				   IPOD_BuffReset(iPod_Handle);
		}
#endif
#ifdef IPOD_NUCLUES
		if(pInfo->pBuffer != 0)
		{
			(void) TC_Deallocate_Memory(pInfo->pBuffer);
			IPOD_BuffReset(iPod_Handle);
		}
#endif
		if(pInfo->m_Status != 0)
		{
			memset((void *)pInfo, 0x00, sizeof(IPOD_PLAY_INFO));
		}

	}
}



/**************************************************************************
	Function : IPOD_API_SetStatus

 	Description : It sets the IPOD status for HUB system
				
	Parameter : iPod_Handle / state

  	Return : none
		
**************************************************************************/
void IPOD_API_SetStatus(void *iPod_Handle, IPOD_STATE state)
{	
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(iPod_Handle);

	if(pInfo != 0)
	{
		pInfo->Basic_Info.ipod_state = state;
	}
}

/**************************************************************************
	Function : IPOD_API_GetStatus

 	Description : It gets the IPOD status for HUB system
				
	Parameter : iPod_Handle
	
  	Return : status (IPOD_MOUNTED, IPOD_UNMOUNTED)
		
**************************************************************************/
IPOD_STATE IPOD_API_GetStatus(void *iPod_Handle)
{
	IPOD_STATE lStatus = IPOD_PLUGED;
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(iPod_Handle);

	if(pInfo != 0)
	{
		lStatus = pInfo->Basic_Info.ipod_state;
	}

	return lStatus;
}


/**************************************************************************
	Function : IPOD_API_GetDevNo

 	Description : It returns the iPod device Nmuber.

	Parameter : ExtInfo

  	Return :

**************************************************************************/
int IPOD_API_GetDevNo(void *ExtInfo)
{
	int lDevNo = 0;
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	if(pInfo != 0)
	{
		lDevNo = (int)(pInfo->Basic_Info.DevNo);
	}

	return lDevNo;
}

/**************************************************************************
	Function : IPOD_API_SaveSamplingFreq

 	Description :

	Parameter : ExtInfo / SamplingFreq

  	Return :

**************************************************************************/
void IPOD_API_SaveSamplingFreq(void *ExtInfo, unsigned int SamplingFreq)
{
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	if(pInfo != 0)
	{
		 pInfo->Basic_Info.SamplingFreq = SamplingFreq;
	}
}


/**************************************************************************
	Function : USBH_API_IPOD_GetSampleRate

 	Description : It returns the iPod device current Samplerate.

	Parameter :

  	Return : SampleRate

**************************************************************************/
unsigned int IPOD_API_GetSamplingFreq(void *ExtInfo)
{
	unsigned int lSamplingFreq = 0;
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	if(pInfo != 0)
	{
		lSamplingFreq = pInfo->Basic_Info.SamplingFreq;
	}

	return lSamplingFreq;
}

/**************************************************************************
*	Function : IPOD_Callback_CheckExtInfo
*
*	Description : 
*				
*	Parameter : 
*
*  	Return : 
*		1 : found
*		0 : not found
*
**************************************************************************/
void *IPOD_GetHandle_fromDevNo(unsigned int DevNo)
{
	void *pHandle;
	unsigned long lHandle;
	IPOD_ERROR Err;
	
	Err = IPOD_SearchExtInfo_fromHandle(DevNo, &lHandle);
	if(Err == IPOD_NO_ERROR)
	{
		pHandle = (void *)lHandle;
	}
	else
	{
		pHandle = (void *)NULL;
	}
	return pHandle;
}


/**************************************************************************
*	Function : IPOD_Callback_CheckExtInfo
*
*	Description : 
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*
*  	Return : 
*		1 : found
*		0 : not found
*
**************************************************************************/
unsigned int IPOD_Callback_CheckExtInfo(void *ExtInfo, unsigned long SearchingData)
{
	unsigned int lRet;
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)ExtInfo;
	
	if(pInfo->Basic_Info.DevNo == SearchingData)
	{
		lRet = 1;
	}
	else
	{
		lRet = 0;
	}
	return lRet;
}

/**************************************************************************
*	Function : IPOD_ResetVideoSupportDB
*
*	Description : It reset the DB for video
*				This function is example fucntion.
*				It just select the first item of media kind lists. 
*				
*	Parameter : none
*
*  	Return : none
*
**************************************************************************/
unsigned char media_kind[10][40];

int IPOD_ResetVideoSupportDB(void *iPod_Handle)
{
	int TotalVideo_MediaCnt, i, ret;
	unsigned long index;	
	unsigned long ActualLen;	
	
	ret = IPOD_SelectDBHierarchy(iPod_Handle, DBSEL_VIDEO);
	if(ret == IPOD_NO_ERROR)
	{
		ret = IPOD_GetVideoMediaKindCnt(iPod_Handle, &TotalVideo_MediaCnt);

		if(IPOD_NO_ERROR == ret)
		{
			/*
			 This is a sample code to select the Movies category 
			 In case of iPod touch
			 0 : Movies
			 1 : Music Video
			 2 : TV shows
			 3 : Video poadcasts
			 Select the Media kind from media_kind name data
			*/

		#ifdef WINCE
			IPOD_RECORD_TYPE *pMediaKindName;
			pMediaKindName = (IPOD_RECORD_TYPE *)malloc(sizeof(IPOD_RECORD_TYPE)*TotalVideo_MediaCnt);
			ret = IPOD_AskFileName(iPod_Handle, MEDIA_KIND, 0, TotalVideo_MediaCnt, pMediaKindName);
			if(IPOD_NO_ERROR == ret)
			{
				ret = IPOD_SelectVedeoDBRecord(iPod_Handle, TotalVideo_MediaCnt, 0);
			}
			free(pMediaKindName);
		#else
		
			ret = IPOD_AskFileName(iPod_Handle, MEDIA_KIND, 0, TotalVideo_MediaCnt);
			if(IPOD_NO_ERROR == ret)
			{
				for (i=0; i < TotalVideo_MediaCnt; i++)
				{
					(void)IPOD_GetFileName(iPod_Handle, &index, 40, media_kind[i], &ActualLen);
		//			IPOD_GetVideoMediaKindname(iPod_Handle, i, media_kind[i], 40);
				}
				ret = IPOD_SelectVedeoDBRecord(iPod_Handle, TotalVideo_MediaCnt, 0);
			}
		#endif
		}
		
	}
	else
	{
		ret = IPOD_ResetDB(iPod_Handle);
	}

	return ret;
}

/**************************************************************************
*	Function : IPOD_ResetDataBase
*
*	Description : This function reset the iPod DB 
*				
*	Parameter : none
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_ResetDataBase(void *iPod_Handle)
{
	IPOD_ERROR ret;
	/*
	 This example code to access video data of iPod.
	IPOD_ResetVideoSupportDB();
	*/
	
	/* This fucntion is used to access only music data of iPod.*/
	ret = IPOD_ResetDB(iPod_Handle);

	return ret;
}

/**************************************************************************
*	Function : IPOD_GetVideoTracksCnt
*
*	Description : This function get count of movies on iPod.
*				
*	Parameter : none
*
*  	Return : count of movies
*
**************************************************************************/
int IPOD_GetVideoTracksCnt(void *iPod_Handle)
{
	IPOD_ERROR err;
	long TotalFileNum = 0;

	err = IPOD_SelectDBHierarchy(iPod_Handle, DBSEL_VIDEO);
	if(IPOD_NO_ERROR == err)
	{
		(void) IPOD_SelectListType(iPod_Handle, IPOD_LIB_TRACK, &TotalFileNum);
	}
	return TotalFileNum;
}



/**************************************************************************
*	Function : IPOD_SelectFileList
*
*	Description : This function select track list on STOP state of iPod.
*				
*	Parameter : none
*
*  	Return : none
*
**************************************************************************/
int IPOD_SelectFileList(void *iPod_Handle)
{
	IPOD_ERROR err;
	long TotalFileNum = 0;
	
	err = IPOD_ResetDataBase(iPod_Handle);
	if(IPOD_NO_ERROR == err)
	{
		(void) IPOD_SelectListType(iPod_Handle, IPOD_LIB_TRACK, &TotalFileNum);
	}
	return TotalFileNum;
	
}

/**************************************************************************
*	Function : IPOD_CheckPlayStatus
*
*	Description : This function initialize the Play status of iPod
*				
*	Parameter : iPod_Handle
*
*  	Return : none
*
**************************************************************************/
void IPOD_CheckPlayStatus(void *iPod_Handle)
{

	IPOD_ERROR Err;
	int TotalTrackLength, lTime, lStatus;
	pIPOD_PLAY_INFO pPlayInfo = IPOD_Get_AudioPlayInfo(iPod_Handle);


	if(pPlayInfo != 0)
	{
		Err = IPOD_GetStatus(iPod_Handle, &TotalTrackLength, &lTime, &lStatus);
		if(IPOD_NO_ERROR == Err)
		{
			pPlayInfo->TotalTime = TotalTrackLength;
			pPlayInfo->TimePosition = lTime;
			if(IPOD_STOPPING == lStatus)
			{
				pPlayInfo->m_PlayStatus = IPOD_STATUS_STOPPED;
				pPlayInfo->Rd_playStatus = IPOD_DR_PLAYBACK_STOPPED;
			}
			else if(IPOD_PAUSED == lStatus)
			{
				pPlayInfo->m_PlayStatus = IPOD_STATUS_PAUSED;
				pPlayInfo->Rd_playStatus = IPOD_DR_PLAYBACK_PAUSED;
			}
			else if(IPOD_PLAYING == lStatus)
			{
				pPlayInfo->m_PlayStatus = IPOD_STATUS_PLAYING;
				pPlayInfo->Rd_playStatus = IPOD_DR_PLAYING;
			}
			else
			{
				; /* No statement */
			}
		}
	}


}

/**************************************************************************
*	Function : IPOD_Display_Init
*
*	Description : This function send the bitmap data to iPod to display it.
*				
*	Parameter :
*			- iPod_Handle
*			- Block : Block number (It just used on TCC800X serises )
*
*  	Return : none
*
**************************************************************************/
int IPOD_Display_Init(void *iPod_Handle, unsigned int Block)
{
	int ret = -1;
	IPOD_PIXEL_FORMAT format;
	int height, width;
	IPOD_ERROR Err;
	MLingoType supportMultiLingo;
	
	(void)IPOD_API_GetSupportMultiLingo(iPod_Handle, &supportMultiLingo);
	IPOD_API_SetSkipProcessMode(1);
	if(supportMultiLingo & ML_REMOTE_UI_EXTENDED)
	{
		IPOD_CheckPlayStatus(iPod_Handle);

		Err = IPOD_GetColorDisplayLimit(iPod_Handle, &format, &width, &height );
		if(IPOD_NO_ERROR == Err)
		{
			Err = IPOD_SetBitmap(iPod_Handle, IPOD_PIXEL_MONOCHROME, 96, 50, IPOD_Bitmap);
			if(IPOD_NO_ERROR == Err)
			{
				ret = 1;
			}

		}
	}

	IPOD_API_SetSkipProcessMode(0);
	
	return ret;
}

/**************************************************************************
*	Function : IPOD_SetFileNum
*
*	Description : This function set the current / Total file number of iPod.
*				
*	Parameter :
*			- CurFileNum : Current file name
*			- TotalFileNum : Total File name
*			- pPlaybackInfo : 
*
*  	Return : none
*
**************************************************************************/
void IPOD_SetFileNum(long CurFileNum, long TotalFileNum, pIPOD_PLAY_INFO pPlayInfo)
{
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
	pPlayInfo->CurrentIdx = CurFileNum;
	pPlayInfo->TotalPlayNum = TotalFileNum;

	TotalMusicFileNum = TotalFileNum;
	UI_API_SetCurrFileNum(CurFileNum+1);
	UI_API_SetTotalFileNum(TotalFileNum);
#endif /* defined(TCC860x) || defined(TCC83XX) || defined(TCC78X) */

#ifdef TCC80XX
	pPlayInfo->CurrentIdx = (unsigned int)CurFileNum;
	pPlayInfo->TotalPlayNum = (unsigned int)TotalFileNum;
#endif
}

/**************************************************************************
*	Function : IPOD_GetCuriPodInfo
*
*	Description : This function returns the current / Total file number of iPod.
*				
*	Parameter :
*			- iPod_Handle : iPod Handle
*			- CurFileNum : Current File name
*			- TotalFileNum : Total File name
*			- CurTime : Current time 
*
*  	Return : none
*
**************************************************************************/
void IPOD_GetCuriPodInfo(void *iPod_Handle, long *CurFileNum, long *TotalFileNum, long *CurTime)
{
	pIPOD_PLAY_INFO pPlayInfo = IPOD_Get_AudioPlayInfo(iPod_Handle);

	if(pPlayInfo != 0)
	{
		*CurFileNum = (long)pPlayInfo->CurrentIdx;
		*TotalFileNum = (long)pPlayInfo->TotalPlayNum;
		*CurTime = (long)pPlayInfo->TimePosition_ms/1000;
	}

	return;
}

/**************************************************************************
*	Function : IPOD_Display_No_SongMsg
*
*	Description : This functin displays "No Song" on Accessory display.
*				
*	Parameter : none
*
*  	Return : none
*
**************************************************************************/
static void IPOD_Display_No_SongMsg(void *iPod_Handle)
{
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
	UI_API_DrawPopUp2Line_withoutTimeout("IPOD Init!", "No Song" );
/*	IPOD_Callback_TimeDly(200);*/
#endif
#ifdef TCC80XX
	pIPOD_PLAY_INFO pInfo;
	pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(iPod_Handle);
	
	DMP_MessageEvtUpdateNoSong((int)pInfo->Disk);
#endif
}

/**************************************************************************
*	Function : IPOD_SetPlayTime
*
*	Description : This functin set current play time from iPod.
*				
*	Parameter : 
*		Time : time info
*		drv_type : device type
*		pPlayInfo : iPod extention info
*
*  	Return : none
*
**************************************************************************/
static void IPOD_SetPlayTime(unsigned int Time, pIPOD_PLAY_INFO pPlayInfo)
{
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
	UI_API_SetPlayTime(Time);
#endif

#ifdef TCC80XX
	pPlayInfo->TimePosition = Time * 1000;
#endif

}

/**************************************************************************
*	Function : IPOD_SetPartionID
*
*	Description : This functin set the iPod partion ID
*				
*	Parameter : none.
*
*  	Return : none.
*
**************************************************************************/
static void IPOD_SetPartionID(void)
{
	#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
	g_Part_ID = IPOD_DEVICE_PARTID;
	#endif
}

/**************************************************************************
*	Function : IPOD_API_GetDisplayDataSize
*
*	Description : This functin get display data size
*				
*	Parameter : none.
*
*  	Return : Display data size.
*
**************************************************************************/
static unsigned int IPOD_API_GetDisplayDataSize(void)
{
	unsigned int lDisplayDataSize = 0;

#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
	lDisplayDataSize = 0;
#endif

#ifdef TCC80XX
#ifdef USE_DISPLAY_OBJECT
	lDisplayDataSize = 2*PLAYER_ALBUM_IMAGE_WD*PLAYER_ALBUM_IMAGE_HT;
#else
	lDisplayDataSize = 2*LCD_UI_WIDTH*LCD_UI_HEIGHT;
#endif
#endif

#ifdef WINCE
	lDisplayDataSize = 240*240*2;//(64*1024);
#endif

	return lDisplayDataSize;
}

/**************************************************************************
*	Function : IPOD_API_InitArtworkInfo
*
*	Description : This functin set display limit
*				
*	Parameter : 
*		- pPlayInfo
*
*  	Return : none.
*
**************************************************************************/
void IPOD_API_InitArtworkInfo(pIPOD_PLAY_INFO pPlayInfo)
{
	pIPOD_ARTWORK_INFO pArtworkInfo = &(pPlayInfo->ArtworkInfo);
	unsigned int DisplayDataSize;

	DisplayDataSize = IPOD_API_GetDisplayDataSize();

	if(DisplayDataSize > (IPOD_RXBUFSIZE -20))
	{
		DisplayDataSize = (IPOD_RXBUFSIZE -20);
	}

	pArtworkInfo->MaxDisplaySize = DisplayDataSize;
	pArtworkInfo->BasicFormatID = -1;
	memset(pArtworkInfo->CapableFormatID, -1, sizeof(unsigned int)*IPOD_MAX_ARTWORK);
	pArtworkInfo->MaxFormatCount= 0;
	
}

/**************************************************************************
*	Function : IPOD_GetDefaultArtworkFormatID
*
*	Description : This functin returns default artwork formatID
*				
*	Parameter : iPod_Handle.
*
*  	Return : none.
*
**************************************************************************/
int IPOD_GetDefaultArtworkFormatID(void *iPod_Handle)
{
	pIPOD_PLAY_INFO pInfo;
	unsigned int Ret = -1;
	
	pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(iPod_Handle);

	if(pInfo != 0)
	{
		Ret = pInfo->ArtworkInfo.BasicFormatID;
	}

	return (int)Ret;
}

/**************************************************************************
*	Function : IPOD_SetDefaultArtworkFormatID
*
*	Description : This functin set basic artwork format
*				
*	Parameter : none.
*
*  	Return : none.
*
**************************************************************************/
IPOD_ERROR IPOD_SetDefaultArtworkFormatID(void *iPod_Handle, unsigned long Lingo)
{
	IPOD_ERROR Err;
	long ActualLen;
	int FrameID;
	ArtworkFormat pformat[IPOD_MAX_ARTWORK];
	unsigned int displaysize, MaxDisplaysize;
	unsigned int currentDisplaysize = 0;
	pIPOD_PLAY_INFO pPlayInfo = IPOD_Get_AudioPlayInfo(iPod_Handle);
	pIPOD_ARTWORK_INFO pArtworkInfo = &(pPlayInfo->ArtworkInfo);

	MaxDisplaysize = pArtworkInfo->MaxDisplaySize;
	pArtworkInfo->BasicFormatID = 0;

	if(ML_REMOTE_UI_EXTENDED == Lingo)
	{
		/* In case of Extended Lingo - Default */
		Err = IPOD_GetAlbumArtFormats(iPod_Handle, &pformat[0], IPOD_MAX_ARTWORK, &ActualLen);
	}
	else if(ML_DISPLAY_REMOTE == Lingo)
	{
		/* In case of Display Remote Lingo */
		Err = IPOD_DR_GetArtworkFormats(iPod_Handle, &pformat[0], IPOD_MAX_ARTWORK, &ActualLen);
	}
	else
	{
		Err = IPOD_INVALID_PARAM;
	}
	if(IPOD_NO_ERROR == Err)
	{
		pArtworkInfo->MaxFormatCount = (unsigned int)ActualLen;
		
		for(FrameID=0; FrameID<ActualLen; FrameID++)
		{
			if((RGB565_LITTLE_ENDIAN_16BPP == pformat[FrameID].PixelFormat))
			/*	||(RGB565_BIG_ENDIAN_16BPP == pformat[FrameID].PixelFormat)) */
			{
				displaysize = (unsigned int)((pformat[FrameID].ImageWidth *2)*(pformat[FrameID].ImageHeight));
				if(displaysize <= MaxDisplaysize)
				{
					pArtworkInfo->CapableFormatID[FrameID] = (unsigned int)pformat[FrameID].FormatID;
					pArtworkInfo->CapableSize[FrameID] = displaysize;
					
					if(currentDisplaysize < displaysize)
					{
						currentDisplaysize = displaysize;
						pArtworkInfo->BasicFormatID = (unsigned int)pformat[FrameID].FormatID;
					}

				}
				else
				{
					pArtworkInfo->CapableFormatID[FrameID] = -1;
					pArtworkInfo->CapableSize[FrameID] = -1;
				}

			}
			
		}

	}
	return Err;

}

/**************************************************************************
*	Function : IPOD_DB_Init
*
*	Description : This functin set the iPod DB state and get a Total file / Current file / current Time
*				
*	Parameter : 
*		- pPlaybackInfo
*
*  	Return : none
*
**************************************************************************/
int IPOD_DB_Init(void *iPod_Handle)
{
	int ret = -1;
	int i, lTotalTrackLength, lTime;
	IPOD_PLAYBACK_STATUS lStatus;
	long TotalFileNum = 0;
	IPOD_ERROR Err = IPOD_INVALID_PARAM;
//	unsigned int Evtoption = IPOD_EVT_EXTENDED_PLAY_STATUS_CHANGES | IPOD_EVT_TRACK_INDEX | IPOD_EVT_TRACK_TIME_OFFSET_MSEC
//							|IPOD_EVT_CHAPTER_OFFSET_SEC|  IPOD_EVT_TRACK_MEDIA_TYPE;
//	unsigned int Evtoption = ENABLENOTIFICATION;

	/*For Display Remote*/
	unsigned int Ex_Evtoption = (0x01);
	unsigned int DR_Evtoption = (0x18F);

	unsigned long long eventNotiMask;
	unsigned int maxPayload;

	long CurrentIndx;
	pIPOD_PLAY_INFO pPlayInfo;
	
	MLingoType supportMultiLingo;
	IPOD_API_SetSkipProcessMode(1);
	(void)IPOD_API_GetSupportMultiLingo(iPod_Handle, &supportMultiLingo);

	pPlayInfo = IPOD_Get_AudioPlayInfo(iPod_Handle);

	if(pPlayInfo != 0)
	{
		#ifdef IPOD_NUCLUES
		for(i=0; i<5; i++)
		{
			(void) IPOD_ProcessiPodEvent(iPod_Handle);
		}
		#endif

		IPOD_SetFileNum(0,0, pPlayInfo);

		/* This command is executed on iPod_displayinit function.*/
		//Err = IPOD_GetStatus(iPod_Handle, &lTotalTrackLength, &lTime, &lStatus);
		//if(IPOD_NO_ERROR == Err)
		if(supportMultiLingo & ML_REMOTE_UI_EXTENDED)
		{
			ShuffleMode shuffle;
			CurrentRepeatState repeat;
			lStatus =  pPlayInfo->m_PlayStatus;

			lTotalTrackLength = pPlayInfo->TotalTime;
			lTime = pPlayInfo->TimePosition;

			
			if(lStatus == IPOD_STATUS_STOPPED)
			{
				pPlayInfo->m_PlayStatus = IPOD_STATUS_STOPPED;
				
				pPlayInfo->TotalVideos = IPOD_GetVideoTracksCnt(iPod_Handle);
				TotalFileNum = IPOD_SelectFileList(iPod_Handle);
				if(TotalFileNum == 0)
				{
					IPOD_Display_No_SongMsg(iPod_Handle);
					// Ã»ÓÐ¸èÇú
				}
				else
				{
					(void)IPOD_SelectList(iPod_Handle, IPOD_LIB_TRACK, 0);
					(void) IPOD_ButtonControl(iPod_Handle, PLAYPAUSE);
				}
			}
			else
			{
				pPlayInfo->m_PlayStatus = IPOD_STATUS_PAUSED;
				if(lTime != 0)
				{
					lTime = (int)((unsigned int)lTime/1000);
				}	
				IPOD_SetPlayTime((unsigned int)lTime, pPlayInfo);
				(void) IPOD_GetNumPlayingTracks(iPod_Handle, &TotalFileNum);
			}
			pPlayInfo->TotalTime = lTotalTrackLength;

			//set repeat mode
			Err = IPOD_GetRepeat(iPod_Handle, &repeat);
			if(IPOD_NO_ERROR == Err)
			{
				if (REPEATALLTRACKS != repeat)
				{
					Err = IPOD_SetRepeat(iPod_Handle, REPEATALLTRACKS, RESTORE_ORG_SETTING);
					repeat = REPEATALLTRACKS;
				}
				pPlayInfo->RepeatStatus = (unsigned char)repeat;
			}

			//set Shuffle mode
			Err = IPOD_GetShuffle(iPod_Handle, &shuffle);
			if(IPOD_NO_ERROR == Err)
			{
				if (SHUFFLEOFF != shuffle)
				{
					Err = IPOD_SetShuffle(iPod_Handle, SHUFFLEOFF, RESTORE_ORG_SETTING);
					shuffle = SHUFFLEOFF;
				}
				pPlayInfo->ShuffleStatus = (unsigned char)shuffle;
			}

			IPOD_SetPartionID();

			if(TotalFileNum > 0)
			{
				Err = IPOD_GetCurrentFileNum(iPod_Handle, &CurrentIndx);
				if(IPOD_NO_ERROR == Err)
				{
					IPOD_SetFileNum(CurrentIndx, TotalFileNum, pPlayInfo);
				}
			}
			/*ATS2.2 Accessory sent GetPlayStatus without first attempting SetPlayStatusChangenotification with bit 0 set*/
			(void)IPOD_Enable_event(iPod_Handle, Ex_Evtoption, 1);
			
			Err = IPOD_DR_SetRemoteEventNoti(iPod_Handle, DR_Evtoption);
			(void)IPOD_SetDefaultArtworkFormatID(iPod_Handle, ML_REMOTE_UI_EXTENDED);
		}
		
		else if(supportMultiLingo & ML_DISPLAY_REMOTE)
		{
			Err = IPOD_DR_SetRemoteEventNoti(iPod_Handle, DR_Evtoption);
			(void)IPOD_SetDefaultArtworkFormatID(iPod_Handle, ML_DISPLAY_REMOTE);	
		}
	}


	if(IPOD_NO_ERROR == Err)
	{
		IPOD_API_SetStatus(iPod_Handle, IPOD_MOUNTED);
		ret = 1; /* DB Init Success */
	}
	
	IPOD_API_SetSkipProcessMode(0);

	return ret;
}

/**************************************************************************
*	Function : IPOD_ConvertSingleToMultiLingo
*
*	Description : This functin make pParam->IdentifyToken.ML_Lingo member variable.
*				
*	Parameter : 
*		- pParam : iPod initial parameter
*
*  	Return : none
*
**************************************************************************/
MLingoType IPOD_ConvertSingleToMultiLingo(const IPOD_INIT_PARAM *pParam)
{
	MLingoType lLingo = 0x00;
	unsigned int Add_Lingo;
	int i;
	
	for(i=0; i<(int)(pParam->IdentifyToken.LingoCnt); i++)
	{
		switch(pParam->IdentifyToken.Lingos[i])
		{
			case(LINGO_GENERAL):
				Add_Lingo = ML_GENERAL;
				break;

			case(LINGO_MICROPHONE):
				Add_Lingo = ML_MICROPHONE;
				break;

			case(LINGO_SIMPLE_REMOTE):
				Add_Lingo = ML_SIMPLE_REMOTE;
				break;
				
			case(LINGO_DISPLAY_REMOTE):
				Add_Lingo = ML_DISPLAY_REMOTE;
				break;
				
			case(LINGO_EXTENDED_INTERFACE):
				Add_Lingo = ML_REMOTE_UI_EXTENDED;
				break;

			case(LINGO_RF_TUNER):
				Add_Lingo = ML_RF_TRANSMITTER;
				break;

			case(LINGO_DIGITAL_AUDIO):
				Add_Lingo = ML_DIGITAL_AUDIO;
				break;

			case(LINGO_STORAGE):
				Add_Lingo = ML_STORAGE;
				break;

			default:
				Add_Lingo = 0;
				break;
		}
		lLingo |= Add_Lingo;


	}
//	return (ML_GENERAL | Lingo);
	return (lLingo);
}

/**************************************************************************
*	Function : IPOD_Callback_TimeDly
*
*	Description : This function is callback function of iPod library 
*				
*	Parameter : 
*		- ticks : 
*
*  	Return : none
*
**************************************************************************/
unsigned int IPOD_Callback_TimeDly(void *ExtInfo, unsigned short ticks)
{
	unsigned int i;
	
	for(i=0; i<ticks; i++)
	{
		if(IPOD_GetDetectStatus(ExtInfo) == IPOD_DISCONNECTED)
		{
			break;
		}
		else
		{
			#ifdef IPOD_NUCLUES
			TC_TimeDly(1);
			#endif
			#ifdef WINCE
			Sleep(5);
			#endif
		}
	}

	return i;
}

/**************************************************************************
*	Function : IPOD_Get_Oneword
*
*	Description : This function returns one word from iPod receive buffer.
*				
*	Parameter : 
*		- Data : data pointer
*
*  	Return : one word data
*
**************************************************************************/
unsigned int IPOD_Get_Oneword(const unsigned char *Data)
{
	unsigned int RetData = NULL;

	if(Data != 0)
	{
		RetData = ((unsigned int)Data[0] << 24) & 0xFF000000U;
		RetData |= ((unsigned int)Data[1] << 16) & 0xFF0000U; 
		RetData |= ((unsigned int)Data[2] << 8) & 0xFF00U;
		RetData |= (unsigned int)Data[3] & 0xFFU;
	}

	return RetData;

}

/**************************************************************************
*	Function : IPOD_Get_Short
*
*	Description : This function returns short size data from iPod receive buffer.
*				
*	Parameter : 
*		- Data : data pointer
*
*  	Return : short data
*
**************************************************************************/
unsigned short IPOD_Get_Short(const unsigned char *Data)
{
	unsigned short RetData = NULL;

	if(Data !=0)
	{
		RetData = ((unsigned short)Data[0] << 8) & 0xFF00U;
		RetData |= (unsigned short)Data[1] & 0xFFU;
		
	}

	return RetData;

}

/**************************************************************************
*	Function : IPOD_UpdateTimeInfo
*
*	Description : This function update the current time information
*				
*	Parameter : 
*		- TimePosition : current Time value.
*
*  	Return : none
*
**************************************************************************/
static void IPOD_UpdateTimeInfo(unsigned int TimePosition, unsigned int Disk)
{

#if (defined(TCC860x) || defined(TCC78X) || defined(TCC83XX))

	#ifdef TCLINK_UART_PC_SIMULATOR_INCLUDE
	if(TimePosition != PlaySec)
	{
		PlaySec = TimePosition;
		TCLS_EVT_PlayStatusChanged( TCL_PBS_CURRENTTIME, TimePosition, NULL );
	}
	#endif
	
	#ifdef CD_RIPPING_INCLUDE
	if(((g_Current_ID == PLAY_ID) || (g_Current_ID == RIPPING_ID)) && (IPOD_Navi_Access == 1))
	#else
	if((g_Current_ID == PLAY_ID) && (IPOD_Navi_Access == 1))
	#endif
	{
		if(TimePosition != PlaySec)
		{
			PlaySec = TimePosition;
			//UI_API_Set_UiLCDUpdataFlag(UI_LCD_UPDATE_PLAYTIME);
			//IPOD_Navi_Access = 0;
			UI_FNT_DrawPlayTimeInPlay();
			//IPOD_Navi_Access = 1;
		}
	}
#endif /*defined(TCC860x) || defined(TCC78X) || defined(TCC83XX)*/


#if defined(TCC80XX)
	pPLAYBACK_INFO pPlayback;
	unsigned char loc;

	loc = DMP_GetLocationByDisk((unsigned char)Disk);
	if(loc < MAX_PLAYBACK_INFO)
	{
		pPlayback = MP_GetPlayback((int)loc);
		if ((pPlayback->mIPOD_Access != 0) && (TimePosition != pPlayback->mPlaySec))
		{
			UI_DRV_SetPlaySec(pPlayback, TimePosition);
		}
	}
#endif /*defined(TCC80XX)*/




}

/**************************************************************************
*	Function : DMP_IPOD_DisplayAlbumArt
*
*	Description : This function display of current track(new updated) albumArt data of iPod.
*				
*	Parameter : 
*		- new_index : index
*
*  	Return : none
*
**************************************************************************/
void DMP_IPOD_DisplayAlbumArt(int new_index, int loc)
{
#if defined(TCC80XX)
#if defined(_LCD_CPU_COLOR_) && defined(STILLIMAGE_INCLUDE)
	if(loc == FIRST_PLAYBACK) /* Only display for front-playback */
	{
		void *iPod_Handle;
		IPOD_ERROR Err;
		long ActualLen;
		ArtworkData stArtData;
		unsigned long ImageLen;

#ifdef USE_DISPLAY_OBJECT
		static unsigned char *pAlbumArtBuf = NULL;
		ImageLen = 2*PLAYER_ALBUM_IMAGE_WD*PLAYER_ALBUM_IMAGE_HT;
#else
		ImageLen = 2*LCD_UI_WIDTH*LCD_UI_HEIGHT;
#endif
		stArtData.pImageData = TC_Allocate_Memory(ImageLen);

		if (stArtData.pImageData != NULL)
		{
			iPod_Handle = DISK_GetHandle(MP_GetPlayback(loc)->mCurrentDisk);
			
			Err = IPOD_GetAlbumArt(iPod_Handle, new_index, &stArtData, ImageLen, &ActualLen);
			if (IPOD_NO_ERROR == Err)
			{
#ifdef USE_DISPLAY_OBJECT
				if(pAlbumArtBuf == NULL)
				{
				#ifdef USE_DO_FORMAT_RGB888
					pAlbumArtBuf = TC_Allocate_Memory(ImageLen*2);
				#else
					pAlbumArtBuf = TC_Allocate_Memory(ImageLen);
				#endif
				}

				#ifdef USE_DO_FORMAT_RGB888
				memset(pAlbumArtBuf, 0x00, ImageLen*2);
				TCGL_RGB565ToRGB888((PLAYER_ALBUM_IMAGE_WD-stArtData.sWidth)>>1, (PLAYER_ALBUM_IMAGE_HT-stArtData.sHeight)>>1, stArtData.sWidth, stArtData.sHeight, 0, 0, stArtData.sWidth, stArtData.sHeight, stArtData.pImageData, 0, 0, PLAYER_ALBUM_IMAGE_WD, PLAYER_ALBUM_IMAGE_HT, pAlbumArtBuf);
				#else
				memset(pAlbumArtBuf, 0x00, ImageLen);
				TCGL_DrawBitmapRect((PLAYER_ALBUM_IMAGE_WD-stArtData.sWidth)>>1, (PLAYER_ALBUM_IMAGE_HT-stArtData.sHeight)>>1, stArtData.sWidth, stArtData.sHeight, 0, 0, stArtData.sWidth, stArtData.sHeight, stArtData.pImageData, 0, 0, lSpace, pAlbumArtBuf);
				#endif
				DMP_MessageEvtDirectUpdateAlbumImage(MP_GetPlayback(loc)->mCurrentDisk, pAlbumArtBuf);
#else
				GDI_Bitmap(stArtData.pImageData, stArtData.sTopLeftX, stArtData.sTopLeftY,
				           stArtData.sWidth, stArtData.sHeight, GDI_GetUIFrameBuf(loc));
#endif
			}
			else
			{
#ifdef USE_DISPLAY_OBJECT
				TC_Deallocate_Memory(pAlbumArtBuf);
				pAlbumArtBuf = NULL;
				DMP_MessageEvtDirectUpdateAlbumImage(MP_GetPlayback(loc)->mCurrentDisk, pAlbumArtBuf);
#else
				GDI_FillBox(0, 0, 176, 140, COLOR_BLACK, GDI_GetUIFrameBuf(loc));
#endif
			}

			(void) TC_Deallocate_Memory(stArtData.pImageData);
			stArtData.pImageData = NULL;
		}
	}
#endif
#endif /*defined(TCC80XX)*/
}

/**************************************************************************
*	Function : IPOD_UpdateTrackInfo
*
*	Description : This function update the new track information.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*		- CurrentIdx : new track index.
*
*  	Return : none
*
**************************************************************************/
static void IPOD_UpdateTrackInfo(const IPOD_PLAY_INFO *pInfo/*unsigned int CurrentIdx*/, unsigned int Disk)	/* QAC : 16.7 */
{
#if (defined(TCC860x) || defined(TCC78X) || defined(TCC83XX))
	unsigned int CurrentIdx = pInfo->CurrentIdx;

	#ifdef TCLINK_UART_PC_SIMULATOR_INCLUDE
//	IPOD_GetCurrentFileNum(DISK_GetHandle(gCurrentDisk), &index);
	TCLS_EVT_PlayStatusChanged( TCL_PBS_CURRENTOBJECT, ((CurrentIdx)+1), NULL );
	#endif
	
	if((g_Current_ID == PLAY_ID) && (IPOD_Navi_Access == 1) && (CurrentFileNum != (CurrentIdx+1)))
	{

		#if 0
		//UI_API_Set_UiLCDUpdataFlag( UI_LCD_UPDATE_TRACKNUM | UI_LCD_UPDATE_FILENUM );
		UI_FNT_DrawCurrTrackNumberInPlay();
		UI_FNT_DrawCurrFolderNameInPlay();
		//CurrentFileNum = new_index + 1;
		UI_DRV_GetMusicFileInfo();
		SCR_RestartScroll();
		#else
		UI_API_Set_UiLCDUpdataFlag(UI_LCD_UPDATE_ALL);
	//	UI_API_Set_UiLCDUpdataFlag(UI_LCD_UPDATE_TRACKNUM | UI_LCD_UPDATE_FILENUM | UI_LCD_UPDATE_FILENAME | UI_LCD_UPDATE_FOLDERNAME);
		#endif
	}
#endif /*defined(TCC860x) || defined(TCC78X) || defined(TCC83XX)*/


#if defined(TCC80XX)

#if 0

	IPOD_API_SetTrackChanged(pInfo->CurrentIdx+1, pInfo->TotalPlayNum, Disk);
	IPOD_API_SetTrackChangeProcess();

#else
	pPLAYBACK_INFO pPlayback;
	unsigned char loc;
	unsigned int CurrentIdx = pInfo->CurrentIdx;

	loc = DMP_GetLocationByDisk((unsigned char)Disk);
	if(loc < MAX_PLAYBACK_INFO)
	{
		pPlayback = MP_GetPlayback((int)loc);
		if ((pPlayback->mIPOD_Access != 0) && (pPlayback->mCurrentFileNum != (CurrentIdx+1)))
		{
			UI_DRV_SetCurrentFileNum(pPlayback, (unsigned short)(CurrentIdx+1));
			
	// 		TODO : Please add event to UI task to update the albumart data.
	//		below code is remarked. Please refer to the IMPORTANT NOTICE.
	//		DMP_IPOD_DisplayAlbumArt(CurrentIdx, pPlayback->mLocation);
		}
	}
#endif
#endif /*defined(TCC80XX)*/

}

/**************************************************************************
*	Function : IPOD_UpdateFFSeekStopInfo
*
*	Description : This function update the FF seek stop information.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*		- CurrentIdx : new track index.
*
*  	Return : none
*
**************************************************************************/
static void IPOD_UpdateFFSeekStopInfo(unsigned int Disk)
{
#if defined(TCC860x)
	if((IPOD_Navi_Access == 1) /*&& (CurrentFileNum != (CurrentIdx+1))*/)
	{
		TCCAPI_Timer_CancelTime( TIMER_IPOD_UPDATE_INFO_ID );
		TCCAPI_Timer_SetTime( 2, TIMER_IPOD_UPDATE_INFO_ID, CMD_DemonIpodUpdateInfoFFSeekStopNoSyncFnc );
	}
#elif (defined(TCC78X) || defined(TCC83XX))
	/* To be implemented */
#elif defined(TCC80XX)
	/* To be implemented */
#endif /*defined(TCC80XX)*/
}

/**************************************************************************
*	Function : IPOD_UpdateREWSeekStopInfo
*
*	Description : This function update the REW seek stop information.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*		- CurrentIdx : new track index.
*
*  	Return : none
*
**************************************************************************/
static void IPOD_UpdateREWSeekStopInfo(unsigned int Disk)
{
#if defined(TCC860x)
	if((IPOD_Navi_Access == 1) /*&& (CurrentFileNum != (CurrentIdx+1))*/)
	{
		TCCAPI_Timer_CancelTime( TIMER_IPOD_UPDATE_INFO_ID );
		TCCAPI_Timer_SetTime( 2, TIMER_IPOD_UPDATE_INFO_ID, CMD_DemonIpodUpdateInfoREWSeekStopNoSyncFnc );
	}
#elif (defined(TCC78X) || defined(TCC83XX))
	/* To be implemented */
#elif defined(TCC80XX)
	/* To be implemented */
#endif /*defined(TCC80XX)*/
}

/**************************************************************************
*	Function : IPOD_Callback_GetReturnPlayInfo
*
*	Description : This function updated all informatin of new contents. 
*				callback function of iPod library.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*		- ExtInfo : 
*
*  	Return : none
*
**************************************************************************/
int IPOD_Callback_GetReturnPlayInfo(void *ExtInfo)
{
	int ret = 0;
	pIPOD_PLAY_INFO pInfo;
	unsigned int lDisk;

	if(ExtInfo != 0)
	{
		pInfo = (pIPOD_PLAY_INFO)ExtInfo;	
		lDisk = (unsigned int)pInfo->Disk;

		ret= (int)IPOD_RX_Cmd.Data[0];
		
		switch(ret)
		{
			case STOPPED://0x00
				pInfo->m_PlayStatus = IPOD_STATUS_STOPPED;
				break;
				
			case TRACKCHANGED://0x01
				pInfo->CurrentIdx = IPOD_Get_Oneword(&IPOD_RX_Cmd.Data[1]);
				IPOD_UpdateTrackInfo(pInfo, (unsigned int)lDisk);
				break;
				
			case FFSEEKSTOP://0x02
				pInfo->m_PlayStatus = IPOD_STATUS_PLAYING;
				IPOD_UpdateFFSeekStopInfo((unsigned int)lDisk);
				break;
				
			case REWSEEKSTOP://0x03
				pInfo->m_PlayStatus = IPOD_STATUS_PLAYING;
				IPOD_UpdateREWSeekStopInfo((unsigned int)lDisk);
				break;
				
			case TRACKPOSITION: /* MiliSecond*/
				pInfo->TimePosition = IPOD_Get_Oneword(&IPOD_RX_Cmd.Data[1]);
				IPOD_UpdateTimeInfo(pInfo->TimePosition/1000, (unsigned int)lDisk);
				break;

			case CHAPTERINDEX:
				pInfo->ChapterIdx = IPOD_Get_Oneword(&IPOD_RX_Cmd.Data[1]);
				break;

			case PLAYBACK_STATUS_EXT:
				pInfo->m_PlayStatus = (IPOD_PLAYBACK_STATUS)IPOD_RX_Cmd.Data[1];
				break;

			case TRACKTIME_OFFSET: /* Second */
				pInfo->TimePosition = IPOD_Get_Oneword(&IPOD_RX_Cmd.Data[1]);
				IPOD_UpdateTimeInfo(pInfo->TimePosition, (unsigned int)lDisk);
				break;

			case CHAPTER_TIME_OFFSET_MSEC:
				break;

			case CHAPTER_TIME_OFFSET_SEC:
				pInfo->ChapterTimePosition = IPOD_Get_Oneword(&IPOD_RX_Cmd.Data[1]);
				break;

			case TRACK_UNIQUE_ID:
				break;

			case TRACK_PLAYBACK_MODE:
				pInfo->PlayBackMode= (IPOD_PLAYBACK_MODE)IPOD_RX_Cmd.Data[1];
				break;

			case TRACK_LYRICS_READY:
				break;

			default:
				break;
		}
	}
	return 0;
}


/**************************************************************************
*	Function : IPOD_Callback_DisplayRemoteEvent
*
*	Description : This function updated all informatin of new contents. 
*				callback function of iPod library.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*		- ExtInfo : 
*
*  	Return : none
*
**************************************************************************/
int IPOD_Callback_DisplayRemoteEvent(unsigned char EventNum, const unsigned char *pData, void *ExtInfo)
{
//	int ret = 0;
	pIPOD_PLAY_INFO pInfo;
	unsigned int lDisk;
	int DevNo;
	void *Handle;

	if(0 != ExtInfo)
	{
		pInfo = (pIPOD_PLAY_INFO)ExtInfo;	
		lDisk = (unsigned int)pInfo->Disk;

		switch(EventNum)
		{

			case IPOD_DR_EVT_TRACK_POSITION:
				pInfo->TimePosition_ms = IPOD_Get_Oneword(pData);
				IPOD_UpdateTimeInfo(pInfo->TimePosition_ms/1000, lDisk);
				break;
				
			case IPOD_DR_EVT_TRACK_INDEX:
				pInfo->CurrentIdx = IPOD_Get_Oneword(pData);
				IPOD_UpdateTrackInfo(pInfo, (unsigned int)lDisk);
				break;
				
			case IPOD_DR_EVT_CHAPTER_INFO:
				pInfo->CurrentIdx = IPOD_Get_Oneword(pData);
				pInfo->ChapterCnt = IPOD_Get_Short(&pData[4]);
				pInfo->ChapterIdx = (unsigned long)IPOD_Get_Short(&pData[6]);
				break;
				
			case IPOD_DR_EVT_PLAY_STATUS:
				pInfo->Rd_playStatus = (IPOD_DR_PLAY_STATUS)pData[0];
				#ifdef IPOD_NUCLUES
				if(IPOD_FFREW_Flag)
				{
					if((IPOD_DR_PLAYING==pInfo->Rd_playStatus) || (IPOD_DR_PLAYBACK_PAUSED == pInfo->Rd_playStatus))
					{
						IPOD_ButtonControl_EndFFREWinCallback(Handle, ENDFFREW);
						IPOD_FFREW_Flag = 0;
					}
				}
				#endif
				break;
				
			case IPOD_DR_EVT_MUTE_UI_VOL:
				pInfo->MuteState = pData[0];
				pInfo->UIvolLevel = pData[1];
				break;
				
			case IPOD_DR_EVT_POWER_BATTERY:
				pInfo->PowerStatus = pData[0];
				pInfo->BatteryLevel = pData[1];
				break;
				
			case IPOD_DR_EVT_EQALIZER_STATE:
				pInfo->EqStatus = IPOD_Get_Oneword(pData);
				break;
				
			case IPOD_DR_EVT_SHUFFLE:
				pInfo->ShuffleStatus = pData[0];
				break;
				
			case IPOD_DR_EVT_REPEAT:
				pInfo->RepeatStatus = pData[0];
				break;
				
			case IPOD_DR_EVT_DATE_TIME:
				pInfo->Year = IPOD_Get_Short(pData);
				pInfo->Month = pData[2];
				pInfo->Day = pData[3];
				pInfo->Hour = pData[4];
				pInfo->Minute = pData[5];
				break;
				
			case IPOD_DR_EVT_ALARM:
				pInfo->AlarmStatus = pData[0];
				pInfo->AlarmHour = pData[1];
				pInfo->AlarmMin = pData[2];
				break;
				
			case IPOD_DR_EVT_BACKLIGHT:
				pInfo->BackLight = pData[0];
				break;
				
			case IPOD_DR_EVT_HOLD_SWITCH:
	//			SerialWriteString("Hold Key Event Updated\n\r");
				pInfo->Holdswitch = pData[0];
				break;
				
			case IPOD_DR_EVT_SOUND_CHECK:
				pInfo->SoundCheck= pData[0];
				break;
				
			case IPOD_DR_EVT_AUDIOBOOK:
				pInfo->AudioBook = pData[0];
				break;
				
			case IPOD_DR_EVT_TRACK_POSITION_IN_SECONDS:
				pInfo->TimePosition = IPOD_Get_Short(pData);
				IPOD_UpdateTimeInfo(pInfo->TimePosition, lDisk);
	//			SerialWriteString("Time Updated\n\r");
				break;
				
			case IPOD_DR_EVT_MUTE_UI_ABSOLUTE_VOL:
				pInfo->MuteState = pData[0];
				pInfo->UIvolLevel = pData[1];
				pInfo->AbsoluteVol = pData[2];
				break;

			case IPOD_DR_EVT_TRACK_CAPABILITIES:
				//pInfo->CapabilitiesInfo = IPOD_Get_TrackCapabilities(pData); /*This function was removed*/
				break;
				
			case IPOD_DR_EVT_PLAYBACK_ENGINE_CONTENTS_CHANGED:
				pInfo->TotalPlayNum = IPOD_Get_Oneword(pData);
				break;
								
			default:
				break;
		}
	}
	return 0;
}


/**************************************************************************
*	Function : IPOD_Callback_GetWaitTimeMount
*
*	Description : This function returns mount command timeout value.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*
*  	Return : none
*
**************************************************************************/
unsigned int IPOD_Callback_GetWaitTimeMount(void)
{
#ifdef WINCE
	return IPOD_1MS_TIMEOUT_MOUNT;
#else
	return IPOD_5MS_TIMEOUT_MOUNT;
#endif
}

/**************************************************************************
*	Function : IPOD_Callback_GetWaitTimeMount
*
*	Description : This function returns command timeout value.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*
*  	Return : none
*
**************************************************************************/
unsigned int IPOD_Callback_GetWaitTime(void)
{
#ifdef WINCE
	return IPOD_1MS_TIMEOUT;
#else
	return IPOD_5MS_TIMEOUT;
#endif	
}

/**************************************************************************
*	Function : IPOD_Callback_SetSamplerate
*
*	Description : This function set the sample frequency by new update track information.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*
*  	Return : none
*
**************************************************************************/
void IPOD_Callback_SetSamplerate(void *ExtInfo, unsigned int SamplingFrequency)
{
#ifdef IPOD_USB_INCLUDE

	pIPOD_PLAY_INFO pInfo;

	#if (defined(TCC80XX))
	DISK_DEVICE lDisk;
	#endif

	if(ExtInfo != 0)
	{
		pInfo = (pIPOD_PLAY_INFO)ExtInfo;	

	#if defined(TCC80XX)
		lDisk = (DISK_DEVICE)pInfo->Disk;
		if(DISK_GetState(lDisk) == DISK_STATE_MOUNTCOMPLETE)
		{
			unsigned char loc = DMP_GetLocationByDisk((unsigned char)lDisk);
			unsigned long ulMemory;
			unsigned long ulPlayback;

			if(loc == FIRST_PLAYBACK)
			{
				ulMemory = CodecMemory;
				ulPlayback = (unsigned long)MP_GetPlayback((int)loc);
				(void) CodecSetSampleRate(CODEC_USB_AUDIO, SamplingFrequency, ulMemory, ulPlayback, ExtInfo);
			}
			else if(loc == SECOND_PLAYBACK)
			{
				ulMemory = CodecMemory2;
				ulPlayback = (unsigned long)MP_GetPlayback((int)loc);
				(void) CodecSetSampleRate(CODEC_USB_AUDIO, SamplingFrequency, ulMemory, ulPlayback, ExtInfo);
			}
			else
			{
				USBAudio_SetSamplingFreq(ExtInfo, SamplingFrequency);
			}
	//		(void) CodecSetSampleRate(CODEC_USB_AUDIO, SamplingFrequency, ulMemory, ulPlayback, ExtInfo);
		}
		else
		{
			USBAudio_SetSamplingFreq(ExtInfo, SamplingFrequency);
		}
	#endif

	#if (defined(TCC78X) || defined(TCC83XX))
		CodecSetSampleRate(CODEC_USB_AUDIO, SamplingFrequency, ExtInfo);
	#endif

	#ifdef TCC860x

		if(CODEC_USB_AUDIO == CurrentCodec)
		{
			CodecSetSampleRate(SamplingFrequency, ExtInfo);
		}
		else
		{
			USBAudio_SetSamplingFreq(ExtInfo, SamplingFrequency);
		}
	#endif
	
	}
	
#endif /*IPOD_USB_INCLUDE*/
}
/**************************************************************************
*	Function : IPOD_Callback_EndAuthentication
*
*	Description : This function notify end of iPod authentication. 
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 	iPod_Handle
			IsSuccess(1) - iPod authentication success
			IsSuccess(0) - iPod authentication fail
*
*  	Return : none
*
**************************************************************************/
void IPOD_Callback_EndAuthentication(void* iPod_Handle, unsigned int IsSuccess)
{
	if(IsSuccess == 1)/*iPod authentication success*/
	{
	}
	else/*iPod authentication fail*/
	{
	}
}

/**************************************************************************
*	Function : IPOD_InitBuff
*
*	Description : This function initialize the iPod buffer.
*				usage : iPod initialization / authentication / UTF8 decode buffer / communication buffer
*						USB audio PCM buffer
*				
*	Parameter : 
*		- buffer
*
*  	Return : none
*
**************************************************************************/
void IPOD_InitBuff(pIPOD_BUF_PARAM buf_param, unsigned char *buffer)
{
	unsigned long lAddress;

	lAddress = (unsigned long)buffer;
	buf_param->CP_buffer = lAddress; // buffer for authentication IC. size : 50Kbytes
	buf_param->CP_buffer_size = IPOD_CPBUFSIZE;
	lAddress += IPOD_CPBUFSIZE;
	
	pIPOD_TxBuff = (unsigned char *)lAddress; // size :IPOD_TXBUFSIZE
	buf_param->Tx_buffer = (unsigned char *)lAddress; 
	buf_param->Tx_buffer_size = 	IPOD_TXBUFSIZE;
	lAddress += IPOD_TXBUFSIZE;

	pIPOD_RxBuff = (unsigned char *)lAddress; // size : IPOD_RXBUFSIZE
	buf_param->Rx_buffer = (unsigned char *)lAddress; 
	buf_param->Rx_buffer_size = 	IPOD_RXBUFSIZE;
	lAddress += IPOD_RXBUFSIZE;

	IPOD_RX_W_Ptr = 0;
	IPOD_RX_R_Ptr = 0;

	pIPOD_RXData  = (unsigned char *)lAddress; // size :IPOD_RXBUFSIZE
	buf_param->RxData_buffer = (unsigned char *)lAddress; 
	buf_param->RxData_buffer_size = 	IPOD_RXBUFSIZE;
	lAddress += IPOD_RXBUFSIZE;

	IPOD_UTF8DecodeBuffer = (unsigned char *)lAddress; // size :IPOD_RXBUFSIZE
	buf_param->UTF8DecodeBuffer = (unsigned char *)lAddress; 
	buf_param->UTF8DecodeBuffer_size = 	IPOD_RXBUFSIZE;
	lAddress += IPOD_RXBUFSIZE;
	// Total size : IPOD_TXBUFSIZE + ( IPOD_RXBUFSIZE * 3 ) = about 194Kbytes

#ifdef WINCE

#endif /*WINCE*/

#ifdef IPOD_NUCLUES
#if defined(IPOD_USB_INCLUDE)
	USBH_AUDIO_BUF_API_Init((unsigned char *)lAddress, USBH_AUDIO_PLAYBUFSIZE);
#endif
#endif /*WINCE*/
}


/**************************************************************************
*	Function : IPOD_API_Init
*
*	Description : This function initialize iPod resource & setting.
*				
*	Parameter : 
*
*  	Return : none
*
**************************************************************************/
void IPOD_API_Init(void)
{
	IPOD_initResource();

	#ifdef IPOD_NUCLUES
	IPOD_InitVar(&TCC_IPOD0_SEM, &TCC_IPOD1_SEM, &TCC_IPOD2_SEM, &TCC_IPOD3_SEM, &TCC_IPOD4_SEM);
	#endif

	#ifdef WINCE
	IPOD_InitVar(TCC_IPOD0_SEM, TCC_IPOD1_SEM, TCC_IPOD2_SEM, TCC_IPOD3_SEM, TCC_IPOD4_SEM);
	#endif

/*	IPOD_InitBuff(&gFileBuffer[0]);*/

	#ifdef IPOD_UART_INCLUDE
	IPOD_API_UART_InitPort();
	#endif
}

/**************************************************************************
*	Function : IPOD_GetDetectStatus
*
*	Description : This function returns iPod connection status.
*				
*	Parameter : 
*
*  	Return : none
*
**************************************************************************/
IPOD_PORT_STATE IPOD_GetDetectStatus(void *ExtInfo)
{
	IPOD_PORT_STATE lRet = IPOD_DISCONNECTED;
#ifdef IPOD_UART_INCLUDE
	#ifdef TCC83XX
		if(ISONE(IPOD_RMV_PORT, IPOD_RMV_PIN))
		{
			if(IPOD_Insert)
			{
				UI_API_DrawPopUp2Line("IPOD", "B6 HIGH");
			}
			lRet = IPOD_DISCONNECTED;
		}
		else
		{
			lRet = IPOD_CONNECTED;
		}
		return lRet;
	#endif /*TCC83XX*/
	
	#if (defined(TCC860x) || defined(TCC78X))
		if(ISZERO(IPOD_RMV_PORT, IPOD_RMV_PIN))
		{
			if(IPOD_Insert)
			{
				UI_API_DrawPopUp2Line("IPOD", "B6 HIGH");
			}
			lRet = IPOD_DISCONNECTED;
		}
		else
		{
			lRet = IPOD_CONNECTED;
		}
		return lRet;
	#endif /*(defined(TCC860x) || defined(TCC78X))*/

	#if defined(TCC80XX)
		short Ad_Buff;

		(void) DDI_Read(DDI_AD7_ID, (char *)&Ad_Buff, 2);

		if (Ad_Buff < 500)
		{
			//if(IPOD_Insert)
			//	UI_API_DrawPopUp2Line("IPOD", "B6 HIGH");
			lRet = IPOD_DISCONNECTED;
		}
		else
		{
			lRet = IPOD_CONNECTED;
		}
		return lRet;
	#endif /*defined(TCC80XX)*/

#else /*IPOD_UART_INCLUDE*/

	#ifdef TCC78X
		if(HCDgetstatus()) //For USB 
		{
			lRet = IPOD_DISCONNECTED;
		}
		else
		{
			lRet = IPOD_CONNECTED;
		}
		return lRet;
	#endif /*TCC78X*/
	
	#if (defined(TCC860x) || defined(TCC83XX))
		if( USBH_API_HUB_GetCurrentPortStatus() == DEVICE_CONNECTED) 
		{
			lRet = IPOD_CONNECTED;
		}
		else
		{
			lRet = IPOD_DISCONNECTED;
		}
		return lRet;
	#endif /*(defined(TCC860x) || defined(TCC83XX))*/

	#if defined(TCC80XX)
		unsigned int lDevNo = (unsigned int)IPOD_API_GetDevNo(ExtInfo);
		if ( USBH_FUNC_GetCurrentPortStataus(lDevNo) == DEVICE_CONNECTED) 
		{
			lRet = IPOD_CONNECTED;
		}
		else
		{
			lRet = IPOD_DISCONNECTED;
		}
		return lRet;
	#endif /*defined(TCC80XX)*/

	#ifdef WINCE
	pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	if(pInfo)
	{
		if(pInfo->DisconnecEvt == 1)
		{
			//TLOG(CH_CMDCTL, LV_ERROR, (TEXT(" ******* IPOD Disconnection Detected !!!!!!! *******\r\n")));
			return IPOD_DISCONNECTED;
			
		}
		else
		{
			return IPOD_CONNECTED;
		}
		
	}
	else
	{
		return IPOD_INVALID_PARAM;
	}	
	#endif
	
#endif /*IPOD_UART_INCLUDE*/
}

/**************************************************************************
*	Function : IPOD_SendSync
*
*	Description : This function send a sync data over UART connection.
*				
*	Parameter : none.
*
*  	Return : none
*
**************************************************************************/
void IPOD_SendSync(void)
{
#ifdef TCC78X
	IO_UART_WaitTXRDY(1);
	IO_UART_TXD(1, IPOD_SYNC);
#endif

#ifdef TCC860x
	while(HwUTLSR & HwUTLSR_TF);
	HwUTTXD = IPOD_SYNC;
#endif

#ifdef TCC83XX
	SerialWriteByte(IPOD_SYNC);
#endif

#if defined(TCC80XX)
	char sync_data = IPOD_SYNC;
	(void) DDI_Write(DDI_UART0_ID, &sync_data, 1);
#endif

	return;
}

/**************************************************************************
*	Function : IPOD_Calc_CheckSum
*
*	Description : This function check the checksum
*				
*	Parameter : 
*		- buff : 
*
*  	Return : none
*
**************************************************************************/
unsigned char IPOD_Calc_CheckSum(unsigned char *buff)
{
#if 1	/* QAC 17.4, 10.1, 12.7, 13.2, 12.13 */
	unsigned char *p;
	int len, i;
	unsigned char checksum;

	/* Initialzie value */
	i=0;
	p = &buff[1];
	len = (int)p[i];
	checksum = p[i];
	i++;

	if(len == 0)
	{
		len = p[i] & 0xFF;
		checksum = (unsigned char)len;
		i++;
		len = (int)((unsigned int)len << 8) + (int)(p[i] & 0xFF);
		checksum += p[i];
		i++;
	}

	while(len != 0)
	{
		len--;
		checksum += p[i];
		i++;
	}

	return ~checksum + 1;
#else
	unsigned char *p = buff + 1;
	int len = *p;
	unsigned char checksum = len;

	p++;
	if(len == 0){
		len = *p & 0xFF;
		checksum = len;
		p++;
		len = (len << 8) + (*p & 0xFF);
		checksum += *p;
		p++;
	}
	while(len--){
		checksum += *p;
		p++;
	}
	return ~checksum + 1;
#endif
}

/**************************************************************************
*	Function : IPOD_Calc_CheckSum_L
*
*	Description : This function check the checksum of large packet
*				
*	Parameter : 
*		- data : 
*		- size :
*
*  	Return : none
*
**************************************************************************/
unsigned char IPOD_Calc_CheckSum_L(const unsigned char *data, int size)
{
	int i;
	unsigned char sum=0;

	for (i=1; i<(size-1); i++) {
		sum += data[i];
	}
	return (0-sum);
}
#ifdef WINCE

#else /*WINCE*/
/**************************************************************************
*	Function : IPOD_SendPacket
*
*	Description : 
*				
*	Parameter : 
*
*  	Return : 0: success  / others : error
*
**************************************************************************/
int IPOD_SendPacket(unsigned char *buff, int len)
{
#ifdef IPOD_UART_INCLUDE
	#ifdef TCC78X
		while(len--){
			IO_UART_WaitTXRDY(1);
			IO_UART_TXD(1, *buff++);
		}
		return 0;
	#endif
	
	#ifdef TCC860x
		while(len--){
			while(HwUTLSR & HwUTLSR_TF);
			HwUTTXD = *buff++;
		}
		return 0;
	#endif
	
	#ifdef TCC83XX
		while(len--){
			SerialWriteByte(*buff++);
		}
		return 0;
	#endif

	#ifdef TCC80XX
	(void) DDI_Write(DDI_UART0_ID, buff, (int) len);
	return 0;
	#endif

#else /*IPOD_UART_INCLUDE*/

	return HID_Send_Buffer(buff, (unsigned int)len);
#endif
}
#endif /*WINCE*/

/**************************************************************************
*	Function : IPOD_SetAccess
*
*	Description : This function initialize the iPod access values.
*				
*	Parameter : 
*		- pPlayInfo : 
*		- set : 
*
*  	Return : none
*
**************************************************************************/
void IPOD_SetAccess(void *pPlayInfo, int set)
{
#if (defined(TCC860x) || defined(TCC78X) || defined(TCC83XX))
	IPOD_Access = set;
	IPOD_Navi_Access = set;
#endif

#if defined(TCC80XX)
	pPLAYBACK_INFO pPlayback = (pPLAYBACK_INFO)pPlayInfo; 
	pPlayback->mIPOD_Access = set;
	pPlayback->mIPOD_Navi_Access = set;
#endif
	
}

/**************************************************************************
*	Function : IPOD_API_EventProcess
*
*	Description : This function process the event data.
*				
*	Parameter : none
*
*  	Return : none
*
**************************************************************************/
static unsigned int Skip_Process_Mode = 0;
void IPOD_API_EventProcess(void)
{
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
	IPOD_STATE state;
	void *pHandle = DISK_GetHandle(DISK_DEVICE_IPOD);
#endif
#if defined(TCC80XX)
	unsigned char loc;
	void *pHandle = DISK_GetHandle(DISK_DEVICE_IPOD);
	void *pHandle2 = DISK_GetHandle(DISK_DEVICE_IPOD_2);
#endif

	if(Skip_Process_Mode == 0)
	{
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)

#ifdef TCC_MOUNT_TASK_INCLUDE

		state = IPOD_API_GetStatus(pHandle);
		if(IPOD_MOUNTED == state)
		{
				(void) IPOD_ProcessiPodEvent(pHandle);
				(void) IPOD_Check_iPod_status(pHandle);
		}
#else
		(void) IPOD_ProcessiPodEvent(pHandle);
		(void) IPOD_Check_iPod_status(pHandle);
#endif
#endif
#if defined(TCC80XX)
		if(pHandle != 0)
		{
			if(DISK_GetState(DISK_DEVICE_IPOD) == DISK_STATE_MOUNTCOMPLETE)
			{
				(void) IPOD_ProcessiPodEvent(pHandle);
				(void) IPOD_Check_iPod_status(pHandle);
			}
		}
		if(pHandle2 != 0)
		{
			if(DISK_GetState(DISK_DEVICE_IPOD_2) == DISK_STATE_MOUNTCOMPLETE)
			{
				(void) IPOD_ProcessiPodEvent(pHandle2);
				(void) IPOD_Check_iPod_status(pHandle2);
			}
		}
#endif
	}
}

/**************************************************************************
*	Function : IPOD_API_SetSkipProcessMode
*
*	Description : This function set the event process as skip mode.
*				
*	Parameter : Mode
*
*  	Return : none
*
**************************************************************************/
void IPOD_API_SetSkipProcessMode(unsigned int Mode)
{
	Skip_Process_Mode = Mode;
}


/**************************************************************************
*	Function : IPOD_SetDisconnectionStatus
*
*	Description : This function set the disconnection status to iPod thread
*				
*	Parameter : Mode
*
*  	Return : none
*
**************************************************************************/
void IPOD_SetDisconnectionStatus(void *Handle)
{
	pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(Handle);

	if(pInfo)
	{
		pInfo->DisconnecEvt = 1;
		
	}


}

/**************************************************************************
*	Function : IPOD_API_CheckiPodOption
*
*	Description : This function returns the iPod lingo option.
*				
*	Parameter : iPod_Handle
*
*  	Return : none
*
**************************************************************************/
void IPOD_API_CheckiPodOption(void *iPod_Handle, pIPOD_INIT_PARAM pParam, pIPOD_LINGO_INFO_DATA pLingo_InfoData)
{
	#ifdef IPOD_CHECK_OPTION
	IPOD_ERROR iPod_err;

	mem_set(pLingo_InfoData, 0x00, sizeof(IPOD_LINGO_INFO_DATA));

	/*Check Storage Lingo*/
	iPod_err = IPOD_CheckiPodOption((void *)iPod_Handle, LINGO_STORAGE, &(pLingo_InfoData->m_LingoInfo), &(pLingo_InfoData->m_IsVerison));
	pLingo_InfoData->m_Lingo_result[LINGO_STORAGE] = iPod_err;
	#endif
	
	(void)IPOD_CheckLingoOption(iPod_Handle, pParam);
	
}

/**************************************************************************
	Function : IPOD_API_Check_Storage_tagging_support

 	Description : It check whether the iPod support Storage lingo tagging function or not.
				
	Parameter : 
		IPOD_LINGO_INFO_DATA : iPod Lingo option or version information.

  	Return : 
  		1 : support
  		0 : not support
		
**************************************************************************/
int IPOD_API_Check_Storage_tagging_support(const IPOD_LINGO_INFO_DATA *pLingo_InfoData)
{
	int ret = 0;
	/*Storage Lingo support check routine*/
	if(IPOD_NO_ERROR == pLingo_InfoData->m_Lingo_result[LINGO_STORAGE])
	{
		if(pLingo_InfoData->m_IsVerison)
		{
			unsigned long MajorVer,MinorVer;
			MajorVer = pLingo_InfoData->m_LingoInfo.LingoVer[LINGO_STORAGE].Major;
			MinorVer = pLingo_InfoData->m_LingoInfo.LingoVer[LINGO_STORAGE].Minor;
			if((MajorVer >= 1) &&(MinorVer >=1))
			{
				/*It support Storage Lingo tagging*/
				ret = 1;
			}
		}
		else
		{
			unsigned long long Lingo_option;
			Lingo_option= pLingo_InfoData->m_LingoInfo.LingoOption[LINGO_STORAGE];
			if(Lingo_option & 0x01ull)
			{
				/*It support Storage Lingo tagging*/
				ret = 1;
			}
		}
	}

	return ret;


}

/**************************************************************************
*	Function : IPOD_Callback_OpenDataSessionForProtocol
*
*	Description : iPhone OS application communicatin callback
*				
*	Parameter : Mode
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_Callback_OpenDataSessionForProtocol( void *iPod_Handle, unsigned int SessionID, unsigned int nProtocolIndex )
{
	/* Sample code */
	int ret = IPOD_NO_ERROR;
	void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);
	pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	if ( NULL == iPod_Handle )
	{
		ret = IPOD_BAD_PARAMETER;
	}
	else
	{
		pInfo->m_iPod_OSApp_DataSesiongID = SessionID;
		pInfo->m_iPod_OSApp_ProtocolIndex = nProtocolIndex;		
	}
	
	return ret;
}

/**************************************************************************
*	Function : IPOD_Callback_CloseDataSession
*
*	Description : iPhone OS application communicatin callback
*				
*	Parameter : Mode
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_Callback_CloseDataSession( void *iPod_Handle, unsigned int SessiongID )
{
	/* Sample code */
	int ret = IPOD_NO_ERROR;
	void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);
	pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	if ( NULL == iPod_Handle )
	{
		ret = IPOD_BAD_PARAMETER;
	}
	else if ( SessiongID != pInfo->m_iPod_OSApp_DataSesiongID  )
	{
		ret = IPOD_BAD_PARAMETER;
	}
	else
	{
		// Implement here
		pInfo->m_iPod_OSApp_DataSesiongID = IPOD_NOT_ESTABLISED_SESSIONGID;
		pInfo->m_iPod_OSApp_ProtocolIndex = 0;
	}
	
	return ret;
}

/**************************************************************************
*	Function : IPOD_Callback_iPodDataTransfer
*
*	Description : iPhone OS application communicatin callback
*				
*	Parameter : Mode
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_Callback_iPodDataTransfer( void *iPod_Handle, unsigned int usSessionID, unsigned char *pData, unsigned int nDataSize )
{
	/* Sample code */
	int ret = IPOD_NO_ERROR;
	void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);
	pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	if ( (NULL == iPod_Handle) || (NULL == pData) )
	{
		ret = IPOD_BAD_PARAMETER;
	}
	else if ( IPOD_NOT_ESTABLISED_SESSIONGID == pInfo->m_iPod_OSApp_DataSesiongID )
	{
		ret = IPOD_BAD_PARAMETER;
	}
	else
	{
		// Implement here
//		IPOD_optionLog(0x10, 0x00400000,"Session ID : 0x%x", usSessionID);
//		IPOD_optionLog(0x10, 0x00400000," rcv data : -->%s<-- ", pData);
	}
	
	return ret;
}

/*
int IPOD_Callback_iPodNotification( void )
{
	int ret = IPOD_NO_ERROR;
	
	return ret;
}
*/

/**************************************************************************
*	Function : IPOD_SAMPLE_DevDataTransfer
*
*	Description : iPhone OS application communicatin sample program
*				
*	Parameter : Mode
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_API_Transfer_DevData_to_App(void *iPod_Handle, unsigned char *SendBuff, unsigned int size)
{
	int ret = 0;
	void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);
	pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)ExtInfo;

    unsigned int DevDataTransferRetryCnt = 0;
    unsigned int RetryTransID;
    unsigned int RetryDataCount;
    unsigned int compareTransID;
    
	if ( NULL == iPod_Handle )
	{
		ret = -1;
	}
	else if ( IPOD_NOT_ESTABLISED_SESSIONGID == pInfo->m_iPod_OSApp_DataSesiongID )
	{
		ret = -2;
	}
	else
	{
		ret = IPOD_DevDataTransfer( iPod_Handle, pInfo->m_iPod_OSApp_DataSesiongID, SendBuff, size, IPOD_DATATRANSFER_NORMAL, &RetryTransID, &RetryDataCount);
		
		//if(ret == IPOD_COMMAND_TIMEOUT)
		//{
		//    for(DevDataTransferRetryCnt = 1; DevDataTransferRetryCnt < MAX_RETRY_DATA_TRANSFER_COUNT; DevDataTransferRetryCnt++)
		//    {
		//        compareTransID = RetryTransID;
		//        ret = IPOD_DevDataTransfer( iPod_Handle, pInfo->m_iPod_OSApp_DataSesiongID, SendBuff, size, IPOD_DATATRANSFER_TIMEOUT, &RetryTransID, &RetryDataCount);
		//        if(ret == IPOD_NO_ERROR)
		//        {
		//            /*successed IPOD_DevDataTransfer*/
		//            break;
		//        }
		//        else
		//        {
		//            if(ret == IPOD_COMMAND_TIMEOUT)
		//            {
		//                if(compareTransID != RetryTransID)
		//                {
		//                    DevDataTransferRetryCnt = 0;
		//                    compareTransID = RetryTransID;
		//                }
		//            }
		//        }
		//    }
		//}
	}

	return ret;
}

/**************************************************************************
*	Function : iPod_ExampleCode_getLingoProtocolVer
*
*	Description : iPod user command example - to get a lingo protocol version.
*				
*	Parameter : 
*		void *iPod_Handle
*		unsigned long Lingo
*		unsigned char *inform
*		unsigned char *major
*		unsigned char *minor
*
*  	Return : none
*
**************************************************************************/
#define TEST_REQUEST_LINGOPROTOCOLVERSION						0x0F
#define TEST_RETURN_LINGOPROTOCOLVERSION						0x10
IPOD_ERROR iPod_ExampleCode_getLingoProtocolVer(void *iPod_Handle, unsigned long Lingo, unsigned char *inform, unsigned char *major, unsigned char *minor)
{
	IPOD_ERROR ret;
	IPOD_CMD_PARAM CmdParam = {0, };
	unsigned char *buff = IPOD_GetTxBuffer(iPod_Handle); /*Please use this function to get a Txbuffer */
	unsigned char *pData;
	unsigned long DataSize;
	
	ret = IPOD_USER_EnterCriticalSection(iPod_Handle);
	if(IPOD_NO_ERROR == ret)
	{

		if(NULL != buff)
		{
			buff[0] = LINGO_GENERAL;
			buff[1] = TEST_REQUEST_LINGOPROTOCOLVERSION;
			buff[2] = Lingo;

			CmdParam.m_iPod_Handle = iPod_Handle;
			CmdParam.m_CurCmd = TEST_REQUEST_LINGOPROTOCOLVERSION;
			CmdParam.m_SendCmdBuf = buff;
			CmdParam.m_SendCmdBufSize = 3; /*buffer size of User added*/
			CmdParam.m_TimeOut = IPOD_Callback_GetWaitTime();

			ret= IPOD_USER_FUNC_SendCmd_RcvResponse(&CmdParam, LINGO_GENERAL, TEST_RETURN_LINGOPROTOCOLVERSION);
			if(ret == IPOD_COMMAND_ACCEPTED)
			{
				ret = IPOD_NO_ERROR;
				
				pData = CmdParam.m_ResponseBuf;
				DataSize = CmdParam.m_ResponseBufSize;

				*inform =pData[0];
				*major = pData[1];
				*minor = pData[2];
			}

		}		
		IPOD_USER_ExitCriticalSection(iPod_Handle);
	}
}


/**************************************************************************
*	Function : IPOD_API_GetDRPlayStatus
*
*	Description : It returns play status of iPod
*				
*	Parameter : 
*		void *iPod_Handle
*		IPOD_DR_PLAY_STATUS *playStatus
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_API_GetDRPlayStatus(void *iPod_Handle, IPOD_DR_PLAY_STATUS *playStatus)
{
	IPOD_ERROR ret= IPOD_NO_ERROR;
	pIPOD_PLAY_INFO pInfo;
	void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);

	if(NULL != ExtInfo)
	{
		pInfo = (pIPOD_PLAY_INFO)ExtInfo;
		*playStatus = pInfo->Rd_playStatus;
	}
	else
	{
		ret = IPOD_INVALID_HANDLE;
	}

	return ret;
}

/**************************************************************************
*	Function : IPOD_API_SetDRPlayStatus
*
*	Description : It sets play status of iPod
*				
*	Parameter : 
*		void *iPod_Handle
*		IPOD_DR_PLAY_STATUS *playStatus
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_API_SetDRPlayStatus(void *iPod_Handle, IPOD_DR_PLAY_STATUS playStatus)
{
	IPOD_ERROR ret= IPOD_NO_ERROR;
	pIPOD_PLAY_INFO pInfo;
	void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);

	if(NULL != ExtInfo)
	{
		pInfo = (pIPOD_PLAY_INFO)ExtInfo;
		pInfo->Rd_playStatus = playStatus;
	}
	else
	{
		ret = IPOD_INVALID_HANDLE;
	}

	return ret;
}

#ifdef WINCE

IPOD_ERROR IPOD_API_Open(void *iPod_Handle)
{
	IPOD_ERROR ret;
	
	ret = IPOD_Open(iPod_Handle);
	
	return ret;
}
IPOD_ERROR IPOD_API_Malloc_ExtInfo(void *iPod_Handle)
{
	IPOD_ERROR ret;
	void* ExtInfo;
	ExtInfo = IPOD_Malloc_iPodBuf();
	if(ExtInfo != NULL)
	{
		IPOD_Malloc_ExtInfo(iPod_Handle, ExtInfo);
	}

	return ret;
}

HANDLE IPOD_API_GetControlThreadID(void* iPod_Handle)
{
    HANDLE ret;
    if(NULL != iPod_Handle)
    {
        ret = IPOD_GetControlThreadID(iPod_Handle);
    }
    else
    {
        ret = 0;
    }
    return ret;
}
HANDLE IPOD_API_GetDataThreadID(void* iPod_Handle)
{
    HANDLE ret;
    if(NULL != iPod_Handle)
    {
        ret = IPOD_GetDataThreadID(iPod_Handle);
    }
    else
    {
        ret = 0;
    }
    return ret;
}
#endif
/**************************************************************************
*	Function : IPOD_Callback_iPodNotification
*
*	Description : This function updated all informatin of new contents. 
*				callback function of iPod library.
*
*	IMPORTANT NOTICE : Please don't use IPOD library API on callback function.
*				
*	Parameter : 
*		- ExtInfo : 
*
*  	Return : none
*
**************************************************************************/
int IPOD_Callback_iPodNotification(void* iPod_Handle, unsigned char NotiType, const unsigned char *pData)
{
	unsigned int WaitTime;
	unsigned short OverflowTransID;
	IPOD_NOTI_TAG_STATUS TagStatus;
	IPOD_NOTI_CAMERA_PAYLOAD CameraPayload;
	long ActualLen;
	//unsigned char *AppString;
	unsigned short SessionID;
	IPOD_NOTI_DATABASE_AVAILABLE_STATUS DatabaseAvailableStatus;
	IPOD_NOTI_COMMAND_COMPLETION_STATUS CommandCompletionStatus;
	IPOD_NOTI_CHARGING_INFO_TYPE ChargingInfoType;
	IPOD_NOTI_CHARGING_INFO_VALUE ChargingInfoValue;
	void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);
	pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)ExtInfo;

	switch(NotiType)
	{
		case IPOD_NOTI_TYPE_FLOW_CONTROL :
			pInfo->m_Noti_WaitTime = IPOD_Get_Oneword(&pData[0]);
			pInfo->m_Noti_OverflowTransID = IPOD_Get_Short(&pData[4]);
			/*TCC800X*/
			//DMP_MessageEvtUpdateiPodNotiFlowControl(pInfo->Disk);
			break;
		case IPOD_NOTI_TYPE_RADIO_TAGGING :
			TagStatus = pData[0];
			break;
		case IPOD_NOTI_TYPE_CAMERA_NOTIFICATIONS :
			CameraPayload = pData[0];
			break;
		case IPOD_NOTI_TYPE_CHARGING_INFO :
			ChargingInfoType = pData[0];
			ChargingInfoValue = IPOD_Get_Short(&pData[1]);
			break;
		case IPOD_NOTI_TYPE_NOWPLAYINGAPPFOCUSCHANGE :
			ActualLen =  IPOD_UTF8Decoder(pData);
			//AppString = (unsigned char*)malloc(sizeof(unsigned char) * ActualLen);
			//memcpy(AppString, &pData[0], ActualLen);
			//free(AppString);
			break;
		case IPOD_NOTI_TYPE_SESSIONSPACEAVAILABLE :
			SessionID = IPOD_Get_Short(&pData[0]);
			break;
		case IPOD_NOTI_TYPE_DATABASE_AVAILABLE :
			DatabaseAvailableStatus = pData[0];
			break;
		case IPOD_NOTI_TYPE_COMMAND_COMPLETE :
			CommandCompletionStatus = pData[0];
			break;
		default :
			break;
	}
	
	return 0;
}

/**************************************************************************
*	Function : IPOD_API_GetSupportMultiLingo
*
*	Description : It returns current supportMultiLingo.
*				
*	Parameter : 
*		void *iPod_Handle
*		MLingoType *supportMultiLingo
*
*  	Return : none
*
**************************************************************************/
IPOD_ERROR IPOD_API_GetSupportMultiLingo(void* iPod_Handle, MLingoType *supportMultiLingo)
{
	IPOD_ERROR ret;
	if(NULL != iPod_Handle)
	{
		ret = IPOD_GetSupportMultiLingo(iPod_Handle, supportMultiLingo);
	}
	else
	{
		ret = IPOD_INVALID_HANDLE;
	}
	return ret;
}

IPOD_ERROR IPOD_API_GetIDPSSupport(void* iPod_Handle, IPOD_DEFAULT_CONNECTION *IDPS_support)
{
    IPOD_ERROR ret;
	if(NULL != iPod_Handle)
	{
		ret = IPOD_GetCheckIDPSSupport(iPod_Handle, IDPS_support);
	}
	else
	{
		ret = IPOD_INVALID_HANDLE;
	}
	return ret;
}

#endif   /*IPOD_INCLUDE*/
