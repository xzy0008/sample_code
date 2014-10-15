// vgFrameWorkView.h : interface of the CvgFrameWorkView class
//


#pragma once




class CvgFrameWorkView : public CView
{
protected: // create from serialization only
	CvgFrameWorkView();
	DECLARE_DYNCREATE(CvgFrameWorkView)



// Attributes
public:
	CvgFrameWorkDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CvgFrameWorkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
	bool initGLContext(void);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	// device
	CDC*	m_pDC;
	HGLRC	m_hGLContext;



public:
	afx_msg void OnDestroy();
	void releaseGLContext(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void renderScene(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);



	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVgterrainWireframe();
	afx_msg void OnVgterrainNowireframe();
	afx_msg void OnVgterrainTurnon();
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);

	afx_msg LRESULT OnRender(WPARAM wParam, LPARAM lParam); 
	virtual void OnInitialUpdate();


	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);



	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	


	// File
	afx_msg void OnSceneRead();


	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);


	// aboutDlg
	afx_msg void OnAppAbout();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);



	afx_msg void OnVgmImport();
};

#ifndef _DEBUG  // debug version in vgFrameWorkView.cpp
inline CvgFrameWorkDoc* CvgFrameWorkView::GetDocument() const
   { return reinterpret_cast<CvgFrameWorkDoc*>(m_pDocument); }
#endif

