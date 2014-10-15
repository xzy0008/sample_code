
#include <vgStableHeaders.h>

#include "vgGroupNodeManager.h"


//----------------------------------------------------------------
namespace	vgGroup
{

	//----------------------------------------------------------------
	GroupNodeItem::GroupNodeItem( String name/* = ""*/, 
		GroupNodeItemPtr pParentNode/* = NULL*/,
		UINT id/* = 0*/, 
		GroupNodeType type/* = GROUP_NODE_LEAF*/
		)
		:_id(id)
		,_name(name)
		,_type(type)
		,_path(name)
		,_pParentNode(pParentNode)
		,_countLeaf(0)
		,_countBranch(0)
	{
		if ( !isLeafItem() && pParentNode)
		{
			_path = pParentNode->getPath() + _path + '\\';
		}
	}

	//----------------------------------------------------------------
	GroupNodeItem::GroupNodeItem(const GroupNodeItem& item )
	{
		*this = item;
	}
	//----------------------------------------------------------------
	void GroupNodeItem::appendSubItem( GroupNodeItem& item )
	{
		_subItems.push_back(item);
		
		if ( item.isLeafItem() )
		{
			_countLeaf ++;
		} 
		else
		{
			_countBranch ++;

			_countBranch	+= item._countBranch;
			_countLeaf		+= item._countLeaf;
		}
	}

	//----------------------------------------------------------------
	void GroupNodeItem::appendSubItem( String name/* = ""*/, 
		UINT id/* = 0*/, 
		GroupNodeType type/* = GROUP_NODE_LEAF*/
		)
	{
		appendSubItem( GroupNodeItem(name,  this, id, type) );
	}
	//----------------------------------------------------------------
	bool GroupNodeItem::hasSubItem()
	{
		//return !_subItems.empty();
		return GROUP_NODE_BRANCH == _type && !_subItems.empty();
	}

	//----------------------------------------------------------------
	GroupNodeItem& GroupNodeItem::operator=( const GroupNodeItem& item )
	{
		_type		= item._type;
		_id			= item._id;
		_name		= item._name;

		_subItems	= item._subItems;

		_countLeaf		= item._countLeaf;
		_countBranch	= item._countBranch;
		_path			= item._path;

		_pParentNode	= item._pParentNode;
		for ( GroupNodeItemVecItr itr = _subItems.begin();
			itr != _subItems.end(); itr ++ )
		{
			itr->getParentNode() = this;
		}

		return *this;
	}
	
	//----------------------------------------------------------------
	GroupNodeItemVec* GroupNodeItem::getSubItems()
	{
		return &_subItems;
	}

	//----------------------------------------------------------------
	GroupNodeItemPtr GroupNodeItem::getSubItemByName(String leaf_name)
	{
		return getSubItemByName(leaf_name, &_subItems);
	}
	
	//----------------------------------------------------------------
	GroupNodeItemPtr GroupNodeItem::getSubItemByName(String leaf_name,
		GroupNodeItemVec* pMenuItems)
	{
		for (GroupNodeItemVec::iterator itr = pMenuItems->begin();
			itr != pMenuItems->end(); itr ++ )
		{
			if ( itr->_type == GROUP_NODE_LEAF
				&& itr->_name == leaf_name )
			{
				return &(*itr);
			}

			else
			{
				return getSubItemByName( leaf_name, itr->getSubItems() );
			}
		}

		return NULL;
	}

	
	//----------------------------------------------------------------
	GroupNodeItemPtr GroupNodeItem::getSubItemByID(UINT leaf_id)
	{
		return getSubItemByID(leaf_id, &_subItems);
	}

	//----------------------------------------------------------------
	GroupNodeItemPtr GroupNodeItem::getSubItemByID(UINT leaf_id,
		GroupNodeItemVec* pMenuItems)
	{
		for (GroupNodeItemVec::iterator itr = pMenuItems->begin();
			itr != pMenuItems->end(); itr ++ )
		{
			if ( itr->_type == GROUP_NODE_LEAF 
				&& itr->_id == leaf_id )
			{
				return &(*itr);
			}

			else
			{
				return getSubItemByID( leaf_id, itr->getSubItems() );
			}
		}

		return NULL;
	}

