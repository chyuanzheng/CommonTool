#pragma once
//#include "../GxxLib/base.h"
#include "i2c/chip.h"
#include "INC/Param.h"
#include "CHardware.h"
//#include "LoadConfig.h"
#include "Ftun.h"
#include "Dtef6606.h"
#include "Hero/public.h"

#define FREQ(rf)	((rf)==0?0xFFFFFF:(rf) & 0xFFFFFF)
#define LV(rf)		((rf)&0xFF000000)


#define MAXNUM 60
class RadioHardware : public CHardware
{
protected:
	int bSearching;
	// 存放FM频道的数组
	UINT FMChanel[MAXNUM];
	// 存放AM频道的数组
	UINT AMChanel[MAXNUM];
	// 当前频道数组指针
	UINT *CurrentFreqTable;
	int curFMAM;
public:
	enum
	{
		FMMODE,
		AMMODE
	};
	virtual BOOL Init()
	{
		return 1;
	}
	virtual UINT GetCurFreq()
	{
		return 0;
	}
	virtual UINT GetMinFreq()
	{
		return 0;
	}
	virtual UINT GetMaxFreq()
	{
		return 0;
	}
	virtual UINT GetStep()
	{
		return 0;
	}
	UINT* GetCurFreqTable()
	{
		return CurrentFreqTable;
	}
	UINT* GetFMTable()
	{
		return FMChanel;
	}
	UINT* GetAMTable()
	{
		return AMChanel;
	}
	virtual void SwitchBand(BAND band)
	{

	}
	virtual BOOL AutoScan(BOOL updown, BOOL errorquit = 0)
	{
		return 0;
	}
	virtual void StopSearch()
	{

	}
	BOOL IsSearch()
	{
		return bSearching;
	}
	virtual void SetFreq(UINT rf)
	{

	}
	BOOL GetFMorAM()
	{
		return curFMAM;
	}
	virtual int	GetBand()
	{
		return 0;
	}
	virtual BOOL IsAfOn()
	{
		return 0;
	}
	virtual BOOL IsTaOn()
	{
		return 0;
	}
	virtual BOOL IsPtyOn()
	{
		return 0;
	}
	virtual void SetAfOn(BOOL)
	{

	}
	virtual void SetTaOn(BOOL)
	{

	}
	virtual void SetPtyOn(BOOL)
	{

	}
	virtual int GetCurPTY()
	{
		return 0;
	}
	virtual void SetCurPty(int)
	{

	}
	virtual void SetFMAM(int fmam)
	{

	}
	virtual BOOL StartSearch()
	{
		return 0;
	}
	virtual BOOL StartManualSearch(BOOL UpDown)
	{
		return 0;
	}
	virtual BOOL StartRDSSearch()
	{
		return 0;
	}
	virtual void SetStero(BOOL)
	{

	}
	virtual BOOL CheckFreq(int)
	{
		return 0;
	}
	virtual CStdString FormatFreq(int freq)
	{
		return _T("");
	}
	virtual void FreqAdd()
	{

	}
	virtual void FreqSub()
	{

	}
	virtual BOOL GetForceMono()
	{
		return 0;
	}
	virtual BOOL CheckStereo()
	{
		return 0;
	}
	virtual BYTE GetFsv()
	{
		return 0;
	}
	virtual void SetLoDx(BOOL bEnableLocal)
	{

	}
	int GetFreqPreset(UINT freq)
	{
		if (GetFMorAM() == FMMODE)
		{
			for (int i=0;i<18;i++)
			{
				if (FREQ(freq) == FREQ(GetCurFreqTable()[i]))
				{
					return i;
				}
			}
		}
		else
		{
			for (int i=0;i<12;i++)
			{
				if (FREQ(freq) == FREQ(GetCurFreqTable()[i]))
				{
					return i;
				}
			}
		}

		return -1;
	}
	int InsertFreq(int freq)
	{
		int i=0;
		if (FREQ(GetCurFreqTable()[0]) == 0 || 0xFFFFFF == FREQ(GetCurFreqTable()[0]))
		{
			GetCurFreqTable()[0] = freq;
			WriteBandTable(GetCurFreqTable(),GetFMorAM());
			return 0;
		}
		for (;i<MAXNUM;i++)
		{
			if (FREQ(GetCurFreqTable()[i]) == freq)
			{
				return i;
			}
		}
		for (i=0;i<MAXNUM-1;i++)
		{
			if (FREQ(GetCurFreqTable()[i]) < freq && FREQ(GetCurFreqTable()[i+1]) == 0)
			{
				GetCurFreqTable()[i+1] = freq;
				return i+1;
			}
			if (FREQ(GetCurFreqTable()[i]) == 0  || 0xFFFFFF == FREQ(GetCurFreqTable()[0]))
			{
				return i;
			}
			if (FREQ(GetCurFreqTable()[i]) < freq && FREQ(GetCurFreqTable()[i+1]) >freq)
			{
				break;
			}
		}
		for (int j=MAXNUM-1;j>i;j--)
		{
			if (j-1)
			{
				GetCurFreqTable()[j] = GetCurFreqTable()[j-1];
			}
		}
		GetCurFreqTable()[i+1] = freq;
		WriteBandTable(GetCurFreqTable(),GetFMorAM());
		return i+1;
	}
	int GetTotalCh()
	{
		int i=0;
		for (;i<MAXNUM;i++)
		{
			if (GetCurFreqTable()[i] == 0)
			{
				return i;
			}
		}
		return MAXNUM;
	}
};

#define WM_RADIOSEARCH	(WM_USER+83)
// 为了减少耦合,收音控制模块搜索时候向界面控制模块发送消息
// wParam = 当前频率
// lParam = 有台时为当前台号,无台时为-1,-2表示搜台结束
#define WM_RADIOSEARCHEND (WM_USER+84)
// 搜索结束


class TEF6606Hardware : public RadioHardware
{
	BAND curBand;
	UINT curFreq;
	BOOL bUpDown;
	BOOL Init()
	{
		Ftun_Init(Band_FM, FMmin);
		curBand = Band_FM;
		curFreq = FMmin;
		CurrentFreqTable = FMChanel;
		curFMAM = FMMODE;
		bSearching = 0;
		return 1;
	}
	UINT GetCurFreq()
	{
		return curFreq;
	}
	UINT GetMinFreq()
	{
		switch(curBand)				//setting up of tuning step and edge limit subject to different bands
		{
		case Band_LW:	
			return  LWmin;
			break;
		case Band_MW:	
			return MWmin;
			break;
		case Band_FM:	
			return FMmin;
			break;
		case Band_SW:	
			return SWmin;
			break;
		case Band_OIRT:	
			return OIRTmin;
			break;
		}
		return FMmin;
	}
	UINT GetMaxFreq()
	{
		switch(curBand)				//setting up of tuning step and edge limit subject to different bands
		{
		case Band_LW:	
			return  LWmax;
			break;
		case Band_MW:	
			return MWmax;
			break;
		case Band_FM:	
			return FMmax;
			break;
		case Band_SW:	
			return SWmax;
			break;
		case Band_OIRT:	
			return OIRTmax;
			break;
		}
		return FMmax;
	}
	UINT GetStep()
	{
		switch(curBand)				//setting up of tuning step and edge limit subject to different bands
		{
		case Band_LW:	
			return  LWSeekStep;
			break;
		case Band_MW:	
			return MWSeekStep;
			break;
		case Band_FM:	
			return FMSeekStep;
			break;
		case Band_SW:	
			return SWSeekStep;
			break;
		case Band_OIRT:	
			return OIRTSeekStep;
			break;
		}
		return FMSeekStep;
	}

