#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxListGroupBase.h"

class GxxSetupLBList;
typedef  map<string ,GxxSetupLBList*> TMap_ListBox;
class CE_CONTROL_API GxxSetupListGroup : public GxxListGroupBase
{
protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	//�ؼ�����Ϣ�������
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	void setListBoxList( TiXmlElement * ele ) ;
	virtual void onPause(){S_curList = NULL;}
	//virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	//virtual bool TranslateMessage( GxxView* mesView, UINT nMsg, WPARAM wParam, LPARAM lParam );

	static TMap_ListBox s_allListBox;
	DWORD m_downTime;
	static GxxLBList* S_curList;//��ǰlist


public:
	GxxSetupListGroup();
	virtual ~GxxSetupListGroup();
	static GxxLBList* GetCurList(){return S_curList;}

	//bReturn = 0��ʾ��һ�ν���setup
	//bReturn = 1��ʾ��һ���Ժ���벻ͬ��setup
	//bReturn = 2��ʾsetup����
	void setActiveListBox(const string & listname,int isReStart);
	static GxxView* CreateControl();
	BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );
	void LineBtnDown( WPARAM wParam, LPARAM lParam );
	void finish();
	static GxxView * S_FindList( const string & str );
};
