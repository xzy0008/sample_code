// CommandWnd.cpp : implementation file
/*
** Created by Lesky Zhou 
*/

#include <vgStableHeaders.h>
#if 0
#include "vgScript/CommandWnd.h"

#include <vgScript/vgscScriptManager.h>
#include <vgKernel/vgkSelectManager.h>




// 主菜单显示的TEXT
std::string s_menuName = "脚本系统(&T)";

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
const static UINT ID_SCRIPT_RUN_FILE		= ::RegisterWindowMessage( _T("ID_SCRIPT_RUN_FILE") )  ;
const static UINT ID_SCRIPT_RUN_CONSOLE	= ::RegisterWindowMessage( _T("ID_SCRIPT_RUN_CONSOLE") )  ;
const static UINT ID_SCRIPT_RUN_CONFIG		= ::RegisterWindowMessage( _T("ID_SCRIPT_RUN_CONFIG") )  ;

const static UINT ID_SCRIPT_REFRESH		= ::RegisterWindowMessage( _T("ID_SCRIPT_REFRESH") )  ;


IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_SCRIPT_RUN_FILE, OnScriptRunFile ) 
	ON_REGISTERED_MESSAGE( ID_SCRIPT_RUN_CONSOLE, OnScriptRunConsole ) 
	ON_REGISTERED_MESSAGE( ID_SCRIPT_RUN_CONFIG, OnScriptRunConfig ) 
	ON_REGISTERED_MESSAGE( ID_SCRIPT_REFRESH, OnScriptRefresh ) 
END_MESSAGE_MAP()

LRESULT CCommandWnd::OnScriptRunFile( WPARAM wParam, LPARAM lParam )
{
	vgScript::ScriptManager::getSingleton().createMultiSelectDailogAndRunScript();
return 0;
}

LRESULT CCommandWnd::OnScriptRunConsole( WPARAM wParam, LPARAM lParam )
{
	vgScript::ScriptManager::getSingleton().runScriptConsole();

	return 0;
}

LRESULT CCommandWnd::OnScriptRunConfig( WPARAM wParam, LPARAM lParam )
{
	vgScript::ScriptManager::getSingleton().runUserScriptConfig();
	return 0;
}

LRESULT CCommandWnd::OnScriptRefresh( WPARAM wParam, LPARAM lParam )
{
	using namespace vgScript;


	ScriptManager::getSingleton().setUserDefinedScripts( 
		ScriptManager::getSingleton().getUserDefinedScripts() );

	return 0;
}


// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("运行脚本(Run Script Fi&le)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_SCRIPT_RUN_FILE;
	(*NextMenuID)++;


	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("运行控制台(Run Script Consol&e)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SCRIPT_RUN_CONSOLE;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("用户脚本设置(User Script Confi&g)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SCRIPT_RUN_CONFIG;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("刷新脚本(Re&fresh Script)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SCRIPT_REFRESH;
	(*NextMenuID)++;



	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	if (ID == ID_SCRIPT_RUN_FILE)
	{
		//return (vgSolar::SolarManager::);
	}

	if (ID == ID_SCRIPT_RUN_CONSOLE)
	{
		//return (vgGIS3nalysisType());
	}

	if (ID == ID_SCRIPT_RUN_CONFIG)
	{
		//return (vgGIS3D::GisArea == vgGIS3D::GisManager::getSingleton().getAnalysisType());
	}
	


	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{
	if (ID == ID_SCRIPT_RUN_FILE)
	{
		//return (vgSolar::SolarManager::);
	}

	if (ID == ID_SCRIPT_RUN_CONSOLE)
	{
		//return (vgGIS3nalysisType());
	}

	if (ID == ID_SCRIPT_RUN_CONFIG)
	{
		//return (vgGIS3D::GisArea == vgGIS3D::GisManager::getSingleton().getAnalysisType());
	}



	// 默认菜单开启
	return true;
}
#endif