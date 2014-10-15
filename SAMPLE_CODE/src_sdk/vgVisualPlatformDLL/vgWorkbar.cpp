#include <vgStableHeaders.h>
#include <vgWorkbar.h>

 BEGIN_MESSAGE_MAP(vgWorkbar, CBCGPDockingControlBar)
 	//{{AFX_MSG_MAP(CWorkSpaceBar)
 	ON_WM_CREATE()
 	ON_WM_SIZE()
 	ON_WM_PAINT()
 	ON_WM_CONTEXTMENU()
 	//ON_WM_MOUSEMOVE()
 	//ON_WM_TIMER()
 	//ON_WM_LBUTTONUP()
 	//ON_WM_LBUTTONDOWN()
 	////}}AFX_MSG_MAP
 	//ON_NOTIFY(TVN_SELCHANGED, NIDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnTvnSelchangedTree1)
 
 	//ON_MESSAGE(VG_MSG_TREEDRAG, &vgWorkbar::OnTreeDrag)
 	//ON_NOTIFY(TVN_BEGINDRAG, NIDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnTvnBegindragTree1)
 	//ON_NOTIFY(NM_RCLICK, NIDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnNMRclickTree1)
 END_MESSAGE_MAP()

  int vgWorkbar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
  {
  	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
  		return -1;
  	
  	CRect rectDummy;
  	rectDummy.SetRectEmpty ();
  
  	CRect rectTab;
  	ScreenToClient (&rectTab);
  
  	m_wndTab.Create (CBCGPTabWnd::STYLE_3D, rectTab, this, 1,
  		CBCGPTabWnd::LOCATION_TOP);
  
  	m_wndTab.SetImageList (NIDB_WORKSPACE, 16, RGB (255, 0, 255));
  
  	m_wndTab.SetLocation(CBCGPTabWnd::LOCATION_BOTTOM);
  	CArray<COLORREF, COLORREF> arColors;
  
  	arColors.Add (RGB (210, 210, 255));
  	arColors.Add (RGB (190, 218, 153));
  	arColors.Add (RGB (255, 170, 100));
  
  	m_wndTab.SetAutoColors (arColors);
  	m_wndTab.EnableAutoColor (TRUE);
  	m_wndTab.RecalcLayout ();
  	m_wndTab.RedrawWindow ();
  
  	// Create tree windows.
  	// TODO: create your own tab windows here:
  	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
  								TVS_LINESATROOT | TVS_HASBUTTONS;// | TVS_SHOWSELALWAYS;
  	
  
  	if (!m_wndTree.Create (dwViewStyle, rectDummy, &m_wndTab, NIDC_WORKSPACE_TREE1))
  	{
  		TRACE0("Failed to create workspace view\n");
  		return -1;      // fail to create
  	}
  	if (!m_wndTree2.Create (dwViewStyle, rectDummy, &m_wndTab, NIDC_WORKSPACE_TREE1))
  	{
  		TRACE0("Failed to create workspace view\n");
  		return -1;      // fail to create
  	}
  
  
  	// Setup trees content:
  	/*HTREEITEM hRoot1 = m_wndTree.InsertItem (_T("Root 1"));
  	m_wndTree.InsertItem (_T("Item 1"), hRoot1);
  	m_wndTree.InsertItem (_T("Item 2"), hRoot1);*/
  
  	// 设置Tree Item图标
  	HICON hIcon[3];
  
  	m_imageList.Create(16, 16,ILC_COLOR32|ILC_MASK, 3, 3);
  	hIcon[0] = AfxGetApp()->LoadIcon(NIDI_ICON1);
  	hIcon[1] = AfxGetApp()->LoadIcon(NIDI_ICON3);
  	hIcon[2] = AfxGetApp()->LoadIcon(NIDI_ICON2);
  
  	for (int i=0; i<3; i++)
  	{
  		m_imageList.Add(hIcon[i]);
  	}
  	
  	m_wndTree.SetImageList(&m_imageList, TVSIL_NORMAL);
  	m_wndTree2.SetImageList(&m_imageList, TVSIL_NORMAL);
  	
  	//m_wndTab.AddTab(&m_wndTree, "树视图1", 0, FALSE);
  	//m_wndTab.AddTab(&m_wndTree2, "树视图2", 0, FALSE);
  #if VGK_LANG_CHS
  	m_wndTab.AddTab(&m_wndTree, "场景视图", 0, FALSE);
  	//m_wndTab.AddTab(&m_wndTree2, "矢量视图", 0, FALSE);
  #else
  	m_wndTab.AddTab(&m_wndTree, "Scene View", 0, FALSE);
  	//m_wndTab.AddTab(&m_wndTree2, "Vector View", 0, FALSE);
  #endif
  
  	return 0;
  }
  
  void vgWorkbar::OnSize(UINT nType, int cx, int cy) 
  {
  	CBCGPDockingControlBar::OnSize(nType, cx, cy);
  
  	// Tab control should cover a whole client area:
  	//m_wndTree.SetWindowPos (NULL, nBorderSize, nBorderSize, 
  	//	cx - 2 * nBorderSize, cy - 2 * nBorderSize,
  	//	SWP_NOACTIVATE | SWP_NOZORDER);
  
  	CRect rectClient;
  	GetClientRect (rectClient);
  	m_wndTab.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
  }
  
  void vgWorkbar::OnPaint() 
  {
  	CPaintDC dc(this); // device context for painting
  	
  	CRect rectTree;
  	m_wndTree.GetWindowRect (rectTree);
  	ScreenToClient (rectTree);
  
  	rectTree.InflateRect (-1, -1);
  	dc.Draw3dRect (rectTree,	::GetSysColor (COLOR_3DSHADOW), 
  								::GetSysColor (COLOR_3DSHADOW));
  }

  void vgWorkbar::OnContextMenu(CWnd* pWnd, CPoint pos)
  {
	  return ;
  }