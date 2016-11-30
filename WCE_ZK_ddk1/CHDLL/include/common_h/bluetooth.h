#pragma once


class Item
{
public:
	int iId;
};

class PhoneItem : public Item
{
public:
	wstring cPhoneNum;	//电话号
	wstring strName; //名字
};

class RecordItem : public Item
{
public:
	typedef enum RecordType
	{
		INCALL = 1,		//来电
		OUTCALL,			//去电
		CALLMISS	//未接
	};
	RecordType eRecordType;
	wstring cPhoneNum;	//电话
	wstring date;	//来电或去电的时间
	wstring cPerson;
};




//电话列表接口
class  PhoneListInterface
{
public:
	virtual bool GetSelected(PhoneItem & item) = 0;		//获取选中的ITEM的ID
	virtual void DeleteAllItem() = 0;	//删除所有项
	virtual int  GetAllItemCount() = 0;		//获得所有项的数目
	virtual bool AddItem(const PhoneItem& item) = 0;	//增加项
	virtual bool DeleteItem(int iItemId) = 0;  	//删除项
	virtual void  ResetList()=0;  	//重设后 刷新
};


//电话列表接口
//class  PhoneListInterface
//{
//public:
//	virtual void DeleteAllItem() = 0;	//删除所有项
//	virtual void  ResetList(RecordItem::RecordType)=0;  	//重设后 刷新
//
//	virtual void PushFront(const PhoneItem& item);	//从头部插入
//	virtual void PushBack(const PhoneItem& item);	//从尾部插入
//};

//电话记录接口
class  RecordListInterface
{
public:
	virtual bool GetSelected(RecordItem & item) = 0;		//获取选中的ITEM的ID
	virtual void DeleteAllItem() = 0;	//删除所有项
	virtual bool AddItem(const RecordItem& item, bool toBack = true) = 0;	//增加项
	virtual void  ResetList()=0;  	//重设后 刷新
};


class DeviceItem : public Item
{
public:
	wstring strDeviceName;	//设备名字
	
	typedef enum DeviceStatus
	{
		CONNECTED = 0,
		DISCONNECTED
	};
	DeviceStatus eDeviceStatus;
	 
};

//蓝牙设备列表接口
class  PhoneDeviceInterface
{
public:
	virtual bool SetDeviceStatus(int iItemID, DeviceItem::DeviceStatus eDeviceStatus) = 0;	//设定设备的状态
	virtual bool GetSelected(DeviceItem & item) = 0;		//获取选中的ITEM的ID
	virtual void DeleteAllItem() = 0;	//删除所有项
	virtual int  GetAllItemCount() = 0;		//获得所有项的数目
	virtual bool AddItem(const DeviceItem& item) = 0;	//增加项
	virtual bool DeleteItem(int iItemId) = 0;  	//删除项
	virtual void  ResetList()=0;  	//重设后 刷新
};