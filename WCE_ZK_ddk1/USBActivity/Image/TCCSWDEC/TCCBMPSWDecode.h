
#ifndef __BMPSW_DECODER__
#define __BMPSW_DECODER__

#include "..\Image.h"
#include "TCCXXX_BMP_DEC.h"

class CTCCBmpSwDecode : public CImageDecoder
{
public:
	CTCCBmpSwDecode();
	virtual ~CTCCBmpSwDecode();

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

	uint32 *BMP_FILE_BUF;
	unsigned char *LCDbuf;

	uint32 m_uiDecodeWidth;//*pwidth
	uint32 m_uiDecodeHeight;//*pheight

	uint32 output_size;//outputSize
	FLOAT rotateAngle;
	BOOL isBMPInfoChanged;

	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hMemBitmap;
	HBITMAP m_hBackupBitmap;

	BOOL m_bSWBMPImage;

private:
	unsigned char* CreateBitMap(unsigned int width, int height, unsigned int *buffsize, GE_CH_DATAFORMAT format);
};

#endif // __PNGSW_DECODER__

