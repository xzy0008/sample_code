


#ifndef __VGTERRITORY_TFILEREADERVTR_H__
#define __VGTERRITORY_TFILEREADERVTR_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtFileDefinitionVtr.h>

	
namespace vgTerritory {


	using namespace vgKernel;

	/**
		@date 	2008/09/02  9:34	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT FileReaderVtr
	{
	private:
		FileReaderVtr()
		{
			
		}
		~FileReaderVtr()
		{
			
		}
	
	public:

		static VtrBriefPtrVec* readFromFile( const String& abs_filename );

		static VtrHeaderPtr readHeaderFromFile( const String& abs_filename );

	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TFILEREADERVTR_H__