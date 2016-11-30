#ifndef __JPGSW_DECODER__
#define __JPGSW_DECODER__

#include "..\Image.h"
#include "TCCXXX_JPEGDEC.h"

class CTCCJpgSwDecode : public CImageDecoder
{
public:
	CTCCJpgSwDecode();
	virtual ~CTCCJpgSwDecode();

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
#ifdef __TCC89XX_WINCE__
	uint32  h_jpeg_dec; //After 1.68 
#endif
	JD_SRC_FMT src_fmt_info;
	IM_CUSTOM_OUTPUT out_callback;
	uint32	output_size;
	int * lcd_resize_buf;

	uint32 m_uiDecodeWidth;
	uint32 m_uiDecodeHeight;
	FLOAT rotateAngle;
	BOOL isJPGInfoChanged;

	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hMemBitmap;
	HBITMAP m_hBackupBitmap;

	BOOL m_bSWJPGImage;

private:
	unsigned char* CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format);
};

#endif // __JPGSW_DECODER__
