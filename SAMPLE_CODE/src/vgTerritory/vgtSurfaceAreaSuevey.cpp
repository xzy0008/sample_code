



#include <vgStableHeaders.h>
#include <vgTerritory/vgtSurfaceAreaSurvey.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtElevationFilter.h>
#include <vgKernel/vgkRendererManager.h>
//#include "vgDlgPlaneLevel.h"

#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkWarning.h>
#include <vgKernel/vgkCoordSystem.h>

#include <gdal/ogr_geometry.h>
#include <vgKernel/vgkSystemUtility.h>

namespace vgTerritory {



	//----------------------------------------------------------------
	SurfaceAreaSurvey::SurfaceAreaSurvey()
	{
		//_heightRender = NULL;

		SetHandleStatus( VG_INPUT_VGT_CUTLEVELLING );//直接用的土方测量的
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		//_terrainMgr = TerrainManager::getSingletonPtr();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();


		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGT_CUTLEVELLING  );	//直接用的土方测量的

		btm=false;	//默认鼠标没有按下
		totalArea = 0.0f;
		_displayListID = 0;

		//_polyPoint = NULL;
		_polyPoint = new Vec3Vector;
		_heightRender = new Vec3Vector;

		m_dlgSetCellSize = NULL;

	}
	//----------------------------------------------------------------
	SurfaceAreaSurvey::~SurfaceAreaSurvey()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		if ( _heightRender != NULL )
		{
			delete _heightRender;
			_heightRender = NULL;
		}

		if ( _polyPoint != NULL)
		{
			delete _polyPoint;
			_polyPoint = NULL;
		}

		if ( m_dlgSetCellSize != NULL)
		{
			delete m_dlgSetCellSize;
			m_dlgSetCellSize = NULL;
		}
		_pointsInSelectArea.clear();
		 _pointsInSelectArea1.clear();
		 _pointsInSelectArea2.clear();
		 _pointsInSelectArea3.clear();

