#ifndef __GIFSW_DECODER__
#define __GIFSW_DECODER__

#include "..\Image.h"
//#ifdef __TCC79XX_WINCE__
//#include "TCCXXX_GIF_DEC_1.h"
//#else
#include "TCCXXX_GIF_DEC.h"
//#endif

class CTCCGifSwDecode : public CImageDecoder
{
public:
	CTCCGifSwDecode();
	virtual ~CTCCGifSwDecode();

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

public:
	uint32 m_uiDisplayWidth;
	uint32 m_uiDisplayHeight;

private:
	FILE *fp;

	GIFD_HANDLE hGif;
	GIFD_INIT init;
	unsigned char *LCDbuf;
	int heap_size;

	uint32 m_uiDecodeWidth;//*pwidth
	uint32 m_uiDecodeHeight;//*pheight

	uint32 output_size;//outputSize

	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hMemBitmap;
	HBITMAP m_hBackupBitmap;

	BOOL m_bSWGIFImage;
	BOOL isGIFInfoChanged;

private:
	unsigned char* CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format);
};

#endif 
