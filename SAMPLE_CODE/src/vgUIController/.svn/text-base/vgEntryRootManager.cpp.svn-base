#include <vgStableHeaders.h>

#include "vguicontroller/vgEntryRootManager.h"


//----------------------------------------------------------------
EntryRootManager::EntryRootManager()
{

}


//----------------------------------------------------------------
EntryRootManager::~EntryRootManager()
{

}


//----------------------------------------------------------------
HTREEITEM	EntryRootManager::getEntryRootByType( EDynamicEntryType entryType)
{
	int nType = (int)entryType;
	DynamicEntryRootMap::iterator itr =  _entryRootsDynamic.find(nType);

	if (itr != _entryRootsDynamic.end())
	{
		return itr->second;
	}
	else
	{
		assert(0);
		return NULL;
	}
}


//----------------------------------------------------------------
HTREEITEM	EntryRootManager::getEntryRootByType( EStaticEntryType entryType )
{
	int nType = (int)entryType;
	//DynamicEntryRootMap::iterator itr = find(_entryRootsDynamic.begin(), 
	//	_entryRootsDynamic.end(), nType);
	DynamicEntryRootMap::iterator itr = _entryRootsStatic.find(nType);
	
	if (itr != _entryRootsStatic.end())
	{
		return itr->second;
	}
	else
	{
		assert(0);
		return NULL;
	}
}


//----------------------------------------------------------------
void EntryRootManager::initializeEntryRoots()
{

}


//----------------------------------------------------------------
void EntryRootManager::appendEntryRootItem(EDynamicEntryType entryType, HTREEITEM item)
{
	int nType = (int)entryType;
	DynamicEntryRootMap::iterator itr =  _entryRootsDynamic.find(nType);

	if (itr == _entryRootsDynamic.end())
	{
		_entryRootsDynamic.insert( EntryRoot_Pair(nType, item) );
	}
	else
	{
		assert(0);
	}
}


//----------------------------------------------------------------
void EntryRootManager::appendEntryRootItem( EStaticEntryType entryType, HTREEITEM item )
{
	int nType = (int)entryType;
	StaticEntryRootMap::iterator itr = _entryRootsStatic.find(nType);
	
	if (itr == _entryRootsStatic.end())
	{
		_entryRootsStatic.insert( EntryRoot_Pair(nType, item) );
	}
	else
	{
		assert(0);
	}
}