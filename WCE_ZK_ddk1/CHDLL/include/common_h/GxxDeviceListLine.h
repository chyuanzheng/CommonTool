#pragma once

#include "GxxView.h"
#include "GxxLBLine.h"
#include "bluetooth.h"
class GxxSwText;
class GxxAniButton;
class CE_CONTROL_API GxxDeviceListLine : public GxxLBLine
{
public:

	GxxDeviceListLine();
	virtual ~GxxDeviceListLine();
	void setDeviceLine( int index, int top,const wstring& wstr,DeviceItem::DeviceStatus ds);//index 是第几行，nline可以计算line的Rect
	

	const wstring & getLineName();
	DeviceItem::DeviceStatus getStatus(){ return m_status;}
	bool SetDeviceStatus( DeviceItem::DeviceStatus ds );

	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
private: 

	GxxAniButton *m_btn_Delete;
	GxxAniButton *m_btn_Connect;
	GxxSwText *m_text_Delete;
	GxxSwText *m_text_Connect;
	GxxSwText *m_pTextTitle;
	DeviceItem::DeviceStatus m_status;
	
};
