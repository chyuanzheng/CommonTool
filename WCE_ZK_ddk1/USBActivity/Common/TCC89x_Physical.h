/****************************************************************************
 *   FileName    : TCC89x_Physical.h
 *   Description : 
 ****************************************************************************
 *
 *   TCC Version 1.0
 *   Copyright (c) Telechips, Inc.
 *   ALL RIGHTS RESERVED
 *
 ****************************************************************************/

/****************************************************************************

  Revision History

 ****************************************************************************

 ****************************************************************************/

/************************************************************************
*	TCC89x Internal Register Definition File
************************************************************************/
#ifndef	__TCC89x_H__
#define	__TCC89x_H__


/************************************************************************
*	Bit Field Definition
************************************************************************/
#define	Hw37									(1LL << 37)
#define	Hw36									(1LL << 36)
#define	Hw35									(1LL << 35)
#define	Hw34									(1LL << 34)
#define	Hw33									(1LL << 33)
#define	Hw32									(1LL << 32)
#define	Hw31									0x80000000
#define	Hw30									0x40000000
#define	Hw29									0x20000000
#define	Hw28									0x10000000
#define	Hw27									0x08000000
#define	Hw26									0x04000000
#define	Hw25									0x02000000
#define	Hw24									0x01000000
#define	Hw23									0x00800000
#define	Hw22									0x00400000
#define	Hw21									0x00200000
#define	Hw20									0x00100000
#define	Hw19									0x00080000
#define	Hw18									0x00040000
#define	Hw17									0x00020000
#define	Hw16									0x00010000
#define	Hw15									0x00008000
#define	Hw14									0x00004000
#define	Hw13									0x00002000
#define	Hw12									0x00001000
#define	Hw11									0x00000800
#define	Hw10									0x00000400
#define	Hw9										0x00000200
#define	Hw8										0x00000100
#define	Hw7										0x00000080
#define	Hw6										0x00000040
#define	Hw5										0x00000020
#define	Hw4										0x00000010
#define	Hw3										0x00000008
#define	Hw2										0x00000004
#define	Hw1										0x00000002
#define	Hw0										0x00000001
#define	HwZERO									0x00000000

/*******************************************************************************
*	 TCC8900_DataSheet_PART 2 SMU & PMU_V0.00 Dec.11 2008
********************************************************************************/
/************************************************************************
*	1. Clock Controller Register Define			(Base Addr = 0xF0400000) // R/W
************************************************************************/
//---------------------------------------------------------------------------------------------
//31  | 30  | 29  | 28  | 27  | 26  | 25  | 24  | 23  | 22  | 21  | 20  | 19  | 18  | 17  | 16 |
//  												 		|CFGEN|MODE | NCKOE/DPRD           |
//15  | 14  | 13  | 12  | 11  | 10  |  9  |  8  |  7  |   6 |   5 |   4 |   3 |   2 |   1 |  0 |
//   NCKOE/DMIN  		|		NCKOE/DMAX      |		  NCKOE/DCDIV   |     |	    CKSEL      |
//----------------------------------------------------------------------------------------------   
#define HwCLK_BASE					*(volatile unsigned long *)0xF0400000
#define HwCKC						((PCKC)&HwCLK_BASE)

/************************************************************************
*	2. Vectored Priority Interrupt Controller Register Map(Base Addr = 0xF0401000)
************************************************************************/
#define	HwPIC_BASE					*(volatile unsigned long *)0xF0401000
#define	HwVIC_BASE					*(volatile unsigned long *)0xF0401200
#define HwPIC						((PPIC)&HwPIC_BASE)
#define HwVIC						((PVIC)&HwVIC_BASE)


// Interrupt Enable 0
#define	HwINT0_EHI0					Hw31										// R/W, External Host Interface0 Interrupt Enable
#define	HwINT0_ECC					Hw30										// R/W, ECC Interrupt Enable 
#define	HwINT0_DMA					Hw29										// R/W, DMA Controller Interrupt Enable
#define	HwINT0_TSADC				Hw28										// R/W, TSADC Interrupt Enable
#define	HwINT0_G2D					Hw27										// R/W, Graphic Engine 2D Hardware Interrupt Enable
#define	HwINT0_3DMMU				Hw26										// R/W, 3D MMU Interrupt Enable
#define	HwINT0_3DGP					Hw25										// R/W, 3D Geometary Interrupt Enable
#define	HwINT0_3DPP					Hw24										// R/W, 3D Pixel Processor Interrupt Enable
#define	HwINT0_VCDC					Hw23										// R/W, Video CODEC Interrupt Enable
#define	HwINT0_JPGD					Hw22										// R/W, JPEG Decoder Interrupt Enable
#define	HwINT0_JPGE					Hw21										// R/W, JPEG Encoder Interrupt Enable
#define	HwINT0_VIPET				Hw20										// R/W, VIPET Controller Interrupt Enable
#define	HwINT0_LCD1					Hw19										// R/W, LCD Controller1 Interrupt Enable
#define	HwINT0_LCD0					Hw18										// R/W, LCD Controller0 Interrupt Enable
#define	HwINT0_CAM					Hw17										// R/W, Camera Interrupt Enable
#define	HwINT0_SC1					Hw16										// R/W, Mem-to-Mem Scaler1 Interrupt Enable
#define	HwINT0_SC0					Hw15										// R/W, Mem-to-Mem Scaler0 Interrupt Enable
#define	HwINT0_EI11					Hw14										// R/W, External Interrupt11 Enable
#define	HwINT0_EI10					Hw13										// R/W, External Interrupt10 Enable
#define	HwINT0_EI9					Hw12										// R/W, External Interrupt9 Enable
#define	HwINT0_EI8					Hw11										// R/W, External Interrupt8 Enable
#define	HwINT0_EI7					Hw10										// R/W, External Interrupt7 Enable
#define	HwINT0_EI6					Hw9											// R/W, External Interrupt6 Enable
#define	HwINT0_EI5					Hw8											// R/W, External Interrupt5 Enable
#define	HwINT0_EI4					Hw7											// R/W, External Interrupt4 Enable
#define	HwINT0_EI3					Hw6											// R/W, External Interrupt3 Enable
#define	HwINT0_EI2					Hw5											// R/W, External Interrupt2 Enable
#define	HwINT0_EI1					Hw4											// R/W, External Interrupt1 Enable
#define	HwINT0_EI0					Hw3											// R/W, External Interrupt0 Enable
#define	HwINT0_SMUI2C				Hw2											// R/W, SMU_I2C Interrupt Enable
#define	HwINT0_TC1					Hw1											// R/W, Timer1 Interrupt Enable
#define	HwINT0_TC0					Hw0											// R/W, Timer0 Interrupt Enable

// Interrupt Enable 1
#define	HwINT1_AEIRQ				Hw31										// R/W, Not maskable error ARM DMA interrupt enable
#define	HwINT1_ASIRQ				Hw30										// R/W, Secure ARM DMA select interrupt enable
#define	HwINT1_AIRQ					Hw29										// R/W, Non secure ARM DMA interrupt enable
#define	HwINT1_APMU					Hw28										// R/W, ARM System Metrics interrupt enable
#define	HwINT1_AUDIO				Hw27										// R/W, AUDIO interrupt enable
#define	HwINT1_ADMA					Hw26										// R/W, AUDIO DMA interrupt enable
#define	HwINT1_DAITX				Hw25										// R/W, DAI transmit interrupt enable
#define	HwINT1_DAIRX				Hw24										// R/W, DAI receive interrupt enable
#define	HwINT1_CDRX					Hw23										// R/W, CDIF receive interrupt enable
#define	HwINT1_TSIF1				Hw22										// R/W, TS interface 1 interrupt enable
#define	HwINT1_TSIF0				Hw21										// R/W, TS interface 0 interrupt enable
#define	HwINT1_GPS2					Hw20										// R/W, GPS AGPS interrupt enable
#define	HwINT1_GPS1					Hw19										// R/W, GPS TCXO expired interrupt enable
#define	HwINT1_GPS0					Hw18										// R/W, GPS RTC expired interrupt enable
#define	HwINT1_NotUsed				Hw17										// R/W, Reserved
#define	HwINT1_UOTG					Hw16										// R/W, USB 2.0 OTG interrupt enable
#define	HwINT1_UART					Hw15										// R/W, UART interrupt enable
#define	HwINT1_SPDTX				Hw14										// R/W, SPDIF transmitter interrupt enable
#define	HwINT1_SD1					Hw13										// R/W, SD/MMC 1 interrupt enable
#define	HwINT1_SD0					Hw12										// R/W, SD/MMC 0 interrupt enable
#define	HwINT1_RTC					Hw11										// R/W, RTC interrupt enable
#define	HwINT1_RMT					Hw10										// R/W, Remote Control interrupt enable
#define	HwINT1_NFC					Hw9											// R/W, Nand flash controller interrupt enable
#define	HwINT1_MS					Hw8											// R/W, Memory Stick interrupt enable
#define	HwINT1_MPEFEC				Hw7											// R/W, MPEFEC interrupt enable
#define	HwINT1_I2C					Hw6											// R/W, I2C interrupt enable
#define	HwINT1_HDD					Hw5											// R/W, HDD controller interrupt enable
#define	HwINT1_GPSB					Hw4											// R/W, GPSB Interrupt Enable
#define	HwINT1_NotUsed1				Hw3											// R/W, Reserved
#define	HwINT1_HDMI					Hw2											// R/W, HDMI interrupt enable
#define	HwINT1_NotUsed2				Hw1											// R/W, Reserved
#define	HwINT1_EHI1					Hw0											// R/W, External Host Interface1 Interrupt Enable

#define	HwALLMSK_FIQ				Hw1										// FIQ mask register
#define	HwALLMSK_IRQ				Hw0										// IRQ mask register
	
/***********************************************************************
*	3. Timer/Counter Register Map (Base Address = 0xF0403000) 
************************************************************************/
#define	HwTMR_BASE					*(volatile unsigned long *)0xF0403000	// Timer/Counter Base Register
#define HwTMR						((PTIMER)&HwTMR_BASE)

/***********************************************************************
*	4. PMU(POWER MANAGEMENT UNIT) Register Map (Base Address = 0xF0404000) 
************************************************************************/
#define	HwPMU_BASE  				*(volatile unsigned long *)0xF0404000 	//R/W   PMU Control Register 

/*******************************************************************************
*	5. SMUI2C Controller Register Define   (Base Addr = 0xF0405000)
********************************************************************************/
#define HwSMU_I2CMASTER0_BASE     	*(volatile unsigned long *)0xF0405000
#define HwSMU_I2CMASTER1_BASE     	*(volatile unsigned long *)0xF0405040
#define HwSMU_I2CICLK_BASE     		*(volatile unsigned long *)0xF0405080	//I2C_SCL divider Regist
#define HwI2CSTATUS_BASE            *(volatile unsigned long *)0xF05300C0

