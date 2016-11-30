// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
//#include "base.h"
#include "Image.h"

#include "WINCEDEC\WinCEDecoder.h"

#ifdef __TCC79XX_WINCE__
#include "TCCHWDEC\TCCJPGHWDecode.h"
CYUVRenderer* CImageDecoder::m_pYUVRenderer = NULL;
#else

#ifdef HWJPGDEC_ENABLE
#include "common/include/clock.h"
#include "TCC89X_DEC\TCC89X_HW_JPG_Decode.h"
#endif

CImageRender* CImageDecoder::m_pYUVRenderer = NULL;
#endif
#include "TCCSWDEC\TCCJPGSWDecode.h"
#include "TCCSWDEC\TCCBMPSWDecode.h"
#include "TCCSWDEC\TCCPNGSWDecode.h"
#include "TCCSWDEC\TCCGIFSWDecode.h"


//////////////////////////////////////////////////////////////////////
// Extern value
//////////////////////////////////////////////////////////////////////
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
extern BOOL bDetectHDMI;	// When Conntect HDMI, bDetectHDMI set TRUE
#endif
#if (defined(__TCC89XX_WINCE__) && defined(HWJPGDEC_ENABLE))
extern BOOL ControlVPUClock;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage()
{
	m_CodeType = TYPE_WINCE;

	// register TCC Image decoder
#ifdef __TCC79XX_WINCE__
	#ifdef HWJPGwithSWJPG
	m_pDecoder[TYPE_TCCHWJPG] = new CTCCJpgHwDecode;
	#endif
#else
	#ifdef HWJPGDEC_ENABLE
	/////////////////////////////////////////////////
	if(TWS_CKC_GetFBUS(6)>0)
	{
		ControlVPUClock=FALSE;
	}
	else
	{
		ControlVPUClock=TRUE;
		TWS_CKC_SetFBUSForVPUOn(); //Control to TCC89x HW JPG Decoder Block Bus
	}
	//printf("ControlVPUClock=%d\r\n",ControlVPUClock);
	m_pDecoder[TYPE_TCC89HWJPG] = new CTCC89HWJPGDecode;
	#endif
#endif

	m_pDecoder[TYPE_TCCSWJPG] = new CTCCJpgSwDecode;
	m_pDecoder[TYPE_TCCSWBMP] = new CTCCBmpSwDecode;
	m_pDecoder[TYPE_TCCSWPNG] = new CTCCPngSwDecode;
	m_pDecoder[TYPE_TCCSWGIF] = new CTCCGifSwDecode;
	m_pDecoder[TYPE_WINCE] = new CCEDecoder;

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	m_ConvertPhysicalAddr = 0;
	m_ConvertVirtualAddr = NULL;
	m_YUVPhysicalAddr = 0;
	m_YUVVirtualAddr = NULL;
#endif
}

CImage::~CImage()
{
#ifdef __TCC79XX_WINCE__
	#ifdef HWJPGwithSWJPG
	SAFE_DELETE(m_pDecoder[TYPE_TCCHWJPG]);
	#endif
#else
	#ifdef HWJPGDEC_ENABLE
	SAFE_DELETE(m_pDecoder[TYPE_TCC89HWJPG]);
	#endif
#endif
	SAFE_DELETE(m_pDecoder[TYPE_TCCSWJPG]);
	SAFE_DELETE(m_pDecoder[TYPE_TCCSWBMP]);
	SAFE_DELETE(m_pDecoder[TYPE_TCCSWPNG]);
	SAFE_DELETE(m_pDecoder[TYPE_TCCSWGIF]);
	SAFE_DELETE(m_pDecoder[TYPE_WINCE]);
}

unsigned int CImage::CheckImageCodec(GUID RawDataFormat)
{
	//printf("ImageInfo RawDataFormat : 0x%08x\r\n", RawDataFormat);
	if( ImageFormatJPEG == RawDataFormat )
	{
#ifdef __TCC89XX_WINCE__
		#ifdef HWJPGDEC_ENABLE
			return TYPE_TCC89HWJPG;
		#else
			return TYPE_TCCSWJPG;
		#endif
#else
	#ifdef HWJPGwithSWJPG
//		return TYPE_TCCSWJPG;
		return TYPE_TCCHWJPG;
	#else
		return TYPE_TCCSWJPG;
	#endif
#endif
	}
	else if( ImageFormatPNG == RawDataFormat )
	{
		return TYPE_TCCSWPNG;
	}
	else if( ImageFormatBMP == RawDataFormat )
	{
		return TYPE_TCCSWBMP;
	}
	else if( ImageFormatGIF == RawDataFormat )
	{
		return TYPE_TCCSWGIF;
	}
	else
		return TYPE_WINCE;
}

