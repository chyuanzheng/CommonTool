
/****************************************************************************
*   FileName    : TCC88x_Physical.h
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

 ****************************************************************************/

/************************************************************************
*   TCC88x Internal Register Definition File
************************************************************************/
#ifndef __TCC88x_H__
#define __TCC88x_H__

/************************************************************************
*   Bit Field Definition
************************************************************************/
#define Hw37                                    (1LL << 37)
#define Hw36                                    (1LL << 36)
#define Hw35                                    (1LL << 35)
#define Hw34                                    (1LL << 34)
#define Hw33                                    (1LL << 33)
#define Hw32                                    (1LL << 32)
#define Hw31                                    0x80000000
#define Hw30                                    0x40000000
#define Hw29                                    0x20000000
#define Hw28                                    0x10000000
#define Hw27                                    0x08000000
#define Hw26                                    0x04000000
#define Hw25                                    0x02000000
#define Hw24                                    0x01000000
#define Hw23                                    0x00800000
#define Hw22                                    0x00400000
#define Hw21                                    0x00200000
#define Hw20                                    0x00100000
#define Hw19                                    0x00080000
#define Hw18                                    0x00040000
#define Hw17                                    0x00020000
#define Hw16                                    0x00010000
#define Hw15                                    0x00008000
#define Hw14                                    0x00004000
#define Hw13                                    0x00002000
#define Hw12                                    0x00001000
#define Hw11                                    0x00000800
#define Hw10                                    0x00000400
#define Hw9                                     0x00000200
#define Hw8                                     0x00000100
#define Hw7                                     0x00000080
#define Hw6                                     0x00000040
#define Hw5                                     0x00000020
#define Hw4                                     0x00000010
#define Hw3                                     0x00000008
#define Hw2                                     0x00000004
#define Hw1                                     0x00000002
#define Hw0                                     0x00000001
#define HwZERO                                  0x00000000


/*******************************************************************************
*
*    TCC88x DataSheet PART 2 SMU & PMU
*
********************************************************************************/
/************************************************************************
*   1. CKC (Base Addr = 0xF0400000)
************************************************************************/
#define HwCKC_BASE									(0xF0400000)

/************************************************************************
*   2. VPIC(Vectored Priority Interrupt Controller) (Base Addr = 0xF0401000)
************************************************************************/
#define HwVPIC_BASE									(0xF0401000)
#define HwPIC_BASE_O									(0xF0401000)
#define HwPIC_BASE									*(volatile unsigned long *)(0xF0401000)
#define HwVIC_BASE									(0xF0401200)

/************************************************************************
*   3. Timer/Counter (Base Addr = 0xF0403000)
************************************************************************/
#define HwTMR_BASE									(0xF0403000)

/************************************************************************
*   4. PMU(Power Management Unit) (Base Addr = 0xF0404000)
************************************************************************/
#define HwPMU_BASE									(0xF0404000)

/************************************************************************
*   5. SMU_I2C (Base Addr = 0xF0405000)
************************************************************************/
#define HwSMUI2C_BASE								(0xF0405000)
#define HwSMUI2C_MASTER0_BASE						(0xF0405000)
#define HwSMUI2C_MASTER1_BASE						(0xF0405040)
#define HwSMUI2C_COMMON_BASE						(0xF0405080)


/************************************************************************
*   6. GPIO & Port Multiplexing (Base Addr = 0xF0308000)
************************************************************************/
#define HwGPIO_BASE									(0xF0308000)
#define HwGPIOA_BASE								(0xF0308000)
#define HwGPIOB_BASE								(0xF0308040)
#define HwGPIOC_BASE								(0xF0308080)
#define HwGPIOD_BASE								(0xF03080C0)
#define HwGPIOE_BASE								(0xF0308100)
#define HwGPIOF_BASE								(0xF0308140)
#define HwGPIOG_BASE								(0xF03081C0)

#define HwGPIO						((PGPIO)HwGPIO_BASE)
#define HwGPIOA						((PGPION)HwGPIOA_BASE)
#define HwGPIOB						((PGPION)HwGPIOB_BASE)
#define HwGPIOC						((PGPION)HwGPIOC_BASE)
#define HwGPIOD						((PGPION)HwGPIOD_BASE)
#define HwGPIOE						((PGPION)HwGPIOE_BASE)
#define HwGPIOF						((PGPION)HwGPIOF_BASE)
#define HwEINTSEL					((PGPIOINT)HwEINTSEL_BASE)

#define HwEINTSEL_BASE								(0xF0308184)
#define HwSYSMONEN_BASE								(0xF030818C)
#define HwECID_BASE									(0xF0308190)

/************************************************************************
*   8. SMU Config (Base Addr = 0xF05F4000)
************************************************************************/
#define HwSMUCONFIG_BASE							(0xF05F4000)




/*******************************************************************************
*
*    TCC88x DataSheet PART 3 GRAPHIC BUS
*
********************************************************************************/

/************************************************************************
*   4. 2D/3D GPU Register Define				(Base Addr = 0xF0000000) // R/W
************************************************************************/
#define HwGPU_BASE								(0xF0000000)

