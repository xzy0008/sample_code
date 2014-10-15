

#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerrainCenter.h>
#include <vgTerritory/vgtTerrainManager.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	TerrainCenter::TerrainCenter( FileHandleVtr* vtrfile , const int& layer ,
		bool islastlayer )
	{
		_isLastLayer = islastlayer;

		_curBlockPosX = -1;
		_curBlockPosZ = -1;
		_vtrFilehandle = vtrfile;

		assert( _vtrFilehandle != NULL );

		_curLayer = layer;
		assert( _curLayer >= 0 );

		// 这里获得指针是为了方便调试
		VtrHeader* vtrheader = vtrfile->getHeader().getPointer();

		assert( vtrheader != NULL );
	
		//------------------------------------------
		// 开始赋值_prefix
		//------------------------------------------
		std::ostringstream o;
		o << String( vtrheader->name ) << "_level" << layer << '_';

		_prefix = o.str().c_str();

		//------------------------------------------
		// 开始计算blockwidth
		//------------------------------------------
		int n = vtrheader->N;
		assert( n > 6 );
		assert( n <= 8 );

		float cellsize = vtrheader->cellsize;

		_blockWidth = pow( 2.0f, n ) * cellsize * pow( 2.0f , layer );


		// 其他
		_elevMgr = ElevationManager::getSingletonPtr();

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_curElevItem[i] = _elevMgr->getEmptyElevationItem();
			_prevElevItem[i] = _elevMgr->getEmptyElevationItem();
		}

#if VGT_USE16X16

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_cornerItem[i] = NULL;
			_prevCornerItem[i] = NULL;
		}

		for ( int i = 0 ; i < 8 ; ++i )
		{
			_upItem[i] = NULL;
			_prevUpItem[i] = NULL;
		}
#endif


		_absCenterX = 0.0f;
		_absCenterZ = 0.0f;
	}
	//----------------------------------------------------------------
	TerrainCenter::~TerrainCenter()
	{

	}
	//----------------------------------------------------------------
	void TerrainCenter::updateImpl( const int& xblockpos , const int& zblockpos )
	{

		const int __vgt_LEFT_UP	 = 0;
		const int __vgt_LEFT_DOWN = 1;
		const int __vgt_RIGHT_UP = 2;
		const int __vgt_RIGHT_DOWN = 3;

		_curBlockPosX = xblockpos;
		_curBlockPosZ = zblockpos;

		_absCenterX = _blockWidth * _curBlockPosX;
		_absCenterZ = _blockWidth * _curBlockPosZ;

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_prevElevItem[i] = _curElevItem[i];
		}
#if __vgt_USE16X16
		for ( int i = 0 ; i < 4 ; ++i )
		{
			_prevCornerItem[i] = _cornerItem[i];
		}

		for ( int i = 0 ; i < 8 ; ++i )
		{
			_prevUpItem[i] = _upItem[i];
		}
#endif

		std::ostringstream o;
		o << _prefix << _curBlockPosX << '_' << _curBlockPosZ << ".vgtr";
		_curElevItem[ __vgt_RIGHT_DOWN ] = 
			_elevMgr->getElevationItem( o.str() , true );

		std::ostringstream o1;
		o1 << _prefix << _curBlockPosX - 1 << '_' << _curBlockPosZ << ".vgtr";
		_curElevItem[ __vgt_LEFT_DOWN ] = 
			_elevMgr->getElevationItem( o1.str() , true );

		std::ostringstream o2;
		o2 << _prefix << _curBlockPosX << '_' << _curBlockPosZ - 1 << ".vgtr";
		_curElevItem[ __vgt_RIGHT_UP ] = 
			_elevMgr->getElevationItem( o2.str() , true );

		std::ostringstream o3;
		o3 << _prefix << _curBlockPosX - 1 << '_' << _curBlockPosZ - 1 << ".vgtr";
		_curElevItem[ __vgt_LEFT_UP ] = 
			_elevMgr->getElevationItem( o3.str() , true );

