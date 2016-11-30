
#include "stdafx.h"
#include "iPodConfig.h"

//#include "iPodPlayer.h"
//#include "iPodPlayerDlg.h"
#include "iPodCommandControl.h"
#include <winioctl.h>
#include "./LIB/iPodLib.h"
#include "./LIB/iPod_api.h"
#include "AVSet.h"
#include "inc/param.h"


typedef enum {
	IPOD_CONTROL_STATE_NONE,
	IPOD_CONTROL_STATE_INITIALIZED,
	IPOD_CONTROL_STATE_TERMINATED,

	IPOD_CONTROL_STATE_MAX
} CONTROLPROCESSOR_STATE;
		
#define IS_CMDOK(x)	((x) == (IPOD_NO_ERROR) )
#define IS_CMDERROR(x)	( (x) != (IPOD_NO_ERROR) )


/******************************************
        TccHID driver IOCTL CODE
********************************************/
#define TCC_IOCTLCode(f,m)	CTL_CODE ( FILE_DEVICE_UNKNOWN , 0xA00 + (f), (m), FILE_ANY_ACCESS )


#define IOCTL_USBH_TCCHID_GET_DRIVER_VERSION	TCC_IOCTLCode(1300, METHOD_BUFFERED)


#define IOCTL_USBH_TCCHID_LAST_IOCTL				TCC_IOCTLCode(1399, METHOD_BUFFERED)


#ifdef TIME_CHECK
short g_nMSGRequestCheckTick[WM_EVENTCTRL_MSGBASE];
DWORD g_nMSGResCheckTick = 0;
#endif

CategoryType IPOD_GetVideoUpperCategory( CategoryType eCurrnetType){
	CategoryType eUpperCategory;

	switch( eCurrnetType ){
		case IPOD_LIB_TRACK:
			eUpperCategory = IPOD_LIB_GENRE;
			break;
		default:
			eUpperCategory = IPOD_LIB_ALL;
			break;
	}

	return eUpperCategory;
}

BOOL bPlayList = 0;
CategoryType IPOD_GetUpperCategory( CategoryType eCurrnetType){
	CategoryType eUpperCategory;
	
	switch( eCurrnetType ){
		case IPOD_LIB_GENRE:
			eUpperCategory = IPOD_LIB_ALL;
			break;
		case IPOD_LIB_ARTIST:
			eUpperCategory = IPOD_LIB_GENRE;
			break;
		case IPOD_LIB_ALBUM:
			eUpperCategory = IPOD_LIB_ARTIST;
			break;
		case IPOD_LIB_TRACK:
			if (bPlayList)
			{
				eUpperCategory = IPOD_LIB_PLAYLIST;
			}
			else
				eUpperCategory = IPOD_LIB_ALBUM;
			break;
		default:
			eUpperCategory = IPOD_LIB_ALL;
			break;
	}

	return eUpperCategory;
}

CategoryType IPOD_GetVideoSubCategory( CategoryType eCurrnetType){
	CategoryType eSubCategory;

	switch( eCurrnetType ){
		case IPOD_LIB_GENRE:
			eSubCategory = IPOD_LIB_TRACK;
			break;
		default:
			eSubCategory = IPOD_LIB_ALL;
			break;
	}

	return eSubCategory;
}

CategoryType IPOD_GetSubCategory( CategoryType eCurrnetType){
	CategoryType eSubCategory;
	
	switch( eCurrnetType ){
		case IPOD_LIB_PLAYLIST:
			eSubCategory = IPOD_LIB_TRACK;
			bPlayList = 1;
			break;
		case IPOD_LIB_GENRE:
			eSubCategory = IPOD_LIB_ARTIST;
			break;
		case IPOD_LIB_ARTIST:
			eSubCategory = IPOD_LIB_ALBUM;
			break;
		case IPOD_LIB_ALBUM:
			bPlayList = 0;
			eSubCategory = IPOD_LIB_TRACK;
			break;
		default:
			eSubCategory = IPOD_LIB_ALL;
			break;
	}

	return eSubCategory;
}



#define CP_POWERCTL_OFF	(0)
#define CP_POWERCTL_ON		(1)

#define PCA9539HIGH	(0xEE)
#define PCA9539LOW	(0xE8)

#define GXP_PORTOUTPUT 0
#define GXP_PORTINPUT 1

#if defined(TCC890X_WINCE)
#define GXP_IPOD_CP_POWER		(0x2000)
#define GXP_IPOD_CP_RESET_		(0x0010)

#define GXP_IPOD_CP_POWER_PORT	PCA9539LOW
#define GXP_IPOD_CP_RESET_PORT	PCA9539HIGH
#define GXP_IPOD_CP_POWER_PIN	GXP_IPOD_CP_POWER
#define GXP_IPOD_CP_RESET_PIN	GXP_IPOD_CP_RESET_
#elif defined(TCC880X_WINCE) || defined(TCC892X_WINCE)
#define GXP_IPOD_CP_MAINPOWER_PORT	(0xEC)	//Power Board
#define GXP_IPOD_CP_MAINPOWER_PIN	(1<<9)
#define GXP_IPOD_CP_POWER_PORT	(0xE8)	//PCA9539LOW
#define GXP_IPOD_CP_POWER_PIN	(1<<9)
#define GXP_IPOD_CP_RESET_PORT	(0xEE)	//PCA9539HIGH
#define GXP_IPOD_CP_RESET_PIN	(1<<3)
#else
#error "Chipset is not selected"
#endif

typedef struct _GXPINFO{
    unsigned short    uiDevice;
    unsigned short    uiPort;
    unsigned int    uiState;
}GXPINFO, *PGXPINFO;


BOOL IAP_CP_PowerControl( HANDLE hGXPDevice, DWORD OnOff ){
	BOOL ret = FALSE;

#if (_WIN32_WCE < 0x500)
	#error WinCE4 or earlier is not supported
#elif (_WIN32_WCE < 0x800)
	ret=TRUE;
#else

	DWORD dwByteReturned;
	GXPINFO GxpInfo;

	if ( IS_NULL(hGXPDevice) ){
		TLOG(CH_CMDCTL, LV_ERROR,   (TEXT(" IAP_CP_PowerControl() > Invalid handle\r\n")));
		goto EXIT;
	}

#if defined(TCC880X_WINCE) || defined(TCC892X_WINCE)
	GxpInfo.uiDevice = GXP_IPOD_CP_MAINPOWER_PORT; // GPIO Expander Device
	GxpInfo.uiPort = GXP_IPOD_CP_MAINPOWER_PIN;
	GxpInfo.uiState = OnOff;
	ret = WriteFile(hGXPDevice, &GxpInfo, sizeof(GxpInfo), &dwByteReturned, NULL);
	if (ret == FALSE) {
		TLOG(CH_CMDCTL, LV_ERROR,  (TEXT("IPOD Power control failed\r\n")));
		goto EXIT;
	}
	#if 0
	while (1) {
		GxpInfo.uiState = 0;
		ret = WriteFile(hGXPDevice, &GxpInfo, sizeof(GxpInfo), &dwByteReturned, NULL);
		if (ret == FALSE) {
			TLOG(CH_CMDCTL, LV_ERROR,  (TEXT("IPOD Power control failed\r\n")));
			goto EXIT;
		}
		Sleep(500);
		GxpInfo.uiState = 1;
		ret = WriteFile(hGXPDevice, &GxpInfo, sizeof(GxpInfo), &dwByteReturned, NULL);
		if (ret == FALSE) {
			TLOG(CH_CMDCTL, LV_ERROR,  (TEXT("IPOD Power control failed\r\n")));
			goto EXIT;
		}
		Sleep(500);
	}
	#endif
#endif

	GxpInfo.uiDevice = GXP_IPOD_CP_POWER_PORT; // GPIO Expander Device
	GxpInfo.uiPort = GXP_IPOD_CP_POWER_PIN;
	GxpInfo.uiState = OnOff;

	ret = WriteFile(hGXPDevice, &GxpInfo, sizeof(GxpInfo), &dwByteReturned, NULL);
	if (ret == FALSE) {
		TLOG(CH_CMDCTL, LV_ERROR,  (TEXT("IPOD Power control failed\r\n")));
		goto EXIT;
	}

	// Check the value
	GxpInfo.uiDevice = GXP_IPOD_CP_POWER_PORT; // GPIO Expander Device
	GxpInfo.uiPort=GXP_PORTOUTPUT;
	GxpInfo.uiState=0;

	if( FALSE==ReadFile(hGXPDevice, &GxpInfo, 2, &dwByteReturned, NULL) )	{
		TLOG(CH_CMDCTL, LV_WARN, (TEXT("ERROR: IAP_PowerControl()\r\n")));
	}

	TLOG(CH_CMDCTL, LV_LOG, (TEXT("%s IPOD Power %s\r\n"), TEXT("[ IAP ]"), ((GxpInfo.uiState & GXP_IPOD_CP_POWER_PIN)?L"ON":L"OFF")));
#endif

EXIT:
	return ret;
}

BOOL IAP_CP_SetReset( HANDLE hGXPDevice ){
	BOOL ret = FALSE;
#if (_WIN32_WCE < 0x500)
	#error WinCE4 or earlier is not supported
#elif (_WIN32_WCE < 0x800)
	TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("IAP_CP_SetReset() > start\r\n")));

#define	HwGPESET								*(volatile unsigned long *)0xB005A0C8	// W, OR function on GPE Output Data
#define	HwGPECLR								*(volatile unsigned long *)0xB005A0CC	// W, BIC function on GPE Output Data
#define	Hw9		0x00000200

	HwGPECLR=Hw9;

#ifdef AUTH_IC_20B //def AUTH_IC_20B
	TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("[AUTH_IC_20B] Keep 0\r\n")));

	Sleep(50);
#else
	TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("[OTHER IC VER] Keep 0\r\n")));

	Sleep(20);
#endif	
	HwGPESET=Hw9;

	ret=TRUE;
	TLOG(CH_CMDCTL, LV_DEBUG,  (TEXT("IAP_CP_SetReset() > finish\r\n")));
#else
	DWORD dwByteReturned;
	GXPINFO GxpInfo;

	if ( IS_NULL(hGXPDevice) ){
		TLOG(CH_CMDCTL, LV_ERROR,  (TEXT(" IAP_CP_PowerControl() > Invalid handle\r\n")));
		goto EXIT;
	}
#ifdef AUTH_IC_20B	
	TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("IAP_CP_SetReset() > start\r\n")));

	GxpInfo.uiDevice = GXP_IPOD_CP_RESET_PORT; // GPIO Expander Device
	GxpInfo.uiPort = GXP_IPOD_CP_RESET_PIN;
	GxpInfo.uiState = 0; // reset
	
	ret = WriteFile(hGXPDevice, &GxpInfo, sizeof(GxpInfo), &dwByteReturned, NULL);
	if (ret == FALSE) {
		TLOG(CH_CMDCTL, LV_DEBUG,(TEXT("IAP_CP_SetReset() > failed\r\n")));
		goto EXIT;
	}
#endif

#ifdef AUTH_IC_20B //def AUTH_IC_20B
	TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("[AUTH_IC_20B] Keep 0\r\n")));

	Sleep(50);
