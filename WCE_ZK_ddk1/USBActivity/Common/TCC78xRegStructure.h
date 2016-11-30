#ifndef __TCC78xCKCReg__
#define __TCC78xCKCReg__

typedef struct __TCC78xCKC{

	unsigned int CLKCTRL;			//0x00		R/W 	0x800FF011 CPU & Bus Clock Control Register
	unsigned int PLL0CFG;			//0x04		R/W 	0x00015003 PLL0 Configuration Register
	unsigned int PLL1CFG;			//0x08		R/W 	0x00015003 PLL1 Configuration Register
	unsigned int CLKDIVC;			//0x0C		R/W 	0x81828383 Divided Clock Configuration Register
	unsigned int CLKDIVC1;		//0x10		R/W 	0x00000000 PLL 0 Divider 1 Configuration Register
	unsigned int MODECTR;			//0x14		R/W 	0x00010000 Operating Mode Control Register
	unsigned int BCLKCTR;			//0x18		R/W 	0xFFFFFFFF Bus Clock Mask Control Register
	unsigned int SWRESET;			//0x1C		R/W 	0x00800000 Software Reset Control Register
	unsigned int PCK_USB11H;	//0x20		R/W 	0x14000000 USB11H Clock Control Register
	unsigned int PCK_SDMMC;		//0x24		R/W 	0x14000000 SD/MMC Clock Control Register
	unsigned int PCK_MSTICK;	//0x28		R/W 	0x14000000 Memory Stick Clock Control Register
	unsigned int PCK_I2C;			//0x2C		R/W 	0x14000000 I2C Clock Control Register
	unsigned int PCK_LCD;			//0x30		R/W 	0x14000000 LCD Clock Control Register
	unsigned int PCK_CAM;			//0x34		R/W 	0x14000000 Camera Clock Control Register
	unsigned int PCK_UART0;		//0x38		R/W 	0x14000000 UART0 Clock Control Register (UART2)
	unsigned int PCK_UART1;		//0x3C		R/W 	0x14000000 UART1 Clock Control Register
	unsigned int PCK_GSIO;		//0x40		R/W 	0x14000000 GSIO Clock Control Register
	unsigned int PCK_TCT;			//0x44		R/W 	0x14000000 Timer T-Clock Control Register
	unsigned int PCK_TCX;			//0x48		R/W 	0x14000000 Clock Output for GPIO[2]
	unsigned int PCK_TCZ;			//0x4C		R/W 	0x14000000 Clock Output for GPIO[3]
	unsigned int PCK_ADC;			//0x50		R/W 	0x14000000 ADC Clock Control Register
	unsigned int PCK_DAI;			//0x54		R/W 	0x0A000000 DAI Clock Control Register
	unsigned int PCK_SPDTX;		//0x58		R/W 	0x14000000 SPDIF TX Clock Control Register
	unsigned int PCK_RFREQ;		//0x5C		R/W 	0x14000000 SDRAM Refresh Clock Control Reigster
	unsigned int PCK_SPIS;		//0x60		R/W 	0x14000000 SPI Slave Clock Control Register
	unsigned int PCK_SCALER;	//0x64		R/W 	0x14000000 CIF Scaler Clock Control Register
	unsigned int CKC_NOTUSED0;	//0x68
	unsigned int CKC_NOTUSED1;	//0x70
	unsigned int CKC_NOTUSED2;	//0x74
	unsigned int CKC_NOTUSED3;	//0x78
	unsigned int CKC_NOTUSED4;	//0x7C
	unsigned int BCKVCFG;			//0x80		R/W 	0xFFFFFFFF Bus Clock(in video part) Control Register
	unsigned int Reserved;		//0x84		R 		0x00000000 Reserved
	unsigned int MCLKCTRL;		//0x88		R/W 	0x8000000F Main Processor Clock Control Register
	unsigned int SCLKCTRL;		//0x8C		R/W 	0x8000000F Sub Processor Clock Control Register
	unsigned int BCLKMSKE;		//0x90		R/W 	0xFFFFFFFF Bus Clock Mask Enable Register
	unsigned int OPTION0;			//0xFC		R/W 	0x00000000 Option Registe

}TCC78xCKCReg;

#endif //__TCC78xCKCReg__