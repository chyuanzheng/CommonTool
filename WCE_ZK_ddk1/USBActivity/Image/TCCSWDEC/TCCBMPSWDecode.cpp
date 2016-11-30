#include "stdAfx.h"
#include "TCCBMPSWDecode.h"

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
extern BOOL bDetectHDMI;			// When Conntect HDMI, bDetectHDMI set TRUE
#endif

#define	BMP_DEC_MAX_WIDTH 2400
#define	BMP_DEC_MAX_HEIGHT 1440

CTCCBmpSwDecode::CTCCBmpSwDecode()
{
	fp=NULL;
	BMP_FILE_BUF = NULL;

	m_hDC = ::GetDC(NULL);
	m_hMemDC=::CreateCompatibleDC(m_hDC);
	m_hMemBitmap = NULL;

	rotateAngle = 0;
	isBMPInfoChanged = FALSE;
	m_bSWBMPImage = FALSE;
}

CTCCBmpSwDecode::~CTCCBmpSwDecode()
{
	if(fp)
	{
		fclose(fp);	
		fp=NULL;
	}

	if(m_hMemBitmap)
	{
		::DeleteObject(m_hMemBitmap);
		m_hMemBitmap = NULL;
	}
	
	ReleaseResource();

	if(m_hMemDC)
	{
		::DeleteDC(m_hMemDC);
		m_hMemDC = NULL;
	}
	::ReleaseDC(NULL, m_hDC);
}

unsigned int CTCCBmpSwDecode::PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	bmphandle_t bh;
	
	BMP_CALLBACKS_INIT BMP_callbacks_init = {(size_t (*)(void *, size_t, size_t, void *))fread};

	if(uiWidth == 0 || uiHeight == 0)
		return 0;
    
	if(fp)
	{
		fclose(fp);	
		fp=NULL;
	}
	
	fp = _wfopen(szFileName, L"rb");
	if(fp == NULL)
	{
		printf("fopen Fail");
		return 0;
	}

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(!bDetectHDMI)
#endif
	if((uiWidth*uiHeight*2)>(BMP_DEC_MAX_WIDTH*BMP_DEC_MAX_HEIGHT*2))
	{
		if( BMP_DEC_MAX_WIDTH/uiWidth > BMP_DEC_MAX_HEIGHT/uiHeight )
		{
			uiWidth = BMP_DEC_MAX_HEIGHT*uiWidth/uiHeight;
			uiHeight = BMP_DEC_MAX_HEIGHT;
			if(uiWidth>BMP_DEC_MAX_WIDTH)
			{
				uiHeight = BMP_DEC_MAX_WIDTH*uiHeight/uiWidth;
				uiWidth = BMP_DEC_MAX_WIDTH;
			}
		}
		else
		{
			uiHeight = BMP_DEC_MAX_WIDTH*uiHeight/uiWidth;
			uiWidth = BMP_DEC_MAX_WIDTH;
			if(uiHeight>BMP_DEC_MAX_HEIGHT)
			{
				uiWidth = BMP_DEC_MAX_HEIGHT*uiWidth/uiHeight;
				uiHeight = BMP_DEC_MAX_HEIGHT;
			}
		}
		//printf("[BMP Size is width(%d), height(%d)]\n", uiWidth, uiHeight);
	}

	if(uiWidth == 0 || uiHeight == 0)
	{
		ReleaseResource();		
		return 0;
	}

	if(uiWidth % 2)
	{
		uiWidth += 1;
	}	
	if(uiHeight % 2)
	{
		uiHeight += 1;
	}

	m_uiDecodeWidth  = m_uiDisplayWidth = uiWidth;
	m_uiDecodeHeight = m_uiDisplayHeight= uiHeight;

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		output_size = (uiWidth * uiHeight)+(uiWidth * uiHeight)/2;
	}
	else
