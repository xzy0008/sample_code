


#include <vgStableHeaders.h>
#include <vgShape/vgshMultiPoint.h>
#include <vgShape/vgshLayer.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkOpenGLSupport.h>


namespace vgShape {

	//----------------------------------------------------------------
	MultiPoint::MultiPoint( OGRFeature* feat , Layer* father ) 
		: Geometry( feat , father )
	{
		_wkbSize = -1;
		_wkbBuffer = NULL;
		_isOpenGLCoordinate = false;
		_callListId = 0;
		_box3d = Box3d::NULL_BOX;

	}

	//----------------------------------------------------------------
	void MultiPoint::renderUsingDisplayList()
	{
		//assert(0);
		if ( _wkbBuffer == NULL )
		{
			return;
		}

		VGK_CHECK_OPENGL_ERROR();

		if ( _callListId == 0 )
		{
			_callListId = glGenLists( 1 );   
			assert( _callListId != 0 );

			glNewList( _callListId, GL_COMPILE );
			renderOnceForDisplayList();
			glEndList();	
		}
		VGK_CHECK_OPENGL_ERROR();

		assert( _callListId != 0 );

		glPushMatrix();
		glCallList( _callListId );
		glPopMatrix();

		return;
	}
	//----------------------------------------------------------------
	bool MultiPoint::readDataFromOGRFeature( )
	{
		OGRFeature* feature = getOGRFeature();

		if ( feature == NULL )
		{
			return false;
		}

		// 利用智能指针析构.
		assert( feature  != NULL );
		OGRFeaturePtr featPtr( feature );

		// 开始读取wkb数据
		OGRGeometry* geo = featPtr->GetGeometryRef();
		assert( geo != NULL );

		//geo->getEnvelope(&_envelope);

		if ( wkbFlatten( geo->getGeometryType() ) != wkbMultiPoint )
		{
			assert(0);
			return false;
		}

		assert( wkbFlatten( geo->getGeometryType() )
			== wkbMultiPoint );

		OGRMultiPoint* points = ( OGRMultiPoint* )geo;

		VGSH_CHECK_OGR_ERROR();
		//------------------------------------------
		// 设定为25D模式
		//------------------------------------------
		int dimension = geo->getDimension();
		if ( dimension != 3 )
		{
			geo->setCoordinateDimension( 3 );
		}
		VGSH_CHECK_OGR_ERROR();

		assert( _wkbSize == -1 );

		_wkbSize = points->WkbSize();
		assert( _wkbSize > 0 );

		if ( _wkbSize <= 0 )
		{
			return false;
		}

		assert( _wkbBuffer == NULL );

		_wkbBuffer = new uchar[ _wkbSize ];
		memset( _wkbBuffer , 0 , _wkbSize );

		// 导出到wkb缓冲区
		OGRErr err = points->exportToWkb( wkbNDR , _wkbBuffer );
		if ( err != OGRERR_NONE )
		{
			clearRecoverableData();
			return false;
		}

		//------------------------------------------
		// 开始读取wkb数据
		//------------------------------------------
		bool readwkbok = readWkbData( _wkbBuffer , _wkbSize , _addrPoints );
		if ( readwkbok == false )
		{
			clearRecoverableData();
			return false;
		}

		//------------------------------------------
		// 转换坐标
		//------------------------------------------
		_isOpenGLCoordinate = false;

		converToCoordinate( _isOpenGLCoordinate ,_addrPoints, true );

		//------------------------------------------
		// 开始计算box3d信息
		//------------------------------------------	
		for ( int j = 0 ; j < _addrPoints.size() ;  ++ j )
		{
			double* addr =  _addrPoints[j];
			_box3d.merge( Vec3d( addr) );
		}

		VGSH_CHECK_OGR_ERROR();

		//------------------------------------------
		// 最后将feature写回, 便于以后写入.
		//------------------------------------------
		setFeature( feature );

		VGSH_CHECK_OGR_ERROR();


		//------------------------------------------
		// 开始读取style
		//------------------------------------------
		getDrawingDescriptor()->importFromOGRFeature( feature );

		return true;
	}
	//----------------------------------------------------------------
	bool MultiPoint::readWkbData(  uchar* buf , int buf_size , 
		std::vector<double*> points)
	{
		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}

		points.clear();