void CImage::SettingSWDecoderForHDMI(unsigned int *pWidth, unsigned int *pHeight)
{
 
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	unsigned int uiWidth =m_pDecoder[TYPE_WINCE]->m_Width;
	unsigned int uiHeight=m_pDecoder[TYPE_WINCE]->m_Height;
	
	if(CImageDecoder::m_pYUVRenderer == NULL)
	{
		static CImageRender yuvRenderer(WINDOW_W, WINDOW_H);
		CImageDecoder::m_pYUVRenderer = &yuvRenderer;
	}

	HDMIDisplayOnOff(FALSE);

	if((uiWidth*uiHeight*2)>(WINDOW_W*WINDOW_H*2))
	{
		if( WINDOW_W/uiWidth > WINDOW_H/uiHeight )
		{
			uiWidth = WINDOW_H*uiWidth/uiHeight;
			uiHeight = WINDOW_H;
			if(uiWidth>WINDOW_W)
			{
				uiHeight = WINDOW_W*uiHeight/uiWidth;
				uiWidth = WINDOW_W;
			}
		}
		else
		{
			uiHeight = WINDOW_W*uiHeight/uiWidth;
			uiWidth = WINDOW_W;
			if(uiHeight>WINDOW_H)
			{
				uiWidth = WINDOW_H*uiWidth/uiHeight;
				uiHeight = WINDOW_H;
			}
		}
	}

	uiWidth = ((uiWidth+15)>>4)<<4;
	uiHeight= ((uiHeight+15)>>4)<<4;

	m_ConvertPhysicalAddr = m_pDecoder[m_CodeType]->m_pYUVRenderer->m_pConvertAddress;
	m_ConvertVirtualAddr = (unsigned char*)SetVirtual(m_ConvertPhysicalAddr, uiWidth*uiHeight*2);
	{
		memset(m_ConvertVirtualAddr, 0, uiWidth*uiHeight*2);
	}

	m_YUVPhysicalAddr = m_pDecoder[m_CodeType]->m_pYUVRenderer->m_pVideoStartMem;
	m_YUVVirtualAddr = (unsigned char*)SetVirtual(m_YUVPhysicalAddr, uiWidth*uiHeight*3/2);
	{
		//memset(m_YUVVirtualAddr, 0, uiWidth*uiHeight);
		//memset(m_YUVVirtualAddr + uiWidth*uiHeight, 0x80, (uiWidth*uiHeight)>>1);
	}
	
	m_pDecoder[m_CodeType]->m_pYUVRenderer->SetRotatedResultForSWDec(FALSE,0);
	m_pDecoder[m_CodeType]->DrawYUV420toRender(m_ConvertVirtualAddr, m_YUVVirtualAddr);

	*pWidth =uiWidth;
	*pHeight=uiHeight;
#endif
}

