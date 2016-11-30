// ----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// File       : ioctl_code.h
// Description: Contains the constants for the local hardware platform IOCTL
//              routines
// Assumptions:
// ----------------------------------------------------------------------------

#ifndef __IOCTL_CODE_H__
#define __IOCTL_CODE_H__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOCTL_HAL_TCCCKC	CTL_CODE(FILE_DEVICE_HAL, 1000, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HAL_TCCGPIO	CTL_CODE(FILE_DEVICE_HAL, 1001, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define TCC_IOCTLCode(f,m)	CTL_CODE ( FILE_DEVICE_UNKNOWN , 0xA00 + (f), (m), FILE_ANY_ACCESS )
/*******************************************
NAND Controller IOCTL CODE
********************************************/
#define DISK_HD_WRITE					TCC_IOCTLCode(1,METHOD_BUFFERED)
#define DISK_HD_READ					TCC_IOCTLCode(2,METHOD_BUFFERED)
#define DISK_FW_UPDATE					TCC_IOCTLCode(3,METHOD_BUFFERED)
#define DISK_GET_SERIALNUM				TCC_IOCTLCode(4,METHOD_BUFFERED)
#define DISK_MULTI_HD_WRITE				TCC_IOCTLCode(5,METHOD_BUFFERED)
#define DISK_MULTI_HD_READ				TCC_IOCTLCode(6,METHOD_BUFFERED)
#define DISK_GET_BOOTCRCCODE			TCC_IOCTLCode(7,METHOD_BUFFERED)
#define DISK_GET_MAX_SECTOR_PER_BLOCK	TCC_IOCTLCode(8,METHOD_BUFFERED)
#define DISK_SET_ALIGN_CACHE			TCC_IOCTLCode(9,METHOD_BUFFERED)

/*******************************************
		 CKC Controller IOCTL CODE
********************************************/
#define IOCTL_CKC_SET_PERI 			TCC_IOCTLCode(101, METHOD_BUFFERED)
#define IOCTL_CKC_GET_PERI 			TCC_IOCTLCode(102, METHOD_BUFFERED)
#define IOCTL_CKC_SET_PERIBUS 		TCC_IOCTLCode(103, METHOD_BUFFERED)
#define IOCTL_CKC_GET_PERIBUS 		TCC_IOCTLCode(104, METHOD_BUFFERED)
#define IOCTL_CKC_SET_PERISWRESET	TCC_IOCTLCode(105, METHOD_BUFFERED)
#define IOCTL_CKC_SET_CPU			TCC_IOCTLCode(106, METHOD_BUFFERED)
#define IOCTL_CKC_SET_SMUI2C		TCC_IOCTLCode(107, METHOD_BUFFERED)
#define IOCTL_CKC_GET_CPU			TCC_IOCTLCode(108, METHOD_BUFFERED)
#define IOCTL_CKC_GET_BUS			TCC_IOCTLCode(109, METHOD_BUFFERED)

#define IOCTL_CKC_GET_VALIDPLLINFO	TCC_IOCTLCode(110, METHOD_BUFFERED)
#define IOCTL_CKC_GET_CLOCKINFO 	TCC_IOCTLCode(111, METHOD_BUFFERED)

#define IOCTL_CKC_SET_FBUS			TCC_IOCTLCode(112, METHOD_BUFFERED)
#define IOCTL_CKC_GET_FBUS			TCC_IOCTLCode(113, METHOD_BUFFERED)
#define IOCTL_CKC_SET_PMUPOWER		TCC_IOCTLCode(114, METHOD_BUFFERED)
#define IOCTL_CKC_GET_PMUPOWER		TCC_IOCTLCode(115, METHOD_BUFFERED)

#define IOCTL_CKC_SET_CHANGECPU		TCC_IOCTLCode(120, METHOD_BUFFERED)
#define IOCTL_CKC_SET_CHANGEMEM 	TCC_IOCTLCode(121, METHOD_BUFFERED)
#define IOCTL_CKC_SET_CHANGEFBUS 	TCC_IOCTLCode(122, METHOD_BUFFERED)

#define IOCTL_CKC_SET_FBUSSWRESET	TCC_IOCTLCode(123, METHOD_BUFFERED)

#define IOCTL_CKC_SET_DDIPWDN	 	TCC_IOCTLCode(124, METHOD_BUFFERED)
#define IOCTL_CKC_GET_DDIPWDN	 	TCC_IOCTLCode(125, METHOD_BUFFERED)
#define IOCTL_CKC_SET_VIDEOCFGPWDN	 	TCC_IOCTLCode(126, METHOD_BUFFERED)
#define IOCTL_CKC_GET_VIDEOCFGPWDN	 	TCC_IOCTLCode(127, METHOD_BUFFERED)
#define IOCTL_CKC_SET_VIDEOCFGSWRESET	 	TCC_IOCTLCode(128, METHOD_BUFFERED)



