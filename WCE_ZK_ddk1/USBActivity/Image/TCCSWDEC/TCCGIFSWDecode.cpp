#include "stdAfx.h"
#include "TCCGIFSWDecode.h"

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
extern BOOL bDetectHDMI;			// When Conntect HDMI, bDetectHDMI set TRUE
#endif

CTCCGifSwDecode::CTCCGifSwDecode()
{
	fp=NULL;

	LCDbuf = NULL;
	m_hDC = ::GetDC(NULL);
	m_hMemDC=::CreateCompatibleDC(m_hDC);
	m_hMemBitmap = NULL;

	isGIFInfoChanged = FALSE;
	m_bSWGIFImage = FALSE;

	memset(&init, 0, sizeof(init));
}

CTCCGifSwDecode::~CTCCGifSwDecode()
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

unsigned int CTCCGifSwDecode::PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	GIFD_INFO info;

	GIFD_CALLBACKS callbacks = {(unsigned long (*)(void *, unsigned long, unsigned long, void *))fread, (unsigned long (*)(void *, long, long))fseek};

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

	heap_size = TCCXXX_GIFDEC_GetHeapSize(uiWidth, uiHeight, GIFD_OUT_RGB565);

//	printf("[GIF_PrePare]heap_size =%d\n",heap_size);

	init.input_src = fp;					// file handle
	init.callback  = callbacks;				// callbacks
	init.out_width = uiWidth;				// output width
	init.out_height= uiHeight;				// output height
	init.out_format= GIFD_OUT_RGB565;		// output color format
	init.out_flip  = FALSE;					// flipped output
	init.out_option= 0;						// 0: default (keep background | center output)
	init.heap_buff = new unsigned char[heap_size];	// allocate heap memory
	init.heap_size = heap_size;					// allocated heap size

#if 0
	printf(	"==<< GIF Test >>========================\n"
			" Out Size: %d * %d \n"
			" Out Format: %d \n"
			" Flipped: %d \n"
			"\n"
			"==<< Decoding >>========================\n",
			init.out_width, init.out_height,
			init.out_format,
			init.out_flip
			);
#endif

	hGif = TCCXXX_GIFDEC_Init(&init, &info);
	if(hGif == NULL || init.heap_buff == NULL)
	{
		ReleaseResource();		
		printf("[TCCXXX_GIF_Decode]Fail to TCCXXX_GIF_Init\n");
		return 0;
	}

	return 1;
}

BOOL CTCCGifSwDecode::DecodeImage(unsigned int *pResultSize, unsigned int Index)
{
	int dec_ret;
	GIFD_DECIN dec_in;
	GIFD_DECOUT dec_out;

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		//printf("[TCCXXX_GIF_Decode]bDetectHDMI Endable\n");
		if(LCDbuf == NULL)
			return FALSE;
	}
	else
#endif
	{
		//printf("[TCCXXX_GIF_Decode]bDetectHDMI Disable\n");
		if(LCDbuf == NULL)
		{
			LCDbuf = CreateBitMap(m_uiDisplayWidth, m_uiDisplayHeight, &output_size, FORMAT_RGB565);
			if(LCDbuf == NULL)
				return FALSE;
			else
			{
				memset(LCDbuf, 0, (m_uiDisplayWidth * m_uiDisplayHeight * 2));
				//memset(LCDbuf, 0xFF, (m_uiDisplayWidth * m_uiDisplayHeight * 2));
			}
		}
	}

	dec_in.out_buffer = LCDbuf;
	dec_ret = TCCXXX_GIFDEC_Decode(hGif, &dec_in, &dec_out);//, GDI_Temp2);
	if(dec_ret < 0)
	{
		printf("[GIF_TEST] Decoding Failed (code: %d)\n", dec_ret);
		return -1;
	}

#if 0
	switch(dec_ret)
	{
	case RESULT_IMAGE_COMPLETE:
		printf("RESULT_IMAGE_COMPLETE(delay : %d)\r\n", dec_out.delay_time);
		break;
	case RESULT_IMAGE_INCOMPLETE:
		printf("RESULT_IMAGE_INCOMPLETE\r\n");
		break;	
	case RESULT_SEQUENCE_COMPLETE:
		printf("RESULT_SEQUENCE_COMPLETE\r\n");
		break;
	case RESULT_DECODE_COMPLETE:
		printf("RESULT_DECODE_COMPLETE\r\n");
		break;
	}
#endif
	
	Sleep(dec_out.delay_time * 10);	// Unit of dec_out.delay_time is 1/100 second

	*pResultSize = output_size;
	m_bSWGIFImage = TRUE;
	return TRUE; 
}

BOOL CTCCGifSwDecode::EndDecode()
{
	if(output_size)
	{
		m_hBackupBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBitmap);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCCGifSwDecode::CheckDrawImage()
{	
	return m_bSWGIFImage;
}

void CTCCGifSwDecode::ClearDrawImage()
{	
	RECT rt = {0, 0, WINDOW_W, WINDOW_H};
	HDC hdc = ::GetDC(NULL);
	::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
	::ReleaseDC(NULL, hdc);
}

BOOL CTCCGifSwDecode::IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight)
{
	if(isGIFInfoChanged)
	{
		m_Width = m_uiDecodeWidth;
		m_Height= m_uiDecodeHeight;

		*uiWidth = m_uiDecodeWidth;
		*uiHeight= m_uiDecodeHeight;
		return TRUE;
	}
	return FALSE;
}

unsigned int CTCCGifSwDecode::CheckDecodingCodecFormat()
{
	return TYPE_TCCSWGIF;
}

void CTCCGifSwDecode::DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff)
{
	LCDbuf = pConvertBuff;
}

BOOL CTCCGifSwDecode::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
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

BOOL CTCCGifSwDecode::RotateImage(FLOAT angle)
{
	return TRUE;
}

void CTCCGifSwDecode::ReleaseResource()
{
	if(init.heap_buff)
	{
		delete [] init.heap_buff;
		init.heap_buff = NULL;
	}

	LCDbuf = NULL;

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
	
	isGIFInfoChanged = FALSE;
	m_bSWGIFImage = FALSE;
}

unsigned char* CTCCGifSwDecode::CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format)
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
