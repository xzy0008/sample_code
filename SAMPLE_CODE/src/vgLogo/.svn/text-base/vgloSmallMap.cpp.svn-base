// SmallMapLogo.cpp: implementation of the SmallMapLogo class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>

#include <vglogo/vgloSmallMap.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgKernel/vgkBox.h>
#include <vgImage/vgiFreeImageWrapper.h>
#include <vgCam/vgcaCamManager.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgkernel/vgkOpenGLSupport.h>

#define  SMALLMAP_PATH "E:\\_HawkeyeImage.tga"
#define  SMALLMAP_FILE_NAME "_HawkeyeImage.tga"

#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

#define  SAMLLMAPLOGOWIDTH 0.5
#define  CAM_HEIGHT 150

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace vgLogo
{
//-------------------------------------------------------------------------------------
	SmallMapLogo::SmallMapLogo()
	{
		imageData = NULL;

		m_FrustumAngle = 60.0;

		m_transparency = 120;

		int viewport[4];

		glGetIntegerv( GL_VIEWPORT, viewport );

		m_viewWidth = viewport[2];
		m_viewHeight = viewport[3];

		m_textureID = NULL;

		m_currentTexID = -1;

		radio = 1.0;

		xlengthIn3dscene = 0;	
		ylengthIn3dscene = 0;
		xcenterIn3dscene = 0;
		ycenterIn3dscene = 0;
		m_sceneradiomapx = 0;	
		m_sceneradiomapy = 0;
		m_currentpointx = 0;
		m_currentpointy = 0;

		m_mousepointx = 0;

		m_mousepointy = 0;

		zcenterIn3dscene = 0;

		b_hasscenedata = false;

		b_initialized = false;

		setRenderState( false );

		SetHandleStatus( VG_SAMLL_MAP_LOGO );
		vgKernel::InputSystem::getSingleton().registerHandle(this);
// 		vgKernel::InputSystem::getSingleton().setCurrentStatus( VG_SAMLL_MAP_LOGO | 
// 			VG_INPUTMODE_CAMERA | VG_INPUTMODE_SELECT | VG_INPUTMODE_UI );
	}
//---------------------------------------------------------------------------------------
	SmallMapLogo::~SmallMapLogo()
	{
		if ( imageData != NULL )
		{
			delete[] imageData;

			imageData = NULL;
		}
	}

//-----------------------------------------------------------------------------------------
	void SmallMapLogo::DrawSmallmap( float camerax,float cameraz )
	{
		if ( !b_hasscenedata)
		{
			initscenedata();
		}

		if ( !getRenderState() )
		{
			return;
		}
		else
		{
			if ( m_texNameIDMap.size() == 0 )
			{
				return;
			}

			map<string, GLuint>::iterator _iter = m_texNameIDMap.begin();

			GLuint _textureID = _iter->second;

			recalculate();

			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();

			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

			glPushMatrix();

			glTranslatef( getCenterPos()->x, getCenterPos()->y, 0);       //中心点的位置

			glEnable(GL_TEXTURE_2D);

			glColor3f(1,1,1);
			assert( m_textureID != NULL );
			glBindTexture( GL_TEXTURE_2D, m_textureID[_textureID] );

			float halfHeight = m_logoHeight / 2.0;
			float halfWidth = m_logoWidth / 2.0;

			glBegin(GL_POLYGON);   
			glTexCoord2i( 0, 0 );
			glVertex3f( (-1) * halfWidth ,(-1) * halfHeight, 0.0 );
			glTexCoord2i( 0, 1 );
			glVertex3f( (-1) * halfWidth, halfHeight,0.0 );
			glTexCoord2i( 1, 1 );
			glVertex3f( halfWidth, halfHeight, 0.0 );
			glTexCoord2i( 1, 0 );
			glVertex3f( halfWidth, (-1) * halfHeight, 0.0 );
			glEnd();

			glDisable(GL_TEXTURE_2D);
			calculatecurrentpoint();

			if ((camerax >= xcenterIn3dscene - xlengthIn3dscene /2) && (camerax <= xcenterIn3dscene + xlengthIn3dscene /2)
	 				&& (cameraz >= ycenterIn3dscene - ylengthIn3dscene / 2) && (cameraz <= ycenterIn3dscene + ylengthIn3dscene / 2))
	 		{
 				glPushMatrix();
 				glColor3f(1.0,0.0,0.0);
 				glPointSize(4.0);
 
 				glTranslatef(m_currentpointx,m_currentpointy,0);
 
 				glBegin(GL_POINTS);
 				glVertex3f(0,0,0);
 				glEnd();
 				glPointSize(1.0);

 				glPopMatrix();
			}

			glPopMatrix();

			glEnable(GL_DEPTH_TEST);

			glDisable(GL_BLEND);

			if ( Isinsmallmapregion( m_mousepointx, m_mousepointy) )
			{
				glPushMatrix();

				glColor3f(0.0,1.0,0.0);
				glPointSize(4.0);

				glTranslatef(m_mousepointx,m_mousepointy,0);

				glBegin(GL_POINTS);
				glVertex3f(0,0,0);
				glEnd();
				glPointSize(1.0);

				glPopMatrix();
			}



			glLineWidth(1.0);
			glMatrixMode( GL_PROJECTION );
			glPopMatrix();

			glMatrixMode( GL_MODELVIEW );
			glPopMatrix();

			////////////////////////////////////////////////////////////////////////
		}
	}
//--------------------------------------------------------------------------------------
	void SmallMapLogo::OutPutSmallmapImage( string _filepath )
	{
		int viewport[4];

		glGetIntegerv(GL_VIEWPORT,viewport);

		CaptureGLBufferToBMP(_filepath,viewport[0],viewport[1],
			viewport[2],viewport[3]);
	}
//-----------------------------------------------------------------------------
	bool SmallMapLogo::CaptureGLBufferToBMP(String filename,
		int x, int y,int width, int height)
	{

		imageData = new char[width*height*4];		// allocate memory for the imageData

		memset(imageData, 0, width*height*4);	// clear imageData memory contents

		// read the image data from the window
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		vgImage::FreeImageWrapper img;

		for (int i =0 ; i < width * height; i++)
		{
			char data = imageData[i*4];
			imageData[i*4] = imageData[i*4 + 2];
			imageData[i * 4 + 2] = data;
			imageData[i * 4 + 3] = m_transparency;//半透明
		}

		img.createFromArray( (unsigned char*)imageData , 
			width , height , 32 , false );

		img.saveToFile(filename);

		delete[] imageData;

		imageData = NULL;

		return true;
	}
//---------------------------------------------------------------------------------

	void SmallMapLogo::changesceneposition( float _x, float _y )
	{
		m_currentpointx  = _x - getCenterPos()->x;

		m_currentpointy = _y - getCenterPos()->y;

		float scenex = m_currentpointx * m_sceneradiomapx + xcenterIn3dscene;

		float sceney = ycenterIn3dscene - m_currentpointy * m_sceneradiomapy;

		vgKernel::Vec3 _vec(scenex, zcenterIn3dscene, sceney );

		vgCam::CamManager::getSingleton().setCurrentPosition( _vec );
	}

//---------------------------------------------------------------------------------
	void SmallMapLogo::calculatecurrentpoint()
	{
		vgKernel::Vec3  campos = 
			vgCam::CamManager::getSingleton().getCurrentPosition();

		if ( m_sceneradiomapx != 0 && m_sceneradiomapy != 0 )
		{
			m_currentpointx = (campos.x - xcenterIn3dscene) / m_sceneradiomapx;

			m_currentpointy = (ycenterIn3dscene - campos.z) / m_sceneradiomapy;
		}
	}

//----------------------------------------------------------------------------------
	void SmallMapLogo::OutPutHawkeyeMapInSky( string _filepath )
	{
		float length,width;

		double	g_eye[3];		

		double	g_look[3];		

		vgKernel::Box	_box  = 
			vgKernel::RendererManager::getSingleton().getAllRendererBoxWithoutshp();

		length = _box._maxVertex.x - _box._minVertex.x;

		width = _box._maxVertex.z - _box._minVertex.z; 

		m_lengthradiowidth = length / width;

		xlengthIn3dscene = length;

		ylengthIn3dscene = width;

		xcenterIn3dscene = _box.getCenter().x;

		ycenterIn3dscene = _box.getCenter().z;
		
		zcenterIn3dscene = CAM_HEIGHT;

		g_look[0] = xcenterIn3dscene;

		g_look[1] = _box.getCenter().y;

		g_look[2] = ycenterIn3dscene;

		g_eye[0] = xcenterIn3dscene;

		g_eye[1] = g_look[1] +3000;             

		g_eye[2] = ycenterIn3dscene;

		{

			glClear(GL_COLOR_BUFFER_BIT);

			GLfloat PerModelMatrix[16];

			glMatrixMode( GL_MODELVIEW );

			glGetFloatv(GL_MODELVIEW_MATRIX, PerModelMatrix);

			glLoadIdentity();

			gluLookAt(g_eye[0],g_eye[1],g_eye[2],g_look[0],g_look[1],g_look[2],0.0,0.0,-1.0);

			GLfloat PerSpecMatrix[16];

			glGetFloatv(GL_PROJECTION_MATRIX, PerSpecMatrix);

			glMatrixMode(GL_PROJECTION);

			glLoadIdentity();

			glOrtho(-length/2,length/2,-width/2,width/2,1,10000);  //人为扩大了区域

			vgCam::CamManager::getSingleton().updateCurrentFrustum();

			vgKernel::RendererManager::getSingleton().renderBegin();

			vgMesh::MeshManager::getSingleton().render();

			OutPutSmallmapImage(  _filepath );

			glMatrixMode(GL_PROJECTION);

			glLoadIdentity();

			glMultMatrixf(PerSpecMatrix);

			glMatrixMode( GL_MODELVIEW );

			glLoadIdentity();

			glMultMatrixf(PerModelMatrix);

			glClear( GL_COLOR_BUFFER_BIT );

		}

	}
//--------------------------------------------------------------------------------------
	void SmallMapLogo::render()
	{
		glDisable( GL_DEPTH_TEST );

		vgKernel::Vec3 _campos = 
 			vgCam::CamManager::getSingleton().getCurrentPosition();

		DrawSmallmap( _campos.x , _campos.z );

		glEnable( GL_DEPTH_TEST );
	}

//---------------------------------------------------------------------------------
	void SmallMapLogo::loadTexture( vgKernel::StringVector fileNames )
	{
		int fileNums = fileNames.size();

		//先释放初始化时分配的内存
		if ( fileNums > 1 && m_textureID != NULL )
		{
			delete[] m_textureID;
			m_textureID = new GLuint[fileNums];
		}

		String exepath = vgKernel::SystemUtility::getCurrentProcessPath();

		String texturePath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_TEXTURE_PATH);

		for ( int i = 0; i < fileNums; i++ )
		{
			String logopath = exepath + texturePath + fileNames[i];

			vgImage::FreeImageWrapper img;

			img.loadFromFile( logopath.c_str() );

			if ( img.getImageSize() == 0 )
			{
				return;
			}

			img.swapRedAndBlueChannel();

			if ( img.getInfoHeader()->biBitCount == 24)
			{
				glGenTextures(1, &m_textureID[i]);					// Create 1 Textures
				glBindTexture(GL_TEXTURE_2D, m_textureID[i]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,  img.getWidth(), img.getHeight(),
					GL_RGB, GL_UNSIGNED_BYTE, img.accessAlignedPixels());
			}
			else if (  img.getInfoHeader()->biBitCount == 32 )
			{
				glGenTextures(1, &m_textureID[i]);					// Create 1 Textures
				glBindTexture(GL_TEXTURE_2D, m_textureID[i]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,  img.getWidth(), img.getHeight(),
					GL_RGBA, GL_UNSIGNED_BYTE, img.accessAlignedPixels());
			}

			m_texNameIDMap.insert( std::make_pair( fileNames[i], i ) );
		}
	}