#define IOCTL_CKC_SET_ETCBLOCK		TCC_IOCTLCode(130, METHOD_BUFFERED)

#define IOCTL_BLK_SETPOWER			TCC_IOCTLCode(140, METHOD_BUFFERED)
#define IOCTL_BLK_GETPOWER			TCC_IOCTLCode(141, METHOD_BUFFERED)


/*******************************************
         GPSB-SPI Master IOCTL CODE
********************************************/
#define IOCTL_SPI_SETUP					TCC_IOCTLCode(201, METHOD_BUFFERED)
#define IOCTL_SPI_LOOPBACK				TCC_IOCTLCode(202, METHOD_BUFFERED)

/*******************************************
         GPSB-TSIF Slave IOCTL CODE
********************************************/
#define IOCTL_TSIF_SET_MODE				TCC_IOCTLCode(301, METHOD_BUFFERED)
#define IOCTL_TSIF_DMA_START			TCC_IOCTLCode(302, METHOD_BUFFERED)
#define IOCTL_TSIF_DMA_STOP				TCC_IOCTLCode(303, METHOD_BUFFERED)
#define IOCTL_TSIF_WAIT_DMA_DONE		TCC_IOCTLCode(304, METHOD_BUFFERED)
#define IOCTL_TSIF_GET_MAX_DMA_SIZE		TCC_IOCTLCode(305, METHOD_BUFFERED)
#define IOCTL_TSIF_SET_PID				TCC_IOCTLCode(306, METHOD_BUFFERED)

/*******************************************
		 GEN IOCTL CODE
********************************************/
#define IOCTL_UID_VIRTUALCOPY			TCC_IOCTLCode(401, METHOD_BUFFERED)
//#define IOCTL_UID_FREE_PATVA			TCC_IOCTLCode(402, METHOD_BUFFERED)
//#define IOCTL_UID_GET_HWDECODEMEM 	TCC_IOCTLCode(403, METHOD_BUFFERED)
#define IOCTL_HAL_VIRTUALCOPY			TCC_IOCTLCode(410, METHOD_BUFFERED)
#define IOCTL_HAL_TEST					TCC_IOCTLCode(440, METHOD_BUFFERED)
#define IOCTL_HAL_DONE					TCC_IOCTLCode(444, METHOD_BUFFERED)

/*******************************************
I2C Controller IOCTL CODE
********************************************/
#define IOCTL_I2C_INIT					 TCC_IOCTLCode(500, METHOD_BUFFERED)
#define IOCTL_I2C_OPEN					 TCC_IOCTLCode(501, METHOD_BUFFERED)
#define IOCTL_I2C_CLOSE 				 TCC_IOCTLCode(502, METHOD_BUFFERED)
#define IOCTL_I2C_READ					 TCC_IOCTLCode(503, METHOD_BUFFERED)
#define IOCTL_I2C_WRITE 				 TCC_IOCTLCode(504, METHOD_BUFFERED)

/*******************************************
GPIO Driver IOCTL CODE
********************************************/
#define IOCTL_GPIO_PATOVA			 	TCC_IOCTLCode(600, METHOD_BUFFERED)
//#define IOCTL_GPIO_FREEBASE			TCC_IOCTLCode(601, METHOD_BUFFERED)
//#define IOCTL_GPIO_SETCHANGEMODE 		TCC_IOCTLCode(602, METHOD_BUFFERED)
#define IOCTL_GPIO_GET_HWCODECBASEADDRESS	TCC_IOCTLCode(610, METHOD_BUFFERED)



/*******************************************
		 Camera Interface Controller IOCTL CODE
********************************************/
#define IOCTL_CIF_PORTINITIALIZE		TCC_IOCTLCode(700, METHOD_BUFFERED)
#define IOCTL_CIF_PREVIEWCONFIG 		TCC_IOCTLCode(701, METHOD_BUFFERED)
#define IOCTL_CIF_CAPTURECONFIG 		TCC_IOCTLCode(702, METHOD_BUFFERED)
#define IOCTL_CIF_STARTCAPTURE			TCC_IOCTLCode(703, METHOD_BUFFERED)
#define IOCTL_CIF_FUNCTIONCONTROL		TCC_IOCTLCode(704, METHOD_BUFFERED)
#define IOCTL_CIF_SETEFFECT 			TCC_IOCTLCode(705, METHOD_BUFFERED)
#define IOCTL_CIF_STARTOPERATING		TCC_IOCTLCode(706, METHOD_BUFFERED)
#define IOCTL_CIF_STOPOPERATING 		TCC_IOCTLCode(707, METHOD_BUFFERED)

