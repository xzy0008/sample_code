/****************************************************************************
PropertiesDialog.cpp : Implementation file for the CPropertiesDialog class
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
#include "ImageData.h"
#include "PropertiesDialog.h"
#include "BitmapInfoHeader.h"

#include "pja_bitmap.h"

// CPropertiesDialog dialog

IMPLEMENT_DYNAMIC(CPropertiesDialog, CDialog)

CPropertiesDialog::CPropertiesDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CPropertiesDialog::IDD, pParent)
    , MinimumSize(123, 34)
{
}

CPropertiesDialog::~CPropertiesDialog()
{
}

void CPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertiesDialog, CDialog)
    ON_MESSAGE(WMU_SETPROPERTIES, &CPropertiesDialog::OnSetProperties)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_WM_GETMINMAXINFO()
    ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CPropertiesDialog message handlers

void CPropertiesDialog::OnCancel()
{
    ShowWindow(SW_HIDE);
}

void CPropertiesDialog::OnOK()
{
    ShowWindow(SW_HIDE);
}

LRESULT CPropertiesDialog::OnSetProperties(WPARAM, LPARAM lp)
{
    ASSERT (NULL != lp);

    if (NULL != lp)
    {
        CImageData *pData = reinterpret_cast<CImageData *>(lp);
        CBitmapInfoHeader BitmapInfoHeader(pData->GetBitmapInfoHeader());

        SetDlgItemInt(IDC_EDITWIDTH, BitmapInfoHeader.biWidth, FALSE);
        SetDlgItemInt(IDC_EDITHEIGHT, BitmapInfoHeader.biHeight, FALSE);
        SetDlgItemInt(IDC_EDITBITS, BitmapInfoHeader.biBitCount, FALSE);
        SetDlgItemText(IDC_EDITPATH, pData->GetSourcePath().c_str());
        SetDlgItemText(IDC_EDITFILE, pData->GetSourceFile().c_str());
        SetDlgItemText(IDC_EDITLINE, pData->GetSourceLine().c_str());
        SetDlgItemText(IDC_EDITFUNCTION, pData->GetSourceFunction().c_str());
        SetDlgItemText(IDC_EDITTIME, pData->GetTime().c_str());
        SetDlgItemText(IDC_EDITTEXT, pData->GetText().c_str());
    }

    return 0;
}

int CPropertiesDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;

    CreateSizeGrip();

    return 0;
}

void CPropertiesDialog::OnDestroy()
{
    CDialog::OnDestroy();

    CRect WindowRect;
    GetWindowRect(WindowRect);
    theApp.WriteObjectArray(_T("Settings"), _T("Properties Window Position"), &WindowRect);

    DestroyIcon(hIcon);
}

void CPropertiesDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    CWnd *pWnd = GetDlgItem(IDC_EDITWIDTH);
    if (IsWindow(*pWnd))
    {
        CRect rc;
        pWnd->GetWindowRect(rc);
        ScreenToClient(rc);
        int offset = rc.top;

        UINT IDs[] = { IDC_EDITWIDTH,
                       IDC_EDITHEIGHT,
                       IDC_EDITBITS,
                       IDC_EDITPATH,
                       IDC_EDITFILE,
                       IDC_EDITLINE,
                       IDC_EDITFUNCTION,
                       IDC_EDITTIME,
                       IDC_EDITTEXT };

        HDWP hDWP = BeginDeferWindowPos(_countof(IDs) + 1);
        for (int x = 0; x < _countof(IDs); ++x)
        {
            pWnd = GetDlgItem(IDs[x]);
            pWnd->GetWindowRect(rc);
            ScreenToClient(rc);
            rc.right = cx - offset;
            hDWP = DeferWindowPos(hDWP, *pWnd, NULL, 0, 0, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOZORDER);
        }

        rc.bottom = cy - offset;
        hDWP = DeferWindowPos(hDWP, *pWnd, NULL, 0, 0, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOZORDER);

        EndDeferWindowPos(hDWP);
    }

    UpdateSizeGrip();
}

BOOL CPropertiesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    CRect rc;
    GetWindowRect(rc);
    MinimumSize.x = rc.Width();
    MinimumSize.y = rc.Height();

    hIcon = reinterpret_cast<HICON>(LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_PROPERTY), IMAGE_ICON, 0, 0, 0));
    SetIcon(hIcon, FALSE);

    CRect WindowRect(0, 0, 0, 0);
    if (ERROR_SUCCESS == theApp.GetObjectArray(_T("Settings"), _T("Properties Window Position"), &WindowRect))
    {
        MoveWindow(WindowRect.left, WindowRect.top, WindowRect.Width(), WindowRect.Height());
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    lpMMI->ptMinTrackSize.x = MinimumSize.x;
    lpMMI->ptMinTrackSize.y = MinimumSize.y;

    CDialog::OnGetMinMaxInfo(lpMMI);
}

BOOL CPropertiesDialog::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN &&
        pMsg->wParam == VK_TAB &&
        ((IsSHIFTpressed() && pMsg->hwnd == *GetDlgItem(IDC_EDITWIDTH)) ||
        (!IsSHIFTpressed() && pMsg->hwnd == *GetDlgItem(IDC_EDITTEXT))))
    {
        // Allow the user to tab from the properties dialog to the main window
        GetParent()->SetFocus();
        return TRUE;
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CPropertiesDialog::OnSetFocus(CWnd* pOldWnd)
{
    CDialog::OnSetFocus(pOldWnd);

    if (IsSHIFTpressed())
    {
        CWnd *pWnd = GetDlgItem(IDC_EDITTEXT);
        pWnd->SetFocus();
        pWnd->SendMessage(EM_SETSEL, 0, -1);
    }
}
