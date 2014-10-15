


#include <vgStableHeaders.h>
#include <vgGis3d/vggiPoint.h>
#include <vgGis3d/vggiLayer.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkOpenGLSupport.h>


namespace vgGIS3D {

	//----------------------------------------------------------------
	Point::Point( OGRFeature* feat , Layer* father ) 
		: Geometry( feat , father )
	{
		_wkbSize = -1;
		_wkbBuffer = NULL;
		_isOpenGLCoordinate = false;
		_callListId = 0;
		_box3d = Box3d::NULL_BOX;

		_addrPoint = NULL;
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	void Point::renderUsingDisplayList()
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
	bool Point::readDataFromOGRFeature( )
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

		if ( wkbFlatten( geo->getGeometryType() ) != wkbPoint )
		{
			assert(0);
			return false;
		}

		assert( wkbFlatten( geo->getGeometryType() )
			== wkbPoint );

		OGRPoint* point = ( OGRPoint* )geo;

		VGGI_CHECK_OGR_ERROR();
		//------------------------------------------
		// 设定为25D模式
		//------------------------------------------
		int dimension = geo->getDimension();
		if ( dimension != 3 )
		{
			geo->setCoordinateDimension( 3 );
		}
		VGGI_CHECK_OGR_ERROR();

		assert( _wkbSize == -1 );

		_wkbSize = point->WkbSize();
		assert( _wkbSize > 0 );

		if ( _wkbSize <= 0 )
		{
			return false;
		}

		assert( _wkbBuffer == NULL );

		_wkbBuffer = new uchar[ _wkbSize ];
		memset( _wkbBuffer , 0 , _wkbSize );

		// 导出到wkb缓冲区
		OGRErr err = point->exportToWkb( wkbNDR , _wkbBuffer );
		if ( err != OGRERR_NONE )
		{
			clearRecoverableData();
			return false;
		}

		//------------------------------------------
		// 开始读取wkb数据
		//------------------------------------------
		bool readwkbok = readWkbData( _wkbBuffer , _wkbSize , &_addrPoint );
		if ( readwkbok == false )
		{
			clearRecoverableData();
			return false;
		}

		//------------------------------------------
		// 转换坐标
		//------------------------------------------
		_isOpenGLCoordinate = false;

		converToCoordinate( _isOpenGLCoordinate ,&_addrPoint, true );

		//------------------------------------------
		// 开始计算box3d信息
		//------------------------------------------	
		_box3d.merge( Vec3d( _addrPoint) );


		VGGI_CHECK_OGR_ERROR();

		//------------------------------------------
		// 最后将feature写回, 便于以后写入.
		//------------------------------------------
		setFeature( feature );

		VGGI_CHECK_OGR_ERROR();


		//------------------------------------------
		// 开始读取style
		//------------------------------------------
		getDrawingDescriptor()->importFromOGRFeature( feature );

		return true;
	}
	//----------------------------------------------------------------
	bool Point::readWkbData(  uchar* buf , int buf_size , 
		double** ppPoint)
	{
		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}


		/**
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

		assert( (pbuf - buf) == buf_size );

		return true;
	}
	//----------------------------------------------------------------
	void Point::renderOnceForDisplayList()
	{
#if 1
		// blue
		glColor3f( 0, 0, 1 );
		glDisable( GL_TEXTURE_2D );
		glPointSize( 3.0f );
		glPushMatrix();

		glBegin( GL_POINTS );

#if 1
		glVertex3dv( _addrPoint );
#else
		Vec3d	tempVec(_addrPoint);
		tempVec /= 10000.0f;
		glVertex3dv(  (double*)&tempVec);
#endif

		glEnd();

		glPopMatrix();
#else
		renderInSelectedMode();
#endif

		return;
	}

	//----------------------------------------------------------------
	void Point::converToCoordinate( bool& isopenglCoord ,double** ppPoint,
		const bool& convert_to_opengl)
	{
		// 转换到opengl坐标时.
		if ( convert_to_opengl )
		{
			if ( isopenglCoord )
			{
				return;
			}

			double tmp = *( *ppPoint + 1 ); 
			*( *ppPoint + 1 ) = *( *ppPoint + 2 ); // 保存高度Y
			*( *ppPoint + 2 ) = -tmp; // z坐标取反

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


			double tmp = *( *ppPoint + 1 ); 
			*( *ppPoint + 1 ) = -*( *ppPoint + 2 ); // z坐标取反
			*( *ppPoint + 2 ) = tmp; // 保存高度Y


			isopenglCoord = false;
		}

		return;
	}
	//----------------------------------------------------------------
	void Point::clearRecoverableData()
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
	int Point::getNumOfPoints()
	{
		return 1;
	}
	//----------------------------------------------------------------
	bool Point::testIntersect(  const RayLine3d& rayline  )
	{
		return false;
	}
	//----------------------------------------------------------------
	void Point::renderInSelectedMode()
	{
		// red
		glColor3f( 1, 0, 0 );
		glDisable( GL_TEXTURE_2D );
		glPointSize( 5.0f );
		glPushMatrix();

		glDisable( GL_DEPTH_TEST );

		glBegin( GL_POINTS );

		glVertex3dv( _addrPoint );

		glEnd();

		glEnable( GL_DEPTH_TEST );

		glPopMatrix();
	}
	//----------------------------------------------------------------
	uchar* Point::getShapeCoordinateBuf() 
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
			double *pPoint = NULL;
			readWkbData( newbuf , _wkbSize , &pPoint );

			bool isopengl = true;
			converToCoordinate( isopengl , &pPoint , false );
		}

		return newbuf;
	}
	//----------------------------------------------------------------
	bool Point::attachToTerrain()
	{
		assert( _wkbBuffer != NULL );

		vgKernel::Vec3 vec3;
		_box3d = Box3d::NULL_BOX;

		vec3.x = *(_addrPoint);
		vec3.z = *(_addrPoint+2);

		float height = getFatherLayer()->getHeightInOpenGL( vec3 );

		*(_addrPoint+1) = height;
		_box3d.merge(vec3);

		//------------------------------------------
		// 开始复制wkb
		//------------------------------------------
		uchar* buf = new uchar[ _wkbSize ];
		memset( buf, 0 , _wkbSize );

		memcpy( buf, _wkbBuffer , _wkbSize );

		bool isopengl = _isOpenGLCoordinate;
		double* addrPointTemp;


		readWkbData( buf , _wkbSize , &addrPointTemp );

		converToCoordinate( isopengl , &addrPointTemp, false );

		OGRFeaturePtr pfeat = getOGRFeaturePtr();
		assert( pfeat.isNull() == false );


		//OGRGeometry* geo = pfeat->GetGeometryRef();

		OGRGeometry* newgeo =
			OGRGeometryFactory::createGeometry( wkbPoint25D );

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
	void Point::invalidateRendering()
	{
		clearDisplayListID();
	}
	//----------------------------------------------------------------
	void Point::clearDisplayListID()
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
