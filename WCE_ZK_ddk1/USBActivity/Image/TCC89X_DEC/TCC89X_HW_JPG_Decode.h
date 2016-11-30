/******************************************************************************
*
*  (C)Copyright All Rights Reserved by Telechips Inc.
*                                   
*  This material is confidential and shall remain as such. 
*  Any unauthorized use, distribution, reproduction is strictly prohibited. 
*
*   FileName    : TCC89X_HW_JPG_Decode.h
*   Description : 
*   TCC Version 1.0
*   Copyright (c) Telechips, Inc.
*   ALL RIGHTS RESERVED
*******************************************************************************/
/******************************************************************************
* include 
******************************************************************************/
#include "../Image.h"
#ifdef HWJPGDEC_ENABLE

#ifndef __TCC89X_HW_JPEG_DECODE_H__
#define __TCC89X_HW_JPEG_DECODE_H__
#include "TCC89X_HW_JPG_Proc.h"

/******************************************************************************
* defines 
******************************************************************************/

/******************************************************************************
* typedefs & structure
******************************************************************************/

typedef struct{
FILE *handle;
unsigned int width;
unsigned int height;
unsigned int thumb_offset;
unsigned int debug_flag;
unsigned int color_format;
}jpeg89hwInType;


typedef struct{
unsigned int width;
unsigned int height;	
unsigned char *out_ptr;
}jpeg89hwOutType;


typedef struct {
jpeg89hwInType	jpegin;
jpeg89hwOutType	jpegout;
}jpeg89hwStr;	

enum {
	JPEGIP_ERROR_NONE,
	JPEGIP_ERROR_DECOUT_BUF,
	JPEGIP_ERROR_INIT_DEC,
	JPEGIP_ERROR_DEC,
	HWJPEG_ERROR_MAX		
};

struct jdSIZE
{
	int cx;
	int cy;
};

class CTCC89HWJPGDecode : public CImageDecoder
{
public:
	CTCC89HWJPGDecode();
	~CTCC89HWJPGDecode();

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
	void SetSWDrawValue(unsigned int addr, unsigned int width, unsigned int height, int iHWAngle);

private:
	void   CalcZoomRatioToFitInScreen(int width, int height, const yrSIZE& srcOriginalSize, double& dHWRatioZoom);
	void   CalcZoomRatioToFitInScreenRotated(int width, int height,yrSIZE& srcOriginalSize, double& dHWRatioZoom);
	yrRECT CalcDestinationRenderRect(const double dHWRatioZoom, const yrSIZE& srcOriginalSize);
	yrRECT CalcRotateDestinationRenderRect(const double dHWRatioZoom, yrSIZE& srcOriginalSize);
	yrRECT CalcSourceRenderRect(const double dHWRatioZoom, const POINT& srcRenderCenterPt, const yrRECT& rendDstRect, const yrSIZE& srcOriginalSize);
	yrRECT CalcRotateSourceRenderRect(const double dHWRatioZoom, POINT& srcRenderCenterPt, const yrRECT& rendDstRect, yrSIZE& srcOriginalSize);
	BOOL   IsMoreZoomInAvailable(const yrRECT& rendSrcRect, const yrRECT& rendDstRect, const double dRatioToZoom);
	void   RenderImage(const unsigned int srcPhyAddr, const yrSIZE& srcOriginalSize, const yrSIZE& srcPadSize, const yrRECT& rendSrcRect, const yrRECT& rendDstRect, BOOL bEffectRender);
	BOOL RotateImage_Open();

private:
	jpeg89hwStr *mpJpegHwStr;
	Jpeg_Ip_Memory_Structure_Element *mpScaleMem;

	BOOL bHWJPGErrStatus;
	BOOL bHWJPGSetRotate;
	int iHWJPGAngle;
	double dHWRatioZoom;
	double dHWFitRatioZoom;

	HANDLE m_hFile;
	GxxString m_csFileName;

	unsigned int m_pSrcSize;

	yrSIZE rendSrcOriginalSize;
	yrSIZE rendSrcPadSize;
	yrRECT rendSrcRect;
	yrRECT rendDstRect;
	POINT srcRenderCenterPt;

	BOOL m_bHWJPGImage;
private:
	BOOL bSWDrawValue;

};
#endif
#endif

