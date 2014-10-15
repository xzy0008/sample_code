


#include <vgStableHeaders.h>
#include <vgTerritory/vgtCutSurfaceVisibility2.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgKernel/vgkRendererManager.h>

namespace vgTerritory {
	
	


	//----------------------------------------------------------------
	CutSurfaceVisibility2::CutSurfaceVisibility2()
	{

		_heightRender = NULL;

		SetHandleStatus( VG_INPUT_VGT_CUTVISIBLITY2 );

		vgKernel::InputSystem::getSingleton().registerHandle( this );

		_terrainMgr = TerrainManager::getSingletonPtr();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGT_CUTVISIBLITY2 |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );
		bFirst = true;
		pDlgVisiAna = NULL;
	}
	//----------------------------------------------------------------
	CutSurfaceVisibility2::~CutSurfaceVisibility2()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		if ( _heightRender != NULL )
		{
			delete _heightRender;
			_heightRender = NULL;
		}

		if ( pDlgVisiAna != NULL )
		{
			delete pDlgVisiAna;
			pDlgVisiAna = NULL;
		}

	}
	//----------------------------------------------------------------
	void CutSurfaceVisibility2::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

	}
	//----------------------------------------------------------------
	vgKernel::Vec3 CutSurfaceVisibility2::get3dVecFrom2d( const CPoint& point_2d )
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
	void CutSurfaceVisibility2::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		return;
	}
	//----------------------------------------------------------------
	void CutSurfaceVisibility2::drawPoint( const Vec3& point )
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
	void CutSurfaceVisibility2::OnLButtonDown( UINT nFlags, CPoint position )
	{
		//MessageBox( NULL , _mouseVec.getDetails().c_str() , "" , MB_OK );


		//if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
		//{
			_clickPoints.push_back( _mouseVec );
		//}

		if ( bFirst )
		{
			vecLinePoints.clear();
			vecDisVisiName.clear();
			bFirst = false;
		}
		else
		{
			bFirst = true;
		}

		vecLinePoints.push_back( _mouseVec );

		if ( _clickPoints.size() < 2 )
		{
			return;
		}

		assert( _clickPoints.size() == 2 );

		//------------------------------------------
		// 首先将数据取出来, 然后清空.
		//------------------------------------------
		Vec3 p1 = _clickPoints[ 0 ];
		Vec3 p2 = _clickPoints[ 1 ];
		_clickPoints.clear();


		
		if ( _terrainMgr->hasTerrainData() == false )
		{
			if ( (p1 - p2).length() < 0.2f )
			{
				MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
					"采样点距离过小, 请重新采样" , "通视分析" , MB_OK | MB_ICONQUESTION );

				return;
			}

			Vec3 dir = p2 - p1;
			dir.normalise();

			Vec3 testbeg = p1 + dir * 0.1f;
			Vec3 testend = p2 - dir * 0.1f;

			//------------------------------------------
			// 开始测试renderer物体
			//------------------------------------------
			Segment3 seg( testbeg , testend );

			bool testres = testRenderersIntersect(seg);

			alert( p1 , p2 , testres );

			return;
		}

		float cellsize = 
			ElevationManager::getSingleton().getMainFileHandleVtr()->getHeader()->cellsize;

		long curlayernum = 
			TerrainCenterManager::getSingleton().getCurrentHeightLayerNumber();

		cellsize = cellsize * pow( 2.0f, curlayernum );

		//------------------------------------------
		// 精度问题!!!!!!!!!!!!
		//------------------------------------------
		if ( _heightRender == NULL )
		{
			_heightRender = new Vec3Vector;
		}
		_heightRender->clear();


		int num = (p1 - p2).length() / cellsize;

		if ( num < 3 )
		{
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
				"采样点距离过小, 请重新采样" , "通视分析" , MB_OK | MB_ICONQUESTION );

			return;
		}

		//------------------------------------------
		// 这个时候, 开始判定通透性,和地形一起
		//------------------------------------------
		float dx = ( p2.x - p1.x ) / num;
		float dz = ( p2.z - p1.z ) / num;

		//------------------------------------------
		// 得到起始和末尾的高程点.
		//------------------------------------------
		float p1y = p1.y;
		float p2y = p2.y;

		float p1y_e = 0.0f;
		float p2y_e = 0.0f;
		_terrainMgr->getElevationByPosition( p1 , p1y_e , true );
		_terrainMgr->getElevationByPosition( p2 , p2y_e , true );

		if ( p1y_e > p1.y )
		{
			p1y = p1y_e;
		}

		if ( p2y_e > p2.y )
		{
			p2y = p2y_e;
		}

		float dy = ( p2y - p1y ) / num;
		
 		bool can_not_see_it = false;

		_heightRender->push_back( p1 );

		for ( int k = 1 ; k < num - 1 ; ++ k )
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
				vecDisVisiName.push_back(_T("地形"));
				break;
