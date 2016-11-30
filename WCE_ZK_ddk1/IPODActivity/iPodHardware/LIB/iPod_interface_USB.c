/**************************************************************************			
***                                                                          
***   Telechips SYS1-1 Team                          
***                                                                          
***   Module : iPod_interface_USB.C          
***                                                              
**************************************************************************/
/*Nuclues Version */
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X) || defined(TCC80XX)
#include "main.h"
#include "TC_Kernel.h"
#include "disk.h"
#include "USBHOST/USBHost_header.h"
#include "kernel/telechips.h"
#include "fs/utils.h"
#include "IPOD/iPod_error.h"
#include "IPOD/CP_to_I2C.h"
#endif
#include <Windows.h>


#ifdef IPOD_USB_INCLUDE

#include "./IPOD_API.h"


#if defined(TCC860x) || defined(TCC78X)
#include "lib86x.h"
#endif

#ifdef TCC83XX
#include "IO_TCC7XX.h"
#endif

static unsigned char strIPODProtocolString[] = "com.telechips.externalaccessoryapptest001\0";


/*Nuclues Version */
#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X) || defined(TCC80XX)
static IPOD_ERROR IPOD_API_USB_InitChannelParam(pIPOD_INIT_CHANNRL_PARAM pParam, unsigned long DiskInfo, unsigned int DevNo);
static IPOD_ERROR IPOD_API_USB_InitParam(void *iPod_Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData);
static IPOD_ERROR IPOD_API_USB_InitParamRDisplay(void *iPod_Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData);

/**************************************************************************
	Function : IPOD_API_USB_InitChannelParam

 	Description : It initialize the iPod channels.
				
	Parameter : 
		pParam : iPod channel param
		DiskInfo : DISK_DEVICE type
		DevNo : device number of USBHost

  	Return : IPOD_ERROR
		
**************************************************************************/
static IPOD_ERROR IPOD_API_USB_InitChannelParam(pIPOD_INIT_CHANNRL_PARAM pParam, unsigned long DiskInfo, unsigned int DevNo)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;
	
	mem_set(pParam, 0x00, sizeof(IPOD_INIT_CHANNRL_PARAM));
	
	pParam->ConnectionType = IPOD_USB_CONNECT;
	
	pParam->ExtInfo = IPOD_Malloc_iPodBuf(&pParam->buff);
	if(0 != pParam->ExtInfo)
	{
		pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)pParam->ExtInfo;
		pInfo->Disk = DiskInfo;
		pInfo->Basic_Info.DevNo = DevNo;
		IPOD_API_InitArtworkInfo(pInfo);
		pInfo->Basic_Info.ipod_state = IPOD_PLUGED;
		
	}
	else
	{
		iPod_err = IPOD_MALLOC_ERROR;
	}

	return iPod_err;
}


/**************************************************************************
	Function : IPOD_API_USB_InitParam

 	Description : It initialize the iPod init parameter. ( Extended Lingo )
				
	Parameter : 
		Handle : iPod handle
		pParam : init param for iPod 

  	Return : MOUNT_FAIL, MOUNT_SUCCESS
		
**************************************************************************/
static IPOD_ERROR IPOD_API_USB_InitParam(void *iPod_Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;
	
	// For Digital audio output -> 1wire
	mem_set(pParam, 0x00, sizeof(IPOD_INIT_PARAM));


	#ifdef IPOD_CHECK_OPTION
	if(IPOD_API_Check_Storage_tagging_support(pLingo_InfoData) > 0)
	{
	//	SerialPrintf("******** It support storage Lingo tagging *******");
	}
	else
	{
	//	SerialPrintf("******** It does not support storage Lingo tagging *******");
	}
	#endif
	
#if 1	
	pParam->IdentifyToken.LingoCnt = 5;
	pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
	pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
	pParam->IdentifyToken.Lingos[2] = LINGO_DIGITAL_AUDIO;
	pParam->IdentifyToken.Lingos[3] = LINGO_DISPLAY_REMOTE;
	pParam->IdentifyToken.Lingos[4] = LINGO_SIMPLE_REMOTE;
	

#else
	pParam->IdentifyToken.LingoCnt = 2;
	pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
	pParam->IdentifyToken.Lingos[1] = LINGO_SIMPLE_REMOTE;

#endif

#ifdef IPOD_USB_POWER_MAX_1A
	pParam->IdentifyToken.DeviceOption = (CONSTANT_HIGH_POWER | AUTHENTICATION_IMMEDIATELY);
#else
	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);
