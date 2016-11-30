#ifndef __ITCCVERSIONINFORMATION_H__
#define __ITCCVERSIONINFORMATION_H__

#include <Windows.h>


// {46912672-AD16-459a-A04E-99EFCF124616}
static const GUID IID_ITCCVersionInformation={0x46912672, 0xad16, 0x459a, {0xa0, 0x4e, 0x99, 0xef, 0xcf, 0x12, 0x46, 0x16}};

struct ITCCVersionInformation : public IUnknown
{
	virtual HRESULT GetVersion(LPTSTR lpString, int nMaxCount)=0;
};


#endif
