/******************************************************************************
*
*  (C)Copyright All Rights Reserved by Telechips Inc.
*                                   
*  This material is confidential and shall remain as such. 
*  Any unauthorized use, distribution, reproduction is strictly prohibited. 
*
*   FileName    : TCC89X_HW_JPG_Decode.cpp
*   Description : 
*   TCC Version 1.0
*   Copyright (c) Telechips, Inc.
*   ALL RIGHTS RESERVED
*******************************************************************************/

//#include "base.h"
#include "Main.h"
#include "TCC89X_HW_JPG_Decode.h"
#include "StdAfx.h"
//#define __REASSIGNED__

#ifdef HWJPGDEC_ENABLE
CTCC89HWJPGDecode::CTCC89HWJPGDecode()
{
	mpJpegHwStr = NULL;
	mpScaleMem = NULL;
	m_bHWJPGImage = 0;

	m_hFile = NULL;
	bHWJPGErrStatus = TRUE;
	bHWJPGSetRotate = FALSE;
	iHWJPGAngle = DMA2D_NO_OPERATION;
	bSWDrawValue = FALSE;
}

CTCC89HWJPGDecode::~CTCC89HWJPGDecode()
{
	if(mpJpegHwStr)
	{
		if(mpJpegHwStr->jpegin.handle)
			fclose(mpJpegHwStr->jpegin.handle);
		
		delete [] mpJpegHwStr;
		mpJpegHwStr = NULL;
	}

	if(mpScaleMem)
	{
		if(mpScaleMem->VirAddr)
			VirtualFree((LPBYTE)mpScaleMem->VirAddr,0,MEM_RELEASE);
		
		delete [] mpScaleMem;
		mpScaleMem = NULL;
	}
}

unsigned int CTCC89HWJPGDecode::PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	RETAILMSG(1, (TEXT("21-----------\r\n")));
	if(mpJpegHwStr)
	{
		if(mpJpegHwStr->jpegin.handle)
			fclose(mpJpegHwStr->jpegin.handle);
	
		delete [] mpJpegHwStr;
		mpJpegHwStr = NULL;
	}
	RETAILMSG(1, (TEXT("22-----------\r\n")));
	dHWRatioZoom = 1.0;
	bHWJPGSetRotate	= FALSE;
	dHWFitRatioZoom	=1.0;
	iHWJPGAngle = DMA2D_NO_OPERATION;
	bSWDrawValue = FALSE;
	m_csFileName = szFileName;    

	mpJpegHwStr = new jpeg89hwStr;
	RETAILMSG(1, (TEXT("23-----------\r\n")));

	memset(mpJpegHwStr,0x00,sizeof(jpeg89hwStr));
	RETAILMSG(1, (TEXT("24-----------\r\n")));

	mpJpegHwStr->jpegin.handle = _wfopen(szFileName, L"rb");
	RETAILMSG(1, (TEXT("25-----------\r\n")));

	if(mpJpegHwStr->jpegin.handle == NULL)
	{
		m_pSrcSize = 0;
	    return 0;
	}
	else
	{
		m_pSrcSize = 1;
	    return 1;
    }
}