	BOOL StartSearch()
	{
		if (bSearching == 0)
		{
			bSearching = 1;
			CreateThread(NULL, 0, AutoSearch, this, 0, NULL);
			return 1;
		}
		return 0;
	}
	BOOL StartManualSearch(BOOL UpDown)
	{
		bUpDown = UpDown;
		if (bSearching == 0)
		{
			bSearching = 1;
			CreateThread(NULL, 0, ManualSearch, this, 0, NULL);
			return 1;
		}
		return 0;
	}
	void StopSearch()
	{
		bSearching = 0;
		//SendMsg(WM_RADIOSEARCHEND, 0, 0);
	}

	void SwitchBand(BAND band)
	{
		curBand = (BAND)band;
		if (curBand == Band_FM)
		{
			curFMAM = FMMODE;
			CurrentFreqTable = FMChanel;
		}
		else
		{
			curFMAM = AMMODE;
			CurrentFreqTable = AMChanel;
		}
		Ftun_Init(curBand, GetMinFreq());
		//Ftun_TunetoFrequency(curBand, GetMinFreq(), ATomIC_I2C_WriteMode_Preset);
	}
	int GetBand()
	{
		return curBand;
	}
	void SetFreq(UINT rf)
	{
		curFreq = rf & 0xFFFFFF;
		if (curFreq < GetMinFreq())
		{
			curFreq = GetMinFreq();
		}
		if (curFreq > GetMaxFreq())
		{
			curFreq = GetMaxFreq();
		}
		Ftun_TunetoFrequency(curBand, curFreq, ATomIC_I2C_WriteMode_Preset);
	}
	CStdString FormatFreq(int freq)
	{
		freq &= 0xFFFFFF;
		CStdString strFreq;
		if (curBand == Band_FM)
		{
			int point = (freq%1000)/10;
#ifndef THAILAND			
			point /= 10;
#endif			
			if (freq == 0)
			{
				
			}
			else
			{
#ifdef THAILAND
				strFreq.Format(_T("%d.%02d"),freq/1000, point);
#else
				strFreq.Format(_T("%d.%d"),freq/1000, point);
#endif
				
			}
		}
		else
		{
			if (freq == 0)
			{

			}
			else
			{
				strFreq.Format(_T("%d"),freq);
			}	
		}
		return strFreq;
	}
	BOOL AutoScan(BOOL updown, BOOL errorquit = 0)
	{
		// 向某一个方向搜台,搜到台返回TRUE,搜台循环后仍然搜不到台返回-1
		UINT step,max,min;
		switch(curBand)				//setting up of tuning step and edge limit subject to different bands
		{
		case Band_LW:	step = LWSeekStep;
			max = LWmax;
			min = LWmin;
			break;
		case Band_MW:	step = MWSeekStep;
			max = MWmax;
			min = MWmin;
			break;
		case Band_FM:	step = FMSeekStep;
			max = FMmax;
			min = FMmin;
			break;
		case Band_SW:	step = SWSeekStep;
			max = SWmax;
			min = SWmin;
			break;
		case Band_OIRT:	step = OIRTSeekStep;
			max = OIRTmax;
			min = OIRTmin;
			break;
		}
		UINT freq = curFreq;
		SetFreq(curFreq);
		for (;;)
		{
			if (!IsSearch())
			{
				break;
			}
			if (updown)
			{
				curFreq += step;
			}
			else
			{
				curFreq -= step;
			}
			if (curFreq > max)
			{
				curFreq = min;
				if (errorquit)
				{
					curFreq = max;
					return -1;
				}
			}
			if (curFreq < min)
			{
				curFreq = max;
			}
			if (freq == curFreq)
			{
				break;
			}
			Ftun_TunetoFrequency(curBand,curFreq,ATomIC_I2C_WriteMode_Search);
			if (errorquit == 0)
			{
				SendMsg(WM_RADIOSEARCH, curFreq, -1);
			}
			if(curBand == Band_LW || curBand == Band_MW || curBand == Band_SW)
			{
				Sleep(SeekDelay_AM);
			}
			else
			{
				Sleep(SeekDelay_FM);
			}
			if(Ftun_CheckLevel(curBand) == TRUE)	// 有台
			{
				if (curBand == Band_FM || curBand == Band_OIRT) // FM
				{
					// FM检查信号强度
					if (getUSN() <=  SeekCondition_FM_USN && getWAM() <= SeekCondition_FM_WAM)
					{
						// wait IFC
						int delay = 200;
						while (getIFCounter(FALSE,curBand) == Read_Bit_IFCREADY)
						{
							if (delay-- == 0)
							{
								break;
							}
							Sleep(1);
						}
						if (getIFCounter(TRUE, curBand) <= SeekCondition_FM_Ifcount)// && getStereoIndicator() == STIN_STEREO)
						{
							return 1;
						}
					}
				}
				else	// AM
				{
					int delay = 32;
					while (getIFCounter(FALSE,curBand) == Read_Bit_IFCREADY)
					{
						if (delay-- == 0)
						{
							break;
						}
						Sleep(1);
					}
					//if (delay>0)
					{
						if (getIFCounter(TRUE, curBand) <= SeekCondition_AM_Ifcount)
						{
							return 1;
						}	
					}

				}
			}
			if (errorquit)
			{
				return 0;
			}
		}
		return -1;
	}

	// 自动搜台并保存
	static DWORD AutoSearch(LPVOID lpParam)
	{
		TEF6606Hardware *pRadCon = (TEF6606Hardware*) lpParam;
		pRadCon->curFreq = pRadCon->GetMinFreq();
		//memset(pRadCon->GetCurFreqTable(),0,sizeof(pRadCon->GetCurFreqTable()[0])*MAXNUM); // 清空频率表

		UINT freqTable[MAXNUM] = {0};
		for (int i=0;i<MAXNUM;i++)
		{
			if (pRadCon->GetFMorAM() == FMMODE)
			{
				freqTable[i] = 87000;
			}
			else
			{
				freqTable[i] = 522;
			}
		}
		BOOL bUseQuit = 0;
		int iii=0;
		for ( iii=0;iii<MAXNUM;iii++)
		{
			if (!pRadCon->IsSearch())
			{
				bUseQuit = 1;
				break;
			}
			BOOL bHave = pRadCon->AutoScan(TRUE, 1); //向频率高搜索
			pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, -1);
			if(bHave == 1) //判断是否有台
			{
				freqTable[iii] = pRadCon->curFreq | (getLevel()<<24);
				// 设置显示
				//SendMessage(pRadCon->hWnd, WM_RADIOSEARCH, pRadCon->curfreq, i);
				pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, iii);
			}
			else if (bHave == 0)
			{
				iii--;
			}
			else
			{
				break;
			}
			
		}
		if (pRadCon->GetFMorAM() == AMMODE)
		{
			// 根据信号强度排序,仅保存信号最好的12个台
			for (int i=0;i<MAXNUM;i++)
			{
				for (int j=0;j<MAXNUM-1-i;j++)
				{
					if (LV(freqTable[j]) < LV(freqTable[j+1]))
					{
						UINT temp = freqTable[j];
						freqTable[j] = freqTable[j+1];
						freqTable[j+1] = temp;
					}
				}
			}
			for (int i=12;i<MAXNUM;i++)
			{
				freqTable[i] = 0;
			}
		}
		else
		{
			// FMMODE
			// 根据信号强度排序,仅保存信号最好的18个台
			for (int i=0;i<MAXNUM;i++)
			{
				for (int j=0;j<MAXNUM-1-i;j++)
				{
					if (LV(freqTable[j]) < LV(freqTable[j+1]))
					{
						UINT temp = freqTable[j];
						freqTable[j] = freqTable[j+1];
						freqTable[j+1] = temp;
					}
				}
			}
			for (int i=18;i<MAXNUM;i++)
			{
				freqTable[i] = 0;
			}
			// 根据频率排序
			for (int i=0;i<18;i++)
			{
				for (int j=0;j<18-1-i;j++)
				{
					if (FREQ(freqTable[j]) > FREQ(freqTable[j+1]) && LV(freqTable[j+1])!=0)
					{
						UINT temp = freqTable[j];
						freqTable[j] = freqTable[j+1];
						freqTable[j+1] = temp;
					}
				}
			}
		}
		if (iii == 0 && pRadCon->CurrentFreqTable[0] > pRadCon->GetMinFreq() && pRadCon->CurrentFreqTable[0] < pRadCon->GetMaxFreq())
		{
			bUseQuit = 1;
		}
		if (bUseQuit)
		{
			pRadCon->StopSearch();
			pRadCon->SetFreq(pRadCon->GetCurFreqTable()[0]);
			// 设置显示
			pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, -2);
			for (int j=0;j<MAXNUM;j++)
			{
				if (pRadCon->GetCurFreqTable()[j] == 0)
				{
					pRadCon->SendMsg(WM_RADIOSEARCHEND, 0, j-1);
					break;
				}
			}
		}
		else
		{
			// 复制freqTable到当前频率表
			for (int j=0;j<MAXNUM;j++)
			{
				pRadCon->GetCurFreqTable()[j] = freqTable[j];
			}
			pRadCon->StopSearch();
			pRadCon->SetFreq(pRadCon->GetCurFreqTable()[0]);
			// 设置显示
			pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, -2);
			if (pRadCon->GetFMorAM() == AMMODE)
			{
				pRadCon->SendMsg(WM_RADIOSEARCHEND, 0, iii-1<12?iii-1:11);
			}
			else
			{
				pRadCon->SendMsg(WM_RADIOSEARCHEND, 0, iii-1<18?iii-1:17);
			}
			// 存储电台
			WriteBandTable(pRadCon->GetCurFreqTable(),pRadCon->GetFMorAM());
			WriteCurFreq(pRadCon->GetCurFreqTable()[0]);
		}

		return 0;
	}

	// 自动搜台并保存
	static DWORD ManualSearch(LPVOID lpParam)
	{
		TEF6606Hardware *pRadCon = (TEF6606Hardware*) lpParam;
		pRadCon->AutoScan(pRadCon->bUpDown, 0); 
		pRadCon->StopSearch();
		pRadCon->SendMsg(WM_RADIOSEARCHEND, 1, 0);
		return 0;
	}

	void FreqAdd()
	{
		curFreq += GetStep();
		if (curFreq > GetMaxFreq())
		{
			curFreq = GetMinFreq();
		}
		SetFreq(curFreq);
	}
	void FreqSub()
	{
		curFreq -= GetStep();
		if (curFreq < GetMinFreq())
		{
			curFreq = GetMaxFreq();
		}
		SetFreq(curFreq);
	}
	BYTE GetFsv()
	{
		return getLevel();
	}
};

