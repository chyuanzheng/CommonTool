#ifndef __TCC78XWINCE_H__
#define __TCC78XWINCE_H__


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _REGISTERBITBCLKCTRSWRESETBCLKMASKE
{
	volatile unsigned int USB1_1_Host_Controller:1;
	volatile unsigned int USB2_0_Function_Controller:1;
	volatile unsigned int LCD_Controller:1;
	volatile unsigned int Camera_Interface_Controller:1;
	volatile unsigned int HDD_Controller:1;
	volatile unsigned int DMA_Controller:1;
	volatile unsigned int SD_MMC_Controller:1;
	volatile unsigned int Memory_Stick_Controller:1;
	volatile unsigned int I2C_Controller:1;
	volatile unsigned int NAND_Flash_Controller:1;
	volatile unsigned int Host_Interface_Controller:1;
	volatile unsigned int UART_Controller_Channel_0:1;
	volatile unsigned int UART_Controller_Channel_1:1;
	volatile unsigned int GSIO_Controller:1;
	volatile unsigned int DAI_Controller:1;
	volatile unsigned int GPSB_Channel_1:1;
	volatile unsigned int ECC_Controller:1;
	volatile unsigned int S_PDIF_Transmitter:1;
	volatile unsigned int GPSB_Channel_0:1;
	volatile unsigned int Sub_processor_peripherals:1;
	volatile unsigned int Graphic_2D:1;
	volatile unsigned int RTC:1;
	volatile unsigned int External_Memory_Controller:1;
	volatile unsigned int Sub_processor:1;
	volatile unsigned int ADC:1;
	volatile unsigned int Video_Controller_Hardware:1;
	volatile unsigned int Timer:1;
	volatile unsigned int Main_processor:1;
	volatile unsigned int Vectored_Interrupt_Controller:1;
	volatile unsigned int Memory_to_Memory_Scaler:1;
	volatile unsigned int Mailbox:1;
	volatile unsigned int Main_Bus_Components__should_be__1__:1;
} REGISTERBITBCLKCTRSWRESETBCLKMASKE;

