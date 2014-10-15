/********************************************************************
*	Filename: 	DynamicItems.h 
*	Created:	1/22/2003
*	Class:		DynamicItems
*	Author:		David Excoffier [dexcoffier@yahoo.fr] - Copyright (c) 2001-2003
*				original code v1.0 was "Dynamic Items" by David Excoffier.
*	Improvments: Parts by Lionel Grenier [lionel.grenier@lebios.com]
*
* 			This code may be used in compiled form in any way you desire. This
* 			file may be redistributed unmodified by any means PROVIDING it is 
* 			not sold for profit without the authors written consent, and 
* 			providing that this notice and the authors name is included. If 
* 			the source code in  this file is used in any commercial application 
* 			then acknowledgement must be made to the author of this file 
* 			(in whatever form you wish).
*
* 			This file is provided "as is" with no expressed or implied warranty.
*
* 			Please use and enjoy. Please let me know of any bugs/mods/improvements 
* 			that you have found/implemented and I will fix/incorporate them into this
* 			file. 
*
*	purpose:	This class allows to have a menu with complete dynamic items
*		 based on a configuration file. Your menu can have sub-menus, items, separators, and icons. 
*
*	How To use it: 
*
*		Important: To modify the maximum numbers of items which can be managed, 
*			modify the last line in the file DynamicItems.cpp :
*			e.g., modify
*				int CDynamicItems::m_nbMaxItems = 10;
*			to
*				int CDynamicItems::m_nbMaxItems = 2500;
*			To be able to manage up to 2500 dynamic items at a time
*			(seems impossible to display them all on the screen but why not if you are paranoid...).
*			(But don't forget, you might be limited by the size of your screen, so ...)
*
*		1. In the header of the class that manages your main menu
*		declare
*			CDynamicItems	m_dynamic_menu;
*	
*		2. Now you have to map the call to the dynamic items to the 
*		  rarely used	ON_COMMAND_RANGE message (.cpp) by
*			BEGIN_MESSAGE_MAP(YourCWndClassName, CWnd)
*			//{{AFX_MSG_MAP(YourCWndClassName)
*
*			ON_COMMAND_RANGE( ID_POPUP_DynCmd01, ID_POPUP_DynCmd01 + CDynamicItems::GetNbMaxItems(), OnExecuteDynamicItems )
*			.................
*		
*		3. In the function where you init your object, 
*		insert:
*				m_dynamic_menu.readFromFile(youconfigfile path);
*
*
*		4. Now when you want to display the menu:
*			If your main menu is a Pop_up menu call
*				m_dynamic_menu.CreateDynamicPopupMenu(m_pPopup);
*					with m_pPopup a pointer to the main menu of your object where the
*					dynamic menu will be added
*			If your menu is a Menu bar call
*				m_dynamic_menu->add(DEFAULTDYNMENUPOS);
*					with DEFAULTDYNMENUPOS the position in the Menu Bar
*				to remove it form a Menu bar call
*				m_dynamic_menu->remove()
*
*		5. If you want to have check/uncheck item
*		call for example
*			m_dynamic_menu.switchItemState(ID_POPUP_DynCmd01-nPos);
*			to change the state of the nPos item
*
*
*		6. Config file:
*			The menu that will be displayed is created based on a text file that
*			describe your menu
*			We can have three (3) types of menu items:
*			- Simple Item
*				// the string to display in the menu
*				ITEM display_name
*					//extra info (optional)
*					COMMENT "some comment"
*					// the function allows to associate
*					// an operation to do  when
*					// the item is selected
*					// the string is case independant
*					// since the code parse it to be upper case
*					// Your main app should parse the function name
*					// in OnExecuteDynamicItems to know what to do with it
*					FUNCTION (A string)
*
*			- Separator item
*				SEPARATOR
*
*			- Popup (subMenu) item
*				// start the sub_menu section
*				BEGIN_BRANCH
*				// string to display as a submenu name
*				BRANCH_NAME subMenuName
*					//items
*					ITEM items1
*						COMMENT "some comment"
*						FUNCTION (A string)
*					
*					SEPARATOR
*					
*					BEGIN_BRANCH
*					// string to display as a subsubmenu name
*					BRANCH_NAME subsubMenuName
*						ITEM items2
*							COMMENT "some comment"
*							FUNCTION (A string)
*					END_BRANCH
*
*					ITEM items3
*						COMMENT "some comment"
*						FUNCTION (A string)
*				END_BRANCH
*				// end of the sub_menu section
*
*				So you can see that the submenu can have submenu, 
*				separator and items. You can build a tree in your menu.
*
*			The order in your text file (top to bottom) will be the order 
*			it is displayed in the dynamic menu
*
*
* History:
* ========
* Version 1.1 (01/22/2003):
*    Updated version with submenus and better items management.
*    Now it's a "real dynamic menu" ! 
*    Many thanks to Lionel Grenier [lionel.grenier@lebios.com] for enhancing parts of this code.
* 
*  Version 1.0 (05/17/2001):
*    First "public" version.
* 
*********************************************************************/

