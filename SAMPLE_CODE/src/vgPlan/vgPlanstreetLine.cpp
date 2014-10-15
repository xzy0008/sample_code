

#include <vgStableHeaders.h>
#include <vgPlan/vgPlanstreetLine.h>
#include <vgVector/vgvGeometry.h>

#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkVec2.h>

#include <vgVector/vgvLine.h>
#include <vgVector/vgvShapeItem.h>
#include <vgVector/vgvVectorManager.h>

namespace vgPlan
{

	vgPlanstreetLine::vgPlanstreetLine()
	{
		geo = NULL;
	
		m_pStreetGeometry = NULL;

		_wkbBuffer = NULL;	
	}

	vgPlanstreetLine::vgPlanstreetLine( vgVector::vgvLayer* line, float _width )
	{
//  		vgVector::ShapeItemArray& shapeItemArray = 
//  			vgVector::VectorManager::getSingleton().getShapeItemArray();
//  
//  		tempvec = vgKernel::Vec3::ZERO;
//  
//  
//  		for(vgVector::ShapeItemArrayItr itr = shapeItemArray.begin();
//  			itr != shapeItemArray.end(); itr ++ )
//  		{
//  			if ((*itr)->getGeometryPtr()->getGeometryType() == vgVector::vgGeometryLine )
//  			{
//  				vgVector::Vertex3DPtrArray *aa = ((vgVector::vgvLine*)((*itr)->getGeometryPtr().getPointer()))->getVertex3DArrayPtr();
//  				
//  				int a = aa->size();			
//  				
//  				if ( a < 2)
//  				{
//  					continue;	
//  				}
//  
//  				for ( int i =0 ; i < a; i++)
//  				{
//  					vgKernel::Vec3 pp = *(aa->at(i));
//  
//  					if ( pp != tempvec )
//  					{
//  						linevecs.push_back( pp );
//  						
//  						tempvec = pp;
//  					}
//  				}
//  			}
//  		}
//  
//  		geo = NULL;
//  
//  		_wkbSize = -1;
//  
//  		_wkbBuffer = NULL;
//  
//  		b_updatarender = false;
//  
//  		b_multipolygen = false;
//  
//  		genheadvertex();
//  
//  		genendvertex();
//  
//  		genpolyvertexs( _width );
//  
//  		gengeometry();
	}

	vgPlanstreetLine::~vgPlanstreetLine()
	{
		delete geo;

		geo = NULL;

		delete[] _wkbBuffer;

		_wkbBuffer = NULL;
	}

	void vgPlanstreetLine::gengeometry()
	{
		geo = 
			OGRGeometryFactory::createGeometry( wkbLinearRing );

		OGRLinearRing* pRing =  dynamic_cast<OGRLinearRing*>(geo);
		assert(pRing);
		for (deque<vgKernel::Vec3>::iterator itr = polyvecs.begin();
			itr != polyvecs.end();
			itr ++)
		{
			pRing->addPoint((*itr).x, -(*itr).z);//水平面:x_-z
		}
		pRing->addPoint(polyvecs[0].x, -polyvecs[0].z);//水平面:x_-z


		geo = OGRGeometryFactory::createGeometry( wkbPolygon );

		OGRPolygon* pPolySelector =  dynamic_cast<OGRPolygon*>(geo);
		assert(pPolySelector);

		pPolySelector->addRingDirectly(pRing);
	}

	void vgPlanstreetLine::genpolyvertexs( float _width )
	{
		for(int i = 0; i < linevecs.size()-2; i++)
		{
			vgKernel::Vec2 v1(linevecs[i].x, linevecs[i].z);
			vgKernel::Vec2 v2(linevecs[i+1].x, linevecs[i+1].z);
			vgKernel::Vec2 v3(linevecs[i+2].x, linevecs[i+2].z);

			vgKernel::Vec3 bb = GalPoint(v1, v2, v3, linevecs[i+1].y, _width);

			vgKernel::Vec3 cc(bb);
			cc.x = v2.x * 2 - bb.x;
			cc.z = v2.y * 2 - bb.z;

			polyvecs.push_back(bb);
			polyvecs.push_front(cc);
		}
	}

