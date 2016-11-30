#ifdef __TCC89XX_WINCE__

#if (1100 > _MSC_VER)
#include <olectlid.h>
#else
#include <olectl.h>
#endif	

#include "TCC89x_ImageRenderer.h"
#include "Common/pkfuncs.h"
#include "Common/ioctl_code.h"
#include "common/include/clock.h"
#include "common/include/globals.h"

//#define __2DACCELATE_CHECK__ //Checking after BSP 2662


#define HwMSCLSTATUS_IBUSY			Hw5 // Busy Interrupt Flag
#define	HwMSCLSTATUS_IRDY			Hw4	// Ready Interrupt Flag
#define	HwMSCLSTATUS_RDY			Hw0 // Ready Status Register

#define	HwMSCLSCALE_CTRL_FLS		Hw31 // Flush the internal FIFOs
#define HwMSCLSCALE_CTRL_IEN_BUSY	Hw2 // Scaler Busy Interrupt Enable
#define HwMSCLSCALE_CTRL_IEN_RDY	Hw1 // Scaler Ready Interrupt Enable
#define	HwMSCLSCALE_CTRL_EN			Hw0 // Scaler Enable
#define	HwMSCLSCALE_Y2R				(Hw13+Hw12) // YUV to RGB Conversion Enable


#define	HwLCTRL_TV					Hw7 // TV Out
#define	HwLCTRL_MSEL				Hw4
#define	HwLCTRL_OVP_IMG120			Hw3 //// Image Overlay Priority: 1 - 2 - 0
#define	HwLCTRL_OVP_IMG210			(Hw3 + Hw1) // Image Overlay Priority: 2 - 1 - 0
#define	HwLCTRL_OVP_IMG201			(Hw2 + Hw1) // Image Overlay Priority: 2 - 0 - 1

#define	HwLCTRL_OVP_IMG012			0      //// Image Overlay Priority: 0 - 1 -2
#define	HwLCTRL_OVP_IMG102			(Hw2)  //// Image Overlay Priority: 1 - 0 -2

#define	HwLCTRL_LEN_ENABLE			Hw0 // LCTRL Enable


#define	HwLI0C_AEN				Hw30 // Alpha Blending Enable
#define	HwLI0C_CEN				Hw29 // Chromakeying Enable
#define	HwLI0C_IEN				Hw28 // Image Displaying Enable
#define	HwLI0C_Y2R				Hw8  // YUV to RGB Conversion Enable
#define	HwLI0C_FMT_YUV420SEP	(Hw4+Hw3)     // YUV420 Seperated
#define	HwLI0C_FMT_YUV422SEQ	(Hw4+Hw3+Hw1) // YUV422 Sequential

#define ALPHABLEND_ALPHA_VALUE				16  //192	// 0~255 
#define CHROMAKEY_ALPHABLEND_ALPHA_VALUE	64	// 0~255

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
#define	PHYSICAL_DEC_MEM_START		0x46A00000 //0x01000000
#define	SCALER_TCC89X_OUT1			0x46000000 //0x00300000
#define	SCALER_TCC89X_OUT2			0x46300000 //0x00300000
#define	CONVERT_TCC89X_OUT			0x46600000 //0x00400000
#define	SCALER_TCC89X_SIZE			0x00300000
#define CONVERT_TCC89x_SIZE			0x00400000 
#else
#define	PHYSICAL_DEC_MEM_START		0x46600000 //0x01000000
#define	SCALER_TCC89X_OUT1			0x46000000 //0x00200000
#define	SCALER_TCC89X_OUT2			0x46200000 //0x00200000
#define	CONVERT_TCC89X_OUT			0x46400000 //0x00200000
#define	SCALER_TCC89X_SIZE			0x00200000
#define CONVERT_TCC89x_SIZE			0x00200000
#endif

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
extern BOOL bDetectHDMI;			// When Conntect HDMI, bDetectHDMI set TRUE
#endif

//
// Constructor
//
CImageRender::CImageRender(const int LcdWidth, const int LcdHeight)
:m_nScreenWidth(LcdWidth)
,m_nScreenHeight(LcdHeight)
,m_Mode(1)
,m_nTop(0)
,m_nLeft(0)
,m_nDstSizeH(0)
,m_nDstSizeV(0)
,sMSC(NULL)
,pLcdINF(NULL)
,pPIC(NULL)
,pDDIC(NULL)
,pOverlayMixer(NULL)
{
	m_pScalerAddress = SCALER_TCC89X_OUT1;
	m_pRotateAddress = SCALER_TCC89X_OUT2;
	m_pConvertAddress = CONVERT_TCC89X_OUT;
	m_pVideoStartMem = PHYSICAL_DEC_MEM_START;
	
	HKEY    hk=NULL;
	DWORD   dwStatus;
	DWORD	dwSize,dwType;
	DWORD 	codec_base =0x86000000, codec_len=0x02000000, virtual_offset=0x40000000;
	dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Drivers\\Magellan\\CONFIG", 0, 0, &hk);
	dwType = REG_DWORD;
	dwSize = sizeof(DWORD);
	if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	{	
		dwStatus = RegQueryValueEx(hk, _T("CODEC_BASE"), NULL, &dwType, (LPBYTE) &codec_base, &dwSize);
	}
	if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	{
		dwStatus = RegQueryValueEx(hk, _T("CODEC_LEN"), NULL, &dwType, (LPBYTE) &codec_len, &dwSize);
	}
	if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	{
		dwStatus = RegQueryValueEx(hk, _T("VIRTUAL_OFFSET"), NULL, &dwType, (LPBYTE) &virtual_offset, &dwSize);
	}
	if(dwStatus != ERROR_SUCCESS)
	{
		printf("[ERROR] ImageRender RegQuery Fail\n");
	}
	if(hk != NULL) 
	{
		RegCloseKey(hk);
	}
	
	m_pScalerAddress = (codec_base - virtual_offset);
	m_pRotateAddress = m_pScalerAddress + SCALER_TCC89X_SIZE;
	m_pConvertAddress = m_pRotateAddress + SCALER_TCC89X_SIZE;
	m_pVideoStartMem = m_pConvertAddress + CONVERT_TCC89x_SIZE;

	//printf("Scaler Address : 0x%X\r\n", m_pScalerAddress);
	//printf("Rotate Address : 0x%X\r\n", m_pRotateAddress);
	//printf("Convert Address : 0x%X\r\n", m_pConvertAddress);
	//printf("Video Address : 0x%X\r\n", m_pVideoStartMem);
	
	int ret=VirtualAlloc_Init();
	if(ret<0)
	{
		printf("CImageRender ERROR: VirtualAlloc Init\n");
	}

	Bak_LI0C    = pLcdINF->LI0C; 
	Bak_LCTRL   = pLcdINF->LCTRL;
	Bak_LCLKDIV = pLcdINF->LCLKDIV;
	Bak_LI1C    = pLcdINF->LI1C; 

	for(unsigned int i=0;i<WVBUFF_NUM;i++)
	{
		m_pWinceVBuffer[i]=NULL;
	}
}

