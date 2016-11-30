#pragma once


#include "DllDefine.h"

typedef  map<string,wstring> LAN_TM_STRSTR;//�������ͣ� ֵ
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
	int   m_nLangId;//��ǰѡ�������
	int  m_maxLangues;//һ���ж���������

	

};

