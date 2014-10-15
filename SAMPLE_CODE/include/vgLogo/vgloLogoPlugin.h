


#ifndef __VGLOLOGOPLUGIN_H__
#define __VGLOLOGOPLUGIN_H__

#include <vgLogo/vgloDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>


namespace vgLogo {

	/**
	@date 	2009/06/31  14:45	
	@author  yuxin

	@brief 	

	@see    
	*/
	class LogoPlugin : public vgKernel::Plugin
	{
	public:
		LogoPlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~LogoPlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGL_DLL_NAME;
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


}// end of namespace vgLogo



#endif // end of __VGLOLOGOPLUGIN_H__