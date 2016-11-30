#pragma once

#include "USBDllModule.h"
#include "Image/Image.h"
#include "Image/Effect/Effect.h"
#include "GxxDCContainer.h"

class CE_USBACTIVITY_API PhotoControl
{
	static GxxDCContainer	*pDcContainer;
	static wstring sPlayFile;
	static int degree;
	static CImage *pImage;
	static CEffect				effectView;
	static int zoom;
public:
	static void SetDcContainter(GxxDCContainer *p)
	{
		pDcContainer = p;
		const int CMD_EFFECT = WM_USER + 7;
		effectView.Init((LPVOID)pImage, NULL, CMD_EFFECT);
		effectView.Create(0, 0, WINDOW_W, WINDOW_H, AfxGetHWND());
		//effectView.Create(0, 0, WINDOW_W, WINDOW_H, p->GetHwnd());
		effectView.SetSlideShow(0, 5);
	}
	static void Draw()
	{
		if (pImage->CheckDrawImage())
		{
			unsigned int width, height;
			pImage->GetImageSize(&width, &height);
			CRect rcDraw = pDcContainer->getDcRect();
			CRect rcDrawSrc = rcDraw;
	
			float ratio = (float)width/height;
			if (degree == 0 || degree == 180)
			{
				if (ratio >= (float)800/480)
				{
					// width 比较大
					if (width > rcDrawSrc.Width())
					{
						int h = rcDrawSrc.Width()/ratio;
						rcDraw.top = (rcDrawSrc.Height()-h)/2;
						rcDraw.bottom = rcDraw.top+h;
					}
					if (width<rcDrawSrc.Width())
					{
						rcDraw.left = (rcDrawSrc.Width()-width)/2;
						rcDraw.right = rcDraw.left + width;

						rcDraw.top = (rcDrawSrc.Height()-height)/2;
						rcDraw.bottom = rcDraw.top+height;
					}
				}
				else
				{
					if (height > rcDrawSrc.Height())
					{
						int w = rcDrawSrc.Height()*ratio;
						rcDraw.left = (rcDrawSrc.Width()-w)/2;
						rcDraw.right = rcDraw.left + w;
					}
					else
					{
						rcDraw.left = (rcDrawSrc.Width()-width)/2;
						rcDraw.right = rcDraw.left + width;

						rcDraw.top = (rcDrawSrc.Height()-height)/2;
						rcDraw.bottom = rcDraw.top+height;
					}
				}
			}
			
			//HBRUSH hBrush = CreateSolidBrush(RGB(16,0,16));
			//FillRect(pDcContainer->GetDC(), &pDcContainer->getDcRect(), hBrush);
			
			if (degree==90||degree==270)
			{
				unsigned int temp = width;
				width = height;
				height = temp;
				ratio = (float)width/height;
				if (ratio >= (float)800/480)
				{
					// width 比较大
					if (width > rcDrawSrc.Width())
					{
						int h = rcDrawSrc.Width()/ratio;
						rcDraw.top = (rcDrawSrc.Height()-h)/2;
						rcDraw.bottom = rcDraw.top+h;
					}
					if (width<rcDrawSrc.Width())
					{
						rcDraw.left = (rcDrawSrc.Width()-width)/2;
						rcDraw.right = rcDraw.left + width;

						rcDraw.top = (rcDrawSrc.Height()-height)/2;
						rcDraw.bottom = rcDraw.top+height;
					}
				}
				else
				{
					if (height > rcDrawSrc.Height())
					{
						int w = rcDrawSrc.Height()*ratio;
						rcDraw.left = (rcDrawSrc.Width()-w)/2;
						rcDraw.right = rcDraw.left + w;
					}
					else
					{
						rcDraw.left = (rcDrawSrc.Width()-width)/2;
						rcDraw.right = rcDraw.left + width;

						rcDraw.top = (rcDrawSrc.Height()-height)/2;
						rcDraw.bottom = rcDraw.top+height;
					}
				}
			}
			// 放大缩小
			if (zoom != 100)
			{
				int centerX = (rcDraw.right + rcDraw.left)/2;
				int centerY = (rcDraw.bottom + rcDraw.top)/2;
				int w = rcDraw.Width();
				int h = rcDraw.Height();
				rcDraw.left = centerX-w*zoom/200;
				rcDraw.right = centerX+w*zoom/200;
				rcDraw.top = centerY - h*zoom/200;
				rcDraw.bottom = centerY+ h*zoom/200;
			}
			pImage->Draw(pDcContainer->GetDC(), &rcDraw,zoom);  
			pDcContainer->invalidateRect();
			//pDcContainer->DcToFrame(rcDrawSrc);		
		}
	}
	static int PlayFile(wstring str)
	{
		//if (sPlayFile == str)
		//{
		//	return 0;
		//}
		degree = 0;
		if (str.empty())
		{
			return 0;
		}
		sPlayFile = str;
		//RETAILMSG(1, (TEXT("1-----------\r\n")));
		pImage->ReleaseResource();
		//RETAILMSG(1, (TEXT("2-----------\r\n")));
		if (GetFileAttributes(str.c_str()) == -1)
		{
			return 0;
		}
		if(!pImage->PrepareImage(str.c_str(), 800, 480))
		{
			return 0;
		}
		//RETAILMSG(1, (TEXT("3-----------\r\n")));
		pImage->DecodeImage(0);
		//RETAILMSG(1, (TEXT("4-----------\r\n")));

		zoom = 100;
		Draw();
		//RETAILMSG(1, (TEXT("5-----------\r\n")));
		degree = 0;
		return 1;
	}
	static void Release()
	{
		pImage->ReleaseResource();
	}
	static void Rotate()
	{
		degree += 90;
		if (degree >= 360)
		{
			degree = 0;
		}
		pImage->RotateImage(degree);
		zoom = 100;
		Draw();
	}
	static void ZoomIn()
	{
		zoom /= 2;
		if (zoom < 25)
		{
			zoom = 25;
		}
		Draw();
	}
	static void ZoomOut()
	{
		zoom *= 2;
		if (zoom > 400)
		{
			zoom = 100;
		}
		Draw();
	}
	static wstring GetPlayFile()
	{
		return sPlayFile;
	}
	static void Init()
	{
		pImage = new CImage;
	}
};

