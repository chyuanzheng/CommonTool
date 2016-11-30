#pragma once


#include "DllDefine.h"

typedef  map<string,string> TM_STRSTR;
typedef  map<string,RECT> TM_STRRECT;
typedef  map<string,int> TM_STRINT;
class CE_CONTROL_API ResStringManager
{
public:
	static ResStringManager* GetInstance();
	~ResStringManager();
	const char * getString(const char * cstr);
	int  getInt(const char * cstr);
	bool getRect(const char * cstr,RECT & rect);

private:
	ResStringManager();
	bool Init(const char * cstr);

	void SetStrStr( TiXmlElement * element );
	void SetStrRect( TiXmlElement * element );
	void SetStrInt( TiXmlElement * element );
	TM_STRSTR  m_mapStrRes;
	TM_STRRECT m_mapRectRes;
	TM_STRINT  m_mapIntRes;
	static ResStringManager *m_pInstance;

};

