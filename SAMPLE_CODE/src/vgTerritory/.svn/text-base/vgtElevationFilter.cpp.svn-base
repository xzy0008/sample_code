




#include <vgStableHeaders.h>
#include <vgTerritory/vgtElevationFilter.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgAsyn/vgaIoRequestWrite.h>
#include <vgKernel/vgkTrace.h>

namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	bool ElevationFilter::doFilter( ElevationItem* item , void* buffer ,
		const long& buffersize )
	{
		if ( _enableFiltering == false )
		{
			return true;
		}

		//------------------------------------------
		// 没有相交,则直接返回
		//------------------------------------------
		if ( testPolygonIntersectWithItem( item) == false )
		{
			return false;
		}

		assert( item->isEmptyItem() == false );
		assert( item->isLoaded() == true );

		//------------------------------------------
		// 此时相交,改变数据
		//------------------------------------------
		ElevationPolygonPtrVector::iterator iter = _polygons.begin();
		ElevationPolygonPtrVector::iterator iter_end = _polygons.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ElevationPolygon* poly = *iter;

			poly->filterElevationItem( item , buffer , buffersize );
		}

		return true;
	}
	//----------------------------------------------------------------
	void ElevationFilter::doFilterInMemory()
	{
		ElevationItemVector items = 
			TerrainCenterManager::getSingleton().getContainedElevationItems();

		ElevationItemVector::iterator iter = items.begin();
		ElevationItemVector::iterator iter_end = items.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ElevationItem* item = *iter;

			//------------------------------------------
			// 在内存中过滤.
			//------------------------------------------
			ElevationPolygonPtrVector::iterator iter = _polygons.begin();
			ElevationPolygonPtrVector::iterator iter_end = _polygons.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				ElevationPolygon* poly = *iter;

				if ( item->isEmptyItem() || item->isLoaded() == false )
				{
					continue;
				}

				void* buffer = item->getElevationByLod( VGLOD_CLEAR )->getHeightMapBuffer();
				long w = item->getElevationByLod( VGLOD_CLEAR )->getBufferHeightMapWidth();

				poly->filterElevationItem( item , buffer , w * w * sizeof(float) );
			}
		}

		//------------------------------------------
		// 把更改映射到显存.
		//------------------------------------------
		TerrainCenterManager::getSingleton().dumpElevationBufferToHeightMap();

		return;
	}

	//----------------------------------------------------------------
	bool ElevationFilter::doFilterAndSave()
	{
		using namespace vgAsyn;

		// 得到内存中所有的item
		ElevationItemVectorPtr items;
		items.bind(
			ElevationManager::getSingleton().getElevationItemsByLevel( -1 ) );

		if ( items.isNull() == true )
		{
			return false;
		}

		ElevationItemVector::iterator iter = items->begin();
		ElevationItemVector::iterator iter_end = items->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ElevationItem* itm = *iter;

			if ( testPolygonIntersectWithItem( itm ) )
			{
				//------------------------------------------
				// 此时相交,需要读入item到内存,过滤,最后保存
				//------------------------------------------
				IoRequest* readreq = 
					itm->getElevationByLod( VGLOD_CLEAR )->getIoRequest();

				assert( readreq != NULL );

				// 为了获取buffer的指针,确保不会被删除.
				readreq->setDeleteBufferFlag( false );

				// 开始读入,readreq不会被自动删除.
				readreq->sendRequestAndDoAsynHandlerFunc( true );

				char* buffer = readreq->getBuffer();
				assert( buffer != NULL );

				long buf_size  = readreq->getBufferSize();
				assert( buf_size != 0 );

				FileInfo* fileinfo = readreq->getFileInfoClone();
				
				delete readreq;
				readreq = NULL;

				//------------------------------------------
				// 进行过滤
				//------------------------------------------
				bool filterok = doFilter( itm , buffer , buf_size );
				assert( filterok == true );

				//------------------------------------------
				// 开始保存, buffer在IoRequestWrite负责删除.
				//------------------------------------------
				IoRequestWrite writereq( fileinfo ,  buffer );

				writereq.sendIoRequestWrite();
			}
		}


		//------------------------------------------
		// 清空Polygons
		//------------------------------------------
		clearPolygons();

		return true;
	}
	//----------------------------------------------------------------(
	bool ElevationFilter::testPolygonIntersectWithItem( ElevationItem* item )
	{
		ElevationPolygonPtrVector::iterator iter = _polygons.begin();
		ElevationPolygonPtrVector::iterator iter_end = _polygons.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ElevationPolygon* poly = *iter;

			 if ( poly->testIntersectWithItem( item ) )
			 {
				 return true;
			 }
		}

		return false;
	}
	//----------------------------------------------------------------
	void ElevationFilter::clearPolygons()
	{
		ElevationPolygonPtrVector::iterator iter  = _polygons.begin();
		ElevationPolygonPtrVector::iterator iter_end = _polygons.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			delete *iter;
		}

		_polygons.clear();
	}	
	//----------------------------------------------------------------
	bool ElevationFilter::doFilterPoint( ElevationItem* item , float& out_height , int pos_x , int pos_y )
	{
		if ( _enableFiltering == false )
		{
			return true;
		}

		//------------------------------------------
		// 没有相交,则直接返回
		//------------------------------------------
		if ( testPolygonIntersectWithItem( item) == false )
		{
			return false;
		}

		assert( item->isEmptyItem() == false );

		//------------------------------------------
		// 此时相交,改变数据
		//------------------------------------------
		ElevationPolygonPtrVector::iterator iter = _polygons.begin();
		ElevationPolygonPtrVector::iterator iter_end = _polygons.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ElevationPolygon* poly = *iter;

			poly->filterElevationItemPoint( item , out_height , pos_x , pos_y );
		}

		return true;
	}

	ElevationFilter::~ElevationFilter()
	{
		clearPolygons();
		VGK_TRACE(_T("ElevationFilter destroyed."));
	}

	ElevationFilter::ElevationFilter() : Singleton<ElevationFilter>( 
		VGK_SINGLETON_LEFE_ELEVATIONFILTER )
	{
		_enableFiltering = true;
		VGK_TRACE(_T("ElevationFilter created."));
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