typedef struct _REGISTERCKC // 0xF3000000
{
	volatile unsigned int CLKCTRL; // 0x00 R/W 0x800FF011 CPU & Bus Clock Control Register
	volatile unsigned int PLL0CFG; // 0x04 R/W 0x00015003 PLL0 Configuration Register
	volatile unsigned int PLL1CFG; // 0x08 R/W 0x00015003 PLL1 Configuration Register
	volatile unsigned int CLKDIVC; // 0x0C R/W 0x81828383 Divided Clock Configuration Register
	volatile unsigned int CLKDIVC1; // 0x10 R/W 0x00000000 PLL 0 Divider 1 Configuration Register
	volatile unsigned int MODECTR; // 0x14 R/W 0x00010000 Operating Mode Control Register
	
	REGISTERBITBCLKCTRSWRESETBCLKMASKE BCLKCTR; // 0x18 R/W 0xFFFFFFFF Bus Clock Mask Control Register
	REGISTERBITBCLKCTRSWRESETBCLKMASKE SWRESET; // 0x1C R/W 0x00800000 Software Reset Control Register
	
	volatile unsigned int PCK_USB11H; // 0x20 R/W 0x14000000 USB11H Clock Control Register
	volatile unsigned int PCK_SDMMC; // 0x24 R/W 0x14000000 SD/MMC Clock Control Register
	volatile unsigned int PCK_MSTICK; // 0x28 R/W 0x14000000 Memory Stick Clock Control Register
	volatile unsigned int PCK_I2C; // 0x2C R/W 0x14000000 I2C Clock Control Register
	volatile unsigned int PCK_LCD; // 0x30 R/W 0x14000000 LCD Clock Control Register
	volatile unsigned int PCK_CAM; // 0x34 R/W 0x14000000 Camera Clock Control Register
	volatile unsigned int PCK_UART0; // 0x38 R/W 0x14000000 UART0 Clock Control Register (UART2)
	volatile unsigned int PCK_UART1; // 0x3C R/W 0x14000000 UART1 Clock Control Register
	volatile unsigned int PCK_GSIO; // 0x40 R/W 0x14000000 GSIO Clock Control Register
	volatile unsigned int PCK_TCT; // 0x44 R/W 0x14000000 Timer T-Clock Control Register
	volatile unsigned int PCK_TCX; // 0x48 R/W 0x14000000 Clock Output for GPIO[2]
	volatile unsigned int PCK_TCZ; // 0x4C R/W 0x14000000 Clock Output for GPIO[3]
	volatile unsigned int PCK_ADC; // 0x50 R/W 0x14000000 ADC Clock Control Register
	volatile unsigned int PCK_DAI; // 0x54 R/W 0x0A000000 DAI Clock Control Register
	volatile unsigned int PCK_SPDTX; // 0x58 R/W 0x14000000 SPDIF TX Clock Control Register
	volatile unsigned int PCK_RFREQ; // 0x5C R/W 0x14000000 SDRAM Refresh Clock Control Reigster
	volatile unsigned int PCK_SPIS; // 0x60 R/W 0x14000000 SPI Slave Clock Control Register
	volatile unsigned int PCK_SCALER; // 0x64 R/W 0x14000000 CIF Scaler Clock Control Register
	
	volatile unsigned int UNDEFINED1[6]; // 68, 6c, 70, 74, 78, 7c, 
	
	volatile unsigned int BCKVCFG; // 0x80 R/W 0xFFFFFFFF Bus Clock(in video part) Control Register
	volatile unsigned int Reserved; // 0x84 R 0x00000000 Reserved
	volatile unsigned int MCLKCTRL; // 0x88 R/W 0x8000000F Main Processor Clock Control Register
	volatile unsigned int SCLKCTRL; // 0x8C R/W 0x8000000F Sub Processor Clock Control Register
	
	REGISTERBITBCLKCTRSWRESETBCLKMASKE BCLKMSKE; // 0x90 R/W 0xFFFFFFFF Bus Clock Mask Enable Register
	
	volatile unsigned int UNDEFINED2[26]; // 94, 98, 9c, ax*4, bx*4, cx*4, dx*4, ex*4, f0, f4, f8
	
	volatile unsigned int OPTION0; // 0xFC R/W 0x00000000 Option Register
} REGISTERCKC;


typedef struct _REGISTERSYSC // 0xF3005000
{
	volatile unsigned int REMAP; // 0x00 R/W 0x00000003 Remap Configuration Register
	volatile unsigned int VCFG0; // 0x04 R/W 0x10008000 Video Core Configuration Register 0
	volatile unsigned int ECFG0; // 0x8 R/W - Exceptional Configuration Register 0
	volatile unsigned int MPCFG; // 0x10 R/W 0x00000000 Main Processor Configuration Register
	volatile unsigned int BUSCFG; // 0x20 R/W 0x00001F1F Main Bus Configuration Register
} REGISTERSYSC;


typedef struct _REGISTERBITMBOXCTR
{
	volatile unsigned int ILEVEL:2; // 1 ~ 0  Received fifo level to generate interrupt RW
	// 00b : not-empty
	// /01b : greater equal to 2
	// /10b : greater equal to 4
	// 11b : full
	volatile unsigned int Reserved0:2;
	volatile unsigned int IEN:1; // 4 Received data interrupt enable RW
	volatile unsigned int OEN:1; // 5 Transmit data output enable RW
	volatile unsigned int FLUSH:1; // 6 Flush the transmit data fifo RW
	volatile unsigned int Reserved1:24;
	volatile unsigned int TEST:1; // 31 For Test Purpose -
} REGISTERBITMBOXCTR;

