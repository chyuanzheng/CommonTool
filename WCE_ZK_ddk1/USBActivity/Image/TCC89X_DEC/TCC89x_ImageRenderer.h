#pragma once

#ifdef __TCC89XX_WINCE__

//#define ROTATE_BUFFER	0x23F00000 //Reserved Memory Address

#include <windows.h>
#include "Common/TCC89x_Physical.h"
#include "Common/TCC89x_Structures.h"
#include "Common/Virtual.h"
#include "common/include/clock.h"

typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;

/* RGB */
//#define Output_YUV2RGBConvert    // Define : Using Output data of RGB

#define YUV420 0
#define YUV422 1
#define PARTIAL_ROT		0
#define GENERAL_ROT		1

#define DMA2D_NO_OPERATION			0
#define DMA2D_ROTATE_90_DEGREES		1	// Count-clock Rotation 90 degrees
#define DMA2D_ROTATE_180_DEGREES	2	// Count-clock Rotation 180 degrees
#define DMA2D_ROTATE_270_DEGREES	3	// Count-clock Rotation 270 degrees
#define DMA2D_ROTATE_FLIP_VERTICAL	4	// Mirroring(flipping) vertically
#define DMA2D_ROTATE_FLIP_HORIZON	5	// Mirroring(flipping) horizontally
#define DMA2D_ROTATE_FLIP_ALL		6	// Mirroring(flipping) horizontally and vertically

#define VID_DRV_NO_ERRROR 				0
#define VID_DRV_ERR_INVALID_HANDLE			-1
#define VID_DRV_ERR_INVALID_PARAMETER		-2
#define VID_DRV_ERR_ALLOC_MEM				-3
#define VID_DRV_ERR_INVALID_VIDEO_FORMAT	-4

typedef enum 
{
	CH_DATACOPY = 0,
	CH_HMIRROR  = 2,
	CH_VMIRROR  = 3,
	CH_VHMIRROR = 4,
	CH_ROT90    = 5,		
	CH_ROT180   = 6,		
	CH_ROT270   = 7	
}GE_CH_OPMODE;

typedef enum 
{
	ZF_ZEROFILL,
	ZF_MSBFILL
}GE_FCH_ZEROFILL;

typedef enum
{
	FORMAT_YUV444   = 0,	
	FORMAT_YUV440   = 1,	
	FORMAT_YUV422   = 2,		
	FORMAT_YUV420   = 3,		
	FORMAT_YUV411   = 4,		
	FORMAT_YUV410   = 5,
	FORMAT_INT422   = 6,
	FORMAT_INT420   = 7,
	FORMAT_SEQ444   = 8,		
	FORMAT_SEQ422   = 9,
	FORMAT_RGB332   = 10,
	FORMAT_RGB444   = 12,		
	FORMAT_ARGB4444  = 13,	
	FORMAT_RGB454   = 14,		
	FORMAT_ARGB3454  = 15,	
	FORMAT_RGB555   = 16,		
	FORMAT_ARGB1555  = 17,	
	FORMAT_RGB565   = 18,		
	FORMAT_RGB666   = 20,		
	FORMAT_ARGB4666  = 21,	
	FORMAT_ARGB6666  = 22,	
	FORMAT_RGB888   = 23,
	FORMAT_ARGB4888  = 24,
	FORMAT_ARGB8888  = 25
} GE_CH_DATAFORMAT;

typedef enum 
{
	ARITH_BYPASS  = 0,
	ARITH_FILL	  = 2,
	ARITH_INV	  = 3,
	ARITH_ADD	  = 4,
	ARITH_SUB_A	  = 5,
	ARITH_SUB_B	  = 6,
	ARITH_MUL	  = 7
}GE_SOURCE_ARITHMODE;

typedef enum 
{
	SOURCE_Y2R_DISABLE,
	SOURCE_Y2R_ENABLE
}GE_SOURCE_YUV2RGBEN;

typedef enum 
{
	SOURCE_Y2RCON_TYPE0,
	SOURCE_Y2RCON_TYPE1,
	SOURCE_Y2RCON_TYPE2,
	SOURCE_Y2RCON_TYPE3
}GE_SOURCE_YUV2RGBTYPE;

typedef enum 
{
	SOURCE_CHROMA_DISABLE,
	SOURCE_CHROMA_ENABLE
}GE_SOURCE_CHROMAEN;

typedef enum 
{
	SOURCE_DISABLE,
	SOURCE_FECH0,
	SOURCE_FECH1,
	SOURCE_FECH2
}GE_SOURCE_SELECT;

