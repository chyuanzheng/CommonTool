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

	// 设置 CPU LCD 控制器的亮度和对比度,可以影响所有显示画面,调节幅度和效果较差
	static void CPUSetBright(int bright);
	static void CPUSetContrast(int contrast);
	// 设置 屏幕驱动IC 的亮度和对比度,可以影响所有显示画面,调节效果好,仅仅在系统有驱动IC时才可以用
	static void LCDSetBright(int bright);
	static void LCDSetContast(int c);
	// 设置 模拟视频解码芯片 的亮度,对比度和颜色,仅仅影响dvd,aux,tv等视频画面,调节效果好
	static void VideoSetBrght(int bright);
	static void VideoSetContrast(int c);
	static void VideoSetColor(int color);

	static int SourceCheck();
	static void SelectCVBS();
	static void SelectYC();

	static void BackLight(unsigned char b);
	static void BackLightLevel(unsigned char l);
};