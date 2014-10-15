

#include "stdafx.h"
#include "particlesystem.h"

// this is necessary so that I can pass the glMultiTexCoordARB function down to the particles
PFNGLMULTITEXCOORD2FARBPROC	   glParticleSysMultiTexCoord2fARB	    = NULL;
namespace VR_Ocean
{
	ParticleSystem::ParticleSystem(PSTYPE type, Vector3D pos, PFNGLMULTITEXCOORD2FARBPROC multiTexFunc) 
				   : m_emitRate(0.0f), m_lastEmit(0.0f), m_type(type), m_pos(pos)
	{
	   glParticleSysMultiTexCoord2fARB = multiTexFunc;
	   m_TexIDgray=m_TexIDParticle=0;

	   // seed the random number generator

	   switch(m_type) 
	   {
	   case PST_FIRE:
		  {
			 SetEmitRate(20.0f);
		  }
   		break;
	   case PST_SMOKE:
		  {
			 SetEmitRate(5.0f);
		  }
   		break;
	   case PST_BUBBLES:
		  {
			 SetEmitRate(325.0f);
		  }
   		break;
	   }

	   //get cluster positions -- livenson 20090314
	   for (int i=0;i<CLUSTNUM;i++)
	   {
		   m_Cluster[i].SetX(rand()%200-100-50);
		   m_Cluster[i].SetZ(rand()%300-150);
	   }
	}

	ParticleSystem::~ParticleSystem(void)
	{
	   
	}

	GLvoid ParticleSystem::SetMaxCount(GLuint maxCount)
	{
	   m_maxParticleCount = maxCount;
	}

	GLvoid ParticleSystem::Render(GLfloat deltaTime, float theta)
	{
	   // work out how many new particles to emit

	   GLuint numToEmit = (GLuint)(deltaTime * m_emitRate);
	  

	   for (GLuint i = 0 ; i < numToEmit; i++)
	   {
		  AddParticle();
	   }

	   // render each particle in turn
	   std::list<Particle*>::iterator it;
	 //  std::list<Particle*> toDelete;
	  
	   for (it = m_particles.begin(); it != m_particles.end(); it++)
	   {
		  if (!(*it)->Render(deltaTime, theta))
		  {
			 // particle is dead -> schedule for deletion and removal from list
			// toDelete.push_back(*it);
		  }
	   }

	   // delete the particles that have died
	  /* for (it = toDelete.begin(); it != toDelete.end(); it++)
	   {
		  Particle* particleToDelete = *it;
		  m_particles.remove(particleToDelete);
		  SAFE_DELETE(particleToDelete);
	   }*/
	}

	GLvoid ParticleSystem::SetEmitRate(GLfloat emitRate)
	{
	   m_emitRate = emitRate;
	}