		/**
		WKBMultiPoint    {
			byte                byteOrder;
			uint32            wkbType;     // 4=wkbMultipoint
			uint32            num_wkbPoints;
			WKBPoint            WKBPoints[num_wkbPoints];
		};
		*/

		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbMultiPoint25D );
		pbuf += sizeof( int );

		// num_wkbPoints
		int num_wkbPoints = *(int*)pbuf;
		pbuf += sizeof( int );

		assert( num_wkbPoints >= 0);
		if ( num_wkbPoints <= 0 )
		{
			return false;
		}

		for ( int i = 0 ; i < num_wkbPoints ; ++ i )
		{
			double* addrPoint = NULL;

			long readnum = readSinglePointData( pbuf , &addrPoint );

			pbuf += readnum;

			points.push_back( addrPoint );
		}


		assert( (pbuf - buf) == buf_size );

		return true;
	}
	//----------------------------------------------------------------
	long MultiPoint::readSinglePointData( uchar* buf , double** ppPoint )
	{
		/*
		WKBPoint {
			byte     byteOrder;
			uint32   wkbType;     // 1=wkbPoint
			Point    point;
		};
		*/

		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbPoint25D );
		pbuf += sizeof( int );

		*ppPoint = (double*)pbuf;

		pbuf += sizeof( double ) * 3 * 1;

		return pbuf - buf;
	}

	//----------------------------------------------------------------
	void MultiPoint::renderOnceForDisplayList()
	{
#if 1
		// blue
		glColor3f( 0, 0, 1 );
		glDisable( GL_TEXTURE_2D );
		glPointSize( 3.0f );
		glPushMatrix();

		glBegin( GL_POINTS );

		for ( int j = 0 ; j < _addrPoints.size() ;  ++ j )
		{
			glVertex3dv( _addrPoints[j] );
		}

		glEnd();

		glPopMatrix();
#else
		renderInSelectedMode();
#endif

		return;
	}

	//----------------------------------------------------------------
	void MultiPoint::converToCoordinate( bool& isopenglCoord ,
		std::vector<double*> points,
		const bool& convert_to_opengl)
	{
		// 转换到opengl坐标时.
		if ( convert_to_opengl )
		{
			if ( isopenglCoord )
			{
				return;
			}
			for ( int j = 0 ; j < points.size() ;  ++ j )
			{
				double* addr =  points[j];

				double tmp = *( addr + 1 ); 
				*( addr + 1 ) = *( addr + 2 ); // 保存高度Y
				*( addr + 2 ) = -tmp; // z坐标取反
			}

			isopenglCoord = true;

			return;
		}
		else
		{
			//------------------------------------------
			// 转换到shape坐标
			//------------------------------------------
			if ( isopenglCoord == false )
			{
				return;
			}

			for ( int j = 0 ; j < points.size() ;  ++ j )
			{
				double* addr =  points[j];

				double tmp = *( addr + 1 ); 
				*( addr + 1 ) = -*( addr + 2 ); // z坐标取反
				*( addr + 2 ) = tmp; // 保存高度Y
			}

			isopenglCoord = false;
		}

		return;
	}
	//----------------------------------------------------------------
	void MultiPoint::clearRecoverableData()
	{
		if ( _wkbBuffer != NULL )
		{
			delete _wkbBuffer;
			_wkbBuffer = NULL;
		}
		_wkbSize = -1;
		_isOpenGLCoordinate = false;

		clearDisplayListID();
	}
	//----------------------------------------------------------------
	int MultiPoint::getNumOfPoints()
	{
		return _addrPoints.size();
	}
	//----------------------------------------------------------------
	bool MultiPoint::testIntersect(  const RayLine3d& rayline  )
	{
		return false;
	}
	//----------------------------------------------------------------
	void MultiPoint::renderInSelectedMode()
	{
		// red
		glColor3f( 1, 0, 0 );
		glDisable( GL_TEXTURE_2D );
		glPointSize( 5.0f );
		glPushMatrix();

		glDisable( GL_DEPTH_TEST );

		glBegin( GL_POINTS );

		for ( int j = 0 ; j < _addrPoints.size() ;  ++ j )
		{
			glVertex3dv( _addrPoints[j] );
		}

		glEnd();

		glEnable( GL_DEPTH_TEST );

		glPopMatrix();
	}
	//----------------------------------------------------------------
	uchar* MultiPoint::getShapeCoordinateBuf() 
	{
		if ( _wkbBuffer == NULL )
		{
			assert(0);
			return NULL;
		}

		//------------------------------------------
		// 此时为shape坐标,直接复制返回即可.
		//------------------------------------------
		uchar* newbuf = NULL;
		newbuf = new uchar[ _wkbSize ];

		memset( newbuf , 0 , _wkbSize );
		memcpy( newbuf  , _wkbBuffer , _wkbSize );

		if( _isOpenGLCoordinate )
		{
			std::vector<double*> points;

			readWkbData( newbuf , _wkbSize , points );

			bool isopengl = true;
			converToCoordinate( isopengl , points , false );
		}

		return newbuf;
	}
	//----------------------------------------------------------------
	bool MultiPoint::attachToTerrain()
	{
		assert( _wkbBuffer != NULL );

		vgKernel::Vec3 vec3;

		for ( int j = 0 ; j < _addrPoints.size() ;  ++ j )
		{
			vec3.x = *(_addrPoints[j]);
			vec3.z = *(_addrPoints[j]+2);

			float height = getFatherLayer()->getHeightInOpenGL( vec3 );

			*(_addrPoints[j]+1) = height;
		}

		//------------------------------------------
		// 开始复制wkb
		//------------------------------------------
		uchar* buf = new uchar[ _wkbSize ];
		memset( buf, 0 , _wkbSize );

		memcpy( buf, _wkbBuffer , _wkbSize );

		bool isopengl = _isOpenGLCoordinate;
		std::vector<double*> points;


		readWkbData( buf , _wkbSize , points );

		converToCoordinate( isopengl , points, false );

		OGRFeaturePtr pfeat = getOGRFeaturePtr();
		assert( pfeat.isNull() == false );


		//OGRGeometry* geo = pfeat->GetGeometryRef();

		OGRGeometry* newgeo =
			OGRGeometryFactory::createGeometry( wkbMultiPoint25D );

		assert( newgeo != NULL );

		OGRErr err = newgeo->importFromWkb( buf );
		assert( err == OGRERR_NONE );

		err = pfeat->SetGeometry( newgeo );
		assert( err == OGRERR_NONE );

		//------------------------------------------
		// 写回feature
		//------------------------------------------
		setFeature( pfeat.getPointer() );

		delete[] buf;
		buf = NULL;

		delete newgeo;

		return true;
	}
	//----------------------------------------------------------------
	void MultiPoint::invalidateRendering()
	{
		clearDisplayListID();
	}
	//----------------------------------------------------------------
	void MultiPoint::clearDisplayListID()
	{
		if ( _callListId != 0 )
		{
			VGK_CHECK_OPENGL_ERROR();

			glDeleteLists( _callListId , 1 );
			_callListId = 0;

			VGK_CHECK_OPENGL_ERROR();
		}
	}
	//----------------------------------------------------------------


}// end of namespace vgShape
