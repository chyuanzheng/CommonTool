#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "PhoneDevcieActivity.h"
#include "ControlHelp.h"
#include "Audio/Audio.h"
#include "PIP/PIP.h"
#include "AVSet.h"
#include "VolumeControl.h"



Activity* PhoneDevcieActivity::CreateControl()
{
	return new PhoneDevcieActivity;
}

void PhoneDevcieActivity::onCreate()
{
	setContentView("layout\\phone\\PhoneDeviceActivity.xml");
	Activity::onCreate();
	
	pLabelList_DeleteAll = (GxxAniLable*)safeFindViewByName("List_DeleteAll");
	pLabelList_DeleteAll->setDraw(false);

	pLstPairRecord = (GxxDeviceListGroup*)safeFindViewByName("DeviceList");

	Notify notify;
	notify.dwParam = this;

	notify.funNotify = BtStatusNotify;
	GXNotify::RegisterNotifyHandler("btstatus", notify);
	notify.funNotify = PairRecordNotify;
	GXNotify::RegisterNotifyHandler("pairrecord", notify);
	//notify.funNotify = GetPhoneHardware;
	//GXNotify::RegisterNotifyHandler("PhoneHardware", notify);
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);


	pPhoneHardware = PhoneHardwareManager::GetPhoneHardware();
	
	PreparePairRecord();

	bConnectStatus = false;

	//iTimerConnect = RegisterTimer(1000);
}

LRESULT PhoneDevcieActivity::PairRecordNotify(DWORD param1, DWORD param2)
{
	PhoneHardware::PairInfo *info = (PhoneHardware::PairInfo*)param1;

	GxxString name;
	name.UTF8ToUNICODE(info->name);

	InsertPairRecord( name, info->index);


	return 0;
}

void PhoneDevcieActivity::InsertPairRecord(GxxString strName, int pos)
{
	RETAILMSG(COUT_MSG, (L"pos = %d, Device = %s \r\n", pos, strName.GetData()));
	DeviceItem item;
	/*if (pos == 0)
	{
		return;
	}*/

	if(pos ==1 && pPhoneHardware->BtStatus == PhoneHardware::BT_CONNECTED)
	{

		item.eDeviceStatus = DeviceItem::DISCONNECTED;
		item.strDeviceName = strName.GetData();
		item.iId = 1;
		pLstPairRecord->AddItem(item);
		pLstPairRecord->ResetList();

	}
	else
	{
		item.eDeviceStatus = DeviceItem::CONNECTED;
		item.strDeviceName = strName.GetData();
		item.iId = pos;
		pLstPairRecord->AddItem(item);
		pLstPairRecord->ResetList();

	}

}

void PhoneDevcieActivity::DeletePairRecord(int pos)
{
	if(pos ==1 && pPhoneHardware->BtStatus == PhoneHardware::BT_CONNECTED)
	{
		PairDisConnect();
		Sleep(200);
	}

	pPhoneHardware->DeletePairInfo(pos);
	Sleep(100);
	PreparePairRecord();
}

void PhoneDevcieActivity::PreparePairRecord()
{
	

	//删除所有匹配项
	pLstPairRecord->DeleteAllItem();
	pLstPairRecord->ResetList();


	//获得匹配项目
	pPhoneHardware->PairRecord();	
}


LRESULT PhoneDevcieActivity::BtStatusNotify(DWORD param1, DWORD param2)
{
	switch((PhoneHardware::BTSTATUS)param1)
	{
	case PhoneHardware::BT_CONNECTED:
		{
			PreparePairRecord();
			AfxMessageBox("ID_WAIT_BT",0);//去掉对话框
			AfxPostMessage(CTR_BUTTON_SWITCH, 0, 0);
			break;
		}
	case PhoneHardware::BT_DISCONNECT:
		{
			if(bConnectAnotherBtDevice)
			{
				bConnectAnotherBtDevice = false;

				PairConnect(iWillingSelect);
			}
			else if(bDeleteBtDevice)
			{
				bDeleteBtDevice = false;
				DeletePairRecord(iWillingSelect);
			}
			else
			{
				PreparePairRecord();
			}
			

			break;
		}
	case PhoneHardware::BT_LINEIN:
		{

			break;
		}
	case PhoneHardware::BT_DIALING:
		{

			break;
		}
	case PhoneHardware::BT_DIALNO:
		{

			break;
		}
	case PhoneHardware::BT_RECV:
		{

			break;
		}
	case PhoneHardware::BT_HANGUP:
		{
			break;
		}

	}
	return 0;
}

void PhoneDevcieActivity::PairDisConnect()
{
	pPhoneHardware->HshfDisconnect();
	
	
}

void PhoneDevcieActivity::PairConnect(int select)
{
	pPhoneHardware->HshfConnect(select);

	RECT rc;
	::SetRect(&rc,180,100,680,200);
	AfxMessageBox("ID_WAIT_BT",5,&rc);//启动等待对话框
	AfxPostMessage(CTR_BUTTON_SWITCH, 1, 0);
	
}

BOOL PhoneDevcieActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_DELETE_ALL:
		{
			//删除所有记录
			pPhoneHardware->DeletePairInfo(-1);
			return TRUE;
		}
		return FALSE;
	case CTR_LISTBOX_X:
		{
			finish();
			return true;
		}
		return FALSE;
	case CTR_LISTBOX_MES:
		{
			
			return TRUE;
		}
		return FALSE;
	case CTR_DEVICE_DELETE:
		{
			
			int iSelect = lParam;
			//已经连接时，先断开连接，并记录下要断开的设备ID
			if(pPhoneHardware->BtStatus == PhoneHardware::BT_CONNECTED && iSelect == 1)
			{
				PairDisConnect();
				bDeleteBtDevice = true;
				iWillingSelect = iSelect;
			}
			else
			{
				DeletePairRecord(iSelect);
			}

			return TRUE;
		}
		return FALSE;
	case CTR_DEVICE_CONNECT:
		{
			int iSelect = lParam;

			//已经连接时，先断开连接，并记录下要连接的设备ID
			if(pPhoneHardware->BtStatus == PhoneHardware::BT_CONNECTED)
			{
				PairDisConnect();
				bConnectAnotherBtDevice = true;
				iWillingSelect = iSelect;
			}	
			
			//连接新设备
			if(pPhoneHardware->BtStatus == PhoneHardware::BT_DISCONNECT)
			{
				PairConnect(iSelect);
			}
			
			return TRUE;
		}
		return FALSE;
	case CTR_DEVICE_DISCONNECT:
		{
			if(pPhoneHardware->BtStatus == PhoneHardware::BT_CONNECTED)
			{
				PairDisConnect();
			}

			return TRUE;
		}
		return FALSE;
	
	default:
		return FALSE;
	}
	return FALSE;
}

LRESULT PhoneDevcieActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	//删除所有记录
	if(pPhoneHardware)
	{
		pPhoneHardware->DeletePairInfo(-1);
	}
	
	return 0;
}

void PhoneDevcieActivity::onStop()
{
	
}

void PhoneDevcieActivity::onResume()
{
	
}

void PhoneDevcieActivity::onPause()
{
	

}

static RegisterHelp help("PhoneDevcieActivity", PhoneDevcieActivity::CreateControl);