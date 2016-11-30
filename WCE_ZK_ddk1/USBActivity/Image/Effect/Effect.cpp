#include "StdAfx.h"
#include <windowsx.h>
#include "Effect.h"

#include "..\Image.h"
//#include "..\preview\imageCont.h"
#include "..\TCCSWDEC\TCCXXX_JPEGDEC.h"
#include "..\TCCSWDEC\TCCXXX_BMP_DEC.h"
#include "..\TCCSWDEC\TCCXXX_PNG_DEC.h"


extern HWND g_hParentHwnd;

GxxString GetNextFile()
{
	//if(SendMessage(g_hParentHwnd, WM_PHOTOGETNEXT, 0, 0) == -1)
	//{
	//	// 最后一个
	//	return _T("LAST");
	//}
	//FILE *fp = fopen("\\photonextfile", "r");
	//if (fp)
	//{
	//	TCHAR fnBuff[MAX_PATH] = {0};
	//	fgetws(fnBuff, MAX_PATH, fp);
	//	fclose(fp);
	//	return fnBuff;
	//}
	return _T("");
}

extern int  WINDOW_H;
extern int  WINDOW_W;

CEffect* CEffect::mpInstance = NULL;

typedef enum
{
	TIMER_DECODE = 1,
	TIMER_SLIDESHOW,
	TIMER_EXIT
}TIMER_INDEX;

CEffect::CEffect()
: m_pImageDecoder(NULL)
//, m_pImageFileCont(NULL)
, m_hWnd(NULL)
, m_Format(FORMAT_YUV420)//FORMAT_RGB565)
, m_bShowEffect(FALSE)
, m_hDC(NULL)
, m_hMemDC(NULL)
, m_hMemBitmap(NULL)
{
	mpInstance = this;

	NexImage_Init();

	m_hEventThreadExit = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hEventDecode[0] = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEventDecode[1] = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	m_FileIndex = 0;
	m_NextFileIndex = 0;
	m_BaseIndex = 0;
	
	m_bRepeat = TRUE;
	m_bShuffle= FALSE;
	
	if( FALSE==cThread::Create() )
	{
		printf("cound not create a thread.\r\n");
	}

	#if (!(defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__)))
	unsigned int BufferSize;
	if(m_Format == FORMAT_RGB565)
		BufferSize = WINDOW_W * WINDOW_H * 2;
	else	// FORMAT_YUV420
		BufferSize = WINDOW_W * WINDOW_H * 3 / 2;
	
	m_pSrcBuffer[0] = new unsigned char[BufferSize];
	m_pSrcBuffer[1] = new unsigned char[BufferSize];
	m_pEffectBuffer = new unsigned char[BufferSize];

	m_EffectRect.left = 0;
	m_EffectRect.top = 0;
	m_EffectRect.right = WINDOW_W;
	m_EffectRect.bottom = WINDOW_H;
	#endif
	DecodePFn[TYPE_JPEG] = JPGDecoder;
	DecodePFn[TYPE_BMP] = BMPDecoder;
	DecodePFn[TYPE_PNG] = PNGDecoder;

	::InitializeCriticalSection(&m_CS);	
}

CEffect::~CEffect()
{
	NexImage_DeInit();

	if(mhThread)
	{
		::SetEvent(m_hEventThreadExit);
		::WaitForSingleObject(mhThread, INFINITE);

		::CloseHandle(mhThread);
		mhThread=NULL;
	}

	::CloseHandle(m_hEventThreadExit);
	::CloseHandle(m_hEventDecode[0]);
	::CloseHandle(m_hEventDecode[1]);

	if(m_hMemBitmap)
		::DeleteObject(m_hMemBitmap);
	if(m_hMemDC)
		::DeleteDC(m_hMemDC);
	if(m_hDC)
		::ReleaseDC(NULL, m_hDC);

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	Destroy();
#else
	if(m_pSrcBuffer[0])
		delete [] m_pSrcBuffer[0];
	if(m_pSrcBuffer[1])
		delete [] m_pSrcBuffer[1];
	if(m_pEffectBuffer && m_Format == FORMAT_YUV420)
		delete [] m_pEffectBuffer;	
#endif
	::DeleteCriticalSection(&m_CS);
}

void CEffect::Init(LPVOID pImageDecoder, LPVOID pImageFileCont, int Message)
{
	m_pImageDecoder = (CImage*)pImageDecoder;
	//m_pImageFileCont = (CImageFileCont*)pImageFileCont;
	m_Message = Message;
}

void CEffect::Destroy()
{
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	if(m_pSrcBuffer[0])
	{
		delete [] m_pSrcBuffer[0];
		m_pSrcBuffer[0]=NULL;
	}
	if(m_pSrcBuffer[1])
	{
		delete [] m_pSrcBuffer[1];
		m_pSrcBuffer[1]=NULL;
	}
	if(m_pEffectBuffer && m_Format == FORMAT_YUV420)
	{
		delete [] m_pEffectBuffer;
		m_pEffectBuffer=NULL;
	}
#endif
}

void CEffect::Create(int X, int Y, int nWidth, int nHeight, HWND hWndParent)
{
	m_hWnd = hWndParent;
	
#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	unsigned int BufferSize;
	if(m_Format == FORMAT_RGB565)
		BufferSize = nWidth * nHeight * 2;
	else	// FORMAT_YUV420
		BufferSize = nWidth * nHeight * 3 / 2;
	
	m_pSrcBuffer[0] = new unsigned char[BufferSize];
	m_pSrcBuffer[1] = new unsigned char[BufferSize];
	m_pEffectBuffer = new unsigned char[BufferSize];

	m_EffectRect.left = 0;
	m_EffectRect.top = 0;
	m_EffectRect.right = nWidth;
	m_EffectRect.bottom = nHeight;
#endif

	if(m_Format == FORMAT_RGB565)
	{
		m_hDC = ::GetDC(m_hWnd);
		m_hMemDC=::CreateCompatibleDC(m_hDC);

		// bmiColors struct size is strange... so shoud be add 12bytes
		unsigned char *pBITMAPINFOBuff = new unsigned char[sizeof(BITMAPINFO) + 12];
		memset(pBITMAPINFOBuff, 0, sizeof(BITMAPINFO) + 12);

		BITMAPINFO *pbmInfo = (BITMAPINFO*)pBITMAPINFOBuff;

		pbmInfo->bmiHeader.biSize			=	sizeof(BITMAPINFOHEADER);
		pbmInfo->bmiHeader.biWidth			=	nWidth;
		pbmInfo->bmiHeader.biHeight			=	-nHeight;	//'-' means top-down DIB, '+' means bottom-up DIB
		pbmInfo->bmiHeader.biPlanes			=	1;
		pbmInfo->bmiHeader.biBitCount		=	16;	// RGB565 format has 2bytes per pixel
		pbmInfo->bmiHeader.biCompression	=	BI_BITFIELDS;
		pbmInfo->bmiHeader.biSizeImage		=	nWidth * nHeight * 2;
		pbmInfo->bmiHeader.biXPelsPerMeter	=	0;
		pbmInfo->bmiHeader.biYPelsPerMeter	=	0;
		pbmInfo->bmiHeader.biClrUsed		=	0;	
		pbmInfo->bmiHeader.biClrImportant	=	0;	

		// set bitmask for RGB565
		unsigned long *pmask = (unsigned long *)(pbmInfo->bmiColors);
		pmask[0] = 0xf800;
		pmask[1] = 0x07e0;
		pmask[2] = 0x001f;
		pmask[3] = 0x0000;

		m_hMemBitmap = CreateDIBSection(m_hMemDC, (BITMAPINFO*)pbmInfo, DIB_RGB_COLORS, (void**)&m_pEffectBuffer, NULL, 0);

		delete [] pBITMAPINFOBuff;

		m_hBackupBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBitmap);
	}
}

