#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxToolButton.h"
#define  SIZE_TOOL_APP  4
struct T_AppModule;
class CE_CONTROL_API GxxToolGroup : public GxxView
{
public:
	GxxToolGroup();

	void LoadAppTools();

	virtual ~GxxToolGroup();
	void startAnimation(BOOL up);

	void setChildDraw(BOOL e);
	void setLock(BOOL lk){m_bLock = lk;}
	
	BOOL AniationScaleMsg( UINT lp );
	BOOL AniationTraMsg( UINT lp );
	void MoveSetModule( GxxToolButton * btn, T_AppModule * module );
	void MoveExchangeModule( GxxToolButton * a, GxxToolButton * b );
	void WriteToolBtnLayout();
	void resetToFactory();

protected:
	HANDLE     m_handleback;
	//按钮图片
	//判断是否被按下
	//TCHAR     m_isGxxButtonDown;


	void setChildShowBtn(BOOL e);
	//绘画
	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	bool ModuleInGroup(T_AppModule *m_);
	void SetUpAni() ;
	//void SetDownAni() ;

	BOOL InMyArea( int x, int y );




	AnimationAction * m_traAction;
	AnimationAction * m_scaleAction;

    

	bool  m_isBtnDown;
	BOOL  m_bLock;//是否锁定，不能使之动画
	BOOL  m_bDownToUp;
	HANDLE m_hAni;
	int   m_nth[SIZE_TOOL_APP];
private:
	string       m_toolLocal;


};
