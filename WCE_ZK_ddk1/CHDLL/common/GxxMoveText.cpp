#include "StdAfx.h"
#include "GxxMoveText.h"
#include "XmlDef.h"
#include "ControlHelp.h"
#include "StrHelp.h"
#include "LangStringManager.h"
static RegisterHelp help("GxxMoveText", GxxMoveText::CreateControl);
const int STEP_LEN = 3;
GxxView* GxxMoveText::CreateControl()
{
	return new GxxMoveText;
}

GxxMoveText::GxxMoveText()
{
	m_idTimer = RegisterTimer(100);
	m_bNeedTimer = false;
	setOnlyDrawActRect(true);
}

GxxMoveText::~GxxMoveText()
{
	UnRegisterTimer(m_idTimer); 
}

void GxxMoveText::Draw(  )
{
	//»æÖÆÎÄ×Ö
	RECT rc = m_ActRect;
	if (m_bNeedTimer)
	{
		int nMove = m_ActRect.right - m_ActRect.left -m_nCount*STEP_LEN;
		::SetRect(&rc, rc.left+nMove, rc.top, rc.right+nMove, rc.bottom);
	}
	if (NULL!=m_wstrFromId)
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(*m_wstrFromId, rc, m_format,m_wfont);
	}else
	{
		SkiaBitmapManager::GetInstance()->DrawTextInRect(m_wstrText, rc, m_format,m_wfont);
	}	
}


void GxxMoveText::OnTextSet()
{
	if (NULL!=m_wstrFromId)
	{
		m_nTextLen = SkiaBitmapManager::GetInstance()->GetTextLen(*m_wstrFromId,m_wfont);
	}
	else
	{
		m_nTextLen = SkiaBitmapManager::GetInstance()->GetTextLen(m_wstrText,m_wfont);
	}
	if (m_nTextLen>300)
	{
		m_nTextLen = 300;
	}
	if (m_nTextLen > m_ActRect.right - m_ActRect.left)
	{
		m_bNeedTimer = true;
		m_nCount = 0;
		StartTimer(m_idTimer);
	}
	else
	{
		if (m_bNeedTimer)
		{
			m_bNeedTimer= false;
			StopTimer(m_idTimer);
		}
	}
}

void GxxMoveText::TimerTick( UINT nIDEvent )
{
	m_nCount++;
	if (m_nCount>(m_nTextLen + m_ActRect.right - m_ActRect.left)/STEP_LEN)
	{
		m_nCount =0;
	}
	AfxInvalidateRect(&m_ActRect);
}

void GxxMoveText::onResume()
{
	OnTextSet();
}

void GxxMoveText::onPause()
{
	if (m_bNeedTimer)
	{
		StopTimer(m_idTimer);
	}
}