void CEffect::OnTimer(unsigned int id)
{
	switch(id)
	{
	case TIMER_DECODE:
		{
			::KillTimer(m_hWnd, TIMER_DECODE);
			
			TransitionParamSet(NULL);
			//::SetTimer(m_hWnd, TIMER_SLIDESHOW, m_TransitionTime, NULL);	// start slide show
			::SetTimer(m_hWnd, TIMER_SLIDESHOW, 0, NULL);	// start slide show
		}
		break;

	case TIMER_SLIDESHOW:
		{
			::KillTimer(m_hWnd, TIMER_SLIDESHOW);
	
			if(m_TransitionCount < m_TransitionNumber)
			{
				if(TransitionImage() == TRUE)
				{
					if(m_bEffectProcess == TRUE)
					{						
						::SetTimer(m_hWnd, TIMER_SLIDESHOW, m_TransitionTime, NULL);	// start slide show
					ReDraw();
					}
				}
				else		// slide show complete
				{
					if(m_BaseIndex == 0)
					{
						m_BaseIndex = 1;						
						::SetEvent(m_hEventDecode[0]);	// decode next image
					}
					else
					{
						m_BaseIndex = 0;						
						::SetEvent(m_hEventDecode[0]);	// decode next image
					}
				}
			}
			else		// slide show complete
			{
				if(m_bEffectProcess == TRUE)
					::SetTimer(m_hWnd, TIMER_DECODE, m_SlideTime, NULL);
				
				if(m_BaseIndex == 0)
				{
					m_BaseIndex = 1;					
					::SetEvent(m_hEventDecode[0]);	// decode next image
				}
				else
				{
					m_BaseIndex = 0;					
					::SetEvent(m_hEventDecode[1]);	// decode next image
				}
			}
		}
		break;

	case TIMER_EXIT:
		{
			::KillTimer(m_hWnd, TIMER_DECODE);
			::KillTimer(m_hWnd, TIMER_SLIDESHOW);
			::KillTimer(m_hWnd, TIMER_EXIT);
			Destroy();
			::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(m_Message, 0), SetEndEffectIndex());
		}
		break;
	}
}

int CEffect::SetEndEffectIndex()
{
	return m_FileIndex;
	//return (m_FileIndex==0)?0:m_FileIndex-1;
}

int CEffect::OnCmdExit(BOOL bImageOpen)
{
	printf("OnCmdExit\r\n");
	
	::EnterCriticalSection(&m_CS);

	if(bImageOpen == TRUE)
	    ::SetTimer(m_hWnd, TIMER_EXIT, 0, NULL);
	else
	    ::SetTimer(m_hWnd, TIMER_EXIT, m_SlideTime, NULL);
	
	m_bEffectProcess = FALSE;
	m_bShowEffect = FALSE;	
	::LeaveCriticalSection(&m_CS);

	//if(bImageOpen)
	//    ::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(m_Message, 0), SetEndEffectIndex());

	return SetEndEffectIndex();
}

void CEffect::ReDraw()
{
	if(m_Format == FORMAT_YUV420)
	{		
		m_pImageDecoder->DrawEffect(m_pEffectBuffer, &m_EffectRect, &m_EffectRect);
	}
	
	m_bShowEffect = TRUE;

	HDC hdc = ::GetDC(m_hWnd);
	RECT rtClient;
	if(m_bShowEffect == TRUE)
	{
		if(m_Format == FORMAT_RGB565)
		{
			rtClient = m_EffectRect;
			if(m_hMemDC && m_hMemBitmap)
			{
				::BitBlt(hdc, rtClient.left, rtClient.top, rtClient.right-rtClient.left, rtClient.bottom-rtClient.top, m_hMemDC, 0, 0, SRCCOPY);
			}
		}
		else
		{	
			::GetClientRect(m_hWnd, &rtClient);
			HBRUSH hBrush = ::CreateSolidBrush(RGB(16,0,16));
			::FillRect(hdc, &rtClient, hBrush);
			::DeleteObject(hBrush);
		}
	}
	::ReleaseDC(m_hWnd, hdc);
}

DecoderType CEffect::CheckImageType(GxxString filename)
{
	if( (filename.Find(_T(".jpg")) >= 0) || (filename.Find(_T(".JPG")) >= 0))
		return TYPE_JPEG;
	if( (filename.Find(_T(".jpeg")) >= 0) || (filename.Find(_T(".JPEG")) >= 0))
		return TYPE_JPEG;
	else if( (filename.Find(_T(".bmp")) >= 0) || (filename.Find(_T(".BMP")) >= 0))
		return TYPE_BMP;
	else if( (filename.Find(_T(".png")) >= 0) || (filename.Find(_T(".PNG")) >= 0))
		return TYPE_PNG;
	else
		return TYPE_MAX;
}

