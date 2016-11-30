#pragma once

#include "Animation.h"
#include "DllDefine.h"


class CE_CONTROL_API RotateYAnimation: public Animation
{
public:
	RotateYAnimation(float fb,float fe,TypeInter tInter = T_LinerInter);
	void renewAction(int nth, UINT len);
	float getRotateY(){return m_rotateValue;}
private:
	float m_fromRotate;
	float m_toRotate;

	float m_rotateValue;
};

