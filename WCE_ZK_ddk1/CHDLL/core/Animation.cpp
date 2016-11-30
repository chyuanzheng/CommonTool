#include "StdAfx.h"
#include "Animation.h"

//typedef	enum
//{
//	T_LinerInter,		
//	T_SquareInInter,		
//	T_SquareOutInter,	
//	T_SquareInoutInter,		
//	T_CubicInInter,		
//	,	
//	,		
//	,		
//	,	
//	,		
//	,		
//	,	
//	,		
//	,		
//	,	
//	,		
//	
//}TypeInter;
Animation::Animation(ANI_TYPE at,TypeInter tInter):anitype(at)
{
	switch( tInter )
	{
	case T_LinerInter:
		m_interp_type = new LinerInter;
		break;
	case T_SquareInInter:
		m_interp_type = new SquareInInter;
		break;
	case T_SquareOutInter:
		m_interp_type = new SquareOutInter;
		break;
	case T_SquareInoutInter:
		m_interp_type = new SquareInoutInter;
		break;
	case T_CubicInInter:
		m_interp_type = new CubicInInter;
		break;
	case T_CubicOutInter:
		m_interp_type = new CubicOutInter;
		break;
	case T_CubicInOutInter:
		m_interp_type = new CubicInOutInter;
		break;
	case T_SineInInter:
		m_interp_type = new SineInInter;
		break;
	case T_SineOutInter:
		m_interp_type = new SineOutInter;
		break;
	case T_SineInOutInter:
		m_interp_type = new SineInOutInter;
		break;
	case T_ElasticInter:
		m_interp_type = new ElasticInter;
		break;
	case T_BackInInter:
		m_interp_type = new BackInInter;
		break;
	case T_BackOutInter:
		m_interp_type = new BackOutInter;
		break;
	case T_BackInOutInter:
		m_interp_type = new BackInOutInter;
		break;
	case T_BounceInInter:
		m_interp_type = new BounceInInter;
		break;
	case T_BounceOutInter:
		m_interp_type = new BounceOutInter;
		break;
	case T_BounceInOutInter:
		m_interp_type = new BounceInOutInter;
		break;
	default:
		m_interp_type = new LinerInter;
	}


}

Animation::~Animation()
{
	if (NULL!=m_interp_type)
	{
		delete m_interp_type;
	}
}