/*******************************************************************************
*	 TCC8900_DataSheet_PART 3 GPIO_V0.00 Dec.11 2008
********************************************************************************/
/************************************************************************
*	1. GPIO Register Map (Base Address = 0xF0102000) 
************************************************************************/
#define	HwGPIO_BASE  				*(volatile unsigned long *)0xF0102000  	// 
#define	HwGPIOA_BASE  				*(volatile unsigned long *)0xF0102000  	// 
#define	HwGPIOB_BASE  				*(volatile unsigned long *)0xF0102040  	// 
#define	HwGPIOC_BASE  				*(volatile unsigned long *)0xF0102080  	// 
#define	HwGPIOD_BASE  				*(volatile unsigned long *)0xF01020C0  	// 
#define	HwGPIOE_BASE  				*(volatile unsigned long *)0xF0102100  	// 
#define	HwGPIOF_BASE  				*(volatile unsigned long *)0xF0102140  	// 
#define	HwEINTSEL_BASE  			*(volatile unsigned long *)0xF0102180  	// 
#define HwGPIO						((PGPIO)&HwGPIO_BASE)
#define HwGPIOA						((PGPION)&HwGPIOA_BASE)
#define HwGPIOB						((PGPION)&HwGPIOB_BASE)
#define HwGPIOC						((PGPION)&HwGPIOC_BASE)
#define HwGPIOD						((PGPION)&HwGPIOD_BASE)
#define HwGPIOE						((PGPION)&HwGPIOE_BASE)
#define HwGPIOF						((PGPION)&HwGPIOF_BASE)
#define HwEINTSEL					((PGPIOINT)&HwEINTSEL_BASE)

#define	HwPORTCFG_GPFN0(X)			((X)<<0)	// 0~3
#define HwPORTCFG_GPFN0_MASK		(0xF)		// HwPORTCFG_GPFN0(15)
#define	HwPORTCFG_GPFN1(X)			((X)<<4)	// 4~7
#define HwPORTCFG_GPFN1_MASK		(0xF<<4)	// HwPORTCFG_GPFN1(15)
#define	HwPORTCFG_GPFN2(X)			((X)<<8)	// 8~11
#define HwPORTCFG_GPFN2_MASK		(0xF<<8)	// HwPORTCFG_GPFN2(15)
#define	HwPORTCFG_GPFN3(X)			((X)<<12)	// 12~15
#define HwPORTCFG_GPFN3_MASK		(0xF<<12)	// HwPORTCFG_GPFN3(15)
#define	HwPORTCFG_GPFN4(X)			((X)<<16)	// 16~19
#define HwPORTCFG_GPFN4_MASK		(0xF<<16)	// HwPORTCFG_GPFN4(15)
#define	HwPORTCFG_GPFN5(X)			((X)<<20)	// 20~23
#define HwPORTCFG_GPFN5_MASK		(0xF<<20)	// HwPORTCFG_GPFN5(15)
#define	HwPORTCFG_GPFN6(X)			((X)<<24)	// 24~27
#define HwPORTCFG_GPFN6_MASK		(0xF<<24)	// HwPORTCFG_GPFN6(15)
#define	HwPORTCFG_GPFN7(X)			((X)<<28)	// 28~31
#define HwPORTCFG_GPFN7_MASK		(0xF<<28)	// HwPORTCFG_GPFN7(15)

/*******************************************************************************
*	 TCC8900_DataSheet_PART 4 CORE & MEMORY BUS_V0.00 Dec.11 2008
********************************************************************************/
/************************************************************************
*	3. DRAM CONTROLLER Register Map (Base Address = 0xF0301000) 
************************************************************************/
#define	HwDRAM_BASE  				*(volatile unsigned long *)0xF0301000  	//
#define	HwDRAMM0_BASE  				*(volatile unsigned long *)0xF0301000  	//
#define	HwDRAMM1_BASE  				*(volatile unsigned long *)0xF0302000  	//
#define	HwDRAMMISC_BASE  			*(volatile unsigned long *)0xF0303000  	//
#define	HwDRAMPHY_BASE  			*(volatile unsigned long *)0xF0304400  	//
#define	HwDRAMMEMBUS_BASE  			*(volatile unsigned long *)0xF0305004  	//

/************************************************************************
*	4-1. MISC CORE BUS CONFIGURATION REGISTERS				(Base Addr = 0xF0101000)
************************************************************************/
#define	HwCORECFG_BASE				*(volatile unsigned long *)0xF0101000	
       
/************************************************************************
*	4-2. Virtual MMU Table  Register Define	(Base Addr = 0xF7000000)
************************************************************************/
#define	HwVMT_BASE					*(volatile unsigned long *)0x20000000	// VMT Base Regiseter
#define	HwREGION_BASE				*(volatile unsigned long *)0xF0600000	// R/W, Configuration Register for Region 0


/*******************************************************************************
*	 TCC8900_DataSheet_PART 5 IO BUS_V0.00 Dec.11 2008
********************************************************************************/
/*******************************************************************************
*	 4. Memory Stick Host Controller Register Define   (Base Addr = 0xF0590000)
********************************************************************************/
#define HwSMSHC_BASE                *(volatile unsigned long *)0xF0590000
#define HwPORTCFG_BASE              *(volatile unsigned long *)0xF05F1000

/********************************************************************************
*	 5. SD/SDIO/MMC/CE-ATA Host Controller Register Define   (Base Addr = 0xF05A0000)
********************************************************************************/
#define HwSDCORE0SLOT0_BASE         *(volatile unsigned long *)0xF05A0000	// Core 0 Slot 0
#define HwSDCORE0SLOT1_BASE         *(volatile unsigned long *)0xF05A0100	// Core 0 Slot 1
#define HwSDCORE1SLOT2_BASE         *(volatile unsigned long *)0xF05A0200	// Core 1 Slot 2
#define HwSDCORE1SLOT3_BASE         *(volatile unsigned long *)0xF05A0300	// Core 1 Slot 3

// Channel Control Register
#define HwSDCHCTRL_BASE             *(volatile unsigned long *)0xF05A0800 // R/W 0x0000 SD/MMC port control register

/*******************************************************************************
*	 6. NAND Flash Controller(NFC) Register Define   (Base Addr = 0xF05B0000)
********************************************************************************/
#define HwNFC_BASE                  *(volatile unsigned long *)0xF05B0000
#define HwNFC						((PNFC)&HwNFC_BASE)

// NFC Control Register
#define	HwNFC_CTRL_RDYIEN_EN		Hw31							// Nand Flash Ready Interrupt Enable
#define	HwNFC_CTRL_RDYIEN_DIS		~Hw31							// Nand Flash Ready Interrupt Disable
#define	HwNFC_CTRL_PROGIEN_EN		Hw30							// Nand Flash Program Interrupt Enable 
#define	HwNFC_CTRL_PROGIEN_DIS		~Hw30							// Nand Flash Program Interrupt Disable
#define	HwNFC_CTRL_READIEN_EN		Hw29							// Nand Flash Read Interrupt Enable
#define	HwNFC_CTRL_READIEN_DIS		~Hw29							// Nand Flash Read Interrupt Disable
#define	HwNFC_CTRL_DEN_EN			Hw28							// Nand Flash DMA Request Enable
#define	HwNFC_CTRL_DEN_DIS			~Hw28							// Nand Flash DMA Request Disable
#define	HwNFC_CTRL_FS_RDY			Hw27							// FIFO status is Ready to write and read in FIFO
#define	HwNFC_CTRL_FS_BUSY			~Hw27							// FIFO status is Busy to write and read in FIFO
#define	HwNFC_CTRL_BW_16			Hw26							// Bus width = 8bit
#define	HwNFC_CTRL_BW_8				HwZERO							// Bus width = 16bit
#define	HwNFC_CTRL_CS3SEL_1			Hw25							// Nand Flash nCS3 is High (Disabled)
#define	HwNFC_CTRL_CS3SEL_0			HwZERO							// Nand Flash nCS3 is Low (Enabled)
#define	HwNFC_CTRL_CS2SEL_1			Hw24							// Nand Flash nCS2 is High (Disabled)
#define	HwNFC_CTRL_CS2SEL_0			HwZERO							// Nand Flash nCS2 is Low (Enabled)
#define	HwNFC_CTRL_CS1SEL_1			Hw23							// Nand Flash nCS1 is High (Disabled)
#define	HwNFC_CTRL_CS1SEL_0			HwZERO							// Nand Flash nCS1 is Low (Enabled)
#define	HwNFC_CTRL_CS0SEL_1			Hw22							// Nand Flash nCS0 is High (Disabled)
#define	HwNFC_CTRL_CS0SEL_0			HwZERO							// Nand Flash nCS0 is Low (Enabled)
#define	HwNFC_CTRL_CFG_nCS3			HwNFC_CTRL_CS3SEL_1
#define	HwNFC_CTRL_CFG_nCS2			HwNFC_CTRL_CS2SEL_1
#define	HwNFC_CTRL_CFG_nCS1			HwNFC_CTRL_CS1SEL_1
#define	HwNFC_CTRL_CFG_nCS0			HwNFC_CTRL_CS0SEL_1
#define	HwNFC_CTRL_CSnSEL(X)		((X)*Hw22)						// Nand Flash nCS[3:0] Set
#define	HwNFC_CTRL_CFG_NOACT		HwNFC_CTRL_CSnSEL(15)
#define	HwNFC_CTRL_RDY_RDY			Hw21							// External Nand Flash Controller is Ready
#define	HwNFC_CTRL_RDY_BUSY			~Hw21							// External Nand Flash Controller is Busy
#define	HwNFC_CTRL_BSIZE(X)			((X)*Hw19)
#define	HwNFC_CTRL_BSIZE_1			HwNFC_CTRL_BSIZE(0)				// 1Read/Write
#define	HwNFC_CTRL_BSIZE_2			HwNFC_CTRL_BSIZE(1)				// 2Read/Write
#define	HwNFC_CTRL_BSIZE_4			HwNFC_CTRL_BSIZE(2)				// 4Read/Write
#define	HwNFC_CTRL_BSIZE_8			HwNFC_CTRL_BSIZE(3)				// 8Read/Write
#define	HwNFC_CTRL_BSIZE_MASK		HwNFC_CTRL_BSIZE(3)
#define	HwNFC_CTRL_PSIZE(X)			((X)*Hw16)
#define	HwNFC_CTRL_PSIZE_256		HwNFC_CTRL_PSIZE(0)				// 1 Page = 256 Half-Word
#define	HwNFC_CTRL_PSIZE_512		HwNFC_CTRL_PSIZE(1)				// 1 Page = 512 Byte
#define	HwNFC_CTRL_PSIZE_1024		HwNFC_CTRL_PSIZE(2)				// 1 Page = 1024 Half-Word
#define	HwNFC_CTRL_PSIZE_2048		HwNFC_CTRL_PSIZE(3)				// 1 Page = 2048 Byte
#define	HwNFC_CTRL_PSIZE_4096		HwNFC_CTRL_PSIZE(4)				// 1 Page = 4096 Byte
#define	HwNFC_CTRL_PSIZE_MASK		HwNFC_CTRL_PSIZE(7)
#define	HwNFC_CTRL_MASK_EN			Hw15							// Address/Command Mask Enable
#define	HwNFC_CTRL_CADDR			Hw12							// Number of Address Cycle
#define	HwNFC_CTRL_bSTP(X)			((X)*Hw8)						// Number of Base cycle for Setup Time
#define	HwNFC_CTRL_bSTP_MASK		HwNFC_CTRL_bSTP(15)
#define	HwNFC_CTRL_bPW(X)			((X)*Hw4)						// Number of Base cycle for Pulse Width
#define	HwNFC_CTRL_bPW_MASK			HwNFC_CTRL_bPW(15)
#define	HwNFC_CTRL_bHLD(X)			((X)*Hw0)						// Number of Base cycle for Hold Time
#define	HwNFC_CTRL_bHLD_MASK		HwNFC_CTRL_bHLD(15)

