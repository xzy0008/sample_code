
// includes
#include <vgStableHeaders.h>
#include "vgEffect/vgFire.h"


// class vgFountain
namespace vgMod
{
	
	VGK_RENDERER_IMPLEMENT( vgFire ,RENDERER_TYPE_PARTICLE)
	
	static GLfloat colors[12][3]=		
	{
		{1.0f,0.5f,0.5f},{0.9f,0.32f,0.0f}/*{1.0f,0.75f,0.5f}*/,{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
		{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
		{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
	};
	
	vgFire::vgFire()
	{
		m_pFire	= NULL ;
		m_height = 30.0f;
		m_width  = 15.0f;
		m_speed	 = 10.0f;
		


		strcpy( m_name, "fire");
		
		//TYPE = VG_FIRE;
		
		//m_numOfFaces = 100;  //???

		colorIndex	= 1;
		xspeed		= 1.0f ;
		yspeed		= 1.0f ;
		slowdown	= 1.0f ;
		delay		= 0;

		m_RenderTypeInt = 2;

		m_eSubType = PARTICLE_FIRE;
	}
	vgFire::~vgFire()
	{
		delete m_pFire;
		m_pFire = NULL;
	}
	
	
	void vgFire::Initialize()									
	{
		m_pFire = new tagFIRE[m_nParticleCount];
		
		for (int loop=0; loop < m_nParticleCount; loop++)				
		{
			m_pFire[loop].active=true;								// Make All The Particles Active
			m_pFire[loop].life=1.0f;								// Give All The Particles Full Life
			m_pFire[loop].fade=float(rand()%300/*100*/)/1000.0f+0.03f;	// Random Fade Speed
			
			m_pFire[loop].color.x=colors[loop*(12/m_nParticleCount)][0];	// Select Red Rainbow Color
			m_pFire[loop].color.y=colors[loop*(12/m_nParticleCount)][1];	// Select Red Rainbow Color
			m_pFire[loop].color.z=colors[loop*(12/m_nParticleCount)][2];	// Select Red Rainbow Color
			
			m_pFire[loop].position = m_Position;
			
			m_pFire[loop].velocity.x = float( rand()%int(m_width) 
				- m_width/2.0f )*10.0f;		// Random Speed On X Axis
			m_pFire[loop].velocity.y = float( rand()%int(m_height)
				- m_height/2.0f )*10.0f;		// Random Speed On Y Axis
			m_pFire[loop].velocity.z = float( rand()%int(m_width) 
				- m_width/2.0f )*10.0f;		// Random Speed On Z Axis
			
			m_pFire[loop].gravity.x = 0.0f;									// Set Horizontal Pull To Zero
			m_pFire[loop].gravity.y = m_speed/10.0f/*-0.8f*//*0.8f*/;						// Set Vertical Pull Downward
			m_pFire[loop].gravity.z = 0.0f;									// Set Pull On Z Axis To Zero
		}
		
		
		assert( m_pTexture.isNull() );
		m_pTexture = 
			vgCore::TextureManager::getSingleton().getTexturePtr( m_texturename );
		m_pTexture;
	}
	
	void vgFire::Render()
	{
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glAlphaFunc(GL_GREATER, 0.0f) ;

		//glTexEnvf    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glEnable(GL_TEXTURE_2D) ;
		glEnable(GL_BLEND) ;
		glDisable(GL_DEPTH_TEST) ;
		
		//glBindTexture(GL_TEXTURE_2D , m_pTexture) ;								// Enable Blending
		m_pTexture->useBind();

		 for (int loop=0;loop<m_nParticleCount;loop++)					// Loop Through All The Particles
		{
			if (m_pFire[loop].active)							// If The Particle Is Active
			{
				float x=m_pFire[loop].position.x;						// Grab Our Particle X Position
				float y=m_pFire[loop].position.y;						// Grab Our Particle Y Position
				float z=m_pFire[loop].position.z;					// Particle Z Pos + Zoom
				
				// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
				glColor4f(m_pFire[loop].color.x, m_pFire[loop].color.y, 
					m_pFire[loop].color.z, m_pFire[loop].life);
				
				glBegin(GL_TRIANGLE_STRIP);						
				glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); 
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); 
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); 
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); 
				glEnd();										
				
				m_pFire[loop].position.x+=m_pFire[loop].velocity.x/(slowdown*1000);
				m_pFire[loop].position.y+=m_pFire[loop].velocity.y/(slowdown*1000);
				m_pFire[loop].position.z+=m_pFire[loop].velocity.z/(slowdown*1000);
				
				m_pFire[loop].velocity.x+=m_pFire[loop].gravity.x ;			// Take Pull On X Axis Into Account
				m_pFire[loop].velocity.y+=m_pFire[loop].gravity.y ;			// Take Pull On Y Axis Into Account
				m_pFire[loop].velocity.z+=m_pFire[loop].gravity.z ;			// Take Pull On Z Axis Into Account
				m_pFire[loop].life-=m_pFire[loop].fade;		// Reduce Particles Life By 'Fade'
				
				if (m_pFire[loop].life<0.0f)					// If Particle Is Burned Out
				{
					m_pFire[loop].life=1.0f;					// Give It New Life
					m_pFire[loop].fade=float(rand()%300/*100*/)/1000.0f+0.03f;	// Random Fade Value
					m_pFire[loop].position.x = m_Position.x ;	 					
					m_pFire[loop].position.y = m_Position.y ;					
					m_pFire[loop].position.z = m_Position.z ;						
		
					m_pFire[loop].velocity.x = float( rand()%int(m_width) 
						- m_width/2.0f )*10.0f;		// Random Speed On X Axis
					m_pFire[loop].velocity.y = float( rand()%int(m_height)
						- m_height/2.0f )*10.0f;		// Random Speed On Y Axis
					m_pFire[loop].velocity.z = float( rand()%int(m_width) 
						- m_width/2.0f )*10.0f;		// Random Speed On Z Axis
					
					m_pFire[loop].color.x    = colors[colorIndex][0];			
					m_pFire[loop].color.y	 = colors[colorIndex][1];			
					m_pFire[loop].color.z	 = colors[colorIndex][2];		
				}
				
// 				if ( delay < 25 )
// 				{
// 					delay ++;
// 				}
// 				else
// 				{
// 					delay = 0;
// 					if (colorIndex < 12)
// 					{	
// 						colorIndex ++;
// 					}
// 					else
// 					{
// 						colorIndex = 0;
// 					}
// 				}// else(delay >= 25)

			}// if (m_pFire[loop].active)
		}// for (int loop)
		
