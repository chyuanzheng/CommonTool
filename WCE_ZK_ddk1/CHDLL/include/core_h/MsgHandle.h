#pragma once
#include "DllDefine.h"
//#include "SkiaBitmapManager.h"


class GxxView;
class MsgHandle;
typedef DWORD (*MsgHandler)(void *pControl, DWORD dwParam, UINT &msg, WPARAM wParam, LPARAM lParam);	// 使用 UINT &msg,当自定义消息处理函数不希望该消息被标准消息处理函数处理时,可以设置msg=0


typedef list<MsgHandle> T_MSG_HANDLES;
typedef map<int, T_MSG_HANDLES>  TMAP_MSG_HANDLES;

class CE_CONTROL_API MsgHandle
{
	
public:
	friend class CCommonWnd;
	void *pThis;
	DWORD dwParam;
	MsgHandler	funMsg;

	bool operator==(const MsgHandle &m)
	{
		if (this->pThis == m.pThis && this->dwParam == m.dwParam && this->funMsg == m.funMsg)
		{
			return true;
		}
		return false;
	}
	friend CE_CONTROL_API void SetMsgHook(DWORD msg, MsgHandle msgHandle);
	friend CE_CONTROL_API void SetMsgHandler(DWORD msg, MsgHandler handler, DWORD dwParam, void *p_this = NULL);


private:
	static  TMAP_MSG_HANDLES mapMsgHandle;
};




