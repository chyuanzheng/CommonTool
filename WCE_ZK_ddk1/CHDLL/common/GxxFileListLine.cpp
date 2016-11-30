#include "StdAfx.h"
#include "GxxFileListLine.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "GxxAniPictureA.h"
#include "GxxSwText.h"
#include "GxxDelimiter.h"
#include "bluetooth.h"

#include "GxxPicture.h"
#include "LangStringManager.h"

GxxPicture *GxxFileListLine::S_iconMusic = NULL;//左边 icon
GxxPicture *GxxFileListLine::S_iconMovie = NULL;//左边 icon
GxxPicture *GxxFileListLine::S_iconPicture = NULL;//左边 icon
GxxPicture *GxxFileListLine::S_iconFolder = NULL;//左边 icon
GxxSwText  *GxxFileListLine::S_pTextName = NULL;//左边 icon

GxxFileListLine::GxxFileListLine()
{
	m_icon_type =NoneLine;
	m_strText_id = NULL;
	bool b;
	if (NULL== S_iconMusic)
	{
		S_iconMusic = new GxxPicture;
		const char* ani_path = ResStringManager::GetInstance()->getString("IconMusic");
		b = S_iconMusic->setPicHandle(ani_path);
		ASSERT(b);
	}

	if (NULL== S_iconMovie)
	{
		S_iconMovie = new GxxPicture;
		const char* ani_path = ResStringManager::GetInstance()->getString("IconMovie");
		b = S_iconMovie->setPicHandle(ani_path);
		ASSERT(b);
	}

	if (NULL== S_iconPicture)
	{
		S_iconPicture = new GxxPicture;
		const char* ani_path = ResStringManager::GetInstance()->getString("IconPicture");
		b = S_iconPicture->setPicHandle(ani_path);
		ASSERT(b);
	}

	if (NULL== S_iconFolder)
	{
		S_iconFolder = new GxxPicture;
		const char* ani_path = ResStringManager::GetInstance()->getString("IconFolder");
		b = S_iconFolder->setPicHandle(ani_path);
		ASSERT(b);
	}


	if (NULL== S_pTextName)
	{
		S_pTextName = new GxxSwText;
		S_pTextName->setFormat(DT_VCENTER|DT_LEFT);
		S_pTextName->setTextFont(0xffffffff,26);
		//ASSERT(b);
	}


}

GxxFileListLine::~GxxFileListLine()
{
}


void GxxFileListLine::Draw()
{
	GxxLBLine::Draw();
	RECT rcText = m_ActRect;
	RECT rcIcon = m_ActRect;
	::SetRect(&rcIcon,rcIcon.left+10,rcText.top+10,rcIcon.left+50,rcText.top+50);
	switch(m_icon_type)
	{
	case NoneLine:
		rcText.left += 10;
		S_pTextName->DrawTextWithRect( m_strText_id,m_strText,rcText);
		break;
	case MusicLine:
		rcText.left += 70;
		S_pTextName->DrawTextWithRect( m_strText_id,m_strText,rcText);
		S_iconMusic->DrawPicWithRect(rcIcon);
		break;
	case MovieLine:
		rcText.left += 70;
		S_pTextName->DrawTextWithRect( m_strText_id,m_strText,rcText);
		S_iconMovie->DrawPicWithRect(rcIcon);
		break;
	case PictureLine:
		rcText.left += 70;
		S_pTextName->DrawTextWithRect( m_strText_id,m_strText,rcText);
		S_iconPicture->DrawPicWithRect(rcIcon);
		break;
	case FolderLine:
		rcText.left += 70;
		S_pTextName->DrawTextWithRect( m_strText_id,m_strText,rcText);
		S_iconFolder->DrawPicWithRect(rcIcon);
		break;
	default:
		ASSERT(0);
		break;
	}
}


//这个是文件列表框用的
void GxxFileListLine::setFileLine( int index,const wstring  & wstr,ICON_TYPE type ,HANDLE h)
{
	m_index = index;
	RECT p_rect = getParentView()->getCtrRect();
	::SetRect(&m_ActRect,p_rect.left,0,p_rect.right,GxxLBLine::S_nlineHeight);
	m_icon_type = type;

	m_strText = wstr;
	m_handle = h;

}

void GxxFileListLine::setFileLine( int index,const string &str_id,ICON_TYPE type,HANDLE h )
{
	m_index = index;
	RECT p_rect = getParentView()->getCtrRect();
	::SetRect(&m_ActRect,p_rect.left,0,p_rect.right,GxxLBLine::S_nlineHeight);
	m_icon_type = type;

	m_strText_id = LangStringManager::GetInstance()->getString(str_id);
	m_handle = h;
}


