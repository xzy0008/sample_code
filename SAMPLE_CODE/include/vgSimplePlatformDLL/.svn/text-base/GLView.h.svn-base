#pragma once


// CGLView view

class CGLView : public CView
{
	DECLARE_DYNAMIC(CGLView)

protected:
	CGLView();           // protected constructor used by dynamic creation
	virtual ~CGLView();

protected:
	CDC         *_CDC;
	HWND        mHWnd; 

	HGLRC		mHGLRC;

	CRect       mRect;
	int			mWidth;
	int			mHeight;

public:

	bool setupOpenGL();

	virtual void fireRenderStarted() = 0;

	virtual void renderScene() = 0;

	virtual void fireRenderEnded() = 0;



public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