		glEnable(GL_DEPTH_TEST) ;	
		glDisable(GL_BLEND) ;
		glDisable(GL_TEXTURE_2D) ;

	}	//void vgFire::Render()

	BoundingBox vgFire::ComputeBoundBox()
	{
		float	minFadeSpeed= 0.03f;
		float	maxLifeTime = 1/minFadeSpeed;
		float	maxWidth	= m_width/ 200.0f * maxLifeTime;
		float	maxHeight	= m_height/200.0f * maxLifeTime;

		m_BoundryBox.maxPoint.x = m_Position.x + maxWidth;
		m_BoundryBox.maxPoint.y = m_Position.y + maxHeight;
		m_BoundryBox.maxPoint.z = m_Position.z + maxWidth;
		
		m_BoundryBox.minPoint.x = m_Position.x - maxWidth;
		m_BoundryBox.minPoint.y = m_Position.y ;
		m_BoundryBox.minPoint.z = m_Position.z - maxWidth;
		
		return	m_BoundryBox;
	}	//BoundingBox ComputeBoundBox()
	
	
	//void vgFire::WriteNodeToVG(CFile &fp)	//写入文件
	//{
	//	int i;
	//	
	//	i = VG_PARTICLE;

	//long newpos;	

	////fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

	//Posinfile = fp.GetPosition();
	//	
	//fp.Write(&nodelength, sizeof(long));
	//
	//	fp.Write(&i , sizeof(int));	               //写类型type

	//	i = 1;									//写火类型

	//	fp.Write(&i, sizeof(int));
	//	fp.Write(m_LayerName , 20);						
	//	
	//	fp.Write(&m_isVisible, sizeof(bool));			//写可见性标记
	//	
	//	/*	char name[20]=" ";*/			
	//	fp.Write(m_texturename.c_str(), 20);			//写材质名
	//	
	//	fp.Write(&m_Position.x , sizeof(float));		//写节点中心点位置
	//	fp.Write(&m_Position.y, sizeof(float));	
	//	fp.Write(&m_Position.z , sizeof(float));
	//	
	//	fp.Write(&m_height, sizeof(float));	//写粒子属性 含高度、宽度、速度、大小
	//	fp.Write(&m_width, sizeof(float));
	//	fp.Write(&m_speed, sizeof(float));
	//	fp.Write(&m_PartLenth, sizeof(float));
	//	fp.Write(&m_PartWidth, sizeof(float));
	//	
	//	fp.Write(&m_nParticleCount, sizeof(int));		//写粒子数目

	//newpos = fp.GetPosition();
	//	
	//nodelength = newpos - Posinfile- sizeof(long);

	//fp.Seek(Posinfile, CFile::begin);

	//fp.Write(&nodelength, sizeof(long));

	//fp.SeekToEnd();
	//}	//	WriteNodeToVG(CFile &fp)

	void vgFire::UpdatePos()
	{
		m_Position.x = (m_BoundryBox.maxPoint.x + m_BoundryBox.minPoint.x) / 2;

		m_Position.y = m_BoundryBox.minPoint.y;

		m_Position.z = (m_BoundryBox.maxPoint.z + m_BoundryBox.minPoint.z) / 2;

		m_prePositon = m_Position;

		/*vgCore::QuadtreeSceneManager &mgr = 
			vgCore::QuadtreeSceneManager::getSingleton();

		if (mgr.GetNodeAbstract(m_id))
		{
			mgr.GetNodeAbstract(m_id)->GetBoundryBox() = m_BoundryBox;

			mgr.GetNodeAbstract(m_id)->m_Position = m_Position;
		}*/
	}

}	//namespace vgCore
