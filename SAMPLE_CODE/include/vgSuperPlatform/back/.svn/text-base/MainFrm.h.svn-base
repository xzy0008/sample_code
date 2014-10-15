// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "vgWorkSpaceBar.h"
#include "WorkSpaceBar2.h"
//#include "vgOutputBar.h"
#include "vgPropertiesViewBar.h"
#include "vgTestNode1TabOne.h"
#include "Resource.h"
#include "vgTestNode1PropertiesTab.h"
#include "vgUIController.h"

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
	BOOL	IsFullScreen();
// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
public:
	// control bar embedded members
	// CBCGPStatusBar			m_wndStatusBar;
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	// vgWorkSpaceBar		m_wndWorkSpace;
	// CWorkSpaceBar2		m_wndWorkSpace2;
	//vgOutputBar				m_wndOutput;
	// TabOne				tab;
	// PropertiesTab		pTab;

	// CPropertiesViewBar	m_wndPropertiesView;
	CBCGPToolBarImages		m_UserImages;
	// Generated message map functions
protected:
		
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	void OnToolsViewUserToolbar (UINT id);
	void OnUpdateToolsViewUserToolbar (CCmdUI* pCmdUI);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	afx_msg void OnTestUpdate();
	
	afx_msg void OnFullScreen();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);

	DECLARE_MESSAGE_MAP()
	
	UINT			m_nAppLook;
	bool			InitUIControl(void);

	WINDOWPLACEMENT m_wpPrev;
	CRect			m_FullScreenWindowRect;
	CBCGPToolBar	*m_pwndFullScrnBar;
	bool			m_bFullScreen;
};


