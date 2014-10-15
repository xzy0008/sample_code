/****************************************************************************
pja_dc.h - Header file for win32 device context classes
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
    // CBaseDC class is the class all other DC classes are derived
    // from. It has a protected c'tor so users can not use it directly.
    // The HDC() operator allows these classes to be used the same
    // as any HDC handle in WIN32 GDI APIs.
    // The derived classes call SaveDC() in their c'tors and RestoreDC()
    // in their d'tors to ensure all GDI objects are restored before they
    // are released or destroyed. Since the d'tors are called in the reverse
    // order of the c'tors, to ensure this works properly it is very
    // important that these device contexts are created after the GDI
    // objects that are selected into them. If not the GDI objects will
    // still be selected into the dc resulting in resource leaks.

    class CBaseDC
    {
        friend class CCompatibleDC;

    protected:
        HWND m_hWnd;
        HDC  m_hDC;
        int  m_SavedDC;
        bool m_Copied;

        CBaseDC();
        CBaseDC(HDC hDC);
        CBaseDC(CBaseDC &BaseDC);

    public:
        virtual ~CBaseDC();
        operator HDC() const;
    };

    // wraps the DC to the entire screen
    class CScreenDC : public CBaseDC
    {
    public:
        CScreenDC();
    };

    // wraps the DC to the client area of the window
    class CClientDC : public CBaseDC
    {
    public:
        CClientDC(HWND hWnd);
    };

    // wraps the DC to the entire window, borders and client area
    class CWindowDC : public CBaseDC
    {
    public:
        CWindowDC(HWND hWnd);
    };

    // wraps a paint DC to the window, calls BeginPaint() and EndPaint() APIs
    class CPaintDC : public CBaseDC
    {
    protected:
        PAINTSTRUCT m_PS;

    public:
        CPaintDC(HWND hWnd);
        virtual ~CPaintDC();
        const LPPAINTSTRUCT GetPaintStruct();
    };

    // wraps a DC that is compatible to the supplied DC.
    // the DC is created with the CreateCompatibleDC() API
    class CCompatibleDC : public CBaseDC
    {
    public:
        CCompatibleDC(const CBaseDC &dc);
        CCompatibleDC(HDC dc = NULL);
        virtual ~CCompatibleDC();
    };

    // Wraps a compatible DC that has a bitmap of the supplied size
    // selected into it.
    class CDoubleBufferDC : public CCompatibleDC
    {
    protected:
        CBaseDC m_BaseDC;
        RECT m_rc;
        HBITMAP m_Bitmap;
        int m_SavedDC;

    public:
        CDoubleBufferDC(CBaseDC &BaseDC, const RECT *prc = NULL );
        virtual ~CDoubleBufferDC();
    };
}