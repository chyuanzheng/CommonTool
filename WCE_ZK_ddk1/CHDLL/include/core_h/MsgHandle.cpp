#include "stdAfx.h"
#include "MsgHandle.h"
//#include "SkiaBitmapManager.h"


TMAP_MSG_HANDLES  MsgHandle::mapMsgHandle;

void  SetMsgHandler(DWORD msg, MsgHandler handler, DWORD dwParam, void *p_this /*= NULL*/)
{
	MsgHandle msgHandle;
	msgHandle.dwParam = dwParam;
	msgHandle.pThis = p_this;
	msgHandle.funMsg = handler;
	SetMsgHook(msg, msgHandle);
}


void SetMsgHook(DWORD msg, MsgHandle msgHandle)
{
	TMAP_MSG_HANDLES::iterator map_pos;
	map_pos =MsgHandle:: mapMsgHandle.find(msg);
	if (map_pos == MsgHandle::mapMsgHandle.end())
	{
		T_MSG_HANDLES lstHandle;
		lstHandle.push_back(msgHandle);
		MsgHandle::mapMsgHandle.insert(pair<int, T_MSG_HANDLES>(msg, lstHandle));
	}
	else
	{
		map_pos->second.remove(msgHandle);
		map_pos->second.push_back(msgHandle);
	}
}
