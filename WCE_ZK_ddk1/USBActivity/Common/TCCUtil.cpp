
#include "TCCUtil.h"

void* TC_Allocate_Memory (unsigned int iSize)
{
	return new unsigned char[iSize];
}

int TC_Deallocate_Memory(void *pvPtr)
{
	if(pvPtr){
		delete [] pvPtr;
		pvPtr = NULL;
		return 0;
	}
	else
		return -1;
}

int	TC_Check_Pointer(unsigned uNum, char *pSrc, unsigned uLine, ...)
{	
	return	1;
}
