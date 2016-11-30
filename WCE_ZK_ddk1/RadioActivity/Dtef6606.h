/***************************************************************************************
* (C) Copyright NXP semiconductor, All rights reserved
* FILE NAME:	<Dtef6606.h>
* VERSION:		<1.0>
* DESCRIPTION:	Header file for Dtef6606.c
* DOCUMENT REF: <References to specification or other documents related to this module>
* NOTES:		<File notes>
***************************************************************************************/

#ifndef _DTEF6606_H
#define _DTEF6606_H

/*-------------------------------------------------
define for I2C info
--------------------------------------------------*/
#define ATomIC_I2C_LENGTH 5
#define ATomIC_I2C_Addr 0xC0
#define ATomIC_I2C_SubType 1
#define ATomIC_I2C_FreqAdr 0x00
#define ATomIC_I2C_MonoAdr 0x03
#define ATomIC_I2C_SetupAdr 0x02
#define ATomIC_I2C_WriteMode_None 0x00
#define ATomIC_I2C_WriteMode_Preset 0x20
#define ATomIC_I2C_WriteMode_Search 0x40
#define ATomIC_I2C_WriteMode_End 0xe0

/*-------------------------------------------------
define for I2C Read subaddress and mask
--------------------------------------------------*/
#define Read_STATUS 0
#define Read_LEVEL 1
#define Read_USN_WAM 2
#define Read_IFCOUNT 3
#define Read_ID 4
#define Read_Bit_IFCOUNT 0x1F
#define Read_Bit_IFCREADY 0xc0
#define Read_Bit_USN 0xF0
#define Read_Bit_WAM 0x0F
#define Read_Bit_FORCEMONO 0x04


#define TEF6606_BYTE3H_DEFAULT 80

/*---------------------------------------------------
Function declaration in Dtef6606.c
----------------------------------------------------*/
uint8 readTunerRegister(uint8 i2c_adr, uint8 *read_buffer, uint32 num);
uint8 writeTunerRegister(uint8 i2c_adr, uint8 i2c_subtype, uint32 sub_adr, uint8 *write_buffer, uint32 num);
extern uint8 getLevel(void);
extern uint8 getIFCounter(uint8 IFCReady,uint8 band);
extern uint8 getUSN(void);
extern uint8 getWAM(void);
extern enum STIN getStereoIndicator(void);
extern void setFrequency (enum BAND band, uint32 freq, uint8 write_mode);
extern void setMono(uint8 ForceMono);

#endif