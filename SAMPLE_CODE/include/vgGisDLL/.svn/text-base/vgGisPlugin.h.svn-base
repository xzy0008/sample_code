


#ifndef __VGTTERRITORYPLUGIN_H__
#define __VGTTERRITORYPLUGIN_H__

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkPlugin.h>
#include <vgKernel/vgkRenderer.h>

#include <vgEntry/vgGisLayerEntry.h>
#include <vgGIS3D/vgPipeLineEntry.h>
	
namespace vgGIS3D {

	/**
		@date 	2009/06/24  14:45	
		@author  lss
	
		@brief 	
	
		@see    
	*/
	class GisPlugin : public vgKernel::Plugin
	{
	public:
		GisPlugin():
		  vgKernel::Plugin()
		{
			
		}
		virtual ~GisPlugin()
		{
			
		}

	public:

		virtual String getName();		

		virtual void render();

		virtual bool uninitInOpenGL();

		virtual vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer );

		virtual void readProject(const String& projpath , const String& projname);

		virtual void saveProject( const String& projpath , const String& projname );
	};

	

	
}// end of namespace vgTerritory
	


#endif // end of __VGTTERRITORYPLUGIN_H__