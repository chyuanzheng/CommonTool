/******************************************************************************
* TCC_COPYRIGHT
*
* END_TCC_COPYRIGHT
******************************************************************************/

#include "image.h"

namespace tcw{	
HBITMAP CreateDibSectionFromDibFile(PCTSTR szFileName, BYTE*& pBits)
{
	BITMAPFILEHEADER bmfh ;
	BITMAPINFO     * pbmi ;

	BOOL             bSuccess ;
	DWORD            dwInfoSize, dwBytesRead ;
	HANDLE           hFile ;
	HBITMAP          hBitmap ;

	// Open the file: read access, prohibit write access
	hFile = CreateFile (szFileName, GENERIC_READ, FILE_SHARE_READ,
	NULL, OPEN_EXISTING, 0, NULL) ;

	if (hFile == INVALID_HANDLE_VALUE)
		return NULL ;

	// Read in the BITMAPFILEHEADER
	bSuccess = ReadFile (hFile, &bmfh, sizeof (BITMAPFILEHEADER), 
		&dwBytesRead, NULL) ;

	if (!bSuccess || (dwBytesRead != sizeof (BITMAPFILEHEADER))         
		|| (bmfh.bfType != * (WORD *) "BM"))
	{
		CloseHandle (hFile) ;
		return NULL ;
	}

	// Allocate memory for the BITMAPINFO structure & read it in
	dwInfoSize = bmfh.bfOffBits - sizeof (BITMAPFILEHEADER) ;
	pbmi = static_cast<BITMAPINFO*>(malloc (dwInfoSize)) ;
	bSuccess = ReadFile (hFile, pbmi, dwInfoSize, &dwBytesRead, NULL) ;
	if (!bSuccess || (dwBytesRead != dwInfoSize))
	{
		free (pbmi) ;
		CloseHandle (hFile) ;
		return NULL ;
	}

	// Create the DIB Section
	hBitmap = CreateDIBSection (NULL, pbmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&pBits), NULL, 0) ;
	if (hBitmap == NULL)
	{
		free (pbmi) ;
		CloseHandle (hFile) ;
		return NULL ;
	}

	// Read in the bitmap bits
	ReadFile (hFile, pBits, bmfh.bfSize - bmfh.bfOffBits, &dwBytesRead, NULL) ;
	free (pbmi) ;
	CloseHandle (hFile) ;

	return hBitmap ;
}


}