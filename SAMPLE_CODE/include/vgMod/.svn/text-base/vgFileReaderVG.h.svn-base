

#ifndef __VGMVGFILEREADERVG_H__
#define __VGMVGFILEREADERVG_H__

#include <vgmod/vgFileReaderVGAbstract.h>

namespace vgMod{

	using namespace vgCore;
	
	/**
	@date 	2009/03/02  21:12	
	@author  lss

	@brief 	

	@see    
	*/
	class	 VGDEP_EXPORT FileReaderVG : public FileReaderVGAbstract
	{
	public:
		FileReaderVG();
		~FileReaderVG();

		virtual	bool	read( const String& open_absolute_path, 
			NodeAbsPtrVec* pNodeIndexList,
			NodePtrPackage* pNodePackage,
			bool bDirectly = false);

	protected:
		virtual	bool	readOherModulesFromVg();

		virtual	bool	readNodeModuleFromVg();
		virtual	bool	readAbstractNodesFromVG();
		virtual	bool	readDataNodesByAbstractNodeFromVG();

		virtual	bool	generateVgNodeFromBuffer(char *pBuffer ,Node** pNodeData);
		
		
		virtual	bool	addVgNodeToManager();
		bool			readOherModulesDirectly();

		//virtual	bool	addVgNodeToUI();
	
	protected:
		vgKernel::StreamReaderPtr m_pfile;
		String	m_strFilePath;
		
		VGFileHeader	m_fileHeader;

		NodeAbsPtrVec* m_pNodeIndexList;
		NodePtrPackage* m_pNodePackage;

	};
}//namespace vgMod

#endif//__VGMVGFILEREADERVG_H__
