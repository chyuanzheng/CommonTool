#pragma once

#include "stdafx.h"
#include "iic.h"

class PCA9545
{
	BYTE WriteBytes[2];
	static const BYTE slaveAddr = 0xE0;              // 默认地址为0x70,这里写的是7位地址
	static const BYTE ConfigByte = 0x0f;
public:
	PCA9545()
	{
		WriteBytes[0] = slaveAddr;
	}
	/// <summary>
	/// 打开所有通道
	/// </summary>
public:
	void OpenAll()
	{
		WriteBytes[0] = slaveAddr;
		WriteBytes[1] = ConfigByte;
		WriteIIC();
	}

	/// <summary>
	/// I2C写入
	/// </summary>
	BOOL WriteIIC()
	{
		return IICWrite(WriteBytes,2);
	}
};