//------------------------------------------------------------------------------------
	void SmallMapLogo::initscenedata()
	{
		float length,width;

		vgKernel::Box	_box  = 
			vgKernel::RendererManager::getSingleton().getAllRendererBoxWithoutshp();

		length = _box._maxVertex.x - _box._minVertex.x;

		width = _box._maxVertex.z - _box._minVertex.z; 

		m_lengthradiowidth = length / width;

		xlengthIn3dscene = length;

		ylengthIn3dscene = width;

		xcenterIn3dscene = _box.getCenter().x;

		ycenterIn3dscene = _box.getCenter().z;

		zcenterIn3dscene =   CAM_HEIGHT;

		if ( _box._minVertex.x >= _box._maxVertex.x )
		{
			b_hasscenedata = false;
		}
		else
			b_hasscenedata = true;
	}
//------------------------------------------------------------------------------------
	void SmallMapLogo::initsmallmap()
	{
		if ( !b_hasscenedata)
		{
			return;
		}

		if ( m_textureID != NULL )
		{
			delete[] m_textureID;

			m_textureID = NULL;
		}

		m_textureID = new GLuint[1];

		float tempradio = xlengthIn3dscene / ylengthIn3dscene;

		radio = 	m_viewHeight / m_viewWidth;

		setLogoWidth( (float)SAMLLMAPLOGOWIDTH,  radio * tempradio);

		m_logoHeight = m_logoWidth / (radio * tempradio);

		setCenterPos( vgKernel::Vec2( (float)1.0, (float)(1-m_logoHeight) ), false );

		logomultiview = SAMLLMAPLOGOWIDTH * m_viewWidth;

		calculatesceneradiomap();

		//加载纹理
		vgKernel::StringVector fileNames;

		fileNames.push_back( SMALLMAP_FILE_NAME );

		this->loadTexture( fileNames );

	}
