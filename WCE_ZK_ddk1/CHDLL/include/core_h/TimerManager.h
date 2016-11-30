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
	/*       ��ʱ������״̬alive_always��ʾTimer��һֱ������Ϣ��
	alive_when_active ֻ�е�View����active�ᷢ����Ϣ��
	alive_only_active ��View������activeʱ��ر�Timer*/
	/************************************************************************/
	//typedef enum {alive_always,alive_when_active,alive_only_active} TimerType;
	static TimerManager* GetInstance();

	/*isRecFromBack true�����ڱ���activityʱ��Ȼ������Ϣ�����򵱿ؼ�����activity���ǵ�ǰactivityʱ��Timer���Զ��ر�*/
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
