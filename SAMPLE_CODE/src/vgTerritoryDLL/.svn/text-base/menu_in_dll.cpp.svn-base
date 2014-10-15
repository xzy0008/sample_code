#include <vgStableHeaders.h>
#if 0
#include <vgDynamicMenu/menu_plugin_api.h>
#include "CommandWnd.h"

CWnd *								s_CommandWnd ;
CommandToMessage					s_CommandToMessage ; 
CommandCheckMessage					s_CommandCheckMessage;
CommandEnableMessage				s_CommandEnableMessage;
CBCGPMenuBar*						s_pMenuBar;

extern std::string s_menuName;
extern UINT s_menuPosition;

extern bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID);
extern bool GetUserMenuCheck(UINT ID);
extern bool GetUserMenuEnable(UINT ID);

/////////////////////////////////////////////////////////////////////////////////////////////

// 被DLL导出的动态菜单加载函数
// 以下函数一般不需要用户改动

// 加载菜单
BOOL InstallExtMenu( HWND ParentWindow, CBCGPMenuBar* pMenuBar, DWORD ChildID, UINT * NextMenuID )
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	BOOL bReturn = FALSE ; 

	HMENU hMenu = pMenuBar->GetDefaultMenu();

	// 避免重复加载
	if ( hMenu != NULL && s_CommandWnd == NULL )
	{

		CMenu ParentMenu ;
		if (! ParentMenu.Attach( hMenu ) )
		{
			AfxMessageBox("Main frm menu Attach failed ");
			return FALSE;
		}

		CMenu * SubMenu = NULL ; 

		int TestPosition = GetMenuPosition( &ParentMenu, s_menuName.c_str() ) ; // see if the test menu exists
		int HelpPosition = ParentMenu.GetMenuItemCount() ;

		if ( TestPosition != MENU_POSITION_ERR ) 
		{
			SubMenu = ParentMenu.GetSubMenu( TestPosition ) ;

			CBCGPToolbarMenuButton  menubtn (0, 
				SubMenu->GetSafeHmenu() , -1, s_menuName.c_str());

			if ( pMenuBar->InsertButton ( menubtn, TestPosition ) == -1)
			{
				AfxMessageBox("Insert Error");
			} 
		}
		else 
		{
			CMenu Menu ;
			Menu.CreateMenu() ;
			// detach the HMENU so that it isn't destroyed when Menu goes out of scope.
			HMENU hSubMenu = Menu.Detach();

 			if ( s_menuPosition == -1)
 			{
 				// 添加在help前
 				ParentMenu.InsertMenu( HelpPosition-1, MF_BYPOSITION| MF_POPUP|MF_STRING, (UINT_PTR)hSubMenu, s_menuName.c_str() ) ;
 			}
  			else
  			{
				// 添加在自定义位置
  				ParentMenu.InsertMenu( s_menuPosition, MF_BYPOSITION| MF_POPUP|MF_STRING, (UINT_PTR)hSubMenu, s_menuName.c_str() ) ;
  			}

			TestPosition = GetMenuPosition( &ParentMenu, s_menuName.c_str() ) ;
			SubMenu = ParentMenu.GetSubMenu( TestPosition ) ;

			if ( SubMenu->GetMenuItemCount() > 0 )
			{
				SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") ) ;
			}

			SetUserMenu(SubMenu, NextMenuID);

			CBCGPToolbarMenuButton  menubtn (0, 
				SubMenu->GetSafeHmenu() , -1, s_menuName.c_str());

			// 添加在help前或自定义位置
			if (s_menuPosition == -1)
			{
				pMenuBar->InsertButton ( menubtn, HelpPosition -1  );
			}
			else
			{
				pMenuBar->InsertButton ( menubtn, s_menuPosition  );
			}
		}


		// 创建命令响应窗口
		s_CommandWnd = new CCommandWnd ; 
		bReturn = s_CommandWnd->Create( NULL, _T(""), ChildID, CRect(-1,-1,-1,-1), CWnd::FromHandle(ParentWindow), ChildID ) ;

		pMenuBar->AdjustLayout();
		pMenuBar->AdjustSizeImmediate ();
		CWnd::FromHandle(ParentWindow)->DrawMenuBar() ;

		SubMenu->Detach();
		ParentMenu.Detach() ; 

		s_pMenuBar = pMenuBar;
	}

	return bReturn ; 
}

// 移除菜单
BOOL RemoveExtMenu()
{
	BOOL bReturn = TRUE ; 

	HMENU hMenu = s_pMenuBar->GetDefaultMenu();

	CMenu menu;
	menu.Attach(hMenu);

	if (menu.GetMenuItemCount() == -1)
	{
		AfxMessageBox("Menu Attach Faild.");
		return FALSE;
	}

	int pos = ::GetMenuPosition(&menu, s_menuName.c_str());

	if (pos != -1)
	{
		s_pMenuBar->RemoveButton(pos);
	}

	menu.Detach();

	s_pMenuBar->AdjustLayout();
	s_pMenuBar->AdjustSizeImmediate();
	AfxGetApp()->GetMainWnd()->DrawMenuBar();

	if (s_CommandWnd != NULL)
	{
		s_CommandWnd->DestroyWindow();
		delete s_CommandWnd;
		s_CommandWnd = NULL;
	}

	return bReturn ; 
}

// 得到事件ID,以备转发消息事件
UINT GetExtMenuItem( UINT Index )
{
	CommandToMessage::iterator iterIndex = s_CommandToMessage.find(Index);

	if (iterIndex == s_CommandToMessage.end())
	{
		return 0;
	}

	return iterIndex->second;
}

// 得到控件状态 Check
UINT GetExtMenuCheck( UINT Index )
{
	CommandToMessage::iterator iterIndex = s_CommandToMessage.find(Index);

	if (iterIndex == s_CommandToMessage.end())
	{
		return -1;
	}

	UINT id = iterIndex->second;

	if ( GetUserMenuCheck(id) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// 得到控件状态 Enable/Gray
UINT GetExtMenuEnable( UINT Index )
{
	CommandToMessage::iterator iterIndex = s_CommandToMessage.find(Index);

	if (iterIndex == s_CommandToMessage.end())
	{
		return -1;
	}

	UINT id = iterIndex->second;

	if ( GetUserMenuEnable(id) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
#endif