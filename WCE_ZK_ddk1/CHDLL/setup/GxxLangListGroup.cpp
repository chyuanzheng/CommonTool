#include "StdAfx.h"
#include "GxxSelectLBList.h"
#include "GxxLangListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxSetupListLine.h"
#include "GxxSwText.h"
//
//#include "aygshell.h"
static RegisterHelp help("GxxLangListGroup", GxxLangListGroup::CreateControl);
GxxView* GxxLangListGroup::CreateControl()
{
	return new GxxLangListGroup;
}
GxxLangListGroup::GxxLangListGroup()
{

}

GxxLangListGroup::~GxxLangListGroup()
{

}
