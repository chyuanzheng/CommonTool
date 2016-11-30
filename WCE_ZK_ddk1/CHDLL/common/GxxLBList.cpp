#include "StdAfx.h"
#include "GxxLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxSetupListLine.h"
#include "LangStringManager.h"

const int MOVE_LEN = 10;
const int MOVE_MIN = 20;

GxxLBList::GxxLBList()
{
	m_titleFromId = NULL;
	m_nLineStart = m_nLineEnd = 0;
	

	m_uTimerId = RegisterTimer(30);
	m_preListBox= NULL;
	m_isBtnDown = false;
	m_bStartMove = false;
	m_nOverMove = 0;
	m_nHaveMove = 0;
	ResStringManager::GetInstance()->getRect("ListBoxRect",m_ActRect);
	m_nPageNum = (m_ActRect.bottom - m_ActRect.top)/GxxLBLine:: S_nlineHeight;
	setOnlyDrawActRect(true);
	m_bMoveLine = true;
}

GxxLBList::~GxxLBList()
{
	UnRegisterTimer(m_uTimerId);
}



void GxxLBList::SetNameTitle( TiXmlElement * ele )
{
	setCtrName(ele);

	const CHAR *titleid = ele->Attribute(LISTBOX_TITLE_ID);
	if (NULL!=titleid)
	{
		m_titleFromId = LangStringManager::GetInstance()->getString(titleid);
	}
	else
	{
		const CHAR *title = ele->Attribute(LISTBOX_TITLE);
		if(NULL!=title)
		{
			m_title = title;
		}
	}
}



void GxxLBList::setPreListBox( GxxLBList * pre )
{
	m_preListBox  = pre;
}





BOOL GxxLBList::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case TR_IS_IN_MOVE:
		return m_bStartMove;

	case WM_LBUTTONDOWN: 
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			AfxSendMessage(CTR_CYCLE_STOP,0,0);
			StopTimer(m_uTimerId);
			m_isBtnDown = true;
			m_bStartMove = false;
			m_nStartY = HIWORD( lParam );
			return TRUE;

		}
		break;
	case  WM_MOUSEMOVE:
		if (m_isBtnDown)//需要移动
		{
			int nY = HIWORD( lParam );
			int nmoveY = (nY-m_nStartY);
			if (!m_bStartMove)
			{
				if (::abs(nmoveY) > MOVE_LEN)
				{
					m_bStartMove = true;
					GxxLBLine::S_ClearBtnDown();

				}
			}
			if (m_bMoveLine && m_bStartMove && (getCtrlsSize() > m_nPageNum-1))//在多于 m_nPageNum-1的时候可以进行滑动,而且必须允许滑动
			{
				m_nStartY = nY;
				MoveLineList(nmoveY);
				CaculateRation(false,false);

			}
			else
			{
				m_bStartMove = false;

			}
			return TRUE;
		}
		break;

	case WM_LBUTTONUP://
		if(m_isBtnDown )
		{
			//checkMove(HIWORD( lParam ));
			//AfxPostMessage(CTR_CYCLE_STOP,WPARAM(true),0);
			if (m_bStartMove)
			{
				CaculateRation();
				AfxInvalidateRect(&m_ActRect);
			}
			

			m_isBtnDown = false;
			return true;

		}
		break;
	default:
		break;
	}
	return false;

}


void GxxLBList::onPause()
{
	if(m_isBtnDown )
	{
		//checkMove(HIWORD( lParam ));
		//AfxPostMessage(CTR_CYCLE_STOP,WPARAM(true),0);
		StopTimer(m_uTimerId);
		GxxLBLine::S_ClearBtnDown();
		m_isBtnDown = false;
	}

}

//回到第一项
void GxxLBList::ResetPosition()
{
	int n =GetTopLen();
	if (n!=0)
	{
		MoveLineList(n);
		//m_nOverMove = 0;
		CaculateRation(false);
	}
}


void GxxLBList::TimerTick( UINT nIDEvent )
{
	ASSERT(m_uTimerId == nIDEvent);
	if (m_nOverMove == 0)
	{
		m_bStartMove = false;
		StopTimer(m_uTimerId);
		return;
	}
	int ntoMove = 0;
	UINT nlen = ::abs(m_nOverMove);
	if (nlen > MOVE_MIN)
	{
		ntoMove = nlen*3/5;
	}
	else
	{
		ntoMove = 10;
	}
	if (m_nOverMove<0)
	{
		ntoMove = -ntoMove;
		if (ntoMove < m_nOverMove)
		{
			ntoMove = m_nOverMove;
		}
	}
	else
	{
		if (ntoMove > m_nOverMove)
		{
			ntoMove = m_nOverMove;
		}
	}
	MoveLineList(ntoMove);
	m_nOverMove -= ntoMove;
}

//列表下移动的时候，nmoveY为正数。反之。
void GxxLBList::MoveLineList( int nmoveY )
{
	m_nHaveMove += nmoveY;
	//setMoveRect(0,nmoveY);//移动
	AfxInvalidateRect(&m_ActRect);
}


void GxxLBList::MoveToLine( int nline )
{
	//MoveLineList
	if (nline>=m_nLineStart && nline < (m_nLineEnd-1) )
	{
		return;
	}
	if (nline>=0 && nline<m_nLineStart)
	{
		MoveLineList( (m_nLineStart-nline)*GxxLBLine:: S_nlineHeight );
		CaculateRation(false);
	}
	else if (nline>= (m_nLineEnd-1)&&nline<getCtrlsSize())
	{
		if (m_nLineEnd == getCtrlsSize())
		{
			return;
		}
		MoveLineList( (m_nLineEnd-nline-1)*GxxLBLine:: S_nlineHeight );
		CaculateRation(false);
	}
}
void GxxLBList::MoveToLineMid( int nline )
{
	//MoveLineList
	if (nline<0 || nline >= getCtrlsSize())
	{
		return;
	}
	int nstart_mid = (m_nLineStart+m_nLineEnd-1)/2;
	int ntomove = nstart_mid-nline;

	MoveLineList(ntomove*GxxLBLine:: S_nlineHeight );
	CaculateRation(false);

}


