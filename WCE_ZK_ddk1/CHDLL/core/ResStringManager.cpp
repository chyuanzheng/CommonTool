#include "StdAfx.h"
#include "ResStringManager.h"
#include "StrHelp.h"

ResStringManager *ResStringManager::m_pInstance = NULL;
ResStringManager::ResStringManager()
{
	bool b = Init("layout\\resouce\\strings.xml");
	ASSERT(b);
}

ResStringManager::~ResStringManager()
{

}

const char * ResStringManager::getString(const char * cstr)
{
	ASSERT(NULL != cstr);
	TM_STRSTR::iterator pos = m_mapStrRes.find(string(cstr));
	if (pos != m_mapStrRes.end())
	{
		return (*pos).second.c_str();
	}
	ASSERT(0);
	return NULL;
}


bool ResStringManager::getRect( const char * cstr,RECT & rect )
{
	ASSERT(NULL != cstr);
	TM_STRRECT::iterator pos = m_mapRectRes.find(string(cstr));
	if (pos != m_mapRectRes.end())
	{
		 rect =(*pos).second;
		 return true;
	}
	ASSERT(0);
	return false;
}


int ResStringManager::getInt( const char * cstr )
{
	ASSERT(NULL != cstr);
	TM_STRINT::iterator pos = m_mapIntRes.find(string(cstr));
	if (pos != m_mapIntRes.end())
	{
		return (*pos).second;
	}
	ASSERT(0);
	return 0;
}

bool ResStringManager::Init(const char * cstr)
{
	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);


	if (!xmlDoc->LoadFile(AfxAddWorkPathA(cstr) ))
	{
		ASSERT(0);
		return false;
	}

	TiXmlElement *root = xmlDoc->RootElement();
	if (strcmp(root->Value(), "resources") != 0)
	{
		return false;
	}

	TiXmlElement * element = root->FirstChildElement();



	while(element)
	{
		if (strcmp(element->Value(), "string") == 0)
		{
			SetStrStr(element);

		}
		else if (strcmp(element->Value(), "rect") == 0)
		{
			SetStrRect(element);
		}
		else if (strcmp(element->Value(), "integer") == 0)
		{
			SetStrInt(element);
		}

		element = element->NextSiblingElement();

	}

	return true;
}

ResStringManager* ResStringManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new ResStringManager;
	}
	return m_pInstance;
}

void ResStringManager::SetStrStr( TiXmlElement * element )
{
	string sname;
	string svalue;
	const char *c = element->Attribute("name");
	ASSERT(NULL!=c);
	sname = c;
	TiXmlNode*  strele = element->FirstChild();
	if (NULL != strele)
	{
		svalue = strele->Value();
		m_mapStrRes[sname] = svalue;
	}
}

void ResStringManager::SetStrRect( TiXmlElement * element )
{
	string sname;
	//const char * svalue;
	//RECT rect;
	const char *c = element->Attribute("name");
	ASSERT(NULL!=c);
	sname = c;
	TiXmlNode*  strele = element->FirstChild();
	if (NULL != strele)
	{
		m_mapRectRes[sname] = StrHelp::StringToRect( strele->Value() );

	}	
}

void ResStringManager::SetStrInt( TiXmlElement * element )
{
	string sname;
	const char *c = element->Attribute("name");
	ASSERT(NULL!=c);
	sname = c;
	TiXmlNode*  strele = element->FirstChild();
	if (NULL != strele)
	{
		m_mapIntRes[sname] = StrHelp::StrToInt( strele->Value() );

	}	
}

