#include <vgStableHeaders.h>
#include <vgPropBar.h>


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar


 vgPropBar::vgPropBar()
 {
 }
 
 vgPropBar::~vgPropBar()
 {
 	//::MessageBox(NULL, "Destory View Bar Message", "Info", MB_OK);
 }


  BEGIN_MESSAGE_MAP(vgPropBar, CBCGPDockingControlBar)
  	//{{AFX_MSG_MAP(CPropertiesViewBar)
  	ON_WM_CREATE()
  	ON_WM_SIZE()
  	//}}AFX_MSG_MAP
  END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

  void vgPropBar::AdjustLayout ()
  {
  	if (GetSafeHwnd () == NULL)
  	{
  		return;
  	}
  
   	CRect rectClient;
   	GetClientRect (rectClient);
   	m_wndTab.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
   	
  }


  int vgPropBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
  {
  	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
  		return -1;
  	
  	CRect rectDummy;
  	rectDummy.SetRectEmpty ();
  
  	// Create combo:
  	/*const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
  		| WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
  	*/
  	CRect rectTab;
  
  	ScreenToClient (&rectTab);
  
  	m_wndTab.Create (CBCGPTabWnd::STYLE_3D, rectTab, this, 1,
  		CBCGPTabWnd::LOCATION_TOP);
  	m_wndTab.EnableAutoColor (TRUE);
  	// m_wndTab.SetImageList (NIDB_TABICON, 16, RGB (255, 0, 255));
  
  	AdjustLayout ();
  
  	return 0;
  }
 
  void vgPropBar::OnSize(UINT nType, int cx, int cy) 
  {
  	CBCGPDockingControlBar::OnSize(nType, cx, cy);
  	AdjustLayout ();
  }

	CBCGPTabWnd* vgPropBar::GetTabControl()
	{
		return &m_wndTab;
	}

	void vgPropBar::AddTab(string name, CWnd *wnd)
	{
		m_wndTab.AddTab(wnd, name.c_str(), m_tabCnt++, FALSE);

		//zsc ÉèÖÃ½¹µã
		((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveView()->SetFocus();
	}

	void vgPropBar::RemoveAllTab()
	{
		m_wndTab.RemoveAllTabs();
		m_tabCnt = 0;
	}
