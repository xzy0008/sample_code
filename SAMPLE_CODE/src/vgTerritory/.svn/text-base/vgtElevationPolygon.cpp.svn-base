



#include <vgStableHeaders.h>
#include <vgTerritory/vgtElevationPolygon.h>
#include <vgKernel/vgkPointInPolygon.h>


namespace vgTerritory {
	
	
	ElevationBound ElevationPolygon::s_uvTestBound( Vec2(0, 0) , Vec2(1, 1) );
	
	
	//----------------------------------------------------------------
	ElevationBound ElevationPolygon::calculateBound( const Vec2Vector* const vertices )
	{
		int size  = vertices->size();

		assert( size > 2 );

		Vec2 maxvec2 = (*vertices)[0];
		Vec2 minvec2 = (*vertices)[0];

		for ( int i = 0 ; i < size ; ++ i )
		{
			if ( minvec2.x > (*vertices)[i].x )
			{
				minvec2.x = (*vertices)[i].x;
			}

			if ( minvec2.y > (*vertices)[i].y )
			{
				minvec2.y = (*vertices)[i].y;
			}

			if ( maxvec2.x < (*vertices)[i].x )
			{
				maxvec2.x = (*vertices)[i].x;
			}

			if ( maxvec2.y < (*vertices)[i].y )
			{
				maxvec2.y = (*vertices)[i].y;
			}
		}

		return ElevationBound( minvec2 , maxvec2 );

	}
	//----------------------------------------------------------------
	Vec2Vector* ElevationPolygon::getCopyAndMappingPoints( ElevationItem* item )
	{
		Vec2Vector* ret = getCopyOfPoints();

		Vec2Vector::iterator iter = ret->begin();
		Vec2Vector::iterator iter_end = ret->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter) = item->mappingVertexToGrid( *iter );
		}

		return ret;
	}
	//----------------------------------------------------------------
	bool ElevationPolygon::filterElevationItem( ElevationItem* item , 
		void* buffer , const long& buffersize )
	{
		assert( item != NULL );

		if ( item->isEmptyItem() )
		{
			return false;
		}

		assert( buffersize %4 == 0 );
		assert( buffersize != 0 );

		if ( buffer == NULL || buffersize == 0 || buffersize %4 != 0 )
		{
			return false;
		}

		//------------------------------------------
		// 首先进行包围盒相交测试
		//------------------------------------------
		assert( _bound.isSafe() );

		if ( testIntersectWithItem( item ) == false )
		{
			return false;
		}

		//------------------------------------------
		// 此时相交,进行过滤处理
		//------------------------------------------
		Vec2VectorPtr mappingvecs;
		mappingvecs.bind( getCopyAndMappingPoints( item ) );
		assert( mappingvecs.getPointer() != NULL );

		if ( mappingvecs->empty() )
		{
			return false;
		}

		ElevationBound boundtest = calculateBound( mappingvecs.getPointer() );

		PointInPolygon pip( mappingvecs->size() , &(*mappingvecs)[0] );

		float* buf = (float*)buffer;
		assert( buf != NULL );

		//------------------------------------------
		// 修改buffer
		//------------------------------------------
		int w = item->getHeightMapWidth();
		assert( buffersize == w * w * 4 );

		Vec2 t;

		for ( int i = 0 ; i < w  ; ++ i )
		{
			for ( int j  = 0 ; j < w ; ++ j )
			{
				t.x = i;
				t.y = j;

				if ( boundtest.testInside( t ) )
				{
					if ( pip.contains( t ) )
					{ 
						buf[ i + j * w ] = item->mappingHeightToGrid( _height );
					}
				}
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	bool ElevationPolygon::testIntersectWithItem( ElevationItem* item )
	{
		ElevationBound tmp;

		tmp.minPos = item->mappingVertexToUV( _bound.minPos );
		tmp.maxPos = item->mappingVertexToUV( _bound.maxPos );

		return tmp.testIntersection( s_uvTestBound );
	}
	//----------------------------------------------------------------
	bool ElevationPolygon::filterElevationItemPoint( ElevationItem* item , float& out_height , int pos_x , int pos_y )
	{
		assert( item != NULL );

		if ( item->isEmptyItem() )
		{
			return false;
		}

		assert( pos_x >= 0 );
		assert( pos_y >= 0 );

		//------------------------------------------
		// 首先进行包围盒相交测试
		//------------------------------------------
		assert( _bound.isSafe() );

		if ( testIntersectWithItem( item ) == false )
		{
			return false;
		}

		//------------------------------------------
		// 此时相交,进行过滤处理
		//------------------------------------------
		Vec2VectorPtr mappingvecs;
		mappingvecs.bind( getCopyAndMappingPoints( item ) );
		assert( mappingvecs.getPointer() != NULL );

		if ( mappingvecs->empty() )
		{
			return false;
		}

		ElevationBound boundtest = calculateBound( mappingvecs.getPointer() );

		PointInPolygon pip( mappingvecs->size() , &(*mappingvecs)[0] );


		//------------------------------------------
		// 修改buffer
		//------------------------------------------
		int w = item->getHeightMapWidth();
		assert( pos_x < w );
		assert( pos_y < w );

		Vec2 t;

		t.x = pos_x;
		t.y = pos_y;

		if ( boundtest.testInside( t ) )
		{
			if ( pip.contains( t ) )
			{ 
				out_height = ( _height );
			}
		}

		return true;
	}
	//----------------------------------------------------------------





}// end of namespace vgTerritory
