/****************************************************************************
pja_dc.cpp - Implementation file for win32 device context classes
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
#include "pja_dc.h"

pja::CBaseDC::CBaseDC()
: m_hWnd(NULL)
, m_hDC(NULL)
, m_SavedDC(0)
, m_Copied(false)
{
}

pja::CBaseDC::CBaseDC(HDC hDC)
: m_hWnd(NULL)
, m_hDC(hDC)
, m_SavedDC(0)
, m_Copied(false)
{
}

pja::CBaseDC::CBaseDC(pja::CBaseDC &BaseDC)
: m_hWnd(BaseDC.m_hWnd)
, m_hDC(BaseDC.m_hDC)
, m_SavedDC(0)
, m_Copied(true)
{
}

pja::CBaseDC::~CBaseDC()
{
    if (m_hDC != NULL && m_SavedDC != 0)
    {
        RestoreDC(m_hDC, m_SavedDC);
    }

    if (!m_Copied && m_hDC != NULL)
    {
        ReleaseDC(m_hWnd, m_hDC);
    }
}

pja::CBaseDC::operator HDC() const
{
    return m_hDC;
}

pja::CScreenDC::CScreenDC()
{
    m_hDC = GetDC(NULL);
}

pja::CClientDC::CClientDC(HWND hWnd)
{
    if (IsWindow(hWnd))
    {
        m_hWnd = hWnd;
        m_hDC = GetDC(m_hWnd);
        m_SavedDC = SaveDC(m_hDC);
    }
}

pja::CWindowDC::CWindowDC(HWND hWnd)
{
    if (IsWindow(hWnd))
    {
        m_hWnd = hWnd;
        m_hDC = GetWindowDC(m_hWnd);
        m_SavedDC = SaveDC(m_hDC);
    }
}

pja::CPaintDC::CPaintDC(HWND hWnd)
{
    ZeroMemory(&m_PS, sizeof(PAINTSTRUCT));

    if (IsWindow(hWnd))
    {
        m_hWnd = hWnd;
        m_hDC = BeginPaint(m_hWnd, &m_PS);
        m_SavedDC = SaveDC(m_hDC);
    }
}

pja::CPaintDC::~CPaintDC()
{
    if (m_hDC != NULL && m_SavedDC != 0)
    {
        RestoreDC(m_hDC, m_SavedDC);
        m_SavedDC = 0;
    }

    if (m_hDC != NULL)
    {
        EndPaint(m_hWnd, &m_PS);
        m_hDC = NULL;
    }
}

const LPPAINTSTRUCT pja::CPaintDC::GetPaintStruct()
{
    return &m_PS;
}

pja::CCompatibleDC::CCompatibleDC(const pja::CBaseDC &dc)
{
    HDC tempdc = CreateCompatibleDC(dc.m_hDC);
    if (tempdc != NULL)
    {
        m_hDC = tempdc;
        m_SavedDC = SaveDC(m_hDC);
        m_hWnd = dc.m_hWnd;
    }
}

pja::CCompatibleDC::CCompatibleDC(HDC dc /* = NULL */)
{
    HDC tempdc = CreateCompatibleDC(dc);
    if (tempdc != NULL)
    {
        m_hDC = tempdc;
        m_SavedDC = SaveDC(m_hDC);
    }
}

pja::CCompatibleDC::~CCompatibleDC()
{
    if (m_hDC != NULL && m_SavedDC != 0)
    {
        RestoreDC(m_hDC, m_SavedDC);
        m_SavedDC = 0;
    }

    if (m_hDC != NULL)
    {
        DeleteDC(m_hDC);
        m_hDC = NULL;
    }
}

pja::CDoubleBufferDC::CDoubleBufferDC(pja::CBaseDC &BaseDC, const RECT *prc)
: pja::CCompatibleDC(BaseDC)
, m_BaseDC(BaseDC)
, m_Bitmap(NULL)
, m_SavedDC(0)
{
    if (m_hDC != NULL)
    {
        SetRectEmpty(&m_rc);

        if (prc != NULL)
        {
            CopyRect(&m_rc, prc);

            if (m_rc.left > m_rc.right)
            {
                long temp = m_rc.left;
                m_rc.left = m_rc.right;
                m_rc.right = temp;
            }

            if (m_rc.top > m_rc.bottom)
            {
                long temp = m_rc.top;
                m_rc.top = m_rc.bottom;
                m_rc.bottom = temp;
            }
        }

        if (IsRectEmpty(&m_rc))
        {
            if (IsWindow(m_hWnd))
            {
                GetClientRect(m_hWnd, &m_rc);
            }
            else
            {
                m_rc.left = 0;
                m_rc.top = 0;
                m_rc.right = GetSystemMetrics(SM_CXSCREEN);
                m_rc.bottom = GetSystemMetrics(SM_CYSCREEN);
            }
        }

        m_Bitmap = CreateCompatibleBitmap(m_BaseDC, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top);
        if (m_Bitmap != NULL)
        {
            m_SavedDC = SaveDC(m_hDC);
            SelectObject(m_hDC, m_Bitmap);
            BitBlt(m_hDC, 0, 0, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top, m_BaseDC, m_rc.left, m_rc.top, SRCCOPY);
        }
    }
}

pja::CDoubleBufferDC::~CDoubleBufferDC()
{
    if (m_hDC != NULL && m_SavedDC != 0)
    {
        BitBlt(m_BaseDC, m_rc.left, m_rc.top, m_rc.right - m_rc.left, m_rc.bottom - m_rc.top, m_hDC, 0, 0, SRCCOPY);
        RestoreDC(m_hDC, m_SavedDC);
        m_SavedDC = 0;
        DeleteObject(m_Bitmap);
    }
}
