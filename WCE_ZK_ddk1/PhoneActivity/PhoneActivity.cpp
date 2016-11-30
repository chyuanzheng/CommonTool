#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "PhoneActivity.h"
#include "ControlHelp.h"

#include "AVSet.h"
#include "VolumeControl.h"
#include "INC/param.h"

#include "WheelMsg.h"
#include "../NaviActivity/NaviActivity.h"

#define ELAPSE_PHONEBOOK 5000

#define ELAPSE_PHONETIME 1000	//来电计时间隔

#define ELAPSE_ONE_MINUTE 1000

Activity* PhoneActivity::CreateControl()
{
	return new PhoneActivity;
}

void PhoneActivity::onCreate()
{
	
	setContentView("layout\\phone\\PhonePad.xml");
	Activity::onCreate();

	VolumeControl::ApplayForPermission(VolumeModuleId::PHONE, 0, L"PHONE");

	phoneHardware = PhoneHardwareManager::GetPhoneHardware();

	//设置蓝牙名称
	#if _DEBUG
		phoneHardware->SetName("AlpineFeng");
	#else
		phoneHardware->SetName("Alpine");
	#endif

	pLabelRecentCalls = (GxxAniLable*)safeFindViewByName("LabelRecentCalls");

	pLabelPhoneBook = (GxxAniLable*)safeFindViewByName("LabelPhoneBook");

	pLabelKeypad = (GxxAniLable*)safeFindViewByName("LabelKeypad");

	pLabel_Return_Main = (GxxAniLable*)safeFindViewByName("Label_Return_Main");


	pControlGroup_Main = (GxxControlGroup*)safeFindViewByName("ControlGroup_Main");	//主界面
	pControlGroup_keypad = (GxxControlGroup*)safeFindViewByName("ControlGroup_keypad");	//键盘界面
	pControlGroup_PhoneList = (GxxControlGroup*)safeFindViewByName("ControlGroup_PhoneList");	//电话本界面
	pControlGroup_RecordList = (GxxControlGroup*)safeFindViewByName("ControlGroup_RecordList");	//来电记录界面
	pControlGroup_CallReceive = (GxxControlGroup*)safeFindViewByName("ControlGroup_CallReceive");	//电话通话窗口
	

	pLabel_Key0 = (GxxAniLable*)safeFindViewByName("Label_Key0");
	pLabel_Key1 = (GxxAniLable*)safeFindViewByName("Label_Key1");
	pLabel_Key2 = (GxxAniLable*)safeFindViewByName("Label_Key2");
	pLabel_Key3 = (GxxAniLable*)safeFindViewByName("Label_Key3");
	pLabel_Key4 = (GxxAniLable*)safeFindViewByName("Label_Key4");
	pLabel_Key5 = (GxxAniLable*)safeFindViewByName("Label_Key5");
	pLabel_Key6 = (GxxAniLable*)safeFindViewByName("Label_Key6");
	pLabel_Key7 = (GxxAniLable*)safeFindViewByName("Label_Key7");
	pLabel_Key8 = (GxxAniLable*)safeFindViewByName("Label_Key8");
	pLabel_Key9 = (GxxAniLable*)safeFindViewByName("Label_Key9");

	pLabel_KeyC = (GxxAniLable*)safeFindViewByName("Label_KeyC");
	pLabel_KeyXin = (GxxAniLable*)safeFindViewByName("Label_KeyXin");	
	pLabel_KeyJin = (GxxAniLable*)safeFindViewByName("Label_KeyJin");
	pLabelDeleteAll = (GxxAniLable*)safeFindViewByName("LabelDeleteAll");

	pLabel_KeyRing = (GxxAniLable*)safeFindViewByName("Label_KeyRing");

	pLabel_Disconnect = (GxxAniLable*)safeFindViewByName("Label_Disconnect");
	pLabel_Reconnect = (GxxAniLable*)safeFindViewByName("Label_Reconnect");

	pLabelContactsName = (GxxAniLable*)safeFindViewByName("LabelContactsName");

	pLabelHandup = (GxxAniLable*)safeFindViewByName("LabelHandup");
	pLabelSwitchAudio = (GxxAniLable*)safeFindViewByName("LabelSwitchAudio");
	pLabelDiagKeyToKeypad = (GxxAniLable*)safeFindViewByName("LabelDiagKeyToKeypad");
	pLabelDialInterfaceRing = (GxxAniLable*)safeFindViewByName("LabelDialInterfaceRing");
	pLabelDialInterfaceTime = (GxxAniLable*)safeFindViewByName("LabelDialInterfaceTime");
	pLabelDialInterfaceTip = (GxxAniLable*)safeFindViewByName("LabelDialInterfaceTip");

	pLabel_CallReceiveReturnMain = (GxxAniLable*)safeFindViewByName("Label_CallReceiveReturnMain");

	pLabel_ChangeDevice = (GxxAniLable*)safeFindViewByName("Label_ChangeDevice");

	pLabel_To_Music = (GxxAniLable*)safeFindViewByName("Label_To_Music");


	pTextBox_PhoneNum = (GxxTextBox*)safeFindViewByName("TextBox_PhoneNum");
	//pTextBox_PhoneNum->SetText(L"1234", true);

	Notify notify;

	notify.dwParam = this;
	notify.funNotify = BtStatusNotify;
	GXNotify::RegisterNotifyHandler("btstatus", notify);

	
	iTimerPhonebook	= RegisterTimer(ELAPSE_PHONEBOOK);

	iTimerPhoneTime = RegisterTimer(ELAPSE_PHONETIME);

	iTimerPhoneAutoAnswer   = RegisterTimer(ELAPSE_ONE_MINUTE);

	dialTime = 0;	//通话时间


	notify.dwParam = this;
	notify.funNotify = PhoneBookNotify;
	GXNotify::RegisterNotifyHandler("phonebookstatus", notify);

	notify.funNotify = NotifyOpenOrCloseBT;
	GXNotify::RegisterNotifyHandler("NotifyOpenOrCloseBT", notify);

	notify.funNotify = NotifySetBtPassword;
	GXNotify::RegisterNotifyHandler("NotifySetBtPassword", notify);

	notify.funNotify = NotifySetAutoConnect;
	GXNotify::RegisterNotifyHandler("NotifySetAutoConnect", notify);

	notify.funNotify = NotifyReadBTPassword;
	GXNotify::RegisterNotifyHandler("NotifyReadBTPassword", notify);

	
	notify.funNotify = NotifyPhoneRecordStatus;
	GXNotify::RegisterNotifyHandler("phonerecordstatus", notify);

	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);

	findActivity("PhoneDevcieActivity");
	

	UpdateUI(DISCONNECT);
	UpdateUI(MAIN_INTERFACE);

	pPhoneList =  (GxxPhoneListGroup*)safeFindViewByName("PhoneList");
	
	pRecordList =  (GxxRecordListGroup*)safeFindViewByName("RecordList");

	pInc_Into_MainInterface = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");



	
	iPhoneRecordCount = 0;	//电话本记录数

	InitAutoAnswer();

	pLastActivity = NULL;

	//查询蓝牙的状态
	phoneHardware->QueryHFP();

	isNaviOnBeforeCalling = false;	//通话前，是否在导航界面

}