BOOL CTCC89HWJPGDecode::DecodeImage(unsigned int *pResultSize, unsigned int Index)
{
	FILE *infile = mpJpegHwStr->jpegin.handle;
	unsigned int dec_o_width;
	unsigned int dec_o_height;
	unsigned int dec_format;
	unsigned int m_HDMI_INCLUDE_Condition=0;

	RETAILMSG(1, (TEXT("31-----------\r\n")));
	if(m_pYUVRenderer == NULL || m_pYUVRenderer->m_pVideoStartMem == 0)
	{
		printf("Can't get a decoding start address\r\n");
		return FALSE;
	}

	RETAILMSG(1,(TEXT("m_pVideoStartMem = 0x%x\r\n"), m_pYUVRenderer->m_pVideoStartMem));

	/* set dec component para */
	Jpeg_Ip_Info_Init(m_pYUVRenderer->m_pVideoStartMem);
	RETAILMSG(1, (TEXT("32-----------\r\n")));
    fseek(infile,0,0);
	RETAILMSG(1, (TEXT("33-----------\r\n")));
#ifdef __HDMI_INCLUDE__
	m_HDMI_INCLUDE_Condition = 1;
#endif

	/* TC89XX_JPGDEC_Init */
	if(!Jpeg_Ip_Decoder_Init(infile,(int*)&mpJpegHwStr->jpegout.width,(int*)&mpJpegHwStr->jpegout.height, (int*)&mpJpegHwStr->jpegin.color_format, m_HDMI_INCLUDE_Condition))
	{
		Jpeg_Ip_Info_DeInit();
		printf(" [ERROR] HWJPG_TCC89x::Jpeg_Ip_Decoder_Init \n");
		return 0;
	}
	/* Get Out Physical Buffer (YUV420)*/
	RETAILMSG(1, (TEXT("34-----------\r\n")));
	if(mpScaleMem)
	{
		if(mpScaleMem->VirAddr)
			VirtualFree((LPBYTE)mpScaleMem->VirAddr,0,MEM_RELEASE);
		
		delete [] mpScaleMem;
		mpScaleMem = NULL;
	}
	RETAILMSG(1, (TEXT("35-----------\r\n")));
	mpScaleMem = new Jpeg_Ip_Memory_Structure_Element;

	dec_o_width = mpJpegHwStr->jpegout.width;
	dec_o_height = mpJpegHwStr->jpegout.height;
	dec_format = mpJpegHwStr->jpegin.color_format;
	RETAILMSG(1, (TEXT("36-----------\r\n")));
	if(Jpeg_Ip_Info_Set_Mem_Scale_Out(mpScaleMem, dec_o_width*dec_o_height*1.5) != JPEG_IP_ERROR_NONE)
	{
		ReleaseResource();
		Jpeg_Ip_Info_DeInit();
		printf(" [ERROR] JPEGIP_ERROR_DECOUT_BUF \n");
		return FALSE;
	}
	RETAILMSG(1, (TEXT("37-----------\r\n")));
	/********************************/
	/* TC89XX_JPGDEC Deocde */			
	if(!Jpeg_Ip_Decode(0, mpScaleMem->PhyAddr, &dec_o_width, &dec_o_height)){
		ReleaseResource();
		Jpeg_Ip_Info_DeInit();
		printf(" [ERROR] JPEGIP_ERROR_DEC \n");								
		return FALSE;
	}
	RETAILMSG(1, (TEXT("38-----------\r\n")));
	//printf("dec_o_width : %d, dec_o_height : %d, format : %d\r\n", dec_o_width, dec_o_height, dec_format);
	if(0)
	{
		FILE *fp =fopen("nand\\dec_out.raw", "wb");
		if(mpScaleMem->VirAddr)
			fwrite((void*)mpScaleMem->VirAddr, 1,dec_o_width*dec_o_height*1.5, fp);
		fclose(fp);
	}

	fclose(mpJpegHwStr->jpegin.handle);
	mpJpegHwStr->jpegin.handle = NULL;
	
    m_Width = dec_o_width;
	m_Height = dec_o_height;

	m_bHWJPGImage = TRUE;

	jdSIZE decodedSize;
	jdSIZE decodedPadSize;

	decodedSize.cx = dec_o_width;
	decodedSize.cy = dec_o_height;

	decodedPadSize.cx = dec_o_width;
	decodedPadSize.cy = dec_o_height;

	rendSrcOriginalSize.cx = decodedSize.cx;
	rendSrcOriginalSize.cy = decodedSize.cy;
	rendSrcPadSize.cx = decodedPadSize.cx;
	rendSrcPadSize.cy = decodedPadSize.cy;

	srcRenderCenterPt.x = rendSrcOriginalSize.cx / 2;
	srcRenderCenterPt.y = rendSrcOriginalSize.cy / 2;
	RETAILMSG(1, (TEXT("39-----------\r\n")));
	return m_bHWJPGImage;
}

