#pragma once

#include "GxxView.h"
#include "AnimationManage.h"
#include "HardwareDllModule.h"

class CE_HardwareDll_API GxxProgressBar : public GxxView
{
protected:
	HANDLE     m_handleBack;	//����
	HANDLE     m_handleProgress;	//ǰ��
	HANDLE     m_handleConver;	//����
	RECT       m_ProRect;//��ʾ��RECT
	int        iMax;
	int		   iMin;
	int        iPos;	//λ��

protected:

	//�滭
	virtual void Draw( );
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
    

public:
	GxxProgressBar();
	virtual ~GxxProgressBar();
	virtual void SetDisplayPos(int n);
	int  GetRatioNum();
	void SetRange(int _iMin, int _iMax);
	static GxxView* CreateControl();
	//void startAnimation(Animation * ani);
	

};
