// vgUIController 

#pragma once

#include "vgPropertiesViewBar.h"
#include "vgWorkSpaceBar.h"
#include "vgBaseEntry.h"
#include "vgBasedTabPage.h"
#include "vgTabDef.h"
#include "vgPropertyPage.h"
#include "vgOutputBar.h"


#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkInputSystem.h>

#include "vgCoordinateEntry.h"//2008.9.11
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
 
class vgUIController : public vgKernel::InputHandler
{
public:

	static vgUIController* GetInstance();

	static vgUIController& getSingleton()
	{
		return *GetInstance();
	}

	static void DestoryInstance();

	// status bar index
	static const int nStatusInfo = 0;
	static const int nStatusProgress = 1;

	static const int nStatusFrame = 2;// 3;
	static const int nStatusOcc	  = 3;

protected:

	static vgUIController* s_pInstance;

public:
	vgOutputBar* GetOutputBar() { return m_pOutputBar ; } 

	CBCGPStatusBar* GetStatusBar() { return m_wndStatusBar; }

	vgPropertiesViewBar* GetPropertiesViewBar();

	void AddTabPage(string pageName, CWnd* page);
	
	void RemoveAllPages();


	vgWorkSpaceBar* GetWorkSpaceBar();

	HTREEITEM AddNode(HTREEITEM parent, vgBaseEntry* node); 
	
	HTREEITEM AddNode(vgBaseEntry* node); 
	
	HTREEITEM AddNode(vgBaseEntry* parentNode, vgBaseEntry* node); 
	
	HTREEITEM AddNode(string parentName, vgBaseEntry *node, HTREEITEM parentItem = NULL);

	void      DeleteNode(vgBaseEntry* pNode, bool delhItem) { m_pWorkSpaceBar->DeleteNode(pNode, delhItem); }
	// 根据注册ID 得到控制属性页
	// @see vgTabDef.h
	vgBasedTabPage* GetTabPage(long ID);
	
	// 得到自动属性页用于自动生成
	// @see vgPropertyPage
	vgPropertyPage* GetPropPage();

	vector<vgBaseEntry*>& GetNodeList(); 
		
	// 通知树视图选中pNode指向的节点
	void SelectNode(vgBaseEntry* pNode);

	void ClearSelection();

	void AddSelection(vgBaseEntry* pNode);

	// 得到当前选中的节点
	// 更新节点数据时，通过此函数判断是否应该更新属性显示
	// @see vgTestNode1::SetPosX
	vgBaseEntry* GetCurrentSelectedNode(); 

	// FrameWork调用设置当前选择节点
	// @see vgEditTreeCtrl::OnSelectedChanged
	void SetCurrentSelectedNode(vgBaseEntry* pNode); 

public:
	// extends from Inputsystem.  
	virtual void OnChar(int keyCode);

public:
	// StatusBar 函数

	// 开启进度条
	void EnableProgressBar();

	// 关闭进度条
	void DisableProgressBar();

	// 设置进度
	void SetProgress(UINT cnt);

	// 设置帧速
	void SetFrameSpeed(UINT speed);

	void SetNewOccCnt(UINT tcnt,UINT rcnt,UINT cnt);

protected:
	vgUIController(void);
	
	virtual ~vgUIController(void);
	
	vgBaseEntry					*m_currentSelected;
	
	// 属性视图
	vgPropertiesViewBar			*m_pTabView;
	
	// 树视图
	vgWorkSpaceBar				*m_pWorkSpaceBar;	

	vgOutputBar					*m_pOutputBar;
	
	// 已注册的Tab页
	vgBasedTabPage*				m_listTabPage[TAB_ARRAY_SIZ];
	
	// 可自动生成的属性页
	vgPropertyPage				*m_propPage;

	// 状态栏
	CBCGPStatusBar				*m_wndStatusBar;

public:
	bool			InitUIControl(void);
	
protected:

	//	树视图根节点
	HTREEITEM		m_hRootQuadtree;
	
