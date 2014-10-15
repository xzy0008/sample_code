/////////////////////////////////////////////////////////////////////////////
// CDynamicItems.cpp : implementation file
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
*	purpose:	This class allows to have a menu complete dynamic items
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
*				m_dynamic_menu->add();
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

//#include "StdAfx.h"
#include "vgStableHeaders.h"
#include "resource.h"
#include "MainFrm.h"
#include "DynamicItems.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynamicItems

CDynamicItems::CDynamicItems()
{
	m_nItemPosition = -1;

}

CDynamicItems::~CDynamicItems()
{
	// clear our menu components
	clearMenu();
}


void CDynamicItems::updateDynamicItems(const char* pFileName)
{
	// This method must be called each time we want to update dynamic items in memory 
	// (not directly in menu)...

	TRACE0("CDynamicItems::updateDynamicItems: Loading file and chirping data in memory\n");
	
	if (!readFromFile(pFileName))
		TRACE0("Unable to download file !\n");

}

/////////////////////////////////////////////////////////////////////////////
// PUBLIC OPERATION
BOOL CDynamicItems::readFromFile(const char* pFileName)
{

#if 0
	std::string content;

	std::fstream file;
	file.open( pFileName , std::ios::_Nocreate | std::ios::binary );
	if ( file.fail() )
	{
		assert(0);
	}

	file.seekg(0,   std::ios::end);       
	streampos   ps   =   file.tellg();

	long filesize = ps;

	char* buf = new char[ filesize ];

	file.seekg( 0 , std::ios::beg );

	file.read( buf , filesize );

	return readFromString( buf );
#endif


	


	TRACE0("CDynamicItems::readFromFile: Loading file \n");

	// Loads items from a file
	// return TRUE if file loaded successfully
	// return FALSE if file not loaded, or empty
	BOOL	bRet = FALSE;


	CPopMenuItem* tmpitem = new CPopMenuItem();
	int backitempos = m_nItemPosition;
	
	ifstream* i_file = NULL;
	i_file = new ifstream (pFileName, std::ios::_Nocreate | std::ios::binary);


	if (*i_file)
	{
		// Read all lines
		while (i_file->eof()==0)
		{
			addMenuItem(tmpitem, i_file);
		}
		
		//#ifdef _DEBUG
		//	// dump our menu struct into debug out
		//	dumpMenu(&m_listeItems);
		//#endif

		bRet = TRUE;
	}
	
	delete i_file;
	

	if ( bRet == TRUE )
	{
		m_listeItems.addItem( tmpitem );
	}
	else
	{
		delete tmpitem;
		m_nItemPosition = backitempos;
	}

	return bRet;
}
BOOL CDynamicItems::readFromString( const char* filecontent )
{
	std::istringstream *i_file = new std::istringstream( filecontent );

	// Loads items from a file
	// return TRUE if file loaded successfully
	// return FALSE if file not loaded, or empty
	BOOL	bRet = FALSE;

	// init our Item list
	//clearMenu();

	CPopMenuItem* tmpitem = new CPopMenuItem();
	int backitempos = m_nItemPosition;

	if (*i_file)
	{
		// Read all lines
		while (i_file->eof()==0)
		{
			addMenuItem(tmpitem, i_file);
		}

		//#ifdef _DEBUG
		//	// dump our menu struct into debug out
		//	dumpMenu(&m_listeItems);
		//#endif

		bRet = TRUE;
	}

	delete i_file;

	if ( bRet == TRUE )
	{
		m_listeItems.addItem( tmpitem );
	}
	else
	{
		delete tmpitem;
		m_nItemPosition = backitempos;
	}

	return bRet;
}


