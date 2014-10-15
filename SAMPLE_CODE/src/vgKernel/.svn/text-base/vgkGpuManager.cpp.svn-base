


#include <vgStableHeaders.h>
#include <vgKernel/vgkGpuManager.h>


namespace vgKernel {
	
	
	
	
	//----------------------------------------------------------------
	bool GpuManager::initAfterOpenGLSetup()
	{
		assert( _gpuSupport == NULL );
		_gpuSupport = new vgKernel::GpuSupport;

		return true;
	}
	//----------------------------------------------------------------
	bool GpuManager::uninitBeforeOpenGLDestroy()
	{
		assert( _gpuSupport != NULL );
		delete _gpuSupport;
		_gpuSupport = NULL;

		return true;
	}

	GpuManager::GpuManager() : Singleton<GpuManager>( VGK_SINGLETON_LEFE_GPUMGR )
	{
		_gpuSupport = NULL;
		VGK_TRACE(_T("GpuManager created."));
	}

	GpuManager::~GpuManager()
	{
		VGK_TRACE(_T("GpuManager destroyed."));
	}
	//----------------------------------------------------------------
}// end of namespace vgKernel
