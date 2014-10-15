


#include <vgStableHeaders.h>
#include <vgTerritory/vgtElevationFilter.h>
#include <vgTerritory/vgtIoRequestElevation.h>


namespace vgTerritory {
	

	//----------------------------------------------------------------
	IoRequestElevation::IoRequestElevation( Elevation* elev )
		: vgAsyn::IoRequest( elev->getFileInfoClone() )
	{
		assert( elev != NULL );

		_oldElev = elev;
		_elevItemName = elev->getFatherElevItem()->getName();

		_lod = elev->getLod();

		setAsynchronousMode( false );
	}
	//----------------------------------------------------------------
	bool IoRequestElevation::anotherThreadHandler()
	{
		dispatchMainThreadFunc();
		return true;
	}
	//----------------------------------------------------------------
	bool IoRequestElevation::mainThreadHandler()
	{
		/**
		此时_oldItem可能已经不存在了.
		*/
		ElevationItem* item = 
			ElevationManager::getSingleton().getElevationItem( _elevItemName ,false );

		if ( item == NULL )
		{
			return true;
		}

		assert( _lod  == VGLOD_CLEAR );

		Elevation* elev = item->getElevationByLod( _lod );
		assert( elev != NULL );

		const int count = elev->getReferenceCount();
		assert( count >= 0 );

		//------------------------------------------
		// 只有计数值大于0并且map的id不为空的时候才需要重置
		//------------------------------------------
		if ( count != 0 && elev->getHeightMapID() == VG_NULL_TEXTURE_ID )
		{
			//------------------------------------------
			// 开始过滤
			//------------------------------------------
			ElevationFilter::getSingleton().doFilter( item , _buffer , _fileInfo->_fileSize );

			bool setok = elev->setHeightMapID( _buffer , _fileInfo->_fileSize );

			assert( setok == true );

			if ( setok == false )
			{
				delete this;
				return false;
			}
		}

		delete this;
		return true;
	}
	//----------------------------------------------------------------
	bool IoRequestElevation::isReallyNeedToSend()
	{
		/**
		这个时候检查Elevation中的RefCount
		*/
		const int count = _oldElev->getReferenceCount();

		if( count == NULL || 
			_oldElev->getHeightMapID() != VG_NULL_TEXTURE_ID )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
}// end of namespace vgTerritory
