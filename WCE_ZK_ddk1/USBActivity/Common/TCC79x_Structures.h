/************************************************************************
*	TCC79x WinCE Board Support Package
*	------------------------------------------------
*
*	FUNCTION	: TCC79x Structures DEFINE
*	MODEL		: TCC79x WinCE
*	CPU	NAME	: TCC79x
*	SOURCE		: TCC79xStructures.H
*
*	START DATE	: 2007 Aug. 21
*	MODIFY DATE	:
*	DEVISION	: DEPT. 4GROUP SYSTME 3 TEAM
*				: TELECHIPS, INC.
************************************************************************/

/************************************************************************
*	TCC79x Internal Register Definition File
************************************************************************/
#ifndef	__TCC79xSTRUCTURES_H__
#define	__TCC79xSTRUCTURES_H__


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


//#define	HwVERSION								*(volatile unsigned long *)0xE0001FFC
/************************************************************************
*	LCD INTERFACE Definition
************************************************************************/
//LCDC Register Map (Base Address = 0xF0000000)
//#define HwLCDC			0xF0000000
typedef struct _LCD{
	volatile unsigned int		LCTRL;				// 0x00 W 0x00000000 LCD Control Register
	volatile unsigned int		LBC;				// 0x04 W 0x00000000 LCD Background Color Register
	volatile unsigned int		LCLKDIV;			// 0x08 W 0x00000000 LCD Clock Divider Register
	volatile unsigned int		LHTIME1;			// 0x0C W 0x00000000 LCD Horizontal Timing Register 1
	volatile unsigned int		LHTIME2;			// 0x10 W 0x00000000 LCD Horizontal Timing Register 2
	volatile unsigned int		LVTIME1;			// 0x14 W 0x00000000 LCD Vertical Timing Register 1
	volatile unsigned int		LVTIME2;			// 0x18 W 0x00000000 LCD Vertical Timing Register 2
	volatile unsigned int		LVTIME3;			// 0x1C W 0x00000000 LCD Vertical Timing Register 3
	volatile unsigned int		LVTIME4;			// 0x20 W 0x00000000 LCD Vertical Timing Register 4
	volatile unsigned int		LLUTR;				// 0x24 W 0x00000000 LCD Lookup Register for Red
	volatile unsigned int		LLUTG;				// 0x28 W 0x00000000 LCD Lookup Register for Green
	volatile unsigned int		LLUTB;				// 0x2C W 0x00000000 LCD Lookup Register for Blue
	volatile unsigned int		LDP7L;				// 0x30 W 0x4d2b3401 LCD Modulo 7 Dithering Pattern (low)
	volatile unsigned int		LDP7H;				// 0x34 W 0x0000003f LCD Modulo 7 Dithering Pattern (high)
	volatile unsigned int		LDP5;				// 0x38 W 0x1d0b0610 LCD Modulo 5 Dithering Pattern Register
	volatile unsigned int		LDP4;				// 0x3C W 0x00000768 LCD Modulo 4 Dithering Pattern Register
	volatile unsigned int		LDP3;				// 0x40 W 0x00000034 LCD 3-bit Dithering Pattern Register
	volatile unsigned int		LCP1;				// 0x44 W 0x000000ff LCD Clipping Register1
	volatile unsigned int		LCP2;				// 0x48 W 0x000000ff LCD Clipping Register2
	volatile unsigned int		LK1;				// 0x4C W 0x00000000 LCD Keying Register 1
	volatile unsigned int		LK2;				// 0x50 W 0x00000000 LCD Keying Register 2
	volatile unsigned int		LKM1;				// 0x54 W 0x00000000 LCD Keying Mask Register 1
	volatile unsigned int		LKM2;				// 0x58 W 0x00000000 LCD Keying Mask Register 2
	volatile unsigned int		LDS;				// 0x5C W 0x00000000 LCD Display Size Register
	volatile unsigned int		LSTATUS;			// 0x60 R/CLR 0x00000000 LCD Status Register
	volatile unsigned int		LIM;				// 0x64 W 0x0000001f LCD Interrupt Register.
	volatile unsigned int		LI0C;				// 0x68 W 0x00000000 LCD Image 0 Control Register
	volatile unsigned int		LI0P;				// 0x6C W 0x00000000 LCD Image 0 Position Register
	volatile unsigned int		LI0S;				// 0x70 W 0x00000000 LCD Image 0 Size Register
	volatile unsigned int		LI0BA0;				// 0x74 W 0x00000000 LCD Image 0 Base Address 0 Register.
	volatile unsigned int		LI0CA;				// 0x78 W 0x00000000 LCD Image 0 Current Address Register.
	volatile unsigned int		LI0BA1;				// 0x7C W 0x00000000 LCD Image 0 Base Address 1 Register
	volatile unsigned int		LI0BA2;				// 0x80 W 0x00000000 LCD Image 0 Base Address 2 Register
	volatile unsigned int		LI0O;				// 0x84 W 0x00000000 LCD Image 0 Offset Register
	volatile unsigned int		LI0SR;				// 0x88 W 0x00000000 LCD Image 0 Scale ratio
	volatile unsigned int		LI1C;				// 0x8C W 0x00000000 LCD Image 1 Control Register
	volatile unsigned int		LI1P;				// 0x90 W 0x00000000 LCD Image 1 Position Register
	volatile unsigned int		LI1S;				// 0x94 W 0x00000000 LCD Image 1 Size Register
	volatile unsigned int		LI1BA0;				// 0x98 W 0x00000000 LCD Image 1 Base Address 0 Register.
	volatile unsigned int		LI1CA;				// 0x9C W 0x00000000 LCD Image 1 Current Address Register.
	volatile unsigned int		NOTDEFINE0;			// 0xA0 0x00000000
	volatile unsigned int		NOTDEFINE1;			// 0xA4 0x00000000
	volatile unsigned int		LI1O;				// 0xA8 W 0x00000000 LCD Image 1 Offset Register
	volatile unsigned int		LI1SR;				// 0xAC W 0x00000000 LCD Image 1 Scale ratio-
	volatile unsigned int		LI2C;				// 0xB0 W 0x00000000 LCD Image 2 Control Register
	volatile unsigned int		LI2P;				// 0xB4 W 0x00000000 LCD Image 2 Position Register
	volatile unsigned int		LI2S;				// 0xB8 W 0x00000000 LCD Image 2 Size Register
	volatile unsigned int		LI2BA0;				// 0xBC W 0x00000000 LCD Image 2 Base Address 0 Register.
	volatile unsigned int		LI2CA;				// 0xC0 W 0x00000000 LCD Image 2 Current Address Register.
	volatile unsigned int		NOTDEFINE2;			// 0xC4 0x00000000
	volatile unsigned int		NOTDEFINE3;			// 0xC8 0x00000000
	volatile unsigned int		LI2O;				// 0xCC W 0x00000000 LCD Image 2 Offset Register
	volatile unsigned int		LI2SR;				// 0xD0 W 0x00000000 LCD Image 2 Scale ratio
	volatile unsigned int		DLCTRL;				// 0xD4 W 0x00000000 Dual LCD Control Register
	volatile unsigned int		NOTDEFINE4;			// 0xD8 0x00000000
	volatile unsigned int		DLCSA0;				// 0xDC W 0x00000000 Dual LCD Configuration Start Address 0
	volatile unsigned int		DLCSA1;				// 0xE0 W 0x00000000 Dual LCD Configuration Start Address 1
	//volatile unsigned int		LCDLUT;				// 0xC00 W - LCD Lookup Table.
}LCD, *PLCD;

#define	HwPORTCFG0								*(volatile unsigned long *)0xF005A000	// R/W, Port Configuration Register 0
	#define	HwPORTCFG0_LPD23(X)	((X)*Hw28)	// LPD[23]		= LPD[23]		| -			| GPIOC[23]	| SD_CMD(0)	| MS_BUS(0)	| SFRM(10)
	#define	HwPORTCFG0_LPD22(X)	((X)*Hw24)	// LPD[22]		= LPD[22]		| -			| GPIOC[22]	| SD_CLK(0)	| MS_CLK(0)	| SCLK(10)
	#define	HwPORTCFG0_LPD21(X)	((X)*Hw20)	// LPD[21]		= LPD[21]		| -			| GPIOC[21]	| SD_D0(0)	| MS_D0(0)	| SDI(10)
	#define	HwPORTCFG0_LPD20(X)	((X)*Hw16)	// LPD[20]		= LPD[20]		| -			| GPIOC[20]	| SD_D1(0)	| MS_D1(0)	| SDO(10)
	#define	HwPORTCFG0_LPD19(X)	((X)*Hw12)	// LPD[19:18]		= LPD[19:18]	| -			| GPIOC[19:18]	| SD_D[2:3](0)	| MS_D[2:3](0)	| -
	#define	HwPORTCFG0_LCD18(X)	((X)*Hw8)	// LPD[17:16]		= LPD[17:16]	| LXD[17:16]	| GPIOC[17:16]	| -			| -			| -
	#define	HwPORTCFG0_LCD16(X)	((X)*Hw4)	// LPD[15:8]		= LPD[15:8]	| LXD[15:8]	| GPIOC[15:8]	| -			| -			| -
	#define	HwPORTCFG0_LCD8(X)		((X)*Hw0)	// LPD[7:0]		= LPD[7:0]	| LXD[7:0]	| GPIOC[7:0]	| -			| -			| -

#define	HwPORTCFG1								*(volatile unsigned long *)0xF005A004	// R/W, Port Configuration Register 1
	#define	HwPORTCFG1_LDE(X)		((X)*Hw28)	// LBIAS			= LDE		| LWEN		| GPIOC[25]	| -			| -			| -
	#define	HwPORTCFG1_LCK(X)		((X)*Hw24)	// LCK			= LCK		| LOEN		| GPIOC[26]	| -			| -			| -
	#define	HwPORTCFG1_LHS(X)		((X)*Hw20)	// LHS			= LHS		| LXA		| GPIOC[27]	| -			| -			| -
	#define	HwPORTCFG1_LVS(X)		((X)*Hw16)	// LVS			= LVS		| LCSN[0]		| GPIOC[28]	| -			| -			| -
	#define	HwPORTCFG1_LCS(X)		((X)*Hw12)	// GPIOC[29]		= GPIOC[29]	| LCSN[1]		| GPIOC[29]	| -			| -			| -
	#define	HwPORTCFG1_GPIOC30(X)	((X)*Hw8)	// GPIOC[30]		= GPIOC[30]	| GPIOC[30]	| GPIOC[30]	| -			| -			| -
	#define	HwPORTCFG1_GPIOC31(X)	((X)*Hw4)	// GPIOC[31]		= GPIOC[31]	| GPIOC[31]	| GPIOC[31]	| -			| -			| -
	#define	HwPORTCFG1_GPIOF27(X)	((X)*Hw0)	// GPIOF[27]		= -			| GPIOF[27]	| SFRM(9)		| NANDRDY3	| -			| LDE_IN

#define	HwPORTCFG2								*(volatile unsigned long *)0xF005A008	// R/W, Port Configuration Register 2
	#define	HwPORTCFG2_GPIOF26(X)	((X)*Hw28)	// GPIOF[26]		= -			| GPIOF[26]	| SCLK(9)		| NDRDY2		| HDDRDY		| LCLK_IN
	#define	HwPORTCFG2_GPIOF25(X)	((X)*Hw24)	// GPIOF[25]		= -			| GPIOF[25]	| SDI(9)		| NDCSN3		| -			| LVS_IN
	#define	HwPORTCFG2_HPCSN_L(X)	((X)*Hw20)	// HPCSN_L		= HPCSN_L	| GPIOF[24]	| SDO(9)		| NDCSN2		| HDDAK		| LHS_IN
	#define	HwPORTCFG2_HPCTRL(X)	((X)*Hw16)	/*
													HPINTO		= HPINTO	| GPIOF[23]	| MS_CLK(1)	| SD_CLK(1)	| HDDRQ		| LPDIN[23]
													HPXA[1]		= HPXA[1]	| GPIOF[22]	| MS_BUS(1)	| SD_CMD(1)	| HDDXA[2]	| LPDIN[22]
													HPXA[0]		= HPXA[0]	| GPIOF[21]	| MS_D0(1)	| SD_D0(1)	| HDDXA[1]	| LPDIN[21]
													HPWRN		= HPWRN		| GPIOF[19]	| MS_D2(1)	| SD_D2(1)	| HDDIOW	| LPDIN[19]
													HPRDN		= HPRDN		| GPIOF[18]	| MS_D3(1)	| SD_D3(1)	| HDDIOR	| LPDIN[18]
												*/
	#define	HwPORTCFG2_HPXD17(X)	((X)*Hw12)	/*
													HPXD[17]	= HPXD[17]	| GPIOF[17]	| SD_CLK(3)	| SD_CLK(2)	| HDDCSN1	| LPDIN[17]
													HPXD[16]	= HPXD[16]	| GPIOF[16]	| SD_CMD(3)	| SD_CMD(2)	| HDDCSN0	| LPDIN[16]
												*/
	#define	HwPORTCFG2_HPXD15(X)	((X)*Hw8)	// HPXD[15:12]	= HPXD[15:12]	| GPIOF[15:12]	| NDXD[15:12]	| SD_D[7:4](2)	| HDDXD[15:12]| LPDIN[15:12]
	#define	HwPORTCFG2_HPXD11(X)	((X)*Hw4)	// HPXD[11:8]		= HPXD[11:8]	| GPIOF[11:8]	| NDXD[11:8]	| SD_D[3:0](2)	| HDDXD[11:8]	| LPDIN[11:8]
	#define	HwPORTCFG2_HPXD7(X)	((X)*Hw0)	// HPXD[7]		= HPXD[7]	| GPIOF[7]	| SD_D7(3)	| SFRM(8)		| HDDXD[7]	| LPDIN[7]

#define	HwPORTCFG3								*(volatile unsigned long *)0xF005A00C	// R/W, Port Configuration Register 3
	#define	HwPORTCFG3_HPXD6(X)	((X)*Hw28)	// HPXD[6]		= HPXD[6]	| GPIOF[6]	| SD_D6(3)	| SCLK(8)		| HDDXD[6]	| LPDIN[6]
	#define	HwPORTCFG3_HPXD5(X)	((X)*Hw24)	// HPXD[5]		= HPXD[5]	| GPIOF[5]	| SD_D5(3)	| SDI(8)		| HDDXD[5]	| LPDIN[5]
	#define	HwPORTCFG3_HPXD4(X)	((X)*Hw20)	// HPXD[4]		= HPXD[4]	| GPIOF[4]	| SD_D4(3)	| SDO(8)		| HDDXD[4]	| LPDIN[4]
	#define	HwPORTCFG3_HPXD3(X)	((X)*Hw16)	// HPXD[3]		= HPXD[3]	| GPIOF[3]	| SD_D3(3)	| SFRM(7)		| HDDXD[3]	| LPDIN[3]
	#define	HwPORTCFG3_HPXD2(X)	((X)*Hw12)	// HPXD[2]		= HPXD[2]	| GPIOF[2]	| SD_D2(3)	| SCLK(7)		| HDDXD[2]	| LPDIN[2]
	#define	HwPORTCFG3_HPXD1(X)	((X)*Hw8)	// HPXD[1]		= HPXD[1]	| GPIOF[1]	| SD_D1(3)	| SDI(7)		| HDDXD[1]	| LPDIN[1]
	#define	HwPORTCFG3_HPXD0(X)	((X)*Hw4)	// HPXD[0]		= HPXD[0]	| GPIOF[0]	| SD_D0(3)	| SDO(7)		| HDDXD[0]	| LPDIN[0]
	#define	HwPORTCFG3_SCMD0(X)	((X)*Hw0)	// SCMD0			= SFRM(6)	| GPIOD[5]	| -			| -			| -			| -

#define	HwPORTCFG4								*(volatile unsigned long *)0xF005A010	// R/W, Port Configuration Register 4
	#define	HwPORTCFG4_SCLK0(X)	((X)*Hw28)	// SCLK0			= SCLK(6)		| GPIOD[6]	| -			| -			| -			| -
	#define	HwPORTCFG4_SDI0(X)		((X)*Hw24)	// SDI0			= SDI(6)		| GPIOD[7]	| -			| -			| -			| -
	#define	HwPORTCFG4_SDO0(X)		((X)*Hw20)	// SDO0			= SDO(6)		| GPIOD[8]	| -			| -			| -			| -
	#define	HwPORTCFG4_GPIOA2(X)	((X)*Hw16)	// GPIOA[2]		= GPIOA[2]	| CLK_OUT0	| -			| -			| -			| -
	#define	HwPORTCFG4_GPIOA3(X)	((X)*Hw12)	// GPIOA[3]		= GPIOA[3]	| CLK_OUT1	| -			| -			| -			| -
	#define	HwPORTCFG4_GPIOA4(X)	((X)*Hw8)	// GPIOA[4]*		= GPIOA[4]	| WDTRSTO	| TCO3		| -			| -			| -
	#define	HwPORTCFG4_GPIOA5(X)	((X)*Hw4)	// GPIOA[5]*		= GPIOA[5]	| -			| TCO2		| -			| -			| -
	#define	HwPORTCFG4_CSN_CS0(X)	((X)*Hw0)	// CSN_CS0		= CSN_CS0	| GPIOC[24]	| -			| -			| -			| -

