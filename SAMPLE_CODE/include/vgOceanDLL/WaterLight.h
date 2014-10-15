
#ifndef _CLIGHT_H
#define _CLIGHT_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "VOdefinition.h"

namespace VR_Ocean
{
	class VO_EXPORT CLight
	{

	public:

		class V4
		{
		public:
			V4(void)
			{
				x = y = z = l = 0;
			}
			V4( float _x, float _y, float _z, float _l = 0.0f )
			{
				x = _x;
				y = _y;
				z = _z;
				l = _l;
			}
			float x;
			float y;
			float z;
			float l;
		};

		CLight(void);

		~CLight(void);

		void update(void);

		void renderGLScene( V4 p);

		void drawLight(const V4 p, float pp, float theta );
	private:
		V4 *BasicPos;

		float *ColorArray,
				*Vertices;

		GLuint *Indices;
	};
}

#endif
