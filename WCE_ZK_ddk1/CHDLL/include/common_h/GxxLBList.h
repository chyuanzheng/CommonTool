#pragma once

#include "AnimationManage.h"
#include "GxxView.h"
#include "GxxTimer.h"
class CE_CONTROL_API GxxLBList : public GxxView,protected GxxTimer
{
public:
	GxxLBList();
	virtual ~GxxLBList();
	void MovePage(bool bNext);
	void setPreListBox( GxxLBList * pre );
	void ResetPosition();
	GxxLBList *getPreListBox(){ return m_preListBox;}
	void getFRation(float & fs, float &fe);
	void FreshListBox();
	int  getHaveMove(){ return m_nHaveMove;}

	

	const string &getTitle(){return m_title;}
	const wstring *getTitleFromID(){return m_titleFromId;}

	void CaculateRation(bool b_needAni= true, bool b_needMove=true);
	void  MoveToLine(int nline);//让某一行在见的区域
	void  MoveToLineMid(int nline);//
	int  GetCurPageFistLine(){return m_nLineStart;}//得到当前页的一行
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	virtual void Paint();//**
	int     m_nPageNum;
	bool      m_isBtnDown;
	bool      m_bStartMove;//是否开始滑动
	int       m_nStartY;

	int      m_nLineStart;
	int      m_nLineEnd;


	UINT      m_uTimerId;
	string    m_title;
	const wstring    *m_titleFromId;//语言
	GxxLBList  *m_preListBox;
	int m_nOverMove;
	int m_nHaveMove;//已经移动的距离

	bool m_bMoveLine;//是否可以滑动列表
	ControlList::iterator m_startPos;
	
protected:
	//绘画
	virtual void TimerTick(UINT nIDEvent);
	virtual void Draw( ){}
	virtual BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void    onMoveRect(int x_len, int y_len ){}//不需要更新本区域
	virtual void onPause();
	

	

	void SetNameTitle(TiXmlElement * ele);
	int GetTopLen() ;


	void MoveLineList( int nmoveY ) ;

    


};
