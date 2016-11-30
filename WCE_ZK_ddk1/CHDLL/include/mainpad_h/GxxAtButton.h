#pragma once
#include "GxxView.h"
class GxxAniPictureA;
class GxxPicture;
class GxxSwText;
class GxxAppGroup;
class GxxToolGroup;
struct T_AppModule;
class EDIT_VALUE; 

class CE_CONTROL_API GxxAtButton : public GxxView
{
public:
	typedef enum {TOOL_BTN,APP_BTN }TYPE_BTN;
	

	int getNth();
	GxxAtButton(int nth);
	virtual ~GxxAtButton();

	static bool    getEditMode();
	static void    setEditMode(bool b);	
	static void    setBorder( int left, int right );
	static void    SetAppGroup( GxxAppGroup*  g );
	static void    SetToolGroup( GxxToolGroup* g );

	T_AppModule *  getBtnModule( ){ return m_appModule;}
	HANDLE getAppActHandle();

	GxxPicture * GetAniPic( );

protected:

	virtual void Draw( );
	//响应自身事件
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

	virtual TYPE_BTN getBtnType() = 0;
	void       RectChanged();
	virtual    int  GetPageMoveX() { return 0;}


	BOOL getBtnIsDown();


	bool  setBtnModule( T_AppModule * m );
private:
	void moveBtnEnd();
	void InvalidateMoveRect(int x=0,int y=0);
	bool  setBtnModule( int nth );
	void StartAniBtn();
	void StopAniBtn();
	

	RECT  m_playRect;

	T_AppModule *m_appModule;
	
	GxxPicture *m_pPicUpEnable;
	GxxPicture *m_pPicUpDisable;

	GxxPicture *m_pS_PicUpEnable;
	GxxPicture *m_pS_PicUpDisable;

	GxxSwText  *m_titleText;

	static GxxPicture *m_pPicPlaying;

	static GxxAniPictureA *s_pAniPicBack;
	static EDIT_VALUE      *s_editValue;

	
	bool  m_bStartAniBack;

};