void CImageRender::ReConfig()
{
	//m_pScalerAddress = SCALER_TCC89X_OUT1;
	//m_pRotateAddress = SCALER_TCC89X_OUT2;
	//m_pConvertAddress = CONVERT_TCC89X_OUT;
	//m_pVideoStartMem = PHYSICAL_DEC_MEM_START;

	//HKEY    hk=NULL;
	//DWORD   dwStatus;
	//DWORD	dwSize,dwType;
	//DWORD 	codec_base =0x86000000, codec_len=0x02000000, virtual_offset=0x40000000;
	//dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Drivers\\Magellan\\CONFIG", 0, 0, &hk);
	//dwType = REG_DWORD;
	//dwSize = sizeof(DWORD);
	//if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	//{	
	//	dwStatus = RegQueryValueEx(hk, _T("CODEC_BASE"), NULL, &dwType, (LPBYTE) &codec_base, &dwSize);
	//}
	//if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	//{
	//	dwStatus = RegQueryValueEx(hk, _T("CODEC_LEN"), NULL, &dwType, (LPBYTE) &codec_len, &dwSize);
	//}
	//if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	//{
	//	dwStatus = RegQueryValueEx(hk, _T("VIRTUAL_OFFSET"), NULL, &dwType, (LPBYTE) &virtual_offset, &dwSize);
	//}
	//if(dwStatus != ERROR_SUCCESS)
	//{
	//	printf("[ERROR] ImageRender RegQuery Fail\n");
	//}
	//if(hk != NULL) 
	//{
	//	RegCloseKey(hk);
	//}

	//m_pScalerAddress = (codec_base - virtual_offset);
	//m_pRotateAddress = m_pScalerAddress + SCALER_TCC89X_SIZE;
	//m_pConvertAddress = m_pRotateAddress + SCALER_TCC89X_SIZE;
	//m_pVideoStartMem = m_pConvertAddress + CONVERT_TCC89x_SIZE;

	//printf("Scaler Address : 0x%X\r\n", m_pScalerAddress);
	//printf("Rotate Address : 0x%X\r\n", m_pRotateAddress);
	//printf("Convert Address : 0x%X\r\n", m_pConvertAddress);
	//printf("Video Address : 0x%X\r\n", m_pVideoStartMem);

	//int ret=VirtualAlloc_Init();
	//if(ret<0)
	//{
	//	printf("CImageRender ERROR: VirtualAlloc Init\n");
	//}

	//Bak_LI0C    = pLcdINF->LI0C; 
	//Bak_LCTRL   = pLcdINF->LCTRL;
	//Bak_LCLKDIV = pLcdINF->LCLKDIV;
	//Bak_LI1C    = pLcdINF->LI1C; 

	//for(unsigned int i=0;i<WVBUFF_NUM;i++)
	//{
	//	m_pWinceVBuffer[i]=NULL;
	//}
}
//
// Destructor
//
CImageRender::~CImageRender()
{
	pLcdINF->LCTRL   = Bak_LCTRL;
	pLcdINF->LI0C	 = Bak_LI0C;
	pLcdINF->LCLKDIV = Bak_LCLKDIV;	
	pLcdINF->LI1C = Bak_LI1C; 

	VirtualAlloc_Free();
	for(unsigned int i=0;i<WVBUFF_NUM;i++)
	{
		if(m_pWinceVBuffer[i])
		{
			FreeVirtual((void*)m_pWinceVBuffer[i],WVBUFF_SIZE);
			m_pWinceVBuffer[i]=NULL;
		}
	}
}

int CImageRender::VirtualAlloc_Init(void)
{
	TWS_CKC_SetDDIBUS(DDIPWDN_MSCL1, 1);	//MSCL1

	sMSC = (volatile tMSC_REG*)SetVirtual( 0xF0220000, sizeof(tMSC_REG));	
	if( sMSC == NULL ) {
		return -1;
	}
	pLcdINF = (volatile tLcdInterface *)SetVirtual(0xF0204000,sizeof(tLcdInterface));
	if( pLcdINF == NULL ) {
		return -1;
	}	
	pPIC = (PPIC)SetVirtual((DWORD)&HwPIC_BASE, sizeof(PPIC));
	if( pPIC == NULL ) {
		return -1;
	}
	pDDIC = (volatile tDDICInterface*)SetVirtual(0xF0250000,sizeof(tDDICInterface));
	if(pDDIC==NULL)
	{
		return -1;
	}
	else
	{	
#ifndef __HDMI_INCLUDE__
		pDDIC->DDIC_CTRL =(Hw10|Hw11|Hw12|Hw5|Hw6|Hw7);
		pDDIC->DDIC_CFG0 = (5<<16|6<<24);
		pDDIC->DDIC_CFG1 = (7<<0|10<<8|11<<16|12<<24);
#endif
	}

#ifdef __2DACCELATE_CHECK__
	int iGraphicBusValue = TWS_CKC_GetGraphicBus();
	if(iGraphicBusValue<=0) //  Fxgrp :x , BSP Overlay :x
	{
		TWS_CKC_SetFBUSForGRPOn();

		pOverlayMixer = (tOVERLAYMixer*)SetVirtual(0xF0010000, sizeof(tOVERLAYMixer));
		if(pOverlayMixer == NULL) {
			return -1;
		}
		pOverlayMixer->FCH2_SADDR0=0xFF00;
	}
	else
	{
		printf("GraphicBus is aleady ON : %d\n",iGraphicBusValue);
		pOverlayMixer = (tOVERLAYMixer*)SetVirtual(0xF0010000, sizeof(tOVERLAYMixer));
		if(pOverlayMixer == NULL) {
			return -1;
		}
		if(pOverlayMixer->FCH2_SADDR0 == 0) // Fxgrp :O , BSP Overlay :x
			pOverlayMixer->FCH2_SADDR0 = 0xFF00;
		//else Fxgrp :O, BSP Overlay :O
	}

	printf("pOverlayMixer->FCH2_SADDR00 : 0x%X - 0x%X\r\n", &(pOverlayMixer->FCH2_SADDR0), pOverlayMixer->FCH2_SADDR0);

#else
	TWS_CKC_SetFBUSForGRPOn();

	pOverlayMixer = (tOVERLAYMixer*)SetVirtual(0xF0010000, sizeof(tOVERLAYMixer));
	if(pOverlayMixer == NULL) {
		return -1;
	}
#endif


	return 1;
}


void CImageRender::VirtualAlloc_Free(void)
{
	FreeVirtual((void*)sMSC, sizeof(tMSC_REG));
	FreeVirtual((void*)pLcdINF, sizeof(tLcdInterface));	
	FreeVirtual((void*)pPIC,sizeof(PPIC));
	FreeVirtual((void*)pDDIC,sizeof(pDDIC));
	FreeVirtual((void*)pOverlayMixer,sizeof(tOVERLAYMixer));
}


