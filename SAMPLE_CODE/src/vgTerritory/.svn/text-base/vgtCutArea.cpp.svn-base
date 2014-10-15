


#include <vgStableHeaders.h>
#include <vgTerritory/vgtCutArea.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtFileWriterVtr.h>
#include <vgTerritory/vgtDlgCutArea.h>

#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkColorableObject.h>
#include <vgKernel/vgkRgbaQuad.h>

#include <vgKernel/vgkSystemUtility.h>
#include <gdal/ogr_geometry.h>

namespace vgTerritory {
	


	//----------------------------------------------------------------
	CutArea::CutArea()
	{
		_heightRender = NULL;

		_bStopRecord = false;
		_bFillArea = false;
		_callListId = 0;
		_bHasSelectOperate = false;
		_pSegment = NULL;

		SetHandleStatus( VG_INPUT_VGT_CUT_AREA );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		_terrainMgr = TerrainManager::getSingletonPtr();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGT_CUT_AREA |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI  );

	}
	//----------------------------------------------------------------
	CutArea::~CutArea()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		reset();

		if ( _heightRender != NULL )
		{
			delete _heightRender;
			_heightRender = NULL;
		}
	}
	//----------------------------------------------------------------
	void CutArea::OnMouseMove( UINT nFlags, CPoint position )
	{
		if ( !_bStopRecord )
		{
			_mouseVec = get3dVecFrom2d( position );
			vgKernel::SelectManager::getSingleton().setPolygonPt( _mouseVec );
		}
	}
	//----------------------------------------------------------------
	vgKernel::Vec3 CutArea::get3dVecFrom2d( const CPoint& point_2d )
	{
		vgKernel::Vec3 ret;

		glPushMatrix();

		int ViewPort[4],winy;
		GLdouble ModelView[16];
		GLdouble Projection[16];
		GLfloat winx,winz;
		GLdouble vrx,vry, vrz;

		glGetIntegerv(GL_VIEWPORT,ViewPort);

		winx = (float)point_2d.x;
		winy = ViewPort[3] - point_2d.y;

		glGetDoublev(GL_MODELVIEW_MATRIX,ModelView);
		glGetDoublev(GL_PROJECTION_MATRIX,Projection);
		glReadPixels(point_2d.x,winy,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winz);
		gluUnProject((GLdouble)winx,(GLdouble)winy,(GLdouble)winz,ModelView,Projection,ViewPort,&vrx,&vry,&vrz);

		ret.x = (float) vrx;
		ret.y = (float) vry;
		ret.z = (float) vrz;

		glPopMatrix();

		return ret;
	}
	//----------------------------------------------------------------
	void CutArea::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		// 双击时放弃上一次切块结果，并充许重新切块

		reset();

		return;

#if 0
		//------------------------------------------
		// 这个时候,显示结果,并且重置当前状态
		//------------------------------------------

		float cellsize = 
			ElevationManager::getSingleton().getMainFileHandleVtr()->getHeader()->cellsize;

		long curlayernum = 
			TerrainCenterManager::getSingleton().getCurrentHeightLayerNumber();

		cellsize = cellsize * pow( 2.0f, curlayernum );

		//------------------------------------------
		// 精度问题!!!!!!!!!!!!
		//------------------------------------------
		if ( _clickPoints.size() < 2 )
		{
			_clickPoints.clear();
			return;
		}

		if ( _heightRender == NULL )
		{
			_heightRender = new Vec3Vector;
		}

		_heightRender->clear();

		int size = _clickPoints.size();

		for ( int i = 0 ; i < size - 1; ++ i )
		{
			Vec3 p1 = _clickPoints[ i ];
			Vec3 p2 = _clickPoints[ i + 1 ];

			int num = (p1 - p2).length() / cellsize;

			float dx = ( p2.x - p1.x ) / num;
			float dz = ( p2.z - p1.z ) / num;

			for ( int k = 0 ; k < num ; ++ k )
			{
				Vec3 t;
				t.x = p1.x + dx * k;
				t.z = p1.z + dz * k;

				float elev = 0.0f;
				bool getok = _terrainMgr->getElevationByPosition( t , elev , false );

				t.y = elev;

				_heightRender->push_back( t );
			}

			// 加入最后一个
			Vec3 lastone = p2;
			float elev = 0.0f;
			bool getok = _terrainMgr->getElevationByPosition( lastone , elev , false );
			lastone.y = elev;
			_heightRender->push_back( lastone );

		}

		_clickPoints.clear();