#else
	#ifdef AUTH_IC_20C
	TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("[AUTH_IC_20C] Keep 0\r\n")));
	if(0x20 == IAP_CP_slaveaddr)
	{
		Sleep(10);//RST pin is keeping low level over 3ms 
	}
	else if(0x22 == IAP_CP_slaveaddr)
	{
		//RST pin is keeping low level for 1.5ms 
	}
	#else
	TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("[OTHER IC VER] Keep 0\r\n")));

	Sleep(20);
	#endif
#endif	

	GxpInfo.uiDevice = GXP_IPOD_CP_RESET_PORT; // GPIO Expander Device
	GxpInfo.uiPort = GXP_IPOD_CP_RESET_PIN;
	GxpInfo.uiState = 1; // reset

	ret = WriteFile(hGXPDevice, &GxpInfo, sizeof(GxpInfo), &dwByteReturned, NULL);
	if (ret == FALSE) {
		TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("IAP_CP_SetReset() > failed\r\n")));
		goto EXIT;
	}
	
	TLOG(CH_CMDCTL, LV_DEBUG,  (TEXT("IAP_CP_SetReset() > finish\r\n")));
#endif

EXIT:
	return ret;
}

BOOL IAP_CP_Init( HANDLE hGXPDevice )
{

	return TRUE;


	BOOL IsSuccess = FALSE;
#if (_WIN32_WCE < 0x500)
	#error WinCE4 or earlier is not supported
#elif (_WIN32_WCE < 0x800)
	// No power control for iPod CP Chip
	//IsSuccess=TRUE;
	IsSuccess = IAP_CP_SetReset( hGXPDevice );
#else
	
	if ( hGXPDevice ){
		IsSuccess = IAP_CP_PowerControl( hGXPDevice, CP_POWERCTL_ON );
		if ( FALSE == IsSuccess ){
			TLOG(CH_CMDCTL, LV_ERROR,  (TEXT("IAP_CP_Init() > Failed power control\r\n")));
			goto EXIT;
		}

		Sleep(100);

		IsSuccess = IAP_CP_SetReset( hGXPDevice );
		if ( FALSE == IsSuccess ){
			TLOG(CH_CMDCTL, LV_ERROR,  (TEXT("IAP_CP_Init() > Failed reset CP\r\n")));
			goto EXIT;
		}

		Sleep(350);

		//IAP_CP_wait();
	}
	else{
		TLOG(CH_CMDCTL, LV_ERROR,  (TEXT("IAP_CP_Init() > Invalid parameter\r\n")));
		goto EXIT;
	}
#endif

EXIT:
	return IsSuccess;
}

#ifdef TIME_CHECK
LPCTSTR GetMessageName( DWORD MsgID )
{
	LPCTSTR pString = NULL;
	switch( MsgID ){
		case WM_UI_UPDATE_CURRENTTRACKINFO:
			pString = L"WM_UI_UPDATE_CURRENTTRACKINFO";
			break;
		case WM_UI_UPDATE_CURRENTTRACKNUM:
			pString = L"WM_UI_UPDATE_CURRENTTRACKNUM";
			break;
		case WM_UI_UPDATE_TRACKPLAYBACKPOSITION:
			pString = L"WM_UI_UPDATE_TRACKPLAYBACKPOSITION";
			break;
		case WM_UI_UPDATE_FFSEEKSTOP:
			pString = L"WM_UI_UPDATE_FFSEEKSTOP";
			break;
		case WM_UI_UPDATE_REWSEEKSTOP:
			pString =L"WM_UI_UPDATE_REWSEEKSTOP";
			break;
		case WM_UI_UPDATE_SAMPLINGFREQUENCE:
			pString = L"WM_UI_UPDATE_SAMPLINGFREQUENCE";
			break;
		case WM_UI_MESSAGE_MAX :
			pString = L"WM_UI_MESSAGE_MAX ";
			break;

		case WM_CMDCTRL_INIT:
			pString = L"WM_CMDCTRL_INIT";
			break;

		case WM_CMDCTRL_SEND_HANDLE:
			pString = L"WM_CMDCTRL_SEND_HANDLE";
			break;
		case WM_CMDCTRL_RES_INIT:
			pString = L"WM_CMDCTRL_RES_INIT";
			break;
		case WM_CMDCTRL_STOP:
			pString = L"WM_CMDCTRL_STOP";
			break;
		case WM_CMDCTRL_RES_STOP:
			pString = L"WM_CMDCTRL_RES_STOP";
			break;
		case WM_CMDCTRL_TERMINATE:
			pString = L"WM_CMDCTRL_TERMINATE";
			break;
		case WM_CMDCTRL_RES_TERMINATE:
			pString = L"WM_CMDCTRL_RES_TERMINATE";
			break;
		case WM_CMDCTRL_CANCELCMD:
			pString = L"WM_CMDCTRL_CANCELCMD";
			break;
		case WM_CMDCTRL_RES_CANCELCMD:
			pString = L"WM_CMDCTRL_RES_CANCELCMD";
			break;
		
		case WM_CMDCTRL_PLAY:
			pString = L"WM_CMDCTRL_PLAY";
			break;
		case WM_CMDCTRL_PLAY_IN_BRWSLIST:
			pString = L"WM_CMDCTRL_PLAY_IN_BRWSLIST";
			break;
		case WM_CMDCTRL_RES_PLAY:
			pString = L"WM_CMDCTRL_RES_PLAY";
			break;
		case WM_CMDCTRL_PAUSE:
			pString = L"WM_CMDCTRL_PAUSE";
			break;
		case WM_CMDCTRL_RES_PAUSE:
			pString = L"WM_CMDCTRL_RES_PAUSE";
			break;
		case WM_CMDCTRL_NEXTTRACK:
			pString = L"WM_CMDCTRL_NEXTTRACK";
			break;
		case WM_CMDCTRL_RES_NEXTTRACK:
			pString = L"WM_CMDCTRL_RES_NEXTTRACK";
			break;
		case WM_CMDCTRL_PREVIOUSTRACK:
			pString =L"WM_CMDCTRL_PREVIOUSTRACK";
			break;
		case WM_CMDCTRL_RES_PREVIOUSTRACK:
			pString = L"WM_CMDCTRL_RES_PREVIOUSTRACK";
			break;
		case WM_CMDCTRL_FF:
			pString = L"WM_CMDCTRL_FF";
			break;
		case WM_CMDCTRL_RES_FF:
			pString = L"WM_CMDCTRL_RES_FF";
			break;
		case WM_CMDCTRL_REW:
			pString = L"WM_CMDCTRL_REW";
			break;
		case WM_CMDCTRL_RES_REW:
			pString = L"WM_CMDCTRL_RES_REW";
			break;

		case WM_CMDCTRL_GETCURRENTTRACKINDEX:
			pString = L"WM_CMDCTRL_GETCURRENTTRACKINDEX";
			break;
		case WM_CMDCTRL_RES_GETCURRENTTRACKINDEX:
			pString = L"WM_CMDCTRL_RES_GETCURRENTTRACKINDEX";
			break;
		case WM_CMDCTRL_GETTOTALPLAYTRACKS:
			pString = L"WM_CMDCTRL_GETTOTALPLAYTRACKS";
			break;
		case WM_CMDCTRL_RES_GETTOTALPLAYTRACKS:
			pString = L"WM_CMDCTRL_RES_GETTOTALPLAYTRACKS";
			break;
		case WM_CMDCTRL_GETTITLE:
			pString = L"WM_CMDCTRL_GETTITLE";
			break;
		case WM_CMDCTRL_RES_GETTITLE:
			pString = L"WM_CMDCTRL_RES_GETTITLE";
			break;
		case WM_CMDCTRL_GETARTIST:
			pString = L"WM_CMDCTRL_GETARTIST";
			break;
		case WM_CMDCTRL_RES_GETARTIST:
			pString = L"WM_CMDCTRL_RES_GETARTIST";
			break;
		case WM_CMDCTRL_GETALBUM:
			pString = L"WM_CMDCTRL_GETALBUM";
			break;
		case WM_CMDCTRL_RES_GETALBUM:
			pString = L"WM_CMDCTRL_RES_GETALBUM";
			break;
		case WM_CMDCTRL_GETALBUMART:
			pString = L"WM_CMDCTRL_GETALBUMART";
			break;
		case WM_CMDCTRL_RES_GETALBUMART:
			pString = L"WM_CMDCTRL_RES_GETALBUMART";
			break;
		case WM_CMDCTRL_INFORM_SAMPLINGFREQ_CHECKED:
			pString = L"WM_CMDCTRL_INFORM_SAMPLINGFREQ_CHECKED";
			break;
		case WM_CMDCTRL_RES_INFORM_SAMPLINGFREQ_CHECKED:
			pString = L"WM_CMDCTRL_RES_INFORM_SAMPLINGFREQ_CHECKED";
			break;


		case WM_CMDCTRL_BRWS_INIT:
			pString = L"WM_CMDCTRL_BRWS_INIT";
			break;
		case WM_CMDCTRL_BRWS_RES_INIT:
			pString = L"WM_CMDCTRL_BRWS_RES_INIT";
			break;
		case WM_CMDCTRL_BRWS_SELECTALL:
			pString = L"WM_CMDCTRL_BRWS_SELECTALL";
			break;
		case WM_CMDCTRL_BRWS_RES_SELECTALL:
			pString = L"WM_CMDCTRL_BRWS_RES_SELECTALL";
			break;
		case WM_CMDCTRL_BRWS_SELECT:
			pString = L"WM_CMDCTRL_BRWS_SELECT";
			break;
		case WM_CMDCTRL_BRWS_RES_SELECT:
			pString = L"WM_CMDCTRL_BRWS_RES_SELECT";
			break;
		case WM_CMDCTRL_BRWS_MOVEUPPER:
			pString = L"WM_CMDCTRL_BRWS_MOVEUPPER";
			break;
		case WM_CMDCTRL_BRWS_RES_MOVEUPPER:
			pString = L"WM_CMDCTRL_BRWS_RES_MOVEUPPER";
			break;
		case WM_CMDCTRL_BRWS_GETNAME:
			pString = L"WM_CMDCTRL_BRWS_GETNAME";
			break;
		case WM_CMDCTRL_BRWS_RES_GETNAME:
			pString = L"WM_CMDCTRL_BRWS_RES_GETNAME";
			break;
		case WM_CMDCTRL_EXT_FUNC1:
			pString = L"WM_CMDCTRL_EXT_FUNC1";
			break;
		case WM_CMDCTRL_RES_EXT_FUNC1:
			pString = L"WM_CMDCTRL_EXT_FUNC1";
			break;
		case WM_CMDCTRL_EXT_FUNC2:
			pString = L"WM_CMDCTRL_EXT_FUNC2";
			break;
		case WM_CMDCTRL_RES_EXT_FUNC2:
			pString = L"WM_CMDCTRL_EXT_FUNC2";
			break;
		case WM_CMDCTRL_EXT_FUNC3:
			pString = L"WM_CMDCTRL_EXT_FUNC3";
			break;
		case WM_CMDCTRL_RES_EXT_FUNC3:
			pString = L"WM_CMDCTRL_EXT_FUNC3";
			break;
		case WM_CMDCTRL_RES_EXT_FUNC4:
			pString = L"WM_CMDCTRL_EXT_FUNC4";
			break;
		case WM_CMDCTRL_RES_EXT_FUNC5:
			pString = L"WM_CMDCTRL_EXT_FUNC5";
			break;


		default:
			pString = L"NOTDEFINEDMSG";
			break;
	}

	return pString;
}
#endif

