


#ifndef __VGSHSHAPEPLUGIN_H__
#define __VGSHSHAPEPLUGIN_H__

#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkPlugin.h>

	
namespace vgShape {

	/**
		@date 	2009/06/29  14:41	
		@author  lss
	
		@brief 	
	
		@see    
	*/
	class ShapePlugin : public vgKernel::Plugin
	{
	public:
		ShapePlugin():
		  vgKernel::Plugin()
		{
			
		}
		virtual ~ShapePlugin()
		{
			
		}

	public:

		virtual String getName();	

		virtual bool initInOpenGL();

		virtual void render();

		virtual bool uninitInOpenGL();
		
		virtual void reset();

		virtual vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer );

	};

	

	
}// end of namespace vgShape
	


#endif // end of __VGSHSHAPEPLUGIN_H__