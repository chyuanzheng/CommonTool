#pragma once
#include "GxxPicture.h"
#include "AnimationManage.h"
#include "GxxTimer.h"

class GxxProgressV;
class GxxSwText;
class CE_CONTROL_API GxxVolume : public GxxPicture,protected GxxTimer
{
public:
	GxxVolume();
	virtual ~GxxVolume();
	static GxxView* CreateControl();
protected:
	virtual void TimerTick(UINT nIDEvent);
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	void renewVolume();
	GxxProgressV *m_progress;
	GxxSwText *m_textvol;
	UINT      m_uTimerId;
	int      m_nMaxVolume;
	int      m_nCurVolume;
	
};