#if 0
static void IPOD_API_USB_InitParam(void *Handle, pIPOD_INIT_PARAM pParam, void *Hid_Handle, void *I2C_Handle, unsigned long EventThreadID, IAP_CONNECTION_MODE connectionType, unsigned long I2C_ChannelNum)
{
	unsigned char *IPod_Buffer;
	// For Digital audio output -> 1wire
	memset(pParam, 0x00, sizeof(IPOD_INIT_PARAM));
	

	TLOG(CH_CMDCTL, LV_LOG, (TEXT("Event thread ID = 0x%x\r\n"), EventThreadID));

	pParam->DevHandleDes.HID = Hid_Handle;
	pParam->DevHandleDes.I2C = I2C_Handle;
	pParam->DevHandleDes.I2C_channelNum = I2C_ChannelNum;
	pParam->EventThreadID = EventThreadID;

	pParam->ConnectionType = IPOD_USB_CONNECT;


	if(ONE_WIRE_CONNECTION == connectionType)
	{
		pParam->IdentifyToken.LingoCnt = 3;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
		pParam->IdentifyToken.Lingos[2] = LINGO_DIGITAL_AUDIO;

	}
	else
	{
		pParam->IdentifyToken.LingoCnt = 2;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
	}

#ifdef IPOD_USB_POWER_MAX_1A
	pParam->IdentifyToken.DeviceOption = (CONSTANT_HIGH_POWER | AUTHENTICATION_IMMEDIATELY);
#else
	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);
#endif

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->pAccInfoToken = &gIPOD_AccInfo;


#if 1 /* Digital audio support */

	if(ONE_WIRE_CONNECTION == connectionType)
	{
		pParam->AccesoryCapToken = (AC_USB_DIGITAL_AUDIO);
		pParam->AccPrefToken.Total_PreferenceCnt = 0;
	}
	else
	{
		pParam->AccesoryCapToken = (AC_ANALOG_LINE_OUT);
		pParam->AccPrefToken.Total_PreferenceCnt = 0;
	}
	
#else /* Analog Video output support */
	pParam->AccesoryCapToken = (AC_USB_DIGITAL_AUDIO|AC_ANALOG_VIDEO_OUT);

	pParam->AccPrefToken.Total_PreferenceCnt = 1;
	pParam->AccPrefToken.Pref[0].ClassID = 0;
	pParam->AccPrefToken.Pref[0].SettingID = 1;
	pParam->AccPrefToken.Pref[0].RestoreOnExit = 0;
#endif	
	

	pParam->ExtInfo = IPOD_Malloc_AudioPlayInfo();
	if(pParam->ExtInfo)
	{
		pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)pParam->ExtInfo;
//		pInfo->Disk = DiskInfo;
//		pInfo->Basic_Info.DevNo = DevNo;
		pInfo->Basic_Info.ipod_state = IPOD_PLUGED;
		
	}
	IPod_Buffer = new unsigned char[64*1024*4];
	IPOD_Malloc_Mem(&pParam->buff, IPod_Buffer);

}
#endif

DWORD iPodDisconnectionDetectThread(LPVOID pData) {
	HWND hWnd=(HWND)pData;

	CONTROLPROCESSOR_STATE	iPodDisconnectionState = IPOD_CONTROL_STATE_NONE;
	MSG RequestMsg;


	TLOG(CH_DISCNTCTL, LV_DEBUG, (TEXT("+ iPodDisconnectionDetectThread() > \r\n")));

	while ( IPOD_CONTROL_STATE_TERMINATED != iPodDisconnectionState ) 
	{
		
		if ( FALSE == GetMessage(&RequestMsg, NULL, 0, 0) )
		{
			break;
		}
		else
		{

			TLOG(CH_DISCNTCTL, LV_DEBUG, (TEXT("> It is an acceptable message.\r\n")));
			void *Handle = (void *)(RequestMsg.wParam);


			switch( RequestMsg.message )
			{
				case WM_DISCNTDETECT_EVENT:
				case WM_DISCNTDETECT_TERMINATE:
					TLOG(CH_DISCNTCTL, LV_DEBUG, (TEXT("> Set Disconnection to LIB.\r\n")));
					IPOD_SetDisconnectionStatus(Handle);
					break;
					
				default:
					break;
			}
		}

	}
	TLOG(CH_DISCNTCTL, LV_DEBUG, (TEXT("- iPodCMDControlThread() > \r\n")));

	return 0;


	
}


void USER_FUNC_func1(HWND hWnd, void *Handle)
{
	/* User command Example */
	unsigned char inform, major, minor;
	iPod_ExampleCode_getLingoProtocolVer(Handle, LINGO_EXTENDED_INTERFACE, &inform, &major, &minor);

}
void USER_FUNC_func2(HWND hWnd, void *Handle)
{

}
void USER_FUNC_func3(HWND hWnd, void *Handle, unsigned char *pAlbumArtData)
{

}

void USER_FUNC_func4(HWND hWnd, void *Handle)
{

}

void USER_FUNC_func5(HWND hWnd, void *Handle)
{

}

