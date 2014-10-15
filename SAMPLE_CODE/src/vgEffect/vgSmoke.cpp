
#include <vgStableHeaders.h>
#include "vgEffect/vgSmoke.h"



static GLfloat colors[12][3]=		
{
	{1.0f,0.5f,0.5f},{/*0.9f,0.32f,0.0f*/0.40f,0.40f,0.35f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};


// class vgSmoke
namespace vgMod
{
	
	VGK_RENDERER_IMPLEMENT( vgSmoke ,RENDERER_TYPE_PARTICLE)
	
	vgSmoke::vgSmoke()
	{
		


		m_pSmoke = NULL ;
		m_height = 50.0f;
		m_width  = 50.0f;
		m_speed	 =  2.0f;
		

		strcpy( m_name, "smoke");
		m_nParticleCount = MAX_PARTICLES;
		
		//TYPE = VG_FIRE;
		
		//m_numOfFaces = 100;  //???
		
		colorIndex	= 1;
		xspeed		= 1.0f ;
		yspeed		= 1.0f ;
		slowdown	= 1.0f ;
		delay		= 0;
		
		
		centerX		= 0.0f;
		centerY		= 0.0f;
		centerZ		= 0.0f;

		m_eSubType = PARTICLE_SMOKE;

	}
	vgSmoke::~vgSmoke()
	{
		delete m_pSmoke;
		m_pSmoke = NULL;
		gluDeleteQuadric(m_Sphere);
	}
	
	
	void vgSmoke::Initialize()									
	{
		m_pSmoke = new SmokeParticles[m_nParticleCount];
		
		m_Sphere=gluNewQuadric();
		gluQuadricDrawStyle(m_Sphere,GLU_FILL);
		
		for (GLuint loop=0;loop<m_nParticleCount;loop++)				
		{
			srand((unsigned)time(NULL) );
			m_pSmoke[loop].active=true;								// Make All The Particles Active
			m_pSmoke[loop].life=1.0f;								// Give All The Particles Full Life
			m_pSmoke[loop].fade=float(rand()%30)/10000.0f+
				/*0.003f*/0.3f;	// Random Fade Speed
				
				m_pSmoke[loop].r=colors[loop*(12/m_nParticleCount)][0];	// Select Red Rainbow Color
			m_pSmoke[loop].g=colors[loop*(12/m_nParticleCount)][1];	// Select Red Rainbow Color
			m_pSmoke[loop].b=colors[loop*(12/m_nParticleCount)][2];	// Select Red Rainbow Color
			
			m_pSmoke[loop].x = m_Position.x ;
			m_pSmoke[loop].y = m_Position.y ;
			m_pSmoke[loop].z = m_Position.z ;
			
			m_pSmoke[loop].xi= float( rand()%int(m_width) 
				- m_width/2.0f )*10.0f;		// Random Speed On X Axis
			m_pSmoke[loop].yi=float( rand()%int(m_height)
				- m_width/2.0f )*10.0f;		// Random Speed On Y Axis
			m_pSmoke[loop].zi=float( rand()%int(m_width) 
				- m_width/2.0f )*10.0f;		// Random Speed On Z Axis
			
			m_pSmoke[loop].xg=0.0f;									// Set Horizontal Pull To Zero
			m_pSmoke[loop].yg=m_speed/10.0f;								// Set Vertical Pull Downward
			m_pSmoke[loop].zg=0.0f;									// Set Pull On Z Axis To Zero
			m_pSmoke[loop].point = (bool)(loop%2) ;
		}
		delay = 0;
		
		
		assert( m_pTexture.isNull() );
		m_pTexture = 
			vgCore::TextureManager::getSingleton().getTexturePtr( m_texturename );
		
		
	}
	
	void vgSmoke::Render(GLvoid)										// Here's Where We Do All The Drawing
	{
		/*glEnable*/glDisable(GL_TEXTURE_2D) ;
		
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
		glEnable/*glDisable*/(GL_BLEND) ;
		glDisable/*glEnable*/(GL_DEPTH_TEST) ;
		
		//	glBindTexture(GL_TEXTURE_2D , m_pTexture) ;								// Enable Blending
		m_pTexture->useBind();
		
		for (GLuint loop=0;loop<m_nParticleCount;loop++)					// Loop Through All The Particles
		{
			if (m_pSmoke[loop].active)							// If The Particle Is Active
			{
				float x=m_pSmoke[loop].x;						// Grab Our Particle X Position
				float y=m_pSmoke[loop].y;						// Grab Our Particle Y Position
				float z=m_pSmoke[loop].z;					// Particle Z Pos + Zoom
				
				// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
				glColor4f(m_pSmoke[loop].r,m_pSmoke[loop].g,m_pSmoke[loop].b,m_pSmoke[loop].life);
				
				if (m_pSmoke[loop].point)
				{			
					glPointSize(1.0f);
					glBegin(GL_POINTS);
					glVertex3f(x, y, z);
					glEnd();
				}
				else
				{	
					glBegin(GL_TRIANGLE_STRIP);						
					glTexCoord2d(1,1); glVertex3f(x+0.05f/*0.5f*/,y+0.05f/*0.5f*/,z); 
					glTexCoord2d(0,1); glVertex3f(x-0.05f/*0.5f*/,y+0.05f/*0.5f*/,z); 
					glTexCoord2d(1,0); glVertex3f(x+0.05f/*0.5f*/,y-0.05f/*0.5f*/,z); 
					glTexCoord2d(0,0); glVertex3f(x-0.05f/*0.5f*/,y-0.05f/*0.5f*/,z); 
					glEnd();
				}
				
				// 			glPushMatrix();
				//			glTranslatef(x,y,z);
				// 			gluSphere(m_Sphere,0.05,4,4);
				// 			glPopMatrix();
				
				m_pSmoke[loop].x+=m_pSmoke[loop].xi/(slowdown*1000);
				m_pSmoke[loop].y+=m_pSmoke[loop].yi/(slowdown*1000);
				m_pSmoke[loop].z+=m_pSmoke[loop].zi/(slowdown*1000);
				
				m_pSmoke[loop].xi+=m_pSmoke[loop].xg;			// Take Pull On X Axis Into Account
				m_pSmoke[loop].yi+=m_pSmoke[loop].yg;			// Take Pull On Y Axis Into Account
				m_pSmoke[loop].zi+=m_pSmoke[loop].zg;			// Take Pull On Z Axis Into Account
				m_pSmoke[loop].life-=m_pSmoke[loop].fade;		// Reduce Particles Life By 'Fade'
				
				if (m_pSmoke[loop].life<0.0f)					// If Particle Is Burned Out
				{
					m_pSmoke[loop].life=1.0f;					// Give It New Life
					m_pSmoke[loop].fade=float(rand()%80)/1000.0f+
						/*0.003f*/0.02f;	// Random Fade Speed
						m_pSmoke[loop].x=m_Position.x ;						
					m_pSmoke[loop].y=m_Position.y ;					
					m_pSmoke[loop].z=m_Position.z ;						
					m_pSmoke[loop].xi=xspeed+float( rand()%int(m_width) 
						- m_width/2.0f )*10.0f;		// Random Speed On X Axis
					m_pSmoke[loop].yi=yspeed+float( rand()%int(m_height)
						- m_width/2.0f )*10.0f;		// Random Speed On Y Axis
					m_pSmoke[loop].zi=float( rand()%int(m_width) 
						- m_width/2.0f )*10.0f;		// Random Speed On Z Axis
					m_pSmoke[loop].r=colors[colorIndex][0];			
					m_pSmoke[loop].g=colors[colorIndex][1];			
					m_pSmoke[loop].b=colors[colorIndex][2];		
				}
				
				
			}
		}
		
		glEnable(GL_DEPTH_TEST) ;	
		glDisable(GL_BLEND) ;
		glDisable(GL_TEXTURE_2D) ;
	}
	
	void vgSmoke::SetCenter(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
	
	void vgSmoke::SetCount( int count/*=MAX_PARTICLES */ )
	{
		m_nParticleCount = count;
	}
	
		
	
	BoundingBox vgSmoke::ComputeBoundBox()
	{
		float	minFadeSpeed= 0.02f;
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



	
	//void vgSmoke::WriteNodeToVG(CFile &fp)	//写入文件
	//{
	//	int i;

	//	i = VG_PARTICLE;
	//	long newpos;

	//	//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

	//	Posinfile = fp.GetPosition();

	//	fp.Write(&nodelength, sizeof(long));			
	//	fp.Write(&i , sizeof(int));	               //写类型type

	//	i = 2;									//写烟类型

	//	fp.Write(&i, sizeof(int));
	//	fp.Write(m_LayerName , 20);		

	//	fp.Write(m_name, 20);

	//	fp.Write(&m_isVisible, sizeof(bool));			//写可见性标记

	//	/*	char name[20]=" ";*/			
	//	fp.Write(m_texturename.c_str(), 20);			//写材质名

	//	fp.Write(&m_Position.x , sizeof(float));		//写节点中心点位置
	//	fp.Write(&m_Position.y, sizeof(float));	
	//	fp.Write(&m_Position.z , sizeof(float));

	//	fp.Write(&m_height, sizeof(float));	//写粒子属性 含高度、宽度、速度、大小
	//	fp.Write(&m_width, sizeof(float));
	//	fp.Write(&m_speed, sizeof(float));
	//	fp.Write(&m_PartLenth, sizeof(float));
	//	fp.Write(&m_PartWidth, sizeof(float));

	//	fp.Write(&m_nParticleCount, sizeof(int));		//写粒子数目
	//	newpos = fp.GetPosition();

	//	nodelength = newpos - Posinfile- sizeof(long);

	//	fp.Seek(Posinfile, CFile::begin);

	//	fp.Write(&nodelength, sizeof(long));

	//	fp.SeekToEnd();
	//}	//	WriteNodeToVG(CFile &fp)

	
	void vgSmoke::UpdatePos()
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

}		//namespace vgCore