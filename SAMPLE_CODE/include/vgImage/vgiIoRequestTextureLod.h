





#ifndef __VGIIOREQUESTTEXTURELOD_H__
#define __VGIIOREQUESTTEXTURELOD_H__
#include <vgImage/vgiDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequest.h>

namespace vgImage {

	class Texture;

	/**
		@date 	2008/06/25  13:39	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGI_EXPORT IoRequestTextureLod : public vgAsyn::IoRequest
	{
	public:
		IoRequestTextureLod( Texture* tex , vgAsyn::FileInfo* fileinfo )
			: IoRequest( fileinfo ) ,
			_texture( tex )
		{

		}
		virtual ~IoRequestTextureLod()
		{
			
		}
	


		virtual bool anotherThreadHandler();

		virtual bool mainThreadHandler();


	private:

		Texture* _texture;
	
	};
	
	
	
	
}// end of namespace vgImage

#endif // end of __VGIIOREQUESTTEXTURELOD_H__