// 		 if (_terrainMgr != NULL)
// 		 {
// 			 delete _terrainMgr;
// 			 _terrainMgr = NULL;
// 		 }

	}
	//----------------------------------------------------------------
	void SurfaceAreaSurvey::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

	}
	//----------------------------------------------------------------
	vgKernel::Vec3 SurfaceAreaSurvey::get3dVecFrom2d( const CPoint& point_2d )
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
	void SurfaceAreaSurvey::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		//下面开始计算，首先需要确定的是积分的单元格cellsize
 		OGRPolygon surf_polygon;
 		OGRLinearRing poly_ring;
 		surf_polygon.setCoordinateDimension(3);
 		poly_ring.setCoordinateDimension(3);

		float m_cellsize = 0.0;
		bool flagDlgCellShow = TerrainManager::getSingleton().flagDlgCellSize;
		if ( flagDlgCellShow)		//设置差值间隔
		{

			m_dlgSetCellSize = new CdlgSetCellSize;
			CWnd* pwnd = vgKernel::SystemUtility::getCurrentViewWnd();

			pwnd->SetTimer( 1, 150, NULL );
			int status = m_dlgSetCellSize->DoModal();
			pwnd->SetTimer( 1, 15, NULL );

			//m_dlgSetCellSize->DoModal();

			if (m_dlgSetCellSize != NULL)
			{
				m_cellsize = m_dlgSetCellSize->cellSize;
			}

			TerrainManager::getSingleton().flagDlgCellSize = false;
					
		}

		if (m_cellsize == 0.0)	//如果设置为0的话，则更改为默认的10
		{
			m_cellsize = 10.0;
		}

		//float cellsize = 
		//	ElevationManager::getSingleton().getMainFileHandleVtr()->getHeader()->cellsize;

		//long curlayernum = 
		//	TerrainCenterManager::getSingleton().getCurrentHeightLayerNumber();
		////在这里获取最精细的cellsize
		//cellsize = cellsize * pow( 2.0f, curlayernum );

		float cellsize = m_cellsize;

		if ( _clickPoints.size() < 3 )
		{
			_clickPoints.clear();
			_pointsInSelectArea.clear();		// FengYK 
			_pointsInSelectArea1.clear();
			_pointsInSelectArea2.clear();
			surf_polygon.empty();
			poly_ring.empty();

			return;
		}
			
		vgTerritory::TerrainManager::getSingleton().showProcessingDlg(true);

		////////////////////////////////////////////////////////////////////////////
		////计算沿着地形表面的曲线
		int size = _clickPoints.size();

		if ( _heightRender == NULL )
		{
			_heightRender = new Vec3Vector;
		}

		_heightRender->clear();
		surf_polygon.empty();
		poly_ring.empty();

		for ( int i = 0 ; i < size - 1; ++ i )
		{
			Vec3 p1 = _clickPoints[ i ];
			Vec3 p2 = _clickPoints[ i + 1 ];

			int num = (p1 - p2).length() / cellsize;

			float dxa = ( p2.x - p1.x ) / num;
			float dza = ( p2.z - p1.z ) / num;

			for ( int k = 0 ; k < num ; ++ k )
			{
				Vec3 t;
				t.x = p1.x + dxa * k;
				t.z = p1.z + dza * k;

				float elev = 0.0f;
				bool getok = TerrainManager::getSingleton().getElevationByPosition( t , elev , true );
				
				if ( getok )
				{
					t.y = elev;
				}

				_heightRender->push_back( t );

				poly_ring.addPoint(t.x, -t.z, t.y);
			}
			//-------------------------------------
			if ( i == (size - 2) )
			{
				Vec3 m_point3 = _clickPoints[ size - 1 ];
				Vec3 m_point4 = _clickPoints[ 0 ];
				int m_num = (m_point3 - m_point4).length() / cellsize;

				float m_dx1 = ( m_point4.x - m_point3.x ) / m_num;
				float m_dz1 = ( m_point4.z - m_point3.z ) / m_num;

				for ( int k = 0 ; k < m_num ; ++ k )
				{
					Vec3 m_t1;
					m_t1.x = m_point3.x + m_dx1 * k;
					m_t1.z = m_point3.z + m_dz1 * k;

					float elev = 0.0f;
					bool getok = TerrainManager::getSingleton().getElevationByPosition( m_t1 , elev , true );

					m_t1.y = elev;

					_heightRender->push_back( m_t1 );

					poly_ring.addPoint(m_t1.x, -m_t1.z, m_t1.y);
				}
			}
		}
		poly_ring.closeRings();
		surf_polygon.addRing(&poly_ring);

		if ( _polyPoint == NULL )
		{
			_polyPoint = new Vec3Vector;
		}

		_polyPoint->clear();
		////////////////////////////////////////////////////////////////////////////
		
		_pointsInSelectArea.clear();		//FengYK
		_pointsInSelectArea1.clear();
		_pointsInSelectArea2.clear();
		_pointsInSelectArea3.clear();

		Vec3 t;
		float elev;
		
		//------------------------------------------
		OGREnvelope envolp;

		surf_polygon.flattenTo2D();

		surf_polygon.getEnvelope(&envolp);

		OGRGeometry* geo = 
			OGRGeometryFactory::createGeometry( wkbPoint );

		assert( geo != NULL );
		assert( wkbFlatten( geo->getGeometryType() )== wkbPoint );

		geo->setCoordinateDimension(2);

		OGRPoint* pt = ( OGRPoint * )geo;

		int rowNum = (envolp.MaxX - envolp.MinX) / cellsize;
		int seriesNum = (envolp.MaxY - envolp.MinY) / cellsize;

		for ( int k = 0 ; k < rowNum ; ++ k )
		{
			vgTerritory::TerrainManager::getSingleton().setProcessingProgress((int)(((float)k/rowNum) * 100));
			vgTerritory::TerrainManager::getSingleton().setProcessingInfo("正在进行地形表面面积计算，请等待...");

			for ( int l = 0 ; l < seriesNum ; ++ l )
			{
				
				pt->setX( envolp.MinX + k*cellsize );
				pt->setY( envolp.MinY + l*cellsize );

				OGRBoolean bo = surf_polygon.Contains( pt );

				if (bo)
				{
					t.x = pt->getX();
					t.z = -(pt->getY());
					bool getok = TerrainManager::getSingleton().getElevationByPosition( t , elev , true );
					
					if ( getok )
					{
						t.y = elev;

						_polyPoint->push_back(t);
						//TRACE("_polyPoint = %f, %f, %f \n", t.x, t.y, t.z );

						if ( (k % 2) == 0)
						{
							_pointsInSelectArea1.push_back(t);
							//TRACE("Point1 = %f, %f, %f \n", t.x, t.y, t.z );
						}
						else
						{
							_pointsInSelectArea2.push_back(t);
							//TRACE("Point2 = %f, %f, %f \n", t.x, t.y, t.z );
						}	

					}

				}
				
			}//for

			if ((k % 2) != 0)
			{
				int size1 = _pointsInSelectArea1.size();
				int size2 = _pointsInSelectArea2.size();

				if (size1 < size2)
				{
					for (int i = 0; i < size1; i++)
					{
						_pointsInSelectArea.push_back(_pointsInSelectArea1[i]);
						_pointsInSelectArea.push_back(_pointsInSelectArea2[i]);
						_pointsInSelectArea3.push_back(_pointsInSelectArea2[i]);
					}
					for (; size1 < size2; size1++)
					{
						_pointsInSelectArea3.push_back(_pointsInSelectArea2[size1]);
					}
				}
				else
				{
					for (int i = 0; i < size2; i++)
					{
						_pointsInSelectArea.push_back(_pointsInSelectArea1[i]);
						_pointsInSelectArea.push_back(_pointsInSelectArea2[i]);
						_pointsInSelectArea3.push_back(_pointsInSelectArea2[i]);
					}
				}
				_pointsInSelectArea1.clear();
				_pointsInSelectArea2.clear();
			}
			else if ((k % 2) == 0 && k > 2)
			{
				int size3 = _pointsInSelectArea3.size();
				int size1 = _pointsInSelectArea1.size();
				if (size3 < size1)
				{
					for (int i = 0; i < size3; i++)
					{
						_pointsInSelectArea.push_back(_pointsInSelectArea3[i]);
						_pointsInSelectArea.push_back(_pointsInSelectArea1[i]);
					}
				}
				else
				{
					for (int i = 0; i < size1; i++)
					{
						_pointsInSelectArea.push_back(_pointsInSelectArea3[i]);
						_pointsInSelectArea.push_back(_pointsInSelectArea1[i]);
					}
				}

				_pointsInSelectArea3.clear();
			}
		}//for

		OGRGeometryFactory::destroyGeometry( geo );

		if ( _pointsInSelectArea.size() > 3)	//用海伦公式计算三角形面积，然后加和
		{
			for (int i = 0; i < _pointsInSelectArea.size()-2; i++)
			{
				totalArea += hailun(_pointsInSelectArea[i], _pointsInSelectArea[i+1], _pointsInSelectArea[i+2]);
			}
		}

		CString strResult;
		double polyArea = 0.0;
		int numRing = 0;
		numRing = poly_ring.getNumPoints();

		if ( numRing != 0 )		//判断边界的差值点数是否为0
		{
			polyArea = surf_polygon.get_Area();		//获得平面面积
		}
		if ( totalArea < polyArea)
		{
			totalArea = polyArea;
		}

		if (totalArea == 0)
		{
			strResult.Format("选择区域太小，无法准确计算，请重新选择或者取消测量状态后重新设置差值点间隔！");
		}
		else
		{
			strResult.Format("地形表面面积是:%.5f平方米,投影到平面面积是%.5f平方米", totalArea, polyArea);
		}

		vgTerritory::TerrainManager::getSingleton().showProcessingDlg(false);

		AfxMessageBox(strResult);
		totalArea = 0.0f;
		_clickPoints.clear();
		surf_polygon.empty();
		poly_ring.empty();
		return;

	}
	//----------------------------------------------------------------
	void SurfaceAreaSurvey::drawPoint( const Vec3& point )
	{
		glDisable( GL_TEXTURE_2D );

		glColor3f( 1, 0.1f ,  0 );
		glPointSize( 3.0f );

		glPushMatrix();

		glBegin( GL_POINTS );
		glVertex3fv( point.v );
		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void SurfaceAreaSurvey::OnLButtonDown( UINT nFlags, CPoint position )
	{

		if (btm==false)
		{
			if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
			{
				_clickPoints.push_back( _mouseVec );
			}
		}

	}
	void SurfaceAreaSurvey::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{

	}
	//----------------------------------------------------------------
	void SurfaceAreaSurvey::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		glDisable( GL_DEPTH_TEST );

		drawPoint( _mouseVec );					
		drawLines( _clickPoints , _mouseVec,btm);		//绘制跟踪鼠标的线

 		if ( _heightRender != NULL )				//绘制沿地形起伏的线
 		{
 			drawHeight( _heightRender );
 		}
		//renderSelectedArea();							//绘制选择的地形区域
		if ( _polyPoint != NULL)
		{
			drawPolygon( _polyPoint);
		}

		glEnable( GL_DEPTH_TEST );

	}
	void SurfaceAreaSurvey::OnRBottonDown(UINT nFlags, CPoint position) 
	{

	}

	//----------------------------------------------------------------
	void SurfaceAreaSurvey::drawHeight( Vec3Vector* points )
	{
		assert( points != NULL );

		Vec3Vector::iterator iter = points->begin();
		Vec3Vector::iterator iter_end = points->end();

		glDisable( GL_TEXTURE_2D );
		glLineWidth( 2.0f );
		glColor3f( 1.0f , 0 , 0 );

		glPushMatrix();
		glBegin( GL_LINE_LOOP );

		for ( ; iter != iter_end ; ++ iter )
		{
			glVertex3fv( iter->v );
		}

		glEnd();
		glPopMatrix();		

		return;
	}
	//----------------------------------------------------------------
	void SurfaceAreaSurvey::drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm)
	{
		if ( points.size() < 1 )
		{
			return;
		}

		Vec3Vector::const_iterator iter = points.begin();
		Vec3Vector::const_iterator iter_end = points.end();

		glPushMatrix();
		glDisable( GL_DEPTH_TEST ) ;
		glDisable( GL_TEXTURE_2D );
		glLineWidth(2.0f);

		glBegin( GL_LINE_LOOP );
		for ( ; iter != iter_end ; ++ iter )
		{	
			glVertex3fv( iter->v );
		}
		if (btm==false)
			glVertex3fv( mousevec.v );

		glEnd();

		glEnable( GL_DEPTH_TEST );
		glPopMatrix();
	}
	//----------------------------------------------------------------
	void SurfaceAreaSurvey::OnKeyDown( int keyCode )
	{

	}
	//----------------------------------------------------------------
	bool SurfaceAreaSurvey::getFlagButtonDown()
	{
		return btm;
	}
	//----------------------------------------------------------------
	void SurfaceAreaSurvey::renderSelectedArea()
	{

		glEnable( GL_BLEND );

		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();				
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);		
		glShadeModel(GL_FLAT);

		glBegin(GL_TRIANGLE_STRIP);
		int pointSize = _pointsInSelectArea.size();
		
		for (int i= 0; i < pointSize; i++)
		{
			glVertex3f(_pointsInSelectArea[i].x, _pointsInSelectArea[i].y + 8, _pointsInSelectArea[i].z);
		}
		glEnd();

		glDisable( GL_DEPTH_TEST );				
		glPopMatrix();
		glPopAttrib();
		glDisable( GL_BLEND );
	}
	//----------------------------------------------------------------------------------
	float SurfaceAreaSurvey::hailun(vgKernel::Vec3 a,vgKernel::Vec3 b,vgKernel::Vec3 c)
	{	
		float la,lb,lc;
		la = a.distance(b);
		lb = b.distance(c);
		lc = c.distance(a);
		float p=(la+lb+lc)/2;
		float s=sqrt(p*(p-la)*(p-lb)*(p-lc));
		return  s;

	}
	//----------------------------------------------------------------------------------
	void SurfaceAreaSurvey::drawPolygon( Vec3Vector* points )
	{
		assert( points != NULL );

		Vec3Vector::iterator iter = points->begin();
		Vec3Vector::iterator iter_end = points->end();
		glDisable( GL_TEXTURE_2D );

		glColor3f( 1, 0.1f ,  0 );
		glPointSize( 5.0f );

		glPushMatrix();
		glDisable( GL_DEPTH_TEST );
		glBegin( GL_POINTS );

		for ( ; iter != iter_end ; ++ iter )
		{
			glVertex3fv( iter->v );
		}

		glEnd();

		glEnable( GL_DEPTH_TEST );
		glPopMatrix();
	}
}// end of namespace vgTerritory