	HTREEITEM		m_hTerainNode;		//顶层

	// 节点过滤器////////////////////////////////////////////////////////////////////////
	HTREEITEM		m_hRootNode;		//顶层
		
	HTREEITEM		m_hRootSound;		// 音效
	
	HTREEITEM		m_hRootCamera;		// 相机
	
	HTREEITEM       m_hRootSpecial;		// 特效
	
	HTREEITEM		m_hRootMoving;		// 动画

	HTREEITEM		m_hRootModel;		// 模型

	HTREEITEM		m_hRootTopic;		// 专题
	//矢量节点
	HTREEITEM		m_hSubVecString;
	/////////////////////////////////////////////////////////////////////////chunyongma
	
	// 音效
	HTREEITEM       m_hSub3DSound;
	
	// 相机
	HTREEITEM       m_hSubStaticCamera;

	// 特效
	HTREEITEM       m_hSubBillboard;

	HTREEITEM       m_hSubFountain;
	HTREEITEM       m_hSubFire;
	HTREEITEM       m_hSubSmoke;
	HTREEITEM       m_hSubFlag;
	
	// 动画
	HTREEITEM		m_hSubKeyframe;
	HTREEITEM		m_hSubSkeleton;
	HTREEITEM		m_hSubAnimation;

	// GisMatch
	HTREEITEM		m_hSubROAD;
	HTREEITEM        m_hCityplan;
	// 模型
	HTREEITEM		m_hSubVGM;
	HTREEITEM		m_hSubMOD;

	//////////////////////////////////////////////////////////////////////////
	HTREEITEM       m_hSubWater;
	HTREEITEM       m_hSubGlass;
	HTREEITEM       m_hSubMirror;
	HTREEITEM       m_hSubMetal;
	HTREEITEM       m_hSubFloor;
	HTREEITEM       m_hSubVideotexture;
	HTREEITEM       m_hSubMoveskybox;
	HTREEITEM		m_hSubAutobuild;
	HTREEITEM		m_hSubTrigger;
	HTREEITEM		m_hSubDynamictex;

public:
	HTREEITEM&  GetRootVecString()			{	return m_hSubVecString;} //zhu
	//////////////////////////////////////////////////////////////////////////chunyongma
	HTREEITEM&  GetRoot3DSound()		{   return m_hSub3DSound; }
	HTREEITEM&  GetRootStaticCamera()	{   return m_hSubStaticCamera; }

	HTREEITEM&  GetRootBillboard()		{   return m_hSubBillboard; }
	
	HTREEITEM&  GetRootFountain()		{   return m_hSubFountain; }
	HTREEITEM&  GetRootFire()			{   return m_hSubFire; }
	HTREEITEM&  GetRootSmoke()			{   return m_hSubSmoke; }
	HTREEITEM&  GetRootFlag()			{   return m_hSubFlag; }
	
	HTREEITEM&  GetRootKeyframe()		{   return m_hSubKeyframe; }
	HTREEITEM&  GetRootSkeleton()		{	return m_hSubSkeleton; }
	HTREEITEM&  GetRootAnimation()		{	return m_hSubAnimation; }
	HTREEITEM&  GetRootROAD()			{	return m_hSubROAD;} //----- [9/23/2008 YX]
	HTREEITEM&  GetRootCityplan()      { return m_hCityplan; }//2008.10.21


	HTREEITEM&  GetRootVGM()			{   return m_hSubVGM; }
	HTREEITEM&  GetRootMOD()			{	return m_hSubMOD; }

	HTREEITEM&  GetRootGpu( vgCore::IMAGETYPE EFFECT_IMAGE_TYPE );
	
	HTREEITEM&  GetRootQuadtree()		{	return m_hRootQuadtree; }
	void  SetRootQuadtree(HTREEITEM hRootQuadtree)	{	m_hRootQuadtree = hRootQuadtree; }



