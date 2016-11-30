#include "StdAfx.h"
#include "GxxPicIcon.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "StrHelp.h"

static RegisterHelp help("GxxPicIcon", GxxPicIcon::CreateControl);
GxxView* GxxPicIcon::CreateControl()
{
	return new GxxPicIcon;
}


GxxPicIcon::GxxPicIcon()
{


}

GxxPicIcon::~GxxPicIcon()
{

}

void GxxPicIcon::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	if (setPicHandle(ele,BTN_UP))
	{
		if ( !setCtrRectUseCenter(ele,getPicWidth(),getPicHeight()) ){
			if (!setCtrRectUseCenter(ele))
			{
				if (!setCtrRect(ele) )
				{
					ASSERT(0);
				}
			}
		}
		checkToParent(ele);
		bindHandleRect();//m_pPicDisable
	}
	else
	{
		setCtrRectUseCenter(ele);
		//ASSERT(0);
	}
}

const char* GxxPicIcon::GetPicPath()
{
	return SkiaBitmapManager::GetInstance()->GetImagePath(m_hPicture);
}

bool GxxPicIcon::SetPicPath( const char* path )//重新设置路径
{
	if (ResetPicHandle(path))//必须是false
	{
		bindHandleRect(m_ActRect);
		return true;
	}
	return false;
}

bool GxxPicIcon::SetPicPath( const WCHAR* path )
{
	if (path==NULL)
	{
		return false;
	}
	string spath = StrHelp::WStringToString(wstring(path));
	return SetPicPath(spath.c_str());
}