BOOL CEffect::JPGDecoder(unsigned char *pdst, unsigned int *pwidth, unsigned int *pheight)
{
	BOOL ret_dec;
	int ret_val;

	FILE *fp_jpg = NULL;
	JD_SRC_FMT src_fmt_info;
	IM_CUSTOM_OUTPUT outCallback;
	unsigned int outputSize;
	int * lcd_resize_buf = NULL;
	int aaa = 0;

#ifdef __TCC89XX_WINCE__
	uint32  h_jpeg_dec; //After 1.68 
	JD_CALLBACKS callbacks;
	
	callbacks.read_func = (uint16 (*)(void *, size_t, size_t, void *))fread;
	callbacks.malloc_func = (void* (*)(unsigned int))malloc;
	callbacks.free_func = (void (*)(void *))free;
#else
	JD_CALLBACKS callbacks = {(uint16 (*)(void *, size_t, size_t, void *))fread};
#endif

	fp_jpg = _wfopen(mpInstance->m_CurFileName, L"rb");
	if(fp_jpg == NULL)
	{
		return FALSE;
	}

	memset(&src_fmt_info, 0x00, sizeof(JD_SRC_FMT));
	memset(&outCallback, 0, sizeof(outCallback));

	*pwidth  = WINDOW_W;
	*pheight = WINDOW_H;

#ifdef __TCC89XX_WINCE__
	src_fmt_info.Origin_Size_Decode = 0;

	uint32 size_of_resize_buf = ((WINDOW_W*4) >  (WINDOW_H*4)) ? WINDOW_W*4*2 : WINDOW_H*4*2;
	size_of_resize_buf = MAX(size_of_resize_buf, resize_buf_size);
	lcd_resize_buf = (int *)new BYTE[size_of_resize_buf];
	
	if(lcd_resize_buf == 0)
	{
		lcd_resize_buf = NULL;
		ret_dec = FALSE;
		printf("[lcd_resize_buf]Not Support!\n");
		goto finish;
	}
	
	ret_val = TCCXXX_JPEGDEC_Init2(&h_jpeg_dec, fp_jpg, *pwidth, *pheight, &lcd_resize_buf, &src_fmt_info, &callbacks);
#else
	lcd_resize_buf = (int *) new BYTE[RESIZE_BUF_SIZE(WINDOW_W, WINDOW_H)];
	if(lcd_resize_buf == 0)
	{
		lcd_resize_buf = NULL;
		ret_dec = FALSE;
		printf("[lcd_resize_buf]Not Support!\n");
		goto finish;
	}

	ret_val = TCCXXX_JPEGDEC_Init2(fp_jpg, *pwidth, *pheight, lcd_resize_buf, &src_fmt_info, callbacks);
#endif
	if(ret_val != ERROR_NONE)
	{
		printf("[fp_jpg:Fail]INIT\n");
		ret_dec = FALSE;
		goto finish;
	}

	outCallback.Calc_Buf = (unsigned short*)new unsigned char[src_fmt_info.JD_Calc_Buf_Size];
	if(outCallback.Calc_Buf == 0)
	{
		printf("outCallback.Calc_Buf is NULL\r\n");
		outCallback.Calc_Buf = NULL;
		ret_dec = FALSE;
		goto finish;
	}
	memset(outCallback.Calc_Buf,0, src_fmt_info.JD_Calc_Buf_Size);

	if(mpInstance->m_Format == FORMAT_RGB565)
	{
		src_fmt_info.JD_Color_Space = JD_SRC_RGB;
#ifdef __TCC89XX_WINCE__
		outCallback.write_func = 0;
		outCallback.write_block_func = 0;
		outCallback.write_block_func = TCC_JPEG_CustomOutput_RGB565_Block;
#else
		outCallback.write_func = (void (*)(IM_PIX_INFO))TCC_CustomOutput_RGB565;
#endif
		outputSize = (*pwidth * *pheight) * 2;
	}
	else // FORMAT_YUV420
	{
		src_fmt_info.JD_Color_Space = JD_SRC_YUV;
#ifdef __TCC89XX_WINCE__
		outCallback.write_func = 0;//(void (*)(IM_PIX_INFO))TCC_CustomOutput_YUV420;
		outCallback.write_block_func = 0;  // Initialize
		outCallback.write_block_func = TCC_JPEG_CustomOutput_YUV420_Block;

		/*if(*pwidth & 3)
			*pwidth += 4 - (*pwidth&3);
		if(*pheight & 3)
			*pheight += 4 - (*pheight&3);
		*/
		outputSize = (*pwidth * *pheight)+(*pwidth * *pheight)/2;
#else
		outCallback.write_func = (void (*)(IM_PIX_INFO))TCC_CustomOutput_YUV420;
		outputSize = (*pwidth * *pheight)+(*pwidth * *pheight)/2;
#endif
	}

#ifdef __TCC89XX_WINCE__
	JPG_IM_2nd_Offset = *pwidth * *pheight;
	JPG_IM_3rd_Offset = JPG_IM_2nd_Offset + *pwidth * *pheight / 4;
	JPG_IM_LCD_Half_Stride = *pwidth / 2;
#else
	IM_2nd_Offset = *pwidth * *pheight;
	IM_3rd_Offset = IM_2nd_Offset + *pwidth * *pheight / 4;
	IM_LCD_Half_Stride = *pwidth / 2;
#endif

	outCallback.LCD_OUTPUT_BUFFER = new unsigned char[outputSize];
	if(mpInstance->m_Format == FORMAT_RGB565)
	{
		memset(outCallback.LCD_OUTPUT_BUFFER, 0, outputSize);
	}
	else
	{
		memset(outCallback.LCD_OUTPUT_BUFFER , 0, ((*pwidth) * (*pheight)));
		memset(outCallback.LCD_OUTPUT_BUFFER+((*pwidth) * (*pheight)) , 0x80, ((*pwidth)*(*pheight))>>1);	
	}
	
#ifdef __TCC89XX_WINCE__
	JPG_IM_LCD_Addr = (unsigned int)outCallback.LCD_OUTPUT_BUFFER;
#else
	IM_LCD_Addr = (unsigned int)outCallback.LCD_OUTPUT_BUFFER;
#endif

	ret_val=1;
	while(ret_val > 0)
	{
#ifdef __TCC89XX_WINCE__
		ret_val = TCCXXX_JPEGDEC_Decode(&h_jpeg_dec, outCallback);
#else
		ret_val = TCCXXX_JPEGDEC_Decode(outCallback);
#endif
		if(ret_val < 0)
		{
			ret_dec = FALSE;
			goto finish;
		}
	}

#if 0
	FILE *fp;	
	fp=fopen("/NAND/jpgdecoder.yuv","wb");
	fwrite(outCallback.LCD_OUTPUT_BUFFER, outputSize, 1, fp);
	fclose(fp);
#endif
	memcpy(pdst, outCallback.LCD_OUTPUT_BUFFER, outputSize);
	ret_dec = TRUE;

finish:
#ifdef __TCC89XX_WINCE__
	TCCXXX_JPEGDEC_Close(&h_jpeg_dec);
#endif		
	if(lcd_resize_buf){
		delete [] lcd_resize_buf;
		lcd_resize_buf = NULL;
	}
	if(outCallback.Calc_Buf){
		delete [] outCallback.Calc_Buf;
		outCallback.Calc_Buf = NULL;
	}

	if(outCallback.LCD_OUTPUT_BUFFER){
		delete [] outCallback.LCD_OUTPUT_BUFFER;
		outCallback.LCD_OUTPUT_BUFFER = NULL;
	}

	if(fp_jpg){
		fclose(fp_jpg);
		fp_jpg = NULL;
	}

    return ret_dec;
}

