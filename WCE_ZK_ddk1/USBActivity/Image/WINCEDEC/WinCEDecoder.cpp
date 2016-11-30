#include "stdAfx.h"
#include "initguid.h"
#include "WinCEDecoder.h"


CCEDecoder::CCEDecoder()
{
	m_pImagingFactory = NULL;
	m_pImageSink = NULL;
	m_pImageDecoder = NULL;
	m_pBitmapImage = NULL;
	m_pStream = NULL;
	m_pImage = NULL;

	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HRESULT hr = CoCreateInstance(CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IImagingFactory, (void**)&m_pImagingFactory);
	if(FAILED(hr))
	{
		printf("CoCreateInstance failed, hr: 0x%08x\r\n", hr);
	}
}

CCEDecoder::~CCEDecoder()
{
	SAFE_RELEASE(m_pImage);
	SAFE_RELEASE(m_pStream);
	SAFE_RELEASE(m_pImageSink);
	SAFE_RELEASE(m_pImageDecoder);
	SAFE_RELEASE(m_pImagingFactory);
}

unsigned int CCEDecoder::PrepareImage(LPCTSTR szFileName, unsigned int uiWidth, unsigned int uiHeight)
{
	HRESULT hr;

	if(FAILED(hr = CreateStreamOnFile(szFileName, &m_pStream)))
	{
		printf("CreateStreamOnFile failed, hr: 0x%08x\r\n", hr);
		goto finish;
	}

	if(FAILED(hr = m_pImagingFactory->CreateImageDecoder(m_pStream, DecoderInitFlagBuiltIn1st, &m_pImageDecoder)))
	{
		printf("CreateImageDecoder failed, hr: 0x%08x\r\n", hr);
		goto finish;
	}

	if(FAILED(hr = m_pImageDecoder->GetImageInfo(&m_ii)))
	{
		printf("GetImageInfo failed, hr: 0x%08x\r\n", hr);
		goto finish;
	}
	
	m_Width = m_ii.Width;
	m_Height = m_ii.Height;
	m_PixelFormat = m_ii.PixelFormat;
	m_RawDataFormat = m_ii.RawDataFormat;

	#if 0
	printf("ImageInfo RawDataFormat : 0x%08x\r\n", m_ii.RawDataFormat);
	printf("ImageInfo PixelFormat : 0x%08x\r\n", m_ii.PixelFormat);
	printf("ImageInfo Width       : 0x%08x\r\n", m_ii.Width);
	printf("ImageInfo Height      : 0x%08x\r\n", m_ii.Height);
	printf("ImageInfo TileWidth   : 0x%08x\r\n", m_ii.TileWidth);
	printf("ImageInfo TileHeight  : 0x%08x\r\n", m_ii.TileHeight);
	printf("ImageInfo Xdpi        : 0x%08x\r\n", m_ii.Xdpi);
	printf("ImageInfo Ydpi        : 0x%08x\r\n", m_ii.Ydpi);
	printf("ImageInfo Flags       : 0x%08x\r\n", m_ii.Flags);
	#endif

	if(m_ii.RawDataFormat == ImageFormatGIF )
	{
		UINT nCount;
		m_pImageDecoder->GetFrameDimensionsCount(&nCount);
		if(nCount > (sizeof(Guids)/sizeof(Guids[0])) )
			nCount = (sizeof(Guids)/sizeof(Guids[0]));			
		m_pImageDecoder->GetFrameDimensionsList(Guids, nCount);
		m_pImageDecoder->GetFrameCount(&Guids[0], &m_NumofFrame);
	}
	else
	{
		m_NumofFrame = 1;//setting default;
	}
	EndDecode();

	return m_NumofFrame;

finish:	
	//SAFE_RELEASE(m_pImagingFactory);
	SAFE_RELEASE(m_pImageDecoder);
	SAFE_RELEASE(m_pStream);
	return 0;
}

