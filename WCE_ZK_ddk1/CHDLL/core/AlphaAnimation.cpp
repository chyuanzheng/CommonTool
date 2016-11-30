#include "StdAfx.h"

#include "AlphaAnimation.h"
#include "StrHelp.h"

AlphaAnimation::AlphaAnimation( float fb,float fe,TypeInter tInter /*= T_LinerInter*/ )
:Animation(ALPHA,tInter)
{
	//ASSERT(fb>=0.0f&&fe<=1.0f&&fe>fb);
	m_fromAlpha = fb;
	m_toAlpha = fe;
}

//BOOL AlphaAnimation::RenewAlpha()
//{
//
//}

void AlphaAnimation::renewAction(int nth, UINT len)
{
	m_alphaValue = m_interp_type->fun_tween(nth,m_fromAlpha,m_toAlpha-m_fromAlpha,len);
}
