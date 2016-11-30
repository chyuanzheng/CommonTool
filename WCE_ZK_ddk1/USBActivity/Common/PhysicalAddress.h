#ifndef __PHYSICALADDRESS_H__
#define __PHYSICALADDRESS_H__

#include <Windows.h>


#if defined(__TCC89XX_WINCE__) || defined(__TCC88XX_WINCE__)
#include "ioctl_code.h"
#include "Pkfuncs.h"

#else
#include <CEDDK.h>
#endif


template<class ACCESSTYPE> class cPhysicalAddress
{
protected:
    DWORD mdwPhysicalAddress;
    DWORD mdwSize;

    ACCESSTYPE *mpVirtualAddress;

public:
    cPhysicalAddress()
        : mdwPhysicalAddress(0)
        , mdwSize(0)
        , mpVirtualAddress(NULL)
    {
    }

    cPhysicalAddress(DWORD dwPhysicalAddress, DWORD dwSize=sizeof(ACCESSTYPE))
        : mdwPhysicalAddress(dwPhysicalAddress)
        , mdwSize(dwSize)
        , mpVirtualAddress(NULL)
    {
        ASSERT(mdwPhysicalAddress);
        Open();
    };

    virtual ~cPhysicalAddress()
    {
        Close();
    };


    ACCESSTYPE &operator[](unsigned int offset)const
    {
        return mpVirtualAddress[offset];
    };

    ACCESSTYPE *operator->()const
    {
        return mpVirtualAddress;
    }

    DWORD VirtualAddress(void)const
    {
        return (DWORD)mpVirtualAddress;
    };

    DWORD VirtualAddress(int Offset)const
    {
        return ((DWORD)mpVirtualAddress)+Offset;
    };

    DWORD PhysicalAddress(void)const
    {
        return mdwPhysicalAddress;
    }

    DWORD PhysicalAddress(int Offset)const
    {
        return mdwPhysicalAddress+Offset;
    }

    DWORD Size(void)const
    {
        return mdwSize;
    };

    BOOL IsAvailable(void)const
    {
        return mpVirtualAddress?TRUE:FALSE;
    };

    void SetPhysicalAddress(DWORD dwPhysicalAddress)
    {
        mdwPhysicalAddress=dwPhysicalAddress;
    };

    void SetSize(DWORD dwSize)
    {
        mdwSize=dwSize;
    };

public:
    virtual BOOL Open(void)
    {
        if( NULL==mpVirtualAddress )
        {
#if defined(__TCC89XX_WINCE__) || defined(__TCC88XX_WINCE__)
            PVOID pVirtualAddress=(ACCESSTYPE *)::VirtualAlloc( 0, mdwSize, MEM_RESERVE, PAGE_NOACCESS);
#else
            PHYSICAL_ADDRESS PhysicalAddress={mdwPhysicalAddress, 0};
            PVOID pVirtualAddress=::MmMapIoSpace(PhysicalAddress, mdwSize, FALSE);
#endif

            if( pVirtualAddress )
            {
#if defined(__TCC89XX_WINCE__) || defined(__TCC88XX_WINCE__)
                struct 
                {
                    DWORD dwHwBaseAddress;
                    DWORD dwAllocBaseAddress;
                    DWORD dwSize;
                } UidMem;
                UidMem.dwHwBaseAddress=mdwPhysicalAddress>>8;
                UidMem.dwAllocBaseAddress=(DWORD)pVirtualAddress;
                UidMem.dwSize=mdwSize;

                ::KernelIoControl(IOCTL_HAL_VIRTUALCOPY, &UidMem, sizeof(UidMem), NULL, NULL, NULL);
#endif

                mpVirtualAddress=(ACCESSTYPE *)pVirtualAddress;

                ///::printf("cPhysicalAddress %08x %08x\r\n", mdwPhysicalAddress, mpVirtualAddress);
                return TRUE;
            }

            ::printf("[arc][FAIL]cPhysicalAddress::Open\r\n");
            return FALSE;
        }

        ::printf("[arc][FAIL]cPhysicalAddress::Already Open %x\r\n",mdwPhysicalAddress);
        return FALSE;
    };

    virtual BOOL Open(DWORD dwPhysicalAddress, DWORD dwSize=sizeof(ACCESSTYPE))
    {
        mdwPhysicalAddress=dwPhysicalAddress;
        mdwSize=dwSize;

        return Open();
    };


    virtual BOOL Close(void)
    {
        BOOL r=FALSE;

        if( mpVirtualAddress )
        {
#if defined(__TCC89XX_WINCE__) || defined(__TCC88XX_WINCE__)
            r=::VirtualFree((PVOID)mpVirtualAddress, 0, MEM_RELEASE);
            if( FALSE==r )
            {
                RETAILMSG(1, (TEXT("fail VirtualFree=%d\r\n"), ::GetLastError()));
            }
#else
            ::MmUnmapIoSpace((PVOID)mpVirtualAddress, mdwSize);
            r=TRUE;
#endif
            mpVirtualAddress=NULL;
        }

        return r;
    };
};

#endif//__PHYSICALADDRESS_H__

