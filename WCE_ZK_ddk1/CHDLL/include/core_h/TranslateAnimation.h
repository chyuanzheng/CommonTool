#pragma once

#include "Animation.h"
#include "DllDefine.h"


class CE_CONTROL_API TranslateAnimation: public Animation
{
public:
	TranslateAnimation(float fromX,float toX,float fromY,float toY,TypeInter tInter = T_LinerInter);
	//先变化X的，再变化Y轴的
	//BOOL  RenewTranslate( );
	void renewAction(int nth, UINT len);
	float getTranXValue(){return m_tranX;}
	float getTranYValue(){return m_tranY;}
	 
private:
	float m_fromX;
	float m_toX;
	float m_fromY;
	float m_toY;

	float m_tranX;
	float m_tranY;
};