#define	HwNFC_IREQ_FLAG2			Hw6						//
#define	HwNFC_IREQ_FLAG1			Hw5						//
#define	HwNFC_IREQ_FLAG0			Hw4						//
#define	HwNFC_IREQ_IRQ2				Hw2						// Ready Interrupt
#define	HwNFC_IREQ_IRQ1				Hw1						// Program Interrupt
#define	HwNFC_IREQ_IRQ0				Hw0						// Reading Interrupt

/*******************************************************************************
*	 7. Static Memory Controller(SMC) Register Define   (Base Addr = 0xF05F0000)
********************************************************************************/
#define HwSMC_BASE                  *(volatile unsigned long *)0xF05F0000
#define HwSMC_STATUS                *(volatile unsigned long *)0xF05F0000 // R/W Unknown Status Register
#define HwSMC_CSNCFG0               *(volatile unsigned long *)0xF05F0020 // R 0x4b40_3183 External Chip Select0 Config Register
#define HwSMC_CSNCFG1               *(volatile unsigned long *)0xF05F0024 // R/W 0x4b40_1104 External Chip Select1 Config Register
#define HwSMC_CSNCFG2               *(volatile unsigned long *)0xF05F0028 // W 0x4b40_4082 External Chip Select2 Config Register
#define HwSMC_CSNCFG3               *(volatile unsigned long *)0xF05F002C // R/W 0x4b40_20C5 External Chip Select3 Config. Register
#define HwSMC_CSNOFFSET             *(volatile unsigned long *)0xF05F0030 // R/W 0x0 Wapping Address Mode OFFSET Register
#define HwSMC_INDIRADDR             *(volatile unsigned long *)0xF05F0034 // R/W 0x0 Indirect Address

/*******************************************************************************
*	 8. External Device Interface (EDI) Register Define   (Base Addr = 0xF05F6000)
********************************************************************************/
#define HwEDI_BASE                  *(volatile unsigned long *)0xF05F6000
#define HwEDI						((PEDI)&HwEDI_BASE)

/*******************************************************************************
*	 9. IDE Controller Register Define   (Base Addr = 0xF0520000)
********************************************************************************/
#define HwIDE_BASE                  *(volatile unsigned long *)0xF0520000

/*******************************************************************************
*	 10. SATA Interface Register Define   (Base Addr = 0xF0560000)
********************************************************************************/
#define HwSATA_BASE                 *(volatile unsigned long *)0xF0560000
//SCR5-SCR15 0x38-0x60 32 See description 0x0 Reserved for SATA Dependencies: Reads to these locations return zeros; writes have no effect

/*******************************************************************************
*	 11-1. Audio DMA Controller Register Define   (Base Addr = 0xF0533000)
********************************************************************************/
#define HwADMA_BASE                 *(volatile unsigned long *)0xF0533000

/*******************************************************************************
*	 11-2. DAI Register Define   (Base Addr = 0xF0534000)
********************************************************************************/
#define HwADMA_DAIBASE              *(volatile unsigned long *)0xF0534000

/*******************************************************************************
*	 11-3. CDIF Register Define   (Base Addr = 0xF0534000)
********************************************************************************/
#define HwADMA_CDIFBASE             *(volatile unsigned long *)0xF0534080

/*******************************************************************************
*	 11-4. SPDIF Register Define   (Base Addr = 0xF0535000/0xF0535800)
********************************************************************************/
#define HwADMA_SPDIFTXBASE          *(volatile unsigned long *)0xF0535000

/*******************************************************************************
*	 12-1. DAI Register Define   (Base Addr = 0xF0537000
********************************************************************************/
#define HwDAI_BASE                  *(volatile unsigned long *)0xF0537000

/*******************************************************************************
*	 12-2. CDIF Register Define   (Base Addr = 0xF0537000
********************************************************************************/
#define HwCDIF_BASE                 *(volatile unsigned long *)0xF0537080

/*******************************************************************************
*	 13. SPDIF Register Define   (Base Addr = 0xF0538000)
********************************************************************************/
#define HwSPDIF_BASE                *(volatile unsigned long *)0xF0538000

/*******************************************************************************
*	 14-1. USB1.1 HOST Controller & Transceiver       (Base Addr = 0xF0500000)
********************************************************************************/
#define HwUSBHOST_BASE              *(volatile unsigned long *)0xF0500000

/*******************************************************************************
*	 14-2 USB1.1 HOST Configuration Register        (Base Addr = 0xF05F5000)
********************************************************************************/
#define HwUSBHOSTCFG_BASE           *(volatile unsigned long *)0xF05F5000

/*******************************************************************************
*	 15-1. USB2.0 OTG Controller Define   (Base Addr = 0xF0550000)
********************************************************************************/
#define HwUSB20OTG_BASE             *(volatile unsigned long *)0xF0550000

/*******************************************************************************
*	 15-2. USB OTG Configuration Register Define   (Base Addr = 0xF05F5000)
********************************************************************************/
#define HwUSBOTGCFG_BASE            *(volatile unsigned long *)0xF05F5000

/*******************************************************************************
*	 15-3. USB PHY Configuration Register Define   (Base Addr = 0xF05F5028)
********************************************************************************/
#define HwUSBPHYCFG_BASE            *(volatile unsigned long *)0xF05F5028

/*******************************************************************************
*	 16. External Host Interface Register Define   (Base Addr = 0xF0570000/0xF0580000)
********************************************************************************/
#define HwEHICS0_BASE               *(volatile unsigned long *)0xF0570000
#define HwEHICS1_BASE               *(volatile unsigned long *)0xF0580000

/*******************************************************************************
*	 17. General Purpose Serial Bus (GPSB) Register Define   (Base Addr = 0xF0538000)
********************************************************************************/
#if 0
#define HwGPSBCH0_BASE              *(volatile unsigned long *)0xF0057000
#define HwGPSBCH1_BASE              *(volatile unsigned long *)0xF0057100
#define HwGPSBCH2_BASE              *(volatile unsigned long *)0xF0057200
#define HwGPSBCH3_BASE              *(volatile unsigned long *)0xF0057300
#define HwGPSBCH4_BASE              *(volatile unsigned long *)0xF0057400
#define HwGPSBCH5_BASE              *(volatile unsigned long *)0xF0057500
#define HwGPSBPORTCFG_BASE          *(volatile unsigned long *)0xF0057800
#define HwGPSBPIDTABLE_BASE         *(volatile unsigned long *)0xF0057F00

#define	HwGPSB_PIDT(X)				*(volatile unsigned long *)(0xF0057F00+(X)*4)	// R/W, PID Table Register
#define	HwGPSB_PIDT_CH2				Hw31											// Channel 2 enable
#define	HwGPSB_PIDT_CH1				Hw30											// Channel 1 enable
#define	HwGPSB_PIDT_CH0				Hw29											// Channel 0 enable
#else
#define HwGPSBCH0_BASE              *(volatile unsigned long *)0xF0536000
#define HwGPSBCH1_BASE              *(volatile unsigned long *)0xF0536100
#define HwGPSBCH2_BASE              *(volatile unsigned long *)0xF0536200
#define HwGPSBCH3_BASE              *(volatile unsigned long *)0xF0536300
#define HwGPSBCH4_BASE              *(volatile unsigned long *)0xF0536400
#define HwGPSBCH5_BASE              *(volatile unsigned long *)0xF0536500
#define HwGPSBPORTCFG_BASE          *(volatile unsigned long *)0xF0536800
#define HwGPSBPIDTABLE_BASE         *(volatile unsigned long *)0xF0536F00

#define	HwGPSB_PIDT(X)				*(volatile unsigned long *)(0xF0536F00+(X)*4)	// R/W, PID Table Register
#define	HwGPSB_PIDT_CH2				Hw31											// Channel 2 enable
#define	HwGPSB_PIDT_CH1				Hw30											// Channel 1 enable
#define	HwGPSB_PIDT_CH0				Hw29											// Channel 0 enable
#endif

/*******************************************************************************
*	 18. The Transport Stream Interface (TSIF) Register Define   (Base Addr = 0xF0538000)
********************************************************************************/
#define HwTSIF_BASE                 *(volatile unsigned long *)0xF053B000
#define HwTSIFPORTSEL_BASE          *(volatile unsigned long *)0xF053B800

/*******************************************************************************
*	 19. GPS Interface Register Define   (Base Addr = )
********************************************************************************/


/*******************************************************************************
*	 20. Remote Control Interface Register Define   (Base Addr = 0xF05F3000)
********************************************************************************/
#define HwREMOCON_BASE             *(volatile unsigned long *)0xF05F3000


/*******************************************************************************
*	 21. I2C Controller Register Define   (Base Addr = 0xF0530000)
********************************************************************************/
#define HwI2CMASTER0_BASE          *(volatile unsigned long *)0xF0530000
#define HwI2CMASTER1_BASE          *(volatile unsigned long *)0xF0530040
#define HwI2CSLAVE_BASE            *(volatile unsigned long *)0xF0530080
#define HwI2CSTATUS_BASE           *(volatile unsigned long *)0xF05300C0

#define HwI2CMASTER0			((PSMUI2CMASTER)&HwI2CMASTER0_BASE)
#define HwI2CMASTER1			((PSMUI2CMASTER)&HwI2CMASTER1_BASE)