typedef enum 
{
	CHROMA_DISABLE,
	CHROMA_S0,
	CHROMA_S1
}GE_OP_CHROMA_SOURCE;

typedef enum 
{
	OPMODE_BLACK	= 0,
	OPMODE_MCOPY	= 1,
	OPMODE_MPAINT   = 2,
	OPMODE_PCOPY	= 3,
	OPMODE_PINV	    = 4,
	OPMODE_PPAINT   = 5,
	OPMODE_SCOPY	= 6,
	OPMODE_SINV	    = 7,
	OPMODE_SPAINT   = 8,
	OPMODE_SAND	    = 9,
	OPMODE_SERASE   = 10,
	OPMODE_NSCOPY   = 11,
	OPMODE_NSERASE  = 12,
	OPMODE_DCOPY	= 13,
	OPMODE_NDCOPY   = 14,
	OPMODE_WHITE	= 15,
	OPMODE_ATYPE0   = 16,
	OPMODE_ATYPE1   = 24
}GE_OP_OPMODE;

typedef enum 
{
	BCH_R2Y_DISABLE,
	BCH_R2Y_ENABLE
}GE_BCH_RGB2YUVEN;

typedef enum 
{
	BCH_R2YCON_TYPE0,
	BCH_R2YCON_TYPE1,
	BCH_R2YCON_TYPE2,
	BCH_R2YCON_TYPE3
}GE_BCH_RGB2YUVTYPE;

typedef enum 
{
	GE_INT_DISABLE,
	GE_INT_ENABLE
}GE_CTRL_INTENABLE;

typedef enum 
{
	GE_DISABLE      = 0, 
	GE_ENABLE_FCH0  = 1,
	GE_ENABLE_FCH1  = 2,
	GE_ENABLE_FCH01 = 4
}GE_CTRL_GEENABLE;

#define xCHValue 0x100010 // chromakey value : R:16 G:0 B:16

typedef struct _tMSC_REG{
unsigned int 	SRC_Y_BASE;//				//R/W  -  Scaler source image Y base address register 
unsigned int 	SRC_U_BASE;//			 	//R/W  -  Scaler source image U base address register 
unsigned int 	SRC_V_BASE;//			 	//R/W  -  Scaler source image V base address register 
unsigned int 	SRC_SIZE;//				 	//R/W  -  Source image size register 
unsigned int 	SRC_OFFSET;//			  	//R/W  -  Source image line offset register 
unsigned int 	SRC_CONFIG;//			 	//R/W  0x000x  Source image configuration register 
unsigned int	NOTDEFINED1;			
unsigned int 	NOTDEFINED2;
unsigned int 	DST_Y_BASE;//				//R/W  -  Scaler destination image Y base address register
unsigned int 	DST_U_BASE;//				//R/W  -  Scaler destination image U base address register
unsigned int 	DST_V_BASE;//			 	//R/W  -  Scaler destination image V base address register
unsigned int 	DST_SIZE;//				  	//R/W  -  Destination image size register 
unsigned int 	DST_OFFSET;//			 	//R/W  -  Destination image line offset register 
unsigned int 	DST_CONFIG;//			  	//R/W  0x00x  Destination image configuration register 
unsigned int	NOTDEFINED3;
unsigned int 	NOTDEFINED4;
unsigned int 	SCALE_RATIO;//			  	//R/W  0x01000100 Scale ratio register 
unsigned int 	SCALE_CTRL;//			  	//R/W  0x00000000 Scaler control register 
unsigned int 	STATUS;//				  	//R  -  Scaler status register 
unsigned int 	NOTDEFINED5;
unsigned int 	DST_RM_CNT;//			  	//R/W 0x00000000 Destination rolling(middle) line counter. 
unsigned int 	C_ROLL_CNT;//			 	//R  -  Current Rolling line counter. 
}tMSC_REG;

