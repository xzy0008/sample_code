// MyListViewView.h : interface of the CMyListViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLISTVIEWVIEW_H__E7C610D0_C3C4_11D3_A6BE_88BBC02C944D__INCLUDED_)
#define AFX_MYLISTVIEWVIEW_H__E7C610D0_C3C4_11D3_A6BE_88BBC02C944D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyLeftFileTreeCtrl.h"


#include "VgimgReaderDoc.h"

class CMyListViewView : public CView
{
protected: // create from serialization only
	CMyListViewView();
	DECLARE_DYNCREATE(CMyListViewView)

// Attributes
public:
	CVgimgReaderDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyListViewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CMyLeftFileTreeCtrl m_ListCtrl;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

#ifndef _DEBUG  // debug version in MyListViewView.cpp
inline CVgimgReaderDoc* CMyListViewView::GetDocument()
   { return (CVgimgReaderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTVIEWVIEW_H__E7C610D0_C3C4_11D3_A6BE_88BBC02C944D__INCLUDED_)