#define	HwPORTCFG5								*(volatile unsigned long *)0xF005A014	// R/W, Port Configuration Register 5
	#define	HwPORTCFG5_CSN_NOR(X)	((X)*Hw28)	// CSN_NOR		= CSN_NOR	| GPIOF[28]	| -			| -			| -			| -
	#define	HwPORTCFG5_GPIOB0(X)	((X)*Hw24)	// GPIOB[0]		= GPIOB[0]	| NDXD[0]	| SD_D0(5)	| SFRM(3)		| -			| SRAMIF_XD[0]
	#define	HwPORTCFG5_GPIOB1(X)	((X)*Hw20)	// GPIOB[1]		= GPIOB[1]	| NDXD[1]	| SD_D1(5)	| SCLK(3)		| -			| SRAMIF_XD[1]
	#define	HwPORTCFG5_GPIOB2(X)	((X)*Hw16)	// GPIOB[2]		= GPIOB[2]	| NDXD[2]	| SD_D2(5)	| SDI(3)		| -			| SRAMIF_XD[2]
	#define	HwPORTCFG5_GPIOB3(X)	((X)*Hw12)	// GPIOB[3]		= GPIOB[3]	| NDXD[3]	| SD_D3(5)	| SDO(3)		| -			| SRAMIF_XD[3]
	#define	HwPORTCFG5_GPIOB4(X)	((X)*Hw8)	// GPIOB[4]		= GPIOB[4]	| NDXD[4]	| SD_D4(5)	| SFRM(2)		| -			| SRAMIF_XD[4]
	#define	HwPORTCFG5_GPIOB5(X)	((X)*Hw4)	// GPIOB[5]		= GPIOB[5]	| NDXD[5]	| SD_D5(5)	| SCLK(2)		| -			| SRAMIF_XD[5]
	#define	HwPORTCFG5_GPIOB6(X)	((X)*Hw0)	// GPIOB[6]		= GPIOB[6]	| NDXD[6]	| SD_D6(5)	| SDI(2)		| -			| SRAMIF_XD[6]

#define	HwPORTCFG6								*(volatile unsigned long *)0xF005A018	// R/W, Port Configuration Register 6
	#define	HwPORTCFG6_GPIOB7(X)	((X)*Hw28)	// GPIOB[7]		= GPIOB[7]	| NDXD[7]	| SD_D7(5)	| SDO(2)		| -			| SRAMIF_XD[7]
	#define	HwPORTCFG6_GPIOB8(X)	((X)*Hw24)	// GPIOB[8]		= GPIOB[8]	| NDOEN		| SD_CMD(5)	| -			| -			| SRAMIF_OEN
	#define	HwPORTCFG6_GPIOB9(X)	((X)*Hw20)	// GPIOB[9]		= GPIOB[9]	| NDWEN		| SD_CLK(5)	| -			| -			| SRAMIF_WEN
	#define	HwPORTCFG6_GPIOB10(X)	((X)*Hw16)	// GPIOB[10]		= GPIOB[10]	| NDCSN0		| SD_D0(6)	| MS_D0(3)	| SFRM(1)		| SRAMIF_CSN0
	#define	HwPORTCFG6_GPIOB11(X)	((X)*Hw12)	// GPIOB[11]		= GPIOB[11]	| NDCSN1		| SD_D1(6)	| MS_D1(3)	| SCLK(1)		| SRAMIF_CSN1
	#define	HwPORTCFG6_GPIOB12(X)	((X)*Hw8)	// GPIOB[12]		= GPIOB[12]	| NDCLE		| SD_D2(6)	| MS_D2(3)	| SDI(1)		| SRAMIF_XA[0]
	#define	HwPORTCFG6_GPIOB13(X)	((X)*Hw4)	// GPIOB[13]		= GPIOB[13]	| NDALE		| SD_D3(6)	| MS_D3(3)	| SDO(1)		| SRAMIF_XA[1]
	#define	HwPORTCFG6_GPIOB14(X)	((X)*Hw0)	// GPIOB[14]		= GPIOB[14]	| NDRDY0		| SD_CMD(6)	| MS_BUS(3)	| -			| -

#define	HwPORTCFG7								*(volatile unsigned long *)0xF005A01C	// R/W, Port Configuration Register 7
	#define	HwPORTCFG7_GPIOB15(X)	((X)*Hw28)	// GPIOB[15]		= GPIOB[15]	| NDRDY1		| SD_CLK(6)	| MS_CLK(3)	| -			| -
	#define	HwPORTCFG7_SCMD1(X)	((X)*Hw24)	// SCMD1			= SFRM(5)	| GPIOD[9]	| -			| -			| -			| -
	#define	HwPORTCFG7_SCLK1(X)	((X)*Hw20)	// SCLK1			= SCLK(5)		| GPIOD[10]	| -			| -			| -			| -
	#define	HwPORTCFG7_SDI1(X)		((X)*Hw16)	// SDI1			= SDI(5)		| GPIOD[11]	| -			| -			| -			| -
	#define	HwPORTCFG7_SDO1(X)		((X)*Hw12)	// SDO1			= SDO(5)		| GPIOD[12]	| -			| -			| -			| -
	#define	HwPORTCFG7_GPIOA6(X)	((X)*Hw8)	// GPIOA[6]		= GPIOA[6]	| SPDIFTX		| TCO1		| -			| -			| -
	#define	HwPORTCFG7_GPIOA7(X)	((X)*Hw4)	// GPIOA[7]		= GPIOA[7]	| EXTCLKI		| TCO0		| -			| -			| -
	#define	HwPORTCFG7_GPIOA8(X)	((X)*Hw0)	// GPIOA[8]		= GPIOA[8]	| SCL1		| -			| -			| -			| -

#define	HwPORTCFG8								*(volatile unsigned long *)0xF005A020	// R/W, Port Configuration Register 8
	#define	HwPORTCFG8_GPIOA9(X)	((X)*Hw28)	// GPIOA[9]		= GPIOA[9]	| SDA1		| -			| -			| -			| -
	#define	HwPORTCFG8_GPIOA10(X)	((X)*Hw24)	// GPIOA[10]		= GPIOA[10]	| CBCLK		| -			| -			| -			| -
	#define	HwPORTCFG8_GPIOA11(X)	((X)*Hw20)	// GPIOA[11]		= GPIOA[11]	| CLRCK		| -			| -			| -			| -
	#define	HwPORTCFG8_GPIOA12(X)	((X)*Hw16)	// GPIOA[12]		= GPIOA[12]	| CDATA		| -			| -			| -			| -
	#define	HwPORTCFG8_AIN0(X)		((X)*Hw12)	// AIN[0]			= AIN[0]		| GPIOE[24]	| -			| -			| -			| -
	#define	HwPORTCFG8_AIN1(X)		((X)*Hw8)	// AIN[1]			= AIN[1]		| GPIOE[25]	| -			| -			| -			| -
	#define	HwPORTCFG8_AIN2(X)		((X)*Hw4)	// AIN[2]			= AIN[2]		| GPIOE[26]	| SD_CMD(7)	| MS_BUS(4)	| -			| -
	#define	HwPORTCFG8_AIN3(X)		((X)*Hw0)	// AIN[3]			= AIN[3]		| GPIOE[27]	| SD_CLK(7)	| MS_CLK(4)	| -			| -

#define	HwPORTCFG9								*(volatile unsigned long *)0xF005A024	// R/W, Port Configuration Register 9
	#define	HwPORTCFG9_AIN4(X)		((X)*Hw28)	// AIN[4]			= AIN[4]		| GPIOE[28]	| SD_D0(7)	| MS_D0(4)	| SFRM(0)		| -
	#define	HwPORTCFG9_AIN5(X)		((X)*Hw24)	// AIN[5]			= AIN[5]		| GPIOE[29]	| SD_D1(7)	| MS_D1(4)	| SCLK(0)		| -
	#define	HwPORTCFG9_AIN6(X)		((X)*Hw20)	// AIN[6]			= AIN[6]		| GPIOE[30]	| SD_D2(7)	| MS_D2(4)	| SDI(0)		| -
	#define	HwPORTCFG9_AIN7(X)		((X)*Hw16)	// AIN[7]			= AIN[7]		| GPIOE[31]	| SD_D3(7)	| MS_D3(4)	| SDO(0)		| -
	#define	HwPORTCFG9_UTXD0(X)	((X)*Hw12)	// UTXD(0)		= UTXD(0)	| GPIOE[0]	| -			| -			| -			| -
	#define	HwPORTCFG9_URXD0(X)	((X)*Hw8)	// URXD(0)		= URXD(0)	| GPIOE[1]	| -			| -			| -			| -
	#define	HwPORTCFG9_UCTS0(X)	((X)*Hw4)	// UCTS(0)		= UCTS(0)		| GPIOE[2]	| UTXD(4)		| -			| -			| -
	#define	HwPORTCFG9_URTS0(X)	((X)*Hw0)	// URTS(0)		= URTS(0)		| GPIOE[3]	| URXD(4)		| -			| -			| -

#define	HwPORTCFG10							*(volatile unsigned long *)0xF005A028	// R/W, Port Configuration Register 10
	#define	HwPORTCFG10_UTXD1(X)	((X)*Hw28)	// UTXD(1)		= UTXD(1)	| GPIOE[4]	| -			| -			| -			| -
	#define	HwPORTCFG10_URXD1(X)	((X)*Hw24)	// URXD(1)		= URXD(1)	| GPIOE[5]	| -			| -			| -			| -
	#define	HwPORTCFG10_UCTS1(X)	((X)*Hw20)	// UCTS(1)		= UCTS(1)		| GPIOE[6]	| UTXD(5)		| SD_CLK(4)	| MS_CLK(2)	| -
	#define	HwPORTCFG10_URTS1(X)	((X)*Hw16)	// URTS(1)		= URTS(1)		| GPIOE[7]	| URXD(5)		| SD_CMD(4)	| MS_BUS(2)	| -
	#define	HwPORTCFG10_UTXD2(X)	((X)*Hw12)	// UTXD(2)		= UTXD(2)	| GPIOE[8]	| SFRM(4)		| SD_D0(4)	| MS_D0(2)	| -
	#define	HwPORTCFG10_URXD2(X)	((X)*Hw8)	// URXD(2)		= URXD(2)	| GPIOE[9]	| SCLK(4)		| SD_D1(4)	| MS_D1(2)	| -
	#define	HwPORTCFG10_UTXD3(X)	((X)*Hw4)	// UTXD(3)		= UTXD(3)	| GPIOE[10]	| SDI(4)		| SD_D2(4)	| MS_D2(2)	| -
	#define	HwPORTCFG10_URXD3(X)	((X)*Hw0)	// URXD(3)		= URXD(3)	| GPIOE[11]	| SDO(4)		| SD_D3(4)	| MS_D3(2)	| -

#define	HwPORTCFG11							*(volatile unsigned long *)0xF005A02C	// R/W, Port Configuration Register 11
	#define	HwPORTCFG11_BM(X)		((X)*Hw28)	// BM[2:0]		= BM[2:0]		| GPIOF[31:29]	| -			| -			| -			| -
	#define	HwPORTCFG11_BCLK(X)	((X)*Hw24)	// BCLK			= BCLK		| GPIOD[0]	| -			| -			| -			| -
	#define	HwPORTCFG11_LRCK(X)	((X)*Hw20)	// LRCK			= LRCK		| GPIOD[1]	| -			| -			| -			| -
	#define	HwPORTCFG11_MCLK(X)	((X)*Hw16)	// MCLK			= MCLK		| GPIOD[2]	| -			| -			| -			| -
	#define	HwPORTCFG11_DAO(X)		((X)*Hw12)	// DAO			= DAO		| GPIOD[3]	| -			| -			| -			| -
	#define	HwPORTCFG11_DAI(X)		((X)*Hw8)	// DAI			= DAI		| GPIOD[4]	| -			| -			| -			| -
	#define	HwPORTCFG11_GPIOA0(X)	((X)*Hw4)	/*
													GPIOA[0]		= GPIOA[0]	| SCL0		| -			| -			| -			| -
													GPIOA[1]		= GPIOA[1]	| SDA0		| -			| -			| -			| -
												*/
	#define	HwPORTCFG11_CCKI(X)	((X)*Hw0)	// CCKI			= CCKI		| GPIOE[20]	| -			| -			| -			| -

#define	HwPORTCFG12							*(volatile unsigned long *)0xF005A030	// R/W, Port Configuration Register 12
	#define	HwPORTCFG12_CCKO(X)	((X)*Hw28)	// CCKO			= CCKO		| GPIOE[23]	| -			| -			| -			| -
	#define	HwPORTCFG12_CVS(X)		((X)*Hw24)	// CVS			= CVS		| GPIOE[21]	| -			| -			| -			| -
	#define	HwPORTCFG12_CHS(X)		((X)*Hw20)	// CHS			= CHS		| GPIOE[22]	| -			| -			| -			| -
	#define	HwPORTCFG12_CPD0(X)	((X)*Hw16)	// CPD[0]			= CPD[0]		| GPIOE[12]	| -			| -			| -			| -
	#define	HwPORTCFG12_CPD1(X)	((X)*Hw12)	// CPD[1]			= CPD[1]		| GPIOE[13]	| -			| -			| -			| -
	#define	HwPORTCFG12_CPD2(X)	((X)*Hw8)	// CPD[2]			= CPD[2]		| GPIOE[14]	| -			| -			| -			| -
	#define	HwPORTCFG12_CPD3(X)	((X)*Hw4)	// CPD[3]			= CPD[3]		| GPIOE[15]	| -			| -			| -			| -
	#define	HwPORTCFG12_CPD4(X)	((X)*Hw0)	// CPD[4]			= CPD[4]		| GPIOE[16]	| -			| -			| -			| -

#define	HwPORTCFG13							*(volatile unsigned long *)0xF005A034	// R/W, Port Configuration Register 13
	#define	HwPORTCFG13_CPD5(X)	((X)*Hw28)	// CPD[5]			= CPD[5]		| GPIOE[17]	| -			| -			| -			| -
	#define	HwPORTCFG13_CPD6(X)	((X)*Hw24)	// CPD[6]			= CPD[6]		| GPIOE[18]	| -			| -			| -			| -
	#define	HwPORTCFG13_CPD7(X)	((X)*Hw20)	// CPD[7]			= CPD[7]		| GPIOE[19]	| -			| -			| -			| -
	#define	HwPORTCFG13_HPCSN(X)	((X)*Hw0)	// HPCSN			= HPCSN		| GPIOF[20]	| MS_D1(1)	| SD_D1(1)	| HDDXA[0]	| LPDIN[20]


/************************************************************************
*	LCD System INTERFACE Definition
************************************************************************/
//LCDSI Register map(0xF0000000)
//#define HwLCDSI			0xF0000000

typedef struct _LCDSI0{
	volatile unsigned int		CTRL0;				// 0x400 R/W 0x00000000 Control register for LCDSI
}LCDSI0, *PLCDSI0;

typedef struct _LCDSI1{
	volatile unsigned int		CTRL1;				// 0x800 R/W 0xA0229011 Control register for nCS0 when RS=0(for core access)
	volatile unsigned int		CTRL2;				// 0x804 R/W 0xA0429021 Control register for nCS0 when RS=1(for core access)
	volatile unsigned int		CTRL3;				// 0x808 R/W 0xA0129009 Control register for nCS1 when RS=0(for core access)
	volatile unsigned int		CTRL4;				// 0x80C R/W 0xA0229011 Control register for nCS1 when RS=1(for core access)
	volatile unsigned int		CS0RS0;				// 0x810 R/W -if this register is read or written, reading or writing operations are generated on nCS0 while RS = 0.
	volatile unsigned int		NOTDEFINE0;			// 0x814
	volatile unsigned int		CS0RS1;				// 0x818 R/W -if this register is read or written, reading or writing operations are generated on nCS0 while RS = 1.
	volatile unsigned int		NOTDEFINE1;			// 0x81C
	volatile unsigned int		CS1RS0;				// 0x820 R/W -if this register is read or written, reading or writing operations are generated on nCS1 while RS = 0.
	volatile unsigned int		NOTDEFINE2;			// 0x824
	volatile unsigned int		CS1RS1;				// 0x828 R/W -if this register is read or written, reading or writing operations are generated on nCS1 while RS = 1.
	volatile unsigned int		NOTDEFINE3;			// 0x82C
	volatile unsigned int		CTRL5;				// 0x830 R/W 0xA0229011 Control register for nCS0 when RS=0(for lcd access)
	volatile unsigned int		CTRL6;				// 0x834 R/W 0xA0429021 Control register for nCS0 when RS=1(for lcd access)
	volatile unsigned int		CTRL7;				// 0x838 R/W 0xA0129009 Control register for nCS1 when RS=0(for lcd access)
	volatile unsigned int		CTRL8;				// 0x83C R/W 0xA0229011 Control register for nCS1 when RS=1(for lcd access)
}LCDSI1, *PLCDSI1;

