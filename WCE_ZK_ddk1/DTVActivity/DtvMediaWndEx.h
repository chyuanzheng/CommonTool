#pragma once
#include "DTVDllModule.h"
#include "TccMediaWnd.h"
#include "ControlHelp.h"
#include "pip/PIP.h"

//#include "GXNotify.h"

class CE_DTVACTIVITY_API DtvMediaWndEx : public TccMediaWnd
{
public:
	DtvMediaWndEx::DtvMediaWndEx()
	{
		m_mesView = NULL;
	} 
	static GxxView* CreateControl()
	{
		return new DtvMediaWndEx;
	}




	void SetFullScreen();
	void ReductionScreen();


	void setDraw(bool bShow);
	void SetMessageView( GxxView* v ){m_mesView = v;}

protected:
	void Draw();

	BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );
	void setCtrLayout( TiXmlElement * ele );
private:
	CRect rcOld;

	int iWidth;
	int iHeight;
	GxxView *m_mesView;
};


	