/**
 * render YUV420 image to LCD0 
 *
 * @Param _srcInfo			the information of source image 
 * @Param _srcRenderRect	the source rect to render (padded by 16)
 * @Param _destRect			the destination rect to render (padded by 16)
 */
 void CImageRender::Render(const yrIMG_INFO& _srcInfo, const yrRECT& _srcRenderRect, 
						  const yrRECT& _destRect)
{
	yrRECT srcRenderRect = _srcRenderRect;
	yrRECT destRect = _destRect; 

	// should be multiple of 16
	srcRenderRect.left = (_srcRenderRect.left>>4)<<4;
	srcRenderRect.right = (_srcRenderRect.right>>4)<<4;

	// should be multiple of 2
	srcRenderRect.top = (_srcRenderRect.top>>1)<<1;
	srcRenderRect.bottom = (_srcRenderRect.bottom>>1)<<1;
	
	// should be multiple of 8
	destRect.left = (_destRect.left>>3)<<3;

	// width of destination rect should be a multiply of 16 because of LCD control
#if 1
	if( (((_destRect.right-_destRect.left)>>4)<<4) < 16 )
	{
		destRect.right = (_destRect.right>>3)<<3;
	}
	else
#endif	
	
		destRect.right = destRect.left + (((_destRect.right-_destRect.left)>>4)<<4);
	
	// should be multiple of 2
	destRect.top = (_destRect.top>>1)<<1;
	destRect.bottom = (_destRect.bottom>>1)<<1;
	
	m_Rect = destRect;
	WriteFrame(_srcInfo.phyAddr, _srcInfo.paddedSize, srcRenderRect, 1, 0);
}

void CImageRender::GetStatusValue(BOOL bJPGSetRotate,int iJPGAngle)
{
	bHWJPGSetRotate = bJPGSetRotate;
	iHWJPGAngle		= iJPGAngle;
}

void CImageRender::IsEffectRender(BOOL bEffectRender)
{
	bIsEffectRender = bEffectRender;
}

void CImageRender::SetDisplaySize(DWORD dwScreenWidth,DWORD dwScreenHeight)
{
	m_nScreenWidth=dwScreenWidth;
	m_nScreenHeight=dwScreenHeight;
	//printf("\t\t Windows Size(%d,%d)\n",m_nScreenWidth,m_nScreenHeight);
}

void CImageRender::TCC_VideoScale (
		U8 *pSrcBase, U16 nSrcWidth, U16 nSrcHeight, const yrRECT& srcRenderRect, U8 nSrcType, U32 nSrcOffsetY, 
		U8 *pDstBase, U16 nDstWidth, U16 nDstHeight, const yrRECT& dstRenderRect, U8 nDstType, U32 nDstOffsetY,
		U8 nHeightOffset // garbage lines due to 16bit alignment output
		)
{
	U32		nScaleH, nScaleV;
	U32		nSrcOffsetC, nDstOffsetC;
	U32		nSrcFrameWidth, nDstFrameWidth;
	U32		nSrcRenderWidth, nSrcRenderHeight;
	U32		nDstRenderWidth, nDstRenderHeight;

	nSrcRenderWidth = srcRenderRect.right - srcRenderRect.left;
	nSrcRenderHeight = srcRenderRect.bottom - srcRenderRect.top;

	nDstRenderWidth = dstRenderRect.right - dstRenderRect.left;
	nDstRenderHeight = dstRenderRect.bottom - dstRenderRect.top;

	while ( (sMSC->STATUS & HwMSCLSTATUS_RDY) != HwMSCLSTATUS_RDY ) 
	{
		Sleep(0); 	// do nothing
	}
	
	nScaleH = nSrcRenderWidth * 256 / nDstWidth;
	nScaleV = (nSrcRenderHeight-nHeightOffset) * 256 / nDstHeight;

	nSrcOffsetC = nSrcOffsetY / 2;
#ifndef Output_YUV2RGBConvert
	nDstOffsetC = nDstOffsetY / 2;
#else
	nDstOffsetC = nDstWidth*2;
#endif

	nSrcFrameWidth = nSrcOffsetY;
	nDstFrameWidth = nDstOffsetY;

	const int offsetToRenderSrcInLuminance = (nSrcFrameWidth*srcRenderRect.top + srcRenderRect.left);
	const int offsetToRenderSrcInChrominance = (nSrcFrameWidth>>1)*(srcRenderRect.top>>1) + (srcRenderRect.left>>1);

	//Setting the Source Image Information 
	sMSC->SRC_Y_BASE= (unsigned int)(pSrcBase + offsetToRenderSrcInLuminance);
	sMSC->SRC_U_BASE= (unsigned int)(pSrcBase + nSrcFrameWidth * nSrcHeight + offsetToRenderSrcInChrominance);
	sMSC->SRC_V_BASE= (unsigned int)(sMSC->SRC_U_BASE + ((nSrcFrameWidth * nSrcHeight)>>2));
	
	sMSC->SRC_SIZE = ((nSrcRenderHeight-nHeightOffset)<<16) | (nSrcRenderWidth<<0);
	sMSC->SRC_OFFSET	= (nSrcOffsetC<<16) | (nSrcOffsetY<<0);
	sMSC->SRC_CONFIG 	= nSrcType;

	const int offsetToRenderDstInLuminance = (nDstFrameWidth*dstRenderRect.top + dstRenderRect.left);
	const int offsetToRenderDstInChrominance = (nDstFrameWidth>>1)*(dstRenderRect.top>>1) + (dstRenderRect.left>>1);

	//Setting the Destination Image Information
#ifndef Output_YUV2RGBConvert
	sMSC->DST_Y_BASE	= (unsigned int)(pDstBase /*+ offsetToRenderDstInLuminance*/);
	sMSC->DST_U_BASE	= (unsigned int)(pDstBase + nDstFrameWidth * nDstHeight /*+ offsetToRenderDstInChrominance*/);
	sMSC->DST_V_BASE 	= sMSC->DST_U_BASE + ((nDstFrameWidth * nDstHeight)>>2);

	sMSC->DST_SIZE 	= (nDstHeight<<16) | (nDstWidth<<0);
	sMSC->DST_OFFSET 	= (nDstOffsetC<<16) | (nDstOffsetY<<0);
	sMSC->DST_CONFIG	= nDstType;
#else
	sMSC->DST_Y_BASE	= pDstBase;
	sMSC->DST_SIZE 		= (nDstHeight<<16) | (nDstWidth<<0);
	sMSC->DST_OFFSET 	= ((nDstOffsetC)<<0);
	sMSC->DST_CONFIG	= 4;//Output : RGB565
#endif

	//Setting the Scale Factor
	sMSC->SCALE_RATIO	= (nScaleV << 16) | (nScaleH << 0);
	
	//Setting the Control Register
	sMSC->STATUS 		|= HwMSCLSTATUS_IRDY;
	//sMSC->SCALE_CTRL = HwMSCLSCALE_CTRL_IEN_RDY | HwMSCLSCALE_CTRL_EN | Hw29; // Hw29 = TCC83x Scaler type
#ifndef Output_YUV2RGBConvert
	sMSC->SCALE_CTRL = HwMSCLSCALE_CTRL_IEN_RDY | HwMSCLSCALE_CTRL_EN;
#else
	sMSC->SCALE_CTRL = HwMSCLSCALE_CTRL_IEN_RDY | HwMSCLSCALE_CTRL_EN | HwMSCLSCALE_Y2R;
#endif
	sMSC->SCALE_CTRL = HwMSCLSCALE_CTRL_IEN_RDY;
}

