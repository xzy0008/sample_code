
#include <vgStableHeaders.h>
#include <vgLogo/vgloCorpLogo.h>
#include <vgLogo/vgloLogoManager.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgImage/vgiFreeImageWrapper.h>

#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

#define VGDATA_FILECONF						"DataFileConfig"
#define VGDATA_FILECONF_TEXTURE_LOGO		"LogoName"


namespace vgLogo {  


	//-----------------------------------------------------------
	CorpLogo::CorpLogo()
	{
		m_varyType = NONE;
		m_dWidth = 512.0;
		m_dHeight = 477.0;

		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );
		m_lastViewWidth = viewport[2];
		m_lastViewHeight = viewport[3];

		//先为纹理ID数组分配一个空间，保证渲染时可以没有贴图
		m_textureID = new GLuint[1];
	}

	//-----------------------------------------------------------
	CorpLogo::~CorpLogo()
	{
		this->unloadData();
	}

	//-----------------------------------------------------------
	void CorpLogo::initCorpLogoRU()
	{
		//调用培父类接口设置数据
		setRenderState( true );
		//setLogoWidth( (float)0.2 );(宽高比为1:1)

		// 设置宽度和宽高比
		//setLogoWidth( (float)0.6, (float)2.76 );
		setLogoWidth( (float)0.48, (float)1.9 );// (不进行手动缩放)

		// 设置位置在右上角
		//setCenterPos( vgKernel::Vec2( (float)1.0, (float)0.8 ), false );
		
		// 设置位置在右下角
		setCenterPos( vgKernel::Vec2( (float)1.0, (float)-1.0 ), false );

		//设置自己独有的数据
		m_bRotate = false;
		m_zRot = 0;

		//加载MenuLogo纹理
		vgKernel::StringVector fileNames;
		fileNames.push_back( "MenuLogo1.tga" );
		fileNames.push_back( "MenuLogo2.tga" );
		fileNames.push_back( "MenuLogo3.tga" );
		fileNames.push_back( "MenuLogo4.tga" );
		fileNames.push_back( "MenuLogo5.tga" );
		fileNames.push_back( "MenuLogo6.tga" );
		this->loadTexture( fileNames );

		// 加载CorpLogo纹理
		loadTexture();
	}

	//-----------------------------------------------------------
	void CorpLogo::unloadData()
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
	
	//-----------------------------------------------------------
	// Load Bitmaps And Convert To Textures
	void  CorpLogo::loadTexture()								
	{
		String exepath = vgKernel::SystemUtility::getCurrentProcessPath();

		String texturePath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_TEXTURE_PATH);

		String textureName =  VG_EXECONF_GET_STRING( 
			VGDATA_FILECONF,  
			VGDATA_FILECONF_TEXTURE_LOGO);

		String logopath = exepath + texturePath + textureName;

		vgImage::FreeImageWrapper img;

		img.loadFromFile( logopath.c_str() );

		if ( img.getImageSize() == 0 )
		{
			return;
		}

		img.swapRedAndBlueChannel();

		if ( img.getInfoHeader()->biBitCount == 24)
		{
			glGenTextures(1, &m_textureID[0]);					// Create 1 Textures
			glBindTexture(GL_TEXTURE_2D, m_textureID[0]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,  img.getWidth(), img.getHeight(),
				GL_RGB, GL_UNSIGNED_BYTE, img.accessAlignedPixels());
		}
		else if (  img.getInfoHeader()->biBitCount == 32 )
		{
			glGenTextures(1, &m_textureID[0]);					// Create 1 Textures
			glBindTexture(GL_TEXTURE_2D, m_textureID[0]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,  img.getWidth(), img.getHeight(),
				GL_RGBA, GL_UNSIGNED_BYTE, img.accessAlignedPixels());
		}
	}

	//-----------------------------------------------------------
	// Load Bitmaps And Convert To Textures
	void  CorpLogo::loadTexture( vgKernel::StringVector fileNames )								
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

	//-----------------------------------------------------------
	void CorpLogo::render()
	{
		if ( !getRenderState() )
		{
			return;
		}
		else
		{
			recalculate();   //当渲染窗口改变时重新计算参数

			glPushAttrib(GL_CURRENT_BIT);

			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();

			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

			glAlphaFunc(GL_GREATER, 0.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);

			glDisable(GL_DEPTH_TEST);

			//////////////////////////////////////////////////////////////////////////
			    glTranslatef( getCenterPos()->x, getCenterPos()->y, 0 );       //中心点的位置

				//是否旋转
				if ( m_bRotate )
				{
					this->renderBegin();
					glRotatef(m_zRot,0.0f,0.0f,1.0f);
				}
				
				glEnable(GL_TEXTURE_2D);
				glColor3f(1,1,1);
				assert( m_textureID != NULL );
				glBindTexture( GL_TEXTURE_2D, m_textureID[m_currentTexID] );

				float halfHeight = m_logoHeight / 2.0;
				float halfWidth = m_logoWidth / 2.0;

				glBegin(GL_POLYGON);   
					glTexCoord2i( 0, 0 );
					glVertex3f( (-1) * halfWidth,(-1) * halfHeight, 0.0 );
					glTexCoord2i( 0, 1 );
					glVertex3f( (-1) * halfWidth, halfHeight,0.0 );
					glTexCoord2i( 1, 1 );
					glVertex3f( halfWidth, halfHeight, 0.0 );
					glTexCoord2i( 1, 0 );
					glVertex3f( halfWidth, (-1) * halfHeight, 0.0 );
				glEnd();
		
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

	//-----------------------------------------------------------
	void CorpLogo::renderBegin()
	{
		m_zRot += 0.1f;
	}

	//-----------------------------------------------------------
	void CorpLogo::reset()
	{/*
		m_bRender = true;
		m_centerPos = vgKernel::Vec2();
		m_logoHeight = 0.1f;                             
		m_logoWidth = 0.1f;
	
		m_zRot = 0;
		m_bRotate = true;*/
	}

	//-----------------------------------------------------------
	void CorpLogo::recalculate()
	{
		//当渲染窗口大小变化时重新计算Logo的参数
		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		static int m_lastViewWidth = viewport[2];  //上一次viewport宽度
		static int lastViewHeigth = viewport[3]; //上一次viewport高度

		//只宽度变化
		if ( viewport[2] != m_lastViewWidth && viewport[3] == lastViewHeigth )
		{
			m_lastViewWidth = viewport[2];
			this->setVaryType( WIDTH );
		}
		//只高度变化 
		if ( viewport[3] != lastViewHeigth && viewport[2] == m_lastViewWidth )
		{
			lastViewHeigth = viewport[3];
			this->setVaryType( HEIGHT );
		}
		//高度宽度都变化
		if ( viewport[2] != m_lastViewWidth && viewport[3] != lastViewHeigth )
		{
			m_lastViewWidth = viewport[2];
			lastViewHeigth = viewport[3];
			this->setVaryType( BOTH );
		}

		//根据窗口变化类型，重新计算MenuLogo各参数
		if ( m_varyType != NONE )
		{
			//this->recalculateData();
			this->setVaryType( NONE );
		}
	}

	//-----------------------------------------------------------
	void CorpLogo::recalculateData()
	{
		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		// 1.恢复原始参数
		setLogoWidth( getOriginalWidth() );
		setLogoHeight( getOriginalHeight() );
		setCenterPos( getOriginalCenterPos(), true );
		// 2.计算比例
		float radio = viewport[2] / (float)viewport[3];

		float originalHeight = getOriginalHeight();
		float originalWidth = getOriginalWidth();

		if ( m_varyType == WIDTH )  //保持宽度比例，让高度变化
		{
#if 0  
			// 1.恢复原始参数
			setLogoWidth( getOriginalWidth() );
			setLogoHeight( getOriginalHeight() );
			setCenterPos( getOriginalCenterPos(), true );

			// 2.计算比例
			float ratio = viewport[2] / (float)viewport[3];
			float originalHeight = getOriginalHeight();
#endif
			// 3.设置新的参数
			setLogoHeight( originalHeight * radio );
			//getCenterPos()->y -= getHCounter() * ( getLogoHeight() - originalHeight ) / 2.0;
			
			// 因为现在Logo是在场景的右下角
			getCenterPos()->y += getHCounter() * ( getLogoHeight() - originalHeight ) / 2.0;
		}
		else if ( m_varyType == HEIGHT  )  //保持宽度比例，让宽度变化
		{
			//此比例须重新计算，与其它两种情况不同
			radio = ( viewport[3] / m_dHeight ) * ( m_dWidth / (float)viewport[2] );

			// 3.设置新的参数
			//setLogoWidth( originalWidth * radio );
			setLogoWidth( originalWidth / radio );
			getCenterPos()->x -= getWCounter() * ( getLogoWidth() - originalWidth ) / 2.0;
		}
		else if ( m_varyType == BOTH )   //保持宽度比例，让高度变化
		{
			// 3.设置新的参数
			setLogoHeight( originalHeight * radio );
			//getCenterPos()->y -= getHCounter() * ( getLogoHeight() - originalHeight ) / 2.0;

			// 因为现在Logo是在场景的右下角
			getCenterPos()->y += getHCounter() * ( getLogoHeight() - originalHeight ) / 2.0;
		}
	}

	//-----------------------------------------------------------
	void CorpLogo::setCurrentTexID( string texFileName )
	{
		map<string, GLuint>::iterator keyFind = m_texNameIDMap.find( texFileName );

		if ( keyFind != m_texNameIDMap.end() )
		{
			m_currentTexID = keyFind->second;
		}
	}

}//namespace vgLogo



