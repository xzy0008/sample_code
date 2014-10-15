#if !defined(AFX_FILETREEVIEW_H__291F8A76_6444_4A2D_AA9D_10B2B337C282__INCLUDED_)
#define AFX_FILETREEVIEW_H__291F8A76_6444_4A2D_AA9D_10B2B337C282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTreeView.h : header file
//


#define DIR		0
#define FILE	1

#define ID_FILETREE 96367
/////////////////////////////////////////////////////////////////////////////
// CFileTreeView view

class CFileTreeView : public CView
{
protected:
	CFileTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFileTreeView)

// Attributes
public:

// Operations
public:
	void OnFiletreeRefresh();
	void HideButton(HTREEITEM hti);
	BOOL HaveSubDirOrFile(char *szCurDir);
	BOOL GetSubSiblingItem(HTREEITEM hItem, char *szCurDir);
	CString GetFileExName(TCHAR cFileName[MAX_PATH]);
	void DisplayButton(HTREEITEM hti);
	void InitRootDirectory();

	CTreeCtrl m_tree;

	CImageList	m_ImageList;
	CString m_strOpenFile;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTreeView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFileTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileTreeView)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETREEVIEW_H__291F8A76_6444_4A2D_AA9D_10B2B337C282__INCLUDED_)