#if VGT_VISIBILITY_DRAW_HEIGHT
				break;
#endif
			}
		}

		_heightRender->push_back( p2 );

		Vec3 testbeg( p1.x + dx * 1 , p1y + dy * 1 , p1.z + dz * 1 );
		Vec3 testend( p1.x + dx * (num-2) , p1y + dy * (num-2) , p1.z + dz * (num-2) );

		//------------------------------------------
		// 开始测试renderer物体
		//------------------------------------------
		if ( can_not_see_it == false )
		{
			Segment3 seg( testbeg , testend );

			bool testres = testRenderersIntersect(seg);

			can_not_see_it = testres;
		}

		alert( p1 , p2 , !can_not_see_it );

		return;
	}
	//----------------------------------------------------------------
	void CutSurfaceVisibility2::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		

		drawPoint( _mouseVec );
		drawLines( _clickPoints , _mouseVec);

		if ( pDlgVisiAna != NULL )
		{
			if ( pDlgVisiAna->getClosed() )
			{
				vecLinePoints.clear();
				pDlgVisiAna->setClosed( false );
			}
		}

		drawHeight( &vecLinePoints );

		glDisable( GL_DEPTH_TEST );

#if VGT_VISIBILITY_DRAW_HEIGHT
		if ( _heightRender != NULL )
		{
			drawHeight( _heightRender );
		}
#endif

		glEnable( GL_DEPTH_TEST );

	}

	//----------------------------------------------------------------
	void CutSurfaceVisibility2::drawHeight( Vec3Vector* points )
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
	void CutSurfaceVisibility2::drawLines( const Vec3Vector& points , const Vec3& mousevec )
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
	bool CutSurfaceVisibility2::testRenderersIntersect( const Segment3& seg )
	{
		vgKernel::RendererPackage* _culledRenderers = 
			RendererManager::getSingletonPtr()->getCulledRendererPackage();


		RendererPackage::iterator ipac = _culledRenderers->begin();
		RendererPackage::iterator ipac_end = _culledRenderers->end();

		bool result = false;

		for ( ; ipac != ipac_end; ++ ipac )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end ; ++ iter )
			{
				Renderer* cr = *iter;

				bool testres = 
					cr->testIntersectWithTriangles( seg );

				if ( testres == true )
				{
					CString strName(_T(""));
					strName = cr->getName().c_str();
					vecDisVisiName.push_back( strName );
					result = true;
					//return true;
				}
			}
		}// end ipac

		return result;
		return false;
	}
	//----------------------------------------------------------------
	void CutSurfaceVisibility2::alert( const Vec3& p1 , const Vec3& p2 , const bool& visible )
	{
		std::ostringstream o;

		if ( !visible )
		{	
			o << "视点不可见.";
		}
		else
		{
			o << "视点可见.";
		}

		o << "\n\n点1: " << p1.getDetails() 
			<< "\n点2: " << p2.getDetails();

		if ( !visible )
		{
			if ( pDlgVisiAna != NULL )
			{
				delete pDlgVisiAna;
				pDlgVisiAna = NULL;
			}

			pDlgVisiAna = new CDlg_VisibleAnalyst;
			pDlgVisiAna->vecStrModName.clear();
			if ( vecDisVisiName.size() > 0 )
			{
				std::vector <CString> ::iterator iter = vecDisVisiName.begin();
				std::vector <CString> ::iterator iterEnd = vecDisVisiName.end();
				
				for ( iter; iter != iterEnd; iter++ )
				{
					CString txtName = (*iter);
					pDlgVisiAna->vecStrModName.push_back(txtName);
				}
			}

			pDlgVisiAna->Create( CDlg_VisibleAnalyst::IDD, NULL );
			pDlgVisiAna->ShowWindow(SW_SHOW);
			
			pDlgVisiAna->strVisiAnaRes = o.str().c_str();
			pDlgVisiAna->UpdateData( FALSE );
		}
		else
		{
			if ( pDlgVisiAna != NULL )
			{
				delete pDlgVisiAna;
				pDlgVisiAna = NULL;
			}

			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
				o.str().c_str() , "通视分析" , MB_OK | MB_ICONQUESTION );
		}

		return;
	}
	//----------------------------------------------------------------

	
}// end of namespace vgTerritory