#if 0

#define CHARGEPUMP	0xd1		//Reg0
#define PLL_L		0x0			//Reg1
#define PLL_H		0x0			//Reg2
#define	TV1			0x0			//Reg3
#define TV2			0x0			//Reg4
#define IFC1		0x1a		//Reg5
#define IFC2		0x8f		//Reg6		12.5KHz
#define AM_CTL		0x0			//Reg7
#define QUALITYISS	0x64		//Reg8		0x60 ISS_ON 0x61  ISS_OFF
#define QUALITYAC	0xf8		//Reg9		0xd0
#define QUALITYMP	0x08		//Reg10		0x20
#define QUALITYDEV	0x4a		//Reg11		0x4a
#define MUTE1		0xf3//0x80	//Reg12		0xff 0xf3 0x93	 0x97=53dBu
#define MUTE2		0xaf		//Reg13		0xaf
#define PLLREF		0x35		//Reg14
#define FMAGC		0x80		//Reg15		0x20
#define AMAGC		0xf8		//Reg16
#define DEM_ADJ		0xc0		//Reg17		0xc0
#define FM_LEVEL	0x33		//Reg18		0x34 (b4=0 smeter++ ,b4=1 smeter--;b3_0 + offset + ) 40dBu st>20dB
#define AM_LEVEL	0x2b		//*REG18
#define XTAL_FM		0xdf		//Reg19		23.5pF			IF1gain=18dB
#define XTAL_AM		0xd9		//*Reg19	IF1gain=9dB
#define TANK_ADJ	0x00		//Reg20
#define IQ_ADJ		0x07		//Reg21		0deg
#define AMIFNB		0x04		//Reg22
#define SCTRL		0x6e//0x7e  //Reg23		0x3e SSTOP=IFC&FSU>1.43V  +1=+0.27V	 0x6e >2.24V	 FM=0x5e=20dBu
//#define AM_SCTRL	0x7e		//*Reg23	AM=0xfe=23+15dBu
#define STD1		0x46		//Reg24		0x46
#define STD2		0x9e		//Reg25		0x5e 0xbe =75uS  ,0x9e=50uS	   7.5dB
#define STD3		0xe7		//Reg26
#define STD4		0x7f		//Reg27		0x7d
#define STD5		0x6f		//Reg28		0x7c 0x6c
#define STD6		0xdc		//Reg29		0xdc
#define STD7		0x15		//Reg30		Roll_off 7.8%
#define STD8		0x5d		//Reg31		0xdd   0x7d
#define STD9		0x04		//Reg32		0x04  0x74
#define TESTTU1		0x00		//Reg33
#define TESTTU2		0x00		//Reg34
#define TESTTU3		0x00		//Reg35
#define TESTTU4		0x00		//Reg36
#define TESTTU5		0x00		//Reg37
#define TESTSTD		0xfe		//Reg38
#define FMDEMSB		0xfe		//Reg39

#define FLAG		0xEA
#define EEP_FLAG	0x30
#define R_YEAR		6
#define R_MONTH		5
#define R_DATE		30
#define EEP_YEAR	0x31
#define EEP_MONTH	0x32
#define EEP_DATE	0x33
#define VER			1
#define EEP_VER		0x34

#define EEP_CHARGEPUMP	0x00		//Reg0
#define EEP_PLL_L		0x01		//Reg1
#define EEP_PLL_H		0x02		//Reg2
#define	EEP_TV1			0x03		//Reg3
#define EEP_TV2			0x04		//Reg4
#define EEP_IFC1		0x05		//Reg5
#define EEP_IFC2		0x06		//Reg6
#define EEP_AM_CTL		0x07		//Reg7
#define EEP_QUALITYISS	0x08		//Reg8
#define EEP_QUALITYAC	0x09		//Reg9
#define EEP_QUALITYMP	0x0a		//Reg10
#define EEP_QUALITYDEV	0x0b		//Reg11
#define EEP_MUTE1		0x0c		//Reg12
#define EEP_MUTE2		0x0d		//Reg13
#define EEP_PLLREF		0x0e		//Reg14
#define EEP_FMAGC		0x0f		//Reg15
#define EEP_AMAGC		0x10		//Reg16
#define EEP_DEM_ADJ		0x11		//Reg17
#define EEP_LEVEL		0x12		//Reg18
#define EEP_XTAL_FM		0x13		//Reg19
#define EEP_TANK_ADJ	0x14		//Reg20
#define EEP_IQ_ADJ		0x15		//Reg21
#define EEP_AMIFNB		0x16		//Reg22
#define EEP_SCTRL		0x17		//Reg23
#define EEP_STD1		0x18		//Reg24
#define EEP_STD2		0x19		//Reg25
#define EEP_STD3		0x1a		//Reg26
#define EEP_STD4		0x1b		//Reg27
#define EEP_STD5		0x1c		//Reg28
#define EEP_STD6		0x1d		//Reg29
#define EEP_STD7		0x1e		//Reg30
#define EEP_STD8		0x1f		//Reg31
#define EEP_STD9		0x20		//Reg32
#define EEP_TESTTU1		0x21		//Reg33
#define EEP_TESTTU2		0x22		//Reg34
#define EEP_TESTTU3		0x23		//Reg35
#define EEP_TESTTU4		0x24		//Reg36
#define EEP_TESTTU5		0x25		//Reg37
#define EEP_TESTSTD		0x26		//Reg38
#define EEP_FMDEMSB		0x27		//Reg39
/*
#define EEP_TV2_67		0x28 	//65_69
#define EEP_TV2_72		0x29 	//69_74
#define EEP_TV2_79		0x2a	//76--83
#define EEP_TV2_86		0x2b 	//83--90
#define EEP_TV2_92		0x2c	//87.5--98
#define EEP_TV2_103		0x2d	//98--108
*/
#define EEP_TV2_65		0x28
#define EEP_TV2_76		0x29
#define EEP_TV2_87		0x2a

