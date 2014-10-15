


#include <vgStableHeaders.h>
#include <vgKernel/vgkCamMgrHolder.h>


namespace vgKernel {
	
	
	
	

	CamMgrHolder::CamMgrHolder() : Singleton<CamMgrHolder>( VGK_SINGLETON_LEFE_CAMMGRHOLDER )
	{
		_camImpl = NULL;
		VGK_TRACE(_T("CamMgrHolder created."));
	}

	CamMgrHolder::~CamMgrHolder()
	{
		VGK_TRACE(_T("CamMgrHolder destroyed."));
	}
}// end of namespace vgKernel