/************************************************************************
*   4-3. Pixel Processor Register Define		(Base Addr = 0xF0000000) // R/W
************************************************************************/
#define HwPIXELPROCESSOR_BASE					(0xF0000000)
#define HwGPU_PXL_FRAMEREGISTERS_BASE			(0xF0000000)
#define HwGPU_PXL_WRITEBACKREGISTER_BASE		(0xF0000100)
#define HWGPU_PXL_MANAGEMENTREGISTER_BASE		(0xF0001000)

/************************************************************************
*   4-4. Geometry Processor Register Define         (Base Addr = 0xF0002000) // R/W
************************************************************************/
#define HwGEOMETRYPROCESSOR_BASE				(0xF0002000)
#define HwGPU_GEO_CONTROLREGISTER_BASE			(0xF0002000)
//#define HwGPU_GEO_PLBCONFIGREGISTER_BASE		0x0100	
//#define HwGPU_GEO_VERTEXSHADER_BASE			0x0000

/*************************************************************************
*   4-5. MMU Register Define                        (Base Addr = 0xF0003000) // R/W
************************************************************************/
#define HwGPUMMUCONFIG_BASE						(0xF0003000)

/************************************************************************
*   5. Graphic Bus Configuration Register Define  (Base Addr = 0xF0004000) // R/W
************************************************************************/
#define HwGRPBUSCONFIG_BASE						(0xF0004000)


/*******************************************************************************
*
*    TCC88x DataSheet PART 4 MEMORY BUS
*
********************************************************************************/
/*
* 0xF0300000    Memory Bus Matrix Control 
* 0xF0301000    PL340 Controller (LPDDR) 
* 0xF0302000    PL341 Controller (DDR2) 
* 0xF0303000    Memory Controller Configuration 
* 0xF0304000    DDR PHY Configuration 
* 0xF0305000    Memory Bus Configuration 1 
* 0xF0306000    LPCON Controller (LPDDR, LPDDR2) 
* 0xF0307000    Memory Bus Configuration 2 
* 0xF0308000    GPIO 
* 0xF0309000    DDR2/3 Controller (DDR2, DDR3) 
* 0xF0600000    Hardware MMU Table
*/

/************************************************************************
*   3. Multi-layer Bus Matrix Register (Base Addr = 0xF0300000) // R/W
************************************************************************/
#define HwMULTILAYERBUSMATRIX_BASE				(0xF0300000)

/************************************************************************
*   4. DDR SDRAM Memory Controller (Base Addr = 0xF0301000) // R/W
************************************************************************/
#define HwLPDDR_BASE							(0xF0301000)
#define HwDDR2_BASE								(0xF0302000)
#define HwLPCON_BASE							(0xF0306000)
#define HwDDR23_BASE							(0xF0309000)

#define HwDDRIFCFG_BASE							(0xF0303000)
#define HwDDRPHY_BASE							(0xF0304400)

/************************************************************************
*   6. Memory Bus Configuration (Base Addr = ) // R/W
************************************************************************/
#define HwMEMBUSCFG1_BASE						(0xF0305000)
#define HwMEMBUSCFG2_BASE						(0xF0307000)

/************************************************************************
*   7. Internal Memory BUS Configuration (Base Addr = ) // R/W
************************************************************************/
#define HwVMT_BASE								(0x20000000)
#define HwINTNLMEMBUSCFG_BASE					(0xF0600000)


/*******************************************************************************
*
*    TCC88x DataSheet PART 5 IO BUS
*
********************************************************************************/

/*******************************************************************************
*    4. Memory Stick Host Controller Register Define (Base Addr = 0xF0590000)
********************************************************************************/
#define HwSMSHC_BASE							(0xF0590000)
#define HwSMSHC_PORTCFG_BASE					(0xF05F1000)

/*******************************************************************************
*    5. SD/SDIO/MMC Host Controller Register Define (Base Addr = 0xF05A0000)
********************************************************************************/
#define HwSDMMC_BASE							(0xF05A0000)
#define HwSDMMC0_BASE							(0xF05A0000)
#define HwSDMMC1_BASE							(0xF05A0200)
#define HwSDMMC2_BASE							(0xF05A0400)
#define HwSDMMC3_BASE							(0xF05A0600)
#define HwSDMMC_CHCTRL_BASE						(0xF05A0800)

/*******************************************************************************
*    6. EHI Register Define (Base Addr = 0xF0570000)
********************************************************************************/
#define HwEHI_BASE								(0xF0570000)
#define HwEHI0_BASE								(0xF0570000)
#define HwEHI1_BASE								(0xF0580000)

/*******************************************************************************
*    7. DMA Controller Register Define (Base Addr = 0xF0540000)
********************************************************************************/
// #define HwGDMA_BASE								(0xF0540000)
// #define HwGDMA0_BASE							(0xF0540000)
// #define HwGDMA1_BASE							(0xF0540100)
// #define HwGDMA2_BASE							(0xF0540200)
// #define HwGDMA3_BASE							(0xF0540300)
#define HwGDMA0_BASE               *(volatile unsigned long *)0xF0540000
#define HwGDMA1_BASE               *(volatile unsigned long *)0xF0540100
#define HwGDMA2_BASE               *(volatile unsigned long *)0xF0540200
#define HwGDMA3_BASE               *(volatile unsigned long *)0xF0540300

