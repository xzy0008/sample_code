/****************************************************************************
ChildStatusBar.h : Header file for the CChildStatusBar class
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

#include "ImageData.h"

// CChildStatusBar

class CChildStatusBar : public CStatusBar
{
    DECLARE_DYNAMIC(CChildStatusBar)

public:
    CChildStatusBar();
    virtual ~CChildStatusBar();

    enum ChildStatusBarPane
    {
        CSBP_NONE   = 0x00,
        CSBP_TEXT   = 0x01,
        CSBP_TIME   = 0x02,
        CSBP_FILE   = 0x04,
        CSBP_LINE   = 0x08,
        CSBP_METHOD = 0x10,
        CSBP_SIZE   = 0x20
    };

    DWORD TogglePane(ChildStatusBarPane Pane);
    DWORD GetPanes() { return Panes; }

    virtual LRESULT OnUpdateStatusBar(WPARAM, LPARAM);
    void UpdatePaneText(CImageData *pImageData);

protected:
    int GetPaneWidth(std::tstring &Text);
    DWORD Panes;

    DECLARE_MESSAGE_MAP()
};


