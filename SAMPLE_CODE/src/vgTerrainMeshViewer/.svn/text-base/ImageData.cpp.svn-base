/****************************************************************************
ImageData.cpp : Implementation file for the CImageData class
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


#include <vgStableHeaders.h>
#include "ImageViewerApp.h"
#include "ImageData.h"

#include "pja_dc.h"

#include <shlwapi.h>

size_t CImageData::MemUsage = 0;

// default c'tor
CImageData::CImageData()
: pCriticalSection(NULL)
, pData(NULL)
, Bitmap(NULL)
, DataSize(0)
, BPP(0)
{
}

// copy c'tor
CImageData::CImageData(const CImageData &ImageData)
: pCriticalSection(NULL)
, pData(NULL)
, Bitmap(NULL)
, DataSize(0)
, BPP(0)
{
    *this = ImageData;
}

CImageData::CImageData(HBITMAP hBitmap, WORD Bits)
: pCriticalSection(NULL)
, pData(NULL)
, Bitmap(NULL)
, DataSize(0)
, BPP(Bits)
{
    BITMAP bm;
    if (GetObject(hBitmap, sizeof(BITMAP), &bm))
    {
        pCriticalSection = new CCriticalSection;
        ULONG *pRef = new ULONG(1);
        pData = (LPBYTE)pRef;
        Bitmap = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        DataSize = ((bm.bmWidth * bm.bmBitsPixel +31) & (~31)) / 8 * bm.bmHeight;

        MemUsage += GetSize();
    }
}

// d'tor
CImageData::~CImageData()
{
    DeleteData();
}

// copy the data from another CImageData object
CImageData& CImageData::operator =(const CImageData &ImageData)
{
    DeleteData();

    if (NULL != ImageData.pCriticalSection)
    {
        CSingleLock(ImageData.pCriticalSection, TRUE);
        if (NULL != ImageData.pData)
        {
            pData = ImageData.pData;
            DataSize = ImageData.DataSize;
            pCriticalSection = ImageData.pCriticalSection;
            Bitmap = ImageData.Bitmap;
            BPP = ImageData.BPP;

            IncrementReferenceCount();
        }
    }

    return *this;
}

// Get the data that was sent from the ImageViewer.dll.
// See CRecieverWindow::OnCopyData() and see the SendBitmapToViewer()
// function in the Viewer Library project.
bool CImageData::CopyData(const size_t &Size, LPBYTE Data)
{
    ASSERT (Size > 0);
    ASSERT (NULL != Data);

    bool ret = false;

    if (WAIT_OBJECT_0 != WaitForSingleObject(theApp.MemoryEvent, 0))
    {
        // out of memory, we cannot copy the image data
        return ret;
    }

    DeleteData();

    if (0 >= Size || NULL == Data)
    {
        return ret;
    }

    try
    {
        DataSize = Size;
        pData = new BYTE[sizeof(ULONG) + DataSize];                 // Include space for a reference counter
        pCriticalSection = new CCriticalSection;

        *reinterpret_cast<PULONG>(pData) = 0;                       // Set the reference counter to zero
        if (memcpy_s(pData + sizeof(ULONG), Size, Data, Size) == 0) // copy the image data into the buffer
        {
            ret = true;
            IncrementReferenceCount();
        }
    }
    catch (CMemoryException *me)
    {
        theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, IDS_OUTOFMEMORY, 0);
        theApp.MemoryEvent.ResetEvent();
        TRACE("\n***************************  Out of Memory  *****************************\n\n");
        me->ReportError();
        me->Delete();
        ret = false;
    }

    if (!ret)
    {
        // unable to copy data, clean up
        delete[] pData;
        pData = NULL;
        DataSize = 0;

        delete pCriticalSection;
        pCriticalSection = NULL;
    }

    if (ret)
    {
        MemUsage += GetSize();
        if (MemUsage / 1024 >= theApp.MaximumMemoryUsage)
        {
            theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, IDS_OUTOFMEMORY, 0);
            theApp.MemoryEvent.ResetEvent();
            TRACE(_T("Viewer Application - CImageData::OnCopyData: Memory limit reached\n"));
        }
    }

    return ret;
}

// cleanup
void CImageData::DeleteData()
{
    if (NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);

        if (NULL != pData)
        {
            PULONG pReferenceCounter = reinterpret_cast<PULONG>(pData);
            --*pReferenceCounter;
            if (0 == *pReferenceCounter)
            {
                delete[] pData;
                SingleLock.Unlock();
                delete pCriticalSection;

                if (NULL != Bitmap)
                {
                    DeleteObject(Bitmap);
                }

                MemUsage -= GetSize();
            }
        }
    }

    pData = NULL;
    DataSize = 0;
    pCriticalSection = NULL;
    Bitmap = NULL;
    BPP = 0;
}

// increase the reference counter
void CImageData::IncrementReferenceCount()
{
    if (NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            ++*reinterpret_cast<PULONG>(pData);
        }
    }
}

DWORD CImageData::GetProcessID() const
{
    DWORD ProcessID = 0;

    if (NULL == Bitmap && NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            ProcessID = *reinterpret_cast<DWORD *>(pData + sizeof(ULONG));      // ProcessID is the first DWORD after the reference counter
        }
    }

    return ProcessID;
}

RECT CImageData::GetRegionRect() const
{
    RECT RegionRect = {0};

    if (NULL == Bitmap && NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);

        if (NULL != pData)
        {
            // RegionRect will be empty if there is no region in this image
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD);                 // Skip over the reference counter and the processID
            LPRECT Rect = reinterpret_cast<LPRECT>(ptr);                        // Get the region rectangle
            memcpy_s(&RegionRect, sizeof(RECT), Rect, sizeof(RECT));
        }
    }

    return RegionRect;
}



std::tstring CImageData::GetSourceFilePath() const
{
    std::tstring ret;

    if (NULL == Bitmap && NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);

        if (NULL != pData)
        {
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD) + sizeof(RECT);  // Skip over the reference counter, ProcessID and the region rectangle
            std::wstring Text = reinterpret_cast<LPWSTR>(ptr);                  // Get the text
            std::wstring::size_type end = Text.find(L"\n");                     // The file path is the first line

            ret = CW2CT(Text.substr(0, end).c_str());
        }
    }

    return ret;
}

std::tstring CImageData::GetSourceFile() const
{
    TCHAR Buffer[_MAX_PATH] = {0};
    _tcscpy_s(Buffer, _MAX_PATH, GetSourceFilePath().c_str());
    PathStripPath(Buffer);

    return std::tstring(Buffer);
}

std::tstring CImageData::GetSourcePath() const
{
    TCHAR Buffer[_MAX_PATH] = {0};
    _tcscpy_s(Buffer, _MAX_PATH, GetSourceFilePath().c_str());
    PathRemoveFileSpec(Buffer);
    PathAddBackslash(Buffer);

    return std::tstring(Buffer);
}


std::tstring CImageData::GetSourceLine() const
{
    std::tstring ret;

    if (NULL == Bitmap && NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD) + sizeof(RECT);  // Skip over the reference counter, ProcessID and the region rectangle
            std::wstring Text = reinterpret_cast<LPWSTR>(ptr);                  // Get the text
            std::wstring::size_type start = Text.find(L"\n") + 1;               // Skip over the file path
            std::wstring::size_type end = Text.find(L"\n", start);              // The line number is the second line

            ret = CW2CT(Text.substr(start, end - start).c_str());
        }
    }

    return ret;
}

std::tstring CImageData::GetSourceFunction() const
{
    std::tstring ret;

    if (NULL == Bitmap && NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD) + sizeof(RECT);  // Skip over the reference counter, ProcessID and the region rectangle
            std::wstring Text = reinterpret_cast<LPWSTR>(ptr);                  // Get the text
            std::wstring::size_type start = Text.find(L"\n") + 1;               // Skip over the file path
            start = Text.find(L"\n", start) + 1;                                // Skip over the line number
            std::wstring::size_type end = Text.find(L"\n", start);              // The function name is the third line

            ret = CW2CT(Text.substr(start, end - start).c_str());
        }
    }

    return ret;
}

std::tstring CImageData::GetTime() const
{
    std::tstring ret;

    if (NULL == Bitmap && NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD) + sizeof(RECT);  // Skip over the reference counter, ProcessID and the region rectangle
            std::wstring Text = reinterpret_cast<LPWSTR>(ptr);                  // Get the text
            std::wstring::size_type start = Text.find(L"\n") + 1;               // Skip over the file path
            start = Text.find(L"\n", start) + 1;                                // Skip over the line number
            start = Text.find(L"\n", start) + 1;                                // Skip over the function name
            std::wstring::size_type end = Text.find(L"\n", start);              // The time is the fourth line

            ret = CW2CT(Text.substr(start, end - start).c_str());
        }
    }

    return ret;
}

std::tstring CImageData::GetText() const
{
    std::tstring ret;

    if (NULL == Bitmap && NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD) + sizeof(RECT);  // Skip over the reference counter, ProcessID and the region rectangle
            std::wstring Text = reinterpret_cast<LPWSTR>(ptr);                  // Get the text
            std::wstring::size_type start = Text.find(L"\n") + 1;               // Skip over the file path
            start = Text.find(L"\n", start) + 1;                                // Skip over the line number
            start = Text.find(L"\n", start) + 1;                                // Skip over the function name
            start = Text.find(L"\n", start) + 1;                                // Skip over the time

            ret = CW2CT(Text.substr(start).c_str());                            // The text is the remaining lines

            std::tstring::size_type finder = ret.find_first_of(_T("\r\n"));     // change any <CR>s or <LF>s to <CRLF>s for proper display in edit controls
            while (finder != std::tstring::npos)
            {
                if (ret[finder] == _T('\n'))
                {
                    if (finder == 0 || ret[finder - 1] != _T('\r'))
                    {
                        ret.insert(finder++, _T("\r"));
                    }
                }
                else if (ret[++finder] != _T('\n'))
                {
                    ret.insert(finder++, _T("\n"));
                }

                finder = ret.find_first_of(_T("\r\n"), ++finder);
            }
        }
    }

    return ret;
}

CBitmapInfoHeader CImageData::GetBitmapInfoHeader() const
{
    CBitmapInfoHeader BitmapInfoHeader;

    if (NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);

        if (NULL != Bitmap)
        {
            BITMAP b;
            if (GetObject(Bitmap, sizeof(BITMAP), &b))
            {
                BitmapInfoHeader.biWidth = b.bmWidth;
                BitmapInfoHeader.biHeight = b.bmHeight;
                BitmapInfoHeader.biBitCount = 0 == BPP ? b.bmBitsPixel : BPP;
            }
        }
        else if (NULL != pData)
        {
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD) + sizeof(RECT);  // Skip over the reference counter, ProcessID and the region rectangle
            LPWSTR Text = reinterpret_cast<LPWSTR>(ptr);                        // The text is next
            ptr += (wcslen(Text) + 1) * sizeof(WCHAR);                          // Skip over all the text

            LPBITMAPINFO pBitmapInfo = reinterpret_cast<LPBITMAPINFO>(ptr);     // The BITMAPINFO structure is after the text

            BitmapInfoHeader = pBitmapInfo->bmiHeader;
        }
    }

    return BitmapInfoHeader;
}

HBITMAP CImageData::GetBitmap() const
{
    if (NULL != Bitmap)
    {
        HBITMAP ret = (HBITMAP)CopyImage(Bitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        return ret;
    }

    HBITMAP hBitmap = NULL;

    if (NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            LPBYTE ptr = pData + sizeof(ULONG) + sizeof(DWORD) + sizeof(RECT);  // Skip over the reference counter, ProcessID and the region rectangle
            LPWSTR Text = reinterpret_cast<LPWSTR>(ptr);                        // The text is next
            ptr += (wcslen(Text) + 1) * sizeof(WCHAR);                          // Skip over all the text

            LPBITMAPINFO pBitmapInfo = reinterpret_cast<LPBITMAPINFO>(ptr);     // The BITMAPINFO structure is after the text
            ptr += sizeof(BITMAPINFO);

            int ColourTableSize = pBitmapInfo->bmiHeader.biBitCount < 16 ? sizeof(RGBQUAD) * 256 : 0;
            LPRGBQUAD pColourTable = NULL;
            if (0 != ColourTableSize)
            {
                pColourTable = reinterpret_cast<LPRGBQUAD>(ptr);                // If there is a colour table it is after the BITMAPINFO structure
                ptr += ColourTableSize;
            }

            pja::CCompatibleDC DC;
            LPVOID dummy = NULL;
            hBitmap = CreateDIBSection(DC, pBitmapInfo, DIB_RGB_COLORS, &dummy, NULL, 0);

            if (NULL != hBitmap)
            {
                if (NULL != pColourTable)
                {
                    SetDIBColorTable(DC, 0, 1 << pBitmapInfo->bmiHeader.biBitCount, pColourTable);
                }

                if (!SetDIBits(DC, hBitmap, 0, pBitmapInfo->bmiHeader.biHeight, ptr, pBitmapInfo, DIB_RGB_COLORS))  // Last is the bitmap bits
                {
                    DeleteObject(hBitmap);
                    hBitmap = NULL;
                }
            }
        }
    }

    return hBitmap;
}

// write the data into a CArchive. See CImageViewerDoc::Serialize()
void CImageData::SaveData(CArchive &ar)
{
    if (NULL != pCriticalSection)
    {
        CSingleLock SingleLock(pCriticalSection, TRUE);
        if (NULL != pData)
        {
            ar << DataSize;
            ar.Write(pData + sizeof(ULONG), DataSize);
        }
    }
}

// read the data from a CArchive. See CImageViewerDoc::Serialize()
bool CImageData::ReadData(CArchive &ar)
{
    bool ret = false;

    if (WAIT_OBJECT_0 != WaitForSingleObject(theApp.MemoryEvent, 0))
    {
        // out of memory, we cannot copy the image data
        return ret;
    }

    DeleteData();

    ar >> DataSize;
    if (0 != DataSize)
    {
        try
        {
            pData = new BYTE[DataSize + sizeof(ULONG)];
            memset(pData, 0, DataSize + sizeof(ULONG));
            pCriticalSection = new CCriticalSection;

            if (ar.Read(pData + sizeof(ULONG), (UINT)DataSize) == DataSize)
            {
                ret = true;
                IncrementReferenceCount();
            }
            else
            {
                AfxThrowArchiveException(CArchiveException::endOfFile);
            }
        }
        catch (CMemoryException *me)
        {
            theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, IDS_OUTOFMEMORY, 0);
            theApp.MemoryEvent.ResetEvent();
            TRACE("\n***************************  Out of Memory  *****************************\n\n");
            me->ReportError();
            me->Delete();
            ret = false;
        }
    }

    if (!ret)
    {
        delete[] pData;
        pData = NULL;
        DataSize = 0;

        delete pCriticalSection;
        pCriticalSection = NULL;
    }

    if (ret)
    {
        MemUsage += GetSize();
        if (MemUsage / 1024 >= theApp.MaximumMemoryUsage)
        {
            theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, IDS_OUTOFMEMORY, 0);
            theApp.MemoryEvent.ResetEvent();
            ret = false;
        }
    }

    return ret;
}

size_t CImageData::GetSize(void) const
{
    // Image data + reference counter + this + critical section object
    return DataSize + sizeof(ULONG) + sizeof(CImageData) + sizeof(CCriticalSection);
}
