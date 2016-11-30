#pragma once
#include "StdAfx.h"
#include <windows.h>
//#include "base.h"
#include "Common\Thread.h"
#include "NexEffecter.h"
#include "GxxString.h"

typedef struct
{
	unsigned long	ulEffectID;
	unsigned long	ulOpFlags;
	unsigned long	ulShape;
	unsigned long	ulDirectionFlags;
	unsigned long	ulDirectionCode;
	unsigned long ulDivisonCount;
	unsigned long ulValue;
	unsigned long ulCurrent;
	unsigned long ulTotal;
}IMAGE_EFFECT_INFO;

typedef enum 
{
	TYPE_JPEG,
	TYPE_BMP,
	TYPE_PNG,
	TYPE_MAX
}DecoderType;

class CImage;
//class CImageFileCont;

class CEffect : private cThread
{
public:
	CEffect();
	virtual ~CEffect();

	void Init(LPVOID pImageDecoder, LPVOID pImageFileCont, int Message);
	void Create(int X, int Y, int nWidth, int nHeight, HWND hWndParent);
	void Destroy();

	int CheckEffectFileIndex();
	void SetSelectedFile(int iFileIndex);
	void SetEffect();
	void SetSlideShow(BOOL repeat, int duration);
	int SetEndEffectIndex();

	void OnTimer(unsigned int id);
	int OnCmdExit(BOOL bImageOpen=TRUE);

	BOOL m_bRepeat;
	BOOL m_bShuffle;

protected:
	void ReDraw();	
	DecoderType CheckImageType(GxxString filename);

	BOOL (*DecodePFn[TYPE_MAX])(unsigned char *pdst, unsigned int *pwidth, unsigned int *pheight);
	static BOOL JPGDecoder(unsigned char *pdst, unsigned int *pwidth, unsigned int *pheight);
	static BOOL BMPDecoder(unsigned char *pdst, unsigned int *pwidth, unsigned int *pheight);
	static BOOL PNGDecoder(unsigned char *pdst, unsigned int *pwidth, unsigned int *pheight);

	BOOL EffectParamSet(IMAGE_EFFECT_INFO *EffectInfo);
	BOOL EffectImage();
	BOOL TransitionParamSet(IMAGE_EFFECT_INFO *EffectInfo);
	BOOL TransitionImage();

	DWORD Run();

protected:
	HWND m_hWnd;
	static CEffect *mpInstance;	

	HANDLE m_hEventThreadExit;
	HANDLE m_hEventDecode[2];

	CImage *m_pImageDecoder;
	//CImageFileCont *m_pImageFileCont;
	int m_Message;

	unsigned char m_Format;

	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hMemBitmap;
	HBITMAP m_hBackupBitmap;

	int m_FileIndex;
	int m_NextFileIndex;
	GxxString m_CurFileName;
	GxxString m_FileName[2];
	unsigned char m_BaseIndex;	

	unsigned char *m_pSrcBuffer[2];
	unsigned char *m_pEffectBuffer;

	NEXIMAGEEffectPARAM m_EffectParam;
	NEXIMAGETransitionPARAM m_TransitionParam;
	unsigned char m_TransitionNumber;
	unsigned char m_TransitionCount;

	BOOL m_bEffectProcess;
	BOOL m_bShowEffect;
	RECT m_EffectRect;
	BOOL m_bIsTransition;

	DWORD m_SlideTime;
	DWORD m_TransitionTime;

	CRITICAL_SECTION m_CS;
};
