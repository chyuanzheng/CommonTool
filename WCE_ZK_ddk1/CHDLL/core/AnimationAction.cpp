#include "StdAfx.h"
#include "AnimationAction.h"

#include "SkiaBitmapManager.h"
#include "GxxView.h"
AnimationAction::AnimationAction()
{
	m_lenth = 0;
	m_delay = 0;
	m_bAfter_draw = true;
	m_bBefore_draw = true;
}

AnimationAction::~AnimationAction()
{
	TL_ANIMATION::iterator pos;

	for (pos=m_listAnimation.begin();pos!=m_listAnimation.end();pos++)
	{
		delete (*pos);
	}
}

void AnimationAction::setDuration( UINT t )
{
	ASSERT(t>=ANIMOTION_TIME);
	m_lenth = t/ANIMOTION_TIME;
}

void AnimationAction::setDelay( int t )
{
	m_delay = t/ANIMOTION_TIME;
}
void AnimationAction::PreAction( int tick,BOOL fromRvt )
{
	int iner_tick = tick-m_delay;
	if (iner_tick>=0&&iner_tick<=m_lenth)
	{

		TL_HANDLE::iterator h_pos;

		for (h_pos=m_listHandle.begin();h_pos!=m_listHandle.end();h_pos++)
		{
			SkiaBitmapManager::GetInstance()->PreAction(*h_pos);
		}
	}

}
void AnimationAction::Action( int tick,BOOL fromRvt )
{
	int iner_tick = tick-m_delay;

	TL_ANIMATION::iterator pos;
	TL_HANDLE::iterator h_pos;


	if (iner_tick>=0&&iner_tick<=m_lenth)
	{

		for (pos=m_listAnimation.begin();pos!=m_listAnimation.end();pos++)
		{
			(*pos)->renewAction(iner_tick,m_lenth);

			for (h_pos=m_listHandle.begin();h_pos!=m_listHandle.end();h_pos++)
			{
				SkiaBitmapManager::GetInstance()->DoAction(*h_pos,*pos);
			}
		}
		AfxInvalidateRect(&m_Rect);//( &(*pos) );//更新显示本动画的区域
	}

	if (!m_bBefore_draw && iner_tick<0 )
	{
		for (h_pos=m_listHandle.begin();h_pos!=m_listHandle.end();h_pos++)
		{
			SkiaBitmapManager::GetInstance()->NotInAction(*h_pos);
		}
	}

	if (!m_bAfter_draw && iner_tick> m_lenth)
	{
		for (h_pos=m_listHandle.begin();h_pos!=m_listHandle.end();h_pos++)
		{
			SkiaBitmapManager::GetInstance()->NotInAction(*h_pos);
		}
	}
	if (iner_tick == 0)
	{

		AfxPostMessage( CTR_ANIMATION_MES, (WPARAM)this, MAKELONG(ANIMATION_START, fromRvt));//向控件发送完成的消息	
	
	}
	else if (m_lenth==iner_tick)
	{

		AfxPostMessage( CTR_ANIMATION_MES, (WPARAM)this, MAKELONG(ANIMATION_END,fromRvt) );//向控件发送完成的消息
	}
}


void AnimationAction::AddHandle( HANDLE h )
{
	if (NULL != h)
	{
		m_listHandle.push_back(h);
	}
}
void AnimationAction::RemoveHandle( HANDLE h )
{
	m_listHandle.remove(h);
}


void AnimationAction::ClearHandles()
{
	m_listHandle.clear();
}
void AnimationAction::AddAnimation( Animation * ani )
{
	m_listAnimation.push_back(ani);
}


void AnimationAction::SetAniRect(const RECT &rt )
{
	m_Rect = (rt);
}


Animation * AnimationAction::getAnimation( const char *name /*= NULL*/ )
{
	ASSERT(m_listAnimation.size()>0);
	string strname ;
	if (NULL!=name)
	{
		strname = name;
	}
	else
	{
		return *m_listAnimation.begin();
	}
	
	TL_ANIMATION::iterator pos;
	for (pos=m_listAnimation.begin();pos!=m_listAnimation.end();pos++)
	{
		const char *sname = (*pos)->getName();
		if (NULL!=sname && strname == sname)
		{
			return *pos;
		}

	}
	ASSERT(0);
	return NULL;
}



