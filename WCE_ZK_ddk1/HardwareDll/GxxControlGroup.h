#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "HardwareDllModule.h"
class CE_HardwareDll_API GxxControlGroup : public GxxView
{

protected:
	virtual void setCtrLayout( TiXmlElement * ele);

    

public:
	GxxControlGroup();
	virtual ~GxxControlGroup();
	//void startAnimation(Animation * ani);
	virtual void Draw( );
	static GxxView* CreateControl();


	void MoveSubControls(int iRelateX, int iRelateY);

	//void SetVisibleStatus(bool _bIsVisible);	//设置控件是否显示
	//BOOL GetVisibleStatus(){ return bIsVisible; }	//获取控件是否显示的状态

private:
	bool bIsVisible;	//控件是否显示
	HANDLE    m_handleBack;
	COLORREF backColor;

	COLORREF getColor(const char* str);
	
};