BOOL CCEDecoder::DecodeImage(unsigned int *pResultSize, unsigned int Index)
{
	HRESULT hr;

	SAFE_RELEASE(m_pBitmapImage);
	SAFE_RELEASE(m_pImageSink);
	SAFE_RELEASE(m_pImage);

	m_pImageDecoder->SelectActiveFrame(&Guids[0], Index);

	if(FAILED(hr = m_pImagingFactory->CreateNewBitmap(m_ii.Width, m_ii.Height, m_ii.PixelFormat, &m_pBitmapImage)))
	{
		printf("CreateNewBitmap failed, hr = 0x%08x\r\n", hr);
		goto finish;
	}
	
	if(FAILED(hr = m_pBitmapImage->QueryInterface(IID_IImageSink, (void**)&m_pImageSink)))
	{
		printf("QueryInterface for ImageSink from BitmapImage failed, hr: 0x%08x\r\n", hr);
		goto finish;
	}
	
	if(FAILED(hr = m_pBitmapImage->QueryInterface(IID_IImage, (void**)&m_pImage)))
	{
		printf("QueryInterface for Image from BitmapImage failed, hr: 0x%08x\r\n", hr);
		goto finish;
	}
	
	if(FAILED(hr = m_pImageDecoder->BeginDecode(m_pImageSink, NULL)))
	{
		printf("BeginDecode into Bitmap Image failed, hr = 0x%08d\r\n", hr);
		goto finish;
	}

	while(E_PENDING == (hr = m_pImageDecoder->Decode()))
		Sleep(0);

	hr = m_pImageDecoder->EndDecode(hr);
	if(FAILED(hr))
	{
		printf("Decoding failed, hr = 0x%08x\r\n", hr);
		goto finish;
	}
	return TRUE;

finish:
	SAFE_RELEASE(m_pBitmapImage);
	SAFE_RELEASE(m_pImageSink);
	SAFE_RELEASE(m_pImage);
	return FALSE;
}

BOOL CCEDecoder::EndDecode()
{
	if(0)
	{
		RECT rt = {0, 0, WINDOW_W, WINDOW_H};
		HDC hdc = ::GetDC(NULL);
		::FillRect(hdc, &rt, (HBRUSH)::GetStockObject(BLACK_BRUSH));
		::ReleaseDC(NULL, hdc);
		return TRUE;
	}
	return TRUE;
}

BOOL CCEDecoder::CheckDrawImage()
{
	if(m_pImage)
		return TRUE;	
	return FALSE;
}

void CCEDecoder::ClearDrawImage()
{
	SAFE_RELEASE(m_pImage);
}

BOOL CCEDecoder::IsImageInfoChanged(unsigned int *uiWidth, unsigned int *uiHeight)
{
	return FALSE;
}

unsigned int CCEDecoder::CheckDecodingCodecFormat()
{
	if(m_ii.RawDataFormat == ImageFormatBMP )
		return TYPE_WINCE + 1;
	else if(m_ii.RawDataFormat == ImageFormatPNG )
		return TYPE_WINCE + 2;
	else if(m_ii.RawDataFormat == ImageFormatGIF)
		return TYPE_WINCE + 3;
	return 0;
}

void CCEDecoder::DrawYUV420toRender(unsigned char *pConvertBuff, unsigned char *pOutBuff)
{
}

BOOL CCEDecoder::Draw(HDC hdc, RECT* dstRect, int zoomlevel)
{
	if(m_NumofFrame>1)
		::FillRect(hdc, dstRect, (HBRUSH)::GetStockObject(BLACK_BRUSH));

	HRESULT hr = m_pImage->Draw(hdc, dstRect, NULL);
	return SUCCEEDED(hr);
}

