#pragma once


class Item
{
public:
	int iId;
};

class PhoneItem : public Item
{
public:
	wstring cPhoneNum;	//�绰��
	wstring strName; //����
};

class RecordItem : public Item
{
public:
	typedef enum RecordType
	{
		INCALL = 1,		//����
		OUTCALL,			//ȥ��
		CALLMISS	//δ��
	};
	RecordType eRecordType;
	wstring cPhoneNum;	//�绰
	wstring date;	//�����ȥ���ʱ��
	wstring cPerson;
};




//�绰�б�ӿ�
class  PhoneListInterface
{
public:
	virtual bool GetSelected(PhoneItem & item) = 0;		//��ȡѡ�е�ITEM��ID
	virtual void DeleteAllItem() = 0;	//ɾ��������
	virtual int  GetAllItemCount() = 0;		//������������Ŀ
	virtual bool AddItem(const PhoneItem& item) = 0;	//������
	virtual bool DeleteItem(int iItemId) = 0;  	//ɾ����
	virtual void  ResetList()=0;  	//����� ˢ��
};


//�绰�б�ӿ�
//class  PhoneListInterface
//{
//public:
//	virtual void DeleteAllItem() = 0;	//ɾ��������
//	virtual void  ResetList(RecordItem::RecordType)=0;  	//����� ˢ��
//
//	virtual void PushFront(const PhoneItem& item);	//��ͷ������
//	virtual void PushBack(const PhoneItem& item);	//��β������
//};

//�绰��¼�ӿ�
class  RecordListInterface
{
public:
	virtual bool GetSelected(RecordItem & item) = 0;		//��ȡѡ�е�ITEM��ID
	virtual void DeleteAllItem() = 0;	//ɾ��������
	virtual bool AddItem(const RecordItem& item, bool toBack = true) = 0;	//������
	virtual void  ResetList()=0;  	//����� ˢ��
};


class DeviceItem : public Item
{
public:
	wstring strDeviceName;	//�豸����
	
	typedef enum DeviceStatus
	{
		CONNECTED = 0,
		DISCONNECTED
	};
	DeviceStatus eDeviceStatus;
	 
};

//�����豸�б�ӿ�
class  PhoneDeviceInterface
{
public:
	virtual bool SetDeviceStatus(int iItemID, DeviceItem::DeviceStatus eDeviceStatus) = 0;	//�趨�豸��״̬
	virtual bool GetSelected(DeviceItem & item) = 0;		//��ȡѡ�е�ITEM��ID
	virtual void DeleteAllItem() = 0;	//ɾ��������
	virtual int  GetAllItemCount() = 0;		//������������Ŀ
	virtual bool AddItem(const DeviceItem& item) = 0;	//������
	virtual bool DeleteItem(int iItemId) = 0;  	//ɾ����
	virtual void  ResetList()=0;  	//����� ˢ��
};