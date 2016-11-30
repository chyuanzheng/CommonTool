#include "StdAfx.h"
#include "LangStringManager.h"
#include "StrHelp.h"
#include "VersionXml.h"

LangStringManager *LangStringManager::m_pInstance = NULL;

LangStringManager::LangStringManager()
{
	//SetLangID(0);
	m_nLangId = m_maxLangues =0 ;
	bool b = Init("layout\\setup\\lang.xml");
	ASSERT(b);
}

LangStringManager::~LangStringManager()
{

}


void LangStringManager::SetLangID( int nlan )
{
	if(nlan < 0 || nlan >= m_maxLangues)
	{
		nlan = 1;
	}
	m_nLangId=nlan;

	string slan = "L";
	slan += (48 + nlan);

	LAN_TM_M_STRSTR::iterator pos;
	for (pos = m_lanMapRes.begin(); pos != m_lanMapRes.end(); ++pos)
	{
		string textId = pos->first;
		ASSERT(pos->second.size()!=0);
		if ( pos->second.size()-1<= nlan)
		{
			pos->second[textId] = pos->second[string("L0")];//默认第一种语言
		}
		else
		{
			pos->second[textId] = pos->second[slan];
		}
		
	}
}

const wstring * LangStringManager::getString( const string & textId )
{
	LAN_TM_M_STRSTR::iterator pos =m_lanMapRes.find(textId);
	ASSERT(pos != m_lanMapRes.end());
	LAN_TM_STRSTR item = pos->second; 
	return &(item[textId]);//返回指针，所以只需要返回一次
}

bool LangStringManager::Init(const char * cstr)
{
	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);


	if (!xmlDoc->LoadFile(AfxAddWorkPathA(cstr) ))
	{
		ASSERT(0);
		return false;
	}

	TiXmlElement *root = xmlDoc->RootElement();
	if (strcmp(root->Value(), "languages") != 0)
	{
		return false;
	}

	TiXmlElement * element = root->FirstChildElement();

	while(element)
	{
		if (strcmp(element->Value(), "string") == 0)
		{

			LAN_TM_STRSTR tms;
			const char *sid = element->Attribute("id");
			ASSERT(sid!=NULL);
			string slang = "L";
			int index = 0;
			for (int i=0; i<7; i++)
			{
				index = i;

				if ( VersionXml::GetInstance()->GetLanguage() == VersionXml::LAN_ALL)
				{
					//n_cursor = 0;
					//sline_data = "All";
				}
				else if (VersionXml::GetInstance()->GetLanguage() == VersionXml::LAN_Simplified)
				{
					if (1==i)
					{
						continue;//去掉繁体
					}
					else if (i>1)
					{
						index--;
					}
					//n_cursor = 1;
					//sline_data = "Simplified";
				}
				else if (VersionXml::GetInstance()->GetLanguage() == VersionXml::LAN_Traditional)
				{
					if (2==i)
					{
						continue;//去掉简体
					}
					else if (i>2)
					{
						index--;
					}
					//n_cursor = 2;
					//sline_data = "Traditional";
				}
				else
				{
					ASSERT(0);
				}
				string slan = slang;
				slan += (48+i);
				const char * stext = element->Attribute(slan.c_str());
				if (stext == NULL)
				{
					break;
				}

				string slanIndex = slang;
				slanIndex += (48+index);
				tms[slanIndex]=StrHelp::StringToWString(string(stext));
			}
			if ( index > m_maxLangues)
			{
				m_maxLangues = index;
			}
			tms[sid] = L"";//在选择了语言后，这里放正真的值
			m_lanMapRes[sid] = tms;

		}
		element = element->NextSiblingElement();

	}
	ASSERT(m_maxLangues != 0);
	return true;
}

LangStringManager* LangStringManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new LangStringManager;
	}
	return m_pInstance;
}