//-------------------------------------------------------------------------------
	void SmallMapLogo::calculatesceneradiomap()
	{
		m_sceneradiomapx =  xlengthIn3dscene /  m_logoWidth ;

		m_sceneradiomapy = ylengthIn3dscene / m_logoHeight;
	}
//-------------------------------------------------------------------------------
	void SmallMapLogo::recalculate()
	{
		//当渲染窗口大小变化时重新计算Logo的参数
		int viewport[4];

		glGetIntegerv( GL_VIEWPORT, viewport );

		static int m_lastViewWidth = viewport[2];  //上一次viewport宽度
		static int lastViewHeigth = viewport[3]; //上一次viewport高度

		if ( viewport[2] != m_lastViewWidth || viewport[3] != lastViewHeigth )
		{
			radio =	(float)viewport[3]/(float)viewport[2];

			if ( ylengthIn3dscene == 0)
			{
				 return;
			}

			float tempradio = xlengthIn3dscene / ylengthIn3dscene;

			m_logoWidth = logomultiview / (float)viewport[2];

			m_logoHeight = m_logoWidth / (radio * tempradio);

			m_lastViewWidth = viewport[2];  //上一次viewport宽度

			lastViewHeigth = viewport[3]; //上一次viewport高度

			calculatesceneradiomap();

			setCenterPos( vgKernel::Vec2( (float)1.0, (float)(1-m_logoHeight)), false );
		}
	}
