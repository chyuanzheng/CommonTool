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
	void  MoveToLine(int nline);//��ĳһ���ڼ�������
	void  MoveToLineMid(int nline);//
	int  GetCurPageFistLine(){return m_nLineStart;}//�õ���ǰҳ��һ��
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	virtual void Paint();//**
	int     m_nPageNum;
	bool      m_isBtnDown;
	bool      m_bStartMove;//�Ƿ�ʼ����
	int       m_nStartY;

	int      m_nLineStart;
	int      m_nLineEnd;


	UINT      m_uTimerId;
	string    m_title;
	const wstring    *m_titleFromId;//����
	GxxLBList  *m_preListBox;
	int m_nOverMove;
	int m_nHaveMove;//�Ѿ��ƶ��ľ���

	bool m_bMoveLine;//�Ƿ���Ի����б�
	ControlList::iterator m_startPos;
	
protected:
	//�滭
	virtual void TimerTick(UINT nIDEvent);
	virtual void Draw( ){}
	virtual BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void    onMoveRect(int x_len, int y_len ){}//����Ҫ���±�����
	virtual void onPause();
	

	

	void SetNameTitle(TiXmlElement * ele);
	int GetTopLen() ;


	void MoveLineList( int nmoveY ) ;

    


};
