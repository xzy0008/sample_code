



#include <vgStableHeaders.h>
#include <vgGis3D/vggiBuffer.h>

#include <vgGis3D/vggiPrerequisite.h>

#include <vgTerritory/vgtTerrainManager.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgGIS3D/vggiPoint.h>
#include <vgGIS3D/vggiLine.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkCoordSystem.h>
#include <vgGIS3D/vggiBuildingSolid.h>
#include <vgGIS/vgGisManager.h>

namespace vgGIS3D {


	//--------------------------------------------------------------
	Buffer::Buffer()
	{
		m_bRenderOutline = true;
		m_bRenderBuffer = true;

		m_callListId = 0;

		m_wkbSize = -1;
		m_wkbBuffer = NULL;

		m_pPlugin = NULL;
		m_bLoadTerrainDLL = false;
		m_bHasTerrain = false;
		m_terrainCellSize = 0;

		m_bNeedLine = false;
		m_bLeftRightBuffer = false;
		m_bNeedDestroyOgr = false;

		m_matrix = vgKernel::Mat4::IDENTITY;

		m_pAnalsisLayer = NULL;
	}

	//--------------------------------------------------------------
	Buffer::~Buffer()
	{ 
		unrenderModelAnalysisResult();
		unrenderShapeAnalysisResult();
		unInit();
	}

