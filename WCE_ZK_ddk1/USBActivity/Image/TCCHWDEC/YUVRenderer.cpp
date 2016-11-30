#ifdef __TCC79XX_WINCE__

#include "..\stdafx.h"
#include "YUVRenderer.h"
#include "Common/debug.h"
#include "Common/Virtual.h"

#include "Common/TCC79x_Physical.h"
#include "Common/TCC79x_Structures.h"

#include "Common/TCCUtil.h"

const unsigned int xCHValue = 0x100010; // chromakey value : R:16 G:0 B:16

CYUVRenderer::CYUVRenderer(const int LcdWidth, const int LcdHeight) 
:mMode(1)
,mpLcdReg(NULL)
,mLcdWidth(LcdWidth)	
,mLcdHeight(LcdHeight)
,pGEREG(NULL)
{
	VirtualAlloc_Init();
	mLcdReg_Bak26 = *(mpLcdReg + 26);
	mLcdReg_Bak0 = *(mpLcdReg);
}

CYUVRenderer::~CYUVRenderer()
{
	*(mpLcdReg) = mLcdReg_Bak0;
	*(mpLcdReg + 26) = mLcdReg_Bak26;
	VirtualAlloc_Free();
}

/**
 * render YUV420 image to LCD0 
 *
 * @Param _srcInfo			the information of source image 
 * @Param _srcRenderRect	the source rect to render (padded by 16)
 * @Param _destRect			the destination rect to render (padded by 16)
 */
void CYUVRenderer::Render(const yrIMG_INFO& _srcInfo, const yrRECT& _srcRenderRect, 
						  const yrRECT& _destRect)
{
	yrRECT srcRenderRect = _srcRenderRect;
	yrRECT destRect = _destRect; 

	// should be multiple of 8
	srcRenderRect.left = (_srcRenderRect.left>>3)<<3;
	srcRenderRect.right = (_srcRenderRect.right>>3)<<3;

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
	
	mRect = destRect;
	WriteFrame(_srcInfo.phyAddr, _srcInfo.paddedSize, srcRenderRect, 1, 0);
}

void CYUVRenderer::GetStatusValue(BOOL bJPGSetRotate,int iJPGAngle)
{
	bHWJPGSetRotate = bJPGSetRotate;
	iHWJPGAngle		= iJPGAngle;
}

void CYUVRenderer::IsEffectRender(BOOL bEffectRender)
{
	bIsEffectRender = bEffectRender;
}

void CYUVRenderer::GetChromakeyColor(int& r, int& g, int& b)
{
	r = 0x10;
	g = 0x00;
	b = 0x10;
}

int CYUVRenderer::VirtualAlloc_Init(void)
{
	mMsc = (MSC_REG*)SetVirtual( 0xF0070000, sizeof(MSC_REG));
	if( mMsc == NULL ) {
		return -1;
	}

	mpLcdReg = (unsigned int*)SetVirtual(0xF0000000, 40 * 4);
	if( mpLcdReg == NULL ) {
		return -1;
	}
#ifdef M2MSCALER_CLOCKCONTROL		
	pCKCREG = (TCC78xCKCReg*)SetVirtual( (unsigned int)&HwCLKCTRL, sizeof(TCC78xCKCReg) );
	if( pCKCREG == NULL ) {
		return -1;
	}
	BITSET(pCKCREG->BCLKCTR , HwBCLKCTR_M2MS); // M2M Scaler Bus clock enable
#endif	

#ifndef HWJPGwithSWJPG
	pCKCREG = (volatile TCC79xCKCReg*)SetVirtual((unsigned int)0xF3000000, sizeof(TCC79xCKCReg) );
	if( pCKCREG == NULL ) {
		return FALSE;
	}
	pCKCREG->SWRESET0 |= HwSWRESET_M2MS;
	pCKCREG->SWRESET0 &= ~HwSWRESET_M2MS;	
	FreeVirtual((void*)pCKCREG, sizeof(TCC79xCKCReg));
	pCKCREG=NULL;
#endif	

	pGEREG = (tGraphicEngineInterface *)SetVirtual((unsigned int)&HwGE_BASE,sizeof(tGraphicEngineInterface));
	if( pGEREG == NULL ) {
		return -1;
	}	

	HKEY    hk=NULL;
	DWORD   dwStatus;
	DWORD	dwSize,dwType;
	
	m_pScalerAddress = SCALER_TCC79X_OUT1; // Default TCC79x Phyiscal Memory Address for SCALER1
	dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Drivers\\TCC79X\\CONFIG", 0, 0, &hk);

	dwType   = REG_DWORD;
	if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	{
		dwSize = sizeof(DWORD);
		dwStatus = RegQueryValueEx(hk, _T("LCD_Width"), NULL, &dwType, (LPBYTE) &mLcdWidth, &dwSize);
	}
	if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	{
		dwSize = sizeof(DWORD);
		dwStatus = RegQueryValueEx(hk, _T("LCD_Height"), NULL, &dwType, (LPBYTE) &mLcdHeight, &dwSize);
	}

	DWORD dwStartAddrScaler;
	if(dwStatus == ERROR_SUCCESS && dwType == REG_DWORD) 
	{
		dwSize = sizeof(DWORD);
		dwStatus = RegQueryValueEx(hk, _T("VIDEO_MEM_SCALER"), NULL, &dwType, (LPBYTE) &dwStartAddrScaler, &dwSize);
	}
	m_pScalerAddress = dwStartAddrScaler;

	if(hk != NULL) 
	{
		RegCloseKey(hk);
	}
	return 1;
}

