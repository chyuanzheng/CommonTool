#pragma once

#include "GxxView.h"
#include "GxxPicture.h"
typedef  vector<RECT> TV_RECT;
class CE_CONTROL_API GxxRationPage : public GxxView
{
public:
	GxxRationPage();
	virtual ~GxxRationPage();
	static GxxView* CreateControl();
	void setRation(int pos, int sun);


protected:
	//»æ»­
	virtual void Draw( );
	virtual void setCtrLayout( TiXmlElement * ele);

private:
	GxxPicture *m_curIcon;
	GxxPicture *m_norIcon;

	int m_iconWidth;
	int m_iconHeight;
	int m_iconTop;

	TV_RECT m_tv_rect;
	int    m_pos;
};