LRESULT PhoneActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//不在本窗口下
	if( Activity::GetActiveActiviy() != (PhoneActivity*)this)
	{
		return 0;
	}

	int iMsg = param1;
	switch(iMsg)
	{
	case HardwareBtnMatch::ANSWER_KEY:	//接听
		{
			Contact();
		}
	case HardwareBtnMatch::DROP_KEY:	//挂断
		{
			Handup();
		}
	case HardwareBtnMatch::BACK_KEY:	//返回
		{
			AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		}

	}
	return 0;
}


LRESULT PhoneActivity::NotifyReadBTPassword(DWORD param1, DWORD param2)
{
	phoneHardware->ReadPassword();
	return 0;
}


LRESULT PhoneActivity::NotifyPhoneRecordStatus(DWORD param1, DWORD param2)
{
	CONTACT* contact = (CONTACT*)(param2);
	//ASSERT(contact != NULL);

	if(contact == NULL)
	{
		if(param1 == PhoneHardware::RECORD_DIAL)
		{
			phoneHardware->ReadRecord(PhoneHardware::RECORD_RECV);
		}
		else if(param1 == PhoneHardware::RECORD_RECV)
		{
			phoneHardware->ReadRecord(PhoneHardware::RECORD_MISS);
		}
		else
		{
			
		}

		//return 0;
	}
	else
	{

		RecordItem recordItem;
		GxxString strName = contact->Name;
		GxxString strNum = contact->num.GetPhoneNum();

		int now_record = param1;
		switch(now_record)
		{
		case PhoneHardware::RECORD_DIAL:
			{
				recordItem.cPhoneNum = strNum.GetData();
				recordItem.cPerson = strName.GetData();
				if(recordItem.cPerson == L"")
				{
					recordItem.cPerson = L"Unknown";
				}
				recordItem.eRecordType = RecordItem::OUTCALL;
				
				pRecordList->AddItem(recordItem);	//增加项
				pRecordList->ResetList();
				RETAILMSG(COUT_MSG,(TEXT("phone record  name=%s, num=%s, RECORD_DIAL \r\n"), strName.GetData(), strNum.GetData()));
			}
			break;
		case PhoneHardware::RECORD_RECV:
			{
				recordItem.cPhoneNum = strNum.GetData();
				recordItem.cPerson = strName.GetData();
				recordItem.eRecordType = RecordItem::INCALL;

				if(recordItem.cPerson == L"")
				{
					recordItem.cPerson = L"Unknown";
				}

				pRecordList->AddItem(recordItem);	//增加项
				pRecordList->ResetList();
				RETAILMSG(COUT_MSG,(TEXT("phone record  name=%s, num=%s, RECORD_RECV \r\n"), strName.GetData(), strNum.GetData()));
			}
			break;
		case PhoneHardware::RECORD_MISS:
			{
				recordItem.cPhoneNum = strNum.GetData();
				recordItem.cPerson = strName.GetData();
				recordItem.eRecordType = RecordItem::CALLMISS;

				if(recordItem.cPerson == L"")
				{
					recordItem.cPerson = L"Unknown";
				}

				pRecordList->AddItem(recordItem);	//增加项
				pRecordList->ResetList();
				RETAILMSG(COUT_MSG,(TEXT("phone record  name=%s, num=%s, RECORD_MISS \r\n"), strName.GetData(), strNum.GetData()));
			}
			break;

		}
		phoneHardware->NextRecord();
	}
	
	
	return 0;
}

