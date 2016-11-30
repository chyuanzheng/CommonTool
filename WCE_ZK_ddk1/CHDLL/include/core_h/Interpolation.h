#pragma once

#pragma warning(disable:4244) //
#define PI 3.1415926

#include "MesDef.h"

enum
{
	EASEIN,			// 前慢后快
	EASEOUT,		// 前快后慢
	EASEINOUT		// 慢快慢
};

class Interpolation
{

public:
	/* tween算法。
	t: 动画已经执行的时间（执行多少次/帧数）
	b: 起始位置
	c: 终止位置
	d: 从起始位置到终止位置的经过时间（总共执行多少次/帧数）
	*/
	virtual float fun_tween(float t, float b, float c, float d)
	{
		return 0;
	}
};

class LinerInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		return (c)*t/d+b;
	}
};


class SquareInInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		return c*(t/=d)*t + b; 
	}
};


class SquareOutInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		return -c * (t-2)*(t/=d) + b; 
	}
};


class SquareInoutInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		if ((t/=d/2) < 1) 
		{
			return c*t*t/2 + b;
		}
		return -c * ((--t)*(t-2) - 1)/2 + b;
	}
};

class CubicInInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		return c*(t/=d)*t*t + b;
	}
};

class CubicOutInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		return c*((t=t/d-1)*t*t + 1) + b;
	}
};

class CubicInOutInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		if ((t/=d/2) < 1) return c/2*t*t*t + b;
		return c/2*((t-=2)*t*t + 2) + b;
	}
};

class SineInInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		return -c * cos(t/d * (PI/2)) + c + b;
	}
};

class SineOutInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		 return c * sin(t/d * (PI/2)) + b;
	}
};

class SineInOutInter : public Interpolation
{
public:
	float fun_tween(float t, float b, float c, float d)
	{
		return -c/2 * (cos(PI*t/d) - 1) + b;
	}
};

// 指数衰减的正弦曲线缓动,弹簧效果
class ElasticInter : public Interpolation
{
	float a;
	float p;
	int type;
public:
	ElasticInter(int t=EASEOUT)
	{
		a = 0;
		p = 0;
		type = t;
	}
	ElasticInter(float a0, float p0, int t=EASEOUT)
	{
		a = a0;
		p = p0;
		type = t;
	}
	float fun_tween(float t, float b, float c, float d)
	{
		if (type == EASEIN)
		{
			if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
			float s = 0;
			if (!a || a < abs(c)) { a=c;  s=p/4; }
			else  s = p/(2*PI) * asin (c/a);
			return -(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )) + b;
		}
		if (type == EASEOUT)
		{
			float s = 0;
			if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
			if (!a || a < abs(c)) { a=c;  s=p/4; }
			else  s = p/(2*PI) * asin (c/a);
			return (a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);
		}
		if (type == EASEINOUT)
		{
			float s = 0;
			if (t==0) return b;  if ((t/=d/2)==2) return b+c;  if (!p) p=d*(.3*1.5);
			if (!a || a < abs(c)) { a=c;  s=p/4; }
			else  s = p/(2*PI) * asin (c/a);
			if (t < 1) return -.5*(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )) + b;
			return a*pow(2,-10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )*.5 + c + b;
		}
		return 0;
	}
};

// 超过范围的三次方缓动（(s+1)*t^3 - s*t^2）, 回弹效果
class BackInInter : public Interpolation
{
	float s;
public:
	BackInInter()
	{
		s = 1.70158;
	}
	BackInInter(float f)
	{
		s = f;
	}
	float fun_tween(float t, float b, float c, float d)
	{
		return c*(t/=d)*t*((s+1)*t - s) + b;
	}
};

class BackOutInter : public Interpolation
{
	float s;
public:
	BackOutInter()
	{
		s = 1.70158;
	}
	BackOutInter(float f)
	{
		s = f;
	}
	float fun_tween(float t, float b, float c, float d)
	{
		return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
	}
};

class BackInOutInter : public Interpolation
{
	float s;
public:
	BackInOutInter()
	{
		s = 1.70158;
	}
	BackInOutInter(float f)
	{
		s = f;
	}
	float fun_tween(float t, float b, float c, float d)
	{
		if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525))+1)*t - s)) + b;
		return c/2*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2) + b;
	}
};
// 指数衰减的反弹缓动, 小球弹地效果
class BounceInInter : public Interpolation
{
	float fun_tween_out(float t, float b, float c, float d)
	{
		if ((t/=d) < (1/2.75)) {
			return c*(7.5625*t*t) + b;
		} else if (t < (2/2.75)) {
			return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
		} else if (t < (2.5/2.75)) {
			return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
		} else {
			return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
		}
	}
public:
	float fun_tween(float t, float b, float c, float d)
	{
		 return c - fun_tween_out(d-t, 0, c, d) + b;
	}
};

class BounceOutInter : public Interpolation
{
	
public:
	float fun_tween(float t, float b, float c, float d)
	{
		if ((t/=d) < (1/2.75)) {
			return c*(7.5625*t*t) + b;
		} else if (t < (2/2.75)) {
			return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
		} else if (t < (2.5/2.75)) {
			return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
		} else {
			return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
		}
	}
};

class BounceInOutInter : public Interpolation
{
	float fun_tween_out(float t, float b, float c, float d)
	{
		if ((t/=d) < (1/2.75)) {
			return c*(7.5625*t*t) + b;
		} else if (t < (2/2.75)) {
			return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
		} else if (t < (2.5/2.75)) {
			return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
		} else {
			return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
		}
	}
	float fun_tween_in(float t, float b, float c, float d)
	{
		return c - fun_tween_out(d-t, 0, c, d) + b;
	}
public:
	float fun_tween(float t, float b, float c, float d)
	{
		if (t < d/2) return fun_tween_in(t*2, 0, c, d) * .5 + b;
		else return fun_tween_out(t*2-d, 0, c, d) * .5 + c*.5 + b;
	}
};
