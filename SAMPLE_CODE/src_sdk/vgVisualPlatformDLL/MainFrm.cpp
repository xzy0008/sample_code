// MainFrm.cpp : implementation of the CMainFrame class
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "MainFrm.h"

#include "vgEntry/vgRootEntry.h"
#include "vgEntry/vgCamMgrEntry.h"
#include "vgUIController/vgPropertyPage.h"

#include <vgRoot.h>
#include <vgMesh/vgmMeshManager.h>

#include "res.h"

#include <vgDlgTestMultisample.h>

#include <vgUIController/vgUIController.h>
#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdProfileManager.h>
#include <vgScript/vgscScriptManager.h>


#include "vgUserScriptSystem.h"
#include "vgUserScriptOtherModules.h"

#include <vgGlobal/vggVgmodUtility.h>
#include <vgMod/vgTriggerManager.h>
#include <vgMod/vgModMisc.h>
#include <vgMovingManager.h>

// 在导入头文件前定义 DYNAMIC_MENU_EXEC_MODULE 
// 指明是EXE在使用动态菜单
#define DYNAMIC_MENU_EXEC_MODULE
#include <vgDynamicMenu/menu_plugin_api.h>

#include <vgkernel/vgkPlugin.h>
#include <vgSolar/vgsoDefinition.h>
#include <vgkernel/vgkPluginManager.h>
#include <vgDatabase/vgdDefinition.h>

#include <vgScript/vgscDefinition.h>
//#include <vgSound/vgSoundDefinition.h>
#include <vgScript/vgscScriptManager.h>

#include <vgKernel/vgkInputSystem.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

const	int  iMaxUserToolbars		= 10;

static	UINT s_MainMenuLastID	= 43286;//同res.h的_APS_NEXT_COMMAND_VALUE

const	UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const	UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