#endif

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;
	
	pParam->pAccInfoToken = &gIPOD_AccInfo;


#if 1 /* Digital audio support */
	pParam->AccesoryCapToken = (AC_USB_DIGITAL_AUDIO);
	pParam->AccPrefToken.Total_PreferenceCnt = 0;

#else /* Analog Video output support */
	pParam->AccesoryCapToken = (AC_USB_DIGITAL_AUDIO|AC_ANALOG_VIDEO_OUT);

	pParam->AccPrefToken.Total_PreferenceCnt = 1;
	pParam->AccPrefToken.Pref[0].ClassID = 0;
	pParam->AccPrefToken.Pref[0].SettingID = 1;
	pParam->AccPrefToken.Pref[0].RestoreOnExit = 0;
#endif	

	return iPod_err;
	
}

/**************************************************************************
	Function : IPOD_API_USB_InitParamRDisplay

 	Description : It initialize the iPod init parameter. ( Display remote Lingo )
				
	Parameter : 
		Handle : iPod handle
		pParam : init param for iPod 

  	Return : MOUNT_FAIL, MOUNT_SUCCESS
		
**************************************************************************/
static IPOD_ERROR IPOD_API_USB_InitParamRDisplay(void *iPod_Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;

	mem_set(pParam, 0x00, sizeof(IPOD_INIT_PARAM));

	if(IPOD_API_Check_Storage_tagging_support(pLingo_InfoData) > 0)
	{
	//	SerialPrintf("******** It support storage Lingo tagging *******");
	}
	else
	{
	//	SerialPrintf("******** It does not support storage Lingo tagging *******");
	}
	
	
	pParam->IdentifyToken.LingoCnt = 3;
	pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
	pParam->IdentifyToken.Lingos[1] = LINGO_DISPLAY_REMOTE;
	pParam->IdentifyToken.Lingos[2] = LINGO_SIMPLE_REMOTE;


	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;
	
	pParam->pAccInfoToken = &gIPOD_AccInfo;

	pParam->AccesoryCapToken = (AC_ANALOG_LINE_OUT);
	pParam->AccPrefToken.Total_PreferenceCnt = 0;

	return iPod_err;
	
}

/**************************************************************************
	Function : IPOD_API_USB_InitParamOSApp

 	Description : It initialize the iPod init parameter. ( communication with OS application )
				
	Parameter : 
		Handle : iPod handle
		pParam : init param for iPod 
		diskInfo : DISK TYPE
		DevNo : Device Number for USBhost

  	Return : none
		
**************************************************************************/
static void IPOD_API_USB_InitParamOSApp(void *iPod_Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData)
{
	memset(pParam, 0x00, sizeof(IPOD_INIT_PARAM));

	if(IPOD_API_Check_Storage_tagging_support(pLingo_InfoData) > 0)
	{
	//	SerialPrintf("******** It support storage Lingo tagging *******");
	}
	else
	{
	//	SerialPrintf("******** It does not support storage Lingo tagging *******");
	}
	
	pParam->IdentifyToken.LingoCnt = 3;
	pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
	pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
	pParam->IdentifyToken.Lingos[2] = LINGO_DIGITAL_AUDIO;


	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;
	
	pParam->pAccInfoToken = &gIPOD_AccInfo;

	pParam->AccesoryCapToken = (AC_SUPPORT_IPHONE_OS_APP|AC_USB_DIGITAL_AUDIO);
	pParam->AccPrefToken.Total_PreferenceCnt = 0;

	// For SDKProtocolToken
	pParam->m_SDKProtocolToken.Total_ProtocolCnt = 1;
	pParam->m_SDKProtocolToken.m_protocolTokenData[0].m_protocolIndex = 1;
	pParam->m_SDKProtocolToken.m_protocolTokenData[0].m_ProtocolStringSize= 42;
	pParam->m_SDKProtocolToken.m_protocolTokenData[0].m_pProtocolString = &strIPODProtocolString[0];
	

	// For BundleSeedIDPreToken
	pParam->m_BundleSeedIDPrefToken.m_BundleSeedIDIsExist = 1;
	memset( &(pParam->m_BundleSeedIDPrefToken.m_BundleSeedIDString[0]), 0x00, IPOD_BUNDLE_SEEDID_STRING_SIZE ); 
	memcpy( &(pParam->m_BundleSeedIDPrefToken.m_BundleSeedIDString[0]), "AZ3V4GJQCV", sizeof("AZ3V4GJQCV") );

	
}


