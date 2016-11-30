#pragma once
#include "StdAfx.h"
#include "GxxTextBox.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"


GxxTextBox::GxxTextBox()
{
	m_picIcon = NULL;
	m_swtext = NULL;
	
}

GxxTextBox::~GxxTextBox()
{

}

void GxxTextBox::setCtrLayout( TiXmlElement * ele )
{
	GxxPicIcon::setCtrLayout(ele );

	ASSERT(NULL == m_swtext);
	m_swtext = new GxxSwText;
	AddCtrl(m_swtext);
	m_swtext->setCtrRect(m_ActRect);
	m_swtext->setTextFont(0xff000000,25);
	

}

void GxxTextBox::SetText( const wstring &str, bool bDraw /*= true*/ )
{	
	m_swtext->setText(str);
	if (bDraw)
	{
		AfxInvalidateRect(&m_ActRect);
	}
}



void GxxTextBox::SetText( const char *str,bool bDraw /*= true*/ )
{
	m_swtext->setText(str);
	if (bDraw)
	{
		AfxInvalidateRect(&m_ActRect);
	}
}

//清空
void GxxTextBox::DeleteAll()
{
	SetText(L"", true);
}

//是否为空
bool GxxTextBox::IsEmpty()
{
	ASSERT(m_swtext != NULL);
	wstring wstr = m_swtext->getText();
	if(wstr.size() == 0)
	{
		return true;
	}
	return false;
	
}

//获取长度
int GxxTextBox::GetLength()
{
	ASSERT(m_swtext != NULL);
	wstring wstr = m_swtext->getText();
	return wstr.size();
}

//增加一个字符
bool GxxTextBox::AddOneChar(char c)
{
	ASSERT(m_swtext != NULL);
	wstring wstr = m_swtext->getText();
	wstr.append(1,c);
	SetText(wstr, true);
	return true;
}

//删除一个字符
bool GxxTextBox::DeleteOneChar()
{
	ASSERT(m_swtext != NULL);
	wstring wstr = m_swtext->getText();
	if(wstr.size() <= 0)
	{
		return false;
	}
	wstring newwstr;
	newwstr = wstr.substr(0,wstr.size()-1);

	SetText(newwstr, true);
	return true;
}

wstring GxxTextBox::GetText()
{
	ASSERT(m_swtext != NULL);
	wstring wstr = m_swtext->getText();
	return wstr;
}






BOOL GxxTextBox::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		
		return FALSE;

	case WM_LBUTTONUP:
		
		return FALSE;
	default:
		return FALSE;
	}
}

GxxView* GxxTextBox::CreateControl()
{
	return new GxxTextBox;
}

static RegisterHelp help("GxxTextBox", GxxTextBox::CreateControl);