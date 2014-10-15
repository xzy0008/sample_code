


#ifndef __VGKGPUMANAGER_H__
#define __VGKGPUMANAGER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkGpuSupport.h>
#include <vgKernel/vgkTrace.h>

	
namespace vgKernel {

	/**
		@date 	2008/08/19  9:22	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class VGK_EXPORT  GpuManager : public vgKernel::Singleton<GpuManager>
	{
		friend class vgKernel::Singleton<GpuManager>;
	private:
		GpuManager();
		virtual~GpuManager();

	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown()
		{
			assert( _gpuSupport == NULL );
			return true;
		}


	public:

		virtual void reset(){};

		bool initAfterOpenGLSetup();

		bool uninitBeforeOpenGLDestroy();

		vgKernel::GpuSupport* getGpuSupport()
		{
			assert( _gpuSupport != NULL );
			return _gpuSupport;
		}

	private:

		vgKernel::GpuSupport* _gpuSupport;

	};


	
}// end of namespace vgKernel
	


#endif // end of __VGKGPUMANAGER_H__