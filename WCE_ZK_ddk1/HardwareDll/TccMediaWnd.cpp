#include "stdafx.h"
#include "TccMediaWnd.h"
#include "ControlHelp.h"
#include "pip/PIP.h"
#include "param.h"
#include "GxxLabel.h"

TccMediaWnd::TccMediaWnd()
{
	//colBack = RGB(16, 0, 16) | 0xFF000000;
	//SetMsgHandler(WM_LBUTTONDOWN, LButtonDownHandler, (DWORD)this);
	//SetMsgHandler(WM_MOUSEMOVE, MouseMoveHandler, (DWORD)this);
	bAutoTop = 0;
	bAlwaysOnBottom = 1;
	bEnableVideo = 1;

	backColor = 0xff160016;

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = CarBrakeChange;
	GXNotify::RegisterNotifyHandler("car_brake_change", notify);

	pLabelWarnning = NULL;
//	bAllowShowWarning = true;
	bBrake = true;
}

TccMediaWnd::~TccMediaWnd()
{

}

void TccMediaWnd::CreateFromXml(TiXmlElement *pXmlElement)
{
	//GxxWindow::CreateFromXml(pXmlElement);
	//sBackupBackImage.FromUTF8(pXmlElement->Attribute("backupimg"));
}

LRESULT TccMediaWnd::OnLButtonDown(POINT pt)
{
	if (!bEnableVideo)
	{
		return 0;
	}
	CRect rc = m_ActRect;
	if (rc.PtInRect(pt) && bAlwaysOnBottom == 0)
	{
		//if (iLayer == 0)
		//{
		//	KillTimer(0);
		//	MediaControl::SetVMode(1);
		//	iLayer = 2;
		//	Invalidate(1);
		//}
		//else
		//{
		//	MediaControl::SetVMode(180);
		//	iLayer = 0;
		//	Invalidate(1);
		//}
	}
	return 0;
}

GxxView* TccMediaWnd::CreateControl()
{
	return new TccMediaWnd;
}

DWORD TccMediaWnd::LButtonDownHandler(GxxView *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{
	if (pControl->getDraw())
	{
		//pControl->SetTimer(0, 3000, NULL);
	}
	return 0;
}

DWORD TccMediaWnd::MouseMoveHandler(GxxView *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{

	if (pControl->getDraw())
	{
	//	pControl->SetTimer(0, 3000, NULL);
	}
	return 0;
}

LRESULT TccMediaWnd::OnTimer(UINT nID)
{
	if (!bEnableVideo)
	{
		return 0;
	}
	if (nID == 0)
	{
		//KillTimer(0);
		//if (bAutoTop)
		//{
		//	SetLayer(2);
		//	Invalidate(1);
		//	MediaControl::SetVMode(1);
		//}
	}
	return 1;
}
void TccMediaWnd::ShowWindow(int show, int redraw)
{
	//GXBaseControl::ShowWindow(show, redraw);
	if (show == 0)
	{
		MediaControl::SetVMode(1);
	}
}

void TccMediaWnd::AutoTopScreen(BOOL b)
{
	/*bAutoTop = b;
	if (!b)
	{
		KillTimer(0);
	}
	else
	{
		SetTimer(0, 3000, NULL);
	}*/
}

void TccMediaWnd::SetTopScreen(BOOL b)
{
	/*if (b)
	{
		SetLayer(2);
	}
	else
	{
		SetLayer(0);
	}*/
//	Invalidate(1);
}

void TccMediaWnd::AlwaysOnBottom(BOOL b, BOOL redraw)
{
	if (b)
	{
		bAlwaysOnBottom = 1;
		//AutoTopScreen(0);
		//SetLayer(0);
		if (redraw)
		{
			CRect rect;
			getCtrRect(rect);
			AfxInvalidateRect(&rect);
		}
	}
	else
	{
		bAlwaysOnBottom = 0;
		//AutoTopScreen(1);
	}
}
bool TccMediaWnd::GetVideoEnable()
{
	return bEnableVideo;
}

void TccMediaWnd::CloseVideo(BOOL redraw)
{
	if (bEnableVideo == 0)
	{
		return;
	}
	bEnableVideo = 0;
	//sImageBack = sBackupBackImage;
	//iLayer = 0;
	backColor = 0xff161616;
	if (redraw)
	{
		CRect rect;
		getCtrRect(rect);
		AfxInvalidateRect(&rect);
	}
}

void TccMediaWnd::ShowVideo(BOOL redraw)
{
	if (bEnableVideo == 1)
	{
		return ;
	}
	bEnableVideo = 1;
	//sImageBack.Empty();
	backColor = 0xff160016;
	if (redraw)
	{
		CRect rect;
		getCtrRect(rect);
		AfxInvalidateRect(&rect);
	}
}

bool TccMediaWnd::GetIsBrake()
{
	return bBrake;
}

// 刹车变化需要做出反应
LRESULT TccMediaWnd::CarBrakeChange(DWORD param1, DWORD param2)
{
	if (sysConfig.sysParam.BrakeDetect)	// 1 不检测刹车
	{
		// 如果不检测刹车,不作出反应
		return 0;
	}
	bBrake = param1;
	if (param1)
	{
		
		// 当前刹车状态,显示视频
		pLabelWarnning->setDraw(false);
		backColor = 0xff160016;
		AfxInvalidateRect(NULL);

	}
	else
	{
		
		// 当前行驶状态,显示警告语
		//bBrake = false;
		if(getDraw())	//视频窗口显示时，才去显示警告语
		{
			pLabelWarnning->setDraw(true);
		}
		
		backColor = 0xff161616;
		AfxInvalidateRect(NULL);
		

	}
	return 0;
}
void TccMediaWnd::SetBackColor(COLORREF color)
{
	//if ((color & (0xFF<<24)) == 0)
	//{
	//	colBack = color | (0xFF<<24);
	//}
	//else
	//{
	//	colBack = color;
	//}
}


static RegisterHelp help("TCCMEDIAWND", TccMediaWnd::CreateControl);