DWORD iPodCMDControlThread(LPVOID pData) {
	HWND hWnd=(HWND)pData;

	HANDLE hControlDevice = 0;
	HANDLE hI2CDevice = 0;
	HANDLE hGXPDevice = 0;

	CONTROLPROCESSOR_STATE	iPodControlState = IPOD_CONTROL_STATE_NONE;
	
	MSG RequestMsg;
	MSG ResponseMsg;
	BOOL IsAcceptableMessage = FALSE;
	int ret = 0;

	BOOL IsSuccess = FALSE;
	IPOD_ERROR	eCMDErrorCode = IPOD_NO_ERROR;
	BOOL IsFFREWMode = FALSE;
	unsigned short Info;
	unsigned long InitRetry;

	unsigned char strTitle[UI_MAX_STRING_LEN] = {0,};
	unsigned char strArtist[UI_MAX_STRING_LEN] = {0,};
	unsigned char strAlbum[UI_MAX_STRING_LEN] = {0,};
	unsigned char strIpodName[UI_MAX_STRING_LEN] = {0,};

	BRWSGetNameResInfo stBrwsGetNameResInfo;
	DWORD nBrwsMaxCountRequested = 0;

	void *iPodLibApiHandle = NULL;
	void *piPodLibApiHandle = 0;
	unsigned char *pAblumartData = 0;

	DWORD stCheckTimeGetNumCategorizedDBRecord = 0;
	DWORD stCurrentTick = 0;
	TLOG(CH_CMDCTL, LV_LOG, (TEXT("+ iPodCMDControlThread() > \r\n")));

	memset(&stBrwsGetNameResInfo, 0x00, sizeof(stBrwsGetNameResInfo) );

	ResponseMsg.hwnd = hWnd;
	ResponseMsg.message = WM_CMDCTRL_MAX;
	ResponseMsg.wParam = 0;
	ResponseMsg.lParam = 0;
	
	while ( IPOD_CONTROL_STATE_TERMINATED != iPodControlState ) {

		if ( FALSE == GetMessage(&RequestMsg, NULL, 0, 0) ){
			break;
		}
		else{

			TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("> It is an acceptable message.\r\n")));

			IsSuccess = FALSE;
			ResponseMsg.wParam = 0;
			ResponseMsg.lParam = 0;

			#ifdef TIME_CHECK
			DWORD nCurrentTick = GetTickCount();
			g_nMSGRequestCheckTick[RequestMsg.message] = nCurrentTick - g_nMSGRequestCheckTick[RequestMsg.message];
			#endif

			switch( RequestMsg.message ){
				//////////////////////////////////////////////////////////////
				//
				//               
				//
				case WM_CMDCTRL_INIT:
				//	TLOG(CH_CMDCTL, LV_DEBUG,
				//				(TEXT("WM_CMDCTRL_INIT, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					RETAILMSG(COUT_MSG,(TEXT("------>  WM_CMDCTRL_INIT, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					if ( IPOD_CONTROL_STATE_NONE == iPodControlState ){
						DWORD connection_type;
						DWORD driverID;
						DWORD EventThreadID;
						pIPOD_CMD_CTRL_PARAM piPodCMDCtrlParam;
						IPOD_DEFAULT_CONNECTION IsSupportIDPS;
						HANDLE hd=0;
						WCHAR strDeviceDriverName[16] = {0,};
						
						piPodCMDCtrlParam = (pIPOD_CMD_CTRL_PARAM)RequestMsg.wParam;
						connection_type = piPodCMDCtrlParam->m_ConnectionType;
				 		driverID = piPodCMDCtrlParam->m_DeviceNumber;	
						EventThreadID = piPodCMDCtrlParam->m_EventThreadID;
						iPodLibApiHandle = piPodCMDCtrlParam->m_iPodDev;

						free(piPodCMDCtrlParam);
						
						ResponseMsg.message = WM_CMDCTRL_SEND_HANDLE;
						ResponseMsg.wParam = (WPARAM)iPodLibApiHandle;
						ResponseMsg.lParam = 0;
						SendMessage(ResponseMsg.hwnd, ResponseMsg.message, ResponseMsg.wParam, ResponseMsg.lParam);
						
						// THC_XXX driver
						if (hControlDevice ){
							CloseHandle(hControlDevice);
							hControlDevice=0;
						}
						wsprintf(strDeviceDriverName, (L"THC%d:"), driverID);
						//hd=CreateFile(_T("THC1:"),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
						__try{
							hd=CreateFile(strDeviceDriverName, GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
						}
						__except(EXCEPTION_EXECUTE_HANDLER){
							hd=INVALID_HANDLE_VALUE;
							TLOG(CH_CMDCTL, LV_ERROR, (TEXT("[++++++++ERROR++++++++] > EXCEPTION on Create THC handle \r\n")));
						}
						if (hd==INVALID_HANDLE_VALUE) {
							hd=0;
							TLOG(CH_CMDCTL, LV_ERROR, 
										(TEXT("THC > INVALID_HANDLE_VALUE\r\n")));
						} else {
							hControlDevice=hd;
						}

						// I2C_XXX driver
						if (hI2CDevice){
							CloseHandle(hI2CDevice);
							hI2CDevice=0;
						}
						hd=CreateFile(_T("I2C1:"),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH,NULL);
						if (hd==INVALID_HANDLE_VALUE) {
							hd=0;
							TLOG(CH_CMDCTL, LV_ERROR, 
										(TEXT("I2C > INVALID_HANDLE_VALUE\r\n")));
						} else {
							hI2CDevice=hd;
						}

						#if (_WIN32_WCE < 0x500)
						#error WinCE4 or earlier is not supported
						#elif (_WIN32_WCE < 0x800)
						// WINCE5
						IAP_CP_Init(0);
						#else
						// WINCE6
						// GXP_XXX driver
						if (hGXPDevice){
							CloseHandle(hGXPDevice);
							hGXPDevice=0;
						}
						hd=CreateFile(_T("GXP1:"),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH,NULL);
						if (hd==INVALID_HANDLE_VALUE) {
							hd=0;
							TLOG(CH_CMDCTL, LV_ERROR,
										(TEXT("GXP > INVALID_HANDLE_VALUE\r\n")));
						} else {
							BOOL ret_cp_init = FALSE;

							hGXPDevice=hd;
							ret_cp_init = IAP_CP_Init( hGXPDevice );

							TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("IAP_CP_Init() return %d\r\n"),ret_cp_init));
						}
						#endif

#if (_WIN32_WCE < 0x500)
	#error WinCE4 or earlier is not supported
#elif (_WIN32_WCE < 0x800)
						if ( hControlDevice &&  hI2CDevice )
#else
						if ( hControlDevice &&  hI2CDevice && hGXPDevice )
#endif
						{
							IPOD_INIT_PARAM stDeviceInitParam;
							IPOD_INIT_CHANNRL_PARAM stChannelParam;
							IPOD_LINGO_INFO_DATA stLingoInfoData;
							unsigned int CheckOption=1;

							//eCMDErrorCode = IPOD_Open(&iPodLibApiHandle); move to dlg
							if(NULL != iPodLibApiHandle)
							{
								eCMDErrorCode = IPOD_NO_ERROR;	
							}
							else
							{
								eCMDErrorCode = IPOD_INVALID_HANDLE;
							}
							if(IPOD_NO_ERROR == eCMDErrorCode)
							{
								extern HWAVEOUT h_output;
								//if (h_output)
								{
									//waveOutSetVolume(0,0);
									//waveOutSetVolume(0,0);

									//AVSET::Mute();
								}

								ResponseMsg.message = WM_CMDCTRL_SEND_HANDLE;
								ResponseMsg.wParam = (WPARAM)iPodLibApiHandle;
								ResponseMsg.lParam = 0;

								SendMessage(ResponseMsg.hwnd, ResponseMsg.message, ResponseMsg.wParam, ResponseMsg.lParam);

								piPodLibApiHandle = (void*)iPodLibApiHandle;

								memset(&stChannelParam, 0x00, sizeof(IPOD_INIT_CHANNRL_PARAM));
								stChannelParam.iPod_Handle = piPodLibApiHandle;
								IPOD_API_WINCE_USB_InitChannelParam(&stChannelParam, hControlDevice, hI2CDevice, EventThreadID, IPOD_I2C_CH);
								eCMDErrorCode = IPOD_InitChannel(piPodLibApiHandle, &stChannelParam);
								if(IPOD_NO_ERROR == eCMDErrorCode)
								{
									// 增加线程优先级
									//HANDLE HControlThread =  IPOD_API_GetControlThreadID(piPodLibApiHandle);							 
									//HANDLE hDataThread = IPOD_API_GetDataThreadID(piPodLibApiHandle);
									//CeSetThreadPriority(HControlThread, 240);
									//CeSetThreadPriority(hDataThread, 240);
									for(InitRetry = 0; InitRetry<IPOD_INIT_RETRY_CNT; InitRetry++)
									{
										if(IPOD_IDPS_TIMEOUT == eCMDErrorCode)
										{
											CheckOption = 0;
											eCMDErrorCode = IPOD_NO_ERROR;
										}
										else
										{
											eCMDErrorCode = IPOD_CheckiPodTaskStatus(piPodLibApiHandle);
										}
										if(IPOD_NO_ERROR == eCMDErrorCode)
										{
											if(1 == CheckOption)
											{
												
												IPOD_API_CheckiPodOption(piPodLibApiHandle, &stDeviceInitParam, &stLingoInfoData);
											}

											IPOD_API_WINCE_USB_InitParam(piPodLibApiHandle, &stDeviceInitParam, &stLingoInfoData, 
																(IAP_CONNECTION_MODE)connection_type);
										//	IPOD_API_WINCE_USB_InitParamOSApp(piPodLibApiHandle, &stDeviceInitParam, &stLingoInfoData, 
										//						(IAP_CONNECTION_MODE)connection_type);

										
											IPOD_API_GetIDPSSupport(piPodLibApiHandle, &IsSupportIDPS);
											if(connection_type == ONE_WIRE_CONNECTION && IsSupportIDPS == IPOD_IDPS_NOT_SUPPORT)
											{
												/* need to set fullbandwidth to get sampling rate. */
												SendMessage(ResponseMsg.hwnd, WM_AUDIOCTRL_SET_FULLBAND_WIDTH, NULL, NULL);
											}

											TLOG(CH_INITCTL, LV_DEBUG, (TEXT("iPod_Init() start handle : 0x%x\r\n"),piPodLibApiHandle));
											
											eCMDErrorCode = IPOD_Init(piPodLibApiHandle, &stDeviceInitParam );
											Sleep(1000);
											TLOG(CH_INITCTL, LV_DEBUG, (TEXT("iPod_Init() return %d\r\n"),eCMDErrorCode));
											//if (h_output)
											{
												//waveOutSetVolume(0,0xFFFFFFFF);
												//waveOutSetVolume(0,0xFFFFFFFF);
												//if (!(bool)sysConfig.bMute)
												//{
												//	AVSET::UnMute();
												//}
												
											}										
											if((IPOD_COMMAND_TIMEOUT == eCMDErrorCode) || (IPOD_COMMAND_FAILED == eCMDErrorCode) 
												||(IPOD_IO_CP_ERROR == eCMDErrorCode) || (IPOD_IDPS_TIMEOUT == eCMDErrorCode) || (IPOD_RETRY_IDPS == eCMDErrorCode))
											{
												continue;
											}
											else
											{
												break;
											}


										}
									}
								}
								if ( IS_CMDERROR(eCMDErrorCode) ){
									TLOG(CH_CMDCTL, LV_ERROR, 
												(TEXT("iPod init fail(%d).\r\n"), eCMDErrorCode));

									iPodControlState = IPOD_CONTROL_STATE_NONE;
									IPOD_Free_AudioPlayInfo(piPodLibApiHandle);
									IPOD_Close(piPodLibApiHandle);
								}
								else{
									//int length, time, status;
									long nCurrentIndex = 0;
									long nCount = 0;

									TLOG(CH_CMDCTL, LV_LOG, 
												(TEXT("iPod init success\r\n")));
									
									IPOD_CheckPlayStatus(piPodLibApiHandle);
									IsFFREWMode = FALSE;
									
									if(IPOD_DB_Init(piPodLibApiHandle)>0)
									{
										void *ExtInfo = IPOD_GetExtInfo(piPodLibApiHandle);
										pIPOD_PLAY_INFO pInfo  = (pIPOD_PLAY_INFO)ExtInfo;

										nCount = pInfo->TotalPlayNum;
										iPodControlState = IPOD_CONTROL_STATE_INITIALIZED;
										ResponseMsg.lParam = pInfo->CurrentIdx;
										IsSuccess = TRUE;
									}
									

								}
							}
							else
							{
								TLOG(CH_CMDCTL, LV_WARN, 
											(TEXT("iPod open error \r\n")));
							}
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("Invalid device handle\r\n")));
							if(NULL != iPodLibApiHandle)
							{
								IPOD_Free_AudioPlayInfo(iPodLibApiHandle);
								eCMDErrorCode = IPOD_Close(iPodLibApiHandle);
								if ( IS_FAIL(eCMDErrorCode) ){
									TLOG(CH_CMDCTL, LV_ERROR, (TEXT("IPOD_Close() > Fail(%d).\r\n"), eCMDErrorCode));
								}
							}
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_INIT > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_INIT;
					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					break;
					
				case WM_CMDCTRL_STOP:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_STOP, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					//IPOD_SetDisconnectionStatus(piPodLibApiHandle); --> moved 
					IPOD_Free_AudioPlayInfo(piPodLibApiHandle);
					eCMDErrorCode = IPOD_Close(piPodLibApiHandle);
					if ( IS_FAIL(eCMDErrorCode) ){
						TLOG(CH_CMDCTL, LV_ERROR, (TEXT("IPOD_Deinit() > Fail(%d).\r\n"), eCMDErrorCode));
					}

					iPodLibApiHandle = 0;
					piPodLibApiHandle = 0;

					IsSuccess = TRUE;
					iPodControlState = IPOD_CONTROL_STATE_NONE;
					ResponseMsg.message = WM_CMDCTRL_RES_STOP;
					ResponseMsg.wParam = 1;

					break;
					
				case WM_CMDCTRL_TERMINATE:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_TERMINATE, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

#if (_WIN32_WCE < 0x500)
	#error WinCE4 or earlier is not supported
#elif (_WIN32_WCE < 0x800)
					if (hControlDevice && hI2CDevice)
#else
					if (hControlDevice && hI2CDevice && hGXPDevice) 
