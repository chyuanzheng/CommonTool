#include "StdAfx.h"
#include "AEdit.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
//#include "aygshell.h"

AEdit::AEdit()
{
	//��Ҫ�����ڴ�ı�������Ҫ��Ĭ�Ϲ��캯���и���ֵ

}

AEdit::~AEdit()
{

}

void AEdit::Draw( )
{
	//::DrawText(hdcDst,m_text.c_str(),m_text.size(),&m_ActRect,DT_LEFT);
}


BOOL AEdit::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;
	return FALSE;
}

void AEdit::setCtrLayout( TiXmlElement * ele )
{
	GxxView::setCtrLayout(ele);
}

void AEdit::SetText( const WCHAR * t )
{
	m_text = t;
	AfxInvalidateRect(&m_ActRect);
}

