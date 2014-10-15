



#include <vgStableHeaders.h>
#include <vgSolar/vgsoSolarManager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkShadowCastObject.h>

//#include <vgImage/vgiCximageWrapper.h>
//#include <vgImage/vgiTextureManager.h>
//#include <vgImage/vgiTextureObserver.h>


#include <vgSolar/vgsoSolarDirectionCalc.h>

#include <vgSolar/vgsoDefinition.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgSolar/SolarAnalysis.h>
#include <vgKernel/vgkDynamicLibraryUtility.h>
#include <vgKernel/vgkCamMgrHolder.h>
#include <vgKernel/vgkCamMgrImpl.h>



VGK_DLL_RES_DECLARE();


namespace vgSolar {
	


	/**
		在这里创建project config
	*/
	vgConf::ProjectConfigRegProxy shadow_project_reg1( 
		VGSO_NAME , VGSO_SHADOW_ENABLE , VGSO_SHADOW_ENABLE_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy shadow_project_reg2( 
		VGSO_NAME , VGSO_USECOMPUTERDATE , VGSO_USECOMPUTERDATE_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy shadow_project_reg3( 
		VGSO_NAME , VGSO_CURRENTYEAR , VGSO_CURRENTYEAR_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy shadow_project_reg4( 
		VGSO_NAME , VGSO_CURRENTMONTH , VGSO_CURRENTMONTH_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy shadow_project_reg5( 
		VGSO_NAME , VGSO_CURRENTDAY , VGSO_CURRENTDAY_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy shadow_project_reg6( 
		VGSO_NAME , VGSO_CURRENTHOUR , VGSO_CURRENTHOUR_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy shadow_project_reg7( 
		VGSO_NAME , VGSO_CURRENTMINUTE , VGSO_CURRENTMINUTE_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy shadow_project_reg8( 
		VGSO_NAME , VGSO_CURRENTLATITUDE , VGSO_CURRENTLATITUDE_DEFAULT_STR );



	
	
	//----------------------------------------------------------------
	void SolarManager::renderEnd()
	{
		if ( _analysis != NULL )
		{
			_analysis->render();
		}

		if ( _shadowEnabled == false )
		{
			return;
		}


		//using namespace vgSolar;

		//SolarDirectionCalc sunangle;
		//sunangle.SetDate( 1996 , 12, 1);
		//sunangle.SetTime(12, 0);
		//sunangle.SetLat( 36 );
		//float hh=sunangle.GetHeightOfSun();

		//float nowtime= 12+0/60;
		//float t=(nowtime-12)/12*3.14159265;//化为弧度的时角

		//vgKernel::Vec3 sun;
		//if( hh <= 0.0f )//太阳没出的话按照-1计算！
		//{
		//	sun.x=-cos(hh)*sin(t);
		//	sun.y=-sin(hh);
		//	sun.z=cos(hh)*cos(t);
		//}

		//sun.normalise();

		//static bool zz=true;
		//if ( zz == true )
		//{
		//	zz = false;
		//	changeLightDirection( sun );
		//}


		if ( _shadowedObjects.empty() )
		{
			return;
		}

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );

		glClear(GL_STENCIL_BUFFER_BIT);


		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_STENCIL_TEST);
		glColorMask(0, 0, 0, 0);
		glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

		// first pass, stencil operation decreases stencil value
		glFrontFace(GL_CCW);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

		//if (SunDirChanged())


		//{
		//	b_updatashadows = true;
		//	SunDirUpdata();
		//}
		//DrawShadowsWithTree(rootnode);
		//drawRendererShadow();//zhu 2009-1-16

		//b_updatashadows = false;



		// 开始渲染阴影体
		renderShadowCastObjects();




		//second pass, stencil operation increases stencil value
		glFrontFace(GL_CW);
		glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);




		//DrawShadowsWithTree(rootnode);
		//drawRendererShadow();//zhu 2009-1-16

		// 开始渲染阴影体
		renderShadowCastObjects();



		glFrontFace(GL_CCW);
		glColorMask(1, 1, 1, 1);

		//draw a shadowing rectangle covering the entire screen

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glPushMatrix();
		glLoadIdentity();


		//////////////////////////////////////////////////////////////////////////

#if 0

		using namespace vgImage;

		TextureObserver* obs = 
			TextureManager::getSingleton().getTextureObserver( "b0001074.dds" ,
			VGLOD_CLEAR );

		if ( obs != NULL )
		{
#if 0
			glDisable( GL_CULL_FACE );
			glEnable( GL_BLEND );
			glEnable(GL_TEXTURE_2D);
			glColor4f( 1,1,1 , 0.5f );
			obs->useBind();

			int logolength = 50;
			int logowidth = 30;

			glBegin( GL_POLYGON );   
			glTexCoord2i(0,0);
			glVertex3f((-1) *logolength,(-1) * logowidth,0.0);
			//glVertex3f(-50,-50,-20);
			glTexCoord2i(0,1);
			glVertex3f((-1) *logolength,logowidth,0.0);
			//glVertex3f(-50, 50,-20);

			glTexCoord2i(1,1);
			glVertex3f(logolength,logowidth,0.0);
			//glVertex3f( 50, 50,-20);
			glTexCoord2i(1,0);
			glVertex3f(logolength,(-1) * logowidth,0.0);
			//glVertex3f( 50,-50,-20);
			glEnd();
#endif

			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();

			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();

			float t_begin_x = - 1.0f;
			float t_begin_y =  - 1.0f;

			float t_end_x = 1.0f;
			float t_end_y =  1.0f;

			glDisable( GL_CULL_FACE );
			glEnable( GL_BLEND );
			glEnable(GL_TEXTURE_2D);
			glColor4f( 1,1,1 , 0.5f );
			obs->useBind();

			//------------------------------------------
			// 画线
			//------------------------------------------

				//glBegin(GL_LINE_LOOP);
				//{
				//	glVertex2f( t_begin_x, t_begin_y );
				//	glVertex2f( t_begin_x, t_end_y );
				//	glVertex2f( t_end_x, t_end_y );
				//	glVertex2f( t_end_x , t_begin_y );
				//}
				//glEnd();

				glBegin( GL_POLYGON );   
				{
					glTexCoord2i(0,0);
					glVertex2f( t_begin_x, t_begin_y );
					glTexCoord2i(0,1);
					glVertex2f( t_begin_x, t_end_y );
					glTexCoord2i(1,1);
					glVertex2f( t_end_x, t_end_y );
					glTexCoord2i(1,0);
					glVertex2f( t_end_x , t_begin_y );
				}

				//glTexCoord2i(0,0);
				//glVertex3f((-1) *logolength,(-1) * logowidth,0.0);
				////glVertex3f(-50,-50,-20);
				//glTexCoord2i(0,1);
				//glVertex3f((-1) *logolength,logowidth,0.0);
				////glVertex3f(-50, 50,-20);

				//glTexCoord2i(1,1);
				//glVertex3f(logolength,logowidth,0.0);
				////glVertex3f( 50, 50,-20);
				//glTexCoord2i(1,0);
				//glVertex3f(logolength,(-1) * logowidth,0.0);
				////glVertex3f( 50,-50,-20);
				glEnd();


			glMatrixMode( GL_PROJECTION );
			glPopMatrix();

			glMatrixMode( GL_MODELVIEW );
			glPopMatrix();

		}
		else
		{
			glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
			glBegin(GL_TRIANGLE_STRIP);
			{
				glVertex3f(-50, 50,-20);
				glVertex3f(-50,-50,-20);
				glVertex3f( 50, 50,-20);
				glVertex3f( 50,-50,-20);
			}
			glEnd();
		}

#else

			glDisable( GL_TEXTURE_2D );
			glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
			glBegin(GL_TRIANGLE_STRIP);
			{
				glVertex3f(-50, 50,-20);
				glVertex3f(-50,-50,-20);
				glVertex3f( 50, 50,-20);
				glVertex3f( 50,-50,-20);
			}
			glEnd();

#endif












		glPopMatrix();
		glDisable(GL_BLEND);

		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		//glEnable(GL_LIGHTING);
		glDisable( GL_CULL_FACE );
		glDisable(GL_STENCIL_TEST);
		glShadeModel(GL_SMOOTH);


		//////////////////////////////////////////////////////////////////////////


#if 0

		static bool aa=true;

		if ( aa == true )
		{
			aa= false;

			GLint viewport[4];
			glGetIntegerv (GL_VIEWPORT, viewport); 

			int width = viewport[2] - viewport[0];
			int height = viewport[3] - viewport[1];

			float* buf = new float[ width * height ];
			memset( buf , 0 , width * height * sizeof( float ) );

			glReadPixels(  0 , 0 , width , height , 
				GL_STENCIL_INDEX , GL_FLOAT , buf );

			for ( int i = 0 ; i < width ; ++ i )
			{
				for ( int j = 0 ; j < height ; ++ j )
				{
					float ee = buf[ i * width + j ];

					ee = ee;

					if ( ee != 0.0f )
					{
						int sdfasdf = 4243;
					}
				}
			}
			
			using namespace vgImage;

			CximageWrapper img;
			img.createFromArray( buf , width , height , 32 );

			img.saveToFile( "d:\\aaa.bmp" );

		}

#endif



		return;
	}
	//----------------------------------------------------------------
	void SolarManager::renderShadowCastObjects()
	{
		using namespace vgKernel;
#if 0
		RendererPackage::iterator iter = pac->begin();
		RendererPackage::iterator iter_end = pac->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			RendererQueue* qu = iter->second;

			if ( qu->empty() )
			{
				continue;
			}

			Renderer* ren = *qu->begin();

			ShadowCastObject* swobj = dynamic_cast< ShadowCastObject*>( ren );
			if( swobj != NULL )
			{
				RendererQueue::iterator i = qu->begin();
				RendererQueue::iterator i_end = qu->end();

				for ( ; i != i_end ; ++ i )
				{
					swobj = dynamic_cast< ShadowCastObject*>( *i );
					assert( swobj != NULL );

					swobj->renderInShadowMode();
				}
			}
		}
#else

		ShadowCastObjectVec::iterator iter = _shadowedObjects.begin();
		ShadowCastObjectVec::iterator iter_end = _shadowedObjects.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->renderInShadowMode();
		}


#endif



		return;
	}
	//----------------------------------------------------------------
	bool SolarManager::turnOnShadowEffect( 
		vgKernel::RendererQueue* renderer_queue ,
		vgKernel::Vec3* new_light_dir ,
		bool force_to_load )
	{
		using namespace vgKernel;
		if ( new_light_dir == NULL )
		{
			new_light_dir = &_lightDir;
		}

		if( _shadowEnabled == true )
		{
			changeLightDirection( *new_light_dir );
			return true;
		}

		// 置标记位
		_shadowEnabled = true;
		_lightDir = *new_light_dir;


		assert( _shadowedObjects.empty() == true );

		if ( renderer_queue == NULL || renderer_queue->empty() )
		{
			return false;
		}


		vgKernel::ShadowCastObject* swobj = NULL;

		vgKernel::RendererQueue::iterator iter = renderer_queue->begin();
		vgKernel::RendererQueue::iterator iter_end = renderer_queue->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::Renderer* ren = *iter;
			swobj = dynamic_cast<ShadowCastObject *>( ren );

			if( swobj != NULL )
			{
				_shadowedObjects.push_back( swobj );
			}
		}

		if ( _shadowedObjects.empty() )
		{
			return false;
		}

		// 开始通知所有的物体进行开启
		{
			ShadowCastObjectVec::iterator iter = _shadowedObjects.begin();
			ShadowCastObjectVec::iterator iter_end = _shadowedObjects.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->turnOnShadowCast( *new_light_dir , force_to_load );
			}
		}



		return true;
	}
	//----------------------------------------------------------------
	bool SolarManager::turnOffShadowEffect()
	{
		using namespace vgKernel;
		if ( _shadowEnabled == false )
		{
			return true;
		}

		// 这个时候需要通知注册的物体进行卸载。

		ShadowCastObjectVec::iterator iter = _shadowedObjects.begin();
		ShadowCastObjectVec::iterator iter_end = _shadowedObjects.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->turnOffShadowCast();
		}

