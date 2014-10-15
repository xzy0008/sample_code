/****************************************************************************
BitmapInfoHeader.h : Header file for the CBitmapInfoHeader class
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

// add a copy c'tor and operator = to the BITMAPINFOHEADER structure

class CBitmapInfoHeader : public BITMAPINFOHEADER
{
public:
    CBitmapInfoHeader()
    {
        memset(this, 0, sizeof(BITMAPINFOHEADER));
    }

    CBitmapInfoHeader(const BITMAPINFOHEADER &bmi)
    {
        *this = bmi;
    }

    CBitmapInfoHeader &operator =(const BITMAPINFOHEADER &bmi)
    {
        memcpy_s(this, sizeof(BITMAPINFOHEADER), &bmi, sizeof(BITMAPINFOHEADER));
        return *this;
    }
};
