/**************************************************************************			
***                                                                          
***   Telechips SYS1-1 Team                          
***                                                                          
***   Module : iPod_interface_UART.C          
***                                                              
**************************************************************************/


#ifdef IPOD_UART_INCLUDE
#include "include/main.h"
#include "Resource/TC_Kernel.h"
#include "FS/disk.h"
#include "FileBuffer/FileBufferCtrl.h"

#if defined(TCC860x) || defined(TCC83XX) || defined(TCC78X)
#include "lib86x.h"
//#include "TCC86x.h"
#endif

#ifdef TCC80XX
#include "IO_LIB/include/IO_TCC7XX.h"
#include "include/common_array.h"
#include "DDI/DDIManager/DDI_DeviceID.h"
#include "DDI/DDIManager/DDI_manager.h"
#include "DDI/DDI_UART/DDI_UART.h"
#include "USBHost/USBHost_header.h"
#endif

#include "kernel/telechips.h"
#include "fs/utils.h"

#include "ipod_error.h"
#include "IPOD/IPOD_API.h"

//#include "IPOD/CP_API.h"
#include "IPOD/CP_to_I2C.h"

int IPOD_UFDStatusFlag = 0;

#define IPOD_UART_CP_USE

static IPOD_ERROR IPOD_API_UART_InitChannelParam(pIPOD_INIT_CHANNRL_PARAM pParam, unsigned long DiskInfo)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;
	
	memset(pParam, 0x00, sizeof(IPOD_INIT_CHANNRL_PARAM));
	
	pParam->ConnectionType = IPOD_UART_CONNECT;

#ifdef IPOD_UART_CP_USE
	pParam->IDPS_support = IPOD_IDPS_SUPPORT;
#else
	pParam->IDPS_support = IPOD_IDPS_NOT_SUPPORT;
#endif

	pParam->ExtInfo = IPOD_Malloc_iPodBuf(&pParam->buff);
	if(pParam->ExtInfo)
	{
		pIPOD_PLAY_INFO pInfo = (pIPOD_PLAY_INFO)pParam->ExtInfo;
		pInfo->Disk = DiskInfo;
		IPOD_API_InitArtworkInfo(pInfo);
		pInfo->Basic_Info.ipod_state = IPOD_PLUGED;
	}
	else
	{
		iPod_err = IPOD_MALLOC_ERROR;
	}
	
	IPOD_SetDefaultSupportLingoIDs(ML_GENERAL|ML_REMOTE_UI_EXTENDED);

	return iPod_err;
}

/**************************************************************************
	Function : IPOD_API_UART_InitParamOSApp

 	Description : It initialize the iPod init parameter. ( communication with OS application )
				
	Parameter : 
		Handle : iPod handle
		pParam : init param for iPod 
		pLingo_InfoData : lingo data

  	Return : none
		
**************************************************************************/
static unsigned char strIPODProtocolString[] = "com.telechips.externalaccessoryapptest001\0";
static IPOD_ERROR IPOD_API_UART_InitParamOSApp(pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;
	memset(pParam, 0x00, sizeof(IPOD_INIT_PARAM));

	if(IPOD_API_Check_Storage_tagging_support(pLingo_InfoData) > 0)
	{
	//	SerialPrintf("******** It support storage Lingo tagging *******");
	}
	else
	{
	//	SerialPrintf("******** It does not support storage Lingo tagging *******");
	}
	
	pParam->IdentifyToken.LingoCnt = 4;
	pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
	pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
	pParam->IdentifyToken.Lingos[2] = LINGO_DISPLAY_REMOTE;
	pParam->IdentifyToken.Lingos[3] = LINGO_SIMPLE_REMOTE;

	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;
	
	pParam->pAccInfoToken = &gIPOD_AccInfo;

	pParam->AccesoryCapToken = (AC_SUPPORT_IPHONE_OS_APP|AC_ANALOG_LINE_OUT);
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

	return iPod_err;	
}

