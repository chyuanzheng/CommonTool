// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////
#include "GxxString.h"
#if !defined(AFX_IMAGE_H__50FB07A2_D9C9_47D5_804D_C1D66C2B0561__INCLUDED_)
#define AFX_IMAGE_H__50FB07A2_D9C9_47D5_804D_C1D66C2B0561__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 

#undef __HDMI_INCLUDE__

#ifdef __TCC79XX_WINCE__
#include "TCCHWDEC\YUVRenderer.h"
#else
//#define HWJPGDEC_ENABLE //Using the block of TCC89x HW JPG Decoder
#include "TCC89X_DEC\TCC89x_ImageRenderer.h"
#endif
//#include "base.h"
#if !defined (SAFE_RELEASE)
   #define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}
#endif

#if !defined (SAFE_DELETE)
	#define SAFE_DELETE(x) if(x){delete (x); x=NULL;}
#endif

#ifdef __TCC79XX_WINCE__
#define HWJPGwithSWJPG
#endif

#ifdef __TCC89XX_WINCE__
    #ifdef __HDMI_INCLUDE__
        #define CheckDetectHDMI 10	//Timer Index:Check to HDMI detect as 100ms
    #endif
#endif

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
#define __HDMI_ZOOM__ // Support the zoom operation on HDMI display
#endif

#ifdef __TCC79XX_WINCE__
#define DEC_MAX_WIDTH	1920 //480*4 =1920 or 800*4=3200
#define DEC_MAX_HEIGHT	1088 //272*4 =1088 or 480*4=1920
#else
#define DEC_MAX_WIDTH	3200 //480*4 =1920 or 800*4=3200
#define DEC_MAX_HEIGHT	1920 //272*4 =1088 or 480*4=1920
#endif

typedef enum
{
#ifdef __TCC79XX_WINCE__
	#ifdef HWJPGwithSWJPG
	TYPE_TCCHWJPG,
	#endif
#else
	#ifdef HWJPGDEC_ENABLE
	TYPE_TCC89HWJPG,
	#endif
#endif
	TYPE_TCCSWJPG,
	TYPE_TCCSWBMP,
	TYPE_TCCSWPNG,
	TYPE_TCCSWGIF,
	TYPE_WINCE
}CODEC_TYPE;

extern int  WINDOW_H;
extern int  WINDOW_W;

class CImageDecoder
{
public:
	CImageDecoder(){};
	virtual ~CImageDecoder(){};

public:
	virtual unsigned int PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight) = 0;
	virtual BOOL DecodeImage(unsigned int *pResultSize, unsigned int Index) = 0;
	virtual BOOL EndDecode() = 0;
	virtual BOOL CheckDrawImage() = 0;
	virtual void ClearDrawImage() = 0;
	virtual BOOL IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight) = 0;
	virtual unsigned int CheckDecodingCodecFormat() = 0;
	virtual BOOL Draw(HDC hdc, RECT* dstRect, int zoomlevel) = 0;
	virtual BOOL RotateImage(FLOAT angle) = 0;
	virtual void ReleaseResource() = 0;	
	virtual void DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff) = 0;

	unsigned int m_Width;
	unsigned int m_Height;
	unsigned int m_PixelFormat;
        GUID m_RawDataFormat;

#ifdef __TCC79XX_WINCE__
	static CYUVRenderer *m_pYUVRenderer;
#else
	static CImageRender *m_pYUVRenderer;
#endif
};


class CImage
{
public:
	CImage();
	virtual ~CImage();

public:
	unsigned int PrepareImage(const WCHAR * szFileName, unsigned int uiWidth, unsigned int uiHeight);
	BOOL DecodeImage(unsigned int Index);
	BOOL CheckDrawImage();
	void ClearDrawImage();
	unsigned int CheckDecodingCodecFormat();
	BOOL Draw(HDC hdc, RECT* dstRect, int zoomlevel);
	BOOL DrawEffect(unsigned char *pBuffer, RECT* srcRect, RECT* dstRect);
	BOOL RotateImage(FLOAT angle);
	void ReleaseResource();
	void HDMIDisplayOnOff(BOOL bSetting);//ON:TRUE

	BOOL GetImageInfo(unsigned int *pWidth, unsigned int *pHeight, unsigned int *pPixelFormat, GUID *pRawDataFormat);
	void GetImageSize(unsigned int *pWidth, unsigned int *pHeight);
	int GetCodeType()
	{
		return m_CodeType;
	}

private:
	CImageDecoder *m_pDecoder[TYPE_WINCE + 1];
	unsigned char m_CodeType;
	GxxString szCurrFileName;

	unsigned int CheckImageCodec(GUID RawDataFormat);
	void SettingSWDecoderForHDMI(unsigned int *pWidth, unsigned int *pHeight);

#if (defined(__TCC89XX_WINCE__) && defined(__HDMI_INCLUDE__))
	unsigned int m_ConvertPhysicalAddr;
	unsigned char *m_ConvertVirtualAddr;
	unsigned int m_YUVPhysicalAddr;
	unsigned char *m_YUVVirtualAddr;
#endif
};

#endif // !defined(AFX_IMAGE_H__50FB07A2_D9C9_47D5_804D_C1D66C2B0561__INCLUDED_)
