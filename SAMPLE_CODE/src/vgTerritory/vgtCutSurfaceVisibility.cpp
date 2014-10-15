


#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtCutSurfaceVisibility.h>


namespace vgTerritory {
	


	//----------------------------------------------------------------
	CutSurfaceVisibility::CutSurfaceVisibility()
	{

		_heightRender = NULL;

		SetHandleStatus( VG_INPUT_VGT_CUTVISIBLITY );

		vgKernel::InputSystem::getSingleton().registerHandle( this );

		_terrainMgr = TerrainManager::getSingletonPtr();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGT_CUTVISIBLITY |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );

	}
	//----------------------------------------------------------------
	CutSurfaceVisibility::~CutSurfaceVisibility()
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
	void CutSurfaceVisibility::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

	}
	//----------------------------------------------------------------
	vgKernel::Vec3 CutSurfaceVisibility::get3dVecFrom2d( const CPoint& point_2d )
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
	void CutSurfaceVisibility::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		return;
	}
	//----------------------------------------------------------------
	void CutSurfaceVisibility::drawPoint( const Vec3& point )
	{
		glDisable( GL_DEPTH_TEST );

		glDisable( GL_TEXTURE_2D );

		glColor3f( 1, 0.1f ,  0 );
		glPointSize( 5.0f );

		glPushMatrix();

		glBegin( GL_POINTS );
		glVertex3fv( point.v );
		glEnd();

		glPopMatrix();

		glEnable( GL_DEPTH_TEST );
	}
	//----------------------------------------------------------------
	void CutSurfaceVisibility::OnLButtonDown( UINT nFlags, CPoint position )
	{
		//MessageBox( NULL , _mouseVec.getDetails().c_str() , "" , MB_OK );


		if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
		{
			_clickPoints.push_back( _mouseVec );
		}

		if ( _clickPoints.size() < 2 )
		{
			return;
		}

		//------------------------------------------
		// 这个时候, 开始判定通透性
		//------------------------------------------
		float cellsize = 
			ElevationManager::getSingleton().getMainFileHandleVtr()->getHeader()->cellsize;

		long curlayernum = 
			TerrainCenterManager::getSingleton().getCurrentHeightLayerNumber();

		cellsize = cellsize * pow( 2.0f, curlayernum );

		//------------------------------------------
		// 精度问题!!!!!!!!!!!!
		//------------------------------------------
		assert( _clickPoints.size() == 2 );

		if ( _heightRender == NULL )
		{
			_heightRender = new Vec3Vector;
		}
		_heightRender->clear();


		Vec3Vector heights;

		int size = _clickPoints.size();
		assert( size == 2 );

		int i = 0;

		Vec3 p1 = _clickPoints[ i ];
		Vec3 p2 = _clickPoints[ i + 1 ];

		int num = (p1 - p2).length() / cellsize;

		float dx = ( p2.x - p1.x ) / num;
		float dz = ( p2.z - p1.z ) / num;

		//------------------------------------------
		// 得到起始和末尾的高程点.
		//------------------------------------------
		float p1y = 0.0f;
		float p2y = 0.0f;
		_terrainMgr->getElevationByPosition( p1 , p1y , true );
		_terrainMgr->getElevationByPosition( p2 , p2y , true );


		float dy = ( p2y - p1y ) / num;
		
 		bool can_not_see_it = false;

		for ( int k = 0 ; k < num ; ++ k )
		{
			Vec3 t;
			t.x = p1.x + dx * k;
			t.z = p1.z + dz * k;

			float datumY = p1y + dy * k;

			float elev = 0.0f;
			bool getok = _terrainMgr->getElevationByPosition( t , elev , true );

			t.y = elev;
			_heightRender->push_back( t );

			if ( datumY < elev )
			{
				can_not_see_it = true;
			}
		}



		_clickPoints.clear();

		std::ostringstream o;

		if ( can_not_see_it )
		{	
			o << "视点不可见.";
		}
		else
		{
			o << "视点可见.";
		}
		
		o << "\n\n点1: " << p1.getDetails() 
			<< "\n点2: " << p2.getDetails();
		
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			o.str().c_str() , "通视分析" , MB_OK | MB_ICONQUESTION );


		return;
	}
	//----------------------------------------------------------------
	void CutSurfaceVisibility::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		

		drawPoint( _mouseVec );
		drawLines( _clickPoints , _mouseVec);

		glDisable( GL_DEPTH_TEST );

		if ( _heightRender != NULL )
		{
			drawHeight( _heightRender );
		}

		glEnable( GL_DEPTH_TEST );

	}

	//----------------------------------------------------------------
	void CutSurfaceVisibility::drawHeight( Vec3Vector* points )
	{
		assert( points != NULL );

		Vec3Vector::iterator iter = points->begin();
		Vec3Vector::iterator iter_end = points->end();

		glDisable( GL_TEXTURE_2D );
		glLineWidth( 3.0f );
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
	void CutSurfaceVisibility::drawLines( const Vec3Vector& points , const Vec3& mousevec )
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
