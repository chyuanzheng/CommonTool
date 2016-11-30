#include "StdAfx.h"
#include "GxxSelectLBList.h"
#include "GxxBassListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxSetupListLine.h"
#include "GxxPicIcon.h"
#include "ResStringManager.h"

//
//#include "aygshell.h"
static RegisterHelp help("GxxBassListGroup", GxxBassListGroup::CreateControl);
GxxView* GxxBassListGroup::CreateControl()
{
	return new GxxBassListGroup;
}
GxxBassListGroup::GxxBassListGroup()
{
	pic_path[0] =  ResStringManager::GetInstance()->getString("bass_eq1");
	//pic_handle[0] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[1] =  ResStringManager::GetInstance()->getString("bass_eq2");
	//pic_handle[1] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[2] =  ResStringManager::GetInstance()->getString("bass_eq3");
	//pic_handle[2] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[3] =  ResStringManager::GetInstance()->getString("bass_eq4");
	//pic_handle[3] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[4] =  ResStringManager::GetInstance()->getString("bass_eq5");
	//pic_handle[4] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 


	pic_path[5] =  ResStringManager::GetInstance()->getString("bass_eq6");
	//pic_handle[5] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[6] =  ResStringManager::GetInstance()->getString("bass_eq7");
	//pic_handle[6] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[7] =  ResStringManager::GetInstance()->getString("bass_eq8");
	//pic_handle[7] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[8] =  ResStringManager::GetInstance()->getString("bass_eq9");
	//pic_handle[8] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 

	pic_path[9] =  ResStringManager::GetInstance()->getString("bass_eq10");
	//pic_handle[9] = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pic_path)); 
 

}

GxxBassListGroup::~GxxBassListGroup()
{

}


void GxxBassListGroup::setCtrLayout( TiXmlElement * ele )
{
	GxxSelectListGroupBase::setCtrLayout(ele);
	m_bassPic = (GxxPicIcon *)safeFindViewByName("pic_bass");
}

bool GxxBassListGroup::SetSelLine( int nlan,bool showSel/*=false */ )
{
	ASSERT(nlan <10);
	m_bassPic->setPicHandle(pic_path[nlan].c_str());
	m_bassPic->bindHandleRect();
	bool b = GxxSelectListGroupBase::SetSelLine(nlan);
	ASSERT(b);

	getParentView()->TranslateMessage(CTR_TRANLATE_MES,nlan,0);
	return true;
}






