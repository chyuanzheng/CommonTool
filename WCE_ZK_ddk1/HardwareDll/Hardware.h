#pragma once
#include "i2c/memdef.h"

namespace Hardware
{
	BYTE CE_HardwareDll_API ReadHardwareCode();
	BYTE CE_HardwareDll_API ReadBack();
	BYTE CE_HardwareDll_API ReadLight();
	BYTE CE_HardwareDll_API ReadBrake();
	BYTE CE_HardwareDll_API ReadPowerKey();
	void CE_HardwareDll_API FanPower(BOOL on);
	void CE_HardwareDll_API DVDPower(BOOL on);
	void CE_HardwareDll_API PowerDownSystem();
	void CE_HardwareDll_API DTVIrCustomer(BYTE c);	//IR ¿Í»§Âë
	void CE_HardwareDll_API DTVIrCode(BYTE c);
	BYTE CE_HardwareDll_API ReadWheelKey();
	void CE_HardwareDll_API ExtAMPPower(BYTE p);
	void CE_HardwareDll_API RadioAntPower(BYTE p);
	BYTE CE_HardwareDll_API ReadIRCode();
}