typedef struct _REGISTERBITMBOXSTR
{
	volatile unsigned int MEMP:1; // 0 Empty Status of Transmit FIFO R
	volatile unsigned int MFUL:1; // 1 Full Status of Transmit FIFO R
	volatile unsigned int Reserved0:2;
	volatile unsigned int MCOUNT:4; // 7 ~ 4 Stored data in Transmit FIFO ( 0 ~ 8, 0 is empty) R
	volatile unsigned int Reserved1:8;
	volatile unsigned int SEMP:1; // 16 Empty Status of Receive FIFO RW
	volatile unsigned int SFUL:1; // 17 - Full Status of Receive FIFO RW
	volatile unsigned int Reserved2:2;
	volatile unsigned int SCOUNT:4; // 23 ~ 20 - Filled Count of counter-part ( 0 ~ 8, 0 is empty) RW
} REGISTERBITMBOXSTR;

typedef struct _REGISTERMAILBOX // Base Address = 0xF4000000
{
	volatile unsigned int MBOXTXD[8];
	volatile unsigned int MBOXRXD[8];
	REGISTERBITMBOXCTR MBOXCTR;
	REGISTERBITMBOXSTR MBOXSTR;
} REGISTERMAILBOX;


typedef struct _REGISTERBITPRIORITYINTERRUPTCONTROLLER
{
	volatile unsigned int EI0:1; // 0x0 External interrupt 0 enable RW
	volatile unsigned int EI1:1; // 0x0 External interrupt 1 enable RW
	volatile unsigned int EI2:1; // 0x0 External interrupt 2 enable RW
	volatile unsigned int EI3:1; // 0x0 External interrupt 3 enable RW
	volatile unsigned int RTC:1; // 0x0 RTC interrupt enable RW
	volatile unsigned int GPSB0:1; // 0x0 GPSB Channel 0 Interrupt enable RW
	volatile unsigned int TC0:1; // 0x0 Timer 0 interrupt enable RW
	volatile unsigned int TC1:1; // 0x0 Timer 1 interrupt enable RW
	volatile unsigned int SCORE:1; // 0x0 Sub processor interrupt enable RW
	volatile unsigned int SPDTX:1; // 0x0 SPDIF transmitter interrupt enable RW
	volatile unsigned int VIDEO:1; // 0x0 Video hardware interrupt enable RW
	volatile unsigned int GSIO:1; // 0x0 GSIO interrupt enable RW
	volatile unsigned int SC:1; // 0x0 Mem-to-Mem scaler interrupt enable RW
	volatile unsigned int I2C:1; // 0x0 I2C interrupt enable RW
	volatile unsigned int DAIRX:1; // 0x0 DAI receive interrupt enable RW
	volatile unsigned int DAITX:1; // 0x0 DAI transmit interrupt enable RW
	volatile unsigned int CDRX:1; // 0x0 CDIF receive interrupt enable RW
	volatile unsigned int HPI:1; // 0x0 EHI interrupt enable RW
	volatile unsigned int UT0:1; // 0x0 UART channel 0 interrupt enable RW
	volatile unsigned int UT1:1; // 0x0 UART channel 1 interrupt enable RW
	volatile unsigned int UDMA:1; // 0x0 USB 2.0 DMA interrupt enable RW
	volatile unsigned int UD:1; // 0x0 USB 2.0 device interrupt enable RW
	volatile unsigned int UH:1; // 0x0 USB 1.1 host interrupt enable RW
	volatile unsigned int DMA:1; // 0x0 DMA controller interrupt enable RW
	volatile unsigned int HDD:1; // 0x0 HDD controller interrupt enable RW
	volatile unsigned int MS:1; // 0x0 Memory stick interrupt enable RW
	volatile unsigned int NFC:1; // 0x0 Nand flash controller interrupt enable RW
	volatile unsigned int SD:1; // 0x0 SD/MMC interrupt enable RW
	volatile unsigned int CAM:1; // 0x0 Camera interrupt enable RW
	volatile unsigned int LCD:1; // 0x0 LCD controller interrupt enable RW
	volatile unsigned int ADC:1; // 0x0 ADC interrupt enable RW
	volatile unsigned int GPSB1:1; // 0x0 GPSB Channel 1 Interrupt enable RW
} REGISTERBITPRIORITYINTERRUPTCONTROLLER;

