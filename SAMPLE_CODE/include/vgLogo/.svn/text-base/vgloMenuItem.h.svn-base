



#ifndef __VGUSERMENUMANAGER_H__
#define __VGUSERMENUMANAGER_H__


#include <vgKernel/vgkStringVector.h>
#include <vgLogo/vgloLogoHandle.h>

	/**
		@date 	2009/10/26  15:21	
		@author  LiuSS
	
		@brief 	
	
		@see    
	*/


namespace	vgLogo
{

	using namespace std;
	//----------------------------------------------------------------
	enum	MenuItemType
	{
		USER_MENU_BRANCH,
		USER_MENU_LEAF,
		USER_MENU_TYPE_COUNT
	};


	//----------------------------------------------------------------
	class MenuItem;
	typedef std::vector<MenuItem*>		        MenuItemVecL1;
	typedef std::vector<MenuItem*>::iterator    MenuItemVecL1Itr;
	
	class  VGL_EXPORT  MenuItem : public LogoHandle
	{
	public:
		MenuItem( String name = "", UINT id = 0, 
			MenuItemType type = USER_MENU_BRANCH, MenuItem* pParent = NULL );

		MenuItem(const MenuItem& item);

		virtual ~MenuItem();
	

	public:
		bool	hasSubItem();
		void	appendSubItem(MenuItem* item);
		void	appendSubItem( String name = "", UINT id = 0,
			MenuItemType type = USER_MENU_LEAF, MenuItem* pParent = NULL );

		MenuItemVecL1*	getSubItems();
		MenuItem*	getSubItemByName(String leaf_name);
		MenuItem*	getSubItemByID(UINT leaf_id);

		MenuItem&	operator=(const MenuItem& item);

	
	public:
		UINT&	getID();
		String&	getName();
		MenuItemType&	getType();
		MenuItem* getParentPtr();
		void setParentPtr( MenuItem* parent );


	protected:

		MenuItem*	getSubItemByName(String leaf_name,
			MenuItemVecL1* pMenuItems);
		
		MenuItem*	getSubItemByID(UINT leaf_id,
			MenuItemVecL1* pMenuItems);
		
	public:

		//由父类LogoHandle继承而来
		virtual void render();
		virtual void loadTexture( vgKernel::StringVector fileNames );
		virtual void unloadData();
		
		//子类独有接口
		bool  textPointInRect( CPoint point );

		void setCurrentTexID( bool bState )
		{
			m_currentTexID = ( bState == true ) ? 1 : 0;
		}

		bool isMouseInLogo()
		{
			return _bMouseOn;
		}
		
		void setMouseInLogo( bool bState )
		{
			_bMouseOn = bState;
		}

	protected:
		UINT	        _id;
		String	        _name;
		MenuItemType	_type;
		
		MenuItemVecL1	_subItems;

		MenuItem*       _pParent;

		bool            _bMouseOn;

	};// class MenuItem

	//----------------------------------------------------------------
}// namespace vgSDK


	


#endif // end of __VGSDKUSERMENUMANAGER_H__