#pragma once

#include "GxxView.h"
#include "AnimationManage.h"

class GxxAniButton;
class GxxAniLable;

#define		MES_CHOOSE_BTN_DISABLE               15   //向父控件发送设置失败
class CE_CONTROL_API GxxSetupChooseBtn : public GxxView
{
public:
	GxxSetupChooseBtn(int x,int y, const string &strName);
	virtual ~GxxSetupChooseBtn();




private:
	//virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	void ReadSetData(const char * pStr);

	void CheckEnable();

	void WriteSetData();
	void DisableAll();
	void DisableWaiting();

	string       m_strName;
	int          m_minCursor;
	int          m_maxCursor;
	int          m_curCursor;
	GxxAniButton *m_btnleft;
	GxxAniButton *m_btnright;
	GxxAniLable  *m_midlable;



};


