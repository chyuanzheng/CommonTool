#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAppButton.h"
class CE_CONTROL_API GxxAppPage : public GxxView
{

protected:
	int m_move;
	//�滭
	virtual void Draw( );
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	static RECT       m_lineLeftRect;
	static RECT       m_lineRightRect;


public:
	GxxAppPage();
	virtual ~GxxAppPage();
	void SetXmove( int xmove ){m_move =xmove;}
	int  GetXmove(){return m_move;}
	void resetRect();
	bool checkAddBtn( GxxAppButton* at );

	void InsertBtn( GxxAppButton* at ) ;
	void InsertBtn( GxxAppButton* to, GxxAppButton* down);
	void sortBtn();
	void exchangeBtn( GxxAppButton * downBtn, GxxAppButton * toBtn );
	//void AddHandlesToAction( AnimationAction * action );
	static void SetLineRect( int nleft, int ntop, int nwidth, int nheight, int r_width );
	void WritePageNth( TiXmlDocument &tDoc );
	static void ExchangeBtn( GxxAppButton * downBtn, GxxAppButton * toBtn, GxxAppPage * downPage, GxxAppPage * toPage );
	static HANDLE     m_handleLine;

};
