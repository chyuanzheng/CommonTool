/****************************************************************************
 *   FileName    : TCC78xPhysical.h
 *   Description : TCC78x REGISTER DEFINE FUNCTION
 ****************************************************************************
 *
 *   TCC Version 1.0
 *   Copyright (c) Telechips, Inc.
 *   ALL RIGHTS RESERVED
 *
 *  HISTORY OF MODIFIED
 *	2006 MAR. 15 Created BY JY.JANG
 *
 ****************************************************************************/

/************************************************************************
*	TCC78x Internal Register Definition File
************************************************************************/
#ifndef	__TCC78x_H__
#define	__TCC78x_H__

#define TCC_FONTFILE_NAME	"780FONT_.TCC"
#define TCC_DMBDBFILE_NAME	"780DMBDB.TCC"

enum {
	IRQ_EI0,
	IRQ_EI1,
	IRQ_EI2,
	IRQ_EI3,
	IRQ_RTC,
	IRQ_GPSB,
	IRQ_TC0,	
	IRQ_TC1,
	IRQ_SCORE,
	IRQ_SPDTX,
	IRQ_VIDEO,
	IRQ_GSIO,
	IRQ_SC,
	IRQ_I2C,
	IRQ_DAIRX,
	IRQ_DAITX,
	IRQ_CDRX,
	IRQ_HPI,
	IRQ_UT0,
	IRQ_UT1,
	IRQ_UDMA,
	IRQ_UD,
	IRQ_UH,
	IRQ_DMA,
	IRQ_HDD,
	IRQ_MS,
	IRQ_NFC,
	IRQ_SD,
	IRQ_CAM,
	IRQ_LCD,
	IRQ_ADC,
	IRQ_ECC
};

/************************************************************************
*	Bit Field Definition
************************************************************************/
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

#define	HwVERSION								*(volatile unsigned long *)0xE0001FFC

/************************************************************************
*	LCD INTERFACE Register Define				(Base Addr = 0xF0000000)
************************************************************************/
#define	HwLCTRL									*(volatile unsigned long *)0xF0000000	// W, LCD Control Register
#define	HwLCTRL_Y2R2_EN							Hw31									// YUV to RGB Channel Converter Enable 2
#define	HwLCTRL_AEN2_EN							Hw30									// Alpha Blend Enable 2
#define	HwLCTRL_CEN2_EN							Hw29									// Chroma Key Enable 2
#define	HwLCTRL_Y2R1_EN							Hw28									// YUV to RGB Channel Converter Enable 1
#define	HwLCTRL_AEN1_EN							Hw27									// Alpha Blend Enable 1
#define	HwLCTRL_CEN1_EN							Hw26									// Chroma Key Enable 1
#define	HwLCTRL_Y2R0_EN							Hw25									// YUV to RGB Channel Converter Enable 0
#define	HwLCTRL_656_EN							Hw24									// CCIR 601 to 656 Enable
#define	HwLCTRL_BPP_1							HwZERO									// Bit Per Pixel = 1bbp
#define	HwLCTRL_BPP_2							Hw20									// Bit Per Pixel = 2bbp 
#define	HwLCTRL_BPP_4							Hw21									// Bit Per Pixel = 4bbp
#define	HwLCTRL_BPP_332							(Hw21+Hw20)								// Bit Per Pixel = 332bbp
#define	HwLCTRL_BPP_444							Hw22									// Bit Per Pixel = 444bbp
#define	HwLCTRL_BPP_565							(Hw22+Hw20)								// Bit Per Pixel = 565bbp
#define	HwLCTRL_BPP_555							(Hw22+Hw21)								// Bit Per Pixel = 555bbp
#define	HwLCTRL_BPP_888							(Hw22+Hw21+Hw20)						// Bit Per Pixel = 888bbp
#define	HwLCTRL_PXDW_4							HwZERO									// Pixel Data Width = 4pxdw
#define	HwLCTRL_PXDW_8							Hw16									// Pixel Data Width = 8pxdw
#define	HwLCTRL_PXDW_888						Hw17									// Pixel Data Width = 888pxdw
#define	HwLCTRL_PXDW_565						(Hw17+Hw16)								// Pixel Data Width = 565pxdw
#define	HwLCTRL_PXDW_555						Hw18									// Pixel Data Width = 555pxdw
#define	HwLCTRL_PXDW_18							(Hw18+Hw16)								// Pixel Data Width = 18pxdw
#define	HwLCTRL_PXDW_8UY						(Hw18+Hw17)								// Pixel Data Width = 8pxdw(UY)
#define	HwLCTRL_PXDW_8VY						(Hw18+Hw17+Hw16)						// Pixel Data Width = 8pxdw(VY)
#define	HwLCTRL_PXDW_16YU						Hw19									// Pixel Data Width = 16pxdw(YU)
#define	HwLCTRL_PXDW_16YV						(Hw19+Hw16)								// Pixel Data Width = 16pxdw(YV)
#define	HwLCTRL_ID_INVERTED						Hw15									// Inverted ACBIAS
#define HwLCTRL_IV_INVERTED						Hw14									// Inverted Vertical Sync
#define	HwLCTRL_IH_INVERTED						Hw13									// Inverted Horizontal Sync
#define	HwLCTRL_IP_FEDGE						Hw12									// Data is driven onto the LCD's data pins on the falling edge of pixel clock pin
#define HwLCTRL_R2Y_EN							Hw10									// RGB to YUV Channel Converter Enable
#define HwLCTRL_DP_2							Hw9										// One pixel data per 2 PXCLK cycle is output
#define	HwLCTRL_NI_PMODE						Hw8										// Non-interlace Mode (Progressive Mode)
#define	HwLCTRL_TV								Hw7										// TV Mode. In this mode, all values of LVTIMEn registers are divided by 2
#define	HwLCTRL_TFT								Hw6										// TFT-LCD Mode
#define	HwLCTRL_STN								Hw5										// STN-LCD Mode
#define	HwLCTRL_MSEL							Hw4										// Master Select
#define	HwLCTRL_IEN2_EN							Hw3										// Fetch Enable 2
#define	HwLCTRL_IEN1_EN							Hw2										// Fetch Enable 1
#define HwLCTRL_IEN0_EN							Hw1										// Fetch Enable 0
#define HwLCTRL_LEN_EN							Hw0										// LCD Controller Enable
                                        	
#define	HwLBC									*(volatile unsigned long *)0xF0000004	// W, LCD Background Color Register
                                        	
#define	HwLCLKDIV								*(volatile unsigned long *)0xF0000008	// W, LCD Clock Divider Register
#define	HwLCLKDIV_CS							Hw31									// Clock source
                                        	
#define	HwLHTIME1								*(volatile unsigned long *)0xF000000C	// W, LCD Horizontal Timing Register 1
                                        	
#define	HwLHTIME2								*(volatile unsigned long *)0xF0000010	// W, LCD Horizontal Timing Register 2
                                        	
#define	HwLVTIME1								*(volatile unsigned long *)0xF0000014	// W, LCD Vertical Timing Register 1
                                        	
#define	HwLVTIME2								*(volatile unsigned long *)0xF0000018	// W, LCD Vertical Timing Register 2
                                        	
#define	HwLVTIME3								*(volatile unsigned long *)0xF000001C	// W, LCD Vertical Timing Register 3
                                        	
#define	HwLVTIME4								*(volatile unsigned long *)0xF0000020	// W, LCD Vertical Timing Register 4
                                        	
#define	HwLLUTR									*(volatile unsigned long *)0xF0000024	// W, LCD Lookup Register for Red
                                        	
#define	HwLLUTG									*(volatile unsigned long *)0xF0000028	// W, LCD Lookup Register for Green
                                        	
#define	HwLLUTB									*(volatile unsigned long *)0xF000002C	// W, LCD Lookup Register for Blue
                                        	
#define	HwLDP7L									*(volatile unsigned long *)0xF0000030	// W, LCD Modulo 7 Dithering Pattern (Low)
                                        	
#define	HwLDP7H									*(volatile unsigned long *)0xF0000034	// W, LCD Modulo 7 Dithering Pattern (High)
                                        	
#define	HwLDP5									*(volatile unsigned long *)0xF0000038	// W, LCD Modulo 5 Dithering Pattern Register
                                        	
#define	HwLDP4									*(volatile unsigned long *)0xF000003C	// W, LCD Modulo 4 Dithering Pattern Register
                                        	
#define	HwLDP3									*(volatile unsigned long *)0xF0000040	// W, LCD 3-bit Dithering Pattern Register
                                        	
#define	HwLCP1									*(volatile unsigned long *)0xF0000044	// W, LCD Clipping Register 1
                                        	
#define	HwLCP2									*(volatile unsigned long *)0xF0000048	// W, LCD Clipping Register 2
                                        	
#define	HwLK1									*(volatile unsigned long *)0xF000004C	// W, LCD Keying Register 1
#define	HwLK1_A10_MAX							(Hw25+Hw24)								//
                                        	
#define	HwLK2									*(volatile unsigned long *)0xF0000050	// W, LCD Keying Register 2
#define	HwLK2_A20_MAX							(Hw25+Hw24)								//
                                        	
#define	HwLKM1									*(volatile unsigned long *)0xF0000054	// W, LCD Keying Mask Register 1
#define	HwLKM1_A11_MAX							(Hw25+Hw24)								//
                                        	
#define	HwLKM2									*(volatile unsigned long *)0xF0000058	// W, LCD Keying Mask Register 2
#define	HwLKM2_A21_MAX							(Hw25+Hw24)								//
                                        	
#define	HwLDS									*(volatile unsigned long *)0xF000005C	// W, LCD Display Size Register
                                        	
#define	HwLSTATUS								*(volatile unsigned long *)0xF0000060	// R/Clr, LCD Status Register
#define	HwLSTATUS_VS							Hw15									// Monitoring vertical sync.
#define HwLSTATUS_ITY							Hw12									// Interrupt Type
#define	HwLSTATUS_ICR							Hw8										// Interrupt Clear, using ITY is level type
#define	HwLSTATUS_BY							Hw6										// Busy signal
#define HwLSTATUS_EF							Hw5										// Even-Field(Read Only). 0:Odd field or frame, 1:Even field or frame
#define HwLSTATUS_DD							Hw4										// Disable Done(Read/Clear). If LEN is disabled, DD will be 1 after current frame has been displayed. As MDD of LIM register is cleared, it can be LCD interrupt source
#define HwLSTATUS_RU							Hw3										// Register Update(Read/Clear). It indicates that all registers programmed are applied to current frame data. As MRU of LIM register is cleared, it can be LCD interrupt source
#define HwLSTATUS_FU							Hw0										// FIFO underrun(Read/Clear). It indicates that FIFO underrun has been occurred. In this case, LCLK frequency must be lower. As MFU of LIM register is cleared, it can be LCD interrupt source
                                        	
#define	HwLIM									*(volatile unsigned long *)0xF0000064	// W, LCD Interrupt Register
#define HwLIM_MDD								Hw4										// Masking disable done interrupt
#define HwLIM_MRU								Hw3										// Masking register update interrupt
#define HwLIM_MFU								Hw0										// Masking FIFO underrun interrupt
                                        	
#define	HwLI0C									*(volatile unsigned long *)0xF0000068	// W, LCD Image 0 Control Register
#define	HwLIOC_IMG012							HwZERO									//
#define	HwLIOC_IMG021							Hw12									//
#define	HwLIOC_IMG102							Hw13									//
#define	HwLIOC_IMG201							(Hw13+Hw12)								//
#define	HwLIOC_IMG120							Hw14									//
#define	HwLIOC_IMG210							(Hw14+Hw12)								//
#define HwLI0C_BR_BE							Hw7										// Big Endian pixel data
#define HwLI0C_YUV_420							Hw4										// YUV 4:2:0
#define HwLI0C_YUV_422							(Hw5+Hw4)								// YUV 4:2:2
#define HwLI0C_YUV_422P							(Hw6+Hw5+Hw4)							// YUV 4:2:2 Patch
#define HwLI0C_BPP_1							HwZERO									// Bit Per Pixel = 1bpp
#define HwLI0C_BPP_2							Hw0										// Bit Per Pixel = 2bpp
#define HwLI0C_BPP_4							Hw1										// Bit Per Pixel = 4bpp
#define HwLI0C_BPP_332							(Hw1+Hw0)								// Bit Per Pixel = 332bpp
#define HwLI0C_BPP_444							Hw2										// Bit Per Pixel = 444bpp
#define HwLI0C_BPP_565							(Hw2+Hw0)								// Bit Per Pixel = 565bpp
#define HwLI0C_BPP_555							(Hw2+Hw1)								// Bit Per Pixel = 555bpp
#define HwLI0C_BPP_888							(Hw2+Hw1+Hw0)							// Bit Per Pixel = 888bpp
                                        	
#define HwLI0P									*(volatile unsigned long *)0xF000006C	// W, LCD Image 0 Position Register
	                                    	
#define	HwLI0S									*(volatile unsigned long *)0xF0000070	// W, LCD Image 0 Size Register
                                        	
#define	HwLI0BA0								*(volatile unsigned long *)0xF0000074	// W, LCD Image 0 Base Address 0 Register
                                        	
#define	HwLI0CA									*(volatile unsigned long *)0xF0000078	// W, LCD Image 0 Current Address Register
                                        	
#define	HwLI0BA1								*(volatile unsigned long *)0xF000007C	// W, LCD Image 0 Base Address 1 Register
                                        	
#define HwLI0BA2								*(volatile unsigned long *)0xF0000080	// W, LCD Image 0 Base Address 2 Register
                                        	
#define	HwLI0O									*(volatile unsigned long *)0xF0000084	// W, LCD Image 0 Offset Register
                                        	
#define HwLI0SCALE								*(volatile unsigned long *)0xF0000088	// W, LCD Image 0 Scale Ratio
#define	HwLI0SCALE_Y_NS							HwZERO									// Non-Scalable
#define	HwLI0SCALE_Y_D2							Hw4										// DownScale by 2
#define	HwLI0SCALE_Y_D3							Hw5										// DownScale by 3
#define HwLI0SCALE_Y_D4							(Hw5+Hw4)								// DownScale by 4
#define	HwLI0SCALE_Y_D8							(Hw6+Hw5+Hw4)							// DownScale by 8
#define	HwLI0SCALE_Y_U2							(Hw7+Hw4)								// UpScale by 2
#define	HwLI0SCALE_Y_U3							(Hw7+Hw5)								// UpScale by 3
#define	HwLI0SCALE_Y_U4							(Hw7+Hw5+Hw4)							// UpScale by 4
#define	HwLI0SCALE_Y_U8							(Hw7+Hw6+Hw5+Hw4)						// UpScale by 8
#define	HwLI0SCALE_X_NS							HwZERO									// Non-Scalable
#define	HwLI0SCALE_X_D2							Hw0										// DownScale by 2
#define	HwLI0SCALE_X_D3							Hw1										// DownScale by 3
#define HwLI0SCALE_X_D4							(Hw1+Hw0)								// DownScale by 4
#define	HwLI0SCALE_X_D8							(Hw2+Hw1+Hw0)							// DownScale by 8
#define	HwLI0SCALE_X_U2							(Hw3+Hw0)								// UpScale by 2
#define	HwLI0SCALE_X_U3							(Hw3+Hw1)								// UpScale by 3
#define	HwLI0SCALE_X_U4							(Hw3+Hw1+Hw0)							// UpScale by 4
#define	HwLI0SCALE_X_U8							(Hw3+Hw2+Hw1+Hw0)						// UpScale by 8
                                        	
#define	HwLI1C									*(volatile unsigned long *)0xF000008C	// W, LCD Image 1 Control Register
#define HwLI1C_BR_BE							Hw7										// Big Endian pixel data
#define HwLI1C_YUV_420							Hw4										// YUV 4:2:0
#define HwLI1C_YUV_422							(Hw5+Hw4)								// YUV 4:2:2
#define HwLI1C_YUV_422P							(Hw6+Hw5+Hw4)							// YUV 4:2:2 Patch
#define HwLI1C_BPP_1							HwZERO									// Bit Per Pixel = 1bpp
#define HwLI1C_BPP_2							Hw0										// Bit Per Pixel = 2bpp
#define HwLI1C_BPP_4							Hw1										// Bit Per Pixel = 4bpp
#define HwLI1C_BPP_332							(Hw1+Hw0)								// Bit Per Pixel = 332bpp
#define HwLI1C_BPP_444							Hw2										// Bit Per Pixel = 444bpp
#define HwLI1C_BPP_565							(Hw2+Hw0)								// Bit Per Pixel = 565bpp
#define HwLI1C_BPP_555							(Hw2+Hw1)								// Bit Per Pixel = 555bpp
#define HwLI1C_BPP_888							(Hw2+Hw1+Hw0)							// Bit Per Pixel = 888bpp
                                        	
#define HwLI1P									*(volatile unsigned long *)0xF0000090	// W, LCD Image 1 Position Register
                                        	
#define	HwLI1S									*(volatile unsigned long *)0xF0000094	// W, LCD Image 1 Size Register
                                        	
#define	HwLI1BA0								*(volatile unsigned long *)0xF0000098	// W, LCD Image 1 Base Address 0 Register
                                        	
#define	HwLI1CA									*(volatile unsigned long *)0xF000009C	// W, LCD Image 1 Current Address Register
                                        	
#define	HwLI1BA1								*(volatile unsigned long *)0xF00000A0	// W, LCD Image 1 Base Address 1 Register
                                        	
#define HwLI1BA2								*(volatile unsigned long *)0xF00000A4	// W, LCD Image 1 Base Address 2 Register
                                        	
#define	HwLI1O									*(volatile unsigned long *)0xF00000A8	// W, LCD Image 1 Offset Register
                                        	
#define HwLI1SCALE								*(volatile unsigned long *)0xF00000AC	// W, LCD Image 1 Scale Ratio
#define	HwLI1SCALE_Y_NS							HwZERO									// Non-Scalable
#define	HwLI1SCALE_Y_D2							Hw4										// DownScale by 2
#define	HwLI1SCALE_Y_D3							Hw5										// DownScale by 3
#define HwLI1SCALE_Y_D4							(Hw5+Hw4)								// DownScale by 4
#define	HwLI1SCALE_Y_D8							(Hw6+Hw5+Hw4)							// DownScale by 8
#define	HwLI1SCALE_Y_U2							(Hw7+Hw4)								// UpScale by 2
#define	HwLI1SCALE_Y_U3							(Hw7+Hw5)								// UpScale by 3
#define	HwLI1SCALE_Y_U4							(Hw7+Hw5+Hw4)							// UpScale by 4
#define	HwLI1SCALE_Y_U8							(Hw7+Hw6+Hw5+Hw4)						// UpScale by 8
#define	HwLI1SCALE_X_NS							HwZERO									// Non-Scalable
#define	HwLI1SCALE_X_D2							Hw0										// DownScale by 2
#define	HwLI1SCALE_X_D3							Hw1										// DownScale by 3
#define HwLI1SCALE_X_D4							(Hw1+Hw0)								// DownScale by 4
#define	HwLI1SCALE_X_D8							(Hw2+Hw1+Hw0)							// DownScale by 8
#define	HwLI1SCALE_X_U2							(Hw3+Hw0)								// UpScale by 2
#define	HwLI1SCALE_X_U3							(Hw3+Hw1)								// UpScale by 3
#define	HwLI1SCALE_X_U4							(Hw3+Hw1+Hw0)							// UpScale by 4
#define	HwLI1SCALE_X_U8							(Hw3+Hw2+Hw1+Hw0)						// UpScale by 8
                                        	
#define	HwLI2C									*(volatile unsigned long *)0xF00000B0	// W, LCD Image 2 Control Register
#define	HwLI2C_LUT_EN							Hw9										// Use the Color Lookup Table
#define HwLI2C_BR_BE							Hw7										// Big Endian pixel data
#define HwLI2C_YUV_420							Hw4										// YUV 4:2:0
#define HwLI2C_YUV_422							(Hw5+Hw4)								// YUV 4:2:2
#define HwLI2C_YUV_422P							(Hw6+Hw5+Hw4)							// YUV 4:2:2 Patch
#define HwLI2C_BPP_1							HwZERO									// Bit Per Pixel = 1bpp
#define HwLI2C_BPP_2							Hw0										// Bit Per Pixel = 2bpp
#define HwLI2C_BPP_4							Hw1										// Bit Per Pixel = 4bpp
#define HwLI2C_BPP_332							(Hw1+Hw0)								// Bit Per Pixel = 332bpp
#define HwLI2C_BPP_444							Hw2										// Bit Per Pixel = 444bpp
#define HwLI2C_BPP_565							(Hw2+Hw0)								// Bit Per Pixel = 565bpp
#define HwLI2C_BPP_555							(Hw2+Hw1)								// Bit Per Pixel = 555bpp
#define HwLI2C_BPP_888							(Hw2+Hw1+Hw0)							// Bit Per Pixel = 888bpp
                                        	
#define HwLI2P									*(volatile unsigned long *)0xF00000B4	// W, LCD Image 2 Position Register
                                        	
#define	HwLI2S									*(volatile unsigned long *)0xF00000B8	// W, LCD Image 2 Size Register
                                        	
#define	HwLI2BA0								*(volatile unsigned long *)0xF00000BC	// W, LCD Image 2 Base Address 0 Register
                                        	
#define	HwLI2CA									*(volatile unsigned long *)0xF00000C0	// W, LCD Image 2 Current Address Register
                                        	
#define	HwLI2BA1								*(volatile unsigned long *)0xF00000C4	// W, LCD Image 2 Base Address 1 Register
                                        	
#define HwLI2BA2								*(volatile unsigned long *)0xF00000C8	// W, LCD Image 2 Base Address 2 Register
                                        	
#define	HwLI2O									*(volatile unsigned long *)0xF00000CC	// W, LCD Image 2 Offset Register
                                        	
#define HwLI2SCALE								*(volatile unsigned long *)0xF00000D0	// W, LCD Image 2 Scale Ratio
#define	HwLI2SCALE_Y_NS							HwZERO									// Non-Scalable
#define	HwLI2SCALE_Y_D2							Hw4										// DownScale by 2
#define	HwLI2SCALE_Y_D3							Hw5										// DownScale by 3
#define HwLI2SCALE_Y_D4							(Hw5+Hw4)								// DownScale by 4
#define	HwLI2SCALE_Y_D8							(Hw6+Hw5+Hw4)							// DownScale by 8
#define	HwLI2SCALE_Y_U2							(Hw7+Hw4)								// UpScale by 2
#define	HwLI2SCALE_Y_U3							(Hw7+Hw5)								// UpScale by 3
#define	HwLI2SCALE_Y_U4							(Hw7+Hw5+Hw4)							// UpScale by 4
#define	HwLI2SCALE_Y_U8							(Hw7+Hw6+Hw5+Hw4)						// UpScale by 8
#define	HwLI2SCALE_X_NS							HwZERO									// Non-Scalable
#define	HwLI2SCALE_X_D2							Hw0										// DownScale by 2
#define	HwLI2SCALE_X_D3							Hw1										// DownScale by 3
#define HwLI2SCALE_X_D4							(Hw1+Hw0)								// DownScale by 4
#define	HwLI2SCALE_X_D8							(Hw2+Hw1+Hw0)							// DownScale by 8
#define	HwLI2SCALE_X_U2							(Hw3+Hw0)								// UpScale by 2
#define	HwLI2SCALE_X_U3							(Hw3+Hw1)								// UpScale by 3
#define	HwLI2SCALE_X_U4							(Hw3+Hw1+Hw0)							// UpScale by 4
#define	HwLI2SCALE_X_U8							(Hw3+Hw2+Hw1+Hw0)						// UpScale by 8
                                        	
#define	HwDLCTRL								*(volatile unsigned long *)0xF000000D4	// W, Dual LCD Control
#define	HwDLCTRL_DRE							Hw4										// Dual LCD Register Update Enable
#define HwDLCTRL_DLE							Hw0										// Dual LCD Operation Enable
                                        	
#define	HwDLCSA0								*(volatile unsigned long *)0xF00000DC	// W, Dual LCD Configuration Start Address 0
                                        	
#define	HwDLCSA1								*(volatile unsigned long *)0xF00000E0	// W, Dual LCD Configuration Start Address 1
                                        	
#define	HwY2RP0									*(volatile unsigned long *)0xF00000E4	// W, YCbCr to RGB Conversion Parameter 0
                                        	
#define	HwY2RP1									*(volatile unsigned long *)0xF00000E8	// W, YCbCr to RGB Conversion Parameter 1
                                        	
#define	HwLCDLUT								*(volatile unsigned long *)0xF0000C00	// W, LCD Lookup Table

/************************************************************************
*	LCD System Interface Register Define		(Base Addr = 0xF0000400)
************************************************************************/
#define	HwLCDSICTRL0							*(volatile unsigned long *)0xF0000400	// R/W, Control Register for LCDSI
#define HwLCDSICTRL0_IA_LOW						Hw15									// LACBIAS(Data Enable) signal is active low
#define HwLCDSICTRL0_IVS_LOW					Hw14									// LYSYNC signal is active low
#define HwLCDSICTRL0_CS_1						Hw7										// If IM is high, CS1 is active during operationgs. Otherwise, it is no applicable. These bits are only available when IM is high
#define HwLCDSICTRL0_RSP_HIGH					Hw6										// If IM is high, RS is high. Otherwise, it is not applicable
#define HwLCDSICTRL0_FMT_8RGB565				HwZERO									// LCDC pixel data output:RGB565
																						// LCDSI pixel data output(8bits):RGB565[7:0], RGB565[15:8]
																						// LCDSI CTRL1-4.WBW must be 1
#define HwLCDSICTRL0_FMT_16RGB565				(Hw4+Hw3)								// LCDC pixel data output:RGB565
																						// LCDSI pixel data output(16bits):RGB565[15:0]
																						// LCDSI CTRL1-4.WBW must be 0
#define HwLCDSICTRL0_FMT_8RGB888				Hw2										// LCDC pixel data output:RGB888
																						// LCDSI pixel data output(8bits):R[7:0],G[7:0],B[7:0]
																						// LCDSI CTRL1-4.WBW must be 1
#define HwLCDSICTRL0_FMT_9RGB888				(Hw3+Hw2)								// LCDC pixel data output:RGB888
																						// LCDSI pixel data output(9bits):{G[2:0],R[5:0]},{B[5:0],G[5:3]}
																						// LCDSI CTRL1-4.WBW must be 0
#define HwLCDSICTRL0_FMT_16RGB888				(Hw4+Hw2)								// LCDC pixel data output:RGB888
																						// LCDSI pixel data output(16bits):RGB565[15:0]
																						// LCDSI CTRL1-4.WBW must be 0
#define HwLCDSICTRL0_FMT_18RGB888				(Hw4+Hw3+Hw2)							// LCDC pixel data output:RGB888
																						// LCDSI pixel data output(16bits):{B[3:0],G[5:0],R[5:0]},B[5:4]
																						// LCDSI CTRL1-4.WBW must be 0
#define HwLCDSICTRL0_OM							Hw1										//
#define HwLCDSICTRL0_IM							Hw0										//
                                    			
#define	HwLCDSICTRL1							*(volatile unsigned long *)0xF0000800	// R/W, Control Register for nCS0 when RS = 0
#define	HwLCDSICTRL1_BW_8						HwZERO									// Data width is 8 bits
#define HwLCDSICTRL1_BW_16						Hw15									// Data width is 16 bits
#define HwLCDSICTRL1_BW_18						(Hw31+Hw15)								// Data width is 18 bits
                                    			
#define	HwLCDSICTRL2							*(volatile unsigned long *)0xF0000804	// R/W, Control Register for nCS0 when RS = 1
#define	HwLCDSICTRL2_BW_8						HwZERO									// Data width is 8 bits
#define HwLCDSICTRL2_BW_16						Hw15									// Data width is 16 bits
#define HwLCDSICTRL2_BW_18						(Hw31+Hw15)								// Data width is 18 bits
                                    			
#define	HwLCDSICTRL3							*(volatile unsigned long *)0xF0000808	// R/W, Control Register for nCS1 when RS = 0
#define	HwLCDSICTRL3_BW_8						HwZERO									// Data width is 8 bits
#define HwLCDSICTRL3_BW_16						Hw15									// Data width is 16 bits
#define HwLCDSICTRL3_BW_18						(Hw31+Hw15)								// Data width is 18 bits
                                    			
#define	HwLCDSICTRL4							*(volatile unsigned long *)0xF000080C	// R/W, Control Register for nCS0 when RS = 1
#define	HwLCDSICTRL4_BW_8						HwZERO									// Data width is 8 bits
#define HwLCDSICTRL4_BW_16						Hw15									// Data width is 16 bits
#define HwLCDSICTRL4_BW_18						(Hw31+Hw15)								// Data width is 18 bits
                                        	
#define	HwLCDSICS0RS0							*(volatile short *)0xF0000810			// R/W, If this register is read or written, reading or writing operations are generated on nCS0 while RS = 0
                                        	
#define	HwLCDSICS0RS1							*(volatile short *)0xF0000818			// R/W, If this register is read or written, reading or writing operations are generated on nCS0 while RS = 1
                                        	
#define	HwLCDSICS1RS0							*(volatile short *)0xF0000820			// R/W, If this register is read or written, reading or writing operations are generated on nCS1 while RS = 0
                                        	
#define	HwLCDSICS1RS1							*(volatile short *)0xF0000828			// R/W, If this register is read or written, reading or writing operations are generated on nCS1 while RS = 1
                                        	
/*                                      	
#define	HwLCDSICS0RS0							*(volatile unsigned long *)0xF0000810	// R/W, If this register is read or written, reading or writing operations are generated on nCS0 while RS = 0
#define	HwLCDSICS0RS1							*(volatile unsigned long *)0xF0000818	// R/W, If this register is read or written, reading or writing operations are generated on nCS0 while RS = 1
#define	HwLCDSICS1RS0							*(volatile unsigned long *)0xF0000820	// R/W, If this register is read or written, reading or writing operations are generated on nCS1 while RS = 0
#define	HwLCDSICS1RS1							*(volatile unsigned long *)0xF0000828	// R/W, If this register is read or written, reading or writing operations are generated on nCS1 while RS = 1
*/                                      	
                                        	
#define	HwLCDSICTRL5							*(volatile unsigned long *)0xF0000830	// R/W, 
#define	HwLCDSICTRL5_WBW						Hw31									//
                                        	
#define	HwLCDSICTRL6							*(volatile unsigned long *)0xF0000834	// R/W, 
#define	HwLCDSICTRL6_WBW						Hw31									//
                                        	
#define	HwLCDSICTRL7							*(volatile unsigned long *)0xF0000838	// R/W, 
#define	HwLCDSICTRL7_WBW						Hw31									//
                                        	
#define	HwLCDSICTRL8							*(volatile unsigned long *)0xF000083C	// R/W, 
#define	HwLCDSICTRL8_WBW						Hw31									//

/***********************************************************************
*	USB Controller Register Define				(Base Addr = 0xF0010000)
************************************************************************/
#define	HwIR									*(volatile unsigned long *)0xF0010000	// R/W, Index Register
                                        	
#define	HwEIR									*(volatile unsigned long *)0xF0010004	// R/W, Endpoint Interrupt Register
#define	HwEIR_EP0INT							Hw0										// W : Clear the EP0 interrupt flag, R : Indicates that the USB EP0 interrupt has been generated
#define	HwEIR_EP1INT							Hw1										// W : Clear the EP1 interrupt flag, R : Indicates that the USB EP1 interrupt has been generated
#define	HwEIR_EP2INT							Hw2										// W : Clear the EP2 interrupt flag, R : Indicates that the USB EP2 interrupt has been generated
#define	HwEIR_EP3INT							Hw3										// W : Clear the EP3 interrupt flag, R : Indicates that the USB EP3 interrupt has been generated
                                	    	
#define	HwEIER									*(volatile unsigned long *)0xF0010008	// R/W, Endpoint Interrupt Enable Register
#define	HwEIER_EP0INT_EN						Hw0										// Enable EP0 interrupt
#define	HwEIER_EP0INT_DIS						~Hw0									// Disable EP0 interrupt
#define	HwEIER_EP1INT_EN						Hw1										// Enable EP1 interrupt
#define	HwEIER_EP1INT_DIS						~Hw1									// Disable EP1 interrupt
#define	HwEIER_EP2INT_EN						Hw2										// Enable EP2 interrupt
#define	HwEIER_EP2INT_DIS						~Hw2									// Disable EP2 interrupt
#define	HwEIER_EP3INT_EN						Hw3										// Enable EP3 interrupt
#define	HwEIER_EP3INT_DIS						~Hw3									// Disable EP3 interrupt
                                        	
#define	HwFAR									*(volatile unsigned long *)0xF001000C	// Function Address Register
                                        	
#define	HwEDR									*(volatile unsigned long *)0xF0010014	// R/W, Endpoint Direction Register
#define	HwEDR_EP0_TX							Hw0										// Tx Endpoint
#define	HwEDR_EP0_RX							~Hw0									// Rx Endpoint
#define	HwEDR_EP1_TX							Hw1										// Tx Endpoint
#define	HwEDR_EP1_RX							~Hw1									// Rx Endpoint
#define	HwEDR_EP2_TX							Hw2										// Tx Endpoint
#define	HwEDR_EP2_RX							~Hw2									// Rx Endpoint
#define	HwEDR_EP3_TX							Hw3										// Tx Endpoint
#define	HwEDR_EP3_RX							~Hw3									// Rx Endpoint
                                        	
#define	HwUTST									*(volatile unsigned long *)0xF0010018	// Test Register
#define	HwUTST_VBUS_ON							Hw15									//
#define	HwUTST_VBUS_OFF							~Hw15									//
#define	HwUTST_EUERR							Hw13									// EB underrun error in transceiver
#define	HwUTST_PERR								Hw12									// PID Error Flag
#define	HwUTST_TPS_ON							Hw3										// Transmit test packets
#define	HwUTST_TPS_OFF							~Hw3									// Stop Transmitting
#define	HwUTST_TKS_ON							Hw2										// Transmit test K packets
#define	HwUTST_TKS_OFF							~Hw2									// Stop Transmitting
#define	HwUTST_TJS_ON							Hw1										// Transmit test J packets
#define	HwUTST_TJS_OFF							~Hw1									// Stop Transmitting
#define	HwUTST_TSNS_ON							Hw0										// Transmit test SE0 NAK
#define	HwUTST_TSNS_OFF							~Hw0									// Stop Transmitting
                                        	
#define	HwSSR									*(volatile unsigned long *)0xF001001C	// R/W, System Status Register
#define	HwSSR_BAERR								Hw15									// Byte-Align Error
#define	HwSSR_TMERR								Hw14									// Timeout Error
#define	HwSSR_BSERR								Hw13									// Bit Stuff Error
#define	HwSSR_TCERR								Hw12									// Token CRC Error
#define	HwSSR_DCERR								Hw11									// Data CRC Error
#define	HwSSR_EOERR								Hw10									// EB Overrun Error
#define	HwSSR_VBUS_OFF							Hw9										// VBUS is in Off state.
																						// 	(active when VBUS OFF interrupt is enabled)
#define	HwSSR_VBUS_ON							Hw8										// VBUS is in ON state.
																						// 	(active when VBUS ON interrupt is enabled)
#define	HwSSR_TBM								Hw7										// Toggle Bit Mismatch Error
#define	HwSSR_DP_HIGH							Hw6										// D+ == High State
#define	HwSSR_DP_LOW							~Hw6									// D+ == Low State
#define	HwSSR_DN_HIGH							Hw5										// D- == High State
#define	HwSSR_DN_LOW							~Hw5									// D- == Low State
#define	HwSSR_HSP_HIGH							Hw4										// Host is High Speed.
#define	HwSSR_HSP_FULL							~Hw4									// Host is Full Speed.
#define	HwSSR_SDE_END							Hw3										// Speed Detection is Ended.
#define	HwSSR_HFRM								Hw2										// Host sends Resume signaling.
#define	HwSSR_HFSUSP							Hw1										// Host sends Suspend signaling.
#define	HwSSR_HFRES								Hw0										// Host sends Reset signaling.
                                        	
#define	HwSCR									*(volatile unsigned long *)0xF0010020	// R/W, System Control Register
#define	HwSCR_DTZIEN_EN							Hw14									// DMA Total Count Zero Interrupt Enabled
#define	HwSCR_DTZIEN_DIS						~Hw14									// DMA Total Count Zero Interrupt Disabled
#define	HwSCR_DIEN_EN							Hw12									// Dual Interrupt Enabled
#define	HwSCR_DIEN_DIS							~Hw12									// Dual Interrupt Disabled
#define	HwSCR_VBUSOFF_EN						Hw11									// HwSSR(VBUS OFF flag) Enabled
#define	HwSCR_VBUSOFF_DIS						~Hw11									// HwSSR(VBUS OFF flag) Disabled
#define	HwSCR_VBUSON_EN							Hw10									// HwSSR(VBUS ON flag) Enabled
#define	HwSCR_VBUSON_DIS						~Hw10									// HwSSR(VBUS ON flag) Disabled
#define	HwSCR_RWDE_EN							Hw9										// High byte data [15:8] is sent first.
#define	HwSCR_RWDE_DIS							~Hw9									// Low byte data [7:0] is sent first.
#define	HwSCR_EIE_EN							Hw8										// Error Interrupt Enable
#define	HwSCR_EIE_DIS							~Hw8									// Error Interrupt Disable
#define	HwSCR_SDE_EN							Hw6										// Speed Detection End Interrupt Enable
#define	HwSCR_SDE_DIS							~Hw6									// Speed Detection End Interrupt Disable
#define	HwSCR_RRDE_EN							Hw5										// First received data is loaded in Low byte [7:0]
#define	HwSCR_RRDE_DIS							~Hw5									// First received data is loaded in High byte [15:8]
#define	HwSCR_IPS_HIGH							Hw4										// Active High Interrupt Polarity
#define	HwSCR_IPS_LOW							~Hw4									// Active Low Interrupt Polarity
#define	HwSCR_MFRM_ON							Hw2										// USB Core generates Resume signaling.
#define	HwSCR_MFRM_OFF							~Hw2									// USB Core stop generating Resume signaling.
#define	HwSCR_HSUSPE_EN							Hw1										// USB Core can repond to the Suspend signaling from HOST.
#define	HwSCR_HSUSPE_DIS						~Hw1									// USB Core cannot repond to the Suspend signaling from HOST.
#define	HwSCR_HRESE_EN							Hw0										// USB Core can repond to the Reset signaling from HOST.
#define	HwSCR_HRESE_DIS							~Hw0									// USB Core cannot repond to the Reset signaling from HOST.
                                        	
#define	HwEP0SR									*(volatile unsigned long *)0xF0010024	// R/W, EP0 Status Register
#define	HwEP0SR_LWO								Hw6										// Last Word Odd
#define	HwEP0SR_SHT								Hw4										// Stall Handshake Transmitted
#define	HwEP0SR_TST								Hw1										// TX Successfully Transmitted
#define	HwEP0SR_RSR								Hw0										// RX Successfully Received
                                        	
#define	HwEP0CR									*(volatile unsigned long *)0xF0010028	// R/W, EP0 Control Register
#define	HwEP0CR_TTE_EN							Hw3										// TX Test Enable
#define	HwEP0CR_TTE_DIS							~Hw3									// TX Test Disable
#define	HwEP0CR_TTS_SET							Hw2										// Set Toggle Bit (active when TTE is set)
#define	HwEP0CR_TTS_CLR							~Hw2									// Clear Toggle Bit (active when TTE is set)
#define	HwEP0CR_ESS_SET							Hw1										// Send STALL Handshake to Host
#define	HwEP0CR_ESS_CLR							~Hw1									// Stop sending STALL Handshake
#define	HwEP0CR_TZLS_SET						Hw0										// Transmit Zero Length Data (active when TTE is set)
#define	HwEP0CR_TZLS_CLR						~Hw0									// Stop Transmitting Zero Length Data (active when TTE is set)
                                        	
#define	HwESR									*(volatile unsigned long *)0xF001002C	// R/W, Endpoint Status Register
#define	HwESR_FUDR								Hw15									// FIFO Underflow
#define	HwESR_FOVF								Hw14									// FIFO Overflow
#define	HwESR_FPID_ON							Hw11									// First OUT packet cannot generate interrupt in OUT DMA operation.
#define	HwESR_FPID_OFF							~Hw11									// First OUT packet generate interrupt in OUT DMA operation.
#define	HwESR_OSD								Hw10									// OUT packet is first received after DMA registers are set.
#define	HwESR_DTCZ								Hw9										// DMA Total Count Zero
#define	HwESR_SPT								Hw8										// Short Packet Received during OUT DMA operation
#define	HwESR_DOM								Hw7										// Dual Operation Mode (Max packet = FIFO size / 2)
#define	HwESR_FFS								Hw6										// FIFO Flushed (Cleared by FLUSH of HwECR register)
#define	HwESR_FSC								Hw5										// Function Stall Condition is sent to Host.
#define	HwESR_LWO								Hw4										// Last Word Odd
#define	HwESR_PSIF_NP							HwZERO									// No Packet in FIFO
#define	HwESR_PSIF_1P							Hw2										// 1 Packet in FIFO
#define	HwESR_PSIF_2P							Hw3										// 2 Packets in FIFO
#define	HwESR_TPS								Hw1										// TX Packet Success
#define	HwESR_RPS								Hw0										// RX Packet Success
                                        	
#define	HwECR									*(volatile unsigned long *)0xF0010030	// R/W, Endpoint Control Register
#define	HwECR_INHLD_EN							Hw12									// In-Packet Hold Enable (USB sends NAK regardless of IN FIFO status)
#define	HwECR_INHLD_DIS							~Hw12									// In-Packet Hold Disable (USB sends IN data)
#define	HwECR_OUTHLD_EN							Hw11									// Out-Packet Hold Enable (USB doesn't accept OUT data)
#define	HwECR_OUTHLD_DIS						~Hw11									// Out-Packet Hold Disable (USB accept OUT data)
#define	HwECR_TNPMF_1T							Hw9										// 1 Transaction Per MicroFrame
#define	HwECR_TNPMF_2T							Hw10									// 2 Transactions Per MicroFrame
#define	HwECR_TNPMF_3T							(Hw10+Hw9)								// 3 Transactions Per MicroFrame
#define	HwECR_DUEN_EN							Hw7										// Dual FIFO Mode Enable
#define	HwECR_DUEN_DIS							~Hw7									// Dual FIFO Mode Disable
#define	HwECR_FLUSH_EN							Hw6										// FIFO is Flushed (automatically cleared after writing)
#define	HwECR_TTE_EN							Hw5										// TX Toggle Forcing Enable
#define	HwECR_TTE_DIS							~Hw5									// TX Toggle Forcing Disable
#define	HwECR_TTS_PID0							HwZERO									// TX Data Toggle bit = PID 0
#define	HwECR_TTS_PID1							Hw3										// TX Data Toggle bit = PID 1
#define	HwECR_TTS_PID2							Hw4										// TX Data Toggle bit = PID 2 (ISO only)
#define	HwECR_TTS_PIDM							(Hw4+Hw3)								// TX Data Toggle bit = PID M (ISO only)
#define	HwECR_CDP_CLR							Hw2										// Clear Data PID register
#define	HwECR_ESS_SET							Hw1										// send STALL handshake to Host
#define	HwECR_ESS_CLR							~Hw1									// stop sending STALL handshake
#define	HwECR_TZLS_SET							Hw0										// Transmit Zero Length Data (active when TTE is set)
#define	HwECR_TZLS_CLR							~Hw0									// Stop Transmitting Zero Length Data (active when TTE is set)
                                        	
#define	HwBRCR									*(volatile unsigned long *)0xF0010034	// R, Byte Read Counter (Half-word unit)
                                        	
#define	HwBWCR									*(volatile unsigned long *)0xF0010038	// W, Byte Write Counter (Byte unit)
                                        	
#define	HwMPR									*(volatile unsigned long *)0xF001003C	// R/W, Max Packet Register (Byte unit)
                                        	
#define	HwDCR									*(volatile unsigned long *)0xF0010040	// R/W, DMA Control Register
#define	HwDCR_ARDRD_ON							Hw5										// Auto RX DMA Run Disable On
#define	HwDCR_ARDRD_OFF							~Hw5									// Auto RX DMA Run Disable Off
#define	HwDCR_FMDE_EN							Hw4										// Fly Mode DMA Enable
#define	HwDCR_FMDE_DIS							~Hw4									// Fly Mode DMA Disable
#define	HwDCR_DMDE_EN							Hw3										// Demand Mode DMA Enable
#define	HwDCR_DMDE_DIS							~Hw3									// Demand Mode DMA Disable
#define	HwDCR_TDR_RUN							Hw2										// TX DMA Run
#define	HwDCR_TDR_STOP							~Hw2									// TX DMA Stop
#define	HwDCR_RDR_RUN							Hw1										// RX DMA Run
#define	HwDCR_RDR_STOP							~Hw1									// RX DMA Stop
#define	HwDCR_DEN_EN							Hw0										// DMA Enable
#define	HwDCR_DEN_DIS							~Hw0									// DMA Disable
                                        	
#define	HwDTCR									*(volatile unsigned long *)0xF0010044	// DMA Transfer Counter Register (Byte unit)
                                        	
#define	HwDFCR									*(volatile unsigned long *)0xF0010048	// DMA FIFO Counter Register (Byte unit)
                                        	
#define	HwDTTCR1								*(volatile unsigned long *)0xF001004C	// Lower-Half of DMA Total Transfer Counter Register
                                        	
#define	HwDTTCR2								*(volatile unsigned long *)0xF0010050	// Upper-Half of DMA Total Transfer Counter Register
                                        	
#define	HwEP0BUF								*(volatile unsigned long *)0xF0010060	// EP0 Buffer Register
                                        	
#define	HwEP1BUF								*(volatile unsigned long *)0xF0010064	// EP1 Buffer Register
                                        	
#define	HwEP2BUF								*(volatile unsigned long *)0xF0010068	// EP2 Buffer Register
                                        	
#define	HwEP3BUF								*(volatile unsigned long *)0xF001006C	// EP3 Buffer Register
                                        	
#define	HwDLYCTRL								*(volatile unsigned long *)0xF0010080	// Delay Control Register
                                        	
#define HwDMAR1									*(volatile unsigned long *)0xF00100A0	// DMA MCU Address Register 1
                                        	
#define HwDMAR2									*(volatile unsigned long *)0xF00100A4	// DMA MCU Address Register 2
                                        	
#define HwDTSR									*(volatile unsigned long *)0xF00100C0	// DMA Transfer Status Register
                                        	
#define	HwUBCFG									*(volatile unsigned long *)0xF00100C4	// R/W, USB Configuration Register
#define HwUBCFG_XSEL_FS							Hw13									// FS Transceiver enable
#define HwUBCFG_TERM_FSOS						(Hw12+Hw11)								// Full-speed termination is enabled for FS-only and FS-Serial modes
#define HwUBCFG_TERM_LS							Hw12									// Low-speed signaling is enable for LS-Serial modes
#define HwUBCFG_TERM_FS							Hw11									// Full-speed termination is enabled
#define HwUBCFG_TERM_HS							HwZERO									// High-speed termination is enabled
#define	HwUBCFG_FSXO_SERIAL						Hw10									// Serial Interface Select
#define	HwUBCFG_DWS_HOST						Hw6										// Host Mode
#define	HwUBCFG_XO_EN							Hw5										// XO_OUT output enable
#define	HwUBCFG_CKSEL_12						HwZERO									// 12MHz
#define	HwUBCFG_CKSEL_24						Hw0										// 24MHz
#define	HwUBCFG_CKSEL_48						Hw1										// 48MHz

/************************************************************************
*	USB Host Register Define					(Base Addr = 0xF0020000)
************************************************************************/
#define	HwHcRevision							*(volatile unsigned long *)0xF0020000	// Control and status register
                                        	
#define	HwHcControl								*(volatile unsigned long *)0xF0020004	// Control and status register
                                        	
#define	HwHcCommandStatus						*(volatile unsigned long *)0xF0020008	// Control and status register
                                        	
#define	HwHcInterruptStatus						*(volatile unsigned long *)0xF002000C	// Control and status register
                                        	
#define	HwHcInterruptEnable						*(volatile unsigned long *)0xF0020010	// Control and status register
                                        	
#define	HwHcInterruptDisable					*(volatile unsigned long *)0xF0020014	// Control and status register
                                        	
#define	HwHcHCCA								*(volatile unsigned long *)0xF0020018	// Memory pointer register
                                        	
#define	HwHcPeroidCurrentED						*(volatile unsigned long *)0xF002001C	// Memory pointer register
                                        	
#define	HwHcControlHeadED						*(volatile unsigned long *)0xF0020020	// Memory pointer register
                                        	
#define	HwHcControlCurrentED					*(volatile unsigned long *)0xF0020024	// Memory pointer register
                                        	
#define	HwHcBulkHeadED							*(volatile unsigned long *)0xF0020028	// Memory pointer register
                                        	
#define	HwHcBulkCurrentED						*(volatile unsigned long *)0xF002002C	// Memory pointer register
                                        	
#define	HwHcDoneHead							*(volatile unsigned long *)0xF0020030	// Memory pointer register
                                        	
#define	HwHcRmInterval							*(volatile unsigned long *)0xF0020034	// Frame counter register
                                        	
#define	HwHcFmRemaining							*(volatile unsigned long *)0xF0020038	// Frame counter register
                                        	
#define	HwHcFmNumber							*(volatile unsigned long *)0xF002003C	// Frame counter register
                                        	
#define	HwHcPeriodStart							*(volatile unsigned long *)0xF0020040	// Frame counter register
                                        	
#define	HwHcLSThreshold							*(volatile unsigned long *)0xF0020044	// Frame counter register
                                        	
#define	HwRhDescriptorA							*(volatile unsigned long *)0xF0020048	// Root hub register
                                        	
#define	HwRhDescriptorB							*(volatile unsigned long *)0xF002004C	// Root hub register
                                        	
#define	HwRhStatus								*(volatile unsigned long *)0xF0020050	// Root hub register
                                        	
#define	HwRhPortStatus1							*(volatile unsigned long *)0xF0020054	// Root hub register
                                        	
#define	HwRhPortStatus2							*(volatile unsigned long *)0xF0020058	// Root hub register
                                        	
#define	HwUHINT_ST								HwHcInterruptStatus
#define	HwUHINT_EN								HwHcInterruptEnable
#define	HwUHINT_DIS								HwHcInterruptDisable
#define	HwUH_RHP0								HwRhPortStatus1
#define	HwUHCMD_ST								HwHcCommandStatus

/************************************************************************
*	IDE Interface Register Define				(Base Addr = 0xF0030000)
************************************************************************/
#define	HwCS0n									*(volatile unsigned long *)0xF0030000	// R/W, PIO CS0n Access register
#define	HwCS00									0xF0030000								// PIO CS00 Register Address
                                        	
#define	REG_PTR    								*(volatile unsigned short *)			// get the content of pointer
#define	IDE_BASE_CS0							0xF0030000
#define	HwIDE_RD_DATA							(REG_PTR(IDE_BASE_CS0+(0x00<<2)+ 0x00))
#define	HwIDE_WR_DATA							HwIDE_RD_DATA
                                        	
#define	HwCS1n									*(volatile unsigned long *)0xF0030020	// R/W, PIO CS1n Access register
#define	HwCS10									0xF0030020								// PIO CS10 Register Address
                                        	
#define	HwPIOCTRL								*(volatile unsigned long *)0xF0030040	// R/W, PIO Mode control register
#define	HwPIOCTRL_SYNC_BYPASS					HwZERO									// Bypass
#define	HwPIOCTRL_SYNC_1						Hw21									// 1 Sync
#define	HwPIOCTRL_SYNC_2						Hw22									// 2 Sync
#define	HwPIOCTRL_MD_PIO						HwZERO									// PIO Mode
#define	HwPIOCTRL_MD_UDMA						Hw20									// UDMA(IN/OUT) Mode
#define	HwPIOCTRL_RDY_IRR						HwZERO									// PW cycles is irrelative of IORDY
#define	HwPIOCTRL_RDY_EXT						Hw0										// PW cycles are extended by IORDY
                                        	
#define	HwUDMACTRL								*(volatile unsigned long *)0xF0030044	// R/W, UDMA Mode control register
#define	HwUDMACTRL_HTRL4						HwZERO									// 4
#define	HwUDMACTRL_HTRL8						Hw28									// 8
#define	HwUDMACTRL_HTRL12						Hw29									// 12
#define	HwUDMACTRL_HTRL14						(Hw29+Hw28)								// 14
#define	HwUDMACTRL_OTL1							HwZERO									// Single Transfer (1read/1write)
#define	HwUDMACTRL_OTL4							Hw25									// 4 (vcnt <= 12)
#define	HwUDMACTRL_OTL8							Hw26									// 8 (vcnt <= 8)
#define	HwUDMACTRL_OTL12						(Hw26+Hw25)								// 12 (vcnt <= 4)
#define	HwUDMACTRL_OTL16						(Hw27+Hw26)								// 16 (Empty)
#define	HwUDMACTRL_ITL1							HwZERO									// Single Transfer
#define	HwUDMACTRL_ITL4							Hw23									// 4 (32bit data) (vcnt >= 4)
#define	HwUDMACTRL_ITL8							Hw24									// 8 (32bit data) (vcnt >= 8)
#define	HwUDMACTRL_ITL12						(Hw24+Hw23)								// 12 (32bit data) (vcnt >= 12)
#define	HwUDMACTRL_AHB1							HwZERO									// The hold margin of the data to be transferred has one AHB clock period
#define	HwUDMACTRL_AHB2							Hw15									// The hold margin of the data to be transferred has two AHB clock period
#define	HwUDMACTRL_HTB_OFF						HwZERO									//
#define	HwUDMACTRL_HTB_ON						Hw5										// HOST terminate operation when CTCNT reaches zero.
#define	HwUDMACTRL_TS16							HwZERO									// 16bit Transfer Mode (in Internal Bus)
#define	HwUDMACTRL_TS32							Hw4										// 32bit Transfer Mode (in Internal Bus)
#define	HwUDMACTRL_BS_OFF						HwZERO									//
#define	HwUDMACTRL_BS_ON						Hw3										// BUS Share Mode
#define	HwUDMACTRL_HT_OFF						HwZERO									//
#define	HwUDMACTRL_HT_ON						Hw2										// HOST Termination
#define	HwUDMACTRL_UIO_IN						HwZERO									// UDMA-IN Mode
#define	HwUDMACTRL_UIO_OUT						Hw1										// UDMA-OUT Mode
#define	HwUDMACTRL_UEN_OFF						HwZERO									//
#define	HwUDMACTRL_UEN_ON						Hw0										// UDMA Enable Bit
                                        	
#define	HwIDMACTRL								*(volatile unsigned long *)0xF0030048	// R/W, IDMA control register
#define	HwIDMACTRL_ARB_OFF						HwZERO									//
#define	HwIDMACTRL_ARB_ON						Hw4										// IDMA transfer executed with arbitration transfer
#define	HwIDMACTRL_LOC_OFF						HwZERO									//
#define	HwIDMACTRL_LOC_ON						Hw3										// DMA transfer executed with lock transfer
#define	HwIDMACTRL_CON							HwZERO									// DMA transfer begins from CSAR/CDAR address
#define	HwIDMACTRL_CON_MEAN						Hw2										// DMA transfer begins from CSAR/CDAR address, It must be used after the former transfer has been executed, so that CSAR and CDAR contaion a meaningful value
#define	HwIDMACTRL_REP_AUTODIS					HwZERO									// When UDMA operation end, IDE bit is automatically disabled
#define	HwIDMACTRL_REP_NOTDIS					Hw1										// When UDMA operation end, IDE bit is not disabled
#define	HwIDMACTRL_IDE_OFF						HwZERO									//
#define	HwIDMACTRL_IDE_ON						Hw0										// Internal DMA(IDMA) enable bit
                                        	
#define	HwIDMASA								*(volatile unsigned long *)0xF003004C	// R/W, IDMA source address register
                                        	
#define	HwIDMASP								*(volatile unsigned long *)0xF0030050	// R/W, IDMA source parameter register
                                        	
#define	HwIDMACSA								*(volatile unsigned long *)0xF0030054	// R, IDMA current source address register
                                        	
#define	HwIDMADA								*(volatile unsigned long *)0xF0030058	// R/W, destination address IDMA register
                                        	
#define	HwIDMADP								*(volatile unsigned long *)0xF003005C	// R/W, destination parameter IDMA register
                                        	
#define	HwIDMACDA								*(volatile unsigned long *)0xF0030060	// R, current destination address IDMA register
                                        	
#define	HwIDEINT								*(volatile unsigned long *)0xF0030064	// R/W, IDE interrupt register
#define	HwIDEINT_UB								Hw31									// UDMA is Busy(1), State of UDMA is IDLE(0)
#define	HwIDEINT_NWA_ON							HwZERO									// Word(32bit) aligned
#define	HwIDEINT_NWA_OFF						Hw30									// Not Word(32bit) aligned
#define	HwIDEINT_DT_OFF							HwZERO									// Device did not terminate operation
#define	HwIDEINT_DT_ON							Hw29									// Device terminated operation
#define	HwIDEINT_URS_AUTOCLR					HwZERO									// UDMA request from the device is not active or automatically clear
#define	HwIDEINT_URS_ACTIVE						Hw11									// UDMA request from the device is active
#define	HwIDEINT_FES_GOOD						HwZERO									// Not FIFO Error
#define	HwIDEINT_FES_ERROR						Hw10									// FIFO Error
#define	HwIDEINT_TRS_AUTOCLR					HwZERO									// Trigger level request is not active or automatically clear
#define	HwIDEINT_TRS_ACTIVE						Hw9										// Trigger level request is active
#define	HwIDEINT_OPE_OFF						HwZERO									// Host or Device dose not terminate operation yet
#define	HwIDEINT_OPE_ON							Hw8										// Host or Device terminate operation
#define	HwIDEINT_URE_DIS						HwZERO									// UDMA request interrupt is disabled
#define	HwIDEINT_URE_EN							Hw3										// UDMA request interrupt is enabled
#define	HwIDEINT_FEE_DIS						HwZERO									// FIFO Error interrupt is disabled
#define	HwIDEINT_FEE_EN							Hw2										// FIFO Error interrupt is enabled
#define	HwIDEINT_TRE_DIS						HwZERO									// Trigger level interrupt is disabled
#define	HwIDEINT_TRE_EN							Hw1										// Trigger level interrupt is enabled
                                        	
#define	HwUDMATCNT								*(volatile unsigned long *)0xF0030068	// R/W, UDMA transfer counter register
                                        	
#define	HwUDMAIN								*(volatile unsigned long *)0xF003006C	// R, UDMA-IN access register
                                        	
#define	HwUDMAOUT								*(volatile unsigned long *)0xF0030070	// W, UDMA-OUT access register
                                        	
#define	HwUDMACRC								*(volatile unsigned long *)0xF0030074	// R, UDMA CRC register
                                        	
#define	HwUDMACTCNT								*(volatile unsigned long *)0xF0030078	// R, UDMA status register

/***********************************************************************
*	DMA Controller Register Define				(Base Addr = 0xF0040000)
************************************************************************/
#define	HwST_SADR0								*(volatile unsigned long *)0xF0040000	// R/W, Start Address of Source Block Register
                                    	
#define	HwSPARAM0								*(volatile unsigned long *)0xF0040004	// R/W, Parameter of Source Block Register
                                    	
#define	HwC_SADR0								*(volatile unsigned long *)0xF004000C	// R, Current Address of Source Block Register
                                    	
#define	HwST_DADR0								*(volatile unsigned long *)0xF0040010	// R/W, Start Address of Destination Block Register
                                    	
#define	HwDPARAM0								*(volatile unsigned long *)0xF0040014	// R/W, Parameter of Destination Block Register
                                    	
#define	HwC_DADR0								*(volatile unsigned long *)0xF004001C	// R, Current Address of Destination Block Register
                                    	
#define	HwHCOUNT0								*(volatile unsigned long *)0xF0040020	// R/W, Initial and Current Hop Count Register
                                    	
#define	HwCHCTRL0								*(volatile unsigned long *)0xF0040024	// R/W, Channel Control Register
#define	HwCHCTRL0_DMASEL_UART1_RX				Hw30									// Connected Hardware = UART Channel 1 Receiver
#define	HwCHCTRL0_DMASEL_UART1_TX				Hw29									// Connected Hardware = UART Channel 1 Transmitter
#define	HwCHCTRL0_DMASEL_UART0_RX				Hw28									// Connected Hardware = UART Channel 0 Receiver
#define	HwCHCTRL0_DMASEL_UART0_TX				Hw27									// Connected Hardware = UART Channel 0 Transmitter
#define	HwCHCTRL0_DMASEL_GSIO					Hw26									// Connected Hardware = GSIO Controller
#define	HwCHCTRL0_DMASEL_I2C_CH1				Hw25									// Connected Hardware = I2C Controller Channel 1
#define	HwCHCTRL0_DMASEL_DAIR					Hw24									// Connected Hardware = DAI Receiver
#define	HwCHCTRL0_DMASEL_DAIT					Hw23									// Connected Hardware = DAI Transmitter
#define	HwCHCTRL0_DMASEL_CDIF					Hw22									// Connected Hardware = CD I/F
#define	HwCHCTRL0_DMASEL_SPDIF_UDATA			Hw21									// Connected Hardware = SPDIF User Data
#define	HwCHCTRL0_DMASEL_SPDIF_PDATA			Hw20									// Connected Hardware = SPDIF Packet(Audio) Data
#define	HwCHCTRL0_DMASEL_I2C_CH0				Hw19									// Connected Hardware = I2C Controller Channel 0
#define	HwCHCTRL0_DMASEL_NFC					Hw18									// Connected Hardware = NAND Flash Controller
#define	HwCHCTRL0_DMASEL_MSTICK					Hw17									// Connected Hardware = Memory Stick
#define	HwCHCTRL0_DMASEL_SDMMC					Hw16									// Connected Hardware = SD/MMC
#define HwCHCTRL0_CONT_C						Hw15									// DMA transfer begins from C_SADR / C_DADR address. It must be used after the former transfer has been executed, so that C_SADR and C_DADR contain a meaningful vlaue
#define HwCHCTRL0_SWAP_EN						Hw14									// Swap Channel 1 Data
#define HwCHCTRL0_SYNC_EN						Hw13									// Synchronize Hardware Request
#define HwCHCTRL0_HRD_W							Hw12									// ACK/EOT signals are issued When DMA-Write Operation
#define HwCHCTRL0_LOCK_EN						Hw11									// DMA transfer executed with lock transfer
#define HwCHCTRL0_BST_NOARB						Hw10									// DMA transfer executed with no arbitration(burst operation)
#define HwCHCTRL0_TYPE_SE						HwZERO									// SINGLE transfer with edge-triggered detection
#define HwCHCTRL0_TYPE_SL						(Hw9+Hw8)								// SINGLE transfer with level-triggered detection
#define HwCHCTRL0_TYPE_HW						Hw8										// HW transfer
#define HwCHCTRL0_TYPE_SW						Hw9										// SW transfer
#define HwCHCTRL0_BSIZE_1						HwZERO									// 1 Burst transfer consists of 1 read or write cycle
#define HwCHCTRL0_BSIZE_2						Hw6										// 1 Burst transfer consists of 2 read or write cycle
#define HwCHCTRL0_BSIZE_4						Hw7										// 1 Burst transfer consists of 4 read or write cycle
#define HwCHCTRL0_BSIZE_8						(Hw7+Hw6)								// 1 Burst transfer consists of 8 read or write cycle
#define HwCHCTRL0_WSIZE_8						HwZERO									// Each cycle read or write 8bit data
#define HwCHCTRL0_WSIZE_16						Hw4										// Each cycle read or write 16bit data
#define HwCHCTRL0_WSIZE_32						Hw5										// Each cycle read or write 32bit data
#define HwCHCTRL0_FLAG							Hw3										// W : Clears FLAG to 0, R : Represents that all hop of transfer are fulfilled
#define HwCHCTRL0_IEN_EN						Hw2										// At the same time the FLAG goes to 1, DMA interrupt request is generated
#define HwCHCTRL0_REP_EN						Hw1										// The DMA channel remains enabled. When another DMA request has occurred, the DMA channel start transfer data again with the same manner(type,address,increment,mask) as the latest transfer of that channel
#define HwCHCTRL0_EN_EN							Hw0										// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request
                                    	
#define	HwRPTCTRL0								*(volatile unsigned long *)0xF0040028	// R/W, Repeat Control Register
#define HwRPTCTRL0_DRI_LAST						Hw31									// DAM interrupt occur is  occurred at the last DMA Repeated DMA operation
#define HwRPTCTRL0_DEOT_LAST					Hw30									// EOT signal is occurred at the last Repeated DAM operation in HW(including Single) transfer Mode
                                    		
#define	HwST_SADR1								*(volatile unsigned long *)0xF0040100	// R/W, Start Address of Source Block Register
                                    		
#define	HwSPARAM1								*(volatile unsigned long *)0xF0040104	// R/W, Parameter of Source Block Register
                                    		
#define	HwC_SADR1								*(volatile unsigned long *)0xF004010C	// R, Current Address of Source Block Register
                                    		
#define	HwST_DADR1								*(volatile unsigned long *)0xF0040110	// R/W, Start Address of Destination Block Register
                                    		
#define	HwDPARAM1								*(volatile unsigned long *)0xF0040114	// R/W, Parameter of Destination Block Register
                                    		
#define	HwC_DADR1								*(volatile unsigned long *)0xF004011C	// R, Current Address of Destination Block Register
                                    		
#define	HwHCOUNT1								*(volatile unsigned long *)0xF0040120	// R/W, Initial and Current Hop Count Register
                                    		
#define	HwCHCTRL1								*(volatile unsigned long *)0xF0040124	// R/W, Channel Control Register
#define	HwCHCTRL1_DMASEL_UART1_RX				Hw30									// Connected Hardware = UART Channel 1 Receiver
#define	HwCHCTRL1_DMASEL_UART1_TX				Hw29									// Connected Hardware = UART Channel 1 Transmitter
#define	HwCHCTRL1_DMASEL_UART0_RX				Hw28									// Connected Hardware = UART Channel 0 Receiver
#define	HwCHCTRL1_DMASEL_UART0_TX				Hw27									// Connected Hardware = UART Channel 0 Transmitter
#define	HwCHCTRL1_DMASEL_GSIO					Hw26									// Connected Hardware = GSIO Controller
#define	HwCHCTRL1_DMASEL_I2C_CH1				Hw25									// Connected Hardware = I2C Controller Channel 1
#define	HwCHCTRL1_DMASEL_DAIR					Hw24									// Connected Hardware = DAI Receiver
#define	HwCHCTRL1_DMASEL_DAIT					Hw23									// Connected Hardware = DAI Transmitter
#define	HwCHCTRL1_DMASEL_CDIF					Hw22									// Connected Hardware = CD I/F
#define	HwCHCTRL1_DMASEL_SPDIF_UDATA			Hw21									// Connected Hardware = SPDIF User Data
#define	HwCHCTRL1_DMASEL_SPDIF_PDATA			Hw20									// Connected Hardware = SPDIF Packet(Audio) Data
#define	HwCHCTRL1_DMASEL_I2C_CH0				Hw19									// Connected Hardware = I2C Controller Channel 0
#define	HwCHCTRL1_DMASEL_NFC					Hw18									// Connected Hardware = NAND Flash Controller
#define	HwCHCTRL1_DMASEL_MSTICK					Hw17									// Connected Hardware = Memory Stick
#define	HwCHCTRL1_DMASEL_SDMMC					Hw16									// Connected Hardware = SD/MMC
#define HwCHCTRL1_CONT_C						Hw15									// DMA transfer begins from C_SADR / C_DADR address. It must be used after the former transfer has been executed, so that C_SADR and C_DADR contain a meaningful vlaue
#define HwCHCTRL1_SWAP_EN						Hw14									// Swap Channel 1 Data
#define HwCHCTRL1_SYNC_EN						Hw13									// Synchronize Hardware Request
#define HwCHCTRL1_HRD_W							Hw12									// ACK/EOT signals are issued When DMA-Write Operation
#define HwCHCTRL1_LOCK_EN						Hw11									// DMA transfer executed with lock transfer
#define HwCHCTRL1_BST_NOARB						Hw10									// DMA transfer executed with no arbitration(burst operation)
#define HwCHCTRL1_TYPE_SE						HwZERO									// SINGLE transfer with edge-triggered detection
#define HwCHCTRL1_TYPE_SL						(Hw9+Hw8)								// SINGLE transfer with level-triggered detection
#define HwCHCTRL1_TYPE_HW						Hw8										// HW transfer
#define HwCHCTRL1_TYPE_SW						Hw9										// SW transfer
#define HwCHCTRL1_BSIZE_1						HwZERO									// 1 Burst transfer consists of 1 read or write cycle
#define HwCHCTRL1_BSIZE_2						Hw6										// 1 Burst transfer consists of 2 read or write cycle
#define HwCHCTRL1_BSIZE_4						Hw7										// 1 Burst transfer consists of 4 read or write cycle
#define HwCHCTRL1_BSIZE_8						(Hw7+Hw6)								// 1 Burst transfer consists of 8 read or write cycle
#define HwCHCTRL1_WSIZE_8						HwZERO									// Each cycle read or write 8bit data
#define HwCHCTRL1_WSIZE_16						Hw4										// Each cycle read or write 16bit data
#define HwCHCTRL1_WSIZE_32						Hw5										// Each cycle read or write 32bit data
#define HwCHCTRL1_FLAG							Hw3										// W : Clears FLAG to 0, R : Represents that all hop of transfer are fulfilled
#define HwCHCTRL1_IEN_EN						Hw2										// At the same time the FLAG goes to 1, DMA interrupt request is generated
#define HwCHCTRL1_REP_EN						Hw1										// The DMA channel remains enabled. When another DMA request has occurred, the DMA channel start transfer data again with the same manner(type,address,increment,mask) as the latest transfer of that channel
#define HwCHCTRL1_EN_EN							Hw0										// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request
                                    		
#define	HwRPTCTRL1								*(volatile unsigned long *)0xF0040128	// R/W, Repeat Control Register
#define HwRPTCTRL1_DRI_LAST						Hw31									// DAM interrupt occur is  occurred at the last DMA Repeated DMA operation
#define HwRPTCTRL1_DEOT_LAST					Hw30									// EOT signal is occurred at the last Repeated DAM operation in HW(including Single) transfer Mode
                                    		
#define	HwST_SADR2								*(volatile unsigned long *)0xF0040200	// R/W, Start Address of Source Block Register
                                    		
#define	HwSPARAM2								*(volatile unsigned long *)0xF0040204	// R/W, Parameter of Source Block Register
                                    		
#define	HwC_SADR2								*(volatile unsigned long *)0xF004020C	// R, Current Address of Source Block Register
                                    		
#define	HwST_DADR2								*(volatile unsigned long *)0xF0040210	// R/W, Start Address of Destination Block Register
                                    		
#define	HwDPARAM2								*(volatile unsigned long *)0xF0040214	// R/W, Parameter of Destination Block Register
                                    		
#define	HwC_DADR2								*(volatile unsigned long *)0xF004021C	// R, Current Address of Destination Block Register
                                    		
#define	HwHCOUNT2								*(volatile unsigned long *)0xF0040220	// R/W, Initial and Current Hop Count Register
                                    		
#define	HwCHCTRL2								*(volatile unsigned long *)0xF0040224	// R/W, Channel Control Register
#define	HwCHCTRL0_DMASEL_UART1_RX				Hw30									// Connected Hardware = UART Channel 1 Receiver
#define	HwCHCTRL0_DMASEL_UART1_TX				Hw29									// Connected Hardware = UART Channel 1 Transmitter
#define	HwCHCTRL0_DMASEL_UART0_RX				Hw28									// Connected Hardware = UART Channel 0 Receiver
#define	HwCHCTRL0_DMASEL_UART0_TX				Hw27									// Connected Hardware = UART Channel 0 Transmitter
#define	HwCHCTRL0_DMASEL_GSIO					Hw26									// Connected Hardware = GSIO Controller
#define	HwCHCTRL0_DMASEL_I2C_CH1				Hw25									// Connected Hardware = I2C Controller Channel 1
#define	HwCHCTRL0_DMASEL_DAIR					Hw24									// Connected Hardware = DAI Receiver
#define	HwCHCTRL0_DMASEL_DAIT					Hw23									// Connected Hardware = DAI Transmitter
#define	HwCHCTRL0_DMASEL_CDIF					Hw22									// Connected Hardware = CD I/F
#define	HwCHCTRL0_DMASEL_SPDIF_UDATA			Hw21									// Connected Hardware = SPDIF User Data
#define	HwCHCTRL0_DMASEL_SPDIF_PDATA			Hw20									// Connected Hardware = SPDIF Packet(Audio) Data
#define	HwCHCTRL0_DMASEL_I2C_CH0				Hw19									// Connected Hardware = I2C Controller Channel 0
#define	HwCHCTRL0_DMASEL_NFC					Hw18									// Connected Hardware = NAND Flash Controller
#define	HwCHCTRL0_DMASEL_MSTICK					Hw17									// Connected Hardware = Memory Stick
#define	HwCHCTRL0_DMASEL_SDMMC					Hw16									// Connected Hardware = SD/MMC
#define HwCHCTRL2_CONT_C						Hw15									// DMA transfer begins from C_SADR / C_DADR address. It must be used after the former transfer has been executed, so that C_SADR and C_DADR contain a meaningful vlaue
#define HwCHCTRL2_SWAP_EN						Hw14									// Swap Channel 1 Data
#define HwCHCTRL2_SYNC_EN						Hw13									// Synchronize Hardware Request
#define HwCHCTRL2_HRD_W							Hw12									// ACK/EOT signals are issued When DMA-Write Operation
#define HwCHCTRL2_LOCK_EN						Hw11									// DMA transfer executed with lock transfer
#define HwCHCTRL2_BST_NOARB						Hw10									// DMA transfer executed with no arbitration(burst operation)
#define HwCHCTRL2_TYPE_SE						HwZERO									// SINGLE transfer with edge-triggered detection
#define HwCHCTRL2_TYPE_SL						(Hw9+Hw8)								// SINGLE transfer with level-triggered detection
#define HwCHCTRL2_TYPE_HW						Hw8										// HW transfer
#define HwCHCTRL2_TYPE_SW						Hw9										// SW transfer
#define HwCHCTRL2_BSIZE_1						HwZERO									// 1 Burst transfer consists of 1 read or write cycle
#define HwCHCTRL2_BSIZE_2						Hw6										// 1 Burst transfer consists of 2 read or write cycle
#define HwCHCTRL2_BSIZE_4						Hw7										// 1 Burst transfer consists of 4 read or write cycle
#define HwCHCTRL2_BSIZE_8						(Hw7+Hw6)								// 1 Burst transfer consists of 8 read or write cycle
#define HwCHCTRL2_WSIZE_8						HwZERO									// Each cycle read or write 8bit data
#define HwCHCTRL2_WSIZE_16						Hw4										// Each cycle read or write 16bit data
#define HwCHCTRL2_WSIZE_32						Hw5										// Each cycle read or write 32bit data
#define HwCHCTRL2_FLAG							Hw3										// W : Clears FLAG to 0, R : Represents that all hop of transfer are fulfilled
#define HwCHCTRL2_IEN_EN						Hw2										// At the same time the FLAG goes to 1, DMA interrupt request is generated
#define HwCHCTRL2_REP_EN						Hw1										// The DMA channel remains enabled. When another DMA request has occurred, the DMA channel start transfer data again with the same manner(type,address,increment,mask) as the latest transfer of that channel
#define HwCHCTRL2_EN_EN							Hw0										// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request
                                    		
#define	HwRPTCTRL2								*(volatile unsigned long *)0xF0040228	// R/W, Repeat Control Register
#define HwRPTCTRL2_DRI_LAST						Hw31									// DAM interrupt occur is  occurred at the last DMA Repeated DMA operation
#define HwRPTCTRL2_DEOT_LAST					Hw30									// EOT signal is occurred at the last Repeated DAM operation in HW(including Single) transfer Mode

typedef	volatile struct {
	unsigned	ST_SADR;
	unsigned	SPARAM;
	unsigned	_SPARAM;
	unsigned	C_SADR;
	unsigned	ST_DADR;
	unsigned	DPARAM;
	unsigned	_DPARAM;
	unsigned	C_DADR;
	unsigned	HCOUNT;
	unsigned	CHCTRL;
	unsigned	RPTCTRL;
} sHwDMA;

#define	HwCHCTRL_DMASEL_UART1_RX				Hw30									// Connected Hardware = UART Channel 1 Receiver
#define	HwCHCTRL_DMASEL_UART1_TX				Hw29									// Connected Hardware = UART Channel 1 Transmitter
#define	HwCHCTRL_DMASEL_UART0_RX				Hw28									// Connected Hardware = UART Channel 0 Receiver
#define	HwCHCTRL_DMASEL_UART0_TX				Hw27									// Connected Hardware = UART Channel 0 Transmitter
#define	HwCHCTRL_DMASEL_GSIO					Hw26									// Connected Hardware = GSIO Controller
#define	HwCHCTRL_DMASEL_I2C_CH1					Hw25									// Connected Hardware = I2C Controller Channel 1
#define	HwCHCTRL_DMASEL_DAIR					Hw24									// Connected Hardware = DAI Receiver
#define	HwCHCTRL_DMASEL_DAIT					Hw23									// Connected Hardware = DAI Transmitter
#define	HwCHCTRL_DMASEL_CDIF					Hw22									// Connected Hardware = CD I/F
#define	HwCHCTRL_DMASEL_SPDIF_UDATA				Hw21									// Connected Hardware = SPDIF User Data
#define	HwCHCTRL_DMASEL_SPDIF_PDATA				Hw20									// Connected Hardware = SPDIF Packet(Audio) Data
#define	HwCHCTRL_DMASEL_I2C_CH0					Hw19									// Connected Hardware = I2C Controller Channel 0
#define	HwCHCTRL_DMASEL_NFC						Hw18									// Connected Hardware = NAND Flash Controller
#define	HwCHCTRL_DMASEL_MSTICK					Hw17									// Connected Hardware = Memory Stick
#define	HwCHCTRL_DMASEL_SDMMC					Hw16									// Connected Hardware = SD/MMC
#define HwCHCTRL_CONT_C							Hw15									// DMA transfer begins from C_SADR / C_DADR address. It must be used after the former transfer has been executed, so that C_SADR and C_DADR contain a meaningful vlaue
#define HwCHCTRL_SWAP_EN						Hw14									// Swap Channel 1 Data
#define HwCHCTRL_SYNC_EN						Hw13									// Synchronize Hardware Request
#define HwCHCTRL_HRD_W							Hw12									// ACK/EOT signals are issued When DMA-Write Operation
#define HwCHCTRL_HRD_RD							HwZERO									// ACK/EOT signals are issued When DMA-Read Operation
#define HwCHCTRL_LOCK_EN						Hw11									// DMA transfer executed with lock transfer
#define HwCHCTRL_LOCK_ON						Hw11									// DMA transfer executed with lock transfer
#define HwCHCTRL_BST_NOARB						Hw10									// DMA transfer executed with no arbitration(burst operation)
#define HwCHCTRL_BST_BURST						Hw10									// DMA transfer executed with no arbitration(burst operation)
#define HwCHCTRL_BST_ARB						HwZERO									// DMA transfer executed with arbitration(burst operation)
#define HwCHCTRL_TYPE_SE						HwZERO									// SINGLE transfer with edge-triggered detection
#define HwCHCTRL_TYPE_SL						(Hw9+Hw8)								// SINGLE transfer with level-triggered detection
#define HwCHCTRL_TYPE_SINGL						(Hw9+Hw8)								// SINGLE transfer with level-triggered detection
#define HwCHCTRL_TYPE_HW						Hw8										// HW transfer
#define HwCHCTRL_TYPE_SW						Hw9										// SW transfer
#define HwCHCTRL_BSIZE_1						HwZERO									// 1 Burst transfer consists of 1 read or write cycle
#define HwCHCTRL_BSIZE_2						Hw6										// 1 Burst transfer consists of 2 read or write cycle
#define HwCHCTRL_BSIZE_4						Hw7										// 1 Burst transfer consists of 4 read or write cycle
#define HwCHCTRL_BSIZE_8						(Hw7+Hw6)								// 1 Burst transfer consists of 8 read or write cycle
#define HwCHCTRL_WSIZE_8						HwZERO									// Each cycle read or write 8bit data
#define HwCHCTRL_WSIZE_16						Hw4										// Each cycle read or write 16bit data
#define HwCHCTRL_WSIZE_32						Hw5										// Each cycle read or write 32bit data
#define HwCHCTRL_FLAG							Hw3										// W : Clears FLAG to 0, R : Represents that all hop of transfer are fulfilled
#define HwCHCTRL_IEN_EN							Hw2										// At the same time the FLAG goes to 1, DMA interrupt request is generated
#define HwCHCTRL_IEN_ON							Hw2										// At the same time the FLAG goes to 1, DMA interrupt request is generated
#define HwCHCTRL_REP_EN							Hw1										// The DMA channel remains enabled. When another DMA request has occurred, the DMA channel start transfer data again with the same manner(type,address,increment,mask) as the latest transfer of that channel
#define HwCHCTRL_EN_EN							Hw0										// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request
#define HwCHCTRL_EN_ON							Hw0										// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request

/***********************************************************************
*	I/O Bus Controller Register Define			(Base Addr = 0xF0050000)
************************************************************************/
#define	HwUSB20D								*(volatile unsigned long *)0xF0050000	// R/W, USB2.0 Device Configuration Register
#define	HwUSB20D_OSC_48							Hw16									// Oscillator Frequency - 48MHz
                                    			
#define	HwUSB11H								*(volatile unsigned long *)0xF0050004	// R/W, USB1.1 Host Configuration Register
#define	HwUSB11H_CNT							Hw2										//
                                    			
#define	HwIOBAPB								*(volatile unsigned long *)0xF0050008	// R/W, I/O Bus APB Configuration Register
#define	HwIOBAPB_IOBC							Hw0										// I/O Bus Control and Configuration Register
#define	HwIOBAPB_MS								Hw1										// Memory Stick Host Controller
#define	HwIOBAPB_I2C							Hw2										// I2C Interface Controller - Master Only
#define	HwIOBAPB_NFC							Hw3										// NAND Flash Interface Controller
#define	HwIOBAPB_CMIC							Hw4										// Camera Module Interface Controller
#define	HwIOBAPB_UART0							Hw5										// UART Channel 0 (16C550 Compatible and TCC76x Compatible)
#define	HwIOBAPB_UART1							Hw6										// UART Channel 1
#define	HwIOBAPB_GSIO							Hw7										// GSIO Controller and SPI Slave Controller
#define	HwIOBAPB_SDMMC							Hw8										// SD/MMC Host Controller
#define	HwIOBAPB_DAICDIF						Hw9										// DAI/CDIF Controller
#define	HwIOBAPB_GPIO							Hw10									// GPIO Controller
#define	HwIOBAPB_ECC							Hw11									// ECC Calculator
#define	HwIOBAPB_SPDIF							Hw12									// SPDIF Transmitter
                                    			
#define	HwSTORAGE								*(volatile unsigned long *)0xF005000C	// R/W, Storage Device Configuration Register
#define HwSTORAGE_ECCS_SBUS						HwZERO									// Storage Bus
#define HwSTORAGE_ECCS_IOBUS					Hw16									// I/O bus
#define HwSTORAGE_ECCS_GPMEM					Hw17									// General purpose SRAM or DTCM
#define HwSTORAGE_ECCS_MPDBUS					(Hw17+Hw16)								// Main processor data bus
#define HwSTORAGE_U0SEL_TCC76X					Hw8										// The UART ports of channel 0 is controlled by UART compatible for TCC76x
#define HwSTORAGE_MSB_BIG						Hw3										// The Endian for memory stick is big-endian byte aligned format
#define HwSTORAGE_MSBS_16						HwZERO									// The interface data bus width for memory stick is 16bits data bus
#define HwSTORAGE_MSBS_32						Hw1										// The interface data bus width for memory stick is 32bits data bus
#define HwSTORAGE_MSCS_PAD						Hw0										// The data synchronization clock is looped-back clock through PAD

/***********************************************************************
*	Memory Stick Host Controller Register Define(Base Addr = 0xF0051000)
************************************************************************/
#define	HwCOMMAND								*(volatile unsigned long *)0xF0051000	// R/W, Command register
#define	HwCOMMAND_TPC_RDL						Hw13									// Read Long Data Command
#define	HwCOMMAND_TPC_RDS						(Hw13+Hw12)								// Read Short Data Command
#define	HwCOMMAND_TPC_RDR						Hw14									// Read Register Command
#define	HwCOMMAND_TPC_GETINT					(Hw14+Hw13+Hw12)						// Get Interrupt Command
#define	HwCOMMAND_TPC_WRL						(Hw15+Hw14+Hw12)						// Write Long Data Command
#define	HwCOMMAND_TPC_WRS						(Hw15+Hw14)								// Write Short Data Command
#define	HwCOMMAND_TPC_WRR						(Hw15+Hw13+Hw12)						// Write Register Command
#define	HwCOMMAND_TPC_SRRA						Hw15									// Set R/W Register Address Command
#define	HwCOMMAND_TPC_SETCMD					(Hw15+Hw14+Hw13)						// Set Command
#define	HwCOMMAND_TPC_EXSETCMD					(Hw15+Hw12)								// Exit Set Command
#define	HwCOMMAND_DSL_EXT						Hw10									// External Memory - Not Supported
#define	HwCOMMAND_DSL_INT						~Hw10									// Internal FIFO - Only Supported
                                	    	
#define	HwDATA									*(volatile unsigned long *)0xF0051004	// R/W, Data register
                                	    	
#define	HwSTATUS								*(volatile unsigned long *)0xF0051008	// R/W, Status register
#define	HwSTATUS_DRQ							Hw14									// DMA Requested
#define	HwSTATUS_MSINT							Hw13									// Interrupt Activated
#define	HwSTATUS_RDY							Hw12									// Command Receive Enabled or Protocol Ended
#define	HwSTATUS_CRC							Hw9										// CRC Error Occurred
#define	HwSTATUS_TOE							Hw8										// Time-Out Error Occurred
#define	HwSTATUS_EMP							Hw5										// FIFO Empty
#define	HwSTATUS_FUL							Hw4										// FIFO Full
#define	HwSTATUS_CED							Hw3										// Command Ended
#define	HwSTATUS_ERR							Hw2										// Error Occurred, Cleared by writing command register
#define	HwSTATUS_BRQ							Hw1										// Data Buffer Requested, Cleared by writing command register
#define	HwSTATUS_CNK							Hw0										// Not Acknowledge, Cleared by writing command register
                                	    	
#define	HwSYSTEM								*(volatile unsigned long *)0xF005100C	// R/W, System Control register
#define	HwSYSTEM_RST_RST						Hw15									// Reset, Automatically cleared
#define	HwSYSTEM_RST_NORST						~Hw15									// Not Reset
#define	HwSYSTEM_SRAC_S							Hw14									// Serial Mode
#define	HwSYSTEM_SRAC_P							~Hw14									// Parallel Mode
#define	HwSYSTEM_INTEN_EN						Hw13									// Enabled
#define	HwSYSTEM_INTEN_DIS						~Hw13									// Disabled
#define	HwSYSTEM_NCRC_DIS						Hw12									// CRC Output Disabled
#define	HwSYSTEM_NCRC_EN						~Hw12									// CRC Output Enabled
#define	HwSYSTEM_ICLR_CLR						Hw11									// Interrupt Clear, Automatically clear
#define	HwSYSTEM_ICLR_NOTCLR					~Hw11									// Not clear
#define	HwSYSTEM_MSIEN_EN						Hw10									// Enabled
#define	HwSYSTEM_MSIEN_DIS						~Hw10									// Disabled
#define	HwSYSTEM_FCLR_CLR						Hw9										// FIFO clear, Automatically clear
#define	HwSYSTEM_FCLR_NOTCLR					~Hw9									// Not clear
#define	HwSYSTEM_FDIR_T							Hw8										// Transmit Mode
#define	HwSYSTEM_FDIR_R							~Hw8									// Receive Mode
#define	HwSYSTEM_DAM_S							Hw7										// Single Address Mode
#define	HwSYSTEM_DAM_D							~Hw7									// Dual Addrsss Mode
#define	HwSYSTEM_DRM_E							Hw6										// Edge Mode
#define	HwSYSTEM_DRM_L							~Hw6									// Level Mode
#define	HwSYSTEM_DRSL_GEN						Hw5										// Generate interrupt when a data request occurs, In software mode
#define	HwSYSTEM_DRSL_NOTGEN					~Hw5									// Do not generate interrupt when a data request occurs, In DAM mode
#define	HwSYSTEM_REI_RISE						Hw4										// Input data sampled by rising edge
#define	HwSYSTEM_REI_FALL						~Hw4									// Input data sampled by falling edge
#define	HwSYSTEM_REO_RISE						Hw3										// Output data generated at rising edge
#define	HwSYSTEM_REO_FALL						~Hw3									// Output data generated at falling edge

/************************************************************************
*	I2C Register Define							(Base Addr = 0xF0052000)
************************************************************************/
#define	HwI2CMCH0_PRES							*(volatile unsigned long *)0xF0052000	// R/W, I2C Clock Prescale Register
                                    		
#define	HwI2CMCH0_CTRL							*(volatile unsigned long *)0xF0052004	// R/W, I2C Control Register
#define	HwI2CMCH0_CTRL_EN_ON					Hw7										// Enabled
#define	HwI2CMCH0_CTRL_EN_OFF					~Hw7									// Disabled
#define	HwI2CMCH0_CTRL_IEN_ON					Hw6										// Enabled
#define	HwI2CMCH0_CTRL_IEN_OFF					~Hw6									// Disabled
#define	HwI2CMCH0_CTRL_MOD_16					Hw5										// 16bit Mode
#define	HwI2CMCH0_CTRL_MOD_8					~Hw5									// 8bit Mode
                                    		
#define	HwI2CMCH0_TXR							*(volatile unsigned long *)0xF0052008	// W, I2C Transmit Register
                                    		
#define	HwI2CMCH0_CMD							*(volatile unsigned long *)0xF005200C	// W, I2C Command Register
#define	HwI2CMCH0_CMD_STA_EN					Hw7 									// Start Condition Generation Enabled
#define	HwI2CMCH0_CMD_STA_DIS					~Hw7 									// Start Condition Generation Disabled
#define	HwI2CMCH0_CMD_STO_EN					Hw6 									// Stop Condition Generation Enabled
#define	HwI2CMCH0_CMD_STO_DIS					~Hw6 									// Stop Condition Generation Disabled
#define	HwI2CMCH0_CMD_RD_EN						Hw5 									// Read From Slave Enabled
#define	HwI2CMCH0_CMD_RD_DIS					~Hw5 									// Read From Slave Disabled
#define	HwI2CMCH0_CMD_WR_EN						Hw4 									// Wrtie to Slabe Enabled
#define	HwI2CMCH0_CMD_WR_DIS					~Hw4 									// Wrtie to Slabe Disabled
#define	HwI2CMCH0_CMD_ACK_EN					Hw3 									// Sent ACK Enabled
#define	HwI2CMCH0_CMD_ACK_DIS					~Hw3 									// Sent ACK Disalbed
#define	HwI2CMCH0_CMD_IACK_CLR					Hw0 									// Clear a pending interrupt
                                    		
#define	HwI2CMCH0_RXR							*(volatile unsigned long *)0xF0052010	// R, I2C Receive Register
                                    		
#define	HwI2CMCH0_SR							*(volatile unsigned long *)0xF0052014	// R, I2C Status Register
#define	HwI2CMCH0_SR_RxACK						Hw7										// 1:Acknowledge received, 0:No Acknowledge received
#define	HwI2CMCH0_SR_BUSY						Hw6										// 1:Start signal detected, 0:Stop signal detected
#define	HwI2CMCH0_SR_AL							Hw5										// 1:The core lost arbitration, 0:The core don't lost arbitration
#define	HwI2CMCH0_SR_TIP						Hw1										// 1:Transfer Complete, 0:Transferring Data
#define	HwI2CMCH0_SR_IF							Hw0										// 1:Interrupt is pending
                                    		
#define	HwI2CMCH0_TR							*(volatile unsigned long *)0xF0052018	// Timing Register
#define	HwI2CMCH0_TR_CKSEL						Hw5										// Clock Source Select
                                			
#define	HwI2CMCH1_PRES							*(volatile unsigned long *)0xF0052040	// R/W, I2C Clock Prescale Register
                                    		
#define	HwI2CMCH1_CTRL							*(volatile unsigned long *)0xF0052044	// R/W, I2C Control Register
#define	HwI2CMCH1_CTRL_EN_ON					Hw7										// Enabled
#define	HwI2CMCH1_CTRL_EN_OFF					~Hw7									// Disabled
#define	HwI2CMCH1_CTRL_IEN_ON					Hw6										// Enabled
#define	HwI2CMCH1_CTRL_IEN_OFF					~Hw6									// Disabled
#define	HwI2CMCH1_CTRL_MOD_16					Hw5										// 16bit Mode
#define	HwI2CMCH1_CTRL_MOD_8					~Hw5									// 8bit Mode
                                    		
#define	HwI2CMCH1_TXR							*(volatile unsigned long *)0xF0052048	// W, I2C Transmit Register
                                    		
#define	HwI2CMCH1_CMD							*(volatile unsigned long *)0xF005204C	// W, I2C Command Register
#define	HwI2CMCH1_CMD_STA_EN					Hw7 									// Start Condition Generation Enabled
#define	HwI2CMCH1_CMD_STA_DIS					~Hw7 									// Start Condition Generation Disabled
#define	HwI2CMCH1_CMD_STO_EN					Hw6 									// Stop Condition Generation Enabled
#define	HwI2CMCH1_CMD_STO_DIS					~Hw6 									// Stop Condition Generation Disabled
#define	HwI2CMCH1_CMD_RD_EN						Hw5 									// Read From Slave Enabled
#define	HwI2CMCH1_CMD_RD_DIS					~Hw5 									// Read From Slave Disabled
#define	HwI2CMCH1_CMD_WR_EN						Hw4 									// Wrtie to Slabe Enabled
#define	HwI2CMCH1_CMD_WR_DIS					~Hw4 									// Wrtie to Slabe Disabled
#define	HwI2CMCH1_CMD_ACK_EN					Hw3 									// Sent ACK Enabled
#define	HwI2CMCH1_CMD_ACK_DIS					~Hw3 									// Sent ACK Disalbed
#define	HwI2CMCH1_CMD_IACK_CLR					Hw0 									// Clear a pending interrupt
                                    		
#define	HwI2CMCH1_RXR							*(volatile unsigned long *)0xF0052050	// R, I2C Receive Register
                                    		
#define	HwI2CMCH1_SR							*(volatile unsigned long *)0xF0052054	// R, I2C Status Register
#define	HwI2CMCH1_SR_RxACK						Hw7										// 1:Acknowledge received, 0:No Acknowledge received
#define	HwI2CMCH1_SR_BUSY						Hw6										// 1:Start signal detected, 0:Stop signal detected
#define	HwI2CMCH1_SR_AL							Hw5										// 1:The core lost arbitration, 0:The core don't lost arbitration
#define	HwI2CMCH1_SR_TIP						Hw1										// 1:Transfer Complete, 0:Transferring Data
#define	HwI2CMCH1_SR_IF							Hw0										// 1:Interrupt is pending
                                    		
#define	HwI2CMCH1_TR							*(volatile unsigned long *)0xF0052058	// Timing Register
#define	HwI2CMCH1_TR_CKSEL						Hw5										// Clock Source Select
                                    		
#define	HwI2CS_DPORT							*(volatile unsigned long *)0xF0052080	// Data Port
                                    		
#define	HwI2CS_CTL								*(volatile unsigned long *)0xF0052084	// Control Register
#define	HwI2CS_CTL_SLV_2M						HwZERO									// 2 master operation
#define	HwI2CS_CTL_SLV_1M1S						Hw30									// 1 master / 1 slave
#define	HwI2CS_CTL_RCLR							Hw5										// clear interrupt status at read cycle
#define	HwI2CS_CTL_WS							Hw4										// wait status control by SCL stretching
#define	HwI2CS_CTL_SDA							Hw3										//
#define	HwI2CS_CTL_CLR							Hw2										// Clear FIFO
#define	HwI2CS_CTL_EN							Hw0										// Enable for this slave core
                                    		
#define	HwI2CS_ADDR								*(volatile unsigned long *)0xF0052088	// Address Register
                                    		
#define	HwI2CS_INT								*(volatile unsigned long *)0xF005208C	// Interrupt Register
#define	HwI2CS_INT_STAT_R_BYTE					Hw27									//
#define	HwI2CS_INT_STAT_W_BYTE					Hw26									//
#define	HwI2CS_INT_STAT_R_BUFF					Hw25									//
#define	HwI2CS_INT_STAT_W_BUFF					Hw24									//
#define	HwI2CS_INT_STAT_TXUR					Hw23									//
#define	HwI2CS_INT_STAT_RXOR					Hw22									//
#define	HwI2CS_INT_STAT_TXB						Hw21									//
#define	HwI2CS_INT_STAT_RXF						Hw20									//
#define	HwI2CS_INT_STAT_TXE						Hw19									//
#define	HwI2CS_INT_STAT_RXNE					Hw18									//
#define	HwI2CS_INT_STAT_TXL						Hw17									//
#define	HwI2CS_INT_STAT_RXL						Hw16									//
#define	HwI2CS_INT_EN_R_BYTE					Hw11									//
#define	HwI2CS_INT_EN_W_BYTE					Hw10									//
#define	HwI2CS_INT_EN_R_BUFF					Hw9										//
#define	HwI2CS_INT_EN_W_BUFF					Hw8										//
#define	HwI2CS_INT_EN_TXUR						Hw7										//
#define	HwI2CS_INT_EN_RXOR						Hw6										//
#define	HwI2CS_INT_EN_TXB						Hw5										//
#define	HwI2CS_INT_EN_RXF						Hw4										//
#define	HwI2CS_INT_EN_TXE						Hw3										//
#define	HwI2CS_INT_EN_RXNE						Hw2										//
#define	HwI2CS_INT_EN_TXL						Hw1										//
#define	HwI2CS_INT_EN_RXL						Hw0										//
                                    		
#define	HwI2CS_STAT								*(volatile unsigned long *)0xF0052090	// Status Register
#define	HwI2CS_STAT_DDIR						Hw23									// Data Direction
                                    		
#define	HwI2CS_MBF								*(volatile unsigned long *)0xF005209C	// Buffer Valid Flag Register
                                    		
#define	HwI2CS_MB0								*(volatile unsigned long *)0xF00520A0	// Data Buffer 0
                                    		
#define	HwI2CS_MB1								*(volatile unsigned long *)0xF00520A4	// Data Buffer 1

/***********************************************************************
*	 NAND Flash Controller Register Define		(Base Addr = 0xF0053000)
************************************************************************/
typedef	volatile struct {
	unsigned	CMD;
	unsigned	LADR;
	unsigned	BADR;
	unsigned	SADR;
	union {
		unsigned char	D8;
		unsigned short	D16;
		unsigned int	D32;
	} WDATA;
	unsigned	uDummy[3+8];
	union {
		unsigned char	D8;
		unsigned short	D16;
		unsigned int	D32;
	} SDATA;
} sHwND;

#define	HwNFC_CMD								*(volatile unsigned long *)0xF0053000	// W, Nand Flash Command Register
                                    		
#define	HwNFC_LADDR								*(volatile unsigned long *)0xF0053004	// W, Nand Flash Linear Address Register
                                    		
#define	HwNFC_BADDR								*(volatile unsigned long *)0xF0053008	// W, Nand Flash Block Address Register
                                    		
#define	HwNFC_SADDR								*(volatile unsigned long *)0xF005300C	// W, Nand Flash Signal Address Register
                                    		
#define	HwNFC_WDATA								*(volatile unsigned long *)0xF0053010	// R/W, Nand Flash Word Data Register
                                    		
#define	HwNFC_LDATA								*(volatile unsigned long *)0xF0053020	// R/W, Nand Flash Linear Data Register
                                    		
#define	HwNFC_SDATA								*(volatile unsigned long *)0xF0053040	// R/W, Nand Flash Single Data Register
                                    		
#define	HwNFC_CTRL								*(volatile unsigned long *)0xF0053050	// R/W, Nand Flash Control Register
#define	HwNFC_CTRL_RDYIEN_EN					Hw31									// Nand Flash Ready Interrupt Enable
#define	HwNFC_CTRL_RDYIEN_DIS					~Hw31									// Nand Flash Ready Interrupt Disable
#define	HwNFC_CTRL_PROGIEN_EN					Hw30									// Nand Flash Program Interrupt Enable 
#define	HwNFC_CTRL_PROGIEN_DIS					~Hw30									// Nand Flash Program Interrupt Disable
#define	HwNFC_CTRL_READIEN_EN					Hw29									// Nand Flash Read Interrupt Enable
#define	HwNFC_CTRL_READIEN_DIS					~Hw29									// Nand Flash Read Interrupt Disable
#define	HwNFC_CTRL_DEN_EN						Hw28									// Nand Flash DMA Request Enable
#define	HwNFC_CTRL_DEN_DIS						~Hw28									// Nand Flash DMA Request Disable
#define	HwNFC_CTRL_FS_RDY						Hw27									// FIFO status is Ready to write and read in FIFO
#define	HwNFC_CTRL_FS_BUSY						~Hw27									// FIFO status is Busy to write and read in FIFO
#define	HwNFC_CTRL_BW_16						Hw26									// Bus width = 8bit
#define	HwNFC_CTRL_BW_8							HwZERO									// Bus width = 16bit
#define	HwNFC_CTRL_AR_EN						Hw25									// Auto read start Enable
#define	HwNFC_CTRL_AR_DIS						~Hw25									// Auto read start Disable
#define	HwNFC_CTRL_CEN_CONT						Hw24									// Nand Flash CS is generated by Controller
#define	HwNFC_CTRL_CEN_LOW						~Hw24									// Nand Flash CS is Low
#define	HwNFC_CTRL_C0E_DIS						Hw23									// Nand Flash nCS0 Disable
#define	HwNFC_CTRL_CFG_nCS0						Hw23
#define	HwNFC_CTRL_CFG_nCS1						Hw22
#define	HwNFC_CTRL_C1E_DIS						Hw22									// Nand Flash nCS1 Disable
#define	HwNFC_CTRL_CFG_NOACT					(Hw23+Hw22)
#define	HwNFC_CTRL_STA_RDY						Hw21									// Nand Flash Controller is Ready
#define	HwNFC_CTRL_STA_BUSY						~Hw21									// Nand Flash Controller is Busy
#define	HwNFC_CTRL_RDY_RDY						Hw20									// External Nand Flash Controller is Ready
#define	HwNFC_CTRL_RDY_BUSY						~Hw20									// External Nand Flash Controller is Busy
#define	HwNFC_CTRL_BSIZE_1						HwZERO									// 1Read/Write
#define	HwNFC_CTRL_BSIZE_2						Hw18									// 2Read/Write
#define	HwNFC_CTRL_BSIZE_4						Hw19									// 4Read/Write
#define	HwNFC_CTRL_BSIZE_8						(Hw19+Hw18)								// 8Read/Write
#define	HwNFC_CTRL_PSIZE_256					HwZERO									// 1 Page = 256 Half-Word
#define	HwNFC_CTRL_PSIZE_512					Hw16									// 1 Page = 512 Byte
#define	HwNFC_CTRL_PSIZE_1024					Hw17									// 1 Page = 1024 Half-Word
#define	HwNFC_CTRL_PSIZE_2048					(Hw17+Hw16)								// 1 Page = 2048 Byte
#define	HwNFC_CTRL_MASK_EN						Hw15									// Address/Command Mask Enable
#define	HwNFC_CTRL_CADDR						Hw12									// Number of Address Cycle
                                    		
#define	HwNFC_PSTART							*(volatile unsigned long *)0xF0053054	// W, Nand Flash Program Start Register
                                    		
#define	HwNFC_RSTART							*(volatile unsigned long *)0xF0053058	// W, Nand Flash Read Start Register
                                    		
#define	HwNFC_DSIZE								*(volatile unsigned long *)0xF005305C	// R/W, Nand Flash Data Size Register
                                    		
#define	HwNFC_IREQ								*(volatile unsigned long *)0xF0053060	// R/W, Nand Flash Interrupt Request Register
#define	HwNFC_IREQ_FLAG2						Hw6										// R:The Rising edge of Ready Signal is occurred, W:Ready Flag Clear
#define	HwNFC_IREQ_FLAG1						Hw5										// R:Program data transfer is finished, W:Program Flag Clear
#define	HwNFC_IREQ_FLAG0						Hw4										// R:Read data transfer is finished, W:Read Flag Clear
#define	HwNFC_IREQ_IRQ2							Hw2										// Ready Interrupt
#define	HwNFC_IREQ_IRQ1							Hw1										// Program Interrupt
#define	HwNFC_IREQ_IRQ0							Hw0										// Reading Interrupt
                                    		
#define	HwNFC_RST								*(volatile unsigned long *)0xF0053064	// W, Nand Flash Controller Reset Register

/***********************************************************************
*	UART0 Controller Register Define			(Base Addr = 0xF0055000)
************************************************************************/
#define	HwUART0_RBR								*(volatile unsigned long *)0xF0055000	// R, Receiver Buffer Register (DLAB = 0)
                                			
#define	HwUART0_THR								*(volatile unsigned long *)0xF0055000	// W, Transmitter Holding Register (DLAB = 0)
                                			
#define	HwUART0_DLL								*(volatile unsigned long *)0xF0055000	// R/W, Divisor Latch Register (DLAB = 1)
                                			
#define	HwUART0_DLM								*(volatile unsigned long *)0xF0055004	// R/W, Divisor Latch Register (DLAB = 1)
                                			
#define	HwUART0_IER								*(volatile unsigned long *)0xF0055004	// R/W, Interrupt Enable Register (DLAB = 0)
#define	HwUART0_IER_EMSI_EN						Hw3										// Enable Modem status interrupt
#define	HwUART0_IER_EMSI_DIS					~Hw3									// Disable Modem status interrupt
#define	HwUART0_IER_ELSI_EN						Hw2										// Enable receiver line status interrupt
#define	HwUART0_IER_ELSI_DIS					~Hw2									// Disable receiver line status interrupt
#define	HwUART0_IER_ETXI_EN						Hw1										// Enable transmitter holding register empty interrupt
#define	HwUART0_IER_ETXI_DIS					~Hw1									// Disable transmitter holding register empty interrupt
#define	HwUART0_IER_ERXI_EN						Hw0										// Enable received data available interrupt
#define	HwUART0_IER_ERXI_DIS					~Hw0									// Disable received data available interrupt
                                			
#define	HwUART0_IIR								*(volatile unsigned long *)0xF0055008	// R, Interrupt Ident. Register (DLAB = 0)
#define	HwUART0_IIR_IPF							Hw0										// 1:Interrupt has not generated, 0:Interrupt pending
                                			
#define	HwUART0_FCR								*(volatile unsigned long *)0xF0055008	// W, FIFO Control Register (DLAB = 1)
#define	HwUART0_FCR_RXT_1						~(Hw7+Hw6)								// RX FIFO Trigger Level 1byte
#define	HwUART0_FCR_RXT_4						Hw6										// RX FIFO Trigger Level 4bytes
#define	HwUART0_FCR_RXT_8						Hw7										// RX FIFO Trigger Level 8bytes
#define	HwUART0_FCR_RXT_14						(Hw7+Hw6)								// RX FIFO Trigger Level 16bytes
#define	HwUART0_FCR_DMS_EN						Hw3										// DMA Mode Enabled
#define	HwUART0_FCR_DMS_DIS						~Hw3									// DMA Mode Disabled
#define	HwUART0_FCR_TXFR_EN						Hw2										// Reset TX FIFO counter and FIFO Data
#define	HwUART0_FCR_TXFR_DIS					~Hw2									//
#define	HwUART0_FCR_RXFR_EN						Hw1										// Reset RX FIFO counter and FIFO Data
#define	HwUART0_FCR_RXFR_DIS					~Hw1									//
#define	HwUART0_FCR_FE_EN						Hw0										// Enable TX and RX FIFOs
#define	HwUART0_FCR_FE_DIS						~Hw0									// Disable TX and RX FIFOs
                                			
#define	HwUART0_LCR								*(volatile unsigned long *)0xF005500C	// R/W, Line Control Register
#define	HwUART0_LCR_DLAB_ON						Hw7										// Access the divisor latches of the baud generator
#define	HwUART0_LCR_DLAB_OFF					~Hw7									// Access the receiver buff, the transmitter holding register, or the interrupt enable register
#define	HwUART0_LCR_SB_ON						Hw6										// The serial output is forced to the spacing (logic 0) state
#define	HwUART0_LCR_SB_OFF						~Hw6									// Disable the break
#define	HwUART0_LCR_SP_ON						Hw5										// When bits 3, 4 and 5 are logic 1 the parity bits is transmitted and checked as a logic 0. If bits 3 and 5 are 1 and bit 4 is a logic 0 then the parity bit is transmitted and checked as a logic 1
#define	HwUART0_LCR_SP_OFF						~Hw5									// Disable stick parity
#define	HwUART0_LCR_EPS_EVEN					Hw4										// Generate or check even parity
#define	HwUART0_LCR_EPS_ODD						~Hw4									// Generate or check odd parity
#define	HwUART0_LCR_PEN_ON						Hw3										// A parity bit is generated (TX) or Checked (RX)
#define	HwUART0_LCR_PEN_OFF						~Hw3									// Disabled
#define	HwUART0_LCR_STB_ONE						Hw2										// One stop bit is generated in the transmitted data
#define	HwUART0_LCR_STB_WLS						~Hw2									// When 5bit word length is selected, one and a half stop bits are generated. When either a 6-, 7-, or 8-bit word length is selected, two stop bits are generated.
#define	HwUART0_LCR_WLS_5						~(Hw1+Hw0)								// 5 bits word length
#define	HwUART0_LCR_WLS_6						Hw0										// 6 bits word length
#define	HwUART0_LCR_WLS_7						Hw1										// 7 bits word length
#define	HwUART0_LCR_WLS_8						(Hw1+Hw0)								// 8 bits word length
                                			
#define	HwUART0_MCR								*(volatile unsigned long *)0xF0055010	// R/W, MODEM Control Register
#define	HwUART0_MCR_LOOP_ON						Hw4										// Loop Back Enable
#define	HwUART0_MCR_LOOP_OFF					~Hw4									// Loop Back Disable
#define	HwUART0_MCR_RTS							Hw1										// This bit informs the external modem that the uart is ready to exchange data
                                			
#define	HwUART0_LSR								*(volatile unsigned long *)0xF0055014	// R, Line Status Register
#define	HwUART0_LSR_ERF_FIFO					Hw7										// In the FIFO mode this bit is set when there is at least one parity error, framing error or break indication in the FIFO
#define	HwUART0_LSR_ERF_16450					~Hw7									// In the 16450 mode
#define	HwUART0_LSR_TEMT_ON						Hw6										// Transmitter holding register and the transmitter shift register are both empty
#define	HwUART0_LSR_TEMT_OFF					~Hw6									//
#define	HwUART0_LSR_THRE_ON						Hw5										// UART is ready to accept a new char for transmission
#define	HwUART0_LSR_THRE_OFF					~Hw5									//
#define	HwUART0_LSR_BI_ON						Hw4										// The received data input is held in the spacing (logic 0) state for longer than a full word transmission time
#define	HwUART0_LSR_BI_OFF						~Hw4									//
#define	HwUART0_LSR_FE_ON						Hw3										// The received character did not have a valid stop bit
#define	HwUART0_LSR_FE_OFF						~Hw3									//
#define	HwUART0_LSR_PE_ON						Hw2										// The received data character does not have the correct even or odd parity
#define	HwUART0_LSR_PE_OFF						~Hw2									//
#define	HwUART0_LSR_OE_ON						Hw1										// The receiver buffer register was not read by the CPU before the next character was transferred into the receiver buffer register
#define	HwUART0_LSR_OE_OFF						~Hw1									//
#define	HwUART0_LSR_DR_ON						Hw0										// The receiver data ready
#define	HwUART0_LSR_DR_OFF						~Hw0									//
                                			
#define	HwUART0_MSR								*(volatile unsigned long *)0xF0055018	// R, MODEM Status Register
#define HwUART0_MSR_CTS							Hw4										// This bit is the complement of the Claer to Send input
#define	HwUART0_MSR_DCTS						Hw0										// This bit is the Delta Clear to Send indicator
                                			
#define	HwUART0_SCR								*(volatile unsigned long *)0xF005501C	// R/W, Scratch Register
																						// This 8bit Read/Write Register does not control the UART in anyway. It is intended as a scratch pad register to be used by the programmer to hold data temporarily

/***********************************************************************
*	UART2 Controller Register Define			(Base Addr = 0xF0055800)
************************************************************************/
#define	HwUART2_UTRXD							*(volatile unsigned long *)0xF0055800	// R, Receiver Buffer Register
                                		    	
#define	HwUART2_UTTXD							*(volatile unsigned long *)0xF0055800	// W, Transmitter Holding Register
                                		    	
#define	HwUART2_UTDL							*(volatile unsigned long *)0xF0055804	// W, Divisor Latch Register
                                		    	
#define	HwUART2_UTIR							*(volatile unsigned long *)0xF0055808	// R/W, Interrupt Register
#define	HwUART2_UTIR_ERS_EN						Hw10									// Receiver Line Status interrupt is enabled
#define	HwUART2_UTIR_ERS_DIS					~Hw10									// Receiver Line Status interrupt is disabled
#define	HwUART2_UTIR_ETX_EN						Hw9										// Transmitter Holding Register Empty interrupt is enabled
#define	HwUART2_UTIR_ETX_DIS					~Hw9									// Transmitter Holding Register Empty interrupt is disabled
#define	HwUART2_UTIR_ERX_EN						Hw8										// Receiver Data Available interrupt is enabled
#define	HwUART2_UTIR_ERX_DIS					~Hw8									// Receiver Data Available interrupt is disabled
#define	HwUART2_UTIR_FRS_CHG					Hw6										// Indicated that Receiver Line Status has changed
#define	HwUART2_UTIR_FRS_NOTCHG					~Hw6									// Indicated that Receiver Line Status has not changed
#define	HwUART2_UTIR_FTX_GEN					Hw5										// Interrupt has generated, but not cleared
#define	HwUART2_UTIR_FTX_NOTGEN					~Hw5									// Interrupt has not generated
#define	HwUART2_UTIR_FRX_GEN					Hw4										// Interrupt has generated, but not cleared
#define	HwUART2_UTIR_FRX_NOTGEN					~Hw4									// Interrupt has not generated
#define	HwUART2_UTIR_QRS_GEN					Hw2										// Indicated that Receiver Line Status interrupt has generated
#define	HwUART2_UTIR_QRS_NOTGEN					~Hw2									// Indicated that Receiver Line Status interrupt has not generated
#define	HwUART2_UTIR_QTX_GEN					Hw1										// Transmitter Holding Register Empty interrupt has generated
#define	HwUART2_UTIR_QTX_NOTGEN					~Hw1									// Transmitter Holding Register Empty interrupt has not generated
#define	HwUART2_UTIR_QRX_GEN					Hw0										// Indicated that Receiver Data Available interrupt has generated
#define	HwUART2_UTIR_QRX_NOTGEN					~Hw0									// Indicated that Receiver Data Available interrupt has not generated
                                		    	
#define	HwUART2_UTCR							*(volatile unsigned long *)0xF005580C	// R/W, UART Control Register
#define	HwUART2_UTCR_NO_NOTCHK					Hw9										// Don't check the pulse width of start bit (test or boot mode only)
#define	HwUART2_UTCR_NO_CHK						~Hw9									// Check if the pulse width of start bit is more than 0.5 bit duration of baud rate
#define	HwUART2_UTCR_BK_THR						Hw8										// Bit '0' is transmitted regardless of THR
#define	HwUART2_UTCR_BK_NORMAL					~Hw8									// Normal operation
#define	HwUART2_UTCR_TF_CLR						Hw7										// The transmitter FIFO is cleared
#define	HwUART2_UTCR_TF_NOTCLR					~Hw7									//
#define	HwUART2_UTCR_RF_CLR						Hw6										// The receiver FIFO is cleared
#define	HwUART2_UTCR_RF_NOTCLR					~Hw6									//
#define	HwUART2_UTCR_FIFO_1						HwZERO									// 1byte FIFO
#define	HwUART2_UTCR_FIFO_2						Hw4										// 2byte FIFO
#define	HwUART2_UTCR_FIFO_4						Hw5										// 4byte FIFO
#define	HwUART2_UTCR_FIFO_7						(Hw5+Hw4)								// 7byte FIFO
#define	HwUART2_UTCR_PR_EVEN					HwZERO									// Even parity
#define	HwUART2_UTCR_PR_ODD						Hw2										// Odd parity
#define	HwUART2_UTCR_PR_DIS						Hw3										// Parity is disabled
#define	HwUART2_UTCR_ST_2						Hw1										// 2 Stop bit
#define	HwUART2_UTCR_ST_1						~Hw1									// 1 Stop bit
                                		    	
#define	HwUART2_UTLSR							*(volatile unsigned long *)0xF0055810	// R, Status Register
#define	HwUART2_UTLSR_TE_NOSTR					Hw4										// No data is stored in transmitter FIFO
#define	HwUART2_UTLSR_TE_STR					~Hw4									// At least 1 byte is stored in transmitter FIFO
#define	HwUART2_UTLSR_TF_NOSTR					Hw3										// No data is stored in transmitter FIFO
#define	HwUART2_UTLSR_TF_STR					~Hw3									// At least 1 byte is stored in transmitter FIFO
#define	HwUART2_UTLSR_FE_ERR					Hw2										// The received data in the FIFO don't have valid stop bit
#define	HwUART2_UTLSR_FE_GOOD					~Hw2									// Stop bit is received and correct
#define	HwUART2_UTLSR_PE_ERR					Hw1										// The received data in the FIFO don't have valid parity bit
#define	HwUART2_UTLSR_PE_GOOD					~Hw1									// Parity bit is received and correct
#define	HwUART2_UTLSR_RA_RECV					Hw0										// At least 1 received data is stored in the FIFO
#define	HwUART2_UTLSR_RA_NORECV					~Hw0									// No data has been received
                                            	
#define	HwUART2_IrDACFG1						*(volatile unsigned long *)0xF0055814	// R/W, IrDA Configuration Register1
#define	HwUART2_IrDACFG1_EN_ON					Hw15									// IrDA TX is enable
#define	HwUART2_IrDACFG1_EN_OFF					~Hw15									// IrDA TX is disable, UART mode is used
#define	HwUART2_IrDACFG1_P1_BASE				Hw14									// Pulse width is proportional to UART base clock speed
#define	HwUART2_IrDACFG1_P1_BAUD				~Hw14									// Pulse width is proportional to selected baud used
#define	HwUART2_IrDACFG1_POL_LOW				Hw13									// TX '0' data is converted to level low pulse
#define	HwUART2_IrDACFG1_POL_HIGH				~Hw13									// TX '0' data is converted to level high pulse
#define	HwUART2_IrDACFG1_LB_RX					Hw12									// Transmitted data is feedback to RX port
#define	HwUART2_IrDACFG1_LB_NORMAL				~Hw12									// Normal operation
                                            	
#define	HwUART2_IrDACFG2						*(volatile unsigned long *)0xF0055818	// R/W, IrDA Configuration Register2
#define	HwUART2_IrDACFG2_EN_ON					Hw15									// IrDA RX is enable
#define	HwUART2_IrDACFG2_EN_OFF					~Hw15									// IrDA RX is disable, UART mode is used
#define	HwUART2_IrDACFG2_P1_BASE				Hw14									// Received Pulse width is proportional to UART base clock speed
#define	HwUART2_IrDACFG2_P1_BAUD				~Hw14									// Received Pulse width is proportional to selected baud used
#define	HwUART2_IrDACFG2_POL_LOW				Hw13									// The polarity of received data is inverted
#define	HwUART2_IrDACFG2_POL_HIGH				~Hw13									// The polarity of received data is not inverted

/***********************************************************************
*	UART1 Controller Register Define			(Base Addr = 0xF0056000)
************************************************************************/
#define	HwUART1_RBR								*(volatile unsigned long *)0xF0056000	// R, Receiver Buffer Register (DLAB = 0)
                                			
#define	HwUART1_THR								*(volatile unsigned long *)0xF0056000	// W, Transmitter Holding Register (DLAB = 0)
                                			
#define	HwUART1_DLL								*(volatile unsigned long *)0xF0056000	// R/W, Divisor Latch Register (DLAB = 1)
                                			
#define	HwUART1_DLM								*(volatile unsigned long *)0xF0056004	// R/W, Divisor Latch Register (DLAB = 1)
                                			
#define	HwUART1_IER								*(volatile unsigned long *)0xF0056004	// R/W, Interrupt Enable Register (DLAB = 0)
#define	HwUART1_IER_EMSI_EN						Hw3										// Enable Modem status interrupt
#define	HwUART1_IER_EMSI_DIS					~Hw3									// Disable Modem status interrupt
#define	HwUART1_IER_ELSI_EN						Hw2										// Enable receiver line status interrupt
#define	HwUART1_IER_ELSI_DIS					~Hw2									// Disable receiver line status interrupt
#define	HwUART1_IER_ETXI_EN						Hw1										// Enable transmitter holding register empty interrupt
#define	HwUART1_IER_ETXI_DIS					~Hw1									// Disable transmitter holding register empty interrupt
#define	HwUART1_IER_ERXI_EN						Hw0										// Enable received data available interrupt
#define	HwUART1_IER_ERXI_DIS					~Hw0									// Disable received data available interrupt
                                			
#define	HwUART1_IIR								*(volatile unsigned long *)0xF0056008	// R, Interrupt Ident. Register (DLAB = 0)
#define	HwUART1_IIR_IPF							Hw0										// 1:Interrupt has not generated, 0:Interrupt pending
                                			
#define	HwUART1_FCR								*(volatile unsigned long *)0xF0056008	// W, FIFO Control Register (DLAB = 1)
#define	HwUART1_FCR_RXT_1						~(Hw7+Hw6)								// RX FIFO Trigger Level 1byte
#define	HwUART1_FCR_RXT_4						Hw6										// RX FIFO Trigger Level 4bytes
#define	HwUART1_FCR_RXT_8						Hw7										// RX FIFO Trigger Level 8bytes
#define	HwUART1_FCR_RXT_14						(Hw7+Hw6)								// RX FIFO Trigger Level 16bytes
#define	HwUART1_FCR_DMS_EN						Hw3										// DMA Mode Enabled
#define	HwUART1_FCR_DMS_DIS						~Hw3									// DMA Mode Disabled
#define	HwUART1_FCR_TXFR_EN						Hw2										// Reset TX FIFO counter and FIFO Data
#define	HwUART1_FCR_TXFR_DIS					~Hw2									//
#define	HwUART1_FCR_RXFR_EN						Hw1										// Reset RX FIFO counter and FIFO Data
#define	HwUART1_FCR_RXFR_DIS					~Hw1									//
#define	HwUART1_FCR_FE_EN						Hw0										// Enable TX and RX FIFOs
#define	HwUART1_FCR_FE_DIS						~Hw0									// Disable TX and RX FIFOs
                                			
#define	HwUART1_LCR								*(volatile unsigned long *)0xF005600C	// R/W, Line Control Register
#define	HwUART1_LCR_DLAB_ON						Hw7										// Access the divisor latches of the baud generator
#define	HwUART1_LCR_DLAB_OFF					~Hw7									// Access the receiver buff, the transmitter holding register, or the interrupt enable register
#define	HwUART1_LCR_SB_ON						Hw6										// The serial output is forced to the spacing (logic 0) state
#define	HwUART1_LCR_SB_OFF						~Hw6									// Disable the break
#define	HwUART1_LCR_SP_ON						Hw5										// When bits 3, 4 and 5 are logic 1 the parity bits is transmitted and checked as a logic 0. If bits 3 and 5 are 1 and bit 4 is a logic 0 then the parity bit is transmitted and checked as a logic 1
#define	HwUART1_LCR_SP_OFF						~Hw5									// Disable stick parity
#define	HwUART1_LCR_EPS_EVEN					Hw4										// Generate or check even parity
#define	HwUART1_LCR_EPS_ODD						~Hw4									// Generate or check odd parity
#define	HwUART1_LCR_PEN_ON						Hw3										// A parity bit is generated (TX) or Checked (RX)
#define	HwUART1_LCR_PEN_OFF						~Hw3									// Disabled
#define	HwUART1_LCR_STB_ONE						Hw2										// One stop bit is generated in the transmitted data
#define	HwUART1_LCR_STB_WLS						~Hw2									// When 5bit word length is selected, one and a half stop bits are generated. When either a 6-, 7-, or 8-bit word length is selected, two stop bits are generated.
#define	HwUART1_LCR_WLS_5						~(Hw1+Hw0)								// 5 bits word length
#define	HwUART1_LCR_WLS_6						Hw0										// 6 bits word length
#define	HwUART1_LCR_WLS_7						Hw1										// 7 bits word length
#define	HwUART1_LCR_WLS_8						(Hw1+Hw0)								// 8 bits word length
                                			
#define	HwUART1_MCR								*(volatile unsigned long *)0xF0056010	// R/W, MODEM Control Register
#define	HwUART1_MCR_LOOP_ON						Hw4										// Loop Back Enable
#define	HwUART1_MCR_LOOP_OFF					~Hw4									// Loop Back Disable
#define	HwUART1_MCR_RTS							Hw1										// This bit informs the external modem that the uart is ready to exchange data
                                			
#define	HwUART1_LSR								*(volatile unsigned long *)0xF0056014	// R, Line Status Register
#define	HwUART1_LSR_ERF_FIFO					Hw7										// In the FIFO mode this bit is set when there is at least one parity error, framing error or break indication in the FIFO
#define	HwUART1_LSR_ERF_16450					~Hw7									// In the 16450 mode
#define	HwUART1_LSR_TEMT_ON						Hw6										// Transmitter holding register and the transmitter shift register are both empty
#define	HwUART1_LSR_TEMT_OFF					~Hw6									//
#define	HwUART1_LSR_THRE_ON						Hw5										// UART is ready to accept a new char for transmission
#define	HwUART1_LSR_THRE_OFF					~Hw5									//
#define	HwUART1_LSR_BI_ON						Hw4										// The received data input is held in the spacing (logic 0) state for longer than a full word transmission time
#define	HwUART1_LSR_BI_OFF						~Hw4									//
#define	HwUART1_LSR_FE_ON						Hw3										// The received character did not have a valid stop bit
#define	HwUART1_LSR_FE_OFF						~Hw3									//
#define	HwUART1_LSR_PE_ON						Hw2										// The received data character does not have the correct even or odd parity
#define	HwUART1_LSR_PE_OFF						~Hw2									//
#define	HwUART1_LSR_OE_ON						Hw1										// The receiver buffer register was not read by the CPU before the next character was transferred into the receiver buffer register
#define	HwUART1_LSR_OE_OFF						~Hw1									//
#define	HwUART1_LSR_DR_ON						Hw0										// The receiver data ready
#define	HwUART1_LSR_DR_OFF						~Hw0									//
                                			
#define	HwUART1_MSR								*(volatile unsigned long *)0xF0056018	// R, MODEM Status Register
#define HwUART1_MSR_CTS							Hw4										// This bit is the complement of the Claer to Send input
#define	HwUART1_MSR_DCTS						Hw0										// This bit is the Delta Clear to Send indicator
                                			
#define	HwUART1_SCR								*(volatile unsigned long *)0xF005601C	// R/W, Scratch Register
																						// This 8bit Read/Write Register does not control the UART in anyway. It is intended as a scratch pad register to be used by the programmer to hold data temporarily

/************************************************************************
*	GSIO Port Register Define					(Base Addr = 0xF0057000)
************************************************************************/
#define	HwGSDO0									*(volatile unsigned long *)0xF0057000	// R/W, GSIO0 Output Data Register
                                			
#define	HwGSDI0									*(volatile unsigned long *)0xF0057004	// R/W, GSIO0 Input Data Register
                                			
#define	HwGSCR0									*(volatile unsigned long *)0xF0057008	// R/W, GSIO0 Control Register
#define	HwGSCR0_EN_ON							Hw31									// GSIO Enable
#define	HwGSCR0_EN_OFF							~Hw31									// GSIO Disable
#define	HwGSCR0_MS_MSB							Hw30									// MSB First
#define	HwGSCR0_MS_LSB							~Hw30									// LSB First
#define	HwGSCR0_WS_BW							Hw25									// Word Size
#define	HwGSCR0_WS_WORD							~Hw25									// Word Size
#define	HwGSCR0_CP_RISE							Hw17									// Clock Polarity
#define	HwGSCR0_CP_FALL							~Hw17									// Clock Polarity
#define	HwGSCR0_CM_MASK							Hw16									// Last Clock Mask
#define	HwGSCR0_CM_NOMASK						~Hw16									// Last Clock Mask
#define	HwGSCR0_FP_HIGH							Hw12									// Frame Polarity
#define	HwGSCR0_FP_LOW							~Hw12									// Frame Polarity
                                			
#define	HwGSGCR									*(volatile unsigned long *)0xF005700C	// R/W, GSIO0 Global Control Register
#define	HwGSGCR_G1_ON							Hw13									// 
#define	HwGSGCR_G1_OFF							~Hw13									//
#define	HwGSGCR_G0_ON							Hw12									//
#define	HwGSGCR_G0_OFF							~Hw12									//
#define	HwGSGCR_IEN1							Hw9										// GSIO1 Interrupt enable
#define	HwGSGCR_IEN0							Hw8										// GSIO0 Interrupt enable
#define	HwGSGCR_FLG1							Hw5										//
#define	HwGSGCR_FLG0							Hw4										//
#define	HwGSGCR_BUSY1							Hw1										//
#define	HwGSGCR_BUSY0							Hw0										//
                                			
#define	HwGSDO1									*(volatile unsigned long *)0xF0057010	// R/W, GSIO1 Output Data Register
                                			
#define	HwGSDI1									*(volatile unsigned long *)0xF0057014	// R/W, GSIO1 Input Data Register
                                			
#define	HwGSCR1									*(volatile unsigned long *)0xF0057018	// R/W, GSIO1 Control Register
#define	HwGSCR1_EN_ON							Hw31									// GSIO Enable
#define	HwGSCR1_EN_OFF							~Hw31									// GSIO Disable
#define	HwGSCR1_MS_MSB							Hw30									// MSB First
#define	HwGSCR1_MS_LSB							~Hw30									// LSB First
#define	HwGSCR1_WS_BW							Hw25									// Word Size
#define	HwGSCR1_WS_WORD							~Hw25									// Word Size
#define	HwGSCR1_CP_RISE							Hw17									// Clock Polarity
#define	HwGSCR1_CP_FALL							~Hw17									// Clock Polarity
#define	HwGSCR1_CM_MASK							Hw16									// Last Clock Mask
#define	HwGSCR1_CM_NOMASK						~Hw16									// Last Clock Mask
#define	HwGSCR1_FP_HIGH							Hw12									// Frame Polarity
#define	HwGSCR1_FP_LOW							~Hw12									// Frame Polarity
                                			
#define	WAIT_GSIO0_BUSY							{while((HwGSGCR & HwGSGCR_BUSY0));}
                                			
#define	WAIT_GSIO1_BUSY							{while((HwGSGCR & HwGSGCR_BUSY1));}

/************************************************************************
*	GPSB(General Purpose Serial Bus) Define		(Base Addr = 0xF0057400)
************************************************************************/
#define	HwGPSB_CH0_BASE							*(volatile unsigned long *)0xF0057400
#define	HwGPSB_CH1_BASE							*(volatile unsigned long *)0xF0057800

typedef	volatile struct {
	unsigned	PORT;
	unsigned	STAT;
	unsigned	INTEN;
	unsigned	MODE;
	unsigned	CTRL;
	unsigned	Dummy1[3];
	unsigned	TXBASE;
	unsigned	RXBASE;
	unsigned	PACKET;
	unsigned	DMACTR;
	unsigned	DMASTR;
} sHwGPSB;

#define	HwGPSB_STAT_WOR					Hw8									// Write FIFO over-run error flag
#define	HwGPSB_STAT_RUR					Hw7									// Read FIFO under-run error flag
#define	HwGPSB_STAT_WUR					Hw6									// Write FIFO under-run error flag
#define	HwGPSB_STAT_ROR					Hw5									// Read FIFO over-run error flag
#define	HwGPSB_STAT_RF						Hw4									// Read FIFO full flag
#define	HwGPSB_STAT_WE						Hw3									// Write FIFO empty flag
#define	HwGPSB_STAT_RNE					Hw2									// Read FIFO not empty flag
#define	HwGPSB_STAT_WTH					Hw1									// Wrtie FIFO valid entry count is under threshold
#define	HwGPSB_STAT_RTH					Hw0									// Read FIFO valid entry increased over threshold
#define	HwGPSB_INTEN_DW					Hw31								// DMA request enable for transmit FIFO
#define	HwGPSB_INTEN_DR					Hw30								// DMA request enable for receive FIFO
#define	HwGPSB_INTEN_SWD_BHW				Hw27								// Swap byte in half-word
#define	HwGPSB_INTEN_SWD_HWW				Hw26								// Swap half-word in word
#define	HwGPSB_INTEN_SRD_BHW				Hw25								// Swap byte in half-word
#define	HwGPSB_INTEN_SRD_HWW				Hw24								// Swap half-word in word
#define	HwGPSB_INTEN_CFGWTH(X)			((X)*Hw20)								// Write FIFO threshold for Interrupt or DMA Request
#define	HwGPSB_INTEN_CFGRTH(X)			((X)*Hw16)								// Read FIFO threshold for Interrupt or DMA Request
#define	HwGPSB_INTEN_RC					Hw15								// Clear status[8:0] at the end of read cycle
#define	HwGPSB_INTEN_WOR					Hw8									// Write FIFO over-run error interrupt enable
#define	HwGPSB_INTEN_RUR					Hw7									//Read FIFO under-run error flag interrupt enable
#define	HwGPSB_INTEN_WUR					Hw6									// Write FIFO under-run error flag interrupt enable
#define	HwGPSB_INTEN_ROR					Hw5									// Read FIFO over-run error flag interrupt enable
#define	HwGPSB_INTEN_RF					Hw4									// Read FIFO full flag interrupt enable
#define	HwGPSB_INTEN_WE					Hw3									// Write FIFO empty flag interrupt enable
#define	HwGPSB_INTEN_RNE					Hw2									// Read FIFO not empty flag interrupt enable
#define	HwGPSB_INTEN_WTH					Hw1									// Wrtie FIFO valid entry count is under threshold interrupt enable
#define	HwGPSB_INTEN_RTH					Hw0									// Read FIFO valid entry increased over threshold interrupt enable
#define	HwGPSB_MODE_TRE					Hw23								// Master recovery time
#define	HwGPSB_MODE_THL					Hw22								// Master hold time
#define	HwGPSB_MODE_TSU					Hw21								// Master setup time
#define	HwGPSB_MODE_PCS					Hw20								// Polarity control for CS(FRM) - Master Only
#define	HwGPSB_MODE_PCD					Hw19								// Polarity control for CMD(FRM)- Master Only
#define	HwGPSB_MODE_PWD					Hw18								// Polarity control for transmit data - Master Only
#define	HwGPSB_MODE_PRD					Hw17								// Polarity control for receive data - Master Only
#define	HwGPSB_MODE_PCK					Hw16								// Polarity control for serial clock
#define	HwGPSB_MODE_CRF					Hw15								// Clear receive FIFO counter
#define	HwGPSB_MODE_CWF					Hw14								// Clear transmit FIFO counter
#define	HwGPSB_MODE_SD					Hw7									// Data shift direction control
#define	HwGPSB_MODE_LB						Hw6									// Data looop-back enable
#define	HwGPSB_MODE_CTF					Hw4									// Continuous transfer mode enable
#define	HwGPSB_MODE_EN					Hw3									// Operation enable
#define	HwGPSB_MODE_SLV					Hw2									// Slave mode configuration
#define	HwGPSB_MODE_MD_SPI				HwZERO								// SPI compatible
#define	HwGPSB_MODE_MD_SSP				Hw0									// SSP Compatible
#define	HwGPSB_CTRL_LCW					Hw31								// Last clock disable for write cycle
#define	HwGPSB_CTRL_LCR					Hw30								// Last clock disable for read cycle
#define	HwGPSB_CTRL_PLW					Hw7									// Polarity control for write command
#define	HwGPSB_DMACTRL_DTE				Hw31								// Transmit DMA request enable
#define	HwGPSB_DMACTRL_DRE				Hw30								// Receive DMA request enable
#define	HwGPSB_DMACTRL_CT					Hw29								// Continuous mode enable
#define	HwGPSB_DMACTRL_END				Hw28								// Byte endian mode register
#define	HwGPSB_DMACTRL_MP					Hw19								// PID match mode register
#define	HwGPSB_DMACTRL_MS					Hw18								// Sync byte match control register
#define	HwGPSB_DMACTRL_IS					Hw11								// IRQ mode selection
#define	HwGPSB_DMACTRL_MD_NOR			HwZERO								// normal mode
#define	HwGPSB_DMACTRL_MD_MP2TS			Hw4									// MPEG2-TS mode
#define	HwGPSB_DMACTRL_IEN					Hw1									// Interrupt enable
#define	HwGPSB_DMACTRL_EN					Hw0									// DMA enable

#define	HwGPSB_CH0PORT							*(volatile unsigned long *)0xF0057400	// R/W, Data Port
                                			
#define	HwGPSB_CH0STAT							*(volatile unsigned long *)0xF0057404	// R/W, Status Register
#define	HwGPSB_CH0STAT_WOR						Hw8										// Write FIFO over-run error flag
#define	HwGPSB_CH0STAT_RUR						Hw7										// Read FIFO under-run error flag
#define	HwGPSB_CH0STAT_WUR						Hw6										// Write FIFO under-run error flag
#define	HwGPSB_CH0STAT_ROR						Hw5										// Read FIFO over-run error flag
#define	HwGPSB_CH0STAT_RF						Hw4										// Read FIFO full flag
#define	HwGPSB_CH0STAT_WE						Hw3										// Write FIFO empty flag
#define	HwGPSB_CH0STAT_RNE						Hw2										// Read FIFO not empty flag
#define	HwGPSB_CH0STAT_WTH						Hw1										// Wrtie FIFO valid entry count is under threshold
#define	HwGPSB_CH0STAT_RTH						Hw0										// Read FIFO valid entry increased over threshold
                                			
#define	HwGPSB_CH0INTEN							*(volatile unsigned long *)0xF0057408	// R/W, Interrupt Enable
#define	HwGPSB_CH0INTEN_DW						Hw31									// DMA request enable for transmit FIFO
#define	HwGPSB_CH0INTEN_DR						Hw30									// DMA request enable for receive FIFO
#define	HwGPSB_CH0INTEN_SWD_BHW					Hw27									// Swap byte in half-word
#define	HwGPSB_CH0INTEN_SWD_HWW					Hw26									// Swap half-word in word
#define	HwGPSB_CH0INTEN_SRD_BHW					Hw25									// Swap byte in half-word
#define	HwGPSB_CH0INTEN_SRD_HWW					Hw24									// Swap half-word in word
#define	HwGPSB_CH0INTEN_RC						Hw15									// Clear status[8:0] at the end of read cycle
#define	HwGPSB_CH0INTEN_WOR						Hw8										// Write FIFO over-run error interrupt enable
#define	HwGPSB_CH0INTEN_RUR						Hw7										//Read FIFO under-run error flag interrupt enable
#define	HwGPSB_CH0INTEN_WUR						Hw6										// Write FIFO under-run error flag interrupt enable
#define	HwGPSB_CH0INTEN_ROR						Hw5										// Read FIFO over-run error flag interrupt enable
#define	HwGPSB_CH0INTEN_RF						Hw4										// Read FIFO full flag interrupt enable
#define	HwGPSB_CH0INTEN_WE						Hw3										// Write FIFO empty flag interrupt enable
#define	HwGPSB_CH0INTEN_RNE						Hw2										// Read FIFO not empty flag interrupt enable
#define	HwGPSB_CH0INTEN_WTH						Hw1										// Wrtie FIFO valid entry count is under threshold interrupt enable
#define	HwGPSB_CH0INTEN_RTH						Hw0										// Read FIFO valid entry increased over threshold interrupt enable
                                			
#define	HwGPSB_CH0MODE							*(volatile unsigned long *)0xF005740C	// R/W, Mode Register
#define	HwGPSB_CH0MODE_TRE						Hw23									// Master recovery time
#define	HwGPSB_CH0MODE_THL						Hw22									// Master hold time
#define	HwGPSB_CH0MODE_TSU						Hw21									// Master setup time
#define	HwGPSB_CH0MODE_PCS						Hw20									// Polarity control for CS(FRM) - Master Only
#define	HwGPSB_CH0MODE_PCD						Hw19									// Polarity control for CMD(FRM)- Master Only
#define	HwGPSB_CH0MODE_PWD						Hw18									// Polarity control for transmit data - Master Only
#define	HwGPSB_CH0MODE_PRD						Hw17									// Polarity control for receive data - Master Only
#define	HwGPSB_CH0MODE_PCK						Hw16									// Polarity control for serial clock
#define	HwGPSB_CH0MODE_CRF						Hw15									// Clear receive FIFO counter
#define	HwGPSB_CH0MODE_CWF						Hw14									// Clear transmit FIFO counter
#define	HwGPSB_CH0MODE_SD						Hw7										// Data shift direction control
#define	HwGPSB_CH0MODE_LB						Hw6										// Data looop-back enable
#define	HwGPSB_CH0MODE_CTF						Hw4										// Continuous transfer mode enable
#define	HwGPSB_CH0MODE_EN						Hw3										// Operation enable
#define	HwGPSB_CH0MODE_SLV						Hw2										// Slave mode configuration
#define	HwGPSB_CH0MODE_MD_SPI					HwZERO									// SPI compatible
#define	HwGPSB_CH0MODE_MD_SSP					Hw0										// SSP Compatible
                                			
#define	HwGPSB_CH0CTRL							*(volatile unsigned long *)0xF0057410	// R/W, Control Register
#define	HwGPSB_CH0CTRL_LCW						Hw31									// Last clock disable for write cycle
#define	HwGPSB_CH0CTRL_LCR						Hw30									// Last clock disable for read cycle
#define	HwGPSB_CH0CTRL_PLW						Hw7										// Polarity control for write command
                                			
#define	HwGPSB_CH0TXBASE						*(volatile unsigned long *)0xF0057420	// R/W, TX base address register
                                			
#define	HwGPSB_CH0RXBASE						*(volatile unsigned long *)0xF0057424	// R/W, RX base address register
                                			
#define	HwGPSB_CH0PACKET						*(volatile unsigned long *)0xF0057428	// R/W, Packet register
                                        	
#define	HwGPSB_CH0DMACTRL						*(volatile unsigned long *)0xF005742C	// R/W, DMA control register
#define	HwGPSB_CH0DMACTRL_DTE					Hw31									// Transmit DMA request enable
#define	HwGPSB_CH0DMACTRL_DRE					Hw30									// Receive DMA request enable
#define	HwGPSB_CH0DMACTRL_CT					Hw29									// Continuous mode enable
#define	HwGPSB_CH0DMACTRL_END					Hw28									// Byte endian mode register
#define	HwGPSB_CH0DMACTRL_MP					Hw19									// PID match mode register
#define	HwGPSB_CH0DMACTRL_MS					Hw18									// Sync byte match control register
#define	HwGPSB_CH0DMACTRL_IS					Hw11									// IRQ mode selection
#define	HwGPSB_CH0DMACTRL_MD_NOR				HwZERO									// normal mode
#define	HwGPSB_CH0DMACTRL_MD_MP2TS				Hw4										// MPEG2-TS mode
#define	HwGPSB_CH0DMACTRL_IEN					Hw1										// Interrupt enable
#define	HwGPSB_CH0DMACTRL_EN					Hw0										// DMA enable
                                    			
#define	HwGPSB_CH0DMASTAT						*(volatile unsigned long *)0xF0057430	// R/W, DMA status register
                                    			
#define	HwGPSB_CH1PORT							*(volatile unsigned long *)0xF0057800	// R/W, Data Port
                                    			
#define	HwGPSB_CH1STAT							*(volatile unsigned long *)0xF0057804	// R/W, Status Register
#define	HwGPSB_CH1STAT_WOR						Hw8										// Write FIFO over-run error flag
#define	HwGPSB_CH1STAT_RUR						Hw7										// Read FIFO under-run error flag
#define	HwGPSB_CH1STAT_WUR						Hw6										// Write FIFO under-run error flag
#define	HwGPSB_CH1STAT_ROR						Hw5										// Read FIFO over-run error flag
#define	HwGPSB_CH1STAT_RF						Hw4										// Read FIFO full flag
#define	HwGPSB_CH1STAT_WE						Hw3										// Write FIFO empty flag
#define	HwGPSB_CH1STAT_RNE						Hw2										// Read FIFO not empty flag
#define	HwGPSB_CH1STAT_WTH						Hw1										// Wrtie FIFO valid entry count is under threshold
#define	HwGPSB_CH1STAT_RTH						Hw0										// Read FIFO valid entry increased over threshold
                                    			
#define	HwGPSB_CH1INTEN							*(volatile unsigned long *)0xF0057808	// R/W, Interrupt Enable
#define	HwGPSB_CH1INTEN_DW						Hw31									// DMA request enable for transmit FIFO
#define	HwGPSB_CH1INTEN_DR						Hw30									// DMA request enable for receive FIFO
#define	HwGPSB_CH1INTEN_SWD_BHW					Hw27									// Swap byte in half-word
#define	HwGPSB_CH1INTEN_SWD_HWW					Hw26									// Swap half-word in word
#define	HwGPSB_CH1INTEN_SRD_BHW					Hw25									// Swap byte in half-word
#define	HwGPSB_CH1INTEN_SRD_HWW					Hw24									// Swap half-word in word
#define	HwGPSB_CH1INTEN_RC						Hw15									// Clear status[8:0] at the end of read cycle
#define	HwGPSB_CH1INTEN_WOR						Hw8										// Write FIFO over-run error interrupt enable
#define	HwGPSB_CH1INTEN_RUR						Hw7										//Read FIFO under-run error flag interrupt enable
#define	HwGPSB_CH1INTEN_WUR						Hw6										// Write FIFO under-run error flag interrupt enable
#define	HwGPSB_CH1INTEN_ROR						Hw5										// Read FIFO over-run error flag interrupt enable
#define	HwGPSB_CH1INTEN_RF						Hw4										// Read FIFO full flag interrupt enable
#define	HwGPSB_CH1INTEN_WE						Hw3										// Write FIFO empty flag interrupt enable
#define	HwGPSB_CH1INTEN_RNE						Hw2										// Read FIFO not empty flag interrupt enable
#define	HwGPSB_CH1INTEN_WTH						Hw1										// Wrtie FIFO valid entry count is under threshold interrupt enable
#define	HwGPSB_CH1INTEN_RTH						Hw0										// Read FIFO valid entry increased over threshold interrupt enable
                                    			
#define	HwGPSB_CH1MODE							*(volatile unsigned long *)0xF005780C	// R/W, Mode Register
#define	HwGPSB_CH1MODE_TRE						Hw23									// Master recovery time
#define	HwGPSB_CH1MODE_THL						Hw22									// Master hold time
#define	HwGPSB_CH1MODE_TSU						Hw21									// Master setup time
#define	HwGPSB_CH1MODE_PCS						Hw20									// Polarity control for CS(FRM) - Master Only
#define	HwGPSB_CH1MODE_PCD						Hw19									// Polarity control for CMD(FRM)- Master Only
#define	HwGPSB_CH1MODE_PWD						Hw18									// Polarity control for transmit data - Master Only
#define	HwGPSB_CH1MODE_PRD						Hw17									// Polarity control for receive data - Master Only
#define	HwGPSB_CH1MODE_PCK						Hw16									// Polarity control for serial clock
#define	HwGPSB_CH1MODE_CRF						Hw15									// Clear receive FIFO counter
#define	HwGPSB_CH1MODE_CWF						Hw14									// Clear transmit FIFO counter
#define	HwGPSB_CH1MODE_SD						Hw7										// Data shift direction control
#define	HwGPSB_CH1MODE_LB						Hw6										// Data looop-back enable
#define	HwGPSB_CH1MODE_CTF						Hw4										// Continuous transfer mode enable
#define	HwGPSB_CH1MODE_EN						Hw3										// Operation enable
#define	HwGPSB_CH1MODE_SLV						Hw2										// Slave mode configuration
#define	HwGPSB_CH1MODE_MD_SPI					HwZERO									// SPI compatible
#define	HwGPSB_CH1MODE_MD_SSP					Hw0										// SSP Compatible
                                    			
#define	HwGPSB_CH1CTRL							*(volatile unsigned long *)0xF0057810	// R/W, Control Register
#define	HwGPSB_CH1CTRL_LCW						Hw31									// Last clock disable for write cycle
#define	HwGPSB_CH1CTRL_LCR						Hw30									// Last clock disable for read cycle
#define	HwGPSB_CH1CTRL_PLW						Hw7										// Polarity control for write command
                                    			
#define	HwGPSB_CH1TXBASE						*(volatile unsigned long *)0xF0057820	// R/W, TX base address register
                                    			
#define	HwGPSB_CH1RXBASE						*(volatile unsigned long *)0xF0057824	// R/W, RX base address register
                                    			
#define	HwGPSB_CH1PACKET						*(volatile unsigned long *)0xF0057828	// R/W, Packet register
                                    			
#define	HwGPSB_CH1DMACTRL						*(volatile unsigned long *)0xF005782C	// R/W, DMA control register
#define	HwGPSB_CH1DMACTRL_DTE					Hw31									// Transmit DMA request enable
#define	HwGPSB_CH1DMACTRL_DRE					Hw30									// Receive DMA request enable
#define	HwGPSB_CH1DMACTRL_CT					Hw29									// Continuous mode enable
#define	HwGPSB_CH1DMACTRL_END					Hw28									// Byte endian mode register
#define	HwGPSB_CH1DMACTRL_MP					Hw19									// PID match mode register
#define	HwGPSB_CH1DMACTRL_MS					Hw18									// Sync byte match control register
#define	HwGPSB_CH1DMACTRL_IS					Hw11									// IRQ mode selection
#define	HwGPSB_CH1DMACTRL_MD_NOR				HwZERO									// normal mode
#define	HwGPSB_CH1DMACTRL_MD_MP2TS				Hw4										// MPEG2-TS mode
#define	HwGPSB_CH1DMACTRL_IEN					Hw1										// Interrupt enable
#define	HwGPSB_CH1DMACTRL_EN					Hw0										// DMA enable
                                    			
#define	HwGPSB_CH1DMASTAT						*(volatile unsigned long *)0xF0057830	// R/W, DMA status register

/***********************************************************************
*	 SD/MMC Controller Register Define			(Base Addr = 0xF0058000)
************************************************************************/
#define	HwSDICLK								*(volatile unsigned long *)0xF0058004	// R/W, Clock control register
#define	HwSDICLK_BP_ON							Hw13									//
#define	HwSDICLK_BP_OFF							~Hw13									//
#define	HwSDICLK_EN_ON							Hw12									//
#define	HwSDICLK_EN_OFF							~Hw12									//
                                        	
#define	HwSDIARGU								*(volatile unsigned long *)0xF0058008	// R/W, Command argument register
                                        	
#define	HwSDICMD								*(volatile unsigned long *)0xF005800C	// R/W, Command index and type register
#define	HwSDICMD_EN_ON							Hw11									//
#define	HwSDICMD_EN_OFF							~Hw11									//
#define	HwSDICMD_CD_WITH_DATA					Hw10									//
#define	HwSDICMD_CD_WITHOUT_DATA				~Hw10									//
#define	HwSDICMD_RT_1							Hw7										// normal command with response of 48bit width
#define	HwSDICMD_RT_1B							Hw8										// command with optional busy signal
#define	HwSDICMD_RT_2							(Hw8+Hw7)								// CID, CSD register
#define	HwSDICMD_RT_3							Hw9										// OCR register
#define	HwSDICMD_RT_4							(Hw9+Hw7)								// CMD5 for SDIO
#define	HwSDICMD_RT_5							(Hw9+Hw8)								// CMD52, CMD53 or SDIO
#define	HwSDICMD_RT_6							(Hw9+Hw8+Hw7)							// Published RCA response
#define	HwSDICMD_WR_RES							Hw6										//
#define	HwSDICMD_WR_NORES						~Hw6									//
                                        	
                                        	
#define	HwSDIRSPCMD								*(volatile unsigned long *)0xF0058010	// R, Response index register
                                        	
#define	HwSDIRSPARGU0							*(volatile unsigned long *)0xF0058014	// R, Response argument register0
                                        	
#define	HwSDIRSPARGU1							*(volatile unsigned long *)0xF0058018	// R, Response argument register1
                                        	
#define	HwSDIRSPARGU2							*(volatile unsigned long *)0xF005801C	// R, Response argument register2
                                        	
#define	HwSDIRSPARGU3							*(volatile unsigned long *)0xF0058020	// R, Response argument register3
	                                    	
#define	HwSDIDITIMER							*(volatile unsigned long *)0xF0058024	// R/W, Wait cycles for data transfer
                                        	
#define	HwSDIDCTRL2								*(volatile unsigned long *)0xF0058028	// R/W, Data path control 2 register
#define	HwSDIDCTRL2_ST							Hw3										// Stop Transfer
#define	HwSDIDCTRL2_BM							Hw2										// Transfer Mode
#define	HwSDIDCTRL2_DD							Hw1										// Transfer Direction
#define	HwSDIDCTRL2_MODE						Hw0										// SDIO Data Transfer Mode
                                        	
#define	HwSDIDCTRL								*(volatile unsigned long *)0xF005802C	// R/W, Data path control register
#define	HwSDIDCTRL_WTD							Hw28									// Controller waits data forever
#define	HwSDIDCTRL_BE_BIG						Hw24									//
#define	HwSDIDCTRL_BE_LITTLE					~Hw24									//
#define	HwSDIDCTRL_FSR_OP						Hw12									//
#define	HwSDIDCTRL_FSR_RST						~Hw12									//
#define	HwSDIDCTRL_WB_1							~(Hw3+Hw2)								//
#define	HwSDIDCTRL_WB_4							Hw2										//
#define	HwSDIDCTRL_WB_8							Hw3										//
#define	HwSDIDCTRL_DTM_STM						Hw1										//
#define	HwSDIDCTRL_DTM_BLK						~Hw1									//
#define	HwSDIDCTRL_DEN_ON						Hw0										//
#define	HwSDIDCTRL_DEN_OFF						~Hw0									//
                                        	
#define	HwSDISTATUS								*(volatile unsigned long *)0xF0058030	// R, Status register
#define	HwSDISTATUS_SI							Hw26									// SDIO Interrupt
#define	HwSDISTATUS_MBE							Hw25									//
#define	HwSDISTATUS_SBE							Hw24									//
#define	HwSDISTATUS_FD							Hw23									//
#define	HwSDISTATUS_DPR							Hw22									//
#define	HwSDISTATUS_CPR							Hw21									//
#define	HwSDISTATUS_RFU							Hw20									//
#define	HwSDISTATUS_TFO							Hw19									//
#define	HwSDISTATUS_FFR							Hw18									//
#define	HwSDISTATUS_FLR							Hw17									//
#define	HwSDISTATUS_FCF							Hw16									//
#define	HwSDISTATUS_FF							Hw15									//
#define	HwSDISTATUS_FE							Hw14									//
#define	HwSDISTATUS_RA							Hw13									//
#define	HwSDISTATUS_TA							Hw12									//
#define	HwSDISTATUS_RDBE						Hw10									//
#define	HwSDISTATUS_TDBE						Hw9										//
#define	HwSDISTATUS_CRE							Hw7										//
#define	HwSDISTATUS_FWE							Hw6										//
#define	HwSDISTATUS_DTO							Hw4										//
#define	HwSDISTATUS_CTO							Hw3										//
#define	HwSDISTATUS_RDCF						Hw2										//
#define	HwSDISTATUS_TDCF						Hw1										//
#define	HwSDISTATUS_CCF							Hw0										//
                                        	
#define	HwSDIIFLAG								*(volatile unsigned long *)0xF0058034	// R/W, Interrupt flag register
#define	HwSDIIFLAG_SDIOI						Hw9										// SDIO Interrupt
#define	HwSDIIFLAG_DRI							Hw8										//
#define	HwSDIIFLAG_CRI							Hw7										//
#define	HwSDIIFLAG_FWEI							Hw6										//
#define	HwSDIIFLAG_SBEI							Hw5										//
#define	HwSDIIFLAG_DTI							Hw4										//
#define	HwSDIIFLAG_RTI							Hw3										//
#define	HwSDIIFLAG_RDCFI						Hw2										//
#define	HwSDIIFLAG_TDCFI						Hw1										//
#define	HwSDIIFLAG_RCFI							Hw0										//
                                        	
#define	HwSDIWDATA								*(volatile unsigned long *)0xF0058038	// R/W, Transmit data register
                                        	
#define	HwSDIRDATA								*(volatile unsigned long *)0xF005803C	// R, Receive data register
                                        	
#define	HwSDIIENABLE							*(volatile unsigned long *)0xF0058040	// R/W, Interrupt enable register
#define	HWSDIIENABLE_SDIIOI_EN					Hw9										//
#define	HWSDIIENABLE_SDIIOI_DIS					~Hw9									//
#define	HwSDIIENABLE_DRI_EN						Hw8										//
#define	HwSDIIENABLE_DRI_DIS					~Hw8									//
#define	HwSDIIENABLE_CRI_EN						Hw7										//
#define	HwSDIIENABLE_CRI_DIS					~Hw7									//
#define	HwSDIIENABLE_FWEI_EN					Hw6										//
#define	HwSDIIENABLE_FWEI_DIS					~Hw6									//
#define	HwSDIIENABLE_SBEI_EN					Hw5										//
#define	HwSDIIENABLE_SBEI_DIS					~Hw5									//
#define	HwSDIIENABLE_DTI_EN						Hw4										//
#define	HwSDIIENABLE_DTI_DIS					~Hw4									//
#define	HwSDIIENABLE_RTI_EN						Hw3										//
#define	HwSDIIENABLE_RTI_DIS					~Hw3									//
#define	HwSDIIENABLE_RDCFI_EN					Hw2										//
#define	HwSDIIENABLE_RDCFI_DIS					~Hw2									//
#define	HwSDIIENABLE_TDCFI_EN					Hw1										//
#define	HwSDIIENABLE_TDCFI_DIS					~Hw1									//
#define	HwSDIIENABLE_RCFI_EN					Hw0										//
#define	HwSDIIENABLE_RCFI_DIS					~Hw0									//

/************************************************************************
*	DAI & CDIF Register Define					(Base Addr = 0xF0059000)
************************************************************************/
#define	HwDADI_L0								*(volatile unsigned long *)0xF0059000	// R, Digital Audio Left Input Register 0
                                    			
#define	HwDADI_R0								*(volatile unsigned long *)0xF0059004	// R, Digital Audio Right Input Register 0
                                    			
#define	HwDADI_L1								*(volatile unsigned long *)0xF0059008	// R, Digital Audio Left Input Register 1
                                    			
#define	HwDADI_R1								*(volatile unsigned long *)0xF005900C	// R, Digital Audio Right Input Register 1
                                    			
#define	HwDADI_L2								*(volatile unsigned long *)0xF0059010	// R, Digital Audio Left Input Register 2
                                    			
#define	HwDADI_R2								*(volatile unsigned long *)0xF0059014	// R, Digital Audio Right Input Register 2
                                    			
#define	HwDADI_L3								*(volatile unsigned long *)0xF0059018	// R, Digital Audio Left Input Register 3
                                    			
#define	HwDADI_R3								*(volatile unsigned long *)0xF005901C	// R, Digital Audio Right Input Register 3
                                    			
#define	HwDADO_L0								*(volatile unsigned long *)0xF0059020	// R/W, Digital Audio Left output Register 0
                                    			
#define	HwDADO_R0								*(volatile unsigned long *)0xF0059024	// R/W, Digital Audio Right output Register 0
                                    			
#define	HwDADO_L1								*(volatile unsigned long *)0xF0059028	// R/W, Digital Audio Left output Register 1
                                    			
#define	HwDADO_R1								*(volatile unsigned long *)0xF005902C	// R/W, Digital Audio Right output Register 1
                                    			
#define	HwDADO_L2								*(volatile unsigned long *)0xF0059030	// R/W, Digital Audio Left output Register 2
                                    			
#define	HwDADO_R2								*(volatile unsigned long *)0xF0059034	// R/W, Digital Audio Right output Register 2
                                    			
#define	HwDADO_L3								*(volatile unsigned long *)0xF0059038	// R/W, Digital Audio Left output Register 3
                                    			
#define	HwDADO_R3								*(volatile unsigned long *)0xF005903C	// R/W, Digital Audio Right output Register 3
                                    			
#define	HwDAMR									*(volatile unsigned long *)0xF0059040	// R/W, Digital Audio Mode Register
#define	HwDAMR_RXE_EN							Hw22									// DAI RX Data Sign Extension Enable
#define	HwDAMR_RXE_DIS							~Hw22									// DAI RX Data Sign Extension Disable
#define	HwDAMR_RXS_MSB24						HwZERO									// Bit-pack MSB and 24bit mode
#define	HwDAMR_RXS_MSB16						Hw20									// Bit-pack MSB and 24bit mode
#define	HwDAMR_RXS_LSB24						Hw21									// Bit-pack LSB and 24bit mode
#define	HwDAMR_RXS_LSB16						(Hw21+Hw20)								// Bit-pack LSB and 16bit mode
#define	HwDAMR_TXS_MSB							~Hw19									// Bit-pack MSB mode
#define	HwDAMR_TXS_LSB24						Hw19									// Bit-pack LSB and 24bit mode
#define	HwDAMR_TXS_LSB16						(Hw19+Hw18)								// Bit-pack LSB and 16bit mode
#define	HwDAMR_EN_ON							Hw15									// Enable DAI module
#define	HwDAMR_EN_OFF							~Hw15									// Disable DAI module
#define	HwDAMR_TE_EN							Hw14									// DAI Transimit Enable
#define	HwDAMR_TE_DIS							~Hw14									// DAI Transimit Disable
#define	HwDAMR_RE_EN							Hw13									// DAI Receive Enable
#define	HwDAMR_RE_DIS							~Hw13									// DAI Receive Disable
#define	HwDAMR_MD_MSB							Hw12									// Set DAI bus as MSB justified mode
#define	HwDAMR_MD_IIS							~Hw12									// Set DAI bus as IIS bus mode
#define	HwDAMR_SM_INT							Hw11									// Set that DAI system clock is generated by the clock generator block
#define	HwDAMR_SM_EXT							~Hw11									// Set that DAI system clock is come from external pin
#define	HwDAMR_BM_INT							Hw10									// Set that DAI bit clock is generated by dividing DAI system clock
#define	HwDAMR_BM_EXT							~Hw10									// Set that DAI bit clock is come from external pin
#define	HwDAMR_FM_INT							Hw9										// Set that DAI Frame Clock is generated by dividing DAI bit clock
#define	HwDAMR_FM_EXT							~Hw9									// Set that DAI Frame Clock is come from external pin
#define	HwDAMR_CC_EN							Hw8										// Enable CDIF Clock master mode
#define	HwDAMR_CC_DIS							~Hw8									// Disable CDIF Clock master mode
#define	HwDAMR_BD_DIV4							HwZERO									// Select Div4 (256fs->64fs)
#define	HwDAMR_BD_DIV6							Hw6										// Select Div6 (384fs->64fs)
#define	HwDAMR_BD_DIV8							Hw7										// Select Div8 (512fs->64fs, 384fs->48fs, 256fs->32fs)
#define	HwDAMR_BD_DIV16							(Hw7+Hw6)								// Select Div16 (512fs->32fs)
#define	HwDAMR_FD_DIV32							HwZERO									// Select Div32 (32fs->fs)
#define	HwDAMR_FD_DIV48							Hw4										// Select Div48 (48fs->fs)
#define	HwDAMR_FD_DIV64							Hw5										// Select Div64 (64fs->fs)
#define	HwDAMR_BP_NEGA							Hw3										// Set that data is captured at negative edge of bit clock
#define	HwDAMR_BP_POSI							~Hw3									// Set that data is captured at positive edge of bit clock
#define	HwDAMR_CM_EN							Hw2										// Enable CDIF monitor mode. Data bypass from CDIF
#define	HwDAMR_CM_DIS							~Hw2									// Disable CDIF monitor mode
#define	HwDAMR_MM_EN							Hw1										// Enable DAI monitor mode. Transmitter should be enabled(TE=1).
#define	HwDAMR_MM_DIS							~Hw1									// Disable DAI monitor mode.
#define	HwDAMR_LB_EN							Hw0										// Enable DAI Loop back mode
#define	HwDAMR_LB_DIS							~Hw0									// Disable DAI Loop back mode
                                    			
#define	HwDAVC									*(volatile unsigned long *)0xF0059044	// R/W, Digital Audio Volume Control Register
#define	HwDAVC_0dB								HwZERO									// 0dB Volume
#define	HwDAVC_6dB								Hw0										// -6dB Volume
#define	HwDAVC_12dB								Hw1										// -12dB Volume
#define	HwDAVC_18dB								(Hw1+Hw0)								// -18dB Volume
#define	HwDAVC_24dB								Hw2										// -24dB Volume
#define	HwDAVC_30dB								(Hw2+Hw0)								// -30dB Volume
#define	HwDAVC_36dB								(Hw2+Hw1)								// -36dB Volume
#define	HwDAVC_42dB								(Hw2+Hw1+Hw0)							// -42dB Volume
#define	HwDAVC_48dB								Hw3										// -48dB Volume
#define	HwDAVC_54dB								(Hw3+Hw0)								// -54dB Volume
#define	HwDAVC_60dB								(Hw3+Hw1)								// -60dB Volume
#define	HwDAVC_66dB								(Hw3+Hw1+Hw0)							// -66dB Volume
#define	HwDAVC_72dB								(Hw3+Hw2)								// -72dB Volume
#define	HwDAVC_78dB								(Hw3+Hw2+Hw0)							// -78dB Volume
#define	HwDAVC_84dB								(Hw3+Hw2+Hw1)							// -84dB Volume
#define	HwDAVC_90dB								(Hw3+Hw2+Hw1+Hw0)						// -90dB Volume
                                    			
#define	HwCDDI_0								*(volatile unsigned long *)0xF0059080	// R, CD Digital Audio Input Register 0
                                    			
#define	HwCDDI_1								*(volatile unsigned long *)0xF0059084	// R, CD Digital Audio Input Register 1
                                    			
#define	HwCDDI_2								*(volatile unsigned long *)0xF0059088	// R, CD Digital Audio Input Register 2
                                    			
#define	HwCDDI_3								*(volatile unsigned long *)0xF005908C	// R, CD Digital Audio Input Register 3
                                    			
#define	HwCICR									*(volatile unsigned long *)0xF0059090	// R/W, CD Interface Control Register
#define	HwCICR_EN_ON							Hw7										// CIDF Enable
#define	HwCICR_EN_OFF							~Hw7									// CIDF Disable
#define	HwCICR_BS_64							HwZERO									// 64fs
#define	HwCICR_BS_32							Hw2										// 32fs
#define	HwCICR_BS_48							Hw3										// 48fs
#define	HwCICR_MD_LSB							Hw1										// Select LSB justified format
#define	HwCICR_MD_IIS							~Hw1									// Select IIS format
#define	HwCICR_BP_NEGA							Hw0										// Set that data is captured at negative edge of bit clock
#define	HwCICR_BP_POSI							~Hw0									// Set that data is captured at positive edge of bit clock

/************************************************************************
*	GPIO Port Register Define					(Base Addr = 0xF005A000)
************************************************************************/
#define	HwPORTCFG0								*(volatile unsigned long *)0xF005A000	// R/W, Port Configuration Register 0
#define	HwPORTCFG0_GPA7_0						HwZERO									// General Purpose Register
#define	HwPORTCFG0_GPA7_1						Hw30									// External Clock Input for CKC
#define	HwPORTCFG0_GPA7_3						(Hw31+Hw30)								// Timer Counter Output 0
#define	HwPORTCFG0_GPA6_0						HwZERO									// General Purpose Register
#define	HwPORTCFG0_GPA6_1						Hw28									// Transmitter Signal for SPDIF
#define	HwPORTCFG0_GPA6_3						(Hw29+Hw28)								// Timer Counter Output 1
#define	HwPORTCFG0_GPA5_0						HwZERO									// General Purpose Register
#define	HwPORTCFG0_GPA5_1						Hw26									// Fast GPIO Signal
#define	HwPORTCFG0_GPA5_3						(Hw27+Hw26)								// Timer Counter Output 2
#define	HwPORTCFG0_GPA4_0						HwZERO									// General Purpose Register
#define	HwPORTCFG0_GPA4_1						Hw24									// GPIO Signal
#define	HwPORTCFG0_GPA4_3						(Hw25+Hw24)								// Timer Counter Output 3
#define	HwPORTCFG0_GPA3_0						HwZERO									// General Purpose Register
#define	HwPORTCFG0_GPA3_1						Hw22									// GPIO Signal
#define	HwPORTCFG0_GPA3_2						Hw23									// Write Enable Signal for NAND Flash in External Memory Controller
#define	HwPORTCFG0_GPA3_3						(Hw23+Hw22)								// CKC Peripheral clock divider output for ZCLK
#define	HwPORTCFG0_GPA2_0						HwZERO									// General Purpose Register
#define	HwPORTCFG0_GPA2_1						Hw20									// GPIO Signal
#define	HwPORTCFG0_GPA2_2						Hw21									// Chip Select Signal for IDE in External Memory Controller
#define	HwPORTCFG0_GPA2_3						(Hw21+Hw20)								// CKC Peripheral clock divider output for XCLK
#define	HwPORTCFG0_GPA0_0						HwZERO									// General Purpose Register
#define	HwPORTCFG0_GPA0_1						Hw18									// SCL/SDA for I2C Controller
#define	HwPORTCFG0_EINT_0						HwZERO									// External Interrupt for Vectored Interrupt Contoller
#define	HwPORTCFG0_EINT_1						Hw16									// X'th Data Bus of Y'th Channel for SD Controller
#define	HwPORTCFG0_EINT_2						Hw17									// X'th Data Bus of Y'th Channel for Memory Stick Controller
#define	HwPORTCFG0_EINT_3						(Hw17+Hw16)								// General Purpose Register
#define	HwPORTCFG0_CDAI_0						HwZERO									// Input Data Signal for CD Interface
#define	HwPORTCFG0_CDAI_1						Hw14									// General Purpose Register
#define	HwPORTCFG0_DAI_0						HwZERO									// DAI for Digital Audio Interface
#define	HwPORTCFG0_DAI_1						Hw12									// General Purpose Register
#define	HwPORTCFG0_CSN2_0						HwZERO									// Chip Enable 2 for External Memory Interface
#define	HwPORTCFG0_CSN2_1						Hw10									// General Purpose Register
#define	HwPORTCFG0_CSN1_0						HwZERO									// Chip Enable 1 for External Memory Interface
#define	HwPORTCFG0_CSN1_1						Hw8										// General Purpose Register
#define	HwPORTCFG0_CSN0_0						HwZERO									// Chip Enable 0 for External Memory Interface
#define	HwPORTCFG0_CSN0_1						Hw6										// General Purpose Register
#define	HwPORTCFG0_SDCKE_0						HwZERO									// SDRAM Clock Enable Signal for DRAM Channel 0
#define	HwPORTCFG0_SDCKE_1						Hw4										// General Purpose Register
#define	HwPORTCFG0_SDCSN_0						HwZERO									// SDRAM Chip Enable Signal for DRAM Channel 0
#define	HwPORTCFG0_SDCSN_1						Hw2										// General Purpose Register
#define	HwPORTCFG0_XDU16_0						HwZERO									// Upper 16Bits Data Bus for External Memory Interface Channel 0
#define	HwPORTCFG0_XDU16_1						Hw0										// General Purpose Register
#define HwPORTCFG0_XDU16_3						(Hw1+Hw0)								// Video SDRAM for DRAM Channel 1
                                    			
#define	HwPORTCFG1								*(volatile unsigned long *)0xF005A004	// R/W, Port Configuration Register 1
#define	HwPORTCFG1_LCTRL_0						HwZERO									// General Purpose Register
#define	HwPORTCFG1_LCTRL_1						Hw30									// LCD Signal with Memory Interface
#define	HwPORTCFG1_LCTRL_3						(Hw31+Hw30)								// LCD Signal with RGB Interface
#define	HwPORTCFG1_HP4_0						HwZERO									// Upper 2 bits data bus for external host interface
#define	HwPORTCFG1_HP4_1						Hw26									// General Purpose I/O
#define	HwPORTCFG1_HP3_0						HwZERO									// Upper Nibble Data Bus for External Host Interface
#define	HwPORTCFG1_HP3_1						Hw24									// General Purpose Register
#define	HwPORTCFG1_HP3_3						(Hw25+Hw24)								// Timer Counter Output 5
#define	HwPORTCFG1_HP2_0						HwZERO									// Nibble Data Bus for External Host Interface
#define	HwPORTCFG1_HP2_1						Hw22									// General Purpose Register
#define	HwPORTCFG1_HP2_2						Hw23									// SPI Slave Controller Channel 1
#define	HwPORTCFG1_HP2_3						(Hw23+Hw22)								// Timer Counter Output 4
#define	HwPORTCFG1_HP1_0						HwZERO									// Data Bus for External Host Interface
#define	HwPORTCFG1_HP1_1						Hw20									// Data Bus for SD Controller for Channel 1 (y=1)
#define	HwPORTCFG1_HP1_2						Hw21									// General Purpose Register
#define	HwPORTCFG1_HP0_0						HwZERO									// External Host
#define	HwPORTCFG1_HP0_1						Hw18									// SD Controller Channel 1 (y=1)
#define	HwPORTCFG1_HP0_2						Hw19									// Memory Stick Controller Channel 1(y=1)
#define	HwPORTCFG1_HP0_3						(Hw19+Hw18)								// General Purpose I/O
#define	HwPORTCFG1_CAM07_0						HwZERO									// Data Bus for Camera Module Interface
#define	HwPORTCFG1_CAM07_1						Hw16									// Data Bus for Camera Module Interface
#define	HwPORTCFG1_CAM07_2						Hw17									// General Purpose I/O
#define	HwPORTCFG1_CAM07_3						(Hw16+Hw17)								// General Purpose I/O
#define	HwPORTCFG1_CAMC_0						HwZERO									// Camera Modue
#define	HwPORTCFG1_CAMC_1						Hw14									// Camera Modue
#define	HwPORTCFG1_CAMC_2						Hw15									// General Purpose I/O
#define	HwPORTCFG1_LCDU8_0						HwZERO									// Data Bus for LCD Controller
#define	HwPORTCFG1_LCDU8_1						Hw12									// Data Bus for Camera Module
#define	HwPORTCFG1_LCDU8_2						Hw13									// General Purpose I/O
#define	HwPORTCFG1_LCDU8_3						(Hw13+Hw12)								// SPI Slave Controller for Channel 2 (y=2)
#define	HwPORTCFG1_LCD47_0						HwZERO									// Data Bus for LCD Controller (CCIR Interface)
#define	HwPORTCFG1_LCD47_1						Hw10									// Data Bus for LCD Controller (Memory Interface)
#define	HwPORTCFG1_LCD47_2						Hw11									// General Purpose I/O
#define	HwPORTCFG1_LCD03_0						HwZERO									// Data Bus for LCD Controller (CCIR Interface)
#define	HwPORTCFG1_LCD03_1						Hw8										// Data Bus for LCD Controller (Memory Interface)
#define	HwPORTCFG1_LCD03_2						Hw9										// General Purpose I/O
#define	HwPORTCFG1_LCD03_3						(Hw9+Hw8)								// Timer Counter Output 3
#define	HwPORTCFG1_LCDC_0						HwZERO									// LCD Controller (CCIR Interface)
#define	HwPORTCFG1_LCDC_1						Hw6										// LCD Controller (Memory Interface)
#define	HwPORTCFG1_LCDC_2						Hw7										// General Purpose I/O
#define	HwPORTCFG1_LCDC_3						(Hw7+Hw6)								// Timer Counter Output 5
                                    			
#define	HwPORTCFG2								*(volatile unsigned long *)0xF005A008	// R/W, Port Configuration Register 2
#define	HwPORTCFG2_SPISEL_0						HwZERO									//
#define	HwPORTCFG2_SPISEL_1						Hw14									//
#define	HwPORTCFG2_SPISEL_2						Hw15									//
#define	HwPORTCFG2_MSISEL_0						HwZERO									//
#define	HwPORTCFG2_MSISEL_1						Hw12									//
#define	HwPORTCFG2_MSISEL_2						Hw13									//
#define	HwPORTCFG2_SDISEL_0						HwZERO									//
#define	HwPORTCFG2_SDISEL_1						Hw10									//
#define	HwPORTCFG2_SDISEL_2						Hw11									//
#define	HwPORTCFG2_SDISEL_3						(Hw11+Hw10)								//
#define HwPORTCFG2_LSEL_CCIR					Hw8										// This is for selecting the operation interface of LCD data bus. If '0', the interface type of LPD I/O's is CCIR interface type. Otherwise, the interface type of LPD I/O's is memory interface type
#define HwPORTCFG2_LSEL_MEM						Hw8										// This is for selecting the operation interface of LCD data bus. If '0', the interface type of LPD I/O's is CCIR interface type. Otherwise, the interface type of LPD I/O's is memory interface type
#define	HwPORTCFG2_UART0_0						HwZERO									//
#define	HwPORTCFG2_UART0_1						Hw6										//
#define	HwPORTCFG2_UART0_2						Hw7										//
#define	HwPORTCFG2_UART0_3						(Hw7+Hw6)								//
#define	HwPORTCFG2_UARTC0_0						HwZERO									//
#define	HwPORTCFG2_UARTC0_1						Hw4										//
#define	HwPORTCFG2_UARTC0_2						Hw5										//
#define	HwPORTCFG2_UARTC0_3						(Hw5+Hw4)								//
#define	HwPORTCFG2_UART1_0						HwZERO									//
#define	HwPORTCFG2_UART1_1						Hw2										//
#define	HwPORTCFG2_UART1_2						Hw3										//
#define	HwPORTCFG2_UART1_3						(Hw3+Hw2)								//
#define	HwPORTCFG2_UARTC1_0						HwZERO									//
#define	HwPORTCFG2_UARTC1_1						Hw0										//
#define	HwPORTCFG2_UARTC1_2						Hw1										//
#define	HwPORTCFG2_UARTC1_3						(Hw1+Hw0)								//
                                    			
#define	HwPORTCFG3								*(volatile unsigned long *)0xF005A00C	// R/W, Port Configuration Register 3
#define	HwPORTCFG3_SDO1_0						HwZERO									// Output data signal for GSIO Channel 1
#define	HwPORTCFG3_SDO1_1						Hw26									// Data Signal of SD Controller for channel 3
#define	HwPORTCFG3_SDO1_2						Hw27									// GPIO signal
#define	HwPORTCFG3_SDO1_3						(Hw27+Hw26)								// GPIO signal
#define	HwPORTCFG3_SDI1_0						HwZERO									// Input data signal for GSIO channel 1
#define	HwPORTCFG3_SDI1_1						Hw24									// Data signal of SD controller for channel 3
#define	HwPORTCFG3_SDI1_2						Hw25									// GPIO signal
#define	HwPORTCFG3_SDI1_3						(Hw25+Hw24)								// GPIO signal
#define	HwPORTCFG3_SCK1_0						HwZERO									// Clock signal for GSIO channel 1
#define	HwPORTCFG3_SCK1_1						Hw22									// Data signal of SD controller for channel 3
#define	HwPORTCFG3_SCK1_2						Hw23									// GPIO signal
#define	HwPORTCFG3_SCK1_3						(Hw23+Hw22)								// GPIO signal
#define	HwPORTCFG3_FRM1_0						HwZERO									// Frame signal for GSIO channel 1
#define	HwPORTCFG3_FRM1_1						Hw20									// Data signal of SD controller for channel 3
#define	HwPORTCFG3_FRM1_2						Hw21									// GPIO signal
#define	HwPORTCFG3_FRM1_3						(Hw21+Hw20)								// GPIO signal
#define	HwPORTCFG3_SDO0_0						HwZERO									// Output data signal for GSIO channel 1
#define	HwPORTCFG3_SDO0_1						Hw18									// GPIO group E signal
#define	HwPORTCFG3_SDO0_2						Hw19									// Output data for SPI slave controller channel 0
#define	HwPORTCFG3_SDO0_3						(Hw19+Hw18)								// GPIO signal
#define	HwPORTCFG3_SDI0_0						HwZERO									// Input data signal for GSIO channel 1
#define	HwPORTCFG3_SDI0_1						Hw16									// GPIO group E signal
#define	HwPORTCFG3_SDI0_2						Hw17									// Input data for SPI slave controller channel 0
#define	HwPORTCFG3_SDI0_3						(Hw17+Hw16)								// GPIO signal
#define	HwPORTCFG3_SCK0_0						HwZERO									// Clock signal for GSIO channel 1
#define	HwPORTCFG3_SCK0_1						Hw14									// GPIO group E signal
#define	HwPORTCFG3_SCK0_2						Hw15									// Clock signal for SPI slave controller channel 0
#define	HwPORTCFG3_SCK0_3						(Hw15+Hw14)								// GPIO signal
#define	HwPORTCFG3_FRM0_0						HwZERO									// Frame signal for GSIO channel 1
#define	HwPORTCFG3_FRM0_1						Hw12									// GPIO group E signal
#define	HwPORTCFG3_FRM0_2						Hw13									// Frame signal for SPI slave controller channel 0
#define	HwPORTCFG3_FRM0_3						(Hw13+Hw12)								// GPIO signal
#define	HwPORTCFG3_CCKO_0						HwZERO									// GPIO group A signal
#define	HwPORTCFG3_CCKO_1						Hw10									// Camera Clock output signal
#define	HwPORTCFG3_I2C1_0						HwZERO									// GPIO group A signal
#define	HwPORTCFG3_I2C1_1						Hw8										// I2C channel 1 signal
#define	HwPORTCFG3_HDD3_0						HwZERO									//
#define	HwPORTCFG3_HDD3_1						Hw6										//
#define	HwPORTCFG3_HDD3_2						Hw7										//
#define	HwPORTCFG3_HDD3_3						(Hw7+Hw6)								// LCD data output for RGB(CCIR) interface
#define	HwPORTCFG3_HDD2_0						HwZERO									//
#define	HwPORTCFG3_HDD2_1						Hw4										//
#define	HwPORTCFG3_HDD2_2						Hw5										//
#define	HwPORTCFG3_HDD2_3						(Hw5+Hw4)								//
#define	HwPORTCFG3_HDD1_0						HwZERO									//
#define	HwPORTCFG3_HDD1_1						Hw2										//
#define	HwPORTCFG3_HDD1_2						Hw3										//
#define	HwPORTCFG3_HDD1_3						(Hw3+Hw2)								//
#define	HwPORTCFG3_HDD0_0						HwZERO									//
#define	HwPORTCFG3_HDD0_1						Hw0										//
#define	HwPORTCFG3_HDD0_2						Hw1										//
                                    			
#define	HwGPADAT								*(volatile unsigned long *)0xF005A020	// R/W, GPA Data Register
                                    			
#define	HwGPAEN								*(volatile unsigned long *)0xF005A024	// R/W, GPA Output Enable Register
                                    			
#define	HwGPASET								*(volatile unsigned long *)0xF005A028	// W, OR function on GPA Output Data
                                    			
#define	HwGPACLR								*(volatile unsigned long *)0xF005A02C	// W, BIC function on GPA Output Data
                                    			
#define	HwGPAXOR								*(volatile unsigned long *)0xF005A030	// W, XOR function on GPA Output Data
                                    			
#define	HwGPBDAT								*(volatile unsigned long *)0xF005A040	// R/W, GPB Data Register
                                    			
#define	HwGPBEN								*(volatile unsigned long *)0xF005A044	// R/W, GPB Output Enable Register
                                    			
#define	HwGPBSET								*(volatile unsigned long *)0xF005A048	// W, OR function on GPB Output Data
                                    			
#define	HwGPBCLR								*(volatile unsigned long *)0xF005A04C	// W, BIC function on GPB Output Data
                                    			
#define	HwGPBXOR								*(volatile unsigned long *)0xF005A050	// W, XOR function on GPB Output Data
                                    			
#define	HwGPCDAT								*(volatile unsigned long *)0xF005A060	// R/W, GPC Data Register
                                    			
#define	HwGPCEN								*(volatile unsigned long *)0xF005A064	// R/W, GPC Output Enable Register
                                    			
#define	HwGPCSET								*(volatile unsigned long *)0xF005A068	// W, OR function on GPC Output Data
                                    			
#define	HwGPCCLR								*(volatile unsigned long *)0xF005A06C	// W, BIC function on GPC Output Data
                                    			
#define	HwGPCXOR								*(volatile unsigned long *)0xF005A070	// W, XOR function on GPC Output Data
                                    			
#define	HwGPDDAT								*(volatile unsigned long *)0xF005A080	// R/W, GPD Data Register
                                    			
#define	HwGPDEN									*(volatile unsigned long *)0xF005A084	// R/W, GPD Output Enable Register
                                    			
#define	HwGPDSET								*(volatile unsigned long *)0xF005A088	// W, OR function on GPD Output Data
                                    			
#define	HwGPDCLR								*(volatile unsigned long *)0xF005A08C	// W, BIC function on GPD Output Data
                                    			
#define	HwGPDXOR								*(volatile unsigned long *)0xF005A090	// W, XOR function on GPD Output Data
                                    			
#define	HwGPEDAT								*(volatile unsigned long *)0xF005A0A0	// R/W, GPE Data Register
                                    			
#define	HwGPEEN									*(volatile unsigned long *)0xF005A0A4	// R/W, GPE Output Enable Register
                                    			
#define	HwGPESET								*(volatile unsigned long *)0xF005A0A8	// W, OR function on GPE Output Data
                                    			
#define	HwGPECLR								*(volatile unsigned long *)0xF005A0AC	// W, BIC function on GPE Output Data
                                    			
#define	HwGPEXOR								*(volatile unsigned long *)0xF005A0B0	// W, XOR function on GPE Output Data
                                    			
#define	HwCPUD0									*(volatile unsigned long *)0xF005A0C0	// R/W, Pull-Up/Down Control Register 0
#define	HwCPUD0_CPD7_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD7_1							Hw30									// Pull-up enabled
#define	HwCPUD0_CPD7_2							Hw31									// Pull-down enabled
#define	HwCPUD0_CPD7_3							(Hw31+Hw30)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPD6_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD6_1							Hw28									// Pull-up enabled
#define	HwCPUD0_CPD6_2							Hw29									// Pull-down enabled
#define	HwCPUD0_CPD6_3							(Hw29+Hw28)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPD5_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD5_1							Hw26									// Pull-up enabled
#define	HwCPUD0_CPD5_2							Hw27									// Pull-down enabled
#define	HwCPUD0_CPD5_3							(Hw27+Hw26)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPD4_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD4_1							Hw24									// Pull-up enabled
#define	HwCPUD0_CPD4_2							Hw25									// Pull-down enabled
#define	HwCPUD0_CPD4_3							(Hw25+Hw24)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPD3_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD3_1							Hw22									// Pull-up enabled
#define	HwCPUD0_CPD3_2							Hw23									// Pull-down enabled
#define	HwCPUD0_CPD3_3							(Hw23+Hw22)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPD2_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD2_1							Hw20									// Pull-up enabled
#define	HwCPUD0_CPD2_2							Hw21									// Pull-down enabled
#define	HwCPUD0_CPD2_3							(Hw21+Hw20)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPD1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD1_1							Hw18									// Pull-up enabled
#define	HwCPUD0_CPD1_2							Hw19									// Pull-down enabled
#define	HwCPUD0_CPD1_3							(Hw19+Hw18)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPD0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPD0_1							Hw16									// Pull-up enabled
#define	HwCPUD0_CPD0_2							Hw17									// Pull-down enabled
#define	HwCPUD0_CPD0_3							(Hw17+Hw16)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CPWDN_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CPWDN_1							Hw14									// Pull-up enabled
#define	HwCPUD0_CPWDN_2							Hw15									// Pull-down enabled
#define	HwCPUD0_CPWDN_3							(Hw15+Hw14)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CHS_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CHS_1							Hw12									// Pull-up enabled
#define	HwCPUD0_CHS_2							Hw13									// Pull-down enabled
#define	HwCPUD0_CHS_3							(Hw13+Hw12)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CVS_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CVS_1							Hw10									// Pull-up enabled
#define	HwCPUD0_CVS_2							Hw11									// Pull-down enabled
#define	HwCPUD0_CVS_3							(Hw11+Hw10)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_CCK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_CCK_1							Hw8										// Pull-up enabled
#define	HwCPUD0_CCK_2							Hw9										// Pull-down enabled
#define	HwCPUD0_CCK_3							(Hw9+Hw8)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_LBIAS_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_LBIAS_1							Hw6										// Pull-up enabled
#define	HwCPUD0_LBIAS_2							Hw7										// Pull-down enabled
#define	HwCPUD0_LBIAS_3							(Hw7+Hw6)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_LCK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_LCK_1							Hw4										// Pull-up enabled
#define	HwCPUD0_LCK_2							Hw5										// Pull-down enabled
#define	HwCPUD0_LCK_3							(Hw5+Hw4)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_LHS_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_LHS_1							Hw2										// Pull-up enabled
#define	HwCPUD0_LHS_2							Hw3										// Pull-down enabled
#define	HwCPUD0_LHS_3							(Hw3+Hw2)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD0_LVS_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD0_LVS_1							Hw0										// Pull-up enabled
#define	HwCPUD0_LVS_2							Hw1										// Pull-down enabled
#define	HwCPUD0_LVS_3							(Hw1+Hw0)								// Both pull-up and pull-down are enabled - you should not write like this
                                    			
#define	HwCPUD1									*(volatile unsigned long *)0xF005A0C4	// R/W, Pull-Up/Down Control Register 1
#define	HwCPUD1_LPD15_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD15_1							Hw30									// Pull-up enabled
#define	HwCPUD1_LPD15_2							Hw31									// Pull-down enabled
#define	HwCPUD1_LPD15_3							(Hw31+Hw30)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD14_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD14_1							Hw28									// Pull-up enabled
#define	HwCPUD1_LPD14_2							Hw29									// Pull-down enabled
#define	HwCPUD1_LPD14_3							(Hw29+Hw28)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD13_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD13_1							Hw26									// Pull-up enabled
#define	HwCPUD1_LPD13_2							Hw27									// Pull-down enabled
#define	HwCPUD1_LPD13_3							(Hw27+Hw26)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD12_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD12_1							Hw24									// Pull-up enabled
#define	HwCPUD1_LPD12_2							Hw25									// Pull-down enabled
#define	HwCPUD1_LPD12_3							(Hw25+Hw24)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD11_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD11_1							Hw22									// Pull-up enabled
#define	HwCPUD1_LPD11_2							Hw23									// Pull-down enabled
#define	HwCPUD1_LPD11_3							(Hw23+Hw22)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD10_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD10_1							Hw20									// Pull-up enabled
#define	HwCPUD1_LPD10_2							Hw21									// Pull-down enabled
#define	HwCPUD1_LPD10_3							(Hw21+Hw20)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD9_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD9_1							Hw18									// Pull-up enabled
#define	HwCPUD1_LPD9_2							Hw19									// Pull-down enabled
#define	HwCPUD1_LPD9_3							(Hw19+Hw18)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD8_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD8_1							Hw16									// Pull-up enabled
#define	HwCPUD1_LPD8_2							Hw17									// Pull-down enabled
#define	HwCPUD1_LPD8_3							(Hw17+Hw16)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD7_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD7_1							Hw14									// Pull-up enabled
#define	HwCPUD1_LPD7_2							Hw15									// Pull-down enabled
#define	HwCPUD1_LPD7_3							(Hw15+Hw14)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD6_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD6_1							Hw12									// Pull-up enabled
#define	HwCPUD1_LPD6_2							Hw13									// Pull-down enabled
#define	HwCPUD1_LPD6_3							(Hw13+Hw12)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD5_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD5_1							Hw10									// Pull-up enabled
#define	HwCPUD1_LPD5_2							Hw11									// Pull-down enabled
#define	HwCPUD1_LPD5_3							(Hw11+Hw10)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD4_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD4_1							Hw8										// Pull-up enabled
#define	HwCPUD1_LPD4_2							Hw9										// Pull-down enabled
#define	HwCPUD1_LPD4_3							(Hw9+Hw8)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD3_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD3_1							Hw6										// Pull-up enabled
#define	HwCPUD1_LPD3_2							Hw7										// Pull-down enabled
#define	HwCPUD1_LPD3_3							(Hw7+Hw6)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD2_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD2_1							Hw4										// Pull-up enabled
#define	HwCPUD1_LPD2_2							Hw5										// Pull-down enabled
#define	HwCPUD1_LPD2_3							(Hw5+Hw4)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD1_1							Hw2										// Pull-up enabled
#define	HwCPUD1_LPD1_2							Hw3										// Pull-down enabled
#define	HwCPUD1_LPD1_3							(Hw3+Hw2)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD1_LPD0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD1_LPD0_1							Hw0										// Pull-up enabled
#define	HwCPUD1_LPD0_2							Hw1										// Pull-down enabled
#define	HwCPUD1_LPD0_3							(Hw1+Hw0)								// Both pull-up and pull-down are enabled - you should not write like this
                                    			
#define	HwCPUD2									*(volatile unsigned long *)0xF005A0C8	// R/W, Pull-Up/Down Control Register 2
#define	HwCPUD2_HDDXD15_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD15_1						Hw30									// Pull-up enabled
#define	HwCPUD2_HDDXD15_2						Hw31									// Pull-down enabled
#define	HwCPUD2_HDDXD15_3						(Hw31+Hw30)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD14_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD14_1						Hw28									// Pull-up enabled
#define	HwCPUD2_HDDXD14_2						Hw29									// Pull-down enabled
#define	HwCPUD2_HDDXD14_3						(Hw29+Hw28)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD13_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD13_1						Hw26									// Pull-up enabled
#define	HwCPUD2_HDDXD13_2						Hw27									// Pull-down enabled
#define	HwCPUD2_HDDXD13_3						(Hw27+Hw26)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD12_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD12_1						Hw24									// Pull-up enabled
#define	HwCPUD2_HDDXD12_2						Hw25									// Pull-down enabled
#define	HwCPUD2_HDDXD12_3						(Hw25+Hw24)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD11_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD11_1						Hw22									// Pull-up enabled
#define	HwCPUD2_HDDXD11_2						Hw23									// Pull-down enabled
#define	HwCPUD2_HDDXD11_3						(Hw23+Hw22)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD10_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD10_1						Hw20									// Pull-up enabled
#define	HwCPUD2_HDDXD10_2						Hw21									// Pull-down enabled
#define	HwCPUD2_HDDXD10_3						(Hw21+Hw20)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD9_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD9_1						Hw18									// Pull-up enabled
#define	HwCPUD2_HDDXD9_2						Hw19									// Pull-down enabled
#define	HwCPUD2_HDDXD9_3						(Hw19+Hw18)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD8_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD8_1						Hw16									// Pull-up enabled
#define	HwCPUD2_HDDXD8_2						Hw17									// Pull-down enabled
#define	HwCPUD2_HDDXD8_3						(Hw17+Hw16)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD7_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD7_1						Hw14									// Pull-up enabled
#define	HwCPUD2_HDDXD7_2						Hw15									// Pull-down enabled
#define	HwCPUD2_HDDXD7_3						(Hw15+Hw14)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD6_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD6_1						Hw12									// Pull-up enabled
#define	HwCPUD2_HDDXD6_2						Hw13									// Pull-down enabled
#define	HwCPUD2_HDDXD6_3						(Hw13+Hw12)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD5_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD5_1						Hw10									// Pull-up enabled
#define	HwCPUD2_HDDXD5_2						Hw11									// Pull-down enabled
#define	HwCPUD2_HDDXD5_3						(Hw11+Hw10)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD4_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD4_1						Hw8										// Pull-up enabled
#define	HwCPUD2_HDDXD4_2						Hw9										// Pull-down enabled
#define	HwCPUD2_HDDXD4_3						(Hw9+Hw8)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD3_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD3_1						Hw6										// Pull-up enabled
#define	HwCPUD2_HDDXD3_2						Hw7										// Pull-down enabled
#define	HwCPUD2_HDDXD3_3						(Hw7+Hw6)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD2_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD2_1						Hw4										// Pull-up enabled
#define	HwCPUD2_HDDXD2_2						Hw5										// Pull-down enabled
#define	HwCPUD2_HDDXD2_3						(Hw5+Hw4)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD1_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD1_1						Hw2										// Pull-up enabled
#define	HwCPUD2_HDDXD1_2						Hw3										// Pull-down enabled
#define	HwCPUD2_HDDXD1_3						(Hw3+Hw2)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD2_HDDXD0_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD2_HDDXD0_1						Hw0										// Pull-up enabled
#define	HwCPUD2_HDDXD0_2						Hw1										// Pull-down enabled
#define	HwCPUD2_HDDXD0_3						(Hw1+Hw0)								// Both pull-up and pull-down are enabled - you should not write like this
                                    			
#define	HwCPUD3									*(volatile unsigned long *)0xF005A0CC	// R/W, Pull-Up/Down Control Register 3
#define	HwCPUD3_XDL								Hw29									// The XDL field controls the lower 16 bits data bus of the main memory bus for external memory controller
#define	HwCPUD3_VXD								Hw28									// The VXD field controls all the data bus of the video memory bus for SDRAM channel 1
#define	HwCPUD3_EINT3_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_EINT3_1							Hw26									// Pull-up enabled
#define	HwCPUD3_EINT3_2							Hw27									// Pull-down enabled
#define	HwCPUD3_EINT3_3							(Hw27+Hw26)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_EINT2_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_EINT2_1							Hw24									// Pull-up enabled
#define	HwCPUD3_EINT2_2							Hw25									// Pull-down enabled
#define	HwCPUD3_EINT2_3							(Hw25+Hw24)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_EINT1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_EINT1_1							Hw22									// Pull-up enabled
#define	HwCPUD3_EINT1_2							Hw23									// Pull-down enabled
#define	HwCPUD3_EINT1_3							(Hw23+Hw22)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_EINT0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_EINT0_1							Hw20									// Pull-up enabled
#define	HwCPUD3_EINT0_2							Hw21									// Pull-down enabled
#define	HwCPUD3_EINT0_3							(Hw21+Hw20)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDRDY_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDRDY_1						Hw18									// Pull-up enabled
#define	HwCPUD3_HDDRDY_2						Hw19									// Pull-down enabled
#define	HwCPUD3_HDDRDY_3						(Hw19+Hw18)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDAK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDAK_1							Hw16									// Pull-up enabled
#define	HwCPUD3_HDDAK_2							Hw17									// Pull-down enabled
#define	HwCPUD3_HDDAK_3							(Hw17+Hw16)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDRQ_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDRQ_1							Hw14									// Pull-up enabled
#define	HwCPUD3_HDDRQ_2							Hw15									// Pull-down enabled
#define	HwCPUD3_HDDRQ_3							(Hw15+Hw14)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDIOW_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDIOW_1						Hw12									// Pull-up enabled
#define	HwCPUD3_HDDIOW_2						Hw13									// Pull-down enabled
#define	HwCPUD3_HDDIOW_3						(Hw13+Hw12)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDIOR_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDIOR_1						Hw10									// Pull-up enabled
#define	HwCPUD3_HDDIOR_2						Hw11									// Pull-down enabled
#define	HwCPUD3_HDDIOR_3						(Hw11+Hw10)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDCSN1_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDCSN1_1						Hw8										// Pull-up enabled
#define	HwCPUD3_HDDCSN1_2						Hw9										// Pull-down enabled
#define	HwCPUD3_HDDCSN1_3						(Hw9+Hw8)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDCSN0_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDCSN0_1						Hw6										// Pull-up enabled
#define	HwCPUD3_HDDCSN0_2						Hw7										// Pull-down enabled
#define	HwCPUD3_HDDCSN0_3						(Hw7+Hw6)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDXA2_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDXA2_1						Hw4										// Pull-up enabled
#define	HwCPUD3_HDDXA2_2						Hw5										// Pull-down enabled
#define	HwCPUD3_HDDXA2_3						(Hw5+Hw4)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDXA1_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDXA1_1						Hw2										// Pull-up enabled
#define	HwCPUD3_HDDXA1_2						Hw3										// Pull-down enabled
#define	HwCPUD3_HDDXA1_3						(Hw3+Hw2)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD3_HDDXA0_0						HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD3_HDDXA0_1						Hw0										// Pull-up enabled
#define	HwCPUD3_HDDXA0_2						Hw1										// Pull-down enabled
#define	HwCPUD3_HDDXA0_3						(Hw1+Hw0)								// Both pull-up and pull-down are enabled - you should not write like this
                                    			
#define	HwCPUD4									*(volatile unsigned long *)0xF005A0D0	// R/W, Pull-Up/Down Control Register 4
#define	HwCPUD4_XD31_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD31_1							Hw30									// Pull-up enabled
#define	HwCPUD4_XD31_2							Hw31									// Pull-down enabled
#define	HwCPUD4_XD31_3							(Hw31+Hw30)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD30_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD30_1							Hw28									// Pull-up enabled
#define	HwCPUD4_XD30_2							Hw29									// Pull-down enabled
#define	HwCPUD4_XD30_3							(Hw29+Hw28)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD29_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD29_1							Hw26									// Pull-up enabled
#define	HwCPUD4_XD29_2							Hw27									// Pull-down enabled
#define	HwCPUD4_XD29_3							(Hw27+Hw26)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD28_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD28_1							Hw24									// Pull-up enabled
#define	HwCPUD4_XD28_2							Hw25									// Pull-down enabled
#define	HwCPUD4_XD28_3							(Hw25+Hw24)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD27_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD27_1							Hw22									// Pull-up enabled
#define	HwCPUD4_XD27_2							Hw23									// Pull-down enabled
#define	HwCPUD4_XD27_3							(Hw23+Hw22)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD26_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD26_1							Hw20									// Pull-up enabled
#define	HwCPUD4_XD26_2							Hw21									// Pull-down enabled
#define	HwCPUD4_XD26_3							(Hw21+Hw20)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD25_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD25_1							Hw18									// Pull-up enabled
#define	HwCPUD4_XD25_2							Hw19									// Pull-down enabled
#define	HwCPUD4_XD25_3							(Hw19+Hw18)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD24_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD24_1							Hw16									// Pull-up enabled
#define	HwCPUD4_XD24_2							Hw17									// Pull-down enabled
#define	HwCPUD4_XD24_3							(Hw17+Hw16)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD23_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD23_1							Hw14									// Pull-up enabled
#define	HwCPUD4_XD23_2							Hw15									// Pull-down enabled
#define	HwCPUD4_XD23_3							(Hw15+Hw14)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD22_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD22_1							Hw12									// Pull-up enabled
#define	HwCPUD4_XD22_2							Hw13									// Pull-down enabled
#define	HwCPUD4_XD22_3							(Hw13+Hw12)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD21_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD21_1							Hw10									// Pull-up enabled
#define	HwCPUD4_XD21_2							Hw11									// Pull-down enabled
#define	HwCPUD4_XD21_3							(Hw11+Hw10)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD20_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD20_1							Hw8										// Pull-up enabled
#define	HwCPUD4_XD20_2							Hw9										// Pull-down enabled
#define	HwCPUD4_XD20_3							(Hw9+Hw8)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD19_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD19_1							Hw6										// Pull-up enabled
#define	HwCPUD4_XD19_2							Hw7										// Pull-down enabled
#define	HwCPUD4_XD19_3							(Hw7+Hw6)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD18_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD18_1							Hw4										// Pull-up enabled
#define	HwCPUD4_XD18_2							Hw5										// Pull-down enabled
#define	HwCPUD4_XD18_3							(Hw5+Hw4)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD17_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD17_1							Hw2										// Pull-up enabled
#define	HwCPUD4_XD17_2							Hw3										// Pull-down enabled
#define	HwCPUD4_XD17_3							(Hw3+Hw2)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD4_XD16_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD4_XD16_1							Hw0										// Pull-up enabled
#define	HwCPUD4_XD16_2							Hw1										// Pull-down enabled
#define	HwCPUD4_XD16_3							(Hw1+Hw0)								// Both pull-up and pull-down are enabled - you should not write like this
                                    			
#define	HwCPUD5									*(volatile unsigned long *)0xF005A0D4	// R/W, Pull-Up/Down Control Register 5
#define	HwCPUD5_CBCLK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_CBCLK_1							Hw30									// Pull-up enabled
#define	HwCPUD5_CBCLK_2							Hw31									// Pull-down enabled
#define	HwCPUD5_CBCLK_3							(Hw31+Hw30)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_CLRCK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_CLRCK_1							Hw28									// Pull-up enabled
#define	HwCPUD5_CLRCK_2							Hw29									// Pull-down enabled
#define	HwCPUD5_CLRCK_3							(Hw29+Hw28)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_CDAI_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_CDAI_1							Hw26									// Pull-up enabled
#define	HwCPUD5_CDAI_2							Hw27									// Pull-down enabled
#define	HwCPUD5_CDAI_3							(Hw27+Hw26)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_DAO_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_DAO_1							Hw24									// Pull-up enabled
#define	HwCPUD5_DAO_2							Hw25									// Pull-down enabled
#define	HwCPUD5_DA0_3							(Hw25+Hw24)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_DAI_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_DAI_1							Hw22									// Pull-up enabled
#define	HwCPUD5_DAI_2							Hw23									// Pull-down enabled
#define	HwCPUD5_DAI_3							(Hw23+Hw22)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_MCLK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_MCLK_1							Hw20									// Pull-up enabled
#define	HwCPUD5_MCLK_2							Hw21									// Pull-down enabled
#define	HwCPUD5_MCLK_3							(Hw21+Hw20)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_LRCK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_LRCK_1							Hw18									// Pull-up enabled
#define	HwCPUD5_LRCK_2							Hw19									// Pull-down enabled
#define	HwCPUD5_LRCK_3							(Hw19+Hw18)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_BCLK_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_BCLK_1							Hw16									// Pull-up enabled
#define	HwCPUD5_BCLK_2							Hw17									// Pull-down enabled
#define	HwCPUD5_BCLK_3							(Hw17+Hw16)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_SDO1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_SDO1_1							Hw14									// Pull-up enabled
#define	HwCPUD5_SDO1_2							Hw15									// Pull-down enabled
#define	HwCPUD5_SDO1_3							(Hw15+Hw14)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_SDI1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_SDI1_1							Hw12									// Pull-up enabled
#define	HwCPUD5_SDI1_2							Hw13									// Pull-down enabled
#define	HwCPUD5_SDI1_3							(Hw13+Hw12)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_SCK1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_SCK1_1							Hw10									// Pull-up enabled
#define	HwCPUD5_SCK1_2							Hw11									// Pull-down enabled
#define	HwCPUD5_SCK1_3							(Hw11+Hw10)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_FRM1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_FRM1_1							Hw8										// Pull-up enabled
#define	HwCPUD5_FRM1_2							Hw9										// Pull-down enabled
#define	HwCPUD5_FRM1_3							(Hw9+Hw8)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_SDO0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_SDO0_1							Hw6										// Pull-up enabled
#define	HwCPUD5_SDO0_2							Hw7										// Pull-down enabled
#define	HwCPUD5_SDO0_3							(Hw7+Hw6)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_SDI0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_SDI0_1							Hw4										// Pull-up enabled
#define	HwCPUD5_SDI0_2							Hw5										// Pull-down enabled
#define	HwCPUD5_SDI0_3							(Hw5+Hw4)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_SCK0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_SCK0_1							Hw2										// Pull-up enabled
#define	HwCPUD5_SCK0_2							Hw3										// Pull-down enabled
#define	HwCPUD5_SCK0_3							(Hw3+Hw2)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD5_FRM0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD5_FRM0_1							Hw0										// Pull-up enabled
#define	HwCPUD5_FRM0_2							Hw1										// Pull-down enabled
#define	HwCPUD5_FRM0_3							(Hw1+Hw0)								// Both pull-up and pull-down are enabled - you should not write like this
                                    			
#define	HwCPUD6									*(volatile unsigned long *)0xF005A0D8	// R/W, Pull-Up/Down Control Register 6
#define	HwCPUD6_GPA15_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA15_1							Hw30									// Pull-up enabled
#define	HwCPUD6_GPA15_2							Hw31									// Pull-down enabled
#define	HwCPUD6_GPA15_3							(Hw31+Hw30)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA14_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA14_1							Hw28									// Pull-up enabled
#define	HwCPUD6_GPA14_2							Hw29									// Pull-down enabled
#define	HwCPUD6_GPA14_3							(Hw29+Hw28)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA13_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA13_1							Hw26									// Pull-up enabled
#define	HwCPUD6_GPA13_2							Hw27									// Pull-down enabled
#define	HwCPUD6_GPA13_3							(Hw27+Hw26)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA12_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA12_1							Hw24									// Pull-up enabled
#define	HwCPUD6_GPA12_2							Hw25									// Pull-down enabled
#define	HwCPUD6_GPA12_3							(Hw25+Hw24)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA11_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA11_1							Hw22									// Pull-up enabled
#define	HwCPUD6_GPA11_2							Hw23									// Pull-down enabled
#define	HwCPUD6_GPA11_3							(Hw23+Hw22)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA10_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA10_1							Hw20									// Pull-up enabled
#define	HwCPUD6_GPA10_2							Hw21									// Pull-down enabled
#define	HwCPUD6_GPA10_3							(Hw21+Hw20)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA9_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA9_1							Hw18									// Pull-up enabled
#define	HwCPUD6_GPA9_2							Hw19									// Pull-down enabled
#define	HwCPUD6_GPA9_3							(Hw19+Hw18)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA8_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA8_1							Hw16									// Pull-up enabled
#define	HwCPUD6_GPA8_2							Hw17									// Pull-down enabled
#define	HwCPUD6_GPA8_3							(Hw17+Hw16)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA7_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA7_1							Hw14									// Pull-up enabled
#define	HwCPUD6_GPA7_2							Hw15									// Pull-down enabled
#define	HwCPUD6_GPA7_3							(Hw15+Hw14)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA6_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA6_1							Hw12									// Pull-up enabled
#define	HwCPUD6_GPA6_2							Hw13									// Pull-down enabled
#define	HwCPUD6_GPA6_3							(Hw13+Hw12)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA5_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA5_1							Hw10									// Pull-up enabled
#define	HwCPUD6_GPA5_2							Hw11									// Pull-down enabled
#define	HwCPUD6_GPA5_3							(Hw11+Hw10)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA4_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA4_1							Hw8										// Pull-up enabled
#define	HwCPUD6_GPA4_2							Hw9										// Pull-down enabled
#define	HwCPUD6_GPA4_3							(Hw9+Hw8)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA3_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA3_1							Hw6										// Pull-up enabled
#define	HwCPUD6_GPA3_2							Hw7										// Pull-down enabled
#define	HwCPUD6_GPA3_3							(Hw7+Hw6)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA2_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA2_1							Hw4										// Pull-up enabled
#define	HwCPUD6_GPA2_2							Hw5										// Pull-down enabled
#define	HwCPUD6_GPA2_3							(Hw5+Hw4)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA1_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA1_1							Hw2										// Pull-up enabled
#define	HwCPUD6_GPA1_2							Hw3										// Pull-down enabled
#define	HwCPUD6_GPA1_3							(Hw3+Hw2)								// Both pull-up and pull-down are enabled - you should not write like this
#define	HwCPUD6_GPA0_0							HwZERO									// Neither pull-up or pull-down is enable
#define	HwCPUD6_GPA0_1							Hw0										// Pull-up enabled
#define	HwCPUD6_GPA0_2							Hw1										// Pull-down enabled
#define	HwCPUD6_GPA0_3							(Hw1+Hw0)								// Both pull-up and pull-down are enabled - you should not write like this
                                    			
#define	HwEINTSEL								*(volatile unsigned long *)0xF005A0E0	// R/W, External Interrupt Select Register
#define	HwEINTSEL_EINT3SEL_EINT0				HwZERO									//
#define	HwEINTSEL_EINT3SEL_EINT1				Hw24									//
#define	HwEINTSEL_EINT3SEL_EINT2				Hw25									//		
#define	HwEINTSEL_EINT3SEL_EINT3				(Hw25+Hw24)								//
#define	HwEINTSEL_EINT3SEL_GPA0					Hw26									//
#define	HwEINTSEL_EINT3SEL_GPA1					(Hw26+Hw24)								//
#define	HwEINTSEL_EINT3SEL_GPA2					(Hw26+Hw25)								//
#define	HwEINTSEL_EINT3SEL_GPA3					(Hw26+Hw25+Hw24)						//
#define	HwEINTSEL_EINT3SEL_GPA4					Hw27									//
#define	HwEINTSEL_EINT3SEL_GPA5					(Hw27+Hw24)								//
#define	HwEINTSEL_EINT3SEL_GPA6					(Hw27+Hw25)								//
#define	HwEINTSEL_EINT3SEL_GPA7					(Hw27+Hw25+Hw24)						//
#define	HwEINTSEL_EINT3SEL_GPE0					(Hw27+Hw26)								//
#define	HwEINTSEL_EINT3SEL_GPE1					(Hw27+Hw26+Hw24)						//
#define	HwEINTSEL_EINT3SEL_GPE2					(Hw27+Hw26+Hw25)						//
#define	HwEINTSEL_EINT3SEL_GPE3					(Hw27+Hw26+Hw25+Hw24)					//
#define	HwEINTSEL_EINT3SEL_GPE4					Hw28									//
#define	HwEINTSEL_EINT3SEL_GPE5					(Hw28+Hw24)								//
#define	HwEINTSEL_EINT3SEL_GPE6					(Hw28+Hw25)								//
#define	HwEINTSEL_EINT3SEL_GPE7					(Hw28+Hw25+Hw25)						//
#define	HwEINTSEL_EINT3SEL_GPE8					(Hw28+Hw26)								//
#define	HwEINTSEL_EINT3SEL_GPE9					(Hw28+Hw26+Hw24)						//
#define	HwEINTSEL_EINT3SEL_GPE10				(Hw28+Hw26+Hw25)						//
#define	HwEINTSEL_EINT3SEL_GPE11				(Hw28+Hw26+Hw25+Hw24)					//
#define	HwEINTSEL_EINT3SEL_GPE12				(Hw28+Hw27)								//
#define	HwEINTSEL_EINT3SEL_GPE13				(Hw28+Hw27+Hw24)						//
#define	HwEINTSEL_EINT3SEL_GPE14				(Hw28+Hw27+Hw25)						//
#define	HwEINTSEL_EINT3SEL_GPE15				(Hw28+Hw27+Hw25+Hw24)					//
#define	HwEINTSEL_EINT3SEL_PMWKUP				(Hw28+Hw27+Hw26)						//
#define	HwEINTSEL_EINT3SEL_SDD3					(Hw28+Hw27+Hw26+Hw24)					//
#define	HwEINTSEL_EINT3SEL_SPIFRM				(Hw28+Hw27+Hw26+Hw25)					//
#define	HwEINTSEL_EINT3SEL_CVS					(Hw28+Hw27+Hw26+Hw25+Hw24)				//
                                    			
#define	HwEINTSEL_EINT2SEL_EINT0				HwZERO									//
#define	HwEINTSEL_EINT2SEL_EINT1				Hw16									//
#define	HwEINTSEL_EINT2SEL_EINT2				Hw17									//		
#define	HwEINTSEL_EINT2SEL_EINT3				(Hw17+Hw16)								//
#define	HwEINTSEL_EINT2SEL_GPA0					Hw18									//
#define	HwEINTSEL_EINT2SEL_GPA1					(Hw18+Hw16)								//
#define	HwEINTSEL_EINT2SEL_GPA2					(Hw18+Hw17)								//
#define	HwEINTSEL_EINT2SEL_GPA3					(Hw18+Hw17+Hw16)						//
#define	HwEINTSEL_EINT2SEL_GPA4					Hw19									//
#define	HwEINTSEL_EINT2SEL_GPA5					(Hw19+Hw16)								//
#define	HwEINTSEL_EINT2SEL_GPA6					(Hw19+Hw17)								//
#define	HwEINTSEL_EINT2SEL_GPA7					(Hw19+Hw17+Hw16)						//
#define	HwEINTSEL_EINT2SEL_GPE0					(Hw19+Hw18)								//
#define	HwEINTSEL_EINT2SEL_GPE1					(Hw19+Hw18+Hw16)						//
#define	HwEINTSEL_EINT2SEL_GPE2					(Hw19+Hw18+Hw17)						//
#define	HwEINTSEL_EINT2SEL_GPE3					(Hw19+Hw18+Hw17+Hw16)					//
#define	HwEINTSEL_EINT2SEL_GPE4					Hw20									//
#define	HwEINTSEL_EINT2SEL_GPE5					(Hw20+Hw16)								//
#define	HwEINTSEL_EINT2SEL_GPE6					(Hw20+Hw17)								//
#define	HwEINTSEL_EINT2SEL_GPE7					(Hw20+Hw17+Hw16)						//
#define	HwEINTSEL_EINT2SEL_GPE8					(Hw20+Hw18)								//
#define	HwEINTSEL_EINT2SEL_GPE9					(Hw20+Hw18+Hw16)						//
#define	HwEINTSEL_EINT2SEL_GPE10				(Hw20+Hw18+Hw17)						//
#define	HwEINTSEL_EINT2SEL_GPE11				(Hw20+Hw18+Hw17+Hw16)					//
#define	HwEINTSEL_EINT2SEL_GPE12				(Hw20+Hw19)								//
#define	HwEINTSEL_EINT2SEL_GPE13				(Hw20+Hw19+Hw16)						//
#define	HwEINTSEL_EINT2SEL_GPE14				(Hw20+Hw19+Hw17)						//
#define	HwEINTSEL_EINT2SEL_GPE15				(Hw20+Hw19+Hw17+Hw16)					//
#define	HwEINTSEL_EINT2SEL_PMWKUP				(Hw20+Hw19+Hw18)						//
#define	HwEINTSEL_EINT2SEL_SDD3					(Hw20+Hw19+Hw18+Hw16)					//
#define	HwEINTSEL_EINT2SEL_SPIFRM				(Hw20+Hw19+Hw18+Hw17)					//
#define	HwEINTSEL_EINT2SEL_CVS					(Hw20+Hw19+Hw18+Hw17+Hw16)				//
                                    			
#define	HwEINTSEL_EINT1SEL_EINT0				HwZERO									//
#define	HwEINTSEL_EINT1SEL_EINT1				Hw8										//
#define	HwEINTSEL_EINT1SEL_EINT2				Hw9										//		
#define	HwEINTSEL_EINT1SEL_EINT3				(Hw9+Hw8)								//
#define	HwEINTSEL_EINT1SEL_GPA0					Hw10									//
#define	HwEINTSEL_EINT1SEL_GPA1					(Hw10+Hw8)								//
#define	HwEINTSEL_EINT1SEL_GPA2					(Hw10+Hw9)								//
#define	HwEINTSEL_EINT1SEL_GPA3					(Hw10+Hw9+Hw8)							//
#define	HwEINTSEL_EINT1SEL_GPA4					Hw11									//
#define	HwEINTSEL_EINT1SEL_GPA5					(Hw11+Hw8)								//
#define	HwEINTSEL_EINT1SEL_GPA6					(Hw11+Hw9)								//
#define	HwEINTSEL_EINT1SEL_GPA7					(Hw11+Hw9+Hw8)							//
#define	HwEINTSEL_EINT1SEL_GPE0					(Hw11+Hw10)								//
#define	HwEINTSEL_EINT1SEL_GPE1					(Hw11+Hw10+Hw8)							//
#define	HwEINTSEL_EINT1SEL_GPE2					(Hw11+Hw10+Hw9)							//
#define	HwEINTSEL_EINT1SEL_GPE3					(Hw11+Hw10+Hw9+Hw8)						//
#define	HwEINTSEL_EINT1SEL_GPE4					Hw12									//
#define	HwEINTSEL_EINT1SEL_GPE5					(Hw12+Hw8)								//
#define	HwEINTSEL_EINT1SEL_GPE6					(Hw12+Hw9)								//
#define	HwEINTSEL_EINT1SEL_GPE7					(Hw12+Hw9+Hw8)							//
#define	HwEINTSEL_EINT1SEL_GPE8					(Hw12+Hw10)								//
#define	HwEINTSEL_EINT1SEL_GPE9					(Hw12+Hw10+Hw8)							//
#define	HwEINTSEL_EINT1SEL_GPE10				(Hw12+Hw10+Hw9)							//
#define	HwEINTSEL_EINT1SEL_GPE11				(Hw12+Hw10+Hw9+Hw8)						//
#define	HwEINTSEL_EINT1SEL_GPE12				(Hw12+Hw11)								//
#define	HwEINTSEL_EINT1SEL_GPE13				(Hw12+Hw11+Hw8)							//
#define	HwEINTSEL_EINT1SEL_GPE14				(Hw12+Hw11+Hw9)							//
#define	HwEINTSEL_EINT1SEL_GPE15				(Hw12+Hw11+Hw9+Hw8)						//
#define	HwEINTSEL_EINT1SEL_PMWKUP				(Hw12+Hw11+Hw10)						//
#define	HwEINTSEL_EINT1SEL_SDD3					(Hw12+Hw11+Hw10+Hw8)					//
#define	HwEINTSEL_EINT1SEL_SPIFRM				(Hw12+Hw11+Hw10+Hw9)					//
#define	HwEINTSEL_EINT1SEL_CVS					(Hw12+Hw11+Hw10+Hw9+Hw8)				//
                                    			
#define	HwEINTSEL_EINT0SEL_EINT0				HwZERO									//
#define	HwEINTSEL_EINT0SEL_EINT1				Hw0										//
#define	HwEINTSEL_EINT0SEL_EINT2				Hw1										//		
#define	HwEINTSEL_EINT0SEL_EINT3				(Hw1+Hw0)								//
#define	HwEINTSEL_EINT0SEL_GPA0					Hw2										//
#define	HwEINTSEL_EINT0SEL_GPA1					(Hw2+Hw0)								//
#define	HwEINTSEL_EINT0SEL_GPA2					(Hw2+Hw1)								//
#define	HwEINTSEL_EINT0SEL_GPA3					(Hw2+Hw1+Hw0)							//
#define	HwEINTSEL_EINT0SEL_GPA4					Hw3										//
#define	HwEINTSEL_EINT0SEL_GPA5					(Hw3+Hw0)								//
#define	HwEINTSEL_EINT0SEL_GPA6					(Hw3+Hw1)								//
#define	HwEINTSEL_EINT0SEL_GPA7					(Hw3+Hw1+Hw0)							//
#define	HwEINTSEL_EINT0SEL_GPE0					(Hw3+Hw2)								//
#define	HwEINTSEL_EINT0SEL_GPE1					(Hw3+Hw2+Hw0)							//
#define	HwEINTSEL_EINT0SEL_GPE2					(Hw3+Hw2+Hw1)							//
#define	HwEINTSEL_EINT0SEL_GPE3					(Hw3+Hw2+Hw1+Hw0)						//
#define	HwEINTSEL_EINT0SEL_GPE4					Hw4										//
#define	HwEINTSEL_EINT0SEL_GPE5					(Hw4+Hw0)								//
#define	HwEINTSEL_EINT0SEL_GPE6					(Hw4+Hw1)								//
#define	HwEINTSEL_EINT0SEL_GPE7					(Hw4+Hw1+Hw0)							//
#define	HwEINTSEL_EINT0SEL_GPE8					(Hw4+Hw2)								//
#define	HwEINTSEL_EINT0SEL_GPE9					(Hw4+Hw2+Hw0)							//
#define	HwEINTSEL_EINT0SEL_GPE10				(Hw4+Hw2+Hw1)							//
#define	HwEINTSEL_EINT0SEL_GPE11				(Hw4+Hw2+Hw1+Hw0)						//
#define	HwEINTSEL_EINT0SEL_GPE12				(Hw4+Hw3)								//
#define	HwEINTSEL_EINT0SEL_GPE13				(Hw4+Hw3+Hw0)							//
#define	HwEINTSEL_EINT0SEL_GPE14				(Hw4+Hw3+Hw1)							//
#define	HwEINTSEL_EINT0SEL_GPE15				(Hw4+Hw3+Hw1+Hw0)						//
#define	HwEINTSEL_EINT0SEL_PMWKUP				(Hw4+Hw3+Hw2)							//
#define	HwEINTSEL_EINT0SEL_SDD3					(Hw4+Hw3+Hw2+Hw0)						//
#define	HwEINTSEL_EINT0SEL_SPIFRM				(Hw4+Hw3+Hw2+Hw1)						//
#define	HwEINTSEL_EINT0SEL_CVS					(Hw4+Hw3+Hw2+Hw1+Hw0)					//

/************************************************************************
*	ECC Register Define							(Base Addr = 0xF005B000)
************************************************************************/
#define	HwECC_CTRL								*(volatile unsigned long *)0xF005B000	// R/W, ECC Control Register
#define	HwECC_CTRL_DEN_EN						Hw28									// ECC DMA Request Enable
#define	HwECC_CTRL_DEN_DIS						~Hw28									// ECC DMA Request Disable
#define	HwECC_CTRL_ENC_ENC						Hw27									// Encoding Calculation for MLC3/4 ECC
#define	HwECC_CTRL_ENC_DEC						~Hw27									// Decoding Calculation for MLC3/4 ECC
#define	HwECC_CTRL_IRQ_CLR						Hw26									// MLC ECC Flag
#define	HwECC_CTRL_IEN_EN						Hw25									// MLC ECC4 Interrupt Enable
#define	HwECC_CTRL_IEN_DIS						~Hw25									// MLC ECC4 Interrupt Disable
#define	HwECC_CTRL_MN_EN						Hw22									// Manual Correction Start Enable
#define	HwECC_CTRL_MN_DIS						~Hw22									// Manual Correction Start Disable
#define	HwECC_CTRL_HD_EN						Hw7										// Hold Enabled. ECC output register is not changed.
#define	HwECC_CTRL_HD_DIS						~Hw7									// Hold Disabled.
#define	HwECC_CTRL_M4EN_EN						Hw6										// MLC ECC4 Enable
#define	HwECC_CTRL_M4EN_DIS						~Hw6									// MLC ECC4 Disable
#define	HwECC_CTRL_ZERO							Hw5										// Means that ECC output register (SLC & MLC_ECC0R & MLC_ECC1R & MLC_ECC2R for MLC) contains 0.
#define	HwECC_CTRL_M3EN_EN						Hw4										// MLC ECC3 Enable
#define	HwECC_CTRL_M3EN_DIS						~Hw4									// MLC ECC3 Disable
#define	HwECC_CTRL_SE_EN						Hw0										// Enable ECC for SLC
#define	HwECC_CTRL_SE_DIS						~Hw0									// Disable ECC for SLC
                                        	
#define	HwECC_BASE								*(volatile unsigned long *)0xF005B004	// R/W, Base Address for ECC Calculation Register
                                			
#define	HwECC_MASK								*(volatile unsigned long *)0xF005B008	// R/W, Address Mask for ECC Area Register
                                			
#define	HwECC_CLR								*(volatile unsigned long *)0xF005B00C	// W, Clear ECC Output Register
                                			
#define	HwSLC_ECC0								*(volatile unsigned long *)0xF005B010	// R, 1st Block ECC Output for SLC Nand Register
                                			
#define	HwSLC_ECC1								*(volatile unsigned long *)0xF005B014	// R, 2nd Block ECC Output for SLC Nand Register
                                			
#define	HwSLC_ECC2								*(volatile unsigned long *)0xF005B018	// R, 3nd Block ECC Output for SLC Nand Register
                                			
#define	HwSLC_ECC3								*(volatile unsigned long *)0xF005B01C	// R, 4th Block ECC Output for SLC Nand Register
                                			
#define	HwSLC_ECC4								*(volatile unsigned long *)0xF005B020	// R, 5th Block ECC Output for SLC Nand Register
                                			
#define	HwSLC_ECC5								*(volatile unsigned long *)0xF005B024	// R, 6th Block ECC Output for SLC Nand Register
                                			
#define	HwSLC_ECC6								*(volatile unsigned long *)0xF005B028	// R, 7th Block ECC Output for SLC Nand Register
                                			
#define	HwSLC_ECC7								*(volatile unsigned long *)0xF005B02C	// R, 8th Block ECC Output for SLC Nand Register
                                			
#define	HwMLC_ECC0W								*(volatile unsigned long *)0xF005B030	// W, MLC Nand ECC Calculation Register 0
                                			
#define	HwMLC_ECC1W								*(volatile unsigned long *)0xF005B034	// W, MLC Nand ECC Calculation Register 1
                                			
#define	HwMLC_ECC2W								*(volatile unsigned long *)0xF005B038	// W, MLC Nand ECC Calculation Register 2
                                			
#define	HwMLC_ECC0R								*(volatile unsigned long *)0xF005B040	// R, Calculated ECC Output 0 for MLC Nand Register
                                			
#define	HwMLC_ECC1R								*(volatile unsigned long *)0xF005B044	// R, Calculated ECC Output 1 for MLC Nand Register
                                			
#define	HwMLC_ECC2R								*(volatile unsigned long *)0xF005B048	// R, Calculated ECC Output 2 for MLC Nand Register
                                        	
#define	HwCORR_START							*(volatile unsigned long *)0xF005B04C	// W, MLC ECC4 Correction Start Register
                                        	
#define	HwERRADDR0								*(volatile unsigned long *)0xF005B050	// R, MLC ECC4 Error Address Register1
                            		    	
#define	HwERRADDR1								*(volatile unsigned long *)0xF005B054	// R, MLC ECC4 Error Address Register2
                            		    	
#define	HwERRADDR2								*(volatile unsigned long *)0xF005B058	// R, MLC ECC4 Error Address Register3
	                        		    	
#define	HwERRADDR3								*(volatile unsigned long *)0xF005B05C	// R, MLC ECC4 Error Address Register4
                            		    	
#define	HwERRDATA0								*(volatile unsigned long *)0xF005B060	// R, MLC ECC4 Error Data Register1
                            		    	
#define	HwERRDATA1								*(volatile unsigned long *)0xF005B064	// R, MLC ECC4 Error Data Register2
                            		    	
#define	HwERRDATA2								*(volatile unsigned long *)0xF005B068	// R, MLC ECC4 Error Data Register3
                            		    	
#define	HwERRDATA3								*(volatile unsigned long *)0xF005B06C	// R, MLC ECC4 Error Data Register4
                                        	
#define	HwERR_NUM								*(volatile unsigned long *)0xF005B070	// R, MLC ECC4 Error Number Register
#define	HwERR_NUM_ERR1							HwZERO									// Correctable Error(SLC), Error Occurred(MLC3), 1 Error Occurred(MLC4)
#define	HwERR_NUM_ERR2							Hw0										// 2 Error Occurred(MLC4)
#define	HwERR_NUM_ERR3							Hw1										// 3 Error Occurred(MLC4)
#define	HwERR_NUM_ERR4							(Hw1+Hw0)								// 4 Error Occurred(MLC4)
#define	HwERR_NUM_NOERR							Hw2										// No Error
#define	HwERR_NUM_CORIMP						(Hw2+Hw1+Hw0)							// Correction Impossible(SLC, MLC4)

/************************************************************************
*	SPDIF Transmitter Register Define			(Base Addr = 0xF005C000)
************************************************************************/
#define	HwTxVersion								*(volatile unsigned long *)0xF005C000	// R, Version Register
#define	HwTxVersion_CSB							Hw12									// Channel Status Buffer Available bit
#define	HwTxVersion_UDB							Hw11									// User Data Buffer Available bit
#define	HwTxVersion_DW							Hw4										// Value of Data Width
                                			
#define	HwTxConfig								*(volatile unsigned long *)0xF005C004	// R/W, Configuration Register 
#define	HwTxConfig_IEN							Hw2										// Interrupt Output Enable
#define	HwTxConfig_TXD							Hw1										// Data Vaild
#define	HwTxConfig_TXEN							Hw0										// Transmitter Enable
                                			
#define	HwTxChStat								*(volatile unsigned long *)0xF005C008	// R/W, Channel Status Control Register
#define	HwTxChStat_FREQ_441						HwZERO									// 44.1Khz
#define	HwTxChStat_FREQ_48						Hw6										// 48Khz
#define	HwTxChStat_FREQ_32						Hw7										// 32Khz
#define	HwTxChStat_FREQ_CON						(Hw7+Hw6)								// Sample Rate Converter
#define	HwTxChStat_GSTS							Hw3										// Status Generation
#define	HwTxChStat_PRE							Hw2										// Pre-emphasis
#define	HwTxChStat_CPY							Hw1										// Copyright
#define	HwTxChStat_AU							Hw0										// Data Format
                                			
#define	HwTxIntMask								*(volatile unsigned long *)0xF005C00C	// R/W, Interrupt Mask Register
#define	HwTxIntMask_HCSB						Hw4										// Higher Channel Status/User Data Buffer Empty
#define	HwTxIntMask_LCSB						Hw3										// Lower Channel Status/User Data Buffer Empty
#define	HwTxIntMask_HSB							Hw2										// Higher Data Buffer Empty
#define	HwTxIntMask_LSB							Hw1										// Lower Data Buffer Empty
                                			
#define	HwTxIntStat								*(volatile unsigned long *)0xF005C010	// R/W, Interrupt Status Register
#define	HwTxIntStat_HCSB						Hw4										// Higher Channel Status/User Data Buffer Empty
#define	HwTxIntStat_LCSB						Hw3										// Lower Channel Status/User Data Buffer Empty
#define	HwTxIntStat_HSB							Hw2										// Higher Data Buffer Empty
#define	HwTxIntStat_LSB							Hw1										// Lower Data Buffer Empty
                                			
#define	HwUserData								*(volatile unsigned long *)0xF005C080	// W, User Data Buffer 
                                			
#define HwChStatus								*(volatile unsigned long *)0xF005C100	// W, Channel Status Buffer
                                			
#define	HwTxBuffer								*(volatile unsigned long *)0xF005C200	// W, Transmit Data Buffer

/***********************************************************************
*	 Camera Interface Register Define			(Base Addr = 0xF0060000)
************************************************************************/
#define	HwICPCR1								*(volatile unsigned long *)0xF0060000	// W, Input Image Color/Pattern Configuration Register 1
#define	HwICPCR1_ON							Hw31									// 0 : Can't operate CIF, 1 : Operating CIF
#define	HwICPCR1_PWD							Hw30									// Power down mode in camera
#define	HwICPCR1_BPS							Hw23									// Bypass Scaler
#define	HwICPCR1_POL							Hw21									// PXCLK Polarity
#define	HwICPCR1_NOT_SKIP						HwZERO									// Not Skip
#define	HwICPCR1_M420_NOT_CVT					HwZERO									// Not Convert
#define	HwICPCR1_M420_ODD_SKIP					Hw17									// Converted in odd line skip
#define	HwICPCR1_M420_EVEN_SKIP					(Hw17+Hw16)								// Converted in even line skip
#define	HwICPCR1_BP								Hw15									// Bypass
#define	HwICPCR1_BBS_LSB8						Hw14									// When bypass 16bits mode, LSB 8bits are stored in first
#define	HwICPCR1_C656							Hw13									// Convert 656 format
#define	HwICPCR1_CP_RGB							Hw12									// RGB(555,565,bayer) color pattern
#define	HwICPCR1_PF_444							HwZERO									// 4:4:4 format
#define	HwICPCR1_PF_422							Hw10									// 4:2:2 format
#define	HwICPCR1_PF_420							Hw11									// 4:2:0 format or RGB(555,565,bayer) mode
#define	HwICPCR1_RGBM_BAYER						HwZERO									// Bayer RGB Mode
#define	HwICPCR1_RGBM_RGB555					Hw8										// RGB555 Mode
#define	HwICPCR1_RGBM_RGB565					Hw9										// RGB565 Mode
#define	HwICPCR1_RGBBM_16						HwZERO									// 16bit mode
#define	HwICPCR1_RGBBM_8DISYNC					Hw6										// 8bit disable sync
#define	HwICPCR1_RGBBM_8						Hw7										// 8bit mode
#define	HwICPCR1_CS_RGBMG						HwZERO									// 555RGB:RGB(MG), 565RGB:RGB, 444/422/420:R/Cb/U first, Bayer RGB:BG->GR, CCIR656:YCbYCr
#define	HwICPCR1_CS_RGBLG						Hw4										// 555RGB:RGB(LG), 565RGB:RGB, 444/422/420:R/Cb/U first, Bayer RGB:GR->BG, CCIR656:YCrYCb
#define	HwICPCR1_CS_BGRMG						Hw5										// 555RGB:BGR(MG), 565RGB:BGR, 444/422/420:B/Cr/V first, Bayer RGB:RG->GB, CCIR656:CbYCrY
#define	HwICPCR1_CS_BGRLG						(Hw5+Hw4)								// 555RGB:BGR(LG), 565RGB:BGR, 444/422/420:B/Cr/V first, Bayer RGB:GB->RG, CCIR656:CrYCbY
#define	HwICPCR1_BO_SW							Hw2										// Switch the MSB/LSB 8bit Bus
#define	HwICPCR1_HSP_HIGH						Hw1										// Active high
#define	HwICPCR1_VSP_HIGH						Hw0										// Active high
                                    		
#define	Hw656FCR1								*(volatile unsigned long *)0xF0060004	// W, CCIR656 Format Configuration Register 1
#define	Hw656FCR1_PSL_1ST						HwZERO									// The status word is located the first byte of EAV & SAV
#define	Hw656FCR1_PSL_2ND						Hw25									// The status word is located the second byte of EAV & SAV
#define	Hw656FCR1_PSL_3RD						Hw26									// The status word is located the third byte of EAV & SAV
#define	Hw656FCR1_PSL_4TH						(Hw26+Hw25)								// The status word is located the forth byte of EAV & SAV
                                    		
#define	Hw656FCR2								*(volatile unsigned long *)0xF0060008	// W, CCIR656 Format Configuration Register 2
                                    		
#define	HwIIS									*(volatile unsigned long *)0xF006000C	// W, Input Image Size
                                    		
#define	HwIIW1									*(volatile unsigned long *)0xF0060010	// W, Input Image Windowing 1
                                    		
#define	HwIIW2									*(volatile unsigned long *)0xF0060014	// W, Input Image Windowing 2
                                    		
#define	HwCDCR1									*(volatile unsigned long *)0xF0060018	// W, DMA Configuratin Register 1
#define	HwCDCR1_TM_INC							Hw3										// INC Transfer
#define	HwCDCR1_LOCK_ON							Hw2										// Lock Transfer
#define	HwCDCR1_BS_1							HwZERO									// The DMA transfers the image data as 1 word to memory
#define	HwCDCR1_BS_2							Hw0										// The DMA transfers the image data as 2 word to memory
#define	HwCDCR1_BS_4							Hw1										// The DMA transfers the image data as 4 word to memory
#define	HwCDCR1_BS_8							(Hw1+Hw0)								// The DMA transfers the image data as 8 word to memory (default)
                                    		
#define	HwCDCR2									*(volatile unsigned long *)0xF006001C	// W, DMA Configuration Register 2
                                    		
#define	HwCDCR3									*(volatile unsigned long *)0xF0060020	// W, DMA Configuration Register 3
                                    		
#define	HwCDCR4									*(volatile unsigned long *)0xF0060024	// W, DMA Configuration Register 4
                                    		
#define	HwCDCR5									*(volatile unsigned long *)0xF0060028	// W, DMA Configuration Register 5
                                    		
#define	HwCDCR6									*(volatile unsigned long *)0xF006002C	// W, DMA Configuration Register 6
                                    		
#define	HwCDCR7									*(volatile unsigned long *)0xF0060030	// W, DMA Configuration Register 7
                                    		
#define	HwFIFOSTATE								*(volatile unsigned long *)0xF0060034	// R, FIFO Status Register
#define	HwFIFOSTATE_CLR							Hw21									// 1:Clear, 0:Not Clear
#define	HwFIFOSTATE_REO							Hw19									// 1:The empty signal of input overlay FIFO and read enable signal are High, 0:The empty signal of overlay FIFO is low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_REV							Hw18									// 1:The empty signal of input V(B) channel FIFO and read enable signal are High, 0:The empty signal of V(B) channel FIFO is Low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_REU							Hw17									// 1:The empty signal of input U(R) channel FIFO and read enable signal are High, 0:The empty signal of U(R) channel FIFO is Low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_REY							Hw16									// 1:The empty signal of input Y(G) channel FIFO and read enable signal are High, 0:The empty signal of Y(G) channel FIFO is Low, or empty is High and read enable signal is Low.
#define	HwFIFOSTATE_WEO							Hw13									// 1:The full signal of overlay FIFO and write enable signal are High, 0:The full signal of overlay FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_WEV							Hw12									// 1:The full signal of V(B) channel FIFO and write enable signal are High, 0:The full signal of V(B) channel FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_WEU							Hw11									// 1:The full signal of U(R) channel FIFO and write enable signal are High, 0:The full signal of U(R) channel FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_WEY							Hw10									// 1:The full signal of Y channel FIFO and write enable signal are High, 0:The full signal of Y channel FIFO is Low, or full is High and write enable signal is Low.
#define	HwFIFOSTATE_EO							Hw8										// 1:The state of overlay FIFO is empty, 0:The state of overlay FIFO is non-empty.
#define	HwFIFOSTATE_EV							Hw7										// 1:The state of V(B) channel FIFO is empty, 0:The state of V(B) channel FIFO is non-empty.
#define	HwFIFOSTATE_EU							Hw6										// 1:The state of U(R) channel FIFO is empty, 0:The state of U(R) channel FIFO is non-empty.
#define	HwFIFOSTATE_EY							Hw5										// 1:The state of Y channel FIFO is empty, 0:The state of Y channel FIFO is non-empty.
#define	HwFIFOSTATE_FO							Hw3										// 1:The state of overlay FIFO is full, 0:The state of overlay FIFO is non-full.
#define	HwFIFOSTATE_FV							Hw2										// 1:The state of V(B) channel FIFO is full, 0:The state of V(B) channel FIFO is non-full.
#define	HwFIFOSTATE_FU							Hw1										// 1:The state of U(R) channel FIFO is full, 0:The state of U(R) channel FIFO is non-full.
#define	HwFIFOSTATE_FY							Hw0										// 1:The state of Y channel FIFO is full, 0:The state of Y channel FIFO is non-full.
                                    		
#define	HwCIRQ										*(volatile unsigned long *)0xF0060038	// R/W, Interrupt & CIF Operating Register
#define	HwCIRQ_IEN_EN								Hw31									// Interrupt Enable
#define	HwCIRQ_URV									Hw30									// Update Register in VSYNC
#define	HwCIRQ_ITY									Hw29									// Interrupt Type
#define	HwCIRQ_ICR									Hw28									// Interrupt Clear
#define	HwCIRQ_MVN								Hw26									// Mask Interrupt of VS negative edge
#define	HwCIRQ_MVP								Hw25									// Mask Interrupt of VS positive edge
#define	HwCIRQ_MVIT								Hw24									// Mask Interrupt of VCNT INterrupt
#define	HwCIRQ_MSE								Hw23									// Mask Interrupt of Scaler Error
#define	HwCIRQ_MSF								Hw22									// Mask Interrupt of Scaler finish
#define	HwCIRQ_MENS								Hw21									// Mask Interrupt of Encoding start
#define	HwCIRQ_MRLV								Hw20									// Mask Interrupt of Rolling V address
#define	HwCIRQ_MRLU								Hw19									// Mask Interrupt of Rolling U address
#define	HwCIRQ_MRLY								Hw18									// Mask Interrupt of Rolling Y address
#define	HwCIRQ_MSCF								Hw17									// Mask Interrupt of Capture frame
#define	HwCIRQ_MSOF								Hw16									// Mask Interrupt of Stored one frame
#define	HwCIRQ_VSS									Hw12									// Status of vertical sync 
#define	HwCIRQ_VN									Hw10									// VS negative
#define	HwCIRQ_VP									Hw9										// VS positive
#define	HwCIRQ_VIT									Hw8										// VCNT Interrupt
#define	HwCIRQ_SE									Hw7										// Scaler Error
#define	HwCIRQ_SF									Hw6										// Scaler Finish
#define	HwCIRQ_ENS									Hw5										// Encoding start stauts
#define	HwCIRQ_ROLV								Hw4										// Rolling V address status
#define	HwCIRQ_ROLU								Hw3										// Rolling U address status
#define	HwCIRQ_ROLY								Hw2										// Rolling Y address status
#define	HwCIRQ_SCF									Hw1										// Stored captured frame
#define	HwCIRQ_SOF									Hw0										// Stored one frame
                                    		
#define	HwOCTRL1								*(volatile unsigned long *)0xF006003C	// W, Overlay Control 1
#define	HwOCTRL1_OCNT_MAX						(Hw27+Hw26+Hw25+Hw24+Hw23)				//
#define	HwOCTRL1_OM_BLOCK						Hw16									// Block image overlay
#define	HwOCTRL1_OE_EN							Hw12									// Overlay enable
#define	HwOCTRL1_XR1_100						Hw10									// 100%
#define	HwOCTRL1_XR0_100						Hw9										// 100%
#define	HwOCTRL1_AP1_25							HwZERO									// 25%			
#define	HwOCTRL1_AP1_50							Hw6										// 50%
#define	HwOCTRL1_AP1_75							Hw7										// 75%				
#define	HwOCTRL1_AP1_100						(Hw7+Hw6)								// 100%		
#define	HwOCTRL1_AP0_25							HwZERO									// 25%			
#define	HwOCTRL1_AP0_50							Hw4										// 50%
#define	HwOCTRL1_AP0_75							Hw5										// 75%				
#define	HwOCTRL1_AP0_100						(Hw5+Hw4)								// 100%
#define HwOCTRL1_AEN_EN							Hw2										// Alpha enable
#define HwOCTRL1_CEN_EN							Hw0										// Chroma key enable
                                    		
#define	HwOCTRL2								*(volatile unsigned long *)0xF0060040	// W, Overlay Control 4
#define	HwOCTRL2_CONV							Hw3										// Color Converter Enable
#define	HwOCTRL2_RGB_565						HwZERO									// 565RGB
#define	HwOCTRL2_RGB_555						Hw1										// 555RGB
#define	HwOCTRL2_RGB_444						Hw2										// 444RGB
#define	HwOCTRL2_RGB_332						(Hw2+Hw1)								// 332RGB
#define	HwOCTRL2_MD							Hw0										// Color Mode, 0 = YUB, 1 = RGB
                                    		
#define	HwOCTRL3								*(volatile unsigned long *)0xF0060044	// W, Overlay Control 2
#define	HwOCTRL3_KEYR_MAX						0x00FF0000
#define	HwOCTRL3_KEYG_MAX						0x0000FF00
#define	HwOCTRL3_KEYB_MAX						0x000000FF
                                    		
#define	HwOCTRL4								*(volatile unsigned long *)0xF0060048	// W, Overlay Control 3
#define	HwOCTRL4_MKEYR_MAX						0x00FF0000
#define	HwOCTRL4_MKEYG_MAX						0x0000FF00
#define	HwOCTRL4_MKEYB_MAX						0x000000FF
                                    		
#define	HwOIS									*(volatile unsigned long *)0xF006004C	// W, Overlay Image Size
                                    		
#define	HwOIW1									*(volatile unsigned long *)0xF0060050	// W, Overlay Image Windowing 1
                                    		
#define	HwOIW2									*(volatile unsigned long *)0xF0060054	// W, Overlay Image Windowing 2
                                    		
#define	HwCOBA									*(volatile unsigned long *)0xF0060058	// W, Overlay Base Address
                                    		
#define	HwCDS									*(volatile unsigned long *)0xF006005C	// W, Camera Down Scaler
#define	HwCDS_SFH_1								HwZERO									// 1/1 down scale
#define	HwCDS_SFH_2								Hw4										// 1/2 down scale
#define	HwCDS_SFH_4								Hw5										// 1/4 down scale
#define	HwCDS_SFH_8								(Hw5+Hw4)								// 1/8 down scale
#define	HwCDS_SFV_1								HwZERO									// 1/1 down scale
#define	HwCDS_SFV_2								Hw2										// 1/2 down scale
#define	HwCDS_SFV_4								Hw3										// 1/4 down scale
#define	HwCDS_SFV_8								(Hw3+Hw2)								// 1/8 down scale
#define HwCDS_SEN_EN							Hw0										// Scale enable
                                    		
#define	HwCCM1									*(volatile unsigned long *)0xF0060060	// R/W, Capture Mode 1
#define	HwCCM1_CB								Hw10									// Capture Busy
#define	HwCCM1_EIT								Hw9										// Encoding INT count
#define	HwCCM1_UES								Hw8										// Using Encoding Start Address
#define	HwCCM1_RLV								Hw3										// Rolling address V
#define	HwCCM1_RLU								Hw2										// Rolling address U
#define	HwCCM1_RLY								Hw1										// Rolling address Y
#define	HwCCM1_CAP								Hw0										// Image Capture
                                    		
#define	HwCCM2									*(volatile unsigned long *)0xF0060064	// R/W, Capture Mode 2
#define	HwCCM2_VEN								Hw0										// VCNT folling enable
                                    		
#define	HwCESA									*(volatile unsigned long *)0xF0060068	// R/W, Encoding Start Address
                                    		
#define	HwCR2Y									*(volatile unsigned long *)0xF006006C	// R/W, R2Y Configuration
#define	HwCR2Y_565RGB_SEQ16						HwZERO									// 16bit 565RGB (RGB sequence)
#define	HwCR2Y_565BGR_SEQ16						Hw1										// 16bit 565RGB (BGR sequence)
#define	HwCR2Y_555RGB_GAR16						Hw3										// 16bit 555RGB	(RGB-garbage)
#define	HwCR2Y_555BGR_GAR16						(Hw3+Hw1)								// 16bit 555RGB (BGR-garbage)
#define	HwCR2Y_555GAR_RGB16						(Hw3+Hw2)								// 16bit 555RGB	(garbage-RGB)
#define	HwCR2Y_555GAR_BGR16						(Hw3+Hw2+Hw1)							// 16bit 555RGB (garbage-BGR)
#define	HwCR2Y_565RGB_SEQ8						Hw4										// 8bit 565RGB (RGB sequence)
#define	HwCR2Y_565BGR_SEQ8						(Hw4+Hw1)								// 8bit 565RGB (BGR sequence)
#define	HwCR2Y_555RGB_GAR8						(Hw4+Hw3)								// 8bit 555RGB (RGB-garbage)
#define	HwCR2Y_555BGR_GAR8						(Hw4+Hw3+Hw1)							// 8bit 555RGB (BGR-garbage)
#define	HwCR2Y_555GAR_RGB8						(Hw4+Hw3+Hw2)							// 8bit 555RGB (garbage-RGB)
#define	HwCR2Y_555GAR_BGR8						(Hw4+Hw3+Hw2+Hw1)						// 8bit 555RGB (garbage-BGR)
#define	HwCR2Y_EN								Hw0										// R2Y Enable
                                    		
#define	HwCCYA									*(volatile unsigned long *)0xF0060070	// R, Current Y Address
                                    		
#define	HwCCUA									*(volatile unsigned long *)0xF0060074	// R, Current U Address
                                    		
#define	HwCCVA									*(volatile unsigned long *)0xF0060078	// R, Current V Address
                                    		
#define	HwCCLC									*(volatile unsigned long *)0xF006007C	// R, Current Line Count
                                    		
#define	HwCEM									*(volatile unsigned long *)0xF0060100	// R/W, Effect Mode Register
#define	HwCEM_UVS								Hw15									// UV Swap
#define	HwCEM_VB								Hw14									// V Bias (V Channel value offset)
#define	HwCEM_UB								Hw13									// U Bias (U Channel value offset)
#define	HwCEM_YB								Hw12									// Y Bias (Y Channel value offset)
#define	HwCEM_YCS								Hw11									// YC Swap
#define	HwCEM_IVY								Hw10									// Invert Y
#define	HwCEM_STC								Hw9										// Strong C
#define	HwCEM_YCL								Hw8										// Y Clamp (Y value clipping)
#define	HwCEM_CS								Hw7										// C Select (Color filter)
#define	HwCEM_SKT								Hw6										// Sketch Enable
#define	HwCEM_EMM								Hw5										// Emboss Mode
#define	HwCEM_EMB								Hw4										// Emboss
#define	HwCEM_NEGA								Hw3										// Nagative Mode
#define	HwCEM_GRAY								Hw2										// Gray Mode
#define	HwCEM_SEPI								Hw1										// Sepia Mode
#define	HwCEM_NOR								Hw0										// Normal Mode
                                    		
#define	HwCSUV									*(volatile unsigned long *)0xF0060104	// Sepia UV
                                    		
#define HwCCS									*(volatile unsigned long *)0xF0060108	// Color Selection
                                    		
#define	HwCHFC									*(volatile unsigned long *)0xF006010C	// H filter Coefficient
                                    		
#define	HwCST									*(volatile unsigned long *)0xF0060110	// Sketch Threshold
                                    		
#define	HwCCT									*(volatile unsigned long *)0xF0060114	// Clamp Threshold
                                    		
#define	HwCBR									*(volatile unsigned long *)0xF0060118	// Bias Register
                                    		
#define	HwCEIS									*(volatile unsigned long *)0xF006011C	// Effect Image Size
                                    		
#define	HwCIC									*(volatile unsigned long *)0xF0060140	// Inpath Control
#define	HwCIC_INPR								Hw3										//
#define	HwCIC_FA								Hw2										// Flush All
#define	HwCIC_INE								Hw1										// Inpath Enable
#define	HwCIC_INP								Hw0										// Inpath Mode
                                    		
#define	HwCISA1									*(volatile unsigned long *)0xF0060144	// Inpath SRC Address 1
                                    		
#define	HwCISA2									*(volatile unsigned long *)0xF0060148	// Inpath SRC Address 2
#define	HwCISA2_SRCTYPE_422SEQ0					HwZERO									// 4:2:2 SEQ0
#define	HwCISA2_SRCTYPE_422SEQ1					Hw28									// 4:2:2 SEQ1
#define	HwCISA2_SRCTYPE_422SEP					Hw29									// 4:2:2 Separate
#define	HwCISA2_SRCTYPE_420SEP					(Hw29+Hw28)								// 4:2:0 Separate
                                    		
#define	HwCISA3									*(volatile unsigned long *)0xF006014C	// Inpath SRC Address 3
                                    		
#define	HwCISS									*(volatile unsigned long *)0xF0060150	// Inpath SRC Size
                                    		
#define	HwCISO									*(volatile unsigned long *)0xF0060154	// Inpath SRC Offset
                                    		
#define	HwCIDS									*(volatile unsigned long *)0xF0060158	// Inpath DST Size
                                    		
#define	HwCIS									*(volatile unsigned long *)0xF006015C	// Inpath Scale
                                    		
#define	HwCSC									*(volatile unsigned long *)0xF0060200	// Scaler CTRL
#define	HwCSC_EN								Hw0										// Scaler Enable
                                    		
#define	HwCSSF									*(volatile unsigned long *)0xF0060204	// Scaler Scale Factor
                                    		
#define	HwCSSO									*(volatile unsigned long *)0xF0060208	// Scaler SRC Offset
                                    		
#define	HwCSSS									*(volatile unsigned long *)0xF006020C	// Scaler SRC Size
                                    		
#define	HwCSDS									*(volatile unsigned long *)0xF0060210	// Scaler DST Size

/***********************************************************************
*	MSC(Memory-to-Memory Scaler) Define			(Base Addr = 0xF0070000)
************************************************************************/
#define	HwSRCBASEY								*(volatile unsigned long *)0xF0070000	// R/W, Source Base Address for Y
                                        	
#define	HwSRCBASEU								*(volatile unsigned long *)0xF0070004	// R/W, Source Base Address for U(Cb)
                                        	
#define	HwSRCBASEV								*(volatile unsigned long *)0xF0070008	// R/W, Source Base Address for V(Cr)
                                        	
#define	HwSRCSIZE								*(volatile unsigned long *)0xF007000C	// R/W, Source Size Information Register
                                        	
#define	HwSRCOFF								*(volatile unsigned long *)0xF0070010	// R/W, Source Offset Information Register
                                        	
#define	HwSRCCFG								*(volatile unsigned long *)0xF0070014	// R/W, Source Configuration Register
#define	HwSRCCFG_422SEQ0						HwZERO									// 4:2:2 Sequential Mode 0
#define	HwSRCCFG_422SEQ1						Hw0										// 4:2:2 Sequential Mode 1
#define	HwSRCCFG_422SEP							Hw1										// 4:2:2 Separate Mode
#define	HwSRCCFG_420SEP							(Hw1+Hw0)								// 4:2:0 Separate Mode
                                        	
#define	HwDSTBASEY								*(volatile unsigned long *)0xF0070020	// R/W, Destination Base Address for Y
                                        	
#define	HwDSTBASEU								*(volatile unsigned long *)0xF0070024	// R/W, Destination Base Address for U(Cb)
                                        	
#define	HwDSTBASEV								*(volatile unsigned long *)0xF0070028	// R/W, Destination Base Address for V(Cr)
                                        	
#define	HwDSTSIZE								*(volatile unsigned long *)0xF007002C	// R/W, Destination Size Information Register
                                        	
#define	HwDSTOFF								*(volatile unsigned long *)0xF0070030	// R/W, Destination Offset Information Register
                                        	
#define	HwDSTCFG								*(volatile unsigned long *)0xF0070034	// R/W, Destination Configuration Register
#define	HwDSTCFG_COP							Hw11									// Chrominance Writing Mode Register Defined for 4:2:0 Seperate Mode
																						// 0 : Y0->U0->V0->Y1->Y2->U1...
																						// 1 : Y0->U0->Y1->V0->Y2->U1...
#define	HwDSTCFG_RDY							Hw6										// Access Wait Control Register
#define	HwDSTCFG_PATH							Hw4										// Destination Type Register
#define	HwDSTCFG_422SEQ0						HwZERO									// 4:2:2 Sequential Mode 0
#define	HwDSTCFG_422SEQ1						Hw0										// 4:2:2 Sequential Mode 1
#define	HwDSTCFG_422SEP							Hw1										// 4:2:2 Separate Mode
#define	HwDSTCFG_420SEP							(Hw1+Hw0)								// 4:2:0 Separate Mode
                                        	
#define	HwMSCINF								*(volatile unsigned long *)0xF0070040	// R/W, Scaling Information Register
                                        	
#define	HwMSCCTR								*(volatile unsigned long *)0xF0070044	// R/W, Control Register
#define	HwMSCCTR_FLS							Hw31									// Flush the internal FIFOs
#define	HwMSCCTR_TST							Hw30									// Should be zero for test purpose
#define	HwMSCCTR_IEN_BUSY						Hw2										// Interrupt Enable Register
#define	HwMSCCTR_IEN_RDY							Hw1										// Interrupt Enable Register
#define	HwMSCCTR_EN								Hw0										// Enable Register
                                        	
#define	HwMSCSTR								*(volatile unsigned long *)0xF0070048	// R/W, Status Register
#define	HwMSCSTR_IBUSY							Hw5										// Busy Interrupt Flag
#define	HwMSCSTR_IRDY							Hw4										// Ready Interrupt Flag
#define	HwMSCSTR_BUSY							Hw1										// Busy Status Register
#define	HwMSCSTR_RDY							Hw0										// Ready Status Register

/************************************************************************
*	Channel 0 Memory Controller Register Define	(Base Addr = 0xF1000000)
************************************************************************/
#define	HwSDCFG									*(volatile unsigned long *)0xF1000000	// R/W, SDRAM Configuration
#define	HwSDCFG_CL								Hw31									// CAS Latency
#define	HwSDCFG_BW								Hw30									// Bus Width
#define	HwSDCFG_CW8								HwZERO
#define	HwSDCFG_CW9								Hw29
#define	HwSDCFG_CW10							(Hw29+Hw28)
#define	HwSDCFG_CW_MAX							(Hw29+Hw28)								//
#define	HwSDCFG_RD0								Hw15									// Delay from RAS to CAS
#define	HwSDCFG_RW11							Hw10									//
#define	HwSDCFG_RW12							HwZERO									//
#define	HwSDCFG_RW13							Hw11									//
#define	HwSDCFG_RW_MAX							(Hw11+Hw10)								//
                                			
#define	HwSDFSM									*(volatile unsigned long *)0xF1000004	// R, SDRAM FSM Status
                                			
#define	HwMCFG									*(volatile unsigned long *)0xF1000008	// R/W, Misc. Configuration
#define	HwMCFG_RDY								Hw15									// Bus Width Flag
#define	HwMCFG_XDM								Hw14									//
#define	HwMCFG_BW								(Hw12+Hw11)								//
#define	HwMCFG_SDW								Hw7										//
#define	HwMCFG_ENCK								Hw6										//
#define	HwMCFG_ECKE								Hw5										// JTAG port Enable
#define	HwMCFG_SDEN								Hw4										// SDRAM Enable
#define	HwMCFG_ERF								Hw0										// Refresh cycles occurred by external refresh clock
                                			
#define	HwTST									*(volatile unsigned long *)0xF100000C	// W, Test mode
                                        	
#define	HwCSCFG_BW_8							(Hw29+Hw28)
#define	HwCSCFG_BW_16							(Hw29)
#define	HwCSCFG_PSIZE_256						HwZERO
#define	HwCSCFG_PSIZE_512						(Hw17)
#define	HwCSCFG_PSIZE_1024						(Hw18)
#define	HwCSCFG_PSIZE_2048						(Hw18+Hw17)
#define	HwCSCFG_CADDR							(Hw14)
                                        	
#define	HwCSCFG0								*(volatile unsigned long *)0xF1000010	// R/W, Ext. CS Configuration
#define	HwCSCFG0_OD								Hw27									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for OE signal
#define	HwCSCFG0_WD								Hw26									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for WE signal
#define	HwCSCFG0_URDY							Hw21									// Use Ready
#define	HwCSCFG0_RDY							Hw20									// Ready/ Busy Select
#define	HwCSCFG0_AMSK							Hw19									// Address Mask
                                			
#define	HwCSCFG1								*(volatile unsigned long *)0xF1000014	// R/W, Ext. CS Configuration
#define	HwCSCFG1_OD								Hw27									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for OE signal
#define	HwCSCFG1_WD								Hw26									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for WE signal
#define	HwCSCFG1_URDY							Hw21									// Use Ready
#define	HwCSCFG1_RDY							Hw20									// Ready/ Busy Select
#define	HwCSCFG1_AMSK							Hw19									// Address Mask
                                			
#define	HwCSCFG2								*(volatile unsigned long *)0xF1000018	// R/W, Ext. CS Configration
#define	HwCSCFG2_OD								Hw27									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for OE signal
#define	HwCSCFG2_WD								Hw26									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for WE signal
#define	HwCSCFG2_URDY							Hw21									// Use Ready
#define	HwCSCFG2_RDY							Hw20									// Ready/ Busy Select
#define	HwCSCFG2_AMSK							Hw19									// Address Mask
                                			
#define	HwCSCFG3								*(volatile unsigned long *)0xF100001C	// R/W, Ext. CS Configration
#define	HwCSCFG3_OD								Hw27									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for OE signal
#define	HwCSCFG3_WD								Hw26									// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for WE signal
#define	HwCSCFG3_URDY							Hw21									// Use Ready
#define	HwCSCFG3_RDY							Hw20									// Ready/ Busy Select
#define	HwCSCFG3_AMSK							Hw19									// Address Mask
                                			
#define	HwCLKCFG								*(volatile unsigned long *)0xF1000020	// R/W,
                                			
#define	HwSDCMD									*(volatile unsigned long *)0xF1000024	// W,

/************************************************************************
*	Channel 1 Memory Controller Register Define	(Base Addr = 0xF1001000)
************************************************************************/
#define	HwVSDCFG								*(volatile unsigned long *)0xF1001000	// R/W, SDRAM Configuration
#define	HwVSDCFG_CL								Hw31									// CAS Latency
#define	HwVSDCFG_BW								Hw30									// Bus Width
#define	HwVSDCFG_CW_MAX							(Hw29+Hw28)								//
#define	HwVSDCFG_RD0							Hw15									// Delay from RAS to CAS
#define	HwVSDCFG_RW11							Hw10									//
#define	HwVSDCFG_RW12							HwZERO									//
#define	HwVSDCFG_RW13							Hw11									//
#define	HwVSDCFG_RW_MAX							(Hw11+Hw10)								//
                                			    
#define	HwVSDFSM								*(volatile unsigned long *)0xF1001004	// R, SDRAM FSM Status Register
                                			    
#define	HwVMCFG									*(volatile unsigned long *)0xF1001008	// R/W, Miscellaneous Configuration Register
#define	HwVMCFG_RDY								Hw15									// Bus Width Flag
#define	HwVMCFG_XDM								Hw14									//
#define	HwVMCFG_BW								(Hw12+Hw11)								//
#define	HwVMCFG_SDW								Hw7										//
#define	HwVMCFG_ENCK							Hw6										//
#define	HwVMCFG_ECKE							Hw5										// JTAG port Enable
#define	HwVMCFG_SDEN							Hw4										// SDRAM Enable
#define	HwVMCFG_ERF								Hw0										// Refresh cycles occurred by external refresh clock
                                			
#define	HwVTST									*(volatile unsigned long *)0xF100100C	// W, Should not write to this - it's for TEST
                                			
#define	HwVSDCMD								*(volatile unsigned long *)0xF1001010	// W, SDRAM Command Write Register
                                    
/************************************************************************
*	NAND Flash Register Define					(Base Addr = N * 0x10000000)
************************************************************************/
#define	NAND_CS									0x60000000
                                			
#define	HwNDCMD									*(volatile unsigned long *)(NAND_CS + 0x00000000)	// R/W, Command Cycle
                                			
#define	HwNDLADR								*(volatile unsigned long *)(NAND_CS + 0x00000004)	// W, Linear Address Cycle
                                			
#define	HwNDRADR								*(volatile unsigned long *)(NAND_CS + 0x00000008)	// W, Row Address Cycle
                                			
#define	HwNDIADR								*(volatile unsigned long *)(NAND_CS + 0x0000000C)	// W, Single Address Cycle
                                			
#define	HwNDDATA								*(volatile unsigned long *)(NAND_CS + 0x00000010)	// R/W, Data Access Cycle
                                			
#define	NANDWaitTilNotBusy()					{ while(!((HwMCFG) & HwMCFG_RDY)); }				//

/************************************************************************
*	Clock Controller Register Define			(Base Addr = 0xF3000000)
************************************************************************/
#define	HwCLKCTRL								*(volatile unsigned long *)0xF3000000	// R/W, CPU & Bus Clock Control Register
#define	HwCLKCTRL_XE_EN							Hw31									// XIN Oscillator Enabled
#define	HwCLKCTRL_XE_DIS						~Hw31									// XIN Oscillator Disabled
#define	HwCLKCTRL_MB							Hw29									// Main processor clock selection register
#define	HwCLKCTRL_SB							Hw28									// Sub processor clock selection register
#define	HwCLKCTRL_CKSEL_FPLL0					HwZERO									// Direct output from PLL0
#define	HwCLKCTRL_CKSEL_FPLL1					Hw0										// Direct output form PLL1
#define	HwCLKCTRL_CKSEL_FPLL0DIV				Hw1										// Divided output from PLL0
#define	HwCLKCTRL_CKSEL_FPLL1DIV				(Hw1+Hw0)								// Divided output from PLL1
#define	HwCLKCTRL_CKSEL_FXIN					Hw2										// XIN from external main oscillator(shared by UTMI clock)
#define	HwCLKCTRL_CKSEL_FXINDIV					(Hw2+Hw0)								// Divided output from XIN
#define	HwCLKCTRL_CKSEL_FXTIN					(Hw2+Hw1)								// XTIN from external sub oscillator(shared by RTC)
#define	HwCLKCTRL_CKSEL_FXTINDIV				(Hw2+Hw1+Hw0)							// Divided output from XTIN
#define	HwCLKCTRL_CKSEL_Fpll0					HwZERO
#define	HwCLKCTRL_CKSEL_Fpll1					Hw0
#define	HwCLKCTRL_CKSEL_Fpll0div				Hw1
#define	HwCLKCTRL_CKSEL_Fpll1div				(Hw1+Hw0)
#define	HwCLKCTRL_CKSEL_Fxin					HwCLKCTRL_CKSEL_FXIN
#define	HwCLKCTRL_CKSEL_Fxindiv					(Hw2+Hw0)
#define	HwCLKCTRL_CKSEL_Fxtin					(Hw2+Hw1)
#define	HwCLKCTRL_CKSEL_Fxtindiv				(Hw2+Hw1+Hw0)
                                    			
#define	HwPLLCFG(X)								*((volatile unsigned long *)0xF3000004 + (X))
#define	HwPLL0CFG								*(volatile unsigned long *)0xF3000004	// R/W, PLL0 Configuration Register
#define	HwPLL0CFG_PD_DIS						Hw31									// PLL Disable
#define	HwPLL0CFG_PD_EN							~Hw31									// PLL Enable
                                    			
#define	HwPLL1CFG								*(volatile unsigned long *)0xF3000008	// R/W, PLL1 Configuration Register
#define	HwPLL1CFG_PD_DIS						Hw31									// PLL Disable
#define	HwPLL1CFG_PD_EN							~Hw31									// PLL Enable
                                    			
#define	HwCLKDIVC								*(volatile unsigned long *)0xF300000C	// R/W, Divided Clock Configuration Register
#define	HwCLKDIVC_P0E_EN						Hw31									// PLL0 Divider Enable
#define	HwCLKDIVC_P0E_DIS						~Hw31									// PLL0 Divider Disable
#define	HwCLKDIVC_P1E_EN						Hw23									// PLL1 Divider Enabled
#define	HwCLKDIVC_XE_EN							Hw15									// XIN Divider Enable
#define	HwCLKDIVC_XE_DIS						~Hw15									// XIN Divider Disable
#define	HwCLKDIVC_XTE_EN						Hw7										// XTIN Divider Enable
#define	HwCLKDIVC_XTE_DIS						~Hw7									// XTIN Divider Disable
                                    			
#define	HwCLKDIVC1								*(volatile unsigned long *)0xF3000010	// R/W, PLL0 Divider 1 Configuration Register
#define	HwCLKDIVC1_P1E_EN						Hw15									// PLL1 Divider 1 Enabled
#define	HwCLKDIVC1_P0E_EN						Hw7										// PLL0	Divider 0 Enabled
                                    			
#define	HwMODECTR								*(volatile unsigned long *)0xF3000014	// R/W, Operating Mode Control Register
#define	HwMODECTR_PDCK_XTIN						Hw9										// XTIN Selected
#define	HwMODECTR_PDCK_XIN						~Hw9									// XIN Selected
#define	HwMODECTR_PD_ON							Hw8										// Enter Power Down mode
#define	HwMODECTR_PD_OFF						~Hw8									// Stay in Normal mode
#define	HwMODECTR_HALT_ON						Hw0										// Enter Halt mode
#define	HwMODECTR_HALT_OFF						~Hw0									// Stay in Normal mode
                                    			
#define	HwBCLKCTR								*(volatile unsigned long *)0xF3000018	// R/W, Bus Clock Enable Register
#define	HwBCLKCTR_MBC_ON						Hw31									// Enable Main Bus Components (should be '1')
#define HwBCLKCTR_MB							Hw30									// Enable MailBox
#define	HwBCLKCTR_M2MS							Hw29									// Enable Memory to Memory Scaler
#define	HwBCLKCTR_VIC_ON						Hw28									// Enable Vectored Interrupt Controller
#define	HwBCLKCTR_MAINPRO						Hw27									// Enable Main processor
#define	HwBCLKCTR_TMR_ON						Hw26									// Enable the Bus Clock for Timer Controller
#define	HwBCLKCTR_TMR_OFF						~Hw26									// Disable the Bus Clock for Timer Controller
#define	HwBCLKCTR_VCH_ON						Hw25									// Enable Video Controller Hardware
#define	HwBCLKCTR_ADC_ON						Hw24									// Enable the Bus Clock for ADC controller
#define	HwBCLKCTR_ADC_OFF						~Hw24									// Disable the Bus Clock for ADC Controller
#define HwBCLKCTR_SUBPRO						Hw23									// Enable Sub processor
#define HwBCLKCTR_MEM_ON						Hw22									// Enable Memory Controller
#define	HwBCLKCTR_RTC_ON						Hw21									// Enable the Bus Clock for RTC Controller
#define	HwBCLKCTR_RTC_OFF						~Hw21									// Disable the Bus Clock for RTC Controller
#define	HwBCLKCTR_2D							Hw20									// Enable the Graphic 2D
#define	HwBCLKCTR_SUBPROPERI					Hw19									// Enable the Sub processor peripherals
#define	HwBCLKCTR_SPI_ON						Hw18									// Enable the Bus Clock for SPI Slave Interface Controller
#define	HwBCLKCTR_SPI_OFF						~Hw18									// Disable the Bus Clock for SPI Slave Interface Controller
#define HwBCLKCTR_SPDIF_ON						Hw17									// Enable SPDIF Transmitter
#define	HwBCLKCTR_ECC_ON						Hw16									// Enable the Bus Clock for ECC Controller
#define	HwBCLKCTR_ECC_OFF						~Hw16									// Disable the Bus Clock for ECC Controller
#define	HwBCLKCTR_GPSB1_ON						Hw15
#define	HwBCLKCTR_GPSB1_OFF						~Hw15
#define	HwBCLKCTR_DAI_ON						Hw14									// Enable the Bus Clock for DAI Controller
#define	HwBCLKCTR_DAI_OFF						~Hw14									// Disable the Bus Clock for DAI Controller
#define	HwBCLKCTR_GS_ON							Hw13									// Enable the Bus Clock for GSIO Controller
#define	HwBCLKCTR_GS_OFF						~Hw13									// Disable the Bus Clock for GSIO Controller
#define	HwBCLKCTR_UA1_ON						Hw12									// Enable the Bus Clock for UART1 Controller
#define	HwBCLKCTR_UA1_OFF						~Hw12									// Disable the Bus Clock for UART1 Controller
#define	HwBCLKCTR_UA0_ON						Hw11									// Enable the Bus Clock for UART0 Controller
#define	HwBCLKCTR_UA0_OFF						~Hw11									// Disable the Bus Clock for UART0 Controller
#define	HwBCLKCTR_EHI_ON						Hw10									// Enable the Bus Clock for External Host Interface Controller
#define	HwBCLKCTR_EHI_OFF						~Hw10									// Disable the Bus Clock for External Host Interface Controller
#define	HwBCLKCTR_ND_ON							Hw9										// Enable the Bus Clock for NAND Flash Controller
#define	HwBCLKCTR_ND_OFF						~Hw9									// Disable the Bus Clock for NAND Flash Controller
#define	HwBCLKCTR_I2C_ON						Hw8										// Enable the Bus Clock for I2C Controller
#define	HwBCLKCTR_I2C_OFF						~Hw8									// Disable the Bus Clock for I2C Controller
#define	HwBCLKCTR_MS_ON							Hw7										// Enable the Bus Clock for Memory Stick Controller
#define	HwBCLKCTR_MS_OFF						~Hw7									// Disable the Bus Clock for Memory Stick Controller
#define	HwBCLKCTR_SD_ON							Hw6										// Enable the Bus Clock for SD/MMC Controller
#define	HwBCLKCTR_SD_OFF						~Hw6									// Disable the Bus Clock for SD/MMC Controller
#define	HwBCLKCTR_DMA_ON						Hw5										// Enable the Bus Clock for DMA Controller
#define	HwBCLKCTR_DMA_OFF						~Hw5									// Disable the Bus Clock for DMA Controller
#define	HwBCLKCTR_HDD_ON						Hw4										// Enable HDD Controller
#define	HwBCLKCTR_CIC_ON						Hw3										// Enable Camera Interface Controller
#define	HwBCLKCTR_LCD_ON						Hw2										// Enable LCD Controller
#define	HwBCLKCTR_UB_ON							Hw1										// Enable the Bus Clock for USB2.0 Device Controller
#define	HwBCLKCTR_UB_OFF						~Hw1									// Disable the Bus Clock for USB2.0 Device Controller
#define	HwBCLKCTR_UBH_ON						Hw0										// Enable the Bus Clock for USB1.1 Host Controller
#define	HwBCLKCTR_UBH_OFF						~Hw0									// Disable the Bus Clock for USB1.1 Host Controller
                                    			
#define	HwSWRESET								*(volatile unsigned long *)0xF300001C	// R/W, UART Clock
#define	HwSWRESET_MBC_ON						Hw31									// Enable Main Bus Components (should be '1')
#define HwSWRESET_MB							Hw30									// Enable MailBox
#define	HwSWRESET_M2MS							Hw29									// Enable Memory to Memory Scaler
#define	HwSWRESET_VIC							Hw28									// Enable Vectored Interrupt Controller
#define	HwSWRESET_MAINPRO						Hw27									// Enable Main processor
#define	HwSWRESET_TMR_ON						Hw26									// Enable the Bus Clock for Timer Controller
#define	HwSWRESET_VCH_ON						Hw25									// Enable Video Controller Hardware
#define	HwSWRESET_ADC_ON						Hw24									// Enable the Bus Clock for ADC controller
#define HwSWRESET_SUBPRO						Hw23									// Enable Sub processor
#define HwSWRESET_MEM_ON						Hw22									// Enable Memory Controller
#define	HwSWRESET_RTC_ON						Hw21									// Enable the Bus Clock for RTC Controller
#define	HwSWRESET_2D							Hw20									// Enable the Graphic 2D
#define HwSWRESET_SUBPROPERI					Hw19									// Enable the Sub processor peripherals
#define	HwSWRESET_SPI_ON						Hw18									// Enable the Bus Clock for SPI Slave Interface Controller
#define HwSWRESET_SPDIF_ON						Hw17									// Enable SPDIF Transmitter
#define	HwSWRESET_ECC_ON						Hw16									// Enable the Bus Clock for ECC Controller
#define	HwSWRESET_GPSB_1						Hw15
#define	HwSWRESET_DAI_ON						Hw14									// Enable the Bus Clock for DAI Controller
#define	HwSWRESET_GS_ON							Hw13									// Enable the Bus Clock for GSIO Controller
#define	HwSWRESET_UA1_ON						Hw12									// Enable the Bus Clock for UART1 Controller
#define	HwSWRESET_UA0_ON						Hw11									// Enable the Bus Clock for UART0 Controller
#define	HwSWRESET_EHI_ON						Hw10									// Enable the Bus Clock for External Host Interface Controller
#define	HwSWRESET_ND_ON							Hw9										// Enable the Bus Clock for NAND Flash Controller
#define	HwSWRESET_I2C_ON						Hw8										// Enable the Bus Clock for I2C Controller
#define	HwSWRESET_MS_ON							Hw7										// Enable the Bus Clock for Memory Stick Controller
#define	HwSWRESET_SD_ON							Hw6										// Enable the Bus Clock for SD/MMC Controller
#define	HwSWRESET_DMA_ON						Hw5										// Enable the Bus Clock for DMA Controller
#define	HwSWRESET_HDD_ON						Hw4										// Enable HDD Controller
#define	HwSWRESET_CIC_ON						Hw3										// Enable Camera Interface Controller
#define	HwSWRESET_LCD_ON						Hw2										// Enable LCD Controller
#define	HwSWRESET_UB_ON							Hw1										// Enable the Bus Clock for USB2.0 Device Controller
#define	HwSWRESET_UBH_ON						Hw0										// Enable the Bus Clock for USB1.1 Host Controller
                                    			
#define	HwPCK_EN_EN								Hw28									// Clock Divider Enable
#define	HwPCK_SEL								Hw24
#define	HwPCK_SEL_PLL0							(0 * HwPCK_SEL)							// PLL0 Direct Output
#define	HwPCK_SEL_PLL1							(1 * HwPCK_SEL)							// PLL1 Direct Output
#define	HwPCK_SEL_PLL0DIV						(2 * HwPCK_SEL)							// PLL0 Divider Output
#define	HwPCK_SEL_PLL1DIV						(3 * HwPCK_SEL)							// PLL1 Divider Output
#define	HwPCK_SEL_XIN							(4 * HwPCK_SEL)							// XIN Output
#define	HwPCK_SEL_XINDIV						(5 * HwPCK_SEL)							// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_SEL_XTIN							(6 * HwPCK_SEL)							// XTIN Output
#define	HwPCK_SEL_XIN_1							(6 * HwPCK_SEL)							// XIN Output
#define	HwPCK_SEL_XTINDIV						(7 * HwPCK_SEL)							// XTIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_SEL_XINDIV_1						(7 * HwPCK_SEL)							// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_SEL_PLL0DIV1						(8 * HwPCK_SEL)							// PLL0 Divider 1 Output
#define	HwPCK_SEL_PLL1DIV1						(9 * HwPCK_SEL)							// PLL1 Divider 1 Output
#define	HwPCK_SEL_EXTCLK						(10 * HwPCK_SEL)						// External Clock
#define	HwPCK_SEL_TMR1							(11 * HwPCK_SEL)						// Timer counter output 1
#define	HwPCK_SEL_TMR2							(12 * HwPCK_SEL)						// Timer counter output 2
#define	HwPCK_SEL_TMR3							(13 * HwPCK_SEL)						// Timer counter output 3
#define	HwPCK_SEL_TMR4							(14 * HwPCK_SEL)						// Timer counter output 4
#define	HwPCK_SEL_TMR5							(15 * HwPCK_SEL)						// Timer counter output 5
                                    			
#define	HwPCK_USB11H							*(volatile unsigned long *)0xF3000020	// R/W, USB11H Clock Control Register
#define	HwPCK_USB11H_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_USB11H_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_USB11H_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_USB11H_SEL_PLL0DIV				Hw25									// PLL0 Divider Output
#define	HwPCK_USB11H_SEL_PLL1DIV				(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_USB11H_SEL_XIN					Hw26									// XIN Output
#define	HwPCK_USB11H_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_USB11H_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_USB11H_SEL_XTINDIV				(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_USB11H_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_USB11H_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_USB11H_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_USB11H_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_USB11H_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_USB11H_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_USB11H_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_USB11H_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_SDMMC								*(volatile unsigned long *)0xF3000024	// R/W, SD/MMC Clock Control Register
#define	HwPCK_SDMMC_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_SDMMC_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_SDMMC_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_SDMMC_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_SDMMC_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_SDMMC_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_SDMMC_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_SDMMC_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_SDMMC_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_SDMMC_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_SDMMC_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_SDMMC_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_SDMMC_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_SDMMC_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_SDMMC_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_SDMMC_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_SDMMC_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_MSTICK							*(volatile unsigned long *)0xF3000028	// R/W, Memory Stick Clock Control Register
#define	HwPCK_MSTICK_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_MSTICK_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_MSTICK_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_MSTICK_SEL_PLL0DIV				Hw25									// PLL0 Divider Output
#define	HwPCK_MSTICK_SEL_PLL1DIV				(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_MSTICK_SEL_XIN					Hw26									// XIN Output
#define	HwPCK_MSTICK_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_MSTICK_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_MSTICK_SEL_XTINDIV				(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_MSTICK_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_MSTICK_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_MSTICK_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_MSTICK_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_MSTICK_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_MSTICK_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_MSTICK_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_MSTICK_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_I2C								*(volatile unsigned long *)0xF300002C	// R/W, I2C Clock Control Register
#define	HwPCK_I2C_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_I2C_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_I2C_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_I2C_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_I2C_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_I2C_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_I2C_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_I2C_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_I2C_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_I2C_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_I2C_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_I2C_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_I2C_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_I2C_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_I2C_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_I2C_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_I2C_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_LCD								*(volatile unsigned long *)0xF3000030	// R/W, LCD Clock Control Register
#define	HwPCK_LCD_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_LCD_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_LCD_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_LCD_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_LCD_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_LCD_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_LCD_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_LCD_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_LCD_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_LCD_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_LCD_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_LCD_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_LCD_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_LCD_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_LCD_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_LCD_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_LCD_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_CAM								*(volatile unsigned long *)0xF3000034	// R/W, Camera Clock Control Register
#define	HwPCK_CAM_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_CAM_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_CAM_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_CAM_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_CAM_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_CAM_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_CAM_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_CAM_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_CAM_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_CAM_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_CAM_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_CAM_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_CAM_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_CAM_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_CAM_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_CAM_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_CAM_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_UART0								*(volatile unsigned long *)0xF3000038	// R/W, UART0 Clock Control Register
#define	HwPCK_UART0_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_UART0_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_UART0_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_UART0_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_UART0_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_UART0_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_UART0_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_UART0_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_UART0_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_UART0_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_UART0_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_UART0_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_UART0_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_UART0_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_UART0_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_UART0_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_UART0_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_UART1								*(volatile unsigned long *)0xF300003C	// R/W, UART1 Clock Control Register
#define	HwPCK_UART1_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_UART1_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_UART1_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_UART1_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_UART1_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_UART1_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_UART1_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_UART1_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_UART1_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_UART1_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_UART1_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_UART1_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_UART1_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_UART1_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_UART1_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_UART1_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_UART1_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_GSIO								*(volatile unsigned long *)0xF3000040	// R/W, GSIO Clock Control Register
#define	HwPCK_GSIO_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_GSIO_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_GSIO_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_GSIO_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_GSIO_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_GSIO_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_GSIO_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_GSIO_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_GSIO_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_GSIO_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_GSIO_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_GSIO_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_GSIO_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_GSIO_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_GSIO_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_GSIO_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_GSIO_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_TCT								*(volatile unsigned long *)0xF3000044	// R/W, Timer T Clock Control Register
#define	HwPCK_TCT_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_TCT_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_TCT_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_TCT_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_TCT_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_TCT_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_TCT_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_TCT_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_TCT_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_TCT_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_TCT_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_TCT_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_TCT_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_TCT_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_TCT_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_TCT_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_TCT_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_TCX								*(volatile unsigned long *)0xF3000048	// R/W, Timer X Clock Control Register
#define	HwPCK_TCX_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_TCX_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_TCX_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_TCX_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_TCX_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_TCX_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_TCX_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_TCX_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_TCX_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_TCX_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_TCX_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_TCX_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_TCX_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_TCX_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_TCX_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_TCX_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_TCX_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_TCZ								*(volatile unsigned long *)0xF300004C	// R/W, Timer Z Clock Control Register
#define	HwPCK_TCZ_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_TCZ_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_TCZ_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_TCZ_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_TCZ_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_TCZ_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_TCZ_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_TCZ_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_TCZ_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_TCZ_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_TCZ_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_TCZ_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_TCZ_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_TCZ_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_TCZ_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_TCZ_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_TCZ_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_ADC								*(volatile unsigned long *)0xF3000050	// R/W, ADC Clock Control Register
#define	HwPCK_ADC_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_ADC_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_ADC_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_ADC_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_ADC_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_ADC_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_ADC_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_ADC_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_ADC_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_ADC_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_ADC_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_ADC_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_ADC_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_ADC_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_ADC_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_ADC_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_ADC_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_DAI								*(volatile unsigned long *)0xF3000054	// R/W, DAI Clock Control Register
#define	HwPCK_DAI_MD							Hw31									// DCO Mode
#define	HwPCK_DAI_EN_EN							Hw28									// Clock Divider Enable
#define	HwPCK_DAI_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_DAI_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_DAI_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_DAI_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_DAI_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_DAI_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_DAI_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_DAI_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_DAI_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_DAI_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_DAI_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_DAI_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_DAI_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_DAI_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_DAI_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_DAI_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_SPDIF								*(volatile unsigned long *)0xF3000058	// R/W, SPDIF TX Clock Control Register
#define	HwPCK_SPDIF_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_SPDIF_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_SPDIF_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_SPDIF_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_SPDIF_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_SPDIF_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_SPDIF_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_SPDIF_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_SPDIF_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_SPDIF_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_SPDIF_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_SPDIF_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_SPDIF_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_SPDIF_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_SPDIF_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_SPDIF_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_SPDIF_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_RFREQ								*(volatile unsigned long *)0xF300005C	// R/W, SDRAM Refresh Clock Control Register
#define	HwPCK_RFREQ_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_RFREQ_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_RFREQ_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_RFREQ_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_RFREQ_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_RFREQ_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_RFREQ_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_RFREQ_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_RFREQ_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_RFREQ_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_RFREQ_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_RFREQ_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_RFREQ_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_RFREQ_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_RFREQ_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_RFREQ_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_RFREQ_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_SPIS								*(volatile unsigned long *)0xF3000060	// R/W, SPI Slave Clock Control Register
#define	HwPCK_SPIS_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_SPIS_SEL_PLL0						HwZERO									// PLL0 Direct Output
#define	HwPCK_SPIS_SEL_PLL1						Hw24									// PLL1 Direct Output
#define	HwPCK_SPIS_SEL_PLL0DIV					Hw25									// PLL0 Divider Output
#define	HwPCK_SPIS_SEL_PLL1DIV					(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_SPIS_SEL_XIN						Hw26									// XIN Output
#define	HwPCK_SPIS_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_SPIS_SEL_XTIN						(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_SPIS_SEL_XTINDIV					(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_SPIS_SEL_PLL0DIV1					Hw27									// PLL0 Divider 1 Output
#define	HwPCK_SPIS_SEL_PLL1DIV1					(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_SPIS_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_SPIS_SEL_TMR1						(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_SPIS_SEL_TMR2						(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_SPIS_SEL_TMR3						(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_SPIS_SEL_TMR4						(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_SPIS_SEL_TMR5						(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5
                                    			
#define	HwPCK_SCALER							*(volatile unsigned long *)0xF3000064	// R/W, CIF Scaler Clock Control Register
#define	HwPCK_SCALER_EN_EN						Hw28									// Clock Divider Enable
#define	HwPCK_SCALER_SEL_PLL0					HwZERO									// PLL0 Direct Output
#define	HwPCK_SCALER_SEL_PLL1					Hw24									// PLL1 Direct Output
#define	HwPCK_SCALER_SEL_PLL0DIV				Hw25									// PLL0 Divider Output
#define	HwPCK_SCALER_SEL_PLL1DIV				(Hw25+Hw24)								// PLL1 Divider Output
#define	HwPCK_SCALER_SEL_XIN					Hw26									// XIN Output
#define	HwPCK_SCALER_SEL_XINDIV					(Hw26+Hw24)								// XIN Divider Output(EXTCLK for DAI and SPDIF)
#define	HwPCK_SCALER_SEL_XTIN					(Hw26+Hw25)								// XTIN direct output
#define	HwPCK_SCALER_SEL_XTINDIV				(Hw26+Hw25+Hw24)						// XTIN	divider output
#define	HwPCK_SCALER_SEL_PLL0DIV1				Hw27									// PLL0 Divider 1 Output
#define	HwPCK_SCALER_SEL_PLL1DIV1				(Hw27+Hw24)								// PLL1 Divider 1 Output
#define	HwPCK_SCALER_SEL_EXTCLK					(Hw27+Hw25)								// External Clock
#define	HwPCK_SCALER_SEL_TMR1					(Hw27+Hw25+Hw24)						// Timer counter output 1
#define	HwPCK_SCALER_SEL_TMR2					(Hw27+Hw26)								// Timer counter output 2
#define	HwPCK_SCALER_SEL_TMR3					(Hw27+Hw26+Hw24)						// Timer counter output 3
#define	HwPCK_SCALER_SEL_TMR4					(Hw27+Hw26+Hw25)						// Timer counter output 4
#define	HwPCK_SCALER_SEL_TMR5					(Hw27+Hw26+Hw25+Hw24)					// Timer counter output 5

#define	HwBCLKMASKE							*(volatile unsigned long *)0xF3000090

/************************************************************************
*	Vectored Interrupt controller Define		(Base Addr = 0xF3001000)
************************************************************************/
typedef volatile struct {
	unsigned	IEN;																	// Enable Interrupt
	unsigned	ICLR;																	// Clear Interrupt
	unsigned	ISTS;																	// Interrupt Status
	unsigned	ISEL;																	// IRQ/FIQ selection
	unsigned	SRC;																	// Test interrupt selection
	unsigned	MSTS;																	// Masked Interrupt Status
	unsigned	TREQ;																	// Test interrupt request
	unsigned	IPOL;																	// Polarity of interrupt signal (0 = active high, 1 = active low)
	unsigned	IRQ;																	// IRQ interrupt status
	unsigned	FIQ;																	// FIQ interrupt status
	unsigned	MIRQ;																	// Masked IRQ interrupt status
	unsigned	MFIQ;																	// Masked FIQ interrupt status
	unsigned	MODE;																	// Trigger mode selection (0 = edge, 1 = level)
	unsigned	SYNC;																	// Enable Synchronizing
	unsigned	WKEN;																	// Select Wakeup signal
	unsigned	MODEA;																	// Edge trigger mode selection (0 = single edge, 1 = both edge)
	unsigned	IRQMSK;																	// IRQ Output Masking Register
	unsigned	ALLMSK;																	// All Mask Register
} sHwINT;

#define	HwVIC_BASE								*(volatile unsigned long *)0xF3001000
#define	HwSUBVIC_BASE							*(volatile unsigned long *)0xFF011000

#define	HwIEN									*(volatile unsigned long *)0xF3001000	// R/W, Interrupt Enable Register
#define	HwIEN_ECC								Hw31									//
#define	HwIEN_ADC								Hw30									//
#define	HwIEN_LCD								Hw29									//
#define	HwIEN_CAM								Hw28									//
#define	HwIEN_SD								Hw27									//
#define	HwIEN_NFC								Hw26									//
#define	HwIEN_MS								Hw25									//
#define	HwIEN_HDD								Hw24									//
#define	HwIEN_DMA								Hw23									//
#define	HwIEN_UH								Hw22									//
#define	HwIEN_UD								Hw21									//
#define	HwIEN_UDMA								Hw20									//
#define	HwIEN_UT1								Hw19									//
#define	HwIEN_UT0								Hw18									//
#define	HwIEN_HPI								Hw17									//
#define	HwIEN_CDRX								Hw16									//
#define	HwIEN_DAITX								Hw15									//
#define	HwIEN_DAIRX								Hw14									//
#define	HwIEN_I2C								Hw13									//
#define	HwIEN_SC								Hw12									//
#define	HwIEN_GSIO								Hw11									//
#define	HwIEN_VIDEO								Hw10									//
#define	HwIEN_SPDTX								Hw9										//
#define	HwIEN_SCORE								Hw8										//
#define	HwIEN_TC1								Hw7										//
#define	HwIEN_TC0								Hw6										//
#define	HwIEN_GPSB								Hw5										//
#define	HwIEN_RTC								Hw4										//
#define	HwIEN_EI3								Hw3										//
#define	HwIEN_EI2								Hw2										//
#define	HwIEN_EI1								Hw1										//
#define	HwIEN_EI0								Hw0										//
                                    			
#define	HwCLR									*(volatile unsigned long *)0xF3001004	// R/W, Interrupt Clear Register
#define	HwCLR_ECC								Hw31									//
#define	HwCLR_ADC								Hw30									//
#define	HwCLR_LCD								Hw29									//
#define	HwCLR_CAM								Hw28									//
#define	HwCLR_SD								Hw27									//
#define	HwCLR_NFC								Hw26									//
#define	HwCLR_MS								Hw25									//
#define	HwCLR_HDD								Hw24									//
#define	HwCLR_DMA								Hw23									//
#define	HwCLR_UH								Hw22									//
#define	HwCLR_UD								Hw21									//
#define	HwCLR_UDMA								Hw20									//
#define	HwCLR_UT1								Hw19									//
#define	HwCLR_UT0								Hw18									//
#define	HwCLR_HPI								Hw17									//
#define	HwCLR_CDRX								Hw16									//
#define	HwCLR_DAITX								Hw15									//
#define	HwCLR_DAIRX								Hw14									//
#define	HwCLR_I2C								Hw13									//
#define	HwCLR_SC								Hw12									//
#define	HwCLR_GSIO								Hw11									//
#define	HwCLR_VIDEO								Hw10									//
#define	HwCLR_SPDTX								Hw9										//
#define	HwCLR_SCORE								Hw8										//
#define	HwCLR_TC1								Hw7										//
#define	HwCLR_TC0								Hw6										//
#define	HwCLR_GPSB								Hw5										//
#define	HwCLR_RTC								Hw4										//
#define	HwCLR_EI3								Hw3										//
#define	HwCLR_EI2								Hw2										//
#define	HwCLR_EI1								Hw1										//
#define	HwCLR_EI0								Hw0										//
                                    			
#define	HwSTS									*(volatile unsigned long *)0xF3001008	// R, Interrupt Status Register
#define	HwSTS_ECC								Hw31									//
#define	HwSTS_ADC								Hw30									//
#define	HwSTS_LCD								Hw29									//
#define	HwSTS_CAM								Hw28									//
#define	HwSTS_SD								Hw27									//
#define	HwSTS_NFC								Hw26									//
#define	HwSTS_MS								Hw25									//
#define	HwSTS_HDD								Hw24									//
#define	HwSTS_DMA								Hw23									//
#define	HwSTS_UH								Hw22									//
#define	HwSTS_UD								Hw21									//
#define	HwSTS_UDMA								Hw20									//
#define	HwSTS_UT1								Hw19									//
#define	HwSTS_UT0								Hw18									//
#define	HwSTS_HPI								Hw17									//
#define	HwSTS_CDRX								Hw16									//
#define	HwSTS_DAITX								Hw15									//
#define	HwSTS_DAIRX								Hw14									//
#define	HwSTS_I2C								Hw13									//
#define	HwSTS_SC								Hw12									//
#define	HwSTS_GSIO								Hw11									//
#define	HwSTS_VIDEO								Hw10									//
#define	HwSTS_SPDTX								Hw9										//
#define	HwSTS_SCORE								Hw8										//
#define	HwSTS_TC1								Hw7										//
#define	HwSTS_TC0								Hw6										//
#define	HwSTS_GPSB								Hw5										//
#define	HwSTS_RTC								Hw4										//
#define	HwSTS_EI3								Hw3										//
#define	HwSTS_EI2								Hw2										//
#define	HwSTS_EI1								Hw1										//
#define	HwSTS_EI0								Hw0										//
                                    			
#define	HwSEL									*(volatile unsigned long *)0xF300100C	// R/W, IRQ or FIR Selection Register
#define	HwSEL_ECC								Hw31									//
#define	HwSEL_ADC								Hw30									//
#define	HwSEL_LCD								Hw29									//
#define	HwSEL_CAM								Hw28									//
#define	HwSEL_SD								Hw27									//
#define	HwSEL_NFC								Hw26									//
#define	HwSEL_MS								Hw25									//
#define	HwSEL_HDD								Hw24									//
#define	HwSEL_DMA								Hw23									//
#define	HwSEL_UH								Hw22									//
#define	HwSEL_UD								Hw21									//
#define	HwSEL_UDMA								Hw20									//
#define	HwSEL_UT1								Hw19									//
#define	HwSEL_UT0								Hw18									//
#define	HwSEL_HPI								Hw17									//
#define	HwSEL_CDRX								Hw16									//
#define	HwSEL_DAITX								Hw15									//
#define	HwSEL_DAIRX								Hw14									//
#define	HwSEL_I2C								Hw13									//
#define	HwSEL_SC								Hw12									//
#define	HwSEL_GSIO								Hw11									//
#define	HwSEL_VIDEO								Hw10									//
#define	HwSEL_SPDTX								Hw9										//
#define	HwSEL_SCORE								Hw8										//
#define	HwSEL_TC1								Hw7										//
#define	HwSEL_TC0								Hw6										//
#define	HwSEL_GPSB								Hw5										//
#define	HwSEL_RTC								Hw4										//
#define	HwSEL_EI3								Hw3										//
#define	HwSEL_EI2								Hw2										//
#define	HwSEL_EI1								Hw1										//
#define	HwSEL_EI0								Hw0										//
                                    			
#define	HwSRC									*(volatile unsigned long *)0xF3001010	// R/W, Real or Test Interrupt Selection Register
#define	HwSRC_ECC								Hw31									//
#define	HwSRC_ADC								Hw30									//
#define	HwSRC_LCD								Hw29									//
#define	HwSRC_CAM								Hw28									//
#define	HwSRC_SD								Hw27									//
#define	HwSRC_NFC								Hw26									//
#define	HwSRC_MS								Hw25									//
#define	HwSRC_HDD								Hw24									//
#define	HwSRC_DMA								Hw23									//
#define	HwSRC_UH								Hw22									//
#define	HwSRC_UD								Hw21									//
#define	HwSRC_UDMA								Hw20									//
#define	HwSRC_UT1								Hw19									//
#define	HwSRC_UT0								Hw18									//
#define	HwSRC_HPI								Hw17									//
#define	HwSRC_CDRX								Hw16									//
#define	HwSRC_DAITX								Hw15									//
#define	HwSRC_DAIRX								Hw14									//
#define	HwSRC_I2C								Hw13									//
#define	HwSRC_SC								Hw12									//
#define	HwSRC_GSIO								Hw11									//
#define	HwSRC_VIDEO								Hw10									//
#define	HwSRC_SPDTX								Hw9										//
#define	HwSRC_SCORE								Hw8										//
#define	HwSRC_TC1								Hw7										//
#define	HwSRC_TC0								Hw6										//
#define	HwSRC_GPSB								Hw5										//
#define	HwSRC_RTC								Hw4										//
#define	HwSRC_EI3								Hw3										//
#define	HwSRC_EI2								Hw2										//
#define	HwSRC_EI1								Hw1										//
#define	HwSRC_EI0								Hw0										//
                                    			
#define	HwMSTS									*(volatile unsigned long *)0xF3001014	// R/W, Masked Status Register
#define	HwMSTS_ECC								Hw31									//
#define	HwMSTS_ADC								Hw30									//
#define	HwMSTS_LCD								Hw29									//
#define	HwMSTS_CAM								Hw28									//
#define	HwMSTS_SD								Hw27									//
#define	HwMSTS_NFC								Hw26									//
#define	HwMSTS_MS								Hw25									//
#define	HwMSTS_HDD								Hw24									//
#define	HwMSTS_DMA								Hw23									//
#define	HwMSTS_UH								Hw22									//
#define	HwMSTS_UD								Hw21									//
#define	HwMSTS_UDMA								Hw20									//
#define	HwMSTS_UT1								Hw19									//
#define	HwMSTS_UT0								Hw18									//
#define	HwMSTS_HPI								Hw17									//
#define	HwMSTS_CDRX								Hw16									//
#define	HwMSTS_DAITX							Hw15									//
#define	HwMSTS_DAIRX							Hw14									//
#define	HwMSTS_I2C								Hw13									//
#define	HwMSTS_SC								Hw12									//
#define	HwMSTS_GSIO								Hw11									//
#define	HwMSTS_VIDEO							Hw10									//
#define	HwMSTS_SPDTX							Hw9										//
#define	HwMSTS_SCORE							Hw8										//
#define	HwMSTS_TC1								Hw7										//
#define	HwMSTS_TC0								Hw6										//
#define	HwMSTS_GPSB								Hw5										//
#define	HwMSTS_RTC								Hw4										//
#define	HwMSTS_EI3								Hw3										//
#define	HwMSTS_EI2								Hw2										//
#define	HwMSTS_EI1								Hw1										//
#define	HwMSTS_EI0								Hw0										//
                                    			
#define	HwTIG									*(volatile unsigned long *)0xF3001018	// R/W, Test Interrupt Generation Register
#define	HwTIG_ECC								Hw31									//
#define	HwTIG_ADC								Hw30									//
#define	HwTIG_LCD								Hw29									//
#define	HwTIG_CAM								Hw28									//
#define	HwTIG_SD								Hw27									//
#define	HwTIG_NFC								Hw26									//
#define	HwTIG_MS								Hw25									//
#define	HwTIG_HDD								Hw24									//
#define	HwTIG_DMA								Hw23									//
#define	HwTIG_UH								Hw22									//
#define	HwTIG_UD								Hw21									//
#define	HwTIG_UDMA								Hw20									//
#define	HwTIG_UT1								Hw19									//
#define	HwTIG_UT0								Hw18									//
#define	HwTIG_HPI								Hw17									//
#define	HwTIG_CDRX								Hw16									//
#define	HwTIG_DAITX								Hw15									//
#define	HwTIG_DAIRX								Hw14									//
#define	HwTIG_I2C								Hw13									//
#define	HwTIG_SC								Hw12									//
#define	HwTIG_GSIO								Hw11									//
#define	HwTIG_VIDEO								Hw10									//
#define	HwTIG_SPDTX								Hw9										//
#define	HwTIG_SCORE								Hw8										//
#define	HwTIG_TC1								Hw7										//
#define	HwTIG_TC0								Hw6										//
#define	HwTIG_GPSB								Hw5										//
#define	HwTIG_RTC								Hw4										//
#define	HwTIG_EI3								Hw3										//
#define	HwTIG_EI2								Hw2										//
#define	HwTIG_EI1								Hw1										//
#define	HwTIG_EI0								Hw0										//
                                    			
#define	HwPOL									*(volatile unsigned long *)0xF300101C	// R/W, Interrupt Polarity Register
#define	HwPOL_ECC								Hw31									//
#define	HwPOL_ADC								Hw30									//
#define	HwPOL_LCD								Hw29									//
#define	HwPOL_CAM								Hw28									//
#define	HwPOL_SD								Hw27									//
#define	HwPOL_NFC								Hw26									//
#define	HwPOL_MS								Hw25									//
#define	HwPOL_HDD								Hw24									//
#define	HwPOL_DMA								Hw23									//
#define	HwPOL_UH								Hw22									//
#define	HwPOL_UD								Hw21									//
#define	HwPOL_UDMA								Hw20									//
#define	HwPOL_UT1								Hw19									//
#define	HwPOL_UT0								Hw18									//
#define	HwPOL_HPI								Hw17									//
#define	HwPOL_CDRX								Hw16									//
#define	HwPOL_DAITX								Hw15									//
#define	HwPOL_DAIRX								Hw14									//
#define	HwPOL_I2C								Hw13									//
#define	HwPOL_SC								Hw12									//
#define	HwPOL_GSIO								Hw11									//
#define	HwPOL_VIDEO								Hw10									//
#define	HwPOL_SPDTX								Hw9										//
#define	HwPOL_SCORE								Hw8										//
#define	HwPOL_TC1								Hw7										//
#define	HwPOL_TC0								Hw6										//
#define	HwPOL_GPSB								Hw5										//
#define	HwPOL_RTC								Hw4										//
#define	HwPOL_EI3								Hw3										//
#define	HwPOL_EI2								Hw2										//
#define	HwPOL_EI1								Hw1										//
#define	HwPOL_EI0								Hw0										//
                                    			
#define	HwIRQ									*(volatile unsigned long *)0xF3001020	// R, IRQ Raw Status Register
#define	HwIRQ_ECC								Hw31									//
#define	HwIRQ_ADC								Hw30									//
#define	HwIRQ_LCD								Hw29									//
#define	HwIRQ_CAM								Hw28									//
#define	HwIRQ_SD								Hw27									//
#define	HwIRQ_NFC								Hw26									//
#define	HwIRQ_MS								Hw25									//
#define	HwIRQ_HDD								Hw24									//
#define	HwIRQ_DMA								Hw23									//
#define	HwIRQ_UH								Hw22									//
#define	HwIRQ_UD								Hw21									//
#define	HwIRQ_UDMA								Hw20									//
#define	HwIRQ_UT1								Hw19									//
#define	HwIRQ_UT0								Hw18									//
#define	HwIRQ_HPI								Hw17									//
#define	HwIRQ_CDRX								Hw16									//
#define	HwIRQ_DAITX								Hw15									//
#define	HwIRQ_DAIRX								Hw14									//
#define	HwIRQ_I2C								Hw13									//
#define	HwIRQ_SC								Hw12									//
#define	HwIRQ_GSIO								Hw11									//
#define	HwIRQ_VIDEO								Hw10									//
#define	HwIRQ_SPDTX								Hw9										//
#define	HwIRQ_SCORE								Hw8										//
#define	HwIRQ_TC1								Hw7										//
#define	HwIRQ_TC0								Hw6										//
#define	HwIRQ_GPSB								Hw5										//
#define	HwIRQ_RTC								Hw4										//
#define	HwIRQ_EI3								Hw3										//
#define	HwIRQ_EI2								Hw2										//
#define	HwIRQ_EI1								Hw1										//
#define	HwIRQ_EI0								Hw0										//
                                    			
#define	HwFIQ									*(volatile unsigned long *)0xF3001024	// R, FIQ Status Register
#define	HwFIQ_ECC								Hw31									//
#define	HwFIQ_ADC								Hw30									//
#define	HwFIQ_LCD								Hw29									//
#define	HwFIQ_CAM								Hw28									//
#define	HwFIQ_SD								Hw27									//
#define	HwFIQ_NFC								Hw26									//
#define	HwFIQ_MS								Hw25									//
#define	HwFIQ_HDD								Hw24									//
#define	HwFIQ_DMA								Hw23									//
#define	HwFIQ_UH								Hw22									//
#define	HwFIQ_UD								Hw21									//
#define	HwFIQ_UDMA								Hw20									//
#define	HwFIQ_UT1								Hw19									//
#define	HwFIQ_UT0								Hw18									//
#define	HwFIQ_HPI								Hw17									//
#define	HwFIQ_CDRX								Hw16									//
#define	HwFIQ_DAITX								Hw15									//
#define	HwFIQ_DAIRX								Hw14									//
#define	HwFIQ_I2C								Hw13									//
#define	HwFIQ_SC								Hw12									//
#define	HwFIQ_GSIO								Hw11									//
#define	HwFIQ_VIDEO								Hw10									//
#define	HwFIQ_SPDTX								Hw9										//
#define	HwFIQ_SCORE								Hw8										//
#define	HwFIQ_TC1								Hw7										//
#define	HwFIQ_TC0								Hw6										//
#define	HwFIQ_GPSB								Hw5										//
#define	HwFIQ_RTC								Hw4										//
#define	HwFIQ_EI3								Hw3										//
#define	HwFIQ_EI2								Hw2										//
#define	HwFIQ_EI1								Hw1										//
#define	HwFIQ_EI0								Hw0										//
                                    			
#define	HwMIRQ									*(volatile unsigned long *)0xF3001028	// R, Masked IRQ Status Register
#define	HwMIRQ_ECC								Hw31									//
#define	HwMIRQ_ADC								Hw30									//
#define	HwMIRQ_LCD								Hw29									//
#define	HwMIRQ_CAM								Hw28									//
#define	HwMIRQ_SD								Hw27									//
#define	HwMIRQ_NFC								Hw26									//
#define	HwMIRQ_MS								Hw25									//
#define	HwMIRQ_HDD								Hw24									//
#define	HwMIRQ_DMA								Hw23									//
#define	HwMIRQ_UH								Hw22									//
#define	HwMIRQ_UD								Hw21									//
#define	HwMIRQ_UDMA								Hw20									//
#define	HwMIRQ_UT1								Hw19									//
#define	HwMIRQ_UT0								Hw18									//
#define	HwMIRQ_HPI								Hw17									//
#define	HwMIRQ_CDRX								Hw16									//
#define	HwMIRQ_DAITX							Hw15									//
#define	HwMIRQ_DAIRX							Hw14									//
#define	HwMIRQ_I2C								Hw13									//
#define	HwMIRQ_SC								Hw12									//
#define	HwMIRQ_GSIO								Hw11									//
#define	HwMIRQ_VIDEO							Hw10									//
#define	HwMIRQ_SPDTX							Hw9										//
#define	HwMIRQ_SCORE							Hw8										//
#define	HwMIRQ_TC1								Hw7										//
#define	HwMIRQ_TC0								Hw6										//
#define	HwMIRQ_GPSB								Hw5										//
#define	HwMIRQ_RTC								Hw4										//
#define	HwMIRQ_EI3								Hw3										//
#define	HwMIRQ_EI2								Hw2										//
#define	HwMIRQ_EI1								Hw1										//
#define	HwMIRQ_EI0								Hw0										//
                                    			
#define	HwMFIQ									*(volatile unsigned long *)0xF300102C	// R, Masked FIQ Status Register
#define	HwMFIQ_ECC								Hw31									//
#define	HwMFIQ_ADC								Hw30									//
#define	HwMFIQ_LCD								Hw29									//
#define	HwMFIQ_CAM								Hw28									//
#define	HwMFIQ_SD								Hw27									//
#define	HwMFIQ_NFC								Hw26									//
#define	HwMFIQ_MS								Hw25									//
#define	HwMFIQ_HDD								Hw24									//
#define	HwMFIQ_DMA								Hw23									//
#define	HwMFIQ_UH								Hw22									//
#define	HwMFIQ_UD								Hw21									//
#define	HwMFIQ_UDMA								Hw20									//
#define	HwMFIQ_UT1								Hw19									//
#define	HwMFIQ_UT0								Hw18									//
#define	HwMFIQ_HPI								Hw17									//
#define	HwMFIQ_CDRX								Hw16									//
#define	HwMFIQ_DAITX							Hw15									//
#define	HwMFIQ_DAIRX							Hw14									//
#define	HwMFIQ_I2C								Hw13									//
#define	HwMFIQ_SC								Hw12									//
#define	HwMFIQ_GSIO								Hw11									//
#define	HwMFIQ_VIDEO							Hw10									//
#define	HwMFIQ_SPDTX							Hw9										//
#define	HwMFIQ_SCORE							Hw8										//
#define	HwMFIQ_TC1								Hw7										//
#define	HwMFIQ_TC0								Hw6										//
#define	HwMFIQ_GPSB								Hw5										//
#define	HwMFIQ_RTC								Hw4										//
#define	HwMFIQ_EI3								Hw3										//
#define	HwMFIQ_EI2								Hw2										//
#define	HwMFIQ_EI1								Hw1										//
#define	HwMFIQ_EI0								Hw0										//
                                    			
#define	HwMODE									*(volatile unsigned long *)0xF3001030	// R/W, Trigger Mode Register (Level or Edge)
#define	HwMODE_ECC								Hw31									//
#define	HwMODE_ADC								Hw30									//
#define	HwMODE_LCD								Hw29									//
#define	HwMODE_CAM								Hw28									//
#define	HwMODE_SD								Hw27									//
#define	HwMODE_NFC								Hw26									//
#define	HwMODE_MS								Hw25									//
#define	HwMODE_HDD								Hw24									//
#define	HwMODE_DMA								Hw23									//
#define	HwMODE_UH								Hw22									//
#define	HwMODE_UD								Hw21									//
#define	HwMODE_UDMA								Hw20									//
#define	HwMODE_UT1								Hw19									//
#define	HwMODE_UT0								Hw18									//
#define	HwMODE_HPI								Hw17									//
#define	HwMODE_CDRX								Hw16									//
#define	HwMODE_DAITX							Hw15									//
#define	HwMODE_DAIRX							Hw14									//
#define	HwMODE_I2C								Hw13									//
#define	HwMODE_SC								Hw12									//
#define	HwMODE_GSIO								Hw11									//
#define	HwMODE_VIDEO							Hw10									//
#define	HwMODE_SPDTX							Hw9										//
#define	HwMODE_SCORE							Hw8										//
#define	HwMODE_TC1								Hw7										//
#define	HwMODE_TC0								Hw6										//
#define	HwMODE_GPSB								Hw5										//
#define	HwMODE_RTC								Hw4										//
#define	HwMODE_EI3								Hw3										//
#define	HwMODE_EI2								Hw2										//
#define	HwMODE_EI1								Hw1										//
#define	HwMODE_EI0								Hw0										//
                                    			
#define	HwSYNC									*(volatile unsigned long *)0xF3001034	// R/W, Synchronization Enable Register
#define	HwSYNC_ECC								Hw31									//
#define	HwSYNC_ADC								Hw30									//
#define	HwSYNC_LCD								Hw29									//
#define	HwSYNC_CAM								Hw28									//
#define	HwSYNC_SD								Hw27									//
#define	HwSYNC_NFC								Hw26									//
#define	HwSYNC_MS								Hw25									//
#define	HwSYNC_HDD								Hw24									//
#define	HwSYNC_DMA								Hw23									//
#define	HwSYNC_UH								Hw22									//
#define	HwSYNC_UD								Hw21									//
#define	HwSYNC_UDMA								Hw20									//
#define	HwSYNC_UT1								Hw19									//
#define	HwSYNC_UT0								Hw18									//
#define	HwSYNC_HPI								Hw17									//
#define	HwSYNC_CDRX								Hw16									//
#define	HwSYNC_DAITX							Hw15									//
#define	HwSYNC_DAIRX							Hw14									//
#define	HwSYNC_I2C								Hw13									//
#define	HwSYNC_SC								Hw12									//
#define	HwSYNC_GSIO								Hw11									//
#define	HwSYNC_VIDEO							Hw10									//
#define	HwSYNC_SPDTX							Hw9										//
#define	HwSYNC_SCORE							Hw8										//
#define	HwSYNC_TC1								Hw7										//
#define	HwSYNC_TC0								Hw6										//
#define	HwSYNC_GPSB								Hw5										//
#define	HwSYNC_RTC								Hw4										//
#define	HwSYNC_EI3								Hw3										//
#define	HwSYNC_EI2								Hw2										//
#define	HwSYNC_EI1								Hw1										//
#define	HwSYNC_EI0								Hw0										//
                                    			
#define	HwWKEN									*(volatile unsigned long *)0xF3001038	// R/W, Wakeup Event Enable Register
#define	HwWKEN_ECC								Hw31									//
#define	HwWKEN_ADC								Hw30									//
#define	HwWKEN_LCD								Hw29									//
#define	HwWKEN_CAM								Hw28									//
#define	HwWKEN_SD								Hw27									//
#define	HwWKEN_NFC								Hw26									//
#define	HwWKEN_MS								Hw25									//
#define	HwWKEN_HDD								Hw24									//
#define	HwWKEN_DMA								Hw23									//
#define	HwWKEN_UH								Hw22									//
#define	HwWKEN_UD								Hw21									//
#define	HwWKEN_UDMA								Hw20									//
#define	HwWKEN_UT1								Hw19									//
#define	HwWKEN_UT0								Hw18									//
#define	HwWKEN_HPI								Hw17									//
#define	HwWKEN_CDRX								Hw16									//
#define	HwWKEN_DAITX							Hw15									//
#define	HwWKEN_DAIRX							Hw14									//
#define	HwWKEN_I2C								Hw13									//
#define	HwWKEN_SC								Hw12									//
#define	HwWKEN_GSIO								Hw11									//
#define	HwWKEN_VIDEO							Hw10									//
#define	HwWKEN_SPDTX							Hw9										//
#define	HwWKEN_SCORE							Hw8										//
#define	HwWKEN_TC1								Hw7										//
#define	HwWKEN_TC0								Hw6										//
#define	HwWKEN_GPSB								Hw5										//
#define	HwWKEN_RTC								Hw4										//
#define	HwWKEN_EI3								Hw3										//
#define	HwWKEN_EI2								Hw2										//
#define	HwWKEN_EI1								Hw1										//
#define	HwWKEN_EI0								Hw0										//
                                    			
#define	HwMODEA									*(volatile unsigned long *)0xF300103C	// R/W, Both Edge or Single Edge Register
#define	HwMODEA_ECC								Hw31									//
#define	HwMODEA_ADC								Hw30									//
#define	HwMODEA_LCD								Hw29									//
#define	HwMODEA_CAM								Hw28									//
#define	HwMODEA_SD								Hw27									//
#define	HwMODEA_NFC								Hw26									//
#define	HwMODEA_MS								Hw25									//
#define	HwMODEA_HDD								Hw24									//
#define	HwMODEA_DMA								Hw23									//
#define	HwMODEA_UH								Hw22									//
#define	HwMODEA_UD								Hw21									//
#define	HwMODEA_UDMA							Hw20									//
#define	HwMODEA_UT1								Hw19									//
#define	HwMODEA_UT0								Hw18									//
#define	HwMODEA_HPI								Hw17									//
#define	HwMODEA_CDRX							Hw16									//
#define	HwMODEA_DAITX							Hw15									//
#define	HwMODEA_DAIRX							Hw14									//
#define	HwMODEA_I2C								Hw13									//
#define	HwMODEA_SC								Hw12									//
#define	HwMODEA_GSIO							Hw11									//
#define	HwMODEA_VIDEO							Hw10									//
#define	HwMODEA_SPDTX							Hw9										//
#define	HwMODEA_SCORE							Hw8										//
#define	HwMODEA_TC1								Hw7										//
#define	HwMODEA_TC0								Hw6										//
#define	HwMODEA_GPSB							Hw5										//
#define	HwMODEA_RTC								Hw4										//
#define	HwMODEA_EI3								Hw3										//
#define	HwMODEA_EI2								Hw2										//
#define	HwMODEA_EI1								Hw1										//
#define	HwMODEA_EI0								Hw0										//
                                    			
#define	HwIRQMSK								*(volatile unsigned long *)0xF3001040	// R/W, IRQ Output Mask Register
#define	HwIRQMSK_ECC							Hw31									//
#define	HwIRQMSK_ADC							Hw30									//
#define	HwIRQMSK_LCD							Hw29									//
#define	HwIRQMSK_CAM							Hw28									//
#define	HwIRQMSK_SD								Hw27									//
#define	HwIRQMSK_NFC							Hw26									//
#define	HwIRQMSK_MS								Hw25									//
#define	HwIRQMSK_HDD							Hw24									//
#define	HwIRQMSK_DMA							Hw23									//
#define	HwIRQMSK_UH								Hw22									//
#define	HwIRQMSK_UD								Hw21									//
#define	HwIRQMSK_UDMA							Hw20									//
#define	HwIRQMSK_UT1							Hw19									//
#define	HwIRQMSK_UT0							Hw18									//
#define	HwIRQMSK_HPI							Hw17									//
#define	HwIRQMSK_CDRX							Hw16									//
#define	HwIRQMSK_DAITX							Hw15									//
#define	HwIRQMSK_DAIRX							Hw14									//
#define	HwIRQMSK_I2C							Hw13									//
#define	HwIRQMSK_SC								Hw12									//
#define	HwIRQMSK_GSIO							Hw11									//
#define	HwIRQMSK_VIDEO							Hw10									//
#define	HwIRQMSK_SPDTX							Hw9										//
#define	HwIRQMSK_SCORE							Hw8										//
#define	HwIRQMSK_TC1							Hw7										//
#define	HwIRQMSK_TC0							Hw6										//
#define	HwIRQMSK_GPSB							Hw5										//
#define	HwIRQMSK_RTC							Hw4										//
#define	HwIRQMSK_EI3							Hw3										//
#define	HwIRQMSK_EI2							Hw2										//
#define	HwIRQMSK_EI1							Hw1										//
#define	HwIRQMSK_EI0							Hw0										//
                                    			
#define	HwALLMSK								*(volatile unsigned long *)0xF3001044	// R/W, All IRQ Mask Register
#define	HwALLMSK_FIQ							Hw1										// FIQ mask register
#define	HwALLMSK_IRQ							Hw0										// IRQ mask register
                                    			
#define	HwVAIRQ									*(volatile unsigned long *)0xF3001080	// R, IRQ Vector Register
#define	HwVAIRQ_INV								Hw31									// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source
                                    			
#define	HwVAFIQ									*(volatile unsigned long *)0xF3001084	// R, FIQ Vector Register
#define	HwVAFIQ_INV								Hw31									// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source
                                    			
#define	HwVNIRQ									*(volatile unsigned long *)0xF3001088	// R, IRQ Vector Number Register
#define	HwVNIRQ_INV								Hw31									// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source
                                    			
#define	HwVNFIQ									*(volatile unsigned long *)0xF300108C	// R, FIQ Vcoter Number Register
#define	HwVNFIQ_INV								Hw31									// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source
                                    			
#define	HwVCTRL									*(volatile unsigned long *)0xF3001090	// R/W, Vector Control Register
#define	HwVCTRL_RCL_RD							Hw31									// The reading the VN or VA register clears the interrupt status
#define	HwVCTRL_FPOL_10							Hw30									// The INV field means valid for '1', invalid for '0'
#define	HwVCTRL_FFLG_VLD						Hw29									// Valid flag enable for FIQ vector registers
#define	HwVCTRL_IFLG_VLD						Hw28									// Valid flag enable for IRQ vector registers
#define	HwVCTRL_FHD_EN							Hw27									// Enable the holding vector for FIQ until cleared
#define	HwVCTRL_IHD_EN							Hw26									// Enable the holding vector for IRQ until cleared
                                    			
#define	HwPRI04									*(volatile unsigned long *)0xF30010A0	// R/W, Priorities for Interrupt 0~3
                                    			
#define	HwPRI08									*(volatile unsigned long *)0xF30010A4	// R/W, Priorities for Interrupt 4~7
                                    			
#define	HwPRI12									*(volatile unsigned long *)0xF30010A8	// R/W, Priorities for Interrupt 8~11
                                    			
#define	HwPRI16									*(volatile unsigned long *)0xF30010AC	// R/W, Priorities for Interrupt 12~15
                                    			
#define	HwPRI20									*(volatile unsigned long *)0xF30010B0	// R/W, Priorities for Interrupt 16~19
                                    			
#define	HwPRI24									*(volatile unsigned long *)0xF30010B4	// R/W, Priorities for Interrupt 20~23
                                    			
#define	HwPRI28									*(volatile unsigned long *)0xF30010B8	// R/W, Priorities for Interrupt 24~27
                                    			
#define	HwPRI32									*(volatile unsigned long *)0xF30010BC	// R/W, Priorities for Interrupt 28~31

/************************************************************************
*	RTC Register Define							(Base Addr = 0xF3002000)
************************************************************************/
#define	HwRTCCON								*(volatile unsigned long *)0xF3002000	// R/W, RTC Control Register
#define	HwRTCCON_HALT							Hw0										//
#define	HwRTCCON_RTCEN							Hw1										// RTC Register write enabled
#define	HwRTCCON_CLKSEL_NORM					HwZERO									// Counting clock is 1Hz.
#define	HwRTCCON_CLKSEL_FAST					Hw2										// Counting clock is 32.768kHz
#define	HwRTCCON_CNTSEL_NORM					HwZERO									// BCD counter acts normally
#define	HwRTCCON_CNTSEL_SEP					Hw3										// BCD counter acts separately.
#define	HwRTCCON_CLKRST_ON					Hw4										// BCD counter is reseted.
#define	HwRTCCON_OSCEN_TEN					Hw5										// Oscillator & Divider circuit test enabled.
#define	HwRTCCON_AIOUTEN_EN					Hw6										// Alarm Interrupt Output Enable
#define	HwRTCCON_WUOUTEN_EN					Hw7										// Wakeup Output Enable
                                    			
#define	HwRTCRST								*(volatile unsigned long *)0xF3002004	// R/W, RTC Round Reset Register
#define	HwRTCRST_SECCR_30SEC					(Hw1+Hw0)								// Round-up by 30sec boundary
#define	HwRTCRST_SECCR_40SEC					Hw2										// Round-up by 40sec boundary
#define	HwRTCRST_SECCR_50SEC					(Hw2+Hw0)								// Round-up by 50sec boundary
#define	HwRTCRST_SRSTEN_EN						Hw3										// Round-up enabled

#define	HwINTCON								*(volatile unsigned long *)0xF3002004	// R/W, RTC Interrupt Control Register
#define	HwINTCON_INTWREN						Hw0										// Interrupt Block Write Enable
#define	HwINTCON_STATUS						Hw1										// User-Defined Status Register
                                    			
#define	HwRTCALM								*(volatile unsigned long *)0xF3002008	// R/W, RTC Alarm Control Register
#define	HwRTCALM_SECEN_EN						Hw0										// Second Alarm interrupt enabled
#define	HwRTCALM_MINEN_EN						Hw1										// Minute Alarm interrupt enabled
#define	HwRTCALM_HOUREN_EN					Hw2										// Hour Alarm interrupt enabled
#define	HwRTCALM_DATEEN_EN						Hw3										// Date Alarm interrupt enabled
#define	HwRTCALM_DAYEN_EN						Hw4										// Day of Week Alarm interrupt enabled
//#define	HwRTCALM_MONEN_EN						Hw5										// Month Alarm interrupt enabled
//#define	HwRTCALM_YEAREN_EN						Hw6										// Year Alarm interrupt enabled
#define	HwRTCALM_ALMEN_EN						Hw5										// Alarm interrupt enabled (global enable)
#define	HwRTCALM_ALLEN							0x3F									//
                                    			
#define	HwALMSEC								*(volatile unsigned long *)0xF300200C	// R/W, Alarm Second Data Register
                                    			
#define	HwALMMIN								*(volatile unsigned long *)0xF3002010	// R/W, Alarm Minute Data Register
                                    			
#define	HwALMHOUR								*(volatile unsigned long *)0xF3002014	// R/W, Alarm Hour Data Register
                                    			
#define	HwALMDATE								*(volatile unsigned long *)0xF3002018	// R/W, Alarm Date Data Register
                                    			
#define	HwALMDAY								*(volatile unsigned long *)0xF300201C	// R/W, Alarm Day of Week Data Register
enum {	HwALMDAY_SUN	= 0,            	
		HwALMDAY_MON,                   	
		HwALMDAY_TUE,                   	
		HwALMDAY_WED,                   	
		HwALMDAY_THR,                   	
		HwALMDAY_FRI,                   	
		HwALMDAY_SAT                    	
};                                      	
                                        	
#define	HwALMMON								*(volatile unsigned long *)0xF3002020	// R/W, Alarm Month Data Register
                                    			
#define	HwALMYEAR								*(volatile unsigned long *)0xF3002024	// R/W, Alarm Year Data Register
                                    			
#define	HwBCDSEC								*(volatile unsigned long *)0xF3002028	// R/W, BCD Second Register
                                    			
#define	HwBCDMIN								*(volatile unsigned long *)0xF300202C	// R/W, BCD Minute Register
                                    			
#define	HwBCDHOUR								*(volatile unsigned long *)0xF3002030	// R/W, BCD Hour Register
                                    			
#define	HwBCDDATE								*(volatile unsigned long *)0xF3002034	// R/W, BCD Date Register
                                    			
#define	HwBCDDAY								*(volatile unsigned long *)0xF3002038	// R/W, BCD Day of Week Register
enum {	HwBCDDAY_SUN	= 0,            	
		HwBCDDAY_MON,                   	
		HwBCDDAY_TUE,                   	
		HwBCDDAY_WED,                   	
		HwBCDDAY_THR,                   	
		HwBCDDAY_FRI,                   	
		HwBCDDAY_SAT                    	
};                                      	
                                        	
#define	HwBCDMON								*(volatile unsigned long *)0xF300203C	// R/W, BCD Month Register
                                    			
#define	HwBCDYEAR								*(volatile unsigned long *)0xF3002040	// R/W, BCD Year Register
                                    			
#define	HwRTCIM									*(volatile unsigned long *)0xF3002044	// R/W, RTC Interrupt Mode Register
#define	HwRTCIM_ALMINT_EDGE_EN					Hw0										//
#define	HwRTCIM_ALMINT_LEVEL_EN					(Hw1+Hw0)								//
#define	HwRTCIM_ALMINT_DIS						HwZERO									//
#define	HwRTCIM_PEINT_EN						Hw2										//
#define	HwRTCIM_PEINT_DIS						HwZERO									//
#define	HwRTCIM_PEINT_1P0SEC					(0 << 3)								// no pending interrupt generated
#define	HwRTCIM_PEINT_1P256SEC					(1 << 3)								// 1/256 sec
#define	HwRTCIM_PEINT_1P64SEC					(2 << 3)								// 1/64 sec
#define	HwRTCIM_PEINT_1P16SEC					(3 << 3)								// 1/16 sec
#define	HwRTCIM_PEINT_1P4SEC					(4 << 3)								// 1/4 sec
#define	HwRTCIM_PEINT_1P2SEC					(5 << 3)								// 1/2 sec
#define	HwRTCIM_PEINT_1SEC						(6 << 3)								// 1 sec
                                    			
#define	HwRTCPEND								*(volatile unsigned long *)0xF3002048	// R/W, RTC Interrupt Pending Register
#define	HwRTCPEND_PENDING						Hw0										//
                                    			
#define	HwRTCSTR								*(volatile unsigned long *)0xF300204C	// R/W, RTC Interrupt Status Register

/***********************************************************************
*	Timer/Counter Register Define				(Base Addr = 0xF3003000)
************************************************************************/
#define	HwTCFG0									*(volatile unsigned long *)0xF3003000	// R/W, Timer Configuration Register
#define	HwTCFG0_STOP							Hw9										// If TCNT0 is equal to the TREF0, the TCNT0 counter stop to increment
#define	HwTCFG0_CC_ZERO							Hw8										// TCNT0 is cleared to zero
#define	HwTCFG0_CC_NOT							~Hw8									// TCNT0 is not cleared
#define	HwTCFG0_POL_F							Hw7										// TCNT0 is incremented at falling edge of the selected counting clock
#define	HwTCFG0_POL_R							~Hw7									// TCNT0 is incremented at rising edge of the selected counting clock
#define	HwTCFG0_IEN_EN							Hw3										// Enable Timer/Counter interrupt
#define	HwTCFG0_IEN_DIS							~Hw3									// Disable Timer/Counter interrupt
#define	HwTCFG0_PWM_EN							Hw2										// Enable PWM mode
#define	HwTCFG0_PWM_DIS							~Hw2									// Disable PWM mode
#define	HwTCFG0_CON_ON							Hw1										// The TCNT0 continues counting from the TREF0
#define	HwTCFG0_CON_OFF							~Hw1									// When the TCNT0 is reached to TREF0, TCNT0 restarts counting from 0 at the next pulse of selected clock source
#define	HwTCFG0_EN_ON							Hw0										// Timer counter is enabled
#define	HwTCFG0_EN_OFF							~Hw0									// Timer counter is disabled
                                    			
#define	HwTCNT0									*(volatile unsigned long *)0xF3003004	// R/W, Timer Counter Register
                                    			
#define	HwTREF0  								*(volatile unsigned long *)0xF3003008	// R/W, Timer Reference Register
                                    			
#define	HwTMREF0 								*(volatile unsigned long *)0xF300300C	// R/W, Timer Middle reference Register
                                    			
#define	HwTCFG1									*(volatile unsigned long *)0xF3003010	// R/W, Timer Configuration Register
#define	HwTCFG1_STOP							Hw9										// If TCNT1 is equal to the TREF1, the TCNT1 counter stop to increment
#define	HwTCFG1_CC_ZERO							Hw8										// TCNT1 is cleared to zero
#define	HwTCFG1_CC_NOT							~Hw8									// TCNT1 is not cleared
#define	HwTCFG1_POL_F							Hw7										// TCNT1 is incremented at falling edge of the selected counting clock
#define	HwTCFG1_POL_R							~Hw7									// TCNT1 is incremented at rising edge of the selected counting clock
#define	HwTCFG1_IEN_EN							Hw3										// Enable Timer/Counter interrupt
#define	HwTCFG1_IEN_DIS							~Hw3									// Disable Timer/Counter interrupt
#define	HwTCFG1_PWM_EN							Hw2										// Enable PWM mode
#define	HwTCFG1_PWM_DIS							~Hw2									// Disable PWM mode
#define	HwTCFG1_CON_ON							Hw1										// The TCNT1 continues counting from the TREF1
#define	HwTCFG1_CON_OFF							~Hw1									// When the TCNT1 is reached to TREF1, TCNT1 restarts counting from 0 at the next pulse of selected clock source
#define	HwTCFG1_EN_ON							Hw0										// Timer counter is enabled
#define	HwTCFG1_EN_OFF							~Hw0									// Timer counter is disabled
                                    			
#define	HwTCNT1									*(volatile unsigned long *)0xF3003014	// R/W, Timer Counter Register
                                    			
#define	HwTREF1									*(volatile unsigned long *)0xF3003018	// R/W, Timer Reference Register
                                    			
#define	HwTMREF1								*(volatile unsigned long *)0xF300301C	// R/W, Timer Middle reference Register
                                    			
#define	HwTCFG2									*(volatile unsigned long *)0xF3003020	// R/W, Timer Configuration Register
#define	HwTCFG2_STOP							Hw9										// If TCNT2 is equal to the TREF2, the TCNT2 counter stop to increment
#define	HwTCFG2_CC_ZERO							Hw8										// TCNT2 is cleared to zero
#define	HwTCFG2_CC_NOT							~Hw8									// TCNT2 is not cleared
#define	HwTCFG2_POL_F							Hw7										// TCNT2 is incremented at falling edge of the selected counting clock
#define	HwTCFG2_POL_R							~Hw7									// TCNT2 is incremented at rising edge of the selected counting clock
#define	HwTCFG2_IEN_EN							Hw3										// Enable Timer/Counter interrupt
#define	HwTCFG2_IEN_DIS							~Hw3									// Disable Timer/Counter interrupt
#define	HwTCFG2_PWM_EN							Hw2										// Enable PWM mode
#define	HwTCFG2_PWM_DIS							~Hw2									// Disable PWM mode
#define	HwTCFG2_CON_ON							Hw1										// The TCNT2 continues counting from the TREF2
#define	HwTCFG2_CON_OFF							~Hw1									// When the TCNT2 is reached to TREF2, TCNT2 restarts counting from 0 at the next pulse of selected clock source
#define	HwTCFG2_EN_ON							Hw0										// Timer counter is enabled
#define	HwTCFG2_EN_OFF							~Hw0									// Timer counter is disabled
                                    			
#define	HwTCNT2									*(volatile unsigned long *)0xF3003024	// R/W, Timer Counter Register
                                    			
#define	HwTREF2									*(volatile unsigned long *)0xF3003028	// R/W, Timer Reference Register
                                    			
#define	HwTMREF2								*(volatile unsigned long *)0xF300302C	// R/W, Timer Middle reference Register
                                    			
#define	HwTCFG3									*(volatile unsigned long *)0xF3003030	// R/W, Timer Configuration Register
#define	HwTCFG3_STOP							Hw9										// If TCNT3 is equal to the TREF3, the TCNT3 counter stop to increment
#define	HwTCFG3_CC_ZERO							Hw8										// TCNT3 is cleared to zero
#define	HwTCFG3_CC_NOT							~Hw8									// TCNT3 is not cleared
#define	HwTCFG3_POL_F							Hw7										// TCNT3 is incremented at falling edge of the selected counting clock
#define	HwTCFG3_POL_R							~Hw7									// TCNT3 is incremented at rising edge of the selected counting clock
#define	HwTCFG3_IEN_EN							Hw3										// Enable Timer/Counter interrupt
#define	HwTCFG3_IEN_DIS							~Hw3									// Disable Timer/Counter interrupt
#define	HwTCFG3_PWM_EN							Hw2										// Enable PWM mode
#define	HwTCFG3_PWM_DIS							~Hw2									// Disable PWM mode
#define	HwTCFG3_CON_ON							Hw1										// The TCNT3 continues counting from the TREF3
#define	HwTCFG3_CON_OFF							~Hw1									// When the TCNT3 is reached to TREF3, TCNT3 restarts counting from 0 at the next pulse of selected clock source
#define	HwTCFG3_EN_ON							Hw0										// Timer counter is enabled
#define	HwTCFG3_EN_OFF							~Hw0									// Timer counter is disabled
                                    			
#define	HwTCNT3									*(volatile unsigned long *)0xF3003034	// R/W, Timer Counter Register
                                    			
#define	HwTREF3									*(volatile unsigned long *)0xF3003038	// R/W, Timer Reference Register
                                    			
#define	HwTMREF3								*(volatile unsigned long *)0xF300303C 	// R/W, Timer Middle reference Register
                                    			
#define	HwTCFG4									*(volatile unsigned long *)0xF3003040	// R/W, Timer Configuration Register
#define	HwTCFG4_STOP							Hw9										// If TCNT4 is equal to the TREF4, the TCNT4 counter stop to increment
#define	HwTCFG4_CC_ZERO							Hw8										// TCNT4 is cleared to zero
#define	HwTCFG4_CC_NOT							~Hw8									// TCNT4 is not cleared
#define	HwTCFG4_POL_F							Hw7										// TCNT4 is incremented at falling edge of the selected counting clock
#define	HwTCFG4_POL_R							~Hw7									// TCNT4 is incremented at rising edge of the selected counting clock
#define	HwTCFG4_IEN_EN							Hw3										// Enable Timer/Counter interrupt
#define	HwTCFG4_IEN_DIS							~Hw3									// Disable Timer/Counter interrupt
#define	HwTCFG4_PWM_EN							Hw2										// Enable PWM mode
#define	HwTCFG4_PWM_DIS							~Hw2									// Disable PWM mode
#define	HwTCFG4_CON_ON							Hw1										// The TCNT4 continues counting from the TREF4
#define	HwTCFG4_CON_OFF							~Hw1									// When the TCNT4 is reached to TREF4, TCNT4 restarts counting from 0 at the next pulse of selected clock source
#define	HwTCFG4_EN_ON							Hw0										// Timer counter is enabled
#define	HwTCFG4_EN_OFF							~Hw0									// Timer counter is disabled
                                    			
#define	HwTCNT4									*(volatile unsigned long *)0xF3003044	// R/W, Timer Counter Register
                                    			
#define	HwTREF4									*(volatile unsigned long *)0xF3003048	// R/W, Timer Reference Register
                                    			
#define	HwTCFG5									*(volatile unsigned long *)0xF3003050	// R/W, Timer Configuration Register
#define	HwTCFG5_STOP							Hw9										// If TCNT5 is equal to the TREF5, the TCNT5 counter stop to increment
#define	HwTCFG5_CC_ZERO							Hw8										// TCNT5 is cleared to zero
#define	HwTCFG5_CC_NOT							~Hw8									// TCNT5 is not cleared
#define	HwTCFG5_POL_F							Hw7										// TCNT5 is incremented at falling edge of the selected counting clock
#define	HwTCFG5_POL_R							~Hw7									// TCNT5 is incremented at rising edge of the selected counting clock
#define	HwTCFG5_IEN_EN							Hw3										// Enable Timer/Counter interrupt
#define	HwTCFG5_IEN_DIS							~Hw3									// Disable Timer/Counter interrupt
#define	HwTCFG5_PWM_EN							Hw2										// Enable PWM mode
#define	HwTCFG5_PWM_DIS							~Hw2									// Disable PWM mode
#define	HwTCFG5_CON_ON							Hw1										// The TCNT5 continues counting from the TREF5
#define	HwTCFG5_CON_OFF							~Hw1									// When the TCNT5 is reached to TREF5, TCNT5 restarts counting from 0 at the next pulse of selected clock source
#define	HwTCFG5_EN_ON							Hw0										// Timer counter is enabled
#define	HwTCFG5_EN_OFF							~Hw0									// Timer counter is disabled
                                    			
#define	HwTCNT5									*(volatile unsigned long *)0xF3003054	// R/W, Timer Counter Register
                                    			
#define	HwTREF5									*(volatile unsigned long *)0xF3003058	// R/W, Timer Reference Register
                                        	
typedef	volatile struct {               	
	unsigned	TCFG;                   	
#define	HwTCFG_CC_ZERO							Hw8										// TCNT is cleared to zero
#define	HwTCFG_POL_F							Hw7										// TCNT is incremented at falling edge of the selected counting clock
#define	HwTCFG_TCK_DIV2							(0 * Hw4)								// Counter clock is come from TCLK divided by 2.
#define	HwTCFG_TCK_DIV4							(1 * Hw4)								// Counter clock is come from TCLK divided by 4.
#define	HwTCFG_TCK_DIV8							(2 * Hw4)								// Counter clock is come from TCLK divided by 8.
#define	HwTCFG_TCK_DIV16						(3 * Hw4)								// Counter clock is come from TCLK divided by 16.
#define	HwTCFG_TCK_DIV32						(4 * Hw4)								// Counter clock is come from TCLK divided by 32.
#define	HwTCFG_TCK_DIV1K						(5 * Hw4)								// Counter clock is come from TCLK divided by 1024.
#define	HwTCFG_TCK_DIV4K						(6 * Hw4)								// Counter clock is come from TCLK divided by 4096.
#define	HwTCFG_TCK_EXTCLK						(7 * Hw4)								// Counter clock is come from external clock.
#define	HwTCFG_IEN_EN							Hw3										// Enable Timer/Counter interrupt
#define	HwTCFG_PWM_EN							Hw2										// Enable PWM mode
#define	HwTCFG_CON_ON							Hw1										// The TCNT3 continues counting without return to zero.
#define	HwTCFG_EN_ON							Hw0										// Timer counter is enabled
	unsigned	TCNT;                   	
	unsigned	TREF;                   	
	unsigned	TMREF;                  	
} sHwTMR;                               	
                                        	
#define	HwTIREQ									*(volatile unsigned long *)0xF3003060	// R/W, Timer Interrupt Request Register
#define	HwTIREQ_TWF								Hw14									// Watchdog Timer Flag
#define	HwTIREQ_TF5								Hw13									// Timer5 Flag
#define	HwTIREQ_TF4								Hw12									// Timer4 Flag
#define	HwTIREQ_TF3								Hw11									// Timer3 Flag
#define	HwTIREQ_TF2								Hw10									// Timer2 Flag
#define	HwTIREQ_TF1								Hw9										// Timer1 Flag
#define	HwTIREQ_TF0								Hw8										// Timer0 Flag
#define	HwTIREQ_TWI								Hw6										// Watchdog Timer Interrupt Request Flag
#define	HwTIREQ_TI5								Hw5										// Timer5 Interrupt Request Flag
#define	HwTIREQ_TI4								Hw4										// Timer4 Interrupt Request Flag
#define	HwTIREQ_TI3								Hw3										// Timer3 Interrupt Request Flag
#define	HwTIREQ_TI2								Hw2										// Timer2 Interrupt Request Flag
#define	HwTIREQ_TI1								Hw1										// Timer1 Interrupt Request Flag
#define	HwTIREQ_TI0								Hw0										// Timer0 Interrupt Request Flag
                                    			
#define	HwTWDCFG								*(volatile unsigned long *)0xF3003070	// R/W, Watchdog Timer Configuration Register
#define	HwTWDCFGT_IEN_ON						Hw3										// Watchdog timer interrupt is enabled
#define	HwTWDCFGT_IEN_OFF						~Hw3									// Watchdog timer interrupt is disabled
#define	HwTWDCFG_ISEL_NOGEN						Hw1										// Watchdog timer does not generate reset signal although it reaches to the reference value, and it continue counting from 0.
#define	HwTWDCFG_ISEL_GEN						~Hw1									// Watchdog timer generates the reset signal when it reaches to the reference value, the reset signal is applied to every component in the chip.
#define	HwTWDCFG_EN_ON							Hw0										// Watchdog timer is enabled
#define	HwTWDCFG_EN_OFF							~Hw0									// Watchdog timer is disabled
                                    			
#define	HwTWDCLR								*(volatile unsigned long *)0xF3003074	// W, Watchdog Timer Clear Register
                                    			
#define	HwTC32EN								*(volatile unsigned long *)0xF3003080	// R/W, 32bit Counter enable / Pre-scale value
#define	HwTC32EN_LDM1_ON						Hw29									// Reload counter when the counter value matched with CMP1
#define	HwTC32EN_LDM1_OFF						~Hw29									// Reload counter when the counter value matched with CMP1
#define	HwTC32EN_LDM0_ON						Hw28									// Reload counter when the counter value matched with CMP0
#define	HwTC32EN_LDM0_OFF						~Hw28									// Reload counter when the counter value matched with CMP0
#define	HwTC32EN_STPMOD_ON						Hw26									// Stop Mode
#define	HwTC32EN_STPMOD_OFF						~Hw26									// Free running Mode
#define	HwTC32EN_LDZERO_ON						Hw25									// By default, counter starts form LOADVAL(HwTC32LDV)
#define	HwTC32EN_LDZERO_OFF						~Hw25									// By default, counter starts form LOADVAL(HwTC32LDV)
#define	HwTC32EN_ENABLE_ON						Hw24									// Counter enable
#define	HwTC32EN_ENABLE_OFF						~Hw24									// Counter disable
                                    			
#define	HwTC32LDV								*(volatile unsigned long *)0xF3003084	// R/W, 32bit Counter load value Register
                                    			
#define	HwTC32CMP0								*(volatile unsigned long *)0xF3003088	// R/W, 32bit Counter match value 0 Register
                                    			
#define	HwTC32CMP1								*(volatile unsigned long *)0xF300308C	// R/W, 32bit Counter match value 1 Register
                                    			
#define	HwTC32PCNT								*(volatile unsigned long *)0xF3003090	// R/W, 32bit Counter current value (pre-scale counter) Register
                                    			
#define	HwTC32MCNT								*(volatile unsigned long *)0xF3003094	// R/W, 32bit Counter current value (main counter) Register
                                    			
#define	HwTC32IRQ								*(volatile unsigned long *)0xF3003098	// R/W, 32bit Counter interrupt control Register
#define	HwTC32IRQ_IRQCLR_WRITE					Hw31									// Interrupt clear control
#define	HwTC32IRQ_IRQCLR_READ					~Hw31									// Interrupt clear control
#define	HwTC32IRQ_RSYNC_DIS						Hw30									// Synchronization control
#define	HwTC32IRQ_RSYNC_EN						~Hw30									// Synchronization control
#define	HwTC32IRQ_IRQEN4_EN						Hw20									// Enable interrupt at the rising edge of a counter bit selected by BITSEL
#define	HwTC32IRQ_IRQEN4_DIS					~Hw20									// Enable interrupt at the rising edge of a counter bit selected by BITSEL
#define	HwTC32IRQ_IRQEN3_EN						Hw19									// Enable interrupt at the end of prescale count
#define	HwTC32IRQ_IRQEN3_DIS					~Hw19									// Enable interrupt at the end of prescale count
#define	HwTC32IRQ_IRQEN2_EN						Hw18									// Enable interrupt at the end of count
#define	HwTC32IRQ_IRQEN2_DIS					~Hw18									// Enable interrupt at the end of count
#define	HwTC32IRQ_IRQEN1_EN						Hw17									// Enable interrupt when the counter value matched with CMP1
#define	HwTC32IRQ_IRQEN1_DIS					~Hw17									// Enable interrupt when the counter value matched with CMP1
#define	HwTC32IRQ_IRQEN0_EN						Hw16									// Enable interrupt when the counter value matched with CMP0
#define	HwTC32IRQ_IRQEN0_DIS					~Hw16									// Enable interrupt when the counter value matched with CMP0

/************************************************************************
*	ADC Controller Register Define				(Base Addr = 0xF3004000)
************************************************************************/
#define	HwADCCON								*(volatile unsigned long *)0xF3004000	// R/W, ADC Control
#define	HwADCCON_STB_ON							Hw4										// ADC goes Standby mode
#define	HwADCCON_STB_OFF						~Hw4									// ADC Start operating
#define	HwADCCON_ASEL_CH0						HwZERO									//
#define	HwADCCON_ASEL_CH1						Hw0										//
#define	HwADCCON_ASEL_CH2						Hw1										//
#define	HwADCCON_ASEL_CH3						(Hw1+Hw0)								//
#define	HwADCCON_ASEL_CH4						Hw2										//
#define	HwADCCON_ASEL_CH5						(Hw2+Hw0)								//
#define	HwADCCON_ASEL_CH6						(Hw2+Hw1)								//
#define	HwADCCON_ASEL_CH7						(Hw2+Hw1+Hw0)							//
                                    			
#define	HwADDATA								*(volatile unsigned long *)0xF3004004	// R, ADC Data
#define	HwADDATA_FLG							Hw0										//
                                    			
#define	HwADCCONA								*(volatile unsigned long *)0xF3004080	// R/W, ADC Control Register A
#define	HwADCCONA_STB_ON						Hw4										// ADC goes Standby mode
#define	HwADCCONA_STB_OFF						~Hw4									// ADC Start operating
#define	HwADCCONA_ASEL_CH0						HwZERO									//
#define	HwADCCONA_ASEL_CH1						Hw0										//
#define	HwADCCONA_ASEL_CH2						Hw1										//
#define	HwADCCONA_ASEL_CH3						(Hw1+Hw0)								//
#define	HwADCCONA_ASEL_CH4						Hw2										//
#define	HwADCCONA_ASEL_CH5						(Hw2+Hw0)								//
#define	HwADCCONA_ASEL_CH6						(Hw2+Hw1)								//
#define	HwADCCONA_ASEL_CH7						(Hw2+Hw1+Hw0)							//
                                    			
#define	HwADCSTATUS								*(volatile unsigned long *)0xF3004084	// R/W, ADC Status Register
                                    			
#define	HwADCCFG								*(volatile unsigned long *)0xF3004088	// R/W, Configuration Register
#define	HwADCCFG_NEOC							~Hw7									//
#define	HwADCCFG_IRQE_ON						Hw3										//
#define	HwADCCFG_IRQE_OFF						~Hw3									//
#define	HwADCCFG_R8_8BIT						Hw2										//
#define	HwADCCFG_R8_10BIT						~Hw2									//
#define	HwADCCFG_APD_ON							Hw1										//
#define	HwADCCFG_APD_OFF						~Hw1									//
#define	HwADCCFG_SM_EN							Hw0										//
#define	HwADCCFG_SM_DIS							~Hw0									//

/***********************************************************************
*	System Controller Register Define			(Base Addr = 0xF3005000)
************************************************************************/
#define	HwREMAP									*(volatile unsigned long *)0xF3005000	// R/W, Remap Configuration Register
#define	HwREMAP_JTAG_MAIN						HwZERO									// The JTAG is connected to only main processor
#define	HwREMAP_JTAG_SUB						Hw25									// The JTAG is connected to only sub processor
#define	HwREMAP_JTAG_BOTH						(Hw25+Hw24)								// The JTAG is connected to both main processor and sub processor. In this case, the JTAG is connected to sub processor through main processor with chained structure
#define	HwREMAP_CFGBM							(Hw20-Hw16)								//
#define	HwREMAP_CFGBW							(Hw9+Hw8)								//
#define	HwREMAP_CBCK							Hw4										//
#define	HwREMAP_REMAP10							HwZERO									// Remap 0x1... to 0x0...
#define	HwREMAP_REMAP20							Hw0										// Remap 0x2... to 0x0...
#define	HwREMAP_REMAP30							Hw1										// Remap 0x3... to 0x0...
#define	HwREMAP_REMAP70							(Hw1+Hw0)								// Remap 0x7... to 0x0...
#define	HwREMAP_NOTREMAP						Hw2										// Do not remap
#define	HwREMAP_REMAPE0							(Hw2+Hw1+Hw0)							// Remap 0xE... to 0x0...
                                    			
#define	HwVCFG0									*(volatile unsigned long *)0xF3005004	// R/W, Video Core Configuration Register 0
                                    			
#define	HwECFG0									*(volatile unsigned long *)0xF300500C	// R/W, Exceptional Configuration Register 0
#define	HwECFG0_LCK1							Hw3										// LCD Clock Output Enable to GPA14
#define	HwECFG0_LCK0							Hw2										// LCD Clock Output Enable to HDDRQ
#define	HwECFG0_ME1								Hw1										// Bus Clock Dynamic Mask Enable for I/O Bus to Main Bus
#define	HwECFG0_ME0								Hw0										// Bus Clock Dynamic Mask Enable for Main Bus to I/O Bus
                                    			
#define HwMPCFG									*(volatile unsigned long *)0xF3005010	// R/W, Main Processor Configuration Register
#define	HwMPCFG_INI								Hw31									// ITCM boot enable register
                                    			
#define	HwMBCFG									*(volatile unsigned long *)0xF3005020	// R/W, Main Bus Configuration Register
#define	HwMBCFG_INCRB_IOBUS						Hw4										// I/O bus, all the peripherals
#define	HwMBCFG_INCRB_VSRAM						Hw3										// Video SRAM
#define	HwMBCFG_INCRB_SDRAM						Hw2										// SDRAM Channel 1 (0x3...)
#define	HwMBCFG_INCRB_ESMEM						Hw1										// External Static Memory, SDRAM Channel 0 (0x2...)
#define	HwMBCFG_INCRB_GPMEM						Hw0										// General purpose SRAM, Shared SRAM, DTCM, Boot-ROM

/************************************************************************
*	Protect Register Define						(Base Addr = 0xF3006000)
************************************************************************/
#define	HwCLZDATA0								*(volatile unsigned long *)0xF3006000	// R/W, Raw Data
                                    			
#define	HwCLZDATA1								*(volatile unsigned long *)0xF3006004	// R/W, Bit-reversed Data
                                    			
#define	HwCLZDATA2								*(volatile unsigned long *)0xF3006008	// R/W, Bit-reversed data (11~0)
                                    			
#define	HwCLZDATA3								*(volatile unsigned long *)0xF300600C	// R/W, Count leading zero
                                    			
#define	HwPRTDATA0								*(volatile unsigned long *)0xF3006010	// R/W, 
                                    			
#define	HwPRTDATA1								*(volatile unsigned long *)0xF3006014	// R/W, 
                                    			
#define	HwPRTDATA2								*(volatile unsigned long *)0xF3006018	// R/W, 
                                    			
#define	HwPRTDATA3								*(volatile unsigned long *)0xF300601C	// R/W, 

/************************************************************************
*	MAILBOX Register Define						(Base Addr = 0xF4000000)
************************************************************************/
#define	HwMBOX_BASE							*(volatile unsigned long *)0xF4000000
#define	HwMBOXTXD								*(volatile unsigned long *)0xF4000000	// W, Transmit FIFO Data Region
                                    			
#define	HwMBOXRXD								*(volatile unsigned long *)0xF4000020	// R, Received FIFO Data Region
                                    			
#define HwMBOXCTR								*(volatile unsigned long *)0xF4000040	// R/W, MAILBOX Control
#define HwMBOXCTR_TEST							Hw31							// For Test Purpose
#define HwMBOXCTR_FLUSH							Hw6								// Flush the transmit data fifo
#define HwMBOXCTR_OEN							Hw5								// Transmit data output enable
#define HwMBOXCTR_IEN							Hw4								// Received data interrupt enable
                                    			
#define	HwMBOXSTR								*(volatile unsigned long *)0xF4000044	// R/W, MAILBOX Status
#define	HwMBOXSTR_SFUL							Hw17							// Full Status of Recevie FIFO
#define	HwMBOXSTR_SEMP							Hw16						// Empty Status of Receive FIFO
#define	HwMBOXSTR_MFUL							Hw1								// Full Status of Transmit FIFO
#define	HwMBOXSTR_MEMP							Hw0							// Empty Status of Transmit FIFO

#define	HwSUBMBOX_BASE						*(volatile unsigned long *)0xFF050000
#define	HwSUBMBOXTXD							*(volatile unsigned long *)0xFF050000	// W, Transmit FIFO Data Region
#define	HwSUBMBOXRXD							*(volatile unsigned long *)0xFF050020	// R, Transmit FIFO Data Region
#define	HwSUBMBOXCTR							*(volatile unsigned long *)0xFF050040	// R/W, MAILBOX Control
#define	HwSUBMBOXSTR							*(volatile unsigned long *)0xFF050044	// R/W, MAILBOX Status
#define	HwSUBHALT								*(volatile unsigned long *)0xFF010000	//subcore에서 현재 명령라인에서 sleep함. 이후 다시 메시지가 들어오면 이후부터 계속 수행됨.

/***********************************************************************
*	External Host Interface Register Define		(Base Addr = 0xF5000000)
************************************************************************/
#define	HwEHST									*(volatile unsigned long *)0xF5000000	// R/W, Status register
#define	HwEHST_RDY								Hw7										//
                                        		
#define	HwEHIINT								*(volatile unsigned long *)0xF5000004	// R/W,  Internal interrupt control register
#define	HwEHIINT_IIRQ							Hw0										//
                                        		
#define	HwEHEINT								*(volatile unsigned long *)0xF5000008	// R/W,  External interrupt control register
#define	HwEHEINT_EIRQ							Hw0										//
                                        		
#define	HwEHA									*(volatile unsigned long *)0xF500000C	// R/W,  Address register
                                        		
#define	HwEHAM									*(volatile unsigned long *)0xF5000010	// R,  Address masking register
                                        		
#define	HwEHD									*(volatile unsigned long *)0xF5000014	// R/W,  Data register
                                        		
#define	HwEHSEM									*(volatile unsigned long *)0xF5000018	// R/W,  Semaphore register
#define	HwEHSEM_FLG_NOT							HwZERO									//
#define	HwEHSEM_FLG_RWEHDROCPU					Hw0										//
#define	HwEHSEM_FLG_RWCPUROEHD					Hw1										//
#define	HwEHSEM_FLG_NA							(Hw1+Hw0)								//
                                        		
#define	HwEHCFG									*(volatile unsigned long *)0xF500001C	// R/W,  Configuration register
#define	HwEHCFG_RDYP							Hw4										//
#define	HwEHCFG_RDYE_RDY						Hw3										//
#define	HwEHCFG_RDYE_IRQ						HwZERO									//
#define	HwEHCFG_BW_16							Hw2										//
#define	HwEHCFG_BW_8							HwZERO									//
#define	HwEHCFG_MD_68							Hw0										//
#define	HwEHCFG_MD_80							HwZERO									//
                                        		
#define	HwEHIND									*(volatile unsigned long *)0xF5000020	// W,  Index register
                                        		
#define	HwEHRWCS								*(volatile unsigned long *)0xF5000024	// R/W,  Read/Write Control/Status register
#define	HwEHRWCS_AI								Hw7										//
#define	HwEHRWCS_LOCK_ON						Hw6										//
#define	HwEHRWCS_LOCK_OFF						~Hw6									//
#define	HwEHRWCS_RW_EHI							~(Hw5+Hw4)								//
#define	HwEHRWCS_RW_WAHB						Hw4										//
#define	HwEHRWCS_RW_RAHB						Hw5										//
#define	HwEHRWCS_RW_NA							(Hw5+Hw4)								//

/***********************************************************************
*	2D DMA Controller Register Define			(Base Addr = 0xF6000000)
************************************************************************/
#define	Hw2D_SRCA_F								*(volatile unsigned long *)0xF6000000	// Front Source Address Register
                                			
#define	Hw2D_SRCOFF_F							*(volatile unsigned long *)0xF6000004	// Front Source Offset Register
                                			
#define	Hw2D_DSTA_F								*(volatile unsigned long *)0xF6000008	// Front Destination Address Register
                                			
#define	Hw2D_DSTOFF_F							*(volatile unsigned long *)0xF600000C	// Front Destination Offset Register
                                			
#define	Hw2D_NUMT_F								*(volatile unsigned long *)0xF6000010	// Front Transfer Count Number Register
                                			
#define	Hw2D_SRCA_B								*(volatile unsigned long *)0xF6000014	// Back Source Address Register
                                			
#define	Hw2D_SRCOFF_B							*(volatile unsigned long *)0xF6000018	// Back Source Offset Register
                                			
#define	Hw2D_DSTA_B								*(volatile unsigned long *)0xF600001C	// Back Destination Address Register
                                			
#define	Hw2D_DSTOFF_B							*(volatile unsigned long *)0xF6000020	// Back Destination Offset Register
                                			
#define	Hw2D_NUMT_B								*(volatile unsigned long *)0xF6000024	// Back Transfer Count Number Register
                                			
#define	Hw2D_SRC1A_R							*(volatile unsigned long *)0xF6000028	// ROP Source 1 Address Register
                                			
#define	Hw2D_SRC1OFF_R							*(volatile unsigned long *)0xF600002C	// ROP Source 1 Offset Register
                                			
#define	Hw2D_SRC2A_R							*(volatile unsigned long *)0xF6000030	// ROP Source 2(Y) Address Register
                                			
#define	Hw2D_SRC2OFF_R							*(volatile unsigned long *)0xF6000034	// ROP Source 2 Offset Register
                                			
#define	Hw2D_SRC2CBA_R							*(volatile unsigned long *)0xF6000038	// ROP Source 2 Cb Address Register
                                			
#define	Hw2D_SRC2CRA_R							*(volatile unsigned long *)0xF600003C	// ROP Source 2 Cr Address Register
                                			
#define	Hw2D_DSTA_R								*(volatile unsigned long *)0xF6000040	// ROP Destination (Y) Address Register
                                			
#define	Hw2D_DSTOFF_R							*(volatile unsigned long *)0xF6000044	// ROP Destination Offset Register
                                			
#define	Hw2D_DSTCBA_R							*(volatile unsigned long *)0xF6000048	// ROP Destination Cb Address Register
                                			
#define	Hw2D_DSTCRA_R							*(volatile unsigned long *)0xF600004C	// ROP Destination Cr Address Register
                                			
#define	Hw2D_IMGSIZE							*(volatile unsigned long *)0xF6000050	// Image Size Register
                                			
#define Hw2D_MEMADDR							*(volatile unsigned long *)0xF6000054	// Buffer Memory Address Register
                                			
#define	Hw2D_LOCAL								*(volatile unsigned long *)0xF6000058	// Local Region Register
                                			
#define	Hw2D_FPVALUE							*(volatile unsigned long *)0xF600005C	// Fill/Pattern Value Register
                                        	
#define	Hw2D_IMGFM_R							*(volatile unsigned long *)0xF6000060	// ROP Image Format Register
#define	Hw2D_IMGFM_R_SRC1IMG_RGB888				HwZERO									// RGB888
#define	Hw2D_IMGFM_R_SRC1IMG_RGB666				Hw8										// RGB666
#define	Hw2D_IMGFM_R_SRC1IMG_RGB565				Hw9										// RGB565
#define	Hw2D_IMGFM_R_SRC1IMG_YCBCR422SEQ		(Hw9+Hw8)								// YCbCr 4:2:2 Sequential Format
#define	Hw2D_IMGFM_R_SRC2IMG_RGB888				HwZERO									// RGB888
#define	Hw2D_IMGFM_R_SRC2IMG_RGB666				Hw4										// RGB666
#define	Hw2D_IMGFM_R_SRC2IMG_RGB565				Hw5										// RGB565
#define	Hw2D_IMGFM_R_SRC2IMG_YCBCR422SEQ		(Hw5+Hw4)								// YCbCr 4:2:2 Sequential Format
#define	Hw2D_IMGFM_R_SRC2IMG_YCBCR420SEQ		Hw6										// YCbCr 4:2:0 Sequential Format
#define	Hw2D_IMGFM_R_SRC2IMG_YCBCR420SEP		(Hw6+Hw4)								// YCbCr 4:2:0 Separated Format
#define	Hw2D_IMGFM_R_DSTIMG_RGB888				HwZERO									// RGB888
#define	Hw2D_IMGFM_R_DSTIMG_RGB666				Hw0										// RGB666
#define	Hw2D_IMGFM_R_DSTIMG_RGB565				Hw1										// RGB565
#define	Hw2D_IMGFM_R_DSTIMG_YCBCR422SEQ			(Hw1+Hw0)								// YCbCr 4:2:2 Sequential Format
#define	Hw2D_IMGFM_R_DSTIMG_YCBCR420SEQ			Hw2										// YCbCr 4:2:0 Sequential Format
#define	Hw2D_IMGFM_R_DSTIMG_YCBCR420SEP			(Hw2+Hw0)								// YCbCr 4:2:0 Separated Format
                                        	
#define	Hw2D_CHROMA_R							*(volatile unsigned long *)0xF6000064	// Chroma Register
#define	Hw2D_CHROMA_R_KEYR_MAX					0x00FF0000
#define	Hw2D_CHROMA_R_KEYG_MAX					0x0000FF00
#define	Hw2D_CHROMA_R_KEYB_MAX					0x000000FF
                                        	
#define	Hw2D_CONTROL							*(volatile unsigned long *)0xF6000070	// Control Register
#define	Hw2D_CONTROL_BDTP						Hw31									// Backend Destination Transfer Type
#define	Hw2D_CONTROL_BSTP						Hw30									// Backend Source Transfer Type
#define	Hw2D_CONTROL_BIEN						Hw29									// Backend Interrupt Enable
#define	Hw2D_CONTROL_BFILL						Hw28									// Backend Fill Mode
#define	Hw2D_CONTROL_BEN						Hw27									// Backend DMA Enable
#define	Hw2D_CONTROL_FDTP						Hw25									// Frontend Destination Transfer Type
#define	Hw2D_CONTROL_FSTP						Hw24									// Frontend Source Transfer Type
#define	Hw2D_CONTROL_FIEN						Hw23									// Frontend Interrupt Enable
#define	Hw2D_CONTROL_FFILL						Hw22									// Frontend Fill Mode
#define	Hw2D_CONTROL_FEN						Hw21									// Frontend DMA Enable
#define	Hw2D_CONTROL_CHEN						Hw20									// Chroma-Key Enable
#define	Hw2D_CONTROL_ROPFUNC_NOP				HwZERO									// No Operation
#define	Hw2D_CONTROL_ROPFUNC_BNESS				Hw16									// Blackness
#define	Hw2D_CONTROL_ROPFUNC_DSTINV				Hw17									// Destination Invert
#define	Hw2D_CONTROL_ROPFUNC_MERCPY				(Hw17+Hw16)								// Merge Copy
#define	Hw2D_CONTROL_ROPFUNC_MERPIT				Hw18									// Merge Paint
#define	Hw2D_CONTROL_ROPFUNC_NOTSRCCPY			(Hw18+Hw16)								// Not Source Copy
#define	Hw2D_CONTROL_ROPFUNC_NOTSRCERA			(Hw18+Hw17)								// Not Source Erase
#define	Hw2D_CONTROL_ROPFUNC_PATCPY				(Hw18+Hw17+Hw16)						// Pat Copy
#define	Hw2D_CONTROL_ROPFUNC_PATINV				Hw19									// Pat Invert
#define	Hw2D_CONTROL_ROPFUNC_PATPIT				(Hw19+Hw16)								// Pat Paint
#define	Hw2D_CONTROL_ROPFUNC_SRCAND				(Hw19+Hw17)								// Source AND
#define	Hw2D_CONTROL_ROPFUNC_SRCCPY				(Hw19+Hw17+Hw16)						// Source Copy
#define	Hw2D_CONTROL_ROPFUNC_SRCERA				(Hw19+Hw18)								// Source Erase
#define	Hw2D_CONTROL_ROPFUNC_SRCINV				(Hw19+Hw18+Hw16)						// Source Invert
#define	Hw2D_CONTROL_ROPFUNC_SRCPIT				(Hw19+Hw18+Hw17)						// Source Paint
#define	Hw2D_CONTROL_ROPFUNC_WNESS				(Hw19+Hw18+Hw17+Hw16)					// Whiteness
#define	Hw2D_CONTROL_SCALARFUNC_NOP				HwZERO									// No Operation
#define	Hw2D_CONTROL_SCALARFUNC_FOP				Hw12									// Filling Operation
#define	Hw2D_CONTROL_SCALARFUNC_IPOP			Hw13									// Pixel Inverting Operation
#define	Hw2D_CONTROL_SCALARFUNC_PAOP			(Hw13+Hw12)								// Pixel Adding Operation
#define	Hw2D_CONTROL_SCALARFUNC_PSOP			Hw14									// Pixel Subtracting Operation
#define	Hw2D_CONTROL_SCALARFUNC_PMOP			(Hw14+Hw12)								// Pixel Multiplying Operation
#define	Hw2D_CONTROL_GEOFUNC_NOP				HwZERO									// No Operation
#define	Hw2D_CONTROL_GEOFUNC_ROT90				Hw8										// Rotation 90 degrees
#define	Hw2D_CONTROL_GEOFUNC_ROT180				Hw9										// Rotation 180 degrees
#define	Hw2D_CONTROL_GEOFUNC_ROT270				(Hw9+Hw8)								// Rotation 270 degrees
#define	Hw2D_CONTROL_GEOFUNC_MIRH				Hw10									// Mirroring(flipping) horizontally
#define	Hw2D_CONTROL_GEOFUNC_MIRV				(Hw10+Hw8)								// Mirroring(flipping) Vertically
#define	Hw2D_CONTROL_GEOFUNC_MIRHV				(Hw10+Hw9)								// Mirroring(flipping) horizontally and vertically
#define	Hw2D_CONTROL_MEMSIZE_1616				HwZERO									// One buffer transfer size is 16x16
#define	Hw2D_CONTROL_MEMSIZE_3232				Hw4										// One buffer transfer size is 32x32
#define Hw2D_CONTROL_DMAG						Hw3										// DMA General Use
#define Hw2D_CONTROL_LEN						Hw2										// Local Region Enable
#define Hw2D_CONTROL_IEN						Hw1										// Interrupt Enable
#define Hw2D_CONTROL_MEN						Hw0										// Main Enable
                                        	
#define Hw2D_INT								*(volatile unsigned long *)0xF6000074	// Interrupt Register
#define Hw2D_INT_CB								Hw10									// Clear Backend DMA Interrupt
#define Hw2D_INT_CF								Hw9										// Clear Frontend DMA Interrupt
#define Hw2D_INT_CD								Hw8										// Clear Done Interrupt
#define Hw2D_INT_B								Hw2										// Backend DMA Interrupt Status
#define Hw2D_INT_F								Hw1										// Frontend DMA Interrupt Status
#define Hw2D_INT_DONE							Hw0										// Local Region Enable
                            		    	
#define	Hw2D_INTEN								*(volatile unsigned long *)0xF6000078	// Interrupt Enable Register
#define	Hw2D_INTEN_B							Hw2										// Enable Interrupt for Backend DMA
#define	Hw2D_INTEN_F							Hw1										// Enable Interrupt for Frontend DMA
#define	Hw2D_INTEN_DONE							Hw0										// Enable Interrupt for Done

/************************************************************************
*	Virtual MMU Register Define					(Base Addr = 0xF7000000)
************************************************************************/
#define	HwVMT_REGION0							*(volatile unsigned long *)0xF7000000	// R/W, Configuration Register for Region 0

#define	HwVMT_SZ(X)								(((X)-1)*Hw12)
#define	SIZE_4GB								32
#define	SIZE_2GB								31
#define	SIZE_1GB								30
#define	SIZE_512MB								29
#define	SIZE_256MB								28
#define	SIZE_128MB								27
#define	SIZE_64MB								26
#define	SIZE_32MB								25
#define	SIZE_16MB								24
#define	SIZE_8MB								23
#define	SIZE_4MB								22
#define	SIZE_2MB								21
#define	SIZE_1MB								20
#define	HwVMT_REGION_AP_ALL					(Hw11+Hw10)
#define	HwVMT_DOMAIN(X)						((X)*Hw5)
#define	HwVMT_REGION_EN						Hw9										// Region Enable Register
#define	HwVMT_CACHE_ON						Hw3										// Cacheable Register
#define	HwVMT_CACHE_OFF						HwZERO
#define	HwVMT_BUFF_ON							Hw2										// Bufferable Register
#define	HwVMT_BUFF_OFF							HwZERO

#define	HwVMT_REGION0_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION0_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION0_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_REGION1							*(volatile unsigned long *)0xF7000004	// R/W, Configuration Register for Region 1
#define	HwVMT_REGION1_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION1_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION1_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_REGION2							*(volatile unsigned long *)0xF7000008	// R/W, Configuration Register for Region 2
#define	HwVMT_REGION2_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION2_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION2_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_REGION3							*(volatile unsigned long *)0xF700000C	// R/W, Configuration Register for Region 3
#define	HwVMT_REGION3_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION3_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION3_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_REGION4							*(volatile unsigned long *)0xF7000010	// R/W, Configuration Register for Region 4
#define	HwVMT_REGION4_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION4_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION4_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_REGION5							*(volatile unsigned long *)0xF7000014	// R/W, Configuration Register for Region 5
#define	HwVMT_REGION5_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION5_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION5_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_REGION6							*(volatile unsigned long *)0xF7000018	// R/W, Configuration Register for Region 6
#define	HwVMT_REGION6_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION6_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION6_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_REGION7							*(volatile unsigned long *)0xF700001C	// R/W, Configuration Register for Region 7
#define	HwVMT_REGION7_EN						Hw9										// Region Enable Register
#define	HwVMT_REGION7_CA						Hw3										// Cacheable Register
#define	HwVMT_REGION7_BU						Hw2										// Bufferable Register
                                    			
#define	HwVMT_TABBASE							*(volatile unsigned long *)0xF7008000	// R, MMU Table Base Address

/************************************************************************
*	ETC Define
************************************************************************/
//#define PLL_FREQ								2031428
//#define PLL_FREQ								2400000
//#define PLL_FREQ								2160000
#define PLL_FREQ								1968000
//#define PLL_FREQ								2485714
//#define GET_DPHASE(fs,system)					(unsigned long)((fs)*(system)*16384/PLL_FREQ)

/************************************************************************
*	ARM
************************************************************************/
#define	IO_ARM_MMU_DTCM							Hw16
#define	IO_ARM_MMU_ICACHE						Hw12
#define	IO_ARM_MMU_DCACHE						Hw2
#define	IO_ARM_MMU_PROT							Hw0
#define	IO_ARM_MMU_ALL							(Hw16+Hw12+Hw2+Hw0)

#endif

/* end of file */