unsigned int CImage::PrepareImage(const WCHAR * szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	unsigned int ret;
	unsigned int pixelformat;
	GUID RawDataFormat;
	unsigned int ce_ret = m_pDecoder[TYPE_WINCE]->PrepareImage(szFileName, uiWidth, uiHeight);
	if(GetImageInfo(&uiWidth, &uiHeight, &pixelformat, &RawDataFormat))
	{
		//printf("DecCodec = %d\n",m_CodeType);
		uiWidth = m_pDecoder[TYPE_WINCE]->m_Width;
		uiHeight = m_pDecoder[TYPE_WINCE]->m_Height;
		szCurrFileName = szFileName;
		if (uiWidth <500 || uiHeight < 400)
		{
			// 小图片使用软件解码
			m_CodeType = TYPE_WINCE;
		}
		else
		{
			m_CodeType = CheckImageCodec(RawDataFormat);
			//if (m_CodeType == TYPE_TCC89HWJPG)
			//{
			//	m_CodeType = TYPE_WINCE;
			//}
			if (m_CodeType == TYPE_TCCSWBMP)
			{
				m_CodeType = TYPE_WINCE;
			}
			if (m_CodeType == TYPE_TCCSWPNG)
			{
				m_CodeType = TYPE_WINCE;
			}
		}
		//if (szFileName.Ext() == L"bmp")
		//{
		//	m_CodeType = TYPE_TCCSWBMP;
		//}
	}
	else
	{
		m_CodeType = TYPE_WINCE;
	}

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
#ifdef HWJPGDEC_ENABLE
	if( ((m_CodeType < TYPE_WINCE) && (m_CodeType>TYPE_TCC89HWJPG)) && bDetectHDMI)
#else
	if((m_CodeType < TYPE_WINCE) && bDetectHDMI)
#endif
	{
		//SettingSWDecoderForHDMI(&uiWidth, &uiHeight);
		//printf("PrepareImage::[SettingSWDecoderForHDMI]uiWidth=%d,uiHeight=%d\r\n",uiWidth,uiHeight);
		m_pDecoder[m_CodeType]->m_Width = uiWidth;
		m_pDecoder[m_CodeType]->m_Height= uiHeight;
	}
#endif
	// do not delete below code.
	// a stating physical memory adddress of renderer will be used at TCC89x hw jpg decoding.
	// so renderer should be created before TCC89x hw jpg decoding.
#ifdef __TCC89XX_WINCE__
	#ifdef HWJPGDEC_ENABLE
	if(m_CodeType == TYPE_TCC89HWJPG)
	{
		if(CImageDecoder::m_pYUVRenderer == NULL)
		{
			static CImageRender yuvRenderer(WINDOW_W, WINDOW_H);
			CImageDecoder::m_pYUVRenderer = &yuvRenderer;
		}
	}
	#endif
#endif
	if(m_CodeType < TYPE_WINCE)
	{
		//printf("[Decoder] %d among TCCDecoder\n",m_CodeType);
		if(m_pDecoder[m_CodeType])
		{
			m_pDecoder[m_CodeType]->m_Width = uiWidth;
			m_pDecoder[m_CodeType]->m_Height = uiHeight;

			ret = m_pDecoder[m_CodeType]->PrepareImage((LPCTSTR)szFileName, uiWidth, uiHeight);
			if(m_CodeType == TYPE_TCCSWGIF)
				return ce_ret;
			
			return ret;
		}
	}
	
	return ce_ret;//m_pDecoder[TYPE_WINCE]->PrepareImage((LPTSTR)szFileName.GetBuffer(szFileName.GetLength()), uiWidth, uiHeight);
}

BOOL CImage::DecodeImage(unsigned int Index)
{
	BOOL ret;
	if(m_CodeType < TYPE_WINCE)
	{
		unsigned int DecodeSize = 1;
		ret = m_pDecoder[m_CodeType]->DecodeImage(&DecodeSize, Index);
	
		// if hardware jpg decoder fail, use software jpg decoder
#ifdef __TCC89XX_WINCE__
	#ifdef HWJPGDEC_ENABLE
 		if((m_CodeType == TYPE_TCC89HWJPG) && (ret == FALSE || DecodeSize == 0) )
		{
			printf("Change DecCodec by TYPE_TCCSWJPG\n");
			m_CodeType = TYPE_TCCSWJPG;
			m_pDecoder[TYPE_TCCSWJPG]->m_Width = m_pDecoder[TYPE_TCC89HWJPG]->m_Width;
			m_pDecoder[TYPE_TCCSWJPG]->m_Height = m_pDecoder[TYPE_TCC89HWJPG]->m_Height;
			m_pDecoder[TYPE_TCC89HWJPG]->ReleaseResource();

			#ifdef __HDMI_INCLUDE__
			if( ((m_CodeType < TYPE_WINCE) && (m_CodeType>TYPE_TCC89HWJPG)) && bDetectHDMI)
			{
				unsigned int uiWidth;
				unsigned int uiHeight;

				SettingSWDecoderForHDMI(&uiWidth, &uiHeight);
				//printf("DecodeImage::[SettingSWDecoderForHDMI]uiWidth=%d,uiHeight=%d\r\n",uiWidth,uiHeight);
				m_pDecoder[m_CodeType]->m_Width = uiWidth;
				m_pDecoder[m_CodeType]->m_Height= uiHeight;
			}
			#endif

			if(m_pDecoder[TYPE_TCCSWJPG]->PrepareImage(szCurrFileName, m_pDecoder[TYPE_TCCSWJPG]->m_Width, m_pDecoder[TYPE_TCCSWJPG]->m_Height) == TRUE)
			{
			        ret = m_pDecoder[TYPE_TCCSWJPG]->DecodeImage(&DecodeSize, 0);
			}
		}
	#endif
#else
	#ifdef HWJPGwithSWJPG
		if((m_CodeType == TYPE_TCCHWJPG) && (ret == FALSE || DecodeSize == 0) )
		{
			printf("Change DecCodec by TYPE_TCCSWJPG\n");
			m_CodeType = TYPE_TCCSWJPG;
			m_pDecoder[TYPE_TCCSWJPG]->m_Width = m_pDecoder[TYPE_TCCHWJPG]->m_Width;
			m_pDecoder[TYPE_TCCSWJPG]->m_Height = m_pDecoder[TYPE_TCCHWJPG]->m_Height;
			m_pDecoder[TYPE_TCCHWJPG]->ReleaseResource();
		}
		if(m_pDecoder[TYPE_TCCSWJPG]->PrepareImage(szCurrFileName, m_pDecoder[TYPE_TCCSWJPG]->m_Width, m_pDecoder[TYPE_TCCSWJPG]->m_Height) == TRUE)
		{
	        ret = m_pDecoder[TYPE_TCCSWJPG]->DecodeImage(&DecodeSize, 0);
		}
	#endif
#endif
		
		if(ret == TRUE && DecodeSize)
		{
			m_pDecoder[m_CodeType]->EndDecode();
		}
	
		return ret;

	}
	return m_pDecoder[m_CodeType]->DecodeImage(NULL, Index);
}

