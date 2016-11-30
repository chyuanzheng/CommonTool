#pragma once
#include "Typedef.h"

extern U8 I2C1_WriteData(U8 SlaveAddr,U8 *BufferP,U8 Num);
extern U8 I2C1_ReadData(U8 SlaveAddr,U8 *BufferP,U8 Num);
void TimerDelayMs(int ms);