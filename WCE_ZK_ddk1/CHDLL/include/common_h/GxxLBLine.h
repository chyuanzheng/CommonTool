#pragma once

#include "GxxView.h"


class GxxDelimiter;
class GxxAniPictureA;

#define		TR_IS_IN_MOVE               16  //列表框消息

class CE_CONTROL_API GxxLBLine : public GxxView
{
public:
	friend class GxxLBList;

	GxxLBLine();
	virtual ~GxxLBLine();
	
	
	int  getIndex(){return m_index;}
	static void S_ClearBtnDown();

	static const int S_nlineHeight;

protected:

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void Draw();
	
	
	bool       m_isBtnDown;
	int        m_index;

	static GxxLBLine * s_downBtn;
	void ClearBtnDown();
	

private:
	
	void PaintLine(int ntop);
	

	static GxxAniPictureA *S_pAniPicBack;
	static GxxPicture *S_pPicDelimiter;
	
	//string   m_title;
	//string   m_btnName;//要设置的xml标签 的名字
	
};