#define IOCTL_CAM_STARTPREVIEW			TCC_IOCTLCode(710, METHOD_BUFFERED)
#define IOCTL_CAM_STOPPREVIEW			TCC_IOCTLCode(711, METHOD_BUFFERED)
#define IOCTL_CAM_STARTCAPTURECAMERA	TCC_IOCTLCode(712, METHOD_BUFFERED)
#define IOCTL_CAM_CONTINUEPREVIEW		TCC_IOCTLCode(713, METHOD_BUFFERED)
#define IOCTL_CAM_EFFECT				TCC_IOCTLCode(714, METHOD_BUFFERED)

#define IOCTL_MODULE_INIT				TCC_IOCTLCode(720, METHOD_BUFFERED)
#define IOCTL_MODULE_PREVIEW			TCC_IOCTLCode(721, METHOD_BUFFERED)
#define IOCTL_MODULE_CAPTURE			TCC_IOCTLCode(722, METHOD_BUFFERED)
#define IOCTL_MODULE_MODE				TCC_IOCTLCode(723, METHOD_BUFFERED)
#define IOCTL_MODULE_DEINIT 			TCC_IOCTLCode(724, METHOD_BUFFERED)

/*******************************************
Remote Control IOCTL CODE
********************************************/
#define IOCTL_RMT_PWRKEY				TCC_IOCTLCode(750, METHOD_BUFFERED)

/*******************************************
         TSADC Driver IOCTL Code
********************************************/
#define IOCTL_TSADC_CHANNEL0			TCC_IOCTLCode(800, METHOD_BUFFERED)
#define IOCTL_TSADC_CHANNEL1			TCC_IOCTLCode(801, METHOD_BUFFERED)
#define IOCTL_TSADC_CHANNEL2			TCC_IOCTLCode(802, METHOD_BUFFERED)
#define IOCTL_TSADC_CHANNEL3			TCC_IOCTLCode(803, METHOD_BUFFERED)
#define IOCTL_TSADC_TOUCHSCREEN			TCC_IOCTLCode(804, METHOD_BUFFERED)
#define IOCTL_TSADC_TOUCHSCREEN_GPIO	TCC_IOCTLCode(805, METHOD_BUFFERED)

/*******************************************
         SDMMC IOCTL CODE
********************************************/
#define IOCTL_SD_STATE					TCC_IOCTLCode(900, METHOD_BUFFERED)

/*******************************************
         USB OTG IOCTL CODE
********************************************/
#define IOCTL_USBOTG_START_OTGHOST      TCC_IOCTLCode(950, METHOD_BUFFERED)
#define IOCTL_USBOTG_STOP_OTGHOST      TCC_IOCTLCode(951, METHOD_BUFFERED)



/*******************************************
		 USBHost AUDIO CLASS
********************************************/
#define IOCTL_USBH_AUDIO_GET_DRIVER_VERSION			TCC_IOCTLCode(1100, METHOD_BUFFERED)
#define IOCTL_USBH_AUDIO_SET_FULL_BANDWIDTH			TCC_IOCTLCode(1101, METHOD_BUFFERED)
#define IOCTL_USBH_AUDIO_SET_ZERO_BANDWIDTH			TCC_IOCTLCode(1102, METHOD_BUFFERED)
#define IOCTL_USBH_AUDIO_SET_SAMPLE_FREQ			TCC_IOCTLCode(1103, METHOD_BUFFERED)

/*******************************************
		 WAVE Driver IOCTL CODE
********************************************/
#define IOCTL_MODE_AEC_ON							TCC_IOCTLCode(1150, METHOD_BUFFERED)
#define IOCTL_MODE_AEC_OFF							TCC_IOCTLCode(1151, METHOD_BUFFERED)
#define IOCTL_WAVE_INPUT_TYPE						TCC_IOCTLCode(1152, METHOD_BUFFERED)

/******************************************
         TVOUT Controller IOCTL CODE
********************************************/
#define IOCTL_TVOUT_TYPE				TCC_IOCTLCode(1200, METHOD_BUFFERED)
#define IOCTL_TVOUT_OPEN				TCC_IOCTLCode(1201, METHOD_BUFFERED)
#define IOCTL_TVOUT_CLOSE				TCC_IOCTLCode(1202, METHOD_BUFFERED)
#define IOCTL_TVOUT_CONNECT_LCDC		TCC_IOCTLCode(1203, METHOD_BUFFERED)


/******************************************
  USB Host TccHID client driver IOCTL Code
********************************************/
#define IOCTL_USBH_TCCHID_GET_DRIVER_VERSION	TCC_IOCTLCode(1300, METHOD_BUFFERED)
#define IOCTL_USBH_TCCHID_LAST_IOCTL			TCC_IOCTLCode(1399, METHOD_BUFFERED)


//@Power
/*******************************************
POWER Control IOCTL CODE
********************************************/
#define IOCTL_PWR_CONTROL				TCC_IOCTLCode(1400, METHOD_BUFFERED)


//CTL_CODE Function Type range is 2048-4095 so, A00+f(n) max n is 1535 !!!!!!

#ifdef __cplusplus
}
#endif

#endif // __IOCTL_CFG_H__
