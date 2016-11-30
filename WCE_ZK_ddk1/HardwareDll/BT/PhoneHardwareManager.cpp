#pragma once
#include "PhoneHardwareManager.h"
#include "StdAfx.h"

//GxxString PhoneHardware::sVersion;	//xyfÐÞ¸Ä
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