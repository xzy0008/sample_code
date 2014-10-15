/****************************************************************************
ChildStatusBar.cpp : Implementation file for the CChildStatusBar class
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
#include "ChildStatusBar.h"
#include "BitmapInfoHeader.h"
#include "Resource.h"

#include "pja_dc.h"
#include "pja_bitmap.h"
#include "pja_format.h"


// CChildStatusBar

IMPLEMENT_DYNAMIC(CChildStatusBar, CStatusBar)

CChildStatusBar::CChildStatusBar()
{
}

CChildStatusBar::~CChildStatusBar()
{
}


BEGIN_MESSAGE_MAP(CChildStatusBar, CStatusBar)
END_MESSAGE_MAP()


// CChildStatusBar message handlers

DWORD CChildStatusBar::TogglePane(ChildStatusBarPane Pane)
{
    Panes ^= Pane;

    theApp.WriteProfileInt(_T("Settings"), _T("Child Statusbar Panes"), Panes);
    AfxGetMainWnd()->SendMessageToDescendants(WMU_UPDATECHILDSTATUSBAR, Panes);

    return Panes;
}

LRESULT CChildStatusBar::OnUpdateStatusBar(WPARAM wp, LPARAM)
{
    if (wp == -1)
    {
        Panes = theApp.GetProfileInt(_T("Settings"), _T("Child Statusbar Panes"), CChildStatusBar::CSBP_NONE);
    }
    else
    {
        Panes = wp;
    }

    if (Panes != CSBP_NONE)
    {
        std::vector<UINT> Indicators;
        Indicators.reserve(6);

        Indicators.push_back(ID_SEPARATOR);     // Status bar text

        if (Panes & CSBP_TIME)
        {
            Indicators.push_back(ID_SEPARATOR); // Image creation date and time
        }

        if (Panes & CSBP_FILE)
        {
            Indicators.push_back(ID_SEPARATOR); // Source file name
        }

        if (Panes & CSBP_LINE)
        {
            Indicators.push_back(ID_SEPARATOR); // Source file line
        }

        if (Panes & CSBP_METHOD)
        {
            Indicators.push_back(ID_SEPARATOR); // Source function name
        }

        if (Panes & CSBP_SIZE)
        {
            Indicators.push_back(ID_SEPARATOR); // Dimensions of image in pixels
        }

        SetIndicators(&Indicators[0], Indicators.size());
    }

    return Panes;
}

void CChildStatusBar::UpdatePaneText(CImageData *pImageData)
{
    // Sanity check, no use doing anything if we have no data or no status bar
    if (NULL == pImageData || CSBP_NONE == Panes)
    {
        return;
    }

    int CurrentPane = 0;

    UINT nID, nStyle;
    int cxWidth;
    std::tstring Text;

    if (Panes & CSBP_TEXT)
    {
        CRect RegionRect = pImageData->GetRegionRect();
        if (!RegionRect.IsRectEmpty())
        {
            pja::CFormat cf;
            Text = cf.MakeMessage(NULL, IDS_REGION_STATUS, 4,
                                  cf.TS(RegionRect.left),
                                  cf.TS(RegionRect.top),
                                  cf.TS(RegionRect.right),
                                  cf.TS(RegionRect.bottom));
        }
        Text += pImageData->GetText();
    }

    GetPaneInfo(CurrentPane, nID, nStyle, cxWidth);
    cxWidth = min(GetPaneWidth(Text), 50);
    SetPaneInfo(CurrentPane, nID, SBPS_STRETCH, cxWidth);
    SetPaneText(CurrentPane++, Text.c_str());

    if (Panes & CSBP_TIME)
    {
        Text = pImageData->GetTime();
        GetPaneInfo(CurrentPane, nID, nStyle, cxWidth);
        SetPaneInfo(CurrentPane, nID, nStyle, GetPaneWidth(Text));
        SetPaneText(CurrentPane, Text.c_str());
        ++CurrentPane;
    }

    if (Panes & CSBP_FILE)
    {
        Text = pImageData->GetSourceFile();
        GetPaneInfo(CurrentPane, nID, nStyle, cxWidth);
        SetPaneInfo(CurrentPane, nID, nStyle, GetPaneWidth(Text));
        SetPaneText(CurrentPane, Text.c_str());
        ++CurrentPane;
    }

    if (Panes & CSBP_LINE)
    {
        Text = pImageData->GetSourceLine();
        GetPaneInfo(CurrentPane, nID, nStyle, cxWidth);
        SetPaneInfo(CurrentPane, nID, nStyle, GetPaneWidth(Text));
        SetPaneText(CurrentPane, Text.c_str());
        ++CurrentPane;
    }

    if (Panes & CSBP_METHOD)
    {
        Text = pImageData->GetSourceFunction();
        GetPaneInfo(CurrentPane, nID, nStyle, cxWidth);
        SetPaneInfo(CurrentPane, nID, nStyle, GetPaneWidth(Text));
        SetPaneText(CurrentPane, Text.c_str());
        ++CurrentPane;
    }

    if (Panes & CSBP_SIZE)
    {
        CBitmapInfoHeader BitmapInfoHeader(pImageData->GetBitmapInfoHeader());
        pja::CFormat cf;
        Text = cf.MakeMessage(_T("%1 x %2"), 2,
                              cf.TS(BitmapInfoHeader.biWidth),
                              cf.TS(BitmapInfoHeader.biHeight));
        GetPaneInfo(CurrentPane, nID, nStyle, cxWidth);
        SetPaneInfo(CurrentPane, nID, nStyle, GetPaneWidth(Text));
        SetPaneText(CurrentPane, Text.c_str());
        ++CurrentPane;
    }
}

int CChildStatusBar::GetPaneWidth(std::tstring &Text)
{
    // truncate the text at the first newline character
    std::tstring::size_type end = Text.find_first_of(_T("\r\n"));
    if (end != std::tstring::npos)
    {
        Text = Text.substr(0, end);
    }

    // handle an empty string
    if (Text.empty())
    {
        Text = _T("   ");  // to ensure any residuals get erased
        return 1;
    }

    // Calculate the required width of the text pane
    pja::CClientDC DC(*this);
    CRect rc(0, 0, 0, 0);
    CFont *pFont = GetFont();
    SelectObject(DC, NULL == pFont ? GetStockObject(ANSI_VAR_FONT) : *pFont);
    DrawText(DC, Text.c_str(), -1, rc, DT_CALCRECT | DT_SINGLELINE | DT_NOPREFIX);
    return rc.Width();
}