/*******************************************************************************
*    8. GPSB Controller Register Define (Base Addr = 0xF0535000)
********************************************************************************/
#define HwGPSB_BASE								(0xF0535000)
#define HwGPSB0_BASE							(0xF0535000)
#define HwGPSB1_BASE							(0xF0535100)
#define HwGPSB2_BASE							(0xF0535200)
#define HwGPSB3_BASE							(0xF0535300)
#define HwGPSB4_BASE							(0xF0535400)
#define HwGPSB5_BASE							(0xF0535500)
#define HwGPSB_PORTCFG_BASE						(0xF0535800)
#define HwGPSB_PIDTABLE_BASE					(0xF0535F00)

/*******************************************************************************
*    9. Overlay Mixer Register Define (Base Addr = 0xF0560000)
********************************************************************************/
//#define HwOVERLAYMIXER_BASE						(0xF0560000)
#define HwOVERLAYMIXER_BASE         *(volatile unsigned long *)0xF0560000

/*******************************************************************************
*    10. Audio0(7.1ch) Register Define (Base Addr = 0xF0532000)
********************************************************************************/
#define HwAUDIO0_DMA_BASE						(0xF0532000)
#define HwAUDIO0_DAI_BASE						(0xF0533000)
#define HwAUDIO0_CDIF_BASE						(0xF0533080)
#define HwAUDIO0_SPDIFTX_BASE					(0xF0534000)
#define HwAUDIO0_SPDIFRX_BASE					(0xF0534800)

/*******************************************************************************
*    11. Audio1(Stereo) Register Define (Base Addr = 0xF0536000)
********************************************************************************/
#define HwAUDIO1_DAI0_BASE						(0xF0536000)
#define HwAUDIO1_CDIF_BASE						(0xF0536080)
#define HwAUDIO1_DAI1_BASE						(0xF0536100)
#define HwAUDIO1_SPDIFTX_BASE					(0xF0537000)

/*******************************************************************************
*    12. NFC(NAND Flash Controller) Register Define (Base Addr = 0xF05B0000)
********************************************************************************/
#define HwNFC_BASE								(0xF05B0000)	

#define	HwNFC_CTRL_CS3SEL_1			Hw31							// Nand Flash nCS3 is High (Disabled)
#define	HwNFC_CTRL_CS3SEL_0			HwZERO							// Nand Flash nCS3 is Low (Enabled)
#define	HwNFC_CTRL_CS2SEL_1			Hw30							// Nand Flash nCS2 is High (Disabled)
#define	HwNFC_CTRL_CS2SEL_0			HwZERO							// Nand Flash nCS2 is Low (Enabled)
#define	HwNFC_CTRL_CS1SEL_1			Hw29							// Nand Flash nCS1 is High (Disabled)
#define	HwNFC_CTRL_CS1SEL_0			HwZERO							// Nand Flash nCS1 is Low (Enabled)
#define	HwNFC_CTRL_CS0SEL_1			Hw28							// Nand Flash nCS0 is High (Disabled)
#define	HwNFC_CTRL_CS0SEL_0			HwZERO							// Nand Flash nCS0 is Low (Enabled)
#define	HwNFC_CTRL_CFG_nCS3			HwNFC_CTRL_CS3SEL_1
#define	HwNFC_CTRL_CFG_nCS2			HwNFC_CTRL_CS2SEL_1
#define	HwNFC_CTRL_CFG_nCS1			HwNFC_CTRL_CS1SEL_1
#define	HwNFC_CTRL_CFG_nCS0			HwNFC_CTRL_CS0SEL_1
#define	HwNFC_CTRL_CFG_NOACT		(Hw31|Hw30|Hw29|Hw28)

#define	HwNFC_CTRL_RDNDLY(X)		((X)*Hw25)						// Nand Flash Read Data Delay 
#define	HwNFC_CTRL_RDNDLY_0			HwNFC_CTRL_RDNDLY(0)			// Nand Flash Read Data Delay (NONE)
#define	HwNFC_CTRL_RDNDLY_1			HwNFC_CTRL_RDNDLY(1)			// Nand Flash Read Data Delay (1 Clock)
#define	HwNFC_CTRL_RDNDLY_2			HwNFC_CTRL_RDNDLY(2)			// Nand Flash Read Data Delay (2 Clock)
#define	HwNFC_CTRL_RDNDLY_3			HwNFC_CTRL_RDNDLY(3)			// Nand Flash Read Data Delay (3 Clock)
#define	HwNFC_CTRL_RDNDLY_4			HwNFC_CTRL_RDNDLY(4)			// Nand Flash Read Data Delay (4 Clock)
#define	HwNFC_CTRL_RDNDLY_5			HwNFC_CTRL_RDNDLY(5)			// Nand Flash Read Data Delay (5 Clock)
#define	HwNFC_CTRL_RDNDLY_6			HwNFC_CTRL_RDNDLY(6)			// Nand Flash Read Data Delay (6 Clock)
#define	HwNFC_CTRL_RDNDLY_7			HwNFC_CTRL_RDNDLY(7)			// Nand Flash Read Data Delay (7 Clock)

#define	HwNFC_CTRL_ARFW_FLAG_EN		Hw24							// Nand Flash Automatically Ready Flag Wait Enanble 
#define	HwNFC_CTRL_ARFW_FLAG_DIS	~Hw24							// Nand Flash Automatically Ready Flag Wait Disable

