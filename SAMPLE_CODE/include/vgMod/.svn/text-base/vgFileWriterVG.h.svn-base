

#ifndef __VGMVGFILEWRITERVG_H__
#define __VGMVGFILEWRITERVG_H__

#include <vgMod/vgFileWriterVGAbstract.h>

namespace vgMod{

	using namespace vgCore;
	
	/**
	@date 	2009/03/02  19:12	
	@author  lss

	@brief 	

	@see    
	*/
	class	 VGDEP_EXPORT FileWriterVG : public FileWriterVGAbstract
	{
	public:
		FileWriterVG();
		~FileWriterVG();

		virtual	bool	write( const String& save_absolute_path, 
			NodeAbsPtrVec* pNodeIndexList,
			bool bDirectly = false);

	protected:
		virtual	bool	writeOherModulesToVg();

		virtual	bool	writeModModuleToVg();
		virtual	unsigned int writeAbstractNodesToVG();
		virtual	bool	writeDataNodesByAbstractNodeToVG();
		virtual	bool	writeOherModulesDirectly();
	protected:
		vgKernel::StreamWriterPtr m_pfile;
		String	m_strFilePath;
		
		VGFileHeader	m_fileHeader;
		NodeAbsPtrVec* m_pNodeIndexList;

	};
}//namespace vgMod

#endif//__VGMVGFILEWRITERVG_H__