static	UINT s_firstMenu = s_MainMenuLastID;
static	UINT s_lastMenu = s_MainMenuLastID; 

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(NID_VIEW_CUSTOMIZE, OnViewCustomize)
	//ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND_RANGE(NID_VIEW_APPLOOK_2000, NID_VIEW_APPLOOK_VS2008, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(NID_VIEW_APPLOOK_2000, NID_VIEW_APPLOOK_VS2008, OnUpdateAppLook)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	//ON_COMMAND(NID_VIEW_HELLO, &CMainFrame::OnTestUpdate)

	ON_WM_GETMINMAXINFO()
	ON_COMMAND(NID_VIEW_FULLSCREEN, &CMainFrame::OnFullScreen)
	ON_COMMAND(NID_SFULLSCREEN, &CMainFrame::OnFullScreen)

	ON_COMMAND(NID_VIEW_PROPERTIES, &CMainFrame::OnViewProperties)
	ON_UPDATE_COMMAND_UI(NID_VIEW_PROPERTIES, &CMainFrame::OnUpdateViewProperties)
	ON_COMMAND(NID_VIEW_WORKSPACE, &CMainFrame::OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(NID_VIEW_WORKSPACE, &CMainFrame::OnUpdateViewWorkspace)
	ON_COMMAND(NID_VIEW_OUTPUT, &CMainFrame::OnViewOutput)
	ON_UPDATE_COMMAND_UI(NID_VIEW_OUTPUT, &CMainFrame::OnUpdateViewOutput)
	ON_WM_CLOSE()

	ON_REGISTERED_MESSAGE(BCGM_RESETMENU, OnResetMenu)
	ON_COMMAND_RANGE( ID_POPUP_DynCmd01, ID_POPUP_DynCmd01 + CDynamicItems::GetNbMaxItems(), OnExecuteDynamicMenu )

	ON_COMMAND(ID_LOAD_VTR_DLL, &CMainFrame::OnLoadVtrDll)

	// auto menu
	ON_UPDATE_COMMAND_UI_RANGE(s_MainMenuLastID, s_MainMenuLastID + 500, &CMainFrame::OnUpdateDynamicMenuUI)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND(ID_UNLOAD_VTR_DLL, &CMainFrame::OnUnloadVtrDll)
	ON_COMMAND(ID_GIS_LOAD_DLL, &CMainFrame::OnGisLoadDll)
	ON_COMMAND(ID_GIS_UNLOAD_DLL, &CMainFrame::OnGisUnloadDll)
	ON_COMMAND(ID_SHP_LOAD_DLL, &CMainFrame::OnShpLoadDll)
	ON_COMMAND(ID_SHP_UNLOAD_DLL, &CMainFrame::OnShpUnloadDll)
	ON_COMMAND(ID_SOUND_LOAD_DLL, &CMainFrame::OnSoundLoadDll)
	ON_COMMAND(ID_SOUND_UNLOAD_DLL, &CMainFrame::OnSoundUnloadDll)
	ON_COMMAND(ID_SOLAR_LOAD_DLL, &CMainFrame::OnSolarLoadDll)
	ON_COMMAND(ID_SOLAR_UNLOAD_DLL, &CMainFrame::OnSolarUnloadDll)
	ON_COMMAND(ID_LOAD_LOGO_DLL, &CMainFrame::OnLoadLogoDll)
	ON_COMMAND(ID_UNLOAD_LOGO_DLL, &CMainFrame::OnUnloadLogoDll)
	ON_COMMAND(ID_LOAD_FONT_DLL, &CMainFrame::OnLoadFontDll)
	ON_COMMAND(ID_UNLOAD_FONT_DLL, &CMainFrame::OnUnloadFontDll)
	ON_COMMAND(ID_LOAD_DB_DLL, &CMainFrame::OnLoadDbDll)
	ON_COMMAND(ID_UNLOAD_DB_DLL, &CMainFrame::OnUnloadDbDll)
	ON_COMMAND(ID_SCRIPT_LOAD, &CMainFrame::OnScriptLoad)
	ON_COMMAND(ID_SCRIPT_UNLOAD, &CMainFrame::OnScriptUnload)
	ON_COMMAND(ID_PLANDLL_LOAD, &CMainFrame::OnPlandllLoad)
	ON_COMMAND(ID_PLANDLL_UNLOAD, &CMainFrame::OnPlandllUnload)

	ON_COMMAND(ID_STOPDEMOCREATE, &CMainFrame::OnStopdemocreate)
	ON_COMMAND(ID_ROTOVIEW, &CMainFrame::OnRotoview)
	ON_COMMAND(ID_ONOFFFULLSCREEN, &CMainFrame::OnOnOffFullscreen)
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_PROGRESS,	// progress bar
	ID_SEPARATOR,			// text label
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

vgCore::Root *p_root = new vgCore::Root("win_log.log");  //李文的全局变量


// CMainFrame construction/destruction

CMainFrame::CMainFrame()//:tab(new int(1))
{
	m_bFullScreen = false;
	// m_nAppLook = theApp.GetInt (_T("ApplicationLook"), NID_VIEW_APPLOOK_VS2005);
	// TODO: add member initialization code here
	m_nAppLook = NID_VIEW_APPLOOK_2007;

	// 为使用动态菜单，关闭自动检测
	m_bAutoMenuEnable = false;
	RightMenu = NULL;
	menu.LoadMenu(IDR_RIGHT_FLOATINGMENU);
}

CMainFrame::~CMainFrame()
{
	//vgUI::UIController::getSingleton().unload();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	vgKernel::PluginManager::getSingleton().registerLoader( this );

	test_multisample_dlg.DoModal();


	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	OnAppLook (m_nAppLook);

	// VISUAL_MANAGER
	
	if (CBCGPToolBar::GetUserImages () == NULL)
	{
		// Load toolbar user images:
		if (!m_UserImages.Load (_T(".\\UserImages.bmp")))
		{
			//TRACE(_T("Failed to load user images\n"));
		}
		else
		{
			CBCGPToolBar::SetUserImages (&m_UserImages);
		}
	}

	CBCGPToolBar::EnableQuickCustomization ();


	// TODO: Define your own basic commands. Be sure, that each pulldown 
	// menu have at least one basic command.

	CList<UINT, UINT>	lstBasicCommands;

	//lstBasicCommands.AddTail( ID_SCENE_READ );


	//CBCGPToolBar::SetBasicCommands (lstBasicCommands);



// 	for (int i=0; i<100000; i++)
// 	{
// 		lstBasicCommands.AddTail(i);
// 	}

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	CBCGPToolBar::SetMenuSizes (CSize (22, 22), CSize (16, 16));


	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) >= 16;

	UINT uiToolbarHotID = bIsHighColor ? NIDB_TOOLBAR256 : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(NIDR_MAINFRAME, 0, 
		NIDB_TOOLBAR256_S, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// 编辑工具条的选择形状
	if (!m_wndToolBarSRShape.Create(this,
		WS_CHILD|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		IDR_TOOLBAR_SR_SHAPE) || 
		!m_wndToolBarSRShape.LoadToolBar (IDR_TOOLBAR_SR_SHAPE))
	{
		TRACE0("Failed to create build toolbar\n");
		return -1;      // fail to create
	}


	// 编辑工具条的选区模式
	if (!m_wndToolBarSRMode.Create(this,
		WS_CHILD|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		IDR_TOOLBAR_SR_MODE) || 
		!m_wndToolBarSRMode.LoadToolBar (IDR_TOOLBAR_SR_MODE))
	{
		TRACE0("Failed to create build toolbar\n");
		return -1;      // fail to create
	}
	
	// 编辑工具条的全包含还是相交
	if (!m_wndToolBarSMInclude.Create(this,
		WS_CHILD|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		IDR_TOOLBAR_SM_INCLUDE) || 
		!m_wndToolBarSMInclude.LoadToolBar (IDR_TOOLBAR_SM_INCLUDE))
	{
		TRACE0("Failed to create build toolbar\n");
		return -1;      // fail to create
	}

	// 编辑工具条
	UINT uiToolbarHotID_EDIT = bIsHighColor ? IDB_BITMAP_EDIT : 0;

	if (!m_wndToolBar2_edit.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_TOOLBAR_EDIT_ID)||
		!m_wndToolBar2_edit.LoadToolBar(IDR_TOOLBAR1_EDIT, 0, 
		IDB_BITMAP_EDIT_S, FALSE, 0, 0, uiToolbarHotID_EDIT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// 相机工具条
	UINT uiToolbarHotID_camera = bIsHighColor ? IDB_BITMAP_CAMERA : 0;

	if (!m_wndToolBar3_camera.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_TOOLBAR_CAMERA_ID ) ||
		!m_wndToolBar3_camera.LoadToolBar(IDR_TOOLBAR_CAMERA, 0, 
		IDB_BITMAP_CAMERA_S, FALSE, 0, 0, uiToolbarHotID_camera))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar3_camera.AdjustLayout();

	// new 初始化状态栏 =============================================================
	CBCGPStatusBar *pStatusBar = vgUI::UIController::getSingleton().GetStatusBar();

	if (!pStatusBar->Create(this) ||
		!pStatusBar->SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	pStatusBar->SetPaneStyle (vgUI::UIController::StatusInfo, SBPS_STRETCH | SBPS_NOBORDERS);
	

#if VGK_LANG_CHS
	// 遮挡剔除信息栏
	pStatusBar->SetPaneWidth(vgUI::UIController::StatusOcc, 80);
	pStatusBar->SetPaneText(vgUI::UIController::StatusOcc, "遮挡剔除");

	// 帧速信息栏
	pStatusBar->SetPaneWidth (vgUI::UIController::StatusFrame, 50);
	pStatusBar->SetPaneText(vgUI::UIController::StatusFrame, "帧速");
#else
	// 遮挡剔除信息栏
	pStatusBar->SetPaneWidth(vgUI::UIController::StatusOcc, 80);
	pStatusBar->SetPaneText(vgUI::UIController::StatusOcc, "Occ");

	// 帧速信息栏
	pStatusBar->SetPaneWidth (vgUI::UIController::StatusFrame, 50);
	pStatusBar->SetPaneText(vgUI::UIController::StatusFrame, "Frame");
#endif


	// 设置进度条
	pStatusBar->SetPaneWidth (vgUI::UIController::StatusProgress, 80);
	pStatusBar->EnablePaneProgressBar (vgUI::UIController::StatusProgress, -1);
	pStatusBar->SetPaneText(vgUI::UIController::StatusProgress, "");

	// ===========================================================================

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (NIDB_WORKSPACE);
	
	// vgWorkSpaceBar* workspace = vgUI::UIController::getSingleton().GetWorkSpaceBar();
	vgUI::UIController::getSingleton().SetWorkSpaceBar(&m_workBar);

#if VGK_LANG_CHS
	if (!m_workBar.Create (_T("节点视图"),this, CRect (0, 0, 200, 200),
		TRUE,
		NID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS,  /*~CBRS_BCGP_AUTOHIDE*/dwDefaultBCGDockingBarStyle))	//@FengYK 2009/11/26
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}
#else
	if (!workspace->Create (_T("Scene graph"),this, CRect (0, 0, 200, 200),
		TRUE,
		NID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS,  /*~CBRS_BCGP_AUTOHIDE*/dwDefaultBCGDockingBarStyle))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}
#endif

	m_workBar.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);


