#ifndef I2C_H
#define I2C_H

#define u08 uchar

uchar i2cWrite(u08 device, u08 subAddr, u08 data);
uchar i2cRead(u08 device, u08 subAddr, u08 *data);
void I2CInit(void);
void delay_us(uint us);

#endif