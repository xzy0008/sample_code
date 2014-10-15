


#ifndef __VGDecoder3DSPLUGIN_H__
#define __VGDecoder3DSPLUGIN_H__


#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkPlugin.h>

#include <vgDecoder3DSDLL/vgDecoder3DSDefinition.h>

	
namespace vgEdit {

	/**
		@date 	2010/04/26  14:45	
		@author  lss
	
		@brief 	
	
		@see    
	*/
	class Decoder3DSPlugin : public vgKernel::Plugin
	{
	public:
		Decoder3DSPlugin():
		  vgKernel::Plugin()
		{
			
		}
		virtual ~Decoder3DSPlugin()
		{
			
		}

	public:

		virtual String getName() 
		{
			return VGDECODER3DS_DLL_NAME;
		}

		virtual bool initInOpenGL();

		virtual bool uninitInOpenGL();

		
	};

	

	
}// end of namespace vgTerritory
	


#endif // end of __VGTTERRITORYPLUGIN_H__