#pragma once

#include "stdafx.h"
#include "iic.h"

class PCA9545
{
	BYTE WriteBytes[2];
	static const BYTE slaveAddr = 0xE0;              // Ĭ�ϵ�ַΪ0x70,����д����7λ��ַ
	static const BYTE ConfigByte = 0x0f;
public:
	PCA9545()
	{
		WriteBytes[0] = slaveAddr;
	}
	/// <summary>
	/// ������ͨ��
	/// </summary>
public:
	void OpenAll()
	{
		WriteBytes[0] = slaveAddr;
		WriteBytes[1] = ConfigByte;
		WriteIIC();
	}

	/// <summary>
	/// I2Cд��
	/// </summary>
	BOOL WriteIIC()
	{
		return IICWrite(WriteBytes,2);
	}
};

