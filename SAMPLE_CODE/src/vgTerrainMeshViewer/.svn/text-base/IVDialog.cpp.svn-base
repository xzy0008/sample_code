/****************************************************************************
IVDialog.cpp : Implementation file for the CIVDialog (Image Viewer Dialog) class
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
#include "IVDialog.h"
#include "ImageViewerApp.h"

IMPLEMENT_DYNAMIC(CIVDialog, CDialog)

CIVDialog::CIVDialog(UINT nID, CWnd* pParent /*=NULL*/)
    : CDialog(nID, pParent)
{
}

CIVDialog::CIVDialog(LPCTSTR Name, CWnd *pParent /*=NULL*/)
    : CDialog(Name, pParent)
{
}

CIVDialog::~CIVDialog()
{
}

BEGIN_MESSAGE_MAP(CIVDialog, CDialog)
END_MESSAGE_MAP()


// CIVDialog message handlers

INT_PTR CIVDialog::DoModal()
{
    // Set the ModalDialogEvent to stop CMainFrame::OnCopyData()
    // from opening any new files. If it does open a new file then
    // the dialogs opened via a call to CDialog::DoModal will
    // loose their 'modal-ness'.

    theApp.ModalDialogEvent.ResetEvent();

    INT_PTR ret = CDialog::DoModal();

    theApp.ModalDialogEvent.SetEvent();

    return ret;
}