	GLvoid ParticleSystem::AddParticle(void)
	{
	   // if space is available, add to the list
	   if ((GLuint)m_particles.size() < m_maxParticleCount)
	   {
		  Particle* newParticle = NULL;
	      
		  switch(m_type)
		  {
		  case PST_FIRE:
			 {
				// create a fire particle system
				newParticle = new Particle(glParticleSysMultiTexCoord2fARB);

				if (newParticle)
				{
					newParticle->SetPos(m_pos);
				   newParticle->SetInitialSize(1.5f);
				   newParticle->SetFinalSize(0.8f);
				   newParticle->SetAge(3.0f);
				   newParticle->SetSpeed(2.0f);
				   newParticle->SetInitialAlpha(0.3f);
				   newParticle->SetFinalAlpha(1.0f);
	               
				   newParticle->SetInitialColour(Vector3D(0.7f, 0.3f, 0.0f));
				   newParticle->SetFinalColour(Vector3D(0.8f, 0.8f, 0.0f));

				   Vector3D particleHeading(0.0f, 1.0f, 0.0f);
				   // get a random number between 0 and 0.5 
				   GLfloat randNum = (GLfloat)(rand()%5)/10.0f;
				   particleHeading.SetX(-0.25f+randNum);
				   newParticle->SetHeading(particleHeading);
				}
			 }
      		break;
		  case PST_SMOKE:
			 {
				// create a smoke particle system
				newParticle = new Particle(glParticleSysMultiTexCoord2fARB);

				if (newParticle)
				{
				   newParticle->SetPos(m_pos);
				   newParticle->SetInitialSize(1.5f);
				   newParticle->SetFinalSize(3.0f);
				   newParticle->SetAge(10.0f);
				   newParticle->SetSpeed(1.0f);
				   newParticle->SetInitialAlpha(0.5f);
				   newParticle->SetFinalAlpha(0.0f);
	               
				   newParticle->SetInitialColour(Vector3D(0.4f, 0.4f, 0.4f));
				   newParticle->SetFinalColour(Vector3D(0.4f, 0.4f, 0.4f));

				   Vector3D particleHeading(0.0f, 1.0f, 0.0f);
				   // get a random number between 0 and 0.3 
				   GLfloat randNum = (GLfloat)(rand()%3)/10.0f;
				   particleHeading.SetX(-0.15f+randNum);
				   newParticle->SetHeading(particleHeading);
				}
			 }
      		break;
		  case PST_BUBBLES:
			 {
				// create a smoke particle system
				newParticle = new Particle(glParticleSysMultiTexCoord2fARB);

				if (newParticle)
				{
				   // get a random number to spread out the emmission
				   GLfloat randNum = (GLfloat)(rand()%240);
				   Vector3D pos = m_pos;
				   if(0)
				   {
						pos.SetX(-140.0f+randNum);
						randNum = (GLfloat)(rand()%340);
						pos.SetZ(-100.0f+randNum);
				   }
				   else
				   {
					   int Cluster=rand()%CLUSTNUM;
					   randNum=(float)((float)rand()/RAND_MAX*2-1);
					   pos.SetX(m_Cluster[Cluster].m_X+randNum);
					   randNum=(float)((float)rand()/RAND_MAX*2-1);
					   pos.SetZ(m_Cluster[Cluster].m_Z+randNum);
				   }

				   newParticle->m_InitialPos=pos;
				   newParticle->SetInitialSize(0.5f);
				   newParticle->SetFinalSize(0.2f);
				   newParticle->SetAge(4.5f);
				   newParticle->SetSpeed(12.0f);
				   newParticle->SetInitialAlpha(0.5f);
				   newParticle->SetFinalAlpha(0.5f);               
				   newParticle->SetInitialColour(Vector3D(1.0f, 1.0f, 1.0f));
				   newParticle->SetFinalColour(Vector3D(1.0f, 1.0f, 1.0f));
				   newParticle->SetPos(pos);
				}
			 }
      		break;
		  }

		  // add to the list
		  if (newParticle)
		  {
			 m_particles.push_back(newParticle);
		  }
	   }
	}

	GLvoid ParticleSystem::SetPos(Vector3D newPos)
	{
	   m_pos = newPos;
	}
	GLuint ParticleSystem::LoadTexture(const char *cFileName)
	{
		int UseGLNearest=1;
		int strLen = (GLuint)strlen(cFileName);
		GLuint TexterID;
		glGenTextures(1,&TexterID);

		if (tolower(cFileName[strLen-4]) == '.' && tolower(cFileName[strLen-3] == 'j')&& tolower(cFileName[strLen-2] == 'p') && tolower(cFileName[strLen-1] == 'g')
			||tolower(cFileName[strLen-4]) == '.' && tolower(cFileName[strLen-3] == 'b')&& tolower(cFileName[strLen-2] == 'm') && tolower(cFileName[strLen-1] == 'p'))
		{
			// jpeg file
			// IPictureLoader Image(m_pDC->m_hDC);
			IPictureLoader Image(NULL);

			if (!Image.LoadFromFile(cFileName))
			{
				char err[128];
				sprintf(err, "Error loading \"%s\"", cFileName); 
				AfxMessageBox(_T("Error load  particle texture"));
				return false;
			}

			glBindTexture(GL_TEXTURE_2D, TexterID);

			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,UseGLNearest ? GL_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,UseGLNearest ? GL_NEAREST : GL_LINEAR_MIPMAP_LINEAR);

			if (Image.GetColourDepth() == 24)
				gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image.GetWidth(), Image.GetHeight(), 
				GL_RGB, GL_UNSIGNED_BYTE, Image.GetData());
			else
				gluBuild2DMipmaps(GL_TEXTURE_2D, 4, Image.GetWidth(), Image.GetHeight(), 
				GL_RGBA, GL_UNSIGNED_BYTE, Image.GetData());
		}
		else
		{
			// assume tga
			TGALoader Image;

			if (!Image.LoadFromFile(cFileName))
			{
				char err[128];
				sprintf(err, "Error loading \"%s\"", cFileName); 
				AfxMessageBox(_T("Error load  particle texture"));
				return false;
			}

			glBindTexture(GL_TEXTURE_2D, TexterID);

			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

			if (Image.GetColourDepth() == 24)
				gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image.GetWidth(), Image.GetHeight(), 
				GL_RGB, GL_UNSIGNED_BYTE, Image.GetData());
			else
				gluBuild2DMipmaps(GL_TEXTURE_2D, 4, Image.GetWidth(), Image.GetHeight(), 
				GL_RGBA, GL_UNSIGNED_BYTE, Image.GetData());
		}

		return TexterID;
	}
}
