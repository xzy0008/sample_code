

#ifndef __VGMVGFILEWRITERVGABSTRACT_H__
#define __VGMVGFILEWRITERVGABSTRACT_H__

#include <vgKernel/vgkStreamWriter.h>

#include <vgMod/vgFileDefinitionVG.h>
#include <vgMod/vgNode.h>


namespace vgMod{

	using namespace vgCore;
	

	/**
		@date 	2009/03/04  11:28	
		@author  lss
	
		@brief 	
	
		@see    
		*/
	class	FileWriterVGAbstract
	{
	public:
		FileWriterVGAbstract()	{}
		~FileWriterVGAbstract()	{}

		virtual	bool	write( const String& save_absolute_path, 
			NodeAbsPtrVec* pNodeIndexList,
			bool bDirectly = false) = 0;

	protected:
		virtual	bool	writeOherModulesToVg() = 0;

		virtual	bool	writeModModuleToVg() = 0;
		virtual	unsigned int writeAbstractNodesToVG() = 0;
		virtual	bool	writeDataNodesByAbstractNodeToVG() = 0;

	};
}//namespace vgMod

#endif//__VGMVGFILEWRITERVGABSTRACT_H__
