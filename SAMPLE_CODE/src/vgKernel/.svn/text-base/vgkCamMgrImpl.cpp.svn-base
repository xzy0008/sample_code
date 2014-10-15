


#include <vgStableHeaders.h>
#include <vgKernel/vgkCamMgrImpl.h>
#include <vgKernel/vgkCamMgrHolder.h>


namespace vgKernel {
	
	
	
	

	CamMgrImpl::CamMgrImpl( bool autoreg /*= true */ )
	{
		if ( autoreg )
		{
			CamMgrHolder::getSingleton().registerCamMgr( this );
		}
	}
}// end of namespace vgKernel