/////////////////////////////////////////////////////////////////////////////
// PUBLIC OPERATION
void CDynamicItems::CreateDynamicPopupMenu(CMenu* &pSubMenu)
{
	// Here adds Dynamic item to the Popup menu
	TRACE0("CDynamicItems::CreateDynamicPopupMenu: Update static Popup Menu with Dynamic Items\n");
	//if ( _tempItems.size() == 0 )
	//{
	assert( m_listeItems.size() != 0 );

	addDynamicPopupMenu( pSubMenu , 
		(CPopMenuItem*)m_listeItems[ m_listeItems.size() - 1] );
	//}
	//else
	//{
	//	addDynamicPopupMenu(pSubMenu, &_tempItems);
	//	_tempItems.clear();
	//}
}




std::string  CDynamicItems::GetItemText(UINT nID)
{
	// Returns the Item text (displayed in the menu)
	// Retrieve the correct index in my list
	string	strItemName="";

	CMenuItem* item = FindItemInList(nID);
	if ( item )
		strItemName = item->getName();

	if (strItemName=="")
	{
		int nRank = nID - ID_POPUP_DynCmd01;

		CMenuItem* findres = FindItemInList(nRank);

		if ( findres == NULL )
		{
			return "";
		}

		strItemName = findres->getName();
	}

	return strItemName;
}

std::string  CDynamicItems::GetItemComment(UINT nID)
{
	// Returns the Item text (displayed in the menu)
	// Retrieve the correct index in my list
	string	strItemComment="";
	CMenuItem* item = FindItemInList(nID);
	if ( item )
		strItemComment = item->getComment();

	if (strItemComment=="")
	{
		int nRank = nID - ID_POPUP_DynCmd01;
		CMenuItem* findres = FindItemInList(nRank);
		if ( findres == NULL )
		{
			return "";
		}

		strItemComment = findres->getComment();
	}


	return strItemComment;
}

std::string  CDynamicItems::GetItemFunctionType(UINT nID)
{



	string	strItemFunction="";
	CMenuItem* item = FindItemInList(nID);
	if ( item )
		strItemFunction = item->getFunctionType();

	if (strItemFunction=="")
	{
		int nRank = nID - ID_POPUP_DynCmd01;
		CMenuItem* findres = FindItemInList(nRank);
		if ( findres == NULL )
		{
			return "";
		}

		strItemFunction = findres->getFunctionType();
	}


	return strItemFunction;
}


/////////////////////////////////////////////////////////////////////////////
// switch the check state of an item
void CDynamicItems::switchItemState(UINT nID)
{
	// Returns the Item text (displayed in the menu)
	// Retrieve the correct index in my list
	CMenuItem* item =  FindItemInList(nID);
	item->switchState();
}


//////////////////////////////////////////////////////////////////////////////
// PRIVATE PART
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// PRIVATE: Add dynamic popup menu to the system tray
void CDynamicItems::addDynamicPopupMenu(CMenu* pSubMenu, 
										CPopMenuItem* menu_item)
{
	// Here adds Dynamic item to the Popup menu
	TRACE0("CDynamicItems::addDynamicPopupMenu: Update static Popup Menu with Dynamic Items\n");
	
	if (menu_item->size()>0)
	{
		CMenuItem* PopupCurrentItem;
	
		for (int i=menu_item->size()-1; i >= 0; i--)
		{
			//Add Item dynamically
			PopupCurrentItem = (*menu_item)[i];
		

			switch ( PopupCurrentItem->getType() )
			{
			case CMenuItem::POPUP:
				{
					CMenu* menu = new CMenu();
					menu->CreatePopupMenu();
					addDynamicPopupMenu(menu, (CPopMenuItem*)(PopupCurrentItem));
					pSubMenu->InsertMenu( 0, MF_BYPOSITION | MF_POPUP, (UINT)menu->GetSafeHmenu(), PopupCurrentItem->getName().c_str() );
					//delete menu;
				}
				break;
				
			case CMenuItem::ITEM:
				{
					// Add Text
					pSubMenu->InsertMenu( 0, MF_BYPOSITION | MF_POPUP, ID_POPUP_DynCmd01 + PopupCurrentItem->getPosition(), PopupCurrentItem->getName().c_str() );
					
					if (PopupCurrentItem->getState())
						pSubMenu->CheckMenuItem(ID_POPUP_DynCmd01 + PopupCurrentItem->getPosition(), MF_CHECKED);
					
					//Here you can add your own icon associated to the dynamic item if you want
					// The following code is only an dummy example
					
					// Get the first letter of the item
					//CString strFirstChar;
					//strFirstChar = PopupCurrentItem->getName()[0];
					//strFirstChar.MakeUpper();
					
					//if (strFirstChar>="A" && strFirstChar<"I")
					//	addIconItem(pSubMenu, IDBMP_GREEN);
					//if (strFirstChar>="I" && strFirstChar <"Q")
					//	addIconItem(pSubMenu, IDBMP_ORANGE);
					//if (strFirstChar>="Q" && strFirstChar <="Z")
					//	addIconItem(pSubMenu, IDBMP_RED);
					
					pSubMenu->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED );
				}
				break;

			case CMenuItem::SEPARATOR:
				/// we insert a separator
				pSubMenu->InsertMenu (0, MF_BYPOSITION | MF_SEPARATOR);
				break;

			}
		}
	}
}