BOOL CImage::CheckDrawImage()
{
	return m_pDecoder[m_CodeType]->CheckDrawImage();
}

void CImage::ClearDrawImage()
{
	m_pDecoder[m_CodeType]->ClearDrawImage();
}

unsigned int CImage::CheckDecodingCodecFormat()
{
	return m_pDecoder[m_CodeType]->CheckDecodingCodecFormat();
}

BOOL CImage::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
{
#ifdef __TCC79XX_WINCE__
	static CYUVRenderer yuvRenderer(WINDOW_W, WINDOW_H);

	if(CImageDecoder::m_pYUVRenderer == NULL)
	{
		CImageDecoder::m_pYUVRenderer = &yuvRenderer;
	}

#else
	if (m_CodeType == TYPE_WINCE)
	{
		//return m_pDecoder[m_CodeType]->Draw(hdc, dstRect, zoomlevel);
	}
	if(CImageDecoder::m_pYUVRenderer == NULL)
	{
		static CImageRender yuvRenderer(WINDOW_W, WINDOW_H);
		CImageDecoder::m_pYUVRenderer = &yuvRenderer;
	}
#ifdef HWJPGDEC_ENABLE

	if (m_CodeType != TYPE_TCC89HWJPG)
	{
		int width = dstRect->right-dstRect->left;
		int height = dstRect->bottom-dstRect->top;
	}
	else
	{
	}
#endif

	//m_pDecoder[m_CodeType]->m_pYUVRenderer->SetDisplaySize(m_pDecoder[m_CodeType]->m_Width, m_pDecoder[m_CodeType]->m_Height);
	m_pDecoder[m_CodeType]->m_pYUVRenderer->SetDisplaySize(WINDOW_W, WINDOW_H);
#endif
	
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
#ifdef HWJPGDEC_ENABLE
	if(bDetectHDMI&&(m_CodeType>TYPE_TCC89HWJPG)) 
#else
	if(bDetectHDMI) 
#endif
	{
		yrIMG_INFO srcInfo;
		yrRECT srRect;
		yrRECT DstRect;

		if(m_CodeType == TYPE_TCCSWGIF)
		{
			m_pDecoder[m_CodeType]->m_pYUVRenderer->RGBtoYUV((unsigned char*)m_ConvertPhysicalAddr, FORMAT_RGB565,
																m_pDecoder[m_CodeType]->m_Width, m_pDecoder[m_CodeType]->m_Height,
																(unsigned char*)m_YUVPhysicalAddr, FORMAT_YUV420);
		}
		
		if(0)	// dump YUV420
		{			
			FILE *fp =fopen("\\NAND\\softwareYUV.raw", "wb");
			fwrite((void*)m_YUVVirtualAddr, 1,(m_pDecoder[m_CodeType]->m_Width)*(m_pDecoder[m_CodeType]->m_Height)*1.5, fp);
			fclose(fp);
		}

		// render

		#ifndef __HDMI_ZOOM__
		if(m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedResultForSWDec())
		{

			srcInfo.phyAddr = m_pDecoder[m_CodeType]->m_pYUVRenderer->m_pRotateAddress;

			srRect.left = 0;
			srRect.top = 0;
			if((m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec()==3)||(m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec()==1))
			{
				srcInfo.paddedSize.cx = m_pDecoder[m_CodeType]->m_Height;
				srcInfo.paddedSize.cy = m_pDecoder[m_CodeType]->m_Width;
			}
			else
			{
				srcInfo.paddedSize.cx = m_pDecoder[m_CodeType]->m_Width;
				srcInfo.paddedSize.cy = m_pDecoder[m_CodeType]->m_Height;
			}

			srRect.right = srcInfo.paddedSize.cx;
 			srRect.bottom = srcInfo.paddedSize.cy;
			//printf("CImage::Draw[srcInfo]Width : %d, Height : %d\r\n", srcInfo.paddedSize.cx, srcInfo.paddedSize.cy);

			DstRect.left = WINDOW_W/2-(srcInfo.paddedSize.cx)/2;
			DstRect.top = WINDOW_H/2-(srcInfo.paddedSize.cy)/2;
			DstRect.right = DstRect.left+(srcInfo.paddedSize.cx);
			DstRect.bottom = DstRect.top+(srcInfo.paddedSize.cy);

			//printf("CImage::Draw[DstRect(%d, %d, %d, %d)]\r\n",DstRect.left, DstRect.right, DstRect.top, DstRect.bottom);
		    m_pDecoder[m_CodeType]->m_pYUVRenderer->IsEffectRender(FALSE);	
			m_pDecoder[m_CodeType]->m_pYUVRenderer->Render(srcInfo, srRect, DstRect);
		}
		else
		{
			srcInfo.phyAddr = m_YUVPhysicalAddr;
			srcInfo.paddedSize.cx = m_pDecoder[m_CodeType]->m_Width;
			srcInfo.paddedSize.cy = m_pDecoder[m_CodeType]->m_Height;

			//printf("CImage::Draw[srcInfo]Width : %d, Height : %d\r\n", srcInfo.paddedSize.cx, srcInfo.paddedSize.cy);

			yrRECT srRect;
			srRect.left = 0;
			srRect.right = srcInfo.paddedSize.cx;
			srRect.top = 0;
			srRect.bottom = srcInfo.paddedSize.cy;

			yrRECT DstRect;
			DstRect.left = WINDOW_W/2-(srcInfo.paddedSize.cx)/2;
			DstRect.top = WINDOW_H/2-(srcInfo.paddedSize.cy)/2;
			DstRect.right = DstRect.left+(srcInfo.paddedSize.cx);
			DstRect.bottom = DstRect.top+(srcInfo.paddedSize.cy);
			//printf("CImage::Draw[DstRect(%d, %d, %d, %d)]\r\n",DstRect.left, DstRect.right, DstRect.top, DstRect.bottom);

			m_pDecoder[m_CodeType]->m_pYUVRenderer->GetStatusValue(FALSE,0);
			m_pDecoder[m_CodeType]->m_pYUVRenderer->IsEffectRender(FALSE);
			m_pDecoder[m_CodeType]->m_pYUVRenderer->Render(srcInfo, srRect, DstRect);
		}
		#else
		#ifdef HWJPGDEC_ENABLE
		CTCC89HWJPGDecode *pHWJpg = (CTCC89HWJPGDecode*)m_pDecoder[TYPE_TCC89HWJPG];

		if(m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedResultForSWDec())
		{
			if((m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec()==3)||(m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec()==1))
			{
				pHWJpg->SetSWDrawValue(m_pDecoder[m_CodeType]->m_pYUVRenderer->m_pRotateAddress, m_pDecoder[m_CodeType]->m_Height, m_pDecoder[m_CodeType]->m_Width, m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec());
			}
			else
			{
				pHWJpg->SetSWDrawValue(m_pDecoder[m_CodeType]->m_pYUVRenderer->m_pRotateAddress, m_pDecoder[m_CodeType]->m_Width, m_pDecoder[m_CodeType]->m_Height, m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec());
			}
			m_pDecoder[TYPE_TCC89HWJPG]->m_pYUVRenderer->GetStatusValue(FALSE,m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec());
		}
		else
		{
			pHWJpg->SetSWDrawValue(m_YUVPhysicalAddr, m_pDecoder[m_CodeType]->m_Width, m_pDecoder[m_CodeType]->m_Height, m_pDecoder[m_CodeType]->m_pYUVRenderer->GetRotatedAngleForSWDec());
			m_pDecoder[TYPE_TCC89HWJPG]->m_pYUVRenderer->GetStatusValue(FALSE,0);
		}

		m_pDecoder[TYPE_TCC89HWJPG]->m_pYUVRenderer->IsEffectRender(FALSE);
		//printf("CImage::Draw[dstRect(%d, %d, %d, %d)]\r\n",dstRect->left, dstRect->right, dstRect->top, dstRect->bottom);
		return m_pDecoder[TYPE_TCC89HWJPG]->Draw(hdc, dstRect, zoomlevel);
		#endif
		#endif
		
		if(0)
		{
			HBRUSH hBrush = ::CreateSolidBrush(RGB(16,0,16));
//			RECT rt = {srRect.left,srRect.top, srRect.right, srRect.bottom};
//			RECT rt = {dstRect->left,dstRect->top, dstRect->right, dstRect->bottom};
			RECT rt = {DstRect.left,DstRect.top, DstRect.right, DstRect.bottom};
			::FillRect(hdc, &rt, hBrush);
			::DeleteObject(hBrush);
		}
		return TRUE;
	}
#endif
	m_pDecoder[m_CodeType]->m_pYUVRenderer->IsEffectRender(FALSE);
	
	BOOL ret;
	//if (m_CodeType != TYPE_TCC89HWJPG)
	//{
	//	HDC memDC = CreateCompatibleDC(hdc);
	//	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, dstRect->right-dstRect->left, dstRect->bottom-dstRect->top);
	//	HBITMAP hOldBmp = (HBITMAP)SelectObject(memDC, hBitmap);
	//	m_pDecoder[m_CodeType]->Draw(memDC, dstRect, zoomlevel);
	//	//BitBlt(hdc, dstRect->left, dstRect->top, dstRect->right-dstRect->left,  dstRect->bottom-dstRect->top, memDC, 0, 0, SRCCOPY);
	//	BitBlt(hdc, 0, 0, dstRect->right-dstRect->left,  dstRect->bottom-dstRect->top, memDC, 0, 0, SRCCOPY);
	//	SelectObject(memDC, hOldBmp);
	//	DeleteObject(hBitmap);
	//	DeleteDC(memDC);
	//	return TRUE;
	//}
	return m_pDecoder[m_CodeType]->Draw(hdc, dstRect, zoomlevel);
}

