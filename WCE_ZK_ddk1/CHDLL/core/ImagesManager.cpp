#include "StdAfx.h"
#include <initguid.h>
#include "ImagesManager.h"


#include <imgguids.h>


CImagesManager *CImagesManager::m_pInstance = NULL;
CImagesManager* CImagesManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CImagesManager;
	}
	return m_pInstance;
}

CImagesManager::CImagesManager()
{

	m_hdcMem         = ::CreateCompatibleDC(NULL);
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoCreateInstance (CLSID_ImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IImagingFactory,
		(void **)&m_pImgFactory);
}

CImagesManager::~CImagesManager()
{

	if (m_hdcMem)
	{
		DeleteDC(m_hdcMem);
		m_hdcMem = NULL;
	}
	m_pImgFactory->Release();
	CoUninitialize();

}

BOOL CImagesManager::GetImageFromFile( const TCHAR* file,PARGBImageInfo* imageinfo )
{

	IImage *pImage                 = NULL;

	BOOL Result = TRUE;

	if (SUCCEEDED(m_pImgFactory->CreateImageFromFile(file, &pImage)))
	{
		ImageInfo imgInfo = {0};
		if (SUCCEEDED(pImage->GetImageInfo(&imgInfo)))
		{
			BitmapData bmpData           = {0};
			IBitmapImage *pBitmapImage = NULL;
			RECT rc                       = {0, 0, imgInfo.Width, imgInfo.Height};

			imageinfo->Width = imgInfo.Width;
			imageinfo->Height = imgInfo.Height;
			imageinfo->pixelformat = imgInfo.PixelFormat;

			// 如果图片的像素格式是PIXFMT_32BPP_PARGB 的则说明具备Alpha通道
			if(IsAlphaPixelFormat(imgInfo.PixelFormat))
			{
				DWORD formatid = PIXFMT_32BPP_PARGB;
				//if(imgInfo.PixelFormat == Format32bppArgb)
				//	formatid = PIXFMT_32BPP_PARGB;
				//else if(imgInfo.PixelFormat == Format24bppRgb)
				//	formatid = PixelFormat24bppRGB;

				if (SUCCEEDED(m_pImgFactory->CreateBitmapFromImage(pImage, 0, 0, formatid, 
					InterpolationHintDefault, &pBitmapImage)))
				{
					pBitmapImage->LockBits(&rc, ImageLockModeRead, formatid, &bmpData);
					imageinfo->hBitMap = CreateBitmap(imgInfo.Width, imgInfo.Height, 1, 
						GetPixelFormatSize(imgInfo.PixelFormat), bmpData.Scan0);
					if(imageinfo->hBitMap == NULL)
					{
						Result = FALSE;
					}

					pBitmapImage->UnlockBits(&bmpData);
					pBitmapImage->Release(); 

				}
				else
				{
					Result = FALSE;
				}
			}
			else
			{
				HDC hdc = ::GetDC(NULL);
				HDC memHdc = ::CreateCompatibleDC(hdc);
				imageinfo->hBitMap = CreateCompatibleBitmap(hdc,imgInfo.Width,imgInfo.Height);
				HGDIOBJ hOldBitmap=SelectObject(memHdc,imageinfo->hBitMap);
				RECT rect = { 0, 0, imgInfo.Width,imgInfo.Height};
				pImage->Draw(memHdc,&rect,NULL);

				SelectObject(memHdc, hOldBitmap);
				DeleteDC(memHdc);
				ReleaseDC(NULL,hdc);
			}
		}

		pImage->Release();
	}
	else
	{
		Result = FALSE;
	}

	return Result;
}

HANDLE CImagesManager::AddImage( const TCHAR* file )
{

	PARGBImageInfo* imageinfo = (PARGBImageInfo*)::LocalAlloc(LPTR,sizeof(PARGBImageInfo));
	if(imageinfo && GetImageFromFile(file,imageinfo))
	{
		return (HANDLE)imageinfo;
	}

	if (imageinfo)
	{
		LocalFree(imageinfo);//cyz 10/10/8 # 14 :08
	}
	return NULL;//fail



}

BOOL CImagesManager::RemoveImage( HANDLE ResID )
{

	PARGBImageInfo* info = (PARGBImageInfo*)ResID;

	if(info && info->hBitMap)
	{
		DeleteObject(info->hBitMap);
	}
	LocalFree(info);

	return TRUE;
		
}

BOOL CImagesManager::DrawAlphaImage( HANDLE ResID,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha/*=255*/ )
{
	PARGBImageInfo* info = (PARGBImageInfo*)ResID;
	if(info)
	{
		RECT SourceRECT;
		if(srcRC == NULL)
		{
			SourceRECT.left = 0; SourceRECT.top = 0;
			SourceRECT.right = info->Width; SourceRECT.bottom = info->Height;
		}
		else SourceRECT = *srcRC;
//DWORD time =::GetTickCount();
		DrawAlphaImage(info->hBitMap,info->pixelformat,destDC,&SourceRECT,destRC,Alpha);
		//time = ::GetTickCount()-time;
		//WCHAR  show[60];
		//wsprintf(show,L"time is :%d",time);
		//OutputDebugString(show);

		return TRUE;
	}

	return FALSE;
}

BOOL CImagesManager::DrawAlphaImage( HBITMAP bmp,DWORD imgPixelformat,HDC destDC,RECT* srcRC,RECT* destRC,BYTE Alpha/*=255*/ )
{
	/*HDC hdcMem         = ::CreateCompatibleDC(NULL);*/
	HGDIOBJ hGdiObjOld = ::SelectObject(m_hdcMem, bmp);

//	if(IsAlphaPixelFormat(imgPixelformat))
//	{
//		BLENDFUNCTION blendFunction = {0};
//		blendFunction.AlphaFormat = AC_SRC_ALPHA;
//		blendFunction.BlendFlags = 0;
//		blendFunction.BlendOp = AC_SRC_OVER;
//		blendFunction.SourceConstantAlpha = Alpha; 
//
//		//int iiii = GetTickCount();
//		::AlphaBlend(destDC, destRC->left, destRC->top, 
//			destRC->right-destRC->left, destRC->bottom-destRC->top, 
//			m_hdcMem, srcRC->left, srcRC->top, 
//			srcRC->right - srcRC->left, 
//			srcRC->bottom - srcRC->top, blendFunction);
//// 		iiii = GetTickCount() -iiii;
//// 		iiii++;
//	}
//	else
	{
		::StretchBlt(destDC,destRC->left,destRC->top,
			destRC->right-destRC->left, destRC->bottom-destRC->top, 
			m_hdcMem,srcRC->left, srcRC->top,srcRC->right-srcRC->left, srcRC->bottom-srcRC->top, SRCCOPY);
	}
	::SelectObject(m_hdcMem, hGdiObjOld);
// 	if (m_hdcMem)
// 	{
// 		DeleteDC(m_hdcMem);
// 		m_hdcMem = NULL;
// 	}
	return TRUE;
}

