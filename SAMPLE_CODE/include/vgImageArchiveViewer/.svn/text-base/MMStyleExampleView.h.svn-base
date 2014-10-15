//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MMStyleExampleView.h : interface of the CMMStyleExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMSTYLEEXAMPLEVIEW_H__2B4A9A0C_0017_40BA_9788_802E09CE9F1D__INCLUDED_)
#define AFX_MMSTYLEEXAMPLEVIEW_H__2B4A9A0C_0017_40BA_9788_802E09CE9F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <afxcview.h>
#include <vgImage/vgiFileDefinitionVgi.h>
#include <vgTerritory/vgtFileDefinitionVtr.h>



struct IDropTargetHelper;    // in case the newest PSDK isn't available.

class CMMStyleExampleView : public CListView
{
protected: // create from serialization only
	CMMStyleExampleView();
	DECLARE_DYNCREATE(CMMStyleExampleView)

	// Attributes
public:
	CMMStyleExampleDoc* GetDocument();

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMStyleExampleView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void OnDragLeave();
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CMMStyleExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList         m_imglist;
	COleDropTarget     m_droptarget;

	IDropTargetHelper* m_piDropHelper;
	bool               m_bUseDnDHelper;

	vgImage::VgiBriefPtrVec* vgiBriefs;

	vgTerritory::VtrBriefPtrVec* vtrBriefs;

	String _vgiFilename;

	String _vtrFilename;

	BOOL ReadHdropData ( COleDataObject* pDataObject );

	void openVgi( String vgifile, CListCtrl &list, int nIndex );

	void opengVtr( String vtrfile, CListCtrl &list, int nIndex );


	// Generated message map functions
protected:
	//{{AFX_MSG(CMMStyleExampleView)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectAll();
	afx_msg void OnInvertSelection();
	afx_msg void OnRemoveFromList();
	afx_msg void OnClearList();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();

	void clearAllData();
};

#ifndef _DEBUG  // debug version in MultiFilerView.cpp
inline CMMStyleExampleDoc* CMMStyleExampleView::GetDocument()
{ return (CMMStyleExampleDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MMSTYLEEXAMPLEVIEW_H__2B4A9A0C_0017_40BA_9788_802E09CE9F1D__INCLUDED_)