BOOL CImage::DrawEffect(unsigned char *pBuffer, RECT* srcRect, RECT* dstRect)
{
#if 0
#ifdef __TCC79XX_WINCE__
	static CYUVRenderer yuvRenderer(WINDOW_W, WINDOW_H);
	if(CImageDecoder::m_pYUVRenderer == NULL)
	{
		CImageDecoder::m_pYUVRenderer = &yuvRenderer;
	}

	SIZE srcSize = {(srcRect->right - srcRect->left), (srcRect->bottom - srcRect->top)};
	// Temp: m_pRotateAddress = m_pScalerAddress - 0x00100000;//0x20480000 - 0x00100000;
	unsigned int EffectPhysicalAddr = yuvRenderer.m_pScalerAddress-0x00100000;
	unsigned char* pEffectVirtualAddr = (unsigned char*)SetVirtual(EffectPhysicalAddr, srcSize.cx * srcSize.cy * 3 / 2);
	
#else
	if(CImageDecoder::m_pYUVRenderer == NULL)
	{
		static CImageRender yuvRenderer(WINDOW_W, WINDOW_H);
		CImageDecoder::m_pYUVRenderer = &yuvRenderer;
	}

	SIZE srcSize = {(srcRect->right - srcRect->left), (srcRect->bottom - srcRect->top)};
	unsigned int EffectPhysicalAddr = m_pDecoder[m_CodeType]->m_pYUVRenderer->m_pVideoStartMem;//for 800x480-0x00100000 
	                                                               //for HDMI-0x00300000
	unsigned char* pEffectVirtualAddr = (unsigned char*)SetVirtual(EffectPhysicalAddr, srcSize.cx * srcSize.cy * 3 / 2);
	//printf("EffectPhysicalAddr =%d\n",EffectPhysicalAddr);
#endif
	
	// only YUV420
	memcpy(pEffectVirtualAddr, pBuffer, srcSize.cx * srcSize.cy * 3 /2);

	// render
	yrIMG_INFO srcInfo;
	srcInfo.phyAddr = EffectPhysicalAddr;
	srcInfo.paddedSize.cx = srcSize.cx;
	srcInfo.paddedSize.cy = srcSize.cy;

	yrRECT srRect;
	srRect.left = srcRect->left;
	srRect.top = srcRect->top;
	srRect.right = srcRect->right;
	srRect.bottom = srcRect->bottom;

	yrRECT drRect;
	drRect.left = dstRect->left;
	drRect.top = dstRect->top;
	drRect.right = dstRect->right;
	drRect.bottom = dstRect->bottom;

#ifdef __TCC89XX_WINCE__
	m_pDecoder[m_CodeType]->m_pYUVRenderer->SetDisplaySize(WINDOW_W, WINDOW_H);
#endif
	m_pDecoder[m_CodeType]->m_pYUVRenderer->GetStatusValue(FALSE,0);
	m_pDecoder[m_CodeType]->m_pYUVRenderer->IsEffectRender(TRUE);
	m_pDecoder[m_CodeType]->m_pYUVRenderer->Render(srcInfo, srRect, drRect);

	FreeVirtual(pEffectVirtualAddr, srcSize.cx * srcSize.cy * 3 / 2);
#endif
	return TRUE;
}

