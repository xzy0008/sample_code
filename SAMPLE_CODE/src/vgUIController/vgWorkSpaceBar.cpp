// workspace.cpp : implementation of the CWorkSpaceBar class
//

#include <vgStableHeaders.h>

#include <vgUIController/vgWorkSpaceBar.h>
#include <vgUIController/vgBasedTabPage.h> 
#include <vgUIController/vgUIController.h>

#include <vgEntry/vgRootEntry.h>
#include <string>

#include <vgMesh/vgmMeshItem.h>
#include <vgMesh/vgmMeshManager.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using std::string;

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

// BEGIN_MESSAGE_MAP(vgWorkSpaceBar, CBCGPDockingControlBar)
// 	//{{AFX_MSG_MAP(CWorkSpaceBar)
// 	ON_WM_CREATE()
// 	ON_WM_SIZE()
// 	ON_WM_PAINT()
// 	ON_WM_CONTEXTMENU()
// 	//ON_WM_MOUSEMOVE()
// 	//ON_WM_TIMER()
// 	//ON_WM_LBUTTONUP()
// 	//ON_WM_LBUTTONDOWN()
// 	////}}AFX_MSG_MAP
// 	//ON_NOTIFY(TVN_SELCHANGED, NIDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnTvnSelchangedTree1)
// 
// 	ON_MESSAGE(VG_MSG_TREEDRAG, &vgWorkSpaceBar::OnTreeDrag)
// 	//ON_NOTIFY(TVN_BEGINDRAG, NIDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnTvnBegindragTree1)
// 	//ON_NOTIFY(NM_RCLICK, NIDC_WORKSPACE_TREE1, &vgWorkSpaceBar::OnNMRclickTree1)
// END_MESSAGE_MAP()


// LRESULT vgWorkSpaceBar::OnTreeDrag(WPARAM h1,LPARAM h2)
// {
// 	string sItemName((char*)h1);
// 	string dItemName((char*)h2);
// 	
// 	TRACE("%s drag to %s", sItemName.c_str(), dItemName.c_str());
// 
// 	delete[] (char*)h1;
// 	delete[] (char*)h2;
// 	return 0;
// }

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

vgWorkSpaceBar::vgWorkSpaceBar()
{
	// TODO: add one-time construction code here
	//	m_bDragging = false;//开始不是处在拖拽状态
	m_nodeList.clear();
	//m_meshNodeList.clear();
}

vgWorkSpaceBar::~vgWorkSpaceBar()
{
	int size = m_nodeList.size();
	
	for (int i=0; i<size; i++)
	{
		if (m_nodeList[i] != NULL)
			delete m_nodeList[i];
	}

	m_nodeList.clear();

	// 删除MeshNode
// 	for (int i=0; i<m_meshNodeList.size(); i++)
// 	{
// 		if (m_meshNodeList[i] != NULL)
// 		{
// 			delete m_meshNodeList[i];
// 		}
// 	}
	
}

void vgWorkSpaceBar::DeleteAllNode()
{
	for( int i = 0; i < m_nodeList.size(); i++ )
	{
		if( m_nodeList[i] != NULL )
		{
			delete m_nodeList[i];
		}
		
		m_nodeList[i] = NULL;
	}
	m_nodeList.clear();

	m_pNodeList = NULL;
}


void vgWorkSpaceBar::cleartree( HTREEITEM item )
{
	if (m_wndTree.ItemHasChildren(item))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_wndTree.GetChildItem(item);

		while (hChildItem != NULL)
		{
			hNextItem = m_wndTree.GetNextItem(hChildItem, TVGN_NEXT);
			cleartree( hChildItem );
			hChildItem = hNextItem;
		}
		cleartree( item );
	}
	else
		m_wndTree.DeleteItem(item);

}

HTREEITEM vgWorkSpaceBar::AddNode(vgBaseEntry* node)
{

		m_pTreeSelect	= &m_wndTree;
		m_pNodeList		= &m_nodeList;


	if (m_pNodeList->empty())
	{
		node->hTreeItem =  m_pTreeSelect->InsertItem(node->GetName().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage());
	}
	else
	{
		node->hTreeItem =  m_pTreeSelect->InsertItem(node->GetName().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage(), (m_pNodeList->at(0))->hTreeItem);
	}

	m_pNodeList->push_back(node);
	
	m_pTreeSelect->SetItemData(node->hTreeItem, (DWORD_PTR)node);

	return node->hTreeItem;
	//return m_wndTree.AddNode(node);
}

