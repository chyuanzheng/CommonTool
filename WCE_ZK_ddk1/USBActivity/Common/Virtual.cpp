
#include "Virtual.h"

#if defined(__TCC79XX_WINCE__)||defined(__TCC78XX_WINCE__)
#include <ceddk.h>

volatile LPVOID SetVirtual(unsigned int physical_addr, unsigned int mem_size)
{
	LPVOID pVirtual;

	PHYSICAL_ADDRESS PA;
	PA.LowPart = (DWORD)(physical_addr);

	pVirtual = (DWORD*)MmMapIoSpace(PA,mem_size, FALSE); 
	if(!pVirtual){
		printf("MmMapIoSpace GetLastError() : %d\n",GetLastError());
		return NULL;
	}
	return pVirtual;
}
volatile LPVOID SetVirtualCache(unsigned int physical_addr, unsigned int mem_size)
{
	LPVOID pVirtual;

	PHYSICAL_ADDRESS PA;
	PA.LowPart = (DWORD)(physical_addr);

	pVirtual = (DWORD*)MmMapIoSpace(PA,mem_size, TRUE); 
	if(!pVirtual){
		printf("MmMapIoSpace GetLastError() : %d\n",GetLastError());
		return NULL;
	}
	return pVirtual;
}
void FreeVirtual(LPVOID virtual_ptr, unsigned int mem_size)
{
	MmUnmapIoSpace(virtual_ptr, mem_size);
}
#else

#include "ioctl_code.h"
#include "Pkfuncs.h"
volatile LPVOID SetVirtual(unsigned int HwBaseAddress, unsigned int nSize)
{
	volatile LPVOID pVirtual;
	UID_MEM uid_mem;
	if(HwBaseAddress&0xFFF)
	{
		RETAILMSG(1,(TEXT("Need to Align Baseaddress.. (%x) \n"),HwBaseAddress&0xFFF));
		return NULL;
	}
	//need align 8bit
	uid_mem.dwHwBaseAddress = (DWORD)(HwBaseAddress>>8);
	//alloc virtual space
	pVirtual = VirtualAlloc(0, 
		nSize, 
		MEM_RESERVE, 
		PAGE_NOACCESS);
	uid_mem.dwAllocBaseAddress =(DWORD)pVirtual;
	//define alloc size
	uid_mem.dwSize = nSize;
	DWORD nhRet =KernelIoControl(IOCTL_HAL_VIRTUALCOPY,&uid_mem, sizeof(UID_MEM), NULL, NULL, NULL);
	return pVirtual;
}

void FreeVirtual(LPVOID pVirtualAddress, unsigned int nSize)
{
	if(VirtualFree(pVirtualAddress, 0, MEM_RELEASE) == 0)
	{
		RETAILMSG(1,(TEXT("(VirtualFree Fail.. (%d) \n"),GetLastError()));
	}
}
#endif