LRESULT PhoneActivity::NotifyOpenOrCloseBT(DWORD param1, DWORD param2)
{
	bool bFlag = (bool)param1;
	phoneHardware->BTSwitch(bFlag);
	return 0;
}

LRESULT PhoneActivity::NotifySetBtPassword(DWORD param1, DWORD param2)
{
	char* cPassword = (char *)param1;
	phoneHardware->SetPassword(cPassword);
	return 0;
}


LRESULT PhoneActivity::NotifySetAutoConnect(DWORD param1, DWORD param2)
{
	bool bIsAutoConnect = (bool)param1;
	
	phoneHardware->AutoConnect(bIsAutoConnect);
	
	return 0;
}



void PhoneActivity::KeyKeyPad(char c)
{
	if (phoneHardware->CallStatus == PhoneHardware::CALL_IN)
	{
		phoneHardware->DTMF(c);
		pTextBox_PhoneNum->AddOneChar(c);
	}
	else
	{
		pTextBox_PhoneNum->AddOneChar(c);
	}
}


void PhoneActivity::InsertPhoneRecord(GxxString strName, GxxString strNO, RecordItem::RecordType type)
{

	//RETAILMSG(COUT_MSG, (L"phoneRecord = %s\r\n", strNO.GetData()));


	static int staticID = 0;
	staticID++;
	PHONE phone;
	phone.strNo = strNO;
	phone.strName = strName;
	mapPhoneRecord.insert(pair<int,PHONE>( staticID, phone));

	if (!pRecordList)
	{
		return ;
	}

	// 得到当前时间
	SYSTEMTIME st;
	GetLocalTime(&st);
	GxxString strTime;
	strTime.Format(_T("%02d:%02d %02d%02d"), st.wHour, st.wMinute, st.wMonth, st.wDay);
	
	iPhoneRecordCount++;
	 

	RecordItem item;

	item.cPerson = strName;
	item.cPhoneNum = strNO;
	item.date = strTime;
	item.iId = iPhoneRecordCount;

	item.eRecordType = type;
	RETAILMSG(COUT_MSG, (L"phoneRecord item: no=%s, name=%s, type = %d\r\n", strNO.GetData(), strName.GetData(), type));

	pRecordList->AddItem(item, false);	//插入到列表前面
	pRecordList->ResetList();
}

