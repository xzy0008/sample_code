


#ifndef __VGDDATABASEPLUGIN_H__
#define __VGDDATABASEPLUGIN_H__

#include <vgDatabase/vgdDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>

namespace vgDatabase {

	/**
	@date 	2009/06/29 14:45	
	@author  yuxin

	@brief 	

	@see    
	*/
	class DatabasePlugin : public vgKernel::Plugin
	{
	public:
		DatabasePlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~DatabasePlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGD_DLL_NAME;
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


}// end of namespace vgDatabase



#endif // end of __VGDDATABASEPLUGIN_H__