void CYUVRenderer::VirtualAlloc_Free(void)
{
    FreeVirtual((void*)mMsc, sizeof(MSC_REG));
	FreeVirtual((void*)mpLcdReg, 40 * 4);
	mpLcdReg = NULL;
#ifdef M2MSCALER_CLOCKCONTROL	
	if(pCKCREG) { 
		BITCLR(pCKCREG->BCLKCTR , HwBCLKCTR_M2MS); //M2M Scaler Bus clock Disable
		FreeVirtual( (void*)pCKCREG, sizeof(pCKCREG) ); pCKCREG = NULL; }	
#endif

	if(pGEREG)
	{
		pGEREG->GE_IREQ = (HwGE_IREQ_FLAG|HwGE_IREQ_IRQ);
		pGEREG->GE_CTRL = 0;
		FreeVirtual((void*)pGEREG, sizeof(tGraphicEngineInterface)); 
		pGEREG=NULL;
	}
}

void CYUVRenderer::TCC_VideoScale (
		U8 *pSrcBase, U16 nSrcWidth, U16 nSrcHeight, const yrRECT& srcRenderRect, U8 nSrcType, U32 nSrcOffsetY, 
		U8 *pDstBase, U16 nDstWidth, U16 nDstHeight, const yrRECT& dstRenderRect, U8 nDstType, U32 nDstOffsetY,
		volatile MSC_REG *mMsc
		,U8 nHeightOffset // garbage lines due to 16bit alignment output
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

	while ( (mMsc->MSCSTR & HwMSCSTR_RDY) != HwMSCSTR_RDY ) 
	{
		Sleep(0); 	// do nothing
	}
	nScaleH = nSrcRenderWidth * 256 / nDstWidth;
	nScaleV = (nSrcRenderHeight-nHeightOffset) * 256 / nDstHeight;

	nSrcOffsetC = nSrcOffsetY / 2;
	nDstOffsetC = nDstOffsetY / 2;

	nSrcFrameWidth = nSrcOffsetY;
	nDstFrameWidth = nDstOffsetY;

	const int offsetToRenderSrcInLuminance = (nSrcFrameWidth*srcRenderRect.top + srcRenderRect.left);
	const int offsetToRenderSrcInChrominance = (nSrcFrameWidth>>1)*(srcRenderRect.top>>1) + (srcRenderRect.left>>1);
	mMsc->SRCBASEY = (unsigned int)(pSrcBase + offsetToRenderSrcInLuminance);
	mMsc->SRCBASEU = (unsigned int)(pSrcBase + nSrcFrameWidth * nSrcHeight + offsetToRenderSrcInChrominance);
	mMsc->SRCBASEV = mMsc->SRCBASEU + ((nSrcFrameWidth * nSrcHeight)>>2);
	
	mMsc->SRCSIZE = ((nSrcRenderHeight-nHeightOffset)<<16) | (nSrcRenderWidth<<0);
	mMsc->SRCOFF = (nSrcOffsetC<<16) | (nSrcOffsetY<<0);
	mMsc->SRCCFG = nSrcType;

	const int offsetToRenderDstInLuminance = (nDstFrameWidth*dstRenderRect.top + dstRenderRect.left);
	const int offsetToRenderDstInChrominance = (nDstFrameWidth>>1)*(dstRenderRect.top>>1) + (dstRenderRect.left>>1);
	mMsc->DSTBASEY	= (unsigned int)(pDstBase /*+ offsetToRenderDstInLuminance*/);
	mMsc->DSTBASEU = (unsigned int)(pDstBase + nDstFrameWidth * nDstHeight /*+ offsetToRenderDstInChrominance*/);
	mMsc->DSTBASEV = mMsc->DSTBASEU + ((nDstFrameWidth * nDstHeight)>>2);
	mMsc->DSTSIZE = (nDstHeight<<16) | (nDstWidth<<0);
	mMsc->DSTOFF = (nDstOffsetC<<16) | (nDstOffsetY<<0);
	mMsc->DSTCFG = nDstType;

	//Setting the Scale Factor
	mMsc->MSCINF = (nScaleV << 16) | (nScaleH << 0);
	
	//Setting the Control Register
	mMsc->MSCSTR |= HwMSCSTR_IRDY;
	mMsc->MSCCTR = HwMSCCTR_IEN_RDY | Hw0;		// IEN | EN
	mMsc->MSCCTR = HwMSCCTR_IEN_RDY;			// IEN
}