BOOL CCEDecoder::RotateImage(FLOAT angle)
{
	HRESULT hr;
	IBasicBitmapOps *m_pBasicBitmapOps =NULL;
	IBitmapImage *newBitmap = NULL;

	if((m_pBitmapImage == NULL) || (m_pImage ==NULL))
	{
		printf("RoateImage InitValue failed\r\n");
		return FALSE;
	}
	
	if(FAILED(hr = m_pBitmapImage->QueryInterface(IID_IBasicBitmapOps, (void**)(&m_pBasicBitmapOps))))
	{
		printf("QueryInterface for m_pBasicBitmapOps from m_pBitmapImage failed, hr: 0x%08x\r\n", hr);
		goto finish;
	}
	
	if(FAILED(hr = m_pBasicBitmapOps->Rotate(angle, InterpolationHintNearestNeighbor, &newBitmap)))
	{
		printf("Rotate failed from m_pBasicBitmapOps , hr: 0x%08x\r\n", hr);
		goto finish;
	}

	SAFE_RELEASE(m_pImage);
		
	if(FAILED(hr = newBitmap->QueryInterface(IID_IImage, (void**)(&m_pImage))))
	{
		printf("newBitmap failed from m_pBasicBitmapOps , hr: 0x%08x\r\n", hr);
		goto finish;
	}
	


	SAFE_RELEASE(m_pBasicBitmapOps);
	SAFE_RELEASE(newBitmap);
	return TRUE;	

finish:
	SAFE_RELEASE(m_pImage);
	SAFE_RELEASE(m_pBasicBitmapOps);
	SAFE_RELEASE(newBitmap);
	return FALSE;
}

void CCEDecoder::ReleaseResource()
{
	SAFE_RELEASE(m_pImageSink);
	SAFE_RELEASE(m_pImageDecoder);
	SAFE_RELEASE(m_pBitmapImage);
	SAFE_RELEASE(m_pStream);
	SAFE_RELEASE(m_pImage);
}

HRESULT CCEDecoder::CreateStreamOnFile(const TCHAR * tszFilename, IStream ** ppStream)
{
	HRESULT hr = S_OK;
	HGLOBAL hg = NULL;
	HANDLE hFile = NULL;
	DWORD dwSize, dwRead;
	BYTE* pbLocked = NULL;

	// Open the file
	hFile = CreateFile(tszFilename, GENERIC_READ, /*0*/FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(INVALID_HANDLE_VALUE == hFile)
	{
		printf("CreateFile failed with GLE = %d\r\n", GetLastError());
		hr = 0x80000000 + GetLastError();
		goto error;
	}

	dwSize = GetFileSize(hFile, NULL);
	if(0xffffffff == dwSize)
	{
		printf("GetFileSize failed with GLE = %d\r\n", GetLastError());
		hr = 0x80000000 + GetLastError();
		goto error;
	}

	// Open a memory object
	hg = GlobalAlloc(GMEM_MOVEABLE, dwSize);
	if(NULL == hg)
	{
		printf("GlobalAlloc failed with GLE = %d\r\n", GetLastError());
		hr = 0x80000000 + GetLastError();
		goto error;
	}

	// Ge a pointer to the memory we just allocated
	pbLocked = (BYTE*) GlobalLock(hg);
	if(NULL == pbLocked)
	{
		printf("GlobalLock failed with GLE = %d\r\n", GetLastError());
		hr = 0x80000000 + GetLastError();
		goto error;
	}

	// copy the file
	if(!ReadFile(hFile, pbLocked, dwSize, &dwRead, NULL))
	{
		printf("ReadFile failed with GLE = %d\r\n", GetLastError());
		hr = 0x80000000 + GetLastError();
		goto error;
	}

	GlobalUnlock(hg);
    
	// Create the stream
	hr = CreateStreamOnHGlobal(hg, TRUE, ppStream);

	CloseHandle(hFile);
	return hr;

error:
	if(pbLocked)
		GlobalUnlock(hg);
	if(hg)
		GlobalFree(hg);
	if(hFile)
		CloseHandle(hFile);
	return hr;
}