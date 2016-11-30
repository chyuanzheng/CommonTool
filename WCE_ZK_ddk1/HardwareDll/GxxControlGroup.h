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

	//void SetVisibleStatus(bool _bIsVisible);	//���ÿؼ��Ƿ���ʾ
	//BOOL GetVisibleStatus(){ return bIsVisible; }	//��ȡ�ؼ��Ƿ���ʾ��״̬

private:
	bool bIsVisible;	//�ؼ��Ƿ���ʾ
	HANDLE    m_handleBack;
	COLORREF backColor;

	COLORREF getColor(const char* str);
	
};