#endif
					{
					//	int length, time, status;
						IPOD_DR_PLAY_STATUS playStatus;
					
						IPOD_Free_AudioPlayInfo(piPodLibApiHandle);
						eCMDErrorCode = IPOD_Close( piPodLibApiHandle );
						if ( IS_CMDERROR(eCMDErrorCode) ){
							TLOG(CH_CMDCTL, LV_ERROR, (TEXT("IPOD_Deinit() > Fail(%d).\r\n"), eCMDErrorCode));
						}
	
					//	if( IS_CMDOK(IPOD_GetStatus( piPodLibApiHandle, &length, &time, &status)) ){
						if(IS_CMDOK(IPOD_API_GetDRPlayStatus(piPodLibApiHandle, &playStatus)))
						{
							if (IPOD_DR_PLAYING == playStatus)
							{
								if ( IsFFREWMode ){
									eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW);
									if ( IS_CMDOK(eCMDErrorCode) ){
										IsSuccess = TRUE;
									}
									IsFFREWMode = FALSE;
								}
								ret = IPOD_ButtonControl( piPodLibApiHandle, PLAYPAUSE );
								if ( IS_CMDOK(ret) ){
									//IsSuccess = TRUE;
								}
							}
						}
					}
					IsSuccess = TRUE;
					
					iPodControlState = IPOD_CONTROL_STATE_TERMINATED;

					ResponseMsg.message = WM_CMDCTRL_RES_TERMINATE;
					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					break;

				//////////////////////////////////////////////////////////////
				//
				//               PLAYBACK
				//
				case WM_CMDCTRL_PLAY:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_PLAY, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					
					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState )
					{
					//	int length, time, status;
						IPOD_DR_PLAY_STATUS playStatus;
						unsigned long NewTrackInfoStatus;
						IPOD_UPDATE_PLAY_STATUS UpdatePlayStatus = IPOD_UPDATE_PLAY;
						
						//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----1\r\n")));

						if(IS_CMDOK(IPOD_CheckNewTrackInfoStatus(piPodLibApiHandle, &NewTrackInfoStatus)))
						{
							//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----2\r\n")));
							if(0x00ul == NewTrackInfoStatus)
							{
								//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----3\r\n")));
								IPOD_ButtonControl( piPodLibApiHandle, NEXTTRACK );
								Sleep(10);
								IPOD_ButtonControl( piPodLibApiHandle, PREVIOUSTRACK );
							}
						}
						//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----4\r\n")));
						TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("IsFFREWMode(%d)\r\n"), IsFFREWMode));
						if ( IsFFREWMode ){
							//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----5\r\n")));
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW );
							if ( IS_CMDOK(eCMDErrorCode) ){
								//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----6\r\n")));
								IsSuccess = TRUE;
							}
							IsFFREWMode = FALSE;
						}
				//		else if( IS_CMDOK(IPOD_GetStatus( piPodLibApiHandle, &length, &time, &status)) )
						else if(IS_CMDOK(IPOD_API_GetDRPlayStatus(piPodLibApiHandle, &playStatus)))
						{
							//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----16\r\n")));
							if (IPOD_DR_PLAYING == playStatus){
								IsSuccess = TRUE;
								UpdatePlayStatus = IPOD_UPDATE_PAUSE;
								//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----7\r\n")));
							}
							else{														
								//eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, PLAYPAUSE);
								eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, NEWPLAY);
								//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----8\r\n")));
								
								if ( IS_CMDOK(eCMDErrorCode) ){
									IsSuccess = TRUE;
								}
							}
						}
						else{
							TLOG(CH_CMDCTL, LV_DEBUG, (TEXT("Invalid state\r\n"), IsFFREWMode));
							//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----9\r\n")));
						}
						if(UpdatePlayStatus == IPOD_UPDATE_PAUSE)
						{
							ResponseMsg.message = WM_CMDCTRL_RES_PAUSE;
						}
						else
						{
							ResponseMsg.message = WM_CMDCTRL_RES_PLAY;
						}
						ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					}	
					else{
						//RETAILMSG(1, (TEXT("WM_CMDCTRL_PLAY -----10\r\n")));
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_PLAY > Invalid state or invalid message.\r\n")));
						ResponseMsg.message = WM_CMDCTRL_RES_PLAY;
						ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					}
					break;
				case WM_CMDCTRL_PLAY_IN_BRWSLIST:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_PLAY_IN_BRWSLIST, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					
					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState )
					{
						IsSuccess = TRUE;
						ResponseMsg.message = WM_CMDCTRL_RES_PLAY;
						ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					}
					break;
				case WM_CMDCTRL_PAUSE:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_PAUSE, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----1\r\n")));
					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
					//	int length, time, status;
						IPOD_DR_PLAY_STATUS playStatus;
						IPOD_UPDATE_PLAY_STATUS UpdatePlayStatus = IPOD_UPDATE_PAUSE;
						//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----2\r\n")));
						if ( IsFFREWMode ){
							//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----31\r\n")));
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW);
							if ( IS_CMDOK(eCMDErrorCode) ){
								//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----4\r\n")));
								IsSuccess = TRUE;
							}
							IsFFREWMode = FALSE;
						}

					//	eCMDErrorCode = IPOD_GetStatus( piPodLibApiHandle, &length, &time, &status);
						eCMDErrorCode = IPOD_API_GetDRPlayStatus(piPodLibApiHandle, &playStatus);
						if( IS_CMDOK(eCMDErrorCode) ){
							//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----5\r\n")));
							if (IPOD_DR_PLAYING == playStatus){		
								//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----6\r\n")));
								eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, NEWPAUSE);
								if ( IS_CMDOK(eCMDErrorCode) ){
									//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----7\r\n")));
									IsSuccess = TRUE;						
								}
								else{
									//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----8\r\n")));
									TLOG(CH_CMDCTL, LV_WARN, (TEXT("WM_CMDCTRL_PAUSE > IPOD_ButtonControl() Failed(%d)\r\n"), eCMDErrorCode));
								}
							}
							else{
								//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----9\r\n")));
								IsSuccess = TRUE;
								UpdatePlayStatus = IPOD_UPDATE_PLAY;
							}
						}
						else{
							//RETAILMSG(1, (TEXT("WM_CMDCTRL_PAUSE -----10\r\n")));
							TLOG(CH_CMDCTL, LV_WARN, (TEXT("WM_CMDCTRL_PAUSE > IPOD_GetStatus() Failed(%d)\r\n"), eCMDErrorCode));
						}

						if(UpdatePlayStatus == IPOD_UPDATE_PLAY)
						{
							ResponseMsg.message = WM_CMDCTRL_RES_PLAY;
						}
						else
						{
							ResponseMsg.message = WM_CMDCTRL_RES_PAUSE;
						}
						ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
						
					}	
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_PAUSE > Invalid state or invalid message.\r\n")));
						ResponseMsg.message = WM_CMDCTRL_RES_PAUSE;
						ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					}
					break;

				case WM_CMDCTRL_NEXTTRACK:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_NEXTTRACK, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ){
						if ( IsFFREWMode ){
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW);
							if ( IS_CMDOK(eCMDErrorCode) ){
								IsSuccess = TRUE;
							}
							IsFFREWMode = FALSE;
						}
						ret = IPOD_ButtonControl( piPodLibApiHandle, NEXTTRACK);
						if ( IS_CMDOK(ret) ){
							IsSuccess = TRUE;
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, (TEXT("WM_CMDCTRL_NEXTTRACK > Failed\r\n") ));
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_NEXTTRACK > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_NEXTTRACK;
					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					break;

				case WM_CMDCTRL_PREVIOUSTRACK:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_PREVIOUSTRACK, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ){
						if ( IsFFREWMode ){
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW);
							if ( IS_CMDOK(eCMDErrorCode) ){
								IsSuccess = TRUE;
							}
							IsFFREWMode = FALSE;
						}
						ret = IPOD_ButtonControl( piPodLibApiHandle, PREVIOUSTRACK);
						if ( IS_CMDOK(ret) ){
							IsSuccess = TRUE;
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, (TEXT("WM_CMDCTRL_PREVIOUSTRACK > Failed\r\n") ));
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_PREVIOUSTRACK > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_PREVIOUSTRACK;
					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					break;

				case WM_CMDCTRL_FF:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_FF, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
					//	int length, time, status;
						IPOD_DR_PLAY_STATUS playStatus;
						if ( IsFFREWMode ){
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW);
							if ( IS_CMDOK(eCMDErrorCode) ){
								IsSuccess = TRUE;
							}
							IsFFREWMode = FALSE;
						}
					//	if( IS_CMDOK(IPOD_GetStatus(piPodLibApiHandle, &length, &time, &status )))
						if(IS_CMDOK(IPOD_API_GetDRPlayStatus(piPodLibApiHandle, &playStatus)))
						{
							if (IPOD_DR_PLAYING == playStatus){
								ret = IPOD_ButtonControl( piPodLibApiHandle, STARTFF );
								if ( IS_CMDOK(ret) ){
									IsFFREWMode = TRUE;
									IsSuccess = TRUE;
								}
							}
						}
					}	
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_FF > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_FF;
					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;

					break;

				case WM_CMDCTRL_REW:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_REW, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
					//	int length, time, status;
						IPOD_DR_PLAY_STATUS playStatus;
						if ( IsFFREWMode ){
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW);
							if ( IS_CMDOK(eCMDErrorCode) ){
								IsSuccess = TRUE;
							}
							IsFFREWMode = FALSE;
						}
					//	if( IS_CMDOK(IPOD_GetStatus( piPodLibApiHandle, &length, &time, &status )))
						if(IS_CMDOK(IPOD_API_GetDRPlayStatus(piPodLibApiHandle, &playStatus)))
						{
							if (IPOD_DR_PLAYING == playStatus){
								ret = IPOD_ButtonControl( piPodLibApiHandle, STARTREW );
								if ( IS_CMDOK(ret) ){
									IsFFREWMode = TRUE;
									IsSuccess = TRUE;
								}
							}
						}
					}	
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_REW > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_REW;
					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;

					break;

				case WM_CMDCTRL_GETCURRENTTRACKINDEX:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_GETCURRENTTRACKINDEX, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						long nCurrentIndex = 0;

						eCMDErrorCode = IPOD_GetCurrentFileNum( piPodLibApiHandle, &nCurrentIndex );
						if ( IS_CMDOK(eCMDErrorCode) ){
							IsSuccess = TRUE;
							ResponseMsg.wParam = (DWORD)nCurrentIndex;
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("IPOD_GetCurrentFileNum() > Failed(%d).\r\n"), eCMDErrorCode));
						}

					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_GETCURRENTINDEX > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_GETCURRENTTRACKINDEX;
					ResponseMsg.wParam = ( IsSuccess ) ? ResponseMsg.wParam : (0xFFFFFFFF);

					break;
				case WM_CMDCTRL_GETTOTALPLAYTRACKS:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_GETTOTALPLAYTRACKS, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						long nTotalTrackNum = 0;

						eCMDErrorCode = IPOD_GetNumPlayingTracks( piPodLibApiHandle, &nTotalTrackNum );
						if ( IS_CMDOK(eCMDErrorCode) ){
							IsSuccess = TRUE;
							ResponseMsg.wParam = (DWORD)nTotalTrackNum;
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("IPOD_GetNumPlayingTracks() > Failed(%d).\r\n"), eCMDErrorCode));
						}

					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_GETTOTALPLAYTRACKS > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_GETTOTALPLAYTRACKS;
					ResponseMsg.wParam = ( IsSuccess ) ? ResponseMsg.wParam : (0xFFFFFFFF);
					break;
				case WM_CMDCTRL_RES_GETIPODNAME:
					{
						TLOG(CH_CMDCTL, LV_DEBUG,
							(TEXT("WM_CMDCTRL_RES_GETIPODNAME, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

						if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
							long dwActualLen = 0;
							eCMDErrorCode = IPOD_GetIPODName( piPodLibApiHandle,  strIpodName, MAX_PATH, &dwActualLen);
							if ( IS_CMDOK(eCMDErrorCode) ){
								IsSuccess = TRUE;
								ResponseMsg.wParam = (DWORD)dwActualLen;
								ResponseMsg.lParam = (LPARAM)&strIpodName[0];
								strIpodName[dwActualLen] = 0;//cyz
								strIpodName[dwActualLen+1] = 0;//cyz
							}
							else{
								TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("IPOD_GetIPODName() > Failed(%d).\r\n"), eCMDErrorCode));
							}

						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
								(TEXT("WM_CMDCTRL_GETTOTALPLAYTRACKS > Invalid state or invalid message.\r\n")));
						}

						ResponseMsg.message = WM_CMDCTRL_RES_GETIPODNAME;
						ResponseMsg.wParam = ( IsSuccess ) ? ResponseMsg.wParam : (0xFFFFFFFF);
						break;
					}
				case WM_CMDCTRL_GETTITLE:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_GETTITLE, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						int nIndex = RequestMsg.wParam;
						long nStringLen = 0;
						unsigned char strName[UI_MAX_STRING_LEN] = {0,};

						if ( 0xFFFFFFFF == nIndex ){
							long nCurrentIndex = 0;
							eCMDErrorCode = IPOD_GetCurrentFileNum( piPodLibApiHandle, &nCurrentIndex );
							if ( IS_CMDOK(eCMDErrorCode) ){
								nIndex = (int)nCurrentIndex;
							}
							else{
								nIndex = 0;
							}
						}

						eCMDErrorCode = IPOD_GetTitle(piPodLibApiHandle, nIndex, &strTitle[0], UI_MAX_STRING_LEN, &nStringLen );
						if ( IS_CMDOK(eCMDErrorCode) ){
							IsSuccess = TRUE;
							ResponseMsg.wParam = (DWORD)&strTitle[0];
							ResponseMsg.lParam = (DWORD)nStringLen;
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("IPOD_GetTitle() > Failed(%d).\r\n"), ret));
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_GETTITLE > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_GETTITLE;

					break;

				case WM_CMDCTRL_GETARTIST:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_GETARTIST, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						int nIndex = RequestMsg.wParam;
						long nStringLen = 0;
						unsigned char strName[UI_MAX_STRING_LEN] = {0,};

						if ( 0xFFFFFFFF == nIndex ){
							long nCurrentIndex = 0;
							eCMDErrorCode = IPOD_GetCurrentFileNum( piPodLibApiHandle, &nCurrentIndex );
							if ( IS_CMDOK(eCMDErrorCode) ){
								nIndex = (int)nCurrentIndex;

								TLOG(CH_CMDCTL, LV_DEBUG, 
											(TEXT("IPOD_GetCurrentFileNum() > nCurrentIndex=%d.\r\n"), nCurrentIndex));

							}
							else{
								nIndex = 0;
							}
						}

						eCMDErrorCode = IPOD_GetArtist(piPodLibApiHandle, nIndex, &strArtist[0], UI_MAX_STRING_LEN, &nStringLen );
						if ( IS_CMDOK(eCMDErrorCode) ){
							IsSuccess = TRUE;
							ResponseMsg.wParam = (DWORD)&strArtist[0];
							ResponseMsg.lParam = (DWORD)nStringLen;
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("IPOD_GetArtist() > Failed(%d)\r\n"), eCMDErrorCode));
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_GETARTIST > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_GETARTIST;

					break;

				case WM_CMDCTRL_GETALBUM:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_GETALBUM, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						int nIndex = RequestMsg.wParam;
						long nStringLen = 0;
						unsigned char strName[UI_MAX_STRING_LEN] = {0,};

						if ( 0xFFFFFFFF == nIndex ){
							long nCurrentIndex = 0;
							eCMDErrorCode = IPOD_GetCurrentFileNum( piPodLibApiHandle, &nCurrentIndex );
							if ( IS_CMDOK(eCMDErrorCode) ){
								nIndex = (int)nCurrentIndex;
								TLOG(CH_CMDCTL, LV_DEBUG, 
											(TEXT("IPOD_GetCurrentFileNum() > nCurrentIndex=%d.\r\n"), nCurrentIndex));
							}
							else{
								nIndex = 0;
							}
						}

						eCMDErrorCode = IPOD_GetAlbum( piPodLibApiHandle, nIndex, &strAlbum[0], UI_MAX_STRING_LEN, &nStringLen );
						if ( IS_CMDOK(eCMDErrorCode) ){
							IsSuccess = TRUE;
							ResponseMsg.wParam = (DWORD)&strAlbum[0];
							ResponseMsg.lParam = (DWORD)nStringLen;
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("IPOD_GetAlbum() > Failed(%d)\r\n"), eCMDErrorCode));
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_GETALBUM > Invalid state or invalid message.\r\n")));
					}


					ResponseMsg.message = WM_CMDCTRL_RES_GETALBUM;
					break;

				case WM_CMDCTRL_GETALBUMART:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("iPodCMDControlThread() > msgid=WM_CMDCTRL_GETALBUMART, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						int nIndex = RequestMsg.wParam;
						DWORD nStringLen = 0;
						unsigned char strName[UI_MAX_STRING_LEN] = {0,};

						if ( 0xFFFFFFFF == nIndex ){
							long nCurrentIndex = 0;
							eCMDErrorCode = IPOD_GetCurrentFileNum( piPodLibApiHandle, &nCurrentIndex );
							if ( IS_CMDOK(eCMDErrorCode) ){
								nIndex = (int)nCurrentIndex;
								TLOG(CH_CMDCTL, LV_DEBUG, 
											(TEXT("IPOD_GetCurrentFileNum() > nCurrentIndex=%d.\r\n"), nCurrentIndex));
							}
							else{
								nIndex = 0;
								TLOG(CH_CMDCTL, LV_WARN, 
											(TEXT("IPOD_GetCurrentFileNum() > Failed(%d)\r\n"), eCMDErrorCode));
							}
						}
						//REVIEWME@20100201, Test iPod library updated for IDPS, review me
						ArtworkData ArtData;
						unsigned long nActualLen = 0;
						ArtData.pImageData=(unsigned char *)RequestMsg.lParam;
						pAblumartData = (unsigned char *)RequestMsg.lParam;
						eCMDErrorCode = IPOD_GetAlbumArt( piPodLibApiHandle, nIndex,&ArtData, 2*600*600, &nActualLen);
						//eCMDErrorCode = IPOD_DR_GetAlbumArt( piPodLibApiHandle, nIndex,&ArtData, 2*600*600, &nActualLen);
						switch (eCMDErrorCode) {
							case 17:	// test
							case IPOD_NO_ERROR:
								IsSuccess = TRUE;
								ResponseMsg.wParam = ArtData.sWidth;
								ResponseMsg.lParam = ArtData.sHeight;

								//TLOG(CH_CMDCTL, LV_LOG, 
								//		(TEXT("[ALBUMART] pixelformat=%d, w=%d, h=%d, x1=%d, y1=%d, y2=%d, y2=%d, RowSize=%d, TotalSize=%d\r\n"), 
								//			ArtData.cPixelFormat, ArtData.sWidth, ArtData.sHeight, ArtData.sTopLeftX, ArtData.sTopLeftY, ArtData.sBottomRightX,
								//			ArtData.sBottomRightY, ArtData.uiRowSize, ArtData.uiTotalSize));
								TLOG(CH_CMDCTL, LV_DEBUG, 
											(TEXT("IPOD_GetAlbumArt() > Success(%d)\r\n"), eCMDErrorCode));

								break;
							case IPOD_NO_DATA:
								// height=0, height=0
								ResponseMsg.wParam = 0;
								ResponseMsg.lParam = 0;
								TLOG(CH_CMDCTL, LV_LOG, 
											(TEXT("IPOD_GetAlbum() > No Album Art\r\n")));
								break;
							default:
								TLOG(CH_CMDCTL, LV_WARN, 
											(TEXT("IPOD_GetAlbum() > Failed(%d)\r\n"), eCMDErrorCode));
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_GETALBUM > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_RES_GETALBUMART;
					break;

				case WM_CMDCTRL_INFORM_SAMPLINGFREQ_CHECKED:
					//REVIEWME@20100201, Test iPod library updated for IDPS
					#if 1 // NOT READY
					Info = (unsigned short)RequestMsg.wParam;
					/* TrackNewAudioAttribute's AccessoryAck move to iPod Library. */
					//eCMDErrorCode = IPOD_SendAccAck(piPodLibApiHandle, Info);
					if ( IS_CMDOK(eCMDErrorCode) ){
						 IsSuccess = TRUE;
					}
					#endif
					IsSuccess = TRUE;
					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					ResponseMsg.message = WM_CMDCTRL_RES_INFORM_SAMPLINGFREQ_CHECKED;
					break;

				case WM_CMDCTRL_GET_DEVICEDISPLAYINFO:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_GET_DEVICEDISPLAYINFO, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {

						DEVICEDISPLAY_INFO *pstDeviceDisplayInfo = (DEVICEDISPLAY_INFO*)RequestMsg.wParam;
						if ( NULL == pstDeviceDisplayInfo )
						{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("WM_CMDCTRL_GET_DEVICEDISPLAYINFO() > Invalid param > pstDeviceDisplayInfo = (0x%x)\r\n"), pstDeviceDisplayInfo));
						}
						else
						{
							int width,height;
							IPOD_PIXEL_FORMAT format;
							eCMDErrorCode = IPOD_GetColorDisplayLimit( piPodLibApiHandle, &format, &width, &height );
							if ( IS_CMDOK(eCMDErrorCode) )
							{
								pstDeviceDisplayInfo->width = width;
								pstDeviceDisplayInfo->height = height;
								pstDeviceDisplayInfo->displayformat = format;
							
								IsSuccess = TRUE;
								ResponseMsg.lParam = (DWORD)pstDeviceDisplayInfo;
							}
						}
					}

					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					ResponseMsg.message = WM_CMDCTRL_RES_DEVICEDISPLAYINFO;

					break;

				case WM_CMDCTRL_SET_DEVICEDISPLAYIMAGE:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_SET_DEVICEDISPLAYIMAGE, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));

					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {

						DEVICEDISPLAY_INFO *pstDeviceDisplayInfo = (DEVICEDISPLAY_INFO*)RequestMsg.wParam;
						if ( NULL == pstDeviceDisplayInfo )
						{
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("WM_CMDCTRL_SET_DEVICEDISPLAYIMAGE() > Invalid param > pstDeviceDisplayInfo = (0x%x)\r\n"), pstDeviceDisplayInfo));

						}
						else
						{

							eCMDErrorCode=IPOD_SetBitmap( piPodLibApiHandle, 
												IPOD_PIXEL_RGB_565_LITTLE,
												pstDeviceDisplayInfo->width,
												pstDeviceDisplayInfo->height,
												pstDeviceDisplayInfo->pImage);
							if ( IS_CMDOK(eCMDErrorCode)) 
							{
								IsSuccess = TRUE;
							}
							else
							{
								TLOG(CH_CMDCTL, LV_DEBUG, 
											(TEXT("WM_CMDCTRL_SET_DEVICEDISPLAYIMAGE() > IPOD_SetBitmap() Failed > eCMDErrorCode=-x%x\r\n"), eCMDErrorCode));

							}
						}
					}

					ResponseMsg.wParam = ( IsSuccess ) ? 1 : 0;
					ResponseMsg.message = WM_CMDCTRL_RES_DEVICEDISPLAYIMAGE;

					break;




				//////////////////////////////////////////////////////////////
				//
				//               BROWSER
				//

				case WM_CMDCTRL_BRWS_INIT:

					TLOG(CH_CMDCTL, LV_DEBUG,
						(TEXT("WM_CMDCTRL_BRWS_INIT, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					stCurrentTick = GetTickCount();
					if(stCurrentTick - stCheckTimeGetNumCategorizedDBRecord < IPOD_1S_TIME_CHECK)
					{
						TLOG(CH_CMDCTL, LV_WARN, 
							(TEXT("WM_CMDCTRL_BRWS_INIT > ATS Time Error.\r\n")));
					}
					else if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						CategoryType eCategory = (CategoryType)RequestMsg.wParam;
						IPOD_SEL_DB_TYPE selType = (IPOD_SEL_DB_TYPE)RequestMsg.lParam;
						long nCount = 0;

						if (IPOD_LIB_ALL == eCategory ){
							eCategory = IPOD_LIB_GENRE;
						}
						if (selType == DBSEL_VIDEO){//cyz
							eCMDErrorCode = IPOD_SelectDBHierarchy( piPodLibApiHandle,  DBSEL_VIDEO);
						}
						else{
							eCMDErrorCode = IPOD_ResetDB( piPodLibApiHandle );
						}
						
						if ( IS_CMDOK(eCMDErrorCode) ){
							eCMDErrorCode = IPOD_SelectListType( piPodLibApiHandle, eCategory, &nCount );
							if ( IS_CMDOK(eCMDErrorCode) ){
								IsSuccess = TRUE;
								ResponseMsg.wParam = nCount;
								ResponseMsg.lParam = (DWORD) eCategory;
								stCheckTimeGetNumCategorizedDBRecord = stCurrentTick;
							}
							else{
								TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("IPOD_SelectListType() > Failed(%d).\r\n"), eCMDErrorCode));
							}
						}
						else{
							TLOG(CH_CMDCTL, LV_WARN, 
								(TEXT("IPOD_ResetDB() > Failed(%d).\r\n"), eCMDErrorCode));	
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
							(TEXT("WM_CMDCTRL_BRWS_INIT > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_BRWS_RES_INIT;
					ResponseMsg.wParam = ( IsSuccess ) ? ResponseMsg.wParam : 0xFFFFFFFF;

					break;

				case WM_CMDCTRL_BRWS_SELECT:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_BRWS_SELECT, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					stCurrentTick = GetTickCount();
					if(stCurrentTick - stCheckTimeGetNumCategorizedDBRecord < IPOD_1S_TIME_CHECK)
					{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_BRWS_SELECT > ATS Time Error.\r\n")));
					}
					else if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						CategoryType eCategory = (CategoryType)RequestMsg.wParam;
						int zIndex = (int)RequestMsg.lParam;
						long nCount = 0;
						if ( IsFFREWMode ){
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, ENDFFREW);
							if ( IS_CMDOK(eCMDErrorCode) ){
								IsSuccess = TRUE;
							}
							IsFFREWMode = FALSE;
						}
						if ( IPOD_LIB_TRACK == eCategory ){
							eCMDErrorCode = IPOD_ButtonControl( piPodLibApiHandle, STOP);
							if ( IS_CMDERROR(eCMDErrorCode) ){
								TLOG(CH_CMDCTL, LV_WARN, 
											(TEXT("IPOD_ButtonControl(STOP) > Falied(%d).\r\n"), eCMDErrorCode));
							}
						}
						if ( IPOD_LIB_TRACK == eCategory)
						{
							eCMDErrorCode = IPOD_PlayCurrentSelection(piPodLibApiHandle, zIndex); /* this command is deprecated. it is used for iPod nano 1G. */
						}
						else
						{
							//	eCMDErrorCode = IPOD_SelectSortList( piPodLibApiHandle, eCategory, zIndex, SORTBYARTIST );
							eCMDErrorCode = IPOD_SelectList(piPodLibApiHandle, eCategory, zIndex);
							
						}

						if ( IS_CMDERROR(eCMDErrorCode) ){
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("IPOD_SelectSortList > Falied(%d).\r\n"), eCMDErrorCode));
						}
						else{
							if ( IPOD_LIB_TRACK == eCategory ){
								IsSuccess = TRUE;
								ResponseMsg.wParam = eCategory;
								ResponseMsg.lParam = (DWORD)0;
							}
							else{
								eCategory = IPOD_GetSubCategory( eCategory);

								eCMDErrorCode = IPOD_SelectListType( piPodLibApiHandle, eCategory, &nCount );
								if ( IS_CMDOK(eCMDErrorCode) ){
									IsSuccess = TRUE;
									ResponseMsg.wParam = eCategory;
									ResponseMsg.lParam = (DWORD)nCount;
								}
								else{
									TLOG(CH_CMDCTL, LV_WARN, 
												(TEXT("IPOD_SelectListType > Falied(%d).\r\n"), eCMDErrorCode));
								}
							}
							stCheckTimeGetNumCategorizedDBRecord = stCurrentTick;
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_BRWS_SELECT > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_BRWS_RES_SELECT;
					ResponseMsg.lParam = ( IsSuccess ) ? ResponseMsg.lParam : 0xFFFFFFFF;
					break;

				case WM_CMDCTRL_BRWS_MOVEUPPER:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_BRWS_MOVEUPPER, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					stCurrentTick = GetTickCount();
					if(stCurrentTick - stCheckTimeGetNumCategorizedDBRecord < IPOD_1S_TIME_CHECK)
					{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_BRWS_MOVEUPPER > ATS Time Error.\r\n")));
					}
					else if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						CategoryType eCategory = (CategoryType)RequestMsg.wParam;
						int zIndex = (-1);
						long nCount = 0;

						eCategory = IPOD_GetUpperCategory( eCategory );
						if ( IPOD_LIB_ALL == eCategory )  {
							TLOG(CH_CMDCTL, LV_WARN, 
										(TEXT("IPOD_GetUpperCategory > Invalid category(%d).\r\n"), eCategory));
						}
						else{
					//		eCMDErrorCode = IPOD_SelectSortList( piPodLibApiHandle, eCategory, zIndex, SORTBYARTIST );
							eCMDErrorCode = IPOD_SelectList(piPodLibApiHandle, eCategory, zIndex);

							if ( IS_CMDERROR(eCMDErrorCode) ){
								TLOG(CH_CMDCTL, LV_WARN, 
											(TEXT("IPOD_SelectSortList > Falied(%d).\r\n"), eCMDErrorCode));
							}
							else{
								eCMDErrorCode = IPOD_SelectListType( piPodLibApiHandle, eCategory, &nCount );
								if ( IS_CMDOK(eCMDErrorCode) ){
									IsSuccess = TRUE;
									ResponseMsg.wParam = eCategory;
									ResponseMsg.lParam = (DWORD)nCount;
									stCheckTimeGetNumCategorizedDBRecord = stCurrentTick;
								}
								else{
									TLOG(CH_CMDCTL, LV_WARN, 
												(TEXT("IPOD_SelectListType > Falied(%d).\r\n"), eCMDErrorCode));
								}
							}						
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_BRWS_MOVEUPPER > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_BRWS_RES_MOVEUPPER;
					ResponseMsg.lParam = ( IsSuccess ) ? ResponseMsg.lParam : 0xFFFFFFFF;

					break;

				case WM_CMDCTRL_BRWS_GETNAME:
					TLOG(CH_CMDCTL, LV_DEBUG,
								(TEXT("WM_CMDCTRL_BRWS_GETNAME, WPARAM=0x%x, LPARAM=0x%x\r\n"), RequestMsg.wParam, RequestMsg.lParam));
					if ( IPOD_CONTROL_STATE_INITIALIZED == iPodControlState ) {
						BRWSListReqInfo *pBrwsListReqInfo = NULL;
						pBrwsListReqInfo = (BRWSListReqInfo *)RequestMsg.wParam;
	
						if ( pBrwsListReqInfo && pBrwsListReqInfo->nCount ){
							//pBrwsListReqInfo->eCategory;
							if ( NULL == stBrwsGetNameResInfo.pBrwsDBRecord ){
								stBrwsGetNameResInfo.pBrwsDBRecord = (PIPOD_RECORD_TYPE)malloc( (pBrwsListReqInfo->nCount)*sizeof(IPOD_RECORD_TYPE) );
								nBrwsMaxCountRequested = pBrwsListReqInfo->nCount;
							}
							else {
								if ( nBrwsMaxCountRequested < (pBrwsListReqInfo->nCount) ){
									free(stBrwsGetNameResInfo.pBrwsDBRecord);
									stBrwsGetNameResInfo.pBrwsDBRecord = (PIPOD_RECORD_TYPE)malloc( (pBrwsListReqInfo->nCount)*sizeof(IPOD_RECORD_TYPE) );
									nBrwsMaxCountRequested = pBrwsListReqInfo->nCount;
								}
							}

							if ( stBrwsGetNameResInfo.pBrwsDBRecord ){
								stBrwsGetNameResInfo.eCategory = pBrwsListReqInfo->eCategory;
								stBrwsGetNameResInfo.nBrwsDBRecordNum = pBrwsListReqInfo->nCount;

								eCMDErrorCode = IPOD_AskFileName( piPodLibApiHandle, pBrwsListReqInfo->eCategory, pBrwsListReqInfo->zStartIndex, pBrwsListReqInfo->nCount,
														stBrwsGetNameResInfo.pBrwsDBRecord );
								if ( IS_CMDOK(eCMDErrorCode) ){
									IsSuccess = TRUE;
									ResponseMsg.wParam = (unsigned int)(&stBrwsGetNameResInfo);
								}
								else{
									TLOG(CH_CMDCTL, LV_WARN, 
												(TEXT("IPOD_AskFileName() > Failed(%d)\r\n"), eCMDErrorCode));
								}
							}
							else{
								TLOG(CH_CMDCTL, LV_WARN, 
											(TEXT("WM_CMDCTRL_BRWS_GETNAME > stBrwsGetNameResInfo.pBrwsDBRecord is NULL\r\n")));
							}
						}
					}
					else{
						TLOG(CH_CMDCTL, LV_WARN, 
									(TEXT("WM_CMDCTRL_BRWS_GETNAME > Invalid state or invalid message.\r\n")));
					}

					ResponseMsg.message = WM_CMDCTRL_BRWS_RES_GETNAME;

					break;
					
				case WM_CMDCTRL_EXT_FUNC1:
					USER_FUNC_func1(hWnd, piPodLibApiHandle);
					ResponseMsg.message = WM_CMDCTRL_RES_EXT_FUNC1;
					break;
					
				case WM_CMDCTRL_EXT_FUNC2:
					USER_FUNC_func2(hWnd, piPodLibApiHandle);
					ResponseMsg.message = WM_CMDCTRL_RES_EXT_FUNC2;
					break;
					
				case WM_CMDCTRL_EXT_FUNC3:
					USER_FUNC_func3(hWnd, piPodLibApiHandle, pAblumartData);
					ResponseMsg.message = WM_CMDCTRL_RES_EXT_FUNC3;
					break;

				case WM_CMDCTRL_EXT_FUNC4:
					USER_FUNC_func4(hWnd, piPodLibApiHandle);
					ResponseMsg.message = WM_CMDCTRL_RES_EXT_FUNC4;
					break;
					
				case WM_CMDCTRL_EXT_FUNC5:
					USER_FUNC_func5(hWnd, piPodLibApiHandle);
					ResponseMsg.message = WM_CMDCTRL_RES_EXT_FUNC5;
					break;
					
				default:
					IsSuccess = FALSE;
					break;
			}			

			#ifdef TIME_CHECK
			DWORD nPrierTick = nCurrentTick;
			CString str;

			//nCurrentTick = GetTickCount();
			g_nMSGResCheckTick = GetTickCount();
			//str.Format(_T("%s > s(%d), e(%d) => %d\r\n\r\n"), GetMessageName(RequestMsg.message), nPrierTick, nCurrentTick, (nCurrentTick-nPrierTick) );
			//str.Format(_T("%d\r\n\r\n"), nCurrentTick );
			TLOG(CH_CMDCTL, LV_TIME, (str ));
			#endif

			//PostMessage(ResponseMsg.hwnd, ResponseMsg.message, ResponseMsg.wParam, ResponseMsg.lParam);
			SendMessage(ResponseMsg.hwnd, ResponseMsg.message, ResponseMsg.wParam, ResponseMsg.lParam);

		}
		
	}


	
	if (hControlDevice ){
		CloseHandle(hControlDevice);
		hControlDevice=0;
	}
	if (hI2CDevice){
		CloseHandle(hI2CDevice);
		hI2CDevice=0;
	}