#if VGK_LANG_CHS
	if (!vgUI::UIController::getSingleton().GetOutputBar()->Create (_T("提示信息"), this, CSize (150, 150),
		TRUE /* Has gripper */, NID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, CBRS_BCGP_REGULAR_TABS,  /*~CBRS_BCGP_AUTOHIDE*/dwDefaultBCGDockingBarStyle))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}
#else
	if (!vgUI::UIController::getSingleton().GetOutputBar()->Create (_T("Tips"), this, CSize (150, 150),
		TRUE /* Has gripper */, NID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, CBRS_BCGP_REGULAR_TABS,  /*~CBRS_BCGP_AUTOHIDE*/dwDefaultBCGDockingBarStyle))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}
#endif

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (NIDS_MAIN_TOOLBAR);
	

#if VGK_LANG_CHS
	m_wndToolBar.SetWindowText ("标准");
	m_wndToolBar2_edit.SetWindowText ("编辑");
	m_wndToolBar3_camera.SetWindowText ("相机");
#else
	m_wndToolBar.SetWindowText ("Standard");
	m_wndToolBar2_edit.SetWindowText ("Edit");
	m_wndToolBar3_camera.SetWindowText ("Camera");
#endif

	vgUI::UIController::getSingleton().SetPropertiesViewBar(&m_propBar);
	//vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();
	//pageViewBar->m_bDisableAnimation = true;
	
	// Create propertise view added by zsc
	// 创建 PropertiesBar
#if VGK_LANG_CHS
	if (!m_propBar.Create (_T("属性栏"), this, CRect (0, 0, 300, 200),
		TRUE, 
		NID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS,  /*~CBRS_BCGP_AUTOHIDE*/dwDefaultBCGDockingBarStyle))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}
#else
	if (!pageViewBar->Create (_T("Properties"), this, CRect (0, 0, 300, 200),
		TRUE, 
		NID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS,  /*~CBRS_BCGP_AUTOHIDE*/dwDefaultBCGDockingBarStyle))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}
#endif

	// 设置属性页图标 在DOCK时显示
	HICON hPropertiesBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
		MAKEINTRESOURCE (NIDR_MAINFRAME),
		IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_propBar.SetIcon (hPropertiesBarIcon, FALSE);



	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarSRShape.EnableDocking( CBRS_ALIGN_ANY );
	m_wndToolBarSRMode.EnableDocking( CBRS_ALIGN_ANY );
	m_wndToolBarSMInclude.EnableDocking( CBRS_ALIGN_ANY );
	m_wndToolBar2_edit.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar3_camera.EnableDocking(CBRS_ALIGN_ANY);

	m_workBar.EnableDocking(CBRS_ALIGN_ANY);

	// m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	vgUI::UIController::getSingleton().GetOutputBar()->EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);

	DockControlBar(&m_wndToolBar3_camera);
	DockControlBarLeftOf (&m_wndToolBar2_edit, &m_wndToolBar3_camera);
	DockControlBarLeftOf (&m_wndToolBar, &m_wndToolBar2_edit);


	//DockControlBar(&m_wndToolBar);
	//DockControlBar(&m_wndToolBar2_edit);
	////DockControlBar(&m_wndToolBar3_camera);
	//DockControlBarLeftOf (&m_wndToolBar3_camera, &m_wndToolBar);
	
	//DockControlBarLeftOf (&m_wndToolBar2_edit, &m_wndToolBar3_camera);


	DockControlBar(&m_workBar);
	// m_wndWorkSpace2.AttachToTabWnd(workspace, BCGP_DM_STANDARD, FALSE, NULL);
	// 开启Dock
	m_propBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_propBar);
	DockControlBar(vgUI::UIController::getSingleton().GetOutputBar());


#if VGK_LANG_CHS
	m_wndToolBar.EnableCustomizeButton (TRUE, NID_VIEW_CUSTOMIZE, _T("订制..."));
	m_wndToolBar2_edit.EnableCustomizeButton (TRUE, NID_VIEW_CUSTOMIZE, _T("订制..."));
	m_wndToolBar3_camera.EnableCustomizeButton (TRUE, NID_VIEW_CUSTOMIZE, _T("订制..."));
