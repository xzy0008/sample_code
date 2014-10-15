


#include <vgStableHeaders.h>
#include <vgKernel/vgkClassFactory.h>
#include <vgKernel/vgkClassFactoryManager.h>


namespace vgKernel {
	
	
	
	

	ClassFacRegProxy::ClassFacRegProxy( ClassFactory* fac )
	{
		bool regok = ClassFactoryManager::getSingleton().registerFactory( fac );

		assert( regok == true );
	}
}// end of namespace vgKernel
