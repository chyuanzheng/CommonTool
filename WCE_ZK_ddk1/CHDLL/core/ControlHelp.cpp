#include "StdAfx.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"

RegisterHelp::RegisterHelp( const CHAR *cName, FunCrtControl funCreate )
{
	GXCreateControl::RegisterControlCreate(cName, funCreate);
}

RegisterHelp::RegisterHelp( const CHAR *cName, FunCrtActivity funCreate )
{
	GXCreateControl::RegisterActivityCreate(cName, funCreate);
}