#else
	m_wndToolBar.EnableCustomizeButton (TRUE, NID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_wndToolBar2_edit.EnableCustomizeButton (TRUE, NID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_wndToolBar3_camera.EnableCustomizeButton (TRUE, NID_VIEW_CUSTOMIZE, _T("Customize..."));

#endif

	// Allow user-defined toolbars operations:
	InitUserToobars (NULL,
					uiFirstUserToolBarId,
					uiLastUserToolBarId);

#if VGK_LANG_CHS
	// Enable control bar context menu (list of bars + customize command):
	EnableControlBarMenu (	
		TRUE,				// Enable
		NID_VIEW_CUSTOMIZE, 	// Customize command ID
		_T("定制..."),	// Customize command text
		NID_VIEW_TOOLBARS,
		FALSE, TRUE);	// Menu items with this ID will be replaced by
							// toolbars menu
#else
	// Enable control bar context menu (list of bars + customize command):
	EnableControlBarMenu (	
		TRUE,				// Enable
		NID_VIEW_CUSTOMIZE, 	// Customize command ID
		_T("Customize..."),	// Customize command text
		NID_VIEW_TOOLBARS,
		FALSE, TRUE);	// Menu items with this ID will be replaced by
	// toolbars menu
#endif

	vgKernel::InputSystem::getSingleton().initialise(AfxGetApp()->m_hInstance, AfxGetMainWnd()->GetSafeHwnd() );

	this->InitUIControl();

	EnableFullScreenMode(NID_VIEW_FULLSCREEN);
	EnableFullScreenMainMenu(FALSE);	

	return 0;
}

void CMainFrame::OnDestroy()
{

	vgUI::UIController::getSingleton().unload();

	CBCGPFrameWnd::OnDestroy();

	//CPropertiesViewBar::DestoryInstance();
	//vgUI::UIController::DestoryInstance();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style=WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST | WS_MAXIMIZE;

	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	/*int maxx = GetSystemMetrics(SM_CXSCREEN);
	int maxy = GetSystemMetrics(SM_CYSCREEN);
	
	cs.x        = 0 ;
	cs.y        = 0 ;
	cs.cx       = maxx;
	cs.cy       = maxy;*/
//#if VG_EXPLORER_AUTO_LOAD
//	cs.x        = maxx/2 - 200 ;
//	cs.y        = maxy/2  - 200 ;
//	cs.cx       = 400;
//	cs.cy       = 400;
//	cs.lpszName = "VRGIS Explorer";
//#else
	//cs.x        = maxx/10 ;
	//cs.y        = maxy/10 ;
	//cs.cx       = 4*maxx/5;
	//cs.cy       = 4*maxy/5;
	//cs.lpszName = "VRGIS Editor Edition";
//#endif 

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */);

	pDlgCust->EnableUserDefinedToolbars ();
	pDlgCust->Create ();
}

//afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
//{
//	// TODO: reset toolbar with id = (UINT) wp to its initial state:
//	//
//	// UINT uiToolBarId = (UINT) wp;
//	// if (uiToolBarId == NIDR_MAINFRAME)
//	// {
//	//		do something with m_wndToolBar
//	// }
//
//	return 0;
//}

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case NID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case NID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case NID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case NID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case NID_VIEW_APPLOOK_2007:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		break;

	case NID_VIEW_APPLOOK_2007_1:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);

		break;
	case NID_VIEW_APPLOOK_2007_2:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
		break;

	case NID_VIEW_APPLOOK_2007_3:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
		break;


	case NID_VIEW_APPLOOK_VS2005:
		// enable VS 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case NID_VIEW_APPLOOK_VS2008:
		// enable VS 2008 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}
 // RIBBON_APP

bool CMainFrame::InitUIControl(void)
{

	VGK_SHOW(" Welcome to VR-GIS platform! \r\n");
	
	vgUI::UIController::getSingleton().SetFrameSpeed(50);

	// vgTestNode1 node("World"); // 导致无效的引用
	// 不必担心内存泄露，UIController会负责释放内存

	vgUI::UIController::getSingleton().initUIControl();
///////////////////////////////////////////////////////////////////
// 	vgBaseEntry *node = new vgRootEntry();
// 	HTREEITEM root = vgUI::UIController::getSingleton().AddNode(node);
// 
// 
// 	//就只有这一个!
// 	node = new vgCamMgrEntry();
// 	vgUI::UIController::getSingleton().AddNode(node);
///////////////////////////////////////////////////////////////////
	/*vgUI::UIController::getSingleton().AddNode(root, node);

	node = new vgRootEntry();
	vgUI::UIController::getSingleton().AddNode(root, node);*/

// 	node = new vgTestNode1("TestNodo1");
// 	vgUI::UIController::getSingleton().AddNode(root, node);
// 
// 	node = new vgTestNode1("TestNode2");
// 	vgUI::UIController::getSingleton().AddNode(root, node);
	
	//node = new vgObjectNode("Line1");
	//vgUI::UIController::getSingleton().AddNode(root, node);

	//node = new vgObjectNode("Box1");
	//vgUI::UIController::getSingleton().AddNode(root, node);

	//node = new vgObjectNode("Box2");
	//vgUI::UIController::getSingleton().AddNode(root, node);
	//
// 	HTREEITEM itemArray[10];
// 
// 	CTreeCtrl *pTree = (CTreeCtrl*)GetDlgItem(NIDC_TREE1);
// 
// 	CString strName;
// 
// 	for (int i=0; i<10; i++)
// 	{
// 		strName.Format(_T("Item Array %d"), i);
// 		node = new vgRootEntry(strName.GetString());
// 		itemArray[i] = vgUI::UIController::getSingleton().AddNode(root, node);
// 	}
// 	
// 	int j = -1;
// 
// 	for (int i=0; i<20000; i++)
// 	{
// 		if (i % 2000 == 0)
// 		{
// 			j ++;
// 			//TRACE("=");
// 		}
// 
// 		strName.Format("Node %d", i);
// 		node= new vgTestNode1(strName.GetString());
// 		vgUI::UIController::getSingleton().AddNode(itemArray[j], node);
// 
// 	}


	return true;
}

//void CMainFrame::OnTestUpdate()
//{
//	assert(0);
//
//#if 0
//	//TRACE("SIZE : %d \n", sizeof(vgObjectNode));
//
//	//TRACE("触发Update \n");
//	vgTestNode1* node = dynamic_cast<vgTestNode1*> (vgUI::UIController::getSingleton().GetNode("TestNodo1"));
//
//	if (node != NULL)
//	{
//		//TRACE("获得node成功 \n");
//		vgUI::UIController::getSingleton().SelectNode(node);
//	
//		if (vgUI::UIController::getSingleton().GetCurrentSelectedNode() == node)
//			//TRACE("确认选择 \n");
//	}
//
//	float val = 0.f;
//
//	for (int i=0; i<10; i++)
//	{
//		//TRACE("更新数据 \n");
//		node->SetPosX(val);
//		node->SetPosY(val+1);
//		
//		node->SetCaption("新的标题");
//		node->SetEnable(TRUE);
//
//		node->SetSize(22);
//		val += 10.f;
//		Sleep(100);
//	}
//
//#endif
//}

