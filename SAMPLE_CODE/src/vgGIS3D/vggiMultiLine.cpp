


#include <vgStableHeaders.h>
#include <vgGis3D/vggiMultiLine.h>
#include <vgGis3D/vggiLayer.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkOpenGLSupport.h>
#include <vgKernel/vgkMath.h>


namespace vgGIS3D {

	//----------------------------------------------------------------
	MultiLine::MultiLine( OGRFeature* feat , Layer* father ) 
		: Geometry( feat , father )
	{
		_wkbSize = -1;
		_wkbBuffer = NULL;
		_isOpenGLCoordinate = false;
		_callListId = 0;
		_box3d = Box3d::NULL_BOX;
		_envelope = NULL; 

		m_dis = 0.0;
	}

	//----------------------------------------------------------------
	void MultiLine::renderUsingDisplayList()
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
	bool MultiLine::readDataFromOGRFeature( )
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

		if ( wkbFlatten( geo->getGeometryType() ) != wkbMultiLineString )
		{
			assert(0);
			return false;
		}

		assert( wkbFlatten( geo->getGeometryType() )
			== wkbMultiLineString );

		OGRMultiLineString* line = ( OGRMultiLineString* )geo;

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
		bool readwkbok = readWkbData( _wkbBuffer , _wkbSize , _rings );
		if ( readwkbok == false )
		{
			clearRecoverableData();
			return false;
		}

		//------------------------------------------
		// 转换坐标
		//------------------------------------------
		_isOpenGLCoordinate = false;

		converToCoordinate( _isOpenGLCoordinate , _rings , true );

		//------------------------------------------
		// 开始计算box3d信息
		//------------------------------------------
		if ( !aroundingBox.empty() )
		{
			aroundingBox.clear();
		}

		RingStructVec::iterator iter = _rings.begin();
		RingStructVec::iterator iter_end = _rings.end();

		for ( ; iter != iter_end ; ++iter )
		{
			RingStruct& ring = *iter;
			for(int j = 0; j < ring._numPoints; j++)
			{
				GLdouble* addr = ring._pointsBeginAddr + 3 * j;
				_box3d.merge( Vec3d( addr) );
			}

			for ( int l = 0; l < ring._numPoints - 1; l++)
			{
				GLdouble* addr = ring._pointsBeginAddr + 3 * l;

				vgKernel::Vec3 startPt;
				vgKernel::Vec3 endPt;
				vgKernel::Vec3 maxPoint;
				vgKernel::Vec3 minPoint;
				vgKernel::Box new_box = vgKernel::Box::NULL_BOX;

				startPt.x = *( addr );
				startPt.y = *( addr + 1 );
				startPt.z = *( addr + 2 );

				endPt.x = *( addr + 3 );
				endPt.y = *( addr + 4 );
				endPt.z = *( addr + 5 );
				
				new_box.merge( startPt );
				new_box.merge( endPt );

				maxPoint.x = new_box.getMaximum().x + m_dis;
				maxPoint.y = new_box.getMaximum().y + m_dis;
				maxPoint.z = new_box.getMaximum().z + m_dis;

				minPoint.x = new_box.getMinimum().x - m_dis;
				minPoint.y = new_box.getMinimum().y - m_dis;
				minPoint.z = new_box.getMinimum().z - m_dis;

				new_box.setMaximum( maxPoint );
				new_box.setMinimum( minPoint );

				aroundingBox.push_back( new_box );
			}
		}

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
	bool MultiLine::readWkbData(  uchar* buf , int buf_size , 
		RingStructVec& out_rings )
	{
		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}