BOOL CEffect::BMPDecoder(unsigned char *pdst, unsigned int *pwidth, unsigned int *pheight)
{
	BOOL ret_dec;
	int ret_val;

	FILE *fp_bmp = NULL;
	bmphandle_t bh;
	unsigned char *LCDbuf;
	unsigned char *BMP_FILE_BUF;
	unsigned int outputSize;

	BMP_CALLBACKS_INIT BMP_callbacks_init = {(size_t (*)(void *, size_t, size_t, void *))fread};
	BMP_CALLBACKS_DECODE BMP_callbacks_decode = {(unsigned int (*)(void *, long, int))fseek,  (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_YUV420};

	fp_bmp = _wfopen(mpInstance->m_CurFileName, L"rb");
	if(fp_bmp == NULL)
	{
		return FALSE;
	}

	*pwidth  = WINDOW_W;
	*pheight = WINDOW_H;

	outputSize = (*pwidth * *pheight)+(*pwidth * *pheight)/2;
	LCDbuf = new unsigned char[outputSize];

	bh = TCCXXX_BMP_Init(fp_bmp, BMP_callbacks_init, *pheight, *pwidth);

	if(bh == NULL)
	{
		printf("Not Support from BMP Decoder!!");
		ret_dec = FALSE;
		goto finish;
	}

	BMP_FILE_BUF = new unsigned char[outputSize];
	//memset(BMP_FILE_BUF, 0, outputSize);//;bh->width);
	memset(BMP_FILE_BUF , 0, ((*pwidth) * (*pheight)));
	memset(BMP_FILE_BUF+((*pwidth) * (*pheight)), 0x80, ((*pwidth)*(*pheight))>>1);	
		
	PNG_IM_LCD_Addr = (unsigned int)LCDbuf;	
	memset((void *)PNG_IM_LCD_Addr , 0, ((*pwidth) * (*pheight)));
	memset((void *)(PNG_IM_LCD_Addr+((*pwidth) * (*pheight))), 0x80, ((*pwidth)*(*pheight))>>1);	
	
	PNG_IM_2nd_Offset = WINDOW_W * WINDOW_H;
	PNG_IM_3rd_Offset = PNG_IM_2nd_Offset+(PNG_IM_2nd_Offset>>2);
	PNG_IM_LCD_Half_Stride = WINDOW_W>>1;

	ret_val=1;
	while(ret_val)
	{
		ret_val = TCCXXX_BMP_Decode(BMP_callbacks_decode,(unsigned int *)BMP_FILE_BUF);
		if(ret_val < 0)
		{
			ret_dec = FALSE;
			goto finish;
		}
	}
#if 0
	FILE *fp;	
	fp=fopen("/NAND/Dump_bmpdecoder.yuv","wb");
	fwrite((void *)LCDbuf, outputSize, 1, fp);
	fclose(fp);
#endif

	memcpy(pdst, (void *)LCDbuf, outputSize);
	ret_dec = TRUE;

finish:
	if(LCDbuf){
		delete [] LCDbuf;
		LCDbuf = NULL;
	}
	if(BMP_FILE_BUF){
		delete [] BMP_FILE_BUF;
		BMP_FILE_BUF = NULL;
	}

	if(fp_bmp){
		fclose(fp_bmp);
		fp_bmp = NULL;
	}

    return ret_dec;
}

#define PNG_BUF_SIZE (WINDOW_W * WINDOW_H * 4)

BOOL CEffect::PNGDecoder(unsigned char *pdst, unsigned int *pwidth, unsigned int *pheight)
{
	BOOL ret_dec;

	FILE *fp_png = NULL;
	unsigned int uiTotFileSize;

	int ret_value;
	
	uint32 PNG_width;
	uint32 PNG_height;
	uint32 PNG_Alpha;
	uint32 heap_size;

	unsigned char* OutBuff;
	PD_CUSTOM_DECODE output_setting;
	
	unsigned char * pHeapBuf;
	char * pInstanceMem;
	
	PD_INIT *pPD_init_Mem;
//	PD_CALLBACKS callbacks = {(int (*)(void *, int, int, void *))fread};
	PD_CALLBACKS callbacks = {(size_t (*)(void *, size_t, size_t, void *))fread};
	memset( &output_setting, 0, sizeof(PD_CUSTOM_DECODE) );

	fp_png = _wfopen(mpInstance->m_CurFileName, L"rb");
	if(fp_png == NULL)
	{
		ret_dec = FALSE;
		goto finish;
	}

	fseek(fp_png, 0, SEEK_SET);
	fseek(fp_png, 0, SEEK_END);
	uiTotFileSize = ftell(fp_png); //V1.65
	fseek(fp_png, 0, SEEK_SET);
	
	pInstanceMem = (char *)new unsigned char[PD_INSTANCE_MEM_SIZE];
	if( pInstanceMem == NULL ) {
		ret_dec = FALSE;
		goto finish;
	}
	memset( pInstanceMem, 0, PD_INSTANCE_MEM_SIZE );

	pPD_init_Mem = (PD_INIT *)new unsigned char[sizeof(PD_INIT)];
	if( pPD_init_Mem == NULL ) {
		ret_dec = FALSE;
		goto finish;
	}
	memset( pPD_init_Mem, 0, sizeof(PD_INIT) );

	*pwidth  = WINDOW_W;
	*pheight = WINDOW_H;

	pPD_init_Mem->pInstanceBuf = pInstanceMem;
	pPD_init_Mem->datasource = (void *)fp_png;
	pPD_init_Mem->lcd_width = WINDOW_W;
	pPD_init_Mem->lcd_height = WINDOW_H;
	pPD_init_Mem->iTotFileSize = uiTotFileSize;			//V1.65

	ret_value = TCCXXX_PNG_Decode( PD_DEC_INIT, pPD_init_Mem, &callbacks, 0 );
	if(ret_value == PD_RETURN_INIT_FAIL) {
		printf("[PD_DEC_INIT] Initialization Failure\n");
		ret_dec = FALSE;
		goto finish;
	}

	PNG_width  = pPD_init_Mem->image_width;
	PNG_height = pPD_init_Mem->image_height;
	PNG_Alpha  = pPD_init_Mem->alpha_available;
	heap_size  = pPD_init_Mem->heap_size;

	OutBuff = new unsigned char[PNG_BUF_SIZE];
	PNG_IM_LCD_Addr = (int32)OutBuff;

	output_setting.ERROR_DET_MODE = PD_ERROR_CHK_NONE;

	output_setting.RESOURCE_OCCUPATION = PD_RESOURCE_LEVEL_NONE;

	output_setting.write_func = (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_YUV420;//PNG_TCC_CustomOutput_RGB565;//PNG_TCC_CustomOutput_YUV420;
	if(output_setting.write_func == PNG_TCC_CustomOutput_YUV420)
	{
		memset((void *)PNG_IM_LCD_Addr , 0, ((*pwidth) * (*pheight)));
		memset((void *)(PNG_IM_LCD_Addr+((*pwidth) * (*pheight))), 0x80, ((*pwidth)*(*pheight))>>1);	

		PNG_IM_2nd_Offset = WINDOW_W * WINDOW_H;
		PNG_IM_3rd_Offset = PNG_IM_2nd_Offset+(PNG_IM_2nd_Offset>>2);
		PNG_IM_LCD_Half_Stride = WINDOW_W>>1;
	}
	else
	{
		memset((void *)PNG_IM_LCD_Addr, 0, PNG_BUF_SIZE);
	}

	pHeapBuf = (unsigned char *)new uint32[heap_size];
	if( pHeapBuf == NULL ) {
		ret_dec = FALSE;
		goto finish;
	}
	memset(pHeapBuf, 0, heap_size);
	output_setting.Heap_Memory = pHeapBuf;	

	output_setting.MODIFY_IMAGE_POS = 0;
	if(output_setting.MODIFY_IMAGE_POS ) {
		output_setting.IMAGE_POS_X = 310;
		output_setting.IMAGE_POS_Y = 230;
	}

	output_setting.USE_ALPHA_DATA = PD_ALPHA_DISABLE;
	if(0)//PNG_Alpha == PD_ALPHA_AVAILABLE)
	{
		printf("PD_ALPHA_AVAILABLE\n");
		output_setting.USE_ALPHA_DATA = PD_ALPHA_AVAILABLE;
		output_setting.write_func = (void (*)(PNG_IM_PIX_INFO))PNG_TCC_CustomOutput_RGB888_With_Alpha;
	}

	ret_value = 1;
	while(ret_value > 0)
	{
		ret_value = TCCXXX_PNG_Decode( PD_DEC_DECODE, &output_setting, 0, 0 );
	}

	if(ret_value == PD_RETURN_DECODE_DONE) {
		/*
		FILE *out_fp;	
		out_fp=fopen("/NAND/Dump_pngdecoder.yuv","wb");
		fwrite((void *)PNG_IM_LCD_Addr, PNG_BUF_SIZE, 1, out_fp);
		fclose(out_fp);
		*/
	}
	else 
	{
		printf(" Decoding Failure [Error_code: %d]!!!\n", ret_value);
	}
	
	memcpy(pdst, (void *)PNG_IM_LCD_Addr,(WINDOW_W * WINDOW_H*3/2) );
	ret_dec = TRUE;

finish:
	if(OutBuff != NULL) {
		delete [] OutBuff;
		OutBuff = NULL;
	}	
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
	if(fp_png){
		fclose(fp_png);
		fp_png = NULL;
	}

    return ret_dec;
}

int CEffect::CheckEffectFileIndex()
{
	return (m_FileIndex - 1);
}

void CEffect::SetSelectedFile(int iFileIndex)
{
	printf("CEffect Set[WINDOW_W : %d, WINDOW_H : %d]\r\n", WINDOW_W, WINDOW_H);

	if(m_Format == FORMAT_RGB565)
	{
		memset(m_pSrcBuffer[0], 0, WINDOW_W*WINDOW_H*2);
		memset(m_pSrcBuffer[1], 0, WINDOW_W*WINDOW_H*2);
		memset(m_pEffectBuffer, 0, WINDOW_W*WINDOW_H*2);
	}
	else	// FORMAT_YUV420
	{		
		memset(m_pSrcBuffer[0], 0, WINDOW_W*WINDOW_H);
		memset(m_pSrcBuffer[0]+WINDOW_W*WINDOW_H, 0x80, (WINDOW_W*WINDOW_H)>>1);
		memset(m_pSrcBuffer[1], 0, WINDOW_W*WINDOW_H);
		memset(m_pSrcBuffer[1]+WINDOW_W*WINDOW_H, 0x80, (WINDOW_W*WINDOW_H)>>1);
		memset(m_pEffectBuffer, 0, WINDOW_W*WINDOW_H);
		memset(m_pEffectBuffer+WINDOW_W*WINDOW_H, 0x80, (WINDOW_W*WINDOW_H)>>1);
	}

	m_BaseIndex = 0;
	m_FileIndex = iFileIndex;
	m_NextFileIndex = iFileIndex;
}

void CEffect::SetEffect()
{
	::EnterCriticalSection(&m_CS);
	
	unsigned int width, height;

	if(m_pSrcBuffer[0] == NULL || m_pEffectBuffer == NULL)
		return ;

	//m_CurFileName = m_pImageFileCont->GetFileName(m_FileIndex);
	// 得到文件名
	DecoderType type = CheckImageType(m_CurFileName);
	if(type < TYPE_MAX)
	{
		if( DecodePFn[type](m_pSrcBuffer[0], &width,&height) == FALSE)
			return;
	}
	else
		return;

	EffectParamSet(NULL);

	if(EffectImage() == TRUE)
	{
		ReDraw();
	}

	::LeaveCriticalSection(&m_CS);
}

void CEffect::SetSlideShow(BOOL repeat, int duration)
{
	::EnterCriticalSection(&m_CS);
	
	if(m_pImageDecoder == NULL)
	{
		printf("SetSlideShow is Fail(line %d)\r\n", __LINE__);
		return;
	}

	if(m_pSrcBuffer[0] == NULL || m_pSrcBuffer[1] == NULL || m_pEffectBuffer == NULL)
	{
		printf("SetSlideShow is Fail(line %d)\r\n", __LINE__);
		return;
	}

	////////////////////////////
	m_TransitionTime	= 50;
	switch(duration)
	{
		case 0: //1sec
			m_SlideTime			= 3000;
			break;

		case 1: //5sec
			m_SlideTime			= 5000;
			break;

		case 2:	//7sec
			m_SlideTime			= 7000;
			break;

		case 3:	//10sec
			m_SlideTime			= 10000;
			break;

		case 4:	//15sec
			m_SlideTime			= 15000;
			break;

		default:
			m_SlideTime			= 5000;
			break;
	}
	
	m_bRepeat = repeat;
	////////////////////////////

	m_bEffectProcess = TRUE;
	m_bIsTransition = FALSE;

	::SetEvent(m_hEventDecode[0]);

	::LeaveCriticalSection(&m_CS);
}

BOOL CEffect::EffectParamSet(IMAGE_EFFECT_INFO *EffectInfo)
{
	unsigned long EffectID = NEXIMAGE_EFFECTID_WIND_DISTORTION;
	switch(EffectID)
	{
	case NEXIMAGE_EFFECTID_GAUSSIAN:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = 0;
			m_EffectParam.ulFilterSize = 3;	//constant 3
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;
		}
		break;

	case NEXIMAGE_EFFECTID_MEAN:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = 0;
			m_EffectParam.ulFilterSize = 3;	//constant 3
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;
		}
		break;

	case NEXIMAGE_EFFECTID_WIND_BLUR:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = NEXIMAGE_EFFECTDIRECTION_RIGHT;	// right or left
			m_EffectParam.ulFilterSize = 3;	// range : 1 ~ 6
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;
		}
		break;

	case NEXIMAGE_EFFECTID_MEDIAN:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = 0;
			m_EffectParam.ulFilterSize = 3;	//constant 3
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;
		}
		break;

	case NEXIMAGE_EFFECTID_SHARPEN:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = 0;
			m_EffectParam.ulFilterSize = 3;	//constant 3
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;
		}
		break;

	case NEXIMAGE_EFFECTID_SOBEL:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = NEXIMAGE_SOBELOPFLAG_FORCEBINARY;
			m_EffectParam.ulDirection = 0;
			m_EffectParam.ulFilterSize = 3;	//constant 3
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 128;	// if ulOpFlags vaule is NEXIMAGE_SOBELOPFLAG_FORCEBINARY, range : 0 ~ 255
		}
		break;

	case NEXIMAGE_EFFECTID_WIND_DISTORTION:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = NEXIMAGE_EFFECTDIRECTION_RIGHT;	// right or left
			m_EffectParam.ulFilterSize = 0;
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;
		}
		break;

	case NEXIMAGE_EFFECTID_SPHERIZE:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = 0;
			m_EffectParam.ulFilterSize = 0;
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;	// Convex(0 < value < 512), No Effect(0), Concave( -512 < value < 0)
		}
		break;

	case NEXIMAGE_EFFECTID_THIN:
		{
			m_EffectParam.ulEffectID = EffectID;
			m_EffectParam.ulOpFlags = 0;
			m_EffectParam.ulDirection = NEXIMAGE_EFFECTDIRECTION_HORIZONTAL;	// horizontal or vertical
			m_EffectParam.ulFilterSize = 0;
			m_EffectParam.ulColor = 0;
			m_EffectParam.lValue = 0;	// range : 1 ~ 256
		}
		break;
	}
	
	return TRUE;
}

