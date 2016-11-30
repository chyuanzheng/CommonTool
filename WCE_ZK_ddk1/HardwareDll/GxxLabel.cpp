#pragma once
#include "StdAfx.h"
#include "GxxLabel.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
//
//#include "aygshell.h"

GxxLabel::GxxLabel()
{
	//��Ҫ�����ڴ�ı�������Ҫ��Ĭ�Ϲ��캯���и���ֵ
	m_handleUp = NULL;
	m_isGxxLabelDown = FALSE;
	handleOldUp = NULL;
	
}

GxxLabel::~GxxLabel()
{

	if (m_handleUp!=NULL)
	{
		
		SkiaBitmapManager::GetInstance()->DeInitImage(m_handleUp);
	}

}



void GxxLabel::Draw(  )
{
	

	//������Ϊ��
	
	if( m_isGxxLabelDown == TRUE )
	{

			//��ԭʼͼƬ
			if (NULL!=m_handleUp)
			{
				SkiaBitmapManager::GetInstance()->DrawImage(m_handleUp,&m_ActRect,80);//80

			}

		
	}
	//������Ϊ�� 
	else 
	{
		//��ԭʼͼƬ
		if (NULL!=m_handleUp)
		{
			SkiaBitmapManager::GetInstance()->DrawImage(m_handleUp,&m_ActRect);
		}
		
	}

	

	//��������
	if(!wstrText.empty())
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(wstrText, m_ActRect, DT_CENTER | DT_VCENTER);
	}
	//��������
	else if(!strText.empty())
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(strText, m_ActRect, DT_CENTER | DT_VCENTER);
	}

}



void GxxLabel::SetText(const wstring & str, BOOL bDraw/* = TRUE*/)
{
	ASSERT(this != NULL);
	wstrText = str;
	if(bDraw)
	{
		AfxInvalidateRect(&m_ActRect);
	}
}

void GxxLabel::SetText(string str, BOOL bDraw/* = TRUE*/)
{
	strText = str;
	if(bDraw)
	{
		AfxInvalidateRect(&m_ActRect);
	}
}

BOOL GxxLabel::InMyArea( int x, int y )
{
	//�ж�����
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

//����ַ�
void GxxLabel::Empty()
{
	strText.empty();
	wstrText.empty();
}

BOOL GxxLabel::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			//::SetCapture( m_hWnd );
			m_isGxxLabelDown = TRUE;
			AfxInvalidateRect(&m_ActRect);
			//AfxPostMessage( CTR_MESSAGE, (WPARAM)this, MES_LBUTTONDOWN );
			return TRUE;
		}
		return FALSE;

	case WM_LBUTTONUP:
		//������ť����������
		if( m_isGxxLabelDown == TRUE )
		{
			//::ReleaseCapture();
			m_isGxxLabelDown = FALSE;
			AfxInvalidateRect(&m_ActRect);
			if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
			{
	
				AfxPostMessage( CTR_MESSAGE, (WPARAM)this, MES_LBUTTONUP );
				
			}
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
}

////ͨ�����ĵ���λ�þ���
//CRect GxxLabel::setCtrolLayoutByCenterPoint(int pointX, int pointY, int width, int height)
//{
//	CRect rect;
//
//	rect.left = iCenterX - iWidth/2;
//	rect.top =  iCenterY - iHeight/2;
//	rect.right =  iWidth + rect.left;
//	rect.bottom =  iHeight + rect.top;
//	return rect;
//}

void GxxLabel::setCtrLayout( TiXmlElement * ele )
{
	string path;
	AfxGetWorkPathA(path);

	//SkiaInfo* m_handleUp ;
	const char* pa = ele->Attribute(BTN_UP);
	//string strTail;
	if (NULL!=pa)
	{
		 m_handleUp = SkiaBitmapManager::GetInstance()->InitImage((path + string(pa)).c_str());

		 ASSERT(m_handleUp != NULL);

		 handleOldUp = m_handleUp;
		// iWidth = m_handleUp->ctrRect.fLeft;//)->width();
		iWidth =  SkiaBitmapManager::GetInstance()->GetWidth(m_handleUp);
		iHeight = SkiaBitmapManager::GetInstance()->GetHeight(m_handleUp);
	}
	
	const CHAR *elename = ele->Attribute(CTR_NAME);
	if (NULL!=elename)
	{
		setCtrName(elename);
	}

	setCtrRectUseCenter(ele,iWidth,iHeight);
	

	
	SkiaBitmapManager::GetInstance()->SetRect(m_handleUp,&m_ActRect);
	
	if(ele->Attribute(LABEL_TEXT))
	{
		strText = ele->Attribute(LABEL_TEXT);
	}
	
	
}


GxxView* GxxLabel::CreateControl()
{
	return new GxxLabel;
}

static RegisterHelp help("GXXLABEL", GxxLabel::CreateControl);