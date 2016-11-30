#include "SkMMapStream.h"

#ifdef UNDER_CE
#include <stdio.h>
#define errno GetLastError()
#define open fopen
#define lseek fseek
#define off_t int
#define close fclose
#define O_RDONLY	"r"
#else
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#endif


SkMMAPStream::SkMMAPStream(const char filename[])
{
    fFildes = -1;   // initialize to failure case

    //FILE* fildes = open(filename, O_RDONLY);
	wchar_t wfilename[MAX_PATH] = {0};
	mbstowcs(wfilename, filename, MAX_PATH);
	wfilename[MAX_PATH-1] = 0;
    HANDLE fildes = CreateFileForMapping(wfilename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (fildes == INVALID_HANDLE_VALUE)
    {
        SkDEBUGF(("---- failed to open(%s) for mmap stream error=%d\n", filename, errno));
        return;
    }

 //   off_t offset = lseek(fildes, 0, SEEK_END);    // find the file size
 //   
	//if (offset == -1)
 //   {
 //       SkDEBUGF(("---- failed to lseek(%s) for mmap stream error=%d\n", filename, errno));
 //       close(fildes);
 //       return;
 //   }
 //   (void)lseek(fildes, 0, SEEK_SET);   // restore file offset to beginning
	off_t offset = GetFileSize(fildes, NULL);

    // to avoid a 64bit->32bit warning, I explicitly create a size_t size
    size_t size = static_cast<size_t>(offset);

    //void* addr = mmap(NULL, size, PROT_READ, MAP_SHARED, fildes, 0);
	HANDLE hMap = CreateFileMapping(fildes, 
		NULL,
		PAGE_READONLY,
		0,
		size,
		NULL);

	void* addr = MapViewOfFile(hMap, 
		FILE_MAP_READ,
		0,
		0,
		NULL);
    if (NULL == addr)
    {
        SkDEBUGF(("---- failed to mmap(%s) for mmap stream error=%d\n", filename, errno));
        close(fildes);
        return;
    }

    this->INHERITED::setMemory(addr, size);

    fFildes = (int)fildes;
    fAddr = addr;
    fSize = size;
	fMap = hMap;
}

SkMMAPStream::~SkMMAPStream()
{
    this->closeMMap();
}

void SkMMAPStream::setMemory(const void* data, size_t length, bool copyData)
{
    this->closeMMap();
    this->INHERITED::setMemory(data, length, copyData);
}

void SkMMAPStream::closeMMap()
{
    if (fFildes >= 0)
    {
        //munmap(fAddr, fSize);
        //close((FILE*)fFildes);
		UnmapViewOfFile(fAddr);
		CloseHandle((HANDLE)fMap);
		CloseHandle((HANDLE)fFildes);
        fFildes = -1;
    }
}