	//////////////////////////////////////////////////////////////////////////
protected:
	//	矢量图形根节点
	HTREEITEM	m_hRootVector;
	HTREEITEM	m_hRootLayer;
	HTREEITEM	m_hSubShape;

	HTREEITEM	m_hSubShapePoint;
	HTREEITEM	m_hSubShapeLine;
	HTREEITEM	m_hSubShapePolygon;
	HTREEITEM	m_hSubShapeUnknow;
public:
	HTREEITEM&  GetRootVector()			{   return m_hRootVector; }
	HTREEITEM&  GetRootLayer()			{   return m_hRootLayer; }
	HTREEITEM&  GetSubShape()			{   return m_hSubShape; }

	HTREEITEM&  GetSubShapePoint()			{   return m_hSubShapePoint; }
	HTREEITEM&  GetSubShapeLine()			{   return m_hSubShapeLine; }
	HTREEITEM&  GetSubShapePolygon()		{   return m_hSubShapePolygon; }
	HTREEITEM&  GetSubShapeUnknow()			{   return m_hSubShapeUnknow; }



	//------------------------------------------
	// leven add
	//------------------------------------------

private:

	struct HTreeItemWrap
	{
	public:
		HTreeItemWrap( HTREEITEM item )
		{
			_hTreeItem = item;
		}

		HTREEITEM _hTreeItem;
		//TreeItemMap _children;
	};

	typedef std::map< String, HTreeItemWrap > TreeItemMap;
	typedef std::pair<TreeItemMap::iterator , bool> TreeItemMapInsertRes;

	TreeItemMap _rootItems;

public:

	bool addEntryToRootByName( const String& root_name , 
		vgBaseEntry* entry , 
		const bool& add_if_need = true );

	//bool addChildEntryByName( const String& father_entry , 
	//	const String& child_entry_name , vgBaseEntry* entry , 
	//	const bool& add_if_need = true );

};

inline vector<vgBaseEntry*>& vgUIController::GetNodeList()
{
	return m_pWorkSpaceBar->GetNodeList();
}

inline HTREEITEM vgUIController::AddNode(HTREEITEM parent, vgBaseEntry* node) 
{ 
	return m_pWorkSpaceBar->AddNode(parent, node); 
}

inline HTREEITEM vgUIController::AddNode(vgBaseEntry* node) 
{ 
	return m_pWorkSpaceBar->AddNode(node); 
}

inline HTREEITEM vgUIController::AddNode(vgBaseEntry* parentNode, vgBaseEntry* node) 
{ 
	return m_pWorkSpaceBar->AddNode(parentNode, node); 
}

inline HTREEITEM vgUIController::AddNode(string parentName, vgBaseEntry *node, 
										 HTREEITEM parentItem/* = NULL*/)
{
	return m_pWorkSpaceBar->AddNode(parentName, node, parentItem) ;
}


// inline vgBaseEntry* vgUIController::GetNode(string nameID)
// { 
// 	return m_pWorkSpaceBar->GetNode(nameID); 
// }

inline void vgUIController::SelectNode(vgBaseEntry* pNode)
{ 
	m_currentSelected = pNode;
	m_pWorkSpaceBar->SelectNode(pNode); 
	pNode->AddNodeTabs();
}

inline void vgUIController::ClearSelection()
{
	m_currentSelected = NULL;
	m_pWorkSpaceBar->ClearSelection(); 
}

inline void vgUIController::AddSelection(vgBaseEntry* pNode)
{
	ASSERT(m_currentSelected != NULL);
	m_pWorkSpaceBar->AddSelectedNode(pNode);

	//m_currentSelected = pNode;
	//pNode->AddNodeTabs();
}

inline vgBaseEntry* vgUIController::GetCurrentSelectedNode() 
{ 
	return m_currentSelected; 
}

inline void vgUIController::SetCurrentSelectedNode(vgBaseEntry* pNode) 
{ 
	m_currentSelected = pNode; 
}
