


#include <vgStableHeaders.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkRendererHolder.h>
#include <vgKernel/vgkRendererHolderManager.h>


namespace vgKernel {
	
	
	
	
	//----------------------------------------------------------------
	RendererHolder::RendererHolder( bool auto_register /*= true */ )
	{
		if ( auto_register )
		{
			registerToHolderMananger();
		}
	}
	//----------------------------------------------------------------
	void RendererHolder::registerToHolderMananger()
	{
		RendererHolderManager::getSingleton().registerHolder( this );
	}
	//----------------------------------------------------------------

	RendererHolder::~RendererHolder()
	{
		RendererHolderManager::getSingleton().unregisterHolder(this);
	}
}// end of namespace vgKernel
