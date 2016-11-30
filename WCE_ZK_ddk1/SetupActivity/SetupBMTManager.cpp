#include "StdAfx.h"
#include "SetupBMTManager.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "AVSet.h"
#include "StrDef.h"
const string bass_set  =		"bass_set";
const string midle_set  =		"midle_set";
const string treble_set  =		"treble_set";
const string sound_enhancement_set  =		"sound_enhancement_set";



SetupBMTManager *SetupBMTManager::m_pInstance = NULL;
SetupBMTManager::SetupBMTManager()
{

	if (sysConfig.sysParam.curSoundEnhancement>1)
	{
		sysConfig.sysParam.curSoundEnhancement = 0;
	}
	SetDataInArea(sysConfig.sysParam.curTreble,-7,7);
	SetDataInArea(sysConfig.sysParam.curBass,-7,7);
	SetDataInArea(sysConfig.sysParam.curMiddle,-7,7);

	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curBass);;
	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curMiddle);
	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curTreble);
	sysConfig.WriteConfig(&sysConfig.sysParam.curSoundEnhancement);
	AVSET::SetLoudness(sysConfig.sysParam.curSoundEnhancement);
	AVSET::SetBass(sysConfig.sysParam.curBass);
	AVSET::SetMiddle(sysConfig.sysParam.curMiddle);
	AVSET::SetTreble(sysConfig.sysParam.curTreble);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);

}

SetupBMTManager::~SetupBMTManager()
{

}

//ª÷∏¥≥ˆ≥ß…Ë÷√
LRESULT SetupBMTManager::RestoreDefault(DWORD param1, DWORD param2)
{

	sysConfig.sysParam.curBass = 0;
	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curBass);
	AVSET::SetBass(sysConfig.sysParam.curBass);

	sysConfig.sysParam.curMiddle = 0;
	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curMiddle);
	AVSET::SetMiddle(sysConfig.sysParam.curMiddle);


	sysConfig.sysParam.curTreble = 0;
	sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curTreble);
	AVSET::SetTreble(sysConfig.sysParam.curTreble);

	sysConfig.sysParam.curSoundEnhancement = false;
	sysConfig.WriteConfig(&sysConfig.sysParam.curSoundEnhancement);
	AVSET::SetLoudness(sysConfig.sysParam.curSoundEnhancement);	

	return 0;
}

SetupBMTManager* SetupBMTManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupBMTManager;
	}
	return m_pInstance;
}


bool SetupBMTManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{

	if (sound_enhancement_set == sline_name)
	{
		min_cursor = 0;
		max_cursor = 1;
		return true;//
	}
	min_cursor = -7;
	max_cursor = 7;

	return true;//
}

bool SetupBMTManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{

	if (sline_name == bass_set)
	{
		n_cursor = (int)sysConfig.sysParam.curBass;
	}
	else if (sline_name == midle_set)
	{
		n_cursor = (int)sysConfig.sysParam.curMiddle;

	}
	else if (sline_name == treble_set)
	{
		n_cursor = (int)sysConfig.sysParam.curTreble;

	}
	else if (sline_name == sound_enhancement_set)
	{
		n_cursor = (bool)sysConfig.sysParam.curSoundEnhancement;
		if ((bool)n_cursor)
		{
			sline_data = CHDLL_STR::C_ON ;
		}
		else
		{
			sline_data = CHDLL_STR::C_OFF;
		}
		AfxInvalidateRect(NULL);
		return true;
	}

	char text_v[16]; 
	sprintf(text_v,"%d",n_cursor);
	sline_data = text_v;

	AfxInvalidateRect(NULL);
	return true;
}



bool SetupBMTManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == bass_set)
	{
		sysConfig.sysParam.curBass = n_cursor;
		ReadSetup(sline_name,n_cursor,sline_data);
		sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curBass);
		AVSET::SetBass(sysConfig.sysParam.curBass);
	}
	else if (sline_name == midle_set)
	{
		sysConfig.sysParam.curMiddle = n_cursor;
		ReadSetup(sline_name,n_cursor,sline_data);
		sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curMiddle);
		AVSET::SetMiddle(sysConfig.sysParam.curMiddle);

	}
	else if (sline_name == treble_set)
	{
		sysConfig.sysParam.curTreble = n_cursor;
		ReadSetup(sline_name,n_cursor,sline_data);
		sysConfig.WriteConfig((BYTE *)&sysConfig.sysParam.curTreble);
		AVSET::SetTreble(sysConfig.sysParam.curTreble);
	}
	else if (sline_name == sound_enhancement_set)
	{
		sysConfig.sysParam.curSoundEnhancement = (bool)n_cursor;
		ReadSetup(sline_name,n_cursor,sline_data);
		sysConfig.WriteConfig(&sysConfig.sysParam.curSoundEnhancement);
		AVSET::SetLoudness(sysConfig.sysParam.curSoundEnhancement);	
	}
	else
	{
		ASSERT(0);
	}

	return true;
}


void SetupBMTManager::SetDataInArea( char &d, char min, char max )
{
	if (d<min ||  d > max)
	{
		d =(min+ max)/2;
	}
}
