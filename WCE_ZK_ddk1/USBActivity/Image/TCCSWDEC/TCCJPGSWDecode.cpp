#include "stdAfx.h"
#include "TCCJPGSWDecode.h"

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
extern BOOL bDetectHDMI;			// When Conntect HDMI, bDetectHDMI set TRUE
#endif

CTCCJpgSwDecode::CTCCJpgSwDecode()
{
	fp=NULL;
#ifdef __TCC89XX_WINCE__
	h_jpeg_dec=NULL;
#endif
	memset(&out_callback, 0, sizeof(out_callback));
	lcd_resize_buf = NULL;

	m_hDC = ::GetDC(NULL);
	m_hMemDC=::CreateCompatibleDC(m_hDC);
	m_hMemBitmap = NULL;

	rotateAngle = 0;
	isJPGInfoChanged = FALSE;
	m_bSWJPGImage = FALSE;
}

CTCCJpgSwDecode::~CTCCJpgSwDecode()
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

unsigned int CTCCJpgSwDecode::PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	int ret_val;

#ifdef __TCC89XX_WINCE__
	JD_CALLBACKS callbacks;
	
	callbacks.read_func = (uint16 (*)(void *, size_t, size_t, void *))fread;
	callbacks.malloc_func = (void* (*)(unsigned int))malloc;
	callbacks.free_func = (void (*)(void *))free;
#else
	JD_CALLBACKS callbacks = {(uint16 (*)(void *, size_t, size_t, void *))fread};
#endif
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
	if((uiWidth*uiHeight*2)>(DEC_MAX_WIDTH*DEC_MAX_HEIGHT*2))
	{
		if( DEC_MAX_WIDTH/uiWidth > DEC_MAX_HEIGHT/uiHeight )
		{
			uiWidth = DEC_MAX_HEIGHT*uiWidth/uiHeight;
			uiHeight = DEC_MAX_HEIGHT;
			if(uiWidth>DEC_MAX_WIDTH)
			{
				uiHeight = DEC_MAX_WIDTH*uiHeight/uiWidth;
				uiWidth = DEC_MAX_WIDTH;
			}
		}
		else
		{
			uiHeight = DEC_MAX_WIDTH*uiHeight/uiWidth;
			uiWidth = DEC_MAX_WIDTH;
			if(uiHeight>DEC_MAX_HEIGHT)
			{
				uiWidth = DEC_MAX_HEIGHT*uiWidth/uiHeight;
				uiHeight = DEC_MAX_HEIGHT;
			}
		}
	}
	
	if(uiWidth == 0 || uiHeight == 0)
	{
		ReleaseResource();		
		printf("[JPG Size has a strange - width(%d), height(%d)]\n", uiWidth, uiHeight);
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

	m_uiDisplayWidth = m_uiDecodeWidth = uiWidth;
	m_uiDisplayHeight = m_uiDecodeHeight = uiHeight;

#ifdef __TCC89XX_WINCE__
#if 1
	src_fmt_info.Origin_Size_Decode = 0;

//	lcd_resize_buf = (int *) new BYTE[RESIZE_BUF_SIZE(uiWidth, uiHeight)];
	uint32 size_of_resize_buf = ((uiWidth*4) >  (uiHeight*4)) ? uiWidth*4*2 : uiHeight*4*2;
	size_of_resize_buf = MAX(size_of_resize_buf, resize_buf_size);
	lcd_resize_buf = (int *)new BYTE[size_of_resize_buf];
	
	if(lcd_resize_buf == 0)
	{
		ReleaseResource();		
		printf("[lcd_resize_buf]Not Support!\n");
		return 0;
	}
	
	ret_val = TCCXXX_JPEGDEC_Init2(&h_jpeg_dec, fp, uiWidth, uiHeight, &lcd_resize_buf, &src_fmt_info, &callbacks);
#else
	int *resize_buf = 0;
	src_fmt_info.Origin_Size_Decode = 1;

	ret_val = TCCXXX_JPEGDEC_Init2(&h_jpeg_dec, fp, uiWidth, uiHeight, &resize_buf, &src_fmt_info, &callbacks);
#endif
#else
	lcd_resize_buf = (int *) new BYTE[RESIZE_BUF_SIZE(uiWidth, uiHeight)];
	if(lcd_resize_buf == 0)
	{
		ReleaseResource();		
		printf("[lcd_resize_buf]Not Support!\n");
		return 0;
	}

	ret_val = TCCXXX_JPEGDEC_Init2(fp, uiWidth, uiHeight, lcd_resize_buf, &src_fmt_info, callbacks);
#endif
	if(ret_val != 0)
	{
		ReleaseResource();
		printf("[TCCXXX_JPEGDEC_Init2]Not Support!\n");
		return 0;
	}

	return 1;
}

