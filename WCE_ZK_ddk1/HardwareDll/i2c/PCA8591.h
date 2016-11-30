#pragma once

class PCF8591
{
	static const byte slaveAddr = 0x90;
	static const byte VOUTControlBite = 0x40;
	BYTE ReadBytes[4];
	//BYTE aip0 = 0;
	//BYTE aip1 = 0;
	//BYTE aip2 = 0;
	//BYTE aip3 = 0;
	/// <summary>
	/// 模拟输入口
	/// </summary>
	enum AIP
	{
		/// <summary>
		/// AFS
		/// </summary>
		AIN0,
		/// <summary>
		/// QUALITY
		/// </summary>
		AIN1,
		/// <summary>
		/// STOP
		/// </summary>
		AIN2,
		/// <summary>
		/// FSU
		/// </summary>
		AIN3
	};
	/// <summary>
	/// 读取电压(X/256)*5
	/// </summary>
	/// <param name="aip"></param>
	/// <returns></returns>
	BYTE read(AIP aip)
	{
		byte result = 0x00;
		switch (aip)
		{
		case AIN0:
			{
				result = ReadIIC(0x00);
				break;
			}
		case AIN1:
			{
				result = ReadIIC(0x01);
				break;
			}
		case AIN2:
			{
				result = ReadIIC(0x02);
				break;
			}
		case AIN3:
			{
				result = ReadIIC(0x03);
				break;
			}
		}
		return result;
	}
	/// <summary>
	/// 读取8591通道的信息
	/// </summary>
	/// <returns>是否成功读取</returns>
	BYTE ReadIIC(byte sub)
	{
		BYTE result = 0x00;
		IICRead(slaveAddr,sub,1,&result);
		if(IICRead(slaveAddr,sub,1,&result))
		{
			return result;
		}
		return 0;
	}
public:
	BYTE ReadFSU(void)
	{
		return read(AIN3);
	}

	BYTE ReadSSTOP(void)
	{
		return read(AIN2);
	}
};