void GxxLBList::CaculateRation( bool b_needAni/*=true*/, bool b_needMove/*=true*/ )
{
	int nslen = GetTopLen();
	int nyu = nslen%GxxLBLine:: S_nlineHeight;
	if (nyu > GxxLBLine:: S_nlineHeight/2 || nyu < -GxxLBLine:: S_nlineHeight/2)
	{
		nslen += nyu;
	}
	m_nLineStart = nslen/GxxLBLine:: S_nlineHeight;
	m_nLineEnd =  m_nLineStart + m_nPageNum;


	if (m_nPageNum >= getCtrlsSize())
	{
		m_nLineEnd = getCtrlsSize();
		m_nLineStart =  0;
	}
	else if (m_nLineStart < 0)
	{
		m_nLineStart = 0;
		m_nLineEnd = m_nPageNum;	
	}
	else if (m_nLineEnd > getCtrlsSize())
	{
		m_nLineStart = getCtrlsSize() -m_nPageNum; 
		m_nLineEnd = getCtrlsSize();
	}

	m_startPos = m_pCtrlVet->begin();
	std::advance(m_startPos,m_nLineStart);


	if (b_needMove)
	{
		m_nOverMove = GetTopLen() - m_nLineStart*GxxLBLine:: S_nlineHeight;

		if (0 != m_nOverMove)
		{
			if (!b_needAni)
			{
				MoveLineList(m_nOverMove);//不需要回弹
				m_nOverMove =0;
				//StopTimer(m_uTimerId);
			}
			else
			{
				StartTimer(m_uTimerId);
				TimerTick(m_uTimerId);

			}
		}
	}

	GxxView *p = getParentView();
	if (NULL != p)
	{
		p->TranslateMessage(CTR_TRANLATE_MES,0,0);
	}
}


/** 控件的消息处理入口函数 
    （WM_DESTROY WM_EXIT_PROSS WM_PAINT 不在此处理）
    
    先处理本控件中的子控件的消息
	然后再处理本控件的消息 （Response）
*/
BOOL GxxLBList::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( !getDraw()||!getEnable())
	{
		if (message < WM_USER || CTR_ANIMATION_MES ==  message|| CTR_MESSAGE ==  message)
		{
			return FALSE;
		}

		//if (0x119==message || WM_LBUTTONDOWN==message || WM_LBUTTONUP ==message || WM_MOUSEMOVE ==  message || CTR_MESSAGE ==  message || WM_SETCURSOR ==  message || CTR_ANIMATION_MES ==  message)
		//{
		//	return FALSE;//
		//}
		
	}

	int nline = m_nLineEnd - m_nLineStart;
	if (message == WM_MOUSEMOVE|| nline==0)
	{
		return GxxLBList::Response(message,wParam,lParam);//子控件不需要处理 WM_MOUSEMOVE消息
	}

	ControlList::iterator pos_deal= m_startPos;	

	int i = 0;
	while(i < nline)
	{
		if ((*pos_deal)->DealCtrlMsg(message, wParam, lParam ))
		{
			return TRUE;
		}
		++pos_deal;
		i++;
	}


	return Response(message, wParam, lParam );

}


void GxxLBList::Paint()
{
	if (!getDraw())
	{
		return;
	}

	if ( getOnlyDrawActRect() )
	{
		SkiaBitmapManager::GetInstance()->SaveStatus();
		SkiaBitmapManager::GetInstance()->SetClipRect(m_ActRect);
	}
	Draw();


	int nline = m_nLineEnd - m_nLineStart;
	if ( nline!=0)
	{
		ControlList::iterator pos_deal= m_startPos;	
		int nStartTop = GxxLBLine::S_nlineHeight*m_nLineStart + m_ActRect.top + m_nHaveMove;
		if (pos_deal != m_pCtrlVet->begin())
		{
			--pos_deal;
			++nline;
			nStartTop -= GxxLBLine::S_nlineHeight;
		}
		int i = 0;
		while(i < nline)
		{
			((GxxLBLine*)(*pos_deal))->PaintLine(nStartTop);
			nStartTop += GxxLBLine::S_nlineHeight;
			++pos_deal;
			i++;
		}
		if (pos_deal!= m_pCtrlVet->end())
		{
			((GxxLBLine*)(*pos_deal))->PaintLine(nStartTop);
		}
	}





	if (getOnlyDrawActRect())
	{
		SkiaBitmapManager::GetInstance()->ReleasStatus();
	}
}

void GxxLBList::MovePage( bool bNext )
{
	int npageheight = m_nPageNum*GxxLBLine:: S_nlineHeight;
	if (bNext)//向后
	{

		MoveLineList(-npageheight);
	}
	else
	{
		MoveLineList(npageheight);
	}

	CaculateRation(false);
	AfxInvalidateRect(&m_ActRect);
	
}

void GxxLBList::getFRation( float & fs, float &fe )
{
	int nsize = getCtrlsSize();
	if (nsize==0)
	{
		fs = 0.0;
		fe = 1.0;
		return;
	}
	fs = float(m_nLineStart)/nsize;
	fe = float(m_nLineEnd)/nsize;

}

int GxxLBList::GetTopLen()
{
	return -m_nHaveMove;
}


void GxxLBList::FreshListBox()
{
	CaculateRation(false);
}







