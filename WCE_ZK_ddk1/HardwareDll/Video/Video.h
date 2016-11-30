#pragma once

class Video
{
public:
	static void Init();
	static void ToDVD();
	static void ToIpod();
	static void ToAux();
	static void ToTV();
	static void ToCamera();

	// ���� CPU LCD �����������ȺͶԱȶ�,����Ӱ��������ʾ����,���ڷ��Ⱥ�Ч���ϲ�
	static void CPUSetBright(int bright);
	static void CPUSetContrast(int contrast);
	// ���� ��Ļ����IC �����ȺͶԱȶ�,����Ӱ��������ʾ����,����Ч����,������ϵͳ������ICʱ�ſ�����
	static void LCDSetBright(int bright);
	static void LCDSetContast(int c);
	// ���� ģ����Ƶ����оƬ ������,�ԱȶȺ���ɫ,����Ӱ��dvd,aux,tv����Ƶ����,����Ч����
	static void VideoSetBrght(int bright);
	static void VideoSetContrast(int c);
	static void VideoSetColor(int color);

	static int SourceCheck();
	static void SelectCVBS();
	static void SelectYC();

	static void BackLight(unsigned char b);
	static void BackLightLevel(unsigned char l);
};