/************************************************************************
*	NTSC/PAL ENCODER COMPOSITE OUTPUT Definition
************************************************************************/
//STATA 0xF9000000
//#define HwNTSCPAL		0x90000000
typedef struct _NTSCPAL{
	volatile unsigned int STATA;					//0x00
	volatile unsigned int	ECMDA;					//0x04
	volatile unsigned int	ECMDB;					//0x08
	volatile unsigned int	GLK;					//0x0C
	volatile unsigned int	SCH;					//0x10
	volatile unsigned int	HUE;					//0x14
	volatile unsigned int	SAT;					//0x18
	volatile unsigned int	CONT;					//0x1C
	volatile unsigned int	BRIGHT;					//0x20
	volatile unsigned int	FSC_ADJM;				//0x24
	volatile unsigned int	FSC_ADJL;				//0x28
	volatile unsigned int	ECMDC;					//0x2C
	volatile unsigned int	CSDLY;					//0x30
	volatile unsigned int	NOTDEFINE0[3];			//0x34, 38, 3C
	volatile unsigned int	DACSEL;					//0x40
	volatile unsigned int	DACSEL32;				//0x44
	volatile unsigned int	DACSEL54;				//0x48
	volatile unsigned int	DACLP;					//0x4C
	volatile unsigned int	DACPD;					//0x50
	volatile unsigned int	NOTDEFINE2[11];			//0x54, 58, 5C, 60, 64, 68, 6C, 70, 74, 78, 7C
	volatile unsigned int	ICNTL;					//0x80
	volatile unsigned int	HVOFFST;				//0x84
	volatile unsigned int	HOFFST;					//0x88
	volatile unsigned int	VOFFST;					//0x8C
	volatile unsigned int	HSVSO;					//0x90
	volatile unsigned int	HSOB;					//0x94
	volatile unsigned int	HSOE;					//0x98
	volatile unsigned int	VSOB;					//0x9C
	volatile unsigned int	VSOE;					//0xA0
}NTSCPAL, *PNTSCPAL;


typedef struct _NTSCPALOP{
	volatile unsigned int	VENCON;					//0xF90000800
	volatile unsigned int	VENCIF;					//0xF90000804
}NTSCPALOP, *PNTSCPALOP;


/************************************************************************
*	SCALER Definition
************************************************************************/
//Scaler Registers (Base Address = 0xF0070000)
//#define HwSCALER			0xF0070000
typedef struct _SCALER{
	volatile unsigned int SRC_Y_BASE;			// 0x000 R/W 0x00000000 Scaler source image Y base address register
	volatile unsigned int	SRC_U_BASE;			// 0x004 R/W 0x00000000 Scaler source image U base address register
	volatile unsigned int	SRC_V_BASE;			// 0x008 R/W 0x00000000 Scaler source image V base address register
	volatile unsigned int	SRC_SIZE;			// 0x00c R/W 0x00000000 Source image size register
	volatile unsigned int	SRC_OFFSET;			// 0x010 R/W 0x00000000 Source image line offset register
	volatile unsigned int	SRC_CONFIG;			// 0x014 R/W 0x00000000 Source image configuration register
	volatile unsigned int	NOTDEFINE0[2];		// 0x018, 1C
	volatile unsigned int	DST_Y_BASE;			// 0x020 R/W 0x00000000 Scaler destination image Y base address register
	volatile unsigned int	DST_U_BASE;			// 0x024 R/W 0x00000000 Scaler destination image U base address register
	volatile unsigned int	DST_V_BASE;			// 0x028 R/W 0x00000000 Scaler destination image V base address register
	volatile unsigned int	DST_SIZE;			// 0x02c R/W 0x00000000 Destination image size register
	volatile unsigned int	DST_OFFSET;			// 0x030 R/W 0x00000000 Destination image line offset register
	volatile unsigned int	DST_CONFIG;			// 0x034 R/W 0x00000000 Destination image configuration register
	volatile unsigned int	NOTDEFINE1[2];		// 0x038, 3C
	volatile unsigned int	SCALE_RATIO;		// 0x040 R/W 0x00000000 Scale ratio register
	volatile unsigned int	SCALE_CTRL;			// 0x044 R/W 0x00000000 Scaler control register
	volatile unsigned int	STATUS;				// 0x048 R 0x00000000 Scaler status register
}SCALER,* PSCALER;

/************************************************************************
*	USB CONTROLLER Definition
************************************************************************/
//USB Register Map (Base Address = 0xF0010000)
//#define HwUSB					0xF0010000
typedef struct _USB {
	volatile unsigned int	IR;						//Index Register IR 0x00 
	volatile unsigned int	EIR;					//Endpoint Interrupt Register EIR 0x04 
	volatile unsigned int	EIER;					//Endpoint Interrupt Register EIER 0x08 
	volatile unsigned int	NOTDEFINE0;				//0x0C
	volatile unsigned int	EDR;					//Endpoint Direction Register EDR 0x14 
	volatile unsigned int	NOTDEFINE1;				//0x18 
	volatile unsigned int	SSR;					//System Status Register SSR 0x1C 
	volatile unsigned int	SCR;					//System Control Register SCR 0x20 
	volatile unsigned int	EP0SR;					//EP0 Status Register EP0SR 0x24 
	volatile unsigned int	EP0CR;					//EP0 Control Register EP0CR 0x28 
	volatile unsigned int	ESR;					//Endpoints Status Register ESR 0x2C
	volatile unsigned int	ECR;					//Endpoint Control Register ECR 0x30
	volatile unsigned int	BRCR;					//Byte Read Count Register BRCR 0x34
	volatile unsigned int	BWCR;					//Byte Write Count Register BWCR 0x38
	volatile unsigned int	MPR;					//Reserved Max Packet Register MPR 0x3C
	volatile unsigned int	DCR;					//DMA Control Register DCR 0x40
	volatile unsigned int	DTCR;					//DMA Transfer Counter Register DTCR 0x44
	volatile unsigned int	DFCR;					//DMA FIFO Counter Register DFCR 0x48
	volatile unsigned int	DTTCR1;					//DMA Total Transfer Counter1 Register DTTCR1 0x4C
	volatile unsigned int	DTTCR2;					//DMA Total Transfer Counter2 Register DTTCR2 0x50
	volatile unsigned int	NOTDEFINE2[3];			//0x54, 0x58, 0x5C
	volatile unsigned int	EP0BUF;					//EP0 Buffer Register EP0BUF 0x60
	volatile unsigned int	EP1BUF;					//EP1 Buffer Register EP1BUF 0x64
	volatile unsigned int	EP2BUF;					//EP2 Buffer Register EP2 BUF 0x68
	volatile unsigned int	EP3BUF;					//EP3 Buffer Register EP3 BUF 0x6C
	volatile unsigned int	NOTDEFINE3[12];	// 12[4 * 3(7,8,9)] 
	volatile unsigned int	DMAR1;					// 0xA0
	volatile unsigned int	DMAR2;					// 0xA4
	volatile unsigned int	NOTDEFINE4[6];	// [A8, AC, C0 + 4 * 1(B) +] 
	volatile unsigned int	UBCFG;					// C4
}USB, *pUSB;

//USB Host Register Map (Base Address = 0xF0020000)
//#define HwUSBHOST			0xF0020000
typedef struct _USBHOST{
	volatile unsigned int	HcRevision;				// 0x00 R 0x00000010
	volatile unsigned int	HcControl;				// 0x04 R/W 0x00000000
	volatile unsigned int	HcCommandStatus;		// 0x08 R 0x00000000
	volatile unsigned int	HcInterruptStatus;		// 0x0C R 0x00000000
	volatile unsigned int	HcInterruptEnable;		// 0x10 R/W 0x00000000
	volatile unsigned int	HcInterruptDisable;		// 0x14 W 0x00000000
	volatile unsigned int	HcHCCA;					// 0x18 R/W 0x00000000
	volatile unsigned int	HcPeriodCurrentED;		// 0x1C R 0x00000000
	volatile unsigned int	HcControlHeadED;		// 0x20 R/W 0x00000000
	volatile unsigned int	HcControlCurrentED;		// 0x24 R/W 0x00000000
	volatile unsigned int	HcBulkHeadED;			// 0x28 R/W 0x00000000
	volatile unsigned int	HcBulkCurrentED;		// 0x2C R/W 0x00000000
	volatile unsigned int	HcDoneHead;				// 0x30 R 0x00000000
	volatile unsigned int	HcRmInterval;			// 0x34 R/W 0x00002EDF
	volatile unsigned int	HcFmRemaining;			// 0x38 R/W 0x00000000
	volatile unsigned int	HcFmNumber;				// 0x3C R/W 0x00000000
	volatile unsigned int	HcPeriodStart;			// 0x40 R/W 0x00000000
	volatile unsigned int	HcLSThreshold;			// 0x44 R/W 0x00000628
	volatile unsigned int	HcRhDescriptorA;		// 0x48 R/W 0x02001202
	volatile unsigned int	HcRhDescriptorB;		// 0x4C R/W 0x00000000
	volatile unsigned int	HcRhStatus;				// 0x50 R/W 0x00000000
	volatile unsigned int	HcRhPortStatus1;		// 0x54 R/W 0x00000100
	volatile unsigned int	HcRhPortStatus2;		// 0x58 R/W 0x00000100
}USBHOST, * PUSBHOST;

/************************************************************************
*	IDE Definition
************************************************************************/
//IDE Registers (Base = 0xF0030000)
//#define HwIDE					0xF0030000
typedef struct _IDE{
	volatile unsigned int	CS000;					// 0x00~ 0x03 R/W - PIO CS0n Access Register
	volatile unsigned int	CS004;					// 0x04~ 0x07 R/W - PIO CS0n Access Register
	volatile unsigned int	CS008;					// 0x08~ 0x0B R/W - PIO CS0n Access Register
	volatile unsigned int	CS00C;					// 0x0C~ 0x0F R/W - PIO CS0n Access Register
	volatile unsigned int	CS010;					// 0x10~ 0x13 R/W - PIO CS0n Access Register
	volatile unsigned int	CS014;					// 0x14~ 0x17 R/W - PIO CS0n Access Register
	volatile unsigned int	CS018;					// 0x18~ 0x1B R/W - PIO CS0n Access Register
	volatile unsigned int	CS01C;					// 0x1C~ 0x1F R/W - PIO CS0n Access Register
	volatile unsigned int	CS120;					// 0x20~ 0x23 R/W - PIO CS1n Access Register
	volatile unsigned int	CS124;					// 0x24~ 0x27 R/W - PIO CS1n Access Register
	volatile unsigned int	CS128;					// 0x28~ 0x2B R/W - PIO CS1n Access Register
	volatile unsigned int	CS12C;					// 0x2C~ 0x2F R/W - PIO CS1n Access Register
	volatile unsigned int	CS130;					// 0x30~ 0x33 R/W - PIO CS1n Access Register
	volatile unsigned int	CS134;					// 0x34~ 0x37 R/W - PIO CS1n Access Register
	volatile unsigned int	CS138;					// 0x38~ 0x3B R/W - PIO CS1n Access Register
	volatile unsigned int	CS13C;					// 0x3C~ 0x3F R/W - PIO CS1n Access Register
	volatile unsigned int	PIOCTRL;				// 0x40 R/W 0x00600000 PIO Mode Control Register
	volatile unsigned int	UDMACTRL;				// 0x44 R/W 0x00000000 UDMA Mode Control Register
	volatile unsigned int	IDMACTRL;				// 0x48 R/W 0x00000000 IDMA Control Register
	volatile unsigned int	IDMASA;					// 0x4C R/W 0x00000000 IDMA Source Address Register
	volatile unsigned int	IDMASP;					// 0x50 R/W 0x00000000 IDMA Source Parameter Register
	volatile unsigned int	IDMACSA;				// 0x54 R 0x00000000 IDMA Current Source Address Register
	volatile unsigned int	IDMADA;					// 0x58 R/W 0x00000000 IDMA Destination Address Register
	volatile unsigned int	IDMADP;					// 0x5C R/W 0x00000000 IDMA Destination Parameter Register
	volatile unsigned int	IDMACDA;				// 0x60 R 0x00000000 IDMA Current Destination Address Register
	volatile unsigned int	IDEINT;					// 0x64 R/W 0x0000_0000 IDE Interrupt Register
	volatile unsigned int	UDMATCNT;				// 0x68 R/W 0x00FF_FFFF UDMA Transfer Counter Register
	volatile unsigned int	UDMAIN;					// 0x6C R - UDMA-IN Access Register
	volatile unsigned int	UDMAOUT;				// 0x70 W - UDMA-OUT Access register
	volatile unsigned int	UDMACRC;				// 0x74 R 0x0000_4ABA UDMA CRC Register
	volatile unsigned int	UDMACTCNT;				// 0x78 R 0x00FF_FFFF UDMA Current Transfer Counter Register
}IDE, * PIDE;

/************************************************************************
*	DMA CONTROLLER Definition
************************************************************************/
//General DMA0 Controller Register Map (Base Address = 0xF0040000)
//#define HwDMA0				0xF0040000
typedef struct _DMA0{
	volatile unsigned int	ST_SADR0;				// 0x00 R/W 0x00000000 Start Address of Source Block
	volatile unsigned int	SPARAM0;				// 0x04 R/W 0x00000000 Parameter of Source Block
	volatile unsigned int	NOTDEFINE0;				// 0x08
	volatile unsigned int	C_SADR0;				// 0x0C R 0x00000000 Current Address of Source Block
	volatile unsigned int	ST_DADR0;				// 0x10 R/W 0x00000000 Start Address of Destination Block
	volatile unsigned int	DPARAM0;				// 0x14 R/W 0x00000000 Parameter of Destination Block
	volatile unsigned int	NOTDEFINE1;				// 0x18
	volatile unsigned int	C_DADR0;				// 0x1C R 0x00000000 Current Address of Destination Block
	volatile unsigned int	HCOUNT0;				// 0x20 R/W 0x00000000 Initial and Current Hop count
	volatile unsigned int	CHCTRL0;				// 0x24 R/W 0x00000000 Channel Control Register
	volatile unsigned int	RPTCTRL0;				// 0x28 R/W 0x00000000 Repeat Control Register
	volatile unsigned int	EXTREQ0;				// 0x2C R/W 0x00000000 External DMA Request register
}DMA0,* pDMA0;

//General DMA1 Controller Register Map (Base Address = 0xF0040100)
//#define HwDMA1				0xF0040100
typedef struct _DMA1{
	volatile unsigned int	ST_SADR1;				// 0x30 R/W 0x00000000 Start Address of Source Block
	volatile unsigned int	SPARAM1;				// 0x34 R/W 0x00000000 Parameter of Source Block
	volatile unsigned int	NOTDEFINE0;				// 0x38
	volatile unsigned int	C_SADR1;				// 0x3C R 0x00000000 Current Address of Source Block
	volatile unsigned int	ST_DADR1;				// 0x40 R/W 0x00000000 Start Address of Destination Block
	volatile unsigned int	DPARAM1;				// 0x44 R/W 0x00000000 Parameter of Destination Block
	volatile unsigned int	NOTDEFINE1;				// 0x48
	volatile unsigned int	C_DADR1;				// 0x4C R 0x00000000 Current Address of Destination Block
	volatile unsigned int	HCOUNT1;				// 0x50 R/W 0x00000000 Initial and Current Hop count
	volatile unsigned int	CHCTRL1;				// 0x54 R/W 0x00000000 Channel Control Register
	volatile unsigned int	RPTCTRL1;				// 0x58 R/W 0x00000000 Repeat Control Register
	volatile unsigned int	EXTREQ1;				// 0x5C R/W 0x00000000 External DMA Request register
}DMA1,* pDMA1;

//General DMA2 Controller Register Map (Base Address = 0xF0040200)
//#define HwDMA2				0xF0040200
typedef struct _DMA2{
	volatile unsigned int	ST_SADR2;				// 0x60 R/W 0x00000000 Start Address of Source Block
	volatile unsigned int	SPARAM2;				// 0x64 R/W 0x00000000 Parameter of Source Block
	volatile unsigned int	NOTDEFINE0;				// 0x68
	volatile unsigned int	C_SADR2;				// 0x6C R 0x00000000 Current Address of Source Block
	volatile unsigned int	ST_DADR2;				// 0x70 R/W 0x00000000 Start Address of Destination Block
	volatile unsigned int	DPARAM2;				// 0x74 R/W 0x00000000 Parameter of Destination Block
	volatile unsigned int	NOTDEFINE1;				// 0x78
	volatile unsigned int	C_DADR2;				// 0x7C R 0x00000000 Current Address of Destination Block
	volatile unsigned int	HCOUNT2;				// 0x80 R/W 0x00000000 Initial and Current Hop count
	volatile unsigned int	CHCTRL2;				// 0x84 R/W 0x00000000 Channel Control Register
	volatile unsigned int	RPTCTRL2;				// 0x88 R/W 0x00000000 Repeat Control Register
	volatile unsigned int	EXTREQ2;				// 0x8C R/W 0x00000000 External DMA Request register
	volatile unsigned int	CHCONFIG;				// 0x90 R/W 0x00000000 Channel Configuration Register
}DMA2,* pDMA2;