typedef struct _tLcdInterface{
unsigned int	LCTRL;//					// W, LCD Control Register
unsigned int	LBC;//						// W, LCD Background Color Register
unsigned int	LCLKDIV;//					// W, LCD Clock Divider Register
unsigned int	LHTIME1;//					// W, LCD Horizontal Timing Register 1

unsigned int	LHTIME2;//					// W, LCD Horizontal Timing Register 2
unsigned int	LVTIME1;//					// W, LCD Vertical Timing Register 1
unsigned int	LVTIME2;//					// W, LCD Vertical Timing Register 2
unsigned int	LVTIME3;//					// W, LCD Vertical Timing Register 3

unsigned int	LVTIME4;//					// W, LCD Vertical Timing Register 4
unsigned int	LLUTR;//					// W, LCD Lookup Register for Red
unsigned int	LLUTG;//					// W, LCD Lookup Register for Green
unsigned int	LLUTB;//					// W, LCD Lookup Register for Blue

unsigned int	LDP7L;//					// W, LCD Modulo 7 Dithering Pattern (Low)
unsigned int	LDP7H;//					// W, LCD Modulo 7 Dithering Pattern (High)
unsigned int	LDP5;//						// W, LCD Modulo 5 Dithering Pattern Register
unsigned int	LDP4;//						// W, LCD Modulo 4 Dithering Pattern Register

unsigned int	LDP3;//						// W, LCD 3-bit Dithering Pattern Register
unsigned int	LCP1;//						// W, LCD Clipping Register
unsigned int	LCP2;//						// W, LCD Clipping Register
unsigned int	LDS;//						// W, LCD Display Size Register

unsigned int	LSTATUS;//					// R/Clr, LCD Status Register
unsigned int	LIM;//						// R/W, LCD Interrupt Register
unsigned int	LGR0;//						// R/WW, LCD Gamma Correction Register 0 for Red Color
unsigned int	LGR1;//						// R/W  0x00000000 LCD Gamma Correction Register 1 for Red Color 

unsigned int	LGG0;//						// R/W  0x00000000 LCD Gamma Correction Register 0 for Green Color 
unsigned int	LGG1;//						// R/W  0x00000000 LCD Gamma Correction Register 1 for Green Color 
unsigned int	LGB0;//						// R/W  0x00000000 LCD Gamma Correction Register 0 for Blue Color 
unsigned int	LGB1;//						// R/W  0x00000000 LCD Gamma Correction Register 1 for Blue Color 

unsigned int	LENH;//						// R/W 0x00000020 LCD Color Enhancement Register 
unsigned int	NOTDEFINED1;//  
unsigned int	LI0C;// 						// R/W 0x00000000 LCD Image 0 Control Register 
unsigned int	LI0P;// 						// R/W  0x00000000 LCD Image 0 Position Register 

unsigned int	LI0S;// 						// R/W  0x00000000 LCD Image 0 Size Register 
unsigned int	LI0BA0;// 					// R/W  0x00000000 LCD Image 0 Base Address 0 Register. 
unsigned int	LI0CA;// 					// R/W 0x00000000 LCD Image 0 Current Address Register. 
unsigned int	LI0BA1;// 					// R/W 0x00000000 LCD Image 0 Base Address 1 Register 

unsigned int	LI0BA2;// 					// R/W 0x00000000 LCD Image 0 Base Address 2 Register 
unsigned int	LI0O;// 						// R/W 0x00000000 LCD Image 0 Offset Register 
unsigned int	LI0SR;// 					// R/W  0x00000000 LCD Image 0 Scale ratio 
unsigned int	LI0A;// 						// R/W 0x00000000 LCD Image 0 Alpha Configuration Register 

unsigned int	LI0KR;// 					// R/W  0x00000000 LCD Image 0 Keying Register for RED or LUMA(Y) 
unsigned int	LI0KG;// 					// R/W  0x00000000 LCD Image 0 Keying Register for BLUE or CHROMA(Cb) 
unsigned int	LI0KB;// 					// R/W  0x00000000 LCD Image 0 Keying Register for GREEN or CHROMA(Cr)
unsigned int	LI0EN;// 					// R/W 0x00000000 LCD Image 0 Enhancement Register 

unsigned int	LI1C;//						// R/W 0x00000000 LCD Image 1 Control Register 
unsigned int	LI1P;//						// R/W  0x00000000 LCD Image 1 Position Register 
unsigned int	LI1S;//						// R/W  0x00000000 LCD Image 1 Size Register 
unsigned int	LI1BA0;//					// R/W  0x00000000 LCD Image 1 Base Address 0 Register. 

unsigned int	LI1CA;//					// R/W 0x00000000 LCD Image 1 Current Address Register. 
unsigned int	LI1BA1;//					// R/W 0x00000000 Not Used 
unsigned int	LI1BA2;//					// R/W 0x00000000 Not Used 
unsigned int	LI1O;//						// R/W 0x00000000 LCD Image 1 Offset Register 

unsigned int	LI1SR;//						// R/W  0x00000000 LCD Image 1 Scale ratio- 
unsigned int	LI1A;//						// R/W 0x00000000 LCD Image 1 Alpha Configuration Register 
unsigned int	LI1KR;//						// R/W  0x00000000 LCD Image 1 Keying Register for RED or LUMA(Y) 
unsigned int	LI1KG;//					// R/W  0x00000000 LCD Image 1 Keying Register for BLUE or CHROMA(Cb) 

unsigned int	LI1KB;//						// R/W  0x00000000 LCD Image 1 Keying Register for GREEN or CHROMA(Cr)
unsigned int	LI1EN;//					// R/W 0x00000000 LCD Image 1 Enhancement Register 
unsigned int	LI2C;//						// R/W 0x00000000 LCD Image 2 Control Register 
unsigned int	LI2P;//						// R/W  0x00000000 LCD Image 2 Position Register 

unsigned int	LI2S;//						// R/W  0x00000000 LCD Image 2 Size Register 
unsigned int	LI2BA0;//					// R/W  0x00000000 LCD Image 2 Base Address 0 Register. 
unsigned int	LI2CA;//					// R/W 0x00000000 LCD Image 2 Current Address Register. 
unsigned int	LI2BA1;//					// R/W 0x00000000 Not Used 

unsigned int	LI2BA2;//					// R/W 0x00000000 Not Used 
unsigned int	LI2O;//						// R/W 0x00000000 LCD Image 2 Offset Register 
unsigned int	LI2SR;//						// R/W  0x00000000 LCD Image 2 Scale ratio 
unsigned int	LI2A;//						// R/W  0x00000000 LCD Image 2 Alpha Register 

unsigned int	LI2KR;//						// R/W  0x00000000 LCD Image 2 Keying Register for RED or LUMA(Y) 
unsigned int	LI2KG;//					// R/W  0x00000000 LCD Image 2 Keying Register for BLUE or CHROMA(Cb) 
unsigned int	LI2KB;//						// R/W  0x00000000 LCD Image 2 Keying Register for GREEN or CHROMA(Cr)
unsigned int	LI2EN;//					// R/W 0x00000000 LCD Image 2 Enhancement Register      
//unsigned int	LUTIDX;//					//    Lookup Table index Register 
}tLcdInterface;

