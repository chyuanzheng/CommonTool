#ifdef __TCC79XX_WINCE__
#include "..\stdafx.h"
#include "TCCJPGHWDecode.h"

const int ZOOM_IN_LIMIT = 4;//8;

inline int Screen2Image(int length, double ratioZoom){return static_cast<int>(length/ratioZoom);}
inline int Image2Screen(int length, double ratioZoom){return static_cast<int>(length*ratioZoom);}

inline int MAKEMULTI_16(int value){return (value<<4)>>4;}
inline int MAKEMULTI_8(int value){return (value<<3)>>3;}

#ifdef HWJPGwithSWJPG

CTCCJpgHwDecode::CTCCJpgHwDecode()
{
	g_pDecoder = CJpegDecoderBuilder::BuildHWDecoder();

	m_hFile = NULL;
	bHWJPGErrStatus = TRUE;
	bHWJPGSetRotate = FALSE;
	iHWJPGAngle = DMA2D_NO_OPERATION;

	pSrcAddr = NULL;
	pSrcSize = 0;
	destPhyAddr = 0;
	
	m_bHWJPGImage = 0;
}

CTCCJpgHwDecode::~CTCCJpgHwDecode()
{
	if(m_hFile)
	{
		::CloseHandle(m_hFile);	
		m_hFile=NULL;
	}
	delete g_pDecoder;
}

unsigned int CTCCJpgHwDecode::PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	BYTE *pBuf = NULL;
	DWORD fileSize;

	dHWRatioZoom = 1.0;
	bHWJPGSetRotate	= FALSE;
	dHWFitRatioZoom	=1.0;
	iHWJPGAngle = DMA2D_NO_OPERATION;
	m_csFileName = szFileName;    

	if(LoadFile(szFileName, pBuf, fileSize))
	{
		pSrcAddr = pBuf;
		pSrcSize = fileSize;
		return 1;
	}
	else
	{
		if(pBuf)
			delete [] pBuf;
		return 0;
	}
}

BOOL CTCCJpgHwDecode::DecodeImage(unsigned int *pResultSize, unsigned int Index)
{
	unsigned char *pDestVirtual = NULL;
			
	jdSIZE decodedSize;
	jdSIZE decodedPadSize;

	if( DecodeJpegFile(pSrcAddr, pSrcSize, destPhyAddr, pDestVirtual, originalImgSize, decodedSize, decodedPadSize) )
	{
		rendSrcOriginalSize.cx = decodedSize.cx;
		rendSrcOriginalSize.cy = decodedSize.cy;
		rendSrcPadSize.cx = decodedPadSize.cx;
		rendSrcPadSize.cy = decodedPadSize.cy;

		srcRenderCenterPt.x = rendSrcOriginalSize.cx / 2;
		srcRenderCenterPt.y = rendSrcOriginalSize.cy / 2;						
	}
	else
	{
		delete [] pSrcAddr;
		pSrcAddr = NULL;

		*pResultSize = 0;
		//m_bHWJPGImage = FALSE;
		return FALSE;
	}
	delete [] pSrcAddr;
	pSrcAddr = NULL;
	
	m_bHWJPGImage = TRUE;

	return m_bHWJPGImage;
}

BOOL CTCCJpgHwDecode::EndDecode()
{
	if(pSrcSize)
	{
		RECT rt = {0, 0, WINDOW_W, WINDOW_H};
		HDC hdc = ::GetDC(NULL);
		::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
		::ReleaseDC(NULL, hdc);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCCJpgHwDecode::CheckDrawImage()
{	
	return m_bHWJPGImage;
}

void CTCCJpgHwDecode::ClearDrawImage()
{
	{
		RECT rt = {0, 0, WINDOW_W, WINDOW_H};
		HDC hdc = ::GetDC(NULL);
		::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
		::ReleaseDC(NULL, hdc);
	}
	//m_bHWJPGImage = FALSE;
}

BOOL CTCCJpgHwDecode::IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight)
{
	return FALSE;
}

unsigned int CTCCJpgHwDecode::CheckDecodingCodecFormat()
{
	return TYPE_TCCHWJPG;
}

void CTCCJpgHwDecode::DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff)
{
}

