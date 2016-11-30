#include "StdAfx.h"
#include "GxxMsgBox.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GxxPicture.h"
#include "GxxSwText.h"
#include "LangStringManager.h"

GxxMsgBox * GxxMsgBox::S_msgBox = NULL;
static RegisterHelp help("GxxMsgBox", GxxMsgBox::CreateControl);
GxxView* GxxMsgBox::CreateControl()
{
	ASSERT(S_msgBox == NULL);
	S_msgBox = new GxxMsgBox;
	return S_msgBox;
}


GxxMsgBox::GxxMsgBox()
{
	m_pPicBack = new GxxPicture;
	m_textlable = new GxxSwText;
	setDraw(false);
	setOnlyDrawActRect(true);
	m_uTimerId = RegisterTimer(1000);
}

GxxMsgBox::~GxxMsgBox()
{
	delete m_pPicBack;
	delete m_textlable;
	UnRegisterTimer(m_uTimerId);
}

void GxxMsgBox::Draw(  )
{
	m_pPicBack->DrawPicWithRect(m_ActRect);
	m_textlable->DrawTextWithRect(m_ActRect);
}


BOOL GxxMsgBox::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;
	return FALSE;
}

void GxxMsgBox::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRectUseCenter(ele);

	m_defRect = m_ActRect;

	const char* pa = ele->Attribute(BACK_BMP);
	if (m_pPicBack->setPicHandle(pa))
	{
		m_textlable->setTextFont(0xffffffff,22);

	}


}

void GxxMsgBox::ShowMsgBox( const string& text, UINT time, LPCRECT rc,bool bIsID )
{
	ASSERT(S_msgBox != NULL);
	S_msgBox->DoShowMsgBox(text,time,rc,bIsID);
}

void GxxMsgBox::DoShowMsgBox( const string& text, UINT time, LPCRECT rc ,bool bIsID )
{
	if (time == 0)//0 等于取消显示
	{
		setDraw(false);
		invalidateRect();
		StopTimer(m_uTimerId);
		return;
	}

	if (bIsID)
	{
		m_textlable->setText(LangStringManager::GetInstance()->getString(text));
	}
	else
	{
		m_textlable->setText(text.c_str());
	}
	
	m_timeCount = time;
	ASSERT(m_timeCount > 0);
	if (rc != NULL)
	{
		setCtrRect(*rc);
	}
	else
	{
		setCtrRect(m_defRect);
	}
	setDraw(true);
	if (m_uTimerId != UINT(-1))//-1就永远显示
	{
		StartTimer(m_uTimerId);
	}
	invalidateRect();
}

void GxxMsgBox::TimerTick( UINT nIDEvent )
{
	m_timeCount--;
	if (m_timeCount == 0)
	{
		setDraw(false);
		StopTimer(m_uTimerId);
		invalidateRect();
		return;
	}
}

void GxxMsgBox::onPause()
{
	if (getDraw())
	{
		setDraw(false);
		StopTimer(m_uTimerId);
		invalidateRect();
	}

}
