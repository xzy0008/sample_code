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

#include <vgDlgTestMultisample.h>
#include "DynamicItems.h"


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

	// --- dyn menu begin----
	CDynamicItems	m_dynamic_menu;
	afx_msg void OnExecuteDynamicMenu( UINT nID );
	afx_msg LRESULT OnResetMenu(WPARAM,LPARAM);

	CBCGPMenuBar* getCBCGPMenuBar()
	{
		return &m_wndMenuBar;
	}

	void resetMenuItems()
	{
		m_wndMenuBar.RestoreOriginalstate();
		m_dynamic_menu.clearMenu();
	}
	
	// 从file文件中读取
	bool loadScriptMenu( const String& filename ,
		const String& menu_name , const int& insert_pos );

	// 从内存数据中读取
	bool loadScriptMenuFromString( const String& content , 
		const String& menu_name , const int& insert_pos );

	void removeAllMenuItems()
	{
		m_wndMenuBar.RemoveAllButtons();
		m_wndMenuBar.AdjustLayout();
		m_wndMenuBar.AdjustSizeImmediate ();
	}
	void removeMenuItem( const int& index )
	{
		m_wndMenuBar.RemoveButton( index );
		m_wndMenuBar.AdjustLayout();
		m_wndMenuBar.AdjustSizeImmediate ();
	}
	// --- dyn menu end

	afx_msg void OnFullScreen();

	DlgTestMultisample test_multisample_dlg; 
	// control bar embedded members
    // CBCGPStatusBar			m_wndStatusBar;
	//CStatusBar				m_wndStatusBar;

	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;

	CBCGPToolBar			m_wndToolBar2_edit;

	CBCGPToolBar			m_wndToolBar3_camera;

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
	
	
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);

	DECLARE_MESSAGE_MAP()
	
	UINT			m_nAppLook;
	bool			InitUIControl(void);

	WINDOWPLACEMENT m_wpPrev;
	CRect			m_FullScreenWindowRect;
	CBCGPToolBar	*m_pwndFullScrnBar;
	bool			m_bFullScreen;
public:
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateViewProperties(CCmdUI *pCmdUI);
	afx_msg void OnViewWorkspace();
	afx_msg void OnUpdateViewWorkspace(CCmdUI *pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI *pCmdUI);
	afx_msg void OnClose();
};