void PhoneActivity::InsertPhoneBook(GxxString strName, GxxString strNO)
{
	static int staticID = 0;
	staticID++;
 	RETAILMSG(COUT_MSG, (TEXT("phone : name=%s, num = %s\r\n"), strName.GetData(), strNO.GetData()));
	PHONE phone;
	phone.strNo = strNO;
	phone.strName = strName;
	mapPhoneBook.insert(pair<int,PHONE>( staticID, phone));

	PhoneItem item;
	item.iId = staticID;
	item.cPhoneNum = strNO;
	item.strName = strName;

	pPhoneList->AddItem(item);

	//通话薄显示时，刷新
	if(pControlGroup_PhoneList->getDraw())
	{
		pPhoneList->ResetList();
	}
}

LRESULT PhoneActivity::PhoneBookNotify(DWORD param1, DWORD param2)
{
	switch((PhoneHardware::PHONEBOOKSTATUS)param1)
	{
	case PhoneHardware::PHONEBOOK_INITED:
		{
			break;
		}
	case PhoneHardware::PHONEBOOK_SUPPORT:
		{
			break;
		}
	case PhoneHardware::PHONEBOOK_UNSUPPORT:
		{
			break;
		}
	case PhoneHardware::PHONEBOOK_NO:
		{
			CONTACT* contact = (CONTACT*)param2;
			InsertPhoneBook(contact->Name, contact->num.GetPhoneNum());
			break;
		}
	case PhoneHardware::PHONEBOOK_MOBILEEND:
		{
			// 获取sim卡电话本
			Sleep(300);
			phoneHardware->GetSimBook();
			break;
		}
	case PhoneHardware::PHONEBOOK_SIMEND:
		{
			// 读完所有电话本后，开始下载通话记录
			ReadRecord();
			break;
		}
	}
	return 0;
}

void PhoneActivity::UpdateUI(int iStatus)
{
	

	switch(iStatus)
	{
	case DISCONNECT:
		{
			pLabelRecentCalls->setEnable(false);
			pLabelPhoneBook->setEnable(false);
			pLabelKeypad->setEnable(false);
			pControlGroup_CallReceive->setDraw(false);

			pLabel_Disconnect->setDraw(false);
			pLabel_Reconnect ->setDraw(true);
		}
		break;
	case CONNECT:
		{
			pLabelRecentCalls->setEnable(true);
			pLabelPhoneBook->setEnable(true);
			pLabelKeypad->setEnable(true);

			pLabel_Disconnect->setDraw(true);
			pLabel_Reconnect ->setDraw(false);

		}
		break;
	case KEYPAD_INTERFACE:	//键盘界面
		{
			pControlGroup_keypad->setDraw(true);
			pControlGroup_PhoneList->setDraw(false);
			pControlGroup_Main->setDraw(false);
			pControlGroup_RecordList->setDraw(false);
			pControlGroup_CallReceive->setDraw(false);
		}
		break;
	case RECORD_INTERFACE:	//电话记录界面
		{
			pControlGroup_keypad->setDraw(false);
			pControlGroup_PhoneList->setDraw(false);
			pControlGroup_Main->setDraw(false);
			pControlGroup_CallReceive->setDraw(false);
			pControlGroup_RecordList->setDraw(true);
		}
		break;
	case PHONE_INTERFACE:	//电话本界面
		{
			pControlGroup_PhoneList->setDraw(true);
			pPhoneList->ResetList();
			pControlGroup_Main->setDraw(false);
			pControlGroup_keypad->setDraw(false);
			pControlGroup_CallReceive->setDraw(false);
			pControlGroup_RecordList->setDraw(false);

		}
		break;
	case CALLING_INTERFACE:	//通话中界面
		{
			pControlGroup_Main->setDraw(false);
			pControlGroup_keypad->setDraw(false);
			pControlGroup_PhoneList->setDraw(false);
			pControlGroup_RecordList->setDraw(false);
			pControlGroup_CallReceive->setDraw(true);		

			pLabelDialInterfaceTime->setDraw(true);
			pLabelDialInterfaceTip->setDraw(false);

			//pLabelDialInterfaceRing->setEnable(true);
			//pLabelSwitchAudio->setEnable(false);
			pLabelHandup->setEnable(true);
			if (phoneHardware->CallStatus == PhoneHardware::CALL_OUT)
			{
				pLabelDialInterfaceRing->setEnable(true);
				pLabelSwitchAudio->setEnable(false);
				pLabelHandup->setEnable(false);
				pLabel_CallReceiveReturnMain->setDraw(true);

				
			}
			else if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
			{
				//pLabelDialInterfaceRing->setEnable(false);

				pLabelSwitchAudio->setEnable(false);
				pLabel_CallReceiveReturnMain->setDraw(false);
				//pLabelHandup->setEnable(false);
			}
			else if (phoneHardware->CallStatus == PhoneHardware::CALL_DIALING)
			{
				pLabelDialInterfaceRing->setEnable(false);
				pLabelSwitchAudio->setEnable(true);
				pLabel_CallReceiveReturnMain->setDraw(false);
				
				//显示“拨号中”
				pLabelDialInterfaceTip->setDraw(true);
				pLabelDialInterfaceTime->setDraw(false);
				
			}
			
			
		}
		break;
	case MAIN_INTERFACE:	//主界面
		{
			pControlGroup_Main->setDraw(true);
			pControlGroup_keypad->setDraw(false);
			pControlGroup_PhoneList->setDraw(false);
			pControlGroup_RecordList->setDraw(false);
			pControlGroup_CallReceive->setDraw(false);

		}
		break;
	}

	iCurrentUIInterface = iStatus;

	AfxInvalidateRect(&m_ActRect);

}

