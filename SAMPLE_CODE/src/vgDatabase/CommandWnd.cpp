// CommandWnd.cpp : implementation file
/*
** Created by Lesky Zhou 
*/

#include <vgStableHeaders.h>
#include "vgDatabase/CommandWnd.h"
#if 0

#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgDlgDBConnect.h>


// 主菜单显示的TEXT
std::string s_menuName = "数据库(&Database)";
UINT s_menuPosition = -1;

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
const static UINT ID_DB_DLL_CONNECT		= ::RegisterWindowMessage( _T("ID_DB_DLL_CONNECT") );
const static UINT ID_DB_DLL_DISCONNECT  = ::RegisterWindowMessage( _T("ID_DB_DLL_DISCONNECT") );
const static UINT ID_DB_DLL_CONDITION   = ::RegisterWindowMessage( _T("ID_DB_DLL_CONDITION") );

IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
	m_dbCondition = NULL;
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_DB_DLL_CONNECT, OnDbConnect ) 
	ON_REGISTERED_MESSAGE( ID_DB_DLL_DISCONNECT, OnDbDisconnect ) 
	ON_REGISTERED_MESSAGE( ID_DB_DLL_CONDITION, OnDbCondition ) 

 	ON_REGISTERED_MESSAGE( WM_DELETE_DLG, OnDelDlgMsg )
END_MESSAGE_MAP()

// CCommandWnd message handlers
LRESULT CCommandWnd::OnDbConnect( WPARAM wParam, LPARAM lParam )
{
	DBConnectDlg dialog;

	dialog.DoModal();

	return 0;
}

LRESULT CCommandWnd::OnDbDisconnect( WPARAM wParam, LPARAM lParam )
{
	if (! vgDatabase::DatabaseManager::getSingleton().CloseDatabase())
	{
		AfxMessageBox("数据库未连接或关闭失败!");
	}
	else
	{
		AfxMessageBox("已关闭数据库连接!");
	}

	return 0;
}

LRESULT CCommandWnd::OnDbCondition( WPARAM wParam, LPARAM lParam )
{
	if (! vgDatabase::DatabaseManager::getSingleton().IsOpen())
	{
		DBConnectDlg dialog;

		dialog.DoModal();

		if (! vgDatabase::DatabaseManager::getSingleton().IsOpen())
		{
			return 0;
		}
	}

	if (!vgDatabase::ProfileManager::getSingleton().IsProfileLoaded())
	{
		AfxMessageBox("未加载profile文件，请先加载动态库再打开场景vg文件！");
		return 0;
	}

	if(m_dbCondition)
	{
		m_dbCondition->SetForegroundWindow();
	}
	else
	{
		m_dbCondition = new DBCondition(this);
		m_dbCondition->Create(DBCondition::IDD, GetDesktopWindow());
		m_dbCondition->ShowWindow(SW_SHOW);
	}

	return 0;
}

LRESULT  CCommandWnd::OnDelDlgMsg( WPARAM wParam, LPARAM lParam )
{
	delete m_dbCondition;
	m_dbCondition = NULL;

	return 0;
}


// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("连接数据库(&Link Database)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_DB_DLL_CONNECT;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("断开数据库(&Dislink Database)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_DB_DLL_DISCONNECT;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("自定义查询(&Custom Query)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_DB_DLL_CONDITION;
	(*NextMenuID)++;


	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	if (ID == ID_DB_DLL_CONNECT)
	{
	}

	if (ID == ID_DB_DLL_DISCONNECT)
	{
	}

	if (ID == ID_DB_DLL_CONDITION)
	{
	}

	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{
	if (ID == ID_DB_DLL_CONNECT)
	{
	}

	if (ID == ID_DB_DLL_DISCONNECT)
	{
	}

	if (ID == ID_DB_DLL_CONDITION)
	{
	}

	// 默认菜单开启
	return true;
}
#endif