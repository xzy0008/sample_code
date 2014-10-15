#include "stdafx.h"
#include "particle.h"

PFNGLMULTITEXCOORD2FARBPROC	   glParticleMultiTexCoord2fARB	    = NULL;

Particle::Particle(PFNGLMULTITEXCOORD2FARBPROC multiTexFunc) :
                       m_particleHeading(0.0f, 1.0f, 0.0f), m_particleEnabled(false), m_particleAge(0.0f),
                       m_particleInitialColour(1.0f, 1.0f, 1.0f), m_particleFinalColour(1.0f, 1.0f, 1.0f),
                       m_particleInitialSize(0.0f), m_particleSpeed(0.0f),
                       m_particleFinalSize(0.0f), m_particleOriginalAge(0.0f), m_particleSizeDelta(0.0f),
                       m_particleInitialAlpha(1.0f), m_particleFinalAlpha(1.0f), m_particleAlphaDelta(0.0f)
{
   glParticleMultiTexCoord2fARB = multiTexFunc;

   this->m_InitialPos.m_X=0;
   this->m_InitialPos.m_Y=0;
   this->m_InitialPos.m_Z=0;
}

Particle::~Particle(void)
{
}

GLvoid Particle::Enable(GLboolean enableParticle)
{
   // enable/disable the particle
   m_particleEnabled = enableParticle;
}

GLboolean Particle::Render(GLfloat deltaTime, float theta)
{
   // update the particles age
   m_particleAge -= deltaTime;

   // return false if this particle is dead
   if (m_particleAge < 0.0f)
   {
	   m_particleAge=m_particleOriginalAge;
	   m_particlePos=m_InitialPos;
   }

   // update the position
   static int times=0;
   static float Viberate=0;
   times++;
   if(times==4)
   {
	   times=0;
	   Viberate=(float)rand()/RAND_MAX*0.03-0.015;
   }
   m_particlePos.Set(m_particlePos.X()+(m_particleSpeed*deltaTime)*m_particleHeading.X()+times*Viberate,
                     m_particlePos.Y()+(m_particleSpeed*deltaTime)*m_particleHeading.Y(),
                     m_particlePos.Z()+(m_particleSpeed*deltaTime)*m_particleHeading.Z()+times*Viberate);

   // update the size
   GLfloat agePercentage = (m_particleOriginalAge - m_particleAge)/m_particleOriginalAge;
   GLfloat finalSize = m_particleInitialSize + (m_particleSizeDelta * agePercentage);

   // update the colour
   Vector3D finalColour = m_particleInitialColour + (m_particleColourDelta * agePercentage);

   // update the alpha
   GLfloat finalAlpha = m_particleInitialAlpha + (m_particleAlphaDelta * agePercentage);

   // draw the particle


   glPushMatrix();
      //glColor4f(finalColour.X(), finalColour.Y(), finalColour.Z(), finalAlpha);
		glTranslatef(m_particlePos.X(), m_particlePos.Y(), m_particlePos.Z());
	  //GLfloat theta=1.0;//=atan(my3DSCene.m_cCamera.m_ViewDerection.x/my3DSCene.m_cCamera.m_ViewDerection.y);
	  //theta=theta*180.0/PI;
	  glRotatef(theta,0.0,1.0,0.0);

      glBegin(GL_TRIANGLE_STRIP);
         glParticleMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0, 0.0); glVertex3f(-finalSize/2.0f, -finalSize/2.0f, 0.0f);
         glParticleMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 0.0); glVertex3f(finalSize/2.0f, -finalSize/2.0f, 0.0f);
         glParticleMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0, 1.0); glVertex3f(-finalSize/2.0f, finalSize/2.0f, 0.0f);
         glParticleMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 1.0); glVertex3f(finalSize/2.0f, finalSize/2.0f, 0.0f);
      glEnd();
   glPopMatrix();

   return true;
}

const Vector3D Particle::GetPos(void) const
{
   return m_particlePos;
}

const Vector3D Particle::GetInitialColour(void) const
{
   return m_particleInitialColour;
}

const Vector3D Particle::GetFinalColour(void) const
{
   return m_particleFinalColour;
}

const Vector3D Particle::GetHeading(void) const
{
   return m_particleHeading;
}

const GLfloat Particle::GetSpeed(void) const
{
   return m_particleSpeed;
}

const GLfloat Particle::GetAge(void) const
{
   return m_particleAge;
}

const GLfloat Particle::GetInitialSize(void) const
{
   return m_particleInitialSize;
}

const GLfloat Particle::GetFinalSize(void) const
{
   return m_particleFinalSize;;
}

const GLfloat Particle::GetInitialAlpha(void) const
{
   return m_particleInitialAlpha;
}

const GLfloat Particle::GetFinalAlpha(void) const
{
   return m_particleFinalAlpha;
}

GLvoid Particle::SetPos(const Vector3D newPos)
{
	m_particleAge=((float)rand()/RAND_MAX)*m_particleOriginalAge;
	m_particlePos.Set(newPos.X()+m_particleSpeed*(m_particleOriginalAge-m_particleAge)*m_particleHeading.X(),
		newPos.Y()+m_particleSpeed*(m_particleOriginalAge-m_particleAge)*m_particleHeading.Y(),
		newPos.Z()+m_particleSpeed*(m_particleOriginalAge-m_particleAge)*m_particleHeading.Z());
}

GLvoid Particle::SetInitialColour(const Vector3D newColour)
{  
   m_particleInitialColour = newColour;
   m_particleColourDelta = m_particleFinalColour - m_particleInitialColour;
}

GLvoid Particle::SetFinalColour(const Vector3D newColour)
{
   m_particleFinalColour = newColour;
   m_particleColourDelta = m_particleFinalColour - m_particleInitialColour;
}

GLvoid Particle::SetHeading(const Vector3D newHeading)
{
   m_particleHeading = newHeading;
}

GLvoid Particle::SetSpeed(const GLfloat newSpeed)
{
   m_particleSpeed = newSpeed;
}

GLvoid Particle::SetAge(const GLfloat newAge)
{
   m_particleAge = newAge;
   m_particleOriginalAge = newAge;
}

GLvoid Particle::SetInitialSize(const GLfloat newSize)
{
   m_particleInitialSize = newSize;
   m_particleSizeDelta = m_particleFinalSize - m_particleInitialSize;
}

GLvoid Particle::SetFinalSize(const GLfloat newSize)
{
   m_particleFinalSize = newSize;
   m_particleSizeDelta = m_particleFinalSize - m_particleInitialSize;
}

GLvoid Particle::SetInitialAlpha(const GLfloat newAlpha)
{
   m_particleInitialAlpha = newAlpha;
   m_particleAlphaDelta = m_particleFinalAlpha - m_particleInitialAlpha;
}

GLvoid Particle::SetFinalAlpha(const GLfloat newAlpha)
{
   m_particleFinalAlpha = newAlpha;
   m_particleAlphaDelta = m_particleFinalAlpha - m_particleInitialAlpha;
}

