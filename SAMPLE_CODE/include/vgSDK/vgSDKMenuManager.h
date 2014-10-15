#ifndef __VGSDKMENUMANAGER_H__
#define __VGSDKMENUMANAGER_H__

#include "vgSDKDefinition.h"

#include <vgKernel/vgkStringVector.h>



	/**
		@date 	2009/10/23  20:21	
		@author  LiuSS
	
		@brief 	
	
		@see    
	*/


namespace	 vgSDK
{
	CommandToMessage	VGSDK_EXPORT 		s_CommandToMessage ;

	//----------------------------------------------------------------
	class	VGSDK_EXPORT MenuIDManager
	{
	public:
		typedef std::vector<UINT> MenuIDs;
		typedef std::pair<String, MenuIDs>					SubMenuIDsLevel1Pair;
		typedef std::vector<SubMenuIDsLevel1Pair>			SubMenuIDsLevel1;

		typedef std::pair<String, SubMenuIDsLevel1>		SubMenuIDsLevel2Pair;
		typedef std::vector<SubMenuIDsLevel2Pair>		SubMenuIDsLevel2;

	public:
		MenuIDManager();
		~MenuIDManager();

	public:
		SubMenuIDsLevel2*	getMenuIDs();

		void	initialize(SubMenuIDsLevel2* pIDs = NULL);

	protected:
		SubMenuIDsLevel2*	_menuIDs;

	};// class MenuIDManager

	typedef MenuIDManager::MenuIDs					VGSDK_EXPORT MenuIDs;
	typedef MenuIDManager::SubMenuIDsLevel1Pair	VGSDK_EXPORT SubMenuIDsLevel1Pair;
	typedef MenuIDManager::SubMenuIDsLevel1		VGSDK_EXPORT SubMenuIDsLevel1;
	typedef MenuIDManager::SubMenuIDsLevel2Pair	VGSDK_EXPORT SubMenuIDsLevel2Pair;
	typedef MenuIDManager::SubMenuIDsLevel2		VGSDK_EXPORT SubMenuIDsLevel2;

	//----------------------------------------------------------------
	class	 VGSDK_EXPORT MenuNameManager
	{
	public:
		typedef std::pair<String, vgKernel::StringVector>	SubMenuNamesLevel1Pair;
		typedef std::vector<SubMenuNamesLevel1Pair>			SubMenuNamesLevel1;

		typedef std::pair<String, SubMenuNamesLevel1>	SubMenuNamesLevel2Pair;
		typedef std::vector<SubMenuNamesLevel2Pair>		SubMenuNamesLevel2;

	public:
		MenuNameManager();
		~MenuNameManager();

	public:
		SubMenuNamesLevel2*	getMenuNames();

		void	initialize(SubMenuNamesLevel2*	pNames = NULL);

	protected:
		SubMenuNamesLevel2*	_menuNames;

	};// class MenuNameManager



	typedef MenuNameManager::SubMenuNamesLevel1Pair	 VGSDK_EXPORT SubMenuNamesLevel1Pair;
	typedef MenuNameManager::SubMenuNamesLevel1		VGSDK_EXPORT SubMenuNamesLevel1;
	typedef MenuNameManager::SubMenuNamesLevel2Pair VGSDK_EXPORT SubMenuNamesLevel2Pair;
	typedef MenuNameManager::SubMenuNamesLevel2		VGSDK_EXPORT SubMenuNamesLevel2;


	//----------------------------------------------------------------
	class VGSDK_EXPORT MenuAppendManager
	{
	public:
		MenuAppendManager(CMenu* SubMenu, UINT * NextMenuID);

		~MenuAppendManager();


	public:
		void	setUserMenu();

		void	initialize(SubMenuIDsLevel2* pIDs = NULL,
			SubMenuNamesLevel2*	pNames = NULL);


	protected:
		void	appendMenuActual(CMenu* SubMenu, UINT * NextMenuID,
			int MenuID, string& menuName);

		CMenu*	appendMenuVirtual(CMenu* SubMenu, string menuName);

		CMenu*	appendMenuBranch(CMenu* SubMenu, UINT * NextMenuID, 
			String menuNameParent,
			vgKernel::StringVector names,
			MenuIDs nBeginMenuID);

		void	appendMenuRootCameraView(CMenu* SubMenu, UINT * NextMenuID,
			String menuNameParent,
			SubMenuNamesLevel1 menuNamesSub, 
			SubMenuIDsLevel1 firstIDs);

	protected:
		CMenu* _SubMenu;
		UINT * _NextMenuID;

		MenuNameManager	_menuNames;
		MenuIDManager		_menuIDs;

	};// class MenuAppendManager

	//----------------------------------------------------------------
}// namespace vgSDK


	


#endif // end of __VGSDKMENUMANAGER_H__