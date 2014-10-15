

#pragma once
#include <list>
#include <GL/GL.h>
#include <GL/GLu.h>
#include "particle.h"
#include <time.h>
#include <stdlib.h>
#include "VOdefinition.h"
#include "Vector3D.h"
#include "TgaLoader.h"
#include "IPictureLoader.h"

// different types of particle system
namespace VR_Ocean
{
	typedef enum
	{
	   PST_FIRE,
	   PST_SMOKE,
	   PST_BUBBLES,
	} PSTYPE;

	#define CLUSTNUM 30

	class VO_EXPORT ParticleSystem
	{
	public:
	   ParticleSystem(PSTYPE type, Vector3D pos, PFNGLMULTITEXCOORD2FARBPROC multiTexFunc);
	   virtual ~ParticleSystem(void);

	   static GLuint LoadTexture(const char* cFileName);

	   GLvoid SetMaxCount(GLuint maxCount);
	   GLvoid Render(GLfloat deltaTime, float theta=0.0);
	   GLvoid SetEmitRate(GLfloat emitRate);
	   GLvoid SetPos(Vector3D newPos);

	   GLuint m_TexIDgray,m_TexIDParticle;

	private:
	   GLvoid AddParticle(void);

	private:
	   std::list<Particle*> m_particles;         // the particles in the system
	   GLuint               m_maxParticleCount;  // maximum number of particles in the system
	   GLfloat              m_emitRate;          // how many particles emmitted per second
	   GLfloat              m_lastEmit;          // the time since the last particle emmission
	   PSTYPE               m_type;              // the type of particle system (fire, rain etc etc)
	   Vector3D             m_pos;               // the position of the emmitter

	   //Record the position of every cluster --livenson 20090314
	   Vector3D   m_Cluster[CLUSTNUM];
	};
}