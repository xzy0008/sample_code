/****************************************************************************
pja_bitmap.cpp - Header file for Win32 HBITMAP wrapper class
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

#define WIN32_LEAN_AND_MEAN        // Exclude rarely-used stuff from Windows headers
#include <windows.h>

namespace pja
{
    class CBitmap
    {
        HBITMAP hBitmap;
        BITMAP  Bitmap;
        RECT    Rectangle;

    public:
        CBitmap();
        CBitmap(HBITMAP bmp, bool MakeCopy = false);
        CBitmap(UINT ID, HMODULE hModule = NULL);
        CBitmap(LPCTSTR Name, HMODULE hModule = NULL);
        CBitmap(HDC hdc, int width, int height);
        virtual ~CBitmap();
        void DeleteObject();
        long Width() const;
        long Height() const;
        unsigned short BitsPixel() const;
        LPCRECT Rect();
        CBitmap &operator =(const HBITMAP &hbmp);
        CBitmap &operator =(const CBitmap &Bitmap);
        operator HBITMAP() const { return hBitmap; }
    };
}