typedef struct _tDDICInterface{
unsigned int DDIC_CTRL;
unsigned int DDIC_CFG0;
unsigned int DDIC_CFG1;
}tDDICInterface;

typedef struct _tOVERLAYMixer{		// 0xF0010000
unsigned int	FCH0_SADDR0;				//0x00 R/W 0x00000000 Front-End Channel 0 Source Address 0
unsigned int	FCH0_SADDR1;				//0x04 R/W 0x00000000 Front-End Channel 0 Source Address 1
unsigned int	FCH0_SADDR2;				//0x08 R/W 0x00000000 Front-End Channel 0 Source Address 2
unsigned int	FCH0_SFSIZE;				//0x0C R/W 0x00000000 Front-End Channel 0 Source Frame Pixel Size
unsigned int	FCH0_SOFF;				//0x10 R/W 0x00000000 Front-End Channel 0 Source Pixel Offset
unsigned int	FCH0_SISIZE;				//0x14 R/W 0x00000000 Front-End Channel 0 Source Image Pixel Size
unsigned int	FCH0_WOFF;				//0x18 R/W 0x00000000 Front-End Channel 0 Window Pixel Offset
unsigned int	FCH0_SCTRL;				//0x1C R/W 0x00000000 Front-End Channel 0 Control

unsigned int	FCH1_SADDR0;				//0x20 R/W 0x00000000 Front-End Channel 1 Source Address 0
unsigned int	FCH1_SADDR1;				//0x24 R/W 0x00000000 Front-End Channel 1 Source Address 1
unsigned int	FCH1_SADDR2;				//0x28 R/W 0x00000000 Front-End Channel 1 Source Address 2
unsigned int	FCH1_SFSIZE;				//0x2C R/W 0x00000000 Front-End Channel 1 Source Frame Pixel Size
unsigned int	FCH1_SOFF;				//0x30 R/W 0x00000000 Front-End Channel 1 Source Pixel Offset
unsigned int	FCH1_SISIZE;				//0x34 R/W 0x00000000 Front-End Channel 1 Source Image Pixel Size
unsigned int	FCH1_WOFF;				//0x38 R/W 0x00000000 Front-End Channel 1 Window Pixel Offset
unsigned int	FCH1_SCTRL;				//0x3C R/W 0x00000000 Front-End Channel 1 Control

unsigned int	FCH2_SADDR0;				//0x40 R/W 0x00000000 Front-End Channel 2 Source Address 0
unsigned int	FCH2_SADDR1;				//0x44 R/W 0x00000000 Front-End Channel 2 Source Address 1
unsigned int	FCH2_SADDR2;				//0x48 R/W 0x00000000 Front-End Channel 2 Source Address 2
unsigned int	FCH2_SFSIZE;			//0x4C R/W 0x00000000 Front-End Channel 2 Source Frame Pixel Size
unsigned int	FCH2_SOFF;				//0x50 R/W 0x00000000 Front-End Channel 2 Source Pixel Offset
unsigned int	FCH2_SISIZE;				//0x54 R/W 0x00000000 Front-End Channel 2 Source Image Pixel Size
unsigned int	FCH2_WOFF;				//0x58 R/W 0x00000000 Front-End Channel 2 Window Pixel Offset
unsigned int	FCH2_SCTRL;				//0x5C R/W 0x00000000 Front-End Channel 2 Control

unsigned int	S0_CHROMA;				// 0x60 R/W 0x00000000 Source 0 Chroma-Key Parameter
unsigned int	S0_PAR;				// 0x64 R/W 0x00000000 Source 0 Arithmetic Parameter
unsigned int	S1_CHROMA;				// 0x68 R/W 0x00000000 Source 1 Chroma-Key Parameter
unsigned int	S1_PAR;				// 0x6C R/W 0x00000000 Source 1 Arithmetic Parameter
unsigned int	S2_CHROMA;				// 0x70 R/W 0x00000000 Source 2 Chroma-Key Parameter
unsigned int	S2_PAR;				// 0x74 R/W 0x00000000 Source 2 Arithmetic Parameter
unsigned int	S_CTRL;				// 0x78 R/W 0x00000000 Source Control Register

unsigned int	NOTDEFINED0;				//- 0x7C - - Reserved

unsigned int	OP0_PAT;				// 0x80 R/W 0x00000000 Source Operator 0 Pattern
unsigned int	OP1_PAT;				// 0x84 R/W 0x00000000 Source Operator 1 Pattern
unsigned int	OP_CTRL;				// 0x88 R/W 0x00000000 Source Operation Control Register

unsigned int	NOTDEFINED1;				//- 0x8C - - Reserved

unsigned int	BCH_DADDR0;				// 0x90 R/W 0x00000000 Back-End Channel Destination Address 0
unsigned int	BCH_DADDR1;				// 0x94 R/W 0x00000000 Back -End Channel Destination Address 1
unsigned int	BCH_DADDR2;				// 0x98 R/W 0x00000000 Back -End Channel Destination Address 2
unsigned int	BCH_DFSIZE;				// 0x9C R/W 0x00000000 Back -End Channel Destination Frame Pixel Size
unsigned int	BCH_DOFF;				// 0xA0 R/W 0x00000000 Back -End Channel Destination Pixel Offset
unsigned int	BCH_DCTRL;				// 0xA4 R/W 0x00000000 Back -End Channel Control

unsigned int	NOTDEFINED2[2];				//- 0xA8 . 0xAF - - Reserved

unsigned int	BCH_DDMAT0;				// 0xB0 R/W 0x00000000 Back-End Channel Destination Dither Matrix 0
unsigned int	BCH_DDMAT1;				// 0xB4 R/W 0x00000000 Back-End Channel Destination Dither Matrix 1
unsigned int	BCH_DDMAT2;				// 0xB8 R/W 0x00000000 Back-End Channel Destination Dither Matrix 2
unsigned int	BCH_DDMAT3;			// 0xBC R/W 0x00000000 Back-End Channel Destination Dither Matrix 3
unsigned int	OM_CTRL	;			// 0xC0 R/W 0x00000000 Overlay Mixer Control
unsigned int	OM_IREQ	;			// 0xC4 R/W 0x00000000 Overlay Mixer Interrupt Request

//unsigned int	NOTDEFINED3[206]			// 0xC8 . 0x3FF - - Reserved

//unsigned int	FCH0_LUT			// 0x400 . 0x7FF R/W - Front-End Channel 0 Lookup Table
//unsigned int	FCH1_LUT			// 0x800 . 0xBFF R/W - Front-End Channel 1 Lookup Table
//unsigned int	FCH2_LUT			// 0xC00 . 0xFFF R/W - Front-End Channel 2 Lookup Table
}tOVERLAYMixer;