#define EEP_IQ_65		0x2b
#define EEP_IQ_76		0x2c
#define EEP_IQ_87		0x2d

#define OIRT_STEP		3
#define JAPAN_STEP		3
#define EUROPE_STEP		0

#define EEP_AM_LEVEL	0x2e	
#define EEP_AM_XTAL		0x2f

#define HIGH	1
#define LOW		0	

// 频段列表
enum BAND 
{
	FMEU, 		  //87---108MHz	  50K
	FMA1,		  //87---108MHz	  200K
	FMA2,		  //87---108MHz	  100K
	FMJP,		  //76---90MHz	  50K
	FMRU,		  //65---74MHz   50K
	MWEU, 		  //522---1620KHz	9K
	MWA1,		  //530---1710KHz	10K
	MWA2,		  //530---1710KHz	10K
	MWJP,		  //522---1629KHz   9K
	MWRU,		  //522---1629KHz   9K
	LW,			  //153---281KHz	1K	
	SW0			 
};


// 区域频段列表
static const int BANDZONE[6][3] = 
{
	FMEU, MWEU, LW,
	FMA1, MWA1, LW,
	FMA2, MWA2, LW,
	FMJP, MWJP, LW,
	FMRU, MWRU, LW,
	FMA2, MWEU, LW,
};

class TDA7540Hardware : public RadioHardware
{
public:

public:
	BYTE eeprom[90]; //用于存放从24c02读出的数据
	// 收音机模块从地址
	static const BYTE TDA7540ADDR = 0xc4;
	// 24c02从地址
	static const BYTE EepromAddr = 0xA0;
#define MAXNUM 60
	// 存放FM频道的数组
	UINT FMChanel[MAXNUM];
	// 存放AM频道的数组
	UINT AMChanel[MAXNUM];

	// 当前频道数组指针
	UINT *CurrentFreqTable;


	// 频率值
	UINT minfreq,maxfreq,curfreq,inputfreq;

	BYTE buffer[14];

	// 
	BOOL bUpDown;

	// 当前是否自动搜索状态
	BOOL bSearching;

	// 当前频段
	int CurrentBand;
	int CurFMAM;

	// rds
	// TA switch
	BOOL TaOn;
	// AF switch
	BOOL AfOn;
	// PTY switch
	BOOL PtyOn;
	// RadioText switch
	BOOL RTOn;
	// 是否需要AF跳转
	BOOL bAFJump;
	// 当前PTY
	int  curPTY;
	//
	BOOL bRDSRecv;

	BOOL bForceMono;

	// 一些可变的参数 
	BYTE tank,tv2,tv2s,tv2_65,tv2_76,tv2_87;
	BYTE iq,iq_65,iq_76,iq_87,xtal_FM,xtal_AM;

	BYTE reff,step;
	char tv2_step;

	enum ZONE { USA, EURO, ASIA };
	// 私有方法
	BOOL InitParaTable(void)
	{
		if(!IICReadMcu(EepromAddr,0,0x34,eeprom))
		{
			RETAILMSG(1,(TEXT("RADIO : Read 24c02 failed\r\n")));
			goto Error;
		}
		if (FLAG != eeprom[EEP_FLAG])
		{
			RETAILMSG(1,(TEXT("RADIO : Read 24c02 failed2\r\n")));
			goto Error;
		}
		tank	= eeprom[EEP_TANK_ADJ];
		tv2_65	= eeprom[EEP_TV2_65];
		tv2_76	= eeprom[EEP_TV2_76];
		tv2_87	= eeprom[EEP_TV2_87];

		iq_65	= eeprom[EEP_IQ_65];	
		iq_76	= eeprom[EEP_IQ_76];
		iq_87	= eeprom[EEP_IQ_87];

		xtal_FM	= eeprom[EEP_XTAL_FM];
		xtal_AM	= eeprom[EEP_AM_XTAL];

		return TRUE;

Error:
		tank	= TANK_ADJ;
		tv2_65	= TV2;
		tv2_76	= TV2;
		tv2_87	= TV2;
		iq_65	= IQ_ADJ;	
		iq_76	= IQ_ADJ;
		iq_87	= IQ_ADJ;

		xtal_FM	= XTAL_FM;
		xtal_AM	= XTAL_AM;

		return FALSE;
	}

