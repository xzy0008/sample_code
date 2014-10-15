// workspace.cpp : implementation of the CWorkSpaceBar class
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "vgWorkSpaceBar.h"
#include "vgBasedTabPage.h"
#include "vgUIController.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using std::string;

const int nBorderSize = 1;
/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(vgWorkSpaceBar, CBCGPDockingControlBar)
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
	//ON_NOTIFY(TVN_SELCHANGED, IDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnTvnSelchangedTree1)

	ON_MESSAGE(VG_MSG_TREEDRAG, &vgWorkSpaceBar::OnTreeDrag)
	//ON_NOTIFY(TVN_BEGINDRAG, IDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnTvnBegindragTree1)
	//ON_NOTIFY(NM_RCLICK, IDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnNMRclickTree1)
END_MESSAGE_MAP()


LRESULT vgWorkSpaceBar::OnTreeDrag(WPARAM h1,LPARAM h2)
{
	string sItemName((char*)h1);
	string dItemName((char*)h2);
	
	TRACE("%s drag to %s", sItemName.c_str(), dItemName.c_str());

	delete[] (char*)h1;
	delete[] (char*)h2;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

vgWorkSpaceBar::vgWorkSpaceBar()
	:m_uiRootNodeCount(0)
{
	// TODO: add one-time construction code here
	//	m_bDragging = false;//开始不是处在拖拽状态
}

vgWorkSpaceBar::~vgWorkSpaceBar()
{
	//int size = m_nodeList.size();
	
	for (int i=0; i<m_uiRootNodeCount; i++)
	{
		if (m_nodeList[i] != NULL)
			delete m_nodeList[i];
	}
	
}

HTREEITEM vgWorkSpaceBar::AddNode(vgBasedNode* node)
{
	node->hTreeItem =  m_wndTree.InsertItem(node->GetNameID().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage());
	m_nodeList.push_back(node);
	
	m_wndTree.SetItemData(node->hTreeItem, (DWORD_PTR)node);

	return node->hTreeItem;
	//return m_wndTree.AddNode(node);
}

HTREEITEM vgWorkSpaceBar::AddNode(HTREEITEM parent, vgBasedNode* node)
{
	node->hTreeItem = m_wndTree.InsertItem(node->GetNameID().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage(), parent);
	m_nodeList.push_back(node);

	m_wndTree.SetItemData(node->hTreeItem, (DWORD_PTR)node);

	return node->hTreeItem;
	//return m_wndTree.AddNode(parent, node);
}

HTREEITEM vgWorkSpaceBar::AddNode(vgBasedNode* parentNode, vgBasedNode* node)
{
	node->hTreeItem = m_wndTree.InsertItem(node->GetNameID().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage(), parentNode->hTreeItem);
	m_nodeList.push_back(node);

	m_wndTree.SetItemData(node->hTreeItem, (DWORD_PTR)node);

	return node->hTreeItem;
	// return m_wndTree.AddNode(parentNode, node);
}
/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int vgWorkSpaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	CRect rectTab;
	ScreenToClient (&rectTab);

	m_wndTab.Create (CBCGPTabWnd::STYLE_3D, rectTab, this, 1,
		CBCGPTabWnd::LOCATION_TOP);

	m_wndTab.SetImageList (IDB_WORKSPACE, 16, RGB (255, 0, 255));

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
	

	if (!m_wndTree.Create (dwViewStyle, rectDummy, &m_wndTab, IDC_WORKSPACE_TREE1))
	{
		TRACE0("Failed to create workspace view\n");
		return -1;      // fail to create
	}
	if (!m_wndTree2.Create (dwViewStyle, rectDummy, &m_wndTab, IDC_WORKSPACE_TREE1))
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
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_ICON1);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_ICON3);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_ICON2);

	for (int i=0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}
	
	m_wndTree.SetImageList(&m_imageList, TVSIL_NORMAL);
	m_wndTree2.SetImageList(&m_imageList, TVSIL_NORMAL);
	
	m_wndTab.AddTab(&m_wndTree, "树视图1", 0, FALSE);
	m_wndTab.AddTab(&m_wndTree2, "树视图2", 0, FALSE);
	return 0;
}

void vgWorkSpaceBar::OnSize(UINT nType, int cx, int cy) 
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

void vgWorkSpaceBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTree;
	m_wndTree.GetWindowRect (rectTree);
	ScreenToClient (rectTree);

	rectTree.InflateRect (nBorderSize, nBorderSize);
	dc.Draw3dRect (rectTree,	::GetSysColor (COLOR_3DSHADOW), 
								::GetSysColor (COLOR_3DSHADOW));
}

// 使用一个 OnContextMenu 屏蔽右键菜单
void vgWorkSpaceBar::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	// 注释此行可屏蔽原有的右键菜单 
	//__super::OnContextMenu(pWnd, point);
}

vgBasedNode* vgWorkSpaceBar::GetNode(string nameId)
{
	int size = m_nodeList.size();

	for (int i=0; i<size; i++)
	{
		if (m_nodeList[i] != NULL && m_nodeList[i]->GetNameID() == nameId)
			return m_nodeList[i];
	}

	return NULL;
}