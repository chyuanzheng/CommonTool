#include "StdAfx.h"
#include "GxxLBLine.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "GxxAniPictureA.h"
#include "GxxSwText.h"
#include "GxxDelimiter.h"
//

const int GxxLBLine:: S_nlineHeight = ResStringManager::GetInstance()->getInt("ListLineHeight");
GxxLBLine * GxxLBLine::s_downBtn = NULL;
GxxAniPictureA * GxxLBLine::S_pAniPicBack = NULL;
GxxPicture * GxxLBLine::S_pPicDelimiter = NULL;
GxxLBLine::GxxLBLine()
{
	m_isBtnDown = false;

	if (NULL== GxxLBLine::S_pAniPicBack)
	{
		GxxLBLine::S_pAniPicBack = new GxxAniPictureA;
		const char* ani_path = ResStringManager::GetInstance()->getString("ListLineAniBack");
		bool b =S_pAniPicBack->setPicHandle(ani_path);
		ASSERT(b);
	}

	if (NULL== GxxLBLine::S_pPicDelimiter)
	{
		GxxLBLine::S_pPicDelimiter = new GxxPicture;
		bool b = GxxLBLine::S_pPicDelimiter->setPicHandle(ResStringManager::GetInstance()->getString("short_delimiter"));
		ASSERT(b);
	}
	
}

GxxLBLine::~GxxLBLine()
{
	

}




BOOL GxxLBLine::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN: 
		if( InMyArea( getParentView()->getCtrRect(),LOWORD(lParam ), HIWORD(lParam) ) //必须在父控件内
			&& InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{		
			getParentView()->TranslateMessage(nMsg, wParam,lParam);
			if ( !getParentView()->TranslateMessage(TR_IS_IN_MOVE,0,0) )
			{
				GxxLBLine::s_downBtn = this;
				m_isBtnDown = true;
				AddCtrl(S_pAniPicBack);
				S_pAniPicBack->setCtrRect(m_ActRect);
				S_pAniPicBack->bindHandleRect();
				S_pAniPicBack->Start();
				AfxInvalidateRect(&m_ActRect);
			}
			return TRUE;//让父类处理 消息
		}
		return FALSE;

	case WM_LBUTTONUP://
		if(m_isBtnDown )
		{
			ClearBtnDown();
			saftGetParentView()->TranslateMessage(nMsg, wParam,lParam);
			saftGetParentView()->saftGetParentView()->TranslateMessage( CTR_LISTLINE_MES, (WPARAM)this, m_index );//直接发送到gruop
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
	return FALSE;
}



void GxxLBLine::PaintLine( int ntop )
{

	if (!getDraw())
	{
		return;
	}

	int nNeedMove = ntop - m_ActRect.top;
	if (nNeedMove!=0)
	{
		setMoveRect(0,nNeedMove);
	}

	Draw();

	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{
		(*pos)->Paint(  );		
		pos++;
	}

}


void GxxLBLine::Draw(  )
{


	RECT rc;
	SetRect(&rc,m_ActRect.left,m_ActRect.bottom-2,m_ActRect.right,m_ActRect.bottom);
	S_pPicDelimiter->DrawPicWithRect(rc);
}










void GxxLBLine::ClearBtnDown()
{
	GxxLBLine::s_downBtn = NULL;
	m_isBtnDown = false;
	S_pAniPicBack->Stop();
	removeCtrl(S_pAniPicBack);
	AfxInvalidateRect(&m_ActRect);
}



void GxxLBLine::S_ClearBtnDown()
{
	if (s_downBtn)
	{
		s_downBtn->ClearBtnDown();
	}
}