BOOL CEffect::EffectImage()
{
	NEXIMAGEIMG Src, Dst;
	
	if(m_Format == FORMAT_RGB565)
	{
		Src.Channel1.pRGB = m_pSrcBuffer[0];
		Src.iWidth = WINDOW_W;
		Src.iHeight = WINDOW_H;
		Src.iYPitch = Src.iWidth * 2;
		Src.iUVPitch = Src.iWidth >> 1;
		Src.ulFormat = NEXIMAGE_PIXELFORMAT_RGB565;

		Dst.Channel1.pRGB = m_pEffectBuffer;
		Dst.iWidth = WINDOW_W;
		Dst.iHeight = WINDOW_H;
		Dst.iYPitch = Dst.iWidth * 2;
		Dst.iUVPitch = Dst.iWidth >> 1;
		Dst.ulFormat = NEXIMAGE_PIXELFORMAT_RGB565;
	}
	else
	{
		Src.Channel1.pY = m_pSrcBuffer[0];
		Src.Channel2.pU = Src.Channel1.pY + (WINDOW_W * WINDOW_H);
		Src.Channel3.pV = Src.Channel2.pU + (WINDOW_W * WINDOW_H)/4;
		Src.iWidth = WINDOW_W;
		Src.iHeight = WINDOW_H;
		Src.iYPitch = Src.iWidth;
		Src.iUVPitch = Src.iWidth >> 1;
		Src.ulFormat = NEXIMAGE_PIXELFORMAT_YUV420_256;

		Dst.Channel1.pY = m_pEffectBuffer;
		Dst.Channel2.pU = Dst.Channel1.pY + (WINDOW_W  * WINDOW_H);
		Dst.Channel3.pV = Dst.Channel2.pU + (WINDOW_W  * WINDOW_H)/4;
		Dst.iWidth = WINDOW_W;
		Dst.iHeight = WINDOW_H;
		Dst.iYPitch = Dst.iWidth;
		Dst.iUVPitch = Dst.iWidth >> 1;
		Dst.ulFormat = NEXIMAGE_PIXELFORMAT_YUV420_256;
	}
	
	NEXIMAGEERR ret = NexImage_Effect(&Dst, &Src, &m_EffectParam);
	if(ret != NEXIMAGEERR_OK)
		return FALSE;
	else
		return TRUE;
}

