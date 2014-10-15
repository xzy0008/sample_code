



#include <vgStableHeaders.h>
#include <vgKernel/vgkRendererHolderManager.h>


namespace vgKernel {
	
	
	
	
	//----------------------------------------------------------------
	bool RendererHolderManager::unregisterHolder( RendererHolder* holder )
	{
		//TRACE("Unregister holder %d \n", holder);
		if ( checkExist( holder ) == false )
		{
			return false;
		}

		deleteHolder( holder );
		return true;
	}
	//----------------------------------------------------------------
	bool RendererHolderManager::registerHolder( RendererHolder* holder )
	{
		if ( checkExist( holder ) == true )
		{
			return false;
		}
		//TRACE("RendereHolderManager--Regedit holder %d\n", holder);
		_holders.push_back( holder );

		RendererHolderPtrVec::iterator iter = _holders.begin();
		RendererHolderPtrVec::iterator iter_end = _holders.end();

		for ( ; iter != iter_end ; ++iter )
		{
			RendererHolder* pholder = *iter;
			//TRACE("ONADD holder address %d \n", pholder);

		}

		return true;
	}
	//----------------------------------------------------------------
	bool RendererHolderManager::deleteRenderer( Renderer* renderer )
	{
		RendererHolderPtrVec::iterator iter1 = _holders.begin();
		RendererHolderPtrVec::iterator iter_end1 = _holders.end();

		for ( ; iter1 != iter_end1 ; ++iter1 )
		{
			RendererHolder* pholder = *iter1;
			//TRACE("ONADD holder address %d \n", pholder);

		}

		RendererHolderPtrVec::iterator iter = _holders.begin();
		RendererHolderPtrVec::iterator iter_end = _holders.end();

		for ( ; iter != iter_end ; ++iter )
		{
			RendererHolder* pholder = *iter;

			if ( pholder->onDeleteRenderer( renderer ) )
			{
				return true;
			}
		}

		return false;
	}
	//----------------------------------------------------------------
	bool RendererHolderManager::checkExist( RendererHolder* holder )
	{
		RendererHolderPtrVec::iterator iter = _holders.begin();
		RendererHolderPtrVec::iterator iter_end = _holders.end();

		for ( ; iter != iter_end ; ++iter )
		{
			if ( holder == *iter )
			{
				return true;
			}
		}

		return false;
	}
	//----------------------------------------------------------------
	void RendererHolderManager::deleteHolder( RendererHolder* holder )
	{
		RendererHolderPtrVec::iterator iter = _holders.begin();

		while ( iter != _holders.end() )
		{
			if ( *iter == holder )
			{
				iter = _holders.erase( iter );
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
