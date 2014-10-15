// workspacebar.h : interface of the CWorkSpaceBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define   DRAG_DELAY   60
 
#include <vector>
#include "vgBasedNode.h"
#include "vgXTreeCtrl.h"
#include "vgEditTreeCtrlEx.h"

using std::vector;

/**
* vgWorkSpaceBar 在vgUIController的控制下管理树视图
*
* @see		   vgUIController
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0+
*/

class vgWorkSpaceBar : public CBCGPDockingControlBar
{
	friend class vgUIController;
public:
	vgWorkSpaceBar();
	
	HTREEITEM AddNode(HTREEITEM parent, vgBasedNode* node);
	
	HTREEITEM AddNode(vgBasedNode* node);
	
	HTREEITEM AddNode(vgBasedNode* parentNode, vgBasedNode* node);

	vgBasedNode* GetNode(string nameId);

	vector<vgBasedNode*>& GetNodeList(); 

	void SelectNode(vgBasedNode* pNode);

	void SetRootNodeCount(unsigned int nodeCount)	{	m_uiRootNodeCount = nodeCount;}
// Attributes
protected:
	CEditTreeCtrlEx			m_wndTree;
	CEditTreeCtrlEx			m_wndTree2;

	vector <vgBasedNode*>	m_nodeList;
	unsigned int			m_uiRootNodeCount;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkSpaceBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~vgWorkSpaceBar();

// Generated message map functions
protected:
	CImageList		m_imageList;
	CBCGPTabWnd		m_wndTab;

	//{{AFX_MSG(CWorkSpaceBar)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG

	//afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMRclickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);

	afx_msg LRESULT OnTreeDrag(WPARAM h1,LPARAM h2); 
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnTimer(UINT nIDEvent);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:
	//HTREEITEM CopyBranch(HTREEITEM htiBranch,HTREEITEM htiNewParent,HTREEITEM htiAfter);
	//HTREEITEM CopyItem(HTREEITEM hItem,HTREEITEM htiNewParent,HTREEITEM htiAfter);
};

/////////////////////////////////////////////////////////////////////////////

inline vector<vgBasedNode*>& vgWorkSpaceBar::GetNodeList()
{
	return m_nodeList;
}

inline void vgWorkSpaceBar::SelectNode(vgBasedNode* pNode) 
{
	// 点选同一node也触发刷新
	m_wndTree.ClearSelection();
	m_wndTree.SelectItem(pNode->hTreeItem); 
}