#define WVBUFF_SIZE 0x300000
#define WVBUFF_NUM	4 // 2^n 

struct yrSIZE
{
	int cx;
	int cy;
};

struct yrIMG_INFO
{
	unsigned int phyAddr;
	yrSIZE paddedSize;
};

struct yrRECT
{
	int left;
	int top;
	int right;
	int bottom;
};

class CImageRender
{
public:
	CImageRender(const int LcdWidth, const int LcdHeight);
	~CImageRender();

	void ReConfig();

	void	Render(const yrIMG_INFO& srcInfo, const yrRECT& srcRenderRect, const yrRECT& destRect);

	unsigned int RGBtoYUV(unsigned char *pSrcBase, unsigned char SrcFormat,
						unsigned int SrcHsize, unsigned int SrcVsize,
						unsigned char *pDstBase, unsigned char DstFormat);
private:	
	int VirtualAlloc_Init(void);
	void VirtualAlloc_Free(void);

	void TCC_VideoScale(U8 *pSrcBase, U16 nSrcWidth, U16 nSrcHeight, const yrRECT& srcRenderRect, 
						U8 nSrcType, U32 nSrcOffsetY, 
						U8 *pDstBase, U16 nDstWidth, U16 nDstHeight, const yrRECT& dstRenderRect, 
						U8 nDstType, U32 nDstOffsetY, 
						U8 nHeightOffset);
	void WriteFrame(unsigned int srcPhyAddr, const yrSIZE& srcSize, const yrRECT& srcRenderRect, int nType, int nHeightOffset);	