typedef struct _REGISTERPRIORITYINTERRUPTCONTROLLER // 0xF3001000
{
	REGISTERBITPRIORITYINTERRUPTCONTROLLER IEN; // Enable Interrupt
	REGISTERBITPRIORITYINTERRUPTCONTROLLER CLR; // Clear Interrupt
	REGISTERBITPRIORITYINTERRUPTCONTROLLER STS; // Interrupt Status
	REGISTERBITPRIORITYINTERRUPTCONTROLLER SEL; // IRQ/FIQ selection
	REGISTERBITPRIORITYINTERRUPTCONTROLLER SRC; // Test interrupt selection
	REGISTERBITPRIORITYINTERRUPTCONTROLLER MSTS; // Masked Interrupt Status
	REGISTERBITPRIORITYINTERRUPTCONTROLLER TIG; // Test interrupt request
	REGISTERBITPRIORITYINTERRUPTCONTROLLER POL; // Polarity of interrupt signal (0 = active high, 1 = active low)
	REGISTERBITPRIORITYINTERRUPTCONTROLLER IRQ; // IRQ interrupt status
	REGISTERBITPRIORITYINTERRUPTCONTROLLER FIQ; // FIQ interrupt status
	REGISTERBITPRIORITYINTERRUPTCONTROLLER MIRQ; // Masked IRQ interrupt status
	REGISTERBITPRIORITYINTERRUPTCONTROLLER MFIQ; // Masked FIQ interrupt status
	REGISTERBITPRIORITYINTERRUPTCONTROLLER MODE; // Trigger mode selection (0 = edge, 1 = level)
	REGISTERBITPRIORITYINTERRUPTCONTROLLER SYNC; // Enable Synchronizing
	REGISTERBITPRIORITYINTERRUPTCONTROLLER WKEN; // Select Wakeup signal
	REGISTERBITPRIORITYINTERRUPTCONTROLLER MODEA; // Edge trigger mode selection (0 = single edge, 1 = both edge)
	REGISTERBITPRIORITYINTERRUPTCONTROLLER INTMSK; // IRQ Output Masking Register
	struct ALLMSK // All Mask Register
	{
		volatile unsigned int IRQ:1; // 0x0 IRQ mask register RW
		volatile unsigned int FIQ:1; // 0x0 FIQ mask register RW
		// 31 ~ 2 - - Undefined -
	};
} REGISTERPRIORITYINTERRUPTCONTROLLER;


typedef struct _REGISTERGPSB // 0xF0057400, 0xF0057800
{
	volatile unsigned int PORT; // 0x00 R/W 0x0000 Data port
	volatile unsigned int STAT; // 0x04 R/W 0x0000 Status register
	volatile unsigned int INTEN; // 0x08 R/W 0x0000 Interrupt enable
	volatile unsigned int MODE; // 0x0C R/W 0x0000 Mode register
	volatile unsigned int CTRL; // 0x10 R/W 0x0000 Control register

	volatile unsigned int UNDEFINED1[3]; // 14, 18, 1c,
	
	volatile unsigned int TXBASE; // 0x20 R/W 0x0000 TX base address register
	volatile unsigned int RXBASE; // 0x24 R/W 0x0000 RX base address register
	volatile unsigned int PACKET; // 0x28 R/W 0x0000 Packet register
	volatile unsigned int DMACTR; // 0x2C R/W 0x0000 DMA control register
	volatile unsigned int DMASTR; // 0x30 R/W 0x0000 DMA status register
} REGISTERGPSB;


