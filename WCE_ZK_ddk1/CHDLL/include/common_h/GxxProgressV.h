#pragma once

#include "GxxPicture.h"
#include "AnimationManage.h"
class CE_CONTROL_API GxxProgressV : public GxxView
{
public:
	GxxProgressV();
	virtual ~GxxProgressV();

	//void SetSum(int s);
	void SetProgress( float fs, float fe );
	static GxxView* CreateControl();
	//void startAnimation(Animation * ani);
protected:

	//�滭
	virtual void Draw( );
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
    
protected:

	float      m_fstart;
	float      m_fend;

	bool       m_isHorizon;//�Ƿ�Ϊˮƽ
	GxxPicture *m_pPicUp;
	GxxPicture *m_pPicProgress;

	GxxPicture *m_pPicBack;

};
