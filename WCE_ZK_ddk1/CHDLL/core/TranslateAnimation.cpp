#include "StdAfx.h"

#include "TranslateAnimation.h"
#include "StrHelp.h"



TranslateAnimation::TranslateAnimation( float fromX,float toX,float fromY,float toY,TypeInter tInter /*= T_LinerInter*/ )
:Animation(TRANSLATE,tInter)
{
	//ASSERT(fb>=0.0f&&fe<=0.1f&&fb>fe);
	m_fromX= fromX;
	m_toX = toX;
	m_fromY = fromY;
	m_toY = toY;
}



void TranslateAnimation::renewAction(int nth, UINT len )
{

	m_tranX = m_interp_type->fun_tween(nth,m_fromX,m_toX-m_fromX,len);
	m_tranY = m_interp_type->fun_tween(nth,m_fromY,m_toY-m_fromY,len);
}