/*******************************************************************************
*	 22. UART Controller Register Define   (Base Addr = 0xF0538000)
********************************************************************************/
#define HwUARTCH0_BASE             *(volatile unsigned long *)0xF0532000
#define HwUARTCH1_BASE             *(volatile unsigned long *)0xF0532100
#define HwUARTCH2_BASE             *(volatile unsigned long *)0xF0532200
#define HwUARTCH3_BASE             *(volatile unsigned long *)0xF0532300
#define HwUARTCH4_BASE             *(volatile unsigned long *)0xF0532400
#define HwUARTCH5_BASE             *(volatile unsigned long *)0xF0532500
#define HwUARTPORTMUX_BASE         *(volatile unsigned long *)0xF0532600

/*******************************************************************************
*	 23. CAN Controller Register Define   (Base Addr = 0xF0531000)
********************************************************************************/
#define HwCAN_BASE                 *(volatile unsigned long *)0xF0531000

/*******************************************************************************
*	 24. DMA Controller Register Define   (Base Addr = 0xF0540000)
********************************************************************************/
#define HwGDMA0_BASE               *(volatile unsigned long *)0xF0540000
#define HwGDMA1_BASE               *(volatile unsigned long *)0xF0540100
#define HwGDMA2_BASE               *(volatile unsigned long *)0xF0540200
#define HwGDMA3_BASE               *(volatile unsigned long *)0xF0540300

/*******************************************************************************
*	 25. Real Time Clock(RTC) Register Define   (Base Addr = 0xF05F2000)
********************************************************************************/
#define HwRTC_BASE                 *(volatile unsigned long *)0xF05F2000

/*******************************************************************************
*	 26. TouchScreen ADC (TSADC) Register Define   (Base Addr = 0xF05F4000)
********************************************************************************/
#define HwTSADC_BASE               *(volatile unsigned long *)0xF05F4000

/*******************************************************************************
*	 27. Error Correction Code Register Define   (Base Addr = 0xF0539000)
********************************************************************************/
#define HwECC_BASE                 *(volatile unsigned long *)0xF0539000

// ECC Control
#define	HwECC_CTRL_IEN_MECC16_EN	Hw20										// MLC ECC16 Decoding Interrupt Enable
#define	HwECC_CTRL_IEN_MECC16_DIS	~Hw20										// MLC ECC16 Decoding Interrupt Disable
#define	HwECC_CTRL_IEN_MECC14_EN	Hw19										// MLC ECC14 Decoding Interrupt Enable
#define	HwECC_CTRL_IEN_MECC14_DIS	~Hw19										// MLC ECC14 Decoding Interrupt Disable
#define	HwECC_CTRL_IEN_MECC12_EN	Hw18										// MLC ECC12 Decoding Interrupt Enable
#define	HwECC_CTRL_IEN_MECC12_DIS	~Hw18										// MLC ECC12 Decoding Interrupt Disable
#define	HwECC_CTRL_IEN_MECC8_EN		Hw17										// MLC ECC8 Decoding Interrupt Enable
#define	HwECC_CTRL_IEN_MECC8_DIS	~Hw17										// MLC ECC8 Decoding Interrupt Disable
#define	HwECC_CTRL_IEN_MECC4_EN		Hw16										// MLC ECC4 Decoding Interrupt Enable
#define	HwECC_CTRL_IEN_MECC4_DIS	~Hw16										// MLC ECC4 Decoding Interrupt Disable

// ECC Disable
#define	HwECC_CTRL_EN_SLCEN			Hw2											// SLC ECC Encoding Enable
#define	HwECC_CTRL_EN_SLCDE			(Hw2|Hw0)									// SLC ECC Decoding Enable
#define	HwECC_CTRL_EN_MCL4EN		(Hw2|Hw1)									// MLC ECC4 Encoding Enable
#define	HwECC_CTRL_EN_MCL4DE		(Hw2|Hw1|Hw0)								// MLC ECC4 Decoding Enable
#define	HwECC_CTRL_EN_MCL8EN		(Hw3)										// MLC ECC8 Encoding Enable
#define	HwECC_CTRL_EN_MCL8DE		(Hw3|Hw0)									// MLC ECC8 Decoding Enable
#define	HwECC_CTRL_EN_MCL12EN		(Hw3|Hw1)									// MLC ECC12 Encoding Enable
#define	HwECC_CTRL_EN_MCL12DE		(Hw3|Hw1|Hw0)								// MLC ECC12 Decoding Enable
#define	HwECC_CTRL_EN_MCL14EN		(Hw3|Hw2)									// MLC ECC14 Encoding Enable
#define	HwECC_CTRL_EN_MCL14DE		(Hw3|Hw2|Hw0)								// MLC ECC14 Decoding Enable
#define	HwECC_CTRL_EN_MCL16EN		(Hw3|Hw2|Hw1)								// MLC ECC16 Encoding Enable
#define	HwECC_CTRL_EN_MCL16DE		(Hw3|Hw2|Hw1|Hw0)							// MLC ECC16 Decoding Enable
#define	HwECC_CTRL_EN_DIS			~(Hw3|Hw2|Hw1|Hw0)							// ECC Disable

// ECC Error Number
#define	HwERR_NUM_ERR1				Hw0											// Correctable Error(SLC), Error Occurred(MLC3), 1 Error Occurred(MLC4)
#define	HwERR_NUM_ERR2				Hw1											// 2 Error Occurred(MLC4)
#define	HwERR_NUM_ERR3				(Hw1|Hw0)									// 3 Error Occurred(MLC4)
#define	HwERR_NUM_ERR4				Hw2											// 4 Error Occurred(MLC4)
#define	HwERR_NUM_ERR5				(Hw2|Hw0)									// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR6				(Hw2|Hw1)									// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR7				(Hw2|Hw1|Hw0)								// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR8				Hw3											// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR9				(Hw3|Hw0)									// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR10				(Hw3|Hw1)									// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR11				(Hw3|Hw1|Hw0)								// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR12				(Hw3|Hw2)									// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR13				(Hw3|Hw2|Hw0)								// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR14				(Hw3|Hw2|Hw1)								// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR15				(Hw3|Hw2|Hw1|Hw0)							// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR16				Hw4											// 5 Error Occurred(MLC4)
#define	HwERR_NUM_NOERR				HwZERO										// No Error
#define	HwERR_NUM_CORIMP			(Hw1|Hw0)									// Correction Impossible(SLC, MLC4)

// ECC Interrupt Control
#define	HwECC_IREQ_SEF				Hw17										// SLC ECC Encoding Flag Register
#define	HwECC_IREQ_SDF				Hw16										// SLC ECC Decoding Flag Register
#define	HwECC_IREQ_M4EF				Hw19										// MLC ECC4 Encoding Flag Register
#define	HwECC_IREQ_M4DF				Hw18										// MLC ECC4 Decoding Flag Register
#define	HwECC_IREQ_M8EF				Hw21										// MLC ECC8 Encoding Flag Register
#define	HwECC_IREQ_M8DF				Hw20										// MLC ECC8 Decoding Flag Register
#define	HwECC_IREQ_M12EF			Hw23										// MLC ECC12 Encoding Flag Register
#define	HwECC_IREQ_M12DF			Hw22										// MLC ECC12 Decoding Flag Register
#define	HwECC_IREQ_M14EF			Hw25										// MLC ECC14 Encoding Flag Register
#define	HwECC_IREQ_M14DF			Hw24										// MLC ECC14 Decoding Flag Register
#define	HwECC_IREQ_M16EF			Hw27										// MLC ECC16 Encoding Flag Register
#define	HwECC_IREQ_M16DF			Hw26										// MLC ECC16 Decoding Flag Register
#define	HwECC_IREQ_M4DI				Hw2											// MLC ECC4 Decoding Interrupt Request Register
#define	HwECC_IREQ_M8DI				Hw4											// MLC ECC8 Decoding Interrupt Request Register
#define	HwECC_IREQ_M12DI			Hw6											// MLC ECC12 Decoding Interrupt Request Register
#define	HwECC_IREQ_M14DI			Hw8											// MLC ECC14 Decoding Interrupt Request Register
#define	HwECC_IREQ_M16DI			Hw10										// MLC ECC16 Decoding Interrupt Request Register
#define	HwECC_IREQ_CLR				(Hw27|Hw26|Hw25|Hw24|Hw23|Hw22|Hw21|Hw20|Hw19|Hw18|Hw17|Hw16|Hw10|Hw8|Hw6|Hw4|Hw2)

/*******************************************************************************
*	 28. Multi-Protocol Encapsulation Forward Error Correction (MPEFEC)
*    Register Define   (Base Addr = 0xF0510000)
********************************************************************************/
#define HwMPEFEC_BASE              *(volatile unsigned long *)0xF0510000

/*******************************************************************************
*	 29. IOBUS Configuration Register Define   (Base Addr = 0xF05F5000)
********************************************************************************/
#define HwIOBUSCFG_BASE            *(volatile unsigned long *)0xF05F5000
#define HwIOBUSCFG					((PIOBUSCFG)&HwIOBUSCFG_BASE)

// IOBUS AHB 0
#define HwIOBUSCFG_USB				Hw1											// USB2.0 OTG
#define HwIOBUSCFG_IDE				Hw2											// IDE Controller
#define HwIOBUSCFG_DMA				Hw3											// DMA Controller
#define HwIOBUSCFG_SD				Hw4											// SD/MMC Controller
#define HwIOBUSCFG_MS				Hw6											// Memory Stick Controller
#define HwIOBUSCFG_I2C				Hw7											// I2C Controller
#define HwIOBUSCFG_NFC				Hw8											// NFC Controller
#define HwIOBUSCFG_EHI0				Hw9											// External Host Interface 0
#define HwIOBUSCFG_EHI1				Hw10										// External Host Interface 1
#define HwIOBUSCFG_UART0			Hw11										// UART Controller 0
#define HwIOBUSCFG_UART1			Hw12										// UART Controller 1
#define HwIOBUSCFG_UART2			Hw13										// UART Controller 2
#define HwIOBUSCFG_UART3			Hw14										// UART Controller 3
#define HwIOBUSCFG_UART4			Hw15										// UART Controller 4
#define HwIOBUSCFG_UART5			Hw16										// UART Controller 5
#define HwIOBUSCFG_GPSB0			Hw17										// GPSB Controller 0
#define HwIOBUSCFG_GPSB1			Hw18										// GPSB Controller 1
#define HwIOBUSCFG_GPSB2			Hw19										// GPSB Controller 2
#define HwIOBUSCFG_GPSB3			Hw20										// GPSB Controller 3
#define HwIOBUSCFG_GPSB4			Hw21										// GPSB Controller 4
#define HwIOBUSCFG_GPSB5			Hw22										// GPSB Controller 5
#define HwIOBUSCFG_DAI				Hw23										// DAI/CDIF Interface
#define HwIOBUSCFG_ECC				Hw24										// ECC Calculator
#define HwIOBUSCFG_SPDIF			Hw25										// SPDIF Tx Controller
#define HwIOBUSCFG_RTC				Hw26										// RTC
#define HwIOBUSCFG_TSADC			Hw27										// TSADC Controller
#define HwIOBUSCFG_GPS				Hw28										// GPS Interface
#define HwIOBUSCFG_ADMA				Hw31										// Audio DMA Controller

