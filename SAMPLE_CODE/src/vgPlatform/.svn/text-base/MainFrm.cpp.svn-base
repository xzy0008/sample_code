// MainFrm.cpp : implementation of the CMainFrame class
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "MainFrm.h"
#include "vgTestNode1.h"
#include "vgRootNode.h"
#include "vgObjectNode.h"
#include "vgPropertyPage.h"
#include "vgCameraNode.h"

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
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnUpdateAppLook)

	ON_COMMAND(ID_VIEW_HELLO, &CMainFrame::OnTestUpdate)

	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_VIEW_FULLSCREEN, &CMainFrame::OnFullScreen)
	ON_COMMAND(ID_SFULLSCREEN, &CMainFrame::OnFullScreen)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()//:tab(new int(1))
{
	m_bFullScreen = false;
	// m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_VS2005);
	// TODO: add member initialization code here
	m_nAppLook = ID_VIEW_APPLOOK_2003;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	OnAppLook (m_nAppLook);

	// VISUAL_MANAGER
	
	if (CBCGPToolBar::GetUserImages () == NULL)
	{
		// Load toolbar user images:
		if (!m_UserImages.Load (_T(".\\UserImages.bmp")))
		{
			TRACE(_T("Failed to load user images\n"));
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

	lstBasicCommands.AddTail (ID_VIEW_TOOLBARS);
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
	lstBasicCommands.AddTail (ID_VIEW_CUSTOMIZE);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2000);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_XP);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2003);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS2005);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_WIN_XP);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_1);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_2);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_3);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS2008);
	lstBasicCommands.AddTail (ID_VIEW_HELLO);
	lstBasicCommands.AddTail (ID_VIEW_FULLSCREEN);

	CBCGPToolBar::SetBasicCommands (lstBasicCommands);

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	
	vgWorkSpaceBar* workspace = vgUIController::GetInstance()->GetWorkSpaceBar();

	if (!workspace->Create (_T("节点视图"),this, CRect (0, 0, 200, 200),
		TRUE,
		ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}
	//workspace->Create("", this, C)
	//workspace->Create
	//workspace->E
	TRACE("Can hide? %d \n", workspace->CanAutoHide());
;	workspace->SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	//if (!m_wndWorkSpace2.Create (_T("View 2"), this, CRect (0, 0, 200, 200),
	//	TRUE, ID_VIEW_WORKSPACE2,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	//{
	//	TRACE0("Failed to create Workspace bar 2\n");
	//	return -1;      // fail to create
	//}

	//m_wndWorkSpace2.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);


	if (!m_wndOutput.Create (_T("提示信息"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);


	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
	//pageViewBar->m_bDisableAnimation = true;
	
	// Create propertise view added by zsc
	// 创建 PropertiesBar
	if (!pageViewBar->Create (_T("属性栏"), this, CRect (0, 0, 300, 200),
		TRUE, 
		ID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI,CBRS_BCGP_REGULAR_TABS, ~CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}

	// 设置属性页图标 在DOCK时显示
	HICON hPropertiesBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
		MAKEINTRESOURCE (IDR_MAINFRAME),
		IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	pageViewBar->SetIcon (hPropertiesBarIcon, FALSE);



	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	workspace->EnableDocking(CBRS_ALIGN_ANY);

	// m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(workspace);
	// m_wndWorkSpace2.AttachToTabWnd(workspace, BCGP_DM_STANDARD, FALSE, NULL);
	// 开启Dock
	pageViewBar->EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(pageViewBar);
	DockControlBar(&m_wndOutput);


	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("订制..."));

	// Allow user-defined toolbars operations:
	InitUserToobars (NULL,
					uiFirstUserToolBarId,
					uiLastUserToolBarId);

	// Enable control bar context menu (list of bars + customize command):
	EnableControlBarMenu (	
		TRUE,				// Enable
		ID_VIEW_CUSTOMIZE, 	// Customize command ID
		_T("定制..."),	// Customize command text
		ID_VIEW_TOOLBARS);	// Menu items with this ID will be replaced by
							// toolbars menu

	vgKernel::InputSystem::getSingleton().initialise(AfxGetApp()->m_hInstance, AfxGetMainWnd()->GetSafeHwnd() );

	this->InitUIControl();
	return 0;
}

void CMainFrame::OnDestroy()
{
	CBCGPFrameWnd::OnDestroy();

	//CPropertiesViewBar::DestoryInstance();
	vgUIController::DestoryInstance();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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
	// if (uiToolBarId == IDR_MAINFRAME)
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
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	//case ID_VIEW_APPLOOK_2007:
	//case ID_VIEW_APPLOOK_2007_1:
	//case ID_VIEW_APPLOOK_2007_2:
	//case ID_VIEW_APPLOOK_2007_3:
	//	// enable Office 2007 look:
	//	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
	//	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
	//	break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2008:
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

	// vgTestNode1 node("World"); // 导致无效的引用
	// 不必担心内存泄露，UIController会负责释放内存

	vgBasedNode *node = new vgRootNode("VG-Scene");
	HTREEITEM root = vgUIController::GetInstance()->AddNode(node);


	node = new vgCameraNode("Camera1");
	vgUIController::GetInstance()->AddNode(root, node);

	node = new vgTestNode1("TestNodo1");
	vgUIController::GetInstance()->AddNode(root, node);

	node = new vgTestNode1("TestNode2");
	vgUIController::GetInstance()->AddNode(root, node);
	
	//node = new vgObjectNode("Line1");
	//vgUIController::GetInstance()->AddNode(root, node);

	//node = new vgObjectNode("Box1");
	//vgUIController::GetInstance()->AddNode(root, node);

	//node = new vgObjectNode("Box2");
	//vgUIController::GetInstance()->AddNode(root, node);
	//
// 	HTREEITEM itemArray[10];
// 
// 	CTreeCtrl *pTree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
// 
// 	CString strName;
// 
// 	for (int i=0; i<10; i++)
// 	{
// 		strName.Format(_T("Item Array %d"), i);
// 		node = new vgRootNode(strName.GetString());
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
// 			TRACE("=");
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
	TRACE("SIZE : %d \n", sizeof(vgObjectNode));

	TRACE("触发Update \n");
	vgTestNode1* node = dynamic_cast<vgTestNode1*> (vgUIController::GetInstance()->GetNode("TestNodo1"));

	if (node != NULL)
	{
		TRACE("获得node成功 \n");
		vgUIController::GetInstance()->SelectNode(node);
	
		if (vgUIController::GetInstance()->GetCurrentSelectedNode() == node)
			TRACE("确认选择 \n");
	}

	float val = 0.f;

	for (int i=0; i<10; i++)
	{
		TRACE("更新数据 \n");
		node->SetPosX(val);
		node->SetPosY(val+1);
		
		node->SetCaption("新的标题");
		node->SetEnable(TRUE);

		node->SetSize(22);
		val += 10.f;
		Sleep(100);
	}
}

void CMainFrame::OnFullScreen()
{
	TRACE("FullScreen \n");

	RECT rectDesktop;
	WINDOWPLACEMENT wpNew;

	if (!IsFullScreen())
	{
		// need to hide all status bars
		// m_wndStatusBar.ShowWindow(SW_HIDE);
		// m_wndToolBar.ShowWindow(SW_HIDE);

		m_wndOutput.Slide(TRUE);

		m_wndStatusBar.ShowControlBar(FALSE, FALSE, TRUE);
		m_wndToolBar.ShowControlBar(FALSE, FALSE, TRUE);
		m_wndMenuBar.ShowControlBar(FALSE, FALSE, TRUE);
		m_wndOutput.ShowControlBar(FALSE, FALSE, TRUE);
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
		// 修改IDB_TOOLBAR256更换图标
		if (!m_pwndFullScrnBar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
			!m_pwndFullScrnBar->LoadToolBar(IDR_FULLSCREEN, 0, 0, FALSE, 0, 0, IDB_TOOLBAR256))
		{
			TRACE0("Failed to create toolbar\n");
			return ;
		}

		//don't allow the toolbar to dock
		m_pwndFullScrnBar->EnableDocking(0);
		m_pwndFullScrnBar->SetWindowPos(0, 100,100, 0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);   
		m_pwndFullScrnBar->SetWindowText(_T("提示"));
		m_pwndFullScrnBar->SetToolBarBtnText(0, _T("关闭全屏"));
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
		m_wndStatusBar.ShowControlBar(TRUE, TRUE, TRUE);
		m_wndToolBar.ShowControlBar(TRUE, TRUE, TRUE);


		m_wndOutput.ShowControlBar(TRUE, TRUE, TRUE);
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

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if (IsFullScreen())
	{
		lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
		lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
	}

}