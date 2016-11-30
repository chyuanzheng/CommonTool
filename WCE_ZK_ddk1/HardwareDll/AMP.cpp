#include "stdafx.h"
#include "Amp.h"

CSerial AMP::serial;

//协议头	命令 数据长度  数据 	校验和 	结束符
//字节数	1	1	1	0-255	1	1
//
//协议头	固定0xFE
//命令	0x01		电源控制
//0x02		静音控制
//0x03		vol
//0x04		eq1
//0x05		eq2
//0x06		eq3
//0x07		eq4
//0x08		eq5
//0x09		eq6
//0x10		eq7
//0x11		eq8

//电源控制:
//数据长度	1
//数据		0	关闭电源
//1	开启电源
//静音控制:
//数据长度	1
//数据		0	不静音
//1	静音
//vol:
//数据长度	1
//数据		0-60
//
//eq:
//数据长度	1
//数据		0-20
void AMP::SetVol(int vol)
{
	SendCMD(0x3, vol);
}

void AMP::SetEQ(int eqnum, int eqdata)
{
	SendCMD(eqnum+4, eqdata);
}

void AMP::SetPower(BOOL bPower)
{
	SendCMD(0x1, bPower);
}

void AMP::SetMute(BOOL bMute)
{
	SendCMD(0x2, bMute);
}