#define	HwNFC_CTRL_DACK_EN			Hw20							// Nand Flash DMA Acknowledge Enable
#define	HwNFC_CTRL_DACK_DIS			~Hw20							// Nand Flash DMA Acknowledge Disable
#define	HwNFC_CTRL_DMODE_NDMA		Hw19							// Nand Flash DMA Mode Selection ( NDMA )
#define	HwNFC_CTRL_DMODE_GDMA		~Hw19							// Nand Flash DMA Mode Selection ( GDMA )
#define	HwNFC_CTRL_BMODE_BURST		Hw18							// Nand Flash Burst Operation Mode Selection For NDMA( Burst Mode[User Data + ECC] )
#define	HwNFC_CTRL_BMODE_NOR		~Hw18							// Nand Flash Burst Operation Mode Selection For NDMA( Normal Mode[User Data])
#define	HwNFC_CTRL_ECCON_EN			Hw17							// Nand Flash ECC Encoding/Decoding Enable
#define	HwNFC_CTRL_ECCON_DIS		~Hw17							// Nand Flash ECC Encoding/Decoding Disable
#define	HwNFC_CTRL_PRSEL_P			Hw16							// Nand Flash Program Mode Selection for Burst Transfer
#define	HwNFC_CTRL_PRSEL_R			~Hw16							// Nand Flash Read Mode Selection for Burst Transfer
#define	HwNFC_CTRL_DNUM(X)			((X)*Hw14)
#define	HwNFC_CTRL_DNUM_0			HwNFC_CTRL_DNUM(0)				// Nand Flash Multiplee Data Configuration Number 
#define	HwNFC_CTRL_DNUM_1			HwNFC_CTRL_DNUM(1)				// Nand Flash Multiplee Data Configuration Number 
#define	HwNFC_CTRL_DNUM_2			HwNFC_CTRL_DNUM(2)				// Nand Flash Multiplee Data Configuration Number 

#define	HwNFC_CTRL_RDY0SEL			Hw12							// NAND Flash Extend Ready Input Selection 
#define	HwNFC_CTRL_RDY3TO0SEL		~Hw12							// Address/Command Mask Enable
#define	HwNFC_CTRL_RDY_MSK_EN		Hw11							// NAND Flahs Ready Mask Enable(Mask) 
#define	HwNFC_CTRL_RDY_MSK_DIS		~Hw11							// NAND Flahs Ready Mask DIsable(UnMask)
#define	HwNFC_CTRL_MASK_EN			Hw10							// Address/Command Mask Enable
#define	HwNFC_CTRL_MASK_DIS			~Hw10							// Address/Command Mask Enable

#define	HwNFC_CTRL_BW(X)			((X)*Hw8)
#define	HwNFC_CTRL_BW_8				HwNFC_CTRL_BW(0)				// 1Read/Write
#define	HwNFC_CTRL_BW_16			HwNFC_CTRL_BW(1)				// 2Read/Write
#define	HwNFC_CTRL_BW_32			HwNFC_CTRL_BW(2)				// 4Read/Write

#define	HwNFC_CTRL_BSIZE(X)			((X)*Hw6)
#define	HwNFC_CTRL_BSIZE_1			HwNFC_CTRL_BSIZE(0)				// 1Read/Write
#define	HwNFC_CTRL_BSIZE_2			HwNFC_CTRL_BSIZE(1)				// 2Read/Write
#define	HwNFC_CTRL_BSIZE_4			HwNFC_CTRL_BSIZE(2)				// 4Read/Write
#define	HwNFC_CTRL_BSIZE_8			HwNFC_CTRL_BSIZE(3)				// 8Read/Write

#define	HwNFC_CTRL_PSIZE(X)			((X)*Hw3)
#define	HwNFC_CTRL_PSIZE_256		HwNFC_CTRL_PSIZE(0)				// 1 Page = 256 Half-Word
#define	HwNFC_CTRL_PSIZE_512		HwNFC_CTRL_PSIZE(1)				// 1 Page = 512 Byte
#define	HwNFC_CTRL_PSIZE_1024		HwNFC_CTRL_PSIZE(2)				// 1 Page = 1024 Half-Word
#define	HwNFC_CTRL_PSIZE_2048		HwNFC_CTRL_PSIZE(3)				// 1 Page = 2048 Byte
#define	HwNFC_CTRL_PSIZE_4096		HwNFC_CTRL_PSIZE(4)				// 1 Page = 4096 Byte
#define	HwNFC_CTRL_PSIZE_MASK		HwNFC_CTRL_PSIZE(7)
#define	HwNFC_CTRL_CADDR			Hw0								// Number of Address Cycle

/*******************************************************************************
* NFC IRQCFC														(0xF05B0064)
*******************************************************************************/
#define HwNFC_IRQCFG_RDYIEN         Hw31							//NAND Flash Ready Interrupt Enable
#define HwNFC_IRQCFG_PIEN			Hw30							//NAND Flash Program Interrupt Enable
#define HwNFC_IRQCFG_RDIEN			Hw29							//NAND Flash Read Interrupt Enable

