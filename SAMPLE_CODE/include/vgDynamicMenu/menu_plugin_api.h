
// 插件式构架Menu Api，供exe和dll使用
// 定义 DYNAMIC_MENU_EXEC_MODULE 宏为exe使用
// 其余部分为 dll plugin 使用

#ifndef __MENU_PLUGIN_API_H__
#define __MENU_PLUGIN_API_H__

#include <string>

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#include <BCGPMenuBar.h>
#include <BCGPToolbarButton.h>
#include <BCGPToolbarMenuButton.h>
#include <BCGPToolBar.h>

using std::string;

#ifdef DYNAMIC_MENU_EXEC_MODULE
	// exe 动态菜单接口
	// exe 调用 dll 按隐式约定在内部实现的函数
	BOOL InstallExtMenu( HMODULE Module, HWND ParentWindow, CBCGPMenuBar* pMenuBar/*HMENU hMenu*/, DWORD ChildID, UINT * NextMenuID ) ;
	BOOL RemoveExtMenu( HMODULE Module ) ;

	BOOL InstallRightExtMenu(HMODULE Module, HWND ParentWindow, CMenu* pRightMenu, DWORD ChildID, UINT * NextMenuID);
	BOOL GetRightExtMenuItem(HMODULE Module, UINT Index, UINT * Item );
	UINT GetRightExtMenuCheck( HMODULE Module, UINT Index );
	UINT GetRightExtMenuEnable( HMODULE Module, UINT Index );

	BOOL GetExtMenuItemCount( HMODULE Module, UINT * Count ) ;
	BOOL GetExtMenuItem( HMODULE Module, UINT Index, UINT * Item ) ;
	UINT GetExtMenuCheck( HMODULE Module, UINT Index );
	UINT GetExtMenuEnable( HMODULE Module, UINT Index );

	// Simplify the names 
    #define RINSTALL _T("InstallRightExtMenu")
    #define RGETITEM _T("GetRightExtMenuItem")
    #define RGETCHECK _T("GetRightExtMenuCheck")
    #define RGETENABLE _T("GetRightExtMenuEnable")

	#define INSTALL _T("InstallExtMenu")
	#define REMOVE _T("RemoveExtMenu")
	#define GETCOUNT _T("GetExtMenuItemCount")
	#define GETITEM _T("GetExtMenuItem")
	#define GETCHECK _T("GetExtMenuCheck")
	#define GETENABLE _T("GetExtMenuEnable")

	// Set up the function signatures.
	typedef BOOL ( *fn_InstallExtMenu)( HWND, CBCGPMenuBar*, DWORD, UINT* ) ;
	typedef BOOL ( *fn_RemoveExtMenu)( ) ;

	typedef BOOL ( *fn_RightInstallExtMenu)(HWND, CMenu*, DWORD, UINT*);
	typedef UINT (*fn_getRightExtMenuItem)( UINT);
	typedef UINT ( *fn_GetRightExtMenuEnable)( UINT ) ;
	typedef UINT ( *fn_GetRightExtMenuCheck)( UINT );

	typedef UINT ( *fn_GetExtMenuItemCount)( ) ;
	typedef UINT ( *fn_GetExtMenuItem)( UINT ) ;
	typedef UINT ( *fn_GetExtMenuEnable)( UINT ) ;
	typedef UINT ( *fn_GetExtMenuCheck)( UINT );

	// All interfaces take an HMODULE argument, the HMODULE argument allows us 
	// to use other DLLs which have the same interface.

	// All functions here return a BOOL regardless of the what the contained function does
	// so it can report whether the access to the function is supported.

	BOOL InstallExtMenu( HMODULE Module, HWND ParentWindow, CBCGPMenuBar* pMenuBar/*HMENU hMenu*/, DWORD ChildID, UINT * NextMenuID ) 
	{
		if ( Module != NULL && NextMenuID != NULL )
		{
			fn_InstallExtMenu fn = (fn_InstallExtMenu)GetProcAddress( Module, INSTALL ) ;
			if ( fn != NULL )
			{
				return fn( ParentWindow, pMenuBar/* hMenu*/, ChildID, NextMenuID ) ;
			}
		}
		return FALSE ;
	}
	
	BOOL RemoveExtMenu( HMODULE Module ) 
	{
		if ( Module != NULL ) 
		{
			fn_RemoveExtMenu fn = (fn_RemoveExtMenu)GetProcAddress( Module, REMOVE ) ;
			if ( fn != NULL )
			{
				return fn() ;
			}
		}
		return FALSE ;
	}

	BOOL InstallRightExtMenu(HMODULE Module, HWND ParentWindow, CMenu* pRightMenu, DWORD ChildID, UINT * NextMenuID)
	{
		if (Module != NULL && NextMenuID != NULL)
		{
			fn_RightInstallExtMenu fn = (fn_RightInstallExtMenu)GetProcAddress(Module, RINSTALL);

			if (fn != NULL)
			{
				return fn( ParentWindow,  pRightMenu, ChildID, NextMenuID ) ;
			}
		}
		return FALSE;
	}

	BOOL GetExtMenuItemCount( HMODULE Module, UINT * Count ) 
	{
		BOOL ReturnVal = FALSE ;
		if ( Module != NULL && Count != NULL )
		{
			fn_GetExtMenuItemCount fn = (fn_GetExtMenuItemCount)GetProcAddress( Module, GETCOUNT ) ;
			if ( fn != NULL )
			{
				*Count = fn(  ) ;
				ReturnVal = TRUE ;
			}
		}
		return ReturnVal ;
	}

	BOOL GetExtMenuItem( HMODULE Module, UINT Index, UINT * Item ) 
	{
		BOOL ReturnVal = FALSE ;
		if ( Module != NULL && Item != NULL )
		{
			fn_GetExtMenuItem fn = (fn_GetExtMenuItem)GetProcAddress( Module, GETITEM ) ;
			if ( fn != NULL )
			{
				*Item = fn( Index ) ;
				ReturnVal = ( *Item > 0 ) ;
			}
		}
		return ReturnVal ;
	}
	
	UINT GetExtMenuEnable( HMODULE Module, UINT Index )
	{
		UINT ReturnVal = -1;
		if ( Module != NULL )
		{
			fn_GetExtMenuEnable fn = (fn_GetExtMenuEnable)GetProcAddress( Module, GETENABLE );
			if ( fn != NULL )
			{
				ReturnVal = fn( Index );
			}
		}

		return ReturnVal;
	}

	UINT GetExtMenuCheck( HMODULE Module, UINT Index )
	{
		UINT ReturnVal = -1;

		if ( Module != NULL )
		{
			fn_GetExtMenuCheck fn = (fn_GetExtMenuCheck)GetProcAddress( Module, GETCHECK );
			if ( fn != NULL)
			{
				ReturnVal = fn( Index );
			}
		}

		return ReturnVal;
	}