void PhoneActivity::IntoLastUIInterface()
{
	UpdateUI(iLastUIInterface);
}

LRESULT PhoneActivity::BtStatusNotify(DWORD param1, DWORD param2)
{
	switch((PhoneHardware::BTSTATUS)param1)
	{
	case PhoneHardware::BT_CONNECTED:
		{
			// 蓝牙已连接

			//PreparePairRecord();	//初始化匹配记录 
			UpdateUI(CONNECT);

			
			//开始下载电话本
			StartTimer(iTimerPhonebook);
			

			//发送蓝牙已连接的消息
			AfxPostMessage(CTR_BT_CONNECTED, 0, 0);
			break;
		}
	case PhoneHardware::BT_DISCONNECT:
		{
			//清空当前的匹配名称
			UpdateUI(MAIN_INTERFACE);
			UpdateUI(DISCONNECT);

			pRecordList->DeleteAllItem();

			if (sysConfig.bRecvPhone)
			{
				UpdateUI(MAIN_INTERFACE);
				sysConfig.bRecvPhone = 0;
			}

			// 清空电话本
			StopTimer(iTimerPhonebook);
			ClearPhoneBook();

			//发送蓝牙已断开的消息
			AfxPostMessage(CTR_BT_DISCONNECTED, 0, 0);

			break;
		}
	case PhoneHardware::BT_LINEIN:
		{
		 	// 来电

			//保存当前的窗口
			Activity* pCurrentActivity = Activity::GetActiveActiviy();

			if(pPhoneCallingActivity != pCurrentActivity)
			{
				//跳转到通话界面，并保存指针
				startActivity(pCurrentActivity, "PhoneCallingActivity");
				pPhoneCallingActivity = PhoneCallingActivity::pThis;
				
				NaviActivity* activity = (NaviActivity*)findActivity("NaviActivity");
				if(activity->IsNaviOnTop())
				{
					activity->HideNavi();
					isNaviOnBeforeCalling = true;	//标志在导航界面，接听了电话
				}

				pLastActivity = pCurrentActivity;

			}

			//startActivity(NULL ,"PhoneActivity");

			//UpdateUI(CALLING_INTERFACE);

			if (phoneHardware->contact.num.GetLen() > 0 
				&& phoneHardware->contact.num.GetPhoneNum() != L"+")
			{
				((PhoneCallingActivity*)pPhoneCallingActivity)->SetContactName
					(GetNameFromNo(phoneHardware->contact.num.GetPhoneNum()));
				//pLabelContactsName->SetText(phoneHardware->contact.num.GetPhoneNum().GetData(),
				//						GetNameFromNo(phoneHardware->contact.num.GetPhoneNum()));

				AutoAnswer();	//自动应答

				sysConfig.bRecvPhone = 2;
			}
			else
			{
				pLabelContactsName->SetText(L"", L"");
			}

			break;
		}
	case PhoneHardware::BT_DIALING:
		{

			startActivity(NULL ,"PhoneActivity");
			UpdateUI(CALLING_INTERFACE);

			NaviActivity* activity = (NaviActivity*)findActivity("NaviActivity");
			if(activity->IsNaviOnTop())
			{
				activity->HideNavi();
				//isNaviOnBeforeCalling = true;	//标志在导航界面，接听了电话
			}

			//sysConfig.bRecvPhone++;
			break;
		}
	case PhoneHardware::BT_DIALNO:
		{
			// 拨号号码

			UpdateUI(CALLING_INTERFACE);
			GxxString strPhoneNum = pTextBox_PhoneNum->GetText().c_str();


			pLabelContactsName->SetText(phoneHardware->contact.num.GetPhoneNum().GetData(), GetNameFromNo(phoneHardware->contact.num.GetPhoneNum()));
			

			if (strPhoneNum != phoneHardware->contact.num.GetPhoneNum())
			{
				InsertPhoneRecord(GetNameFromNo(phoneHardware->contact.num.GetPhoneNum()), 
					phoneHardware->contact.num.GetPhoneNum(), RecordItem::OUTCALL);
			}
			break;
		}
	case PhoneHardware::BT_RECV:
		{
			// 接听电话/通话中
			
			UpdateUI(CALLING_INTERFACE);
			dialTime = 0;
			pLabelDialInterfaceTime->SetText(L"", true);
			StartTimer(iTimerPhoneTime);

			sysConfig.bRecvPhone++;

			break;
		}
	case PhoneHardware::BT_HANGUP:
		{

			// 挂断电话
			if(pPhoneCallingActivity)
			{
				
				
				if(pPhoneCallingActivity == Activity::GetActiveActiviy())
				{
					pPhoneCallingActivity->finish();
				}
				if(isNaviOnBeforeCalling)	//通话前的模式是导航
				{
					isNaviOnBeforeCalling = false;

					//启动导航
					//startActivity(NULL,"NaviActivity");
					NaviActivity* activity = (NaviActivity*)findActivity("NaviActivity");
					activity->ShowNavi();
				}
				
			}
			

			pLabelDialInterfaceTime->SetText(L"", true);
			StopTimer(iTimerPhoneTime);

			if (sysConfig.bRecvPhone == 2)
			{
				if (phoneHardware->contact.num.GetLen() > 0)
				{
					InsertPhoneRecord(GetNameFromNo(phoneHardware->contact.num.GetPhoneNum()), 
						phoneHardware->contact.num.GetPhoneNum(), RecordItem::CALLMISS);
				}
			}
			if (sysConfig.bRecvPhone == 3)
			{
				if (phoneHardware->contact.num.GetLen() > 0)
				{
					InsertPhoneRecord(GetNameFromNo(phoneHardware->contact.num.GetPhoneNum()), 
						phoneHardware->contact.num.GetPhoneNum(), RecordItem::INCALL);
				}
			}
			UpdateUI(MAIN_INTERFACE);
			sysConfig.bRecvPhone = 0;

			ExitAutoAnswer();

			break;
		}
	}
	return 0;
}