	//--------------------------------------------------------------
	bool Buffer::genBuffer( const GeometryPointerVec* pGeoVec, double radius, int nQuadSegs /*=30*/  )
	{
		if ( radius < 0 || vgKernel::Math::Abs( radius ) < 0.00001 )
		{
			string msg;
			msg = "缓冲半径必需大于0！";
			vgKernel::SystemUtility::showModelDialog( msg );
			return false;
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
		vgGIS3D::GisManager::getSingleton().setProcessingInfo("正在生成缓冲区...");

		for (int i=0; i<pGeoVec->size(); i++)
		{
			vgGIS3D::GisManager::getSingleton().setProcessingProgress((int)((float)i/pGeoVec->size()*100));

			// 调用平台Geometry类的接口生成buffer
			Geometry* pGeo = pGeoVec->at(i);

			OGRGeometry* pBuffer = pGeo->Buffer( radius, nQuadSegs );

			if ( pBuffer != NULL )
			{
				m_ogrGeoPtrVec.push_back( pBuffer );
			}
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

		if ( !pGeoVec->empty() )
		{
			m_matrix = ((pGeoVec->at(0))->getFatherLayer())->getMatrix();
		}

		bufferUnion();  // 缓冲区求并

		checkTerrainLoad();  // 检测贴地相关信息

		attachToTerrain();  // 缓冲区贴地处理
		
		return true;
	}

	//--------------------------------------------------------------
	void Buffer::render()
	{
		if ( m_callListId == 0 )
		{
			m_callListId = glGenLists( 1 );
			assert( m_callListId != 0 );

			glNewList( m_callListId, GL_COMPILE );
				renderOnceForDisplayList();
			glEndList();
		}
		else
		{
			glPushMatrix();
				glCallList( m_callListId );
			glPopMatrix();
		}
	}

	//--------------------------------------------------------------
	void Buffer::renderOnceForDisplayList()
	{
		glDisable( GL_TEXTURE_2D );
		glDisable( GL_DEPTH_TEST );

		glPushMatrix();

		    ////////////////////////////////////画轮廓线
			if ( m_bRenderOutline )
			{
				glColor3f( 0.0, 0.0, 0.0 );
				for ( int i = 0 ; i < m_ptDataVec.size() ; i++ )
				{
					glBegin( GL_LINE_LOOP );
					for( int j = 0; j < m_ptDataVec[i].size(); j++ )
					{
						glVertex3fv( m_ptDataVec[i][j]->v );
					}
					glEnd();
				}
			}
			

			////////////////////////////////////画轮缓冲区
			if( m_bRenderBuffer )
			{
				/////////实现半透明//////////////////////
				glAlphaFunc( GL_GREATER, 0.0f );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

				glEnable( GL_ALPHA_TEST );
				glEnable( GL_BLEND );

				glColor4f( (GLfloat)1.0, (GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.5 );


				////////////////////////////////////////////////////////////
				//**************************填充多边************************

				// 创建分格化对像 
				GLUtesselator *pTess = NULL;
				pTess = gluNewTess();

				// 注册多个回调函数
				gluTessCallback( pTess, GLU_BEGIN, (void(__stdcall*)())glBegin );
				gluTessCallback( pTess, GLU_END, (void(__stdcall*)())glEnd );
				gluTessCallback( pTess, GLU_VERTEX, (void(__stdcall*)())glVertex3dv );

				// 设置分格属性
				gluTessProperty( pTess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD );

				gluTessBeginPolygon( pTess, NULL );
				for ( int i = 0 ; i < m_ptDataVec.size() ; i++ )
				{
					gluTessBeginContour( pTess );
					for ( int j = 0; j < m_ptDataVec[i].size(); j++ )
					{
						Vec3d* pt = new Vec3d( *( m_ptDataVec[i][j] ) );

						// 这里要求第二个参数为double类型数组
						gluTessVertex( pTess, pt->v, pt->v );

						m_vecForTess.push_back( pt );

					} // end for j
					gluTessEndContour( pTess );

				} // end for i
				gluTessEndPolygon( pTess );  // 多边形分格完成

				// 删除分格对象
				gluDeleteTess( pTess );
				pTess = NULL;

				//*****************************************************************

				///关闭相应状态/////////////////////
				glDisable( GL_ALPHA_TEST );
				glDisable( GL_BLEND );
				////////////////////////////////////

				//VGK_CHECK_OPENGL_ERROR();
			}
			
		glPopMatrix();
		
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_TEXTURE_2D );
	}

	//--------------------------------------------------------------
	void Buffer::clearDisplayList()
	{
		if ( m_callListId != 0 )
		{
			glDeleteLists( m_callListId, 1 );
			m_callListId = 0;
		}
	}

	//--------------------------------------------------------------
	bool Buffer::bufferUnion()
	{
		if ( m_ogrGeoPtrVec.size() == 1 )
		{
			if ( m_bLeftRightBuffer )
			{
				m_bNeedDestroyOgr = true;
				clearPtDataVec();
			}
			return true;
		}
		
		// 调用OGR的接口实现Buffer的合并
		OGRGeometry* pResult = ( m_ogrGeoPtrVec.at(0) )->Union( m_ogrGeoPtrVec.at(1) );

		assert( pResult != NULL );
		if ( pResult == NULL )
		{
			return false;
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
		vgGIS3D::GisManager::getSingleton().setProcessingInfo("开始合并缓冲区...");

		// 对其余缓冲区循环求并
		for ( int i = 2; i < m_ogrGeoPtrVec.size(); i++ )
		{
			vgGIS3D::GisManager::getSingleton().setProcessingProgress((int)((float)i/m_ogrGeoPtrVec.size()*100));

			pResult = pResult->Union( m_ogrGeoPtrVec.at(i) );

			assert( pResult != NULL );
			if ( pResult == NULL )
			{
				return false;
			}
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

		// 清空原数组，重新装入新元素
		if ( m_bLeftRightBuffer )
		{
			destroyOgrGeo();
			clearPtDataVec();
		}

		m_ogrGeoPtrVec.clear();
		m_ogrGeoPtrVec.push_back( pResult );

		return true;
	}

	//--------------------------------------------------------------
	void Buffer::attachToTerrain()
	{
		if ( m_ogrGeoPtrVec.size() <= 0 )
		{
			return;
		}

		switch( m_ogrGeoPtrVec[0]->getGeometryType() )
		{
		case wkbPolygon:
			{
				getDataFromOgrGeo( m_ogrGeoPtrVec[0] );

				clearRecoverableData();
			}
			break;

		case wkbMultiPolygon:
			{
				OGRGeometryCollection* pOgrGeoCollection = 
					dynamic_cast<OGRGeometryCollection*>( m_ogrGeoPtrVec[0]);

				for ( int i = 0; i < pOgrGeoCollection->getNumGeometries(); i++ )
				{
					OGRGeometry* pOgrGeo = pOgrGeoCollection->getGeometryRef( i );
					assert( pOgrGeo->getGeometryType() != wkbMultiPolygon );

					getDataFromOgrGeo( pOgrGeo );

					clearRecoverableData();
				}
			}
			break;

		default:
			break;

		}  // end switch
	}

	//--------------------------------------------------------------
	void Buffer::getDataFromOgrGeo( const OGRGeometry* pOgrGeo )
	{
		m_wkbSize = pOgrGeo->WkbSize();
		assert( m_wkbSize > 0 );
		if ( m_wkbSize <= 0 )
		{
			return;
		}


		assert( m_wkbBuffer == NULL );
		m_wkbBuffer = new uchar[ m_wkbSize ];
		memset( m_wkbBuffer , 0 , m_wkbSize );


		// 导出到wkb缓冲区
		OGRErr err = pOgrGeo->exportToWkb( wkbNDR , m_wkbBuffer );
		if ( err != OGRERR_NONE )
		{
			clearRecoverableData();
		}

		//------------------------------------------
		// 开始读取wkb数据
		//------------------------------------------
		bool readwkbok = readWkbData( m_wkbBuffer , m_wkbSize );
		if ( readwkbok == false )
		{
			clearRecoverableData();
		}

	}

	//--------------------------------------------------------------
	bool Buffer::readWkbData(  uchar* buf , int buf_size )
	{
		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}


		uchar* pbuf = buf;


		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );


		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbPolygon );
		pbuf += sizeof( int );


		// numRings
		int numRings = *(int*)pbuf;
		pbuf += sizeof( int );


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

			// 插值以便于贴地
			interpolation( numPoints, (double*)pbuf ); 

			// 跳过这些点.
			pbuf += sizeof( double ) * 2 * numPoints;
		}

		assert( ( pbuf - buf ) == buf_size );

		return true;
	}