void CMainFrame::OnFullScreen()
{
	//TRACE("FullScreen \n");

	//ShowFullScreen();
	this->vg_ShowFullScreen(0, 0, 2, 2);
	return ;

	RECT rectDesktop;
	WINDOWPLACEMENT wpNew;

	if (!IsFullScreen())
	{
		// need to hide all status bars
		// m_wndStatusBar.ShowWindow(SW_HIDE);
		// m_wndToolBar.ShowWindow(SW_HIDE);

		vgUI::UIController::getSingleton().GetOutputBar()->Slide(TRUE);

		//m_wndStatusBar.ShowControlBar(FALSE, FALSE, TRUE);
		vgUI::UIController::getSingleton().GetStatusBar()->ShowControlBar(FALSE, FALSE, TRUE);
		m_wndToolBar.ShowControlBar(FALSE, FALSE, TRUE);

		m_wndToolBar2_edit.ShowControlBar(FALSE, FALSE, TRUE);

		m_wndMenuBar.ShowControlBar(FALSE, FALSE, TRUE);
		vgUI::UIController::getSingleton().GetOutputBar()->ShowControlBar(FALSE, FALSE, TRUE);
		vgUI::UIController::getSingleton().GetPropertiesViewBar()->ShowControlBar(FALSE, TRUE, TRUE);
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->ShowControlBar(FALSE, TRUE, TRUE);
//		m_wndWorkSpace2.ShowControlBar(FALSE, TRUE, TRUE);


		// We'll need these to restore the original state.
		GetWindowPlacement (&m_wpPrev);

		m_wpPrev.length = sizeof m_wpPrev;

		//Adjust RECT to new size of window
		::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
		::AdjustWindowRectEx(&rectDesktop, GetStyle(), TRUE, GetExStyle());

		// Remember this for OnGetMinMaxInfo()
		m_FullScreenWindowRect = rectDesktop;

		wpNew = m_wpPrev;
		wpNew.showCmd =  SW_SHOWNORMAL;
		wpNew.rcNormalPosition = rectDesktop;

		m_pwndFullScrnBar=new CBCGPToolBar;
		// 修改NIDB_TOOLBAR256更换图标
		if (!m_pwndFullScrnBar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
			!m_pwndFullScrnBar->LoadToolBar(NIDR_FULLSCREEN, 0, 0, FALSE, 0, 0, NIDB_TOOLBAR256))
		{
			TRACE0("Failed to create toolbar\n");
			return ;
		}

		//don't allow the toolbar to dock
		m_pwndFullScrnBar->EnableDocking(0);
		m_pwndFullScrnBar->SetWindowPos(0, 100,100, 0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);   
#if VGK_LANG_CHS

		m_pwndFullScrnBar->SetWindowText(_T("提示"));
		m_pwndFullScrnBar->SetToolBarBtnText(0, _T("关闭全屏"));
#else
		m_pwndFullScrnBar->SetWindowText(_T("Tips"));
		m_pwndFullScrnBar->SetToolBarBtnText(0, _T("Escape Fullscreen"));
#endif
		//FloatControlBar(m_pwndFullScrnBar, CPoint(100,100));
		m_pwndFullScrnBar->FloatControlBar(CRect());
		m_bFullScreen=TRUE;
	}
	else
	{
		m_pwndFullScrnBar->DestroyWindow();
		delete m_pwndFullScrnBar;

		m_bFullScreen=FALSE;

		m_wndMenuBar.ShowControlBar(TRUE, TRUE, TRUE);
//		m_wndStatusBar.ShowControlBar(TRUE, TRUE, TRUE);
		vgUI::UIController::getSingleton().GetStatusBar()->ShowControlBar(TRUE, TRUE, TRUE);
		m_wndToolBar.ShowControlBar(TRUE, TRUE, TRUE);

		m_wndToolBar2_edit.ShowControlBar(TRUE, TRUE, TRUE);


		vgUI::UIController::getSingleton().GetOutputBar()->ShowControlBar(TRUE, TRUE, TRUE);
//		m_wndWorkSpace2.ShowControlBar(TRUE, TRUE, TRUE);
		vgUI::UIController::getSingleton().GetPropertiesViewBar()->ShowControlBar(TRUE, TRUE, TRUE);
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->ShowControlBar(TRUE, TRUE, TRUE);


		wpNew = m_wpPrev;
	}

	SetWindowPlacement ( &wpNew );
}

//BOOL CMainFrame::IsFullScreen()
//{
//	return m_bFullScreen;
//}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

// 	if (IsFullScreen())
// 	{
// 		lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
// 		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
// 		lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
// 		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
// 	}

	CBCGPFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnViewProperties()
{
	vgUI::UIController::getSingleton().GetPropertiesViewBar()->ShowControlBar (
		!vgUI::UIController::getSingleton().GetPropertiesViewBar()->IsVisible() , FALSE, TRUE);
}


void CMainFrame::OnUpdateViewProperties(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( vgUI::UIController::getSingleton().GetPropertiesViewBar()->IsVisible() );
}

void CMainFrame::OnViewWorkspace()
{
	vgUI::UIController::getSingleton().GetWorkSpaceBar()->ShowControlBar (
		!vgUI::UIController::getSingleton().GetWorkSpaceBar()->IsVisible() , FALSE, TRUE);
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( vgUI::UIController::getSingleton().GetWorkSpaceBar()->IsVisible() );
}

void CMainFrame::OnViewOutput()
{
	vgUI::UIController::getSingleton().GetOutputBar()->ShowControlBar (
		!vgUI::UIController::getSingleton().GetOutputBar()->IsVisible() , FALSE, TRUE);
}

void CMainFrame::OnUpdateViewOutput(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( vgUI::UIController::getSingleton().GetOutputBar()->IsVisible() );
}

void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//Set
	/*WINDOWPLACEMENT wp;
	wp.length=sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		wp.flags|=WPF_RESTORETOMAXIMIZED;
		WriteWindowPlacement(&wp);
	}*/

	int maxx = GetSystemMetrics(SM_CXSCREEN);
	int maxy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos (NULL , 0 , 0 , maxx, maxy,SWP_NOMOVE|SWP_NOZORDER);

	CBCGPFrameWnd::OnClose();


}

