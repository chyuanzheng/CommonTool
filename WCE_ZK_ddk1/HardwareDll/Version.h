#pragma once
#include "HardwareDllModule.h"
class CE_HardwareDll_API Version 
{
	static string sVer1;
	static string sVer2;
	static string sVer3;
	static string sVer4;
	static string sVer5;
public:
	static string MCUVersion();
	static string	CANVersion();
	static string BTModuleVersion();
	static string APPVersion();
	static string CoreVersion();
	static string CDVersrion();
	static string BootVersion();

	static string HardwareSerial();
	static string	NaviSoftVersion();
	static string NaviDataVersion1();
	static string NaviDataVersion2();
	static string NaviDataVersion3();
	static string NaviDataVersion4();
	static string NaviDataVersion5();
};