/**************************************************************************
	Function : IPOD_API_USB_MountDev

 	Description : Mount the IPOD.
				
	Parameter : none

  	Return : MOUNT_FAIL, MOUNT_SUCCESS
		
**************************************************************************/
int IPOD_API_USB_MountDev(void)
{
	int ret = MOUNT_FAIL;
	IPOD_INIT_PARAM init_param;
	IPOD_INIT_CHANNRL_PARAM ChannelPrarm;
	IPOD_LINGO_INFO_DATA LingoInfoData;
	
	unsigned long iPod_Handle=0x00U;
	IPOD_ERROR err;
	int DevNo = USBH_API_HUB_GetCurrentDiskNum();
	void *Handle_Check; // = DISK_GetHandle(DISK_DEVICE_IPOD);
	IPOD_STATE State;
	IPOD_INIT_TYPE InitType;
	unsigned int InitRetry;
	unsigned int CheckOption=1;

	Handle_Check = IPOD_GetHandle_fromDevNo(DevNo);
	
      
	UI_API_DrawPopUp2Line_withoutTimeout("IPOD Init!", "Start" );

	State = IPOD_API_GetStatus(Handle_Check);
	if(IPOD_PLUGED == State)
	{
		err = IPOD_Open(&iPod_Handle);

		if(IPOD_NO_ERROR == err)
		{
			err = IPOD_API_USB_InitChannelParam(&ChannelPrarm, DISK_DEVICE_IPOD, (unsigned int)DevNo);
			if(IPOD_NO_ERROR == err)
			{
				for(InitRetry = 0; InitRetry < 3; InitRetry++)
				{
					if(IPOD_IDPS_TIMEOUT == err)
					{
						CheckOption = 0;
					}
					err = IPOD_InitChannel((void *)iPod_Handle, &ChannelPrarm);
					if(IPOD_NO_ERROR == err)
					{
						if(CheckOption)
						{
							IPOD_API_CheckiPodOption((void *)iPod_Handle, &LingoInfoData);
						}
						//IPOD_API_USB_InitParamOSApp((void *)iPod_Handle, &init_param, &LingoInfoData);
						//IPOD_API_USB_InitParamRDisplay((void *)iPod_Handle, &init_param, &LingoInfoData);
						IPOD_API_USB_InitParam((void *)iPod_Handle, &init_param, &LingoInfoData);
						err = IPOD_Init((void *)iPod_Handle, &init_param);
						if(IPOD_NO_ERROR == err)
						{
							DISK_SetHandle(DISK_DEVICE_IPOD, (void *)iPod_Handle);
							IPOD_Display_Init((void *)iPod_Handle, 0);
							ret = MOUNT_SUCCESS;
							break;
						}
					}

					if((IPOD_COMMAND_TIMEOUT == err) ||(IPOD_COMMAND_FAILED == err) 
						||(IPOD_IO_CP_ERROR == err) || (IPOD_IDPS_TIMEOUT == err) ||(IPOD_RETRY_IDPS == err))
					{
						continue;
					}
					else
					{
						break;
					}

				}
			}
			if(IPOD_NO_ERROR != err)
			{
				IPOD_Free_AudioPlayInfo((void *)iPod_Handle);
				IPOD_Close((void *)iPod_Handle);
				DISK_SetState(DISK_DEVICE_IPOD, DISK_STATE_MOUNTERR);
			}
		}
	}
	else  if(IPOD_INITIALIZED == State) 
	{
		/* IPOD already inited by USB host ( not filesystem)*/
		iPod_Handle = (unsigned long)Handle_Check;
		DISK_SetHandle(DISK_DEVICE_IPOD, (void *)iPod_Handle);
		ret = MOUNT_SUCCESS;
	}
	else
	{
		/* Do nothting */
		;
	}


	if (ret == MOUNT_SUCCESS)
	{
		err = IPOD_GetInitType((void *)iPod_Handle, &InitType);
		if(IPOD_NO_ERROR == err)
		{
			if(IPOD_DIGITAL_AUDIO == InitType)
			{
			#ifdef IPOD_RENEW_TEST
				/* This must be moved to Audio Task */
				/* Please refer to Media_Mount_InitMode in MAIN.c */
				#ifdef IPOD_AUDIO_BANDWIDTH_DYNAMIC_SETTING
				#else
				(void)USB_AUDIO_Set_FullBandwidthInterface(); /* Just enable Audio Class Isochronous Stream */
				#endif
			#else /* IPOD_RENEW_TEST */
				Open_USBAudioTrack();  // 1 wire 
			#endif /* IPOD_RENEW_TEST */
			}
		}


		DISK_SetState (DISK_DEVICE_IPOD, DISK_STATE_MOUNTSUCCEED);
		DISK_SetDiskPartitionIndex(DISK_DEVICE_IPOD, IPOD_DEVICE_PARTID);
		
		IPOD_SetAccess((void *)NULL, SET);
		IPOD_API_SetStatus(iPod_Handle, IPOD_INITIALIZED);
		IPOD_Check_iPod_status((void *)iPod_Handle);
	}
	return ret;
}
#endif /*#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X) || defined(TCC80XX)*/