	BOOL Init()
	{
		AfOn = 0;
		TaOn = 0;
		PtyOn = 0;
		RTOn = 0;
		if (!InitParaTable() || !InitTda7540b())
		{
			RETAILMSG(1,(TEXT("Init radio failed\r\n")));
			return FALSE;
		}
		else
		{
			RETAILMSG(1,(TEXT("Init radio success\r\n")));
			return TRUE;
		}
	}
	// 切换频率段
	void SwitchBand(BAND band)
	{
		if (band > LW)
		{
			band = FMEU;
		}
		CurrentBand = band;
		if (band > FMRU)
		{
			CurrentFreqTable = AMChanel;
		}
		else
		{
			CurrentFreqTable = FMChanel;
		}
		SwitchBand0(band);
	}
	void SwitchBand0(BAND band)
	{
		if(band==FMRU)
		{	
			//65---74
			minfreq=65000;
			maxfreq=74000;
			tv2_step=OIRT_STEP;
			tv2s=tv2_65;
			iq=iq_65;
			reff=10;
			step=50;

			buffer[7]=0x0+0x30+0x4+0x02;	//FM+10K+180deg+div3
			buffer[2]=0x6f;//6.25K FM_10.7MHz
		}
		if(band==FMJP)
		{		
			//76---90
			minfreq=76000;
			maxfreq=90000;
			tv2_step=-JAPAN_STEP;
			tv2s=tv2_76;
			iq=iq_76;
			reff=25;
			step=50;

			buffer[7]=0x0+0x28+0x0+0x02;	//FM+25K+0deg+div3
		}
		if(band==FMEU)
		{		  
			//87---108
			minfreq=87000;
			maxfreq=108000;
			tv2_step=-EUROPE_STEP;
			tv2s=tv2_87;
			iq=iq_87;
			reff=50;
			step=50;

			buffer[7]=0x0+0x20+0x4+0x01;	//FM+50K+180deg+div2
		}	
		if(band==FMA1)
		{		  
			//87---108
			minfreq=87000;
			maxfreq=108000;
			tv2_step=-EUROPE_STEP;
			tv2s=tv2_87;
			iq=iq_87;
			reff=50;
			step=200;

			buffer[7]=0x0+0x20+0x4+0x01;	//FM+50K+180deg+div2
		}	
		if(band==FMA2)
		{		  
			//87---108
			minfreq=87000;
			maxfreq=108000;
			tv2_step=-EUROPE_STEP;
			tv2s=tv2_87;
			iq=iq_87;
			reff=50;
			step=100;

			buffer[7]=0x0+0x20+0x4+0x01;	//FM+50K+180deg+div2
		}	

		buffer[4]=FM_LEVEL;
		buffer[5]=xtal_FM;
		buffer[8]=0;		// div 10
		buffer[10]=MUTE1;
		////	buffer[12]=SCTRL;
		if(band==MWEU)
		{		  
			//522---1620

			minfreq=522;
			maxfreq=1620;
			reff=1;	//=10/10
			step=9;

			//	//	buffer[0]=0x45;//IFC1_addr
			//	//		buffer[1]=0x2e;
			//	//		buffer[2]=0x81;//AM_450KHz		2KHz
			buffer[4]=AM_LEVEL;
			buffer[5]=xtal_AM;
			buffer[7]=0x40+0x30+0x4+0x01;	//AM+10K+180deg+div2
			buffer[8]=0x0;		// div 10		
			buffer[10]&=0x7f;
			//	buffer[12]=AM_SCTRL;
		}
		if(band==MWJP || band==MWRU)
		{		  
			//522---1629

			minfreq=522;
			maxfreq=1629;
			reff=1;	//=10/10
			step=9;

			//	//	buffer[0]=0x45;//IFC1_addr
			//	//		buffer[1]=0x2e;
			//	//		buffer[2]=0x81;//AM_450KHz		2KHz
			buffer[4]=AM_LEVEL;
			buffer[5]=xtal_AM;
			buffer[7]=0x40+0x30+0x4+0x01;	//AM+10K+180deg+div2
			buffer[8]=0x0;		// div 10		
			buffer[10]&=0x7f;
			//	buffer[12]=AM_SCTRL;
		}
		if(band==MWEU)
		{		  
			//522---1629

			minfreq=522;
			maxfreq=1629;
			reff=1;	//=10/10
			step=9;

			//	//	buffer[0]=0x45;//IFC1_addr
			//	//		buffer[1]=0x2e;
			//	//		buffer[2]=0x81;//AM_450KHz		2KHz
			buffer[4]=AM_LEVEL;
			buffer[5]=xtal_AM;
			buffer[7]=0x40+0x30+0x4+0x01;	//AM+10K+180deg+div2
			buffer[8]=0x0;		// div 10		
			buffer[10]&=0x7f;
			//	buffer[12]=AM_SCTRL;
		}
		if(band==MWA1)
		{		  
			//530---1710

			minfreq=530;
			maxfreq=1710;
			reff=1;	//=10/10
			step=10;
			//	//	buffer[0]=0x45;//IFC1_addr
			//	//		buffer[1]=0x2e;
			//	//		buffer[2]=0x81;//AM_450KHz	2KHz
			buffer[4]=AM_LEVEL;
			buffer[5]=xtal_AM;
			buffer[7]=0x40+0x30+0x0+0x01;	//AM+10K+0deg+div2
			buffer[8]=0x0;		// div 10	
			buffer[10]&=0x7f;
			//	//	buffer[12]=AM_SCTRL;
		}
		if(band==MWA2)
		{		  
			//530---1710

			minfreq=530;
			maxfreq=1710;
			reff=1;	//=10/10
			step=10;
			//	//	buffer[0]=0x45;//IFC1_addr
			//	//		buffer[1]=0x2e;
			//	//		buffer[2]=0x81;//AM_450KHz	2KHz
			buffer[4]=AM_LEVEL;
			buffer[5]=xtal_AM;
			buffer[7]=0x40+0x30+0x0+0x01;	//AM+10K+0deg+div2
			buffer[8]=0x0;		// div 10	
			buffer[10]&=0x7f;
			//	//	buffer[12]=AM_SCTRL;
		}
		if(band==LW)
		{		  //153---281

			minfreq=153;
			maxfreq=281;
			reff=1;		//=10/10
			step=1;
			//	//	buffer[0]=0x45;//IFC1_addr
			//	//		buffer[1]=0x2e;
			//	//		buffer[2]=0x61;//AM_450KHz	 1KHz
			buffer[4]=AM_LEVEL;
			buffer[5]=xtal_AM;
			buffer[7]=0x40+0x30+0x0+0x01;	//AM+10K+0deg+div2
			buffer[8]=0;		// div 10
			buffer[10]&=0x7f;
			//	//	buffer[12]=AM_SCTRL;
		}
		if(band==SW0)
		{		  
			//1800---5170

			minfreq=1000;
			maxfreq=5170;
			reff=1;	//1.25=10/8
			step=10;
			//	//	buffer[0]=0x45;//IFC1_addr
			//	//		buffer[1]=0x2e;
			//	//		buffer[2]=0x81;//AM_450KHz	2KHz
			buffer[4]=AM_LEVEL;
			buffer[5]=xtal_AM;
			buffer[7]=0x40+0x30+0x0+0x01;	//AM+10K+0deg+div2
			buffer[8]=0x04;		// div 8	
			buffer[10]&=0x7f;
			//	//	buffer[12]=AM_SCTRL;
		}



		if (curfreq<minfreq || curfreq>maxfreq)
		{
			curfreq=minfreq;
		}
		//	buffer[0]=0x45;//IFC1_addr
		//	WriteI2c(TDA7540ADDR,&buffer[0],3);
		buffer[3]=0x40+18; //LEVEL
		WriteI2c(TDA7540ADDR,&buffer[3],3);
		buffer[6]=14;
		WriteI2c(TDA7540ADDR,&buffer[6],2);

		SetAMCTRL(buffer[8]);
		buffer[9]=12; //MUTE1
		WriteI2c(TDA7540ADDR,&buffer[9],2);
		//buffer[11]=23; //SCTRL
		//WriteI2c(TDA7540ADDR,&buffer[11],2);
		SetIQ();
	}
	// 自动搜台
	BOOL AutoScan(BOOL updown, BOOL errorquit = 0)
	{
		BOOL retval = FALSE;
		unsigned long int tempf;
		tempf=curfreq;
		OnOffIFC(1);
		for(;;)
		{
			if (bSearching == FALSE)
			{
				retval = FALSE;
				break;
			}
			if(updown)
			{
				curfreq+=step;
				if (curfreq>maxfreq)
				{
					curfreq = minfreq;
					if (errorquit)
					{
						retval = FALSE;
						break;
					}
				}
			}
			else
				curfreq-=step;
			SetFreq(curfreq);
			// 设置显示
			//SendMessage(hWnd, WM_RADIOSEARCH, curfreq, -1);
			SendMsg(WM_RADIOSEARCH, curfreq, -1);
			if(curfreq==tempf)
			{
				retval = FALSE;
				break;
			}
			//	DisFreq();
			Sleep(3);			 //delay 1mS
			if(step<11)	 		//AM delay 16mS
				Sleep(17);
			if(HasStableFreq()) //判断是否有台
			{
				retval = TRUE;
				break;
			}
			if (errorquit)
			{
				break;
			}

		}
		OnOffIFC(0);
		if (bSearching == 2)
		{
			bSearching = 0;
		}
		return retval;
	}