BOOL CImage::RotateImage(FLOAT angle)
{
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
#ifdef HWJPGDEC_ENABLE
	if( ((m_CodeType < TYPE_WINCE) && (m_CodeType>TYPE_TCC89HWJPG)) && bDetectHDMI)
#else
	if((m_CodeType < TYPE_WINCE) && bDetectHDMI)
#endif
	{
		if(0)	// dump YUV420
		{			
			FILE *fp =fopen("\\NAND\\RotateImage.raw", "wb");
			fwrite((void*)m_YUVVirtualAddr, 1,m_pDecoder[m_CodeType]->m_Width*m_pDecoder[m_CodeType]->m_Height*1.5, fp);
			fclose(fp);
		}
		//printf("[RotateImage]Width : %d, Height : %d\r\n", m_pDecoder[m_CodeType]->m_Width,m_pDecoder[m_CodeType]->m_Height);
		return m_pDecoder[m_CodeType]->m_pYUVRenderer->RotateForSWDecOutput((unsigned char*)m_YUVPhysicalAddr,angle,m_pDecoder[m_CodeType]->m_Width,m_pDecoder[m_CodeType]->m_Height);
	}
	else
#endif
	return m_pDecoder[m_CodeType]->RotateImage(angle);
}

void CImage::ReleaseResource()
{
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(m_ConvertVirtualAddr)
	{
		FreeVirtual(m_ConvertVirtualAddr, (m_pDecoder[m_CodeType]->m_Width)*(m_pDecoder[m_CodeType]->m_Height)*2);
		m_ConvertVirtualAddr = NULL;
	}
	if(m_YUVVirtualAddr)
	{
		FreeVirtual(m_YUVVirtualAddr, (m_pDecoder[m_CodeType]->m_Width)*(m_pDecoder[m_CodeType]->m_Height)*3/2);
		m_YUVVirtualAddr = NULL;
	}
#endif
	// release all decoder resource
	for(int i = 0; i < (TYPE_WINCE + 1); i++)
	{
		if(m_pDecoder[i])
			m_pDecoder[i]->ReleaseResource();
	}
}