//读取通话记录
void PhoneActivity::ReadRecord()
{
	phoneHardware->ReadRecord(PhoneHardware::RECORD_DIAL);
}

void PhoneActivity::InitAutoAnswer()	//初始化自动应答
{
	iAutoAnswerTime = 0;
}

void PhoneActivity::ExitAutoAnswer()	//退出自动应答
{
	StopTimer(iTimerPhoneAutoAnswer);

	iAutoAnswerTime = 0;
}

void PhoneActivity::AutoAnswer()	//自动应答
{
	
	if(iAutoAnswerTime > 0) return;	//自动已经开始计时

	//RETAILMSG(COUT_MSG, (L"-----------------------into autoAnswerTimer------------ \r\n"));

	StopTimer(iTimerPhoneAutoAnswer);

	int iTimer = sysConfig.sysParam.curPhoneAutoAnswer;
	switch(iTimer)
	{
	case 0:
		{
			
		}
		break;
	case 5:
		{
			StartTimer(iTimerPhoneAutoAnswer);
		}
		break;
	case 10:
		{
			StartTimer(iTimerPhoneAutoAnswer);
		}
		break;
	case 15:
		{
			StartTimer(iTimerPhoneAutoAnswer);
		}
		break;

	}
}

GxxString PhoneActivity::GetNameFromNo(GxxString strNo)
{
	map<int, PHONE>::iterator iter;
	for(iter = mapPhoneBook.begin();iter!= mapPhoneBook.end(); iter++)
	{
		PHONE phone = iter->second;
		if(phone.strNo == strNo)
		{
			return phone.strName;
		}
	}

	GxxString str86;
	str86 = (GxxString)L"+86" + strNo;
	for(iter = mapPhoneBook.begin();iter!= mapPhoneBook.end(); iter++)
	{
		PHONE phone = iter->second;
		if(phone.strNo == str86)
		{
			return phone.strName;
		}
	}
	return strNo;
}

