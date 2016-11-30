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
	virtual bool SetDeviceStatus(int iItemID, DeviceItem::DeviceStatus ds);	//设定设备的状态
	virtual bool GetSelected(DeviceItem & item);		//获取选中的ITEM的ID
	virtual void DeleteAllItem();	//删除所有项
	virtual int  GetAllItemCount();		//获得所有项的数目
	virtual bool AddItem(const DeviceItem&  item);	//增加项
	virtual bool DeleteItem(int iItemId);  	//删除项
	virtual void  ResetList();  	//重设后刷新

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