BOOL CImage::GetImageInfo(unsigned int *pWidth, unsigned int *pHeight, unsigned int *pPixelFormat, GUID *pRawDataFormat)
{
	if(1)//m_CodeType == TYPE_WINCE)
	{
		*pWidth = m_pDecoder[TYPE_WINCE]->m_Width;
		*pHeight = m_pDecoder[TYPE_WINCE]->m_Height;
		*pPixelFormat = m_pDecoder[TYPE_WINCE]->m_PixelFormat;
		*pRawDataFormat = m_pDecoder[TYPE_WINCE]->m_RawDataFormat;
		return TRUE;
	}
	else
		return FALSE;
}

void CImage::GetImageSize(unsigned int *pWidth, unsigned int *pHeight)
{
	*pWidth = m_pDecoder[m_CodeType]->m_Width;
	*pHeight = m_pDecoder[m_CodeType]->m_Height;
}

void CImage::HDMIDisplayOnOff(BOOL bSetting)
{
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	m_pDecoder[m_CodeType]->m_pYUVRenderer->DisplayVideoChannel(bSetting);
#endif
}



#ifdef __TCC89XX_WINCE__
//#define __HDMI_INCLUDE__
//#define HWJPGDEC_ENABLE
#endif

#ifdef __TCC89XX_WINCE__
#include "objbase.h"
#include "initguid.h"