//---------------------------------------------------------------------------------
	vgKernel::Vec3 SmallMapLogo::get3dVecFrom2d( const CPoint& point_2d )
	{
		vgKernel::Vec3 ret;
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glLoadIdentity();

////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
		glMatrixMode( GL_PROJECTION );
		glPopMatrix();

		glMatrixMode( GL_MODELVIEW );
		glPopMatrix();

		return ret;
	}
//-------------------------------------------------------------------------------

	void SmallMapLogo::OnLButtonDown( UINT nFlags, CPoint position )
	{
		vgKernel::Vec3 _vec = get3dVecFrom2d( position );

		if ( Isinsmallmapregion( _vec.x, _vec.y ))
		{
			changesceneposition( _vec.x, _vec.y );
		}
	}
//-------------------------------------------------------------------------------

	bool SmallMapLogo::Isinsmallmapregion( float _x, float _y )
	{
		float centerx = getCenterPos()->x;

		float centery = getCenterPos()->y;

		if ( ( _x >= centerx - m_logoWidth/2 )&&( _x < centerx + m_logoWidth /2 ) 
				&& ( _y >= centery - m_logoHeight/2) && ( _y <= centery + m_logoHeight /2))
		{
			return true;
		}
		else
			return false;
	}
	//-------------------------------------------------------------------------------

	void SmallMapLogo::setRenderState( bool _render )
	{

		initscenedata();

		if ( !b_hasscenedata )
		{
			return;
		}

		if ( !b_initialized )
		{
			b_initialized = true;

			initsmallmap();
		}

		m_bRender = _render;

		if ( m_bRender )
		{
			vgKernel::InputSystem::getSingleton().setCurrentStatus( VG_SAMLL_MAP_LOGO | 
				VG_INPUTMODE_CAMERA | VG_INPUTMODE_SELECT | VG_INPUTMODE_UI );
		}
		else
		{
			vgKernel::InputSystem::getSingleton().setCurrentStatus(  
				VG_INPUTMODE_CAMERA | VG_INPUTMODE_SELECT | VG_INPUTMODE_UI );
		}
	}
//-------------------------------------------------------------------------------------------
	void SmallMapLogo::OnMouseMove( UINT nFlags, CPoint position )
	{
		vgKernel::Vec3 _vec = get3dVecFrom2d( position );

		m_mousepointx = _vec.x;

		m_mousepointy = _vec.y;
	}
}
