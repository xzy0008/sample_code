

#include <vgStableHeaders.h>
#include <vgKernel/vgkSingleton.h>


namespace vgKernel {
	
	
	SingletonManager::SingletonInstanceMap* SingletonManager::_otherInstancesPtrMap = NULL;

	SingletonManager* SingletonManager::_instance=0;

	
	void SingletonManager::deleteSingletonsByWeight()
	{
		if ( _otherInstancesPtrMap ==NULL )
		{
			return;
		}

		// the smaller one is in begin position.
		SingletonInstanceMap::iterator iter = _otherInstancesPtrMap->begin();
		SingletonInstanceMap::iterator iter_end = _otherInstancesPtrMap->end();

		for ( ; iter != iter_end ; ++iter )
		{
			assert( iter->second.isNull() == false );

			bool shutdown_result = iter->second->shutdown();
			// assert( shutdown_result == true );

			if ( shutdown_result == false )
			{
				// 此时有致命错误
				// assert(0);
			}

			iter->second.setNull();
		}
	}
	//----------------------------------------------------------------
	void SingletonManager::deleteSingletonInstance( 
		SingletonInstance* need_to_delete )
	{
		if ( _otherInstancesPtrMap ==NULL )
		{
			return;
		}


		SingletonInstanceMap::iterator iter = _otherInstancesPtrMap->begin();

		while ( iter != _otherInstancesPtrMap->end() )
		{
			if ( iter->second.getPointer() == need_to_delete )
			{
				bool shutdown_result = iter->second->shutdown();
				assert( shutdown_result == true );

				if ( shutdown_result == false )
				{
					//此时有致命错误
					assert(0);
				}

				iter->second->notifyDeleteInstance();

				iter->second.setNull();

				iter = _otherInstancesPtrMap->erase( iter );
			}
			else
			{
				++iter;
			}
		}

		return;
	}
	//----------------------------------------------------------------

}// end of namespace vgKernel
