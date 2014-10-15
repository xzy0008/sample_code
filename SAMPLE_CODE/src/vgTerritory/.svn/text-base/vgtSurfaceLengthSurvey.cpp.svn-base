



#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtSurfaceLengthSurvey.h>
#include <stack>


namespace vgTerritory {
	
	
	
	//----------------------------------------------------------------
	SurfaceLengthSurvey::SurfaceLengthSurvey()
	{
		_heightRender = NULL;

		SetHandleStatus( VG_INPUT_VGT_CUTANALYSIS );//直接用的剖面分析的
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		_terrainMgr = TerrainManager::getSingletonPtr();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGT_CUTANALYSIS |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI  );//直接用的剖面分析的
		
		_heightRender = new Vec3Vector;

	}
	//----------------------------------------------------------------
	SurfaceLengthSurvey::~SurfaceLengthSurvey()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		if ( _heightRender != NULL )
		{
			delete _heightRender;
			_heightRender = NULL;
		}

	}
	//----------------------------------------------------------------
	void SurfaceLengthSurvey::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

	}
	//----------------------------------------------------------------
	vgKernel::Vec3 SurfaceLengthSurvey::get3dVecFrom2d( const CPoint& point_2d )
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
	void SurfaceLengthSurvey::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
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

// 		if ( _heightRender == NULL )
// 		{
// 			_heightRender = new Vec3Vector;
// 		}

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
				bool getok = _terrainMgr->getElevationByPosition( t , elev , true );
				
				t.y = elev;

				_heightRender->push_back( t );
			}

			// 加入最后一个
			Vec3 lastone = p2;
			float elev = 0.0f;
			bool getok = _terrainMgr->getElevationByPosition( lastone , elev , true );
			lastone.y = elev;
			_heightRender->push_back( lastone );

		}
		//计算地形表面测量线的长度
		Vec3Vector::iterator iter = _heightRender->begin();
		Vec3Vector::iterator iter_end = _heightRender->end();
 		std::stack <Vec3> m_tempPoint_stck;
 		double surfLineLength = 0.0;
 		CString strSuryResult;

 		for (; iter != iter_end; iter++)
 		{
 			if (m_tempPoint_stck.empty())
 			{
 				m_tempPoint_stck.push((*iter));
 			}
 			else
 			{
 				vgKernel::Vec3 m_pt = m_tempPoint_stck.top();
 				surfLineLength += m_pt.distance((*iter));
 				m_tempPoint_stck.push((*iter));
 			}
 		}
 
 		while (!m_tempPoint_stck.empty())//清空栈
 		{
 			m_tempPoint_stck.pop();
 		}
 		
 		strSuryResult.Format("地形表面长度:%.5f 米!", surfLineLength);
 		
		_clickPoints.clear();

		AfxMessageBox(strSuryResult);
		
	}
	//----------------------------------------------------------------
	void SurfaceLengthSurvey::drawPoint( const Vec3& point )
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
	void SurfaceLengthSurvey::OnLButtonDown( UINT nFlags, CPoint position )
	{

		if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
		{
			_clickPoints.push_back( _mouseVec );
		}
	}
	//----------------------------------------------------------------
	void SurfaceLengthSurvey::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		glDisable( GL_DEPTH_TEST );

		drawPoint( _mouseVec );
		drawLines( _clickPoints , _mouseVec);

		if ( _heightRender != NULL )
		{
			drawHeight( _heightRender );
		}

		glEnable( GL_DEPTH_TEST );
	}

	//----------------------------------------------------------------
	void SurfaceLengthSurvey::drawHeight( Vec3Vector* points )
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
	void SurfaceLengthSurvey::drawLines( const Vec3Vector& points , const Vec3& mousevec )
	{
		if ( points.size() < 1 )
		{
			return;
		}

		Vec3Vector::const_iterator iter = points.begin();
		Vec3Vector::const_iterator iter_end = points.end();

		glPushMatrix();

		glDisable( GL_TEXTURE_2D );
		glLineWidth(5.0f);

		glBegin( GL_LINE_STRIP );
		for ( ; iter != iter_end ; ++ iter )
		{	
			glVertex3fv( iter->v );
		}

		glVertex3fv( mousevec.v );

		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
