


#ifndef __VGIFILEREADERVGI_H__
#define __VGIFILEREADERVGI_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiFileDefinitionVgi.h>

	
namespace vgImage {

	/**
		@date 	2008/08/04  9:38	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGI_EXPORT FileReaderVgi
	{
	private:
		FileReaderVgi()
		{
			
		}
		~FileReaderVgi()
		{
			
		}
	
	
	public:

		static VgiBriefPtrVec* readFromFile( const String& abs_filename , 
			VgiHeader& outHeader );
	
	
	};
	
	
}// end of namespace vgImage
	


#endif // end of __VGIFILEREADERVGI_H__