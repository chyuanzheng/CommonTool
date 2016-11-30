#pragma once

#include "Animation.h"
#include "DllDefine.h"


class CE_CONTROL_API ScaleAnimation: public Animation
{
public:
	ScaleAnimation(float fromX,float toX,float fromY,float toY,PIVOT_TYPE pivotXType,float pivotXValue,PIVOT_TYPE pivotYType,float pivotYValue,TypeInter tInter = T_LinerInter);

	//先变化X的，再变化Y轴的
	//BOOL  RenewScale();
	void renewAction(int nth, UINT len);

	PIVOT_TYPE getPivotXType(){return m_pivottypeX;}
	PIVOT_TYPE getPivotYType(){return m_pivottypeY;}

	float getPivotXValue(){return m_pivotX;}
	float getPivotYValue(){return m_pivotY;}

	float getScaleXValue(){return m_scaleX;}
	float getScaleYValue(){return m_scaleY;}
private:
	float m_fromXScale;
	float m_toXScale;
	float m_fromYScale;
	float m_toYScale;
	float m_pivotX;
	float m_pivotY;
	PIVOT_TYPE   m_pivottypeX;
	PIVOT_TYPE   m_pivottypeY;

	float m_scaleX;
	float m_scaleY;
};