	void vgPlanstreetLine::genheadvertex()
	{
		if ( linevecs.size() >= 2 )
		{
			vgKernel::Vec2 v1(linevecs[0].x, linevecs[0].z);

			vgKernel::Vec2 v2(linevecs[1].x, linevecs[1].z);

			vgKernel::Vec2 v3 = v1 - ( v2 - v1);

			vgKernel::Vec3 head(v3.x, linevecs[0].y, v3.y );

			vector<vgKernel::Vec3>::iterator _begin = linevecs.begin();

			linevecs.insert( _begin,head );
		}
	}

	void vgPlanstreetLine::genendvertex()
	{
		int k = linevecs.size();

		if ( k >= 2 )
		{
			vgKernel::Vec2 v5(linevecs[k-2].x, linevecs[k-2].z);
			vgKernel::Vec2 v6(linevecs[k-1].x, linevecs[k-1].z);

			vgKernel::Vec2 v4 = v6 + ( v6 - v5);

			vgKernel::Vec3 end(v4.x, linevecs[k-1].y, v4.y );

			linevecs.push_back( end );
		}
	}

	float vgPlanstreetLine::mathcal1(vgKernel::Vec2 &V1, vgKernel::Vec2 &V2)
	{
		float a = sqrt((V1.x - V2.x) * (V1.x - V2.x) + (V1.y - V2.y) * (V1.y - V2.y));

		return a;

	}

	vgKernel::Vec3 vgPlanstreetLine::GalPoint(vgKernel::Vec2 &V1, vgKernel::Vec2 &V2, 
									vgKernel::Vec2 &V3, float &y, float _width)
	{
		float a = mathcal1(V1, V2);

		float c = mathcal1(V3, V2);

		double b = a*((V3.x - V2.x)*_width*a + (V2.x*V1.y - V1.x*V2.y)*(V3.x-V2.x) - V2.x*(V3.x-V2.x)*(V1.y-V2.y) - V2.y*(V3.y-V2.y)*(V1.y-V2.y));

		double d = c*((V1.x - V2.x)*_width*a + (V2.x*V1.y - V1.x*V2.y)*(V1.x-V2.x) - V2.x*(V1.x-V2.x)*(V1.y-V2.y) - V2.y*(V1.y-V2.y)*(V1.y-V2.y));

		double e = c*a*a - a*((V3.x-V2.x)*(V1.x-V2.x)+(V3.y-V2.y)*(V1.y-V2.y));

		if (e == 0)
		{
			e = 0.1;
		}

		double z = (b-d)/e;

		double t = V1.y - V2.y;

		double x;

		if ( V1.y == V2.y)
		{
			x = V2.x - _width;
		}
		else
		x = (_width*a + (V1.x-V2.x)*z + V2.x*V1.y - V1.x*V2.y)/t;

		return vgKernel::Vec3(x,y,z);

	}

	void vgPlanstreetLine::Updategeometrypoints()
	{
 		polyvecs.clear();
 
 		genpolyvertexfromgeo();
	}

	void vgPlanstreetLine::converToCoordinate( bool isopenglCoord , 
		uchar* buf , 
		std::vector<RingStruct>& rings, const bool convert_to_opengl)
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

	bool vgPlanstreetLine::readWkbData(  uchar* buf , int buf_size
		,std::vector<RingStruct>& out_rings)
	{


		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}

		out_rings.clear();

		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
/*		assert( geotype == wkbPolygon25D );*/
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