#if (_WIN32_WCE < 0x500)
	#error WinCE4 or earlier is not supported
#elif (_WIN32_WCE < 0x800)
	// hGXPDevice
#else
	if (hGXPDevice){
		CloseHandle(hGXPDevice);
		hGXPDevice=0;
	}
#endif

	TLOG(CH_CMDCTL, LV_LOG, (TEXT("- iPodCMDControlThread() > \r\n")));

	return 0;
}


HANDLE iPod_DisconnectionDetectThread( HANDLE hWnd, DWORD *pThreadID ) {
	BOOL fRet = FALSE;
	HANDLE hThread = NULL;
	DWORD ThreadID = 0;

	TLOG(CH_CMDCTL, LV_LOG, (TEXT("+ iPod_DisconnectionDetectThread() > \r\n")));

	if ( IS_NULL(hWnd) ){
		TLOG(CH_CMDCTL, LV_LOG, (TEXT("iPod_DisconnectionDetectThread() > Invalid parameter\r\n")));
		goto EXIT;
	}
	
	
	hThread=CreateThread(NULL,0,iPodDisconnectionDetectThread, hWnd,0, &ThreadID );
	if ( NULL!=hThread ){
		if ( pThreadID ) *pThreadID = ThreadID;
	}

EXIT:
	
	TLOG(CH_CMDCTL, LV_LOG, (TEXT("- iPod_DisconnectionDetectThread() > \r\n")));

	return hThread;
}

