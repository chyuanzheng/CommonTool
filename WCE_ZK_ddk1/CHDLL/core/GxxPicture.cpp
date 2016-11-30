#include "StdAfx.h"
#include "GxxPicture.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"


GxxPicture::GxxPicture()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_hPicture = NULL;

}

GxxPicture::~GxxPicture()
{

	releaseHandle();
}



void GxxPicture::Draw(  )
{
	if(NULL!=m_hPicture)
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_hPicture);
	}
	
}


bool GxxPicture::setPicHandle( TiXmlElement * ele,const char *attr )
{
	return  setPicHandle( ele->Attribute(attr) );
}
bool GxxPicture::setPicHandle( const char* picPath )
{
	if(NULL!=picPath)
	{
		DoSetHandle(AfxAddWorkPathA(picPath));
	}
	return m_hPicture != NULL;
}



bool GxxPicture::ResetPicHandle( const char* picPath )
{
	if(NULL!=picPath)
	{
		releaseHandle();
		m_hPicture =  SkiaBitmapManager::GetInstance()->InitImage(picPath,NULL,false);
	}
	return m_hPicture != NULL;
}

bool GxxPicture::bindHandleRect()
{
	if(NULL!=m_hPicture)
	{
		SkiaBitmapManager::GetInstance()->SetRect(m_hPicture,&m_ActRect);
		return true;
	}
	return false;
	
}

bool GxxPicture::bindHandleRect( const RECT &rc )
{
	if(NULL!=m_hPicture)
	{
		SkiaBitmapManager::GetInstance()->SetRect(m_hPicture,&rc);
		return true;
	}
	return false;
}

bool GxxPicture::setHandleAlpha( UINT a )
{
	if (NULL!=m_hPicture)
	{
		SkiaBitmapManager::GetInstance()->SetAlpha(m_hPicture,a);
		return true;
	}
	return false;
}

int GxxPicture::getPicWidth()
{
	if (NULL==m_hPicture)
	{
		return 0;
	}
	return SkiaBitmapManager::GetInstance()->GetWidth(m_hPicture);
}

int GxxPicture::getPicHeight()
{
	if (NULL==m_hPicture)
	{
		return 0;
	}
	return SkiaBitmapManager::GetInstance()->GetHeight(m_hPicture);
}

void GxxPicture::onMoveRect( int x_len, int y_len )
{
	GxxView::onMoveRect(x_len,y_len);
	bindHandleRect();
}

void GxxPicture::releaseHandle()
{
	if (m_hPicture!=NULL)
	{		
		SkiaBitmapManager::GetInstance()->DeInitImage(m_hPicture);
		m_hPicture=NULL;
	}
}


void GxxPicture::DrawPicWithRect( const RECT &rc,UINT alpha /*= 255*/ )
{
	if (getDraw())
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_hPicture,&rc,alpha);
	}
	
}

void GxxPicture::DrawPic()
{

	if (getDraw())
	{
		Draw( );
	}
	
	
}


void GxxPicture::DrawPicWithRect( int xm,int ym,UINT alpha /*= 255*/ )
{
	RECT rt;
	::SetRect(&rt,m_ActRect.left+xm,m_ActRect.top+ym,m_ActRect.right+xm,m_ActRect.bottom+ym);
	DrawPicWithRect(rt,alpha);
}

void GxxPicture::setPicRect( int cx,int cy )
{
	if (NULL!=m_hPicture)
	{
		setCtrRectUseCenter(cx,cy,getPicWidth(),getPicHeight());
	}
}

void GxxPicture::DoSetHandle( const char* picPath )
{
	releaseHandle();
	m_hPicture =  SkiaBitmapManager::GetInstance()->InitImage(picPath);
}

void GxxPicture::DoSetHandle( const WCHAR* picPath )
{
	releaseHandle();
	m_hPicture =  SkiaBitmapManager::GetInstance()->InitImage(picPath);
}






