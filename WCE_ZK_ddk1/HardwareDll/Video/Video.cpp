#include "stdafx.h"
#include "Video.h"
#include "../i2c/chip.h"

BYTE orgin_lcd_bright;
BYTE orgin_ldc_contrast;
void Video::Init()
{
	IICRead(0x50, 0x69, 1, &orgin_lcd_bright);
	IICRead(0x50, 0x68, 1, &orgin_ldc_contrast);
	chip_fms6502.GainControl(0xFF);
}

void Video::ToDVD()
{
	chip_saa7111.SelectYC();
	chip_fms6502.Output3Select(FMS6502::INPUT_6);
}

void Video::ToIpod()
{
	chip_saa7111.SelectCVBS();
	chip_fms6502.Output3Select(FMS6502::INPUT_2);
}

void Video::ToAux()
{
	chip_saa7111.SelectCVBS();
	chip_fms6502.Output3Select(FMS6502::INPUT_8);
}

void Video::ToTV()
{
	chip_saa7111.SelectCVBS();
	chip_fms6502.Output3Select(FMS6502::INPUT_3);
}

void Video::ToCamera()
{
	chip_saa7111.SelectCamera();
	chip_fms6502.Output3Select(FMS6502::INPUT_1);
}

void Video::CPUSetBright(int bright)
{
	BrightnessSet(bright);
}

void Video::CPUSetContrast(int contrast)
{
	ContrastSet(-contrast);
}

void Video::LCDSetBright(int bright)
{
	IICWrite(0x50, 0x69, orgin_lcd_bright+bright*4);
}

void Video::LCDSetContast(int c)
{
	IICWrite(0x50, 0x68, orgin_ldc_contrast+c*4);	
}

void Video::VideoSetBrght(int bright)
{
	chip_saa7111.BrightnessSet(bright);
}

void Video::VideoSetContrast(int c)
{
	chip_saa7111.ContrastSet(c);
}

void Video::VideoSetColor(int color)
{
	chip_saa7111.SetSaturation(color);
}

int Video::SourceCheck()
{
	return chip_saa7111.SourceCheck();
}

void Video::SelectCVBS()
{
	chip_saa7111.SelectCVBS();
}

void Video::SelectYC()
{
	chip_saa7111.SelectYC();
}

void Video::BackLight(BYTE b)
{
	::BackLight(b);
}

void Video::BackLightLevel(BYTE l)
{
	::BackLight(255-l*50);
}