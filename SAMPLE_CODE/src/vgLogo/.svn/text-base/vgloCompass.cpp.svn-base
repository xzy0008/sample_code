// SmallMap.cpp: implementation of the SmallMap class.
//
//////////////////////////////////////////////////////////////////////


#include <vgStableHeaders.h>
#include <vgLogo/vgloCorpLogo.h>
#include <vgLogo/vgloLogoManager.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgImage/vgiFreeImageWrapper.h>

#include <vgConf/vgcoExeConfig.h>

#include <vgLogo/vgloCompass.h>

#include <vgcam/vgcaCamManager.h>

#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

#define VGDATA_FILECONF						"DataFileConfig"
#define VGDATA_FILECONF_TEXTURE_LOGO		"LogoName"

#define  CAMPASSLOGOWIDTH 0.5

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

//-------------------------------------------------------------------------
	CompassLogo::CompassLogo()
	{
		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		m_viewWidth = viewport[2];
		m_viewHeight = viewport[3];

		m_textureID = NULL;

		m_currentTexID = -1;

		m_zRot = 0.0;

		radio = 1.0;

		logomultiview = 1.0;

		b_rotate = false;
	}
//-------------------------------------------------------------------------
	CompassLogo::~CompassLogo()
	{
		unloadData();
	}

//-------------------------------------------------------------------------
	void CompassLogo::loadTexture( vgKernel::StringVector fileNames )
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
//-------------------------------------------------------------------------
	void CompassLogo::render()
	{
		glDisable( GL_DEPTH_TEST );

		recalculate();

		map<string, GLuint>::iterator _iter = m_texNameIDMap.begin();

		map<string , GLuint>::iterator _end = m_texNameIDMap.end();

		for ( ; _iter != _end; _iter++ )
		{
			int texid = _iter->second;

			b_rotate = false;

			if ( _iter->first == "luopan.png" )
			{
				renderbegin();
			}
			render( texid );
		}

		glEnable( GL_DEPTH_TEST );
	}
//-------------------------------------------------------------------------
	void CompassLogo::render( GLuint _textureID )
	{
		if ( !getRenderState() )
		{
			return;
		}
		else
		{
			glPushAttrib(GL_CURRENT_BIT);

			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();

			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

			glAlphaFunc(GL_GREATER, 0.5f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
 			glEnable(GL_ALPHA_TEST);
   			glEnable(GL_BLEND);

			glDisable(GL_DEPTH_TEST);

			//////////////////////////////////////////////////////////////////////////
			glTranslatef( getCenterPos()->x, getCenterPos()->y, 0);       //中心点的位置


			glEnable(GL_TEXTURE_2D);
			glColor3f(1,1,1);
			assert( m_textureID != NULL );
			glBindTexture( GL_TEXTURE_2D, m_textureID[_textureID] );

			float halfHeight = m_logoHeight / 2.0;
			float halfWidth = m_logoWidth / 2.0;

			if ( !b_rotate )
			{
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
			}
			else
			{
				float _x, _y;
				glBegin( GL_POLYGON );
				glTexCoord2i( 0, 0 );
				_x = (-1) * halfWidth;
				_y = (-1) * halfWidth;
				rotateangle( _x, _y, -m_zRot );
				glVertex3f( _x, _y/radio, 0.0 );

				glTexCoord2i( 0, 1 );
				_x = (-1) * halfWidth;
				_y = halfWidth;
				rotateangle( _x, _y, -m_zRot );
				glVertex3f( _x, _y/radio, 0.0 );

				glTexCoord2i( 1, 1 );
				_x = halfWidth;
				_y = halfWidth;
				rotateangle( _x, _y, -m_zRot );
				glVertex3f( _x, _y/radio, 0.0 );

				glTexCoord2i( 1, 0 );
				_x = halfWidth;
				_y =  (-1) *halfWidth;
				rotateangle( _x, _y, -m_zRot );
				glVertex3f( _x, _y/radio, 0.0 );

				glEnd();
			}

			glDisable(GL_TEXTURE_2D);

			//////////////////////////////////////////////////////////////////////////
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable( GL_ALPHA_TEST );

			glMatrixMode( GL_PROJECTION );
			glPopMatrix();

			glMatrixMode( GL_MODELVIEW );
			glPopMatrix();

			glPopAttrib();
		}
		return;

	}
//-------------------------------------------------------------------------
	void CompassLogo::initcompass()
	{
		setRenderState( false );

		m_textureID = new GLuint[1];

		radio = 	m_viewHeight/m_viewWidth;



		setLogoWidth( (float)CAMPASSLOGOWIDTH,  radio);

		setCenterPos( vgKernel::Vec2( (float)(CAMPASSLOGOWIDTH-1), (float)(1-m_logoHeight) ), false );

		logomultiview = CAMPASSLOGOWIDTH * m_viewWidth;

		//加载纹理
		vgKernel::StringVector fileNames;
		fileNames.push_back( "luopan.png" );
		fileNames.push_back( "zhizhen.png" );
		this->loadTexture( fileNames );

	}
//-------------------------------------------------------------------------
	void CompassLogo::unloadData()
	{

			if ( m_textureID == NULL )
			{
				return;
			}

			for ( int i = 0; i < sizeof(m_textureID) / sizeof(m_textureID[0]); i++ )
			{
				if ( m_textureID[i] != 0 )
				{
					glDeleteTextures( 1, &m_textureID[i] );
					m_textureID[i] = 0;
				}
			}

			delete[] m_textureID;
			m_textureID = NULL;

	}
//-------------------------------------------------------------------------
	void CompassLogo::renderbegin()
	{
		vgKernel::Vec3 _camdir = 
			vgCam::CamManager::getSingleton().getCurrentDirection();

		float _camx = _camdir.x;

		float _camz = _camdir.z;

		float _length = _camx * _camx+ _camz * _camz ;

		float m = sqrt( _length );

		float angle = asin( _camx / m );

		m_zRot = angle/3.1415916 * 180.0;

		if ( _camz < 0 )
		{
			m_zRot =180 - m_zRot;
		}

		b_rotate = true;
	}
//-------------------------------------------------------------------------
	void CompassLogo::rotateangle( float &_x, float &_y, float _angle )
	{
		float x, y;

		float tempangle = _angle/180.0*3.1415916;

		x = _x*cos(tempangle) - _y*sin(tempangle);
		y = _x*sin(tempangle) + _y*cos(tempangle);

		_x = x;
		_y = y;

		return;
	}

//---------------------------------------------------------------------------
	void CompassLogo::recalculate()
	{
		//当渲染窗口大小变化时重新计算Logo的参数
		int viewport[4];

		glGetIntegerv( GL_VIEWPORT, viewport );

		static int m_lastViewWidth = viewport[2];  //上一次viewport宽度
		static int lastViewHeigth = viewport[3]; //上一次viewport高度

//  		if ( viewport[2] != m_lastViewWidth || viewport[3] != lastViewHeigth )
//  		{
			radio =	(float)viewport[3]/(float)viewport[2];

			m_logoWidth = logomultiview / (float)viewport[2];

			m_logoHeight = m_logoWidth / radio;

			m_lastViewWidth = viewport[2];  //上一次viewport宽度
			
			lastViewHeigth = viewport[3]; //上一次viewport高度

			setCenterPos( vgKernel::Vec2( (float)(m_logoWidth-1), (float)(1-m_logoHeight)), false );
/* 		}*/

	}
}
