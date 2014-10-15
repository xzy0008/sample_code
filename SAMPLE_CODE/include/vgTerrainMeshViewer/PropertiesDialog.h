/****************************************************************************
PropertiesDialog.h : Header file for the CPropertiesDialog class
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

#include "ResizableGrip.h"

// CPropertiesDialog dialog

class CPropertiesDialog : public CDialog, CResizableGrip
{
    DECLARE_DYNAMIC(CPropertiesDialog)

public:
    CPropertiesDialog(CWnd* pParent = NULL);   // standard constructor
    virtual ~CPropertiesDialog();

// Dialog Data
    enum { IDD = IDD_PROPERTIES };

public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
    HICON hIcon;
    CPoint MinimumSize;

    virtual CWnd* GetResizableWnd() const { return CWnd::FromHandle(m_hWnd); }
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnCancel();
    virtual void OnOK();
    virtual BOOL OnInitDialog();

    afx_msg LRESULT OnSetProperties(WPARAM, LPARAM);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSetFocus(CWnd* pOldWnd);
};
