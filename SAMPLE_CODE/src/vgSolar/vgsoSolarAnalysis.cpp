


#include <vgStableHeaders.h>
#include <vgSolar/vgsoSolarAnalysis.h>
#include <vgSolar/vgsoSolarManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgSolar/vgsoSolarDirectionCalc.h>
#include <vgImage/vgiFreeImageWrapper.h>

#include <vgKernel/vgkOpenGLSupport.h>
#include <vgKernel/vgkCamMgrHolder.h>
#include <vgKernel/vgkCamMgrImpl.h>

namespace vgSolar {
	
	
	
	
	//----------------------------------------------------------------
	SolarAnalysis::SolarAnalysis( vgSolar::DateTimeAndLocation date , 
		float begin_hour , float end_hour  )
	{
		_beginHour = floor( begin_hour);
		_endHour = floor( end_hour);

		_beginMin = ( begin_hour - _beginHour ) * 60.0;
		_endMin = ( end_hour - _endHour ) * 60.0;

		_floatBuffer =NULL;
		_resultTextureID = 0;
		_calcuatedAlready = false;
		_nowLocation = date;

		SetHandleStatus( VG_INPUT_SOLAR_ANALYSIS );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_SOLAR_ANALYSIS );

		vgKernel::CamMgrHolder::getSingleton().getCamManager()->setMovingEnable( false );
		//vgCam::CamManager::getSingleton().setMovingEnable( false );

		vgKernel::SelectManager::getSingleton().setEnableRenderSelected( false );

		vgKernel::SelectManager::getSingleton().getViewSize( 
			_viewSizeWidth , _viewSizeHeight );

		_intBuffer = NULL;
	}
	//----------------------------------------------------------------
	SolarAnalysis::~SolarAnalysis()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		//vgCam::CamManager::getSingleton().setMovingEnable( true );

		vgKernel::CamMgrHolder::getSingleton().getCamManager()->setMovingEnable( true );

		if ( _resultTextureID != 0 )
		{
			glDeleteTextures( 1 , &_resultTextureID );
			_resultTextureID  = 0;
		}

		if ( _floatBuffer != NULL )
		{
			delete[] _floatBuffer;
			_floatBuffer  =NULL;
		}

		if ( _intBuffer != NULL )
		{
			delete[]  _intBuffer;
			_intBuffer =NULL;
		}
		vgKernel::SelectManager::getSingleton().setEnableRenderSelected( true );

		// Edit by KingHJ @ 2010-05-11
		//SolarManager::getSingleton().turnOffShadowEffect();
	}
	//----------------------------------------------------------------
	void SolarAnalysis::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = get3dVecFrom2d( position );
	}
	//----------------------------------------------------------------
	void SolarAnalysis::OnLButtonDown( UINT nFlags, CPoint position )
	{

	}
	//----------------------------------------------------------------
	void SolarAnalysis::OnLButtonUp( UINT nFlags, CPoint position )
	{

	}
	//----------------------------------------------------------------
	void SolarAnalysis::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		int click_x = position.x;
		int click_y = _viewSizeHeight - position.y - 1;

		assert( click_x < _viewSizeWidth );
		assert( click_y < _viewSizeHeight );

		assert( _floatBuffer != NULL );
		if ( _floatBuffer == NULL )
		{
			return;
		}

		float cur_value = _floatBuffer[ click_x + click_y * _viewSizeWidth ];

		
		//////////////////////////////////////////////////////////////////////////
		//CximageWrapper img;
		//img.createFromArray( _floatBuffer , _viewSizeWidth , _viewSizeHeight ,
		//	32 , true );

		//img.saveToFile("d:\\aaaa.bmp");


		//////////////////////////////////////////////////////////////////////////

		float step_all = (float)_lightDirs.size();


		// 每5分钟计算一次
		float all_time_in_minute = step_all * 5.0f; 

		float solar_time_in_minute = all_time_in_minute * cur_value;

		std::ostringstream o;

		char buf[1024];

		sprintf( buf, "当前时间：%s\n\n开始时刻: %d时%d分, 结束时刻:%d时%d分, 总时间:%.2f 小时.\n\n阴影时间:%.2f小时\n\n日照时间:%.2f小时",
			_nowLocation.getDateDescription().c_str(),
			_beginHour , _beginMin,
			_endHour , _endMin,
			all_time_in_minute / 60.0f , 
			solar_time_in_minute / 60.0f,
			all_time_in_minute / 60.0f - solar_time_in_minute / 60.0f );

		MessageBox( NULL , buf , "日照分析结果" , MB_OK );
		//add by KingHJ @2010-05-11 查询日照信息之后，关闭键盘和鼠标事件
		vgKernel::CamMgrHolder::getSingleton().getCamManager()->setMovingEnable( false );

		return;