	//----------------------------------------------------------------
	UINT& GroupNodeItem::getID()
	{
		return _id;
	}

	//----------------------------------------------------------------
	String& GroupNodeItem::getName()
	{
		return _name;
	}

	//----------------------------------------------------------------
	GroupNodeType& GroupNodeItem::getType()
	{
		return _type;
	}

	//----------------------------------------------------------------
	bool GroupNodeItem::isLeafItem()
	{
		return GROUP_NODE_LEAF == _type;
	}

	//----------------------------------------------------------------
	UINT& GroupNodeItem::getCountLeaf()
	{
		return _countLeaf;
	}

	//----------------------------------------------------------------
	UINT& GroupNodeItem::getCountBranch()
	{
		return _countBranch;
	}

	//----------------------------------------------------------------
	String& GroupNodeItem::getPath()
	{
		return _path;
	}

	//----------------------------------------------------------------
	GroupNodeItemPtr& GroupNodeItem::getParentNode()
	{
		return _pParentNode;
	}

	//----------------------------------------------------------------
	void GroupNodeItem::copy( const GroupNodeItem& item, bool bRecursive /*= false*/ )
	{
		if ( bRecursive )
		{
			*this = item;
		} 
		else
		{
			_type		= item._type;
			_id			= item._id;
			_name		= item._name;

			//_subItems	= item._subItems;

			//_countLeaf		= item._countLeaf;
			//_countBranch	= item._countBranch;
			_path			= item._path;

		}
	}

	//----------------------------------------------------------------
	void GroupNodeItem::erase( String node_name, GroupNodeItemPtr pNode, bool bRecursive /*= false */ )
	{
		GroupNodeItemVec* pSubItemsTemp = pNode->getSubItems();

		for (GroupNodeItemVec::iterator itr = pSubItemsTemp->begin();
			itr != pSubItemsTemp->end(); itr ++ )
		{
			String nodeDes(itr->_name);
			vgUtility::PatchUtility::toLowerCase(nodeDes);

			if ( itr->_type == GROUP_NODE_LEAF
				&& nodeDes == node_name )
			{
				pSubItemsTemp->erase( itr );
				pNode->_countLeaf -- ;
				return ;
			}
			else if( bRecursive )
			{
				return erase( node_name, &(*itr), bRecursive );
			}
		}
	}

	//----------------------------------------------------------------
	void GroupNodeItem::erase( String node_name, bool bRecursive /*= false */ )
	{
		erase( node_name, this, bRecursive );
	}

	//----------------------------------------------------------------
	void GroupNodeItem::updateBeforeErase()
	{
		GroupNodeItemPtr pParent = this;
		
		do 
		{
			pParent->_countLeaf --;

			pParent = pParent->getParentNode();

		} while ( pParent );
		
	}

	//----------------------------------------------------------------
	void GroupNodeItem::deleteAllData()
	{
		setDefault();
	}

	//----------------------------------------------------------------
	void GroupNodeItem::setDefault()
	{
		_subItems.clear();

		_pParentNode = NULL;

		//_path = _name = "";

		_countLeaf = _countBranch = 0;
	}
	//----------------------------------------------------------------
	GroupNodeManager::GroupNodeManager()
	{

		String exePath = vgUtility::PatchUtility::getCurrentProcessPath();
		_pathIn = exePath.c_str();

		TCHAR szFind[MAX_PATH]; 

		lstrcpy(szFind, _pathIn.c_str() ); 
		lstrcat(szFind, "\\"); 
		lstrcat(szFind, "*.*"); // 找所有文件 

		WIN32_FIND_DATA wfd; 

		HANDLE hFind = FindFirstFile( szFind, &wfd ); 

		if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败 
			return; 	
		do 
		{ 
			if (wfd.cFileName[0] == '.') 
				continue; // 过滤这两个目录 

			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{ 
				_pathIn = _pathIn + wfd.cFileName + "\\";
			} 

		} while (FindNextFile(hFind, &wfd)); 

		FindClose(hFind); // 关闭查找句柄 


		exePath = exePath.substr(0, exePath.find_last_of('\\') );
		exePath = exePath.substr(0, exePath.find_last_of('\\') );

		exePath += "\\temp\\";
		_pathOut = exePath.c_str();	
		
		initializeGroupNode();
	}	