typedef struct _DMA{
	volatile unsigned int	ST_SADR0;				// 0x00 R/W 0x00000000 Start Address of Source Block
	volatile unsigned int	SPARAM0;				// 0x04 R/W 0x00000000 Parameter of Source Block
	volatile unsigned int	NOTDEFINE0;				// 0x08
	volatile unsigned int	C_SADR0;				// 0x0C R 0x00000000 Current Address of Source Block
	volatile unsigned int	ST_DADR0;				// 0x10 R/W 0x00000000 Start Address of Destination Block
	volatile unsigned int	DPARAM0;				// 0x14 R/W 0x00000000 Parameter of Destination Block
	volatile unsigned int	NOTDEFINE1;				// 0x18
	volatile unsigned int	C_DADR0;				// 0x1C R 0x00000000 Current Address of Destination Block
	volatile unsigned int	HCOUNT0;				// 0x20 R/W 0x00000000 Initial and Current Hop count
	volatile unsigned int	CHCTRL0;				// 0x24 R/W 0x00000000 Channel Control Register
	volatile unsigned int	RPTCTRL0;				// 0x28 R/W 0x00000000 Repeat Control Register
	volatile unsigned int	EXTREQ0;				// 0x2C R/W 0x00000000 External DMA Request register
	volatile unsigned int	ST_SADR1;				// 0x30 R/W 0x00000000 Start Address of Source Block
	volatile unsigned int	SPARAM1;				// 0x34 R/W 0x00000000 Parameter of Source Block
	volatile unsigned int	NOTDEFINE2;				// 0x38
	volatile unsigned int	C_SADR1;				// 0x3C R 0x00000000 Current Address of Source Block
	volatile unsigned int	ST_DADR1;				// 0x40 R/W 0x00000000 Start Address of Destination Block
	volatile unsigned int	DPARAM1;				// 0x44 R/W 0x00000000 Parameter of Destination Block
	volatile unsigned int	NOTDEFINE3;				// 0x48
	volatile unsigned int	C_DADR1;				// 0x4C R 0x00000000 Current Address of Destination Block
	volatile unsigned int	HCOUNT1;				// 0x50 R/W 0x00000000 Initial and Current Hop count
	volatile unsigned int	CHCTRL1;				// 0x54 R/W 0x00000000 Channel Control Register
	volatile unsigned int	RPTCTRL1;				// 0x58 R/W 0x00000000 Repeat Control Register
	volatile unsigned int	EXTREQ1;				// 0x5C R/W 0x00000000 External DMA Request register
	volatile unsigned int	ST_SADR2;				// 0x60 R/W 0x00000000 Start Address of Source Block
	volatile unsigned int	SPARAM2;				// 0x64 R/W 0x00000000 Parameter of Source Block
	volatile unsigned int	NOTDEFINE4;				// 0x68
	volatile unsigned int	C_SADR2;				// 0x6C R 0x00000000 Current Address of Source Block
	volatile unsigned int	ST_DADR2;				// 0x70 R/W 0x00000000 Start Address of Destination Block
	volatile unsigned int	DPARAM2;				// 0x74 R/W 0x00000000 Parameter of Destination Block
	volatile unsigned int	NOTDEFINE5;				// 0x78
	volatile unsigned int	C_DADR2;				// 0x7C R 0x00000000 Current Address of Destination Block
	volatile unsigned int	HCOUNT2;				// 0x80 R/W 0x00000000 Initial and Current Hop count
	volatile unsigned int	CHCTRL2;				// 0x84 R/W 0x00000000 Channel Control Register
	volatile unsigned int	RPTCTRL2;				// 0x88 R/W 0x00000000 Repeat Control Register
	volatile unsigned int	EXTREQ2;				// 0x8C R/W 0x00000000 External DMA Request register
	volatile unsigned int	CHCONFIG;				// 0x90 R/W 0x00000000 Channel Configuration Register
}DMA,* pDMA;

/************************************************************************
*	MEMORY STICK Definition
************************************************************************/
//MSHC Register Map (Base Address = 0xF0051000)
//#define HwMSHC				0xF0051000
typedef struct _MSHC{
	volatile unsigned int	COMMAND;				// 0x00 R/W 0x00000000 Command Register
	volatile unsigned int	DATA;					// 0x04 R/W Unknown Data Register
	volatile unsigned int	STATUS;					// 0x08 R/W 0x00001020 Status Register
	volatile unsigned int	SYSTEM;					// 0x0C R/W 0x00004455 System Control Register
}MSHC,* PMSHC;

/************************************************************************
*	SD/MMC CONTROLLER Definition
************************************************************************/


/************************************************************************
*	NFC Definition ( Nand Frash Controller)
************************************************************************/
//Nand Flash Controller Register Map (Base Address = 0xF00B0000)
//#define HwNFC					0xF00B0000 
typedef struct _NFC {
	volatile unsigned int	NFC_CMD;				// 0x00 W - Nand Flash Command Register
	volatile unsigned int	NFC_LADDR;				// 0x04 W - Nand Flash Linear Address Register
	volatile unsigned int	NFC_BADDR;				// 0x08 W - Nand Flash Block Address Register
	volatile unsigned int	NFC_SADDR;				// 0x0C W - Nand Flash Signal Address Register
	volatile unsigned int	NFC_WDATA;				// 0x1x R/W Unknown Nand Flash Word Data Register
	volatile unsigned int	NOTDEFINE0[3];			// 0x14, 18, 1C
	volatile unsigned int	NFC_LDATA;				// 0x2x/3x R/W Unknown Nand Flash Linear Data Register
	volatile unsigned int	NOTDEFINE1[7];			// 0x24, 28, 2C, 30, 34, 38, 3C
	volatile unsigned int	NFC_SDATA;				// 0x40 R/W Unknown Nand Flash Single Data Register
	volatile unsigned int	NOTDEFINE2[3];			// 0x44, 48, 4C
	volatile unsigned int	NFC_CTRL;				// 0x50 R/W 0x03e08000 Nand Flash Control Register
	volatile unsigned int	NFC_PSTART;				// 0x54 W - Nand Flash Program Start Register
	volatile unsigned int	NFC_RSTART;				// 0x58 W - Nand Flash Read Start Register
	volatile unsigned int	NFC_DSIZE;				// 0x5C R/W 0x0000ffff Nand Flash Data Size Register
	volatile unsigned int	NFC_IREQ;				// 0x60 R/W 0x07000000 Nand Flash Interrupt Request Register
	volatile unsigned int	NFC_RST;				// 0x64 W - Nand Flash Controller Reset Register
	volatile unsigned int	NFC_CTRL1;				// 0x68 R/W 0x00000000 Nand Flash Control Register 1
	volatile unsigned int	NOTDEFINE3;				// 0x6C
	volatile unsigned int	NFC_MDATA;				// 0x7x R/W Unknown Nand Flash Multiple Data Register
}NFC, * PNFC;


/************************************************************************
*	ECC Definition
************************************************************************/
//ECC Register Map (Base Address = 0xF005B000)
//#define HwECC					0xF005B000
typedef struct _ECCSLC{
	volatile unsigned int	ECC_CTRL;					// 0x00 R/W 0x00000000 ECC Control Register
	volatile unsigned int	ECC_BASE;					// 0x04 R/W 0x00000000 Base Address for ECC Calculation
	volatile unsigned int	ECC_MASK;					// 0x08 R/W 0x00000000 Address mask for ECC area.
	volatile unsigned int	ECC_CLEAR;					// 0x0C R/W ECC Clear
	volatile unsigned int	SECC_0;						// 0x10 R/W 0x00000000 1st SLC ECC Code Register
	volatile unsigned int	SECC_1;						// 0x14 R/W 0x00000000 2nd SLC ECC Code register
	volatile unsigned int	SECC_2;						// 0x18 R/W 0x00000000 3rd SLC ECC Code Register
	volatile unsigned int	SECC_3;						// 0x1C R/W 0x00000000 4th SLC ECC Code Register
	volatile unsigned int	SECC_4;						// 0x20 R/W 0x00000000 5th SLC ECC Code Register
	volatile unsigned int	SECC_5;						// 0x24 R/W 0x00000000 6th SLC ECC Code Register
	volatile unsigned int	SECC_6;						// 0x28 R/W 0x00000000 7th SLC ECC Code Register
	volatile unsigned int	SECC_7;						// 0x2C R/W 0x00000000 8th SLC ECC Code Register
	volatile unsigned int	SECC_8;						// 0x30 R/W 0x00000000 9th SLC ECC Code Register
	volatile unsigned int	SECC_9;						// 0x34 R/W 0x00000000 10th SLC ECC Code Register
	volatile unsigned int	SECC_10;					// 0x38 R/W 0x00000000 11th SLC ECC Code Register
	volatile unsigned int	SECC_11;					// 0x3C R/W 0x00000000 12th SLC ECC Code Register
	volatile unsigned int	SECC_12;					// 0x40 R/W 0x00000000 13th SLC ECC Code Register
	volatile unsigned int	SECC_13;					// 0x44 R/W 0x00000000 14th SLC ECC Code Register
	volatile unsigned int	SECC_14;					// 0x48 R/W 0x00000000 15th SLC ECC Code Register
	volatile unsigned int	SECC_15;					// 0x4C R/W 0x00000000 16th SLC ECC Code Register
	volatile unsigned int	SECC_EADDR0;				// 0x50 R 0x00000000 SLC ECC Error Address Register0
	volatile unsigned int	SECC_EADDR1;				// 0x54 R 0x00000000 SLC ECC Error Address Register1
	volatile unsigned int	SECC_EADDR2;				// 0x58 R 0x00000000 SLC ECC Error Address Register2
	volatile unsigned int	SECC_EADDR3;				// 0x5C R 0x00000000 SLC ECC Error Address Register3
	volatile unsigned int	SECC_EADDR4;				// 0x60 R 0x00000000 SLC ECC Error Address Register4
	volatile unsigned int	SECC_EADDR5;				// 0x64 R 0x00000000 SLC ECC Error Address Register5
	volatile unsigned int	SECC_EADDR6;				// 0x68 R 0x00000000 SLC ECC Error Address Register6
	volatile unsigned int	SECC_EADDR7;				// 0x6C R 0x00000000 SLC ECC Error Address Register7
	volatile unsigned int	SECC_EADDR8;				// 0x70 R 0x00000000 SLC ECC Error Address Register8
	volatile unsigned int	SECC_EADDR9;				// 0x74 R 0x00000000 SLC ECC Error Address Register9
	volatile unsigned int	SECC_EADDR10;				// 0x78 R 0x00000000 SLC ECC Error Address Register10
	volatile unsigned int	SECC_EADDR11;				// 0x7C R 0x00000000 SLC ECC Error Address Register11
	volatile unsigned int	SECC_EADDR12;				// 0x80 R 0x00000000 SLC ECC Error Address Register12
	volatile unsigned int	SECC_EADDR13;				// 0x84 R 0x00000000 SLC ECC Error Address Register13
	volatile unsigned int	SECC_EADDR14;				// 0x88 R 0x00000000 SLC ECC Error Address Register14
	volatile unsigned int	SECC_EADDR15;				// 0x8C R 0x00000000 SLC ECC Error Address Register15
	volatile unsigned int	ERRNUM;						// 0x90 R 0x00000000 ECC Error Number
	volatile unsigned int	ECC_IREQ;					// 0x94 R/W 0x00000000 ECC Interrupt Control Register
	volatile unsigned int	ECC_FSMSTATE;				// 0x98 R 0x00000001 ECC FSM State Register
	volatile unsigned int	NOTDEFINE0[20];				// 0xA0, A4, A8, AC, B0, B4, B8, BC, C0, C4, C8, CC, D0, D4, D8, DC, E0, E4, E8, EC
	volatile unsigned int	ENCSEED;					// 0xF0 W Test Mode Register
	volatile unsigned int	ENCMASK;					// 0xF4 W Test Mode Register
	volatile unsigned int	ENCDATA;					// 0xF8 R/W Test Mode Register
}ECCSLC,* PECCSLC;

typedef struct _ECCMLC4{
	volatile unsigned int	ECC_CTRL;					// 0x00 R/W 0x00000000 ECC Control Register
	volatile unsigned int	ECC_BASE;					// 0x04 R/W 0x00000000 Base Address for ECC Calculation
	volatile unsigned int	ECC_MASK;					// 0x08 R/W 0x00000000 Address mask for ECC area.
	volatile unsigned int	ECC_CLEAR;					// 0x0C R/W ECC Clear
	volatile unsigned int	MECC4_0;					// 0x10 R/W 0x00000000 1st MLC ECC4 Code Register
	volatile unsigned int	MECC4_1;					// 0x14 R/W 0x00000000 2nd MLC ECC4 Code Register
	volatile unsigned int	MECC4_2;					// 0x18 R/W 0x00000000 3rd MLC ECC4 Code Register
	volatile unsigned int	MECC4_EADDR0;				// 0x50 R 0x00000000 MLC ECC Error Address Register0
	volatile unsigned int	MECC4_EADDR1;				// 0x54 R 0x00000000 MLC ECC Error Address Register1
	volatile unsigned int	MECC4_EADDR2;				// 0x58 R 0x00000000 MLC ECC Error Address Register2
	volatile unsigned int	MECC4_EADDR3;				// 0x5C R 0x00000000 MLC ECC Error Address Register3
	volatile unsigned int	MECC4_EDATA0;				// 0x70 R 0x00000000 MLC ECC Error Data Register0
	volatile unsigned int	MECC4_EDATA1;				// 0x74 R 0x00000000 MLC ECC Error Data Register1
	volatile unsigned int	MECC4_EDATA2;				// 0x78 R 0x00000000 MLC ECC Error Data Register2
	volatile unsigned int	MECC4_EDATA3;				// 0x7C R 0x00000000 MLC ECC Error Data Register3
	volatile unsigned int	ERRNUM;						// 0x90 R 0x00000000 ECC Error Number
	volatile unsigned int	ECC_IREQ;					// 0x94 R/W 0x00000000 ECC Interrupt Control Register
	volatile unsigned int	ECC_FSMSTATE;				// 0x98 R 0x00000001 ECC FSM State Register
	volatile unsigned int	NOTDEFINE0[20];				// 0xA0, A4, A8, AC, B0, B4, B8, BC, C0, C4, C8, CC, D0, D4, D8, DC, E0, E4, E8, EC
	volatile unsigned int	ENCSEED;					// 0xF0 W Test Mode Register
	volatile unsigned int	ENCMASK;					// 0xF4 W Test Mode Register
	volatile unsigned int	ENCDATA;					// 0xF8 R/W Test Mode Register
}ECCMLC4,* PECCMLC4;

typedef struct _ECCMLC8{
	volatile unsigned int	ECC_CTRL;					// 0x00 R/W 0x00000000 ECC Control Register
	volatile unsigned int	ECC_BASE;					// 0x04 R/W 0x00000000 Base Address for ECC Calculation
	volatile unsigned int	ECC_MASK;					// 0x08 R/W 0x00000000 Address mask for ECC area.
	volatile unsigned int	ECC_CLEAR;					// 0x0C R/W ECC Clear
	volatile unsigned int	MECC8_0;					// 0x10 R/W 0x00000000 1st MLC ECC8 Code Register
	volatile unsigned int	MECC8_1;					// 0x14 R/W 0x00000000 2nd MLC ECC8 Code Register
	volatile unsigned int	MECC8_2;					// 0x18 R/W 0x00000000 3rd MLC ECC8 Code Register
	volatile unsigned int	MECC8_3;					// 0x1C R/W 0x00000000 4th MLC ECC8 Code Register
	volatile unsigned int	MECC8_4;					// 0x20 R/W 0x00000000 5th MLC ECC8 Code Register
	volatile unsigned int	MECC8_EADDR0;				// 0x50 R 0x00000000 MLC ECC8 Error Address Register0
	volatile unsigned int	MECC8_EADDR1;				// 0x54 R 0x00000000 MLC ECC8 Error Address Register1
	volatile unsigned int	MECC8_EADDR2;				// 0x58 R 0x00000000 MLC ECC8 Error Address Register2
	volatile unsigned int	MECC8_EADDR3;				// 0x5C R 0x00000000 MLC ECC8 Error Address Register3
	volatile unsigned int	MECC8_EADDR4;				// 0x60 R 0x00000000 MLC ECC8 Error Address Register4
	volatile unsigned int	MECC8_EADDR5;				// 0x64 R 0x00000000 MLC ECC8 Error Address Register5
	volatile unsigned int	MECC8_EADDR6;				// 0x68 R 0x00000000 MLC ECC8 Error Address Register6
	volatile unsigned int	MECC8_EADDR7;				// 0x6C R 0x00000000 MLC ECC8 Error Address Register7
	volatile unsigned int	MECC8_EDATA0;				// 0x70 R 0x00000000 MLC ECC8 Error Data Register0
	volatile unsigned int	MECC8_EDATA1;				// 0x74 R 0x00000000 MLC ECC8 Error Data Register1
	volatile unsigned int	MECC8_EDATA2;				// 0x78 R 0x00000000 MLC ECC8 Error Data Register2
	volatile unsigned int	MECC8_EDATA3;				// 0x7C R 0x00000000 MLC ECC8 Error Data Register3
	volatile unsigned int	MECC8_EDATA4;				// 0x80 R 0x00000000 MLC ECC8 Error Data Register4
	volatile unsigned int	MECC8_EDATA5;				// 0x84 R 0x00000000 MLC ECC8 Error Data Register5
	volatile unsigned int	MECC8_EDATA6;				// 0x88 R 0x00000000 MLC ECC8 Error Data Register6
	volatile unsigned int	MECC8_EDATA7;				// 0x8C R 0x00000000 MLC ECC8 Error Data Register7
	volatile unsigned int	ERRNUM;						// 0x90 R 0x00000000 ECC Error Number
	volatile unsigned int	ECC_IREQ;					// 0x94 R/W 0x00000000 ECC Interrupt Control Register
	volatile unsigned int	ECC_FSMSTATE;				// 0x98 R 0x00000001 ECC FSM State Register
	volatile unsigned int	NOTDEFINE0[20];				// 0xA0, A4, A8, AC, B0, B4, B8, BC, C0, C4, C8, CC, D0, D4, D8, DC, E0, E4, E8, EC
	volatile unsigned int	ENCSEED;					// 0xF0 W Test Mode Register
	volatile unsigned int	ENCMASK;					// 0xF4 W Test Mode Register
	volatile unsigned int	ENCDATA;					// 0xF8 R/W Test Mode Register
}ECCMLC8,* PECCMLC8;

