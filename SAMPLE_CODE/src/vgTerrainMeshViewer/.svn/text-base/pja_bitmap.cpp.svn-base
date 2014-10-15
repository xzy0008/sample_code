/****************************************************************************
pja_bitmap.cpp - Implementation file for Win32 HBITMAP wrapper class
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
#include "pja_bitmap.h"
#include <crtdbg.h>

// Default c'tor
pja::CBitmap::CBitmap()
: hBitmap(NULL)
{
    memset(&Bitmap, 0, sizeof(BITMAP));
}

// Construct a CBitmap from an HBITMAP
// The HBITMAP that is supplied here will be destroyed when this
// CBitmap object is deleted or goes out of scope. If you do not
// want the original bitmap to be destroyed set the MakeCopy
// parameter to true.
pja::CBitmap::CBitmap(HBITMAP bmp, bool MakeCopy /*=false*/)
: hBitmap(NULL)
{
    memset(&Bitmap, 0, sizeof(BITMAP));

    if (MakeCopy)
    {
        *this = bmp;
    }
    else
    {
        hBitmap = bmp;

        if (NULL != hBitmap)
        {
            if (0 == GetObject(hBitmap, sizeof(BITMAP), &Bitmap))
            {
                memset(this, 0, sizeof(CBitmap));
            }
        }
    }
}

// Construct a CBitmap by loading a bitmap from resources
pja::CBitmap::CBitmap(UINT ID, HMODULE hModule)
: hBitmap(NULL)
{
    _ASSERT (0 != ID);

    memset(&Bitmap, 0, sizeof(BITMAP));

    if (NULL == hModule)
    {
        hModule = GetModuleHandle(NULL);
    }

    hBitmap = reinterpret_cast<HBITMAP>(LoadImage(hModule,
                                                  MAKEINTRESOURCE(ID),
                                                  IMAGE_BITMAP,
                                                  0, 0,
                                                  LR_DEFAULTCOLOR));

    if (NULL != hBitmap)
    {
        if (0 == GetObject(hBitmap, sizeof(BITMAP), &Bitmap))
        {
            memset(this, 0, sizeof(CBitmap));
        }
    }
}

// Construct a CBitmap by loading a bitmap from resources
pja::CBitmap::CBitmap(LPCTSTR Name, HMODULE hModule)
: hBitmap(NULL)
{
    _ASSERT (NULL != Name);

    memset(&Bitmap, 0, sizeof(BITMAP));

    if (NULL == hModule)
    {
        hModule = GetModuleHandle(NULL);
    }

    hBitmap = reinterpret_cast<HBITMAP>(LoadImage(hModule,
                                                  Name,
                                                  IMAGE_BITMAP,
                                                  0, 0,
                                                  LR_DEFAULTCOLOR));
    if (NULL != hBitmap)
    {
        if (0 == GetObject(hBitmap, sizeof(BITMAP), &Bitmap))
        {
            memset(this, 0, sizeof(CBitmap));
        }
    }
}

// Construct a memory bitmap that is compatible with the supplied device context
pja::CBitmap::CBitmap(HDC hdc, int width, int height)
: hBitmap(NULL)
{
    _ASSERT (width > 0 && height > 0);

    HDC TempDC = hdc;

    if (NULL == hdc)
    {
        TempDC = GetDC(NULL);
    }

    ZeroMemory(&Bitmap, sizeof(BITMAP));
    hBitmap = CreateCompatibleBitmap(TempDC, width, height);

    if (NULL != hBitmap)
    {
        if (0 == GetObject(hBitmap, sizeof(BITMAP), &Bitmap))
        {
            memset(this, 0, sizeof(CBitmap));
        }
    }

    if (NULL == hdc)
    {
        ReleaseDC(NULL, TempDC);
    }
}

// Clean up the HBITMAP handle
pja::CBitmap::~CBitmap()
{
    DeleteObject();
}

void pja::CBitmap::DeleteObject()
{
    ::DeleteObject(hBitmap);
    hBitmap = NULL;

    ZeroMemory(&Bitmap, sizeof(BITMAP));
}

// Get the pixel width of the bitmap
long pja::CBitmap::Width() const
{
    return Bitmap.bmWidth;
}

// Get the pixel height of the bitmap
long pja::CBitmap::Height() const
{
    return Bitmap.bmHeight;
}

// Get the colour depth of the bitmap
unsigned short pja::CBitmap::BitsPixel() const
{
    return Bitmap.bmBitsPixel;
}

// copy the supplied HBITMAP
pja::CBitmap &pja::CBitmap::operator =(const HBITMAP &hbmp)
{
    DeleteObject();
    hBitmap = reinterpret_cast<HBITMAP>(CopyImage(hbmp, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION));

    if (NULL != hBitmap)
    {
        if (0 == GetObject(hBitmap, sizeof(BITMAP), &Bitmap))
        {
            memset(this, 0, sizeof(CBitmap));
        }
    }

    return *this;
}

pja::CBitmap &pja::CBitmap::operator =(const pja::CBitmap &Bitmap)
{
    return *this = Bitmap.hBitmap;
}

LPCRECT pja::CBitmap::Rect()
{
    SetRect(&Rectangle, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight);
    return &Rectangle;
}