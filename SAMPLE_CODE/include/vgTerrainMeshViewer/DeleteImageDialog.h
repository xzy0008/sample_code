/****************************************************************************
DeleteImageDialog.h : Header file for the CDeleteImageDialog class
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
#include "IVDialog.h"
#include "Resource.h"

// CDeleteImageDialog dialog

class CDeleteImageDialog : public CIVDialog
{
    DECLARE_DYNAMIC(CDeleteImageDialog)

public:
    CDeleteImageDialog(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDeleteImageDialog();

// Dialog Data
    enum { IDD = IDD_DELETE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg LRESULT OnIdle(WPARAM, LPARAM);

    DECLARE_MESSAGE_MAP()
public:
    int Selection;
    UINT From;
    UINT To;
protected:
    CButton m_OK;
    CEdit m_EditFrom;
    CStatic m_StaticFrom;
    CStatic m_StaticTo;
    CEdit m_EditTo;
    CButton m_RadioSelect;
};