/**************************************************************************
	Function : IPOD_API_UART_InitParam

 	Description : It initialize the iPod init parameter. 
				
	Parameter : 

  	Return : none
		
**************************************************************************/
static IPOD_ERROR IPOD_API_UART_InitParam(pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData)
{
	IPOD_ERROR iPod_err = IPOD_NO_ERROR;
	
	memset(pParam, 0x00, sizeof(IPOD_INIT_PARAM));

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

	
	pParam->IdentifyToken.DeviceOption = (LOW_POWER_ONLY | AUTHENTICATION_IMMEDIATELY);
	pParam->IdentifyToken.EnterExtendedModeOnInit = IPOD_FUNC_ENABLE;

#ifdef IPOD_UART_CP_USE /* IDPS support on UART mode */
	pParam->IdentifyToken.LingoCnt = 3;
	pParam->IdentifyToken.Lingos[0] = LINGO_GENERAL;
	pParam->IdentifyToken.Lingos[1] = LINGO_EXTENDED_INTERFACE;
	pParam->IdentifyToken.Lingos[2] = LINGO_SIMPLE_REMOTE;

	pParam->AccPrefToken.Total_PreferenceCnt = 1;
	pParam->AccPrefToken.Pref[0].m_ClassID = IPOD_LINE_OUT_USAGE;
	pParam->AccPrefToken.Pref[0].m_SettingID = IPOD_SETTING_ON;
	pParam->AccPrefToken.Pref[0].m_RestoreOnExit = 0;
	 
#else
	pParam->IdentifyToken.LingoCnt = 1;
	pParam->IdentifyToken.Lingos[0] = LINGO_EXTENDED_INTERFACE;
#endif

	pParam->IdentifyToken.ML_Lingo = IPOD_ConvertSingleToMultiLingo(pParam);
	pParam->AccesoryCapToken = AC_ANALOG_LINE_OUT;

	pParam->pAccInfoToken = &gIPOD_AccInfo;


	return iPod_err;

}

/**************************************************************************
	Function : IPOD_API_UART_MountDev

 	Description : It initialize the iPod init parameter. ( communication with OS application )
				
	Parameter : 

  	Return : none
		
**************************************************************************/
int IPOD_API_UART_MountDev(void)
{
	IPOD_INIT_PARAM init_param;
	IPOD_INIT_CHANNRL_PARAM ChannelPrarm;
	IPOD_LINGO_INFO_DATA LingoInfoData;
	unsigned long iPod_Handle;
	/* UART connection : USB 0 block*/
	unsigned int Block = 0;
	unsigned long DiskDevice = ((unsigned long)DISK_DEVICE_IPOD + (unsigned long)Block);
	int Mount_Status = TC_FAIL;
	IPOD_ERROR ipod_err;
	void *Handle_Check; // = DISK_GetHandle(DISK_DEVICE_IPOD);
	IPOD_STATE State;
	unsigned int InitRetry;

	Handle_Check = DISK_GetHandle(DiskDevice);

#if defined(TCC860x) || defined(TCC78X) || defined(TCC83XX)
	UI_API_DrawPopUp3Line_withoutTimeout("IPOD", "Device", "Detect");
#endif

	State = IPOD_API_GetStatus(Handle_Check);
	if(IPOD_PLUGED == State)
	{
		ipod_err = IPOD_Open(&iPod_Handle);
		if(IPOD_NO_ERROR == ipod_err)
		{
			ipod_err = IPOD_API_UART_InitChannelParam(&ChannelPrarm, DISK_DEVICE_IPOD);
			if(IPOD_NO_ERROR == ipod_err)
			{
				for(InitRetry = 0; InitRetry < 2; InitRetry++)
				{
					ipod_err = IPOD_InitChannel((void *)iPod_Handle, &ChannelPrarm);
					if(IPOD_NO_ERROR == ipod_err)
					{
						#ifdef IPOD_UART_SUPPORT_IDPS
						IPOD_API_CheckiPodOption((void *)iPod_Handle, &LingoInfoData);
						#endif

						//ipod_err = IPOD_API_UART_InitParamOSApp(&init_param, &LingoInfoData);
						ipod_err = IPOD_API_UART_InitParam(&init_param, &LingoInfoData);
						if(IPOD_NO_ERROR == ipod_err)
						{
							ipod_err = IPOD_Init((void *)iPod_Handle, &init_param);
							if(ipod_err == IPOD_NO_ERROR)
							{
								Mount_Status = TC_SUCCESS;

								#ifdef IPOD_UART_CP_USE
								#else
									IPOD_EnterRemoteUIMode((void *)iPod_Handle);
								#endif
								
								DISK_SetHandle((int)DiskDevice, (void *)iPod_Handle);
								#if defined(TCC860x) || defined(TCC78X) || defined(TCC83XX)
								UI_API_DrawPopUp3Line("IPOD", "Device Mount", "Success");
								#endif
								IPOD_Display_Init((void *)iPod_Handle, Block);
								IPOD_SetAccess((void *)NULL, SET);

							}
						//-	else
						//-	{
						//-		IPOD_Free_AudioPlayInfo((void *)iPod_Handle);
						//-		IPOD_Close((void *)iPod_Handle);
						//-	}
						}
					}
					if((IPOD_COMMAND_TIMEOUT == ipod_err) ||(IPOD_COMMAND_FAILED == ipod_err) 
						||(IPOD_IO_CP_ERROR == ipod_err))
					{
						continue;
					}
					else
					{
						break;
					}

					
				}
				if(IPOD_NO_ERROR != ipod_err)
				{
					IPOD_Free_AudioPlayInfo((void *)iPod_Handle);
					IPOD_Close((void *)iPod_Handle);
				}
				
			}
		}
	}
	else  if(IPOD_INITIALIZED == State) 
	{
		/* IPOD already inited by USB host ( not filesystem)*/
		iPod_Handle = (unsigned long)Handle_Check;
		DISK_SetHandle(DiskDevice, (void *)iPod_Handle);
		Mount_Status = TC_SUCCESS;
	}


	return Mount_Status;
}



