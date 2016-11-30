#ifndef __CACHEALLOCATOR_H__
#define __CACHEALLOCATOR_H__

#include <new>


class cCache
{
public:
    void *mp;
    int mCount;

public:
    cCache(): mp(NULL), mCount(0)
    {
    };

    ~cCache()
    {
        int c=0;

        void *p;
        while( mp )
        {
            p=mp;
            mp=*(void **)mp;

            delete p;
            ++c;
        }

        if( c!=mCount )
        {
            RETAILMSG(1, (TEXT("~%08x [caution] Total %d allcocated, %d deleted\r\n"), this, mCount, c));
        }
    };
};

template<class T> class cCacheAllocator
{
protected:
    static cCache mCache;

public:
    static void *operator new(unsigned int Size) throw(std::bad_alloc)
    {
        if( sizeof(T)==Size )
        {
            if( mCache.mp )
            {
                T *p=(T *)mCache.mp;
                mCache.mp=*(void **)mCache.mp;

                return p;
            }
            ++mCache.mCount;
        }
        else
        {
            RETAILMSG(1, (TEXT("~%08x [caution] new different size(%d, %d)\r\n"), &mCache, sizeof(T), Size));
        }

        return ::operator new(Size);
    };

    static void operator delete(void *p, unsigned int Size) throw()
    {
        if( p )
        {
            if( sizeof(T)==Size )
            {
                *(void **)p=mCache.mp;
                mCache.mp=p;

                return;
            }
            else
            {
                RETAILMSG(1, (TEXT("~%08x [caution] delete different size(%d, %d)\r\n"), &mCache, sizeof(T), Size));
            }

            ::operator delete(p);
        }
    };
};

template<class T> cCache cCacheAllocator<T>::mCache;


#endif//__CACHEALLOCATOR_H__
