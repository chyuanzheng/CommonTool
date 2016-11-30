#include "StdAfx.h"
#include "GxxDelimiter.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "ResStringManager.h"

static RegisterHelp help("GxxDelimiter", GxxDelimiter::CreateControl);
string GxxDelimiter::s_str_path;  
GxxView* GxxDelimiter::CreateControl()
{
	return new GxxDelimiter;
}


GxxDelimiter::GxxDelimiter()
{


}

GxxDelimiter::~GxxDelimiter()
{

}

void GxxDelimiter::setLayout()
{

	RECT p_rect = getParentView()->getCtrRect();
	if (p_rect.right - p_rect.left > 500)
	{
		if ( !setPicHandle(ResStringManager::GetInstance()->getString("delimiter")) )
		{
			ASSERT(0);
		}
	}
	else
	{
		if ( !setPicHandle(ResStringManager::GetInstance()->getString("short_delimiter")) )
		{
			ASSERT(0);
		}
	}

	//setCtrRectUseCenter(ele,getPicWidth(),getPicHeight());	
	int nwidth = getPicWidth(); 
	int nheight = getPicHeight(); 
	int ncenterX = (p_rect.left + p_rect.right)/2;

	m_ActRect.left  = ncenterX - nwidth/2;
	m_ActRect.right = ncenterX + nwidth/2;
	m_ActRect.top    = p_rect.bottom - nheight;
	m_ActRect.bottom = p_rect.bottom;
	bindHandleRect();//m_pPicDisable
}