BOOL CTCC89HWJPGDecode::EndDecode()
{
	if(m_pSrcSize)
	{
		//RECT rt = {0, 0, WINDOW_W, WINDOW_H};
		//HDC hdc = ::GetDC(NULL);
		//::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
		//::ReleaseDC(NULL, hdc);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCC89HWJPGDecode::CheckDrawImage()
{	
	return m_bHWJPGImage;
}

void CTCC89HWJPGDecode::ClearDrawImage()
{
	{
		RECT rt = {0, 0, WINDOW_W, WINDOW_H};
		HDC hdc = ::GetDC(NULL);
		::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
		::ReleaseDC(NULL, hdc);
	}
	//m_bHWJPGImage = FALSE;
}

void CTCC89HWJPGDecode::DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff)
{
}

BOOL CTCC89HWJPGDecode::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
{
	int dstWidthInImgCoord;
	int dstHeightInImgCoord;
	POINT MovePt, CenterPt;
	
	if( (bSWDrawValue == FALSE) && ((iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES)||(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES)))
	{
		dstWidthInImgCoord = (dstRect->bottom-dstRect->top);
		dstHeightInImgCoord= (dstRect->right-dstRect->left);

		CenterPt.y = srcRenderCenterPt.x;
		CenterPt.x = srcRenderCenterPt.y;
	}
	else
	{
		dstWidthInImgCoord = (dstRect->right-dstRect->left);
		dstHeightInImgCoord= (dstRect->bottom-dstRect->top);

		CenterPt.x = srcRenderCenterPt.x;
		CenterPt.y = srcRenderCenterPt.y;
	}

	MovePt.x = (max((dstRect->right - WINDOW_W), 0) + min((dstRect->left - 0), 0)) / 2;
	MovePt.y = (max((dstRect->bottom - WINDOW_H), 0) + min((dstRect->top -0), 0)) / 2;

	if(bSWDrawValue == FALSE && iHWJPGAngle == DMA2D_ROTATE_90_DEGREES)
	{
		MovePt.x = CenterPt.x - MovePt.x;
		MovePt.y = CenterPt.y + MovePt.y;
	}
	else if(bSWDrawValue == FALSE && iHWJPGAngle == DMA2D_ROTATE_180_DEGREES)
	{
		MovePt.x = CenterPt.x + MovePt.x;
		MovePt.y = CenterPt.y + MovePt.y;
	}
	else if(bSWDrawValue == FALSE && iHWJPGAngle == DMA2D_ROTATE_270_DEGREES)
	{
		MovePt.x = CenterPt.x + MovePt.x;
		MovePt.y = CenterPt.y - MovePt.y;
	}
	else
	{
		MovePt.x = CenterPt.x - MovePt.x;
		MovePt.y = CenterPt.y - MovePt.y;
	}
    
	if( (bSWDrawValue == FALSE) && ((iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES)||(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES)))
	{
		CalcZoomRatioToFitInScreen(dstWidthInImgCoord,dstHeightInImgCoord,rendSrcOriginalSize,dHWRatioZoom);
	
		if(zoomlevel == 100)
			dHWFitRatioZoom = dHWRatioZoom;

		rendDstRect = CalcRotateDestinationRenderRect(dHWRatioZoom, rendSrcOriginalSize);
		rendSrcRect = CalcRotateSourceRenderRect(dHWRatioZoom, MovePt, rendDstRect, rendSrcOriginalSize);
	}
	else
	{
		CalcZoomRatioToFitInScreen(dstWidthInImgCoord,dstHeightInImgCoord,rendSrcOriginalSize,dHWRatioZoom);
		
		if(zoomlevel == 100)
			dHWFitRatioZoom = dHWRatioZoom;

		rendDstRect = CalcDestinationRenderRect(dHWRatioZoom, rendSrcOriginalSize);
		rendSrcRect = CalcSourceRenderRect(dHWRatioZoom, MovePt, rendDstRect, rendSrcOriginalSize);
	}		
    
	BOOL bZoomAvailableRet = IsMoreZoomInAvailable(rendSrcRect, rendDstRect, 2);
	//printf("bZoomAvailableRet : %d\r\n", bZoomAvailableRet);
	if(bZoomAvailableRet)
	{
		//printf("\t line(%d) rendDstRect(%d,%d,%d,%d)\n", __LINE__, rendDstRect.left, rendDstRect.top, rendDstRect.right, rendDstRect.bottom);
		//printf("\t line(%d) rendSrcRect(%d,%d,%d,%d)\n", __LINE__, rendSrcRect.left, rendSrcRect.top, rendSrcRect.right, rendSrcRect.bottom);

		// add by grt to set image center the window
		int width = rendDstRect.right-rendDstRect.left;
		int height = rendDstRect.bottom-rendDstRect.top;

		if( (bSWDrawValue == FALSE) && ((iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES)||(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES)))
		{
			rendDstRect.top = dstRect->top + ((dstRect->bottom-dstRect->top)-(width))/2;
			rendDstRect.bottom = rendDstRect.top + width;
			rendDstRect.left = dstRect->left + ((dstRect->right-dstRect->left)-(height))/2;
			rendDstRect.right = rendDstRect.left + height;
		}
		else
		{
			rendDstRect.left = dstRect->left + ((dstRect->right-dstRect->left)-(width))/2;
			rendDstRect.right = rendDstRect.left + width;
			rendDstRect.top = dstRect->top + ((dstRect->bottom-dstRect->top)-(height))/2;
			rendDstRect.bottom = rendDstRect.top + height;
		}


		//if (abs(width-(dstRect->right-dstRect->left)) <= abs(height-(dstRect->bottom-dstRect->top)))
		//{
		//	rendDstRect.left = dstRect->left + ;
		//	rendDstRect.right = dstRect->right;
		//	rendDstRect.top = dstRect->top + ((dstRect->bottom-dstRect->top)-(height))/2;
		//	rendDstRect.bottom = rendDstRect.top + height;
		//}
		//else
		//{
		//	rendDstRect.top = dstRect->top;
		//	rendDstRect.bottom = dstRect->bottom;
		//	rendDstRect.left = dstRect->left + ((dstRect->right-dstRect->left)-(width))/2;
		//	rendDstRect.right = rendDstRect.left + width;
		//}
		//---------------------------------------------
		RenderImage(mpScaleMem->PhyAddr, rendSrcOriginalSize, rendSrcPadSize, rendSrcRect, rendDstRect, FALSE);
	}

#ifdef __REASSIGNED__
	if(!((iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES) || (iHWJPGAngle == DMA2D_ROTATE_270_DEGREES)))
    {
        if((dstRect->right-dstRect->left)>(m_pYUVRenderer->m_nDstSizeH))
        {
            dstRect->left +=((dstRect->right-dstRect->left)-(m_pYUVRenderer->m_nDstSizeH))/2;
        }
        else
        {
            dstRect->left-=((m_pYUVRenderer->m_nDstSizeH)-(dstRect->right-dstRect->left))/2;
        }
     	dstRect->top=m_pYUVRenderer->m_nTop;
       
   		dstRect->right=dstRect->left+m_pYUVRenderer->m_nDstSizeH;
   	    dstRect->bottom=dstRect->top+m_pYUVRenderer->m_nDstSizeV;
    }
    else
#endif
    {
    	dstRect->left =m_pYUVRenderer->m_nLeft;
    	dstRect->top=m_pYUVRenderer->m_nTop;
    	if( (iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES) || (iHWJPGAngle == DMA2D_ROTATE_270_DEGREES) )
    	{
    		dstRect->right=m_pYUVRenderer->m_nLeft+m_pYUVRenderer->m_nDstSizeV;
    		dstRect->bottom=m_pYUVRenderer->m_nTop+m_pYUVRenderer->m_nDstSizeH;
    	}
    	else
    	{
    		dstRect->right=m_pYUVRenderer->m_nLeft+m_pYUVRenderer->m_nDstSizeH;
    	    dstRect->bottom=m_pYUVRenderer->m_nTop+m_pYUVRenderer->m_nDstSizeV;
    	}
    }
	
	if(m_pSrcSize)
	{
		HBRUSH hBrush = ::CreateSolidBrush(RGB(16,0,16));
		RECT rt = {dstRect->left,dstRect->top, dstRect->right, dstRect->bottom};//, dstRect->top, dstRect->right, dstRect->bottom);
		::FillRect(hdc, &rt, hBrush);
		::DeleteObject(hBrush);
	}
	return bZoomAvailableRet;
}

BOOL CTCC89HWJPGDecode::RotateImage(FLOAT angle)
{
	iHWJPGAngle = (int)angle;
	
	switch(iHWJPGAngle)
	{
	case 90:
		bHWJPGSetRotate =TRUE;
		iHWJPGAngle = DMA2D_ROTATE_270_DEGREES;
		break;

	case 180:
		bHWJPGSetRotate =TRUE;
		iHWJPGAngle = DMA2D_ROTATE_180_DEGREES;
		break;
		
	case 270:
		bHWJPGSetRotate =TRUE;
		iHWJPGAngle = DMA2D_ROTATE_90_DEGREES;
		break;
		
	case 0:
	default :
		bHWJPGSetRotate =FALSE;
		iHWJPGAngle = DMA2D_NO_OPERATION;
		break;
	}

	//RotateImage_Open();

	mpJpegHwStr->jpegin.handle = _wfopen(m_csFileName, L"rb");

	if(mpJpegHwStr->jpegin.handle == NULL)
	    return 0;
	
	DecodeImage(NULL, 0);
	return TRUE;
}

void CTCC89HWJPGDecode::ReleaseResource(void)
{
	m_bHWJPGImage = FALSE;

	m_pSrcSize = 0;

	if(mpJpegHwStr)
	{
		if(mpJpegHwStr->jpegin.handle)
			fclose(mpJpegHwStr->jpegin.handle);
		
		delete [] mpJpegHwStr;
		mpJpegHwStr = NULL;
	}

	if(mpScaleMem)
	{
		if(mpScaleMem->VirAddr)
			VirtualFree((LPBYTE)mpScaleMem->VirAddr,0,MEM_RELEASE);

		delete [] mpScaleMem;
		mpScaleMem = NULL;
	}
}

BOOL CTCC89HWJPGDecode::IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight)
{
	return FALSE;
}

