



#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtCutSurfaceAnalysis2.h>
#include <vgTerritory/vgtTerrainManager.h>


namespace vgTerritory {
	
	
	
	//----------------------------------------------------------------
	CutSurfaceAnalysis2::CutSurfaceAnalysis2()
	{

		SetHandleStatus( VG_INPUT_VGT_CUTANALYSIS2 );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		_terrainMgr = TerrainManager::getSingletonPtr();

		_gpuProgram = _terrainMgr->getGpuProgramPtr();
		assert( _gpuProgram != NULL );

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		_plane = NULL;
 

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGT_CUTANALYSIS2 |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI  );
		
		_cutSufSecType = SECT_NONE;
	}
	//----------------------------------------------------------------
	CutSurfaceAnalysis2::~CutSurfaceAnalysis2()
	{
		glDisable( GL_CLIP_PLANE0 );

		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		if ( _plane != NULL )
		{
			delete _plane;
			_plane  =NULL;
		}
	}
	//----------------------------------------------------------------
	void CutSurfaceAnalysis2::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

	}
	//----------------------------------------------------------------
	vgKernel::Vec3 CutSurfaceAnalysis2::get3dVecFrom2d( const CPoint& point_2d )
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
	void CutSurfaceAnalysis2::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		_clickPoints.clear();
		glDisable( GL_CLIP_PLANE0 );

		if ( _plane != NULL )
		{
			delete _plane;
			_plane  =NULL;
		}
	}
	//----------------------------------------------------------------
	void CutSurfaceAnalysis2::drawPoint( const Vec3& point )
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
	void CutSurfaceAnalysis2::OnLButtonDown( UINT nFlags, CPoint position )
	{
		// 灰掉了if 判断,使在没有地形的情况下也可以使用,但是准确性降低
		//if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
		//{
			_clickPoints.push_back( _mouseVec );
		//}


		//------------------------------------------
		// 这个时候,显示结果,并且重置当前状态
		//------------------------------------------
		
		// Edit By FengYK @2010-04-26 15:01
		// 以下这三句话实际没有用到,这里把他们灰掉了
		//float cellsize = 
		//	ElevationManager::getSingleton().getMainFileHandleVtr()->getHeader()->cellsize;

		//long curlayernum = 
		//	TerrainCenterManager::getSingleton().getCurrentHeightLayerNumber();

		//cellsize = cellsize * pow( 2.0f, curlayernum );

		//------------------------------------------
		// 精度问题!!!!!!!!!!!!
		//------------------------------------------
		if ( _clickPoints.size() < 2 )
		{
			return;
		}

		assert( _clickPoints.size() == 2 );


		if ( _clickPoints.size() != 2 )
		{
			_clickPoints.clear();
			return;
		}

		//------------------------------------------
		// 创建Plane
		//------------------------------------------
		if ( _plane != NULL )
		{
			delete _plane;
			_plane = NULL;
		}

		Vec3 p3 = _clickPoints[1];

		if ( _cutSufSecType == SECT_VERTICAL )
		{
			p3.y += 100;

			_plane = new vgKernel::Plane(_clickPoints[1] , _clickPoints[0] , p3 );
		}
		else if ( _cutSufSecType == SECT_HORIZONTAL )
		{
			p3.y = _clickPoints[0].y;
			p3.z += 100;

			Vec3 ptTemp( _clickPoints[1].x, _clickPoints[0].y, _clickPoints[1].z );
			_plane = new vgKernel::Plane(_clickPoints[0] , ptTemp , p3 );
		}
		else if ( _cutSufSecType == SECT_INCLINE )
		{
			p3.z += 100;
			_plane = new vgKernel::Plane( _clickPoints[1], _clickPoints[0], p3 );
		}


		_clickPoints.clear();
	}
	//----------------------------------------------------------------
	void CutSurfaceAnalysis2::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------

		// Edit By FengYK @2010-04-26 15:56
		// 测试发现开启深度缓存,划线的效果更好一点

		//glDisable( GL_DEPTH_TEST );

		drawPoint( _mouseVec );
		drawLines( _clickPoints , _mouseVec);


		//glEnable( GL_DEPTH_TEST );

		if ( _plane != NULL )
		{
			glEnable( GL_CLIP_PLANE0 );
			
			_clipPlaneParam[0] = _plane->_normal[0];
			_clipPlaneParam[1] = _plane->_normal[1];
			_clipPlaneParam[2] = _plane->_normal[2];
			_clipPlaneParam[3] = _plane->_distance;

			_gpuProgram->setUserClipParam( _clipPlaneParam );

			double dparam[4];

			for ( int i = 0 ; i < 4 ; ++ i )
			{
				dparam[i] = _clipPlaneParam[i];
			}

			glClipPlane( GL_CLIP_PLANE0 , dparam );
		}
	}

	//----------------------------------------------------------------
	void CutSurfaceAnalysis2::drawHeight( Vec3Vector* points )
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
	void CutSurfaceAnalysis2::drawLines( const Vec3Vector& points , const Vec3& mousevec )
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
	void CutSurfaceAnalysis2::OnRBottonDown(UINT nFlags, CPoint position)
	{
		// 右击将裁减面取消
		//glDisable( GL_CLIP_PLANE0 );

		//if ( _plane != NULL )
		//{
		//	delete _plane;
		//	_plane  =NULL;
		//}
	}
	
	
}// end of namespace vgTerritory
