// vgUIController 

#pragma once

#include "vgPropertiesViewBar.h"
#include "vgWorkSpaceBar.h"
#include "vgBasedNode.h"
#include "vgBasedTabPage.h"
#include "vgTabDef.h"
#include "vgPropertyPage.h"

#include "vgCameraNode.h"
#include "vgRootNode.h"
#include "vgTestNode1.h"

/**
* vgUIController 是UI的核心控制组件，用于管理应用程序界面
* 的树视图和属性视图。vgUIController 使用单态封装，用户可
* 通过单态函数控制UI组件.
* 当前版本vgUIController可管理树视图vgWorkSpaceBar,属性视
* 图vgPropertyViewBar.
*
* @see		   vgWorkSpaceBar
* @see		   vgPropertiesViewBar
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0+
*/

//enum	E_IMAGE_TYPE
//{
//	NONE_SELECT,				// 0
//	
//	BASE_SELECT,				// 1
//	BASE_UNSELECT,
//	
//	OBJECT_SELECT,				// 3
//	OBJECT_UNSELECT,
//	OBJECT_KEYFRAME_SELECT,		// 5
//	OBJECT_KEYFRAME_UNSELECT,
//	OBJECT_BAKED_SELECT,		// 7
//	OBJECT_BAKED_UNSELECT
//};

class vgUIController
{
public:
	static vgUIController* GetInstance();
	static void DestoryInstance();

protected:
	static vgUIController* s_pInstance;

public:
	vgPropertiesViewBar* GetPropertiesViewBar();

	void AddTabPage(string pageName, CWnd* page);
	
	void RemoveAllPages();

	vgWorkSpaceBar* GetWorkSpaceBar();

	HTREEITEM AddNode(HTREEITEM parent, vgBasedNode* node); 
	
	HTREEITEM AddNode(vgBasedNode* node); 
	
	HTREEITEM AddNode(vgBasedNode* parentNode, vgBasedNode* node); 
	
	// 根据注册ID 得到控制属性页
	// @see vgTabDef.h
	vgBasedTabPage* GetTabPage(long ID);
	
	// 得到自动属性页用于自动生成
	// @see vgPropertyPage
	vgPropertyPage* GetPropPage();

	vector<vgBasedNode*>& GetNodeList(); 
	
	// 根据节点名称获得节点
	vgBasedNode* GetNode(string nameID); //{ return m_pWorkSpaceBar->GetNode(nameID); }
	
	// 通知树视图选中pNode指向的节点
	void SelectNode(vgBasedNode* pNode);// { m_pWorkSpaceBar->SelectNode(pNode); }

	// 得到当前选中的节点
	// 更新节点数据时，通过此函数判断是否应该更新属性显示
	// @see vgTestNode1::SetPosX
	vgBasedNode* GetCurrentSelectedNode(); //{ return m_currentSelected; }

	// FrameWork调用设置当前选择节点
	// @see vgEditTreeCtrl::OnSelectedChanged
	void SetCurrentSelectedNode(vgBasedNode* pNode); //{ m_currentSelected = pNode; }

protected:
	vgUIController(void);
	
	~vgUIController(void);
	
	vgBasedNode					*m_currentSelected;
	
	// 属性视图
	vgPropertiesViewBar			*m_pTabView;
	
	// 树视图
	vgWorkSpaceBar				*m_pWorkSpaceBar;	
	
	// 已注册的Tab页
	vgBasedTabPage*				m_listTabPage[TAB_ARRAY_SIZ];
	
	// 可自动生成的属性页
	vgPropertyPage*				m_propPage;

	//ui////////////////////////////////////////////////////////////////////////
	HTREEITEM		m_hRootNode;	//rootnode层

	HTREEITEM		m_hRootVGM;		//vgm层
	HTREEITEM		m_hRootVG;		//vg层
	HTREEITEM		m_hRootCamera;	//camera层
public:
	bool			InitUIControl(void);
	HTREEITEM&	GetRootNode()		{	return m_hRootNode; }
	HTREEITEM&	GetRootVGM()		{	return m_hRootVGM; }
	HTREEITEM&	GetRootVG()			{	return m_hRootVG; }
	HTREEITEM&	GetRootCamera()		{	return m_hRootCamera; }
};

inline vector<vgBasedNode*>& vgUIController::GetNodeList()
{
	return m_pWorkSpaceBar->GetNodeList();
}

inline HTREEITEM vgUIController::AddNode(HTREEITEM parent, vgBasedNode* node) 
{ 
	return m_pWorkSpaceBar->AddNode(parent, node); 
}

inline HTREEITEM vgUIController::AddNode(vgBasedNode* node) 
{ 
	return m_pWorkSpaceBar->AddNode(node); 
}

inline HTREEITEM vgUIController::AddNode(vgBasedNode* parentNode, vgBasedNode* node) 
{ 
	return m_pWorkSpaceBar->AddNode(parentNode, node); 
}

inline vgBasedNode* vgUIController::GetNode(string nameID)
{ 
	return m_pWorkSpaceBar->GetNode(nameID); 
}

inline void vgUIController::SelectNode(vgBasedNode* pNode)
{ 
	m_pWorkSpaceBar->SelectNode(pNode); 
}

inline vgBasedNode* vgUIController::GetCurrentSelectedNode() 
{ 
	return m_currentSelected; 
}

inline void vgUIController::SetCurrentSelectedNode(vgBasedNode* pNode) 
{ 
	m_currentSelected = pNode; 
}
