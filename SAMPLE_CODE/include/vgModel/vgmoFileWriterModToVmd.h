


#ifndef __VGMO_FILEWRITERMODTOVMD_H__
#define __VGMO_FILEWRITERMODTOVMD_H__



#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgModel/vgmoFileDefinitionVmd.h>
#include <vgKernel/vgkProcessObserver.h>
#include <vgKernel/vgkStringPairVector.h>

	
namespace vgModel {

	/**
		@date 	2008/08/06  14:49	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class VGMO_EXPORT FileWriterModToVmd : public vgKernel::ProcessNotifier
	{
	public:
		FileWriterModToVmd()
		{
			
		}
		virtual ~FileWriterModToVmd()
		{
			
		}
	
	
	public:

		/**
			 输入都需要是绝对路径
		*/
		bool writeToVmdFromStringPairs( 
			const vgKernel::StringPairVector& inputpairs , const float& lod0_factor , 
			const float& lod1_factor ,
			const float& squareDistNear , const float& squareDistFar );


	private:

		// lod0_factor为最模糊的一级
		static bool writeToVmdFileFromModStream( 
			const vgKernel::StreamReaderPtr preader , const String& save_absolute_path,
			const float& lod0_factor , const float& lod1_factor ,
			const float& squareDistNear , const float& squareDistFar );
		
	};
	
	
}// end of namespace vgModel
	


#endif // end of __VGMO_FILEWRITERMODTOVMD_H__