#if !defined(__DYNAMIC_ITEMS_H__)
#define __DYNAMIC_ITEMS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using std::ifstream;
using std::string;
using std::vector;



// version 1.1 : 
// Define a high unusual number to be sure it won't conflict to some id in
// the project... This is NOT the number max. of items managed !
#define ID_POPUP_DynCmd01	48000 

// keywords used in file...
#define	KEYWORD_IGNORE1			"//"
#define	KEYWORD_IGNORE2			"#"
#define KEYWORD_BEGIN_BRANCH	"BEGIN_BRANCH"
#define	KEYWORD_BRANCH_NAME		"BRANCH_NAME"
#define	KEYWORD_ITEM			"ITEM"
#define	KEYWORD_END_BRANCH		"END_BRANCH"
#define	KEYWORD_COMMENT			"COMMENT"
#define	KEYWORD_SEPARATOR		"SEPARATOR"
#define	KEYWORD_FUNCTION		"FUNCTION"
#define	KEYWORD_NONE			"NONE"

/////////////////////////////////////////////////////////////////////////////
// DynamicItems window

class CDynamicItems
{
public:
	// sub classe that handle a Menu Item information


	void stringStrip( std::string& str )
	{
		const std::string& delstr = " \t\r";

		str.erase(str.find_last_not_of(delstr)+1); // trim right

		str.erase(0, str.find_first_not_of(delstr)); // trim left
	}

	class CMenuItem
	{
	public:
		/// type of an item
		enum MENU_ITEM_TYPE
		{
			ITEM = 0,
			POPUP,
			SEPARATOR
		};
		
	public:
		// cstr
		CMenuItem()
			: m_type( ITEM )
			, m_comment("NONE")
			, m_name("NONE")
			, m_state(false)
			, m_position(-1)
			, m_function("NONE") { }
		
		virtual	void	clear() {}

		virtual CMenuItem* clone()
		{
			CMenuItem* newItem = new CMenuItem();
			newItem->setName(getName());
			newItem->setComment(getComment());
			newItem->setPosition(getPosition());
			newItem->setFunctionType(getFunctionType());
			newItem->setType( getType() );
			return newItem;
		}

		/// set/get the name to be display
		void  	setName(const std::string name) { m_name = name; }
		const std::string& getName() const	{ return m_name; }
		std::string getName()			{ return m_name; }
		
		/// set/get the comment of this item
		void  	setComment(const std::string comment) { m_comment = comment; }
		const std::string& getComment() const	{ return m_comment; }
		std::string getComment()		{ return m_comment; }
		
		/// set/get the check state of the item
		void	setState(bool b) 		{ m_state = b; }
		bool	getState()	const 		{ return m_state; }
		void	switchState() 			{ m_state = !m_state; }

		/// set/get the position of this item
		/// the position is an unique identifier that
		/// allow the Cwnd object that owns the menu
		/// to know which function to call on the ON_COMMAND message
		void	setPosition(int pos)  		{ m_position = pos; }
		int		getPosition()	const 		{ return m_position; }

		/// set/get the function id of this item
		/// this allows to perform specific function
		/// when the item is selected
		void	setFunctionType(const std::string func_type)  		{ m_function = func_type; }
		std::string		getFunctionType()	const { return m_function; }


		/// set/get the type of this item
		void	setType(MENU_ITEM_TYPE t) 	{ m_type = t; }
		MENU_ITEM_TYPE getType() 			{ return m_type; }
	
	protected:
		/// type of this item
		MENU_ITEM_TYPE	m_type;

		/// name to be displayed
		std::string		m_name;
		
		/// check state of the item
		bool			m_state;

		/// position of the item
		int				m_position;
		
		/// a comment (tooltip ?) associate with the item
		std::string		m_comment;

		/// id of function linked to this item
		/// list of functions is defined in the class that own
		/// and manage the dynamic menu
		std::string		m_function;
	};

