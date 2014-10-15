



#ifndef __VGSCSCRIPTPLUGIN_H__
#define __VGSCSCRIPTPLUGIN_H__

#include <vgScript/vgscDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>

	
namespace vgScript {

	/**
		@date 	2009/07/01  10:12	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class ScriptPlugin : public vgKernel::Plugin
	{
	public:
		ScriptPlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~ScriptPlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGSC_DLL_NAME;
		}

		virtual bool initInOpenGL();


		virtual void renderFirst();

		virtual void render();

		virtual void renderLast();

		virtual bool uninitInOpenGL();

		virtual void reset();

		virtual void readProjectEnd( const String& projpath , 
			const String& projname);

		virtual void saveProject(  const String& projpath ,
			const String& projname );


	};
	
	
	
}// end of namespace vgScript
	


#endif // end of __VGSCSCRIPTPLUGIN_H__