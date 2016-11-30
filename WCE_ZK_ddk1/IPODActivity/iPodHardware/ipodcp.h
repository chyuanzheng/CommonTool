#pragma once

#include "i2c/iic.h"

class IpodCP
{
	static const BYTE CPADDR = 0x20;
	BYTE version;
public:
	BYTE certData[1920];
	int	certLen;
	int deviceID;
public:
	IpodCP()
	{
		version = 0;
	}
	BOOL DetectIpodCPVersion()
	{
		if(IICReadIpodCP(CPADDR, 0x0, 1, &version))
		{
			return version;
		}
		return 0;
	}
	BOOL IsExisted()
	{
		return version;
	}

	void ReadDeviceID()
	{
		BYTE data[4] = {0};
		IICReadIpodCP(CPADDR, 0x4, 4, data);
		deviceID = data[0]<<24 | data[1]<<16 | data[2]<<8 | data[3];
	}

	void ReadAcCertificateData()
	{
		if (certLen == 0)
		{
			return;
		}
		int lenLeave = certLen;
		for (int i=0;;i++)
		{
			if (lenLeave >= 128)
			{
				IICReadIpodCP(CPADDR, 0x31+i, 128, &certData[i*128]);
			}
			if (lenLeave < 128)
			{
				IICReadIpodCP(CPADDR, 0x31+i, lenLeave, &certData[i*128]);
				break;
			}
			lenLeave -= 128;
		}
		
	}
	int ReadAcCertificateLength()
	{
		BYTE data[2] ={0};
		if(IICReadIpodCP(CPADDR, 0x30, 2, data))
		{
			certLen = data[0]<<8 | data[1];
			return certLen;
		}
		certLen = 0;
		return 0;
	}
	BOOL SelfTest()
	{
		BYTE data = 0x1;
		if (IICWriteIpodCP(CPADDR, 0x40, 1, &data))
		{
			data = 0xFF;
			if (IICReadIpodCP(CPADDR, 0x40, 1, &data))
			{
				return data;
			}
		}
		return 0;
	}

	void WriteChallengeData(BYTE *data, int len)
	{
		IICWriteIpodCP(CPADDR, 0x21, len, data);
	}
	
	enum
	{
		NO_EFFECT,
		GENERATE_SIGNATURE,
		GENERATE_CHALLENGE,
		VERIFY_SIGNATURE,
		CERT_VALIDATION,
		FORCE_SLEEP
	};
	void WriteAuthControl(BYTE control)
	{
		IICWriteIpodCP(CPADDR, 0x10, control);
	}
	
	//	Most recent process did not produce valid results. 0
	//	Accessory signature successfully generated. 1
	//	Challenge successfully generated. 2
	//	iPod signature successfully verified. 3
	//	iPod certificate successfully validated. 4
	//	Reserved 5-7
	int ReadAuthStatus()
	{
		BYTE data;
		IICReadIpodCP(CPADDR, 0x10, 1, &data);
		return data;
	}
	BOOL Wait4Process()
	{
		return 0;
	}

	int ReadSignatureData(BYTE *data)
	{
		BYTE len[2] = {0};
		BYTE ret = IICReadIpodCP(CPADDR, 0x11, 2, len);
		int Len = len[0]<<8 | len[1];
		if (Len)
		{
			IICReadIpodCP(CPADDR, 0x12, Len, data);
		}
		return Len;
	}


protected:
private:
};