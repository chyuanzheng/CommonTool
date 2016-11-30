#pragma once
#include "GxxLBList.h"
#include "bluetooth.h"

class GxxDeviceListLine;

class CE_CONTROL_API GxxDeviceLBList : public GxxLBList
{
public:
	GxxDeviceLBList(){;}
	virtual ~GxxDeviceLBList(){;}
	void AddDevice( int id, const wstring &name,DeviceItem::DeviceStatus ds );
	void DeleteItem( int iItemId );
	bool SetDeviceStatus( int iItemID, DeviceItem::DeviceStatus ds );

private:
	GxxDeviceListLine * FindLineFromId( int iItemId ) ;
};