HANDLE iPod_StartCMDControlThread( HANDLE hWnd, DWORD *pThreadID ) {
	BOOL fRet = FALSE;
	HANDLE hThread = NULL;
	DWORD ThreadID = 0;

	TLOG(CH_CMDCTL, LV_LOG, (TEXT("+ iPod_StartCMDControlThread() > \r\n")));

	if ( IS_NULL(hWnd) ){
		TLOG(CH_CMDCTL, LV_LOG, (TEXT("iPod_StartCMDControlThread() > Invalid parameter\r\n")));
		goto EXIT;
	}
	
	
	hThread=CreateThread(NULL,0,iPodCMDControlThread, hWnd,0, &ThreadID );
	if ( NULL!=hThread ){
		if ( pThreadID ) *pThreadID = ThreadID;
	}

EXIT:
	
	TLOG(CH_CMDCTL, LV_LOG, (TEXT("- iPod_StartCMDControlThread() > \r\n")));

	return hThread;
}

BOOL iPod_StopDisconnectionDetectThread( HANDLE hThread, DWORD ThreadID ) {
	BOOL fRet = FALSE;
	
	TLOG(CH_CMDCTL, LV_LOG, (TEXT("+ iPod_StopDisconnectionDetectThread() > \r\n")));

	if ( hThread && ThreadID ){
		DWORD ExitCode = 0;

		PostThreadMessage( ThreadID, WM_DISCNTDETECT_TERMINATE, 0, 0);

		Sleep(100); // ?

		if ( GetExitCodeThread( hThread, &ExitCode ) ){
			ExitThread( ExitCode );

			fRet = TRUE;
		}
		else{
			TLOG(CH_CMDCTL, LV_ERROR, (TEXT("iPod_StopDisconnectionDetectThread() > %d \r\n"), GetLastError()));
		}
		//TerminateThread(hThread,0);

		CloseHandle( hThread );
		hThread = NULL;

	}

	TLOG(CH_CMDCTL, LV_LOG, (TEXT("- iPod_StopDisconnectionDetectThread() > \r\n")));

	return fRet;
}