//#if VGK_LANG_CHS
//
//		o << "开始时间: " << _beginHour << "点"
//			<< ", 结束时间: " << _endHour << "点"
//			<< ", 总时间: " << all_time_in_minute << "分钟, 即" << 
//			all_time_in_minute / 60.0f << "小时.\n"
//			<< "\n阴影时间: " << solar_time_in_minute << "分钟, 即" << 
//			solar_time_in_minute / 60.0f << "小时.\n"
//			<< "\n日照时间: " << all_time_in_minute - solar_time_in_minute << "分钟, 即" << 
//			(all_time_in_minute - solar_time_in_minute) / 60.0f << "小时.\n";
//		MessageBox( NULL , o.str().c_str() , "日照分析" , MB_OK );
//#else
//		o << "总时间: " << 	all_time_in_minute / 60.0f << " Hours.\n"
//			<< "日照时间: " solar_time_in_minute / 60.0f << " Hours.\n";
//		MessageBox( NULL , o.str().c_str() , "Solar Analysis" , MB_OK );
//#endif

	}
	//----------------------------------------------------------------
	void SolarAnalysis::render()
	{	
		int tmpwidth;
		int tmpheight;

		vgKernel::SelectManager::getSingleton().getViewSize( tmpwidth , tmpheight );

		if ( tmpwidth != _viewSizeWidth ||
			tmpheight != _viewSizeHeight )
		{
			//invalidate();
#if VGK_LANG_CHS
			VGK_SHOW( "视窗改变,自动退出日照分析." );
#else
			VGK_SHOW( "Window changed, quit solar analysis." );
#endif
			
			_viewSizeWidth = tmpwidth;
			_viewSizeHeight = tmpheight;
			SolarManager::getSingleton().setSolarAnalysis( false );
			return;
		}

		if ( _viewSizeWidth == 0 ||
			_viewSizeHeight == 0 )
		{
			return;
		}

		if ( _calcuatedAlready == true )
		{
			renderResults();
		}
		else
		{
			calcuateOnce();
		}

		drawPoint( _mouseVec );
	}
	//----------------------------------------------------------------
	void SolarAnalysis::calcuateOnce()
	{
		//------------------------------------------
		// 首先计算光线各个角度
		//------------------------------------------
		if ( _lightDirs.empty() )
		{
			makeLightDirections();
			assert( _lightDirs.empty() == false );
		}

		if ( _lightDirs.empty() )
		{
			_calcuatedAlready = true;
			return;
		}

		assert( _floatBuffer == NULL );
		assert( _resultTextureID == 0 );


		vgKernel::RendererQueue* selected = &vgKernel::SelectManager::getSingleton().getSelectedItems();


		SolarManager::getSingleton().turnOnShadowEffect( 
			selected , NULL , true );



		GLint viewport[4];
		glGetIntegerv (GL_VIEWPORT, viewport); 

		int width = viewport[2] - viewport[0];
		int height = viewport[3] - viewport[1];

		assert( width > 0 );
		assert( height > 0 );
		assert( width == _viewSizeWidth );
		assert( height == _viewSizeHeight );

		// 最终存储的目标地
		uchar* texture_buffer = new uchar[ width * height * 4 ];
		memset( texture_buffer, 0 , width * height * 4 );
		
		// 中间的临时文件
		float* float_buf = new float[ width * height ];
		memset( float_buf , 0 , width * height * 4);
		_floatBuffer = float_buf;

		if ( _intBuffer != NULL )
		{
			delete[] _intBuffer;
			 _intBuffer =NULL;
		}

		// 每次读取的缓存
		_intBuffer = new int[ width * height ];
		memset( _intBuffer , 0 , width * height * sizeof( int ) );
		
		//------------------------------------------
		// 开始遍历每一个光线角度
		//------------------------------------------
		Vec3Vector::iterator iter = _lightDirs.begin();
		Vec3Vector::iterator iter_end = _lightDirs.end();

		float step = 1.0f / (float)_lightDirs.size();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::Vec3 dir = *iter;

			if ( dir.squaredLength() <= 0.0f )
			{
				//------------------------------------------
				// 这个时候太阳还没出，全是黑色的，应该都加一个值。
				//------------------------------------------
				for ( int x = 0 ; x < width ; ++ x )
				{
					for ( int y = 0; y < height ; ++ y )
					{
						float_buf[ x + width * y ] += step;
					}
				}
			}
			else
			{
				SolarManager::getSingleton().changeLightDirection( dir );

				// 开始利用stencil buffer来读
				clearStencilAndRenderOnce();

				glReadPixels(  0 , 0 , width , height , 
					GL_STENCIL_INDEX , GL_INT , _intBuffer );
				glFlush();
				glFinish();

				for ( int x = 0 ; x < width ; ++ x )
				{
					for ( int y = 0; y < height ; ++ y )
					{
						if ( _intBuffer[ x + width * y ] >0 )
						{
							float_buf[ x + width * y ] += step;
						}
					}
				}
			}// end of else
		}



		//------------------------------------------
		// 从float缓冲区折算到RGBA缓冲区
		//------------------------------------------
		for ( int x = 0 ; x < width ; ++ x )
		{
			for ( int y = 0; y < height ; ++ y )
			{
				//float_buf[ x + width * y ] += step;
			
				if ( float_buf[ x + width * y ] > 0.0f )
				{
					texture_buffer[ 4 * x + 4 * width * y ] = 255;		//R

					//int ddd = float_buf[ x + width * y ] * 255;

					texture_buffer[ 4 * x + 4 * width * y + 1 ] =
						255 - float_buf[ x + width * y ] * 255;	//G

					//texture_buffer[ 4 * x + 4 * width * y + 2 ] =
					//	float_buf[ x + width * y ] * 255;	//B

					texture_buffer[ 4 * x + 4 * width * y + 3 ] = 255;	//A
				}

			}
		}

		//------------------------------------------
		// 开始创建纹理
		//------------------------------------------
		glGenTextures(1, &_resultTextureID);

		glBindTexture(GL_TEXTURE_2D, _resultTextureID );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, texture_buffer );



		//////////////////////////////////////////////////////////////////////////
		//FreeImageWrapper img;
		//img.createFromArray( texture_buffer , width , height ,
		//	32 );

		//img.saveToFile("d:\\aaaa.bmp");



		//------------------------------------------
		// 清除临时数据
		//------------------------------------------
		delete[] texture_buffer;
		

		_calcuatedAlready = true;
	}
	//----------------------------------------------------------------
	void SolarAnalysis::renderResults()
	{
		VGK_CHECK_OPENGL_ERROR();

		glDisable( GL_STENCIL_TEST );


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
		glDisable( GL_BLEND );
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5f);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);


		glColor4f( 1,1,1 , 1 );

		//obs->useBind();
		glBindTexture( GL_TEXTURE_2D , _resultTextureID );

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

		VGK_CHECK_OPENGL_ERROR();

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

		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
		glDisable( GL_ALPHA_TEST );

		VGK_CHECK_OPENGL_ERROR();
	}
	//----------------------------------------------------------------
	void SolarAnalysis::clearStencilAndRenderOnce()
	{
		glClear(GL_STENCIL_BUFFER_BIT);

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );

		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_STENCIL_TEST);
		glColorMask(0, 0, 0, 0);
		glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

		// first pass, stencil operation decreases stencil value
		glFrontFace(GL_CCW);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

		// render 
		SolarManager::getSingleton().renderShadowCastObjects();

		//second pass, stencil operation increases stencil value
		glFrontFace(GL_CW);
		glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);

		// render 
		SolarManager::getSingleton().renderShadowCastObjects();


		glFrontFace(GL_CCW);
		glColorMask(1, 1, 1, 1);

		//draw a shadowing rectangle covering the entire screen

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	}
	//----------------------------------------------------------------
	void SolarAnalysis::makeLightDirections()
	{
		assert( _lightDirs.empty() == true );

		// 先测试早上8点到晚上17点。
		int begin_hour = _beginHour;
		int end_hour = _endHour;

		//------------------------------------------
		// 每5分钟计算一次
		//------------------------------------------
		DateTimeAndLocation tmp = _nowLocation;

		for ( int i = begin_hour ; i <= end_hour ; ++ i )
		{
			tmp.setHour( i );

			int j = 0;
			if ( i == begin_hour )
			{
				j = _beginMin / 5;
			}
			int j_end = 60 / 5;
			if ( i == end_hour )
			{
				j_end = _endMin / 5;
			}
			for ( ; j < j_end ; ++ j )
			{
				tmp.setMinute( j * 5 );

				SolarDirectionCalc cal( &tmp );
				vgKernel::Vec3* dir = cal.getSolarDirection();

				if ( dir == NULL )
				{
					_lightDirs.push_back( vgKernel::Vec3() );
				}
				else
				{
					_lightDirs.push_back( vgKernel::Vec3(*dir) );
					delete dir;
				}
			}
		}

		return;
	}
	//----------------------------------------------------------------
	vgKernel::Vec3 SolarAnalysis::get3dVecFrom2d( const CPoint& point_2d )
	{
		vgKernel::Vec3 ret;

		glPushMatrix();

		int ViewPort[4],winy;
		GLdouble ModelView[16];
		GLdouble Projection[16];
		GLfloat winx,winz;
		GLdouble vrx,vry, vrz;

		glGetIntegerv(GL_VIEWPORT,ViewPort);

		//assert( ( ViewPort[2] - ViewPort[0]) == _viewSizeWidth );
		//assert( ( ViewPort[3] - ViewPort[1]) == _viewSizeHeight );

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
	void SolarAnalysis::drawPoint( const vgKernel::Vec3& point )
	{
		glDisable( GL_DEPTH_TEST );


		glDisable( GL_TEXTURE_2D );

		glColor3f( 0.0f , 0.5f ,  1.0f );
		glPointSize( 10.0f );

		glPushMatrix();

		glBegin( GL_POINTS );
		glVertex3fv( point.v );
		glEnd();

		glPopMatrix();

		glEnable( GL_DEPTH_TEST );
	}
	//----------------------------------------------------------------
	void SolarAnalysis::invalidate()
	{
		if ( _resultTextureID != 0 )
		{
			glDeleteTextures( 1 , &_resultTextureID );
			_resultTextureID  = 0;
		}

		if ( _floatBuffer != NULL )
		{
			delete[] _floatBuffer;
			_floatBuffer = NULL;
		}
		_calcuatedAlready = false;

		_lightDirs.clear();
	}
	//----------------------------------------------------------------



}// end of namespace vgSolar
