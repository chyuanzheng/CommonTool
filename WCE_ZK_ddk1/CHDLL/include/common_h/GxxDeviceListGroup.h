#pragma once
#include "StrHelp.h"
#include "bluetooth.h"
#include "GxxListGroupBase.h"
#include "GXNotify.h"


class GxxDeviceListLine;
class GxxListPercent;
class GxxAniLable;
class CE_CONTROL_API GxxDeviceListGroup : public GxxListGroupBase ,public PhoneDeviceInterface
{
public:
	virtual bool SetDeviceStatus(int iItemID, DeviceItem::DeviceStatus ds);	//�趨�豸��״̬
	virtual bool GetSelected(DeviceItem & item);		//��ȡѡ�е�ITEM��ID
	virtual void DeleteAllItem();	//ɾ��������
	virtual int  GetAllItemCount();		//������������Ŀ
	virtual bool AddItem(const DeviceItem&  item);	//������
	virtual bool DeleteItem(int iItemId);  	//ɾ����
	virtual void  ResetList();  	//�����ˢ��

public:
	GxxDeviceListGroup();
	virtual ~GxxDeviceListGroup();
	
	static GxxView* CreateControl();



protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, GxxDeviceListGroup);
	void LineBtnDown( WPARAM wParam, LPARAM lParam );
	GxxDeviceListLine *m_select_line;
	GxxListPercent *m_percentBtn;
	GxxAniLable  *m_deleteAll;
	
};
