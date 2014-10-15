/****************************************************************************
MainFrm.h : Header file for the CMainFrame class
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

#include <map>
#include "ImageData.h"
#include "ImageViewerDoc.h"
#include "PropertiesDialog.h"
#include "MDIClient.h"
#include "TrueColorToolBar.h"
#include "TooltipWindow.h"
#include "MainStatusBar.h"

class CMainFrame : public CMDIFrameWnd
{
    DECLARE_DYNAMIC(CMainFrame)
public:
    CMainFrame();

// Attributes
public:
    // A map that maps process ID's to active documents. With this
    // I can keep track of which incoming images go to which documents
    typedef std::map<DWORD, CImageViewerDoc *> IDDocMap;
    IDDocMap IDDocs;

    // The properties dialog is always active, it is just not
    // visible when the user does not want to see it
    CPropertiesDialog PropertiesDialog;

// Operations
public:

// Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// Implementation
public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CMainStatusBar      m_wndStatusBar; // status bar with a custom drawn pane that shows memory usage
    CTrueColorToolBar   m_wndToolBar;   // tool bar with 24 bit full colour buttons
    CMDIClient          MDIClient;      // mdi client window with logo icon drawn in bottom right corner

    CTooltipWindow ColourTooltip;       // tooltip that shows when the mouse cursor
                                        // is over an image in a view window
    bool HexTooltip;
    bool DisplayLock;
    COLORREF BackgroundColour;

// Generated message map functions
protected:
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    afx_msg LRESULT OnSetMessageString(WPARAM, LPARAM);

    afx_msg void OnFileCloseActive();
    afx_msg void OnFileCloseAll();
    afx_msg void OnFileCloseAllExceptActive();
    afx_msg void OnViewBackgroundColour();
    afx_msg void OnViewHexadecimalTooltips();
    afx_msg void OnUpdateViewHexadecimalTooltips(CCmdUI *pCmdUI);
    afx_msg void OnViewDisplayLock();
    afx_msg void OnUpdateViewDisplayLock(CCmdUI *pCmdUI);
    afx_msg void OnViewOnTop();
    afx_msg void OnUpdateViewOnTop(CCmdUI *pCmdUI);
    afx_msg void OnImageProperties();
    afx_msg void OnUpdateImageProperties(CCmdUI *pCmdUI);
    afx_msg void OnUpdateIndicatorMem(CCmdUI *pCmdUI);

    afx_msg LRESULT OnAreYouMe(WPARAM, LPARAM);
    afx_msg LRESULT OnGetBGColour(WPARAM, LPARAM);
    afx_msg LRESULT OnGetDisplayLock(WPARAM, LPARAM);
    afx_msg LRESULT OnSetProperties(WPARAM, LPARAM);
    afx_msg LRESULT OnDocumentClosing(WPARAM, LPARAM);
    afx_msg LRESULT OnUpdateTooltip(WPARAM, LPARAM);
    DECLARE_MESSAGE_MAP()
};


