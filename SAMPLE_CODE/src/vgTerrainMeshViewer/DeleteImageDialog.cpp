/****************************************************************************
DeleteImageDialog.cpp : Implementation file for the CDeleteImageDialog class
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
#include "DeleteImageDialog.h"

// CDeleteImageDialog dialog

IMPLEMENT_DYNAMIC(CDeleteImageDialog, CIVDialog)

CDeleteImageDialog::CDeleteImageDialog(CWnd* pParent /*=NULL*/)
: CIVDialog(CDeleteImageDialog::IDD, pParent)
, Selection(0)
, From(1)
, To(1)
{
}

CDeleteImageDialog::~CDeleteImageDialog()
{
}

void CDeleteImageDialog::DoDataExchange(CDataExchange* pDX)
{
    CIVDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDOK, m_OK);
    DDX_Control(pDX, IDC_FROM, m_EditFrom);
    DDX_Control(pDX, IDC_STATICFROM, m_StaticFrom);
    DDX_Control(pDX, IDC_STATICTO, m_StaticTo);
    DDX_Control(pDX, IDC_TO, m_EditTo);
    DDX_Control(pDX, IDC_SELECT, m_RadioSelect);
    DDX_Radio(pDX, IDC_CURRENT, Selection);
    DDX_Text(pDX, IDC_FROM, From);
    DDX_Text(pDX, IDC_TO, To);
}


BEGIN_MESSAGE_MAP(CDeleteImageDialog, CIVDialog)
    ON_MESSAGE(WM_KICKIDLE, &CDeleteImageDialog::OnIdle)
END_MESSAGE_MAP()


// CDeleteImageDialog message handlers

LRESULT CDeleteImageDialog::OnIdle(WPARAM, LPARAM)
{
    // enable or disable child controls depending on what the user has entered
    bool bEnable = m_RadioSelect.GetCheck() == BST_CHECKED;
    m_EditFrom.EnableWindow(bEnable);
    m_EditTo.EnableWindow(bEnable);
    m_StaticFrom.EnableWindow(bEnable);
    m_StaticTo.EnableWindow(bEnable);
    m_OK.EnableWindow(!bEnable || (GetDlgItemInt(IDC_TO) != 0 && GetDlgItemInt(IDC_FROM) != 0));

    return 0;
}
