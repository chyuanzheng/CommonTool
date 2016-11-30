#pragma once
#include "HardwareDllModule.h"
#include "PhoneHardware2.h"

class CE_HardwareDll_API PhoneHardwareManager
{
public:
	static PhoneHardware* This;
	static PhoneHardware* GetPhoneHardware();
};
