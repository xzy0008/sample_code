


#include <vgStableHeaders.h>
#include <vgTree/vgtTreeFactory.h>
#include <vgTree/vgtSimpleTree.h>
#include <vgTree/vgtMagicTree.h>



namespace vgTree {

	//TreeFactory* tree_fac = new TreeFactory;
	
	std::vector<AbstractTree*>	TreeFactory::_treeVec;

	TreeFactory::TreeFactory()
	{
		//_treeVec.push_back( new	SimpleTree);
		//_treeVec.push_back( new	vgMagicTree);
	}
	TreeFactory::~TreeFactory()
	{
		/*for (std::vector<AbstractTree*>::iterator iter = _treeVec.begin();
			iter != _treeVec.end(); iter++ )
		{
			if ( *iter)
			{
				delete *iter;
			}
		}

		_treeVec.clear();*/
	}

	AbstractTree* TreeFactory::getTreeByType( TREE_TYPE treeType /*= TREE_LINEAR*/ )
	{
		/*for (std::vector<AbstractTree*>::iterator iter = _treeVec.begin();
		iter != _treeVec.end(); iter++ )
		{
		if ( treeType == (*iter)->getType() )
		{
		return	*iter;
		}
		}

		AbstractTree* pNewTree = NULL;*/
		switch (treeType)
		{
		case TREE_LINEAR:
			return	new	SimpleTree;
			break;

		//case TREE_QUAD:
		//	return	new	vgMagicTree;
		//	break;

		default:
			return NULL;
		}

		//_treeVec.push_back(pNewTree);
		//return	pNewTree;
	}

	AbstractTree* TreeFactory::create()
	{
		return	new	SimpleTree;
	}
}// end of namespace vgTree
