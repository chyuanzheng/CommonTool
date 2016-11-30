/****************************************************************************
*   FileName    : globals.h
*   Description : 
****************************************************************************
*
*   TCC Version : 1.0
*   Copyright (c) Telechips, Inc.
*   ALL RIGHTS RESERVED
*
****************************************************************************/

#if defined(__TCC79XX_WINCE__)||defined(__TCC89XX_WINCE__)
#include "globals_TCC89x.H"
#elif __TCC88XX_WINCE__
#include "globals_TCC88x.H"
#endif
