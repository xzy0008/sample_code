


#include <vgStableHeaders.h>
#include <vggis3d/vggiPolygon.h>
#include <vggis3d/vggiLayer.h>

#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkOpenGLSupport.h>

namespace vgGIS3D {
	
	//----------------------------------------------------------------
	Polygon::Polygon( OGRFeature* feat , Layer* father ) 
		: Geometry( feat , father )
	{
		_wkbSize = -1;
		_wkbBuffer = NULL;
		_isOpenGLCoordinate = false;
		_callListId = 0;
		_box3d = Box3d::NULL_BOX;

		// 块颜色
/*		DrawingDescriptor* desc = getDrawingDescriptor();
		vgKernel::ColorVal col = desc->getFillingColorVal();
		
		srand((unsigned long)time(NULL));
		col.r = rand()%100/100.0f ;
		col.g = rand()%100/100.0f ;
		col.b = rand()%100/100.0f ;
		desc->setFillColor(col.getAsColorRef());*/
	}
	//----------------------------------------------------------------
	
	//----------------------------------------------------------------
	void Polygon::renderUsingDisplayList()
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
	bool Polygon::readDataFromOGRFeature( )
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

		if ( wkbFlatten( geo->getGeometryType() ) != wkbPolygon )
		{
			assert(0);
			return false;
		}

		assert( wkbFlatten( geo->getGeometryType() )
			== wkbPolygon );

		OGRPolygon* poly = ( OGRPolygon* )geo;

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

		_wkbSize = poly->WkbSize();
		assert( _wkbSize > 0 );

		if ( _wkbSize <= 0 )
		{
			return false;
		}

		assert( _wkbBuffer == NULL );

		_wkbBuffer = new uchar[ _wkbSize ];
		memset( _wkbBuffer , 0 , _wkbSize );

		// 导出到wkb缓冲区
		OGRErr err = poly->exportToWkb( wkbNDR , _wkbBuffer );
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

		converToCoordinate( _isOpenGLCoordinate , 
			_wkbBuffer , _rings , true );

		//------------------------------------------
		// 开始计算box3d信息
		// 自己算exterior即可
		//------------------------------------------
		if ( _rings.empty() == false )
		{
			for(int j = 0; j < _rings[0]._numPoints; j++)
			{
				GLdouble* addr = _rings[0]._pointsBeginAddr + 3 * j;
				_box3d.merge( Vec3d( addr) );
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
	bool Polygon::readWkbData(  uchar* buf , int buf_size , 
		std::vector<RingStruct>& out_rings )
	{
		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}

		out_rings.clear();

		/**
			WKBPolygon    {
			byte                byteOrder;
			uint32            wkbType;     // 3=wkbPolygon
			uint32            numRings;
			LinearRing        rings[numRings];
		};
		*/

		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbPolygon25D );
		pbuf += sizeof( int );

		// numRings
		int numRings = *(int*)pbuf;
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

		assert( numRings >= 0);
		if ( numRings <= 0 )
		{
			return false;
		}

		for ( int i = 0 ; i < numRings ; ++ i )
		{
			int numPoints = *(int*)pbuf;
			assert( numPoints >= 0 );
			pbuf += sizeof( int );

			out_rings.push_back( RingStruct( numPoints , (double*)pbuf ) );

			// 跳过这些点.
			pbuf += sizeof( double ) * 3 * numPoints;
		}

		assert( (pbuf - buf) == buf_size );

		return true;
	}
	//----------------------------------------------------------------
	void Polygon::renderOnceForDisplayList()
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


		if ( desc->isDrawFilling() )
		{
			VGK_CHECK_OPENGL_ERROR();

			//glColor3f(0.3f, 0.3f, 0.3f); 
			//float randfloat = rand() *1.0 / RAND_MAX ;
			//glColor3f( randfloat, 0.3, 0.3f);
			vgKernel::ColorVal col = desc->getFillingColorVal();
			col.useBind();

			VGK_CHECK_OPENGL_ERROR();
			glDisable( GL_TEXTURE_2D );
			//glPushAttrib(GL_CURRENT_BIT);
			glPushMatrix();
			{
				GLUtesselator *pTess = NULL;
				pTess = gluNewTess();

				gluTessCallback(pTess, GLU_BEGIN, (void(__stdcall*)())glBegin);
				gluTessCallback(pTess, GLU_END, (void(__stdcall*)())glEnd);
				gluTessCallback(pTess, GLU_VERTEX, (void(__stdcall*)())glVertex3dv);

				gluTessProperty(pTess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);

				gluTessBeginPolygon(pTess, NULL); // No user data

				for ( int i = 0 ; i < _rings.size() ; ++ i )
				{
					if ( i == 0 )
					{
						double* addr;
						// 渲染exterior rings
						gluTessBeginContour(pTess);
						for(int j = 0; j < _rings[i]._numPoints; j++)
						{
							addr = _rings[i]._pointsBeginAddr + 3 * j;

							gluTessVertex( pTess, addr,  addr );
						}
						gluTessEndContour(pTess);
					}
					else
					{
						double* addr;
						// 渲染exterior rings
						gluTessBeginContour(pTess);
						for(int j = 0; j < _rings[i]._numPoints; j++)
						{
							addr = _rings[i]._pointsBeginAddr + 3 * j;

							gluTessVertex( pTess, addr,  addr );
						}
						gluTessEndContour(pTess);
					}
				}


				// All done with polygon
				gluTessEndPolygon(pTess);

				// No longer need tessellator object
				gluDeleteTess(pTess);            
			}

			VGK_CHECK_OPENGL_ERROR();

			glPopMatrix();
		}





