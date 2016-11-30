#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "SkiaBitmapManager.h"
#include "GxxTimer.h"
#include "GxxSwText.h"
class CE_CONTROL_API GxxMoveText : public GxxSwText,GxxTimer 
{
public:
	GxxMoveText();
	virtual ~GxxMoveText();
	static GxxView* CreateControl();	
protected:
	virtual void onResume();
	virtual void onPause();
	virtual void TimerTick(UINT nIDEvent);
	virtual void Draw( );
	virtual void OnTextSet();
	UINT m_idTimer;
	UINT m_nTextLen;
	int  m_nCount;
	bool m_bNeedTimer;
};
