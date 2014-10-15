/****************************************************************************
MainStatusBar.cpp : Implementation file for the CMainStatusBar class
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
#include "MainStatusBar.h"
#include "ImageViewerApp.h"
#include "pja_bitmap.h"
#include "pja_dc.h"
#include "pja_format.h"

//#define ACTIVATE_VIEWER
#include <ImageViewer.h>

// CMainStatusBar

IMPLEMENT_DYNAMIC(CMainStatusBar, CStatusBar)

CMainStatusBar::CMainStatusBar()
{
}

CMainStatusBar::~CMainStatusBar()
{
}

BEGIN_MESSAGE_MAP(CMainStatusBar, CStatusBar)
    ON_MESSAGE(WM_THEMECHANGED, &CMainStatusBar::OnThemeChanged)
END_MESSAGE_MAP()

// CMainStatusBar message handlers
BOOL CMainStatusBar::Create(CWnd *pParent)
{
    BOOL ret = CStatusBar::CreateEx(pParent);

    if (FALSE != ret)
    {
        UpdateStatusBarPanes();
    }

    return ret;
}

void CMainStatusBar::UpdateStatusBarPanes()
{
    std::vector<UINT> Indicators;
    Indicators.reserve(4);
    Indicators.push_back(ID_SEPARATOR);         // Status bar text
    Indicators.push_back(ID_INDICATOR_MEM);     // Memory usage indicator
    Indicators.push_back(ID_INDICATOR_SCRL);    // Scroll lock indicator

    SetIndicators(&Indicators[0], Indicators.size());

    NONCLIENTMETRICS ncm = {0};
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0) != 0)
    {
        Font.DeleteObject();
        Font.CreateFontIndirect(&ncm.lfStatusFont);
    }

    UINT nID, nStyle;
    int cxWidth;
    GetPaneInfo(0, nID, nStyle, cxWidth);
    SetPaneInfo(0, nID, SBPS_STRETCH, 100);     // minimum width of 100 pixels
    GetPaneInfo(1, nID, nStyle, cxWidth);
    SetPaneInfo(1, nID, SBPS_OWNERDRAW, 100);   // 100 pixels, 1 pixel for each percentage point
}

LRESULT CMainStatusBar::OnThemeChanged(WPARAM, LPARAM)
{
    LRESULT ret = Default();

    UpdateStatusBarPanes();

    return ret;
}

void CMainStatusBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (1 == lpDrawItemStruct->itemID)
    {
        CRect rcItem(lpDrawItemStruct->rcItem);

        if (rcItem.Height() > 0 && rcItem.Width() > 0)
        {
            HDC hDC = lpDrawItemStruct->hDC;
            CRect TextRect(0, 0, 100, rcItem.Height());

            pja::CBitmap BackGroundBitmap(hDC, TextRect.Width(), TextRect.Height());;
            pja::CCompatibleDC BackGroundDC(hDC);
            SelectObject(BackGroundDC, BackGroundBitmap);
            BitBlt(BackGroundDC, 0, 0, rcItem.Width(), rcItem.Height(), hDC, rcItem.left, rcItem.top, SRCCOPY);
            ShowDC2(BackGroundDC, _T("BackGroundDC with the status bar background"));

            size_t memusage = *(size_t*)(lpDrawItemStruct->itemData);
            int percent = (int)((double)memusage / (double)theApp.MaximumMemoryUsage * TextRect.Width());

            if (percent > 0)
            {
                BLENDFUNCTION bf = {0};
                bf.SourceConstantAlpha = 64;

                // Load the progess bar bitmap into ProgressBarDC
                pja::CBitmap ProgressBarBitmap(IDB_MEMUSAGE);
                pja::CCompatibleDC ProgressBarDC(hDC);
                SelectObject(ProgressBarDC, ProgressBarBitmap);
                ShowDC2(ProgressBarDC, _T("ProgressBarDC with the progress bar bitmap"));

                // Blend the progress bar bitmap onto the background
                AlphaBlend(BackGroundDC, 0, 0, percent, TextRect.Height(),
                           ProgressBarDC, 0, 0, percent, ProgressBarBitmap.Height(), bf);
                ShowDC2(BackGroundDC, _T("BackGroundDC after the alphablend"));
            }

            pja::CFormat cf;
            std::tstring Text = cf.MakeMessage(NULL, ID_INDICATOR_MEM, 1, cf.TS(memusage));

            SelectObject(BackGroundDC, Font);
            SetBkMode(BackGroundDC, TRANSPARENT);
            DrawText(BackGroundDC, Text.c_str(), -1, TextRect, DT_CENTER | DT_VCENTER);
            ShowDC2(BackGroundDC, _T("BackGroundDC after the DrawText"));

            // Copy the final progress bar to the status bar
            BitBlt(hDC, rcItem.left, rcItem.top, rcItem.Width(), rcItem.Height(), BackGroundDC, 0, 0, SRCCOPY);
        }
    }
}