// IOBUS AHB 1
#define HwIOBUSCFG_MPE				Hw0											// MPE_FEC
#define HwIOBUSCFG_TSIF				Hw1											// TSIF
#define HwIOBUSCFG_SRAM				Hw2											// SRAM Controller

#define	HwIOBUSCFG_STORAGE_ECC		~(Hw17|Hw16)							// Storage Bus
#define	HwIOBUSCFG_STORAGE_AHB_BUS1	Hw16							// I/O bus
#define	HwIOBUSCFG_STORAGE_AHB_BUS2	Hw17							// General purpose SRAM or DTCM
#define	HwIOBUSCFG_STORAGE_NFC		(Hw17|Hw16)						// Main processor data bus

/************************************************************************
*	Channel 0 Memory Controller Register Define	(Base Addr = 0xF1000000)
************************************************************************/
#define	HwEMC_BASE				   *(volatile unsigned long *)0xF1000000	// External Memory Controller Base Register

/*******************************************************************************
*	 TCC8900_DataSheet_PART 6 DDI_BUS_V0.00 Dec.11 2008
********************************************************************************/
/************************************************************************
*	4. LCD INTERFACE Register Define				(Base Addr = 0xF0200000)
************************************************************************/
#define	HwLCDC0_BASE				*(volatile unsigned long *)0xF0200000	// LCDC0 Control Base Register
#define HwLCDLUT0_BASE				*(volatile unsigned long *)0xF0200400	// LCD LUT 0 Base Register
#define	HwLCDC1_BASE				*(volatile unsigned long *)0xF0204000	// LCDC1 Control Base Register
#define HwLCDLUT1_BASE				*(volatile unsigned long *)0xF0204400	// LCD LUT 1 Base Register

/************************************************************************
*	5. LCD System Interface Register Define		(Base Addr = 0xF0200400)
************************************************************************/
#define	HwLCDSI_BASE				*(volatile unsigned long *)0xF020C000	// LCDSI Base Register

/***********************************************************************
*	6. Memory to Memory Scaler Register Define	(Base Addr = 0xF0210000/0xF0220000)
************************************************************************/
#define HwM2MSCALER0_BASE           *(volatile unsigned long *)0xF0210000
#define HwM2MSCALER1_BASE           *(volatile unsigned long *)0xF0220000

/************************************************************************
*	7. NTSC/PAL ENCODER Composite Output Register Define (Base Addr = 0xF0240000)
************************************************************************/
#define	HwTVE_BASE					*(volatile unsigned long *)0xF0240000	// TV Encoder Base Register

/************************************************************************
*	8. HDMI Register Define				(Base Addr = 0xF0254000)
************************************************************************/
//Controller register base address 
#define HwHDMICTRL_BASE				*(volatile unsigned long *)0xF0254000	//Controller register base address 
	
//HDMI register base address 
#define HwHDMICORE_BASE  			*(volatile unsigned long *)0xF0255000  

//AES register base address 
#define HwHDMIAES_BASE  			*(volatile unsigned long *)0xF0256000  //AES register base address 

//SPDIF Receiver register base address 
#define HwHDMISPDIF_BASE  			*(volatile unsigned long *)0xF0257000  

//I2S Receiver register base address 
#define HwHDMII2S_BASE  			*(volatile unsigned long *)0xF0258000  
				
 //CEC register base address 					
#define HwHDMICEC_BASE  			*(volatile unsigned long *)0xF0259000 

/***********************************************************************
*	 9-1. Camera Interface Register Define			(Base Addr = 0xF0230000)
************************************************************************/
#define	HwCIF_BASE					*(volatile unsigned long *)0xF0230000	// CIF Base Register
#define HwCIF						((PCIF)&HwCIF_BASE)

// Input Image Color/Pattern Configuration 1
#define	HwICPCR1_ON					Hw31										// On/Off on CIF >> 0:Can't operate CIF , 1:Operating CIF
#define	HwICPCR1_PWD				Hw30										// Power down mode in camera >> 0:Disable, 1:Power down mode , This power down mode is connected the PWDN of camera sensor
#define	HwICPCR1_BPS				Hw23										// Bypass Scaler >> 0:Non, 1:Bypass
#define	HwICPCR1_POL				Hw21										// PXCLK Polarity >> 0:Positive edge, 1:Negative edge
#define	HwICPCR1_SKPF				(Hw20|Hw19|Hw18)							// Skip Frame >> 0~7 #Frames skips	[20:18]
#define	HwICPCR1_M420_ZERO			HwZERO										// Format Convert (YUV422->YUV420) , Not-Convert
#define	HwICPCR1_M420_ODD			Hw17										// converted in odd line skip
#define	HwICPCR1_M420_EVEN			(Hw17|Hw16)									// converted in even line skip
#define	HwICPCR1_BP					Hw15										// Bypass
#define	HwICPCR1_BBS_LSB8			Hw14										// When bypass 16bits mode, LSB 8bits are stored in first
#define	HwICPCR1_C656				Hw13										// Convert 656 format 0:Disable, 1:Enable
#define	HwICPCR1_CP_RGB				Hw12										// RGB(555,565,bayer) color pattern
#define	HwICPCR1_PF_444				HwZERO										// 4:4:4 format
#define	HwICPCR1_PF_422				Hw10										// 4:2:2 format
#define	HwICPCR1_PF_420				Hw11										// 4:2:0 format or RGB(555,565,bayer) mode
#define	HwICPCR1_RGBM_BAYER			HwZERO										// Bayer RGB Mode
#define	HwICPCR1_RGBM_RGB555		Hw8											// RGB555 Mode
#define	HwICPCR1_RGBM_RGB565		Hw9											// RGB565 Mode
#define	HwICPCR1_RGBBM_16			HwZERO										// 16bit mode
#define	HwICPCR1_RGBBM_8DISYNC		Hw6											// 8bit disable sync
#define	HwICPCR1_RGBBM_8			Hw7											// 8bit mode
#define	HwICPCR1_CS_RGBMG			HwZERO										// 555RGB:RGB(MG), 565RGB:RGB, 444/422/420:R/Cb/U first, Bayer RGB:BG->GR, CCIR656:YCbYCr
#define	HwICPCR1_CS_RGBLG			Hw4											// 555RGB:RGB(LG), 565RGB:RGB, 444/422/420:R/Cb/U first, Bayer RGB:GR->BG, CCIR656:YCrYCb
#define	HwICPCR1_CS_BGRMG			Hw5											// 555RGB:BGR(MG), 565RGB:BGR, 444/422/420:B/Cr/V first, Bayer RGB:RG->GB, CCIR656:CbYCrY
#define	HwICPCR1_CS_BGRLG			(Hw5|Hw4)									// 555RGB:BGR(LG), 565RGB:BGR, 444/422/420:B/Cr/V first, Bayer RGB:GB->RG, CCIR656:CrYCbY
#define	HwICPCR1_BO_SW				Hw2											// Switch the MSB/LSB 8bit Bus
#define	HwICPCR1_HSP_HIGH			Hw1											// Active high
#define	HwICPCR1_VSP_HIGH			Hw0											// Active high

// CCIR656 Format Configuration 1
#define	Hw656FCR1_PSL_1ST			HwZERO										// The status word is located the first byte of EAV & SAV
#define	Hw656FCR1_PSL_2ND			Hw25										// The status word is located the second byte of EAV & SAV
#define	Hw656FCR1_PSL_3RD			Hw26										// The status word is located the third byte of EAV & SAV
#define	Hw656FCR1_PSL_4TH			(Hw26|Hw25)									// The status word is located the forth byte of EAV & SAV
																				//FPV [23:16] 0x00FF0000,	SPV [15:8] 0x0000FF00, TPV [7:0]	0x000000FF
// CMOSIF DMA Configuratin 1
#define	HwCDCR1_TM_INC				Hw3											// INC Transfer
#define	HwCDCR1_LOCK_ON				Hw2											// Lock Transfer
#define	HwCDCR1_BS_1				HwZERO										// The DMA transfers the image data as 1 word to memory
#define	HwCDCR1_BS_2				Hw0											// The DMA transfers the image data as 2 word to memory
#define	HwCDCR1_BS_4				Hw1											// The DMA transfers the image data as 4 word to memory
#define	HwCDCR1_BS_8				(Hw1|Hw0)									// The DMA transfers the image data as 8 word to memory (default)

// FIFO Status
#define	HwFIFOSTATE_CLR				Hw21										// Clear FIFO states, 1:Clear, 0:Not Clear
#define	HwFIFOSTATE_REO				Hw19										// Overlay FIFO Read ERROR,	1:The empty signal of input overlay FIFO and read enable signal are High, 0:The empty signal of overlay FIFO is low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_REV				Hw18										// V(B) Channel FiFO Read ERROR, 1:The empty signal of input V(B) channel FIFO and read enable signal are High, 0:The empty signal of V(B) channel FIFO is Low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_REU				Hw17										// U(R) Channel FiFO Read ERROR, 1:The empty signal of input U(R) channel FIFO and read enable signal are High, 0:The empty signal of U(R) channel FIFO is Low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_REY				Hw16										// Y(G) Channel FiFO Read ERROR, 1:The empty signal of input Y(G) channel FIFO and read enable signal are High, 0:The empty signal of Y(G) channel FIFO is Low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_WEO				Hw13										// Overlay FIFO Write ERROR, 1:The full signal of overlay FIFO and write enable signal are High, 0:The full signal of overlay FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_WEV				Hw12										// V(B) Channel FiFO Write ERROR, 1:The full signal of V(B) channel FIFO and write enable signal are High, 0:The full signal of V(B) channel FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_WEU				Hw11										// U(R) Channel FiFO Write ERROR, 1:The full signal of U(R) channel FIFO and write enable signal are High, 0:The full signal of U(R) channel FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_WEY				Hw10										// Y(G) Channel FiFO Write ERROR, 1:The full signal of Y channel FIFO and write enable signal are High, 0:The full signal of Y channel FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_EO				Hw8											// Overlay FIFO Empty Signal, 1:The state of overlay FIFO is empty, 0:The state of overlay FIFO is non-empty.
#define	HwFIFOSTATE_EV				Hw7											// V(B) Channel FiFO Empty Signal, 1:The state of V(B) channel FIFO is empty, 0:The state of V(B) channel FIFO is non-empty.
#define	HwFIFOSTATE_EU				Hw6											// U(R) Channel FiFO Empty Signal, 1:The state of U(R) channel FIFO is empty, 0:The state of U(R) channel FIFO is non-empty.
#define	HwFIFOSTATE_EY				Hw5											// Y(G) Channel FiFO Empty Signal, 1:The state of Y channel FIFO is empty, 0:The state of Y channel FIFO is non-empty.
#define	HwFIFOSTATE_FO				Hw3											// Overlay FiFO FULL Signal, 1:The state of overlay FIFO is full, 0:The state of overlay FIFO is non-full.
#define	HwFIFOSTATE_FV				Hw2											// V(B) Channel FiFO FULL Signal, 1:The state of V(B) channel FIFO is full, 0:The state of V(B) channel FIFO is non-full.
#define	HwFIFOSTATE_FU				Hw1											// U(R) Channel FiFO FULL Signal, 1:The state of U(R) channel FIFO is full, 0:The state of U(R) channel FIFO is non-full.
#define	HwFIFOSTATE_FY				Hw0											// Y(G) Channel FiFO FULL Signal, 1:The state of Y(G) channel FIFO is full, 0:The state of Y(G) channel FIFO is non-full.