HTREEITEM vgWorkSpaceBar::AddNode(HTREEITEM parent, vgBaseEntry* node)
{
	ASSERT(parent);

		m_pTreeSelect	= &m_wndTree;
		m_pNodeList		= &m_nodeList;


	node->hTreeItem = m_pTreeSelect->InsertItem(node->GetName().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage(), parent);
	m_pNodeList->push_back(node);

	m_pTreeSelect->SetItemData(node->hTreeItem, (DWORD_PTR)node);

	return node->hTreeItem;
	//return m_wndTree.AddNode(parent, node);
}

HTREEITEM vgWorkSpaceBar::AddNode(vgBaseEntry* parentNode, vgBaseEntry* node)
{
	ASSERT(parentNode);


		m_pTreeSelect	= &m_wndTree;
		m_pNodeList		= &m_nodeList;

	node->hTreeItem = m_pTreeSelect->InsertItem(node->GetName().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage(), parentNode->hTreeItem);
	m_pNodeList->push_back(node);

	m_pTreeSelect->SetItemData(node->hTreeItem, (DWORD_PTR)node);

	return node->hTreeItem;
	// return m_wndTree.AddNode(parentNode, node);
}

HTREEITEM vgWorkSpaceBar::AddNode(string parentName, vgBaseEntry* node, HTREEITEM parentItem)
{

		m_pTreeSelect	= &m_wndTree;
		m_pNodeList		= &m_nodeList;


	for (int i=0; i<m_pNodeList->size(); i++)
	{
		if (m_pNodeList->at(i) && parentName == (m_pNodeList->at(i))->GetName())
		{
			node->hTreeItem = m_pTreeSelect->InsertItem(node->GetName().c_str(), node->GetUnSelectedImage(), 
				node->GetSelectedImage(),(m_pNodeList->at(i))->hTreeItem);
			m_pNodeList->push_back(node);

			m_pTreeSelect->SetItemData(node->hTreeItem, (DWORD_PTR)node);

			return node->hTreeItem;
		}
	}
	
	HTREEITEM	hRootItem;
	if(parentItem)
	{
		hRootItem = parentItem;
	}
	else
	{
		hRootItem = (m_pNodeList->at(0))->hTreeItem;
	}
	vgBaseEntry *entry = new vgRootEntry(parentName);
	entry->hTreeItem = AddNode(hRootItem, entry);

	node->hTreeItem = m_pTreeSelect->InsertItem(node->GetName().c_str(), node->GetUnSelectedImage(), node->GetSelectedImage(),entry->hTreeItem);
	m_pNodeList->push_back(node);

	m_pTreeSelect->SetItemData(node->hTreeItem, (DWORD_PTR)node);

	return node->hTreeItem;
}