void PhoneActivity::ClearPhoneBook()
{
	mapPhoneBook.clear();
	iPhoneRecordCount = 0;
	if (pPhoneList)
	{
		pPhoneList->DeleteAllItem();
		pPhoneList->ResetList();
	}
}

void PhoneActivity::RememberLastUIInterfatce()	//记住上一个界面
{
	iLastUIInterface = iCurrentUIInterface;
}


BOOL PhoneActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_LISTBOX_MES:
		{
			if(pControlGroup_RecordList->getDraw())
			{
				//GxxRecordListLine *recordListLine = (GxxRecordListLine *)wParam;
				RecordItem recordItem;
				pRecordList->GetSelected(recordItem);

				recordItem.cPhoneNum;
				pTextBox_PhoneNum->SetText(recordItem.cPhoneNum, true);
				pLabelContactsName->SetText(GetNameFromNo(recordItem.cPhoneNum.c_str()).GetData());

				RememberLastUIInterfatce();	//记住上一个界面
					
				UpdateUI(CALLING_INTERFACE);

			}
			else if(pControlGroup_PhoneList->getDraw())
			{
				int iItemLine = lParam;
				map<int, PHONE>::iterator it;

				it = mapPhoneBook.find(iItemLine);
				if(it != mapPhoneBook.end())
				{
					PHONE phone = it->second;
					pTextBox_PhoneNum->SetText(phone.strNo.GetData(), true);
					if (pTextBox_PhoneNum->GetLength())
					{
						GxxString strNum = pTextBox_PhoneNum->GetText().c_str();
						pLabelContactsName->SetText(GetNameFromNo(pTextBox_PhoneNum->GetText().c_str()).GetData(), true);
					}

					RememberLastUIInterfatce();	//记住上一个界面

					UpdateUI(CALLING_INTERFACE);
					

				}
			}
			

		}
		return TRUE;
	case CTR_LISTBOX_X:
		{
			UpdateUI(MAIN_INTERFACE);
			return TRUE;
		}
		return FALSE;
	case  MES_MSG_OK:
		{
			RememberLastUIInterfatce();	//记住上一个界面
			Contact();	//拨电话
			return TRUE;
		}
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxAniLable *)wParam == pLabel_ChangeDevice)	
			{
				startActivity(this ,"PhoneDevcieActivity");
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_To_Music)		//跳转到蓝牙音乐界面
			{
				startActivity(NULL ,"BTMusicActivity");
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pInc_Into_MainInterface)	
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelDialInterfaceRing)	//通话界面中接听电话
			{
				if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
				{
					phoneHardware->Reject();
				}
				else
				{
					Contact();
				}
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelRecentCalls)	//跳转到通话界面
			{
				UpdateUI(RECORD_INTERFACE);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelSwitchAudio)	//切换手机与蓝牙声道
			{
				KeyTransform();
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pLabelKeypad)	//跳转到键盘界面
			{
				UpdateUI(KEYPAD_INTERFACE);
				return TRUE;
			}

			if ((GxxAniLable *)wParam == pLabel_CallReceiveReturnMain )	//电话界面跳转
			{
				//UpdateUI(MAIN_INTERFACE);
				IntoLastUIInterface();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Return_Main )	//跳转到主界面
			{
				if(phoneHardware->CallStatus == PhoneHardware::CALL_DIALING || 
					phoneHardware->CallStatus == PhoneHardware::CALL_COMING ||
					phoneHardware->CallStatus == PhoneHardware::CALL_IN)
				{
					UpdateUI(CALLING_INTERFACE);
				}
				else
				{
					UpdateUI(MAIN_INTERFACE);
				}
				
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pLabelPhoneBook)	//跳转到电话本界面
			{
				UpdateUI(PHONE_INTERFACE);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Disconnect)	//断开蓝牙连接
			{
				phoneHardware->HshfDisconnect();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Reconnect)	//重新连接蓝牙
			{
				phoneHardware->HshfConnect(0);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelDiagKeyToKeypad)	//到蓝牙键盘界面
			{
				UpdateUI(KEYPAD_INTERFACE);
				return TRUE;
			}
			
			if ((GxxAniLable *)wParam == pLabel_Key0)	
			{
				KeyKeyPad('0');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key1)	
			{
				KeyKeyPad('1');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key2)	
			{
				KeyKeyPad('2');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key3)	
			{
				KeyKeyPad('3');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key4)	
			{
				KeyKeyPad('4');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key5)	
			{
				KeyKeyPad('5');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key6)	
			{
				KeyKeyPad('6');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key7)	
			{
				KeyKeyPad('7');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key8)	
			{
				KeyKeyPad('8');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Key9)	
			{
				KeyKeyPad('9');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyC)	
			{
				pTextBox_PhoneNum->DeleteOneChar();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelDeleteAll)	
			{
				pTextBox_PhoneNum->DeleteAll();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyXin)	
			{
				KeyKeyPad('*');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyJin)	
			{
				KeyKeyPad('#');
				
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_KeyRing)	
			{
				if(pTextBox_PhoneNum->GetLength() > 0)
				{
					AfxMessageBox(pTextBox_PhoneNum->GetText(),
						this, 0, ZKY_MB_DIAL_CANCEL);
				}
				
				
				return TRUE;
			}
			if((GxxAniLable *)wParam == pLabelHandup)
			{
				Handup();
				return TRUE;
			}
	
		}
	default:
		return FALSE;

	}
	return FALSE;
}
 
