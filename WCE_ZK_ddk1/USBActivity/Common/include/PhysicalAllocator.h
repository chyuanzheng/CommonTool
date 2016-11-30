#ifndef __PHYSICALALLOCATOR_H__
#define __PHYSICALALLOCATOR_H__

#include <streams.h>


// {E87E4466-0111-41a3-A43F-1A5690DF4286}
static const GUID IID_PhysicalMediaSample={0xe87e4466, 0x111, 0x41a3, {0xa4, 0x3f, 0x1a, 0x56, 0x90, 0xdf, 0x42, 0x86}};


struct IPhysicalMediaSample: public IUnknown
{
    virtual DWORD PhysicalAddress(void)=0;
};


class cPhysicalMediaSample: public CMediaSample, public IPhysicalMediaSample
{
protected:
    DWORD mPhysicalAddress;

public:
    cPhysicalMediaSample(TCHAR *pName, CBaseAllocator *pAllocator, HRESULT *phr, PBYTE pBuffer, LONG Length, DWORD PhysicalAddress)
        : CMediaSample(pName, pAllocator, phr, pBuffer, Length)
        , mPhysicalAddress(PhysicalAddress)
    {
    };

    ~cPhysicalMediaSample()
    {
    };

public:
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if( IID_PhysicalMediaSample==riid )
            return ::GetInterface((IPhysicalMediaSample *)this, ppv);

        return CMediaSample::QueryInterface(riid, ppv);
    };

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        return CMediaSample::AddRef();
    };

    STDMETHODIMP_(ULONG) Release(void)
    {
        return CMediaSample::Release();
    };

    DWORD PhysicalAddress(void)
    {
        return mPhysicalAddress;
    };

    CMediaSample *&Next(void)
    {
        return m_pNext;
    };
};


///#define __DEBUG_PHYSICALALLOCATOR__

// {E016004C-8DB0-40e2-ADB9-494E38044CEB}
static const GUID IID_IPhysicalAllocator={0xe016004c, 0x8db0, 0x40e2, {0xad, 0xb9, 0x49, 0x4e, 0x38, 0x4, 0x4c, 0xeb}};

struct IPhysicalAllocator: public IUnknown
{
    virtual HRESULT GetVirtualAddress(DWORD *pAddress)=0;
    virtual HRESULT GetPhysicalAddress(DWORD *pAddress)=0;
    virtual HRESULT GetSize(DWORD *pSize)=0;
};

class cPhysicalAllocator: public CBaseAllocator, public IPhysicalAllocator
{
protected:
    unsigned int mPhysicalAddress;
    unsigned int mVirtualAddress;
    unsigned int mSize;

    LONG mlAlignedSize;

protected:
    void Free(void)
    {
        ASSERT(m_lAllocated==m_lFree.GetCount());

        CMediaSample *pSample;
        while( (pSample=m_lFree.RemoveHead()) )
        {
            delete pSample;
        }
        m_lAllocated=0;

        if( mPhysicalAddress )
        {
            ReleasePhysicalMemory(mPhysicalAddress, mVirtualAddress);

            mPhysicalAddress=0;
            mVirtualAddress=0;
            mSize=0;
        }

        m_bChanged=TRUE;
    };

    HRESULT Alloc(void)
    {
        CAutoLock lck(this);

        HRESULT hr=CBaseAllocator::Alloc();
        if( SUCCEEDED(hr) )
        {
            if( hr==S_FALSE )
            {
                ASSERT(mPhysicalAddress);
                return NOERROR;
            }
            ASSERT(hr==S_OK);
            ASSERT(0==m_lAllocated);

            mlAlignedSize=m_lSize+m_lPrefix;
            if( 1<m_lAlignment )
            {
                LONG lRemainder=mlAlignedSize%m_lAlignment;
                if( lRemainder )
                {
                    mlAlignedSize+=(m_lAlignment-lRemainder);
                }
            }
            ASSERT(mlAlignedSize%m_lAlignment==0);

            mSize=m_lCount*mlAlignedSize;
            mPhysicalAddress=ReservePhysicalMemory(mSize, mVirtualAddress);
            if( mPhysicalAddress )
            {
                LPBYTE pNext=(LPBYTE)mVirtualAddress;
                DWORD PhysicalAddress=mPhysicalAddress;

                CMediaSample *pSample;
                for(; m_lAllocated<m_lCount; ++m_lAllocated, pNext+=mlAlignedSize, PhysicalAddress+=mlAlignedSize)
                {
                    pSample=CreatePhysicalMediaSample(&hr, pNext+m_lPrefix, m_lSize, PhysicalAddress+m_lPrefix);

                    ASSERT(SUCCEEDED(hr));
                    if( NULL==pSample )
                    {
                        Free();
                        return E_OUTOFMEMORY;
                    }

                    m_lFree.Add(pSample);
                }

                m_bChanged=FALSE;
                return NOERROR;
            }
            mSize=0;

            return E_OUTOFMEMORY;
        }

        return VFW_E_SIZENOTSET==hr?S_FALSE:hr;
    };