void vgWorkSpaceBar::DeleteNode(vgBaseEntry* pNode, bool delhItem)
{
	// 删除时只是把指针设置为NULL

	if (pNode)
	{
		for (int i=0; i<m_nodeList.size(); i++)
		{
			if (m_nodeList[i] == pNode)
			{
				if (delhItem)
				{
					TRACE("Delete Item herer !!!");
					m_wndTree.DeleteItem(m_nodeList[i]->hTreeItem);
				}

				delete m_nodeList[i];

				m_nodeList[i] = NULL;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers
// 
// int vgWorkSpaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
// {
// 	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
// 		return -1;
// 	
// 	CRect rectDummy;
// 	rectDummy.SetRectEmpty ();
// 
// 	CRect rectTab;
// 	ScreenToClient (&rectTab);
// 
// 	m_wndTab.Create (CBCGPTabWnd::STYLE_3D, rectTab, this, 1,
// 		CBCGPTabWnd::LOCATION_TOP);
// 
// 	m_wndTab.SetImageList (NIDB_WORKSPACE, 16, RGB (255, 0, 255));
// 
// 	m_wndTab.SetLocation(CBCGPTabWnd::LOCATION_BOTTOM);
// 	CArray<COLORREF, COLORREF> arColors;
// 
// 	arColors.Add (RGB (210, 210, 255));
// 	arColors.Add (RGB (190, 218, 153));
// 	arColors.Add (RGB (255, 170, 100));
// 
// 	m_wndTab.SetAutoColors (arColors);
// 	m_wndTab.EnableAutoColor (TRUE);
// 	m_wndTab.RecalcLayout ();
// 	m_wndTab.RedrawWindow ();
// 
// 	// Create tree windows.
// 	// TODO: create your own tab windows here:
// 	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
// 								TVS_LINESATROOT | TVS_HASBUTTONS;// | TVS_SHOWSELALWAYS;
// 	
// 
// 	if (!m_wndTree.Create (dwViewStyle, rectDummy, &m_wndTab, NIDC_WORKSPACE_TREE1))
// 	{
// 		TRACE0("Failed to create workspace view\n");
// 		return -1;      // fail to create
// 	}
// 	if (!m_wndTree2.Create (dwViewStyle, rectDummy, &m_wndTab, NIDC_WORKSPACE_TREE1))
// 	{
// 		TRACE0("Failed to create workspace view\n");
// 		return -1;      // fail to create
// 	}
// 
// 
// 	// Setup trees content:
// 	/*HTREEITEM hRoot1 = m_wndTree.InsertItem (_T("Root 1"));
// 	m_wndTree.InsertItem (_T("Item 1"), hRoot1);
// 	m_wndTree.InsertItem (_T("Item 2"), hRoot1);*/
// 
// 	// 设置Tree Item图标
// 	HICON hIcon[3];
// 
// 	m_imageList.Create(16, 16,ILC_COLOR32|ILC_MASK, 3, 3);
// 	hIcon[0] = AfxGetApp()->LoadIcon(NIDI_ICON1);
// 	hIcon[1] = AfxGetApp()->LoadIcon(NIDI_ICON3);
// 	hIcon[2] = AfxGetApp()->LoadIcon(NIDI_ICON2);
// 
// 	for (int i=0; i<3; i++)
// 	{
// 		m_imageList.Add(hIcon[i]);
// 	}
// 	
// 	m_wndTree.SetImageList(&m_imageList, TVSIL_NORMAL);
// 	m_wndTree2.SetImageList(&m_imageList, TVSIL_NORMAL);
// 	
// 	//m_wndTab.AddTab(&m_wndTree, "树视图1", 0, FALSE);
// 	//m_wndTab.AddTab(&m_wndTree2, "树视图2", 0, FALSE);
// #if VGK_LANG_CHS
// 	m_wndTab.AddTab(&m_wndTree, "场景视图", 0, FALSE);
// 	//m_wndTab.AddTab(&m_wndTree2, "矢量视图", 0, FALSE);
// #else
// 	m_wndTab.AddTab(&m_wndTree, "Scene View", 0, FALSE);
// 	//m_wndTab.AddTab(&m_wndTree2, "Vector View", 0, FALSE);
// #endif
// 
// 	return 0;
// }
// 
// void vgWorkSpaceBar::OnSize(UINT nType, int cx, int cy) 
// {
// 	CBCGPDockingControlBar::OnSize(nType, cx, cy);
// 
// 	// Tab control should cover a whole client area:
// 	//m_wndTree.SetWindowPos (NULL, nBorderSize, nBorderSize, 
// 	//	cx - 2 * nBorderSize, cy - 2 * nBorderSize,
// 	//	SWP_NOACTIVATE | SWP_NOZORDER);
// 
// 	CRect rectClient;
// 	GetClientRect (rectClient);
// 	m_wndTab.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
// }
// 
// void vgWorkSpaceBar::OnPaint() 
// {
// 	CPaintDC dc(this); // device context for painting
// 	
// 	CRect rectTree;
// 	m_wndTree.GetWindowRect (rectTree);
// 	ScreenToClient (rectTree);
// 
// 	rectTree.InflateRect (nBorderSize, nBorderSize);
// 	dc.Draw3dRect (rectTree,	::GetSysColor (COLOR_3DSHADOW), 
// 								::GetSysColor (COLOR_3DSHADOW));
// }


// 四叉树视图

