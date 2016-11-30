#ifdef __TCC79XX_WINCE__

#ifndef __JPGHW_DECODER__
#define __JPGHW_DECODER__

#include "..\Image.h"
#include "JpegDecoderBuilder.h"
#include "YUVRenderer.h"

class CTCCJpgHwDecode : public CImageDecoder
{
public:
	CTCCJpgHwDecode();
	virtual ~CTCCJpgHwDecode();

public:
	unsigned int PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight);
	BOOL DecodeImage(unsigned int *pResultSize, unsigned int Index);
	BOOL EndDecode();
	BOOL CheckDrawImage();
	void ClearDrawImage();
	BOOL IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight);
	unsigned int CheckDecodingCodecFormat();
	BOOL Draw(HDC hdc, RECT* dstRect, int zoomlevel);
	BOOL RotateImage(FLOAT angle);
	void ReleaseResource();
	void DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff);

private:
	BOOL bHWJPGErrStatus;
	BOOL bHWJPGSetRotate;
	int iHWJPGAngle;
	double dHWRatioZoom;
	double dHWFitRatioZoom;

	HANDLE m_hFile;
	GXString m_csFileName;

	CJpegDecoder *g_pDecoder;

	unsigned char* pSrcAddr;
	unsigned int pSrcSize;
	unsigned int destPhyAddr;

	jdSIZE originalImgSize;

	yrSIZE rendSrcOriginalSize;
	yrSIZE rendSrcPadSize;
	yrRECT rendSrcRect;
	yrRECT rendDstRect;
	POINT srcRenderCenterPt;

	BOOL m_bHWJPGImage;

private:
	BOOL LoadFile(LPCTSTR fileName, BYTE*& pBuf, DWORD& fileSize);
	BOOL DecodeJpegFile(unsigned char* pSrc, const unsigned int srcSize, unsigned int& destPhyAddr, unsigned char*& pDestVirtual, jdSIZE& originalSize, jdSIZE& decodedSize, jdSIZE& paddecodedSize);
	void   CalcZoomRatioToFitInScreen(int width, int height, const yrSIZE& srcOriginalSize, double& dHWRatioZoom);
	void   CalcZoomRatioToFitInScreenRotated(int width, int height,yrSIZE& srcOriginalSize, double& dHWRatioZoom);
	yrRECT CalcDestinationRenderRect(const double dHWRatioZoom, const yrSIZE& srcOriginalSize);
	yrRECT CalcRotateDestinationRenderRect(const double dHWRatioZoom, yrSIZE& srcOriginalSize);
	yrRECT CalcSourceRenderRect(const double dHWRatioZoom, const POINT& srcRenderCenterPt, const yrRECT& rendDstRect, const yrSIZE& srcOriginalSize);
	yrRECT CalcRotateSourceRenderRect(const double dHWRatioZoom, POINT& srcRenderCenterPt, const yrRECT& rendDstRect, yrSIZE& srcOriginalSize);
	BOOL   IsMoreZoomInAvailable(const yrRECT& rendSrcRect, const yrRECT& rendDstRect, const double dRatioToZoom);
	void   RenderImage(const unsigned int srcPhyAddr, const yrSIZE& srcOriginalSize, const yrSIZE& srcPadSize, const yrRECT& rendSrcRect, const yrRECT& rendDstRect, BOOL bEffectRender);
	BOOL RotateImage_Open();
};

#endif // __JPGHW_DECODER__

#endif