/************************************************************************
*	CAMERA INTERFACE Definition
************************************************************************/
//CIF Register Map (Base Address = 0xF0060000)
//#define HwCIF					0xF0060000
typedef struct _CIF{
	volatile unsigned int	ICPCR1;					// 0x00 W/R 0x00000000 Input Image Color/Pattern Configuration Register 1
	volatile unsigned int	CCIR656FCR1;				// 0x04 W/R 0x06ff0000 CCIR656 Format Configuration Register 1
	volatile unsigned int	CCIR656FCR2;				// 0x08 W/R 0x010b CCIR656 Format Configuration Register 2
	volatile unsigned int	IIS;					// 0x0C W/R 0x00000000 Input Image Size
	volatile unsigned int	IIW1;					// 0x10 W/R 0x00000000 Input Image Windowing 1
	volatile unsigned int	IIW2;					// 0x14 W/R 0x00000000 Input Image Windowing 2
	volatile unsigned int	CDCR1;					// 0x18 W/R 0x0003 DMA Configuration Register 1
	volatile unsigned int	CDCR2;					// 0x1C W/R 0x00000000 DMA Configuration Register 2
	volatile unsigned int	CDCR3;					// 0x20 W/R 0x00000000 DMA Configuration Register 3
	volatile unsigned int	CDCR4;					// 0x24 W/R 0x00000000 DMA Configuration Register 4
	volatile unsigned int	CDCR5;					// 0x28 W/R 0x00000000 DMA Configuration Register 5
	volatile unsigned int	CDCR6;					// 0x2C W/R 0x00000000 DMA Configuration Register 6
	volatile unsigned int	CDCR7;					// 0x30 W/R 0x00000000 DMA Configuration Register 7
	volatile unsigned int	FIFOSTATE;				// 0x34 R 0x00000000 FIFO Status Register
	volatile unsigned int	CIRQ;					// 0x38 W/R 0x00000000 Interrupt & Status register
	volatile unsigned int	OCTRL1;					// 0x3C W/R 0x37000000 Overlay Control 1
	volatile unsigned int	OCTRL2;					// 0x40 W/R 0x00000000 Overlay Control 2
	volatile unsigned int	OCTRL3;					// 0x44 W/R 0x00000000 Overlay Control 3
	volatile unsigned int	OCTRL4;					// 0x48 W/R 0x00000000 Overlay Control 4
	volatile unsigned int	OIS;					// 0x4C W/R 0x00000000 Overlay Image Size
	volatile unsigned int	OIW1;					// 0x50 W/R 0x00000000 Overlay Image Windowing 1
	volatile unsigned int	OIW2;					// 0x54 W/R 0x00000000 Overlay Image Windowing 2
	volatile unsigned int	COBA;					// 0x58 W/R 0x00000000 Overlay Base Address
	volatile unsigned int	CDS;					// 0x5C W/R 0x00000000 Camera Down Scaler
	volatile unsigned int	CCM1;					// 0x60 W/R 0x00000000 Capture Mode Configuration 1
	volatile unsigned int	CCM2;					// 0x64 W/R 0x00000000 Capture Mode Configuration 2
	volatile unsigned int	CESA;					// 0x68 W/R 0x00000000 Point Encoding Start Address
	volatile unsigned int	CR2Y;					// 0x6C W/R 0x00000000 RGB2YUV Format converter Configuration
	volatile unsigned int	CCYA;					// 0x70 R - Current Y Address
	volatile unsigned int	CCYU;					// 0x74 R - Current U Address
	volatile unsigned int	CCYV;					// 0x78 R - Current V Address
	volatile unsigned int	CCLC;					// 0x7C R Current Line count
}CIF, * PCIF;

//Effect Register Map (Base Address = 0xF0060100)
//#define HwEFFECT			0xF0060100
typedef struct _EFFECT{
	volatile unsigned int	EMR;					// 0x00 W/R 0x00000000 Effect mode register
	volatile unsigned int	SEPIAUV;				// 0x04 W/R 0x00000000 Sepia UV setting
	volatile unsigned int	CSR;					// 0x08 W/R 0x00000000 Color selection register
	volatile unsigned int	HFIL_COEF;				// 0x0C W/R 0x00000000 H-filter coefficent0
	volatile unsigned int	SKETCHTH;				// 0x10 W/R 0x00000000 Sketch threshold register
	volatile unsigned int	CLAMPTH;				// 0x14 W/R 0x00000000 Clamp threshold register
	volatile unsigned int	BIAS;					// 0x18 W/R 0x00000000 BIAS register
	volatile unsigned int	ISIZE;					// 0x1C W/R 0x00000000 Image size register
	volatile unsigned int	NOTDEFINE0[8];			// 0x20, 24, 28, 2C, 30, 34, 38, 3C,
	volatile unsigned int	INPATH_CTRL;			// 0x40 W/R 0x00000000 Inpath configuration
	volatile unsigned int	SRC_ADDRY;				// 0x44 W/R 0x00000000 Source address in Y channel
	volatile unsigned int	SRC_ADDRU;				// 0x48 W/R 0x00000000 Source address in U channel
	volatile unsigned int	SRC_ADDRV;				// 0x4C W/R 0x00000000 Source address in V channel
	volatile unsigned int	SRC_SIZE;				// 0x50 W/R 0x00000000 Source image size
	volatile unsigned int	SRC_OFFS;				// 0x54 W/R 0x00000000 Source image offset
	volatile unsigned int	DST_SIZE;				// 0x58 W/R 0x00000000 Destination image size
	volatile unsigned int	TAR_SCALE;				// 0x5C W/R 0x00000000 Target scale	
}EFFECT, * PEFFECT;

//Scaler Register Map (Base Address = 0xF0060200)
//#define HwCIFSACLER		0xF0060200
typedef struct _CIFSACLER{
	volatile unsigned int	SC_CTRL;				// 0x00 W/R 0x00000000 Scaler configuration
	volatile unsigned int	SC_SCALE;				// 0x04 W/R 0x00000000 Scale factor
	volatile unsigned int	SC_SRC_OFFSET;			// 0x08 W/R 0x00000000 Image offset
	volatile unsigned int	SC_SRC_SIZE;			// 0x0C W/R 0x00000000 Source image size
	volatile unsigned int	SC_DST_SIZE;			// 0x10 W/R 0x00000000 Destination image size
}CIFSACLER,* PCIFSACLER;

/************************************************************************
*	GRAPHIC ENGINE Definition
************************************************************************/
//Graphic Engine Register Map (Base Address = 0xF6000000)
//#define HwGE					0xF6000000
typedef struct _GE{
	volatile unsigned int	FCH0_SADDR0;		// 0x00 R/W 0x00000000 Front-End Channel 0 Source Address 0
	volatile unsigned int	FCH0_SADDR1;		// 0x04 R/W 0x00000000 Front-End Channel 0 Source Address 1
	volatile unsigned int	FCH0_SADDR2;		// 0x08 R/W 0x00000000 Front-End Channel 0 Source Address 2
	volatile unsigned int	FCH0_SFSIZE;		// 0x0C R/W 0x00000000 Front-End Channel 0 Source Frame Pixel Size
	volatile unsigned int	FCH0_SOFF;			// 0x10 R/W 0x00000000 Front-End Channel 0 Source Pixel Offset
	volatile unsigned int	FCH0_SISIZE;		// 0x14 R/W 0x00000000 Front-End Channel 0 Source Image Pixel Size
	volatile unsigned int	FCH0_WOFF;			// 0x18 R/W 0x00000000 Front-End Channel 0 Window Pixel Offset
	volatile unsigned int	FCH0_SCTRL;			// 0x1C R/W 0x00000000 Front-End Channel 0 Control
	volatile unsigned int	FCH1_SADDR0;		// 0x20 R/W 0x00000000 Front-End Channel 1 Source Address 0
	volatile unsigned int	FCH1_SADDR1;		// 0x24 R/W 0x00000000 Front-End Channel 1 Source Address 1
	volatile unsigned int	FCH1_SADDR2;		// 0x28 R/W 0x00000000 Front-End Channel 1 Source Address 2
	volatile unsigned int	FCH1_SFSIZE;		// 0x2C R/W 0x00000000 Front-End Channel 1 Source Frame Pixel Size
	volatile unsigned int	FCH1_SOFF;			// 0x30 R/W 0x00000000 Front-End Channel 1 Source Pixel Offset
	volatile unsigned int	FCH1_SISIZE;		// 0x34 R/W 0x00000000 Front-End Channel 1 Source Image Pixel Size
	volatile unsigned int	FCH1_WOFF;			// 0x38 R/W 0x00000000 Front-End Channel 1 Window Pixel Offset
	volatile unsigned int	FCH1_SCTRL;			// 0x3C R/W 0x00000000 Front-End Channel 1 Control
	volatile unsigned int	NOTDEFINE0[8];		// 0x40, 44, 48, 4C, 50, 54, 58, 5C
	volatile unsigned int	S0_CHROMA;			// 0x60 R/W 0x00000000 Source 0 Chroma-Key Parameter
	volatile unsigned int	S0_PAR;				// 0x64 R/W 0x00000000 Source 0 Arithmetic Parameter
	volatile unsigned int	S1_CHROMA;			// 0x68 R/W 0x00000000 Source 1 Chroma-Key Parameter
	volatile unsigned int	S1_PAR;				// 0x6C R/W 0x00000000 Source 1 Arithmetic Parameter
	volatile unsigned int	S2_CHROMA;			// 0x70 R/W 0x00000000 Source 2 Chroma-Key Parameter
	volatile unsigned int	S2_PAR;				// 0x74 R/W 0x00000000 Source 2 Arithmetic Parameter
	volatile unsigned int	S_CTRL;				// 0x78 R/W 0x00000000 Source Control Register
	volatile unsigned int	NOTDEFINE1;			//- 0x7C - - Reserved
	volatile unsigned int	OP0_PAT;			// 0x80 R/W 0x00000000 Source Operator 0 Pattern
	volatile unsigned int	OP1_PAT;			// 0x84 R/W 0x00000000 Source Operator 1 Pattern
	volatile unsigned int	OP_CTRL;			// 0x88 R/W 0x00000000 Source Operation Control Register
	volatile unsigned int	NOTDEFINE2;			//- 0x8C - - Reserved
	volatile unsigned int	BCH_DADDR0;			// 0x90 R/W 0x00000000 Back-End Channel Destination Address 0
	volatile unsigned int	BCH_DADDR1;			// 0x94 R/W 0x00000000 Back -End Channel Destination Address 1
	volatile unsigned int	BCH_DADDR2;			// 0x98 R/W 0x00000000 Back -End Channel Destination Address 2
	volatile unsigned int	BCH_DFSIZE;			// 0x9C R/W 0x00000000 Back -End Channel Destination Frame Pixel Size
	volatile unsigned int	BCH_DOFF;			// 0xA0 R/W 0x00000000 Back -End Channel Destination Pixel Offset
	volatile unsigned int	BCH_DCTRL;			// 0xA4 R/W 0x00000000 Back -End Channel Control
	volatile unsigned int	NOTDEFINE3[2];		// 0xA8, AC
	volatile unsigned int	GE_CTRL;			// 0xB0 R/W 0x00000000 Graphic Engine Control
	volatile unsigned int	GE_IREQ;			// 0xB4 R/W 0x00000000 Graphic Engine Interrupt Request
}GE, *PGE;

/************************************************************************
* EHI Definition
************************************************************************/
//The EHI registers are shown in Table 18.2. Chip Select 0 (HPCSN_L) base address is
//0xF5000000 and Chip Select 1 (HPCSN) 1 base address is 0xF00A0000.
//EHI register map
//#define HwEHICH0			0xF000000
//#define HwEHICH1			0xF00A000	
typedef struct _EHI{
	volatile unsigned int	EHST;					// 0x00 R/W R/W 0x00000080 Status register
	volatile unsigned int	EHIINT;					// 0x04 R/W R/W 0x00000000 Internal interrupt control register
	volatile unsigned int	EHEINT;					// 0x08 R/W R/W 0x00000000 External interrupt control register
	volatile unsigned int	EHA;					// 0x0C R R/W 0x00000000 Address register
	volatile unsigned int	EHAM ;					// 0x10 R/W R 0x00000000 Address masking register
	volatile unsigned int	EHD;					// 0x14 R/W R/W 0x00000000 Data register
	volatile unsigned int	EHSEM;					// 0x18 R/W R/W 0x00000000 Semaphore register
	volatile unsigned int	EHCFG;					// 0x1C R/W R/W 0x00000000 Configuration registers
	volatile unsigned int	EHIND;					// 0x20 R W 0x00000000 Index register
	volatile unsigned int	EHRWCS;					// 0x24 R R/W 0x00000000 Read/Write Control/Status register
}EHI,* PECHI;


/************************************************************************
*	DAI&CDIF Definition
************************************************************************/
//DAI Register Map (Base Address = 0xF0059000)
//#define HwDAI					0xF0059000
typedef struct _DAI{
	volatile unsigned int	DADI_L0;				// 0x00 R - Digital Audio Left Input Register 0
	volatile unsigned int	DADI_R0;				// 0x04 R - Digital Audio Right Input Register 0
	volatile unsigned int	DADI_L1;				// 0x08 R - Digital Audio Left Input Register 1
	volatile unsigned int	DADI_R1;				// 0x0C R - Digital Audio Right Input Register 1
	volatile unsigned int	DADI_L2;				// 0x10 R - Digital Audio Right Input Register 2
	volatile unsigned int	DADI_R2;				// 0x14 R - Digital Audio Right Input Register 2
	volatile unsigned int	DADI_L3;				// 0x18 R - Digital Audio Right Input Register 3
	volatile unsigned int	DADI_R3;				// 0x1C R - Digital Audio Right Input Register 3
	volatile unsigned int	DADO_L0;				// 0x20 R/W - Digital Audio Left Output Register 0
	volatile unsigned int	DADO_R0;				// 0x24 R/W - Digital Audio Right Output Register 0
	volatile unsigned int	DADO_L1;				// 0x28 R/W - Digital Audio Left Output Register 1
	volatile unsigned int	DADO_R1;				// 0x2C R/W - Digital Audio Right Output Register 1
	volatile unsigned int	DADO_L2;				// 0x30 R/W - Digital Audio Left Output Register 2
	volatile unsigned int	DADO_R2;				// 0x34 R/W - Digital Audio Right Output Register 2
	volatile unsigned int	DADO_L3;				// 0x38 R/W - Digital Audio Left Output Register 3
	volatile unsigned int	DADO_R3;				// 0x3C R/W - Digital Audio Right Output Register 3
	volatile unsigned int	DAMR;					// 0x40 R/W 0x00000000 Digital Audio Mode Register
	volatile unsigned int	DAVC;					// 0x44 R/W 0x0000 Digital Audio Volume Control Register
}DAI, *PDAI;
//CDIF Register Map (Base Address = 0xF0059080)
//#define HwCDIF				0xF0059080
typedef struct _CDIF{
	volatile unsigned int	CDDI_0;					// 0x80 R CD Digital Audio Input Register 0
	volatile unsigned int	CDDI_1;					// 0x84 R CD Digital Audio Input Register 1
	volatile unsigned int	CDDI_2;					// 0x88 R CD Digital Audio Input Register 2
	volatile unsigned int	CDDI_3;					// 0x8C R CD Digital Audio Input Register 3
	volatile unsigned int	CICR;						// 0x90 R/W 0x0000 CD Interface Control Register	
}CDIF, *PCDIF;