		return;
	}

	//----------------------------------------------------------------
	void Polygon::converToCoordinate( bool& isopenglCoord , 
		uchar* buf , 
		std::vector<RingStruct>& rings, const bool& convert_to_opengl)
	{
		// 转换到opengl坐标时.
		if ( convert_to_opengl )
		{
			if ( isopenglCoord )
			{
				return;
			}

			if ( buf == NULL )
			{
				assert(0);
				return;
			}

			assert( rings.empty() == false );

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

			if ( buf == NULL )
			{
				assert(0);
				return;
			}

			assert( rings.empty() == false );

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
	void Polygon::clearRecoverableData()
	{
		if ( _wkbBuffer != NULL )
		{
			delete _wkbBuffer;
			_wkbBuffer = NULL;
		}
		_wkbSize = -1;
		_rings.clear();
		_isOpenGLCoordinate = false;

		clearDisplayListID();
	}
	//----------------------------------------------------------------
	int Polygon::getNumOfPoints()
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
	bool Polygon::testIntersect(  const RayLine3d& rayline  )
	{
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

		OGRPolygon poly;
		OGRErr err = poly.importFromWkb( shp_buf , _wkbSize );
		assert( err == OGRERR_NONE );

		// 删除缓冲区
		delete[] shp_buf;
		shp_buf = NULL;

		// 变为2D
		poly.flattenTo2D();

		OGRBoolean bo = poly.Contains( pt );

		//OGRBoolean bo = poly.Intersect( ls );
		OGRGeometryFactory::destroyGeometry( geo );
		if ( bo == TRUE )
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------
	void Polygon::renderInSelectedMode()
	{
		// red
		glColor3f( 1, 0, 0 );
		glDisable( GL_TEXTURE_2D );
		glPointSize( 5.0f );
		glPushMatrix();

		glDisable( GL_DEPTH_TEST );

		// 选择模式下画点
		/*glBegin( GL_POINTS );
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
		glEnd();*/
		
		//选择模式下画线
		glLineWidth( 3.0 );
		glBegin( GL_LINES );
			for ( int i = 0; i < _rings.size(); ++i )
			{
				for ( int j = 0; j < _rings[i]._numPoints - 1; j++ )
				{
					GLdouble* addrFirst = _rings[i]._pointsBeginAddr + 3*j;
					GLdouble* addrSecond = _rings[i]._pointsBeginAddr + 3*(j+1);

					glVertex3dv( addrFirst );
					glVertex3dv( addrSecond );
				}

				GLdouble* addrEnd = _rings[i]._pointsBeginAddr + 3 * ( _rings[i]._numPoints - 1 );
				GLdouble* addrStart = _rings[i]._pointsBeginAddr;
				glVertex3dv( addrEnd );
				glVertex3dv( addrStart );
			}
		glEnd();

		glEnable( GL_DEPTH_TEST );

		glPopMatrix();
	}
	//----------------------------------------------------------------
	uchar* Polygon::getShapeCoordinateBuf() 
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
			std::vector<RingStruct> ringsvec;

			readWkbData( newbuf , _wkbSize , ringsvec );

			bool isopengl = true;
			converToCoordinate( isopengl , newbuf , ringsvec , false );
		}

		return newbuf;
	}
	//----------------------------------------------------------------
	bool Polygon::attachToTerrain()
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

		//------------------------------------------
		// 开始更新box3d信息
		// 自己算exterior即可
		//------------------------------------------
		_box3d = Box3d::NULL_BOX;
		if ( _rings.empty() == false )
		{
			for(int j = 0; j < _rings[0]._numPoints; j++)
			{
				GLdouble* addr = _rings[0]._pointsBeginAddr + 3 * j;
				_box3d.merge( Vec3d( addr) );
			}
		}


		//------------------------------------------
		// 开始复制wkb
		//------------------------------------------
		uchar* buf = new uchar[ _wkbSize ];
		memset( buf, 0 , _wkbSize );

		memcpy( buf, _wkbBuffer , _wkbSize );

		bool isopengl = _isOpenGLCoordinate;
		std::vector<RingStruct> ring;

		readWkbData( buf , _wkbSize , ring );

		converToCoordinate( isopengl , buf , ring , false );

		OGRFeaturePtr pfeat = getOGRFeaturePtr();
		assert( pfeat.isNull() == false );

		
		//OGRGeometry* geo = pfeat->GetGeometryRef();

		OGRGeometry* newgeo =
			OGRGeometryFactory::createGeometry( wkbPolygon25D );

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
	void Polygon::invalidateRendering()
	{
		clearDisplayListID();
	}
	//----------------------------------------------------------------
	void Polygon::clearDisplayListID()
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
