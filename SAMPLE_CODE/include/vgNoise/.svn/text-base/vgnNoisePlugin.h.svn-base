


#ifndef __VGNOISEPLUGIN_H__
#define __VGNOISEPLUGIN_H__

#include <vgNoise/vgn_api.h>
#include <vgNoise/vgnDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkPlugin.h>


namespace vgNoise {


	class NoisePlugin : public vgKernel::Plugin
	{
	public:
		NoisePlugin():
		  vgKernel::Plugin()
		  {

		  }
		  virtual ~NoisePlugin()
		  {

		  }

	public:

		virtual String getName() 
		{
			return VGNOISE_DLL_NAME;
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