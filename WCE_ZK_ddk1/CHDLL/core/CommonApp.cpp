#include "stdAfx.h"
#include "StrHelp.h"
#include "GXCreateControls.h"
#include "CommonApp.h"
#include "CommonWnd.h"
#include "ResStringManager.h"
#include "CWnd.h"
#include "CPopupWnd.h"

#include <iostream>
#include <fstream>
/////////////////////////////////////////////////////////////////////////
// CCommonApp member functions

BOOL CCommonApp::InitInstance ()
{
	//AfxShowTaskBar(FALSE);
	


	m_pMainWnd = new CCommonWnd;
	m_pMainWnd->ShowWindow (m_nCmdShow);
	m_pMainWnd->UpdateWindow();  
	//m_pPopupWnd = new CPopupWnd;
	//m_pPopupWnd->ShowWindow(SW_HIDE);

	if (!InitActivity("layout\\WinceManifest.xml"))// concrete code ,adjusts later
	{
		ASSERT(0);
		return FALSE;
	}
	ResStringManager::GetInstance();

	//DWORD s0 = GetTickCount();

	//DWORD s1 = GetTickCount() - s0;
	//CHAR  show[60];
	//sprintf(show,"time is :%d",s1);

	//std::ofstream   file("\\NAND\\test.txt");
	//file << show << endl;
	


	//RETAILMSG(1,(show));
    return TRUE;
}

BOOL CCommonApp::DeInitInstance()
{
	AfxShowTaskBar();
	return TRUE;
}

//这里非常容易内存溢出 注意delete
BOOL CCommonApp::InitActivity( const char* strManifest )
{
	//throw std::exception("The method or operation is not implemented.");

	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);


	if (!xmlDoc->LoadFile(AfxAddWorkPathA(strManifest) ))
	{
		OutputDebugString(L"LoadFile error! \r\n");
		return FALSE;
	}

	TiXmlElement *root = xmlDoc->RootElement();
	if (strcmp(root->Value(), "manifest") != 0)
	{
		return FALSE;
	}
	
	TiXmlElement * element = root->FirstChildElement();
   
	Activity *mainAct = NULL;
	while(element)
	{
		if (strcmp(element->Value(), "Module") != 0)
		{
			return FALSE;
		}

		const char * strName= element->Attribute("name");
		const char * strAction= element->Attribute("action");
		const char * strActivity= element->Attribute("activity");
		
		if (string(strActivity) == "MainPad" )//if (string(strAction) == "MAIN"|| string(strAction) == "SetupActivity")
		{
			//ASSERT(NULL!= strActivity);
			//DWORD s0 = GetTickCount();
			mainAct = Activity::findActivity(string(strActivity));
			//DWORD s1 = GetTickCount() - s0;
			//CHAR  show[60];
			//sprintf(show,"time is :%d",s1);
			//std::ofstream   file("\\NAND\\test1.txt");
			//file << show << endl;
		}
		else if ( string(strActivity) == "SetupActivity")
		{
			Activity::loadDllModule(strName, strActivity);
		}
		else if (string(strAction) == "DLL")
		{
			Activity::AddActivityDll(strActivity,strName);
			//loadDllModule(strName, strActivity);
		}
		else 
		{
			ASSERT(0);
		}
		element = element->NextSiblingElement();

	}
	ASSERT(mainAct!=NULL);
	mainAct->TranslateMessage(CTR_MAIN_LOAD,0,0);


	return TRUE;
}