#ifdef __HDMI_INCLUDE__
#include "Common/pkfuncs.h"
#include "Common/ioctl_code.h"
#include "Common/PhysicalAddress.h"
#endif
#else
#define INITGUID
#endif

#ifdef __TCC89XX_WINCE__
int  WINDOW_H = 480;
int  WINDOW_W = 800;
#else
int  WINDOW_H = 272;
int  WINDOW_W = 480;
#endif

#ifdef __TCC89XX_WINCE__
#include "common/include/globals.h"
#endif



#if (defined(__TCC89XX_WINCE__) && defined(HWJPGDEC_ENABLE))
BOOL ControlVPUClock = TRUE;	//TRUE : TCPhotoManager can control VPUClock
//FALSE: TCPhotoManager can not control VPUCLOCK
#endif

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
BOOL bDetectHDMI=FALSE;			// When Conntect HDMI, bDetectHDMI set TRUE
static BOOL bOldSet=FALSE;

void LoadHDMIStatus(BOOL *mode,int *Width,int *Height)
{
	HKEY    hk;
	DWORD   dwStatus;
	DWORD dwSize,dwType;
	int displayflag = 0;
#if 0
	bDetectHDMI=TRUE;
	WINDOW_W=*Width=800;
	WINDOW_H=*Height=480;
#else
	dwStatus = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Drivers\\Display\\Magellan\\CONFIG", 0, 0, &hk);
	if( ERROR_SUCCESS != dwStatus )
	{
		return;
	}

	if(dwStatus == ERROR_SUCCESS) 
	{
		dwSize = sizeof(DWORD);
		dwStatus = ::RegQueryValueEx(hk, _T("HDMISet"), NULL, &dwType, (BYTE*) mode, &dwSize);		

		if(bOldSet != *mode)
		{
			bOldSet = *mode;
			displayflag = 1;
		}
	}

	if(dwStatus == ERROR_SUCCESS && *mode)
	{
		if(dwStatus == ERROR_SUCCESS) 
		{
			dwSize = sizeof(DWORD);

			dwStatus = ::RegQueryValueEx(hk, _T("HDMIWidth"), NULL, &dwType, (BYTE*)Width, &dwSize);

			if(displayflag)
			{
				printf("[TCPhotoManager]HDMIWidth : %d\n",*Width);
			}

			if(*Width <=0 || *Width > 1920)
			{
				*Width = ::GetSystemMetrics(SM_CXSCREEN);//800;
				if(displayflag)
				{
					printf("[TCPhotoManager]Default HDMIWidth : %d\n",*Width);
				}
			}

		}
		if(dwStatus == ERROR_SUCCESS) 
		{
			dwSize = sizeof(DWORD);

			dwStatus = ::RegQueryValueEx(hk, _T("HDMIHeight"), NULL, &dwType,(BYTE*) Height, &dwSize);
			if(displayflag)
			{
				printf("[TCPhotoManager]HDMIHeight : %d\n",*Height);
			}

			if(*Height <=0 || *Height > 1080)
			{
				*Height = ::GetSystemMetrics(SM_CYSCREEN);//480;
				if(displayflag)
				{
					printf("[TCPhotoManager]Default HDMIHeight : %d\n",*Height);
				}
			}
		}
		WINDOW_W=*Width;
		WINDOW_H=*Height;
	}
	else
	{
		WINDOW_W=*Width= ::GetSystemMetrics(SM_CXSCREEN);//800;
		WINDOW_H=*Height=::GetSystemMetrics(SM_CYSCREEN);//480;
		if(displayflag)
		{
			printf("\tHDMI Out~!: (%d, %d)\n",WINDOW_W,WINDOW_H);
		}
	}

	if(hk != NULL) 
	{
		::RegCloseKey(hk);
	}
#endif
}
#endif