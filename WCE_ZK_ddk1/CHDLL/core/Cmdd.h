#pragma once

#ifdef CMDD_EXPORTS
#define CE_CONTROL_API __declspec(dllexport)
#else
#define CE_CONTROL_API __declspec(dllimport)
#endif


#include "Activity.h"