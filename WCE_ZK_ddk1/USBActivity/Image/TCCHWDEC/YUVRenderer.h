#ifdef __TCC79XX_WINCE__
#pragma once

#include "Common/shared.h"

//#define ROTATE_BUFFER	0x23F00000 //Reserved Memory Address

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
	FORMAT_SEQ444   = 6,		
	FORMAT_SEQ422   = 7,		
	FORMAT_RGB444   = 8,		
	FORMAT_ARGB444  = 9,	
	FORMAT_RGB454   = 10,		
	FORMAT_ARGB454  = 11,	
	FORMAT_RGB555   = 12,		
	FORMAT_ARGB555  = 13,	
	FORMAT_RGB565   = 14,		
	FORMAT_RGB666   = 16,		
	FORMAT_ARGB666  = 17,	
	FORMAT_RGB888   = 18,		
	FORMAT_ARGB888  = 19
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

#ifndef HWJPGwithSWJPG
typedef struct __TCC79xCKC  // 0xF3000000
{
unsigned int	CLKCTRL; 	//0x00 R/W 0x800FF011 CPU & Bus Clock Control Register
unsigned int	PLL0CFG; 	//0x04 R/W 0x00015003 PLL0 Configuration Register
unsigned int	PLL1CFG; 	//0x08 R/W 0x00015003 PLL1 Configuration Register
unsigned int	CLKDIVC; 	//0x0C R/W 0x81828383 Clock Divider Configuration Register
unsigned int	CLKDIVC1; 	//0x10 R/W 0x00000000 PLL1 Divider Configuration Register
unsigned int	MODECTR; 	//0x14 R/W 0x00010000 Operating Mode Control Register
unsigned int	BCLKCTR0;	//0x18 R/W 0xFFFFFFFF Bus Clock Mask Control Register for Group 0
unsigned int	BCLKCTR1;	//0x1C R/W 0xFFFFFFFF Bus Clock Mask Control Register for Group 1
unsigned int	SWRESET0; 	//0x20 R/W 0x00800000 Software Reset Control Register for Group 0
unsigned int	SWRESET1; 	//0x24 R/W 0x00000000 Software Reset Control Register for Group 1
// ......
}TCC79xCKCReg;
#endif

typedef struct tGraphicEngineInterface{
unsigned int	FCH0_SADDR0;//						*(volatile unsigned long *)0xF6000000	// R/W,  Front-End Channel 0 Source Address 0 Register
unsigned int	FCH0_SADDR1;//						*(volatile unsigned long *)0xF6000004	// R/W,  Front-End Channel 0 Source Address 1 Register
unsigned int	FCH0_SADDR2;//						*(volatile unsigned long *)0xF6000008	// R/W,  Front-End Channel 0 Source Address 2 Register
unsigned int	FCH0_SFSIZE;//						*(volatile unsigned long *)0xF600000C	// R/W,  Front-End Channel 0 Source Frame Pixel Size Register
unsigned int	FCH0_SOFF;//						*(volatile unsigned long *)0xF6000010	// R/W,  Front-End Channel 0 Source Pixel Offset Register
unsigned int	FCH0_SISIZE;//						*(volatile unsigned long *)0xF6000014	// R/W,  Front-End Channel 0 Source Pixel Size Register
unsigned int	FCH0_WOFF;//						*(volatile unsigned long *)0xF6000018	// R/W,  Front-End Channel 0 Window Pixel Offset Register
unsigned int	FCH0_SCTRL;//						*(volatile unsigned long *)0xF600001C	// R/W,  Front-End Channel 0 Control Register
unsigned int	FCH1_SADDR0;//						*(volatile unsigned long *)0xF6000020	// R/W,  Front-End Channel 1 Source Address 0 Register
unsigned int	FCH1_SADDR1;//						*(volatile unsigned long *)0xF6000024	// R/W,  Front-End Channel 1 Source Address 1 Register
unsigned int	FCH1_SADDR2;//						*(volatile unsigned long *)0xF6000028	// R/W,  Front-End Channel 1 Source Address 2 Register
unsigned int	FCH1_SFSIZE;//						*(volatile unsigned long *)0xF600002C	// R/W,  Front-End Channel 1 Source Frame Pixel Size Register
unsigned int	FCH1_SOFF;//						*(volatile unsigned long *)0xF6000030	// R/W,  Front-End Channel 1 Source Pixel Offset Register
unsigned int	FCH1_SISIZE;//						*(volatile unsigned long *)0xF6000034	// R/W,  Front-End Channel 1 Source Pixel Size Register
unsigned int	FCH1_WOFF;//						*(volatile unsigned long *)0xF6000038	// R/W,  Front-End Channel 1 Window Pixel Offset Register
unsigned int	FCH1_SCTRL;//						*(volatile unsigned long *)0xF600003C	// R/W,  Front-End Channel 1 Control Register
unsigned int 	NOTDEFINES1[8];//
unsigned int	S0_CHROMA;//						*(volatile unsigned long *)0xF6000060	// R/W,  Source 0 Chroma-Key Parameter Register
unsigned int	S0_PARAM;//						*(volatile unsigned long *)0xF6000064	// R/W,  Source 0 Arithmetic Parameter Register
unsigned int	S1_CHROMA;//						*(volatile unsigned long *)0xF6000068	// R/W,  Source 1 Chroma-Key Parameter Register
unsigned int	S1_PARAM;//						*(volatile unsigned long *)0xF600006C	// R/W,  Source 1 Arithmetic Parameter Register
unsigned int	S2_CHROMA;//						*(volatile unsigned long *)0xF6000070	// R/W,  Source 2 Chroma-Key Parameter Register
unsigned int	S2_PARAM;//						*(volatile unsigned long *)0xF6000074	// R/W,  Source 2 Arithmetic Parameter Register
unsigned int	S_CTRL;//							*(volatile unsigned long *)0xF6000078	// R/W,  Source Control Register
unsigned int 	NOTDEFINES2;
unsigned int	OP0_PAT;//							*(volatile unsigned long *)0xF6000080	// R/W,  Source Operator 0 Pattern Register
unsigned int	OP1_PAT;//							*(volatile unsigned long *)0xF6000084	// R/W,  Source Operator 1 Pattern Register
unsigned int	OP_CTRL;//							*(volatile unsigned long *)0xF6000088	// R/W,  Source Operation Control Register
unsigned int 	NOTDEFINES3;
unsigned int	BCH_DADDR0;//						*(volatile unsigned long *)0xF6000090	// R/W,  Back-End Destination Address 0 Register
unsigned int	BCH_DADDR1;//						*(volatile unsigned long *)0xF6000094	// R/W,  Back-End Destination Address 1 Register
unsigned int	BCH_DADDR2;//						*(volatile unsigned long *)0xF6000098	// R/W,  Back-End Destination Address 2 Register
unsigned int	BCH_DFSIZE;//						*(volatile unsigned long *)0xF600009C	// R/W,  Back-End Destination Frame Pixel Size Register
unsigned int	BCH_DOFF;//						*(volatile unsigned long *)0xF60000A0	// R/W,  Back-End Destination Pixel Offset Register
unsigned int	BCH_DCTRL;//						*(volatile unsigned long *)0xF60000A4	// R/W,  Back-End Channel Control Register
unsigned int 	NOTDEFINES4[2];
unsigned int	GE_CTRL;//							*(volatile unsigned long *)0xF60000B0	// R/W,  Graphic Engine Control Register
unsigned int	GE_IREQ;//							*(volatile unsigned long *)0xF60000B4	// R/W,  Graphic Engine Interrupt Request Register
}tGraphicEngineInterface;

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

