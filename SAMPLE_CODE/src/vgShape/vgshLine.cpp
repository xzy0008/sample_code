


#include <vgStableHeaders.h>
#include <vgShape/vgshLine.h>
#include <vgShape/vgshLayer.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkOpenGLSupport.h>



namespace vgShape {

	//----------------------------------------------------------------
	LineString::LineString( OGRFeature* feat , Layer* father ) 
		: Geometry( feat , father )
	{
		_wkbSize = -1;
		_wkbBuffer = NULL;
		_isOpenGLCoordinate = false;
		_callListId = 0;
		_box3d = Box3d::NULL_BOX;
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	void LineString::renderUsingDisplayList()
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
	bool LineString::readDataFromOGRFeature( )
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

		if ( wkbFlatten( geo->getGeometryType() ) != wkbLineString )
		{
			assert(0);
			return false;
		}

		assert( wkbFlatten( geo->getGeometryType() )
			== wkbLineString );

		OGRLineString* line = ( OGRLineString* )geo;

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

		_wkbSize = line->WkbSize();
		assert( _wkbSize > 0 );

		if ( _wkbSize <= 0 )
		{
			return false;
		}

		assert( _wkbBuffer == NULL );

		_wkbBuffer = new uchar[ _wkbSize ];
		memset( _wkbBuffer , 0 , _wkbSize );

		// 导出到wkb缓冲区
		OGRErr err = line->exportToWkb( wkbNDR , _wkbBuffer );
		if ( err != OGRERR_NONE )
		{
			clearRecoverableData();
			return false;
		}

		//------------------------------------------
		// 开始读取wkb数据
		//------------------------------------------
		bool readwkbok = readWkbData( _wkbBuffer , _wkbSize , _ring );
		if ( readwkbok == false )
		{
			clearRecoverableData();
			return false;
		}

		//------------------------------------------
		// 转换坐标
		//------------------------------------------
		_isOpenGLCoordinate = false;

		converToCoordinate( _isOpenGLCoordinate , _ring , true );

		//------------------------------------------
		// 开始计算box3d信息
		//------------------------------------------
		for(int j = 0; j < _ring._numPoints; j++)
		{
			GLdouble* addr = _ring._pointsBeginAddr + 3 * j;
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
	bool LineString::readWkbData(  uchar* buf , int buf_size , 
		RingStruct& out_ring )
	{
		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}


		/**
		WKBLineString {
		byte     byteOrder;
		uint32   wkbType;     // 2=wkbLineString
		uint32   numPoints;
		Point    points[numPoints];
		};
		*/

		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbLineString25D );
		pbuf += sizeof( int );

		// numPoints
		int numPoints = *(int*)pbuf;
		pbuf += sizeof( int );

		//------------------------------------------
		// 开始读取LinearRing   
		//------------------------------------------
		/**
		LinearRing   {
		uint32  numPoints;
		Point   points[numPoints];
		};
		*/

		assert( numPoints >= 0);
		if ( numPoints <= 0 )
		{
			return false;
		}

		out_ring._numPoints = numPoints;
		out_ring._pointsBeginAddr = (double*)pbuf;

		pbuf += sizeof( double ) * 3 * numPoints;
		
		assert( (pbuf - buf) == buf_size );

		return true;
	}
	//----------------------------------------------------------------
	void LineString::renderOnceForDisplayList()
	{

		DrawingDescriptor* desc = getDrawingDescriptor();

		double penwidth = desc->getPenWidth();

		if ( penwidth >= vgKernel::Math::ZERO_TOLERANCE )
		{
			VGK_CHECK_OPENGL_ERROR();

			glDisable( GL_TEXTURE_2D );

			vgKernel::ColorVal col = desc->getPenColorVal();
			col.useBind();

			//// Green polygon
			//glColor3f(0.5f, 1.0f, 0.0f);

			glLineWidth( penwidth );
			glPushMatrix();

			glBegin( GL_LINE_STRIP );
			for(int j = 0; j < _ring._numPoints; j++)
			{
				GLdouble* addr = _ring._pointsBeginAddr + 3 * j;

#if 1
				glVertex3dv( addr );
#else
				Vec3d	tempVec(addr);
				tempVec /= 10000.0f;
				glVertex3dv(  (double*)&tempVec);
#endif
			}
			glEnd();


			glPopMatrix();
			VGK_CHECK_OPENGL_ERROR();
		}



		return;
	}