	// 自动搜台并保存
	static DWORD AutoSearch(LPVOID lpParam)
	{
		TDA7540Hardware *pRadCon = (TDA7540Hardware*) lpParam;
		pRadCon->curfreq = pRadCon->minfreq;
		memset(pRadCon->CurrentFreqTable,0,sizeof(pRadCon->CurrentFreqTable[0])*MAXNUM); // 清空频率表

		pRadCon->bSearching = 1;
		for (int i=0;i<MAXNUM;i++)
		{
			if (!pRadCon->bSearching)
			{
				break;
			}
			BOOL bHave = pRadCon->AutoScan(TRUE, 1); //向频率高搜索
			if(pRadCon->curfreq == pRadCon->minfreq)
			{
				break;
			}
			if(bHave) //判断是否有台
			{
				pRadCon->CurrentFreqTable[i] = pRadCon->curfreq;
				// 设置显示
				//SendMessage(pRadCon->hWnd, WM_RADIOSEARCH, pRadCon->curfreq, i);
				pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curfreq, i);
			}
			else
			{
				i--;
			}
		}
		pRadCon->StopSearch();
		pRadCon->SetFreq(pRadCon->CurrentFreqTable[0]);
		// 设置显示
		//SendMessage(pRadCon->hWnd, WM_RADIOSEARCH, pRadCon->curfreq, -2);
		pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curfreq, -2);
		// 存储电台
		WriteBandTable(pRadCon->CurrentFreqTable,pRadCon->CurFMAM);
		WriteCurChannel(0);
		WriteCurFreq(pRadCon->CurrentFreqTable[0]);

		return 0;
	}
	// 半自动搜台
	static DWORD ManualSearch(LPVOID lpParam)
	{
		TDA7540Hardware *pRadCon = (TDA7540Hardware*) lpParam;
		pRadCon->AutoScan(pRadCon->bUpDown);
		pRadCon->StopSearch();
		return 0;
	}

	// rds 自动搜索
	static DWORD RDSAutoSearching(LPVOID lpParam)
	{
		TDA7540Hardware *p = (TDA7540Hardware*) lpParam;
		int oldfreq = p->curfreq;
		if (p->PtyOn)
		{
			// 显示搜索pty
		}
		if (p->TaOn)
		{
			// 显示搜索TA
		}

		while (1)
		{
			if (!p->bSearching)
			{
				break;
			}
			BOOL bHave = p->AutoScan(TRUE,TRUE); //向频率高搜索
			if (oldfreq == p->curfreq)
			{
				break;
			}
			if(bHave) //判断是否有台
			{
				Sleep(100);
				if (chip_saa6588.bHasRDS || chip_mcu.RDSReady())
				{
					if (p->TaOn)
					{
						Sleep(800);
						if (chip_saa6588.ta)
						{
							break;
						}
					}
					if (p->PtyOn)
					{
						Sleep(500);
						if (chip_saa6588.ptyReadyFlag)
						{
							if (p->curPTY == chip_saa6588.pty)
							{
								break;
							}
						}
					}
				}

			}
		}
		p->TaOn = 0;
		p->PtyOn = 0;
		p->StopSearch();
		return 0;
	}

	BOOL StartSearch()
	{
		if (bSearching == 0)
		{
			bSearching = 1;
			CreateThread(NULL, 0, AutoSearch, this, 0, NULL);
			return 1;
		}
		return 0;
	}

	BOOL StartRDSSearch()
	{
		if (bSearching == 0)
		{
			bSearching = 1;
			CreateThread(NULL, 0, RDSAutoSearching, this, 0, NULL);
			return 1;
		}
		return 0;
	}

	BOOL StartManualSearch(BOOL UpDown)
	{
		bUpDown = UpDown;
		if (bSearching == 0)
		{
			bSearching = 1;
			CreateThread(NULL, 0, ManualSearch, this, 0, NULL);
			return 1;
		}
		return 0;
	}

	// 不显示的SetFreq
	void SetFreq(UINT rf)
	{
		if (!CreatecHardware::IsAuthOK())
		{
			return;
		}
		if(rf>maxfreq)
		{
			rf=minfreq;
		}
		if(rf<minfreq)
		{
			rf=maxfreq;
		}
		curfreq = rf;
		if(reff==25)
			rf=rf-10700;
		else
			rf=rf+10700;
		rf/=reff;
		rf-=32;
		buffer[0]=0x41;
		buffer[1]=rf;
		buffer[2]=rf>>8;
		WriteI2c(TDA7540ADDR,&buffer[0],3);	

		tv2=(rf-minfreq)/1000;
		tv2=tv2s+(tv2_step*tv2);
		SetTV2();
		chip_saa6588.Clear();
		SetStero(1);
	}

	BOOL InitTda7540b(void){
		buffer[0]=0x0;	//chargepump_addr
		buffer[1]=CHARGEPUMP;
		WriteI2c(TDA7540ADDR,&buffer[0],2);

		buffer[0]=0x40+3;	//TV1_addr
		buffer[1]=0;	//TV1=0		  Reg3
		buffer[2]=tv2;	//TV2;		  Reg4
		buffer[3]=IFC1;				//Reg5
		buffer[4]=IFC2;				//Reg6
		buffer[5]=AM_CTL;			//Reg7
		buffer[6]=QUALITYISS;		//Reg8
		buffer[7]=QUALITYAC;		//Reg9
		buffer[8]=QUALITYMP;		//Reg10
		buffer[9]=QUALITYDEV;		//Reg11
		buffer[10]=MUTE1	;		//Reg12
		buffer[11]=MUTE2	;		//Reg13
		buffer[12]=PLLREF	;		//Reg14
		buffer[13]=FMAGC		;	//Reg15
		if(WriteI2c(TDA7540ADDR,&buffer[0],14)==0)
		{
			return 0;
		}

		buffer[0]=0x40+0x10;
		buffer[1]=AMAGC		;		//Reg16
		buffer[2]=DEM_ADJ	;		//Reg17
		buffer[3]=FM_LEVEL	;		//Reg18
		buffer[4]=xtal_FM	;		//Reg19
		buffer[5]=tank		;		//Reg20
		buffer[6]=IQ_ADJ	;		//Reg21
		buffer[7]=AMIFNB	;		//Reg22
		buffer[8]=SCTRL		;		//Reg23
		WriteI2c(TDA7540ADDR,&buffer[0],9);


		buffer[0]=0x40+24;
		buffer[1]=STD1		;		//Reg24
		buffer[2]=STD2		;		//Reg25
		buffer[3]=STD3		;		//Reg26
		buffer[4]=STD4		;		//Reg27
		buffer[5]=STD5		;		//Reg28
		buffer[6]=STD6		;		//Reg29
		buffer[7]=STD7		;		//Reg30
		buffer[8]=STD8		;		//Reg31
		WriteI2c(TDA7540ADDR,&buffer[0],9);

		buffer[0]=0x40+0x20	;
		buffer[1]=STD9		;		//Reg32
		buffer[2]=TESTTU1	;		//Reg33
		buffer[3]=TESTTU2	;		//Reg34
		buffer[4]=TESTTU3	;		//Reg35
		buffer[5]=TESTTU4	;		//Reg36
		buffer[6]=TESTTU5	;		//Reg37
		buffer[7]=TESTSTD	;		//Reg38
		buffer[8]=FMDEMSB	;		//Reg39
		WriteI2c(TDA7540ADDR,&buffer[0],9);
		OnOffIFC(0);
		return 1;	
	}

	BOOL WriteI2c(BYTE SlaveAddr,BYTE *buff,int iLen)
	{
		BYTE databuf[15];
		databuf[0] = SlaveAddr;
		for (int i=0;i<iLen;i++)
		{
			databuf[i+1] = buff[i];
		}
		return IICWrite4(databuf,iLen+1);
	}
	void SetStero(BOOL on)
	{
		buffer[0] = 25;
		buffer[1] = 0x9a | (on<<2);
		WriteI2c(TDA7540ADDR,&buffer[0],2);
		Sleep(1); 
		bForceMono = !on;
	}
	BOOL GetForceMono()
	{
		return bForceMono;
	}
	void SetLoDx(BOOL bEnableLocal)
	{
		buffer[0] = 7;
		buffer[1] = AM_CTL | (bEnableLocal<<7);
		WriteI2c(TDA7540ADDR,&buffer[0],2);
		Sleep(1); 
	}
	void SetTV2(void){
		buffer[0]=4;	//tv2_addr
		buffer[1]=tv2;
		WriteI2c(TDA7540ADDR,&buffer[0],2);
		Sleep(1);  
	}

	void SetTANK(void){
		buffer[0]=20;	//tank_addr
		buffer[1]=tank;
		WriteI2c(TDA7540ADDR,&buffer[0],2);
		Sleep(1);  
	}

	void SetAMCTRL(unsigned char ctr){
		buffer[0]=7;//AM_CTL_addr
		buffer[1]=ctr;
		WriteI2c(TDA7540ADDR,&buffer[0],2);
		Sleep(1);
	}

	void SetIQ(void){
		buffer[0]=21;
		buffer[1]=iq;
		WriteI2c(TDA7540ADDR,&buffer[0],2);
		Sleep(1);  
	}

	BOOL CheckStereo(void){	//=0 mono =1 stereo
		unsigned char daa;
		IICRead4(TDA7540ADDR,1,&daa);
		if((daa&0x04)&&(daa!=255))
			return 1;
		return 0;
	}
	void CloseISS(BOOL cl){
		buffer[0]=8;
		buffer[1]=QUALITYISS;
		if(cl)
			buffer[1]|=1;
		WriteI2c(TDA7540ADDR,&buffer[0],2);
	}
	void OnOffIFC(BOOL onoff){
		buffer[0]=0x45;
		if(step>10){  //FM
			buffer[1]=IFC1;
			buffer[2]=IFC2;
		}
		else{		  //AM
			buffer[1]=0x2e;
			buffer[2]=0x61;//AM_450KHz	 1KHz
		}
		if(onoff==0){
			buffer[1]&=~0x48;  //off IFC
		}
		buffer[0]=0x45;//IFC1_addr
		WriteI2c(TDA7540ADDR,&buffer[0],3);
	}
	BOOL HasStableFreq(void)
	{
		CStdString strFreq;
		CStdString strError;
		strFreq.Format(_T("freq = %d "),curfreq);
		BYTE fsv = GetFsv();
		int sstopcount = 0;

		if (fsv > 240)
		{
			for (int i=0;i<10;i++)
			{
			}
			if (sstopcount>2)
			{
				strError.Format(L"OUT1 sstopcount = %d\r\n",sstopcount);
				//STLOG_WRITE(strFreq+strError);
				return FALSE;
			}
			strError.Format(L"IN1 fsv = %d\r\n", fsv);
			//STLOG_WRITE(strFreq+strError);
			return TRUE;
		}

		if (!chip_mcu.ReadSStop())
		{
			return FALSE;
		}

		sstopcount = 0;
		for (int i=0;i<100;i++)
		{
			if (chip_mcu.ReadSStop() == 0)
			{
				Sleep(0);
				sstopcount++;
			}
		}
		if (sstopcount > 5)
		{
			strError.Format(L"OUT2 sstopcount = %d\r\n",sstopcount);
			//STLOG_WRITE(strFreq+strError);
			return FALSE;
		}
		return TRUE;
	}
	CStdString FormatFreq(int freq)
	{
		int band = CurrentBand;
		CStdString strFreq;
		if (freq<minfreq)
		{
			freq = minfreq;
		}
		if (freq>maxfreq)
		{
			freq=maxfreq;
		}
		if (band <= FMRU)
		{
			int point = (freq%1000)/10;
			if (band == FMEU || band == FMJP)
			{
				strFreq.Format(_T("%d.%02d"),freq/1000, point);
			}
			else
			{
				point /= 10;
				strFreq.Format(_T("%d.%d"),freq/1000, point);
			}
		}
		if (band >= MWEU)
		{
			strFreq.Format(_T("%d"),freq);
		}
		return strFreq;
	}

	BYTE GetFsv()
	{
		BYTE fsv = 0;
		IICRead4(0xd2,0x4,1,&fsv);
		return fsv;
	}
	void StopSearch()
	{
		bSearching = 0;
		SendMsg(WM_RADIOSEARCHEND, 0, 0);
	}
	BOOL IsSearch()
	{
		return bSearching;
	}
	int GetCurrentFreq()
	{
		return curfreq;
	}
	void FreqAdd()
	{
		curfreq += step;
		SetFreq(curfreq);
	}
	void FreqSub()
	{
		curfreq -= step;
		SetFreq(curfreq);
	}
	BOOL CheckFreq(int freq)
	{
		if (freq < minfreq)
		{
			return FALSE;
		}
		if (freq > maxfreq)
		{
			return FALSE;
		}
		return TRUE;
	}
};
#endif


