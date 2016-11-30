#include "stdafx.h"
#include "lcdc_regfield.h"
#include "lcdc_ioctlcode.h"

#pragma once

class CDSSINTF
{
private:
	int m_TvoStatus;
public:
    CDSSINTF(void);
    ~CDSSINTF(void);

    int RequestDriver(unsigned int ioctlcode, PDRIVERPARAM pInParam, PDRIVERPARAM pOutParam);
    void ConfigController(unsigned int id, unsigned int func, PCTRCFGPARAM pParam);
    void ConfigImageChannel(unsigned int id, unsigned int ch, unsigned int mode, PIMGCFGPARAM pParam);
    void SetDemoType(unsigned int demotype);
    void SetDisplayMode(int function);
    void TvoutSetting(unsigned int channel, unsigned int tvtype, unsigned int demotype, PIMGCFGPARAM pImgCfgParam);
	void SetTVOState(int enable);
	int GetTVOState(void);

};
