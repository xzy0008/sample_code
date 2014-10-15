/****************************************************************************
WindowScroller.h : header file
Written by : PJ Arends
pja@telus.net

Copyright © 2003 PJ Arends

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

#if !defined(AFX_WINDOWSCROLLER_H__EAD6ECEB_81D1_4E3F_A858_6F3902A9911C__INCLUDED_)
#define AFX_WINDOWSCROLLER_H__EAD6ECEB_81D1_4E3F_A858_6F3902A9911C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWindowScroller window

// Registered message used to inform parent window that this scroller has been destroyed
const UINT RWM_DESTROYWINDOWSCROLLER = RegisterWindowMessage(_T("DestroyWindowScroller{3B89C798-5382-4b00-8668-5EB1649C6294}"));

namespace pja
{
    class CWindowScroller : public CWnd
    {
    // Construction
    public:
        CWindowScroller(CWnd *pParent, CPoint Point, int Pixels = 15, UINT Elapse = 30, int Direction = Both, BOOL bUseThumbPos = TRUE);

    // Attributes
    public:
        enum AlignEnum
        {
            Vertical = 1,
            Horizontal = 2,
            Both = 3
        };

        HHOOK m_hKeyboardHook;
        HHOOK m_hMouseHook;
        static CWindowScroller* pWindowScroller;

    protected:
        BOOL m_bWindowScrolled;
        CPoint m_CenterPoint;
        CRgn m_WndRgn;
        CWnd *m_pParentWnd;
        UINT m_ParentWndType;

        HCURSOR m_DownCursor;
        HCURSOR m_DownLeftCursor;
        HCURSOR m_DownRightCursor;
        HCURSOR m_LeftCursor;
        HCURSOR m_NeutralCursor;
        HCURSOR m_RightCursor;
        HCURSOR m_UpCursor;
        HCURSOR m_UpLeftCursor;
        HCURSOR m_UpRightCursor;

        HICON m_hIcon;

        int m_Alignment;
        int m_HorzScroll;
        int m_ScrollFlag;
        int m_ScrollRatio;
        int m_VertScroll;

    // Operations
    protected:
        void BuildCursors();
        UINT GetParentWndType() const;
        void Initialize();
        void SetMyCursor();

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CWindowScroller)
        protected:
        virtual void PostNcDestroy();
        //}}AFX_VIRTUAL

    // Implementation
    public:

    // Generated message map functions
    protected:
        //{{AFX_MSG(CWindowScroller)
        afx_msg void OnCaptureChanged(CWnd *pWnd);
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDestroy();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnPaint();
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnTimer(UINT nIDEvent);
        //}}AFX_MSG
        afx_msg LRESULT OnXButtonDown(WPARAM wp, LPARAM lp);
        afx_msg LRESULT OnXButtonUp(WPARAM wp, LPARAM lp);
        DECLARE_MESSAGE_MAP()
    };
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWSCROLLER_H__EAD6ECEB_81D1_4E3F_A858_6F3902A9911C__INCLUDED_)