class CYUVRenderer
{
public:
	CYUVRenderer(const int LcdWidth, const int LcdHeight);
	~CYUVRenderer();

	void	Render(const yrIMG_INFO& srcInfo, const yrRECT& srcRenderRect, const yrRECT& destRect);
	static void	GetChromakeyColor(int& r, int& g, int& b);

private:
	int		VirtualAlloc_Init(void);
	void	VirtualAlloc_Free(void);
	void	TCC_VideoScale(
			U8 *pSrcBase, U16 nSrcWidth, U16 nSrcHeight, const yrRECT& srcRenderRect, 
			U8 nSrcType, U32 nSrcOffsetY, 
			U8 *pDstBase, U16 nDstWidth, U16 nDstHeight, const yrRECT& dstRenderRect, 
			U8 nDstType, U32 nDstOffsetY, 
			volatile MSC_REG *mMsc, U8 nHeightOffset);
	void	WriteFrame(unsigned int srcPhyAddr, const yrSIZE& srcSize, const yrRECT& srcRenderRect, int nType, int nHeightOffset);

public:
	void RotateImage(U8 *nSrcBaseY, unsigned int  nSrcWidth, unsigned int  nSrcHeight, int iHWJPGAngle);
	int	 TCC_ImageRotate(U8 *pSrource, U8 *pDestination, unsigned int  nSrcWidth, unsigned int  nSrcHeight, unsigned int  nRotateType, unsigned int  nImgType);
	unsigned int TCCAPI_2DDMA_Rotate(unsigned char *pSrcBaseY, unsigned char *pSrcBaseU, unsigned char *pSrcBaseV,
				                   unsigned char *pDstBaseY, unsigned char *pDstBaseU, unsigned char *pDstBaseV,
				                   unsigned int SrcHsize, unsigned int SrcVsize, unsigned int DstHsize, unsigned int DstVsize,
				                   unsigned int iRotVal, unsigned char ImgFormat, unsigned int uiPartialRot, int refStartPos, 
				                   unsigned int uiBlkSize);
public:
	void GetStatusValue(BOOL bJPGSetRotate,int iJPGAngle);
	void IsEffectRender(BOOL bEffectRender);

private:
	BOOL bHWJPGSetRotate;
	int iHWJPGAngle;
	BOOL bIsEffectRender;

private:
	yrRECT mRect;

	volatile MSC_REG		*mMsc;
	volatile unsigned int	*mpLcdReg;
	volatile unsigned int	mLcdReg_Bak0;
	volatile unsigned int	mLcdReg_Bak26;
	int mMode;	// chromakey mode (1)
	const int mLcdWidth;
	const int mLcdHeight;

	volatile TCC79xCKCReg* pCKCREG;

public:
	unsigned int m_pScalerAddress;
	unsigned int m_pRotateAddress; 

public:
	volatile tGraphicEngineInterface* pGEREG;
};


#endif
