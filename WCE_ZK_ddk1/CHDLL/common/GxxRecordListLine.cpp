#include "StdAfx.h"
#include "GxxRecordListLine.h"
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


GxxPicture *GxxRecordListLine::S_iconInCall = NULL;//×ó±ß icon
GxxPicture *GxxRecordListLine::S_iconOutCall = NULL;//×ó±ß icon
GxxPicture *GxxRecordListLine::S_iconCallMiss = NULL;//×ó±ß icon

GxxSwText  *GxxRecordListLine::S_pText= NULL;
int  GxxRecordListLine::S_nwith = 0;
int  GxxRecordListLine::S_nheight = 0;

GxxRecordListLine::GxxRecordListLine()
{
	if (NULL== S_iconInCall)
	{
		bool b;
		S_iconInCall = new GxxPicture;
		const char* ani_path = ResStringManager::GetInstance()->getString("InCall");
		b = S_iconInCall->setPicHandle(ani_path);
		ASSERT(b);

		S_iconOutCall = new GxxPicture;
		ani_path = ResStringManager::GetInstance()->getString("OutCall");
		b = S_iconOutCall->setPicHandle(ani_path);
		ASSERT(b);

		S_iconCallMiss = new GxxPicture;
		ani_path = ResStringManager::GetInstance()->getString("CallMiss");
		b = S_iconCallMiss->setPicHandle(ani_path);
		ASSERT(b);

		S_nwith = S_iconCallMiss->getPicWidth();
		S_nheight = S_iconCallMiss->getPicHeight();

		S_pText = new GxxSwText;
		S_pText->setFormat(DT_VCENTER|DT_LEFT);
		S_pText->setTextFont(0xffffffff,26);
	}

}

GxxRecordListLine::~GxxRecordListLine()
{

}

void GxxRecordListLine::setRecordLine( int index, int top,const wstring& wstr ,RecordItem::RecordType rt, const wstring &date, const wstring &strPerson )
{

	m_rtype = rt;
	m_index = index;
	RECT p_rect = getParentView()->getCtrRect();
	::SetRect(&m_ActRect,p_rect.left,top,p_rect.right,top +S_nlineHeight);
	m_strDate = date;
	m_strName = wstr;
	m_strPerson = strPerson;

	//CheckEnable();

	//int d =  ((m_ActRect.bottom-m_ActRect.top)-h)/2;
	//RECT rect;
	//::SetRect(&rect,m_ActRect.left, m_ActRect.top+d,  m_ActRect.left+w, m_ActRect.top+d+h);
	//m_phoneIcon->setCtrRect(rect);
	//m_phoneIcon->bindHandleRect();

	//::SetRect(&rect,m_ActRect.left+w+20, m_ActRect.top,  m_ActRect.right, m_ActRect.bottom);
	//m_pTextTitle->setText(wstr);
	//m_pTextTitle->setCtrRect(rect);


	//::SetRect(&rect,580, m_ActRect.top,  800, m_ActRect.bottom);
	//m_pTextDate->setText(date);
	//m_pTextDate->setCtrRect(rect);

}

const wstring & GxxRecordListLine::getLineName()
{
	return m_strName;
}

const wstring & GxxRecordListLine::getDate()
{
	return m_strDate;
}

const wstring & GxxRecordListLine::getPerson()
{
	return m_strPerson;
}

void GxxRecordListLine::Draw()
{
	GxxLBLine::Draw();

	RECT rcIcon;
	int d =  ((m_ActRect.bottom-m_ActRect.top)-S_nheight)/2;
	::SetRect(&rcIcon, m_ActRect.left+10,m_ActRect.top+d, m_ActRect.left+10+S_nwith, m_ActRect.top+d+S_nheight);

	switch(m_rtype)
	{
	case RecordItem::INCALL:
		S_iconInCall->DrawPicWithRect(rcIcon);
		break;
	case RecordItem::OUTCALL:
		S_iconOutCall->DrawPicWithRect(rcIcon);
		break;
	case RecordItem::CALLMISS:
		S_iconCallMiss->DrawPicWithRect(rcIcon);
		break;
	default:
		//ASSERT(0);
		break;
	}

	RECT rcText = m_ActRect;
	rcText.left = rcIcon.right + 20;

	S_pText->DrawTextWithRect( m_strPerson,rcText);

	rcText.left = rcIcon.right + 300;
	S_pText->DrawTextWithRect( m_strName,rcText);//m_strDate
}



