
#ifndef __PNGSW_DECODER__
#define __PNGSW_DECODER__

#include "..\Image.h"
#include "TCCXXX_PNG_DEC.h"

class CTCCPngSwDecode : public CImageDecoder
{
public:
	CTCCPngSwDecode();
	virtual ~CTCCPngSwDecode();

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

	PD_CUSTOM_DECODE output_setting;
	PD_INIT *pPD_init_Mem;

	unsigned char *pHeapBuf;
	char *pInstanceMem;
	unsigned char *LCDbuf;

	uint32 output_size;//PNG_BUF_SIZE
	uint32 m_uiDecodeWidth;//PNG_width
	uint32 m_uiDecodeHeight;//PNG_height
	uint32 PNG_Alpha;
	uint32 heap_size;
	unsigned int PNG_pixelDepth;

	FLOAT rotateAngle;
	BOOL isPNGInfoChanged;

	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hMemBitmap;
	HBITMAP m_hBackupBitmap;

	BOOL m_bSWPNGImage;

private:
	unsigned char* CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format);
};

#endif // __PNGSW_DECODER__
