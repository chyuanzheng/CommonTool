#pragma once


#include "DllDefine.h"
#include "Interpolation.h"

class CE_CONTROL_API Animation
{
public:
	typedef	enum
	{
		T_LinerInter,		
		T_SquareInInter,		
		T_SquareOutInter,	
		T_SquareInoutInter,		
		T_CubicInInter,		
		T_CubicOutInter,	
		T_CubicInOutInter,		
		T_SineInInter,		
		T_SineOutInter,	
		T_SineInOutInter,		
		T_ElasticInter,		
		T_BackInInter,	
		T_BackOutInter,		
		T_BackInOutInter,		
		T_BounceInInter,	
		T_BounceOutInter,		
		T_BounceInOutInter
	}TypeInter;

	friend class AnimationAction;
	typedef enum {ALPHA, SCALE, TRANSLATE, ROTATE_Y} ANI_TYPE; 
	typedef enum {NO_NEED, RELATIVE_TO_SELF, RELATIVE_TO_ORIGIN} PIVOT_TYPE;
	Animation(ANI_TYPE at,TypeInter tInter);
	virtual ~Animation();
	ANI_TYPE getType(){return anitype;}
	void setName(const char*name)
	{
		ASSERT(NULL!=name);
		m_strname = name;
	}
	const char * getName(){return m_strname.c_str();}





protected:
	virtual void renewAction(int nth, UINT len)=0;
	
	//void resetCount(){m_count=0;}
	Interpolation   *m_interp_type;
private:
	string m_strname;
	const ANI_TYPE  anitype;
};