void CYUVRenderer::WriteFrame(unsigned int srcPhyAddr, const yrSIZE& srcSize, const yrRECT& srcRenderRect, 
							  int nType, int nHeightOffset)
{
	U32	nBaseY;
	U32	nDstBaseY;
	U32	nDstSizeH, nDstSizeV;
	U32 nWndSizeH,nWndSizeV;
	U32 nTop,nLeft;
	U32	nRegTemp;

	unsigned int Rotate_DstSize_X;
	unsigned int Rotate_DstSize_Y;

	nWndSizeH = mRect.right - mRect.left;
	nWndSizeV = mRect.bottom - mRect.top;
	nDstSizeH = (nWndSizeH>>3)<<3; 
	nDstSizeV = (nWndSizeV>>3)<<3;
//	nDstSizeV = (nWndSizeV>>2)<<2;

	//printf("***************** WriteFrame (%d)*****************\r\n", iHWJPGAngle);
	//printf("\t line(%d) mRect(%d,%d,%d,%d)\n", __LINE__, mRect.left, mRect.top, mRect.right, mRect.bottom);
	//printf("\t line(%d) nWndSizeH : %d, nWndSizeV : %d, nDstSizeH : %d, nDstSizeV : %d\r\n", __LINE__, nWndSizeH, nWndSizeV, nDstSizeH, nDstSizeV);

	if((iHWJPGAngle == DMA2D_ROTATE_90_DEGREES)||(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES))
	{
		nTop=mRect.top;
		nLeft=mRect.left;

		if ( (nTop+nDstSizeV) > static_cast<unsigned int>(mLcdHeight))
		{
			nTop =0;
		}
		if ( (nLeft+nDstSizeH) > static_cast<unsigned int>(mLcdWidth))
		{
			nLeft =0;
		}
	}
	else
	{
		if ( nDstSizeH > static_cast<unsigned int>(mLcdWidth)||nDstSizeH==0 ) 
		{
			nDstSizeH = mLcdWidth;
		}
		if ( nDstSizeV > static_cast<unsigned int>(mLcdHeight)||nDstSizeV==0 )
		{
			nDstSizeV = mLcdHeight;
		}
		nTop=mRect.top;
		nLeft=mRect.left;

		if ( (nTop+nDstSizeV) > static_cast<unsigned int>(mLcdHeight))
		{
			nTop =0;
		}
		if ( (nLeft+nDstSizeH) > static_cast<unsigned int>(mLcdWidth))
		{
			nLeft =0;
		}
	}

	nBaseY	= (U32) srcPhyAddr;
	nDstBaseY	=  m_pScalerAddress;

	//if(mLcdWidth > 640)	// 800x480 Only
	//	nDstBaseY	=  0x23B00000;
	#if 0
	printf("\r\n[1. WriteFrame]\r\n");
	printf("\tnBaseY = 0x%X\r\n", nBaseY);
	printf("\tsrcSize.cx = %d\r\n", srcSize.cx);
	printf("\tsrcSize.cy = %d\r\n", srcSize.cy);
	printf("\tnType = %d\r\n", nType);
	printf("\tsrcRenderRect(left = %d, top = %d, right = %d, bottom = %d\r\n", srcRenderRect.left, srcRenderRect.top, srcRenderRect.right, srcRenderRect.bottom);
	printf("\tnDstBaseY = 0x%X\r\n", nDstBaseY);
	printf("\tnDstSizeH = %d\r\n", nDstSizeH);
	printf("\tnDstSizeV = %d\r\n", nDstSizeV);
	printf("\tmRect(left = %d, top = %d, right = %d, bottom = %d\r\n", mRect.left, mRect.top, mRect.right, mRect.bottom);
	printf("\tnHeightOffset = %d\r\n", nHeightOffset);
	#endif
	
	if(!bIsEffectRender)
	{
	TCC_VideoScale (
		(U8 *)nBaseY, 
		(U16)srcSize.cx, 
		(U16)srcSize.cy/nType,
		srcRenderRect,
		3,  // 4:2:0 separate mode
		(U16)srcSize.cx*nType,  //type mpeg2 is 2, h264 is 1
		(unsigned char*)nDstBaseY,
		nDstSizeH,
		nDstSizeV,
		mRect,
		3,  // 4:2:0 separate mode
		nDstSizeH,
		mMsc
		,(U8)nHeightOffset // garbage lines due to 16bit alignment output
		);
	}

	if(bHWJPGSetRotate)
	{
		while ( (mMsc->MSCSTR & HwMSCSTR_RDY) != HwMSCSTR_RDY ) 
		{
			Sleep(0); 	// check scaler routine
		}

		RotateImage((U8 *)nDstBaseY,nDstSizeH,nDstSizeV,iHWJPGAngle);

		
		if(iHWJPGAngle == DMA2D_ROTATE_90_DEGREES ||iHWJPGAngle ==DMA2D_ROTATE_270_DEGREES)
		{
			nTop=(mLcdHeight-nDstSizeH)/2;
			nLeft=(mLcdWidth-nDstSizeV)/2;

			if ( (nTop+nDstSizeH) > static_cast<unsigned int>(mLcdHeight))
			{
				nTop =0;
			}
			if ( (nLeft+nDstSizeV) > static_cast<unsigned int>(mLcdWidth))
			{
				nLeft =0;
			}

//////////////////////
			// Rotate output->Scaler input
			unsigned int Rotate_SrcBaseY = m_pRotateAddress;
			unsigned int Rotate_SrcSize_X = nDstSizeV;
			unsigned int Rotate_SrcSize_Y = nDstSizeH;
			yrRECT Rotate_SrcRect;
			Rotate_SrcRect.left = 0;
			Rotate_SrcRect.right = 0 +  Rotate_SrcSize_X;
			Rotate_SrcRect.top = 0;
			Rotate_SrcRect.bottom = 0 + Rotate_SrcSize_Y;
			

			// Scaler output setting			
			// remodeling of CalcDestinationRenderRect() 
			yrRECT Rotate_DstRect;
			Rotate_DstRect.left = 0;
			Rotate_DstRect.right = min((int)(Rotate_DstRect.left + Rotate_SrcSize_X), mLcdWidth);
			Rotate_DstRect.top = 0;
			Rotate_DstRect.bottom = min((int)(Rotate_DstRect.top + Rotate_SrcSize_Y), mLcdHeight);

			// Rotate Image-> Scaling output address
			unsigned int Rotate_DstBaseY = m_pRotateAddress + 0x80000 ;//nDstBaseY;
			
			Rotate_DstSize_X = Rotate_DstRect.right - Rotate_DstRect.left;
			Rotate_DstSize_Y = Rotate_DstRect.bottom - Rotate_DstRect.top;

			*(mpLcdReg + 29) = m_pRotateAddress;	// base output address	(Y)
//////////////////////
			*(mpLcdReg + 28) = (Rotate_DstSize_Y<<16) | (Rotate_DstSize_X);
		}
		else
		{
			*(mpLcdReg + 28) = (nDstSizeV<<16) | (nDstSizeH); 
			*(mpLcdReg + 29) = m_pRotateAddress; // base output address	(Y)
		}
	}
	else
	{
		*(mpLcdReg + 28) = (nDstSizeV<<16) | (nDstSizeH); // size
		if(bIsEffectRender)
		{
			*(mpLcdReg + 29) = 	nBaseY;
		}
		else
		{
			*(mpLcdReg + 29) = nDstBaseY;	// base output address	(Y)
		}
	}

    
	if(bHWJPGSetRotate)
	{
		if(iHWJPGAngle == DMA2D_ROTATE_90_DEGREES ||iHWJPGAngle ==DMA2D_ROTATE_270_DEGREES)
		{
			*(mpLcdReg + 27) = (nTop <<16)     | (nLeft); // position
			*(mpLcdReg + 31) = *(mpLcdReg + 29) + Rotate_DstSize_X*Rotate_DstSize_Y ; //(U)
			*(mpLcdReg + 32) = *(mpLcdReg + 31) + (Rotate_DstSize_X*Rotate_DstSize_Y)/4;//(V)
		}
		else
		{
			*(mpLcdReg + 27) = (nTop <<16)     | (nLeft); // position
			*(mpLcdReg + 31) = *(mpLcdReg + 29) + nDstSizeH*nDstSizeV ; //(U)
			*(mpLcdReg + 32) = *(mpLcdReg + 31) + nDstSizeH*nDstSizeV/4;//(V)
		}
	}
	else
	{
		*(mpLcdReg + 27) = (nTop <<16)     | (nLeft); // position
		*(mpLcdReg + 31) = *(mpLcdReg + 29) + nDstSizeH*nDstSizeV ; //(U)
		*(mpLcdReg + 32) = *(mpLcdReg + 31) + nDstSizeH*nDstSizeV/4;//(V)
	} 
	
	if(mMode==2) // alpha blending 25%
	{
		printf("CYUVRenderer::WriteFrame[alpha blending 25% settting]\r\n");
		*(mpLcdReg + 26)  = HwLI0C_IMG210|HwLI0C_YUV_420|HwLI0C_BPP_332;  //or YUV
		*(mpLcdReg + 19)  = 0x01000000;	// Alpha value for Channel 1 : 25%

		nRegTemp          = *(mpLcdReg) & 0x03FFFFF0;
		nRegTemp         |= HwLCTRL_LEN_EN |	//[ 0] LCD Controller Enable						0x0A556147 |
						//	HwLCTRL_Y2R2_EN|	//[31] YUV to RGB Channel Converter Enable 2
						//	HwLCTRL_AEN2_EN|	//[30] Alpha Blend Enable 2
						//	HwLCTRL_CEN2_EN|	//[29] Chroma Key Enable 2
						//	HwLCTRL_Y2R1_EN|	//[28] YUV to RGB Channel Converter Enable 1
							HwLCTRL_AEN1_EN|	//[27] Alpha Blend Enable 1
						//	HwLCTRL_CEN1_EN|	//[26] Chroma Key Enable 1
							HwLCTRL_Y2R0_EN|	//[25] YUV to RGB Channel Converter Enable 0
						//	HwLCTRL_IEN2_EN|	//[ 3] Fetch Enable 2
							HwLCTRL_IEN1_EN|	//[ 2] Fetch Enable 1
							HwLCTRL_IEN0_EN|	//[ 1] Fetch Enable 0
							0;		
		*(mpLcdReg) = nRegTemp;
	}
	else if(mMode==1) // chromakey setting
	{
		//printf("CYUVRenderer::WriteFrame[chromakey settting]\r\n");
		*(mpLcdReg + 26)  = HwLI0C_IMG210|HwLI0C_YUV_420|HwLI0C_BPP_332; //or YUV
		*(mpLcdReg + 19) |= xCHValue;//Chroma key value setting 16,0,16
		*(mpLcdReg + 21)  = 0x00; //reset
		*(mpLcdReg + 21) |= 0xFFFFFF;//Chroma key value setting 16,0,16
		nRegTemp          = *(mpLcdReg) & 0x03FFFFF0;
		nRegTemp         |= HwLCTRL_LEN_EN |	//[ 0] LCD Controller Enable						0x0A556147 |
						//	HwLCTRL_Y2R2_EN|	//[31] YUV to RGB Channel Converter Enable 2
						//	HwLCTRL_AEN2_EN|	//[30] Alpha Blend Enable 2
						//	HwLCTRL_CEN2_EN|	//[29] Chroma Key Enable 2
						//	HwLCTRL_Y2R1_EN|	//[28] YUV to RGB Channel Converter Enable 1
						//	HwLCTRL_AEN1_EN|	//[27] Alpha Blend Enable 1
							HwLCTRL_CEN1_EN|	//[26] Chroma Key Enable 1
							HwLCTRL_Y2R0_EN|	//[25] YUV to RGB Channel Converter Enable 0
						//	HwLCTRL_IEN2_EN|	//[ 3] Fetch Enable 2
							HwLCTRL_IEN1_EN|	//[ 2] Fetch Enable 1
							HwLCTRL_IEN0_EN|	//[ 1] Fetch Enable 0
							0;		
		*(mpLcdReg) = nRegTemp;
	}
	else if(mMode==3) // chromakey & alpha blending setting
	{
		printf("CYUVRenderer::WriteFrame[chromakey & alpha blending setting]\r\n");
   		*(mpLcdReg + 26) = HwLI0C_IMG210|HwLI0C_YUV_420|HwLI0C_BPP_332;
		*(mpLcdReg + 19) |= xCHValue;//Chroma key value setting 16,0,16
		*(mpLcdReg + 19) |= 3<<24;   // alphablend 0(0%),1(25)%,2(50%),3(75%)
		*(mpLcdReg + 21)  = 0x00; //reset
		*(mpLcdReg + 21) |= 0xFFFFFF;//Chroma key value setting 16,0,16
		nRegTemp          = *(mpLcdReg) & 0x03FFFFF0;
		nRegTemp         |= HwLCTRL_LEN_EN |	//[ 0] LCD Controller Enable						0x0A556147 |
						//	HwLCTRL_Y2R2_EN|	//[31] YUV to RGB Channel Converter Enable 2
						//	HwLCTRL_AEN2_EN|	//[30] Alpha Blend Enable 2
						//	HwLCTRL_CEN2_EN|	//[29] Chroma Key Enable 2
						//	HwLCTRL_Y2R1_EN|	//[28] YUV to RGB Channel Converter Enable 1
							HwLCTRL_AEN1_EN|	//[27] Alpha Blend Enable 1
							HwLCTRL_CEN1_EN|	//[26] Chroma Key Enable 1
							HwLCTRL_Y2R0_EN|	//[25] YUV to RGB Channel Converter Enable 0
						//	HwLCTRL_IEN2_EN|	//[ 3] Fetch Enable 2
							HwLCTRL_IEN1_EN|	//[ 2] Fetch Enable 1
							HwLCTRL_IEN0_EN|	//[ 1] Fetch Enable 0
							0;		
		*(mpLcdReg) = nRegTemp;
	}	
	else  // default     (no alpha blending & no  chromakey)
	{
		printf("CYUVRenderer::WriteFrame[default setting]\r\n");
		*(mpLcdReg + 26)  = HwLI0C_YUV_420|HwLI0C_BPP_332; //or YUV
		*(mpLcdReg + 19)  = 0x03000000;	
		nRegTemp          = *(mpLcdReg) & 0x03FFFFF0;
		nRegTemp         |= HwLCTRL_LEN_EN |	//[ 0] LCD Controller Enable						0x0A556147 |
						//	HwLCTRL_Y2R2_EN|	//[31] YUV to RGB Channel Converter Enable 2
						//	HwLCTRL_AEN2_EN|	//[30] Alpha Blend Enable 2
						//	HwLCTRL_CEN2_EN|	//[29] Chroma Key Enable 2
						//	HwLCTRL_Y2R1_EN|	//[28] YUV to RGB Channel Converter Enable 1
						//	HwLCTRL_AEN1_EN|	//[27] Alpha Blend Enable 1
						//	HwLCTRL_CEN1_EN|	//[26] Chroma Key Enable 1
							HwLCTRL_Y2R0_EN|	//[25] YUV to RGB Channel Converter Enable 0
						//	HwLCTRL_IEN2_EN|	//[ 3] Fetch Enable 2
						//	HwLCTRL_IEN1_EN|	//[ 2] Fetch Enable 1
							HwLCTRL_IEN0_EN|	//[ 1] Fetch Enable 0
							0;
		*(mpLcdReg) = nRegTemp;
	}
	
}


