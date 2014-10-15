



#include <vgStableHeaders.h>
#include <vgTerritory/vgtCutSurfaceLevelling.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtElevationFilter.h>
#include <vgKernel/vgkRendererManager.h>
//#include "vgDlgPlaneLevel.h"

#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkWarning.h>
#include <vgKernel/vgkCoordSystem.h>


namespace vgTerritory {



	//----------------------------------------------------------------
	CutSurfaceLevelling::CutSurfaceLevelling()
	{
		_heightRender = NULL;

		SetHandleStatus( VG_INPUT_VGT_CUTLEVELLING );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		_terrainMgr = TerrainManager::getSingletonPtr();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();


		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VGT_CUTLEVELLING  );
		//  [11/10/2008 zhu]
		btm=false;
		avh=0;

	}
	//----------------------------------------------------------------
	CutSurfaceLevelling::~CutSurfaceLevelling()
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
	void CutSurfaceLevelling::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

	}
	//----------------------------------------------------------------
	vgKernel::Vec3 CutSurfaceLevelling::get3dVecFrom2d( const CPoint& point_2d )
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
	void CutSurfaceLevelling::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		//------------------------------------------
		// 这个时候,显示结果,并且重置当前状态
		//------------------------------------------

		if ( _clickPoints.size() < 3 )
		{
			_clickPoints.clear();
			return;
		}

		if (btm==false)//  [11/10/2008 zhu]
		{
			btm=true;


			int size = _clickPoints.size();

			rect=new double*[size];
			for(int i=0;i<size;i++)
				rect[i]=new double[3];

			Vec2Vector* vec2s = new Vec2Vector;

			for ( int i = 0 ; i < size; ++ i )
			{
				Vec3 p1 = _clickPoints[ i ];

				vec2s->push_back( Vec2(  p1.x, p1.z ) );
				rect[i][0]=p1.x;
				rect[i][1]=avh;
				rect[i][2]=p1.z;
			}
			return;
		}
		else
		{
			
			int size = _clickPoints.size();

			Vec2Vector* vec2s = new Vec2Vector;

			for ( int i = 0 ; i < size; ++ i )
			{
				Vec3 p1 = _clickPoints[ i ];

				vec2s->push_back( Vec2( p1.x , p1.z ) );
			}

			ElevationPolygon* poly = new ElevationPolygon( vec2s , avh );/*500.0f*/

			if(vgTerritory::TerrainManager::getSingleton().hasTerrainData() )//如果是vtr的地形，走这个路线
			{
				

				//此poly作为此次的计算土方来使用
				//--------------------------------------
				//以下是计算代码
				//--------------------------------------

				Vec3 pmin = _clickPoints[ 0 ];//minx minz
				Vec3 pmax =	_clickPoints[ 0 ];//maxx,maxz

				for ( int i = 0 ; i < size - 1; ++ i )
				{
					if (_clickPoints[ i ].x<pmin.x) pmin.x=_clickPoints[ i ].x;
					if (_clickPoints[ i ].z<pmin.z) pmin.z=_clickPoints[ i ].z;
					if (_clickPoints[ i ].x>pmax.x) pmax.x=_clickPoints[ i ].x;
					if (_clickPoints[ i ].z>pmax.z) pmax.z=_clickPoints[ i ].z;
				}
				//现在pmin,pmax就是包围盒了
				//下面开始计算，首先需要确定的是积分的单元格cellsize

				int cellsize=8;	//在这里获取最精细的cellsize
				float cellarea=cellsize*cellsize;
				int xnum = (pmax.x - pmin.x)/ cellsize;
				int znum = (pmax.z - pmin.z)/ cellsize;

				float dx = pmin.x / cellsize;
				float dz = pmin.z / cellsize;

				Vec3 t;
				float Volume1=0,Volume2=0,Volume3=0;//统计总的体积
				float elev;
				vgKernel::PointInPolygon pip( size , &(*vec2s)[0] );//还不知道这样构造是否正确，有待验证

				for ( int k = 0 ; k < xnum ; ++ k )
				{
					for ( int l = 0 ; l < znum ; ++ l )
					{
						t.x=pmin.x+k*cellsize;
						t.z=pmin.z+l*cellsize;
						if(pip.contains(Vec2(t.x,t.z)))//t在多边形之内的话
						{
							bool getok = _terrainMgr->getElevationByPosition( t , elev , true );
							if (elev>avh)
								Volume1+=(elev-avh);//挖掉的
							else if(elev<avh)
								Volume2+=(avh-elev);//填充的
						}
					}
				}
				//===================
				getNeedLevellingRenderer(_clickPoints);
				//===================
				Volume1*=cellarea;
				Volume2*=cellarea;
				char msg[100];
				if(Volume1>Volume2)
				{	Volume3=Volume1-Volume2;
				sprintf_s(msg,"需挖土方%.0f方,需填土方%.0f方,两者相抵实际需挖土方%.0f方",Volume1,Volume2,Volume3);}
				else
				{
					Volume3=Volume2-Volume1;
					sprintf_s(msg,"需挖土方%.0f方,需填土方%.0f方,两者相抵实际需填土方%.0f方",Volume1,Volume2,Volume3);
				}


				std::ostringstream o;

				o << msg << "\n\n" << "是否进行平整操作?";

				if ( vgKernel::SelectManager::getSingleton().getSelectedItems().empty() 
					== false )
				{
					o << " 提示: 选择集不为空, 平整将对此部分物体进行操作.";
				}

				int ret = VGK_WARN( vgKernel::Warning::WARN_INTERNAL_WARNING , 
					vgKernel::Warning::BUTTON_YES_NO, 
					o.str(),
					"CutSurfaceLevelling::OnLButtonDbClick");

				if ( ret == vgKernel::Warning::RETURN_NO )
				{
					_clickPoints.clear();

					btm=false;//  [11/10/2008 zhu]

					vgKernel::SelectManager::getSingleton().clearSelection();
					//------------------------------------------
					// 取消当前状态
					//------------------------------------------
					TerrainManager::getSingleton().setCutSurfaceLevellingFlag(false);

					return;
				}

				//MessageBox(NULL,msg,"GIS分析",0);
				//

				// add by lss when 2009-1-11 15:31:04 
				//vgMod::ModTerrainManager::getSingleton().doFilter(vec2s , avh);


				ElevationFilter::getSingleton().pushPolygon( poly );
				//------------------------------------------
				// 将更改反映到屏幕上.
				//------------------------------------------
				ElevationFilter::getSingleton().doFilterInMemory();
			}


			_clickPoints.clear();

			btm=false;//  [11/10/2008 zhu]
		}


		vgKernel::SelectManager::getSingleton().clearSelection();
		//------------------------------------------
		// 取消当前状态
		//------------------------------------------
		TerrainManager::getSingleton().setCutSurfaceLevellingFlag(false);

	}
	vgKernel::RendererQueue* CutSurfaceLevelling::getNeedLevellingRenderer(Vec3Vector _clickPoints)
	{
		vgKernel::RendererQueue tmpque;

		if ( !vgKernel::SelectManager::getSingleton().getSelectedItems().empty() )
		{
			vgKernel::RendererQueue* queue =
				&vgKernel::SelectManager::getSingleton().getSelectedItems();
			//------------------------------------------
			// 拷贝
			//------------------------------------------
			{
				vgKernel::RendererQueue::iterator iter = queue->begin();
				vgKernel::RendererQueue::iterator iter_end = queue->end();
				for (  ; iter != iter_end ; ++ iter )
				{
					tmpque.push_back( *iter );
				}
			}
		}
		else
		{
			vgKernel::RendererPackage* _culledRenderers =RendererManager::getSingletonPtr()->getAllRendererPackage();
			RendererPackage::iterator ipac = _culledRenderers->begin();
			RendererPackage::iterator ipac_end = _culledRenderers->end();

			for ( ; ipac != ipac_end; ++ ipac )
			{
				RendererQueue* que = &ipac->second;
				vgKernel::RendererQueue::iterator iter = que->begin();
				vgKernel::RendererQueue::iterator iter_end = que->end();
				for (  ; iter != iter_end ; ++ iter )
				{
					tmpque.push_back( *iter );
				}
			}
		}
		

		vgKernel::SelectManager::getSingleton().clearSelection();

		//vgKernel::RendererPackage* _culledRenderers =RendererManager::getSingletonPtr()->getCulledRendererPackage();
		//RendererPackage::iterator ipac = _culledRenderers->begin();
		//RendererPackage::iterator ipac_end = _culledRenderers->end();

		Vec2 pmin( _clickPoints[ 0 ].x , _clickPoints[ 0 ].z );
		Vec2 pmax = pmin;

		for ( int i = 0 ; i < _clickPoints.size(); ++ i )
		{
			if (_clickPoints[ i ].x<pmin.x) pmin.x=_clickPoints[ i ].x;
			if (_clickPoints[ i ].z<pmin.y) pmin.y=_clickPoints[ i ].z;
			if (_clickPoints[ i ].x>pmax.x) pmax.x=_clickPoints[ i ].x;
			if (_clickPoints[ i ].z>pmax.y) pmax.y=_clickPoints[ i ].z;
		}

		ElevationBound bd( pmin , pmax );

		RendererQueue* que = &tmpque;
		assert( que != NULL );

		RendererQueue::iterator iter  = que->begin();
		RendererQueue::iterator iter_end = que->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Renderer* mi = *iter;

			vgKernel::Box boundBox = mi->getBoundingBox();

			ElevationBound tmpbd( 
				boundBox._minVertex.x ,
				boundBox._minVertex.z ,
				boundBox._maxVertex.x ,
				boundBox._maxVertex.z );

			if ( bd.testIntersection( tmpbd ) )
			{
				vgKernel::SelectManager::getSingleton().addSelection( mi );
			}
		}

		return	&vgKernel::SelectManager::getSingleton().getSelectedItems();
	}
	//----------------------------------------------------------------
	void CutSurfaceLevelling::drawPoint( const Vec3& point )
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
	void CutSurfaceLevelling::OnLButtonDown( UINT nFlags, CPoint position )
	{
		//MessageBox( NULL , _mouseVec.getDetails().c_str() , "" , MB_OK );

		if (btm==false)
		{
			if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
			{
				_clickPoints.push_back( _mouseVec );
			}
		}

	}
	void CutSurfaceLevelling::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		if ( _clickPoints.size() < 3 )
		{
			_clickPoints.clear();
			return;
		}

		if(zDelta>0)

			avh+=1;
		else if(zDelta<0)
			avh-=1;
		if (btm==true)
		{

			int num=_clickPoints.size();
			for(int dnum=0;dnum<num;dnum++)
			{
				rect[dnum][1]=avh;
			}

		}


	}
	//----------------------------------------------------------------
	void CutSurfaceLevelling::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		glDisable( GL_DEPTH_TEST );


		drawPoint( _mouseVec );
		drawLines( _clickPoints , _mouseVec,btm);

		if ( _heightRender != NULL )
		{
			drawHeight( _heightRender );
		}

		glEnable( GL_DEPTH_TEST );
		renderExtra();
	}
	void CutSurfaceLevelling::renderExtra()//  [11/10/2008 zhu]
	{

		glEnable( GL_BLEND );

		if(btm==TRUE)
		{
			glPushAttrib(GL_CURRENT_BIT);
			glPushMatrix();				
			glColor4f(0,0,10,0.5);
			glEnable(GL_DEPTH_TEST);
			// 绘制模拟面 [11/5/2008 zhu]
			basetess = gluNewTess();
			gluTessCallback(basetess, GLU_BEGIN, (void(__stdcall*)())glBegin);
			gluTessCallback(basetess, GLU_VERTEX,(void(__stdcall*)())glVertex3dv);
			gluTessCallback(basetess, GLU_END, glEnd);
			glShadeModel(GL_FLAT); 
			//绘制路径
			gluTessBeginPolygon(basetess, (GLvoid *)0);
			gluTessBeginContour(basetess);
			for(int dnum=0;dnum<_clickPoints.size();dnum++)
			{		
				gluTessVertex(basetess, rect[dnum], rect[dnum]);
			}
			gluTessEndContour(basetess);
			gluTessEndPolygon(basetess);
			gluDeleteTess(basetess);


			glDisable( GL_DEPTH_TEST );
			// 绘制模拟边界 [11/5/2008 zhu]
			Vec3Vector::iterator iter = _clickPoints.begin();
			Vec3Vector::iterator iter_end = _clickPoints.end();
			glBegin(GL_LINE_LOOP);
			for ( ;iter != iter_end ; ++ iter)
			{
				glVertex3f((*iter).x,avh,(*iter).z);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
			}
			glEnd();
			glEnable(GL_DEPTH_TEST);				
			glPopMatrix();
			glPopAttrib();
		}

		glDisable( GL_BLEND );

		return;
	}
	void CutSurfaceLevelling::OnRBottonDown(UINT nFlags, CPoint position) 
	{
		CWnd *pwnd=AfxGetApp()->m_pMainWnd;
		if(btm==TRUE)
		{
			assert(0);

#if 0
			CPlaneLevel *dlg=new CPlaneLevel;

			vgKernel::Vec3 v = 
				vgKernel::CoordSystem::getSingleton().getProjectionCoord();

			dlg->m_plane_level=avh+ v.y;	
			dlg->Create(IDD_WATER_LEVEL,NULL);			
			dlg->SetWindowPos(pwnd,400,300,NULL,NULL,SWP_NOSIZE);
			dlg->ShowWindow(SW_SHOW);
#endif
		}	

	}

	//----------------------------------------------------------------
	void CutSurfaceLevelling::drawHeight( Vec3Vector* points )
	{
		assert( points != NULL );

		Vec3Vector::iterator iter = points->begin();
		Vec3Vector::iterator iter_end = points->end();

		glDisable( GL_TEXTURE_2D );
		glLineWidth( 2.0f );
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
	void CutSurfaceLevelling::drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm)
	{
		if ( points.size() < 1 )
		{
			return;
		}

		Vec3Vector::const_iterator iter = points.begin();
		Vec3Vector::const_iterator iter_end = points.end();

		glPushMatrix();

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

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void CutSurfaceLevelling::OnKeyDown( int keyCode )
	{
		if(keyCode == vgKernel::InputCode::ESCAPE)
		{
			//------------------------------------------
			// 取消当前状态
			//------------------------------------------
			TerrainManager::getSingleton().setCutSurfaceLevellingFlag(false);
		}
	}
	
	//----------------------------------------------------------------
	bool CutSurfaceLevelling::getFlagButtonDown()
	{
		return btm;
	}

	//----------------------------------------------------------------
	float CutSurfaceLevelling::getHeight()
	{
		return avh;
	}

}// end of namespace vgTerritory