#define HwNFC_IRQCFG_SPWIEN			Hw27							//NAND Flash Spare Area Burst Write Interrupt
#define HwNFC_IRQCFG_SPRIEN			Hw26							//NAND Flash Spare Area Burst Read Interrupt

#define HwNFC_IRQCFG_MEIEN			Hw26							//MLC ECC Decoding Interrupt Enable 

/*******************************************************************************
* NFC IRQ															(0xF05B0068)
*******************************************************************************/
#define HwNFC_IRQ_MEDIRQ			Hw23
#define HwNFC_IRQ_PFG				Hw14
#define HwNFC_IRQ_RDFG				Hw13

#define	HwECC_IREQ_MEDFG			Hw7								// MLC ECC Decoding Flag Register
#define	HwECC_IREQ_MEEFG			Hw6								// MLC ECC Encoding Flag Register
#define	HwECC_IREQ_SEDFG			Hw5								// SLC ECC Decoding Flag Register
#define	HwECC_IREQ_SEEFG			Hw4								// SLC ECC Encoding Flag Register
#define	HwECC_IREQ_ERRFG			Hw3								// MLC/SLC Error Flag

/*******************************************************************************
* NFC STATUS														(0xF05B006C)
*******************************************************************************/
#define HwNFC_STATUS_RDY_RDY		Hw31							// NAND Flash Ready Flag Status 
#define	HwNFC_CTRL_RDY_BUSY			~Hw31							// External Nand Flash Controller is Busy
#define	HwNFC_CTRL_FS_RDY			Hw30							// FIFO status is Ready to write and read in FIFO
#define	HwNFC_CTRL_FS_BUSY			~Hw30							// FIFO status is Busy to write and read in FIFO

/* Here SubPage!!!! */

/*******************************************************************************
* ECC CONTROL REGISTER 
*******************************************************************************/
#define HwECC_BASE								(0xF05B0200)	

#define HwECC_CTRL_DSIZE_CLEAR		(Hw26|Hw25|Hw24|Hw23|Hw22|Hw21|Hw20|Hw19|Hw18|Hw17|Hw16)

#define HwECC_CTRL_CORPASS_EN		Hw5								// MLC Correction Pass Enable
#define HwECC_CTRL_CORPASS_DIS		~Hw5							// MLC Correction Pass Disable
#define HwECC_CTRL_ECCMODE_NDM_EN	Hw4								// ECC Mode Selection( 0: Nor 1: NFC Dedicated Memory)
#define HwECC_CTRL_ECCMODE_NDM_DIS	~Hw4							// ECC Mode Selection( 0: Nor 1: NFC Dedicated Memory)

#define	HwECC_CTRL_EN_SLCEN			Hw2								// SLC ECC Encoding Enable
#define	HwECC_CTRL_EN_SLCDE			(Hw2|Hw0)						// SLC ECC Decoding Enable
#define	HwECC_CTRL_EN_MCL4EN		(Hw2|Hw1)						// MLC ECC4 Encoding Enable
#define	HwECC_CTRL_EN_MCL4DE		(Hw2|Hw1|Hw0)					// MLC ECC4 Decoding Enable
#define	HwECC_CTRL_EN_MCL6EN		(Hw3)							// MLC ECC6 Encoding Enable
#define	HwECC_CTRL_EN_MCL6DE		(Hw3|Hw0)						// MLC ECC6 Decoding Enable
#define	HwECC_CTRL_EN_MCL12EN		(Hw3|Hw1)						// MLC ECC12 Encoding Enable
#define	HwECC_CTRL_EN_MCL12DE		(Hw3|Hw1|Hw0)					// MLC ECC12 Decoding Enable
#define	HwECC_CTRL_EN_MCL16EN		(Hw3|Hw2)						// MLC ECC16 Encoding Enable
#define	HwECC_CTRL_EN_MCL16DE		(Hw3|Hw2|Hw0)					// MLC ECC16 Decoding Enable
#define	HwECC_CTRL_EN_MCL24EN		(Hw3|Hw2|Hw1)					// MLC ECC24 Encoding Enable
#define	HwECC_CTRL_EN_MCL24DE		(Hw3|Hw2|Hw1|Hw0)				// MLC ECC24 Decoding Enable
#define	HwECC_CTRL_EN_DIS			~(Hw3|Hw2|Hw1|Hw0)				// ECC Disable

/*******************************************************************************
* ECC Error Status Register 
*******************************************************************************/
#define HwNFCECCERR_BASE						 (0xF05B0260)