#else

	// DLL 动态菜单接口
	extern "C" _declspec(dllexport) BOOL InstallExtMenu( HWND ParentWindow, CBCGPMenuBar* pMenuBar, DWORD ChildID, UINT * NextMenuID );
	extern "C" _declspec(dllexport) BOOL RemoveExtMenu();
	extern "C" _declspec(dllexport) BOOL InstallRightExtMenu(HWND ParentWindow, CMenu* RightMenu, DWORD ChildID, UINT * NextMenuID);
	extern "C" _declspec(dllexport) UINT GetExtMenuItem( UINT Index );
	extern "C" _declspec(dllexport) UINT GetExtMenuEnable ( UINT Index );
	extern "C" _declspec(dllexport) UINT GetExtMenuCheck ( UINT Index );

	// DLL 动态菜单工具函数
	#define MENU_POSITION_ERR (UINT)-1 

	UINT GetMenuPosition( CMenu * Menu, LPCTSTR MenuName )
	{
		UINT uReturn = MENU_POSITION_ERR ;
		CString strMenuName( MenuName ) ;
		CString strCompare ; 
		MENUITEMINFO  MenuItemInfo ; 
		ZeroMemory( &MenuItemInfo, sizeof(MenuItemInfo) ) ;
		MenuItemInfo.cbSize= sizeof(MenuItemInfo) ;
		MenuItemInfo.fMask = MIIM_DATA|MIIM_TYPE ; // use MIIM_STRING for WINVER > 0x500
		UINT Count = Menu->GetMenuItemCount() ;
		for ( UINT i = 0 ; i < Count ; i++ ) 
		{
			MenuItemInfo.cch = strMenuName.GetLength() + 2 ; // add 1 for '&' and 1 for NULL termination!
			MenuItemInfo.dwTypeData = strCompare.GetBuffer(MenuItemInfo.cch) ; // allocate the buffer
			Menu->GetMenuItemInfo( i, &MenuItemInfo, TRUE ) ;
			strCompare.ReleaseBuffer() ;
/*			strCompare.Remove( _T('&') ) ;*/
			if ( strMenuName.Compare( strCompare ) == 0 )
		 {
			 uReturn = i ; 
			 break ;
		 }
		}

		return uReturn ; 
	}

#endif

#endif // __MENU_PLUGIN_API_H__