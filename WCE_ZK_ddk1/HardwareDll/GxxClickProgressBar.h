#pragma once

#include "GxxProgressBar.h"
#include "AnimationManage.h"
#include "HardwareDllModule.h"
#include "GRect.h"

class CE_HardwareDll_API GxxClickProgressBar : public GxxProgressBar
{
public:
	GxxClickProgressBar();
	virtual ~GxxClickProgressBar();
	static GxxView* CreateControl();
	virtual void SetDisplayPos(int n);
	void    SetMessageView(GxxView *pView);
	//void startAnimation(Animation * ani);

protected:
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
    virtual void setCtrLayout( TiXmlElement * ele);
	void SetDisplayX( int xpos );
private:
	GRect m_clickRect;
	bool m_bClick;
	GxxView * m_mesView;
	

};
