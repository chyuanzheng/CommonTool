#include "StdAfx.h"
#include "../i2c/chip.h"
#include "Hardware.h"


namespace Hardware
{
	BYTE ReadHardwareCode()
	{
		return chip_mcu.ReadCarStatus();
	}
	BYTE ReadBack()
	{
		return chip_mcu.ReadBack();
	}
	BYTE ReadLight()
	{
		return chip_mcu.ReadLight();
	}
	BYTE ReadBrake()
	{
		return chip_mcu.ReadBrake();
	}
	BYTE ReadPowerKey()
	{
		return chip_mcu.ReadPowerKey();
	}
	void FanPower(BOOL on)
	{
		chip_mcu.FanPower(on);
	}
	void DVDPower(BOOL on)
	{
		chip_mcu.DVDPower(on);
	}
	void PowerDownSystem()
	{
		chip_mcu.PowerDown();
	}
	void DTVIrCustomer(BYTE c)
	{
		chip_mcu.DTVIRCustom(c);
	}
	void DTVIrCode(BYTE c)
	{
		chip_mcu.DTVIRCode(c);
	}
	BYTE ReadWheelKey()
	{
		return chip_mcu.ReadWheelKey();
	}
	void ExtAMPPower(BYTE p)
	{
		chip_mcu.ExtAMPPower(p);
	}
	void RadioAntPower(BYTE p)
	{
		chip_mcu.RaidoAntPower(p);
	}
	BYTE ReadIRCode()
	{
		return chip_mcu.ReadIRCode();
	}
}