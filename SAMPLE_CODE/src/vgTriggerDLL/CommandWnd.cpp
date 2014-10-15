// CommandWnd.cpp : implementation file
/*
** Created by FengYK
*/

#include <vgStableHeaders.h>
#include "vgTriggerDLL/CommandWnd.h"

#include "vgTrigger/vgtrTriggerManager.h"
#include "vgKernel/vgkSelectManager.h"
#include <vgTrigger/vgtrDialogTriggerSetting.h>

#define VGMSGBOX2(A) {\
	this->SetTimer(1, 150, NULL);\
	A; \
	this->SetTimer(1, 15, NULL);}


// 主菜单显示的TEXT
 std::string s_menuName = "事件系统(&E)";
 UINT s_menuPosition = -1;

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
/*const*/ /*static*/
const static UINT ID_TRIGGER_CONVERT_DLL= ::RegisterWindowMessage( _T("ID_TRIGGER_CONVERT_DLL") );
const static UINT ID_TRIGGER_ENABLE_DLL		= ::RegisterWindowMessage( _T("ID_TRIGGER_ENABLE_DLL") );
const static UINT ID_TRIGGER_EDIT_EVENT_DLL		= ::RegisterWindowMessage( _T("ID_TRIGGER_EDIT_EVENT_DLL") );

IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_TRIGGER_CONVERT_DLL, OnTriggerConvert ) 
 	ON_REGISTERED_MESSAGE( ID_TRIGGER_ENABLE_DLL, OnTriggerEnable ) 
 	ON_REGISTERED_MESSAGE( ID_TRIGGER_EDIT_EVENT_DLL, OnTriggerEditEvent ) 

	//ON_UPDATE_COMMAND_UI(ID_TRIGGER_ENABLE, &CvgFrameWorkView::OnUpdateTriggerEnable)

END_MESSAGE_MAP()

// CCommandWnd message handlers
LRESULT CCommandWnd::OnTriggerConvert( WPARAM wParam, LPARAM lParam )
{
	// TODO: 在此添加命令处理程序代码
	vgKernel::RendererQueue queue = vgKernel::SelectManager::getSingleton().getSelectedItems();

	vgTrigger::Trigger *pTrigger = NULL;
	if (queue.size() == 1)
	{
		pTrigger = vgTrigger::TriggerManager::getSingleton().addTrigger(queue.at(0));
	}
	else if (queue.empty())
	{
		AfxMessageBox("请选择接受触发的模型！");
		vgKernel::SelectManager::getSingleton().clearSelection();		
	}

	if ( pTrigger )
	{
		vgKernel::SelectManager::getSingleton().clearSelection();
		vgKernel::SelectManager::getSingleton().addSelection(pTrigger);			
	}

	return 0;

}

LRESULT CCommandWnd::OnTriggerEnable( WPARAM wParam, LPARAM lParam )
{
	vgTrigger::TriggerManager::getSingleton().setAllTriggerEnable(
		! vgTrigger::TriggerManager::getSingleton().getAllTriggerEnable());

	return 0;
}


LRESULT CCommandWnd::OnTriggerEditEvent( WPARAM wParam, LPARAM lParam )
{
	CDialogTriggerSetting	dlg;
	VGMSGBOX2 ( dlg.DoModal() )

	return 0;
}

// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("转换所选物体为触发器(Convert to &Trigger)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_TRIGGER_CONVERT_DLL;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("开启关闭所有触发器(Enable\\Disable &event)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_TRIGGER_ENABLE_DLL;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("触发器事件编辑器(Event Ed&itor)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_TRIGGER_EDIT_EVENT_DLL;
	(*NextMenuID)++;

	return true;
}
//add by kinghj 2009.12.3实现用户自加载的右键菜单项
bool SetRightUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	//查看下面注掉的内容添加菜单项。也可以参见上面的SetUserMenu()函数
	//SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("动态加载") ) ;
	//s_CommandToMessage[*NextMenuID] = ID_DYNAMICADD_DLL;
	//(*NextMenuID)++;

	//SubMenu->InsertMenu(3,MF_BYPOSITION|MF_POPUP|MF_STRING,

	//	(UINT) SubMenu,"二级菜单"); //添加子菜单


	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	if (ID == ID_TRIGGER_CONVERT_DLL)
	{
	}

	if (ID == ID_TRIGGER_ENABLE_DLL)
	{
		return vgTrigger::TriggerManager::getSingleton().getAllTriggerEnable();
	}

	if (ID == ID_TRIGGER_EDIT_EVENT_DLL)
	{
	}

	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{
	if (ID == ID_TRIGGER_CONVERT_DLL)
	{
	}

	if (ID == ID_TRIGGER_ENABLE_DLL)
	{
	}

	if (ID == ID_TRIGGER_EDIT_EVENT_DLL)
	{
	}
	// 默认菜单开启
	return true;
}