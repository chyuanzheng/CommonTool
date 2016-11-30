#pragma once

#ifdef HARDWAREDLL_EXPORTS
#define CE_HardwareDll_API __declspec(dllexport)
#else
#define CE_HardwareDll_API __declspec(dllimport)
#endif