BOOL CTCCJpgHwDecode::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
{
	int dstWidthInImgCoord;
	int dstHeightInImgCoord;
	POINT MovePt, CenterPt;
	
	if((iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES)||(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES))
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
	if(iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES)
	{
		MovePt.x = CenterPt.x - MovePt.x;
		MovePt.y = CenterPt.y + MovePt.y;
	}
	else if(iHWJPGAngle ==DMA2D_ROTATE_180_DEGREES)
	{
		MovePt.x = CenterPt.x + MovePt.x;
		MovePt.y = CenterPt.y + MovePt.y;
	}
	else if(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES)
	{
		MovePt.x = CenterPt.x + MovePt.x;
		MovePt.y = CenterPt.y - MovePt.y;
	}
	else
	{
		MovePt.x = CenterPt.x - MovePt.x;
		MovePt.y = CenterPt.y - MovePt.y;
	}
    
	if((iHWJPGAngle ==DMA2D_ROTATE_90_DEGREES)||(iHWJPGAngle == DMA2D_ROTATE_270_DEGREES))
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
	if(bZoomAvailableRet)
	{
		//printf("\t line(%d) rendDstRect(%d,%d,%d,%d)\n", __LINE__, rendDstRect.left, rendDstRect.top, rendDstRect.right, rendDstRect.bottom);
		//printf("\t line(%d) rendSrcRect(%d,%d,%d,%d)\n", __LINE__, rendSrcRect.left, rendSrcRect.top, rendSrcRect.right, rendSrcRect.bottom);
		RenderImage(destPhyAddr, rendSrcOriginalSize, rendSrcPadSize, rendSrcRect, rendDstRect, FALSE);
	}

	if(pSrcSize)
	{
		int r,g,b;
		CYUVRenderer::GetChromakeyColor(r,g,b);
		HBRUSH hBrush = ::CreateSolidBrush(RGB(r,g,b));
		RECT rt = {dstRect->left,dstRect->top, dstRect->right, dstRect->bottom};//, dstRect->top, dstRect->right, dstRect->bottom);
		::FillRect(hdc, &rt, hBrush);
		::DeleteObject(hBrush);
	}

	return bZoomAvailableRet;
}

BOOL CTCCJpgHwDecode::RotateImage(FLOAT angle)
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

	RotateImage_Open();
	return TRUE;
}

void CTCCJpgHwDecode::ReleaseResource()
{
	m_bHWJPGImage = FALSE;

	bHWJPGErrStatus = TRUE;
	bHWJPGSetRotate = FALSE;
	iHWJPGAngle = 0;

	pSrcAddr = NULL;
	pSrcSize = 0;
	destPhyAddr = 0;

	if(m_hFile)
	{
		::CloseHandle(m_hFile);	
		m_hFile=NULL;
	}
}

BOOL CTCCJpgHwDecode::LoadFile(LPCTSTR fileName, BYTE*& pBuf, DWORD& fileSize)
{
	// read source file
	m_hFile = CreateFile (fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		printf("couldn't read file. invalid file name\r\n");
		return FALSE;
	}
	fileSize = GetFileSize(m_hFile, 0);
	pBuf = new BYTE[fileSize];
	if( !pBuf ) 
	{
		printf("couldn't alloc memory for jpg file\r\n");
		return FALSE;
	}

	DWORD dwRead;
	ReadFile(m_hFile, pBuf, fileSize, &dwRead, NULL);
	//tcw_assert_eq(fileSize, dwRead);
	CloseHandle(m_hFile);

	return fileSize;
}

BOOL CTCCJpgHwDecode::DecodeJpegFile(unsigned char* pSrc, const unsigned int srcSize, unsigned int& destPhyAddr, unsigned char*& pDestVirtual, 
					jdSIZE& originalSize, jdSIZE& decodedSize, jdSIZE& paddecodedSize)
{
	unsigned int destBufSize;
    
	bHWJPGErrStatus = TRUE;

	CJpegDecoder::ENUM_RESULT result = g_pDecoder->Decode(pSrc, srcSize, 
 		destPhyAddr, pDestVirtual, destBufSize, originalSize, decodedSize, paddecodedSize);
	
	switch(result)
	{
	case CJpegDecoder::ER_VCORE_FAIL :
	case CJpegDecoder::ER_BIGGER_THAN_4080_WIDTH :
	case CJpegDecoder::ER_MEM_ALLOCATION_FAIL :
	case CJpegDecoder::ER_SCALE_FAIL :
	case CJpegDecoder::ER_NOT_SPECIFIED :
		{
			bHWJPGErrStatus = FALSE;
		}
		break;
	case CJpegDecoder::ER_SUCCESS :
		break;
	default:
		MessageBox(NULL, _T("abnormal result value"), _T(""), 0);
		break;
	}
	
	// if fail, destroy and create to initialize
	if( result != CJpegDecoder::ER_SUCCESS ) {
		delete g_pDecoder;		
		g_pDecoder = CJpegDecoderBuilder::BuildHWDecoder();
	}
	return result == CJpegDecoder::ER_SUCCESS;
}