// Interrupt & CIF Operating
#define	HwCIRQ_IEN					Hw31										// Interrupt Enable	0:interrupt disable, 1:interrupt enable
#define	HwCIRQ_URV					Hw30										// Update Register in VSYNC	0:Register is update without VSYNC , 1:When VSYNC is posedge, register is updated.
#define	HwCIRQ_ITY					Hw29										// Interrupt Type	0:Pulse type, 1:Hold-up type when respond signal(ICR) is high
#define	HwCIRQ_ICR					Hw28										// Interrupt Clear 0:.... , 1:Interrupt Clear (using ITY is Hold-up type)
#define	HwCIRQ_MVN					Hw26										// Mask interrupt of VS negative edge,	0:Don't mask, 1:Mask
#define	HwCIRQ_MVP					Hw25										// Mask interrupt of VS positive edge,	0:Don't mask, 1:Mask
#define	HwCIRQ_MVIT					Hw24										// Mask interrupt of VCNT Interrupt,	0:Don't mask, 1:Mask
#define	HwCIRQ_MSE					Hw23										// Mask interrupt of Scaler Error,	0:Don't mask, 1:Mask
#define	HwCIRQ_MSF					Hw22										// Mask interrupt of Scaler finish,	0:Don't mask, 1:Mask
#define	HwCIRQ_MENS					Hw21										// Mask interrupt of Encoding start,	0:Don't mask, 1:Mask
#define	HwCIRQ_MRLV					Hw20										// Mask interrupt of Rolling V address,	0:Don't mask, 1:Mask
#define	HwCIRQ_MRLU					Hw19										// Mask interrupt of Rolling U address,	0:Don't mask, 1:Mask
#define	HwCIRQ_MRLY					Hw18										// Mask interrupt of Rolling Y address,	0:Don't mask, 1:Mask
#define	HwCIRQ_MSCF					Hw17										// Mask interrupt of Capture frame,	0:Don't mask, 1:Mask
#define	HwCIRQ_MSOF					Hw16										// Mask interrupt of Stored one frame,	0:Don't mask, 1:Mask
#define	HwCIRQ_VSS					Hw12										// Status of vertical sync, Non-vertical sync blank area.
#define	HwCIRQ_VN					Hw10										// VS negative, 0:-, 1:When VS is generated if negative edge
#define	HwCIRQ_VP					Hw9											// VS positive, 0:-, 1:When VS is generated if positive edge
#define	HwCIRQ_VIT					Hw8											// VCNT Interrupt, 0:-, 1:When VCNT is generated....
#define	HwCIRQ_SE					Hw7											// Scaler Error, 0:-, 1:When Scale operation is not correct.
#define	HwCIRQ_SF					Hw6											// Scaler Finish, 0:-, 1:When Scale operation is finished
#define	HwCIRQ_ENS					Hw5											// Encoding start status, 0:-, 1:When Y address is bigger than encoding start address, this bit is high
#define	HwCIRQ_ROLV					Hw4											// Rolling V address status, 0:-, 1:If V address is move to start address, this bit is high
#define	HwCIRQ_ROLU					Hw3											// Rolling U address starus, 0:-, 1:If U address is move to start address, this bit is high 
#define	HwCIRQ_ROLY					Hw2											// Rolling Y address starus, 0:-, 1:If Y address is move to start address, this bit is high 
#define	HwCIRQ_SCF					Hw1											// Stored captured frame,	0:-, 1:If Captured frame is stored, this bit is high
#define	HwCIRQ_SOF					Hw0											// Stored One frame, 0-, 1:If one frame if stored, this bit is high.

// Overlay Control 1
#define	HwOCTRL1_OCNT_MAX			(Hw29|Hw28|Hw27|Hw26|Hw25|Hw24)				//[28:24] Overlay Count FIFO (Hw27|Hw26|Hw25|Hw24|Hw23)
#define	HwOCTRL1_OM_BLOCK			Hw16										// Overlay Method 0:Full image overlay, 1:Block image overlay	, Full image overlay mode, overlay image size is equal to the input image size.
#define	HwOCTRL1_OE_EN				Hw12										// Overlay enable 0:Disable, 1:Enable
#define	HwOCTRL1_XR1_100			Hw10										// XOR in AP1 is 3 (100%)	0:XOR operation, 1:100%	, When AP1 is 3 and CEN & AEN is 1, We select the 100% alpha value or XOR.
#define	HwOCTRL1_XR0_100			Hw9											// XOR in AP0 is 3 (100%)	0:XOR operation, 1:100%	, When AP0 is 3 and CEN & AEN is 1, We select the 100% alpha value or XOR.
#define	HwOCTRL1_AP1_25				HwZERO										// Alpha Value in alpha is 1		// 25%			
#define	HwOCTRL1_AP1_50				Hw6											// Alpha Value in alpha is 1		// 50%
#define	HwOCTRL1_AP1_75				Hw7											// Alpha Value in alpha is 1		// 75%				
#define	HwOCTRL1_AP1_100			(Hw7|Hw6)									// Alpha Value in alpha is 1		// 100% or XOR operation (for XR value)
#define	HwOCTRL1_AP0_25				HwZERO										// Alpha Value in alpha is 0		// 25%			
#define	HwOCTRL1_AP0_50				Hw4											// Alpha Value in alpha is 0		// 50%
#define	HwOCTRL1_AP0_75				Hw5											// Alpha Value in alpha is 0		// 75%				
#define	HwOCTRL1_AP0_100			(Hw5|Hw4)									// Alpha Value in alpha is 0		// 100% or XOR operation
																				// When 565RGB and AEN, alpha value is depend on AP0 value.
#define	HwOCTRL1_AEN_EN				Hw2											// Alpha enable	0:Disable, 1:Enable
#define	HwOCTRL1_CEN_EN				Hw0											// Chroma key enable	0:Disable, 1:Enable

// Overlay Control 2 
#define	HwOCTRL2_CONV				Hw3											// Color Converter Enable 0:Disable, 1:Enable 
#define	HwOCTRL2_RGB_565			HwZERO										// RGB mode 565RGB 
#define	HwOCTRL2_RGB_555			Hw1											// RGB mode 555RGB
#define	HwOCTRL2_RGB_444			Hw2											// RGB mode 444RGB
#define	HwOCTRL2_RGB_332			(Hw2|Hw1)									// RGB mode 332RGB
#define	HwOCTRL2_MD					Hw0											// Color Mode	0:YUV Color, 1:RGB color

// Overlay Control 3 -- KEY Value 
#define	HwOCTRL3_KEYR_MAX			0x00FF0000									// Chroma-key value R(U), Chroea-key value in R(U) channel, Default value is 0x00
#define	HwOCTRL3_KEYG_MAX			0x0000FF00									// Chroma-key value G(Y), Chroea-key value in G(Y) channel, Default value is 0x00
#define	HwOCTRL3_KEYB_MAX			0x000000FF									// Chroma-key value B(V), Chroea-key value in B(V) channel, Default value is 0x00
 
// Overlay Control 4 -- Mask KEY Value
#define	HwOCTRL4_MKEYR_MAX			0x00FF0000									// Mask Chroma-key value R(U), Chroea-key value in R(U) channel, Default value is 0x00
#define	HwOCTRL4_MKEYG_MAX			0x0000FF00									// Mask Chroma-key value G(Y), Chroea-key value in G(Y) channel, Default value is 0x00
#define	HwOCTRL4_MKEYB_MAX			0x000000FF									// Mask Chroma-key value B(V), Chroea-key value in B(V) channel, Default value is 0x00

// Camera Down Scaler
#define	HwCDS_SFH_1					HwZERO										// Horizontal Scale Factor, 1/1 down scale
#define	HwCDS_SFH_2					Hw4											// Horizontal Scale Factor, 1/2 down scale
#define	HwCDS_SFH_4					Hw5											// Horizontal Scale Factor, 1/4 down scale
#define	HwCDS_SFH_8					(Hw5|Hw4)									// Horizontal Scale Factor, 1/8 down scale
#define	HwCDS_SFV_1					HwZERO										// Vertical Scale Factor, 1/1 down scale
#define	HwCDS_SFV_2					Hw2											// Vertical Scale Factor, 1/2 down scale
#define	HwCDS_SFV_4					Hw3											// Vertical Scale Factor, 1/4 down scale
#define	HwCDS_SFV_8					(Hw3|Hw2)									// Vertical Scale Factor, 1/8 down scale
#define	HwCDS_SEN_EN				Hw0											// Scale enable, 0:Disable, 1:enable

// CMOSIF Capture mode1
#define	HwCCM1_ENCNUM				0xF0000000									// Encode INT number (using CAP mode) [31:28], value area (0~15), Encode interrupt number
#define	HwCCM1_ROLNUMV				0x0F000000									// Rolling number in V (using CAP mode) [27:24], value area (0~15), Rolling number
#define	HwCCM1_ROLNUMU				0x00F00000									// Rolling number in U (using CAP mode) [23:20], value area (0~15), Rolling number
#define	HwCCM1_ROLNUMY				0x000F0000									// Rolling number in Y (using CAP mode) [19:16], value area (0~15), Rolling number
#define	HwCCM1_CB					Hw10										// Capture Busy,	0:-, 1:Capture busy
#define	HwCCM1_EIT					Hw9											// Encodig INT count,	0:Always 1 pulse, 1:Counting encoding INT
#define	HwCCM1_UES					Hw8											// Using Encoding Start Address,	0:disable, 1:Enable
#define	HwCCM1_SKIPNUM				0x000000F0									// Skip frame number (using CAP mode) [7:4], value area (0~15), Skip frame number
#define	HwCCM1_RLV					Hw3											// Rolling address V,	0:disable, 1:Enable
#define	HwCCM1_RLU					Hw2											// Rolling address U,	0:disable, 1:Enable
#define	HwCCM1_RLY					Hw1											// Rolling address Y,	0:disable, 1:Enable
#define	HwCCM1_CAP					Hw0											// Image Capture,	0:Normal, 1:Image Capture

