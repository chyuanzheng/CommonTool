#pragma once
#include "GxxView.h"
#include "AnimationManage.h"
#include "GxxString.h"
#include "CRect.h"
#include "HardwareDllModule.h"
#include "GxxPicIcon.h"
#include "GxxSwText.h"
#include "GxxPicIcon.h"

class CE_HardwareDll_API GxxTextBox : public GxxPicIcon
{
public:
	//���
	void DeleteAll();

	//�Ƿ�Ϊ��
	bool IsEmpty();

	//��ȡ����
	int GetLength();

	//����һ���ַ�
	bool AddOneChar(char c);

	//ɾ��һ���ַ�
	bool DeleteOneChar();

	wstring GetText();

	void SetText(const wstring &str, bool bDraw = true);
	void SetText(const char *str,bool bDraw = true);
protected:
	
	//��Ӧ�����¼�
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	


	GxxSwText *m_swtext;
	GxxPicIcon *m_picIcon;
	GxxPicIcon *m_pPicDisable;

	void SetLayout( int center_x,int center_y,const char *picDisable );
	//void setChildLayout( TiXmlElement * ele );
	virtual void setCtrLayout( TiXmlElement * ele);

public:
	GxxTextBox();
	virtual ~GxxTextBox();

	static GxxView* CreateControl();
};