#if VGT_USE16X16
		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX - 2 << '_' << _curBlockPosZ - 2 << ".vgtr";
			_cornerItem[ 0 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX - 2 << '_' << _curBlockPosZ + 2 << ".vgtr";
			_cornerItem[ 1 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX + 2 << '_' << _curBlockPosZ - 2 << ".vgtr";
			_cornerItem[ 2 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX + 2 << '_' << _curBlockPosZ + 2 << ".vgtr";
			_cornerItem[ 3 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		//----------------------------------------------------------------

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX + 1 << '_' << _curBlockPosZ + 2 << ".vgtr";
			_upItem[ 0 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX + 2 << '_' << _curBlockPosZ + 1 << ".vgtr";
			_upItem[ 1 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX + 1 << '_' << _curBlockPosZ - 2 << ".vgtr";
			_upItem[ 2 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX - 2 << '_' << _curBlockPosZ + 1 << ".vgtr";
			_upItem[ 3 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX - 1 << '_' << _curBlockPosZ + 2 << ".vgtr";
			_upItem[ 4 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX + 2 << '_' << _curBlockPosZ - 1 << ".vgtr";
			_upItem[ 5 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX - 2 << '_' << _curBlockPosZ - 1 << ".vgtr";
			_upItem[ 6 ] = _elevMgr->getElevationItem( o.str() , true );
		}

		{
			std::ostringstream o;
			o3 << _prefix << _curBlockPosX - 1 << '_' << _curBlockPosZ - 2 << ".vgtr";
			_upItem[ 7 ] = _elevMgr->getElevationItem( o.str() , true );
		}

#endif
		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _curElevItem[i] != NULL )
			{
				_curElevItem[i]->addViewRef();
			}
		}

#if VGT_USE16X16
		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _cornerItem[i] != NULL )
			{
				_cornerItem[i]->addViewRef();
			}
		}

		for ( int i = 0 ; i < 8 ; ++i )
		{
			if ( _upItem[i] != NULL )
			{
				_upItem[i]->addViewRef();
			}
		}
#endif
		//----------------------------------------------------------------

		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _prevElevItem[i] != NULL )
			{
				_prevElevItem[i]->releaseViewRef();
			}
		}

#if VGT_USE16X16

		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _prevCornerItem[i] != NULL )
			{
				_prevCornerItem[i]->releaseViewRef();
			}
		}

		for ( int i = 0 ; i < 8 ; ++i )
		{
			if ( _prevUpItem[i] != NULL )
			{
				_prevUpItem[i]->releaseViewRef();
			}
		}
#endif
	}
	//----------------------------------------------------------------
	void TerrainCenter::update( const float& curpos_x, const float& curpos_z )
	{
		//------------------------------------------
		// 首先需要转换
		//------------------------------------------
		int tmpBlockPosX = floor( curpos_x / _blockWidth  + 0.5f );
		int tmpBlockPosZ = floor( curpos_z / _blockWidth  + 0.5f );

		//确定是正数
		//if ( tmpBlockPosX < 1 )
		//{
		//	tmpBlockPosX = 1;
		//}

		//if ( tmpBlockPosZ < 1 )
		//{
		//	tmpBlockPosZ = 1;
		//}

		// 最后一层不参与更新
		if ( _isLastLayer == true )
		{
			tmpBlockPosX = 1;
			tmpBlockPosZ =1;
		}

		if ( tmpBlockPosX == _curBlockPosX && 
			tmpBlockPosZ == _curBlockPosZ )
		{
			return;
		}

		// 此时需要更新
		updateImpl( tmpBlockPosX , tmpBlockPosZ );
	}

	float TerrainCenter::getLogicCenterX()
	{
		// 地形偏移时打开
		return -_absCenterX /*- TerrainManager::getSingleton().getGlobalOffsetX()*/;
	}
	//----------------------------------------------------------------
	float TerrainCenter::getLogicCenterZ()
	{
		return -_absCenterZ /*- TerrainManager::getSingleton().getGlobalOffsetZ()*/;
	}
	//----------------------------------------------------------------
	bool TerrainCenter::isLoadedFully()
	{
		for ( int i = 0; i < 4 ; ++ i )
		{
			if ( _curElevItem[i] != NULL )
			{
				if ( _curElevItem[i]->isLoaded() == false )
				{
					return false;
				}
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	bool TerrainCenter::reload()
	{
		//------------------------------------------
		// 重复项不需要包含.
		//------------------------------------------

		std::set<ElevationItem*> itemset;

		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _prevElevItem[i] != NULL )
			{
				if ( _prevElevItem[i]->isEmptyItem() == false )
				{
					itemset.insert( _prevElevItem[i] );
				}
			}
		}

		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _curElevItem[i] != NULL )
			{
				if ( _curElevItem[i]->isEmptyItem() == false )
				{
					itemset.insert( _curElevItem[i] );
				}
			}
		}

		//------------------------------------------
		// 开始更新
		//------------------------------------------
		std::set<ElevationItem*>::iterator iter = itemset.begin();
		std::set<ElevationItem*>::iterator iter_end = itemset.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ElevationItem* itm = *iter;

			assert( itm != NULL );
			assert( itm->isEmptyItem() == false );

			int refcount = itm->getViewRef();

			if ( refcount <= 0 )
			{
				continue;
			}

			while( itm->getViewRef() != 0 )
			{
				itm->releaseViewRef();
			}

			while( itm->getViewRef() != refcount )
			{
				itm->addViewRef();
			}
		}
		
		return true;
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