		_shadowedObjects.clear();
		_shadowEnabled = false;

		return true;
	}
	//----------------------------------------------------------------
	bool SolarManager::changeLightDirection(
		const vgKernel::Vec3& new_light_dir )
	{
		if ( new_light_dir.length() == 0 )
		{
			return false;
		}

		if ( _shadowEnabled == false )
		{
			return false;
		}

		if ( new_light_dir == _lightDir )
		{
			return true;
		}

		// 这个时候需要通知注册的物体进行update

		ShadowCastObjectVec::iterator iter = _shadowedObjects.begin();
		ShadowCastObjectVec::iterator iter_end = _shadowedObjects.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->onLightDirectionChanged( new_light_dir );
		}

		_lightDir = new_light_dir;

		return true;
	}
	//----------------------------------------------------------------
	void SolarManager::uninitBeforeOpenGLDestroy()
	{
		// Edit by KingHJ @ 2010-05-11
		//turnOffShadowEffect();
	}
	//----------------------------------------------------------------
	void SolarManager::readProject()
	{
		_shadowEnabled = VG_PROJCONF_GET_BOOL( VGSO_NAME , 
			VGSO_SHADOW_ENABLE );

		_useComputerDateAndTime = VG_PROJCONF_GET_BOOL( VGSO_NAME , 
			VGSO_USECOMPUTERDATE );

		_currentDateAndTime.setYear( VG_PROJCONF_GET_INT( VGSO_NAME , 
			VGSO_CURRENTYEAR )	);

		_currentDateAndTime.setMonth( VG_PROJCONF_GET_INT( VGSO_NAME , 
			VGSO_CURRENTMONTH )	);

		_currentDateAndTime.setDay( VG_PROJCONF_GET_INT( VGSO_NAME , 
			VGSO_CURRENTDAY )	);

		_currentDateAndTime.setHour( VG_PROJCONF_GET_INT( VGSO_NAME , 
			VGSO_CURRENTHOUR )	);

		_currentDateAndTime.setMinute( VG_PROJCONF_GET_INT( VGSO_NAME , 
			VGSO_CURRENTMINUTE )	);

		_currentDateAndTime.setLatitude( VG_PROJCONF_GET_FLOAT( VGSO_NAME , 
			VGSO_CURRENTLATITUDE )	);

		SolarDirectionCalc calc( &_currentDateAndTime );

		vgKernel::Vec3* dir = calc.getSolarDirection();

		if ( dir != NULL )
		{
			_lightDir = *dir;
			delete dir;
		}
		

		// 这里默认的不打开
		_shadowEnabled = false;
	}
	//----------------------------------------------------------------
	void SolarManager::saveProject()
	{
		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_SHADOW_ENABLE , _shadowEnabled );

		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_USECOMPUTERDATE , _useComputerDateAndTime );

		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_CURRENTYEAR , _currentDateAndTime.getYear() );

		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_CURRENTMONTH , _currentDateAndTime.getMonth() );

		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_CURRENTDAY , _currentDateAndTime.getDay() );

		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_CURRENTHOUR , _currentDateAndTime.getHour() );

		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_CURRENTMINUTE , _currentDateAndTime.getMinute() );

		VG_PROJCONF_SET( VGSO_NAME , 
			VGSO_CURRENTLATITUDE , _currentDateAndTime.getLatitude() );

	}
	//----------------------------------------------------------------
	bool SolarManager::turnOnShadowEffectWithDate(
		vgKernel::RendererQueue* renderer_queue , 
		vgSolar::DateTimeAndLocation* date_loc ,
		bool force_to_load )
	{

		vgKernel::Vec3 new_light_dir;

		SolarDirectionCalc calc( date_loc );

		vgKernel::Vec3* tmpdir = calc.getSolarDirection();

		if ( tmpdir == NULL )
		{
			turnOffShadowEffect();
			return false;
		}

		new_light_dir = *tmpdir;
		delete tmpdir;

		if( _shadowEnabled == true )
		{
			changeLightDirection( new_light_dir );
			return true;
		}

		assert( _shadowedObjects.empty() == true );

		if ( renderer_queue == NULL || renderer_queue->empty() )
		{
			return false;
		}

		vgKernel::ShadowCastObject* swobj = NULL;

		vgKernel::RendererQueue::iterator iter = renderer_queue->begin();
		vgKernel::RendererQueue::iterator iter_end = renderer_queue->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::Renderer* ren = *iter;
			swobj = dynamic_cast<ShadowCastObject *>( ren );

			if( swobj != NULL )
			{
				_shadowedObjects.push_back( swobj );
			}
		}

		if ( _shadowedObjects.empty() )
		{
			return false;
		}

		// 开始通知所有的物体进行开启
		{
			ShadowCastObjectVec::iterator iter = _shadowedObjects.begin();
			ShadowCastObjectVec::iterator iter_end = _shadowedObjects.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->turnOnShadowCast( new_light_dir , force_to_load );
			}
		}

		// 置标记位
		_shadowEnabled = true;
		_lightDir = new_light_dir;

		return true;
	}
	//----------------------------------------------------------------
	bool SolarManager::changeDateTimeAndLoc( DateTimeAndLocation* loc )
	{
		SolarDirectionCalc sunangle( loc );

		vgKernel::Vec3* solardir = sunangle.getSolarDirection();

		if ( solardir == NULL )
		{
			return false;
		}
		else
		{
			changeLightDirection(
				*solardir );

			_currentDateAndTime = *loc;

			delete solardir;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool SolarManager::setSolarAnalysis( bool enable_it  )
	{
		VGK_DLL_RES_SWITCH();

		if ( _analysis != NULL )
		{
			delete _analysis;
			_analysis = NULL;
		}

		if ( enable_it == true )
		{
			vgKernel::CamMgrHolder::getSingleton().getCamManager()->setMovingEnable( false );
			//vgCam::CamManager::getSingleton().setMovingEnable( false );
			CSolarAnalysis dlg( &_currentDateAndTime );
			if ( dlg.DoModal() == IDOK )
			{
				_currentDateAndTime = dlg.getTimeAndLoc();
				_analysis = new SolarAnalysis( dlg.getTimeAndLoc() ,
					dlg.getHourBegin() , dlg.getHourEnd() );
			}
			else
			{
				vgKernel::CamMgrHolder::getSingleton().getCamManager()->setMovingEnable( true );
				//vgCam::CamManager::getSingleton().setMovingEnable( true );
			}
		}
		else
		{
			// Edit by KingHJ @ 2010-05-11
			turnOffShadowEffect();
		}

		return true;
	}
	//----------------------------------------------------------------

	
}// end of namespace vgSolar
