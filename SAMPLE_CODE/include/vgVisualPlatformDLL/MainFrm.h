// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "vgUIController/vgWorkSpaceBar.h"
#include "vgUIController/WorkSpaceBar2.h"
//#include "vgOutputBar.h"
#include "vgUIController/vgPropertiesViewBar.h"

#include "Resource.h"

#include "vgPropBar.h"
#include "vgWorkbar.h"

#include <vgDlgTestMultisample.h>
#include "DynamicItems.h"

#include <vgKernel/vgkPluginLoader.h>

class CMainFrame : public CBCGPFrameWnd ,
	public vgKernel::PluginLoader
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


	virtual void loadPlugin( const String& plugin_name );

	virtual void unloadPlugin( const String& plugin_name );

	virtual void loadRightMenuPlugin(const String& plugin_name, CMenu& RightMenu);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//BOOL	IsFullScreen();
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
	vgPropBar	/*CBCGPDockingControlBar	*/		m_propBar;
	vgWorkbar	/*CBCGPDockingControlBar	*/		m_workBar;


	CBCGPDropDownToolBar    m_wndToolBarSRShape;
	CBCGPDropDownToolBar    m_wndToolBarSRMode;
	CBCGPDropDownToolBar    m_wndToolBarSMInclude;


	// vgWorkSpaceBar		m_wndWorkSpace;
	// CWorkSpaceBar2		m_wndWorkSpace2;
	//vgOutputBar				m_wndOutput;
	// TabOne				tab;
	// PropertiesTab		pTab;

	// CPropertiesViewBar	m_wndPropertiesView;
	CBCGPToolBarImages		m_UserImages;
	// Generated message map functions
	CMenu *RightMenu;
	CMenu menu;

protected:
		
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	
	afx_msg void OnViewCustomize();
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);

	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);

	DECLARE_MESSAGE_MAP()
	

protected:
	UINT			m_nAppLook;

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

protected:
	bool	InitUIControl(void);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void OnUpdateDynamicMenuUI(CCmdUI* pCmdUI);

	//void loadPluginDLL(const String& dllName);
	//void unloadPluginDLL(const String& dllName);
public:
	afx_msg void OnLoadVtrDll();
	afx_msg void OnUnloadVtrDll();
	afx_msg void OnGisLoadDll();
	afx_msg void OnGisUnloadDll();
	afx_msg void OnShpLoadDll();
	afx_msg void OnShpUnloadDll();
	afx_msg void OnSoundLoadDll();
	afx_msg void OnSoundUnloadDll();
	afx_msg void OnSolarLoadDll();
	afx_msg void OnSolarUnloadDll();
	afx_msg void OnLoadLogoDll();
	afx_msg void OnUnloadLogoDll();
	afx_msg void OnLoadFontDll();
	afx_msg void OnUnloadFontDll();
	afx_msg void OnLoadDbDll();
	afx_msg void OnUnloadDbDll();
	afx_msg void OnScriptLoad();
	afx_msg void OnScriptUnload();
	afx_msg void OnPlandllLoad();
	afx_msg void OnPlandllUnload();
	virtual void ActivateFrame(int nCmdShow = -1);
	afx_msg void OnStopdemocreate();
	afx_msg void OnRotoview();
	afx_msg void OnOnOffFullscreen();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
};


