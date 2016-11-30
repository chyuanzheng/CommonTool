#include "StdAfx.h"
#include "TimerManager.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "Activity.h"
#include "GxxTimer.h"
struct T_TIMER_S
{
	T_TIMER_S()
	{
		timer = NULL;
		_isStart = false;
	}
	GxxTimer *timer;
	bool _isStart;
};

typedef list<T_TIMER_S> L_T_TIMER_S;

class TIMER_SET 
{
public:
	L_T_TIMER_S					_ltTimer;
	Activity *					_viewActivity;
	UINT						_uElapse;
	string                      _name;

	void Start( GxxTimer * timer,UINT uID ) 
	{
		L_T_TIMER_S::iterator pos;
		for (pos = _ltTimer.begin();pos != _ltTimer.end();++pos)
		{
			if ((*pos).timer == timer)
			{
				(*pos)._isStart = true;
				_viewActivity = Activity::GetActiveActiviy();
				::SetTimer(AfxGetHWND(),uID,_uElapse,NULL);
				break;
			}
		}
	}

	void Stop( GxxTimer * timer, UINT uID ) 
	{
		L_T_TIMER_S::iterator pos;
		bool b = false;
		for (pos = _ltTimer.begin();pos != _ltTimer.end();++pos)
		{
			if ((*pos).timer == timer)
			{
				(*pos)._isStart = false;
			}
			b = b|(*pos)._isStart;
		}	
		if (!b)
		{
			::KillTimer(AfxGetHWND(),uID);
		}
	}

	void DoTick( UINT uID ) 
	{
		L_T_TIMER_S::iterator pos;
		for (pos = _ltTimer.begin();pos != _ltTimer.end();++pos)
		{
			if ((*pos)._isStart)
			{
				 (*pos).timer->TimerTick(uID);
			}
		}
	}

};
TimerManager *TimerManager::m_pInstance = NULL;
TimerManager::TimerManager()
{
}

TimerManager::~TimerManager()
{
}

TimerManager* TimerManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new TimerManager;
	}
	return m_pInstance;
}

void TimerManager::StartTimer(GxxTimer *timer, UINT uID )
{
	TIMER_SET *ts = findTimerSet(uID);
	ASSERT(ts);
	ts->Start(timer,uID);
	
}

void TimerManager::StopTimer( GxxTimer *timer,UINT uID )
{
	TIMER_SET *ts = findTimerSet(uID);
	ts->Stop(timer,uID);
	

}

void TimerManager::DoTimerMessage( WPARAM wParam )
{
	UINT uID =  UINT (wParam);

	TIMER_SET *ts = findTimerSet(uID);
	if (NULL!=ts)
	{
		ts->DoTick(uID);
	}
	
}

UINT TimerManager::OpenTimer( GxxTimer *timer,const char * name )
{
	TM_ID_SET::iterator pos;
	for (pos = m_tmIdSet.begin();pos != m_tmIdSet.end(); ++pos)
	{
		if ((*pos).second->_name == name)
		{
			T_TIMER_S  ttr;
			ttr._isStart = false;
			ttr.timer = timer;
			(*pos).second->_ltTimer.push_back(ttr);
			return (*pos).first;
		}
		
	}
	//ASSERT(0);
	return 0;
}


UINT TimerManager::RegisterTimer( GxxTimer *timer,UINT uElapse,const char* name /*= NULL*/ )
{
	UINT uID =0;
	if (name !=NULL)
	{
		uID =OpenTimer(timer,name);
		if (uID !=0)//ºöÂÔ uElapse
		{
			return uID;
		}
	}

	uID = findAFreeID();

	TIMER_SET *ts = new TIMER_SET;
	T_TIMER_S  ttr;
	ttr._isStart = false;
	ttr.timer = timer;
	ts->_ltTimer.push_back(ttr);
	ts->_uElapse = uElapse;
	if (name!=NULL)
	{
		ts->_name = name;
	}
	m_tmIdSet[uID] = ts;

	return uID;
}

void TimerManager::UnRegisterTimer(GxxTimer *timer, UINT uID )
{
	
	TIMER_SET *ts = findTimerSet(uID);

	L_T_TIMER_S::iterator pos;
	for (pos = ts->_ltTimer.begin();pos != ts->_ltTimer.end();++pos)
	{
		if ((*pos).timer == timer)
		{
			ts->_ltTimer.erase(pos);
			break;
		}
	}

	if (ts->_ltTimer.size()==0)
	{
		::KillTimer(AfxGetHWND(),uID);
		delete ts;
		m_tmIdSet.erase(uID);
	}
	
}

UINT TimerManager::findAFreeID()
{
	TM_ID_SET::iterator pos;
	UINT uID = 126;
	while(1)
	{
		pos = m_tmIdSet.find(uID);
		if (pos == m_tmIdSet.end())
		{
			break;
		}
		uID++;
	}
	return uID;
}

TIMER_SET * TimerManager::findTimerSet( UINT uID )
{
	TM_ID_SET::iterator pos = m_tmIdSet.find(uID);
	if (pos == m_tmIdSet.end())
	{
		//ASSERT(0);
		return NULL;
	}
	return (*pos).second;
}