unsigned int CTCC89HWJPGDecode::CheckDecodingCodecFormat()
{
	return TYPE_TCC89HWJPG;
}

void CTCC89HWJPGDecode::CalcZoomRatioToFitInScreen(int width, int height, const yrSIZE& srcOriginalSize, double& dHWRatioZoom)
{
	float a = (float)width/srcOriginalSize.cx;
	float b = (float)height/srcOriginalSize.cy;
	if( (float)width/srcOriginalSize.cx < (float)height/srcOriginalSize.cy )
		dHWRatioZoom = min(static_cast<double>(width) / srcOriginalSize.cx, ZOOM_IN_LIMIT);
	else
		dHWRatioZoom = min(static_cast<double>(height) / srcOriginalSize.cy, ZOOM_IN_LIMIT);		
}

yrRECT CTCC89HWJPGDecode::CalcDestinationRenderRect(const double dHWRatioZoom, const yrSIZE& srcOriginalSize)
{
	yrRECT rendDstRect;
	// width of destination rect should be a multiply of 16 because of LCD control
	int srcWidthInScreenCoord = MAKEMULTI_16(Image2Screen(srcOriginalSize.cx, dHWRatioZoom));
	int srcHeightInScreenCoord = MAKEMULTI_8(Image2Screen(srcOriginalSize.cy, dHWRatioZoom));

	rendDstRect.left = MAKEMULTI_8(max(WINDOW_W/2 - srcWidthInScreenCoord / 2, 0));
	rendDstRect.right = min(rendDstRect.left + srcWidthInScreenCoord, WINDOW_W);
	rendDstRect.top = MAKEMULTI_8(max(WINDOW_H/2 - srcHeightInScreenCoord / 2, 0));
	rendDstRect.bottom = min(rendDstRect.top + srcHeightInScreenCoord, WINDOW_H);

	return rendDstRect;
}

