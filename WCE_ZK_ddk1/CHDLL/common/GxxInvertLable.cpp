#include "StdAfx.h"
#include "GxxInvertLable.h"
#include "XmlDef.h"
#include "ControlHelp.h"
#include "StrHelp.h"
#include "LangStringManager.h"
static RegisterHelp help("GxxInvertLable", GxxInvertLable::CreateControl);
GxxView* GxxInvertLable::CreateControl()
{
	return new GxxInvertLable;
}


GxxInvertLable::GxxInvertLable()
{


}

GxxInvertLable::~GxxInvertLable()
{

}

void GxxInvertLable::Draw(  )
{

}



void GxxInvertLable::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	if (!setCtrRectUseCenter(ele))
	{
		ASSERT(0);
	}

	const char * c = ele->Attribute("Invert_y",&m_Invert_y);
	ASSERT( NULL != c );

	//setOnlyDrawActRect(true);
	TiXmlElement * chid = ele->FirstChildElement();
	setCtrList(chid);

}

void GxxInvertLable::Paint()
{

	SkiaBitmapManager::GetInstance()->SaveStatus();
	SkiaBitmapManager::GetInstance()->SetInvertX(m_Invert_y);
	SkiaBitmapManager::GetInstance()->SetClipRect(m_ActRect);

	Draw();
	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{
		(*pos)->Paint(  );	
		pos++;
	}


	SkiaBitmapManager::GetInstance()->ReleasStatus();
	
}






