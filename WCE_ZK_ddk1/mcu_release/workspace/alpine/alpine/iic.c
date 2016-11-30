#include "sfr_r82b.h"
#include "macro.h"
#include "iic.h"

void delay_us(uint us)
{
	for(;us>0;us--)
	{
		asm("NOP");
	}
}

#define WRITE 	0
#define READ	1

#define QDEL  delay_us(5)        // i2c quarter-bit delay
#define HDEL  delay_us(10)       // i2c half-bit delay

#define I2C_SDL_HI	SDA=1
#define I2C_SDL_LO	SDA=0
#define I2C_SCL_HI	SCL=1
#define I2C_SCL_LO	SCL=0

#define SDAIN	SDAD=0
#define SDAOUT	SDAD=1
#define SCLIN	SCLD=0
#define SCLOUT	SCLD=1

#define I2C_SCL_TOGGLE  HDEL; I2C_SCL_HI; HDEL; I2C_SCL_LO;
#define I2C_START       I2C_SDL_LO; QDEL; I2C_SCL_LO; 
#define I2C_STOP        HDEL; I2C_SCL_HI; QDEL; I2C_SDL_HI; HDEL;

uchar i2cPutbyte(u08 b)
{
	uchar i;
	uchar r = 0;
	for (i=8;i>0;i--)
	{
		delay_us(1);
		if ( b & (1<<(i-1)) )
			I2C_SDL_HI;
		else
			I2C_SDL_LO;         // address bit
		I2C_SCL_TOGGLE;     // clock HI, delay, then LO
	}

	I2C_SDL_HI;                 // leave SDL HI
	// added    
	//cbi(SDADDR, SDA);           // change direction to input on SDA line (may not be needed)
	SDAIN;
	HDEL;
	I2C_SCL_HI;                 // clock back up
	// 判断CLK线是否为高
	SCLIN;
	i = 100;
	while (i>1)
	{
		if (SCL == 1)
		{
			break;
		}
		i--;
		delay_us(5);
	}
	SCLOUT;
	I2C_SCL_HI;
	QDEL;
	r = SDA;					// get the ACK bit
	SDAOUT;
	QDEL;
	I2C_SCL_LO;                 // not really ??
	//sbi(SDADDR, SDA);           // change direction back to output
	return (r == 0);            // return ACK value
}


u08 i2cGetbyte(uchar last)
{
	uchar i;
	uchar c;
	u08 b = 0;

	//SDAH;                 // make sure pullups are ativated
	//cbi(SDADDR, SDA);           // change direction to input on SDA line (may not be needed)
	SDAIN;

	for(i=8;i>0;i--)
	{
		HDEL;
		I2C_SCL_HI;             // clock HI
		QDEL;
		c = SDA;  
		b <<= 1;
		if(c) b |= 1;
		QDEL;
		I2C_SCL_LO;             // clock LO
	}

	//sbi(SDADDR, SDA);           // change direction to output on SDA line
	delay_us(1);

	if (last)
	{
		I2C_SDL_HI;             // set NAK
		SDAOUT;
		I2C_SDL_HI; 
	}
	else
	{
		I2C_SDL_LO;             // set ACK
		SDAOUT;
		I2C_SDL_LO;
	}

	I2C_SCL_TOGGLE;             // clock pulse
	//I2C_SDL_HI;                 // leave with SDL HI

	return b;                   // return received byte
}

void I2CInit(void)
{
	//sbi( SDADDR, SDA);          // set SDA as output
	//sbi( SCLDDR, SCL);          // set SCL as output
	SDAOUT;
	SCLOUT;
	I2C_SDL_HI;                 // set I/O state and pull-ups
	I2C_SCL_HI;                 // set I/O state and pull-ups
}

//! Retrieve a byte sequence on the I2C bus
uchar i2cReceive(u08 device, u08 subAddr, u08 length, u08 *data)
{
	uchar j = length;
	u08 *p = data;

	I2C_START;                  // do start transition
	if(!i2cPutbyte(device))		// send DEVICE address
	{
		I2C_STOP;
		return FALSE;
	}        
	if(!i2cPutbyte(subAddr))        // and the subaddress
	{
		I2C_STOP;
		return FALSE;
	}
	// this time SCL  changed to low just now
	QDEL;
	I2C_SDL_HI;
	QDEL;						
	I2C_SCL_HI;                 // do a repeated START
	QDEL;
	I2C_START;                  // transition

	if(!i2cPutbyte(device | READ))  // resend DEVICE, with READ bit set
	{
		I2C_STOP;
		return FALSE;
	}

	// receive data bytes
	while (j--)
		*p++ = i2cGetbyte(j == 0);

	delay_us(1);
	I2C_SDL_LO;                 // clear data line and
	I2C_STOP;                   // send STOP transition
	return TRUE;
}

uchar i2cSend(u08 device, u08 subAddr, u08 length, u08 *data)
{
	uchar res = TRUE;
	I2C_START;                  // do start transition
	if(!i2cPutbyte(device))		// send DEVICE address
	{
		I2C_STOP;
		return FALSE;
	}        
	if(!i2cPutbyte(subAddr))	// and the subaddress
	{
		I2C_STOP;
		return FALSE;
	}       

	// send the data
	while (length--)
		i2cPutbyte(*data++);

	I2C_SDL_LO;                 // clear data line and
	I2C_STOP;                   // send STOP transition
	return res;
}

uchar i2cWrite(u08 device, u08 subAddr, u08 data)
{
	i2cSend(device, subAddr, 1, &data);
}

uchar i2cRead(u08 device, u08 subAddr, u08 *data)
{
	i2cReceive(device, subAddr, 1, data);
}