void CTCCJpgHwDecode::CalcZoomRatioToFitInScreen(int width, int height, const yrSIZE& srcOriginalSize, double& dHWRatioZoom)
{
	if( width/srcOriginalSize.cx < height/srcOriginalSize.cy )
		dHWRatioZoom = min(static_cast<double>(width) / srcOriginalSize.cx, ZOOM_IN_LIMIT);
	else
		dHWRatioZoom = min(static_cast<double>(height) / srcOriginalSize.cy, ZOOM_IN_LIMIT);		
}

yrRECT CTCCJpgHwDecode::CalcDestinationRenderRect(const double dHWRatioZoom, const yrSIZE& srcOriginalSize)
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

yrRECT CTCCJpgHwDecode::CalcRotateDestinationRenderRect(const double dHWRatioZoom, yrSIZE& srcOriginalSize)
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

yrRECT CTCCJpgHwDecode::CalcSourceRenderRect(const double dHWRatioZoom, const POINT& srcRenderCenterPt, 
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

	/*
	printf("\t [CalcSourceRenderRect]\r\n");
	printf("\t\t line(%d) width : %d, height : %d\r\n", __LINE__, dstWidthInImgCoord, dstHeightInImgCoord);
	printf("\t\t line(%d) srcRenderCenterPt.x : %d, srcRenderCenterPt.y : %d\r\n", __LINE__, srcRenderCenterPt.x, srcRenderCenterPt.y);
	printf("\t\t line(%d) minX : %d, maxX : %d, minY : %d, maxY : %d\n", __LINE__, minX, maxX, minY, maxY);
	*/

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

yrRECT CTCCJpgHwDecode::CalcRotateSourceRenderRect(const double dHWRatioZoom, POINT& srcRenderCenterPt, 
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

BOOL CTCCJpgHwDecode::IsMoreZoomInAvailable(const yrRECT& rendSrcRect, const yrRECT& rendDstRect, const double dRatioToZoom)
{
	if(((rendDstRect.right-rendDstRect.left)<8)||((rendDstRect.bottom-rendDstRect.top)<2)) return FALSE;

	double dRatioWidthEnlarge = static_cast<double>(rendDstRect.right-rendDstRect.left) / 
								(rendSrcRect.right-rendSrcRect.left);

	return dRatioWidthEnlarge*dRatioToZoom <= ZOOM_IN_LIMIT;
}

void CTCCJpgHwDecode::RenderImage(const unsigned int srcPhyAddr, const yrSIZE& srcOriginalSize, 
				 const yrSIZE& srcPadSize, const yrRECT& rendSrcRect, const yrRECT& rendDstRect, BOOL bEffectRender)
{
//	static CYUVRenderer yuvRenderer(WINDOW_W, WINDOW_H);

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

BOOL CTCCJpgHwDecode::RotateImage_Open()
{
	BYTE *pBuf = NULL;
	DWORD fileSize;

	if(LoadFile(m_csFileName, pBuf, fileSize))
	{
		unsigned char *pDestVirtual = NULL;	
				
		jdSIZE decodedSize;
		jdSIZE decodedPadSize;

		if( DecodeJpegFile(pBuf, fileSize, destPhyAddr, pDestVirtual, originalImgSize, decodedSize, decodedPadSize) )
		{
			rendSrcOriginalSize.cx = decodedSize.cx;
			rendSrcOriginalSize.cy = decodedSize.cy;
			rendSrcPadSize.cx = decodedPadSize.cx;
			rendSrcPadSize.cy = decodedPadSize.cy;

			srcRenderCenterPt.x = rendSrcOriginalSize.cx / 2;
			srcRenderCenterPt.y = rendSrcOriginalSize.cy / 2;						

			EndDecode();

			if(pBuf)
			{
				delete [] pBuf;
				pBuf = NULL;
			}
   			return TRUE;
		}
	}
	if(pBuf)
	{
		delete [] pBuf;
		pBuf = NULL;
	}

	return FALSE;
}

#endif

#endif
