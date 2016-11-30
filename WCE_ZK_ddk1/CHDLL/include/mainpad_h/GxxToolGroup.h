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
	//��ťͼƬ
	//�ж��Ƿ񱻰���
	//TCHAR     m_isGxxButtonDown;


	void setChildShowBtn(BOOL e);
	//�滭
	virtual void Draw( );
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	bool ModuleInGroup(T_AppModule *m_);
	void SetUpAni() ;
	//void SetDownAni() ;

	BOOL InMyArea( int x, int y );




	AnimationAction * m_traAction;
	AnimationAction * m_scaleAction;

    

	bool  m_isBtnDown;
	BOOL  m_bLock;//�Ƿ�����������ʹ֮����
	BOOL  m_bDownToUp;
	HANDLE m_hAni;
	int   m_nth[SIZE_TOOL_APP];
private:
	string       m_toolLocal;


};