// CMOSIF Capture mode2
#define	HwCCM2_VCNT					0x000000F0									// Description (Using CAP mode) [7:4], Threshold line counter in interrupt 1:16 line, 2:32 line, 3: 48 line...
#define	HwCCM2_VEN					Hw0											// VCNT folling enable (Using CAP mode) 0:Normal(?) Disalbe아닌가?, 1:Enable

// CMOSIF R2Y confiquration
#define	HwCR2Y_FMT					(Hw4|Hw3|Hw2|Hw1)							// FMT[4:1]	0000 -> Input format 16bit 565RGB(RGB sequence) 자세한 사항 750A CIF SPEC. 1-22
#define	HwCR2Y_EN					Hw0											// R2Y Enable,	0:disable, 1:Enable

// CMOSIF Current Line Count
#define	HwCCLC_LCNT					0x0000FFFF									// LCNT[15:0]	Current Line Count



/***********************************************************************
*	 9-2. Effect Register Define			(Base Addr = 0xF0230100)
************************************************************************/
#define	HwCEM_BASE    				*(volatile unsigned long *)0xF0230100  //W/R  0x00000000  Effect mode register 
#define HwCEM						((PEFFECT)&HwCEM_BASE)

// CMOSIF Effect mode
#define	HwCEM_UVS					Hw15										// UV Swap	0:u-v-u-v sequence, 1:v-u-v-u sequence
#define	HwCEM_VB					Hw14										// V Bias (V channel value offset),	0:disable, 1:Enable 
#define	HwCEM_UB					Hw13										// U Bias (U channel value offset),	0:disable, 1:Enable
#define	HwCEM_YB					Hw12										// Y Bias (Y channel value offset),	0:disable, 1:Enable
#define	HwCEM_YCS					Hw11										// YC Swap	0:u-y-v-y sequence, 1:y-u-y-v sequence
#define	HwCEM_IVY					Hw10										// Invert Y,	0:disable, 1:Enable 
#define	HwCEM_STC					Hw9											// Strong C,	0:disable, 1:Enable 
#define	HwCEM_YCL					Hw8											// Y Clamp (Y value clipping),	0:disable, 1:Enable 
#define	HwCEM_CS					Hw7											// C Select (Color filter),	0:disable, 1:Enable(Color filter)	
#define	HwCEM_SKT					Hw6											// Sketch Enable,	0:disable, 1:Enable 
#define	HwCEM_EMM					Hw5											// Emboss mode,	0:Positive emboss, 1:Negative emboss
#define	HwCEM_EMB					Hw4											// Emboss,	0:disable, 1:Enable	
#define	HwCEM_NEGA					Hw3											// Negative mode,	0:disable, 1:Enable 
#define	HwCEM_GRAY					Hw2											// Gray mode,	0:disable, 1:Enable 
#define	HwCEM_SEPI					Hw1											// Sepia mode,	0:disable, 1:Enable	
#define	HwCEM_NOR					Hw0											// Normal mode,	0:Effect mode, 1:Normal mode 

// CMOSIF Sepia UV Setting
#define	HwHwCSUV_SEPIA_U			0x0000FF00									// SEPIA_U[15:8] U channel threshold value for sepia
#define	HwHwCSUV_SEPIA_V			0x000000FF									// SEPIA_V[7:0] V channel threshold value for sepia

// CMOSIF Color selection
#define	HwCCS_USTART				0xFF000000									// USTART [31:24]	Color filter range start point of U channel
#define	HwCCS_UEND					0x00FF0000									// UEND	[23:16]	Color filter range end point of U channel
#define	HwCCS_VSTART				0x0000FF00									// VSTART [15:8]	Color filter range start point of V channel
#define	HwCCS_VEND					0x000000FF									// VEND	[7:0]	 Color filter range end point of V channel

// CMOSIF H-filter coefficent
#define	HwCHFC_COEF0				0x00FF0000									// COEF0	[23:16] Horizontal filter coefficient0 for emboss or sketch 
#define	HwCHFC_COEF1				0x0000FF00									// COEF1	[15:8] Horizontal filter coefficient1 for emboss or sketch 
#define	HwCHFC_COEF2				0x000000FF									// COEF2	[7:0] Horizontal filter coefficient2 for emboss or sketch 

// CMOSIF Sketch threshold
#define	HwCST_THRESHOLD				0x000000FF									// Sketch [7:0] Sketch threshold

// CMOSIF Clamp threshold
#define	HwCCT_THRESHOLD				0x000000FF									// Clamp [7:0] Clamp threshold

// CMOSIF BIAS
#define	HwCBR_YBIAS					0x00FF0000									// Y_BIAS [23:16] Y value offset
#define	HwCBR_UBIAS					0x0000FF00									// U_BIAS [15:8]	U value offset
#define	HwCBR_VBIAS					0x000000FF									// V_BIAS [7:0]	V value offset

// CMOSIF Image size
#if defined (SENSOR_3M) || defined (SENSOR_5M)
#define	HwCEIS_HSIZE				0x0FFF0000									// HSIZE [26:16]	Horizontal size of input image
#else
#define	HwCEIS_HSIZE				0x07FF0000									// HSIZE [26:16]	Horizontal size of input image
#endif
#define	HwCEIS_VSIZE				0x000007FF									// VSIZE [10:0]	Vertical size of input image

#define HwCIC_H2H_WAIT                      0xFFFF0000       // H2H_WAIT [31:16]   Horizontal sync (hs)to hs wait cycle
#define HwCIC_STB_CYCLE                      0x0000FF00      // STB_CYCLE [15:8]  CCIR strobe cycle,  Minimum Value of STB_CYCLE is 4.
#define HwCIC_INP_WAIT                        (Hw6|Hw5|Hw4)      // INP_WAIT [6:4]     ???????????????
#define HwCIC_INPR                                Hw3     // ???????????????
#define HwCIC_FA                                   Hw2     // Flush all
#define HwCIC_INE                                  Hw1     // Inpath Enalbe,   0:disable, 1:Enable 
#define HwCIC_INP                                  Hw0     // Inpath Mode,   0:Camera mode, 1:Memory mode

// Y값은 32전체를 다 세팅하도록 하고 U, V값은 상위 4bit는 생략해도 cif에서 address를 추정하는 것이 가능하다.
//	HwCISA1_SRC_BASE는 Y값만 4비트 더 존재해서 구별해 놓은 것임 ,, 실제로 사용할 경우 그냥 32 address를 할당 한다. 
// CMOSIF INPATH Source address in Y channel
#define	HwCISA1_SRC_BASE			0xF0000000									// SRC_BASE [31:28] Source base address (31 down to 28 bit assign in base address)
#define	HwCISA1_SRC_BASE_Y			0x0FFFFFFF									// SRC_BASE_Y [27:0] Source base address in Y channel (27 down to 0 bit assign in bass address)

// CMOSIF INPATH Source address in U channel
#define	HwCISA2_SRC_TYPE_422SEQ0	HwZERO										// 0: (4:2:2 SEQ0)
#define	HwCISA2_SRC_TYPE_422SEQ1	Hw28										// 1: (4:2:2 SEQ1)
#define	HwCISA2_SRC_TYPE_422SEPA	Hw29										// 2: (4:2:2 Separate)
#define	HwCISA2_SRC_TYPE_420SEPA	(Hw29|Hw28)									// 3: (4:2:0 Separate)
#define	HwCISA2_SRC_BASE_U			0x0FFFFFFF									// SRC_BASE_U [27:0] Source base address in U channal (27 down to 0 bit assign in base address)

// CMOSIF INPATH Source address in V channel
#define	HwCISA3_SRC_BASE_V			0x0FFFFFFF									// SRC_BASE_V [27:0] Source base address in V channal (27 down to 0 bit assign in base address)


// CMOSIF INPATH Source image offset
//#define	HwCISO_SRC_OFFSET_H			0x0FFF0000									// SRC_OFFSET_H [27:16] source address offset in H
//#define	HwCISO_SRC_OFFSET_V			0x00000FFF									// SRC_OFFSET_V [11:0]	source address offset in V
#define	HwCISO_SRC_OFFSET_Y			0x0FFF0000									// SRC_OFFSET_Y [27:16] source address offset in Y channel
#define	HwCISO_SRC_OFFSET_C			0x00000FFF									// SRC_OFFSET_C [11:0]	source address offset in C channel

// CMOSIF INPATH Source image size
#define	HwCISS_SRC_HSIZE			0x0FFF0000									// SRC_HSIZE [27:16] Horizontal size in source image
#define	HwCISS_SRC_VSIZE			0x00000FFF									// SRC_VSIZE [11:0]	Vertical size in source image


// CMOSIF INPATH Destination image size
#define	HwCIDS_DST_HSIZE			0x0FFF0000									// DST_HSIZE [27:16] Horizontal size in destination image
#define	HwCIDS_DST_VSIZE			0x00000FFF									// DST_VSIZE [11:0]	Vertical size in destination image

// HSCALE = SRC_HSIZE*256/DST_HSIZE
// VSCALE = SRC_VSIZE*256/DST_VSIZE
// CMOSIF INPATH Target scale
#define	HwCIS_HSCALE				0x3FFF0000									// HSCALE [29:16] Horizontal scale factor
#define	HwCIS_VSCALE				0x00003FFF									// VSCALE [13:0]	Vertical scale factor



/***********************************************************************
*	 9-3. Scaler Register Define			(Base Addr = 0xF0230200)
************************************************************************/
#define	HwCSC_BASE    				*(volatile unsigned long *)0xF0230200  //W/R  0x00000000  Scaler configuration 
#define HwCSC						((PCIFSCALER)&HwCSC_BASE)

// Scaler configuration
#define	HwSCC_EN					Hw0											// Scaler Enable	0:disable, 1:Enable 

// HSCALE = SRC_HSIZE*256/DST_HSIZE
// VSCALE = SRC_VSIZE*256/DST_VSIZE
// Scale factor
#define	HwSCSF_HSCALE				0x3FFF0000									// HSCALE [29:16] Horizontal scale factor
#define	HwSCSF_VSCALE				0x00003FFF									// VSCALE [13:0]	Vertical scale factor

