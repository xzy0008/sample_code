


#include <vgStableHeaders.h>
#include <vgKernel/vgkAbstractTreeFacMgr.h>
#include <vgKernel/vgkAbstractTreeFac.h>


namespace vgKernel {
	
	
	
	

	AbstractTreeFacMgr::AbstractTreeFacMgr() : Singleton<AbstractTreeFacMgr>( VGK_SINGLETON_LEFE_ABSTREEFACMGR )
	{
		_fac = NULL;
		VGK_TRACE(_T("AbstractTreeFacMgr created."));
	}

	AbstractTreeFacMgr::~AbstractTreeFacMgr()
	{
		VGK_TRACE(_T("AbstractTreeFacMgr destroyed."));
	}

	bool AbstractTreeFacMgr::shutdown()
	{
		if ( _fac != NULL )
		{
			delete _fac;
			_fac = NULL;
		}
		return true;
	}
}// end of namespace vgKernel
