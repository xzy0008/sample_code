


#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerrainCenterManager.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	TerrainCenterManager::TerrainCenterManager()
		: Singleton<TerrainCenterManager>( 
		VGK_SINGLETON_LEFE_TERRAINCENTERMGR )
	{
		_currentHeightLayer = 0;
		_camMgr = NULL;
		VGK_TRACE(_T("TerrainCenterManager created."));
	}
	//----------------------------------------------------------------
	bool TerrainCenterManager::initialise()
	{
		_camMgr = vgCam::CamManager::getSingletonPtr();
		assert( _camMgr != NULL );

		return true;
	}
	//----------------------------------------------------------------
	void TerrainCenterManager::updateCentersInEveryFrame(
		const int& height_render_flag )
	{
		assert( _centerLayers.empty() == false );

		const vgKernel::Vec3 pos = _camMgr->getCurrentPosition();

		//TerrainCenterPtrVec::iterator iter = _centerLayers.begin();
		//TerrainCenterPtrVec::iterator iter_end = _centerLayers.end();

		//for ( ; iter != iter_end ; ++iter )
		//{
		//	// 地形偏移时打开
		//	(*iter)->update( pos.x /*+ 32.0f*/, pos.z );
		//}

		int size = _centerLayers.size();
		_currentHeightLayer = 
			height_render_flag > (size -1) ? (size - 1) : height_render_flag;

		for ( int i = _currentHeightLayer ; i < size ; ++ i )
		{
			// 地形偏移时打开
			_centerLayers[i]->update( pos.x /*+ 32.0f*/, pos.z );
		}

		for ( int i = 0 ; i < _currentHeightLayer ; ++ i )
		{
			_centerLayers[i]->update(  -40960000.0f , -40960000.0f );
		}

	}
	//----------------------------------------------------------------
	bool TerrainCenterManager::uninitBeforeOpenGLDestroy()
	{
		return clearData();
	}
	//----------------------------------------------------------------
	bool TerrainCenterManager::generateCenters( FileHandleVtr* vtrfilehandle )
	{
		assert( vtrfilehandle != NULL );
		if ( vtrfilehandle == NULL )
		{
			return false;
		}

		assert( _centerLayers.empty() == true );

		VtrHeaderPtr pheader = 
			vtrfilehandle->getHeader();
		assert( pheader.isNull() == false );

		int layernum = pheader->numOfCenterLayers;


		for ( int i = 0 ; i < layernum ; ++ i )
		{
			if ( i == (layernum - 1) )
			{
				_centerLayers.push_back( new TerrainCenter( vtrfilehandle , i , true ) );
			}
			else
			{
				_centerLayers.push_back( new TerrainCenter( vtrfilehandle , i , false ) );
			}
		}

		assert( _centerLayers.empty() == false );

 
		return true;
	}
	//----------------------------------------------------------------
	TerrainCenter* TerrainCenterManager::getSuitableCenter(
		const int& layer )
	{
		assert( _centerLayers.empty() == false );
		assert( layer >= 0 );

		if ( layer >= ( _centerLayers.size() - 1 )  )
		{
			return _centerLayers[ _centerLayers.size() - 1 ];
		}

		return _centerLayers[ layer ];
	}
	//----------------------------------------------------------------
	bool TerrainCenterManager::clearData()
	{
		TerrainCenterPtrVec::iterator iter = _centerLayers.begin();
		TerrainCenterPtrVec::iterator iter_end = _centerLayers.end();

		for ( ; iter != iter_end ; ++iter )
		{
			TerrainCenter* curcenter = *iter;
			delete curcenter;
		}

		_centerLayers.clear();
		return true;
	}
	//----------------------------------------------------------------
	ElevationItemVector TerrainCenterManager::getContainedElevationItems()
	{
		ElevationItemVector ret;

		TerrainCenterPtrVec::iterator iter = _centerLayers.begin();
		TerrainCenterPtrVec::iterator iter_end = _centerLayers.end();

		for (; iter != iter_end ; ++ iter )
		{
			TerrainCenter* curcenter = *iter;

			for ( int i = 0 ; i < 4 ; ++ i )
			{
				ret.push_back( curcenter->_curElevItem[i] );
			}
		}

		return ret;
	}
	//----------------------------------------------------------------
	void TerrainCenterManager::dumpElevationBufferToHeightMap()
	{
		TerrainCenterPtrVec::iterator iter = _centerLayers.begin();
		TerrainCenterPtrVec::iterator iter_end = _centerLayers.end();

		for (; iter != iter_end ; ++ iter )
		{
			TerrainCenter* curcenter = *iter;

			for ( int i = 0 ; i < 4 ; ++ i )
			{
				if ( curcenter->_curElevItem[i]->isEmptyItem() == false )
				{
					curcenter->_curElevItem[i]->getElevationByLod( 
						VGLOD_CLEAR )->dumpBufferToHeightMap();
				}
			}
		}
	}
	//----------------------------------------------------------------
	bool TerrainCenterManager::reloadAllCenters()
	{
		TerrainCenterPtrVec::iterator iter = _centerLayers.begin();
		TerrainCenterPtrVec::iterator iter_end = _centerLayers.end();

		for (; iter != iter_end ; ++ iter )
		{
			TerrainCenter* curcenter = *iter;

			curcenter->reload();
		}

		dumpElevationBufferToHeightMap();

		return true;
	}
	//----------------------------------------------------------------

}// end of namespace vgTerritory
