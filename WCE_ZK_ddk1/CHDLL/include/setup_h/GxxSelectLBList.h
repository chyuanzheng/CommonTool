#pragma once
#include "GxxLBList.h"
class GxxSetupListLine;
class CE_CONTROL_API GxxSelectLBList : public GxxLBList
{
public:
	GxxSelectLBList();
	virtual ~GxxSelectLBList();
	virtual void setCtrLayout( TiXmlElement * ele);
	bool SetLineChoosed( int nlan,bool showSel=false );
	int GetLineChoosed(){ return m_nSelNth;}
	GxxSetupListLine * GetNthLine( int nlan );
	int GetViewIndex( GxxView * vline );
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	virtual void    onMoveRect(int x_len, int y_len );
	virtual void Draw( );
	

private:
	GxxPicture *m_selPic;
	int m_nSelNth;
};