	/// sub class that handle a popup item
	class CPopMenuItem: public CMenuItem
	{
	public:
		/// constructor
		CPopMenuItem()
			: CMenuItem()
		{
			// set the popup type
			m_type = POPUP;
		}
		
		/// destructor
		~CPopMenuItem()
		{
			clear();
		}
		
		/// delete all the items contain in this popup item
		void	clear()
		{
			std::vector< CMenuItem* >::iterator iter = m_items.begin();
			for ( ; iter != m_items.end(); ++iter )
			{
				(*iter)->clear();
				delete (*iter);
			}
			m_items.clear();
		}
		
		/// add a new menu Item to this popup item
		void	addItem(CMenuItem* item) { m_items.push_back(item); }
		
		/// how many items is in this popup item
		int		size() { return m_items.size(); }

		/// to get an item by calling item[idx]
		CMenuItem* operator[] (int pos)
		{
			ASSERT( pos < m_items.size());
			return m_items[pos];
		}
	
		virtual CMenuItem* clone()
		{
			CPopMenuItem* newItem = new CPopMenuItem();
			newItem->setName(getName());
			newItem->setComment(getComment());
			newItem->setPosition(getPosition());
			newItem->setFunctionType(getFunctionType());
			newItem->setType( getType() );

			for ( int i = 0 ; i < size() ; ++ i )
			{
				CMenuItem* itm = m_items[i];
				assert( itm != NULL );
				CMenuItem* copyitm = itm->clone();
				newItem->addItem( copyitm );
			}

			return newItem;
		}
	protected:
		/// vector of all items in this popup item
		std::vector<CMenuItem*>	m_items;
	};


// Operations
public:
	CDynamicItems();
	virtual ~CDynamicItems();

	/// setup functions
	void		updateDynamicItems(const char* pFileName);
	/// Read the file and Update the Dynamic Items in memory (do not modify menu)
	BOOL		readFromFile(const char* pFileName);

	BOOL  readFromString( const char* filecontent );


	/// Create the Popup Menu with the Dynamic Items present in memory
	/// this will be called by the CWnd object that own the menu and the dynamic menu object
	void		CreateDynamicPopupMenu(CMenu* &pSubMenu);

	/// Item management :
	/// Returns the Item text (displayed in the menu)
	std::string GetItemText(UINT nID);
	
	/// Returns the Item comment 
	std::string GetItemComment(UINT nID);

	/// Returns the Item function type 
	std::string GetItemFunctionType(UINT nID);

	/// change the check/uncheck state of an item
	void		switchItemState(UINT nID);

	// version 1.1 :
	static int	GetNbMaxItems(){ return m_nbMaxItems; }
	void		SetNbMaxItems(int nbMaxItems){ m_nbMaxItems = nbMaxItems; } 


	/// add this dynamic menu to the main menu
	/// at a specific postion
	// default pos is the first one
	bool		add(int insert_pos , const std::string& menuname );
	/// remove this dynamic menu form the main menu
	bool		remove();
	
	// clean our Menu
	void	clearMenu();

private:
	
	// My list of Dynamic Items
	CPopMenuItem	m_listeItems;



	// version 1.1 : 

	int		m_nItemPosition;

	// static member that count the number of elements in the menu.
	// This member MUST BE static to be used in the ON_COMMAND_RANGE of the CMainFrame...
	static	int		m_nbMaxItems;

private:
	
	// add a new item
	BOOL	addMenuItem(CPopMenuItem* menu, std::istream* i_file);
	
	// add a new branch/pop_up menu
	void	addDynamicPopupMenu(CMenu* pSubMenu, CPopMenuItem* menu_item);

	

#if 0
	// Add icon to an Item
	void	addIconItem(CMenu* &pSubMenu, UINT nIcon);
#endif

	// dump into Debug Out all items
	void	dumpMenu(CPopMenuItem* menu_item);

	// Finds an items from its number in the list and return a POPUP_ITEM.
	CMenuItem* FindItemInList(int nRank);
	CMenuItem* FindItemInList(CPopMenuItem* item, int nRank);
};

inline std::string
UpperCase (const std::string& s)
{
	std::string temp (s);
	/// we change all characters in our string
	/// to be uppercase
	for (int i=0; i<temp.length(); ++i)
		temp[i] = toupper (temp[i]);

	// return our transform string
	return temp;
}


/////////////////////////////////////////////////////////////////////////////

#endif // !defined(__DYNAMIC_ITEMS_H__)