void CYUVRenderer::RotateImage(U8 *nSrcBaseY, unsigned int  nSrcWidth, unsigned int  nSrcHeight, int iHWJPGAngle) 
{
//	printf("\r\n[2.RotateImage] Rotateprocess ------nSrcWidth = %d     nSrcHeight = %d------ \r\n",nSrcWidth,nSrcHeight);
    m_pRotateAddress = m_pScalerAddress - 0x00100000;//Ju :ROTATE_BUFFER;
//    printf("\r\n[2.RotateImage] [m_pScalerAddress] : 0x%08x\n ",m_pScalerAddress);
//    printf("\r\n[2.RotateImage] [m_pRotateAddress] : 0x%08x\n ",m_pRotateAddress);

	TCC_ImageRotate(
		(U8 *)nSrcBaseY, 
		(U8 *)m_pRotateAddress,
		nSrcWidth,			
		nSrcHeight,	
		iHWJPGAngle,
		YUV420
	);
}


int CYUVRenderer::TCC_ImageRotate(U8 *pSrource, U8 *pDestination, unsigned int  nSrcWidth, unsigned int  nSrcHeight,unsigned int  nRotateType, unsigned int  nImgType) 
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

unsigned int CYUVRenderer::TCCAPI_2DDMA_Rotate(unsigned char *pSrcBaseY, unsigned char *pSrcBaseU, unsigned char *pSrcBaseV,
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
	if (uiPartialRot == PARTIAL_ROT || pGEREG==NULL)
	{
		return 1;
	}
	else 
	{	
		while( pGEREG->GE_CTRL)
			::Sleep(0);

		pGEREG->FCH0_SADDR0 = ((unsigned int)(pSrcBaseY));
		pGEREG->FCH0_SADDR1 = ((unsigned int)(pSrcBaseU));
		pGEREG->FCH0_SADDR2 = ((unsigned int)(pSrcBaseV));
		pGEREG->FCH0_SFSIZE = (SrcVsize<<16)|SrcHsize; 
		pGEREG->FCH0_SISIZE = (SrcVsize<<16)|SrcHsize; 
		pGEREG->FCH0_SOFF = (0<<16)|0;
		pGEREG->FCH0_WOFF = (0<<16)|0;
		pGEREG->FCH0_SCTRL = 0;
		pGEREG->FCH0_SCTRL = (CH_DATACOPY<<8)|(ZF_ZEROFILL<<5)|(iDataformat);

		pGEREG->S0_CHROMA = 0;
		pGEREG->S0_PARAM = 0;
		pGEREG->S1_CHROMA = 0;
		pGEREG->S1_PARAM = 0;		
		pGEREG->S_CTRL = 0;
		pGEREG->S_CTRL = (ARITH_BYPASS<<19)|(SOURCE_Y2R_DISABLE<<17)|(SOURCE_Y2R_DISABLE<<16)|
			(SOURCE_Y2RCON_TYPE0<11)|(SOURCE_Y2RCON_TYPE0<<9)|
			(SOURCE_CHROMA_DISABLE<<7)|(SOURCE_CHROMA_DISABLE<<6)|			
			(SOURCE_DISABLE<<2)|(SOURCE_FECH0);

		pGEREG->OP0_PAT = 0;
		pGEREG->OP_CTRL = 0;
		pGEREG->OP_CTRL = (OPMODE_SCOPY<<16) |(CHROMA_DISABLE<<5) |(OPMODE_SCOPY);

		pGEREG->BCH_DADDR0 = ((unsigned int)(pDstBaseY));
		pGEREG->BCH_DADDR1 = ((unsigned int)(pDstBaseU));
		pGEREG->BCH_DADDR2 = ((unsigned int)(pDstBaseV));
		pGEREG->BCH_DFSIZE= (DstVsize<<16)|DstHsize; 
		pGEREG->BCH_DOFF = (0<<16)|0;
		pGEREG->BCH_DCTRL = 0;
		pGEREG->BCH_DCTRL = (BCH_R2Y_DISABLE<<15) | (BCH_R2YCON_TYPE0<13) | (iRotateType<<8) | (iDataformat);

		//pGEREG->GE_IREQ = 0; 
		pGEREG->GE_CTRL = 0;
		pGEREG->GE_CTRL  = (GE_INT_DISABLE<<16)|GE_ENABLE_FCH0; // start GE - Ch0 enable			

		while(!(pGEREG->GE_IREQ & HwGE_IREQ_FLAG)) // Polling
		{
			Sleep(0);
		}
		pGEREG->GE_IREQ = (HwGE_IREQ_FLAG|HwGE_IREQ_IRQ);
	}		
	return 0;
}

#endif