#ifdef TCC860x
void IPOD_UartInit(void)
{
	HwHCLKSTOP &= ~Hw5;				// enabling HCLK for UART/IrDA Block

	// GPIO Setting for UART
	HwGSEL_B |= Hw8; 				// GPIO_B8 -> TxD
	HwGIOCON_B &= ~Hw9;			// GPIO_B9(RxD) : Input
	HwGIOCON_B	|= Hw8;				// GPIO_B8(TxD) : Output
	
	// 2006.10.04 JHJ - Always 48MHz for UART Clock
	HwSW_nRST	|= Hw5;		// Reset UART
	HwDIVMODE |= Hw7;	// Divider Mode for UART Clock
	HwUTCLKmode = Hw14|((PLL_FREQ/48000)-1);	// 48 MHz;
	HwCKCTRL &= 0xFFFFFFDF;			// UART clock enable
//	HwUTDL = 48000000 / (16 * 115200);	// Baud rate = 115200 
	HwUTDL = 48000000 / (16 * 57600);	// Baud rate = 57600

	// Operation mode Setting
	HwUTIR = 0;
	HwUTCR = HwUTCR_TF | HwUTCR_RF | Hw3;		// Clear TX/RX FIFO, 1byte FIFO, No parity, 1 stop bit

	// Interrupt / Polling Setting
  	HwUTIR = HwUTIR_ERX | HwUTIR_QTX | HwUTIR_QRX;			// Enable Rx Interrupt 
	//HwUTIR |= HwUTIR_ETX;			// Enable Tx Interrupt (TX Int is enabled only when tx is started)
    	
	HwIRQSEL |= HwINT_UT;			// IRQ Selection
	HwIEN |= HwINT_UT;				// Interrupt enable
}
#endif


void IPOD_API_UART_InitPort(void)
{
#ifdef TCC860x
	IPOD_UartInit();
	BITCLR(IPOD_RMV_CON, IPOD_RMV_PIN);

	IPOD_Usb2Gpio();
	IPOD_Uart2Gpio();
#endif

#if (defined(TCC83XX) || defined(TCC78X))
	BITSET(IPOD_SW_CON, IPOD_SW_PIN);
	BITCLR(IPOD_RMV_CON, IPOD_RMV_PIN);

	IPOD_Usb2Gpio();
	IPOD_Uart2Gpio();
#endif

#ifdef TCC80XX
	int lBaudrate;
	(void) DDI_Open(DDI_AD7_ID, DDI_OP_READ);
	(void) DDI_Open(DDI_UART0_ID, DDI_OP_READ|DDI_OP_WRITE|DDI_OP_RXIRQ|DDI_OP_TXIRQ);
	lBaudrate = BAUDRATE_57600;
	(void) DDI_Ioctl(DDI_UART0_ID, UART_IOCTL_BAUDRATE, &lBaudrate, NULL);

	IPOD_Usb2Gpio();
	IPOD_Uart2Gpio();
#endif

}