// Image offset
#define	HwSCSO_OFFSET_H				0x0FFF0000									// H [27:16] Horizontal offset
#define	HwSCSO_OFFSET_V				0x00000FFF									// V [11:0]	Vertical offset

// Source image size
#define	HwSCSS_HSIZE				0x0FFF0000									// H [27:16] Horizontal size in source image
#define	HwSCSS_VSIZE				0x00000FFF									// V [11:0]	Vertical size in source image

// Destination image size
#define	HwSCDS_HSIZE				0x0FFF0000									// H [27:16] Horizontal size in destination image
#define	HwSCDS_VSIZE				0x00000FFF									// V [11:0]	Vertical size in destination image

/***********************************************************************
*   10. Video and Image  Quality Enhancer Register Define	(Base Addr = 0xF0230200)
************************************************************************/
#define HwVIQE_BASE                 *(volatile unsigned long *)0xF0252000

/***********************************************************************
*   11. LVDS Register Define                	(Base Addr = 0xF0230200)
************************************************************************/
#define HwDDI_CONFIG_BASE           *(volatile unsigned long *)0xF0251000
#define HwDDI_CONFIG				((PDDICONFIG)&HwDDI_CONFIG_BASE)

// HDMI Control register
#define	HwDDIC_HDMI_CTRL_EN			Hw15
#define	HwDDIC_HDMI_CTRL_SEL_LCDC0	HwZERO
#define	HwDDIC_HDMI_CTRL_SEL_LCDC1	Hw14
#define	HwDDIC_HDMI_CTRL_RST_HDMI	Hw0
#define	HwDDIC_HDMI_CTRL_RST_SPDIF	Hw1
#define	HwDDIC_HDMI_CTRL_RST_TMDS	Hw2
#define	HwDDIC_HDMI_CTRL_RST_NOTUSE	Hw3

// Power Down
#define	HwDDIC_PWDN_HDMI			Hw8											// HDMI Interface
#define	HwDDIC_PWDN_DDIC			Hw7											// DDIBUS Cache
#define	HwDDIC_PWDN_MSCL1			Hw6											// Memory Scaler 1
#define	HwDDIC_PWDN_MSCL0			Hw5											// Memory Scaler 0
#define	HwDDIC_PWDN_LCDSI			Hw4											// LCDSI Interface
#define	HwDDIC_PWDN_LCDC1			Hw3											// LCD 1 Interface
#define	HwDDIC_PWDN_LCDC0			Hw2											// LCD 0 Interface
#define	HwDDIC_PWDN_VIQE			Hw1											// Video Image Quality Enhancer
#define	HwDDIC_PWDN_CIF				Hw0											// Camera Interface

// Soft Reset
#define	HwDDIC_SWRESET_HDMI			Hw8											// HDMI Interface
#define	HwDDIC_SWRESET_DDIC			Hw7											// DDIBUS Cache
#define	HwDDIC_SWRESET_MSCL1		Hw6											// Memory Scaler 1
#define	HwDDIC_SWRESET_MSCL0		Hw5											// Memory Scaler 0
#define	HwDDIC_SWRESET_LCDSI		Hw4											// LCDSI Interface
#define	HwDDIC_SWRESET_LCDC1		Hw3											// LCD 1 Interface
#define	HwDDIC_SWRESET_LCDC0		Hw2											// LCD 0 Interface
#define	HwDDIC_SWRESET_VIQE			Hw1											// Video Image Quality Enhancer
#define	HwDDIC_SWRESET_CIF			Hw0											// Camera Interface

#define HwDDI_CACHE_BASE            *(volatile unsigned long *)0xF0250000
#define HwDDI_CACHE					((PDDICACHE)&HwDDI_CACHE_BASE)

// DDI CACHE Control
#define	HwDDIC_CTRL_BW				Hw31
#define	HwDDIC_CTRL_CIF_DMA			Hw25
#define	HwDDIC_CTRL_VIQE_DMA2_2		Hw24
#define	HwDDIC_CTRL_VIQE_DMA2_1		Hw23
#define	HwDDIC_CTRL_VIQE_DMA2_0		Hw22
#define	HwDDIC_CTRL_VIQE_DMA1_2		Hw21
#define	HwDDIC_CTRL_VIQE_DMA1_1		Hw20
#define	HwDDIC_CTRL_VIQE_DMA1_0		Hw19
#define	HwDDIC_CTRL_VIQE_DMA0_2		Hw18
#define	HwDDIC_CTRL_VIQE_DMA0_1		Hw17
#define	HwDDIC_CTRL_VIQE_DMA0_0		Hw16
#define	HwDDIC_CTRL_MSCL1_DMA2		Hw15
#define	HwDDIC_CTRL_MSCL1_DMA1		Hw14
#define	HwDDIC_CTRL_MSCL1_DMA0		Hw13
#define	HwDDIC_CTRL_MSCL0_DMA2		Hw12
#define	HwDDIC_CTRL_MSCL0_DMA1		Hw11
#define	HwDDIC_CTRL_MSCL0_DMA0		Hw10
#define	HwDDIC_CTRL_LCD1_DMA2		Hw9
#define	HwDDIC_CTRL_LCD1_DMA1		Hw8
#define	HwDDIC_CTRL_LCD1_DMA0_2		Hw7
#define	HwDDIC_CTRL_LCD1_DMA0_1		Hw6
#define	HwDDIC_CTRL_LCD1_DMA0_0		Hw5
#define	HwDDIC_CTRL_LCD0_DMA2		Hw4
#define	HwDDIC_CTRL_LCD0_DMA1		Hw3
#define	HwDDIC_CTRL_LCD0_DMA0_2		Hw2
#define	HwDDIC_CTRL_LCD0_DMA0_1		Hw1
#define	HwDDIC_CTRL_LCD0_DMA0_0		Hw0

// DDI CACHE Configuration
#define	HwDDIC_CFG_CIF_DMA			(25)
#define	HwDDIC_CFG_VIQE_DMA2_2		(24)
#define	HwDDIC_CFG_VIQE_DMA2_1		(23)
#define	HwDDIC_CFG_VIQE_DMA2_0		(22)
#define	HwDDIC_CFG_VIQE_DMA1_2		(21)
#define	HwDDIC_CFG_VIQE_DMA1_1		(20)
#define	HwDDIC_CFG_VIQE_DMA1_0		(19)
#define	HwDDIC_CFG_VIQE_DMA0_2		(18)
#define	HwDDIC_CFG_VIQE_DMA0_1		(17)
#define	HwDDIC_CFG_VIQE_DMA0_0		(16)
#define	HwDDIC_CFG_MSCL1_DMA2		(15)
#define	HwDDIC_CFG_MSCL1_DMA1		(14)
#define	HwDDIC_CFG_MSCL1_DMA0		(13)
#define	HwDDIC_CFG_MSCL0_DMA2		(12)
#define	HwDDIC_CFG_MSCL0_DMA1		(11)
#define	HwDDIC_CFG_MSCL0_DMA0		(10)
#define	HwDDIC_CFG_LCD1_DMA2		(9)
#define	HwDDIC_CFG_LCD1_DMA1		(8)
#define	HwDDIC_CFG_LCD1_DMA0_2		(7)
#define	HwDDIC_CFG_LCD1_DMA0_1		(6)
#define	HwDDIC_CFG_LCD1_DMA0_0		(5)
#define	HwDDIC_CFG_LCD0_DMA2		(4)
#define	HwDDIC_CFG_LCD0_DMA1		(3)
#define	HwDDIC_CFG_LCD0_DMA0_2		(2)
#define	HwDDIC_CFG_LCD0_DMA0_1		(1)
#define	HwDDIC_CFG_LCD0_DMA0_0		(0)	

#define HwDDIC_CFG_MASK			(0x1F)
#define	HwDDIC_CFG26(X)			((X)<<16)
#define	HwDDIC_CFG27(X)			((X)<<24)
#define	HwDDIC_CFG28(X)			((X))
#define	HwDDIC_CFG29(X)			((X)<<8)
#define	HwDDIC_CFG30(X)			((X)<<16)
#define	HwDDIC_CFG31(X)			((X)<<24)

/*******************************************************************************
*	 TCC8900_DataSheet_PART 7 VIDEO BUS_V0.00 Dec.11 2008
********************************************************************************/
/***********************************************************************
*   4. VIDEO CODEC Register Define                	(Base Addr = 0x0xF0700000)
************************************************************************/
#define HwVIDEOCODEC_BASE           *(volatile unsigned long *)0xF0700000

/***********************************************************************
*   5. JPEG CODEC Register Define                	(Base Addr = 0x0xF0710000/0xF0720000)
************************************************************************/
#define HwJPEGDECODER_BASE          *(volatile unsigned long *)0xF0710000
#define HwJPEGENCODER_BASE          *(volatile unsigned long *)0xF0720000
#define HwVIDEOCACHE_BASE           *(volatile unsigned long *)0xF0701000
#define HwVIDEOBUSCFG_BASE           *(volatile unsigned long *)0xF0702000

/*******************************************************************************
*	 TCC8900_DataSheet_PART 8 GRAPHIC BUS_V0.00 Dec.11 2008
********************************************************************************/
/***********************************************************************
*	 4. Overlay Mixer Register Define	(Base Addr = 0xF0010000)
************************************************************************/
#define HwOVERLAYMIXER_BASE         *(volatile unsigned long *)0xF0010000

/*******************************************************************************
*	 5-1. 2D/3D GPU
*
*	 Pixel Processor Register Map Register Define   (Base Addr = 0xF0000000)
********************************************************************************/
#define HwPIXELPROCESSOR_BASE       *(volatile unsigned long *)0xF0000000

/*******************************************************************************
*	 5-2. Geometry Processor Register Map Register Define   (Base Addr = 0xF0000000)
********************************************************************************/
#define HwGEOMETRYPROCESSOR_BASE    *(volatile unsigned long *)0xF0002000

/*******************************************************************************
*	 5-3. MMU Configuration Register Define   (Base Addr = 0xF0003000)
********************************************************************************/
#define HwMMUCONFIG_BASE            *(volatile unsigned long *)0xF0003000

/*******************************************************************************
*	 5-4. GRPBUS Configuration Register Define   (Base Addr = 0xF0004000)
********************************************************************************/
#define HwGRPBUS_BASE               *(volatile unsigned long *)0xF0004000

/*******************************************************************************
*	 5-5. GRPBUS BWRAP Register Define   (Base Addr = 0xF0005000)
********************************************************************************/
#define HwGRPBUSBWRAP_BASE          *(volatile unsigned long *)0xF0005000

#endif						
