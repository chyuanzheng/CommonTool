#pragma once
#include "StrHelp.h"
#include "bluetooth.h"
#include "GxxListGroupBase.h"
#include "GXNotify.h"


class GxxRecordListLine;
class GxxListPercent;
class GxxAniLable;
class GxxRecordLBList;

class CE_CONTROL_API GxxRecordListGroup : public GxxListGroupBase ,public RecordListInterface
{
public:

	virtual bool GetSelected(RecordItem & item);		//��ȡѡ�е�ITEM��ID
	virtual void DeleteAllItem();	//ɾ��������
	virtual bool AddItem(const RecordItem&  item, bool toBack = true);	//������
	virtual void  ResetList();  	//�����ˢ��

public:
	GxxRecordListGroup();
	virtual ~GxxRecordListGroup();
	
	static GxxView* CreateControl();



protected:
	virtual void setCtrLayout( TiXmlElement * ele);

	

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

private:
	DECLARE_NOTIFY_CALLBACK(RestoreDefault, GxxRecordListGroup);
	void LineBtnDown( WPARAM wParam, LPARAM lParam );
	void SetCallList( RecordItem::RecordType type );
	void InitList();

	//void SetCallList( RecordItem::RecordType type );
	GxxRecordListLine *m_select_line;
	GxxListPercent *m_percentBtn;
	GxxAniLable  *m_deleteAll;

	GxxRecordLBList*	 m_curOutCall;
	GxxRecordLBList*	 m_curInCall;
	GxxRecordLBList*	 m_curMissCall;

    

	RecordItem::RecordType   m_callType;
	GxxAniLable			*m_lableOutCall;
	GxxAniLable			*m_lableInCall;
	GxxAniLable			*m_lableMissCall;
	
};
