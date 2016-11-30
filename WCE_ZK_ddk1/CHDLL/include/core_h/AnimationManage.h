#pragma once


#include "DllDefine.h"
#include "AnimationAction.h"
#include "GxxTimer.h"
typedef list<AnimationAction *> TL_ACTION; 
struct T_ANI_SET;
typedef  list<T_ANI_SET *> TLIST_ANI_SET;
class CE_CONTROL_API AnimationManage: protected  GxxTimer
{
public:
	static AnimationManage* GetInstance();
	~AnimationManage();
	HANDLE InitAniSet();
	HANDLE InitAniSet(const char* path);
	AnimationAction *GetAction(HANDLE h,const char* name=NULL);

	

	void DeInitAniSet(HANDLE h);
	

	void AddAction(HANDLE h,AnimationAction * action);
	void RemoveAction(HANDLE h,AnimationAction * action);
	//这里进行实质的matrix alpha 变化
	void ProssAcion();
	virtual void TimerTick(UINT nIDEvent);
	BOOL ProssAcion(T_ANI_SET* tas);
	void StartAction(HANDLE h,bool breset = true);
	void StopAction(HANDLE h);
	BOOL IsInAction(HANDLE h);
	

	//breset 从头开始，或者尾部开始
	void setDirect(HANDLE h,BOOL fromRvt);
	BOOL getDirect(HANDLE h);


private:
	AnimationManage();
	void setAction( TiXmlElement * ele_act, T_ANI_SET * tas );
	void setAnimation( TiXmlElement * ele_Ani, AnimationAction * ani_action );
	void setTimeSection( HANDLE h,int start, int end );
	TLIST_ANI_SET  m_allSet;
	
	static AnimationManage *m_pInstance;
	TL_ACTION m_tlaction;
	BOOL    m_bIsStart;
	UINT    m_uTimerID;
	//int m_start;
	//int m_end;
	//int m_count;
	//BOOL m_isInAction;
	//BOOL m_fromRvt;//是否反方向动画
};