		/**
		WKBMultiLineString    {
			byte              byteOrder;
			uint32            wkbType;     // 5=wkbMultiLineString
			uint32            num_wkbLineStrings;
			WKBLineString     WKBLineStrings[num_wkbLineStrings];
		};
		*/

		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbMultiLineString25D );
		pbuf += sizeof( int );

		// num_wkbLineStrings
		int numRings = *(int*)pbuf;
		pbuf += sizeof( int );

		//------------------------------------------
		// 开始读取WKBLineString   
		//------------------------------------------
		/**
		WKBLineString {
		byte     byteOrder;
		uint32   wkbType;     // 2=wkbLineString
		uint32   numPoints;
		Point    points[numPoints];
		};
		*/

		assert( numRings >= 0);
		if ( numRings <= 0 )
		{
			return false;
		}

		for ( int i = 0 ; i < numRings ; ++ i )
		{
			RingStruct ring;

			long readnum = readSingleLineData( pbuf , ring );

			pbuf += readnum;

			out_rings.push_back( ring );
		}

		
		assert( (pbuf - buf) == buf_size );

		return true;
	}
	//----------------------------------------------------------------
	long MultiLine::readSingleLineData( uchar* buf , 
		RingStruct& out_ring )
	{
		
		/**
		WKBLineString {
			byte     byteOrder;
			uint32   wkbType;     // 2=wkbLineString
			uint32   numPoints;
			Point    points[numPoints];
		};*/

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

		assert( numPoints >= 0);
		if ( numPoints <= 0 )
		{
			return false;
		}

		out_ring._numPoints = numPoints;
		out_ring._pointsBeginAddr = (double*)pbuf;

		pbuf += sizeof( double ) * 3 * numPoints;

		return pbuf - buf;
	}

	//----------------------------------------------------------------
	void MultiLine::renderOnceForDisplayList()
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

			for ( int i = 0 ; i < _rings.size() ; ++ i )
			{
				glBegin( GL_LINE_STRIP );
				for(int j = 0; j < _rings[i]._numPoints; j++)
				{
					GLdouble* addr = _rings[i]._pointsBeginAddr + 3 * j;

					glVertex3dv( addr );
				}
				glEnd();
			}



			glPopMatrix();
			VGK_CHECK_OPENGL_ERROR();
		}



		return;
	}

	//----------------------------------------------------------------
	void MultiLine::converToCoordinate( bool& isopenglCoord , 
		RingStructVec& rings, const bool& convert_to_opengl)
	{
		// 转换到opengl坐标时.
		if ( convert_to_opengl )
		{
			if ( isopenglCoord )
			{
				return;
			}


			for ( int i = 0 ; i < rings.size() ; ++ i )
			{
				for ( int j = 0 ; j < rings[i]._numPoints ;  ++ j )
				{
					double* addr =  rings[i]._pointsBeginAddr + 3 * j;

					double tmp = *( addr + 1 ); 
					*( addr + 1 ) = *( addr + 2 ); // 保存高度Y
					*( addr + 2 ) = -tmp; // z坐标取反
				}
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


			for ( int i = 0 ; i < rings.size() ; ++ i )
			{
				for ( int j = 0 ; j < rings[i]._numPoints ;  ++ j )
				{
					double* addr =  rings[i]._pointsBeginAddr + 3 * j;

					double tmp = *( addr + 1 ); 
					*( addr + 1 ) = -*( addr + 2 ); // z坐标取反
					*( addr + 2 ) = tmp; // 保存高度Y
				}
			}

			isopenglCoord = false;
		}

		return;
	}
	//----------------------------------------------------------------
	void MultiLine::clearRecoverableData()
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
	int MultiLine::getNumOfPoints()
	{
		int ret = 0;
		std::vector<RingStruct>::iterator iter = _rings.begin();
		std::vector<RingStruct>::iterator iter_end = _rings.end();

		for ( ; iter != iter_end  ;++ iter )
		{
			ret += iter->_numPoints;
		}

		return ret;
	}
	//----------------------------------------------------------------
	bool MultiLine::testIntersect(  const RayLine3d& rayline  )
	{
		assert( OGRGeometryFactory::haveGEOS() == TRUE );

		//------------------------------------------
		// 首先判断是否和envelope相交.
		//------------------------------------------
		std::vector<vgKernel::Box>::iterator iter = aroundingBox.begin();
		std::vector<vgKernel::Box>::iterator iter_end = aroundingBox.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::Box _box = *iter;

			std::pair<bool, float> result = vgKernel::Math::intersects( 
				rayline.getRay3d().getRayFloat(), _box );

			if (result.first != false)
			{
				return true;
			}

		}
		return false;
 		//if ( new_box.testInside2D( rayline._pointEnd ) == false )
 		//{
 		//	return false;
 		//}

 		//if( _box3d.testInside2D( rayline._pointEnd ) == false )
 		//{
 		//	return false;
 		//}
#if 0
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

		if (_envelope==NULL)
		{
			_envelope = Buffer(0.1,5);
		}

		OGRBoolean isintersect = _envelope->Intersects(pt);

		return isintersect;
#endif
		//--------------------------------------
		//	Edit By FengYK @2010-01-27 15:59
		//	使用"测试射线和每条线段的包围盒相交"的方法判断点选
		//--------------------------------------
#if 0
		//--------------------------------------
		//   Edit By FengYK @2010-01-25 13:59
		//--------------------------------------

		vgKernel::Vec3 lineStartPt;
		vgKernel::Vec3 lineEndPt;

		lineStartPt.x = rayline._pointStart.x;
		lineStartPt.y = rayline._pointStart.y;
		lineStartPt.z = rayline._pointStart.z;

		lineEndPt.x = rayline._pointEnd.x;
		lineEndPt.y = rayline._pointEnd.y;
		lineEndPt.z = rayline._pointEnd.z;

		vgKernel::Ray lookray = vgKernel::Ray( lineStartPt, lineEndPt );

		std::vector<aRound_Point>::iterator iter = aroundingPoints.begin();
		std::vector<aRound_Point>::iterator iter_end = aroundingPoints.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			aRound_Point aPoint = *iter;

			//tempPt1 = aPoint.arPoint1;
			//tempPt2 = aPoint.arPoint2;
			//tempPt3 = aPoint.arPoint3;
			//tempPt4 = aPoint.arPoint4;

			// 测试是否穿过三角形
			if ( tri_Interect(lookray, aPoint.arPoint1, aPoint.arPoint2, aPoint.arPoint3) )
			{
				return true;
			}

			if ( tri_Interect(lookray, aPoint.arPoint2, aPoint.arPoint3, aPoint.arPoint4) )
			{
				return true;
			}

		}

		return false;
		
