#include <Windows.h>
#include "stdAfx.h"
#include "TCCPNGSWDecode.h"

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
extern BOOL bDetectHDMI;			// When Conntect HDMI, bDetectHDMI set TRUE
#endif

CTCCPngSwDecode::CTCCPngSwDecode()
{
	fp=NULL;

	memset( &output_setting, 0, sizeof(PD_CUSTOM_DECODE) );

	pHeapBuf= NULL;
	pInstanceMem= NULL;
	pPD_init_Mem = NULL;

	m_hDC = ::GetDC(NULL);
	m_hMemDC=::CreateCompatibleDC(m_hDC);
	m_hMemBitmap = NULL;

	rotateAngle = 0;
	isPNGInfoChanged = FALSE;
	m_bSWPNGImage = FALSE;
}

CTCCPngSwDecode::~CTCCPngSwDecode()
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

unsigned int CTCCPngSwDecode::PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	int ret_val;
	//PD_CALLBACKS callbacks = {(int (*)(void *, int, int, void *))fread};
	PD_CALLBACKS callbacks = {(size_t (*)(void *, size_t, size_t, void *))fread};

	//printf("[pInstanceMem]PrepareImage\n");

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

	memset(&output_setting, 0, sizeof(PD_CUSTOM_DECODE) );

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
		printf("[PNG Size is invalid - width(%d), height(%d)]\n", uiWidth, uiHeight);
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

	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	unsigned int uiTotFileSize = ftell(fp); //V1.65
	fseek(fp, 0, SEEK_SET);
	//printf("input stream: %s, size=%d bytes\n",szFileName, uiTotFileSize);
	//printf("[PNG Size is width(%d), height(%d)]\n", m_uiDisplayWidth, m_uiDisplayHeight);

	pInstanceMem = (char *)new unsigned char[PD_INSTANCE_MEM_SIZE];
	if( pInstanceMem == NULL ) {
		ReleaseResource();		
		printf("[pInstanceMem]Fail to new\n");
		return 0;
	}
	memset( pInstanceMem, 0, PD_INSTANCE_MEM_SIZE );

	pPD_init_Mem = (PD_INIT *)new unsigned char[sizeof(PD_INIT)];
	if( pPD_init_Mem == NULL ) {
		ReleaseResource();		
		printf("[pPD_init_Mem]Fail to new\n");
		return 0;
	}
	memset( pPD_init_Mem, 0, sizeof(PD_INIT) );

	pPD_init_Mem->pInstanceBuf = pInstanceMem;
	pPD_init_Mem->datasource = (void *)fp;
	pPD_init_Mem->lcd_width = m_uiDisplayWidth;
	pPD_init_Mem->lcd_height = m_uiDisplayHeight;
	pPD_init_Mem->iTotFileSize = uiTotFileSize;			//V1.65

	//printf("[TCCXXX_PNG_Decode]PD_DEC_INIT\n");
	ret_val = TCCXXX_PNG_Decode( PD_DEC_INIT, pPD_init_Mem, &callbacks, 0 );
	if(ret_val == PD_RETURN_INIT_FAIL) {
		ReleaseResource();		
		printf("[TCCXXX_PNG_Decode]Fail to PD_DEC_INIT\n");
		return 0;
	}

	return 1;
}