void CMainFrame::OnExecuteDynamicMenu( UINT nID )
{
#if 0
	{
		CString strItemText = m_dynamic_menu.GetItemText(nID).c_str();

		// Retrieve the selected dynamic item associated comment
		CString strItemComment = m_dynamic_menu.GetItemComment(nID).c_str();

		CString func = m_dynamic_menu.GetItemFunctionType(nID).c_str();

		// Display it.

		CString strMsg="";

		strMsg.Format("Cmd %d selected.\nItem Name:%s\nCommnet:%s\nfunc:%s",
			(nID -ID_POPUP_DynCmd01), strItemText,             
			strItemComment ,func );

		AfxMessageBox(strMsg);
	}

#endif
	// Retrieve the selected dynamic item Name

	//CString func_name = m_dynamic_menu.GetItemFunctionType(nID).c_str();

	//CString strMsg="";

	//strMsg.Format("Cmd %d selected.\nFunc Name: %s",
	//	(nID -ID_POPUP_DynCmd01), func_name );

	//AfxMessageBox(strMsg);


	//String scriptstr = m_dynamic_menu.GetItemComment( nID );

	String scriptstr = m_dynamic_menu.GetItemFunctionType( nID );

	//AfxMessageBox(scriptstr.c_str());

	vgScript::ScriptManager::getSingleton().runScriptString( scriptstr );
}

LRESULT CMainFrame::OnResetMenu( WPARAM,LPARAM )
{


	//CMenu menu;
	//menu.LoadMenu (IDR_DYNAMIC_MENU2); 

	//m_wndMenuBar.InsertButton (CBCGPToolbarMenuButton (0, menu, -1, _T ("&DynamicMenu")));

	//m_wndMenuBar.AdjustLayout();
	//m_wndMenuBar.AdjustSizeImmediate ();


	return 0;
}

bool CMainFrame::loadScriptMenu( const String& filename ,
								const String& menu_name , const int& insert_pos )
{

	if ( m_dynamic_menu.readFromFile( filename.c_str() ) )
	{
		m_dynamic_menu.add( insert_pos , menu_name );
		return true;
	}

	return false;
}

bool CMainFrame::loadScriptMenuFromString( const String& content , const String& menu_name , const int& insert_pos )
{
	if ( m_dynamic_menu.readFromString( content.c_str() ) )
	{
		m_dynamic_menu.add( insert_pos , menu_name );
		return true;
	}

	return false;
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	UINT nSendMsg = 0 ;

	PluginPointerVec& pluginVec = *vgKernel::PluginManager::getSingleton().getPluginVecRef();

	for (int i=0; i<pluginVec.size(); i++)
	{
		vgKernel::Plugin *pPlugin = pluginVec[i];

		if ( ::GetExtMenuItem( pPlugin->getPluginHandle(), (UINT)wParam, &nSendMsg ) != FALSE )
		{
			CWnd * pWnd = GetDlgItem( pPlugin->getCmdWndId() ) ;

			if ( pWnd != NULL && pWnd->GetSafeHwnd() != NULL )
			{
				VGK_DLL_RES_SWITCH_NAME( pPlugin->getName().c_str() );
				this->GetActiveView()->SetTimer(1, 150, NULL);

				BOOL re = (BOOL)pWnd->SendMessage( nSendMsg, 0, 0 ) ;

				this->GetActiveView()->SetTimer(1, 15, NULL);

				return re;
			}

		}
	}

	//UINT nSendRightMsg = 0 ;	

	//for (int i=0; i<pluginVec.size(); i++)
	//{
	//	vgKernel::Plugin *pPlugin = pluginVec[i];

	//	if ( ::GetRightExtMenuItem( pPlugin->getPluginHandle(), (UINT)wParam, &nSendRightMsg ) != FALSE )
	//	{
	//		CWnd * pRightWnd = GetDlgItem( pPlugin->getCmdWindowId() ) ;

	//		if ( pPlugin != NULL && pRightWnd->GetSafeHwnd() != NULL )
	//		{
	//			VGK_DLL_RES_SWITCH_NAME( pPlugin->getName().c_str() );
	//			this->GetActiveView()->SetTimer(1, 150, NULL);

	//			BOOL rest = (BOOL)pRightWnd->SendMessage( nSendRightMsg, 0, 0 ) ;

	//			this->GetActiveView()->SetTimer(1, 15, NULL);

	//			return rest;
	//		}

	//	}		
	//}

	return CBCGPFrameWnd::OnCommand(wParam, lParam);	
	//return CFrameWnd::OnCommand(wParam, lParam);
}


void CMainFrame::OnUpdateDynamicMenuUI(CCmdUI* pCmdUI)
{
	PluginPointerVec& pluginVec = *vgKernel::PluginManager::getSingleton().getPluginVecRef();
	
	for (int i=0; i<pluginVec.size(); i++)
	{
		vgKernel::Plugin *pPlugin = pluginVec[i];
		if (pPlugin == NULL)
		{
			continue;
		}

		UINT re = ::GetExtMenuCheck(pPlugin->getPluginHandle(), pCmdUI->m_nID);

		if ( re != -1 )
		{
			if (re == 0)
			{
				pCmdUI->SetCheck(false);
			}
			else
			{
				pCmdUI->SetCheck(true);
			}

			re = ::GetExtMenuEnable(pPlugin->getPluginHandle(), pCmdUI->m_nID);
			if (re == 0)
			{
				pCmdUI->Enable(false);
			}
			else
			{
				pCmdUI->Enable(true);
			}

			return ;
		}

		///*UINT rest = ::GetRightExtMenuCheck(pPlugin->getPluginHandle(), pCmdUI->m_nID);

		//if ( rest != -1 )
		//{
		//	if (rest == 0)
		//	{
		//		pCmdUI->SetCheck(false);
		//	}
		//	else
		//	{
		//		pCmdUI->SetCheck(true);
		//	}

		//	rest = ::GetRightExtMenuEnable(pPlugin->getPluginHandle(), pCmdUI->m_nID);
		//	if (rest == 0)
		//	{
		//		pCmdUI->Enable(false);
		//	}
		//	else
		//	{
		//		pCmdUI->Enable(true);
		//	}

		//	return ;
		//}*/
	}
}