yrRECT CTCC89HWJPGDecode::CalcRotateDestinationRenderRect(const double dHWRatioZoom, yrSIZE& srcOriginalSize)
{
	yrRECT rendDstRect;

	// width of destination rect should be a multiply of 16 because of LCD control
	int srcWidthInScreenCoord = MAKEMULTI_16(Image2Screen(srcOriginalSize.cx, dHWRatioZoom));
	int srcHeightInScreenCoord = MAKEMULTI_8(Image2Screen(srcOriginalSize.cy, dHWRatioZoom));

	rendDstRect.left = MAKEMULTI_8(max(WINDOW_H/2 - srcWidthInScreenCoord / 2, 0));
	rendDstRect.right = min(rendDstRect.left + srcWidthInScreenCoord, WINDOW_H);
	rendDstRect.top = MAKEMULTI_8(max(WINDOW_W/2 - srcHeightInScreenCoord / 2, 0));
	rendDstRect.bottom = min(rendDstRect.top + srcHeightInScreenCoord, WINDOW_W);

	return rendDstRect;
}

yrRECT CTCC89HWJPGDecode::CalcSourceRenderRect(const double dHWRatioZoom, const POINT& srcRenderCenterPt, 
						  const yrRECT& rendDstRect, const yrSIZE& srcOriginalSize)
{
	yrRECT rendSrcRect;	

	int dstWidthInImgCoord = Screen2Image(rendDstRect.right-rendDstRect.left, dHWRatioZoom);
	int dstHeightInImgCoord = Screen2Image(rendDstRect.bottom-rendDstRect.top, dHWRatioZoom);

	dstWidthInImgCoord = MAKEMULTI_8(dstWidthInImgCoord);
	dstHeightInImgCoord = MAKEMULTI_8(dstHeightInImgCoord);	

	int minX = dstWidthInImgCoord/2;
	int maxX = srcOriginalSize.cx - dstWidthInImgCoord/2;
	int minY = dstHeightInImgCoord/2;
	int maxY = srcOriginalSize.cy - dstHeightInImgCoord/2;

	if( srcRenderCenterPt.x >= maxX ) {
		rendSrcRect.right = MAKEMULTI_8(srcOriginalSize.cx);
		rendSrcRect.left = rendSrcRect.right - dstWidthInImgCoord;
	}
	else if( srcRenderCenterPt.x <= minX ) {		
		rendSrcRect.left = 0;
		rendSrcRect.right = rendSrcRect.left + dstWidthInImgCoord;
	}
	else {
		rendSrcRect.left = MAKEMULTI_8(srcRenderCenterPt.x - dstWidthInImgCoord/2);
		rendSrcRect.right = rendSrcRect.left + dstWidthInImgCoord;
	}

	if( srcRenderCenterPt.y >= maxY ) {
		rendSrcRect.bottom = MAKEMULTI_8(srcOriginalSize.cy);
		rendSrcRect.top = rendSrcRect.bottom - dstHeightInImgCoord;
	}
	else if( srcRenderCenterPt.y <= minY ) {		
		rendSrcRect.top = 0;
		rendSrcRect.bottom = rendSrcRect.top + dstHeightInImgCoord;
	}
	else {
		rendSrcRect.top = MAKEMULTI_8(srcRenderCenterPt.y - dstHeightInImgCoord/2);
		rendSrcRect.bottom = rendSrcRect.top + dstHeightInImgCoord;
	}

	return rendSrcRect;
}