	//----------------------------------------------------------------
	void GroupNodeManager::filterVersion( GroupNodeItemPtr pNode,
		const StringVector& filters, FolderNameMap folderMap )
	{
		GroupNodeItemPtr	pRootNodeTemp		= pNode;

		GroupNodeItemVec*	pSubItems = pRootNodeTemp->getSubItems();

		GroupNodeItemVec::iterator itr = pSubItems->begin();
		for ( ; itr != pSubItems->end(); )
		{
			//如果是分支，检测文件夹是否需要过滤,目前只检测bin 下的子文件夹
			if ( itr->getType() == GROUP_NODE_BRANCH && itr->getParentNode()->getParentNode() == NULL )
			{
				if ( !checkIsNeedFilter( &(*itr), folderMap ) )
				{
					itr ++;
					continue;
				}

			}

			if (  itr->isLeafItem() )
			{
				String nodeName = itr->getName();
				vgUtility::PatchUtility::toLowerCase(nodeName);

				// 是否符合过滤条件

				StringVector::const_iterator itrFilter = filters.begin();
				for( ; itrFilter != filters.end(); itrFilter ++ )
				{
					String filterString(*itrFilter);
					vgUtility::PatchUtility::toLowerCase(filterString);

					//过滤第三方库和标准库的debug版
					if ( filters.size() == 1 && filterString == "debug" )
					{
						std::string ext = vgUtility::PatchUtility::getFileExtension( nodeName );
						if ( ext == "dll" )
						{
							size_t length = nodeName.length();
							size_t pos = nodeName.find_first_of( '.', 0 );
							if ( nodeName.at( pos - 1 ) == 'd' )
							{
								break;
							}
						}
						
					}

					if ( String::npos != nodeName.find( filterString ) )
					{
						break;
					}
				}

				// 过滤
				if ( itrFilter != filters.end() )
				{
					pRootNodeTemp->updateBeforeErase();
					
					itr = pSubItems->erase( itr );

					continue;
				}
				
			}
			else
			{
				filterVersion( &(*itr), filters, folderMap );
			}


			itr++;
		}


	}

	//----------------------------------------------------------------
	GroupNodeItem* GroupNodeManager::getVersionByVersionName( String& name )
	{
		String nameLower(name);

		vgUtility::PatchUtility::toLowerCase( nameLower );

		VersionMapItr itr = _versions.find( nameLower );
		
		if( itr != _versions.end() )
		{
			return &itr->second;
		}

		return NULL;
	}

	void GroupNodeManager::initializeGroupNode()
	{
		GroupNodeItem	rootNode( _pathIn, NULL, 0, GROUP_NODE_BRANCH );

		_versions.insert( VersionPair("all",	rootNode ) );

		StringVector filterString;
		
		filterString.clear();
		_filters.insert( FiltersPair("all",		filterString ) );
		

	}

	//----------------------------------------------------------------
	StringVector* GroupNodeManager::getFilterByVersionName( String& name )
	{
		String nameLower(name);

		vgUtility::PatchUtility::toLowerCase( nameLower );

		FiltersMapItr itr = _filters.find( nameLower );

		if( itr != _filters.end() )
		{
			return &itr->second;
		}

		return NULL;
	}

	//----------------------------------------------------------------
	VersionMap* GroupNodeManager::getVersionsPtr()
	{
		return &_versions;
	}

	//----------------------------------------------------------------
	FiltersMap* GroupNodeManager::getFiltersPtr()
	{
		return &_filters;
	}

	//----------------------------------------------------------------
	String& GroupNodeManager::getPathIn()
	{
		return _pathIn;
	}

	//----------------------------------------------------------------
	String& GroupNodeManager::getPathOut()
	{
		return _pathOut;
	}

	//----------------------------------------------------------------
	bool GroupNodeManager::checkIsNeedFilter( GroupNodeItemPtr pNode, FolderNameMap folderMap )
	{
		bool needDeal = true;

		FolderNameMapItr iter = folderMap.begin();
		FolderNameMapItr iter_end = folderMap.end();

		for ( ; iter != iter_end; iter++  )
		{ 
			if ( pNode->getName() == iter->second )
			{
				needDeal = false;
				break;
			}
		}

		return needDeal;
	}

}// namespace	vgGroup