//////////////////////////////////////////////////////////////////////////////
// PRIVATE: Add Icon to an item of the menu
#if 0
void CDynamicItems::addIconItem(CMenu* &pSubMenu, UINT nIcon)
{
	// Add an icon to an Item in my Popup Menu
	static CBitmap cbmpRed,cbmpOrange, cbmpGreen;

	if ( cbmpRed.m_hObject==0 ) 
	{	// Loads bitmaps only once
		cbmpRed.LoadBitmap( IDBMP_RED );
		cbmpOrange.LoadBitmap( IDBMP_ORANGE );
		cbmpGreen.LoadBitmap( IDBMP_GREEN );
	}

	switch (nIcon)
	{
		case IDBMP_RED: pSubMenu->SetMenuItemBitmaps( 0, MF_BYPOSITION, &cbmpRed, &cbmpRed ); break;
		case IDBMP_ORANGE: pSubMenu->SetMenuItemBitmaps( 0, MF_BYPOSITION, &cbmpOrange, &cbmpOrange ); break;
		case IDBMP_GREEN: pSubMenu->SetMenuItemBitmaps( 0, MF_BYPOSITION, &cbmpGreen, &cbmpGreen ); break;
		default: break;
	}
}
#endif


/////////////////////////////////////////////////////////////////////////////
// PRIVATE: Add an item to the menu
BOOL CDynamicItems::addMenuItem(CPopMenuItem* menu, std::istream* i_file)
{
	char buf[1024];
	if( i_file->getline (buf, 1024) )
	{
		string line (buf);
	
		// comments line
		if ( line.find(KEYWORD_IGNORE1) != std::string::npos  || line.find(KEYWORD_IGNORE2) != std::string::npos)
			return TRUE;

		// Separator Item token
		if ( line.find(KEYWORD_SEPARATOR) != std::string::npos )
		{
			CMenuItem* newItem = new CMenuItem();
			newItem->setType(CMenuItem::SEPARATOR);
			
			// Adds the item in List
			menu->addItem(newItem);

			return TRUE;
		}
	
		// Branch Menu token
		if ( line.find(KEYWORD_BEGIN_BRANCH) != std::string::npos )
		{
			if( i_file->getline (buf, 1024) )
			{
				string line (buf);

				CPopMenuItem* pop_menu = new CPopMenuItem();
				if ( line.find(KEYWORD_BRANCH_NAME) != std::string::npos )
				{
					//extract the pop_up name
					std::string strBranchName=KEYWORD_BRANCH_NAME;

					std::string name = line.substr(line.find(KEYWORD_BRANCH_NAME)+strBranchName.size()+1, line.find("\n")-1);
					//name = name.substr(0,name.size()-1);
					pop_menu->setName(name);
				}
				
				while ( addMenuItem(pop_menu, i_file) )
				{ /** nothing to do here **/ }
				
				menu->addItem(pop_menu);
			}
			return TRUE;
		}
		
		// End branch Menu token
		if ( line.find(KEYWORD_END_BRANCH) != std::string::npos )
		{
			return FALSE;
		}


		//Menu Item token
		if ( line.find(KEYWORD_ITEM) != std::string::npos )
		{
			std::string name	= KEYWORD_NONE;
			std::string comment = KEYWORD_NONE;
			std::string function_type = KEYWORD_NONE;
			int position = -1;

			stringStrip( line );

			//extract the pop_up name
			int pos = line.find( " " )+1;
			line = line.substr(pos, line.size());
			
			// find the name
			name = line.substr(0, line.size());
		

			// find the comment
			i_file->getline (buf, 1024);
			line = buf;
			if ( line.find(KEYWORD_COMMENT) != std::string::npos )
			{
				std::string	strComment=KEYWORD_COMMENT;
				int pos = line.find(KEYWORD_COMMENT)+strComment.size()+1;
				line = line.substr(pos, line.size());
				comment = line.substr(0, line.size());

				i_file->getline (buf, 1024);
				line = buf;
			}
			

			if ( line.find(KEYWORD_FUNCTION) != std::string::npos )
			{
				std::string	strFunc=KEYWORD_FUNCTION;
				int pos = line.find(KEYWORD_FUNCTION)+strFunc.size()+1;
				line = line.substr(pos, line.size());
				function_type = line.substr(0, line.size());

				// we want only uppercase string
				//function_type = UpperCase(function_type);
			}
			
			// Automatic positionning :
			position = ++m_nItemPosition;

			// create and add our menu to our list
			CMenuItem* newItem = new CMenuItem();
			newItem->setName(name);
			newItem->setComment(comment);
			newItem->setPosition(position);
			newItem->setFunctionType(function_type);
			
			// Adds the item in List
			menu->addItem(newItem);

			return TRUE;
		}

		return TRUE;
	}
	return FALSE;
	
}