int IPOD_UFD_Insert(void)
{
	unsigned int TxPinCheck_one, RxPinCheck_zero;
	unsigned int TxPinCheck_zero, RxPinCheck_one;
	
	if((IPOD_UFDStatusFlag == IPOD_UFD_REMOVED) && (IPOD_Insert == 0))
	{
		TxPinCheck_one = ISONE(IPOD_RTX_PORT, IPOD_TX_PIN);
		RxPinCheck_zero = ISZERO(IPOD_RTX_PORT, IPOD_RX_PIN);

		TxPinCheck_zero = ISZERO(IPOD_RTX_PORT, IPOD_TX_PIN);
		RxPinCheck_one = ISONE(IPOD_RTX_PORT, IPOD_RX_PIN);
		
		if((!IPOD_Insert) && (TxPinCheck_one) && (RxPinCheck_zero))
		{
			IPOD_UFDStatusFlag = IPOD_UFD_INSERTED;
			IPOD_Gpio2Usb();
			return 0;
		}
		else if((TxPinCheck_zero) && (RxPinCheck_one))
		{
			return -1;
		}
	}
	return 0;
}

void IPOD_UFD_Remove(void)
{
	if(IPOD_UFDStatusFlag == IPOD_UFD_INSERTED)
	{
		IPOD_Usb2Gpio();
		IPOD_UFDStatusFlag = IPOD_UFD_REMOVED;
	}

}
//#endif
#if 0
//#ifdef TCC860x
void IPOD_USBEnable(void)
{
	HwIRQSEL 	|= HwINT_UH;	// USB HOST interrupt should be set to IRQ mode
	HwIEN		|= HwINT_UH;	// USB HOST interrupt should be enabled
}

void IPOD_USBDisable(void)
{
	//HwIRQSEL 	&= ~HwINT_UH;	// USB HOST interrupt should be set to IRQ mode
	HwIEN		&= ~HwINT_UH;	// USB HOST interrupt should be enabled
}
#endif

void IPOD_Gpio2Usb(void)
{
#ifdef TCC860x
	HwGIOCON_B |= Hw29|Hw28;
	HwGSEL_B   |= Hw29|Hw28;
//	IPOD_USBEnable();
	USBH_FUNC_EnablePort(0);
	TC_TimeDly(1);
#endif

#if (defined(TCC83XX) || defined(TCC78X))
	BITSET(IPOD_SW_PORT, IPOD_SW_PIN);	// Set "ASW_SEL" port to HIGH.
	TC_TimeDly(1);
#endif

#ifdef TCC80XX
//	IPOD_USBEnable();
	USBH_FUNC_EnablePort(0, 0);
	TC_TimeDly(1);
#endif

}

void IPOD_Usb2Gpio(void)
{
#ifdef TCC860x
	HwGIOCON_B &= ~(Hw29|Hw28);
	HwGSEL_B   &= ~(Hw29|Hw28);
//	IPOD_USBDisable();
	USBH_FUNC_DisablePort(0);
#endif

#if (defined(TCC83XX) || defined(TCC78X))
	BITCLR(IPOD_SW_PORT, IPOD_SW_PIN);	// Set "ASW_SEL" port to LOW.
#endif

#ifdef TCC80XX
	USBH_FUNC_DisablePort(0, 0);
#endif

}

