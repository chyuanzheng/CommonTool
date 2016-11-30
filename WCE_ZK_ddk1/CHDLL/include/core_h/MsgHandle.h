#pragma once
#include "DllDefine.h"
//#include "SkiaBitmapManager.h"


class GxxView;
class MsgHandle;
typedef DWORD (*MsgHandler)(void *pControl, DWORD dwParam, UINT &msg, WPARAM wParam, LPARAM lParam);	// ʹ�� UINT &msg,���Զ�����Ϣ��������ϣ������Ϣ����׼��Ϣ����������ʱ,��������msg=0


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




