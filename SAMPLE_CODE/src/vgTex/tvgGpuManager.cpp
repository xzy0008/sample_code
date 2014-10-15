
#include <vgStableHeaders.h>
#include <vgStableHeaders.h>
#include <vgTex/tvgGpuManager.h>


template <> 
vgCore::GpuManager* ::Singleton<vgCore::GpuManager>::ms_pSingleton = 0;


namespace vgCore {
	
	//----------------------------------------------------------------
	GpuManager* GpuManager::getSingletonPtr(void)
	{
		return ms_pSingleton;
	}
	//----------------------------------------------------------------
	GpuManager& GpuManager::getSingleton(void)
	{  
		assert( ms_pSingleton );  
		return ( *ms_pSingleton );  
	}
	//----------------------------------------------------------------


	
}// end of namespace vgCore
