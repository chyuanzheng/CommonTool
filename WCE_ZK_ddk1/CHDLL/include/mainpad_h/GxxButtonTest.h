#pragma once

#include "GxxView.h"
#include "AnimationManage.h"

class GxxVedioSetup;
class CE_CONTROL_API GxxButtonTest : public GxxView
{
protected:
	HANDLE     m_handleUp;
	GxxVedioSetup *m_setupV;
	//��ťͼƬ
	//�ж��Ƿ񱻰���
	TCHAR     m_isGxxButtonDown;
protected:

	//�滭
	virtual void Draw( );
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void setCtrLayout( TiXmlElement * ele);
	BOOL InMyArea( int x, int y );
    

public:
	GxxButtonTest();
	virtual ~GxxButtonTest();
	static GxxView* CreateControl();
	DWORD m_time;
	//void startAnimation(Animation * ani);
	

};
