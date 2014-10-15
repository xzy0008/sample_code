


#ifndef __VGTRIPLUGIN_H__
#define __VGTRIPLUGIN_H__

#include <vgTrigger/vgtrDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>


namespace vgTrigger {

	/**
	@date 	2009/12/7  15:25	
	@author  kinghj

	@brief 	

	@see    
	*/
	class TriggerPlugin : public vgKernel::Plugin
	{
	public:
		TriggerPlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~TriggerPlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGTRI_DLL_NAME;
		}

		virtual bool initInOpenGL();

		virtual void render();

		virtual bool uninitInOpenGL();

		virtual void reset();

		virtual void readProject(  const String& projpath ,
			const String& projname );

		virtual void saveProject(  const String& projpath ,
			const String& projname );

		virtual vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer );

	};


}// end of namespace vgTrigger



#endif // end of __VGTRIPLUGIN_H__