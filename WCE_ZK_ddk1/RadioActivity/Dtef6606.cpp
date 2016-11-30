/***************************************************************************************
* (C) Copyright NXP semiconductor, All rights reserved
* FILE NAME:	<Dtef6606.c>
* VERSION:		<1.0>
* DESCRIPTION:	Tuner driver part
* DOCUMENT REF: <References to specification or other documents related to this module>
* NOTES:		<File notes>
***************************************************************************************/

// =================================================================================================
// Header files
// =================================================================================================
#include "stdafx.h"
#include "6606.h"
#include "Dtef6606.h"
#include "Ftun.h"
#include "i2c/iic.h"
// =================================================================================================
// Public data
// =================================================================================================
uint8 Tuner_Read[ATomIC_I2C_LENGTH];	//Tuner reading 5 registers

/*-----------------------------------------------------------------------
Function name:	readTunerRegister
Input:			i2c_adr,*read_buffer,num
Output:			N/A
Description:	Read tuner registers
------------------------------------------------------------------------*/
uint8 readTunerRegister(uint8 i2c_adr, uint8 *read_buffer, uint32 num)
{	
	//return (IRcvNByte(i2c_adr, read_buffer, num));;
	return IICRead4(i2c_adr, num, read_buffer);
}

/*-----------------------------------------------------------------------
Function name:	writeTunerRegister
Input:			i2c_adr,i2c_subtype,sub_adr,*write_buffer,num
Output:			N/A
Description:	Write tuner registers
------------------------------------------------------------------------*/
uint8 writeTunerRegister(uint8 i2c_adr, uint8 i2c_subtype, uint32 sub_adr, uint8 *write_buffer, uint32 num)
{
	//return (I2C_WriteNByte(i2c_adr, i2c_subtype, sub_adr, write_buffer, num));
	//BYTE *pData = new BYTE[num+2];
	//pData[0] = i2c_adr;
	//pData[1] = sub_adr;
	//memcpy(&pData[2], write_buffer, num);
	//BOOL ret = IICWrite4(pData, num+2);
	//delete []pData;
	//return ret;
	return IICWrite4(i2c_adr, sub_adr, num, write_buffer);
}

/*-----------------------------------------------------------------------
Function name:	getLevel
Input:			N/A
Output:			Level
Description:	Get Level
------------------------------------------------------------------------*/
uint8 getLevel(void)
{
	if(readTunerRegister(ATomIC_I2C_Addr, Tuner_Read, ATomIC_I2C_LENGTH))
	return(Tuner_Read[Read_LEVEL]);
	return 0;
}

/*-----------------------------------------------------------------------
Function name:	getIFCounter
Input:			IFCReady
Output:			IFcount_result
Description:	Get IFCOUNT result while IFCReady is true (32ms IFCounter
				result available), or return IFCounter result status.
------------------------------------------------------------------------*/
uint8 getIFCounter(uint8 IFCReady,uint8 band) 
{	
	readTunerRegister(ATomIC_I2C_Addr, Tuner_Read, ATomIC_I2C_LENGTH);
	if(IFCReady)
		{
			if(band == Band_FM || band == Band_OIRT)
				return((Tuner_Read[Read_IFCOUNT] & Read_Bit_IFCOUNT)*5+5);
			else
				return((Tuner_Read[Read_IFCOUNT] & Read_Bit_IFCOUNT)/2+1/2);       //Jimmy add for handling AM_IFC data 20081203

		}
	else
		return((Tuner_Read[Read_IFCOUNT] & Read_Bit_IFCREADY));

}

/*-----------------------------------------------------------------------
Function name:	getUSN
Input:			N/A
Output:			USN
Description:	Get USN indication
------------------------------------------------------------------------*/
uint8 getUSN(void)
{
	readTunerRegister(ATomIC_I2C_Addr, Tuner_Read, ATomIC_I2C_LENGTH);
	return((Tuner_Read[Read_USN_WAM] & Read_Bit_USN) >> 4);
}

/*-----------------------------------------------------------------------
Function name:	getWAM
Input:			N/A
Output:			WAM
Description:	Get WAM indication
------------------------------------------------------------------------*/
uint8 getWAM(void)
{
	readTunerRegister(ATomIC_I2C_Addr, Tuner_Read, ATomIC_I2C_LENGTH);
	return(Tuner_Read[Read_USN_WAM] & Read_Bit_WAM);
}

/*-----------------------------------------------------------------------
Function name:	getStereoIndicator
Input:			N/A
Output:			STIN
Description:	Get Stereo Pilot and judge stereo output according to
				signal level configured in stereo blend control of weak
				signal processing function.
------------------------------------------------------------------------*/
enum STIN getStereoIndicator(void)
{
	readTunerRegister(ATomIC_I2C_Addr, Tuner_Read, ATomIC_I2C_LENGTH);
	if ((Tuner_Read[Read_STATUS] >> Read_Bit_FORCEMONO) & ON)	//Read STIN indicator
		if(getLevel() > StereoSeparation_Level)					//Judge Stereo by LEVEL
		 														//according to SNC setting
			return(STIN_STEREO);
	return(STIN_MONO);
}

/*-----------------------------------------------------------------------
Function name:	setFrequency
Input:			band,freqency,write_mode
Output:			N/A
Description:	Set tuning band and frequency
------------------------------------------------------------------------*/
void setFrequency (enum BAND band, uint32 freq, uint8 write_mode) 
{	uint8 freq_array[2];
	uint8 factor,setband;
	uint16 unit;
	switch (band)
	{
	case Band_LW:	
	case Band_MW:		factor = 1;
						unit = 1;
						setband = 0;
						break;
	case Band_FM:		factor = 20;
						unit = 1000;
						setband = 1;
						break;
	case Band_SW:		factor = 1;
						unit = 5;
						setband = 2;
						break;
	case Band_OIRT:		factor = 100;
						unit = 1000;
						setband = 3;
						break;
	default: break;
	}
	
	if (write_mode == ATomIC_I2C_WriteMode_End)
		{ 	freq_array[0] = 0x00;
			writeTunerRegister (ATomIC_I2C_Addr, ATomIC_I2C_SubType, write_mode, freq_array, 1);
		}
	else
	{
		freq_array[1] = (freq*factor/unit) & 0xff; 
		freq_array[0] = ((freq*factor/unit)>>8) | (setband << 5); 
    	writeTunerRegister (ATomIC_I2C_Addr, ATomIC_I2C_SubType, write_mode|ATomIC_I2C_FreqAdr, freq_array, 2);
	}
}

/*-----------------------------------------------------------------------
Function name:	setMono
Input:			ForceMono
Output:			N/A
Description:	Switch Forcemono on/off
------------------------------------------------------------------------*/
void setMono(uint8 ForceMono)
{	uint8 monoreg;
	if (ForceMono == OFF)
		monoreg = TEF6606_BYTE3H_DEFAULT;
	else if (ForceMono == ON)
		monoreg = TEF6606_BYTE3H_DEFAULT | 0X10;
	writeTunerRegister (ATomIC_I2C_Addr, ATomIC_I2C_SubType, ATomIC_I2C_WriteMode_None|ATomIC_I2C_MonoAdr, &monoreg, 1);
			
}