    virtual unsigned int ReservePhysicalMemory(unsigned int Size, unsigned int &rVirtualAddress)=0
    {
        RETAILMSG(1, (TEXT("%s should never be called.\r\n"), TEXT(__FUNCTION__)));

        rVirtualAddress=0;
        return 0;
    };

    virtual bool ReleasePhysicalMemory(unsigned int PhysicalAddress, unsigned int VirtualAddress)=0
    {
        RETAILMSG(1, (TEXT("%s should never be called.\r\n"), TEXT(__FUNCTION__)));
        return false;
    };

    virtual cPhysicalMediaSample *CreatePhysicalMediaSample(HRESULT *phr, PBYTE pBuffer, LONG Length, DWORD PhysicalAddress)
    {
        cPhysicalMediaSample *pSample=new cPhysicalMediaSample(NAME("PhysicalMediaSample"), this, phr, pBuffer, Length, PhysicalAddress);

        if( FAILED(*phr) )
        {
            delete pSample;
            return NULL;
        }

        return pSample;
    };

public:
    cPhysicalAllocator(TCHAR *pName, HRESULT *phr)
        : CBaseAllocator(pName, NULL, phr)
        , mPhysicalAddress(0)
        , mVirtualAddress(0)
        , mSize(0)
        , mlAlignedSize(0)
    {
    };

    ~cPhysicalAllocator()
    {
    };

public:
    STDMETHODIMP SetProperties(ALLOCATOR_PROPERTIES *pRequest, ALLOCATOR_PROPERTIES *pActual)
    {
        CheckPointer(pActual, E_POINTER);
        ValidateReadWritePtr(pActual, sizeof(ALLOCATOR_PROPERTIES));
        CAutoLock cObjectLock(this);

        ZeroMemory(pActual, sizeof(ALLOCATOR_PROPERTIES));

        SYSTEM_INFO SysInfo;
        GetSystemInfo(&SysInfo);

        /*  Check the alignment request is a power of 2 */
        if ((-pRequest->cbAlign & pRequest->cbAlign) != pRequest->cbAlign)
        {
            DbgLog((LOG_ERROR, 1, TEXT("Alignment requested 0x%x not a power of 2!"), pRequest->cbAlign));
        }
        /*  Check the alignment requested */
        if (pRequest->cbAlign == 0 || (SysInfo.dwAllocationGranularity & (pRequest->cbAlign - 1)) != 0)
        {
            DbgLog((LOG_ERROR, 1, TEXT("Invalid alignment 0x%x requested - granularity = 0x%x"), pRequest->cbAlign, SysInfo.dwAllocationGranularity));
            return VFW_E_BADALIGN;
        }

        /* Can't do this if already committed, there is an argument that says we
        should not reject the SetProperties call if there are buffers still
        active. However this is called by the source filter, which is the same
        person who is holding the samples. Therefore it is not unreasonable
        for them to free all their samples before changing the requirements */

        if (m_bCommitted == TRUE) {
            return VFW_E_ALREADY_COMMITTED;
        }

        /* Must be no outstanding buffers */
        if (m_lFree.GetCount() < m_lAllocated) {
            return VFW_E_BUFFERS_OUTSTANDING;
        }

        /* There isn't any real need to check the parameters as they will just be rejected when the user finally calls Commit */

        // round length up to alignment - remember that prefix is included in the alignment
        LONG lSize = pRequest->cbBuffer + pRequest->cbPrefix;
        LONG lRemainder = lSize % pRequest->cbAlign;
        if( lRemainder )
        {
            lSize=lSize-lRemainder+pRequest->cbAlign;
        }
        pActual->cbBuffer=m_lSize=(lSize-pRequest->cbPrefix);

        pActual->cBuffers=m_lCount=pRequest->cBuffers;
        pActual->cbAlign=m_lAlignment=pRequest->cbAlign;
        pActual->cbPrefix=m_lPrefix=pRequest->cbPrefix;

        m_bChanged=TRUE;
        return NOERROR;
    };

public:
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if( IID_IPhysicalAllocator==riid )
            return ::GetInterface((IPhysicalAllocator *)this, ppv);

        return CBaseAllocator::QueryInterface(riid, ppv);
    };

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        return CBaseAllocator::AddRef();
    };

    STDMETHODIMP_(ULONG) Release(void)
    {
        return CBaseAllocator::Release();
    };

    HRESULT GetVirtualAddress(DWORD *pAddress)
    {
        if( mPhysicalAddress && pAddress )
        {
            *pAddress=mVirtualAddress;
            return S_OK;
        }

        return E_FAIL;
    };

    HRESULT GetPhysicalAddress(DWORD *pAddress)
    {
        if( mPhysicalAddress && pAddress )
        {
            *pAddress=mPhysicalAddress;
            return S_OK;
        }

        return E_FAIL;
    };

    HRESULT GetSize(DWORD *pSize)
    {
        if( mPhysicalAddress && pSize )
        {
            *pSize=mSize;
            return S_OK;
        }

        return E_FAIL;
    };
};


#endif//__PHYSICALALLOCATOR_H__
