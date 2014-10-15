



#ifndef __VGGroupNodeManager_H__
#define __VGGroupNodeManager_H__


#include <vgKernel/vgkStringVector.h>


	/**
		@date 	2009/10/26  15:21	
		@author  LiuSS
	
		@brief 	
	
		@see    
	*/

namespace	vgGroup
{
	
	//----------------------------------------------------------------
	enum	GroupNodeType
	{
		GROUP_NODE_BRANCH,
		GROUP_NODE_LEAF,
		GROUP_NODE_TYPE_COUNT
	};

	//----------------------------------------------------------------
	class GroupNodeItem;
	typedef std::vector<GroupNodeItem>		GroupNodeItemVec;
	typedef std::vector<GroupNodeItem>::iterator		GroupNodeItemVecItr;
	typedef	GroupNodeItem*		GroupNodeItemPtr;

	class GroupNodeItem
	{
	public:
		GroupNodeItem( String name = "", 
			GroupNodeItemPtr pParentNode = NULL,
			UINT id = 0,
			GroupNodeType type = GROUP_NODE_LEAF );

		GroupNodeItem(const GroupNodeItem& item);

		~GroupNodeItem(){}
	

	public:
		bool	hasSubItem();
		void	appendSubItem( GroupNodeItem& item);
		void	appendSubItem( String name = "", 
			UINT id = 0,
			GroupNodeType type = GROUP_NODE_LEAF );

		GroupNodeItemVec*	getSubItems();

		GroupNodeItemPtr	getSubItemByName(String leaf_name);

		GroupNodeItemPtr	getSubItemByID(UINT leaf_id);

		GroupNodeItem&	operator=(const GroupNodeItem& item);

		bool	isLeafItem();

		void	copy(const GroupNodeItem& item, bool bRecursive = false);

		void	erase(String node_name, bool bRecursive = false );
		void	updateBeforeErase();

		void	deleteAllData();


	public:
		UINT&	getID();
		String&	getName();
		GroupNodeType&	getType();


	public:
		UINT&	getCountLeaf();
		UINT&	getCountBranch();
		String&	getPath();
		GroupNodeItemPtr& getParentNode();


	protected:
		GroupNodeItemPtr	getSubItemByName(String leaf_name,
			GroupNodeItemVec* pMenuItems);

		
		GroupNodeItemPtr	getSubItemByID(UINT leaf_id,
			GroupNodeItemVec* pMenuItems);

		void	erase(String node_name,
			GroupNodeItemPtr pNode, bool bRecursive = false );

		void	setDefault();


		// 基本属性和基本数据
	protected:
		UINT	_id;
		String	_name;
		GroupNodeType	_type;

		GroupNodeItemVec	_subItems;


		// 统计属性和统计数据
	protected:
		String  _path;
		
		UINT	_countLeaf;
		UINT	_countBranch;

		GroupNodeItemPtr _pParentNode;

	};// class GroupNodeItem

	typedef std::map< String, vgKernel::StringVector >				FiltersMap;
	typedef std::map< String, vgKernel::StringVector >::iterator	FiltersMapItr;
	typedef std::pair< String, vgKernel::StringVector >				FiltersPair;

	typedef std::map< String, GroupNodeItem>			VersionMap;
	typedef std::map< String, GroupNodeItem>::iterator	VersionMapItr;
	typedef std::pair< String, GroupNodeItem>			VersionPair;

	typedef std::map< int, String>             FolderNameMap;
	typedef std::map< int, String>::iterator   FolderNameMapItr;
	typedef std::pair< int, String>            FolderNamePair;
	//----------------------------------------------------------------
	class GroupNodeManager
	{
	public:
		GroupNodeManager();
		
		~GroupNodeManager()	{}


	public:
		VersionMap*	getVersionsPtr();
		FiltersMap*	getFiltersPtr();

		String&	getPathIn();
		String& getPathOut();

	public:
		virtual	void	initializeGroupNode();

	public:
		GroupNodeItem*	getVersionByVersionName( String& name);

		vgKernel::StringVector* getFilterByVersionName( String& name);

		static bool checkIsNeedFilter( GroupNodeItemPtr pNode, FolderNameMap folderMap );

		static void	filterVersion( GroupNodeItemPtr pNode,
			const vgKernel::StringVector& filters, FolderNameMap folderMap );

	
	protected:
		//GroupNodeItem	_rootGroupNode;
		VersionMap	_versions;

		FiltersMap	_filters;

		String _pathIn, _pathOut;
	};// class GroupNodeManager 

	//----------------------------------------------------------------
}// namespace vgGroup


	


#endif // end of __VGGroupNodeManager_H__