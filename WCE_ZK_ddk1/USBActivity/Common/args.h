/****************************************************************************
*   FileName    : args.h
*   Description : 
****************************************************************************
*
*   TCC Version : 1.0
*   Copyright (c) Telechips, Inc.
*   ALL RIGHTS RESERVED
*
****************************************************************************/

#ifndef __ARGS_H__
#define __ARGS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _tSYSTEM_ARGS {
	BYTE NANDUUID[32];
	BYTE CHIPID[32];
	BYTE KITL[4];
	BYTE MACADDRESS[32];
	BYTE IPADDRESS[32];
}tSYSTEM_ARGS, *ptSYSTEM_ARGS;


typedef struct _tDMA_BUFS {
	BYTE CH0_BUFFER[0x200];
	BYTE CH1_BUFFER[0x200];
	BYTE CH2_BUFFER[0x200];	
}tDMA_BUFS, *ptDMA_BUFS;

typedef struct _tSYSTEMP_PARAM {
//	OAL_ARGS_HEADER	header;
	BYTE ADMA_BUFFER[0x200*16]; 	// 8KByte
	
	tDMA_BUFS DMA0;
	tDMA_BUFS DMA1;
	tDMA_BUFS DMA2;
	tDMA_BUFS DMA3;
	
	tSYSTEM_ARGS SYSTEM_ARGS; 			// 132Byte
					// 875Byte
	unsigned int	SUSPEND_MASK[2];	// 8Byte
	BYTE POWER_KEY;					// 1Byte
	BYTE dummy[495];
	BYTE RESERVED[380];	
}tSYSTEM_PARAM, *ptSYSTEM_PARAM; // 14.149Kbyte	+ 875Byte = 15KByte

#define LCD_FRAME_WIDTH_SIZE_MAX	 	800
#define LCD_FRAME_WIDTH_HEIGHT_MAX		480
#define LCD_FRAME_BIT_CONFIG_MAX 		4

#define LCD_FRAME_BUFFER_ADDRESS	0x40000000
#define LCD_FRAME_BUFFER_SIZE	 	LCD_FRAME_WIDTH_SIZE_MAX*LCD_FRAME_WIDTH_HEIGHT_MAX*LCD_FRAME_BIT_CONFIG_MAX

#define KERNEL_BASEADDRESS		(LCD_FRAME_BUFFER_ADDRESS+((LCD_FRAME_BUFFER_SIZE + 0x100000)/0x100000)*0x100000)
#define SYSTEM_PARAM_BASEADDRESS ((KERNEL_BASEADDRESS-(sizeof(tSYSTEM_PARAM)+0x1000)/0x1000*0x1000 )) 

//HW CODEC Decode Buffer (Only 128MB)
#define HW_CODEC_DECODE_BUFFER_SIZE 	0x1E00000
#define HW_CODEC_DECODE_BUFFER_BASE		0x46200000

VOID OALArgsInit(DWORD BASEADDRESS);


#define SYSTEM_ARGSMAXSIZE		0x200
#define PROGRAM_BASE_ADDRESS  0x20500000
#define PROGRAM_TCBOOTSUS_ADDRESS  0x204ffffc
#define PROGRAM_BSPSUS_ADDRESS  0xa04ffffc
#define SYSTEM_STARTADDR_TCBOOT  0x20100000
#define SYSTEM_STARTADDR  0xa0100000
#define BOOTARGS_STARTADDR	(SYSTEM_STARTADDR_TCBOOT-SYSTEM_ARGSMAXSIZE)
#define BSPARGS_STARTADDR	(SYSTEM_STARTADDR-SYSTEM_ARGSMAXSIZE)

//Suspend define 
#define BSP_SUSPEND_MASK1       	0x424E4654 //"TFNB"
#define BSP_SUSPEND_MASK2       	0x6C426E45 //"EnBl"
#define	BSP_SUSPEND_KEY				0xE1
#define	BSP_SLEEP_KEY				0xE0
/************************************************************************************************
*  BOOT Arguments Structures
************************************************************************************************/
typedef struct _KITL{
	unsigned int	nKITLMode;				// 0 -- disable, 1 -- active, 2 -- passive
	unsigned int	nDHCP;					// 0 -- disable, 1 -- enable
	unsigned int	nIPAddr;
	unsigned int	nSubnetMask;
	USHORT			chMACAddr[3];
	unsigned char	Reserved[2];
}KITL,* PKITL;

typedef struct _MEMBUF{
	unsigned int	INTBUF;
	unsigned char	CHARBUF;
	unsigned char	Reseved[3];
}MEMBUF,* PMEMBUF;

typedef struct _SYSTEMPARAM{
	unsigned char	SIGTCBOOT[32];
	unsigned char	DeviceID[32];
	unsigned char	NANDID[32];
	unsigned long long CHIPID;
	unsigned int	nSignature;           // Config signature (used to validate).
	unsigned int	nVerMajor;            // Config major version.
    unsigned int	nVerMinor;            // Config minor version.
	unsigned int	nBootDelay;           // Bootloader count-down delay.
	unsigned int	LaunchAddress;       // Kernel region launch address.
}SYSTEMPARAM,* PSYSTEMPARAM;

#define LCD_NORMAL		0x00000001
#define LCD_ALPHA		0x00000002
#define LCD_CHROMA		0x00000004
#define LCD_ORDER012	0x00000010
#define LCD_ORDER102	0x00000020
#define LCD_ORDER201	0x00000040
#define LCD_ORDER210	0x00000080

typedef struct _LCDINFO{
	unsigned int	nWidth;
	unsigned int	nHeight;
	unsigned int	nMode;
	unsigned int	nChromaKey;
}LCDINFO,* PLCDINFO;

typedef struct	_BOOTARGS {
	unsigned int	nConfigFlags;	
	KITL			mKitl;
	MEMBUF			mMemBuf;
	SYSTEMPARAM		mSystemParam;
	LCDINFO			mLcdInfo;
	unsigned int	SetFlag;
}BOOTARGS,* PBOOTARGS;

#ifdef __cplusplus
}
#endif

#endif // __ARGS_H__