typedef struct _DAICDIF{
	volatile unsigned int	DADI_L0;				// 0x00 R - Digital Audio Left Input Register 0
	volatile unsigned int	DADI_R0;				// 0x04 R - Digital Audio Right Input Register 0
	volatile unsigned int	DADI_L1;				// 0x08 R - Digital Audio Left Input Register 1
	volatile unsigned int	DADI_R1;				// 0x0C R - Digital Audio Right Input Register 1
	volatile unsigned int	DADI_L2;				// 0x10 R - Digital Audio Right Input Register 2
	volatile unsigned int	DADI_R2;				// 0x14 R - Digital Audio Right Input Register 2
	volatile unsigned int	DADI_L3;				// 0x18 R - Digital Audio Right Input Register 3
	volatile unsigned int	DADI_R3;				// 0x1C R - Digital Audio Right Input Register 3
	volatile unsigned int	DADO_L0;				// 0x20 R/W - Digital Audio Left Output Register 0
	volatile unsigned int	DADO_R0;				// 0x24 R/W - Digital Audio Right Output Register 0
	volatile unsigned int	DADO_L1;				// 0x28 R/W - Digital Audio Left Output Register 1
	volatile unsigned int	DADO_R1;				// 0x2C R/W - Digital Audio Right Output Register 1
	volatile unsigned int	DADO_L2;				// 0x30 R/W - Digital Audio Left Output Register 2
	volatile unsigned int	DADO_R2;				// 0x34 R/W - Digital Audio Right Output Register 2
	volatile unsigned int	DADO_L3;				// 0x38 R/W - Digital Audio Left Output Register 3
	volatile unsigned int	DADO_R3;				// 0x3C R/W - Digital Audio Right Output Register 3
	volatile unsigned int	DAMR;					// 0x40 R/W 0x00000000 Digital Audio Mode Register
	volatile unsigned int	DAVC;					// 0x44 R/W 0x0000 Digital Audio Volume Control Register
	volatile unsigned int NOTDEFINE0[14];			// 0x48, 4C, 50, 54, 58, 5C, 60, 64, 68, 6C, 70, 74, 78, 7C
	volatile unsigned int	CDDI_0;					// 0x80 R CD Digital Audio Input Register 0
	volatile unsigned int	CDDI_1;					// 0x84 R CD Digital Audio Input Register 1
	volatile unsigned int	CDDI_2;					// 0x88 R CD Digital Audio Input Register 2
	volatile unsigned int	CDDI_3;					// 0x8C R CD Digital Audio Input Register 3
	volatile unsigned int	CICR;					// 0x90 R/W 0x0000 CD Interface Control Register	
}DAICDIF, *PDAICDIF;

/************************************************************************
*	GPSB Definition
************************************************************************/
//SPDIF Register Map (Base Address = 0xF005C000)
//#define HwGPSB				0xF0057000
typedef struct _GPSBCH0{
	volatile unsigned int	PORT;						// 0x000 R/W 0x0000 Data port
	volatile unsigned int	STAT;						// 0x004 R/W 0x0000 Status register
	volatile unsigned int	INTEN;						// 0x008 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODE;						// 0x00C R/W 0x0000 Mode register
	volatile unsigned int	CTRL;						// 0x010 R/W 0x0000 Control register
	volatile unsigned int	NOTDEFINE0[3];				// 0x014, 18, 1C
	volatile unsigned int	TXBASE;						// 0x020 R/W 0x0000 TX base address register
	volatile unsigned int	RXBASE;						// 0x024 R/W 0x0000 RX base address register
	volatile unsigned int	PACKET;						// 0x028 R/W 0x0000 Packet register
	volatile unsigned int	DMACTR;						// 0x02C R/W 0x0000 DMA control register
	volatile unsigned int	DMASTR;						// 0x030 R/W 0x0000 DMA status register
	volatile unsigned int	DMAICR;						// 0x034 R/W 0x0000 DMA interrupt control register
}GPSBCH0, *PGPSBCH0;

typedef struct _GPSBCH1{
	volatile unsigned int	PORT;						// 0x100 R/W 0x0000 Data port
	volatile unsigned int	STAT;						// 0x104 R/W 0x0000 Status register
	volatile unsigned int	INTEN ;						// 0x108 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODE;						// 0x10C R/W 0x0000 Mode register
	volatile unsigned int	CTRL;						// 0x110 R/W 0x0000 Control register
	volatile unsigned int	NOTDEFINE0[3];				// 0x114, 18, 1C
	volatile unsigned int	TXBASE;						// 0x120 R/W 0x0000 TX base address register
	volatile unsigned int	RXBASE;						// 0x124 R/W 0x0000 RX base address register
	volatile unsigned int	PACKET;						// 0x128 R/W 0x0000 Packet register
	volatile unsigned int	DMACTR;						// 0x12C R/W 0x0000 DMA control register
	volatile unsigned int	DMASTR;						// 0x130 R/W 0x0000 DMA status register
	volatile unsigned int	DMAICR;						// 0x130 R/W 0x0000 DMA status register
}GPSBCH1, *PGPSBCH1;

typedef struct _GPSBCH2{
	volatile unsigned int	PORT;						// 0x200 R/W 0x0000 Data port
	volatile unsigned int	STAT;						// 0x204 R/W 0x0000 Status register
	volatile unsigned int	INTEN ;						// 0x208 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODE;						// 0x20C R/W 0x0000 Mode register
	volatile unsigned int	CTRL;						// 0x210 R/W 0x0000 Control register
}GPSBCH2, *PGPSBCH2;

typedef struct _GPSBCH3{
	volatile unsigned int	PORT;						// 0x300 R/W 0x0000 Data port
	volatile unsigned int	STAT;						// 0x304 R/W 0x0000 Status register
	volatile unsigned int	INTEN;						// 0x308 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODE;						// 0x30C R/W 0x0000 Mode register
	volatile unsigned int	CTRL;						// 0x310 R/W 0x0000 Control register
}GPSBCH3, *PGPSBCH3;

typedef struct _GPSB{
	volatile unsigned int	PORTCH0;					// 0x000 R/W 0x0000 Data port
	volatile unsigned int	STATCH0;					// 0x004 R/W 0x0000 Status register
	volatile unsigned int	INTENCH0;					// 0x008 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODECH0;					// 0x00C R/W 0x0000 Mode register
	volatile unsigned int	CTRLCH0;					// 0x010 R/W 0x0000 Control register
	volatile unsigned int	NOTDEFINE0[3];				// 0x014, 18, 1C
	volatile unsigned int	TXBASECH0;					// 0x020 R/W 0x0000 TX base address register
	volatile unsigned int	RXBASECH0;					// 0x024 R/W 0x0000 RX base address register
	volatile unsigned int	PACKETCH0;					// 0x028 R/W 0x0000 Packet register
	volatile unsigned int	DMACTRCH0;					// 0x02C R/W 0x0000 DMA control register
	volatile unsigned int	DMASTRCH0;					// 0x030 R/W 0x0000 DMA status register
	volatile unsigned int	DMAICRCH0;					// 0x034 R/W 0x0000 DMA interrupt control register
	volatile unsigned int	NOTDEFINE1[50];				// 0x038, 3C, (4[0,4,8,c])*(12[4,5,6,7,8,9,A,B,C,D,E,F])
	volatile unsigned int	PORTCH1;					// 0x100 R/W 0x0000 Data port
	volatile unsigned int	STATCH1;					// 0x104 R/W 0x0000 Status register
	volatile unsigned int	INTENCH1;					// 0x108 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODECH1;					// 0x10C R/W 0x0000 Mode register
	volatile unsigned int	CTRLCH1;					// 0x110 R/W 0x0000 Control register
	volatile unsigned int	NOTDEFINE2[3];				// 0x114, 18, 1C
	volatile unsigned int	TXBASECH1;					// 0x120 R/W 0x0000 TX base address register
	volatile unsigned int	RXBASECH1;					// 0x124 R/W 0x0000 RX base address register
	volatile unsigned int	PACKETCH1;					// 0x128 R/W 0x0000 Packet register
	volatile unsigned int	DMACTRCH1;					// 0x12C R/W 0x0000 DMA control register
	volatile unsigned int	DMASTRCH1;					// 0x130 R/W 0x0000 DMA status register
	volatile unsigned int	DMAICRCH1;					// 0x130 R/W 0x0000 DMA status register
	volatile unsigned int	NOTDEFINE3[51];				// 0x134, 38, 3C, (4[0,4,8,c])*(12[4,5,6,7,8,9,A,B,C,D,E,F])
	volatile unsigned int	PORTCH2;					// 0x200 R/W 0x0000 Data port
	volatile unsigned int	STATCH2;					// 0x204 R/W 0x0000 Status register
	volatile unsigned int	INTENCH2;					// 0x208 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODECH2;					// 0x20C R/W 0x0000 Mode register
	volatile unsigned int	CTRLCH2;					// 0x210 R/W 0x0000 Control register
	volatile unsigned int	NOTDEFINE4[59];				// 0x214, 18, 1C, (4[0,4,8,c])*(14[2,3,4,5,6,7,8,9,A,B,C,D,E,F])
	volatile unsigned int	PORTCH3;					// 0x300 R/W 0x0000 Data port
	volatile unsigned int	STATCH3;					// 0x304 R/W 0x0000 Status register
	volatile unsigned int	INTENCH3;					// 0x308 R/W 0x0000 Interrupt enable
	volatile unsigned int	MODECH3;					// 0x30C R/W 0x0000 Mode register
	volatile unsigned int	CTRLCH3;					// 0x310 R/W 0x0000 Control register
	//volatile unsigned int	PCFG;						// 0x800 R/W 0x03020100 Port Configuration Register
	//volatile unsigned int	PIDT;						// 0xF00 R/W
}GPSB, *PGPSB;

/************************************************************************
*	SPDIF INTERFACE Definition
************************************************************************/
//SPDIF Register Map (Base Address = 0xF005C000)
//#define HwSPDIF 			0xF005C000
/*
typedef struct _SPDIF{
volatile unsigned int	TxVersion;				// 0x00 R Version Register
volatile unsigned int	TxConfig;					// 0x04 R/W Configuration Register
volatile unsigned int	TxChStat;					// 0x08 R/W Channel Status Control Register
volatile unsigned int	TxIntMask;				// 0x0C R/W Interrupt Mask Register
volatile unsigned int	TxIntStat;				// 0x10 R/W Interrupt Status Register
volatile unsigned int	NOTDEFINE0[27];		// 0x14, 18, 1C + 24 (4[0,4,8,C]) * (6[2,3,4,5,6,7])
volatile unsigned int	UserData[23];			// 0x80~0xDC W - User Data Buffer
volatile unsigned int	NOTDEFINE0[27];		// 0x14, 18, 1C + 24 (4[0,4,8,C]) * (6[2,3,4,5,6,7])
volatile unsigned int	ChStatus;					// 0x100~0x15C W - Channel Status Buffer
volatile unsigned int	TxBuffer;					// 0x200~0x210 W - Transmit Data Buffer
volatile unsigned int	DMACFG;						// 0x400 R/W - Additional Configuration for DMA
}SPDIF,* SPDIF;
*/
/************************************************************************
*	UART ENGINEDefinition
************************************************************************/
//The base address of UART channel 0, 1, 2, and 3 are 0xF0055000, 0xF0055100,
//0xF0055200, and 0xF0055300 respectively.
//UART Register Map
//#define HwUART0 			0xF0055000
//#define HwUART1 			0xF0055100
//#define HwUART2 			0xF0055200
//#define HwUART3 			0xF0055300
typedef struct _UART{
	union
	{
		volatile unsigned int	RBR;				// 0x00 R Unknown Receiver Buffer Register(DLAB = 0)
		volatile unsigned int	THR;				// 0x00 W 0x00 Transmitter Holding Register (DLAB=0)
		volatile unsigned int	DLL;				// 0x00 R/W 0x00 Divisor Latch (LSB) (DLAB=1)
	};
	union
	{
		volatile unsigned int	IER;				// 0x04 R/W 0x00 Interrupt Enable Register (DLAB=0)
		volatile unsigned int	DLM;				// 0x04 R/W 0x00 Divisor Latch (MSB) (DLAB=1)
	};
	union
	{
		volatile unsigned int	IIR;				// 0x08 R Unknown Interrupt Ident. Register (DLAB=0)
		volatile unsigned int	FCR;				// 0x08 W 0xC0 FIFO Control Register (DLAB=1)
	};
	volatile unsigned int	LCR;					// 0x0C R/W 0x03 Line Control Register
	volatile unsigned int	MCR;					// 0x10 R/W 0x00 MODEM Control Register
	volatile unsigned int	LSR;					// 0x14 R Unknown Line Status Register
	volatile unsigned int	MSR;					// 0x18 R Unknown MODEM Status Register
	volatile unsigned int	SCR;					// 0x1C R/W 0x00 Scratch Register
	volatile unsigned int	AFT;					// 0x20 R/W 0x00 AFC Trigger Level Register
	volatile unsigned int	UCR;					// 0x24 R/W 0x00 UART Control Register
	volatile unsigned int	NOTDEFINE0[6];			// 0x28, 2C, 30, 34, 38, 3C, 
	volatile unsigned int	SRBR;					// 0x40 R Unknown Rx Buffer Register
	volatile unsigned int	STHR;					// 0x44 W 0x00 Transmitter Holding Register
	volatile unsigned int	SDLL;					// 0x48 R/W 0x00 Divisor Latch (LSB)
	volatile unsigned int	SDLM;					// 0x4C R/W 0x00 Divisor Latch (MSB)
	volatile unsigned int	SIER;					// 0x50 R/W 0x00 Interrupt Enable Register
	volatile unsigned int	IRCFG ;					// 0x80 R/W 0x00 IRDA Configuration Register
}UART,*PUART;

/************************************************************************
* CKC Definition
************************************************************************/
//CKC Register Map (Base Address = 0xF3000000)
//#define HwCLKCTRL 		0xF3000000
typedef struct _CKC{
	volatile unsigned int	CLKCTRL;				// 0x00 R/W 0x800FF011 CPU & Bus Clock Control Register
	volatile unsigned int	PLL0CFG;				// 0x04 R/W 0x00015003 PLL0 Configuration Register
	volatile unsigned int	PLL1CFG;				// 0x08 R/W 0x00015003 PLL1 Configuration Register
	volatile unsigned int	CLKDIVC;				// 0x0C R/W 0x81828383 Divided Clock Configuration Register
	volatile unsigned int	CLKDIVC1;				// 0x10 R/W 0x00000000 PLL 0 Divider 1 Configuration Register
	volatile unsigned int	MODECTR;				// 0x14 R/W 0x00010000 Operating Mode Control Register
	volatile unsigned int	BCLKCTR0;				// 0x18 R/W 0xFFFFFFFF Bus Clock Mask Control Register for Group 0
	volatile unsigned int	BCLKCTR1;				// 0x1C R/W 0xFFFFFFFF Bus Clock Mask Control Register for Group 1
	volatile unsigned int	SWRESET0;				// 0x20 R/W 0x00800000 Software Reset Control Register for Group 0
	volatile unsigned int	SWRESET1;				// 0x24 R/W 0x00000000 Software Reset Control Register for Group 1
	volatile unsigned int	WDTCTRL;				// 0x28 R/W 0x00000000 Watchdog Control Register
	volatile unsigned int	NOTDEFINE0[21];			// 0x2C 20=(4[0,4,8,C])*(5[3,4,5,6,7])
	volatile unsigned int	PCK_USB11H;				// 0x80 R/W 0x14000000 USB11H Clock Control Register
	volatile unsigned int	PCK_SDMMC;				// 0x84 R/W 0x14000000 SD/MMC Clock Control Register
	volatile unsigned int	PCK_MSTICK;				// 0x88 R/W 0x14000000 Memory Stick Clock Control Register
	volatile unsigned int	PCK_I2C;				// 0x8C R/W 0x14000000 I2C Clock Control Register
	volatile unsigned int	PCK_LCD;				// 0x90 R/W 0x14000000 LCD Clock Control Register
	volatile unsigned int	PCK_CAM;				// 0x94 R/W 0x14000000 Camera Clock Control Register
	volatile unsigned int	PCK_UART0;				// 0x98 R/W 0x14000000 UART0 Clock Control Register
	volatile unsigned int	PCK_UART1;				// 0x9C R/W 0x14000000 UART1 Clock Control Register
	volatile unsigned int	PCK_UART2;				// 0xA0 R/W 0x14000000 UART2 Clock Control Register
	volatile unsigned int	PCK_UART3;				// 0xA4 R/W 0x14000000 UART3 Clock Control Register
	volatile unsigned int	PCK_TCT;				// 0xA8 R/W 0x14000000 Timer T-Clock Control Register
	volatile unsigned int	PCK_TCX;				// 0xAC R/W 0x14000000 Clock Output for GPIO[2]
	volatile unsigned int	PCK_TCZ;				// 0xB0 R/W 0x14000000 Clock Output for GPIO[3]
	volatile unsigned int	PCK_DAI;				// 0xB4 R/W 0x0A000000 DAI Clock Control Register
	volatile unsigned int	PCK_GPSB0;				// 0xB8 R/W 0x14000000 GPSB0 Clock Control Register
	volatile unsigned int	PCK_GPSB1;				// 0xBC R/W 0x14000000 GPSB1 Clock Control Register
	volatile unsigned int	PCK_GPSB2;				// 0xC0 R/W 0x14000000 GPSB2 Clock Control Register
	volatile unsigned int	PCK_GPSB3;				// 0xC4 R/W 0x14000000 GPSB3 Clock Control Register
	volatile unsigned int	PCK_ADC;				// 0xC8 R/W 0x14000000 SPDIF TX Clock Control Register
	volatile unsigned int	PCK_SPDIF;				// 0xCC R/W 0x14000000 SPDIF TX Clock Control Register
	volatile unsigned int	PCK_RFREQ;				// 0xD0 R/W 0x14000000 SDRAM Refresh Clock Control Reigster
	volatile unsigned int	PCK_SCALER;				// 0xD4 R/W 0x14000000 CIF Scaler Clock Control Register
	volatile unsigned int	PCK_EHI0;				// 0xD8 R/W 0x14000000 EHI0 Clock Control Register
	volatile unsigned int	PCK_EHI1;				// 0xDC R/W 0x14000000 EHI1 Clock Control Register
	volatile unsigned int	BCKVCFG;				// 0xE0 R/W 0xFFFFFFFF Bus Clock Mask Register for Video Block
	volatile unsigned int	NOTDEFINE1;				// 0xE4
	volatile unsigned int	MCLKCTRL;				// 0xE8 R/W 0x8000000F Main Processor Clock Control Register
	volatile unsigned int	SCLKCTRL;				// 0xEC R/W 0x8000000F Sub Processor Clock Control Register
	volatile unsigned int	BCLKMSKE0;				// 0xF0 R/W 0xFFFFFFFF Bus Clock Mask Enable Register for Group 0
	volatile unsigned int	BCLKMSKE1;				// 0xF4 R/W 0xFFFFFFFF Bus Clock Mask Enable Register for Group 1
	volatile unsigned int	OPTION0;				// 0xFC R/W 0x00000000 Option Register
}CKC, *PCKC;