	//--------------------------------------------------------------
	void Buffer::interpolation( int ptNum, double* addr )
	{
		Vec3PtrVec  vec;
		vec.clear();


		for ( int i = 0; i < ptNum - 1; i++ )
		{
			Vec3* p1 = new Vec3( addr[2*i], 0, -addr[2*i+1] );
			Vec3* p2 = new Vec3( addr[2*i+2], 0, -addr[2*i+3] );

			if ( m_bLoadTerrainDLL && m_bHasTerrain )  // 插值
			{
				int num = ( *p1 - *p2 ).length() / m_terrainCellSize;
				
				if ( num > 0 ) 
				{
					float dx = ( p2->x - p1->x ) / num;
					float dz = ( p2->z - p1->z ) / num;

					for ( int k = 0 ; k < num ; ++ k )
					{
						Vec3* t = new Vec3(0,0,0);
						t->x = p1->x + dx * k;
						t->z = p1->z + dz * k;

						float elev = 0.0f;

						*t = vgKernel::Math::translateVec3( m_matrix, *t );

						VGK_DLL_DECLARE_CLASSFUNC( m_pPlugin, TerrainManager, getElevationByPosition, pfn1 );
						assert( pfn1 != NULL );

						if ( pfn1( *t, elev, true ) )
						{
							t->y = elev;
						}
						
						vec.push_back( t );
					}

					if ( i == ptNum - 1 )  // 加入最后一个
					{
						float elev = 0.0f;

						*p2 = vgKernel::Math::translateVec3( m_matrix, *p2 );

						VGK_DLL_DECLARE_CLASSFUNC( m_pPlugin, TerrainManager, getElevationByPosition, pfn2 );
						assert( pfn2 != NULL );

						if ( pfn2( *p2, elev, true ) )
						{
							p2->y = elev;
						}
						
						vec.push_back( p2 );
					}
				}
				else // 无需插入新点
				{
					float elev = 0.0;

					if ( vec.empty() )  // 保证点不重复，避免产多余的点
					{
						*p1 = vgKernel::Math::translateVec3( m_matrix, *p1 );

						VGK_DLL_DECLARE_CLASSFUNC( m_pPlugin, TerrainManager, getElevationByPosition, pfn3 );
						assert( pfn3 != NULL );

						if ( pfn3( *p1, elev, true ) )
						{
							p1->y = elev;
						}

						vec.push_back( p1 );
					}

					*p2 = vgKernel::Math::translateVec3( m_matrix, *p2 );

					VGK_DLL_DECLARE_CLASSFUNC( m_pPlugin, TerrainManager, getElevationByPosition, pfn4 );
					assert( pfn4 != NULL );

					if ( pfn4( *p2, elev, true ) )
					{
						p2->y = elev;
					}

					vec.push_back( p2 );
				}
				
			}
			else  // 直接加入数组
			{
				if ( vec.empty() )
				{
					*p1 = vgKernel::Math::translateVec3( m_matrix, *p1 );
					vec.push_back( p1 );
				}

				*p2 = vgKernel::Math::translateVec3( m_matrix, *p2 );
				vec.push_back( p2 );
			}
			
		}

		m_ptDataVec.push_back( vec );

	}

	//--------------------------------------------------------------
	OGRGeoPtrVec* Buffer::getBufferVec()
	{
		return &m_ogrGeoPtrVec;
	}

	//--------------------------------------------------------------
	void Buffer::clearRecoverableData()
	{
		if ( m_wkbBuffer != NULL )
		{
			delete[] m_wkbBuffer;
			m_wkbBuffer = NULL;
		}
		m_wkbSize = -1;

	}

	//--------------------------------------------------------------
	void Buffer::checkTerrainLoad()
	{
		m_pPlugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

		// 判断是否加载了地形DLL
		if ( m_pPlugin == NULL )
		{
			return;
		}

		m_bLoadTerrainDLL = true;

		// 判断是否有地形数据
		VGK_DLL_DECLARE_CLASSFUNC( m_pPlugin, TerrainManager, hasTerrainData, pfn );
		if ( pfn == NULL )
		{
			return;
		}

		if ( pfn() )
		{
			m_bHasTerrain = true;
		}


		// 计算地形网格大小 
		if ( m_bHasTerrain && m_bLoadTerrainDLL )
		{
			VGK_DLL_DECLARE_FUNC( m_pPlugin, getMainFileHandleVtrHeader, pfn1 );
			assert( pfn1 != NULL );

			vgTerritory::StructVtrHeader* m_header = (*pfn1)();
			m_terrainCellSize = m_header->cellsize;


			VGK_DLL_DECLARE_FUNC( m_pPlugin, getCurrentHeightLayerNumber, pfn2 );
			assert( pfn2 != NULL );

			long curlayernum = (*pfn2)();

			m_terrainCellSize = m_terrainCellSize * pow( 2.0f, curlayernum );
		}
	}



