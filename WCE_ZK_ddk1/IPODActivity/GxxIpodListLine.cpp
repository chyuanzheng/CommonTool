#include "StdAfx.h"
#include "GxxIpodListLine.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
//#include "GxxThreeBtnA.h"
#include "ResStringManager.h"
#include "GxxAniPictureA.h"
#include "GxxSwText.h"
#include "GxxDelimiter.h"
//#include "bluetooth.h"

#include "GxxPicture.h"
#include "LangStringManager.h"

GxxSwText  *GxxIpodListLine::S_pTextName = NULL;//×ó±ß icon
GxxIpodListLine::GxxIpodListLine()
{
	if (NULL== S_pTextName)
	{
		S_pTextName = new GxxSwText;
		S_pTextName->setFormat(DT_VCENTER|DT_LEFT);
		S_pTextName->setTextFont(0xffffffff,26);
		//ASSERT(b);
	}
	m_strText_id = NULL;
}

GxxIpodListLine::~GxxIpodListLine()
{

}

void GxxIpodListLine::Draw()
{
	GxxLBLine::Draw();
	RECT rcText = m_ActRect;
	rcText.left += 10;
	if (m_strText_id!=NULL)
	{
		S_pTextName->DrawTextWithRect( *m_strText_id,rcText);
	}
	else
	{
		S_pTextName->DrawTextWithRect( m_strText,rcText);
		//RETAILMSG(COUT_MSG, (TEXT("m_strText = %s\r\n"), m_strText.c_str()));
	}
	
}



void GxxIpodListLine::setIpodLine( int nth, const string * s_id, const wstring * s )
{
	m_index = nth;
	RECT p_rect = getParentView()->getCtrRect();
	::SetRect(&m_ActRect,p_rect.left,0,p_rect.right,GxxLBLine::S_nlineHeight);
	if ( s_id)
	{
		m_strText_id = LangStringManager::GetInstance()->getString(*s_id);
	}
	else
	{
		m_strText = *s;
	}

}

const wstring& GxxIpodListLine::GetTextName()
{
	if (m_strText_id)
	{
		return *m_strText_id;
	}
	return m_strText;
}