#endif
		
#if 0
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
	void MultiLine::renderInSelectedMode()
	{
		// red
		glColor3f( 1, 0, 0 );
		glDisable( GL_TEXTURE_2D );
		glPointSize( 5.0f );
		glPushMatrix();

		glDisable( GL_DEPTH_TEST );

#if 0
		// 选择模式下画点
		glBegin( GL_POINTS );

		for ( int i = 0 ; i < _rings.size() ; ++ i )
		{
			for(int j = 0; j < _rings[i]._numPoints; j++)
			{
				GLdouble* addr = _rings[i]._pointsBeginAddr + 3 * j;

				//double x = *(addr);
				//double y = *(addr+1);
				//double z = *(addr+2);

				glVertex3dv( addr );
			}
		}

		glEnd();

#endif
		// 选择模式下画线
		for ( int i = 0 ; i < _rings.size() ; ++ i )
		{
			glBegin( GL_LINE_STRIP );
			for(int j = 0; j < _rings[i]._numPoints; j++)
			{
				GLdouble* addr = _rings[i]._pointsBeginAddr + 3 * j;

				glVertex3dv( addr );
			}
			glEnd();
		}

		//glBegin( GL_TRIANGLES );
 
		//glVertex3f( tempPt1.x, tempPt1.y, tempPt1.z );
		//glVertex3f( tempPt2.x, tempPt2.y, tempPt2.z );
		//glVertex3f( tempPt3.x, tempPt3.y, tempPt3.z );
 
		//glVertex3f( tempPt2.x, tempPt2.y, tempPt2.z );
		//glVertex3f( tempPt3.x, tempPt3.y, tempPt3.z );
		//glVertex3f( tempPt4.x, tempPt4.y, tempPt4.z );
 
		//glEnd();
 
		glEnable( GL_DEPTH_TEST );

		glPopMatrix();
	}
	//----------------------------------------------------------------
	uchar* MultiLine::getShapeCoordinateBuf() 
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
			RingStructVec ringsTemp;

			readWkbData( newbuf , _wkbSize , ringsTemp );

			bool isopengl = true;
			converToCoordinate( isopengl , ringsTemp , false );
		}

		return newbuf;
	}
	//----------------------------------------------------------------
	bool MultiLine::attachToTerrain()
	{
		assert( _wkbBuffer != NULL );

		vgKernel::Vec3 vec3;
		_box3d = Box3d::NULL_BOX;

		for ( int i = 0 ; i < _rings.size() ; ++ i )
		{
			for(int j = 0; j < _rings[i]._numPoints; j++)
			{
				GLdouble* addr = _rings[i]._pointsBeginAddr + 3 * j;

				vec3.x = *(addr);
				vec3.z = *(addr+2);
				//double z = *(addr+2);

				float height = getFatherLayer()->getHeightInOpenGL( vec3 );

				*(addr+1) = height;

				_box3d.merge(vec3);
			}
		}

#if 1	
		//------------------------------------------
		// 开始复制wkb
		//------------------------------------------
		uchar* buf = new uchar[ _wkbSize ]; 
		memset( buf, 0 , _wkbSize );

		memcpy( buf, _wkbBuffer , _wkbSize );

		bool isopengl = _isOpenGLCoordinate;
		RingStructVec ringsTemp;

		readWkbData( buf , _wkbSize , ringsTemp );

		converToCoordinate( isopengl , ringsTemp , false );

		OGRFeaturePtr pfeat = getOGRFeaturePtr();
		assert( pfeat.isNull() == false );


		//OGRGeometry* geo = pfeat->GetGeometryRef();

		OGRGeometry* newgeo =
			OGRGeometryFactory::createGeometry( wkbMultiLineString25D );

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
	void MultiLine::invalidateRendering()
	{
		clearDisplayListID();

		//----------------------------------------------
		// Edit By FengYK @2010-01-27 15:59
		// 使用"测试射线和每条线段的包围盒相交"的方法判断点选
		//----------------------------------------------
		setIntersectDis();
#if 0
		RingStructVec m_rings = _rings;
		Vec3d line_Pot1;
		Vec3d line_Pot2;

		if ( !aroundingPoints.empty() )
		{
			aroundingPoints.clear();
		}

		for (int i=0; i<m_rings.size(); i++)
		{
			RingStruct RingsRef = m_rings.at(i);

			for (int j=0; j<RingsRef._numPoints - 1; j++)
			{
				GLdouble* addr = RingsRef._pointsBeginAddr + 3 * j;

				double startPot_x = *( addr );
				double startPot_y = *( addr + 1 );
				double startPot_z = *( addr + 2 );

				double endPot_x = *( addr + 3 );
				double endPot_y = *( addr + 4 );
				double endPot_z = *( addr + 5 );

				line_Pot1.x = startPot_x;
				line_Pot1.y = startPot_y;
				line_Pot1.z = startPot_z;

				line_Pot2.x = endPot_x;
				line_Pot2.y = endPot_y;
				line_Pot2.z = endPot_z;

				// 当两个点组成的线与Y轴平行时，不能叉乘，排除和Y轴平行的情况
				if ( (line_Pot1.x == line_Pot2.x) && (line_Pot1.z == line_Pot2.z) )
				{
					return;
				}

				// 两个点连成的向量
				Vec3d line_Vec;
				line_Vec.x = line_Pot1.x - line_Pot2.x;
				line_Vec.y = line_Pot1.y - line_Pot2.y;
				line_Vec.z = line_Pot1.z - line_Pot2.z;

				Vec3d AxisY;	// Y轴单位向量
				AxisY.x = 0.0;
				AxisY.y = 1.0;
				AxisY.z = 0.0;

				// 叉乘,两个点组成的向量与Y轴的单位向量(0, 1, 0) 叉乘后的结果
				Vec3d crossedProduct = line_Vec.crossProduct( AxisY );

				// 单位化
				Vec3d unitization = crossedProduct.normalisedRef();

				// 乘以距离d 
				Vec3d multiply_d;
				multiply_d.x = unitization.x * m_dis;
				multiply_d.y = unitization.y * m_dis;
				multiply_d.z = unitization.z * m_dis;

				// 点1
				vgKernel::Vec3 aRound_Pot1;
				aRound_Pot1.x = multiply_d.x + line_Pot1.x;
				aRound_Pot1.y = multiply_d.y + line_Pot1.y;
				aRound_Pot1.z = multiply_d.z + line_Pot1.z;

				// 点2
				vgKernel::Vec3 aRound_Pot2;
				aRound_Pot2.x = -multiply_d.x + line_Pot1.x;
				aRound_Pot2.y = -multiply_d.y + line_Pot1.y;
				aRound_Pot2.z = -multiply_d.z + line_Pot1.z;

				// 点3
				vgKernel::Vec3 aRound_Pot3;
				aRound_Pot3.x = multiply_d.x + line_Pot2.x;
				aRound_Pot3.y = multiply_d.y + line_Pot2.y;
				aRound_Pot3.z = multiply_d.z + line_Pot2.z;

				// 点4
				vgKernel::Vec3 aRound_Pot4;
				aRound_Pot4.x = -multiply_d.x + line_Pot2.x;
				aRound_Pot4.y = -multiply_d.y + line_Pot2.y;
				aRound_Pot4.z = -multiply_d.z + line_Pot2.z;

				aRound_Point apoints;
				apoints.arPoint1 = aRound_Pot1;
				apoints.arPoint2 = aRound_Pot2;
				apoints.arPoint3 = aRound_Pot3;
				apoints.arPoint4 = aRound_Pot4;

				aroundingPoints.push_back(apoints);
			}
		}

#endif
		
	}
	//----------------------------------------------------------------
	void MultiLine::clearDisplayListID()
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
	bool MultiLine::tri_Interect( const vgKernel::Ray& ray, vgKernel::Vec3 pt1, vgKernel::Vec3 pt2, vgKernel::Vec3 pt3 )
	{
		std::pair<bool, float> result = vgKernel::Math::intersects( ray , pt1 , pt2 , pt3 );
		if(result.first == true)
			return true;
		else
			return false;
	}
	//----------------------------------------------------------------
	void MultiLine::setIntersectDis()
	{
		vgKernel::Box fatherLayerBoundBox = this->getFatherLayer()->getBoundingBox();
		Vec3d m_boxSize = fatherLayerBoundBox.getSize();

		if ( m_boxSize.x > m_boxSize.z )
		{
			m_dis = m_boxSize.z * 0.003;
		}
		else
		{
			m_dis = m_boxSize.x * 0.003;
		}

		if ( m_dis > 0.5 )
		{
			m_dis = 0.5;
		}
	}
	//----------------------------------------------------------------
}// end of namespace vgShape