BOOL CTCCJpgSwDecode::DecodeImage(unsigned int *pResultSize, unsigned int Index)
{
	out_callback.Calc_Buf = (uint16 *)new BYTE[src_fmt_info.JD_Calc_Buf_Size+4];
	//printf("out_callback.Calc_Buf=%d\n",src_fmt_info.JD_Calc_Buf_Size);
	if(out_callback.Calc_Buf == 0)
	{
		ReleaseResource();
		printf("[out_callback.Calc_Buf]Not Support!\n");
		return FALSE;
	}
	memset(out_callback.Calc_Buf,0, src_fmt_info.JD_Calc_Buf_Size);

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		src_fmt_info.JD_Color_Space = JD_SRC_YUV;
#ifdef __TCC89XX_WINCE__
		out_callback.write_func = 0;//(void (*)(IM_PIX_INFO))TCC_CustomOutput_YUV420;
		out_callback.write_block_func = 0;  // Initialize
		out_callback.write_block_func = TCC_JPEG_CustomOutput_YUV420_Block;

		/*if(m_uiDisplayWidth & 3)
			m_uiDisplayWidth += 4 - (m_uiDisplayWidth&3);
		if(m_uiDisplayHeight & 3)
			m_uiDisplayHeight += 4 - (m_uiDisplayHeight&3);
		*/
		output_size = (m_uiDisplayWidth*m_uiDisplayHeight)+(m_uiDisplayWidth*m_uiDisplayHeight)/2;

		JPG_IM_2nd_Offset = (m_uiDisplayWidth*m_uiDisplayHeight);
		JPG_IM_3rd_Offset = JPG_IM_2nd_Offset + (m_uiDisplayWidth*m_uiDisplayHeight)/4;
		JPG_IM_LCD_Half_Stride = m_uiDisplayWidth/2;

#else
		out_callback.write_func = (void (*)(IM_PIX_INFO))TCC_CustomOutput_YUV420;
		output_size = (m_uiDisplayWidth*m_uiDisplayHeight)+(m_uiDisplayWidth*m_uiDisplayHeight)/2;

		IM_2nd_Offset = (m_uiDisplayWidth*m_uiDisplayHeight);
		IM_3rd_Offset = IM_2nd_Offset + (m_uiDisplayWidth*m_uiDisplayHeight)/4;
		IM_LCD_Half_Stride = m_uiDisplayWidth/2;
#endif
		printf("m_uiDisplayWidth : %d, m_uiDisplayHeight : %d\r\n", m_uiDisplayWidth, m_uiDisplayHeight);
		
		//out_callback.LCD_OUTPUT_BUFFER = new unsigned char[output_size];
		if(out_callback.LCD_OUTPUT_BUFFER == NULL)
		{
			ReleaseResource();
			printf("[out_callback.LCD_OUTPUT_BUFFER]Not Support!\n");
			return FALSE;
		}

		memset(out_callback.LCD_OUTPUT_BUFFER , 0, (m_uiDisplayWidth*m_uiDisplayHeight));
		memset(out_callback.LCD_OUTPUT_BUFFER+(m_uiDisplayWidth*m_uiDisplayHeight) , 0x80, (m_uiDisplayWidth*m_uiDisplayHeight)>>1);
	}
	else
#endif
	{
		src_fmt_info.JD_Color_Space = JD_SRC_RGB;

		if(src_fmt_info.JD_Color_Space == JD_SRC_RGB)
		{
#ifdef __TCC89XX_WINCE__
			out_callback.write_func = 0;//(void (*)(IM_PIX_INFO))TCC_CustomOutput_RGB565;
			out_callback.write_block_func = 0;  // Initialize
			out_callback.write_block_func = TCC_JPEG_CustomOutput_RGB565_Block;
#else
			out_callback.write_func = (void (*)(IM_PIX_INFO))TCC_CustomOutput_RGB565;		
#endif
		}
		
		if(m_hMemBitmap)
		{
			::SelectObject(m_hMemDC, m_hBackupBitmap);
			::DeleteObject(m_hMemBitmap);
			m_hMemBitmap = NULL;
		}

		out_callback.LCD_OUTPUT_BUFFER = CreateBitMap(m_uiDisplayWidth, m_uiDisplayHeight, &output_size, FORMAT_RGB565);
		if(out_callback.LCD_OUTPUT_BUFFER == NULL)
			return FALSE;
	}
#ifdef __TCC89XX_WINCE__
	JPG_IM_LCD_Addr = (unsigned int)out_callback.LCD_OUTPUT_BUFFER;
#else
	IM_LCD_Addr = (unsigned int)out_callback.LCD_OUTPUT_BUFFER;
#endif

	int ret_val =1;

	if(output_size ==0)
	{
		*pResultSize = 0;
		return FALSE;
	}
	
#ifdef __TCC89XX_WINCE__
	while(ret_val > 0)
	{
		ret_val = TCCXXX_JPEGDEC_Decode(&h_jpeg_dec, out_callback);
	}

#else
	while(ret_val > 0)
	{
		ret_val = TCCXXX_JPEGDEC_Decode(out_callback);
	}