BOOL CEffect::TransitionParamSet(IMAGE_EFFECT_INFO *EffectInfo)
{
	unsigned int TransitionID = Random() % (NEXIMAGE_TRANSITIONID_MAX);
	unsigned int DirectionCode = Random() % (NEXIMAGE_TRANSITIONDIRECTION_LEFTUP + 1);
	unsigned int DirectionFlags = Random() % (NEXIMAGE_TRANSITIONDIRECTION_COUNTERCLOCKWISE + 1);
	unsigned int Shape = Random() % (NEXIMAGE_TRANSITIONSHAPE_PLUS + 1);
	
	switch(TransitionID)
	{
	case NEXIMAGE_TRANSITIONID_BLIND:
		{
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = ((DirectionFlags >> 4) & NEXIMAGE_TRANSITIONDIRECTION_VERTICAL);	// horizontal, virtical
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 6;
			m_TransitionParam.ulValue = 0;
		}
		break;
		
	case NEXIMAGE_TRANSITIONID_COVER:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = DirectionCode;	// up, rightup, right, rightdown, down, leftdown, left, leftup
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_UNCOVER:
		{
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = DirectionCode;	// up, rightup, right, rightdown, down, leftdown, left, leftup
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_RANDOM:
		{
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = ((DirectionFlags >> 4) & NEXIMAGE_TRANSITIONDIRECTION_VERTICAL);	// horizontal, virtical
			m_TransitionParam.ulShape = (Shape % 2);	// dot, bar
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 100;	// seed value
		}
		break;

	case NEXIMAGE_TRANSITIONID_FADEWITHBLACK:
		{
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_OVERLAP:
		{
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_WIPE:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = DirectionCode;	// up, rightup, right, rightdown, down, leftdown, left, leftup
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_BOX:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = ((DirectionFlags >> 5) & NEXIMAGE_TRANSITIONDIRECTION_OUTSIDE);	// inside, outside
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_CHECKERBOARD:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = ((DirectionFlags >> 4) & NEXIMAGE_TRANSITIONDIRECTION_VERTICAL);	// horizontal, virtical
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 5;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_COMB:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = ((DirectionFlags >> 4) & NEXIMAGE_TRANSITIONDIRECTION_VERTICAL);	// horizontal, virtical
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 8;
			m_TransitionParam.ulValue = 0;
		}
		break;
		
	case NEXIMAGE_TRANSITIONID_PUSH:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = (NEXIMAGE_TRANSITIONDIRECTION_LEFT >> 1) << 1;	// up, right, down, left
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;
		
	case NEXIMAGE_TRANSITIONID_SPLIT:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = ((DirectionFlags >> 4) & NEXIMAGE_TRANSITIONDIRECTION_VERTICAL) | ((DirectionFlags >> 5) & NEXIMAGE_TRANSITIONDIRECTION_OUTSIDE);	// (horizontal , vertical) | (inside | outside)
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;
		
	case NEXIMAGE_TRANSITIONID_STRIPS:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = ((NEXIMAGE_TRANSITIONDIRECTION_RIGHTDOWN >> 1) << 1) + 1;	// rightup, rightdown, leftdown, leftup
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 10;
			m_TransitionParam.ulValue = 0;
		}
		break;
		
	case NEXIMAGE_TRANSITIONID_WEDGE:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;
		
	case NEXIMAGE_TRANSITIONID_WHEEL:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = ((DirectionFlags >> 6) & NEXIMAGE_TRANSITIONDIRECTION_CLOCKWISE);//NEXIMAGE_TRANSITIONDIRECTION_COUNTERCLOCKWISE);	// clockwise, counterclockwise
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 1;
			m_TransitionParam.ulValue = 0;
		}
		break;
		
	case NEXIMAGE_TRANSITIONID_SHAPE:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = Shape / 2 + 3;	// circle, diamond, plus
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 0;
		}
		break;

	case NEXIMAGE_TRANSITIONID_NEWFLASH:
		{			
			m_TransitionParam.ulEffectID = TransitionID;
			m_TransitionParam.ulOpFlags = NEXIMAGE_TRANSITIONOPFLAG_NORMAL;
			m_TransitionParam.ulDirectionCode = 0;
			m_TransitionParam.ulDirectionFlags = 0;
			m_TransitionParam.ulShape = 0;
			m_TransitionParam.ulDivisionCount = 0;
			m_TransitionParam.ulValue = 1;
		}
		break;

	}

	m_TransitionNumber = 12;
	m_TransitionCount = 0;

	return TRUE;
}

