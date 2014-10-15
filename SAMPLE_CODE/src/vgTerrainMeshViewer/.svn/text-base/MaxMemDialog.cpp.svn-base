/****************************************************************************
MaxMemDialog.cpp : Implementation file for the CMaximumMemoryDialog class
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
#include "MaxMemDialog.h"

// CMaximumMemoryDialog dialog

IMPLEMENT_DYNAMIC(CMaximumMemoryDialog, CIVDialog)

CMaximumMemoryDialog::CMaximumMemoryDialog(CWnd* pParent /*=NULL*/)
    : CIVDialog(CMaximumMemoryDialog::IDD, pParent)
{
}

CMaximumMemoryDialog::~CMaximumMemoryDialog()
{
}

void CMaximumMemoryDialog::DoDataExchange(CDataExchange* pDX)
{
    CIVDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATICTEXT, m_Text);
    DDX_Control(pDX, IDC_EDITMAXMEM, m_EditMaxMem);
    DDX_Text(pDX, IDC_EDITMAXMEM, theApp.MaximumMemoryUsage);
    DDX_Control(pDX, IDC_SPINMAXMEM, m_SpinMaxMem);
}


BEGIN_MESSAGE_MAP(CMaximumMemoryDialog, CIVDialog)
END_MESSAGE_MAP()


// CMaximumMemoryDialog message handlers

BOOL CMaximumMemoryDialog::OnInitDialog()
{
    CIVDialog::OnInitDialog();

    m_Text.SetWindowText(_T("Set the maximum amount of memory that the Image Viewer ")
                         _T("can use to store images that it recieves. When this ")
                         _T("memory has been reached the Image Viewer will no longer ")
                         _T("accept more images"));

    UDACCEL UDAccel[] = { {0, 100}, {2, 1000}, {4, 10000} };

    m_SpinMaxMem.SetRange32(100000, 1750000); // 100 MB to 1.75GB (roughly)
    m_SpinMaxMem.SetAccel(_countof(UDAccel), UDAccel);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CMaximumMemoryDialog::OnOK()
{
    UpdateData();

    if (theApp.MaximumMemoryUsage < 100000)
    {
        theApp.MaximumMemoryUsage = 100000;
    }

    else if (theApp.MaximumMemoryUsage > 1750000)
    {
        theApp.MaximumMemoryUsage = 1750000;
    }

    EndDialog(IDOK);
}