	//--------------------------------------------------------------
	bool Buffer::genLeftRightBuffer( const GeometryPointerVec* pGeoVec, double leftRadius, 
		double rightRadius, int nQuadSegs /* = 30 */ )
	{
		GeometryPointerVec::const_iterator itr = pGeoVec->begin();
		GeometryPointerVec::const_iterator itr_end = pGeoVec->end();

		if ( leftRadius < 0 || rightRadius < 0 )
		{
			string msg;
			msg = "缓冲区生成失败！缓冲半径不能小于0!";
			vgKernel::SystemUtility::showModelDialog( msg );

			return false;
		}
		else if ( vgKernel::Math::Abs( leftRadius)  < 1E-6 && 
			      vgKernel::Math::Abs( rightRadius ) < 1E-6 ) 
		{
			string msg;
			msg = "缓冲区生成失败！左右半径不能同时为0!";
			vgKernel::SystemUtility::showModelDialog( msg );

			return false;
		}

		for ( ; itr != itr_end; itr++ )
		{
			if ( (*itr)->getType() != GEOMTRY_LINE )
			{
				string msg;
				msg = "缓冲区生成失败！要素要求为简单单线!";
				vgKernel::SystemUtility::showModelDialog( msg );

				unInit();

				return false;
			}


			Vec3PtrVec vec; // 支持多线缓冲区

			if (  vgKernel::Math::Abs( leftRadius) < 0.00001 )
			{
				m_bNeedLine = true;
				genSingleSideBuffer( *itr, vec, RIGHT, rightRadius, nQuadSegs );
				appendLinePt( *itr, vec );
			}
			else if ( vgKernel::Math::Abs( rightRadius ) < 0.00001 )
			{
				m_bNeedLine = true;
				genSingleSideBuffer( *itr, vec, LEFT, leftRadius, nQuadSegs );
				appendLinePt( *itr, vec );
			}
			else
			{
				m_bNeedLine = false;
				genSingleSideBuffer( *itr, vec, RIGHT, rightRadius, nQuadSegs );
				genSingleSideBuffer( *itr, vec, LEFT, leftRadius, nQuadSegs );
			}

			m_bLeftRightBuffer = true;
		}

		constructOgrGeo();

		bufferUnion();

		checkTerrainLoad();

		attachToTerrain();

		return true;
	}

	//--------------------------------------------------------------
	void Buffer::genSingleSideBuffer( Geometry* pGeo, Vec3PtrVec& vec, SideType type, double radius, int nQuadSegs /* = 30 */ )
	{
		assert ( radius > 0 );

		// 生成OGR缓冲区
		OGRGeometry* pBuffer = pGeo->Buffer( radius, nQuadSegs );
		assert( pBuffer != NULL );


		// ------------------------------------------
		// 读取OGRWkb中的数据
		//-------------------------------------------

		m_wkbSize = pBuffer->WkbSize();
		assert( m_wkbSize > 0 );
		if ( m_wkbSize <= 0 )
		{
			return;
		}

		assert( m_wkbBuffer == NULL );
		m_wkbBuffer = new uchar[ m_wkbSize ];
		memset( m_wkbBuffer , 0 , m_wkbSize );


		// 导出到wkb缓冲区
		OGRErr err = pBuffer->exportToWkb( wkbNDR , m_wkbBuffer );
		if ( err != OGRERR_NONE )
		{
			clearRecoverableData();
		}


		uchar* pbuf = m_wkbBuffer;

		// 检查byteorder
		byte byteorder = *pbuf;
		assert( byteorder == wkbNDR );
		pbuf += sizeof( byte );


		// 检查type
		int geotype = *(int*)pbuf;
		assert( geotype == wkbPolygon );
		pbuf += sizeof( int );


		// numRings
		int numRings = *(int*)pbuf;
		pbuf += sizeof( int );

		assert( numRings > 0);
		if ( numRings <= 0 )
		{
			return;
		}

		LineString* pLine = (LineString*)pGeo;
		assert( pLine != NULL );

		for ( int i = 0 ; i < 1 /*numRings*/; ++ i )  // 此处i < 1 排除岛的干扰，但有失精度
		{
			int numPoints = *(int*)pbuf;
			assert( numPoints > 0 );
			pbuf += sizeof( int );

			genOutlinePt( (double*)pbuf, pLine->getRing(), vec, type, radius, numPoints );

			pbuf += sizeof( double ) * 2 * numPoints;
		}

		clearRecoverableData();
	}

	//--------------------------------------------------------------
	bool Buffer::genOutlinePt( const double* addr, const RingStruct& rs, Vec3PtrVec& vec,
		SideType type, double radius,  int numPts )
	{
		Vec3 firstPt, lastPt;
		calculateTowEndpoint( rs, radius, firstPt, lastPt );

		if ( type == LEFT )
		{
			/*CFile file;
			file.Open( "F:\\result\\left.txt", CFile::modeCreate|CFile::modeWrite );
			CString str;
			for ( int i = 0; i < numPts; i++ )
			{
				str.Empty();
				str.Format( "%.8f  %.8f", addr[2*i], -addr[2*i+1] );
				file.Write( str, str.GetLength() );
				file.Write( "\r\n", 2 );
			}
			file.Close();*/

			// 找到起始端点与结束端点的索引号
			int startIndex, endIndex;
			findStartAndEndIndex( addr, numPts, firstPt, lastPt, startIndex, endIndex );

			// 此情况为--OGR轮廓线从中间而非两端点开始
			if ( startIndex > endIndex )
			{
				for ( int i = endIndex; i <= startIndex; i++ )
				{
					Vec3* pt = new Vec3( addr[2*i], 0, -addr[2*i+1] );
					vec.push_back( pt );
				}
			}
			else
			{
				// 从结束端点一直到最后
				for ( int i = endIndex; i < numPts; i++ )
				{
					Vec3* pt = new Vec3( addr[2*i], 0, -addr[2*i+1] );
					vec.push_back( pt );
				}

				// 从第一个点一直到起始端点
				for ( int i = 0; i <= startIndex; i++ )
				{
					Vec3* pt = new Vec3( addr[2*i], 0, -addr[2*i+1] );
					vec.push_back( pt );
				}
			}

			if ( !m_bNeedLine )
			{
				m_ptDataVec.push_back( vec );
			}
		}
		else if ( type == RIGHT )
		{
			/*CFile file;
			file.Open( "F:\\result\\right.txt", CFile::modeCreate|CFile::modeWrite );
			CString str;
			for ( int i = 0; i < numPts; i++ )
			{
				str.Empty();
				str.Format( "%.8f  %.8f", addr[2*i], -addr[2*i+1] );
				file.Write( str, str.GetLength() );
				file.Write( "\r\n", 2 );
			}
			file.Close();*/

			 // 找到起始端点与结束端点的索引号
			int startIndex, endIndex ;
			findStartAndEndIndex( addr, numPts, firstPt, lastPt, startIndex, endIndex );


			// 此情况为--OGR轮廓线从中间而非两端点开始
			if ( startIndex > endIndex )
			{
				for ( int i = startIndex; i < numPts; i++ )
				{
					Vec3* pt = new Vec3( addr[2*i], 0, -addr[2*i+1] );
					vec.push_back( pt );
				}

				for ( int i = 0; i <= endIndex; i++ )
				{
					Vec3* pt = new Vec3( addr[2*i], 0, -addr[2*i+1] );
					vec.push_back( pt );
				}
			}
			else
			{
				for ( int i = startIndex; i <= endIndex; i++ )
				{
					Vec3* pt = new Vec3( addr[2*i], 0, -addr[2*i+1] );
					vec.push_back( pt );
				}
			}

		}

		return true;
	}

