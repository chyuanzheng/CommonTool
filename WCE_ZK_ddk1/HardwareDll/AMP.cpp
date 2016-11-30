#include "stdafx.h"
#include "Amp.h"

CSerial AMP::serial;

//Э��ͷ	���� ���ݳ���  ���� 	У��� 	������
//�ֽ���	1	1	1	0-255	1	1
//
//Э��ͷ	�̶�0xFE
//����	0x01		��Դ����
//0x02		��������
//0x03		vol
//0x04		eq1
//0x05		eq2
//0x06		eq3
//0x07		eq4
//0x08		eq5
//0x09		eq6
//0x10		eq7
//0x11		eq8

//��Դ����:
//���ݳ���	1
//����		0	�رյ�Դ
//1	������Դ
//��������:
//���ݳ���	1
//����		0	������
//1	����
//vol:
//���ݳ���	1
//����		0-60
//
//eq:
//���ݳ���	1
//����		0-20
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