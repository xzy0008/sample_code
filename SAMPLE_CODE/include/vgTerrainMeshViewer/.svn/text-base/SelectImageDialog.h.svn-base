/****************************************************************************
SelectImageDialog.h : Header file for the CSelectImageDialog class
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


// CSelectImageDialog dialog
#include "resource.h"
#include "IVDialog.h"

class CSelectImageDialog : public CIVDialog
{
    DECLARE_DYNAMIC(CSelectImageDialog)

public:
    CSelectImageDialog(CWnd* pParent = NULL);   // standard constructor
    virtual ~CSelectImageDialog();

// Dialog Data
    enum { IDD = IDD_SELECT };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnEnChangeEditSelect();
    DECLARE_MESSAGE_MAP()
public:
    UINT m_Image;
    UINT m_MaxImage;
protected:
    CSpinButtonCtrl m_Spinner;
public:
    virtual BOOL OnInitDialog();
};
