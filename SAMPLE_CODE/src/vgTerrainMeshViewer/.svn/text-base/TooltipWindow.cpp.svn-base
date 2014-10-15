/****************************************************************************
TooltipWindow.cpp : Implementation file for the CTooltipWindow class
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
#include "TooltipWindow.h"
#include "ImageViewerApp.h"
#include "pja_dc.h"
#include "pja_format.h"

#include <iomanip>
class Hex
{
    unsigned int _h;
public:
    Hex(unsigned int h) { _h = h; }
    friend std::tostream &operator << (std::tostream &, const Hex &);
};

std::tostream &operator << (std::tostream &s, const Hex &h)
{
    s.unsetf(std::tios::dec);
    s.setf(std::tios::hex | std::tios::uppercase);
    s << _T("0x") << std::setfill(_T('0')) << std::setw(2) << h._h;
    return s;
}

// CTooltipWindow

#define UPDATETIMER 0xFEB11965

IMPLEMENT_DYNAMIC(CTooltipWindow, CWnd)

CTooltipWindow::CTooltipWindow()
: Hexadecimal(false)
, LastImagePoint(MAXLONG, MAXLONG)
{
}

CTooltipWindow::~CTooltipWindow()
{
    if (IsWindow(*this))
    {
        DestroyWindow();
    }
}


BEGIN_MESSAGE_MAP(CTooltipWindow, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

// CTooltipWindow message handlers

bool CTooltipWindow::Create(CWnd *pParent)
{
    UINT ClassStyle = CS_PARENTDC | CS_DROPSHADOW;

    OSVERSIONINFO OSVersionInfo = {0};
    OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&OSVersionInfo);
    if (OSVersionInfo.dwMajorVersion < 5 ||
        OSVersionInfo.dwMajorVersion == 5 &&
        OSVersionInfo.dwMinorVersion == 0)
    {
        // do not use CS_DROPSHADOW on W2K or earlier
        ClassStyle &= ~CS_DROPSHADOW;
    }

    bool ret = CreateEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
                        AfxRegisterWndClass(ClassStyle,
                                            NULL,
                                            GetSysColorBrush(COLOR_INFOBK),
                                            NULL),
                        NULL,
                        WS_POPUP | WS_BORDER,
                        CRect(0, 0, 0, 0),
                        pParent,
                        0, 0) != 0;
    if (ret)
    {
        SetFont();
    }

    return ret;
}

bool CTooltipWindow::Activate(bool bActivate)
{
    if (IsWindow(m_hWnd) && bActivate)
    {
        SetTimer(UPDATETIMER, USER_TIMER_MINIMUM, NULL);
        return true;
    }

    KillTimer(UPDATETIMER);
    ShowWindow(SW_HIDE);
    LastImagePoint = CPoint(MAXLONG, MAXLONG);

    return false;
}

void CTooltipWindow::Show(CPoint pt)
{
    pja::CClientDC DC(*this);
    if (DC != NULL)
    {
        // Calculate the size of the tooltip window
        SelectObject(DC, Font);

        SIZE Size;
        GetTextExtentPoint32(DC, Text.c_str(), (int)Text.length(), &Size);

        // ensure the tooltip is contained within the work area of
        // the monitor that the mouse cursor is on.
        HMONITOR hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
        MONITORINFO MonitorInfo = {0};
        MonitorInfo.cbSize = sizeof(MonitorInfo);
        GetMonitorInfo(hMonitor, &MonitorInfo);

        if (pt.x + Size.cx + 5 > MonitorInfo.rcWork.right)
            pt.x = MonitorInfo.rcWork.right - Size.cx - 5;
        else if (pt.x < MonitorInfo.rcWork.left)
            pt.x = MonitorInfo.rcWork.left;

        if (pt.y + 20 + Size.cy + 3 > MonitorInfo.rcWork.bottom)
            pt.y = pt.y - Size.cy - 30;
        else if (pt.y < MonitorInfo.rcWork.top)
            pt.y = MonitorInfo.rcWork.top;

        SetWindowPos(NULL, pt.x, pt.y + 20, Size.cx + 5, Size.cy + 3, SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }
}

void CTooltipWindow::OnPaint()
{
    pja::CPaintDC DC(*this);
    if (DC != NULL)
    {
        SetBkMode(DC, TRANSPARENT);
        SetTextColor(DC, GetSysColor(COLOR_INFOTEXT));
        SelectObject(DC, Font);
        TextOut(DC, 2, 0, Text.c_str(), (int)Text.length());
    }
}

void CTooltipWindow::OnTimer(UINT_PTR nIDEvent)
{
    if (UPDATETIMER == nIDEvent)
    {
        CPoint pt;
        GetCursorPos(&pt);
        Data.Point = pt;
        Data.Colour = CLR_NONE;

        if (this == WindowFromPoint(pt))
        {
            // user has moved mouse on top of the tooltip. caused easily
            // at maximum zoom when shift + down arrow pressed.
            // move the tooltip window out of the way
            Show(pt);
        }

        CWnd *pWindowFromPoint = WindowFromPoint(pt);

        if (pWindowFromPoint->GetTopLevelParent() == AfxGetMainWnd() &&
            pWindowFromPoint->SendMessage(WMU_GETPOINTDATA, (WPARAM)this, (LPARAM)&Data) != 0)
        {
            // CImageViewerView::OnGetPointData() will return 1 if
            // the mouse cursor is over the image it is showing.
            if (Data.Point != LastImagePoint && Data.Colour != CLR_NONE)
            {
                pja::CFormat cf;
                if (Hexadecimal)
                {
                    Text = cf.MakeMessage(NULL,
                                          IDS_COLOURTOOLTIP,
                                          5,
                                          cf.TS(Data.Point.x),
                                          cf.TS(Data.Point.y),
                                          cf.TS(Hex(GetRValue(Data.Colour))),
                                          cf.TS(Hex(GetGValue(Data.Colour))),
                                          cf.TS(Hex(GetBValue(Data.Colour))));
                }
                else
                {
                    Text = cf.MakeMessage(NULL,
                                          IDS_COLOURTOOLTIP,
                                          5,
                                          cf.TS(Data.Point.x),
                                          cf.TS(Data.Point.y),
                                          cf.TS(GetRValue(Data.Colour)),
                                          cf.TS(GetGValue(Data.Colour)),
                                          cf.TS(GetBValue(Data.Colour)));
                }
                LastImagePoint = Data.Point;
                Invalidate();
            }
        }
        if (Data.Colour == CLR_NONE)
        {
            ShowWindow(SW_HIDE);
        }
        else
        {
            Show(pt);
        }
    }
}

void CTooltipWindow::Update()
{
    // Setting the last image point to an impossible to reach value
    // will cause the tooltip to refresh at the next WM_TIMER interval
    LastImagePoint = CPoint(MAXLONG, MAXLONG);
}

bool CTooltipWindow::SetHex(bool bHex)
{
    bool ret = Hexadecimal;
    if (bHex != Hexadecimal)
    {
        Hexadecimal = bHex;
        Update();
    }
    return ret;
}

void CTooltipWindow::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
    CWnd::OnSettingChange(uFlags, lpszSection);

    if (SPI_SETNONCLIENTMETRICS == uFlags)
    {
        // change to system font setting?
        SetFont();
        Update();
    }
}

void CTooltipWindow::SetFont(void)
{
    // Create the tooltip font using the system setting for tooltip
    // and status bar fonts
    NONCLIENTMETRICS ncm = {0};
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0) != 0)
    {
        Font.DeleteObject();
        Font.CreateFontIndirect(&ncm.lfStatusFont);
    }
}
