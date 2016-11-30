/****************************************************************************
 *   FileName    : tca_ckcstr.h
 *   Description : 
 ****************************************************************************
 *
 *   TCC Version 1.0
 *   Copyright (c) Telechips, Inc.
 *   ALL RIGHTS RESERVED
 *
 ****************************************************************************/

#ifndef __TCA_CKCSTR_H__
#define __TCA_CKCSTR_H__

#ifdef _LINUX_	//for bootloader
	#include <common.h>
	#if defined(TCC79X)
		#ifndef _TCC79x_
		#define _TCC79x_
		#endif
	#elif defined(TCC83XX)
		#ifndef _TCC83x_
		#define _TCC83x_
		#endif
	#elif defined(TCC80XX)
		#ifndef _TCC80x_
		#define _TCC80x_
		#endif
	#endif 
#endif

#define MHz 1
#define KHz 0
enum
{
	IDLE_PRIORITY = 0, // Don't Return IDLE_PRIORITY
	LOW_PRIORITY,
	MID_PRIORITY,
	HIGH_PRIORITY,
	MAX_PRIORITY,

	CLOCK_PRIORITY_NUM,
//}stCKC_PRIORITY;
};

typedef struct _stSYSTEM_CKC
{
	unsigned int mFPll;
	unsigned int mFCpu;
	unsigned int mFBus;
	unsigned int mFUsed;
}stSYSTEM_CKC;


// For CKC Controller
typedef struct _stCKCIOCTL{
	unsigned int ControlCode;
	//Reset or bus Enable name
	unsigned int PeriRBName; 
	//Peri Clock
	unsigned int PeriClockName; 
	unsigned int PeriClockSource; 
	unsigned int PeriUnit;			//Mhz or Khz
	unsigned int PeriFreq;
	//PLL Cllock
	unsigned int PllChannel;
	unsigned int PllValue;
	unsigned int P;
	unsigned int M;
	unsigned int S;
	//CPU Cllock
	unsigned int CpuValue; 
	//BUS Cllock
	unsigned int BusValue;
	//mode 
	unsigned int Mode; // Enable, Disable, ahalf, athird

	unsigned int Priority;
}stCKCIOCTL;


typedef struct _stCKCINFO{
	unsigned int CurrentBusFreq;
	unsigned int CurrentSysFreq;
	unsigned int CurrentCpuFreq;
//#ifdef _TCC79x_
	unsigned int CurrentSubCpuFreq;
//#endif
	int PeriFreq; 
	unsigned int ValidPll[30];
	int retVal;
	unsigned int CurrentPriority;

}stCKCINFO;


/************************************************************************************************
*                                        ENUM                                                   *
************************************************************************************************/
enum{ /* System Clock Source */
	DIRECTPLL0=0,
	DIRECTPLL1,
	DIVIDEPLL0,
	DIVIDEPLL1,
	DIRECTXIN,
	DIVIDEXIN,
	DIRECTXTIN,
	DIVIDEXTIN,
};

#if defined(_TCC80x_)
	enum{ /* Periperals Clock Source */
		DIRECTPLL2=8,
		DIVIDEPLL2,
		PK0,
		PK1,
		PK2,
		PK3,
		PK4,
		CLKFROM48M,
	};
#else
enum{ /* Periperals Clock Source */
	PLL0DIVIDER1=8,
	PLL1DIVIDER1,
	EXTERNALCLOCK,
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4,
	CLKFROM48M,
};
#endif



#if defined(_TCC79x_)
enum{
	PERI_USB11H,
	PERI_SDMMC,
	PERI_MSTICK,
	PERI_I2C,
	PERI_LCD,
	PERI_CAM,
	PERI_UART0,
	PERI_UART1,
	PERI_UART2,
	PERI_UART3,
	PERI_TCT,
	PERI_TCX,
	PERI_TCZ,
	PERI_DAI,
	PERI_GPSB0,
	PERI_GPSB1,
	PERI_GPSB2,
	PERI_GPSB3,
	PERI_ADC,
	PERI_SPDIF,
	PERI_RFREQ,
	PERI_SCALER,
	PERI_EHI0,
	PERI_EHI1,
	PERI_ALLPERIPERALS
};
#elif defined(_TCC83x_)
enum{
	PERI_RFREQ = 0,		//PCLKCFG0 H
	
