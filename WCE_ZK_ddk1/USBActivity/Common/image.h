/**********************************************************************
* TCC_COPYRIGHT
*

* END_TCC_COPYRIGHT
***********************************************************************/

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <windows.h>

namespace tcw{	

HBITMAP CreateDibSectionFromDibFile(PCTSTR szFileName, BYTE*& pBits);

}
#endif
