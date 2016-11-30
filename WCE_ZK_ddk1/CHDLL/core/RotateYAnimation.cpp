#include "StdAfx.h"

#include "RotateYAnimation.h"
#include "StrHelp.h"

RotateYAnimation::RotateYAnimation( float fb,float fe,TypeInter tInter /*= T_LinerInter*/ )
:Animation(ROTATE_Y,tInter)
{
	//ASSERT(fb>=0.0f&&fe<=1.0f&&fe>fb);
	m_fromRotate = fb;
	m_toRotate = fe;
}

//BOOL RotateYAnimation::RenewAlpha()
//{
//
//}

void RotateYAnimation::renewAction(int nth, UINT len)
{
	m_rotateValue = m_interp_type->fun_tween(nth,m_fromRotate,m_toRotate-m_fromRotate,len);
}
