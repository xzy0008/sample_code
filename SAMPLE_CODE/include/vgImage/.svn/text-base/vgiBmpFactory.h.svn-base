


#ifndef __VGIBMPFACTORY_H__
#define __VGIBMPFACTORY_H__

#include <vgKernel/vgkForward.h>
#include <vgImage/vgiImageRGBA.h>

	
namespace vgImage {

	/**
		@date 	2009/04/18  21:07	
		@author  leven
	
		@brief 	注意，先不要使用，实现有问题
	
		@see    
	*/
	class VGK_EXPORT BmpFactory
	{
	private:
		BmpFactory()
		{

		}
	public:
		~BmpFactory()
		{

		}


	public:

		static ImageRGBA* decodeBmpFileToRGBA( 
			const String& file_path );

		static ImageRGBA* decodeBmpToRGBAInMemory( 
			char* file_buffer , long buf_size, bool filp_y );

	};
	
	
}// end of namespace vgImage
	


#endif // end of __VGIBMPFACTORY_H__