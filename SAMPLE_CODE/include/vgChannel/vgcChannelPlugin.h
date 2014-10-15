


#ifndef __VGCHANPLUGIN_H__
#define __VGCHANPLUGIN_H__

#include <vgChannel/vgcDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>


namespace vgChannel {

	/**
	@date 	2009/06/30  14:45	
	@author  yuxin

	@brief 	

	@see    
	*/
	class ChannelPlugin : public vgKernel::Plugin
	{
	public:
		ChannelPlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~ChannelPlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGCHAN_DLL_NAME;
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


}// end of namespace vgChannel



#endif // end of __VGCHANPLUGIN_H__