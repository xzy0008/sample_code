
#include "vgStableHeaders.h"
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgPlan/vgAreaSelector.h>
#include <vgTerritory/vgtElevationPolygon.h>
#include <vgPlan/vgPlanmanager.h>
#include <vgKernel/vgkInputCodeDef.h>

namespace vgPlan
{



	//----------------------------------------------------------------
	AreaSelector::AreaSelector()
	{
		_heightRender = NULL;

		SetHandleStatus( VG_INPUT_PLAN_SELECTOR );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		//_terrainMgr = TerrainManager::getSingletonPtr();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();


		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_PLAN_SELECTOR | VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );
		//  [11/10/2008 zhu]
		btm=false;
		avh=0;

	}
	//----------------------------------------------------------------
	AreaSelector::~AreaSelector()
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
	void AreaSelector::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );

	}
	//----------------------------------------------------------------
	vgKernel::Vec3 AreaSelector::get3dVecFrom2d( const CPoint& point_2d )
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
	void AreaSelector::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		//------------------------------------------
		// 这个时候,显示结果,并且重置当前状态
		//------------------------------------------

		if ( _clickPoints.size() < 3 )
		{
			_clickPoints.clear();
			return;
		}
		
		// rect = new double*[_clickPoints.size() + 1];
		_resultVec.clear();
		for (int i=0; i<_clickPoints.size(); i++)
		{
			_resultVec.push_back(_clickPoints[i]);
		}

		_resultVec.push_back(_mouseVec);

		vgPlan::vgPlanManager::getSingleton().setSelectorFlag(false);

		return ;
	}

	//----------------------------------------------------------------
	void AreaSelector::drawPoint( const Vec3& point )
	{
		glDisable( GL_TEXTURE_2D );

		glColor3f( 0.f, 0.f , 1.f );
		glPointSize( 3.0f );

		glPushMatrix();

		glBegin( GL_POINTS );
		glVertex3fv( point.v );
		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void AreaSelector::OnLButtonDown( UINT nFlags, CPoint position )
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
	void AreaSelector::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{


	}
	//----------------------------------------------------------------
	void AreaSelector::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		glDisable( GL_DEPTH_TEST );


		drawPoint( _mouseVec );
		drawLines( _clickPoints , _mouseVec,btm);

		glEnable( GL_DEPTH_TEST );
		// renderExtra();
	}

	void AreaSelector::renderExtra()//  [11/10/2008 zhu]
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
	void AreaSelector::OnRBottonDown(UINT nFlags, CPoint position) 
	{

		_clickPoints.clear();
		vgPlanManager::getSingleton().setSelectorFlag(false);
	}

	//----------------------------------------------------------------
	void AreaSelector::drawHeight( Vec3Vector* points )
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
	void AreaSelector::drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm)
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
		glColor3f( 0.f, 0.f , 1.f );

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
	void AreaSelector::OnKeyDown( int keyCode )
	{
		if(keyCode == vgKernel::InputCode::ESCAPE)
		{
			//------------------------------------------
			// 取消当前状态
			//------------------------------------------
			// TerrainManager::getSingleton().setCutSurfaceLevellingFlag(false);
		}
	}
}