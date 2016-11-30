#pragma once
	/************************************************************************/
	/*       定时器三种状态alive_always表示Timer会一直发送消息，
	alive_when_active 只有当View处于active会发送消息，
	alive_only_active 当View不处于active时会关闭Timer*/
	/************************************************************************/
class CE_CONTROL_API GxxTimer 
{
protected:
	UINT RegisterTimer(UINT uElapse, const char* name = NULL);
	void UnRegisterTimer(UINT uID);

	UINT OpenTimer(const char * name);
	void StartTimer(UINT uID);
	void StopTimer(UINT uID);
	GxxTimer( ){};
	virtual ~GxxTimer( ){};
	//控件根据 ele中的参数设置自己的属性
public:
	virtual void TimerTick(UINT nIDEvent){}

};

