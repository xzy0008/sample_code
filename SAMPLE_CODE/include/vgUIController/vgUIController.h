// UIController 

#pragma once

#include <vgUIController/vgUIControlDefinition.h>
#include <vgUIController/vgPropertiesViewBar.h>
#include <vgUIController/vgWorkSpaceBar.h>

#include <vgUIController/vgBasedTabPage.h>
#include <vgUIController/vgTabDef.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgUIController/vgBasedTabPage.h>
#include <vgUIController/vgOutputBar.h>

#include <vgUIController/vgEntryRootManager.h>

#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgEntry/vgBaseEntry.h>
#include <vgEntry/vgCoordinateEntry.h>
#include <vgEntry/vgBackgroundEntry.h>
#include <vgEntry/vgFogEntry.h>
/**
* UIController 是UI的核心控制组件，用于管理应用程序界面
* 的树视图和属性视图。UIController 使用单态封装，用户可
* 通过单态函数控制UI组件.
* 当前版本UIController可管理树视图vgWorkSpaceBar,属性视
* 图vgPropertyViewBar.
*
* @see		   vgWorkSpaceBar
* @see		   vgPropertiesViewBar
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0+
*/
namespace vgUI
{

	class  VGUI_EXPORT UIController : public vgKernel::InputHandler
		, public vgKernel::Singleton<UIController>
	{
		friend class vgKernel::Singleton<UIController>;
		//成员函数
	public :
		UIController();
		virtual ~UIController();

	protected:
		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			return true;
		}

		// status bar index
	
	public :
		enum	EStatusType
		{
			StatusInfo,
			StatusProgress,
			StatusFrame,
			StatusOcc
		};

	public:

		void unload();


		void reset();

		vgOutputBar* GetOutputBar() { return m_pOutputBar ; } 

		CBCGPStatusBar* GetStatusBar() { return m_wndStatusBar; }

		// get and set for properties bar
		vgPropertiesViewBar* GetPropertiesViewBar();
		
		void  SetPropertiesViewBar(vgPropertiesViewBar* pPorpView);

		void AddTabPage(string pageName, CWnd* page);

		void RemoveAllPages();

		// get and set for workspace bar 
		vgWorkSpaceBar* GetWorkSpaceBar();
		
		void SetWorkSpaceBar(vgWorkSpaceBar *pWorkSpaceBar);

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
		bool			initUIControl(void);

		//HTREEITEM       m_hTrigger;			// 触发器


	public:
		EntryRootManager*	getEntryRoot();

		HTREEITEM	getEntryRootItemByType(EDynamicEntryType entryType);
		HTREEITEM	getEntryRootItemByType(EStaticEntryType entryType);

		void appendEntryRootItem(EDynamicEntryType entryType, HTREEITEM item);
		void appendEntryRootItem(EStaticEntryType entryType, HTREEITEM item);

		HTREEITEM	appendStaticEntryRoot(String	rootname);
		HTREEITEM	appendStaticEntryRoot(EStaticEntryType entryType,
			vgBaseEntry* baseEntry);

		HTREEITEM	appendDynamicEntryRoot(String& rootname,
			EDynamicEntryType entryType );

		//HTREEITEM& GetRootTrigger()         { return m_hTrigger; }

	protected:
		EntryRootManager	m_entryRoot;

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

	inline vector<vgBaseEntry*>& UIController::GetNodeList()
	{
		return m_pWorkSpaceBar->GetNodeList();
	}

	inline HTREEITEM UIController::AddNode(HTREEITEM parent, vgBaseEntry* node) 
	{ 
		return m_pWorkSpaceBar->AddNode(parent, node); 
	}

	inline HTREEITEM UIController::AddNode(vgBaseEntry* node) 
	{ 
		return m_pWorkSpaceBar->AddNode(node); 
	}

	inline HTREEITEM UIController::AddNode(vgBaseEntry* parentNode, vgBaseEntry* node) 
	{ 
		return m_pWorkSpaceBar->AddNode(parentNode, node); 
	}

	inline HTREEITEM UIController::AddNode(string parentName, vgBaseEntry *node, 
		HTREEITEM parentItem/* = NULL*/)
	{
		return m_pWorkSpaceBar->AddNode(parentName, node, parentItem) ;
	}


	// inline vgBaseEntry* UIController::GetNode(string nameID)
	// { 
	// 	return m_pWorkSpaceBar->GetNode(nameID); 
	// }

	inline void UIController::SelectNode(vgBaseEntry* pNode)
	{ 
		m_currentSelected = pNode;
		m_pWorkSpaceBar->SelectNode(pNode); 
		pNode->AddNodeTabs();
	}

	inline void UIController::ClearSelection()
	{
		m_currentSelected = NULL;
		m_pWorkSpaceBar->ClearSelection(); 
	}

	inline void UIController::AddSelection(vgBaseEntry* pNode)
	{
		ASSERT(m_currentSelected != NULL);
		m_pWorkSpaceBar->AddSelectedNode(pNode);

		//m_currentSelected = pNode;
		//pNode->AddNodeTabs();
	}

	inline vgBaseEntry* UIController::GetCurrentSelectedNode() 
	{ 
		return m_currentSelected; 
	}

	inline void UIController::SetCurrentSelectedNode(vgBaseEntry* pNode) 
	{ 
		m_currentSelected = pNode; 
	}
}// namespace vgUI