#endif
	{
		output_size = (uiWidth * uiHeight)*2;//+(m_uiDecodeWidth * m_uiDecodeHeight)/2;
	}

	//printf("SW BMP Decoder::[%d|%d]output_size =%d\n",m_uiDecodeWidth,m_uiDecodeHeight,output_size);

	bh = TCCXXX_BMP_Init(fp, BMP_callbacks_init, m_uiDecodeHeight, m_uiDecodeWidth);
	if(bh == NULL)
	{
		ReleaseResource();		
		printf("[TCCXXX_BMP_Decode]Fail to TCCXXX_BMP_Init\n");
		return 0;
	}

	//BMP_FILE_BUF = (uint32 *)malloc((bh->bytes_per_line*2*sizeof(uint32)));
	BMP_FILE_BUF = new uint32[bh->bytes_per_line*2];//[output_size];//
	if(BMP_FILE_BUF == NULL)
	{
		ReleaseResource();		
		printf("[TCCXXX_BMP_Decode]Fail to BMP_FILE_BUF\n");
		return 0;
	}
	memset(BMP_FILE_BUF, 0, bh->bytes_per_line *2 * sizeof(uint32));//
	return 1;
}

BOOL CTCCBmpSwDecode::DecodeImage(unsigned int *pResultSize, unsigned int Index)
{
	int ret_val;
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		BMP_CALLBACKS_DECODE BMP_callbacks_decode = {(unsigned int (*)(void *, long, int))fseek,  (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_YUV420};

		PNG_IM_LCD_Addr = (unsigned int)LCDbuf;
		memset((void *)PNG_IM_LCD_Addr , 0, (m_uiDisplayWidth*m_uiDisplayHeight));
		memset((void *)(PNG_IM_LCD_Addr+(m_uiDisplayWidth*m_uiDisplayHeight)), 0x80, (m_uiDisplayWidth*m_uiDisplayHeight)>>1);	
		
		PNG_IM_2nd_Offset = (m_uiDisplayWidth*m_uiDisplayHeight);
		PNG_IM_3rd_Offset = PNG_IM_2nd_Offset+(PNG_IM_2nd_Offset>>2);
		PNG_IM_LCD_Half_Stride = m_uiDisplayWidth>>1;		

		ret_val=1;
		while(ret_val)
		{
			ret_val = TCCXXX_BMP_Decode(BMP_callbacks_decode,(unsigned int *)BMP_FILE_BUF);//(unsigned int *)PNG_IM_LCD_Addr);//
			if(ret_val < 0)
			{
				printf("[CTCCBmpSwDecode]Fail to TCCXXX_BMP_Decode - Error_code: %d\n", ret_val);
				ReleaseResource();
				return FALSE;
			}
		}
	}
	else
#endif
	{
		BMP_CALLBACKS_DECODE BMP_callbacks_decode = {(unsigned int (*)(void *, long, int))fseek,  (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_RGB565};
		
		unsigned char* pOutBuffer = CreateBitMap(m_uiDisplayWidth, m_uiDisplayHeight, &output_size, (GE_CH_DATAFORMAT)FORMAT_RGB565);
		
		if(pOutBuffer == NULL)
			return FALSE;

		PNG_IM_LCD_Addr = (unsigned int)pOutBuffer;	
		memset((void *)PNG_IM_LCD_Addr, 0, output_size);
	
		ret_val=1;
		while(ret_val)
		{
			ret_val = TCCXXX_BMP_Decode(BMP_callbacks_decode,(unsigned int *)BMP_FILE_BUF);//(unsigned int *)PNG_IM_LCD_Addr);//
			if(ret_val < 0)
			{
				printf("[CTCCBmpSwDecode]Fail to TCCXXX_BMP_Decode - Error_code: %d\n", ret_val);
				ReleaseResource();
				return FALSE;
			}
		}
	}

#if 0
	FILE *fp;	
	fp=fopen("/NAND/Dump_bmpdecoder.yuv","wb");
	fwrite((void *)PNG_IM_LCD_Addr, output_size, 1, fp);
	fclose(fp);
#endif

	*pResultSize = output_size;
	m_bSWBMPImage = TRUE;
	return TRUE; 
}

BOOL CTCCBmpSwDecode::EndDecode()
{
	if(output_size)
	{
		m_hBackupBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBitmap);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCCBmpSwDecode::CheckDrawImage()
{	
	return m_bSWBMPImage;
}

void CTCCBmpSwDecode::ClearDrawImage()
{	
	RECT rt = {0, 0, WINDOW_W, WINDOW_H};
	HDC hdc = ::GetDC(NULL);
	::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
	::ReleaseDC(NULL, hdc);
}

BOOL CTCCBmpSwDecode::IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight)
{
	if(isBMPInfoChanged)
	{
		m_Width = m_uiDecodeWidth;
		m_Height= m_uiDecodeHeight;

		*uiWidth = m_uiDecodeWidth;
		*uiHeight= m_uiDecodeHeight;
		return TRUE;
	}
	return FALSE;
}

unsigned int CTCCBmpSwDecode::CheckDecodingCodecFormat()
{
	return TYPE_TCCSWBMP;
}

void CTCCBmpSwDecode::DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff)
{
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		LCDbuf = pOutBuff;
	}