	//--------------------------------------------------------------
	void Buffer::calculateTowEndpoint( const RingStruct& rs, double radius, Vec3& firstPt, Vec3& lastPt )
	{
		assert( rs._numPoints >= 2 );
		if ( rs._numPoints < 2 )
		{
			return;
		}

		// 计算结束端点
		float x1 = rs._pointsBeginAddr[0];
		float z1 = rs._pointsBeginAddr[2];

		float x2 = rs._pointsBeginAddr[3];
		float z2 = rs._pointsBeginAddr[5];

		Vec3 dir = Vec3( x1 - x2, 0, z1 - z2 );
		float divisor = vgKernel::Math::Sqrt( dir.x*dir.x + dir.z*dir.z );

		lastPt.x = x1 + dir.x * radius / divisor;
		lastPt.z = z1 + dir.z * radius / divisor;

		// 计算起始端点
		x1 = rs._pointsBeginAddr[(rs._numPoints-1)*3];
		z1 = rs._pointsBeginAddr[(rs._numPoints-1)*3+2];

		x2 = rs._pointsBeginAddr[(rs._numPoints-2)*3];
		z2 = rs._pointsBeginAddr[(rs._numPoints-2)*3+2];

		dir = Vec3( x1 - x2, 0, z1 - z2 );
		divisor = vgKernel::Math::Sqrt( dir.x*dir.x + dir.z*dir.z );

		firstPt.x = x1 + dir.x * radius / divisor;
		firstPt.z = z1 + dir.z * radius / divisor;
	}

	//--------------------------------------------------------------
	void Buffer::findStartAndEndIndex( const double* addr, int numPts, const Vec3& firstPt, 
		const Vec3 lastPt, int& sIndex, int& eIndex )
	{
		// 查找与端点最近的OGRBuffer轮廓线上点的索引号
		float sMin, eMin;
		float sMinIndex, eMinIndex;

		float sx,sz;
		sx = addr[0] - firstPt.x;
		sz = -addr[1] - lastPt.z;

		sMin = vgKernel::Math::Sqrt( sx*sx + sz*sz );
		sMinIndex = 0;

		float ex,ez;
		ex = addr[0] - lastPt.x;
		ez = -addr[1] - lastPt.z;

		eMin = vgKernel::Math::Sqrt( ex*ex + ez*ez );
		eMinIndex = 0;

		bool sOk = false;
		bool eOk = false;

		for ( int i = 1; i < numPts; i++ )
		{
			if ( !sOk )
			{
				sx = addr[2*i] - firstPt.x;
				sz = -addr[2*i+1] - firstPt.z;

				float tempSMin = vgKernel::Math::Sqrt( sx*sx + sz*sz );
				if ( tempSMin < sMin )
				{
					sMin = tempSMin;
					sMinIndex = i;
				}

				if ( sMin < 0.0001 )
				{
					sOk = true;
					if ( eOk )
						break;
				}
			}

			if ( !eOk )
			{
				ex = addr[2*i] - lastPt.x;
				ez = -addr[2*i+1] - lastPt.z;

				float tempEMin = vgKernel::Math::Sqrt( ex*ex + ez*ez );
				if ( tempEMin < eMin )
				{
					eMin = tempEMin;
					eMinIndex = i;
				}

				if ( eMin < 0.0001 )
				{
					eOk = true;
					if ( sOk )
						break;
				}
			}
		}

		sIndex = sMinIndex;
		eIndex = eMinIndex;
	}

