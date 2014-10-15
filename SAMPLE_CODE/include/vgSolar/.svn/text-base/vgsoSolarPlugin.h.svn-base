



#ifndef __VGSOSOLARPLUGIN_H__
#define __VGSOSOLARPLUGIN_H__

#include <vgSolar/vgsoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>

	
namespace vgSolar {

	/**
		@date 	2009/06/29  14:21	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class SolarPlugin : public vgKernel::Plugin
	{
	public:
		SolarPlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~SolarPlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGSO_DLL_NAME;
		}

		virtual bool initInOpenGL();

		virtual void render();

		virtual void renderEnd();


		virtual bool uninitInOpenGL();

		virtual void reset();

		virtual void readProject(  const String& projpath ,
			const String& projname );

		virtual void saveProject(  const String& projpath ,
			const String& projname );


	};

	
	
}// end of namespace vgSolar
	


#endif // end of __VGSOSOLARPLUGIN_H__