void IPOD_Gpio2Uart(void)
{
#ifdef TCC78X
	//GPIO mode -> UART mode
	BITCLR(HwPORTCFG2, HwPORTCFG2_UART1_3);
#endif

#ifdef TCC860x
//	HwGSEL_B |= Hw8; 				// GPIO_B8 -> TxD
//	HwGIOCON_B &= ~Hw9;			// GPIO_B9(RxD) : Input
//	HwGIOCON_B	|= Hw8;				// GPIO_B8(TxD) : Output
	IPOD_UartInit();
#endif

#ifdef TCC83XX
	//GPIO mode -> UART mode
	//BITSET(HwGSEL_B, HwGSEL_B_N2_UT0);
	BITSET(HwGSEL_F, HwGSEL_B_N3_UT1);
	//HwIEN |= Hw7;
#endif

#ifdef TCC80XX
	int lBaudrate;
	(void) DDI_Open(DDI_UART0_ID, DDI_OP_READ|DDI_OP_WRITE|DDI_OP_RXIRQ|DDI_OP_TXIRQ);
	lBaudrate = BAUDRATE_57600;
	(void) DDI_Ioctl(DDI_UART0_ID, UART_IOCTL_BAUDRATE, &lBaudrate, NULL);
#endif

}

void IPOD_Uart2Gpio(void)
{
#ifdef TCC78X
	//UART mode -> GPIO mode
	BITSET(HwPORTCFG2, HwPORTCFG2_UART1_3);
	BITCLR(IPOD_RTX_CON, IPOD_RX_PIN|IPOD_TX_PIN);
#endif

#ifdef TCC860x	//uart0
	HwGSEL_B &= ~Hw8; //gpio mode
	IPOD_RTX_CON &= ~(IPOD_RX_PIN | IPOD_TX_PIN);
	HwCKCTRL |= HwCLK_UART;
#endif

#ifdef TCC83XX
	//UART mode -> GPIO mode
	//HwIEN &= ~ Hw7;
	//BITCLR(HwGSEL_B, HwGSEL_B_N2_UT0);	//uart 0
	BITCLR(HwGSEL_F, HwGSEL_B_N3_UT1);		//uart 3
	BITCLR(IPOD_RTX_CON, IPOD_RX_PIN|IPOD_TX_PIN);
#endif

#ifdef TCC80XX
	DDI_Close(DDI_UART0_ID);

	BITCLR(IPOD_RTX_SEL, IPOD_RX_PIN|IPOD_TX_PIN);
	BITCLR(IPOD_RTX_CON, IPOD_RX_PIN|IPOD_TX_PIN);
#endif


}


int IPOD_Ioctl(int function, void *param)
{
	void *iPod_Handle = DISK_GetHandle(DISK_DEVICE_IPOD);
	//void *ExtInfo = IPOD_GetExtInfo(iPod_Handle);

	switch(function){
		case	DEV_INITIALIZE:
		case	DEV_GET_DISKINFO:
		case	DEV_BOOTCODE_READ_PAGE:
		case	DEV_BOOTCODE_WRITE_PAGE:
		case	DEV_GET_WRITE_PROTECT:
		case	DEV_SERIAL_PROCESS:
			break;
		case DEV_SET_REMOVED:
			break;
		case DEV_GET_PREV_STATUS:
			break;
		case DEV_GET_INSERTED:
			{
				if(IPOD_UFDStatusFlag == IPOD_UFD_INSERTED)
					return 0;
				
				if(!IPOD_Insert)
				{
					if((ISZERO(IPOD_RTX_PORT, IPOD_TX_PIN)) && (ISONE(IPOD_RTX_PORT, IPOD_RX_PIN)))
					{
						/* Remove detection Pin check */
						if(IPOD_GetDetectStatus((void *)0) == IPOD_CONNECTED)
						{
							IPOD_Insert = 1;
							IPOD_Gpio2Uart();
							return 1;
						}
					}
					return 0;
				}
				
				
				else
				{
					if(IPOD_GetDetectStatus((void *)0) == IPOD_CONNECTED)
					{
						return 1;
					}
					else
					{
						IPOD_Insert = 0;
						IPOD_UFD_Remove();
						IPOD_Free_AudioPlayInfo(iPod_Handle);
						IPOD_Close(iPod_Handle);
						IPOD_Uart2Gpio();
						return 0;
					}
				}
			}
			break;
		case DEV_GET_PLAYABLE_STATUS:
			break;
		default:
			return 0;
	}
	return 0;
}

#endif//IPOD_UART_INCLUDE