	//--------------------------------------------------------------
	void Buffer::appendLinePt( Geometry* pGeo, Vec3PtrVec& vec )
	{
		// 数组中最后一个点离Line的哪一端点近从哪端开始加
		LineString* pLine = (LineString*)pGeo;
		assert( pLine != NULL );

		RingStruct rs = pLine->getRing();
		assert( rs._numPoints > 1 );


		// 与线段起点的距离
		float dx = vec[vec.size()-1]->x - rs._pointsBeginAddr[0];
		float dz = vec[vec.size()-1]->z - rs._pointsBeginAddr[2];
		float d1 = vgKernel::Math::Sqrt( dx*dx + dz*dz );


		// 与线段终点的距离
		dx = vec[vec.size()-1]->x - rs._pointsBeginAddr[(rs._numPoints-1)*3];
		dz = vec[vec.size()-1]->z - rs._pointsBeginAddr[(rs._numPoints-1)*3+2];
		float d2 = vgKernel::Math::Sqrt( dx*dx + dz*dz );

		if ( d1 < d2 )
		{
			// 先加入起点
			for ( int i = 0; i < rs._numPoints; i++ )
			{
				Vec3* pt = new Vec3( rs._pointsBeginAddr[3*i], 0, rs._pointsBeginAddr[3*i+2] );
				vec.push_back( pt );
			}
		}
		else
		{
			// 先加入终点
			for ( int i = rs._numPoints - 1; i >= 0; i-- )
			{
				Vec3* pt = new Vec3( rs._pointsBeginAddr[3*i], 0, rs._pointsBeginAddr[3*i+2] );
				vec.push_back( pt );
			}
		}

		m_ptDataVec.push_back( vec );
	}

	//--------------------------------------------------------------
	void Buffer::constructOgrGeo()
	{
		for ( int i = 0; i < m_ptDataVec.size(); i++ )
		{
			OGRGeometry* pGeo = OGRGeometryFactory::createGeometry( wkbLinearRing );
			assert( pGeo != NULL );

			OGRLinearRing* pOgrLinearRing = dynamic_cast<OGRLinearRing*>(pGeo);
			assert( pOgrLinearRing != NULL );

			if ( m_ptDataVec[i].size() <= 0 )
			{
				OGRGeometryFactory::destroyGeometry( pGeo );
				return;
			}

			for ( int j = 0; j < m_ptDataVec[i].size(); j++ )
			{
				pOgrLinearRing->addPoint( (m_ptDataVec[i][j])->x, -(m_ptDataVec[i][j])->z );
			}
			pOgrLinearRing->addPoint( (m_ptDataVec[i][0])->x, -(m_ptDataVec[i][0])->z );

			OGRGeometry* pGeoPloy = OGRGeometryFactory::createGeometry( wkbPolygon );
			assert( pGeoPloy != NULL );

			OGRPolygon* pPloygon = dynamic_cast<OGRPolygon*>(pGeoPloy);
			assert( pPloygon != NULL );

			pPloygon->addRingDirectly( pOgrLinearRing );

			m_ogrGeoPtrVec.push_back( pPloygon );
		}
	}

	//--------------------------------------------------------------
	void Buffer::unInit()
	{
		clearDisplayList();

		assert( m_wkbBuffer == NULL );

		// 使指针指向空
		if ( m_pPlugin != NULL )
		{
			m_pPlugin = NULL;
		}

		clearPtDataVec();

		// 释放内存，此内存用于gluTessVertex
		Vec3dPtrVec::iterator itr = m_vecForTess.begin();
		Vec3dPtrVec::iterator itr_end = m_vecForTess.end();

		for ( ; itr != itr_end; itr++ )
		{
			if ( *itr != NULL )
			{
				delete *itr;
				*itr = NULL;
			}
		}
		m_vecForTess.clear();

		// destroy 生成左右缓冲时create的OGR指针
		if ( m_bNeedDestroyOgr )
		{
			destroyOgrGeo();
		}

		if ( m_pAnalsisLayer != NULL )
		{
			m_pAnalsisLayer->invalidateRendering();
			m_pAnalsisLayer = NULL;
		}
	}

	//--------------------------------------------------------------
	void Buffer::clearPtDataVec()
	{
		// 释放空间，以备重新装入
		for ( int i = 0; i < m_ptDataVec.size(); i++ )
		{
			for ( int j = 0; j < m_ptDataVec[i].size(); j++ )
			{
				if ( m_ptDataVec[i][j] != NULL )
				{
					delete m_ptDataVec[i][j];
					m_ptDataVec[i][j] = NULL;
				}
			}

			m_ptDataVec[i].clear();
		}
		m_ptDataVec.clear();
	}

