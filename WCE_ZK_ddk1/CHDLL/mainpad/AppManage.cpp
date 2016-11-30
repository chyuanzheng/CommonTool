#include "StdAfx.h"
#include "AppManage.h"
#include "StrHelp.h"

#define  DLL_MANI_PATH  "layout\\DllManifest.xml"
#define  DLL_MANIFEST   "dllmanifest"
#define  APPMODULE      "AppModule"
#define  S_ACTIVITY     "activity" 
#define  S_ICONBACK     "iconback" 
#define  ICON         "icon" 
#define  ICONG         "icong" 
#define  S_ICON         "s_icon" 
#define  S_ICONG         "s_icong" 
#define  S_TITLE        "title" 
#define  S_TITLE_ID        "title_id" 
#define  S_PARAM_ID      "param_id" 
#define  S_ICON_PLAY      "iconplay" 


TV_Module AppManage::m_vModule;
AppManage *AppManage::m_pInstance = NULL;
string T_AppModule::iconback = string();
string T_AppModule::iconplay = string();
AppManage::AppManage()
{
	init();
}

AppManage::~AppManage()
{

}


AppManage* AppManage::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new AppManage;
	}
	return m_pInstance;
}

void AppManage::init()
{
	InitDllManifest();

}

void AppManage::InitDllManifest()
{

	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	bool ret = xmlDoc->LoadFile(AfxAddWorkPathA(DLL_MANI_PATH));
	ASSERT(ret);

	TiXmlElement *root = xmlDoc->RootElement();
	if (strcmp(root->Value(), DLL_MANIFEST) != 0)
	{
		ASSERT(0);
	}

	const CHAR *elename = NULL;
	elename = root->Attribute(S_ICONBACK);
	ASSERT(NULL!=elename);
	T_AppModule::iconback = elename;

	elename = root->Attribute(S_ICON_PLAY);
	ASSERT(NULL!=elename);
	T_AppModule::iconplay = elename;

	

	TiXmlElement * ele = root->FirstChildElement();
	
	int i=0;
	while(ele)
	{
		T_AppModule *tapp = new T_AppModule;
		tapp->m_nth = i;
		i++;
		elename = ele->Attribute(S_ACTIVITY);
		ASSERT(NULL!=elename);
		tapp->activity=elename;



		elename = ele->Attribute(ICON);
		ASSERT(NULL!=elename);
		tapp->icon=elename;

		elename = ele->Attribute(ICONG);
		ASSERT(NULL!=elename);
		tapp->icong=elename;

		elename = ele->Attribute(S_ICON);
		ASSERT(NULL!=elename);
		tapp->s_icon=elename;

		elename = ele->Attribute(S_ICONG);
		ASSERT(NULL!=elename);
		tapp->s_icong=elename;

		elename = ele->Attribute(S_TITLE);
		if(NULL!=elename)
		{
			tapp->title=elename;
		}
		


		elename = ele->Attribute(S_TITLE_ID);
		if (NULL!=elename)
		{
			tapp->title_id=elename;
		}
		
		

		elename = ele->Attribute(S_PARAM_ID);
		if (NULL!=elename)
		{
			tapp->param_id = elename;
		}
		else
		{
			tapp->param_id = "";
		}

		m_vModule.push_back(tapp);

		ele = ele->NextSiblingElement();

	}
}

T_AppModule* AppManage::GetModule( UINT nth )
{
	if(nth>=m_vModule.size())
	{
		return NULL;
	}
	return m_vModule[nth];
}

void AppManage::SetAppPlaying( const string & str_a,const string & str_para )
{
	for (TV_Module::iterator pos = m_vModule.begin();pos != m_vModule.end(); ++pos)
	{
		if (str_a == (*pos)->activity /*&& str_para == (*pos)->param_id*/)
		{
			(*pos)->b_playing = true;
		}
		else
		{
			(*pos)->b_playing = false;
		}
	}
}

void AppManage::SetAppEnable( const string & str_a,bool b )
{
	for (TV_Module::iterator pos = m_vModule.begin();pos != m_vModule.end(); ++pos)
	{
		if (str_a == (*pos)->activity)
		{
			(*pos)->b_enable = b;
			if (!b)
			{
				(*pos)->b_playing = false;
			}
		}
	}
}

bool AppManage::GetAppEnable( const string & str_a, bool& ret)
{
	for (TV_Module::iterator pos = m_vModule.begin();pos != m_vModule.end(); ++pos)
	{
		if (str_a == (*pos)->activity)
		{
			ret =  (*pos)->b_enable;
			return true;				//获取成功，返回true
		}
	}
	return false;	//获取失败，返回false
}

void AppManage::SetActivity( const string& tostart, Activity * pAct )
{
	for (TV_Module::iterator pos = m_vModule.begin();pos != m_vModule.end(); ++pos)
	{
		if (tostart == (*pos)->activity)
		{
			(*pos)->p_act = pAct;
		}
	}
}

int AppManage::GetActivityNth( Activity * const pAct )
{
	if (pAct)
	{
		int i = 0;
		for (TV_Module::iterator pos = m_vModule.begin();pos != m_vModule.end(); ++pos,++i)
		{
			if (pAct == (*pos)->p_act)
			{
				return i;
			}
		}
	}
	return -1;
}
