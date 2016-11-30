/****************************************************************************
 *   FileName    : TCC79x.h
 *   Description : TCC79x REGISTER DEFINE FUNCTION
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

/****************************************************************************

  Revision History

 ****************************************************************************

 ****************************************************************************/

/************************************************************************
*	TCC79x Internal Register Definition File
************************************************************************/
#ifndef	__TCC79x_H__
#define	__TCC79x_H__

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
	IRQ_SEL0,
	IRQ_SEL1,
	IRQ_SC,
	IRQ_I2C,
	IRQ_DAIRX,
	IRQ_DAITX,
	IRQ_CDRX,
	IRQ_EHI,
	IRQ_UT,
	IRQ_SEL2,
	IRQ_G2D,
	IRQ_UD,
	IRQ_UH,
	IRQ_DMA,
	IRQ_HDD,
	IRQ_SEL3,
	IRQ_NFC,
	IRQ_SD,
	IRQ_CAM,
	IRQ_LCD,
	IRQ_ADC,
	IRQ_SEL4,
	IRQ_MaxNum
};
#define	IRQ_VIDEO		IRQ_SEL0
#define	IRQ_EHI0		IRQ_SEL0
#define	IRQ_EI4			IRQ_SEL0
#define	IRQ_GPSB_SEL1	IRQ_SEL1
#define	IRQ_EHI1_SEL1	IRQ_SEL1
#define	IRQ_EI5			IRQ_SEL1
#define	IRQ_UT_SEL2		IRQ_SEL2
#define	IRQ_EHI1_SEL2	IRQ_SEL2
#define	IRQ_MS			IRQ_SEL3
#define	IRQ_EI6			IRQ_SEL3
#define	IRQ_GPSB_SEL4	IRQ_SEL4
#define	IRQ_ECC			IRQ_SEL4
#define	IRQ_EI7			IRQ_SEL4
#define	IRQ_UDMA		IRQ_SEL4

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

#define	HwVERSION								*(volatile unsigned long *)0xE0001FFC

/************************************************************************
*	LCD INTERFACE Register Define				(Base Addr = 0xF0000000)
************************************************************************/
#define	HwLCD_BASE							*(volatile unsigned long *)0xF0000000	// LCD Control Base Register

#define	HwLCTRL									*(volatile unsigned long *)0xF0000000	// W, LCD Control Register
	#define	HwLCTRL_Y2R2_EN							Hw31									// YUV to RGB Channel Converter Enable 2
	#define	HwLCTRL_AEN2_EN							Hw30									// Alpha Blend Enable 2
	#define	HwLCTRL_CEN2_EN							Hw29									// Chroma Key Enable 2
	#define	HwLCTRL_Y2R1_EN							Hw28									// YUV to RGB Channel Converter Enable 1
	#define	HwLCTRL_AEN1_EN							Hw27									// Alpha Blend Enable 1
	#define	HwLCTRL_CEN1_EN							Hw26									// Chroma Key Enable 1
	#define	HwLCTRL_Y2R0_EN							Hw25									// YUV to RGB Channel Converter Enable 0
	#define	HwLCTRL_656_EN							Hw24									// CCIR 601 to 656 Enable
	#define	HwLCTRL_CL_1							Hw23									// Pixel Clock is operated without Buffer Full Signal
	#define	HwLCTRL_CL_0							HwZERO									// Pixel Clock is operated by Buffer Full Signal of LCDSI & PIP mode
	#define	HwLCTRL_BPP(X)							((X)*Hw20)								// Bit Per Pixel
	#define	HwLCTRL_BPP_1							HwZERO									// Bit Per Pixel = 1bbp
	#define	HwLCTRL_BPP_2							Hw20									// Bit Per Pixel = 2bbp 
	#define	HwLCTRL_BPP_4							Hw21									// Bit Per Pixel = 4bbp
	#define	HwLCTRL_BPP_332							(Hw21+Hw20)								// Bit Per Pixel = 332bbp
	#define	HwLCTRL_BPP_444							Hw22									// Bit Per Pixel = 444bbp
	#define	HwLCTRL_BPP_MASK						(Hw22+Hw21+Hw20)						// Bit Per Pixel Mask
	#define	HwLCTRL_PXDW(X)						((X)*Hw16)								// Pixel Data Width
	#define	HwLCTRL_PXDW_4							HwZERO									// Pixel Data Width = 4pxdw
	#define	HwLCTRL_PXDW_8							Hw16									// Pixel Data Width = 8pxdw
	#define	HwLCTRL_PXDW_8S_RGB					Hw17									// Pixel Data Width = 8pxdw (stripe type: R8-G8-B8)
	#define	HwLCTRL_PXDW_565						(Hw17+Hw16)								// Pixel Data Width = 565pxdw
	#define	HwLCTRL_PXDW_555						Hw18									// Pixel Data Width = 555pxdw
	#define	HwLCTRL_PXDW_18							(Hw18+Hw16)								// Pixel Data Width = 18pxdw
	#define	HwLCTRL_PXDW_8UY						(Hw18+Hw17)								// Pixel Data Width = 8pxdw(UY)
	#define	HwLCTRL_PXDW_8VY						(Hw18+Hw17+Hw16)						// Pixel Data Width = 8pxdw(VY)
	#define	HwLCTRL_PXDW_16YU						Hw19									// Pixel Data Width = 16pxdw(YU)
	#define	HwLCTRL_PXDW_16YV						(Hw19+Hw16)								// Pixel Data Width = 16pxdw(YV)
	#define	HwLCTRL_PXDW_888D_EvGRB				HwLCTRL_PXDW(10)						// Pixel Data Width = 888pxdw (Delta type: odd=RGB, even=GRB)
	#define	HwLCTRL_PXDW_888D_EvRGB				HwLCTRL_PXDW(11)						// Pixel Data Width = 888pxdw (Delta type: odd=GRB, even=RGB)
	#define	HwLCTRL_PXDW_888						HwLCTRL_PXDW(12)						// Pixel Data Width = 888pxdw (stripe type: RGB)
	#define	HwLCTRL_PXDW_8S_RGBD					HwLCTRL_PXDW(13)						// Pixel Data Width = 8pxdw (stripe type with dummy: RGBD)
	#define	HwLCTRL_PXDW_MASK						(Hw20-Hw16)								// Pixel Data Width Mask
	#define	HwLCTRL_ID_INVERTED						Hw15									// Inverted ACBIAS
	#define	HwLCTRL_IV_INVERTED						Hw14									// Inverted Vertical Sync
	#define	HwLCTRL_IH_INVERTED						Hw13									// Inverted Horizontal Sync
	#define	HwLCTRL_IP_FEDGE						Hw12									// Data is driven onto the LCD's data pins on the falling edge of pixel clock pin
	#define	HwLCTRL_CLEN							Hw11									// Clipping Enable
	#define	HwLCTRL_R2Y_EN							Hw10									// RGB to YUV Channel Converter Enable
	#define	HwLCTRL_DP_2							Hw9										// One pixel data per 2 PXCLK cycle is output
	#define	HwLCTRL_NI_PMODE						Hw8										// Non-interlace Mode (Progressive Mode)
	#define	HwLCTRL_TV								Hw7										// TV Mode. In this mode, all values of LVTIMEn registers are divided by 2
	#define	HwLCTRL_TFT								Hw6										// TFT-LCD Mode
	#define	HwLCTRL_STN								Hw5										// STN-LCD Mode
	#define	HwLCTRL_MSEL							Hw4										// Master Select
	#define	HwLCTRL_IEN2_EN							Hw3										// Fetch Enable 2
	#define	HwLCTRL_IEN1_EN							Hw2										// Fetch Enable 1
	#define	HwLCTRL_IEN0_EN							Hw1										// Fetch Enable 0
	#define	HwLCTRL_LEN_EN							Hw0										// LCD Controller Enable

#define	HwLBC									*(volatile unsigned long *)0xF0000004	// W, LCD Background Color Register
	#define	HwLBC_BG2(X)							((X)*Hw16)						// Background Color 2 (Y/B)
	#define	HwLBC_BG2_MASK							(Hw24-Hw16)
	#define	HwLBC_BG1(X)							((X)*Hw8)						// Background Color 1 (Cb/G)
	#define	HwLBC_BG1_MASK							(Hw16-Hw8)
	#define	HwLBC_BG0(X)							((X)*Hw0)						// Background Color 0 (Cr/R)
	#define	HwLBC_BG0_MASK							(Hw8-Hw0)

#define	HwLCLKDIV								*(volatile unsigned long *)0xF0000008	// W, LCD Clock Divider Register
	#define	HwLCLKDIV_CS							Hw31									// Clock source
	#define	HwLCLKDIV_ACDIV(X)						((X)*Hw16)						// AC Bias Divider (STN only)
	#define	HwLCLKDIV_ACDIV_MASK					(Hw24-Hw16)
	#define	HwLCLKDIV_LCLKDIV(X)					((X)*Hw8)						// LCLK clock divider (Used if CS is set to 1)
	#define	HwLCLKDIV_LCLKDIV_MASK					(Hw16-Hw8)
	#define	HwLCLKDIV_PXCLKDIV(X)					((X)*Hw0)						// Pixel clock divider (Pixel clock = Lclk / (2*PXCLKDIV))
	#define	HwLCLKDIV_PXCLKDIV_MASK				(Hw8-Hw0)

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
	#define	HwLK_SA1_PIXEL							Hw31							// Alpha is applied in pixel data value
	#define	HwLK_SA1_REGISTER						HwZERO							// Alpha is applied in register value
	#define	HwLK_Ax0(X)								((X)*Hw24)						// Alpha Value
	#define	HwLK_A10_MASK							HwLK_Ax0(15)
	#define	HwLK1_A10_MAX							HwLK_Ax0(15)
	#define	HwLK_KR(X)								((X)*Hw16)						// Chroma-Key in R(Y) channel
	#define	HwLK_KR_MASK							HwLK_KR(255)
	#define	HwLK_KG(X)								((X)*Hw8)						// Chroma-Key in G(U) channel
	#define	HwLK_KG_MASK							HwLK_KG(255)
	#define	HwLK_KB(X)								((X)*Hw0)						// Chroma-Key in B(V) channel
	#define	HwLK_KB_MASK							HwLK_KB(255)

#define	HwLK2									*(volatile unsigned long *)0xF0000050	// W, LCD Keying Register 2
	#define	HwLK2_A20_MAX							HwLK_Ax0(15)

#define	HwLKM1									*(volatile unsigned long *)0xF0000054	// W, LCD Keying Mask Register 1
	#define	HwLKM1_A11_MAX							HwLK_Ax0(15)

#define	HwLKM2									*(volatile unsigned long *)0xF0000058	// W, LCD Keying Mask Register 2
	#define	HwLKM2_A21_MAX							HwLK_Ax0(15)

#define	HwLDS									*(volatile unsigned long *)0xF000005C	// W, LCD Display Size Register
                                        	
#define	HwLSTATUS								*(volatile unsigned long *)0xF0000060	// R/Clr, LCD Status Register
	#define	HwLSTATUS_VS							Hw15							// Monitoring vertical sync.
	#define	HwLSTATUS_ITY							Hw12							// Interrupt Type
	#define	HwLSTATUS_ICR							Hw8								// Interrupt Clear, using ITY is level type
	#define	HwLSTATUS_BY							Hw6								// Busy signal
	#define	HwLSTATUS_EF							Hw5								// Even-Field(Read Only). 0:Odd field or frame, 1:Even field or frame
	#define	HwLSTATUS_DD							Hw4								// Disable Done(Read/Clear). If LEN is disabled, DD will be 1 after current frame has been displayed. As MDD of LIM register is cleared, it can be LCD interrupt source
	#define	HwLSTATUS_RU							Hw3								// Register Update(Read/Clear). It indicates that all registers programmed are applied to current frame data. As MRU of LIM register is cleared, it can be LCD interrupt source
	#define	HwLSTATUS_FU							Hw0								// FIFO underrun(Read/Clear). It indicates that FIFO underrun has been occurred. In this case, LCLK frequency must be lower. As MFU of LIM register is cleared, it can be LCD interrupt source

#define	HwLIM									*(volatile unsigned long *)0xF0000064	// W, LCD Interrupt Register
	#define	HwLIM_MDD								Hw4								// Masking disable done interrupt
	#define	HwLIM_MRU								Hw3								// Masking register update interrupt
	#define	HwLIM_MFU								Hw0								// Masking FIFO underrun interrupt

#define	HwLI0C									*(volatile unsigned long *)0xF0000068	// W, LCD Image 0 Control Register
	#define	HwLI0C_PD_MSB							Hw15							// Padding MSB
	#define	HwLI0C_PD_ZERO							HwZERO							// Padding ZERO
	#define	HwLI0C_IMG012							HwZERO							//
	#define	HwLI0C_IMG021							Hw12							//
	#define	HwLI0C_IMG102							Hw13							//
	#define	HwLI0C_IMG201							(Hw13+Hw12)						//
	#define	HwLI0C_IMG120							Hw14							//
	#define	HwLI0C_IMG210							(Hw14+Hw12)						//
	#define	HwLI0C_BR_BE							Hw7								// Big Endian pixel data
	#define	HwLI0C_YUV_420							Hw4								// YUV 4:2:0
	#define	HwLI0C_YUV_422							(Hw5+Hw4)						// YUV 4:2:2
	#define	HwLI0C_YUV_422P							(Hw6+Hw5+Hw4)					// YUV 4:2:2 Patch
	#define	HwLIC_BPP(X)							((X))
	#define	HwLIC_BPP_MASK							HwLIC_BPP(15)
	#define	HwLI0C_BPP_1							HwLIC_BPP(0)					// Bit Per Pixel = 1bpp
	#define	HwLI0C_BPP_2							HwLIC_BPP(1)					// Bit Per Pixel = 2bpp
	#define	HwLI0C_BPP_4							HwLIC_BPP(2)					// Bit Per Pixel = 4bpp
	#define	HwLI0C_BPP_332							HwLIC_BPP(3)					// Bit Per Pixel = 332bpp
	#define	HwLI0C_BPP_444							HwLIC_BPP(4)					// Bit Per Pixel = 444bpp
	#define	HwLI0C_BPP_565							HwLIC_BPP(5)					// Bit Per Pixel = 565bpp
	#define	HwLI0C_BPP_555							HwLIC_BPP(6)					// Bit Per Pixel = 555bpp
	#define	HwLI0C_BPP_888							HwLIC_BPP(7)					// Bit Per Pixel = 888bpp
	#define	HwLI0C_BPP_666							HwLIC_BPP(8)					// Bit Per Pixel = 666bpp					

#define	HwLI0P									*(volatile unsigned long *)0xF000006C	// W, LCD Image 0 Position Register

#define	HwLI0S									*(volatile unsigned long *)0xF0000070	// W, LCD Image 0 Size Register

#define	HwLI0BA0								*(volatile unsigned long *)0xF0000074	// W, LCD Image 0 Base Address 0 Register

#define	HwLI0CA									*(volatile unsigned long *)0xF0000078	// W, LCD Image 0 Current Address Register

#define	HwLI0BA1								*(volatile unsigned long *)0xF000007C	// W, LCD Image 0 Base Address 1 Register

#define	HwLI0BA2								*(volatile unsigned long *)0xF0000080	// W, LCD Image 0 Base Address 2 Register

#define	HwLI0O									*(volatile unsigned long *)0xF0000084	// W, LCD Image 0 Offset Register

#define	HwLI0SCALE								*(volatile unsigned long *)0xF0000088	// W, LCD Image 0 Scale Ratio
	#define	HwLISCALE_Y(X)							((X)*Hw4)
	#define	HwLISCALE_Y_MASK						HwLISCALE_Y(15)
	#define	HwLISCALE_X(X)							((X))
	#define	HwLISCALE_X_MASK						HwLISCALE_X(15)
	#define	HwLI0SCALE_Y_NS							HwZERO							// Non-Scalable
	#define	HwLI0SCALE_Y_D2							Hw4								// DownScale by 2
	#define	HwLI0SCALE_Y_D3							Hw5								// DownScale by 3
	#define	HwLI0SCALE_Y_D4							(Hw5+Hw4)						// DownScale by 4
	#define	HwLI0SCALE_Y_D8							(Hw6+Hw5+Hw4)					// DownScale by 8
	#define	HwLI0SCALE_Y_U2							(Hw7+Hw4)						// UpScale by 2
	#define	HwLI0SCALE_Y_U3							(Hw7+Hw5)						// UpScale by 3
	#define	HwLI0SCALE_Y_U4							(Hw7+Hw5+Hw4)					// UpScale by 4
	#define	HwLI0SCALE_Y_U8							(Hw7+Hw6+Hw5+Hw4)				// UpScale by 8
	#define	HwLI0SCALE_X_NS							HwZERO							// Non-Scalable
	#define	HwLI0SCALE_X_D2							Hw0								// DownScale by 2
	#define	HwLI0SCALE_X_D3							Hw1								// DownScale by 3
	#define	HwLI0SCALE_X_D4							(Hw1+Hw0)						// DownScale by 4
	#define	HwLI0SCALE_X_D8							(Hw2+Hw1+Hw0)					// DownScale by 8
	#define	HwLI0SCALE_X_U2							(Hw3+Hw0)						// UpScale by 2
	#define	HwLI0SCALE_X_U3							(Hw3+Hw1)						// UpScale by 3
	#define	HwLI0SCALE_X_U4							(Hw3+Hw1+Hw0)					// UpScale by 4
	#define	HwLI0SCALE_X_U8							(Hw3+Hw2+Hw1+Hw0)				// UpScale by 8

#define	HwLI1C									*(volatile unsigned long *)0xF000008C	// W, LCD Image 1 Control Register
	#define	HwLI1C_PD_EN							Hw15							// Enable Padding
	#define	HwLI1C_PD_DIS							~Hw15							// Disable Padding
	#define	HwLI1C_BR_BE							Hw7								// Big Endian pixel data
	#define	HwLI1C_YUV_420							Hw4								// YUV 4:2:0
	#define	HwLI1C_YUV_422							(Hw5+Hw4)						// YUV 4:2:2
	#define	HwLI1C_YUV_422P							(Hw6+Hw5+Hw4)					// YUV 4:2:2 Patch
	#define	HwLI1C_BPP_1							HwLIC_BPP(0)					// Bit Per Pixel = 1bpp
	#define	HwLI1C_BPP_2							HwLIC_BPP(1)					// Bit Per Pixel = 2bpp
	#define	HwLI1C_BPP_4							HwLIC_BPP(2)					// Bit Per Pixel = 4bpp
	#define	HwLI1C_BPP_332							HwLIC_BPP(3)					// Bit Per Pixel = 332bpp
	#define	HwLI1C_BPP_444							HwLIC_BPP(4)					// Bit Per Pixel = 444bpp
	#define	HwLI1C_BPP_565							HwLIC_BPP(5)					// Bit Per Pixel = 565bpp
	#define	HwLI1C_BPP_555							HwLIC_BPP(6)					// Bit Per Pixel = 555bpp
	#define	HwLI1C_BPP_888							HwLIC_BPP(7)					// Bit Per Pixel = 888bpp
	#define	HwLI1C_BPP_666							HwLIC_BPP(8)					// Bit Per Pixel = 666bpp					

#define	HwLI1P									*(volatile unsigned long *)0xF0000090	// W, LCD Image 1 Position Register

#define	HwLI1S									*(volatile unsigned long *)0xF0000094	// W, LCD Image 1 Size Register

#define	HwLI1BA0								*(volatile unsigned long *)0xF0000098	// W, LCD Image 1 Base Address 0 Register

#define	HwLI1CA									*(volatile unsigned long *)0xF000009C	// W, LCD Image 1 Current Address Register

#define	HwLI1BA1								*(volatile unsigned long *)0xF00000A0	// W, LCD Image 1 Base Address 1 Register

#define	HwLI1BA2								*(volatile unsigned long *)0xF00000A4	// W, LCD Image 1 Base Address 2 Register

#define	HwLI1O									*(volatile unsigned long *)0xF00000A8	// W, LCD Image 1 Offset Register

#define	HwLI1SCALE								*(volatile unsigned long *)0xF00000AC	// W, LCD Image 1 Scale Ratio
	#define	HwLI1SCALE_Y_NS							HwZERO							// Non-Scalable
	#define	HwLI1SCALE_Y_D2							Hw4								// DownScale by 2
	#define	HwLI1SCALE_Y_D3							Hw5								// DownScale by 3
	#define	HwLI1SCALE_Y_D4							(Hw5+Hw4)						// DownScale by 4
	#define	HwLI1SCALE_Y_D8							(Hw6+Hw5+Hw4)					// DownScale by 8
	#define	HwLI1SCALE_Y_U2							(Hw7+Hw4)						// UpScale by 2
	#define	HwLI1SCALE_Y_U3							(Hw7+Hw5)						// UpScale by 3
	#define	HwLI1SCALE_Y_U4							(Hw7+Hw5+Hw4)					// UpScale by 4
	#define	HwLI1SCALE_Y_U8							(Hw7+Hw6+Hw5+Hw4)				// UpScale by 8
	#define	HwLI1SCALE_X_NS							HwZERO							// Non-Scalable
	#define	HwLI1SCALE_X_D2							Hw0								// DownScale by 2
	#define	HwLI1SCALE_X_D3							Hw1								// DownScale by 3
	#define	HwLI1SCALE_X_D4							(Hw1+Hw0)						// DownScale by 4
	#define	HwLI1SCALE_X_D8							(Hw2+Hw1+Hw0)					// DownScale by 8
	#define	HwLI1SCALE_X_U2							(Hw3+Hw0)						// UpScale by 2
	#define	HwLI1SCALE_X_U3							(Hw3+Hw1)						// UpScale by 3
	#define	HwLI1SCALE_X_U4							(Hw3+Hw1+Hw0)					// UpScale by 4
	#define	HwLI1SCALE_X_U8							(Hw3+Hw2+Hw1+Hw0)				// UpScale by 8
                                        	
#define	HwLI2C									*(volatile unsigned long *)0xF00000B0	// W, LCD Image 2 Control Register
	#define	HwLI2C_PD_EN							Hw15							// Enable Padding
	#define	HwLI2C_PD_DIS							~Hw15							// Disable Padding
	#define	HwLI2C_LUT(X)							((X)*Hw9)						// Use the Color Lookup Table
	#define	HwLI2C_LUT_CH0							HwLI2C_LUT(1)					// Use the Color Lookup Table in channel 0
	#define	HwLI2C_LUT_CH1							HwLI2C_LUT(2)					// Use the Color Lookup Table in channel 1
	#define	HwLI2C_LUT_CH2							HwLI2C_LUT(3)					// Use the Color Lookup Table in channel 2
	#define	HwLI2C_BR_BE							Hw7								// Big Endian pixel data
	#define	HwLI2C_YUV_420							Hw4								// YUV 4:2:0
	#define	HwLI2C_YUV_422							(Hw5+Hw4)						// YUV 4:2:2
	#define	HwLI2C_YUV_422P							(Hw6+Hw5+Hw4)					// YUV 4:2:2 Patch
	#define	HwLI2C_BPP_1							HwLIC_BPP(0)					// Bit Per Pixel = 1bpp
	#define	HwLI2C_BPP_2							HwLIC_BPP(1)					// Bit Per Pixel = 2bpp
	#define	HwLI2C_BPP_4							HwLIC_BPP(2)					// Bit Per Pixel = 4bpp
	#define	HwLI2C_BPP_332							HwLIC_BPP(3)					// Bit Per Pixel = 332bpp
	#define	HwLI2C_BPP_444							HwLIC_BPP(4)					// Bit Per Pixel = 444bpp
	#define	HwLI2C_BPP_565							HwLIC_BPP(5)					// Bit Per Pixel = 565bpp
	#define	HwLI2C_BPP_555							HwLIC_BPP(6)					// Bit Per Pixel = 555bpp
	#define	HwLI2C_BPP_888							HwLIC_BPP(7)					// Bit Per Pixel = 888bpp
	#define	HwLI2C_BPP_666							HwLIC_BPP(8)					// Bit Per Pixel = 666bpp					

#define	HwLI2P									*(volatile unsigned long *)0xF00000B4	// W, LCD Image 2 Position Register

#define	HwLI2S									*(volatile unsigned long *)0xF00000B8	// W, LCD Image 2 Size Register

#define	HwLI2BA0								*(volatile unsigned long *)0xF00000BC	// W, LCD Image 2 Base Address 0 Register

#define	HwLI2CA									*(volatile unsigned long *)0xF00000C0	// W, LCD Image 2 Current Address Register

#define	HwLI2BA1								*(volatile unsigned long *)0xF00000C4	// W, LCD Image 2 Base Address 1 Register

#define	HwLI2BA2								*(volatile unsigned long *)0xF00000C8	// W, LCD Image 2 Base Address 2 Register

#define	HwLI2O									*(volatile unsigned long *)0xF00000CC	// W, LCD Image 2 Offset Register

#define	HwLI2SCALE								*(volatile unsigned long *)0xF00000D0	// W, LCD Image 2 Scale Ratio
	#define	HwLI2SCALE_Y_NS							HwZERO							// Non-Scalable
	#define	HwLI2SCALE_Y_D2							Hw4								// DownScale by 2
	#define	HwLI2SCALE_Y_D3							Hw5								// DownScale by 3
	#define	HwLI2SCALE_Y_D4							(Hw5+Hw4)						// DownScale by 4
	#define	HwLI2SCALE_Y_D8							(Hw6+Hw5+Hw4)					// DownScale by 8
	#define	HwLI2SCALE_Y_U2							(Hw7+Hw4)						// UpScale by 2
	#define	HwLI2SCALE_Y_U3							(Hw7+Hw5)						// UpScale by 3
	#define	HwLI2SCALE_Y_U4							(Hw7+Hw5+Hw4)					// UpScale by 4
	#define	HwLI2SCALE_Y_U8							(Hw7+Hw6+Hw5+Hw4)				// UpScale by 8
	#define	HwLI2SCALE_X_NS							HwZERO							// Non-Scalable
	#define	HwLI2SCALE_X_D2							Hw0								// DownScale by 2
	#define	HwLI2SCALE_X_D3							Hw1								// DownScale by 3
	#define	HwLI2SCALE_X_D4							(Hw1+Hw0)						// DownScale by 4
	#define	HwLI2SCALE_X_D8							(Hw2+Hw1+Hw0)					// DownScale by 8
	#define	HwLI2SCALE_X_U2							(Hw3+Hw0)						// UpScale by 2
	#define	HwLI2SCALE_X_U3							(Hw3+Hw1)						// UpScale by 3
	#define	HwLI2SCALE_X_U4							(Hw3+Hw1+Hw0)					// UpScale by 4
	#define	HwLI2SCALE_X_U8							(Hw3+Hw2+Hw1+Hw0)				// UpScale by 8

#define	HwDLCTRL								*(volatile unsigned long *)0xF00000D4	// W, Dual LCD Control
	#define	HwDLCTRL_DRE							Hw4								// Dual LCD Register Update Enable
	#define	HwDLCTRL_DLE							Hw0								// Dual LCD Operation Enable

#define	HwDLCSA0								*(volatile unsigned long *)0xF00000DC	// W, Dual LCD Configuration Start Address 0

#define	HwDLCSA1								*(volatile unsigned long *)0xF00000E0	// W, Dual LCD Configuration Start Address 1

#define	HwY2RP0									*(volatile unsigned long *)0xF00000E4	// W, YCbCr to RGB Conversion Parameter 0

#define	HwY2RP1									*(volatile unsigned long *)0xF00000E8	// W, YCbCr to RGB Conversion Parameter 1

#define	HwLPMCTRL								*(volatile unsigned long *)0xF00000F0	// W, PIP Mode Control
	#define	HwLPMCTRL_PL_INT						Hw7								// PIP in TCCxxx Chip
	#define	HwLPMCTRL_PL_EXT						HwZERO							// PIP in External Chip
	#define	HwLPMCTRL_PS_WINDOW					Hw6								// PIP with Windowing Method
	#define	HwLPMCTRL_PS_CHROMA					HwZERO							// PIP with Chroma-key Method
	#define	HwLPMCTRL_FL_FLUSH						Hw5								// FIFO Flush
	#define	HwLPMCTRL_DS_DE						Hw4								// Detect using Data Enable or H-Sync
	#define	HwLPMCTRL_DS_VS						HwZERO							// Detect using V-Sync
	#define	HwLPMCTRL_DEP_LOW						Hw3								// Data Enable Polarity : Active Low
	#define	HwLPMCTRL_DEP_HIGH						HwZERO							// Data Enable Polarity : Active High
	#define	HwLPMCTRL_VP_LOW						Hw2								// V-Sync Polarity : Active Low
	#define	HwLPMCTRL_VP_HIGH						HwZERO							// V-Sync Polarity : Active High
	#define	HwLPMCTRL_ENS_HS						Hw1								// Use H-Sync
	#define	HwLPMCTRL_ENS_DE						HwZERO							// Use ACBias (DATAEN)
	#define	HwLPMCTRL_EN_EN						Hw0								// Enable PIP

#define	HwLPMW0								*(volatile unsigned long *)0xF00000F4	// W, PIP Mode Windowing 0

#define	HwLPMW1								*(volatile unsigned long *)0xF00000F8	// W, PIP Mode Windowing 1

#define	HwLPMH									*(volatile unsigned long *)0xF00000FC	// W, PIP Mode Height

#define	HwLPMC									*(volatile unsigned long *)0xF0000100	// W, PIP Mode Chroma-Key

#define	HwLPMMC								*(volatile unsigned long *)0xF0000104	// W, PIP Mode Mask Chroma-Key

#define	HwLCDLUT								*(volatile unsigned long *)0xF0000C00	// W, LCD Lookup Table
typedef	volatile struct {
	unsigned LCTRL;
	unsigned LBC;
	unsigned LCLKDIV;
	unsigned LHTIME1;
	unsigned LHTIME2;
	unsigned LVTIME1;
	unsigned LVTIME2;
	unsigned LVTIME3;
	unsigned LVTIME4;
	unsigned LLUTR;
	unsigned LLUTG;
	unsigned LLUTB;
	unsigned LDP7L;
	unsigned LDP7H;
	unsigned LDP5;
	unsigned LDP4;
	unsigned LDP3;
	unsigned LCP1;
	unsigned LCP2;
	unsigned LK1;
	unsigned LK2;
	unsigned LKM1;
	unsigned LKM2;
	unsigned LDS;
	unsigned LSTATUS;
	unsigned LIM;
	unsigned LI0C;
	unsigned LI0P;
	unsigned LI0S;
	unsigned LI0BA0;
	unsigned LI0CA;
	unsigned LI0BA1;
	unsigned LI0BA2;
	unsigned LI0O;
	unsigned LI0SR;
	unsigned LI1C;
	unsigned LI1P;
	unsigned LI1S;
	unsigned LI1BA0;
	unsigned LI1CA;
	unsigned LI1BA1;
	unsigned LI1BA2;
	unsigned LI1O;
	unsigned LI1SR;
	unsigned LI2C;
	unsigned LI2P;
	unsigned LI2S;
	unsigned LI2BA0;
	unsigned LI2CA;
	unsigned LI2BA1;
	unsigned LI2BA2;
	unsigned LI2O;
	unsigned LI2SR;
} sHwLCD;

/************************************************************************
*	LCD System Interface Register Define		(Base Addr = 0xF0000400)
************************************************************************/
#define	HwLCDSI_BASE							*(volatile unsigned long *)0xF0000400	// LCDSI Base Register

#define	HwLCDSICTRL0							*(volatile unsigned long *)0xF0000400	// R/W, Control Register for LCDSI
	#define	HwLCDSICTRL0_IA_LOW						Hw15						// LACBIAS(Data Enable) signal is active low
	#define	HwLCDSICTRL0_IVS_LOW					Hw14							// LYSYNC signal is active low
	#define	HwLCDSICTRL0_CS_1						Hw7								// If IM is high, CS1 is active during operationgs. Otherwise, it is no applicable. These bits are only available when IM is high
	#define	HwLCDSICTRL0_RSP_HIGH					Hw6								// If IM is high, RS is high. Otherwise, it is not applicable
	#define	HwLCDSICTRL0_FMT_8RGB565				HwZERO							// LCDC pixel data output:RGB565
																					// LCDSI pixel data output(8bits):RGB565[7:0], RGB565[15:8]
																					// LCDSI CTRL1-4.WBW must be 1
	#define	HwLCDSICTRL0_FMT_16RGB565				(Hw4+Hw3)						// LCDC pixel data output:RGB565
																					// LCDSI pixel data output(16bits):RGB565[15:0]
																					// LCDSI CTRL1-4.WBW must be 0
	#define	HwLCDSICTRL0_FMT_8RGB888				Hw2								// LCDC pixel data output:RGB888
																					// LCDSI pixel data output(8bits):R[7:0],G[7:0],B[7:0]
																					// LCDSI CTRL1-4.WBW must be 1
	#define	HwLCDSICTRL0_FMT_9RGB888				(Hw3+Hw2)						// LCDC pixel data output:RGB888
																					// LCDSI pixel data output(9bits):{G[2:0],R[5:0]},{B[5:0],G[5:3]}
																					// LCDSI CTRL1-4.WBW must be 0
	#define	HwLCDSICTRL0_FMT_16RGB888				(Hw4+Hw2)						// LCDC pixel data output:RGB888
																					// LCDSI pixel data output(16bits):RGB565[15:0]
																					// LCDSI CTRL1-4.WBW must be 0
	#define	HwLCDSICTRL0_FMT_18RGB888				(Hw4+Hw3+Hw2)					// LCDC pixel data output:RGB888
																					// LCDSI pixel data output(16bits):{B[3:0],G[5:0],R[5:0]},B[5:4]
																					// LCDSI CTRL1-4.WBW must be 0
	#define	HwLCDSICTRL0_OM						Hw1								//
	#define	HwLCDSICTRL0_IM						Hw0								//

#define	HwLCDSICTRL1							*(volatile unsigned long *)0xF0000800	// R/W, Control Register for nCS0 when RS = 0
	#define	HwLCDSICTRL1_BW_8						HwZERO							// Data width is 8 bits
	#define	HwLCDSICTRL1_BW_16						Hw15							// Data width is 16 bits
	#define	HwLCDSICTRL1_BW_18						(Hw31+Hw15)						// Data width is 18 bits
	#define	HwLCDSICTRL_BW_8						HwZERO							// Data width is 8 bits
	#define	HwLCDSICTRL_BW_16						Hw15							// Data width is 16 bits
	#define	HwLCDSICTRL_BW_18						(Hw31+Hw15)						// Data width is 18 bits

#define	HwLCDSICTRL2							*(volatile unsigned long *)0xF0000804	// R/W, Control Register for nCS0 when RS = 1
	#define	HwLCDSICTRL2_BW_8						HwZERO							// Data width is 8 bits
	#define	HwLCDSICTRL2_BW_16						Hw15							// Data width is 16 bits
	#define	HwLCDSICTRL2_BW_18						(Hw31+Hw15)						// Data width is 18 bits

#define	HwLCDSICTRL3							*(volatile unsigned long *)0xF0000808	// R/W, Control Register for nCS1 when RS = 0
	#define	HwLCDSICTRL3_BW_8						HwZERO							// Data width is 8 bits
	#define	HwLCDSICTRL3_BW_16						Hw15							// Data width is 16 bits
	#define	HwLCDSICTRL3_BW_18						(Hw31+Hw15)						// Data width is 18 bits

#define	HwLCDSICTRL4							*(volatile unsigned long *)0xF000080C	// R/W, Control Register for nCS0 when RS = 1
	#define	HwLCDSICTRL4_BW_8						HwZERO							// Data width is 8 bits
	#define	HwLCDSICTRL4_BW_16						Hw15							// Data width is 16 bits
	#define	HwLCDSICTRL4_BW_18						(Hw31+Hw15)						// Data width is 18 bits

#define	HwLCDSICS0RS0							*(volatile short *)0xF0000810			// R/W, If this register is read or written, reading or writing operations are generated on nCS0 while RS = 0

#define	HwLCDSICS0RS1							*(volatile short *)0xF0000818			// R/W, If this register is read or written, reading or writing operations are generated on nCS0 while RS = 1

#define	HwLCDSICS1RS0							*(volatile short *)0xF0000820			// R/W, If this register is read or written, reading or writing operations are generated on nCS1 while RS = 0

#define	HwLCDSICS1RS1							*(volatile short *)0xF0000828			// R/W, If this register is read or written, reading or writing operations are generated on nCS1 while RS = 1

#define	HwLCDSICTRL5							*(volatile unsigned long *)0xF0000830	// R/W, 
	#define	HwLCDSICTRL5_WBW						Hw31							//
	#define	HwLCDSICTRL_WBW						Hw31							//

#define	HwLCDSICTRL6							*(volatile unsigned long *)0xF0000834	// R/W, 
	#define	HwLCDSICTRL6_WBW						Hw31							//

#define	HwLCDSICTRL7							*(volatile unsigned long *)0xF0000838	// R/W, 
	#define	HwLCDSICTRL7_WBW						Hw31							//

#define	HwLCDSICTRL8							*(volatile unsigned long *)0xF000083C	// R/W, 
	#define	HwLCDSICTRL8_WBW						Hw31							//
typedef	volatile struct {
	unsigned CTRL0;
	unsigned _Dummy[(0x400-0x4)/4];
	unsigned CTRL1;
	unsigned CTRL2;
	unsigned CTRL3;
	unsigned CTRL4;
	unsigned CS0RS0;
	unsigned _Dummy_1;
	unsigned CS0RS1;
	unsigned _Dummy_2;
	unsigned CS1RS0;
	unsigned _Dummy_3;
	unsigned CS1RS1;
	unsigned _Dummy_4;
	unsigned CTRL5;
	unsigned CTRL6;
	unsigned CTRL7;
	unsigned CTRL8;

} sHwLCDSI;

/************************************************************************
*	TV Encoder Register Define				(Base Addr = 0xF9000000)
************************************************************************/
#define	HwTVE_BASE								*(volatile unsigned long *)0xF9000000	// TV Encoder Base Register

#define	HwTVESTATA								*(volatile unsigned long *)0xF9000000	// R, Status Register

#define	HwTVECMDA								*(volatile unsigned long *)0xF9000004	// R/W, Encoder Mode Control Register A
	#define	HwTVECMDA_PWDENC_PD					Hw7								// Power down mode for entire digital logic of TV encoder
	#define	HwTVECMDA_FDRST_1						Hw6								// Chroma is free running as compared to H-sync
	#define	HwTVECMDA_FDRST_0						HwZERO							// Relationship between color burst & H-sync is maintained for video standards
	#define	HwTVECMDA_FSCSEL(X)					((X)*Hw4)
	#define	HwTVECMDA_FSCSEL_NTSC					HwTVECMDA_FSCSEL(0)			// Color subcarrier frequency is 3.57954545 MHz for NTSC
	#define	HwTVECMDA_FSCSEL_PALX					HwTVECMDA_FSCSEL(1)			// Color subcarrier frequency is 4.43361875 MHz for PAL-B,D,G,H,I,N
	#define	HwTVECMDA_FSCSEL_PALM					HwTVECMDA_FSCSEL(2)			// Color subcarrier frequency is 3.57561149 MHz for PAL-M
	#define	HwTVECMDA_FSCSEL_PALCN				HwTVECMDA_FSCSEL(3)			// Color subcarrier frequency is 3.58205625 MHz for PAL-combination N
	#define	HwTVECMDA_FSCSEL_MASK					HwTVECMDA_FSCSEL(3)
	#define	HwTVECMDA_PEDESTAL					Hw3								// Video Output has a pedestal
	#define	HwTVECMDA_NO_PEDESTAL					HwZERO							// Video Output has no pedestal
	#define	HwTVECMDA_PIXEL_SQUARE				Hw2								// Input data is at square pixel rates.
	#define	HwTVECMDA_PIXEL_601					HwZERO							// Input data is at 601 rates.
	#define	HwTVECMDA_IFMT_625						Hw1								// Output data has 625 lines
	#define	HwTVECMDA_IFMT_525						HwZERO							// Output data has 525 lines
	#define	HwTVECMDA_PHALT_PAL					Hw0								// PAL encoded chroma signal output
	#define	HwTVECMDA_PHALT_NTSC					HwZERO							// NTSC encoded chroma signal output

#define	HwTVECMDB								*(volatile unsigned long *)0xF9000008	// R/W, Encoder Mode Control Register B
	#define	HwTVECMDB_YBIBLK_BLACK				Hw4								// Video data is forced to Black level for Vertical non VBI processed lines.
	#define	HwTVECMDB_YBIBLK_BYPASS				HwZERO							// Input data is passed through forn non VBI processed lines.
	#define	HwTVECMDB_CBW(X)						((X)*Hw2)
	#define	HwTVECMDB_CBW_LOW					HwTVECMDB_CBW(0)				// Low Chroma band-width
	#define	HwTVECMDB_CBW_MEDIUM					HwTVECMDB_CBW(1)				// Medium Chroma band-width
	#define	HwTVECMDB_CBW_HIGH					HwTVECMDB_CBW(2)				// High Chroma band-width
	#define	HwTVECMDB_CBW_MASK					HwTVECMDB_CBW(3)				// 
	#define	HwTVECMDB_YBW(X)						((X)*Hw0)
	#define	HwTVECMDB_YBW_LOW					HwTVECMDB_YBW(0)				// Low Luma band-width
	#define	HwTVECMDB_YBW_MEDIUM					HwTVECMDB_YBW(1)				// Medium Luma band-width
	#define	HwTVECMDB_YBW_HIGH					HwTVECMDB_YBW(2)				// High Luma band-width
	#define	HwTVECMDB_YBW_MASK					HwTVECMDB_YBW(3)				// 

#define	HwTVEGLK								*(volatile unsigned long *)0xF900000C	// R/W, Encoder Clock Generator Register
	#define	HwTVEGLK_XT24_24MHZ					Hw4								// 24MHz Clock input
	#define	HwTVEGLK_XT24_27MHZ					HwZERO							// 27MHz Clock input
	#define	HwTVEGLK_GLKEN_RST_EN					Hw3								// Reset Genlock
	#define	HwTVEGLK_GLKEN_RST_DIS					~Hw3							// Release Genlock
	#define	HwTVEGLK_GLKE(X)						((X)*Hw1)
	#define	HwTVEGLK_GLKE_INT						HwTVEGLK_GLKE(0)				// Chroma Fsc is generated from internal constants based on current user setting
	#define	HwTVEGLK_GLKE_RTCO						HwTVEGLK_GLKE(2)				// Chroma Fsc is adjusted based on external RTCO input
	#define	HwTVEGLK_GLKE_CLKI						HwTVEGLK_GLKE(3)				// Chroma Fsc tracks non standard encoder clock (CLKI) frequency
	#define	HwTVEGLK_GLKE_MASK						HwTVEGLK_GLKE(3)				//
	#define	HwTVEGLK_GLKEN_GLKPL_HIGH				Hw0								// PAL ID polarity is active high
	#define	HwTVEGLK_GLKEN_GLKPL_LOW				HwZERO							// PAL ID polarity is active low

#define	HwTVESCH								*(volatile unsigned long *)0xF9000010	// R/W, Color burst phase relation control (relative to Sync trip)

#define	HwTVEHUE								*(volatile unsigned long *)0xF9000014	// R/W, Active video Color burst phase relation control (relative to color burst)

#define	HwTVESAT								*(volatile unsigned long *)0xF9000018	// R/W, Active video Chroma gain control relative to color burst gain

#define	HwTVECONT								*(volatile unsigned long *)0xF900001C	// R/W, Luma gain control

#define	HwTVEBRIGHT							*(volatile unsigned long *)0xF9000020	// R/W, Luma offset control

#define	HwTVEFSC_ADJM							*(volatile unsigned long *)0xF9000024	// R/W, MSB of Fsc adjust value
#define	HwTVEFSC_ADJL							*(volatile unsigned long *)0xF9000028	// R/W, LSB of Fsc adjust value

#define	HwTVECMDC								*(volatile unsigned long *)0xF900002C	// R/W, Encoder Mode Control Register C
	#define	HwTVECMDC_CSMDE_EN					Hw7								// Composite Sync mode enabled
	#define	HwTVECMDC_CSMDE_DIS					~Hw7							// Composite Sync mode disabled (pin is tri-stated)
	#define	HwTVECMDC_CSMD(X)						((X)*Hw5)
	#define	HwTVECMDC_CSMD_CSYNC					HwTVECMDC_CSMD(0)				// CSYN pin is Composite sync signal
	#define	HwTVECMDC_CSMD_KEYCLAMP				HwTVECMDC_CSMD(1)				// CSYN pin is Keyed clamp signal
	#define	HwTVECMDC_CSMD_KEYPULSE				HwTVECMDC_CSMD(2)				// CSYN pin is Keyed pulse signal
	#define	HwTVECMDC_CSMD_MASK					HwTVECMDC_CSMD(3)
	#define	HwTVECMDC_RGBSYNC(X)					((X)*Hw3)
	#define	HwTVECMDC_RGBSYNC_NOSYNC				HwTVECMDC_RGBSYNC(0)			// Disable RGBSYNC (when output is configured for analog EGB mode)
	#define	HwTVECMDC_RGBSYNC_RGB				HwTVECMDC_RGBSYNC(1)			// Sync on RGB output signal (when output is configured for analog EGB mode)
	#define	HwTVECMDC_RGBSYNC_G					HwTVECMDC_RGBSYNC(2)			// Sync on G output signal (when output is configured for analog EGB mode)
	#define	HwTVECMDC_RGBSYNC_MASK				HwTVECMDC_RGBSYNC(3)

#define	HwTVEDACSEL							*(volatile unsigned long *)0xF9000040	// R/W, DAC Output Selection
	#define	HwTVEDACSEL_DACSEL_CODE0				HwZERO							// Data output is diabled (output is code '0')
	#define	HwTVEDACSEL_DACSEL_CVBS				Hw0								// Data output in CVBS format

#define	HwTVEDACPD								*(volatile unsigned long *)0xF9000050	// R/W, DAC Power Down
	#define	HwTVEDACPD_PD_EN						Hw0								// DAC Power Down Enabled
	#define	HwTVEDACPD_PD_DIS						~Hw0							// DAC Power Down Disabled

#define	HwTVEICNTL								*(volatile unsigned long *)0xF9000080	// R/W, Sync Control
	#define	HwTVEICNTL_FSIP_ODDHIGH				Hw7								// Odd field active high
	#define	HwTVEICNTL_FSIP_ODDLOW					HwZERO							// Odd field active low
	#define	HwTVEICNTL_VSIP_HIGH					Hw6								// V-sync active high
	#define	HwTVEICNTL_VSIP_LOW					HwZERO							// V-sync active low
	#define	HwTVEICNTL_HSIP_HIGH					Hw5								// H-sync active high
	#define	HwTVEICNTL_HSIP_LOW					HwZERO							// H-sync active low
	#define	HwTVEICNTL_HSVSP_RISING				Hw4								// H/V-sync latch enabled at rising edge
	#define	HwTVEICNTL_HVVSP_FALLING				HwZERO							// H/V-sync latch enabled at falling edge
	#define	HwTVEICNTL_VSMD_START					Hw3								// Even/Odd field H/V sync output are aligned to video line start
	#define	HwTVEICNTL_VSMD_MID					HwZERO							// Even field H/V sync output are aligned to video line midpoint
	#define	HwTVEICNTL_ISYNC(X)						((X)*Hw0)
	#define	HwTVEICNTL_ISYNC_FSI					HwTVEICNTL_ISYNC(0)			// Alignment input format from FSI pin
	#define	HwTVEICNTL_ISYNC_HVFSI					HwTVEICNTL_ISYNC(1)			// Alignment input format from HSI,VSI,FSI pin
	#define	HwTVEICNTL_ISYNC_HVSI					HwTVEICNTL_ISYNC(2)			// Alignment input format from HSI,VSI pin
	#define	HwTVEICNTL_ISYNC_VFSI					HwTVEICNTL_ISYNC(3)			// Alignment input format from VSI,FSI pin
	#define	HwTVEICNTL_ISYNC_VSI					HwTVEICNTL_ISYNC(4)			// Alignment input format from VSI pin
	#define	HwTVEICNTL_ISYNC_ESAV_L				HwTVEICNTL_ISYNC(5)			// Alignment input format from EAV,SAV codes (line by line)
	#define	HwTVEICNTL_ISYNC_ESAV_F				HwTVEICNTL_ISYNC(6)			// Alignment input format from EAV,SAV codes (frame by frame)
	#define	HwTVEICNTL_ISYNC_FREE					HwTVEICNTL_ISYNC(7)			// Alignment is free running (Master mode)
	#define	HwTVEICNTL_ISYNC_MASK					HwTVEICNTL_ISYNC(7)

#define	HwTVEHVOFFST							*(volatile unsigned long *)0xF9000084	// R/W, Offset Control
	#define	HwTVEHVOFFST_INSEL(X)					((X)*Hw6)
	#define	HwTVEHVOFFST_INSEL_BW16_27MHZ			HwTVEHVOFFST_INSEL(0)			// 16bit YUV 4:2:2 sampled at 27MHz
	#define	HwTVEHVOFFST_INSEL_BW16_13P5MHZ		HwTVEHVOFFST_INSEL(1)			// 16bit YUV 4:2:2 sampled at 13.5MHz
	#define	HwTVEHVOFFST_INSEL_BW8_13P5MHZ		HwTVEHVOFFST_INSEL(2)			// 8bit YUV 4:2:2 sampled at 13.5MHz
	#define	HwTVEHVOFFST_INSEL_MASK				HwTVEHVOFFST_INSEL(3)
	#define	HwTVEHVOFFST_VOFFST_256				Hw3								// Vertical offset bit 8 (Refer to HwTVEVOFFST)
	#define	HwTVEHVOFFST_HOFFST_1024				Hw2								// Horizontal offset bit 10 (Refer to HwTVEHOFFST)
	#define	HwTVEHVOFFST_HOFFST_512				Hw1								// Horizontal offset bit 9 (Refer to HwTVEHOFFST)
	#define	HwTVEHVOFFST_HOFFST_256				Hw0								// Horizontal offset bit 8 (Refer to HwTVEHOFFST)

#define	HwTVEVOFFST								*(volatile unsigned long *)0xF9000088	// R/W, Vertical Offset Control (bit [7:0], bit 8 is at HwTVEHVOFFST)
#define	HwTVEHOFFST								*(volatile unsigned long *)0xF900008C	// R/W, Horizontal Offset Control (bit [7:0], bit 10~8 is at HwTVEHVOFFST)

#define	HwTVEHSVSO								*(volatile unsigned long *)0xF9000090	// R/W, Sync Output Control
	#define	HwTVEHSVSO_VSOB_256					Hw6								// VSOB bit 8 (Refer to HwVSOB)
	#define	HwTVEHSVSO_HSOB_1024					Hw5								// HSOB bit 10 (Refer to HwHSOB)
	#define	HwTVEHSVSO_HSOB_512					Hw4								// HSOB bit 9 (Refer to HwHSOB)
	#define	HwTVEHSVSO_HSOB_256					Hw3								// HSOB bit 8 (Refer to HwHSOB)
	#define	HwTVEHSVSO_HSOE_1024					Hw2								// HSOE bit 10 (Refer to HwHSOE)
	#define	HwTVEHSVSO_HSOE_512					Hw1								// HSOE bit 9 (Refer to HwHSOE)
	#define	HwTVEHSVSO_HSOE_256					Hw0								// HSOE bit 8 (Refer to HwHSOE)

#define	HwTVEHSOE								*(volatile unsigned long *)0xF9000094	// R/W, Trailing Edge of Horizontal Sync Control (bit[7:0], bit 10~8 is at HwTVEHSVSO)

#define	HwTVEHSOB								*(volatile unsigned long *)0xF9000098	// R/W, Leading Edge of Horizontal Sync Control (bit[7:0], bit 10~8 is at HwTVEHSVSO)

#define	HwTVEVSOB								*(volatile unsigned long *)0xF900009C	// R/W, Leading Edge of Vertical Sync Control (bit[7:0], bit 8 is at HwTVEHSVSO)

#define	HwTVEVSOE								*(volatile unsigned long *)0xF90000A0	// R/W, Trailing Edge of Vertical Sync Control
	#define	HwTVEVSOE_VSOST(X)						((X)*Hw6)						// Programs V-sync relative location for Odd/Even Fields.
	#define	HwTVEVSOE_NOVRST_EN					Hw5								// No vertical reset on every field
	#define	HwTVEVSOE_NOVRST_NORMAL				HwZERO							// Normal vertical reset operation (interlaced output timing)
	#define	HwTVEVSOE_VSOE(X)						((X)*Hw0)						// Trailing Edge of Vertical Sync Control

#define	HwTVEVENCON							*(volatile unsigned long *)0xF9000800	// R/W, Connection between LCDC & TVEncoder Control
	#define	HwTVEVENCON_EN_EN						Hw0								// Connection between LCDC & TVEncoder Enabled
	#define	HwTVEVENCON_EN_DIS						~Hw0							// Connection between LCDC & TVEncoder Disabled

#define	HwTVEVENCIF								*(volatile unsigned long *)0xF9000804	// R/W, I/F between LCDC & TVEncoder Selection
//	#define	HwTVEVENCIF_DAC_EN						Hw2								// Enable DAC of TVEncoder
//	#define	HwTVEVENCIF_MV_1						Hw1								// reserved
	#define	HwTVEVENCIF_FMT_1						Hw0								// PXDATA[7:0] => CIN[7:0], PXDATA[15:8] => YIN[7:0]
	#define	HwTVEVENCIF_FMT_0						HwZERO							// PXDATA[7:0] => YIN[7:0], PXDATA[15:8] => CIN[7:0]

/***********************************************************************
*	USB Controller Register Define				(Base Addr = 0xF0010000)
************************************************************************/
#define	HwUSBD_BASE							*(volatile unsigned long *)0xF0010000	// USB Device Base Register

#define	HwIR									*(volatile unsigned long *)0xF0010000	// R/W, Index Register

#define	HwEIR									*(volatile unsigned long *)0xF0010004	// R/W, Endpoint Interrupt Register
	#define	HwEIR_EP0INT							Hw0								// W : Clear the EP0 interrupt flag, R : Indicates that the USB EP0 interrupt has been generated
	#define	HwEIR_EP1INT							Hw1								// W : Clear the EP1 interrupt flag, R : Indicates that the USB EP1 interrupt has been generated
	#define	HwEIR_EP2INT							Hw2								// W : Clear the EP2 interrupt flag, R : Indicates that the USB EP2 interrupt has been generated
	#define	HwEIR_EP3INT							Hw3								// W : Clear the EP3 interrupt flag, R : Indicates that the USB EP3 interrupt has been generated

#define	HwEIER									*(volatile unsigned long *)0xF0010008	// R/W, Endpoint Interrupt Enable Register
	#define	HwEIER_EP0INT_EN						Hw0								// Enable EP0 interrupt
	#define	HwEIER_EP0INT_DIS						~Hw0							// Disable EP0 interrupt
	#define	HwEIER_EP1INT_EN						Hw1								// Enable EP1 interrupt
	#define	HwEIER_EP1INT_DIS						~Hw1							// Disable EP1 interrupt
	#define	HwEIER_EP2INT_EN						Hw2								// Enable EP2 interrupt
	#define	HwEIER_EP2INT_DIS						~Hw2							// Disable EP2 interrupt
	#define	HwEIER_EP3INT_EN						Hw3								// Enable EP3 interrupt
	#define	HwEIER_EP3INT_DIS						~Hw3							// Disable EP3 interrupt

#define	HwFAR									*(volatile unsigned long *)0xF001000C	// Function Address Register

#define	HwFNR									*(volatile unsigned long *)0xF0010010	// Frame Number Register
	#define	HwFNR_FTL								Hw14							// Frame Timer Lock
	#define	HwFNR_SM								Hw13							// SOF Missing
	#define	HwFNR_FN_MASK							0x7FF							// Frame Number Mask

#define	HwEDR									*(volatile unsigned long *)0xF0010014	// R/W, Endpoint Direction Register
	#define	HwEDR_EP0_TX							Hw0								// Tx Endpoint
	#define	HwEDR_EP0_RX							~Hw0							// Rx Endpoint
	#define	HwEDR_EP1_TX							Hw1								// Tx Endpoint
	#define	HwEDR_EP1_RX							~Hw1							// Rx Endpoint
	#define	HwEDR_EP2_TX							Hw2								// Tx Endpoint
	#define	HwEDR_EP2_RX							~Hw2							// Rx Endpoint
	#define	HwEDR_EP3_TX							Hw3								// Tx Endpoint
	#define	HwEDR_EP3_RX							~Hw3							// Rx Endpoint

#define	HwUTST									*(volatile unsigned long *)0xF0010018	// Test Register
	#define	HwUTST_VBUS_ON							Hw15							//
	#define	HwUTST_VBUS_OFF						~Hw15							//
	#define	HwUTST_EUERR							Hw13							// EB underrun error in transceiver
	#define	HwUTST_PERR							Hw12							// PID Error Flag
	#define	HwUTST_TPS_ON							Hw3								// Transmit test packets
	#define	HwUTST_TPS_OFF							~Hw3							// Stop Transmitting
	#define	HwUTST_TKS_ON							Hw2								// Transmit test K packets
	#define	HwUTST_TKS_OFF							~Hw2							// Stop Transmitting
	#define	HwUTST_TJS_ON							Hw1								// Transmit test J packets
	#define	HwUTST_TJS_OFF							~Hw1							// Stop Transmitting
	#define	HwUTST_TSNS_ON							Hw0								// Transmit test SE0 NAK
	#define	HwUTST_TSNS_OFF						~Hw0							// Stop Transmitting

#define	HwSSR									*(volatile unsigned long *)0xF001001C	// R/W, System Status Register
	#define	HwSSR_BAERR							Hw15							// Byte-Align Error
	#define	HwSSR_TMERR							Hw14							// Timeout Error
	#define	HwSSR_BSERR							Hw13							// Bit Stuff Error
	#define	HwSSR_TCERR							Hw12							// Token CRC Error
	#define	HwSSR_DCERR							Hw11							// Data CRC Error
	#define	HwSSR_EOERR							Hw10							// EB Overrun Error
	#define	HwSSR_VBUS_OFF							Hw9								// VBUS is in Off state.(active when VBUS OFF interrupt is enabled)
	#define	HwSSR_VBUS_ON							Hw8								// VBUS is in ON state.(active when VBUS ON interrupt is enabled)
	#define	HwSSR_TBM								Hw7								// Toggle Bit Mismatch Error
	#define	HwSSR_DP_HIGH							Hw6								// D+ == High State
	#define	HwSSR_DP_LOW							~Hw6							// D+ == Low State
	#define	HwSSR_DN_HIGH							Hw5								// D- == High State
	#define	HwSSR_DN_LOW							~Hw5							// D- == Low State
	#define	HwSSR_HSP_HIGH							Hw4								// Host is High Speed.
	#define	HwSSR_HSP_FULL							~Hw4							// Host is Full Speed.
	#define	HwSSR_SDE_END							Hw3								// Speed Detection is Ended.
	#define	HwSSR_HFRM								Hw2								// Host sends Resume signaling.
	#define	HwSSR_HFSUSP							Hw1								// Host sends Suspend signaling.
	#define	HwSSR_HFRES							Hw0								// Host sends Reset signaling.

#define	HwSCR									*(volatile unsigned long *)0xF0010020	// R/W, System Control Register
	#define	HwSCR_DTZIEN_EN						Hw14							// DMA Total Count Zero Interrupt Enabled
	#define	HwSCR_DTZIEN_DIS						~Hw14							// DMA Total Count Zero Interrupt Disabled
	#define	HwSCR_DIEN_EN							Hw12							// Dual Interrupt Enabled
	#define	HwSCR_DIEN_DIS							~Hw12							// Dual Interrupt Disabled
	#define	HwSCR_VBUSOFF_EN						Hw11							// HwSSR(VBUS OFF flag) Enabled
	#define	HwSCR_VBUSOFF_DIS						~Hw11							// HwSSR(VBUS OFF flag) Disabled
	#define	HwSCR_VBUSON_EN						Hw10							// HwSSR(VBUS ON flag) Enabled
	#define	HwSCR_VBUSON_DIS						~Hw10							// HwSSR(VBUS ON flag) Disabled
	#define	HwSCR_RWDE_EN							Hw9								// High byte data [15:8] is sent first.
	#define	HwSCR_RWDE_DIS						~Hw9							// Low byte data [7:0] is sent first.
	#define	HwSCR_EIE_EN							Hw8								// Error Interrupt Enable
	#define	HwSCR_EIE_DIS							~Hw8							// Error Interrupt Disable
	#define	HwSCR_SDE_EN							Hw6								// Speed Detection End Interrupt Enable
	#define	HwSCR_SDE_DIS							~Hw6							// Speed Detection End Interrupt Disable
	#define	HwSCR_RRDE_EN							Hw5								// First received data is loaded in Low byte [7:0]
	#define	HwSCR_RRDE_DIS							~Hw5							// First received data is loaded in High byte [15:8]
	#define	HwSCR_IPS_HIGH							Hw4								// Active High Interrupt Polarity
	#define	HwSCR_IPS_LOW							~Hw4							// Active Low Interrupt Polarity
	#define	HwSCR_MFRM_ON							Hw2								// USB Core generates Resume signaling.
	#define	HwSCR_MFRM_OFF							~Hw2							// USB Core stop generating Resume signaling.
	#define	HwSCR_HSUSPE_EN						Hw1								// USB Core can repond to the Suspend signaling from HOST.
	#define	HwSCR_HSUSPE_DIS						~Hw1							// USB Core cannot repond to the Suspend signaling from HOST.
	#define	HwSCR_HRESE_EN							Hw0								// USB Core can repond to the Reset signaling from HOST.
	#define	HwSCR_HRESE_DIS						~Hw0							// USB Core cannot repond to the Reset signaling from HOST.

#define	HwEP0SR									*(volatile unsigned long *)0xF0010024	// R/W, EP0 Status Register
	#define	HwEP0SR_LWO							Hw6								// Last Word Odd
	#define	HwEP0SR_SHT							Hw4								// Stall Handshake Transmitted
	#define	HwEP0SR_TST								Hw1								// TX Successfully Transmitted
	#define	HwEP0SR_RSR							Hw0								// RX Successfully Received

#define	HwEP0CR									*(volatile unsigned long *)0xF0010028	// R/W, EP0 Control Register
	#define	HwEP0CR_TTE_EN							Hw3								// TX Test Enable
	#define	HwEP0CR_TTE_DIS						~Hw3							// TX Test Disable
	#define	HwEP0CR_TTS_SET						Hw2								// Set Toggle Bit (active when TTE is set)
	#define	HwEP0CR_TTS_CLR						~Hw2							// Clear Toggle Bit (active when TTE is set)
	#define	HwEP0CR_ESS_SET						Hw1								// Send STALL Handshake to Host
	#define	HwEP0CR_ESS_CLR						~Hw1							// Stop sending STALL Handshake
	#define	HwEP0CR_TZLS_SET						Hw0								// Transmit Zero Length Data (active when TTE is set)
	#define	HwEP0CR_TZLS_CLR						~Hw0							// Stop Transmitting Zero Length Data (active when TTE is set)

#define	HwESR									*(volatile unsigned long *)0xF001002C	// R/W, Endpoint Status Register
	#define	HwESR_FUDR								Hw15							// FIFO Underflow
	#define	HwESR_FOVF								Hw14							// FIFO Overflow
	#define	HwESR_FPID_ON							Hw11							// First OUT packet cannot generate interrupt in OUT DMA operation.
	#define	HwESR_FPID_OFF							~Hw11							// First OUT packet generate interrupt in OUT DMA operation.
	#define	HwESR_OSD								Hw10							// OUT packet is first received after DMA registers are set.
	#define	HwESR_DTCZ								Hw9								// DMA Total Count Zero
	#define	HwESR_SPT								Hw8								// Short Packet Received during OUT DMA operation
	#define	HwESR_DOM								Hw7								// Dual Operation Mode (Max packet = FIFO size / 2)
	#define	HwESR_FFS								Hw6								// FIFO Flushed (Cleared by FLUSH of HwECR register)
	#define	HwESR_FSC								Hw5								// Function Stall Condition is sent to Host.
	#define	HwESR_LWO								Hw4								// Last Word Odd
	#define	HwESR_PSIF_NP							HwZERO							// No Packet in FIFO
	#define	HwESR_PSIF_1P							Hw2								// 1 Packet in FIFO
	#define	HwESR_PSIF_2P							Hw3								// 2 Packets in FIFO
	#define	HwESR_TPS								Hw1								// TX Packet Success
	#define	HwESR_RPS								Hw0								// RX Packet Success

#define	HwECR									*(volatile unsigned long *)0xF0010030	// R/W, Endpoint Control Register
	#define	HwECR_INHLD_EN							Hw12							// In-Packet Hold Enable (USB sends NAK regardless of IN FIFO status)
	#define	HwECR_INHLD_DIS						~Hw12							// In-Packet Hold Disable (USB sends IN data)
	#define	HwECR_OUTHLD_EN						Hw11							// Out-Packet Hold Enable (USB doesn't accept OUT data)
	#define	HwECR_OUTHLD_DIS						~Hw11							// Out-Packet Hold Disable (USB accept OUT data)
	#define	HwECR_TNPMF_1T							Hw9								// 1 Transaction Per MicroFrame
	#define	HwECR_TNPMF_2T							Hw10							// 2 Transactions Per MicroFrame
	#define	HwECR_TNPMF_3T							(Hw10+Hw9)						// 3 Transactions Per MicroFrame
	#define	HwECR_DUEN_EN							Hw7								// Dual FIFO Mode Enable
	#define	HwECR_DUEN_DIS							~Hw7							// Dual FIFO Mode Disable
	#define	HwECR_FLUSH_EN							Hw6								// FIFO is Flushed (automatically cleared after writing)
	#define	HwECR_TTE_EN							Hw5								// TX Toggle Forcing Enable
	#define	HwECR_TTE_DIS							~Hw5							// TX Toggle Forcing Disable
	#define	HwECR_TTS_PID0							HwZERO							// TX Data Toggle bit = PID 0
	#define	HwECR_TTS_PID1							Hw3								// TX Data Toggle bit = PID 1
	#define	HwECR_TTS_PID2							Hw4								// TX Data Toggle bit = PID 2 (ISO only)
	#define	HwECR_TTS_PIDM							(Hw4+Hw3)						// TX Data Toggle bit = PID M (ISO only)
	#define	HwECR_CDP_CLR							Hw2								// Clear Data PID register
	#define	HwECR_ESS_SET							Hw1								// send STALL handshake to Host
	#define	HwECR_ESS_CLR							~Hw1							// stop sending STALL handshake
	#define	HwECR_TZLS_SET							Hw0								// Transmit Zero Length Data (active when TTE is set)
	#define	HwECR_TZLS_CLR							~Hw0							// Stop Transmitting Zero Length Data (active when TTE is set)

#define	HwBRCR									*(volatile unsigned long *)0xF0010034	// R, Byte Read Counter (Half-word unit)

#define	HwBWCR									*(volatile unsigned long *)0xF0010038	// W, Byte Write Counter (Byte unit)

#define	HwMPR									*(volatile unsigned long *)0xF001003C	// R/W, Max Packet Register (Byte unit)

#define	HwDCR									*(volatile unsigned long *)0xF0010040	// R/W, DMA Control Register
	#define	HwDCR_ARDRD_ON						Hw5								// Auto RX DMA Run Disable On
	#define	HwDCR_ARDRD_OFF						~Hw5							// Auto RX DMA Run Disable Off
	#define	HwDCR_FMDE_EN							Hw4								// Fly Mode DMA Enable
	#define	HwDCR_FMDE_DIS							~Hw4							// Fly Mode DMA Disable
	#define	HwDCR_DMDE_EN							Hw3								// Demand Mode DMA Enable
	#define	HwDCR_DMDE_DIS						~Hw3							// Demand Mode DMA Disable
	#define	HwDCR_TDR_RUN							Hw2								// TX DMA Run
	#define	HwDCR_TDR_STOP						~Hw2							// TX DMA Stop
	#define	HwDCR_RDR_RUN							Hw1								// RX DMA Run
	#define	HwDCR_RDR_STOP						~Hw1							// RX DMA Stop
	#define	HwDCR_DEN_EN							Hw0								// DMA Enable
	#define	HwDCR_DEN_DIS							~Hw0							// DMA Disable

#define	HwDTCR									*(volatile unsigned long *)0xF0010044	// DMA Transfer Counter Register (Byte unit)

#define	HwDFCR									*(volatile unsigned long *)0xF0010048	// DMA FIFO Counter Register (Byte unit)

#define	HwDTTCR1								*(volatile unsigned long *)0xF001004C	// Lower-Half of DMA Total Transfer Counter Register

#define	HwDTTCR2								*(volatile unsigned long *)0xF0010050	// Upper-Half of DMA Total Transfer Counter Register

#define	HwEP0BUF								*(volatile unsigned long *)0xF0010060	// EP0 Buffer Register

#define	HwEP1BUF								*(volatile unsigned long *)0xF0010064	// EP1 Buffer Register

#define	HwEP2BUF								*(volatile unsigned long *)0xF0010068	// EP2 Buffer Register

#define	HwEP3BUF								*(volatile unsigned long *)0xF001006C	// EP3 Buffer Register

#define	HwPLICR									*(volatile unsigned long *)0xF00100A0	// PHYLINK Interface Control Register

#define	HwPCR									*(volatile unsigned long *)0xF00100A4	// PHY Control Register
	#define	HwPCR_URST_EN							Hw7								// uTMI_RESET enable
	#define	HwPCR_URST_DIS							~Hw7							// UTMI_RESET disable
	#define	HwPCR_SIDC_1							Hw6								// SIDDQ Control ; SIDDQ = 1
	#define	HwPCR_SIDC_0							~Hw6							// SIDDQ Control ; SIDDQ = 0
	#define	HwPCR_OPMC_RESET						((~Hw5)&(~Hw4))					// OPMODE Control ; reset, reserved
	#define	HwPCR_OPMC_DIS							Hw4								// OPMODE Control ; Disable bit stuffing and NRZI encoding
	#define	HwPCR_OPMC_ND							Hw5								// OPMODE Control ; Non-Driving
	#define	HwPCR_OPMC_NORMAL						(Hw5+Hw4)						// OPMODE Control ; Normal
	#define	HwPCR_TMSC_1							Hw3								// TERMSEL Control ; TERMSEL = 1
	#define	HwPCR_TMSC_0							~Hw3							// TERMSEL Control ; TERMSEL = 0
	#define	HwPCR_XCRC_1							Hw2								// XCVRSEL = 1
	#define	HwPCR_XCRC_0							~Hw2							// XCVRSEL = 0
	#define	HwPCR_SUSPC_1							Hw1								// SUSPENDM = 1
	#define	HwPCR_SUSPC_0							~Hw1							// SUSPENDM = 0
	#define	HwPCR_PCE_EN							Hw0								// Control Enable
	#define	HwPCR_PCE_DIS							~Hw0							// Control Disable

#define	HwUPCFG0								*(volatile unsigned long *)0xF00100C8	// USB PHY Configuration Register 0
	#define	HwUPCFG0_PR_EN							Hw14							// Rer-Port Reset Enable
	#define	HwUPCFG0_PR_DIS						~Hw14							// Rer-Port Reset Disable
	#define	HwUPCFG0_CM_EN							Hw13							// Common Block Power Down Enable
	#define	HwUPCFG0_CM_DIS						~Hw13							// Common Block Power Down Disable
	#define	HwUPCFG0_RCS_11						(Hw12+Hw11)						// Reference Clock Select for PLL Block ; The PLL uses CLKCORE as reference
	#define	HwUPCFG0_RCS_10						Hw12							// Reference Clock Select for PLL Block ; The PLL uses CLKCORE as reference
	#define	HwUPCFG0_RCS_01						Hw11							// Reference Clock Select for PLL Block ; The XO block uses an external clock supplied on the XO pin
	#define	HwUPCFG0_RCS_00						((~Hw12)&(~Hw11))				// Reference Clock Select for PLL Block ; The XO block uses the clock from a crystal
	#define	HwUPCFG0_RCD_48						Hw10							// Reference Clock Frequency Select ; 48MHz
	#define	HwUPCFG0_RCD_24						Hw9								// Reference Clock Frequency Select ; 24MHz
	#define	HwUPCFG0_RCD_12						((~Hw10)&(~Hw9))					// Reference Clock Frequency Select ; 12MHz
	#define	HwUPCFG0_SDI_EN						Hw8								// IDDQ Test Enable ; The analog blocks are powered down
	#define	HwUPCFG0_SDI_DIS						~Hw8							// IDDQ Test Disable ; The analog blocks are not powered down
	#define	HwUPCFG0_FO_SI							Hw7								// UTMI/Serial Interface Select ; Serial Interface
	#define	HwUPCFG0_FO_UTMI						~Hw7							// UTMI/Serial Interface Select ; UTMI

#define	HwUPCFG1								*(volatile unsigned long *)0xF00100CC	// USB PHY Configuration Register 1

#define	HwUPCFG2								*(volatile unsigned long *)0xF00100D0	// USB PHY Configuration Register 2

#define	HwUPCFG3								*(volatile unsigned long *)0xF00100D4	// USB PHY Configuration Register 3

//#define	HwDLYCTRL								*(volatile unsigned long *)0xF0010080	// Delay Control Register

//#define	HwDMAR1								*(volatile unsigned long *)0xF00100A0	// DMA MCU Address Register 1

//#define	HwDMAR2								*(volatile unsigned long *)0xF00100A4	// DMA MCU Address Register 2

//#define	HwDTSR									*(volatile unsigned long *)0xF00100C0	// DMA Transfer Status Register

//#define	HwUBCFG								*(volatile unsigned long *)0xF00100C4	// R/W, USB Configuration Register
	//#define	HwUBCFG_XSEL_FS						Hw13							// FS Transceiver enable
	//#define	HwUBCFG_TERM_FSOS						(Hw12+Hw11)						// Full-speed termination is enabled for FS-only and FS-Serial modes
	//#define	HwUBCFG_TERM_LS						Hw12							// Low-speed signaling is enable for LS-Serial modes
	//#define	HwUBCFG_TERM_FS						Hw11							// Full-speed termination is enabled
	//#define	HwUBCFG_TERM_HS						HwZERO							// High-speed termination is enabled
	//#define	HwUBCFG_FSXO_SERIAL					Hw10							// Serial Interface Select
	//#define	HwUBCFG_DWS_HOST						Hw6								// Host Mode
	//#define	HwUBCFG_XO_EN							Hw5								// XO_OUT output enable
	//#define	HwUBCFG_CKSEL_12						HwZERO							// 12MHz
	//#define	HwUBCFG_CKSEL_24						Hw0								// 24MHz
	//#define	HwUBCFG_CKSEL_48						Hw1								// 48MHz

/************************************************************************
*	USB Host Register Define					(Base Addr = 0xF0020000)
************************************************************************/
#define	HwUSBH_BASE							*(volatile unsigned long *)0xF0020000	// USB Host Base Register

#define	HwHcRevision								*(volatile unsigned long *)0xF0020000	// Control and status register

#define	HwHcControl								*(volatile unsigned long *)0xF0020004	// Control and status register

#define	HwHcCommandStatus						*(volatile unsigned long *)0xF0020008	// Control and status register

#define	HwHcInterruptStatus						*(volatile unsigned long *)0xF002000C	// Control and status register

#define	HwHcInterruptEnable						*(volatile unsigned long *)0xF0020010	// Control and status register

#define	HwHcInterruptDisable						*(volatile unsigned long *)0xF0020014	// Control and status register

#define	HwHcHCCA								*(volatile unsigned long *)0xF0020018	// Memory pointer register

#define	HwHcPeroidCurrentED						*(volatile unsigned long *)0xF002001C	// Memory pointer register

#define	HwHcControlHeadED						*(volatile unsigned long *)0xF0020020	// Memory pointer register

#define	HwHcControlCurrentED						*(volatile unsigned long *)0xF0020024	// Memory pointer register

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
#define	HwIDE_BASE								*(volatile unsigned long *)0xF0030000	// IDE Base Register

#define	HwCS0n									*(volatile unsigned long *)0xF0030000	// R/W, PIO CS0n Access register
#define	HwCS00									0xF0030000						// PIO CS00 Register Address

#define	REG_PTR    								*(volatile unsigned short *)			// get the content of pointer
#define	IDE_BASE_CS0							0xF0030000
#define	HwIDE_RD_DATA							(REG_PTR(IDE_BASE_CS0+(0x00<<2)+ 0x00))
#define	HwIDE_WR_DATA							HwIDE_RD_DATA

#define	HwCS1n									*(volatile unsigned long *)0xF0030020	// R/W, PIO CS1n Access register
#define	HwCS10									0xF0030020						// PIO CS10 Register Address

#define	HwPIOCTRL								*(volatile unsigned long *)0xF0030040	// R/W, PIO Mode control register
	#define	HwPIOCTRL_SYNC_BYPASS					HwZERO							// Bypass
	#define	HwPIOCTRL_SYNC_1						Hw21							// 1 Sync
	#define	HwPIOCTRL_SYNC_2						Hw22							// 2 Sync
	#define	HwPIOCTRL_MD_PIO						HwZERO							// PIO Mode
	#define	HwPIOCTRL_MD_UDMA						Hw20							// UDMA(IN/OUT) Mode
	#define	HwPIOCTRL_RDY_IRR						HwZERO							// PW cycles is irrelative of IORDY
	#define	HwPIOCTRL_RDY_EXT						Hw0								// PW cycles are extended by IORDY

#define	HwUDMACTRL								*(volatile unsigned long *)0xF0030044	// R/W, UDMA Mode control register
	#define	HwUDMACTRL_HTRL4						HwZERO							// 4
	#define	HwUDMACTRL_HTRL8						Hw28							// 8
	#define	HwUDMACTRL_HTRL12						Hw29							// 12
	#define	HwUDMACTRL_HTRL14						(Hw29+Hw28)						// 14
	#define	HwUDMACTRL_OTL1						HwZERO							// Single Transfer (1read/1write)
	#define	HwUDMACTRL_OTL4						Hw25							// 4 (vcnt <= 12)
	#define	HwUDMACTRL_OTL8						Hw26							// 8 (vcnt <= 8)
	#define	HwUDMACTRL_OTL12						(Hw26+Hw25)						// 12 (vcnt <= 4)
	#define	HwUDMACTRL_OTL16						(Hw27+Hw26)						// 16 (Empty)
	#define	HwUDMACTRL_ITL1						HwZERO							// Single Transfer
	#define	HwUDMACTRL_ITL4						Hw23							// 4 (32bit data) (vcnt >= 4)
	#define	HwUDMACTRL_ITL8						Hw24							// 8 (32bit data) (vcnt >= 8)
	#define	HwUDMACTRL_ITL12						(Hw24+Hw23)						// 12 (32bit data) (vcnt >= 12)
	#define	HwUDMACTRL_AHB1						HwZERO							// The hold margin of the data to be transferred has one AHB clock period
	#define	HwUDMACTRL_AHB2						Hw15							// The hold margin of the data to be transferred has two AHB clock period
	#define	HwUDMACTRL_HTB_OFF						HwZERO							//
	#define	HwUDMACTRL_HTB_ON						Hw5								// HOST terminate operation when CTCNT reaches zero.
	#define	HwUDMACTRL_TS16						HwZERO							// 16bit Transfer Mode (in Internal Bus)
	#define	HwUDMACTRL_TS32						Hw4								// 32bit Transfer Mode (in Internal Bus)
	#define	HwUDMACTRL_BS_OFF						HwZERO							//
	#define	HwUDMACTRL_BS_ON						Hw3								// BUS Share Mode
	#define	HwUDMACTRL_HT_OFF						HwZERO							//
	#define	HwUDMACTRL_HT_ON						Hw2								// HOST Termination
	#define	HwUDMACTRL_UIO_IN						HwZERO							// UDMA-IN Mode
	#define	HwUDMACTRL_UIO_OUT					Hw1								// UDMA-OUT Mode
	#define	HwUDMACTRL_UEN_OFF						HwZERO							//
	#define	HwUDMACTRL_UEN_ON						Hw0								// UDMA Enable Bit

#define	HwIDMACTRL								*(volatile unsigned long *)0xF0030048	// R/W, IDMA control register
	#define	HwIDMACTRL_ARB_OFF						HwZERO							//
	#define	HwIDMACTRL_ARB_ON						Hw4								// IDMA transfer executed with arbitration transfer
	#define	HwIDMACTRL_LOC_OFF						HwZERO							//
	#define	HwIDMACTRL_LOC_ON						Hw3								// DMA transfer executed with lock transfer
	#define	HwIDMACTRL_CON							HwZERO							// DMA transfer begins from CSAR/CDAR address
	#define	HwIDMACTRL_CON_MEAN					Hw2								// DMA transfer begins from CSAR/CDAR address, It must be used after the former transfer has been executed, so that CSAR and CDAR contaion a meaningful value
	#define	HwIDMACTRL_REP_AUTODIS				HwZERO							// When UDMA operation end, IDE bit is automatically disabled
	#define	HwIDMACTRL_REP_NOTDIS					Hw1								// When UDMA operation end, IDE bit is not disabled
	#define	HwIDMACTRL_IDE_OFF						HwZERO							//
	#define	HwIDMACTRL_IDE_ON						Hw0								// Internal DMA(IDMA) enable bit

#define	HwIDMASA								*(volatile unsigned long *)0xF003004C	// R/W, IDMA source address register

#define	HwIDMASP								*(volatile unsigned long *)0xF0030050	// R/W, IDMA source parameter register

#define	HwIDMACSA								*(volatile unsigned long *)0xF0030054	// R, IDMA current source address register

#define	HwIDMADA								*(volatile unsigned long *)0xF0030058	// R/W, destination address IDMA register

#define	HwIDMADP								*(volatile unsigned long *)0xF003005C	// R/W, destination parameter IDMA register

#define	HwIDMACDA								*(volatile unsigned long *)0xF0030060	// R, current destination address IDMA register

#define	HwIDEINT								*(volatile unsigned long *)0xF0030064	// R/W, IDE interrupt register
	#define	HwIDEINT_UB								Hw31							// UDMA is Busy(1), State of UDMA is IDLE(0)
	#define	HwIDEINT_NWA_ON						HwZERO							// Word(32bit) aligned
	#define	HwIDEINT_NWA_OFF						Hw30							// Not Word(32bit) aligned
	#define	HwIDEINT_DT_OFF							HwZERO							// Device did not terminate operation
	#define	HwIDEINT_DT_ON							Hw29							// Device terminated operation
	#define	HwIDEINT_URS_AUTOCLR					HwZERO							// UDMA request from the device is not active or automatically clear
	#define	HwIDEINT_URS_ACTIVE					Hw11							// UDMA request from the device is active
	#define	HwIDEINT_FES_GOOD						HwZERO							// Not FIFO Error
	#define	HwIDEINT_FES_ERROR						Hw10							// FIFO Error
	#define	HwIDEINT_TRS_AUTOCLR					HwZERO							// Trigger level request is not active or automatically clear
	#define	HwIDEINT_TRS_ACTIVE						Hw9								// Trigger level request is active
	#define	HwIDEINT_OPE_OFF						HwZERO							// Host or Device dose not terminate operation yet
	#define	HwIDEINT_OPE_ON						Hw8								// Host or Device terminate operation
	#define	HwIDEINT_URE_DIS						HwZERO							// UDMA request interrupt is disabled
	#define	HwIDEINT_URE_EN							Hw3								// UDMA request interrupt is enabled
	#define	HwIDEINT_FEE_DIS						HwZERO							// FIFO Error interrupt is disabled
	#define	HwIDEINT_FEE_EN							Hw2								// FIFO Error interrupt is enabled
	#define	HwIDEINT_TRE_DIS						HwZERO							// Trigger level interrupt is disabled
	#define	HwIDEINT_TRE_EN							Hw1								// Trigger level interrupt is enabled

#define	HwUDMATCNT								*(volatile unsigned long *)0xF0030068	// R/W, UDMA transfer counter register

#define	HwUDMAIN								*(volatile unsigned long *)0xF003006C	// R, UDMA-IN access register

#define	HwUDMAOUT								*(volatile unsigned long *)0xF0030070	// W, UDMA-OUT access register

#define	HwUDMACRC								*(volatile unsigned long *)0xF0030074	// R, UDMA CRC register

#define	HwUDMACTCNT							*(volatile unsigned long *)0xF0030078	// R, UDMA status register

/***********************************************************************
*	DMA Controller Register Define				(Base Addr = 0xF0040000)
************************************************************************/
//GDMA 0 - channel 0
#define	HwDMA_BASECH0						*(volatile unsigned long *)0xF0040000	// DMA Base Register
#define	HwST_SADR0							*(volatile unsigned long *)0xF0040000	// R/W, Start Address of Source Block Register
#define	HwSPARAM0								*(volatile unsigned long *)0xF0040004	// R/W, Parameter of Source Block Register
#define	HwC_SADR0								*(volatile unsigned long *)0xF004000C	// R, Current Address of Source Block Register
#define	HwST_DADR0							*(volatile unsigned long *)0xF0040010	// R/W, Start Address of Destination Block Register
#define	HwDPARAM0								*(volatile unsigned long *)0xF0040014	// R/W, Parameter of Destination Block Register
#define	HwC_DADR0								*(volatile unsigned long *)0xF004001C	// R, Current Address of Destination Block Register
#define	HwHCOUNT0								*(volatile unsigned long *)0xF0040020	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL0								*(volatile unsigned long *)0xF0040024	// R/W, Channel Control Register
#define	HwRPTCTRL0							*(volatile unsigned long *)0xF0040028	// R/W, Repeat Control Register
#define	HwEXTREQ0								*(volatile unsigned long *)0xF004002C	// R/W, External DMA Request Register
//GDMA 0 - channel 1
#define	HwDMA_BASECH1						*(volatile unsigned long *)0xF0040030	// DMA Base Register
#define	HwST_SADR1							*(volatile unsigned long *)0xF0040030	// R/W, Start Address of Source Block Register
#define	HwSPARAM1 							*(volatile unsigned long *)0xF0040034	// R/W, Parameter of Source Block Register
#define	HwC_SADR1								*(volatile unsigned long *)0xF004003C	// R, Current Address of Source Block Register
#define	HwST_DADR1							*(volatile unsigned long *)0xF0040040	// R/W, Start Address of Destination Block Register
#define	HwDPARAM1								*(volatile unsigned long *)0xF0040044	// R/W, Parameter of Destination Block Register
#define	HwC_DADR1								*(volatile unsigned long *)0xF004004C	// R, Current Address of Destination Block Register
#define	HwHCOUNT1								*(volatile unsigned long *)0xF0040050	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL1								*(volatile unsigned long *)0xF0040054	// R/W, Channel Control Register
#define	HwRPTCTRL1							*(volatile unsigned long *)0xF0040058	// R/W, Repeat Control Register
#define	HwEXTREQ1								*(volatile unsigned long *)0xF004005C	// R/W, External DMA Request Register
//GDMA 0 - channel 2
#define	HwDMA_BASECH2						*(volatile unsigned long *)0xF0040060	// DMA Base Register
#define	HwST_SADR2							*(volatile unsigned long *)0xF0040060	// R/W, Start Address of Source Block Register
#define	HwSPARAM2								*(volatile unsigned long *)0xF0040064	// R/W, Parameter of Source Block Register
#define	HwC_SADR2								*(volatile unsigned long *)0xF004006C	// R, Current Address of Source Block Register
#define	HwST_DADR2							*(volatile unsigned long *)0xF0040070	// R/W, Start Address of Destination Block Register
#define	HwDPARAM2								*(volatile unsigned long *)0xF0040074	// R/W, Parameter of Destination Block Register
#define	HwC_DADR2								*(volatile unsigned long *)0xF004007C	// R, Current Address of Destination Block Register
#define	HwHCOUNT2								*(volatile unsigned long *)0xF0040080	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL2								*(volatile unsigned long *)0xF0040084	// R/W, Channel Control Register
#define	HwRPTCTRL2							*(volatile unsigned long *)0xF0040088	// R/W, Repeat Control Register
#define	HwEXTREQ2								*(volatile unsigned long *)0xF004008C	// R/W, External DMA Request Register
//GDMA 1 - channel 0
#define	HwDMA_BASECH3						*(volatile unsigned long *)0xF0040100	// DMA Base Register
#define	HwST_SADR3							*(volatile unsigned long *)0xF0040100	// R/W, Start Address of Source Block Register
#define	HwSPARAM3								*(volatile unsigned long *)0xF0040104	// R/W, Parameter of Source Block Register
#define	HwC_SADR3								*(volatile unsigned long *)0xF004010C	// R, Current Address of Source Block Register
#define	HwST_DADR3							*(volatile unsigned long *)0xF0040110	// R/W, Start Address of Destination Block Register
#define	HwDPARAM3								*(volatile unsigned long *)0xF0040114	// R/W, Parameter of Destination Block Register
#define	HwC_DADR3								*(volatile unsigned long *)0xF004011C	// R, Current Address of Destination Block Register
#define	HwHCOUNT3								*(volatile unsigned long *)0xF0040120	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL3								*(volatile unsigned long *)0xF0040124	// R/W, Channel Control Register
#define	HwRPTCTRL3							*(volatile unsigned long *)0xF0040128	// R/W, Repeat Control Register
#define	HwEXTREQ3								*(volatile unsigned long *)0xF004012C	// R/W, External DMA Request Register
//GDMA 1 - channel 1
#define	HwDMA_BASECH4						*(volatile unsigned long *)0xF0040130	// DMA Base Register
#define	HwST_SADR4							*(volatile unsigned long *)0xF0040130	// R/W, Start Address of Source Block Register
#define	HwSPARAM4								*(volatile unsigned long *)0xF0040134	// R/W, Parameter of Source Block Register
#define	HwC_SADR4								*(volatile unsigned long *)0xF004013C	// R, Current Address of Source Block Register
#define	HwST_DADR4							*(volatile unsigned long *)0xF0040140	// R/W, Start Address of Destination Block Register
#define	HwDPARAM4								*(volatile unsigned long *)0xF0040144	// R/W, Parameter of Destination Block Register
#define	HwC_DADR4								*(volatile unsigned long *)0xF004014C	// R, Current Address of Destination Block Register
#define	HwHCOUNT4								*(volatile unsigned long *)0xF0040150	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL4								*(volatile unsigned long *)0xF0040154	// R/W, Channel Control Register
#define	HwRPTCTRL4							*(volatile unsigned long *)0xF0040158	// R/W, Repeat Control Register
#define	HwEXTREQ4								*(volatile unsigned long *)0xF004015C	// R/W, External DMA Request Register
//GDMA 1 - channel 2                                                 
#define	HwDMA_BASECH5						*(volatile unsigned long *)0xF0040160	// DMA Base Register
#define	HwST_SADR5							*(volatile unsigned long *)0xF0040160	// R/W, Start Address of Source Block Register
#define	HwSPARAM5								*(volatile unsigned long *)0xF0040164	// R/W, Parameter of Source Block Register
#define	HwC_SADR5								*(volatile unsigned long *)0xF004016C	// R, Current Address of Source Block Register
#define	HwST_DADR5							*(volatile unsigned long *)0xF0040170	// R/W, Start Address of Destination Block Register
#define	HwDPARAM5								*(volatile unsigned long *)0xF0040174	// R/W, Parameter of Destination Block Register
#define	HwC_DADR5								*(volatile unsigned long *)0xF004017C	// R, Current Address of Destination Block Register
#define	HwHCOUNT5								*(volatile unsigned long *)0xF0040180	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL5								*(volatile unsigned long *)0xF0040184	// R/W, Channel Control Register
#define	HwRPTCTRL5							*(volatile unsigned long *)0xF0040188	// R/W, Repeat Control Register
#define	HwEXTREQ5								*(volatile unsigned long *)0xF004018C	// R/W, External DMA Request Register
//GDMA 2 - channel 0
#define	HwDMA_BASECH6						*(volatile unsigned long *)0xF0040200	// DMA Base Register
#define	HwST_SADR6							*(volatile unsigned long *)0xF0040200	// R/W, Start Address of Source Block Register
#define	HwSPARAM6 							*(volatile unsigned long *)0xF0040204	// R/W, Parameter of Source Block Register
#define	HwC_SADR6								*(volatile unsigned long *)0xF004020C	// R, Current Address of Source Block Register
#define	HwST_DADR6							*(volatile unsigned long *)0xF0040210	// R/W, Start Address of Destination Block Register
#define	HwDPARAM6								*(volatile unsigned long *)0xF0040214	// R/W, Parameter of Destination Block Register
#define	HwC_DADR6								*(volatile unsigned long *)0xF004021C	// R, Current Address of Destination Block Register
#define	HwHCOUNT6								*(volatile unsigned long *)0xF0040220	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL6								*(volatile unsigned long *)0xF0040224	// R/W, Channel Control Register
#define	HwRPTCTRL6							*(volatile unsigned long *)0xF0040228	// R/W, Repeat Control Register
#define	HwEXTREQ6								*(volatile unsigned long *)0xF004022C	// R/W, External DMA Request Register
//GDMA 2 - channel 1                                                 
#define	HwDMA_BASECH7						*(volatile unsigned long *)0xF0040230	// DMA Base Register
#define	HwST_SADR7							*(volatile unsigned long *)0xF0040230	// R/W, Start Address of Source Block Register
#define	HwSPARAM7								*(volatile unsigned long *)0xF0040234	// R/W, Parameter of Source Block Register
#define	HwC_SADR7								*(volatile unsigned long *)0xF004023C	// R, Current Address of Source Block Register
#define	HwST_DADR7							*(volatile unsigned long *)0xF0040240	// R/W, Start Address of Destination Block Register
#define	HwDPARAM7								*(volatile unsigned long *)0xF0040244	// R/W, Parameter of Destination Block Register
#define	HwC_DADR7								*(volatile unsigned long *)0xF004024C	// R, Current Address of Destination Block Register
#define	HwHCOUNT7								*(volatile unsigned long *)0xF0040250	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL7								*(volatile unsigned long *)0xF0040254	// R/W, Channel Control Register
#define	HwRPTCTRL7							*(volatile unsigned long *)0xF0040258	// R/W, Repeat Control Register
#define	HwEXTREQ7								*(volatile unsigned long *)0xF004025C	// R/W, External DMA Request Register
//GDMA 2 - channel 2                                                 
#define	HwDMA_BASECH8						*(volatile unsigned long *)0xF0040260	// DMA Base Register
#define	HwST_SADR8							*(volatile unsigned long *)0xF0040260	// R/W, Start Address of Source Block Register
#define	HwSPARAM8								*(volatile unsigned long *)0xF0040264	// R/W, Parameter of Source Block Register
#define	HwC_SADR8								*(volatile unsigned long *)0xF004026C	// R, Current Address of Source Block Register
#define	HwST_DADR8							*(volatile unsigned long *)0xF0040270	// R/W, Start Address of Destination Block Register
#define	HwDPARAM8								*(volatile unsigned long *)0xF0040274	// R/W, Parameter of Destination Block Register
#define	HwC_DADR8								*(volatile unsigned long *)0xF004027C	// R, Current Address of Destination Block Register
#define	HwHCOUNT8								*(volatile unsigned long *)0xF0040280	// R/W, Initial and Current Hop Count Register
#define	HwCHCTRL8								*(volatile unsigned long *)0xF0040284	// R/W, Channel Control Register
#define	HwRPTCTRL8							*(volatile unsigned long *)0xF0040288	// R/W, Repeat Control Register
#define	HwEXTREQ8								*(volatile unsigned long *)0xF004028C	// R/W, External DMA Request Register
	#define	HwCHCTRL_CONT_C						Hw15							// DMA transfer begins from C_SADR / C_DADR address. It must be used after the former transfer has been executed, so that C_SADR and C_DADR contain a meaningful vlaue
	#define	HwCHCTRL_DTM_EN						Hw14							// Differential Transfer Mode Enabled
																					//    (for WSIZE=2, BSIZE=3 32bit to 16bit transfer : 4 Read / 8 Write)
																					//    (for WSIZE=3, BSIZE=3 16bit to 32bit transfer : 8 Read / 4 Write)
	#define	HwCHCTRL_SYNC_EN						Hw13							// Synchronize Hardware Request
	#define	HwCHCTRL_HRD_W						Hw12							// ACK/EOT signals are issued When DMA-Write Operation
	#define	HwCHCTRL_LOCK_EN						Hw11							// DMA transfer executed with lock transfer
	#define	HwCHCTRL_BST_NOARB					Hw10							// DMA transfer executed with no arbitration(burst operation)
	#define	HwCHCTRL_TYPE_SE						HwZERO							// SINGLE transfer with edge-triggered detection
	#define	HwCHCTRL_TYPE_SL						(Hw9+Hw8)						// SINGLE transfer with level-triggered detection
	#define	HwCHCTRL_TYPE_HW						Hw8								// HW transfer
	#define	HwCHCTRL_TYPE_SW						Hw9								// SW transfer
	#define	HwCHCTRL_BSIZE_1						HwZERO							// 1 Burst transfer consists of 1 read or write cycle
	#define	HwCHCTRL_BSIZE_2						Hw6								// 1 Burst transfer consists of 2 read or write cycle
	#define	HwCHCTRL_BSIZE_4						Hw7								// 1 Burst transfer consists of 4 read or write cycle
	#define	HwCHCTRL_BSIZE_8						(Hw7+Hw6)						// 1 Burst transfer consists of 8 read or write cycle
	#define	HwCHCTRL_WSIZE_8						HwZERO							// Each cycle read or write 8bit data
	#define	HwCHCTRL_WSIZE_16						Hw4								// Each cycle read or write 16bit data
	#define	HwCHCTRL_WSIZE_32						Hw5								// Each cycle read or write 32bit data
	#define	HwCHCTRL_FLAG							Hw3								// W : Clears FLAG to 0, R : Represents that all hop of transfer are fulfilled
	#define	HwCHCTRL_IEN_EN						Hw2								// At the same time the FLAG goes to 1, DMA interrupt request is generated
	#define	HwCHCTRL_REP_EN						Hw1								// The DMA channel remains enabled. When another DMA request has occurred, the DMA channel start transfer data again with the same manner(type,address,increment,mask) as the latest transfer of that channel
	#define	HwCHCTRL_EN_EN						Hw0								// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request


	#define	HwRPTCTRL_DRI_LAST					Hw31							// DAM interrupt occur is  occurred at the last DMA Repeated DMA operation
	#define	HwRPTCTRL_DEOT_LAST					Hw30							// EOT signal is occurred at the last Repeated DAM operation in HW(including Single) transfer Mode


	#define	HwEXTREQ_UART1_RX						Hw30							// Connected Hardware = UART Channel 1 Receiver
	#define	HwEXTREQ_UART1_TX						Hw29							// Connected Hardware = UART Channel 1 Tranceiver
	#define	HwEXTREQ_UART0_RX						Hw27							// Connected Hardware = UART Channel 0 Receiver
	#define	HwEXTREQ_UART0_TX						Hw26							// Connected Hardware = UART Channel 0 Tranceiver
	#define	HwEXTREQ_I2C_CH1						Hw25							// Connected Hardware = I2C Controller Channel 1
	#define	HwEXTREQ_DAIR							Hw24							// Connected Hardware = DAI Receiver
	#define	HwEXTREQ_DAIT							Hw23							// Connected Hardware = DAI Transmitter
	#define	HwEXTREQ_CDIF							Hw22							// Connected Hardware = CD I/F
	#define	HwEXTREQ_SPDIF_UDATA					Hw21							// Connected Hardware = SPDIF User Data
	#define	HwEXTREQ_SPDIF_PDATA					Hw20							// Connected Hardware = SPDIF Packet(Audio) Data
	#define	HwEXTREQ_I2C_CH0						Hw19							// Connected Hardware = I2C Controller Channel 0
	#define	HwEXTREQ_NFC							Hw18							// Connected Hardware = NAND Flash Controller
	#define	HwEXTREQ_MSTICK						Hw17							// Connected Hardware = Memory Stick
	#define	HwEXTREQ_ECC							Hw12							// Connected Hardware = ECC
	#define	HwEXTREQ_UART3_RX						Hw11							// Connected Hardware = UART Channel 3 Receiver
	#define	HwEXTREQ_UART3_TX						Hw10							// Connected Hardware = UART Channel 3 Tranceiver
	#define	HwEXTREQ_UART2_RX						Hw9								// Connected Hardware = UART Channel 2 Receiver
	#define	HwEXTREQ_UART2_TX						Hw8								// Connected Hardware = UART Channel 2 Tranceiver
	#define	HwEXTREQ_GPSB3_RX						Hw7								// Connected Hardware = GPSB Channel 3 Receiver
	#define	HwEXTREQ_GPSB2_RX						Hw6								// Connected Hardware = GPSB Channel 2 Receiver
	#define	HwEXTREQ_GPSB1_RX						Hw5								// Connected Hardware = GPSB Channel 1 Receiver
	#define	HwEXTREQ_GPSB0_RX						Hw4								// Connected Hardware = GPSB Channel 0 Receiver
	#define	HwEXTREQ_GPSB3_TX						Hw3								// Connected Hardware = GPSB Channel 3 Tranceiver
	#define	HwEXTREQ_GPSB2_TX						Hw2								// Connected Hardware = GPSB Channel 2 Tranceiver
	#define	HwEXTREQ_GPSB1_TX						Hw1								// Connected Hardware = GPSB Channel 1 Tranceiver
	#define	HwEXTREQ_GPSB0_TX						Hw0								// Connected Hardware = GPSB Channel 0 Tranceiver

#define	HwCHCONFIG0							*(volatile unsigned long *)0xF0040090	// R/W, External DMA Request Register
#define	HwCHCONFIG1							*(volatile unsigned long *)0xF0040190	// R/W, External DMA Request Register
#define	HwCHCONFIG2							*(volatile unsigned long *)0xF0040290	// R/W, External DMA Request Register

typedef	volatile struct
{
	unsigned	ST_SADR;	// 0x00
	unsigned	SPARAM;		// 0x04
	unsigned	_SPARAM;	// 0x08
	unsigned	C_SADR;		// 0x0C

	unsigned	ST_DADR;	// 0x10
	unsigned	DPARAM;		// 0x14
	unsigned	_DPARAM;	// 0x18
	unsigned	C_DADR;		// 0x1C

	unsigned	HCOUNT;		// 0x20
	unsigned	CHCTRL;		// 0x24
	unsigned	RPTCTRL;	// 0x28
	unsigned	EXTREQ;		// 0x2C
} sHwDMA;

	#define	HwCHCTRL_CONT_C						Hw15							// DMA transfer begins from C_SADR / C_DADR address. It must be used after the former transfer has been executed, so that C_SADR and C_DADR contain a meaningful vlaue
	#define	HwCHCTRL_DTM_EN						Hw14							// Differential Transfer Mode Enabled
																					//    (for WSIZE=2, BSIZE=3 32bit to 16bit transfer : 4 Read / 8 Write)
																					//    (for WSIZE=3, BSIZE=3 16bit to 32bit transfer : 8 Read / 4 Write)
	#define	HwCHCTRL_SYNC_EN						Hw13							// Synchronize Hardware Request
	#define	HwCHCTRL_HRD_W						Hw12							// ACK/EOT signals are issued When DMA-Write Operation
	#define	HwCHCTRL_HRD_RD						HwZERO							// ACK/EOT signals are issued When DMA-Read Operation
	#define	HwCHCTRL_LOCK_EN						Hw11							// DMA transfer executed with lock transfer
	#define	HwCHCTRL_LOCK_ON						Hw11							// DMA transfer executed with lock transfer
	#define	HwCHCTRL_BST_NOARB					Hw10							// DMA transfer executed with no arbitration(burst operation)
	#define	HwCHCTRL_BST_BURST					Hw10							// DMA transfer executed with no arbitration(burst operation)
	#define	HwCHCTRL_BST_ARB						HwZERO							// DMA transfer executed with arbitration(burst operation)
	#define	HwCHCTRL_TYPE_SE						HwZERO							// SINGLE transfer with edge-triggered detection
	#define	HwCHCTRL_TYPE_SL						(Hw9+Hw8)						// SINGLE transfer with level-triggered detection
	#define	HwCHCTRL_TYPE_SINGL					(Hw9+Hw8)						// SINGLE transfer with level-triggered detection
	#define	HwCHCTRL_TYPE_HW						Hw8								// HW transfer
	#define	HwCHCTRL_TYPE_SW						Hw9								// SW transfer
	#define	HwCHCTRL_BSIZE(X)						((X)*Hw6)
//	#define	HwCHCTRL_BSIZE_1						HwCHCTRL_BSIZE(0)				// 1 Burst transfer consists of 1 read or write cycle
//	#define	HwCHCTRL_BSIZE_2						HwCHCTRL_BSIZE(1)				// 1 Burst transfer consists of 2 read or write cycle
//	#define	HwCHCTRL_BSIZE_4						HwCHCTRL_BSIZE(2)				// 1 Burst transfer consists of 4 read or write cycle
//	#define	HwCHCTRL_BSIZE_8						HwCHCTRL_BSIZE(3)				// 1 Burst transfer consists of 8 read or write cycle
//	#define	HwCHCTRL_BSIZE_MASK					HwCHCTRL_BSIZE(3)
	#define	HwCHCTRL_WSIZE(X)						((X)*Hw4)
//	#define	HwCHCTRL_WSIZE_8						HwCHCTRL_WSIZE(0)				// Each cycle read or write 8bit data
//	#define	HwCHCTRL_WSIZE_16						HwCHCTRL_WSIZE(1)				// Each cycle read or write 16bit data
//	#define	HwCHCTRL_WSIZE_32						HwCHCTRL_WSIZE(2)				// Each cycle read or write 32bit data
//	#define	HwCHCTRL_WSIZE_MASK					HwCHCTRL_WSIZE(3)
	#define	HwCHCTRL_FLAG							Hw3								// W : Clears FLAG to 0, R : Represents that all hop of transfer are fulfilled
	#define	HwCHCTRL_IEN_EN						Hw2								// At the same time the FLAG goes to 1, DMA interrupt request is generated
	#define	HwCHCTRL_IEN_ON						Hw2								// At the same time the FLAG goes to 1, DMA interrupt request is generated
	#define	HwCHCTRL_REP_EN						Hw1								// The DMA channel remains enabled. When another DMA request has occurred, the DMA channel start transfer data again with the same manner(type,address,increment,mask) as the latest transfer of that channel
	#define	HwCHCTRL_EN_EN							Hw0								// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request
	#define	HwCHCTRL_EN_ON							Hw0								// DMA channel is enabled. If software type transfer is selected, this bit generates DMA request directly, or if hardware type transfer is used, the selected interrupt request flag generate DMA request

	#define	HwEXTREQ_UART1_RX						Hw30							// Connected Hardware = UART Channel 1 Receiver
	#define	HwEXTREQ_UART1_TX						Hw29							// Connected Hardware = UART Channel 1 Tranceiver
	#define	HwEXTREQ_UART0_RX						Hw27							// Connected Hardware = UART Channel 0 Receiver
	#define	HwEXTREQ_UART0_TX						Hw26							// Connected Hardware = UART Channel 0 Tranceiver
	#define	HwEXTREQ_I2C_CH1						Hw25							// Connected Hardware = I2C Controller Channel 1
	#define	HwEXTREQ_DAIR							Hw24							// Connected Hardware = DAI Receiver
	#define	HwEXTREQ_DAIT							Hw23							// Connected Hardware = DAI Transmitter
	#define	HwEXTREQ_CDIF							Hw22							// Connected Hardware = CD I/F
	#define	HwEXTREQ_SPDIF_UDATA					Hw21							// Connected Hardware = SPDIF User Data
	#define	HwEXTREQ_SPDIF_PDATA					Hw20							// Connected Hardware = SPDIF Packet(Audio) Data
	#define	HwEXTREQ_I2C_CH0						Hw19							// Connected Hardware = I2C Controller Channel 0
	#define	HwEXTREQ_NFC							Hw18							// Connected Hardware = NAND Flash Controller
	#define	HwEXTREQ_MSTICK						Hw17							// Connected Hardware = Memory Stick
	#define	HwEXTREQ_ECC							Hw12							// Connected Hardware = ECC
	#define	HwEXTREQ_UART3_RX						Hw11							// Connected Hardware = UART Channel 3 Receiver
	#define	HwEXTREQ_UART3_TX						Hw10							// Connected Hardware = UART Channel 3 Tranceiver
	#define	HwEXTREQ_UART2_RX						Hw9								// Connected Hardware = UART Channel 2 Receiver
	#define	HwEXTREQ_UART2_TX						Hw8								// Connected Hardware = UART Channel 2 Tranceiver
	#define	HwEXTREQ_GPSB3_RX						Hw7								// Connected Hardware = GPSB Channel 3 Receiver
	#define	HwEXTREQ_GPSB2_RX						Hw6								// Connected Hardware = GPSB Channel 2 Receiver
	#define	HwEXTREQ_GPSB1_RX						Hw5								// Connected Hardware = GPSB Channel 1 Receiver
	#define	HwEXTREQ_GPSB0_RX						Hw4								// Connected Hardware = GPSB Channel 0 Receiver
	#define	HwEXTREQ_GPSB3_TX						Hw3								// Connected Hardware = GPSB Channel 3 Tranceiver
	#define	HwEXTREQ_GPSB2_TX						Hw2								// Connected Hardware = GPSB Channel 2 Tranceiver
	#define	HwEXTREQ_GPSB1_TX						Hw1								// Connected Hardware = GPSB Channel 1 Tranceiver
	#define	HwEXTREQ_GPSB0_TX						Hw0								// Connected Hardware = GPSB Channel 0 Tranceiver

#define	HwGDMA_BASE(X)							*(volatile unsigned long *)(0xF0040000 + (X)*0x100)

#define	HwGDMA_CH_BASE(X)						*(volatile unsigned long *)(0xF0040000 + ((X)*0x100/0x300) + ((X) - ((X)/3)*3) * 0x30)
#define	HwGDMA_CHCTRL(X)				*(volatile unsigned long *)(0xF0040000 + ((X)*0x100/0x300) + ((X) - ((X)/3)*3) * 0x30 + 0x24)
#define	HwGDMA_ST_SADR(X)				*(volatile unsigned long *)(0xF0040000 + ((X)*0x100/0x300) + ((X) - ((X)/3)*3) * 0x30)
#define	HwGDMA_ST_DADR(X)				*(volatile unsigned long *)(0xF0040000 + ((X)*0x100/0x300) + ((X) - ((X)/3)*3) * 0x30 + 0x10 )

#define	HwGDMA_MAX_CH							9

typedef	volatile struct
{
	sHwDMA	CH[3];
	unsigned	CONFIG;
} sHwGDMA;
	#define	HwCHCONFIG_IS2_1						Hw22							// Channel 2 Interrupt Flag (Regardless of IEN state)
	#define	HwCHCONFIG_IS1_1						Hw21							// Channel 1 Interrupt Flag (Regardless of IEN state)
	#define	HwCHCONFIG_IS0_1						Hw20							// Channel 0 Interrupt Flag (Regardless of IEN state)
	#define	HwCHCONFIG_MIS2_1						Hw18							// Channel 2 Masked Interrupt Flag (only when IEN = 1)
	#define	HwCHCONFIG_MIS1_1						Hw17							// Channel 1 Masked Interrupt Flag (only when IEN = 1)
	#define	HwCHCONFIG_MIS0_1						Hw16							// Channel 0 Masked Interrupt Flag (only when IEN = 1)
	#define	HwCHCONFIG_SWP2_EN					Hw10							// Swap Channel 2 Data (D3D2D1D0 -> D0D1D2D3 / D1D0 -> D0D1)
	#define	HwCHCONFIG_SWP1_EN					Hw10							// Swap Channel 1 Data (D3D2D1D0 -> D0D1D2D3 / D1D0 -> D0D1)
	#define	HwCHCONFIG_SWP0_EN					Hw10							// Swap Channel 0 Data (D3D2D1D0 -> D0D1D2D3 / D1D0 -> D0D1)
	#define	HwCHCONFIG_PRICFG(X)					((X)*Hw4)
	#define	HwCHCONFIG_PRI_012						HwCHCONFIG_PRICFG(0)			// Channel Priority CH0 > CH1 > CH2 (only when FIX = 1)
	#define	HwCHCONFIG_PRI_021						HwCHCONFIG_PRICFG(1)			// Channel Priority CH0 > CH2 > CH1 (only when FIX = 1)
	#define	HwCHCONFIG_PRI_102						HwCHCONFIG_PRICFG(2)			// Channel Priority CH1 > CH0 > CH2 (only when FIX = 1)
	#define	HwCHCONFIG_PRI_120						HwCHCONFIG_PRICFG(3)			// Channel Priority CH1 > CH2 > CH0 (only when FIX = 1)
	#define	HwCHCONFIG_PRI_210						HwCHCONFIG_PRICFG(4)			// Channel Priority CH2 > CH1 > CH0 (only when FIX = 1)
	#define	HwCHCONFIG_PRI_201						HwCHCONFIG_PRICFG(5)			// Channel Priority CH2 > CH0 > CH1 (only when FIX = 1)
	#define	HwCHCONFIG_PRI_MASK					HwCHCONFIG_PRICFG(7)
	#define	HwCHCONFIG_FIX_EN						Hw0								// Channel Priority Fixed

/***********************************************************************
*	I/O Bus Controller Register Define			(Base Addr = 0xF0050000)
************************************************************************/
#define	HwIOBC_BASE							*(volatile unsigned long *)0xF0050000	// IOBC Base Register

#define	HwUSB11H								*(volatile unsigned long *)0xF0050004	// R/W, USB1.1 Host Configuration Register
	#define	HwUSB11H_CNT							Hw2								//

#define	HwIOBAPB								*(volatile unsigned long *)0xF0050008	// R/W, I/O Bus APB Configuration Register
	#define	HwIOBAPB_IOBC							Hw0								// I/O Bus Control and Configuration Register
	#define	HwIOBAPB_MS							Hw1								// Memory Stick Host Controller
	#define	HwIOBAPB_I2C							Hw2								// I2C Interface Controller - Master Only
	#define	HwIOBAPB_NFC							Hw3								// NAND Flash Interface Controller
	#define	HwIOBAPB_CMIC							Hw4								// Camera Module Interface Controller
	#define	HwIOBAPB_UART0							Hw5								// UART Channel 0 (16C550 Compatible and TCC76x Compatible)
	#define	HwIOBAPB_UART1							Hw6								// UART Channel 1
	#define	HwIOBAPB_GSIO							Hw7								// GSIO Controller and SPI Slave Controller
	#define	HwIOBAPB_SDMMC						Hw8								// SD/MMC Host Controller
	#define	HwIOBAPB_DAICDIF						Hw9								// DAI/CDIF Controller
	#define	HwIOBAPB_GPIO							Hw10							// GPIO Controller
	#define	HwIOBAPB_ECC							Hw11							// ECC Calculator
	#define	HwIOBAPB_SPDIF							Hw12							// SPDIF Transmitter

#define	HwSTORAGE								*(volatile unsigned long *)0xF005000C	// R/W, Storage Device Configuration Register
	#define	HwSTORAGE_ECCS_SBUS					HwZERO							// Storage Bus
	#define	HwSTORAGE_ECCS_IOBUS					Hw16							// I/O bus
	#define	HwSTORAGE_ECCS_GPMEM					Hw17							// General purpose SRAM or DTCM
	#define	HwSTORAGE_ECCS_MPDBUS				(Hw17+Hw16)						// Main processor data bus
	#define	HwSTORAGE_U0SEL_TCC76X				Hw8								// The UART ports of channel 0 is controlled by UART compatible for TCC76x
	#define	HwSTORAGE_MSB_BIG						Hw3								// The Endian for memory stick is big-endian byte aligned format
	#define	HwSTORAGE_MSBS_16						HwZERO							// The interface data bus width for memory stick is 16bits data bus
	#define	HwSTORAGE_MSBS_32						Hw1								// The interface data bus width for memory stick is 32bits data bus
	#define	HwSTORAGE_MSCS_PAD					Hw0								// The data synchronization clock is looped-back clock through PAD

/***********************************************************************
*	Memory Stick Host Controller Register Define(Base Addr = 0xF0051000)
************************************************************************/
#define	HwMSTICK_BASE							*(volatile unsigned long *)0xF0051000	// Memory Stick Base Register

#define	HwCOMMAND								*(volatile unsigned long *)0xF0051000	// R/W, Command register
	#define	HwCOMMAND_TPC_RDL						Hw13							// Read Long Data Command
	#define	HwCOMMAND_TPC_RDS					(Hw13+Hw12)						// Read Short Data Command
	#define	HwCOMMAND_TPC_RDR					Hw14							// Read Register Command
	#define	HwCOMMAND_TPC_GETINT					(Hw14+Hw13+Hw12)				// Get Interrupt Command
	#define	HwCOMMAND_TPC_WRL					(Hw15+Hw14+Hw12)				// Write Long Data Command
	#define	HwCOMMAND_TPC_WRS					(Hw15+Hw14)						// Write Short Data Command
	#define	HwCOMMAND_TPC_WRR					(Hw15+Hw13+Hw12)				// Write Register Command
	#define	HwCOMMAND_TPC_SRRA					Hw15							// Set R/W Register Address Command
	#define	HwCOMMAND_TPC_SETCMD					(Hw15+Hw14+Hw13)				// Set Command
	#define	HwCOMMAND_TPC_EXSETCMD				(Hw15+Hw12)						// Exit Set Command
	#define	HwCOMMAND_DSL_EXT						Hw10							// External Memory - Not Supported
	#define	HwCOMMAND_DSL_INT						~Hw10							// Internal FIFO - Only Supported

#define	HwDATA									*(volatile unsigned long *)0xF0051004	// R/W, Data register

#define	HwSTATUS								*(volatile unsigned long *)0xF0051008	// R/W, Status register
	#define	HwSTATUS_DRQ							Hw14							// DMA Requested
	#define	HwSTATUS_MSINT							Hw13							// Interrupt Activated
	#define	HwSTATUS_RDY							Hw12							// Command Receive Enabled or Protocol Ended
	#define	HwSTATUS_CRC							Hw9								// CRC Error Occurred
	#define	HwSTATUS_TOE							Hw8								// Time-Out Error Occurred
	#define	HwSTATUS_EMP							Hw5								// FIFO Empty
	#define	HwSTATUS_FUL							Hw4								// FIFO Full
	#define	HwSTATUS_CED							Hw3								// Command Ended
	#define	HwSTATUS_ERR							Hw2								// Error Occurred, Cleared by writing command register
	#define	HwSTATUS_BRQ							Hw1								// Data Buffer Requested, Cleared by writing command register
	#define	HwSTATUS_CNK							Hw0								// Not Acknowledge, Cleared by writing command register

#define	HwSYSTEM								*(volatile unsigned long *)0xF005100C	// R/W, System Control register
	#define	HwSYSTEM_RST_RST						Hw15							// Reset, Automatically cleared
	#define	HwSYSTEM_RST_NORST					~Hw15							// Not Reset
	#define	HwSYSTEM_SRAC_S						Hw14							// Serial Mode
	#define	HwSYSTEM_SRAC_P						~Hw14							// Parallel Mode
	#define	HwSYSTEM_INTEN_EN						Hw13							// Enabled
	#define	HwSYSTEM_INTEN_DIS						~Hw13							// Disabled
	#define	HwSYSTEM_NCRC_DIS						Hw12							// CRC Output Disabled
	#define	HwSYSTEM_NCRC_EN						~Hw12							// CRC Output Enabled
	#define	HwSYSTEM_ICLR_CLR						Hw11							// Interrupt Clear, Automatically clear
	#define	HwSYSTEM_ICLR_NOTCLR					~Hw11							// Not clear
	#define	HwSYSTEM_MSIEN_EN						Hw10							// Enabled
	#define	HwSYSTEM_MSIEN_DIS						~Hw10							// Disabled
	#define	HwSYSTEM_FCLR_CLR						Hw9								// FIFO clear, Automatically clear
	#define	HwSYSTEM_FCLR_NOTCLR					~Hw9							// Not clear
	#define	HwSYSTEM_FDIR_T						Hw8								// Transmit Mode
	#define	HwSYSTEM_FDIR_R						~Hw8							// Receive Mode
	#define	HwSYSTEM_DAM_S							Hw7								// Single Address Mode
	#define	HwSYSTEM_DAM_D						~Hw7							// Dual Addrsss Mode
	#define	HwSYSTEM_DRM_E							Hw6								// Edge Mode
	#define	HwSYSTEM_DRM_L							~Hw6							// Level Mode
	#define	HwSYSTEM_DRSL_GEN						Hw5								// Generate interrupt when a data request occurs, In software mode
	#define	HwSYSTEM_DRSL_NOTGEN					~Hw5							// Do not generate interrupt when a data request occurs, In DAM mode
	#define	HwSYSTEM_REI_RISE						Hw4								// Input data sampled by rising edge
	#define	HwSYSTEM_REI_FALL						~Hw4							// Input data sampled by falling edge
	#define	HwSYSTEM_REO_RISE						Hw3								// Output data generated at rising edge
	#define	HwSYSTEM_REO_FALL						~Hw3							// Output data generated at falling edge

/************************************************************************
*	I2C Register Define							(Base Addr = 0xF0052000)
************************************************************************/
#define	HwI2CM_CH0_BASE					*(volatile unsigned long *)0xF0052000
#define	HwI2CM_CH1_BASE					*(volatile unsigned long *)0xF0052040
#define	HwI2CM_BASE(X)						*(volatile unsigned long *)(0xF0052000+(X)*0x40)
#define	HwI2C_BASE							*(volatile unsigned long *)0xF0052000	// I2C Base Register

#define	HwI2CM_MAX_CH								2

typedef volatile struct
{
	unsigned	PRES;
	unsigned	CTRL;
	unsigned	TXR;
	unsigned	CMD;
	unsigned	RXR;
	unsigned	SR;
	unsigned	TR;
} sHwI2CM;

	#define	HwI2CM_CTRL_EN_ON					Hw7									// Enabled
	#define	HwI2CM_CTRL_EN_OFF					HwZERO								// Disabled
	#define	HwI2CM_CTRL_IEN_ON					Hw6									// Enabled
	#define	HwI2CM_CTRL_IEN_OFF					HwZERO								// Disabled
	#define	HwI2CM_CTRL_MOD_16					Hw5									// 16bit Mode
	#define	HwI2CM_CTRL_MOD_8					HwZERO								// 8bit Mode
	#define	HwI2CM_CMD_STA_EN					Hw7 								// Start Condition Generation Enabled
	#define	HwI2CM_CMD_STA_DIS				HwZERO 								// Start Condition Generation Disabled
	#define	HwI2CM_CMD_STO_EN					Hw6 								// Stop Condition Generation Enabled
	#define	HwI2CM_CMD_STO_DIS				HwZERO 								// Stop Condition Generation Disabled
	#define	HwI2CM_CMD_RD_EN					Hw5 								// Read From Slave Enabled
	#define	HwI2CM_CMD_RD_DIS					HwZERO 								// Read From Slave Disabled
	#define	HwI2CM_CMD_WR_EN					Hw4 								// Wrtie to Slabe Enabled
	#define	HwI2CM_CMD_WR_DIS					HwZERO 								// Wrtie to Slabe Disabled
	#define	HwI2CM_CMD_ACK_EN					Hw3 								// Sent ACK Enabled
	#define	HwI2CM_CMD_ACK_DIS				HwZERO 								// Sent ACK Disalbed
	#define	HwI2CM_CMD_IACK_CLR				Hw0 								// Clear a pending interrupt
	#define	HwI2CM_SR_RxACK					Hw7									// 1:Acknowledge received, 0:No Acknowledge received
	#define	HwI2CM_SR_BUSY						Hw6									// 1:Start signal detected, 0:Stop signal detected
	#define	HwI2CM_SR_AL						Hw5									// 1:The core lost arbitration, 0:The core don't lost arbitration
	#define	HwI2CM_SR_TIP						Hw1									// 1:Transfer Complete, 0:Transferring Data
	#define	HwI2CM_SR_IF						Hw0									// 1:Interrupt is pending
	#define	HwI2CM_TR_CKSEL					Hw5									// Clock Source Select

#define	HwI2CMCH0_PRES							*(volatile unsigned long *)0xF0052000	// R/W, I2C Clock Prescale Register

#define	HwI2CMCH0_CTRL							*(volatile unsigned long *)0xF0052004	// R/W, I2C Control Register
	#define	HwI2CMCH0_CTRL_EN_ON					Hw7								// Enabled
	#define	HwI2CMCH0_CTRL_EN_OFF					~Hw7							// Disabled
	#define	HwI2CMCH0_CTRL_IEN_ON					Hw6								// Enabled
	#define	HwI2CMCH0_CTRL_IEN_OFF					~Hw6							// Disabled
	#define	HwI2CMCH0_CTRL_MOD_16					Hw5								// 16bit Mode
	#define	HwI2CMCH0_CTRL_MOD_8					~Hw5							// 8bit Mode

#define	HwI2CMCH0_TXR							*(volatile unsigned long *)0xF0052008	// W, I2C Transmit Register

#define	HwI2CMCH0_CMD							*(volatile unsigned long *)0xF005200C	// W, I2C Command Register
	#define	HwI2CMCH0_CMD_STA_EN					Hw7 							// Start Condition Generation Enabled
	#define	HwI2CMCH0_CMD_STA_DIS					~Hw7 							// Start Condition Generation Disabled
	#define	HwI2CMCH0_CMD_STO_EN					Hw6 							// Stop Condition Generation Enabled
	#define	HwI2CMCH0_CMD_STO_DIS					~Hw6 							// Stop Condition Generation Disabled
	#define	HwI2CMCH0_CMD_RD_EN					Hw5 							// Read From Slave Enabled
	#define	HwI2CMCH0_CMD_RD_DIS					~Hw5 							// Read From Slave Disabled
	#define	HwI2CMCH0_CMD_WR_EN					Hw4 							// Wrtie to Slabe Enabled
	#define	HwI2CMCH0_CMD_WR_DIS					~Hw4 							// Wrtie to Slabe Disabled
	#define	HwI2CMCH0_CMD_ACK_EN					Hw3 							// Sent ACK Enabled
	#define	HwI2CMCH0_CMD_ACK_DIS					~Hw3 							// Sent ACK Disalbed
	#define	HwI2CMCH0_CMD_IACK_CLR				Hw0 							// Clear a pending interrupt

#define	HwI2CMCH0_RXR							*(volatile unsigned long *)0xF0052010	// R, I2C Receive Register

#define	HwI2CMCH0_SR							*(volatile unsigned long *)0xF0052014	// R, I2C Status Register
	#define	HwI2CMCH0_SR_RxACK					Hw7								// 1:Acknowledge received, 0:No Acknowledge received
	#define	HwI2CMCH0_SR_BUSY						Hw6								// 1:Start signal detected, 0:Stop signal detected
	#define	HwI2CMCH0_SR_AL						Hw5								// 1:The core lost arbitration, 0:The core don't lost arbitration
	#define	HwI2CMCH0_SR_TIP						Hw1								// 1:Transfer Complete, 0:Transferring Data
	#define	HwI2CMCH0_SR_IF						Hw0								// 1:Interrupt is pending

#define	HwI2CMCH0_TR							*(volatile unsigned long *)0xF0052018	// Timing Register
	#define	HwI2CMCH0_TR_CKSEL						Hw5								// Clock Source Select

#define	HwI2CMCH1_PRES							*(volatile unsigned long *)0xF0052040	// R/W, I2C Clock Prescale Register

#define	HwI2CMCH1_CTRL							*(volatile unsigned long *)0xF0052044	// R/W, I2C Control Register
	#define	HwI2CMCH1_CTRL_EN_ON					Hw7								// Enabled
	#define	HwI2CMCH1_CTRL_EN_OFF					~Hw7							// Disabled
	#define	HwI2CMCH1_CTRL_IEN_ON					Hw6								// Enabled
	#define	HwI2CMCH1_CTRL_IEN_OFF					~Hw6							// Disabled
	#define	HwI2CMCH1_CTRL_MOD_16					Hw5								// 16bit Mode
	#define	HwI2CMCH1_CTRL_MOD_8					~Hw5							// 8bit Mode

#define	HwI2CMCH1_TXR							*(volatile unsigned long *)0xF0052048	// W, I2C Transmit Register

#define	HwI2CMCH1_CMD							*(volatile unsigned long *)0xF005204C	// W, I2C Command Register
	#define	HwI2CMCH1_CMD_STA_EN					Hw7 							// Start Condition Generation Enabled
	#define	HwI2CMCH1_CMD_STA_DIS					~Hw7 							// Start Condition Generation Disabled
	#define	HwI2CMCH1_CMD_STO_EN					Hw6 							// Stop Condition Generation Enabled
	#define	HwI2CMCH1_CMD_STO_DIS					~Hw6 							// Stop Condition Generation Disabled
	#define	HwI2CMCH1_CMD_RD_EN					Hw5 							// Read From Slave Enabled
	#define	HwI2CMCH1_CMD_RD_DIS					~Hw5 							// Read From Slave Disabled
	#define	HwI2CMCH1_CMD_WR_EN					Hw4 							// Wrtie to Slabe Enabled
	#define	HwI2CMCH1_CMD_WR_DIS					~Hw4 							// Wrtie to Slabe Disabled
	#define	HwI2CMCH1_CMD_ACK_EN					Hw3 							// Sent ACK Enabled
	#define	HwI2CMCH1_CMD_ACK_DIS					~Hw3 							// Sent ACK Disalbed
	#define	HwI2CMCH1_CMD_IACK_CLR				Hw0 							// Clear a pending interrupt

#define	HwI2CMCH1_RXR							*(volatile unsigned long *)0xF0052050	// R, I2C Receive Register

#define	HwI2CMCH1_SR							*(volatile unsigned long *)0xF0052054	// R, I2C Status Register
	#define	HwI2CMCH1_SR_RxACK					Hw7								// 1:Acknowledge received, 0:No Acknowledge received
	#define	HwI2CMCH1_SR_BUSY						Hw6								// 1:Start signal detected, 0:Stop signal detected
	#define	HwI2CMCH1_SR_AL						Hw5								// 1:The core lost arbitration, 0:The core don't lost arbitration
	#define	HwI2CMCH1_SR_TIP						Hw1								// 1:Transfer Complete, 0:Transferring Data
	#define	HwI2CMCH1_SR_IF						Hw0								// 1:Interrupt is pending

#define	HwI2CMCH1_TR							*(volatile unsigned long *)0xF0052058	// Timing Register
	#define	HwI2CMCH1_TR_CKSEL						Hw5								// Clock Source Select

#define	HwI2CS_DPORT							*(volatile unsigned long *)0xF0052080	// Data Port

#define	HwI2CS_CTL								*(volatile unsigned long *)0xF0052084	// Control Register
	#define	HwI2CS_CTL_SLV_2M						HwZERO							// 2 master operation
	#define	HwI2CS_CTL_SLV_1M1S					Hw30							// 1 master / 1 slave
	#define	HwI2CS_CTL_RCLR						Hw5								// clear interrupt status at read cycle
	#define	HwI2CS_CTL_WS							Hw4								// wait status control by SCL stretching
	#define	HwI2CS_CTL_SDA							Hw3								// Reserved
	#define	HwI2CS_CTL_CLR							Hw2								// Clear FIFO
	#define	HwI2CS_CTL_EN							Hw0								// Enable for this slave core

#define	HwI2CS_ADDR								*(volatile unsigned long *)0xF0052088	// Address Register

#define	HwI2CS_MAX_CH								1

typedef volatile struct
{
	unsigned	DPORT;
	unsigned	CTL;
	unsigned	ADDR;
	unsigned	INT;
	unsigned	STAT;
	unsigned	MBF;
	unsigned	MB0;
	unsigned	MB1;
} sHwI2CS;

#define	HwI2CS_INT								*(volatile unsigned long *)0xF005208C	// Interrupt Register
	#define	HwI2CS_INT_STAT_R_BYTE					Hw27							// All byte of data buffer has been read by a master
	#define	HwI2CS_INT_STAT_W_BYTE					Hw26							// All byte of data buffer has been written by a master
	#define	HwI2CS_INT_STAT_R_BUFF					Hw25							// Data buffer has been read by a master
	#define	HwI2CS_INT_STAT_W_BUFF					Hw24							// Data buffer has been written by a master
	#define	HwI2CS_INT_STAT_TXUR					Hw23							// TX FIFO under run
	#define	HwI2CS_INT_STAT_RXOR					Hw22							// RX FIFO over run
	#define	HwI2CS_INT_STAT_TXB					Hw21							// TX bus cycle started with TX FIFO empty
	#define	HwI2CS_INT_STAT_RXF						Hw20							// RX FIFO full
	#define	HwI2CS_INT_STAT_TXE						Hw19							// TX FIFO empty
	#define	HwI2CS_INT_STAT_RXNE					Hw18							// RX FIFO not empty
	#define	HwI2CS_INT_STAT_TXL						Hw17							// TX FIFO Level (TXVC <= TXTH)
	#define	HwI2CS_INT_STAT_RXL						Hw16							// RX FIFO Level (RXVC <= RXTH)
	#define	HwI2CS_INT_EN_R_BYTE					Hw11							// All byte of data buffer has been read by a master
	#define	HwI2CS_INT_EN_W_BYTE					Hw10							// All byte of data buffer has been written by a master
	#define	HwI2CS_INT_EN_R_BUFF					Hw9								// Data buffer has been read by a master
	#define	HwI2CS_INT_EN_W_BUFF					Hw8								// Data buffer has been written by a master
	#define	HwI2CS_INT_EN_TXUR						Hw7								// TX FIFO under run
	#define	HwI2CS_INT_EN_RXOR						Hw6								// RX FIFO over run
	#define	HwI2CS_INT_EN_TXB						Hw5								// TX bus cycle started with TX FIFO empty
	#define	HwI2CS_INT_EN_RXF						Hw4								// RX FIFO full
	#define	HwI2CS_INT_EN_TXE						Hw3								// TX FIFO empty
	#define	HwI2CS_INT_EN_RXNE						Hw2								// RX FIFO not empty
	#define	HwI2CS_INT_EN_TXL						Hw1								// TX FIFO Level (TXVC <= TXTH)
	#define	HwI2CS_INT_EN_RXL						Hw0								// RX FIFO Level (RXVC <= RXTH)

#define	HwI2CS_STAT								*(volatile unsigned long *)0xF0052090	// Status Register
	#define	HwI2CS_STAT_DDIR						Hw23							// Data Direction is TX state
	#define	HwI2CS_STAT_SLVADDR_MASK				(Hw8-Hw0)						// Slave Address Received from address cycle

#define	HwI2CS_MBF								*(volatile unsigned long *)0xF005209C	// Buffer Valid Flag Register

#define	HwI2CS_MB0								*(volatile unsigned long *)0xF00520A0	// Data Buffer 0

#define	HwI2CS_MB1								*(volatile unsigned long *)0xF00520A4	// Data Buffer 1

#define	HwI2C_IRQSTR							*(volatile unsigned long *)0xF00520C0	// IRQ Status
	#define	HwI2C_IRQSTR_ST2						Hw2								// IRQ Status of I2C Slave Controller
	#define	HwI2C_IRQSTR_ST1						Hw1								// IRQ Status of I2C Master Controller Channel 1
	#define	HwI2C_IRQSTR_ST0						Hw0								// IRQ Status of I2C Master Controller Channel 0

/***********************************************************************
*	 NAND Flash Controller Register Define		(Base Addr = 0xF00B0000)
************************************************************************/
#define	HwNFC_BASE								*(volatile unsigned long *)0xF00B0000	// NFC Base Register

typedef	volatile struct
{
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

#define	HwNFC_CMD								*(volatile unsigned long *)0xF00B0000	// W, Nand Flash Command Register

#define	HwNFC_LADDR							*(volatile unsigned long *)0xF00B0004	// W, Nand Flash Linear Address Register

#define	HwNFC_BADDR							*(volatile unsigned long *)0xF00B0008	// W, Nand Flash Block Address Register

#define	HwNFC_SADDR							*(volatile unsigned long *)0xF00B000C	// W, Nand Flash Signal Address Register

#define	HwNFC_WDATA							*(volatile unsigned long *)0xF00B0010	// R/W, Nand Flash Word Data Register

#define	HwNFC_LDATA							*(volatile unsigned long *)0xF00B0020	// R/W, Nand Flash Linear Data Register

#define	HwNFC_SDATA							*(volatile unsigned long *)0xF00B0040	// R/W, Nand Flash Single Data Register

#define	HwNFC_CTRL								*(volatile unsigned long *)0xF00B0050	// R/W, Nand Flash Control Register
	#define	HwNFC_CTRL_RDYIEN_EN					Hw31							// Nand Flash Ready Interrupt Enable
	#define	HwNFC_CTRL_RDYIEN_DIS					~Hw31							// Nand Flash Ready Interrupt Disable
	#define	HwNFC_CTRL_PROGIEN_EN					Hw30							// Nand Flash Program Interrupt Enable 
	#define	HwNFC_CTRL_PROGIEN_DIS					~Hw30							// Nand Flash Program Interrupt Disable
	#define	HwNFC_CTRL_READIEN_EN					Hw29							// Nand Flash Read Interrupt Enable
	#define	HwNFC_CTRL_READIEN_DIS					~Hw29							// Nand Flash Read Interrupt Disable
	#define	HwNFC_CTRL_DEN_EN						Hw28							// Nand Flash DMA Request Enable
	#define	HwNFC_CTRL_DEN_DIS						~Hw28							// Nand Flash DMA Request Disable
	#define	HwNFC_CTRL_FS_RDY						Hw27							// FIFO status is Ready to write and read in FIFO
	#define	HwNFC_CTRL_FS_BUSY						~Hw27							// FIFO status is Busy to write and read in FIFO
	#define	HwNFC_CTRL_BW_16						Hw26							// Bus width = 8bit
	#define	HwNFC_CTRL_BW_8						HwZERO							// Bus width = 16bit
	#define	HwNFC_CTRL_CS3SEL_1					Hw25							// Nand Flash nCS3 is High (Disabled)
	#define	HwNFC_CTRL_CS3SEL_0					HwZERO							// Nand Flash nCS3 is Low (Enabled)
	#define	HwNFC_CTRL_CS2SEL_1					Hw24							// Nand Flash nCS2 is High (Disabled)
	#define	HwNFC_CTRL_CS2SEL_0					HwZERO							// Nand Flash nCS2 is Low (Enabled)
	#define	HwNFC_CTRL_CS1SEL_1					Hw23							// Nand Flash nCS1 is High (Disabled)
	#define	HwNFC_CTRL_CS1SEL_0					HwZERO							// Nand Flash nCS1 is Low (Enabled)
	#define	HwNFC_CTRL_CS0SEL_1					Hw22							// Nand Flash nCS0 is High (Disabled)
	#define	HwNFC_CTRL_CS0SEL_0					HwZERO							// Nand Flash nCS0 is Low (Enabled)
	#define	HwNFC_CTRL_CFG_nCS3					HwNFC_CTRL_CS3SEL_1
	#define	HwNFC_CTRL_CFG_nCS2					HwNFC_CTRL_CS2SEL_1
	#define	HwNFC_CTRL_CFG_nCS1					HwNFC_CTRL_CS1SEL_1
	#define	HwNFC_CTRL_CFG_nCS0					HwNFC_CTRL_CS0SEL_1
	#define	HwNFC_CTRL_CSnSEL(X)					((X)*Hw22)						// Nand Flash nCS[3:0] Set
	#define	HwNFC_CTRL_CFG_NOACT					HwNFC_CTRL_CSnSEL(15)
	#define	HwNFC_CTRL_RDY_RDY						Hw21							// External Nand Flash Controller is Ready
	#define	HwNFC_CTRL_RDY_BUSY					~Hw21							// External Nand Flash Controller is Busy
	#define	HwNFC_CTRL_BSIZE(X)						((X)*Hw19)
	#define	HwNFC_CTRL_BSIZE_1						HwNFC_CTRL_BSIZE(0)			// 1Read/Write
	#define	HwNFC_CTRL_BSIZE_2						HwNFC_CTRL_BSIZE(1)			// 2Read/Write
	#define	HwNFC_CTRL_BSIZE_4						HwNFC_CTRL_BSIZE(2)			// 4Read/Write
	#define	HwNFC_CTRL_BSIZE_8						HwNFC_CTRL_BSIZE(3)			// 8Read/Write
	#define	HwNFC_CTRL_BSIZE_MASK					HwNFC_CTRL_BSIZE(3)
	#define	HwNFC_CTRL_PSIZE(X)						((X)*Hw16)
	#define	HwNFC_CTRL_PSIZE_256					HwNFC_CTRL_PSIZE(0)			// 1 Page = 256 Half-Word
	#define	HwNFC_CTRL_PSIZE_512					HwNFC_CTRL_PSIZE(1)			// 1 Page = 512 Byte
	#define	HwNFC_CTRL_PSIZE_1024					HwNFC_CTRL_PSIZE(2)			// 1 Page = 1024 Half-Word
	#define	HwNFC_CTRL_PSIZE_2048					HwNFC_CTRL_PSIZE(3)			// 1 Page = 2048 Byte
	#define	HwNFC_CTRL_PSIZE_4096					HwNFC_CTRL_PSIZE(4)			// 1 Page = 4096 Byte
	#define	HwNFC_CTRL_PSIZE_MASK					HwNFC_CTRL_PSIZE(7)
	#define	HwNFC_CTRL_MASK_EN						Hw15							// Address/Command Mask Enable
	#define	HwNFC_CTRL_CADDR						Hw12							// Number of Address Cycle
	#define	HwNFC_CTRL_bSTP(X)						((X)*Hw8)						// Number of Base cycle for Setup Time
	#define	HwNFC_CTRL_bSTP_MASK					HwNFC_CTRL_bSTP(15)
	#define	HwNFC_CTRL_bPW(X)						((X)*Hw4)						// Number of Base cycle for Pulse Width
	#define	HwNFC_CTRL_bPW_MASK					HwNFC_CTRL_bPW(15)
	#define	HwNFC_CTRL_bHLD(X)						((X)*Hw0)						// Number of Base cycle for Hold Time
	#define	HwNFC_CTRL_bHLD_MASK					HwNFC_CTRL_bHLD(15)

#define	HwNFC_PSTART							*(volatile unsigned long *)0xF00B0054	// W, Nand Flash Program Start Register

#define	HwNFC_RSTART							*(volatile unsigned long *)0xF00B0058	// W, Nand Flash Read Start Register

#define	HwNFC_DSIZE							*(volatile unsigned long *)0xF00B005C	// R/W, Nand Flash Data Size Register

#define	HwNFC_IREQ								*(volatile unsigned long *)0xF00B0060	// R/W, Nand Flash Interrupt Request Register
	#define	HwNFC_IREQ_FLAG2						Hw6								// R:The Rising edge of Ready Signal is occurred, W:Ready Flag Clear
	#define	HwNFC_IREQ_FLAG1						Hw5								// R:Program data transfer is finished, W:Program Flag Clear
	#define	HwNFC_IREQ_FLAG0						Hw4								// R:Read data transfer is finished, W:Read Flag Clear
	#define	HwNFC_IREQ_IRQ2						Hw2								// Ready Interrupt
	#define	HwNFC_IREQ_IRQ1						Hw1								// Program Interrupt
	#define	HwNFC_IREQ_IRQ0						Hw0								// Reading Interrupt

#define	HwNFC_RST								*(volatile unsigned long *)0xF00B0064	// W, Nand Flash Controller Reset Register

#define	HwNFC_CTRL1							*(volatile unsigned long *)0xF00B0068	// W, Nand Flash Controller Register 1
	#define	HwNFC_CTRL1_DAK_EN						Hw31							// DMA Acknowledge Enabled
	#define	HwNFC_CTRL1_rSTP(X)						((X)*Hw20)						// Number of additional cycle for Setup Time in Reading
	#define	HwNFC_CTRL1_rSTP_MASK					HwNFC_CTRL1_rSTP(15)
	#define	HwNFC_CTRL1_rPW(X)						((X)*Hw16)						// Number of additional cycle for Pulse width Time in Reading
	#define	HwNFC_CTRL1_rPW_MASK					HwNFC_CTRL1_rPW(15)
	#define	HwNFC_CTRL1_rHLD(X)						((X)*Hw12)						// Number of additional cycle for Hold Time in Reading
	#define	HwNFC_CTRL1_rHLD_MASK					HwNFC_CTRL1_rHLD(15)
	#define	HwNFC_CTRL1_wSTP(X)					((X)*Hw8)						// Number of additional cycle for Setup Time in Writing
	#define	HwNFC_CTRL1_wSTP_MASK					HwNFC_CTRL1_wSTP(15)
	#define	HwNFC_CTRL1_wPW(X)						((X)*Hw4)						// Number of additional cycle for Pulse width Time in Writing
	#define	HwNFC_CTRL1_wPW_MASK					HwNFC_CTRL1_wPW(15)
	#define	HwNFC_CTRL1_wHLD(X)					((X)*Hw0)						// Number of additional cycle for Hold Time in Writing
	#define	HwNFC_CTRL1_wHLD_MASK					HwNFC_CTRL1_wHLD(15)

#define	HwNFC_MDATA							*(volatile unsigned long *)0xF00B0070	// R/W, Nand Flash Multiple Data Register

/***********************************************************************
*	UART0 Controller Register Define			(Base Addr = 0xF0055000)
************************************************************************/
#define	HwUART0_BASE							*(volatile unsigned long *)0xF0055000	// UART 0 Base Register

#define	HwUART0_RBR							*(volatile unsigned long *)0xF0055000	// R, Receiver Buffer Register (DLAB = 0)

#define	HwUART0_THR							*(volatile unsigned long *)0xF0055000	// W, Transmitter Holding Register (DLAB = 0)

#define	HwUART0_DLL								*(volatile unsigned long *)0xF0055000	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART0_DLM							*(volatile unsigned long *)0xF0055004	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART0_IER								*(volatile unsigned long *)0xF0055004	// R/W, Interrupt Enable Register (DLAB = 0)
	#define	HwUART0_IER_EMSI_EN					Hw3								// Enable Modem status interrupt
	#define	HwUART0_IER_EMSI_DIS					~Hw3							// Disable Modem status interrupt
	#define	HwUART0_IER_ELSI_EN						Hw2								// Enable receiver line status interrupt
	#define	HwUART0_IER_ELSI_DIS					~Hw2							// Disable receiver line status interrupt
	#define	HwUART0_IER_ETXI_EN						Hw1								// Enable transmitter holding register empty interrupt
	#define	HwUART0_IER_ETXI_DIS					~Hw1							// Disable transmitter holding register empty interrupt
	#define	HwUART0_IER_ERXI_EN						Hw0								// Enable received data available interrupt
	#define	HwUART0_IER_ERXI_DIS					~Hw0							// Disable received data available interrupt

#define	HwUART0_IIR								*(volatile unsigned long *)0xF0055008	// R, Interrupt Ident. Register (DLAB = 0)
	#define	HwUART0_IIR_STF							Hw27							// 1:TX is done (SmartCard TX done flag)
	#define	HwUART0_IIR_IPF							Hw0								// 1:Interrupt has not generated, 0:Interrupt pending

#define	HwUART0_FCR							*(volatile unsigned long *)0xF0055008	// W, FIFO Control Register (DLAB = 1)
	#define	HwUART0_FCR_RXT_1						~(Hw7+Hw6)						// RX FIFO Trigger Level 1byte
	#define	HwUART0_FCR_RXT_4						Hw6								// RX FIFO Trigger Level 4bytes
	#define	HwUART0_FCR_RXT_8						Hw7								// RX FIFO Trigger Level 8bytes
	#define	HwUART0_FCR_RXT_14						(Hw7+Hw6)						// RX FIFO Trigger Level 16bytes
	#define	HwUART0_FCR_DMS_EN					Hw3								// DMA Mode Enabled
	#define	HwUART0_FCR_DMS_DIS					~Hw3							// DMA Mode Disabled
	#define	HwUART0_FCR_TXFR_EN					Hw2								// Reset TX FIFO counter and FIFO Data
	#define	HwUART0_FCR_TXFR_DIS					~Hw2							//
	#define	HwUART0_FCR_RXFR_EN					Hw1								// Reset RX FIFO counter and FIFO Data
	#define	HwUART0_FCR_RXFR_DIS					~Hw1							//
	#define	HwUART0_FCR_FE_EN						Hw0								// Enable TX and RX FIFOs
	#define	HwUART0_FCR_FE_DIS						~Hw0							// Disable TX and RX FIFOs

#define	HwUART0_LCR							*(volatile unsigned long *)0xF005500C	// R/W, Line Control Register
	#define	HwUART0_LCR_DLAB_ON					Hw7								// Access the divisor latches of the baud generator
	#define	HwUART0_LCR_DLAB_OFF					~Hw7							// Access the receiver buff, the transmitter holding register, or the interrupt enable register
	#define	HwUART0_LCR_SB_ON						Hw6								// The serial output is forced to the spacing (logic 0) state
	#define	HwUART0_LCR_SB_OFF						~Hw6							// Disable the break
	#define	HwUART0_LCR_SP_ON						Hw5								// When bits 3, 4 and 5 are logic 1 the parity bits is transmitted and checked as a logic 0. If bits 3 and 5 are 1 and bit 4 is a logic 0 then the parity bit is transmitted and checked as a logic 1
	#define	HwUART0_LCR_SP_OFF						~Hw5							// Disable stick parity
	#define	HwUART0_LCR_EPS_EVEN					Hw4								// Generate or check even parity
	#define	HwUART0_LCR_EPS_ODD					~Hw4							// Generate or check odd parity
	#define	HwUART0_LCR_PEN_ON						Hw3								// A parity bit is generated (TX) or Checked (RX)
	#define	HwUART0_LCR_PEN_OFF					~Hw3							// Disabled
	#define	HwUART0_LCR_STB_ONE					Hw2								// One stop bit is generated in the transmitted data
	#define	HwUART0_LCR_STB_WLS					~Hw2							// When 5bit word length is selected, one and a half stop bits are generated. When either a 6-, 7-, or 8-bit word length is selected, two stop bits are generated.
	#define	HwUART0_LCR_WLS_5						~(Hw1+Hw0)						// 5 bits word length
	#define	HwUART0_LCR_WLS_6						Hw0								// 6 bits word length
	#define	HwUART0_LCR_WLS_7						Hw1								// 7 bits word length
	#define	HwUART0_LCR_WLS_8						(Hw1+Hw0)						// 8 bits word length

#define	HwUART0_MCR							*(volatile unsigned long *)0xF0055010	// R/W, MODEM Control Register
	#define	HwUART0_MCR_LOOP_ON					Hw4								// Loop Back Enable
	#define	HwUART0_MCR_LOOP_OFF					~Hw4							// Loop Back Disable
	#define	HwUART0_MCR_RTS						Hw1								// This bit informs the external modem that the uart is ready to exchange data

#define	HwUART0_LSR							*(volatile unsigned long *)0xF0055014	// R, Line Status Register
	#define	HwUART0_LSR_ERF_FIFO					Hw7								// In the FIFO mode this bit is set when there is at least one parity error, framing error or break indication in the FIFO
	#define	HwUART0_LSR_ERF_16450					~Hw7							// In the 16450 mode
	#define	HwUART0_LSR_TEMT_ON					Hw6								// Transmitter holding register and the transmitter shift register are both empty
	#define	HwUART0_LSR_TEMT_OFF					~Hw6							//
	#define	HwUART0_LSR_THRE_ON					Hw5								// UART is ready to accept a new char for transmission
	#define	HwUART0_LSR_THRE_OFF					~Hw5							//
	#define	HwUART0_LSR_BI_ON						Hw4								// The received data input is held in the spacing (logic 0) state for longer than a full word transmission time
	#define	HwUART0_LSR_BI_OFF						~Hw4							//
	#define	HwUART0_LSR_FE_ON						Hw3								// The received character did not have a valid stop bit
	#define	HwUART0_LSR_FE_OFF						~Hw3							//
	#define	HwUART0_LSR_PE_ON						Hw2								// The received data character does not have the correct even or odd parity
	#define	HwUART0_LSR_PE_OFF						~Hw2							//
	#define	HwUART0_LSR_OE_ON						Hw1								// The receiver buffer register was not read by the CPU before the next character was transferred into the receiver buffer register
	#define	HwUART0_LSR_OE_OFF						~Hw1							//
	#define	HwUART0_LSR_DR_ON						Hw0								// The receiver data ready
	#define	HwUART0_LSR_DR_OFF						~Hw0							//

#define	HwUART0_MSR							*(volatile unsigned long *)0xF0055018	// R, MODEM Status Register
	#define	HwUART0_MSR_CTS						Hw4								// This bit is the complement of the Claer to Send input
	#define	HwUART0_MSR_DCTS						Hw0								// This bit is the Delta Clear to Send indicator

#define	HwUART0_SCR							*(volatile unsigned long *)0xF005501C	// R/W, Scratch Register
																				// This 8bit Read/Write Register does not control the UART in anyway. It is intended as a scratch pad register to be used by the programmer to hold data temporarily

#define	HwUART0_AFT								*(volatile unsigned long *)0xF0055020	// R/W, AFC Trigger Level Register

#define	HwUART0_UCR							*(volatile unsigned long *)0xF0055024	// R/W, UART Control Register

#define	HwUART0_SRBR							*(volatile unsigned long *)0xF0055040	// R, Same as RBR except not affected by DLAB bit

#define	HwUART0_STHR							*(volatile unsigned long *)0xF0055044	// W, Same as THR except not affected by DLAB bit

#define	HwUART0_SDLL							*(volatile unsigned long *)0xF0055048	// R/W, Same as DLL except not affected by DLAB bit

#define	HwUART0_SDLM							*(volatile unsigned long *)0xF005504C	// R/W, Same as DLM except not affected by DLAB bit

#define	HwUART0_SIER							*(volatile unsigned long *)0xF0055050	// R/W, Same as IER except not affected by DLAB bit

#define	HwUART0_SCCR							*(volatile unsigned long *)0xF0055060	// R/W, SmartCard Control Register

#define	HwUART0_STC							*(volatile unsigned long *)0xF0055064	// R/W, SmartCard TX Count Register

#define	HwUART0_IRCFG							*(volatile unsigned long *)0xF0055080	// R/W, IRDA Configuration Register

/***********************************************************************
*	UART1 Controller Register Define			(Base Addr = 0xF0055100)
************************************************************************/
#define	HwUART1_BASE							*(volatile unsigned long *)0xF0055100	// UART 1 Base Register

#define	HwUART1_RBR							*(volatile unsigned long *)0xF0055100	// R, Receiver Buffer Register (DLAB = 0)

#define	HwUART1_THR							*(volatile unsigned long *)0xF0055100	// W, Transmitter Holding Register (DLAB = 0)

#define	HwUART1_DLL								*(volatile unsigned long *)0xF0055100	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART1_DLM							*(volatile unsigned long *)0xF0055104	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART1_IER								*(volatile unsigned long *)0xF0055104	// R/W, Interrupt Enable Register (DLAB = 0)
	#define	HwUART1_IER_EMSI_EN					Hw3								// Enable Modem status interrupt
	#define	HwUART1_IER_EMSI_DIS					~Hw3							// Disable Modem status interrupt
	#define	HwUART1_IER_ELSI_EN						Hw2								// Enable receiver line status interrupt
	#define	HwUART1_IER_ELSI_DIS					~Hw2							// Disable receiver line status interrupt
	#define	HwUART1_IER_ETXI_EN						Hw1								// Enable transmitter holding register empty interrupt
	#define	HwUART1_IER_ETXI_DIS					~Hw1							// Disable transmitter holding register empty interrupt
	#define	HwUART1_IER_ERXI_EN						Hw0								// Enable received data available interrupt
	#define	HwUART1_IER_ERXI_DIS					~Hw0							// Disable received data available interrupt

#define	HwUART1_IIR								*(volatile unsigned long *)0xF0055108	// R, Interrupt Ident. Register (DLAB = 0)
	#define	HwUART1_IIR_STF							Hw27							// 1:TX is done (SmartCard TX done flag)
	#define	HwUART1_IIR_IPF							Hw0								// 1:Interrupt has not generated, 0:Interrupt pending

#define	HwUART1_FCR							*(volatile unsigned long *)0xF0055108	// W, FIFO Control Register (DLAB = 1)
	#define	HwUART1_FCR_RXT_1						~(Hw7+Hw6)						// RX FIFO Trigger Level 1byte
	#define	HwUART1_FCR_RXT_4						Hw6								// RX FIFO Trigger Level 4bytes
	#define	HwUART1_FCR_RXT_8						Hw7								// RX FIFO Trigger Level 8bytes
	#define	HwUART1_FCR_RXT_14						(Hw7+Hw6)						// RX FIFO Trigger Level 16bytes
	#define	HwUART1_FCR_DMS_EN					Hw3								// DMA Mode Enabled
	#define	HwUART1_FCR_DMS_DIS					~Hw3							// DMA Mode Disabled
	#define	HwUART1_FCR_TXFR_EN					Hw2								// Reset TX FIFO counter and FIFO Data
	#define	HwUART1_FCR_TXFR_DIS					~Hw2							//
	#define	HwUART1_FCR_RXFR_EN					Hw1								// Reset RX FIFO counter and FIFO Data
	#define	HwUART1_FCR_RXFR_DIS					~Hw1							//
	#define	HwUART1_FCR_FE_EN						Hw0								// Enable TX and RX FIFOs
	#define	HwUART1_FCR_FE_DIS						~Hw0							// Disable TX and RX FIFOs

#define	HwUART1_LCR							*(volatile unsigned long *)0xF005510C	// R/W, Line Control Register
	#define	HwUART1_LCR_DLAB_ON					Hw7								// Access the divisor latches of the baud generator
	#define	HwUART1_LCR_DLAB_OFF					~Hw7							// Access the receiver buff, the transmitter holding register, or the interrupt enable register
	#define	HwUART1_LCR_SB_ON						Hw6								// The serial output is forced to the spacing (logic 0) state
	#define	HwUART1_LCR_SB_OFF						~Hw6							// Disable the break
	#define	HwUART1_LCR_SP_ON						Hw5								// When bits 3, 4 and 5 are logic 1 the parity bits is transmitted and checked as a logic 0. If bits 3 and 5 are 1 and bit 4 is a logic 0 then the parity bit is transmitted and checked as a logic 1
	#define	HwUART1_LCR_SP_OFF						~Hw5							// Disable stick parity
	#define	HwUART1_LCR_EPS_EVEN					Hw4								// Generate or check even parity
	#define	HwUART1_LCR_EPS_ODD					~Hw4							// Generate or check odd parity
	#define	HwUART1_LCR_PEN_ON						Hw3								// A parity bit is generated (TX) or Checked (RX)
	#define	HwUART1_LCR_PEN_OFF					~Hw3							// Disabled
	#define	HwUART1_LCR_STB_ONE					Hw2								// One stop bit is generated in the transmitted data
	#define	HwUART1_LCR_STB_WLS					~Hw2							// When 5bit word length is selected, one and a half stop bits are generated. When either a 6-, 7-, or 8-bit word length is selected, two stop bits are generated.
	#define	HwUART1_LCR_WLS_5						~(Hw1+Hw0)						// 5 bits word length
	#define	HwUART1_LCR_WLS_6						Hw0								// 6 bits word length
	#define	HwUART1_LCR_WLS_7						Hw1								// 7 bits word length
	#define	HwUART1_LCR_WLS_8						(Hw1+Hw0)						// 8 bits word length

#define	HwUART1_MCR							*(volatile unsigned long *)0xF0055110	// R/W, MODEM Control Register
	#define	HwUART1_MCR_LOOP_ON					Hw4								// Loop Back Enable
	#define	HwUART1_MCR_LOOP_OFF					~Hw4							// Loop Back Disable
	#define	HwUART1_MCR_RTS						Hw1								// This bit informs the external modem that the uart is ready to exchange data

#define	HwUART1_LSR							*(volatile unsigned long *)0xF0055114	// R, Line Status Register
	#define	HwUART1_LSR_ERF_FIFO					Hw7								// In the FIFO mode this bit is set when there is at least one parity error, framing error or break indication in the FIFO
	#define	HwUART1_LSR_ERF_16450					~Hw7							// In the 16450 mode
	#define	HwUART1_LSR_TEMT_ON					Hw6								// Transmitter holding register and the transmitter shift register are both empty
	#define	HwUART1_LSR_TEMT_OFF					~Hw6							//
	#define	HwUART1_LSR_THRE_ON					Hw5								// UART is ready to accept a new char for transmission
	#define	HwUART1_LSR_THRE_OFF					~Hw5							//
	#define	HwUART1_LSR_BI_ON						Hw4								// The received data input is held in the spacing (logic 0) state for longer than a full word transmission time
	#define	HwUART1_LSR_BI_OFF						~Hw4							//
	#define	HwUART1_LSR_FE_ON						Hw3								// The received character did not have a valid stop bit
	#define	HwUART1_LSR_FE_OFF						~Hw3							//
	#define	HwUART1_LSR_PE_ON						Hw2								// The received data character does not have the correct even or odd parity
	#define	HwUART1_LSR_PE_OFF						~Hw2							//
	#define	HwUART1_LSR_OE_ON						Hw1								// The receiver buffer register was not read by the CPU before the next character was transferred into the receiver buffer register
	#define	HwUART1_LSR_OE_OFF						~Hw1							//
	#define	HwUART1_LSR_DR_ON						Hw0								// The receiver data ready
	#define	HwUART1_LSR_DR_OFF						~Hw0							//

#define	HwUART1_MSR							*(volatile unsigned long *)0xF0055118	// R, MODEM Status Register
	#define	HwUART1_MSR_CTS						Hw4								// This bit is the complement of the Claer to Send input
	#define	HwUART1_MSR_DCTS						Hw0								// This bit is the Delta Clear to Send indicator

#define	HwUART1_SCR							*(volatile unsigned long *)0xF005511C	// R/W, Scratch Register
																					// This 8bit Read/Write Register does not control the UART in anyway. It is intended as a scratch pad register to be used by the programmer to hold data temporarily

#define	HwUART1_AFT								*(volatile unsigned long *)0xF0055120	// R/W, AFC Trigger Level Register

#define	HwUART1_UCR							*(volatile unsigned long *)0xF0055124	// R/W, UART Control Register

#define	HwUART1_SRBR							*(volatile unsigned long *)0xF0055140	// R, Same as RBR except not affected by DLAB bit

#define	HwUART1_STHR							*(volatile unsigned long *)0xF0055144	// W, Same as THR except not affected by DLAB bit

#define	HwUART1_SDLL							*(volatile unsigned long *)0xF0055148	// R/W, Same as DLL except not affected by DLAB bit

#define	HwUART1_SDLM							*(volatile unsigned long *)0xF005514C	// R/W, Same as DLM except not affected by DLAB bit

#define	HwUART1_SIER							*(volatile unsigned long *)0xF0055150	// R/W, Same as IER except not affected by DLAB bit

#define	HwUART1_SCCR							*(volatile unsigned long *)0xF0055160	// R/W, SmartCard Control Register

#define	HwUART1_STC							*(volatile unsigned long *)0xF0055164	// R/W, SmartCard TX Count Register

#define	HwUART1_IRCFG							*(volatile unsigned long *)0xF0055180	// R/W, IRDA Configuration Register

/***********************************************************************
*	UART2 Controller Register Define			(Base Addr = 0xF0055200)
************************************************************************/
#define	HwUART2_BASE							*(volatile unsigned long *)0xF0055200	// UART 2 Base Register

#define	HwUART2_RBR							*(volatile unsigned long *)0xF0055200	// R, Receiver Buffer Register (DLAB = 0)

#define	HwUART2_THR							*(volatile unsigned long *)0xF0055200	// W, Transmitter Holding Register (DLAB = 0)

#define	HwUART2_DLL								*(volatile unsigned long *)0xF0055200	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART2_DLM							*(volatile unsigned long *)0xF0055204	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART2_IER								*(volatile unsigned long *)0xF0055204	// R/W, Interrupt Enable Register (DLAB = 0)
	#define	HwUART2_IER_EMSI_EN					Hw3								// Enable Modem status interrupt
	#define	HwUART2_IER_EMSI_DIS					~Hw3							// Disable Modem status interrupt
	#define	HwUART2_IER_ELSI_EN						Hw2								// Enable receiver line status interrupt
	#define	HwUART2_IER_ELSI_DIS					~Hw2							// Disable receiver line status interrupt
	#define	HwUART2_IER_ETXI_EN						Hw1								// Enable transmitter holding register empty interrupt
	#define	HwUART2_IER_ETXI_DIS					~Hw1							// Disable transmitter holding register empty interrupt
	#define	HwUART2_IER_ERXI_EN						Hw0								// Enable received data available interrupt
	#define	HwUART2_IER_ERXI_DIS					~Hw0							// Disable received data available interrupt

#define	HwUART2_IIR								*(volatile unsigned long *)0xF0055208	// R, Interrupt Ident. Register (DLAB = 0)
	#define	HwUART2_IIR_STF							Hw27							// 1:TX is done (SmartCard TX done flag)
	#define	HwUART2_IIR_IPF							Hw0								// 1:Interrupt has not generated, 0:Interrupt pending

#define	HwUART2_FCR							*(volatile unsigned long *)0xF0055208	// W, FIFO Control Register (DLAB = 1)
	#define	HwUART2_FCR_RXT_1						~(Hw7+Hw6)						// RX FIFO Trigger Level 1byte
	#define	HwUART2_FCR_RXT_4						Hw6								// RX FIFO Trigger Level 4bytes
	#define	HwUART2_FCR_RXT_8						Hw7								// RX FIFO Trigger Level 8bytes
	#define	HwUART2_FCR_RXT_14						(Hw7+Hw6)						// RX FIFO Trigger Level 16bytes
	#define	HwUART2_FCR_DMS_EN					Hw3								// DMA Mode Enabled
	#define	HwUART2_FCR_DMS_DIS					~Hw3							// DMA Mode Disabled
	#define	HwUART2_FCR_TXFR_EN					Hw2								// Reset TX FIFO counter and FIFO Data
	#define	HwUART2_FCR_TXFR_DIS					~Hw2							//
	#define	HwUART2_FCR_RXFR_EN					Hw1								// Reset RX FIFO counter and FIFO Data
	#define	HwUART2_FCR_RXFR_DIS					~Hw1							//
	#define	HwUART2_FCR_FE_EN						Hw0								// Enable TX and RX FIFOs
	#define	HwUART2_FCR_FE_DIS						~Hw0							// Disable TX and RX FIFOs

#define	HwUART2_LCR							*(volatile unsigned long *)0xF005520C	// R/W, Line Control Register
	#define	HwUART2_LCR_DLAB_ON					Hw7								// Access the divisor latches of the baud generator
	#define	HwUART2_LCR_DLAB_OFF					~Hw7							// Access the receiver buff, the transmitter holding register, or the interrupt enable register
	#define	HwUART2_LCR_SB_ON						Hw6								// The serial output is forced to the spacing (logic 0) state
	#define	HwUART2_LCR_SB_OFF						~Hw6							// Disable the break
	#define	HwUART2_LCR_SP_ON						Hw5								// When bits 3, 4 and 5 are logic 1 the parity bits is transmitted and checked as a logic 0. If bits 3 and 5 are 1 and bit 4 is a logic 0 then the parity bit is transmitted and checked as a logic 1
	#define	HwUART2_LCR_SP_OFF						~Hw5							// Disable stick parity
	#define	HwUART2_LCR_EPS_EVEN					Hw4								// Generate or check even parity
	#define	HwUART2_LCR_EPS_ODD					~Hw4							// Generate or check odd parity
	#define	HwUART2_LCR_PEN_ON						Hw3								// A parity bit is generated (TX) or Checked (RX)
	#define	HwUART2_LCR_PEN_OFF					~Hw3							// Disabled
	#define	HwUART2_LCR_STB_ONE					Hw2								// One stop bit is generated in the transmitted data
	#define	HwUART2_LCR_STB_WLS					~Hw2							// When 5bit word length is selected, one and a half stop bits are generated. When either a 6-, 7-, or 8-bit word length is selected, two stop bits are generated.
	#define	HwUART2_LCR_WLS_5						~(Hw1+Hw0)						// 5 bits word length
	#define	HwUART2_LCR_WLS_6						Hw0								// 6 bits word length
	#define	HwUART2_LCR_WLS_7						Hw1								// 7 bits word length
	#define	HwUART2_LCR_WLS_8						(Hw1+Hw0)						// 8 bits word length

#define	HwUART2_MCR							*(volatile unsigned long *)0xF0055210	// R/W, MODEM Control Register
	#define	HwUART2_MCR_LOOP_ON					Hw4								// Loop Back Enable
	#define	HwUART2_MCR_LOOP_OFF					~Hw4							// Loop Back Disable
	#define	HwUART2_MCR_RTS						Hw1								// This bit informs the external modem that the uart is ready to exchange data

#define	HwUART2_LSR							*(volatile unsigned long *)0xF0055214	// R, Line Status Register
	#define	HwUART2_LSR_ERF_FIFO					Hw7								// In the FIFO mode this bit is set when there is at least one parity error, framing error or break indication in the FIFO
	#define	HwUART2_LSR_ERF_16450					~Hw7							// In the 16450 mode
	#define	HwUART2_LSR_TEMT_ON					Hw6								// Transmitter holding register and the transmitter shift register are both empty
	#define	HwUART2_LSR_TEMT_OFF					~Hw6							//
	#define	HwUART2_LSR_THRE_ON					Hw5								// UART is ready to accept a new char for transmission
	#define	HwUART2_LSR_THRE_OFF					~Hw5							//
	#define	HwUART2_LSR_BI_ON						Hw4								// The received data input is held in the spacing (logic 0) state for longer than a full word transmission time
	#define	HwUART2_LSR_BI_OFF						~Hw4							//
	#define	HwUART2_LSR_FE_ON						Hw3								// The received character did not have a valid stop bit
	#define	HwUART2_LSR_FE_OFF						~Hw3							//
	#define	HwUART2_LSR_PE_ON						Hw2								// The received data character does not have the correct even or odd parity
	#define	HwUART2_LSR_PE_OFF						~Hw2							//
	#define	HwUART2_LSR_OE_ON						Hw1								// The receiver buffer register was not read by the CPU before the next character was transferred into the receiver buffer register
	#define	HwUART2_LSR_OE_OFF						~Hw1							//
	#define	HwUART2_LSR_DR_ON						Hw0								// The receiver data ready
	#define	HwUART2_LSR_DR_OFF						~Hw0							//

#define	HwUART2_MSR							*(volatile unsigned long *)0xF0055218	// R, MODEM Status Register
	#define	HwUART2_MSR_CTS						Hw4								// This bit is the complement of the Claer to Send input
	#define	HwUART2_MSR_DCTS						Hw0								// This bit is the Delta Clear to Send indicator

#define	HwUART2_SCR							*(volatile unsigned long *)0xF005521C	// R/W, Scratch Register
																					// This 8bit Read/Write Register does not control the UART in anyway. It is intended as a scratch pad register to be used by the programmer to hold data temporarily

#define	HwUART2_AFT								*(volatile unsigned long *)0xF0055220	// R/W, AFC Trigger Level Register

#define	HwUART2_UCR							*(volatile unsigned long *)0xF0055224	// R/W, UART Control Register

#define	HwUART2_SRBR							*(volatile unsigned long *)0xF0055240	// R, Same as RBR except not affected by DLAB bit

#define	HwUART2_STHR							*(volatile unsigned long *)0xF0055244	// W, Same as THR except not affected by DLAB bit

#define	HwUART2_SDLL							*(volatile unsigned long *)0xF0055248	// R/W, Same as DLL except not affected by DLAB bit

#define	HwUART2_SDLM							*(volatile unsigned long *)0xF005524C	// R/W, Same as DLM except not affected by DLAB bit

#define	HwUART2_SIER							*(volatile unsigned long *)0xF0055250	// R/W, Same as IER except not affected by DLAB bit

#define	HwUART2_SCCR							*(volatile unsigned long *)0xF0055260	// R/W, SmartCard Control Register

#define	HwUART2_STC							*(volatile unsigned long *)0xF0055264	// R/W, SmartCard TX Count Register

#define	HwUART2_IRCFG							*(volatile unsigned long *)0xF0055280	// R/W, IRDA Configuration Register

/***********************************************************************
*	UART3 Controller Register Define			(Base Addr = 0xF0055300)
************************************************************************/
#define	HwUART3_BASE							*(volatile unsigned long *)0xF0055300	// UART 3 Base Register

#define	HwUART3_RBR							*(volatile unsigned long *)0xF0055300	// R, Receiver Buffer Register (DLAB = 0)

#define	HwUART3_THR							*(volatile unsigned long *)0xF0055300	// W, Transmitter Holding Register (DLAB = 0)

#define	HwUART3_DLL								*(volatile unsigned long *)0xF0055300	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART3_DLM							*(volatile unsigned long *)0xF0055304	// R/W, Divisor Latch Register (DLAB = 1)

#define	HwUART3_IER								*(volatile unsigned long *)0xF0055304	// R/W, Interrupt Enable Register (DLAB = 0)
	#define	HwUART3_IER_EMSI_EN					Hw3								// Enable Modem status interrupt
	#define	HwUART3_IER_EMSI_DIS					~Hw3							// Disable Modem status interrupt
	#define	HwUART3_IER_ELSI_EN						Hw2								// Enable receiver line status interrupt
	#define	HwUART3_IER_ELSI_DIS					~Hw2							// Disable receiver line status interrupt
	#define	HwUART3_IER_ETXI_EN						Hw1								// Enable transmitter holding register empty interrupt
	#define	HwUART3_IER_ETXI_DIS					~Hw1							// Disable transmitter holding register empty interrupt
	#define	HwUART3_IER_ERXI_EN						Hw0								// Enable received data available interrupt
	#define	HwUART3_IER_ERXI_DIS					~Hw0							// Disable received data available interrupt

#define	HwUART3_IIR								*(volatile unsigned long *)0xF0055308	// R, Interrupt Ident. Register (DLAB = 0)
	#define	HwUART3_IIR_STF							Hw27							// 1:TX is done (SmartCard TX done flag)
	#define	HwUART3_IIR_IPF							Hw0								// 1:Interrupt has not generated, 0:Interrupt pending

#define	HwUART3_FCR							*(volatile unsigned long *)0xF0055308	// W, FIFO Control Register (DLAB = 1)
	#define	HwUART3_FCR_RXT_1						~(Hw7+Hw6)						// RX FIFO Trigger Level 1byte
	#define	HwUART3_FCR_RXT_4						Hw6								// RX FIFO Trigger Level 4bytes
	#define	HwUART3_FCR_RXT_8						Hw7								// RX FIFO Trigger Level 8bytes
	#define	HwUART3_FCR_RXT_14						(Hw7+Hw6)						// RX FIFO Trigger Level 16bytes
	#define	HwUART3_FCR_DMS_EN					Hw3								// DMA Mode Enabled
	#define	HwUART3_FCR_DMS_DIS					~Hw3							// DMA Mode Disabled
	#define	HwUART3_FCR_TXFR_EN					Hw2								// Reset TX FIFO counter and FIFO Data
	#define	HwUART3_FCR_TXFR_DIS					~Hw2							//
	#define	HwUART3_FCR_RXFR_EN					Hw1								// Reset RX FIFO counter and FIFO Data
	#define	HwUART3_FCR_RXFR_DIS					~Hw1							//
	#define	HwUART3_FCR_FE_EN						Hw0								// Enable TX and RX FIFOs
	#define	HwUART3_FCR_FE_DIS						~Hw0							// Disable TX and RX FIFOs

#define	HwUART3_LCR							*(volatile unsigned long *)0xF005530C	// R/W, Line Control Register
	#define	HwUART3_LCR_DLAB_ON					Hw7								// Access the divisor latches of the baud generator
	#define	HwUART3_LCR_DLAB_OFF					~Hw7							// Access the receiver buff, the transmitter holding register, or the interrupt enable register
	#define	HwUART3_LCR_SB_ON						Hw6								// The serial output is forced to the spacing (logic 0) state
	#define	HwUART3_LCR_SB_OFF						~Hw6							// Disable the break
	#define	HwUART3_LCR_SP_ON						Hw5								// When bits 3, 4 and 5 are logic 1 the parity bits is transmitted and checked as a logic 0. If bits 3 and 5 are 1 and bit 4 is a logic 0 then the parity bit is transmitted and checked as a logic 1
	#define	HwUART3_LCR_SP_OFF						~Hw5							// Disable stick parity
	#define	HwUART3_LCR_EPS_EVEN					Hw4								// Generate or check even parity
	#define	HwUART3_LCR_EPS_ODD					~Hw4							// Generate or check odd parity
	#define	HwUART3_LCR_PEN_ON						Hw3								// A parity bit is generated (TX) or Checked (RX)
	#define	HwUART3_LCR_PEN_OFF					~Hw3							// Disabled
	#define	HwUART3_LCR_STB_ONE					Hw2								// One stop bit is generated in the transmitted data
	#define	HwUART3_LCR_STB_WLS					~Hw2							// When 5bit word length is selected, one and a half stop bits are generated. When either a 6-, 7-, or 8-bit word length is selected, two stop bits are generated.
	#define	HwUART3_LCR_WLS_5						~(Hw1+Hw0)						// 5 bits word length
	#define	HwUART3_LCR_WLS_6						Hw0								// 6 bits word length
	#define	HwUART3_LCR_WLS_7						Hw1								// 7 bits word length
	#define	HwUART3_LCR_WLS_8						(Hw1+Hw0)						// 8 bits word length

#define	HwUART3_MCR							*(volatile unsigned long *)0xF0055310	// R/W, MODEM Control Register
	#define	HwUART3_MCR_LOOP_ON					Hw4								// Loop Back Enable
	#define	HwUART3_MCR_LOOP_OFF					~Hw4							// Loop Back Disable
	#define	HwUART3_MCR_RTS						Hw1								// This bit informs the external modem that the uart is ready to exchange data

#define	HwUART3_LSR							*(volatile unsigned long *)0xF0055314	// R, Line Status Register
	#define	HwUART3_LSR_ERF_FIFO					Hw7								// In the FIFO mode this bit is set when there is at least one parity error, framing error or break indication in the FIFO
	#define	HwUART3_LSR_ERF_16450					~Hw7							// In the 16450 mode
	#define	HwUART3_LSR_TEMT_ON					Hw6								// Transmitter holding register and the transmitter shift register are both empty
	#define	HwUART3_LSR_TEMT_OFF					~Hw6							//
	#define	HwUART3_LSR_THRE_ON					Hw5								// UART is ready to accept a new char for transmission
	#define	HwUART3_LSR_THRE_OFF					~Hw5							//
	#define	HwUART3_LSR_BI_ON						Hw4								// The received data input is held in the spacing (logic 0) state for longer than a full word transmission time
	#define	HwUART3_LSR_BI_OFF						~Hw4							//
	#define	HwUART3_LSR_FE_ON						Hw3								// The received character did not have a valid stop bit
	#define	HwUART3_LSR_FE_OFF						~Hw3							//
	#define	HwUART3_LSR_PE_ON						Hw2								// The received data character does not have the correct even or odd parity
	#define	HwUART3_LSR_PE_OFF						~Hw2							//
	#define	HwUART3_LSR_OE_ON						Hw1								// The receiver buffer register was not read by the CPU before the next character was transferred into the receiver buffer register
	#define	HwUART3_LSR_OE_OFF						~Hw1							//
	#define	HwUART3_LSR_DR_ON						Hw0								// The receiver data ready
	#define	HwUART3_LSR_DR_OFF						~Hw0							//

#define	HwUART3_MSR							*(volatile unsigned long *)0xF0055318	// R, MODEM Status Register
	#define	HwUART3_MSR_CTS						Hw4								// This bit is the complement of the Claer to Send input
	#define	HwUART3_MSR_DCTS						Hw0								// This bit is the Delta Clear to Send indicator

#define	HwUART3_SCR							*(volatile unsigned long *)0xF005531C	// R/W, Scratch Register
																					// This 8bit Read/Write Register does not control the UART in anyway. It is intended as a scratch pad register to be used by the programmer to hold data temporarily

#define	HwUART3_AFT								*(volatile unsigned long *)0xF0055320	// R/W, AFC Trigger Level Register

#define	HwUART3_UCR							*(volatile unsigned long *)0xF0055324	// R/W, UART Control Register

#define	HwUART3_SRBR							*(volatile unsigned long *)0xF0055340	// R, Same as RBR except not affected by DLAB bit

#define	HwUART3_STHR							*(volatile unsigned long *)0xF0055344	// W, Same as THR except not affected by DLAB bit

#define	HwUART3_SDLL							*(volatile unsigned long *)0xF0055348	// R/W, Same as DLL except not affected by DLAB bit

#define	HwUART3_SDLM							*(volatile unsigned long *)0xF005534C	// R/W, Same as DLM except not affected by DLAB bit

#define	HwUART3_SIER							*(volatile unsigned long *)0xF0055350	// R/W, Same as IER except not affected by DLAB bit

#define	HwUART3_SCCR							*(volatile unsigned long *)0xF0055360	// R/W, SmartCard Control Register

#define	HwUART3_STC							*(volatile unsigned long *)0xF0055364	// R/W, SmartCard TX Count Register

#define	HwUART3_IRCFG							*(volatile unsigned long *)0xF0055380	// R/W, IRDA Configuration Register

#define	HwUART_BASE(X)							*(volatile unsigned long *)(0xF0055000+(X)*0x100)
#define	HwUART_MAX_CH							4
#define	HwUART_CH0_BASE(X)						HwUART_BASE(0)
#define	HwUART_CH1_BASE(X)						HwUART_BASE(1)
#define	HwUART_CH2_BASE(X)						HwUART_BASE(2)
#define	HwUART_CH3_BASE(X)						HwUART_BASE(3)
/*
typedef volatile struct
{
	unsigned	RBR;
		#define	THR			RBR
		#define	DLL			RBR
		#define	UTRXD		RBR
		#define	UTTXD		RBR

	unsigned	IER;
		#define	DLM			IER
		#define	UTDL		IER

	unsigned	IIR;
		#define	UTIR		IIR
		#define	FCR			IIR

	unsigned	LCR;

	unsigned	MCR;

	unsigned	LSR;

	unsigned	MSR;

	unsigned	SCR;
	unsigned	AFT;
	unsigned	UCR;
	unsigned	_Dummy[(0x40-0x28)/4];
	unsigned	SRBR;
	unsigned	STHR;
	unsigned	SDLL;
	unsigned	SDLM;
	unsigned	SIER;
	unsigned	_Dummy2[(0x60-0x54)/4];
	unsigned	SCCR;
	unsigned	STC;
	unsigned	_Dummy3[(0x80-0x68)/4];
	unsigned	IRCFG;
} sHwUART;
*/
	#define	HwUART_IER_EMSI_EN				Hw3								// Enable Modem status interrupt
	#define	HwUART_IER_EMSI_DIS			~Hw3							// Disable Modem status interrupt
	#define	HwUART_IER_ELSI_EN				Hw2								// Enable receiver line status interrupt
	#define	HwUART_IER_ELSI_DIS				~Hw2							// Disable receiver line status interrupt
	#define	HwUART_IER_ETXI_EN				Hw1								// Enable transmitter holding register empty interrupt
	#define	HwUART_IER_ETXI_DIS				~Hw1							// Disable transmitter holding register empty interrupt
	#define	HwUART_IER_ERXI_EN				Hw0								// Enable received data available interrupt
	#define	HwUART_IER_ERXI_DIS				~Hw0							// Disable received data available interrupt

	#define	HwUART_IIR_STF					Hw27							// 1:TX is done (SmartCard TX done flag)
	#define	HwUART_IIR_IPF					Hw0								// 1:Interrupt has not generated, 0:Interrupt pending
	#define	HwUART_IID(X)					((X)*Hw1)
	#define	HwUART_IID_LSE					HwUART_IID(3)					// Line Status Error
	#define	HwUART_IID_RA					HwUART_IID(2)					// Received data Available
	#define	HwUART_IID_TOI					HwUART_IID(6)					// Character Time-Out Indication
	#define	HwUART_IID_THRE					HwUART_IID(1)					// Transmit Holding Register Empty
	#define	HwUART_IID_MDS					HwUART_IID(0)					// Modem Status
	#define	HwUART_IID_MASK				HwUART_IID(7)

	#define	HwUART_FCR_RXT_1				~(Hw7+Hw6)						// RX FIFO Trigger Level 1byte
	#define	HwUART_FCR_RXT_4				Hw6								// RX FIFO Trigger Level 4bytes
	#define	HwUART_FCR_RXT_8				Hw7								// RX FIFO Trigger Level 8bytes
	#define	HwUART_FCR_RXT_14				(Hw7+Hw6)						// RX FIFO Trigger Level 16bytes
	#define	HwUART_FCR_DMS_EN				Hw3								// DMA Mode Enabled
	#define	HwUART_FCR_DMS_DIS			~Hw3							// DMA Mode Disabled
	#define	HwUART_FCR_TXFR_EN				Hw2								// Reset TX FIFO counter and FIFO Data
	#define	HwUART_FCR_TXFR_DIS			~Hw2							//
	#define	HwUART_FCR_RXFR_EN				Hw1								// Reset RX FIFO counter and FIFO Data
	#define	HwUART_FCR_RXFR_DIS			~Hw1							//
	#define	HwUART_FCR_FE_EN				Hw0								// Enable TX and RX FIFOs
	#define	HwUART_FCR_FE_DIS				~Hw0							// Disable TX and RX FIFOs

	#define	HwUART_LCR_DLAB_ON				Hw7								// Access the divisor latches of the baud generator
	#define	HwUART_LCR_DLAB_OFF				~Hw7							// Access the receiver buff, the transmitter holding register, or the interrupt enable register
	#define	HwUART_LCR_SB_ON					Hw6								// The serial output is forced to the spacing (logic 0) state
	#define	HwUART_LCR_SB_OFF					~Hw6							// Disable the break
	#define	HwUART_LCR_SP_ON					Hw5								// When bits 3, 4 and 5 are logic 1 the parity bits is transmitted and checked as a logic 0. If bits 3 and 5 are 1 and bit 4 is a logic 0 then the parity bit is transmitted and checked as a logic 1
	#define	HwUART_LCR_SP_OFF					~Hw5							// Disable stick parity
	#define	HwUART_LCR_EPS_EVEN				Hw4								// Generate or check even parity
	#define	HwUART_LCR_EPS_ODD				~Hw4							// Generate or check odd parity
	#define	HwUART_LCR_PEN_ON					Hw3								// A parity bit is generated (TX) or Checked (RX)
	#define	HwUART_LCR_PEN_OFF					~Hw3							// Disabled
	#define	HwUART_LCR_STB_ONE					Hw2								// One stop bit is generated in the transmitted data
	#define	HwUART_LCR_STB_WLS				~Hw2							// When 5bit word length is selected, one and a half stop bits are generated. When either a 6-, 7-, or 8-bit word length is selected, two stop bits are generated.
	#define	HwUART_LCR_WLS_5					~(Hw1+Hw0)						// 5 bits word length
	#define	HwUART_LCR_WLS_6					Hw0								// 6 bits word length
	#define	HwUART_LCR_WLS_7					Hw1								// 7 bits word length
	#define	HwUART_LCR_WLS_8					(Hw1+Hw0)						// 8 bits word length

	#define	HwUART_MCR_RS_START				Hw6								// nRTS is deasserted at the RX Start Condition
	#define	HwUART_MCR_RS_STOP				HwZERO							// nRTS is deasserted at the RX Stop Condition
	#define	HwUART_MCR_AFE_EN					Hw5								// Auto Flow Control Enabled
	#define	HwUART_MCR_LOOP_ON				Hw4								// Loop Back Enable
	#define	HwUART_MCR_LOOP_OFF				HwZERO							// Loop Back Disable
	#define	HwUART_MCR_RTS						Hw1								// This bit informs the external modem that the uart is ready to exchange data

	#define	HwUART_LSR_ERF_FIFO					Hw7								// In the FIFO mode this bit is set when there is at least one parity error, framing error or break indication in the FIFO
	#define	HwUART_LSR_ERF_16450				~Hw7							// In the 16450 mode
	#define	HwUART_LSR_TEMT_ON					Hw6								// Transmitter holding register and the transmitter shift register are both empty
	#define	HwUART_LSR_TEMT_OFF				~Hw6							//
	#define	HwUART_LSR_THRE_ON					Hw5								// UART is ready to accept a new char for transmission
	#define	HwUART_LSR_THRE_OFF				~Hw5							//
	#define	HwUART_LSR_BI_ON					Hw4								// The received data input is held in the spacing (logic 0) state for longer than a full word transmission time
	#define	HwUART_LSR_BI_OFF					~Hw4							//
	#define	HwUART_LSR_FE_ON					Hw3								// The received character did not have a valid stop bit
	#define	HwUART_LSR_FE_OFF					~Hw3							//
	#define	HwUART_LSR_PE_ON					Hw2								// The received data character does not have the correct even or odd parity
	#define	HwUART_LSR_PE_OFF					~Hw2							//
	#define	HwUART_LSR_OE_ON					Hw1								// The receiver buffer register was not read by the CPU before the next character was transferred into the receiver buffer register
	#define	HwUART_LSR_OE_OFF					~Hw1							//
	#define	HwUART_LSR_DR_ON					Hw0								// The receiver data ready
	#define	HwUART_LSR_DR_OFF					~Hw0							//

	#define	HwUART_MSR_CTS						Hw4								// This bit is the complement of the Claer to Send input
	#define	HwUART_MSR_DCTS					Hw0								// This bit is the Delta Clear to Send indicator

#define	HwUARTC_BASE							*(volatile unsigned long *)0xF0055400	// UART Control Base Register

#define	HwUART_CHSEL							*(volatile unsigned long *)0xF0055400	// R/W, Channel Selection Register

#define	HwUART_CHST							*(volatile unsigned long *)0xF0055404	// R, Channel Status Register


/************************************************************************
*	GPSB(General Purpose Serial Bus) Define		(Base Addr = 0xF0057000)
************************************************************************/
#define	HwGPSB_CH0_BASE						*(volatile unsigned long *)0xF0057000
#define	HwGPSB_CH1_BASE						*(volatile unsigned long *)0xF0057100
#define	HwGPSB_CH2_BASE						*(volatile unsigned long *)0xF0057200
#define	HwGPSB_CH3_BASE						*(volatile unsigned long *)0xF0057300
#define	HwGPSB_BASE(X)							*(volatile unsigned long *)(0xF0057000+(X)*0x100)
#define	HwGPSB_MAX_CH							4

typedef	volatile struct {
	unsigned	PORT;
	unsigned	STAT;
	unsigned	INTEN;
	unsigned	MODE;
	unsigned	CTRL;
	unsigned	_Dummy1[(0x20-0x14)/4];

	unsigned	TXBASE;
	unsigned	RXBASE;
	unsigned	PACKET;

	unsigned	DMACTR;
	unsigned	DMASTR;
	unsigned	DMAICR;
} sHwGPSB;

	#define	HwGPSB_STAT_WOR					Hw8								// Write FIFO over-run error flag
	#define	HwGPSB_STAT_RUR					Hw7								// Read FIFO under-run error flag
	#define	HwGPSB_STAT_WUR					Hw6								// Write FIFO under-run error flag
	#define	HwGPSB_STAT_ROR					Hw5								// Read FIFO over-run error flag
	#define	HwGPSB_STAT_RF						Hw4								// Read FIFO full flag
	#define	HwGPSB_STAT_WE						Hw3								// Write FIFO empty flag
	#define	HwGPSB_STAT_RNE					Hw2								// Read FIFO not empty flag
	#define	HwGPSB_STAT_WTH					Hw1								// Wrtie FIFO valid entry count is under threshold
	#define	HwGPSB_STAT_RTH					Hw0								// Read FIFO valid entry increased over threshold

	#define	HwGPSB_INTEN_DW					Hw31							// DMA request enable for transmit FIFO
	#define	HwGPSB_INTEN_DR					Hw30							// DMA request enable for receive FIFO
	#define	HwGPSB_INTEN_SWD_BHW				Hw27							// Swap byte in half-word
	#define	HwGPSB_INTEN_SWD_HWW				Hw26							// Swap half-word in word
	#define	HwGPSB_INTEN_SRD_BHW				Hw25							// Swap byte in half-word
	#define	HwGPSB_INTEN_SRD_HWW				Hw24							// Swap half-word in word
	#define	HwGPSB_INTEN_CFGWTH(X)			((X)*Hw20)							// Write FIFO threshold for Interrupt or DMA Request
	#define	HwGPSB_INTEN_CFGWTH_MASK			HwGPSB_INTEN_CFGWTH(7)
	#define	HwGPSB_INTEN_CFGRTH(X)			((X)*Hw16)							// Read FIFO threshold for Interrupt or DMA Request
	#define	HwGPSB_INTEN_CFGRTH_MASK			HwGPSB_INTEN_CFGRTH(7)
	#define	HwGPSB_INTEN_RC					Hw15							// Clear status[8:0] at the end of read cycle
	#define	HwGPSB_INTEN_WOR					Hw8								// Write FIFO over-run error interrupt enable
	#define	HwGPSB_INTEN_RUR					Hw7								//Read FIFO under-run error flag interrupt enable
	#define	HwGPSB_INTEN_WUR					Hw6								// Write FIFO under-run error flag interrupt enable
	#define	HwGPSB_INTEN_ROR					Hw5								// Read FIFO over-run error flag interrupt enable
	#define	HwGPSB_INTEN_RF					Hw4								// Read FIFO full flag interrupt enable
	#define	HwGPSB_INTEN_WE					Hw3								// Write FIFO empty flag interrupt enable
	#define	HwGPSB_INTEN_RNE					Hw2								// Read FIFO not empty flag interrupt enable
	#define	HwGPSB_INTEN_WTH					Hw1								// Wrtie FIFO valid entry count is under threshold interrupt enable
	#define	HwGPSB_INTEN_RTH					Hw0								// Read FIFO valid entry increased over threshold interrupt enable

	#define	HwGPSB_MODE_DIVLDV(X)				((X)*Hw24)
	#define	HwGPSB_MODE_DIVLDV_MASK			HwGPSB_MODE_DIVLDV(255)
	#define	HwGPSB_MODE_TRE					Hw23							// Master recovery time (TRE+1)*SCKO
	#define	HwGPSB_MODE_THL					Hw22							// Master hold time (THL+1)*SCKO
	#define	HwGPSB_MODE_TSU					Hw21							// Master setup time (TSU+1)*SCKO
	#define	HwGPSB_MODE_PCS					Hw20							// Polarity control for CS(FRM) - Master Only
	#define	HwGPSB_MODE_PCS_HIGH				Hw20
	#define	HwGPSB_MODE_PCD					Hw19							// Polarity control for CMD(FRM)- Master Only
	#define	HwGPSB_MODE_PCD_HIGH				Hw19
	#define	HwGPSB_MODE_PWD					Hw18							// Polarity control for transmit data - Master Only
	#define	HwGPSB_MODE_PWD_RISE				Hw18
	#define	HwGPSB_MODE_PRD					Hw17							// Polarity control for receive data - Master Only
	#define	HwGPSB_MODE_PRD_FALL				Hw17
	#define	HwGPSB_MODE_PCK					Hw16							// Polarity control for serial clock
	#define	HwGPSB_MODE_CRF					Hw15							// Clear receive FIFO counter
	#define	HwGPSB_MODE_CWF					Hw14							// Clear transmit FIFO counter
	#define	HwGPSB_MODE_BWS(X)				((X)*Hw8)						// Bit width Selection.(BWS+1. Valid = 7~31)
	#define	HwGPSB_MODE_BWS_MASK				HwGPSB_MODE_BWS(31)
	#define	HwGPSB_MODE_SD					Hw7								// Data shift direction control
	#define	HwGPSB_MODE_LB						Hw6								// Data looop-back enable
	#define	HwGPSB_MODE_CTF					Hw4								// Continuous transfer mode enable
	#define	HwGPSB_MODE_EN					Hw3								// Operation enable
	#define	HwGPSB_MODE_SLV					Hw2								// Slave mode configuration
	#define	HwGPSB_MODE_MD_SPI				HwZERO							// SPI compatible
	#define	HwGPSB_MODE_MD_SSP				Hw0								// SSP Compatible

	#define	HwGPSB_CTRL_LCW					Hw31							// Last clock disable for write cycle
	#define	HwGPSB_CTRL_LCR					Hw30							// Last clock disable for read cycle
	#define	HwGPSB_CTRL_CMDEND(X)				((X)*Hw24)						// Command End Position
	#define	HwGPSB_CTRL_CMDEND_MASK			HwGPSB_CTRL_CMDEND(31)
	#define	HwGPSB_CTRL_CMDST(X)				((X)*Hw16)						// Command Start Position
	#define	HwGPSB_CTRL_CMDST_MASK			HwGPSB_CTRL_CMDST(31)
	#define	HwGPSB_CTRL_RDST(X)				((X)*Hw8)						// Read Start Position
	#define	HwGPSB_CTRL_RDST_MASK				HwGPSB_CTRL_RDST(31)
	#define	HwGPSB_CTRL_PLW					Hw7								// Polarity control for write command
	#define	HwGPSB_CTRL_PSW(X)					((X)*Hw0)						// Write Command Position
	#define	HwGPSB_CTRL_PSW_MASK				HwGPSB_CTRL_PSW(31)

	#define	HwGPSB_DMACTRL_DTE				Hw31							// Transmit DMA request enable
	#define	HwGPSB_DMACTRL_DRE				Hw30							// Receive DMA request enable
	#define	HwGPSB_DMACTRL_CT					Hw29							// Continuous mode enable
	#define	HwGPSB_DMACTRL_END				Hw28							// Byte endian mode register
	#define	HwGPSB_DMACTRL_MP					Hw19							// PID match mode register
	#define	HwGPSB_DMACTRL_MS					Hw18							// Sync byte match control register
	#define	HwGPSB_DMACTRL_TXAM(X)			((X)*Hw16)
	#define	HwGPSB_DMACTRL_TXAM_FIXED			HwGPSB_DMACTRL_TXAM(0)		// TX address is fixed to TXBASE
	#define	HwGPSB_DMACTRL_TXAM_SINGLE		HwGPSB_DMACTRL_TXAM(1)		// TX address is rolling within 1 packet range
	#define	HwGPSB_DMACTRL_TXAM_MULTI			HwGPSB_DMACTRL_TXAM(2)		// TX address is rolling within full packet range
	#define	HwGPSB_DMACTRL_TXAM_MASK			HwGPSB_DMACTRL_TXAM(3)
	#define	HwGPSB_DMACTRL_RXAM(X)			((X)*Hw14)
	#define	HwGPSB_DMACTRL_RXAM_FIXED			HwGPSB_DMACTRL_RXAM(0)		// RX address is fixed to RXBASE
	#define	HwGPSB_DMACTRL_RXAM_SINGLE		HwGPSB_DMACTRL_RXAM(1)		// RX address is rolling within 1 packet range
	#define	HwGPSB_DMACTRL_RXAM_MULTI			HwGPSB_DMACTRL_RXAM(2)		// RX address is rolling within full packet range
	#define	HwGPSB_DMACTRL_RXAM_MASK			HwGPSB_DMACTRL_RXAM(3)
	#define	HwGPSB_DMACTRL_MD_NOR			HwZERO							// normal mode
	#define	HwGPSB_DMACTRL_MD_MP2TS			Hw4								// MPEG2-TS mode
	#define	HwGPSB_DMACTRL_EN					Hw0								// DMA enable

	#define	HwGPSB_DMAICR_ISD					Hw29							// IRQ Status for "Done Interrupt"
	#define	HwGPSB_DMAICR_ISP					Hw28							// IRQ Status for "Packet Interrupt"
	#define	HwGPSB_DMAICR_IRQS_RCV			Hw27							// IRQ is generated when receiving is done.
	#define	HwGPSB_DMAICR_IRQS_TRANS			HwZERO							// IRQ is generated when transmit is done.
	#define	HwGPSB_DMAICR_IED_EN				Hw17							// Enable "Done Interrupt"
	#define	HwGPSB_DMAICR_IEP_EN				Hw16							// Enable "Packet Interrupt"
	#define	HwGPSB_DMAICR_IRQPCNT_MASK		(Hw13-1)

#define	HwGPSB0_BASE							*(volatile unsigned long *)0xF0057000	// GPSB 0 Base Register

#define	HwGPSB_CH0PORT							*(volatile unsigned long *)0xF0057000	// R/W, Data Port

#define	HwGPSB_CH0STAT							*(volatile unsigned long *)0xF0057004	// R/W, Status Register
	#define	HwGPSB_CH0STAT_WOR					Hw8								// Write FIFO over-run error flag
	#define	HwGPSB_CH0STAT_RUR					Hw7								// Read FIFO under-run error flag
	#define	HwGPSB_CH0STAT_WUR					Hw6								// Write FIFO under-run error flag
	#define	HwGPSB_CH0STAT_ROR					Hw5								// Read FIFO over-run error flag
	#define	HwGPSB_CH0STAT_RF						Hw4								// Read FIFO full flag
	#define	HwGPSB_CH0STAT_WE						Hw3								// Write FIFO empty flag
	#define	HwGPSB_CH0STAT_RNE					Hw2								// Read FIFO not empty flag
	#define	HwGPSB_CH0STAT_WTH					Hw1								// Wrtie FIFO valid entry count is under threshold
	#define	HwGPSB_CH0STAT_RTH					Hw0								// Read FIFO valid entry increased over threshold

#define	HwGPSB_CH0INTEN						*(volatile unsigned long *)0xF0057008	// R/W, Interrupt Enable
	#define	HwGPSB_CH0INTEN_DW					Hw31							// DMA request enable for transmit FIFO
	#define	HwGPSB_CH0INTEN_DR						Hw30							// DMA request enable for receive FIFO
	#define	HwGPSB_CH0INTEN_SWD_BHW				Hw27							// Swap byte in half-word
	#define	HwGPSB_CH0INTEN_SWD_HWW				Hw26							// Swap half-word in word
	#define	HwGPSB_CH0INTEN_SRD_BHW				Hw25							// Swap byte in half-word
	#define	HwGPSB_CH0INTEN_SRD_HWW				Hw24							// Swap half-word in word
	#define	HwGPSB_CH0INTEN_RC						Hw15							// Clear status[8:0] at the end of read cycle
	#define	HwGPSB_CH0INTEN_WOR					Hw8								// Write FIFO over-run error interrupt enable
	#define	HwGPSB_CH0INTEN_RUR					Hw7								//Read FIFO under-run error flag interrupt enable
	#define	HwGPSB_CH0INTEN_WUR					Hw6								// Write FIFO under-run error flag interrupt enable
	#define	HwGPSB_CH0INTEN_ROR					Hw5								// Read FIFO over-run error flag interrupt enable
	#define	HwGPSB_CH0INTEN_RF						Hw4								// Read FIFO full flag interrupt enable
	#define	HwGPSB_CH0INTEN_WE					Hw3								// Write FIFO empty flag interrupt enable
	#define	HwGPSB_CH0INTEN_RNE					Hw2								// Read FIFO not empty flag interrupt enable
	#define	HwGPSB_CH0INTEN_WTH					Hw1								// Wrtie FIFO valid entry count is under threshold interrupt enable
	#define	HwGPSB_CH0INTEN_RTH					Hw0								// Read FIFO valid entry increased over threshold interrupt enable

#define	HwGPSB_CH0MODE						*(volatile unsigned long *)0xF005700C	// R/W, Mode Register
	#define	HwGPSB_CH0MODE_TRE					Hw23							// Master recovery time
	#define	HwGPSB_CH0MODE_THL					Hw22							// Master hold time
	#define	HwGPSB_CH0MODE_TSU					Hw21							// Master setup time
	#define	HwGPSB_CH0MODE_PCS					Hw20							// Polarity control for CS(FRM) - Master Only
	#define	HwGPSB_CH0MODE_PCD					Hw19							// Polarity control for CMD(FRM)- Master Only
	#define	HwGPSB_CH0MODE_PWD					Hw18							// Polarity control for transmit data - Master Only
	#define	HwGPSB_CH0MODE_PRD					Hw17							// Polarity control for receive data - Master Only
	#define	HwGPSB_CH0MODE_PCK					Hw16							// Polarity control for serial clock
	#define	HwGPSB_CH0MODE_CRF					Hw15							// Clear receive FIFO counter
	#define	HwGPSB_CH0MODE_CWF					Hw14							// Clear transmit FIFO counter
	#define	HwGPSB_CH0MODE_SD						Hw7								// Data shift direction control
	#define	HwGPSB_CH0MODE_LB						Hw6								// Data looop-back enable
	#define	HwGPSB_CH0MODE_CTF					Hw4								// Continuous transfer mode enable
	#define	HwGPSB_CH0MODE_EN						Hw3								// Operation enable
	#define	HwGPSB_CH0MODE_SLV					Hw2								// Slave mode configuration
	#define	HwGPSB_CH0MODE_MD_SPI					HwZERO							// SPI compatible
	#define	HwGPSB_CH0MODE_MD_SSP				Hw0								// SSP Compatible

#define	HwGPSB_CH0CTRL							*(volatile unsigned long *)0xF0057010	// R/W, Control Register
	#define	HwGPSB_CH0CTRL_LCW					Hw31							// Last clock disable for write cycle
	#define	HwGPSB_CH0CTRL_LCR					Hw30							// Last clock disable for read cycle
	#define	HwGPSB_CH0CTRL_PLW					Hw7								// Polarity control for write command

#define	HwGPSB_CH0TXBASE						*(volatile unsigned long *)0xF0057020	// R/W, TX base address register

#define	HwGPSB_CH0RXBASE						*(volatile unsigned long *)0xF0057024	// R/W, RX base address register

#define	HwGPSB_CH0PACKET						*(volatile unsigned long *)0xF0057028	// R/W, Packet register

#define	HwGPSB_CH0DMACTRL						*(volatile unsigned long *)0xF005702C	// R/W, DMA control register
	#define	HwGPSB_CH0DMACTRL_DTE					Hw31							// Transmit DMA request enable
	#define	HwGPSB_CH0DMACTRL_DRE					Hw30							// Receive DMA request enable
	#define	HwGPSB_CH0DMACTRL_CT					Hw29							// Continuous mode enable
	#define	HwGPSB_CH0DMACTRL_END					Hw28							// Byte endian mode register
	#define	HwGPSB_CH0DMACTRL_MP					Hw19							// PID match mode register
	#define	HwGPSB_CH0DMACTRL_MS					Hw18							// Sync byte match control register
	#define	HwGPSB_CH0DMACTRL_IS					Hw11							// IRQ mode selection
	#define	HwGPSB_CH0DMACTRL_MD_NOR				HwZERO							// normal mode
	#define	HwGPSB_CH0DMACTRL_MD_MP2TS			Hw4								// MPEG2-TS mode
	#define	HwGPSB_CH0DMACTRL_IEN					Hw1								// Interrupt enable
	#define	HwGPSB_CH0DMACTRL_EN					Hw0								// DMA enable

#define	HwGPSB_CH0DMASTAT						*(volatile unsigned long *)0xF0057030	// R/W, DMA status register

#define	HwGPSB_CH0DMAICR						*(volatile unsigned long *)0xF0057034	// R/W, DMA IRQ register

#define	HwGPSB1_BASE							*(volatile unsigned long *)0xF0057100	// GPSB 1 Base Register

#define	HwGPSB_CH1PORT							*(volatile unsigned long *)0xF0057100	// R/W, Data Port

#define	HwGPSB_CH1STAT							*(volatile unsigned long *)0xF0057104	// R/W, Status Register
	#define	HwGPSB_CH1STAT_WOR					Hw8								// Write FIFO over-run error flag
	#define	HwGPSB_CH1STAT_RUR					Hw7								// Read FIFO under-run error flag
	#define	HwGPSB_CH1STAT_WUR					Hw6								// Write FIFO under-run error flag
	#define	HwGPSB_CH1STAT_ROR					Hw5								// Read FIFO over-run error flag
	#define	HwGPSB_CH1STAT_RF						Hw4								// Read FIFO full flag
	#define	HwGPSB_CH1STAT_WE						Hw3								// Write FIFO empty flag
	#define	HwGPSB_CH1STAT_RNE					Hw2								// Read FIFO not empty flag
	#define	HwGPSB_CH1STAT_WTH					Hw1								// Wrtie FIFO valid entry count is under threshold
	#define	HwGPSB_CH1STAT_RTH					Hw0								// Read FIFO valid entry increased over threshold

#define	HwGPSB_CH1INTEN						*(volatile unsigned long *)0xF0057108	// R/W, Interrupt Enable
	#define	HwGPSB_CH1INTEN_DW					Hw31							// DMA request enable for transmit FIFO
	#define	HwGPSB_CH1INTEN_DR						Hw30							// DMA request enable for receive FIFO
	#define	HwGPSB_CH1INTEN_SWD_BHW				Hw27							// Swap byte in half-word
	#define	HwGPSB_CH1INTEN_SWD_HWW				Hw26							// Swap half-word in word
	#define	HwGPSB_CH1INTEN_SRD_BHW				Hw25							// Swap byte in half-word
	#define	HwGPSB_CH1INTEN_SRD_HWW				Hw24							// Swap half-word in word
	#define	HwGPSB_CH1INTEN_RC						Hw15							// Clear status[8:0] at the end of read cycle
	#define	HwGPSB_CH1INTEN_WOR					Hw8								// Write FIFO over-run error interrupt enable
	#define	HwGPSB_CH1INTEN_RUR					Hw7								//Read FIFO under-run error flag interrupt enable
	#define	HwGPSB_CH1INTEN_WUR					Hw6								// Write FIFO under-run error flag interrupt enable
	#define	HwGPSB_CH1INTEN_ROR					Hw5								// Read FIFO over-run error flag interrupt enable
	#define	HwGPSB_CH1INTEN_RF						Hw4								// Read FIFO full flag interrupt enable
	#define	HwGPSB_CH1INTEN_WE					Hw3								// Write FIFO empty flag interrupt enable
	#define	HwGPSB_CH1INTEN_RNE					Hw2								// Read FIFO not empty flag interrupt enable
	#define	HwGPSB_CH1INTEN_WTH					Hw1								// Wrtie FIFO valid entry count is under threshold interrupt enable
	#define	HwGPSB_CH1INTEN_RTH					Hw0								// Read FIFO valid entry increased over threshold interrupt enable

#define	HwGPSB_CH1MODE						*(volatile unsigned long *)0xF005710C	// R/W, Mode Register
	#define	HwGPSB_CH1MODE_TRE					Hw23							// Master recovery time
	#define	HwGPSB_CH1MODE_THL					Hw22							// Master hold time
	#define	HwGPSB_CH1MODE_TSU					Hw21							// Master setup time
	#define	HwGPSB_CH1MODE_PCS					Hw20							// Polarity control for CS(FRM) - Master Only
	#define	HwGPSB_CH1MODE_PCD					Hw19							// Polarity control for CMD(FRM)- Master Only
	#define	HwGPSB_CH1MODE_PWD					Hw18							// Polarity control for transmit data - Master Only
	#define	HwGPSB_CH1MODE_PRD					Hw17							// Polarity control for receive data - Master Only
	#define	HwGPSB_CH1MODE_PCK					Hw16							// Polarity control for serial clock
	#define	HwGPSB_CH1MODE_CRF					Hw15							// Clear receive FIFO counter
	#define	HwGPSB_CH1MODE_CWF					Hw14							// Clear transmit FIFO counter
	#define	HwGPSB_CH1MODE_SD						Hw7								// Data shift direction control
	#define	HwGPSB_CH1MODE_LB						Hw6								// Data looop-back enable
	#define	HwGPSB_CH1MODE_CTF					Hw4								// Continuous transfer mode enable
	#define	HwGPSB_CH1MODE_EN						Hw3								// Operation enable
	#define	HwGPSB_CH1MODE_SLV					Hw2								// Slave mode configuration
	#define	HwGPSB_CH1MODE_MD_SPI					HwZERO							// SPI compatible
	#define	HwGPSB_CH1MODE_MD_SSP				Hw0								// SSP Compatible

#define	HwGPSB_CH1CTRL							*(volatile unsigned long *)0xF0057110	// R/W, Control Register
	#define	HwGPSB_CH1CTRL_LCW					Hw31							// Last clock disable for write cycle
	#define	HwGPSB_CH1CTRL_LCR					Hw30							// Last clock disable for read cycle
	#define	HwGPSB_CH1CTRL_PLW					Hw7								// Polarity control for write command

#define	HwGPSB_CH1TXBASE						*(volatile unsigned long *)0xF0057120	// R/W, TX base address register

#define	HwGPSB_CH1RXBASE						*(volatile unsigned long *)0xF0057124	// R/W, RX base address register

#define	HwGPSB_CH1PACKET						*(volatile unsigned long *)0xF0057128	// R/W, Packet register

#define	HwGPSB_CH1DMACTRL						*(volatile unsigned long *)0xF005712C	// R/W, DMA control register
	#define	HwGPSB_CH1DMACTRL_DTE					Hw31							// Transmit DMA request enable
	#define	HwGPSB_CH1DMACTRL_DRE					Hw30							// Receive DMA request enable
	#define	HwGPSB_CH1DMACTRL_CT					Hw29							// Continuous mode enable
	#define	HwGPSB_CH1DMACTRL_END					Hw28							// Byte endian mode register
	#define	HwGPSB_CH1DMACTRL_MP					Hw19							// PID match mode register
	#define	HwGPSB_CH1DMACTRL_MS					Hw18							// Sync byte match control register
	#define	HwGPSB_CH1DMACTRL_IS					Hw11							// IRQ mode selection
	#define	HwGPSB_CH1DMACTRL_MD_NOR				HwZERO							// normal mode
	#define	HwGPSB_CH1DMACTRL_MD_MP2TS			Hw4								// MPEG2-TS mode
	#define	HwGPSB_CH1DMACTRL_IEN					Hw1								// Interrupt enable
	#define	HwGPSB_CH1DMACTRL_EN					Hw0								// DMA enable

#define	HwGPSB_CH1DMASTAT						*(volatile unsigned long *)0xF0057130	// R/W, DMA status register

#define	HwGPSB_CH1DMAICR						*(volatile unsigned long *)0xF0057134	// R/W, DMA IRQ register

#define	HwGPSB2_BASE							*(volatile unsigned long *)0xF0057200	// GPSB 2 Base Register

#define	HwGPSB_CH2PORT							*(volatile unsigned long *)0xF0057200	// R/W, Data Port

#define	HwGPSB_CH2STAT							*(volatile unsigned long *)0xF0057204	// R/W, Status Register

#define	HwGPSB_CH2INTEN						*(volatile unsigned long *)0xF0057208	// R/W, Interrupt Enable

#define	HwGPSB_CH2MODE						*(volatile unsigned long *)0xF005720C	// R/W, Mode Register

#define	HwGPSB_CH2CTRL							*(volatile unsigned long *)0xF0057210	// R/W, Control Register

#define	HwGPSB3_BASE							*(volatile unsigned long *)0xF0057300	// GPSB 3 Base Register

#define	HwGPSB_CH3PORT							*(volatile unsigned long *)0xF0057300	// R/W, Data Port

#define	HwGPSB_CH3STAT							*(volatile unsigned long *)0xF0057304	// R/W, Status Register

#define	HwGPSB_CH3INTEN						*(volatile unsigned long *)0xF0057308	// R/W, Interrupt Enable

#define	HwGPSB_CH3MODE						*(volatile unsigned long *)0xF005730C	// R/W, Mode Register

#define	HwGPSB_CH3CTRL							*(volatile unsigned long *)0xF0057310	// R/W, Control Register

#define	HwGPSBC_BASE							*(volatile unsigned long *)0xF0057800	// GPSB Control Base Register

#define	HwGPSB_PCFG							*(volatile unsigned long *)0xF0057800	// R/W, GPSB Port Configuration Register
#define	HwGPSB_PIDT							*(volatile unsigned long *)0xF0057F00	// R/W, PID Table Register

/***********************************************************************
*	 SD/MMC Controller Register Define			(Base Addr = 0xF0058000)
************************************************************************/
#define	HwSDMMC_CH0_BASE						*(volatile unsigned long *)0xF0058000	// R/W, SDMMC Channel 0 Base Register
#define	HwSDMMC_CH1_BASE						*(volatile unsigned long *)0xF0058100	// R/W, SDMMC Channel 1 Base Register
#define	HwSDMMC_BASE(X)						*(volatile unsigned long *)(0xF0058000+(X)*0x100)	// R/W, SDMMC Channel Base Register
typedef volatile struct
{
	unsigned	SDMA;				// R/W, SDMA System Address
	unsigned	BPARAM;				// R/W, Block Size & Count
		#define	HwSD_BPARAM_BCNT(X)				((X)*Hw16)						// Block Count for current transfer (Valid only in multiple block transfers)
		#define	HwSD_BPARAM_BCNT_MASK			HwSD_BPARAM_BCNT(65535)
		#define	HwSD_BPARAM_SDMABUF(X)			((X)*Hw12)
		#define	HwSD_BPARAM_SDMABUF_4KB			HwSD_BPARAM_SDMABUF(0)
		#define	HwSD_BPARAM_SDMABUF_8KB			HwSD_BPARAM_SDMABUF(1)
		#define	HwSD_BPARAM_SDMABUF_16KB			HwSD_BPARAM_SDMABUF(2)
		#define	HwSD_BPARAM_SDMABUF_32KB			HwSD_BPARAM_SDMABUF(3)
		#define	HwSD_BPARAM_SDMABUF_64KB			HwSD_BPARAM_SDMABUF(4)
		#define	HwSD_BPARAM_SDMABUF_128KB		HwSD_BPARAM_SDMABUF(5)
		#define	HwSD_BPARAM_SDMABUF_256KB		HwSD_BPARAM_SDMABUF(6)
		#define	HwSD_BPARAM_SDMABUF_512KB		HwSD_BPARAM_SDMABUF(7)
		#define	HwSD_BPARAM_SDMABUF_MASK			HwSD_BPARAM_SDMABUF(7)
		#define	HwSD_BPARAM_BSIZE(X)				((X)*Hw0)						// 0~2048 bytes
		#define	HwSD_BPARAM_BSIZE_512				HwSD_BPARAM_BSIZE(512)
		#define	HwSD_BPARAM_BSIZE_1KB				HwSD_BPARAM_BSIZE(1024)
		#define	HwSD_BPARAM_BSIZE_2KB				HwSD_BPARAM_BSIZE(2048)
		#define	HwSD_BPARAM_BSIZE_MASK			HwSD_BPARAM_BSIZE(4095)

	unsigned	ARG;				// R/W, Argument (specified as bit39~8 of Command Format)
	unsigned	TCMD;				// R/W, Command & Transfer Mode
		#define	HwSD_TCMD_CMDIDX(X)				((X)*Hw24)						// Command Index
		#define	HwSD_TCMD_CMDIDX_MASK			HwSD_TCMD_CMDIDX(63)
		#define	HwSD_TCMD_CTYPE(X)					((X)*Hw22)						// Suspend, Resume, Abort, Other
		#define	HwSD_TCMD_CTYPE_MASK				HwSD_TCMD_CTYPE(3)
		#define	HwSD_TCMD_DATSEL_PRESENT			Hw21							// Data is present and shall be transferred
		#define	HwSD_TCMD_DATSEL_NODATA			HwZERO
		#define	HwSD_TCMD_CICHK_EN				Hw20							// Check the Index field in the response
		#define	HwSD_TCMD_CRCHK_EN				Hw19							// Check the CRC field in the response
		#define	HwSD_TCMD_RTYPE(X)					((X)*Hw16)						// Response Type
		#define	HwSD_TCMD_RTYPE_NORESP			HwSD_TCMD_RTYPE(0)			// No Response
		#define	HwSD_TCMD_RTYPE_R136				HwSD_TCMD_RTYPE(1)			// Response with 136 bytes
		#define	HwSD_TCMD_RTYPE_R48				HwSD_TCMD_RTYPE(2)			// Response with 48 bytes
		#define	HwSD_TCMD_RTYPE_R48CHK			HwSD_TCMD_RTYPE(3)			// Response with 48 bytes - check Busy after response
		#define	HwSD_TCMD_SPI_MODE				Hw7								// SPI Mode
		#define	HwSD_TCMD_SD_MODE				HwZERO							// SD Mode
		#define	HwSD_TCMD_ATACMD					Hw6								// CE-ATA Mode (Device will send Command Completion Signal)
		#define	HwSD_TCMD_MS_MULTI				Hw5								// Multiple Block Mode
		#define	HwSD_TCMD_MS_SINGLE				HwZERO							// Single Block Mode
		#define	HwSD_TCMD_DIR_READ				Hw4								// Read Mode (Transfer from Card to Host)
		#define	HwSD_TCMD_DIR_WRITE				HwZERO							// Write Mode (Transfer from Host to Card)
		#define	HwSD_TCMD_ACMD12_EN				Hw2								// CMD12 is issued automatically after last block transfer is completed.
		#define	HwSD_TCMD_BCNTEN_EN				Hw1								// Enable Block Count Register (BCNT). only relevant for multiple block transfers
		#define	HwSD_TCMD_DMAEN_EN				Hw0								// DMA Enabled (can be enabled only if CA register tells it support DMA)

	unsigned	RESP[4];				// R, Response Words [127:0]
	unsigned	DATA;				// R/W, Buffer Data Port
	unsigned	STATE;				// R, Present State
		#define	HwSD_STATE_DAT7_HIGH				Hw28							// State of DAT7 line
		#define	HwSD_STATE_DAT6_HIGH				Hw27							// State of DAT6 line
		#define	HwSD_STATE_DAT5_HIGH				Hw26							// State of DAT5 line
		#define	HwSD_STATE_DAT4_HIGH				Hw25							// State of DAT4 line
		#define	HwSD_STATE_CMD_HIGH				Hw24							// State of CMD line
		#define	HwSD_STATE_DAT3_HIGH				Hw23							// State of DAT3 line
		#define	HwSD_STATE_DAT2_HIGH				Hw22							// State of DAT2 line
		#define	HwSD_STATE_DAT1_HIGH				Hw21							// State of DAT1 line
		#define	HwSD_STATE_DAT0_HIGH				Hw20							// State of DAT0 line
		#define	HwSD_STATE_SDWP_HIGH				Hw19							// State of WP line
		#define	HwSD_STATE_SDCD_DET				Hw18							// Inverse State of CD# line (Card Detected State)
		#define	HwSD_STATE_CDST_STABLE			Hw17							// Card Detect Pin level is stable
		#define	HwSD_STATE_CDIN_INSERT				Hw16							// Card has been inserted
		#define	HwSD_STATE_RDEN_EN					Hw11							// Buffer Read Enable (Readable data exist in the buffer)
		#define	HwSD_STATE_WREN_EN				Hw10							// Buffer Write Enable (Data can be written to the buffer)
		#define	HwSD_STATE_RDACT_ACTIVE			Hw9								// Read transfer is active
		#define	HwSD_STATE_WRACT_ACTIVE			Hw8								// Write transfer is active
		#define	HwSD_STATE_DATACT_ACTIVE			Hw2								// DAT[7:0] line on SD bus is in use
		#define	HwSD_STATE_NODAT_INHIBIT			Hw1								// DAT line or Read Transfer is active (No Command using DAT is allowed)
		#define	HwSD_STATE_NOCMD_INHIBIT			Hw0								// CMD line is in use (No Command is allowed)

	unsigned	CTRL;				// R/W, (Power, Host, Wakeup, Block Gap) Control
		#define	HwSD_CTRL_WKOUT_EN				Hw26							// Enable Wakeup event on Card Removal
		#define	HwSD_CTRL_WKIN_EN					Hw25							// Enable Wakeup event on Card Insertion
		#define	HwSD_CTRL_WKINT_EN					Hw24							// Enable Wakeup event on Card Interrupt
		#define	HwSD_CTRL_BGINT_EN					Hw19							// Enable interrupt detection at the block gap for multiple block transfer (valid only 4bit SDIO mode)
		#define	HwSD_CTRL_RDWAIT_EN				Hw18							// Enable use of read-wait protocol to stop read data using DAT2 line
		#define	HwSD_CTRL_CONREQ_EN				Hw17							// Restart a transaction that was stopped by BGSTOP request
		#define	HwSD_CTRL_BGSTOP_EN				Hw16							// Executing transaction stops at the next block gap for non-DMA, SDMA, ADMA transfers.
		#define	HwSD_CTRL_VOLTSEL(X)				((X)*Hw9)						// Selects voltage level for the SD Card
		#define	HwSD_CTRL_VOLTSEL_V33				HwSD_CTRL_VOLTSEL(7)			// 3.3V Flattop
		#define	HwSD_CTRL_VOLTSEL_V30				HwSD_CTRL_VOLTSEL(6)			// 3.0V (typical)
		#define	HwSD_CTRL_VOLTSEL_V18				HwSD_CTRL_VOLTSEL(5)			// 1.8V (typical)
		#define	HwSD_CTRL_VOLTSEL_MASK			HwSD_CTRL_VOLTSEL(7)
		#define	HwSD_CTRL_POW_ON					Hw8								// SD Bus Power On (VOLTSEL should be set ahead)
		#define	HwSD_CTRL_DETSEL_TST				Hw7								// Card detect test level is selected (test purpose only)
		#define	HwSD_CTRL_DETSEL_SDCD				HwZERO							// SDCD# line is selected (normal case)
		#define	HwSD_CTRL_SD8_EN					Hw5								// SD 8bit mode is selected
		#define	HwSD_CTRL_SELDMA(X)				((X)*Hw3)						// SD DMA Selection
		#define	HwSD_CTRL_SELDMA_SDMA				HwSD_CTRL_SELDMA(0)			// SDMA is selected
		#define	HwSD_CTRL_SELDMA_ADMA1			HwSD_CTRL_SELDMA(1)			// ADMA1 (32bit address) is selected
		#define	HwSD_CTRL_SELDMA_ADMA2_32			HwSD_CTRL_SELDMA(2)			// ADMA2 (32bit address) is selected
		#define	HwSD_CTRL_SELDMA_ADMA2_64			HwSD_CTRL_SELDMA(3)			// ADMA2 (64bit address) is selected
		#define	HwSD_CTRL_SELDMA_MASK				HwSD_CTRL_SELDMA(3)
		#define	HwSD_CTRL_HS_EN					Hw2								// Enable High Speed
		#define	HwSD_CTRL_SD4_EN					Hw1								// SD 4bit mode is selected
		#define	HwSD_CTRL_SD1_EN					HwZERO							// SD 1bit mode is selected
		#define	HwSD_CTRL_LED_ON					Hw0								// LED ON

	unsigned	CLK;				// R/W, Clock control / Reset & TimeOut Control
		#define	HwSD_CLK_RSTDAT_EN				Hw26							// SW Reset for DAT line
																					// DATA, STATE(RDEN, WREN, RDACT, WRACT, DATACT, NODAT) are cleared
																					// CTRL(CONREQ, BGSTOP), STS(RDRDY,WRRDY,BLKGAP,TDONE) are cleared
		#define	HwSD_CLK_RSTCMD_EN				Hw25							// SW Reset for CMD line
																					// STATE(NOCMD), STS(CDONE) are cleared
		#define	HwSD_CLK_RSTALL_EN					Hw24							// SW Reset for All (except Card Detection Circuit)
		#define	HwSD_CLK_TIMEOUT(X)				((X)*Hw16)						// Time Out Selection
		#define	HwSD_CLK_TIMEOUT_TM8K				HwSD_CLK_TIMEOUT(0)			// Timeout = TMCLK * 8K
		#define	HwSD_CLK_TIMEOUT_TM16K			HwSD_CLK_TIMEOUT(1)			// Timeout = TMCLK * 16K
		#define	HwSD_CLK_TIMEOUT_TM32K			HwSD_CLK_TIMEOUT(2)			// Timeout = TMCLK * 32K
		#define	HwSD_CLK_TIMEOUT_TM64K			HwSD_CLK_TIMEOUT(3)			// Timeout = TMCLK * 64K
		#define	HwSD_CLK_TIMEOUT_TM128K			HwSD_CLK_TIMEOUT(4)			// Timeout = TMCLK * 128K
		#define	HwSD_CLK_TIMEOUT_TM256K			HwSD_CLK_TIMEOUT(5)			// Timeout = TMCLK * 256K
		#define	HwSD_CLK_TIMEOUT_TM512K			HwSD_CLK_TIMEOUT(6)			// Timeout = TMCLK * 512K
		#define	HwSD_CLK_TIMEOUT_TM1M				HwSD_CLK_TIMEOUT(7)			// Timeout = TMCLK * 1M
		#define	HwSD_CLK_TIMEOUT_TM2M				HwSD_CLK_TIMEOUT(8)			// Timeout = TMCLK * 2M
		#define	HwSD_CLK_TIMEOUT_TM4M				HwSD_CLK_TIMEOUT(9)			// Timeout = TMCLK * 4M
		#define	HwSD_CLK_TIMEOUT_TM8M				HwSD_CLK_TIMEOUT(10)			// Timeout = TMCLK * 8M
		#define	HwSD_CLK_TIMEOUT_TM16M			HwSD_CLK_TIMEOUT(11)			// Timeout = TMCLK * 16M
		#define	HwSD_CLK_TIMEOUT_TM32M			HwSD_CLK_TIMEOUT(12)			// Timeout = TMCLK * 32M
		#define	HwSD_CLK_TIMEOUT_TM64M			HwSD_CLK_TIMEOUT(13)			// Timeout = TMCLK * 64M
		#define	HwSD_CLK_TIMEOUT_TM128M			HwSD_CLK_TIMEOUT(14)			// Timeout = TMCLK * 128M
		#define	HwSD_CLK_TIMEOUT_MASK				HwSD_CLK_TIMEOUT(15)
		#define	HwSD_CLK_SDCLKSEL(X)				((X)*Hw8)						// SDCLK Frequency Selection
		#define	HwSD_CLK_SDCLKSEL_D256			HwSD_CLK_SDCLKSEL(128)		// SDCLK = base clock / 256
		#define	HwSD_CLK_SDCLKSEL_D128			HwSD_CLK_SDCLKSEL(64)			// SDCLK = base clock / 128
		#define	HwSD_CLK_SDCLKSEL_D64				HwSD_CLK_SDCLKSEL(32)			// SDCLK = base clock / 64
		#define	HwSD_CLK_SDCLKSEL_D32				HwSD_CLK_SDCLKSEL(16)			// SDCLK = base clock / 32
		#define	HwSD_CLK_SDCLKSEL_D16				HwSD_CLK_SDCLKSEL(8)			// SDCLK = base clock / 16
		#define	HwSD_CLK_SDCLKSEL_D8				HwSD_CLK_SDCLKSEL(4)			// SDCLK = base clock / 8
		#define	HwSD_CLK_SDCLKSEL_D4				HwSD_CLK_SDCLKSEL(2)			// SDCLK = base clock / 4
		#define	HwSD_CLK_SDCLKSEL_D2				HwSD_CLK_SDCLKSEL(1)			// SDCLK = base clock / 2
		#define	HwSD_CLK_SDCLKSEL_D1				HwSD_CLK_SDCLKSEL(0)			// SDCLK = base clock (10MHz ~ 63MHz)
		#define	HwSD_CLK_SDCLKSEL_MASK			HwSD_CLK_SDCLKSEL(255)
		#define	HwSD_CLK_SCKEN_EN					Hw2								// SDCLK Enable
		#define	HwSD_CLK_CLKRDY_STABLE			Hw1								// R, Internal base clock is stable
		#define	HwSD_CLK_CLKEN_EN					Hw0								// Internal base clock Enable

	unsigned	STS;				// R, Normal Interrupt Status
		#define	HwSD_STS_VENDOR3_ERR				Hw31							// Vendor specific error status3
		#define	HwSD_STS_VENDOR2_ERR				Hw30							// Vendor specific error status2
		#define	HwSD_STS_VENDOR1_ERR				Hw29							// Vendor specific error status1
		#define	HwSD_STS_VENDOR0_ERR				Hw28							// Vendor specific error status0
		#define	HwSD_STS_ADMA_ERR					Hw25							// Error detected when ADMA Transfers
		#define	HwSD_STS_ACMD12_ERR				Hw24							// One of CMD12ERR register has been set to 1
		#define	HwSD_STS_CLIMIT_ERR				Hw23							// Exceeding Current limit
		#define	HwSD_STS_DATEND_ERR				Hw22							// 0 detected at the end bit position of read
		#define	HwSD_STS_DATCRC_ERR				Hw21							// CRC error detected
		#define	HwSD_STS_DATTIME_ERR				Hw20							// Data Timeout error detected
		#define	HwSD_STS_CINDEX_ERR				Hw19							// Command Index error detected in the command response
		#define	HwSD_STS_CMDEND_ERR				Hw18							// 0 deteced at the end bit position of a command response
		#define	HwSD_STS_CMDCRC_ERR				Hw17							// Command CRC error detected
		#define	HwSD_STS_CMDTIME_ERR				Hw16							// Command Timeout error detected (no response returned within 64 SDCLKs)
		#define	HwSD_STS_ERR						Hw15							// Error detected (One of above flags is set)
		#define	HwSD_STS_CDINT						Hw8								// Card Interrupt is generated
		#define	HwSD_STS_CDOUT					Hw7								// Card Removed (STATE.CDIN changes from 1 to 0)
		#define	HwSD_STS_CDIN						Hw6								// Card Inserted (STATE.CDIN changes from 0 to 1)
		#define	HwSD_STS_RDRDY					Hw5								// Buffer Read Ready (STATE.RDEN changes from 0 to 1, and ready to read)
		#define	HwSD_STS_WRRDY					Hw4								// Buffer Write Ready (STATE.WREN changes from 0 to 1, and ready to read)
		#define	HwSD_STS_DMAINT					Hw3								// DMA Interrupt
		#define	HwSD_STS_BLKGAP					Hw2								// Block Gap Event (STATE.DATACT falling in read transfer, STATE.WRACT falling in write transfer)
		#define	HwSD_STS_TDONE						Hw1								// Transfer Complete
		#define	HwSD_STS_CDONE					Hw0								// The end bit of the command response acquired (except Auto CMD12)

	unsigned	STSEN;				// R/W, Normal Interrupt Status Enable
		#define	HwSD_STSEN_VENDOR3_ERR			Hw31							// Enable STS.VENDOR3
		#define	HwSD_STSEN_VENDOR2_ERR			Hw30							// Enable STS.VENDOR2
		#define	HwSD_STSEN_VENDOR1_ERR			Hw29							// Enable STS.VENDOR1
		#define	HwSD_STSEN_VENDOR0_ERR			Hw28							// Enable STS.VENDOR0
		#define	HwSD_STSEN_ADMA_ERR				Hw25							// Enable STS.ADMA
		#define	HwSD_STSEN_ACMD12_ERR				Hw24							// Enable STS.ACMD12
		#define	HwSD_STSEN_CLIMIT_ERR				Hw23							// Enable STS.CLIMIT
		#define	HwSD_STSEN_DATEND_ERR				Hw22							// Enable STS.DATEND
		#define	HwSD_STSEN_DATCRC_ERR				Hw21							// Enable STS.DATCRC
		#define	HwSD_STSEN_DATTIME_ERR			Hw20							// Enable STS.DATTIME
		#define	HwSD_STSEN_CINDEX_ERR				Hw19							// Enable STS.CINDEX
		#define	HwSD_STSEN_CMDEND_ERR				Hw18							// Enable STS.CMDEND
		#define	HwSD_STSEN_CMDCRC_ERR			Hw17							// Enable STS.CMDCRC
		#define	HwSD_STSEN_CMDTIME_ERR			Hw16							// Enable STS.CMDTIME
		#define	HwSD_STSEN_CDINT					Hw8								// Enable STS.CDINT
		#define	HwSD_STSEN_CDOUT					Hw7								// Enable STS.CDOUT
		#define	HwSD_STSEN_CDIN					Hw6								// Enable STS.CDIN
		#define	HwSD_STSEN_RDRDY					Hw5								// Enable STS.RDRDY
		#define	HwSD_STSEN_WRRDY					Hw4								// Enable STS.WRRDY
		#define	HwSD_STSEN_DMAINT					Hw3								// Enable STS.DMAINT
		#define	HwSD_STSEN_BLKGAP					Hw2								// Enable STS.BLKGAP
		#define	HwSD_STSEN_TDONE					Hw1								// Enable STS.TDONE
		#define	HwSD_STSEN_CDONE					Hw0								// Enable STS.CDONE
	unsigned	INTEN;				// R/W, Normal Interrupt Signal Enable
		#define	HwSD_INTEN_VENDOR3_ERR			Hw31							// Enable Interrupt of INT.VENDOR3
		#define	HwSD_INTEN_VENDOR2_ERR			Hw30							// Enable Interrupt of INT.VENDOR2
		#define	HwSD_INTEN_VENDOR1_ERR			Hw29							// Enable Interrupt of INT.VENDOR1
		#define	HwSD_INTEN_VENDOR0_ERR			Hw28							// Enable Interrupt of INT.VENDOR0
		#define	HwSD_INTEN_ADMA_ERR				Hw25							// Enable Interrupt of INT.ADMA
		#define	HwSD_INTEN_ACMD12_ERR				Hw24							// Enable Interrupt of INT.ACMD12
		#define	HwSD_INTEN_CLIMIT_ERR				Hw23							// Enable Interrupt of INT.CLIMIT
		#define	HwSD_INTEN_DATEND_ERR				Hw22							// Enable Interrupt of INT.DATEND
		#define	HwSD_INTEN_DATCRC_ERR				Hw21							// Enable Interrupt of INT.DATCRC
		#define	HwSD_INTEN_DATTIME_ERR				Hw20							// Enable Interrupt of INT.DATTIME
		#define	HwSD_INTEN_CINDEX_ERR				Hw19							// Enable Interrupt of INT.CINDEX
		#define	HwSD_INTEN_CMDEND_ERR				Hw18							// Enable Interrupt of INT.CMDEND
		#define	HwSD_INTEN_CMDCRC_ERR				Hw17							// Enable Interrupt of INT.CMDCRC
		#define	HwSD_INTEN_CMDTIME_ERR			Hw16							// Enable Interrupt of INT.CMDTIME
		#define	HwSD_INTEN_CDINT					Hw8								// Enable Interrupt of INT.CDINT
		#define	HwSD_INTEN_CDOUT					Hw7								// Enable Interrupt of INT.CDOUT
		#define	HwSD_INTEN_CDIN					Hw6								// Enable Interrupt of INT.CDIN
		#define	HwSD_INTEN_RDRDY					Hw5								// Enable Interrupt of INT.RDRDY
		#define	HwSD_INTEN_WRRDY					Hw4								// Enable Interrupt of INT.WRRDY
		#define	HwSD_INTEN_DMAINT					Hw3								// Enable Interrupt of INT.DMAINT
		#define	HwSD_INTEN_BLKGAP					Hw2								// Enable Interrupt of INT.BLKGAP
		#define	HwSD_INTEN_TDONE					Hw1								// Enable Interrupt of INT.TDONE
		#define	HwSD_INTEN_CDONE					Hw0								// Enable Interrupt of INT.CDONE

	unsigned	CMD12ERR;			// R, Auto CMD12 Error Status
		#define	HwSD_CMD12ERR_NOCMD				Hw7								// CMD_wo_DAT is not executed due to an Auto CMD12 Error
		#define	HwSD_CMD12ERR_INDEX_ERR			Hw4								// Command Index error occurs
		#define	HwSD_CMD12ERR_ENDBIT_ERR			Hw3								// 0 is detected at the end bit of command response
		#define	HwSD_CMD12ERR_CRC_ERR			Hw2								// CRC error is detected in command response
		#define	HwSD_CMD12ERR_TIMEOUT_ERR			Hw1								// CMD12 Timeout error detected (no response returned within 64 SDCLKs)
		#define	HwSD_CMD12ERR_NORUN_ERR			Hw0								// Auto CMD12 cannot be issued due to some error.

	unsigned	CA;					// R, Capabilities
		#define	HwSD_CA_SPIBLK						Hw30							// SPI Block Mode Supported
		#define	HwSD_CA_SPI						Hw29							// SPI Mode Supported
		#define	HwSD_CA_BUS64						Hw28							// 64bit System Bus Supported
		#define	HwSD_CA_INT						Hw27							// Interrupt Mode Supported
		#define	HwSD_CA_V18						Hw26							// 1.8V Supported
		#define	HwSD_CA_V30						Hw25							// 3.0V Supported
		#define	HwSD_CA_V33						Hw24							// 3.3V Supported
		#define	HwSD_CA_RESUME					Hw23							// Suspend/Resume Supported
		#define	HwSD_CA_SDMA						Hw22							// SDMA Supported
		#define	HwSD_CA_HS							Hw21							// HS Supported
		#define	HwSD_CA_ADMA2						Hw19							// ADMA2 Supported
		#define	HwSD_CA_EXTBUS						Hw18							// Extended Media Bus Supported
		#define	HwSD_CA_MAXBLK(X)					((X)*Hw16)						// Max Block Supported
		#define	HwSD_CA_MAXBLK_512				HwSD_CA_MAXBLK(0)				// Max Block is 512 bytes
		#define	HwSD_CA_MAXBLK_1K					HwSD_CA_MAXBLK(1)				// Max Block is 1K bytes
		#define	HwSD_CA_MAXBLK_2K					HwSD_CA_MAXBLK(2)				// Max Block is 2K bytes
		#define	HwSD_CA_MAXBLK_4K					HwSD_CA_MAXBLK(3)				// Max Block is 4K bytes
		#define	HwSD_CA_MAXBLK_MASK				HwSD_CA_MAXBLK(3)
		#define	HwSD_CA_BASECLK(X)					((X)*Hw8)						// Base Clock Frequency (1 ~ 63 MHz)
		#define	HwSD_CA_BASECLK_MASK				HwSD_CA_BASECLK(63)
		#define	HwSD_CA_TUNIT_MHZ					Hw7								// MHz Unit for base clock frequency used to detect Data Timeout Error
		#define	HwSD_CA_TUNIT_KHZ					HwZERO							// KHz Unit for base clock frequency used to detect Data Timeout Error
		#define	HwSD_CA_TMCLK(X)					((X)*Hw0)						// Base clock frequency used to detect Data Timeout Error (1~63)
		#define	HwSD_CA_TMCLK_MASK				HwSD_CA_TMCLK(63)

	unsigned	_RSV0;
	unsigned	CUR;				// R, Maximum Current Capabilities
		#define	HwSD_CUR_MAXCV18(X)				((X)*Hw16)						// Maximum Current for 1.8V
		#define	HwSD_CUR_MAXCV18_MASK			HwSD_CUR_MAXCV18(255)
		#define	HwSD_CUR_MAXCV30(X)				((X)*Hw8)						// Maximum Current for 3.0V
		#define	HwSD_CUR_MAXCV30_MASK			HwSD_CUR_MAXCV30(255)
		#define	HwSD_CUR_MAXCV33(X)				((X)*Hw0)						// Maximum Current for 3.3V
		#define	HwSD_CUR_MAXCV33_MASK			HwSD_CUR_MAXCV33(255)
	unsigned	_RSV1;
	unsigned	FORCE;				// W, Force Event for Error
		#define	HwSD_FORCE_VENDOR3_ERR			Hw31							// Force Event for INT.VENDOR3
		#define	HwSD_FORCE_VENDOR2_ERR			Hw30							// Force Event for INT.VENDOR2
		#define	HwSD_FORCE_VENDOR1_ERR			Hw29							// Force Event for INT.VENDOR1
		#define	HwSD_FORCE_VENDOR0_ERR			Hw28							// Force Event for INT.VENDOR0
		#define	HwSD_FORCE_ADMA_ERR				Hw25							// Force Event for INT.ADMA
		#define	HwSD_FORCE_ACMD12_ERR				Hw24							// Force Event for INT.ACMD12
		#define	HwSD_FORCE_CLIMIT_ERR				Hw23							// Force Event for INT.CLIMIT
		#define	HwSD_FORCE_DATEND_ERR				Hw22							// Force Event for INT.DATEND
		#define	HwSD_FORCE_DATCRC_ERR				Hw21							// Force Event for INT.DATCRC
		#define	HwSD_FORCE_DATTIME_ERR			Hw20							// Force Event for INT.DATTIME
		#define	HwSD_FORCE_CINDEX_ERR				Hw19							// Force Event for INT.CINDEX
		#define	HwSD_FORCE_CMDEND_ERR			Hw18							// Force Event for INT.CMDEND
		#define	HwSD_FORCE_CMDCRC_ERR			Hw17							// Force Event for INT.CMDCRC
		#define	HwSD_FORCE_CMDTIME_ERR			Hw16							// Force Event for INT.CMDTIME
		#define	HwSD_FORCE_CDINT					Hw8								// Force Event for INT.CDINT
		#define	HwSD_FORCE_CDOUT					Hw7								// Force Event for INT.CDOUT
		#define	HwSD_FORCE_CDIN					Hw6								// Force Event for INT.CDIN
		#define	HwSD_FORCE_RDRDY					Hw5								// Force Event for INT.RDRDY
		#define	HwSD_FORCE_WRRDY					Hw4								// Force Event for INT.WRRDY
		#define	HwSD_FORCE_DMAINT					Hw3								// Force Event for INT.DMAINT
		#define	HwSD_FORCE_BLKGAP					Hw2								// Force Event for INT.BLKGAP
		#define	HwSD_FORCE_TDONE					Hw1								// Force Event for INT.TDONE
		#define	HwSD_FORCE_CDONE					Hw0								// Force Event for INT.CDONE

	unsigned	ADMAERR;			// R/W, ADMA Error Status
		#define	HwSD_ADMAERR_LEN_ERR				Hw2								// ADMA Length Mismatch Error
		#define	HwSD_ADMAERR_STATE(X)				((X)*Hw0)
		#define	HwSD_ADMAERR_STATE_STOP			HwSD_ADMAERR_STATE(0)		// 
		#define	HwSD_ADMAERR_STATE_FDS			HwSD_ADMAERR_STATE(1)		//
		#define	HwSD_ADMAERR_STATE_TFR			HwSD_ADMAERR_STATE(3)		//
		#define	HwSD_ADMAERR_STATE_MASK			HwSD_ADMAERR_STATE(3)

	unsigned	ADDR[2];			// R/W, ADMA Address
	unsigned	_RSV2[(0xF0-0x60)/4];
	unsigned	SPIINT;				// R/W, SPI Interrupt Support
	unsigned	_RSV3[2];
	unsigned short	VERSION;	// R, Host Controller Version
		#define	HwSD_VERSION_SPEC(X)				((X)*Hw0)						// Specification Number (0 = V1.0, 1 = V2.0, 2 = V2.0 with ADMA)
		#define	HwSD_VERSION_SPEC_MASK			(Hw8-Hw0)
		#define	HwSD_VERSION_VENDOR(X)			((X)*Hw8)						// Vendor Number
		#define	HwSD_VERSION_VENDOR_MASK			(Hw16-Hw8)
	unsigned short	SLOTINT;		// R, Slot Interrupt Status
		#define	HwSD_SLOTINT_1						Hw0
		#define	HwSD_SLOTINT_2						Hw1
		#define	HwSD_SLOTINT_3						Hw2
		#define	HwSD_SLOTINT_4						Hw3
		#define	HwSD_SLOTINT_5						Hw4
		#define	HwSD_SLOTINT_6						Hw5
		#define	HwSD_SLOTINT_7						Hw6
		#define	HwSD_SLOTINT_8						Hw7
} sHwSDMMC;

#define	HwSD0_BASE								*(volatile unsigned long *)0xF0058000	// SDMMC 0 Base Register

#define	HwSD0_SDMA								*(volatile unsigned long *)0xF0058000	// R/W, SDMA System Address Register

#define	HwSD0_BPARAM							*(volatile unsigned long *)0xF0058004	// R/W, Block Size & Count Register

#define	HwSD0_ARG								*(volatile unsigned long *)0xF0058008	// R/W, Argument Register

#define	HwSD0_TCMD								*(volatile unsigned long *)0xF005800C	// R/W, Command & Transfer Mode Register

#define	HwSD0_RESP_01							*(volatile unsigned long *)0xF0058010	// R, Response Register

#define	HwSD0_RESP_23							*(volatile unsigned long *)0xF0058014	// R, Response Register

#define	HwSD0_RESP_45							*(volatile unsigned long *)0xF0058018	// R, Response Register

#define	HwSD0_RESP_67							*(volatile unsigned long *)0xF005801C	// R, Response Register

#define	HwSD0_DATA								*(volatile unsigned long *)0xF0058020	// R/W, Buffer Data Port Register

#define	HwSD0_STATE							*(volatile unsigned long *)0xF0058024	// R, Present State Register

#define	HwSD0_CTRL								*(volatile unsigned long *)0xF0058028	// R/W, Control Register

#define	HwSD0_CLK								*(volatile unsigned long *)0xF005802C	// R/W, Clock / Reset / TimeOut Register

#define	HwSD0_STS								*(volatile unsigned long *)0xF0058030	// R, Normal Interrupt Status Register

#define	HwSD0_STSEN							*(volatile unsigned long *)0xF0058034	// R/W, Normal Interrupt Status Enable Register

#define	HwSD0_INTEN								*(volatile unsigned long *)0xF0058038	// R/W, Normal Interrupt Signal Enable Register

#define	HwSD0_CMD12ERR						*(volatile unsigned long *)0xF005803C	// R, Auto CMD12 Error Status Register

#define	HwSD0_CA								*(volatile unsigned long *)0xF0058040	// R, Capabilities Register

#define	HwSD0_CUR								*(volatile unsigned long *)0xF0058048	// R, Maximum Current Capabilities Register

#define	HwSD0_FORCE							*(volatile unsigned long *)0xF0058050	// W, Force Event Error Register

#define	HwSD0_ADMAERR							*(volatile unsigned long *)0xF0058054	// R/W, ADMA Error Status Register

#define	HwSD0_ADDR0							*(volatile unsigned long *)0xF0058058	// R/W, ADMA Address 0 Register

#define	HwSD0_ADDR1							*(volatile unsigned long *)0xF005805C	// R/W, ADMA Address 1 Register

#define	HwSD0_VERSION							*(volatile unsigned short*)0xF00580FC	// R, Host Controller Version Register

#define	HwSD0_SLOTINT							*(volatile unsigned short*)0xF00580FE	// R, Slot Interrupt Status Register

#define	HwSD1_BASE								*(volatile unsigned long *)0xF0058100	// SDMMC 1 Base Register

#define	HwSD1_SDMA								*(volatile unsigned long *)0xF0058100	// R/W, SDMA System Address Register

#define	HwSD1_BPARAM							*(volatile unsigned long *)0xF0058104	// R/W, Block Size & Count Register

#define	HwSD1_ARG								*(volatile unsigned long *)0xF0058108	// R/W, Argument Register

#define	HwSD1_TCMD								*(volatile unsigned long *)0xF005810C	// R/W, Command & Transfer Mode Register

#define	HwSD1_RESP_01							*(volatile unsigned long *)0xF0058110	// R, Response Register

#define	HwSD1_RESP_23							*(volatile unsigned long *)0xF0058114	// R, Response Register

#define	HwSD1_RESP_45							*(volatile unsigned long *)0xF0058118	// R, Response Register

#define	HwSD1_RESP_67							*(volatile unsigned long *)0xF005811C	// R, Response Register

#define	HwSD1_DATA								*(volatile unsigned long *)0xF0058120	// R/W, Buffer Data Port Register

#define	HwSD1_STATE							*(volatile unsigned long *)0xF0058124	// R, Present State Register

#define	HwSD1_CTRL								*(volatile unsigned long *)0xF0058128	// R/W, Control Register

#define	HwSD1_CLK								*(volatile unsigned long *)0xF005812C	// R/W, Clock / Reset / TimeOut Register

#define	HwSD1_STS								*(volatile unsigned long *)0xF0058130	// R, Normal Interrupt Status Register

#define	HwSD1_STSEN							*(volatile unsigned long *)0xF0058134	// R/W, Normal Interrupt Status Enable Register

#define	HwSD1_INTEN								*(volatile unsigned long *)0xF0058138	// R/W, Normal Interrupt Signal Enable Register

#define	HwSD1_CMD12ERR						*(volatile unsigned long *)0xF005813C	// R, Auto CMD12 Error Status Register

#define	HwSD1_CA								*(volatile unsigned long *)0xF0058140	// R, Capabilities Register

#define	HwSD1_CUR								*(volatile unsigned long *)0xF0058148	// R, Maximum Current Capabilities Register

#define	HwSD1_FORCE							*(volatile unsigned long *)0xF0058150	// W, Force Event Error Register

#define	HwSD1_ADMAERR							*(volatile unsigned long *)0xF0058154	// R/W, ADMA Error Status Register

#define	HwSD1_ADDR0							*(volatile unsigned long *)0xF0058158	// R/W, ADMA Address 0 Register

#define	HwSD1_ADDR1							*(volatile unsigned long *)0xF005815C	// R/W, ADMA Address 1 Register

#define	HwSD1_VERSION							*(volatile unsigned short*)0xF00581FC	// R, Host Controller Version Register

#define	HwSD1_SLOTINT							*(volatile unsigned short*)0xF00581FE	// R, Slot Interrupt Status Register

/************************************************************************
*	DAI & CDIF Register Define					(Base Addr = 0xF0059000)
************************************************************************/
#define	HwDAI_BASE								*(volatile unsigned long *)0xF0059000	// DAI Base Register

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
	#define	HwDAMR_RXE_EN							Hw22							// DAI RX Data Sign Extension Enable
	#define	HwDAMR_RXE_DIS							~Hw22							// DAI RX Data Sign Extension Disable
	#define	HwDAMR_RXS_MSB24						HwZERO							// Bit-pack MSB and 24bit mode
	#define	HwDAMR_RXS_MSB16						Hw20							// Bit-pack MSB and 24bit mode
	#define	HwDAMR_RXS_LSB24						Hw21							// Bit-pack LSB and 24bit mode
	#define	HwDAMR_RXS_LSB16						(Hw21+Hw20)						// Bit-pack LSB and 16bit mode
	#define	HwDAMR_TXS_MSB						~Hw19							// Bit-pack MSB mode
	#define	HwDAMR_TXS_LSB24						Hw19							// Bit-pack LSB and 24bit mode
	#define	HwDAMR_TXS_LSB16						(Hw19+Hw18)						// Bit-pack LSB and 16bit mode
	#define	HwDAMR_EN_ON							Hw15							// Enable DAI module
	#define	HwDAMR_EN_OFF							~Hw15							// Disable DAI module
	#define	HwDAMR_TE_EN							Hw14							// DAI Transimit Enable
	#define	HwDAMR_TE_DIS							~Hw14							// DAI Transimit Disable
	#define	HwDAMR_RE_EN							Hw13							// DAI Receive Enable
	#define	HwDAMR_RE_DIS							~Hw13							// DAI Receive Disable
	#define	HwDAMR_MD_MSB							Hw12							// Set DAI bus as MSB justified mode
	#define	HwDAMR_MD_IIS							~Hw12							// Set DAI bus as IIS bus mode
	#define	HwDAMR_SM_INT							Hw11							// Set that DAI system clock is generated by the clock generator block
	#define	HwDAMR_SM_EXT							~Hw11							// Set that DAI system clock is come from external pin
	#define	HwDAMR_BM_INT							Hw10							// Set that DAI bit clock is generated by dividing DAI system clock
	#define	HwDAMR_BM_EXT							~Hw10							// Set that DAI bit clock is come from external pin
	#define	HwDAMR_FM_INT							Hw9								// Set that DAI Frame Clock is generated by dividing DAI bit clock
	#define	HwDAMR_FM_EXT							~Hw9							// Set that DAI Frame Clock is come from external pin
	#define	HwDAMR_CC_EN							Hw8								// Enable CDIF Clock master mode
	#define	HwDAMR_CC_DIS							~Hw8							// Disable CDIF Clock master mode
	#define	HwDAMR_BD_DIV4							HwZERO							// Select Div4 (256fs->64fs)
	#define	HwDAMR_BD_DIV6							Hw6								// Select Div6 (384fs->64fs)
	#define	HwDAMR_BD_DIV8							Hw7								// Select Div8 (512fs->64fs, 384fs->48fs, 256fs->32fs)
	#define	HwDAMR_BD_DIV16						(Hw7+Hw6)						// Select Div16 (512fs->32fs)
	#define	HwDAMR_FD_DIV32						HwZERO							// Select Div32 (32fs->fs)
	#define	HwDAMR_FD_DIV48						Hw4								// Select Div48 (48fs->fs)
	#define	HwDAMR_FD_DIV64						Hw5								// Select Div64 (64fs->fs)
	#define	HwDAMR_BP_NEGA						Hw3								// Set that data is captured at negative edge of bit clock
	#define	HwDAMR_BP_POSI							~Hw3							// Set that data is captured at positive edge of bit clock
	#define	HwDAMR_CM_EN							Hw2								// Enable CDIF monitor mode. Data bypass from CDIF
	#define	HwDAMR_CM_DIS							~Hw2							// Disable CDIF monitor mode
	#define	HwDAMR_MM_EN							Hw1								// Enable DAI monitor mode. Transmitter should be enabled(TE=1).
	#define	HwDAMR_MM_DIS							~Hw1							// Disable DAI monitor mode.
	#define	HwDAMR_LB_EN							Hw0								// Enable DAI Loop back mode
	#define	HwDAMR_LB_DIS							~Hw0							// Disable DAI Loop back mode

#define	HwDAVC									*(volatile unsigned long *)0xF0059044	// R/W, Digital Audio Volume Control Register
	#define	HwDAVC_0dB								HwZERO							// 0dB Volume
	#define	HwDAVC_6dB								Hw0								// -6dB Volume
	#define	HwDAVC_12dB							Hw1								// -12dB Volume
	#define	HwDAVC_18dB							(Hw1+Hw0)						// -18dB Volume
	#define	HwDAVC_24dB							Hw2								// -24dB Volume
	#define	HwDAVC_30dB							(Hw2+Hw0)						// -30dB Volume
	#define	HwDAVC_36dB							(Hw2+Hw1)						// -36dB Volume
	#define	HwDAVC_42dB							(Hw2+Hw1+Hw0)					// -42dB Volume
	#define	HwDAVC_48dB							Hw3								// -48dB Volume
	#define	HwDAVC_54dB							(Hw3+Hw0)						// -54dB Volume
	#define	HwDAVC_60dB							(Hw3+Hw1)						// -60dB Volume
	#define	HwDAVC_66dB							(Hw3+Hw1+Hw0)					// -66dB Volume
	#define	HwDAVC_72dB							(Hw3+Hw2)						// -72dB Volume
	#define	HwDAVC_78dB							(Hw3+Hw2+Hw0)					// -78dB Volume
	#define	HwDAVC_84dB							(Hw3+Hw2+Hw1)					// -84dB Volume
	#define	HwDAVC_90dB							(Hw3+Hw2+Hw1+Hw0)				// -90dB Volume

#define	HwCDDI_0								*(volatile unsigned long *)0xF0059080	// R, CD Digital Audio Input Register 0

#define	HwCDDI_1								*(volatile unsigned long *)0xF0059084	// R, CD Digital Audio Input Register 1

#define	HwCDDI_2								*(volatile unsigned long *)0xF0059088	// R, CD Digital Audio Input Register 2

#define	HwCDDI_3								*(volatile unsigned long *)0xF005908C	// R, CD Digital Audio Input Register 3

#define	HwCICR									*(volatile unsigned long *)0xF0059090	// R/W, CD Interface Control Register
	#define	HwCICR_EN_ON							Hw7								// CIDF Enable
	#define	HwCICR_EN_OFF							~Hw7							// CIDF Disable
	#define	HwCICR_BS_64							HwZERO							// 64fs
	#define	HwCICR_BS_32							Hw2								// 32fs
	#define	HwCICR_BS_48							Hw3								// 48fs
	#define	HwCICR_MD_LSB							Hw1								// Select LSB justified format
	#define	HwCICR_MD_IIS							~Hw1							// Select IIS format
	#define	HwCICR_BP_NEGA							Hw0								// Set that data is captured at negative edge of bit clock
	#define	HwCICR_BP_POSI							~Hw0							// Set that data is captured at positive edge of bit clock

/************************************************************************
*	GPIO Port Register Define					(Base Addr = 0xF005A000)
************************************************************************/
#define	HwPORT_BASE							*(volatile unsigned long *)0xF005A000	// PORT Base Register

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

#define	HwGPADAT								*(volatile unsigned long *)0xF005A040	// R/W, GPA Data Register

#define	HwGPAEN								*(volatile unsigned long *)0xF005A044	// R/W, GPA Output Enable Register

#define	HwGPASET								*(volatile unsigned long *)0xF005A048	// W, OR function on GPA Output Data

#define	HwGPACLR								*(volatile unsigned long *)0xF005A04C	// W, BIC function on GPA Output Data

#define	HwGPAXOR								*(volatile unsigned long *)0xF005A050	// W, XOR function on GPA Output Data

#define	HwGPBDAT								*(volatile unsigned long *)0xF005A060	// R/W, GPB Data Register

#define	HwGPBEN								*(volatile unsigned long *)0xF005A064	// R/W, GPB Output Enable Register

#define	HwGPBSET								*(volatile unsigned long *)0xF005A068	// W, OR function on GPB Output Data

#define	HwGPBCLR								*(volatile unsigned long *)0xF005A06C	// W, BIC function on GPB Output Data

#define	HwGPBXOR								*(volatile unsigned long *)0xF005A070	// W, XOR function on GPB Output Data

#define	HwGPCDAT								*(volatile unsigned long *)0xF005A080	// R/W, GPC Data Register

#define	HwGPCEN								*(volatile unsigned long *)0xF005A084	// R/W, GPC Output Enable Register

#define	HwGPCSET								*(volatile unsigned long *)0xF005A088	// W, OR function on GPC Output Data

#define	HwGPCCLR								*(volatile unsigned long *)0xF005A08C	// W, BIC function on GPC Output Data

#define	HwGPCXOR								*(volatile unsigned long *)0xF005A090	// W, XOR function on GPC Output Data

#define	HwGPDDAT								*(volatile unsigned long *)0xF005A0A0	// R/W, GPD Data Register

#define	HwGPDEN								*(volatile unsigned long *)0xF005A0A4	// R/W, GPD Output Enable Register

#define	HwGPDSET								*(volatile unsigned long *)0xF005A0A8	// W, OR function on GPD Output Data

#define	HwGPDCLR								*(volatile unsigned long *)0xF005A0AC	// W, BIC function on GPD Output Data

#define	HwGPDXOR								*(volatile unsigned long *)0xF005A0B0	// W, XOR function on GPD Output Data

#define	HwGPEDAT								*(volatile unsigned long *)0xF005A0C0	// R/W, GPE Data Register

#define	HwGPEEN									*(volatile unsigned long *)0xF005A0C4	// R/W, GPE Output Enable Register

#define	HwGPESET								*(volatile unsigned long *)0xF005A0C8	// W, OR function on GPE Output Data

#define	HwGPECLR								*(volatile unsigned long *)0xF005A0CC	// W, BIC function on GPE Output Data

#define	HwGPEXOR								*(volatile unsigned long *)0xF005A0D0	// W, XOR function on GPE Output Data

#define	HwGPFDAT								*(volatile unsigned long *)0xF005A0E0	// R/W, GPE Data Register
                                    			
#define	HwGPFEN									*(volatile unsigned long *)0xF005A0E4	// R/W, GPE Output Enable Register
                                    			
#define	HwGPFSET								*(volatile unsigned long *)0xF005A0E8	// W, OR function on GPE Output Data
                                    			
#define	HwGPFCLR								*(volatile unsigned long *)0xF005A0EC	// W, BIC function on GPE Output Data
                                    			
#define	HwGPFXOR								*(volatile unsigned long *)0xF005A0F0	// W, XOR function on GPE Output Data

// Type definition for Pull-up/down resistor selection
typedef enum
{
	PUDN,	// Neither Pull-up nor Pull-down
	PUE,		// Pull-up enabled
	PDE,		// Pull-down enabled
	PUDE	// Pull-up/down enabled (should not be used)
} PUDC;

#define	HwCPUD0								*(volatile unsigned long *)0xF005A100	// R/W, Pull-Up/Down Control Register 0
	#define	HwCPUD0_LPD23(X)						((X)*Hw30)
	#define	HwCPUD0_LPD22(X)						((X)*Hw28)
	#define	HwCPUD0_LPD21(X)						((X)*Hw26)
	#define	HwCPUD0_LPD20(X)						((X)*Hw24)
	#define	HwCPUD0_LPD19(X)						((X)*Hw22)
	#define	HwCPUD0_LPD18(X)						((X)*Hw20)
	#define	HwCPUD0_LPD17(X)						((X)*Hw18)
	#define	HwCPUD0_LPD16(X)						((X)*Hw16)
	#define	HwCPUD0_LPD15(X)						((X)*Hw14)
	#define	HwCPUD0_LPD14(X)						((X)*Hw12)
	#define	HwCPUD0_LPD13(X)						((X)*Hw10)
	#define	HwCPUD0_LPD12(X)						((X)*Hw8)
	#define	HwCPUD0_LPD11(X)						((X)*Hw6)
	#define	HwCPUD0_LPD10(X)						((X)*Hw4)
	#define	HwCPUD0_LPD9(X)							((X)*Hw2)
	#define	HwCPUD0_LPD8(X)							((X)*Hw0)

#define	HwCPUD1								*(volatile unsigned long *)0xF005A104	// R/W, Pull-Up/Down Control Register 1
	#define	HwCPUD1_GPIOF27(X)						((X)*Hw30)
	#define	HwCPUD1_GPIOC31(X)						((X)*Hw28)
	#define	HwCPUD1_GPIOC30(X)						((X)*Hw26)
	#define	HwCPUD1_GPIOC29(X)						((X)*Hw24)
	#define	HwCPUD1_LVS(X)							((X)*Hw22)
	#define	HwCPUD1_LHS(X)							((X)*Hw20)
	#define	HwCPUD1_LCK(X)							((X)*Hw18)
	#define	HwCPUD1_LBIAS(X)						((X)*Hw16)
	#define	HwCPUD1_LPD0(X)							((X)*Hw14)
	#define	HwCPUD1_LPD1(X)							((X)*Hw12)
	#define	HwCPUD1_LPD2(X)							((X)*Hw10)
	#define	HwCPUD1_LPD3(X)							((X)*Hw8)
	#define	HwCPUD1_LPD4(X)							((X)*Hw6)
	#define	HwCPUD1_LPD5(X)							((X)*Hw4)
	#define	HwCPUD1_LPD6(X)							((X)*Hw2)
	#define	HwCPUD1_LPD7(X)							((X)*Hw0)

#define	HwCPUD2								*(volatile unsigned long *)0xF005A108	// R/W, Pull-Up/Down Control Register 2
	#define	HwCPUD2_GPIOF26(X)						((X)*Hw30)
	#define	HwCPUD2_GPIOF25(X)						((X)*Hw28)

#define	HwCPUD3								*(volatile unsigned long *)0xF005A10C	// R/W, Pull-Up/Down Control Register 3
	#define	HwCPUD3_SCMD0(X)						((X)*Hw8)
	#define	HwCPUD3_SCLK0(X)						((X)*Hw6)
	#define	HwCPUD3_SDI0(X)							((X)*Hw4)
	#define	HwCPUD3_SDO0(X)						((X)*Hw2)
	#define	HwCPUD3_GPIOA2(X)						((X)*Hw0)

#define	HwCPUD4								*(volatile unsigned long *)0xF005A110	// R/W, Pull-Up/Down Control Register 4
	#define	HwCPUD4_GPIOA3(X)						((X)*Hw30)
	#define	HwCPUD4_GPIOA4(X)						((X)*Hw28)
	#define	HwCPUD4_GPIOA5(X)						((X)*Hw26)
	#define	HwCPUD4_CSN_CS0(X)						((X)*Hw24)
	#define	HwCPUD4_CSN_NOR(X)						((X)*Hw22)
	#define	HwCPUD4_GPIOB0(X)						((X)*Hw20)
	#define	HwCPUD4_GPIOB1(X)						((X)*Hw18)
	#define	HwCPUD4_GPIOB2(X)						((X)*Hw16)
	#define	HwCPUD4_GPIOB3(X)						((X)*Hw14)
	#define	HwCPUD4_GPIOB4(X)						((X)*Hw12)
	#define	HwCPUD4_GPIOB5(X)						((X)*Hw10)
	#define	HwCPUD4_GPIOB6(X)						((X)*Hw8)
	#define	HwCPUD4_GPIOB7(X)						((X)*Hw6)
	#define	HwCPUD4_GPIOB8(X)						((X)*Hw4)
	#define	HwCPUD4_GPIOB9(X)						((X)*Hw2)
	#define	HwCPUD4_GPIOB10(X)						((X)*Hw0)

#define	HwCPUD5								*(volatile unsigned long *)0xF005A114	// R/W, Pull-Up/Down Control Register 5
	#define	HwCPUD5_GPIOB11(X)						((X)*Hw30)
	#define	HwCPUD5_GPIOB12(X)						((X)*Hw28)
	#define	HwCPUD5_GPIOB13(X)						((X)*Hw26)
	#define	HwCPUD5_GPIOB14(X)						((X)*Hw24)
	#define	HwCPUD5_GPIOB15(X)						((X)*Hw22)
	#define	HwCPUD5_SCMD1(X)						((X)*Hw20)
	#define	HwCPUD5_SCLK1(X)						((X)*Hw18)
	#define	HwCPUD5_SDI1(X)							((X)*Hw16)
	#define	HwCPUD5_SDO1(X)						((X)*Hw14)
	#define	HwCPUD5_GPIOA6(X)						((X)*Hw12)
	#define	HwCPUD5_GPIOA7(X)						((X)*Hw10)
	#define	HwCPUD5_GPIOA8(X)						((X)*Hw8)
	#define	HwCPUD5_GPIOA9(X)						((X)*Hw6)
	#define	HwCPUD5_GPIOA10(X)						((X)*Hw4)
	#define	HwCPUD5_GPIOA11(X)						((X)*Hw2)
	#define	HwCPUD5_GPIOA12(X)						((X)*Hw0)

#define	HwCPUD6								*(volatile unsigned long *)0xF005A118	// R/W, Pull-Up/Down Control Register 6
	#define	HwCPUD6_AIN0(X)							((X)*Hw30)
	#define	HwCPUD6_AIN1(X)							((X)*Hw28)
	#define	HwCPUD6_AIN2(X)							((X)*Hw26)
	#define	HwCPUD6_AIN3(X)							((X)*Hw24)
	#define	HwCPUD6_AIN4(X)							((X)*Hw22)
	#define	HwCPUD6_AIN5(X)							((X)*Hw20)
	#define	HwCPUD6_AIN6(X)							((X)*Hw18)
	#define	HwCPUD6_AIN7(X)							((X)*Hw16)
	#define	HwCPUD6_UTXD0(X)						((X)*Hw14)
	#define	HwCPUD6_URXD0(X)						((X)*Hw12)
	#define	HwCPUD6_UCTS0(X)						((X)*Hw10)
	#define	HwCPUD6_URTS0(X)						((X)*Hw8)
	#define	HwCPUD6_UTXD1(X)						((X)*Hw6)
	#define	HwCPUD6_URXD1(X)						((X)*Hw4)
	#define	HwCPUD6_UCTS1(X)						((X)*Hw2)
	#define	HwCPUD6_URTS1(X)						((X)*Hw0)

#define	HwCPUD7								*(volatile unsigned long *)0xF005A11C	// R/W, Pull-Up/Down Control Register 7
	#define	HwCPUD7_UTXD2(X)						((X)*Hw30)
	#define	HwCPUD7_URXD2(X)						((X)*Hw28)
	#define	HwCPUD7_UTXD3(X)						((X)*Hw26)
	#define	HwCPUD7_URXD3(X)						((X)*Hw24)
	#define	HwCPUD7_BCLK(X)						((X)*Hw16)
	#define	HwCPUD7_LRCK(X)						((X)*Hw14)
	#define	HwCPUD7_MCLK(X)						((X)*Hw12)
	#define	HwCPUD7_DAO(X)							((X)*Hw10)
	#define	HwCPUD7_DAI(X)							((X)*Hw8)
	#define	HwCPUD7_GPIOA0(X)						((X)*Hw6)
	#define	HwCPUD7_GPIOA1(X)						((X)*Hw4)
	#define	HwCPUD7_CCKI(X)						((X)*Hw2)
	#define	HwCPUD7_CCKO(X)						((X)*Hw0)

#define	HwCPUD8								*(volatile unsigned long *)0xF005A120	// R/W, Pull-Up/Down Control Register 8
	#define	HwCPUD8_CVS(X)							((X)*Hw30)
	#define	HwCPUD8_CHS(X)							((X)*Hw28)
	#define	HwCPUD8_CPD0(X)						((X)*Hw26)
	#define	HwCPUD8_CPD1(X)						((X)*Hw24)
	#define	HwCPUD8_CPD2(X)						((X)*Hw22)
	#define	HwCPUD8_CPD3(X)						((X)*Hw20)
	#define	HwCPUD8_CPD4(X)						((X)*Hw18)
	#define	HwCPUD8_CPD5(X)						((X)*Hw16)
	#define	HwCPUD8_CPD6(X)						((X)*Hw14)
	#define	HwCPUD8_CPD7(X)						((X)*Hw12)

#define	HwCPUD9								*(volatile unsigned long *)0xF005A124	// R/W, Pull-Up/Down Control Register 9
	#define	HwCPUD9_SDCLK(X)						((X)*Hw30)
	#define	HwCPUD9_SDCKE(X)						((X)*Hw28)
	#define	HwCPUD9_OEN(X)							((X)*Hw26)
	#define	HwCPUD9_CSN_SD(X)						((X)*Hw24)
	#define	HwCPUD9_WEN(X)							((X)*Hw22)

// Type definition for Drive Strength selection
typedef enum
{
	DRVST0,
	DRVST1,
	DRVST2,
	DRVST3
} PDRV;

#define	HwCPDRV0								*(volatile unsigned long *)0xF005A128	// R/W, Driver Strength Control Register 0
	#define	HwCPDRV0_GPIOF(X)						((X)*Hw30)						// GPIOF[27:25]
	#define	HwCPDRV0_GPIOA(X)						((X)*Hw28)						// GPIOA[7:0]
	#define	HwCPDRV0_LPD(X)						((X)*Hw26)						// LPD[23:16]
	#define	HwCPDRV0_LCD(X)						((X)*Hw24)						// LPD[15:0], LBIAS, LCD, LHS, LVS, GPIOC[31:29]
	#define	HwCPDRV0_ADC2(X)						((X)*Hw22)						// AIN[7:2]
	#define	HwCPDRV0_ADC0(X)						((X)*Hw20)						// AIN[1:0]
	#define	HwCPDRV0_CDIF(X)						((X)*Hw18)						// GPIOA[12:10]
	#define	HwCPDRV0_DAIF(X)						((X)*Hw16)						// BCLK, LRCK, MCLK, DAO, DAI
	#define	HwCPDRV0_SD5CTRL(X)					((X)*Hw14)						// GPIOB[9:8]
	#define	HwCPDRV0_SD6(X)						((X)*Hw12)						// GPIOB[15:10]
	#define	HwCPDRV0_GPSB5(X)						((X)*Hw10)						// SCMD1, SCLK1, SDI1, SDO1
	#define	HwCPDRV0_GPSB3(X)						((X)*Hw8)						// GPIOB[3:0]
	#define	HwCPDRV0_GPSB2(X)						((X)*Hw6)						// GPIOB[7:4]
	#define	HwCPDRV0_GPSB0(X)						((X)*Hw4)						// SCMD0, SCLK0, SDI0, SDO0
	#define	HwCPDRV0_HPXD(X)						((X)*Hw2)						// HPXD[17:0]
	#define	HwCPDRV0_HPCTRL(X)						((X)*Hw0)						// HPCSN_L, HPINTO, HPXA[1:0], HPCSN, HPWRN, HPRDN

#define	HwCPDRV1								*(volatile unsigned long *)0xF005A12C	// R/W, Driver Strength Control Register 1
	#define	HwCPDRV1_CIF(X)							((X)*Hw22)						// CCKI, CCKO, CVS, CHS, CPD[7:0]
	#define	HwCPDRV1_UTD3(X)						((X)*Hw20)						// UTXD3, URXD3
	#define	HwCPDRV1_UTD2(X)						((X)*Hw18)						// UTXD2, URXD2
	#define	HwCPDRV1_UTC1(X)						((X)*Hw16)						// UCTS1, URTS1
	#define	HwCPDRV1_UTD1(X)						((X)*Hw14)						// UTXD1, URXD1
	#define	HwCPDRV1_UTC0(X)						((X)*Hw12)						// UCTS0, URTS0
	#define	HwCPDRV1_UTD0(X)						((X)*Hw10)						// UTXD0, URXD0
	#define	HwCPDRV1_I2C1(X)						((X)*Hw8)						// GPIOA[9:8]
	#define	HwCPDRV1_I2C0(X)						((X)*Hw6)						// GPIOA[1:0]
	#define	HwCPDRV1_XD(X)							((X)*Hw4)						// XD[31:0]
	#define	HwCPDRV1_XA(X)							((X)*Hw2)						// XA[23:0]
	#define	HwCPDRV1_MCCTRL(X)						((X)*Hw0)						// SDCLK, SDCKE, CSN_CS0, CSN_NOR, CSN_SD, OEN, WEN

#define	HwAINCFG								*(volatile unsigned long *)0xF005A130	// R/W, Analog Input Pad Control Register
	#define	HwAINCFG_AIN7_DEN						Hw7								// Select AIN7 as Digital Port
	#define	HwAINCFG_AIN6_DEN						Hw6								// Select AIN6 as Digital Port
	#define	HwAINCFG_AIN5_DEN						Hw5								// Select AIN5 as Digital Port
	#define	HwAINCFG_AIN4_DEN						Hw4								// Select AIN4 as Digital Port
	#define	HwAINCFG_AIN3_DEN						Hw3								// Select AIN3 as Digital Port
	#define	HwAINCFG_AIN2_DEN						Hw2								// Select AIN2 as Digital Port
	#define	HwAINCFG_AIN1_DEN						Hw1								// Select AIN1 as Digital Port
	#define	HwAINCFG_AIN0_DEN						Hw0								// Select AIN0 as Digital Port

// Type definition for EINTSEL selection
typedef enum
{
	SEL_URXD3,
	SEL_UTXD2,
	SEL_AIN7,
	SEL_AIN1,
	SEL_AIN0,
	SEL_GPIOA11,
	SEL_GPIOA7,
	SEL_GPIOA6,
	SEL_SDO1,
	SEL_SCMD1,
	SEL_GPIOB15,
	SEL_GPIOB14,
	SEL_GPIOB13,
	SEL_GPIOB4,
	SEL_GPIOB3,
	SEL_GPIOB0,
	SEL_GPIOA5,
	SEL_GPIOA3,
	SEL_GPIOA2,
	SEL_SDO0,
	SEL_SCMD0,
	SEL_HPXD3,
	SEL_HPXD11,
	SEL_HPRDN,
	SEL_HPCSN_L,
	SEL_GPIOF26,
	SEL_GPIOF27,
	SEL_GPIOF30,
	SEL_LPD18,
	SEL_LPD23,
	SEL_PMWKUP
} ESEL;
#define	HwEINTSEL0								*(volatile unsigned long *)0xF005A134	// R/W, External Interrupt Select Register 0
	#define	HwEINTSEL0_EINT3(X)						((X)*Hw24)						// EINT3 Source Selection
	#define	HwEINTSEL0_EINT3SEL_USBVON				HwEINTSEL0_EINT3(31)
	#define	HwEINTSEL0_EINT3SEL_MASK				HwEINTSEL0_EINT3(31)
	#define	HwEINTSEL0_EINT2(X)						((X)*Hw16)						// EINT2 Source Selection
	#define	HwEINTSEL0_EINT2SEL_USBVOFF				HwEINTSEL0_EINT2(31)
	#define	HwEINTSEL0_EINT2SEL_MASK				HwEINTSEL0_EINT2(31)
	#define	HwEINTSEL0_EINT1(X)						((X)*Hw8)						// EINT1 Source Selection
	#define	HwEINTSEL0_EINT1SEL_USBVON				HwEINTSEL0_EINT1(31)
	#define	HwEINTSEL0_EINT1SEL_MASK				HwEINTSEL0_EINT1(31)
	#define	HwEINTSEL0_EINT0(X)						((X)*Hw0)						// EINT0 Source Selection
	#define	HwEINTSEL0_EINT0SEL_USBVOFF				HwEINTSEL0_EINT0(31)
	#define	HwEINTSEL0_EINT0SEL_MASK				HwEINTSEL0_EINT0(31)

#define	HwEINTSEL1								*(volatile unsigned long *)0xF005A138	// R/W, External Interrupt Select Register 1
	#define	HwEINTSEL1_EINT7(X)						((X)*Hw24)						// EINT7 Source Selection
	#define	HwEINTSEL1_EINT7SEL_USBVON				HwEINTSEL1_EINT7(31)
	#define	HwEINTSEL1_EINT7SEL_MASK				HwEINTSEL1_EINT7(31)
	#define	HwEINTSEL1_EINT6(X)						((X)*Hw16)						// EINT6 Source Selection
	#define	HwEINTSEL1_EINT6SEL_USBVOFF				HwEINTSEL1_EINT6(31)
	#define	HwEINTSEL1_EINT6SEL_MASK				HwEINTSEL1_EINT6(31)
	#define	HwEINTSEL1_EINT5(X)						((X)*Hw8)						// EINT5 Source Selection
	#define	HwEINTSEL1_EINT5SEL_USBVON				HwEINTSEL1_EINT5(31)
	#define	HwEINTSEL1_EINT5SEL_MASK				HwEINTSEL1_EINT5(31)
	#define	HwEINTSEL1_EINT4(X)						((X)*Hw0)						// EINT4 Source Selection
	#define	HwEINTSEL1_EINT4SEL_USBVOFF				HwEINTSEL1_EINT4(31)
	#define	HwEINTSEL1_EINT4SEL_MASK				HwEINTSEL1_EINT4(31)

#define	HwIRQSEL								*(volatile unsigned long *)0xF005A13C	// R/W, Interrupt Select Register
	#define	HwIRQSEL_SEL4(X)						((X)*Hw8)
	#define	HwIRQSEL_SEL4_GPSB						HwIRQSEL_SEL4(0)
	#define	HwIRQSEL_SEL4_ECC						HwIRQSEL_SEL4(1)
	#define	HwIRQSEL_SEL4_EINT7						HwIRQSEL_SEL4(2)
	#define	HwIRQSEL_SEL4_USBDMA					HwIRQSEL_SEL4(3)
	#define	HwIRQSEL_SEL4_MASK						HwIRQSEL_SEL4(3)
	#define	HwIRQSEL_SEL3(X)						((X)*Hw8)
	#define	HwIRQSEL_SEL3_MSTICK					HwIRQSEL_SEL3(0)
	#define	HwIRQSEL_SEL3_EINT6						HwIRQSEL_SEL3(1)
	#define	HwIRQSEL_SEL3_MASK						HwIRQSEL_SEL3(3)
	#define	HwIRQSEL_SEL2(X)						((X)*Hw8)
	#define	HwIRQSEL_SEL2_UART						HwIRQSEL_SEL2(0)
	#define	HwIRQSEL_SEL2_EHI1						HwIRQSEL_SEL2(1)
	#define	HwIRQSEL_SEL2_MASK						HwIRQSEL_SEL2(3)
	#define	HwIRQSEL_SEL1(X)						((X)*Hw8)
	#define	HwIRQSEL_SEL1_GPSB						HwIRQSEL_SEL1(0)
	#define	HwIRQSEL_SEL1_EHI1						HwIRQSEL_SEL1(1)
	#define	HwIRQSEL_SEL1_EINT5						HwIRQSEL_SEL1(2)
	#define	HwIRQSEL_SEL1_MASK						HwIRQSEL_SEL1(3)
	#define	HwIRQSEL_SEL0(X)						((X)*Hw8)
	#define	HwIRQSEL_SEL0_VCORE					HwIRQSEL_SEL0(0)
	#define	HwIRQSEL_SEL0_EHI0						HwIRQSEL_SEL0(1)
	#define	HwIRQSEL_SEL0_EINT4						HwIRQSEL_SEL0(2)
	#define	HwIRQSEL_SEL0_MASK						HwIRQSEL_SEL0(3)

/************************************************************************
*	ECC Register Define							(Base Addr = 0xF005B000)
************************************************************************/
#define	HwECCR_BASE							*(volatile unsigned long *)0xF005B000	// ECC Base Register

#define	HwECC_CTRL								*(volatile unsigned long *)0xF005B000	// R/W, ECC Control Register
	#define	HwECC_CTRL_IEN_MECC8_EN				Hw31							// MLC ECC8 Decoding Interrupt Enable
	#define	HwECC_CTRL_IEN_MECC8_DIS				~Hw31							// MLC ECC8 Decoding Interrupt Disable
	#define	HwECC_CTRL_IEN_MECC4_EN				Hw30							// MLC ECC4 Decoding Interrupt Enable
	#define	HwECC_CTRL_IEN_MECC4_DIS				~Hw30							// MLC ECC4 Decoding Interrupt Disable
	#define	HwECC_CTRL_DEN_EN						Hw29							// ECC DMA Request Enable
	#define	HwECC_CTRL_DEN_DIS						~Hw29							// ECC DMA Request Disable
	#define	HwECC_CTRL_DRQ_1						Hw28
	#define	HwECC_CTRL_DATASIZE(X)					((X)*Hw16)						// DataSize N (SLC: N<=1024 word, MLC4: N<=518 bytes, MLC8: N <=528 bytes)
	#define	HwECC_CTRL_DATASIZE_MASK				HwECC_CTRL_DATASIZE(2047)
	#define	HwECC_CTRL_ECCCNT(X)					((X)*Hw4)						// R, ECC Count (SLC: N<1024 word, MLC4: N<518 bytes, MLC8: N <528 bytes)
	#define	HwECC_CTRL_ECCCNT_MASK				HwECC_CTRL_ECCCNT(1023)
	#define	HwECC_CTRL_ECCEN(X)					((X)*Hw0)
	#define	HwECC_CTRL_ENC_DEC					HwECC_CTRL_ECCEN(1)			// ECC Decoding Enable
	#define	HwECC_CTRL_SLCECC_ENC_EN				HwECC_CTRL_ECCEN(2)			// SLC ECC Encoding Enable
	#define	HwECC_CTRL_SE_EN						HwECC_CTRL_SLCECC_ENC_EN
	#define	HwECC_CTRL_EN_SLCEN					HwECC_CTRL_SLCECC_ENC_EN
	#define	HwECC_CTRL_SLCECC_DEC_EN				HwECC_CTRL_ECCEN(3)			// SLC ECC Decoding Enable
	#define	HwECC_CTRL_EN_SLCDE					HwECC_CTRL_SLCECC_DEC_EN
	#define	HwECC_CTRL_MLC4ECC_ENC_EN				HwECC_CTRL_ECCEN(4)			// MLC4 ECC Encoding Enable
	#define	HwECC_CTRL_M4EN_EN						HwECC_CTRL_MLC4ECC_ENC_EN
	#define	HwECC_CTRL_EN_MCL4EN					HwECC_CTRL_MLC4ECC_ENC_EN
	#define	HwECC_CTRL_MLC4ECC_DEC_EN			HwECC_CTRL_ECCEN(5)			// MLC4 ECC Decoding Enable
	#define	HwECC_CTRL_EN_MCL4DE					HwECC_CTRL_MLC4ECC_DEC_EN
	#define	HwECC_CTRL_MLC8ECC_ENC_EN				HwECC_CTRL_ECCEN(6)			// MLC8 ECC Encoding Enable
	#define	HwECC_CTRL_M8EN_EN						HwECC_CTRL_MLC8ECC_ENC_EN
	#define	HwECC_CTRL_EN_MCL8EN					HwECC_CTRL_MLC8ECC_ENC_EN
	#define	HwECC_CTRL_MLC8ECC_DEC_EN			HwECC_CTRL_ECCEN(7)			// MLC8 ECC Decoding Enable
	#define	HwECC_CTRL_EN_MCL8DE					HwECC_CTRL_MLC8ECC_DEC_EN
	#define	HwECC_CTRL_ENCEN_MASK					HwECC_CTRL_ECCEN(7)

	#define	HwECC_CTRL_EN_DIS						~(Hw2|Hw1)						// ECC Disable

#define	HwECC_BASE								*(volatile unsigned long *)0xF005B004	// R/W, Base Address for ECC Calculation Register

#define	HwECC_MASK								*(volatile unsigned long *)0xF005B008	// R/W, Address Mask for ECC Area Register

#define	HwECC_CLR								*(volatile unsigned long *)0xF005B00C	// W, Clear ECC Output Register

#define	HwSECC_ALL								((volatile unsigned long *)0xF005B010)	// R/W, SLC ECC Code Register (can be array indexed from [0] to [15])
#define	HwSLC_ECC0								*(volatile unsigned long *)0xF005B010		// R, 1st Block ECC Output for SLC Nand Register
#define	HwSLC_ECC1								*(volatile unsigned long *)0xF005B014		// R, 2nd Block ECC Output for SLC Nand Register
#define	HwSLC_ECC2								*(volatile unsigned long *)0xF005B018		// R, 3nd Block ECC Output for SLC Nand Register
#define	HwSLC_ECC3								*(volatile unsigned long *)0xF005B01C		// R, 4th Block ECC Output for SLC Nand Register
#define	HwSLC_ECC4								*(volatile unsigned long *)0xF005B020		// R, 5th Block ECC Output for SLC Nand Register
#define	HwSLC_ECC5								*(volatile unsigned long *)0xF005B024		// R, 6th Block ECC Output for SLC Nand Register
#define	HwSLC_ECC6								*(volatile unsigned long *)0xF005B028		// R, 7th Block ECC Output for SLC Nand Register
#define	HwSLC_ECC7								*(volatile unsigned long *)0xF005B02C		// R, 8th Block ECC Output for SLC Nand Register

#define	HwMECC4_ALL							((volatile unsigned long *)0xF005B010)	// R/W, MLC ECC4 Code Register (can be array indexed from [0] to [2])
#define	HwMLC_ECC0R							*(volatile unsigned long *)0xF005B010		// R, Calculated ECC Output 0 for MLC Nand Register
#define	HwMLC_ECC1R							*(volatile unsigned long *)0xF005B014		// R, Calculated ECC Output 1 for MLC Nand Register
#define	HwMLC_ECC2R							*(volatile unsigned long *)0xF005B018		// R, Calculated ECC Output 2 for MLC Nand Register
#define	HwMLC_ECC0W							*(volatile unsigned long *)0xF005B010		// W, MLC Nand ECC Calculation Register 0
#define	HwMLC_ECC1W							*(volatile unsigned long *)0xF005B014		// W, Calculated ECC Calculation Register 1
#define	HwMLC_ECC2W							*(volatile unsigned long *)0xF005B018		// W, Calculated ECC Calculation Register 2
#define	HwMLC_ECC4_0							*(HwMECC4_ALL+0)
#define	HwMLC_ECC4_1							*(HwMECC4_ALL+1)
#define	HwMLC_ECC4_2							*(HwMECC4_ALL+2)

#define	HwMECC8_ALL							((volatile unsigned long *)0xF005B010)	// R/W, MLC ECC8 Code Register (can be array indexed from [0] to [4])
#define	HwMLC_ECC8_0							*(HwMECC8_ALL+0)
#define	HwMLC_ECC8_1							*(HwMECC8_ALL+1)
#define	HwMLC_ECC8_2							*(HwMECC8_ALL+2)
#define	HwMLC_ECC8_3							*(HwMECC8_ALL+3)
#define	HwMLC_ECC8_4							*(HwMECC8_ALL+4)

#define	HwSECC_EADDR_ALL						((volatile unsigned long *)0xF005B050)	// R, SLC ECC Error Address Register (can be array indexed from [0] to [15])

#define	HwMECC4_EADDR_ALL						((volatile unsigned long *)0xF005B050)	// R, MLC ECC4 Error Address Register (can be array indexed from [0] to [3])
#define	HwERRADDR0								*(HwMECC4_EADDR_ALL+0)
#define	HwERRADDR1								*(HwMECC4_EADDR_ALL+1)
#define	HwERRADDR2								*(HwMECC4_EADDR_ALL+2)
#define	HwERRADDR3								*(HwMECC4_EADDR_ALL+3)

#define	HwMECC4_EDATA_ALL						((volatile unsigned long *)0xF005B070)	// R, MLC ECC4 Error Data Register (can be array indexed from [0] to [3])
#define	HwMECC4_EDATA0							*(HwMECC4_EDATA_ALL+0)
#define	HwMECC4_EDATA1							*(HwMECC4_EDATA_ALL+1)
#define	HwMECC4_EDATA2							*(HwMECC4_EDATA_ALL+2)
#define	HwMECC4_EDATA3							*(HwMECC4_EDATA_ALL+3)

#define	HwMECC8_EADDR_ALL						((volatile unsigned long *)0xF005B050)	// R, MLC ECC8 Error Address Register (can be array indexed from [0] to [7])
#define	HwMECC8_EADDR0						*(HwMECC8_EADDR_ALL+0)
#define	HwMECC8_EADDR1						*(HwMECC8_EADDR_ALL+1)
#define	HwMECC8_EADDR2						*(HwMECC8_EADDR_ALL+2)
#define	HwMECC8_EADDR3						*(HwMECC8_EADDR_ALL+3)
#define	HwMECC8_EADDR4						*(HwMECC8_EADDR_ALL+4)
#define	HwMECC8_EADDR5						*(HwMECC8_EADDR_ALL+5)
#define	HwMECC8_EADDR6						*(HwMECC8_EADDR_ALL+6)
#define	HwMECC8_EADDR7						*(HwMECC8_EADDR_ALL+7)

#define	HwMECC8_EDATA_ALL						((volatile unsigned long *)0xF005B070)	// R, MLC ECC8 Error Data Register (can be array indexed from [0] to [7])
#define	HwMECC8_EDATA0							*(HwMECC8_EDATA_ALL+0)
#define	HwMECC8_EDATA1							*(HwMECC8_EDATA_ALL+1)
#define	HwMECC8_EDATA2							*(HwMECC8_EDATA_ALL+2)
#define	HwMECC8_EDATA3							*(HwMECC8_EDATA_ALL+3)
#define	HwMECC8_EDATA4							*(HwMECC8_EDATA_ALL+4)
#define	HwMECC8_EDATA5							*(HwMECC8_EDATA_ALL+5)
#define	HwMECC8_EDATA6							*(HwMECC8_EDATA_ALL+6)
#define	HwMECC8_EDATA7							*(HwMECC8_EDATA_ALL+7)

#define	HwERR_NUM								*(volatile unsigned long *)0xF005B090	// R, ECC Error Number Register
	#define	HwERR_NUM_SLC(X)						((HwERR_NUM & (3 << (2*(X)))) >> (2*(X)))
	#define	HwERR_NUM_MLC							(HwERR_NUM & 31)
	#define	HwERR_NUM_NOERR						0								// No Error
	#define	HwERR_NUM_SLC_ECC_ERR					1								// SLC ECC Error
	#define	HwERR_NUM_SLC_ERR1						2								// SLC ECC Correctable Error
	#define	HwERR_NUM_SLC_CORIMP					3								// Correction Impossible(SLC)
	#define	HwERR_NUM_MLC4_CORIMP					5								// Correction Impossible(MLC4)
	#define	HwERR_NUM_MLC8_ERR8					8								// 8 symbol Error (MLC8)
	#define	HwERR_NUM_MLC8_INSUFF					17								// Insufficient Data Error (MLC8)
	#define	HwERR_NUM_MLC8_EXCESS					18								// Excessive Data Error (MLC8)
	#define	HwERR_NUM_MLC8_ECC_ERR				19								// Error in Bit[9:8] (MLC8)
	#define	HwERR_NUM_MLC8_OUTOFMAP				20								// Error detected at out of Memory Map (MLC8)
	#define	HwERR_NUM_MLC8_CORIMP_MIN				21								// Minimum value when correction is impossible (MLC8)
	#define	HwERR_NUM_MLC8_CORIMP_MAX			29								// Maximum value when correction is impossible (MLC8)

	#define	HwERR_NUM_ERR1							1								// Correctable Error(SLC), Error Occurred(MLC3), 1 Error Occurred(MLC4)
	#define	HwERR_NUM_ERR2							2								// 2 Error Occurred(MLC4)
	#define	HwERR_NUM_ERR3							3								// 3 Error Occurred(MLC4)
	#define	HwERR_NUM_ERR4							4								// 4 Error Occurred(MLC4)
	#define	HwERR_NUM_ERR5							5								// 5 Error Occurred(MLC4)
	#define	HwERR_NUM_ERR6							6								// 5 Error Occurred(MLC4)
	#define	HwERR_NUM_ERR7							7								// 5 Error Occurred(MLC4)
	#define	HwERR_NUM_ERR8							8								// 5 Error Occurred(MLC4)

#define	HwECC_IREQ								*(volatile unsigned long *)0xF005B094	// R/W, ECC Interrupt Control Register
	#define	HwECC_IREQ_SEF							Hw21							// R, SLC ECC Encofing Finished / W, Clear SEF
	#define	HwECC_IREQ_SDF							Hw20							// R, SLC ECC Decofing Finished / W, Clear SDF
	#define	HwECC_IREQ_M4EF						Hw19							// R, MLC ECC4 Encofing Finished / W, Clear M4EF
	#define	HwECC_IREQ_M4DF						Hw18							// R, MLC ECC4 Decofing Finished / W, Clear M4DF/M4DI
	#define	HwECC_IREQ_M8EF						Hw17							// R, MLC ECC8 Encofing Finished / W, Clear M8EF
	#define	HwECC_IREQ_M8DF						Hw16							// R, MLC ECC8 Decofing Finished / W, Clear M8DF/M8DI
	#define	HwECC_IREQ_M4DI						Hw2								// R, MLC ECC4 Decofing Finished Interrupt / W, Clear M4DF/M4DI
	#define	HwECC_IREQ_M8DI						Hw0								// R, MLC ECC8 Decofing Finished Interrupt / W, Clear M8DF/M8DI
	#define	HwECC_IREQ_CLR							((Hw22-Hw16)|Hw2|Hw0)

#define	HwECC_FSMSTATE							*(volatile unsigned long *)0xF005B098	// R, ECC FSM State Register

#define	HwENCSEED								*(volatile unsigned long *)0xF005B0F0	// W, Test Mode Register
#define	HwENCMASK								*(volatile unsigned long *)0xF005B0F4	// W, Test Mode Register
#define	HwENCDATA								*(volatile unsigned long *)0xF005B0F8	// R/W, Test Mode Register

/************************************************************************
*	SPDIF Transmitter Register Define			(Base Addr = 0xF005C000)
************************************************************************/
#define	HwSPDIF_BASE							*(volatile unsigned long *)0xF005C000	// SPDIF Base Register

#define	HwTxVersion								*(volatile unsigned long *)0xF005C000	// R, Version Register
	#define	HwTxVersion_CSB							Hw12							// Channel Status Buffer Available bit
	#define	HwTxVersion_UDB							Hw11							// User Data Buffer Available bit
	#define	HwTxVersion_DW							Hw4								// Value of Data Width

#define	HwTxConfig								*(volatile unsigned long *)0xF005C004	// R/W, Configuration Register 
	#define	HwTxConfig_IEN							Hw2								// Interrupt Output Enable
	#define	HwTxConfig_TXD							Hw1								// Data Vaild
	#define	HwTxConfig_TXEN							Hw0								// Transmitter Enable

#define	HwTxChStat								*(volatile unsigned long *)0xF005C008	// R/W, Channel Status Control Register
	#define	HwTxChStat_FREQ_441						HwZERO							// 44.1Khz
	#define	HwTxChStat_FREQ_48						Hw6								// 48Khz
	#define	HwTxChStat_FREQ_32						Hw7								// 32Khz
	#define	HwTxChStat_FREQ_CON					(Hw7+Hw6)						// Sample Rate Converter
	#define	HwTxChStat_GSTS							Hw3								// Status Generation
	#define	HwTxChStat_PRE							Hw2								// Pre-emphasis
	#define	HwTxChStat_CPY							Hw1								// Copyright
	#define	HwTxChStat_AU							Hw0								// Data Format

#define	HwTxIntMask								*(volatile unsigned long *)0xF005C00C	// R/W, Interrupt Mask Register
	#define	HwTxIntMask_HCSB						Hw4								// Higher Channel Status/User Data Buffer Empty
	#define	HwTxIntMask_LCSB						Hw3								// Lower Channel Status/User Data Buffer Empty
	#define	HwTxIntMask_HSB							Hw2								// Higher Data Buffer Empty
	#define	HwTxIntMask_LSB							Hw1								// Lower Data Buffer Empty

#define	HwTxIntStat								*(volatile unsigned long *)0xF005C010	// R/W, Interrupt Status Register
	#define	HwTxIntStat_HCSB							Hw4								// Higher Channel Status/User Data Buffer Empty
	#define	HwTxIntStat_LCSB							Hw3								// Lower Channel Status/User Data Buffer Empty
	#define	HwTxIntStat_HSB							Hw2								// Higher Data Buffer Empty
	#define	HwTxIntStat_LSB							Hw1								// Lower Data Buffer Empty

#define	HwUserData								*(volatile unsigned long *)0xF005C080	// W, User Data Buffer 

#define	HwChStatus								*(volatile unsigned long *)0xF005C100	// W, Channel Status Buffer

#define	HwTxBuffer								*(volatile unsigned long *)0xF005C200	// W, Transmit Data Buffer

/***********************************************************************
*	 Camera Interface Register Define			(Base Addr = 0xF0060000)
************************************************************************/
#define	HwCIF_BASE								*(volatile unsigned long *)0xF0060000	// CIF Base Register

#define	HwICPCR1								*(volatile unsigned long *)0xF0060000	// W, Input Image Color/Pattern Configuration Register 1
	#define	HwICPCR1_ON							Hw31							// 0 : Can't operate CIF, 1 : Operating CIF
	#define	HwICPCR1_PWD							Hw30							// Power down mode in camera
	#define	HwICPCR1_TV_TVSYNC						Hw29							// TV sync signal
	#define	HwICPCR1_TV_CIFSYNC					HwZERO							// CIF sync signal
	#define	HwICPCR1_VI_INSERT						Hw28							// Insert Vertical Blank in 1 line
	#define	HwICPCR1_VI_NOINSERT					HwZERO							// Don't Insert Vertical Blank
	#define	HwICPCR1_BPS							Hw23							// Bypass Scaler
	#define	HwICPCR1_POL							Hw21							// PXCLK Polarity (Negative edge)
	#define	HwICPCR1_SKIP(X)						((X)*Hw18)						// Skip N frames.
	#define	HwICPCR1_NOT_SKIP						HwICPCR1_SKIP(0)				// Not Skip
	#define	HwICPCR1_SKIP_MASK						HwICPCR1_SKIP(7)
	#define	HwICPCR1_M420_NOT_CVT					HwZERO							// Not Convert
	#define	HwICPCR1_M420_ODD_SKIP				Hw17							// Converted in odd line skip
	#define	HwICPCR1_M420_EVEN_SKIP				(Hw17+Hw16)						// Converted in even line skip
	#define	HwICPCR1_BP							Hw15							// Bypass (non-separate)
	#define	HwICPCR1_BP_SEP						HwZERO							// Non-Bypass (separate)
	#define	HwICPCR1_BBS_LSB8						Hw14							// When bypass 16bits mode, LSB 8bits are stored in first
	#define	HwICPCR1_BBS_MSB8						HwZERO							// When bypass 16bits mode, MSB 8bits are stored in first
	#define	HwICPCR1_C656							Hw13							// Convert 656 format
	#define	HwICPCR1_CP_RGB						Hw12							// RGB(555,565,bayer) color pattern
	#define	HwICPCR1_CP_OTHER						HwZERO							// YCbCr(YUV/RGB) color pattern (Don't change pattern)
	#define	HwICPCR1_PF_444							HwZERO							// 4:4:4 format
	#define	HwICPCR1_PF_422							Hw10							// 4:2:2 format (don't change format)
	#define	HwICPCR1_PF_420							Hw11							// 4:2:0 format or RGB(555,565,bayer) mode
	#define	HwICPCR1_RGBM_BAYER					HwZERO							// Bayer RGB Mode
	#define	HwICPCR1_RGBM_RGB555					Hw8								// RGB555 Mode
	#define	HwICPCR1_RGBM_RGB565					Hw9								// RGB565 Mode
	#define	HwICPCR1_RGBBM_16						HwZERO							// 16bit mode
	#define	HwICPCR1_RGBBM_8DISYNC				Hw6								// 8bit disable sync (Non sync-port)
	#define	HwICPCR1_RGBBM_8						Hw7								// 8bit mode (bayer/555/565RGB), 8bit enable sync (sync-port)

																					// 555RGB	565RGB	444/422/420	BayerRGB	CCIR656
																					//---------------------------------------------------
	#define	HwICPCR1_CS_RGBMG						HwZERO							// RGB(MG)	RGB		R/Cb/U first	BG->GR		YCbYCr
	#define	HwICPCR1_CS_RGBLG						Hw4								// RGB(LG)	RGB		R/Cb/U first	GR->BG		YCrYCb
	#define	HwICPCR1_CS_BGRMG						Hw5								// BGR(MG)	BGR		B/Cr/V first	RG->GB		CbYCrY
	#define	HwICPCR1_CS_BGRLG						(Hw5+Hw4)						// BGR(LG)	BGR		B/Cr/V first	GB->RG		CrYCbY

	#define	HwICPCR1_BO_SW						Hw2								// Switch the MSB/LSB 8bit Bus
	#define	HwICPCR1_HSP_HIGH						Hw1								// Active high
	#define	HwICPCR1_HSP_LOW						HwZERO							// Active low
	#define	HwICPCR1_VSP_HIGH						Hw0								// Active high
	#define	HwICPCR1_VSP_LOW						HwZERO							// Active low

#define	Hw656FCR1								*(volatile unsigned long *)0xF0060004	// W, CCIR656 Format Configuration Register 1
	#define	Hw656FCR1_PSL_1ST						HwZERO							// The status word is located the first byte of EAV & SAV
	#define	Hw656FCR1_PSL_2ND						Hw25							// The status word is located the second byte of EAV & SAV
	#define	Hw656FCR1_PSL_3RD						Hw26							// The status word is located the third byte of EAV & SAV
	#define	Hw656FCR1_PSL_4TH						(Hw26+Hw25)						// The status word is located the forth byte of EAV & SAV
	#define	Hw656FCR1_FPV(X)						((X)*Hw16)						// First preamble value
	#define	Hw656FCR1_FPV_MASK						Hw656FCR1_FPV(255)
	#define	Hw656FCR1_SPV(X)						((X)*Hw8)						// Second preamble value
	#define	Hw656FCR1_SPV_MASK						Hw656FCR1_SPV(255)
	#define	Hw656FCR1_TPV(X)						((X)*Hw0)						// Third preamble value
	#define	Hw656FCR1_TPV_MASK						Hw656FCR1_TPV(255)

#define	Hw656FCR2								*(volatile unsigned long *)0xF0060008	// W, CCIR656 Format Configuration Register 2
	#define	Hw656FCR2_HB_LOCH(X)					((X)*Hw6)						// 'H' Location in Horizontal Blank (0~7)
	#define	Hw656FCR2_HB_LOCH_MASK				Hw656FCR2_HB_LOCH(7)
	#define	Hw656FCR2_HB_VALH_1					Hw5								// Value of 'H' is 1
	#define	Hw656FCR2_HB_VALH_0					HwZERO							// Value of 'H' is 0
	#define	Hw656FCR2_VB_LOCV(X)					((X)*Hw1)						// 'V' Location in Vertical Blank (0~7)
	#define	Hw656FCR2_VB_VALV_1					Hw0								// Value of 'V' is 1
	#define	Hw656FCR2_VB_VALV_0					HwZERO							// Value of 'V' is 0
	#define	Hw656FCR2_VB_LOCV_MASK				Hw656FCR2_VB_LOCV(7)

#define	HwIIS									*(volatile unsigned long *)0xF006000C	// W, Input Image Size (HSIZE[15:0], VSIZE[15:0])

#define	HwIIW1									*(volatile unsigned long *)0xF0060010	// W, Input Image Windowing 1 (Horizontal, HW1[15:0], HW2[15:0])

#define	HwIIW2									*(volatile unsigned long *)0xF0060014	// W, Input Image Windowing 2 (Vertical, VW1[15:0], VW2[15:0])

#define	HwCDCR1								*(volatile unsigned long *)0xF0060018	// W, DMA Configuratin Register 1
	#define	HwCDCR1_TM_INC							Hw3								// INC Transfer
	#define	HwCDCR1_TM_BURST						HwZERO							// Burst Transfer
	#define	HwCDCR1_LOCK_ON						Hw2								// Lock Transfer
	#define	HwCDCR1_LOCK_OFF						HwZERO							// Non-Lock Transfer
	#define	HwCDCR1_BS_1							HwZERO							// The DMA transfers the image data as 1 word to memory
	#define	HwCDCR1_BS_2							Hw0								// The DMA transfers the image data as 2 word to memory
	#define	HwCDCR1_BS_4							Hw1								// The DMA transfers the image data as 4 word to memory
	#define	HwCDCR1_BS_8							(Hw1+Hw0)						// The DMA transfers the image data as 8 word to memory (default)

#define	HwCDCR2									*(volatile unsigned long *)0xF006001C	// W, DMA Configuration Register 2 (Y/G channel base address)

#define	HwCDCR3									*(volatile unsigned long *)0xF0060020	// W, DMA Configuration Register 3 (U/R channel base address)

#define	HwCDCR4									*(volatile unsigned long *)0xF0060024	// W, DMA Configuration Register 4 (V/B channel base address)

#define	HwCDCR5									*(volatile unsigned long *)0xF0060028	// W, DMA Configuration Register 5 (Y/G channel end address, used for rolling)

#define	HwCDCR6									*(volatile unsigned long *)0xF006002C	// W, DMA Configuration Register 6 (U/R channel end address, used for rolling)

#define	HwCDCR7									*(volatile unsigned long *)0xF0060030	// W, DMA Configuration Register 7 (V/B channel end address, used for rolling)

#define	HwFIFOSTATE								*(volatile unsigned long *)0xF0060034	// R, FIFO Status Register
	#define	HwFIFOSTATE_CLR							Hw21							// 1:Clear, 0:Not Clear
	#define	HwFIFOSTATE_REO							Hw19							// 1:Overlay FIFO read error
	#define	HwFIFOSTATE_REV							Hw18							// 1:V(B) channel FIFO read error
	#define	HwFIFOSTATE_REU							Hw17							// 1:U(R) channel FIFO read error
	#define	HwFIFOSTATE_REY							Hw16							// 1:Y(G) channel FIFO read error
	#define	HwFIFOSTATE_WEO						Hw13							// 1:Overlay FIFO write error
	#define	HwFIFOSTATE_WEV						Hw12							// 1:V(B) channel FIFO write error
	#define	HwFIFOSTATE_WEU						Hw11							// 1:U(R) channel FIFO write error
	#define	HwFIFOSTATE_WEY						Hw10							// 1:Y(G) channel FIFO write error
	#define	HwFIFOSTATE_EO							Hw8								// 1:Overlay FIFO is empty
	#define	HwFIFOSTATE_EV							Hw7								// 1:V(B) channel FIFO is empty
	#define	HwFIFOSTATE_EU							Hw6								// 1:U(R) channel FIFO is empty
	#define	HwFIFOSTATE_EY							Hw5								// 1:Y(G) channel FIFO is empty
	#define	HwFIFOSTATE_FO							Hw3								// 1:Overlay FIFO is full
	#define	HwFIFOSTATE_FV							Hw2								// 1:V(B) channel FIFO is full
	#define	HwFIFOSTATE_FU							Hw1								// 1:U(R) channel FIFO is full
	#define	HwFIFOSTATE_FY							Hw0								// 1:Y(G) channel FIFO is full

#define	HwCIRQ									*(volatile unsigned long *)0xF0060038	// R/W, Interrupt & CIF Operating Register
	#define	HwCIRQ_IEN_EN							Hw31							// Interrupt Enable
	#define	HwCIRQ_URV								Hw30							// Update Register in VSYNC
	#define	HwCIRQ_ITY								Hw29							// Hold-up Interrupt Type (Hold until respond signal (ICR) is high)
	#define	HwCIRQ_ITY_PULSE						HwZERO							// Pulse Interrupt Type
	#define	HwCIRQ_ICR								Hw28							// Interrupt Clear
	#define	HwCIRQ_MVN								Hw26							// Mask Interrupt of VS negative edge
	#define	HwCIRQ_MVP								Hw25							// Mask Interrupt of VS positive edge
	#define	HwCIRQ_MVIT							Hw24							// Mask Interrupt of VCNT INterrupt
	#define	HwCIRQ_MSE								Hw23							// Mask Interrupt of Scaler Error
	#define	HwCIRQ_MSF								Hw22							// Mask Interrupt of Scaler finish
	#define	HwCIRQ_MENS							Hw21							// Mask Interrupt of Encoding start
	#define	HwCIRQ_MRLV							Hw20							// Mask Interrupt of Rolling V address
	#define	HwCIRQ_MRLU							Hw19							// Mask Interrupt of Rolling U address
	#define	HwCIRQ_MRLY							Hw18							// Mask Interrupt of Rolling Y address
	#define	HwCIRQ_MSCF							Hw17							// Mask Interrupt of Capture frame
	#define	HwCIRQ_MSOF							Hw16							// Mask Interrupt of Stored one frame
	#define	HwCIRQ_VSS								Hw12							// Status of vertical sync (vertical sync blank area)
	#define	HwCIRQ_VN								Hw10							// VS negative interrupt flag
	#define	HwCIRQ_VP								Hw9								// VS positive interrupt flag
	#define	HwCIRQ_VIT								Hw8								// VCNT Interrupt flag
	#define	HwCIRQ_SE								Hw7								// Scaler Error interrupt flag
	#define	HwCIRQ_SF								Hw6								// Scaler Finish interrupt flag
	#define	HwCIRQ_ENS								Hw5								// Encoding start stauts (Y(G) address is bigger than it's start address)
	#define	HwCIRQ_ROLV							Hw4								// Rolling V address status (V(B) address is moved to it's start address)
	#define	HwCIRQ_ROLU							Hw3								// Rolling U address status (U(R) address is moved to it's start address)
	#define	HwCIRQ_ROLY							Hw2								// Rolling Y address status (Y(G) address is moved to it's start address)
	#define	HwCIRQ_SCF								Hw1								// Stored captured frame
	#define	HwCIRQ_SOF								Hw0								// Stored one frame

#define	HwOCTRL1								*(volatile unsigned long *)0xF006003C	// W, Overlay Control 1
	#define	HwOCTRL1_OCNT_MAX						(Hw28+Hw27+Hw26+Hw25+Hw24)	//
	#define	HwOCTRL1_OM_BLOCK						Hw16							// Block image overlay
	#define	HwOCTRL1_OM_FULL						HwZERO							// Full image overlay
	#define	HwOCTRL1_OE_EN							Hw12							// Overlay enable
	#define	HwOCTRL1_XR1_100						Hw10							// 100% (when AP1 is 3 and AEN,CEN is 1)
	#define	HwOCTRL1_XR1_XOR						HwZERO							// XOR (when AP1 is 3 and AEN,CEN is 1)
	#define	HwOCTRL1_XR0_100						Hw9								// 100% (when AP0 is 3 and AEN,CEN is 1)
	#define	HwOCTRL1_XR0_XOR						HwZERO							// XOR (when AP0 is 3 and AEN,CEN is 1)
	#define	HwOCTRL1_AP1_25						HwZERO							// 25%
	#define	HwOCTRL1_AP1_50						Hw6								// 50%
	#define	HwOCTRL1_AP1_75						Hw7								// 75%
	#define	HwOCTRL1_AP1_100						(Hw7+Hw6)						// 100%
	#define	HwOCTRL1_AP0_25						HwZERO							// 25%
	#define	HwOCTRL1_AP0_50						Hw4								// 50%
	#define	HwOCTRL1_AP0_75						Hw5								// 75%
	#define	HwOCTRL1_AP0_100						(Hw5+Hw4)						// 100%
	#define	HwOCTRL1_AEN_EN						Hw2								// Alpha enable
	#define	HwOCTRL1_CEN_EN						Hw0								// Chroma key enable

#define	HwOCTRL2								*(volatile unsigned long *)0xF0060040	// W, Overlay Control 4
	#define	HwOCTRL2_CONV							Hw3								// Color Converter Enable
	#define	HwOCTRL2_RGB_565						HwZERO							// 565RGB
	#define	HwOCTRL2_RGB_555						Hw1								// 555RGB
	#define	HwOCTRL2_RGB_444						Hw2								// 444RGB
	#define	HwOCTRL2_RGB_332						(Hw2+Hw1)						// 332RGB
	#define	HwOCTRL2_MD							Hw0								// Color Mode, 0 = YUV, 1 = RGB

#define	HwOCTRL3								*(volatile unsigned long *)0xF0060044	// W, Overlay Control 2
	#define	HwOCTRL3_KEYR(X)						((X)*Hw16)
	#define	HwOCTRL3_KEYG(X)						((X)*Hw8)
	#define	HwOCTRL3_KEYB(X)						((X)*Hw0)
	#define	HwOCTRL3_KEYR_MAX						HwOCTRL3_KEYR(255)
	#define	HwOCTRL3_KEYG_MAX						HwOCTRL3_KEYG(255)
	#define	HwOCTRL3_KEYB_MAX						HwOCTRL3_KEYB(255)
	#define	HwOCTRL3_KEYR_MASK					HwOCTRL3_KEYR(255)
	#define	HwOCTRL3_KEYG_MASK					HwOCTRL3_KEYG(255)
	#define	HwOCTRL3_KEYB_MASK					HwOCTRL3_KEYB(255)

#define	HwOCTRL4								*(volatile unsigned long *)0xF0060048	// W, Overlay Control 3
	#define	HwOCTRL4_MKEYR(X)						((X)*Hw16)
	#define	HwOCTRL4_MKEYG(X)						((X)*Hw8)
	#define	HwOCTRL4_MKEYB(X)						((X)*Hw0)
	#define	HwOCTRL4_MKEYR_MAX					HwOCTRL4_MKEYR(255)
	#define	HwOCTRL4_MKEYG_MAX					HwOCTRL4_MKEYG(255)
	#define	HwOCTRL4_MKEYB_MAX					HwOCTRL4_MKEYB(255)
	#define	HwOCTRL4_MKEYR_MASK					HwOCTRL4_MKEYR(255)
	#define	HwOCTRL4_MKEYG_MASK					HwOCTRL4_MKEYG(255)
	#define	HwOCTRL4_MKEYB_MASK					HwOCTRL4_MKEYB(255)

#define	HwOIS									*(volatile unsigned long *)0xF006004C	// W, Overlay Image Size (OHSIZE[15:0], OVSIZE[15:0])

#define	HwOIW1									*(volatile unsigned long *)0xF0060050	// W, Overlay Image Windowing 1 (Horizontal, OHW1[15:0], OHW2[15:0])

#define	HwOIW2									*(volatile unsigned long *)0xF0060054	// W, Overlay Image Windowing 2 (Vertical, OVW1[15:0], OVW2[15:0])

#define	HwCOBA									*(volatile unsigned long *)0xF0060058	// W, Overlay Base Address

#define	HwCDS									*(volatile unsigned long *)0xF006005C	// W, Camera Down Scaler
	#define	HwCDS_SFH_1							HwZERO							// 1/1 down scale
	#define	HwCDS_SFH_2							Hw4								// 1/2 down scale
	#define	HwCDS_SFH_4							Hw5								// 1/4 down scale
	#define	HwCDS_SFH_8							(Hw5+Hw4)						// 1/8 down scale
	#define	HwCDS_SFV_1							HwZERO							// 1/1 down scale
	#define	HwCDS_SFV_2							Hw2								// 1/2 down scale
	#define	HwCDS_SFV_4							Hw3								// 1/4 down scale
	#define	HwCDS_SFV_8							(Hw3+Hw2)						// 1/8 down scale
	#define	HwCDS_SEN_EN							Hw0								// Scale enable

#define	HwCCM1									*(volatile unsigned long *)0xF0060060	// R/W, Capture Mode 1
	#define	HwCCM1_CB								Hw10							// Capture Busy
	#define	HwCCM1_EIT								Hw9								// Encoding INT count
	#define	HwCCM1_UES								Hw8								// Using Encoding Start Address
	#define	HwCCM1_RLV								Hw3								// Rolling address V
	#define	HwCCM1_RLU								Hw2								// Rolling address U
	#define	HwCCM1_RLY								Hw1								// Rolling address Y
	#define	HwCCM1_CAP								Hw0								// Image Capture

#define	HwCCM2									*(volatile unsigned long *)0xF0060064	// R/W, Capture Mode 2
	#define	HwCCM2_VEN								Hw0								// VCNT folling enable

#define	HwCESA									*(volatile unsigned long *)0xF0060068	// R/W, Encoding Start Address

#define	HwCR2Y									*(volatile unsigned long *)0xF006006C	// R/W, R2Y Configuration
	#define	HwCR2Y_565RGB_SEQ16					HwZERO							// 16bit 565RGB (RGB sequence)
	#define	HwCR2Y_565BGR_SEQ16					Hw1								// 16bit 565RGB (BGR sequence)
	#define	HwCR2Y_555RGB_GAR16					Hw3								// 16bit 555RGB	(RGB-garbage)
	#define	HwCR2Y_555BGR_GAR16					(Hw3+Hw1)						// 16bit 555RGB (BGR-garbage)
	#define	HwCR2Y_555GAR_RGB16					(Hw3+Hw2)						// 16bit 555RGB	(garbage-RGB)
	#define	HwCR2Y_555GAR_BGR16					(Hw3+Hw2+Hw1)					// 16bit 555RGB (garbage-BGR)
	#define	HwCR2Y_565RGB_SEQ8						Hw4								// 8bit 565RGB (RGB sequence)
	#define	HwCR2Y_565BGR_SEQ8						(Hw4+Hw1)						// 8bit 565RGB (BGR sequence)
	#define	HwCR2Y_555RGB_GAR8					(Hw4+Hw3)						// 8bit 555RGB (RGB-garbage)
	#define	HwCR2Y_555BGR_GAR8					(Hw4+Hw3+Hw1)					// 8bit 555RGB (BGR-garbage)
	#define	HwCR2Y_555GAR_RGB8					(Hw4+Hw3+Hw2)					// 8bit 555RGB (garbage-RGB)
	#define	HwCR2Y_555GAR_BGR8					(Hw4+Hw3+Hw2+Hw1)				// 8bit 555RGB (garbage-BGR)
	#define	HwCR2Y_EN								Hw0								// R2Y Enable

#define	HwCCYA									*(volatile unsigned long *)0xF0060070	// R, Current Y Address

#define	HwCCUA									*(volatile unsigned long *)0xF0060074	// R, Current U Address

#define	HwCCVA									*(volatile unsigned long *)0xF0060078	// R, Current V Address

#define	HwCCLC									*(volatile unsigned long *)0xF006007C	// R, Current Line Count

#define	HwCEM									*(volatile unsigned long *)0xF0060100	// R/W, Effect Mode Register
	#define	HwCEM_UVS								Hw15							// UV Swap (V-U-V-U sequence)
	#define	HwCEM_UVS_NOSWAP						HwZERO							// UV NoSwap (U-V-U-V sequence)
	#define	HwCEM_VB								Hw14							// V Bias (V Channel value offset) enabled
	#define	HwCEM_UB								Hw13							// U Bias (U Channel value offset) enabled
	#define	HwCEM_YB								Hw12							// Y Bias (Y Channel value offset) enabled
	#define	HwCEM_YCS								Hw11							// YC Swap (Y-U-Y-V sequence)
	#define	HwCEM_YCS_NOSWAP						HwZERO							// YC NoSwap (U-Y-V-Y sequence)
	#define	HwCEM_IVY								Hw10							// Invert Y
	#define	HwCEM_STC								Hw9								// Strong C
	#define	HwCEM_YCL								Hw8								// Y Clamp (Y value clipping)
	#define	HwCEM_CS								Hw7								// C Select (Color filter)
	#define	HwCEM_SKT								Hw6								// Sketch Enable
	#define	HwCEM_EMM								Hw5								// Emboss Mode
	#define	HwCEM_EMB								Hw4								// Emboss
	#define	HwCEM_NEGA								Hw3								// Nagative Mode
	#define	HwCEM_GRAY								Hw2								// Gray Mode
	#define	HwCEM_SEPI								Hw1								// Sepia Mode
	#define	HwCEM_NOR								Hw0								// Normal Mode

#define	HwCSUV									*(volatile unsigned long *)0xF0060104	// Sepia UV (SEPIA_U[7:0], SEPIA_V[7:0])

#define	HwCCS									*(volatile unsigned long *)0xF0060108	// Color Selection (USTART[7:0], UEND[7:0], VSTART[7:0], VEND[7:0])

#define	HwCHFC									*(volatile unsigned long *)0xF006010C	// H filter Coefficient (COEFF0[7:0], COEFF1[7:0], COEFF2[7:0])

#define	HwCST									*(volatile unsigned long *)0xF0060110	// Sketch Threshold

#define	HwCCT									*(volatile unsigned long *)0xF0060114	// Clamp Threshold

#define	HwCBR									*(volatile unsigned long *)0xF0060118	// Bias Register (YBIAS[7:0], UBIAS[7:0], VBIAS[7:0])

#define	HwCEIS									*(volatile unsigned long *)0xF006011C	// Effect Image Size
	#define	HwCEIS_HSIZE(X)							((X)*Hw16)
	#define	HwCEIS_HSIZE_MASK						HwCEIS_HSIZE(2047)
	#define	HwCEIS_VSIZE(X)							((X)*Hw0)
	#define	HwCEIS_VSIZE_MASK						HwCEIS_VSIZE(2047)

#define	HwCIC									*(volatile unsigned long *)0xF0060140	// Inpath Control
	#define	HwCIC_H2HWAIT(X)						((X)*Hw16)						// H-Sync to H-Sync wait cycle
	#define	HwCIC_H2HWAIT_MASK					HwCIC_H2HWAIT(65535)
	#define	HwCIC_STB_CYCLE(X)						((X)*Hw8)						// CCIR strobe cycle
	#define	HwCIC_STB_CYCLE_MASK					HwCIC_STB_CYCLE(255)
	#define	HwCIC_INPR								Hw3								//
	#define	HwCIC_FA								Hw2								// Flush All
	#define	HwCIC_INE								Hw1								// Inpath Enable
	#define	HwCIC_INP								Hw0								// Inpath Mode

#define	HwCISA1									*(volatile unsigned long *)0xF0060144	// Inpath SRC Address 1 (SRC_BASE[31:28], SRC_BASE_Y[27:0])

#define	HwCISA2									*(volatile unsigned long *)0xF0060148	// Inpath SRC Address 2 (SRC_TYPE[29:28], SRC_BASE_U[27:0])
	#define	HwCISA2_SRCTYPE_422SEQ0				HwZERO							// 4:2:2 SEQ0
	#define	HwCISA2_SRCTYPE_422SEQ1				Hw28							// 4:2:2 SEQ1
	#define	HwCISA2_SRCTYPE_422SEP					Hw29							// 4:2:2 Separate
	#define	HwCISA2_SRCTYPE_420SEP					(Hw29+Hw28)						// 4:2:0 Separate

#define	HwCISA3									*(volatile unsigned long *)0xF006014C	// Inpath SRC Address 3 (SRC_BASE_V[27:0])

#define	HwCISS									*(volatile unsigned long *)0xF0060150	// Inpath SRC Size
	#define	HwCISS_HSIZE(X)							((X)*Hw16)
	#define	HwCISS_HSIZE_MASK						HwCISS_HSIZE(4095)
	#define	HwCISS_VSIZE(X)							((X)*Hw0)
	#define	HwCISS_VSIZE_MASK						HwCISS_VSIZE(4095)

#define	HwCISO									*(volatile unsigned long *)0xF0060154	// Inpath SRC Offset
	#define	HwCISO_OFFSET_Y(X)						((X)*Hw16)
	#define	HwCISO_OFFSET_Y_MASK					HwCISO_OFFSET_Y(4095)
	#define	HwCISO_OFFSET_C(X)						((X)*Hw0)
	#define	HwCISO_OFFSET_C_MASK					HwCISO_OFFSET_C(4095)

#define	HwCIDS									*(volatile unsigned long *)0xF0060158	// Inpath DST Size
	#define	HwCIDS_HSIZE(X)							((X)*Hw16)
	#define	HwCIDS_HSIZE_MASK						HwCIDS_HSIZE(4095)
	#define	HwCIDS_VSIZE(X)							((X)*Hw0)
	#define	HwCIDS_VSIZE_MASK						HwCIDS_VSIZE(4095)

#define	HwCIS									*(volatile unsigned long *)0xF006015C	// Inpath Scale
	#define	HwCIS_HSCALE(X)							((X)*Hw16)
	#define	HwCIS_HSCALE_MASK						HwCIS_HSCALE(0x3FFF)
	#define	HwCIS_VSCALE(X)							((X)*Hw0)
	#define	HwCIS_VSCALE_MASK						HwCIS_VSCALE(0x3FFF)

#define	HwCSC									*(volatile unsigned long *)0xF0060200	// Scaler CTRL
	#define	HwCSC_EN								Hw0								// Scaler Enable

#define	HwCSSF									*(volatile unsigned long *)0xF0060204	// Scaler Scale Factor
	#define	HwCSSF_HSCALE(X)						((X)*Hw16)
	#define	HwCSSF_HSCALE_MASK					HwCSSF_HSCALE(0x3FFF)
	#define	HwCSSF_VSCALE(X)						((X)*Hw0)
	#define	HwCSSF_VSCALE_MASK					HwCSSF_VSCALE(0x3FFF)

#define	HwCSSO									*(volatile unsigned long *)0xF0060208	// Scaler SRC Offset
	#define	HwCSSO_HOFFSET(X)						((X)*Hw16)
	#define	HwCSSO_HOFFSET_MASK					HwCSSO_HOFFSET(4095)
	#define	HwCSSO_VOFFSET(X)						((X)*Hw0)
	#define	HwCSSO_VOFFSET_MASK					HwCSSO_VOFFSET(4095)

#define	HwCSSS									*(volatile unsigned long *)0xF006020C	// Scaler SRC Size
	#define	HwCSSS_HSIZE(X)							((X)*Hw16)
	#define	HwCSSS_HSIZE_MASK						HwCSSS_HSIZE(4095)
	#define	HwCSSS_VSIZE(X)							((X)*Hw0)
	#define	HwCSSS_VSIZE_MASK						HwCSSS_VSIZE(4095)

#define	HwCSDS									*(volatile unsigned long *)0xF0060210	// Scaler DST Size
	#define	HwCSDS_HSIZE(X)						((X)*Hw16)
	#define	HwCSDS_HSIZE_MASK						HwCSDS_HSIZE(4095)
	#define	HwCSDS_VSIZE(X)						((X)*Hw0)
	#define	HwCSDS_VSIZE_MASK						HwCSDS_VSIZE(4095)

/***********************************************************************
*	MSC(Memory-to-Memory Scaler) Define			(Base Addr = 0xF0070000)
************************************************************************/
#define	HwMSC_BASE								*(volatile unsigned long *)0xF0070000	// MSC Base Register

#define	HwSRCBASEY								*(volatile unsigned long *)0xF0070000	// R/W, Source Base Address for Y

#define	HwSRCBASEU								*(volatile unsigned long *)0xF0070004	// R/W, Source Base Address for U(Cb)

#define	HwSRCBASEV								*(volatile unsigned long *)0xF0070008	// R/W, Source Base Address for V(Cr)

#define	HwSRCSIZE								*(volatile unsigned long *)0xF007000C	// R/W, Source Size Information Register
	#define	HwSRCSIZE_C_OFF(X)						((X)*Hw16)
	#define	HwSRCSIZE_C_OFF_MASK					HwSRCSIZE_C_OFF(4095)
	#define	HwSRCSIZE_Y_OFF(X)						((X)*Hw0)
	#define	HwSRCSIZE_Y_OFF_MASK					HwSRCSIZE_Y_OFF(4095)

#define	HwSRCOFF								*(volatile unsigned long *)0xF0070010	// R/W, Source Offset Information Register
	#define	HwSRCOFF_C_OFF(X)						((X)*Hw16)
	#define	HwSRCOFF_C_OFF_MASK					HwSRCOFF_C_OFF(4095)
	#define	HwSRCOFF_Y_OFF(X)						((X)*Hw0)
	#define	HwSRCOFF_Y_OFF_MASK					HwSRCOFF_Y_OFF(4095)

#define	HwSRCCFG								*(volatile unsigned long *)0xF0070014	// R/W, Source Configuration Register
	#define	HwSRCCFG_TYPE(X)						((X)*Hw0)
	#define	HwSRCCFG_422SEQ0						HwSRCCFG_TYPE(0)				// YUV 4:2:2 Sequential Mode 0
	#define	HwSRCCFG_422SEQ1						HwSRCCFG_TYPE(1)				// YUV 4:2:2 Sequential Mode 1
	#define	HwSRCCFG_422SEP						HwSRCCFG_TYPE(2)				// YUV 4:2:2 Separate Mode
	#define	HwSRCCFG_420SEP						HwSRCCFG_TYPE(3)				// YUV 4:2:0 Separate Mode
	#define	HwSRCCFG_565							HwSRCCFG_TYPE(4)				// RGB 565
	#define	HwSRCCFG_555							HwSRCCFG_TYPE(5)				// RGB 555
	#define	HwSRCCFG_444							HwSRCCFG_TYPE(6)				// RGB 444
	#define	HwSRCCFG_454							HwSRCCFG_TYPE(7)				// RGB 454
	#define	HwSRCCFG_TYPE_MASK					HwSRCCFG_TYPE(7)

#define	HwDSTBASEY								*(volatile unsigned long *)0xF0070020	// R/W, Destination Base Address for Y

#define	HwDSTBASEU								*(volatile unsigned long *)0xF0070024	// R/W, Destination Base Address for U(Cb)

#define	HwDSTBASEV								*(volatile unsigned long *)0xF0070028	// R/W, Destination Base Address for V(Cr)

#define	HwDSTSIZE								*(volatile unsigned long *)0xF007002C	// R/W, Destination Size Information Register
	#define	HwDSTSIZE_VSIZE(X)						((X)*Hw16)
	#define	HwDSTSIZE_VSIZE_MASK					HwDSTSIZE_VSIZE(4095)
	#define	HwDSTSIZE_HSIZE(X)						((X)*Hw0)
	#define	HwDSTSIZE_HSIZE_MASK					HwDSTSIZE_HSIZE(4095)

#define	HwDSTOFF								*(volatile unsigned long *)0xF0070030	// R/W, Destination Offset Information Register
	#define	HwDSTOFF_C_OFF(X)						((X)*Hw16)
	#define	HwDSTOFF_C_OFF_MASK					HwDSTOFF_C_OFF(4095)
	#define	HwDSTOFF_Y_OFF(X)						((X)*Hw0)
	#define	HwDSTOFF_Y_OFF_MASK					HwDSTOFF_Y_OFF(4095)

#define	HwDSTCFG								*(volatile unsigned long *)0xF0070034	// R/W, Destination Configuration Register
	#define	HwDSTCFG_COP							Hw11							// Chrominance Writing Mode Register Defined for 4:2:0 Seperate Mode
																					// 0 : Y0->U0->V0->Y1->Y2->U1...
																					// 1 : Y0->U0->Y1->V0->Y2->U1...
	#define	HwDSTCFG_WAITCNT(X)					((X)*Hw8)
	#define	HwDSTCFG_WAITCNT_MASK					HwDSTCFG_WAITCNT(7)
	#define	HwDSTCFG_RDY							Hw6								// Wait until Output FIFO is not empty
	#define	HwDSTCFG_RDY_WAITCNT					HwZERO							// Wait for [WAITCNT+1] cycle
	#define	HwDSTCFG_PATH_LCD						Hw4								// Destination Type Register (to LCD)
	#define	HwDSTCFG_PATH_MEM						HwZERO							// Destination Type Register (to Memory)
	#define	HwDSTCFG_TYPE(X)						((X)*Hw0)
	#define	HwDSTCFG_422SEQ0						HwDSTCFG_TYPE(0)				// 4:2:2 Sequential Mode 0
	#define	HwDSTCFG_422SEQ1						HwDSTCFG_TYPE(1)				// 4:2:2 Sequential Mode 1
	#define	HwDSTCFG_422SEP						HwDSTCFG_TYPE(2)				// 4:2:2 Separate Mode
	#define	HwDSTCFG_420SEP						HwDSTCFG_TYPE(3)				// 4:2:0 Separate Mode
	#define	HwDSTCFG_565							HwDSTCFG_TYPE(4)				// RGB 565
	#define	HwDSTCFG_555							HwDSTCFG_TYPE(5)				// RGB 555
	#define	HwDSTCFG_444							HwDSTCFG_TYPE(6)				// RGB 444
	#define	HwDSTCFG_454							HwDSTCFG_TYPE(7)				// RGB 454
	#define	HwDSTCFG_TYPE_MASK					HwDSTCFG_TYPE(7)

#define	HwSC_RATIO								*(volatile unsigned long *)0xF0070040	// R/W, Scaling Ratio Register
#define	HwMSCINF								*(volatile unsigned long *)0xF0070040	// R/W, Scaling Ratio Register
	#define	HwSC_RATIO_VRATIO(X)					((X)*Hw16)						// Vertical scale ratio (= 256*SRC_VSIZE/DST_VSIZE)
	#define	HwMSCINF_VRATIO						((X)*Hw16)
	#define	HwSC_RATIO_VRATIO_MASK				HwSC_RATIO_VRATIO(0x3FFF)
	#define	HwMSCINF_VRATIO_MASK					HwSC_RATIO_VRATIO(0x3FFF)
	#define	HwSC_RATIO_HRATIO(X)					((X)*Hw0)						// Horizontal scale ratio (= 256*SRC_HSIZE/DST_HSIZE)
	#define	HwMSCINF_HRATIO						((X)*Hw0)
	#define	HwSC_RATIO_HRATIO_MASK				HwSC_RATIO_HRATIO(0x3FFF)
	#define	HwMSCINF_HRATIO_MASK					HwSC_RATIO_HRATIO(0x3FFF)

#define	HwSC_CTRL								*(volatile unsigned long *)0xF0070044	// R/W, Scale Control Register
#define	HwMSCCTR								*(volatile unsigned long *)0xF0070044	// R/W, Scale Control Register
	#define	HwMSCCTR_FLS							Hw31							// Flush the internal FIFOs
	#define	HwMSCCTR_TST							Hw30							// Should be zero for test purpose
	#define	HwMSCCTR_REN_EN						Hw23							// Enable Rolling Operation Mode (can use rolling interrupt, rolling go-stop)
	#define	HwSC_CTRL_REN_EN						Hw23							// Enable Rolling Operation Mode (can use rolling interrupt, rolling go-stop)
	#define	HwMSCCTR_MEN_EN						Hw22							// Enable Middle Operation Mode (can use middle interrupt, middle go-stop)
	#define	HwSC_CTRL_MEN_EN						Hw22							// Enable Middle Operation Mode (can use middle interrupt, middle go-stop)
	#define	HwMSCCTR_RLS_RELEASE					Hw19							// Release stop mode (operation continue). This bit is cleared automatically
	#define	HwSC_CTRL_RLS_RELEASE					Hw19							// Release stop mode (operation continue). This bit is cleared automatically
	#define	HwMSCCTR_RGSM_EN						Hw17							// Enable Rolling Go-Stop Mode (scaler stop operation after DST_ROLL_CNT lines)
	#define	HwSC_CTRL_RGSM_EN						Hw17							// Enable Rolling Go-Stop Mode (scaler stop operation after DST_ROLL_CNT lines)
	#define	HwMSCCTR_MGSM_EN						Hw16							// Enable Middle Go-Stop Mode (scaler stop operation after DST_MID_CNT lines)
	#define	HwSC_CTRL_MGSM_EN						Hw16							// Enable Middle Go-Stop Mode (scaler stop operation after DST_MID_CNT lines)
	#define	HwMSCCTR_RIRQ_EN						Hw7								// Enable Rolling Interrupt
	#define	HwSC_CTRL_RIRQ_EN						Hw7								// Enable Rolling Interrupt
	#define	HwMSCCTR_MIRQ_EN						Hw6								// Enable Middle Interrupt
	#define	HwSC_CTRL_MIRQ_EN						Hw6								// Enable Middle Interrupt
	#define	HwMSCCTR_IEN_BUSY						Hw2								// Interrupt Enable Register
	#define	HwSC_CTRL_IEN_BUSY						Hw2								// Interrupt Enable Register
	#define	HwMSCCTR_IEN_RDY						Hw1								// Interrupt Enable Register
	#define	HwSC_CTRL_IEN_RDY						Hw1								// Interrupt Enable Register
	#define	HwMSCCTR_EN							Hw0								// Enable Register
	#define	HwSC_CTRL_EN							Hw0								// Enable Register

#define	HwSC_STATUS							*(volatile unsigned long *)0xF0070048	// R/W, Status Register
#define	HwMSCSTR								*(volatile unsigned long *)0xF0070048	// R/W, Status Register
	#define	HwMSCSTR_IR							Hw7								// Rolling Interrupt Flag (Cleared by writing this bit to 1)
	#define	HwSC_STATUS_IR							Hw7								// Rolling Interrupt Flag (Cleared by writing this bit to 1)
	#define	HwMSCSTR_IM							Hw6								// Middle Interrupt Flag (Cleared by writing this bit to 1)
	#define	HwSC_STATUS_IM							Hw6								// Middle Interrupt Flag (Cleared by writing this bit to 1)
	#define	HwMSCSTR_IBUSY							Hw5								// Busy Interrupt Flag
	#define	HwSC_STATUS_IBUSY						Hw5								// Busy Interrupt Flag
	#define	HwMSCSTR_IRDY							Hw4								// Ready Interrupt Flag
	#define	HwSC_STATUS_IRDY						Hw4								// Ready Interrupt Flag
	#define	HwMSCSTR_BUSY							Hw1								// Busy Status Register
	#define	HwSC_STATUS_BUSY						Hw1								// Busy Status Register
	#define	HwMSCSTR_RDY							Hw0								// Ready Status Register
	#define	HwSC_STATUS_RDY						Hw0								// Ready Status Register

#define	HwDST_RM_CNT							*(volatile unsigned long *)0xF0070050	// R/W, Rolling & Middle Counter
	#define	HwDST_RM_CNT_ROLL(X)					((X)*Hw16)
	#define	HwDST_RM_CNT_ROLL_MASK				HwDST_RM_CNT_ROLL(2047)
	#define	HwDST_RM_CNT_MID(X)					((X)*Hw0)
	#define	HwDST_RM_CNT_MID_MASK					HwDST_RM_CNT_MID(2047)

#define	HwC_R_CNT								*(volatile unsigned long *)0xF0070054	// R, Current Rolling Counter
	#define	HwC_R_CNT_ROLL							(HwC_R_CNT >> 16)

/************************************************************************
*	Channel 0 Memory Controller Register Define	(Base Addr = 0xF1000000)
************************************************************************/
#define	HwEMC_BASE								*(volatile unsigned long *)0xF1000000	// External Memory Controller Base Register

#define	HwSDCFG								*(volatile unsigned long *)0xF1000000	// R/W, SDRAM Configuration
	#define	HwSDCFG_CL								Hw31							// CAS Latency
	#define	HwSDCFG_BW							Hw30							// Bus Width
	#define	HwSDCFG_CW(X)							((X)*Hw28)						// CAS address width
	#define	HwSDCFG_CW8							HwSDCFG_CW(0)
	#define	HwSDCFG_CW9							HwSDCFG_CW(2)
	#define	HwSDCFG_CW10							HwSDCFG_CW(3)
	#define	HwSDCFG_CW_MASK						HwSDCFG_CW(3)
	#define	HwSDCFG_RC(X)							((X)*Hw24)						// Refresh to Idle cycle parameter
	#define	HwSDCFG_RC_MASK						HwSDCFG_RC(15)
	#define	HwSDCFG_RCD(X)							((X)*Hw20)						// RAS to CAS cycle parameter
	#define	HwSDCFG_RCD_MASK						HwSDCFG_RCD(15)
	#define	HwSDCFG_WR(X)							((X)*Hw18)						// Write to Read cycle parameter
	#define	HwSDCFG_WR_MASK						HwSDCFG_WR(3)
	#define	HwSDCFG_RP(X)							((X)*Hw12)						// Precharge to Refresh cycle parameter
	#define	HwSDCFG_RP_MASK						HwSDCFG_RP(15)
	#define	HwSDCFG_RW(X)							((X)*Hw10)						// CAS address width
	#define	HwSDCFG_RW11							HwSDCFG_RW(2)
	#define	HwSDCFG_RW12							HwSDCFG_RW(0)
	#define	HwSDCFG_RW13							HwSDCFG_RW(1)
	#define	HwSDCFG_RW_MASK						HwSDCFG_RW(3)
	#define	HwSDCFG_AM_RBC						Hw3								// Address Matching Configuration (RAS-BA-CAS)
	#define	HwSDCFG_AM_BRC						HwZERO							// Address Matching Configuration (BA-RAS-CAS)
	#define	HwSDCFG_SRF_EN							Hw0								// Self-Refresh Mode Enable

#define	HwSDFSM								*(volatile unsigned long *)0xF1000004	// R, SDRAM FSM Status

#define	HwMCFG									*(volatile unsigned long *)0xF1000008	// R/W, Misc. Configuration
	#define	HwMCFG_RDY								Hw15							// Bus Width Flag
	#define	HwMCFG_XDM								Hw14							//
	#define	HwMCFG_BW								(Hw12+Hw11)						// Read only register for external Bus-width Configuration
	#define	HwMCFG_SDW							Hw7								// Wait 1 cycle for reading from SDRAM
	#define	HwMCFG_ENCK							Hw6								// Enable Dynamic SDCLK control
	#define	HwMCFG_ECKE							Hw5								// SDCKE enabled
	#define	HwMCFG_SDEN							Hw4								// SDRAM Enable (SDCFG should be ahead initialized with appropriate value)
	#define	HwMCFG_CKM								Hw1								// SDRAM Clock Output Mask
	#define	HwMCFG_ERF								Hw0								// Refresh cycles occurred by external refresh clock

#define	HwCSCFG0								*(volatile unsigned long *)0xF1000010	// R/W, Ext. CS Configuration
	#define	HwCSCFG_BW(X)							((X)*Hw22)
	#define	HwCSCFG_BW_8							HwCSCFG_BW(3)
	#define	HwCSCFG_BW_16							HwCSCFG_BW(2)
	#define	HwCSCFG_BW_32							HwCSCFG_BW(0)
	#define	HwCSCFG_PSIZE_256						HwZERO
	#define	HwCSCFG_PSIZE_512						Hw17
	#define	HwCSCFG_PSIZE_1024						Hw18
	#define	HwCSCFG_PSIZE_2048						(Hw18+Hw17)
	#define	HwCSCFG_CADDR							Hw14
	#define	HwCSCFG_OD								Hw27							// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for OE signal
	#define	HwCSCFG_WD							Hw26							// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for WE signal
	#define	HwCSCFG_URDY							Hw21							// Use Ready
	#define	HwCSCFG_RDY							Hw20							// Ready/ Busy State
	#define	HwCSCFG_AMSK							Hw19							// Address Mask
	#define	HwCSCFG_STP(X)							((X)*Hw11)						// N cycle issued between falling edge of nCS and nOE/nWE
	#define	HwCSCFG_STP_MASK						HwCSCFG_STP(7)
	#define	HwCSCFG_PW(X)							((X)*Hw3)						// (N+1) cycle issued between falling edge and rising edge of nOE/nWE
	#define	HwCSCFG_PW_MASK						HwCSCFG_PW(255)
	#define	HwCSCFG_HLD(X)							((X)*Hw0)						// N cycle issued between rising edge of nOE/nWE and nCS
	#define	HwCSCFG_HLD_MASK						HwCSCFG_HLD(7)

#define	HwCSCFG3								*(volatile unsigned long *)0xF100001C	// R/W, Ext. CS Configration
	#define	HwCSCFG3_OD							Hw27							// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for OE signal
	#define	HwCSCFG3_WD							Hw26							// When STP and HLD are zero, 1 cycle would be added for delayed by half-pulse for WE signal
	#define	HwCSCFG3_URDY							Hw21							// Use Ready
	#define	HwCSCFG3_RDY							Hw20							// Ready/ Busy Select
	#define	HwCSCFG3_AMSK							Hw19							// Address Mask

#define	HwCLKCFG								*(volatile unsigned long *)0xF1000020	// R/W,

#define	HwSDCMD								*(volatile unsigned long *)0xF1000024	// W,
	#define	HwSDCMD_CKE							Hw17
	#define	HwSDCMD_A10							Hw16
	#define	HwSDCMD_CSN							Hw15
	#define	HwSDCMD_RAS							Hw14
	#define	HwSDCMD_CAS							Hw13
	#define	HwSDCMD_WEN							Hw12
	#define	HwSDCMD_BA(X)							((X)*Hw10)
	#define	HwSDCMD_CADR(X)						((X)*Hw0)

#define	HwSDCFG1								*(volatile unsigned long *)0xF1000028	// R/W, SDRAM Configuration Register 1
        /*
                                    POR_0(PowerOn)    POR_1        POR_2            POR_3        POR_4        INIT_2            IDLE
            ------------------------------------------------------------------------------------------------
            SDCKE              Low                       High            High                Low           High           High                High
            SDEN                X                           X                X                    Rising        High           High                High
            Description        Self-Refresh           Exit SR       Auto-Refresh   Enter SR    Exit SR       Auto-Refresh   Idle
            ------------------------------------------------------------------------------------------------
            Applied Cycle     X                    tSR2AR       NAP                tSRP          tSR2AR      NAI
        */
	#define	HwSDCFG1_tSR2AR(X)						((X)*Hw24)						// Minimum cycles of exiting self-refresh state
	#define	HwSDCFG1_tSR2AR_MASK					HwSDCFG1_tSR2AR(255)
	#define	HwSDCFG1_tSRP(X)						((X)*Hw16)						// Minimum cycles of self-refresh active period
	#define	HwSDCFG1_tSRP_MASK						HwSDCFG1_tSRP(255)
	#define	HwSDCFG1_NAP(X)						((X)*Hw8)						// Number of Auto-refresh in POR2 state
	#define	HwSDCFG1_NAP_MASK						HwSDCFG1_NAP(255)
	#define	HwSDCFG1_NAI(X)							((X)*Hw0)						// Number of Auto-refresh in INIT2 state
	#define	HwSDCFG1_NAI_MASK						HwSDCFG1_NAI(255)
                                    
/************************************************************************
*	NAND Flash Register Define					(Base Addr = N * 0x10000000)
************************************************************************/
#define	NAND_CS									0x40000000

#define	HwNDCMD								*(volatile unsigned long *)(NAND_CS + 0x00000000)	// R/W, Command Cycle

#define	HwNDLADR								*(volatile unsigned long *)(NAND_CS + 0x00000004)	// W, Linear Address Cycle

#define	HwNDRADR								*(volatile unsigned long *)(NAND_CS + 0x00000008)	// W, Row Address Cycle

#define	HwNDIADR								*(volatile unsigned long *)(NAND_CS + 0x0000000C)	// W, Single Address Cycle

#define	HwNDDATA								*(volatile unsigned long *)(NAND_CS + 0x00000010)	// R/W, Data Access Cycle

#define	NANDWaitTilNotBusy()					{ while(!((HwMCFG) & HwMCFG_RDY)); }				//

/************************************************************************
*	SRAM Interface Register Define				(Base Addr = 0xF0080000)
************************************************************************/
#define	HwSRAMIF_BASE							*(volatile unsigned long *)0xF0080000	// SRAM IF Base Register

typedef volatile struct
{
	unsigned	CTRLCS0XA0;				// Control register for SRAMIF_CS0 when SRAMIF_XA = 0 ~ 1
	unsigned	CTRLCS0XA2;				// Control register for SRAMIF_CS0 when SRAMIF_XA = 2 ~ 3
	unsigned	CTRLCS1XA0;				// Control register for SRAMIF_CS1 when SRAMIF_XA = 0 ~ 1
	unsigned	CTRLCS1XA2;				// Control register for SRAMIF_CS1 when SRAMIF_XA = 2 ~ 3
	unsigned	CS0XA[4];				// Data register for SRAMIF_CS0 with SRAMIF_XA = 0 ~ 3
	unsigned	CS1XA[4];				// Data register for SRAMIF_CS1 with SRAMIF_XA = 0 ~ 3
} sHwSRAMIF;

#define	HwCTRLCS0XA0							*(volatile unsigned long *)0xF0080000	// R/W, Control Register for SRAMIF_CS0 when SRAMIF_XA = 0 ~ 1
	#define	HwCTRLCSnXAn_BW_3						(Hw31+Hw15)						// Fixed Value for BW
	#define	HwCTRLCSnXAn_WSTP(X)					((X)*Hw28)						// Setup Time for Writing (= N cycle)
	#define	HwCTRLCSnXAn_WSTP_MASK				HwCTRLCSnXAn_WSTP(7)
	#define	HwCTRLCSnXAn_RSTP(X)					((X)*Hw12)						// Setup Time for Reading (= N cycle)
	#define	HwCTRLCSnXAn_RSTP_MASK				HwCTRLCSnXAn_RSTP(7)
	#define	HwCTRLCSnXAn_WPW(X)					((X)*Hw19)						// PulseWidth Time for Writing (= N+1 cycle)
	#define	HwCTRLCSnXAn_WPW_MASK				HwCTRLCSnXAn_WPW(511)
	#define	HwCTRLCSnXAn_RPW(X)					((X)*Hw3)						// PulseWidth Time for Reading (= N+1 cycle)
	#define	HwCTRLCSnXAn_RPW_MASK					HwCTRLCSnXAn_RPW(511)
	#define	HwCTRLCSnXAn_WHLD(X)					((X)*Hw16)						// Hold Time for Writing (= N cycle)
	#define	HwCTRLCSnXAn_WHLD_MASK				HwCTRLCSnXAn_WHLD(7)
	#define	HwCTRLCSnXAn_RHLD(X)					((X)*Hw0)						// Hold Time for Reading (= N cycle)
	#define	HwCTRLCSnXAn_RHLD_MASK				HwCTRLCSnXAn_RHLD(7)

#define	HwCTRLCS0XA2							*(volatile unsigned long *)0xF0080004	// R/W, Control Register for SRAMIF_CS0 when SRAMIF_XA = 2 ~ 3
#define	HwCTRLCS1XA0							*(volatile unsigned long *)0xF0080008	// R/W, Control Register for SRAMIF_CS1 when SRAMIF_XA = 0 ~ 1
#define	HwCTRLCS1XA2							*(volatile unsigned long *)0xF008000C	// R/W, Control Register for SRAMIF_CS1 when SRAMIF_XA = 2 ~ 3
#define	HwCS0XA0								*(volatile unsigned long *)0xF0080010	// R/W, Data Register for SRAMIF_CS0 with SRAMIF_XA = 0
#define	HwCS0XA1								*(volatile unsigned long *)0xF0080014	// R/W, Data Register for SRAMIF_CS0 with SRAMIF_XA = 1
#define	HwCS0XA2								*(volatile unsigned long *)0xF0080018	// R/W, Data Register for SRAMIF_CS0 with SRAMIF_XA = 2
#define	HwCS0XA3								*(volatile unsigned long *)0xF008001C	// R/W, Data Register for SRAMIF_CS0 with SRAMIF_XA = 3
#define	HwCS1XA0								*(volatile unsigned long *)0xF0080020	// R/W, Data Register for SRAMIF_CS1 with SRAMIF_XA = 0
#define	HwCS1XA1								*(volatile unsigned long *)0xF0080024	// R/W, Data Register for SRAMIF_CS1 with SRAMIF_XA = 1
#define	HwCS1XA2								*(volatile unsigned long *)0xF0080028	// R/W, Data Register for SRAMIF_CS1 with SRAMIF_XA = 2
#define	HwCS1XA3								*(volatile unsigned long *)0xF008002C	// R/W, Data Register for SRAMIF_CS1 with SRAMIF_XA = 3

/************************************************************************
*	Clock Controller Register Define			(Base Addr = 0xF3000000)
************************************************************************/
#define	HwCKC_BASE								*(volatile unsigned long *)0xF3000000	// Clock Controller Base Register

#define	HwCLKCTRL								*(volatile unsigned long *)0xF3000000	// R/W, CPU & Bus Clock Control Register
	#define	HwCLKCTRL_XE_EN						Hw31							// XIN Oscillator Enabled
	#define	HwCLKCTRL_XE_DIS						~Hw31							// XIN Oscillator Disabled
	#define	HwCLKCTRL_MB							Hw29							// Main processor clock selection register (Fmcpu = Fbus)
	#define	HwCLKCTRL_SB							Hw28							// Sub processor clock selection register (Fscpu = Fbus)
	#define	HwCLKCTRL_MDIV(X)						((X)*Hw16)						// Main processor clock divisor register (Fmcpu = Fbus + (Fsys-Fbus)*(MDIV+1)/16)
	#define	HwCLKCTRL_MDIV_MASK					HwCLKCTRL_MDIV(15)
	#define	HwCLKCTRL_SDIV(X)						((X)*Hw12)						// Sub processor clock divisor register (Fscpu = Fbus + (Fsys-Fbus)*(SDIV+1)/16)
	#define	HwCLKCTRL_SDIV_MASK					HwCLKCTRL_SDIV(15)
	#define	HwCLKCTRL_CKSEL_FPLL0					HwZERO							// Direct output from PLL0
	#define	HwCLKCTRL_CKSEL_FPLL1					Hw0								// Direct output form PLL1
	#define	HwCLKCTRL_CKSEL_FPLL0DIV				Hw1								// Divided output from PLL0
	#define	HwCLKCTRL_CKSEL_FPLL1DIV				(Hw1+Hw0)						// Divided output from PLL1
	#define	HwCLKCTRL_CKSEL_FXIN					Hw2								// XIN from external main oscillator(shared by UTMI clock)
	#define	HwCLKCTRL_CKSEL_FXINDIV				(Hw2+Hw0)						// Divided output from XIN
	#define	HwCLKCTRL_CKSEL_FXTIN					(Hw2+Hw1)						// XTIN from external sub oscillator(shared by RTC)
	#define	HwCLKCTRL_CKSEL_FXTINDIV				(Hw2+Hw1+Hw0)					// Divided output from XTIN
	#define	HwCLKCTRL_CKSEL_Fpll0					HwZERO
	#define	HwCLKCTRL_CKSEL_Fpll1					Hw0
	#define	HwCLKCTRL_CKSEL_Fpll0div					Hw1
	#define	HwCLKCTRL_CKSEL_Fpll1div					(Hw1+Hw0)
	#define	HwCLKCTRL_CKSEL_Fxin					HwCLKCTRL_CKSEL_FXIN
	#define	HwCLKCTRL_CKSEL_Fxindiv					(Hw2+Hw0)
	#define	HwCLKCTRL_CKSEL_Fxtin					(Hw2+Hw1)
	#define	HwCLKCTRL_CKSEL_Fxtindiv					(Hw2+Hw1+Hw0)

#define	HwMCLKCTRL								*(volatile unsigned long *)0xF30000EC	// R/W, Main CPU & Bus Clock Control Register
	#define	HwMCLKCTRL_ACC_EN						Hw31							// Register Access Enable
	#define	HwMCLKCTRL_XB							Hw8								// Same as MB of HwCLKCTRL regiseter
	#define	HwMCLKCTRL_XDIV(X)						((X)*Hw0)						// Same as MDIV of HwCLKCTRL regiseter
	#define	HwMCLKCTRL_XDIV_MASK					HwMCLKCTRL_XDIV(15)

#define	HwSCLKCTRL								*(volatile unsigned long *)0xF30000F0	// R/W, Sub CPU & Bus Clock Control Register
	#define	HwSCLKCTRL_ACC_EN						Hw31							// Register Access Enable
	#define	HwSCLKCTRL_XB							Hw8								// Same as SB of HwCLKCTRL regiseter
	#define	HwSCLKCTRL_XDIV(X)						((X)*Hw0)						// Same as SDIV of HwCLKCTRL regiseter
	#define	HwSCLKCTRL_XDIV_MASK					HwSCLKCTRL_XDIV(15)

#define	HwPLLCFG(X)								*((volatile unsigned long *)0xF3000004 + (X))
	#define	HwPLLCFG_PD_DIS						Hw31
	#define	HwPLLCFG_S(X)							((X)*Hw16)						// S = 1 ~ 4
	#define	HwPLLCFG_S_MASK						HwPLLCFG_S(7)					// Fpll = M*Fin / (P*2^S)
	#define	HwPLLCFG_M(X)							((X)*Hw8)						// 16 < M < 255
	#define	HwPLLCFG_M_MASK						HwPLLCFG_M(255)
	#define	HwPLLCFG_P(X)							((X)*Hw0)						// 1 < P < 63
	#define	HwPLLCFG_P_MASK						HwPLLCFG_P(63)

#define	HwPLL0CFG								*(volatile unsigned long *)0xF3000004	// R/W, PLL0 Configuration Register
	#define	HwPLL0CFG_PD_DIS						Hw31							// PLL Disable
	#define	HwPLL0CFG_PD_EN						~Hw31							// PLL Enable

#define	HwPLL1CFG								*(volatile unsigned long *)0xF3000008	// R/W, PLL1 Configuration Register
	#define	HwPLL1CFG_PD_DIS						Hw31							// PLL Disable
	#define	HwPLL1CFG_PD_EN						~Hw31							// PLL Enable

#define	HwCLKDIVC								*(volatile unsigned long *)0xF300000C	// R/W, Divided Clock Configuration Register
	#define	HwCLKDIVC_P0E_EN						Hw31							// PLL0 Divider Enable
	#define	HwCLKDIVC_P0E_DIS						~Hw31							// PLL0 Divider Disable
	#define	HwCLKDIVC_P0DIV(X)						((X)*Hw24)						// PLL0 Divisor factor (= N+1)
	#define	HwCLKDIVC_P0DIV_MASK					HwCLKDIVC_P0DIV(63)
	#define	HwCLKDIVC_P1E_EN						Hw23							// PLL1 Divider Enabled
	#define	HwCLKDIVC_P1E_DIS						~Hw23							// PLL1 Divider Disable
	#define	HwCLKDIVC_P1DIV(X)						((X)*Hw16)						// PLL1 Divisor factor (= N+1)
	#define	HwCLKDIVC_P1DIV_MASK					HwCLKDIVC_P1DIV(63)
	#define	HwCLKDIVC_XE_EN						Hw15							// XIN Divider Enable
	#define	HwCLKDIVC_XE_DIS						~Hw15							// XIN Divider Disable
	#define	HwCLKDIVC_XDIV(X)						((X)*Hw8)						// XIN Divisor factor (= N+1)
	#define	HwCLKDIVC_XDIV_MASK					HwCLKDIVC_XDIV(63)
	#define	HwCLKDIVC_XTE_EN						Hw7								// XTIN Divider Enable
	#define	HwCLKDIVC_XTE_DIS						~Hw7							// XTIN Divider Disable
	#define	HwCLKDIVC_XTDIV(X)						((X)*Hw0)						// XTIN Divisor factor (= N+1)
	#define	HwCLKDIVC_XTDIV_MASK					HwCLKDIVC_XTDIV(63)

#define	HwCLKDIVC1								*(volatile unsigned long *)0xF3000010	// R/W, PLL0 Divider 1 Configuration Register
	#define	HwCLKDIVC1_P1E_EN						Hw15							// PLL1 Divider 1 Enabled
	#define	HwCLKDIVC1_P1DIV(X)						((X)*Hw8)						// PLL1 Divisor 1 factor (= N+1)
	#define	HwCLKDIVC1_P1DIV_MASK					HwCLKDIVC1_P1DIV(63)
	#define	HwCLKDIVC1_P0E_EN						Hw7								// PLL0 Divider 1 Enabled
	#define	HwCLKDIVC1_P0DIV(X)						((X)*Hw0)						// PLL0 Divisor 1 factor (= N+1)
	#define	HwCLKDIVC1_P0DIV_MASK					HwCLKDIVC1_P0DIV(63)

#define	HwMODECTR								*(volatile unsigned long *)0xF3000014	// R/W, Operating Mode Control Register
	#define	HwMODECTR_PDCK_XTIN					Hw9								// XTIN Selected
	#define	HwMODECTR_PDCK_XIN					~Hw9							// XIN Selected
	#define	HwMODECTR_PD_ON						Hw8								// Enter Power Down mode
	#define	HwMODECTR_PD_OFF						~Hw8							// Stay in Normal mode
	#define	HwMODECTR_HALT_ON						Hw0								// Enter Halt mode
	#define	HwMODECTR_HALT_OFF						~Hw0							// Stay in Normal mode

#define	HwBCLKCTR64							*(volatile unsigned long long *)0xF3000018	// R/W, Bus Clock Enable Register with 64 bit addressing
	#define	HwBCLKCTR64_VIDEOENC_ON				Hw37							// Enable the Bus Clock for  Video Encoder
	#define	HwBCLKCTR64_EHI1_ON					Hw36							// Enable the Bus Clock for  External Host Interface channel 1 Controller
	#define	HwBCLKCTR64_GPSB3_ON					Hw35							// Enable the Bus Clock for  GPSB channel 3 Controller
	#define	HwBCLKCTR64_GPSB2_ON					Hw34							// Enable the Bus Clock for  GPSB channel 2 Controller
	#define	HwBCLKCTR64_SRAMIF_ON					Hw33							// Enable the Bus Clock for  SRAM I/F Controller
	#define	HwBCLKCTR64_UA3_ON					Hw32							// Enable the Bus Clock for  UART channel 3 Controller

#define	HwBCLKCTR								*(volatile unsigned long *)0xF3000018	// R/W, Bus Clock Enable Register 0 (LSW)
	#define	HwBCLKCTR_MBC_ON						Hw31							// Enable Main Bus Components (should be '1')
	#define	HwBCLKCTR_MB							Hw30							// Enable MailBox
	#define	HwBCLKCTR_M2MS						Hw29							// Enable Memory to Memory Scaler
	#define	HwBCLKCTR_VIC_ON						Hw28							// Enable Vectored Interrupt Controller
	#define	HwBCLKCTR_MAINPRO						Hw27							// Enable Main processor
	#define	HwBCLKCTR_TMR_ON						Hw26							// Enable the Bus Clock for Timer Controller
	#define	HwBCLKCTR_TMR_OFF						~Hw26							// Disable the Bus Clock for Timer Controller
	#define	HwBCLKCTR_VCH_ON						Hw25							// Enable Video Controller Hardware
	#define	HwBCLKCTR_ADC_ON						Hw24							// Enable the Bus Clock for ADC controller
	#define	HwBCLKCTR_ADC_OFF						~Hw24							// Disable the Bus Clock for ADC Controller
	#define	HwBCLKCTR_SUBPRO						Hw23							// Enable Sub processor
	#define	HwBCLKCTR_MEM_ON						Hw22							// Enable Memory Controller
	#define	HwBCLKCTR_RTC_ON						Hw21							// Enable the Bus Clock for RTC Controller
	#define	HwBCLKCTR_RTC_OFF						~Hw21							// Disable the Bus Clock for RTC Controller
	#define	HwBCLKCTR_2D							Hw20							// Enable the Graphic 2D
	#define	HwBCLKCTR_SUBPROPERI					Hw19							// Enable the Sub processor peripherals
	#define	HwBCLKCTR_GPSB1_ON					Hw18							// Enable the Bus Clock for GPSB channel 1 Controller
	#define	HwBCLKCTR_SPI_OFF						~Hw18							// Disable the Bus Clock for SPI Slave Interface Controller
	#define	HwBCLKCTR_SPDIF_ON						Hw17							// Enable SPDIF Transmitter
	#define	HwBCLKCTR_ECC_ON						Hw16							// Enable the Bus Clock for ECC Controller
	#define	HwBCLKCTR_ECC_OFF						~Hw16							// Disable the Bus Clock for ECC Controller
	#define	HwBCLKCTR_UA2_ON						Hw15							// Enable the Bus Clock for UART channel 2 Controller
	#define	HwBCLKCTR_DAI_ON						Hw14							// Enable the Bus Clock for DAI Controller
	#define	HwBCLKCTR_GPSB0_ON					Hw13							// Enable the Bus Clock for GPSB channel 0 Controller
	#define	HwBCLKCTR_SPI_ON						Hw13
	#define	HwBCLKCTR_UA1_ON						Hw12							// Enable the Bus Clock for UART1 Controller
	#define	HwBCLKCTR_UA0_ON						Hw11							// Enable the Bus Clock for UART0 Controller
	#define	HwBCLKCTR_EHI_ON						Hw10							// Enable the Bus Clock for External Host Interface Controller
	#define	HwBCLKCTR_ND_ON						Hw9								// Enable the Bus Clock for NAND Flash Controller
	#define	HwBCLKCTR_ND_OFF						~Hw9							// Disable the Bus Clock for NAND Flash Controller
	#define	HwBCLKCTR_I2C_ON						Hw8								// Enable the Bus Clock for I2C Controller
	#define	HwBCLKCTR_I2C_OFF						~Hw8							// Disable the Bus Clock for I2C Controller
	#define	HwBCLKCTR_MS_ON						Hw7								// Enable the Bus Clock for Memory Stick Controller
	#define	HwBCLKCTR_MS_OFF						~Hw7							// Disable the Bus Clock for Memory Stick Controller
	#define	HwBCLKCTR_SD_ON						Hw6								// Enable the Bus Clock for SD/MMC Controller
	#define	HwBCLKCTR_SD_OFF						~Hw6							// Disable the Bus Clock for SD/MMC Controller
	#define	HwBCLKCTR_DMA_ON						Hw5								// Enable the Bus Clock for DMA Controller
	#define	HwBCLKCTR_DMA_OFF						~Hw5							// Disable the Bus Clock for DMA Controller
	#define	HwBCLKCTR_HDD_ON						Hw4								// Enable HDD Controller
	#define	HwBCLKCTR_CIC_ON						Hw3								// Enable Camera Interface Controller
	#define	HwBCLKCTR_LCD_ON						Hw2								// Enable LCD Controller
	#define	HwBCLKCTR_UB_ON						Hw1								// Enable the Bus Clock for USB2.0 Device Controller
	#define	HwBCLKCTR_UB_OFF						~Hw1							// Disable the Bus Clock for USB2.0 Device Controller
	#define	HwBCLKCTR_UBH_ON						Hw0								// Enable the Bus Clock for USB1.1 Host Controller
	#define	HwBCLKCTR_UBH_OFF						~Hw0							// Disable the Bus Clock for USB1.1 Host Controller
#define	HwBCLKCTR1								*(volatile unsigned long *)0xF300001C	// R/W, Bus Clock Enable Register 1 (MSW)
	#define	HwBCLKCTR1_VIDEOENC_ON				Hw5								// Enable the Bus Clock for Video Encoder
	#define	HwBCLKCTR1_EHI1_ON						Hw4								// Enable the Bus Clock for External Host Interface channel 1 Controller
	#define	HwBCLKCTR1_GPSB3_ON					Hw3								// Enable the Bus Clock for GPSB channel 3 Controller
	#define	HwBCLKCTR1_GPSB2_ON					Hw2								// Enable the Bus Clock for GPSB channel 2 Controller
	#define	HwBCLKCTR1_SRAMIF_ON					Hw1								// Enable the Bus Clock for SRAM I/F Controller
	#define	HwBCLKCTR1_UA3_ON						Hw0								// Enable the Bus Clock for UART channel 3 Controller

#define	HwSWRESET64							*(volatile unsigned long long *)0xF3000020	// R/W, S/W Reset Register
	#define	HwSWRESET64_VIDEOENC_ON				Hw37							// Reset Video Encoder
	#define	HwSWRESET64_EHI1_ON					Hw36							// Reset External Host Interface channel 1 Controller
	#define	HwSWRESET64_GPSB3_ON					Hw35							// Reset GPSB channel 3 Controller
	#define	HwSWRESET64_GPSB2_ON					Hw34							// Reset GPSB channel 2 Controller
	#define	HwSWRESET64_SRAMIF_ON					Hw33							// Reset SRAM I/F Controller
	#define	HwSWRESET64_UA3_ON					Hw32							// Reset UART channel 3 Controller

#define	HwSWRESET								*(volatile unsigned long *)0xF3000020	// R/W, S/W Reset Register
	#define	HwSWRESET_MBC_ON						Hw31							// Reset Main Bus Components (should be '1')
	#define	HwSWRESET_MB							Hw30							// Reset MailBox
	#define	HwSWRESET_M2MS						Hw29							// Reset Memory to Memory Scaler
	#define	HwSWRESET_VIC_ON						Hw28							// Reset Vectored Interrupt Controller
	#define	HwSWRESET_MAINPRO						Hw27							// Reset Main processor
	#define	HwSWRESET_TMR_ON						Hw26							// Reset Timer Controller
	#define	HwSWRESET_VCH_ON						Hw25							// Reset Video Controller Hardware
	#define	HwSWRESET_ADC_ON						Hw24							// Reset ADC controller
	#define	HwSWRESET_SUBPRO						Hw23							// Reset Sub processor
	#define	HwSWRESET_MEM_ON						Hw22							// Reset Memory Controller
	#define	HwSWRESET_RTC_ON						Hw21							// Reset RTC Controller
	#define	HwSWRESET_2D							Hw20							// Reset the Graphic 2D
	#define	HwSWRESET_SUBPROPERI					Hw19							// Reset the Sub processor peripherals
	#define	HwSWRESET_SPI_ON						Hw18							// Reset SPI Slave Interface Controller
	#define	HwSWRESET_GPSB1_ON					Hw18							// Reset GPSB channel 1 Controller
	#define	HwSWRESET_SPDIF_ON						Hw17							// Reset SPDIF Transmitter
	#define	HwSWRESET_ECC_ON						Hw16							// Reset ECC Controller
	#define	HwSWRESET_UA2_ON						Hw15							// Reset UART channel 2 Controller
	#define	HwSWRESET_DAI_ON						Hw14							// Reset DAI Controller
	#define	HwSWRESET_GPSB0_ON					Hw13							// Reset GPSB channel 0 Controller
	#define	HwSWRESET_UA1_ON						Hw12							// Reset UART1 Controller
	#define	HwSWRESET_UA0_ON						Hw11							// Reset UART0 Controller
	#define	HwSWRESET_EHI_ON						Hw10							// Reset External Host Interface Controller
	#define	HwSWRESET_ND_ON						Hw9								// Reset NAND Flash Controller
	#define	HwSWRESET_I2C_ON						Hw8								// Reset I2C Controller
	#define	HwSWRESET_MS_ON						Hw7								// Reset Memory Stick Controller
	#define	HwSWRESET_SD_ON						Hw6								// Reset SD/MMC Controller
	#define	HwSWRESET_DMA_ON						Hw5								// Reset DMA Controller
	#define	HwSWRESET_HDD_ON						Hw4								// Reset HDD Controller
	#define	HwSWRESET_CIC_ON						Hw3								// Reset Camera Interface Controller
	#define	HwSWRESET_LCD_ON						Hw2								// Reset LCD Controller
	#define	HwSWRESET_UB_ON						Hw1								// Reset USB2.0 Device Controller
	#define	HwSWRESET_UBH_ON						Hw0								// Reset USB1.1 Host Controller

#define	HwSWRESET1								*(volatile unsigned long *)0xF3000024	// R/W, S/W Reset Register 1
	#define	HwSWRESET1_VIDEOENC_ON				Hw5								// Reset Video Encoder
	#define	HwSWRESET1_EHI1_ON						Hw4								// Reset External Host Interface channel 1 Controller
	#define	HwSWRESET1_GPSB3_ON					Hw3								// Reset GPSB channel 3 Controller
	#define	HwSWRESET1_GPSB2_ON					Hw2								// Reset GPSB channel 2 Controller
	#define	HwSWRESET1_SRAMIF_ON					Hw1								// Reset SRAM I/F Controller
	#define	HwSWRESET1_UA3_ON						Hw0								// Reset UART channel 3 Controller

	#define	HwPCK_EN_EN							Hw28							// Clock Divider Enable
	#define	HwPCK_SEL(X)							((X)*Hw24)
	#define	HwPCK_SEL_PLL0							HwPCK_SEL(0)					// PLL0 Direct Output
	#define	HwPCK_SEL_PLL1							HwPCK_SEL(1)					// PLL1 Direct Output
	#define	HwPCK_SEL_PLL0DIV						HwPCK_SEL(2)					// PLL0 Divider Output
	#define	HwPCK_SEL_PLL1DIV						HwPCK_SEL(3)					// PLL1 Divider Output
	#define	HwPCK_SEL_XIN							HwPCK_SEL(4)					// XIN Output
	#define	HwPCK_SEL_XINDIV						HwPCK_SEL(5)					// XIN Divider Output
	#define	HwPCK_SEL_XTIN							HwPCK_SEL(6)					// XTIN Output
	#define	HwPCK_SEL_XTINDIV						HwPCK_SEL(7)					// XTIN Divider Output
	#define	HwPCK_SEL_PLL0DIV1						HwPCK_SEL(8)					// PLL0 Divider 1 Output
	#define	HwPCK_SEL_PLL1DIV1						HwPCK_SEL(9)					// PLL1 Divider 1 Output
	#define	HwPCK_SEL_EXTCLK						HwPCK_SEL(10)					// External Clock
	#define	HwPCK_SEL_TMR1							HwPCK_SEL(11)					// Timer counter output 1
	#define	HwPCK_SEL_TMR2							HwPCK_SEL(12)					// Timer counter output 2
	#define	HwPCK_SEL_TMR3							HwPCK_SEL(13)					// Timer counter output 3
	#define	HwPCK_SEL_TMR4							HwPCK_SEL(14)					// Timer counter output 4
	#define	HwPCK_SEL_U48MHZ						HwPCK_SEL(15)					// 48MHz Clock from nanoPHY (USB PHY)
	#define	HwPCK_SEL_MASK							HwPCK_SEL(15)

#define	HwPCK_USB11H						*(volatile unsigned long *)0xF3000080	// R/W, USB11H Clock Control Register
#define	HwPCK_SDMMC							*(volatile unsigned long *)0xF3000084	// R/W, SD/MMC Clock Control Register
#define	HwPCK_MSTICK						*(volatile unsigned long *)0xF3000088	// R/W, Memory Stick Clock Control Register
#define	HwPCK_I2C							*(volatile unsigned long *)0xF300008C	// R/W, I2C Clock Control Register
#define	HwPCK_LCD							*(volatile unsigned long *)0xF3000090	// R/W, LCD Clock Control Register
#define	HwPCK_CAM							*(volatile unsigned long *)0xF3000094	// R/W, Camera Clock Control Register
#define	HwPCK_UART0							*(volatile unsigned long *)0xF3000098	// R/W, UART0 Clock Control Register
#define	HwPCK_UART1							*(volatile unsigned long *)0xF300009C	// R/W, UART1 Clock Control Register
#define	HwPCK_UART2							*(volatile unsigned long *)0xF30000A0	// R/W, UART2 Clock Control Register
#define	HwPCK_UART3							*(volatile unsigned long *)0xF30000A4	// R/W, UART3 Clock Control Register
#define	HwPCK_TCT							*(volatile unsigned long *)0xF30000A8	// R/W, Timer T Clock Control Register
#define	HwPCK_TCX							*(volatile unsigned long *)0xF30000AC	// R/W, Timer X Clock Control Register
#define	HwPCK_TCZ							*(volatile unsigned long *)0xF30000B0	// R/W, Timer Z Clock Control Register
#define	HwPCK_DAI							*(volatile unsigned long *)0xF30000B4	// R/W, DAI Clock Control Register
#define	HwPCK_GPSB0							*(volatile unsigned long *)0xF30000B8	// R/W, GPSB0 Clock Control Register
#define	HwPCK_GPSB1							*(volatile unsigned long *)0xF30000BC	// R/W, GPSB1 Clock Control Register
#define	HwPCK_GPSB2							*(volatile unsigned long *)0xF30000C0	// R/W, GPSB2 Clock Control Register
#define	HwPCK_GPSB3							*(volatile unsigned long *)0xF30000C4	// R/W, GPSB3 Clock Control Register
#define	HwPCK_ADC							*(volatile unsigned long *)0xF30000C8	// R/W, ADC Clock Control Register
#define	HwPCK_SPDIF							*(volatile unsigned long *)0xF30000CC	// R/W, SPDIF TX Clock Control Register
#define	HwPCK_RFREQ							*(volatile unsigned long *)0xF30000D0	// R/W, SDRAM Refresh Clock Control Register
#define	HwPCK_SCALER						*(volatile unsigned long *)0xF30000D4	// R/W, CIF Scaler Clock Control Register
#define	HwPCK_EHI0							*(volatile unsigned long *)0xF30000D8	// R/W, External Host Interface 0 Control Register
#define	HwPCK_EHI1							*(volatile unsigned long *)0xF30000DC	// R/W, External Host Interface 1 Control Register
#define	HwBCKVCFG							*(volatile unsigned long *)0xF30000E0	// R/W, Bus Clock Mask Register for Video Hardware
#define	HwBCLKMASKE64						*(volatile unsigned long long *)0xF30000F4
#define	HwBCLKMASKE							*(volatile unsigned long *)0xF30000F4
#define	HwBCLKMASKE1						*(volatile unsigned long *)0xF30000F8
#define	HwOPTION0							*(volatile unsigned long *)0xF30000FC

/************************************************************************
*	Vectored Interrupt controller Define		(Base Addr = 0xF3001000)
************************************************************************/
typedef volatile struct
{
	unsigned	IEN;																	// R/W, Enable Interrupt
	unsigned	ICLR;																// W, Clear Interrupt
	unsigned	ISTS;																// R, Interrupt Status
	unsigned	ISEL;																// R/W, IRQ/FIQ selection
	unsigned	SRC;																// R, Source Interrupt Status
	unsigned	MSTS;																// R, Masked Interrupt Status
	unsigned	TREQ;																// R/W, Test interrupt request
	unsigned	IPOL;																// R/W, Polarity of interrupt signal (0 = active high, 1 = active low)
	unsigned	IRQ;																	// R, IRQ interrupt status
	unsigned	FIQ;																	// R, FIQ interrupt status
	unsigned	MIRQ;																// R, Masked IRQ interrupt status
	unsigned	MFIQ;																// R, Masked FIQ interrupt status
	unsigned	MODE;																// R/W, Trigger mode selection (0 = edge, 1 = level)
	unsigned	SYNC;																// R/W, Enable Synchronizing
	unsigned	WKEN;																// R/W, Select Wakeup signal
	unsigned	MODEA;																// R/W, Edge trigger mode selection (0 = single edge, 1 = both edge)
	unsigned	IRQMSK;																// R/W, IRQ Output Masking Register
	unsigned	ALLMSK;																// R/W, All Mask Register
} sHwINT;

#define	HwSUBVIC_BASE							*(volatile unsigned long *)0xFF011000
#define	HwVIC_BASE								*(volatile unsigned long *)0xF3001000

#define	HwIEN									*(volatile unsigned long *)0xF3001000	// R/W, Interrupt Enable Register
	#define	HwINT_SEL4								Hw31							//
	#define	HwINT_ADC								Hw30							//
	#define	HwINT_LCD								Hw29							//
	#define	HwINT_CAM								Hw28							//
	#define	HwINT_SD								Hw27							//
	#define	HwINT_NFC								Hw26							//
	#define	HwINT_SEL3								Hw25							//
	#define	HwINT_HDD								Hw24							//
	#define	HwINT_DMA								Hw23							//
	#define	HwINT_UH								Hw22							//
	#define	HwINT_UD								Hw21							//
	#define	HwINT_G2D								Hw20							//
	#define	HwINT_SEL2								Hw19							//
	#define	HwINT_UT								Hw18							//
	#define	HwINT_HPI								Hw17							//
	#define	HwINT_CDRX								Hw16							//
	#define	HwINT_DAITX								Hw15							//
	#define	HwINT_DAIRX								Hw14							//
	#define	HwINT_I2C								Hw13							//
	#define	HwINT_SC								Hw12							//
	#define	HwINT_SEL1								Hw11							//
	#define	HwINT_SEL0								Hw10							//
	#define	HwINT_SPDTX								Hw9								//
	#define	HwINT_SCORE							Hw8								//
	#define	HwINT_TC1								Hw7								//
	#define	HwINT_TC0								Hw6								//
	#define	HwINT_GPSB								Hw5								//
	#define	HwINT_RTC								Hw4								//
	#define	HwINT_EI3								Hw3								//
	#define	HwINT_EI2								Hw2								//
	#define	HwINT_EI1								Hw1								//
	#define	HwINT_EI0								Hw0								//

#define	HwCLR									*(volatile unsigned long *)0xF3001004	// R/W, Interrupt Clear Register

#define	HwSTS									*(volatile unsigned long *)0xF3001008	// R, Interrupt Status Register

#define	HwSEL									*(volatile unsigned long *)0xF300100C	// R/W, IRQ or FIR Selection Register

#define	HwSRC									*(volatile unsigned long *)0xF3001010	// R/W, Real or Test Interrupt Selection Register

#define	HwMSTS									*(volatile unsigned long *)0xF3001014	// R/W, Masked Status Register

#define	HwTIG									*(volatile unsigned long *)0xF3001018	// R/W, Test Interrupt Generation Register

#define	HwPOL									*(volatile unsigned long *)0xF300101C	// R/W, Interrupt Polarity Register

#define	HwIRQ									*(volatile unsigned long *)0xF3001020	// R, IRQ Raw Status Register

#define	HwFIQ									*(volatile unsigned long *)0xF3001024	// R, FIQ Status Register

#define	HwMIRQ									*(volatile unsigned long *)0xF3001028	// R, Masked IRQ Status Register

#define	HwMFIQ									*(volatile unsigned long *)0xF300102C	// R, Masked FIQ Status Register

#define	HwMODE									*(volatile unsigned long *)0xF3001030	// R/W, Trigger Mode Register (Level or Edge)

#define	HwSYNC									*(volatile unsigned long *)0xF3001034	// R/W, Synchronization Enable Register

#define	HwWKEN									*(volatile unsigned long *)0xF3001038	// R/W, Wakeup Event Enable Register

#define	HwMODEA								*(volatile unsigned long *)0xF300103C	// R/W, Both Edge or Single Edge Register

#define	HwIRQMSK								*(volatile unsigned long *)0xF3001040	// R/W, IRQ Output Mask Register
#define	HwINTMSK								*(volatile unsigned long *)0xF3001040	// R/W, IRQ Output Mask Register

#define	HwALLMSK								*(volatile unsigned long *)0xF3001044	// R/W, All IRQ Mask Register
	#define	HwALLMSK_FIQ							Hw1								// FIQ mask register
	#define	HwALLMSK_IRQ							Hw0								// IRQ mask register

#define	HwVAIRQ									*(volatile unsigned long *)0xF3001080	// R, IRQ Vector Register
	#define	HwVAIRQ_INV								Hw31							// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source

#define	HwVAFIQ									*(volatile unsigned long *)0xF3001084	// R, FIQ Vector Register
	#define	HwVAFIQ_INV								Hw31							// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source

#define	HwVNIRQ									*(volatile unsigned long *)0xF3001088	// R, IRQ Vector Number Register
	#define	HwVNIRQ_INV								Hw31							// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source

#define	HwVNFIQ									*(volatile unsigned long *)0xF300108C	// R, FIQ Vcoter Number Register
	#define	HwVNFIQ_INV								Hw31							// 1:Invalid for Current Interrupt Source, 0:Valid for Current Interrupt Source

#define	HwVCTRL									*(volatile unsigned long *)0xF3001090	// R/W, Vector Control Register
	#define	HwVCTRL_RCL_RD							Hw31							// The reading the VN or VA register clears the interrupt status
	#define	HwVCTRL_FPOL_10							Hw30							// INV field polarity selection (valid for '1', invalid for '0')
	#define	HwVCTRL_FPOL_01							HwZERO							// INV field polarity selection (valid for '0', invalid for '1')
	#define	HwVCTRL_FFLG_VLD						Hw29							// Valid flag enable for FIQ vector registers
	#define	HwVCTRL_FFLG_INVLD						HwZERO							// InValid flag enable for FIQ vector registers
	#define	HwVCTRL_IFLG_VLD						Hw28							// Valid flag enable for IRQ vector registers
	#define	HwVCTRL_IFLG_INVLD						HwZERO							// InValid flag enable for IRQ vector registers
	#define	HwVCTRL_FHD_EN							Hw27							// Enable the holding vector for FIQ until cleared
	#define	HwVCTRL_IHD_EN							Hw26							// Enable the holding vector for IRQ until cleared

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
#define	HwRTC_BASE								*(volatile unsigned long *)0xF3002000	// RTC Base Register

#define	HwRTCCON								*(volatile unsigned long *)0xF3002000	// R/W, RTC Control Register
	#define	HwRTCCON_HALT							Hw0								//
	#define	HwRTCCON_RTCEN						Hw1								// RTC Register write enabled
	#define	HwRTCCON_CLKSEL_NORM					HwZERO							// Counting clock is 1Hz.
	#define	HwRTCCON_CLKSEL_FAST					Hw2								// Counting clock is 32.768kHz
	#define	HwRTCCON_CNTSEL_NORM					HwZERO							// BCD counter acts normally
	#define	HwRTCCON_CNTSEL_SEP					Hw3								// BCD counter acts separately.
	#define	HwRTCCON_CLKRST_ON					Hw4								// BCD counter is reseted.
	#define	HwRTCCON_OSCEN_TEN					Hw5								// Oscillator & Divider circuit test enabled.
	#define	HwRTCCON_AIOUTEN_EN					Hw6								// Alarm Interrupt Output Enable
	#define	HwRTCCON_WUOUTEN_EN					Hw7								// Wakeup Output Enable

#define	HwINTCON								*(volatile unsigned long *)0xF3002004	// R/W, RTC Interrupt Control Register
	#define	HwINTCON_INTWREN						Hw0								// Interrupt Block Write Enable
	#define	HwINTCON_STATUS						Hw1								// User-Defined Status Register

#define	HwRTCALM								*(volatile unsigned long *)0xF3002008	// R/W, RTC Alarm Control Register
	#define	HwRTCALM_SECEN_EN						Hw0								// Second Alarm interrupt enabled
	#define	HwRTCALM_MINEN_EN						Hw1								// Minute Alarm interrupt enabled
	#define	HwRTCALM_HOUREN_EN					Hw2								// Hour Alarm interrupt enabled
	#define	HwRTCALM_DATEEN_EN						Hw3								// Date Alarm interrupt enabled
	#define	HwRTCALM_DAYEN_EN						Hw4								// Day of Week Alarm interrupt enabled
	#define	HwRTCALM_ALMEN_EN						Hw5								// Alarm interrupt enabled (global enable)
	#define	HwRTCALM_ALLEN							0x3F							//

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
	#define	HwRTCIM_ALMINT_EDGE_EN					Hw0								//
	#define	HwRTCIM_ALMINT_LEVEL_EN				(Hw1+Hw0)						//
	#define	HwRTCIM_ALMINT_DIS						HwZERO							//
	#define	HwRTCIM_WKUPMODE_HIGH					Hw2								// PMWKUP active High
	#define	HwRTCIM_WKUPMODE_LOW					HwZERO							// PMWKUP active Low

#define	HwRTCPEND								*(volatile unsigned long *)0xF3002048	// R/W, RTC Interrupt Pending Register
	#define	HwRTCPEND_PENDING						Hw0								//

#define	HwRTCSTR								*(volatile unsigned long *)0xF300204C	// R/W, RTC Interrupt Status Register

/***********************************************************************
*	Timer/Counter Register Define				(Base Addr = 0xF3003000)
************************************************************************/
#define	HwTMR_BASE								*(volatile unsigned long *)0xF3003000	// Timer/Counter Base Register

typedef	volatile struct
{               	
	unsigned	TCFG;                   	
		#define	HwTCFG_CC_ZERO					Hw8								// TCNT is cleared to zero
		#define	HwTCFG_POL_F						Hw7								// TCNT is incremented at falling edge of the selected counting clock
		#define	HwTCFG_TCK_DIV2					(0 * Hw4)						// Counter clock is come from TCLK divided by 2.
		#define	HwTCFG_TCK_DIV4					(1 * Hw4)						// Counter clock is come from TCLK divided by 4.
		#define	HwTCFG_TCK_DIV8					(2 * Hw4)						// Counter clock is come from TCLK divided by 8.
		#define	HwTCFG_TCK_DIV16					(3 * Hw4)						// Counter clock is come from TCLK divided by 16.
		#define	HwTCFG_TCK_DIV32					(4 * Hw4)						// Counter clock is come from TCLK divided by 32.
		#define	HwTCFG_TCK_DIV1K					(5 * Hw4)						// Counter clock is come from TCLK divided by 1024.
		#define	HwTCFG_TCK_DIV4K					(6 * Hw4)						// Counter clock is come from TCLK divided by 4096.
		#define	HwTCFG_TCK_EXTCLK					(7 * Hw4)						// Counter clock is come from external clock.
		#define	HwTCFG_IEN_EN						Hw3								// Enable Timer/Counter interrupt
		#define	HwTCFG_PWM_EN						Hw2								// Enable PWM mode
		#define	HwTCFG_CON_ON						Hw1								// The TCNT3 continues counting without return to zero.
		#define	HwTCFG_EN_ON						Hw0								// Timer counter is enabled
	unsigned	TCNT;                   	
	unsigned	TREF;                   	
	unsigned	TMREF;                  	
} sHwTMR;

#define	HwTCFG0									*(volatile unsigned long *)0xF3003000	// R/W, Timer Configuration Register
	#define	HwTCFG0_STOP							Hw9								// If TCNT0 is equal to the TREF0, the TCNT0 counter stop to increment
	#define	HwTCFG0_CC_ZERO						Hw8								// TCNT0 is cleared to zero
	#define	HwTCFG0_CC_NOT							~Hw8							// TCNT0 is not cleared
	#define	HwTCFG0_POL_F							Hw7								// TCNT0 is incremented at falling edge of the selected counting clock
	#define	HwTCFG0_POL_R							~Hw7							// TCNT0 is incremented at rising edge of the selected counting clock
	#define	HwTCFG0_IEN_EN							Hw3								// Enable Timer/Counter interrupt
	#define	HwTCFG0_IEN_DIS							~Hw3							// Disable Timer/Counter interrupt
	#define	HwTCFG0_PWM_EN							Hw2								// Enable PWM mode
	#define	HwTCFG0_PWM_DIS						~Hw2							// Disable PWM mode
	#define	HwTCFG0_CON_ON						Hw1								// The TCNT0 continues counting from the TREF0
	#define	HwTCFG0_CON_OFF						~Hw1							// When the TCNT0 is reached to TREF0, TCNT0 restarts counting from 0 at the next pulse of selected clock source
	#define	HwTCFG0_EN_ON							Hw0								// Timer counter is enabled
	#define	HwTCFG0_EN_OFF							~Hw0							// Timer counter is disabled

#define	HwTCNT0									*(volatile unsigned long *)0xF3003004	// R/W, Timer Counter Register

#define	HwTREF0  								*(volatile unsigned long *)0xF3003008	// R/W, Timer Reference Register

#define	HwTMREF0 								*(volatile unsigned long *)0xF300300C	// R/W, Timer Middle reference Register

#define	HwTCFG1									*(volatile unsigned long *)0xF3003010	// R/W, Timer Configuration Register
	#define	HwTCFG1_STOP							Hw9								// If TCNT1 is equal to the TREF1, the TCNT1 counter stop to increment
	#define	HwTCFG1_CC_ZERO						Hw8								// TCNT1 is cleared to zero
	#define	HwTCFG1_CC_NOT							~Hw8							// TCNT1 is not cleared
	#define	HwTCFG1_POL_F							Hw7								// TCNT1 is incremented at falling edge of the selected counting clock
	#define	HwTCFG1_POL_R							~Hw7							// TCNT1 is incremented at rising edge of the selected counting clock
	#define	HwTCFG1_IEN_EN							Hw3								// Enable Timer/Counter interrupt
	#define	HwTCFG1_IEN_DIS							~Hw3							// Disable Timer/Counter interrupt
	#define	HwTCFG1_PWM_EN							Hw2								// Enable PWM mode
	#define	HwTCFG1_PWM_DIS						~Hw2							// Disable PWM mode
	#define	HwTCFG1_CON_ON						Hw1								// The TCNT1 continues counting from the TREF1
	#define	HwTCFG1_CON_OFF						~Hw1							// When the TCNT1 is reached to TREF1, TCNT1 restarts counting from 0 at the next pulse of selected clock source
	#define	HwTCFG1_EN_ON							Hw0								// Timer counter is enabled
	#define	HwTCFG1_EN_OFF							~Hw0							// Timer counter is disabled

#define	HwTCNT1									*(volatile unsigned long *)0xF3003014	// R/W, Timer Counter Register

#define	HwTREF1									*(volatile unsigned long *)0xF3003018	// R/W, Timer Reference Register

#define	HwTMREF1								*(volatile unsigned long *)0xF300301C	// R/W, Timer Middle reference Register

#define	HwTCFG2									*(volatile unsigned long *)0xF3003020	// R/W, Timer Configuration Register
	#define	HwTCFG2_STOP							Hw9								// If TCNT2 is equal to the TREF2, the TCNT2 counter stop to increment
	#define	HwTCFG2_CC_ZERO						Hw8								// TCNT2 is cleared to zero
	#define	HwTCFG2_CC_NOT							~Hw8							// TCNT2 is not cleared
	#define	HwTCFG2_POL_F							Hw7								// TCNT2 is incremented at falling edge of the selected counting clock
	#define	HwTCFG2_POL_R							~Hw7							// TCNT2 is incremented at rising edge of the selected counting clock
	#define	HwTCFG2_IEN_EN							Hw3								// Enable Timer/Counter interrupt
	#define	HwTCFG2_IEN_DIS							~Hw3							// Disable Timer/Counter interrupt
	#define	HwTCFG2_PWM_EN							Hw2								// Enable PWM mode
	#define	HwTCFG2_PWM_DIS						~Hw2							// Disable PWM mode
	#define	HwTCFG2_CON_ON						Hw1								// The TCNT2 continues counting from the TREF2
	#define	HwTCFG2_CON_OFF						~Hw1							// When the TCNT2 is reached to TREF2, TCNT2 restarts counting from 0 at the next pulse of selected clock source
	#define	HwTCFG2_EN_ON							Hw0								// Timer counter is enabled
	#define	HwTCFG2_EN_OFF							~Hw0							// Timer counter is disabled

#define	HwTCNT2									*(volatile unsigned long *)0xF3003024	// R/W, Timer Counter Register

#define	HwTREF2									*(volatile unsigned long *)0xF3003028	// R/W, Timer Reference Register

#define	HwTMREF2								*(volatile unsigned long *)0xF300302C	// R/W, Timer Middle reference Register

#define	HwTCFG3									*(volatile unsigned long *)0xF3003030	// R/W, Timer Configuration Register
	#define	HwTCFG3_STOP							Hw9								// If TCNT3 is equal to the TREF3, the TCNT3 counter stop to increment
	#define	HwTCFG3_CC_ZERO						Hw8								// TCNT3 is cleared to zero
	#define	HwTCFG3_CC_NOT							~Hw8							// TCNT3 is not cleared
	#define	HwTCFG3_POL_F							Hw7								// TCNT3 is incremented at falling edge of the selected counting clock
	#define	HwTCFG3_POL_R							~Hw7							// TCNT3 is incremented at rising edge of the selected counting clock
	#define	HwTCFG3_IEN_EN							Hw3								// Enable Timer/Counter interrupt
	#define	HwTCFG3_IEN_DIS							~Hw3							// Disable Timer/Counter interrupt
	#define	HwTCFG3_PWM_EN							Hw2								// Enable PWM mode
	#define	HwTCFG3_PWM_DIS						~Hw2							// Disable PWM mode
	#define	HwTCFG3_CON_ON						Hw1								// The TCNT3 continues counting from the TREF3
	#define	HwTCFG3_CON_OFF						~Hw1							// When the TCNT3 is reached to TREF3, TCNT3 restarts counting from 0 at the next pulse of selected clock source
	#define	HwTCFG3_EN_ON							Hw0								// Timer counter is enabled
	#define	HwTCFG3_EN_OFF							~Hw0							// Timer counter is disabled

#define	HwTCNT3									*(volatile unsigned long *)0xF3003034	// R/W, Timer Counter Register

#define	HwTREF3									*(volatile unsigned long *)0xF3003038	// R/W, Timer Reference Register

#define	HwTMREF3								*(volatile unsigned long *)0xF300303C 	// R/W, Timer Middle reference Register

#define	HwTCFG4									*(volatile unsigned long *)0xF3003040	// R/W, Timer Configuration Register
	#define	HwTCFG4_STOP							Hw9								// If TCNT4 is equal to the TREF4, the TCNT4 counter stop to increment
	#define	HwTCFG4_CC_ZERO						Hw8								// TCNT4 is cleared to zero
	#define	HwTCFG4_CC_NOT							~Hw8							// TCNT4 is not cleared
	#define	HwTCFG4_POL_F							Hw7								// TCNT4 is incremented at falling edge of the selected counting clock
	#define	HwTCFG4_POL_R							~Hw7							// TCNT4 is incremented at rising edge of the selected counting clock
	#define	HwTCFG4_IEN_EN							Hw3								// Enable Timer/Counter interrupt
	#define	HwTCFG4_IEN_DIS							~Hw3							// Disable Timer/Counter interrupt
	#define	HwTCFG4_PWM_EN							Hw2								// Enable PWM mode
	#define	HwTCFG4_PWM_DIS						~Hw2							// Disable PWM mode
	#define	HwTCFG4_CON_ON						Hw1								// The TCNT4 continues counting from the TREF4
	#define	HwTCFG4_CON_OFF						~Hw1							// When the TCNT4 is reached to TREF4, TCNT4 restarts counting from 0 at the next pulse of selected clock source
	#define	HwTCFG4_EN_ON							Hw0								// Timer counter is enabled
	#define	HwTCFG4_EN_OFF							~Hw0							// Timer counter is disabled

#define	HwTCNT4									*(volatile unsigned long *)0xF3003044	// R/W, Timer Counter Register

#define	HwTREF4									*(volatile unsigned long *)0xF3003048	// R/W, Timer Reference Register

#define	HwTCFG5									*(volatile unsigned long *)0xF3003050	// R/W, Timer Configuration Register
	#define	HwTCFG5_STOP							Hw9								// If TCNT5 is equal to the TREF5, the TCNT5 counter stop to increment
	#define	HwTCFG5_CC_ZERO						Hw8								// TCNT5 is cleared to zero
	#define	HwTCFG5_CC_NOT							~Hw8							// TCNT5 is not cleared
	#define	HwTCFG5_POL_F							Hw7								// TCNT5 is incremented at falling edge of the selected counting clock
	#define	HwTCFG5_POL_R							~Hw7							// TCNT5 is incremented at rising edge of the selected counting clock
	#define	HwTCFG5_IEN_EN							Hw3								// Enable Timer/Counter interrupt
	#define	HwTCFG5_IEN_DIS							~Hw3							// Disable Timer/Counter interrupt
	#define	HwTCFG5_PWM_EN							Hw2								// Enable PWM mode
	#define	HwTCFG5_PWM_DIS						~Hw2							// Disable PWM mode
	#define	HwTCFG5_CON_ON						Hw1								// The TCNT5 continues counting from the TREF5
	#define	HwTCFG5_CON_OFF						~Hw1							// When the TCNT5 is reached to TREF5, TCNT5 restarts counting from 0 at the next pulse of selected clock source
	#define	HwTCFG5_EN_ON							Hw0								// Timer counter is enabled
	#define	HwTCFG5_EN_OFF							~Hw0							// Timer counter is disabled

#define	HwTCNT5									*(volatile unsigned long *)0xF3003054	// R/W, Timer Counter Register

#define	HwTREF5									*(volatile unsigned long *)0xF3003058	// R/W, Timer Reference Register

#define	HwTIREQ									*(volatile unsigned long *)0xF3003060	// R/W, Timer Interrupt Request Register
	#define	HwTIREQ_TWF							Hw14							// Watchdog Timer Flag
	#define	HwTIREQ_TF5								Hw13							// Timer5 Flag
	#define	HwTIREQ_TF4								Hw12							// Timer4 Flag
	#define	HwTIREQ_TF3								Hw11							// Timer3 Flag
	#define	HwTIREQ_TF2								Hw10							// Timer2 Flag
	#define	HwTIREQ_TF1								Hw9								// Timer1 Flag
	#define	HwTIREQ_TF0								Hw8								// Timer0 Flag
	#define	HwTIREQ_TWI								Hw6								// Watchdog Timer Interrupt Request Flag
	#define	HwTIREQ_TI5								Hw5								// Timer5 Interrupt Request Flag
	#define	HwTIREQ_TI4								Hw4								// Timer4 Interrupt Request Flag
	#define	HwTIREQ_TI3								Hw3								// Timer3 Interrupt Request Flag
	#define	HwTIREQ_TI2								Hw2								// Timer2 Interrupt Request Flag
	#define	HwTIREQ_TI1								Hw1								// Timer1 Interrupt Request Flag
	#define	HwTIREQ_TI0								Hw0								// Timer0 Interrupt Request Flag

#define	HwTWDCFG								*(volatile unsigned long *)0xF3003070	// R/W, Watchdog Timer Configuration Register
	#define	HwTWDCFG_TCK_DIV32					(4 * Hw4)						// Counter clock is come from TCLK divided by 32.
	#define	HwTWDCFG_TCK_DIV1K					(5 * Hw4)						// Counter clock is come from TCLK divided by 1024.
	#define	HwTWDCFG_TCK_DIV4K					(6 * Hw4)						// Counter clock is come from TCLK divided by 4096.
	#define	HwTWDCFG_IEN_ON						Hw3								// Watchdog timer interrupt is enabled
	#define	HwTWDCFG_IEN_OFF						~Hw3							// Watchdog timer interrupt is disabled
	#define	HwTWDCFG_ISEL_NOGEN					Hw1								// Watchdog timer does not generate reset signal although it reaches to the reference value, and it continue counting from 0.
	#define	HwTWDCFG_ISEL_GEN						~Hw1							// Watchdog timer generates the reset signal when it reaches to the reference value, the reset signal is applied to every component in the chip.
	#define	HwTWDCFG_EN_ON						Hw0								// Watchdog timer is enabled
	#define	HwTWDCFG_EN_OFF						~Hw0							// Watchdog timer is disabled

#define	HwTWDCLR								*(volatile unsigned long *)0xF3003074	// W, Watchdog Timer Clear Register

#define	HwTC32EN								*(volatile unsigned long *)0xF3003080	// R/W, 32bit Counter enable / Pre-scale value
	#define	HwTC32EN_LDM1_ON						Hw29							// Reload counter when the counter value matched with CMP1
	#define	HwTC32EN_LDM0_ON						Hw28							// Reload counter when the counter value matched with CMP0
	#define	HwTC32EN_STPMOD_ON					Hw26							// Stop Mode (Counting stops when the counter value matched)
	#define	HwTC32EN_LDZERO_ON					Hw25							// counter starts form 0 to LOADVAL(HwTC32LDV) - 1
	#define	HwTC32EN_LDZERO_OFF					HwZERO							// counter starts form LOADVAL(HwTC32LDV) to (CMP0 or CMP1 or 0xFFFFFFFF)
	#define	HwTC32EN_ENABLE_ON						Hw24							// Counter enable
	#define	HwTC32EN_PRESCALE(X)					((X)*Hw0)						// Pre-scale counter load value. (count from 0 to PRESCALE)
	#define	HwTC32EN_PRESCALE_MASK				HwTC32EN_PRESCALE(32767)

#define	HwTC32LDV								*(volatile unsigned long *)0xF3003084	// R/W, 32bit Counter load value Register (LOADVAL)

#define	HwTC32CMP0								*(volatile unsigned long *)0xF3003088	// R/W, 32bit Counter match value 0 Register

#define	HwTC32CMP1								*(volatile unsigned long *)0xF300308C	// R/W, 32bit Counter match value 1 Register

#define	HwTC32PCNT								*(volatile unsigned long *)0xF3003090	// R, 32bit Counter current value (pre-scale counter) Register

#define	HwTC32MCNT								*(volatile unsigned long *)0xF3003094	// R, 32bit Counter current value (main counter) Register

#define	HwTC32IRQ								*(volatile unsigned long *)0xF3003098	// R/W, 32bit Counter interrupt control Register
	#define	HwTC32IRQ_IRQCLR_WRITE					Hw31							// Interrupt clear control (IRQSTAT is only cleared by writing non-zero value)
	#define	HwTC32IRQ_IRQCLR_READ					~Hw31							// Interrupt clear control
	#define	HwTC32IRQ_RSYNC_DIS					Hw30							// Disable Synchronization control
	#define	HwTC32IRQ_RSYNC_EN						~Hw30							// Enable Synchronization control
	#define	HwTC32IRQ_IRQEN4_EN					Hw20							// Enable interrupt at the rising edge of a counter bit selected by BITSEL
	#define	HwTC32IRQ_IRQEN4_DIS					~Hw20							// Enable interrupt at the rising edge of a counter bit selected by BITSEL
	#define	HwTC32IRQ_IRQEN3_EN					Hw19							// Enable interrupt at the end of prescale count
	#define	HwTC32IRQ_IRQEN3_DIS					~Hw19							// Enable interrupt at the end of prescale count
	#define	HwTC32IRQ_IRQEN2_EN					Hw18							// Enable interrupt at the end of count
	#define	HwTC32IRQ_IRQEN2_DIS					~Hw18							// Enable interrupt at the end of count
	#define	HwTC32IRQ_IRQEN1_EN					Hw17							// Enable interrupt when the counter value matched with CMP1
	#define	HwTC32IRQ_IRQEN1_DIS					~Hw17							// Enable interrupt when the counter value matched with CMP1
	#define	HwTC32IRQ_IRQEN0_EN					Hw16							// Enable interrupt when the counter value matched with CMP0
	#define	HwTC32IRQ_IRQEN0_DIS					~Hw16							// Enable interrupt when the counter value matched with CMP0
	#define	HwTC32IRQ_IRQRSTAT4_ON					Hw12							// Raw status of IRQEN4 interrupt
	#define	HwTC32IRQ_IRQRSTAT3_ON					Hw11							// Raw status of IRQEN3 interrupt
	#define	HwTC32IRQ_IRQRSTAT2_ON					Hw10							// Raw status of IRQEN2 interrupt
	#define	HwTC32IRQ_IRQRSTAT1_ON					Hw9								// Raw status of IRQEN1 interrupt
	#define	HwTC32IRQ_IRQRSTAT0_ON					Hw8								// Raw status of IRQEN0 interrupt
	#define	HwTC32IRQ_IRQMSTAT4_ON				Hw4								// Masked status of IRQEN4 interrupt (= IRQEN4 & IRQRSTAT4)
	#define	HwTC32IRQ_IRQMSTAT3_ON				Hw3								// Masked status of IRQEN3 interrupt (= IRQEN3 & IRQRSTAT3)
	#define	HwTC32IRQ_IRQMSTAT2_ON				Hw2								// Masked status of IRQEN2 interrupt (= IRQEN2 & IRQRSTAT2)
	#define	HwTC32IRQ_IRQMSTAT1_ON				Hw1								// Masked status of IRQEN1 interrupt (= IRQEN1 & IRQRSTAT1)
	#define	HwTC32IRQ_IRQMSTAT0_ON				Hw0								// Masked status of IRQEN0 interrupt (= IRQEN0 & IRQRSTAT0)

#define	HwTMR_CH_BASE(X)						*(volatile unsigned long*)(0xF3003000 +(X)*0x10)
#define	HwTMR_MAX_CH								6

/************************************************************************
*	ADC Controller Register Define				(Base Addr = 0xF3004000)
************************************************************************/
#define	HwADC_BASE								*(volatile unsigned long *)0xF3004000	// ADC Base Register

#define	HwADCCON								*(volatile unsigned long *)0xF3004000	// R/W, ADC Control
	#define	HwADCCON_STB_ON						Hw4								// ADC goes Standby mode
	#define	HwADCCON_STB_OFF						~Hw4							// ADC Start operating
	#define	HwADCCON_ASEL(X)						((X)*Hw0)
	#define	HwADCCON_ASEL_CH0						HwADCCON_ASEL(0)
	#define	HwADCCON_ASEL_CH1						HwADCCON_ASEL(1)
	#define	HwADCCON_ASEL_CH2						HwADCCON_ASEL(2)
	#define	HwADCCON_ASEL_CH3						HwADCCON_ASEL(3)
	#define	HwADCCON_ASEL_CH4						HwADCCON_ASEL(4)
	#define	HwADCCON_ASEL_CH5						HwADCCON_ASEL(5)
	#define	HwADCCON_ASEL_CH6						HwADCCON_ASEL(6)
	#define	HwADCCON_ASEL_CH7						HwADCCON_ASEL(7)
	#define	HwADCCON_ASEL_MASK					HwADCCON_ASEL(7)

#define	HwADDATA								*(volatile unsigned long *)0xF3004004	// R, ADC Data
	#define	HwADDATA_FLG							Hw0										//

#define	HwADCCONA								*(volatile unsigned long *)0xF3004080	// R/W, ADC Control Register A
	#define	HwADCCONA_STB_ON						Hw4								// ADC goes Standby mode
	#define	HwADCCONA_STB_OFF						~Hw4							// ADC Start operating
	#define	HwADCCONA_ASEL(X)						((X)*Hw0)
	#define	HwADCCONA_ASEL_CH0					HwADCCONA_ASEL(0)
	#define	HwADCCONA_ASEL_CH1					HwADCCONA_ASEL(1)
	#define	HwADCCONA_ASEL_CH2					HwADCCONA_ASEL(2)
	#define	HwADCCONA_ASEL_CH3					HwADCCONA_ASEL(3)
	#define	HwADCCONA_ASEL_CH4					HwADCCONA_ASEL(4)
	#define	HwADCCONA_ASEL_CH5					HwADCCONA_ASEL(5)
	#define	HwADCCONA_ASEL_CH6					HwADCCONA_ASEL(6)
	#define	HwADCCONA_ASEL_CH7					HwADCCONA_ASEL(7)
	#define	HwADCCONA_ASEL_MASK					HwADCCONA_ASEL(7)

#define	HwADCSTATUS							*(volatile unsigned long *)0xF3004084	// R, ADC Status Register
	#define	HwADCSTATUS_WBVCNT(X)					((X)*Hw28)						// command buffer valid entry count. (up to 4 entries can be posted at a time)
	#define	HwADCSTATUS_WBVCNT_MASK				HwADCSTATUS_WBVCNT(7)
	#define	HwADCSTATUS_RBVCNT(X)					((X)*Hw24)						// data buffer valid entry count. (up to 4 entries can be stored)
	#define	HwADCSTATUS_RBVCNT_MASK				HwADCSTATUS_RBVCNT(7)
	#define	HwADCSTATUS_RSELV(X)					((X)*Hw16)						// ADC channel number for current data. (up to 4 entries can be stored)
	#define	HwADCSTATUS_RSELV_MASK				HwADCSTATUS_RSELV(7)
	#define	HwADCSTATUS_RBDATA(X)					((X)*Hw0)
	#define	HwADCSTATUS_RBDATA_MASK				HwADCSTATUS_RBDATA(511)

#define	HwADCCFG								*(volatile unsigned long *)0xF3004088	// R/W, Configuration Register
	#define	HwADCCFG_CLKDIV(X)						((X)*Hw12)						// Clock divisor value. ADCLK is divided by (CLKDIV+1)*2
	#define	HwADCCFG_CLKDIV_MASK					HwADCCFG_CLKDIV(15)
	#define	HwADCCFG_DLYSTC(X)						((X)*Hw8)						// Delay from SEL to STC (Start conversion) (unit of core clock)
	#define	HwADCCFG_IRQE_ON						Hw3								// Interrupt enable
	#define	HwADCCFG_IRQE_OFF						~Hw3							// Interrupt disable
	#define	HwADCCFG_R8_8BIT						Hw2								// ADC output is shifted right 2 bit. (LSB 2bits are truncated)
	#define	HwADCCFG_R8_10BIT						~Hw2							//
	#define	HwADCCFG_APD_ON						Hw1								// Auto Power Down enabled (valid only if SM == 1)
	#define	HwADCCFG_APD_OFF						~Hw1							//
	#define	HwADCCFG_SM_EN						Hw0								// Single Mode enabled
	#define	HwADCCFG_SM_DIS						~Hw0							//

/***********************************************************************
*	System Controller Register Define			(Base Addr = 0xF3005000)
************************************************************************/
#define	HwSYSCFG_BASE							*(volatile unsigned long *)0xF3005000	// System Config Base Register

#define	HwREMAP								*(volatile unsigned long *)0xF3005000	// R/W, Remap Configuration Register
	#define	HwREMAP_JTAG_MAIN						HwZERO							// The JTAG is connected to only main processor
	#define	HwREMAP_JTAG_SUB						Hw25							// The JTAG is connected to only sub processor
	#define	HwREMAP_JTAG_BOTH						(Hw25+Hw24)						// The JTAG is connected to both main processor and sub processor. In this case, the JTAG is connected to sub processor through main processor with chained structure
	#define	HwREMAP_CFGBM							(Hw20-Hw16)						//
	#define	HwREMAP_CFGBW							(Hw9+Hw8)						//
	#define	HwREMAP_REMAP10						HwZERO							// Remap 0x1... to 0x0...
	#define	HwREMAP_REMAP20						Hw0								// Remap 0x2... to 0x0...
	#define	HwREMAP_REMAP30						Hw1								// Remap 0x3... to 0x0...
	#define	HwREMAP_REMAP70						(Hw1+Hw0)						// Remap 0x7... to 0x0...
	#define	HwREMAP_NOTREMAP						Hw2								// Do not remap
	#define	HwREMAP_REMAPE0						(Hw2+Hw1+Hw0)					// Remap 0xE... to 0x0...

#define	HwVCFG0								*(volatile unsigned long *)0xF3005004	// R/W, Video Core Configuration Register 0 (Base address of Sub-core boot area)

#define	HwECFG0									*(volatile unsigned long *)0xF300500C	// R/W, Exceptional Configuration Register 0
	#define	HwECFG0_RTCWAIT(X)						((X)*Hw8)
	#define	HwECFG0_RTCWAIT_MASK					HwECFG0_RTCWAIT(7)
	#define	HwECFG0_LCK1							Hw3								// LCD Clock Output Enable to GPA14
	#define	HwECFG0_LCK0							Hw2								// LCD Clock Output Enable to HDDRQ
	#define	HwECFG0_ME1							Hw1								// Bus Clock Dynamic Mask Enable for I/O Bus to Main Bus
	#define	HwECFG0_ME0							Hw0								// Bus Clock Dynamic Mask Enable for Main Bus to I/O Bus

#define	HwMPCFG								*(volatile unsigned long *)0xF3005010	// R/W, Main Processor Configuration Register
	#define	HwMPCFG_INI								Hw31							// ITCM boot enable register

#define	HwMBCFG								*(volatile unsigned long *)0xF3005020	// R/W, Main Bus Configuration Register
	#define	HwMBCFG_RR_IOBUS						Hw12							// Round Robin arbitration is enabled for I/O bus, all the peripherals
	#define	HwMBCFG_RR_VSRAM						Hw11							// Round Robin arbitration is enabled for Video SRAM
	#define	HwMBCFG_RR_SDRAM1						Hw10							// Round Robin arbitration is enabled for SDRAM Channel 1 (0x3...)
	#define	HwMBCFG_RR_ESMEM						Hw9								// Round Robin arbitration is enabled for External Static Memory, SDRAM Channel 0 (0x2...)
	#define	HwMBCFG_RR_GPMEM						Hw8								// Round Robin arbitration is enabled for General purpose SRAM, Shared SRAM, DTCM, Boot-ROM
	#define	HwMBCFG_INCRB_IOBUS					Hw4								// Incremental burst locked transfer is enabled for I/O bus, all the peripherals
	#define	HwMBCFG_INCRB_VSRAM					Hw3								// Incremental burst locked transfer is enabled for Video SRAM
	#define	HwMBCFG_INCRB_SDRAM1					Hw2								// Incremental burst locked transfer is enabled for SDRAM Channel 1 (0x3...)
	#define	HwMBCFG_INCRB_ESMEM					Hw1								// Incremental burst locked transfer is enabled for External Static Memory, SDRAM Channel 0 (0x2...)
	#define	HwMBCFG_INCRB_GPMEM					Hw0								// Incremental burst locked transfer is enabled for General purpose SRAM, Shared SRAM, DTCM, Boot-ROM


#define HwPSR1		*(volatile unsigned long *)0xF3005100
#define HwPSR2		*(volatile unsigned long *)0xF3005108
#define HwPSR3		*(volatile unsigned long *)0xF300510C

#define HwPSR4		*(volatile unsigned long *)0xF3005300
#define HwPSR5		*(volatile unsigned long *)0xF3005304
#define HwPSR6		*(volatile unsigned long *)0xF3005308
#define HwPSR7		*(volatile unsigned long *)0xF300530C
#define HwPSR8		*(volatile unsigned long *)0xF3005310
#define HwPSR9		*(volatile unsigned long *)0xF3005314
#define HwPSR10		*(volatile unsigned long *)0xF3005318

#define HwPSR11		*(volatile unsigned long *)0xF3005400
#define HwPSR12		*(volatile unsigned long *)0xF3005404
#define HwPSR13		*(volatile unsigned long *)0xF3005408
#define HwPSR14		*(volatile unsigned long *)0xF300540C
#define HwPSR15		*(volatile unsigned long *)0xF3005410
#define HwPSR16		*(volatile unsigned long *)0xF3005414
#define HwPSR17		*(volatile unsigned long *)0xF3005418
#define HwPSR18		*(volatile unsigned long *)0xF300541C
#define HwPSR19		*(volatile unsigned long *)0xF3005420
#define HwPSR20		*(volatile unsigned long *)0xF3005424


/************************************************************************
*	Protect Register Define						(Base Addr = 0xF3006000)
************************************************************************/
#define	HwCLZ_BASE								*(volatile unsigned long *)0xF3006000	// CLZ Base Register

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

#define	HwMBOXCTR								*(volatile unsigned long *)0xF4000040	// R/W, MAILBOX Control
	#define	HwMBOXCTR_TEST							Hw31							// For Test Purpose
	#define	HwMBOXCTR_FLUSH						Hw6								// Flush the transmit data fifo
	#define	HwMBOXCTR_OEN							Hw5								// Transmit data output enable
	#define	HwMBOXCTR_IEN							Hw4								// Received data interrupt enable

#define	HwMBOXSTR								*(volatile unsigned long *)0xF4000044	// R/W, MAILBOX Status
	#define	HwMBOXSTR_SFUL							Hw17							// Full Status of Recevie FIFO
	#define	HwMBOXSTR_SEMP						Hw16							// Empty Status of Receive FIFO
	#define	HwMBOXSTR_MFUL							Hw1								// Full Status of Transmit FIFO
	#define	HwMBOXSTR_MEMP						Hw0								// Empty Status of Transmit FIFO

#define	HwSUBMBOX_BASE						*(volatile unsigned long *)0xFF050000
#define	HwSUBMBOXTXD							*(volatile unsigned long *)0xFF050000	// W, Transmit FIFO Data Region
#define	HwSUBMBOXRXD							*(volatile unsigned long *)0xFF050020	// R, Transmit FIFO Data Region
#define	HwSUBMBOXCTR							*(volatile unsigned long *)0xFF050040	// R/W, MAILBOX Control
#define	HwSUBMBOXSTR							*(volatile unsigned long *)0xFF050044	// R/W, MAILBOX Status
#define	HwSUBHALT								*(volatile unsigned long *)0xFF010000	// SubCore Enter Halt mode. Wake-up and continue to run after receiving Message.

/***********************************************************************
*	External Host Interface Register Define		(Base Addr = 0xF5000000/0xF00A0000)
************************************************************************/
#define	HwEHI_BASE							*(volatile unsigned long *)0xF00A0000		// Base address of EHI for HPCSN
#define	HwEHI_CH1_BASE						*(volatile unsigned long *)0xF00A0000		// Base address of EHI for HPCSN
#define	HwEHI_CH0_BASE						*(volatile unsigned long *)0xF5000000		// Base address of EHI for HPCSN_L

typedef volatile struct
{
	unsigned	EHST;
	unsigned	EHIINT;
	unsigned	EHEINT;
	unsigned	EHA;
	unsigned	EHAM;
	unsigned	EHD;
	unsigned	EHSEM;
	unsigned	EHCFG;
	unsigned	EHIND;
	unsigned	EHRWCS;
} sHwEHI;

#define	HwEHST									*(volatile unsigned long *)0xF5000000	// R/W, Status register
	#define	HwEHST_RFNE								Hw12							// Read FIFO Not Empty
	#define	HwEHST_WFNE							Hw11							// Write FIFO Not Empty
	#define	HwEHST_WFF								Hw10							// Write FIFO Full
	#define	HwEHST_FUR								Hw9								// Read FIFO Under-Run. (cleared by TCC writing 1 to this bit)
	#define	HwEHST_FOR								Hw8								// Write FIFO Over-Run. (cleared by TCC writing 1 to this bit)
	#define	HwEHST_RDY								Hw7								// if EHCFG.RDYE == 1, HPINT = EHST.RDY ^ EHCFG.RDYP
	#define	HwEHST_ST(X)							((X)*Hw0)
	#define	HwEHST_ST_MASK							HwEHST_ST(127)

#define	HwEHIINT								*(volatile unsigned long *)0xF5000004	// R/W,  Internal interrupt control register
	#define	HwEHIINT_ST(X)							((X)*Hw1)
	#define	HwEHIINT_ST_MASK						HwEHIINT_ST(127)
	#define	HwEHIINT_IIRQ							Hw0								// Internal interrupt request flag

#define	HwEHEINT								*(volatile unsigned long *)0xF5000008	// R/W,  External interrupt control register
	#define	HwEHEINT_ST(X)							((X)*Hw1)
	#define	HwEHEINT_ST_MASK						HwEHEINT_ST(127)
	#define	HwEHEINT_EIRQ							Hw0								// External interrupt request flag. if EHCFG.RDYE == 0, HPINT = EHEINT.EIRQ

#define	HwEHA									*(volatile unsigned long *)0xF500000C	// R/W,  Address register (auto-incremented if EHRWCS.AI==1 && (EHRWCS.RD=1 or EHRWCS.WR=1))

#define	HwEHAM									*(volatile unsigned long *)0xF5000010	// R,  Address masking register (address generated = EHA[31:2] & ~EHAM[31:2])

#define	HwEHD									*(volatile unsigned long *)0xF5000014	// R/W,  Data register (if EHRWCS.RW=1 or 2, external host can access data through this register)

#define	HwEHSEM								*(volatile unsigned long *)0xF5000018	// R/W,  Semaphore register
	#define	HwEHSEM_FLG_NOT						HwZERO							// ST is not occupied by any master
	#define	HwEHSEM_FLG_RWEHDROCPU				Hw0								// ST is read/write by external host, read-only by TCC
	#define	HwEHSEM_FLG_RWCPUROEHD				Hw1								// ST is read/write by TCC, read-only by external host
	#define	HwEHSEM_FLG_NA							(Hw1+Hw0)						// N/A
	#define	HwEHSEM_ST(X)							((X)*Hw2)
	#define	HwEHSEM_ST_MASK						HwEHSEM_ST(63)

#define	HwEHCFG								*(volatile unsigned long *)0xF500001C	// R/W,  Configuration register
	#define	HwEHCFG_WIRQ							Hw7								// Enable Writing Interrupt (when HPCSN,HPWRN is asserted, interrupt is generated)
	#define	HwEHCFG_CSIRQ							Hw6								// Enable Access Interrupt (when HPCSN is asserted, interrupt is generated)
	#define	HwEHCFG_RDYP							Hw4								// if RDYE == 1, HPINT = RDYP ^ EHST.RDY
	#define	HwEHCFG_RDYE_RDY						Hw3								// HPINT is used as RDY signal.
	#define	HwEHCFG_RDYE_IRQ						HwZERO							// HPINT is used as Interrupt signal.
	#define	HwEHCFG_BW_16							Hw2								//
	#define	HwEHCFG_BW_8							HwZERO							//
	#define	HwEHCFG_MD_68							Hw0								//
	#define	HwEHCFG_MD_80							HwZERO							//

#define	HwEHIND									*(volatile unsigned long *)0xF5000020	// W,  Index register (selects internal register for EHI controller, only offset address should be used)

#define	HwEHRWCS								*(volatile unsigned long *)0xF5000024	// R/W,  Read/Write Control/Status register
	#define	HwEHRWCS_AI							Hw7								// Address Auto Increment
	#define	HwEHRWCS_LOCK_ON						Hw6								// Locked transfer mode enable
	#define	HwEHRWCS_LOCK_OFF						~Hw6							// Locked transfer mode disable
	#define	HwEHRWCS_RW_EHI						~(Hw5+Hw4)						// R/W EHI register
	#define	HwEHRWCS_RW_WAHB						Hw4								// Writing through AHB
	#define	HwEHRWCS_RW_RAHB						Hw5								// Reading through AHB
	#define	HwEHRWCS_RW_NA						(Hw5+Hw4)						// N/A

/***********************************************************************
*	2D DMA Controller Register Define			(Base Addr = 0xF6000000)
************************************************************************/
#define	HwGE_FCH0_BASE							*(volatile unsigned long *)0xF6000000	// R/W,  Front-End Channel 0 Base Register
#define	HwGE_FCH1_BASE							*(volatile unsigned long *)0xF6000020	// R/W,  Front-End Channel 1 Base Register
#define	HwGE_FCH_BASE(X)						*(volatile unsigned long *)(0xF6000000+(X)*0x20)	// R/W,  Front-End Channel Base Register
typedef volatile struct
{
	unsigned	SADDR0;			// Front-End Channel Source Address 0 (Y or Frame Base)
	unsigned	SADDR1;			// Front-End Channel Source Address 1 (U Base)
	unsigned	SADDR2;			// Front-End Channel Source Address 2 (V Base)
	unsigned	SFSIZE;			// Front-End Channel Source Frame Pixel Size
		#define	HwGE_FCH_SFSIZE_X(X)				((X)*Hw0)
		#define	HwGE_FCH_SFSIZE_X_MASK				HwGE_FCH_SFSIZE_X(4095)
		#define	HwGE_FCH_SFSIZE_Y(X)				((X)*Hw16)
		#define	HwGE_FCH_SFSIZE_Y_MASK				HwGE_FCH_SFSIZE_Y(4095)
	unsigned	SOFF;			// Front-End Channel Source Pixel Offset
		#define	HwGE_FCH_SOFF_X(X)					((X)*Hw0)
		#define	HwGE_FCH_SOFF_X_MASK				HwGE_FCH_SOFF_X(4095)
		#define	HwGE_FCH_SOFF_Y(X)					((X)*Hw16)
		#define	HwGE_FCH_SOFF_Y_MASK				HwGE_FCH_SOFF_Y(4095)
	unsigned	SISIZE;			// Front-End Channel Source Image Pixel Size
		#define	HwGE_FCH_SISIZE_X(X)				((X)*Hw0)
		#define	HwGE_FCH_SISIZE_X_MASK				HwGE_FCH_SISIZE_X(4095)
		#define	HwGE_FCH_SISIZE_Y(X)				((X)*Hw16)
		#define	HwGE_FCH_SISIZE_Y_MASK				HwGE_FCH_SISIZE_Y(4095)
	unsigned	WOFF;			// Front-End Channel Window Pixel Offset
		#define	HwGE_FCH_WOFF_X(X)					((X)*Hw0)
		#define	HwGE_FCH_WOFF_X_MASK				HwGE_FCH_WOFF_X(4095)
		#define	HwGE_FCH_WOFF_Y(X)					((X)*Hw16)
		#define	HwGE_FCH_WOFF_Y_MASK				HwGE_FCH_WOFF_Y(4095)
	unsigned	SCTRL;			// Front-End Channel Control
		#define	HwGE_FCH_SCTRL_OPMODE(X)			((X)*Hw8)						// Operation Mode
		#define	HwGE_FCH_SCTRL_OPMODE_COPY		HwGE_FCH_SCTRL_OPMODE(0)		// Data Copy
		#define	HwGE_FCH_SCTRL_OPMODE_HMIRROR	HwGE_FCH_SCTRL_OPMODE(2)		// Horizontal Mirror
		#define	HwGE_FCH_SCTRL_OPMODE_VMIRROR	HwGE_FCH_SCTRL_OPMODE(3)		// Vertical Mirror
		#define	HwGE_FCH_SCTRL_OPMODE_VHMIRROR	HwGE_FCH_SCTRL_OPMODE(4)		// Vertical & Horizontal Mirror
		#define	HwGE_FCH_SCTRL_OPMODE_ROT90		HwGE_FCH_SCTRL_OPMODE(5)		// 90 Degree Rotate
		#define	HwGE_FCH_SCTRL_OPMODE_ROT180		HwGE_FCH_SCTRL_OPMODE(6)		// 180 Degree Rotate
		#define	HwGE_FCH_SCTRL_OPMODE_ROT270		HwGE_FCH_SCTRL_OPMODE(7)		// 270 Degree Rotate
		#define	HwGE_FCH_SCTRL_OPMODE_MASK		HwGE_FCH_SCTRL_OPMODE(7)
		#define	HwGE_FCH_SCTRL_ZF_MSBFILL			Hw5								// MSB Fill Mode Enable (used when non RGB888/AlphaRGB888 mode)
		#define	HwGE_FCH_SCTRL_ZF_ZEROFILL			HwZERO							// Zero Fill Mode Enable (used when non RGB888/AlphaRGB888 mode)
		#define	HwGE_FCH_SCTRL_SDFRM(X)			((X)*Hw0)						// Source Data Format
		#define	HwGE_FCH_SCTRL_SDFRM_YUV444		HwGE_FCH_SCTRL_SDFRM(0)		// Seperate YUV 4:4:4
		#define	HwGE_FCH_SCTRL_SDFRM_YUV440		HwGE_FCH_SCTRL_SDFRM(1)		// Seperate YUV 4:4:0
		#define	HwGE_FCH_SCTRL_SDFRM_YUV422		HwGE_FCH_SCTRL_SDFRM(2)		// Seperate YUV 4:2:2
		#define	HwGE_FCH_SCTRL_SDFRM_YUV420		HwGE_FCH_SCTRL_SDFRM(3)		// Seperate YUV 4:2:0
		#define	HwGE_FCH_SCTRL_SDFRM_YUV411		HwGE_FCH_SCTRL_SDFRM(4)		// Seperate YUV 4:1:1
		#define	HwGE_FCH_SCTRL_SDFRM_YUV410		HwGE_FCH_SCTRL_SDFRM(5)		// Seperate YUV 4:1:0
		#define	HwGE_FCH_SCTRL_SDFRM_SEQ444		HwGE_FCH_SCTRL_SDFRM(6)		// Sequential YUV 4:4:4
		#define	HwGE_FCH_SCTRL_SDFRM_SEQ422		HwGE_FCH_SCTRL_SDFRM(7)		// Sequential YUV 4:2:0
		#define	HwGE_FCH_SCTRL_SDFRM_RGB444		HwGE_FCH_SCTRL_SDFRM(8)		// RGB444
		#define	HwGE_FCH_SCTRL_SDFRM_ARGB444		HwGE_FCH_SCTRL_SDFRM(9)		// Alpha-RGB444
		#define	HwGE_FCH_SCTRL_SDFRM_RGB454		HwGE_FCH_SCTRL_SDFRM(10)		// RGB454
		#define	HwGE_FCH_SCTRL_SDFRM_ARGB454		HwGE_FCH_SCTRL_SDFRM(11)		// Alpha-RGB454
		#define	HwGE_FCH_SCTRL_SDFRM_RGB555		HwGE_FCH_SCTRL_SDFRM(12)		// RGB555
		#define	HwGE_FCH_SCTRL_SDFRM_ARGB555		HwGE_FCH_SCTRL_SDFRM(13)		// Alpha-RGB555
		#define	HwGE_FCH_SCTRL_SDFRM_RGB565		HwGE_FCH_SCTRL_SDFRM(14)		// RGB565
		#define	HwGE_FCH_SCTRL_SDFRM_RGB666		HwGE_FCH_SCTRL_SDFRM(16)		// RGB666
		#define	HwGE_FCH_SCTRL_SDFRM_ARGB666		HwGE_FCH_SCTRL_SDFRM(17)		// Alpha-RGB666
		#define	HwGE_FCH_SCTRL_SDFRM_RGB888		HwGE_FCH_SCTRL_SDFRM(18)		// RGB888
		#define	HwGE_FCH_SCTRL_SDFRM_ARGB888		HwGE_FCH_SCTRL_SDFRM(19)		// Alpha-RGB888
		#define	HwGE_FCH_SCTRL_SDFRM_MASK			HwGE_FCH_SCTRL_SDFRM(31)
} sHwGE_FCH;

typedef volatile struct
{
	unsigned	DADDR0;			// Back-End Channel Destination Address 0 (Y or Frame Base Address)
	unsigned	DADDR1;			// Back-End Channel Destination Address 1 (U Base Address)
	unsigned	DADDR2;			// Back-End Channel Destination Address 2 (V Base Address)
	unsigned	DFSIZE;			// Back-End Channel Destination Frame Pixel Size
		#define	HwGE_BCH_DFSIZE_X(X)				((X)*Hw0)
		#define	HwGE_BCH_DFSIZE_X_MASK			HwGE_BCH_DFSIZE_X(4095)
		#define	HwGE_BCH_DFSIZE_Y(X)				((X)*Hw16)
		#define	HwGE_BCH_DFSIZE_Y_MASK			HwGE_BCH_DFSIZE_Y(4095)
	unsigned	DOFF;			// Back-End Channel Destination Pixel Offset
		#define	HwGE_BCH_DOFF_X(X)					((X)*Hw0)
		#define	HwGE_BCH_DOFF_X_MASK				HwGE_BCH_DOFF_X(4095)
		#define	HwGE_BCH_DOFF_Y(X)					((X)*Hw16)
		#define	HwGE_BCH_DOFF_Y_MASK				HwGE_BCH_DOFF_Y(4095)
	unsigned	DCTRL;			// Back-End Channel Control
		#define	HwGE_BCH_DCTRL_R2YEN_EN			Hw15							// RGB to YUV Converter Enable
		#define	HwGE_BCH_DCTRL_R2YMODE(X)			((X)*Hw13)						// RGB to YUV Converter Type
		#define	HwGE_BCH_DCTRL_R2YMODE_TYPE0		HwGE_BCH_DCTRL_R2YMODE(0)	// Y=0.299R+0.587G+0.114B, U=-0.172R-0.339G+0.511B+128, V=0.511R-0.428G-0.083B+128
		#define	HwGE_BCH_DCTRL_R2YMODE_TYPE1		HwGE_BCH_DCTRL_R2YMODE(1)	// Y=0.257R+0.504G+0.098B+16, U=-0.148R-0.291G+0.439B+128, V=0.439R-0.368G-0.071B+128
		#define	HwGE_BCH_DCTRL_R2YMODE_TYPE2		HwGE_BCH_DCTRL_R2YMODE(2)	// Y=0.213R+0.715G+0.072B, U=-0.117R-0.394G+0.511B+128, V=0.511R-0.464G-0.047B+128
		#define	HwGE_BCH_DCTRL_R2YMODE_TYPE3		HwGE_BCH_DCTRL_R2YMODE(3)	// Y=0.183R+0.614G+0.062B+16, U=-0.101R-0.338G+0.439B+128, V=0.439R-0.399G-0.040B+128
		#define	HwGE_BCH_DCTRL_R2YMODE_MASK		HwGE_BCH_DCTRL_R2YMODE(3)
		#define	HwGE_BCH_DCTRL_OPMODE(X)			((X)*Hw8)						// Operation Mode
		#define	HwGE_BCH_DCTRL_OPMODE_COPY		HwGE_BCH_DCTRL_OPMODE(0)		// Data Copy
		#define	HwGE_BCH_DCTRL_OPMODE_HMIRROR	HwGE_BCH_DCTRL_OPMODE(2)		// Horizontal Mirror
		#define	HwGE_BCH_DCTRL_OPMODE_VMIRROR	HwGE_BCH_DCTRL_OPMODE(3)		// Vertical Mirror
		#define	HwGE_BCH_DCTRL_OPMODE_VHMIRROR	HwGE_BCH_DCTRL_OPMODE(4)		// Vertical & Horizontal Mirror
		#define	HwGE_BCH_DCTRL_OPMODE_ROT90		HwGE_BCH_DCTRL_OPMODE(5)		// 90 Degree Rotate
		#define	HwGE_BCH_DCTRL_OPMODE_ROT180		HwGE_BCH_DCTRL_OPMODE(6)		// 180 Degree Rotate
		#define	HwGE_BCH_DCTRL_OPMODE_ROT270		HwGE_BCH_DCTRL_OPMODE(7)		// 270 Degree Rotate
		#define	HwGE_BCH_DCTRL_OPMODE_MASK		HwGE_BCH_DCTRL_OPMODE(7)
		#define	HwGE_BCH_DCTRL_DDFRM(X)			((X)*Hw0)						// Source Data Format
		#define	HwGE_BCH_DCTRL_DDFRM_YUV444		HwGE_BCH_DCTRL_DDFRM(0)		// Seperate YUV 4:4:4
		#define	HwGE_BCH_DCTRL_DDFRM_YUV440		HwGE_BCH_DCTRL_DDFRM(1)		// Seperate YUV 4:4:0
		#define	HwGE_BCH_DCTRL_DDFRM_YUV422		HwGE_BCH_DCTRL_DDFRM(2)		// Seperate YUV 4:2:2
		#define	HwGE_BCH_DCTRL_DDFRM_YUV420		HwGE_BCH_DCTRL_DDFRM(3)		// Seperate YUV 4:2:0
		#define	HwGE_BCH_DCTRL_DDFRM_YUV411		HwGE_BCH_DCTRL_DDFRM(4)		// Seperate YUV 4:1:1
		#define	HwGE_BCH_DCTRL_DDFRM_YUV410		HwGE_BCH_DCTRL_DDFRM(5)		// Seperate YUV 4:1:0
		#define	HwGE_BCH_DCTRL_DDFRM_SEQ444		HwGE_BCH_DCTRL_DDFRM(6)		// Sequential YUV 4:4:4
		#define	HwGE_BCH_DCTRL_DDFRM_SEQ422		HwGE_BCH_DCTRL_DDFRM(7)		// Sequential YUV 4:2:0
		#define	HwGE_BCH_DCTRL_DDFRM_RGB444		HwGE_BCH_DCTRL_DDFRM(8)		// RGB444
		#define	HwGE_BCH_DCTRL_DDFRM_ARGB444		HwGE_BCH_DCTRL_DDFRM(9)		// Alpha-RGB444
		#define	HwGE_BCH_DCTRL_DDFRM_RGB454		HwGE_BCH_DCTRL_DDFRM(10)		// RGB454
		#define	HwGE_BCH_DCTRL_DDFRM_ARGB454		HwGE_BCH_DCTRL_DDFRM(11)		// Alpha-RGB454
		#define	HwGE_BCH_DCTRL_DDFRM_RGB555		HwGE_BCH_DCTRL_DDFRM(12)		// RGB555
		#define	HwGE_BCH_DCTRL_DDFRM_ARGB555		HwGE_BCH_DCTRL_DDFRM(13)		// Alpha-RGB555
		#define	HwGE_BCH_DCTRL_DDFRM_RGB565		HwGE_BCH_DCTRL_DDFRM(14)		// RGB565
		#define	HwGE_BCH_DCTRL_DDFRM_RGB666		HwGE_BCH_DCTRL_DDFRM(16)		// RGB666
		#define	HwGE_BCH_DCTRL_DDFRM_ARGB666		HwGE_BCH_DCTRL_DDFRM(17)		// Alpha-RGB666
		#define	HwGE_BCH_DCTRL_DDFRM_RGB888		HwGE_BCH_DCTRL_DDFRM(18)		// RGB888
		#define	HwGE_BCH_DCTRL_DDFRM_ARGB888		HwGE_BCH_DCTRL_DDFRM(19)		// Alpha-RGB888
		#define	HwGE_BCH_DCTRL_DDFRM_MASK		HwGE_BCH_DCTRL_DDFRM(31)
} sHwGE_BCH;

#define	HwGE_SRC0PARAM_BASE					*(volatile unsigned long *)0xF6000060	// R/W,  Source 0 Parameter Base Register
#define	HwGE_SRC1PARAM_BASE					*(volatile unsigned long *)0xF6000068	// R/W,  Source 1 Parameter Base Register
#define	HwGE_SRC2PARAM_BASE					*(volatile unsigned long *)0xF6000070	// R/W,  Source 2 Parameter Base Register
#define	HwGE_SRCPARAM_BASE(X)					*(volatile unsigned long *)(0xF6000060+(X)*8)	// R/W,  Source Parameter Base Register
typedef volatile struct
{
	unsigned	CHROMA;		// Source Chroma-key Parameter
		#define	HwGE_S_CHROMA_RY(X)				((X)*Hw16)						// R or Y Chroma-Key Value
		#define	HwGE_S_CHROMA_RY_MASK			HwGE_S_CHROMA_RY(255)
		#define	HwGE_S_CHROMA_GU(X)				((X)*Hw8)						// G or U Chroma-Key Value
		#define	HwGE_S_CHROMA_GU_MASK			HwGE_S_CHROMA_GU(255)
		#define	HwGE_S_CHROMA_BV(X)				((X)*Hw0)						// B or V Chroma-Key Value
		#define	HwGE_S_CHROMA_BV_MASK			HwGE_S_CHROMA_BV(255)
	unsigned	PARAM;			// Source Arithmetic Parameter
		#define	HwGE_S_PARAM_RY(X)					((X)*Hw16)						// R or Y Arithmetic Parameter
		#define	HwGE_S_PARAM_RY_MASK				HwGE_S_PARAM_RY(255)
		#define	HwGE_S_PARAM_GU(X)					((X)*Hw8)						// G or U Arithmetic Parameter
		#define	HwGE_S_PARAM_GU_MASK				HwGE_S_PARAM_GU(255)
		#define	HwGE_S_PARAM_BV(X)					((X)*Hw0)						// B or V Arithmetic Parameter
		#define	HwGE_S_PARAM_BV_MASK				HwGE_S_PARAM_BV(255)
} sHwGE_SRC;

typedef volatile struct
{
	sHwGE_FCH	FCH[3];		// Front-End Channel Register Block (Valid only [0], [1]  ([2] is dummy))
	sHwGE_SRC	S[3];		// Source Parameter Register Block
	unsigned		SCTRL;		// Source Control Register
		#define	HwGE_SCTRL_S2ARITH(X)				((X)*Hw25)						// Source 2 Arithmetic Operation
		#define	HwGE_SCTRL_S2ARITH_BYPASS			HwGE_SCTRL_S2ARITH(0)			// Y = Source
		#define	HwGE_SCTRL_S2ARITH_FILL				HwGE_SCTRL_S2ARITH(2)			// Y = Source Param
		#define	HwGE_SCTRL_S2ARITH_INV				HwGE_SCTRL_S2ARITH(3)			// Y = 255 - Source
		#define	HwGE_SCTRL_S2ARITH_ADD			HwGE_SCTRL_S2ARITH(4)			// Y = Source + Source Param
		#define	HwGE_SCTRL_S2ARITH_SUBA			HwGE_SCTRL_S2ARITH(5)			// Y = Source - Source Param
		#define	HwGE_SCTRL_S2ARITH_SUBB			HwGE_SCTRL_S2ARITH(6)			// Y = Source Param - Source
		#define	HwGE_SCTRL_S2ARITH_MUL				HwGE_SCTRL_S2ARITH(7)			// Y = Source * Source Param (Mantisa = [7:6], Fraction = [5:0])
		#define	HwGE_SCTRL_S2ARITH_MASK			HwGE_SCTRL_S2ARITH(7)
		#define	HwGE_SCTRL_S1ARITH(X)				((X)*Hw22)						// Source 1 Arithmetic Operation
		#define	HwGE_SCTRL_S1ARITH_BYPASS			HwGE_SCTRL_S1ARITH(0)			// Y = Source
		#define	HwGE_SCTRL_S1ARITH_FILL				HwGE_SCTRL_S1ARITH(2)			// Y = Source Param
		#define	HwGE_SCTRL_S1ARITH_INV				HwGE_SCTRL_S1ARITH(3)			// Y = 255 - Source
		#define	HwGE_SCTRL_S1ARITH_ADD			HwGE_SCTRL_S1ARITH(4)			// Y = Source + Source Param
		#define	HwGE_SCTRL_S1ARITH_SUBA			HwGE_SCTRL_S1ARITH(5)			// Y = Source - Source Param
		#define	HwGE_SCTRL_S1ARITH_SUBB			HwGE_SCTRL_S1ARITH(6)			// Y = Source Param - Source
		#define	HwGE_SCTRL_S1ARITH_MUL				HwGE_SCTRL_S1ARITH(7)			// Y = Source * Source Param (Mantisa = [7:6], Fraction = [5:0])
		#define	HwGE_SCTRL_S1ARITH_MASK			HwGE_SCTRL_S1ARITH(7)
		#define	HwGE_SCTRL_S0ARITH(X)				((X)*Hw19)						// Source 0 Arithmetic Operation
		#define	HwGE_SCTRL_S0ARITH_BYPASS			HwGE_SCTRL_S0ARITH(0)			// Y = Source
		#define	HwGE_SCTRL_S0ARITH_FILL				HwGE_SCTRL_S0ARITH(2)			// Y = Source Param
		#define	HwGE_SCTRL_S0ARITH_INV				HwGE_SCTRL_S0ARITH(3)			// Y = 255 - Source
		#define	HwGE_SCTRL_S0ARITH_ADD			HwGE_SCTRL_S0ARITH(4)			// Y = Source + Source Param
		#define	HwGE_SCTRL_S0ARITH_SUBA			HwGE_SCTRL_S0ARITH(5)			// Y = Source - Source Param
		#define	HwGE_SCTRL_S0ARITH_SUBB			HwGE_SCTRL_S0ARITH(6)			// Y = Source Param - Source
		#define	HwGE_SCTRL_S0ARITH_MUL				HwGE_SCTRL_S0ARITH(7)			// Y = Source * Source Param (Mantisa = [7:6], Fraction = [5:0])
		#define	HwGE_SCTRL_S0ARITH_MASK			HwGE_SCTRL_S0ARITH(7)
		#define	HwGE_SCTRL_S2Y2REN_EN				Hw18							// Source 2 YUV to RGB Converter Enable
		#define	HwGE_SCTRL_S1Y2REN_EN				Hw17							// Source 1 YUV to RGB Converter Enable
		#define	HwGE_SCTRL_S0Y2REN_EN				Hw16							// Source 0 YUV to RGB Converter Enable
		#define	HwGE_SCTRL_S2Y2RMODE(X)			((X)*Hw13)						// Source 2 YUV to RGB Converter Type
		#define	HwGE_SCTRL_S2Y2RMODE_TYPE0		HwGE_SCTRL_S2Y2RMODE(0)		// R = Y+1.371(V-128), G = Y-0.336(U-128)-0.698(V-128), B = Y+1.732(U-128)
		#define	HwGE_SCTRL_S2Y2RMODE_TYPE1		HwGE_SCTRL_S2Y2RMODE(1)		// R = 1.164(Y-16)+1.159(V-128), G = 1.164(Y-16)-0.391(U-128)-0.813(V-128), B = 1.164(Y-16)+2.018(U-128)
		#define	HwGE_SCTRL_S2Y2RMODE_TYPE2		HwGE_SCTRL_S2Y2RMODE(2)		// R = Y+1.540(V-128), G = Y-0.183(U-128)-0.459(V-128), B = Y+1.816(U-128)
		#define	HwGE_SCTRL_S2Y2RMODE_TYPE3		HwGE_SCTRL_S2Y2RMODE(3)		// R = 1.164(Y-16)+1.793(V-128), G = 1.164(Y-16)-0.213(U-128)-0.534(V-128), B = 1.164(Y-16)+2.115(U-128)
		#define	HwGE_SCTRL_S2Y2RMODE_MASK		HwGE_SCTRL_S2Y2RMODE(3)
		#define	HwGE_SCTRL_S1Y2RMODE(X)			((X)*Hw11)						// Source 1 YUV to RGB Converter Type
		#define	HwGE_SCTRL_S1Y2RMODE_TYPE0		HwGE_SCTRL_S1Y2RMODE(0)		// R = Y+1.371(V-128), G = Y-0.336(U-128)-0.698(V-128), B = Y+1.732(U-128)
		#define	HwGE_SCTRL_S1Y2RMODE_TYPE1		HwGE_SCTRL_S1Y2RMODE(1)		// R = 1.164(Y-16)+1.159(V-128), G = 1.164(Y-16)-0.391(U-128)-0.813(V-128), B = 1.164(Y-16)+2.018(U-128)
		#define	HwGE_SCTRL_S1Y2RMODE_TYPE2		HwGE_SCTRL_S1Y2RMODE(2)		// R = Y+1.540(V-128), G = Y-0.183(U-128)-0.459(V-128), B = Y+1.816(U-128)
		#define	HwGE_SCTRL_S1Y2RMODE_TYPE3		HwGE_SCTRL_S1Y2RMODE(3)		// R = 1.164(Y-16)+1.793(V-128), G = 1.164(Y-16)-0.213(U-128)-0.534(V-128), B = 1.164(Y-16)+2.115(U-128)
		#define	HwGE_SCTRL_S1Y2RMODE_MASK		HwGE_SCTRL_S1Y2RMODE(3)
		#define	HwGE_SCTRL_S0Y2RMODE(X)			((X)*Hw9)						// Source 0 YUV to RGB Converter Type
		#define	HwGE_SCTRL_S0Y2RMODE_TYPE0		HwGE_SCTRL_S0Y2RMODE(0)		// R = Y+1.371(V-128), G = Y-0.336(U-128)-0.698(V-128), B = Y+1.732(U-128)
		#define	HwGE_SCTRL_S0Y2RMODE_TYPE1		HwGE_SCTRL_S0Y2RMODE(1)		// R = 1.164(Y-16)+1.159(V-128), G = 1.164(Y-16)-0.391(U-128)-0.813(V-128), B = 1.164(Y-16)+2.018(U-128)
		#define	HwGE_SCTRL_S0Y2RMODE_TYPE2		HwGE_SCTRL_S0Y2RMODE(2)		// R = Y+1.540(V-128), G = Y-0.183(U-128)-0.459(V-128), B = Y+1.816(U-128)
		#define	HwGE_SCTRL_S0Y2RMODE_TYPE3		HwGE_SCTRL_S0Y2RMODE(3)		// R = 1.164(Y-16)+1.793(V-128), G = 1.164(Y-16)-0.213(U-128)-0.534(V-128), B = 1.164(Y-16)+2.115(U-128)
		#define	HwGE_SCTRL_S0Y2RMODE_MASK		HwGE_SCTRL_S0Y2RMODE(3)
		#define	HwGE_SCTRL_S2CHROMA_EN			Hw8								// Source 2 Chroma-Key Enable for Arithmetic
		#define	HwGE_SCTRL_S1CHROMA_EN			Hw7								// Source 1 Chroma-Key Enable for Arithmetic
		#define	HwGE_SCTRL_S0CHROMA_EN			Hw6								// Source 0 Chroma-Key Enable for Arithmetic
		#define	HwGE_SCTRL_S2SEL(X)					((X)*Hw4)						// Source 2 Selection
		#define	HwGE_SCTRL_S2SEL_DIS				HwGE_SCTRL_S2SEL(0)			// Source 2 Disabled
		#define	HwGE_SCTRL_S2SEL_FCH0				HwGE_SCTRL_S2SEL(1)			// Source 2 = Front-end Channel 0
		#define	HwGE_SCTRL_S2SEL_FCH1				HwGE_SCTRL_S2SEL(2)			// Source 2 = Front-end Channel 1
		#define	HwGE_SCTRL_S2SEL_FCH2				HwGE_SCTRL_S2SEL(3)			// Source 2 = Front-end Channel 2 (Not supported)
		#define	HwGE_SCTRL_S2SEL_MASK				HwGE_SCTRL_S2SEL(3)
		#define	HwGE_SCTRL_S1SEL(X)					((X)*Hw2)						// Source 1 Selection
		#define	HwGE_SCTRL_S1SEL_DIS				HwGE_SCTRL_S1SEL(0)			// Source 1 Disabled
		#define	HwGE_SCTRL_S1SEL_FCH0				HwGE_SCTRL_S1SEL(1)			// Source 1 = Front-end Channel 0
		#define	HwGE_SCTRL_S1SEL_FCH1				HwGE_SCTRL_S1SEL(2)			// Source 1 = Front-end Channel 1
		#define	HwGE_SCTRL_S1SEL_FCH2				HwGE_SCTRL_S1SEL(3)			// Source 1 = Front-end Channel 2 (Not supported)
		#define	HwGE_SCTRL_S1SEL_MASK				HwGE_SCTRL_S1SEL(3)
		#define	HwGE_SCTRL_S0SEL(X)					((X)*Hw0)						// Source 0 Selection
		#define	HwGE_SCTRL_S0SEL_DIS				HwGE_SCTRL_S0SEL(0)			// Source 0 Disabled (Not supported. Source 0 should be enabled)
		#define	HwGE_SCTRL_S0SEL_FCH0				HwGE_SCTRL_S0SEL(1)			// Source 0 = Front-end Channel 0
		#define	HwGE_SCTRL_S0SEL_FCH1				HwGE_SCTRL_S0SEL(2)			// Source 0 = Front-end Channel 1
		#define	HwGE_SCTRL_S0SEL_FCH2				HwGE_SCTRL_S0SEL(3)			// Source 0 = Front-end Channel 2 (Not supported)
		#define	HwGE_SCTRL_S0SEL_MASK				HwGE_SCTRL_S0SEL(3)

	unsigned		_RSV0;
	unsigned		OPPAT[2];	// Source Operator Register Block
		#define	HwGE_OPPAT_ALPHA(X)				((X)*Hw24)						// Alpha Value (Valid only if OPCTRL.OPMODE == Alpha-Blend Type 0)
		#define	HwGE_OPPAT_ALPHA_MASK				HwGE_OPPAT_ALPHA(15)
		#define	HwGE_OPPAT_PAT_RY(X)				((X)*Hw16)						// R or Y pattern value for Raster Operation of Source Operator
		#define	HwGE_OPPAT_PAT_RY_MASK			HwGE_OPPAT_PAT_RY(255)
		#define	HwGE_OPPAT_PAT_GU(X)				((X)*Hw8)						// G or U pattern value for Raster Operation of Source Operator
		#define	HwGE_OPPAT_PAT_GU_MASK			HwGE_OPPAT_PAT_GU(255)
		#define	HwGE_OPPAT_PAT_BV(X)				((X)*Hw0)						// B or V pattern value for Raster Operation of Source Operator
		#define	HwGE_OPPAT_PAT_BV_MASK			HwGE_OPPAT_PAT_BV(255)

	unsigned		OPCTRL;		// Source Operation Control Register
		#define	HwGE_OPCTRL_CSEL1(X)				((X)*Hw21)						// Chroma-Key Source Selection for Operator 1
		#define	HwGE_OPCTRL_CSEL1_DIS				HwGE_OPCTRL_CSEL1(0)			// Chroma-Key Disabled
		#define	HwGE_OPCTRL_CSEL1_S0CHROM			HwGE_OPCTRL_CSEL1(1)			// Chroma-Key source is output of Operator 0, ChromaKey Value = S0_CHROMA
		#define	HwGE_OPCTRL_CSEL1_S1CHROM			HwGE_OPCTRL_CSEL1(2)			// Chroma-Key source is output of Operator 0, ChromaKey Value = S1_CHROMA
		#define	HwGE_OPCTRL_CSEL1_S2CHROM			HwGE_OPCTRL_CSEL1(3)			// Chroma-Key source is Source 2, ChromaKey Value = S2_CHROMA
		#define	HwGE_OPCTRL_CSEL1_MASK			HwGE_OPCTRL_CSEL1(3)
		#define	HwGE_OPCTRL_OP1MODE(X)			((X)*Hw16)						// Operation 1 Mode (A = Result of OP 0, B = Source2, S2_CHROMA used)
		#define	HwGE_OPCTRL_OP1MODE_BLACK		HwGE_OPCTRL_OP1MODE(0)		// Blackness, Result = 0
		#define	HwGE_OPCTRL_OP1MODE_MCOPY		HwGE_OPCTRL_OP1MODE(1)		// Merged Copy, Result = PAT & A
		#define	HwGE_OPCTRL_OP1MODE_MPAINT		HwGE_OPCTRL_OP1MODE(2)		// Merged Paint, Result = ~A | B
		#define	HwGE_OPCTRL_OP1MODE_PCOPY		HwGE_OPCTRL_OP1MODE(3)		// Pattern Copy, Result = PAT
		#define	HwGE_OPCTRL_OP1MODE_PINV			HwGE_OPCTRL_OP1MODE(4)		// Pattern Inverter, Result = PAT ^ B
		#define	HwGE_OPCTRL_OP1MODE_PPAINT		HwGE_OPCTRL_OP1MODE(5)		// Pattern Paint, Result = (PAT | ~A) | B
		#define	HwGE_OPCTRL_OP1MODE_SCOPY		HwGE_OPCTRL_OP1MODE(6)		// Source Copy, Result = A
		#define	HwGE_OPCTRL_OP1MODE_SINV			HwGE_OPCTRL_OP1MODE(7)		// Source Inverter, Result = A ^ B
		#define	HwGE_OPCTRL_OP1MODE_SPAINT		HwGE_OPCTRL_OP1MODE(8)		// Source Paint, Result = A | B
		#define	HwGE_OPCTRL_OP1MODE_SAND			HwGE_OPCTRL_OP1MODE(9)		// Source AND, Result = A & B
		#define	HwGE_OPCTRL_OP1MODE_SERASE		HwGE_OPCTRL_OP1MODE(10)		// Source Erase, Result = A & ~B
		#define	HwGE_OPCTRL_OP1MODE_NSCOPY		HwGE_OPCTRL_OP1MODE(11)		// Not Source Copy, Result = ~A
		#define	HwGE_OPCTRL_OP1MODE_NSERASE		HwGE_OPCTRL_OP1MODE(12)		// Not Source Erase, Result = ~(A | B)
		#define	HwGE_OPCTRL_OP1MODE_DCOPY		HwGE_OPCTRL_OP1MODE(13)		// Destination Copy, Result = B
		#define	HwGE_OPCTRL_OP1MODE_NDCOPY		HwGE_OPCTRL_OP1MODE(14)		// Destination Inverter, Result = ~B
		#define	HwGE_OPCTRL_OP1MODE_WHITE			HwGE_OPCTRL_OP1MODE(15)		// Whiteness, Result = 1
		#define	HwGE_OPCTRL_OP1MODE_ATYPE0		HwGE_OPCTRL_OP1MODE(16)		// Alpha Blending Type 0, Result = Alpha-Blending with Alpha-Value (OP1PAT.ALPHA)
		#define	HwGE_OPCTRL_OP1MODE_ATYPE1		HwGE_OPCTRL_OP1MODE(24)		// Alpha Blending Type 1, Result = Alpha-Blending with Alpha-Value of AlphaRGB
		#define	HwGE_OPCTRL_OP1MODE_MASK			HwGE_OPCTRL_OP1MODE(31)
		#define	HwGE_OPCTRL_CSEL0(X)				((X)*Hw5)						// Chroma-Key Source Selection for Operator 0
		#define	HwGE_OPCTRL_CSEL0_DIS				HwGE_OPCTRL_CSEL0(0)			// Chroma-Key Operation Disabled
		#define	HwGE_OPCTRL_CSEL0_S0CHROM			HwGE_OPCTRL_CSEL0(1)			//  Chroma-Key source is Source 0, ChromaKey Value = S0_CHROMA
		#define	HwGE_OPCTRL_CSEL0_S1CHROM			HwGE_OPCTRL_CSEL0(2)			//  Chroma-Key source is Source 1, ChromaKey Value = S1_CHROMA
		#define	HwGE_OPCTRL_CSEL0_MASK			HwGE_OPCTRL_CSEL0(3)
		#define	HwGE_OPCTRL_OP0MODE(X)			((X)*Hw0)						// Operation 0 Mode (A = Source0, B = Source1, S1_CHROMA used)
		#define	HwGE_OPCTRL_OP0MODE_BLACK		HwGE_OPCTRL_OP0MODE(0)		// Blackness, Result = 0
		#define	HwGE_OPCTRL_OP0MODE_MCOPY		HwGE_OPCTRL_OP0MODE(1)		// Merged Copy, Result = PAT & A
		#define	HwGE_OPCTRL_OP0MODE_MPAINT		HwGE_OPCTRL_OP0MODE(2)		// Merged Paint, Result = ~A | B
		#define	HwGE_OPCTRL_OP0MODE_PCOPY		HwGE_OPCTRL_OP0MODE(3)		// Pattern Copy, Result = PAT
		#define	HwGE_OPCTRL_OP0MODE_PINV			HwGE_OPCTRL_OP0MODE(4)		// Pattern Inverter, Result = PAT ^ B
		#define	HwGE_OPCTRL_OP0MODE_PPAINT		HwGE_OPCTRL_OP0MODE(5)		// Pattern Paint, Result = (PAT | ~A) | B
		#define	HwGE_OPCTRL_OP0MODE_SCOPY		HwGE_OPCTRL_OP0MODE(6)		// Source Copy, Result = A
		#define	HwGE_OPCTRL_OP0MODE_SINV			HwGE_OPCTRL_OP0MODE(7)		// Source Inverter, Result = A ^ B
		#define	HwGE_OPCTRL_OP0MODE_SPAINT		HwGE_OPCTRL_OP0MODE(8)		// Source Paint, Result = A | B
		#define	HwGE_OPCTRL_OP0MODE_SAND			HwGE_OPCTRL_OP0MODE(9)		// Source AND, Result = A & B
		#define	HwGE_OPCTRL_OP0MODE_SERASE		HwGE_OPCTRL_OP0MODE(10)		// Source Erase, Result = A & ~B
		#define	HwGE_OPCTRL_OP0MODE_NSCOPY		HwGE_OPCTRL_OP0MODE(11)		// Not Source Copy, Result = ~A
		#define	HwGE_OPCTRL_OP0MODE_NSERASE		HwGE_OPCTRL_OP0MODE(12)		// Not Source Erase, Result = ~(A | B)
		#define	HwGE_OPCTRL_OP0MODE_DCOPY		HwGE_OPCTRL_OP0MODE(13)		// Destination Copy, Result = B
		#define	HwGE_OPCTRL_OP0MODE_NDCOPY		HwGE_OPCTRL_OP0MODE(14)		// Destination Inverter, Result = ~B
		#define	HwGE_OPCTRL_OP0MODE_WHITE			HwGE_OPCTRL_OP0MODE(15)		// Whiteness, Result = 1
		#define	HwGE_OPCTRL_OP0MODE_ATYPE0		HwGE_OPCTRL_OP0MODE(16)		// Alpha Blending Type 0, Result = Alpha-Blending with Alpha-Value (OP0PAT.ALPHA)
		#define	HwGE_OPCTRL_OP0MODE_ATYPE1		HwGE_OPCTRL_OP0MODE(24)		// Alpha Blending Type 1, Result = Alpha-Blending with Alpha-Value of AlphaRGB
		#define	HwGE_OPCTRL_OP0MODE_MASK			HwGE_OPCTRL_OP0MODE(31)
	unsigned		_RSV1;
	sHwGE_BCH	BCH[1];		// Back-End Channel Register Block
	unsigned		_RSV2, _RSV3;
	unsigned		CTRL;		// Graphic Engine Control Register
		#define	HwGE_CTRL_IEN						Hw16							// Graphic Engine Interrupt Enable
		#define	HwGE_CTRL_FCH0_EN					Hw0								// Graphic Engine Front-End Channel 0 Enable
		#define	HwGE_CTRL_FCH1_EN					Hw1								// Graphic Engine Front-End Channel 1 Enable
		#define	HwGE_CTRL_FCH2_EN					Hw2								// Graphic Engine Front-End Channel 2 Enable (Not supported)
	unsigned		IREQ;		// Graphic Engine Interrupt Request Register
		#define	HwGE_IREQ_FLAG						Hw16							// Graphic Engine Flag (Graphic Engine Operation Completed)
		#define	HwGE_IREQ_IRQ						Hw0								// Graphic Engine Interrupt Occurred (Graphic Engine Operation Completed)
} sHwGE;

#define	HwGE_BASE								*(volatile unsigned long *)0xF6000000	// Graphic Engine Base Regiseter

#define	HwGE_FCH0_SADDR0						*(volatile unsigned long *)0xF6000000	// R/W,  Front-End Channel 0 Source Address 0 Register

#define	HwGE_FCH0_SADDR1						*(volatile unsigned long *)0xF6000004	// R/W,  Front-End Channel 0 Source Address 1 Register

#define	HwGE_FCH0_SADDR2						*(volatile unsigned long *)0xF6000008	// R/W,  Front-End Channel 0 Source Address 2 Register

#define	HwGE_FCH0_SFSIZE						*(volatile unsigned long *)0xF600000C	// R/W,  Front-End Channel 0 Source Frame Pixel Size Register

#define	HwGE_FCH0_SOFF							*(volatile unsigned long *)0xF6000010	// R/W,  Front-End Channel 0 Source Pixel Offset Register

#define	HwGE_FCH0_SISIZE						*(volatile unsigned long *)0xF6000014	// R/W,  Front-End Channel 0 Source Pixel Size Register

#define	HwGE_FCH0_WOFF							*(volatile unsigned long *)0xF6000018	// R/W,  Front-End Channel 0 Window Pixel Offset Register

#define	HwGE_FCH0_SCTRL						*(volatile unsigned long *)0xF600001C	// R/W,  Front-End Channel 0 Control Register

#define	HwGE_FCH1_SADDR0						*(volatile unsigned long *)0xF6000020	// R/W,  Front-End Channel 1 Source Address 0 Register

#define	HwGE_FCH1_SADDR1						*(volatile unsigned long *)0xF6000024	// R/W,  Front-End Channel 1 Source Address 1 Register

#define	HwGE_FCH1_SADDR2						*(volatile unsigned long *)0xF6000028	// R/W,  Front-End Channel 1 Source Address 2 Register

#define	HwGE_FCH1_SFSIZE						*(volatile unsigned long *)0xF600002C	// R/W,  Front-End Channel 1 Source Frame Pixel Size Register

#define	HwGE_FCH1_SOFF							*(volatile unsigned long *)0xF6000030	// R/W,  Front-End Channel 1 Source Pixel Offset Register

#define	HwGE_FCH1_SISIZE						*(volatile unsigned long *)0xF6000034	// R/W,  Front-End Channel 1 Source Pixel Size Register

#define	HwGE_FCH1_WOFF							*(volatile unsigned long *)0xF6000038	// R/W,  Front-End Channel 1 Window Pixel Offset Register

#define	HwGE_FCH1_SCTRL						*(volatile unsigned long *)0xF600003C	// R/W,  Front-End Channel 1 Control Register

#define	HwGE_S0_CHROMA						*(volatile unsigned long *)0xF6000060	// R/W,  Source 0 Chroma-Key Parameter Register

#define	HwGE_S0_PARAM							*(volatile unsigned long *)0xF6000064	// R/W,  Source 0 Arithmetic Parameter Register

#define	HwGE_S1_CHROMA						*(volatile unsigned long *)0xF6000068	// R/W,  Source 1 Chroma-Key Parameter Register

#define	HwGE_S1_PARAM							*(volatile unsigned long *)0xF600006C	// R/W,  Source 1 Arithmetic Parameter Register

#define	HwGE_S2_CHROMA						*(volatile unsigned long *)0xF6000070	// R/W,  Source 2 Chroma-Key Parameter Register

#define	HwGE_S2_PARAM							*(volatile unsigned long *)0xF6000074	// R/W,  Source 2 Arithmetic Parameter Register

#define	HwGE_SCTRL								*(volatile unsigned long *)0xF6000078	// R/W,  Source Control Register

#define	HwGE_OP0PAT							*(volatile unsigned long *)0xF6000080	// R/W,  Source Operator 0 Pattern Register

#define	HwGE_OP1PAT							*(volatile unsigned long *)0xF6000084	// R/W,  Source Operator 1 Pattern Register

#define	HwGE_OPCTRL							*(volatile unsigned long *)0xF6000088	// R/W,  Source Operation Control Register

#define	HwGE_BCH_DADDR0						*(volatile unsigned long *)0xF6000090	// R/W,  Back-End Destination Address 0 Register

#define	HwGE_BCH_DADDR1						*(volatile unsigned long *)0xF6000094	// R/W,  Back-End Destination Address 1 Register

#define	HwGE_BCH_DADDR2						*(volatile unsigned long *)0xF6000098	// R/W,  Back-End Destination Address 2 Register

#define	HwGE_BCH_DFSIZE						*(volatile unsigned long *)0xF600009C	// R/W,  Back-End Destination Frame Pixel Size Register

#define	HwGE_BCH_DOFF							*(volatile unsigned long *)0xF60000A0	// R/W,  Back-End Destination Pixel Offset Register

#define	HwGE_BCH_DCTRL							*(volatile unsigned long *)0xF60000A4	// R/W,  Back-End Channel Control Register

#define	HwGE_CTRL								*(volatile unsigned long *)0xF60000B0	// R/W,  Graphic Engine Control Register

#define	HwGE_IREQ								*(volatile unsigned long *)0xF60000B4	// R/W,  Graphic Engine Interrupt Request Register

/************************************************************************
*	Virtual MMU Register Define					(Base Addr = 0xF7000000)
************************************************************************/
#define	HwVMT_BASE								*(volatile unsigned long *)0xF7000000	// VMT Base Regiseter

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
	#define	HwVMT_REGION_EN						Hw9								// Region Enable Register
	#define	HwVMT_CACHE_ON						Hw3								// Cacheable Register
	#define	HwVMT_CACHE_OFF						HwZERO
	#define	HwVMT_BUFF_ON							Hw2								// Bufferable Register
	#define	HwVMT_BUFF_OFF							HwZERO

	#define	HwVMT_REGION0_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION0_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION0_BU						Hw2								// Bufferable Register

#define	HwVMT_REGION1							*(volatile unsigned long *)0xF7000004	// R/W, Configuration Register for Region 1
	#define	HwVMT_REGION1_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION1_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION1_BU						Hw2								// Bufferable Register

#define	HwVMT_REGION2							*(volatile unsigned long *)0xF7000008	// R/W, Configuration Register for Region 2
	#define	HwVMT_REGION2_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION2_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION2_BU						Hw2								// Bufferable Register

#define	HwVMT_REGION3							*(volatile unsigned long *)0xF700000C	// R/W, Configuration Register for Region 3
	#define	HwVMT_REGION3_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION3_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION3_BU						Hw2								// Bufferable Register

#define	HwVMT_REGION4							*(volatile unsigned long *)0xF7000010	// R/W, Configuration Register for Region 4
	#define	HwVMT_REGION4_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION4_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION4_BU						Hw2								// Bufferable Register

#define	HwVMT_REGION5							*(volatile unsigned long *)0xF7000014	// R/W, Configuration Register for Region 5
	#define	HwVMT_REGION5_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION5_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION5_BU						Hw2								// Bufferable Register

#define	HwVMT_REGION6							*(volatile unsigned long *)0xF7000018	// R/W, Configuration Register for Region 6
	#define	HwVMT_REGION6_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION6_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION6_BU						Hw2								// Bufferable Register

#define	HwVMT_REGION7							*(volatile unsigned long *)0xF700001C	// R/W, Configuration Register for Region 7
	#define	HwVMT_REGION7_EN						Hw9								// Region Enable Register
	#define	HwVMT_REGION7_CA						Hw3								// Cacheable Register
	#define	HwVMT_REGION7_BU						Hw2								// Bufferable Register

#define	HwVMT_TABBASE							*(volatile unsigned long *)0xF7008000	// R, MMU Table Base Address

/************************************************************************
*	ETC Define
************************************************************************/
//#define	PLL_FREQ								2031428
//#define	PLL_FREQ								2400000
//#define	PLL_FREQ								2160000
#define	PLL_FREQ								1920000
//#define	PLL_FREQ								2485714
//#define	GET_DPHASE(fs,system)					(unsigned long)((fs)*(system)*16384/PLL_FREQ)

/************************************************************************
*	ARM
************************************************************************/
#define	IO_ARM_MMU_DTCM						Hw16
#define	IO_ARM_MMU_ICACHE						Hw12
#define	IO_ARM_MMU_DCACHE						Hw2
#define	IO_ARM_MMU_PROT						Hw0
#define	IO_ARM_MMU_ALL							(Hw16+Hw12+Hw2+Hw0)




/* =============================
General Bit Operator
============================= */
//
	#define	IO_CKC_BUS_RSVD		0x88000000
	#define	IO_CKC_BUS_INT			HwBCLKCTR_VIC_ON
	#define	IO_CKC_BUS_DMA			HwBCLKCTR_DMA_ON
	#define	IO_CKC_BUS_HDD			HwBCLKCTR_HDD_ON
	#define	IO_CKC_BUS_GPIO		0
	#define	IO_CKC_BUS_UA2			HwBCLKCTR_UA2_ON
	#define	IO_CKC_BUS_usbDMA		0
	#define	IO_CKC_BUS1_UA3		HwBCLKCTR1_UA3_ON
	#define	IO_CKC_BUS64_UA3		HwBCLKCTR64_UA3_ON
	#define	IO_CKC_BUS_GS			0
	#define	IO_CKC_BUS_SPI1		HwBCLKCTR_GPSB1_ON
	#define	IO_CKC_BUS1_SPI2		HwBCLKCTR1_GPSB2_ON
	#define	IO_CKC_BUS1_SPI3		HwBCLKCTR1_GPSB3_ON
	#define	IO_CKC_BUS64_SPI2		HwBCLKCTR64_GPSB2_ON
	#define	IO_CKC_BUS64_SPI3		HwBCLKCTR64_GPSB3_ON
	#define	IO_CKC_BUS_VideoH		HwBCLKCTR_VCH_ON
	#define	IO_CKC_BUS_VideoC		HwBCLKCTR_SUBPRO
	#define	IO_CKC_BUS_VideoP		HwBCLKCTR_SUBPROPERI
	#define	IO_CKC_BUS1_VideoE		HwBCLKCTR1_VIDEOENC_ON
	#define	IO_CKC_BUS64_VideoE		HwBCLKCTR64_VIDEOENC_ON
	#define	IO_CKC_BUS_EMC			HwBCLKCTR_MEM_ON
	#define	IO_CKC_BUS_SPDIF		HwBCLKCTR_SPDIF_ON
	#define	IO_CKC_BUS_CAM			HwBCLKCTR_CIC_ON
	#define	IO_CKC_BUS_LCD			HwBCLKCTR_LCD_ON
	#define	IO_CKC_BUS_G2D			HwBCLKCTR_2D
	#define	IO_CKC_BUS_M2M			HwBCLKCTR_M2MS
	#define	IO_CKC_BUS_MBOX		HwBCLKCTR_MB
	#define	IO_CKC_BUS1_EHI1		HwBCLKCTR1_EHI1_ON
	#define	IO_CKC_BUS1_SRAMIF		HwBCLKCTR1_SRAMIF_ON
	#define	IO_CKC_BUS64_EHI1		HwBCLKCTR64_EHI1_ON
	#define	IO_CKC_BUS64_SRAMIF	HwBCLKCTR64_SRAMIF_ON
#endif

/* end of file */

