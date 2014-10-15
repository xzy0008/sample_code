

#pragma once
#include "Vector3D.h"
#include <GL/GL.h>
#include <GL/GLu.h>
//#include "glext.h"

// some useful macros
#define SAFE_DELETE(ptr) if (ptr) delete ptr; ptr = NULL
#define SAFE_ARRAY_DELETE(ptr) if (ptr) delete[] ptr; ptr = NULL

// properties of a square Particle (should be a abitrary mesh in a proper system) for a (simple) Particle system
using namespace VR_Ocean;
class Particle
{
public:
   Particle(PFNGLMULTITEXCOORD2FARBPROC multiTexFunc);
   virtual ~Particle(void);

   GLvoid Enable(GLboolean enableParticle=true);
   virtual GLboolean Render(GLfloat deltaTime, float theta=0.0);

   const Vector3D GetPos(void) const;
   const Vector3D GetInitialColour(void) const;
   const Vector3D GetFinalColour(void) const;
   const Vector3D GetHeading(void) const;
   const GLfloat  GetSpeed(void) const;
   const GLfloat  GetAge(void) const;
   const GLfloat  GetInitialSize(void) const;
   const GLfloat  GetFinalSize(void) const;
   const GLfloat  GetInitialAlpha(void) const;
   const GLfloat  GetFinalAlpha(void) const;

   GLvoid SetPos(const Vector3D newPos);
   GLvoid SetInitialColour(const Vector3D newColour);
   GLvoid SetFinalColour(const Vector3D newColour);
   GLvoid SetHeading(const Vector3D newHeading);
   GLvoid SetSpeed(const GLfloat newSpeed);
   GLvoid SetAge(const GLfloat newAge);
   GLvoid SetInitialSize(const GLfloat newSize);
   GLvoid SetFinalSize(const GLfloat newSize);
   GLvoid SetInitialAlpha(const GLfloat newSize);
   GLvoid SetFinalAlpha(const GLfloat newSize);
   Vector3D   m_InitialPos;//the initial position --livenson 20090313

private:
   Vector3D    m_particlePos;          // the current position of the particle
   Vector3D    m_particleInitialColour;// the colour of the particle
   Vector3D    m_particleFinalColour;  // the final colour of the particle
   GLfloat     m_particleSpeed;        // the speed (in units per second) of the aprticle
   Vector3D    m_particleHeading;      // the direction that the particle is heading
   GLboolean   m_particleEnabled;   
   GLfloat     m_particleAge;          // how much time the particle has left (0.0f is dead)
   GLfloat     m_particleOriginalAge;  // the initial age of the particle
   GLfloat     m_particleInitialSize;  // the initial size
   GLfloat     m_particleFinalSize;    // the final size
   GLfloat     m_particleSizeDelta;    // the difference between the initial and the final size
   Vector3D    m_particleColourDelta;  // the difference between the initial and the final colour
   GLfloat     m_particleInitialAlpha; // the initial alpha component of the particle
   GLfloat     m_particleFinalAlpha;   // the final alpha component of the particle
   GLfloat     m_particleAlphaDelta;   // difference between the initial and the final alpha

};