typedef struct _REGISTERGPIO // 0xF005A000
{
	volatile unsigned int PORTCFG0; // 0x00 R/W Port Configuration Register 0
	volatile unsigned int PORTCFG1; // 0x04 R/W Port Configuration Register 1
	volatile unsigned int PORTCFG2; // 0x08 R/W Port Configuration Register 2
	volatile unsigned int PORTCFG3; // 0x0C R/W Port Configuration Register 3

	volatile unsigned int UNDEFINED1[4]; // 10, 14, 18, 1c,
	
	volatile unsigned int GPADAT; // 0x20 R/W 0x00000000 GPA Data Register
	volatile unsigned int GPAEN; // 0x24 R/W 0x00000000 GPA Output Enable Register
	volatile unsigned int GPASET; // 0x28 W - OR function on GPA Output Data
	volatile unsigned int GPACLR; // 0x2C W - BIC function on GPA Output Data
	volatile unsigned int GPAXOR; // 0x30 W - XOR function on GPA Output Data

	volatile unsigned int UNDEFINED2[3]; // 34, 38, 3c,
	
	volatile unsigned int GPBDAT; // 0x40 R/W 0x00000000 GPB Data Register
	volatile unsigned int GPBEN; // 0x44 R/W 0x00000000 GPB Output Enable Register
	volatile unsigned int GPBSET; // 0x48 W - OR function on GPB Output Data
	volatile unsigned int GPBCLR; // 0x4C W - BIC function on GPB Output Data
	volatile unsigned int GPBXOR; // 0x50 W - XOR function on GPB Output Data

	volatile unsigned int UNDEFINED3[3]; // 54, 58, 5c,
	
	volatile unsigned int GPCDAT; // 0x60 R/W 0x00000000 GPC Data Register
	volatile unsigned int GPCEN; // 0x64 R/W 0x00000000 GPC Output Enable Register
	volatile unsigned int GPCSET; // 0x68 W - OR function on GPC Output Data
	volatile unsigned int GPCCLR; // 0x6C W - BIC function on GPC Output Data
	volatile unsigned int GPCXOR; // 0x70 W - XOR function on GPC Output Data

	volatile unsigned int UNDEFINED4[3]; // 74, 78, 7c,
	
	volatile unsigned int GPDDAT; // 0x80 R/W 0x00000000 GPD Data Register
	volatile unsigned int GPDEN; // 0x84 R/W 0x00000000 GPD Output Enable Register
	volatile unsigned int GPDSET; // 0x88 W - OR function on GPD Output Data
	volatile unsigned int GPDCLR; // 0x8C W - BIC function on GPD Output Data
	volatile unsigned int GPDXOR; // 0x90 W - XOR function on GPD Output Data

	volatile unsigned int UNDEFINED5[3]; // 94, 98, 9c,
	
	volatile unsigned int GPEDAT; // 0xA0 R/W 0x00000000 GPE Data Register
	volatile unsigned int GPEEN; // 0xA4 R/W 0x00000000 GPE Output Enable Register
	volatile unsigned int GPESET; // 0xA8 W - OR function on GPE Output Data
	volatile unsigned int GPECLR; // 0xAC W - BIC function on GPE Output Data
	volatile unsigned int GPEXOR; // 0xB0 W - XOR function on GPE Output Data

	volatile unsigned int UNDEFINED6[3]; // b4, b8, bc,
		
	volatile unsigned int CPUD0; // 0xC0 R/W Pull-Up/Down Control Register 0
	volatile unsigned int CPUD1; // 0xC4 R/W Pull-Up/Down Control Register 1
	volatile unsigned int CPUD2; // 0xC8 R/W Pull-Up/Down Control Register 2
	volatile unsigned int CPUD3; // 0xCC R/W Pull-Up/Down Control Register 3
	volatile unsigned int CPUD4; // 0xD0 R/W Pull-Up/Down Control Register 4
	volatile unsigned int CPUD5; // 0xD4 R/W Pull-Up/Down Control Register 5
	volatile unsigned int CPUD6; // 0xD8 R/W Pull-Up/Down Control Register 6

	volatile unsigned int UNDEFINED7[1]; // dc,
	
	volatile unsigned int EINTSEL; // 0xE0 R/W 0x03020100 External Interrupt Select Register
} REGISTERGPIO;