	void RotateImage(U8 *nSrcBaseY, unsigned int nSrcWidth, unsigned int nSrcHeight, int iHWJPGAngle);
	int TCC_ImageRotate(U8 *pSrource, U8 *pDestination, unsigned int  nSrcWidth, unsigned int  nSrcHeight,unsigned int  nRotateType, unsigned int  nImgType);
	unsigned int TCCAPI_2DDMA_Rotate(unsigned char *pSrcBaseY, unsigned char *pSrcBaseU, unsigned char *pSrcBaseV,
				                   unsigned char *pDstBaseY, unsigned char *pDstBaseU, unsigned char *pDstBaseV,
				                   unsigned int SrcHsize, unsigned int SrcVsize, unsigned int DstHsize, unsigned int DstVsize,
				                   unsigned int iRotVal, unsigned char ImgFormat, unsigned int uiPartialRot, int refStartPos, 
				                   unsigned int uiBlkSize);	

public:
	void GetStatusValue(BOOL bJPGSetRotate,int iJPGAngle);
	void IsEffectRender(BOOL bEffectRender);
	void SetDisplaySize(DWORD dwScreenWidth,DWORD dwScreenHeight);

	BOOL RotateForSWDecOutput(U8 *nSrcBaseY,float angle,unsigned int nSrcWidth, unsigned int nSrcHeight);
	void SetRotatedResultForSWDec(BOOL bSetRotate,int iJPGAngle);
	BOOL GetRotatedResultForSWDec();
	int GetRotatedAngleForSWDec();
	void DisplayVideoChannel(BOOL bSetting);

public:
	DWORD m_pScalerAddress; // SCALER Phyisical Memory Address
	DWORD m_pRotateAddress; // ROTATE Phyisical Memory Address
	DWORD m_pConvertAddress; // RGBtoYUV Convert Physical Memory Address
	DWORD m_pVideoStartMem;// Video Physical Memory Start Address

	unsigned int	m_nDstSizeH, m_nDstSizeV;
	unsigned int	m_nTop,m_nLeft;

protected:
	DWORD m_nScreenHeight;
	DWORD m_nScreenWidth;

	volatile tMSC_REG *sMSC;
	volatile tLcdInterface *pLcdINF;
	volatile tDDICInterface* pDDIC;
	volatile PPIC pPIC;
	volatile unsigned int Bak_LCTRL;
	volatile unsigned int Bak_LI0C;
	volatile unsigned int Bak_LCLKDIV;
	volatile unsigned int Bak_LI1C;
	volatile unsigned char* m_pWinceVBuffer[WVBUFF_NUM];

	volatile tOVERLAYMixer *pOverlayMixer;

	yrRECT m_Rect;
	int m_Mode;

	BOOL bHWJPGSetRotate;
	int iHWJPGAngle;
	BOOL bIsEffectRender;

	BOOL bSetRotateForSWDec;
}; // CImageRender

#endif