	//----------------------------------------------------------------
	void LineString::converToCoordinate( bool& isopenglCoord , 
		RingStruct& ring, const bool& convert_to_opengl)
	{
		// 转换到opengl坐标时.
		if ( convert_to_opengl )
		{
			if ( isopenglCoord )
			{
				return;
			}


			for ( int j = 0 ; j < ring._numPoints ;  ++ j )
			{
				double* addr =  ring._pointsBeginAddr + 3 * j;

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


			for ( int j = 0 ; j < ring._numPoints ;  ++ j )
			{
				double* addr =  ring._pointsBeginAddr + 3 * j;

				double tmp = *( addr + 1 ); 
				*( addr + 1 ) = -*( addr + 2 ); // z坐标取反
				*( addr + 2 ) = tmp; // 保存高度Y
			}

			isopenglCoord = false;
		}

		return;
	}
	//----------------------------------------------------------------
	void LineString::clearRecoverableData()
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
	int LineString::getNumOfPoints()
	{
		return _ring._numPoints;
	}
	//----------------------------------------------------------------
	bool LineString::testIntersect(  const RayLine3d& rayline  )
	{
#if	1
		return false;

#else
		assert( OGRGeometryFactory::haveGEOS() == TRUE );

		//------------------------------------------
		// 首先判断是否和envelope相交.
		//------------------------------------------
		if( _box3d.testInside2D( rayline._pointEnd ) == false )
		{
			return false;
		}

		//------------------------------------------
		// 开始遍历每个点进行判断
		//------------------------------------------
		OGRGeometry* geo = 
			OGRGeometryFactory::createGeometry( wkbPoint );

		assert( geo != NULL );
		assert( wkbFlatten( geo->getGeometryType() )== wkbPoint );

		geo->setCoordinateDimension(3);

		OGRPoint* pt = ( OGRPoint * )geo;

		pt->setX( rayline._pointEnd.x );
		pt->setY( -rayline._pointEnd.z ); // 负的

		pt->flattenTo2D();

		assert( _wkbBuffer != NULL );
		// 首先转换opengl坐标到shape坐标
		uchar* shp_buf = getShapeCoordinateBuf();
		assert( shp_buf != NULL );

		OGRLineString	line;
		OGRErr err = line.importFromWkb( shp_buf , _wkbSize );
		assert( err == OGRERR_NONE );


		// 删除缓冲区
		delete[] shp_buf;
		shp_buf = NULL;

		OGRLinearRing* pring = new OGRLinearRing;
		
		int	nPointCount = line.getNumPoints();
		OGRRawPoint * paoPointsOut = new OGRRawPoint[nPointCount];
		double * padfZ = new double[nPointCount];
		
		line.getPoints(paoPointsOut, padfZ);
		pring->setPoints( nPointCount, paoPointsOut, padfZ);
		pring->closeRings();
		if(pring->isClockwise())
			pring->reverseWindingOrder();

		OGRBoolean bo = pring->isPointInRing(pt);
		//OGRPolygon	poly;
		//poly.addRingDirectly(pring);
		
		// 变为2D
		//poly.flattenTo2D();
		//pline->flattenTo2D();

		//OGRBoolean bo = poly.Contains( pt );

		//OGRBoolean bo = poly.Intersect( ls );
		OGRGeometryFactory::destroyGeometry( geo );
		if ( bo == TRUE )
		{
			return true;
		}
		return false;

#endif
	}
	//----------------------------------------------------------------
	void LineString::renderInSelectedMode()
	{
		// red
		glColor3f( 1, 0, 0 );
		glDisable( GL_TEXTURE_2D );
		glPointSize( 5.0f );
		glPushMatrix();

		glDisable( GL_DEPTH_TEST );

		glBegin( GL_POINTS );

		for(int j = 0; j < _ring._numPoints; j++)
		{
			GLdouble* addr = _ring._pointsBeginAddr + 3 * j;

			//double x = *(addr);
			//double y = *(addr+1);
			//double z = *(addr+2);

			glVertex3dv( addr );
		}

		glEnd();

		glEnable( GL_DEPTH_TEST );

		glPopMatrix();
	}
	//----------------------------------------------------------------
	uchar* LineString::getShapeCoordinateBuf() 
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
			RingStruct ring;

			readWkbData( newbuf , _wkbSize , ring );

			bool isopengl = true;
			converToCoordinate( isopengl , ring , false );
		}

		return newbuf;
	}
	//----------------------------------------------------------------
	bool LineString::attachToTerrain()
	{
		assert( _wkbBuffer != NULL );

		vgKernel::Vec3 vec3;

		for(int j = 0; j < _ring._numPoints; j++)
		{
			GLdouble* addr = _ring._pointsBeginAddr + 3 * j;

			vec3.x = *(addr);
			vec3.z = *(addr+2);
			//double z = *(addr+2);

			float height = getFatherLayer()->getHeightInOpenGL( vec3 );

			*(addr+1) = height;
		}

#if 1	
		//------------------------------------------
		// 开始复制wkb
		//------------------------------------------
		uchar* buf = new uchar[ _wkbSize ]; 
		memset( buf, 0 , _wkbSize );

		memcpy( buf, _wkbBuffer , _wkbSize );

		bool isopengl = _isOpenGLCoordinate;
		RingStruct ringTemp;

		readWkbData( buf , _wkbSize , ringTemp );

		converToCoordinate( isopengl , ringTemp , false );

		OGRFeaturePtr pfeat = getOGRFeaturePtr();
		assert( pfeat.isNull() == false );


		//OGRGeometry* geo = pfeat->GetGeometryRef();

		OGRGeometry* newgeo =
			OGRGeometryFactory::createGeometry( wkbLineString25D );

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
#endif

		return true;
	}
	//----------------------------------------------------------------
	void LineString::invalidateRendering()
	{
		clearDisplayListID();
	}
	//----------------------------------------------------------------
	void LineString::clearDisplayListID()
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