#define	HwERR_NUM_ERR1				Hw0								// 1 Error Occurred(MLC4)
#define	HwERR_NUM_ERR2				Hw1								// 2 Error Occurred(MLC4)
#define	HwERR_NUM_ERR3				(Hw1|Hw0)						// 3 Error Occurred(MLC4)
#define	HwERR_NUM_ERR4				Hw2								// 4 Error Occurred(MLC4)
#define	HwERR_NUM_ERR5				(Hw2|Hw0)						// 5 Error Occurred(MLC4)
#define	HwERR_NUM_ERR6				(Hw2|Hw1)						// 6 Error Occurred(MLC4)
#define	HwERR_NUM_ERR7				(Hw2|Hw1|Hw0)					// 7 Error Occurred(MLC4)
#define	HwERR_NUM_ERR8				Hw3								// 8 Error Occurred(MLC4)
#define	HwERR_NUM_ERR9				(Hw3|Hw0)						// 9 Error Occurred(MLC4)
#define	HwERR_NUM_ERR10				(Hw3|Hw1)						// 10 Error Occurred(MLC4)
#define	HwERR_NUM_ERR11				(Hw3|Hw1|Hw0)					// 11 Error Occurred(MLC4)
#define	HwERR_NUM_ERR12				(Hw3|Hw2)						// 12 Error Occurred(MLC4)
#define	HwERR_NUM_ERR13				(Hw3|Hw2|Hw0)					// 13 Error Occurred(MLC4)
#define	HwERR_NUM_ERR14				(Hw3|Hw2|Hw1)					// 14 Error Occurred(MLC4)
#define	HwERR_NUM_ERR15				(Hw3|Hw2|Hw1|Hw0)				// 15 Error Occurred(MLC4)
#define	HwERR_NUM_ERR16				Hw4								// 16 Error Occurred(MLC4)
#define	HwERR_NUM_ERR17				(Hw4|Hw0)						// 17 Error Occurred(MLC4)
#define	HwERR_NUM_ERR18				(Hw4|Hw1)						// 18 Error Occurred(MLC4)
#define	HwERR_NUM_ERR19				(Hw4|Hw1|Hw0)					// 19 Error Occurred(MLC4)
#define	HwERR_NUM_ERR20				(Hw4|Hw2)						// 20 Error Occurred(MLC4)
#define	HwERR_NUM_ERR21				(Hw4|Hw2|Hw0)					// 21 Error Occurred(MLC4)
#define	HwERR_NUM_ERR22				(Hw4|Hw2|Hw1)					// 22 Error Occurred(MLC4)
#define	HwERR_NUM_ERR23				(Hw4|Hw2|Hw1|Hw0)				// 23 Error Occurred(MLC4)
#define	HwERR_NUM_ERR24				(Hw4|Hw3)						// 24 Error Occurred(MLC4)
#define	HwERR_NUM_CORIMP			(Hw4|Hw3|Hw0)					// Correction Impossible Error

#define	HwERR_NUM_NOERR				HwZERO							// No Error

/*******************************************************************************
*    13. SMC(Static Memory Controller) Register Define (Base Addr = 0xF05F0000)
********************************************************************************/
#define HwSMC_BASE								(0xF05F0000)
#define HwSMC_CSNCFG0							(0xF05F0020)

/*******************************************************************************
*    14. EDI(External Device Interface) Register Define (Base Addr = 0xF05F6000)
********************************************************************************/
#define HwEDI_BASE								(0xF05F6000)

/*******************************************************************************
*    15. IDE Register Define (Base Addr = 0xF0520000)
********************************************************************************/
#define HwIDE_BASE								(0xF0520000)

/*******************************************************************************
*    16. USB 1.1 Host Controller & Transceiver Register Define (Base Addr = 0xF0500000)
********************************************************************************/
#define HwUSBHOST_BASE							(0xF0500000)

/*******************************************************************************
*    17. USB 2.0 OTG Controller Register Define (Base Addr = 0xF0550000)
********************************************************************************/
#define HwUSB20OTG_BASE							(0xF0550000)
#define HwUSBPHYCFG_BASE						(0xF05F5028)

/*******************************************************************************
*    18. I2C Controller Register Define (Base Addr = 0xF0550000)
********************************************************************************/
#define HwI2C_CORE0_BASE						(0xF0530000)
#define HwI2C_CORE0_MASTER0_BASE				(0xF0530000)
#define HwI2C_CORE0_MASTER1_BASE				(0xF0530040)
#define HwI2C_CORE0_SLAVE_BASE					(0xF0530080)
#define HwI2C_CORE0_INT_BASE					(0xF05300C0)

#define HwI2C_CORE1_BASE						(0xF0530100)
#define HwI2C_CORE1_MASTER0_BASE				(0xF0530100)
#define HwI2C_CORE1_MASTER1_BASE				(0xF0530140)
#define HwI2C_CORE1_SLAVE_BASE					(0xF0530180)
#define HwI2C_CORE1_INT_BASE					(0xF05301C0)

#define HwI2CIRQ_BASE							(0xF0530300)
#define HwI2CDREQSEL_BASE						(0xF0530400)

/*******************************************************************************
*    19. PWM(Pulse Width Modulation) Register Define (Base Addr = 0xF05D0000)
********************************************************************************/
#define HwPWM_BASE								(0xF05D0000)
#define HwPDM_BASE								(0xF05D0000)

/*******************************************************************************
*    20. Remote Control Interface Register Define (Base Addr = 0xF05F3000)
********************************************************************************/
#define HwREMOTE_BASE							(0xF05F3000)

/*******************************************************************************
*    21. TSADC Interface Register Define (Base Addr = 0xF05F4000)
********************************************************************************/
#define HwTSADC_BASE							(0xF05F4000)

/*******************************************************************************
*    22. TSIF(Transport Stream Interface) Register Define (Base Addr = 0x)
********************************************************************************/
#define HwTSIF_BASE								(0xF0539000)
#define HwTSIF0_BASE							(0xF0539000)
#define HwTSIF1_BASE							(0xF0539100)
#define HwTSIF_PORTSEL_BASE						(0xF0539800)

