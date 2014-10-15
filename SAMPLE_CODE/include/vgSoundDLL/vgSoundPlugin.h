


#ifndef __VGSOUNDPLUGIN_H__
#define __VGSOUNDPLUGIN_H__


#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkPlugin.h>

#include <vgSound/vgSoundDefinition.h>

	
namespace vgSound {

	/**
		@date 	2009/06/18  14:45	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class SoundPlugin : public vgKernel::Plugin
	{
	public:
		SoundPlugin():
		  vgKernel::Plugin()
		{
			
		}
		virtual ~SoundPlugin()
		{
			
		}

	public:

		virtual String getName() 
		{
			return VGSOUND_DLL_NAME;
		}

		virtual bool initInOpenGL();

		virtual bool uninitInOpenGL();

		virtual vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer );

		
	};

	

	
}// end of namespace vgTerritory
	


#endif // end of __VGTTERRITORYPLUGIN_H__