yrRECT CTCC89HWJPGDecode::CalcRotateSourceRenderRect(const double dHWRatioZoom, POINT& srcRenderCenterPt, 
						  const yrRECT& rendDstRect, yrSIZE& srcOriginalSize)
{
	yrRECT rendSrcRect;
	POINT  temp_srcRenderCenterPt;
	
	temp_srcRenderCenterPt.x = srcRenderCenterPt.y;
	temp_srcRenderCenterPt.y = srcRenderCenterPt.x;
	
	int dstWidthInImgCoord = Screen2Image(rendDstRect.right-rendDstRect.left, dHWRatioZoom);
	int dstHeightInImgCoord = Screen2Image(rendDstRect.bottom-rendDstRect.top, dHWRatioZoom);

	dstWidthInImgCoord  = MAKEMULTI_8(dstWidthInImgCoord);
	dstHeightInImgCoord = MAKEMULTI_8(dstHeightInImgCoord);

	int minX = dstWidthInImgCoord/2;
	int maxX = srcOriginalSize.cx - dstWidthInImgCoord/2;
	int minY = dstHeightInImgCoord/2;
	int maxY = srcOriginalSize.cy - dstHeightInImgCoord/2;

	if( temp_srcRenderCenterPt.x >= maxX ) {
		rendSrcRect.right = MAKEMULTI_8(srcOriginalSize.cx);
		rendSrcRect.left = rendSrcRect.right - dstWidthInImgCoord;
	}
	else if( temp_srcRenderCenterPt.x <= minX ) {		
		rendSrcRect.left = 0;
		rendSrcRect.right = rendSrcRect.left + dstWidthInImgCoord;
	}
	else {
		rendSrcRect.left = MAKEMULTI_8(temp_srcRenderCenterPt.x - dstWidthInImgCoord/2);
		rendSrcRect.right = rendSrcRect.left + dstWidthInImgCoord;
	}

	if( temp_srcRenderCenterPt.y >= maxY ) {
		rendSrcRect.bottom = MAKEMULTI_8(srcOriginalSize.cy);
		rendSrcRect.top = rendSrcRect.bottom - dstHeightInImgCoord;
	}
	else if( temp_srcRenderCenterPt.y <= minY ) {		
		rendSrcRect.top = 0;
		rendSrcRect.bottom = rendSrcRect.top + dstHeightInImgCoord;
	}
	else {
		rendSrcRect.top = MAKEMULTI_8(temp_srcRenderCenterPt.y - dstHeightInImgCoord/2);
		rendSrcRect.bottom = rendSrcRect.top + dstHeightInImgCoord;
	}

	return rendSrcRect;
}

