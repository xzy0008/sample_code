



#ifndef __VGMO_FILEREADERVMD_H__
#define __VGMO_FILEREADERVMD_H__
#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgModel/vgmoFileDefinitionVmd.h>
#include <vgModel/vgmoModelItem.h>

	
namespace vgModel {




	/**
		@date 	2008/07/05  14:53	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGMO_EXPORT FileReaderVmd
	{
	public:
		FileReaderVmd()
		{
			
		}
		~FileReaderVmd()
		{
		
		}

	
		static VmdBriefPtrVec* getVmdBriefFromFile(
			const String& absolute_file_path, VmdHeader& out_header );

	//	static VmdDataStructPtrVec*	getVmdDataStructByBrief(
	//		const String& absolute_file_path);

	//	static bool writeVmdBriefToFile(
	//		const String& absolute_file_path);

	//	static bool	writeCrcCheckCodeToFile(
	//		const String& absolute_file_path );

	//	static bool	reCalculateBoundingBox(
	//		const String& absolute_file_path);

	//	static bool	upgradeVmd(
	//		const String& absolute_file_path , String newOutputDir);

	//private:
	//	static VmdDataStructPtrVec*	m_pDataStructPtrVec;
	//	static VmdBriefPtrVec*		m_pBriefPtrVec;
	//	static CFile*				m_pFile;
	};
	
	
}// end of namespace vgModel
	
////复制文件的函数
//BOOL CommonCopyFile(CString SourceFileName, CString DestFileName);

#endif // end of __VGMO_FILEREADERVMD_H__