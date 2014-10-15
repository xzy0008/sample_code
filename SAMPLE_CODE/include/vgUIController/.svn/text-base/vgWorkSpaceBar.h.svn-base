// workspacebar.h : interface of the CWorkSpaceBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define   DRAG_DELAY   60
 
#include <vector>
#include <vgEntry/vgBaseEntry.h>
#include "vgXTreeCtrl.h"
#include "vgEditTreeCtrlEx.h"

#include <vgMesh/vgmMeshItem.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgEntry/vgRootEntry.h>
//#include <vgCamera.h>
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

using std::vector;

/**
* vgWorkSpaceBar 在vgUIController的控制下管理树视图
*
* @see		   vgUIController
*
* @author      ZSC
* @version     VRGIS Platform RC
* @since       VRGIS 1.0+
*/
/**
* 不再提供默认界面实现 只提供接口 所有界面相关实现由应用程序界面重写
*
* @see		   vgUIController	   
*
* @author      ZSC
* @version     VRGIS FrameWork 3.0RC
* @since       VRGIS 2.5
*/
class  VGUI_EXPORT vgWorkSpaceBar /*: public CBCGPDockingControlBar*/
{
	friend class vgUIController;
public:
	vgWorkSpaceBar();
	
	HTREEITEM AddNode(HTREEITEM parent, vgBaseEntry* node);
	
	HTREEITEM AddNode(vgBaseEntry* node);
	
	HTREEITEM AddNode(vgBaseEntry* parentNode, vgBaseEntry* node);

	HTREEITEM AddNode(string parent, vgBaseEntry* node, HTREEITEM parentItem);
	


	void	  DeleteNode(vgBaseEntry* pNode, bool delhItem);

	//vgBaseEntry* GetNode(String nameId);

	vector<vgBaseEntry*>& GetNodeList(); 

	// 点选Node，处理Ctrl点选
	void SelectNode(vgBaseEntry* pNode);

	// 框选时增加选择节点
	void AddSelectedNode(vgBaseEntry* pNode);

	//CTreeCtrl* GetTreeCtrl() { return m_wndTree; }
	void SetItemText(HTREEITEM hItem, String text)
	{
		m_wndTree.SetItemText(hItem, text.c_str());
	}

	//void UpdateMeshNode();

	//void AddMeshNode(vgMeshEntry* node);

	void ClearSelection()
	{
		// m_wndTree.ClearSelection();
		m_wndTree.RemoveAllSeletions();
	}

	void DeleteSelectedNode() 
	{
		m_wndTree.DeleteSelectedNode();
	}

	void Expand(HTREEITEM item) 
	{
		ASSERT(item);
		m_wndTree.Expand(item, TVE_EXPAND);
	}

	void EnsureVisible(HTREEITEM item) 
	{
		ASSERT(item);
		m_wndTree.EnsureVisible(item);
	}
	CEditTreeCtrlEx& GetTree(int nTreeIndex = 1)
	{
		if(2 == nTreeIndex)
			return m_wndTree2;
		else
			return m_wndTree;
	}
public:
	virtual void ShowControlBar(BOOL bShow, BOOL bDelay, BOOL bActivate/* = TRUE*/){}

	virtual BOOL IsVisible()
	{
		return FALSE;
	}

	// Attributes
protected:
	CEditTreeCtrlEx			m_wndTree;
	CEditTreeCtrlEx			m_wndTree2;
	CEditTreeCtrlEx*		m_pTreeSelect;

	vector <vgBaseEntry*>	m_nodeList;

	vector <vgBaseEntry*>*	m_pNodeList;

public:

// Implementation
public:
	virtual ~vgWorkSpaceBar();

// Generated message map functions
protected:
	CImageList		m_imageList;
	CBCGPTabWnd		m_wndTab;

// 	//{{AFX_MSG(CWorkSpaceBar)
// 	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
// 	afx_msg void OnSize(UINT nType, int cx, int cy);
// 	afx_msg void OnPaint();
// 	//}}AFX_MSG
// 
// 	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
// 
// 	afx_msg LRESULT OnTreeDrag(WPARAM h1,LPARAM h2); 
// 
// 	DECLARE_MESSAGE_MAP()

public:
	void cleartree( HTREEITEM item );

	void DeleteAllNode();
	//HTREEITEM CopyBranch(HTREEITEM htiBranch,HTREEITEM htiNewParent,HTREEITEM htiAfter);
	//HTREEITEM CopyItem(HTREEITEM hItem,HTREEITEM htiNewParent,HTREEITEM htiAfter);
};

/////////////////////////////////////////////////////////////////////////////

inline vector<vgBaseEntry*>& vgWorkSpaceBar::GetNodeList()
{
	return m_nodeList;
}

inline void vgWorkSpaceBar::SelectNode(vgBaseEntry* pNode) 
{
// 点选同一node也触发刷新
// m_wndTree.SelectItem(m_nodeList.front()->hTreeItem);
// 	m_wndTree.ClearSelection();
// 	m_wndTree.SelectItem(pNode->hTreeItem); 

	if (pNode == NULL)
		return ;
	
  	if (KEY_DOWN(VK_CONTROL))
  	{
  		m_wndTree.AddSelection(pNode->hTreeItem);
  	}
  	else
  	{
  		m_wndTree.SetSelection(pNode->hTreeItem);
  	}
}

inline void vgWorkSpaceBar::AddSelectedNode(vgBaseEntry* pNode)
{
	if (pNode == NULL)
		return ;
	
	m_wndTree.AddSelection(pNode->hTreeItem);
}