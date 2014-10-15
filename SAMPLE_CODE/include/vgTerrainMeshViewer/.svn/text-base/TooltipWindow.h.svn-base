/****************************************************************************
TooltipWindow.h : Header file for the CTooltipWindow class
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


// CTooltipWindow

class CTooltipWindow : public CWnd
{
    DECLARE_DYNAMIC(CTooltipWindow)

public:
    struct PointData
    {
        CPoint Point;
        COLORREF Colour;
        PointData() { Colour = CLR_NONE; }
    };

    CTooltipWindow();
    virtual ~CTooltipWindow();

    bool Activate(bool bActivate);
    bool Create(CWnd *pParent);
    bool SetHex(bool bHex);
    void Update();

protected:
    bool Hexadecimal;
    PointData Data;
    CPoint LastImagePoint;
    std::tstring Text;
    CFont Font;

    void Show(CPoint pt);

    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
protected:
    void SetFont(void);
};


