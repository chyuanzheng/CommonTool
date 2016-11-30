#pragma once
#include "StrHelp.h"
#include "bluetooth.h"
#include "GxxListGroupBase.h"
#include "GXNotify.h"


class GxxPhoneListLine;
class GxxListPercent;
class GxxAniLable;
class CE_CONTROL_API GxxPhoneListGroup : public GxxListGroupBase ,public PhoneListInterface
{
public:

	virtual bool GetSelected(PhoneItem & item);		//��ȡѡ�е�ITEM��ID
	virtual void DeleteAllItem();	//ɾ��������
	virtual int  GetAllItemCount();		//������������Ŀ
	virtual bool AddItem(const PhoneItem&  item);	//������
	virtual bool DeleteItem(int iItemId);  	//ɾ����
	virtual void  ResetList();  	//�����ˢ��

public:
	GxxPhoneListGroup();
	virtual ~GxxPhoneListGroup();
	
	static GxxView* CreateControl();



protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, GxxPhoneListGroup);
	void LineBtnDown( WPARAM wParam, LPARAM lParam );
	GxxPhoneListLine *m_select_line;
	GxxListPercent *m_percentBtn;
	GxxAniLable  *m_deleteAll;
	
};
