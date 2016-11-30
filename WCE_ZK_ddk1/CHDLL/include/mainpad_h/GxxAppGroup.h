#pragma once

#include "GxxView.h"
#include "GxxAppButton.h"
#include "GxxAppPage.h"
class GxxRationPage;
struct T_MarginI;

typedef list<GxxAppPage *> T_PageGroup;
typedef list<int> T_S_INT;
typedef list<T_S_INT> T_S_S_INT;

class CE_CONTROL_API GxxAppGroup : public GxxView
{
public:
	static GxxView* CreateControl();
	GxxAppGroup();
	virtual ~GxxAppGroup();
	virtual void setCtrLayout( TiXmlElement * ele);
	void    resetToFactory();
	

	//计算rect组
	
	void startRightAnimation(bool isRight);

	bool SetEidtMode( bool e);
	bool MoveAddBtn( GxxAppButton* at );


	bool MoveExchangeBtn( GxxAppButton * downBtn, GxxAppButton * toBtn );


private:
	T_PageGroup   m_allPage;
	T_S_S_INT m_appNthList;

	GxxAppPage   *m_fromCurPage;
	GxxAppPage   *m_toCurPage;
	string       m_appLocal;
	

	T_PageGroup::iterator m_pagepos;

	
	int        m_nCurPage;//第几页

	AnimationAction * m_ActionCurToRight;
	AnimationAction * m_ActionLeftToCur;

	TranslateAnimation *m_AniLeftToCur;//
	TranslateAnimation *m_AniCurToRight;//

	HANDLE m_hAni;
	TCHAR     m_isGxxButtonDown;
	int       m_xMove;
	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	
    GxxRationPage *m_posRation;
	void SetPosRation();



	void SetAniLayout( TiXmlElement * ele ) ;
	bool ReadAppBtnLayout( TiXmlElement * ele );
	void WriteAppBtnLayout();
	void SetAppBtnByLayout(TiXmlElement * ele );
	


	bool checkPrePage(GxxView* v);
	bool checkPostPage(GxxView* v);
	void checkClearPage();

	void ComputeRect(const RECT &groupRect,const T_MarginI &tm, RECT *pageRect);
	void ReLoadCtrls() ;

	
};