#ifdef WINCE
/**************************************************************************
	Function : IPOD_API_WINCE_USB_InitChannelParam

 	Description : It initialize the iPod channels.
				
	Parameter : 
		pParam : iPod channel param
		Hid_Handle : HID handle
		I2C_Handle : I2C handle
		EventThreadID : Event thread ID
		I2C_ChannelNum : I2C Channel Number

  	Return : IPOD_ERROR
		
**************************************************************************/
IPOD_ERROR IPOD_API_WINCE_USB_InitChannelParam(pIPOD_INIT_CHANNRL_PARAM pParam, void *Hid_Handle,void *I2C_Handle, unsigned long EventThreadID, unsigned long I2C_ChannelNum)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;
	pIPOD_PLAY_INFO pInfo;
		
	pInfo = (pIPOD_PLAY_INFO)IPOD_GetExtInfo(pParam->iPod_Handle);
	//memset(pParam, 0x00, sizeof(IPOD_INIT_CHANNRL_PARAM));
	
	pParam->DevHandleDes.HID = Hid_Handle;
	pParam->DevHandleDes.I2C = I2C_Handle;
	pParam->DevHandleDes.I2C_channelNum = I2C_ChannelNum;
	pParam->DevHandleDes.I2C_SlaveAddr = IAP_CP_slaveaddr; 
	pParam->EventThreadID = EventThreadID;

	pParam->ConnectionType = IPOD_USB_CONNECT;
	//IPOD_Malloc_iPodBuf(&pParam->buff); //move to iPodDlg
	pParam->ExtInfo = pInfo;
	if(0 != pParam->ExtInfo)
	{
		IPOD_InitBuff(&pParam->buff, pInfo->pBuffer);
		pInfo = (pIPOD_PLAY_INFO)pParam->ExtInfo;
//		pInfo->Disk = DiskInfo;
//		pInfo->Basic_Info.DevNo = DevNo;
		IPOD_API_InitArtworkInfo(pInfo);
		pInfo->Basic_Info.ipod_state = IPOD_PLUGED;
		
	}
	else
	{
		RETAILMSG(1, (TEXT("NO ipod info\r\n")));
		iPod_err = IPOD_MALLOC_ERROR;
	}

	return iPod_err;

}

