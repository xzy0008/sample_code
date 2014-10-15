/****************************************************************************
ProgressDialog.cpp : Implementation file for the CProgressDialog class
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
#include "ProgressDialog.h"

#include "pja_format.h"

// CProgressDialog dialog

IMPLEMENT_DYNAMIC(CProgressDialog, CIVDialog)

CProgressDialog::CProgressDialog(CWnd* pParent /*=NULL*/)
    : CIVDialog(CProgressDialog::IDD, pParent)
    , Maximum(0)
    , Position(0)
    , Stop(NULL)
{
}

CProgressDialog::~CProgressDialog()
{
    if (IsWindow(*this))
        DestroyWindow();
}

void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
    CIVDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PROGRESSSAVING, ProgressCtrl);
    DDX_Control(pDX, IDC_STATICSAVING, StaticCtrl);
}


BEGIN_MESSAGE_MAP(CProgressDialog, CIVDialog)
END_MESSAGE_MAP()


// CProgressDialog message handlers
bool CProgressDialog::Create(CWnd *pParent,
                          LPCTSTR szCaption,
                          LPCTSTR szFormat,
                          int nMax,
                          volatile bool *pStop)
{
    Caption = szCaption;
    FormatText = szFormat;
    Maximum = nMax;
    Stop = pStop;

    bool ret = CIVDialog::Create(CProgressDialog::IDD, pParent) != 0;

    if (ret)
    {
        // disable the main window, makes this dialog appear modal
        AfxGetMainWnd()->EnableWindow(FALSE);
        EnableWindow(TRUE);
    }

    return ret;
}


BOOL CProgressDialog::OnInitDialog()
{
    CIVDialog::OnInitDialog();

    CenterWindow();

    SetWindowText(Caption);

    ProgressCtrl.SetRange32(0, 2000);
    ProgressCtrl.SetStep(1);
    ProgressCtrl.SetPos(0);

    Stepit();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgressDialog::Stepit()
{
    ++Position;
    ProgressCtrl.SetPos((int)((double)Position / (double)Maximum * 2000.0));

    pja::CFormat cf;
    StaticCtrl.SetWindowText(cf.MakeMessage(FormatText, 2, cf.TS(Position), cf.TS(Maximum)).c_str());

    if (0 == Position % 250)
    {
        while (GetQueueStatus(QS_ALLINPUT))
        {
            AfxGetApp()->PumpMessage(); // so Cancel button works and any images recieved get displayed
        }
        AfxGetApp()->OnIdle(-1);        // to update memory usage display on status bar
    }
}

void CProgressDialog::OnCancel()
{
    // set the stop flag so the calling function knows it has to abort
    *Stop = true;
    CIVDialog::OnCancel();
}

void CProgressDialog::OnOK()
{
    // Do nothing - disables the 'Enter' key
}

BOOL CProgressDialog::DestroyWindow()
{
    BOOL ret = CIVDialog::DestroyWindow();

    // re-enable the main window
    AfxGetMainWnd()->EnableWindow(TRUE);
    AfxGetMainWnd()->SetForegroundWindow();

    return ret;
}
