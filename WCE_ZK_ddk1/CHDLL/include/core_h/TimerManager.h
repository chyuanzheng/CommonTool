#pragma once

#include "GxxView.h"

class TIMER_SET;
class GxxTimer;
typedef  map<UINT ,TIMER_SET *> TM_ID_SET;
class CE_CONTROL_API TimerManager
{
	friend class CWnd;
	friend class CPopupWnd;
	friend class GxxTimer;
private:
	/************************************************************************/
	/*       定时器三种状态alive_always表示Timer会一直发送消息，
	alive_when_active 只有当View处于active会发送消息，
	alive_only_active 当View不处于active时会关闭Timer*/
	/************************************************************************/
	//typedef enum {alive_always,alive_when_active,alive_only_active} TimerType;
	static TimerManager* GetInstance();

	/*isRecFromBack true当处于背景activity时仍然接收消息，否则当控件所在activity不是当前activity时，Timer会自动关闭*/
	UINT RegisterTimer(GxxTimer *timer,UINT uElapse,const char* name = NULL);
	void UnRegisterTimer(GxxTimer *timer,UINT uID);
	UINT OpenTimer(GxxTimer *timer,const char * name);
	void StartTimer(GxxTimer *timer,UINT uID);
	void StopTimer(GxxTimer *timer,UINT uID);
	

	~TimerManager();



private:
	TimerManager();
	TM_ID_SET m_tmIdSet;
	void DoTimerMessage(WPARAM wParam);
	UINT findAFreeID();
	TIMER_SET * findTimerSet( UINT uID ) ;

	static TimerManager* m_pInstance;


};