/**************************************************************************
	Function : IPOD_API_WINCE_USB_InitParam

 	Description : It initialize the iPod init parameter. ( Extended Lingo )
				
	Parameter : 
		Handle : iPod handle
		pParam : init param for iPod 
		connectionType : connection type (UART or USB)

  	Return : MOUNT_FAIL, MOUNT_SUCCESS
		
**************************************************************************/
IPOD_ERROR IPOD_API_WINCE_USB_InitParam(void *Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData, IAP_CONNECTION_MODE connectionType)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;
    int i;
	// For Digital audio output -> 1wire
	memset(pParam, 0x00, sizeof(IPOD_INIT_PARAM));


	if(ONE_WIRE_CONNECTION == connectionType)
	{
		pParam->IdentifyToken.LingoCnt = 4;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
		pParam->IdentifyToken.Lingos[2] = LINGO_DIGITAL_AUDIO;
		pParam->IdentifyToken.Lingos[3] = LINGO_DISPLAY_REMOTE;

	}
	else
	{
		pParam->IdentifyToken.LingoCnt = 3;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
		pParam->IdentifyToken.Lingos[2] = LINGO_DISPLAY_REMOTE;
	}

#ifdef IPOD_USB_POWER_MAX_1A
	pParam->IdentifyToken.DeviceOption = (CONSTANT_HIGH_POWER | AUTHENTICATION_IMMEDIATELY);
#else
	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);
#endif

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->pAccInfoToken = &gIPOD_AccInfo;
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;


#if 0 /* Digital audio support */

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
	pParam->AccPrefToken.Pref[0].m_ClassID = 0;
	pParam->AccPrefToken.Pref[0].m_SettingID = 1;
	pParam->AccPrefToken.Pref[0].m_RestoreOnExit = 0;

	pParam->AccesoryCapToken = (AC_USB_DIGITAL_AUDIO|AC_ANALOG_VIDEO_OUT|AC_CHECK_IPOD_VOLUME);
	pParam->AccPrefToken.Total_PreferenceCnt = 5;
	for(i = 0; i < pParam->AccPrefToken.Total_PreferenceCnt; i++)
	{
		pParam->AccPrefToken.Pref[i].m_ClassID = gIPOD_Pref[i].m_ClassID;
		pParam->AccPrefToken.Pref[i].m_SettingID= gIPOD_Pref[i].m_SettingID;
		pParam->AccPrefToken.Pref[i].m_RestoreOnExit= gIPOD_Pref[i].m_RestoreOnExit;
	}
	
#endif	
	


	return iPod_err;

}

/**************************************************************************
	Function : IPOD_API_WINCE_USB_InitParamRDisplay

 	Description : It initialize the iPod init parameter. ( Display remote Lingo )
				
	Parameter : 
		Handle : iPod handle
		pParam : init param for iPod 
		connectionType : connection type (UART or USB)

  	Return : MOUNT_FAIL, MOUNT_SUCCESS
		
**************************************************************************/
IPOD_ERROR IPOD_API_WINCE_USB_InitParamRDisplay(void *Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData, IAP_CONNECTION_MODE connectionType)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;

	memset(pParam, 0x00, sizeof(IPOD_INIT_PARAM));

	if(ONE_WIRE_CONNECTION == connectionType)
	{
		pParam->IdentifyToken.LingoCnt = 4;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
		pParam->IdentifyToken.Lingos[2] = LINGO_DIGITAL_AUDIO;
		pParam->IdentifyToken.Lingos[3] = LINGO_DISPLAY_REMOTE;

	}
	else
	{
		pParam->IdentifyToken.LingoCnt = 3;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
		pParam->IdentifyToken.Lingos[2] = LINGO_DISPLAY_REMOTE;
	}


