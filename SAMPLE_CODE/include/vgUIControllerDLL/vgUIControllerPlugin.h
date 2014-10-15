


#ifndef __VGTTERRITORYPLUGIN_H__
#define __VGTTERRITORYPLUGIN_H__

#include <vgUIController/vgUIControlDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkPlugin.h>

	
namespace vgUI {

	/**
		@date 	2009/06/24  14:45	
		@author  lss
	
		@brief 	
	
		@see    
	*/
	class UIControllerPlugin : public vgKernel::Plugin
	{
	public:
		UIControllerPlugin():
		  vgKernel::Plugin()
		{
			
		}
		virtual ~UIControllerPlugin()
		{
			
		}

	public:

		virtual String getName();		

		virtual void render();

		virtual bool uninitInOpenGL();
		
	};

	

	
}// end of namespace vgTerritory
	


#endif // end of __VGTTERRITORYPLUGIN_H__