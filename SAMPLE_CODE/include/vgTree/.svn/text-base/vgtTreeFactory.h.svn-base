


#ifndef __VGTTREEFACTORY_H__
#define __VGTTREEFACTORY_H__
#include <vgTree/vgtrDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTree/vgtAbstractTree.h>
#include <vgKernel/vgkAbstractTreeFac.h>

	
namespace vgTree {

	

	class AbstractTree;

	/**
		@date 	2008/08/05  21:07	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGTR_EXPORT TreeFactory : public vgKernel::AbstractTreeFac
	{
	public:
		TreeFactory();
		~TreeFactory();

	public:


		virtual AbstractTree* create();


		static AbstractTree* getTreeByType(TREE_TYPE treeType = TREE_LINEAR);

	private:
		static std::vector<AbstractTree*>	_treeVec;
	};

	
	
}// end of namespace vgTree
	


#endif // end of __VGTTREEFACTORY_H__