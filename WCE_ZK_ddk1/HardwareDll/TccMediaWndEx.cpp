#include "StdAfx.h"
#include "TccMediaWndEx.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
static RegisterHelp help("TCCMEDIAWNDEX", TccMediaWndEx::CreateControl);


void TccMediaWndEx::setCtrLayout( TiXmlElement * ele )
{
	//�������ĵ�ȷ���ؼ�λ��
	GxxView::setCtrRectUseCenter(  ele );
	
	//����λ����Ϣ
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

void TccMediaWndEx::setDraw(bool bShow)	//��ʾ������
{
	TccMediaWnd::setDraw(bShow);
	if(!bShow)
	{
		pLabelWarnning->setDraw(false);
	}
	else
	{
		if(bBrake)	//ɲ��
		{
			pLabelWarnning->setDraw(false);
		}
		else
		{
			pLabelWarnning->setDraw(true);
		}
	}
	
}

//���þ�����
void TccMediaWndEx::SetWarning(GxxAniLable* pLabel, bool bIsShow)
{
	pLabelWarnning = pLabel;

	pLabelWarnning->setDraw(bIsShow);

}




void TccMediaWndEx::Draw(  )
{
	
	//���Ʊ���
	SkiaBitmapManager::GetInstance()->DrawColor(backColor,&m_ActRect);

}


//�����ж��Ƿ�ȫ��
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
			if(IsFullScreen())	//ȫ��״̬
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

//ʵ��ȫ��
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

//��С��Ļ
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
	//�ж�����
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