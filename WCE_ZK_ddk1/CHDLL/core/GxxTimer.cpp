#include "StdAfx.h"
#include "GxxTimer.h"
#include "TimerManager.h"


UINT GxxTimer::RegisterTimer( UINT uElapse, const char* name /*= NULL*/ )
{
	return TimerManager::GetInstance()->RegisterTimer(this,uElapse,name);
}

void GxxTimer::UnRegisterTimer( UINT uID )
{
	TimerManager::GetInstance()->UnRegisterTimer(this,uID);
}

void GxxTimer::StartTimer( UINT uID )
{
	TimerManager::GetInstance()->StartTimer(this,uID);
}

void GxxTimer::StopTimer( UINT uID )
{
	TimerManager::GetInstance()->StopTimer(this,uID);
}

UINT GxxTimer::OpenTimer( const char * name )
{
	return TimerManager::GetInstance()->OpenTimer(this,name);
}
