#include "StdAfx.h"
#include "GxxSetupLBList.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"
#include "TimerManager.h"
#include "GxxSetupListLine.h"

#include "LangStringManager.h"
#include "Activity.h"
#include "VersionXml.h"

GxxSetupLBList::GxxSetupLBList()
{
	m_pCtrline_1 = m_pCtrline_0 = NULL;
}

GxxSetupLBList::~GxxSetupLBList()
{
	delete m_pCtrline_1;
	delete m_pCtrline_0;
}
void GxxSetupLBList::setCtrLayout( TiXmlElement * ele )
{

	SetNameTitle(ele);	

	TiXmlElement * chid = ele->FirstChildElement();
	//setCtrList(chid);//设定每一行
	string ctrname;


	while(chid)
	{
		ctrname = chid->Value();
		if (ctrname == "ANVI_SIMPLE_Line" )
		{
			if (VersionXml::GetInstance()->GetNaviMix()==VersionXml::Navi_Mix_Added)
			{
				TiXmlElement * chid2 =  chid->FirstChildElement();
				ctrname = chid2->Value();
				if ((ctrname == "GxxListLine"))
				{
					AddSetupLine(chid2);
				}
				else if(ctrname == "GxxListLine_1")
				{
					if (NULL==m_pCtrline_1)
					{
						m_pCtrline_1 = new ControlList;
					}
					GxxSetupListLine *ctr = new GxxSetupListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
					m_pCtrline_1->push_back(ctr);
					AddCtrl(ctr);
					ctr->setLineLayout(0,chid2);
					
				}
				else if(ctrname == "GxxListLine_0")
				{
					if (NULL==m_pCtrline_0)
					{
						m_pCtrline_0 = new ControlList;
					}
					GxxSetupListLine *ctr = new GxxSetupListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
					m_pCtrline_0->push_back(ctr);
					AddCtrl(ctr);
					ctr->setLineLayout(0,chid2);	
				}
				
			}

		}
		else if (ctrname == "CheckBlueTooth" )
		{
			if (Activity::s_bluetooth_exist)//如果存在蓝牙
			{
				TiXmlElement * chid2 =  chid->FirstChildElement();
				ctrname = chid2->Value();
				ASSERT(ctrname == "GxxListLine");
				AddSetupLine(chid2);
			}
		}
		else if (ctrname == "BSFVersion_All" )
		{
			if (VersionXml::GetInstance()->GetBSFModule() == VersionXml::Navi_BSF_Added)//
			{
				TiXmlElement * chid2 =  chid->FirstChildElement();
				ctrname = chid2->Value();
				ASSERT(ctrname == "GxxListLine");
				AddSetupLine(chid2);
			}
		}
		else if (ctrname == "BSFVersion_Sipmle" )
		{
			if ( VersionXml::GetInstance()->GetBSFModule() == VersionXml::Navi_BSF_Removed )//
			{
				TiXmlElement * chid2 =  chid->FirstChildElement();
				ctrname = chid2->Value();
				ASSERT(ctrname == "GxxListLine");
				AddSetupLine(chid2);
			}
		}
		else if(ctrname == "GxxListLine_1")
		{
			if (NULL==m_pCtrline_1)
			{
				m_pCtrline_1 = new ControlList;
			}
			GxxSetupListLine *ctr = new GxxSetupListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
			m_pCtrline_1->push_back(ctr);
			AddCtrl(ctr);
			ctr->setLineLayout(0,chid);
		}
		else if(ctrname == "GxxListLine_0")
		{
			if (NULL==m_pCtrline_0)
			{
				m_pCtrline_0 = new ControlList;
			}
			GxxSetupListLine *ctr = new GxxSetupListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
			m_pCtrline_0->push_back(ctr);
			AddCtrl(ctr);
			ctr->setLineLayout(0,chid);	
			
		}
		else
		{
			ASSERT(ctrname == "GxxListLine");
			AddSetupLine(chid);
		}

		chid = chid->NextSiblingElement();
	}
	CaculateRation(false);
	//int nsize= getCtrlsSize();

}

void GxxSetupLBList::AddSetupLine( TiXmlElement * ele )
{
	GxxSetupListLine *ctr=NULL;
	ctr = new GxxSetupListLine;//GXCreateControl::CreateControlByType(ctrname.c_str());
	AddCtrl(ctr);
	ctr->setLineLayout(getCtrlsSize()-1,ele);
	
}

BOOL GxxSetupLBList::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( message == CTR_SETUP_READ_LIST	 ||  message ==  CTR_SETUP_READ_CURSOR	||  message ==  CTR_DEFEAT_ENABLE )
	{
		return GxxView::DealCtrlMsg(message,wParam,lParam);
	}
	else if (message == CTR_LINE_01_SWITCH)
	{
		if (wParam)
		{
			if (m_pCtrline_0)//这里减去所有的 0的line
			{
				RemoveLine(m_pCtrline_0);
				RemoveLine(m_pCtrline_1);
				AddLine(m_pCtrline_1);
				CaculateRation(false);
			}
		}
		else
		{
			if (m_pCtrline_1)//这里减去所有的 1的line
			{
				RemoveLine(m_pCtrline_0);
				RemoveLine(m_pCtrline_1);
				AddLine(m_pCtrline_0);
				CaculateRation(false);
			}
		}
		return TRUE;
	}
	else
	{
		return GxxLBList::DealCtrlMsg(message,wParam,lParam);
	}
	
}

void GxxSetupLBList::RemoveLine( ControlList * pListLine )
{
	if (NULL==pListLine)
	{
		return;
	}
	ControlList::iterator pos = pListLine->begin();
	while(pos != pListLine->end())
	{	
		m_pCtrlVet->remove(*pos);
		pos++;
	}
}

void GxxSetupLBList::AddLine( ControlList * pListLine )
{
	if (NULL==pListLine)
	{
		return;
	}
	ControlList::iterator pos = pListLine->begin();
	while(pos != pListLine->end())
	{	
		m_pCtrlVet->push_back(*pos);
		pos++;
	}
}




