#ifndef __VGSDKUSERMENUMANAGER_H__
#define __VGSDKUSERMENUMANAGER_H__

#include "vgSDKDefinition.h"


//typedef std::map<UINT, UINT> 	VGSDK_EXPORT   CommandToMessage;


	/**
		@date 	2009/10/26  15:21	
		@author  LiuSS
	
		@brief 	
	
		@see    
	*/

namespace	vgSDK
{

	//----------------------------------------------------------------
	enum	VGSDK_EXPORT UserMenuType
	{
		USER_MENU_BRANCH,
		USER_MENU_LEAF,
		USER_MENU_SEPARATOR,
		USER_MENU_TYPE_COUNT
	};

	//----------------------------------------------------------------
	class VGSDK_EXPORT UserMenuItem;
	typedef std::vector<UserMenuItem>		VGSDK_EXPORT UserMenuItemVecL1;
	
	class VGSDK_EXPORT UserMenuItem
	{
	public:
		UserMenuItem( String name = "", 
			UINT id = 0,
			UserMenuType type = USER_MENU_LEAF );

		UserMenuItem(const UserMenuItem& item);

		~UserMenuItem(){}
	

	public:
		bool	hasSubItem();
		void	appendSubItem(UserMenuItem item);
		void	appendSubItem( String name = "", 
			UINT id = 0,
			UserMenuType type = USER_MENU_LEAF );

		UserMenuItemVecL1*	getSubItems();
		UserMenuItem	getSubItemByName(String leaf_name);
		UserMenuItem	getSubItemByID(UINT leaf_id);

		UserMenuItem&	operator=(const UserMenuItem& item);

	
	public:
		UINT&	getID();
		String&	getName();
		UserMenuType&	getType();


	protected:

		UserMenuItem	getSubItemByName(String leaf_name,
			UserMenuItemVecL1* pMenuItems);
		
		UserMenuItem	getSubItemByID(UINT leaf_id,
			UserMenuItemVecL1* pMenuItems);


	protected:
		UINT	_id;
		String	_name;
		UserMenuType	_type;

		UserMenuItemVecL1	_subItems;

	};// class UserMenuItem


	//----------------------------------------------------------------
	class VGSDK_EXPORT UserMenuManager
	{
	public:
		UserMenuManager(CMenu* SubMenu, UINT * NextMenuID,
			CommandToMessage* pCmdToMsg);
		
		~UserMenuManager()	{}


	public:
		void	appendSubItem(UserMenuItem item);

		virtual	void	initializeUserMenu() = 0;

		void	setUserMenu();


	protected:
		void	setUserMenu(UserMenuItemVecL1* pMenuItems,
			CMenu* pParentMenu);

		void	appendMenuActual(CMenu* pParentMenu, UINT * NextMenuID,
			int MenuID, string& menuName);

		CMenu*	appendMenuVirtual(CMenu* pParentMenu, string menuName);

		void	appendMenuSeparator(CMenu* pParentMenu);

	protected:
		UserMenuItem	_rootUserMenu;

		CMenu* _SubMenu;
		UINT * _NextMenuID;
		CommandToMessage*	_cmdToMsg;

	};// class UserMenuManager 

	//----------------------------------------------------------------
}// namespace vgSDK


	


#endif // end of __VGSDKUSERMENUMANAGER_H__