		return true;
	}

	//----------------------------------------------------------------
	bool vgPlanstreetLine::readWkbDatamulti(uchar* buf , int buf_size , 
		std::vector<RingStructVec>& out_polyrings )
	{
		out_polyrings.clear();

		assert( buf != NULL );
		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbMultiPolygon25D );
		pbuf += sizeof( int );

		// num_wkbPolygons
		int num_wkbPolygons = *(int*)pbuf;
		pbuf += sizeof( int );

		for ( int i = 0 ; i < num_wkbPolygons ;++ i )
		{
			RingStructVec rings;

			long readnum = readSinglePolygonData( pbuf , rings );

			pbuf += readnum;

			out_polyrings.push_back( rings );
		}

		assert( (pbuf - buf) == buf_size );

		return true;
	}

	void vgPlanstreetLine::genpolyvertexfrompolygeo()
	{
		clearRecoverableData();

		clearmultiRecoverableData();

		OGRPolygon* poly = ( OGRPolygon* )geo;
		//------------------------------------------
		// 设定为25D模式
		//------------------------------------------
		int dimension = geo->getDimension();
		if ( dimension != 3 )
		{
			geo->setCoordinateDimension( 3 );
		}



		_wkbSize = poly->WkbSize();
		
		assert( _wkbSize > 0 );

		if ( _wkbSize <= 0 )
		{
			return ;
		}

		assert( _wkbBuffer == NULL );

		_wkbBuffer = new uchar[ _wkbSize ];
		memset( _wkbBuffer , 0 , _wkbSize );

		// 导出到wkb缓冲区
		OGRErr err = poly->exportToWkb( wkbNDR , _wkbBuffer );
		if ( err != OGRERR_NONE )
		{
			clearRecoverableData();
			return;
		}

		//------------------------------------------
		// 开始读取wkb数据
		//------------------------------------------
		bool readwkbok = readWkbData( _wkbBuffer , _wkbSize ,_rings );

		converToCoordinate( false , 
			_wkbBuffer , _rings , true );
	}

	void vgPlanstreetLine::genpolyvertexfromgeo()
	{
		if ( wkbFlatten( geo->getGeometryType() ) != wkbPolygon
			&& wkbFlatten(geo->getGeometryType() )!= wkbMultiPolygon)
		{
			assert(0);
			return ;
		}

		if (  wkbFlatten( geo->getGeometryType() ) == wkbPolygon )
		{
			b_multipolygen = false;

			genpolyvertexfrompolygeo();
		}
		else if ( wkbFlatten( geo->getGeometryType() ) == wkbMultiPolygon )
		{
			b_multipolygen = true;

			genpolyvertexfrommultipolygeo();
		}
		else
			return;
	}

	void vgPlanstreetLine::genpolyvertexfrommultipolygeo()
	{

		clearRecoverableData();

		clearmultiRecoverableData();

		OGRMultiPolygon* poly = ( OGRMultiPolygon* )geo;

		//------------------------------------------
		// 设定为25D模式
		//------------------------------------------
		int dimension = geo->getDimension();
		if ( dimension != 3 )
		{
			geo->setCoordinateDimension( 3 );
		}



		_wkbSize = poly->WkbSize();
	
		if ( _wkbSize <= 0 )
		{
			return ;
		}

		assert( _wkbBuffer == NULL );

		_wkbBuffer = new uchar[ _wkbSize ];
		memset( _wkbBuffer , 0 , _wkbSize );

		// 导出到wkb缓冲区
		OGRErr err = poly->exportToWkb( wkbNDR , _wkbBuffer );
		if ( err != OGRERR_NONE )
		{
			clearmultiRecoverableData();
			return ;
		}

		//------------------------------------------
		// 开始读取wkb数据
		//------------------------------------------
		bool readwkbok = readmultiWkbData( _wkbBuffer , _wkbSize , _polygonRings );
		if ( readwkbok == false )
		{
			clearmultiRecoverableData();
			return;
		}

		//------------------------------------------
		// 转换坐标
		//------------------------------------------
		convermultiToCoordinate( false , 
			_wkbBuffer , _polygonRings , true );

	}
	//----------------------------------------------------------------
	void vgPlanstreetLine::clearRecoverableData()
	{
		if ( _wkbBuffer != NULL )
		{
			delete[] _wkbBuffer;
			_wkbBuffer = NULL;
		}
		_wkbSize = -1;

		_rings.clear();
	}
	void vgPlanstreetLine::renderpoly()
	{

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
		glPopMatrix();

		glEnable( GL_TEXTURE_2D );
	}
	void vgPlanstreetLine::rendermultipoly()
	{
		glDisable( GL_TEXTURE_2D );
		//glPushAttrib(GL_CURRENT_BIT);

		glPushMatrix();
		{
			std::vector<RingStructVec>::iterator iter = _polygonRings.begin();
			std::vector<RingStructVec>::iterator iter_end = _polygonRings.end();

			for ( ; iter != iter_end ; ++iter )
			{
				renderRings( *iter );
			}
		}

		VGK_CHECK_OPENGL_ERROR();

		glPopMatrix();
	}
	void vgPlanstreetLine::render()
	{
		if ( !b_updatarender )
		{
			Updategeometrypoints();

			b_updatarender = true;
		}

		if(b_multipolygen)
			rendermultipoly();
		else
			renderpoly();
	}

	void vgPlanstreetLine::clearmultiRecoverableData()
	{
		if ( _wkbBuffer != NULL )
		{
			delete[] _wkbBuffer;
			_wkbBuffer = NULL;
		}
		_wkbSize = -1;
		_polygonRings.clear();
	}
	//----------------------------------------------------------------
	bool vgPlanstreetLine::readmultiWkbData(uchar* buf , int buf_size , 
		std::vector<RingStructVec>& out_polyrings )
	{
		out_polyrings.clear();

		assert( buf != NULL );
		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbMultiPolygon25D );
		pbuf += sizeof( int );

		// num_wkbPolygons
		int num_wkbPolygons = *(int*)pbuf;
		pbuf += sizeof( int );

		for ( int i = 0 ; i < num_wkbPolygons ;++ i )
		{
			RingStructVec rings;

			long readnum = readSinglePolygonData( pbuf , rings );

			pbuf += readnum;

			out_polyrings.push_back( rings );
		}

		assert( (pbuf - buf) == buf_size );

		return true;
	}


	long vgPlanstreetLine::readSinglePolygonData(  uchar* buf , 
		RingStructVec& out_rings  )
	{
		uchar* pbuf = buf;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );

		// 检查type
		int geotype = *(int*)pbuf;

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
			assert(0);
			return -1;
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

		return pbuf - buf;
	}


	void vgPlanstreetLine::convermultiToCoordinate( bool isopenglCoord ,
		uchar* buf , std::vector<RingStructVec>& polyrings,
		const bool convert_to_opengl )
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

			std::vector<RingStructVec>::iterator iter = polyrings.begin();
			std::vector<RingStructVec>::iterator iter_end = polyrings.end();

			for ( ; iter != iter_end ; ++iter )
			{
				RingStructVec& _rings = *iter;

				assert( _rings.empty() == false );

				for ( int i = 0 ; i < _rings.size() ; ++ i )
				{
					for ( int j = 0 ; j < _rings[i]._numPoints ;  ++ j )
					{
						double* addr =  _rings[i]._pointsBeginAddr + 3 * j;

						double tmp = *( addr + 1 ); 
						*( addr + 1 ) = *( addr + 2 ); // 保存高度Y
						*( addr + 2 ) = -tmp; // z坐标取反
					}
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

			std::vector<RingStructVec>::iterator iter = polyrings.begin();
			std::vector<RingStructVec>::iterator iter_end = polyrings.end();

			for ( ; iter != iter_end ; ++iter )
			{
				RingStructVec& _rings = *iter;

				assert( _rings.empty() == false );

				for ( int i = 0 ; i < _rings.size() ; ++ i )
				{
					for ( int j = 0 ; j < _rings[i]._numPoints ;  ++ j )
					{
						double* addr =  _rings[i]._pointsBeginAddr + 3 * j;

						double tmp = *( addr + 1 ); 
						*( addr + 1 ) = -*( addr + 2 ); // z坐标取反
						*( addr + 2 ) = tmp; // 保存高度Y
					}
				}
			}

			isopenglCoord = false;
		}

		return;
	}

	void vgPlanstreetLine::renderRings( RingStructVec& ringstruct )
	{
		RingStructVec& _rings = ringstruct;

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

		return;
	}


	// =========new version code here=================

	bool vgPlanstreetLine::setStreetGemo(OGRGeometry *pGemo, const vgKernel::Mat4& mat)
	{
		if (m_pStreetGeometry != NULL)
		{
			delete m_pStreetGeometry;
			m_pStreetGeometry = NULL;
		}

		m_pStreetGeometry = pGemo;

		int dimension = m_pStreetGeometry->getDimension();
		if ( dimension != 3 )
		{
			m_pStreetGeometry->setCoordinateDimension( 3 );
		}

		int bufferSize = m_pStreetGeometry->WkbSize();
		unsigned char *wkbBuffer = new unsigned char[bufferSize];

		OGRErr err = m_pStreetGeometry->exportToWkb(wkbNDR, wkbBuffer);

		if (err != OGRERR_NONE)
		{
			delete [] wkbBuffer;
			return false;
		}

		unsigned char *bufferStart = wkbBuffer;

		byte byteorder = *wkbBuffer;
		assert( byteorder == wkbNDR );
		wkbBuffer += sizeof( byte );

		// 检查type
		int geotype = *(int*)wkbBuffer;
		assert( geotype == wkbLineString25D );
		wkbBuffer += sizeof( int );

// 		// numRings
// 		int numRings = *(int*)wkbBuffer;
// 		wkbBuffer += sizeof( int );

		// numPoints
		int numPoints = *(int*)wkbBuffer;
		wkbBuffer += sizeof( int );

		assert( numPoints >= 0);
		if ( numPoints <= 0 )
		{
			return false;
		}

		for ( int i = 0 ; i < numPoints ; ++ i )
		{
			double *px = (double*)(wkbBuffer);
			double *py = (double*)(wkbBuffer + sizeof(double)*2);
			double *pz = (double*)(wkbBuffer + sizeof(double));

			vgKernel::Vec3 point(*px, - (*py), *pz);

			vgKernel::Vec3 newPoint = vgKernel::Math::translateVec3(mat, point);

			double *pCoord = (double*)wkbBuffer;
			*pCoord = newPoint.x;
			pCoord = (double*)(wkbBuffer+sizeof(double));
			*pCoord = newPoint.z;
			pCoord = (double*)(wkbBuffer+sizeof(double)*2);
			*pCoord = -newPoint.y;

			wkbBuffer += sizeof( double ) * 3;
		}

		assert( (wkbBuffer - bufferStart) == bufferSize );


		m_pStreetGeometry->importFromWkb(bufferStart);

		delete []bufferStart;

		return true;
	}

	bool vgPlanstreetLine::setLinePoints(const vgShape::RingStruct& ringStruct)
	{
		int numOfPoints = ringStruct._numPoints;
		linevecs.clear();

		stringstream outString;
	
		for (int i=0; i<numOfPoints; i++)
		{
			linevecs.push_back(vgKernel::Vec3(*(ringStruct._pointsBeginAddr + i*3),
											  *(ringStruct._pointsBeginAddr + i*3+1),
											  *(ringStruct._pointsBeginAddr + i*3+2)));
		}
		
		// outString<< "Points : " << linevecs.size() << "\n";
		
		// VGK_SHOW(outString.str());

		return true;
	}

	bool vgPlanstreetLine::setLinePoints(const vgShape::RingStruct& ringStruct, const vgKernel::Mat4& matrix)
	{
		int numOfPoints = ringStruct._numPoints;
		linevecs.clear();

		stringstream outString;

		for (int i=0; i<numOfPoints; i++)
		{
 			vgKernel::Vec3 tmpPoint(*(ringStruct._pointsBeginAddr + i*3),
 				*(ringStruct._pointsBeginAddr + i*3+1),
 				*(ringStruct._pointsBeginAddr + i*3+2));

			vgKernel::Vec3 point = vgKernel::Math::translateVec3(matrix, tmpPoint);
			linevecs.push_back(point);
		}

		return true;
	}

	bool vgPlanstreetLine::convertLineToPoly(int width)
	{
		if (geo != NULL)
		{
			delete geo;
		}
		geo = NULL;
		  
		_wkbSize = -1;
		  
		if (_wkbBuffer != NULL)
		{
			delete _wkbBuffer;
		}
		_wkbBuffer = NULL;
		  
  		b_updatarender = false;
  
  		b_multipolygen = false;
		  
		// 在起始顶点之前生成一个point
  		genheadvertex();
  
		// 在结尾顶点之后生成一个point
  		genendvertex();
  
		// 生成poly
  		genpolyvertexs( width );
  
		// 在此添加贴地代码
  		gengeometry();

		return true;
	}
}