#endif
}


BOOL CTCCBmpSwDecode::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
{
	::SelectObject(hdc, (HBRUSH)::GetStockObject(NULL_BRUSH));

	if(m_hMemDC && m_hMemBitmap)
	{
		StretchBlt(hdc, dstRect->left, dstRect->top, dstRect->right-dstRect->left, dstRect->bottom-dstRect->top,
				m_hMemDC, 0, 0, m_uiDisplayWidth, m_uiDisplayHeight, SRCCOPY);
		return TRUE;
	}

	return FALSE;
}

BOOL CTCCBmpSwDecode::RotateImage(FLOAT angle)
{
	if(rotateAngle == angle)
		return TRUE;

	if(output_size)
	{	
		unsigned int height, width;
		unsigned char *pRotateBuffer = new unsigned char[output_size];
		if(pRotateBuffer == NULL)
		{
			//printf("Rotate buffer memory Allocation fail : %d\r\n", GetLastError());
			return FALSE;
		}

		int direction = 0;
		if(rotateAngle == 0)
		{
			if(angle == 90)
				direction = -1;
			else if(angle == 270)
				direction = 1;
		}
		else if(rotateAngle == 90)
		{
			if(angle == 180)
				direction = -1;
			else if(angle == 0)
				direction = 1;
		}
		else if(rotateAngle == 180)
		{
			if(angle == 270)
				direction = -1;
			else if(angle == 90)
				direction = 1;
		}
		else if(rotateAngle == 270)
		{
			if(angle == 0)
				direction = -1;
			else if(angle == 180)
				direction = 1;
		}

		unsigned short *pDest = (unsigned short*)pRotateBuffer;
		unsigned short *pSrc = (unsigned short*)PNG_IM_LCD_Addr;

		for(height = 0; height < m_uiDecodeHeight; height++)
		{
			for(width = 0; width < m_uiDecodeWidth; width++)
			{
				if(direction == 1)
					pDest[height + ((m_uiDecodeWidth - width - 1) * m_uiDecodeWidth)] = pSrc[width + (height * m_uiDecodeWidth)];
				else if(direction == -1)
					pDest[(m_uiDecodeHeight - height - 1) + (width * m_uiDecodeHeight)] = pSrc[width + (height * m_uiDecodeWidth)];
				else
					pDest[(m_uiDecodeWidth - width - 1) + ((m_uiDecodeHeight - height - 1) * m_uiDecodeWidth)] = pSrc[width + (height * m_uiDecodeWidth)];
			}
		}

		if(direction == 1 || direction == -1)
		{
			m_uiDisplayWidth = m_uiDecodeHeight;
			m_uiDisplayHeight= m_uiDecodeWidth;

			m_uiDecodeWidth = m_uiDisplayWidth;
			m_uiDecodeHeight= m_uiDisplayHeight;
		}
		if(m_hMemBitmap)
		{
			::SelectObject(m_hMemDC, m_hBackupBitmap);
			::DeleteObject(m_hMemBitmap);
			m_hMemBitmap = NULL;
		}

		unsigned char* pOutBuffer = CreateBitMap(m_uiDisplayWidth, m_uiDisplayHeight, &output_size, (GE_CH_DATAFORMAT)FORMAT_RGB565);
		if(pOutBuffer == NULL)
		{
			delete [] pRotateBuffer;
			return FALSE;
		}

		PNG_IM_LCD_Addr = (unsigned int)pOutBuffer;

		memcpy(pOutBuffer, pRotateBuffer, output_size);

		m_hBackupBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBitmap);

		rotateAngle = angle;

		delete [] pRotateBuffer;
	}
	return TRUE;
}

