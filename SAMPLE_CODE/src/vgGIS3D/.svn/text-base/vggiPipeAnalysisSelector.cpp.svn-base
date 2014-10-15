



#include <vgStableHeaders.h>
#include <vgGis3d/vggiPipeAnalysisSelector.h>
#include <vgKernel/vgkCamMgrHolder.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgGis3d/vggiOGRPipeLineMap.h>
#include <vgGis3d/vggiLine.h>
#include <vgGIS3d/vggiPrerequisite.h>
#include <vgGIS3D\vggiDlgPointAttri.h>
#include <vgGIS3D\vgPipeAttriDlg.h>

#include <vgKernel/vgkCamMgrImpl.h>


#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


namespace vgGIS3D {
	
	

	//----------------------------------------------------------------
	PipeAnalysisSelector::PipeAnalysisSelector(OGRPipeLineMap* pipeLine )
	{
		_pipeLine = pipeLine;
		_heightRender = NULL;
		_LBtnDown = false;
		PipeAtrdlg = NULL;
		PointAtrdlg = NULL;

		m_start_x = 0;
		m_start_y = 0;
		m_drag_x = 0;
		m_drag_y = 0;
		m_end_x = 0;
		m_end_y = 0;

		m_window_width = 0;
		m_window_height = 0;

		SetHandleStatus( VG_INPUT_VGSH_PIPEANALYSISSELECTOR );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		//_terrainMgr = TerrainManager::getSingletonPtr();

		//_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		_pipeLine->setEditMode( true );

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGSH_PIPEANALYSISSELECTOR |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI  );

	}
	//----------------------------------------------------------------
	PipeAnalysisSelector::~PipeAnalysisSelector()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		if ( _heightRender != NULL )
		{
			delete _heightRender;
			_heightRender = NULL;
		}

		if (PipeAtrdlg != NULL)
		{
			delete PipeAtrdlg;
			PipeAtrdlg = NULL;
		}

		if (PointAtrdlg != NULL)
		{
			delete PointAtrdlg;
			PointAtrdlg = NULL;
		}

		_pipeLine->setEditMode( false );

		_pipeLine->clearSelectedGeometry();
	}
	//----------------------------------------------------------------
	void PipeAnalysisSelector::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

		if (_LBtnDown)
		{
			m_drag_x = position.x;
			m_drag_y = position.y;
		}

	}
	//----------------------------------------------------------------
	Vec3d PipeAnalysisSelector::get3dVecFrom2d( const CPoint& point_2d )
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
	void PipeAnalysisSelector::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		if (KEY_DOWN(VK_CONTROL))
		{
			selectLayerGeometry(position , false );
		}
		else
		{
			selectLayerGeometry(position , true );
		}

		Renderer* cr = _pipeLine;

		if ( cr->getType() != RENDERER_TYPE_PIPELINE_LAYER )
		{
			MessageBox( NULL , "请选中管线图层" , "提示" , MB_OK );
			return;
		}

		OGRPipeLineMap* la = ( OGRPipeLineMap * ) cr;

		if ( !(la->getSelectedGeometry()->empty()))
		{
			if (PipeAtrdlg != NULL)
			{
				delete PipeAtrdlg;
				PipeAtrdlg = NULL;
			}
			PipeAtrdlg=new vgPipeAttriDlg;				
			PipeAtrdlg->Create(vgPipeAttriDlg::IDD,NULL);
			PipeAtrdlg->ShowWindow(SW_SHOW);
		}
		else
		{
			return;
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

		_clickPoints.clear();
	}
	//----------------------------------------------------------------
	void PipeAnalysisSelector::drawPoint( const Vec3d& point )
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
	void PipeAnalysisSelector::OnLButtonDown( UINT nFlags, CPoint position )
	{
		if (KEY_DOWN(VK_CONTROL))
		{
			selectPipeGeoInVec(position, false);
		}
		else
		{
			_LBtnDown = true;

			m_start_x = position.x;
			m_start_y = position.y;

			m_drag_x = position.x;
			m_drag_y = position.y;
		}
	}
	//----------------------------------------------------------------
	void PipeAnalysisSelector::selectPipeGeoInVec(CPoint position, bool add_before_clear)
	{
		//------------------------------------------
		// 开始点选
		//------------------------------------------
		Renderer* tempMesh = NULL;
		Vec3d click_pos = get3dVecFrom2d(position);
		Vec3 camera_pos = 
			vgKernel::CamMgrHolder::getSingleton().getCamManager()->getCurrentPosition();
		Vec3d click_dir = click_pos - Vec3d(camera_pos);

		click_dir.normalise();
		RayLine3d rayline(camera_pos, click_pos);
		OGRPipeLineMap *la = _pipeLine;
		if (add_before_clear)
		{
			la->clearSelectPipeGeoVec();
		}

		PipeGeoPtr pipeGeo = la->testInterSectWithPipeGeo(rayline);
		if (pipeGeo.isNull() == true)
		{
			return;
		}

		la->addSelectPipeGeo(pipeGeo);
		la->notifyOberversOnEvent(VG_OBS_INVALIDATE_PROPERTIES, NULL);
	}
	//----------------------------------------------------------------
	void PipeAnalysisSelector::render()
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
		glLineWidth(0.2f);
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
	void PipeAnalysisSelector::drawHeight( Vec3dVector* points )
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
	void PipeAnalysisSelector::drawLines( const Vec3dVector& points , const Vec3d& mousevec )
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
	void PipeAnalysisSelector::selectLayerGeometry( CPoint position, bool add_before_clear  )
	{
		//------------------------------------------
		// 开始点选
		//------------------------------------------
		Renderer* tmpMesh = NULL;
		Vec3d click_pos = get3dVecFrom2d(position);
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



			OGRPipeLineMap* la = _pipeLine;

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
	void PipeAnalysisSelector::OnLButtonUp( UINT nFlags, CPoint position )
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
	void PipeAnalysisSelector::SelectRectObject()
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

			Renderer* cr = _pipeLine;

			if ( cr->getType() != RENDERER_TYPE_PIPELINE_LAYER )
			{
				MessageBox( NULL , "请选中管线图层" , "提示" , MB_OK );
				return;
			}

			OGRPipeLineMap* la = ( OGRPipeLineMap * ) cr;

			la->clearSelectedGeometry();
			la->clearSelectedPoint();
			float pipeLineRadius = la->getPipeLineRadius();

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
				Geometry* geometry = *i;

				LineString *ge 
					= dynamic_cast<LineString*>(geometry);

				vgKernel::Box box = ge->getPipeLineEnvelope3f(pipeLineRadius);
				//vgKernel::Box box = la->getPipeLineBox(ge);

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
						//la->addSelectedGeometry( ge );
						RingStruct rings = ge->getRing();

						for (int i = 0; i < rings._numPoints; i ++/*= rings._numPoints */)
						{
							PointStruct pointStruct;	  							
							pointStruct.pos.x = rings._pointsBeginAddr[3 * i + 0];
							pointStruct.pos.y = rings._pointsBeginAddr[3 * i + 1];
							pointStruct.pos.z = rings._pointsBeginAddr[3 * i + 2];

							vgKernel::Vec3 position = vgKernel::Math::translateVec3(la->getMatrix(), pointStruct.pos);
							gluProject(position.x, position.y, position.z,
								model_mat , proj_mat , ViewPort , &winx , &winy , &winz);

							//gluProject(pointStruct.pos.x, pointStruct.pos.y, pointStruct.pos.z,
							//	model_mat , proj_mat , ViewPort , &winx , &winy , &winz);

							if (maxPoint.x < winx || maxPoint.y < winy || minPoint.x > winx || minPoint.y > winy)
							{
								continue;
							}
							else if (winz < 1.0)
							{
								pointStruct.pos = position;
								la->addSelectPoints(pointStruct);
								m_Already = false;
							}
						}
					}
				}
			}

			la->notifyOberversOnEvent(VG_OBS_INVALIDATE_PROPERTIES, NULL);



		return;
	}

	void PipeAnalysisSelector::OnRBottonDown( UINT nFlags, CPoint position )
	{
		Renderer* cr = _pipeLine;

		if ( cr->getType() != RENDERER_TYPE_PIPELINE_LAYER )
		{
			MessageBox( NULL , "请选中管线图层" , "提示" , MB_OK );
			return;
		}

		OGRPipeLineMap* la = ( OGRPipeLineMap * ) cr;

		std::vector <PointStruct>* pointVec = la->getSelectedPointVec();

		if (!pointVec->empty())
		{
			if (m_Already == true)
			{
				return;
			}
			else
			{
				if (PointAtrdlg != NULL)
				{
					delete PointAtrdlg;
					PointAtrdlg = NULL;
				}

				PointAtrdlg = new vgDlgPointAttri();				
				PointAtrdlg->Create(vgDlgPointAttri::IDD,NULL);
				PointAtrdlg->ShowWindow(SW_SHOW);

				m_Already = true;                           //置为true下次右击不会弹出相同的对话框
			}

		}
	}
	//----------------------------------------------------------------

	
}// end of namespace vgShape