class TEF6638Hardware : public RadioHardware
{
	int curBand;
	UINT curFreq;
	BOOL bUpDown;
	BOOL Init()
	{
		curBand = Band_FM;
		curFreq = FMmin;
		CurrentFreqTable = FMChanel;
		curFMAM = FMMODE;
		bSearching = 0;
		return 1;
	}
	UINT GetCurFreq()
	{
		return curFreq;
	}
	UINT GetMinFreq()
	{
		switch(curBand)				//setting up of tuning step and edge limit subject to different bands
		{
		case AMMODE:	
			return 522;
			break;
		case FMMODE:	
			return 87500;
			break;
		}
		return FMmin;
	}
	UINT GetMaxFreq()
	{
		switch(curBand)				//setting up of tuning step and edge limit subject to different bands
		{
		case AMMODE:	
			return MWmax;
			break;
		case FMMODE:	
			return FMmax;
			break;
		}
		return FMmax;
	}
	UINT GetStep()
	{
		switch(curBand)				//setting up of tuning step and edge limit subject to different bands
		{
		case AMMODE:	
			return MWSeekStep;
			break;
		case FMMODE:	
			return FMSeekStep;
			break;
		}
		return FMSeekStep;
	}

	BOOL StartSearch()
	{
		if (bSearching == 0)
		{
			bSearching = 1;
			CreateThread(NULL, 0, AutoSearch, this, 0, NULL);
			return 1;
		}
		return 0;
	}
	BOOL StartManualSearch(BOOL UpDown)
	{
		bUpDown = UpDown;
		if (bSearching == 0)
		{
			bSearching = 1;
			CreateThread(NULL, 0, ManualSearch, this, 0, NULL);
			return 1;
		}
		return 0;
	}
	void StopSearch()
	{
		bSearching = 0;
		//SendMsg(WM_RADIOSEARCHEND, 0, 0);
	}

	void SwitchBand(BAND band)
	{
		curBand = (int)band;
		BYTE band6638 = 0;
		if (curBand == FMMODE)
		{
			curFMAM = FMMODE;
			CurrentFreqTable = FMChanel;
			band6638 = FM1_BAND;
		}
		else
		{
			curFMAM = AMMODE;
			CurrentFreqTable = AMChanel;
			band6638 = MW_BAND;
		}
		
		Radio_SetBand(band6638);
	}
	int GetBand()
	{
		return curBand;
	}
	void SetFreq(UINT rf)
	{
		curFreq = rf & 0xFFFFFF;
		if (curFreq < GetMinFreq())
		{
			curFreq = GetMinFreq();
		}
		if (curFreq > GetMaxFreq())
		{
			curFreq = GetMaxFreq();
		}
		if (GetFMorAM() == FMMODE)
		{
			Radio_SetFreq(Radio_PRESETMODE, FM1_BAND, curFreq/10);
		}
		else
		{
			Radio_SetFreq(Radio_PRESETMODE, MW_BAND, curFreq);
		}
		//Ftun_TunetoFrequency(curBand, curFreq, ATomIC_I2C_WriteMode_Preset);
	}
	CStdString FormatFreq(int freq)
	{
		freq &= 0xFFFFFF;
		CStdString strFreq;
		if (curBand == Band_FM)
		{
			int point = (freq%1000)/10;
#ifndef THAILAND			
			point /= 10;
#endif			
			if (freq == 0)
			{

			}
			else
			{
#ifdef THAILAND
				strFreq.Format(_T("%d.%02d"),freq/1000, point);
#else
				strFreq.Format(_T("%d.%d"),freq/1000, point);
#endif

			}
		}
		else
		{
			if (freq == 0)
			{

			}
			else
			{
				strFreq.Format(_T("%d"),freq);
			}	
		}
		return strFreq;
	}
	BOOL AutoScan(BOOL updown, BOOL errorquit = 0)
	{
		// 向某一个方向搜台,搜到台返回TRUE,搜台循环后仍然搜不到台返回-1
		UINT step,max,min;
		switch(curFMAM)				//setting up of tuning step and edge limit subject to different bands
		{
		case AMMODE:	step = MWSeekStep;
			max = MWmax;
			min = 522;
			break;
		case FMMODE:	step = FMSeekStep;
			max = FMmax;
			min = 87500;
			break;
		}
		UINT freq = curFreq;
		for (;;)
		{
			if (!IsSearch())
			{
				break;
			}
			if (updown)
			{
				curFreq += step;
			}
			else
			{
				curFreq -= step;
			}
			if (curFreq > max)
			{
				curFreq = min;
				if (errorquit)
				{
					curFreq = max;
					return -1;
				}
			}
			if (curFreq < min)
			{
				curFreq = max;
			}
			if (freq == curFreq)
			{
				break;
			}
			if (GetFMorAM() == FMMODE)
			{
				Radio_SetFreq(Radio_SEARCHMODE, FM1_BAND, curFreq/10);
			}
			else
			{
				Radio_SetFreq(Radio_SEARCHMODE, MW_BAND, curFreq);
			}	
			
			//Ftun_TunetoFrequency(curBand,curFreq,ATomIC_I2C_WriteMode_Search);
			if (errorquit == 0)
			{
				SendMsg(WM_RADIOSEARCH, curFreq, -1);
			}
			if(curFMAM == AMMODE)
			{
				Sleep(50);
			}
			else
			{
				Sleep(SeekDelay_FM);
			}
			//if(Ftun_CheckLevel(curBand) == TRUE)	// 有台
			if (Radio_HasStation())
			{
				if (curFMAM == FMMODE)
				{
					if (curFreq == min || curFreq == max)
					{
						if (CheckStereo())
						{
							return 1;
						}
						else
						{
							continue;
						}
					}
				}
				return 1;
			}
			if (errorquit)
			{
				return 0;
			}
		}
		return -1;
	}

