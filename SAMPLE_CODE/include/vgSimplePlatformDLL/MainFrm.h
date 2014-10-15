// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "WorkSpaceBar.h"
#include "WorkSpaceBar2.h"
#include "OutputBar.h"
#include "PropertiesViewBar.h"

class CMainFrame : public CBCGPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
public:

	CBCGPStatusBar			m_wndStatusBar;
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	CWorkSpaceBar			m_wndWorkSpace;
	CWorkSpaceBar2			m_wndWorkSpace2;
	COutputBar				m_wndOutput;

	// added by leven
	CBCGPToolBar			m_wndControlsToolBar;
	CPropertiesViewBar		m_wndPropertiesBar;
	

	CBCGPToolBarImages	m_UserImages;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	void OnToolsViewUserToolbar (UINT id);
	void OnUpdateToolsViewUserToolbar (CCmdUI* pCmdUI);
	afx_msg LRESULT OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()


	UINT	m_nAppLook;
public:
	afx_msg void OnViewFullscreen();
	afx_msg void OnUpdateViewOutput(CCmdUI *pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateViewProperties(CCmdUI *pCmdUI);
};