//void CMainFrame::loadPluginDLL(const String& dllName)
//{
//	VGK_DLL_LOAD( dllName.c_str() );
//
//	vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef(dllName);
//
//	if (plugin == NULL)
//	{
//		return ;
//	}
//
//	HMODULE hModule = plugin->getPluginHandle();
//
//	CBCGPMenuBar* menubar = &this->m_wndMenuBar;
//
//	if (::InstallExtMenu(hModule, this->GetSafeHwnd(), menubar, plugin->getCmdWndId(), &s_lastMenu) == FALSE)
//	{
//		AfxMessageBox("Failed to load dll menu");
//	}
//}

//void CMainFrame::unloadPluginDLL(const String& dllName)
//{
//	vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef(dllName);
//
//	if (plugin == NULL)
//	{
//		return ;
//	}
//
//	if ( ! ::RemoveExtMenu(plugin->getPluginHandle()) )
//	{
//		AfxMessageBox("Failed on load dll menu");
//	}
//
//	VGK_DLL_UNLOAD( dllName.c_str() );
//}


void CMainFrame::OnLoadVtrDll()
{
	// TODO: 在此添加命令处理程序代码
	if ( VGK_DLL_CHECK_LOAD(VGT_DLL_NAME) )
	{
		VGK_DLL_UNLOAD( VGT_DLL_NAME );
		VGK_DLL_LOAD( VGT_DLL_NAME );
	} 
	else
	{
		VGK_DLL_LOAD( VGT_DLL_NAME );
	}

	VGK_DLL_LOAD( "vgMenuGisAnalysisEMeiDLL_Debug.dll" );

}	


void CMainFrame::OnUnloadVtrDll()
{
	VGK_DLL_UNLOAD( VGT_DLL_NAME );
	VGK_DLL_UNLOAD( "vgMenuGisAnalysisEMeiDLL_Debug.dll" );

}

void CMainFrame::OnGisLoadDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_LOAD(VGG_DLL_NAME);
}

void CMainFrame::OnGisUnloadDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_UNLOAD(VGG_DLL_NAME);
}

void CMainFrame::OnShpLoadDll()
{
	// TODO: 在此添加命令处理程序代码
	//VGK_DLL_LOAD(VGSH_DLL_NAME);
}

void CMainFrame::OnShpUnloadDll()
{
	// TODO: 在此添加命令处理程序代码
	//VGK_DLL_UNLOAD(VGSH_DLL_NAME);
}

void CMainFrame::OnSoundLoadDll()
{
	//VGK_DLL_LOAD( VGSOUND_DLL_NAME );

	//vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

	//HWND hWnd = this->GetSafeHwnd();

	//if (plugin != NULL)
	//{
	//	VGK_DLL_DECLARE_CLASSFUNC( plugin, SoundManager, initialise, pfn1 );

	//	assert( pfn1 != NULL );

	//	(*pfn1)( hWnd );
	//}

	// TODO: 在此添加命令处理程序代码
}

void CMainFrame::OnSoundUnloadDll()
{
	//VGK_DLL_UNLOAD( VGSOUND_DLL_NAME );
	// TODO: 在此添加命令处理程序代码
}

void CMainFrame::OnSolarLoadDll()
{
	VGK_DLL_LOAD( VGSO_DLL_NAME );
}

void CMainFrame::OnSolarUnloadDll()
{
	VGK_DLL_UNLOAD( VGSO_DLL_NAME );
}

void CMainFrame::OnLoadLogoDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_LOAD( VGL_DLL_NAME );
}

void CMainFrame::OnUnloadLogoDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_UNLOAD( VGL_DLL_NAME );
}

void CMainFrame::OnLoadFontDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_LOAD( VGF_DLL_NAME );

}

void CMainFrame::OnUnloadFontDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_UNLOAD( VGF_DLL_NAME );

}

void CMainFrame::OnLoadDbDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_LOAD( VGD_DLL_NAME );
}

void CMainFrame::OnUnloadDbDll()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_UNLOAD( VGD_DLL_NAME );
}

void CMainFrame::OnScriptLoad()
{
	//------------------------------------------
	// 设定用户script
	//------------------------------------------

	


	//vgScript::ScriptManager::getSingleton().addUserScriptFunc( 
	//	vgUser::exportSystemModule );

	//vgScript::ScriptManager::getSingleton().addUserScriptFunc( 
	//	vgUser::exportOtherModules );

	VGK_DLL_LOAD( VGSC_DLL_NAME );
	VGK_DLL_LOAD( "vgMenuScriptEMeiDLL_Debug.dll" );


	//vgScript::ScriptManager::getSingleton().initAfterOpenGLSetup();

	//std::ostringstream o;

	//o << "\n"
	//	<< "import vgCam"		<< "\n"
	//	<< "import vgSystem"		<< "\n"
	//	<< "import vgKernel"		<< "\n"
	//	<< "import vgVector"		<< "\n"
	//	<< "import vgTerritory"		<< "\n"
	//	<< "import vgVisualEffects"		<< "\n"
	//	<< "import vgScript"		<< "\n"
	//	<< "import vgSprite"		<< "\n"
	//	<< "import vgConf"		<< "\n"
	//	<< "import vgMusic"		<< "\n"
	//	<< "import vgAsyn"		<< "\n"
	//	;

	//vgScript::ScriptManager::getSingleton().runScriptString( o.str() );
}

void CMainFrame::OnScriptUnload()
{
	VGK_DLL_UNLOAD( VGSC_DLL_NAME );
	VGK_DLL_LOAD( "vgMenuScriptEMeiDLL_Debug.dll" );

}

void CMainFrame::OnPlandllLoad()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_LOAD( VGP_DLL_NAME);
	VGK_DLL_LOAD( "vgMenuPlanEMeiDLL_Debug.dll" );

}

