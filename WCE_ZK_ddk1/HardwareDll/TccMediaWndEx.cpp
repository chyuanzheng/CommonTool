#include "StdAfx.h"
#include "TccMediaWndEx.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
static RegisterHelp help("TCCMEDIAWNDEX", TccMediaWndEx::CreateControl);


void TccMediaWndEx::setCtrLayout( TiXmlElement * ele )
{
	//根据中心点确定控件位置
	GxxView::setCtrRectUseCenter(  ele );
	
	//保存位置信息
	rcOld = m_ActRect;

	

	const CHAR *elename = ele->Attribute(CTR_NAME);
	if (NULL!=elename)
	{
		setCtrName(elename);
	}

	if(ele->Attribute(LABEL_TEXT))
	{
		strText = ele->Attribute(LABEL_TEXT);
	}


}



void TccMediaWndEx::SetFun(FunButton fun, void*	_dwParam)
{

	funClick = fun;
	dwParam = _dwParam;

}

void TccMediaWndEx::setDraw(bool bShow)	//显示或隐藏
{
	TccMediaWnd::setDraw(bShow);
	if(!bShow)
	{
		pLabelWarnning->setDraw(false);
	}
	else
	{
		if(bBrake)	//刹车
		{
			pLabelWarnning->setDraw(false);
		}
		else
		{
			pLabelWarnning->setDraw(true);
		}
	}
	
}

//设置警告语
void TccMediaWndEx::SetWarning(GxxAniLable* pLabel, bool bIsShow)
{
	pLabelWarnning = pLabel;

	pLabelWarnning->setDraw(bIsShow);

}




void TccMediaWndEx::Draw(  )
{
	
	//绘制背景
	SkiaBitmapManager::GetInstance()->DrawColor(backColor,&m_ActRect);

}


//用于判断是否全屏
bool TccMediaWndEx::IsFullScreen()
{
	int iHeight = abs(m_ActRect.top - m_ActRect.bottom);
	int iWidth = abs(m_ActRect.right - m_ActRect.left);
	return (iHeight == 480 && iWidth == 800);
}



BOOL TccMediaWndEx::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if(InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{
			if(IsFullScreen())	//全屏状态
			{
				if(funClick)
				{
					funClick(this, dwParam);
				}
			}
			else
			{
				if(funClick)
				{
					funClick(this, dwParam);
				}
			}
			return TRUE;
		}
		return FALSE;
	default:
		return FALSE;
	}
}

//实现全屏
void TccMediaWndEx::SetFullScreen()
{
	

	m_ActRect.left = 0;
	m_ActRect.top = 0;
	m_ActRect.right = 800;
	m_ActRect.bottom = 480;

	MediaControl::SetMediaRect(CRect(0, 0, 800, 480));
	//Move(0, 0, 800, 480, 1);
	//iLayer = 2;
	//AlwaysOnBottom(0);
	MediaControl::SetVMode(1);
}

//缩小屏幕
void TccMediaWndEx::ReductionScreen()
{
	m_ActRect = rcOld;

	MediaControl::SetMediaRect(CRect(m_ActRect.left, m_ActRect.top, m_ActRect.right, m_ActRect.bottom));
	//Move(0, 0, 800, 480, 1);
	//iLayer = 2;
	//AlwaysOnBottom(0);
	MediaControl::SetVMode(1);
}

BOOL TccMediaWndEx::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL TccMediaWndEx::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if(message == WM_LBUTTONDOWN)
	{
		ptClickPosX = LOWORD( lParam );
		ptClickPosY = HIWORD( lParam );
	//	RETAILMSG(COUT_MSG, (TEXT("TccMediaWndEx x=%d,y=%d \r\n"), ptClickPosX, ptClickPosY));
	}		
	
	return GxxView::DealCtrlMsg(message, wParam, lParam);
}