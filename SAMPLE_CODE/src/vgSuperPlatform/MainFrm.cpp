// MainFrm.cpp : implementation of the CMainFrame class
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "MainFrm.h"
#include "vgTestNode1.h"
#include "vgRootEntry.h"
#include "vgPropertyPage.h"
#include "vgCamMgrEntry.h"

#include <vgRoot.h>
#include <vgMesh/vgmMeshManager.h>

#include "resource.h"

#include <vgDlgTestMultisample.h>

#include "vgUIController.h"
#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdProfileManager.h>
#include <vgScript/vgscScriptManager.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(NID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND_RANGE(NID_VIEW_APPLOOK_2000, NID_VIEW_APPLOOK_VS2008, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(NID_VIEW_APPLOOK_2000, NID_VIEW_APPLOOK_VS2008, OnUpdateAppLook)

	ON_COMMAND(NID_VIEW_HELLO, &CMainFrame::OnTestUpdate)

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
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{


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

	lstBasicCommands.AddTail (NID_VIEW_TOOLBARS);
	lstBasicCommands.AddTail (ID_FILE_NEW);
	lstBasicCommands.AddTail (ID_FILE_OPEN);
	lstBasicCommands.AddTail (ID_FILE_SAVE);
	lstBasicCommands.AddTail (ID_FILE_PRINT);
	lstBasicCommands.AddTail (ID_APP_EXIT);
	lstBasicCommands.AddTail (ID_EDIT_CUT);
	lstBasicCommands.AddTail (ID_EDIT_PASTE);
	lstBasicCommands.AddTail (ID_EDIT_UNDO);
	lstBasicCommands.AddTail (ID_RECORD_NEXT);
	lstBasicCommands.AddTail (ID_RECORD_LAST);
	lstBasicCommands.AddTail (ID_APP_ABOUT);
	lstBasicCommands.AddTail (ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail (NID_VIEW_CUSTOMIZE);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_2000);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_XP);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_2003);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_2007);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_VS2005);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_WIN_XP);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_2007_1);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_2007_2);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_2007_3);
	lstBasicCommands.AddTail (NID_VIEW_APPLOOK_VS2008);
	lstBasicCommands.AddTail (NID_VIEW_FULLSCREEN);
	lstBasicCommands.AddTail(ID_SCENE_READ);
	lstBasicCommands.AddTail(ID_SCENE_RESET);
	lstBasicCommands.AddTail(ID_SCENE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_EXPORT);
	lstBasicCommands.AddTail(ID_FILE_IMPORT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(NID_VIEW_FULLSCREEN);
	lstBasicCommands.AddTail(NID_VIEW_OUTPUT);
	lstBasicCommands.AddTail(NID_VIEW_WORKSPACE);
	lstBasicCommands.AddTail(ID_MESH_OR_LINE);
	lstBasicCommands.AddTail(ID_REDO);
	lstBasicCommands.AddTail(ID_UNDO);
	lstBasicCommands.AddTail(IDM_Zuobiao);
	lstBasicCommands.AddTail(IDM_Juli);
	lstBasicCommands.AddTail(IDM_Mianji);
	lstBasicCommands.AddTail(IDM_GISMATCH);
	lstBasicCommands.AddTail(ID_CREATCAM);
	lstBasicCommands.AddTail(ID_SWITCHCAM);
	lstBasicCommands.AddTail(ID_POSITIONTOOBJ);
	lstBasicCommands.AddTail(ID_EXP_BMP);
	lstBasicCommands.AddTail(ID_EXP_AVI);
	lstBasicCommands.AddTail(ID_COLLISION_ONOFF);
	lstBasicCommands.AddTail(NID_FILE_IMPORT_KFM);
	lstBasicCommands.AddTail(ID_ADDANIMATION);
	lstBasicCommands.AddTail(ID_ANI_Start);
	lstBasicCommands.AddTail(ID_ANI_END);
	lstBasicCommands.AddTail(ID_FILE_IMPORT_MS3D);
	lstBasicCommands.AddTail(ID_VECTOR_SHP_SLOT_RATIO);
	lstBasicCommands.AddTail(ID_VGTERRAIN_NEW_VTR);
	lstBasicCommands.AddTail(ID_VGT_BLEND);
	lstBasicCommands.AddTail(ID_32971);
	lstBasicCommands.AddTail(ID_32972);
	lstBasicCommands.AddTail(ID_32973);
	lstBasicCommands.AddTail(ID_32974);
	lstBasicCommands.AddTail(ID_VGT_CUT_ANALYSIS2);
	lstBasicCommands.AddTail(ID_TERRAIN_LEVELING);
	lstBasicCommands.AddTail(ID_VGT_ATTACH);
	lstBasicCommands.AddTail(ID_VGT_MAPPING_ORIGIN);
	lstBasicCommands.AddTail(ID_33109);
	lstBasicCommands.AddTail(ID_VGT_TERRAIN_SAVE);
	lstBasicCommands.AddTail(ID_SE_FOUNTAIN);
	lstBasicCommands.AddTail(ID_FIRE_ADD);
	lstBasicCommands.AddTail(ID_SE_SMOKE);
	lstBasicCommands.AddTail(ID_RAIN);
	lstBasicCommands.AddTail(ID_RAIN_DEL);
	lstBasicCommands.AddTail(ID_WATER_CONVERT);
	lstBasicCommands.AddTail(ID_GLASS_CONVERT);
	lstBasicCommands.AddTail(ID_CONVERT_BRIGTHFLOOR);
	lstBasicCommands.AddTail(ID_AVI_NODE_CONVERT);
	lstBasicCommands.AddTail(ID_SKYBOX_CONVERT);
	lstBasicCommands.AddTail(ID_SETTREE);
	lstBasicCommands.AddTail(ID_BEGINPLANT);
	lstBasicCommands.AddTail(ID_PLANTINLINE);
	lstBasicCommands.AddTail(ID_OptPlant);
	lstBasicCommands.AddTail(ID_3DSOUND_ADD);
	lstBasicCommands.AddTail(ID_BACKSOUND_SET);
	lstBasicCommands.AddTail(ID_AUTOBUILD);
	lstBasicCommands.AddTail(ID_AUTOBUILD_CLONE);
	lstBasicCommands.AddTail(ID_TRIGGER_SET_AS);
	lstBasicCommands.AddTail(ID_TRIGGER_CONFIG);
	lstBasicCommands.AddTail(ID_SCRIPT_RUNFILE);
	lstBasicCommands.AddTail(ID_SCRIPT_CONSOLE);
	lstBasicCommands.AddTail(ID_VGSC_USER_SCRIPT_CONFIG);
	lstBasicCommands.AddTail(NID_VIEW_PROPERTIES);

	lstBasicCommands.AddTail(ID_EDIT_CLEAR_ALL);
	lstBasicCommands.AddTail(ID_EDIT_TRANALL);
	lstBasicCommands.AddTail(ID_EDIT_SINGLE_FACE_RENDER_SEL);
	lstBasicCommands.AddTail(ID_TEST_MOD_OPACITY);
	lstBasicCommands.AddTail(ID_TEST_MOD_OPACITY_ALL);
	lstBasicCommands.AddTail(NID_VIEW_PROPERTIES);
	lstBasicCommands.AddTail(ID_EDIT_SINGLE_FACE_RENDER_ALL);
	lstBasicCommands.AddTail(ID_TANSLATE_SELECTED);

	lstBasicCommands.AddTail(ID_VGSHAPE_READSHPFILE);
	lstBasicCommands.AddTail(ID_VGSHAPE_READGRIDSHPFILE);
	lstBasicCommands.AddTail(ID_VGSHAPE_SELECTSHPAREA);
	lstBasicCommands.AddTail(ID_VGSHAPE_SAVEASSHAPE);
	lstBasicCommands.AddTail(ID_VGSHAPE_TRANSLATETOORIGIN);
	lstBasicCommands.AddTail(ID_VGSHAPE_ATTACHTOTERRAIN);
	lstBasicCommands.AddTail(ID_TRIGGER_CONFIG);
	
	lstBasicCommands.AddTail(ID_VGPLAN_ADDNEW);
	lstBasicCommands.AddTail(ID_VGPLAN_CGRID);
	lstBasicCommands.AddTail(ID_VGPLAN_GENPLAN);
	lstBasicCommands.AddTail(ID_VGPLAN_OUTPUT);
	lstBasicCommands.AddTail(ID_VGSHAPE_QUERY_GREEN_RATIO);
	lstBasicCommands.AddTail(ID_QUERYPLANINFO_QUERYPLOTRATIO);


	for (int i=0; i<CDynamicItems::GetNbMaxItems(); i++)
	{
		lstBasicCommands.AddTail(ID_POPUP_DynCmd01 + i);
	}

	CBCGPToolBar::SetBasicCommands (lstBasicCommands);



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
	CBCGPStatusBar *pStatusBar = vgUIController::GetInstance()->GetStatusBar();

	if (!pStatusBar->Create(this) ||
		!pStatusBar->SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	pStatusBar->SetPaneStyle (vgUIController::nStatusInfo, SBPS_STRETCH | SBPS_NOBORDERS);
	

#if VGK_LANG_CHS
	// 遮挡剔除信息栏
	pStatusBar->SetPaneWidth(vgUIController::nStatusOcc, 80);
	pStatusBar->SetPaneText(vgUIController::nStatusOcc, "遮挡剔除");

	// 帧速信息栏
	pStatusBar->SetPaneWidth (vgUIController::nStatusFrame, 50);
	pStatusBar->SetPaneText(vgUIController::nStatusFrame, "帧速");
#else
	// 遮挡剔除信息栏
	pStatusBar->SetPaneWidth(vgUIController::nStatusOcc, 80);
	pStatusBar->SetPaneText(vgUIController::nStatusOcc, "Occ");

	// 帧速信息栏
	pStatusBar->SetPaneWidth (vgUIController::nStatusFrame, 50);
	pStatusBar->SetPaneText(vgUIController::nStatusFrame, "Frame");
#endif


	// 设置进度条
	pStatusBar->SetPaneWidth (vgUIController::nStatusProgress, 80);
	pStatusBar->EnablePaneProgressBar (vgUIController::nStatusProgress, -1);
	pStatusBar->SetPaneText(vgUIController::nStatusProgress, "");

	// ===========================================================================

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (NIDB_WORKSPACE);
	
	vgWorkSpaceBar* workspace = vgUIController::GetInstance()->GetWorkSpaceBar();

#if VGK_LANG_CHS
	if (!workspace->Create (_T("节点视图"),this, CRect (0, 0, 200, 200),
		TRUE,
		NID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}
#else
	if (!workspace->Create (_T("Scene graph"),this, CRect (0, 0, 200, 200),
		TRUE,
		NID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}
#endif

	workspace->SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);


#if VGK_LANG_CHS
	if (!vgUIController::GetInstance()->GetOutputBar()->Create (_T("提示信息"), this, CSize (150, 150),
		TRUE /* Has gripper */, NID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}
#else
	if (!vgUIController::GetInstance()->GetOutputBar()->Create (_T("Tips"), this, CSize (150, 150),
		TRUE /* Has gripper */, NID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
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


	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
	//pageViewBar->m_bDisableAnimation = true;
	
	// Create propertise view added by zsc
	// 创建 PropertiesBar
#if VGK_LANG_CHS
	if (!pageViewBar->Create (_T("属性栏"), this, CRect (0, 0, 300, 200),
		TRUE, 
		NID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}
#else
	if (!pageViewBar->Create (_T("Properties"), this, CRect (0, 0, 300, 200),
		TRUE, 
		NID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}
#endif

	// 设置属性页图标 在DOCK时显示
	HICON hPropertiesBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
		MAKEINTRESOURCE (NIDR_MAINFRAME),
		IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	pageViewBar->SetIcon (hPropertiesBarIcon, FALSE);



	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2_edit.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar3_camera.EnableDocking(CBRS_ALIGN_ANY);

	workspace->EnableDocking(CBRS_ALIGN_ANY);

	// m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	vgUIController::GetInstance()->GetOutputBar()->EnableDocking(CBRS_ALIGN_ANY);
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


	DockControlBar(workspace);
	// m_wndWorkSpace2.AttachToTabWnd(workspace, BCGP_DM_STANDARD, FALSE, NULL);
	// 开启Dock
	pageViewBar->EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(pageViewBar);
	DockControlBar(vgUIController::GetInstance()->GetOutputBar());


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
	


	//////////////////////////////////////////////////////////////////////////

	//HMENU hmenu = m_wndMenuBar.GetHMenu();
	//CMenu* cmenu = CMenu::FromHandle( hmenu );

	//SetMenu( cmenu );

	//////////////////////////////////////////////////////////////////////////
	//if ( m_dynamic_menu.readFromFile( "d:\\TestFile.dat" ))
	//{
	//	m_dynamic_menu.add( 0 );

	//	m_wndMenuBar.CreateFromMenu( hmenu );

	//}
	//else
	//{
	//	assert(0);
	//}



	return 0;
}

void CMainFrame::OnDestroy()
{
	CBCGPFrameWnd::OnDestroy();

	//CPropertiesViewBar::DestoryInstance();
	//vgUIController::DestoryInstance();
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

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	// UINT uiToolBarId = (UINT) wp;
	// if (uiToolBarId == NIDR_MAINFRAME)
	// {
	//		do something with m_wndToolBar
	// }

	return 0;
}

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
	
	vgUIController::GetInstance()->SetFrameSpeed(50);

	// vgTestNode1 node("World"); // 导致无效的引用
	// 不必担心内存泄露，UIController会负责释放内存

	char exebuf[512];
	DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

	assert( getret < 512 );
	assert( getret > 0 );

	String exestr( exebuf );
	String exepath = exestr.substr( 0 , 
		exestr.find_last_of("\\/")  + 1);

	string profilePath = exepath + "profile.xml";

	vgDatabase::ProfileManager::getSingleton().LoadFromFile(profilePath);
	// AfxMessageBox(vgDatabase::ProfileManager::getSingleton().CreateQuery("建筑属性2").c_str());

	vgUIController::GetInstance()->InitUIControl();
///////////////////////////////////////////////////////////////////
// 	vgBaseEntry *node = new vgRootEntry();
// 	HTREEITEM root = vgUIController::GetInstance()->AddNode(node);
// 
// 
// 	//就只有这一个!
// 	node = new vgCamMgrEntry();
// 	vgUIController::GetInstance()->AddNode(node);
///////////////////////////////////////////////////////////////////
	/*vgUIController::GetInstance()->AddNode(root, node);

	node = new vgRootEntry();
	vgUIController::GetInstance()->AddNode(root, node);*/

// 	node = new vgTestNode1("TestNodo1");
// 	vgUIController::GetInstance()->AddNode(root, node);
// 
// 	node = new vgTestNode1("TestNode2");
// 	vgUIController::GetInstance()->AddNode(root, node);
	
	//node = new vgObjectNode("Line1");
	//vgUIController::GetInstance()->AddNode(root, node);

	//node = new vgObjectNode("Box1");
	//vgUIController::GetInstance()->AddNode(root, node);

	//node = new vgObjectNode("Box2");
	//vgUIController::GetInstance()->AddNode(root, node);
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
// 		itemArray[i] = vgUIController::GetInstance()->AddNode(root, node);
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
// 		vgUIController::GetInstance()->AddNode(itemArray[j], node);
// 
// 	}


	return true;
}

void CMainFrame::OnTestUpdate()
{
	assert(0);

#if 0
	//TRACE("SIZE : %d \n", sizeof(vgObjectNode));

	//TRACE("触发Update \n");
	vgTestNode1* node = dynamic_cast<vgTestNode1*> (vgUIController::GetInstance()->GetNode("TestNodo1"));

	if (node != NULL)
	{
		//TRACE("获得node成功 \n");
		vgUIController::GetInstance()->SelectNode(node);
	
		if (vgUIController::GetInstance()->GetCurrentSelectedNode() == node)
			//TRACE("确认选择 \n");
	}

	float val = 0.f;

	for (int i=0; i<10; i++)
	{
		//TRACE("更新数据 \n");
		node->SetPosX(val);
		node->SetPosY(val+1);
		
		node->SetCaption("新的标题");
		node->SetEnable(TRUE);

		node->SetSize(22);
		val += 10.f;
		Sleep(100);
	}

#endif
}

void CMainFrame::OnFullScreen()
{
	//TRACE("FullScreen \n");

	ShowFullScreen();

	return ;

	RECT rectDesktop;
	WINDOWPLACEMENT wpNew;

	if (!IsFullScreen())
	{
		// need to hide all status bars
		// m_wndStatusBar.ShowWindow(SW_HIDE);
		// m_wndToolBar.ShowWindow(SW_HIDE);

		vgUIController::GetInstance()->GetOutputBar()->Slide(TRUE);

		//m_wndStatusBar.ShowControlBar(FALSE, FALSE, TRUE);
		vgUIController::GetInstance()->GetStatusBar()->ShowControlBar(FALSE, FALSE, TRUE);
		m_wndToolBar.ShowControlBar(FALSE, FALSE, TRUE);

		m_wndToolBar2_edit.ShowControlBar(FALSE, FALSE, TRUE);

		m_wndMenuBar.ShowControlBar(FALSE, FALSE, TRUE);
		vgUIController::GetInstance()->GetOutputBar()->ShowControlBar(FALSE, FALSE, TRUE);
		vgUIController::GetInstance()->GetPropertiesViewBar()->ShowControlBar(FALSE, TRUE, TRUE);
		vgUIController::GetInstance()->GetWorkSpaceBar()->ShowControlBar(FALSE, TRUE, TRUE);
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
		vgUIController::GetInstance()->GetStatusBar()->ShowControlBar(TRUE, TRUE, TRUE);
		m_wndToolBar.ShowControlBar(TRUE, TRUE, TRUE);

		m_wndToolBar2_edit.ShowControlBar(TRUE, TRUE, TRUE);


		vgUIController::GetInstance()->GetOutputBar()->ShowControlBar(TRUE, TRUE, TRUE);
//		m_wndWorkSpace2.ShowControlBar(TRUE, TRUE, TRUE);
		vgUIController::GetInstance()->GetPropertiesViewBar()->ShowControlBar(TRUE, TRUE, TRUE);
		vgUIController::GetInstance()->GetWorkSpaceBar()->ShowControlBar(TRUE, TRUE, TRUE);


		wpNew = m_wpPrev;
	}

	SetWindowPlacement ( &wpNew );
}

BOOL CMainFrame::IsFullScreen()
{
	return m_bFullScreen;
}

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
	vgUIController::GetInstance()->GetPropertiesViewBar()->ShowControlBar (
		!vgUIController::GetInstance()->GetPropertiesViewBar()->IsVisible() , FALSE, TRUE);
}


void CMainFrame::OnUpdateViewProperties(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( vgUIController::GetInstance()->GetPropertiesViewBar()->IsVisible() );
}

void CMainFrame::OnViewWorkspace()
{
	vgUIController::GetInstance()->GetWorkSpaceBar()->ShowControlBar (
		!vgUIController::GetInstance()->GetWorkSpaceBar()->IsVisible() , FALSE, TRUE);
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( vgUIController::GetInstance()->GetWorkSpaceBar()->IsVisible() );
}

void CMainFrame::OnViewOutput()
{
	vgUIController::GetInstance()->GetOutputBar()->ShowControlBar (
		!vgUIController::GetInstance()->GetOutputBar()->IsVisible() , FALSE, TRUE);
}

void CMainFrame::OnUpdateViewOutput(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck ( vgUIController::GetInstance()->GetOutputBar()->IsVisible() );
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