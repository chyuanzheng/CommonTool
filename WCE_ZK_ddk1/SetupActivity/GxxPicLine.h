#pragma once
#include "SetupDllModule.h"
#include "GxxView.h"
#include "AnimationManage.h"
class CE_SETUPACTIVITY_API GxxPicLine : public GxxView
{
public:
	GxxPicLine();
	virtual ~GxxPicLine();
	static	GxxView* CreateControl();

	void SetPoint(int xline,int yline);
	void SetFront();
	void SetRear();
	void SetLeft();
	void SetRight();


	void InvalidateLine() ;

	void GetPoint(int &xline,int &yline);
	int getMaxLine(){return m_nMaxLine;}
protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	//�滭
	virtual void Draw( );
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	bool	setShowRect( TiXmlElement * ele );
	void    CaculatePoint( int x,int y );
	


	GxxPicture *m_pPicBack;
	GxxPicture *m_pPicPoint;


    RECT        m_ActShowRect;//��ʾ��RECT
	int         m_nLineInterval;

	int         m_x;//����
	int         m_y;//����

	int         m_xline;
	int         m_yline;
	int			m_nMaxLine;

	bool        m_btnDown;

};