	PERI_I2C,				//PCLKCFG1 H	 I2C

	PERI_SPIMS0,			//PCLKCFG2 H
	PERI_SPIMS1,			//PCLKCFG2 L

	PERI_UART1,			//PCLKCFG3 H
	PERI_UART0,			//PCLKCFG3 L
	

	PERI_TCT,				//PCLKCFG4 H TIMER T

	PERI_TCZ,				//PCLKCFG5 H TIMER Z
	PERI_TCX,				//PCLKCFG5 L TIMERX
	
	PERI_DAI0,				//PCLKCFG6 H DAI 
	PERI_ADC,				//PCLKCFG6 L ADC

	PERI_DAI,				//PCLKCFG7 H DCO or Divider mode

	PERI_SCALER,			//PCLKCFG8 H CIF Scaler Clock
	PERI_CAM,				//PCLKCFG8 L CIF Master Clock

	
	PERI_LCD,				//PCLKCFG9 H LCD Clock
	PERI_EHI0,				//PCLKCFG9 L HPI Clock
	
	
	PERI_UART3,			//PCLKCFG10 H		UART 3
	PERI_UART2,			//PCLKCFG10 L		UART 2
	
	PERI_SPDIF,			//PCLKCFG11 H  SPDIF

	PERI_USB11H,			//PCLKCFG12 H		USBHost

	PERI_SDMMC,				//PCLKCFG13 H		SD

	
	PERI_ALLPERIPERALS,
};
#elif defined(_TCC80x_)
enum{
	PERI_RFREQ = 0,		
	
	PERI_I2C,				

	PERI_SPIMS0,			
	PERI_SPIMS1,			

	PERI_UART0,			
	PERI_UART1,			
	PERI_UART2,			
	PERI_UART3,			
	PERI_UART4,			

	PERI_TCT,				
	PERI_TCX,				
	PERI_TCZ,				
	
	PERI_ADC,				
	PERI_DAI0,				
	PERI_DAI,				

	PERI_LCD,				
	PERI_SPDIF,			
	PERI_USB11H,			

	PERI_SDMMC,
	PERI_SDMMC1,

	PERI_C3DEC,
	PERI_EXT,

	PERI_CAN0,
	PERI_CAN1,

	PERI_GSB0,
	PERI_GSB1,
	PERI_GSB2,
	PERI_GSB3,

	PERI_ALLPERIPERALS,
};
#endif

//Reset and BUS 
#if defined(_TCC79x_)
enum{
	RB_USB11HOST=0,
	RB_USB20FUNCTION,
	RB_LCD,
	RB_CAMERA,	
	RB_HDD,

	RB_DMA,
	RB_SDMMC,	
	RB_MSTICK,
	RB_I2C,
	RB_NANDFLASH,
	
	RB_EHI0,		
	RB_UART0,
	RB_UART1,
	RB_GPSB0,
	RB_DAI,
	
	RB_UART2,
	RB_ECC,
	RB_SPDIF,
	RB_GPSB1,
	RB_SUBPERI,
	
	RB_GRAPHIC2D,
	RB_RTC,
	RB_EXTMEMCTRL,
	RB_SUBPORCESSOR,		
	RB_ADC,
	
	RB_VIDEOCONHW,
	RB_TIMER,
	RB_MAINPROCESSOR,
	RB_VECTORINTCON,
	RB_M2MSCALER,
	
	RB_MAILBOX,
	RB_MAINBUSCOMPO,
	RB_UART3,
	RB_SRAMINTER,
	RB_GPSB2,
	
	RB_GPSB3,
	RB_EHI1,	
	RB_VIDEOENC,
	
