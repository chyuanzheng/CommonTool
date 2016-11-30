#pragma once
#include "PhoneHardwareManager.h"
#include "StdAfx.h"

//GxxString PhoneHardware::sVersion;	//xyf�޸�
PhoneHardware* PhoneHardwareManager::This = NULL;


PhoneHardware* PhoneHardwareManager::GetPhoneHardware()
{
	if(This == NULL)
	{
		This = new PhoneHardware();
		This->Init(AfxGetHWND());
	}
	return This;
}