#endif
	}
	//----------------------------------------------------------------
	void CutArea::drawPoint( const Vec3& point )
	{
		glDisable( GL_TEXTURE_2D );

		glColor3f( 1, 0.1f ,  0 );
		glPointSize( 5.0f );

		glPushMatrix();

		glBegin( GL_POINTS );
		glVertex3fv( point.v );
		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void CutArea::OnLButtonDown( UINT nFlags, CPoint position )
	{
		using namespace vgKernel;

		_bHasSelectOperate = true;

		addClickPoint();	

#if 0

		if ( _clickPoints.size() == 2 )
		{

			//------------------------------------------
			// 在这里开始切块处理
			//------------------------------------------
			
			_bStopRecord = true;

			
			ElevationBound bound;

			bound.minPos.x = _clickPoints[0].x;
			bound.minPos.y = _clickPoints[0].z;

			bound.maxPos.x = _clickPoints[1].x;
			bound.maxPos.y = _clickPoints[1].z;

			bound.makeSafe();

			FileWriterVtr writer;

			//assert(0);

			vgtDlgCutArea dlg;
			int ret = dlg.DoModal();

			if ( ret == IDOK )
			{
				String terrainname = dlg.getMetaName();
				String path = dlg.getPath();

				bool writeok = writer.writeToVtrFromItems( 
					ElevationManager::getSingleton().getMainFileHandleVtr(),
					terrainname ,  
					ElevationManager::getSingleton().getIntersectedItemsByBound( bound ) ,
					path ); 

				assert( writeok == true );

				if ( writeok == true )
				{
					std::ostringstream o;
					o << "地形切块保存成功,文件保存在:" << dlg.getAbsName();
					MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
						o.str().c_str() , "提示", MB_OK );
				}
				else
				{
					std::ostringstream o;
					o << "地形切块保存到" <<dlg.getAbsName() <<"时失败, 请重新保存,确认输入数据正确.";
					MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
						o.str().c_str() , "提示", MB_OK );
				}
			}


			vgKernel::InputSystem::getSingleton().setDefaultStatus();

			_clickPoints.clear();

			TerrainManager::getSingleton().setCutAreaFlag( false );

		}