#ifdef IPOD_USB_POWER_MAX_1A
	pParam->IdentifyToken.DeviceOption = (CONSTANT_HIGH_POWER | AUTHENTICATION_IMMEDIATELY);
#else
	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);
#endif

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->pAccInfoToken = &gIPOD_AccInfo;
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;



	if(ONE_WIRE_CONNECTION == connectionType)
	{
		pParam->AccesoryCapToken = (AC_SUPPORT_IPHONE_OS_APP|AC_USB_DIGITAL_AUDIO);
	}
	else
	{
		pParam->AccesoryCapToken = (AC_SUPPORT_IPHONE_OS_APP|AC_ANALOG_LINE_OUT);
	}
	pParam->AccPrefToken.Total_PreferenceCnt = 0;
	
	return iPod_err;
}

/**************************************************************************
	Function : IPOD_API_WINCE_USB_InitParamRDisplay

 	Description : It initialize the iPod init parameter. ( Display remote Lingo )
				
	Parameter : 
		Handle : iPod handle
		pParam : init param for iPod 
		connectionType : connection type (UART or USB)

  	Return : MOUNT_FAIL, MOUNT_SUCCESS
		
**************************************************************************/
IPOD_ERROR IPOD_API_WINCE_USB_InitParamOSApp(void *Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData, IAP_CONNECTION_MODE connectionType)
{
	memset(pParam, 0x00, sizeof(IPOD_INIT_PARAM));

	if(IPOD_API_Check_Storage_tagging_support(pLingo_InfoData) > 0)
	{
	//	SerialPrintf("******** It support storage Lingo tagging *******");
	}
	else
	{
	//	SerialPrintf("******** It does not support storage Lingo tagging *******");
	}
	
	if(ONE_WIRE_CONNECTION == connectionType)
	{
		pParam->IdentifyToken.LingoCnt = 4;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
		pParam->IdentifyToken.Lingos[2] = LINGO_DIGITAL_AUDIO;
		pParam->IdentifyToken.Lingos[3] = LINGO_DISPLAY_REMOTE;

	}
	else
	{
		pParam->IdentifyToken.LingoCnt = 3;
		pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
		pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
		pParam->IdentifyToken.Lingos[2] = LINGO_DISPLAY_REMOTE;
	}


	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;
	
	pParam->pAccInfoToken = &gIPOD_AccInfo;


	if(ONE_WIRE_CONNECTION == connectionType)
	{
		pParam->AccesoryCapToken = (AC_SUPPORT_IPHONE_OS_APP|AC_USB_DIGITAL_AUDIO);
	}
	else
	{
		pParam->AccesoryCapToken = (AC_SUPPORT_IPHONE_OS_APP|AC_ANALOG_LINE_OUT);
	}
	
	pParam->AccPrefToken.Total_PreferenceCnt = 0;

	// For SDKProtocolToken
	pParam->m_SDKProtocolToken.Total_ProtocolCnt = 1;
	pParam->m_SDKProtocolToken.m_protocolTokenData[0].m_protocolIndex = 1;
	pParam->m_SDKProtocolToken.m_protocolTokenData[0].m_ProtocolStringSize= 42;
	pParam->m_SDKProtocolToken.m_protocolTokenData[0].m_pProtocolString = &strIPODProtocolString[0];
	

	// For BundleSeedIDPreToken
	pParam->m_BundleSeedIDPrefToken.m_BundleSeedIDIsExist = 1;
	memset( &(pParam->m_BundleSeedIDPrefToken.m_BundleSeedIDString[0]), 0x00, IPOD_BUNDLE_SEEDID_STRING_SIZE ); 
	memcpy( &(pParam->m_BundleSeedIDPrefToken.m_BundleSeedIDString[0]), "AZ3V4GJQCV", sizeof("AZ3V4GJQCV") );

}


#endif /*WINCE*/


#endif /*IPOD_USB_INCLUDE*/
