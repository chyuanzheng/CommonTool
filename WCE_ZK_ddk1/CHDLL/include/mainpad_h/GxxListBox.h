#pragma once

#include "AnimationManage.h"
#include "GxxView.h"

#include "GxxTimer.h"
class CE_CONTROL_API GxxListBox : public GxxView,protected GxxTimer
{
protected:
	int m_nlineHeight;
	int     m_nPageNum;
	bool      m_isBtnDown;
	bool      m_bStartMove;//是否开始滑动
	int       m_nStartY;

	int      m_nLineStart;
	int      m_nLineEnd;


	UINT      m_uTimerId;
	string    m_title;
	GxxListBox  *m_preListBox;
	//GxxListLine *m_btnListLine;
	int m_nOverMove;

	virtual void    onMoveRect(int x_len, int y_len ){}//不需要更新本区域
protected:
	//绘画
	virtual void TimerTick(UINT nIDEvent);
	virtual void Draw( ){}
	virtual BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );
	
	int CaculateRation();

	int GetTopLen() ;


	void checkMoveBack();
	void MoveLineList( int nmoveY ) ;

    

public:
	GxxListBox();
	virtual ~GxxListBox();
	virtual void setCtrLayout( TiXmlElement * ele);
	void MovePage(bool bNext);
	void setPreListBox( GxxListBox * pre );
	void getFRation(float & fs, float &fe);

};
