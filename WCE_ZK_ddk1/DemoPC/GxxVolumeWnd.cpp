#include "GxxVolumeWnd.h"
#include "CRect.h"
#include "SkiaBitmapManager.h"

GxxVolumeWnd* GxxVolumeWnd::This = NULL;

GxxVolumeWnd::GxxVolumeWnd(void)
{
	This = this;
}
GxxVolumeWnd::~GxxVolumeWnd(void)
{
	m_hWnd = NULL;
}

void GxxVolumeWnd::ShowWindow(int nCmdShow)
{
	ASSERT(m_hWnd != NULL);
	::ShowWindow(m_hWnd, nCmdShow);
}

void GxxVolumeWnd::CreateWnd(TCHAR* szClassName, DWORD dwStyle, int x, int y, int width, int height, HWND hParentWnd, HINSTANCE hInstance)
{
	//hGRTInstance = hInstance;
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc0;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = NULL;
	wc.hCursor       = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szClassName;
	ATOM ret = ::RegisterClass(&wc);
	int error = GetLastError();
	m_hWnd =  CreateWindow(szClassName, szClassName, dwStyle, x, y, width, height, hParentWnd, NULL, hInstance, NULL);
	error = GetLastError();
	//Create(hGxWnd, 0, 0, width, height, NULL);
	//CreateMotionThread();
}

void GxxVolumeWnd::Paint()
{
	//if (T_DRAW_TRASITION == s_bInTransition)
	{
		//RECT rect = AfxGetDcRect();
	//	SkiaBitmapManager::GetInstance()->DrawColor(0xff888888,&AfxGetDcRect());
	//	if (m_bShowBottom)
		{
		//	SkiaBitmapManager::GetInstance()->DrawImage(m_hPicture);
		}

		/*if (m_bShowTop)
		{
			SkiaBitmapManager::GetInstance()->DrawImage(m_hPicture);
		}*/

	}
	
	
		GxxView::Paint();
	
}

LRESULT CALLBACK GxxVolumeWnd::WndProc0(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_CREATE:;
		break;
	case WM_PAINT:
		
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		This->Paint();
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		{
			break;
		}
	case WM_LBUTTONDOWN:
		{
			CRect rect(0, 0 , 800, 480);
			//InvalidateRect(hWnd)
			::InvalidateRect(hWnd,&rect, 1);
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL GxxVolumeWnd::setContentView( const CHAR* layout )
{
	BOOL ret = FALSE;
	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	ret = xmlDoc->LoadFile(AfxAddWorkPathA(layout));
	if (!ret)
	{
		OutputDebugString(L"setContentView LoadFile error! \r\n");
		ASSERT(0);
		return FALSE;
	}

	TiXmlElement *root = xmlDoc->RootElement();
	/*if (strcmp(root->Value(), ABSOLUTE) != 0)
	{
		ASSERT(0);
		return FALSE;
	}*/

	setCtrName(root);
	setCtrRect(root);
	setPicHandle(root,BACKGROUD);
	bindHandleRect();



	TiXmlElement * chid = root->FirstChildElement();
	setCtrList(chid);

	return TRUE;
}