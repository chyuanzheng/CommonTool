
#ifndef __WINCE_DECODER__
#define __WINCE_DECODER__

#include "..\Image.h"
#include <imaging.h>


class CCEDecoder : public CImageDecoder
{
public:
	CCEDecoder();
	virtual ~CCEDecoder();

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
	IImagingFactory *m_pImagingFactory;
	IImageSink *m_pImageSink;
	IImageDecoder *m_pImageDecoder;	
	IBitmapImage *m_pBitmapImage;
	IStream *m_pStream;
	IImage* m_pImage;

	GUID Guids[10];
	UINT m_NumofFrame;

	ImageInfo m_ii;

	HRESULT CreateStreamOnFile(const TCHAR * tszFilename, IStream ** ppStream);
};

#endif // __WINCE_DECODER__