void CImageRender::WriteFrame(unsigned int srcPhyAddr, const yrSIZE& srcSize, const yrRECT& srcRenderRect, 
							  int nType, int nHeightOffset)
{
	unsigned int nBaseY;
	unsigned int nDstBaseY;
	unsigned int nWndSizeH,nWndSizeV;
	unsigned int nRegTemp;

	unsigned int Rotate_DstSize_X;
	unsigned int Rotate_DstSize_Y;
	
	nWndSizeH = m_Rect.right - m_Rect.left;
	nWndSizeV = m_Rect.bottom - m_Rect.top;
	m_nDstSizeH = (nWndSizeH>>3)<<3; 
	m_nDstSizeV = (nWndSizeV>>3)<<3;

	if((iHWJPGAngle == DMA2D_ROTATE_90_DEGREES)||(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES))
	{
		m_nTop=m_Rect.top;
		m_nLeft=m_Rect.left;

		nWndSizeV = m_Rect.right - m_Rect.left;
		nWndSizeH = m_Rect.bottom - m_Rect.top;
		m_nDstSizeH = (nWndSizeH>>3)<<3; 
		m_nDstSizeV = (nWndSizeV>>3)<<3;

		if ( (m_nTop+m_nDstSizeV) > static_cast<unsigned int>(m_nScreenHeight))
		{
			m_nTop =0;
		}
		if ( (m_nLeft+m_nDstSizeH) > static_cast<unsigned int>(m_nScreenWidth))
		{
			m_nLeft =0;
		}

		m_nDstSizeV = (m_nDstSizeV >> 4)<<4;
		m_nDstSizeH = (m_nDstSizeH >> 2)<<2;
	}
	else
	{
		if ( m_nDstSizeH > static_cast<unsigned int>(m_nScreenWidth)||m_nDstSizeH==0 ) 
		{
			m_nDstSizeH = m_nScreenWidth;
		}
		if ( m_nDstSizeV > static_cast<unsigned int>(m_nScreenHeight)||m_nDstSizeV==0 )
		{
			m_nDstSizeV = m_nScreenHeight;
		}
	
		m_nTop=m_Rect.top;
		m_nLeft=m_Rect.left;
	
		if ( (m_nTop+m_nDstSizeV) > static_cast<unsigned int>(m_nScreenHeight))
		{
			m_nTop =0;
		}
		if ( (m_nLeft+m_nDstSizeH) > static_cast<unsigned int>(m_nScreenWidth))
		{
			m_nLeft =0;
		}
	}

	nBaseY	= (unsigned int)srcPhyAddr;
	nDstBaseY	=  m_pScalerAddress;
#if 0
{
	unsigned char *pOut = (unsigned char*)SetVirtual(nBaseY, m_nDstSizeH*m_nDstSizeV*1.5);
	FILE *fp =fopen("\\NAND\\RenderOut.raw", "wb");
	fwrite((void*)pOut, 1,m_nDstSizeH*m_nDstSizeV*1.5, fp);
	fclose(fp);
	FreeVirtual(pOut, m_nDstSizeH*m_nDstSizeV*1.5);
}
#endif

	#if 0
	printf("\r\n[1. WriteFrame]\r\n");
	printf("\tnBaseY = 0x%X\r\n", nBaseY);
	printf("\tsrcSize.cx = %d\r\n", srcSize.cx);
	printf("\tsrcSize.cy = %d\r\n", srcSize.cy);
	printf("\t nType = %d\r\n", nType);
	printf("\tsrcRenderRect(left = %d, top = %d, right = %d, bottom = %d\r\n", srcRenderRect.left, srcRenderRect.top, srcRenderRect.right, srcRenderRect.bottom);
	printf("\tnDstBaseY = 0x%X\r\n", nDstBaseY);
	printf("\tm_nDstSizeH = %d\r\n", m_nDstSizeH);
	printf("\tm_nDstSizeV = %d\r\n", m_nDstSizeV);
	printf("\tm_Rect(left = %d, top = %d, right = %d, bottom = %d\r\n", m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	printf("\tnHeightOffset = %d\r\n", nHeightOffset);
	printf("\bHWJPGSetRotate = %d\r\n", bHWJPGSetRotate);
	printf("\bIsEffectRender = %d\r\n", bIsEffectRender);
	#endif
	
	if((srcSize.cx==m_nDstSizeH)&&(srcSize.cy==m_nDstSizeV))
	{
		bIsEffectRender=TRUE;
		nDstBaseY= nBaseY;
	}

	if(!bIsEffectRender)
	{
		TCC_VideoScale (
			(U8*)nBaseY,
			(U16)srcSize.cx,
			(U16)srcSize.cy/nType,
			srcRenderRect,
			3,
			(U16)srcSize.cx*nType,
			(unsigned char*)nDstBaseY,
			m_nDstSizeH,
			m_nDstSizeV,
			m_Rect,
			3,
			m_nDstSizeH,
			(U8)nHeightOffset // garbage lines due to 16bit alignment output
		);

		#if 0
		{
			unsigned char *pOut = (unsigned char*)SetVirtual(nDstBaseY, m_nDstSizeH*m_nDstSizeV*1.5);
			FILE *fp =fopen("\\NAND\\ScalerOut.raw", "wb");
			fwrite((void*)pOut, 1,m_nDstSizeH*m_nDstSizeV*1.5, fp);
			fclose(fp);
			FreeVirtual(pOut, m_nDstSizeH*m_nDstSizeV*1.5);
		}
		#endif
	}	

#ifndef Output_YUV2RGBConvert

	if(bHWJPGSetRotate)
	{
		while ( (sMSC->STATUS & HwMSCLSTATUS_RDY) != HwMSCLSTATUS_RDY ) 
		{
			Sleep(0); 	// check scaler routine
		}

		RotateImage((U8 *)nDstBaseY,m_nDstSizeH,m_nDstSizeV,iHWJPGAngle);

		#if 0
		{
			unsigned char *pOut = (unsigned char*)SetVirtual(m_pRotateAddress, m_nDstSizeH*m_nDstSizeV*1.5);
			FILE *fp =fopen("\\NAND\\rotate.raw", "wb");
			fwrite((void*)pOut, 1,m_nDstSizeH*m_nDstSizeV*1.5, fp);
			fclose(fp);
			FreeVirtual(pOut, m_nDstSizeH*m_nDstSizeV*1.5);
		}
		#endif
		
		if(iHWJPGAngle == DMA2D_ROTATE_90_DEGREES ||iHWJPGAngle ==DMA2D_ROTATE_270_DEGREES)
		{
			//m_nTop=(m_nScreenHeight-m_nDstSizeH)/2;
			//m_nLeft=(m_nScreenWidth-m_nDstSizeV)/2;

			m_nTop=m_Rect.top+(m_Rect.bottom-m_Rect.top-m_nDstSizeH)/2;
			m_nLeft=m_Rect.left+(m_Rect.right-m_Rect.left-m_nDstSizeV)/2;

			if ( (m_nTop+m_nDstSizeH) > static_cast<unsigned int>(m_nScreenHeight))
			{
				m_nTop =0;
			}
			if ( (m_nLeft+m_nDstSizeV) > static_cast<unsigned int>(m_nScreenWidth))
			{
				m_nLeft =0;
			}

			// Rotate output->Scaler input
			unsigned int Rotate_SrcBaseY = m_pRotateAddress;
			unsigned int Rotate_SrcSize_X = m_nDstSizeV;
			unsigned int Rotate_SrcSize_Y = m_nDstSizeH;
			yrRECT Rotate_SrcRect;
			Rotate_SrcRect.left = 0;
			Rotate_SrcRect.right = 0 +  Rotate_SrcSize_X;
			Rotate_SrcRect.top = 0;
			Rotate_SrcRect.bottom = 0 + Rotate_SrcSize_Y;

			// Scaler output setting			
			// remodeling of CalcDestinationRenderRect() 
			yrRECT Rotate_DstRect;
			Rotate_DstRect.left = 0;
			Rotate_DstRect.right = min((int)(Rotate_DstRect.left + Rotate_SrcSize_X), m_nScreenWidth);
			Rotate_DstRect.top = 0;
			Rotate_DstRect.bottom = min((int)(Rotate_DstRect.top + Rotate_SrcSize_Y), m_nScreenHeight);

			// Rotate Image-> Scaling output address
			//unsigned int Rotate_DstBaseY = m_pRotateAddress + 0x80000 ;//nDstBaseY;
			
			Rotate_DstSize_X = Rotate_DstRect.right - Rotate_DstRect.left;
			Rotate_DstSize_Y = Rotate_DstRect.bottom - Rotate_DstRect.top;

			pLcdINF->LI0BA0 = m_pRotateAddress;	// base output address	(Y)
			pLcdINF->LI0S = (Rotate_DstSize_Y<<16) | (Rotate_DstSize_X);
			pLcdINF->LI0O = ((Rotate_DstSize_X>>1)<<16) | (Rotate_DstSize_X); // Offset
		}
		else
		{
			pLcdINF->LI0BA0 = m_pRotateAddress;	// base output address	(Y)
			pLcdINF->LI0S= (m_nDstSizeV<<16) | (m_nDstSizeH); 
			pLcdINF->LI0O = ((m_nDstSizeH>>1)<<16) | (m_nDstSizeH); // Offset
		}
	}
	else
	{		
		if(bIsEffectRender)
		{
			pLcdINF->LI0BA0 = nBaseY;
		}
		else
		{
			pLcdINF->LI0BA0 = nDstBaseY; // base output Y address
		}
		pLcdINF->LI0S   = (m_nDstSizeV<<16) | (m_nDstSizeH); // size
		pLcdINF->LI0O = ((m_nDstSizeH>>1)     <<16) | (m_nDstSizeH); // Offset
	}

	if(bHWJPGSetRotate)
	{
		if(iHWJPGAngle == DMA2D_ROTATE_90_DEGREES ||iHWJPGAngle ==DMA2D_ROTATE_270_DEGREES)
		{
			pLcdINF->LI0P  = (m_nTop <<16)     | (m_nLeft); // position
			pLcdINF->LI0BA1 = pLcdINF->LI0BA0 + Rotate_DstSize_X*Rotate_DstSize_Y ; // base output U address
			pLcdINF->LI0BA2 = pLcdINF->LI0BA1 + (Rotate_DstSize_X*Rotate_DstSize_Y)/4; // base output V address
		}
		else
		{
			pLcdINF->LI0P  = (m_nTop <<16)     | (m_nLeft); // position
			pLcdINF->LI0BA1 = pLcdINF->LI0BA0 + m_nDstSizeH*m_nDstSizeV; // base output U address
			pLcdINF->LI0BA2 = pLcdINF->LI0BA1 + (m_nDstSizeH*m_nDstSizeV)/4; // base output V address
		}
	}
	else
	{
		pLcdINF->LI0P   = (m_nTop<<16) | (m_nLeft); // position
		pLcdINF->LI0BA1 = pLcdINF->LI0BA0 + m_nDstSizeH*m_nDstSizeV; // base output U address
		pLcdINF->LI0BA2 = pLcdINF->LI0BA1 + (m_nDstSizeH*m_nDstSizeV)/4; // base output V address
	} 

	if(m_Mode==2) // alpha blending 
	{
		nRegTemp = pLcdINF->LCTRL & 0xFFFFFFF0;
		nRegTemp |= HwLCTRL_LEN_ENABLE| HwLCTRL_OVP_IMG210 ;
		pLcdINF->LCTRL= nRegTemp;
		pLcdINF->LI1A = ALPHABLEND_ALPHA_VALUE|(ALPHABLEND_ALPHA_VALUE<<16);
		pLcdINF->LI1C &=~HwLI0C_AEN;
		pLcdINF->LI1C |=HwLI0C_AEN;
		pLcdINF->LI0C = HwLI0C_IEN |HwLI0C_Y2R |HwLI0C_FMT_YUV420SEP;	
	} 
	else if(m_Mode==1) // chromakey setting
	{
		nRegTemp = pLcdINF->LCTRL & 0xFFFFFFF0;
		nRegTemp |= HwLCTRL_LEN_ENABLE| HwLCTRL_OVP_IMG210 ;
		pLcdINF->LCTRL= nRegTemp;

		pLcdINF->LBC=0x80000000;
		pLcdINF->LI1KR = (0xFF<<16)|((xCHValue&0xFF0000)>>16);
		pLcdINF->LI1KG = (0xFF<<16)|((xCHValue&0x00FF00)>>8);
		pLcdINF->LI1KB = (0xFF<<16)|((xCHValue&0x0000FF));
		pLcdINF->LI1C &=~HwLI0C_CEN;
		pLcdINF->LI1C |=HwLI0C_CEN;
		pLcdINF->LI0C = HwLI0C_IEN |HwLI0C_Y2R |HwLI0C_FMT_YUV420SEP;	
	}
	else if(m_Mode==3) // chromakey & alpha blending setting
	{
		nRegTemp = pLcdINF->LCTRL & 0xFFFFFFF0;
		nRegTemp |= HwLCTRL_LEN_ENABLE| HwLCTRL_OVP_IMG210 ;
		pLcdINF->LCTRL= nRegTemp;
		pLcdINF->LI1A = ALPHABLEND_ALPHA_VALUE|(ALPHABLEND_ALPHA_VALUE<<16);
		pLcdINF->LI1KR = (0xFF<<16)|((xCHValue&0xFF0000)>>16);
		pLcdINF->LI1KG = (0xFF<<16)|((xCHValue&0x00FF00)>>8);
		pLcdINF->LI1KB = (0xFF<<16)|((xCHValue&0x0000FF));
		pLcdINF->LI1C &=~HwLI0C_AEN;
		pLcdINF->LI1C &=~HwLI0C_CEN;
		pLcdINF->LI1C|=HwLI0C_AEN;
		pLcdINF->LI1C|=HwLI0C_CEN;
		pLcdINF->LI0C =HwLI0C_IEN |HwLI0C_Y2R |HwLI0C_FMT_YUV420SEP;
	}
	else  // default (no alpha blending & no  chromakey)
	{
		nRegTemp = pLcdINF->LCTRL & 0xFFFFFFF0;
		nRegTemp |= HwLCTRL_LEN_ENABLE| HwLCTRL_OVP_IMG201 ;
		pLcdINF->LCTRL= nRegTemp;
		pLcdINF->LI0C &=~HwLI0C_AEN;
		pLcdINF->LI0C &=~HwLI0C_CEN;
		pLcdINF->LI0C = HwLI0C_IEN |HwLI0C_Y2R |HwLI0C_FMT_YUV420SEP;
	}	
	sMSC->STATUS |= HwMSCLSTATUS_IRDY;
	pPIC->INTMSK0 |=Hw16;
	
#else
//////////////Output: RGB565
#endif
}

void CImageRender::SetRotatedResultForSWDec(BOOL bSetRotate,int iJPGAngle)
{
	//printf("\r\n[SetRotatedResultForSWDec] bSetRotate = %d     iJPGAngle = %d------ \r\n",bSetRotate,iJPGAngle);
	bSetRotateForSWDec = bSetRotate;
	iHWJPGAngle		= iJPGAngle;
}

BOOL CImageRender::GetRotatedResultForSWDec()
{
	return bSetRotateForSWDec;
}

int CImageRender::GetRotatedAngleForSWDec()
{
	return iHWJPGAngle;
}

BOOL CImageRender::RotateForSWDecOutput(U8 *nSrcBaseY,float angle, unsigned int nSrcWidth, unsigned int nSrcHeight)
{
	iHWJPGAngle = (int)angle;
	
	switch(iHWJPGAngle)
	{
	case 90:
		{
		iHWJPGAngle = DMA2D_ROTATE_270_DEGREES;
		break;
		}
	case 180:
		{
		iHWJPGAngle = DMA2D_ROTATE_180_DEGREES;
		break;
		}
	case 270:
		{
		iHWJPGAngle = DMA2D_ROTATE_90_DEGREES;
		break;
		}
	case 0:
	default :
		{
		iHWJPGAngle = DMA2D_NO_OPERATION;
		break;
	        }
	}

	//printf("\r\n[RotateForSWDecOutput]nSrcBaseY = %d     angle = %f	(%d,%d) \r\n",nSrcBaseY,angle,nSrcWidth,nSrcHeight);
	int retVal = TCC_ImageRotate(
		(U8 *)nSrcBaseY,
		(U8 *)m_pRotateAddress,
		nSrcWidth,			
		nSrcHeight,	
		iHWJPGAngle,
		YUV420
	);
	//printf("[CImageRender::RotateForSWDecOutput]retVal=%d\n",retVal);
	SetRotatedResultForSWDec(TRUE,iHWJPGAngle);
	#if 0
		{
			printf("nSrcWidth : %d, nSrcHeight : %d\r\n", nSrcWidth, nSrcHeight);
			unsigned char *pOut = (unsigned char*)SetVirtual(m_pRotateAddress, nSrcWidth*nSrcHeight*1.5);
			FILE *fp =fopen("\\NAND\\RotateOutput.raw", "wb");
			fwrite((void*)pOut, 1,nSrcWidth*nSrcHeight*1.5, fp);
			fclose(fp);
			FreeVirtual(pOut, nSrcWidth*nSrcHeight*1.5);
		}
	#endif
	return TRUE;
}

void CImageRender::RotateImage(U8 *nSrcBaseY, unsigned int nSrcWidth, unsigned int nSrcHeight, int iHWJPGAngle)
{
//	printf("\r\n[2.RotateImage] Rotateprocess ------nSrcWidth = %d     nSrcHeight = %d------ \r\n",nSrcWidth,nSrcHeight);

	TCC_ImageRotate(
		(U8 *)nSrcBaseY,
		(U8 *)m_pRotateAddress,
		nSrcWidth,			
		nSrcHeight,	
		iHWJPGAngle,
		YUV420
	);
}


int CImageRender::TCC_ImageRotate(U8 *pSrource, U8 *pDestination, unsigned int  nSrcWidth, unsigned int  nSrcHeight,unsigned int  nRotateType, unsigned int  nImgType)
{
	unsigned char *nSBase0, *nSBase1, *nSBase2;
	unsigned char *nDBase0, *nDBase1, *nDBase2;

	nSBase0 = (U8 *)pSrource;
	nSBase1 = (U8 *)nSBase0 + (nSrcWidth *nSrcHeight);
	nSBase2 = (U8 *)nSBase1 + ((nSrcWidth *nSrcHeight)/4);

	nDBase0 = (U8 *)pDestination;
	nDBase1 = (U8 *)nDBase0 + (nSrcWidth *nSrcHeight);
	nDBase2 = (U8 *)nDBase1 + ((nSrcWidth *nSrcHeight)/4);
	

	if( nRotateType == DMA2D_ROTATE_90_DEGREES || nRotateType == DMA2D_ROTATE_270_DEGREES )
	{

		TCCAPI_2DDMA_Rotate((unsigned char *)nSBase0, (unsigned char *)nSBase1, (unsigned char *)nSBase2,
							(unsigned char *)nDBase0, (unsigned char *)nDBase1, (unsigned char *)nDBase2,
			                nSrcWidth, nSrcHeight,
			                nSrcHeight, nSrcWidth,
							nRotateType, (unsigned char)nImgType,
							GENERAL_ROT, 0, 32);
	}
	else //if( stDriverInfo->ucRotateType == DMA2D_ROTATE_180_DEGREES )
	{
		TCCAPI_2DDMA_Rotate((unsigned char *)nSBase0, (unsigned char *)nSBase1, (unsigned char *)nSBase2,
							(unsigned char *)nDBase0, (unsigned char *)nDBase1, (unsigned char *)nDBase2,
			                nSrcWidth, nSrcHeight,
							nSrcWidth, nSrcHeight,
							nRotateType, (unsigned char)nImgType,
							GENERAL_ROT, 0, 32);
	}
	return VID_DRV_NO_ERRROR;
}

unsigned int CImageRender::TCCAPI_2DDMA_Rotate(unsigned char *pSrcBaseY, unsigned char *pSrcBaseU, unsigned char *pSrcBaseV,
					                   unsigned char *pDstBaseY, unsigned char *pDstBaseU, unsigned char *pDstBaseV,
					                   unsigned int SrcHsize, unsigned int SrcVsize, unsigned int DstHsize, unsigned int DstVsize,
					                   unsigned int iRotVal, unsigned char ImgFormat, unsigned int uiPartialRot, int refStartPos, 
					                   unsigned int uiBlkSize)
{
	int iDataformat, iRotateType;
	switch(ImgFormat)
	{
	case YUV420:
		iDataformat = FORMAT_YUV420;
		break;
	case YUV422:
		iDataformat = FORMAT_YUV422;
		break;
	default:
		return 1;
	}
	/*	the rotation is different form tcc78x	clockwise in tcc79x, counter-clockwise in tcc78x	*/
	switch(iRotVal)
	{
	case DMA2D_NO_OPERATION:
		iRotateType = CH_DATACOPY;
		break;
	case DMA2D_ROTATE_90_DEGREES:
		iRotateType = CH_ROT270;
		break;
	case DMA2D_ROTATE_180_DEGREES:
		iRotateType = CH_ROT180;
		break;
	case DMA2D_ROTATE_270_DEGREES:  
		iRotateType = CH_ROT90;
		break;
	case DMA2D_ROTATE_FLIP_VERTICAL:
		iRotateType = CH_VMIRROR; 
		break;
	case DMA2D_ROTATE_FLIP_HORIZON:
		iRotateType = CH_HMIRROR;
		break;
	case DMA2D_ROTATE_FLIP_ALL:
		iRotateType = CH_VHMIRROR; 
		break;
	}
	if (uiPartialRot == PARTIAL_ROT || pOverlayMixer==NULL)
	{
		return 1;
	}
	else 
	{	
#ifdef __2DACCELATE_CHECK__
		while((pOverlayMixer->FCH2_SADDR0 != 0xFF00))
		{
			printf("pOverlayMixer->FCH2_SADDR00 : 0x%X - 0x%X\r\n", &(pOverlayMixer->FCH2_SADDR0) , pOverlayMixer->FCH2_SADDR0);
			::Sleep(0);
		}
		pOverlayMixer->FCH2_SADDR0 = 0x8F00;
#endif
		pOverlayMixer->FCH0_SADDR0 = ((unsigned int)(pSrcBaseY));
		pOverlayMixer->FCH0_SADDR1 = ((unsigned int)(pSrcBaseU));
		pOverlayMixer->FCH0_SADDR2 = ((unsigned int)(pSrcBaseV));
		pOverlayMixer->FCH0_SFSIZE = (SrcVsize<<16)|SrcHsize; 
		pOverlayMixer->FCH0_SISIZE = (SrcVsize<<16)|SrcHsize; 
		pOverlayMixer->FCH0_SOFF = (0<<16)|0;
		pOverlayMixer->FCH0_WOFF = (0<<16)|0;
		pOverlayMixer->FCH0_SCTRL = 0;
		pOverlayMixer->FCH0_SCTRL = (CH_DATACOPY<<8)|(ZF_ZEROFILL<<5)|(iDataformat);

		pOverlayMixer->S0_CHROMA = 0;
		pOverlayMixer->S0_PAR = 0;
		pOverlayMixer->S1_CHROMA = 0;
		pOverlayMixer->S1_PAR = 0;		
		pOverlayMixer->S_CTRL = 0;
		pOverlayMixer->S_CTRL = (ARITH_BYPASS<<19)|(SOURCE_Y2R_DISABLE<<17)|(SOURCE_Y2R_DISABLE<<16)|
			(SOURCE_Y2RCON_TYPE0<11)|(SOURCE_Y2RCON_TYPE0<<9)|
			(SOURCE_CHROMA_DISABLE<<7)|(SOURCE_CHROMA_DISABLE<<6)|			
			(SOURCE_DISABLE<<2)|(SOURCE_FECH0);

		pOverlayMixer->OP0_PAT = 0;
		pOverlayMixer->OP_CTRL = 0;
		pOverlayMixer->OP_CTRL = (OPMODE_SCOPY<<16) |(CHROMA_DISABLE<<5) |(OPMODE_SCOPY);

		pOverlayMixer->BCH_DADDR0 = ((unsigned int)(pDstBaseY));
		pOverlayMixer->BCH_DADDR1 = ((unsigned int)(pDstBaseU));
		pOverlayMixer->BCH_DADDR2 = ((unsigned int)(pDstBaseV));
		pOverlayMixer->BCH_DFSIZE= (DstVsize<<16)|DstHsize; 
		pOverlayMixer->BCH_DOFF = (0<<16)|0;
		pOverlayMixer->BCH_DCTRL = 0;
		pOverlayMixer->BCH_DCTRL = (BCH_R2Y_DISABLE<<15) | (BCH_R2YCON_TYPE0<13) | (iRotateType<<8) | (iDataformat);

		//pGEREG->OM_IREQ = 0; 
		pOverlayMixer->OM_CTRL = 0;
		pOverlayMixer->OM_CTRL  = (GE_INT_DISABLE<<16)|GE_ENABLE_FCH0; // start GE - Ch0 enable			

		while(!(pOverlayMixer->OM_IREQ& Hw16)) // Polling
		{
			Sleep(0);
		}
		pOverlayMixer->OM_IREQ = (Hw16|Hw0);
#ifdef __2DACCELATE_CHECK__
		pOverlayMixer->FCH2_SADDR0 = 0xFF00;
#endif
	}		
	return 0;
}

unsigned int CImageRender::RGBtoYUV(unsigned char *pSrcBase, unsigned char SrcFormat,
								unsigned int SrcHsize, unsigned int SrcVsize,
								unsigned char *pDstBase, unsigned char DstFormat)

{
	if(pOverlayMixer==NULL)
		return 1;

#ifdef __2DACCELATE_CHECK__
	while((pOverlayMixer->FCH2_SADDR0 != 0xFF00))
	{
		printf("pOverlayMixer->FCH2_SADDR01 : 0x%X\r\n", pOverlayMixer->FCH2_SADDR0);
		::Sleep(0);
	}
	pOverlayMixer->FCH2_SADDR0 = 0x8F00;
#endif	
	pOverlayMixer->FCH0_SADDR0 = ((unsigned int)(pSrcBase));
	pOverlayMixer->FCH0_SADDR1 = 0;
	pOverlayMixer->FCH0_SADDR2 = 0;
	pOverlayMixer->FCH0_SFSIZE = (SrcVsize<<16)|SrcHsize; 
	pOverlayMixer->FCH0_SISIZE = (SrcVsize<<16)|SrcHsize; 
	pOverlayMixer->FCH0_SOFF = (0<<16)|0;
	pOverlayMixer->FCH0_WOFF = (0<<16)|0;
	pOverlayMixer->FCH0_SCTRL = 0;
	pOverlayMixer->FCH0_SCTRL = (CH_DATACOPY<<8)|(ZF_ZEROFILL<<5)|(SrcFormat);

	pOverlayMixer->S0_CHROMA = 0;
	pOverlayMixer->S0_PAR = 0;
	pOverlayMixer->S1_CHROMA = 0;
	pOverlayMixer->S1_PAR = 0;		
	pOverlayMixer->S_CTRL = 0;
	pOverlayMixer->S_CTRL = (ARITH_BYPASS<<19)|(SOURCE_Y2R_DISABLE<<17)|(SOURCE_Y2R_DISABLE<<16)|
			(SOURCE_Y2RCON_TYPE0<11)|(SOURCE_Y2RCON_TYPE0<<9)|
			(SOURCE_CHROMA_DISABLE<<7)|(SOURCE_CHROMA_DISABLE<<6)|			
			(SOURCE_DISABLE<<2)|(SOURCE_FECH0);

	pOverlayMixer->OP0_PAT = 0;
	pOverlayMixer->OP_CTRL = 0;
	pOverlayMixer->OP_CTRL = (OPMODE_SCOPY<<16) |(CHROMA_DISABLE<<5) |(OPMODE_SCOPY);

	// for YUV 420;
	pOverlayMixer->BCH_DADDR0 = ((unsigned int)(pDstBase));
	pOverlayMixer->BCH_DADDR1 = ((unsigned int)(pDstBase + SrcHsize * SrcVsize));
	pOverlayMixer->BCH_DADDR2 = ((unsigned int)(pDstBase + SrcHsize * SrcVsize + (SrcHsize * SrcVsize)/4));
	pOverlayMixer->BCH_DFSIZE= (SrcVsize<<16)|SrcHsize; 
	pOverlayMixer->BCH_DOFF = (0<<16)|0;
	pOverlayMixer->BCH_DCTRL = 0;
	pOverlayMixer->BCH_DCTRL = (BCH_R2Y_ENABLE<<15) | (BCH_R2YCON_TYPE0<13) | (DstFormat);

	//pGEREG->OM_IREQ = 0; 
	pOverlayMixer->OM_CTRL = 0;
	pOverlayMixer->OM_CTRL  = (GE_INT_DISABLE<<16)|GE_ENABLE_FCH0; // start GE - Ch0 enable			

	while(!(pOverlayMixer->OM_IREQ& Hw16)) // Polling
	{
		Sleep(0);
	}
	pOverlayMixer->OM_IREQ = (Hw16|Hw0);

#ifdef __2DACCELATE_CHECK__
	pOverlayMixer->FCH2_SADDR0 = 0xFF00;
#endif

	return 0;
}

void CImageRender::DisplayVideoChannel(BOOL bSetting)
{
#if 1
	///////////////////////////////////////////////////////////////////////////////////

	unsigned char* m_pVirScalerAddress = (unsigned char*)SetVirtual(m_pScalerAddress, m_nScreenWidth*m_nScreenHeight*3/2);
	{
		memset(m_pVirScalerAddress, 0, m_nScreenWidth*m_nScreenHeight);
		memset(m_pVirScalerAddress + m_nScreenWidth*m_nScreenHeight, 0x80, (m_nScreenWidth*m_nScreenHeight)>>1);
	}

	FreeVirtual(m_pVirScalerAddress, m_nScreenWidth*m_nScreenHeight*3/2);

	unsigned char* m_pVirRotateAddresss = (unsigned char*)SetVirtual(m_pRotateAddress, m_nScreenWidth*m_nScreenHeight*3/2);
	{
		memset(m_pVirRotateAddresss, 0, m_nScreenWidth*m_nScreenHeight);
		memset(m_pVirRotateAddresss + m_nScreenWidth*m_nScreenHeight, 0x80, (m_nScreenWidth*m_nScreenHeight)>>1);
	}

	FreeVirtual(m_pVirRotateAddresss, m_nScreenWidth*m_nScreenHeight*3/2);

	unsigned char* m_pVirConvertAddress = (unsigned char*)SetVirtual(m_pConvertAddress, m_nScreenWidth*m_nScreenHeight*2);
	{
		memset(m_pVirConvertAddress, 0, m_nScreenWidth*m_nScreenHeight*2);
	}

	FreeVirtual(m_pVirConvertAddress, m_nScreenWidth*m_nScreenHeight*2);

	unsigned char* m_pVirVideoStartMem = (unsigned char*)SetVirtual(m_pVideoStartMem, m_nScreenWidth*m_nScreenHeight*3/2);
	{
		memset(m_pVirVideoStartMem, 0, m_nScreenWidth*m_nScreenHeight);
		memset(m_pVirVideoStartMem + m_nScreenWidth*m_nScreenHeight, 0x80, (m_nScreenWidth*m_nScreenHeight)>>1);
	}

	FreeVirtual(m_pVirVideoStartMem, m_nScreenWidth*m_nScreenHeight*3/2);

	///////////////////////////////////////////////////////////////////////////////////
	if(m_Mode!=1) // chromakey setting
		return ; 
#if 0
	if(bSetting)
	{
		pLcdINF->LI0C = HwLI0C_IEN |HwLI0C_Y2R |HwLI0C_FMT_YUV420SEP;
	}
	else
	{
		pLcdINF->LI0C &=~HwLI0C_AEN;
		pLcdINF->LI0C &=~HwLI0C_CEN;
		pLcdINF->LI0C &=~HwLI0C_IEN;
	}
#else
	pLcdINF->LI0BA0 = m_pRotateAddress;	// base output address	(Y)
	pLcdINF->LI0S= (m_nScreenWidth<<16) | (m_nScreenHeight); 
	pLcdINF->LI0O = ((m_nScreenHeight>>1)<<16) | (m_nScreenHeight); // Offset
	pLcdINF->LI0P  = (0<<16)     | (0); // position
	pLcdINF->LI0BA1 = pLcdINF->LI0BA0 + m_nScreenWidth*m_nScreenHeight; // base output U address
	pLcdINF->LI0BA2 = pLcdINF->LI0BA1 + (m_nScreenWidth*m_nScreenHeight)/4; // base output V address

	unsigned int nRegTemp;
	
	nRegTemp = pLcdINF->LCTRL & 0xFFFFFFF0;
	nRegTemp |= HwLCTRL_LEN_ENABLE| HwLCTRL_OVP_IMG210 ;
	pLcdINF->LCTRL= nRegTemp;

	pLcdINF->LBC=0x80000000;
	pLcdINF->LI1KR = (0xFF<<16)|((xCHValue&0xFF0000)>>16);
	pLcdINF->LI1KG = (0xFF<<16)|((xCHValue&0x00FF00)>>8);
	pLcdINF->LI1KB = (0xFF<<16)|((xCHValue&0x0000FF));
	pLcdINF->LI1C &=~HwLI0C_CEN;
	pLcdINF->LI1C |=HwLI0C_CEN;
	pLcdINF->LI0C = HwLI0C_IEN |HwLI0C_Y2R |HwLI0C_FMT_YUV420SEP;	

#endif
#endif
}
#endif
