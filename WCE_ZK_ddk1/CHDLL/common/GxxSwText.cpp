#include "StdAfx.h"
#include "GxxSwText.h"
#include "XmlDef.h"
#include "ControlHelp.h"
#include "StrHelp.h"
#include "LangStringManager.h"
static RegisterHelp help("GxxSwText", GxxSwText::CreateControl);
GxxView* GxxSwText::CreateControl()
{
	return new GxxSwText;
}


GxxSwText::GxxSwText():m_wstrFromId(NULL)
{
	m_format = DT_CENTER | DT_VCENTER;
	m_wfont  = NULL;
	m_size = 20;
	m_alpha = 255;
	m_color = 0xffffffff;

}

GxxSwText::~GxxSwText()
{
	if (NULL!=m_wfont)
	{
		SkiaBitmapManager::GetInstance()->DeInitFont(m_wfont);
	}
}

void GxxSwText::Draw(  )
{
	//»æÖÆÎÄ×Ö
	if (NULL!=m_wstrFromId)
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(*m_wstrFromId, m_ActRect, m_format,m_wfont);
	}else
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(m_wstrText, m_ActRect, m_format,m_wfont);
	}
	
}

void GxxSwText::setTextFont( UINT color,int size,UINT alpha/*=255*/,SkiaBitmapManager::T_TYPEFACE textType /*= SkiaBitmapManager::msyh*/ )
{
	if (NULL!=m_wfont)
	{
		SkiaBitmapManager::GetInstance()->DeInitFont(m_wfont);
	}
	m_wfont = SkiaBitmapManager::GetInstance()->InitFont(color,size,SkiaBitmapManager::SK_UTF16,textType,alpha);
	m_size = size;
	m_color = color;
	m_alpha = alpha;
}


void GxxSwText::setColor( UINT color )
{
	m_color = color;
	setTextFont(m_color,m_size,m_alpha);
}

void GxxSwText::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	if (!setCtrRectUseCenter(ele))
	{
		setCtrRect(getParentView()->getCtrRect());
	}
	

	const char *catrri = ele->Attribute(LABEL_TEXT);
	if (NULL != catrri)
	{
		m_wstrText = StrHelp::StringToWString(string(catrri));
	}

	catrri = ele->Attribute(LABEL_TEXT_ID);
	if (NULL != catrri)
	{
		m_wstrFromId = LangStringManager::GetInstance()->getString(catrri);
	}


	catrri = ele->Attribute(ZKY_SIZE);
	if (NULL != catrri)
	{
		ele->Attribute(ZKY_SIZE,&m_size);
	}


	catrri = ele->Attribute(COLOR);
	if (NULL != catrri)
	{
		m_color = StrHelp::StrToInt(catrri);
	}

	catrri = ele->Attribute(ALPHA,&m_alpha);
	if (NULL == catrri)
	{
		m_alpha = 255;
	}
	setTextFont(m_color,m_size,m_alpha);



	catrri = ele->Attribute("from_color");
	if (NULL != catrri)
	{
		int  nfrom_color,nto_color;
		nfrom_color = StrHelp::StrToInt(catrri);

		catrri = ele->Attribute("to_color");
		ASSERT(NULL != catrri);
		nto_color = StrHelp::StrToInt(catrri);

		double yform,yto;

		catrri = ele->Attribute("from_pos",&yform);
		ASSERT(NULL != catrri);

		catrri = ele->Attribute("to_pos",&yto);
		ASSERT(NULL != catrri);
			
		int ny0,ny1;
		int nw = m_ActRect.bottom - m_ActRect.top;
		ny0 = yform*nw + m_ActRect.top;
		ny1 = yto*nw + m_ActRect.top;

		SkiaBitmapManager::GetInstance()->SetTextGradient(m_wfont,nfrom_color,nto_color,ny0,ny1);
	}

	catrri = ele->Attribute(FORMAT);
	if (NULL != catrri)
	{
		m_format = 0;
		TL_STR tl_str;
		StrHelp::StringToSubStr(string(catrri),tl_str, '-');
		TL_STR::iterator pos;
		for (pos=tl_str.begin();pos!=tl_str.end();++pos)
		{
			if ( "center"==*pos)
			{
				m_format |= DT_CENTER;
			}
			else if ("vcenter"==*pos)
			{
				m_format |= DT_VCENTER;
			}
			else if ("left"==*pos)
			{
				m_format |= DT_LEFT;
			}
			else if ("right"==*pos)
			{
				m_format |= DT_RIGHT;
			}
			else if ("top"==*pos)
			{
				m_format |= DT_TOP;
			}
			else if ("bottom"==*pos)
			{
				m_format |= DT_BOTTOM;
			}
		}

	}
	else
	{
		m_format = DT_CENTER | DT_VCENTER;
	}

	int nmargin = 0;
	if (ele->Attribute(TOPMARGIN))
	{

		ele->Attribute(TOPMARGIN,&nmargin);
		m_ActRect.top += nmargin; 
	}
	if (ele->Attribute(LEFTMARGIN))
	{

		ele->Attribute(LEFTMARGIN,&nmargin);
			m_ActRect.left += nmargin; 
	}
	if (ele->Attribute(BOTTOMMARGIN))
	{

		ele->Attribute(BOTTOMMARGIN,&nmargin);
			m_ActRect.bottom -= nmargin; 
	}
	if (ele->Attribute(RIGHTMARGIN))
	{

		ele->Attribute(RIGHTMARGIN,&nmargin);
			m_ActRect.right -= nmargin; 
	}
	//OnTextSet();
}

void GxxSwText::setTextFromId( const string& sid )
{
	m_wstrFromId = LangStringManager::GetInstance()->getString(sid);
	OnTextSet();
}

void GxxSwText::setText( const char *str )
{
	ASSERT(NULL!=str);
	m_wstrText = StrHelp::StringToWString(string(str));
	m_wstrFromId=NULL;
	OnTextSet();
}

void GxxSwText::setText( const wstring& wstr )
{
	m_wstrText = wstr;
	m_wstrFromId=NULL;
	OnTextSet();
}

void GxxSwText::setText( const wstring* textFromId )
{
	m_wstrFromId = textFromId;
	OnTextSet();
}

void GxxSwText::DrawTextWithRect(const RECT &rc )
{
	if (NULL!=m_wstrFromId)
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(*m_wstrFromId, rc, m_format,m_wfont);
	}else
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(_T("ÄãºÃ"), rc, m_format,m_wfont);
	}

}

void GxxSwText::DrawTextWithRect( int xm,int ym )
{
	RECT rt;
	::SetRect(&rt,m_ActRect.left+xm,m_ActRect.top+ym,m_ActRect.right+xm,m_ActRect.bottom+ym);
	DrawTextWithRect(rt);
}

void GxxSwText::DrawTextWithRect( const wstring &text,const RECT &rc )
{
	SkiaBitmapManager::GetInstance()->DrawTextInRect(text, rc, m_format,m_wfont);
}

void GxxSwText::DrawTextWithRect( const wstring *text_id,const wstring &text,const RECT &rc )
{
	if (text_id!=NULL)
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(*text_id, rc, m_format,m_wfont);
	}
	else
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(text, rc, m_format,m_wfont);
	}
}



