#pragma once
#include "iic.h"
#include "memdef.h"

class MCU
{
	static const BYTE ADDR = 0xD2;
public:
	BYTE ReadCarStatus()
	{
		BYTE data = 0;
		IICReadMcu(ADDR, MEM_CAR_STATE_CHANGE, 1, &data);
		return data;
	}
	BYTE ReadACC()
	{
		BYTE data = 255;
		IICReadMcu(ADDR, MEM_ACC_STATUS, 1, &data);
		return data;
	}
	BYTE ReadBack()
	{
		BYTE data = 255;
		IICReadMcu(ADDR, MEM_BACK_STATUS, 1, &data);
		return data;
	}
	BYTE ReadLight()
	{
		BYTE data = 255;
		IICReadMcu(ADDR, MEM_LIGHT_STATUS, 1, &data);
		return data;
	}
	BYTE ReadBrake()
	{
		BYTE data = 255;
		IICReadMcu(ADDR, MEM_BRAKE_STATUS, 1, &data);
		return data;
	}
	BYTE ReadPowerKey()
	{
		BYTE data = 255;
		IICReadMcu(ADDR, MEM_POWER_KEY, 1, &data);
		return data;
	}
	BYTE ReadWheelKey()
	{
		BYTE data = 255;
		IICReadMcu(ADDR, MEM_WHEEL_KEY, 1, &data);
		return data;
	}
	void FanPower(BOOL on)
	{
		IICWrite4(ADDR, MEM_FAN_POWER, on);
	}
	void DVDPower(BOOL on)
	{
		IICWrite4(ADDR, MEM_DVD_POWER, on);
	}
	BOOL AMPMute(BOOL on)
	{
		return TRUE;
	}
	void PowerDown()
	{
		IICWrite4(ADDR, MEM_SYSTEM_POWER_OFF, 1);
	}
	void DTVIRCustom(BYTE custom)
	{
		IICWrite4(ADDR, MEM_DTV_IR_CUSTOM, custom);
	}
	void DTVIRCode(BYTE code)
	{
		IICWrite4(ADDR, MEM_DTV_IR_CODE, code);
	}
	void ExtAMPPower(BYTE pwr)
	{
		IICWrite4(ADDR, MEM_EXTAMP_POWER, pwr);
	}
	void RaidoAntPower(BYTE pwr)
	{
		IICWrite4(ADDR, MEM_DTV_POWER, pwr);
	}
	BYTE ReadYear()
	{
		BYTE data = 0;
		IICReadMcu(ADDR, MEM_MCU_VER_YEAR, 1, &data);
		return data;
	}
	BYTE ReadMonth()
	{
		BYTE data = 0;
		IICReadMcu(ADDR, MEM_MCU_VER_MONTH, 1, &data);
		return data;
	}
	BYTE ReadDay()
	{
		BYTE data = 0;
		IICReadMcu(ADDR, MEM_MCU_VER_DAY, 1, &data);
		return data;
	}
	BYTE ReadIRCode()
	{
		BYTE data = 0;
		IICReadMcu(ADDR, MEM_IR_ARM, 1, &data);
		return data;
	}
	static void NJW2573Output(BYTE o)
	{
		IICWrite4(ADDR, MEM_NJW_OUTPUT, o);
	}
};
