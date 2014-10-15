

#ifndef __VGMVGFILEREADERVGABSTRACT_H__
#define __VGMVGFILEREADERVGABSTRACT_H__

#include <vgKernel/vgkStreamReader.h>

#include <vgMod/vgFileDefinitionVG.h>
#include <vgMod/vgNode.h>

namespace vgMod{

	using namespace vgCore;
	
	/**
		@action		creation
		@date 		2009/03/04  13:38	
		@author  	lss
	
		@brief 	
	
		@see    
		*/
	class	FileReaderVGAbstract
	{
	public:
		FileReaderVGAbstract()	{}
		~FileReaderVGAbstract()	{}

		virtual	bool	read( const String& open_absolute_path, 
			NodeAbsPtrVec* pNodeIndexList,
			NodePtrPackage* pNodePackage,
			bool bDirectly = false) = 0;

	protected:
		virtual	bool	readOherModulesFromVg() = 0;

		virtual	bool	readNodeModuleFromVg() = 0;
		virtual	bool	readAbstractNodesFromVG() = 0;
		virtual	bool	readDataNodesByAbstractNodeFromVG() = 0;

		virtual	bool	generateVgNodeFromBuffer(char *pBuffer, Node** pNodeData)	 = 0;

		
		virtual	bool	addVgNodeToManager()	 = 0;
		
		//virtual	bool	addVgNodeToUI()	 = 0;
	};
}//namespace vgMod

#endif//__VGMVGFILEREADERVGABSTRACT_H__