void CTCCBmpSwDecode::ReleaseResource()
{

	if(BMP_FILE_BUF){
		delete [] BMP_FILE_BUF;
		BMP_FILE_BUF = NULL;
	}

	if(m_hMemBitmap)
	{
		::SelectObject(m_hMemDC, m_hBackupBitmap);
		::DeleteObject(m_hMemBitmap);
		m_hMemBitmap = NULL;
	}

	if(fp)
	{
		fclose(fp);	
		fp=NULL;
	}	
	
	rotateAngle = 0;	
	isBMPInfoChanged = FALSE;
	m_bSWBMPImage = FALSE;
}

unsigned char* CTCCBmpSwDecode::CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format)
{
	void* pBitmapBuff = NULL;

	if(width == 0 || height == 0)
		return NULL;

	unsigned char bitcount;
	if(format == FORMAT_RGB565)
		bitcount = 16;	// RGB565 format has 2bytes per pixel
	else if(format == FORMAT_RGB888)
		bitcount = 32;	// RGB888 format has 4bytes per pixel
	else
		return NULL;
	
	*buffsize = width * height * (bitcount / 8);

	// add 12bytes for color bitmask
	unsigned char *pBITMAPINFOBuff = new unsigned char[sizeof(BITMAPINFO) + 12];
	memset(pBITMAPINFOBuff, 0, sizeof(BITMAPINFO) + 12);

	BITMAPINFO *pbmInfo = (BITMAPINFO*)pBITMAPINFOBuff;

	pbmInfo->bmiHeader.biSize			=	sizeof(BITMAPINFOHEADER);
	pbmInfo->bmiHeader.biWidth			=	width;
	pbmInfo->bmiHeader.biHeight			=	-height;	//'-' means top-down DIB, '+' means bottom-up DIB
	pbmInfo->bmiHeader.biPlanes			=	1;
	pbmInfo->bmiHeader.biBitCount		=	bitcount;
	pbmInfo->bmiHeader.biCompression	=	(format == FORMAT_RGB565)?BI_BITFIELDS:BI_RGB;
	pbmInfo->bmiHeader.biSizeImage		=	*buffsize;
	pbmInfo->bmiHeader.biXPelsPerMeter	=	0;
	pbmInfo->bmiHeader.biYPelsPerMeter	=	0;
	pbmInfo->bmiHeader.biClrUsed		=	0;
	pbmInfo->bmiHeader.biClrImportant	=	0;

	// set bitmask for RGB565
	if(format == FORMAT_RGB565)
	{
		unsigned long *pmask = (unsigned long *)(pbmInfo->bmiColors);
		pmask[0] = 0xf800;
		pmask[1] = 0x07e0;
		pmask[2] = 0x001f;
		pmask[3] = 0x0000;
	}

	m_hMemBitmap = CreateDIBSection(m_hMemDC, (BITMAPINFO*)pbmInfo, DIB_RGB_COLORS, (void**)&pBitmapBuff, NULL, 0);

	delete [] pBITMAPINFOBuff;
		
	if(m_hMemBitmap == NULL || pBitmapBuff == NULL)
	{
		//printf("Memory Allocation fail : %d\r\n", GetLastError());
		ReleaseResource();
		return NULL;
	}

	return (unsigned char*)pBitmapBuff;
}