/************************************************************************
*	VECTORED Definition
************************************************************************/
//#define HwEINTSEL0		0xF005A134
//#define HwEINTSEL1		0xF005A138
//#define HwIRQSEL			0xF005A13C
//Priority Interrupt Controller Register Map (Base Address = 0xF3001000)
//#define HwIEN					0xF3001000
typedef struct _IEN{
	volatile unsigned int	IEN;					// 0x00 R/W 0x00000000 Interrupt Enable Register
	volatile unsigned int	CLR;					// 0x04 R/W 0x00000000 Interrupt Clear Register
	volatile unsigned int	STS;					// 0x08 R Unknown Interrupt Status Register
	volatile unsigned int	SEL;					// 0x0C R/W 0x00000000 IRQ or FIR Selection Register
	volatile unsigned int	SRC;					// 0x10 R Unknown Source Interrupt Status Register
	volatile unsigned int	MSTS;					// 0x14 R 0x00000000 Masked Status Register
	volatile unsigned int	TIG;					// 0x18 R/W 0x00000000 Test Interrupt Generation Register
	volatile unsigned int	POL;					// 0x1C R/W 0x00000000 Interrupt Polarity Register
	volatile unsigned int	IRQ;					// 0x20 R 0x00000000 IRQ Raw Status Register
	volatile unsigned int	FIQ;					// 0x24 R Unknown FIQ Status Register
	volatile unsigned int	MIRQ;					// 0x28 R 0x00000000 Masked IRQ Status Register
	volatile unsigned int	MFIQ;					// 0x2C R 0x00000000 Masked FIQ Status Register
	volatile unsigned int	MODE;					// 0x30 R/W 0x00000000 Trigger Mode Register ? Level or Edge
	volatile unsigned int	SYNC;					// 0x34 R/W 0xFFFFFFFF Synchronization Enable Register
	volatile unsigned int	WKEN;					// 0x38 R/W 0x00000000 Wakeup Event Enable Register
	volatile unsigned int	MODEA;					// 0x3C R/W 0x00000000 Both Edge or Single Edge Register
	volatile unsigned int	INTMSK;					// 0x40 R/W 0xFFFFFFFF Interrupt Output Masking Register
	volatile unsigned int	ALLMSK;					// 0x44 R/W 0x00000003 All Mask Register
}IEN, *PIEN;

//Vectored Interrupt Controller Register Map (Base Address = 0xF3001080)
//#define HwVIC					0xF3001080
typedef struct _VIC{
	volatile unsigned int	VAIRQ;					// 0x00 R 0x800000XX IRQ Vector Register
	volatile unsigned int	VAFIQ;					// 0x04 R 0x800000XX FIQ Vector Register
	volatile unsigned int	VNIRQ;					// 0x08 R 0x800000XX IRQ Vector Number Register
	volatile unsigned int	VNFIQ;					// 0x0C R 0x800000XX FIQ Vector Number Register
	volatile unsigned int	VCTRL;					// 0x10 R/W 0x00000000 Vector Control Register
	volatile unsigned int	NOTDEFINE0[3];			// 0x14, 18, 1C	
	volatile unsigned int	PRI04;					// 0x20 R/W 0x03020100 Priorities for Interrupt 0 ~ 3
	volatile unsigned int	PRI08;					// 0x24 R/W 0x07060504 Priorities for Interrupt 4 ~ 7
	volatile unsigned int	PRI12;					// 0x28 R/W 0x0B0A0908 Priorities for Interrupt 8 ~ 11
	volatile unsigned int	PRI16;					// 0x2C R/W 0x0F0E0D0C Priorities for Interrupt 12 ~ 15
	volatile unsigned int	PRI20;					// 0x30 R/W 0x13121110 Priorities for Interrupt 16 ~ 19
	volatile unsigned int	PRI24;					// 0x34 R/W 0x17161514 Priorities for Interrupt 20 ~ 23
	volatile unsigned int	PRI28;					// 0x38 R/W 0x1B1A1918 Priorities for Interrupt 24 ~ 27
	volatile unsigned int	PRI32;					// 0x3C R/W 0x1F1E1D1C Priorities for Interrupt 28 ~ 31
}VIC, *PVIC;

/************************************************************************
*	TIMER / COUNTER Definition
************************************************************************/
//Timer/Counter Register Map (Base Address = 0xF3003000)
//#define HwTIMER				0xF3003000
typedef struct _TIMER{
	volatile unsigned int	TCFG0;					// 0x00 R/W 0x00 Timer/Counter 0 Configuration Register
	volatile unsigned int	TCNT0;					// 0x04 R/W 0x0000 Timer/Counter 0 Counter Register
	volatile unsigned int	TREF0;					// 0x08 R/W 0xFFFF Timer/Counter 0 Reference Register
	volatile unsigned int	TMREF0;					// 0x0C R/W 0x0000 Timer/Counter 0 Middle Reference Register
	volatile unsigned int	TCFG1;					// 0x10 R/W 0x00 Timer/Counter 1 Configuration Register
	volatile unsigned int	TCNT1;					// 0x14 R/W 0x0000 Timer/Counter 1 Counter Register
	volatile unsigned int	TREF1;					// 0x18 R/W 0xFFFF Timer/Counter 1 Reference Register
	volatile unsigned int	TMREF1;					// 0x1C R/W 0x0000 Timer/Counter 1 Middle Reference Register
	volatile unsigned int	TCFG2;					// 0x20 R/W 0x00 Timer/Counter 2 Configuration Register
	volatile unsigned int	TCNT2;					// 0x24 R/W 0x0000 Timer/Counter 2 Counter Register
	volatile unsigned int	TREF2;					// 0x28 R/W 0xFFFF Timer/Counter 2 Reference Register
	volatile unsigned int	TMREF2;					// 0x2C R/W 0x0000 Timer/Counter 2 Middle Reference Register
	volatile unsigned int	TCFG3;					// 0x30 R/W 0x00 Timer/Counter 3 Configuration Register
	volatile unsigned int	TCNT3;					// 0x34 R/W 0x0000 Timer/Counter 3 Counter Register
	volatile unsigned int	TREF3;					// 0x38 R/W 0xFFFF Timer/Counter 3 Reference Register
	volatile unsigned int	TMREF3;					// 0x3C R/W 0x0000 Timer/Counter 3 Middle Reference Register
	volatile unsigned int	TCFG4;					// 0x40 R/W 0x00 Timer/Counter 4 Configuration Register
	volatile unsigned int	TCNT4;					// 0x44 R/W 0x00000 Timer/Counter 4 Counter Register
	volatile unsigned int	TREF4;					// 0x48 R/W 0xFFFFF Timer/Counter 4 Reference Register
	volatile unsigned int	NOTDEFINE0;				// 0x4C
	volatile unsigned int	TCFG5;					// 0x50 R/W 0x00 Timer/Counter 5 Configuration Register
	volatile unsigned int	TCNT5;					// 0x54 R/W 0x00000 Timer/Counter 5 Counter Register
	volatile unsigned int	TREF5;					// 0x58 R/W 0xFFFFF Timer/Counter 5 Reference Register
	volatile unsigned int	NOTDEFINE1;				// 0x5C
	volatile unsigned int	TIREQ ;					// 0x60 R/W 0x0000 Timer/Counter n Interrupt Request Register
	volatile unsigned int	NOTDEFINE2[3];			// 0x64, 68, 6C
	volatile unsigned int	TWDCFG;					// 0x70 R/W 0x0000 Watchdog Timer Configuration Register
	volatile unsigned int	TWDCLR;					// 0x74 W - Watchdog Timer Clear Register
	volatile unsigned int	NOTDEFINE3[2];			// 0x78, 7C
	volatile unsigned int	TC32EN;					// 0x80 R/W 0x00007FFF 32-bit Counter Enable / Pre-scale Value
	volatile unsigned int	TC32LDV;				// 0x84 R/W 0x00000000 32-bit Counter Load Value
	volatile unsigned int	TC32CMP0;				// 0x88 R/W 0x00000000 32-bit Counter Match Value 0
	volatile unsigned int	TC32CMP1;				// 0x8C R/W 0x00000000 32-bit Counter Match Value 1
	volatile unsigned int	TC32PCNT;				// 0x90 R/W - 32-bit Counter Current Value (pre-scale counter)
	volatile unsigned int	TC32MCNT;				// 0x94 R/W - 32-bit Counter Current Value (main counter)
	volatile unsigned int	TC32IRQ;				// 0x98 R/W 0x0000---- 32-bit Counter Interrupt ControlTCFG0 0x00 R/W 0x00 Timer/Counter 0 Configuration Register
}TIMER, *PTIMER;

/************************************************************************
*	I2C CONTROLLER Definition
************************************************************************/
//I2C Register Map (Base Address = 0xF0052000)
//#define HwI2C					0xF0052000
#define HwIRQSTR	*(volatile unsigned long *)0xF00520C0
typedef struct _I2CM{
	volatile unsigned int	PRES;				// 0x00 R/W 0xFFFF Clock Prescale register
	volatile unsigned int	CTRL;				// 0x04 R/W 0x0000 Control Register
	volatile unsigned int	TXR;					// 0x08 W 0x0000 Transmit Register
	volatile unsigned int	CMD;					// 0x0C W 0x0000 Command Register
	volatile unsigned int	RXR;					// 0x10 R 0x0000 Receive Register
	volatile unsigned int	SR;					// 0x14 R 0x0000 Status Register
	volatile unsigned int	TIME;				// 0x18 R/W 0x0000 Timing Control Register
}I2CM,*PI2CM;

typedef struct _I2C{
	volatile unsigned int	PRESMA0;				// 0x00 R/W 0xFFFF Clock Prescale register
	volatile unsigned int	CTRLMA0;				// 0x04 R/W 0x0000 Control Register
	volatile unsigned int	TXRMA0;					// 0x08 W 0x0000 Transmit Register
	volatile unsigned int	CMDMA0;					// 0x0C W 0x0000 Command Register
	volatile unsigned int	RXRMA0;					// 0x10 R 0x0000 Receive Register
	volatile unsigned int	SRMA0;					// 0x14 R 0x0000 Status Register
	volatile unsigned int	TIMEMA0;				// 0x18 R/W 0x0000 Timing Control Register
	volatile unsigned int	NOTDEFINE0[9];			// 0x1C, 8= 2-, 3-
	volatile unsigned int	PRESMA1;				// 0x40 R/W 0xFFFF Clock Prescale register
	volatile unsigned int	CTRLMA1;				// 0x44 R/W 0x0000 Control Register
	volatile unsigned int	TXRMA1;					// 0x48 W 0x0000 Transmit Register
	volatile unsigned int	CMDMA1;					// 0x4C W 0x0000 Command Register
	volatile unsigned int	RXRMA1;					// 0x50 R 0x0000 Receive Register
	volatile unsigned int	SRMA1;					// 0x54 R 0x0000 Status Register
	volatile unsigned int	TIMEMA1;				// 0x58 R/W 0x0000 Timing Control Register
	volatile unsigned int	NOTDEFINE1[9];			// 0x5C, 8= 6-, 7-
	volatile unsigned int	PORTSLV;				// 0x80 R/W - Data Access port (TX/RX FIFO)
	volatile unsigned int	CTLSLV;					// 0x84 R/W 0x00000000 Control register
	volatile unsigned int	ADDRSLV;				// 0x88 W 0x00000000 Address register
	volatile unsigned int	INTSLV;					// 0x8C W 0x00000000 Interrupt Enable Register
	volatile unsigned int	STATSLV;				// 0x90 R 0x00000000 Status Register
	volatile unsigned int	MBFSLV;					// 0x9C R/W 0x00000000 Buffer Valid Flag
	volatile unsigned int	MB0SLV;					// 0xA0 R/W 0x00000000 Data Buffer 0 (Byte 3 ~ 0)
	volatile unsigned int	MB1SLV;					// 0xA4 R/W 0x00000000 Data Buffer 1 (Byte 7 ~ 4)
	volatile unsigned int	NOTDEFINE2[6];			// 0xA8 AC 4= B-
	volatile unsigned int	IRQSTR;					// 0xC0 R 0x00000000 IRQ Status Register
}I2C, *PI2C;
/************************************************************************
*	ADC INTERFACE Definition
************************************************************************/
//ADC Controller Register Map (Base Address = 0xF3004000)
//#define HwADC					0xF3004000
typedef struct _ADC{
	volatile unsigned int	ADCCON;					// 0x00 R/W 0x00000018 ADC Control Register
	volatile unsigned int	ADCDATA;				// 0x04 R Unknown ADC Data Register
	volatile unsigned int	NOTDEFINE0[30];			// 0x08, 0C, 28=1-, 2-, 3-, 4-, 5-, 6-, 7-
	volatile unsigned int	ADCCONA;				// 0x80 R/W 0x00000018 ADC Control Register A
	volatile unsigned int	ADCSTATUS;				// 0x84 R/W Unknown ADC Status Register
	volatile unsigned int	ADCCFG;					// 0x88 R/W 0x00002400 ADC Configuration Register
}ADC, *PADC;

/************************************************************************
* RTC Definition
************************************************************************/
//RTC Register Map (Base Address = 0xF3002000)
//#define HwRTC					0xF3002000
typedef struct _RTC{
	volatile unsigned int	RTCCON;					// 0x00 R/W 0x00 RTC Control Register
	volatile unsigned int	INTCON;					// 0x04 R/W - RTC Interrupt Control Register
	volatile unsigned int	RTCALM;					// 0x08 R/W - RTC Alarm Control Register
	volatile unsigned int	ALMSEC;					// 0x0C R/W - Alarm Second Data Register
	volatile unsigned int	ALMMIN;					// 0x10 R/W - Alarm Minute Data Register
	volatile unsigned int	ALMHOUR;				// 0x14 R/W - Alarm Hour Data Register
	volatile unsigned int	ALMDATE;				// 0x18 R/W - Alarm Date Data Register
	volatile unsigned int	ALMDAY;					// 0x1C R/W - Alarm Day of Week Data Register
	volatile unsigned int	ALMMON;					// 0x20 R/W - Alarm Month Data Register
	volatile unsigned int	ALMYEAR;				// 0x24 R/W - Alarm Year Data Register
	volatile unsigned int	BCDSEC;					// 0x28 R/W - BCD Second Register
	volatile unsigned int	BCDMIN;					// 0x2C R/W - BCD Minute Register
	volatile unsigned int	BCDHOUR;				// 0x30 R/W - BCD Hour Register
	volatile unsigned int	BCDDATE;				// 0x34 R/W - BCD Date Register
	volatile unsigned int	BCDDAY;					// 0x38 R/W - BCD Day of Week Register
	volatile unsigned int	BCDMON;					// 0x3C R/W - BCD Month Register
	volatile unsigned int	BCDYEAR;				// 0x40 R/W - BCD Year Register
	volatile unsigned int	RTCIM;					// 0x44 R/W - RTC Interrupt Mode Register
	volatile unsigned int	RTCPEND;				// 0x48 R/W - RTC Interrupt Pending Register
}RTC, *PRTC;