/*******************************************************************************
*    23. UART Register Define (Base Addr = 0xF0531000)
********************************************************************************/
#define HwUART_BASE								(0xF0531000)
#define HwUART0_BASE							(0xF0531000)
#define HwUART1_BASE							(0xF0531100)
#define HwUART2_BASE							(0xF0531200)
#define HwUART3_BASE							(0xF0531300)
#define HwUART4_BASE							(0xF0531400)
#define HwUART5_BASE							(0xF0531500)
#define HwUART_PORTMUX_BASE						(0xF0531600)

/*******************************************************************************
*    24. MPEFEC Register Define (Base Addr = 0xF0510000)
********************************************************************************/
#define HwMPEFEC_BASE							(0xF0510000)

/*******************************************************************************
*    25. RTC(Real-Time Clock) Register Define (Base Addr = 0xF05F2000)
********************************************************************************/
#define HwRTC_BASE								(0xF05F2000)

/*******************************************************************************
*    26. IOBUS Configuration Register Define (Base Addr = 0xF05F5000)
********************************************************************************/
#define HwIOBUSCFG_BASE							(0xF05F5000)





/*******************************************************************************
*
*    TCC88x DataSheet PART 6 HSIO BUS
*
********************************************************************************/

/************************************************************************
*   4. PCIe(PCI Expresss)  (Base Addr = 0xF0800000) // R/W
*************************************************************************/
#define HwPCIE_BASE								(0xF0800000)
#define HwPCIE_DBI_BASE							(0xF0810000)

/************************************************************************
*   5. SATA Host 0/1 (Base Addr = 0xF0820000, 0xF0850000) // R/W
*************************************************************************/
#define HwSATAHOST0_BASE						(0xF0820000)
#define HwSATAHOST1_BASE						(0xF0850000)

/************************************************************************
*   6. SATA Device (Base Addr = 0xF0860000) // R/W
*************************************************************************/
#define HwSATADEVICE_BASE						(0xF0860000)

/************************************************************************
*   7. SATA(PCIe) PHY 0/1 (Base Addr = 0xF0830000, 0xF0870000) // R/W
*************************************************************************/
#define HwSATAPHY0_BASE							(0xF0830000)
#define HwSATAPHY1_BASE							(0xF0870000)

/************************************************************************
*   8. Ethernet(GMAC) (Base Addr = 0xF0840000) // R/W
*************************************************************************/
#define HwGMAC_BASE								(0xF0840000)

/************************************************************************
*   9. USB 2.0 Host (Base Addr = 0xF0880000, 0xF0890000) // R/W
*************************************************************************/
#define HwUSB20HOST_EHCI_BASE					(0xF0880000)
#define HwUSB20HOST_OHCI_BASE					(0xF0890000)

/************************************************************************
*   10. Cipher (Base Addr = 0xF08A2000) // R/W
*************************************************************************/
#define HwCIPHER_BASE							(0xF08A2000)

/************************************************************************
*   11. DMAX Controller (Base Addr = 0xF08A3000) // R/W
*************************************************************************/
#define HwDMAX_BASE								(0xF08A3000)

/************************************************************************
*   12. TS-Demux (Base Addr = 0xF08B0000) // R/W
*************************************************************************/
#define HwTSDEMUX_BASE							(0xF08B0000)

/************************************************************************
*   13. HSDMA Controller  (Base Addr = 0xF08C0000) // R/W
*************************************************************************/
#define HwHSDMA_BASE							(0xF08C0000)

/************************************************************************
*   14. HSIO BUS Configuration (Base Addr = 0xF08A0000) // R/W
*************************************************************************/
#define HwHSIOBUSCFG_BASE						(0xF08A0000)
#define HwHSIOBUSMATRIX_BASE					(0xF08A1000) 


/*******************************************************************************
*
*    TCC88x DataSheet PART 7 DISPLAY BUS
*
********************************************************************************/

/************************************************************************
*   4. LCD Controller (Base Addr = 0xF0200000) // R/W
*************************************************************************/
//#define HwLCDC_BASE								(0xF0200000)
//#define HwLCDC0_BASE							(0xF0200000)
//#define HwLCDLUT0_BASE							(0xF0200400)
//#define HwLCDC1_BASE							(0xF0204000)
//#define HwLCDLUT1_BASE							(0xF0204400)
#define	HwLCDC0_BASE				*(volatile unsigned long *)0xF0200000	// LCDC0 Control Base Register
#define HwLCDLUT0_BASE				*(volatile unsigned long *)0xF0200400	// LCD LUT 0 Base Register
#define	HwLCDC1_BASE				*(volatile unsigned long *)0xF0204000	// LCDC1 Control Base Register
#define HwLCDLUT1_BASE				*(volatile unsigned long *)0xF0204400	// LCD LUT 1 Base Register

/************************************************************************
*   5. LCD System Interface (Base Addr = ) // R/W
*************************************************************************/
#define HwLCDSI_BASE							(0xF020C000)


/************************************************************************
*   6. Memory To Memory Scaler (Base Addr = 0xF0210000) // R/W
*************************************************************************/
#define HwM2MSCALER_BASE						(0xF0210000)
//#define HwM2MSCALER0_BASE						(0xF0210000)
//#define HwM2MSCALER1_BASE						(0xF0220000)