BOOL CTCCPngSwDecode::DecodeImage(unsigned int *pResultSize, unsigned int Index)
{
	int ret_val;
  
	PNG_Alpha  = pPD_init_Mem->alpha_available;
	heap_size  = pPD_init_Mem->heap_size;
	PNG_pixelDepth = pPD_init_Mem->pixel_depth;	//V1.67

	//printf("PNGDecode[Display %d:%d][W:%d, H:%d],[PNG_Alpha:%d, heap_size:%d]\n",m_uiDisplayWidth, m_uiDisplayHeight, pPD_init_Mem->image_width, pPD_init_Mem->image_height, PNG_Alpha, heap_size);

	/* Error Detection Mode Setting */
	output_setting.ERROR_DET_MODE = PD_ERROR_CHK_NONE;

	/* Resource Occupation Degree Setting */
	output_setting.RESOURCE_OCCUPATION = PD_RESOURCE_LEVEL_NONE;

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		output_setting.write_func = (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_YUV420;
	}
	else
#endif
	{
		output_setting.write_func = (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_RGB565;
	}
	
	pHeapBuf = (unsigned char *)new uint32[heap_size];
	if( pHeapBuf == NULL ) {
		ReleaseResource();		
		printf("[pHeapBuf]Fail to new\n");
		return FALSE;
	}
	memset(pHeapBuf, 0, heap_size);
	output_setting.Heap_Memory = pHeapBuf;	

	/* Modify location of output image */
	output_setting.MODIFY_IMAGE_POS = 0;
	if(output_setting.MODIFY_IMAGE_POS ) {
		output_setting.IMAGE_POS_X = 310;
		output_setting.IMAGE_POS_Y = 230;
	}
	
	output_setting.USE_ALPHA_DATA = PD_ALPHA_DISABLE;
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		output_setting.write_func = (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_YUV420;
	}
	else
#endif
	if(PNG_Alpha == PD_ALPHA_AVAILABLE)
	{		
		output_setting.USE_ALPHA_DATA = PD_ALPHA_AVAILABLE;
		output_setting.write_func = (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_RGB888_With_Alpha;
	}

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		PNG_IM_LCD_Addr = (unsigned int)LCDbuf;
		output_size = (m_uiDisplayWidth * m_uiDisplayHeight) + (m_uiDisplayWidth*m_uiDisplayHeight)>>1;
		memset((void *)PNG_IM_LCD_Addr , 0, (m_uiDisplayWidth * m_uiDisplayHeight));
		memset((void *)(PNG_IM_LCD_Addr+(m_uiDisplayWidth * m_uiDisplayHeight)), 0x80, (m_uiDisplayWidth * m_uiDisplayHeight)>>1);	

		PNG_IM_2nd_Offset = (m_uiDisplayWidth * m_uiDisplayHeight);
		PNG_IM_3rd_Offset = PNG_IM_2nd_Offset+(PNG_IM_2nd_Offset>>2);
		PNG_IM_LCD_Half_Stride = m_uiDisplayWidth>>1;
	}
	else
#endif
	{
		if(m_hMemBitmap)
		{
			::SelectObject(m_hMemDC, m_hBackupBitmap);
			::DeleteObject(m_hMemBitmap);
			m_hMemBitmap = NULL;
		}

		unsigned char outformat = FORMAT_RGB565;
		if(PNG_Alpha == PD_ALPHA_AVAILABLE)
			outformat = FORMAT_RGB888;

		unsigned char* pOutBuffer = CreateBitMap(m_uiDisplayWidth, m_uiDisplayHeight, &output_size, (GE_CH_DATAFORMAT)outformat);
		if(pOutBuffer == NULL)
			return FALSE;

		PNG_IM_LCD_Addr = (unsigned int)pOutBuffer;
		memset((void *)PNG_IM_LCD_Addr, 0, output_size);
	}
//	printf("[TCCXXX_PNG_Decode]PD_DEC_DECODE Start\n");
	ret_val = 1;
	while(ret_val > 0)
	{
		ret_val = TCCXXX_PNG_Decode( PD_DEC_DECODE, &output_setting, 0, 0 );
	}

	if(ret_val != PD_RETURN_DECODE_DONE) {
		printf("[TCCXXX_PNG_Decode]Fail to PD_DEC_DECODE - Error_code: %d\n", ret_val);
		ReleaseResource();
		return FALSE;
	}
	else
	{
		//printf("[TCCXXX_PNG_Decode]PD_DEC_DECODE End\n");

		if( pHeapBuf != NULL ) {
			delete [] pHeapBuf;
			pHeapBuf = NULL;
		}
		if( pInstanceMem != NULL ) {
			delete [] pInstanceMem;
			pInstanceMem = NULL;
		}
		if( pPD_init_Mem != NULL ) {
			delete [] pPD_init_Mem;
			pPD_init_Mem = NULL;
		}
#if 0
	 	FILE *out_fp;	
		out_fp=fopen("/NAND/Dump_pngdecoder.rgb","wb");
		fwrite((void *)PNG_IM_LCD_Addr, output_size, 1, out_fp);
		fclose(out_fp);
#endif
		*pResultSize = output_size;
		m_bSWPNGImage = TRUE;
		return TRUE;
	}
}

BOOL CTCCPngSwDecode::EndDecode()
{
	if(output_size)
	{
		m_hBackupBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBitmap);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCCPngSwDecode::CheckDrawImage()
{	
	return m_bSWPNGImage;
}

void CTCCPngSwDecode::ClearDrawImage()
{	
	m_bSWPNGImage = FALSE;
}

BOOL CTCCPngSwDecode::IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight)
{
	if(isPNGInfoChanged)
	{
		m_Width = m_uiDecodeWidth;
		m_Height = m_uiDecodeHeight;

		*uiWidth = m_uiDecodeWidth;
		*uiHeight = m_uiDecodeHeight;
		return TRUE;
	}
	return FALSE;
}

unsigned int CTCCPngSwDecode::CheckDecodingCodecFormat()
{
	return TYPE_TCCSWPNG;
}

void CTCCPngSwDecode::DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff)
{
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(bDetectHDMI)
	{
		LCDbuf = pOutBuff;
	}
#endif
}