	// 自动搜台并保存
	static DWORD AutoSearch(LPVOID lpParam)
	{
		TEF6638Hardware *pRadCon = (TEF6638Hardware*) lpParam;
		pRadCon->curFreq = pRadCon->GetMinFreq();
		//memset(pRadCon->GetCurFreqTable(),0,sizeof(pRadCon->GetCurFreqTable()[0])*MAXNUM); // 清空频率表

		UINT freqTable[MAXNUM] = {0};
		for (int i=0;i<MAXNUM;i++)
		{
			if (pRadCon->GetFMorAM() == FMMODE)
			{
				freqTable[i] = 0;
			}
			else
			{
				freqTable[i] = 0;
			}
		}
		BOOL bUseQuit = 0;
		int iii=0;
		for ( iii=0;iii<MAXNUM;iii++)
		{
			if (!pRadCon->IsSearch())
			{
				bUseQuit = 1;
				break;
			}
			BOOL bHave = pRadCon->AutoScan(TRUE, 1); //向频率高搜索
			pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, -1);
			if(bHave == 1) //判断是否有台
			{
				freqTable[iii] = pRadCon->curFreq | (pRadCon->GetFsv()<<24);
				// 设置显示
				//SendMessage(pRadCon->hWnd, WM_RADIOSEARCH, pRadCon->curfreq, i);
				pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, iii);
			}
			else if (bHave == 0)
			{
				iii--;
			}
			else
			{
				break;
			}

		}
		if (pRadCon->GetFMorAM() == AMMODE)
		{
			// 根据信号强度排序,仅保存信号最好的12个台
			for (int i=0;i<MAXNUM;i++)
			{
				for (int j=0;j<MAXNUM-1-i;j++)
				{
					if (LV(freqTable[j]) < LV(freqTable[j+1]))
					{
						UINT temp = freqTable[j];
						freqTable[j] = freqTable[j+1];
						freqTable[j+1] = temp;
					}
				}
			}
			for (int i=12;i<MAXNUM;i++)
			{
				freqTable[i] = 0;
			}
			// 根据频率排序
			for (int i=0;i<12;i++)
			{
				for (int j=0;j<12-1-i;j++)
				{
					if (FREQ(freqTable[j]) > FREQ(freqTable[j+1]) && LV(freqTable[j+1])!=0)
					{
						UINT temp = freqTable[j];
						freqTable[j] = freqTable[j+1];
						freqTable[j+1] = temp;
					}
				}
			}
		}
		else
		{
			// FMMODE
			// 根据信号强度排序,仅保存信号最好的18个台
			for (int i=0;i<MAXNUM;i++)
			{
				for (int j=0;j<MAXNUM-1-i;j++)
				{
					if (LV(freqTable[j]) < LV(freqTable[j+1]))
					{
						UINT temp = freqTable[j];
						freqTable[j] = freqTable[j+1];
						freqTable[j+1] = temp;
					}
				}
			}
			for (int i=18;i<MAXNUM;i++)
			{
				freqTable[i] = 0;
			}
			// 根据频率排序
			for (int i=0;i<18;i++)
			{
				for (int j=0;j<18-1-i;j++)
				{
					if (FREQ(freqTable[j]) > FREQ(freqTable[j+1]) && LV(freqTable[j+1])!=0)
					{
						UINT temp = freqTable[j];
						freqTable[j] = freqTable[j+1];
						freqTable[j+1] = temp;
					}
				}
			}
		}
		if (iii == 0 && pRadCon->CurrentFreqTable[0] > pRadCon->GetMinFreq() && pRadCon->CurrentFreqTable[0] < pRadCon->GetMaxFreq())
		{
			bUseQuit = 1;
		}
		if (bUseQuit)
		{
			pRadCon->StopSearch();
			pRadCon->SetFreq(pRadCon->GetCurFreqTable()[0]);
			// 设置显示
			pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, -2);
			for (int j=0;j<MAXNUM;j++)
			{
				if (pRadCon->GetCurFreqTable()[j] == 0)
				{
					pRadCon->SendMsg(WM_RADIOSEARCHEND, 0, j-1);
					break;
				}
			}
		}
		else
		{
			// 复制freqTable到当前频率表
			for (int j=0;j<MAXNUM;j++)
			{
				pRadCon->GetCurFreqTable()[j] = freqTable[j];
			}
			pRadCon->StopSearch();
			pRadCon->SetFreq(pRadCon->GetCurFreqTable()[0]);
			// 设置显示
			pRadCon->SendMsg(WM_RADIOSEARCH, pRadCon->curFreq, -2);
			if (pRadCon->GetFMorAM() == AMMODE)
			{
				pRadCon->SendMsg(WM_RADIOSEARCHEND, 0, iii-1<12?iii-1:11);
			}
			else
			{
				pRadCon->SendMsg(WM_RADIOSEARCHEND, 0, iii-1<18?iii-1:17);
			}
			// 存储电台
			WriteBandTable(pRadCon->GetCurFreqTable(),pRadCon->GetFMorAM());
			WriteCurFreq(pRadCon->GetCurFreqTable()[0]);
		}

		return 0;
	}

	// 自动搜台并保存
	static DWORD ManualSearch(LPVOID lpParam)
	{
		TEF6638Hardware *pRadCon = (TEF6638Hardware*) lpParam;

		pRadCon->AutoScan(pRadCon->bUpDown, 0); 
		pRadCon->StopSearch();
		pRadCon->SendMsg(WM_RADIOSEARCHEND, 1, 0);
		return 0;
	}

	void FreqAdd()
	{
		curFreq += GetStep();
		if (curFreq > GetMaxFreq())
		{
			curFreq = GetMinFreq();
		}
		SetFreq(curFreq);
	}
	void FreqSub()
	{
		curFreq -= GetStep();
		if (curFreq < GetMinFreq())
		{
			curFreq = GetMaxFreq();
		}
		SetFreq(curFreq);
	}
	BYTE GetFsv()
	{
		return RadioDrv_GetData(Radio_LEVEL);
		return 0;
	}
	BOOL CheckStereo()
	{
		return RadioDrv_CheckStereoIndicator();
	}
};