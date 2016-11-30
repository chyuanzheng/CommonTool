#pragma once
#include "Activity.h"
#include "SetupDllModule.h"
#include "GXNotify.h"
#include "GxxTimer.h"

class GxxBtnMatchListGroup;

class GxxAniLable;
class GxxSwText;
class GxxSetupListLine;

struct LINE_TEXT 
{
	GxxSwText *txt_show;//当前选中的行的文本
	GxxSetupListLine * txt_line;//消息号
};

typedef map<int,int> M_CODE_MSG;//第一个int是编码，第二个int 是msg 。 实际发消息时会将编码转化成消息号。
typedef map<int,LINE_TEXT> M_MSG_LINE_TXT;//第一个int是编码，第二个int 是msg 。 实际发消息时会将编码转化成消息号。

class CE_SETUPACTIVITY_API  BtnMatchActivity : public Activity
{
public:
	enum{chinese,english};
	BtnMatchActivity();
	virtual ~BtnMatchActivity ();
	virtual  void onCreate();
	virtual void onResume();
	virtual void onPause();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	static Activity* CreateControl();
	static DWORD MCUEventHandler(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam);

private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, BtnMatchActivity);
	void LoadMsgFromRom();
	void SetMatchInfo( GxxSetupListLine * line );
	void RenewText();
	void SaveMatch();
	void InsertMsgLine( const string & lineName, int nMsg );
	void SaveMsg( BYTE &ebyte, int nMsg );
	void OnWheelMsg();
	void OnIrMsg();

	void EraseLikeCode( int code );
	void InsertCodeMsg( int code, int msg );
	void ResetConfig( BYTE & byte );
	
	GxxView  *m_btx;
	GxxBtnMatchListGroup *m_matchGroup;

	
	int  m_nCurMsg;//当前需要翻译的消息号
	int  m_nLine;//当前的行号
	int  m_nCurCode;//当前的当前接收到的编码
	
	M_CODE_MSG m_codeMsg;//所有翻译好的消息
	M_CODE_MSG m_curCodeMsg;//所有正在翻译的消息
	M_MSG_LINE_TXT  m_MsgLine;//


	bool m_IsInMatch;//是否处于翻译学习状态。
	GxxAniLable *m_okLable;

};


