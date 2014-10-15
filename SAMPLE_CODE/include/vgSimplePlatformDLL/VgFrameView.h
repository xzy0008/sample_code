


#ifndef __VGFRAMEVIEW_H__
#define __VGFRAMEVIEW_H__


	



#include "GLView.h"

#include <sys/timeb.h>


class CMainFrame;
class CVgFrameDoc;

class CVgFrameView : public CGLView
{
protected: // create from serialization only
	CVgFrameView();
	DECLARE_DYNCREATE(CVgFrameView)

// Attributes
public:
	CVgFrameDoc* GetDocument() const;

// Operations
public:



	virtual void fireRenderStarted();

	// 需要重写
	virtual void renderScene()
	{

	}

	virtual void fireRenderEnded();


	CMainFrame* getCMainFrame()
	{
		assert( _mainFrame != NULL );
		return _mainFrame;
	}
	
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
	virtual ~CVgFrameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	//控制相关
	bool		m_EnableOrDisableControls;

	CMainFrame *_mainFrame;

	// FPS相关
	bool  _firstRendering;
	timeb _lastTime;
	float _fTimeSinceLastReport;
	int   _FPS;
	timeb _currentTime;
	float _elapsed;
	void showFPS();

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateEditSelectall(CCmdUI *pCmdUI);
	afx_msg void OnEditSelectall();
	afx_msg void OnControlsTurnleft();
	afx_msg void OnUpdateControlsTurnleft(CCmdUI *pCmdUI);
	afx_msg void OnViewcontrolsEnableOrDisable();
	afx_msg void OnUpdateViewcontrolsEnableOrDisable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlsTurnright(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlsRollup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlsFlydown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlsFlyup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlsRolldown(CCmdUI *pCmdUI);
	afx_msg void OnControlsTurnright();
	afx_msg void OnControlsRollup();
	afx_msg void OnControlsRolldown();
	afx_msg void OnControlsFlyup();
	afx_msg void OnControlsFlydown();
};

#ifndef _DEBUG  // debug version in VgFrameView.cpp
inline CVgFrameDoc* CVgFrameView::GetDocument() const
   { return reinterpret_cast<CVgFrameDoc*>(m_pDocument); }
#endif

#endif // end of __VGFRAMEVIEW_H__