#endif

		return;
	}

	//----------------------------------------------------------------
	void CutArea::OnRBottonDown(UINT nFlags, CPoint position)
	{
		if ( _bHasSelectOperate && _clickPoints.size() >= 2 )
		{
			addClickPoint();

			_bStopRecord = true;
			_bFillArea = true;

			_bHasSelectOperate = false;

			// 检测多边形选区是否合法
			if ( _clickPoints.size() > 3 )
			{
				bool bSimple = isSimplePolygon( _clickPoints );
				if ( !bSimple )
				{
					String msg = "切块失败！多边形选区不能自相交！";
					vgKernel::SystemUtility::showModelDialog( msg );
					
					reset();

					return;
				}
			}

			bool bOriginState;
			SelectMode* pMode = SelectManager::getSingleton().getSelectMode();
			bOriginState = pMode->isInclude;
			pMode->isInclude = true;
			SelectManager::getSingleton().setSelectMode( pMode );

			SelectManager::getSingleton().clearSelection();
			SelectManager::getSingleton().SelectPolygonObject( &_clickPoints );


			SelectManager::getSingleton().colorbleSelectedRender( 
				SelectManager::getSingleton().getCurrentSelectedItems() );

			pMode->isInclude = bOriginState;
			SelectManager::getSingleton().setSelectMode( pMode );
		}
	}

	//----------------------------------------------------------------
	void CutArea::render()
	{
#if 0
		// 画线
		drawLines( _clickPoints , _mouseVec );

		// 填充区域
		if ( _bFillArea )
		{
			if ( _callListId == 0 )
			{
				_callListId = glGenLists( 1 );
				assert( _callListId != 0 );

				glNewList( _callListId, GL_COMPILE );
					fillArea( _clickPoints );
				glEndList();
			}
			else
			{
				glCallList( _callListId );
			}
		}

		if ( _heightRender != NULL )
		{
			drawHeight( _heightRender );
		}
#endif
	}

	//----------------------------------------------------------------
	void CutArea::drawHeight( Vec3Vector* points )
	{
		assert( points != NULL );

		Vec3Vector::iterator iter = points->begin();
		Vec3Vector::iterator iter_end = points->end();

		glDisable( GL_TEXTURE_2D );
		glLineWidth( 3.0f );
		glColor3f( 1.0f , 0 , 0 );

		glPushMatrix();
		glBegin( GL_LINE_STRIP );

		for ( ; iter != iter_end ; ++ iter )
		{
			glVertex3fv( iter->v );
		}

		glEnd();
		glPopMatrix();

		return;
	}
	//----------------------------------------------------------------
	void CutArea::drawLines( const Vec3Vector& points , const Vec3& mousevec )
	{
		if ( points.size() < 1 )
		{
			return;
		}
#if 0
		const Vec3& p1 = points[0];

		glPushMatrix();

			glDisable( GL_TEXTURE_2D );

			// 画线框
			glDisable( GL_BLEND );
			glLineWidth(2.0f);

			glBegin( GL_LINE_LOOP );
				glVertex3f( p1.x , p1.y , p1.z );
				glVertex3f( mousevec.x , p1.y , p1.z );
				glVertex3f( mousevec.x , p1.y , mousevec.z );
				glVertex3f( p1.x , p1.y , mousevec.z );
			glEnd();
			
			glEnable( GL_BLEND );

			// 填充线框内的区域
			glEnable( GL_BLEND );
			glColor4f( 1.0f, 0.5f, 0.3f, 0.3f );

			glBegin( GL_QUADS );
				glVertex3f( p1.x , p1.y , p1.z );
				glVertex3f( mousevec.x , p1.y , p1.z );
				glVertex3f( mousevec.x , p1.y , mousevec.z );
				glVertex3f( p1.x , p1.y , mousevec.z );
			glEnd();
			
			glDisable( GL_BLEND );
			glEnable( GL_TEXTURE_2D );

		glPopMatrix();
#endif
		glPushMatrix();

			glDisable( GL_TEXTURE_2D );
			glDisable( GL_DEPTH_TEST );
			glDisable( GL_BLEND );
			
			// 指定线属性
			glLineWidth( 2.0f );
			glColor3f( 1.0f, 0.0f, 0.0f );

			glBegin( GL_LINE_LOOP );
				for ( int i = 0; i < points.size(); i++ )
				{
					glVertex3fv( points[i].v );
				}
				glVertex3fv( mousevec.v );
			glEnd();

			glEnable( GL_DEPTH_TEST );
			glEnable( GL_TEXTURE_2D );

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void CutArea::fillArea( const Vec3Vector& points )
	{
		if ( points.size() < 1 )
		{
			return;
		}

		glPushMatrix();

			glDisable( GL_TEXTURE_2D );
			glDisable( GL_DEPTH_TEST );
			glEnable( GL_BLEND );

			glColor4f( 1.0f, 0.5f, 0.3f, 0.3f );

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
				gluTessBeginContour( pTess );
				for ( int i = 0; i < points.size(); i++ )
				{
					double* addr = new double[3];
					addr[0] = points[i].x;
					addr[1] = points[i].y;
					addr[2] = points[i].z;

					// 这里要求第二个参数为double类型数组
					gluTessVertex( pTess, addr, addr );
					_vecForTess.push_back( addr );

				} // end for i
				gluTessEndContour( pTess );
			gluTessEndPolygon( pTess );  // 多边形分格完成

			// 删除分格对象
			gluDeleteTess( pTess );
			pTess = NULL;

			glDisable( GL_BLEND );
			glEnable( GL_DEPTH_TEST );
			glEnable( GL_TEXTURE_2D );

		glPopMatrix();
	}

	//----------------------------------------------------------------
	void CutArea::OnKeyDown( int keyCode )
	{
		if(keyCode == vgKernel::InputCode::ESCAPE)
		{
			reset();
		}
	}
	//----------------------------------------------------------------
	void CutArea::reset()
	{
		if ( _heightRender != NULL )
		{
			_heightRender->clear();
		}

		vgKernel::SelectManager::getSingleton().uncolorbleSelectedRender( 
			vgKernel::SelectManager::getSingleton().getCurrentSelectedItems() );

		vgKernel::SelectManager::getSingleton().getCurrentSelectedItems().clear();

		_clickPoints.clear();

		_bStopRecord = false;
		_bFillArea = false;

		clearDisplayList();
		clearVecForTess();
		destroySegment();

		vgKernel::SelectManager::getSingleton().clearPolygonVec();
	}

	//----------------------------------------------------------------
	void CutArea::clearVecForTess()
	{
		doublePtrVec::iterator itr = _vecForTess.begin();
		doublePtrVec::iterator itr_end = _vecForTess.end();

		for ( ; itr != itr_end; itr++ )
		{
			if ( *itr != NULL )
			{
				delete *itr;
				*itr = NULL;
			}
		}

		_vecForTess.clear();
	}

	//----------------------------------------------------------------
	void CutArea::clearDisplayList()
	{
		if ( _callListId != 0 )
		{
			glDeleteLists( _callListId, 1 );
			_callListId = 0;
		}
	}

	//----------------------------------------------------------------
	void CutArea::destroySegment()
	{
		if ( _pSegment != NULL )
		{
			delete[] _pSegment;
			_pSegment = NULL;
		}
	}

	//----------------------------------------------------------------
	bool CutArea::isSimplePolygon( const Vec3Vector& pointsVec )
	{
		// 1. 建立线段索引信息
		createSegment( pointsVec );
		assert( _pSegment != NULL );

		// 2.线段相交测试
		for ( int i = 0; i < pointsVec.size(); i++ )
		{
			// 构造用于相交测试的第一条OGR线段
			OGRGeometry* pGeoLine1 = OGRGeometryFactory::createGeometry( wkbLineString );
			OGRLineString* pLineString1 = dynamic_cast<OGRLineString*>( pGeoLine1 );
			
			pLineString1->addPoint( _pSegment[i].start.x, _pSegment[i].start.y );
			pLineString1->addPoint( _pSegment[i].end.x, _pSegment[i].end.y );

			for ( int j = 0; j < pointsVec.size(); j++ )
			{
				if ( i == j ) // 自身不做判断
				{
					continue;
				}

				// 构造用于相交测试的第二条OGR线段
				OGRGeometry* pGeoLine2 = OGRGeometryFactory::createGeometry( wkbLineString );
				OGRLineString* pLineString2 = dynamic_cast<OGRLineString*>( pGeoLine2 );

				pLineString2->addPoint( _pSegment[j].start.x, _pSegment[j].start.y );
				pLineString2->addPoint( _pSegment[j].end.x, _pSegment[j].end.y );

				// 判断两线段是否相交
				if ( pLineString1->Intersect( pLineString2 ) )
				{
					// 求交点
					OGRGeometry* pGeoPoint = pLineString1->Intersection( pLineString2 );

					// 判断交点是否为线段端点(非端点则两线段交叉)
					OGRPoint* pPoint = dynamic_cast<OGRPoint*>( pGeoPoint );
					
					OGRGeometry* pGeoPtStart = OGRGeometryFactory::createGeometry( wkbPoint );
					OGRGeometry* pGeoPtEnd = OGRGeometryFactory::createGeometry( wkbPoint );

					OGRPoint* pStartPoint = dynamic_cast<OGRPoint*>( pGeoPtStart );
					OGRPoint* pEndPoint = dynamic_cast<OGRPoint*>( pGeoPtEnd );

					pLineString2->StartPoint( pStartPoint );
					pLineString2->EndPoint( pEndPoint );

					if ( !(pPoint->Equal(pStartPoint)) && !(pPoint->Equal(pEndPoint)) )
					{
						OGRGeometryFactory::destroyGeometry( pGeoPtStart );
						OGRGeometryFactory::destroyGeometry( pGeoPtEnd );
						pGeoPtStart = NULL;
						pGeoPtEnd = NULL;

						return false;
					}

					OGRGeometryFactory::destroyGeometry( pGeoPtStart );
					OGRGeometryFactory::destroyGeometry( pGeoPtEnd );
					pGeoPtStart = NULL;
					pGeoPtEnd = NULL;
				}

				// 销毁第二条OGR线段
				OGRGeometryFactory::destroyGeometry( pLineString2 );
				pGeoLine2 = NULL;
			}
			
			// 销毁第一条OGR线段
			OGRGeometryFactory::destroyGeometry( pLineString1 );
			pGeoLine1 = NULL;
		}

		return true;
	}

	//----------------------------------------------------------------
	void CutArea::createSegment( const Vec3Vector& pointsVec )
	{
		assert( _pSegment == NULL );

		int numSegs = pointsVec.size();
		_pSegment = new Segment[numSegs];

		for ( int i = 0; i < numSegs; i++ )
		{
			_pSegment[i].start = Vec2( pointsVec[i].x, pointsVec[i].z );  // 线段起点

			int nextIndex = ( i + 2 > numSegs ) ? 0 : i + 1;

			_pSegment[i].end = Vec2( pointsVec[nextIndex].x, pointsVec[nextIndex].z ); // 线段终点
		}
	}

	//----------------------------------------------------------------
	void CutArea::addClickPoint()
	{
		if ( TerrainManager::getSingleton().hasTerrainData() )
		{
			if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
			{
				_clickPoints.push_back( _mouseVec );
				vgKernel::SelectManager::getSingleton().addPolygonPt( _mouseVec );
			}
		}
		else
		{
			_clickPoints.push_back( _mouseVec );
			vgKernel::SelectManager::getSingleton().addPolygonPt( _mouseVec );
		}
	}

	//----------------------------------------------------------------

}// end of namespace vgTerritory
