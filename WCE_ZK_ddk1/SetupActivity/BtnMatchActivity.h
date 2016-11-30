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
	GxxSwText *txt_show;//��ǰѡ�е��е��ı�
	GxxSetupListLine * txt_line;//��Ϣ��
};

typedef map<int,int> M_CODE_MSG;//��һ��int�Ǳ��룬�ڶ���int ��msg �� ʵ�ʷ���Ϣʱ�Ὣ����ת������Ϣ�š�
typedef map<int,LINE_TEXT> M_MSG_LINE_TXT;//��һ��int�Ǳ��룬�ڶ���int ��msg �� ʵ�ʷ���Ϣʱ�Ὣ����ת������Ϣ�š�

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

	
	int  m_nCurMsg;//��ǰ��Ҫ�������Ϣ��
	int  m_nLine;//��ǰ���к�
	int  m_nCurCode;//��ǰ�ĵ�ǰ���յ��ı���
	
	M_CODE_MSG m_codeMsg;//���з���õ���Ϣ
	M_CODE_MSG m_curCodeMsg;//�������ڷ������Ϣ
	M_MSG_LINE_TXT  m_MsgLine;//


	bool m_IsInMatch;//�Ƿ��ڷ���ѧϰ״̬��
	GxxAniLable *m_okLable;

};