#define HwSCALERPOSTFILTER_BASE_O					(0xF025B000)
#define HwSCALERPOSTFILTER_BASE					*(volatile unsigned long *)0xF025B000
#define HwM2MSCALER0_BASE           *(volatile unsigned long *)0xF0210000
#define HwM2MSCALER1_BASE           *(volatile unsigned long *)0xF0220000

/************************************************************************
*   7. NTSC/PAL Encoder Composite Output (Base Addr = 0xF0240000) // R/W
*************************************************************************/
#define HwNTSCPAL_BASE							(0xF0240000)
#define HwTVENCODER_BASE						(0xF0240000)
#define HwNTSCPAL_ENCODER_CTRL_BASE				(0xF0240800)

/************************************************************************
*   8. HDMI (Base Addr = 0xF0254000) // R/W
*************************************************************************/
#define HwHDMI_BASE								(0xF0254000)
#define HwHDMICTRL_BASE							(0xF0254000)
#define HwHDMICORE_BASE							(0xF0255000)
#define HwHDMIAES_BASE							(0xF0256000)
#define HwHDMISPDIF_BASE						(0xF0257000)
#define HwHDMII2S_BASE							(0xF0258000)
#define HwHDMICEC_BASE							(0xF0259000)

/************************************************************************
*   9. Video and Image Quality Enhancer(VIQE) (Base Addr = ) // R/W
*************************************************************************/
//#define HwVIQE_BASE								(0xF0252000)
#define HwVIQE_BASE                 *(volatile unsigned long *)0xF0252000

/************************************************************************
*   10. MIPI(Mobile Industry Processor Interface) (Base Addr = ) // R/W
*************************************************************************/
#define HwMIPI_BASE								(0xF025B000)

/************************************************************************
*   11. DDI_CONFIG (Base Addr = 0xF0250000) // R/W
*************************************************************************/
//#define HwDDI_CONFIG_BASE						(0xF0251000)
#define HwDDI_CONFIG_BASE           *(volatile unsigned long *)0xF0251000

/************************************************************************
*   12. DDI_CACHE (Base Addr = ) // R/W
*************************************************************************/
#define HwDDICTRL_BASE							(0xF0250000)
#define HwDDICACHE_BASE							(0xF0250000)
#define HwDDI_CACHE_BASE            *(volatile unsigned long *)0xF0250000

/*******************************************************************************
*
*    TCC88x DataSheet PART 8 VIDEO BUS
*
********************************************************************************/
/************************************************************************
*   4. JPEG Encoder (Base Addr = 0xF0780000) // R/W
*************************************************************************/
#define HwJPEGENC_BASE 							(0xF0780000)
#define HwJPEGENCODER_BASE						*(volatile unsigned long *)0xF0780000

/************************************************************************
*   5. Video Codec (Base Addr = 0xF0700000) // R/W
*************************************************************************/
#define HwVIDEOCODEC_BASE 						(0xF0700000) 

/************************************************************************
*   6. Video Cache (Base Addr = 0xF0710000) // R/W
*************************************************************************/
#define HwVIDEOCACHE_BASE_O 						(0xF0710000) 
#define HwVIDEOCACHE_BASE 							*(volatile unsigned long *)0xF0710000

/************************************************************************
*   7. Video Bus Configuration (Base Addr = 0xF0720000) // R/W
*************************************************************************/
#define HwVIDEOBUSCFG_BASE_O 						(0xF0720000) 
#define HwVIDEOBUSCFG_BASE 							*(volatile unsigned long *)0xF0720000

/*******************************************************************************
*
*    TCC88x DataSheet PART 9 CAMERA BUS
*
********************************************************************************/

/************************************************************************
*   4. Camera Interface (Base Addr = 0xF0900000) // R/W
*************************************************************************/
#define HwCIF_BASE								(0xF0900000)
#define HwCIFEFFECTOR_BASE						(0xF0900100)
#define HwCIFSCALER_BASE						(0xF0900200)


/************************************************************************
*   5. ISP(Image Signal Processor) (Base Addr = 0xF0910000) // R/W
*************************************************************************/
#define HwISPBASE								(0xF0910000)
#define HwISPIMGEFF_BASE						(0xF0910200)
#define HwISPSI_BASE							(0xF0910300)
#define HwISPISP_BASE							(0xF0910400)
#define HwISPFLASH_BASE							(0xF0910660)
#define HwISPSHUT_BASE							(0xF0910680)
#define HwISPCPROC_BASE							(0xF0910800)
#define HwISPMRSZ_BASE							(0xF0910C00)
#define HwISPSRSZ_BASE							(0xF0911000)
#define HwISPMI_BASE							(0xF0911400)
#define HwISPJPE_BASE							(0xF0911800)
#define HwISPMIPI_BASE							(0xF0911C00)

/************************************************************************
*   6. CAMBUS Configuration (Base Addr = 0xF0920000) // R/W
*************************************************************************/
#define HwCAMBUSMATRIX_BASE						(0xF0920000)
#define HwCAMBUSCFG_BASE						(0xF0930000)


#endif /*__TCC88x_H__*/