void PhoneActivity::Handup()
{
	if (phoneHardware->CallStatus == PhoneHardware::CALL_OUT)
	{
		// 清除当前拨号号码

		pTextBox_PhoneNum->SetText(L"", true);
	}
	else if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
	{
		phoneHardware->RecvCall();
	}
	else
	{
		
		phoneHardware->HangUp();
	}
}

void PhoneActivity::KeyTransform()
{
	if (phoneHardware->SoundStatus == PhoneHardware::SOUND_BTMODULE)
	{
		phoneHardware->Divert();
	}
	else
	{
		phoneHardware->Divert();
	}

}

void PhoneActivity::Contact()	//拨电话
{
	if (phoneHardware->CallStatus == PhoneHardware::BT_DISCONNECT)
	{
		if (pTextBox_PhoneNum->GetText() == _T("*#9417#*"))
		{
//			MediaControl::Close();
			PROCESS_INFORMATION pi;
			CreateProcess(_T("\\windows\\explorer.exe"), NULL, NULL, NULL, 0, 0, NULL, NULL, NULL, &pi);
			DestroyWindow(AfxGetHWND());
			//PostQuitMessage(0);
			return;
		}
	}

	if (phoneHardware->CallStatus == PhoneHardware::CALL_OUT)
	{ 
		if (pTextBox_PhoneNum->GetLength())
		{
			GxxString strNum = pTextBox_PhoneNum->GetText().c_str();
			char num[100] = {0};
			strNum.ToAscii(num);
			phoneHardware->Dial(num);
			
			pLabelContactsName->SetText(GetNameFromNo(pTextBox_PhoneNum->GetText().c_str()).GetData(), true);
			InsertPhoneRecord(GetNameFromNo(pTextBox_PhoneNum->GetText().c_str()), pTextBox_PhoneNum->GetText().c_str(), RecordItem::OUTCALL);
		}
	}
	else if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
	{
		phoneHardware->RecvCall();
	}
}

void PhoneActivity::onStop()
{
	AVSET::LeaveBTPhone();
}

void PhoneActivity::onResume()
{
	AVSET::ToBTPhone();

	//控制音量
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::PHONE);
	

}

void PhoneActivity::onPause()
{



}

void PhoneActivity::TimerTick( UINT nIDEvent )
{

	if (nIDEvent == iTimerPhonebook)
	{
		static int Times = 0;
		if (Times++ > 1)
		{
			StopTimer(nIDEvent);
			if (mapPhoneBook.empty())
			{
				phoneHardware->GetPhoneBook();
			}
			Times = 0;
		}
	}
	else if(nIDEvent == iTimerPhoneTime)
	{
		int min = ++dialTime/60;
		int sec = dialTime%60;
		GxxString strTime;
		strTime.Format(_T("%02d:%02d"), min, sec);
		pLabelDialInterfaceTime->SetText(strTime.GetData(), true);
		
	}
	else if(nIDEvent == iTimerPhoneAutoAnswer)
	{
		int iTimer = sysConfig.sysParam.curPhoneAutoAnswer;
		if(iAutoAnswerTime < iTimer)
		{
			iAutoAnswerTime++;
			RETAILMSG(COUT_MSG, (L"autoAnswerTimer = %d\r\n", iAutoAnswerTime));
		}
		else	//时间到，接听电话
		{
			ExitAutoAnswer();
			
			//接听电话
			if (phoneHardware->CallStatus == PhoneHardware::CALL_COMING)
			{
				phoneHardware->Reject();
			}
		}
	}


}

static RegisterHelp help("PhoneActivity", PhoneActivity::CreateControl);