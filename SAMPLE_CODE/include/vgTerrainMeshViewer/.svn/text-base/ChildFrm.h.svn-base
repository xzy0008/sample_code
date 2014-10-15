/****************************************************************************
ChildFrm.h : Header file for the CChildFrame class
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
#include "ImageData.h"
#include "ChildStatusBar.h"

class CChildFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CChildFrame)
public:
    CChildFrame();
    virtual ~CChildFrame();

// Attributes
protected:
    CImageData *pCurrentImage;
    CChildStatusBar m_StatusBar;

// Operations
public:

// Overrides
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    afx_msg LRESULT OnSetMessageText(WPARAM, LPARAM);
    afx_msg LRESULT OnSetMessageString(WPARAM, LPARAM);
    afx_msg LRESULT OnUpdateChildStatusBar(WPARAM, LPARAM);
    afx_msg LRESULT OnThemeChanged(WPARAM, LPARAM);

    afx_msg void OnViewIndicatorsText();
    afx_msg void OnUpdateViewIndicatorsText(CCmdUI *pCmdUI);
    afx_msg void OnViewIndicatorsTime();
    afx_msg void OnUpdateViewIndicatorsTime(CCmdUI *pCmdUI);
    afx_msg void OnViewIndicatorsFile();
    afx_msg void OnUpdateViewIndicatorsFile(CCmdUI *pCmdUI);
    afx_msg void OnViewIndicatorsLine();
    afx_msg void OnUpdateViewIndicatorsLine(CCmdUI *pCmdUI);
    afx_msg void OnViewIndicatorsMethod();
    afx_msg void OnUpdateViewIndicatorsMethod(CCmdUI *pCmdUI);
    afx_msg void OnViewIndicatorsSize();
    afx_msg void OnUpdateViewIndicatorsSize(CCmdUI *pCmdUI);
    DECLARE_MESSAGE_MAP()
};
