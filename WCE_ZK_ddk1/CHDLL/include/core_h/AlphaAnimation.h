#pragma once

#include "Animation.h"
#include "DllDefine.h"


class CE_CONTROL_API AlphaAnimation: public Animation
{
public:
	AlphaAnimation(float fb,float fe,TypeInter tInter = T_LinerInter);
	void renewAction(int nth, UINT len);
	float getAlphaValue(){return m_alphaValue;}
private:
	float m_fromAlpha;
	float m_toAlpha;

	float m_alphaValue;
};