BOOL CTCC89HWJPGDecode::IsMoreZoomInAvailable(const yrRECT& rendSrcRect, const yrRECT& rendDstRect, const double dRatioToZoom)
{
	if(((rendDstRect.right-rendDstRect.left)<16)||((rendDstRect.bottom-rendDstRect.top)<2)) return FALSE;

	double dRatioWidthEnlarge = static_cast<double>(rendDstRect.right-rendDstRect.left) / 
								(rendSrcRect.right-rendSrcRect.left);

	return dRatioWidthEnlarge*dRatioToZoom <= ZOOM_IN_LIMIT;
}

void CTCC89HWJPGDecode::RenderImage(const unsigned int srcPhyAddr, const yrSIZE& srcOriginalSize, 
				 const yrSIZE& srcPadSize, const yrRECT& rendSrcRect, const yrRECT& rendDstRect, BOOL bEffectRender)
{
	// render
	yrIMG_INFO srcInfo;
	srcInfo.phyAddr = srcPhyAddr;
	srcInfo.paddedSize.cx = srcPadSize.cx;
	srcInfo.paddedSize.cy = srcPadSize.cy;

	yrRECT srRect;
	srRect.left = rendSrcRect.left;
	srRect.top = rendSrcRect.top;
	srRect.right = rendSrcRect.right;
	srRect.bottom = rendSrcRect.bottom;

	yrRECT drRect;
	drRect.left = rendDstRect.left;
	drRect.top = rendDstRect.top;
	drRect.right = rendDstRect.right;
	drRect.bottom = rendDstRect.bottom;

	m_pYUVRenderer->GetStatusValue(bHWJPGSetRotate,iHWJPGAngle);
	m_pYUVRenderer->IsEffectRender(bEffectRender);
	m_pYUVRenderer->Render(srcInfo, srRect, drRect);
}

void CTCC89HWJPGDecode::SetSWDrawValue(unsigned int addr, unsigned int width, unsigned int height, int iHWAngle)
{
	if(mpScaleMem)
	{
		if(mpScaleMem->VirAddr)
			VirtualFree((LPBYTE)mpScaleMem->VirAddr,0,MEM_RELEASE);
		
		delete [] mpScaleMem;
		mpScaleMem = NULL;
	}
	
	mpScaleMem = new Jpeg_Ip_Memory_Structure_Element;
	memset(mpScaleMem, 0, sizeof(Jpeg_Ip_Memory_Structure_Element));
	mpScaleMem->PhyAddr = addr;
	
	rendSrcOriginalSize.cx = width;
	rendSrcOriginalSize.cy = height;
	rendSrcPadSize.cx = width;
	rendSrcPadSize.cy = height;

	srcRenderCenterPt.x = rendSrcOriginalSize.cx / 2;
	srcRenderCenterPt.y = rendSrcOriginalSize.cy / 2;

	m_pSrcSize = 1;
	iHWJPGAngle= iHWAngle;
	bSWDrawValue = TRUE;
	bHWJPGSetRotate = FALSE;
}

#endif
