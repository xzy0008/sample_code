


#include <vgStableHeaders.h>
#include <vgMesh/vgmManipulateManager.h>
#include <vgKernel/vgkTrace.h>

namespace vgMesh {
	
	
	
	
	//----------------------------------------------------------------
	ManipulateManager::ManipulateManager()
		: Singleton<ManipulateManager>( VGK_SINGLETON_LEFE_MANIPULATEMGR )
	{
		_selectBuffer = NULL;
		VGK_TRACE(_T("ManipulateManager created."));
	}
	//----------------------------------------------------------------
	ManipulateManager::~ManipulateManager()
	{
		VGK_TRACE(_T("ManipulateManager destroyed."));
	}
	//----------------------------------------------------------------
	bool ManipulateManager::initialise()
	{
		assert( _selectBuffer == NULL );
		_selectBuffer =  new UniqueIDVector;
		return true;
	}
	//----------------------------------------------------------------
	bool ManipulateManager::shutdown()
	{
		if ( _selectBuffer != NULL )
		{
			delete _selectBuffer;
			_selectBuffer = NULL;
		}
		return true;
	}
	//----------------------------------------------------------------



}// end of namespace vgMesh