/************************************************************************
*	EXTERNAL MEMORY CONTRELLER Definition
************************************************************************/
//Channel 0 Memory Controller Register Map (Base Address = 0xF1000000)
//#define HwEMCCH0					0xF1000000
//Channel 1 Memory Controller Register Map (Base Address = 0xF1000028)
//#define HwEMCCH1					0xF1000028
typedef struct _EMC{
	volatile unsigned int	SDCFG;					// 0x00 R/W 0x62E97080 SDRAM Configuration Register
	volatile unsigned int	SDFSM;					// 0x04 R 0x00000000 SDRAM FSM Status Register
	volatile unsigned int	MCFG;					// 0x08 R/W 0x01000042 Miscellaneous Configuration Register
	volatile unsigned int	TST;					// 0x0C W 0x00000000 Should not write to this ? it¡¯s for TEST
	volatile unsigned int	CSCFG0;					// 0x10 R/W 0x468AC809 External Chip Select 0 Config. Register
	volatile unsigned int	CSCFG1;					// 0x14 R/W 0x508AD01A External Chip Select 1 Config. Register
	volatile unsigned int	CSCFG2;					// 0x18 R/W 0x608AD03A External Chip Select 2 Config. Register
	volatile unsigned int	CSCFG3;					// 0x1C R/W 0x728AD01A External Chip Select 3 Config. Register
	volatile unsigned int	CLKCFG;					// 0x20 R/W 0x00000A05 Memory Controller Version & Periodic Clock
	volatile unsigned int	SDCMD;					// 0x24 R/W - SDRAM Command Write Register
	volatile unsigned int	SDCFG1;					// 0x28 R/W 0xFFFFFFFF Extra SDRAM Configuration Register
}EMC, *PEMC;

//NAND flash Register Map (Base Address = N * 0x10000000)
//Chip Select 0 : 16bit, SRAM, Base = 0x40000000, tSTP=1, tPW=1, tHLD=1
//Chip Select 1 : 32bit, IDE, Base = 0x50000000, not use Ready, tSTP=2, tPW=3, tHLD=2
//Chip Select 2 : 32bit, NAND, Base = 0x60000000, AMSK=1, PSIZE=1, cLADR=3, tSTP=2, tPW=7, tHLD=2
//Chip Select 3 : 16bit, NOR, Base = 0x70000000, tSTP=2, tPW=3, tHLD=2
//#define NAND_CS				0x60000000
//#define HwNAND				0x60000000
typedef struct _NAND{
	volatile unsigned int	NDCMD;					// 0x00 R/W - Command Cycle Register
	volatile unsigned int	NDLADR;					// 0x04 W - Linear Address Cycle Register
	volatile unsigned int	NDRADR;					// 0x08 W - Row Address Cycle Register
	volatile unsigned int	NDIADR;					// 0x0C W - Single Address Cycle Register
	volatile unsigned int	NDDATA;					// 0x10 R/W - Data Access Cycle Register
}NAND, *PNAND;

/************************************************************************
* SDRAM INTERFACE Definition
************************************************************************/
//SRAMIFRegister map (0xF0080000)
//#define HwSDRAMIF			0xF0080000
typedef struct _SDRAMIF{
	volatile unsigned int	CTRLCS0XA0;				// 0x00 R/W 0xA0229011 Control register for SRAMIF_CS0 when SRAMIF_XA=0 and 1
	volatile unsigned int	CTRLCS0XA2;				// 0x04 R/W 0xA0429021 Control register for SRAMIF_CS0 when SRAMIF_XA=2 and 3
	volatile unsigned int	CTRLCS1XA0;				// 0x08 R/W 0xA0129009 Control register for SRAMIF_CS1 when SRAMIF_XA=0 and 1
	volatile unsigned int	CTRLCS1XA2;				// 0x0C R/W 0xA0229011 Control register for SRAMIF_CS1 when SRAMIF_XA=2 and 3
	volatile unsigned int	CS0XA0;					// 0x10 R/W -if this register is read or written, reading or writing operations are generated on SRAMIF_CS0 while SRAMIF_XA = 0.
	volatile unsigned int	CS0XA1;					// 0x14 R/W -If this register is read or written, reading or writing operations are generated on SRAMIF_CS0 while SRAMIF_XA= 1.
	volatile unsigned int	CS0XA2;					// 0x18 R/W -if this register is read or written, reading or writing operations are generated on SRAMIF_CS0 while SRAMIF_XA= 2.
	volatile unsigned int	CS0XA3;					// 0x1C R/W -If this register is read or written, reading or writing operations are generated on SRAMIF_CS0 while SRAMIF_XA= 3.
	volatile unsigned int	CS1XA0;					// 0x20 R/W -if this register is read or written, reading or writing operations are generated on SRAMIF_CS1 while SRAMIF_XA=0
	volatile unsigned int	CS1XA1;					// 0x24 R/W -If this register is read or written, reading or writing operations are generated on SRAMIF_CS1 while SRAMIF_XA=1
	volatile unsigned int	CS1XA2;					// 0x28 R/W -if this register is read or written, reading or writing operations are generated on SRAMIF_CS1 while SRAMIF_XA=2
	volatile unsigned int	CS1XA3;					// 0x2C R/W -If this register is read or written, reading or writing operations are generated on SRAMIF_CS1 while SRAMIF_XA=3
}SDRAMIF, *PSDRAMIF;

/************************************************************************
* MAILBOX Definition
************************************************************************/
//MAILBOX Register Map (Base Address = 0xF4000000)
//#define HwMAILBOX			0xF4000000
typedef struct _MAILBOX{
	volatile unsigned int	MBOXTXD;				// 0x00 ~ 0x1C R/W - Transmit FIFO Data Region
	volatile unsigned int	NOTDEFINE0[7];			// 0x04, 08, 0C, 10, 14, 18, 1C
	volatile unsigned int	MBOXRXD;				// 0x20 ~ 0x3C R/W - Receive FIFO Data Region
	volatile unsigned int	NOTDEFINE1[7];			// 0x24, 28, 2C, 30, 34, 38, 3C
	volatile unsigned int	MBOXCTR;				// 0x40 R/W 0x00015003 Mailbox Control Register
	volatile unsigned int	MBOXSTR;				// 0x44 R/W 0x81828383 Mailbox Status Register
}MAILBOX, *PMAILBOX;

/************************************************************************
* MISCELLANEOUS CONTROLLER Definition
************************************************************************/
//IOBC Register Map (Base Address = 0xF0050000)
//#define HwIOBC				0xF0050000
typedef struct _IOBC{
	volatile unsigned int	USB20D;					// 0x00 R/W 0x00000000 USB 2.0 Device Configuration Register
	volatile unsigned int	USB11H;					// 0x04 R/W 0x00000000 USB 1.1 Host Configuration Register
	volatile unsigned int	IOBAPB;					// 0x08 R/W 0x00000000 I/O Bus APB Configuration Register
	volatile unsigned int	STORAGE;				// 0x0C R/W 0x00000002 Storage Device Configuration Register
}IOBC, *PIOBC;

//SYSC Register Map (Base Address = 0xF3005000)
//#define HwSYSC				0xF3005000
typedef struct _SYSC{
	volatile unsigned int	REMAP;					// 0x00 R/W 0x00000003 Remap Configuration Register
	volatile unsigned int	VCFG0;					// 0x04 R/W 0x10008000 Video Core Configuration Register 0
	volatile unsigned int	ECFG0;					// 0x08 R/W - Exceptional Configuration Register 0
	volatile unsigned int	NOTDEFINE0;				// 0x0C
	volatile unsigned int	MPCFG;					// 0x10 R/W 0x00000000 Main Processor Configuration Register
	volatile unsigned int	NOTDEFINE1[3];			// 0x14, 18, 1C
	volatile unsigned int	BUSCFG;					// 0x20 R/W 0x00001F1F Main Bus Configuration Register
}SYSC, *PSYSC;

//VMT Register Map (Base Address = 0xF7000000)
//#define HwVMT					0xF7000000
typedef struct _VMT{
	volatile unsigned int	REGION0;				// 0x00 R/W - Configuration Register for Region 0
	volatile unsigned int	REGION1;				// 0x04 R/W - Configuration Register for Region 1
	volatile unsigned int	REGION2;				// 0x08 R/W - Configuration Register for Region 2
	volatile unsigned int	REGION3;				// 0x0C R/W - Configuration Register for Region 3
	volatile unsigned int	REGION4;				// 0x10 R/W - Configuration Register for Region 4
	volatile unsigned int	REGION5;				// 0x14 R/W - Configuration Register for Region 5
	volatile unsigned int	REGION6;				// 0x18 R/W - Configuration Register for Region 6
	volatile unsigned int	REGION7;				// 0x1C R/W - Configuration Register for Region 7
	//volatile unsigned int	TABBASE;				// 0x8000 R - MMU Table Base Address
}VMT, *PVMT;

#define	HwVMT_SZ(X)								(((X)-1)*Hw12)
#define	SIZE_4GB								32
#define	SIZE_2GB								31
#define	SIZE_1GB								30
#define	SIZE_512MB							29
#define	SIZE_256MB							28
#define	SIZE_128MB							27
#define	SIZE_64MB								26
#define	SIZE_32MB								25
#define	SIZE_16MB								24
#define	SIZE_8MB								23
#define	SIZE_4MB								22
#define	SIZE_2MB								21
#define	SIZE_1MB								20
#define	HwVMT_REGION_AP_ALL			(Hw11+Hw10)
#define	HwVMT_DOMAIN(X)					((X)*Hw5)
#define	HwVMT_REGION_EN					Hw9										// Region Enable Register
#define	HwVMT_CACHE_ON					Hw3										// Cacheable Register
#define	HwVMT_CACHE_OFF					HwZERO
#define	HwVMT_BUFF_ON						Hw2										// Bufferable Register
#define	HwVMT_BUFF_OFF						HwZERO

/************************************************************************
*	PORT Definition
************************************************************************/
//GPIO Register Map (Base Address = 0xF005A000)
//#define HwGPIO				0xF005A000
typedef struct _GPIO{
	volatile unsigned int	PORTCFG0;				// 0x000 R/W Port Configuration Register 0
	volatile unsigned int	PORTCFG1;				// 0x004 R/W Port Configuration Register 1
	volatile unsigned int	PORTCFG2;				// 0x008 R/W Port Configuration Register 2
	volatile unsigned int	PORTCFG3;				// 0x00C R/W Port Configuration Register 3
	volatile unsigned int	PORTCFG4;				// 0x010 R/W Port Configuration Register 4
	volatile unsigned int	PORTCFG5;				// 0x014 R/W Port Configuration Register 5
	volatile unsigned int	PORTCFG6;				// 0x018 R/W Port Configuration Register 6
	volatile unsigned int	PORTCFG7;				// 0x01C R/W Port Configuration Register 7
	volatile unsigned int	PORTCFG8;				// 0x020 R/W Port Configuration Register 8
	volatile unsigned int	PORTCFG9;				// 0x024 R/W Port Configuration Register 9
	volatile unsigned int	PORTCFG10;				// 0x028 R/W Port Configuration Register 10
	volatile unsigned int	PORTCFG11;				// 0x02C R/W Port Configuration Register 11
	volatile unsigned int	PORTCFG12;				// 0x030 R/W Port Configuration Register 12
	volatile unsigned int	PORTCFG13;				// 0x034 R/W Port Configuration Register 13
	volatile unsigned int	NOTDEFINE0;				// 0x038 -
	volatile unsigned int	NOTDEFINE1;				// 0x03C -
	volatile unsigned int	GPADAT;					// 0x040 R/W 0x00000000 GPA Data Register
	volatile unsigned int	GPAEN;					// 0x044 R/W 0x00000000 GPA Output Enable Register
	volatile unsigned int	GPASET;					// 0x048 W - OR function on GPA Output Data
	volatile unsigned int	GPACLR;					// 0x04C W - BIC function on GPA Output Data
	volatile unsigned int	GPAXOR;					// 0x050 W - XOR function on GPA Output Data
	volatile unsigned int	NOTDEFINE2;				// 0x054
	volatile unsigned int	NOTDEFINE3;				// 0x058
	volatile unsigned int	NOTDEFINE4;				// 0x05C
	volatile unsigned int	GPBDAT;					// 0x060 R/W 0x00000000 GPB Data Register
	volatile unsigned int	GPBEN;					// 0x064 R/W 0x00000000 GPB Output Enable Register
	volatile unsigned int	GPBSET;					// 0x068 W - OR function on GPB Output Data
	volatile unsigned int	GPBCLR;					// 0x06C W - BIC function on GPB Output Data
	volatile unsigned int	GPBXOR;					// 0x070 W - XOR function on GPB Output Data
	volatile unsigned int	NOTDEFINE5;				// 0x074
	volatile unsigned int	NOTDEFINE6;				// 0x078
	volatile unsigned int	NOTDEFINE7;				// 0x07C
	volatile unsigned int	GPCDAT;					// 0x080 R/W 0x00000000 GPC Data Register
	volatile unsigned int	GPCEN;					// 0x084 R/W 0x00000000 GPC Output Enable Register
	volatile unsigned int	GPCSET;					// 0x088 W - OR function on GPC Output Data
	volatile unsigned int	GPCCLR;					// 0x08C W - BIC function on GPC Output Data
	volatile unsigned int	GPCXOR;					// 0x090 W - XOR function on GPC Output Data
	volatile unsigned int	NOTDEFINE8;				// 0x094
	volatile unsigned int	NOTDEFINE9;				// 0x098
	volatile unsigned int	NOTDEFINE10;			// 0x09C
	volatile unsigned int	GPDDAT;					// 0x0A0 R/W 0x00000000 GPD Data Register
	volatile unsigned int	GPDEN;					// 0x0A4 R/W 0x00000000 GPD Output Enable Register
	volatile unsigned int	GPDSET;					// 0x0A8 W - OR function on GPD Output Data
	volatile unsigned int	GPDCLR;					// 0x0AC W - BIC function on GPD Output Data
	volatile unsigned int	GPDXOR;					// 0x0B0 W - XOR function on GPD Output Data
	volatile unsigned int	NOTDEFINE11;			// 0x0B4
	volatile unsigned int	NOTDEFINE12;			// 0x0B8
	volatile unsigned int	NOTDEFINE13;			// 0x0BC
	volatile unsigned int	GPEDAT;					// 0x0C0 R/W 0x00000000 GPE Data Register
	volatile unsigned int	GPEEN;					// 0x0C4 R/W 0x00000000 GPE Output Enable Register
	volatile unsigned int	GPESET;					// 0x0C8 W - OR function on GPE Output Data
	volatile unsigned int	GPECLR;					// 0x0CC W - BIC function on GPE Output Data
	volatile unsigned int	GPEXOR;					// 0x0D0 W - XOR function on GPE Output Data
	volatile unsigned int	NOTDEFINE14[3]; //	0x0D4,0x0D8,0x0DC
	volatile unsigned int	GPFDAT; 				// 0x0E0 R/W 0x00000000 GPF Data Register
	volatile unsigned int	GPFEN; 					//0x0E4 R/W 0x00000000 GPF Output Enable Register
	volatile unsigned int	GPFSET; 				//0x0E8 W - OR function on GPF Output Data
	volatile unsigned int	GPFCLR; 				//0x0EC W - BIC function on GPF Output Data
	volatile unsigned int	GPFXOR; 				//0x0F0 W - XOR function on GPF Output Data
	volatile unsigned int	NOTDEFINE15[3];	//RESERVED 0x0F4 0x0F8 0x0FC
	volatile unsigned int	CPUD0 ;					//0x100 R/W Pull-Up/Down Control Register 0
	volatile unsigned int	CPUD1;					// 0x104 R/W Pull-Up/Down Control Register 1
	volatile unsigned int	CPUD2 ;					//0x108 R/W Pull-Up/Down Control Register 2
	volatile unsigned int	CPUD3 ;					//0x10C R/W Pull-Up/Down Control Register 3
	volatile unsigned int	CPUD4;					// 0x110 R/W Pull-Up/Down Control Register 4
	volatile unsigned int	CPUD5;					// 0x114 R/W Pull-Up/Down Control Register 5
	volatile unsigned int	CPUD6;					// 0x118 R/W Pull-Up/Down Control Register 6
	volatile unsigned int	CPUD7;					// 0x11C R/W Pull-Up/Down Control Register 7
	volatile unsigned int	CPUD8;					// 0x120 R/W Pull-Up/Down Control Register 8
	volatile unsigned int	CPUD9 ;					//0x124 R/W Pull-Up/Down Control Register 9
	volatile unsigned int	CPDRV0;					// 0x128 R/W Driver strength Control Register 0
	volatile unsigned int	CPDRV1;					// 0x12C R/W
	volatile unsigned int	AINCFG;					// 0x130 R/W 0x00000000 Analog Input Pad Control Register
	volatile unsigned int	EINTSEL0;					// 0x134 R/W 0x00000000 External Interrupt Select Register 0
	volatile unsigned int	EINTSEL1;					// 0x138 R/W 0x00000000 External Interrupt Select Register 1
	volatile unsigned int	IRQSEL;					// 0x13C R/W 0x00000000 Interrupt Select Register
}GPIO, *PGPIO;


#endif //__TCC79xSTRUCTURES_H__
