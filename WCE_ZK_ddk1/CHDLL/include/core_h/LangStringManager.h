#pragma once


#include "DllDefine.h"

typedef  map<string,wstring> LAN_TM_STRSTR;//言语类型， 值
typedef  map<string,LAN_TM_STRSTR> LAN_TM_M_STRSTR;
class CE_CONTROL_API LangStringManager
{
public:
	static LangStringManager* GetInstance();
	~LangStringManager();
	void  SetLangID(int nid);
	int   GetLangID(){return m_nLangId;}
	const wstring *  getString(const string & textId);
private:
	LangStringManager();
	static LangStringManager *m_pInstance;

	
	bool Init(const char * cstr);
	LAN_TM_M_STRSTR m_lanMapRes;
	int   m_nLangId;//当前选择的语言
	int  m_maxLangues;//一共有多少种语言

	

};

