#pragma once

#include "CM52795.h"
#include "CTDA7313N.h"
#include "MCU89C662.h"
#include "SAA7111.h"
#include "PCA8591.h"
#include "SAA6588.h"
#include "NJW1110.h"
#include "FMS6502.h"
#include "NJW2753.h"
#include "BD3702.h"
#include "TDA7801.h"
#include "mcu.h"

extern MCU 	chip_mcu;
//extern CM52795		chip_52795;
//extern CTDA7313N	chip_tda7313;
extern SAA7111	CE_HardwareDll_API	chip_saa7111;
extern PCF8591		chip_pca8591;
extern SAA6588		chip_saa6588;
extern NJW1110		chip_njw1110;
extern FMS6502		chip_fms6502;
extern NJW2753		chip_njw2753;
extern BD3702		chip_bd3702;
extern TDA7801		chip_tda7801;

extern BOOL CE_HardwareDll_API VolumeSet(int vol);
extern BOOL VolumeSet2(int vol);
extern int VolumeGet();
extern void SetSoundField(int x, int y);
extern void SetSoundAffect(int affect);
extern void SetVideoAffect(int affect);

BOOL CE_HardwareDll_API DVDAVSelect();
BOOL CE_HardwareDll_API CEAVSelect();
BOOL CE_HardwareDll_API RadioASelect();
BOOL CE_HardwareDll_API PhoneASelect();
BOOL CE_HardwareDll_API AuxAVSelect();
BOOL CE_HardwareDll_API TVAVSelect();
BOOL AndroidASelect();
BOOL AudioToWince();
BOOL CE_HardwareDll_API IpodAVSelect();

BOOL DVDAudio();
BOOL CEAudio();
BOOL AuxAudio();
BOOL TVAudio();
BOOL IpodAudio();
BOOL BackFromPhone();
BOOL NaviAudio();
BOOL BackFromNavi();

BOOL SetTreble(int trebel);
BOOL SetMiddle(int midd);
BOOL SetBass(int bass);
BOOL SetLoudness(int lound);
BOOL SetSubwOn(int lound);

void CE_HardwareDll_API SetBright(int b);
void SetContrast(int c);
void SetSaturation(int s);
void SetHue(int h);

BOOL SystemMute(BOOL b);


extern int FullScreen(BOOL bFullScreen, BOOL bYC = 1, BOOL bForce = 0);
extern void	VideoScale(BOOL zoomin);
extern int CE_HardwareDll_API SourceCheck(int bReset = 1);
void WriteGamma(void);
void FullScreenPal(int b=0);
void FullScreenNtsl(int b=0);
void FullScreenSecam();
void ResetScreen();
void CVBS(int i);

extern void ToNormalScreen();
extern BOOL ToBackCamera();


void ScreenToAndroid();
void ScreenToWince();

//void AndroidKeyInit();
//void AndroidKeyHome();
//void AndroidKeyMenu();
//void AndroidKeyBack();