BOOL CEffect::TransitionImage()
{
	unsigned char *pSrc1, *pSrc2, *pDst;	
	if(m_BaseIndex == 0)
	{
		pSrc1 = m_pSrcBuffer[0];
		pSrc2 = m_pSrcBuffer[1];
		pDst = m_pEffectBuffer;
	}
	else
	{
		pSrc1 = m_pSrcBuffer[1];
		pSrc2 = m_pSrcBuffer[0];
		pDst = m_pEffectBuffer;
	}

	NEXIMAGEIMG Src1, Src2, Dst;
	if(m_Format == FORMAT_RGB565)
	{		
		Src1.Channel1.pRGB = pSrc1;
		Src1.iWidth = WINDOW_W;
		Src1.iHeight = WINDOW_H;
		Src1.iYPitch = Src1.iWidth * 2;
		Src1.iUVPitch = Src1.iWidth >> 1;
		Src1.ulFormat = NEXIMAGE_PIXELFORMAT_RGB565;

		Src2.Channel1.pY = pSrc2;
		Src2.iWidth = WINDOW_W;
		Src2.iHeight = WINDOW_H;
		Src2.iYPitch = Src2.iWidth * 2;
		Src2.iUVPitch = Src2.iWidth >> 1;
		Src2.ulFormat = NEXIMAGE_PIXELFORMAT_RGB565;

		Dst.Channel1.pY = pDst;
		Dst.iWidth = WINDOW_W;
		Dst.iHeight = WINDOW_H;
		Dst.iYPitch = Dst.iWidth * 2;
		Dst.iUVPitch = Dst.iWidth >> 1;
		Dst.ulFormat = NEXIMAGE_PIXELFORMAT_RGB565;
	}
	else
	{
		Src1.Channel1.pY = pSrc1;
		Src1.Channel2.pU = Src1.Channel1.pY + (WINDOW_W * WINDOW_H);
		Src1.Channel3.pV = Src1.Channel2.pU + ((WINDOW_W * WINDOW_H) / 4);
		Src1.iWidth = WINDOW_W;
		Src1.iHeight = WINDOW_H;
		Src1.iYPitch = Src1.iWidth;
		Src1.iUVPitch = Src1.iWidth >> 1;
		Src1.ulFormat = NEXIMAGE_PIXELFORMAT_YUV420_256;

		Src2.Channel1.pY = pSrc2;
		Src2.Channel2.pU = Src2.Channel1.pY + (WINDOW_W * WINDOW_H);
		Src2.Channel3.pV = Src2.Channel2.pU + ((WINDOW_W * WINDOW_H) / 4);
		Src2.iWidth = WINDOW_W;
		Src2.iHeight = WINDOW_H;
		Src2.iYPitch = Src2.iWidth;
		Src2.iUVPitch = Src2.iWidth >> 1;
		Src2.ulFormat = NEXIMAGE_PIXELFORMAT_YUV420_256;

		Dst.Channel1.pY = pDst;
		Dst.Channel2.pU = Dst.Channel1.pY + (WINDOW_W * WINDOW_H);
		Dst.Channel3.pV = Dst.Channel2.pU + ((WINDOW_W * WINDOW_H) / 4);
		Dst.iWidth = WINDOW_W;
		Dst.iHeight = WINDOW_H;
		Dst.iYPitch = Dst.iWidth;
		Dst.iUVPitch = Dst.iWidth >> 1;
		Dst.ulFormat = NEXIMAGE_PIXELFORMAT_YUV420_256;
	}

	NEXIMAGEERR ret = NexImage_Transition(&Dst, &Src1, &Src2, &m_TransitionParam, m_TransitionCount++, m_TransitionNumber);
	if(ret != NEXIMAGEERR_OK)
		return FALSE;
	else
		return TRUE;
}

