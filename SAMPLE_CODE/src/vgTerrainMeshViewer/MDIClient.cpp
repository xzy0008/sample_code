/****************************************************************************
MDIClient.cpp : Implementation file for the CMDIClient class
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
#include "MDIClient.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CMDIClient, CWnd)

CMDIClient::CMDIClient()
: hIcon(NULL)
, IconRect(0, 0, 0, 0)
{
    //hIcon = static_cast<HICON>(LoadImage(AfxGetResourceHandle(),
    //                                     MAKEINTRESOURCE(IDI_PJA),
    //                                     IMAGE_ICON,
    //                                     0, 0,
    //                                     LR_DEFAULTSIZE | LR_SHARED));
}

CMDIClient::~CMDIClient()
{
}


BEGIN_MESSAGE_MAP(CMDIClient, CWnd)
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CMDIClient message handlers

void CMDIClient::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    CRect ClipBox;
    dc.GetClipBox(ClipBox);
    if (!(IconRect & ClipBox).IsRectEmpty())
    {
        //dc.DrawIcon(IconRect.left, IconRect.top, hIcon);
    }
}

void CMDIClient::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    InvalidateRect(IconRect);   // erase the icon at the old position
    IconRect.right = cx - 2;
    IconRect.left = IconRect.right - GetSystemMetrics(SM_CXICON);
    IconRect.bottom = cy - 2;
    IconRect.top = IconRect.bottom - GetSystemMetrics(SM_CYICON);
    InvalidateRect(IconRect);   // draw the icon at the new position
}
