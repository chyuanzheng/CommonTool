#pragma once

#include "StdAfx.h"
#include "GxxView.h"
class CE_CONTROL_API RegisterHelp
{
public:
	RegisterHelp(const CHAR *cName, FunCrtControl funCreate);
	RegisterHelp(const CHAR *cName, FunCrtActivity funCreate);
};