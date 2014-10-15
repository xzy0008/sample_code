


#ifndef __VGFFONTPLUGIN_H__
#define __VGFFONTPLUGIN_H__

#include <vgFont/vgfDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>


namespace vgFont {

	/**
	@date 	2009/06/30  14:45	
	@author  yuxin

	@brief 	

	@see    
	*/
	class FontPlugin : public vgKernel::Plugin
	{
	public:
		FontPlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~FontPlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGF_DLL_NAME;
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


}// end of namespace vgFont



#endif // end of __VGLOLOGOPLUGIN_H__