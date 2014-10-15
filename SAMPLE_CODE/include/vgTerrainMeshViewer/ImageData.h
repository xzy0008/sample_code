/****************************************************************************
ImageData.h : Header file for the CImageData class
written by PJ Arends
pja@telus.net

For updates check http://www.codeproject.com/tools/imageviewer.asp

-----------------------------------------------------------------------------
This code is provided as is, with no warranty as to it's suitability or usefulness
in any application in which it may be used.

This code may be used in any way you desire. This file may be redistributed by any
means as long as it is not sold for profit, and providing that this notice and the
author's name are included. Any modifications not made by the original author should
be clearly marked as such to remove any confusion between the original version and
any other versions.

If any bugs are found and fixed, a note to the author explaining the problem and
fix would be nice.
-----------------------------------------------------------------------------
****************************************************************************/

#pragma once

#include "tstl.h"
#include "BitmapInfoHeader.h"

class CImageData
{
private:
    size_t DataSize;                                // size of the data
    LPBYTE pData;                                   // pointer to the data
    CCriticalSection *pCriticalSection;             // controls access to the data

    HBITMAP Bitmap;
    WORD BPP;

    static size_t MemUsage;                         // running total of memory used by all CImageData objects

protected:
    void DeleteData();                              // decrements reference counter, deletes pointers when zero
    void IncrementReferenceCount();                 // increments reference counter
    size_t GetSize() const;                         // returns the number of bytes used by this CImageData object

public:
    CImageData();                                   // default c'tor
    CImageData(const CImageData &);                 // copy c'tor - calls operator =(const CImageData &)
    CImageData(HBITMAP, WORD Bits = 0);             // Create from an HBITMAP

    ~CImageData();                                  // d'tor - calls DeleteData()

    CImageData& operator = (const CImageData &);    // assignment operator - increments reference counter
    bool CopyData(const size_t &, LPBYTE);          // makes a copy of the supplied data

    void SaveData(CArchive &ar);                    // saves the image data into an archive
    bool ReadData(CArchive &ar);                    // reads the image data from an archive

    HBITMAP GetBitmap() const;                      // handle to the bitmap - call DeleteObject() when you are done with it.
    DWORD GetProcessID() const;                     // the process ID of the app that generated the image
    RECT GetRegionRect() const;                     // the bounding rectangle coordinates of the contained region
    CBitmapInfoHeader GetBitmapInfoHeader() const;  // the BITMAPINFOHEADER that describes the contained image
    std::tstring GetSourceFilePath() const;         // the complete path of the source file that contains the Show* macro
    std::tstring GetSourceFile() const;
    std::tstring GetSourcePath() const;
    std::tstring GetSourceLine() const;             // line number in the source file where the Show* macro is located
    std::tstring GetSourceFunction() const;
    std::tstring GetTime() const;                   // system time that the image was generated
    std::tstring GetText() const;                   // descriptive text associated with the image

    static size_t GetMemUsage()                     // retrieves the total memory used by all CImageData objects
    {
        return MemUsage;
    }
};
