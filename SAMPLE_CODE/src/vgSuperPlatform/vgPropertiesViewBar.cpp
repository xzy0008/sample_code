// PropertiesViewBar.cpp: implementation of the CPropertiesViewBar class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>
//#include "VgFrame.h"
#include "MainFrm.h"
#include "vgPropertiesViewBar.h"
#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar


vgPropertiesViewBar::vgPropertiesViewBar(): m_tabCnt(0)
{
}

vgPropertiesViewBar::~vgPropertiesViewBar()
{
	//::MessageBox(NULL, "Destory View Bar Message", "Info", MB_OK);
}


BEGIN_MESSAGE_MAP(vgPropertiesViewBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CPropertiesViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void vgPropertiesViewBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);
	m_wndTab.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	
}

CBCGPTabWnd* vgPropertiesViewBar::GetTabControl()
{
	return &m_wndTab;
}
void vgPropertiesViewBar::AddTab(string name, CWnd *wnd)
{
	m_wndTab.AddTab(wnd, name.c_str(), m_tabCnt++, FALSE);

	//zsc ÉèÖÃ½¹µã
	((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveView()->SetFocus();
}

void vgPropertiesViewBar::RemoveAllTab()
{
	m_wndTab.RemoveAllTabs();
	m_tabCnt = 0;
}
int vgPropertiesViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	m_wndTab.SetImageList (NIDB_TABICON, 16, RGB (255, 0, 255));

	AdjustLayout ();

	return 0;
}

void vgPropertiesViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();
}
