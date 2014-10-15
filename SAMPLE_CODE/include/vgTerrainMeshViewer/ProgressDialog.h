/****************************************************************************
ProgressDialog.h : Header file for the CProgressDialog class
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
#include "resource.h"
#include "IVDialog.h"

// CProgressDialog dialog

class CProgressDialog : public CIVDialog
{
    DECLARE_DYNAMIC(CProgressDialog)

public:
    CProgressDialog(CWnd* pParent = NULL);   // standard constructor
    virtual ~CProgressDialog();

    bool Create(CWnd *pParent, LPCTSTR szCaption, LPCTSTR szFormat, int nMax, volatile bool *pStop);
    virtual BOOL OnInitDialog();
    virtual BOOL DestroyWindow();
    void Stepit();

// Dialog Data
    enum { IDD = IDD_PROGRESS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnCancel();
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
    CProgressCtrl ProgressCtrl;
    CStatic StaticCtrl;
    CString FormatText;
    CString Caption;
    int Maximum;
    int Position;
    volatile bool *Stop;
};