typedef struct _REGISTERGSIO // 0xF0057000
{
	volatile unsigned int GSDO0; // 0x00 R/W Unknown GSIO0 Output Data Register
	volatile unsigned int GSDI0; // 0x04 R/W Unknown GSIO0 Input Data Register
	volatile unsigned int GSCR0; // 0x08 R/W 0x0000 GSIO0 Control Register
	volatile unsigned int GSGCR; // 0x0C R/W 0x0000 GSIO Global Control Register
	volatile unsigned int GSDO1; // 0x10 R/W Unknown GSIO1 Output Data Register
	volatile unsigned int GSDI1; // 0x14 R/W Unknown GSIO1 Input Data Register
	volatile unsigned int GSCR1; // 0x18 R/W 0x0000 GSIO1 Control Register
} REGISTERGSIO;


typedef struct _REGISTERI2CCONTROLLER // 0xF0052000
{
	volatile unsigned int PRES0; // 0x00 R/W 0xFFFF Clock Prescale register Master 0
	volatile unsigned int CTRL0; // 0x04 R/W 0x0000 Control Register
	volatile unsigned int TXR0; // 0x08 W 0x0000 Transmit Register
	volatile unsigned int CMD0; // 0x0C W 0x0000 Command Register
	volatile unsigned int RXR0; // 0x10 R 0x0000 Receive Register
	volatile unsigned int SR0; // 0x14 R 0x0000 Status Register
	volatile unsigned int TIME0; // 0x18 R/W 0x0000 Timing Control Register Master 1

	volatile unsigned int UNDEFINED1[9]; // 1c, 20, 24, 28, 2c, 30, 34, 38, 3c,
	
	volatile unsigned int PRES1; // 0x40 R/W 0xFFFF Clock Prescale register
	volatile unsigned int CTRL1; // 0x44 R/W 0x0000 Control Register
	volatile unsigned int TXR1; // 0x48 W 0x0000 Transmit Register
	volatile unsigned int CMD1; // 0x4C W 0x0000 Command Register
	volatile unsigned int RXR1; // 0x50 R 0x0000 Receive Register
	volatile unsigned int SR1; // 0x54 R 0x0000 Status Register
	volatile unsigned int TIME1; // 0x58 R/W 0x0000 Timing Control Register Slave

	volatile unsigned int UNDEFINED2[9]; // 5c, 60, 64, 68, 6c, 70, 74, 78, 7c,
	
	volatile unsigned int PORT; // 0x80 R/W - Data Access port (TX/RX FIFO)
	volatile unsigned int CTL; // 0x84 R/W 0x00000000 Control register
	volatile unsigned int ADDR; // 0x88 W 0x00000000 Address register
	volatile unsigned int INT; // 0x8C W 0x00000000 Interrupt Enable Register
	volatile unsigned int STAT; // 0x90 R 0x00000000 Status Register

	volatile unsigned int UNDEFINED3[2]; // 94, 98, 

	volatile unsigned int MBF; // 0x9C R/W 0x00000000 Buffer Valid Flag
	volatile unsigned int MB0; // 0xA0 R/W 0x00000000 Data Buffer 0 (Byte 3 ~ 0)
	volatile unsigned int MB1; // 0xA4 R/W 0x00000000 Data Buffer 1 (Byte 7 ~ 4)

	volatile unsigned int UNDEFINED4[6]; // a8, ac, b0, b4, b8, bc, 

	volatile unsigned int IRQSTR; // 0xC0 R 0x00000000 IRQ Status Register Status
} REGISTERI2CCONTROLLER;


#define BITSET(X, MASK)				( (X) |= (UINT)(MASK) )
#define	BITSCLR(X, SMASK, CMASK)	( (X) = ((((UINT)(X)) | ((UINT)(SMASK))) & ~((UINT)(CMASK))) )
#define	BITCSET(X, CMASK, SMASK)	( (X) = ((((UINT)(X)) & ~((UINT)(CMASK))) | ((UINT)(SMASK))) )
#define	BITCLR(X, MASK)				( (X) &= ~((UINT)(MASK)) )
#define	BITXOR(X, MASK)				( (X) ^= (UINT)(MASK) )


#ifdef __cplusplus
}
#endif

#endif//__TCC78XWINCE_H__