BOOL iPod_StopCMDControlThread( HANDLE hThread, DWORD ThreadID ) {
	BOOL fRet = FALSE;
	
	TLOG(CH_CMDCTL, LV_LOG, (TEXT("+ iPod_StopCMDControlThread() > \r\n")));

	if ( hThread && ThreadID ){
		DWORD ExitCode = 0;

		PostThreadMessage( ThreadID, WM_CMDCTRL_TERMINATE, 0, 0);

		Sleep(500); // ?

		if ( GetExitCodeThread( hThread, &ExitCode ) ){
			ExitThread( ExitCode );

			fRet = TRUE;
		}
		else{
			TLOG(CH_CMDCTL, LV_ERROR, (TEXT("iPod_StopCMDControlThread() > %d \r\n"), GetLastError()));
		}
		//TerminateThread(hThread,0);

		CloseHandle( hThread );
		hThread = NULL;

	}

	TLOG(CH_CMDCTL, LV_LOG, (TEXT("- iPod_StopCMDControlThread() > \r\n")));

	return fRet;
}

DWORD iPod_GetControlDeviceDriverNumber( DWORD UniqueID ){

	/* Device attached message */
	HKEY hClientRegKey = NULL;
	DWORD dwType = 0;
	//DWORD dwLength = sizeof(DWORD);
	DWORD dwLength = 32;
	WCHAR DataBuffer[32] = {0,};
	DWORD DeviceNumber = 0;

	wchar_t RegPath[80] = {0, };

	//iPod
	wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\05AC\\%08x\\TCCHIDClient"),  UniqueID );

	//TC
	//wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\140E\\%08x\\TCCHIDClient"),  UniqueID );

	TLOG(CH_CMDCTL, LV_DEBUG,
				(TEXT("+ GetControlDeviceDriverNumber() > RegPath(%s)\r\n"), RegPath));

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, RegPath, 0, 0, &hClientRegKey) == ERROR_SUCCESS ) { // We found Registry 
		DWORD err = RegQueryValueEx( hClientRegKey,DRIVERSTRING_SZ, NULL,&dwType, (LPBYTE)&DataBuffer[0], &dwLength);
		if ( err == ERROR_SUCCESS ){
			if ( REG_SZ == dwType){
				TLOG(CH_CMDCTL, LV_DEBUG,
							(TEXT("GetControlDeviceDriverNumber() > Data Buffer(%s)\r\n"), &DataBuffer[0]));
				if ( ('T' == DataBuffer[0]) && ('H' == DataBuffer[1]) && ('C' == DataBuffer[2]) ){
					DeviceNumber = DataBuffer[3] - '0';

					if ( 0 < DeviceNumber ) {
						DWORD nOpenCount;
						LONG ret = RegQueryValueEx(hClientRegKey, DRIVEROPENCOUNT_SZ, NULL, &dwType, (LPBYTE)&nOpenCount, &dwLength);
						if ( (ERROR_SUCCESS == ret) && dwLength && (dwType == REG_DWORD)  ){
							if ( 0 != nOpenCount ){
								DeviceNumber = 0;
							}
						}
					}
				}
			}
			else{
				TLOG(CH_CMDCTL, LV_DEBUG, 
							(TEXT("GetControlDeviceDriverNumber() > Invalid data type(%d)\r\n"), dwType));
			}			
		}
		else{
			TLOG(CH_CMDCTL, LV_DEBUG,
						(TEXT("GetControlDeviceDriverNumber() > Failed to open registry key(%s), ErrorCode=%d\r\n"), DRIVERSTRING_SZ, err ));
		}

		RegCloseKey( hClientRegKey );
	}
	else{
		TLOG(CH_CMDCTL, LV_DEBUG,
					(TEXT("GetControlDeviceDriverNumber() > Failed to open registry path(%s)\r\n"), RegPath));
	}

	TLOG(CH_CMDCTL, LV_DEBUG,
				(TEXT("- GetControlDeviceDriverNumber() > DeviceNumber=%d\r\n"), DeviceNumber));
			
	return DeviceNumber;
}

DWORD iPod_getUniqueIDfromString(WCHAR *Str)
{
	unsigned char ansi;
	unsigned int i;
	DWORD UniqueID = NULL, Temp;

	for(i=0; i<8; i++)	
	{
		ansi = (unsigned char)(Str[i]);

		if(('A' <= ansi )&&(ansi <= 'F'))
		{
			ansi = ansi - (unsigned char)'A' + (unsigned char)10;
		}
		else if(('a' <= ansi)&&(ansi <='a'))
		{
			ansi = ansi - (unsigned char)'A' + (unsigned char)10;
		}
		else if(('0'<=ansi)&&(ansi <= '9'))
		{
			ansi = ansi - (unsigned char)'0';
		}
		else
		{
			ansi = 0;
		}

		Temp = (DWORD)(ansi);
		UniqueID |= (Temp & 0x000000FF)<<(4*(7-i));
	
	}

	return UniqueID;
}


//DWORD iPod_RetrieveControlDeviceDriverNumber( void ){
BOOL iPod_RetrieveControlDeviceDriverNumber( DWORD *pDevcieDriverNumber, DWORD *pUniqueID )
{

	/* Device attached message */
	HKEY hClientRegKey = NULL;
	DWORD dwType = 0;
	//DWORD dwLength = sizeof(DWORD);
	DWORD dwLength = 32;
	unsigned char DataBuffer[32] = {0,};
	DWORD DeviceNumber = 0;

	wchar_t RegPath[80] = {0, };

	WCHAR szUniqueId[256];
	DWORD nUniqueIDLen = sizeof(szUniqueId);

	DWORD nQueryMax = 256;
	DWORD nQueryCnt = 0;
	BOOL ret = FALSE;


	if ( (NULL==pDevcieDriverNumber) || (NULL== pUniqueID) )
	{
		// ERROR
	}
	else
	{
		//iPod
		wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\05AC"));

		//TC
		//wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\140E"));

		TLOG(CH_CMDCTL, LV_DEBUG,
					(TEXT("+ iPod_RetrieveControlDeviceDriverNumber() > RegPath(%s)\r\n"), RegPath));

		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, RegPath, 0, 0, &hClientRegKey) == ERROR_SUCCESS ) 
		{ // We found Registry 

			for(nQueryCnt=0; nQueryCnt<nQueryMax; nQueryCnt++)
			{
				if(RegEnumKeyEx(hClientRegKey, nQueryCnt, szUniqueId, &nUniqueIDLen, NULL,
				        NULL, NULL, NULL) == ERROR_SUCCESS)
				{
				        
					HKEY hUniqueID;
					if(RegOpenKeyEx(hClientRegKey, szUniqueId, 0, 0, &hUniqueID) == ERROR_SUCCESS)
					{ //"RegPath\\Unique"
						HKEY hDriver;
						if(RegOpenKeyEx(hUniqueID, L"TCCHIDClient", 0, 0, &hDriver) == ERROR_SUCCESS)
						{ //"RegPath\\Unique\\TCCHIDClient"

							WCHAR DataBuffer[256];
							DWORD dwLength = sizeof(DataBuffer);
							DWORD dwType;

							TLOG(CH_CMDCTL, LV_DEBUG,
									(TEXT(" > TCCHIDClient path foud\r\n")));

							RegQueryValueEx(hDriver, DRIVERSTRING_SZ, NULL, &dwType,
												(LPBYTE)DataBuffer, &dwLength);

							if(dwLength && dwType == REG_SZ)
							{
								if ( ('T' == DataBuffer[0]) && ('H' == DataBuffer[1]) && ('C' == DataBuffer[2]) )
								{
									DeviceNumber = DataBuffer[3] - '0';
	 
									if ( 0 < DeviceNumber ) 
									{
										DWORD nOpenCount;
										LONG ret = RegQueryValueEx(hDriver, DRIVEROPENCOUNT_SZ, NULL, &dwType, (LPBYTE)&nOpenCount, &dwLength);
										if ( (ERROR_SUCCESS == ret) && dwLength && (dwType == REG_DWORD))
										{
											if (  0 !=nOpenCount )
											{
												DeviceNumber = 0;
												RegCloseKey(hDriver);
												RegCloseKey(hUniqueID);
												continue;
											}
										}
									}

									RegCloseKey(hDriver);
									RegCloseKey(hUniqueID);
									*pDevcieDriverNumber = DeviceNumber;
									*pUniqueID = iPod_getUniqueIDfromString(szUniqueId);

									
									ret = TRUE;
									break;
								}

							}

							RegCloseKey(hDriver);
						}

						RegCloseKey(hUniqueID);
					}
				}

			}

			RegCloseKey(hClientRegKey);
		}
		else
		{
			TLOG(CH_CMDCTL, LV_DEBUG,
						(TEXT("> RegOpenKeyEx(%s) failed \r\n"),RegPath));
		}

		TLOG(CH_CMDCTL, LV_DEBUG,
					(TEXT("- iPod_RetrieveControlDeviceDriverNumber() > DeviceNumber=(%d)\r\n"), DeviceNumber));

		ret = TRUE;
		
	}

	return ret;
//	return DeviceNumber;
}