BOOL CTCCPngSwDecode::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
{
	::SelectObject(hdc, (HBRUSH)::GetStockObject(NULL_BRUSH));

	if(m_hMemDC && m_hMemBitmap)
	{
#if __TCC79XX_WINCE__
		if(PNG_Alpha == PD_ALPHA_AVAILABLE)
		{			
			::FillRect(hdc,dstRect,(HBRUSH)::GetStockObject(BLACK_BRUSH));

			BLENDFUNCTION bf;
			bf.BlendOp=AC_SRC_OVER; 
			bf.BlendFlags=0; 
			bf.SourceConstantAlpha=255; 
			bf.AlphaFormat=1;

			AlphaBlend(hdc,dstRect->left, dstRect->top, dstRect->right-dstRect->left, dstRect->bottom-dstRect->top,
					m_hMemDC, 0, 0, m_uiDisplayWidth, m_uiDisplayHeight, bf);	
		}
		else
#endif
		{
		StretchBlt(hdc, dstRect->left, dstRect->top, dstRect->right-dstRect->left, dstRect->bottom-dstRect->top,
				m_hMemDC, 0, 0, m_uiDisplayWidth, m_uiDisplayHeight, SRCCOPY);
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CTCCPngSwDecode::RotateImage(FLOAT angle)
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

		if(PNG_Alpha == PD_ALPHA_AVAILABLE)
		{
			unsigned int *pDest = (unsigned int*)pRotateBuffer;
			unsigned int *pSrc = (unsigned int*)PNG_IM_LCD_Addr;

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
		}
		else
		{
			unsigned short *pDest = (unsigned short*)pRotateBuffer;
			unsigned short *pSrc = (unsigned short*)PNG_IM_LCD_Addr;

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

		unsigned char outformat = FORMAT_RGB565;
		if(PNG_Alpha == PD_ALPHA_AVAILABLE)
			outformat = FORMAT_RGB888;

		unsigned char* pOutBuffer = CreateBitMap(m_uiDisplayWidth, m_uiDisplayHeight, &output_size, (GE_CH_DATAFORMAT)outformat);
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

void CTCCPngSwDecode::ReleaseResource()
{
	if( pHeapBuf != NULL ) {
		delete [] pHeapBuf;
		pHeapBuf = NULL;
	}
	if( pInstanceMem != NULL ) {
		delete [] pInstanceMem;
		pInstanceMem = NULL;
	}
	if( pPD_init_Mem != NULL ) {
		delete [] pPD_init_Mem;
		pPD_init_Mem = NULL;
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
	isPNGInfoChanged = FALSE;
	m_bSWPNGImage = FALSE;
}

unsigned char* CTCCPngSwDecode::CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format)
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