#endif
    
	if(ret_val < 0)
	{
		*pResultSize = 0;
		ReleaseResource();
		return FALSE;
	}
	else
	{
		printf("[CTCCJpgSwDecode]Support!\n");
#ifdef __TCC89XX_WINCE__
		if(h_jpeg_dec!=NULL)
		{
			TCCXXX_JPEGDEC_Close(&h_jpeg_dec);
		}
#endif		

		if(lcd_resize_buf)
		{
			delete [] lcd_resize_buf;
			lcd_resize_buf = NULL;
		}
		if(out_callback.Calc_Buf != 0)
		{
			delete [] out_callback.Calc_Buf;
			out_callback.Calc_Buf = NULL;
		}

		*pResultSize = output_size;
		m_bSWJPGImage = TRUE;

		return TRUE; 
	}
}

BOOL CTCCJpgSwDecode::EndDecode()
{
	if(output_size)
	{
		m_hBackupBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBitmap);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCCJpgSwDecode::CheckDrawImage()
{	
	return m_bSWJPGImage;
}

void CTCCJpgSwDecode::ClearDrawImage()
{	
	{
		RECT rt = {0, 0, WINDOW_W, WINDOW_H};
		HDC hdc = ::GetDC(NULL);
		::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
		::ReleaseDC(NULL, hdc);
	}
}

BOOL CTCCJpgSwDecode::IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight)
{
	if(isJPGInfoChanged)
	{
		m_Width = m_uiDecodeWidth;
		m_Height = m_uiDecodeHeight;

		*uiWidth = m_uiDecodeWidth;
		*uiHeight = m_uiDecodeHeight;
		return TRUE;
	}
	return FALSE;
}

unsigned int CTCCJpgSwDecode::CheckDecodingCodecFormat()
{
	return TYPE_TCCSWJPG;
}

void CTCCJpgSwDecode::DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff)
{
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		out_callback.LCD_OUTPUT_BUFFER = pOutBuff;
	}
#endif
}

BOOL CTCCJpgSwDecode::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
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

BOOL CTCCJpgSwDecode::RotateImage(FLOAT angle)
{
	if(rotateAngle == angle)
		return TRUE;

	if(output_size)
	{	
		unsigned int height, width;
		unsigned char *pRotateBuffer = new unsigned char[output_size];
		if(pRotateBuffer == NULL)
		{
			printf("Rotate buffer memory Allocation fail : %d\r\n", GetLastError());
			return FALSE;
		}

		unsigned short *pDest = (unsigned short*)pRotateBuffer;
		unsigned short *pSrc = (unsigned short*)out_callback.LCD_OUTPUT_BUFFER;

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

		for(height = 0; height < m_uiDecodeHeight; height++)
		{
			for(width = 0; width < m_uiDecodeWidth; width++)
			{
				if(direction == 1)
					pDest[height + ((m_uiDecodeWidth - width - 1) * m_uiDecodeHeight)] = pSrc[width + (height * m_uiDecodeWidth)];
				else if(direction == -1)
					pDest[(m_uiDecodeHeight - height - 1) + (width * m_uiDecodeHeight)] = pSrc[width + (height * m_uiDecodeWidth)];
				else
					pDest[(m_uiDecodeWidth - width - 1) + ((m_uiDecodeHeight - height - 1) * m_uiDecodeWidth)] = pSrc[width + (height * m_uiDecodeWidth)];
			}
		}

		if(direction == 1 || direction == -1)
		{
			m_uiDisplayWidth = m_uiDecodeHeight;
			m_uiDisplayHeight = m_uiDecodeWidth;

			m_uiDecodeWidth = m_uiDisplayWidth;
			m_uiDecodeHeight = m_uiDisplayHeight;
		}
		if(m_hMemBitmap)
		{
			::SelectObject(m_hMemDC, m_hBackupBitmap);
			::DeleteObject(m_hMemBitmap);
			m_hMemBitmap = NULL;
		}

		out_callback.LCD_OUTPUT_BUFFER = CreateBitMap(m_uiDisplayWidth, m_uiDisplayHeight, &output_size, FORMAT_RGB565);
		if(out_callback.LCD_OUTPUT_BUFFER == NULL)
			return FALSE;

		memcpy(out_callback.LCD_OUTPUT_BUFFER, pDest, output_size);

		m_hBackupBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBitmap);

		rotateAngle = angle;

		delete [] pRotateBuffer;
	}
	return TRUE;
}

void CTCCJpgSwDecode::ReleaseResource()
{
#ifdef __TCC89XX_WINCE__
	if(h_jpeg_dec!=NULL)
	{
		TCCXXX_JPEGDEC_Close(&h_jpeg_dec);
	}
#endif

	if(out_callback.Calc_Buf)
	{
		delete [] out_callback.Calc_Buf;
		out_callback.Calc_Buf = NULL;
	}

	if(m_hMemBitmap)
	{
		::SelectObject(m_hMemDC, m_hBackupBitmap);
		::DeleteObject(m_hMemBitmap);
		m_hMemBitmap = NULL;
	}

	if(lcd_resize_buf)
	{
		delete [] lcd_resize_buf;
		lcd_resize_buf = NULL;
	}

	if(fp)
	{
		fclose(fp);	
		fp=NULL;
	}
	
	rotateAngle = 0;	
	isJPGInfoChanged = FALSE;
	m_bSWJPGImage = FALSE;
}

unsigned char* CTCCJpgSwDecode::CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format)
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
