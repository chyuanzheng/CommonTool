#include "StdAfx.h"
#include "VersionXml.h"
VersionXml *VersionXml::m_pInstance = NULL;

#define  XML_PATH    "VersionDefine\\version.xml"

#define  VERSION    "version"
VersionXml::VersionXml()
{
	Init();
}
VersionXml* VersionXml::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new VersionXml;
	}
	return m_pInstance;
}

bool VersionXml::Init()
{
	m_opt_language = LAN_Simplified;
	m_opt_Navi_SoftWare = Navi_GaoDe;
	m_opt_Navi_MixSound = Navi_Mix_Removed;
	m_bt_Module = BT_Module_Removed;
	m_bsf_Module = Navi_BSF_Removed;


	m_strXmlPath  = AfxAddWorkPathA(XML_PATH);

	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	bool ret = xmlDoc->LoadFile(m_strXmlPath.c_str());
	if (!ret)
	{
		ASSERT(0);
		return false;
	}

	TiXmlElement *ele = xmlDoc->RootElement();
	const CHAR * ctrname = NULL;
	while(ele)
	{
		ctrname = ele->Value();

		if (ctrname)
		{
			if (0 == strcmp(ctrname,"languages_set"))
			{
				int data =0;
				ele->Attribute(VERSION, &data);
				if (data>=0 &&  data<=LAN_Simplified )
				{
					m_opt_language  = (Option_Language)data;
				}
				else
				{
					ret = false;
				}
			}

			else if (0 == strcmp(ctrname,"navi_option_set"))
			{
				int data =0;
				ele->Attribute(VERSION, &data);
				if (data>=0 &&  data<=Navi_GaoDe )
				{
					m_opt_Navi_SoftWare  = (Option_NaviSoftWare)data;
				}
				else
				{
					ret = false;
				}
				const char *str = NULL;
				str = ele->Attribute("NaviKing");
				if (str) m_strNaviKing = str;

				str = ele->Attribute("KaiLiDe");
				if (str) m_strKaiLiDe = str;

				str = ele->Attribute("GaoDe");
				if (str) m_strGaoDe = str;

			}

			else if (0 == strcmp(ctrname,"navi_mix_set"))
			{
				int data =0;
				ele->Attribute(VERSION, &data);
				if (data>=0 &&  data<=Navi_Mix_Removed )
				{
					m_opt_Navi_MixSound  = (Option_NaviMixSound)data;
				}
				else
				{
					ret = false;
				}
			}

			else if (0 == strcmp(ctrname,"bt_module_set"))
			{
				int data =0;
				ele->Attribute(VERSION, &data);
				if (data>=0 &&  data<=BT_Module_Removed )
				{
					m_bt_Module  = (Option_BT_Module)data;
				}
				else
				{
					ret = false;
				}
			}

			else if (0 == strcmp(ctrname,"bsf_option_set"))
			{
				int data =0;
				ele->Attribute(VERSION, &data);
				if (data>=0 &&  data<=Navi_BSF_Removed )
				{
					m_bsf_Module  = (Option_BSF_Module)data;
				}
				else
				{
					ret = false;
				}
			}


		}
		else
		{
			ASSERT(0);
		}

		ele = ele->NextSiblingElement();
	}

	if (!ret)
	{
		ASSERT(0);
	}
	//xmlDoc->SaveFile( m_strXmlPath.c_str());
	return ret;
}

void VersionXml::SetLanguage( int index )
{
	ASSERT (index>=0 &&  index<=LAN_Simplified );
	WritXmlValue("languages_set",index);
}

void VersionXml::SetSoftWare( int index )
{
	ASSERT (index>=0 &&  index<=Navi_GaoDe );
	WritXmlValue("navi_option_set",index);
}

void VersionXml::SetNaviMix( int index )
{
	ASSERT (index>=0 &&  index<=Navi_Mix_Removed );
	WritXmlValue("navi_mix_set",index);
}

void VersionXml::SetBtModule( int index )
{
	ASSERT (index>=0 &&  index<=BT_Module_Removed );
	WritXmlValue("bt_module_set",index);
}

void VersionXml::SetBSFModule( int index )
{
	ASSERT (index>=0 &&  index<=Navi_BSF_Removed );
	WritXmlValue("bsf_option_set",index);
}

void VersionXml::WritXmlValue( LPCSTR valueName, int index )
{
	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	bool ret = xmlDoc->LoadFile(m_strXmlPath.c_str());
	if (!ret)
	{
		ASSERT(0);
		return;
	}

	ret = false;
	TiXmlElement *ele = xmlDoc->RootElement();
	const CHAR * ctrname = NULL;
	while(ele)
	{
		ctrname = ele->Value();
		if (ctrname)
		{
			if (0 == strcmp(ctrname,valueName))
			{
				ret = true; 
				ele->SetAttribute(VERSION, index);
				break;
			}

		}
		ele = ele->NextSiblingElement();
	}

	if (ret)
	{
		xmlDoc->SaveFile();
	}
	else
	{
		ASSERT(0);
	}
	
}
