


#ifndef __VGTTERRITORYPLUGIN_H__
#define __VGTTERRITORYPLUGIN_H__

#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkPlugin.h>

	
namespace vgTerritory {

	/**
		@date 	2009/06/18  14:45	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class TerritoryPlugin : public vgKernel::Plugin
	{
	public:
		TerritoryPlugin():
		  vgKernel::Plugin()
		{
			
		}
		virtual ~TerritoryPlugin()
		{
			
		}

	public:

		virtual String getName() 
		{
			return VGT_DLL_NAME;
		}

		virtual bool initInOpenGL();

		virtual void render();

		virtual bool uninitInOpenGL();

		virtual void reset();
	
		virtual void readProject(  const String& projpath ,
			const String& projname );

		virtual void saveProject(  const String& projpath ,
			const String& projname );


	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTTERRITORYPLUGIN_H__