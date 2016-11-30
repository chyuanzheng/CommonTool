#include "StdAfx.h"
#include "GxxPhoneListLine.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "GxxAniPictureA.h"
#include "GxxSwText.h"
#include "GxxDelimiter.h"


GxxPhoneListLine::GxxPhoneListLine()
{
	m_pTextTitle = new GxxSwText;
	m_pTextTitle->setFormat(DT_VCENTER|DT_LEFT);
	m_pTextTitle->setTextFont(0xffffffff,26);
	AddCtrl(m_pTextTitle);


	m_pPhoneNumText = new GxxSwText;
	m_pPhoneNumText->setFormat(DT_VCENTER|DT_LEFT);
	m_pPhoneNumText->setTextFont(0xffffffff,26);
	AddCtrl(m_pPhoneNumText);
}

GxxPhoneListLine::~GxxPhoneListLine()
{
	delete m_pTextTitle;
	delete m_pPhoneNumText;
}

void GxxPhoneListLine::setPhoneLine( int index, int top,const wstring& wstr,const wstring& wstr2)
{

	m_index = index;
	RECT p_rect = getParentView()->getCtrRect();
	int nlineHeight = ResStringManager::GetInstance()->getInt("ListLineHeight");
	::SetRect(&m_ActRect,p_rect.left,top,p_rect.right,top +nlineHeight);

	m_pTextTitle->setText(wstr);
	RECT rc = m_ActRect;
	rc.right  = rc.left + 150; 
	m_pTextTitle->setCtrRect(rc);
	m_pTextTitle->setOnlyDrawActRect(true);

	rc = m_ActRect;
	rc.left += 180; 
	m_pPhoneNumText->setText(wstr2);
	m_pPhoneNumText->setCtrRect(rc);

	//CheckEnable();

}

const wstring & GxxPhoneListLine::getLineName()
{
	return m_pTextTitle->getText();
}