DWORD CEffect::Run()
{
	HANDLE hEvents[3]={m_hEventThreadExit, m_hEventDecode[0], m_hEventDecode[1]};
	while(1)
	{
		DWORD object = ::WaitForMultipleObjects(3, hEvents, FALSE, INFINITE);		
		if(object == WAIT_OBJECT_0)
		{
			break;
		}

		if(m_bEffectProcess == FALSE)
		{
			continue;
		}
		
		::EnterCriticalSection(&m_CS);		
		
		if(object == WAIT_OBJECT_0 + 1)
		{
			DecoderType type;
			//////do
			//////{
			//////	m_FileIndex = m_NextFileIndex;
			//////	//m_FileName[0] = m_pImageFileCont->GetFileName(m_FileIndex);
			//////	//m_FileName[0] = m_pImageFileCont->GetFullName(m_FileIndex);
			//////	// 得到文件名
			//////	if(m_bShuffle == TRUE)
			//////	{
			//////		/*
			//////		*/
			//////	}
			//////	else
			//////	{
			//////		m_NextFileIndex = m_FileIndex + 1;
			//////	}

			//////	type = CheckImageType(m_FileName[0]);
			//////	if(type < TYPE_MAX)
			//////		break;
			//////	else
			//////		m_FileName[0].Empty();

			//////	if((m_bShuffle==FALSE)&&(m_bRepeat==TRUE)&&(m_NextFileIndex == m_pImageFileCont->GetNum()+1))
			//////	{
			//////		m_NextFileIndex = 0;
			//////	}
			//////}while(m_NextFileIndex <= m_pImageFileCont->GetNum());
			
			m_FileName[0] = GetNextFile();

			//////if(m_NextFileIndex > m_pImageFileCont->GetNum())
			//////{				
			//////	// end of slide show
			//////	if(m_bShuffle==FALSE)
			//////		m_FileIndex = m_pImageFileCont->GetNum();

			//////	::LeaveCriticalSection(&m_CS);
			//////	OnCmdExit(FALSE);
			//////}
			if (m_FileName[0] == _T("LAST"))
			{
				// end of slide show
			}

			if(m_FileName[0].GetLength())
			{
				m_CurFileName = m_FileName[0];
				wprintf(_T("m_FileIndex : %d, szCurFileName : %s\r\n"), m_FileIndex, m_CurFileName);
				
				unsigned int width, height;
				if( DecodePFn[type](m_pSrcBuffer[0], &width,&height) == FALSE)
				{
					::SetEvent(m_hEventDecode[0]);		// retry other image decode
				}
				else
				{
					if(m_BaseIndex == 0)
					{
						::SetEvent(m_hEventDecode[1]);	// decode next image
					}
					else
					{
						if(m_bIsTransition == FALSE)
						{
							m_bIsTransition = TRUE;
							//::SetTimer(m_hWnd, TIMER_DECODE, 0, NULL);
							::SetTimer(m_hWnd, TIMER_DECODE, m_SlideTime, NULL);
						}
					}
				}
			}			
		}			
		else if(object == WAIT_OBJECT_0 + 2)
		{
			DecoderType type;
			////////do
			////////{
			////////	m_FileIndex = m_NextFileIndex;
			////////	//m_FileName[1] = m_pImageFileCont->GetFileName(m_FileIndex);
			////////	//m_FileName[1] = m_pImageFileCont->GetFullName(m_FileIndex);
			////////	// 得到文件名2
			////////	if(m_bShuffle == TRUE)
			////////	{
			////////		/*
			////////		*/
			////////	}
			////////	else
			////////	{
			////////		m_NextFileIndex = m_FileIndex + 1;
			////////	}

			////////	type = CheckImageType(m_FileName[1]);
			////////	if(type < TYPE_MAX)
			////////		break;
			////////	else
			////////		m_FileName[1].Empty();

			////////	if((m_bShuffle==FALSE)&&(m_bRepeat==TRUE)&&(m_NextFileIndex == m_pImageFileCont->GetNum()+1))
			////////	{
			////////		m_NextFileIndex = 0;
			////////	}
			////////}while(m_NextFileIndex <= m_pImageFileCont->GetNum());

			m_FileName[0] = GetNextFile();

			////////if(m_NextFileIndex > m_pImageFileCont->GetNum())
			////////{
			////////	// end of slide show
			////////	if(m_bShuffle==FALSE)
			////////		m_FileIndex = m_pImageFileCont->GetNum();

			////////	::LeaveCriticalSection(&m_CS);
			////////	OnCmdExit(FALSE);
			////////}

			if (m_FileName[0] == _T("LAST"))
			{
				// end of slide show
			}

			if(m_FileName[1].GetLength())
			{
				m_CurFileName = m_FileName[1];
				wprintf(_T("m_FileIndex : %d, szCurFileName : %s\r\n"), m_FileIndex, m_CurFileName);
								
				unsigned int width, height;
				if( DecodePFn[type](m_pSrcBuffer[1], &width,&height) == FALSE)
				{
					::SetEvent(m_hEventDecode[1]);		// retry other image decode
				}
				else
				{
					if(m_BaseIndex == 0)
					{
						if(m_bIsTransition == FALSE)
					{
							m_bIsTransition = TRUE;
							//::SetTimer(m_hWnd, TIMER_DECODE, 0, NULL);
							::SetTimer(m_hWnd, TIMER_DECODE, m_SlideTime, NULL);
						}
					}
					else
						::SetEvent(m_hEventDecode[0]);	// decode next image
					}
				}
			}
		
		::LeaveCriticalSection(&m_CS);
	}
	
	return 0;
}