/////////////////////////////////////////////////////////////////////////////
// PRIVATE: Cleans the menu item list
void CDynamicItems::clearMenu()
{
	m_listeItems.clear();
	m_nItemPosition = -1;
}

/////////////////////////////////////////////////////////////////////////////
// Dumps the menu in the debug window (DEBUG Mode only)
void CDynamicItems::dumpMenu(CPopMenuItem* menu_item)
{
	if (menu_item->size()>0)
	{
		CMenuItem* PopupCurrentItem;
	
		for (int i=0; i < menu_item->size(); ++i)
		{
			//Add Item dynamically
			PopupCurrentItem = (*menu_item)[i];
			
			switch ( PopupCurrentItem->getType() )
			{
			case CMenuItem::POPUP:
				{
					TRACE("POPUP NAME %s\n", PopupCurrentItem->getName().c_str());
					dumpMenu((CPopMenuItem*)(PopupCurrentItem));
				}
				break;
				
			case CMenuItem::ITEM:
				{
					TRACE("NAME %s, COMMENT %s, POS %i\n", PopupCurrentItem->getName().c_str(),
											PopupCurrentItem->getComment().c_str(),
											PopupCurrentItem->getPosition());
				}
				break;

			case CMenuItem::SEPARATOR:
				TRACE("SEPARATOR\n");
				break;
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// PRIVATE: Finds an items from its number in the list and return a POPUP_ITEM.
CDynamicItems::CMenuItem* CDynamicItems::FindItemInList(int nRank)
{
	CMenuItem* newItem;
	
	for (int i=0; i<m_listeItems.size(); ++i)
	{
		if ( m_listeItems[i]->getPosition() == nRank)
			return m_listeItems[i];
		else
		{
			switch ( m_listeItems[i]->getType() )
			{
				// do a recursive search for pop_up item
				case CMenuItem::POPUP:
					{
						newItem = FindItemInList((CPopMenuItem*)m_listeItems[i], nRank);
			
						if ( newItem != NULL )
							return newItem;
					}
					break;
				
				case CMenuItem::ITEM:
				case CMenuItem::SEPARATOR:
					break;
			}
		}
	}
		
	return NULL;

}

/////////////////////////////////////////////////////////////////////////////
// PRIVATE: Finds an items from its number in the list and return a POPUP_ITEM.
CDynamicItems::CMenuItem* CDynamicItems::FindItemInList(
	CPopMenuItem* item, int nRank)
{
	CMenuItem* newItem;
	
	for (int i=0; i<item->size(); ++i)
	{
		if ( (*item)[i]->getPosition() == nRank)
			return (*item)[i];
		else
		{
			switch ( (*item)[i]->getType() )
			{
				// do a recursive search for pop_up item
				case CMenuItem::POPUP:
					{
						newItem = FindItemInList((CPopMenuItem*)(*item)[i], nRank);
			
						if ( newItem != NULL )
							return newItem;
					}
					break;
				
				case CMenuItem::ITEM:
				case CMenuItem::SEPARATOR:
					break;

			}
		}
	}

	return NULL;
}

///	this function loads our dynamic menu
//	and inserts it into the current menu at a specified position 
bool CDynamicItems::add(int insert_pos , const std::string& menuname )
{
	if ( m_listeItems.size() == 0)
		return false;

	/// get the top-level menu
	CWnd *wnd = AfxGetMainWnd();
	if (!wnd)
		return false;

	//------------------------------------------
	CMainFrame* mainfrm = ( CMainFrame* )wnd;
	CBCGPMenuBar* menubar = &mainfrm->m_wndMenuBar;

	/// okay, load the menu from a resource
	CMenu* dynamic_menu = new CMenu;
	dynamic_menu->LoadMenu (IDR_DYNAMIC_MENU);

	//dynamic_menu->

	CMenu *pSubMenu = dynamic_menu;
	if (!pSubMenu)
	{
		assert(0);
		return false;
	}

	
	//// we had all our dynamic item to this menu
	CreateDynamicPopupMenu(pSubMenu);



	// we remove our dummy item
	pSubMenu->RemoveMenu (pSubMenu->GetMenuItemCount()-1, MF_BYPOSITION);

	CBCGPToolbarMenuButton  menubtn (0, 
		dynamic_menu->GetSafeHmenu() , -1, _T ( menuname.c_str() ));

	menubar->InsertButton ( menubtn, insert_pos );

	menubar->AdjustLayout();
	menubar->AdjustSizeImmediate ();

	/// redraw the menu bar
	wnd->DrawMenuBar();

	return true;
}


/// helper function:
///	this function deletes a submenu from a given position
bool CDynamicItems::remove()
{
	if ( m_listeItems.size() == 0)
		return false;


	/// get the top-level menu
	CWnd *wnd = AfxGetMainWnd();
	if (!wnd)
		return false;

	CMenu *menu = wnd->GetMenu();
	if (!menu)
		return false;

	/// okay, load the menu from a resource
	CMenu dynamic_menu;
	dynamic_menu.LoadMenu (IDR_DYNAMIC_MENU);

	/// get the name of the submenu we want to remove
	CString menu_name;
	dynamic_menu.GetMenuString (0, menu_name, MF_BYPOSITION);

	/// search through the current items and remove the appropriate one
	int count = menu->GetMenuItemCount();
	for (int j=0; j<count; ++j)
	{
		CString temp;
		menu->GetMenuString (j, temp, MF_BYPOSITION);
		if (temp == menu_name)
		{
			menu->RemoveMenu (j, MF_BYPOSITION);
			break;
		}
	}

	/// now, redraw the menu bar
	wnd->DrawMenuBar();

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Version 1.1:
// Default member init. which defines the max numbers of dynamic items in the menu
int CDynamicItems::m_nbMaxItems = 200;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////