	//--------------------------------------------------------------
	void Buffer::destroyOgrGeo()
	{
		// 生成左右缓冲区时构造过OGR指针，不用时需destroy

		OGRGeoPtrVec::iterator itr = m_ogrGeoPtrVec.begin();
		OGRGeoPtrVec::iterator itr_end = m_ogrGeoPtrVec.end();

		for ( ; itr != itr_end; itr++ )
		{
			if ( *itr != NULL )
			{
				OGRGeometryFactory::destroyGeometry( *itr );
				*itr = NULL;
			}
		}

		m_ogrGeoPtrVec.clear();
	}
	//--------------------------------------------------------------
	void Buffer::shapeAnalysis( Layer* shapeLayer )
	{
		m_pAnalsisLayer = shapeLayer;

		resultShapeGeomtrys = bufferShapeAnalysis2(shapeLayer);

		if ( resultShapeGeomtrys.empty() )
		{
			String msg = "分析结束，没有找到落入缓冲区中的矢量模型!";
			vgKernel::SystemUtility::showModelDialog( msg );
			return;
		}

		/*GeometryPointerVec::iterator iter = resultShapeGeomtrys.begin();
		GeometryPointerVec::iterator iter_end = resultShapeGeomtrys.end();

		std::ostringstream shapeResult;
		for (; iter != iter_end; ++iter)
		{				
			OGRFeature* ogrPtr = (*iter)->getOGRFeature();
		    OGRGeometry* pShapeGeom = ogrPtr->GetGeometryRef();
			shapeResult << pShapeGeom->getGeometryName() << "\n";
		}*/

		renderShapeAnalysisResult(resultShapeGeomtrys);

		//MessageBox(NULL, shapeResult.str().c_str(), "缓冲区分析结果：", MB_OK);

	}
	//--------------------------------------------------------------
	void Buffer::modelAnalysis( Layer* shapeLayer )
	{
 		OGRGeoPtrVec shpGeomtrys = bufferShapeAnalysis(shapeLayer);

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
		vgGIS3D::GisManager::getSingleton().setProcessingInfo("开始地物分析...");

		for (int i=0; i<shpGeomtrys.size(); i++)
		{
			vgGIS3D::GisManager::getSingleton().setProcessingProgress(
				(int)((float)i/shpGeomtrys.size()*100));

			OGRGeometry* pShpGeo = shpGeomtrys.at(i);

			shapeModelAnalysis(pShpGeo,shapeLayer);
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

		if ( resultQueue.empty() )
		{
			String msg = "分析结束，没有找到落入缓冲区中的地物模型!";
			vgKernel::SystemUtility::showModelDialog( msg );
			return;
		}

		renderModelAnalysisResult(resultQueue);

		//MessageBox(NULL, o.str().c_str(), "缓冲区分析结果：", MB_OK);
	}
	//--------------------------------------------------------------
	void Buffer::shapeModelAnalysis(OGRGeometry* bufferGeometry,Layer* shapeLayer)
	{
		assert(bufferGeometry);

		//得到渲染队列所有元素
		vgKernel::RendererPackage* pAllrenders = vgKernel::RendererManager::getSingleton().getAllRendererPackage();
		vgKernel::RendererPackage::iterator iter_pack = pAllrenders->begin();
		vgKernel::RendererPackage::iterator iter_pack_end = pAllrenders->end();

		//进行遍历
		for (; iter_pack != iter_pack_end; iter_pack++)
		{
			vgKernel::RendererQueue* render_queue = &iter_pack->second;

			vgKernel::RendererQueue::iterator iter = render_queue->begin();
			vgKernel::RendererQueue::iterator iter_end = render_queue->end();
			for (; iter != iter_end; iter++)
			{

				vgKernel::Renderer* ren = *iter;
				vgKernel::Box bouBox = ren->getBoundingBox();

				// 平移到原始shape坐标
				vgKernel::Mat4 mat = shapeLayer->getMatrix();
				mat.inverse();

				vgKernel::Vec3 boxCenter = vgKernel::Math::translateVec3(mat,bouBox.getCenter());

				//构造点
				OGRGeometry* pGeom = 
					OGRGeometryFactory::createGeometry( wkbPoint );
				OGRPoint* pPoint =  dynamic_cast<OGRPoint*>(pGeom);
				assert(pPoint);
				
				pPoint->setCoordinateDimension(2);
				pPoint->setX(boxCenter.x);
				pPoint->setY(-boxCenter.z);

				if (bufferGeometry->Intersect(pPoint))
				{
					resultQueue.push_back(ren);

					o <<ren->getName() << "  坐标位置："<<  ren->getPosition().x << ","
					  << ren->getPosition().y << "," << ren->getPosition().z <<"\n";
				}

			}

		}

		return;
	}
	//--------------------------------------------------------------
	OGRGeoPtrVec Buffer::bufferShapeAnalysis( Layer* shapeLayer )
	{
		OGRGeoPtrVec resultGeom;

		//buffer队列
		OGRGeoPtrVec* pBufferVec = getBufferVec();

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
		vgGIS3D::GisManager::getSingleton().setProcessingInfo("正在进行矢量分析...");

		for (int j=0; j<pBufferVec->size(); j++)
		{
			OGRGeometry* pbuffer = pBufferVec->at(j);

			OGRLayer* ogrlayer = shapeLayer->getOGRLayer();

			//得到的缓冲区与每个geometry求交
			for (int i=0; i<ogrlayer->GetFeatureCount(); i++)
			{
				vgGIS3D::GisManager::getSingleton().setProcessingProgress(
					(int)((float)i/ogrlayer->GetFeatureCount()*(j+1)/pBufferVec->size()*100));

				OGRFeature* ogrfeature = ogrlayer->GetFeature(i);
				OGRGeometry* geometry = ogrfeature->GetGeometryRef();

				if (pbuffer->Intersect(geometry))
				{
					resultGeom.push_back(geometry);
				}
			}
			
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

		return resultGeom;
	}
	//--------------------------------------------------------------
	GeometryPointerVec Buffer::bufferShapeAnalysis2( Layer* shapeLayer )
	{
		GeometryPointerVec resultGeom;

		//buffer队列
		OGRGeoPtrVec* pBufferVec = getBufferVec();
		//geometry队列
		GeometryPointerVec* geoPtrVec =  shapeLayer->getGeometries();

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
		vgGIS3D::GisManager::getSingleton().setProcessingInfo("正在进行矢量分析...");

		for (int j=0; j<pBufferVec->size(); j++)
		{
			OGRGeometry* pbuffer = pBufferVec->at(j);

			for (int i=0; i<geoPtrVec->size(); i++)
			{
				vgGIS3D::GisManager::getSingleton().setProcessingProgress(
					(int)((float)i/geoPtrVec->size()*(j+1)/pBufferVec->size()*100));

				Geometry* pGeo = geoPtrVec->at(i);
				OGRFeature* ogrPtr = pGeo->getOGRFeature();
				OGRGeometry *pOgrGeo = ogrPtr->GetGeometryRef();

				if (pbuffer->Intersect(pOgrGeo))
				{
					resultGeom.push_back(pGeo);
				}
			}

		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

		return resultGeom;
	}
	//--------------------------------------------------------------
	void Buffer::renderModelAnalysisResult( vgKernel::RendererQueue& renderResult )
	{
		vgKernel::RendererQueue::iterator iter = renderResult.begin();
		vgKernel::RendererQueue::iterator iter_end = renderResult.end();
		for (; iter != iter_end; ++iter)
		{
			if ((*iter)->getType()==5000||(*iter)->getType()==5010)
			{
				vgKernel::ColorableObject* colorobj 
					= dynamic_cast<vgKernel::ColorableObject*>(*iter);

				RendererColor rendererColor;
				rendererColor.pRenderer = *iter;
				rendererColor.color = colorobj->getRgbaQuad();
				rendererColor.colorState = colorobj->isColorable();
				rendererColors.push_back(rendererColor);//备份原始颜色，以便恢复

				vgKernel::RgbaQuad color(0,255,255,255);
				colorobj->setColorableValue(color);
				colorobj->setColorable(true);
			}
		}
	}
	//--------------------------------------------------------------
	void Buffer::unrenderModelAnalysisResult()
	{
		RenderColorVec::iterator iter = rendererColors.begin();
		RenderColorVec::iterator iter_end = rendererColors.end();
		for (; iter != iter_end; ++iter)
		{
			Renderer* pRender = (*iter).pRenderer;
			RgbaQuad oldColor = (*iter).color;
			bool     oldState = (*iter).colorState;

			vgKernel::ColorableObject* colorobj 
				= dynamic_cast<vgKernel::ColorableObject*>(pRender);

			colorobj->setColorableValue(oldColor);
			colorobj->setColorable(oldState);
		}
	}
	//--------------------------------------------------------------
	void Buffer::renderShapeAnalysisResult(GeometryPointerVec& geoVec)
	{
		GeometryPointerVec::iterator iter = geoVec.begin();
		GeometryPointerVec::iterator iter_end = geoVec.end();
		for (; iter!=iter_end; ++iter)
		{
			Geometry* pGeo = *iter;
			
			GeometryColor geocolor;
			geocolor.pGeometry = pGeo;
			geocolor.fillColor = pGeo->getDrawingDescriptor()->getFillColorRef();
			geocolor.penColor  = pGeo->getDrawingDescriptor()->getPenColorRef();
			geoColors.push_back(geocolor);//备份原始颜色，以便恢复

			pGeo->getDrawingDescriptor()->setFillColor(RGB(0,255,255));
			pGeo->getDrawingDescriptor()->setPenColor(RGB(0,255,255));

			if (pGeo->getType()==GEOMTRY_BUILDING_SOLID)
			{
				BuildingSolid *pB
					= dynamic_cast<BuildingSolid*>(pGeo);

				pB->setSolidColor(vgKernel::ColorVal(1.0f,1.0f,0.0f,1.0f));
			}
		}

		// 参与分析的图层重新生成显示列表
		/*if ( m_pAnalsisLayer != NULL )
		{
			m_pAnalsisLayer->invalidateRendering();
		}*/

	}
	//--------------------------------------------------------------
	void Buffer::unrenderShapeAnalysisResult()
	{
		GeomColorVec::iterator iter = geoColors.begin();
		GeomColorVec::iterator iter_end = geoColors.end();
		for (; iter!=iter_end; ++iter)
		{
			Geometry* pGeo = (*iter).pGeometry;

			pGeo->getDrawingDescriptor()->setFillColor((*iter).fillColor);
			pGeo->getDrawingDescriptor()->setPenColor((*iter).penColor);

			if (pGeo->getType() == GEOMTRY_BUILDING_SOLID)
			{
				BuildingSolid *pB
					= dynamic_cast<BuildingSolid*>(pGeo);

				pB->revertSolidColor();
			}
		}

		// 参与分析的图层重新生成显示列表
		/*if ( m_pAnalsisLayer != NULL )
		{
			m_pAnalsisLayer->invalidateRendering();
		}*/
	}
	//--------------------------------------------------------------
	Vec3 Buffer::getTranslateModeltoShapeOffset()
	{
		Vec3 coord = vgKernel::CoordSystem::getSingleton().getProjectionCoord();
		Vec3 transOffset(-coord.x, -coord.y, coord.z);
		return transOffset;
	}
	//--------------------------------------------------------------

}// end of namespace vgGIS3D
