#include "StdAfx.h"
#include "DtvMediaWndEx.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "TVCommand.h"
static RegisterHelp help("DtvMediaWndEx", DtvMediaWndEx::CreateControl);


void DtvMediaWndEx::setCtrLayout( TiXmlElement * ele )
{
	//根据中心点确定控件位置
	setCtrName(ele);
	GxxView::setCtrRectUseCenter(  ele );
	
	//保存位置信息
	rcOld = m_ActRect;

	// << cyz  2013-8-5
	setCtrList( ele->FirstChildElement() );
	GxxAniLable* lable = (GxxAniLable *)findViewByName("LabelWarnning");
	if (lable)
	{
		pLabelWarnning = lable;
		pLabelWarnning->setDraw(false);
	}
	//cyz  2013-8-5 >>


}



void DtvMediaWndEx::setDraw(bool bShow)	//显示或隐藏
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





void DtvMediaWndEx::Draw(  )
{
	
	//绘制背景
	SkiaBitmapManager::GetInstance()->DrawColor(backColor,&m_ActRect);

}




BOOL DtvMediaWndEx::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if(InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{
			if (m_mesView)
			{
				m_mesView->TranslateMessage(DTV_Click_Media_Wnd,(WPARAM)this,0);
			}
			return TRUE;
		}
		return FALSE;
	default:
		return FALSE;
	}
}

//实现全屏
void DtvMediaWndEx::SetFullScreen()
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
void DtvMediaWndEx::ReductionScreen()
{
	m_ActRect = rcOld;

	MediaControl::SetMediaRect(CRect(m_ActRect.left, m_ActRect.top, m_ActRect.right, m_ActRect.bottom));
	//Move(0, 0, 800, 480, 1);
	//iLayer = 2;
	//AlwaysOnBottom(0);
	MediaControl::SetVMode(1);
}


