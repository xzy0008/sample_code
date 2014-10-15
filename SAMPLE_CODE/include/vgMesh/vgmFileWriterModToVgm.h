


#ifndef __VGMFILEWRITERMODTOVGM_H__
#define __VGMFILEWRITERMODTOVGM_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgMesh/vgmFileDefinitionVgm.h>
#include <vgKernel/vgkProcessObserver.h>
#include <vgKernel/vgkStringPairVector.h>

	
namespace vgMesh {

	/**
		@date 	2008/08/06  14:49	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class FileWriterModToVgm : public vgKernel::ProcessNotifier
	{
	public:
		FileWriterModToVgm()
		{
			
		}
		virtual ~FileWriterModToVgm()
		{
			
		}
	
	
	public:

		/**
			 输入都需要是绝对路径
		*/
		bool writeToVgmFromStringPairs( 
			const vgKernel::StringPairVector& inputpairs , const float& lod0_factor , 
			const float& lod1_factor ,
			const float& squareDistNear , const float& squareDistFar );


	private:

		// lod0_factor为最模糊的一级
		static bool writeToVgmFileFromModStream( 
			const vgKernel::StreamReaderPtr preader , const String& save_absolute_path,
			const float& lod0_factor , const float& lod1_factor ,
			const float& squareDistNear , const float& squareDistFar );
	
		// factor为相乘因子
		// 为0.5时,缩减顶点数目一半
		static VgmDataStruct* getVgmDataStructByLodParam( VgmDataStruct* input_vgm ,
			const float& factor  , VgmBrief* input_brief);
	
	};
	
	
}// end of namespace vgMesh
	


#endif // end of __VGMFILEWRITERMODTOVGM_H__