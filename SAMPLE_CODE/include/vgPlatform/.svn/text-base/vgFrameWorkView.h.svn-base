// vgFrameWorkView.h : interface of the CvgFrameWorkView class
//


#pragma once


#include <vgKernel/vgkForward.h>

#include "vgBasedNode.h"


using std::vector;


struct THREADFLAG 
{
	int height;
	int width;

	bool bResize;
	bool bTerminate;
	bool bModifyFlag;
};

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
	bool InitGLContext(void);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CDC*	m_pDC;
	HGLRC	m_hGLContext;

	vector <vgBasedNode*> &pNodeList;
	vector <vgBasedNode*>::iterator iter;
	vector <vgBasedNode*>::iterator end;

	vector<vgBasedNode*> testVector;
public:
	afx_msg void OnDestroy();
	void ReleaseGLContext(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void RenderScene(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnVgmImportVgm();
	afx_msg void OnVgiImportVgi();
	afx_msg void OnVgmSaveVgm();
	afx_msg void OnVgmiSaveVgmVgi();
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
	afx_msg void OnVgtestFf();
	afx_msg void OnVgterrainConvertDemToVgtr();
	afx_msg void OnVgterrainConvertVgtrHeightmap();
};

#ifndef _DEBUG  // debug version in vgFrameWorkView.cpp
inline CvgFrameWorkDoc* CvgFrameWorkView::GetDocument() const
   { return reinterpret_cast<CvgFrameWorkDoc*>(m_pDocument); }
#endif

