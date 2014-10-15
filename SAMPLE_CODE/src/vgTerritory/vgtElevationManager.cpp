


#include <vgStableHeaders.h>
#include <vgTerritory/vgtElevationManager.h>
#include <vgAsyn/vgaIoServer.h>
#include <vgImage/vgiImageManager.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgImage/vgiTextureIoRequestDispatcher.h>
#include <vgImage/vgiImageManager.h>
#include <vgImage/vgiTextureManager.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkSystemUtility.h>

#include <gdal/ogr_geometry.h>

namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	FileHandleVtr* ElevationManager::openVtrFile( const String& vtrfilename )
	{
		assert( _vtrFileHandles.empty() == true );
		assert( _mainVtrFileHandle == NULL );

		FileHandleVtr* mainfilehandle = new FileHandleVtr( vtrfilename );

		bool openok = mainfilehandle->open();
		assert( openok == true );

		if ( openok == false )
		{
			delete mainfilehandle;
			return NULL;
		}

		//------------------------------------------
		// 注意需要关联
		//------------------------------------------
		bool assok =
			vgAsyn::IoServer::getSingleton().associateWithFileHandle( mainfilehandle );
		assert( assok == true );


		_mainVtrFileHandle = mainfilehandle;
		insertToVtrMap( _mainVtrFileHandle );

		//------------------------------------------
		// 开始插入其他的vtr文件
		//------------------------------------------
		FileHandleVtr* tmp = _mainVtrFileHandle->openNextVtrFile();
		while ( tmp != NULL )
		{
			bool assok =
				vgAsyn::IoServer::getSingleton().associateWithFileHandle( tmp );
			assert( assok == true );

			if ( assok == false )
			{
				std::ostringstream o;
				o << "操作文件: " << tmp->getFilePath() << "时失败.";
				MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );

				delete tmp;
				break;
			}

			insertToVtrMap( tmp );
			tmp = tmp->openNextVtrFile();
		}

		//------------------------------------------
		// 创建空ElevationItem
		//------------------------------------------
		assert( _emptyElevItem  == NULL );
		_emptyElevItem = new ElevationItem( NULL , _mainVtrFileHandle );


		//------------------------------------------
		// 成功之后,在这里计算场景的面积
		//------------------------------------------
		_validSceneBoundMinX = 0.0f;
		_validSceneBoundMinZ = 0.0f;
		_validSceneBoundMaxX = 0.0f;
		_validSceneBoundMaxZ = 0.0f;

		calculateValidSceneBound();

		return _mainVtrFileHandle;
	}
	//----------------------------------------------------------------
	ElevationItem* ElevationManager::getElevationItem( const String& itemname  ,
		const bool& return_empty_item )
	{
		ElevationItem* ret = NULL;

		FileHandleVtrPtrMap::iterator iter = _vtrFileHandles.begin();
		FileHandleVtrPtrMap::iterator iter_end = _vtrFileHandles.end();

		for ( ; iter != iter_end ; ++ iter  )
		{
			FileHandleVtr* vtrhandle = iter->second;
			ElevationItem* getitem = vtrhandle->getElevationItem( itemname );
			
			if ( getitem != NULL )
			{
				ret = getitem;
				break;
			}
		}

		if ( ret == NULL )
		{
			if ( return_empty_item == true )
			{
				ret = _emptyElevItem;
			}
		}

		return ret;
	}
	//----------------------------------------------------------------
	ElevationItem* ElevationManager::getElevationItem( const long& layer , 
		const long& chunkx, const long& chunkz , const bool& return_empty_item )
	{
		assert( _mainVtrFileHandle != NULL );

		if ( chunkx < 0 || chunkz < 0 )
		{
			return return_empty_item == true ? _emptyElevItem : NULL;
		}

		std::ostringstream o;
		o << _mainVtrFileHandle->getTerrainName() << "_level" << layer << '_' 
			<< chunkx << '_' << chunkz << ".vgtr";

		return getElevationItem( o.str() , return_empty_item );
	}
	//----------------------------------------------------------------
	bool ElevationManager::clearData()
	{
		if ( _emptyElevItem != NULL )
		{
			delete _emptyElevItem;
			_emptyElevItem = NULL;
		}

		FileHandleVtrPtrMap::iterator iter = _vtrFileHandles.begin();
		FileHandleVtrPtrMap::iterator iter_end = _vtrFileHandles.end();

		for ( ; iter != iter_end ; ++ iter  )
		{
			delete iter->second;
		}
		_vtrFileHandles.clear();

		_mainVtrFileHandle = NULL;

		_mainVgiFilehandle = NULL;

		//_vgiFilehandle = NULL;

		return true;
	}
	//----------------------------------------------------------------
	bool ElevationManager::getWholeSceneBound( float& out_x , float& out_z )
	{
		if ( _mainVtrFileHandle == NULL  )
		{
			return false;
		}

		float cellsize  = _mainVtrFileHandle->getHeader()->cellsize;

		out_x = _mainVtrFileHandle->getHeader()->xTotalNum * cellsize;
		out_z = _mainVtrFileHandle->getHeader()->zTotalNum * cellsize;

		return true;
	}
	//----------------------------------------------------------------
	ElevationItemVector* ElevationManager::getElevationItemsByLevel( 
		const long& level )
	{
		assert( level >= -1 );

		if ( _vtrFileHandles.empty() == true )
		{
			return NULL;
		}

		ElevationItemVector* ret = new ElevationItemVector;
		
		FileHandleVtrPtrMap::iterator iter = _vtrFileHandles.begin();
		FileHandleVtrPtrMap::iterator iter_end = _vtrFileHandles.end();

		for ( ; iter != iter_end ; ++ iter  )
		{
			FileHandleVtr* vtrhandle = iter->second;

			ElevationItemMap* items = vtrhandle->getElevationItemsPtr();

			ElevationItemMap::iterator iiter = items->begin();
			ElevationItemMap::iterator iiter_end = items->end();

			for ( ; iiter != iiter_end ; ++ iiter )
			{
				ElevationItem* itm = iiter->second;

				if ( level == -1 )
				{
					ret->push_back( itm );
				}
				else  if ( itm->getLevel() == level )
				{
					ret->push_back( itm );
				}
			}
		}

		if ( ret->empty() == true )
		{
			delete ret;
			return NULL;
		}

		return ret;
	}
	//----------------------------------------------------------------
	bool ElevationManager::getValidSceneBound( 
		float& out_min_x , float& out_min_z , float& out_max_x , float& out_max_z )
	{
		if ( _validSceneBoundMaxX <= 0.0f || 
			_validSceneBoundMaxZ <= 0.0f )
		{
			return false;
		}

		out_min_x = _validSceneBoundMinX;
		out_min_z = _validSceneBoundMinZ;
		out_max_x = _validSceneBoundMaxX;
		out_max_z = _validSceneBoundMaxZ;

		return true;
	}
	//----------------------------------------------------------------
	ElevationBound ElevationManager::getValidSceneBound()
	{
		ElevationBound ret;

		getValidSceneBound( ret.minPos.x , ret.minPos.y , ret.maxPos.x , ret.maxPos.y );

		assert( ret.isSafe() );
		return ret;
	}
	//----------------------------------------------------------------
	bool ElevationManager::calculateValidSceneBound()
	{
		assert( _mainVtrFileHandle != NULL );

		if ( _vtrFileHandles.empty() == true )
		{
			return false;
		}

		long chunkminx = 0;
		long chunkminz = 0;
		long chunkmaxx = 0;
		long chunkmaxz = 0;

		bool first_itm = true;

		FileHandleVtrPtrMap::iterator iter = _vtrFileHandles.begin();
		FileHandleVtrPtrMap::iterator iter_end = _vtrFileHandles.end();

		for ( ; iter != iter_end ; ++ iter  )
		{
			FileHandleVtr* vtrhandle = iter->second;

			ElevationItemMap* items = vtrhandle->getElevationItemsPtr();

			ElevationItemMap::iterator iiter = items->begin();
			ElevationItemMap::iterator iiter_end = items->end();

			for ( ; iiter != iiter_end ; ++ iiter )
			{
				ElevationItem* itm = iiter->second;

				if ( itm->getLevel() != 0 || itm->isEmptyItem() )
				{
					continue;
				}

				long x = 0;
				long z = 0;

				itm->getBlockNumber( x , z );

				if ( first_itm )
				{
					first_itm = false;
					chunkmaxx = x;
					chunkmaxz = z;
					chunkminx = x;
					chunkminz = z;
				}

				chunkmaxx = VGT_MAX( chunkmaxx , x );
				chunkmaxz = VGT_MAX( chunkmaxz , z );
				chunkminx = VGT_MIN( chunkminx , x );
				chunkminz = VGT_MIN( chunkminz , z );
			}
		}

		long pow_of_n = pow( 2.0f , _mainVtrFileHandle->getHeader()->N );
		float cellsize = _mainVtrFileHandle->getHeader()->cellsize;

		/*if ( chunkmaxx == 0 ||
			chunkmaxz == 0 )
		{
			assert(0);
			return false;
		}*/
		

		_validSceneBoundMinX = ( chunkminx )* pow_of_n * cellsize;
		_validSceneBoundMinZ = ( chunkminz )* pow_of_n * cellsize;
		_validSceneBoundMaxX = ( chunkmaxx  + 1 )* pow_of_n * cellsize;
		_validSceneBoundMaxZ = ( chunkmaxz + 1 )* pow_of_n * cellsize;

		return true;
	}
	//----------------------------------------------------------------
	ElevationItemVectorPtr ElevationManager::getIntersectedItemsByBound( 
		const ElevationBound& bound )
	{
		ElevationItemVectorPtr ret( new ElevationItemVector );

		FileHandleVtrPtrMap::iterator iter = _vtrFileHandles.begin();
		FileHandleVtrPtrMap::iterator iter_end = _vtrFileHandles.end();

		for ( ; iter != iter_end ; ++ iter  )
		{
			FileHandleVtr* vtrhandle = iter->second;

			ElevationItemMap* items = vtrhandle->getElevationItemsPtr();

			ElevationItemMap::iterator iiter = items->begin();
			ElevationItemMap::iterator iiter_end = items->end();

			for ( ; iiter != iiter_end ; ++ iiter )
			{
				ElevationItem* itm = iiter->second;

				bool testres = itm->testIntersection( bound );

				if ( testres == true )
				{
					ret->push_back( itm );
				}
			}
		}

		if ( ret->empty() == true )
		{
			return ElevationItemVectorPtr();
		}

		return ret;
	}

	//---------------------------------------------------------------
	ElevationItemVectorPtr ElevationManager::getIntersectedItemsByPolygon( 
		const Vec3Vector* pointsVec )
	{
		assert( pointsVec != NULL );
		if ( pointsVec == NULL )
		{
			return ElevationItemVectorPtr();
		}

		ElevationItemVectorPtr ret( new ElevationItemVector );

		FileHandleVtrPtrMap::iterator iter = _vtrFileHandles.begin();
		FileHandleVtrPtrMap::iterator iter_end = _vtrFileHandles.end();

		Vec2 minPos = ElevationBound::UNIT_BOUND.minPos;
		Vec2 maxPos = ElevationBound::UNIT_BOUND.maxPos;

		for ( ; iter != iter_end ; ++ iter  )
		{
			FileHandleVtr* vtrhandle = iter->second;

			ElevationItemMap* items = vtrhandle->getElevationItemsPtr();

			ElevationItemMap::iterator iiter = items->begin();
			ElevationItemMap::iterator iiter_end = items->end();

			for ( ; iiter != iiter_end ; ++ iiter )
			{
				ElevationItem* itm = iiter->second;
				
				// 1. 用ElevationItem的Bound构造OGRPolygon
				OGRGeometry* pGeoLine1 = OGRGeometryFactory::createGeometry( wkbLinearRing );
				OGRLinearRing* pLinearRing1 = dynamic_cast<OGRLinearRing*>( pGeoLine1 );

				pLinearRing1->addPoint( minPos.x, minPos.y );  // 1 -- ( 0, 0 )
				pLinearRing1->addPoint( maxPos.x, minPos.y );  // 2 -- ( 1, 0 )
				pLinearRing1->addPoint( maxPos.x, maxPos.y );  // 3 -- ( 1, 1 )
				pLinearRing1->addPoint( minPos.x, maxPos.y );  // 4 -- ( 0, 1 )
				pLinearRing1->addPoint( minPos.x, minPos.y );  // 1 -- ( 0, 0 )

				OGRGeometry* pGeoPoly1 = OGRGeometryFactory::createGeometry( wkbPolygon );
				OGRPolygon* pPolygon1 = dynamic_cast<OGRPolygon*>( pGeoPoly1 );
				pPolygon1->addRing( pLinearRing1 );


				// 2. 用选区边界点经映射后构造为OGRPolygon
				OGRGeometry* pGeoLine2 = OGRGeometryFactory::createGeometry( wkbLinearRing );
				OGRLinearRing* pLinearRing2 = dynamic_cast<OGRLinearRing*>( pGeoLine2 );

				for ( int i = 0; i < pointsVec->size(); i++ )
				{
					Vec2 ptProj( (pointsVec->at(i)).x, (pointsVec->at(i)).z );
					Vec2 addPt = itm->mappingVertexToUV( ptProj );
					pLinearRing2->addPoint( addPt.x, addPt.y );
				}
				Vec2 ptProj( (pointsVec->at(0)).x, (pointsVec->at(0)).z );
				Vec2 addPt = itm->mappingVertexToUV( ptProj );
				pLinearRing2->addPoint( addPt.x, addPt.y );

				OGRGeometry* pGeoPoly2 = OGRGeometryFactory::createGeometry( wkbPolygon );
				OGRPolygon* pPolygon2 = dynamic_cast<OGRPolygon*>( pGeoPoly2 );
				pPolygon2->addRing( pLinearRing2 );


				// 3. 前两步的OGRPolygon进行相交，相含测试
				OGRBoolean bIntersect = pGeoPoly1->Intersect( pGeoPoly2 );  // 测试是否1相交2
				if ( bIntersect )
				{
					ret->push_back( itm );

					OGRBoolean bWithIn = pGeoPoly1->Within( pGeoPoly2 ); // 测试是否1在2中--用于效率优化
					if ( bWithIn )
					{
						assert( !itm->getStateWithInPolygon() );
						itm->setStateWithInPolygon( true );
					}

					OGRGeometry* pIntersectOgr = pGeoPoly1->Intersection( pGeoPoly2 );
					assert( pIntersectOgr != NULL );
					
					assert( itm->getOgrPtr() == NULL );
					itm->setOgrGeoPtr( pIntersectOgr );
				}


				// 4. 释放OGR申请的内存空间
				OGRGeometryFactory::destroyGeometry( pLinearRing1 );
				OGRGeometryFactory::destroyGeometry( pPolygon1 );
				OGRGeometryFactory::destroyGeometry( pLinearRing2 );
				OGRGeometryFactory::destroyGeometry( pPolygon2 );

				pLinearRing1 = NULL;
				pLinearRing2 = NULL;
				pGeoPoly1 = NULL;
				pGeoPoly2 = NULL;
			}
		}

		if ( ret->empty() == true )
		{
			return ElevationItemVectorPtr();
		}

		return ret;
	}

	//---------------------------------------------------------------
	bool ElevationManager::addRefToAllElevationItems()
	{
		if ( _vtrFileHandles.empty() == true )
		{
			return false;
		}

		FileHandleVtrPtrMap::iterator iter = _vtrFileHandles.begin();
		FileHandleVtrPtrMap::iterator iter_end = _vtrFileHandles.end();

		for ( ; iter != iter_end ; ++ iter  )
		{
			FileHandleVtr* vtrhandle = iter->second;

			ElevationItemMap* items = vtrhandle->getElevationItemsPtr();

			ElevationItemMap::iterator iiter = items->begin();
			ElevationItemMap::iterator iiter_end = items->end();

			for ( ; iiter != iiter_end ; ++ iiter )
			{
				ElevationItem* itm = iiter->second;

				itm->addViewRef();
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	bool ElevationManager::importImageFileOnly( const String& VgiPathName )
	{
		if ( vgKernel::SystemUtility::checkFileExist( VgiPathName ) == false )
		{
			return false;
		}

		vgImage::FileHandleVgi* filehandle =
			vgImage::ImageManager::getSingleton().addImageAndAssociateWithIoServer(
			VgiPathName );

		if( filehandle == NULL )
		{
			std::ostringstream o;
			o << "导入文件:" << VgiPathName << "时出现错误.";
			::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
			return false;
		}

		bool add_rest = 
			vgImage::TextureManager::getSingleton().addTexture( filehandle );

		if( add_rest == false )
		{
			std::ostringstream o;
			o << "导入文件:" << VgiPathName << "时出现错误.";
			::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
			return false;
		}

		//------------------------------------------
		// 开始插入其他的文件
		//------------------------------------------
		vgImage::FileHandleVgi* tmp = filehandle->openNextFile();
		while ( tmp != NULL )
		{
			vgImage::FileHandleVgi* filehandle =
				vgImage::ImageManager::getSingleton().addImageAndAssociateWithIoServer(
				tmp );

			if( filehandle == NULL )
			{
				std::ostringstream o;
				o << "导入文件:" << tmp->getFilePath() << "错误.";
				::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
			}
			else
			{
				bool add_rest = 
					vgImage::TextureManager::getSingleton().addTexture( filehandle );

				if( add_rest == false )
				{
					std::ostringstream o;
					o << "导入文件:" << VgiPathName << "时出现错误.";
					::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
				}
			}

			tmp = tmp->openNextFile();
		}


		//------------------------------------------
		// 没有必要清空
		//------------------------------------------

		// 清空一下渲染队列
		//vgMesh::MeshManager::getSingleton().clearPrevRenderQueue();

		return true;
	}

	ElevationManager::ElevationManager() : Singleton<ElevationManager>( 
		VGK_SINGLETON_LEFE_ELEVATIONMGR )
	{
		_mainVgiFilehandle  = NULL;
		_emptyElevItem = NULL;
		//_elevItems = NULL;
		//_vtrFileHandle = NULL;
		_mainVtrFileHandle = NULL;
		_validSceneBoundMaxX = 0.0f;
		_validSceneBoundMaxZ = 0.0f;
		VGK_TRACE(_T("ElevationManager created."));
	}

	ElevationManager::~ElevationManager()
	{
		VGK_TRACE(_T("ElevationManager destroyed."));
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
