

// includes
#include <vgStableHeaders.h>
#include "vgeffect/vgRain.h"


// class vgRain
namespace vgMod
{
	
	VGK_RENDERER_IMPLEMENT( vgRain ,RENDERER_TYPE_PARTICLE)
	
	vgRain::vgRain()
	{
		m_prain	= NULL ;
		m_height = 150.0f;
		m_width  = 200.0f;
		m_speed	 = 8.0f;
		m_PartLenth	= 10.0f;
		m_PartWidth = 0.05f;
		
		
		strcpy( m_name, "rain");
		
		//TYPE = VG_RAIN;	
		
		//m_numOfFaces = 100;  //£¿£¿£¿
		
	}
	
	vgRain::~vgRain()
	{
		delete m_prain;
		m_prain = NULL;
	}
	
	void vgRain::Initialize()
	{
		
		m_prain = new tagRAIN[ m_nParticleCount ];
		
		srand( GetTickCount() );
		float circleR;
		float circleA;
		for ( GLuint i = 0; i < m_nParticleCount; i++ )
		{
			circleR = rand() % int( (m_width-20.0f)/2.0f ) + 10.0f;
			circleA = float(rand() % 360) * PI /180.0f ;
			
			m_prain[ i ].position.x       = m_Position.x 
				+ circleR* (float)sin(circleA ) ;/*float( rand() % 100 -50)*/;
			m_prain[ i ].position.z       = m_Position.z 
				+ circleR* (float)cos(circleA ) ;/*float( rand() % 100 -50)*/;
			m_prain[ i ].position.y       = m_Position.y 
				+ m_height -20.0f + float( rand() % 20 );
			
			m_prain[ i ].gravity.x          = 0;
			m_prain[ i ].gravity.y          = 0.0005f * 9.8f;
			m_prain[ i ].gravity.z          = 0;
			
			m_prain[ i ].dropSpeed     = m_speed/1000.0f/*0.008f*/ 
				+ m_speed/1000.0f/*0.008f*/ * float( rand() % 100 );
			m_prain[ i ].lineLength    = m_PartLenth/2.0f 
				+ 0.1f * float( rand() % int(5.0f*m_PartLenth) );
			m_prain[ i ].rotY		   = float (rand()%180) ;
		}
		//   if( !TexRGB24("data/Particle24.bmp", *m_pTextureSE) ){
		// 	  status = false;
		//   }
		// 
		// 	return status;
		assert( m_pTexture.isNull() );
		m_pTexture = 
			vgCore::TextureManager::getSingleton().getTexturePtr( m_texturename );
		
	}
	
	void vgRain::Render()
	{
		glPushAttrib(GL_CURRENT_BIT);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glAlphaFunc(GL_GREATER, 0.0f) ;

		if(!m_bStopSE)
		{	  
			glEnable(GL_TEXTURE_2D) ;
			glEnable(GL_BLEND) ;
			glDisable(GL_DEPTH_TEST) ;
			
			//	glBindTexture(GL_TEXTURE_2D , *m_pTextureSE) ;
			m_pTexture->useBind();
			glColor4f(0.85f ,0.85f ,1.0f ,1.0f);
			
			int circleR;
			float circleA;
			glLineWidth(1.0f) ;
			for ( GLuint nIndex = 0; nIndex < m_nParticleCount; nIndex++ )
			{
				glPushMatrix();
				
				glTranslatef( m_prain[ nIndex ].position.x, 
					m_prain[ nIndex ].position.y, 
					m_prain[ nIndex ].position.z );
				float	lineLengh = m_prain[ nIndex ].lineLength;
				glRotatef(m_prain[ nIndex ].rotY , 0.0f, 1.0f, 0.0f);
				glBegin( GL_QUADS );
				glNormal3f( 0.0f, 1.0f, 0.0f );
				glTexCoord2f( 0.0f, 0.0f ); 
				glVertex3f( /*-0.02f*/-m_PartWidth,   0.0f,  0.0f );
				glTexCoord2f( 1.0f, 0.0f ); 
				glVertex3f( /* 0.02f*/m_PartWidth,   0.0f,  0.0f );
				glTexCoord2f( 1.0f, 1.0f ); 
				glVertex3f( /* 0.02f*/m_PartWidth,   lineLengh,  0.0f );
				glTexCoord2f( 0.0f, 1.0f ); 
				glVertex3f( /*-0.02f*/-m_PartWidth,   lineLengh,  0.0f );
				glEnd();
				
				m_prain[ nIndex ].position.y -= m_prain[ nIndex ].dropSpeed;
				m_prain[ nIndex ].dropSpeed += m_prain[ nIndex ].gravity.y ;
				m_prain[ nIndex ].rotY += 20;
				
				if( m_prain[ nIndex ].position.y < m_Position.y -20.0f )
				{
					circleR = rand() % int( (m_width-20)/2 ) + 10.0f;
					circleA = float(rand() % 360) * PI/180.0f ;
					
					m_prain[ nIndex ].position.x       = m_Position.x 
						+ circleR* (float)sin(circleA ) ;/*float( rand() % 100 -50)*/;
					m_prain[ nIndex ].position.z       = m_Position.z 
						+ circleR* (float)cos(circleA ) ;/*float( rand() % 100 -50)*/;
					m_prain[ nIndex ].position.y       = m_Position.y 
						+ 60.0f + float( rand() % 20 );
					
					m_prain[ nIndex ].dropSpeed  = m_speed/1000.0f  
						+ m_speed/1000.0f * float( rand() % 100 );
					
				}// if
				glPopMatrix();	
			}// for ( GLuint nIndex )
			
			
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST) ;
		}// if(!m_bStopSE)

		glPopAttrib();
	}// void vgRain::Render()

}	//namespace vgCore 