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

	virtual bool GetSelected(PhoneItem & item);		//获取选中的ITEM的ID
	virtual void DeleteAllItem();	//删除所有项
	virtual int  GetAllItemCount();		//获得所有项的数目
	virtual bool AddItem(const PhoneItem&  item);	//增加项
	virtual bool DeleteItem(int iItemId);  	//删除项
	virtual void  ResetList();  	//重设后刷新

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