	RB_ALLPERIPERALS,
};
#elif defined(_TCC83x_)
enum{
	RB_DAI = 0,
	RB_INTERRUPT,
	RB_TIMER,
	RB_GPIO,
	RB_USB20FUNCTION,
	RB_UART0,
	RB_UART2,
	RB_I2C,
	RB_UART3,
	RB_ECC,
	RB_ADC,
	RB_USB11HOST,
	RB_GDMA0,
	RB_LCD,
	RB_JPEG,
	RB_RTC,
	RB_NANDFLASH,
	RB_SDMMC,
	RB_GRAPHIC2D,
	RB_HOSTINTERCACE,
	RB_HDD,
	RB_CAMERA,
	RB_GDMA1,
	RB_UART1,
	RB_SPIMS0,
	RB_M2MSCALER,
	RB_MAINBUSCOMPO,
	RB_EXTMEMCTRL,
	RB_INTMEMCTRL,
	RB_DTCM,
	RB_SPIMS1,
	RB_ARM, //31
	RB_BDMA, //32
	RB_ADMA,
	RB_SPDIFTx,
	
	RB_ALLPERIPERALS,
};

enum{
	PERI_LSB	= 0,
	PERI_MSB,
};


static const unsigned int PeriClockDefine[PERI_ALLPERIPERALS][2]={
	/* PERI Name, 			 MSB or LSB*/
	{PERI_RFREQ,			PERI_MSB}, //Virtual
	
	{PERI_I2C,				PERI_MSB},
	
	{PERI_SPIMS0,			PERI_MSB},
	{PERI_SPIMS1,			PERI_LSB},
	
	{PERI_UART1,			PERI_MSB},
	{PERI_UART0,			PERI_LSB}, //uart0
	
	{PERI_TCT,				PERI_MSB},
	
	{PERI_TCZ,				PERI_MSB},
	{PERI_TCX,				PERI_LSB},
	
	{PERI_DAI0,				PERI_MSB},
	{PERI_ADC,				PERI_LSB},
	
	{PERI_DAI,				PERI_MSB},
	
	{PERI_SCALER,			PERI_MSB},
	{PERI_CAM,				PERI_LSB},

	
	{PERI_LCD,				PERI_MSB},
	{PERI_EHI0,				PERI_LSB},

	{PERI_UART3,			PERI_MSB},
	{PERI_UART2,			PERI_LSB},

	
	{PERI_SPDIF,			PERI_MSB},
	
	{PERI_USB11H,			PERI_MSB},
	
	{PERI_SDMMC,				PERI_MSB}
	
};

#elif defined(_TCC80x_)
enum{
	RB_DAI = 0,
	RB_INTERRUPT,
	RB_TIMER,
	RB_GPIO,
	RB_USB20FUNCTION,
	RB_UART0,
	RB_UART2,
	RB_I2C,
	RB_UART3,
	RB_ECC,
	RB_ADC,
	RB_USB11HOST,
	RB_GDMA0,
	RB_LCD,
	RB_RESERVED0,//	RB_JPEG,
	RB_RTC,
	RB_NANDFLASH,
	RB_SDMMC,
	RB_GRAPHIC2D,
	RB_RESERVED1,//	RB_HOSTINTERCACE,
	RB_RESERVED2,//	RB_HDD,
	RB_RESERVED3,//	RB_CAMERA,
	RB_GDMA1,
	RB_UART1,
	RB_SPIMS0,
	RB_M2MSCALER,
	RB_MAINBUSCOMPO, //AHB
	RB_EXTMEMCTRL, // External Memory Controller SDRAM 
	RB_INTMEMCTRL,
	RB_DTCM,
	RB_SPIMS1,
	RB_ARM, //31 CPU
	RB_BDMA, //32
	RB_ADMA,
	RB_SPDIFTx,
	RB_SCFG,
	RB_CID,
	RB_SDMMC1,
	RB_UART4,
	RB_DAI1,
	RB_ADMA1,
	RB_C3DEC,
	RB_CAN0,
	RB_CAN1,
	RB_GPS,
	RB_GSB0,
	RB_GSB1,
	RB_GSB2,
	RB_GSB3,
	RB_GDMA2,
	RB_GDMA3,
	RB_DDRC,
	RB_RB_USB11HOST1,

	RB_ALLPERIPERALS,
};

#endif

#endif /*__TCA_CKCSTR_H__*/


