#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxListGroupBase.h"

class GxxSetupListLine;
class GxxPicIcon;
class CE_CONTROL_API GxxSelectListGroupBase : public GxxListGroupBase
{

public:
	GxxSelectListGroupBase();
	virtual ~GxxSelectListGroupBase();
	static GxxView* CreateControl();
	virtual bool SetSelLine(int nlan,bool showSel=false );
	bool  GetSelLine(int &nline);

protected:
	virtual void setCtrLayout( TiXmlElement * ele);

	BOOL Response( UINT nMsg, WPARAM wParam, LPARAM lParam );
	void LineBtnDown( WPARAM wParam, LPARAM lParam );
	void finish();



	void setListBoxList( TiXmlElement * ele ) ;
	
	GxxPicIcon *m_bassPic;


};
