#include "StdAfx.h"

#include "ScaleAnimation.h"
#include "StrHelp.h"





ScaleAnimation::ScaleAnimation( float fromX,float toX,float fromY,float toY,PIVOT_TYPE pivotXType,float pivotXValue,PIVOT_TYPE pivotYType,float pivotYValue,TypeInter tInter /*= T_LinerInter*/ )
:Animation(SCALE,tInter)
{
	//ASSERT(fb>=0.0f&&fe<=0.1f&&fb>fe);
	m_fromXScale = fromX;
	m_toXScale = toX;
	m_fromYScale = fromY;
	m_toYScale = toY;
	m_pivotX = pivotXValue;
	m_pivotY = pivotYValue;
	m_pivottypeX = (pivotXType);
	m_pivottypeY = (pivotYType);
}


//BOOL ScaleAnimation::RenewScale()
//{
//
//}

void ScaleAnimation::renewAction(int nth, UINT len)
{

	m_scaleX = m_interp_type->fun_tween(nth,m_fromXScale,m_toXScale-m_fromXScale,len);
	m_scaleY = m_interp_type->fun_tween(nth,m_fromYScale,m_toYScale-m_fromYScale,len);
}
