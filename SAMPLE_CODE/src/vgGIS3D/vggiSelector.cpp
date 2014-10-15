



#include <vgStableHeaders.h>
#include <vgGis3d/vggiSelector.h>
#include <vgKernel/vgkCamMgrHolder.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgGis3d/vggiLayer.h>

#include <vgKernel/vgkCamMgrImpl.h>


#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


namespace vgGIS3D {
	
	

	//----------------------------------------------------------------
	Selector::Selector(Layer* layer )
	{
		_layer = layer;
		_heightRender = NULL;
		_LBtnDown = false;

		m_start_x = 0;
		m_start_y = 0;
		m_drag_x = 0;
		m_drag_y = 0;
		m_end_x = 0;
		m_end_y = 0;

		m_window_width = 0;
		m_window_height = 0;

		SetHandleStatus( VG_INPUT_VGSH_SELECTOR );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		//_terrainMgr = TerrainManager::getSingletonPtr();

		//_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		_layer->setEditMode( true );

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGSH_SELECTOR |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI  );

	}
	//----------------------------------------------------------------
	Selector::~Selector()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		if ( _heightRender != NULL )
		{
			delete _heightRender;
			_heightRender = NULL;
		}

		_layer->setEditMode( false );

		_layer->clearSelectedGeometry();
	}
	//----------------------------------------------------------------
	void Selector::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

		if (_LBtnDown)
		{
			m_drag_x = position.x;
			m_drag_y = position.y;
		}

	}
	//----------------------------------------------------------------
	Vec3d Selector::get3dVecFrom2d( const CPoint& point_2d )
	{
		Vec3d ret;

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

		ret.x =  vrx;
		ret.y =  vry;
		ret.z = vrz;

		glPopMatrix();
		return ret;
	}
	//----------------------------------------------------------------
	void Selector::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		if (KEY_DOWN(VK_CONTROL))
		{
			selectLayerGeometry(position , false );
		}
		else
		{
			selectLayerGeometry(position , true );
		}

		return;

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
			_heightRender = new Vec3dVector;
		}

		_heightRender->clear();

		int size = _clickPoints.size();

		//for ( int i = 0 ; i < size - 1; ++ i )
		//{
		//	Vec3d p1 = _clickPoints[ i ];
		//	Vec3d p2 = _clickPoints[ i + 1 ];

		//	int num = (p1 - p2).length() / cellsize;

		//	float dx = ( p2.x - p1.x ) / num;
		//	float dz = ( p2.z - p1.z ) / num;

		//	for ( int k = 0 ; k < num ; ++ k )
		//	{
		//		Vec3d t;
		//		t.x = p1.x + dx * k;
		//		t.z = p1.z + dz * k;

		//		float elev = 0.0f;
		//		bool getok = _terrainMgr->getElevationByPosition( t , elev , true );

		//		t.y = elev;

		//		_heightRender->push_back( t );
		//	}

		//	// 加入最后一个
		//	Vec3d lastone = p2;
		//	float elev = 0.0f;
		//	bool getok = _terrainMgr->getElevationByPosition( lastone , elev , true );
		//	lastone.y = elev;
		//	_heightRender->push_back( lastone );

		//}

		_clickPoints.clear();
	}
	//----------------------------------------------------------------
	void Selector::drawPoint( const Vec3d& point )
	{
		glDisable( GL_TEXTURE_2D );

		glColor3f( 1, 0.1f ,  0 );
		glPointSize( 5.0f );

		glPushMatrix();

		glBegin( GL_POINTS );
		glVertex3dv( point.v );
		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void Selector::OnLButtonDown( UINT nFlags, CPoint position )
	{
		_LBtnDown = true;

		m_start_x = position.x;
		m_start_y = position.y;

		m_drag_x = position.x;
		m_drag_y = position.y;

		//if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
		//{
			//_clickPoints.push_back( _mouseVec );
		//}
	}
	//----------------------------------------------------------------
	void Selector::render()
	{
		//------------------------------------------
		// 得到窗口大小
		//------------------------------------------
		vgKernel::SelectManager::getSingleton().getViewSize( 
			m_window_width , m_window_height );

		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		glDisable( GL_DEPTH_TEST );

		drawPoint( _mouseVec );

		glEnable( GL_DEPTH_TEST );

		if (KEY_DOWN(VK_CONTROL))
		{
			return ;
		}


		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glLoadIdentity();

		float t_begin_x = 
			( (float) m_start_x / (float)m_window_width ) * 2.0f - 1.0f;
		float t_begin_y = 
			( 1.0f - (float) m_start_y / (float)m_window_height ) * 2.0f - 1.0f;

		float t_end_x = 
			( (float)(m_drag_x) / (float)m_window_width ) * 2.0f - 1.0f;
		float t_end_y = 
			( 1.0f - (float) (m_drag_y) / (float)m_window_height ) * 2.0f - 1.0f;

		glDisable( GL_TEXTURE_2D );
		glDisable( GL_DEPTH_TEST);
		glLineWidth(1.0f);
		glColor3f(1,1,1);
		//------------------------------------------
		// 画线
		//------------------------------------------
		if ( _LBtnDown )
		{
			glBegin(GL_LINE_LOOP);
			{
				glVertex2f( t_begin_x, t_begin_y );
				glVertex2f( t_begin_x, t_end_y );
				glVertex2f( t_end_x, t_end_y );
				glVertex2f( t_end_x , t_begin_y );
			}
			glEnd();
		}

		glMatrixMode( GL_PROJECTION );
		glPopMatrix();

		glMatrixMode( GL_MODELVIEW );
		glPopMatrix();

		glEnable(GL_DEPTH_TEST);
		glEnable( GL_TEXTURE_2D );

	}

	//----------------------------------------------------------------
	void Selector::drawHeight( Vec3dVector* points )
	{
		assert( points != NULL );

		Vec3dVector::iterator iter = points->begin();
		Vec3dVector::iterator iter_end = points->end();

		glDisable( GL_TEXTURE_2D );
		glLineWidth( 3.0f );
		glColor3f( 1.0f , 0 , 0 );

		glPushMatrix();
		glBegin( GL_LINE_STRIP );

		for ( ; iter != iter_end ; ++ iter )
		{
			glVertex3dv( iter->v );
		}

		glEnd();
		glPopMatrix();

		return;
	}
	//----------------------------------------------------------------
	void Selector::drawLines( const Vec3dVector& points , const Vec3d& mousevec )
	{
		if ( points.size() < 1 )
		{
			return;
		}

		Vec3dVector::const_iterator iter = points.begin();
		Vec3dVector::const_iterator iter_end = points.end();

		glPushMatrix();

		glDisable( GL_TEXTURE_2D );
		glLineWidth(5.0f);

		glBegin( GL_LINE_STRIP );
		for ( ; iter != iter_end ; ++ iter )
		{	
			glVertex3dv( iter->v );
		}

		glVertex3dv( mousevec.v );

		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void Selector::selectLayerGeometry( CPoint position, bool add_before_clear  )
	{
		//------------------------------------------
		// 开始点选
		//------------------------------------------
		Renderer* tmpMesh = NULL;
		Vec3d click_pos = get3dVecFrom2d(position);
		TRACE ("%f, %f,%f \n",click_pos.x, click_pos.y, click_pos.z);
		Vec3 camera_pos = 
			vgKernel::CamMgrHolder::getSingleton().getCamManager()->getCurrentPosition();


		Vec3d click_dir = click_pos - Vec3d(camera_pos);
		click_dir.normalise();


		//RayLine3d rayline( 
		//	click_pos - click_dir * 100.0 , 
		//	click_pos + click_dir * 100.0 );

		RayLine3d rayline( 
			camera_pos , 
			click_pos );



			Layer* la = _layer;

			if ( add_before_clear )
			{
				la->clearSelectedGeometry();
			}
			
			Geometry* geo = la->testIntersectWithGeometry( rayline );

			if ( geo == NULL )
			{
				return;
			}

			la->addSelectedGeometry( geo );

			la->notifyOberversOnEvent(VG_OBS_INVALIDATE_PROPERTIES, NULL);

	}
	//----------------------------------------------------------------
	void Selector::OnLButtonUp( UINT nFlags, CPoint position )
	{
		
		if (KEY_DOWN(VK_CONTROL))
		{
			_LBtnDown = false;

			return ;
		}

		m_end_x = position.x;
		m_end_y = position.y;

		if ((m_end_x != m_start_x || m_end_y != m_start_y) && _LBtnDown)
		{
			SelectRectObject();
		} 

		_LBtnDown = false;

	}
	//----------------------------------------------------------------
	void Selector::SelectRectObject()
	{
		GLdouble proj_mat[16];
		GLdouble model_mat[16];

		glGetDoublev( GL_PROJECTION_MATRIX , proj_mat);
		glGetDoublev( GL_MODELVIEW_MATRIX , model_mat);

		GLdouble winx;
		GLdouble winy;
		GLdouble winz;

		int ViewPort[4];

		//float maxx, maxy, minx, miny;
		CPoint maxPoint;
		CPoint minPoint;

		glGetIntegerv (GL_VIEWPORT,ViewPort);

		if (m_start_x < m_end_x)
		{
			minPoint.x = (long)m_start_x;
			maxPoint.x = (long)m_end_x;
		} 
		else
		{
			minPoint.x = (long)m_end_x;
			maxPoint.x = (long)m_start_x;
		}

		if (ViewPort[3] - m_end_y < ViewPort[3] - m_start_y)
		{
			minPoint.y = ViewPort[3] - m_end_y;
			maxPoint.y = ViewPort[3] - m_start_y;
		}
		else
		{
			minPoint.y = ViewPort[3] - m_start_y;
			maxPoint.y = ViewPort[3] - m_end_y;
		}

	
		//------------------------------------------
		// 遍历选中物体
		//------------------------------------------

			Renderer* cr = _layer;

			if ( cr->getType() != RENDERER_TYPE_GIS_LAYER )
			{
				MessageBox( NULL , "请选中shape物体" , "提示" , MB_OK );
				return;
			}

			Layer* la = ( Layer * ) cr;

			la->clearSelectedGeometry();

			//------------------------------------------
			// 测试rect
			//------------------------------------------
			using namespace vgGIS3D;
			GeometryPointerVec* geos = la->getGeometries();
			assert( geos != NULL );

			GeometryPointerVec::iterator i = geos->begin();
			GeometryPointerVec::iterator i_end = geos->end();

			for ( ; i != i_end ; ++i )
			{
				Geometry* ge = *i;
				vgKernel::Box box = ge->getEnvelope3f();

				box.matrixTranslation( la->getMatrix() );

				for (int i=0; i<8; i++)
				{
					vgKernel::Vec3 corner = box.getCorner(i);

					gluProject( corner.x , corner.y , corner.z ,
						model_mat , proj_mat , ViewPort , &winx , &winy , &winz );

					if (maxPoint.x < winx || maxPoint.y < winy || minPoint.x > winx || minPoint.y > winy)
					{
						continue;
					}
					else if (winz < 1.0)
					{
						la->addSelectedGeometry( ge );
					}
				}
			}

			la->notifyOberversOnEvent(VG_OBS_INVALIDATE_PROPERTIES, NULL);



		return;
	}
	//----------------------------------------------------------------

	
}// end of namespace vgShape
