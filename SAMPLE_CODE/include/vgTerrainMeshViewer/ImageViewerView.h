/****************************************************************************
ImageViewerView.h : Header file for the CImageViewerView class
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
#include "MouseGesture.h"
#include "pja_bitmap.h"

class CImageViewerView : public CScrollView
{
    DECLARE_DYNCREATE(CImageViewerView)

protected:
    CImageViewerView(); // create from serialization only
    CImageViewerDoc* GetDocument() const;

// Overrides
public:
    virtual ~CImageViewerView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void OnInitialUpdate(); // called first time after construct

// Implementation
#ifdef _DEBUG
public:
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    bool AutoScrollTimer;
    bool LButtonDown;
    bool ViewGrid;
    size_t CurrentImage;        // zero based index
    size_t CurrentZoomRatio;    // zero based index
    CMouseGesture MouseGesture;
    CRect ZoomedBitmapRect;
    pja::CBitmap CurrentBitmap;

protected:
    COLORREF GetPixelColour(CPoint &pt) const;
    CRect GetVisibleRect(void) const;
    void CalcBitmapRect();
    void SetCaption();
    bool SetCurrentImage(size_t nImage, bool PassLock);
    bool MoveCursor(int x, int y);
    bool CenterCursorOnPixel(CPoint CursorPos);
    CPoint GetPixelFromPoint(CPoint Point, bool AdjustedForScrolling = true);
    void MovePixelToPoint(CPoint Pixel, CPoint Client);

// Generated message map functions
protected:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    afx_msg LRESULT OnGetPointData(WPARAM wp, LPARAM lp);
    afx_msg LRESULT OnMouseGesture(WPARAM wp, LPARAM lp);

    afx_msg void OnImageDelete();
    afx_msg void OnUpdateImageDelete(CCmdUI *pCmdUI);
    afx_msg void OnViewCenterMouse();
    afx_msg void OnUpdateViewCenterMouse(CCmdUI *pCmdUI);
    afx_msg void OnImageFirst();
    afx_msg void OnUpdateImageFirst(CCmdUI *pCmdUI);
    afx_msg void OnImagePrevious();
    afx_msg void OnUpdateImagePrevious(CCmdUI *pCmdUI);
    afx_msg void OnImageSelect();
    afx_msg void OnUpdateImageSelect(CCmdUI *pCmdUI);
    afx_msg void OnImageNext();
    afx_msg void OnUpdateImageNext(CCmdUI *pCmdUI);
    afx_msg void OnImageLast();
    afx_msg void OnUpdateImageLast(CCmdUI *pCmdUI);
    afx_msg void OnZoomGrid();
    afx_msg void OnUpdateZoomGrid(CCmdUI *pCmdUI);
    afx_msg void OnZoomZoomIn();
    afx_msg void OnUpdateZoomZoomIn(CCmdUI *pCmdUI);
    afx_msg void OnZoomZoomOut();
    afx_msg void OnUpdateZoomZoomOut(CCmdUI *pCmdUI);

#if !defined NO_GDIPLUS
protected:
    afx_msg void OnImageSave();
    afx_msg void OnUpdateImageSave(CCmdUI *pCmdUI);
#endif // #if !defined NO_GDIPLUS

    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageViewerView.cpp
inline CImageViewerDoc* CImageViewerView::GetDocument() const
   { return reinterpret_cast<CImageViewerDoc*>(m_pDocument); }
#endif

