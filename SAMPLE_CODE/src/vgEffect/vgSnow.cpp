

// includes
#include <vgStableHeaders.h>
#include "vgeffect/vgSnow.h"

#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

// class vgSnow
namespace vgMod
{

	VGK_RENDERER_IMPLEMENT( vgSnow,RENDERER_TYPE_PARTICLE )

	
	
	vgSnow::vgSnow()
	{
		m_psnow	= NULL ;
		m_height = 150.0f;
		m_width  = 200.0f;
		m_speed	 = 1.0f;
		
#if 0
		String exepath = vgKernel::SystemUtility::getCurrentProcessPath();

		String texturePath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_TEXTURE_PATH);

		texturePath = exepath + texturePath;
		m_texturename[0] = texturePath + "SnowLarge.tga";
		m_texturename[1] = texturePath + "SnowMiddle.tga";
		m_texturename[2] = texturePath + "SnowSmall.tga";
#else
		m_texturename[0] = "SnowLarge.tga";
		m_texturename[1] = "SnowMiddle.tga";
		m_texturename[2] = "SnowSmall.tga";
#endif
		strcpy( m_name, "snow");
		
		//TYPE = VG_SNOW;	
		
		//m_numOfFaces = 100;  //£¿£¿£¿
	}
	
	vgSnow::~vgSnow()
	{
		delete[]  m_psnow;
		m_psnow = NULL;
	}
	
	void vgSnow::Initialize()
	{
		
		m_psnow = new tagSNOW[ m_nParticleCount ];
		srand( GetTickCount() );
		
		for ( int i = 0; i < m_nParticleCount; i++ )
		{
			m_psnow[ i ].nIndexTexture = rand() % 3;
			m_psnow[ i ].position.x    = m_Position.x 
				+ float( rand() % (int)m_width - 100 );
			m_psnow[ i ].position.z    = m_Position.z 
				+ float( rand() % (int)m_width - 100 );
			m_psnow[ i ].position.y    = m_Position.y 
				+ float( rand() % (int)m_height - 30 );
			
			m_psnow[ i ].rotation.x    = float(rand() % 180);//0;
			m_psnow[ i ].rotation.y    = float(rand() % 180);//0;
			m_psnow[ i ].rotation.z    = float(rand() % 180);//0;
			
			m_psnow[ i ].dropSpeed     = m_speed/100.0f/*0.01f*/ 
				* ( rand() % 50 + 2 );
			m_psnow[ i ].rotSpeed      =  0.1f * ( rand() % 10 + 2 );
		}
		
		// 	if( !TexRGB24("data/SnowLarge.bmp", m_pTexture[0])   ||
		// 		!TexRGB24("data/SnowMiddle.bmp", m_pTexture[1])  ||
		// 		!TexRGB24("data/SnowSmall.bmp", m_pTexture[2])   ){
		// 		status = false;
		// 	}
		
		for (int indexTex=0; indexTex<3 ; indexTex++ )
		{	
			assert( m_pTexture[indexTex].isNull() );
			m_pTexture[indexTex] = 
				vgCore::TextureManager::getSingleton().getTexturePtr( m_texturename[indexTex] );
		}
		
	}
	
	void vgSnow::Render()
	{
		glPushAttrib(GL_CURRENT_BIT);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glAlphaFunc(GL_GREATER, 0.0f) ;
		
		if(!m_bStopSE)
		{	  
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST) ;
			static GLfloat wAngleY = 10.0f;
			
			glPushMatrix();
			for ( int nIndex = 0; nIndex < m_nParticleCount; nIndex++ )
			{
				glLoadIdentity();
				glTranslatef( 0.0f, -30.0f, -150.0f ); 
				glRotatef( wAngleY, 0.0f, 1.0f, 0.0f );
				
				glTranslatef( m_psnow[ nIndex ].position.x, 
					m_psnow[ nIndex ].position.y, m_psnow[ nIndex ].position.z );
				
				glRotatef( m_psnow[ nIndex ].rotation.x, 1.0f, 0.0f, 0.0f );
				glRotatef( m_psnow[ nIndex ].rotation.y, 0.0f, 1.0f, 0.0f );
				glRotatef( m_psnow[ nIndex ].rotation.z, 0.0f, 0.0f, 1.0f );
				
				//glBindTexture( GL_TEXTURE_2D, m_pTexture[ m_psnow[ nIndex ].nIndexTexture ] );
				m_pTexture[ m_psnow[ nIndex ].nIndexTexture ]->useBind();
				
				glColor4f(1.0f,1.0f,1.0f,1.0f);
				glBegin( GL_QUADS );
				//			glNormal3f( 0.0f, 1.0f, 0.0f );
				glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -0.5f, 0.0f, -0.5f );
				glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  0.5f, 0.0f, -0.5f );
				glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  0.5f, 0.0f,  0.5f );
				glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -0.5f, 0.0f,  0.5f );
				glEnd();
				
				m_psnow[ nIndex ].position.y -= m_psnow[ nIndex ].dropSpeed;
				if( m_psnow[ nIndex ].position.y < -30 )
					m_psnow[ nIndex ].position.y = m_height - 30/*120.0f*/;
				
				m_psnow[ nIndex ].rotation.x += m_psnow[ nIndex ].rotSpeed;
				m_psnow[ nIndex ].rotation.y += m_psnow[ nIndex ].rotSpeed;
				m_psnow[ nIndex ].rotation.z += m_psnow[ nIndex ].rotSpeed;
			}// if(!m_bStopSE)
			
			wAngleY += 0.2f;
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST) ; 
		}	

		glPopAttrib();
	}	//	void vgSnow::Render()
	
	
	
}  // namespace vgCore