void CMainFrame::OnPlandllUnload()
{
	// TODO: 在此添加命令处理程序代码
	VGK_DLL_UNLOAD( VGP_DLL_NAME );
	VGK_DLL_UNLOAD( "vgMenuPlanEMeiDLL_Debug.dll" );

}


void CMainFrame::ActivateFrame(int nCmdShow)
{
	// TODO: 在此添加专用代码和/或调用基类

	nCmdShow = SW_HIDE;
	__super::ActivateFrame(nCmdShow);
}



void CMainFrame::loadPlugin( const String& plugin_name )
{
	VGK_TRACE("begin to load dll menu " + plugin_name);

	vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef(plugin_name);

	if (plugin == NULL)
	{
		VGK_TRACE("plugin == NULL");
		return ;
	}

	HMODULE hModule = plugin->getPluginHandle();

	CBCGPMenuBar* menubar = &this->m_wndMenuBar;

	// 挂接到主菜单
 	if (::InstallExtMenu(hModule, this->GetSafeHwnd(), menubar, plugin->getCmdWndId(), &s_lastMenu) == FALSE)
	{
		//VGK_SHOW( plugin_name + "  menu load Failed or no menu.\n");
	}
	else
	{
		VGK_SHOW( plugin_name + "  menu load ok.\n");
	}

	// 挂接到右键菜单	
	//loadRightMenuPlugin(plugin_name, *RightMenu);

}

void CMainFrame::unloadPlugin( const String& plugin_name )
{
	vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef(plugin_name);

	if (plugin == NULL)
	{
		return ;
	}

	if ( ! ::RemoveExtMenu(plugin->getPluginHandle()) )
	{
		//VGK_SHOW( plugin_name + "  menu unload failed or no menu.\n");
	}
	else
	{
		VGK_SHOW( plugin_name + "  menu unload ok.\n");
	}

}

//add by kinghj 2009.12.3 动态加载右键菜单
void CMainFrame::loadRightMenuPlugin(const String& plugin_name, CMenu& RightMenu)
{
	VGK_TRACE ("begin to load right menu" + plugin_name )	

	vgKernel::Plugin  *plugin = vgKernel::PluginManager::getSingleton().getPluginRef(plugin_name);
	if (plugin == NULL)
	{
		VGK_TRACE (" plugin == null");
	}

	HMODULE hModule = plugin->getPluginHandle();

	if (::InstallRightExtMenu(hModule, this->GetSafeHwnd(), &RightMenu, plugin->getCmdWndId(), &s_lastMenu) == FALSE)
	{
	}
	else
	{		
		VGK_SHOW( plugin_name + "  menu load ok.\n");
	}
	
	//return RightMenu;
}

void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
#if 0
	RightMenu = menu.GetSubMenu(0);

 	vgKernel::PluginLoaderPointerVec *_loaders = vgKernel::PluginManager::getSingleton().getPluginLoaderRef();
 	PluginLoaderPointerVec::iterator iter1 = _loaders->begin();
 	PluginLoaderPointerVec::iterator iter_end1 = _loaders->end();
 
 	vgKernel::PluginPointerVec* _plugins = vgKernel::PluginManager::getSingleton().getPluginVecRef();
 	PluginPointerVec::iterator iter = _plugins->begin();
 	PluginPointerVec::iterator iter_end = _plugins->end();
 
 	for (; iter1 != iter_end1 ; ++ iter1)
 	{
 		for (; iter != iter_end ; ++ iter)
 		{
 			 (*iter1)->loadRightMenuPlugin( (*iter)->getName(), *RightMenu);
 		}
 					
 	}

	ASSERT_VALID(RightMenu);

	if (vgKernel::InputSystem::getSingleton().CheckStatusValid(VG_INPUTMODE_SELECT))
	{
		RightMenu->EnableMenuItem (ID_STOPDEMOCREATE, 
			vgMod::NodeManager::getSingleton().getStatus() ? MF_ENABLED : MF_GRAYED);

		RightMenu->TrackPopupMenu(
			TPM_LEFTALIGN | TPM_RIGHTBUTTON , 
			point.x, point.y, this);

	}

#endif

	__super::OnContextMenu(pWnd, point);
}

void CMainFrame::OnStopdemocreate()
{
	// TODO: 在此添加命令处理程序代码
	vgMod::NodeManager::getSingleton().stopDemoCreate();
}

void CMainFrame::OnRotoview()
{
	// TODO: 在此添加命令处理程序代码
 	vgCam::CamManager::getSingleton().setMouseMode(
 		! vgCam::CamManager::getSingleton().getMouseMode());
}

void CMainFrame::OnOnOffFullscreen()
{
	// TODO: 在此添加命令处理程序代码
	CvgFrameWorkApp *pApp = (CvgFrameWorkApp *)AfxGetApp();
	CMainFrame * pMainFram = NULL;
	pMainFram = (CMainFrame *)pApp->GetMainWnd();
	pMainFram->vg_ShowFullScreen(0, 0, 2, 2);
	//MessageBox ("是否全屏", "菜单消息传递");
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	UINT uiToolBarId = (UINT) wp;

	switch (uiToolBarId)
	{
	case IDR_TOOLBAR1_EDIT:
		{
			ASSERT (m_wndToolBarSRShape.GetSafeHwnd () != NULL);
			ASSERT (m_wndToolBarSRMode.GetSafeHwnd () != NULL);
			ASSERT (m_wndToolBarSMInclude.GetSafeHwnd() != NULL );

			//-----------------------------------
			// Replace dropdown resources button:
			//-----------------------------------
			m_wndToolBar2_edit.ReplaceButton (ID_DUMMY_SR_SHPAE,
				CBCGPDropDownToolbarButton (_T("SRShape"), &m_wndToolBarSRShape));

			m_wndToolBar2_edit.ReplaceButton( ID_DUMMY_SR_MODE,
				CBCGPDropDownToolbarButton (_T("SRMode"), &m_wndToolBarSRMode));

			m_wndToolBar2_edit.ReplaceButton( ID_DUMMY_SM_INCLUDE,
				CBCGPDropDownToolbarButton (_T("SRInclude"), &m_wndToolBarSMInclude));
			
		}
		break;

	default:
		break;
	}

	return 0;
}
